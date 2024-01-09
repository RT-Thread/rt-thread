/**
 *******************************************************************************
 * @file  hc32f4a0_ll_interrupts_share.h
 * @brief This file contains all the functions prototypes of the interrupt driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Rename I2Cx_Error_IrqHandler as I2Cx_EE_IrqHandler
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_LL_SHARE_INTERRUPTS_H__
#define __HC32F4A0_LL_SHARE_INTERRUPTS_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_HC32F4A0_SHARE_INTERRUPTS
 * @{
 */

#if (LL_INTERRUPTS_SHARE_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup Share_Interrupts_Global_Functions
 * @{
 */

int32_t INTC_ShareIrqCmd(en_int_src_t enIntSrc, en_functional_state_t enNewState);

void IRQ128_Handler(void);
void IRQ129_Handler(void);
void IRQ130_Handler(void);
void IRQ131_Handler(void);
void IRQ132_Handler(void);
void IRQ133_Handler(void);
void IRQ134_Handler(void);
void IRQ135_Handler(void);
void IRQ136_Handler(void);
void IRQ137_Handler(void);
void IRQ138_Handler(void);
void IRQ139_Handler(void);
void IRQ140_Handler(void);
void IRQ141_Handler(void);
void IRQ142_Handler(void);
void IRQ143_Handler(void);

void EXTINT00_IrqHandler(void);
void EXTINT01_IrqHandler(void);
void EXTINT02_IrqHandler(void);
void EXTINT03_IrqHandler(void);
void EXTINT04_IrqHandler(void);
void EXTINT05_IrqHandler(void);
void EXTINT06_IrqHandler(void);
void EXTINT07_IrqHandler(void);
void EXTINT08_IrqHandler(void);
void EXTINT09_IrqHandler(void);
void EXTINT10_IrqHandler(void);
void EXTINT11_IrqHandler(void);
void EXTINT12_IrqHandler(void);
void EXTINT13_IrqHandler(void);
void EXTINT14_IrqHandler(void);
void EXTINT15_IrqHandler(void);
void DMA1_TC0_IrqHandler(void);
void DMA1_TC1_IrqHandler(void);
void DMA1_TC2_IrqHandler(void);
void DMA1_TC3_IrqHandler(void);
void DMA1_TC4_IrqHandler(void);
void DMA1_TC5_IrqHandler(void);
void DMA1_TC6_IrqHandler(void);
void DMA1_TC7_IrqHandler(void);
void DMA1_BTC0_IrqHandler(void);
void DMA1_BTC1_IrqHandler(void);
void DMA1_BTC2_IrqHandler(void);
void DMA1_BTC3_IrqHandler(void);
void DMA1_BTC4_IrqHandler(void);
void DMA1_BTC5_IrqHandler(void);
void DMA1_BTC6_IrqHandler(void);
void DMA1_BTC7_IrqHandler(void);
void DMA1_Error0_IrqHandler(void);
void DMA1_Error1_IrqHandler(void);
void DMA1_Error2_IrqHandler(void);
void DMA1_Error3_IrqHandler(void);
void DMA1_Error4_IrqHandler(void);
void DMA1_Error5_IrqHandler(void);
void DMA1_Error6_IrqHandler(void);
void DMA1_Error7_IrqHandler(void);
void DMA2_TC0_IrqHandler(void);
void DMA2_TC1_IrqHandler(void);
void DMA2_TC2_IrqHandler(void);
void DMA2_TC3_IrqHandler(void);
void DMA2_TC4_IrqHandler(void);
void DMA2_TC5_IrqHandler(void);
void DMA2_TC6_IrqHandler(void);
void DMA2_TC7_IrqHandler(void);
void DMA2_BTC0_IrqHandler(void);
void DMA2_BTC1_IrqHandler(void);
void DMA2_BTC2_IrqHandler(void);
void DMA2_BTC3_IrqHandler(void);
void DMA2_BTC4_IrqHandler(void);
void DMA2_BTC5_IrqHandler(void);
void DMA2_BTC6_IrqHandler(void);
void DMA2_BTC7_IrqHandler(void);
void DMA2_Error0_IrqHandler(void);
void DMA2_Error1_IrqHandler(void);
void DMA2_Error2_IrqHandler(void);
void DMA2_Error3_IrqHandler(void);
void DMA2_Error4_IrqHandler(void);
void DMA2_Error5_IrqHandler(void);
void DMA2_Error6_IrqHandler(void);
void DMA2_Error7_IrqHandler(void);
void EFM_ProgramEraseError_IrqHandler(void);
void EFM_ColError_IrqHandler(void);
void EFM_OpEnd_IrqHandler(void);
void QSPI_Error_IrqHandler(void);
void MAU_Sqrt_IrqHandler(void);
void DVP_FrameStart_IrqHandler(void);
void DVP_FrameEnd_IrqHandler(void);
void DVP_LineStart_IrqHandler(void);
void DVP_LineEnd_IrqHandler(void);
void DVP_SWSyncError_IrqHandler(void);
void DVP_FifoError_IrqHandler(void);
void FMAC1_IrqHandler(void);
void FMAC2_IrqHandler(void);
void FMAC3_IrqHandler(void);
void FMAC4_IrqHandler(void);
void DCU1_IrqHandler(void);
void DCU2_IrqHandler(void);
void DCU3_IrqHandler(void);
void DCU4_IrqHandler(void);
void DCU5_IrqHandler(void);
void DCU6_IrqHandler(void);
void DCU7_IrqHandler(void);
void DCU8_IrqHandler(void);
void TMR0_1_CmpA_IrqHandler(void);
void TMR0_1_CmpB_IrqHandler(void);
void TMR0_2_CmpA_IrqHandler(void);
void TMR0_2_CmpB_IrqHandler(void);
void TMR2_1_CmpA_IrqHandler(void);
void TMR2_1_CmpB_IrqHandler(void);
void TMR2_1_OvfA_IrqHandler(void);
void TMR2_1_OvfB_IrqHandler(void);
void TMR2_2_CmpA_IrqHandler(void);
void TMR2_2_CmpB_IrqHandler(void);
void TMR2_2_OvfA_IrqHandler(void);
void TMR2_2_OvfB_IrqHandler(void);
void TMR2_3_CmpA_IrqHandler(void);
void TMR2_3_CmpB_IrqHandler(void);
void TMR2_3_OvfA_IrqHandler(void);
void TMR2_3_OvfB_IrqHandler(void);
void TMR2_4_CmpA_IrqHandler(void);
void TMR2_4_CmpB_IrqHandler(void);
void TMR2_4_OvfA_IrqHandler(void);
void TMR2_4_OvfB_IrqHandler(void);
void RTC_TimeStamp0_IrqHandler(void);
void RTC_TimeStamp1_IrqHandler(void);
void RTC_Alarm_IrqHandler(void);
void RTC_Period_IrqHandler(void);
void CLK_XtalStop_IrqHandler(void);
void SWDT_IrqHandler(void);
void WDT_IrqHandler(void);
void PWC_WakeupTimer_IrqHandler(void);
void TMR6_1_GCmpA_IrqHandler(void);
void TMR6_1_GCmpB_IrqHandler(void);
void TMR6_1_GCmpC_IrqHandler(void);
void TMR6_1_GCmpD_IrqHandler(void);
void TMR6_1_GCmpE_IrqHandler(void);
void TMR6_1_GCmpF_IrqHandler(void);
void TMR6_1_GOvf_IrqHandler(void);
void TMR6_1_GUdf_IrqHandler(void);
void TMR6_1_GDte_IrqHandler(void);
void TMR6_1_SCmpUpA_IrqHandler(void);
void TMR6_1_SCmpDownA_IrqHandler(void);
void TMR6_1_SCmpUpB_IrqHandler(void);
void TMR6_1_SCmpDownB_IrqHandler(void);
void TMR6_2_GCmpA_IrqHandler(void);
void TMR6_2_GCmpB_IrqHandler(void);
void TMR6_2_GCmpC_IrqHandler(void);
void TMR6_2_GCmpD_IrqHandler(void);
void TMR6_2_GCmpE_IrqHandler(void);
void TMR6_2_GCmpF_IrqHandler(void);
void TMR6_2_GOvf_IrqHandler(void);
void TMR6_2_GUdf_IrqHandler(void);
void TMR6_2_GDte_IrqHandler(void);
void TMR6_2_SCmpUpA_IrqHandler(void);
void TMR6_2_SCmpDownA_IrqHandler(void);
void TMR6_2_SCmpUpB_IrqHandler(void);
void TMR6_2_SCmpDownB_IrqHandler(void);
void TMR6_3_GCmpA_IrqHandler(void);
void TMR6_3_GCmpB_IrqHandler(void);
void TMR6_3_GCmpC_IrqHandler(void);
void TMR6_3_GCmpD_IrqHandler(void);
void TMR6_3_GCmpE_IrqHandler(void);
void TMR6_3_GCmpF_IrqHandler(void);
void TMR6_3_GOvf_IrqHandler(void);
void TMR6_3_GUdf_IrqHandler(void);
void TMR6_3_GDte_IrqHandler(void);
void TMR6_3_SCmpUpA_IrqHandler(void);
void TMR6_3_SCmpDownA_IrqHandler(void);
void TMR6_3_SCmpUpB_IrqHandler(void);
void TMR6_3_SCmpDownB_IrqHandler(void);
void TMR6_4_GCmpA_IrqHandler(void);
void TMR6_4_GCmpB_IrqHandler(void);
void TMR6_4_GCmpC_IrqHandler(void);
void TMR6_4_GCmpD_IrqHandler(void);
void TMR6_4_GCmpE_IrqHandler(void);
void TMR6_4_GCmpF_IrqHandler(void);
void TMR6_4_GOvf_IrqHandler(void);
void TMR6_4_GUdf_IrqHandler(void);
void TMR6_4_Gdte_IrqHandler(void);
void TMR6_4_SCmpUpA_IrqHandler(void);
void TMR6_4_SCmpDownA_IrqHandler(void);
void TMR6_4_SCmpUpB_IrqHandler(void);
void TMR6_4_SCmpDownB_IrqHandler(void);
void TMR6_5_GCmpA_IrqHandler(void);
void TMR6_5_GCmpB_IrqHandler(void);
void TMR6_5_GCmpC_IrqHandler(void);
void TMR6_5_GCmpD_IrqHandler(void);
void TMR6_5_GCmpE_IrqHandler(void);
void TMR6_5_GCmpF_IrqHandler(void);
void TMR6_5_GOvf_IrqHandler(void);
void TMR6_5_GUdf_IrqHandler(void);
void TMR6_5_Gdte_IrqHandler(void);
void TMR6_5_SCmpUpA_IrqHandler(void);
void TMR6_5_SCmpDownA_IrqHandler(void);
void TMR6_5_SCmpUpB_IrqHandler(void);
void TMR6_5_SCmpDownB_IrqHandler(void);
void TMR6_6_GCmpA_IrqHandler(void);
void TMR6_6_GCmpB_IrqHandler(void);
void TMR6_6_GCmpC_IrqHandler(void);
void TMR6_6_GCmpD_IrqHandler(void);
void TMR6_6_GCmpE_IrqHandler(void);
void TMR6_6_GCmpF_IrqHandler(void);
void TMR6_6_GOvf_IrqHandler(void);
void TMR6_6_GUdf_IrqHandler(void);
void TMR6_6_Gdte_IrqHandler(void);
void TMR6_6_SCmpUpA_IrqHandler(void);
void TMR6_6_SCmpDownA_IrqHandler(void);
void TMR6_6_SCmpUpB_IrqHandler(void);
void TMR6_6_SCmpDownB_IrqHandler(void);
void TMR6_7_GCmpA_IrqHandler(void);
void TMR6_7_GCmpB_IrqHandler(void);
void TMR6_7_GCmpC_IrqHandler(void);
void TMR6_7_GCmpD_IrqHandler(void);
void TMR6_7_GCmpE_IrqHandler(void);
void TMR6_7_GCmpF_IrqHandler(void);
void TMR6_7_GOvf_IrqHandler(void);
void TMR6_7_GUdf_IrqHandler(void);
void TMR6_7_Gdte_IrqHandler(void);
void TMR6_7_SCmpUpA_IrqHandler(void);
void TMR6_7_SCmpDownA_IrqHandler(void);
void TMR6_7_SCmpUpB_IrqHandler(void);
void TMR6_7_SCmpDownB_IrqHandler(void);
void TMR6_8_GCmpA_IrqHandler(void);
void TMR6_8_GCmpB_IrqHandler(void);
void TMR6_8_GCmpC_IrqHandler(void);
void TMR6_8_GCmpD_IrqHandler(void);
void TMR6_8_GCmpE_IrqHandler(void);
void TMR6_8_GCmpF_IrqHandler(void);
void TMR6_8_GOvf_IrqHandler(void);
void TMR6_8_GUdf_IrqHandler(void);
void TMR6_8_Gdte_IrqHandler(void);
void TMR6_8_SCmpUpA_IrqHandler(void);
void TMR6_8_SCmpDownA_IrqHandler(void);
void TMR6_8_SCmpUpB_IrqHandler(void);
void TMR6_8_SCmpDownB_IrqHandler(void);
void TMR4_1_GCmpUH_IrqHandler(void);
void TMR4_1_GCmpUL_IrqHandler(void);
void TMR4_1_GCmpVH_IrqHandler(void);
void TMR4_1_GCmpVL_IrqHandler(void);
void TMR4_1_GCmpWH_IrqHandler(void);
void TMR4_1_GCmpWL_IrqHandler(void);
void TMR4_1_Ovf_IrqHandler(void);
void TMR4_1_Udf_IrqHandler(void);
void TMR4_1_ReloadU_IrqHandler(void);
void TMR4_1_ReloadV_IrqHandler(void);
void TMR4_1_ReloadW_IrqHandler(void);
void TMR4_2_GCmpUH_IrqHandler(void);
void TMR4_2_GCmpUL_IrqHandler(void);
void TMR4_2_GCmpVH_IrqHandler(void);
void TMR4_2_GCmpVL_IrqHandler(void);
void TMR4_2_GCmpWH_IrqHandler(void);
void TMR4_2_GCmpWL_IrqHandler(void);
void TMR4_2_Ovf_IrqHandler(void);
void TMR4_2_Udf_IrqHandler(void);
void TMR4_2_ReloadU_IrqHandler(void);
void TMR4_2_ReloadV_IrqHandler(void);
void TMR4_2_ReloadW_IrqHandler(void);
void TMR4_3_GCmpUH_IrqHandler(void);
void TMR4_3_GCmpUL_IrqHandler(void);
void TMR4_3_GCmpVH_IrqHandler(void);
void TMR4_3_GCmpVL_IrqHandler(void);
void TMR4_3_GCmpWH_IrqHandler(void);
void TMR4_3_GCmpWL_IrqHandler(void);
void TMR4_3_Ovf_IrqHandler(void);
void TMR4_3_Udf_IrqHandler(void);
void TMR4_3_ReloadU_IrqHandler(void);
void TMR4_3_ReloadV_IrqHandler(void);
void TMR4_3_ReloadW_IrqHandler(void);
void TMRA_1_Ovf_IrqHandler(void);
void TMRA_1_Udf_IrqHandler(void);
void TMRA_1_Cmp_IrqHandler(void);
void TMRA_2_Ovf_IrqHandler(void);
void TMRA_2_Udf_IrqHandler(void);
void TMRA_2_Cmp_IrqHandler(void);
void TMRA_3_Ovf_IrqHandler(void);
void TMRA_3_Udf_IrqHandler(void);
void TMRA_3_Cmp_IrqHandler(void);
void TMRA_4_Ovf_IrqHandler(void);
void TMRA_4_Udf_IrqHandler(void);
void TMRA_4_Cmp_IrqHandler(void);
void TMRA_5_Ovf_IrqHandler(void);
void TMRA_5_Udf_IrqHandler(void);
void TMRA_5_Cmp_IrqHandler(void);
void TMRA_6_Ovf_IrqHandler(void);
void TMRA_6_Udf_IrqHandler(void);
void TMRA_6_Cmp_IrqHandler(void);
void TMRA_7_Ovf_IrqHandler(void);
void TMRA_7_Udf_IrqHandler(void);
void TMRA_7_Cmp_IrqHandler(void);
void TMRA_8_Ovf_IrqHandler(void);
void TMRA_8_Udf_IrqHandler(void);
void TMRA_8_Cmp_IrqHandler(void);
void TMRA_9_Ovf_IrqHandler(void);
void TMRA_9_Udf_IrqHandler(void);
void TMRA_9_Cmp_IrqHandler(void);
void TMRA_10_Ovf_IrqHandler(void);
void TMRA_10_Udf_IrqHandler(void);
void TMRA_10_Cmp_IrqHandler(void);
void TMRA_11_Ovf_IrqHandler(void);
void TMRA_11_Udf_IrqHandler(void);
void TMRA_11_Cmp_IrqHandler(void);
void TMRA_12_Ovf_IrqHandler(void);
void TMRA_12_Udf_IrqHandler(void);
void TMRA_12_Cmp_IrqHandler(void);
void EMB_GR0_IrqHandler(void);
void EMB_GR1_IrqHandler(void);
void EMB_GR2_IrqHandler(void);
void EMB_GR3_IrqHandler(void);
void EMB_GR4_IrqHandler(void);
void EMB_GR5_IrqHandler(void);
void EMB_GR6_IrqHandler(void);
void USART1_RxError_IrqHandler(void);
void USART1_RxFull_IrqHandler(void);
void USART1_TxEmpty_IrqHandler(void);
void USART1_TxComplete_IrqHandler(void);
void USART1_RxTO_IrqHandler(void);
void USART2_RxError_IrqHandler(void);
void USART2_RxFull_IrqHandler(void);
void USART2_TxEmpty_IrqHandler(void);
void USART2_TxComplete_IrqHandler(void);
void USART2_RxTO_IrqHandler(void);
void USART3_RxError_IrqHandler(void);
void USART3_RxFull_IrqHandler(void);
void USART3_TxEmpty_IrqHandler(void);
void USART3_TxComplete_IrqHandler(void);
void USART4_RxError_IrqHandler(void);
void USART4_RxFull_IrqHandler(void);
void USART4_TxEmpty_IrqHandler(void);
void USART4_TxComplete_IrqHandler(void);
void USART5_LinBreakField_IrqHandler(void);
void USART5_LinWakeup_IrqHandler(void);
void USART5_RxError_IrqHandler(void);
void USART5_RxFull_IrqHandler(void);
void USART5_TxEmpty_IrqHandler(void);
void USART5_TxComplete_IrqHandler(void);
void USART6_RxError_IrqHandler(void);
void USART6_RxFull_IrqHandler(void);
void USART6_TxEmpty_IrqHandler(void);
void USART6_TxComplete_IrqHandler(void);
void USART6_RxTO_IrqHandler(void);
void USART7_RxError_IrqHandler(void);
void USART7_RxFull_IrqHandler(void);
void USART7_TxEmpty_IrqHandler(void);
void USART7_TxComplete_IrqHandler(void);
void USART7_RxTO_IrqHandler(void);
void USART8_RxError_IrqHandler(void);
void USART8_RxFull_IrqHandler(void);
void USART8_TxEmpty_IrqHandler(void);
void USART8_TxComplete_IrqHandler(void);
void USART9_RxError_IrqHandler(void);
void USART9_RxFull_IrqHandler(void);
void USART9_TxEmpty_IrqHandler(void);
void USART9_TxComplete_IrqHandler(void);
void USART10_LinBreakField_IrqHandler(void);
void USART10_LinWakeup_IrqHandler(void);
void USART10_RxError_IrqHandler(void);
void USART10_RxFull_IrqHandler(void);
void USART10_TxEmpty_IrqHandler(void);
void USART10_TxComplete_IrqHandler(void);
void SPI1_RxFull_IrqHandler(void);
void SPI1_TxEmpty_IrqHandler(void);
void SPI1_Error_IrqHandler(void);
void SPI1_Idle_IrqHandler(void);
void SPI2_RxFull_IrqHandler(void);
void SPI2_TxEmpty_IrqHandler(void);
void SPI2_Error_IrqHandler(void);
void SPI2_Idle_IrqHandler(void);
void SPI3_RxFull_IrqHandler(void);
void SPI3_TxEmpty_IrqHandler(void);
void SPI3_Error_IrqHandler(void);
void SPI3_Idle_IrqHandler(void);
void SPI4_RxFull_IrqHandler(void);
void SPI4_TxEmpty_IrqHandler(void);
void SPI4_Error_IrqHandler(void);
void SPI4_Idle_IrqHandler(void);
void SPI5_RxFull_IrqHandler(void);
void SPI5_TxEmpty_IrqHandler(void);
void SPI5_Error_IrqHandler(void);
void SPI5_Idle_IrqHandler(void);
void SPI6_RxFull_IrqHandler(void);
void SPI6_TxEmpty_IrqHandler(void);
void SPI6_Error_IrqHandler(void);
void SPI6_Idle_IrqHandler(void);
void CAN1_IrqHandler(void);
void CAN2_IrqHandler(void);
void I2S1_Tx_IrqHandler(void);
void I2S1_Rx_IrqHandler(void);
void I2S1_Error_IrqHandler(void);
void I2S2_Tx_IrqHandler(void);
void I2S2_Rx_IrqHandler(void);
void I2S2_Error_IrqHandler(void);
void I2S3_Tx_IrqHandler(void);
void I2S3_Rx_IrqHandler(void);
void I2S3_Error_IrqHandler(void);
void I2S4_Tx_IrqHandler(void);
void I2S4_Rx_IrqHandler(void);
void I2S4_Error_IrqHandler(void);
void USBFS_Global_IrqHandler(void);
void SDIOC1_Normal_IrqHandler(void);
void SDIOC1_Error_IrqHandler(void);
void SDIOC2_Normal_IrqHandler(void);
void SDIOC2_Error_IrqHandler(void);
void ETH_Global_IrqHandler(void);
void ETH_Wakeup_IrqHandler(void);
void I2C1_RxFull_IrqHandler(void);
void I2C1_TxComplete_IrqHandler(void);
void I2C1_TxEmpty_IrqHandler(void);
void I2C1_EE_IrqHandler(void);
void I2C2_RxFull_IrqHandler(void);
void I2C2_TxComplete_IrqHandler(void);
void I2C2_TxEmpty_IrqHandler(void);
void I2C2_EE_IrqHandler(void);
void I2C3_RxFull_IrqHandler(void);
void I2C3_TxComplete_IrqHandler(void);
void I2C3_TxEmpty_IrqHandler(void);
void I2C3_EE_IrqHandler(void);
void I2C4_RxFull_IrqHandler(void);
void I2C4_TxComplete_IrqHandler(void);
void I2C4_TxEmpty_IrqHandler(void);
void I2C4_EE_IrqHandler(void);
void I2C5_RxFull_IrqHandler(void);
void I2C5_TxComplete_IrqHandler(void);
void I2C5_TxEmpty_IrqHandler(void);
void I2C5_EE_IrqHandler(void);
void I2C6_RxFull_IrqHandler(void);
void I2C6_TxComplete_IrqHandler(void);
void I2C6_TxEmpty_IrqHandler(void);
void I2C6_EE_IrqHandler(void);
void PWC_LVD1_IrqHandler(void);
void PWC_LVD2_IrqHandler(void);
void FCM_Error_IrqHandler(void);
void FCM_End_IrqHandler(void);
void FCM_Ovf_IrqHandler(void);
void CTC_Udf_IrqHandler(void);
void CTC_Ovf_IrqHandler(void);
void ADC1_SeqA_IrqHandler(void);
void ADC1_SeqB_IrqHandler(void);
void ADC1_Cmp0_IrqHandler(void);
void ADC1_Cmp1_IrqHandler(void);
void ADC1_CmpComb_IrqHandler(void);
void ADC2_SeqA_IrqHandler(void);
void ADC2_SeqB_IrqHandler(void);
void ADC2_Cmp0_IrqHandler(void);
void ADC2_Cmp1_IrqHandler(void);
void ADC2_CmpComb_IrqHandler(void);
void ADC3_SeqA_IrqHandler(void);
void ADC3_SeqB_IrqHandler(void);
void ADC3_Cmp0_IrqHandler(void);
void ADC3_Cmp1_IrqHandler(void);
void ADC3_CmpComb_IrqHandler(void);
void NFC_IrqHandler(void);

/**
 * @}
 */

#endif /* LL_INTERRUPTS_SHARE_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_LL_SHARE_INTERRUPTS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
