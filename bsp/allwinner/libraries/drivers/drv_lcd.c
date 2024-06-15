/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-04-12     RT-Thread    the first version
 * 2023-09-02     zbtrs        support sdl2
 */

#include "rtthread.h"
#include <rthw.h>
#include <string.h>
#include <stdatomic.h>

#include "interrupt.h"
#include "mmu.h"
#include "cache.h"

#ifdef BSP_USING_LCD

#include "drv_lcd.h"
#include "lcd_cfg.h"

#ifdef RT_USING_SMART
#include <page.h>
#include <lwp_user_mm.h>
#endif

#include <video/sunxi_display2.h>
#include <dfs_file.h>
#include "dev_disp.h"

#define DEFAULT_SCREEN (0)

#define LCD_DRV_FB_SZ (lcd_drv->lcd_info.width * lcd_drv->lcd_info.height * sizeof(rt_uint32_t))


enum state_buff
{
    EMPTY,
    FULL
};

enum lcd_evt
{
    LCD_EVT_VSYNC = 1,
};

struct buff_info
{
    rt_uint32_t *buff;
    rt_uint32_t *buff_phy;
    enum state_buff status;
};

/* kind of a candidate for the official lcd driver framework */
struct lcd_device
{
    struct rt_device lcd;
    struct rt_device fb;
    struct rt_device_graphic_info lcd_info; /* rtdef.h */
    struct rt_event lcd_evt;
    int use_screen; /* screen index */
    void *framebuffer;
    void *framebuffer_phy;

    atomic_uint refresh_flag;        /* atom flag,  0: nothing. 1:framebuffer ==> front_buf. 2:back_buf ==> front_buf.  */
    struct buff_info front_buf_info; /* TCON hardware framebuffer */
    struct buff_info back_buf_info;  /* rotate swap framebuffer */

    const struct lcd_cfg_panel_info *panel;
};
typedef struct lcd_device *lcd_device_t;

static struct disp_layer_config layer_cfg;
static struct lcd_device _lcd_device;
static const struct lcd_cfg_panel_info *_panel;
static int lcd_status = 0;
static rt_uint8_t lcd_bn = 80;
#define LCD_PWM_DEV_CHANNEL 1

extern void rt_hw_cpu_dcache_clean(void *addr, int size);
extern int disp_ioctl(int cmd, void *arg);
extern int disp_probe(void);

struct lcd_device *g_lcd = RT_NULL;

/* set up the lcd pin function */
static void lcd_gpio_config(void)
{
    int i;
    gpio_pin_t pin;
    gpio_muxsel_t function_index;
    gpio_driving_level_t level;

    if (_panel->bl_pin >= 0)
    {
        hal_gpio_set_direction(_panel->bl_pin, GPIO_DIRECTION_OUTPUT); // bl_pin
        hal_gpio_set_driving_level(_panel->bl_pin, 3);
        hal_gpio_set_data(_panel->bl_pin, _panel->bl_level);
    }

    if (_panel->pwr_pin >= 0)
    {
        hal_gpio_set_direction(_panel->pwr_pin, GPIO_DIRECTION_OUTPUT); // pwr_pin
        hal_gpio_set_driving_level(_panel->pwr_pin, 3);
        hal_gpio_set_data(_panel->pwr_pin, 0);
        rt_thread_delay(10);
        hal_gpio_set_data(_panel->pwr_pin, _panel->pwr_level);
        rt_thread_delay(10);
        lcd_status = _panel->pwr_level;
    }

    if (_panel->bl_mode == 0)
    {
        hal_gpio_set_direction(_panel->bl_gpio_pin, GPIO_DIRECTION_OUTPUT);
        hal_gpio_set_driving_level(_panel->bl_gpio_pin, 3);
        hal_gpio_set_data(_panel->bl_gpio_pin, _panel->bl_gpio_level);
    }
    else
    {
        lcd_bn = _panel->bl_pwm_val;
        set_lcd_backlight(lcd_bn);
    }
}

void *lcd_get_framebuffer(void *dev)
{
    return ((struct lcd_device *)dev)->framebuffer;
}

s32 lcd_vsync_event_process(u32 sel)
{
    lcd_device_t lcd_drv = &_lcd_device;
    uint32_t refresh_flag = atomic_exchange(&lcd_drv->refresh_flag, 0); // read-modify-write, read & clean.

    if (refresh_flag != 0)
    {
        uint32_t len = (uint32_t)lcd_drv->lcd_info.width * lcd_drv->lcd_info.height * (lcd_drv->lcd_info.bits_per_pixel / 8);
        uint32_t len_stage1 = 1024;
        void *dst = lcd_drv->front_buf_info.buff;
        const void *src = lcd_drv->framebuffer;

        if (refresh_flag == 1)
        {
            src = lcd_drv->framebuffer;
        }
        else if (refresh_flag == 2)
        {
            src = lcd_drv->back_buf_info.buff;
        }
        else
        {
            // TODO: error
        }

        memcpy((uint32_t *)dst, (uint32_t *)src, len_stage1);
        rt_hw_cpu_dcache_clean(dst, len_stage1);

        memcpy((uint32_t *)(dst + len_stage1), (uint32_t *)(src + len_stage1), len - len_stage1);
        rt_hw_cpu_dcache_clean((uint32_t *)(dst + len_stage1), len - len_stage1);

        rt_event_send(&lcd_drv->lcd_evt, LCD_EVT_VSYNC);
    }

    rt_event_send(&lcd_drv->lcd_evt, LCD_EVT_VSYNC);
}

static void _framebuffer_rotate_mirror(void *src_buf, void *dst_buf,
                                       const struct rt_device_graphic_info *lcd_info, const struct lcd_cfg_panel_info *_panel_info)
{
    lcd_device_t lcd_drv = &_lcd_device;
    memcpy(dst_buf, src_buf, LCD_DRV_FB_SZ);
}

/* Multi-layer is not supported now. */
#ifdef GUIENGINE_USING_MULTI_LAYER
#include <rtgui/rtgui_layer.h>
struct debe_info
{
    int index;
    void *buffer;
    rt_uint32_t bf_size;
};
static struct debe_info _debe_use[3];
#endif

/* pixel format, only 565 (2 bytes) or 666 (4 bytes) are supported */
static inline int _lcd_format_get(rt_uint8_t pixel_format)
{
    switch (pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        return DISP_FORMAT_RGB_565;
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        return DISP_FORMAT_ARGB_8888;
    default:
        return -1;
    }
}

static int _lcd_drv_init(lcd_device_t lcd_drv)
{
    unsigned long arg[6] = {0};
    void *framebuffer = RT_NULL;
    void *frontbuf = RT_NULL;
    void *backbuf = RT_NULL;

    /*
     * The event is used for the synchronization between updating the
     * framebuffer and flushing the screen.
     */
    rt_event_init(&lcd_drv->lcd_evt, "lcd_evt", RT_IPC_FLAG_FIFO);

    /* the lcd device information defined by RT-Thread */
    arg[0] = lcd_drv->use_screen;
    lcd_drv->lcd_info.width = (rt_uint16_t)disp_ioctl(DISP_GET_SCN_WIDTH, arg);
    lcd_drv->lcd_info.height = (rt_uint16_t)disp_ioctl(DISP_GET_SCN_HEIGHT, arg);
    lcd_drv->lcd_info.bits_per_pixel = 32;
    lcd_drv->lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_ARGB888; /* should be coherent to adding layers */

    /* allocate the framebuffer, the front buffer and the back buffer */
    /* framebuffer */
#ifdef RT_USING_SMART
    framebuffer = rt_pages_alloc(rt_page_bits(LCD_DRV_FB_SZ));
#else
    framebuffer = rt_malloc(LCD_DRV_FB_SZ);
#endif
    if (!framebuffer)
    {
        rt_kprintf("malloc framebuffer fail\n");
        goto out;
    }
    lcd_drv->lcd_info.framebuffer = framebuffer;
    lcd_drv->framebuffer = framebuffer;
    lcd_drv->framebuffer_phy = (void *)((size_t)framebuffer + PV_OFFSET);
    memset(framebuffer, 0, LCD_DRV_FB_SZ);
    rt_hw_cpu_dcache_clean(lcd_drv->framebuffer, LCD_DRV_FB_SZ);
#ifdef RT_USING_SMART
    frontbuf = rt_pages_alloc(rt_page_bits(LCD_DRV_FB_SZ));
#else
    frontbuf = rt_malloc(LCD_DRV_FB_SZ);
#endif
    if (!frontbuf)
    {
        rt_kprintf("malloc frontbuf fail\n");
        goto out;
    }
    lcd_drv->front_buf_info.buff = frontbuf;
    lcd_drv->front_buf_info.buff_phy = (void *)((size_t)frontbuf + PV_OFFSET);
    memset(frontbuf, 0, LCD_DRV_FB_SZ);
    rt_hw_cpu_dcache_clean(lcd_drv->front_buf_info.buff, LCD_DRV_FB_SZ);

    if ((lcd_drv->panel) && (lcd_drv->panel->swap_flag != 0))
    {
        /* backbuf */
#ifdef RT_USING_SMART
        backbuf = rt_pages_alloc(rt_page_bits(LCD_DRV_FB_SZ));
#else
        backbuf = rt_malloc(LCD_DRV_FB_SZ);
#endif
        if (!backbuf)
        {
            rt_kprintf("malloc backbuf fail\n");
            goto out;
        }
        lcd_drv->back_buf_info.buff = backbuf;
        lcd_drv->back_buf_info.buff_phy = (void *)((size_t)backbuf + PV_OFFSET);
        memset(backbuf, 0, LCD_DRV_FB_SZ);
        rt_hw_cpu_dcache_clean(lcd_drv->back_buf_info.buff, LCD_DRV_FB_SZ);
    }

    return RT_EOK;
out:
    if (framebuffer)
    {
#ifdef RT_USING_SMART
        rt_free_align(framebuffer);
#else
        rt_free(framebuffer);
#endif
    }

    if (frontbuf)
    {
#ifdef RT_USING_SMART
        rt_free_align(frontbuf);
#else
        rt_free(frontbuf);
#endif
    }

    if (backbuf)
    {
#ifdef RT_USING_SMART
        rt_free_align(backbuf);
#else
        rt_free(backbuf);
#endif
    }

    return -RT_ERROR;
}

static int _lcd_layer_init(lcd_device_t lcd_drv)
{
    int format;
    int ret;
    unsigned long arg[6] = {0};

    format = _lcd_format_get(lcd_drv->lcd_info.pixel_format);
    if (format < 0)
    {
        rt_kprintf("lcd init faile pixel_format:%d\n", lcd_drv->lcd_info.pixel_format);
        return -RT_ERROR;
    }

    // config layer info
    memset(&layer_cfg, 0, sizeof(layer_cfg));
    layer_cfg.info.b_trd_out = 0;
    layer_cfg.channel = de_feat_get_num_vi_chns(lcd_drv->use_screen); // skip vi channel
    layer_cfg.layer_id = 0;
    layer_cfg.info.fb.format = format;
    layer_cfg.info.fb.crop.x = 0;
    layer_cfg.info.fb.crop.y = 0;
    layer_cfg.info.fb.crop.width = lcd_drv->lcd_info.width;
    layer_cfg.info.fb.crop.height = lcd_drv->lcd_info.height;
    layer_cfg.info.fb.crop.width = layer_cfg.info.fb.crop.width << 32;
    layer_cfg.info.fb.crop.height = layer_cfg.info.fb.crop.height << 32;
    layer_cfg.info.fb.align[0] = 4;
    layer_cfg.info.mode = 0; // LAYER_MODE_BUFFER
    layer_cfg.info.alpha_mode = 1;
    layer_cfg.info.alpha_value = 255;
    layer_cfg.info.zorder = 0;
    layer_cfg.info.screen_win.x = 0;
    layer_cfg.info.screen_win.y = 0;
    layer_cfg.info.screen_win.width = lcd_drv->lcd_info.width;
    layer_cfg.info.screen_win.height = lcd_drv->lcd_info.height;

    layer_cfg.info.fb.size[0].width = lcd_drv->lcd_info.width;
    layer_cfg.info.fb.size[0].height = lcd_drv->lcd_info.height;
    layer_cfg.info.fb.size[1].width = lcd_drv->lcd_info.width;
    layer_cfg.info.fb.size[1].height = lcd_drv->lcd_info.height;
    layer_cfg.info.fb.size[2].width = lcd_drv->lcd_info.width;
    layer_cfg.info.fb.size[2].height = lcd_drv->lcd_info.height;

    layer_cfg.info.fb.addr[0] = (size_t)lcd_drv->front_buf_info.buff_phy;

    /* INTERLEAVED */
    layer_cfg.info.fb.addr[0] = (unsigned long long)(layer_cfg.info.fb.addr[0] + lcd_drv->lcd_info.width * lcd_drv->lcd_info.height / 3 * 0);
    layer_cfg.info.fb.addr[1] = (unsigned long long)(layer_cfg.info.fb.addr[0] + lcd_drv->lcd_info.width * lcd_drv->lcd_info.height / 3 * 1);
    layer_cfg.info.fb.addr[2] = (unsigned long long)(layer_cfg.info.fb.addr[0] + lcd_drv->lcd_info.width * lcd_drv->lcd_info.height / 3 * 2);
    layer_cfg.info.fb.trd_right_addr[0] = (unsigned int)(layer_cfg.info.fb.addr[0] + lcd_drv->lcd_info.width * lcd_drv->lcd_info.height * 3 / 2);
    layer_cfg.info.fb.trd_right_addr[1] = (unsigned int)(layer_cfg.info.fb.trd_right_addr[0] + lcd_drv->lcd_info.width * lcd_drv->lcd_info.height);
    layer_cfg.info.fb.trd_right_addr[2] = (unsigned int)(layer_cfg.info.fb.trd_right_addr[0] + lcd_drv->lcd_info.width * lcd_drv->lcd_info.height * 3 / 2);

    layer_cfg.enable = 1;

    arg[0] = lcd_drv->use_screen;
    arg[1] = (unsigned long)&layer_cfg;
    arg[2] = 1;
    arg[3] = 0;
    ret = disp_ioctl(DISP_LAYER_SET_CONFIG, (void *)arg);
    if (0 != ret)
    {
        rt_kprintf("fail to set layer cfg %d\n", ret);
        return -RT_ERROR;
    }

    arg[0] = lcd_drv->use_screen;
    arg[1] = 1; // enable
    arg[2] = 0;
    ret = disp_ioctl(DISP_VSYNC_EVENT_EN, (void *)arg);
    if (0 != ret)
    {
        rt_kprintf("fail to set vsync enable %d\n", ret);
        return -RT_ERROR;
    }

    return RT_EOK;
}

/* Add the first layer, then enable the interrupt */
static rt_err_t rt_lcd_init(rt_device_t dev)
{
    lcd_device_t lcd_drv = (lcd_device_t)dev;

    RT_ASSERT(lcd_drv != RT_NULL);

    static int lcd_init = 0;

    if (lcd_init)
    {
        return RT_EOK;
    }
    lcd_init = 1;

    _panel = load_lcd_config_from_xml();
    lcd_drv->panel = _panel;

    if (disp_probe() != 0)
    {
        rt_kprintf("lcd disp probe failure\n");
        return -RT_ERROR;
    }

    lcd_gpio_config();

    if (_lcd_drv_init(lcd_drv) != RT_EOK)
    {
        rt_kprintf("lcd drv init failure\n");
        return -RT_ERROR;
    }

    if (_lcd_layer_init(lcd_drv) != RT_EOK)
    {
        rt_kprintf("disp layer init failure\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

void turn_on_lcd_backlight(void)
{
    if (_panel->bl_pin >= 0)
    {
        hal_gpio_set_direction(_panel->bl_pin, GPIO_DIRECTION_OUTPUT); // bl_pin
        hal_gpio_set_driving_level(_panel->bl_pin, 3);
        hal_gpio_set_data(_panel->bl_pin, 1);
    }

    if (_panel->pwr_pin >= 0)
    {
        hal_gpio_set_direction(_panel->pwr_pin, GPIO_DIRECTION_OUTPUT); // pwr_pin
        hal_gpio_set_driving_level(_panel->pwr_pin, 3);
        hal_gpio_set_data(_panel->pwr_pin, 1);
    }
    if (_panel->bl_mode == 0)
    {
        hal_gpio_set_direction(_panel->bl_gpio_pin, GPIO_DIRECTION_OUTPUT);
        hal_gpio_set_driving_level(_panel->bl_gpio_pin, 3);
        hal_gpio_set_data(_panel->bl_gpio_pin, 1);
    }
    else
    {
        struct rt_device_pwm *pwm_dev;
        pwm_dev = (struct rt_device_pwm *)rt_device_find(_panel->bl_pwm_name);
        if (pwm_dev == RT_NULL)
        {
            rt_kprintf("%s open fail\n", _panel->bl_pwm_name);
            return;
        }
        rt_pwm_set(pwm_dev, LCD_PWM_DEV_CHANNEL, 1000000000 / _panel->bl_pwm_hz, lcd_bn * (10000000 / _panel->bl_pwm_hz));
        rt_pwm_enable(pwm_dev, LCD_PWM_DEV_CHANNEL);
    }
    lcd_status = 1;
}

void turn_down_lcd_backlight(void)
{

    if (_panel->bl_pin >= 0)
    {
        hal_gpio_set_direction(_panel->bl_pin, GPIO_DIRECTION_OUTPUT); // bl_pin
        hal_gpio_set_driving_level(_panel->bl_pin, 3);
        hal_gpio_set_data(_panel->bl_pin, 0);
    }

    if (_panel->pwr_pin >= 0)
    {
        hal_gpio_set_direction(_panel->pwr_pin, GPIO_DIRECTION_OUTPUT); // pwr_pin
        hal_gpio_set_driving_level(_panel->pwr_pin, 3);
        hal_gpio_set_data(_panel->pwr_pin, 0);
    }
    if (_panel->bl_mode == 0)
    {
        hal_gpio_set_direction(_panel->bl_gpio_pin, GPIO_DIRECTION_OUTPUT);
        hal_gpio_set_driving_level(_panel->bl_gpio_pin, 3);
        hal_gpio_set_data(_panel->bl_gpio_pin, 0);
    }
    else
    {
        struct rt_device_pwm *pwm_dev;
        pwm_dev = (struct rt_device_pwm *)rt_device_find(_panel->bl_pwm_name);
        if (pwm_dev == RT_NULL)
        {
            rt_kprintf("%s open fail\n", _panel->bl_pwm_name);
            return;
        }
        rt_pwm_set(pwm_dev, LCD_PWM_DEV_CHANNEL, 1000000000 / _panel->bl_pwm_hz, 0 * (10000000 / _panel->bl_pwm_hz));
        rt_pwm_enable(pwm_dev, LCD_PWM_DEV_CHANNEL);
    }
    lcd_status = 0;
    return;
}

void set_lcd_backlight(rt_uint8_t value)
{
    struct rt_device_pwm *pwm_dev;
    pwm_dev = (struct rt_device_pwm *)rt_device_find(_panel->bl_pwm_name);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("%s open fail\n", _panel->bl_pwm_name);
        return;
    }
    rt_pwm_set(pwm_dev, LCD_PWM_DEV_CHANNEL, 1000000000 / _panel->bl_pwm_hz, value * (10000000 / _panel->bl_pwm_hz));
    rt_pwm_enable(pwm_dev, LCD_PWM_DEV_CHANNEL);
}

rt_uint8_t get_lcd_backlight(void)
{
    int result = 0;
    struct rt_device_pwm *pwm_dev;
    struct rt_pwm_configuration cfg = {0};

    pwm_dev = (struct rt_device_pwm *)rt_device_find(_panel->bl_pwm_name);
    cfg.channel = LCD_PWM_DEV_CHANNEL;
    rt_pwm_get(pwm_dev, LCD_PWM_DEV_CHANNEL);

    return cfg.pulse / (10000000 / _panel->bl_pwm_hz);
}

static rt_err_t rt_lcd_control(rt_device_t dev, int cmd, void *args)
{
    struct lcd_device *lcd_drv = (struct lcd_device *)dev;

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        unsigned long arg[6] = {0};
        int ret;

        // clean event.
        rt_event_recv(&lcd_drv->lcd_evt, LCD_EVT_VSYNC, RT_EVENT_FLAG_CLEAR | RT_EVENT_FLAG_OR, 0, NULL);

        // rotate and set refresh_flag
        if ((lcd_drv->panel) && (lcd_drv->panel->swap_flag != 0))
        {
            _framebuffer_rotate_mirror(lcd_drv->framebuffer, lcd_drv->back_buf_info.buff, &lcd_drv->lcd_info, _panel);
            rt_hw_cpu_dcache_clean(lcd_drv->back_buf_info.buff, LCD_DRV_FB_SZ);
            atomic_store(&lcd_drv->refresh_flag, 2); // lcd_drv->refresh_flag = 2;
        }
        else
        {
            atomic_store(&lcd_drv->refresh_flag, 1); // lcd_drv->refresh_flag = 1;
        }

        // wait irq
        rt_err_t result = rt_event_recv(&lcd_drv->lcd_evt, LCD_EVT_VSYNC, RT_EVENT_FLAG_CLEAR | RT_EVENT_FLAG_OR, RT_TICK_PER_SECOND / 20, NULL);
        if (result != RT_EOK)
        {
            rt_kprintf("RTGRAPHIC_CTRL_RECT_UPDATE wait LCD_EVT_VSYNC:%d\n", result);
        }

        break;
    }
    case RTGRAPHIC_CTRL_POWERON:
        if (lcd_status == 0)
        {
#ifdef WATCH_APP_FWK_USING_SCREEN_MGT
            extern void watch_screen_time_update(void);
            watch_screen_time_update();
#endif
            turn_on_lcd_backlight();
            rt_kprintf("lcd driver control power on.\n");
            lcd_status = 1;
        }
        break;
    case RTGRAPHIC_CTRL_POWEROFF:
        if (lcd_status == 1)
        {
            lcd_status = 0;
            turn_down_lcd_backlight();
            rt_kprintf("lcd driver control power off.\n");
        }
        break;
    case RTGRAPHIC_CTRL_SET_BRIGHTNESS:
        lcd_bn = *((rt_uint8_t *)args);
        // TODO::if can SET_BRIGHTNESS
        set_lcd_backlight(lcd_bn);
        rt_kprintf("lcd driver control set brightness: %d.\n", lcd_bn);
        break;

    case RTGRAPHIC_CTRL_GET_BRIGHTNESS:
        lcd_bn = get_lcd_backlight();
        *((rt_uint8_t *)args) = lcd_bn;
        // TODO::if can GET_BRIGHTNESS
        rt_kprintf("lcd driver control get brightness: %d.\n", lcd_bn);
        break;
    case RTGRAPHIC_CTRL_GET_INFO:
        memcpy(args, &lcd_drv->lcd_info, sizeof(struct rt_device_graphic_info));
        break;
    case FBIOGET_FSCREENINFO:
    {
        struct fb_fix_screeninfo *info = (struct fb_fix_screeninfo *)args;
        strncpy(info->id, "lcd", sizeof(info->id));
        info->smem_len = LCD_DRV_FB_SZ;
#ifdef RT_USING_SMART
        info->smem_start = (size_t)lwp_map_user_phy(lwp_self(), RT_NULL, lcd_drv->framebuffer_phy, info->smem_len, 1);
#else
        info->smem_start = (size_t)lcd_drv->framebuffer_phy;
#endif
        info->line_length = lcd_drv->lcd_info.width * sizeof(rt_uint32_t);
        memset((void *)info->smem_start, 0, info->smem_len);
    }
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }
    return RT_EOK;
}

static rt_err_t fb_open(rt_device_t dev,rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t fb_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t fb_control(rt_device_t dev, int cmd, void *args)
{
    switch(cmd) {
        case FBIOGET_PIXELINFO:
        {
            int *fmt = (int *)args;
            *fmt = RTGRAPHIC_PIXEL_FORMAT_ARGB888;
            break;
        }
        case FBIOPAN_DISPLAY:
        {
            struct lcd_device *lcd_drv = g_lcd;
            rt_hw_cpu_dcache_clean(lcd_drv->framebuffer, LCD_DRV_FB_SZ);
            rt_lcd_control((rt_device_t)g_lcd, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
            break;
        }
        case FBIOGET_FSCREENINFO:
        {
            rt_lcd_control((rt_device_t)g_lcd,FBIOGET_FSCREENINFO,args);
            break;
        }
        case FBIOGET_VSCREENINFO:
        {
            struct lcd_device *lcd_drv = g_lcd;
            struct fb_var_screeninfo *info = (struct fb_var_screeninfo *)args;
            info->xres = lcd_drv->lcd_info.width;
            info->yres = lcd_drv->lcd_info.height;
            break;
        }
        case RT_FIOMMAP2:
        {
            struct dfs_mmap2_args *mmap2 = (struct dfs_mmap2_args *)args;
            if (mmap2)
            {
                mmap2->ret = lwp_map_user_phy(lwp_self(),RT_NULL,g_lcd->framebuffer,mmap2->length,1);
            }
            else
            {
                return -EIO;
            }

            break;
        }
        default:
            break;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops fb_ops =
{
    RT_NULL,
    fb_open,
    fb_close,
    RT_NULL,
    RT_NULL,
    fb_control
};
#endif

/* register framebuffer device */
static int fb_init(rt_device_t fb)
{
    static rt_bool_t fb_init_ok = RT_FALSE;

    if (fb_init_ok)
    {
        return 0;
    }
    RT_ASSERT(!rt_device_find("fb0"));
    fb->type    = RT_Device_Class_Miscellaneous;

#ifdef RT_USING_DEVICE_OPS
    fb->ops     = &fb_ops;
#else

    fb->init    = RT_NULL;
    fb->open    = fb_open;
    fb->close   = fb_close;
    fb->read    = RT_NULL;
    fb->write   = RT_NULL;
    fb->control = fb_control;
    fb->user_data = RT_NULL;
#endif

    rt_device_register(fb,"fb0",RT_DEVICE_FLAG_RDWR);

    fb_init_ok = RT_TRUE;

    return RT_EOK;
}

/* set up the 'lcd_device' and register it */
int rt_hw_lcd_init(void)
{
    struct lcd_device *lcd_drv = &_lcd_device;

    g_lcd = lcd_drv;
    /* the content of tcon control registers can be loaded from a xml file ? */
    // _panel = load_config_from_xml();
    memset(lcd_drv, 0, sizeof(struct lcd_device));

    lcd_drv->use_screen = DEFAULT_SCREEN;

    /* initialize device structure, the type of 'lcd' is 'rt_device' */
    lcd_drv->lcd.type = RT_Device_Class_Graphic;
    lcd_drv->lcd.init = rt_lcd_init;
    lcd_drv->lcd.open = RT_NULL;
    lcd_drv->lcd.close = RT_NULL;
    lcd_drv->lcd.control = rt_lcd_control;
    lcd_drv->lcd.user_data = (void *)&lcd_drv->lcd_info;

    /* register lcd device to RT-Thread */
    rt_device_register(&lcd_drv->lcd, "lcd", RT_DEVICE_FLAG_RDWR);

    rt_lcd_init((rt_device_t)lcd_drv);

    if (fb_init(&(lcd_drv->fb)) != RT_EOK)
    {
        rt_kprintf("fb device init failure\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}
// INIT_DEVICE_EXPORT(rt_hw_lcd_init);

static int lcd_draw_point(int args, char *argv[])
{
    struct lcd_device *lcd_drv = g_lcd;
    int x = 0;
    int y = 0;
    int i, k;

    rt_kprintf("lcd_draw_point\n");

    x = atoi(argv[1]);
    y = atoi(argv[2]);

    if (x >= lcd_drv->lcd_info.width)
        x = lcd_drv->lcd_info.width - 1;
    if (y >= lcd_drv->lcd_info.height)
        y = lcd_drv->lcd_info.height - 1;
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    rt_kprintf("Darw point is x:%d,y:%d\n", x, y);

    // memset(lcd->framebuffer, 0, sizeof(rt_uint32_t) * lcd_drv->lcd_info.width * lcd_drv->lcd_info.height);

    for (i = y - 100; i < y + 100; i++)
    {
        if (i < 0)
            continue;
        if (i >= lcd_drv->lcd_info.height)
            break;
        for (k = x - 100; k < x + 100; k++)
        {
            if (k < 0)
                continue;
            if (k >= lcd_drv->lcd_info.width)
                break;

            *((uint32_t *)lcd_drv->framebuffer + lcd_drv->lcd_info.width * i + k) = 0xff00ff00;
        }
    }

    *((uint32_t *)lcd_drv->framebuffer + lcd_drv->lcd_info.width * y + x) = 0xffff0000;
    // *((uint32_t *)lcd->framebuffer + lcd_drv->lcd_info.width * y + x + 2) = 0xff00ff00;

    rt_hw_cpu_dcache_clean(lcd_drv->framebuffer, LCD_DRV_FB_SZ);
    rt_lcd_control((rt_device_t)g_lcd, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);

    return 0;
}
MSH_CMD_EXPORT(lcd_draw_point, draw a point on lcd);

void lcd_pwm_test(int argc, char **argv)
{
    set_lcd_backlight(atoi(argv[1]));
}

MSH_CMD_EXPORT(lcd_pwm_test, set pwm);
#endif
