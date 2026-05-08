#include <lvgl.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG    "lv_port_disp"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

static lv_disp_draw_buf_t disp_buf;
static lv_disp_drv_t disp_drv;
static rt_device_t gpu_device = 0;
static struct rt_device_graphic_info info;

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    lv_color32_t *fbp32 = (lv_color32_t *)info.framebuffer;
    int32_t x, y;

    for (y = area->y1; y <= area->y2; y++)
    {
        for (x = area->x1; x <= area->x2; x++)
        {
            fbp32[y * info.width + x].full = color_p->full;
            color_p++;
        }
    }

    lv_disp_flush_ready(disp_drv);
}

void lv_port_disp_init(void)
{
    rt_err_t result;

    gpu_device = rt_device_find("virtio-gpu0");
    if (gpu_device == RT_NULL)
    {
        LOG_E("virtio-gpu0 device not found");
        return;
    }

    result = rt_device_open(gpu_device, RT_DEVICE_OFLAG_RDWR);
    if (result != RT_EOK)
    {
        LOG_E("failed to open virtio-gpu0: %d", result);
        return;
    }

    result = rt_device_control(gpu_device, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK)
    {
        LOG_E("failed to get graphic info: %d", result);
        return;
    }

    LOG_I("framebuffer: %p, %dx%d, bpp=%d, format=%d",
          info.framebuffer, info.width, info.height,
          info.bits_per_pixel, info.pixel_format);

    lv_color_t *fbuf1 = rt_malloc(info.width * info.height * sizeof(lv_color_t));
    lv_color_t *fbuf2 = rt_malloc(info.width * info.height * sizeof(lv_color_t));
    if (fbuf1 == RT_NULL || fbuf2 == RT_NULL)
    {
        LOG_E("failed to allocate LVGL draw buffers");
        if (fbuf1) rt_free(fbuf1);
        if (fbuf2) rt_free(fbuf2);
        return;
    }

    lv_disp_draw_buf_init(&disp_buf, fbuf1, fbuf2, info.width * info.height);

    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = info.width;
    disp_drv.ver_res = info.height;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = disp_flush;

    lv_disp_drv_register(&disp_drv);

    LOG_I("LVGL display port initialized");
}
