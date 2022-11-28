/*
********************************************************************************
*                                USB UVC Driver
*
*                (c) Copyright 2010-2015, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  usbWebcam.h
*
* Author        :  Kingvan.Tong
*
* Date          :  2013.05.17
*
* Description   :  USB Webcam
*
* Others        :  NULL
*
* History:
*       <time>      <version >      <author>            <desc>
*      2013.05.17      1.0           Kingvan.Tong       build this file
*
********************************************************************************
*/

#include  <string.h>
//#include  "usb_host_config.h"
//#include  "usb_host_base_types.h"
#include  "usb_os_platform.h"
#include  "error.h"
//#include  "misc_lib.h"
#include  "video.h"
#include  "uvcvideo.h"
#include  "usbWebcam.h"
#include  "usbWebcam_proc.h"
#include  "hal_log.h"

static struct uvc_fh *v4l2_handle = NULL;

extern struct uvc_fh * uvc_v4l2_open(struct uvc_streaming *stream);
extern __s32 uvc_v4l2_release(struct uvc_fh *handle);
extern __s32 uvc_v4l2_do_ioctl(struct uvc_fh *handle, unsigned int cmd, void *arg);


__s32 usbWebcam_v4l2_init(UVCDev_t *UVCDev)
{
    if( UVCDev->streams == NULL )
    {
        hal_log_err("usbWebcam_v4l2_init() fail\n");
        return -1;
    }
    if( v4l2_handle != NULL )
    {
        hal_log_err("usbWebcam_v4l2_init() v4l2_handle != NULL\n");
        return -1;
    }
    //1.打开设备文件
    v4l2_handle = uvc_v4l2_open(UVCDev->streams);
    hal_log_info("usbWebcam_v4l2_init()\n");
    if( v4l2_handle == NULL )
        return -1;
    else
        return 0;
}

__s32 usbWebcam_v4l2_exit(UVCDev_t *UVCDev)
{
    if( v4l2_handle == NULL )
    {
        hal_log_err("usbWebcam_v4l2_exit(), v4l2_handle == NULL\n");
        return -1;
    }
    uvc_v4l2_release(v4l2_handle);
    v4l2_handle = NULL;
    hal_log_info("usbWebcam_v4l2_exit()\n");
    return 0;
}

__s32 usbWebcam_v4l2_capture_on(UVCDev_t *UVCDev)
{
    usbWebcam_t *usbWebcam = NULL;
    struct v4l2_format fmt;

    if( v4l2_handle == NULL )
    {
        hal_log_err("usbWebcam_v4l2_capture_on(), v4l2_handle == NULL\n");
        return -1;
    }

    usbWebcam = (usbWebcam_t *)UVCDev->Extern;

    memset( &fmt, 0, sizeof(fmt) );
    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = 1280;
    fmt.fmt.pix.height      = 720;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;   //V4L2_PIX_FMT_MJPEG; V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;

    if(uvc_v4l2_do_ioctl(v4l2_handle, VIDIOC_S_FMT, &fmt) == -1)
    {
        hal_log_err("usbWebcam_v4l2_capture_on() set format fail\n");
        return-1;
    }

    hal_log_info("usbWebcam_v4l2_capture_on() type=%d\n", UVCDev->streams->type);
    return uvc_v4l2_do_ioctl(v4l2_handle, VIDIOC_STREAMON, (void*)UVCDev->streams->type);
}

__s32 usbWebcam_v4l2_capture_off(UVCDev_t *UVCDev)
{
    if( v4l2_handle == NULL )
    {
        hal_log_err("usbWebcam_v4l2_capture_off(), v4l2_handle == NULL\n");
        return -1;
    }

    hal_log_info("usbWebcam_v4l2_capture_on() type=%d\n", UVCDev->streams->type);
    return uvc_v4l2_do_ioctl(v4l2_handle, VIDIOC_STREAMOFF, (void*)UVCDev->streams->type);
}











