/*
********************************************************************************
*                                USB UVC Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  uvc_video.c
*
* Author        :  Kingvan
*
* Date          :  2013/03/26
*
* Description   :  USB VIDEO CONTROL Driver中对USB接口设备的处理
*
* Others        :  NULL
*
* History:
*       <time>          <author>     <version >     <desc>
*      2013.03.26       Kingvan         1.0         build this file
*
********************************************************************************
*/
//#include  "usb_host_config.h"
//#include  "usb_host_base_types.h"
#include  "usb_os_platform.h"
#include  "error.h"

#include  "usb_utils_find_zero_bit.h"
#include  "usb_list.h"
#include  "list_head_ext.h"

#include  "usb_host_common.h"
#include  "usb_gen_dev_mod.h"
#include  "urb.h"
#include  "usb_core_interface.h"
#include  "usb_msg.h"

//#include  "usbh_disk_info.h"
//#include  "usbh_buff_manager.h"
//#include  "usbh_disk_remove_time.h"

#include "video.h"
#include "uvcvideo.h"
#include "uvc_video.h"

/* ------------------------------------------------------------------------
 * UVC Controls
 */
static __inline void put_unaligned_le32(__u32 val, void *p)
{
    __u8 *ptr = (__u8 *)p;

    ptr[0] = (val&0xFF);
    ptr[1] = ((val>>8)&0xFF);
    ptr[2] = ((val>>16)&0xFF);
    ptr[3] = ((val>>24)&0xFF);

}
#if 0
static __inline u32 get_unaligned_le32( const void *p )
{
    __u32 ret;
    __u8 *ptr = (__u8 *)p;
    __u8 b0, b1, b2, b3;

    b0 = ptr[0];
    b1 = ptr[1];
    b2 = ptr[2];
    b3 = ptr[3];

    ret = (b0|(b1<<8)|(b2<<16)|(b2<<24));

    return ret;
}
/**
 * usb_endpoint_dir_in - check if the endpoint has IN direction
 * @epd: endpoint to be checked
 *
 * Returns true if the endpoint is of type IN, otherwise it returns false.
 */
static __inline int usb_endpoint_dir_in(const struct usb_endpoint_descriptor *epd)
{
    return ((epd->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN);
}
#endif
static int __uvc_query_ctrl(UVCDev_t *UVCDev, __u8 query, __u8 unit,
            __u8 intfnum, __u8 cs, void *data, __u16 size,
            __s32 timeout)
{
    __u8 type = USB_TYPE_CLASS | USB_RECIP_INTERFACE;
    __u32 pipe;

    pipe = (query & 0x80) ? usb_rcvctrlpipe(UVCDev->pusb_dev, 0)
                  : usb_sndctrlpipe(UVCDev->pusb_dev, 0);
    type |= (query & 0x80) ? USB_DIR_IN : USB_DIR_OUT;


    return usb_control_msg(UVCDev->pusb_dev, pipe, query, type, cs << 8,
            unit << 8 | intfnum, data, size, timeout);
}

static const char *uvc_query_name(__u8 query)
{
    switch (query) {
    case UVC_SET_CUR:
        return "SET_CUR";
    case UVC_GET_CUR:
        return "GET_CUR";
    case UVC_GET_MIN:
        return "GET_MIN";
    case UVC_GET_MAX:
        return "GET_MAX";
    case UVC_GET_RES:
        return "GET_RES";
    case UVC_GET_LEN:
        return "GET_LEN";
    case UVC_GET_INFO:
        return "GET_INFO";
    case UVC_GET_DEF:
        return "GET_DEF";
    default:
        return "<invalid>";
    }
}

int uvc_query_ctrl(UVCDev_t *UVCDev, __u8 query, __u8 unit,
            __u8 intfnum, __u8 cs, void *data, __u16 size)
{
    int ret;

    ret = __uvc_query_ctrl(UVCDev, query, unit, intfnum, cs, data, size,
                UVC_CTRL_CONTROL_TIMEOUT);
    if (ret != size) {
        hal_log_err("Failed to query (%s) UVC control %u on unit %u: %d (exp. %u).\n",
                uvc_query_name(query), cs, unit, ret, size);
        return -EIO;
    }

    return 0;
}

static void uvc_fixup_video_ctrl(struct uvc_streaming *stream,
    struct uvc_streaming_control *ctrl)
{
    struct uvc_format *format = NULL;
    struct uvc_frame *frame = NULL;
    __u32 i;

    for (i = 0; i < stream->nformats; ++i) {
        if (stream->format[i].index == ctrl->bFormatIndex) {
            format = &stream->format[i];
            break;
        }
    }

    if (format == NULL)
        return;

    for (i = 0; i < format->nframes; ++i) {
        if (format->frame[i].bFrameIndex == ctrl->bFrameIndex) {
            frame = &format->frame[i];
            break;
        }
    }

    if (frame == NULL)
        return;

    if (!(format->flags & UVC_FMT_FLAG_COMPRESSED) ||
         (ctrl->dwMaxVideoFrameSize == 0 &&
          stream->dev->uvc_version < 0x0110))
        ctrl->dwMaxVideoFrameSize =
            frame->dwMaxVideoFrameBufferSize;

    if (!(format->flags & UVC_FMT_FLAG_COMPRESSED) &&
        (stream->dev->quirks & UVC_QUIRK_FIX_BANDWIDTH) &&
        stream->intf->num_altsetting > 1) {
        __u32 interval;
        __u32 bandwidth;

        interval = (ctrl->dwFrameInterval > 100000)
             ? ctrl->dwFrameInterval
             : frame->dwFrameInterval[0];

        /* Compute a bandwidth estimation by multiplying the frame
         * size by the number of video frames per second, divide the
         * result by the number of USB frames (or micro-frames for
         * high-speed devices) per second and add the UVC header size
         * (assumed to be 12 bytes long).
         */
        bandwidth = frame->wWidth * frame->wHeight / 8 * format->bpp;
        bandwidth *= 10000000 / interval + 1;
        bandwidth /= 1000;
        if (stream->dev->pusb_dev->speed == USB_SPEED_HIGH)
            bandwidth /= 8;
        bandwidth += 12;

        /* The bandwidth estimate is too low for many cameras. Don't use
         * maximum packet sizes lower than 1024 bytes to try and work
         * around the problem. According to measurements done on two
         * different camera models, the value is high enough to get most
         * resolutions working while not preventing two simultaneous
         * VGA streams at 15 fps.
         */

        bandwidth = max(bandwidth, 1024);

        ctrl->dwMaxPayloadTransferSize = bandwidth;
    }
}

static int uvc_get_video_ctrl(struct uvc_streaming *stream,
    struct uvc_streaming_control *ctrl, __s32 probe, __u8 query)
{
    __u8 *data;
    __u16 size;
    __s32 ret;

    size = stream->dev->uvc_version >= 0x0110 ? 34 : 26;
    if ((stream->dev->quirks & UVC_QUIRK_PROBE_DEF) &&
            query == UVC_GET_DEF)
        return -EIO;

    data = hal_malloc(size);
    if (data == NULL)
    {
        hal_log_err("hal_malloc fail\n");
        return -ENOMEM;
    }

    ret = __uvc_query_ctrl(stream->dev, query, 0, stream->intfnum,
        probe ? UVC_VS_PROBE_CONTROL : UVC_VS_COMMIT_CONTROL, data,
        size, 5000);

    if ((query == UVC_GET_MIN || query == UVC_GET_MAX) && ret == 2) {
        /* Some cameras, mostly based on Bison Electronics chipsets,
         * answer a GET_MIN or GET_MAX request with the wCompQuality
         * field only.
         */
        hal_log_err("UVC non compliance - GET_MIN/MAX(PROBE) incorrectly supported. Enabling workaround.\n");
        memset(ctrl, 0, sizeof *ctrl);
        ctrl->wCompQuality = *((__u16 *)data);//le16_to_cpup((__le16 *)data);
        ret = 0;
        goto out;
    } else if (query == UVC_GET_DEF && probe == 1 && ret != size) {
        /* Many cameras don't support the GET_DEF request on their
         * video probe control. Warn once and return, the caller will
         * fall back to GET_CUR.
         */
        hal_log_err("UVC non compliance - GET_DEF(PROBE) not supported. Enabling workaround.\n");
        ret = -EIO;
        goto out;
    } else if (ret != size) {
        hal_log_err("Failed to query (%u) UVC %s control : %d (exp. %u).\n",
                query, probe ? "probe" : "commit", ret, size);
        ret = -EIO;
        goto out;
    }

    ctrl->bmHint = *((__u16 *)&data[0]);//le16_to_cpup((__le16 *)&data[0]);
    ctrl->bFormatIndex = data[2];
    ctrl->bFrameIndex = data[3];
    ctrl->dwFrameInterval = *((__u32 *)&data[4]);//le32_to_cpup((__le32 *)&data[4]);
    ctrl->wKeyFrameRate = *((__u16 *)&data[8]);//le16_to_cpup((__le16 *)&data[8]);
    ctrl->wPFrameRate = *((__u16 *)&data[10]);//le16_to_cpup((__le16 *)&data[10]);
    ctrl->wCompQuality = *((__u16 *)&data[12]);//le16_to_cpup((__le16 *)&data[12]);
    ctrl->wCompWindowSize = *((__u16 *)&data[14]);//le16_to_cpup((__le16 *)&data[14]);
    ctrl->wDelay = *((__u16 *)&data[16]);//le16_to_cpup((__le16 *)&data[16]);
    ctrl->dwMaxVideoFrameSize = get_unaligned_le32(&data[18]);
    ctrl->dwMaxPayloadTransferSize = get_unaligned_le32(&data[22]);

    if (size == 34) {
        ctrl->dwClockFrequency = get_unaligned_le32(&data[26]);
        ctrl->bmFramingInfo = data[30];
        ctrl->bPreferedVersion = data[31];
        ctrl->bMinVersion = data[32];
        ctrl->bMaxVersion = data[33];
    } else {
        ctrl->dwClockFrequency = stream->dev->clock_frequency;
        ctrl->bmFramingInfo = 0;
        ctrl->bPreferedVersion = 0;
        ctrl->bMinVersion = 0;
        ctrl->bMaxVersion = 0;
    }

    /* Some broken devices return null or wrong dwMaxVideoFrameSize and
     * dwMaxPayloadTransferSize fields. Try to get the value from the
     * format and frame descriptors.
     */
    uvc_fixup_video_ctrl(stream, ctrl);
    ret = 0;

out:
    hal_free(data);
    return ret;
}

static int uvc_set_video_ctrl(struct uvc_streaming *stream,
    struct uvc_streaming_control *ctrl, __s32 probe)
{
    __u8 *data;
    __u16 size;
    __s32 ret;

    size = stream->dev->uvc_version >= 0x0110 ? 34 : 26;
    data = hal_malloc(size);
    if (data == NULL)
    {
        hal_log_err("hal_malloc fail\n");
        return -ENOMEM;
    } else {
        memset(data, 0, size);
    }

    *(__u16 *)&data[0] = cpu_to_le16(ctrl->bmHint);
    data[2] = ctrl->bFormatIndex;
    data[3] = ctrl->bFrameIndex;
    *(__u32 *)&data[4] = cpu_to_le32(ctrl->dwFrameInterval);
    *(__u16 *)&data[8] = cpu_to_le16(ctrl->wKeyFrameRate);
    *(__u16 *)&data[10] = cpu_to_le16(ctrl->wPFrameRate);
    *(__u16 *)&data[12] = cpu_to_le16(ctrl->wCompQuality);
    *(__u16 *)&data[14] = cpu_to_le16(ctrl->wCompWindowSize);
    *(__u16 *)&data[16] = cpu_to_le16(ctrl->wDelay);
    put_unaligned_le32(ctrl->dwMaxVideoFrameSize, &data[18]);
    put_unaligned_le32(ctrl->dwMaxPayloadTransferSize, &data[22]);

    if (size == 34) {
        put_unaligned_le32(ctrl->dwClockFrequency, &data[26]);
        data[30] = ctrl->bmFramingInfo;
        data[31] = ctrl->bPreferedVersion;
        data[32] = ctrl->bMinVersion;
        data[33] = ctrl->bMaxVersion;
    }

    ret = __uvc_query_ctrl(stream->dev, UVC_SET_CUR, 0, stream->intfnum,
        probe ? UVC_VS_PROBE_CONTROL : UVC_VS_COMMIT_CONTROL, data,
        size, 5000);
    if (ret != size) {
        hal_log_err("Failed to set UVC %s control : %d (exp. %u).\n",
                probe ? "probe" : "commit", ret, size);
        ret = -EIO;
    }

    hal_free(data);
    return ret;
}

int uvc_probe_video(struct uvc_streaming *stream,
    struct uvc_streaming_control *probe)
{
    struct uvc_streaming_control probe_min, probe_max;
    __u16 bandwidth;
    __u32 i;
    __s32 ret;

    /* Perform probing. The device should adjust the requested values
     * according to its capabilities. However, some devices, namely the
     * first generation UVC Logitech webcams, don't implement the Video
     * Probe control properly, and just return the needed bandwidth. For
     * that reason, if the needed bandwidth exceeds the maximum available
     * bandwidth, try to lower the quality.
     */
    ret = uvc_set_video_ctrl(stream, probe, 1);
    if (ret < 0)
        goto done_uvc_probe_video;

    /* Get the minimum and maximum values for compression settings. */
    if (!(stream->dev->quirks & UVC_QUIRK_PROBE_MINMAX)) {
        ret = uvc_get_video_ctrl(stream, &probe_min, 1, UVC_GET_MIN);
        if (ret < 0)
            goto done_uvc_probe_video;
        ret = uvc_get_video_ctrl(stream, &probe_max, 1, UVC_GET_MAX);
        if (ret < 0)
            goto done_uvc_probe_video;

        probe->wCompQuality = probe_max.wCompQuality;
    }

    for (i = 0; i < 2; ++i) {
        ret = uvc_set_video_ctrl(stream, probe, 1);
        if (ret < 0)
            goto done_uvc_probe_video;
        ret = uvc_get_video_ctrl(stream, probe, 1, UVC_GET_CUR);
        if (ret < 0)
            goto done_uvc_probe_video;

        if (stream->intf->num_altsetting == 1)
            break;

        bandwidth = probe->dwMaxPayloadTransferSize;
        if (bandwidth <= stream->maxpsize)
            break;

        if (stream->dev->quirks & UVC_QUIRK_PROBE_MINMAX) {
            ret = -ENOSPC;
            goto done_uvc_probe_video;
        }

        /* TODO: negotiate compression parameters */
        probe->wKeyFrameRate = probe_min.wKeyFrameRate;
        probe->wPFrameRate = probe_min.wPFrameRate;
        probe->wCompQuality = probe_max.wCompQuality;
        probe->wCompWindowSize = probe_min.wCompWindowSize;
    }

done_uvc_probe_video:
    return ret;
}

int uvc_commit_video(struct uvc_streaming *stream,
    struct uvc_streaming_control *probe)
{
    return uvc_set_video_ctrl(stream, probe, 0);
}

#if 1
/* ------------------------------------------------------------------------
 * Video codecs
 */

/* Values for bmHeaderInfo (Video and Still Image Payload Headers, 2.4.3.3) */
#define UVC_STREAM_EOH  (1 << 7)
#define UVC_STREAM_ERR  (1 << 6)
#define UVC_STREAM_STI  (1 << 5)
#define UVC_STREAM_RES  (1 << 4)
#define UVC_STREAM_SCR  (1 << 3)
#define UVC_STREAM_PTS  (1 << 2)
#define UVC_STREAM_EOF  (1 << 1)
#define UVC_STREAM_FID  (1 << 0)

static __s32 uvc_video_buffer_init( struct uvc_streaming *stream )
{
    stream->buf.state         = UVC_BUF_STATE_QUEUED;
    stream->buf.error         = 0;
    stream->buf.buf.mem_buf   = stream->dev->frame_buf0;
    stream->buf.buf.length    = stream->dev->frame_len;
    stream->buf.buf.bytesused = 0;

    return 0;
}

struct uvc_buffer *uvc_queue_next_buffer(struct uvc_streaming *stream,
        struct uvc_buffer *buf)
{
    static __u32 st = 0, complete_cnt = 0, lost_cnt = 0, bsp = 0;
    u8* mem;

    //YUV data
    if ( !(stream->cur_format->flags & UVC_FMT_FLAG_COMPRESSED) )
    {
        mem = (u8*)buf->buf.mem_buf;
        if(mem == NULL)
        {
            hal_log_info("input buf == NULL\n");
            buf->error = 1;
        }
        if( buf->buf.length != buf->buf.bytesused )
        {
            buf->error = 1;
        }
    }
    //M-JPEG data
    else if( (stream->cur_format->flags & UVC_FMT_FLAG_COMPRESSED) )
    {
        mem = (u8*)buf->buf.mem_buf;
        if(mem == NULL)
        {
            hal_log_info("input buf == NULL\n");
            buf->error = 1;
        }

        while( buf->buf.bytesused > 0 && mem[buf->buf.bytesused-1] == 0x00 ) buf->buf.bytesused--;

        if( mem[0] != 0xFF  || mem[1] != 0xD8 )
        {
            hal_log_info("get MJPEG error( %x %x......%x %x)\n", mem[0], mem[1], mem[buf->buf.bytesused-2], mem[buf->buf.bytesused-1]);
            buf->error = 1;
        }
        else if( mem[buf->buf.bytesused-2] != 0xFF || mem[buf->buf.bytesused-1] != 0xD9 )
        {
            mem[buf->buf.bytesused++] = 0xFF;
            mem[buf->buf.bytesused++] = 0xD9;
        }

        {
            while( (buf->buf.bytesused&0x7) != 0) mem[buf->buf.bytesused++] = 0x00;

            *((__u32*)(buf->buf.mem_buf+buf->buf.length-4)) = buf->buf.bytesused;
        }
    }

    if( buf->error == 0 )
    {
#if 1
        complete_cnt++;
        bsp += buf->buf.bytesused;
        if( esKRNL_TimeGet() - st >= 100 )
        {
            hal_log_info("fps:(%d,%d) bsp=%d Mbps\n", complete_cnt, lost_cnt,bsp*8/1024/1024);
            st = esKRNL_TimeGet();
            complete_cnt = 0;
            lost_cnt = 0;
            bsp = 0;
        }
#endif
        if( stream->dev->exchange_buf )
        {
            stream->dev->exchange_buf((__u32*)(&buf->buf.mem_buf), NULL, NULL);
            stream->dev->frame_buf0 = stream->buf.buf.mem_buf;
        }
    }
#if 1
    else
    {
        lost_cnt++;
    }
#endif
    buf->state         = UVC_BUF_STATE_QUEUED;
    buf->error         = 0;
    buf->buf.bytesused = 0;

    return buf;
}

/* Video payload decoding is handled by uvc_video_decode_start(),
 * uvc_video_decode_data() and uvc_video_decode_end().
 *
 * uvc_video_decode_start is called with URB data at the start of a bulk or
 * isochronous payload. It processes header data and returns the header size
 * in bytes if successful. If an error occurs, it returns a negative error
 * code. The following error codes have special meanings.
 *
 * - EAGAIN informs the caller that the current video buffer should be marked
 *   as done, and that the function should be called again with the same data
 *   and a new video buffer. This is used when end of frame conditions can be
 *   reliably detected at the beginning of the next frame only.
 *
 * If an error other than -EAGAIN is returned, the caller will drop the current
 * payload. No call to uvc_video_decode_data and uvc_video_decode_end will be
 * made until the next payload. -EPERM can be used to drop the current
 * payload if no other error code is appropriate.
 *
 * uvc_video_decode_data is called for every URB with URB data. It copies the
 * data to the video buffer.
 *
 * uvc_video_decode_end is called with header data at the end of a bulk or
 * isochronous payload. It performs any additional header data processing and
 * returns 0 or a negative error code if an error occurred. As header data have
 * already been processed by uvc_video_decode_start, this functions isn't
 * required to perform sanity checks a second time.
 *
 * For isochronous transfers where a payload is always transferred in a single
 * URB, the three functions will be called in a row.
 *
 * To let the decoder process header data and update its internal state even
 * when no video buffer is available, uvc_video_decode_start must be prepared
 * to be called with a NULL buf parameter. uvc_video_decode_data and
 * uvc_video_decode_end will never be called with a NULL buffer.
 */
static int uvc_video_decode_start(struct uvc_streaming *stream,
        struct uvc_buffer *buf, const __u8 *data, int len)
{
    __u8 fid;

    /* Sanity checks:
     * - packet must be at least 2 bytes long
     * - bHeaderLength value must be at least 2 bytes (see above)
     * - bHeaderLength value can't be larger than the packet size.
     */
    if (len < 2 || data[0] < 2 || data[0] > len)
    {
        //hal_log_err("Sanity checks error,(%d,%d)\n", data[0], len);
        return -EINVAL;
    }

    /* Skip payloads marked with the error bit ("error frames"). */
    if (data[1] & UVC_STREAM_ERR) {
        //hal_log_err("Dropping payload (error bit set).\n");
        return -EPERM;
    }

    fid = data[1] & UVC_STREAM_FID;

    /* Increase the sequence number regardless of any buffer states, so
     * that discontinuous sequence numbers always indicate lost frames.
     */
    if (stream->last_fid != fid)
        stream->sequence++;

    /* Store the payload FID bit and return immediately when the buffer is
     * NULL.
     */
    if (buf == NULL) {
        //hal_log_err("buf == NULL\n");
        stream->last_fid = fid;
        return -EPERM;
    }

    /* Synchronize to the input stream by waiting for the FID bit to be
     * toggled when the the buffer state is not UVC_BUF_STATE_ACTIVE.
     * stream->last_fid is initialized to -1, so the first isochronous
     * frame will always be in sync.
     *
     * If the device doesn't toggle the FID bit, invert stream->last_fid
     * when the EOF bit is set to force synchronisation on the next packet.
     */
    if (buf->state != UVC_BUF_STATE_ACTIVE) {
        //struct timespec ts;

        if (fid == stream->last_fid) {
            //hal_log_err("Dropping payload (out of sync).\n");
            if ((stream->dev->quirks & UVC_QUIRK_STREAM_NO_FID) &&
                (data[1] & UVC_STREAM_EOF))
                stream->last_fid ^= UVC_STREAM_FID;
            return -EPERM;
        }

        //if (uvc_clock_param == CLOCK_MONOTONIC)
        //  ktime_get_ts(&ts);
        //else
        //  ktime_get_real_ts(&ts);
        //
        //buf->buf.sequence = stream->sequence;
        //buf->buf.timestamp.tv_sec = ts.tv_sec;
        //buf->buf.timestamp.tv_usec = ts.tv_nsec / NSEC_PER_USEC;

        /* TODO: Handle PTS and SCR. */
        buf->state = UVC_BUF_STATE_ACTIVE;
    }

    /* Mark the buffer as done if we're at the beginning of a new frame.
     * End of frame detection is better implemented by checking the EOF
     * bit (FID bit toggling is delayed by one frame compared to the EOF
     * bit), but some devices don't set the bit at end of frame (and the
     * last payload can be lost anyway). We thus must check if the FID has
     * been toggled.
     *
     * stream->last_fid is initialized to -1, so the first isochronous
     * frame will never trigger an end of frame detection.
     *
     * Empty buffers (bytesused == 0) don't trigger end of frame detection
     * as it doesn't make sense to return an empty buffer. This also
     * avoids detecting end of frame conditions at FID toggling if the
     * previous payload had the EOF bit set.
     */
    if (fid != stream->last_fid && buf->buf.bytesused != 0) {
        hal_log_info("Frame complete (FID bit toggled).\n");
        buf->state = UVC_BUF_STATE_READY;
        return -EAGAIN;
    }

    stream->last_fid = fid;

    return data[0];
}

static void uvc_video_decode_data(struct uvc_streaming *stream,
        struct uvc_buffer *buf, const __u8 *data, int len)
{
    unsigned int maxlen, nbytes;
    void *mem;

    if (len <= 0)
        return;

    /* Copy the video data to the buffer. */
    maxlen = buf->buf.length - buf->buf.bytesused;
    mem = (void*)(buf->buf.mem_buf + buf->buf.bytesused);
    nbytes = min((unsigned int)len, maxlen);


    if ( buf->buf.mem_buf )
    {
        memcpy(mem, data, nbytes);
    } else {
        hal_log_info("buf->buf.mem_buf == NULL\n");
    }



    buf->buf.bytesused += nbytes;

    /* Complete the current frame if the buffer size was exceeded. */
    if (len > maxlen) {
        hal_log_info("Frame complete (overflow).(%d, %d)\n", buf->buf.length, buf->buf.bytesused);
        buf->state = UVC_BUF_STATE_READY;
    }
}

static void uvc_video_decode_end(struct uvc_streaming *stream,
        struct uvc_buffer *buf, const __u8 *data, int len)
{

    /* Mark the buffer as done if the EOF marker is set. */
    if ((data[1] & UVC_STREAM_EOF) && buf->buf.bytesused != 0) {
        //hal_log_err("Frame complete (EOF found).%x, (%x %x %x %x)\n", data[1], data[len-2], data[len-1], data[len], data[len+1]);
        //if (data[0] == len)
        //  hal_log_err("EOF in empty payload.\n");
        buf->state = UVC_BUF_STATE_READY;
        if (stream->dev->quirks & UVC_QUIRK_STREAM_NO_FID)
            stream->last_fid ^= UVC_STREAM_FID;
    }
}

/* ------------------------------------------------------------------------
 * URB handling
 */

/*
 * Completion handler for video URBs.
 */
static void uvc_video_decode_isoc(struct urb *urb, struct uvc_streaming *stream,
    struct uvc_buffer *buf)
{
    u8 *mem = NULL;
    int ret, i;


    if( stream->dev->exchange_buf == NULL ) {
        hal_log_info("stream->dev->exchange_buf== null \n");
        return;
    }

    for (i = 0; i < urb->number_of_packets; ++i) {
        if (urb->iso_frame_desc[i].status < 0) {
            hal_log_info("USB isochronous frame lost (%d).\n", urb->iso_frame_desc[i].status);
            /* Mark the buffer as faulty. */
            if (buf != NULL) {
                buf->error = 1;
            }
            continue;
        }

        /* Decode the payload header. */
        mem = (u8*)((__u32)urb->transfer_buffer + urb->iso_frame_desc[i].offset);
        do {
            ret = uvc_video_decode_start(stream, buf, mem, urb->iso_frame_desc[i].actual_length);
            if (ret == -EAGAIN) {
                buf = uvc_queue_next_buffer(stream, buf);
            }
        } while (ret == -EAGAIN);

        if (ret < 0) {
            continue;
        }

        /* Decode the payload data. */
        uvc_video_decode_data(stream, buf, mem + ret, urb->iso_frame_desc[i].actual_length - ret);
        /* Process the header again. */
        uvc_video_decode_end(stream, buf, mem, urb->iso_frame_desc[i].actual_length);


        if (buf->state == UVC_BUF_STATE_READY) {
            buf = uvc_queue_next_buffer(stream, buf);
        }
    }

}

static void uvc_video_decode_isoc_test(struct urb *urb, struct uvc_streaming *stream,
    struct uvc_buffer *buf)
{
    u8 *mem;
    int i;

    if( stream->dev->exchange_buf == NULL )
    {
        return;
    }

    for (i = 0; i < urb->number_of_packets; ++i) {
        if (urb->iso_frame_desc[i].status < 0) {
            continue;
        }

        /* Decode the payload header. */
        mem = (u8*)((__u32)urb->transfer_buffer + urb->iso_frame_desc[i].offset);
        if( mem[0] == 0x02 && mem[1] == 0x80 && urb->iso_frame_desc[i].actual_length == 2 )
        {
            //__log("111\n");
            buf->state         = UVC_BUF_STATE_ACTIVE;
            continue;
        }
        else if( mem[0] == 0x02 && mem[1] == 0x80 && urb->iso_frame_desc[i].actual_length > 2 && buf->state == UVC_BUF_STATE_ACTIVE)
        {
            //__log("%x %x\n", mem[2], mem[3]);
            uvc_video_decode_data(stream, buf, mem + 2, urb->iso_frame_desc[i].actual_length - 2);
            if( buf->state != UVC_BUF_STATE_READY )
                continue;
        }
        else if( mem[0] == 0x02 && mem[1] == 0x82 && urb->iso_frame_desc[i].actual_length == 2 && buf->state == UVC_BUF_STATE_ACTIVE)
        {
            //__log("333\n");
            buf->state         = UVC_BUF_STATE_READY;
        }
        else if( mem[0] == 0x02 && mem[1] == 0x82 && urb->iso_frame_desc[i].actual_length > 2 && buf->state == UVC_BUF_STATE_ACTIVE)
        {
            __log("444\n");
            uvc_video_decode_data(stream, buf, mem + 2, urb->iso_frame_desc[i].actual_length - 2);
            buf->state         = UVC_BUF_STATE_READY;
        }
        else if( urb->iso_frame_desc[i].actual_length < 2)
        {
            //__log("1\n");
            continue;
        }
        else
        {
            //__log("2:(0x%x,0x%x)%d, %d\n", mem[0], mem[1], urb->iso_frame_desc[i].actual_length, buf->state);
            continue;
        }

        if (buf->state == UVC_BUF_STATE_READY)
        {
            static __u32 st = 0, complete_cnt = 0, lost_cnt = 0;
            if( buf->buf.length == buf->buf.bytesused )
            {
#if 1
                complete_cnt++;
                if( esKRNL_TimeGet() - st >= 100 )
                {
                    __log("fps:(%d,%d)\n", complete_cnt, lost_cnt);
                    st = esKRNL_TimeGet();
                    complete_cnt = 0;
                    lost_cnt = 0;
                }
#endif
                if( stream->dev->exchange_buf )
                        stream->dev->exchange_buf((__u32*)(&buf->buf.mem_buf), NULL, NULL);
            }
            else
            {
                lost_cnt++;
            }
            buf->state         = UVC_BUF_STATE_ACTIVE;
            buf->error         = 0;
            buf->buf.bytesused = 0;
        }
    }

}

#endif

static void uvc_video_complete(struct urb *urb)
{
    struct uvc_streaming *stream = urb->context;
//  struct uvc_video_queue *queue = &stream->queue;
    struct uvc_buffer *buf = NULL;
    unsigned long flags;
    int ret;

    switch (urb->status) {
    case 0:
        break;
    case -ECONNRESET:
        //hal_log_err("Disconnect USB CAMERA\n", urb->status);
        return;
    default:
        hal_log_err("Non-zero status (%d) in video completion handler.\n", urb->status);
        break;

//  case -ENOENT:       /* usb_kill_urb() called. */
//      if (stream->frozen)
//          return;
//
//  case -ECONNRESET:   /* usb_unlink_urb() called. */
//  case -ESHUTDOWN:    /* The endpoint is being disabled. */
//      uvc_queue_cancel(queue, urb->status == -ESHUTDOWN);
//      return;
    }

//  spin_lock_irqsave(&queue->irqlock, flags);
//  if (!list_empty(&queue->irqqueue))
//      buf = list_first_entry(&queue->irqqueue, struct uvc_buffer,
//                     queue);
//  spin_unlock_irqrestore(&queue->irqlock, flags);
//
//  stream->decode(urb, stream, buf);

#if 0
    esKRNL_QPost(stream->dev->msg, (void *)urb);
#else
    stream->decode(urb, stream, &stream->buf);
#endif

    if ((ret = usb_submit_urb(urb, 0)) < 0) {
        hal_log_err("Failed to resubmit video URB (%d).\n", ret);
    }

}

/*
 * Free transfer buffers.
 */
static void uvc_free_urb_buffers(struct uvc_streaming *stream)
{
    unsigned int i;

    //for (i = 0; i < UVC_URBS; ++i) {
    //  if (stream->urb_buffer[i]) {
    //      esMEMS_Pfree(stream->urb_buffer[i], stream->urb_size>>10);//esMEMS_Mfree(0, stream->urb_buffer[i]);//usb_free_coherent(stream->dev->udev, stream->urb_size,stream->urb_buffer[i], stream->urb_dma[i]);
    //      stream->urb_buffer[i] = NULL;
    //  }
    //}

    stream->urb_size = 0;
}

/*
 * Allocate transfer buffers. This function can be called with buffers
 * already allocated when resuming from suspend, in which case it will
 * return without touching the buffers.
 *
 * Limit the buffer size to UVC_MAX_PACKETS bulk/isochronous packets. If the
 * system is too low on memory try successively smaller numbers of packets
 * until allocation succeeds.
 *
 * Return the number of allocated packets on success or 0 when out of memory.
 */
static int uvc_alloc_urb_buffers(struct uvc_streaming *stream,
    unsigned int size, unsigned int psize, /*gfp_t*/__s32 gfp_flags)
{
    unsigned int npackets;
    unsigned int i;

    /* Buffers are already allocated, bail out. */
    if (stream->urb_size)
        return stream->urb_size / psize;

    /* Compute the number of packets. Bulk endpoints might transfer UVC
     * payloads across multiple URBs.
     */
    npackets = (((size) + (psize) - 1) / (psize));//DIV_ROUND_UP(size, psize);
    if (npackets > UVC_MAX_PACKETS)
        npackets = UVC_MAX_PACKETS;

    hal_log_info("size=%d, psize=%d, npackets=%d\n", size, psize, npackets);

    /* Retry allocations until one succeed. */
    for (; npackets >= 1; npackets /= 2) {
        for (i = 0; i < UVC_URBS; ++i) {
            stream->urb_size = psize * npackets;
            if( stream->urb_size > UVC_MAX_PACKETS*3 ) {
                hal_log_info("must modify memory of setting\n");
            }
            stream->urb_buffer[i] = (char*)stream->dev->urb_mem[i];//esMEMS_Palloc(stream->urb_size>>10, 0);
            memset(stream->urb_buffer[i], 0xAA, stream->urb_size);
            if (!stream->urb_buffer[i]) {
                hal_log_err("hal_malloc fail\n");
                uvc_free_urb_buffers(stream);
                break;
            }
        }

        if (i == UVC_URBS) {
            hal_log_info("Allocated %u URB buffers of %ux%u bytes each.\n", UVC_URBS, npackets, psize);
            return npackets;
        }
    }

    hal_log_err("Failed to allocate URB buffers (%u bytes per packet).\n", psize);
    return 0;
}

/*
 * Uninitialize isochronous/bulk URBs and free transfer buffers.
 */
static void uvc_uninit_video(struct uvc_streaming *stream, __s32 free_buffers)
{
    struct urb *urb;
    __u32 i;

    for (i = 0; i < UVC_URBS; ++i) {
        urb = stream->urb[i];
        if (urb == NULL)
            continue;

        usb_kill_urb(urb);
        usb_free_urb(urb);
        stream->urb[i] = NULL;
    }

    if (free_buffers)
        uvc_free_urb_buffers(stream);
}

/*
 * Initialize isochronous URBs and allocate transfer buffers. The packet size
 * is given by the endpoint.
 */
static int uvc_init_video_isoc(struct uvc_streaming *stream,
    struct usb_host_virt_endpoint *ep, /*gfp_t*/__s32 gfp_flags)
{
    struct urb *urb = NULL;
    __u32 npackets = 0, i = 0, j = 0;
    __u16 psize = 0;
    __u32 size = 0;

    psize = le16_to_cpu(ep->desc.wMaxPacketSize);
    psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
    size = stream->ctrl.dwMaxVideoFrameSize;

    hal_log_info("ISO MaxVideoFrameSize=%d, wMaxPacketSize=%d, %d\n", size, ep->desc.wMaxPacketSize, psize);
    npackets = uvc_alloc_urb_buffers(stream, size, psize, gfp_flags);
    if (npackets == 0) {
        return -ENOMEM;
    }

    size = npackets * psize;

    for (i = 0; i < UVC_URBS; ++i) {
        urb = usb_alloc_urb(npackets/*, gfp_flags*/);
        if (urb == NULL) {
            uvc_uninit_video(stream, 1);
            return -ENOMEM;
        }

        urb->dev = stream->dev->pusb_dev;
        urb->context = stream;
        urb->pipe = usb_rcvisocpipe(stream->dev->pusb_dev,
                ep->desc.bEndpointAddress);
        urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
        urb->interval = ep->desc.bInterval;
        urb->transfer_buffer = stream->urb_buffer[i];
        urb->transfer_dma = 0;//stream->urb_dma[i];
        urb->complete = uvc_video_complete;
        urb->number_of_packets = npackets;
        urb->transfer_buffer_length = size;

        for (j = 0; j < npackets; ++j) {
            urb->iso_frame_desc[j].offset = j * psize;
            urb->iso_frame_desc[j].length = psize;
        }

//      urb->iso_index = i;
        stream->urb[i] = urb;
    }

    stream->dev->active_buf = uvc_video_buffer_init;

    return 0;
}

/*
 * Initialize bulk URBs and allocate transfer buffers. The packet size is
 * given by the endpoint.
 */
static int uvc_init_video_bulk(struct uvc_streaming *stream,
    struct usb_host_virt_endpoint *ep, /*gfp_t*/__s32 gfp_flags)
{
    struct urb *urb;
    unsigned int npackets, pipe, i;
    u16 psize;
    u32 size;

    psize = le16_to_cpu(ep->desc.wMaxPacketSize) & 0x07ff;
    size = stream->ctrl.dwMaxPayloadTransferSize;
    stream->bulk.max_payload_size = size;

    __wrn("BULK MaxVideoFrameSize=%d\n", size);

    npackets = uvc_alloc_urb_buffers(stream, size, psize, gfp_flags);
    if (npackets == 0)
        return -ENOMEM;

    size = npackets * psize;

    if (usb_endpoint_dir_in(&ep->desc))
        pipe = usb_rcvbulkpipe(stream->dev->pusb_dev,
                       ep->desc.bEndpointAddress);
    else
        pipe = usb_sndbulkpipe(stream->dev->pusb_dev,
                       ep->desc.bEndpointAddress);

    if (stream->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
        size = 0;

    for (i = 0; i < UVC_URBS; ++i) {
        urb = usb_alloc_urb(0/*, gfp_flags*/);
        if (urb == NULL) {
            uvc_uninit_video(stream, 1);
            return -ENOMEM;
        }

        usb_fill_bulk_urb(urb, stream->dev->pusb_dev, pipe,
            stream->urb_buffer[i], size, uvc_video_complete,
            stream);
        urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
        urb->transfer_dma = 0;//stream->urb_dma[i];

        stream->urb[i] = urb;
    }

    return 0;
}

/*
 * Initialize isochronous/bulk URBs and allocate transfer buffers.
 */
static __s32 uvc_init_video(struct uvc_streaming *stream, /*gfp_t*/__s32 gfp_flags)
{
    struct usb_interface *intf = stream->intf;
    struct usb_host_virt_endpoint *ep;
    __u32 i;
    __s32 ret;

    stream->sequence = -1;
    stream->last_fid = -1;
    stream->bulk.header_size = 0;
    stream->bulk.skip_payload = 0;
    stream->bulk.payload_size = 0;

    if (intf->num_altsetting > 1) {
        struct usb_host_virt_endpoint *best_ep = NULL;
        __u32 best_psize = 3 * 1024;
        __u32 bandwidth;
        __u32 altsetting;//uninitialized_var(altsetting);
        __s32 intfnum = stream->intfnum;

        /* Isochronous endpoint, select the alternate setting. */
        bandwidth = stream->ctrl.dwMaxPayloadTransferSize;

        if (bandwidth == 0) {
            hal_log_err("Device requested null bandwidth, defaulting to lowest.\n");
            bandwidth = 1;
        } else {
            hal_log_err("Device requested %u B/frame bandwidth.\n", bandwidth);
        }

        for (i = 0; i < intf->num_altsetting; ++i) {
            struct usb_host_virt_interface *alts;
            unsigned int psize;

            alts = &intf->altsetting[i];
//          hal_log_info("stream->header.bEndpointAddress:%d\n", stream->header.bEndpointAddress);
            ep = uvc_find_endpoint(alts, stream->header.bEndpointAddress);
            if (ep == NULL) {
                continue;
            }

            /* Check if the bandwidth is high enough. */
            psize = le16_to_cpu(ep->desc.wMaxPacketSize);
            psize = (psize & 0x07ff) * (1 + ((psize >> 11) & 3));
            if (psize >= bandwidth && psize <= best_psize) {
                altsetting = i;
                best_psize = psize;
                best_ep = ep;
            }
        }

        if (best_ep == NULL) {
            hal_log_err("No fast enough alt setting for requested bandwidth.\n");
            return -EIO;
        }

        hal_log_info("Selecting alternate setting %u (%u B/frame bandwidth).\n", altsetting, best_psize);
        ret = usb_set_interface(stream->dev->pusb_dev, intfnum, altsetting);
        if (ret < 0) {
            return ret;
        }

        hal_log_info("UVC ISO!\n");
        ret = uvc_init_video_isoc(stream, best_ep, gfp_flags);
    } else {
        /* Bulk endpoint, proceed to URB initialization. */
        ep = uvc_find_endpoint(&intf->altsetting[0],
                stream->header.bEndpointAddress);
        if (ep == NULL)
            return -EIO;

        hal_log_err("UVC BULK!\n");
        ret = uvc_init_video_bulk(stream, ep, gfp_flags);
    }

    if (ret < 0)
        return ret;

    /* Submit the URBs. */
    for (i = 0; i < UVC_URBS; ++i) {
        hal_log_info("submit video URB i:%d\n",i);
        ret = usb_submit_urb(stream->urb[i], gfp_flags);
        if (ret < 0) {
            hal_log_err("Failed to submit URB %u (%d).\n", i, ret);
            uvc_uninit_video(stream, 1);
            return ret;
        }
    }

    return 0;
}

/* --------------------------------------------------------------------------
 * Suspend/resume
 */

/*
 * Stop streaming without disabling the video queue.
 *
 * To let userspace applications resume without trouble, we must not touch the
 * video buffers in any way. We mark the device as frozen to make sure the URB
 * completion handler won't try to cancel the queue when we kill the URBs.
 */
__s32 uvc_video_suspend(struct uvc_streaming *stream)
{
#if 0
    if (!uvc_queue_streaming(&stream->queue))
        return 0;

    stream->frozen = 1;
    uvc_uninit_video(stream, 0);
    usb_set_interface(stream->dev->udev, stream->intfnum, 0);
#else
    usb_set_interface(stream->dev->pusb_dev, stream->intfnum, 0);
    esKRNL_TimeDly(50);
    uvc_uninit_video(stream, 0);
#endif
    return 0;
}

/*
 * Reconfigure the video interface and restart streaming if it was enabled
 * before suspend.
 *
 * If an error occurs, disable the video queue. This will wake all pending
 * buffers, making sure userspace applications are notified of the problem
 * instead of waiting forever.
 */
__s32 uvc_video_resume(struct uvc_streaming *stream)
{
#if 0
    int ret;

    stream->frozen = 0;

    ret = uvc_commit_video(stream, &stream->ctrl);
    if (ret < 0) {
        uvc_queue_enable(&stream->queue, 0);
        return ret;
    }

    if (!uvc_queue_streaming(&stream->queue))
        return 0;

    ret = uvc_init_video(stream, GFP_NOIO);
    if (ret < 0)
        uvc_queue_enable(&stream->queue, 0);

    return ret;
#else
    int ret;

    ret = uvc_commit_video(stream, &stream->ctrl);
    if (ret < 0) {
        hal_log_err("Commit the streaming parameters fail\n");
        return ret;
    }
    ret = uvc_init_video(stream, 0);
#endif
    return 0;
}

/* ------------------------------------------------------------------------
 * Video device
 */

/*
 * Initialize the UVC video device by switching to alternate setting 0 and
 * retrieve the default format.
 *
 * Some cameras (namely the Fuji Finepix) set the format and frame
 * indexes to zero. The UVC standard doesn't clearly make this a spec
 * violation, so try to silently fix the values if possible.
 *
 * This function is called before registering the device with V4L.
 */
int uvc_video_init(struct uvc_streaming *stream)
{
    struct uvc_streaming_control *probe = &stream->ctrl;
    struct uvc_format *format = NULL;
    struct uvc_frame *frame = NULL;
    __u32 i;
    __s32 ret;

    if( stream == NULL )
    {
        hal_log_err("ERR: input error for uvc_streaming!\n");
        return -EINVAL;
    }

    if (stream->nformats == 0) {
        hal_log_err("No supported video formats found.\n");
        return -EINVAL;
    }

//  atomic_set(&stream->active, 0);
//
//  /* Initialize the video buffers queue. */
//  uvc_queue_init(&stream->queue, stream->type, !uvc_no_drop_param);

    /* Alternate setting 0 should be the default, yet the XBox Live Vision
     * Cam (and possibly other devices) crash or otherwise misbehave if
     * they don't receive a SET_INTERFACE request before any other video
     * control request.
     */
    usb_set_interface(stream->dev->pusb_dev, stream->intfnum, 0);

    /* Set the streaming probe control with default streaming parameters
     * retrieved from the device. Webcams that don't suport GET_DEF
     * requests on the probe control will just keep their current streaming
     * parameters.
     */
    if (uvc_get_video_ctrl(stream, probe, 1, UVC_GET_DEF) == 0) {
        uvc_set_video_ctrl(stream, probe, 1);
    }

    /* Initialize the streaming parameters with the probe control current
     * value. This makes sure SET_CUR requests on the streaming commit
     * control will always use values retrieved from a successful GET_CUR
     * request on the probe control, as required by the UVC specification.
     */
    ret = uvc_get_video_ctrl(stream, probe, 1, UVC_GET_CUR);
    if (ret < 0) {
        return ret;
    }

    /* Check if the default format descriptor exists. Use the first
     * available format otherwise.
     */
    for (i = stream->nformats; i > 0; --i) {
        format = &stream->format[i-1];
        if (format->index == probe->bFormatIndex)
            break;
    }

    if (format->nframes == 0) {
        hal_log_err("No frame descriptor found for the default format.\n");
        return -EINVAL;
    }

    /* Zero bFrameIndex might be correct. Stream-based formats (including
     * MPEG-2 TS and DV) do not support frames but have a dummy frame
     * descriptor with bFrameIndex set to zero. If the default frame
     * descriptor is not found, use the first available frame.
     */
    for (i = format->nframes; i > 0; --i) {
        frame = &format->frame[i-1];
        if (frame->bFrameIndex == probe->bFrameIndex)
            break;
    }

    probe->bFormatIndex = format->index;
    probe->bFrameIndex = frame->bFrameIndex;

    stream->cur_format = format;
    stream->cur_frame = frame;

    //hal_log_err("=============== cur_format =========================\n");
    //hal_log_err("                type       = %d                     \n",stream->cur_format->type);
    //hal_log_err("                index      = %d                     \n",stream->cur_format->index);
    //hal_log_err("                colorspace = %d                     \n",stream->cur_format->colorspace);
    //hal_log_err("                fcc        = %c%c%c%c               \n",stream->cur_format->fcc,stream->cur_format->fcc>>8,stream->cur_format->fcc>>16,stream->cur_format->fcc>>24);
    //hal_log_err("                flags      = %d                     \n",stream->cur_format->flags);
    //hal_log_err("                name       = %s                     \n",stream->cur_format->name);
    //hal_log_err("=============== cur_format =========================\n\n");
    //hal_log_err("=============== uvc_frame ==========================\n");
    //hal_log_err("                bFrameIndex               = %d      \n",stream->cur_frame->bFrameIndex);
    //hal_log_err("                bmCapabilities            = %d      \n",stream->cur_frame->bmCapabilities);
    //hal_log_err("                wWidth                    = %d      \n",stream->cur_frame->wWidth);
    //hal_log_err("                wHeight                   = %d      \n",stream->cur_frame->wHeight);
    //hal_log_err("                dwMaxBitRate              = %d      \n",stream->cur_frame->dwMaxBitRate);
    //hal_log_err("                dwMaxVideoFrameBufferSize = %d      \n",stream->cur_frame->dwMaxVideoFrameBufferSize);
    //hal_log_err("                bFrameIntervalType     -  = %d      \n",stream->cur_frame->bFrameIntervalType);
    //hal_log_err("                dwDefaultFrameInterval    = %d      \n",stream->cur_frame->dwDefaultFrameInterval);
    //hal_log_err("                dwFrameInterval        -  = %d      \n",stream->cur_frame->dwFrameInterval[0]);
    //hal_log_err("=============== uvc_frame ==========================\n\n");

    hal_log_err("num_altsetting=%d\n", stream->intf->num_altsetting);
    /* Select the video decoding function */
    if (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
        if (stream->dev->quirks & UVC_QUIRK_BUILTIN_ISIGHT)
            hal_log_err("VIDEO_CAPTURE don't support decode for UVC_QUIRK_BUILTIN_ISIGHT\n");//stream->decode = uvc_video_decode_isight;
        else if (stream->intf->num_altsetting > 1)
            stream->decode = uvc_video_decode_isoc;
        else
            hal_log_err("VIDEO_CAPTURE don't support decode for bulk(stream->intf->num_altsetting <= 1)\n");//stream->decode = uvc_video_decode_bulk;
    } else {
        if (stream->intf->num_altsetting == 1)
            hal_log_err("NOT VIDEO_CAPTURE don't support decode for bulk(stream->intf->num_altsetting == 1)\n");//stream->decode = uvc_video_encode_bulk;
        else {
            hal_log_err("Isochronous endpoints are not supported for video output devices.\n");
            return -EINVAL;
        }
    }

    return 0;
}

#if 0
static void usbWebcamThread(void *p_arg)
{
    struct uvc_streaming *usbWebcam = (struct uvc_streaming *)p_arg;
    int ret;
    __u8 err;
    struct urb *urb;

    while(1){
        if(USB_OS_THREAD_DELREQ(EXEC_prioself) == OS_TASK_DEL_REQ)
        {
            hal_log_err("delete usbWebcamThread task!\n");
            break;
        }

        urb = esKRNL_QPend(usbWebcam->dev->msg, 0, &err);
        if(err!= OS_NO_ERR)
        {
            __wrn("Try to get message from urb failed! Error type:%d\n", err);
        }
        if( urb->status < 0 || urb->actual_length == 0 )
        {
            hal_log_err("urb error status=0x%x, actual_length=%d\n", urb->status, urb->actual_length);
        }
        else
        {
            usbWebcam->decode(urb, usbWebcam, &usbWebcam->buf);
        }

        __msg("submit urb addr=0x%x\n", urb);

        if ((ret = usb_submit_urb(urb, 0)) < 0) {
            hal_log_err("Failed to resubmit video URB (%d).\n", ret);
        }
    }
    USB_OS_THREAD_DELETE(EXEC_prioself);
}
#endif

/*
 * Enable or disable the video stream.
 */
int uvc_video_enable(struct uvc_streaming *stream, __s32 enable)
{
    int ret;
    __u8 err = 0;
#if 0
    if( enable )
    {
        if( stream->dev->msg ==NULL )
        {
            stream->dev->msg = esKRNL_QCreate(UVC_URBS);
            if(stream->dev->msg == NULL){
                hal_log_err("ERR: esKRNL_QCreate msg failed\n");
            }
        }
        if( stream->dev->webcamThdId == NULL )
        {
            stream->dev->webcamThdId = UsbCreateThread((void *)usbWebcamThread, (void *)stream, 0x400,  THREAD_LEVEL_HID_CLIENT);
            if(stream->dev->webcamThdId == OS_NO_ERR)
            {
                hal_log_err("ERR: create usbMouseThd failed\n");
            }
        }
    }
    else
    {
        /* kill thread */
        if( stream->dev->webcamThdId )
        {
            err = USB_OS_THREAD_DELREQ(stream->dev->webcamThdId);
            while(err != OS_TASK_NOT_EXIST)
            {
                hal_log_err("wait for delete usbMouseThd!\n");
                esKRNL_TimeDlyResume(stream->dev->webcamThdId);
                err = USB_OS_THREAD_DELREQ(stream->dev->webcamThdId);
                esKRNL_TimeDly(1);
            }
            stream->dev->webcamThdId = 0;
        }
        if( stream->dev->msg )
        {
            esKRNL_QDel(stream->dev->msg, 0, &err);
            stream->dev->msg = NULL;
        }
    }
#endif
    if (!enable) {
        uvc_uninit_video(stream, 1);
        usb_set_interface(stream->dev->pusb_dev, stream->intfnum, 0);
//      uvc_queue_enable(&stream->queue, 0);
        return 0;
    }

    hal_log_err("=============== cur_format =========================\n");
    hal_log_err("                type       = %d                     \n",stream->cur_format->type);
    hal_log_err("                index      = %d                     \n",stream->cur_format->index);
    hal_log_err("                bpp        = %d                     \n",stream->cur_format->bpp);
    hal_log_err("                colorspace = %d                     \n",stream->cur_format->colorspace);
    hal_log_err("                fcc        = %c%c%c%c               \n",stream->cur_format->fcc,stream->cur_format->fcc>>8,stream->cur_format->fcc>>16,stream->cur_format->fcc>>24);
    hal_log_err("                flags      = %d                     \n",stream->cur_format->flags);
    hal_log_err("                name       = %s                     \n",stream->cur_format->name);
    hal_log_err("                nframes    = %d                     \n",stream->cur_format->nframes);
    hal_log_err("=============== cur_format =========================\n\n");
    hal_log_err("=============== uvc_frame ==========================\n");
    hal_log_err("                bFrameIndex               = %d      \n",stream->cur_frame->bFrameIndex);
    hal_log_err("                bmCapabilities            = %d      \n",stream->cur_frame->bmCapabilities);
    hal_log_err("                wWidth                    = %d      \n",stream->cur_frame->wWidth);
    hal_log_err("                wHeight                   = %d      \n",stream->cur_frame->wHeight);
    hal_log_err("                dwMaxBitRate              = %d Mbps \n",stream->cur_frame->dwMaxBitRate/1024/1024);
    hal_log_err("                dwMaxVideoFrameBufferSize = 0x%x    \n",stream->cur_frame->dwMaxVideoFrameBufferSize);
    hal_log_err("                bFrameIntervalType     -  = %d      \n",stream->cur_frame->bFrameIntervalType);
    hal_log_err("                dwDefaultFrameInterval    = %d      \n",stream->cur_frame->dwDefaultFrameInterval);
    hal_log_err("                dwFrameInterval        -  = %d      \n",stream->cur_frame->dwFrameInterval[0]);
    hal_log_err("=============== uvc_frame ==========================\n\n");

//  ret = uvc_queue_enable(&stream->queue, 1);
//  if (ret < 0)
//      return ret;

    /* Commit the streaming parameters. */
    ret = uvc_commit_video(stream, &stream->ctrl);
    if (ret < 0) {
//      uvc_queue_enable(&stream->queue, 0);
        hal_log_err("Commit the streaming parameters fail\n");
        return ret;
    }

    return uvc_init_video(stream, 0/*GFP_KERNEL*/);
}

