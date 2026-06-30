/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "fb.ili9486"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define ILI9486_NATIVE_WIDTH    320
#define ILI9486_NATIVE_HEIGHT   480
#define ILI9486_BPP             16
#define ILI9486_STRIDE          (ILI9486_NATIVE_WIDTH * (ILI9486_BPP / 8))
#define ILI9486_SPI_MAX_HZ      32000000

struct gpiod
{
    rt_ubase_t pin;
    rt_uint8_t active_val;
};

struct ili9486fb
{
    struct rt_graphic_device parent;
    struct rt_spi_device *spi;

    struct gpiod reset;
    struct gpiod dc;

    rt_uint32_t width;
    rt_uint32_t height;

    rt_uint8_t buffer[ILI9486_NATIVE_WIDTH * ILI9486_NATIVE_HEIGHT * (ILI9486_BPP / 8)];
    rt_uint8_t framebuffer[ILI9486_NATIVE_WIDTH * ILI9486_NATIVE_HEIGHT * (ILI9486_BPP / 8)];
};

static void ili9486fb_set_dc(struct ili9486fb *ifb, rt_bool_t data_mode)
{
    if (ifb->dc.pin >= 0)
    {
        rt_pin_write(ifb->dc.pin, data_mode ? ifb->dc.active_val : !ifb->dc.active_val);
    }
}

static void ili9486fb_write_data(struct ili9486fb *ifb, rt_uint8_t data)
{
    rt_uint8_t send_data[2];

    send_data[0] = (data >> 8) & 0xff;
    send_data[1] = data & 0xff;

    rt_spi_transfer(ifb->spi, send_data, RT_NULL, sizeof(send_data));
}

#define ili9486fb_write_data_list(ifb, ...)                 \
do {                                                        \
    rt_uint8_t __data[] = { __VA_ARGS__ };                  \
    for (int __i = 0; __i < RT_ARRAY_SIZE(__data); ++__i)   \
    {                                                       \
        ili9486fb_write_data(ifb, __data[__i]);             \
    }                                                       \
} while (0)

static void ili9486fb_write_cmd(struct ili9486fb *ifb, rt_uint8_t cmd)
{
    ili9486fb_set_dc(ifb, RT_FALSE);
    ili9486fb_write_data(ifb, cmd);
    ili9486fb_set_dc(ifb, RT_TRUE);
}

static void ili9486fb_write_reg(struct ili9486fb *ifb, rt_uint8_t cmd,
        const rt_uint8_t *params, rt_size_t params_nr)
{
    ili9486fb_write_cmd(ifb, cmd);

    for (rt_size_t i = 0; i < params_nr; ++i)
    {
        ili9486fb_write_data(ifb, params[i]);
    }
}

static void ili9486fb_set_addr_win(struct ili9486fb *ifb,
        rt_uint16_t x, rt_uint16_t y, rt_uint16_t width, rt_uint16_t height)
{
    rt_uint8_t col[] =
    {
        (x >> 8) & 0xff, x & 0xff,
        ((x + width - 1) >> 8) & 0xff, (x + width - 1) & 0xff,
    };
    rt_uint8_t row[] =
    {
        (y >> 8) & 0xff, y & 0xff,
        ((y + height - 1) >> 8) & 0xff, (y + height - 1) & 0xff,
    };

    ili9486fb_write_reg(ifb, 0x2a, col, RT_ARRAY_SIZE(col));
    ili9486fb_write_reg(ifb, 0x2b, row, RT_ARRAY_SIZE(row));
    ili9486fb_write_cmd(ifb, 0x2c);
}

static rt_uint16_t ili9486fb_rgb565_to_be(rt_uint16_t color)
{
    return (color >> 8) | (color << 8);
}

static rt_uint8_t *ili9486fb_copy_pixels_be(rt_uint8_t *dst, const rt_uint16_t *src,
        rt_uint32_t width, rt_uint32_t height, rt_uint32_t src_stride)
{
    rt_uint16_t *dst16 = (rt_uint16_t *)dst;

    if (width == ILI9486_NATIVE_WIDTH)
    {
        rt_size_t count = width * height;

        for (rt_size_t i = 0; i < count; ++i)
        {
            dst16[i] = ili9486fb_rgb565_to_be(src[i]);
        }

        return dst + count * (ILI9486_BPP / 8);
    }

    for (rt_uint32_t y = 0; y < height; ++y)
    {
        for (rt_uint32_t x = 0; x < width; ++x)
        {
            dst16[x] = ili9486fb_rgb565_to_be(src[x]);
        }

        src = (const rt_uint16_t *)((const rt_uint8_t *)src + src_stride);
        dst16 += width;
    }

    return (rt_uint8_t *)dst16;
}

static void ili9486fb_send_pixels(struct ili9486fb *ifb, rt_uint16_t *pixels,
        rt_uint32_t width, rt_uint32_t height, rt_uint32_t stride)
{
    rt_uint8_t *buf_end;

    buf_end = ili9486fb_copy_pixels_be(ifb->buffer, pixels, width, height, stride);

    ili9486fb_set_dc(ifb, RT_TRUE);
    rt_spi_transfer(ifb->spi, ifb->buffer, RT_NULL, buf_end - ifb->buffer);
}

static rt_err_t ili9486fb_plane_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    rt_uint16_t *pixels;
    struct ili9486fb *ifb = rt_container_of(plane->graphic, struct ili9486fb, parent);

    ili9486fb_set_addr_win(ifb, rect->x, rect->y, rect->width, rect->height);

    pixels = (rt_uint16_t *)(ifb->framebuffer +
            rect->y * ILI9486_STRIDE + rect->x * (ILI9486_BPP / 8));

    ili9486fb_send_pixels(ifb, pixels, rect->width, rect->height, ILI9486_STRIDE);

    return RT_EOK;
}

static rt_err_t ili9486fb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    struct ili9486fb *ifb = rt_container_of(plane->graphic, struct ili9486fb, parent);

    plane->line_length = ILI9486_STRIDE;
    plane->bits_per_pixel = rt_graphic_mode_bpp(mode);

    plane->framebuffer = ifb->framebuffer;
    plane->screen_len = sizeof(ifb->framebuffer);
    plane->framebuffer_len = plane->screen_len;

    return RT_EOK;
}

static const struct rt_graphic_plane_ops ili9486fb_plane_ops =
{
    .update = ili9486fb_plane_update,
    .fb_remap = ili9486fb_plane_fb_remap,
};

static rt_uint32_t ili9486fb_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
};

static void ili9486fb_gpio_init(struct ili9486fb *ifb)
{
    if (ifb->reset.pin >= 0)
    {
        rt_pin_mode(ifb->reset.pin, PIN_MODE_OUTPUT);
    }

    if (ifb->dc.pin >= 0)
    {
        rt_pin_mode(ifb->dc.pin, PIN_MODE_OUTPUT);
        ili9486fb_set_dc(ifb, RT_TRUE);
    }
}

static void ili9486fb_reset(struct ili9486fb *ifb)
{
    if (ifb->reset.pin < 0)
    {
        return;
    }

    rt_pin_write(ifb->reset.pin, !ifb->reset.active_val);
    rt_hw_us_delay(20);

    rt_pin_write(ifb->reset.pin, ifb->reset.active_val);
    rt_thread_mdelay(120);
}

static void ili9486fb_set_rotation(struct ili9486fb *ifb, rt_uint32_t rotation)
{
    rt_uint8_t madctl;

    switch (rotation)
    {
    case 90:
        madctl = 0x28;
        ifb->width = ILI9486_NATIVE_HEIGHT;
        ifb->height = ILI9486_NATIVE_WIDTH;
        break;
    case 180:
        madctl = 0x98;
        ifb->width = ILI9486_NATIVE_WIDTH;
        ifb->height = ILI9486_NATIVE_HEIGHT;
        break;
    case 270:
        madctl = 0xf8;
        ifb->width = ILI9486_NATIVE_HEIGHT;
        ifb->height = ILI9486_NATIVE_WIDTH;
        break;
    default:
        madctl = 0x48;
        ifb->width = ILI9486_NATIVE_WIDTH;
        ifb->height = ILI9486_NATIVE_HEIGHT;
        break;
    }

    ili9486fb_write_cmd(ifb, 0x36);
    ili9486fb_write_data(ifb, madctl);

    if (rotation == 90 || rotation == 270)
    {
        ili9486fb_write_cmd(ifb, 0x2b);
        ili9486fb_write_data_list(ifb, 0x00, 0x00, 0x01, 0x3f);

        ili9486fb_write_cmd(ifb, 0x2a);
        ili9486fb_write_data_list(ifb, 0x00, 0x00, 0x01, 0xe0);
    }
    else
    {
        ili9486fb_write_cmd(ifb, 0x2a);
        ili9486fb_write_data_list(ifb, 0x00, 0x00, 0x01, 0x3f);

        ili9486fb_write_cmd(ifb, 0x2b);
        ili9486fb_write_data_list(ifb, 0x00, 0x00, 0x01, 0xe0);
    }
}

static void ili9486fb_init(struct ili9486fb *ifb, rt_uint32_t rotation)
{
    /* Interface Mode Control */
    ili9486fb_write_cmd(ifb, 0xb0);
    ili9486fb_write_data(ifb, 0x00);

    /* Display off */
    ili9486fb_write_cmd(ifb, 0x28);
    rt_thread_mdelay(150);

    /* Interface Pixel Format, 16 bit/pixel */
    ili9486fb_write_cmd(ifb, 0x3a);
    ili9486fb_write_data(ifb, 0x55);

    ili9486fb_write_cmd(ifb, 0xc2);
    ili9486fb_write_data(ifb, 0x44);

    /* VCOM Control */
    ili9486fb_write_cmd(ifb, 0xc5);
    ili9486fb_write_data_list(ifb, 0x00, 0x00, 0x00, 0x00);

    /* PGAMCTRL (Positive Gamma Control) */
    ili9486fb_write_cmd(ifb, 0xe0);
    ili9486fb_write_data_list(ifb, 0x0f, 0x1f, 0x1c, 0x0c, 0x0f, 0x08, 0x48,
            0x98, 0x37, 0x0a, 0x13, 0x04, 0x11, 0x0d, 0x00);

    /* NGAMCTRL (Negative Gamma Correction) */
    ili9486fb_write_cmd(ifb, 0xe1);
    ili9486fb_write_data_list(ifb, 0x0f, 0x32, 0x2e, 0x0b, 0x0d, 0x05, 0x47,
            0x75, 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00);

    /* Digital Gamma Control */
    ili9486fb_write_cmd(ifb, 0xe2);
    ili9486fb_write_data_list(ifb, 0x0f, 0x32, 0x2e, 0x0b, 0x0d, 0x05, 0x47,
            0x75, 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00);

    /* Sleep out */
    ili9486fb_write_cmd(ifb, 0x11);
    rt_thread_mdelay(150);

    /* Display inversion off */
    ili9486fb_write_cmd(ifb, 0x20);

    ili9486fb_set_rotation(ifb, rotation);

    /* Display on */
    ili9486fb_write_cmd(ifb, 0x29);
    rt_thread_mdelay(150);
}

static rt_err_t ili9486fb_spi_setup(struct rt_spi_device *spi_dev)
{
    struct rt_spi_configuration cfg;
    rt_uint32_t max_hz = ILI9486_SPI_MAX_HZ;
    struct rt_device *dev = &spi_dev->parent;

    rt_dm_dev_prop_read_u32(dev, "spi-max-frequency", &max_hz);

    cfg = spi_dev->config;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MODE_0 | RT_SPI_MASTER;
    cfg.max_hz = max_hz;

    return rt_spi_configure(spi_dev, &cfg);
}

static rt_err_t ili9486fb_probe(struct rt_spi_device *spi_dev)
{
    rt_err_t err;
    rt_uint32_t rotation = 0;
    struct rt_device *dev = &spi_dev->parent;
    struct ili9486fb *ifb = rt_calloc(1, sizeof(*ifb));

    if (!ifb)
    {
        return -RT_ENOMEM;
    }
    ifb->spi = spi_dev;

    ifb->reset.pin = rt_pin_get_named_pin(dev, "reset", 0,
            RT_NULL, &ifb->reset.active_val);

    if (ifb->reset.pin < 0 && ifb->reset.pin != -RT_EEMPTY)
    {
        err = ifb->reset.pin;
        goto _fail;
    }

    ifb->dc.pin = rt_pin_get_named_pin(dev, "dc", 0,
            RT_NULL, &ifb->dc.active_val);

    if (ifb->dc.pin < 0)
    {
        err = (ifb->dc.pin == -RT_EEMPTY) ? -RT_EINVAL : ifb->dc.pin;
        goto _fail;
    }

    rt_dm_dev_prop_read_u32(dev, "rotation", &rotation);

    if ((err = ili9486fb_spi_setup(spi_dev)) != RT_EOK)
    {
        goto _fail;
    }

    ili9486fb_gpio_init(ifb);
    ili9486fb_reset(ifb);
    ili9486fb_init(ifb, rotation);

    if ((err = rt_graphic_device_simple_register(&ifb->parent,
            ifb->width, ifb->height, 0, &ili9486fb_plane_ops,
            ili9486fb_modes, RT_ARRAY_SIZE(ili9486fb_modes))))
    {
        goto _fail;
    }

    spi_dev->parent.user_data = ifb;

    return RT_EOK;

_fail:
    rt_free(ifb);

    return err;
}

static rt_err_t ili9486fb_remove(struct rt_spi_device *spi_dev)
{
    struct ili9486fb *ifb = spi_dev->parent.user_data;

    rt_graphic_device_simple_unregister(&ifb->parent);

    ili9486fb_write_cmd(ifb, 0x28);

    rt_free(ifb);

    return RT_EOK;
}

static const struct rt_spi_device_id ili9486fb_ids[] =
{
    { .name = "ili9486" },
    { .name = "rpi-lcd-35" },
    { .name = "piscreen" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id ili9486fb_ofw_ids[] =
{
    { .compatible = "waveshare,rpi-lcd-35" },
    { .compatible = "ozzmaker,piscreen" },
    { .compatible = "ilitek,ili9486" },
    { /* sentinel */ },
};

static struct rt_spi_driver ili9486fb_driver =
{
    .ids = ili9486fb_ids,
    .ofw_ids = ili9486fb_ofw_ids,

    .probe = ili9486fb_probe,
    .remove = ili9486fb_remove,
};
RT_SPI_DRIVER_EXPORT(ili9486fb_driver);
