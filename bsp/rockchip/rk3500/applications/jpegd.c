/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#include <jpegd.h>

#if defined(RT_USING_FINSH) && defined(RT_USING_GRAPHIC) && defined(RT_ROCKCHIP_JPEG_DEC)
#include <finsh.h>
#include <fcntl.h>
#include <unistd.h>

#define JPEGD_TABLE_SIZE       1280
#define JPEGD_MINCODE_OFFSET   384
#define JPEGD_VALUE_OFFSET     704
#define JPEGD_ALIGN(x, a)      (((x) + (a) - 1) & ~((a) - 1))

#define JPEGD_SCALE_HALF       1
#define JPEGD_OUTPUT_RGB888    1

#define JPEGD_INT_TIMEOUT      RT_BIT(2)
#define JPEGD_INT_BUF_EMPTY    RT_BIT(3)
#define JPEGD_SYS_SCALE(x)     ((x) << 12)
#define JPEGD_SYS_FILL_DOWN    RT_BIT(24)
#define JPEGD_SYS_FILL_RIGHT   RT_BIT(25)
#define JPEGD_SYS_OUTPUT(x)    ((x) << 27)
#define JPEGD_SYS_FULL_RANGE   RT_BIT(31)

#define JPEGD_TABLE_QUANT      9
#define JPEGD_TABLE_MINCODE    10
#define JPEGD_TABLE_VALUE      11
#define JPEGD_STREAM_BASE      12
#define JPEGD_OUTPUT_BASE      13

struct jpegd_huff
{
    rt_uint8_t bits[16];
    rt_uint8_t vals[162];
    rt_uint16_t count;
};

struct jpegd_image
{
    rt_uint8_t *data;
    rt_size_t size;
    rt_uint16_t quant[4][64];
    struct jpegd_huff dc[2];
    struct jpegd_huff ac[2];
    rt_uint8_t comp_id[3];
    rt_uint8_t h[3], v[3], qsel[3], dcsel[3], acsel[3];
    rt_uint8_t components, qtables, htable_mask, mode, fill_right, fill_bottom;
    rt_uint16_t width, height, restart;
    rt_size_t scan_offset;
};

static const rt_uint8_t zigzag[64] =
{
     0,  1,  8, 16,  9,  2,  3, 10,
    17, 24, 32, 25, 18, 11,  4,  5,
    12, 19, 26, 33, 40, 48, 41, 34,
    27, 20, 13,  6,  7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46,
    53, 60, 61, 54, 47, 55, 62, 63,
};

/* JPEG stores all multi-byte fields in big-endian order. */

static rt_uint16_t get_be16(const rt_uint8_t *p)
{
    return ((rt_uint16_t)p[0] << 8) | p[1];
}

static rt_err_t parse_dqt(struct jpegd_image *jpg, const rt_uint8_t *p, rt_size_t len)
{
    while (len)
    {
        rt_uint8_t precision, id;
        int i;

        precision = *p >> 4;
        id = *p++ & 0xf;
        --len;
        if (precision > 1 || id > 3 || len < (rt_size_t)(64 << precision))
        {
            return -RT_EINVAL;
        }

        for (i = 0; i < 64; ++i)
        {
            jpg->quant[id][i] = precision ? get_be16(p + i * 2) : p[i];
        }
        p += 64 << precision;
        len -= 64 << precision;
        ++jpg->qtables;
    }
    return RT_EOK;
}

/* Parse the baseline Huffman tables used later to build the hardware tables. */

static rt_err_t parse_dht(struct jpegd_image *jpg, const rt_uint8_t *p, rt_size_t len)
{
    while (len)
    {
        struct jpegd_huff *table;
        rt_uint8_t type, id;
        rt_uint16_t count = 0;
        int i;

        if (len < 17)
        {
            return -RT_EINVAL;
        }

        type = *p >> 4;
        id = *p++ & 0xf;
        --len;
        if (type > 1 || id > 1)
        {
            return -RT_ENOSYS;
        }

        table = type ? &jpg->ac[id] : &jpg->dc[id];
        for (i = 0; i < 16; ++i)
        {
            count += table->bits[i] = p[i];
        }

        p += 16;
        len -= 16;
        if (count > (type ? 162 : 12) || len < count)
        {
            return -RT_EINVAL;
        }

        rt_memcpy(table->vals, p, count);
        table->count = count;
        jpg->htable_mask |= 1U << (id * 2 + type);
        p += count;
        len -= count;
    }
    return RT_EOK;
}

static rt_err_t parse_sof(struct jpegd_image *jpg, const rt_uint8_t *p, rt_size_t len)
{
    int i;

    if (len < 6 || p[0] != 8 || (p[5] != 1 && p[5] != 3) || len != 6U + p[5] * 3U)
    {
        return -RT_ENOSYS;
    }

    jpg->height = get_be16(p + 1);
    jpg->width = get_be16(p + 3);
    jpg->components = p[5];
    if (!jpg->width || !jpg->height)
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < jpg->components; ++i)
    {
        jpg->comp_id[i] = p[6 + i * 3];
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
        jpg->mode = 0;
    }
    else if (jpg->h[0] == 2 && jpg->v[0] == 2)
    {
        jpg->mode = 2;
    }
    else if (jpg->h[0] == 2 && jpg->v[0] == 1)
    {
        jpg->mode = 3;
    }
    else if (jpg->h[0] == 1 && jpg->v[0] == 1)
    {
        jpg->mode = 5;
    }
    else if (jpg->h[0] == 1 && jpg->v[0] == 2)
    {
        jpg->mode = 4;
    }
    else if (jpg->h[0] == 4 && jpg->v[0] == 1)
    {
        jpg->mode = 1;
    }
    else
    {
        return -RT_ENOSYS;
    }

    if (jpg->components == 3 &&
        (jpg->h[1] != 1 || jpg->v[1] != 1 || jpg->h[2] != 1 || jpg->v[2] != 1))
    {
        return -RT_ENOSYS;
    }

    if ((jpg->mode == 3 || jpg->mode == 1 || jpg->mode == 5) &&
        (jpg->height & 15) && (jpg->height & 15) <= 8)
    {
        jpg->fill_bottom = 1;
    }

    if ((jpg->mode == 4 || jpg->mode == 5 || jpg->mode == 0) &&
        (jpg->width & 15) && (jpg->width & 15) <= 8)
    {
        jpg->fill_right = 1;
    }

    return RT_EOK;
}

/* The RKV JPEG decoder accepts a single baseline sequential scan. */

static rt_err_t parse_sos(struct jpegd_image *jpg, const rt_uint8_t *p, rt_size_t len)
{
    int i, j;

    if (len < 4 || p[0] != jpg->components || len != 4U + p[0] * 2U)
    {
        return -RT_ENOSYS;
    }

    for (i = 0; i < p[0]; ++i)
    {
        for (j = 0; j < jpg->components && jpg->comp_id[j] != p[1 + i * 2]; ++j)
        {
        }

        if (j == jpg->components || (p[2 + i * 2] >> 4) > 1 || (p[2 + i * 2] & 0xf) > 1)
        {
            return -RT_ENOSYS;
        }

        jpg->dcsel[i] = p[2 + i * 2] >> 4;
        jpg->acsel[i] = p[2 + i * 2] & 0xf;
    }
    if (p[len - 3] != 0 || p[len - 2] != 63 || p[len - 1] != 0)
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t jpegd_parse(struct jpegd_image *jpg)
{
    rt_size_t pos = 2;
    rt_bool_t sof = RT_FALSE;

    if (jpg->size < 4 || get_be16(jpg->data) != 0xffd8)
    {
        return -RT_EINVAL;
    }

    while (pos + 1 < jpg->size)
    {
        rt_uint8_t marker;
        rt_uint16_t section_len;
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

        section_len = get_be16(jpg->data + pos);
        if (section_len < 2 || pos + section_len > jpg->size)
        {
            return -RT_EINVAL;
        }

        section = jpg->data + pos + 2;
        switch (marker)
        {
        case 0xc0:
            err = parse_sof(jpg, section, section_len - 2);
            sof = err == RT_EOK;
            break;
        case 0xc4:
            err = parse_dht(jpg, section, section_len - 2);
            break;
        case 0xdb:
            err = parse_dqt(jpg, section, section_len - 2);
            break;
        case 0xdd:
            if (section_len != 4)
            {
                err = -RT_EINVAL;
            }
            else
            {
                jpg->restart = get_be16(section);
            }
            break;
        case 0xda:
            if (!sof)
            {
                return -RT_EINVAL;
            }
            err = parse_sos(jpg, section, section_len - 2);
            jpg->scan_offset = pos + section_len;
            return err;
        default:
            if (marker >= 0xc1 && marker <= 0xcf && marker != 0xc4 && marker != 0xc8 && marker != 0xcc)
            {
                return -RT_ENOSYS;
            }
            break;
        }
        if (err)
        {
            return err;
        }

        pos += section_len;
    }
    return -RT_EINVAL;
}

/* Convert JPEG canonical Huffman tables into the RKV decoder table layout. */

static void make_huffman_table(rt_uint8_t *table_mem, struct jpegd_image *jpg)
{
    rt_uint16_t *minp = (rt_uint16_t *)(table_mem + JPEGD_MINCODE_OFFSET);
    rt_uint8_t *valp = table_mem + JPEGD_VALUE_OFFSET;
    int component, type, i;

    for (component = 0; component < jpg->components; ++component)
    {
        for (type = 0; type < 2; ++type)
        {
            struct jpegd_huff *h = type ? &jpg->ac[jpg->acsel[component]] :
                                            &jpg->dc[jpg->dcsel[component]];
            rt_uint16_t mincode[16], addr[16];
            rt_uint16_t code = 0, acc = 0;

            for (i = 0; i < 16; ++i)
            {
                mincode[i] = code;
                code += h->bits[i];
                acc += h->bits[i];
                addr[i] = acc;
                code <<= 1;
            }
            mincode[0] = mincode[15] + (h->bits[15] ? h->bits[15] - 1 : 0);
            for (i = 0; i < 16; ++i)
            {
                *minp++ = mincode[i];
            }
            for (i = 0; i < 8; ++i)
            {
                *minp++ = addr[i * 2] | (addr[i * 2 + 1] << 8);
            }
        }
        rt_memcpy(valp, jpg->dc[jpg->dcsel[component]].vals, 12);
        rt_memcpy(valp + 16, jpg->ac[jpg->acsel[component]].vals, 162);
        valp += 192;
    }
}

static void make_quant_table(rt_uint8_t *table_mem, struct jpegd_image *jpg)
{
    rt_uint16_t *q = (rt_uint16_t *)table_mem;
    int c, i;

    for (c = 0; c < jpg->components; ++c)
    {
        for (i = 0; i < 64; ++i)
        {
            q[c * 64 + zigzag[i]] = jpg->quant[jpg->qsel[c]][i];
        }
    }
}

/* Convert the decoder's RGB888 output to the active framebuffer format. */

static rt_err_t pixel_convert(rt_uint8_t fmt, const rt_uint8_t *rgb, void *dst)
{
    rt_uint8_t r = rgb[0], g = rgb[1], b = rgb[2];

    switch (fmt)
    {
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        *(rt_uint16_t *)dst = (r >> 3) << 11 | (g >> 2) << 5 | b >> 3;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_BGR565:
        *(rt_uint16_t *)dst = (b >> 3) << 11 | (g >> 2) << 5 | r >> 3;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_RGB888:
        ((rt_uint8_t *)dst)[0] = r;
        ((rt_uint8_t *)dst)[1] = g;
        ((rt_uint8_t *)dst)[2] = b;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_BGR888:
        ((rt_uint8_t *)dst)[0] = b;
        ((rt_uint8_t *)dst)[1] = g;
        ((rt_uint8_t *)dst)[2] = r;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        *(rt_uint32_t *)dst = 0xff000000U | r << 16 | g << 8 | b;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        *(rt_uint32_t *)dst = 0xff000000U | b << 16 | g << 8 | r;
        break;
    default:
        return -RT_ENOSYS;
    }
    return RT_EOK;
}

static rt_err_t show_rgb(rt_uint8_t *rgb, int width, int height, int rgb_stride,
                         const char *fb_name)
{
    struct rt_device_graphic_info info;
    struct rt_device_rect_info rect;
    rt_device_t fb = rt_device_find(fb_name);
    struct rt_graphic_device *graphic;
    rt_bool_t restore_auto_update;
    rt_uint8_t *screen, *dst, *src;
    int x0, y0, copy_w, copy_h, x, y, bpp;
    rt_err_t err;

    if (!fb)
    {
        return -RT_EINVAL;
    }

    graphic = rt_container_of(fb, struct rt_graphic_device, parent);
    restore_auto_update = graphic->update_timer != RT_NULL;
    if ((err = rt_device_open(fb, 0)))
    {
        return err;
    }
    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_GET_INFO, &info)))
    {
        goto _out;
    }
    if (!info.framebuffer || !(bpp = info.bits_per_pixel / 8))
    {
        err = -RT_EINVAL;
        goto _out;
    }
    if ((err = rt_device_control(fb, RTGRAPHIC_CTRL_POWERON, RT_NULL)))
    {
        goto _out;
    }

    screen = rt_malloc((rt_size_t)info.pitch * info.height);
    if (!screen)
    {
        err = -RT_ENOMEM;
        goto _out;
    }
    if (restore_auto_update)
    {
        rt_graphic_device_update_auto(graphic, 0);
    }

    rt_memset(screen, 0, (rt_size_t)info.pitch * info.height);
    copy_w = rt_min_t(int, width, info.width);
    copy_h = rt_min_t(int, height, info.height);
    x0 = (info.width - copy_w) / 2;
    y0 = (info.height - copy_h) / 2;
    src = rgb + (height - copy_h) / 2 * rgb_stride +
          (width - copy_w) / 2 * 3;
    for (y = 0; y < copy_h; ++y)
    {
        dst = screen + (y0 + y) * info.pitch + x0 * bpp;
        for (x = 0; x < copy_w; ++x)
        {
            if ((err = pixel_convert(info.pixel_format, src + x * 3, dst + x * bpp)))
            {
                break;
            }
        }
        if (err)
        {
            break;
        }
        src += rgb_stride;
    }
    if (!err)
    {
        rt_memcpy(info.framebuffer, screen, (rt_size_t)info.pitch * info.height);
        rect.x = 0;
        rect.y = 0;
        rect.width = info.width;
        rect.height = info.height;
        rt_device_control(fb, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
        rt_device_control(fb, RTGRAPHIC_CTRL_WAIT_VSYNC, RT_NULL);
    }
    rt_free(screen);
    if (restore_auto_update)
    {
        rt_graphic_device_update_auto(graphic, RT_GRAPHIC_UPDATE_MS);
    }

_out:
    rt_device_close(fb);
    return err;
}

/* Decode one baseline JPEG with jpegd0 and display the half-sized result. */

static int jpegd_show(int argc, char **argv)
{
    const char *path = argc > 1 ? argv[1] : "/arm-boot.jpg";
    const char *fb_name = argc > 2 ? argv[2] : "fb0";
    struct jpegd_image jpg = { 0 };
    struct jpegd_req req = { 0 };
    rt_device_t jpegd = rt_device_find("jpegd0");
    rt_uint8_t *stream = RT_NULL, *tables = RT_NULL, *output = RT_NULL;
    rt_ubase_t stream_dma = 0, tables_dma = 0, output_dma = 0;
    rt_size_t stream_size = 0, output_size = 0;
    rt_uint32_t stride, out_height, display_width, display_height;
    rt_uint32_t table_sel, htable_sel, htable_mincode_len;
    rt_size_t hw_scan_offset, hw_stream_size;
    off_t file_size;
    int fd = -1;
    rt_err_t err = -RT_ERROR;

    if (!jpegd)
    {
        rt_kprintf("jpegd0 not found\n");
        return -RT_EINVAL;
    }

    fd = open(path, O_RDONLY, 0);
    if (fd < 0)
    {
        rt_kprintf("open %s failed\n", path);
        return -RT_EIO;
    }

    file_size = lseek(fd, 0, SEEK_END);
    if (file_size <= 0 || lseek(fd, 0, SEEK_SET) < 0)
    {
        err = -RT_EIO;
        goto _out;
    }

    jpg.size = file_size;
    stream_size = JPEGD_ALIGN(jpg.size, 16);
    stream = rt_dma_alloc_coherent(jpegd, stream_size, &stream_dma);
    if (!stream)
    {
        err = -RT_ENOMEM;
        goto _out;
    }
    if (read(fd, stream, jpg.size) != (int)jpg.size)
    {
        err = -RT_EIO;
        goto _out;
    }

    rt_memset(stream + jpg.size, 0xff, stream_size - jpg.size);
    jpg.data = stream;
    if ((err = jpegd_parse(&jpg)))
    {
        rt_kprintf("unsupported/invalid baseline JPEG: %d\n", err);
        goto _out;
    }
    if (!jpg.htable_mask)
    {
        rt_kprintf("JPEG without DHT is not supported by this example\n");
        err = -RT_ENOSYS;
        goto _out;
    }

    /* The output is RGB888 with the JPEGD half-scale mode enabled. */
    tables = rt_dma_alloc_coherent(jpegd, JPEGD_TABLE_SIZE, &tables_dma);
    display_width = (jpg.width + 1) / 2;
    display_height = (jpg.height + 1) / 2;
    stride = JPEGD_ALIGN(JPEGD_ALIGN(jpg.width, 16) / 2, 16);
    out_height = JPEGD_ALIGN(jpg.height, jpg.fill_bottom ? 16 : 8) / 2;
    output_size = (rt_size_t)stride * out_height * 3;
    output = rt_dma_alloc_coherent(jpegd, output_size, &output_dma);
    if (!tables || !output)
    {
        err = -RT_ENOMEM;
        goto _out;
    }

    rt_memset(tables, 0, JPEGD_TABLE_SIZE);
    rt_memset(output, 0, output_size);
    make_quant_table(tables, &jpg);
    make_huffman_table(tables, &jpg);
    table_sel = jpg.components == 1 ? 1 : (jpg.qtables > 1 ? 3 : 2);
    htable_sel = jpg.components == 1 ? 1 : (jpg.htable_mask > 0x0f ? 3 : 2);
    htable_mincode_len = htable_sel == 2 ? (jpg.components - 1) * 6 - 1 :
                                             jpg.components * 6 - 1;
    hw_scan_offset = jpg.scan_offset & ~(rt_size_t)15;
    hw_stream_size = JPEGD_ALIGN(jpg.size - hw_scan_offset, 16);
    req.reg[1] = JPEGD_INT_TIMEOUT | JPEGD_INT_BUF_EMPTY;
    req.reg[2] = JPEGD_SYS_SCALE(JPEGD_SCALE_HALF) |
                 JPEGD_SYS_OUTPUT(JPEGD_OUTPUT_RGB888) |
                 (jpg.fill_right ? JPEGD_SYS_FILL_RIGHT : 0) |
                 (jpg.fill_bottom ? JPEGD_SYS_FILL_DOWN : 0) |
                 JPEGD_SYS_FULL_RANGE;
    req.reg[3] = (jpg.width - 1) | ((rt_uint32_t)(jpg.height - 1) << 16);
    req.reg[4] = jpg.mode | (table_sel << 8) | (htable_sel << 12);
    if (jpg.restart)
    {
        req.reg[4] |= RT_BIT(15) | ((rt_uint32_t)(jpg.restart - 1) << 16);
    }
    req.reg[5] = (stride * 3 / 16);
    req.reg[6] = (stride * 3 / 16 * out_height) << 4;
    req.reg[7] = (table_sel * 8 - 1) | (htable_mincode_len << 8) |
                 ((htable_sel * 12 - 1) << 16);
    req.reg[8] = (jpg.scan_offset & 15) |
                 ((rt_uint32_t)((hw_stream_size - 1) / 16) << 4);
    req.reg[JPEGD_TABLE_QUANT] = (rt_uint32_t)tables_dma;
    req.reg[JPEGD_TABLE_MINCODE] = (rt_uint32_t)(tables_dma + JPEGD_MINCODE_OFFSET);
    req.reg[JPEGD_TABLE_VALUE] = (rt_uint32_t)(tables_dma + JPEGD_VALUE_OFFSET);
    req.reg[JPEGD_STREAM_BASE] = (rt_uint32_t)(stream_dma + hw_scan_offset);
    req.reg[JPEGD_OUTPUT_BASE] = (rt_uint32_t)output_dma;
    req.reg[14] = 1 | (2 << 5) | (2 << 7);
    req.reg[16] = 0xff;
    req.reg[30] = 3 | (1 << 3) | (0xa << 4);
    if ((rt_ubase_t)(rt_uint32_t)stream_dma != stream_dma ||
        (rt_ubase_t)(rt_uint32_t)tables_dma != tables_dma ||
        (rt_ubase_t)(rt_uint32_t)output_dma != output_dma)
    {
        rt_kprintf("jpegd DMA address exceeds 32 bits\n");
        err = -RT_EINVAL;
        goto _out;
    }
    if ((err = rt_device_control(jpegd, JPEGD_RUN, &req)))
    {
        rt_kprintf("decode failed: %d, irq=0x%08x\n", err, req.irq_status);
        goto _out;
    }

    err = show_rgb(output, display_width, display_height, stride * 3, fb_name);
    if (!err)
    {
        rt_kprintf("displayed %s (%ux%u -> %ux%u) on %s\n", path,
                   jpg.width, jpg.height, display_width, display_height, fb_name);
    }

_out:
    if (output)
    {
        rt_dma_free_coherent(jpegd, output_size, output, output_dma);
    }
    if (tables)
    {
        rt_dma_free_coherent(jpegd, JPEGD_TABLE_SIZE, tables, tables_dma);
    }
    if (stream)
    {
        rt_dma_free_coherent(jpegd, stream_size, stream, stream_dma);
    }
    if (fd >= 0)
    {
        close(fd);
    }

    return err;
}
MSH_CMD_EXPORT(jpegd_show, decode and display once: jpegd_show [/arm-boot.jpg] [fb0]);
#endif /* RT_USING_FINSH && RT_USING_GRAPHIC && RT_ROCKCHIP_JPEG_DEC */
