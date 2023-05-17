/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fxhci.h
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:17:44
 * Description:  This files is for definition of XHCI user function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#ifndef  FXHCI_H
#define  FXHCI_H

/***************************** Include Files *********************************/
#include "fusb.h"


#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
#define FXHCI_EVENT_RING_SIZE    64
#define FXHCI_TRANSFER_RING_SIZE 32 /* Never raise this above 256 to prevent transfer event length overflow! */
#define FXHCI_COMMAND_RING_SIZE  4
#define FXHCI_NUM_EPS            32

#define FXHCI_HC_VERSION_MIN     0x96 /* supported XHCI version from v0.96 to v1.2 */
#define FXHCI_HC_VERSION_MAX     0x120

/* completion code for xhci */
enum
{
    /* Make these high enough to not collide with negative FUSB_HC_XHCI CCs */
    FXHCI_CC_TIMEOUT                =   -65,
    FXHCI_CC_CONTROLLER_ERROR       =   -66,
    FXHCI_CC_COMMUNICATION_ERROR    =   -67,
    FXHCI_CC_OUT_OF_MEMORY          =   -68,
    FXHCI_CC_DRIVER_ERROR           =   -69,
    FXHCI_CC_GENERAL_ERROR          =   -1,

    FXHCI_CC_ZERO_BYTES             =   FUSB_CC_ZERO_BYTES,

    /* defined according to Table 130: TRB Completion Code Definitions in spec */
    FXHCI_CC_SUCCESS                =   FUSB_CC_SUCCESS,

    /* Use as -FXHCI_CC_TRB_ERROR when return as error */
    FXHCI_CC_TRB_ERROR              =   5,
    FXHCI_CC_STALL_ERROR            =   6,
    FXHCI_CC_RESOURCE_ERROR         =   7,
    FXHCI_CC_BANDWIDTH_ERROR        =   8,
    FXHCI_CC_NO_SLOTS_AVAILABLE     =   9,
    FXHCI_CC_SLOT_NOT_ENABLED       =   11,
    FXHCI_CC_SHORT_PACKET           =   13,
    FXHCI_CC_EVENT_RING_FULL_ERROR  =   21,
    FXHCI_CC_COMMAND_RING_STOPPED   =   24,
    FXHCI_CC_COMMAND_ABORTED        =   25,
    FXHCI_CC_STOPPED                =   26,
    FXHCI_CC_STOPPED_LENGTH_INVALID =   27
};

typedef FUsbTransCode FXhciTransCode;
/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
/* 创建XHCI USB 控制器实例，完成初始化 */
FUsbHc *FXhciHcInit(FUsb *instance, uintptr base_addr);

#ifdef __cplusplus
}
#endif


#endif


