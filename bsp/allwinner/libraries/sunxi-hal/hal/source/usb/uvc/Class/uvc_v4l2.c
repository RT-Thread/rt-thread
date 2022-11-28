/*
********************************************************************************
*                                USB UVC Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  uvc_v4l2.c
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



/* ------------------------------------------------------------------------
 * V4L2 interface
 */

/*
 * Find the frame interval closest to the requested frame interval for the
 * given frame format and size. This should be done by the device as part of
 * the Video Probe and Commit negotiation, but some hardware don't implement
 * that feature.
 */
static __u32 uvc_try_frame_interval(struct uvc_frame *frame, __u32 interval)
{
    __u32 i;

    if (frame->bFrameIntervalType) {
        __u32 best = -1, dist;

        for (i = 0; i < frame->bFrameIntervalType; ++i) {
            dist = interval > frame->dwFrameInterval[i]
                 ? interval - frame->dwFrameInterval[i]
                 : frame->dwFrameInterval[i] - interval;

            if (dist > best)
                break;

            best = dist;
        }

        interval = frame->dwFrameInterval[i-1];
    } else {
        const __u32 min = frame->dwFrameInterval[0];
        const __u32 max = frame->dwFrameInterval[1];
        const __u32 step = frame->dwFrameInterval[2];

        interval = min + (interval - min + step/2) / step * step;
        if (interval > max)
            interval = max;
    }

    return interval;
}

static int uvc_v4l2_try_format(struct uvc_streaming *stream,
    struct v4l2_format *fmt, struct uvc_streaming_control *probe,
    struct uvc_format **uvc_format, struct uvc_frame **uvc_frame)
{
    struct uvc_format *format = NULL;
    struct uvc_frame *frame = NULL;
    __u16 rw, rh;
    unsigned int d, maxd;
    unsigned int i;
    __u32 interval;
    int ret = 0;
    __u8 *fcc;

    if (fmt->type != stream->type)
        return -EINVAL;

    fcc = (__u8 *)&fmt->fmt.pix.pixelformat;
    hal_log_info("Trying format 0x%08x (%c%c%c%c): %ux%u.\n",
            fmt->fmt.pix.pixelformat,
            fcc[0], fcc[1], fcc[2], fcc[3],
            fmt->fmt.pix.width, fmt->fmt.pix.height);

    /* Check if the hardware supports the requested format. */
    for (i = 0; i < stream->nformats; ++i) {
        format = &stream->format[i];
        if (format->fcc == fmt->fmt.pix.pixelformat)
            break;
    }

    if (format == NULL || format->fcc != fmt->fmt.pix.pixelformat) {
        hal_log_err("Unsupported format 0x%08x.\n",
                fmt->fmt.pix.pixelformat);
        return -EINVAL;
    }

    /* Find the closest image size. The distance between image sizes is
     * the size in pixels of the non-overlapping regions between the
     * requested size and the frame-specified size.
     */
    rw = fmt->fmt.pix.width;
    rh = fmt->fmt.pix.height;
    maxd = (unsigned int)-1;

    for (i = 0; i < format->nframes; ++i) {
        __u16 w = format->frame[i].wWidth;
        __u16 h = format->frame[i].wHeight;

        d = min(w, rw) * min(h, rh);
        d = w*h + rw*rh - 2*d;
        if (d < maxd) {
            maxd = d;
            frame = &format->frame[i];
        }

        if (maxd == 0)
            break;
    }

    if (frame == NULL) {
        hal_log_err("Unsupported size %ux%u.\n",
                fmt->fmt.pix.width, fmt->fmt.pix.height);
        return -EINVAL;
    }

    /* Use the default frame interval. */
    interval = frame->dwDefaultFrameInterval;
    hal_log_info("Using default frame interval %u.%u us "
        "(%u.%u fps).\n", interval/10, interval%10, 10000000/interval,
        (100000000/interval)%10);

    /* Set the format index, frame index and frame interval. */
    memset(probe, 0, sizeof *probe);
    probe->bmHint = 1;  /* dwFrameInterval */
    probe->bFormatIndex = format->index;
    probe->bFrameIndex = frame->bFrameIndex;
    probe->dwFrameInterval = uvc_try_frame_interval(frame, interval);
    /* Some webcams stall the probe control set request when the
     * dwMaxVideoFrameSize field is set to zero. The UVC specification
     * clearly states that the field is read-only from the host, so this
     * is a webcam bug. Set dwMaxVideoFrameSize to the value reported by
     * the webcam to work around the problem.
     *
     * The workaround could probably be enabled for all webcams, so the
     * quirk can be removed if needed. It's currently useful to detect
     * webcam bugs and fix them before they hit the market (providing
     * developers test their webcams with the Linux driver as well as with
     * the Windows driver).
     */
//  mutex_lock(&stream->mutex);
    if (stream->dev->quirks & UVC_QUIRK_PROBE_EXTRAFIELDS)
        probe->dwMaxVideoFrameSize =
            stream->ctrl.dwMaxVideoFrameSize;

    /* Probe the device. */
    ret = uvc_probe_video(stream, probe);
//  mutex_unlock(&stream->mutex);
    if (ret < 0)
        goto done_try_format;

    fmt->fmt.pix.width = frame->wWidth;
    fmt->fmt.pix.height = frame->wHeight;
    fmt->fmt.pix.field = V4L2_FIELD_NONE;
    fmt->fmt.pix.bytesperline = format->bpp * frame->wWidth / 8;
    fmt->fmt.pix.sizeimage = probe->dwMaxVideoFrameSize;
    fmt->fmt.pix.colorspace = format->colorspace;
    fmt->fmt.pix.priv = 0;

    if (uvc_format != NULL)
        *uvc_format = format;
    if (uvc_frame != NULL)
        *uvc_frame = frame;

done_try_format:
    return ret;
}

static int uvc_v4l2_get_format(struct uvc_streaming *stream,
    struct v4l2_format *fmt)
{
    struct uvc_format *format;
    struct uvc_frame *frame;
    int ret = 0;

    if (fmt->type != stream->type)
        return -EINVAL;

//  mutex_lock(&stream->mutex);
    format = stream->cur_format;
    frame = stream->cur_frame;

    if (format == NULL || frame == NULL) {
        ret = -EINVAL;
        goto done_get_format;
    }

    fmt->fmt.pix.pixelformat = format->fcc;
    fmt->fmt.pix.width = frame->wWidth;
    fmt->fmt.pix.height = frame->wHeight;
    fmt->fmt.pix.field = V4L2_FIELD_NONE;
    fmt->fmt.pix.bytesperline = format->bpp * frame->wWidth / 8;
    fmt->fmt.pix.sizeimage = stream->ctrl.dwMaxVideoFrameSize;
    fmt->fmt.pix.colorspace = format->colorspace;
    fmt->fmt.pix.priv = 0;

done_get_format:
//  mutex_unlock(&stream->mutex);
    return ret;
}

static int uvc_v4l2_set_format(struct uvc_streaming *stream,
    struct v4l2_format *fmt)
{
    struct uvc_streaming_control probe;
    struct uvc_format *format;
    struct uvc_frame *frame;
    __s32 ret;

    if (fmt->type != stream->type)
        return -EINVAL;

    ret = uvc_v4l2_try_format(stream, fmt, &probe, &format, &frame);
    if (ret < 0)
        return ret;

//  mutex_lock(&stream->mutex);

//  if (uvc_queue_allocated(&stream->queue)) {
//      ret = -EBUSY;
//      goto done;
//  }

    memcpy(&stream->ctrl, &probe, sizeof probe);
    stream->cur_format = format;
    stream->cur_frame = frame;

//done:
//  mutex_unlock(&stream->mutex);
    return ret;
}

static __s32 uvc_v4l2_get_streamparm(struct uvc_streaming *stream,
        struct v4l2_streamparm *parm)
{
    __u32 numerator, denominator;

    if (parm->type != stream->type)
        return -EINVAL;

//  mutex_lock(&stream->mutex);
    numerator = stream->ctrl.dwFrameInterval;
//  mutex_unlock(&stream->mutex);

    denominator = 10000000;
    uvc_simplify_fraction(&numerator, &denominator, 8, 333);

    memset(parm, 0, sizeof *parm);
    parm->type = stream->type;

    if (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
        parm->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
        parm->parm.capture.capturemode = 0;
        parm->parm.capture.timeperframe.numerator = numerator;
        parm->parm.capture.timeperframe.denominator = denominator;
        parm->parm.capture.extendedmode = 0;
        parm->parm.capture.readbuffers = 0;
    } else {
        parm->parm.output.capability = V4L2_CAP_TIMEPERFRAME;
        parm->parm.output.outputmode = 0;
        parm->parm.output.timeperframe.numerator = numerator;
        parm->parm.output.timeperframe.denominator = denominator;
    }

    return 0;
}

static __s32 uvc_v4l2_set_streamparm(struct uvc_streaming *stream,
        struct v4l2_streamparm *parm)
{
    struct uvc_streaming_control probe;
    struct v4l2_fract timeperframe;
    __u32 interval;
    __s32 ret;

    if (parm->type != stream->type)
        return -EINVAL;

    if (parm->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
        timeperframe = parm->parm.capture.timeperframe;
    else
        timeperframe = parm->parm.output.timeperframe;

    interval = uvc_fraction_to_interval(timeperframe.numerator,
        timeperframe.denominator);
    hal_log_err("Setting frame interval to %u/%u (%u).\n",
        timeperframe.numerator, timeperframe.denominator, interval);

//  mutex_lock(&stream->mutex);

//  if (uvc_queue_streaming(&stream->queue)) {
//      mutex_unlock(&stream->mutex);
//      return -EBUSY;
//  }

    memcpy(&probe, &stream->ctrl, sizeof probe);
    probe.dwFrameInterval =
        uvc_try_frame_interval(stream->cur_frame, interval);

    /* Probe the device with the new settings. */
    ret = uvc_probe_video(stream, &probe);
    if (ret < 0) {
//      mutex_unlock(&stream->mutex);
        return ret;
    }

    memcpy(&stream->ctrl, &probe, sizeof probe);
//  mutex_unlock(&stream->mutex);

    /* Return the actual frame period. */
    timeperframe.numerator = probe.dwFrameInterval;
    timeperframe.denominator = 10000000;
    uvc_simplify_fraction(&timeperframe.numerator,
        &timeperframe.denominator, 8, 333);

    if (parm->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
        parm->parm.capture.timeperframe = timeperframe;
    else
        parm->parm.output.timeperframe = timeperframe;

    return 0;
}

/* ------------------------------------------------------------------------
 * Privilege management
 */

/*
 * Privilege management is the multiple-open implementation basis. The current
 * implementation is completely transparent for the end-user and doesn't
 * require explicit use of the VIDIOC_G_PRIORITY and VIDIOC_S_PRIORITY ioctls.
 * Those ioctls enable finer control on the device (by making possible for a
 * user to request exclusive access to a device), but are not mature yet.
 * Switching to the V4L2 priority mechanism might be considered in the future
 * if this situation changes.
 *
 * Each open instance of a UVC device can either be in a privileged or
 * unprivileged state. Only a single instance can be in a privileged state at
 * a given time. Trying to perform an operation that requires privileges will
 * automatically acquire the required privileges if possible, or return -EBUSY
 * otherwise. Privileges are dismissed when closing the instance or when
 * freeing the video buffers using VIDIOC_REQBUFS.
 *
 * Operations that require privileges are:
 *
 * - VIDIOC_S_INPUT
 * - VIDIOC_S_PARM
 * - VIDIOC_S_FMT
 * - VIDIOC_REQBUFS
 */
static int uvc_acquire_privileges(struct uvc_fh *handle)
{
    /* Always succeed if the handle is already privileged. */
    if (handle->state == UVC_HANDLE_ACTIVE)
        return 0;

//  /* Check if the device already has a privileged handle. */
//  if (atomic_inc_return(&handle->stream->active) != 1) {
//      atomic_dec(&handle->stream->active);
//      return -EBUSY;
//  }

    handle->state = UVC_HANDLE_ACTIVE;
    return 0;
}

static void uvc_dismiss_privileges(struct uvc_fh *handle)
{
//  if (handle->state == UVC_HANDLE_ACTIVE)
//      atomic_dec(&handle->stream->active);

    handle->state = UVC_HANDLE_PASSIVE;
}

static int uvc_has_privileges(struct uvc_fh *handle)
{
    return handle->state == UVC_HANDLE_ACTIVE;
}
/* ------------------------------------------------------------------------
 * V4L2 file operations
 */
//1.打开设备文件
struct uvc_fh * uvc_v4l2_open(struct uvc_streaming *stream)
{
    struct uvc_fh *handle;

    /* Create the device handle. */
    handle = hal_malloc(sizeof(*handle));
    if (handle == NULL) {
        hal_log_err("esMEMS_Malloc() fail\n");
        return NULL;
    }
    hal_log_err("uvc_v4l2_open\n");

    handle->stream = stream;
    handle->state = UVC_HANDLE_PASSIVE;

    return handle;
}

//11.关闭视频设备
__s32 uvc_v4l2_release(struct uvc_fh *handle)
{
    struct uvc_streaming *stream = handle->stream;

    hal_log_err("uvc_v4l2_release\n");

    /* Only free resources if this is a privileged handle. */
//  if (uvc_has_privileges(handle))
//      uvc_video_enable(stream, 0);

    /* Release the file handle. */
    uvc_dismiss_privileges(handle);
    hal_free(handle);

    return 0;
}

__s32 uvc_v4l2_do_ioctl(struct uvc_fh *handle, unsigned int cmd, void *arg)
{
    struct uvc_streaming *stream = handle->stream;
    long ret = 0;

    hal_log_info("uvc_v4l2_do_ioctl: 0x%x\n", cmd);

    switch (cmd) {
    /* Query capabilities */
    case VIDIOC_QUERYCAP://2.取得设备的capability，看看设备具有什么功能，比如是否具有视频输入,或者音频输入输出等。
    {
//      struct v4l2_capability *cap = arg;
//
//      memset(cap, 0, sizeof *cap);
//      uvc_strlcpy(cap->driver, "uvcvideo", sizeof cap->driver);
//      uvc_strlcpy(cap->card, vdev->name, sizeof cap->card);
//      usb_make_path(stream->dev->udev,
//                cap->bus_info, sizeof(cap->bus_info));
//      cap->version = DRIVER_VERSION_NUMBER;
//      if (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
//          cap->capabilities = V4L2_CAP_VIDEO_CAPTURE
//                    | V4L2_CAP_STREAMING;
//      else
//          cap->capabilities = V4L2_CAP_VIDEO_OUTPUT
//                    | V4L2_CAP_STREAMING;
        break;
    }

    //获取当前驱动支持的视频格式
    /* Try, Get, Set & Enum format */
    case VIDIOC_ENUM_FMT:
    {
        struct v4l2_fmtdesc *fmt = arg;
        struct uvc_format *format;
        enum v4l2_buf_type type = fmt->type;
        __u32 index = fmt->index;

        if (fmt->type != stream->type ||
            fmt->index >= stream->nformats)
            return -EINVAL;

        memset(fmt, 0, sizeof(*fmt));
        fmt->index = index;
        fmt->type = type;

        format = &stream->format[fmt->index];
        fmt->flags = 0;
        if (format->flags & UVC_FMT_FLAG_COMPRESSED)
            fmt->flags |= V4L2_FMT_FLAG_COMPRESSED;
        uvc_strlcpy(fmt->description, format->name,
            sizeof fmt->description);
        fmt->description[sizeof fmt->description - 1] = 0;
        fmt->pixelformat = format->fcc;
        break;
    }
    //验证当前驱动的显示格式
    case VIDIOC_TRY_FMT:
    {
        struct uvc_streaming_control probe;

        return uvc_v4l2_try_format(stream, arg, &probe, NULL, NULL);
    }

    case VIDIOC_S_FMT://3.设置视频帧的格式个包括宽度和高度等
        if ((ret = uvc_acquire_privileges(handle)) < 0)
            return ret;

        return uvc_v4l2_set_format(stream, arg);
    //读取视频帧的格式个包括宽度和高度等
    case VIDIOC_G_FMT:
        return uvc_v4l2_get_format(stream, arg);


    /* Get & Set streaming parameters */
    case VIDIOC_G_PARM:
        return uvc_v4l2_get_streamparm(stream, arg);

    case VIDIOC_S_PARM:
        if ((ret = uvc_acquire_privileges(handle)) < 0)
            return ret;

        return uvc_v4l2_set_streamparm(stream, arg);
    //查询驱动的修剪能力
    /* Cropping and scaling */
    case VIDIOC_CROPCAP:
    {
        struct v4l2_cropcap *ccap = arg;

        if (ccap->type != stream->type)
            return -EINVAL;

        ccap->bounds.left = 0;
        ccap->bounds.top = 0;

//      mutex_lock(&stream->mutex);
        ccap->bounds.width = stream->cur_frame->wWidth;
        ccap->bounds.height = stream->cur_frame->wHeight;
//      mutex_unlock(&stream->mutex);

        ccap->defrect = ccap->bounds;

        ccap->pixelaspect.numerator = 1;
        ccap->pixelaspect.denominator = 1;
        break;
    }
    //设置视频信号的边框
    case VIDIOC_G_CROP:
    case VIDIOC_S_CROP:
        return -EINVAL;

    /* Buffers & streaming */
    case VIDIOC_REQBUFS://4.向驱动申请帧缓冲，一般不超过5个
    {
        struct v4l2_requestbuffers *rb = arg;

        if (rb->type != stream->type ||
            rb->memory != V4L2_MEMORY_MMAP)
            return -EINVAL;

        if ((ret = uvc_acquire_privileges(handle)) < 0)
            return ret;

//      mutex_lock(&stream->mutex);
//      ret = uvc_alloc_buffers(&stream->queue, rb->count,
//                  stream->ctrl.dwMaxVideoFrameSize);
//      mutex_unlock(&stream->mutex);
        if (ret < 0)
            return ret;

        if (ret == 0)
            uvc_dismiss_privileges(handle);

        rb->count = ret;
        ret = 0;
        break;
    }

    case VIDIOC_QBUF://6.将申请到的帧缓冲全部入队列，以便存放采集到的数据; 9.将缓冲重新入队列尾,这样可以循环采集
//      if (!uvc_has_privileges(handle))
//          return -EBUSY;
//
//      return uvc_queue_buffer(&stream->queue, arg);
        break;

    case VIDIOC_DQBUF://8.出队列以取得已采集数据的帧缓冲，取得原始采集数据
//      if (!uvc_has_privileges(handle))
//          return -EBUSY;
//
//      return uvc_dequeue_buffer(&stream->queue, arg,
//          file->f_flags & O_NONBLOCK);
        break;

    case VIDIOC_STREAMON://7.开始视频的采集
    {
        int type = (int)arg;

        if (type != stream->type)
        {
            hal_log_err("%d != %d\n", type, stream->type);
            return -EINVAL;
        }

        if (!uvc_has_privileges(handle))
        {
            hal_log_err("%d\n", handle->state);
            return -EBUSY;
        }

//      mutex_lock(&stream->mutex);
        ret = uvc_video_enable(stream, 1);
//      mutex_unlock(&stream->mutex);
        if (ret < 0)
            return ret;
        break;
    }

    case VIDIOC_STREAMOFF://10.停止视频的采集
    {
        int type = (int)arg;

        if (type != stream->type)
        {
            hal_log_err("%d != %d\n", type, stream->type);
            return -EINVAL;
        }

        if (!uvc_has_privileges(handle))
        {
            hal_log_err("%d\n", handle->state);
            return -EBUSY;
        }

        return uvc_video_enable(stream, 0);
    }

    default:
        hal_log_err("Unknown ioctl 0x%08x\n", cmd);
        return -EINVAL;
    }

    return ret;
}
