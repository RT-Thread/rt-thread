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
#ifndef  __USBWEBCAM_H__
#define  __USBWEBCAM_H__
#include  "usbWebcam_proc.h"

typedef struct _usbWebcam{

    UVCDev_t    *UVCDev;

    FILE        *webcamHdl;
    uvc_irq_t   uvc_irq;

    __u32       urb_mem[UVC_URBS];

}usbWebcam_t;

#endif   //__USBWEBCAM_H__

