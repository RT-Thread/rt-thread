/**
 *******************************************************************************
 * @file  hc32f460_ll_interrupts_share.c
 * @brief This file provides firmware functions to manage the Share Interrupt
 *        Controller (SHARE_INTERRUPTS).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-01-15       CDT             Bug fix of TMRA CMP DCU and USART, refine IRQ143
                                    Rename I2Cx_Error_IrqHandler as I2Cx_EE_IrqHandler
   2023-09-30       CDT             IRQxxx_Handler add __DSB for Arm Errata 838869
                                    The BCSTR register of TimerA is split into BCSTRH and BCSTRL
                                    Modify for head file update: EIRQFR -> EIFR
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_ll_interrupts_share.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_HC32F460_SHARE_INTERRUPTS SHARE_INTERRUPTS
 * @brief Share Interrupts Driver Library
 * @{
 */

#if (LL_INTERRUPTS_SHARE_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup Share_Interrupts_Global_Functions Share Interrupts Global Functions
 * @{
 */
/**
 * @brief  Share IRQ configure
 * @param  [in] enIntSrc: Peripheral interrupt source @ref en_int_src_t
 * @param  [in] enNewState: An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *           - LL_OK: Share IRQ configure successfully
 */
int32_t INTC_ShareIrqCmd(en_int_src_t enIntSrc, en_functional_state_t enNewState)
{
    __IO uint32_t *INTC_VSSELx;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    INTC_VSSELx = (__IO uint32_t *)(((uint32_t)&CM_INTC->VSSEL128) + (4U * ((uint32_t)enIntSrc / 0x20U)));
    if (ENABLE == enNewState) {
        SET_REG32_BIT(*INTC_VSSELx, (1UL << ((uint32_t)enIntSrc & 0x1FUL)));
    } else {
        CLR_REG32_BIT(*INTC_VSSELx, (1UL << ((uint32_t)enIntSrc & 0x1FUL)));
    }
    return LL_OK;
}

/**
 * @brief  Interrupt No.128 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ128_Handler(void)
{
    const uint32_t VSSEL128 = CM_INTC->VSSEL128;

    /* external interrupt 00 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR0) && (0UL != (VSSEL128 & BIT_MASK_00))) {
        EXTINT00_IrqHandler();
    }
    /* external interrupt 01 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR1) && (0UL != (VSSEL128 & BIT_MASK_01))) {
        EXTINT01_IrqHandler();
    }
    /* external interrupt 02 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR2) && (0UL != (VSSEL128 & BIT_MASK_02))) {
        EXTINT02_IrqHandler();
    }
    /* external interrupt 03 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR3) && (0UL != (VSSEL128 & BIT_MASK_03))) {
        EXTINT03_IrqHandler();
    }
    /* external interrupt 04 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR4) && (0UL != (VSSEL128 & BIT_MASK_04))) {
        EXTINT04_IrqHandler();
    }
    /* external interrupt 05 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR5) && (0UL != (VSSEL128 & BIT_MASK_05))) {
        EXTINT05_IrqHandler();
    }
    /* external interrupt 06 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR6) && (0UL != (VSSEL128 & BIT_MASK_06))) {
        EXTINT06_IrqHandler();
    }
    /* external interrupt 07 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR7) && (0UL != (VSSEL128 & BIT_MASK_07))) {
        EXTINT07_IrqHandler();
    }
    /* external interrupt 08 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR8) && (0UL != (VSSEL128 & BIT_MASK_08))) {
        EXTINT08_IrqHandler();
    }
    /* external interrupt 09 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR9) && (0UL != (VSSEL128 & BIT_MASK_09))) {
        EXTINT09_IrqHandler();
    }
    /* external interrupt 10 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR10) && (0UL != (VSSEL128 & BIT_MASK_10))) {
        EXTINT10_IrqHandler();
    }
    /* external interrupt 11 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR11) && (0UL != (VSSEL128 & BIT_MASK_11))) {
        EXTINT11_IrqHandler();
    }
    /* external interrupt 12 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR12) && (0UL != (VSSEL128 & BIT_MASK_12))) {
        EXTINT12_IrqHandler();
    }
    /* external interrupt 13 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR13) && (0UL != (VSSEL128 & BIT_MASK_13))) {
        EXTINT13_IrqHandler();
    }
    /* external interrupt 14 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR14) && (0UL != (VSSEL128 & BIT_MASK_14))) {
        EXTINT14_IrqHandler();
    }
    /* external interrupt 15 */
    if ((1UL == bCM_INTC->EIFR_b.EIFR15) && (0UL != (VSSEL128 & BIT_MASK_15))) {
        EXTINT15_IrqHandler();
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.129 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ129_Handler(void)
{
    const uint32_t VSSEL129 = CM_INTC->VSSEL129;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* DMA1 Ch.0 interrupt enabled */
    if (1UL == bCM_DMA1->CHCTL0_b.IE) {
        /* DMA1 Ch.0 Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKTC0) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.TC0) && (0UL != (VSSEL129 & BIT_MASK_00))) {
                DMA1_TC0_IrqHandler();
            }
        }
        /* DMA1 ch.0 Block Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKBTC0) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC0) && (0UL != (VSSEL129 & BIT_MASK_08))) {
                DMA1_BTC0_IrqHandler();
            }
        }
        /* DMA1 ch.0 Transfer/Request Error */
        u32Tmp1 = CM_DMA1->INTSTAT0 & (BIT_MASK_00 | BIT_MASK_16);
        u32Tmp2 = (uint32_t)(~(CM_DMA1->INTMASK0) & (BIT_MASK_00 | BIT_MASK_16));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16))) {
            DMA1_Error0_IrqHandler();
        }
    }
    /* DMA1 Ch.1 interrupt enabled */
    if (1UL == bCM_DMA1->CHCTL1_b.IE) {
        /* DMA1 Ch.1 Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKTC1) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.TC1) && (0UL != (VSSEL129 & BIT_MASK_01))) {
                DMA1_TC1_IrqHandler();
            }
        }
        /* DMA1 ch.1 Block Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKBTC1) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC1) && (0UL != (VSSEL129 & BIT_MASK_09))) {
                DMA1_BTC1_IrqHandler();
            }
        }
        /* DMA1 ch.1 Transfer/Request Error */
        u32Tmp1 = CM_DMA1->INTSTAT0 & (BIT_MASK_01 | BIT_MASK_17);
        u32Tmp2 = (uint32_t)(~(CM_DMA1->INTMASK0) & (BIT_MASK_01 | BIT_MASK_17));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16))) {
            DMA1_Error1_IrqHandler();
        }
    }
    /* DMA1 Ch.2 interrupt enabled */
    if (1UL == bCM_DMA1->CHCTL2_b.IE) {
        /* DMA1 Ch.2 Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKTC2) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.TC2) && (0UL != (VSSEL129 & BIT_MASK_02))) {
                DMA1_TC2_IrqHandler();
            }
        }
        /* DMA1 ch.2 Block Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKBTC2) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC2) && (0UL != (VSSEL129 & BIT_MASK_10))) {
                DMA1_BTC2_IrqHandler();
            }
        }
        /* DMA1 ch.2 Transfer/Request Error */
        u32Tmp1 = CM_DMA1->INTSTAT0 & (BIT_MASK_02 | BIT_MASK_18);
        u32Tmp2 = (uint32_t)(~(CM_DMA1->INTMASK0) & (BIT_MASK_02 | BIT_MASK_18));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16))) {
            DMA1_Error2_IrqHandler();
        }
    }
    /* DMA1 Ch.3 interrupt enabled */
    if (1UL == bCM_DMA1->CHCTL3_b.IE) {
        /* DMA1 Ch.3 Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKTC3) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.TC3) && (0UL != (VSSEL129 & BIT_MASK_03))) {
                DMA1_TC3_IrqHandler();
            }
        }
        /* DMA1 ch.3 Block Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKBTC3) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC3) && (0UL != (VSSEL129 & BIT_MASK_11))) {
                DMA1_BTC3_IrqHandler();
            }
        }
        /* DMA1 ch.3 Transfer/Request Error */
        u32Tmp1 = CM_DMA1->INTSTAT0 & (BIT_MASK_03 | BIT_MASK_19);
        u32Tmp2 = (uint32_t)(~(CM_DMA1->INTMASK0) & (BIT_MASK_03 | BIT_MASK_19));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16))) {
            DMA1_Error3_IrqHandler();
        }
    }
    /* DMA2 Ch.0 interrupt enabled */
    if (1UL == bCM_DMA2->CHCTL0_b.IE) {
        /* DMA2 ch.0 Tx completed */
        if (0UL == bCM_DMA2->INTMASK1_b.MSKTC0) {
            if ((1UL == bCM_DMA2->INTSTAT1_b.TC0) && (0UL != (VSSEL129 & BIT_MASK_04))) {
                DMA2_TC0_IrqHandler();
            }
        }
        /* DMA2 ch.0 Block Tx completed */
        if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC0) {
            if ((1UL == bCM_DMA2->INTSTAT1_b.BTC0) && (0UL != (VSSEL129 & BIT_MASK_12))) {
                DMA2_BTC0_IrqHandler();
            }
        }
        /* DMA2 Ch.0 Transfer/Request Error */
        u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_00 | BIT_MASK_16);
        u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_00 | BIT_MASK_16));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_17))) {
            DMA2_Error0_IrqHandler();
        }
    }
    if (1UL == bCM_DMA2->CHCTL1_b.IE) {
        /* DMA2 ch.1 Tx completed */
        if (0UL == bCM_DMA2->INTMASK1_b.MSKTC1) {
            if ((1UL == bCM_DMA2->INTSTAT1_b.TC1) && (0UL != (VSSEL129 & BIT_MASK_05))) {
                DMA2_TC1_IrqHandler();
            }
        }
        /* DMA2 ch.1 Block Tx completed */
        if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC1) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC1) && (0UL != (VSSEL129 & BIT_MASK_13))) {
                DMA2_BTC1_IrqHandler();
            }
        }
        /* DMA2 Ch.1 Transfer/Request Error */
        u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_01 | BIT_MASK_17);
        u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_01 | BIT_MASK_17));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_17))) {
            DMA2_Error1_IrqHandler();
        }
    }
    if (1UL == bCM_DMA2->CHCTL2_b.IE) {
        /* DMA2 ch.2 Tx completed */
        if (0UL == bCM_DMA2->INTMASK1_b.MSKTC2) {
            if ((1UL == bCM_DMA2->INTSTAT1_b.TC2) && (0UL != (VSSEL129 & BIT_MASK_06))) {
                DMA2_TC2_IrqHandler();
            }
        }
        /* DMA2 ch.2 Block Tx completed */
        if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC2) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC2) && (0UL != (VSSEL129 & BIT_MASK_14))) {
                DMA2_BTC2_IrqHandler();
            }
        }
        /* DMA2 Ch.2 Transfer/Request Error */
        u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_02 | BIT_MASK_18);
        u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_02 | BIT_MASK_18));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_17))) {
            DMA2_Error2_IrqHandler();
        }
    }
    if (1UL == bCM_DMA2->CHCTL3_b.IE) {
        /* DMA2 ch.3 Tx completed */
        if (0UL == bCM_DMA2->INTMASK1_b.MSKTC3) {
            if ((1UL == bCM_DMA2->INTSTAT1_b.TC3) && (0UL != (VSSEL129 & BIT_MASK_07))) {
                DMA2_TC3_IrqHandler();
            }
        }
        /* DMA2 ch.3 Block Tx completed */
        if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC3) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC3) && (0UL != (VSSEL129 & BIT_MASK_15))) {
                DMA2_BTC3_IrqHandler();
            }
        }
        /* DMA2 Ch.3 Transfer/Request Error */
        u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_03 | BIT_MASK_19);
        u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_03 | BIT_MASK_19));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_17))) {
            DMA2_Error3_IrqHandler();
        }
    }
    /* EFM program/erase Error */
    if (1UL == bCM_EFM->FITE_b.PEERRITE) {
        if ((0UL != (CM_EFM->FSR & 0x0FU)) && (0UL != (VSSEL129 & BIT_MASK_18))) {
            EFM_ProgramEraseError_IrqHandler();
        }
    }
    /* EFM read collision error*/
    if (1UL == bCM_EFM->FITE_b.COLERRITE) {
        /* EFM read collision */
        if ((1UL == bCM_EFM->FSR_b.COLERR) && (0UL != (VSSEL129 & BIT_MASK_19))) {
            EFM_ColError_IrqHandler();
        }
    }
    /* EFM operate end */
    if (1UL == bCM_EFM->FITE_b.OPTENDITE) {
        /* EFM operate end */
        if ((1UL == bCM_EFM->FSR_b.OPTEND) && (0UL != (VSSEL129 & BIT_MASK_20))) {
            EFM_OpEnd_IrqHandler();
        }
    }
    /* QSPI access error */
    if ((0UL != (CM_QSPI->SR & QSPI_SR_RAER)) && (0UL != (VSSEL129 & BIT_MASK_22))) {
        QSPI_Error_IrqHandler();
    }
    /*DCU1 */
    if (1UL == bCM_DCU1->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU1->INTEVTSEL;
        u32Tmp2 = CM_DCU1->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x7FUL)) && (0UL != (VSSEL129 & BIT_MASK_23))) {
            DCU1_IrqHandler();
        }
    }
    /*DCU2 */
    if (1UL == bCM_DCU2->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU2->INTEVTSEL;
        u32Tmp2 = CM_DCU2->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x7FUL)) && (0UL != (VSSEL129 & BIT_MASK_24))) {
            DCU2_IrqHandler();
        }
    }
    /*DCU3 */
    if (1UL == bCM_DCU3->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU3->INTEVTSEL;
        u32Tmp2 = CM_DCU3->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x7FUL)) && (0UL != (VSSEL129 & BIT_MASK_25))) {
            DCU3_IrqHandler();
        }
    }
    /*DCU4 */
    if (1UL == bCM_DCU4->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU4->INTEVTSEL;
        u32Tmp2 = CM_DCU4->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x7FUL)) && (0UL != (VSSEL129 & BIT_MASK_26))) {
            DCU4_IrqHandler();
        }
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.130 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ130_Handler(void)
{
    const uint32_t VSSEL130 = CM_INTC->VSSEL130;
    /* Timer0 Ch. 1 A compare match */
    if (1UL == bCM_TMR0_1->BCONR_b.INTENA) {
        if ((1UL == bCM_TMR0_1->STFLR_b.CMFA) && (0UL != (VSSEL130 & BIT_MASK_00))) {
            TMR0_1_CmpA_IrqHandler();
        }
    }
    /* Timer0 Ch. 1 B compare match */
    if (1UL == bCM_TMR0_1->BCONR_b.INTENB) {
        if ((1UL == bCM_TMR0_1->STFLR_b.CMFB) && (0UL != (VSSEL130 & BIT_MASK_01))) {
            TMR0_1_CmpB_IrqHandler();
        }
    }
    /* Timer0 Ch. 2 A compare match */
    if (1UL == bCM_TMR0_2->BCONR_b.INTENA) {
        if ((1UL == bCM_TMR0_2->STFLR_b.CMFA) && (0UL != (VSSEL130 & BIT_MASK_02))) {
            TMR0_2_CmpA_IrqHandler();
        }
    }
    /* Timer0 Ch. 2 B compare match */
    if (1UL == bCM_TMR0_2->BCONR_b.INTENB) {
        if ((1UL == bCM_TMR0_2->STFLR_b.CMFB) && (0UL != (VSSEL130 & BIT_MASK_03))) {
            TMR0_2_CmpB_IrqHandler();
        }
    }
    /* Main-OSC stop */
    if (CMU_XTALSTDCR_XTALSTDIE ==  READ_REG8_BIT(CM_CMU->XTALSTDCR, CMU_XTALSTDCR_XTALSTDIE)) {
        if ((CMU_XTALSTDSR_XTALSTDF == READ_REG8_BIT(CM_CMU->XTALSTDSR, CMU_XTALSTDSR_XTALSTDF)) && \
            (0UL != (VSSEL130 & BIT_MASK_21))) {
            CLK_XtalStop_IrqHandler();
        }
    }
    /* Wakeup timer */
    if ((PWC_WKTCR_WKOVF == READ_REG16_BIT(CM_PWC->WKTCR, PWC_WKTCR_WKOVF)) && (0UL != (VSSEL130 & BIT_MASK_22))) {
        PWC_WakeupTimer_IrqHandler();
    }
    /* SWDT */
    if ((0UL != (CM_SWDT->SR & (BIT_MASK_16 | BIT_MASK_17))) && (0UL != (VSSEL130 & BIT_MASK_23))) {
        SWDT_IrqHandler();
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.131 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ131_Handler(void)
{
    const uint32_t VSSEL131 = CM_INTC->VSSEL131;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;
    /* Timer6 Unit.1 A compare match */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMAF) && (0UL != (VSSEL131 & BIT_MASK_00))) {
            TMR6_1_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.1 B compare match */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMBF) && (0UL != (VSSEL131 & BIT_MASK_01))) {
            TMR6_1_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.1 C compare match */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMCF) && (0UL != (VSSEL131 & BIT_MASK_02))) {
            TMR6_1_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.1 D compare match */
    if (1UL == bCM_TMR6_1->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMDF) && (0UL != (VSSEL131 & BIT_MASK_03))) {
            TMR6_1_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.1 E compare match */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMEF) && (0UL != (VSSEL131 & BIT_MASK_04))) {
            TMR6_1_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.1 F compare match */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMFF) && (0UL != (VSSEL131 & BIT_MASK_05))) {
            TMR6_1_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.1 overflow */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_1->STFLR_b.OVFF) && (0UL != (VSSEL131 & BIT_MASK_06))) {
            TMR6_1_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.1 underflow */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_1->STFLR_b.UDFF) && (0UL != (VSSEL131 & BIT_MASK_07))) {
            TMR6_1_GUdf_IrqHandler();
        }
    }
    /* Timer6 Unit.1 dead time */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENDTE) {
        if (((1UL == bCM_TMR6_1->STFLR_b.DTEF)) && (0UL != (VSSEL131 & BIT_MASK_08))) {
            TMR6_1_GDte_IrqHandler();
        }
    }
    /* Timer6 Unit.1 A up-down compare match */
    u32Tmp1 = (CM_TMR6_1->ICONR & (BIT_MASK_16 | BIT_MASK_17)) >> 7U;
    u32Tmp2 = CM_TMR6_1->STFLR & (BIT_MASK_09 | BIT_MASK_10);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL131 & BIT_MASK_11))) {
        TMR6_1_SCmpA_IrqHandler();
    }
    /* Timer6 Unit.1 B up-down compare match */
    u32Tmp1 = (CM_TMR6_1->ICONR & (BIT_MASK_18 | BIT_MASK_19)) >> 7U;
    u32Tmp2 = CM_TMR6_1->STFLR & (BIT_MASK_11 | BIT_MASK_12);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL131 & BIT_MASK_12))) {
        TMR6_1_SCmpB_IrqHandler();
    }
    /* Timer6 Unit.2 A compare match */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMAF) && (0UL != (VSSEL131 & BIT_MASK_16))) {
            TMR6_2_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.2 B compare match */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMBF) && (0UL != (VSSEL131 & BIT_MASK_17))) {
            TMR6_2_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.2 C compare match */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMCF) && (0UL != (VSSEL131 & BIT_MASK_18))) {
            TMR6_2_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.2 D compare match */
    if (1UL == bCM_TMR6_2->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMDF) && (0UL != (VSSEL131 & BIT_MASK_19))) {
            TMR6_2_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.2 E compare match */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMEF) && (0UL != (VSSEL131 & BIT_MASK_20))) {
            TMR6_2_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.2 F compare match */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMFF) && (0UL != (VSSEL131 & BIT_MASK_21))) {
            TMR6_2_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.2 overflow */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_2->STFLR_b.OVFF) && (0UL != (VSSEL131 & BIT_MASK_22))) {
            TMR6_2_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.2 underflow */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_2->STFLR_b.UDFF) && (0UL != (VSSEL131 & BIT_MASK_23))) {
            TMR6_2_GUdf_IrqHandler();
        }
    }
    /* Timer6 Unit.2 dead time */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_2->STFLR_b.DTEF) && (0UL != (VSSEL131 & BIT_MASK_24))) {
            TMR6_2_GDte_IrqHandler();
        }
    }
    /* Timer6 Unit.2 A up-down compare match */
    u32Tmp1 = (CM_TMR6_2->ICONR & (BIT_MASK_16 | BIT_MASK_17)) >> 7U;
    u32Tmp2 = CM_TMR6_2->STFLR & (BIT_MASK_09 | BIT_MASK_10);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL131 & BIT_MASK_27))) {
        TMR6_2_SCmpA_IrqHandler();
    }
    /* Timer6 Unit.2 B up-down compare match */
    u32Tmp1 = (CM_TMR6_2->ICONR & (BIT_MASK_18 | BIT_MASK_19)) >> 7U;
    u32Tmp2 = CM_TMR6_2->STFLR & (BIT_MASK_11 | BIT_MASK_12);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL131 & BIT_MASK_28))) {
        TMR6_2_SCmpB_IrqHandler();
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.132 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ132_Handler(void)
{
    const uint32_t VSSEL132 = CM_INTC->VSSEL132;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;
    /* Timer6 Unit.3 A compare match */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMAF) && (0UL != (VSSEL132 & BIT_MASK_00))) {
            TMR6_3_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.3 B compare match */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMBF) && (0UL != (VSSEL132 & BIT_MASK_01))) {
            TMR6_3_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.3 C compare match */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMCF) && (0UL != (VSSEL132 & BIT_MASK_02))) {
            TMR6_3_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.3 D compare match */
    if (1UL == bCM_TMR6_3->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMDF) && (0UL != (VSSEL132 & BIT_MASK_03))) {
            TMR6_3_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.3 E compare match */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMEF) && (0UL != (VSSEL132 & BIT_MASK_04))) {
            TMR6_3_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.3 F compare match */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMFF) && (0UL != (VSSEL132 & BIT_MASK_05))) {
            TMR6_3_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.3 overflow */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_3->STFLR_b.OVFF) && (0UL != (VSSEL132 & BIT_MASK_06))) {
            TMR6_3_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.3 underflow */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_3->STFLR_b.UDFF) && (0UL != (VSSEL132 & BIT_MASK_07))) {
            TMR6_3_GUdf_IrqHandler();
        }
    }
    /* Timer6 Unit.3 dead time */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_3->STFLR_b.DTEF) && (0UL != (VSSEL132 & BIT_MASK_08))) {
            TMR6_3_GDte_IrqHandler();
        }
    }
    /* Timer6 Unit.3 A up-down compare match */
    u32Tmp1 = (CM_TMR6_3->ICONR & (BIT_MASK_16 | BIT_MASK_17)) >> 7U;
    u32Tmp2 = CM_TMR6_3->STFLR & (BIT_MASK_09 | BIT_MASK_10);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (0UL != (VSSEL132 & BIT_MASK_11)))) {
        TMR6_3_SCmpA_IrqHandler();
    }
    /* Timer6 Unit.3 B up-down compare match */
    u32Tmp1 = (CM_TMR6_3->ICONR & (BIT_MASK_18 | BIT_MASK_19)) >> 7U;
    u32Tmp2 = CM_TMR6_3->STFLR & (BIT_MASK_11 | BIT_MASK_12);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (0UL != (VSSEL132 & BIT_MASK_12)))) {
        TMR6_3_SCmpB_IrqHandler();
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.136 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ136_Handler(void)
{
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;
    const uint32_t VSSEL136 = CM_INTC->VSSEL136;

    /* TimerA Unit.1 overflow */
    if (1UL == bCM_TMRA_1->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_1->BCSTRH_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_00))) {
            TMRA_1_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.1 underflow */
    if (1UL == bCM_TMRA_1->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_1->BCSTRH_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_01))) {
            TMRA_1_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_1->ICONR;
    u32Tmp2 = CM_TMRA_1->STFLR;
    /* TimerA Unit.1 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0xFFUL)) && (0UL != (VSSEL136 & BIT_MASK_02))) {
        TMRA_1_Cmp_IrqHandler();
    }

    /* TimerA Unit.2 overflow */
    if (1UL == bCM_TMRA_2->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_2->BCSTRH_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_03))) {
            TMRA_2_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.2 underflow */
    if (1UL == bCM_TMRA_2->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_2->BCSTRH_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_04))) {
            TMRA_2_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_2->ICONR;
    u32Tmp2 = CM_TMRA_2->STFLR;
    /* TimerA Unit.2 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0xFFUL)) && (0UL != (VSSEL136 & BIT_MASK_05))) {
        TMRA_2_Cmp_IrqHandler();
    }

    /* TimerA Unit.3 overflow */
    if (1UL == bCM_TMRA_3->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_3->BCSTRH_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_06))) {
            TMRA_3_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.3 underflow */
    if (1UL == bCM_TMRA_3->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_3->BCSTRH_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_07))) {
            TMRA_3_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_3->ICONR;
    u32Tmp2 = CM_TMRA_3->STFLR;
    /* TimerA Unit.3 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0xFFUL)) && (0UL != (VSSEL136 & BIT_MASK_08))) {
        TMRA_3_Cmp_IrqHandler();
    }

    /* TimerA Unit.4 overflow */
    if (1UL == bCM_TMRA_4->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_4->BCSTRH_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_09))) {
            TMRA_4_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.4 underflow */
    if (1UL == bCM_TMRA_4->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_4->BCSTRH_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_10))) {
            TMRA_4_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_4->ICONR;
    u32Tmp2 = CM_TMRA_4->STFLR;
    /* TimerA Unit.4 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0xFFUL)) && (0UL != (VSSEL136 & BIT_MASK_11))) {
        TMRA_4_Cmp_IrqHandler();
    }

    /* TimerA Unit.5 overflow */
    if (1UL == bCM_TMRA_5->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_5->BCSTRH_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_12))) {
            TMRA_5_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.5 underflow */
    if (1UL == bCM_TMRA_5->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_5->BCSTRH_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_13))) {
            TMRA_5_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_5->ICONR;
    u32Tmp2 = CM_TMRA_5->STFLR;
    /* TimerA Unit.5 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0xFFUL)) && (0UL != (VSSEL136 & BIT_MASK_14))) {
        TMRA_5_Cmp_IrqHandler();
    }

    /* TimerA Unit.6 overflow */
    if (1UL == bCM_TMRA_6->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_6->BCSTRH_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_16))) {
            TMRA_6_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.6 underflow */
    if (1UL == bCM_TMRA_6->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_6->BCSTRH_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_17))) {
            TMRA_6_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_6->ICONR;
    u32Tmp2 = CM_TMRA_6->STFLR;
    /* TimerA Unit.6 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0xFFUL)) && (0UL != (VSSEL136 & BIT_MASK_18))) {
        TMRA_6_Cmp_IrqHandler();
    }

    /* USBFS global interrupt */
    if (1UL == bCM_USBFS->GAHBCFG_b.GINTMSK) {
        u32Tmp1 = CM_USBFS->GINTMSK & 0xF77CFCFBUL;
        u32Tmp2 = CM_USBFS->GINTSTS & 0xF77CFCFBUL;
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL136 & BIT_MASK_19))) {
            USBFS_Global_IrqHandler();
        }
    }

    u32Tmp1 = CM_USART1->SR;
    u32Tmp2 = CM_USART1->CR1;
    /* USART Ch.1 Receive error */
    if ((0UL != (u32Tmp2 & BIT_MASK_05)) && (0UL != (u32Tmp1 & (BIT_MASK_00 | BIT_MASK_01 | BIT_MASK_03))) &&   \
        (0UL != (VSSEL136 & BIT_MASK_22))) {
        USART1_RxError_IrqHandler();
    }
    /* USART Ch.1 Receive completed */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_05)) && (0UL != (BIT_MASK_23 & VSSEL136))) {
        USART1_RxFull_IrqHandler();
    }
    /* USART Ch.1 Transmit data empty */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_07)) && (0UL != (BIT_MASK_24 & VSSEL136))) {
        USART1_TxEmpty_IrqHandler();
    }
    /* USART Ch.1 Transmit completed */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_06)) && (0UL != (BIT_MASK_25 & VSSEL136))) {
        USART1_TxComplete_IrqHandler();
    }
    /* USART Ch.1 Receive timeout */
    if ((0UL != (u32Tmp2 & BIT_MASK_01)) && (0UL != (u32Tmp1 & BIT_MASK_08)) && (0UL != (VSSEL136 & BIT_MASK_26))) {
        USART1_RxTO_IrqHandler();
    }

    u32Tmp1 = CM_USART2->SR;
    u32Tmp2 = CM_USART2->CR1;
    /* USART Ch.2 Receive error */
    if ((0UL != (u32Tmp2 & BIT_MASK_05)) && (0UL != (u32Tmp1 & (BIT_MASK_00 | BIT_MASK_01 | BIT_MASK_03))) &&   \
        (0UL != (VSSEL136 & BIT_MASK_27))) {
        USART2_RxError_IrqHandler();
    }
    /* USART Ch.2 Receive completed */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_05)) && (0UL != (BIT_MASK_28 & VSSEL136))) {
        USART2_RxFull_IrqHandler();
    }
    /* USART Ch.2 Transmit data empty */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_07)) && (0UL != (BIT_MASK_29 & VSSEL136))) {
        USART2_TxEmpty_IrqHandler();
    }
    /* USART Ch.2 Transmit completed */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_06)) && (0UL != (BIT_MASK_30 & VSSEL136))) {
        USART2_TxComplete_IrqHandler();
    }
    /* USART Ch.2 Receive timeout */
    if ((0UL != (u32Tmp2 & BIT_MASK_01)) && (0UL != (u32Tmp1 & BIT_MASK_08)) && (0UL != (VSSEL136 & BIT_MASK_31))) {
        USART2_RxTO_IrqHandler();
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.137 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ137_Handler(void)
{
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;
    const uint32_t VSSEL137 = CM_INTC->VSSEL137;

    u32Tmp1 = CM_USART3->SR;
    u32Tmp2 = CM_USART3->CR1;
    /* USART Ch.3 Receive error */
    if ((0UL != (u32Tmp2 & BIT_MASK_05)) && (0UL != (u32Tmp1 & (BIT_MASK_00 | BIT_MASK_01 | BIT_MASK_03))) &&   \
        (0UL != (VSSEL137 & BIT_MASK_00))) {
        USART3_RxError_IrqHandler();
    }
    /* USART Ch.3 Receive completed */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_05)) && (0UL != (BIT_MASK_01 & VSSEL137))) {
        USART3_RxFull_IrqHandler();
    }
    /* USART Ch.3 Transmit data empty */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_07)) && (0UL != (BIT_MASK_02 & VSSEL137))) {
        USART3_TxEmpty_IrqHandler();
    }
    /* USART Ch.3 Transmit completed */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_06)) && (0UL != (BIT_MASK_03 & VSSEL137))) {
        USART3_TxComplete_IrqHandler();
    }
    /* USART Ch.3 Receive timeout */
    if ((0UL != (u32Tmp2 & BIT_MASK_01)) && (0UL != (u32Tmp1 & BIT_MASK_08)) && (0UL != (VSSEL137 & BIT_MASK_04))) {
        USART3_RxTO_IrqHandler();
    }

    u32Tmp1 = CM_USART4->SR;
    u32Tmp2 = CM_USART4->CR1;
    /* USART Ch.4 Receive error */
    if ((0UL != (u32Tmp2 & BIT_MASK_05)) && (0UL != (u32Tmp1 & (BIT_MASK_00 | BIT_MASK_01 | BIT_MASK_03))) &&   \
        (0UL != (VSSEL137 & BIT_MASK_05))) {
        USART4_RxError_IrqHandler();
    }
    /* USART Ch.4 Receive completed */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_05)) && (0UL != (BIT_MASK_06 & VSSEL137))) {
        USART4_RxFull_IrqHandler();
    }
    /* USART Ch.4 Transmit data empty */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_07)) && (0UL != (BIT_MASK_07 & VSSEL137))) {
        USART4_TxEmpty_IrqHandler();
    }
    /* USART Ch.4 Transmit completed */
    if ((0UL != (u32Tmp2 & u32Tmp1 & BIT_MASK_06)) && (0UL != (BIT_MASK_08 & VSSEL137))) {
        USART4_TxComplete_IrqHandler();
    }
    /* USART Ch.4 Receive timeout */
    if ((0UL != (u32Tmp2 & BIT_MASK_01)) && (0UL != (u32Tmp1 & BIT_MASK_08)) && (0UL != (VSSEL137 & BIT_MASK_09))) {
        USART4_RxTO_IrqHandler();
    }

    u32Tmp1 = CM_SPI1->CR1;
    u32Tmp2 = CM_SPI1->SR;
    /* SPI Ch.1 Receive completed */
    if ((0UL != (u32Tmp1 & BIT_MASK_10)) && (0UL != (u32Tmp2 & BIT_MASK_07)) && (0UL != (VSSEL137 & BIT_MASK_11))) {
        SPI1_RxFull_IrqHandler();
    }
    /* SPI Ch.1 Transmit buf empty */
    if ((0UL != (u32Tmp1 & BIT_MASK_09)) && (0UL != (u32Tmp2 & BIT_MASK_05)) && (0UL != (VSSEL137 & BIT_MASK_12))) {
        SPI1_TxEmpty_IrqHandler();
    }
    /* SPI Ch.1 bus idle */
    if ((0UL != (u32Tmp1 & BIT_MASK_11)) && (0UL == (u32Tmp2 & BIT_MASK_01)) && (0UL != (VSSEL137 & BIT_MASK_13))) {
        SPI1_Idle_IrqHandler();
    }
    /* SPI Ch.1 parity/overflow/underflow/mode error */
    if ((0UL != (u32Tmp1 & BIT_MASK_08))                                                 &&  \
        (0UL != ((u32Tmp2 & (BIT_MASK_00 | BIT_MASK_02 | BIT_MASK_03 | BIT_MASK_04))))   &&  \
        (0UL != (VSSEL137 & BIT_MASK_14))) {
        SPI1_Error_IrqHandler();
    }

    u32Tmp1 = CM_SPI2->CR1;
    u32Tmp2 = CM_SPI2->SR;
    /* SPI Ch.2 Receive completed */
    if ((0UL != (u32Tmp1 & BIT_MASK_10)) && (0UL != (u32Tmp2 & BIT_MASK_07)) && (0UL != (VSSEL137 & BIT_MASK_16))) {
        SPI2_RxFull_IrqHandler();
    }
    /* SPI Ch.2 Transmit buf empty */
    if ((0UL != (u32Tmp1 & BIT_MASK_09)) && (0UL != (u32Tmp2 & BIT_MASK_05)) && (0UL != (VSSEL137 & BIT_MASK_17))) {
        SPI2_TxEmpty_IrqHandler();
    }
    /* SPI Ch.2 bus idle */
    if ((0UL != (u32Tmp1 & BIT_MASK_11)) && (0UL == (u32Tmp2 & BIT_MASK_01)) && (0UL != (VSSEL137 & BIT_MASK_18))) {
        SPI2_Idle_IrqHandler();
    }
    /* SPI Ch.2 parity/overflow/underflow/mode error */
    if ((0UL != (u32Tmp1 & BIT_MASK_08))                                                 &&  \
        (0UL != ((u32Tmp2 & (BIT_MASK_00 | BIT_MASK_02 | BIT_MASK_03 | BIT_MASK_04))))   &&  \
        (0UL != (VSSEL137 & BIT_MASK_19))) {
        SPI2_Error_IrqHandler();
    }

    u32Tmp1 = CM_SPI3->CR1;
    u32Tmp2 = CM_SPI3->SR;
    /* SPI Ch.3 Receive completed */
    if ((0UL != (u32Tmp1 & BIT_MASK_10)) && (0UL != (u32Tmp2 & BIT_MASK_07)) && (0UL != (VSSEL137 & BIT_MASK_21))) {
        SPI3_RxFull_IrqHandler();
    }
    /* SPI Ch.3 Transmit buf empty */
    if ((0UL != (u32Tmp1 & BIT_MASK_09)) && (0UL != (u32Tmp2 & BIT_MASK_05)) && (0UL != (VSSEL137 & BIT_MASK_22))) {
        SPI3_TxEmpty_IrqHandler();
    }
    /* SPI Ch.3 bus idle */
    if ((0UL != (u32Tmp1 & BIT_MASK_11)) && (0UL == (u32Tmp2 & BIT_MASK_01)) && (0UL != (VSSEL137 & BIT_MASK_23))) {
        SPI3_Idle_IrqHandler();
    }
    /* SPI Ch.3 parity/overflow/underflow/mode error */
    if ((0UL != (u32Tmp1 & BIT_MASK_08))                                                 &&  \
        (0UL != ((u32Tmp2 & (BIT_MASK_00 | BIT_MASK_02 | BIT_MASK_03 | BIT_MASK_04))))   &&  \
        (0UL != (VSSEL137 & BIT_MASK_24))) {
        SPI3_Error_IrqHandler();
    }

    u32Tmp1 = CM_SPI4->CR1;
    u32Tmp2 = CM_SPI4->SR;
    /* SPI Ch.4 Receive completed */
    if ((0UL != (u32Tmp1 & BIT_MASK_10)) && (0UL != (u32Tmp2 & BIT_MASK_07)) && (0UL != (VSSEL137 & BIT_MASK_26))) {
        SPI4_RxFull_IrqHandler();
    }
    /* SPI Ch.4 Transmit buf empty */
    if ((0UL != (u32Tmp1 & BIT_MASK_09)) && (0UL != (u32Tmp2 & BIT_MASK_05)) && (0UL != (VSSEL137 & BIT_MASK_27))) {
        SPI4_TxEmpty_IrqHandler();
    }
    /* SPI Ch.4 bus idle */
    if ((0UL != (u32Tmp1 & BIT_MASK_11)) && (0UL == (u32Tmp2 & BIT_MASK_01)) && (0UL != (VSSEL137 & BIT_MASK_28))) {
        SPI4_Idle_IrqHandler();
    }
    /* SPI Ch.4 parity/overflow/underflow/mode error */
    if ((0UL != (u32Tmp1 & BIT_MASK_08))                                                 &&  \
        (0UL != ((u32Tmp2 & (BIT_MASK_00 | BIT_MASK_02 | BIT_MASK_03 | BIT_MASK_04))))   &&  \
        (0UL != (VSSEL137 & BIT_MASK_29))) {
        SPI4_Error_IrqHandler();
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.138 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ138_Handler(void)
{
    const uint32_t VSSEL138 = CM_INTC->VSSEL138;
    uint32_t u32Tmp1;

    u32Tmp1 = CM_TMR4_1->OCSRU;
    /* Timer4 Unit.1 U phase higher compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_00)) && (0UL != (u32Tmp1 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_06))) {
        TMR4_1_GCmpUH_IrqHandler();
    }
    /* Timer4 Unit.1 U phase lower compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_01)) && (0UL != (u32Tmp1 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_07))) {
        TMR4_1_GCmpUL_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_1->OCSRV;
    /* Timer4 Unit.1 V phase higher compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_02)) && (0UL != (u32Tmp1 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_06))) {
        TMR4_1_GCmpVH_IrqHandler();
    }
    /* Timer4 Unit.1 V phase lower compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_03)) && (0UL != (u32Tmp1 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_07))) {
        TMR4_1_GCmpVL_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_1->OCSRW;
    /* Timer4 Unit.1 W phase higher compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_06))) {
        TMR4_1_GCmpWH_IrqHandler();
    }
    /* Timer4 Unit.1 W phase lower compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_07))) {
        TMR4_1_GCmpWL_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_1->CCSR;
    /* Timer4 Unit.1 overflow */
    if ((0UL != (VSSEL138 & BIT_MASK_06)) && (0UL != (u32Tmp1 & BIT_MASK_08)) && (0UL != (u32Tmp1 & BIT_MASK_09))) {
        TMR4_1_GOvf_IrqHandler();
    }
    /* Timer4 Unit.1 underflow */
    if ((0UL != (VSSEL138 & BIT_MASK_07)) && (0UL != (u32Tmp1 & BIT_MASK_13)) && (0UL != (u32Tmp1 & BIT_MASK_14))) {
        TMR4_1_GUdf_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_1->RCSR;
    /* Timer4 Unit.1 U phase reload */
    if ((0UL != (VSSEL138 & BIT_MASK_08)) && (0UL == (u32Tmp1 & BIT_MASK_00)) && (0UL != (u32Tmp1 & BIT_MASK_04))) {
        TMR4_1_ReloadU_IrqHandler();
    }
    /* Timer4 Unit.1 V phase reload */
    if ((0UL != (VSSEL138 & BIT_MASK_09)) && (0UL == (u32Tmp1 & BIT_MASK_01)) && (0UL != (u32Tmp1 & BIT_MASK_08))) {
        TMR4_1_ReloadV_IrqHandler();
    }
    /* Timer4 Unit.1 W phase reload */
    if ((0UL != (VSSEL138 & BIT_MASK_10)) && (0UL == (u32Tmp1 & BIT_MASK_02)) && (0UL != (u32Tmp1 & BIT_MASK_12))) {
        TMR4_1_ReloadW_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_2->OCSRU;
    /* Timer4 Unit.2 U phase higher compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_16)) && (0UL != (u32Tmp1 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_06))) {
        TMR4_1_GCmpUH_IrqHandler();
    }
    /* Timer4 Unit.2 U phase lower compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_17)) && (0UL != (u32Tmp1 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_07))) {
        TMR4_1_GCmpUL_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_2->OCSRV;
    /* Timer4 Unit.2 V phase higher compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_18)) && (0UL != (u32Tmp1 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_06))) {
        TMR4_2_GCmpVH_IrqHandler();
    }
    /* Timer4 Unit.2 V phase lower compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_19)) && (0UL != (u32Tmp1 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_07))) {
        TMR4_2_GCmpVL_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_2->OCSRW;
    /* Timer4 Unit.2 W phase higher compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_20)) && (0UL != (u32Tmp1 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_06))) {
        TMR4_2_GCmpWH_IrqHandler();
    }
    /* Timer4 Unit.2 W phase lower compare match */
    if ((0UL != (VSSEL138 & BIT_MASK_21)) && (0UL != (u32Tmp1 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_07))) {
        TMR4_2_GCmpWL_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_2->CCSR;
    /* Timer4 Unit.2 overflow */
    if ((0UL != (VSSEL138 & BIT_MASK_22)) && (0UL != (u32Tmp1 & BIT_MASK_08)) && (0UL != (u32Tmp1 & BIT_MASK_09))) {
        TMR4_2_GOvf_IrqHandler();
    }
    /* Timer4 Unit.2 underflow */
    if ((0UL != (VSSEL138 & BIT_MASK_23)) && (0UL != (u32Tmp1 & BIT_MASK_13)) && (0UL != (u32Tmp1 & BIT_MASK_14))) {
        TMR4_2_GUdf_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_2->RCSR;
    /* Timer4 Unit.2 U phase reload */
    if ((0UL != (VSSEL138 & BIT_MASK_24)) && (0UL == (u32Tmp1 & BIT_MASK_00)) && (0UL != (u32Tmp1 & BIT_MASK_04))) {
        TMR4_2_ReloadU_IrqHandler();
    }
    /* Timer4 Unit.2 V phase reload */
    if ((0UL != (VSSEL138 & BIT_MASK_25)) && (0UL == (u32Tmp1 & BIT_MASK_01)) && (0UL != (u32Tmp1 & BIT_MASK_08))) {
        TMR4_2_ReloadV_IrqHandler();
    }
    /* Timer4 Unit.2 W phase reload */
    if ((0UL != (VSSEL138 & BIT_MASK_26)) && (0UL == (u32Tmp1 & BIT_MASK_02)) && (0UL != (u32Tmp1 & BIT_MASK_12))) {
        TMR4_2_ReloadW_IrqHandler();
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.139 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ139_Handler(void)
{
    uint32_t u32Tmp1;
    const uint32_t VSSEL139 = CM_INTC->VSSEL139;

    u32Tmp1 = CM_TMR4_3->OCSRU;
    /* Timer4 Unit.3 U phase higher compare match */
    if ((0UL != (VSSEL139 & BIT_MASK_00)) && (0UL != (u32Tmp1 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_06))) {
        TMR4_3_GCmpUH_IrqHandler();
    }
    /* Timer4 Unit.3 U phase lower compare match */
    if ((0UL != (VSSEL139 & BIT_MASK_01)) && (0UL != (u32Tmp1 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_07))) {
        TMR4_3_GCmpUL_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_3->OCSRV;
    /* Timer4 Unit.3 V phase higher compare match */
    if ((0UL != (VSSEL139 & BIT_MASK_02)) && (0UL != (u32Tmp1 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_06))) {
        TMR4_3_GCmpVH_IrqHandler();
    }
    /* Timer4 Unit.3 V phase lower compare match */
    if ((0UL != (VSSEL139 & BIT_MASK_03)) && (0UL != (u32Tmp1 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_07))) {
        TMR4_3_GCmpVL_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_3->OCSRW;
    /* Timer4 Unit.3 W phase higher compare match */
    if ((0UL != (VSSEL139 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_04)) && (0UL != (u32Tmp1 & BIT_MASK_06))) {
        TMR4_3_GCmpWH_IrqHandler();
    }
    /* Timer4 Unit.3 W phase lower compare match */
    if ((0UL != (VSSEL139 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_05)) && (0UL != (u32Tmp1 & BIT_MASK_07))) {
        TMR4_3_GCmpWL_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_3->CCSR;
    /* Timer4 Unit.3 overflow */
    if ((0UL != (VSSEL139 & BIT_MASK_06)) && (0UL != (u32Tmp1 & BIT_MASK_08)) && (0UL != (u32Tmp1 & BIT_MASK_09))) {
        TMR4_3_GOvf_IrqHandler();
    }
    /* Timer4 Unit.3 underflow */
    if ((0UL != (VSSEL139 & BIT_MASK_07)) && (0UL != (u32Tmp1 & BIT_MASK_13)) && (0UL != (u32Tmp1 & BIT_MASK_14))) {
        TMR4_3_GUdf_IrqHandler();
    }

    u32Tmp1 = CM_TMR4_3->RCSR;
    /* Timer4 Unit.3 U phase reload */
    if ((0UL != (VSSEL139 & BIT_MASK_08)) && (0UL == (u32Tmp1 & BIT_MASK_00)) && (0UL != (u32Tmp1 & BIT_MASK_04))) {
        TMR4_1_ReloadU_IrqHandler();
    }
    /* Timer4 Unit.3 V phase reload */
    if ((0UL != (VSSEL139 & BIT_MASK_09)) && (0UL == (u32Tmp1 & BIT_MASK_01)) && (0UL != (u32Tmp1 & BIT_MASK_08))) {
        TMR4_3_ReloadV_IrqHandler();
    }
    /* Timer4 Unit.3 W phase reload */
    if ((0UL != (VSSEL139 & BIT_MASK_10)) && (0UL == (u32Tmp1 & BIT_MASK_02)) && (0UL != (u32Tmp1 & BIT_MASK_12))) {
        TMR4_3_ReloadW_IrqHandler();
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.140 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ140_Handler(void)
{
    const uint32_t VSSEL140 = CM_INTC->VSSEL140;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;
    /* EMB0 */
    u32Tmp1 = CM_EMB0->STAT & 0x0000000FUL;
    u32Tmp2 = CM_EMB0->INTEN & 0x0000000FUL;
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL140 & BIT_MASK_06))) {
        EMB_GR0_IrqHandler();
    }
    /* EMB1 */
    u32Tmp1 = CM_EMB1->STAT & 0x0000000FUL;
    u32Tmp2 = CM_EMB1->INTEN & 0x0000000FUL;
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL140 & BIT_MASK_07))) {
        EMB_GR1_IrqHandler();
    }
    /* EMB2 */
    u32Tmp1 = CM_EMB2->STAT & 0x0000000FUL;
    u32Tmp2 = CM_EMB2->INTEN & 0x0000000FUL;
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL140 & BIT_MASK_08))) {
        EMB_GR2_IrqHandler();
    }
    /* EMB3 */
    u32Tmp1 = CM_EMB3->STAT & 0x0000000FUL;
    u32Tmp2 = CM_EMB3->INTEN & 0x0000000FUL;
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL140 & BIT_MASK_09))) {
        EMB_GR3_IrqHandler();
    }

    /* I2S Ch.1 Transmit */
    if (1UL == bCM_I2S1->CTRL_b.TXIE) {
        if ((1UL == bCM_I2S1->SR_b.TXBA) && (0UL != (VSSEL140 & BIT_MASK_16))) {
            I2S1_Tx_IrqHandler();
        }
    }
    /* I2S Ch.1 Receive */
    if (1UL == bCM_I2S1->CTRL_b.RXIE) {
        if ((1UL == bCM_I2S1->SR_b.RXBA) && (0UL != (VSSEL140 & BIT_MASK_17))) {
            I2S1_Rx_IrqHandler();
        }
    }
    /* I2S Ch.1 Error */
    if (1UL == bCM_I2S1->CTRL_b.EIE) {
        if (0UL != ((CM_I2S1->ER & (BIT_MASK_00 | BIT_MASK_01))) && (0UL != (VSSEL140 & BIT_MASK_18))) {
            I2S1_Error_IrqHandler();
        }
    }
    /* I2S Ch.2 Transmit */
    if (1UL == bCM_I2S2->CTRL_b.TXIE) {
        if ((1UL == bCM_I2S2->SR_b.TXBA) && (0UL != (VSSEL140 & BIT_MASK_19))) {
            I2S2_Tx_IrqHandler();
        }
    }
    /* I2S Ch.2 Receive */
    if (1UL == bCM_I2S2->CTRL_b.RXIE) {
        if ((1UL == bCM_I2S2->SR_b.RXBA) && (0UL != (VSSEL140 & BIT_MASK_20))) {
            I2S2_Rx_IrqHandler();
        }
    }
    /* I2S Ch.2 Error */
    if (1UL == bCM_I2S2->CTRL_b.EIE) {
        if (0UL != ((CM_I2S2->ER & (BIT_MASK_00 | BIT_MASK_01))) && (0UL != (VSSEL140 & BIT_MASK_21))) {
            I2S2_Error_IrqHandler();
        }
    }
    /* I2S Ch.3 Transmit */
    if (1UL == bCM_I2S3->CTRL_b.TXIE) {
        if ((1UL == bCM_I2S3->SR_b.TXBA) && (0UL != (VSSEL140 & BIT_MASK_22))) {
            I2S3_Tx_IrqHandler();
        }
    }
    /* I2S Ch.3 Receive */
    if (1UL == bCM_I2S3->CTRL_b.RXIE) {
        if ((1UL == bCM_I2S3->SR_b.RXBA) && (0UL != (VSSEL140 & BIT_MASK_23))) {
            I2S3_Rx_IrqHandler();
        }
    }
    /* I2S Ch.3 Error */
    if (1UL == bCM_I2S3->CTRL_b.EIE) {
        if (0UL != ((CM_I2S3->ER & (BIT_MASK_00 | BIT_MASK_01))) && (0UL != (VSSEL140 & BIT_MASK_24))) {
            I2S3_Error_IrqHandler();
        }
    }
    /* I2S Ch.4 Transmit */
    if (1UL == bCM_I2S4->CTRL_b.TXIE) {
        if ((1UL == bCM_I2S4->SR_b.TXBA) && (0UL != (VSSEL140 & BIT_MASK_25))) {
            I2S4_Tx_IrqHandler();
        }
    }
    /* I2S Ch.4 Receive */
    if (1UL == bCM_I2S4->CTRL_b.RXIE) {
        if ((1UL == bCM_I2S4->SR_b.RXBA) && (0UL != (VSSEL140 & BIT_MASK_26))) {
            I2S4_Rx_IrqHandler();
        }
    }
    /* I2S Ch.4 Error */
    if (1UL == bCM_I2S4->CTRL_b.EIE) {
        if (0UL != ((CM_I2S4->ER & (BIT_MASK_00 | BIT_MASK_01))) && (0UL != (VSSEL140 & BIT_MASK_27))) {
            I2S4_Error_IrqHandler();
        }
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.141 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ141_Handler(void)
{
    uint32_t  VSSEL141 = CM_INTC->VSSEL141;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;
    /* I2C Ch.1 Receive completed */
    if (1UL == bCM_I2C1->CR2_b.RFULLIE) {
        if ((1UL == bCM_I2C1->SR_b.RFULLF) && (0UL != (VSSEL141 & BIT_MASK_04))) {
            I2C1_RxFull_IrqHandler();
        }
    }
    /* I2C Ch.1 Transmit data empty */
    if (1UL == bCM_I2C1->CR2_b.TEMPTYIE) {
        if ((1UL == bCM_I2C1->SR_b.TEMPTYF) && (0UL != (VSSEL141 & BIT_MASK_05))) {
            I2C1_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.1 Transmit completed */
    if (1UL == bCM_I2C1->CR2_b.TENDIE) {
        if ((1UL == bCM_I2C1->SR_b.TENDF) && (0UL != (VSSEL141 & BIT_MASK_06))) {
            I2C1_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.1 Error */
    u32Tmp1 = CM_I2C1->CR2 & 0x00F05217UL;
    u32Tmp2 = CM_I2C1->SR & 0x00F05217UL;
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL141 & BIT_MASK_07))) {
        I2C1_EE_IrqHandler();
    }
    /* I2C Ch.2 Receive completed */
    if (1UL == bCM_I2C2->CR2_b.RFULLIE) {
        if ((1UL == bCM_I2C2->SR_b.RFULLF) && (0UL != (VSSEL141 & BIT_MASK_08))) {
            I2C2_RxFull_IrqHandler();
        }
    }
    /* I2C Ch.2 Transmit data empty */
    if (1UL == bCM_I2C2->CR2_b.TEMPTYIE) {
        if ((1UL == bCM_I2C2->SR_b.TEMPTYF) && (0UL != (VSSEL141 & BIT_MASK_09))) {
            I2C2_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.2 Transmit completed */
    if (1UL == bCM_I2C2->CR2_b.TENDIE) {
        if ((1UL == bCM_I2C2->SR_b.TENDF)  && (0UL != (VSSEL141 & BIT_MASK_10))) {
            I2C2_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.2 Error */
    u32Tmp1 = CM_I2C2->CR2 & 0x00F05217UL;
    u32Tmp2 = CM_I2C2->SR & 0x00F05217UL;
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL141 & BIT_MASK_11))) {
        I2C2_EE_IrqHandler();
    }
    /* I2C Ch.3 Receive completed */
    if (1UL == bCM_I2C3->CR2_b.RFULLIE) {
        if ((1UL == bCM_I2C3->SR_b.RFULLF) && (0UL != (VSSEL141 & BIT_MASK_12))) {
            I2C3_RxFull_IrqHandler();
        }
    }
    /* I2C Ch.3 Transmit data empty */
    if (1UL == bCM_I2C3->CR2_b.TEMPTYIE) {
        if ((1UL == bCM_I2C3->SR_b.TEMPTYF) && (0UL != (VSSEL141 & BIT_MASK_13))) {
            I2C3_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.3 Transmit completed */
    if (1UL == bCM_I2C3->CR2_b.TENDIE) {
        if ((1UL == bCM_I2C3->SR_b.TENDF)  && (0UL != (VSSEL141 & BIT_MASK_14))) {
            I2C3_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.3 Error */
    u32Tmp1 = CM_I2C3->CR2 & 0x00F05217UL;
    u32Tmp2 = CM_I2C3->SR & 0x00F05217UL;
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL141 & BIT_MASK_15))) {
        I2C3_EE_IrqHandler();
    }
    /* LVD Ch.1 detected */
    if (PWC_PVDCR1_PVD1IRE == READ_REG8_BIT(CM_PWC->PVDCR1, PWC_PVDCR1_PVD1IRE | PWC_PVDCR1_PVD1IRS)) {
        if ((PWC_PVDDSR_PVD1DETFLG == READ_REG8_BIT(CM_PWC->PVDDSR, PWC_PVDDSR_PVD1DETFLG)) && \
            (0UL != (VSSEL141 & BIT_MASK_17))) {
            PWC_LVD1_IrqHandler();
        }
    }
    if (PWC_PVDCR1_PVD2IRE == READ_REG8_BIT(CM_PWC->PVDCR1, PWC_PVDCR1_PVD2IRE | PWC_PVDCR1_PVD2IRS)) {
        /* LVD Ch.2 detected */
        if ((PWC_PVDDSR_PVD2DETFLG == READ_REG8_BIT(CM_PWC->PVDDSR, PWC_PVDDSR_PVD2DETFLG)) && \
            (0UL != (VSSEL141 & BIT_MASK_18))) {
            PWC_LVD2_IrqHandler();
        }
    }
    /* Freq. calculate error detected */
    if (1UL == bCM_FCM->RIER_b.ERRIE) {
        if ((1UL == bCM_FCM->SR_b.ERRF) && (0UL != (VSSEL141 & BIT_MASK_20))) {
            FCM_Error_IrqHandler();
        }
    }
    /* Freq. calculate completed */
    if (1UL == bCM_FCM->RIER_b.MENDIE) {
        if ((1UL == bCM_FCM->SR_b.MENDF) && (0UL != (VSSEL141 & BIT_MASK_21))) {
            FCM_End_IrqHandler();
        }
    }
    /* Freq. calculate overflow */
    if (1UL == bCM_FCM->RIER_b.OVFIE) {
        if ((1UL == bCM_FCM->SR_b.OVF) && (0UL != (VSSEL141 & BIT_MASK_22))) {
            FCM_Ovf_IrqHandler();
        }
    }

    /* WDT */
    if ((0UL != (CM_WDT->SR & (BIT_MASK_16 | BIT_MASK_17))) && (0UL != (VSSEL141 & BIT_MASK_23))) {
        WDT_IrqHandler();
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.142 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ142_Handler(void)
{
    uint32_t u32VSSEL142 = CM_INTC->VSSEL142;
    /* ADC unit.1 seq. A */
    if (1UL == bCM_ADC1->ICR_b.EOCAIEN) {
        if ((1UL == bCM_ADC1->ISR_b.EOCAF) && (0UL != (u32VSSEL142 & BIT_MASK_00))) {
            ADC1_SeqA_IrqHandler();
        }
    }
    /* ADC unit.1 seq. B */
    if (1UL == bCM_ADC1->ICR_b.EOCBIEN) {
        if ((1UL == bCM_ADC1->ISR_b.EOCBF) && (0UL != (u32VSSEL142 & BIT_MASK_01))) {
            ADC1_SeqB_IrqHandler();
        }
    }
    /* ADC unit.1 ADW channel compare */
    if (1UL == bCM_ADC1->AWDCR_b.AWDIEN) {
        if ((0UL != (CM_ADC1->AWDSR & 0x1FFFFU)) && (0UL != (u32VSSEL142 & BIT_MASK_02))) {
            ADC1_ChCmp_IrqHandler();
        }
    }
    /* ADC unit.1 AWD Seq. compare */
    if (1UL == bCM_ADC1->AWDCR_b.AWDIEN) {
        if ((0UL != (CM_ADC1->AWDSR & 0x1FFFFU)) && (0UL != (u32VSSEL142 & BIT_MASK_03))) {
            ADC1_SeqCmp_IrqHandler();
        }
    }

    /* ADC unit.2 seq. A */
    if (1UL == bCM_ADC2->ICR_b.EOCAIEN) {
        if ((1UL == bCM_ADC2->ISR_b.EOCAF) && (0UL != (u32VSSEL142 & BIT_MASK_04))) {
            ADC2_SeqA_IrqHandler();
        }
    }
    /* ADC unit.2 seq. B */
    if (1UL == bCM_ADC2->ICR_b.EOCBIEN) {
        if ((1UL == bCM_ADC2->ISR_b.EOCBF) && (0UL != (u32VSSEL142 & BIT_MASK_05))) {
            ADC2_SeqB_IrqHandler();
        }
    }
    /* ADC unit.2 ADW channel compare */
    if (1UL == bCM_ADC2->AWDCR_b.AWDIEN) {
        if ((0UL != (CM_ADC2->AWDSR & 0x1FFU)) && (0UL != (u32VSSEL142 & BIT_MASK_06))) {
            ADC2_ChCmp_IrqHandler();
        }
    }
    /* ADC unit.2 AWD Seq. compare */
    if (1UL == bCM_ADC2->AWDCR_b.AWDIEN) {
        if ((0UL != (CM_ADC2->AWDSR & 0x1FFU)) && (0UL != (u32VSSEL142 & BIT_MASK_07))) {
            ADC2_SeqCmp_IrqHandler();
        }
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.143 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ143_Handler(void)
{
    uint8_t RTIF;
    uint8_t RTIE;
    uint8_t ERRINT;
    uint8_t TTCFG;
    uint16_t NORINTST;
    uint16_t NORINTSGEN;
    uint16_t ERRINTST;
    uint16_t ERRINTSGEN;
    uint32_t u32VSSEL143 = CM_INTC->VSSEL143;

    /* SDIO Ch.1 */
    if (0UL != (u32VSSEL143 & BIT_MASK_02)) {
        NORINTST = CM_SDIOC1->NORINTST;
        NORINTSGEN = CM_SDIOC1->NORINTSGEN;
        ERRINTST = CM_SDIOC1->ERRINTST;
        ERRINTSGEN = CM_SDIOC1->ERRINTSGEN;

        if ((0U != (NORINTST & NORINTSGEN & 0x01F7U)) || (0U != (ERRINTST & ERRINTSGEN & 0x017FU))) {
            SDIOC1_IrqHandler();
        }
    }

    /* SDIO Ch.2 */
    if (0UL != (u32VSSEL143 & BIT_MASK_05)) {
        NORINTST = CM_SDIOC2->NORINTST;
        NORINTSGEN = CM_SDIOC2->NORINTSGEN;
        ERRINTST = CM_SDIOC2->ERRINTST;
        ERRINTSGEN = CM_SDIOC2->ERRINTSGEN;

        if ((0U != (NORINTST & NORINTSGEN & 0x01F7U)) || (0U != (ERRINTST & ERRINTSGEN & 0x017FU))) {
            SDIOC2_IrqHandler();
        }
    }

    /* CAN */
    if (0UL != (u32VSSEL143 & BIT_MASK_06)) {
        RTIF = CM_CAN->RTIF;
        RTIE = CM_CAN->RTIE;
        ERRINT = CM_CAN->ERRINT;
        TTCFG = CM_CAN->TTCFG;
        if (((0U != (TTCFG & BIT_MASK_05))                                             ||  \
             (0U != (RTIF & BIT_MASK_00))                                              ||  \
             (0U != (RTIF & RTIE & 0xFEU))                                             ||  \
             ((0U != (ERRINT & BIT_MASK_00)) && (0U != (ERRINT & BIT_MASK_01)))        ||  \
             ((0U != (ERRINT & BIT_MASK_02)) && (0U != (ERRINT & BIT_MASK_03)))        ||  \
             ((0U != (ERRINT & BIT_MASK_04)) && (0U != (ERRINT & BIT_MASK_05)))        ||  \
             ((0U != (TTCFG & BIT_MASK_03)) && (0U != (TTCFG  & BIT_MASK_04)))         ||  \
             ((0U != (TTCFG & BIT_MASK_06)) && (0U != (TTCFG & BIT_MASK_07)))) != 0U) {
            CAN_IrqHandler();
        }
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}
/**
 * @}
 */

/**
 * @defgroup Share_Interrupts_Weakdef_Prototypes Share Interrupts weak function prototypes
 * @{
 */
__WEAKDEF void EXTINT00_IrqHandler(void)
{
}
__WEAKDEF void EXTINT01_IrqHandler(void)
{
}
__WEAKDEF void EXTINT02_IrqHandler(void)
{
}
__WEAKDEF void EXTINT03_IrqHandler(void)
{
}
__WEAKDEF void EXTINT04_IrqHandler(void)
{
}
__WEAKDEF void EXTINT05_IrqHandler(void)
{
}
__WEAKDEF void EXTINT06_IrqHandler(void)
{
}
__WEAKDEF void EXTINT07_IrqHandler(void)
{
}
__WEAKDEF void EXTINT08_IrqHandler(void)
{
}
__WEAKDEF void EXTINT09_IrqHandler(void)
{
}
__WEAKDEF void EXTINT10_IrqHandler(void)
{
}
__WEAKDEF void EXTINT11_IrqHandler(void)
{
}
__WEAKDEF void EXTINT12_IrqHandler(void)
{
}
__WEAKDEF void EXTINT13_IrqHandler(void)
{
}
__WEAKDEF void EXTINT14_IrqHandler(void)
{
}
__WEAKDEF void EXTINT15_IrqHandler(void)
{
}
__WEAKDEF void DMA1_TC0_IrqHandler(void)
{
}
__WEAKDEF void DMA1_TC1_IrqHandler(void)
{
}
__WEAKDEF void DMA1_TC2_IrqHandler(void)
{
}
__WEAKDEF void DMA1_TC3_IrqHandler(void)
{
}
__WEAKDEF void DMA2_TC0_IrqHandler(void)
{
}
__WEAKDEF void DMA2_TC1_IrqHandler(void)
{
}
__WEAKDEF void DMA2_TC2_IrqHandler(void)
{
}
__WEAKDEF void DMA2_TC3_IrqHandler(void)
{
}
__WEAKDEF void DMA1_BTC0_IrqHandler(void)
{
}
__WEAKDEF void DMA1_BTC1_IrqHandler(void)
{
}
__WEAKDEF void DMA1_BTC2_IrqHandler(void)
{
}
__WEAKDEF void DMA1_BTC3_IrqHandler(void)
{
}
__WEAKDEF void DMA2_BTC0_IrqHandler(void)
{
}
__WEAKDEF void DMA2_BTC1_IrqHandler(void)
{
}
__WEAKDEF void DMA2_BTC2_IrqHandler(void)
{
}
__WEAKDEF void DMA2_BTC3_IrqHandler(void)
{
}
__WEAKDEF void DMA1_Error0_IrqHandler(void)
{
}
__WEAKDEF void DMA1_Error1_IrqHandler(void)
{
}
__WEAKDEF void DMA1_Error2_IrqHandler(void)
{
}
__WEAKDEF void DMA1_Error3_IrqHandler(void)
{
}
__WEAKDEF void DMA2_Error0_IrqHandler(void)
{
}
__WEAKDEF void DMA2_Error1_IrqHandler(void)
{
}
__WEAKDEF void DMA2_Error2_IrqHandler(void)
{
}
__WEAKDEF void DMA2_Error3_IrqHandler(void)
{
}
__WEAKDEF void EFM_ProgramEraseError_IrqHandler(void)
{
}
__WEAKDEF void EFM_ColError_IrqHandler(void)
{
}
__WEAKDEF void EFM_OpEnd_IrqHandler(void)
{
}
__WEAKDEF void QSPI_Error_IrqHandler(void)
{
}
__WEAKDEF void DCU1_IrqHandler(void)
{
}
__WEAKDEF void DCU2_IrqHandler(void)
{
}
__WEAKDEF void DCU3_IrqHandler(void)
{
}
__WEAKDEF void DCU4_IrqHandler(void)
{
}
__WEAKDEF void TMR0_1_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR0_1_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR0_2_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR0_2_CmpB_IrqHandler(void)
{
}
__WEAKDEF void CLK_XtalStop_IrqHandler(void)
{
}
__WEAKDEF void PWC_WakeupTimer_IrqHandler(void)
{
}
__WEAKDEF void SWDT_IrqHandler(void)
{
}
__WEAKDEF void WDT_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_GDte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_SCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_SCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_GDte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_SCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_SCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_GDte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_SCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_SCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_1_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_2_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_3_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_4_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_5_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_5_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_5_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_6_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_6_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_6_Cmp_IrqHandler(void)
{
}
__WEAKDEF void USBFS_Global_IrqHandler(void)
{
}
__WEAKDEF void USART1_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART1_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART1_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART1_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void USART1_RxTO_IrqHandler(void)
{
}
__WEAKDEF void USART2_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART2_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART2_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART2_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void USART2_RxTO_IrqHandler(void)
{
}
__WEAKDEF void USART3_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART3_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART3_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART3_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void USART3_RxTO_IrqHandler(void)
{
}
__WEAKDEF void USART4_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART4_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART4_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART4_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void USART4_RxTO_IrqHandler(void)
{
}
__WEAKDEF void SPI1_RxFull_IrqHandler(void)
{
}
__WEAKDEF void SPI1_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI1_Error_IrqHandler(void)
{
}
__WEAKDEF void SPI1_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI2_RxFull_IrqHandler(void)
{
}
__WEAKDEF void SPI2_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI2_Error_IrqHandler(void)
{
}
__WEAKDEF void SPI2_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI3_RxFull_IrqHandler(void)
{
}
__WEAKDEF void SPI3_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI3_Error_IrqHandler(void)
{
}
__WEAKDEF void SPI3_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI4_RxFull_IrqHandler(void)
{
}
__WEAKDEF void SPI4_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI4_Error_IrqHandler(void)
{
}
__WEAKDEF void SPI4_Idle_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpUH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpUL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpVH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpVL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpWH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GCmpWL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_ReloadU_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_ReloadV_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_ReloadW_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpUH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpUL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpVH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpVL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpWH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GCmpWL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_ReloadU_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_ReloadV_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_ReloadW_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpUH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpUL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpVH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpVL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpWH_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GCmpWL_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_ReloadU_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_ReloadV_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_ReloadW_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR0_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR1_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR2_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR3_IrqHandler(void)
{
}
__WEAKDEF void I2S1_Tx_IrqHandler(void)
{
}
__WEAKDEF void I2S1_Rx_IrqHandler(void)
{
}
__WEAKDEF void I2S1_Error_IrqHandler(void)
{
}
__WEAKDEF void I2S2_Tx_IrqHandler(void)
{
}
__WEAKDEF void I2S2_Rx_IrqHandler(void)
{
}
__WEAKDEF void I2S2_Error_IrqHandler(void)
{
}
__WEAKDEF void I2S3_Tx_IrqHandler(void)
{
}
__WEAKDEF void I2S3_Rx_IrqHandler(void)
{
}
__WEAKDEF void I2S3_Error_IrqHandler(void)
{
}
__WEAKDEF void I2S4_Tx_IrqHandler(void)
{
}
__WEAKDEF void I2S4_Rx_IrqHandler(void)
{
}
__WEAKDEF void I2S4_Error_IrqHandler(void)
{
}
__WEAKDEF void I2C1_RxFull_IrqHandler(void)
{
}
__WEAKDEF void I2C1_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void I2C1_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C1_EE_IrqHandler(void)
{
}
__WEAKDEF void I2C2_RxFull_IrqHandler(void)
{
}
__WEAKDEF void I2C2_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void I2C2_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C2_EE_IrqHandler(void)
{
}
__WEAKDEF void I2C3_RxFull_IrqHandler(void)
{
}
__WEAKDEF void I2C3_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void I2C3_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C3_EE_IrqHandler(void)
{
}
__WEAKDEF void PWC_LVD1_IrqHandler(void)
{
}
__WEAKDEF void PWC_LVD2_IrqHandler(void)
{
}
__WEAKDEF void FCM_Error_IrqHandler(void)
{
}
__WEAKDEF void FCM_End_IrqHandler(void)
{
}
__WEAKDEF void FCM_Ovf_IrqHandler(void)
{
}
__WEAKDEF void ADC1_SeqA_IrqHandler(void)
{
}
__WEAKDEF void ADC1_SeqB_IrqHandler(void)
{
}
__WEAKDEF void ADC1_ChCmp_IrqHandler(void)
{
}
__WEAKDEF void ADC1_SeqCmp_IrqHandler(void)
{
}
__WEAKDEF void ADC2_SeqA_IrqHandler(void)
{
}
__WEAKDEF void ADC2_SeqB_IrqHandler(void)
{
}
__WEAKDEF void ADC2_ChCmp_IrqHandler(void)
{
}
__WEAKDEF void ADC2_SeqCmp_IrqHandler(void)
{
}
__WEAKDEF void SDIOC1_IrqHandler(void)
{
}
__WEAKDEF void SDIOC2_IrqHandler(void)
{
}
__WEAKDEF void CAN_IrqHandler(void)
{
}
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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
