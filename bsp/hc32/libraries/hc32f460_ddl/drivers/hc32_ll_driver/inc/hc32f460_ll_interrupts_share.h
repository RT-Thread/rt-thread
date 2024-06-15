/**
 *******************************************************************************
 * @file  hc32f460_ll_interrupts_share.h
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
#ifndef __HC32F460_LL_INTERRUPTS_SHARE_H__
#define __HC32F460_LL_INTERRUPTS_SHARE_H__

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
 * @addtogroup LL_HC32F460_SHARE_INTERRUPTS
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
void DMA2_TC0_IrqHandler(void);
void DMA2_TC1_IrqHandler(void);
void DMA2_TC2_IrqHandler(void);
void DMA2_TC3_IrqHandler(void);
void DMA1_BTC0_IrqHandler(void);
void DMA1_BTC1_IrqHandler(void);
void DMA1_BTC2_IrqHandler(void);
void DMA1_BTC3_IrqHandler(void);
void DMA2_BTC0_IrqHandler(void);
void DMA2_BTC1_IrqHandler(void);
void DMA2_BTC2_IrqHandler(void);
void DMA2_BTC3_IrqHandler(void);
void DMA1_Error0_IrqHandler(void);
void DMA1_Error1_IrqHandler(void);
void DMA1_Error2_IrqHandler(void);
void DMA1_Error3_IrqHandler(void);
void DMA2_Error0_IrqHandler(void);
void DMA2_Error1_IrqHandler(void);
void DMA2_Error2_IrqHandler(void);
void DMA2_Error3_IrqHandler(void);

void EFM_ProgramEraseError_IrqHandler(void);
void EFM_ColError_IrqHandler(void);
void EFM_OpEnd_IrqHandler(void);
void QSPI_Error_IrqHandler(void);
void DCU1_IrqHandler(void);
void DCU2_IrqHandler(void);
void DCU3_IrqHandler(void);
void DCU4_IrqHandler(void);

void TMR0_1_CmpA_IrqHandler(void);
void TMR0_1_CmpB_IrqHandler(void);
void TMR0_2_CmpA_IrqHandler(void);
void TMR0_2_CmpB_IrqHandler(void);

void CLK_XtalStop_IrqHandler(void);
void PWC_WakeupTimer_IrqHandler(void);
void SWDT_IrqHandler(void);
void WDT_IrqHandler(void);

void TMR6_1_GCmpA_IrqHandler(void);
void TMR6_1_GCmpB_IrqHandler(void);
void TMR6_1_GCmpC_IrqHandler(void);
void TMR6_1_GCmpD_IrqHandler(void);
void TMR6_1_GCmpE_IrqHandler(void);
void TMR6_1_GCmpF_IrqHandler(void);
void TMR6_1_GOvf_IrqHandler(void);
void TMR6_1_GUdf_IrqHandler(void);
void TMR6_1_GDte_IrqHandler(void);
void TMR6_1_SCmpA_IrqHandler(void);
void TMR6_1_SCmpB_IrqHandler(void);

void TMR6_2_GCmpA_IrqHandler(void);
void TMR6_2_GCmpB_IrqHandler(void);
void TMR6_2_GCmpC_IrqHandler(void);
void TMR6_2_GCmpD_IrqHandler(void);
void TMR6_2_GCmpE_IrqHandler(void);
void TMR6_2_GCmpF_IrqHandler(void);
void TMR6_2_GOvf_IrqHandler(void);
void TMR6_2_GUdf_IrqHandler(void);
void TMR6_2_GDte_IrqHandler(void);
void TMR6_2_SCmpA_IrqHandler(void);
void TMR6_2_SCmpB_IrqHandler(void);

void TMR6_3_GCmpA_IrqHandler(void);
void TMR6_3_GCmpB_IrqHandler(void);
void TMR6_3_GCmpC_IrqHandler(void);
void TMR6_3_GCmpD_IrqHandler(void);
void TMR6_3_GCmpE_IrqHandler(void);
void TMR6_3_GCmpF_IrqHandler(void);
void TMR6_3_GOvf_IrqHandler(void);
void TMR6_3_GUdf_IrqHandler(void);
void TMR6_3_GDte_IrqHandler(void);
void TMR6_3_SCmpA_IrqHandler(void);
void TMR6_3_SCmpB_IrqHandler(void);

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

void USBFS_Global_IrqHandler(void);

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
void USART3_RxTO_IrqHandler(void);
void USART4_RxError_IrqHandler(void);
void USART4_RxFull_IrqHandler(void);
void USART4_TxEmpty_IrqHandler(void);
void USART4_TxComplete_IrqHandler(void);
void USART4_RxTO_IrqHandler(void);

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

void TMR4_1_GCmpUH_IrqHandler(void);
void TMR4_1_GCmpUL_IrqHandler(void);
void TMR4_1_GCmpVH_IrqHandler(void);
void TMR4_1_GCmpVL_IrqHandler(void);
void TMR4_1_GCmpWH_IrqHandler(void);
void TMR4_1_GCmpWL_IrqHandler(void);
void TMR4_1_GOvf_IrqHandler(void);
void TMR4_1_GUdf_IrqHandler(void);
void TMR4_1_ReloadU_IrqHandler(void);
void TMR4_1_ReloadV_IrqHandler(void);
void TMR4_1_ReloadW_IrqHandler(void);
void TMR4_2_GCmpUH_IrqHandler(void);
void TMR4_2_GCmpUL_IrqHandler(void);
void TMR4_2_GCmpVH_IrqHandler(void);
void TMR4_2_GCmpVL_IrqHandler(void);
void TMR4_2_GCmpWH_IrqHandler(void);
void TMR4_2_GCmpWL_IrqHandler(void);
void TMR4_2_GOvf_IrqHandler(void);
void TMR4_2_GUdf_IrqHandler(void);
void TMR4_2_ReloadU_IrqHandler(void);
void TMR4_2_ReloadV_IrqHandler(void);
void TMR4_2_ReloadW_IrqHandler(void);
void TMR4_3_GCmpUH_IrqHandler(void);
void TMR4_3_GCmpUL_IrqHandler(void);
void TMR4_3_GCmpVH_IrqHandler(void);
void TMR4_3_GCmpVL_IrqHandler(void);
void TMR4_3_GCmpWH_IrqHandler(void);
void TMR4_3_GCmpWL_IrqHandler(void);
void TMR4_3_GOvf_IrqHandler(void);
void TMR4_3_GUdf_IrqHandler(void);
void TMR4_3_ReloadU_IrqHandler(void);
void TMR4_3_ReloadV_IrqHandler(void);
void TMR4_3_ReloadW_IrqHandler(void);

void EMB_GR0_IrqHandler(void);
void EMB_GR1_IrqHandler(void);
void EMB_GR2_IrqHandler(void);
void EMB_GR3_IrqHandler(void);

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

void PWC_LVD1_IrqHandler(void);
void PWC_LVD2_IrqHandler(void);

void FCM_Error_IrqHandler(void);
void FCM_End_IrqHandler(void);
void FCM_Ovf_IrqHandler(void);

void ADC1_SeqA_IrqHandler(void);
void ADC1_SeqB_IrqHandler(void);
void ADC1_ChCmp_IrqHandler(void);
void ADC1_SeqCmp_IrqHandler(void);
void ADC2_SeqA_IrqHandler(void);
void ADC2_SeqB_IrqHandler(void);
void ADC2_ChCmp_IrqHandler(void);
void ADC2_SeqCmp_IrqHandler(void);

void SDIOC1_IrqHandler(void);
void SDIOC2_IrqHandler(void);

void CAN_IrqHandler(void);

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

#endif /* __HC32F4A0_LL_INTERRUPTS_SHARE_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
