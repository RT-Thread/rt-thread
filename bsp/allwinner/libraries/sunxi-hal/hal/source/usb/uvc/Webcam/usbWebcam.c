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
* Date          :  2013.03.26
*
* Description   :  USB Webcam
*
* Others        :  NULL
*
* History:
*       <time>      <version >      <author>            <desc>
*      2013.03.26      1.0           Kingvan.Tong       build this file
*
********************************************************************************
*/
#include  <stdio.h>
#include  <string.h>
#include  "usb_os_platform.h"
#include  "error.h"
#include  "video.h"
#include  "uvcvideo.h"
#include  "usbWebcam.h"
#include  "hal_mem.h"
#include  "hal_log.h"
#include  "drv_webcam.h"

static usbWebcam_t *g_usbWebcam = NULL;
typedef __s32 (*active_buf) (struct uvc_streaming *stream) ;

static active_buf p_func;

static __s32  transport(__u32 addr0, __u32 addr1, __u32 addr2)
{
    UVCDev_t *UVCDev = NULL;

    UVCDev = g_usbWebcam->UVCDev;

    hal_log_info("usb:(%x,%x,%x),(%x,%x,%x), %x,%x\n", addr0, addr1, addr2,
            UVCDev->frame_buf0, UVCDev->frame_buf1, UVCDev->frame_buf2, (unsigned int)UVCDev->active_buf, (unsigned int)g_usbWebcam->uvc_irq);
    if((void *)addr0 != NULL)
    {
        UVCDev->frame_len  = 640*480;
        UVCDev->exchange_buf = g_usbWebcam->uvc_irq;

        UVCDev->frame_buf0      = addr0;
        UVCDev->frame_buf1      = 0;
        UVCDev->frame_buf2      = 0;

        if(UVCDev->active_buf==NULL)
        {
            //printf("UVCDev->active_buf==NULL p_func=%x\n",p_func);
            UVCDev->active_buf = p_func;
        }
        UVCDev->active_buf(UVCDev->streams);
    }
    else
    {
        if(UVCDev->active_buf) {
            p_func = UVCDev->active_buf;
        }
        UVCDev->frame_len       = 0;
        UVCDev->active_buf      = NULL;
        UVCDev->exchange_buf    = NULL;
        UVCDev->frame_buf0      = 0;
        UVCDev->frame_buf1      = 0;
        UVCDev->frame_buf2      = 0;
        //printf("transport UVCDev->active_buf==NULL\n");
    }

    return 0;
}

__s32 usbWebcam_probe(UVCDev_t *UVCDev)
{
    usbWebcam_t *usbWebcam = NULL;
    __u8 err = 0;
    __s32 ret = 0;
    extern __s32 DRV_WEBCAM_MInit(void);
    extern __s32 DEV_WEBCAM_Ioctrl(__hdle hWebcam, __u32 cmd, __s32 aux, void *pbuffer);

    if(UVCDev == NULL || g_usbWebcam == NULL){
        hal_log_err("ERR: usbWebcamProbe: input error, 0x%x,0x%x\n", (unsigned int)UVCDev, (unsigned int)g_usbWebcam);
        return -1;
    }
    usbWebcam = g_usbWebcam;

    usbWebcam->UVCDev = UVCDev;
    UVCDev->Extern = usbWebcam;

    DRV_WEBCAM_MInit();
//  usbWebcam->webcamHdl = fopen("b:\\UVC\\WEBCAM","r+");
    if( usbWebcam->webcamHdl == NULL )
    {
        __s32 i;

        hal_log_info("don't fined drv_webcam\n");
        for( i = 0; i < UVC_URBS; ++i )
        {
            UVCDev->urb_mem[i] = usbWebcam->urb_mem[i];
        }
    } else {
        printf("%s %d %s usbWebcam->webcamHdl == NULL!\n", __FILE__, __LINE__, __func__);
    }

    usbWebcam_v4l2_init(UVCDev);

    ret = usbWebcam_v4l2_capture_on(UVCDev);

    if( usbWebcam->webcamHdl )
    {
        DEV_WEBCAM_Ioctrl(usbWebcam->webcamHdl, DRV_WENCAM_CMD_GET_IRQ_CB, 0, (void*)(&usbWebcam->uvc_irq));
        DEV_WEBCAM_Ioctrl(usbWebcam->webcamHdl, DRV_WENCAM_CMD_SET_TRANSPORT_CB, 0, (void*)transport);
        DEV_WEBCAM_Ioctrl(usbWebcam->webcamHdl, DRV_WENCAM_CMD_WEBCAM_INSERT, 0, 0);
    }

    /* Notice: 由于新的设备上来以后，系统的设备管理告知应用程序，因此只能由驱动告知应用程序 */
//  USB_OS_esKSRV_SendMsg(KMSG_USR_SYSTEM_WEBCAM_PLUGIN, KMSG_PRIO_HIGH);
    hal_log_info("webcam plug in message...\n");

    return ret;
}

void* usbWebcam_init(void)
{
    usbWebcam_t *usbWebcam = NULL;
    __u8 err = 0;
    __s32 ret = 0;

    /* 创建一个Webcam设备，并且初始化 */
    usbWebcam = (usbWebcam_t *)hal_malloc(sizeof(usbWebcam_t));
    if(usbWebcam == NULL){
        hal_log_err("ERR: hal_malloc failed\n");
        return NULL;
    }

    memset(usbWebcam, 0, sizeof(usbWebcam_t));
    g_usbWebcam = usbWebcam;
    {
        __s32 i;

        for( i = 0; i < UVC_URBS; ++i )
        {
            usbWebcam->urb_mem[i] = (__u32)hal_malloc(UVC_MAX_PACKETS*3);
            if (!usbWebcam->urb_mem[i]) {
                hal_log_info("esMEMS_Malloc fail\n");
            }
        }
    }

    return (void*)usbWebcam;

}

__s32 usbWebcam_remove(UVCDev_t * UVCDev)
{
    usbWebcam_t *usbWebcam = NULL;
    extern __s32 DEV_WEBCAM_Ioctrl(__hdle hWebcam, __u32 cmd, __s32 aux, void *pbuffer);

    if(UVCDev == NULL){
        hal_log_err("ERR: usbWebcamRemove: input error\n");
        return -1;
    }

    usbWebcam = UVCDev->Extern;
    if(usbWebcam == NULL){
        hal_log_err("ERR: usbWebcamRemove: usbWebcam == NULL\n");
        return -1;
    }

    if( usbWebcam->webcamHdl )
    {
        DEV_WEBCAM_Ioctrl(usbWebcam->webcamHdl, DRV_WENCAM_CMD_SET_TRANSPORT_CB, 0, 0);
        DEV_WEBCAM_Ioctrl(usbWebcam->webcamHdl, DRV_WENCAM_CMD_WEBCAM_MOVED, (__s32)UVCDev->frame_buf0, (void*)UVCDev->frame_buf1);
    }

//  USB_OS_esKSRV_SendMsg(KMSG_USR_SYSTEM_WEBCAM_PLUGOUT, KMSG_PRIO_HIGH);
    hal_log_info("webcam plug out message...\n");

    usbWebcam->UVCDev = NULL;
    UVCDev->Extern = NULL;

    UVCDev->exchange_buf    = NULL;
    UVCDev->frame_buf0      = 0;
    UVCDev->frame_buf1      = 0;
    UVCDev->frame_buf2      = 0;

    usbWebcam_v4l2_capture_off(UVCDev);//关中断发生器

    usbWebcam_v4l2_exit(UVCDev);

    if( usbWebcam->webcamHdl ) {
        fclose(usbWebcam->webcamHdl);
    }

    return 0;
}

__s32 usbWebcam_exit(void* arg)
{
    usbWebcam_t *usbWebcam = (usbWebcam_t *)arg;
    __u8 err = 0;


    if(usbWebcam == NULL){
        hal_log_err("ERR: usbWebcamRemove: usbWebcam == NULL\n");
        return -1;
    }

    {
        __s32 i;

        for (i = 0; i < UVC_URBS; ++i) {
            if (usbWebcam->urb_mem[i]) {
                hal_free((void*)usbWebcam->urb_mem[i]);
                usbWebcam->urb_mem[i] = 0;
            }
        }
    }

    hal_free(usbWebcam);

    return 0;
}




