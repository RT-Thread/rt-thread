/******************************************************************************
* Copyright (C) 2013 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xgpiops_hw.c
* @addtogroup gpiops_v3_7
* @{
*
* This file contains low level GPIO functions.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -----------------------------------------------
* 1.02a hk   08/22/13 First Release
* 3.00  kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* 3.1    kvn  04/13/15 Add support for Zynq Ultrascale+ MP. CR# 856980.
* 3.5   sne  03/01/19 Fixes violations according to MISRAC-2012
*                     in safety mode and modified the code such as
*                     Use of mixed mode arithmetic,Declared the pointer param
*                     as Pointer to const,Casting operation to a pointer,
*                     Literal value requires a U suffix.
* 3.5   sne  03/14/19 Added versal support.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xgpiops_hw.h"
#include "xgpiops.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/


/*****************************************************************************/
/*
*
* This function resets the GPIO module by writing reset values to
* all registers
*
* @param    Base address of GPIO module
*
* @return    None
*
* @note        None.
*
******************************************************************************/
void XGpioPs_ResetHw(u32 BaseAddress)
{
    u32 BankCount;
    u32 Platform,MaxBanks;

    Platform = XGetPlatform_Info();
        if (Platform == (u32)XPLAT_ZYNQ_ULTRA_MP) {
                MaxBanks = (u32)6;
        }
        else if(Platform == (u32)XPLAT_VERSAL)
        {
                if (BaseAddress == (u32)XGPIOPS_PS_GPIO_BASEADDR)
                {
                        MaxBanks = (u32)4;
                }
                else
                {
                        MaxBanks = (u32)5;
                }
        }
        else {
                MaxBanks = (u32)4;
        }

        if (Platform == (u32)XPLAT_VERSAL)
        {
                /* Write reset values to all mask data registers */
                for(BankCount = 3U; BankCount < (u32)MaxBanks; BankCount++) {

                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_DATA_MASK_OFFSET) +
                                         XGPIOPS_DATA_LSW_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_DATA_MASK_OFFSET) +
                                         XGPIOPS_DATA_MSW_OFFSET), 0x0U);
                }
                /* Write reset values to all output data registers */
                for(BankCount = 3U; BankCount < (u32)MaxBanks; BankCount++) {

                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_DATA_BANK_OFFSET) +
                                         XGPIOPS_DATA_OFFSET), 0x0U);
                }

                /* Reset all registers of all GPIO banks */
                for(BankCount = 0U; BankCount < (u32)MaxBanks; BankCount++) {


                        if((BaseAddress == (u32)XGPIOPS_PS_GPIO_BASEADDR) && ((BankCount == (u32)XGPIOPS_ONE) ||(BankCount == (u32)XGPIOPS_TWO)))
                        {
                                continue;
                        }
                        else
                        {
                                if((BaseAddress != (u32)XGPIOPS_PS_GPIO_BASEADDR) && (BankCount == (u32)XGPIOPS_ONE))
                                {
                                        continue;
                                }
                        }
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_DIRM_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_OUTEN_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTMASK_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTEN_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTDIS_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTSTS_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTPOL_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTANY_OFFSET), 0x0U);

                }

                /* Bank 0 Int type */
                XGpioPs_WriteReg(BaseAddress, XGPIOPS_INTTYPE_OFFSET,
                                XGPIOPS_INTTYPE_BANK0_RESET);
                /* Bank 1 Int type */
                XGpioPs_WriteReg(BaseAddress,
                                ((u32)XGPIOPS_REG_MASK_OFFSET + (u32)XGPIOPS_INTTYPE_OFFSET),
                                XGPIOPS_INTTYPE_BANK1_RESET);
                /* Bank 3 Int type */
                XGpioPs_WriteReg(BaseAddress,
                                (((u32)3 * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_INTTYPE_OFFSET),
                                XGPIOPS_INTTYPE_BANK3_RESET);
                /* Bank 4 Int type */
                XGpioPs_WriteReg(BaseAddress,
                                (((u32)4 * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_INTTYPE_OFFSET),
                                XGPIOPS_INTTYPE_BANK4_RESET);
        }
        else
        {
                /* Write reset values to all mask data registers */
                for(BankCount = 2U; BankCount < (u32)MaxBanks; BankCount++) {

                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_DATA_MASK_OFFSET) +
                                         XGPIOPS_DATA_LSW_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_DATA_MASK_OFFSET) +
                                         XGPIOPS_DATA_MSW_OFFSET), 0x0U);
                }
                /* Write reset values to all output data registers */
                for(BankCount = 2U; BankCount < (u32)MaxBanks; BankCount++) {

                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_DATA_BANK_OFFSET) +
                                         XGPIOPS_DATA_OFFSET), 0x0U);
                }
                /* Reset all registers of all GPIO banks */
                for(BankCount = 0U; BankCount < (u32)MaxBanks; BankCount++) {

                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_DIRM_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_OUTEN_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTMASK_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTEN_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTDIS_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTSTS_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTPOL_OFFSET), 0x0U);
                        XGpioPs_WriteReg(BaseAddress,
                                        ((BankCount * XGPIOPS_REG_MASK_OFFSET) +
                                         XGPIOPS_INTANY_OFFSET), 0x0U);
                }
                /* Bank 0 Int type */
                XGpioPs_WriteReg(BaseAddress, XGPIOPS_INTTYPE_OFFSET,
                                XGPIOPS_INTTYPE_BANK0_RESET);
                /* Bank 1 Int type */
                XGpioPs_WriteReg(BaseAddress,
                                ((u32)XGPIOPS_REG_MASK_OFFSET + (u32)XGPIOPS_INTTYPE_OFFSET),
                                XGPIOPS_INTTYPE_BANK1_RESET);
                /* Bank 2 Int type */
                XGpioPs_WriteReg(BaseAddress,
                                (((u32)2 * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_INTTYPE_OFFSET),
                                XGPIOPS_INTTYPE_BANK2_RESET);
                /* Bank 3 Int type */
                XGpioPs_WriteReg(BaseAddress,
                                (((u32)3 * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_INTTYPE_OFFSET),
                                XGPIOPS_INTTYPE_BANK3_RESET);

                if (Platform == (u32)XPLAT_ZYNQ_ULTRA_MP) {
                        /* Bank 4 Int type */
                        XGpioPs_WriteReg(BaseAddress,
                                        (((u32)4 * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_INTTYPE_OFFSET),
                                        XGPIOPS_INTTYPE_BANK4_RESET);
                        /* Bank 5 Int type */
                        XGpioPs_WriteReg(BaseAddress,
                                        (((u32)5 * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_INTTYPE_OFFSET),
                                        XGPIOPS_INTTYPE_BANK5_RESET);
                }
        }

}
/** @} */
