/*
 * MJPEG AVI player for F101.
 *
 * AVI is only a container.  F101's currently enabled VE decoder handles
 * baseline JPEG, so this player intentionally accepts MJPEG AVI video and
 * rejects H.264, MPEG-4, Xvid and other AVI codecs instead of decoding them
 * on the CPU by accident.  Audio tracks are skipped.
 */

#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_DFS) && defined(RT_USING_FINSH) && \
    defined(RT_USING_GRAPHIC) && defined(RT_SOC_SUNXI_JPEG_DEC) && \
    defined(RT_SOC_SUNXI_G2D)

#include <finsh.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sunxi-g2d.h>
#include <sunxi-jpegd.h>

#define AVI_STREAM_ALIGN        1024U
#define AVI_IO_SIZE             4096U
#define AVI_MAX_DIMENSION        2048U
#define AVI_MAX_RECURSION           8U
#define AVI_FOURCC(a, b, c, d) \
    ((rt_uint32_t)(a) | ((rt_uint32_t)(b) << 8) | \
     ((rt_uint32_t)(c) << 16) | ((rt_uint32_t)(d) << 24))

#define AVI_RIFF                AVI_FOURCC('R', 'I', 'F', 'F')
#define AVI_AVI                 AVI_FOURCC('A', 'V', 'I', ' ')
#define AVI_LIST                AVI_FOURCC('L', 'I', 'S', 'T')
#define AVI_HDRL                AVI_FOURCC('h', 'd', 'r', 'l')
#define AVI_STRL                AVI_FOURCC('s', 't', 'r', 'l')
#define AVI_MOVI                AVI_FOURCC('m', 'o', 'v', 'i')
#define AVI_AVIH                AVI_FOURCC('a', 'v', 'i', 'h')
#define AVI_STRH                AVI_FOURCC('s', 't', 'r', 'h')
#define AVI_STRF                AVI_FOURCC('s', 't', 'r', 'f')
#define AVI_VIDS                AVI_FOURCC('v', 'i', 'd', 's')
#define AVI_MJPG                AVI_FOURCC('M', 'J', 'P', 'G')
#define AVI_JPEG                AVI_FOURCC('J', 'P', 'E', 'G')

struct avi_movie
{
    int fd;
    off_t file_size;
    off_t movi_start;
    off_t movi_end;
    rt_uint32_t stream_index;
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t microseconds_per_frame;
    rt_uint32_t declared_frames;
};

struct avi_frame_info
{
    off_t offset;
    rt_size_t size;
};

struct avi_scan
{
    const struct avi_movie *movie;
    rt_size_t largest_frame;
    rt_uint32_t frames;
};

struct avi_player
{
    const struct avi_movie *movie;
    rt_device_t jpegd;
    rt_device_t g2d;
    rt_device_t framebuffer;
    struct rt_device_graphic_info fb_info;
    struct sunxi_jpegd_buffer bitstream;
    struct sunxi_jpegd_buffer decoded;
    struct sunxi_g2d_buffer nv12;
    struct sunxi_g2d_buffer framebuffer_buffer;
    rt_uint32_t source_stride;
    rt_uint32_t source_luma_size;
    rt_uint32_t display_x;
    rt_uint32_t display_y;
    rt_uint32_t display_width;
    rt_uint32_t display_height;
    rt_uint32_t frames;
    rt_uint32_t late_frames;
    rt_bool_t pace;
    rt_tick_t ve_ticks;
    rt_tick_t detile_ticks;
    rt_tick_t g2d_ticks;
    rt_tick_t start_tick;
    rt_bool_t framebuffer_imported;
};

static rt_uint16_t avi_le16(const rt_uint8_t *data)
{
    return (rt_uint16_t)data[0] | ((rt_uint16_t)data[1] << 8);
}

static rt_uint32_t avi_le32(const rt_uint8_t *data)
{
    return (rt_uint32_t)data[0] | ((rt_uint32_t)data[1] << 8) |
            ((rt_uint32_t)data[2] << 16) | ((rt_uint32_t)data[3] << 24);
}

static rt_err_t avi_read_at(int fd, off_t offset, void *data, rt_size_t size)
{
    rt_uint8_t *position = data;

    if (lseek(fd, offset, SEEK_SET) != offset)
    {
        return -RT_EIO;
    }
    while (size)
    {
        int count = read(fd, position, size);

        if (count <= 0)
        {
            return -RT_EIO;
        }
        position += count;
        size -= count;
    }
    return RT_EOK;
}

static rt_err_t avi_read_to_dma(int fd, off_t offset, void *destination,
        rt_size_t size)
{
    rt_uint8_t *bounce;
    rt_uint8_t *output = destination;
    rt_err_t err = RT_EOK;

    bounce = rt_malloc(AVI_IO_SIZE);
    if (!bounce)
    {
        return -RT_ENOMEM;
    }
    if (lseek(fd, offset, SEEK_SET) != offset)
    {
        err = -RT_EIO;
        goto out;
    }
    while (size)
    {
        rt_size_t length = rt_min_t(rt_size_t, size, AVI_IO_SIZE);
        int count = read(fd, bounce, length);

        if (count != (int)length)
        {
            err = -RT_EIO;
            break;
        }
        rt_memcpy(output, bounce, length);
        output += length;
        size -= length;
    }
out:
    rt_free(bounce);
    return err;
}

static rt_bool_t avi_chunk_is_video(rt_uint32_t id, rt_uint32_t stream)
{
    rt_uint8_t first = id & 0xff;
    rt_uint8_t second = (id >> 8) & 0xff;
    rt_uint8_t kind = (id >> 16) & 0xff;

    return first == '0' + stream / 10U && second == '0' + stream % 10U &&
            (kind == 'd' || kind == 'D');
}

static rt_err_t avi_parse_strl(struct avi_movie *movie, off_t start,
        off_t end, rt_uint32_t index, rt_bool_t *found)
{
    rt_uint8_t strh[56] = { 0 };
    rt_uint8_t strf[40] = { 0 };
    rt_bool_t have_strh = RT_FALSE;
    rt_bool_t have_strf = RT_FALSE;
    off_t position = start;

    while (position + 8 <= end)
    {
        rt_uint8_t header[8];
        rt_uint32_t id;
        rt_uint32_t size;
        off_t data;
        off_t next;

        if (avi_read_at(movie->fd, position, header, sizeof(header)))
        {
            return -RT_EIO;
        }
        id = avi_le32(header);
        size = avi_le32(header + 4);
        data = position + 8;
        next = data + size + (size & 1U);
        if (next < data || next > end)
        {
            return -RT_EINVAL;
        }
        if (id == AVI_STRH && size >= sizeof(strh))
        {
            if (avi_read_at(movie->fd, data, strh, sizeof(strh)))
            {
                return -RT_EIO;
            }
            have_strh = RT_TRUE;
        }
        else if (id == AVI_STRF && size >= sizeof(strf))
        {
            if (avi_read_at(movie->fd, data, strf, sizeof(strf)))
            {
                return -RT_EIO;
            }
            have_strf = RT_TRUE;
        }
        position = next;
    }

    if (!have_strh || avi_le32(strh) != AVI_VIDS)
    {
        return RT_EOK;
    }
    if (avi_le32(strh + 4) != AVI_MJPG && avi_le32(strh + 4) != AVI_JPEG &&
            (!have_strf || (avi_le32(strf + 16) != AVI_MJPG &&
                    avi_le32(strf + 16) != AVI_JPEG)))
    {
        return RT_EOK;
    }
    if (*found || !have_strf)
    {
        return *found ? RT_EOK : -RT_ENOSYS;
    }

    movie->width = avi_le32(strf + 4);
    movie->height = avi_le32(strf + 8);
    if ((rt_int32_t)movie->height < 0)
    {
        movie->height = -(rt_int32_t)movie->height;
    }
    if (!movie->width || !movie->height || movie->width > AVI_MAX_DIMENSION ||
            movie->height > AVI_MAX_DIMENSION || (movie->width & 1U) ||
            (movie->height & 1U))
    {
        return -RT_ENOSYS;
    }
    movie->stream_index = index;
    if (avi_le32(strh + 20) && avi_le32(strh + 24))
    {
        movie->microseconds_per_frame = (rt_uint64_t)avi_le32(strh + 20) *
                1000000U / avi_le32(strh + 24);
    }
    movie->declared_frames = avi_le32(strh + 32);
    *found = RT_TRUE;
    return RT_EOK;
}

static rt_err_t avi_parse_hdrl(struct avi_movie *movie, off_t start, off_t end)
{
    off_t position = start;
    rt_uint32_t stream_index = 0;
    rt_bool_t found = RT_FALSE;

    while (position + 12 <= end)
    {
        rt_uint8_t header[12];
        rt_uint32_t id;
        rt_uint32_t size;
        off_t data;
        off_t next;
        rt_err_t err;

        if (avi_read_at(movie->fd, position, header, sizeof(header)))
        {
            return -RT_EIO;
        }
        id = avi_le32(header);
        size = avi_le32(header + 4);
        data = position + 8;
        next = data + size + (size & 1U);
        if (next < data || next > end)
        {
            return -RT_EINVAL;
        }
        if (id == AVI_AVIH && size >= 4)
        {
            movie->microseconds_per_frame = avi_le32(header + 8);
        }
        else if (id == AVI_LIST && size >= 4 && avi_le32(header + 8) == AVI_STRL)
        {
            err = avi_parse_strl(movie, data + 4, data + size, stream_index,
                    &found);
            if (err)
            {
                return err;
            }
            ++stream_index;
        }
        position = next;
    }
    return found ? RT_EOK : -RT_ENOSYS;
}

static rt_err_t avi_open(const char *path, struct avi_movie *movie)
{
    struct stat statbuf;
    rt_uint8_t riff[12];
    off_t position;
    off_t end;
    rt_bool_t have_hdrl = RT_FALSE;

    rt_memset(movie, 0, sizeof(*movie));
    movie->fd = open(path, O_RDONLY, 0);
    if (movie->fd < 0 || fstat(movie->fd, &statbuf) || statbuf.st_size < 12)
    {
        if (movie->fd >= 0)
        {
            close(movie->fd);
        }
        return -RT_EIO;
    }
    movie->file_size = statbuf.st_size;
    if (avi_read_at(movie->fd, 0, riff, sizeof(riff)) ||
            avi_le32(riff) != AVI_RIFF || avi_le32(riff + 8) != AVI_AVI)
    {
        close(movie->fd);
        return -RT_EINVAL;
    }
    end = rt_min_t(off_t, movie->file_size, (off_t)avi_le32(riff + 4) + 8);
    position = 12;
    while (position + 12 <= end)
    {
        rt_uint8_t header[12];
        rt_uint32_t id;
        rt_uint32_t size;
        off_t data;
        off_t next;
        rt_err_t err;

        if (avi_read_at(movie->fd, position, header, sizeof(header)))
        {
            goto malformed;
        }
        id = avi_le32(header);
        size = avi_le32(header + 4);
        data = position + 8;
        next = data + size + (size & 1U);
        if (next < data || next > end)
        {
            goto malformed;
        }
        if (id == AVI_LIST && size >= 4 && avi_le32(header + 8) == AVI_HDRL)
        {
            err = avi_parse_hdrl(movie, data + 4, data + size);
            if (err)
            {
                close(movie->fd);
                return err;
            }
            have_hdrl = RT_TRUE;
        }
        else if (id == AVI_LIST && size >= 4 && avi_le32(header + 8) == AVI_MOVI)
        {
            movie->movi_start = data + 4;
            movie->movi_end = data + size;
        }
        position = next;
    }
    if (!have_hdrl || !movie->movi_start || movie->movi_start >= movie->movi_end)
    {
        goto malformed;
    }
    if (!movie->microseconds_per_frame)
    {
        movie->microseconds_per_frame = 33333U;
    }
    return RT_EOK;

malformed:
    close(movie->fd);
    return -RT_EINVAL;
}

typedef rt_err_t (*avi_frame_callback_t)(const struct avi_frame_info *frame,
        void *context);

static rt_err_t avi_walk_frames(const struct avi_movie *movie, off_t start,
        off_t end, unsigned int level, avi_frame_callback_t callback,
        void *context)
{
    off_t position = start;

    if (level > AVI_MAX_RECURSION)
    {
        return -RT_EINVAL;
    }
    while (position + 8 <= end)
    {
        rt_uint8_t header[12] = { 0 };
        rt_uint32_t id;
        rt_uint32_t size;
        off_t data;
        off_t next;
        rt_err_t err;

        if (avi_read_at(movie->fd, position, header, sizeof(header)))
        {
            return -RT_EIO;
        }
        id = avi_le32(header);
        size = avi_le32(header + 4);
        data = position + 8;
        next = data + size + (size & 1U);
        if (next < data || next > end)
        {
            return -RT_EINVAL;
        }
        if (id == AVI_LIST && size >= 4)
        {
            err = avi_walk_frames(movie, data + 4, data + size, level + 1,
                    callback, context);
        }
        else if (avi_chunk_is_video(id, movie->stream_index))
        {
            struct avi_frame_info frame = { data, size };
            err = callback(&frame, context);
        }
        else
        {
            err = RT_EOK;
        }
        if (err)
        {
            return err;
        }
        position = next;
    }
    return RT_EOK;
}

static rt_err_t avi_scan_frame(const struct avi_frame_info *frame, void *context)
{
    struct avi_scan *scan = context;

    if (!frame->size)
    {
        return -RT_EINVAL;
    }
    scan->largest_frame = rt_max(scan->largest_frame, frame->size);
    ++scan->frames;
    return RT_EOK;
}

static rt_size_t avi_mb32_offset(rt_uint32_t x, rt_uint32_t y,
        rt_uint32_t stride)
{
    return ((rt_size_t)(y / 32U) * (stride / 32U) + x / 32U) * 1024U +
            (y % 32U) * 32U + x % 32U;
}

static rt_err_t avi_detile_nv12(struct avi_player *player,
        const struct sunxi_jpegd_decode *decoded)
{
    const rt_uint8_t *luma = decoded->output->virt_addr;
    const rt_uint8_t *chroma = luma + decoded->luma_size;
    rt_uint8_t *out_luma = player->nv12.virt_addr;
    rt_uint8_t *out_chroma = out_luma + player->source_luma_size;
    rt_uint32_t x;
    rt_uint32_t y;

    if (decoded->width != player->movie->width ||
            decoded->height != player->movie->height ||
            decoded->stride != player->source_stride ||
            decoded->format != SUNXI_JPEGD_FORMAT_MB32_420)
    {
        return -RT_ENOSYS;
    }
    for (y = 0; y < decoded->height; ++y)
    {
        rt_uint8_t *destination = out_luma + (rt_size_t)y * decoded->stride;
        for (x = 0; x < decoded->width; ++x)
        {
            destination[x] = luma[avi_mb32_offset(x, y, decoded->stride)];
        }
    }
    /* VE's F101 JPEG output uses the same MB32 addressing for UV pairs. */
    for (y = 0; y < decoded->height / 2U; ++y)
    {
        rt_uint8_t *destination = out_chroma + (rt_size_t)y * decoded->stride;
        for (x = 0; x < decoded->width; x += 2U)
        {
            rt_size_t source = avi_mb32_offset(x, y, decoded->stride);
            destination[x] = chroma[source];
            destination[x + 1U] = chroma[source + 1U];
        }
    }
    return RT_EOK;
}

static rt_err_t avi_prepare_display(struct avi_player *player,
        const char *framebuffer_name)
{
    rt_uint32_t bytes_per_pixel;
    rt_uint32_t display_width;
    rt_uint32_t display_height;
    struct sunxi_g2d_operation clear;
    rt_err_t err;

    player->framebuffer = rt_device_find(framebuffer_name);
    player->g2d = rt_device_find("g2d0");
    if (!player->g2d)
    {
        player->g2d = rt_device_find("g2d");
    }
    if (!player->framebuffer || !player->g2d)
    {
        return -RT_ENOSYS;
    }
    if ((err = rt_device_open(player->framebuffer, RT_DEVICE_OFLAG_RDWR)) != RT_EOK ||
            (err = rt_device_open(player->g2d, RT_DEVICE_OFLAG_RDWR)) != RT_EOK ||
            (err = rt_device_control(player->framebuffer, RTGRAPHIC_CTRL_GET_INFO,
                    &player->fb_info)) != RT_EOK)
    {
        return err;
    }
    switch (player->fb_info.pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        bytes_per_pixel = 2;
        break;
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        bytes_per_pixel = 4;
        break;
    default:
        return -RT_ENOSYS;
    }
    if (!player->fb_info.framebuffer || !player->fb_info.width ||
            !player->fb_info.height ||
            player->fb_info.pitch < player->fb_info.width * bytes_per_pixel)
    {
        return -RT_EINVAL;
    }

    player->framebuffer_buffer.virt_addr = player->fb_info.framebuffer;
    player->framebuffer_buffer.size = (rt_size_t)player->fb_info.pitch *
            player->fb_info.height;
    err = rt_device_control(player->g2d, SUNXI_G2D_CMD_IMPORT_BUFFER,
            &player->framebuffer_buffer);
    if (err)
    {
        return err;
    }
    player->framebuffer_imported = RT_TRUE;

    display_width = player->fb_info.width;
    display_height = (rt_uint64_t)player->movie->height * display_width /
            player->movie->width;
    if (display_height > player->fb_info.height)
    {
        display_height = player->fb_info.height;
        display_width = (rt_uint64_t)player->movie->width * display_height /
                player->movie->height;
    }
    player->display_width = display_width ? display_width : 1U;
    player->display_height = display_height ? display_height : 1U;
    player->display_x = (player->fb_info.width - player->display_width) / 2U;
    player->display_y = (player->fb_info.height - player->display_height) / 2U;

    rt_memset(&clear, 0, sizeof(clear));
    clear.type = SUNXI_G2D_OPERATION_FILL;
    clear.color = 0;
    clear.timeout = rt_tick_from_millisecond(100);
    clear.destination.format = player->fb_info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565 ?
            SUNXI_G2D_FORMAT_RGB565 : player->fb_info.pixel_format ==
            RTGRAPHIC_PIXEL_FORMAT_ARGB888 ? SUNXI_G2D_FORMAT_ARGB8888 :
            SUNXI_G2D_FORMAT_ABGR8888;
    clear.destination.width = player->fb_info.width;
    clear.destination.height = player->fb_info.height;
    clear.destination.plane[0].buffer = &player->framebuffer_buffer;
    clear.destination.plane[0].pitch = player->fb_info.pitch;
    clear.destination_rect.width = player->fb_info.width;
    clear.destination_rect.height = player->fb_info.height;
    return rt_device_control(player->g2d, SUNXI_G2D_CMD_COMPOSE, &clear);
}

static rt_err_t avi_present(struct avi_player *player)
{
    struct sunxi_g2d_operation operation;
    struct rt_device_rect_info rect = { 0, 0, 0, 0 };
    rt_err_t err;

    rt_memset(&operation, 0, sizeof(operation));
    operation.type = SUNXI_G2D_OPERATION_BLIT;
    operation.flags = SUNXI_G2D_YUV_FULL_RANGE;
    operation.timeout = rt_tick_from_millisecond(100);
    operation.source.format = SUNXI_G2D_FORMAT_NV12;
    operation.source.width = player->movie->width;
    operation.source.height = player->movie->height;
    operation.source.plane[0].buffer = &player->nv12;
    operation.source.plane[0].pitch = player->source_stride;
    operation.source.plane[1].buffer = &player->nv12;
    operation.source.plane[1].offset = player->source_luma_size;
    operation.source.plane[1].pitch = player->source_stride;
    operation.source_rect.width = player->movie->width;
    operation.source_rect.height = player->movie->height;
    operation.destination.format = player->fb_info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565 ?
            SUNXI_G2D_FORMAT_RGB565 : player->fb_info.pixel_format ==
            RTGRAPHIC_PIXEL_FORMAT_ARGB888 ? SUNXI_G2D_FORMAT_ARGB8888 :
            SUNXI_G2D_FORMAT_ABGR8888;
    operation.destination.width = player->fb_info.width;
    operation.destination.height = player->fb_info.height;
    operation.destination.plane[0].buffer = &player->framebuffer_buffer;
    operation.destination.plane[0].pitch = player->fb_info.pitch;
    operation.destination_rect.x = player->display_x;
    operation.destination_rect.y = player->display_y;
    operation.destination_rect.width = player->display_width;
    operation.destination_rect.height = player->display_height;
    if ((err = rt_device_control(player->g2d, SUNXI_G2D_CMD_COMPOSE,
            &operation)) != RT_EOK)
    {
        return err;
    }
    rect.width = player->fb_info.width;
    rect.height = player->fb_info.height;
    return rt_device_control(player->framebuffer, RTGRAPHIC_CTRL_RECT_UPDATE,
            &rect);
}

static rt_err_t avi_play_frame(const struct avi_frame_info *frame, void *context)
{
    struct avi_player *player = context;
    struct sunxi_jpegd_decode request = { 0 };
    rt_tick_t before;
    rt_tick_t target;
    rt_err_t err;

    if (frame->size > player->bitstream.size)
    {
        return -RT_EINVAL;
    }
    before = rt_tick_get();
    if (player->pace)
    {
        target = player->start_tick + (rt_uint64_t)player->frames *
                player->movie->microseconds_per_frame * RT_TICK_PER_SECOND /
                1000000U;
        if ((rt_int32_t)(target - before) > 0)
        {
            rt_thread_delay(target - before);
        }
        else if (player->frames)
        {
            ++player->late_frames;
        }
    }

    if ((err = avi_read_to_dma(player->movie->fd, frame->offset,
            player->bitstream.virt_addr, frame->size)) != RT_EOK)
    {
        return err;
    }
    rt_memset((rt_uint8_t *)player->bitstream.virt_addr + frame->size, 0xff,
            player->bitstream.size - frame->size);
    request.input = &player->bitstream;
    request.output = &player->decoded;
    request.input_size = frame->size;
    request.timeout = rt_tick_from_millisecond(500);
    before = rt_tick_get();
    err = rt_device_control(player->jpegd, SUNXI_JPEGD_CMD_DECODE, &request);
    player->ve_ticks += rt_tick_get() - before;
    if (err)
    {
        return err;
    }
    before = rt_tick_get();
    err = avi_detile_nv12(player, &request);
    player->detile_ticks += rt_tick_get() - before;
    if (err)
    {
        return err;
    }
    before = rt_tick_get();
    err = avi_present(player);
    player->g2d_ticks += rt_tick_get() - before;
    if (err)
    {
        return err;
    }
    ++player->frames;
    return RT_EOK;
}

static void avi_player_cleanup(struct avi_player *player)
{
    if (player->g2d)
    {
        if (player->framebuffer_imported)
        {
            rt_device_control(player->g2d, SUNXI_G2D_CMD_FREE_BUFFER,
                    &player->framebuffer_buffer);
        }
        if (player->nv12.virt_addr)
        {
            rt_device_control(player->g2d, SUNXI_G2D_CMD_FREE_BUFFER,
                    &player->nv12);
        }
        rt_device_close(player->g2d);
    }
    if (player->jpegd)
    {
        if (player->decoded.virt_addr)
        {
            rt_device_control(player->jpegd, SUNXI_JPEGD_CMD_FREE_BUFFER,
                    &player->decoded);
        }
        if (player->bitstream.virt_addr)
        {
            rt_device_control(player->jpegd, SUNXI_JPEGD_CMD_FREE_BUFFER,
                    &player->bitstream);
        }
        rt_device_close(player->jpegd);
    }
    if (player->framebuffer)
    {
        rt_device_close(player->framebuffer);
    }
}

static rt_uint32_t avi_fps(rt_uint32_t frames, rt_tick_t ticks)
{
    return ticks ? (rt_uint64_t)frames * RT_TICK_PER_SECOND * 100U / ticks : 0;
}

static int aviplay(int argc, char **argv)
{
    struct avi_movie movie;
    struct avi_scan scan;
    struct avi_player player;
    rt_uint32_t loops = 1;
    rt_uint32_t loop;
    rt_tick_t elapsed;
    rt_err_t err;

    if (argc < 2 || argc > 5)
    {
        rt_kprintf("Usage: aviplay <mjpeg.avi> [fb0] [loops] [bench]\n");
        rt_kprintf("MJPEG video only; audio streams are skipped. loops=0 repeats forever.\n");
        return -RT_EINVAL;
    }
    if (argc == 4)
    {
        loops = strtoul(argv[3], RT_NULL, 0);
    }
    if (argc == 5 && rt_strcmp(argv[4], "bench"))
    {
        rt_kprintf("last argument must be bench\n");
        return -RT_EINVAL;
    }
    err = avi_open(argv[1], &movie);
    if (err)
    {
        rt_kprintf("%s is not a supported MJPEG AVI: %d\n", argv[1], err);
        return err;
    }
    rt_memset(&scan, 0, sizeof(scan));
    scan.movie = &movie;
    err = avi_walk_frames(&movie, movie.movi_start, movie.movi_end, 0,
            avi_scan_frame, &scan);
    if (err || !scan.frames)
    {
        rt_kprintf("MJPEG frames not found: %d\n", err ? err : -RT_ENOENT);
        close(movie.fd);
        return err ? err : -RT_ENOENT;
    }

    rt_memset(&player, 0, sizeof(player));
    player.movie = &movie;
    player.pace = argc != 5;
    player.jpegd = rt_device_find("jpegd0");
    if (!player.jpegd)
    {
        player.jpegd = rt_device_find("jpegd");
    }
    if (!player.jpegd)
    {
        err = -RT_ENOSYS;
        goto out_movie;
    }
    if ((err = rt_device_open(player.jpegd, RT_DEVICE_OFLAG_RDWR)) != RT_EOK)
    {
        goto out_movie;
    }
    player.bitstream.size = RT_ALIGN(scan.largest_frame, AVI_STREAM_ALIGN);
    player.source_stride = RT_ALIGN(movie.width, 32U);
    player.source_luma_size = player.source_stride * RT_ALIGN(movie.height, 32U);
    player.decoded.size = player.source_luma_size * 3U / 2U;
    if ((err = rt_device_control(player.jpegd, SUNXI_JPEGD_CMD_ALLOC_BUFFER,
            &player.bitstream)) != RT_EOK ||
            (err = rt_device_control(player.jpegd, SUNXI_JPEGD_CMD_ALLOC_BUFFER,
            &player.decoded)) != RT_EOK)
    {
        goto out_player;
    }
    if ((err = avi_prepare_display(&player, argc >= 3 ? argv[2] : "fb0")) != RT_EOK)
    {
        goto out_player;
    }
    player.nv12.size = player.decoded.size;
    if ((err = rt_device_control(player.g2d, SUNXI_G2D_CMD_ALLOC_BUFFER,
            &player.nv12)) != RT_EOK)
    {
        goto out_player;
    }

    rt_kprintf("MJPEG AVI: %ux%u, %u frames, %u.%02u fps, max frame %u bytes%s\n",
            movie.width, movie.height, scan.frames,
            1000000U / movie.microseconds_per_frame,
            (100000000U / movie.microseconds_per_frame) % 100U,
            (rt_uint32_t)scan.largest_frame,
            player.pace ? "" : "; benchmark mode");
    player.start_tick = rt_tick_get();
    for (loop = 0; !loops || loop < loops; ++loop)
    {
        err = avi_walk_frames(&movie, movie.movi_start, movie.movi_end, 0,
                avi_play_frame, &player);
        if (err)
        {
            rt_kprintf("AVI stopped at frame %u: %d\n", player.frames, err);
            break;
        }
    }
    elapsed = rt_tick_get() - player.start_tick;
    rt_kprintf("AVI: %u frames in %u ms, %u.%02u fps; late %u\n",
            player.frames, (rt_uint32_t)((rt_uint64_t)elapsed * 1000U /
            RT_TICK_PER_SECOND), avi_fps(player.frames, elapsed) / 100U,
            avi_fps(player.frames, elapsed) % 100U, player.late_frames);
    rt_kprintf("  VE %u.%02u fps, detile %u.%02u fps, G2D+present %u.%02u fps\n",
            avi_fps(player.frames, player.ve_ticks) / 100U,
            avi_fps(player.frames, player.ve_ticks) % 100U,
            avi_fps(player.frames, player.detile_ticks) / 100U,
            avi_fps(player.frames, player.detile_ticks) % 100U,
            avi_fps(player.frames, player.g2d_ticks) / 100U,
            avi_fps(player.frames, player.g2d_ticks) % 100U);

out_player:
    avi_player_cleanup(&player);
out_movie:
    close(movie.fd);
    if (err)
    {
        rt_kprintf("aviplay failed: %d\n", err);
    }
    return err;
}
MSH_CMD_EXPORT(aviplay, hardware MJPEG AVI player: aviplay movie.avi [fb0] [loops]);

#endif /* enabled player dependencies */
