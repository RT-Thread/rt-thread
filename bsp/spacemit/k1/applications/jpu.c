/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <jpu.h>

#if defined(RT_USING_FINSH) && defined(RT_USING_DFS) && defined(RT_USING_GRAPHIC) && defined(RT_SOC_CHIP_MEDIA_JPU)
#include <finsh.h>
#include <fcntl.h>
#include <unistd.h>

#define JPU_ALIGN(value, align)       (((value) + (align) - 1) & ~((align) - 1))
#define JPU_FILE_IO_CHUNK             512U

struct jpu_huffman
{
    rt_uint8_t bits[JPU_HUFF_BITS_NUM];
    rt_uint8_t values[JPU_HUFF_VALUES_NUM];
    rt_uint16_t count;
};

struct jpu_jpeg
{
    rt_uint8_t *data;
    rt_size_t size;
    rt_uint16_t quant[4][JPU_QUANT_VALUES_NUM];
    struct jpu_huffman huff[JPU_HUFF_TABLE_NUM];
    rt_uint8_t component_id[3];
    rt_uint8_t h[3];
    rt_uint8_t v[3];
    rt_uint8_t qsel[3];
    rt_uint8_t dcsel[3];
    rt_uint8_t acsel[3];
    rt_uint8_t components;
    rt_uint8_t format;
    rt_uint16_t width;
    rt_uint16_t height;
    rt_uint16_t aligned_width;
    rt_uint16_t aligned_height;
    rt_uint16_t restart_interval;
    rt_uint16_t y_stride;
    rt_uint16_t c_stride;
    rt_uint16_t c_height;
    rt_size_t entropy_offset;
};

static rt_uint16_t jpu_get_be16(const rt_uint8_t *p)
{
    return ((rt_uint16_t)p[0] << 8) | p[1];
}

static rt_err_t jpu_read_stream(int fd, void *destination, rt_size_t size)
{
    rt_uint8_t *buffer;
    rt_size_t offset = 0;
    rt_size_t buffer_size = rt_min(size, (rt_size_t)JPU_FILE_IO_CHUNK);
    rt_err_t err = RT_EOK;

    buffer = rt_malloc(buffer_size);
    if (!buffer)
    {
        return -RT_ENOMEM;
    }

    while (offset < size)
    {
        rt_size_t requested = rt_min(size - offset, buffer_size);
        ssize_t received = read(fd, buffer, requested);

        if (received <= 0)
        {
            err = -RT_EIO;
            break;
        }

        rt_memcpy((rt_uint8_t *)destination + offset, buffer, received);
        offset += received;
    }

    rt_free(buffer);
    return err;
}

static rt_err_t jpu_parse_dqt(struct jpu_jpeg *jpg, const rt_uint8_t *p,
        rt_size_t length)
{
    while (length)
    {
        rt_uint8_t precision, table;
        int i;

        precision = p[0] >> 4;
        table = p[0] & 0xf;
        ++p;
        --length;
        if (precision > 1 || table > 3 ||
            length < (rt_size_t)(JPU_QUANT_VALUES_NUM << precision))
        {
            return -RT_EINVAL;
        }

        for (i = 0; i < JPU_QUANT_VALUES_NUM; ++i)
        {
            jpg->quant[table][i] = precision ? jpu_get_be16(p + i * 2) : p[i];
        }

        p += JPU_QUANT_VALUES_NUM << precision;
        length -= JPU_QUANT_VALUES_NUM << precision;
    }

    return RT_EOK;
}

static rt_err_t jpu_parse_dht(struct jpu_jpeg *jpg, const rt_uint8_t *p,
        rt_size_t length)
{
    while (length)
    {
        struct jpu_huffman *huff;
        rt_uint8_t type, id;
        rt_uint16_t count = 0;
        int i;

        if (length < 17)
        {
            return -RT_EINVAL;
        }

        type = p[0] >> 4;
        id = p[0] & 0xf;
        ++p;
        --length;
        if (type > 1 || id > 1)
        {
            return -RT_ENOSYS;
        }

        huff = &jpg->huff[id * 2 + type];
        for (i = 0; i < JPU_HUFF_BITS_NUM; ++i)
        {
            count += huff->bits[i] = p[i];
        }
        p += JPU_HUFF_BITS_NUM;
        length -= JPU_HUFF_BITS_NUM;

        if (count > (type ? JPU_HUFF_VALUES_NUM : 12) || length < count)
        {
            return -RT_EINVAL;
        }

        rt_memcpy(huff->values, p, count);
        huff->count = count;
        p += count;
        length -= count;
    }

    return RT_EOK;
}

static rt_err_t jpu_parse_sof(struct jpu_jpeg *jpg, const rt_uint8_t *p,
        rt_size_t length)
{
    rt_uint8_t sample;
    int i;

    if (length < 6 || p[0] != 8 || (p[5] != 1 && p[5] != 3) ||
        length != 6U + p[5] * 3U)
    {
        return -RT_ENOSYS;
    }

    jpg->height = jpu_get_be16(p + 1);
    jpg->width = jpu_get_be16(p + 3);
    jpg->components = p[5];
    if (!jpg->width || !jpg->height)
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < jpg->components; ++i)
    {
        jpg->component_id[i] = p[6 + i * 3];
        jpg->h[i] = p[7 + i * 3] >> 4;
        jpg->v[i] = p[7 + i * 3] & 0xf;
        jpg->qsel[i] = p[8 + i * 3];
        if (!jpg->h[i] || !jpg->v[i] || jpg->qsel[i] > 3)
        {
            return -RT_EINVAL;
        }
    }

    if (jpg->components == 1)
    {
        jpg->format = JPU_FORMAT_400;
    }
    else
    {
        if (jpg->h[1] != 1 || jpg->v[1] != 1 ||
            jpg->h[2] != 1 || jpg->v[2] != 1)
        {
            return -RT_ENOSYS;
        }

        sample = (jpg->h[0] << 2) | jpg->v[0];
        switch (sample)
        {
        case 0x0a:
            jpg->format = JPU_FORMAT_420;
            break;
        case 0x09:
            jpg->format = JPU_FORMAT_422;
            break;
        case 0x06:
            jpg->format = JPU_FORMAT_440;
            break;
        case 0x05:
            jpg->format = JPU_FORMAT_444;
            break;
        default:
            return -RT_ENOSYS;
        }
    }

    return RT_EOK;
}

static rt_err_t jpu_parse_sos(struct jpu_jpeg *jpg, const rt_uint8_t *p,
        rt_size_t length)
{
    int i, component;

    if (length < 4 || p[0] != jpg->components ||
        length != 4U + p[0] * 2U)
    {
        return -RT_ENOSYS;
    }

    for (i = 0; i < p[0]; ++i)
    {
        for (component = 0; component < jpg->components; ++component)
        {
            if (jpg->component_id[component] == p[1 + i * 2])
            {
                break;
            }
        }

        if (component == jpg->components ||
            (p[2 + i * 2] >> 4) > 1 || (p[2 + i * 2] & 0xf) > 1)
        {
            return -RT_ENOSYS;
        }

        jpg->dcsel[component] = p[2 + i * 2] >> 4;
        jpg->acsel[component] = p[2 + i * 2] & 0xf;
    }

    if (p[length - 3] != 0 || p[length - 2] != 63 || p[length - 1] != 0)
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t jpu_validate_tables(struct jpu_jpeg *jpg)
{
    int i;

    for (i = 0; i < jpg->components; ++i)
    {
        if (!jpg->huff[jpg->dcsel[i] * 2].count ||
            !jpg->huff[jpg->acsel[i] * 2 + 1].count ||
            !jpg->quant[jpg->qsel[i]][0])
        {
            return -RT_EINVAL;
        }
    }

    return RT_EOK;
}

static rt_err_t jpu_parse(struct jpu_jpeg *jpg)
{
    rt_size_t pos = 2;
    rt_bool_t have_sof = RT_FALSE;

    if (jpg->size < 4 || jpu_get_be16(jpg->data) != 0xffd8)
    {
        return -RT_EINVAL;
    }

    while (pos + 1 < jpg->size)
    {
        rt_uint8_t marker;
        rt_uint16_t section_length;
        const rt_uint8_t *section;
        rt_err_t err = RT_EOK;

        while (pos < jpg->size && jpg->data[pos] == 0xff)
        {
            ++pos;
        }
        if (pos >= jpg->size)
        {
            break;
        }

        marker = jpg->data[pos++];
        if (marker == 0xd9)
        {
            break;
        }
        if (marker == 0xd8 || (marker >= 0xd0 && marker <= 0xd7))
        {
            continue;
        }
        if (pos + 2 > jpg->size)
        {
            return -RT_EINVAL;
        }

        section_length = jpu_get_be16(jpg->data + pos);
        if (section_length < 2 || pos + section_length > jpg->size)
        {
            return -RT_EINVAL;
        }
        section = jpg->data + pos + 2;

        switch (marker)
        {
        case 0xc0:
            err = jpu_parse_sof(jpg, section, section_length - 2);
            have_sof = err == RT_EOK;
            break;
        case 0xc4:
            err = jpu_parse_dht(jpg, section, section_length - 2);
            break;
        case 0xdb:
            err = jpu_parse_dqt(jpg, section, section_length - 2);
            break;
        case 0xdd:
            if (section_length != 4)
            {
                err = -RT_EINVAL;
            }
            else
            {
                jpg->restart_interval = jpu_get_be16(section);
            }
            break;
        case 0xda:
            if (!have_sof)
            {
                return -RT_EINVAL;
            }
            if ((err = jpu_parse_sos(jpg, section, section_length - 2)) != RT_EOK)
            {
                return err;
            }
            jpg->entropy_offset = pos + section_length;
            return jpu_validate_tables(jpg);
        default:
            if (marker >= 0xc1 && marker <= 0xcf &&
                marker != 0xc4 && marker != 0xc8 && marker != 0xcc)
            {
                return -RT_ENOSYS;
            }
            break;
        }

        if (err != RT_EOK)
        {
            return err;
        }
        pos += section_length;
    }

    return -RT_EINVAL;
}

static void jpu_fill_tables(struct jpu_dec_tables *tables,
        const struct jpu_jpeg *jpg)
{
    const struct jpu_huffman *fallback_dc = RT_NULL;
    const struct jpu_huffman *fallback_ac = RT_NULL;
    int table, component;

    for (table = 0; table < JPU_HUFF_TABLE_NUM; ++table)
    {
        if (jpg->huff[table].count)
        {
            if (table & 1)
            {
                fallback_ac = &jpg->huff[table];
            }
            else
            {
                fallback_dc = &jpg->huff[table];
            }
        }
    }

    for (table = 0; table < JPU_HUFF_TABLE_NUM; ++table)
    {
        const struct jpu_huffman *huff = &jpg->huff[table];

        if (!huff->count)
        {
            huff = (table & 1) ? fallback_ac : fallback_dc;
        }
        rt_memcpy(tables->huff_bits[table], huff->bits,
                sizeof(tables->huff_bits[table]));
        rt_memcpy(tables->huff_values[table], huff->values,
                sizeof(tables->huff_values[table]));
    }

    for (component = 0; component < JPU_QUANT_COMPONENT_NUM; ++component)
    {
        int source = component < jpg->components ? component : 0;

        rt_memcpy(tables->quant[component], jpg->quant[jpg->qsel[source]],
                sizeof(tables->quant[component]));
    }
}

static void jpu_fill_request(struct jpu_decode_request *req,
        const struct jpu_jpeg *jpg)
{
    req->frame.width = jpg->width;
    req->frame.height = jpg->height;
    req->frame.format = jpg->format;
    req->entropy_offset = jpg->entropy_offset;
    req->restart_interval = jpg->restart_interval;
    req->components = jpg->components;
    rt_memcpy(req->dc_selector, jpg->dcsel, sizeof(req->dc_selector));
    rt_memcpy(req->ac_selector, jpg->acsel, sizeof(req->ac_selector));
    jpu_fill_tables(&req->tables, jpg);
}

static rt_uint8_t jpu_clip(int value)
{
    if (value < 0)
    {
        return 0;
    }
    if (value > 255)
    {
        return 255;
    }
    return value;
}

static rt_err_t jpu_store_pixel(rt_uint8_t format, rt_uint8_t *dst,
        rt_uint8_t r, rt_uint8_t g, rt_uint8_t b)
{
    switch (format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        *(rt_uint16_t *)dst = (r >> 3) << 11 | (g >> 2) << 5 | (b >> 3);
        break;
    case RTGRAPHIC_PIXEL_FORMAT_BGR565:
        *(rt_uint16_t *)dst = (b >> 3) << 11 | (g >> 2) << 5 | (r >> 3);
        break;
    case RTGRAPHIC_PIXEL_FORMAT_RGB888:
        dst[0] = r;
        dst[1] = g;
        dst[2] = b;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_BGR888:
        dst[0] = b;
        dst[1] = g;
        dst[2] = r;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        *(rt_uint32_t *)dst = 0xff000000U | (rt_uint32_t)r << 16 |
                              (rt_uint32_t)g << 8 | b;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        *(rt_uint32_t *)dst = 0xff000000U | (rt_uint32_t)b << 16 |
                              (rt_uint32_t)g << 8 | r;
        break;
    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t jpu_show_frame(const char *fb_name, const struct jpu_jpeg *jpg,
        const rt_uint8_t *frame)
{
    struct rt_device_graphic_info info;
    struct rt_graphic_device *graphic;
    rt_device_t fb = rt_device_find(fb_name);
    rt_bool_t restore_auto_update;
    rt_uint8_t *display_buffer;
    rt_size_t screen_size;
    const rt_uint8_t *y_plane = frame;
    const rt_uint8_t *cb_plane = y_plane + jpg->y_stride * jpg->aligned_height;
    const rt_uint8_t *cr_plane = cb_plane + jpg->c_stride * jpg->c_height;
    int x0, y0, copy_width, copy_height, source_x, source_y;
    int bytes_per_pixel, x, y;
    rt_err_t err;

    if (!fb)
    {
        return -RT_ENOSYS;
    }

    graphic = rt_container_of(fb, struct rt_graphic_device, parent);
    restore_auto_update = graphic->update_timer != RT_NULL;
    if ((err = rt_device_open(fb, RT_DEVICE_OFLAG_RDWR)) != RT_EOK)
    {
        return err;
    }
    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_GET_INFO, &info)) != RT_EOK)
    {
        goto _out;
    }
    if (!info.framebuffer || !(bytes_per_pixel = info.bits_per_pixel / 8))
    {
        err = -RT_EINVAL;
        goto _out;
    }
    screen_size = (rt_size_t)info.pitch * info.height;
    if (!screen_size || screen_size > info.smem_len / 2U)
    {
        rt_kprintf("%s needs a double framebuffer for tear-free display "
                "(have %u, need %u bytes)\n", fb_name,
                (unsigned int)info.smem_len,
                (unsigned int)(screen_size * 2U));
        err = -RT_ENOMEM;
        goto _out;
    }
    display_buffer = (rt_uint8_t *)info.framebuffer + screen_size;

    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_POWERON, RT_NULL)) != RT_EOK)
    {
        goto _out;
    }

    if (restore_auto_update)
    {
        rt_graphic_device_update_auto(graphic, 0);
    }

    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_PAN_DISPLAY,
            info.framebuffer)) != RT_EOK ||
        (err = rt_device_control(fb, RTGRAPHIC_CTRL_WAIT_VSYNC,
            RT_NULL)) != RT_EOK)
    {
        goto _restore;
    }

    rt_memset(display_buffer, 0, screen_size);
    copy_width = rt_min((int)jpg->width, (int)info.width);
    copy_height = rt_min((int)jpg->height, (int)info.height);
    x0 = (info.width - copy_width) / 2;
    y0 = (info.height - copy_height) / 2;
    source_x = (jpg->width - copy_width) / 2;
    source_y = (jpg->height - copy_height) / 2;

    for (y = 0; y < copy_height; ++y)
    {
        rt_uint8_t *dst = display_buffer +
                (y0 + y) * info.pitch + x0 * bytes_per_pixel;
        int sy = source_y + y;

        for (x = 0; x < copy_width; ++x)
        {
            int sx = source_x + x;
            int cx = sx, cy = sy;
            int yy, cb = 128, cr = 128;
            rt_uint8_t r, g, b;

            if (jpg->format == JPU_FORMAT_420 || jpg->format == JPU_FORMAT_422)
            {
                cx >>= 1;
            }
            if (jpg->format == JPU_FORMAT_420 || jpg->format == JPU_FORMAT_440)
            {
                cy >>= 1;
            }
            yy = y_plane[sy * jpg->y_stride + sx];
            if (jpg->format != JPU_FORMAT_400)
            {
                cb = cb_plane[cy * jpg->c_stride + cx];
                cr = cr_plane[cy * jpg->c_stride + cx];
            }

            cb -= 128;
            cr -= 128;
            r = jpu_clip(yy + ((359 * cr) >> 8));
            g = jpu_clip(yy - ((88 * cb + 183 * cr) >> 8));
            b = jpu_clip(yy + ((454 * cb) >> 8));
            if ((err = jpu_store_pixel(info.pixel_format,
                    dst + x * bytes_per_pixel, r, g, b)) != RT_EOK)
            {
                goto _restore;
            }
        }
    }

    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_PAN_DISPLAY,
            display_buffer)) != RT_EOK ||
        (err = rt_device_control(fb, RTGRAPHIC_CTRL_WAIT_VSYNC,
            RT_NULL)) != RT_EOK)
    {
        goto _restore;
    }

_restore:
    if (restore_auto_update)
    {
        rt_graphic_device_update_auto(graphic, RT_GRAPHIC_UPDATE_MS);
    }
_out:
    rt_device_close(fb);
    return err;
}

static int jpu_show(int argc, char **argv)
{
    const char *path;
    const char *fb_name;
    struct jpu_jpeg jpg = { 0 };
    struct jpu_buffer stream = { 0 };
    struct jpu_buffer frame = { 0 };
    struct jpu_decode_request *req = RT_NULL;
    rt_device_t jpu = rt_device_find("jpu0");
    off_t file_size;
    int fd = -1;
    rt_err_t err = -RT_ERROR;

    if (argc < 2 || argc > 3)
    {
        rt_kprintf("Usage: jpu_show <jpeg> [framebuffer]\n");
        return -RT_EINVAL;
    }

    path = argv[1];
    fb_name = argc > 2 ? argv[2] : "fb0";

    if (!jpu)
    {
        rt_kprintf("jpu0 not found\n");
        return -RT_ENOSYS;
    }
    if ((err = rt_device_open(jpu, RT_DEVICE_OFLAG_RDWR)) != RT_EOK)
    {
        rt_kprintf("open jpu0 failed: %d\n", err);
        return err;
    }

    fd = open(path, O_RDONLY, 0);
    if (fd < 0)
    {
        rt_kprintf("open %s failed\n", path);
        err = -RT_EIO;
        goto _out;
    }
    file_size = lseek(fd, 0, SEEK_END);
    if (lseek(fd, 0, SEEK_SET) < 0)
    {
        err = -RT_EIO;
        goto _out;
    }
    if (file_size <= 0 || file_size > JPU_BUFFER_MAX_SIZE - JPU_STREAM_PADDING)
    {
        err = -RT_EINVAL;
        goto _out;
    }

    stream.size = JPU_ALIGN((rt_size_t)file_size + JPU_STREAM_PADDING, 4096);
    if ((err = rt_device_control(jpu, JPU_ALLOC_BUFFER, &stream)) != RT_EOK)
    {
        rt_kprintf("allocate JPU stream buffer failed: %d\n", err);
        goto _out;
    }
    rt_memset(stream.virt_addr, 0xff, stream.size);
    if ((err = jpu_read_stream(fd, stream.virt_addr, file_size)) != RT_EOK)
    {
        rt_kprintf("read %s into JPU stream buffer failed: %d\n", path, err);
        goto _out;
    }

    jpg.data = stream.virt_addr;
    jpg.size = file_size;
    if ((err = jpu_parse(&jpg)) != RT_EOK)
    {
        rt_kprintf("unsupported or invalid baseline JPEG: %d\n", err);
        goto _out;
    }

    req = rt_calloc(1, sizeof(*req));
    if (!req)
    {
        err = -RT_ENOMEM;
        goto _out;
    }
    jpu_fill_request(req, &jpg);
    if ((err = rt_device_control(jpu, JPU_QUERY_FRAME, &req->frame)) != RT_EOK)
    {
        rt_kprintf("unsupported JPU output layout: %d\n", err);
        goto _out;
    }

    jpg.aligned_width = req->frame.aligned_width;
    jpg.aligned_height = req->frame.aligned_height;
    jpg.y_stride = req->frame.y_stride;
    jpg.c_stride = req->frame.c_stride;
    jpg.c_height = req->frame.c_height;

    frame.size = JPU_ALIGN(req->frame.size, 4096);
    if ((err = rt_device_control(jpu, JPU_ALLOC_BUFFER, &frame)) != RT_EOK)
    {
        rt_kprintf("allocate JPU frame buffer failed: %d\n", err);
        goto _out;
    }
    rt_memset(frame.virt_addr, 0, frame.size);

    req->stream_phys = stream.phys_addr;
    req->frame_phys = frame.phys_addr;
    req->stream_size = jpg.size;
    req->stream_capacity = stream.size;
    req->frame_capacity = frame.size;

    if ((err = rt_device_control(jpu, JPU_DECODE, req)) != RT_EOK)
    {
        rt_kprintf("JPU decode failed: %d, irq=0x%08x status=0x%08x errmb=0x%08x\n",
                err, req->irq_status, req->picture_status, req->error_mcu);
        goto _out;
    }

    if ((err = jpu_show_frame(fb_name, &jpg, frame.virt_addr)) != RT_EOK)
    {
        rt_kprintf("display on %s failed: %d\n", fb_name, err);
    }
    else
    {
        rt_kprintf("JPU decoded %s (%ux%u) on %s\n",
                path, jpg.width, jpg.height, fb_name);
    }

_out:
    if (req)
    {
        rt_free(req);
    }
    if (frame.virt_addr)
    {
        rt_device_control(jpu, JPU_FREE_BUFFER, &frame);
    }
    if (stream.virt_addr)
    {
        rt_device_control(jpu, JPU_FREE_BUFFER, &stream);
    }
    if (fd >= 0)
    {
        close(fd);
    }
    rt_device_close(jpu);
    return err;
}
MSH_CMD_EXPORT(jpu_show, decode a baseline JPEG with K1 JPU and display it);
#endif /* RT_USING_FINSH && RT_USING_DFS && RT_USING_GRAPHIC && RT_SOC_CHIP_MEDIA_JPU */
