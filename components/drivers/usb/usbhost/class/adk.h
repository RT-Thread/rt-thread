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
};	
typedef struct uadkinst* uadkinst_t;

#define USB_CLASS_ADK			0xff

#endif

