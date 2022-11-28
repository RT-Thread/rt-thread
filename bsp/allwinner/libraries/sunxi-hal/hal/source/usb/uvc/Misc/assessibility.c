/*
********************************************************************************
*                                USB UVC Driver
*
*                (c) Copyright 2010-2015, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  assessibility.c
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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <hal_log.h>

#include "assessibility.h"

unsigned int uvc_strlcpy(char *dest, const char *src, unsigned int size)
{
    unsigned int ret = strlen(src);

    if (size) {
        unsigned int len = (ret >= size) ? size - 1 : ret;
        memcpy(dest, src, len);
        dest[len] = '\0';
    }
    return ret;
}

unsigned int uvc_strlcat(char *dest, const char *src, unsigned int count)
{
    unsigned int dsize = strlen(dest);
    unsigned int len = strlen(src);
    unsigned int res = dsize + len;

    /* This would be a bug */
    if(dsize >= count) {
        hal_log_err("uvc_strlcat err!\n");
    }

    dest += dsize;
    count -= dsize;
    if (len >= count) {
        len = count-1;
    }
    memcpy(dest, src, len);
    dest[len] = 0;
    return res;
}

unsigned short get_unaligned_le16( const void *p )
{
//  unsigned short *ptr = (unsigned short *)p;
//  return *ptr;

    unsigned char* data = (unsigned char*)p;

    return ((data[0])|(data[1]<<8));
}

unsigned int get_unaligned_le32( const void *p )
{
//  unsigned int *ptr = (unsigned int *)p;
//  return *ptr;

    unsigned char* data = (unsigned char*)p;

    return ((data[0])|(data[1]<<8)|(data[2]<<16)|(data[3]<<24));

}
