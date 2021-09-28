/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemacps_sinit.c
* @addtogroup emacps_v3_11
* @{
*
* This file contains lookup method by device ID when success, it returns
* pointer to config table to be used to initialize the device.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a wsy  01/10/10 New
* 3.00  kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xemacps.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/

/*************************** Variable Definitions *****************************/
extern XEmacPs_Config XEmacPs_ConfigTable[XPAR_XEMACPS_NUM_INSTANCES];

/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

/*****************************************************************************/
/**
* Lookup the device configuration based on the unique device ID.  The table
* contains the configuration info for each device in the system.
*
* @param DeviceId is the unique device ID of the device being looked up.
*
* @return
* A pointer to the configuration table entry corresponding to the given
* device ID, or NULL if no match is found.
*
******************************************************************************/
XEmacPs_Config *XEmacPs_LookupConfig(u16 DeviceId)
{
    XEmacPs_Config *CfgPtr = NULL;
    u32 i;

    for (i = 0U; i < (u32)XPAR_XEMACPS_NUM_INSTANCES; i++) {
        if (XEmacPs_ConfigTable[i].DeviceId == DeviceId) {
            CfgPtr = &XEmacPs_ConfigTable[i];
            break;
        }
    }

    return (XEmacPs_Config *)(CfgPtr);
}
/** @} */
