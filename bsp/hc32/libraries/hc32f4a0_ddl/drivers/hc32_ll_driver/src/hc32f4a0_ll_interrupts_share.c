/**
 *******************************************************************************
 * @file  hc32f4a0_ll_interrupts_share.c
 * @brief This file provides firmware functions to manage the Share Interrupt
 *        Controller (SHARE_INTERRUPTS).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Refine TMRA CMP DCU MAU share handler
                                    Rename I2Cx_Error_IrqHandler as I2Cx_EE_IrqHandler
   2023-09-30       CDT             Modify typo
                                    IRQxxx_Handler add __DSB for Arm Errata 838869
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
#include "hc32f4a0_ll_interrupts_share.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_HC32F4A0_SHARE_INTERRUPTS SHARE_INTERRUPTS
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
    /* DMA1 Ch.4 interrupt enabled */
    if (1UL == bCM_DMA1->CHCTL4_b.IE) {
        /* DMA1 Ch.4 Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKTC4) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.TC4) && (0UL != (VSSEL129 & BIT_MASK_04))) {
                DMA1_TC4_IrqHandler();
            }
        }
        /* DMA1 ch.4 Block Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKBTC4) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC4) && (0UL != (VSSEL129 & BIT_MASK_12))) {
                DMA1_BTC4_IrqHandler();
            }
        }
        /* DMA1 ch.4 Transfer/Request Error */
        u32Tmp1 = CM_DMA1->INTSTAT0 & (BIT_MASK_04 | BIT_MASK_20);
        u32Tmp2 = (uint32_t)(~(CM_DMA1->INTMASK0) & (BIT_MASK_04 | BIT_MASK_20));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16))) {
            DMA1_Error4_IrqHandler();
        }
    }
    /* DMA1 Ch.5 interrupt enabled */
    if (1UL == bCM_DMA1->CHCTL5_b.IE) {
        /* DMA1 Ch.5 Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKTC5) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.TC5) && (0UL != (VSSEL129 & BIT_MASK_05))) {
                DMA1_TC5_IrqHandler();
            }
        }
        /* DMA1 ch.5 Block Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKBTC5) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC5) && (0UL != (VSSEL129 & BIT_MASK_13))) {
                DMA1_BTC5_IrqHandler();
            }
        }
        /* DMA1 ch.5 Transfer/Request Error */
        u32Tmp1 = CM_DMA1->INTSTAT0 & (BIT_MASK_05 | BIT_MASK_21);
        u32Tmp2 = (uint32_t)(~(CM_DMA1->INTMASK0) & (BIT_MASK_05 | BIT_MASK_21));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16))) {
            DMA1_Error5_IrqHandler();
        }
    }
    /* DMA1 Ch.6 interrupt enabled */
    if (1UL == bCM_DMA1->CHCTL6_b.IE) {
        /* DMA1 Ch.6 Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKTC6) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.TC6) && (0UL != (VSSEL129 & BIT_MASK_06))) {
                DMA1_TC6_IrqHandler();
            }
        }
        /* DMA1 ch.6 Block Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKBTC6) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC6) && (0UL != (VSSEL129 & BIT_MASK_14))) {
                DMA1_BTC6_IrqHandler();
            }
        }
        /* DMA1 ch.6 Transfer/Request Error */
        u32Tmp1 = CM_DMA1->INTSTAT0 & (BIT_MASK_06 | BIT_MASK_22);
        u32Tmp2 = (uint32_t)(~(CM_DMA1->INTMASK0) & (BIT_MASK_06 | BIT_MASK_22));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16))) {
            DMA1_Error6_IrqHandler();
        }
    }
    /* DMA1 Ch.7 interrupt enabled */
    if (1UL == bCM_DMA1->CHCTL7_b.IE) {
        /* DMA1 Ch.7 Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKTC7) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.TC7) && (0UL != (VSSEL129 & BIT_MASK_07))) {
                DMA1_TC7_IrqHandler();
            }
        }
        /* DMA1 ch.7 Block Tx completed */
        if (0UL == bCM_DMA1->INTMASK1_b.MSKBTC7) {
            if ((1UL == bCM_DMA1->INTSTAT1_b.BTC7) && (0UL != (VSSEL129 & BIT_MASK_15))) {
                DMA1_BTC7_IrqHandler();
            }
        }
        /* DMA1 ch.7 Transfer/Request Error */
        u32Tmp1 = CM_DMA1->INTSTAT0 & (BIT_MASK_07 | BIT_MASK_22);
        u32Tmp2 = (uint32_t)(~(CM_DMA1->INTMASK0) & (BIT_MASK_07 | BIT_MASK_22));
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL129 & BIT_MASK_16))) {
            DMA1_Error7_IrqHandler();
        }
    }
    /* EFM error */
    if (1UL == bCM_EFM->FITE_b.PEERRITE) {
        /* EFM program/erase/protect/otp error */
        u32Tmp1 = CM_EFM->FSR & (EFM_FSR_PRTWERR0 | EFM_FSR_PGSZERR0 | EFM_FSR_MISMTCH0 |    \
                                 EFM_FSR_PRTWERR1 | EFM_FSR_PGSZERR1 | EFM_FSR_MISMTCH1 |    \
                                 EFM_FSR_OTPWERR0);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL129 & BIT_MASK_17))) {
            EFM_ProgramEraseError_IrqHandler();
        }
    }
    /* EFM read collision error*/
    if (1UL == bCM_EFM->FITE_b.COLERRITE) {
        /* EFM read collision */
        u32Tmp1 = CM_EFM->FSR & (EFM_FSR_COLERR0 | EFM_FSR_COLERR1);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL129 & BIT_MASK_18))) {
            EFM_ColError_IrqHandler();
        }
    }
    /* EFM operate end */
    if (1UL == bCM_EFM->FITE_b.OPTENDITE) {
        /* EFM operate end */
        u32Tmp1 = CM_EFM->FSR & (EFM_FSR_OPTEND0 | EFM_FSR_OPTEND1);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL129 & BIT_MASK_19))) {
            EFM_OpEnd_IrqHandler();
        }
    }
    /* QSPI access error */
    u32Tmp1 = CM_QSPI->SR & QSPI_SR_RAER;
    if ((0UL != u32Tmp1) && (0UL != (VSSEL129 & BIT_MASK_22))) {
        QSPI_Error_IrqHandler();
    }
    /*DCU1 */
    if (1UL == bCM_DCU1->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU1->INTEVTSEL;
        u32Tmp2 = CM_DCU1->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_23))) {
            DCU1_IrqHandler();
        }
    }
    /*DCU2 */
    if (1UL == bCM_DCU2->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU2->INTEVTSEL;
        u32Tmp2 = CM_DCU2->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_24))) {
            DCU2_IrqHandler();
        }
    }
    /*DCU3 */
    if (1UL == bCM_DCU3->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU3->INTEVTSEL;
        u32Tmp2 = CM_DCU3->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_25))) {
            DCU3_IrqHandler();
        }
    }
    /*DCU4 */
    if (1UL == bCM_DCU4->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU4->INTEVTSEL;
        u32Tmp2 = CM_DCU4->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_26))) {
            DCU4_IrqHandler();
        }
    }
    /*DCU5 */
    if (1UL == bCM_DCU5->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU5->INTEVTSEL;
        u32Tmp2 = CM_DCU5->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_27))) {
            DCU5_IrqHandler();
        }
    }
    /*DCU6 */
    if (1UL == bCM_DCU6->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU6->INTEVTSEL;
        u32Tmp2 = CM_DCU6->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_28))) {
            DCU6_IrqHandler();
        }
    }
    /*DCU7 */
    if (1UL == bCM_DCU7->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU7->INTEVTSEL;
        u32Tmp2 = CM_DCU7->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_29))) {
            DCU7_IrqHandler();
        }
    }
    /*DCU8 */
    if (1UL == bCM_DCU8->CTL_b.INTEN) {
        u32Tmp1 = CM_DCU8->INTEVTSEL;
        u32Tmp2 = CM_DCU8->FLAG;
        if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0E7FUL)) && (0UL != (VSSEL129 & BIT_MASK_30))) {
            DCU8_IrqHandler();
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
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* MAU square */
    if (1UL == bCM_MAU->CSR_b.INTEN) {
        if (0UL != (VSSEL130 & BIT_MASK_19)) {
            MAU_Sqrt_IrqHandler();
        }
    } else {
        /* DMA2 Ch.0 interrupt enabled */
        if (1UL == bCM_DMA2->CHCTL0_b.IE) {
            /* DMA2 Ch.0 Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKTC0) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.TC0) && (0UL != (VSSEL130 & BIT_MASK_00))) {
                    DMA2_TC0_IrqHandler();
                }
            }
            /* DMA2 ch.0 Block Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC0) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.BTC0) && (0UL != (VSSEL130 & BIT_MASK_08))) {
                    DMA2_BTC0_IrqHandler();
                }
            }
            /* DMA2 ch.0 Transfer/Request Error */
            u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_00 | BIT_MASK_16);
            u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_00 | BIT_MASK_16));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16))) {
                DMA2_Error0_IrqHandler();
            }
        }
        /* DMA2 Ch.1 interrupt enabled */
        if (1UL == bCM_DMA2->CHCTL1_b.IE) {
            /* DMA2 Ch.1 Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKTC1) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.TC1) && (0UL != (VSSEL130 & BIT_MASK_01))) {
                    DMA2_TC1_IrqHandler();
                }
            }
            /* DMA2 ch.1 Block Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC1) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.BTC1) && (0UL != (VSSEL130 & BIT_MASK_09))) {
                    DMA2_BTC1_IrqHandler();
                }
            }
            /* DMA2 ch.1 Transfer/Request Error */
            u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_01 | BIT_MASK_17);
            u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_01 | BIT_MASK_17));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16))) {
                DMA2_Error1_IrqHandler();
            }
        }
        /* DMA2 Ch.2 interrupt enabled */
        if (1UL == bCM_DMA2->CHCTL2_b.IE) {
            /* DMA2 Ch.2 Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKTC2) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.TC2) && (0UL != (VSSEL130 & BIT_MASK_02))) {
                    DMA2_TC2_IrqHandler();
                }
            }
            /* DMA2 ch.2 Block Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC2) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.BTC2) && (0UL != (VSSEL130 & BIT_MASK_10))) {
                    DMA2_BTC2_IrqHandler();
                }
            }
            /* DMA2 ch.2 Transfer/Request Error */
            u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_02 | BIT_MASK_18);
            u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_02 | BIT_MASK_18));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16))) {
                DMA2_Error2_IrqHandler();
            }
        }
        /* DMA2 Ch.3 interrupt enabled */
        if (1UL == bCM_DMA2->CHCTL3_b.IE) {
            /* DMA2 Ch.3 Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKTC3) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.TC3) && (0UL != (VSSEL130 & BIT_MASK_03))) {
                    DMA2_TC3_IrqHandler();
                }
            }
            /* DMA2 ch.3 Block Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC3) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.BTC3) && (0UL != (VSSEL130 & BIT_MASK_11))) {
                    DMA2_BTC3_IrqHandler();
                }
            }
            /* DMA2 ch.3 Transfer/Request Error */
            u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_03 | BIT_MASK_19);
            u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_03 | BIT_MASK_19));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16))) {
                DMA2_Error3_IrqHandler();
            }
        }
        /* DMA2 Ch.4 interrupt enabled */
        if (1UL == bCM_DMA2->CHCTL4_b.IE) {
            /* DMA2 Ch.4 Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKTC4) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.TC4) && (0UL != (VSSEL130 & BIT_MASK_04))) {
                    DMA2_TC4_IrqHandler();
                }
            }
            /* DMA2 ch.4 Block Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC4) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.BTC4) && (0UL != (VSSEL130 & BIT_MASK_12))) {
                    DMA2_BTC4_IrqHandler();
                }
            }
            /* DMA2 ch.4 Transfer/Request Error */
            u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_04 | BIT_MASK_20);
            u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_04 | BIT_MASK_20));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16))) {
                DMA2_Error4_IrqHandler();
            }
        }
        /* DMA2 Ch.5 interrupt enabled */
        if (1UL == bCM_DMA2->CHCTL5_b.IE) {
            /* DMA2 Ch.5 Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKTC5) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.TC5) && (0UL != (VSSEL130 & BIT_MASK_05))) {
                    DMA2_TC5_IrqHandler();
                }
            }
            /* DMA2 ch.5 Block Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC5) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.BTC5) && (0UL != (VSSEL130 & BIT_MASK_13))) {
                    DMA2_BTC5_IrqHandler();
                }
            }
            /* DMA2 ch.5 Transfer/Request Error */
            u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_05 | BIT_MASK_21);
            u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_05 | BIT_MASK_21));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16))) {
                DMA2_Error5_IrqHandler();
            }
        }
        /* DMA2 Ch.6 interrupt enabled */
        if (1UL == bCM_DMA2->CHCTL6_b.IE) {
            /* DMA2 Ch.6 Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKTC6) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.TC6) && (0UL != (VSSEL130 & BIT_MASK_06))) {
                    DMA2_TC6_IrqHandler();
                }
            }
            /* DMA2 ch.6 Block Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC6) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.BTC6) && (0UL != (VSSEL130 & BIT_MASK_14))) {
                    DMA2_BTC6_IrqHandler();
                }
            }
            /* DMA2 ch.6 Transfer/Request Error */
            u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_06 | BIT_MASK_22);
            u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_06 | BIT_MASK_22));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16))) {
                DMA2_Error6_IrqHandler();
            }
        }
        /* DMA2 Ch.7 interrupt enabled */
        if (1UL == bCM_DMA2->CHCTL7_b.IE) {
            /* DMA2 Ch.7 Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKTC7) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.TC7) && (0UL != (VSSEL130 & BIT_MASK_07))) {
                    DMA2_TC7_IrqHandler();
                }
            }
            /* DMA2 ch.7 Block Tx completed */
            if (0UL == bCM_DMA2->INTMASK1_b.MSKBTC7) {
                if ((1UL == bCM_DMA2->INTSTAT1_b.BTC7) && (0UL != (VSSEL130 & BIT_MASK_15))) {
                    DMA2_BTC7_IrqHandler();
                }
            }
            /* DMA2 ch.7 Transfer/Request Error */
            u32Tmp1 = CM_DMA2->INTSTAT0 & (BIT_MASK_07 | BIT_MASK_22);
            u32Tmp2 = (uint32_t)(~(CM_DMA2->INTMASK0) & (BIT_MASK_07 | BIT_MASK_22));
            if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL130 & BIT_MASK_16))) {
                DMA2_Error7_IrqHandler();
            }
        }
        /* DVP frame start */
        if (1UL == bCM_DVP->IER_b.FSIEN) {
            if ((1UL == bCM_DVP->STR_b.FSF) && (0UL != (VSSEL130 & BIT_MASK_20))) {
                DVP_FrameStart_IrqHandler();
            }
        }
        /* DVP line start */
        if (1UL == bCM_DVP->IER_b.LSIEN) {
            if ((1UL == bCM_DVP->STR_b.LSF) && (0UL != (VSSEL130 & BIT_MASK_21))) {
                DVP_LineStart_IrqHandler();
            }
        }
        /* DVP line end */
        if (1UL == bCM_DVP->IER_b.LEIEN) {
            if ((1UL == bCM_DVP->STR_b.LEF) && (0UL != (VSSEL130 & BIT_MASK_22))) {
                DVP_LineEnd_IrqHandler();
            }
        }
        /* DVP frame end */
        if (1UL == bCM_DVP->IER_b.FEIEN) {
            if ((1UL == bCM_DVP->STR_b.FEF) && (0UL != (VSSEL130 & BIT_MASK_23))) {
                DVP_FrameEnd_IrqHandler();
            }
        }
        /* DVP software sync err */
        if (1UL == bCM_DVP->IER_b.SQUERIEN) {
            if ((1UL == bCM_DVP->STR_b.SQUERF) && (0UL != (VSSEL130 & BIT_MASK_24))) {
                DVP_SWSyncError_IrqHandler();
            }
        }
        /* DVP fifo overfolw err */
        if (1UL == bCM_DVP->IER_b.FIFOERIEN) {
            if ((1UL == bCM_DVP->STR_b.FIFOERF) && (0UL != (VSSEL130 & BIT_MASK_25))) {
                DVP_FifoError_IrqHandler();
            }
        }
        /* FMAC 1 */
        if (1UL == bCM_FMAC1->IER_b.INTEN) {
            if ((1UL == bCM_FMAC1->STR_b.READY) && (0UL != (VSSEL130 & BIT_MASK_27))) {
                FMAC1_IrqHandler();
            }
        }
        /* FMAC 2 */
        if (1UL == bCM_FMAC2->IER_b.INTEN) {
            if ((1UL == bCM_FMAC2->STR_b.READY) && (0UL != (VSSEL130 & BIT_MASK_28))) {
                FMAC2_IrqHandler();
            }
        }
        /* FMAC 3 */
        if (1UL == bCM_FMAC3->IER_b.INTEN) {
            if ((1UL == bCM_FMAC3->STR_b.READY) && (0UL != (VSSEL130 & BIT_MASK_29))) {
                FMAC3_IrqHandler();
            }
        }
        /* FMAC 4 */
        if (1UL == bCM_FMAC4->IER_b.INTEN) {
            if ((1UL == bCM_FMAC4->STR_b.READY) && (0UL != (VSSEL130 & BIT_MASK_30))) {
                FMAC4_IrqHandler();
            }
        }
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

    /* Timer0 unit1, Ch.A compare match */
    if (1UL == bCM_TMR0_1->BCONR_b.INTENA) {
        if ((1UL == bCM_TMR0_1->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_00))) {
            TMR0_1_CmpA_IrqHandler();
        }
    }
    /* Timer0 unit1, Ch.B compare match */
    if (1UL == bCM_TMR0_1->BCONR_b.INTENB) {
        if ((1UL == bCM_TMR0_1->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_01))) {
            TMR0_1_CmpB_IrqHandler();
        }
    }
    /* Timer0 unit2, Ch.A compare match */
    if (1UL == bCM_TMR0_2->BCONR_b.INTENA) {
        if ((1UL == bCM_TMR0_2->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_02))) {
            TMR0_2_CmpA_IrqHandler();
        }
    }
    /* Timer0 unit2, Ch.B compare match */
    if (1UL == bCM_TMR0_2->BCONR_b.INTENB) {
        if ((1UL == bCM_TMR0_2->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_03))) {
            TMR0_2_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit1, Ch.A compare match */
    if (1UL == bCM_TMR2_1->ICONR_b.CMENA) {
        if ((1UL == bCM_TMR2_1->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_04))) {
            TMR2_1_CmpA_IrqHandler();
        }
    }
    /* Timer2 unit1, Ch.B compare match */
    if (1UL == bCM_TMR2_1->ICONR_b.CMENB) {
        if ((1UL == bCM_TMR2_1->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_05))) {
            TMR2_1_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit1, Ch.A overflow */
    if (1UL == bCM_TMR2_1->ICONR_b.OVENA) {
        if ((1UL == bCM_TMR2_1->STFLR_b.OVFA) && (0UL != (VSSEL131 & BIT_MASK_06))) {
            TMR2_1_OvfA_IrqHandler();
        }
    }
    /* Timer2 unit1, Ch.B overflow */
    if (1UL == bCM_TMR2_1->ICONR_b.OVENB) {
        if ((1UL == bCM_TMR2_1->STFLR_b.OVFB) && (0UL != (VSSEL131 & BIT_MASK_07))) {
            TMR2_1_OvfB_IrqHandler();
        }
    }
    /* Timer2 unit2, Ch.A compare match */
    if (1UL == bCM_TMR2_2->ICONR_b.CMENA) {
        if ((1UL == bCM_TMR2_2->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_08))) {
            TMR2_2_CmpA_IrqHandler();
        }
    }
    /* Timer2 unit2, Ch.B compare match */
    if (1UL == bCM_TMR2_2->ICONR_b.CMENB) {
        if ((1UL == bCM_TMR2_2->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_09))) {
            TMR2_2_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit2, Ch.A overflow */
    if (1UL == bCM_TMR2_2->ICONR_b.OVENA) {
        if ((1UL == bCM_TMR2_2->STFLR_b.OVFA) && (0UL != (VSSEL131 & BIT_MASK_10))) {
            TMR2_2_OvfA_IrqHandler();
        }
    }
    /* Timer2 unit2, Ch.B overflow */
    if (1UL == bCM_TMR2_2->ICONR_b.OVENB) {
        if ((1UL == bCM_TMR2_2->STFLR_b.OVFB) && (0UL != (VSSEL131 & BIT_MASK_11))) {
            TMR2_2_OvfB_IrqHandler();
        }
    }
    /* Timer2 unit3, Ch.A compare match */
    if (1UL == bCM_TMR2_3->ICONR_b.CMENA) {
        if ((1UL == bCM_TMR2_3->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_12))) {
            TMR2_3_CmpA_IrqHandler();
        }
    }
    /* Timer2 unit3, Ch.B compare match */
    if (1UL == bCM_TMR2_3->ICONR_b.CMENB) {
        if ((1UL == bCM_TMR2_3->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_13))) {
            TMR2_3_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit3, Ch.A overflow */
    if (1UL == bCM_TMR2_3->ICONR_b.OVENA) {
        if ((1UL == bCM_TMR2_3->STFLR_b.OVFA) && (0UL != (VSSEL131 & BIT_MASK_14))) {
            TMR2_3_OvfA_IrqHandler();
        }
    }
    /* Timer2 unit3, Ch.B overflow */
    if (1UL == bCM_TMR2_3->ICONR_b.OVENB) {
        if ((1UL == bCM_TMR2_3->STFLR_b.OVFB) && (0UL != (VSSEL131 & BIT_MASK_15))) {
            TMR2_3_OvfB_IrqHandler();
        }
    }
    /* Timer2 unit4, Ch.A compare match */
    if (1UL == bCM_TMR2_4->ICONR_b.CMENA) {
        if ((1UL == bCM_TMR2_4->STFLR_b.CMFA) && (0UL != (VSSEL131 & BIT_MASK_16))) {
            TMR2_4_CmpA_IrqHandler();
        }
    }
    /* Timer2 unit4, Ch.B compare match */
    if (1UL == bCM_TMR2_4->ICONR_b.CMENB) {
        if ((1UL == bCM_TMR2_4->STFLR_b.CMFB) && (0UL != (VSSEL131 & BIT_MASK_17))) {
            TMR2_4_CmpB_IrqHandler();
        }
    }
    /* Timer2 unit4, Ch.A overflow */
    if (1UL == bCM_TMR2_4->ICONR_b.OVENA) {
        if ((1UL == bCM_TMR2_4->STFLR_b.OVFA) && (0UL != (VSSEL131 & BIT_MASK_18))) {
            TMR2_4_OvfA_IrqHandler();
        }
    }
    /* Timer2 unit4, Ch.B overflow */
    if (1UL == bCM_TMR2_4->ICONR_b.OVENB) {
        if ((1UL == bCM_TMR2_4->STFLR_b.OVFB) && (0UL != (VSSEL131 & BIT_MASK_19))) {
            TMR2_4_OvfB_IrqHandler();
        }
    }
    /* RTC time stamp 0 */
    if (1UL == bCM_RTC->TPCR0_b.TPIE0) {
        if ((1UL == bCM_RTC->TPSR_b.TPF0) && (0UL != (VSSEL131 & BIT_MASK_24))) {
            RTC_TimeStamp0_IrqHandler();
        }
    }
    /* RTC time stamp 1 */
    if (1UL == bCM_RTC->TPCR1_b.TPIE1) {
        if ((1UL == bCM_RTC->TPSR_b.TPF1) && (0UL != (VSSEL131 & BIT_MASK_24))) {
            RTC_TimeStamp1_IrqHandler();
        }
    }
    /* RTC alarm */
    if (1UL == bCM_RTC->CR2_b.ALMIE) {
        if ((1UL == bCM_RTC->CR2_b.ALMF) && (0UL != (VSSEL131 & BIT_MASK_25))) {
            RTC_Alarm_IrqHandler();
        }
    }
    /* RTC period */
    if (1UL == bCM_RTC->CR2_b.PRDIE) {
        if ((1UL == bCM_RTC->CR2_b.PRDF) && (0UL != (VSSEL131 & BIT_MASK_26))) {
            RTC_Period_IrqHandler();
        }
    }
    /* XTAL stop */
    if (1UL == bCM_CMU->XTALSTDCR_b.XTALSTDIE) {
        if ((1UL == bCM_CMU->XTALSTDSR_b.XTALSTDF) && (0UL != (VSSEL131 & BIT_MASK_29))) {
            CLK_XtalStop_IrqHandler();
        }
    }
    /* Wakeup timer overflow */
    if (1UL == bCM_PWC->WKTC2_b.WKTCE) {
        if ((1UL == bCM_PWC->WKTC2_b.WKOVF) && (0UL != (VSSEL131 & BIT_MASK_30))) {
            PWC_WakeupTimer_IrqHandler();
        }
    }
    /* SWDT underflow or refresh error */
    u32Tmp1 = CM_SWDT->SR & (SWDT_SR_UDF | SWDT_SR_REF);
    if ((0UL != u32Tmp1) && (0UL != (VSSEL131 & BIT_MASK_31))) {
        SWDT_IrqHandler();
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

    /* Timer6 Unit.1 general compare match A */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMAF) && (0UL != (VSSEL132 & BIT_MASK_00))) {
            TMR6_1_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.1 general compare match B */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMBF) && (0UL != (VSSEL132 & BIT_MASK_01))) {
            TMR6_1_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.1 general compare match C */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMCF) && (0UL != (VSSEL132 & BIT_MASK_02))) {
            TMR6_1_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.1 general compare match D */
    if (1UL == bCM_TMR6_1->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMDF) && (0UL != (VSSEL132 & BIT_MASK_03))) {
            TMR6_1_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.1 general compare match E */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMEF) && (0UL != (VSSEL132 & BIT_MASK_04))) {
            TMR6_1_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.1 general compare match F */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMFF) && (0UL != (VSSEL132 & BIT_MASK_05))) {
            TMR6_1_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.1 overflow*/
    if (1UL == bCM_TMR6_1->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_1->STFLR_b.OVFF) && (0UL != (VSSEL132 & BIT_MASK_06))) {
            TMR6_1_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.1 underflow*/
    if (1UL == bCM_TMR6_1->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_1->STFLR_b.UDFF) && (0UL != (VSSEL132 & BIT_MASK_07))) {
            TMR6_1_GUdf_IrqHandler();
        }
    }
    /* Timer4 Unit.1 U phase higher compare match */
    if (1UL == bCM_TMR4_1->OCSRU_b.OCIEH) {
        if ((1UL == bCM_TMR4_1->OCSRU_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_08))) {
            TMR4_1_GCmpUH_IrqHandler();
        }
    }
    /* Timer4 Unit.1 U phase lower compare match */
    if (1UL == bCM_TMR4_1->OCSRU_b.OCIEL) {
        if ((1UL == bCM_TMR4_1->OCSRU_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_09))) {
            TMR4_1_GCmpUL_IrqHandler();
        }
    }
    /* Timer4 Unit.1 V phase higher compare match */
    if (1UL == bCM_TMR4_1->OCSRV_b.OCIEH) {
        if ((1UL == bCM_TMR4_1->OCSRV_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_10))) {
            TMR4_1_GCmpVH_IrqHandler();
        }
    }
    /* Timer4 Unit.1 V phase lower compare match */
    if (1UL == bCM_TMR4_1->OCSRV_b.OCIEL) {
        if ((1UL == bCM_TMR4_1->OCSRV_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_11))) {
            TMR4_1_GCmpVL_IrqHandler();
        }
    }
    /* Timer4 Unit.1 W phase higher compare match */
    if (1UL == bCM_TMR4_1->OCSRW_b.OCIEH) {
        if ((1UL == bCM_TMR4_1->OCSRW_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_12))) {
            TMR4_1_GCmpWH_IrqHandler();
        }
    }
    /* Timer4 Unit.1 W phase lower compare match */
    if (1UL == bCM_TMR4_1->OCSRW_b.OCIEL) {
        if ((1UL == bCM_TMR4_1->OCSRW_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_13))) {
            TMR4_1_GCmpWL_IrqHandler();
        }
    }
    /* Timer4 Unit.1 overflow */
    if (1UL == bCM_TMR4_1->CCSR_b.IRQPEN) {
        if ((1UL == bCM_TMR4_1->CCSR_b.IRQPF) && (0UL != (VSSEL132 & BIT_MASK_14))) {
            TMR4_1_Ovf_IrqHandler();
        }
    }
    /* Timer4 Unit.1 underflow */
    if (1UL == bCM_TMR4_1->CCSR_b.IRQZEN) {
        if ((1UL == bCM_TMR4_1->CCSR_b.IRQZF) && (0UL != (VSSEL132 & BIT_MASK_15))) {
            TMR4_1_Udf_IrqHandler();
        }
    }
    /* Timer6 Unit.2 general compare match A */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMAF) && (0UL != (VSSEL132 & BIT_MASK_16))) {
            TMR6_2_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.2 general compare match B */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMBF) && (0UL != (VSSEL132 & BIT_MASK_17))) {
            TMR6_2_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.2 general compare match C */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMCF) && (0UL != (VSSEL132 & BIT_MASK_18))) {
            TMR6_2_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.2 general compare match D */
    if (1UL == bCM_TMR6_2->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMDF) && (0UL != (VSSEL132 & BIT_MASK_19))) {
            TMR6_2_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.2 general compare match E */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMEF) && (0UL != (VSSEL132 & BIT_MASK_20))) {
            TMR6_2_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.2 general compare match F */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMFF) && (0UL != (VSSEL132 & BIT_MASK_21))) {
            TMR6_2_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.2 overflow*/
    if (1UL == bCM_TMR6_2->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_2->STFLR_b.OVFF) && (0UL != (VSSEL132 & BIT_MASK_22))) {
            TMR6_2_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.2 underflow*/
    if (1UL == bCM_TMR6_2->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_2->STFLR_b.UDFF) && (0UL != (VSSEL132 & BIT_MASK_23))) {
            TMR6_2_GUdf_IrqHandler();
        }
    }
    /* Timer4 Unit.2 U phase higher compare match */
    if (1UL == bCM_TMR4_2->OCSRU_b.OCIEH) {
        if ((1UL == bCM_TMR4_2->OCSRU_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_24))) {
            TMR4_2_GCmpUH_IrqHandler();
        }
    }
    /* Timer4 Unit.2 U phase lower compare match */
    if (1UL == bCM_TMR4_2->OCSRU_b.OCIEL) {
        if ((1UL == bCM_TMR4_2->OCSRU_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_25))) {
            TMR4_2_GCmpUL_IrqHandler();
        }
    }
    /* Timer4 Unit.2 V phase higher compare match */
    if (1UL == bCM_TMR4_2->OCSRV_b.OCIEH) {
        if ((1UL == bCM_TMR4_2->OCSRV_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_26))) {
            TMR4_2_GCmpVH_IrqHandler();
        }
    }
    /* Timer4 Unit.2 V phase lower compare match */
    if (1UL == bCM_TMR4_2->OCSRV_b.OCIEL) {
        if ((1UL == bCM_TMR4_2->OCSRV_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_27))) {
            TMR4_2_GCmpVL_IrqHandler();
        }
    }
    /* Timer4 Unit.2 W phase higher compare match */
    if (1UL == bCM_TMR4_2->OCSRW_b.OCIEH) {
        if ((1UL == bCM_TMR4_2->OCSRW_b.OCFH) && (0UL != (VSSEL132 & BIT_MASK_28))) {
            TMR4_2_GCmpWH_IrqHandler();
        }
    }
    /* Timer4 Unit.2 W phase lower compare match */
    if (1UL == bCM_TMR4_2->OCSRW_b.OCIEL) {
        if ((1UL == bCM_TMR4_2->OCSRW_b.OCFL) && (0UL != (VSSEL132 & BIT_MASK_29))) {
            TMR4_2_GCmpWL_IrqHandler();
        }
    }
    /* Timer4 Unit.2 overflow */
    if (1UL == bCM_TMR4_2->CCSR_b.IRQPEN) {
        if ((1UL == bCM_TMR4_2->CCSR_b.IRQPF) && (0UL != (VSSEL132 & BIT_MASK_30))) {
            TMR4_2_Ovf_IrqHandler();
        }
    }
    /* Timer4 Unit.2 underflow */
    if (1UL == bCM_TMR4_2->CCSR_b.IRQZEN) {
        if ((1UL == bCM_TMR4_2->CCSR_b.IRQZF) && (0UL != (VSSEL132 & BIT_MASK_31))) {
            TMR4_2_Udf_IrqHandler();
        }
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.133 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ133_Handler(void)
{
    const uint32_t VSSEL133 = CM_INTC->VSSEL133;

    /* Timer6 Unit.3 general compare match A */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMAF) && (0UL != (VSSEL133 & BIT_MASK_00))) {
            TMR6_3_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.3 general compare match B */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMBF) && (0UL != (VSSEL133 & BIT_MASK_01))) {
            TMR6_3_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.3 general compare match C */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMCF) && (0UL != (VSSEL133 & BIT_MASK_02))) {
            TMR6_3_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.3 general compare match D */
    if (1UL == bCM_TMR6_3->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMDF) && (0UL != (VSSEL133 & BIT_MASK_03))) {
            TMR6_3_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.3 general compare match E */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMEF) && (0UL != (VSSEL133 & BIT_MASK_04))) {
            TMR6_3_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.3 general compare match F */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMFF) && (0UL != (VSSEL133 & BIT_MASK_05))) {
            TMR6_3_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.3 overflow*/
    if (1UL == bCM_TMR6_3->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_3->STFLR_b.OVFF) && (0UL != (VSSEL133 & BIT_MASK_06))) {
            TMR6_3_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.3 underflow*/
    if (1UL == bCM_TMR6_3->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_3->STFLR_b.UDFF) && (0UL != (VSSEL133 & BIT_MASK_07))) {
            TMR6_3_GUdf_IrqHandler();
        }
    }
    /* Timer4 Unit.3 U phase higher compare match */
    if (1UL == bCM_TMR4_3->OCSRU_b.OCIEH) {
        if ((1UL == bCM_TMR4_3->OCSRU_b.OCFH) && (0UL != (VSSEL133 & BIT_MASK_08))) {
            TMR4_3_GCmpUH_IrqHandler();
        }
    }
    /* Timer4 Unit.3 U phase lower compare match */
    if (1UL == bCM_TMR4_3->OCSRU_b.OCIEL) {
        if ((1UL == bCM_TMR4_3->OCSRU_b.OCFL) && (0UL != (VSSEL133 & BIT_MASK_09))) {
            TMR4_3_GCmpUL_IrqHandler();
        }
    }
    /* Timer4 Unit.3 V phase higher compare match */
    if (1UL == bCM_TMR4_3->OCSRV_b.OCIEH) {
        if ((1UL == bCM_TMR4_3->OCSRV_b.OCFH) && (0UL != (VSSEL133 & BIT_MASK_10))) {
            TMR4_3_GCmpVH_IrqHandler();
        }
    }
    /* Timer4 Unit.3 V phase lower compare match */
    if (1UL == bCM_TMR4_3->OCSRV_b.OCIEL) {
        if ((1UL == bCM_TMR4_3->OCSRV_b.OCFL) && (0UL != (VSSEL133 & BIT_MASK_11))) {
            TMR4_3_GCmpVL_IrqHandler();
        }
    }
    /* Timer4 Unit.3 W phase higher compare match */
    if (1UL == bCM_TMR4_3->OCSRW_b.OCIEH) {
        if ((1UL == bCM_TMR4_3->OCSRW_b.OCFH) && (0UL != (VSSEL133 & BIT_MASK_12))) {
            TMR4_3_GCmpWH_IrqHandler();
        }
    }
    /* Timer4 Unit.3 W phase lower compare match */
    if (1UL == bCM_TMR4_3->OCSRW_b.OCIEL) {
        if ((1UL == bCM_TMR4_3->OCSRW_b.OCFL) && (0UL != (VSSEL133 & BIT_MASK_13))) {
            TMR4_3_GCmpWL_IrqHandler();
        }
    }
    /* Timer4 Unit.3 overflow */
    if (1UL == bCM_TMR4_3->CCSR_b.IRQPEN) {
        if ((1UL == bCM_TMR4_3->CCSR_b.IRQPF) && (0UL != (VSSEL133 & BIT_MASK_14))) {
            TMR4_3_Ovf_IrqHandler();
        }
    }
    /* Timer4 Unit.3 underflow */
    if (1UL == bCM_TMR4_3->CCSR_b.IRQZEN) {
        if ((1UL == bCM_TMR4_3->CCSR_b.IRQZF) && (0UL != (VSSEL133 & BIT_MASK_15))) {
            TMR4_3_Udf_IrqHandler();
        }
    }
    /* Timer6 Unit.1 dead time */
    if (1UL == bCM_TMR6_1->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_1->STFLR_b.DTEF) && (0UL != (VSSEL133 & BIT_MASK_16))) {
            TMR6_1_GDte_IrqHandler();
        }
    }
    /* Timer6 Unit.1 specified up compare match A*/
    if (1UL == bCM_TMR6_1->ICONR_b.INTENSAU) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMSAUF) && (0UL != (VSSEL133 & BIT_MASK_19))) {
            TMR6_1_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Unit.1 specified down compare match A*/
    if (1UL == bCM_TMR6_1->ICONR_b.INTENSAD) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMSADF) && (0UL != (VSSEL133 & BIT_MASK_19))) {
            TMR6_1_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Unit.1 specified up compare match B*/
    if (1UL == bCM_TMR6_1->ICONR_b.INTENSBU) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMSBUF) && (0UL != (VSSEL133 & BIT_MASK_20))) {
            TMR6_1_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Unit.1 specified down compare match B*/
    if (1UL == bCM_TMR6_1->ICONR_b.INTENSBD) {
        if ((1UL == bCM_TMR6_1->STFLR_b.CMSBDF) && (0UL != (VSSEL133 & BIT_MASK_20))) {
            TMR6_1_SCmpDownB_IrqHandler();
        }
    }
    /* Timer4 Unit.1 U phase reload */
    if (0UL == bCM_TMR4_1->RCSR_b.RTIDU) {
        if ((1UL == bCM_TMR4_1->RCSR_b.RTIFU) && (0UL != (VSSEL133 & BIT_MASK_21))) {
            TMR4_1_ReloadU_IrqHandler();
        }
    }
    /* Timer4 Unit.1 V phase reload */
    if (0UL == bCM_TMR4_1->RCSR_b.RTIDV) {
        if ((1UL == bCM_TMR4_1->RCSR_b.RTIFV) && (0UL != (VSSEL133 & BIT_MASK_22))) {
            TMR4_1_ReloadV_IrqHandler();
        }
    }
    /* Timer4 Unit.1 W phase reload */
    if (0UL == bCM_TMR4_1->RCSR_b.RTIDW) {
        if ((1UL == bCM_TMR4_1->RCSR_b.RTIFW) && (0UL != (VSSEL133 & BIT_MASK_23))) {
            TMR4_1_ReloadW_IrqHandler();
        }
    }
    /* Timer6 Unit.2 dead time */
    if (1UL == bCM_TMR6_2->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_2->STFLR_b.DTEF) && (0UL != (VSSEL133 & BIT_MASK_24))) {
            TMR6_2_GDte_IrqHandler();
        }
    }
    /* Timer6 Unit.2 specified up compare match A*/
    if (1UL == bCM_TMR6_2->ICONR_b.INTENSAU) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMSAUF) && (0UL != (VSSEL133 & BIT_MASK_27))) {
            TMR6_2_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Unit.2 specified down compare match A*/
    if (1UL == bCM_TMR6_2->ICONR_b.INTENSAD) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMSADF) && (0UL != (VSSEL133 & BIT_MASK_27))) {
            TMR6_2_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Unit.2 specified up compare match B*/
    if (1UL == bCM_TMR6_2->ICONR_b.INTENSBU) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMSBUF) && (0UL != (VSSEL133 & BIT_MASK_28))) {
            TMR6_2_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Unit.2 specified down compare match B*/
    if (1UL == bCM_TMR6_2->ICONR_b.INTENSBD) {
        if ((1UL == bCM_TMR6_2->STFLR_b.CMSBDF) && (0UL != (VSSEL133 & BIT_MASK_28))) {
            TMR6_2_SCmpDownB_IrqHandler();
        }
    }
    /* Timer4 Unit.2 U phase reload */
    if (0UL == bCM_TMR4_2->RCSR_b.RTIDU) {
        if ((1UL == bCM_TMR4_2->RCSR_b.RTIFU) && (0UL != (VSSEL133 & BIT_MASK_29))) {
            TMR4_2_ReloadU_IrqHandler();
        }
    }
    /* Timer4 Unit.2 V phase reload */
    if (0UL == bCM_TMR4_2->RCSR_b.RTIDV) {
        if ((1UL == bCM_TMR4_2->RCSR_b.RTIFV) && (0UL != (VSSEL133 & BIT_MASK_30))) {
            TMR4_2_ReloadV_IrqHandler();
        }
    }
    /* Timer4 Unit.2 W phase reload */
    if (0UL == bCM_TMR4_2->RCSR_b.RTIDW) {
        if ((1UL == bCM_TMR4_2->RCSR_b.RTIFW) && (0UL != (VSSEL133 & BIT_MASK_31))) {
            TMR4_2_ReloadW_IrqHandler();
        }
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.134 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ134_Handler(void)
{
    const uint32_t VSSEL134 = CM_INTC->VSSEL134;

    /* Timer6 Unit.3 dead time */
    if (1UL == bCM_TMR6_3->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_3->STFLR_b.DTEF) && (0UL != (VSSEL134 & BIT_MASK_00))) {
            TMR6_3_GDte_IrqHandler();
        }
    }
    /* Timer6 Unit.3 specified up compare match A*/
    if (1UL == bCM_TMR6_3->ICONR_b.INTENSAU) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMSAUF) && (0UL != (VSSEL134 & BIT_MASK_03))) {
            TMR6_3_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Unit.3 specified down compare match A*/
    if (1UL == bCM_TMR6_3->ICONR_b.INTENSAD) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMSADF) && (0UL != (VSSEL134 & BIT_MASK_03))) {
            TMR6_3_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Unit.3 specified up compare match B*/
    if (1UL == bCM_TMR6_3->ICONR_b.INTENSBU) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMSBUF) && (0UL != (VSSEL134 & BIT_MASK_04))) {
            TMR6_3_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Unit.3 specified down compare match B*/
    if (1UL == bCM_TMR6_3->ICONR_b.INTENSBD) {
        if ((1UL == bCM_TMR6_3->STFLR_b.CMSBDF) && (0UL != (VSSEL134 & BIT_MASK_04))) {
            TMR6_3_SCmpDownB_IrqHandler();
        }
    }
    /* Timer4 Unit.3 U phase reload */
    if (0UL == bCM_TMR4_3->RCSR_b.RTIDU) {
        if ((1UL == bCM_TMR4_3->RCSR_b.RTIFU) && (0UL != (VSSEL134 & BIT_MASK_05))) {
            TMR4_3_ReloadU_IrqHandler();
        }
    }
    /* Timer4 Unit.3 V phase reload */
    if (0UL == bCM_TMR4_3->RCSR_b.RTIDV) {
        if ((1UL == bCM_TMR4_3->RCSR_b.RTIFV) && (0UL != (VSSEL134 & BIT_MASK_06))) {
            TMR4_3_ReloadV_IrqHandler();
        }
    }
    /* Timer4 Unit.3 W phase reload */
    if (0UL == bCM_TMR4_3->RCSR_b.RTIDW) {
        if ((1UL == bCM_TMR4_3->RCSR_b.RTIFW) && (0UL != (VSSEL134 & BIT_MASK_07))) {
            TMR4_3_ReloadW_IrqHandler();
        }
    }
    /* Timer6 Unit.4 general compare match A */
    if (1UL == bCM_TMR6_4->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMAF) && (0UL != (VSSEL134 & BIT_MASK_16))) {
            TMR6_4_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.4 general compare match B */
    if (1UL == bCM_TMR6_4->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMBF) && (0UL != (VSSEL134 & BIT_MASK_17))) {
            TMR6_4_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.4 general compare match C */
    if (1UL == bCM_TMR6_4->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMCF) && (0UL != (VSSEL134 & BIT_MASK_18))) {
            TMR6_4_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.4 general compare match D */
    if (1UL == bCM_TMR6_4->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMDF) && (0UL != (VSSEL134 & BIT_MASK_19))) {
            TMR6_4_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.4 general compare match E */
    if (1UL == bCM_TMR6_4->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMEF) && (0UL != (VSSEL134 & BIT_MASK_20))) {
            TMR6_4_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.4 general compare match F */
    if (1UL == bCM_TMR6_4->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMFF) && (0UL != (VSSEL134 & BIT_MASK_21))) {
            TMR6_4_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.4 overflow*/
    if (1UL == bCM_TMR6_4->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_4->STFLR_b.OVFF) && (0UL != (VSSEL134 & BIT_MASK_22))) {
            TMR6_4_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.4 underflow*/
    if (1UL == bCM_TMR6_4->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_4->STFLR_b.UDFF) && (0UL != (VSSEL134 & BIT_MASK_23))) {
            TMR6_4_GUdf_IrqHandler();
        }
    }
    /* Timer6 Unit.4 dead time */
    if (1UL == bCM_TMR6_4->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_4->STFLR_b.DTEF) && (0UL != (VSSEL134 & BIT_MASK_24))) {
            TMR6_4_Gdte_IrqHandler();
        }
    }
    /* Timer6 Unit.4 specified up compare match A*/
    if (1UL == bCM_TMR6_4->ICONR_b.INTENSAU) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMSAUF) && (0UL != (VSSEL134 & BIT_MASK_27))) {
            TMR6_4_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Unit.4 specified down compare match A*/
    if (1UL == bCM_TMR6_4->ICONR_b.INTENSAD) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMSADF) && (0UL != (VSSEL134 & BIT_MASK_27))) {
            TMR6_4_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Unit.4 specified up compare match B*/
    if (1UL == bCM_TMR6_4->ICONR_b.INTENSBU) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMSBUF) && (0UL != (VSSEL134 & BIT_MASK_28))) {
            TMR6_4_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Unit.4 specified down compare match B*/
    if (1UL == bCM_TMR6_4->ICONR_b.INTENSBD) {
        if ((1UL == bCM_TMR6_4->STFLR_b.CMSBDF) && (0UL != (VSSEL134 & BIT_MASK_28))) {
            TMR6_4_SCmpDownB_IrqHandler();
        }
    }

    /* Arm Errata 838869: Cortex-M4, Cortex-M4F */
    __DSB();
}

/**
 * @brief  Interrupt No.135 share IRQ handler
 * @param  None
 * @retval None
 */
void IRQ135_Handler(void)
{
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;
    const uint32_t VSSEL135 = CM_INTC->VSSEL135;

    /* Timer6 Unit.5 general compare match A */
    if (1UL == bCM_TMR6_5->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMAF) && (0UL != (VSSEL135 & BIT_MASK_00))) {
            TMR6_5_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.5 general compare match B */
    if (1UL == bCM_TMR6_5->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMBF) && (0UL != (VSSEL135 & BIT_MASK_01))) {
            TMR6_5_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.5 general compare match C */
    if (1UL == bCM_TMR6_5->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMCF) && (0UL != (VSSEL135 & BIT_MASK_02))) {
            TMR6_5_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.5 general compare match D */
    if (1UL == bCM_TMR6_5->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMDF) && (0UL != (VSSEL135 & BIT_MASK_03))) {
            TMR6_5_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.5 general compare match E */
    if (1UL == bCM_TMR6_5->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMEF) && (0UL != (VSSEL135 & BIT_MASK_04))) {
            TMR6_5_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.5 general compare match F */
    if (1UL == bCM_TMR6_5->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMFF) && (0UL != (VSSEL135 & BIT_MASK_05))) {
            TMR6_5_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.5 overflow*/
    if (1UL == bCM_TMR6_5->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_5->STFLR_b.OVFF) && (0UL != (VSSEL135 & BIT_MASK_06))) {
            TMR6_5_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.5 underflow*/
    if (1UL == bCM_TMR6_5->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_5->STFLR_b.UDFF) && (0UL != (VSSEL135 & BIT_MASK_07))) {
            TMR6_5_GUdf_IrqHandler();
        }
    }
    /* Timer6 Unit.5 dead time */
    if (1UL == bCM_TMR6_5->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_5->STFLR_b.DTEF) && (0UL != (VSSEL135 & BIT_MASK_08))) {
            TMR6_5_Gdte_IrqHandler();
        }
    }
    /* Timer6 Unit.5 specified up compare match A*/
    if (1UL == bCM_TMR6_5->ICONR_b.INTENSAU) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMSAUF) && (0UL != (VSSEL135 & BIT_MASK_11))) {
            TMR6_5_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Unit.5 specified down compare match A*/
    if (1UL == bCM_TMR6_5->ICONR_b.INTENSAD) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMSADF) && (0UL != (VSSEL135 & BIT_MASK_11))) {
            TMR6_5_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Unit.5 specified up compare match B*/
    if (1UL == bCM_TMR6_5->ICONR_b.INTENSBU) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMSBUF) && (0UL != (VSSEL135 & BIT_MASK_12))) {
            TMR6_5_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Unit.5 specified down compare match B*/
    if (1UL == bCM_TMR6_5->ICONR_b.INTENSBD) {
        if ((1UL == bCM_TMR6_5->STFLR_b.CMSBDF) && (0UL != (VSSEL135 & BIT_MASK_12))) {
            TMR6_5_SCmpDownB_IrqHandler();
        }
    }
    /* TimerA Unit.1 overflow */
    if (1UL == bCM_TMRA_1->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_1->BCSTRH_b.OVFF) && (0UL != (VSSEL135 & BIT_MASK_13))) {
            TMRA_1_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.1 underflow */
    if (1UL == bCM_TMRA_1->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_1->BCSTRH_b.UDFF) && (0UL != (VSSEL135 & BIT_MASK_14))) {
            TMRA_1_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_1->ICONR;
    u32Tmp2 = CM_TMRA_1->STFLR;
    /* TimerA Unit.1 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL135 & BIT_MASK_15))) {
        TMRA_1_Cmp_IrqHandler();
    }
    /* Timer6 Unit.6 general compare match A */
    if (1UL == bCM_TMR6_6->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMAF) && (0UL != (VSSEL135 & BIT_MASK_16))) {
            TMR6_6_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.6 general compare match B */
    if (1UL == bCM_TMR6_6->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMBF) && (0UL != (VSSEL135 & BIT_MASK_17))) {
            TMR6_6_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.6 general compare match C */
    if (1UL == bCM_TMR6_6->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMCF) && (0UL != (VSSEL135 & BIT_MASK_18))) {
            TMR6_6_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.6 general compare match D */
    if (1UL == bCM_TMR6_6->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMDF) && (0UL != (VSSEL135 & BIT_MASK_19))) {
            TMR6_6_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.6 general compare match E */
    if (1UL == bCM_TMR6_6->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMEF) && (0UL != (VSSEL135 & BIT_MASK_20))) {
            TMR6_6_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.6 general compare match F */
    if (1UL == bCM_TMR6_6->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMFF) && (0UL != (VSSEL135 & BIT_MASK_21))) {
            TMR6_6_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.6 overflow*/
    if (1UL == bCM_TMR6_6->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_6->STFLR_b.OVFF) && (0UL != (VSSEL135 & BIT_MASK_22))) {
            TMR6_6_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.6 underflow*/
    if (1UL == bCM_TMR6_6->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_6->STFLR_b.UDFF) && (0UL != (VSSEL135 & BIT_MASK_23))) {
            TMR6_6_GUdf_IrqHandler();
        }
    }
    /* Timer6 Unit.6 dead time */
    if (1UL == bCM_TMR6_6->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_6->STFLR_b.DTEF) && (0UL != (VSSEL135 & BIT_MASK_24))) {
            TMR6_6_Gdte_IrqHandler();
        }
    }
    /* Timer6 Unit.6 specified up compare match A*/
    if (1UL == bCM_TMR6_6->ICONR_b.INTENSAU) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMSAUF) && (0UL != (VSSEL135 & BIT_MASK_27))) {
            TMR6_6_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Unit.6 specified down compare match A*/
    if (1UL == bCM_TMR6_6->ICONR_b.INTENSAD) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMSADF) && (0UL != (VSSEL135 & BIT_MASK_27))) {
            TMR6_6_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Unit.6 specified up compare match B*/
    if (1UL == bCM_TMR6_6->ICONR_b.INTENSBU) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMSBUF) && (0UL != (VSSEL135 & BIT_MASK_28))) {
            TMR6_6_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Unit.6 specified down compare match B*/
    if (1UL == bCM_TMR6_6->ICONR_b.INTENSBD) {
        if ((1UL == bCM_TMR6_6->STFLR_b.CMSBDF) && (0UL != (VSSEL135 & BIT_MASK_28))) {
            TMR6_6_SCmpDownB_IrqHandler();
        }
    }
    /* TimerA Unit.2 overflow */
    if (1UL == bCM_TMRA_2->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_2->BCSTRH_b.OVFF) && (0UL != (VSSEL135 & BIT_MASK_29))) {
            TMRA_2_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.2 underflow */
    if (1UL == bCM_TMRA_2->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_2->BCSTRH_b.UDFF) && (0UL != (VSSEL135 & BIT_MASK_30))) {
            TMRA_2_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_2->ICONR;
    u32Tmp2 = CM_TMRA_2->STFLR;
    /* TimerA Unit.2 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL135 & BIT_MASK_31))) {
        TMRA_2_Cmp_IrqHandler();
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

    /* Timer6 Unit.7 general compare match A */
    if (1UL == bCM_TMR6_7->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMAF) && (0UL != (VSSEL136 & BIT_MASK_00))) {
            TMR6_7_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.7 general compare match B */
    if (1UL == bCM_TMR6_7->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMBF) && (0UL != (VSSEL136 & BIT_MASK_01))) {
            TMR6_7_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.7 general compare match C */
    if (1UL == bCM_TMR6_7->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMCF) && (0UL != (VSSEL136 & BIT_MASK_02))) {
            TMR6_7_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.7 general compare match D */
    if (1UL == bCM_TMR6_7->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMDF) && (0UL != (VSSEL136 & BIT_MASK_03))) {
            TMR6_7_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.7 general compare match E */
    if (1UL == bCM_TMR6_7->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMEF) && (0UL != (VSSEL136 & BIT_MASK_04))) {
            TMR6_7_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.7 general compare match F */
    if (1UL == bCM_TMR6_7->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMFF) && (0UL != (VSSEL136 & BIT_MASK_05))) {
            TMR6_7_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.7 overflow*/
    if (1UL == bCM_TMR6_7->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_7->STFLR_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_06))) {
            TMR6_7_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.7 underflow*/
    if (1UL == bCM_TMR6_7->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_7->STFLR_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_07))) {
            TMR6_7_GUdf_IrqHandler();
        }
    }
    /* Timer6 Unit.7 dead time */
    if (1UL == bCM_TMR6_7->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_7->STFLR_b.DTEF) && (0UL != (VSSEL136 & BIT_MASK_08))) {
            TMR6_7_Gdte_IrqHandler();
        }
    }
    /* Timer6 Unit.7 specified up compare match A*/
    if (1UL == bCM_TMR6_7->ICONR_b.INTENSAU) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMSAUF) && (0UL != (VSSEL136 & BIT_MASK_11))) {
            TMR6_7_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Unit.7 specified down compare match A*/
    if (1UL == bCM_TMR6_7->ICONR_b.INTENSAD) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMSADF) && (0UL != (VSSEL136 & BIT_MASK_11))) {
            TMR6_7_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Unit.7 specified up compare match B*/
    if (1UL == bCM_TMR6_7->ICONR_b.INTENSBU) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMSBUF) && (0UL != (VSSEL136 & BIT_MASK_12))) {
            TMR6_7_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Unit.7 specified down compare match B*/
    if (1UL == bCM_TMR6_7->ICONR_b.INTENSBD) {
        if ((1UL == bCM_TMR6_7->STFLR_b.CMSBDF) && (0UL != (VSSEL136 & BIT_MASK_12))) {
            TMR6_7_SCmpDownB_IrqHandler();
        }
    }
    /* TimerA Unit.3 overflow */
    if (1UL == bCM_TMRA_3->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_3->BCSTRH_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_13))) {
            TMRA_3_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.3 underflow */
    if (1UL == bCM_TMRA_3->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_3->BCSTRH_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_14))) {
            TMRA_3_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_3->ICONR;
    u32Tmp2 = CM_TMRA_3->STFLR;
    /* TimerA Unit.3 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL136 & BIT_MASK_15))) {
        TMRA_3_Cmp_IrqHandler();
    }
    /* Timer6 Unit.8 general compare match A */
    if (1UL == bCM_TMR6_8->ICONR_b.INTENA) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMAF) && (0UL != (VSSEL136 & BIT_MASK_16))) {
            TMR6_8_GCmpA_IrqHandler();
        }
    }
    /* Timer6 Unit.8 general compare match B */
    if (1UL == bCM_TMR6_8->ICONR_b.INTENB) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMBF) && (0UL != (VSSEL136 & BIT_MASK_17))) {
            TMR6_8_GCmpB_IrqHandler();
        }
    }
    /* Timer6 Unit.8 general compare match C */
    if (1UL == bCM_TMR6_8->ICONR_b.INTENC) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMCF) && (0UL != (VSSEL136 & BIT_MASK_18))) {
            TMR6_8_GCmpC_IrqHandler();
        }
    }
    /* Timer6 Unit.8 general compare match D */
    if (1UL == bCM_TMR6_8->ICONR_b.INTEND) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMDF) && (0UL != (VSSEL136 & BIT_MASK_19))) {
            TMR6_8_GCmpD_IrqHandler();
        }
    }
    /* Timer6 Unit.8 general compare match E */
    if (1UL == bCM_TMR6_8->ICONR_b.INTENE) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMEF) && (0UL != (VSSEL136 & BIT_MASK_20))) {
            TMR6_8_GCmpE_IrqHandler();
        }
    }
    /* Timer6 Unit.8 general compare match F */
    if (1UL == bCM_TMR6_8->ICONR_b.INTENF) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMFF) && (0UL != (VSSEL136 & BIT_MASK_21))) {
            TMR6_8_GCmpF_IrqHandler();
        }
    }
    /* Timer6 Unit.8 overflow*/
    if (1UL == bCM_TMR6_8->ICONR_b.INTENOVF) {
        if ((1UL == bCM_TMR6_8->STFLR_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_22))) {
            TMR6_8_GOvf_IrqHandler();
        }
    }
    /* Timer6 Unit.8 underflow*/
    if (1UL == bCM_TMR6_8->ICONR_b.INTENUDF) {
        if ((1UL == bCM_TMR6_8->STFLR_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_23))) {
            TMR6_8_GUdf_IrqHandler();
        }
    }
    /* Timer6 Unit.8 dead time */
    if (1UL == bCM_TMR6_8->ICONR_b.INTENDTE) {
        if ((1UL == bCM_TMR6_8->STFLR_b.DTEF) && (0UL != (VSSEL136 & BIT_MASK_24))) {
            TMR6_8_Gdte_IrqHandler();
        }
    }
    /* Timer6 Unit.8 specified up compare match A*/
    if (1UL == bCM_TMR6_8->ICONR_b.INTENSAU) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMSAUF) && (0UL != (VSSEL136 & BIT_MASK_27))) {
            TMR6_8_SCmpUpA_IrqHandler();
        }
    }
    /* Timer6 Unit.8 specified down compare match A*/
    if (1UL == bCM_TMR6_8->ICONR_b.INTENSAD) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMSADF) && (0UL != (VSSEL136 & BIT_MASK_27))) {
            TMR6_8_SCmpDownA_IrqHandler();
        }
    }
    /* Timer6 Unit.8 specified up compare match B*/
    if (1UL == bCM_TMR6_8->ICONR_b.INTENSBU) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMSBUF) && (0UL != (VSSEL136 & BIT_MASK_28))) {
            TMR6_8_SCmpUpB_IrqHandler();
        }
    }
    /* Timer6 Unit.8 specified down compare match B*/
    if (1UL == bCM_TMR6_8->ICONR_b.INTENSBD) {
        if ((1UL == bCM_TMR6_8->STFLR_b.CMSBDF) && (0UL != (VSSEL136 & BIT_MASK_28))) {
            TMR6_8_SCmpDownB_IrqHandler();
        }
    }
    /* TimerA Unit.4 overflow */
    if (1UL == bCM_TMRA_4->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_4->BCSTRH_b.OVFF) && (0UL != (VSSEL136 & BIT_MASK_29))) {
            TMRA_4_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.4 underflow */
    if (1UL == bCM_TMRA_4->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_4->BCSTRH_b.UDFF) && (0UL != (VSSEL136 & BIT_MASK_30))) {
            TMRA_4_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_4->ICONR;
    u32Tmp2 = CM_TMRA_4->STFLR;
    /* TimerA Unit.4 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL136 & BIT_MASK_31))) {
        TMRA_4_Cmp_IrqHandler();
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
    const uint32_t VSSEL137 = CM_INTC->VSSEL137;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* EMB0 */
    u32Tmp1 = CM_EMB0->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = CM_EMB0->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                               BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_00))) {
        EMB_GR0_IrqHandler();
    }
    /* EMB1 */
    u32Tmp1 = CM_EMB1->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = CM_EMB1->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                               BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_01))) {
        EMB_GR1_IrqHandler();
    }
    /* EMB2 */
    u32Tmp1 = CM_EMB2->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = CM_EMB2->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                               BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_02))) {
        EMB_GR2_IrqHandler();
    }
    /* EMB3 */
    u32Tmp1 = CM_EMB3->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = CM_EMB3->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                               BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_03))) {
        EMB_GR3_IrqHandler();
    }
    /* EMB4 */
    u32Tmp1 = CM_EMB4->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = CM_EMB4->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                               BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_04))) {
        EMB_GR4_IrqHandler();
    }
    /* EMB5 */
    u32Tmp1 = CM_EMB5->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = CM_EMB5->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                               BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_05))) {
        EMB_GR5_IrqHandler();
    }
    /* EMB6 */
    u32Tmp1 = CM_EMB6->INTEN & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                                BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    u32Tmp2 = CM_EMB6->STAT & (BIT_MASK_01 | BIT_MASK_02 | BIT_MASK_03 |   \
                               BIT_MASK_08 | BIT_MASK_09 | BIT_MASK_10 | BIT_MASK_11);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL137 & BIT_MASK_06))) {
        EMB_GR6_IrqHandler();
    }
    /* USB HS EP1 out */

    /* USB HS EP1 in */

    /* USB HS global */

    /* USB HS wakeup */

    if (1UL == bCM_USART1->CR1_b.RIE) {
        /* USART Ch.1 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART1->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL137 & BIT_MASK_12))) {
            USART1_RxError_IrqHandler();
        }
        /* USART Ch.1 Rx end */
        if ((1UL == bCM_USART1->SR_b.RXNE) && (0UL != (VSSEL137 & BIT_MASK_13))) {
            USART1_RxFull_IrqHandler();
        }
    }
    /* USART Ch.1 Tx buffer empty */
    if (1UL == bCM_USART1->CR1_b.TXEIE) {
        if ((1UL == bCM_USART1->SR_b.TXE) && (0UL != (VSSEL137 & BIT_MASK_14))) {
            USART1_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.1 Tx end */
    if (1UL == bCM_USART1->CR1_b.TCIE) {
        if ((1UL == bCM_USART1->SR_b.TC) && (0UL != (VSSEL137 & BIT_MASK_15))) {
            USART1_TxComplete_IrqHandler();
        }
    }
    /* USART Ch.1 Tx timeout */
    if (1UL == bCM_USART1->CR1_b.RTOIE) {
        if ((1UL == bCM_USART1->SR_b.RTOF) && (0UL != (VSSEL137 & BIT_MASK_16))) {
            USART1_RxTO_IrqHandler();
        }
    }
    if (1UL == bCM_USART2->CR1_b.RIE) {
        /* USART Ch.2 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART2->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL137 & BIT_MASK_17))) {
            USART2_RxError_IrqHandler();
        }
        /* USART Ch.2 Rx end */
        if ((1UL == bCM_USART2->SR_b.RXNE) && (0UL != (VSSEL137 & BIT_MASK_18))) {
            USART2_RxFull_IrqHandler();
        }
    }
    /* USART Ch.2 Tx buffer empty */
    if (1UL == bCM_USART2->CR1_b.TXEIE) {
        if ((1UL == bCM_USART2->SR_b.TXE) && (0UL != (VSSEL137 & BIT_MASK_19))) {
            USART2_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.2 Tx end */
    if (1UL == bCM_USART2->CR1_b.TCIE) {
        if ((1UL == bCM_USART2->SR_b.TC) && (0UL != (VSSEL137 & BIT_MASK_20))) {
            USART2_TxComplete_IrqHandler();
        }
    }
    /* USART Ch.2 Tx timeout */
    if (1UL == bCM_USART2->CR1_b.RTOIE) {
        if ((1UL == bCM_USART2->SR_b.RTOF) && (0UL != (VSSEL137 & BIT_MASK_21))) {
            USART2_RxTO_IrqHandler();
        }
    }
    /* SPI Ch.1 Rx end */
    if (1UL == bCM_SPI1->CR1_b.RXIE) {
        if ((1UL == bCM_SPI1->SR_b.RDFF) && (0UL != (VSSEL137 & BIT_MASK_22))) {
            SPI1_RxFull_IrqHandler();
        }
    }
    /* SPI Ch.1 Tx buffer empty */
    if (1UL == bCM_SPI1->CR1_b.TXIE) {
        if ((1UL == bCM_SPI1->SR_b.TDEF) && (0UL != (VSSEL137 & BIT_MASK_23))) {
            SPI1_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.1 Bus idle */
    if (1UL == bCM_SPI1->CR1_b.IDIE) {
        if ((0UL == bCM_SPI1->SR_b.IDLNF) && (0UL != (VSSEL137 & BIT_MASK_24))) {
            SPI1_Idle_IrqHandler();
        }
    }
    /* SPI Ch.1 parity/overflow/underflow/mode error */
    if (1UL == bCM_SPI1->CR1_b.EIE) {
        u32Tmp1 = CM_SPI1->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL137 & BIT_MASK_25))) {
            SPI1_Error_IrqHandler();
        }
    }
    /* SPI Ch.2 Rx end */
    if (1UL == bCM_SPI2->CR1_b.RXIE) {
        if ((1UL == bCM_SPI2->SR_b.RDFF) && (0UL != (VSSEL137 & BIT_MASK_27))) {
            SPI2_RxFull_IrqHandler();
        }
    }
    /* SPI Ch.2 Tx buffer empty */
    if (1UL == bCM_SPI2->CR1_b.TXIE) {
        if ((1UL == bCM_SPI2->SR_b.TDEF) && (0UL != (VSSEL137 & BIT_MASK_28))) {
            SPI2_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.2 Bus idle */
    if (1UL == bCM_SPI2->CR1_b.IDIE) {
        if ((0UL == bCM_SPI2->SR_b.IDLNF) && (0UL != (VSSEL137 & BIT_MASK_29))) {
            SPI2_Idle_IrqHandler();
        }
    }
    /* SPI Ch.2 parity/overflow/underflow/mode error */
    if (1UL == bCM_SPI2->CR1_b.EIE) {
        u32Tmp1 = CM_SPI2->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL137 & BIT_MASK_30))) {
            SPI2_Error_IrqHandler();
        }
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
    uint32_t u32Tmp2;
    uint8_t RTIF;
    uint8_t RTIE;
    uint8_t ERRINT;
    uint8_t TTCFG;

    /* TimerA Unit.5 overflow */
    if (1UL == bCM_TMRA_5->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_5->BCSTRH_b.OVFF) && (0UL != (VSSEL138 & BIT_MASK_00))) {
            TMRA_5_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.5 underflow */
    if (1UL == bCM_TMRA_5->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_5->BCSTRH_b.UDFF) && (0UL != (VSSEL138 & BIT_MASK_01))) {
            TMRA_5_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_5->ICONR;
    u32Tmp2 = CM_TMRA_5->STFLR;
    /* TimerA Unit.5 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL138 & BIT_MASK_02))) {
        TMRA_5_Cmp_IrqHandler();
    }
    /* TimerA Unit.6 overflow */
    if (1UL == bCM_TMRA_6->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_6->BCSTRH_b.OVFF) && (0UL != (VSSEL138 & BIT_MASK_03))) {
            TMRA_6_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.6 underflow */
    if (1UL == bCM_TMRA_6->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_6->BCSTRH_b.UDFF) && (0UL != (VSSEL138 & BIT_MASK_04))) {
            TMRA_6_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_6->ICONR;
    u32Tmp2 = CM_TMRA_6->STFLR;
    /* TimerA Unit.6 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL138 & BIT_MASK_05))) {
        TMRA_6_Cmp_IrqHandler();
    }
    /* TimerA Unit.7 overflow */
    if (1UL == bCM_TMRA_7->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_7->BCSTRH_b.OVFF) && (0UL != (VSSEL138 & BIT_MASK_06))) {
            TMRA_7_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.7 underflow */
    if (1UL == bCM_TMRA_7->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_7->BCSTRH_b.UDFF) && (0UL != (VSSEL138 & BIT_MASK_07))) {
            TMRA_7_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_7->ICONR;
    u32Tmp2 = CM_TMRA_7->STFLR;
    /* TimerA Unit.7 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL138 & BIT_MASK_08))) {
        TMRA_7_Cmp_IrqHandler();
    }
    /* TimerA Unit.8 overflow */
    if (1UL == bCM_TMRA_8->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_8->BCSTRH_b.OVFF) && (0UL != (VSSEL138 & BIT_MASK_09))) {
            TMRA_8_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.8 underflow */
    if (1UL == bCM_TMRA_8->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_8->BCSTRH_b.UDFF) && (0UL != (VSSEL138 & BIT_MASK_10))) {
            TMRA_8_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_8->ICONR;
    u32Tmp2 = CM_TMRA_8->STFLR;
    /* TimerA Unit.8 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL138 & BIT_MASK_11))) {
        TMRA_8_Cmp_IrqHandler();
    }
    if (1UL == bCM_USART3->CR1_b.RIE) {
        /* USART Ch.3 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART3->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL138 & BIT_MASK_12))) {
            USART3_RxError_IrqHandler();
        }
        /* USART Ch.3 Rx end */
        if ((1UL == bCM_USART3->SR_b.RXNE) && (0UL != (VSSEL138 & BIT_MASK_13))) {
            USART3_RxFull_IrqHandler();
        }
    }
    /* USART Ch.3 Tx buffer empty */
    if (1UL == bCM_USART3->CR1_b.TXEIE) {
        if ((1UL == bCM_USART3->SR_b.TXE) && (0UL != (VSSEL138 & BIT_MASK_14))) {
            USART3_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.3 Tx end */
    if (1UL == bCM_USART3->CR1_b.TCIE) {
        if ((1UL == bCM_USART3->SR_b.TC) && (0UL != (VSSEL138 & BIT_MASK_15))) {
            USART3_TxComplete_IrqHandler();
        }
    }
    if (1UL == bCM_USART4->CR1_b.RIE) {
        /* USART Ch.4 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART4->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL138 & BIT_MASK_16))) {
            USART4_RxError_IrqHandler();
        }
        /* USART Ch.4 Rx end */
        if ((1UL == bCM_USART4->SR_b.RXNE) && (0UL != (VSSEL138 & BIT_MASK_17))) {
            USART4_RxFull_IrqHandler();
        }
    }
    /* USART Ch.4 Tx buffer empty */
    if (1UL == bCM_USART4->CR1_b.TXEIE) {
        if ((1UL == bCM_USART4->SR_b.TXE) && (0UL != (VSSEL138 & BIT_MASK_18))) {
            USART4_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.4 Tx end */
    if (1UL == bCM_USART4->CR1_b.TCIE) {
        if ((1UL == bCM_USART4->SR_b.TC) && (0UL != (VSSEL138 & BIT_MASK_19))) {
            USART4_TxComplete_IrqHandler();
        }
    }
    /* CAN Ch.1 */
    if (0UL != (VSSEL138 & BIT_MASK_20)) {
        RTIF = CM_CAN1->RTIF;
        RTIE = CM_CAN1->RTIE;
        ERRINT = CM_CAN1->ERRINT;
        TTCFG = CM_CAN1->TTCFG;
        if ((0U != (TTCFG & CAN_TTCFG_TEIF))            ||                          \
            (0U != (RTIF & CAN_RTIF_AIF))               ||                          \
            (0U != (RTIF & RTIE & 0xFEU))               ||                          \
            ((0U != (ERRINT & CAN_ERRINT_BEIE))         &&                          \
             (0U != (ERRINT & CAN_ERRINT_BEIF)))        ||                          \
            ((0U != (ERRINT & CAN_ERRINT_ALIE))         &&                          \
             (0U != (ERRINT & CAN_ERRINT_ALIF)))        ||                          \
            ((0U != (ERRINT & CAN_ERRINT_EPIE))         &&                          \
             (0U != (ERRINT & CAN_ERRINT_EPIF)))        ||                          \
            ((0U != (TTCFG & CAN_TTCFG_TTIE))           &&                          \
             (0U != (TTCFG & CAN_TTCFG_TTIF)))          ||                          \
            ((0U != (TTCFG & CAN_TTCFG_WTIE))           &&                          \
             (0U != (TTCFG & CAN_TTCFG_WTIF)))) {
            CAN1_IrqHandler();
        }
    }
    /* CAN Ch.2 */
    if (0UL != (VSSEL138 & BIT_MASK_21)) {
        RTIF = CM_CAN2->RTIF;
        RTIE = CM_CAN2->RTIE;
        ERRINT = CM_CAN2->ERRINT;
        TTCFG = CM_CAN2->TTCFG;
        if ((0U != (TTCFG & CAN_TTCFG_TEIF))            ||                          \
            (0U != (RTIF & CAN_RTIF_AIF))               ||                          \
            (0U != (RTIF & RTIE & 0xFEU))               ||                          \
            ((0U != (ERRINT & CAN_ERRINT_BEIE))         &&                          \
             (0U != (ERRINT & CAN_ERRINT_BEIF)))        ||                          \
            ((0U != (ERRINT & CAN_ERRINT_ALIE))         &&                          \
             (0U != (ERRINT & CAN_ERRINT_ALIF)))        ||                          \
            ((0U != (ERRINT & CAN_ERRINT_EPIE))         &&                          \
             (0U != (ERRINT & CAN_ERRINT_EPIF)))        ||                          \
            ((0U != (TTCFG & CAN_TTCFG_TTIE))           &&                          \
             (0U != (TTCFG & CAN_TTCFG_TTIF)))          ||                          \
            ((0U != (TTCFG & CAN_TTCFG_WTIE))           &&                          \
             (0U != (TTCFG & CAN_TTCFG_WTIF)))) {
            CAN2_IrqHandler();
        }
    }
    /* SPI Ch.3 Rx end */
    if (1UL == bCM_SPI3->CR1_b.RXIE) {
        if ((1UL == bCM_SPI3->SR_b.RDFF) && (0UL != (VSSEL138 & BIT_MASK_22))) {
            SPI3_RxFull_IrqHandler();
        }
    }
    /* SPI Ch.3 Tx buffer empty */
    if (1UL == bCM_SPI3->CR1_b.TXIE) {
        if ((1UL == bCM_SPI3->SR_b.TDEF) && (0UL != (VSSEL138 & BIT_MASK_23))) {
            SPI3_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.3 Bus idle */
    if (1UL == bCM_SPI3->CR1_b.IDIE) {
        if ((0UL == bCM_SPI3->SR_b.IDLNF) && (0UL != (VSSEL138 & BIT_MASK_24))) {
            SPI3_Idle_IrqHandler();
        }
    }
    /* SPI Ch.3 parity/overflow/underflow/mode error */
    if (1UL == bCM_SPI3->CR1_b.EIE) {
        u32Tmp1 = CM_SPI3->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL138 & BIT_MASK_25))) {
            SPI3_Error_IrqHandler();
        }
    }
    /* SPI Ch.4 Rx end */
    if (1UL == bCM_SPI4->CR1_b.RXIE) {
        if ((1UL == bCM_SPI4->SR_b.RDFF) && (0UL != (VSSEL138 & BIT_MASK_27))) {
            SPI4_RxFull_IrqHandler();
        }
    }
    /* SPI Ch.4 Tx buffer empty */
    if (1UL == bCM_SPI4->CR1_b.TXIE) {
        if ((1UL == bCM_SPI4->SR_b.TDEF) && (0UL != (VSSEL138 & BIT_MASK_28))) {
            SPI4_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.4 Bus idle */
    if (1UL == bCM_SPI4->CR1_b.IDIE) {
        if ((0UL == bCM_SPI4->SR_b.IDLNF) && (0UL != (VSSEL138 & BIT_MASK_29))) {
            SPI4_Idle_IrqHandler();
        }
    }
    /* SPI Ch.4 parity/overflow/underflow/mode error */
    if (1UL == bCM_SPI4->CR1_b.EIE) {
        u32Tmp1 = CM_SPI4->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL138 & BIT_MASK_30))) {
            SPI4_Error_IrqHandler();
        }
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
    const uint32_t VSSEL139 = CM_INTC->VSSEL139;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* TimerA Unit.9 overflow */
    if (1UL == bCM_TMRA_9->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_9->BCSTRH_b.OVFF) && (0UL != (VSSEL139 & BIT_MASK_00))) {
            TMRA_9_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.9 underflow */
    if (1UL == bCM_TMRA_9->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_9->BCSTRH_b.UDFF) && (0UL != (VSSEL139 & BIT_MASK_01))) {
            TMRA_9_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_9->ICONR;
    u32Tmp2 = CM_TMRA_9->STFLR;
    /* TimerA Unit.9 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL139 & BIT_MASK_02))) {
        TMRA_9_Cmp_IrqHandler();
    }
    /* TimerA Unit.10 overflow */
    if (1UL == bCM_TMRA_10->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_10->BCSTRH_b.OVFF) && (0UL != (VSSEL139 & BIT_MASK_03))) {
            TMRA_10_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.10 underflow */
    if (1UL == bCM_TMRA_10->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_10->BCSTRH_b.UDFF) && (0UL != (VSSEL139 & BIT_MASK_04))) {
            TMRA_10_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_10->ICONR;
    u32Tmp2 = CM_TMRA_10->STFLR;
    /* TimerA Unit.10 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL139 & BIT_MASK_05))) {
        TMRA_10_Cmp_IrqHandler();
    }
    /* TimerA Unit.11 overflow */
    if (1UL == bCM_TMRA_11->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_11->BCSTRH_b.OVFF) && (0UL != (VSSEL139 & BIT_MASK_06))) {
            TMRA_11_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.11 underflow */
    if (1UL == bCM_TMRA_11->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_11->BCSTRH_b.UDFF) && (0UL != (VSSEL139 & BIT_MASK_07))) {
            TMRA_11_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_11->ICONR;
    u32Tmp2 = CM_TMRA_11->STFLR;
    /* TimerA Unit.11 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL139 & BIT_MASK_08))) {
        TMRA_11_Cmp_IrqHandler();
    }
    /* TimerA Unit.12 overflow */
    if (1UL == bCM_TMRA_12->BCSTRH_b.ITENOVF) {
        if ((1UL == bCM_TMRA_12->BCSTRH_b.OVFF) && (0UL != (VSSEL139 & BIT_MASK_09))) {
            TMRA_12_Ovf_IrqHandler();
        }
    }
    /* TimerA Unit.12 underflow */
    if (1UL == bCM_TMRA_12->BCSTRH_b.ITENUDF) {
        if ((1UL == bCM_TMRA_12->BCSTRH_b.UDFF) && (0UL != (VSSEL139 & BIT_MASK_10))) {
            TMRA_12_Udf_IrqHandler();
        }
    }
    u32Tmp1 = CM_TMRA_12->ICONR;
    u32Tmp2 = CM_TMRA_12->STFLR;
    /* TimerA Unit.12 compare match */
    if ((0UL != (u32Tmp1 & u32Tmp2 & 0x0FUL)) && (0UL != (VSSEL139 & BIT_MASK_11))) {
        TMRA_12_Cmp_IrqHandler();
    }
    /* USART Ch.5 LIN bus break */
    if (1UL == bCM_USART5->CR2_b.LBDIE) {
        if ((1UL == bCM_USART5->SR_b.LBD) && (0UL != (VSSEL139 & BIT_MASK_12))) {
            USART5_LinBreakField_IrqHandler();
        }
    }
    /* USART Ch.5 LIN bus wakeup */
    if (1UL == bCM_USART5->CR2_b.WKUPE) {
        if ((1UL == bCM_USART5->SR_b.WKUP) && (0UL != (VSSEL139 & BIT_MASK_12))) {
            USART5_LinWakeup_IrqHandler();
        }
    }
    if (1UL == bCM_USART5->CR1_b.RIE) {
        /* USART Ch.5 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART5->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL139 & BIT_MASK_13))) {
            USART5_RxError_IrqHandler();
        }
        /* USART Ch.5 Rx end */
        if ((1UL == bCM_USART5->SR_b.RXNE) && (0UL != (VSSEL139 & BIT_MASK_14))) {
            USART5_RxFull_IrqHandler();
        }
    }
    /* USART Ch.5 Tx buffer empty */
    if (1UL == bCM_USART5->CR1_b.TXEIE) {
        if ((1UL == bCM_USART5->SR_b.TXE) && (0UL != (VSSEL139 & BIT_MASK_15))) {
            USART5_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.5 Tx end */
    if (1UL == bCM_USART5->CR1_b.TCIE) {
        if ((1UL == bCM_USART5->SR_b.TC) && (0UL != (VSSEL139 & BIT_MASK_16))) {
            USART5_TxComplete_IrqHandler();
        }
    }
    if (1UL == bCM_USART6->CR1_b.RIE) {
        /* USART Ch.6 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART6->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL139 & BIT_MASK_17))) {
            USART6_RxError_IrqHandler();
        }
        /* USART Ch.6 Rx end */
        if ((1UL == bCM_USART6->SR_b.RXNE) && (0UL != (VSSEL139 & BIT_MASK_18))) {
            USART6_RxFull_IrqHandler();
        }
    }
    /* USART Ch.6 Tx buffer empty */
    if (1UL == bCM_USART6->CR1_b.TXEIE) {
        if ((1UL == bCM_USART6->SR_b.TXE) && (0UL != (VSSEL139 & BIT_MASK_19))) {
            USART6_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.6 Tx end */
    if (1UL == bCM_USART6->CR1_b.TCIE) {
        if ((1UL == bCM_USART6->SR_b.TC) && (0UL != (VSSEL139 & BIT_MASK_20))) {
            USART6_TxComplete_IrqHandler();
        }
    }
    /* USART Ch.6 Tx timeout */
    if (1UL == bCM_USART6->CR1_b.RTOIE) {
        if ((1UL == bCM_USART6->SR_b.RTOF) && (0UL != (VSSEL139 & BIT_MASK_21))) {
            USART6_RxTO_IrqHandler();
        }
    }
    /* SPI Ch.5 Rx end */
    if (1UL == bCM_SPI5->CR1_b.RXIE) {
        if ((1UL == bCM_SPI5->SR_b.RDFF) && (0UL != (VSSEL139 & BIT_MASK_22))) {
            SPI5_RxFull_IrqHandler();
        }
    }
    /* SPI Ch.5 Tx buffer empty */
    if (1UL == bCM_SPI5->CR1_b.TXIE) {
        if ((1UL == bCM_SPI5->SR_b.TDEF) && (0UL != (VSSEL139 & BIT_MASK_23))) {
            SPI5_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.5 Bus idle */
    if (1UL == bCM_SPI5->CR1_b.IDIE) {
        if ((0UL == bCM_SPI5->SR_b.IDLNF) && (0UL != (VSSEL139 & BIT_MASK_24))) {
            SPI5_Idle_IrqHandler();
        }
    }
    /* SPI Ch.5 parity/overflow/underflow/mode error */
    if (1UL == bCM_SPI5->CR1_b.EIE) {
        u32Tmp1 = CM_SPI5->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL139 & BIT_MASK_25))) {
            SPI5_Error_IrqHandler();
        }
    }
    /* SPI Ch.6 Rx end */
    if (1UL == bCM_SPI6->CR1_b.RXIE) {
        if ((1UL == bCM_SPI6->SR_b.RDFF) && (0UL != (VSSEL139 & BIT_MASK_27))) {
            SPI6_RxFull_IrqHandler();
        }
    }
    /* SPI Ch.6 Tx buffer empty */
    if (1UL == bCM_SPI6->CR1_b.TXIE) {
        if ((1UL == bCM_SPI6->SR_b.TDEF) && (0UL != (VSSEL139 & BIT_MASK_28))) {
            SPI6_TxEmpty_IrqHandler();
        }
    }
    /* SPI Ch.6 Bus idle */
    if (1UL == bCM_SPI6->CR1_b.IDIE) {
        if ((0UL == bCM_SPI6->SR_b.IDLNF) && (0UL != (VSSEL139 & BIT_MASK_29))) {
            SPI6_Idle_IrqHandler();
        }
    }
    /* SPI Ch.6 parity/overflow/underflow/mode error */
    if (1UL == bCM_SPI6->CR1_b.EIE) {
        u32Tmp1 = CM_SPI6->SR & (SPI_SR_OVRERF | SPI_SR_MODFERF | SPI_SR_PERF | SPI_SR_UDRERF);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL139 & BIT_MASK_30))) {
            SPI6_Error_IrqHandler();
        }
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
    uint16_t NORINTST;
    uint16_t NORINTSGEN;
    uint16_t ERRINTSGEN;
    uint32_t MMC_REVSTSR;
    uint32_t MMC_TRSSTSR;
    uint32_t MMC_RITCTLR;
    uint32_t MMC_TITCTLR;
    uint32_t DMA_DMASTSR;
    uint32_t DMA_INTENAR;
    uint32_t PTP_INTE;
    uint32_t PMT_INTMASK;
    uint32_t PMT_INTSTSR;
    uint32_t PTP_INTMASK;
    uint32_t PTP_INTSTSR;

    /* I2S Ch.1 Tx */
    if (1UL == bCM_I2S1->CTRL_b.TXIE) {
        if ((1UL == bCM_I2S1->SR_b.TXBA) && (0UL != (VSSEL140 & BIT_MASK_00))) {
            I2S1_Tx_IrqHandler();
        }
    }
    /* I2S Ch.1 Rx */
    if (1UL == bCM_I2S1->CTRL_b.RXIE) {
        if ((1UL == bCM_I2S1->SR_b.RXBA) && (0UL != (VSSEL140 & BIT_MASK_01))) {
            I2S1_Rx_IrqHandler();
        }
    }
    /* I2S Ch.1 Error */
    if (1UL == bCM_I2S1->CTRL_b.EIE) {
        u32Tmp1 = CM_I2S1->ER & (I2S_ER_TXERR | I2S_ER_RXERR);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL140 & BIT_MASK_02))) {
            I2S1_Error_IrqHandler();
        }
    }
    /* I2S Ch.2 Tx */
    if (1UL == bCM_I2S2->CTRL_b.TXIE) {
        if ((1UL == bCM_I2S2->SR_b.TXBA) && (0UL != (VSSEL140 & BIT_MASK_03))) {
            I2S2_Tx_IrqHandler();
        }
    }
    /* I2S Ch.2 Rx */
    if (1UL == bCM_I2S2->CTRL_b.RXIE) {
        if ((1UL == bCM_I2S2->SR_b.RXBA) && (0UL != (VSSEL140 & BIT_MASK_04))) {
            I2S2_Rx_IrqHandler();
        }
    }
    /* I2S Ch.2 Error */
    if (1UL == bCM_I2S2->CTRL_b.EIE) {
        u32Tmp1 = CM_I2S2->ER & (I2S_ER_TXERR | I2S_ER_RXERR);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL140 & BIT_MASK_05))) {
            I2S2_Error_IrqHandler();
        }
    }
    if (1UL == bCM_USART7->CR1_b.RIE) {
        /* USART Ch.7 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART7->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL140 & BIT_MASK_06))) {
            USART7_RxError_IrqHandler();
        }
        /* USART Ch.7 Rx end */
        if ((1UL == bCM_USART7->SR_b.RXNE) && (0UL != (VSSEL140 & BIT_MASK_07))) {
            USART7_RxFull_IrqHandler();
        }
    }
    /* USART Ch.7 Tx buffer empty */
    if (1UL == bCM_USART7->CR1_b.TXEIE) {
        if ((1UL == bCM_USART7->SR_b.TXE) && (0UL != (VSSEL140 & BIT_MASK_08))) {
            USART7_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.7 Tx end */
    if (1UL == bCM_USART7->CR1_b.TCIE) {
        if ((1UL == bCM_USART7->SR_b.TC) && (0UL != (VSSEL140 & BIT_MASK_09))) {
            USART7_TxComplete_IrqHandler();
        }
    }
    /* USART Ch.7 Tx timeout */
    if (1UL == bCM_USART7->CR1_b.RTOIE) {
        if ((1UL == bCM_USART7->SR_b.RTOF) && (0UL != (VSSEL140 & BIT_MASK_10))) {
            USART7_RxTO_IrqHandler();
        }
    }
    if (1UL == bCM_USART8->CR1_b.RIE) {
        /* USART Ch.8 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART8->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL140 & BIT_MASK_11))) {
            USART8_RxError_IrqHandler();
        }
        /* USART Ch.8 Rx end */
        if ((1UL == bCM_USART8->SR_b.RXNE) && (0UL != (VSSEL140 & BIT_MASK_12))) {
            USART8_RxFull_IrqHandler();
        }
    }
    /* USART Ch.8 Tx buffer empty */
    if (1UL == bCM_USART8->CR1_b.TXEIE) {
        if ((1UL == bCM_USART8->SR_b.TXE) && (0UL != (VSSEL140 & BIT_MASK_13))) {
            USART8_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.8 Tx end */
    if (1UL == bCM_USART8->CR1_b.TCIE) {
        if ((1UL == bCM_USART8->SR_b.TC) && (0UL != (VSSEL140 & BIT_MASK_14))) {
            USART8_TxComplete_IrqHandler();
        }
    }
    /* USB FS global interrupt */
    if (1UL == bCM_USBFS->GAHBCFG_b.GINTMSK) {
        u32Tmp1 = CM_USBFS->GINTMSK & 0xF77CFCFBUL;
        u32Tmp2 = CM_USBFS->GINTSTS & 0xF77CFCFBUL;
        if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL140 & BIT_MASK_15))) {
            USBFS_Global_IrqHandler();
        }
    }
    /* SDIO unit 1 */
    if (0UL != (VSSEL140 & BIT_MASK_20)) {
        NORINTST = CM_SDIOC1->NORINTST & (SDIOC_NORINTST_CINT | SDIOC_NORINTST_CRM | SDIOC_NORINTST_CIST |  \
                                          SDIOC_NORINTST_BRR  | SDIOC_NORINTST_BWR | SDIOC_NORINTST_BGE  |  \
                                          SDIOC_NORINTST_TC   | SDIOC_NORINTST_CC);
        NORINTSGEN = CM_SDIOC1->NORINTSGEN & (SDIOC_NORINTSTEN_CINTEN | SDIOC_NORINTSTEN_CRMEN |    \
                                              SDIOC_NORINTSTEN_CISTEN | SDIOC_NORINTSTEN_BRREN |    \
                                              SDIOC_NORINTSTEN_BWREN  | SDIOC_NORINTSTEN_BGEEN |    \
                                              SDIOC_NORINTSTEN_TCEN   | SDIOC_NORINTSTEN_CCEN);
        ERRINTSGEN = CM_SDIOC1->ERRINTSGEN & (SDIOC_ERRINTSTEN_ACEEN | SDIOC_ERRINTSTEN_DEBEEN |    \
                                              SDIOC_ERRINTSTEN_DCEEN | SDIOC_ERRINTSTEN_DTOEEN |    \
                                              SDIOC_ERRINTSTEN_CIEEN | SDIOC_ERRINTSTEN_CEBEEN |    \
                                              SDIOC_ERRINTSTEN_CCEEN | SDIOC_ERRINTSTEN_CTOEEN);
        if (0U != (NORINTST & NORINTSGEN)) {
            SDIOC1_Normal_IrqHandler();
        }
        if ((1UL == bCM_SDIOC1->NORINTST_b.EI) && (0U != ERRINTSGEN)) {
            SDIOC1_Error_IrqHandler();
        }
    }
    /* SDIO unit 2 */
    if (0UL != (VSSEL140 & BIT_MASK_23)) {
        NORINTST = CM_SDIOC2->NORINTST & (SDIOC_NORINTST_CINT | SDIOC_NORINTST_CRM | SDIOC_NORINTST_CIST |  \
                                          SDIOC_NORINTST_BRR  | SDIOC_NORINTST_BWR | SDIOC_NORINTST_BGE  |  \
                                          SDIOC_NORINTST_TC   | SDIOC_NORINTST_CC);
        NORINTSGEN = CM_SDIOC2->NORINTSGEN & (SDIOC_NORINTSTEN_CINTEN | SDIOC_NORINTSTEN_CRMEN |    \
                                              SDIOC_NORINTSTEN_CISTEN | SDIOC_NORINTSTEN_BRREN |    \
                                              SDIOC_NORINTSTEN_BWREN  | SDIOC_NORINTSTEN_BGEEN |    \
                                              SDIOC_NORINTSTEN_TCEN   | SDIOC_NORINTSTEN_CCEN);
        ERRINTSGEN = CM_SDIOC2->ERRINTSGEN & (SDIOC_ERRINTSTEN_ACEEN | SDIOC_ERRINTSTEN_DEBEEN |    \
                                              SDIOC_ERRINTSTEN_DCEEN | SDIOC_ERRINTSTEN_DTOEEN |    \
                                              SDIOC_ERRINTSTEN_CIEEN | SDIOC_ERRINTSTEN_CEBEEN |    \
                                              SDIOC_ERRINTSTEN_CCEEN | SDIOC_ERRINTSTEN_CTOEEN);
        if (0U != (NORINTST & NORINTSGEN)) {
            SDIOC2_Normal_IrqHandler();
        }
        if ((1UL == bCM_SDIOC2->NORINTST_b.EI) && (0U != ERRINTSGEN)) {
            SDIOC2_Error_IrqHandler();
        }
    }
    /* Ethernet global */
    MMC_REVSTSR = CM_ETH->MMC_REVSTSR & (ETH_MMC_REVSTSR_RXOEIS | ETH_MMC_REVSTSR_RXLEIS |  \
                                         ETH_MMC_REVSTSR_RXUGIS | ETH_MMC_REVSTSR_RXREIS |  \
                                         ETH_MMC_REVSTSR_RXAEIS | ETH_MMC_REVSTSR_RXCEIS |  \
                                         ETH_MMC_REVSTSR_RXMGIS | ETH_MMC_REVSTSR_RXBGIS);
    MMC_TRSSTSR = CM_ETH->MMC_TRSSTSR & (ETH_MMC_TRSSTSR_TXEDEIS | ETH_MMC_TRSSTSR_TXUGIS |  \
                                         ETH_MMC_TRSSTSR_TXCAEIS | ETH_MMC_TRSSTSR_TXECEIS |  \
                                         ETH_MMC_TRSSTSR_TXLCEIS | ETH_MMC_TRSSTSR_TXDEEIS |  \
                                         ETH_MMC_TRSSTSR_TXMGIS | ETH_MMC_TRSSTSR_TXBGIS);
    MMC_RITCTLR = CM_ETH->MMC_RITCTLR & (ETH_MMC_RITCTLR_RXBGIM | ETH_MMC_RITCTLR_RXMGIM |  \
                                         ETH_MMC_RITCTLR_RXCEIM | ETH_MMC_RITCTLR_RXAEIM |  \
                                         ETH_MMC_RITCTLR_RXREIM | ETH_MMC_RITCTLR_RXUGIM |  \
                                         ETH_MMC_RITCTLR_RXLEIM | ETH_MMC_RITCTLR_RXOEIM);
    MMC_TITCTLR = CM_ETH->MMC_TITCTLR & (ETH_MMC_TITCTLR_TXBGIM | ETH_MMC_TITCTLR_TXMGIM |  \
                                         ETH_MMC_TITCTLR_TXDEEIM | ETH_MMC_TITCTLR_TXLCEIM |  \
                                         ETH_MMC_TITCTLR_TXECEIM | ETH_MMC_TITCTLR_TXCAEIM |  \
                                         ETH_MMC_TITCTLR_TXUGIM | ETH_MMC_TITCTLR_TXEDEIM);
    PMT_INTMASK = bCM_ETH->MAC_INTMSKR_b.PMTIM;
    PMT_INTSTSR  = bCM_ETH->MAC_INTSTSR_b.PMTIS;
    PTP_INTMASK = bCM_ETH->MAC_INTMSKR_b.TSPIM;
    PTP_INTSTSR  = bCM_ETH->MAC_INTSTSR_b.TSPIS;
    PTP_INTE    = bCM_ETH->PTP_TSPCTLR_b.TSPINT;

    DMA_DMASTSR = CM_ETH->DMA_DMASTSR & (ETH_DMA_DMASTSR_AIS | ETH_DMA_DMASTSR_NIS);
    DMA_INTENAR = CM_ETH->DMA_INTENAR & (ETH_DMA_INTENAR_AIE | ETH_DMA_INTENAR_NIE);
    if (0UL != (VSSEL140 & BIT_MASK_28)) {
        if ((0UL != (MMC_REVSTSR & (~MMC_RITCTLR))) ||                          \
            (0UL != (MMC_TRSSTSR & (~MMC_TITCTLR))) ||                          \
            (0UL != (PMT_INTSTSR & (~PMT_INTMASK))) ||                          \
            (0UL != (PTP_INTSTSR & (~PTP_INTMASK) & PTP_INTE)) ||               \
            (0UL != (DMA_DMASTSR & DMA_INTENAR))) {
            ETH_Global_IrqHandler();
        }
    }

    /* Ethernet wakeup */
    if (0UL == bCM_ETH->MAC_INTMSKR_b.PMTIM) {
        if ((1UL == bCM_ETH->MAC_INTSTSR_b.PMTIS) && (0UL != (VSSEL140 & BIT_MASK_29))) {
            ETH_Wakeup_IrqHandler();
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
    const uint32_t VSSEL141 = CM_INTC->VSSEL141;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* I2S Ch.3 Tx */
    if (1UL == bCM_I2S3->CTRL_b.TXIE) {
        if ((1UL == bCM_I2S3->SR_b.TXBA) && (0UL != (VSSEL141 & BIT_MASK_00))) {
            I2S3_Tx_IrqHandler();
        }
    }
    /* I2S Ch.3 Rx */
    if (1UL == bCM_I2S3->CTRL_b.RXIE) {
        if ((1UL == bCM_I2S3->SR_b.RXBA) && (0UL != (VSSEL141 & BIT_MASK_01))) {
            I2S3_Rx_IrqHandler();
        }
    }
    /* I2S Ch.3 Error */
    if (1UL == bCM_I2S3->CTRL_b.EIE) {
        u32Tmp1 = CM_I2S3->ER & (I2S_ER_TXERR | I2S_ER_RXERR);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL141 & BIT_MASK_02))) {
            I2S3_Error_IrqHandler();
        }
    }
    /* I2S Ch.4 Tx */
    if (1UL == bCM_I2S4->CTRL_b.TXIE) {
        if ((1UL == bCM_I2S4->SR_b.TXBA) && (0UL != (VSSEL141 & BIT_MASK_03))) {
            I2S4_Tx_IrqHandler();
        }
    }
    /* I2S Ch.4 Rx */
    if (1UL == bCM_I2S4->CTRL_b.RXIE) {
        if ((1UL == bCM_I2S4->SR_b.RXBA) && (0UL != (VSSEL141 & BIT_MASK_04))) {
            I2S4_Rx_IrqHandler();
        }
    }
    /* I2S Ch.4 Error */
    if (1UL == bCM_I2S4->CTRL_b.EIE) {
        u32Tmp1 = CM_I2S4->ER & (I2S_ER_TXERR | I2S_ER_RXERR);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL141 & BIT_MASK_05))) {
            I2S4_Error_IrqHandler();
        }
    }
    if (1UL == bCM_USART9->CR1_b.RIE) {
        /* USART Ch.9 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART9->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL141 & BIT_MASK_06))) {
            USART9_RxError_IrqHandler();
        }
        /* USART Ch.9 Rx end */
        if ((1UL == bCM_USART9->SR_b.RXNE) && (0UL != (VSSEL141 & BIT_MASK_07))) {
            USART9_RxFull_IrqHandler();
        }
    }
    /* USART Ch.9 Tx buffer empty */
    if (1UL == bCM_USART9->CR1_b.TXEIE) {
        if ((1UL == bCM_USART9->SR_b.TXE) && (0UL != (VSSEL141 & BIT_MASK_08))) {
            USART9_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.9 Tx end */
    if (1UL == bCM_USART9->CR1_b.TCIE) {
        if ((1UL == bCM_USART9->SR_b.TC) && (0UL != (VSSEL141 & BIT_MASK_09))) {
            USART9_TxComplete_IrqHandler();
        }
    }
    /* USART Ch.10 LIN bus break */
    if (1UL == bCM_USART10->CR2_b.LBDIE) {
        if ((1UL == bCM_USART10->SR_b.LBD) && (0UL != (VSSEL141 & BIT_MASK_10))) {
            USART10_LinBreakField_IrqHandler();
        }
    }
    /* USART Ch.10 LIN bus wakeup */
    if (1UL == bCM_USART10->CR2_b.WKUPE) {
        if ((1UL == bCM_USART10->SR_b.WKUP) && (0UL != (VSSEL141 & BIT_MASK_10))) {
            USART10_LinWakeup_IrqHandler();
        }
    }
    if (1UL == bCM_USART10->CR1_b.RIE) {
        /* USART Ch.10 Rx ORE/FE/PE error */
        u32Tmp1 = CM_USART10->SR & (USART_SR_PE | USART_SR_FE | USART_SR_ORE);
        if ((0UL != u32Tmp1) && (0UL != (VSSEL141 & BIT_MASK_11))) {
            USART10_RxError_IrqHandler();
        }
        /* USART Ch.10 Rx end */
        if ((1UL == bCM_USART10->SR_b.RXNE) && (0UL != (VSSEL141 & BIT_MASK_12))) {
            USART10_RxFull_IrqHandler();
        }
    }
    /* USART Ch.10 Tx buffer empty */
    if (1UL == bCM_USART10->CR1_b.TXEIE) {
        if ((1UL == bCM_USART10->SR_b.TXE) && (0UL != (VSSEL141 & BIT_MASK_13))) {
            USART10_TxEmpty_IrqHandler();
        }
    }
    /* USART Ch.10 Tx end */
    if (1UL == bCM_USART10->CR1_b.TCIE) {
        if ((1UL == bCM_USART10->SR_b.TC) && (0UL != (VSSEL141 & BIT_MASK_14))) {
            USART10_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.1 Rx end */
    if (1UL == bCM_I2C1->CR2_b.RFULLIE) {
        if ((1UL == bCM_I2C1->SR_b.RFULLF) && (0UL != (VSSEL141 & BIT_MASK_16))) {
            I2C1_RxFull_IrqHandler();
        }
    }
    /* I2C Ch.1 Tx buffer empty */
    if (1UL == bCM_I2C1->CR2_b.TEMPTYIE) {
        if ((1UL == bCM_I2C1->SR_b.TEMPTYF) && (0UL != (VSSEL141 & BIT_MASK_17))) {
            I2C1_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.1 Tx end */
    if (1UL == bCM_I2C1->CR2_b.TENDIE) {
        if ((1UL == bCM_I2C1->SR_b.TENDF) && (0UL != (VSSEL141 & BIT_MASK_18))) {
            I2C1_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.1 Error */
    u32Tmp1 = CM_I2C1->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMBHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = CM_I2C1->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL141 & BIT_MASK_19))) {
        I2C1_EE_IrqHandler();
    }
    /* I2C Ch.2 Rx end */
    if (1UL == bCM_I2C2->CR2_b.RFULLIE) {
        if ((1UL == bCM_I2C2->SR_b.RFULLF) && (0UL != (VSSEL141 & BIT_MASK_20))) {
            I2C2_RxFull_IrqHandler();
        }
    }
    /* I2C Ch.2 Tx buffer empty */
    if (1UL == bCM_I2C2->CR2_b.TEMPTYIE) {
        if ((1UL == bCM_I2C2->SR_b.TEMPTYF) && (0UL != (VSSEL141 & BIT_MASK_21))) {
            I2C2_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.2 Tx end */
    if (1UL == bCM_I2C2->CR2_b.TENDIE) {
        if ((1UL == bCM_I2C2->SR_b.TENDF) && (0UL != (VSSEL141 & BIT_MASK_22))) {
            I2C2_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.2 Error */
    u32Tmp1 = CM_I2C2->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMBHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = CM_I2C2->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL141 & BIT_MASK_23))) {
        I2C2_EE_IrqHandler();
    }
    /* I2C Ch.3 Rx end */
    if (1UL == bCM_I2C3->CR2_b.RFULLIE) {
        if ((1UL == bCM_I2C3->SR_b.RFULLF) && (0UL != (VSSEL141 & BIT_MASK_24))) {
            I2C3_RxFull_IrqHandler();
        }
    }
    /* I2C Ch.3 Tx buffer empty */
    if (1UL == bCM_I2C3->CR2_b.TEMPTYIE) {
        if ((1UL == bCM_I2C3->SR_b.TEMPTYF) && (0UL != (VSSEL141 & BIT_MASK_25))) {
            I2C3_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.3 Tx end */
    if (1UL == bCM_I2C3->CR2_b.TENDIE) {
        if ((1UL == bCM_I2C3->SR_b.TENDF) && (0UL != (VSSEL141 & BIT_MASK_26))) {
            I2C3_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.3 Error */
    u32Tmp1 = CM_I2C3->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMBHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = CM_I2C3->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL141 & BIT_MASK_27))) {
        I2C3_EE_IrqHandler();
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
    const uint32_t VSSEL142 = CM_INTC->VSSEL142;
    uint32_t u32Tmp1;
    uint32_t u32Tmp2;

    /* I2C Ch.4 Rx end */
    if (1UL == bCM_I2C4->CR2_b.RFULLIE) {
        if ((1UL == bCM_I2C4->SR_b.RFULLF) && (0UL != (VSSEL142 & BIT_MASK_00))) {
            I2C4_RxFull_IrqHandler();
        }
    }
    /* I2C Ch.4 Tx buffer empty */
    if (1UL == bCM_I2C4->CR2_b.TEMPTYIE) {
        if ((1UL == bCM_I2C4->SR_b.TEMPTYF) && (0UL != (VSSEL142 & BIT_MASK_01))) {
            I2C4_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.4 Tx end */
    if (1UL == bCM_I2C4->CR2_b.TENDIE) {
        if ((1UL == bCM_I2C4->SR_b.TENDF) && (0UL != (VSSEL142 & BIT_MASK_02))) {
            I2C4_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.4 Error */
    u32Tmp1 = CM_I2C4->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMBHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = CM_I2C4->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL142 & BIT_MASK_03))) {
        I2C4_EE_IrqHandler();
    }
    /* I2C Ch.5 Rx end */
    if (1UL == bCM_I2C5->CR2_b.RFULLIE) {
        if ((1UL == bCM_I2C5->SR_b.RFULLF) && (0UL != (VSSEL142 & BIT_MASK_04))) {
            I2C5_RxFull_IrqHandler();
        }
    }
    /* I2C Ch.5 Tx buffer empty */
    if (1UL == bCM_I2C5->CR2_b.TEMPTYIE) {
        if ((1UL == bCM_I2C5->SR_b.TEMPTYF) && (0UL != (VSSEL142 & BIT_MASK_05))) {
            I2C5_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.5 Tx end */
    if (1UL == bCM_I2C5->CR2_b.TENDIE) {
        if ((1UL == bCM_I2C5->SR_b.TENDF) && (0UL != (VSSEL142 & BIT_MASK_06))) {
            I2C5_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.5 Error */
    u32Tmp1 = CM_I2C5->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMBHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = CM_I2C5->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL142 & BIT_MASK_07))) {
        I2C5_EE_IrqHandler();
    }
    /* I2C Ch.6 Rx end */
    if (1UL == bCM_I2C6->CR2_b.RFULLIE) {
        if ((1UL == bCM_I2C6->SR_b.RFULLF) && (0UL != (VSSEL142 & BIT_MASK_08))) {
            I2C6_RxFull_IrqHandler();
        }
    }
    /* I2C Ch.6 Tx buffer empty */
    if (1UL == bCM_I2C6->CR2_b.TEMPTYIE) {
        if ((1UL == bCM_I2C6->SR_b.TEMPTYF) && (0UL != (VSSEL142 & BIT_MASK_09))) {
            I2C6_TxEmpty_IrqHandler();
        }
    }
    /* I2C Ch.6 Tx end */
    if (1UL == bCM_I2C6->CR2_b.TENDIE) {
        if ((1UL == bCM_I2C6->SR_b.TENDF) && (0UL != (VSSEL142 & BIT_MASK_10))) {
            I2C6_TxComplete_IrqHandler();
        }
    }
    /* I2C Ch.6 Error */
    u32Tmp1 = CM_I2C6->CR2 & (I2C_CR2_SMBALRTIE | I2C_CR2_SMBHOSTIE | I2C_CR2_SMBDEFAULTIE | \
                              I2C_CR2_GENCALLIE | I2C_CR2_TMOUTIE  | I2C_CR2_NACKIE       | \
                              I2C_CR2_ARLOIE    | I2C_CR2_STOPIE   | I2C_CR2_SLADDR1IE    | \
                              I2C_CR2_SLADDR0IE | I2C_CR2_STARTIE);
    u32Tmp2 = CM_I2C6->SR & (I2C_SR_SMBALRTF | I2C_SR_SMBHOSTF | I2C_SR_SMBDEFAULTF |   \
                             I2C_SR_GENCALLF | I2C_SR_TMOUTF   | I2C_SR_NACKF       |   \
                             I2C_SR_ARLOF    | I2C_SR_STOPF    | I2C_SR_SLADDR1F    |   \
                             I2C_SR_SLADDR0F | I2C_SR_STARTF);
    if ((0UL != (u32Tmp1 & u32Tmp2)) && (0UL != (VSSEL142 & BIT_MASK_11))) {
        I2C6_EE_IrqHandler();
    }
    /* LVD Ch.1 */
    if (1UL == bCM_PWC->PVDCR1_b.PVD1IRE) {
        if ((1UL == bCM_PWC->PVDDSR_b.PVD1DETFLG) && (0UL != (VSSEL142 & BIT_MASK_13))) {
            PWC_LVD1_IrqHandler();
        }
    }
    /* LVD Ch.2 */
    if (1UL == bCM_PWC->PVDCR1_b.PVD2IRE) {
        if ((1UL == bCM_PWC->PVDDSR_b.PVD2DETFLG) && (0UL != (VSSEL142 & BIT_MASK_14))) {
            PWC_LVD2_IrqHandler();
        }
    }
    /* FCM error */
    if (1UL == bCM_FCM->RIER_b.ERRIE) {
        if ((1UL == bCM_FCM->SR_b.ERRF) && (0UL != (VSSEL142 & BIT_MASK_16))) {
            FCM_Error_IrqHandler();
        }
    }
    /* FCM end */
    if (1UL == bCM_FCM->RIER_b.MENDIE) {
        if ((1UL == bCM_FCM->SR_b.MENDF) && (0UL != (VSSEL142 & BIT_MASK_17))) {
            FCM_End_IrqHandler();
        }
    }
    /* FCM overflow */
    if (1UL == bCM_FCM->RIER_b.OVFIE) {
        if ((1UL == bCM_FCM->SR_b.OVF) && (0UL != (VSSEL142 & BIT_MASK_18))) {
            FCM_Ovf_IrqHandler();
        }
    }
    /* WDT underflow or refresh error */
    u32Tmp1 = CM_WDT->SR & (WDT_SR_UDF | WDT_SR_REF);
    if ((0UL != u32Tmp1) && (0UL != (VSSEL142 & BIT_MASK_19))) {
        WDT_IrqHandler();
    }
    /* CTC overflow or underflow error */
    if (1UL == bCM_CTC->CR1_b.ERRIE) {
        /* underflow */
        if ((1UL == bCM_CTC->STR_b.TRMUDF) && (0UL != (VSSEL142 & BIT_MASK_20))) {
            CTC_Udf_IrqHandler();
        }
        /* overflow */
        if ((1UL == bCM_CTC->STR_b.TRMOVF) && (0UL != (VSSEL142 & BIT_MASK_20))) {
            CTC_Ovf_IrqHandler();
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
    const uint32_t VSSEL143 = CM_INTC->VSSEL143;
    uint32_t u32Tmp1;

    /* ADC unit1 sequence A */
    if (1UL == bCM_ADC1->ICR_b.EOCAIEN) {
        if ((1UL == bCM_ADC1->ISR_b.EOCAF) && (0UL != (VSSEL143 & BIT_MASK_00))) {
            ADC1_SeqA_IrqHandler();
        }
    }
    /* ADC unit1 sequence B */
    if (1UL == bCM_ADC1->ICR_b.EOCBIEN) {
        if ((1UL == bCM_ADC1->ISR_b.EOCBF) && (0UL != (VSSEL143 & BIT_MASK_01))) {
            ADC1_SeqB_IrqHandler();
        }
    }
    /* ADC unit1 window 0 compare */
    if (1UL == bCM_ADC1->AWDCR_b.AWD0IEN) {
        if ((1UL == bCM_ADC1->AWDSR_b.AWD0F) && (0UL != (VSSEL143 & BIT_MASK_02))) {
            ADC1_Cmp0_IrqHandler();
        }
    }
    /* ADC unit1 window 1 compare */
    if (1UL == bCM_ADC1->AWDCR_b.AWD1IEN) {
        /* independence use */
        u32Tmp1 = (uint16_t)(CM_ADC1->AWDCR & ADC_AWDCR_AWDCM);
        if ((1UL == bCM_ADC1->AWDSR_b.AWD1F) && (0UL == u32Tmp1) && (0UL != (VSSEL143 & BIT_MASK_03))) {
            ADC1_Cmp1_IrqHandler();
        }
        /* combination use */
        if ((1UL == bCM_ADC1->AWDSR_b.AWDCMF) && (0UL != u32Tmp1) && (0UL != (VSSEL143 & BIT_MASK_03))) {
            ADC1_CmpComb_IrqHandler();
        }
    }
    /* ADC unit2 sequence A */
    if (1UL == bCM_ADC2->ICR_b.EOCAIEN) {
        if ((1UL == bCM_ADC2->ISR_b.EOCAF) && (0UL != (VSSEL143 & BIT_MASK_04))) {
            ADC2_SeqA_IrqHandler();
        }
    }
    /* ADC unit2 sequence B */
    if (1UL == bCM_ADC2->ICR_b.EOCBIEN) {
        if ((1UL == bCM_ADC2->ISR_b.EOCBF) && (0UL != (VSSEL143 & BIT_MASK_05))) {
            ADC2_SeqB_IrqHandler();
        }
    }
    /* ADC unit2 window 0 compare */
    if (1UL == bCM_ADC2->AWDCR_b.AWD0IEN) {
        if ((1UL == bCM_ADC2->AWDSR_b.AWD0F) && (0UL != (VSSEL143 & BIT_MASK_06))) {
            ADC2_Cmp0_IrqHandler();
        }
    }
    /* ADC unit2 window 1 compare */
    if (1UL == bCM_ADC2->AWDCR_b.AWD1IEN) {
        /* independence use */
        u32Tmp1 = ((uint16_t)(CM_ADC2->AWDCR & ADC_AWDCR_AWDCM));
        if ((1UL == bCM_ADC2->AWDSR_b.AWD1F) && (0UL == u32Tmp1) && (0UL != (0UL != (VSSEL143 & BIT_MASK_07)))) {
            ADC2_Cmp1_IrqHandler();
        }
        /* combination use */
        if ((1UL == bCM_ADC2->AWDSR_b.AWDCMF) && (0UL != u32Tmp1) && (0UL != (0UL != (VSSEL143 & BIT_MASK_07)))) {
            ADC2_CmpComb_IrqHandler();
        }
    }
    /* ADC unit3 sequence A */
    if (1UL == bCM_ADC3->ICR_b.EOCAIEN) {
        if ((1UL == bCM_ADC3->ISR_b.EOCAF) && (0UL != (VSSEL143 & BIT_MASK_08))) {
            ADC3_SeqA_IrqHandler();
        }
    }
    /* ADC unit3 sequence B */
    if (1UL == bCM_ADC3->ICR_b.EOCBIEN) {
        if ((1UL == bCM_ADC3->ISR_b.EOCBF) && (0UL != (VSSEL143 & BIT_MASK_09))) {
            ADC3_SeqB_IrqHandler();
        }
    }
    /* ADC unit3 window 0 compare */
    if (1UL == bCM_ADC3->AWDCR_b.AWD0IEN) {
        if ((1UL == bCM_ADC3->AWDSR_b.AWD0F) && (0UL != (VSSEL143 & BIT_MASK_10))) {
            ADC3_Cmp0_IrqHandler();
        }
    }
    /* ADC unit3 window 1 compare */
    if (1UL == bCM_ADC3->AWDCR_b.AWD1IEN) {
        /* independence use */
        u32Tmp1 = (uint16_t)(CM_ADC3->AWDCR & ADC_AWDCR_AWDCM);
        if ((1UL == bCM_ADC3->AWDSR_b.AWD1F) && (0UL == u32Tmp1) && (0UL != (VSSEL143 & BIT_MASK_11))) {
            ADC3_Cmp1_IrqHandler();
        }
        /* combination use */
        if ((1UL == bCM_ADC3->AWDSR_b.AWDCMF) && (0UL != u32Tmp1) && (0UL != (VSSEL143 & BIT_MASK_11))) {
            ADC3_CmpComb_IrqHandler();
        }
    }
    if (0UL != (VSSEL143 & BIT_MASK_16)) {
        if (0UL != (CM_NFC->IRSR & (NFC_IRSR_RBRS | NFC_IRSR_ECCERS |           \
                                    NFC_IRSR_ECCCRS | NFC_IRSR_ECCECRS | NFC_IRSR_ECCEURS))) {
            NFC_IrqHandler();
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
__WEAKDEF void DMA1_TC4_IrqHandler(void)
{
}
__WEAKDEF void DMA1_TC5_IrqHandler(void)
{
}
__WEAKDEF void DMA1_TC6_IrqHandler(void)
{
}
__WEAKDEF void DMA1_TC7_IrqHandler(void)
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
__WEAKDEF void DMA1_BTC4_IrqHandler(void)
{
}
__WEAKDEF void DMA1_BTC5_IrqHandler(void)
{
}
__WEAKDEF void DMA1_BTC6_IrqHandler(void)
{
}
__WEAKDEF void DMA1_BTC7_IrqHandler(void)
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
__WEAKDEF void DMA1_Error4_IrqHandler(void)
{
}
__WEAKDEF void DMA1_Error5_IrqHandler(void)
{
}
__WEAKDEF void DMA1_Error6_IrqHandler(void)
{
}
__WEAKDEF void DMA1_Error7_IrqHandler(void)
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
__WEAKDEF void DMA2_TC4_IrqHandler(void)
{
}
__WEAKDEF void DMA2_TC5_IrqHandler(void)
{
}
__WEAKDEF void DMA2_TC6_IrqHandler(void)
{
}
__WEAKDEF void DMA2_TC7_IrqHandler(void)
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
__WEAKDEF void DMA2_BTC4_IrqHandler(void)
{
}
__WEAKDEF void DMA2_BTC5_IrqHandler(void)
{
}
__WEAKDEF void DMA2_BTC6_IrqHandler(void)
{
}
__WEAKDEF void DMA2_BTC7_IrqHandler(void)
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
__WEAKDEF void DMA2_Error4_IrqHandler(void)
{
}
__WEAKDEF void DMA2_Error5_IrqHandler(void)
{
}
__WEAKDEF void DMA2_Error6_IrqHandler(void)
{
}
__WEAKDEF void DMA2_Error7_IrqHandler(void)
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
__WEAKDEF void MAU_Sqrt_IrqHandler(void)
{
}
__WEAKDEF void DVP_FrameStart_IrqHandler(void)
{
}
__WEAKDEF void DVP_FrameEnd_IrqHandler(void)
{
}
__WEAKDEF void DVP_LineStart_IrqHandler(void)
{
}
__WEAKDEF void DVP_LineEnd_IrqHandler(void)
{
}
__WEAKDEF void DVP_SWSyncError_IrqHandler(void)
{
}
__WEAKDEF void DVP_FifoError_IrqHandler(void)
{
}
__WEAKDEF void FMAC1_IrqHandler(void)
{
}
__WEAKDEF void FMAC2_IrqHandler(void)
{
}
__WEAKDEF void FMAC3_IrqHandler(void)
{
}
__WEAKDEF void FMAC4_IrqHandler(void)
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
__WEAKDEF void DCU5_IrqHandler(void)
{
}
__WEAKDEF void DCU6_IrqHandler(void)
{
}
__WEAKDEF void DCU7_IrqHandler(void)
{
}
__WEAKDEF void DCU8_IrqHandler(void)
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
__WEAKDEF void TMR2_1_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_1_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_1_OvfA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_1_OvfB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_2_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_2_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_2_OvfA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_2_OvfB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_3_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_3_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_3_OvfA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_3_OvfB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_4_CmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_4_CmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR2_4_OvfA_IrqHandler(void)
{
}
__WEAKDEF void TMR2_4_OvfB_IrqHandler(void)
{
}
__WEAKDEF void RTC_TimeStamp0_IrqHandler(void)
{
}
__WEAKDEF void RTC_TimeStamp1_IrqHandler(void)
{
}
__WEAKDEF void RTC_Alarm_IrqHandler(void)
{
}
__WEAKDEF void RTC_Period_IrqHandler(void)
{
}
__WEAKDEF void CLK_XtalStop_IrqHandler(void)
{
}
__WEAKDEF void SWDT_IrqHandler(void)
{
}
__WEAKDEF void WDT_IrqHandler(void)
{
}
__WEAKDEF void PWC_WakeupTimer_IrqHandler(void)
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
__WEAKDEF void TMR6_1_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_1_SCmpDownB_IrqHandler(void)
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
__WEAKDEF void TMR6_2_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_2_SCmpDownB_IrqHandler(void)
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
__WEAKDEF void TMR6_3_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_3_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_4_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_5_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_6_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_7_SCmpDownB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpC_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpD_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpE_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GCmpF_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GOvf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_GUdf_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_Gdte_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_SCmpUpA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_SCmpDownA_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_SCmpUpB_IrqHandler(void)
{
}
__WEAKDEF void TMR6_8_SCmpDownB_IrqHandler(void)
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
__WEAKDEF void TMR4_1_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_1_Udf_IrqHandler(void)
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
__WEAKDEF void TMR4_2_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_2_Udf_IrqHandler(void)
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
__WEAKDEF void TMR4_3_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMR4_3_Udf_IrqHandler(void)
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
__WEAKDEF void TMRA_7_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_7_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_7_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_8_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_8_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_8_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_9_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_9_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_9_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_10_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_10_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_10_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_11_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_11_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_11_Cmp_IrqHandler(void)
{
}
__WEAKDEF void TMRA_12_Ovf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_12_Udf_IrqHandler(void)
{
}
__WEAKDEF void TMRA_12_Cmp_IrqHandler(void)
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
__WEAKDEF void EMB_GR4_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR5_IrqHandler(void)
{
}
__WEAKDEF void EMB_GR6_IrqHandler(void)
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
__WEAKDEF void USART5_LinBreakField_IrqHandler(void)
{
}
__WEAKDEF void USART5_LinWakeup_IrqHandler(void)
{
}
__WEAKDEF void USART5_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART5_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART5_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART5_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void USART6_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART6_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART6_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART6_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void USART6_RxTO_IrqHandler(void)
{
}
__WEAKDEF void USART7_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART7_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART7_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART7_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void USART7_RxTO_IrqHandler(void)
{
}
__WEAKDEF void USART8_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART8_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART8_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART8_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void USART9_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART9_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART9_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART9_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void USART10_LinBreakField_IrqHandler(void)
{
}
__WEAKDEF void USART10_LinWakeup_IrqHandler(void)
{
}
__WEAKDEF void USART10_RxError_IrqHandler(void)
{
}
__WEAKDEF void USART10_RxFull_IrqHandler(void)
{
}
__WEAKDEF void USART10_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void USART10_TxComplete_IrqHandler(void)
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
__WEAKDEF void SPI5_RxFull_IrqHandler(void)
{
}
__WEAKDEF void SPI5_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI5_Error_IrqHandler(void)
{
}
__WEAKDEF void SPI5_Idle_IrqHandler(void)
{
}
__WEAKDEF void SPI6_RxFull_IrqHandler(void)
{
}
__WEAKDEF void SPI6_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void SPI6_Error_IrqHandler(void)
{
}
__WEAKDEF void SPI6_Idle_IrqHandler(void)
{
}
__WEAKDEF void CAN1_IrqHandler(void)
{
}
__WEAKDEF void CAN2_IrqHandler(void)
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
__WEAKDEF void USBFS_Global_IrqHandler(void)
{
}
__WEAKDEF void SDIOC1_Normal_IrqHandler(void)
{
}
__WEAKDEF void SDIOC1_Error_IrqHandler(void)
{
}
__WEAKDEF void SDIOC2_Normal_IrqHandler(void)
{
}
__WEAKDEF void SDIOC2_Error_IrqHandler(void)
{
}
__WEAKDEF void ETH_Global_IrqHandler(void)
{
}
__WEAKDEF void ETH_Wakeup_IrqHandler(void)
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
__WEAKDEF void I2C4_RxFull_IrqHandler(void)
{
}
__WEAKDEF void I2C4_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void I2C4_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C4_EE_IrqHandler(void)
{
}
__WEAKDEF void I2C5_RxFull_IrqHandler(void)
{
}
__WEAKDEF void I2C5_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void I2C5_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C5_EE_IrqHandler(void)
{
}
__WEAKDEF void I2C6_RxFull_IrqHandler(void)
{
}
__WEAKDEF void I2C6_TxComplete_IrqHandler(void)
{
}
__WEAKDEF void I2C6_TxEmpty_IrqHandler(void)
{
}
__WEAKDEF void I2C6_EE_IrqHandler(void)
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
__WEAKDEF void CTC_Udf_IrqHandler(void)
{
}
__WEAKDEF void CTC_Ovf_IrqHandler(void)
{
}
__WEAKDEF void ADC1_SeqA_IrqHandler(void)
{
}
__WEAKDEF void ADC1_SeqB_IrqHandler(void)
{
}
__WEAKDEF void ADC1_Cmp0_IrqHandler(void)
{
}
__WEAKDEF void ADC1_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void ADC1_CmpComb_IrqHandler(void)
{
}
__WEAKDEF void ADC2_SeqA_IrqHandler(void)
{
}
__WEAKDEF void ADC2_SeqB_IrqHandler(void)
{
}
__WEAKDEF void ADC2_Cmp0_IrqHandler(void)
{
}
__WEAKDEF void ADC2_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void ADC2_CmpComb_IrqHandler(void)
{
}
__WEAKDEF void ADC3_SeqA_IrqHandler(void)
{
}
__WEAKDEF void ADC3_SeqB_IrqHandler(void)
{
}
__WEAKDEF void ADC3_Cmp0_IrqHandler(void)
{
}
__WEAKDEF void ADC3_Cmp1_IrqHandler(void)
{
}
__WEAKDEF void ADC3_CmpComb_IrqHandler(void)
{
}
__WEAKDEF void NFC_IrqHandler(void)
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
