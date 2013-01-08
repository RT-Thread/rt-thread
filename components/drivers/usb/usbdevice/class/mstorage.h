/*
 * File      : mstorage.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-01     Yi Qiu       first version
 * 2012-12-12     heyuanjie87  add MASS endpoints collection
 */
 
#ifndef  __MSTORAGE_H__
#define  __MSTORAGE_H__

#include <rtthread.h>

#define USBREQ_GET_MAX_LUN              0xfe
#define USBREQ_MASS_STORAGE_RESET       0xff

#define SIZEOF_CSW                      0x0d
#define SIZEOF_CBW                      0x1f

#define CBWFLAGS_DIR_M                  0x80
#define CBWFLAGS_DIR_IN                 0x80
#define CBWFLAGS_DIR_OUT                0x00

#define SCSI_TEST_UNIT_READY            0x00
#define SCSI_REQUEST_SENSE              0x03
#define SCSI_INQUIRY_CMD                0x12
#define SCSI_ALLOW_MEDIUM_REMOVAL       0x1e
#define SCSI_MODE_SENSE_6               0x1a
#define SCSI_READ_CAPACITIES            0x23
#define SCSI_READ_CAPACITY              0x25
#define SCSI_READ_10                    0x28
#define SCSI_WRITE_10                   0x2a
#define SCSI_VERIFY_10                  0x2f

#define CBW_SIGNATURE                   0x43425355
#define CSW_SIGNATURE                   0x53425355
#define CBW_TAG_VALUE                   0x12345678

#pragma pack(1)

struct ustorage_cbw 
{
    rt_uint32_t signature;
    rt_uint32_t tag;
    rt_uint32_t xfer_len;
    rt_uint8_t dflags;
    rt_uint8_t lun;
    rt_uint8_t cb_len;
    rt_uint8_t cb[16];
};
typedef struct ustorage_cbw* ustorage_cbw_t;

struct ustorage_csw 
{
    rt_uint32_t signature;
    rt_uint32_t tag;
    rt_uint32_t data_reside;
    rt_uint8_t  status;
};
typedef struct ustorage_csw* ustorage_csw_t;

struct umass_descriptor
{
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

struct mass_eps
{
    uep_t ep_in;
    uep_t ep_out;
};
typedef struct mass_eps* mass_eps_t;

#pragma pack()

#endif
