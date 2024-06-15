/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-01     Yi Qiu       first version
 * 2012-12-12     heyuanjie87  add MASS endpoints collection
 */

#ifndef  __MSTORAGE_H__
#define  __MSTORAGE_H__

#include <rtthread.h>

#pragma pack(1)

struct umass_descriptor
{
#ifdef RT_USB_DEVICE_COMPOSITE
    struct uiad_descriptor iad_desc;
#endif
    struct uinterface_descriptor intf_desc;
    struct uendpoint_descriptor ep_out_desc;
    struct uendpoint_descriptor ep_in_desc;
};
typedef struct umass_descriptor* umass_desc_t;

struct capacity_data
{
    rt_uint8_t LastLogicalBlockAddress[4];
    rt_uint8_t BlockLengthInBytes[4];
};

struct request_sense_data
{
    rt_uint8_t ErrorCode:7;
    rt_uint8_t Valid:1;
    rt_uint8_t Reserved1;
    rt_uint8_t SenseKey:4;
    rt_uint8_t Reserved2:4;
    rt_uint8_t Information[4];
    rt_uint8_t AdditionalSenseLength;
    rt_uint8_t Reserved3[4];
    rt_uint8_t AdditionalSenseCode;
    rt_uint8_t AdditionalSenseCodeQualifier;
    rt_uint8_t Reserved4[4];
}request_sense_data_t;

#pragma pack()

#endif
