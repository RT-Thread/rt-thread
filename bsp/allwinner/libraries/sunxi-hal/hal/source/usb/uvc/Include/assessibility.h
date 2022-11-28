/*
********************************************************************************
*                                USB UVC Driver
*
*                (c) Copyright 2010-2015, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  assessibility.h
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
#ifndef __USB_UVC_ASSESSIBILITY_H__
#define __USB_UVC_ASSESSIBILITY_H__

#include  "usb_os_platform.h"

extern unsigned int uvc_strlcpy(char *dest, const char *src, unsigned int size);
extern unsigned int uvc_strlcat(char *dest, const char *src, unsigned int count);

extern unsigned short get_unaligned_le16( const void *p );
extern unsigned int get_unaligned_le32( const void *p );

#endif


