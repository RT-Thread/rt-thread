/* RT-Thread display driver for K230D */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/classes/graphic.h>
#include <stdlib.h>

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
#include "kd_vo_reg.h"
#include "kd_dsi_reg.h"
#include "sysctl_pwr.h"
#include "sysctl_rst.h"

extern struct panel_drv mipi_st7701_drv;
extern void dwc_dsi_debug_dump(void);
extern volatile sysctl_pwr_s *sysctl_pwr;
extern volatile sysctl_rst_t *sysctl_rst;

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
    rt_err_t                      last_error;
    const char*                   last_stage;
} g_display;

static struct panel_drv* display_drv_list[] = {
    &mipi_st7701_drv,
    RT_NULL,
};

static void display_flush_range(rt_uint8_t *addr, rt_size_t size);

static rt_bool_t display_power_domains_ready(void)
{
    if (!sysctl_pwr)
        return RT_FALSE;

    return ((sysctl_pwr->disp_lpi_state & 0x2U) != 0) &&
           ((sysctl_pwr->dpu_pwr_lpi_state & 0x2U) != 0);
}

static rt_bool_t display_wait_power_domains(void)
{
    for (int i = 0; i < 20; i++) {
        if (display_power_domains_ready())
            return RT_TRUE;
        rt_thread_mdelay(1);
    }

    return RT_FALSE;
}

static rt_err_t display_hw_enable(void)
{
    bool disp_ok;
    bool dpu_ok;

    disp_ok = sysctl_pwr_up(SYSCTL_PD_DISP);
    dpu_ok = sysctl_pwr_up(SYSCTL_PD_DPU);
    if (!display_wait_power_domains()) {
        rt_kprintf("display: power domain enable failed, ret disp=%d dpu=%d state disp=0x%08x dpu=0x%08x\n",
                   disp_ok, dpu_ok,
                   sysctl_pwr ? sysctl_pwr->disp_lpi_state : 0,
                   sysctl_pwr ? sysctl_pwr->dpu_pwr_lpi_state : 0);
        return -RT_ERROR;
    }
    if (!disp_ok || !dpu_ok)
        rt_kprintf("display: power domain enable warning, ret disp=%d dpu=%d state disp=0x%08x dpu=0x%08x\n",
                   disp_ok, dpu_ok, sysctl_pwr->disp_lpi_state,
                   sysctl_pwr->dpu_pwr_lpi_state);

    disp_ok = sysctl_pwr_set_lpi(SYSCTL_PD_DISP, true);
    dpu_ok = sysctl_pwr_set_lpi(SYSCTL_PD_DPU, true);
    if (!disp_ok || !dpu_ok)
        rt_kprintf("display: lpi exit warning, disp=%d dpu=%d\n", disp_ok, dpu_ok);

    (void)sysctl_set_reset_time(SYSCTL_RESET_TIME_DISP_SYS, 0xf, 0xf, 0xf);
    (void)sysctl_set_reset_time(SYSCTL_RESET_TIME_DPU, 0, 0xf, 0xf);

    disp_ok = sysctl_reset(SYSCTL_RESET_DISP);
    dpu_ok = sysctl_reset(SYSCTL_RESET_DPU);
    if (!disp_ok || !dpu_ok)
        rt_kprintf("display: reset warning, ret disp=%d dpu=%d ctl disp=0x%08x dpu=0x%08x\n",
                   disp_ok, dpu_ok,
                   sysctl_rst ? sysctl_rst->disp_rst_ctl : 0,
                   sysctl_rst ? sysctl_rst->dpu_rst_ctl : 0);
    rt_thread_mdelay(1);

    return RT_EOK;
}

static rt_err_t display_fail(const char *stage, rt_err_t error)
{
    g_display.last_stage = stage;
    g_display.last_error = error;
    return error;
}

static void display_fb_release(void)
{
    if (g_display.framebuffer)
        rt_free_align(g_display.framebuffer);

    g_display.framebuffer = RT_NULL;
    g_display.framebuffer_pa = RT_NULL;
    g_display.framebuffer_size = 0;
    rt_memset(&g_display.info, 0, sizeof(g_display.info));
}

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

static void display_commit_framebuffer(void)
{
    if (!g_display.framebuffer || !g_display.framebuffer_size)
        return;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, g_display.framebuffer,
                         g_display.framebuffer_size);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, g_display.framebuffer,
                         g_display.framebuffer_size);
    if (g_display.initialized)
        kd_vo_commit();
}

static void display_bind_default_osd(void)
{
    if (!g_display.initialized || !g_display.framebuffer_pa)
        return;

    kd_vo_set_osd_rgb565_framebuffer(2,
                                     (k_u64)(rt_ubase_t)g_display.framebuffer_pa,
                                     g_display.info.width,
                                     g_display.info.height,
                                     g_display.info.pitch);
    kd_vo_select_osd(2);
}

static rt_uint32_t display_fb_crc32(void)
{
    const rt_uint8_t *data = g_display.framebuffer;
    rt_uint32_t crc = 0xffffffffU;

    if (!data || !g_display.framebuffer_size)
        return 0;

    for (rt_size_t i = 0; i < g_display.framebuffer_size; i++) {
        crc ^= data[i];
        for (int bit = 0; bit < 8; bit++) {
            if (crc & 1U)
                crc = (crc >> 1) ^ 0xedb88320U;
            else
                crc >>= 1;
        }
    }

    return ~crc;
}

static rt_uint16_t display_fb_pixel(rt_uint16_t x, rt_uint16_t y)
{
    rt_uint16_t *line;

    if (!g_display.framebuffer || x >= g_display.info.width || y >= g_display.info.height)
        return 0;

    line = (rt_uint16_t *)(g_display.framebuffer + y * g_display.info.pitch);
    return line[x];
}

static void display_fb_probe_print(const char *tag)
{
    rt_uint16_t x0;
    rt_uint16_t x1;
    rt_uint16_t x2;
    rt_uint16_t y0;
    rt_uint16_t y1;
    rt_uint16_t y2;

    if (!g_display.framebuffer) {
        rt_kprintf("FB_PROBE %s not-ready\n", tag);
        return;
    }

    x0 = 0;
    y0 = 0;
    x1 = g_display.info.width / 2U;
    y1 = g_display.info.height / 2U;
    x2 = g_display.info.width ? (g_display.info.width - 1U) : 0;
    y2 = g_display.info.height ? (g_display.info.height - 1U) : 0;

    rt_kprintf("FB_PROBE %s va=%p pa=%p size=0x%lx pitch=%u align_pa=0x%lx crc=0x%08x\n",
               tag, g_display.framebuffer, g_display.framebuffer_pa,
               (unsigned long)g_display.framebuffer_size, g_display.info.pitch,
               ((unsigned long)(rt_ubase_t)g_display.framebuffer_pa) & 0xfffUL,
               display_fb_crc32());
    rt_kprintf("FB_PROBE %s p00=0x%04x p_mid=0x%04x p_last=0x%04x p120_80=0x%04x p240_80=0x%04x p360_80=0x%04x p120_240=0x%04x p360_480=0x%04x\n",
               tag,
               display_fb_pixel(x0, y0),
               display_fb_pixel(x1, y1),
               display_fb_pixel(x2, y2),
               display_fb_pixel(120, 80),
               display_fb_pixel(240, 80),
               display_fb_pixel(360, 80),
               display_fb_pixel(120, 240),
               display_fb_pixel(360, 480));
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
        display_bind_default_osd();
        display_commit_framebuffer();
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
        display_bind_default_osd();
        if (g_display.initialized)
            kd_vo_commit();
        return;
    }

    for (rt_uint16_t row = 0; row < height; row++) {
        display_flush_range(g_display.framebuffer + (y + row) * g_display.info.pitch +
                            x * bytes_per_pixel,
                            line_bytes);
    }
    display_bind_default_osd();
    if (g_display.initialized)
        kd_vo_commit();
}

static rt_err_t display_init(rt_device_t dev)
{
    rt_size_t fb_size;

    (void)dev;

    if (g_display.initialized)
        return RT_EOK;

    if (!g_display.panel) {
        rt_kprintf("display: no panel selected\n");
        return display_fail("select-panel", -RT_ERROR);
    }

    rt_kprintf("display: init start, panel=%s\n", g_display.panel->name);

    if (display_hw_enable() != RT_EOK)
        return display_fail("hw-enable", -RT_ERROR);

    if (vo_display_remap_init() != 0) {
        rt_kprintf("display: register remap failed\n");
        return display_fail("remap", -RT_ERROR);
    }

    fb_size = g_display.panel->timing.hactive * g_display.panel->timing.vactive * 2;
    g_display.framebuffer = rt_malloc_align(fb_size, K230_DISPLAY_FB_ALIGN);
    if (!g_display.framebuffer) {
        rt_kprintf("display: framebuffer allocation failed\n");
        return display_fail("fb-alloc", -RT_ENOMEM);
    }

    rt_memset(g_display.framebuffer, 0, fb_size);
    g_display.framebuffer_pa = rt_kmem_v2p(g_display.framebuffer);
    if (!g_display.framebuffer_pa || g_display.framebuffer_pa == ARCH_MAP_FAILED) {
        rt_kprintf("display: framebuffer physical address failed\n");
        display_fb_release();
        return display_fail("fb-phys", -RT_ERROR);
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
        display_fb_release();
        return display_fail("panel-power-on", -RT_ERROR);
    }

    g_display.initialized = RT_TRUE;
    g_display.brightness = 255;
    g_display.last_stage = "ready";
    g_display.last_error = RT_EOK;

    kd_vo_disable_osd_all();

    panel_generic_backlight(g_display.panel, 1, g_display.brightness);

    rt_kprintf("display: init done, fb va=%p pa=%p size=0x%lx\n",
               g_display.framebuffer, g_display.framebuffer_pa,
               (unsigned long)g_display.framebuffer_size);
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
    display_bind_default_osd();
    display_commit_framebuffer();
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
    display_bind_default_osd();
    if (g_display.initialized)
        kd_vo_commit();
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
    display_bind_default_osd();
    if (g_display.initialized)
        kd_vo_commit();
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
    display_bind_default_osd();
    if (g_display.initialized)
        kd_vo_commit();
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

static void display_dump(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    rt_kprintf("display initialized=%d panel=%s\n",
               g_display.initialized,
               g_display.panel ? g_display.panel->name : "<none>");
    rt_kprintf("display last_stage=%s last_error=%d\n",
               g_display.last_stage ? g_display.last_stage : "<none>",
               g_display.last_error);
    rt_kprintf("fb va=%p pa=%p size=0x%lx width=%u height=%u pitch=%u bpp=%u brightness=%u\n",
               g_display.framebuffer, g_display.framebuffer_pa,
               (unsigned long)g_display.framebuffer_size,
               g_display.info.width, g_display.info.height,
               g_display.info.pitch, g_display.info.bits_per_pixel,
               g_display.brightness);

    if (g_display.panel) {
        const k_vo_timing *t = &g_display.panel->timing;

        rt_kprintf("timing pclk=%u h=%u/%u/%u/%u v=%u/%u/%u/%u bg=0x%08x\n",
                   t->pclk_khz,
                   t->hactive, t->hsync_len, t->hback_porch, t->hfront_porch,
                   t->vactive, t->vsync_len, t->vback_porch, t->vfront_porch,
                   g_display.panel->bg_color);
    }

    if (sysctl_pwr) {
        rt_kprintf("PWR base=%p disp_ctl=0x%08x disp_state=0x%08x dpu_ctl=0x%08x dpu_state=0x%08x repair=0x%08x\n",
                   sysctl_pwr,
                   sysctl_pwr->disp_lpi_ctl, sysctl_pwr->disp_lpi_state,
                   sysctl_pwr->dpu_pwr_lpi_ctl, sysctl_pwr->dpu_pwr_lpi_state,
                   sysctl_pwr->repair_status);
    } else {
        rt_kprintf("PWR base=<null>\n");
    }

    if (sysctl_rst) {
        rt_kprintf("RMU base=%p dpu_rst_tim=0x%08x dpu_rst_ctl=0x%08x disp_rst_tim=0x%08x disp_rst_ctl=0x%08x\n",
                   sysctl_rst,
                   sysctl_rst->dpu_rst_tim, sysctl_rst->dpu_rst_ctl,
                   sysctl_rst->disp_sys_rst_tim, sysctl_rst->disp_rst_ctl);
    } else {
        rt_kprintf("RMU base=<null>\n");
    }

    kd_vo_debug_dump();
    dwc_dsi_debug_dump();
}
MSH_CMD_EXPORT(display_dump, dump K230 display registers);

static void display_bind_osd(int argc, char** argv)
{
    int osd;

    if (argc != 2) {
        rt_kprintf("usage: display_bind_osd <0-3>\n");
        return;
    }

    if (!g_display.framebuffer_pa) {
        rt_kprintf("display: framebuffer is not ready\n");
        return;
    }

    osd = atoi(argv[1]);
    if (osd < 0 || osd > 3) {
        rt_kprintf("display: invalid osd %d\n", osd);
        return;
    }

    kd_vo_set_osd_rgb565_framebuffer((k_u32)osd,
                                     (k_u64)(rt_ubase_t)g_display.framebuffer_pa,
                                     g_display.info.width, g_display.info.height,
                                     g_display.info.pitch);
    kd_vo_select_osd((k_u32)osd);
    display_commit_framebuffer();
    rt_kprintf("display: bound fb0 to OSD%d\n", osd);
}
MSH_CMD_EXPORT(display_bind_osd, bind fb0 to K230 VO OSD plane);

static void display_peek(int argc, char** argv)
{
    volatile rt_uint32_t *base = RT_NULL;
    unsigned long offset;
    unsigned long count = 1;

    if (argc < 3 || argc > 4) {
        rt_kprintf("usage: display_peek <vo|dsi|phy|pwr|rmu|cmu|stc> <offset> [count]\n");
        return;
    }

    if (vo_display_remap_init() != 0) {
        rt_kprintf("display: register remap failed\n");
        return;
    }

    if (rt_strcmp(argv[1], "vo") == 0) {
        base = (volatile rt_uint32_t *)display_remap->vo_base;
    } else if (rt_strcmp(argv[1], "dsi") == 0) {
        base = (volatile rt_uint32_t *)display_remap->dsi_base;
    } else if (rt_strcmp(argv[1], "phy") == 0) {
        base = (volatile rt_uint32_t *)display_remap->phy_base;
    } else if (rt_strcmp(argv[1], "pwr") == 0) {
        base = (volatile rt_uint32_t *)sysctl_pwr;
    } else if (rt_strcmp(argv[1], "rmu") == 0) {
        base = (volatile rt_uint32_t *)sysctl_rst;
    } else if (rt_strcmp(argv[1], "cmu") == 0) {
        base = (volatile rt_uint32_t *)display_remap->clock_base;
    } else if (rt_strcmp(argv[1], "stc") == 0) {
        base = (volatile rt_uint32_t *)display_remap->timestamp_base;
    } else {
        rt_kprintf("display: unknown region %s\n", argv[1]);
        return;
    }

    if (base == RT_NULL) {
        rt_kprintf("display: region %s is not mapped\n", argv[1]);
        return;
    }

    offset = strtoul(argv[2], RT_NULL, 0);
    if ((offset & 0x3UL) != 0) {
        rt_kprintf("display: offset must be 4-byte aligned\n");
        return;
    }

    if (argc == 4)
        count = strtoul(argv[3], RT_NULL, 0);
    if (count == 0)
        count = 1;
    if (count > 64)
        count = 64;

    for (unsigned long i = 0; i < count; i++) {
        volatile rt_uint32_t *reg = (volatile rt_uint32_t *)((rt_uint8_t *)base + offset + i * 4);

        rt_kprintf("%s[0x%04lx] = 0x%08x\n",
                   argv[1], offset + i * 4, *reg);
    }
}
MSH_CMD_EXPORT(display_peek, read K230 display/sysctl registers);

static void display_poke(int argc, char** argv)
{
    unsigned long offset;
    unsigned long value;

    if (argc != 3) {
        rt_kprintf("usage: display_poke <vo-offset> <value>\n");
        return;
    }

    offset = strtoul(argv[1], RT_NULL, 0);
    value = strtoul(argv[2], RT_NULL, 0);
    if ((offset & 0x3UL) != 0) {
        rt_kprintf("display: offset must be 4-byte aligned\n");
        return;
    }

    kd_vo_poke((k_u32)offset, (k_u32)value);
    rt_kprintf("vo[0x%04lx] <- 0x%08lx\n", offset, value);
}
MSH_CMD_EXPORT(display_poke, write a K230 VO register);

static void display_osd_tune(int argc, char** argv)
{
    int osd;
    unsigned long stride;
    unsigned long dma_ctrl;
    unsigned long addr_sel;

    if (argc != 5) {
        rt_kprintf("usage: display_osd_tune <osd> <stride-reg> <dma-ctrl> <addr-sel>\n");
        rt_kprintf("example: display_osd_tune 2 0x00000078 0x7f 0x100\n");
        return;
    }

    if (!g_display.framebuffer_pa) {
        rt_kprintf("display: framebuffer is not ready\n");
        return;
    }

    osd = atoi(argv[1]);
    if (osd < 0 || osd > 3) {
        rt_kprintf("display: invalid osd %d\n", osd);
        return;
    }

    stride = strtoul(argv[2], RT_NULL, 0);
    dma_ctrl = strtoul(argv[3], RT_NULL, 0);
    addr_sel = strtoul(argv[4], RT_NULL, 0);

    kd_vo_set_osd_rgb565_framebuffer_raw((k_u32)osd,
                                         (k_u64)(rt_ubase_t)g_display.framebuffer_pa,
                                         (k_u64)(rt_ubase_t)g_display.framebuffer_pa,
                                         g_display.info.width,
                                         g_display.info.height,
                                         (k_u32)stride,
                                         (k_u32)dma_ctrl,
                                         (k_u32)addr_sel);
    kd_vo_select_osd((k_u32)osd);
    display_commit_framebuffer();
    rt_kprintf("display: osd%d stride=0x%08lx dma=0x%08lx sel=0x%08lx addr=0x%08lx\n",
               osd, stride, dma_ctrl, addr_sel,
               (unsigned long)(rt_ubase_t)g_display.framebuffer_pa);
}
MSH_CMD_EXPORT(display_osd_tune, tune K230 VO OSD framebuffer registers);

static void display_phy(int argc, char** argv)
{
    unsigned long m;
    unsigned long n;
    unsigned long voc;
    unsigned long hs_freq;

    if (argc != 5) {
        rt_kprintf("usage: display_phy <m> <n> <voc> <hs_freq>\n");
        return;
    }

    if (vo_display_remap_init() != 0) {
        rt_kprintf("display: register remap failed\n");
        return;
    }

    m = strtoul(argv[1], RT_NULL, 0);
    n = strtoul(argv[2], RT_NULL, 0);
    voc = strtoul(argv[3], RT_NULL, 0);
    hs_freq = strtoul(argv[4], RT_NULL, 0);

    k230_dsi_phy_config(K_DSI_2LAN, (k_u32)m, (k_u32)n, (k_u8)voc, (k_u8)hs_freq);
    rt_thread_mdelay(1);
    rt_kprintf("display: phy set m=%lu n=%lu voc=0x%02lx hs_freq=0x%02lx\n",
               m, n, voc, hs_freq);
    dwc_dsi_debug_dump();
}
MSH_CMD_EXPORT(display_phy, configure K230 DSI PHY clock parameters);

static void display_hw_on(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    if (display_hw_enable() == RT_EOK)
        rt_kprintf("display: DISP/DPU power and reset sequence done\n");
}
MSH_CMD_EXPORT(display_hw_on, enable K230 display power domains and reset blocks);

static void display_init_now(int argc, char** argv)
{
    rt_err_t ret;

    (void)argc;
    (void)argv;

    ret = display_init(&g_display.lcd);
    rt_kprintf("display_init_now: ret=%d initialized=%d stage=%s\n",
               ret, g_display.initialized,
               g_display.last_stage ? g_display.last_stage : "<none>");
}
MSH_CMD_EXPORT(display_init_now, initialize K230 display immediately);

static void display_panel_on(int argc, char** argv)
{
    k_u8 vc;
    k_u8 sleep_out[] = { 0x11 };
    k_u8 pixel_format[] = { 0x3A, 0x50 };
    k_u8 display_on[] = { 0x29 };
    int ret_sleep;
    int ret_format;
    int ret_on;

    (void)argc;
    (void)argv;

    if (!g_display.panel) {
        rt_kprintf("display: no panel selected\n");
        return;
    }

    vc = g_display.panel->bus.dsi.vc_id;
    ret_sleep = dwc_dsi_dcs_write(sleep_out, sizeof(sleep_out), vc);
    rt_thread_mdelay(200);
    ret_format = dwc_dsi_dcs_write(pixel_format, sizeof(pixel_format), vc);
    ret_on = dwc_dsi_dcs_write(display_on, sizeof(display_on), vc);
    rt_thread_mdelay(50);

    rt_kprintf("display_panel_on: sleep=%d format=%d display=%d\n",
               ret_sleep, ret_format, ret_on);
    dwc_dsi_debug_dump();
}
MSH_CMD_EXPORT(display_panel_on, send ST7701 sleep-out pixel-format display-on);

static int display_panel_set_colmod(k_u8 value)
{
    k_u8 vc;
    k_u8 pixel_format[2];

    if (!g_display.panel)
        return -RT_ERROR;

    vc = g_display.panel->bus.dsi.vc_id;
    pixel_format[0] = 0x3A;
    pixel_format[1] = value;
    return dwc_dsi_dcs_write(pixel_format, sizeof(pixel_format), vc);
}

static void display_colmod(int argc, char** argv)
{
    unsigned long value;
    int ret;

    if (argc != 2) {
        rt_kprintf("usage: display_colmod <0x50|0x55|0x66>\n");
        return;
    }

    value = strtoul(argv[1], RT_NULL, 0);
    ret = display_panel_set_colmod((k_u8)value);
    rt_kprintf("display: panel COLMOD=0x%02lx ret=%d\n", value & 0xffUL, ret);
    dwc_dsi_debug_dump();
}
MSH_CMD_EXPORT(display_colmod, set panel DCS 0x3A pixel format);

static void display_panel_status_read(k_u8 cmd, const char *name)
{
    k_u8 vc = g_display.panel->bus.dsi.vc_id;
    k_u8 max_return[2] = { 1, 0 };
    k_u8 data[4] = { 0 };
    int ret;

    ret = dwc_dsi_send_packet(0x37, vc, max_return, sizeof(max_return), 0);
    if (ret != 0) {
        rt_kprintf("%s(0x%02x): set-max-return failed ret=%d\n",
                   name, cmd, ret);
        return;
    }

    ret = dwc_dsi_dcs_read(cmd, data, 1, vc);
    if (ret < 0) {
        rt_kprintf("%s(0x%02x): read failed ret=%d\n", name, cmd, ret);
        return;
    }

    rt_kprintf("%s(0x%02x): ret=%d data=0x%02x\n",
               name, cmd, ret, data[0]);
}

static void display_panel_status(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    if (!g_display.panel) {
        rt_kprintf("display: no panel selected\n");
        return;
    }

    display_panel_status_read(0x0A, "power-mode");
    display_panel_status_read(0x0B, "address-mode");
    display_panel_status_read(0x0C, "pixel-format");
    display_panel_status_read(0x0D, "display-mode");
    display_panel_status_read(0x0E, "signal-mode");
    dwc_dsi_debug_dump();
}
MSH_CMD_EXPORT(display_panel_status, read basic panel DCS status registers);

static void display_bg(int argc, char** argv)
{
    unsigned long color;

    if (argc != 2) {
        rt_kprintf("usage: display_bg <rgb888>\n");
        return;
    }

    color = strtoul(argv[1], RT_NULL, 0);
    kd_vo_set_background((k_u32)color);
    rt_kprintf("display: background rgb888=0x%06lx\n", color & 0xffffffUL);
}
MSH_CMD_EXPORT(display_bg, set VO background color from RGB888);

static void display_bg_yuv(int argc, char** argv)
{
    unsigned long color;

    if (argc != 2) {
        rt_kprintf("usage: display_bg_yuv <yuv>\n");
        return;
    }

    color = strtoul(argv[1], RT_NULL, 0);
    kd_vo_set_background_yuv((k_u32)color);
    rt_kprintf("display: background yuv=0x%06lx\n", color & 0xffffffUL);
}
MSH_CMD_EXPORT(display_bg_yuv, set VO background color from packed YUV);

static rt_uint16_t display_rgb565(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b)
{
    return (rt_uint16_t)(((r & 0xf8U) << 8) | ((g & 0xfcU) << 3) | (b >> 3));
}

static void display_fill(int argc, char** argv)
{
    unsigned long rgb;
    rt_uint8_t r;
    rt_uint8_t g;
    rt_uint8_t b;
    rt_uint16_t color;
    rt_uint16_t *fb;
    rt_size_t pixels;

    if (argc != 2) {
        rt_kprintf("usage: display_fill <rgb888>\n");
        return;
    }

    if (!g_display.framebuffer) {
        rt_kprintf("display: framebuffer is not ready\n");
        return;
    }

    rgb = strtoul(argv[1], RT_NULL, 0);
    r = (rt_uint8_t)((rgb >> 16) & 0xffU);
    g = (rt_uint8_t)((rgb >> 8) & 0xffU);
    b = (rt_uint8_t)(rgb & 0xffU);
    color = display_rgb565(r, g, b);
    fb = (rt_uint16_t *)g_display.framebuffer;
    pixels = (g_display.info.pitch / 2U) * g_display.info.height;

    rt_mutex_take(&g_display.lock, RT_WAITING_FOREVER);
    for (rt_size_t i = 0; i < pixels; i++)
        fb[i] = color;
    display_bind_default_osd();
    display_commit_framebuffer();
    rt_mutex_release(&g_display.lock);

    rt_kprintf("display: filled fb0 rgb888=0x%06lx rgb565=0x%04x\n",
               rgb & 0xffffffUL, color);
}
MSH_CMD_EXPORT(display_fill, fill fb0 with one RGB565 color);

static void display_draw_rect_rgb565(rt_int32_t x, rt_int32_t y,
                                     rt_int32_t w, rt_int32_t h,
                                     rt_uint16_t color)
{
    rt_int32_t x0;
    rt_int32_t y0;
    rt_int32_t x1;
    rt_int32_t y1;
    rt_uint16_t *line;

    if (!g_display.framebuffer || w <= 0 || h <= 0)
        return;

    x0 = x;
    y0 = y;
    x1 = x + w;
    y1 = y + h;

    if (x0 < 0)
        x0 = 0;
    if (y0 < 0)
        y0 = 0;
    if (x1 > (rt_int32_t)g_display.info.width)
        x1 = g_display.info.width;
    if (y1 > (rt_int32_t)g_display.info.height)
        y1 = g_display.info.height;
    if (x0 >= x1 || y0 >= y1)
        return;

    for (rt_int32_t row = y0; row < y1; row++) {
        line = (rt_uint16_t *)(g_display.framebuffer +
                               row * g_display.info.pitch +
                               x0 * sizeof(rt_uint16_t));
        for (rt_int32_t col = x0; col < x1; col++)
            *line++ = color;
    }
}

static void display_rect(int argc, char** argv)
{
    rt_int32_t x;
    rt_int32_t y;
    rt_int32_t w;
    rt_int32_t h;
    unsigned long rgb;
    rt_uint16_t color;

    if (argc != 6) {
        rt_kprintf("usage: display_rect <x> <y> <w> <h> <rgb888>\n");
        return;
    }

    if (!g_display.framebuffer) {
        rt_kprintf("display: framebuffer is not ready\n");
        return;
    }

    x = (rt_int32_t)strtol(argv[1], RT_NULL, 0);
    y = (rt_int32_t)strtol(argv[2], RT_NULL, 0);
    w = (rt_int32_t)strtol(argv[3], RT_NULL, 0);
    h = (rt_int32_t)strtol(argv[4], RT_NULL, 0);
    rgb = strtoul(argv[5], RT_NULL, 0);
    color = display_rgb565((rt_uint8_t)((rgb >> 16) & 0xffU),
                           (rt_uint8_t)((rgb >> 8) & 0xffU),
                           (rt_uint8_t)(rgb & 0xffU));

    rt_mutex_take(&g_display.lock, RT_WAITING_FOREVER);
    display_draw_rect_rgb565(x, y, w, h, color);
    display_bind_default_osd();
    display_commit_framebuffer();
    rt_mutex_release(&g_display.lock);

    rt_kprintf("display: rect x=%d y=%d w=%d h=%d rgb888=0x%06lx rgb565=0x%04x\n",
               x, y, w, h, rgb & 0xffffffUL, color);
}
MSH_CMD_EXPORT(display_rect, draw an RGB565 rectangle into fb0);

static void display_blocks(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    if (!g_display.framebuffer) {
        rt_kprintf("display: framebuffer is not ready\n");
        return;
    }

    rt_mutex_take(&g_display.lock, RT_WAITING_FOREVER);
    display_draw_rect_rgb565(0, 0, 120, 160, display_rgb565(255, 0, 0));
    display_draw_rect_rgb565(120, 0, 120, 160, display_rgb565(0, 255, 0));
    display_draw_rect_rgb565(240, 0, 120, 160, display_rgb565(0, 0, 255));
    display_draw_rect_rgb565(360, 0, 120, 160, display_rgb565(255, 255, 255));
    display_draw_rect_rgb565(0, 160, 240, 160, display_rgb565(255, 255, 0));
    display_draw_rect_rgb565(240, 160, 240, 160, display_rgb565(0, 255, 255));
    display_draw_rect_rgb565(0, 320, 240, 320, display_rgb565(255, 0, 255));
    display_draw_rect_rgb565(240, 320, 240, 320, display_rgb565(32, 32, 32));
    display_bind_default_osd();
    display_commit_framebuffer();
    rt_mutex_release(&g_display.lock);

    rt_kprintf("display: drew RGB565 block pattern\n");
}
MSH_CMD_EXPORT(display_blocks, draw fixed RGB565 rectangles into fb0);

static void display_fb_probe(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    display_commit_framebuffer();
    display_fb_probe_print("manual");
    kd_vo_debug_summary();
}
MSH_CMD_EXPORT(display_fb_probe, print framebuffer checksum and key pixels);

static void display_diag_write_blocks(void)
{
    display_draw_rect_rgb565(0, 0, 120, 160, display_rgb565(255, 0, 0));
    display_draw_rect_rgb565(120, 0, 120, 160, display_rgb565(0, 255, 0));
    display_draw_rect_rgb565(240, 0, 120, 160, display_rgb565(0, 0, 255));
    display_draw_rect_rgb565(360, 0, 120, 160, display_rgb565(255, 255, 255));
    display_draw_rect_rgb565(0, 160, 240, 160, display_rgb565(255, 255, 0));
    display_draw_rect_rgb565(240, 160, 240, 160, display_rgb565(0, 255, 255));
    display_draw_rect_rgb565(0, 320, 240, 320, display_rgb565(255, 0, 255));
    display_draw_rect_rgb565(240, 320, 240, 320, display_rgb565(32, 32, 32));
}

static void display_diag_fill_rgb565(rt_uint16_t color)
{
    rt_uint16_t *fb = (rt_uint16_t *)g_display.framebuffer;
    rt_size_t pixels = (g_display.info.pitch / 2U) * g_display.info.height;

    for (rt_size_t i = 0; i < pixels; i++)
        fb[i] = color;
}

static void display_diag_case_format(const char *name, int osd, k_u32 stride,
                                     k_u32 info, k_u32 dma_ctrl, k_u32 addr_sel,
                                     rt_bool_t blocks, rt_uint16_t fill);

static void display_diag_case(const char *name, int osd, k_u32 stride,
                              k_u32 dma_ctrl, k_u32 addr_sel, rt_bool_t blocks,
                              rt_uint16_t fill)
{
    display_diag_case_format(name, osd, stride, 0x00000002U, dma_ctrl, addr_sel,
                             blocks, fill);
}

static void display_diag_case_format(const char *name, int osd, k_u32 stride,
                                     k_u32 info, k_u32 dma_ctrl, k_u32 addr_sel,
                                     rt_bool_t blocks, rt_uint16_t fill)
{
    rt_kprintf("DIAG_CASE begin %s osd=%d stride=0x%08x info=0x%08x dma=0x%08x sel=0x%08x pattern=%s\n",
               name, osd, stride, info, dma_ctrl, addr_sel, blocks ? "blocks" : "fill");

    rt_mutex_take(&g_display.lock, RT_WAITING_FOREVER);
    if (blocks)
        display_diag_write_blocks();
    else
        display_diag_fill_rgb565(fill);
    display_commit_framebuffer();
    kd_vo_set_osd_rgb565_framebuffer_format_raw((k_u32)osd,
                                                (k_u64)(rt_ubase_t)g_display.framebuffer_pa,
                                                (k_u64)(rt_ubase_t)g_display.framebuffer_pa,
                                                g_display.info.width,
                                                g_display.info.height,
                                                stride,
                                                info,
                                                dma_ctrl,
                                                addr_sel);
    kd_vo_select_osd((k_u32)osd);
    rt_mutex_release(&g_display.lock);

    kd_vo_debug_summary();
    display_fb_probe_print(name);
    rt_kprintf("DIAG_CASE end %s observe-screen-now\n", name);
    rt_thread_mdelay(800);
}

static void display_diag_bg_case(const char *name, k_u32 yuv)
{
    rt_kprintf("DIAG_CASE begin %s bg_yuv=0x%06x\n", name, yuv & 0xffffffU);
    kd_vo_disable_osd_all();
    kd_vo_set_background_yuv(yuv);
    kd_vo_debug_summary();
    display_fb_probe_print(name);
    rt_kprintf("DIAG_CASE end %s observe-screen-now\n", name);
    rt_thread_mdelay(500);
}

static void display_bg_only(int argc, char** argv)
{
    unsigned long yuv = 0x4c551dUL;

    if (argc > 2) {
        rt_kprintf("usage: display_bg_only [yuv]\n");
        return;
    }
    if (!g_display.initialized) {
        rt_kprintf("display_bg_only: display is not initialized, run display_init_now first\n");
        return;
    }
    if (argc == 2)
        yuv = strtoul(argv[1], RT_NULL, 0);

    kd_vo_disable_osd_all();
    kd_vo_set_background_yuv((k_u32)yuv);
    rt_kprintf("display: background only yuv=0x%06lx\n", yuv & 0xffffffUL);
    kd_vo_debug_summary();
    dwc_dsi_debug_dump();
}
MSH_CMD_EXPORT(display_bg_only, disable OSD planes and show VO background color);

static void display_diag(int argc, char** argv)
{
    k_u32 stride_sdk;
    k_u32 stride_packed16;
    k_u32 stride_legacy_low;

    (void)argc;
    (void)argv;

    if (!g_display.initialized) {
        rt_kprintf("display_diag: display is not initialized, run display_init_now first\n");
        return;
    }
    if (!g_display.framebuffer || !g_display.framebuffer_pa) {
        rt_kprintf("display_diag: framebuffer is not ready\n");
        return;
    }

    stride_sdk = g_display.info.pitch / 8U;
    stride_packed16 = (g_display.info.pitch / 32U) | ((g_display.info.pitch / 32U) << 16);
    stride_legacy_low = g_display.info.pitch / 32U;

    rt_kprintf("DIAG_START fb_va=%p fb_pa=%p size=0x%lx w=%u h=%u pitch=%u stride_sdk64=0x%08x stride_packed16=0x%08x stride_legacy_low=0x%08x\n",
               g_display.framebuffer, g_display.framebuffer_pa,
               (unsigned long)g_display.framebuffer_size,
               g_display.info.width, g_display.info.height, g_display.info.pitch,
               stride_sdk, stride_packed16, stride_legacy_low);

    display_commit_framebuffer();
    display_fb_probe_print("start");
    kd_vo_debug_summary();
    dwc_dsi_debug_dump();

    display_diag_bg_case("bg-red-yuv", 0x4c551d);
    display_diag_bg_case("bg-green-yuv", 0x952b15);
    display_diag_bg_case("bg-blue-yuv", 0x1d6bff);

    display_diag_case_format("osd2-blocks-sdk-rgb565", 2, stride_sdk, 0x00000002U, 0x0000007fU, 0x00000100U, RT_TRUE, 0);
    display_diag_case_format("osd2-fill-red-sdk-rgb565", 2, stride_sdk, 0x00000002U, 0x0000007fU, 0x00000100U, RT_FALSE, display_rgb565(255, 0, 0));
    display_diag_case_format("osd0-blocks-sdk-rgb565", 0, stride_sdk, 0x00000002U, 0x0000007fU, 0x00000100U, RT_TRUE, 0);
    display_diag_case_format("osd1-blocks-sdk-rgb565", 1, stride_sdk, 0x00000002U, 0x0000007fU, 0x00000100U, RT_TRUE, 0);
    display_diag_case_format("osd3-blocks-sdk-rgb565", 3, stride_sdk, 0x00000002U, 0x0000007fU, 0x00000100U, RT_TRUE, 0);

    display_diag_case_format("osd2-blocks-prev-dma0f", 2, stride_sdk, 0x00000002U, 0x0000000fU, 0x00000100U, RT_TRUE, 0);
    display_diag_case_format("osd2-blocks-prev-dma4f", 2, stride_sdk, 0x00000002U, 0x0000004fU, 0x00000100U, RT_TRUE, 0);
    display_diag_case_format("osd2-blocks-info2-dma3f", 2, stride_sdk, 0x00000002U, 0x0000003fU, 0x00000100U, RT_TRUE, 0);
    display_diag_case_format("osd2-blocks-info2-dma5f", 2, stride_sdk, 0x00000002U, 0x0000005fU, 0x00000100U, RT_TRUE, 0);
    display_diag_case("osd2-blocks-packed16", 2, stride_packed16, 0x0000007fU, 0x00000100U, RT_TRUE, 0);
    display_diag_case("osd2-blocks-legacy-low", 2, stride_legacy_low, 0x0000007fU, 0x00000100U, RT_TRUE, 0);
    display_diag_case("osd2-blocks-sel0", 2, stride_sdk, 0x0000007fU, 0x00000000U, RT_TRUE, 0);

    rt_kprintf("DIAG_DONE\n");
}
MSH_CMD_EXPORT(display_diag, run concentrated display scanout diagnostics);

static void display_dsi_video(int argc, char** argv)
{
    unsigned long dpi_color;
    unsigned long pkt;
    unsigned long hsa;
    unsigned long hbp;
    unsigned long hline;
    unsigned long mode;

    if (argc != 7) {
        rt_kprintf("usage: display_dsi_video <dpi_color> <pkt> <hsa> <hbp> <hline> <mode>\n");
        return;
    }

    dpi_color = strtoul(argv[1], RT_NULL, 0);
    pkt = strtoul(argv[2], RT_NULL, 0);
    hsa = strtoul(argv[3], RT_NULL, 0);
    hbp = strtoul(argv[4], RT_NULL, 0);
    hline = strtoul(argv[5], RT_NULL, 0);
    mode = strtoul(argv[6], RT_NULL, 0);

    dwc_dsi_set_video_scan((k_u32)dpi_color, (k_u32)pkt,
                           (k_u32)hsa, (k_u32)hbp,
                           (k_u32)hline, (k_u32)mode);
    rt_kprintf("display: dsi video dpi=0x%lx pkt=%lu hsa=%lu hbp=%lu hline=%lu mode=%lu\n",
               dpi_color & 0x7UL, pkt, hsa, hbp, hline, mode);
    dwc_dsi_debug_dump();
}
MSH_CMD_EXPORT(display_dsi_video, set DSI DPI video scan registers);

static void display_dsi_diag_case(const char *name, k_u8 colmod,
                                  k_u32 dpi_color, k_u32 pkt,
                                  k_u32 hsa, k_u32 hbp,
                                  k_u32 hline, k_u32 mode)
{
    int ret;
    k_u32 stride_sdk;

    stride_sdk = g_display.info.pitch / 8U;

    rt_kprintf("DSI_DIAG_CASE begin %s colmod=0x%02x dpi=0x%08x pkt=%u hsa=%u hbp=%u hline=%u mode=%u\n",
               name, colmod, dpi_color, pkt, hsa, hbp, hline, mode);

    ret = display_panel_set_colmod(colmod);
    rt_kprintf("DSI_DIAG_CASE %s colmod_ret=%d\n", name, ret);
    dwc_dsi_set_video_scan(dpi_color, pkt, hsa, hbp, hline, mode);

    rt_mutex_take(&g_display.lock, RT_WAITING_FOREVER);
    display_diag_write_blocks();
    display_commit_framebuffer();
    kd_vo_set_osd_rgb565_framebuffer_raw(2,
                                         (k_u64)(rt_ubase_t)g_display.framebuffer_pa,
                                         (k_u64)(rt_ubase_t)g_display.framebuffer_pa,
                                         g_display.info.width,
                                         g_display.info.height,
                                         stride_sdk,
                                         0x0000007fU,
                                         0x00000100U);
    kd_vo_select_osd(2);
    rt_mutex_release(&g_display.lock);

    kd_vo_debug_summary();
    dwc_dsi_debug_dump();
    display_fb_probe_print(name);
    rt_kprintf("DSI_DIAG_CASE end %s observe-screen-now\n", name);
    rt_thread_mdelay(1000);
}

static void display_dsi_diag(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    if (!g_display.initialized) {
        rt_kprintf("display_dsi_diag: display is not initialized, run display_init_now first\n");
        return;
    }
    if (!g_display.framebuffer || !g_display.framebuffer_pa) {
        rt_kprintf("display_dsi_diag: framebuffer is not ready\n");
        return;
    }

    rt_kprintf("DSI_DIAG_START w=%u h=%u pitch=%u fb_pa=%p\n",
               g_display.info.width, g_display.info.height,
               g_display.info.pitch, g_display.framebuffer_pa);
    kd_vo_debug_summary();
    dwc_dsi_debug_dump();

    display_dsi_diag_case("col70-dpi5-p480-h840-burst", 0x70, 5, 480, 30, 30, 840, K_BURST_MODE);
    display_dsi_diag_case("col70-dpi5-p480-h840-sync-event", 0x70, 5, 480, 30, 30, 840, K_NON_BURST_MODE_WITH_SYNC_EVENT);
    display_dsi_diag_case("col70-dpi5-p480-h840-pulses", 0x70, 5, 480, 30, 30, 840, K_NON_BURST_MODE_WITH_PULSES);
    display_dsi_diag_case("col50-dpi0-p480-h560-burst", 0x50, 0, 480, 20, 20, 560, K_BURST_MODE);
    display_dsi_diag_case("col50-dpi1-p480-h560-burst", 0x50, 1, 480, 20, 20, 560, K_BURST_MODE);
    display_dsi_diag_case("col50-dpi2-p480-h560-burst", 0x50, 2, 480, 20, 20, 560, K_BURST_MODE);
    display_dsi_diag_case("col55-dpi5-p480-h840-burst", 0x55, 5, 480, 30, 30, 840, K_BURST_MODE);
    display_dsi_diag_case("col55-dpi5-p480-h560-burst", 0x55, 5, 480, 20, 20, 560, K_BURST_MODE);
    display_dsi_diag_case("col66-dpi5-p480-h840-burst", 0x66, 5, 480, 30, 30, 840, K_BURST_MODE);

    (void)display_panel_set_colmod(0x50);
    dwc_dsi_set_video_scan(1, 480, 20, 20, 560, K_BURST_MODE);
    rt_kprintf("DSI_DIAG_DONE restored colmod=0x50 dpi=1 pkt=480 hline=560 burst\n");
    dwc_dsi_debug_dump();
}
MSH_CMD_EXPORT(display_dsi_diag, scan DSI video color and timing combinations);

static void display_dpi_color(int argc, char** argv)
{
    unsigned long coding;

    if (argc != 2) {
        rt_kprintf("usage: display_dpi_color <0|1|2|5>\n");
        return;
    }

    coding = strtoul(argv[1], RT_NULL, 0);
    dwc_dsi_set_dpi_color_coding((k_u32)coding);
    rt_kprintf("display: DSI DPI color coding=0x%lx\n", coding & 0x7UL);
    dwc_dsi_debug_dump();
}
MSH_CMD_EXPORT(display_dpi_color, set DSI DPI color coding register);

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
    g_display.last_stage = "registered";
    g_display.last_error = RT_EOK;

    rt_kprintf("display: lcd/fb0 device registered\n");
    return 0;
}
INIT_DEVICE_EXPORT(k230_display_init);
