/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xgpiops_sinit.c
* @addtogroup gpiops_v3_7
* @{
*
* This file contains the implementation of the XGpioPs driver's static
* initialization functionality.
*
* @note		None.
*
* <pre>
*
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a sv   01/15/10 First Release
* 3.00  kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xgpiops.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/
extern XGpioPs_Config XGpioPs_ConfigTable[XPAR_XGPIOPS_NUM_INSTANCES];

/*****************************************************************************/
/**
*
* This function looks for the device configuration based on the unique device
* ID. The table XGpioPs_ConfigTable[] contains the configuration information
* for each device in the system.
*
* @param	DeviceId is the unique device ID of the device being looked up.
*
* @return	A pointer to the configuration table entry corresponding to the
*		given device ID, or NULL if no match is found.
*
* @note		None.
*
******************************************************************************/
XGpioPs_Config *XGpioPs_LookupConfig(u16 DeviceId)
{
	XGpioPs_Config *CfgPtr = NULL;
	u32 Index;

	for (Index = 0U; Index < (u32)XPAR_XGPIOPS_NUM_INSTANCES; Index++) {
		if (XGpioPs_ConfigTable[Index].DeviceId == DeviceId) {
			CfgPtr = &XGpioPs_ConfigTable[Index];
			break;
		}
	}

	return (XGpioPs_Config *)CfgPtr;
}
/** @} */
