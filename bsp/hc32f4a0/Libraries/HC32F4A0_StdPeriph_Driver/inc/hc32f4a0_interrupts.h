/**
 *******************************************************************************
 * @file  hc32f4a0_interrupts.h
 * @brief This file contains all the functions prototypes of the interrupt driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
   2020-08-25       Zhangxl         Modify for MISRAC2012-8.4
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_INTERRUPTS_H__
#define __HC32F4A0_INTERRUPTS_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_INTERRUPTS
 * @{
 */

#if (DDL_INTERRUPTS_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup INTC_Global_Types INTC Global Types
 * @{
 */
/**
 * @brief  Interrupt registration structure definition
 */
typedef struct
{
    en_int_src_t    enIntSrc;   /*!< Peripheral interrupt number, can be any value @ref en_int_src_t    */
    IRQn_Type       enIRQn;     /*!< Peripheral IRQ type, can be Int000_IRQn~Int127_IRQn @ref IRQn_Type */
    func_ptr_t      pfnCallback;/*!< Callback function for corresponding peripheral IRQ                 */
} stc_irq_signin_config_t;

/**
 * @brief  NMI initialize configuration structure definition
 */
typedef struct
{
    uint32_t    u32NmiSrc;      /*!< NMI trigger source, @ref NMI_TriggerSrc_Sel for details                */
    func_ptr_t  pfnNmiCallback; /*!< NMI Callback function pointers                                         */
}stc_nmi_init_t;

/**
 * @brief  EXINT initialize configuration structure definition
 */
typedef struct
{
    uint32_t    u32ExIntCh;     /*!< ExInt CH.0~15 @ref EXINT_Channel_Sel */
    uint32_t    u32ExIntFAE;    /*!< ExInt filter A function setting, @ref EXINT_FilterAClock_Sel for details */
    uint32_t    u32ExIntFAClk;  /*!< ExInt filter A clock division, @ref EXINT_FilterAClock_Div for details */
    uint32_t    u32ExIntFBE;    /*!< ExInt filter B function setting, @ref EXINT_FilterBClock_Sel for details*/
    uint32_t    u32ExIntFBTime; /*!< ExInt filter B time, @ref EXINT_FilterBTim_Sel for details*/
    uint32_t    u32ExIntLvl;    /*!< ExInt trigger edge, @ref EXINT_Trigger_Sel for details             */
}stc_exint_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup INTC_Global_Macros INTC Global Macros
 * @{
 */
/**
 * @defgroup INTC_DefaultPriority_Sel Interrupt default priority level
 * Possible values are 0 (high priority) to 15 (low priority)
 * @{
 */
#define DDL_IRQ_PRIORITY_DEFAULT    (15U)
/**
 * @}
 */

/**
 * @defgroup INTC_Priority_Sel Interrupt priority level 00 ~ 15
 * @{
 */
#define DDL_IRQ_PRIORITY_00         (0U)
#define DDL_IRQ_PRIORITY_01         (1U)
#define DDL_IRQ_PRIORITY_02         (2U)
#define DDL_IRQ_PRIORITY_03         (3U)
#define DDL_IRQ_PRIORITY_04         (4U)
#define DDL_IRQ_PRIORITY_05         (5U)
#define DDL_IRQ_PRIORITY_06         (6U)
#define DDL_IRQ_PRIORITY_07         (7U)
#define DDL_IRQ_PRIORITY_08         (8U)
#define DDL_IRQ_PRIORITY_09         (9U)
#define DDL_IRQ_PRIORITY_10         (10U)
#define DDL_IRQ_PRIORITY_11         (11U)
#define DDL_IRQ_PRIORITY_12         (12U)
#define DDL_IRQ_PRIORITY_13         (13U)
#define DDL_IRQ_PRIORITY_14         (14U)
#define DDL_IRQ_PRIORITY_15         (15U)
/**
 * @}
 */

/**
 * @defgroup INTC_Bit_mask definition Bit Mask
 * @{
 */
#define     BIT_MASK_00             (1UL << 0U)
#define     BIT_MASK_01             (1UL << 1U)
#define     BIT_MASK_02             (1UL << 2U)
#define     BIT_MASK_03             (1UL << 3U)
#define     BIT_MASK_04             (1UL << 4U)
#define     BIT_MASK_05             (1UL << 5U)
#define     BIT_MASK_06             (1UL << 6U)
#define     BIT_MASK_07             (1UL << 7U)
#define     BIT_MASK_08             (1UL << 8U)
#define     BIT_MASK_09             (1UL << 9U)
#define     BIT_MASK_10             (1UL << 10U)
#define     BIT_MASK_11             (1UL << 11U)
#define     BIT_MASK_12             (1UL << 12U)
#define     BIT_MASK_13             (1UL << 13U)
#define     BIT_MASK_14             (1UL << 14U)
#define     BIT_MASK_15             (1UL << 15U)
#define     BIT_MASK_16             (1UL << 16U)
#define     BIT_MASK_17             (1UL << 17U)
#define     BIT_MASK_18             (1UL << 18U)
#define     BIT_MASK_19             (1UL << 19U)
#define     BIT_MASK_20             (1UL << 20U)
#define     BIT_MASK_21             (1UL << 21U)
#define     BIT_MASK_22             (1UL << 22U)
#define     BIT_MASK_23             (1UL << 23U)
#define     BIT_MASK_24             (1UL << 24U)
#define     BIT_MASK_25             (1UL << 25U)
#define     BIT_MASK_26             (1UL << 26U)
#define     BIT_MASK_27             (1UL << 27U)
#define     BIT_MASK_28             (1UL << 28U)
#define     BIT_MASK_29             (1UL << 29U)
#define     BIT_MASK_30             (1UL << 30U)
#define     BIT_MASK_31             (1UL << 31U)
/**
 * @}
 */

/**
 * @defgroup NMI_TriggerSrc_Sel NMI trigger source selection
 * @{
 */
#define NMI_SRC_SWDT                (1UL << INTC_NMIFR_SWDTFR_POS)
#define NMI_SRC_PVD1                (1UL << INTC_NMIFR_PVD1FR_POS)
#define NMI_SRC_PVD2                (1UL << INTC_NMIFR_PVD2FR_POS)
#define NMI_SRC_XTAL                (1UL << INTC_NMIFR_XTALSTPFR_POS)
#define NMI_SRC_SRAM_PARITY         (1UL << INTC_NMIFR_REPFR_POS)
#define NMI_SRC_SRAM_ECC            (1UL << INTC_NMIFR_RECCFR_POS)
#define NMI_SRC_BUS_ERR             (1UL << INTC_NMIFR_BUSMFR_POS)
#define NMI_SRC_WDT                 (1UL << INTC_NMIFR_WDTFR_POS)
#define NMI_SRC_MASK                (NMI_SRC_SWDT   | NMI_SRC_PVD1          |   \
                                    NMI_SRC_PVD2    | NMI_SRC_XTAL          |   \
                                    NMI_SRC_BUS_ERR | NMI_SRC_SRAM_PARITY   |   \
                                    NMI_SRC_WDT     | NMI_SRC_SRAM_ECC)
/**
 * @}
 */

/**
 * @defgroup NOCCR_Register_Msk Noise cancel register mask
 * @{
 */
#define INTC_NOCCR_MASK     (INTC_NOCCR_NOCSEL)

/**
 * @}
 */


/**
 * @defgroup MNI_Register_Msk NMI register mask
 * @{
 */
#define INTC_NMIENR_MASK    (INTC_NMIENR_SWDTENR | INTC_NMIENR_PVD1ENR      |   \
                            INTC_NMIENR_PVD2ENR | INTC_NMIENR_XTALSTPENR    |   \
                            INTC_NMIENR_REPENR  | INTC_NMIENR_RECCENR       |   \
                            INTC_NMIENR_BUSMENR | INTC_NMIENR_WDTENR)

#define INTC_NMIFR_MASK     (INTC_NMIFR_SWDTFR | INTC_NMIFR_PVD1FR          |   \
                            INTC_NMIFR_PVD2FR   | INTC_NMIFR_XTALSTPFR      |   \
                            INTC_NMIFR_REPFR    | INTC_NMIFR_RECCFR         |   \
                            INTC_NMIFR_BUSMFR   | INTC_NMIFR_WDTFR)

#define INTC_NMICLR_MASK    (INTC_NMICFR_SWDTCFR  | INTC_NMICFR_PVD1CFR     |   \
                            INTC_NMICFR_PVD2CFR | INTC_NMICFR_XTALSTPCFR    |   \
                            INTC_NMICFR_REPCFR  | INTC_NMICFR_RECCCFR       |   \
                            INTC_NMICFR_BUSMCFR | INTC_NMICFR_WDTCFR)
/**
 * @}
 */

/**
 * @defgroup EXINT_Channel_Sel External interrupt channel selection
 * @{
 */
#define EXINT_CH00                  (1UL << 0U)
#define EXINT_CH01                  (1UL << 1U)
#define EXINT_CH02                  (1UL << 2U)
#define EXINT_CH03                  (1UL << 3U)
#define EXINT_CH04                  (1UL << 4U)
#define EXINT_CH05                  (1UL << 5U)
#define EXINT_CH06                  (1UL << 6U)
#define EXINT_CH07                  (1UL << 7U)
#define EXINT_CH08                  (1UL << 8U)
#define EXINT_CH09                  (1UL << 9U)
#define EXINT_CH10                  (1UL <<10U)
#define EXINT_CH11                  (1UL <<11U)
#define EXINT_CH12                  (1UL <<12U)
#define EXINT_CH13                  (1UL <<13U)
#define EXINT_CH14                  (1UL <<14U)
#define EXINT_CH15                  (1UL <<15U)
#define EXINT_CH_MASK   (EXINT_CH00 | EXINT_CH01 | EXINT_CH02 | EXINT_CH03 |    \
                         EXINT_CH04 | EXINT_CH05 | EXINT_CH06 | EXINT_CH07 |    \
                         EXINT_CH08 | EXINT_CH09 | EXINT_CH10 | EXINT_CH11 |    \
                         EXINT_CH12 | EXINT_CH13 | EXINT_CH14 | EXINT_CH15)
/**
 * @}
 */

/**
 * @defgroup EXINT_FilterAClock_Sel External interrupt filter A function selection
 * @{
 */
#define EXINT_FILTER_A_OFF          (0UL)
#define EXINT_FILTER_A_ON           (INTC_EIRQCR_EFEN)
/**
 * @}
 */

/**
 * @defgroup EXINT_FilterBClock_Sel External interrupt filter B function selection
 * @{
 */
#define EXINT_FILTER_B_OFF          (0UL)
#define EXINT_FILTER_B_ON           (INTC_EIRQCR_NOCEN)
/**
 * @}
 */

/**
 * @defgroup EXINT_FilterAClock_Div External interrupt filter A sampling clock division selection
 * @{
 */
#define EXINT_FACLK_HCLK_DIV1        (0UL)
#define EXINT_FACLK_HCLK_DIV8        (INTC_EIRQCR_EISMPCLK_0)
#define EXINT_FACLK_HCLK_DIV32       (INTC_EIRQCR_EISMPCLK_1)
#define EXINT_FACLK_HCLK_DIV64       (INTC_EIRQCR_EISMPCLK)
/**
 * @}
 */

/**
 * @defgroup EXINT_FilterBTim_Sel External interrupt filter B time selection
 * @{
 */
#define EXINT_FBTIM_500NS           (0UL << INTC_NOCCR_NOCSEL_POS)
#define EXINT_FBTIM_1US             (1UL << INTC_NOCCR_NOCSEL_POS)
#define EXINT_FBTIM_2US             (2UL << INTC_NOCCR_NOCSEL_POS)
#define EXINT_FBTIM_4US             (3UL << INTC_NOCCR_NOCSEL_POS)
/**
 * @}
 */

/**
 * @defgroup EXINT_Trigger_Sel External interrupt trigger method selection
 * @{
 */
#define EXINT_TRIGGER_FALLING       (0UL)
#define EXINT_TRIGGER_RISING        (INTC_EIRQCR_EIRQTRG_0)
#define EXINT_TRIGGER_BOTH          (INTC_EIRQCR_EIRQTRG_1)
#define EXINT_TRIGGER_LOW           (INTC_EIRQCR_EIRQTRG)

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup INTC_Global_Functions
 * @{
 */

/**
 * @brief  AOS software trigger.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void AOS_SW_Trigger(void)
{
    WRITE_REG32(bM4_AOS->INT_SFTTRG_b.STRG, Set);
}

/**
 * @brief  AOS common trigger source 1 config.
 * @param  [in] enTrig can be any value @ref en_event_src_t
 * @retval None
 */
__STATIC_INLINE void AOS_COM_Trigger1(en_event_src_t enTrig)
{
    WRITE_REG32(M4_AOS->COMTRG1, enTrig);
}

/**
 * @brief  AOS common trigger source 2 config.
 * @param  [in] enTrig can be any value @ref en_event_src_t
 * @retval None
 */
__STATIC_INLINE void AOS_COM_Trigger2(en_event_src_t enTrig)
{
    WRITE_REG32(M4_AOS->COMTRG2, enTrig);
}

en_result_t INTC_IrqSignIn(const stc_irq_signin_config_t *pstcIrqSignConfig);
en_result_t INTC_IrqSignOut(IRQn_Type enIRQn);
en_result_t INTC_ShareIrqCmd(en_int_src_t enIntSrc, en_functional_state_t enNewState);
void INTC_WakeupSrcCmd(uint32_t u32WakeupSrc, en_functional_state_t enNewState);
void INTC_EventCmd(uint32_t u32Event, en_functional_state_t enNewState);
void INTC_IntCmd(uint32_t u32Int, en_functional_state_t enNewState);
void INTC_SWICmd(uint32_t u32SWI, en_functional_state_t enNewState);

en_result_t NMI_Init(const stc_nmi_init_t *pstcNmiInit);
en_result_t NMI_StructInit(stc_nmi_init_t *pstcNmiInit);
en_flag_status_t NMI_GetNmiSrc(uint32_t u32NmiSrc);
void NMI_SetNmiSrc(uint32_t u32NmiSrc);
void NMI_ClrNmiSrc(uint32_t u32NmiSrc);

en_result_t EXINT_Init(const stc_exint_init_t *pstcExIntInit);
en_result_t EXINT_StructInit(stc_exint_init_t *pstcExIntInit);
en_flag_status_t EXINT_GetExIntSrc(uint32_t u32ExIntCh);
void EXINT_ClrExIntSrc(uint32_t u32ExIntCh);

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void IRQ000_Handler(void);
void IRQ001_Handler(void);
void IRQ002_Handler(void);
void IRQ003_Handler(void);
void IRQ004_Handler(void);
void IRQ005_Handler(void);
void IRQ006_Handler(void);
void IRQ007_Handler(void);
void IRQ008_Handler(void);
void IRQ009_Handler(void);
void IRQ010_Handler(void);
void IRQ011_Handler(void);
void IRQ012_Handler(void);
void IRQ013_Handler(void);
void IRQ014_Handler(void);
void IRQ015_Handler(void);
void IRQ016_Handler(void);
void IRQ017_Handler(void);
void IRQ018_Handler(void);
void IRQ019_Handler(void);
void IRQ020_Handler(void);
void IRQ021_Handler(void);
void IRQ022_Handler(void);
void IRQ023_Handler(void);
void IRQ024_Handler(void);
void IRQ025_Handler(void);
void IRQ026_Handler(void);
void IRQ027_Handler(void);
void IRQ028_Handler(void);
void IRQ029_Handler(void);
void IRQ030_Handler(void);
void IRQ031_Handler(void);
void IRQ032_Handler(void);
void IRQ033_Handler(void);
void IRQ034_Handler(void);
void IRQ035_Handler(void);
void IRQ036_Handler(void);
void IRQ037_Handler(void);
void IRQ038_Handler(void);
void IRQ039_Handler(void);
void IRQ040_Handler(void);
void IRQ041_Handler(void);
void IRQ042_Handler(void);
void IRQ043_Handler(void);
void IRQ044_Handler(void);
void IRQ045_Handler(void);
void IRQ046_Handler(void);
void IRQ047_Handler(void);
void IRQ048_Handler(void);
void IRQ049_Handler(void);
void IRQ050_Handler(void);
void IRQ051_Handler(void);
void IRQ052_Handler(void);
void IRQ053_Handler(void);
void IRQ054_Handler(void);
void IRQ055_Handler(void);
void IRQ056_Handler(void);
void IRQ057_Handler(void);
void IRQ058_Handler(void);
void IRQ059_Handler(void);
void IRQ060_Handler(void);
void IRQ061_Handler(void);
void IRQ062_Handler(void);
void IRQ063_Handler(void);
void IRQ064_Handler(void);
void IRQ065_Handler(void);
void IRQ066_Handler(void);
void IRQ067_Handler(void);
void IRQ068_Handler(void);
void IRQ069_Handler(void);
void IRQ070_Handler(void);
void IRQ071_Handler(void);
void IRQ072_Handler(void);
void IRQ073_Handler(void);
void IRQ074_Handler(void);
void IRQ075_Handler(void);
void IRQ076_Handler(void);
void IRQ077_Handler(void);
void IRQ078_Handler(void);
void IRQ079_Handler(void);
void IRQ080_Handler(void);
void IRQ081_Handler(void);
void IRQ082_Handler(void);
void IRQ083_Handler(void);
void IRQ084_Handler(void);
void IRQ085_Handler(void);
void IRQ086_Handler(void);
void IRQ087_Handler(void);
void IRQ088_Handler(void);
void IRQ089_Handler(void);
void IRQ090_Handler(void);
void IRQ091_Handler(void);
void IRQ092_Handler(void);
void IRQ093_Handler(void);
void IRQ094_Handler(void);
void IRQ095_Handler(void);
void IRQ096_Handler(void);
void IRQ097_Handler(void);
void IRQ098_Handler(void);
void IRQ099_Handler(void);
void IRQ100_Handler(void);
void IRQ101_Handler(void);
void IRQ102_Handler(void);
void IRQ103_Handler(void);
void IRQ104_Handler(void);
void IRQ105_Handler(void);
void IRQ106_Handler(void);
void IRQ107_Handler(void);
void IRQ108_Handler(void);
void IRQ109_Handler(void);
void IRQ110_Handler(void);
void IRQ111_Handler(void);
void IRQ112_Handler(void);
void IRQ113_Handler(void);
void IRQ114_Handler(void);
void IRQ115_Handler(void);
void IRQ116_Handler(void);
void IRQ117_Handler(void);
void IRQ118_Handler(void);
void IRQ119_Handler(void);
void IRQ120_Handler(void);
void IRQ121_Handler(void);
void IRQ122_Handler(void);
void IRQ123_Handler(void);
void IRQ124_Handler(void);
void IRQ125_Handler(void);
void IRQ126_Handler(void);
void IRQ127_Handler(void);
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

void NMI_IrqHandler(void);
void HardFault_IrqHandler(void);
void MemManage_IrqHandler(void);
void BusFault_IrqHandler(void);
void UsageFault_IrqHandler(void);
void SVC_IrqHandler(void);
void DebugMon_IrqHandler(void);
void PendSV_IrqHandler(void);
void SysTick_IrqHandler(void);
void EXTINT_00_IrqHandler(void);
void EXTINT_01_IrqHandler(void);
void EXTINT_02_IrqHandler(void);
void EXTINT_03_IrqHandler(void);
void EXTINT_04_IrqHandler(void);
void EXTINT_05_IrqHandler(void);
void EXTINT_06_IrqHandler(void);
void EXTINT_07_IrqHandler(void);
void EXTINT_08_IrqHandler(void);
void EXTINT_09_IrqHandler(void);
void EXTINT_10_IrqHandler(void);
void EXTINT_11_IrqHandler(void);
void EXTINT_12_IrqHandler(void);
void EXTINT_13_IrqHandler(void);
void EXTINT_14_IrqHandler(void);
void EXTINT_15_IrqHandler(void);
void DMA_1_Tc0_IrqHandler(void);
void DMA_1_Tc1_IrqHandler(void);
void DMA_1_Tc2_IrqHandler(void);
void DMA_1_Tc3_IrqHandler(void);
void DMA_1_Tc4_IrqHandler(void);
void DMA_1_Tc5_IrqHandler(void);
void DMA_1_Tc6_IrqHandler(void);
void DMA_1_Tc7_IrqHandler(void);
void DMA_1_Btc0_IrqHandler(void);
void DMA_1_Btc1_IrqHandler(void);
void DMA_1_Btc2_IrqHandler(void);
void DMA_1_Btc3_IrqHandler(void);
void DMA_1_Btc4_IrqHandler(void);
void DMA_1_Btc5_IrqHandler(void);
void DMA_1_Btc6_IrqHandler(void);
void DMA_1_Btc7_IrqHandler(void);
void DMA_1_Err0_IrqHandler(void);
void DMA_1_Err1_IrqHandler(void);
void DMA_1_Err2_IrqHandler(void);
void DMA_1_Err3_IrqHandler(void);
void DMA_1_Err4_IrqHandler(void);
void DMA_1_Err5_IrqHandler(void);
void DMA_1_Err6_IrqHandler(void);
void DMA_1_Err7_IrqHandler(void);
void DMA_2_Tc0_IrqHandler(void);
void DMA_2_Tc1_IrqHandler(void);
void DMA_2_Tc2_IrqHandler(void);
void DMA_2_Tc3_IrqHandler(void);
void DMA_2_Tc4_IrqHandler(void);
void DMA_2_Tc5_IrqHandler(void);
void DMA_2_Tc6_IrqHandler(void);
void DMA_2_Tc7_IrqHandler(void);
void DMA_2_Btc0_IrqHandler(void);
void DMA_2_Btc1_IrqHandler(void);
void DMA_2_Btc2_IrqHandler(void);
void DMA_2_Btc3_IrqHandler(void);
void DMA_2_Btc4_IrqHandler(void);
void DMA_2_Btc5_IrqHandler(void);
void DMA_2_Btc6_IrqHandler(void);
void DMA_2_Btc7_IrqHandler(void);
void DMA_2_Err0_IrqHandler(void);
void DMA_2_Err1_IrqHandler(void);
void DMA_2_Err2_IrqHandler(void);
void DMA_2_Err3_IrqHandler(void);
void DMA_2_Err4_IrqHandler(void);
void DMA_2_Err5_IrqHandler(void);
void DMA_2_Err6_IrqHandler(void);
void DMA_2_Err7_IrqHandler(void);
void EFM_PgmEraseErr_IrqHandler(void);
void EFM_ColErr_IrqHandler(void);
void EFM_OpEnd_IrqHandler(void);
void QSPI_Err_IrqHandler(void);
void MAU_Sqrt_IrqHandler(void);
void DVP_FrameStart_IrqHandler(void);
void DVP_FrameEnd_IrqHandler(void);
void DVP_LineStart_IrqHandler(void);
void DVP_LineEnd_IrqHandler(void);
void DVP_SwSyncErr_IrqHandler(void);
void DVP_FifoErr_IrqHandler(void);
void FMAC_1_IrqHandler(void);
void FMAC_2_IrqHandler(void);
void FMAC_3_IrqHandler(void);
void FMAC_4_IrqHandler(void);
void DCU_1_IrqHandler(void);
void DCU_2_IrqHandler(void);
void DCU_3_IrqHandler(void);
void DCU_4_IrqHandler(void);
void DCU_5_IrqHandler(void);
void DCU_6_IrqHandler(void);
void DCU_7_IrqHandler(void);
void DCU_8_IrqHandler(void);
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
void TMR6_1_Gdte_IrqHandler(void);
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
void TMR6_2_Gdte_IrqHandler(void);
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
void TMR6_3_Gdte_IrqHandler(void);
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
void TMRA_1_Cmp1_IrqHandler(void);
void TMRA_1_Cmp2_IrqHandler(void);
void TMRA_1_Cmp3_IrqHandler(void);
void TMRA_1_Cmp4_IrqHandler(void);
void TMRA_2_Ovf_IrqHandler(void);
void TMRA_2_Udf_IrqHandler(void);
void TMRA_2_Cmp1_IrqHandler(void);
void TMRA_2_Cmp2_IrqHandler(void);
void TMRA_2_Cmp3_IrqHandler(void);
void TMRA_2_Cmp4_IrqHandler(void);
void TMRA_3_Ovf_IrqHandler(void);
void TMRA_3_Udf_IrqHandler(void);
void TMRA_3_Cmp1_IrqHandler(void);
void TMRA_3_Cmp2_IrqHandler(void);
void TMRA_3_Cmp3_IrqHandler(void);
void TMRA_3_Cmp4_IrqHandler(void);
void TMRA_4_Ovf_IrqHandler(void);
void TMRA_4_Udf_IrqHandler(void);
void TMRA_4_Cmp1_IrqHandler(void);
void TMRA_4_Cmp2_IrqHandler(void);
void TMRA_4_Cmp3_IrqHandler(void);
void TMRA_4_Cmp4_IrqHandler(void);
void TMRA_5_Ovf_IrqHandler(void);
void TMRA_5_Udf_IrqHandler(void);
void TMRA_5_Cmp1_IrqHandler(void);
void TMRA_5_Cmp2_IrqHandler(void);
void TMRA_5_Cmp3_IrqHandler(void);
void TMRA_5_Cmp4_IrqHandler(void);
void TMRA_6_Ovf_IrqHandler(void);
void TMRA_6_Udf_IrqHandler(void);
void TMRA_6_Cmp1_IrqHandler(void);
void TMRA_6_Cmp2_IrqHandler(void);
void TMRA_6_Cmp3_IrqHandler(void);
void TMRA_6_Cmp4_IrqHandler(void);
void TMRA_7_Ovf_IrqHandler(void);
void TMRA_7_Udf_IrqHandler(void);
void TMRA_7_Cmp1_IrqHandler(void);
void TMRA_7_Cmp2_IrqHandler(void);
void TMRA_7_Cmp3_IrqHandler(void);
void TMRA_7_Cmp4_IrqHandler(void);
void TMRA_8_Ovf_IrqHandler(void);
void TMRA_8_Udf_IrqHandler(void);
void TMRA_8_Cmp1_IrqHandler(void);
void TMRA_8_Cmp2_IrqHandler(void);
void TMRA_8_Cmp3_IrqHandler(void);
void TMRA_8_Cmp4_IrqHandler(void);
void TMRA_9_Ovf_IrqHandler(void);
void TMRA_9_Udf_IrqHandler(void);
void TMRA_9_Cmp1_IrqHandler(void);
void TMRA_9_Cmp2_IrqHandler(void);
void TMRA_9_Cmp3_IrqHandler(void);
void TMRA_9_Cmp4_IrqHandler(void);
void TMRA_10_Ovf_IrqHandler(void);
void TMRA_10_Udf_IrqHandler(void);
void TMRA_10_Cmp1_IrqHandler(void);
void TMRA_10_Cmp2_IrqHandler(void);
void TMRA_10_Cmp3_IrqHandler(void);
void TMRA_10_Cmp4_IrqHandler(void);
void TMRA_11_Ovf_IrqHandler(void);
void TMRA_11_Udf_IrqHandler(void);
void TMRA_11_Cmp1_IrqHandler(void);
void TMRA_11_Cmp2_IrqHandler(void);
void TMRA_11_Cmp3_IrqHandler(void);
void TMRA_11_Cmp4_IrqHandler(void);
void TMRA_12_Ovf_IrqHandler(void);
void TMRA_12_Udf_IrqHandler(void);
void TMRA_12_Cmp1_IrqHandler(void);
void TMRA_12_Cmp2_IrqHandler(void);
void TMRA_12_Cmp3_IrqHandler(void);
void TMRA_12_Cmp4_IrqHandler(void);
void EMB_GR0_IrqHandler(void);
void EMB_GR1_IrqHandler(void);
void EMB_GR2_IrqHandler(void);
void EMB_GR3_IrqHandler(void);
void EMB_GR4_IrqHandler(void);
void EMB_GR5_IrqHandler(void);
void EMB_GR6_IrqHandler(void);
void USART_1_RxErr_IrqHandler(void);
void USART_1_RxEnd_IrqHandler(void);
void USART_1_TxEmpty_IrqHandler(void);
void USART_1_TxEnd_IrqHandler(void);
void USART_1_RxTO_IrqHandler(void);
void USART_2_RxErr_IrqHandler(void);
void USART_2_RxEnd_IrqHandler(void);
void USART_2_TxEmpty_IrqHandler(void);
void USART_2_TxEnd_IrqHandler(void);
void USART_2_RxTO_IrqHandler(void);
void USART_3_RxErr_IrqHandler(void);
void USART_3_RxEnd_IrqHandler(void);
void USART_3_TxEmpty_IrqHandler(void);
void USART_3_TxEnd_IrqHandler(void);
void USART_4_RxErr_IrqHandler(void);
void USART_4_RxEnd_IrqHandler(void);
void USART_4_TxEmpty_IrqHandler(void);
void USART_4_TxEnd_IrqHandler(void);
void USART_5_LinBreakField_IrqHandler(void);
void USART_5_LinWakeup_IrqHandler(void);
void USART_5_RxErr_IrqHandler(void);
void USART_5_RxEnd_IrqHandler(void);
void USART_5_TxEmpty_IrqHandler(void);
void USART_5_TxEnd_IrqHandler(void);
void USART_6_RxErr_IrqHandler(void);
void USART_6_RxEnd_IrqHandler(void);
void USART_6_TxEmpty_IrqHandler(void);
void USART_6_TxEnd_IrqHandler(void);
void USART_6_RxTO_IrqHandler(void);
void USART_7_RxErr_IrqHandler(void);
void USART_7_RxEnd_IrqHandler(void);
void USART_7_TxEmpty_IrqHandler(void);
void USART_7_TxEnd_IrqHandler(void);
void USART_7_RxTO_IrqHandler(void);
void USART_8_RxErr_IrqHandler(void);
void USART_8_RxEnd_IrqHandler(void);
void USART_8_TxEmpty_IrqHandler(void);
void USART_8_TxEnd_IrqHandler(void);
void USART_9_RxErr_IrqHandler(void);
void USART_9_RxEnd_IrqHandler(void);
void USART_9_TxEmpty_IrqHandler(void);
void USART_9_TxEnd_IrqHandler(void);
void USART_10_LinBreakField_IrqHandler(void);
void USART_10_LinWakeup_IrqHandler(void);
void USART_10_RxErr_IrqHandler(void);
void USART_10_RxEnd_IrqHandler(void);
void USART_10_TxEmpty_IrqHandler(void);
void USART_10_TxEnd_IrqHandler(void);
void SPI_1_RxEnd_IrqHandler(void);
void SPI_1_TxEmpty_IrqHandler(void);
void SPI_1_Err_IrqHandler(void);
void SPI_1_Idle_IrqHandler(void);
void SPI_2_RxEnd_IrqHandler(void);
void SPI_2_TxEmpty_IrqHandler(void);
void SPI_2_Err_IrqHandler(void);
void SPI_2_Idle_IrqHandler(void);
void SPI_3_RxEnd_IrqHandler(void);
void SPI_3_TxEmpty_IrqHandler(void);
void SPI_3_Err_IrqHandler(void);
void SPI_3_Idle_IrqHandler(void);
void SPI_4_RxEnd_IrqHandler(void);
void SPI_4_TxEmpty_IrqHandler(void);
void SPI_4_Err_IrqHandler(void);
void SPI_4_Idle_IrqHandler(void);
void SPI_5_RxEnd_IrqHandler(void);
void SPI_5_TxEmpty_IrqHandler(void);
void SPI_5_Err_IrqHandler(void);
void SPI_5_Idle_IrqHandler(void);
void SPI_6_RxEnd_IrqHandler(void);
void SPI_6_TxEmpty_IrqHandler(void);
void SPI_6_Err_IrqHandler(void);
void SPI_6_Idle_IrqHandler(void);
void CAN_1_IrqHandler(void);
void CAN_2_IrqHandler(void);
void I2S_1_Tx_IrqHandler(void);
void I2S_1_Rx_IrqHandler(void);
void I2S_1_Err_IrqHandler(void);
void I2S_2_Tx_IrqHandler(void);
void I2S_2_Rx_IrqHandler(void);
void I2S_2_Err_IrqHandler(void);
void I2S_3_Tx_IrqHandler(void);
void I2S_3_Rx_IrqHandler(void);
void I2S_3_Err_IrqHandler(void);
void I2S_4_Tx_IrqHandler(void);
void I2S_4_Rx_IrqHandler(void);
void I2S_4_Err_IrqHandler(void);
void USBFS_Global_IrqHandler(void);
void SDIOC_1_Normal_IrqHandler(void);
void SDIOC_1_Error_IrqHandler(void);
void SDIOC_2_Normal_IrqHandler(void);
void SDIOC_2_Error_IrqHandler(void);
void ETH_Global_IrqHandler(void);
void ETH_Wakeup_IrqHandler(void);
void I2C_1_RxEnd_IrqHandler(void);
void I2C_1_TxEnd_IrqHandler(void);
void I2C_1_TxEmpty_IrqHandler(void);
void I2C_1_Err_IrqHandler(void);
void I2C_2_RxEnd_IrqHandler(void);
void I2C_2_TxEnd_IrqHandler(void);
void I2C_2_TxEmpty_IrqHandler(void);
void I2C_2_Err_IrqHandler(void);
void I2C_3_RxEnd_IrqHandler(void);
void I2C_3_TxEnd_IrqHandler(void);
void I2C_3_TxEmpty_IrqHandler(void);
void I2C_3_Err_IrqHandler(void);
void I2C_4_RxEnd_IrqHandler(void);
void I2C_4_TxEnd_IrqHandler(void);
void I2C_4_TxEmpty_IrqHandler(void);
void I2C_4_Err_IrqHandler(void);
void I2C_5_RxEnd_IrqHandler(void);
void I2C_5_TxEnd_IrqHandler(void);
void I2C_5_TxEmpty_IrqHandler(void);
void I2C_5_Err_IrqHandler(void);
void I2C_6_RxEnd_IrqHandler(void);
void I2C_6_TxEnd_IrqHandler(void);
void I2C_6_TxEmpty_IrqHandler(void);
void I2C_6_Err_IrqHandler(void);
void PWC_Pvd1_IrqHandler(void);
void PWC_Pvd2_IrqHandler(void);
void FCM_Err_IrqHandler(void);
void FCM_End_IrqHandler(void);
void FCM_Ovf_IrqHandler(void);
void CTC_Udf_IrqHandler(void);
void CTC_Ovf_IrqHandler(void);
void ADC_1_SeqA_IrqHandler(void);
void ADC_1_SeqB_IrqHandler(void);
void ADC_1_Cmp0_IrqHandler(void);
void ADC_1_Cmp1Ind_IrqHandler(void);
void ADC_1_Cmp1Comb_IrqHandler(void);
void ADC_2_SeqA_IrqHandler(void);
void ADC_2_SeqB_IrqHandler(void);
void ADC_2_Cmp0_IrqHandler(void);
void ADC_2_Cmp1Ind_IrqHandler(void);
void ADC_2_Cmp1Comb_IrqHandler(void);
void ADC_3_SeqA_IrqHandler(void);
void ADC_3_SeqB_IrqHandler(void);
void ADC_3_Cmp0_IrqHandler(void);
void ADC_3_Cmp1Ind_IrqHandler(void);
void ADC_3_Cmp1Comb_IrqHandler(void);
void NFC_IrqHandler(void);

/**
 * @}
 */

#endif /* DDL_INTERRUPTS_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_INTERRUPTS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
