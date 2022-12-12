/*
********************************************************************************
*                                USB UVC Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  uvc_driver.h
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
#ifndef __USB_UVC_DRIVER_H__
#define __USB_UVC_DRIVER_H__




extern __s32 uvc_probe(UVCDev_t *UVCDev, const struct usb_drv_dev_match_table *id);
extern void uvc_disconnect(UVCDev_t *UVCDev);












#endif//__USB_UVC_DRIVER_H__

