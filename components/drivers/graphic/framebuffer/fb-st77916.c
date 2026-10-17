/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-01     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "fb.st77916"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define ST77916_DEFAULT_WIDTH       360
#define ST77916_DEFAULT_HEIGHT      360
#define ST77916_INIT_MAX_HZ         10000000
#define ST77916_DEFAULT_MAX_HZ      60000000
#define ST77916_TE_TIMEOUT_MS       100

#define ST77916_MADCTL              0x36
#define ST77916_MADCTL_MY           RT_BIT(7)
#define ST77916_MADCTL_MX           RT_BIT(6)
#define ST77916_MADCTL_MV           RT_BIT(5)

#define ST77916_QSPI_WRITE_CMD        0x02
#define ST77916_QSPI_WRITE_COLOR_DUAL 0xa2
#define ST77916_QSPI_WRITE_COLOR_QUAD 0x32

struct st77916_gpio
{
    rt_base_t pin;
    rt_uint8_t active_value;
};

struct st77916_format
{
    const char *name;
    rt_uint32_t mode;
    rt_uint8_t bytes_per_pixel;
};

static const struct st77916_format st77916_formats[] =
{
    { "r5g6b5", RTGRAPHIC_PIXEL_FORMAT_RGB565, 2 },
    { "r8g8b8", RTGRAPHIC_PIXEL_FORMAT_RGB888, 3 },
};

struct st77916_te
{
    rt_base_t pin;
    struct rt_semaphore sem;
    rt_bool_t sem_initialized;
    rt_bool_t irq_attached;
    rt_bool_t irq_enabled;
};

struct st77916fb
{
    struct rt_graphic_device parent;
    struct rt_qspi_device *qspi;
    struct st77916_gpio reset;
    struct st77916_te te;
    const struct st77916_format *format;
    rt_uint8_t *framebuffer;
    rt_uint8_t *transfer_buffer;
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t max_hz;
    rt_uint8_t pixel_data_lines;
    rt_uint8_t initial_madctl;
    rt_bool_t defer_display_on;
    rt_bool_t panel_enabled;
    rt_uint32_t modes[1];
};

static rt_err_t st77916_transfer(struct st77916fb *fb, rt_uint8_t opcode,
        rt_uint8_t cmd, const void *data, rt_size_t data_size,
        rt_uint8_t data_lines)
{
    struct rt_qspi_message message = {};
    rt_ssize_t result;

    message.instruction.content = opcode;
    message.instruction.qspi_lines = 1;
    message.address.content = (rt_uint32_t)cmd << 8;
    message.address.size = 24;
    message.address.qspi_lines = 1;
    message.parent.send_buf = data;
    message.parent.length = data_size;
    message.parent.cs_take = 1;
    message.parent.cs_release = 1;
    message.qspi_data_lines = data_lines;

    result = rt_qspi_transfer_message(fb->qspi, &message);

    if (result < 0)
    {
        LOG_E("QSPI write %02x:%02x (%u bytes, %u line) failed: %s",
                opcode, cmd, data_size, data_lines, rt_strerror(result));
        return result;
    }

    return result ? RT_EOK : -RT_EIO;
}

static rt_err_t st77916_write_cmd(struct st77916fb *fb, rt_uint8_t cmd,
        const void *data, rt_size_t data_size)
{
    return st77916_transfer(fb, ST77916_QSPI_WRITE_CMD, cmd, data,
            data_size, 1);
}

static void st77916_reset(struct st77916fb *fb)
{
    if (fb->reset.pin < 0)
    {
        return;
    }

    rt_pin_write(fb->reset.pin, fb->reset.active_value);
    rt_thread_mdelay(20);
    rt_pin_write(fb->reset.pin, !fb->reset.active_value);
    rt_thread_mdelay(120);
}

static void st77916_te_isr(void *param)
{
    struct st77916fb *fb = param;

    rt_sem_release(&fb->te.sem);
}

static rt_err_t st77916_te_init(struct st77916fb *fb)
{
    rt_err_t err;

    if (fb->te.pin < 0)
    {
        return RT_EOK;
    }

    if ((err = rt_sem_init(&fb->te.sem, "stte", 0, RT_IPC_FLAG_FIFO)))
    {
        return err;
    }
    fb->te.sem_initialized = RT_TRUE;
    rt_sem_control(&fb->te.sem, RT_IPC_CMD_SET_VLIMIT, (void *)1);

    rt_pin_mode(fb->te.pin, PIN_MODE_INPUT);
    if ((err = rt_pin_attach_irq(fb->te.pin, PIN_IRQ_MODE_RISING,
            st77916_te_isr, fb)))
    {
        return err;
    }
    fb->te.irq_attached = RT_TRUE;

    return RT_EOK;
}

static rt_err_t st77916_te_enable(struct st77916fb *fb)
{
    rt_err_t err;

    if (fb->te.pin < 0 || fb->te.irq_enabled)
    {
        return RT_EOK;
    }

    if (!fb->te.irq_attached)
    {
        return -RT_ENOSYS;
    }

    if ((err = rt_pin_irq_enable(fb->te.pin, PIN_IRQ_ENABLE)) == RT_EOK)
    {
        fb->te.irq_enabled = RT_TRUE;
    }

    return err;
}

static rt_err_t st77916_te_disable(struct st77916fb *fb)
{
    rt_err_t err;

    if (!fb->te.irq_enabled)
    {
        return RT_EOK;
    }

    err = rt_pin_irq_enable(fb->te.pin, PIN_IRQ_DISABLE);
    if (err == RT_EOK)
    {
        fb->te.irq_enabled = RT_FALSE;
    }

    return err;
}

static void st77916_te_deinit(struct st77916fb *fb)
{
    if (fb->te.irq_attached)
    {
        st77916_te_disable(fb);
        rt_pin_detach_irq(fb->te.pin);
        fb->te.irq_attached = RT_FALSE;
    }
    if (fb->te.sem_initialized)
    {
        rt_sem_detach(&fb->te.sem);
        fb->te.sem_initialized = RT_FALSE;
    }
}

static rt_err_t st77916_wait_te(struct st77916fb *fb)
{
    if (fb->te.pin < 0)
    {
        return -RT_ENOSYS;
    }

    if (!fb->te.irq_enabled)
    {
        return -RT_EBUSY;
    }

    /* A pending TE edge is already a suitable frame-boundary synchronisation. */
    return rt_sem_take(&fb->te.sem,
            rt_tick_from_millisecond(ST77916_TE_TIMEOUT_MS));
}

static rt_err_t st77916fb_wait_vsync(struct rt_graphic_device *gdev)
{
    struct st77916fb *fb = rt_container_of(gdev, struct st77916fb, parent);

    return st77916_wait_te(fb);
}

static rt_err_t st77916fb_dpms_switch(struct rt_graphic_device *gdev,
        rt_uint32_t dpms)
{
    struct st77916fb *fb = rt_container_of(gdev, struct st77916fb, parent);
    rt_err_t err;
    rt_uint8_t te_mode = 0x00;

    switch (dpms)
    {
    case RT_GRAPHIC_DPMS_ON:
        /* The boot logo is drawn while a deferred panel remains blanked. */
        if (fb->defer_display_on && !fb->panel_enabled)
        {
            return RT_EOK;
        }
        if (fb->te.pin < 0)
        {
            return RT_EOK;
        }

        /* Enable the panel TE output before accepting its GPIO edges. */
        if ((err = st77916_write_cmd(fb, 0x35, &te_mode, sizeof(te_mode))) != RT_EOK)
        {
            return err;
        }

        err = st77916_te_enable(fb);
        if (err != RT_EOK)
        {
            st77916_write_cmd(fb, 0x34, RT_NULL, 0);
        }

        return err;

    case RT_GRAPHIC_DPMS_STANDBY:
    case RT_GRAPHIC_DPMS_SUSPEND:
    case RT_GRAPHIC_DPMS_OFF:
        if (fb->te.pin < 0)
        {
            return RT_EOK;
        }

        if ((err = st77916_te_disable(fb)) != RT_EOK)
        {
            return err;
        }

        return st77916_write_cmd(fb, 0x34, RT_NULL, 0);

    default:
        return -RT_EINVAL;
    }
}

static rt_err_t st77916_qspi_configure(struct st77916fb *fb, rt_uint32_t max_hz)
{
    struct rt_qspi_configuration config = fb->qspi->config;
    rt_err_t err;

    config.parent.mode = RT_SPI_MODE_0 | RT_SPI_MASTER;
    config.parent.data_width = 8;
    config.parent.max_hz = max_hz;
    config.qspi_dl_width = fb->pixel_data_lines;

    err = rt_qspi_configure(fb->qspi, &config);

    /* The SPI framework applies a non-owner's configuration on its first I/O. */
    return err == -RT_EBUSY ? RT_EOK : err;
}

/*
 * panel-init-sequence records are encoded in DT as:
 *
 *     <command delay-ms payload-length payload...>
 */
static rt_err_t st77916_run_init_sequence(struct st77916fb *fb)
{
    const rt_uint8_t *sequence;
    rt_ssize_t length;
    rt_size_t remain;
    rt_err_t err;

    sequence = rt_ofw_prop_read_raw(fb->parent.parent.ofw_node,
            "panel-init-sequence", &length);
    if (!sequence || length <= 0)
    {
        return -RT_ENOENT;
    }

    remain = length;

    while (remain)
    {
        rt_uint8_t command;
        rt_uint8_t delay_ms;
        rt_uint8_t payload_size;

        if (remain < 3)
        {
            return -RT_EINVAL;
        }

        command = *sequence++;
        delay_ms = *sequence++;
        payload_size = *sequence++;
        remain -= 3;

        if (payload_size > remain)
        {
            return -RT_EINVAL;
        }

        err = st77916_write_cmd(fb, command, sequence, payload_size);
        if (err != RT_EOK)
        {
            LOG_E("panel init command %02x (%u bytes) failed: %s",
                    command, payload_size, rt_strerror(err));
            return err;
        }

        if (command == ST77916_MADCTL && payload_size == 1)
        {
            fb->initial_madctl = sequence[0];
        }

        sequence += payload_size;
        remain -= payload_size;
        if (delay_ms)
        {
            rt_thread_mdelay(delay_ms);
        }
    }

    return RT_EOK;
}

static rt_err_t st77916_set_window(struct st77916fb *fb, rt_uint16_t x,
        rt_uint16_t y, rt_uint16_t width, rt_uint16_t height)
{
    rt_uint8_t addr[] =
    {
        (x >> 8) & 0xff, x & 0xff,
        ((x + width - 1) >> 8) & 0xff, (x + width - 1) & 0xff,
    };
    rt_err_t err;

    if ((err = st77916_write_cmd(fb, 0x2a, addr, sizeof(addr))) != RT_EOK)
    {
        return err;
    }

    addr[0] = (y >> 8) & 0xff;
    addr[1] = y & 0xff;
    addr[2] = ((y + height - 1) >> 8) & 0xff;
    addr[3] = (y + height - 1) & 0xff;

    return st77916_write_cmd(fb, 0x2b, addr, sizeof(addr));
}

static rt_err_t st77916_send_pixels(struct st77916fb *fb,
        const void *pixels, rt_size_t bytes)
{
    rt_uint8_t opcode;

    if (fb->pixel_data_lines == 1)
    {
        opcode = ST77916_QSPI_WRITE_CMD;
    }
    else if (fb->pixel_data_lines == 2)
    {
        opcode = ST77916_QSPI_WRITE_COLOR_DUAL;
    }
    else if (fb->pixel_data_lines == 4)
    {
        opcode = ST77916_QSPI_WRITE_COLOR_QUAD;
    }
    else
    {
        return -RT_EINVAL;
    }

    if (fb->format->mode == RTGRAPHIC_PIXEL_FORMAT_RGB565)
    {
        const rt_uint8_t *src = pixels;
        rt_uint8_t *dst = fb->transfer_buffer;

        if (!dst || bytes & 1)
        {
            return -RT_EINVAL;
        }

        for (rt_size_t i = 0; i < bytes; i += 2)
        {
            dst[i] = src[i + 1];
            dst[i + 1] = src[i];
        }

        pixels = dst;
    }

    return st77916_transfer(fb, opcode, 0x2c, pixels,
            bytes, fb->pixel_data_lines);
}

static rt_err_t st77916fb_plane_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    rt_err_t err;
    rt_uint8_t *pixels;
    rt_uint32_t y;
    struct st77916fb *fb = rt_container_of(plane->graphic, struct st77916fb,
            parent);

    if (!rect->width || !rect->height || rect->x + rect->width > fb->width ||
            rect->y + rect->height > fb->height)
    {
        return -RT_EINVAL;
    }

    pixels = fb->framebuffer +
            (rect->y * fb->width + rect->x) * fb->format->bytes_per_pixel;

    if (fb->te.irq_enabled && (err = st77916_wait_te(fb)) != RT_EOK)
    {
        return err;
    }

    if (rect->width == fb->width)
    {
        if ((err = st77916_set_window(fb, rect->x, rect->y, rect->width,
                rect->height)) != RT_EOK)
        {
            return err;
        }

        return st77916_send_pixels(fb, pixels,
                rect->width * rect->height * fb->format->bytes_per_pixel);
    }

    for (y = 0; y < rect->height; ++y)
    {
        if ((err = st77916_set_window(fb, rect->x, rect->y + y,
                rect->width, 1)) != RT_EOK)
        {
            return err;
        }
        if ((err = st77916_send_pixels(fb, pixels,
                rect->width * fb->format->bytes_per_pixel)) != RT_EOK)
        {
            return err;
        }
        pixels += fb->width * fb->format->bytes_per_pixel;
    }

    return RT_EOK;
}

static rt_err_t st77916fb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    struct st77916fb *fb = rt_container_of(plane->graphic, struct st77916fb,
            parent);

    if (mode != fb->format->mode)
    {
        return -RT_EINVAL;
    }

    plane->line_length = fb->width * fb->format->bytes_per_pixel;
    plane->bits_per_pixel = rt_graphic_mode_bpp(mode);
    plane->framebuffer = fb->framebuffer;
    plane->screen_len = fb->width * fb->height * fb->format->bytes_per_pixel;
    plane->framebuffer_len = plane->screen_len;

    return RT_EOK;
}

static rt_err_t st77916fb_plane_prop_set(struct rt_graphic_plane *plane,
        enum rt_graphic_plane_prop prop, void *value)
{
    struct st77916fb *fb = rt_container_of(plane->graphic, struct st77916fb,
            parent);
    rt_ubase_t rotation = (rt_ubase_t)value;
    rt_uint8_t madctl = fb->initial_madctl;
    struct rt_device_rect_info rect = {0};
    rt_err_t err;

    if (prop != RT_GRAPHIC_PLANE_PROP_ROTATE)
    {
        return -RT_ENOSYS;
    }
    if (rotation > RT_GRAPHIC_PLANE_ROTATE_270)
    {
        return -RT_EINVAL;
    }
    if ((rotation & 1) && fb->width != fb->height)
    {
        return -RT_ENOSYS;
    }

    /* Compose clockwise rotation with the panel's initial address mapping. */
    switch (rotation)
    {
    case RT_GRAPHIC_PLANE_ROTATE_90:
        madctl ^= ST77916_MADCTL_MV |
                ((fb->initial_madctl & ST77916_MADCTL_MV) ?
                ST77916_MADCTL_MY : ST77916_MADCTL_MX);
        break;
    case RT_GRAPHIC_PLANE_ROTATE_180:
        madctl ^= ST77916_MADCTL_MX | ST77916_MADCTL_MY;
        break;
    case RT_GRAPHIC_PLANE_ROTATE_270:
        madctl ^= ST77916_MADCTL_MV |
                ((fb->initial_madctl & ST77916_MADCTL_MV) ?
                ST77916_MADCTL_MX : ST77916_MADCTL_MY);
        break;
    default:
        break;
    }

    err = st77916_write_cmd(fb, ST77916_MADCTL, &madctl, sizeof(madctl));
    if (err != RT_EOK)
    {
        return err;
    }
    plane->rotate = rotation;

    /* Existing GRAM pixels must be rewritten using the new address order. */
    rect.width = fb->width;
    rect.height = fb->height;
    return st77916fb_plane_update(plane, &rect);
}

static const struct rt_graphic_plane_ops st77916fb_plane_ops =
{
    .update = st77916fb_plane_update,
    .fb_remap = st77916fb_plane_fb_remap,
    .prop_set = st77916fb_plane_prop_set,
};

static const struct rt_graphic_device_ops st77916fb_ops =
{
    .dpms_switch = st77916fb_dpms_switch,
    .wait_vsync = st77916fb_wait_vsync,
};

static rt_err_t st77916fb_probe(struct rt_spi_device *spi_dev)
{
    rt_err_t err;
    const char *format_name = "r8g8b8";
    rt_uint32_t init_hz;
    rt_uint32_t width = ST77916_DEFAULT_WIDTH;
    rt_uint32_t height = ST77916_DEFAULT_HEIGHT;
    rt_uint32_t pixel_data_lines = 4;
    rt_size_t framebuffer_size;
    rt_bool_t graphic_registered = RT_FALSE;
    struct rt_device *dev = &spi_dev->parent;
    struct st77916fb *fb = rt_calloc(1, sizeof(*fb));

    if (!fb)
    {
        return -RT_ENOMEM;
    }

    fb->qspi = rt_container_of(spi_dev, struct rt_qspi_device, parent);
    fb->parent.parent.ofw_node = dev->ofw_node;
    fb->reset.pin = PIN_NONE;
    fb->te.pin = PIN_NONE;
    fb->max_hz = ST77916_DEFAULT_MAX_HZ;
    rt_dm_dev_prop_read_u32(dev, "width", &width);
    rt_dm_dev_prop_read_u32(dev, "height", &height);
    rt_dm_dev_prop_read_u32(dev, "spi-max-frequency", &fb->max_hz);
    rt_dm_dev_prop_read_u32(dev, "spi-tx-bus-width", &pixel_data_lines);
    rt_dm_dev_prop_read_string(dev, "format", &format_name);
    fb->defer_display_on = rt_dm_dev_prop_read_bool(dev,
            "rt-thread,defer-display-on");

    for (rt_size_t i = 0; i < RT_ARRAY_SIZE(st77916_formats); ++i)
    {
        if (!rt_strcmp(format_name, st77916_formats[i].name))
        {
            fb->format = &st77916_formats[i];
            break;
        }
    }
    if (!fb->format)
    {
        LOG_E("unsupported pixel format: %s", format_name);
        err = -RT_EINVAL;
        goto _fail;
    }

    if (pixel_data_lines != 1 && pixel_data_lines != 2 && pixel_data_lines != 4)
    {
        LOG_E("ST77916 requires a single-, dual-, or quad-data bus, got %u",
                pixel_data_lines);
        err = -RT_EINVAL;
        goto _fail;
    }
    fb->width = width;
    fb->height = height;
    fb->pixel_data_lines = pixel_data_lines;

    fb->reset.pin = rt_pin_get_named_pin(dev, "reset", 0, RT_NULL,
            &fb->reset.active_value);
    if (fb->reset.pin < 0 && fb->reset.pin != -RT_EEMPTY)
    {
        err = fb->reset.pin;
        goto _fail;
    }

    fb->te.pin = rt_pin_get_named_pin(dev, "te", 0, RT_NULL, RT_NULL);
    if (fb->te.pin < 0 && fb->te.pin != -RT_EEMPTY)
    {
        err = fb->te.pin;
        goto _fail;
    }

    if (fb->reset.pin >= 0)
    {
        rt_pin_mode(fb->reset.pin, PIN_MODE_OUTPUT);
    }
    if ((err = st77916_te_init(fb)) != RT_EOK)
    {
        goto _fail;
    }

    init_hz = fb->max_hz;
    if (init_hz > ST77916_INIT_MAX_HZ)
    {
        init_hz = ST77916_INIT_MAX_HZ;
    }
    if ((err = st77916_qspi_configure(fb, init_hz)) != RT_EOK)
    {
        goto _fail;
    }

    st77916_reset(fb);
    if ((err = st77916_run_init_sequence(fb)) != RT_EOK)
    {
        goto _fail;
    }
    fb->panel_enabled = !fb->defer_display_on;
    if ((err = st77916_qspi_configure(fb, fb->max_hz)) != RT_EOK)
    {
        goto _fail;
    }

    framebuffer_size = fb->width * fb->height * fb->format->bytes_per_pixel;
    fb->framebuffer = rt_calloc(1, framebuffer_size);
    if (!fb->framebuffer)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }
    if (fb->format->mode == RTGRAPHIC_PIXEL_FORMAT_RGB565)
    {
        fb->transfer_buffer = rt_malloc(framebuffer_size);
        if (!fb->transfer_buffer)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }
    }

    /* Clear panel GRAM before the generic logo updates its centre rectangle. */
    if ((err = st77916_set_window(fb, 0, 0, fb->width, fb->height)) != RT_EOK ||
            (err = st77916_send_pixels(fb, fb->framebuffer,
                    framebuffer_size)) != RT_EOK)
    {
        goto _fail;
    }

    fb->modes[0] = fb->format->mode;
    if (fb->te.pin >= 0)
    {
        fb->parent.ops = &st77916fb_ops;
    }
    if ((err = rt_graphic_device_simple_register(&fb->parent, fb->width,
            fb->height, 0, &st77916fb_plane_ops, fb->modes,
            RT_ARRAY_SIZE(fb->modes))) != RT_EOK)
    {
        goto _fail;
    }
    graphic_registered = RT_TRUE;

    if (fb->defer_display_on)
    {
        if ((err = st77916_write_cmd(fb, 0x29, RT_NULL, 0)) != RT_EOK)
        {
            goto _fail;
        }

        fb->panel_enabled = RT_TRUE;
        if ((err = st77916fb_dpms_switch(&fb->parent,
                RT_GRAPHIC_DPMS_ON)) != RT_EOK)
        {
            goto _fail;
        }
    }

    spi_dev->parent.user_data = fb;
    return RT_EOK;

_fail:
    if (graphic_registered)
    {
        rt_graphic_device_simple_unregister(&fb->parent);
    }
    st77916_te_deinit(fb);
    rt_free(fb->transfer_buffer);
    rt_free(fb->framebuffer);
    rt_free(fb);

    return err;
}

static rt_err_t st77916fb_remove(struct rt_spi_device *spi_dev)
{
    struct st77916fb *fb = spi_dev->parent.user_data;

    st77916_te_deinit(fb);
    st77916_write_cmd(fb, 0x28, RT_NULL, 0);
    rt_graphic_device_simple_unregister(&fb->parent);
    rt_free(fb->transfer_buffer);
    rt_free(fb->framebuffer);
    rt_free(fb);

    return RT_EOK;
}

static const struct rt_ofw_node_id st77916fb_ofw_ids[] =
{
    { .compatible = "sitronix,st77916" },
    { /* sentinel */ },
};

static struct rt_spi_driver st77916fb_driver =
{
    .ofw_ids = st77916fb_ofw_ids,
    .probe = st77916fb_probe,
    .remove = st77916fb_remove,
};
RT_SPI_DRIVER_EXPORT(st77916fb_driver);
