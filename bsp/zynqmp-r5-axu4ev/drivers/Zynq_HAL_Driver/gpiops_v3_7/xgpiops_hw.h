/******************************************************************************
* Copyright (C) 2010 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xgpiops_hw.h
* @addtogroup gpiops_v3_7
* @{
*
* This header file contains the identifiers and basic driver functions (or
* macros) that can be used to access the device. Other driver functions
* are defined in xgpiops.h.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------
* 1.00a sv   01/15/10 First Release
* 1.02a hk   08/22/13 Added low level reset API function prototype and
*                     related constant definitions
* 3.00  kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* 3.1    kvn  04/13/15 Corrected reset values of banks.
* 3.5   sne  03/14/19 Added versal support.
* </pre>
*
******************************************************************************/
#ifndef XGPIOPS_HW_H        /* prevent circular inclusions */
#define XGPIOPS_HW_H        /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/***************************** Include Files *********************************/

#include "xil_types.h"
#include "xil_assert.h"
#include "xil_io.h"

/************************** Constant Definitions *****************************/

/** @name Register offsets for the GPIO. Each register is 32 bits.
 *  @{
 */
#define XGPIOPS_DATA_LSW_OFFSET  0x00000000U  /* Mask and Data Register LSW, WO */
#define XGPIOPS_DATA_MSW_OFFSET  0x00000004U  /* Mask and Data Register MSW, WO */
#define XGPIOPS_DATA_OFFSET     0x00000040U  /* Data Register, RW */
#define XGPIOPS_DATA_RO_OFFSET     0x00000060U  /* Data Register - Input, RO */
#define XGPIOPS_DIRM_OFFSET     0x00000204U  /* Direction Mode Register, RW */
#define XGPIOPS_OUTEN_OFFSET     0x00000208U  /* Output Enable Register, RW */
#define XGPIOPS_INTMASK_OFFSET     0x0000020CU  /* Interrupt Mask Register, RO */
#define XGPIOPS_INTEN_OFFSET     0x00000210U  /* Interrupt Enable Register, WO */
#define XGPIOPS_INTDIS_OFFSET     0x00000214U  /* Interrupt Disable Register, WO*/
#define XGPIOPS_INTSTS_OFFSET     0x00000218U  /* Interrupt Status Register, RO */
#define XGPIOPS_INTTYPE_OFFSET     0x0000021CU  /* Interrupt Type Register, RW */
#define XGPIOPS_INTPOL_OFFSET     0x00000220U  /* Interrupt Polarity Register, RW */
#define XGPIOPS_INTANY_OFFSET     0x00000224U  /* Interrupt On Any Register, RW */
/* @} */

/** @name Register offsets for each Bank.
 *  @{
 */
#define XGPIOPS_DATA_MASK_OFFSET 0x00000008U  /* Data/Mask Registers offset */
#define XGPIOPS_DATA_BANK_OFFSET 0x00000004U  /* Data Registers offset */
#define XGPIOPS_REG_MASK_OFFSET  0x00000040U  /* Registers offset */
/* @} */

/* For backwards compatibility */
#define XGPIOPS_BYPM_MASK_OFFSET    (u32)0x40

/** @name Interrupt type reset values for each bank
 *  @{
 */
#ifdef XPAR_PSU_GPIO_0_BASEADDR
#define XGPIOPS_INTTYPE_BANK0_RESET  0x03FFFFFFU  /* Resets specific to Zynq Ultrascale+ MP */
#define XGPIOPS_INTTYPE_BANK1_RESET  0x03FFFFFFU
#define XGPIOPS_INTTYPE_BANK2_RESET  0x03FFFFFFU
#else
#define XGPIOPS_INTTYPE_BANK0_RESET  0xFFFFFFFFU  /* Resets specific to Zynq */
#define XGPIOPS_INTTYPE_BANK1_RESET  0x003FFFFFU
#define XGPIOPS_INTTYPE_BANK2_RESET  0xFFFFFFFFU
#endif

#define XGPIOPS_INTTYPE_BANK3_RESET  0xFFFFFFFFU  /* Reset common to both platforms */
#define XGPIOPS_INTTYPE_BANK4_RESET  0xFFFFFFFFU  /* Resets specific to Zynq Ultrascale+ MP */
#define XGPIOPS_INTTYPE_BANK5_RESET  0xFFFFFFFFU
/* @} */
#define XGPIOPS_PS_GPIO_BASEADDR     0xFF0B0000U     /* Flag for Base Address for PS_GPIO in Versal */
#define XGPIOPS_ZERO    0U  /* Flag for 0 Value */
#define XGPIOPS_ONE     1U  /* Flag for 1 Value */
#define XGPIOPS_TWO     2U  /* Flag for 2 Value */
#define XGPIOPS_THREE   3U  /* Flag for 3 Value */
#define XGPIOPS_FOUR    4U  /* Flag for 4 Value */
#define XGPIOPS_SIX     6U  /* Flag for 6 Value */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/****************************************************************************/
/**
*
* This macro reads the given register.
*
* @param    BaseAddr is the base address of the device.
* @param    RegOffset is the register offset to be read.
*
* @return    The 32-bit value of the register
*
* @note        None.
*
*****************************************************************************/
#define XGpioPs_ReadReg(BaseAddr, RegOffset)        \
        Xil_In32((BaseAddr) + (u32)(RegOffset))

/****************************************************************************/
/**
*
* This macro writes to the given register.
*
* @param    BaseAddr is the base address of the device.
* @param    RegOffset is the offset of the register to be written.
* @param    Data is the 32-bit value to write to the register.
*
* @return    None.
*
* @note        None.
*
*****************************************************************************/
#define XGpioPs_WriteReg(BaseAddr, RegOffset, Data)    \
        Xil_Out32((BaseAddr) + (u32)(RegOffset), (u32)(Data))

/************************** Function Prototypes ******************************/

void XGpioPs_ResetHw(u32 BaseAddress);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XGPIOPS_HW_H */
/** @} */
