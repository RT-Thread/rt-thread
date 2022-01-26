/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xgpiops_selftest.c
* @addtogroup gpiops_v3_7
* @{
*
* This file contains a diagnostic self-test function for the XGpioPs driver.
*
* Read xgpiops.h file for more information.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.00a sv   01/18/10 First Release
* 3.00  kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* 3.5   sne  03/01/19 Fixes violations according to MISRAC-2012
*                     in safety mode and modified the code such as
*                     Use of mixed mode arithmetic,Declared the pointer param
*                     as Pointer to const,Casting operation to a pointer,
*                     Literal value requires a U suffix.
* </pre>
*
*****************************************************************************/

/***************************** Include Files ********************************/

#include "xstatus.h"
#include "xgpiops.h"

/************************** Constant Definitions ****************************/


/**************************** Type Definitions ******************************/

/***************** Macros (Inline Functions) Definitions ********************/

/************************** Variable Definitions ****************************/

/************************** Function Prototypes *****************************/

/*****************************************************************************/
/**
*
* This function runs a self-test on the GPIO driver/device. This function
* does a register read/write test on some of the Interrupt Registers.
*
* @param    InstancePtr is a pointer to the XGpioPs instance.
*
* @return
*        - XST_SUCCESS if the self-test passed.
*         - XST_FAILURE otherwise.
*
*
******************************************************************************/
s32 XGpioPs_SelfTest(const XGpioPs *InstancePtr)
{
    s32 Status = XST_SUCCESS;
    u32 IntrEnabled;
    u32 CurrentIntrType = 0U;
    u32 CurrentIntrPolarity = 0U;
    u32 CurrentIntrOnAny = 0U;
    u32 IntrType = 0U;
    u32 IntrPolarity = 0U;
    u32 IntrOnAny = 0U;
    u32 IntrTestValue = 0x22U;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    /* Disable the Interrupts for Bank 0 . */
    IntrEnabled = XGpioPs_IntrGetEnabled(InstancePtr, XGPIOPS_BANK0);
    XGpioPs_IntrDisable(InstancePtr, XGPIOPS_BANK0, IntrEnabled);

    /*
     * Get the Current Interrupt properties for Bank 0.
     * Set them to a known value, read it back and compare.
     */
    XGpioPs_GetIntrType(InstancePtr, XGPIOPS_BANK0, &CurrentIntrType,
                 &CurrentIntrPolarity, &CurrentIntrOnAny);

    XGpioPs_SetIntrType(InstancePtr, XGPIOPS_BANK0, IntrTestValue,
                 IntrTestValue, IntrTestValue);

    XGpioPs_GetIntrType(InstancePtr, XGPIOPS_BANK0, &IntrType,
                 &IntrPolarity, &IntrOnAny);

    if ((IntrType != IntrTestValue) && (IntrPolarity != IntrTestValue) &&
        (IntrOnAny != IntrTestValue)) {

        Status = XST_FAILURE;
    }

    /*
     * Restore the contents of all the interrupt registers modified in this
     * test.
     */
    XGpioPs_SetIntrType(InstancePtr, XGPIOPS_BANK0, CurrentIntrType,
                 CurrentIntrPolarity, CurrentIntrOnAny);

    XGpioPs_IntrEnable(InstancePtr, XGPIOPS_BANK0, IntrEnabled);

    return Status;
}
/** @} */
