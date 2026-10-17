/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_DFS) && defined(RT_USING_FINSH)

#include <finsh.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sunxi-jpegd.h>

#define F101_JPEGD_IO_SIZE          4096
#define F101_JPEGD_STREAM_ALIGN     1024

static rt_err_t f101_jpegd_read_exact(int fd, void *buffer, rt_size_t size)
{
    rt_uint8_t *data = buffer;

    while (size)
    {
        int length = read(fd, data, size);

        if (length <= 0)
        {
            return -RT_EIO;
        }

        data += length;
        size -= length;
    }

    return RT_EOK;
}

static rt_err_t f101_jpegd_read_to_dma(int fd, void *buffer, rt_size_t size)
{
    rt_uint8_t *bounce;
    rt_uint8_t *destination = buffer;
    rt_err_t err = RT_EOK;

    bounce = rt_malloc(F101_JPEGD_IO_SIZE);
    if (!bounce)
    {
        return -RT_ENOMEM;
    }

    while (size)
    {
        rt_size_t count = rt_min_t(rt_size_t, size, F101_JPEGD_IO_SIZE);

        err = f101_jpegd_read_exact(fd, bounce, count);
        if (err)
        {
            break;
        }

        rt_memcpy(destination, bounce, count);
        destination += count;
        size -= count;
    }

    rt_free(bounce);
    return err;
}

static rt_err_t f101_jpegd_write_all(int fd, const void *buffer,
        rt_size_t size)
{
    const rt_uint8_t *data = buffer;

    while (size)
    {
        int length = write(fd, data, size);

        if (length <= 0)
        {
            return -RT_EIO;
        }

        data += length;
        size -= length;
    }

    return RT_EOK;
}

static void f101_jpegd_free_buffer(rt_device_t device,
        struct sunxi_jpegd_buffer *buffer)
{
    if (buffer->virt_addr)
    {
        rt_device_control(device, SUNXI_JPEGD_CMD_FREE_BUFFER, buffer);
    }
}

#ifdef RT_USING_GRAPHIC
static rt_size_t f101_jpegd_mb32_offset(unsigned int x, unsigned int y,
        unsigned int stride)
{
    return ((rt_size_t)(y / 32) * (stride / 32) + x / 32) * 1024 +
            (y % 32) * 32 + x % 32;
}

static rt_uint8_t f101_jpegd_clip(int value)
{
    return value < 0 ? 0 : value > 255 ? 255 : value;
}

static rt_err_t f101_jpegd_display(const char *name,
        const struct sunxi_jpegd_decode *image)
{
    struct rt_device_graphic_info info = { 0 };
    struct rt_device_rect_info rect = { 0 };
    const rt_uint8_t *luma = image->output->virt_addr;
    const rt_uint8_t *chroma = luma + image->luma_size;
    rt_device_t fb = rt_device_find(name);
    rt_uint8_t *canvas = RT_NULL;
    rt_size_t size;
    unsigned int width, height, left, top, bytes, x, y;
    rt_err_t err;

    if (!fb)
    {
        rt_kprintf("framebuffer not found: %s\n", name);
        return -RT_ENOSYS;
    }
    if (image->format != SUNXI_JPEGD_FORMAT_MB32_420 ||
            !image->width || !image->height)
    {
        return -RT_EINVAL;
    }
    err = rt_device_open(fb, RT_DEVICE_OFLAG_RDWR);
    if (err)
    {
        return err;
    }
    err = rt_device_control(fb, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (err)
    {
        goto _out;
    }
    switch (info.pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        bytes = 2;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        bytes = 4;
        break;
    default:
        rt_kprintf("unsupported framebuffer format: %u\n", info.pixel_format);
        err = -RT_ENOSYS;
        goto _out;
    }
    if (!info.framebuffer || !info.width || !info.height ||
            info.bits_per_pixel != bytes * 8 || info.pitch < info.width * bytes ||
            info.height > (rt_size_t)-1 / info.pitch)
    {
        err = -RT_EINVAL;
        goto _out;
    }
    size = (rt_size_t)info.pitch * info.height;
    canvas = rt_calloc(1, size);
    if (!canvas)
    {
        err = -RT_ENOMEM;
        goto _out;
    }
    width = info.width;
    height = (rt_uint64_t)image->height * width / image->width;
    if (height > info.height)
    {
        height = info.height;
        width = (rt_uint64_t)image->width * height / image->height;
    }
    width = rt_max(width, 1U);
    height = rt_max(height, 1U);
    left = (info.width - width) / 2;
    top = (info.height - height) / 2;

    /* VE MB32 uses 32x32 byte tiles for Y and interleaved UV. */
    for (y = 0; y < height; ++y)
    {
        unsigned int sy = (rt_uint64_t)y * image->height / height;
        rt_uint8_t *row = canvas + (rt_size_t)(top + y) * info.pitch + left * bytes;

        for (x = 0; x < width; ++x)
        {
            unsigned int sx = (rt_uint64_t)x * image->width / width;
            rt_size_t uv = f101_jpegd_mb32_offset(sx & ~1U, sy / 2, image->stride);
            int yy = luma[f101_jpegd_mb32_offset(sx, sy, image->stride)];
            int u = chroma[uv] - 128;
            int v = chroma[uv + 1] - 128;
            rt_uint8_t r = f101_jpegd_clip(yy + ((359 * v) >> 8));
            rt_uint8_t g = f101_jpegd_clip(yy - ((88 * u + 183 * v) >> 8));
            rt_uint8_t b = f101_jpegd_clip(yy + ((454 * u) >> 8));

            if (bytes == 2)
            {
                rt_uint16_t pixel = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
                rt_memcpy(row + x * bytes, &pixel, sizeof(pixel));
            }
            else
            {
                rt_uint32_t pixel = info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888 ?
                        0xff000000U | ((rt_uint32_t)r << 16) | (g << 8) | b :
                        0xff000000U | ((rt_uint32_t)b << 16) | (g << 8) | r;
                rt_memcpy(row + x * bytes, &pixel, sizeof(pixel));
            }
        }
    }
    rt_memcpy(info.framebuffer, canvas, size);
    rect.width = info.width;
    rect.height = info.height;
    err = rt_device_control(fb, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
    if (!err)
    {
        rt_kprintf("JPEG %ux%u displayed on %s\n", image->width, image->height, name);
    }

_out:
    rt_free(canvas);
    rt_device_close(fb);
    return err;
}
#endif

static int f101_jpegd_run(int argc, char **argv, rt_bool_t display)
{
    struct sunxi_jpegd_buffer input = { 0 };
    struct sunxi_jpegd_buffer output = { 0 };
    struct sunxi_jpegd_info info = { 0 };
    struct sunxi_jpegd_decode request = { 0 };
    struct stat statbuf;
    rt_device_t device;
    rt_err_t err = -RT_ERROR;
    rt_size_t input_size;
    int input_fd = -1;
    int output_fd = -1;

    if ((!display && argc != 3) || (display && argc != 2 && argc != 3))
    {
        rt_kprintf(display ? "Usage: jpegshow <input.jpg> [fb0]\n" :
                "Usage: jpegd <input.jpg> <output.mb32>\n");
        return -RT_EINVAL;
    }

    device = rt_device_find("jpegd0");
    if (!device)
    {
        device = rt_device_find("jpegd");
    }
    if (!device)
    {
        rt_kprintf("jpegd device not found\n");
        return -RT_ENOSYS;
    }

    input_fd = open(argv[1], O_RDONLY, 0);
    if (input_fd < 0 || fstat(input_fd, &statbuf) || statbuf.st_size <= 0)
    {
        rt_kprintf("cannot read %s\n", argv[1]);
        err = -RT_EIO;
        goto _out;
    }

    input_size = statbuf.st_size;
    if (input_size > (rt_size_t)-1 - (F101_JPEGD_STREAM_ALIGN - 1))
    {
        err = -RT_EINVAL;
        goto _out;
    }

    input.size = RT_ALIGN(input_size, F101_JPEGD_STREAM_ALIGN);
    err = rt_device_control(device, SUNXI_JPEGD_CMD_ALLOC_BUFFER, &input);
    if (err)
    {
        goto _out;
    }
    err = f101_jpegd_read_to_dma(input_fd, input.virt_addr, input_size);
    if (err)
    {
        goto _out;
    }
    rt_memset((rt_uint8_t *)input.virt_addr + input_size, 0xff,
            input.size - input_size);

    info.input = &input;
    info.input_size = input_size;
    err = rt_device_control(device, SUNXI_JPEGD_CMD_GET_INFO, &info);
    if (err)
    {
        rt_kprintf("invalid or unsupported JPEG: %d\n", err);
        goto _out;
    }

    output.size = info.output_size;
    err = rt_device_control(device, SUNXI_JPEGD_CMD_ALLOC_BUFFER, &output);
    if (err)
    {
        goto _out;
    }

    request.input = &input;
    request.output = &output;
    request.input_size = input_size;
    request.timeout = rt_tick_from_millisecond(500);
    err = rt_device_control(device, SUNXI_JPEGD_CMD_DECODE, &request);
    if (err)
    {
        rt_kprintf("JPEG decode failed: %d\n", err);
        goto _out;
    }

#ifdef RT_USING_GRAPHIC
    if (display)
    {
        err = f101_jpegd_display(argc > 2 ? argv[2] : "fb0", &request);
        goto _out;
    }
#endif

    output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0);
    if (output_fd < 0)
    {
        rt_kprintf("cannot create %s\n", argv[2]);
        err = -RT_EIO;
        goto _out;
    }
    err = f101_jpegd_write_all(output_fd, output.virt_addr, output.size);
    if (err)
    {
        rt_kprintf("write %s failed\n", argv[2]);
        goto _out;
    }

    rt_kprintf("%ux%u JPEG decoded as MB32_420, stride %u, %u bytes\n",
            request.width, request.height, request.stride,
            (rt_uint32_t)output.size);

_out:
    if (output_fd >= 0)
    {
        close(output_fd);
    }
    if (input_fd >= 0)
    {
        close(input_fd);
    }
    f101_jpegd_free_buffer(device, &output);
    f101_jpegd_free_buffer(device, &input);

    return err;
}
static int jpegd(int argc, char **argv)
{
    return f101_jpegd_run(argc, argv, RT_FALSE);
}
MSH_CMD_EXPORT(jpegd, decode baseline JPEG to MB32_420: jpegd input.jpg output.mb32);

#ifdef RT_USING_GRAPHIC
static int jpegshow(int argc, char **argv)
{
    return f101_jpegd_run(argc, argv, RT_TRUE);
}
MSH_CMD_EXPORT(jpegshow, display baseline JPEG: jpegshow input.jpg [fb0]);
#endif

#endif /* RT_USING_DFS && RT_USING_FINSH */
