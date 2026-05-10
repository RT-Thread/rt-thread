/* RT-Thread display driver for K230D */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/classes/graphic.h>

#ifdef RT_USING_SMART
#include <lwp_user_mm.h>
#include <mmu.h>
#ifdef RT_USING_DFS
#include <dfs_file.h>
#endif
#endif

#include "connector_panel.h"
#include "drv_display.h"
#include "vo_display_remap.h"

extern void kd_vo_set_background(k_u32 rgb888);

extern struct panel_drv mipi_st7701_drv;

static struct {
    struct rt_device              lcd;
    struct rt_device              fb;
    struct rt_device_graphic_info info;
    struct panel_desc*            panel;
    struct rt_mutex               lock;
    rt_uint8_t*                   framebuffer;
    void*                         framebuffer_pa;
    rt_size_t                     framebuffer_size;
    rt_uint8_t                    brightness;
    rt_bool_t                     initialized;
} g_display;

static struct panel_drv* display_drv_list[] = {
    &mipi_st7701_drv,
    RT_NULL,
};

static const struct panel_desc* find_panel_by_name(const char* name)
{
    for (int i = 0; display_drv_list[i] != RT_NULL; i++) {
        struct panel_drv* drv = display_drv_list[i];

        if (drv->panel_variants) {
            for (int j = 0; drv->panel_variants[j] != RT_NULL; j++) {
                if (rt_strcmp(drv->panel_variants[j]->name, name) == 0)
                    return drv->panel_variants[j];
            }
        }
        if (drv->active_panel && rt_strcmp(drv->active_panel->name, name) == 0)
            return drv->active_panel;
    }
    return RT_NULL;
}

static void display_flush_range(rt_uint8_t *addr, rt_size_t size)
{
    if (addr && size)
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, addr, size);
}

static void display_flush_rect(const struct rt_device_rect_info *rect)
{
    rt_uint16_t x;
    rt_uint16_t y;
    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint8_t bytes_per_pixel = g_display.info.bits_per_pixel / 8;
    rt_size_t line_bytes;

    if (!g_display.framebuffer)
        return;

    if (!rect) {
        display_flush_range(g_display.framebuffer, g_display.framebuffer_size);
        return;
    }

    if (rect->x >= g_display.info.width || rect->y >= g_display.info.height)
        return;

    x = rect->x;
    y = rect->y;
    width = rect->width;
    height = rect->height;

    if (x + width > g_display.info.width)
        width = g_display.info.width - x;
    if (y + height > g_display.info.height)
        height = g_display.info.height - y;
    if (width == 0 || height == 0)
        return;

    line_bytes = width * bytes_per_pixel;
    if (x == 0 && width == g_display.info.width) {
        display_flush_range(g_display.framebuffer + y * g_display.info.pitch,
                            height * g_display.info.pitch);
        return;
    }

    for (rt_uint16_t row = 0; row < height; row++) {
        display_flush_range(g_display.framebuffer + (y + row) * g_display.info.pitch +
                            x * bytes_per_pixel,
                            line_bytes);
    }
}

static rt_err_t display_init(rt_device_t dev)
{
    rt_size_t fb_size;

    (void)dev;

    if (g_display.initialized)
        return RT_EOK;

    if (!g_display.panel) {
        rt_kprintf("display: no panel selected\n");
        return -RT_ERROR;
    }

    if (vo_display_remap_init() != 0) {
        rt_kprintf("display: register remap failed\n");
        return -RT_ERROR;
    }

    fb_size = g_display.panel->timing.hactive * g_display.panel->timing.vactive * 2;
    g_display.framebuffer = rt_malloc_align(fb_size, K230_DISPLAY_FB_ALIGN);
    if (!g_display.framebuffer) {
        rt_kprintf("display: framebuffer allocation failed\n");
        return -RT_ENOMEM;
    }

    rt_memset(g_display.framebuffer, 0, fb_size);
    g_display.framebuffer_pa = rt_kmem_v2p(g_display.framebuffer);
    if (!g_display.framebuffer_pa || g_display.framebuffer_pa == ARCH_MAP_FAILED) {
        rt_kprintf("display: framebuffer physical address failed\n");
        rt_free_align(g_display.framebuffer);
        g_display.framebuffer = RT_NULL;
        return -RT_ERROR;
    }

    g_display.framebuffer_size = fb_size;
    g_display.info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    g_display.info.bits_per_pixel = 16;
    g_display.info.pitch          = g_display.panel->timing.hactive * 2;
    g_display.info.width          = g_display.panel->timing.hactive;
    g_display.info.height         = g_display.panel->timing.vactive;
    g_display.info.framebuffer    = g_display.framebuffer;
    g_display.info.smem_len       = fb_size;
    display_flush_range(g_display.framebuffer, fb_size);

    if (panel_generic_power_on(g_display.panel) != 0) {
        rt_kprintf("display: power_on failed\n");
        rt_free_align(g_display.framebuffer);
        g_display.framebuffer = RT_NULL;
        g_display.framebuffer_pa = RT_NULL;
        g_display.framebuffer_size = 0;
        rt_memset(&g_display.info, 0, sizeof(g_display.info));
        return -RT_ERROR;
    }

    g_display.initialized = RT_TRUE;
    g_display.brightness = 255;

    panel_generic_backlight(g_display.panel, 1, g_display.brightness);

    return RT_EOK;
}

static rt_err_t display_open(rt_device_t dev, rt_uint16_t oflag)
{
    (void)oflag;
    return display_init(dev);
}

static rt_err_t display_close(rt_device_t dev)
{
    (void)dev;
    return RT_EOK;
}

static rt_ssize_t display_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_size_t count;

    (void)dev;

    if (!buffer || !g_display.framebuffer || pos < 0)
        return 0;
    if ((rt_size_t)pos >= g_display.framebuffer_size)
        return 0;

    count = g_display.framebuffer_size - (rt_size_t)pos;
    if (count > size)
        count = size;

    rt_mutex_take(&g_display.lock, RT_WAITING_FOREVER);
    rt_memcpy(buffer, g_display.framebuffer + pos, count);
    rt_mutex_release(&g_display.lock);

    return count;
}

static rt_ssize_t display_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_size_t count;

    (void)dev;

    if (!buffer || !g_display.framebuffer || pos < 0)
        return 0;
    if ((rt_size_t)pos >= g_display.framebuffer_size)
        return 0;

    count = g_display.framebuffer_size - (rt_size_t)pos;
    if (count > size)
        count = size;

    rt_mutex_take(&g_display.lock, RT_WAITING_FOREVER);
    rt_memcpy(g_display.framebuffer + pos, buffer, count);
    display_flush_range(g_display.framebuffer + pos, count);
    rt_mutex_release(&g_display.lock);

    return count;
}

static rt_err_t display_control(rt_device_t dev, int cmd, void* args)
{
    (void)dev;

    switch (cmd) {
    case RTGRAPHIC_CTRL_GET_INFO:
        if (!args)
            return -RT_EINVAL;
        rt_memcpy(args, &g_display.info, sizeof(g_display.info));
        break;
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        display_flush_rect((const struct rt_device_rect_info *)args);
        break;
    case RTGRAPHIC_CTRL_POWERON:
    case LCD_CTRL_BACKLIGHT_ON:
        panel_generic_backlight(g_display.panel, 1, g_display.brightness);
        break;
    case RTGRAPHIC_CTRL_POWEROFF:
    case LCD_CTRL_BACKLIGHT_OFF:
        panel_generic_backlight(g_display.panel, 0, 0);
        break;
    case RTGRAPHIC_CTRL_SET_BRIGHTNESS:
        g_display.brightness = args ? *(rt_uint8_t *)args : 0;
        panel_generic_backlight(g_display.panel, g_display.brightness ? 1 : 0,
                                g_display.brightness);
        break;
    case RTGRAPHIC_CTRL_GET_BRIGHTNESS:
        if (!args)
            return -RT_EINVAL;
        *(rt_uint8_t *)args = g_display.brightness;
        break;
    case RTGRAPHIC_CTRL_WAIT_VSYNC:
        rt_thread_mdelay(1000 / 60);
        break;
    case LCD_CTRL_SET_BG_COLOR:
        if (args)
            kd_vo_set_background(*(k_u32*)args);
        break;
#ifdef RT_FIOMMAP2
    case RT_FIOMMAP2:
    {
        struct dfs_mmap2_args *mmap2 = (struct dfs_mmap2_args *)args;

        if (!mmap2 || !g_display.framebuffer_pa)
            return -RT_EINVAL;
        if (mmap2->length > g_display.framebuffer_size)
            return -RT_ENOMEM;

        mmap2->ret = lwp_map_user_phy(lwp_self(), RT_NULL, g_display.framebuffer_pa,
                                      mmap2->length, 1);
        break;
    }
#endif
    default:
        return -RT_ERROR;
    }
    return RT_EOK;
}

static void display_set_pixel(const char *pixel, int x, int y)
{
    rt_uint8_t *dst;
    rt_uint8_t bytes_per_pixel = g_display.info.bits_per_pixel / 8;

    if (!pixel || !g_display.framebuffer || x < 0 || y < 0 ||
        x >= g_display.info.width || y >= g_display.info.height)
        return;

    dst = g_display.framebuffer + y * g_display.info.pitch + x * bytes_per_pixel;
    rt_memcpy(dst, pixel, bytes_per_pixel);
    display_flush_range(dst, bytes_per_pixel);
}

static void display_get_pixel(char *pixel, int x, int y)
{
    rt_uint8_t *src;
    rt_uint8_t bytes_per_pixel = g_display.info.bits_per_pixel / 8;

    if (!pixel || !g_display.framebuffer || x < 0 || y < 0 ||
        x >= g_display.info.width || y >= g_display.info.height)
        return;

    src = g_display.framebuffer + y * g_display.info.pitch + x * bytes_per_pixel;
    rt_memcpy(pixel, src, bytes_per_pixel);
}

static void display_draw_hline(const char *pixel, int x1, int x2, int y)
{
    rt_uint8_t bytes_per_pixel = g_display.info.bits_per_pixel / 8;
    rt_uint8_t *dst;

    if (!pixel || !g_display.framebuffer || y < 0 || y >= g_display.info.height)
        return;

    if (x1 > x2) {
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
    }

    if (x2 < 0 || x1 >= g_display.info.width)
        return;
    if (x1 < 0)
        x1 = 0;
    if (x2 >= g_display.info.width)
        x2 = g_display.info.width - 1;

    dst = g_display.framebuffer + y * g_display.info.pitch + x1 * bytes_per_pixel;
    for (int x = x1; x <= x2; x++) {
        rt_memcpy(dst, pixel, bytes_per_pixel);
        dst += bytes_per_pixel;
    }
    display_flush_range(g_display.framebuffer + y * g_display.info.pitch + x1 * bytes_per_pixel,
                        (x2 - x1 + 1) * bytes_per_pixel);
}

static void display_draw_vline(const char *pixel, int x, int y1, int y2)
{
    if (!pixel || !g_display.framebuffer || x < 0 || x >= g_display.info.width)
        return;

    if (y1 > y2) {
        int tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    if (y2 < 0 || y1 >= g_display.info.height)
        return;
    if (y1 < 0)
        y1 = 0;
    if (y2 >= g_display.info.height)
        y2 = g_display.info.height - 1;

    for (int y = y1; y <= y2; y++)
        display_set_pixel(pixel, x, y);
}

static void display_blit_line(const char *pixel, int x, int y, rt_size_t size)
{
    rt_uint8_t bytes_per_pixel = g_display.info.bits_per_pixel / 8;
    rt_uint8_t *dst;
    rt_size_t max_size;

    if (!pixel || !g_display.framebuffer || x < 0 || y < 0 ||
        x >= g_display.info.width || y >= g_display.info.height)
        return;

    max_size = (g_display.info.width - x) * bytes_per_pixel;
    if (size > max_size)
        size = max_size;

    dst = g_display.framebuffer + y * g_display.info.pitch + x * bytes_per_pixel;
    rt_memcpy(dst, pixel, size);
    display_flush_range(dst, size);
}

static struct rt_device_graphic_ops display_graphic_ops = {
    .set_pixel  = display_set_pixel,
    .get_pixel  = display_get_pixel,
    .draw_hline = display_draw_hline,
    .draw_vline = display_draw_vline,
    .blit_line  = display_blit_line,
};

static void list_display(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    rt_kprintf("Display Panels:\n");
    rt_kprintf("%-24s  %-12s  %-7s\n", "NAME", "RESOLUTION", "FPS");
    rt_kprintf("%-24s  %-12s  %-7s\n", "------------------------", "------------", "-------");

    int shown = 0;
    for (int i = 0; display_drv_list[i] != RT_NULL; i++) {
        struct panel_drv* drv = display_drv_list[i];

        if (drv->panel_variants) {
            for (int j = 0; drv->panel_variants[j] != RT_NULL; j++) {
                const struct panel_desc* panel = drv->panel_variants[j];
                int fps = panel_calculate_fps(&panel->timing);
                rt_kprintf("%-24s  %4ux%-4u      %3d fps\n",
                           panel->name, panel->timing.hactive,
                           panel->timing.vactive, fps);
                shown++;
            }
        } else if (drv->active_panel) {
            const struct panel_desc* panel = drv->active_panel;
            int fps = panel_calculate_fps(&panel->timing);
            rt_kprintf("%-24s  %4ux%-4u      %3d fps\n",
                       panel->name, panel->timing.hactive, panel->timing.vactive, fps);
            shown++;
        }
    }

    if (shown == 0)
        rt_kprintf("No panels registered.\n");
}

MSH_CMD_EXPORT(list_display, list display panels);

static const struct rt_device_ops display_ops = {
    .init    = display_init,
    .open    = display_open,
    .close   = display_close,
    .read    = display_read,
    .write   = display_write,
    .control = display_control,
};

int k230_display_init(void)
{
    rt_memset(&g_display, 0, sizeof(g_display));

    g_display.panel = (struct panel_desc*)find_panel_by_name("st7701_480x640_atk");
    if (!g_display.panel) {
        rt_kprintf("display: st7701_480x640_atk panel not found\n");
        return -1;
    }

    rt_mutex_init(&g_display.lock, "display", RT_IPC_FLAG_PRIO);

    g_display.lcd.type      = RT_Device_Class_Graphic;
    g_display.lcd.ops       = &display_ops;
    g_display.lcd.user_data = &display_graphic_ops;

    g_display.fb.type      = RT_Device_Class_Graphic;
    g_display.fb.ops       = &display_ops;
    g_display.fb.user_data = &display_graphic_ops;

    rt_device_register(&g_display.lcd, "lcd", RT_DEVICE_FLAG_RDWR);
    rt_device_register(&g_display.fb, "fb0", RT_DEVICE_FLAG_RDWR);

    if (display_init(&g_display.lcd) != RT_EOK) {
        rt_kprintf("display: auto-init failed\n");
        return -1;
    }

    rt_kprintf("display: lcd/fb0 device ready, %ux%u RGB565\n",
               g_display.info.width, g_display.info.height);
    return 0;
}
INIT_DEVICE_EXPORT(k230_display_init);
