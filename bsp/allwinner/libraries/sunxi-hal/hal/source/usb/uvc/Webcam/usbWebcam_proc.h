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

#ifndef __USB_WEBCAM_PROC_H__
#define __USB_WEBCAM_PROC_H__


extern __s32 usbWebcam_v4l2_init(UVCDev_t *UVCDev);
extern __s32 usbWebcam_v4l2_exit(UVCDev_t *UVCDev);
extern __s32 usbWebcam_v4l2_capture_on(UVCDev_t *UVCDev);
extern __s32 usbWebcam_v4l2_capture_off(UVCDev_t *UVCDev);







#endif

