/* Display demo: draw an RGB565 test pattern through the fb0 device. */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/classes/graphic.h>

static rt_uint16_t rgb565(rt_uint8_t r, rt_uint8_t g, rt_uint8_t b)
{
    return (rt_uint16_t)(((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3));
}

static void display_demo(int argc, char** argv)
{
    rt_device_t fb;
    struct rt_device_graphic_info info;
    rt_uint16_t *line;
    rt_uint16_t colors[] = {
        rgb565(255, 0, 0),
        rgb565(0, 255, 0),
        rgb565(0, 0, 255),
        rgb565(255, 255, 255),
        rgb565(0, 0, 0),
    };
    rt_size_t color_count = sizeof(colors) / sizeof(colors[0]);

    (void)argc;
    (void)argv;

    fb = rt_device_find("fb0");
    if (!fb) {
        rt_kprintf("display_demo: fb0 device not found\n");
        return;
    }

    if (rt_device_open(fb, RT_DEVICE_FLAG_RDWR) != RT_EOK) {
        rt_kprintf("display_demo: open fb0 failed\n");
        return;
    }

    rt_memset(&info, 0, sizeof(info));
    if (rt_device_control(fb, RTGRAPHIC_CTRL_GET_INFO, &info) != RT_EOK ||
        info.pixel_format != RTGRAPHIC_PIXEL_FORMAT_RGB565) {
        rt_kprintf("display_demo: unsupported framebuffer\n");
        rt_device_close(fb);
        return;
    }

    line = rt_malloc(info.pitch);
    if (!line) {
        rt_kprintf("display_demo: no memory\n");
        rt_device_close(fb);
        return;
    }

    for (rt_uint16_t y = 0; y < info.height; y++) {
        for (rt_uint16_t x = 0; x < info.width; x++) {
            rt_uint16_t band = (x * color_count) / info.width;
            rt_uint16_t shade = (y * 31) / info.height;

            line[x] = colors[band];
            if (band == color_count - 1)
                line[x] = (shade << 11) | (shade << 6) | shade;
        }
        rt_device_write(fb, y * info.pitch, line, info.pitch);
    }

    rt_device_control(fb, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
    rt_free(line);
    rt_device_close(fb);

    rt_kprintf("display_demo: wrote %ux%u RGB565 test pattern\n", info.width, info.height);
}

MSH_CMD_EXPORT(display_demo, draw RGB565 test pattern to fb0);
