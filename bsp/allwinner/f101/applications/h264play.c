/*
 * H.264 player for the F101 video engine.
 *
 * The VE decoder returns linear NV12 surfaces. They stay in decoder-owned
 * memory and are imported into G2D only while the frame is held, so there is
 * no CPU colour conversion or copy on the video path.
 */

#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_DFS) && defined(RT_USING_FINSH) && \
    defined(RT_USING_GRAPHIC) && defined(RT_SOC_SUNXI_H264_DEC) && \
    defined(RT_SOC_SUNXI_G2D)

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <finsh.h>
#include <rthw.h>

#include <sunxi-g2d.h>
#include <vdec/vdec.h>

#define H264PLAY_READ_SIZE       (512U * 1024U)
#define H264PLAY_FRAME_RATE      30U
#define H264PLAY_FRAME_PERIOD_US (1000000U / H264PLAY_FRAME_RATE)
#define H264PLAY_AVI_MAX_DEPTH   8U
#define H264PLAY_FOURCC(a, b, c, d) \
    ((rt_uint32_t)(a) | ((rt_uint32_t)(b) << 8) | \
     ((rt_uint32_t)(c) << 16) | ((rt_uint32_t)(d) << 24))

#define H264PLAY_RIFF            H264PLAY_FOURCC('R', 'I', 'F', 'F')
#define H264PLAY_AVI             H264PLAY_FOURCC('A', 'V', 'I', ' ')
#define H264PLAY_LIST            H264PLAY_FOURCC('L', 'I', 'S', 'T')
#define H264PLAY_HDRL            H264PLAY_FOURCC('h', 'd', 'r', 'l')
#define H264PLAY_STRL            H264PLAY_FOURCC('s', 't', 'r', 'l')
#define H264PLAY_MOVI            H264PLAY_FOURCC('m', 'o', 'v', 'i')
#define H264PLAY_AVIH            H264PLAY_FOURCC('a', 'v', 'i', 'h')
#define H264PLAY_STRH            H264PLAY_FOURCC('s', 't', 'r', 'h')
#define H264PLAY_STRF            H264PLAY_FOURCC('s', 't', 'r', 'f')
#define H264PLAY_VIDS            H264PLAY_FOURCC('v', 'i', 'd', 's')
#define H264PLAY_H264            H264PLAY_FOURCC('H', '2', '6', '4')

struct h264play_player
{
    rt_device_t g2d;
    rt_device_t framebuffer;
    struct rt_device_graphic_info fb_info;
    struct sunxi_g2d_buffer framebuffer_buffer;
    rt_bool_t g2d_open;
    rt_bool_t framebuffer_open;
    rt_bool_t framebuffer_imported;
    rt_bool_t pace;
    rt_bool_t diagnostic;
    rt_uint32_t frame_period_us;
    rt_tick_t start_tick;
    rt_tick_t timeline_tick;
    rt_uint32_t frames;
    rt_uint32_t late_frames;
    rt_uint32_t present_intervals;
    rt_uint64_t present_interval_ticks;
    rt_tick_t first_present_tick;
    rt_tick_t last_present_tick;
    rt_tick_t min_present_interval;
    rt_tick_t max_present_interval;
    rt_tick_t decode_ticks;
    rt_tick_t present_ticks;
    rt_tick_t g2d_ticks;
    rt_tick_t display_ticks;
};

struct h264play_avi
{
    int fd;
    off_t file_size;
    off_t movi_start;
    off_t movi_end;
    rt_uint32_t stream_index;
    rt_uint32_t frame_period_us;
};

struct h264play_avi_frame
{
    off_t offset;
    rt_size_t size;
};

struct h264play_bits
{
    const rt_uint8_t *data;
    int size;
    int bit;
};

static rt_uint32_t h264play_le32(const rt_uint8_t *data)
{
    return (rt_uint32_t)data[0] | ((rt_uint32_t)data[1] << 8) |
            ((rt_uint32_t)data[2] << 16) | ((rt_uint32_t)data[3] << 24);
}

static rt_err_t h264play_read_at(int fd, off_t offset, void *data,
        rt_size_t size)
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

static rt_bool_t h264play_avi_chunk_is_video(rt_uint32_t id,
        rt_uint32_t stream)
{
    rt_uint8_t first = id & 0xff;
    rt_uint8_t second = (id >> 8) & 0xff;
    rt_uint8_t kind = (id >> 16) & 0xff;

    return first == '0' + stream / 10U && second == '0' + stream % 10U &&
            (kind == 'd' || kind == 'D');
}

static rt_err_t h264play_avi_parse_strl(struct h264play_avi *avi, off_t start,
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

        if (h264play_read_at(avi->fd, position, header, sizeof(header)))
        {
            return -RT_EIO;
        }
        id = h264play_le32(header);
        size = h264play_le32(header + 4);
        data = position + 8;
        next = data + size + (size & 1U);
        if (next < data || next > end)
        {
            return -RT_EINVAL;
        }
        if (id == H264PLAY_STRH && size >= sizeof(strh))
        {
            if (h264play_read_at(avi->fd, data, strh, sizeof(strh)))
            {
                return -RT_EIO;
            }
            have_strh = RT_TRUE;
        }
        else if (id == H264PLAY_STRF && size >= sizeof(strf))
        {
            if (h264play_read_at(avi->fd, data, strf, sizeof(strf)))
            {
                return -RT_EIO;
            }
            have_strf = RT_TRUE;
        }
        position = next;
    }

    if (!have_strh || h264play_le32(strh) != H264PLAY_VIDS)
    {
        return RT_EOK;
    }
    if (h264play_le32(strh + 4) != H264PLAY_H264 &&
            (!have_strf || h264play_le32(strf + 16) != H264PLAY_H264))
    {
        return RT_EOK;
    }
    if (*found || !have_strf)
    {
        return *found ? RT_EOK : -RT_ENOSYS;
    }

    avi->stream_index = index;
    if (h264play_le32(strh + 20) && h264play_le32(strh + 24))
    {
        avi->frame_period_us = (rt_uint64_t)h264play_le32(strh + 20) *
                1000000U / h264play_le32(strh + 24);
    }
    *found = RT_TRUE;

    return RT_EOK;
}

static rt_err_t h264play_avi_parse_hdrl(struct h264play_avi *avi, off_t start,
        off_t end)
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

        if (h264play_read_at(avi->fd, position, header, sizeof(header)))
        {
            return -RT_EIO;
        }
        id = h264play_le32(header);
        size = h264play_le32(header + 4);
        data = position + 8;
        next = data + size + (size & 1U);
        if (next < data || next > end)
        {
            return -RT_EINVAL;
        }
        if (id == H264PLAY_AVIH && size >= 4)
        {
            avi->frame_period_us = h264play_le32(header + 8);
        }
        else if (id == H264PLAY_LIST && size >= 4 &&
                h264play_le32(header + 8) == H264PLAY_STRL)
        {
            err = h264play_avi_parse_strl(avi, data + 4, data + size,
                    stream_index, &found);
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

static rt_err_t h264play_avi_open(int fd, struct h264play_avi *avi)
{
    struct stat statbuf;
    rt_uint8_t riff[12];
    off_t position;
    off_t end;
    rt_bool_t have_hdrl = RT_FALSE;

    rt_memset(avi, 0, sizeof(*avi));
    if (fstat(fd, &statbuf) || statbuf.st_size < (off_t)sizeof(riff) ||
            h264play_read_at(fd, 0, riff, sizeof(riff)) ||
            h264play_le32(riff) != H264PLAY_RIFF ||
            h264play_le32(riff + 8) != H264PLAY_AVI)
    {
        return -RT_EINVAL;
    }

    avi->fd = fd;
    avi->file_size = statbuf.st_size;
    end = rt_min_t(off_t, avi->file_size, (off_t)h264play_le32(riff + 4) + 8);
    position = sizeof(riff);
    while (position + 12 <= end)
    {
        rt_uint8_t header[12];
        rt_uint32_t id;
        rt_uint32_t size;
        off_t data;
        off_t next;
        rt_err_t err;

        if (h264play_read_at(fd, position, header, sizeof(header)))
        {
            return -RT_EIO;
        }
        id = h264play_le32(header);
        size = h264play_le32(header + 4);
        data = position + 8;
        next = data + size + (size & 1U);
        if (next < data || next > end)
        {
            return -RT_EINVAL;
        }
        if (id == H264PLAY_LIST && size >= 4 &&
                h264play_le32(header + 8) == H264PLAY_HDRL)
        {
            err = h264play_avi_parse_hdrl(avi, data + 4, data + size);
            if (err)
            {
                return err;
            }
            have_hdrl = RT_TRUE;
        }
        else if (id == H264PLAY_LIST && size >= 4 &&
                h264play_le32(header + 8) == H264PLAY_MOVI)
        {
            avi->movi_start = data + 4;
            avi->movi_end = data + size;
        }
        position = next;
    }
    if (!have_hdrl || !avi->movi_start || avi->movi_start >= avi->movi_end)
    {
        return -RT_EINVAL;
    }
    if (!avi->frame_period_us)
    {
        avi->frame_period_us = H264PLAY_FRAME_PERIOD_US;
    }

    return RT_EOK;
}

static unsigned int h264play_bits_ue(struct h264play_bits *bits)
{
    unsigned int value = 0;
    int zeroes = 0;
    int i;

    while (bits->bit < bits->size * 8 &&
            !((bits->data[bits->bit >> 3] >> (7 - (bits->bit & 7))) & 1U))
    {
        ++zeroes;
        ++bits->bit;
    }
    ++bits->bit;
    for (i = 0; i < zeroes && bits->bit < bits->size * 8; ++i)
    {
        value = (value << 1) |
                ((bits->data[bits->bit >> 3] >> (7 - (bits->bit & 7))) & 1U);
        ++bits->bit;
    }

    return ((1U << zeroes) - 1U) + value;
}

static void h264play_slice_info(const rt_uint8_t *nal, int length,
        unsigned int *first_mb)
{
    rt_uint8_t raw[16];
    struct h264play_bits bits;
    int zeroes = 0;
    int i;
    int count = 0;

    for (i = 1; i < length && count < (int)sizeof(raw); ++i)
    {
        if (zeroes >= 2 && nal[i] == 3)
        {
            zeroes = 0;
            continue;
        }
        zeroes = nal[i] == 0 ? zeroes + 1 : 0;
        raw[count++] = nal[i];
    }
    bits.data = raw;
    bits.size = count;
    bits.bit = 0;
    *first_mb = h264play_bits_ue(&bits);
}

static int h264play_find_start_code(const rt_uint8_t *data, int position,
        int end)
{
    for (; position + 2 < end; ++position)
    {
        if (data[position] == 0 && data[position + 1] == 0 &&
                data[position + 2] == 1)
        {
            return position;
        }
        if (position + 3 < end && data[position] == 0 &&
                data[position + 1] == 0 && data[position + 2] == 0 &&
                data[position + 3] == 1)
        {
            return position;
        }
    }

    return end;
}

static int h264play_start_code_size(const rt_uint8_t *data, int position,
        int end)
{
    if (position + 3 < end && data[position] == 0 && data[position + 1] == 0 &&
            data[position + 2] == 0 && data[position + 3] == 1)
    {
        return 4;
    }

    return 3;
}

/* Return the end of one H.264 access unit, or -1 when more file data is needed. */
static int h264play_next_access_unit(const rt_uint8_t *data, int position,
        int available, rt_bool_t eof)
{
    int start = h264play_find_start_code(data, position, available);
    rt_bool_t have_vcl = RT_FALSE;

    while (start < available)
    {
        int start_code_size = h264play_start_code_size(data, start, available);
        int nal = start + start_code_size;
        int next = h264play_find_start_code(data, nal, available);
        int type;

        if (next >= available && !eof)
        {
            return -1;
        }
        if (nal >= available)
        {
            break;
        }
        type = data[nal] & 0x1f;
        if (type == 1 || type == 5)
        {
            unsigned int first_mb;

            h264play_slice_info(data + nal, next - nal, &first_mb);
            if (have_vcl && first_mb == 0)
            {
                return start;
            }
            have_vcl = RT_TRUE;
        }
        else if (have_vcl && (type == 6 || type == 7 || type == 8 || type == 9))
        {
            return start;
        }
        start = next;
    }

    return eof ? available : -1;
}

static enum sunxi_g2d_format h264play_fb_format(rt_uint32_t format)
{
    if (format == RTGRAPHIC_PIXEL_FORMAT_RGB565)
    {
        return SUNXI_G2D_FORMAT_RGB565;
    }
    if (format == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
    {
        return SUNXI_G2D_FORMAT_ARGB8888;
    }
    if (format == RTGRAPHIC_PIXEL_FORMAT_BGR888)
    {
        return SUNXI_G2D_FORMAT_BGR888;
    }

    return SUNXI_G2D_FORMAT_ABGR8888;
}

static rt_err_t h264play_prepare_display(struct h264play_player *player,
        const char *fb_name)
{
    rt_err_t err;

    player->g2d = rt_device_find("g2d0");
    player->framebuffer = rt_device_find(fb_name);
    if (!player->g2d || !player->framebuffer)
    {
        return -RT_ENOSYS;
    }
    if ((err = rt_device_open(player->g2d, RT_DEVICE_OFLAG_RDWR)) != RT_EOK)
    {
        return err;
    }
    player->g2d_open = RT_TRUE;
    if ((err = rt_device_open(player->framebuffer, RT_DEVICE_OFLAG_RDWR)) != RT_EOK)
    {
        return err;
    }
    player->framebuffer_open = RT_TRUE;
    if ((err = rt_device_control(player->framebuffer, RTGRAPHIC_CTRL_GET_INFO,
            &player->fb_info)) != RT_EOK || !player->fb_info.framebuffer ||
            !player->fb_info.width || !player->fb_info.height)
    {
        return err ? err : -RT_EINVAL;
    }

    player->framebuffer_buffer.virt_addr = player->fb_info.framebuffer;
    player->framebuffer_buffer.size = (rt_size_t)player->fb_info.pitch *
            player->fb_info.height;
    err = rt_device_control(player->g2d, SUNXI_G2D_CMD_IMPORT_BUFFER,
            &player->framebuffer_buffer);
    if (err == RT_EOK)
    {
        player->framebuffer_imported = RT_TRUE;
    }

    return err;
}

/* Constant inputs isolate G2D colour conversion from the decoder and tiling. */
static rt_err_t h264play_test_nv12(rt_device_t g2d)
{
    static const rt_uint8_t colors[][3] =
    {
        {0, 128, 128}, {128, 128, 128}, {255, 128, 128},
        {76, 85, 255}, {150, 44, 21}, {29, 255, 107},
    };
    static const rt_uint16_t expected[] = {0x0000, 0x8410, 0xffff, 0xf800, 0x07e0, 0x001f};
    struct sunxi_g2d_buffer src = {0}, dst = {0};
    struct sunxi_g2d_operation op = {0};
    rt_err_t err;
    rt_uint32_t scale, i, j, failed = 0;

    src.size = 32U * 32U * 3U / 2U;
    dst.size = 64U * 64U * 2U;
    err = rt_device_control(g2d, SUNXI_G2D_CMD_ALLOC_BUFFER, &src);
    if (err)
    {
        return err;
    }
    err = rt_device_control(g2d, SUNXI_G2D_CMD_ALLOC_BUFFER, &dst);
    if (err)
    {
        goto free_src;
    }
    op.type = SUNXI_G2D_OPERATION_BLIT;
    op.flags = SUNXI_G2D_YUV_FULL_RANGE;
    op.timeout = rt_tick_from_millisecond(100);
    op.source.format = SUNXI_G2D_FORMAT_NV12;
    op.source.width = op.source.height = 32;
    op.source_rect.width = op.source_rect.height = 32;
    op.source.plane[0].buffer = op.source.plane[1].buffer = &src;
    op.source.plane[0].pitch = op.source.plane[1].pitch = 32;
    op.source.plane[1].offset = 1024;
    op.destination.format = SUNXI_G2D_FORMAT_RGB565;
    op.destination.plane[0].buffer = &dst;
    for (scale = 1; scale <= 2; scale++)
    {
        rt_uint32_t width = 32U * scale;

        op.destination.width = op.destination.height = width;
        op.destination_rect.width = op.destination_rect.height = width;
        op.destination.plane[0].pitch = width * 2U;
        for (i = 0; i < RT_ARRAY_SIZE(colors); i++)
        {
            rt_uint8_t *uv = (rt_uint8_t *)src.virt_addr + 1024;
            rt_uint16_t actual;
            rt_bool_t pass;

            rt_memset(src.virt_addr, colors[i][0], 1024);
            for (j = 0; j < 512; j += 2)
            {
                uv[j] = colors[i][1];
                uv[j + 1] = colors[i][2];
            }
            rt_memset(dst.virt_addr, 0xa5, dst.size);
            err = rt_device_control(g2d, SUNXI_G2D_CMD_COMPOSE, &op);
            if (err)
            {
                goto free_dst;
            }
            actual = ((rt_uint16_t *)dst.virt_addr)[(width / 2) * width + width / 2];
            pass = abs((actual >> 11) - (expected[i] >> 11)) <= 1 &&
                   abs(((actual >> 5) & 63) - ((expected[i] >> 5) & 63)) <= 2 &&
                   abs((actual & 31) - (expected[i] & 31)) <= 1;
            failed += !pass;
            rt_kprintf("NV12 test x%u YUV=%u/%u/%u RGB565=%04x expected=%04x %s\n",
                    scale, colors[i][0], colors[i][1], colors[i][2],
                    actual, expected[i], pass ? "PASS" : "FAIL");
        }
    }
    rt_kprintf("NV12 self-test: %u/12 failed\n", failed);
    /* Capture the real frame even if the independent G2D test fails. */
free_dst:
    rt_device_control(g2d, SUNXI_G2D_CMD_FREE_BUFFER, &dst);
free_src:
    rt_device_control(g2d, SUNXI_G2D_CMD_FREE_BUFFER, &src);
    return err;
}

static int h264play_dump_plane(int fd, const void *data, rt_uint32_t pitch,
        rt_uint32_t width, rt_uint32_t height)
{
    const rt_uint8_t *row = data;
    rt_uint32_t y;

    for (y = 0; y < height; y++, row += pitch)
    {
        rt_uint32_t done = 0;

        while (done < width)
        {
            ssize_t count = write(fd, row + done, width - done);

            if (count <= 0)
            {
                return -EIO;
            }
            done += count;
        }
    }
    return 0;
}

static void h264play_dump_frame(struct h264play_player *player, const struct vdec_frame *frame)
{
    int fd, err;

    /* Diagnostic files are opt-in, and never overwrite an existing capture. */
    fd = open("/h264-first.nv12", O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd >= 0)
    {
        err = h264play_dump_plane(fd, frame->plane[0], frame->stride[0],
                                 frame->width, frame->height);
        if (!err)
        {
            err = h264play_dump_plane(fd, frame->plane[1], frame->stride[1],
                                     frame->width, frame->height / 2);
        }
        if (close(fd) < 0 && !err)
        {
            err = -EIO;
        }
        rt_kprintf("capture /h264-first.nv12 %ux%u: %d\n", frame->width, frame->height, err);
    }
    else
    {
        rt_kprintf("capture /h264-first.nv12 open failed: errno=%d\n", errno);
    }
    if (player->fb_info.pixel_format != RTGRAPHIC_PIXEL_FORMAT_RGB565)
    {
        return;
    }
    fd = open("/h264-first.rgb565", O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd >= 0)
    {
        err = h264play_dump_plane(fd, player->fb_info.framebuffer, player->fb_info.pitch,
                                 player->fb_info.width * 2U, player->fb_info.height);
        if (close(fd) < 0 && !err)
        {
            err = -EIO;
        }
        rt_kprintf("capture /h264-first.rgb565 %ux%u: %d\n",
                   player->fb_info.width, player->fb_info.height, err);
    }
    else
    {
        rt_kprintf("capture /h264-first.rgb565 open failed: errno=%d\n", errno);
    }
}

static void h264play_cleanup(struct h264play_player *player)
{
    if (player->g2d_open)
    {
        if (player->framebuffer_imported)
        {
            rt_device_control(player->g2d, SUNXI_G2D_CMD_FREE_BUFFER,
                    &player->framebuffer_buffer);
        }
        rt_device_close(player->g2d);
    }
    if (player->framebuffer_open)
    {
        rt_device_close(player->framebuffer);
    }
}

static rt_err_t h264play_present(struct h264play_player *player,
        const struct vdec_frame *frame)
{
    struct sunxi_g2d_buffer nv12 = { 0 };
    struct sunxi_g2d_operation operation;
    struct rt_device_rect_info rect = { 0, 0, 0, 0 };
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t x;
    rt_uint32_t y;
    rt_err_t err;
    rt_size_t chroma_offset;
    rt_tick_t before;

    /* NV12 is one contiguous allocation; import it once and offset UV. */
    if ((rt_ubase_t)frame->plane[1] <= (rt_ubase_t)frame->plane[0])
    {
        return -RT_EINVAL;
    }
    chroma_offset = (rt_ubase_t)frame->plane[1] - (rt_ubase_t)frame->plane[0];
    nv12.virt_addr = frame->plane[0];
    nv12.phys_addr = (rt_ubase_t)rt_kmem_v2p(frame->plane[0]);
    nv12.size = chroma_offset + (rt_size_t)frame->stride[1] * ((frame->height + 1U) / 2U);
    if ((err = rt_device_control(player->g2d, SUNXI_G2D_CMD_IMPORT_BUFFER,
            &nv12)) != RT_EOK)
    {
        return err;
    }

    width = player->fb_info.width;
    height = (rt_uint64_t)frame->height * width / frame->width;
    if (height > player->fb_info.height)
    {
        height = player->fb_info.height;
        width = (rt_uint64_t)frame->width * height / frame->height;
    }
    x = (player->fb_info.width - width) / 2U;
    y = (player->fb_info.height - height) / 2U;

    rt_memset(&operation, 0, sizeof(operation));
    operation.type = SUNXI_G2D_OPERATION_BLIT;
    operation.flags = SUNXI_G2D_YUV_FULL_RANGE;
    operation.timeout = rt_tick_from_millisecond(100);
    operation.source.format = SUNXI_G2D_FORMAT_NV12;
    operation.source.width = frame->width;
    operation.source.height = frame->height;
    operation.source.plane[0].buffer = &nv12;
    operation.source.plane[0].pitch = frame->stride[0];
    operation.source.plane[1].buffer = &nv12;
    operation.source.plane[1].offset = chroma_offset;
    operation.source.plane[1].pitch = frame->stride[1];
    operation.source_rect.width = frame->width;
    operation.source_rect.height = frame->height;
    operation.destination.format = h264play_fb_format(player->fb_info.pixel_format);
    operation.destination.width = player->fb_info.width;
    operation.destination.height = player->fb_info.height;
    operation.destination.plane[0].buffer = &player->framebuffer_buffer;
    operation.destination.plane[0].pitch = player->fb_info.pitch;
    operation.destination_rect.x = x;
    operation.destination_rect.y = y;
    operation.destination_rect.width = width;
    operation.destination_rect.height = height;
    before = rt_tick_get();
    err = rt_device_control(player->g2d, SUNXI_G2D_CMD_COMPOSE, &operation);
    player->g2d_ticks += rt_tick_get() - before;
    if (err == RT_EOK)
    {
        if (player->diagnostic && !player->frames)
        {
            rt_kprintf("NV12 source: Y=%p UV=%p pitch=%u/%u offset=%u\n",
                    frame->plane[0], frame->plane[1], frame->stride[0], frame->stride[1],
                    (rt_uint32_t)chroma_offset);
            h264play_dump_frame(player, frame);
        }
        rect.width = player->fb_info.width;
        rect.height = player->fb_info.height;
        before = rt_tick_get();
        err = rt_device_control(player->framebuffer, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
        player->display_ticks += rt_tick_get() - before;
    }
    rt_device_control(player->g2d, SUNXI_G2D_CMD_FREE_BUFFER, &nv12);

    return err;
}

static int h264play_drain(struct h264play_player *player,
        struct vdec_stream *stream, rt_bool_t *done)
{
    for (;;)
    {
        struct vdec_frame frame;
        rt_tick_t before = rt_tick_get();
        int ret = vdec_stream_get_frame(stream, &frame);

        player->decode_ticks += rt_tick_get() - before;
        if (ret == 0)
        {
            rt_tick_t present_start;

            if (player->pace)
            {
                rt_tick_t target = player->timeline_tick +
                        (rt_uint64_t)player->frames * player->frame_period_us *
                        RT_TICK_PER_SECOND / 1000000U;

                rt_int32_t remaining = (rt_int32_t)(target - rt_tick_get());

                if (player->frames && remaining > 0)
                {
                    rt_thread_delay(remaining);
                }
                else if (player->frames && remaining < 0)
                {
                    ++player->late_frames;
                }
            }
            present_start = rt_tick_get();
            before = present_start;
            ret = h264play_present(player, &frame);
            player->present_ticks += rt_tick_get() - before;
            vdec_frame_release(&frame);
            if (ret)
            {
                return ret;
            }
            before = rt_tick_get();
            if (!player->frames)
            {
                /* The first decoded frame establishes the video timebase. */
                player->timeline_tick = present_start;
                player->first_present_tick = before;
            }
            if (player->frames)
            {
                rt_tick_t interval = before - player->last_present_tick;

                if (!player->present_intervals || interval < player->min_present_interval)
                {
                    player->min_present_interval = interval;
                }
                if (interval > player->max_present_interval)
                {
                    player->max_present_interval = interval;
                }
                player->present_interval_ticks += interval;
                ++player->present_intervals;
            }
            player->last_present_tick = before;
            ++player->frames;
            if (player->diagnostic)
            {
                *done = RT_TRUE;
                return 0;
            }
            continue;
        }
        if (ret == -EAGAIN)
        {
            return 0;
        }
        if (ret == -ENODATA)
        {
            *done = RT_TRUE;
            return 0;
        }

        return ret;
    }
}

static int h264play_feed_access_unit(struct h264play_player *player,
        struct vdec_stream *stream, const rt_uint8_t *data, size_t size,
        rt_bool_t *done)
{
    size_t input = 0;

    while (input < size)
    {
        size_t consumed = 0;
        int feed_ret = vdec_stream_feed(stream, data + input, size - input,
                (int64_t)player->frames * player->frame_period_us / 1000U,
                &consumed);
        int err;

        if (feed_ret == 0)
        {
            input += consumed;
        }
        else if (feed_ret != -EAGAIN)
        {
            return feed_ret;
        }
        err = h264play_drain(player, stream, done);
        if (err || *done)
        {
            return err;
        }
        if (!consumed && feed_ret == -EAGAIN)
        {
            return -RT_EBUSY;
        }
    }

    return 0;
}

struct h264play_avi_context
{
    const struct h264play_avi *avi;
    struct h264play_player *player;
    struct vdec_stream *stream;
    rt_uint8_t *buffer;
    rt_bool_t *done;
};

typedef rt_err_t (*h264play_avi_callback_t)(const struct h264play_avi_frame *frame,
        void *context);

static rt_err_t h264play_avi_walk(const struct h264play_avi *avi, off_t start,
        off_t end, unsigned int depth, h264play_avi_callback_t callback,
        void *context)
{
    off_t position = start;

    if (depth > H264PLAY_AVI_MAX_DEPTH)
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

        if (h264play_read_at(avi->fd, position, header, sizeof(header)))
        {
            return -RT_EIO;
        }
        id = h264play_le32(header);
        size = h264play_le32(header + 4);
        data = position + 8;
        next = data + size + (size & 1U);
        if (next < data || next > end)
        {
            return -RT_EINVAL;
        }
        if (id == H264PLAY_LIST && size >= 4)
        {
            err = h264play_avi_walk(avi, data + 4, data + size, depth + 1,
                    callback, context);
        }
        else if (h264play_avi_chunk_is_video(id, avi->stream_index))
        {
            struct h264play_avi_frame frame = { data, size };

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

static rt_err_t h264play_avi_feed(const struct h264play_avi_frame *frame,
        void *context)
{
    struct h264play_avi_context *avi_context = context;

    if (!frame->size || frame->size > H264PLAY_READ_SIZE)
    {
        return -RT_ENOMEM;
    }
    if (h264play_read_at(avi_context->avi->fd, frame->offset,
            avi_context->buffer, frame->size))
    {
        return -RT_EIO;
    }

    return h264play_feed_access_unit(avi_context->player, avi_context->stream,
            avi_context->buffer, frame->size, avi_context->done);
}

static int h264play(int argc, char **argv)
{
    struct h264play_player player;
    struct h264play_avi avi;
    struct vdec_stream_config config;
    struct vdec_stream *stream = RT_NULL;
    rt_uint8_t *data = RT_NULL;
    rt_bool_t eof = RT_FALSE;
    rt_bool_t flushed = RT_FALSE;
    rt_bool_t done = RT_FALSE;
    rt_bool_t avi_input = RT_FALSE;
    int fd = -1;
    int available = 0;
    int position = 0;
    rt_tick_t elapsed;
    rt_tick_t play_span = 0;
    rt_tick_t startup = 0;
    rt_uint64_t expected_span_us = 0;
    rt_uint64_t target_fps_x100;
    rt_uint64_t actual_fps_x100 = 0;
    int err = 0;

    rt_memset(&player, 0, sizeof(player));
    if (argc < 2 || argc > 4)
    {
        rt_kprintf("Usage: h264play <video.h264|video.avi> [fb0] [bench|diag]\n");
        rt_kprintf("Accepts progressive Annex-B H.264 and H264 AVI; bench disables pacing.\n");
        return -RT_EINVAL;
    }
    player.diagnostic = argc == 4 && !rt_strcmp(argv[3], "diag");
    if (argc == 4 && rt_strcmp(argv[3], "bench") && !player.diagnostic)
    {
        return -RT_EINVAL;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        return -RT_ENOENT;
    }
    {
        rt_uint8_t riff[12];

        if (h264play_read_at(fd, 0, riff, sizeof(riff)) == RT_EOK &&
                h264play_le32(riff) == H264PLAY_RIFF &&
                h264play_le32(riff + 8) == H264PLAY_AVI)
        {
            if ((err = h264play_avi_open(fd, &avi)) != RT_EOK)
            {
                rt_kprintf("h264play: unsupported H.264 AVI: %d\n", err);
                goto out;
            }
            avi_input = RT_TRUE;
        }
        if (lseek(fd, 0, SEEK_SET) != 0)
        {
            err = -RT_EIO;
            goto out;
        }
    }
    data = rt_malloc_align(H264PLAY_READ_SIZE, 64);
    if (!data)
    {
        err = -RT_ENOMEM;
        goto out;
    }

    player.pace = argc != 4;
    player.frame_period_us = avi_input ? avi.frame_period_us : H264PLAY_FRAME_PERIOD_US;
    if ((err = h264play_prepare_display(&player, argc >= 3 ? argv[2] : "fb0")) != RT_EOK)
    {
        rt_kprintf("h264play: cannot open g2d0/%s: %d\n", argc >= 3 ? argv[2] : "fb0", err);
        goto out;
    }
    if (player.diagnostic)
    {
        err = h264play_test_nv12(player.g2d);
        if (err)
        {
            goto out;
        }
    }
    rt_memset(&config, 0, sizeof(config));
    config.codec = VDEC_CODEC_H264;
    config.format = VDEC_FORMAT_NV12;
    config.buffer_size = 1024U * 1024U;
    config.no_cache_ops = true;
    if ((err = vdec_stream_open(&config, &stream)) != 0)
    {
        rt_kprintf("h264play: decoder open failed: %d\n", err);
        goto out;
    }
    player.start_tick = rt_tick_get();
    rt_kprintf("H.264 VE playback: %s, VE clock %u Hz%s\n", argv[1],
            vdec_clock_hz(), player.diagnostic ? "; diagnostic (one frame)" :
            player.pace ? "" : "; benchmark mode");

    if (avi_input)
    {
        struct h264play_avi_context avi_context =
        {
            .avi = &avi,
            .player = &player,
            .stream = stream,
            .buffer = data,
            .done = &done,
        };

        err = h264play_avi_walk(&avi, avi.movi_start, avi.movi_end, 0,
                h264play_avi_feed, &avi_context);
        if (!err && !done)
        {
            vdec_stream_flush(stream);
            err = h264play_drain(&player, stream, &done);
        }
    }

    while (!avi_input && !done)
    {
        int end = available > position ? h264play_next_access_unit(data, position,
                available, eof) : -1;

        if (end < 0 && !eof)
        {
            ssize_t count;

            if (available - position >= (int)H264PLAY_READ_SIZE)
            {
                err = -RT_ENOMEM;
                rt_kprintf("h264play: access unit exceeds %u bytes\n", H264PLAY_READ_SIZE);
                break;
            }
            rt_memmove(data, data + position, available - position);
            available -= position;
            position = 0;
            count = read(fd, data + available, H264PLAY_READ_SIZE - available);
            if (count <= 0)
            {
                eof = RT_TRUE;
            }
            else
            {
                available += count;
            }
            continue;
        }
        if (end >= 0)
        {
            err = h264play_feed_access_unit(&player, stream, data + position,
                    end - position, &done);
            position = end;
            if (err || done)
            {
                break;
            }
            continue;
        }

        if (!flushed)
        {
            vdec_stream_flush(stream);
            flushed = RT_TRUE;
        }
        err = h264play_drain(&player, stream, &done);
        if (err)
        {
            break;
        }
    }

    elapsed = rt_tick_get() - player.start_tick;
    if (player.frames)
    {
        startup = player.first_present_tick - player.start_tick;
    }
    if (player.frames > 1U)
    {
        expected_span_us = (rt_uint64_t)(player.frames - 1U) *
                player.frame_period_us;
        play_span = player.last_present_tick - player.first_present_tick;
        if (play_span)
        {
            actual_fps_x100 = (rt_uint64_t)(player.frames - 1U) *
                    RT_TICK_PER_SECOND * 100U / play_span;
        }
    }
    target_fps_x100 = player.frame_period_us ? 100000000U /
            player.frame_period_us : 0;
    rt_kprintf("H.264: %u frames in %u ms, %u.%02u fps; VE %u.%02u fps, G2D %u.%02u fps; late %u\n",
            player.frames, (rt_uint32_t)((rt_uint64_t)elapsed * 1000U / RT_TICK_PER_SECOND),
            elapsed ? (rt_uint32_t)((rt_uint64_t)player.frames * RT_TICK_PER_SECOND * 100U / elapsed) / 100U : 0,
            elapsed ? (rt_uint32_t)((rt_uint64_t)player.frames * RT_TICK_PER_SECOND * 100U / elapsed) % 100U : 0,
            player.decode_ticks ? (rt_uint32_t)((rt_uint64_t)player.frames * RT_TICK_PER_SECOND * 100U / player.decode_ticks) / 100U : 0,
            player.decode_ticks ? (rt_uint32_t)((rt_uint64_t)player.frames * RT_TICK_PER_SECOND * 100U / player.decode_ticks) % 100U : 0,
            player.g2d_ticks ? (rt_uint32_t)((rt_uint64_t)player.frames * RT_TICK_PER_SECOND * 100U / player.g2d_ticks) / 100U : 0,
            player.g2d_ticks ? (rt_uint32_t)((rt_uint64_t)player.frames * RT_TICK_PER_SECOND * 100U / player.g2d_ticks) % 100U : 0,
            player.late_frames);
    if (player.frames)
    {
        rt_kprintf("H.264 stages: avg VE=%u us, G2D=%u us, display=%u us (TE + transfer); late counts deadlines, not dropped frames\n",
                (rt_uint32_t)((rt_uint64_t)player.decode_ticks * 1000000U /
                    RT_TICK_PER_SECOND / player.frames),
                (rt_uint32_t)((rt_uint64_t)player.g2d_ticks * 1000000U /
                    RT_TICK_PER_SECOND / player.frames),
                (rt_uint32_t)((rt_uint64_t)player.display_ticks * 1000000U /
                    RT_TICK_PER_SECOND / player.frames));
    }
    rt_kprintf("H.264 result: target %u.%02u fps, actual %u.%02u fps; expected span %u ms, presentation span %u ms, startup %u ms, late %u/%u\n",
            (rt_uint32_t)(target_fps_x100 / 100U),
            (rt_uint32_t)(target_fps_x100 % 100U),
            (rt_uint32_t)(actual_fps_x100 / 100U),
            (rt_uint32_t)(actual_fps_x100 % 100U),
            (rt_uint32_t)(expected_span_us / 1000U),
            (rt_uint32_t)((rt_uint64_t)play_span * 1000U / RT_TICK_PER_SECOND),
            (rt_uint32_t)((rt_uint64_t)startup * 1000U / RT_TICK_PER_SECOND),
            player.late_frames, player.frames);
    if (player.present_intervals)
    {
        rt_kprintf("H.264 cadence: %u intervals, avg %u.%02u ms, min %u ms, max %u ms\n",
                player.present_intervals,
                (rt_uint32_t)(player.present_interval_ticks * 100000U /
                player.present_intervals / RT_TICK_PER_SECOND) / 100U,
                (rt_uint32_t)(player.present_interval_ticks * 100000U /
                player.present_intervals / RT_TICK_PER_SECOND) % 100U,
                (rt_uint32_t)((rt_uint64_t)player.min_present_interval * 1000U /
                RT_TICK_PER_SECOND),
                (rt_uint32_t)((rt_uint64_t)player.max_present_interval * 1000U /
                RT_TICK_PER_SECOND));
    }

out:
    if (stream)
    {
        vdec_stream_close(stream);
    }
    h264play_cleanup(&player);
    if (data)
    {
        rt_free_align(data);
    }
    if (fd >= 0)
    {
        close(fd);
    }
    if (err)
    {
        rt_kprintf("h264play failed: %d\n", err);
    }

    return err;
}
MSH_CMD_EXPORT(h264play, VE H.264 player: h264play video.h264 or video.avi [fb0] [bench|diag]);

#endif /* player dependencies */
