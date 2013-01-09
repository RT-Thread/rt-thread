/*
 * File      : adk.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-12     Yi Qiu      first version
 */

#ifndef __HID_H__
#define __HID_H__

#include <rtthread.h>

struct uadkinst
{
    upipe_t pipe_in;
    upipe_t pipe_out;

    struct rt_device device;
};    
typedef struct uadkinst* uadkinst_t;

#define USB_ACCESSORY_VENDOR_ID         0x18D1
#define USB_ACCESSORY_PRODUCT_ID        0x2D00
#define USB_ACCESSORY_ADB_PRODUCT_ID    0x2D01

#define ACCESSORY_STRING_MANUFACTURER   0
#define ACCESSORY_STRING_MODEL          1
#define ACCESSORY_STRING_DESCRIPTION    2
#define ACCESSORY_STRING_VERSION        3
#define ACCESSORY_STRING_URI            4
#define ACCESSORY_STRING_SERIAL         5

#define USB_REQ_GET_PROTOCOL            51
#define USB_REQ_SEND_STRING             52
#define USB_REQ_START                   53

#define USB_CLASS_ADK                   0xff

#endif

