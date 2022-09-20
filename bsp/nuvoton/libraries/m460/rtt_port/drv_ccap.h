/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-8-16       Wayne        First version
*
******************************************************************************/

#ifndef __DRV_CCAP_H__
#define __DRV_CCAP_H__

#include "ccap_sensor.h"

#define NU_CCAP_FRAME_END       (1<<0)
#define NU_CCAP_ADDRESS_MATCH   (1<<1)
#define NU_CCAP_MEMORY_ERROR    (1<<2)
#define NU_CCAP_MOTION_DETECT   (1<<3)

typedef void (*nu_ccap_event_handler_t)(void *pvData, uint32_t u32EvtMask);

typedef enum
{
    CCAP_CMD_CONFIG,
    CCAP_CMD_START_CAPTURE,
    CCAP_CMD_STOP_CAPTURE,
    CCAP_CMD_SET_SENCLK,
    CCAP_CMD_SET_PIPES,
    CCAP_CMD_SET_OPMODE,
    CCAP_CMD_SET_BASEADDR,
} ccap_cmd;

typedef struct
{
    struct rt_device_rect_info sRectCropping;
    ccap_view_info sPipeInfo_Packet;
    ccap_view_info sPipeInfo_Planar;
    uint32_t u32Stride_Packet;
    uint32_t u32Stride_Planar;

    nu_ccap_event_handler_t   pfnEvHndler;  // Callback function in ISR
    void *pvData;    // For ISR callback argument.
} ccap_config;
typedef ccap_config *ccap_config_t;

#endif //__DRV_CCAP_H__
