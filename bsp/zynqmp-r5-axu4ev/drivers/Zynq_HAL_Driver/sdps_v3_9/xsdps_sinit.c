/******************************************************************************
* Copyright (C) 2013 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xsdps_sinit.c
* @addtogroup sdps_v3_9
* @{
*
* The implementation of the XSdPs component's static initialization
* functionality.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ---    -------- -----------------------------------------------
* 1.00a hk/sg  10/17/13 Initial release
*       kvn    07/15/15 Modified the code according to MISRAC-2012.
* 3.7   aru    03/12/19 Modified the code according to MISRAC-2012.
*
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/
#include "xstatus.h"
#include "xsdps.h"
#include "xparameters.h"
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/
extern XSdPs_Config XSdPs_ConfigTable[XPAR_XSDPS_NUM_INSTANCES];

/*****************************************************************************/
/**
*
* @brief
* Looks up the device configuration based on the unique device ID. A table
* contains the configuration info for each device in the system.
*
* @param    DeviceId contains the ID of the device to look up the
*        configuration for.
*
* @return
*
* A pointer to the configuration found or NULL if the specified device ID was
* not found. See xsdps.h for the definition of XSdPs_Config.
*
* @note        None.
*
******************************************************************************/
XSdPs_Config *XSdPs_LookupConfig(u16 DeviceId)
{
    XSdPs_Config *CfgPtr = NULL;
    u32 Index;

    for (Index = 0U; Index < (u32)XPAR_XSDPS_NUM_INSTANCES; Index++) {
        if (XSdPs_ConfigTable[Index].DeviceId == DeviceId) {
            CfgPtr = &XSdPs_ConfigTable[Index];
            break;
        }
    }
    return (XSdPs_Config *)CfgPtr;
}
/** @} */
