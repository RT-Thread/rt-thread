/**
 *******************************************************************************
 * @file  system_hc32f4a0.c
 * @brief This file provides two functions and two global variables to be called
 *        from user application.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Delete the __low_level_init function of IAR and $Sub$$main function of MDK
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
#include "system_hc32f4a0.h"

/**
 * @addtogroup CMSIS
 * @{
 */

/**
 * @addtogroup HC32F4A0_System
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('define')
 ******************************************************************************/
/**
 * @defgroup HC32F4A0_System_Local_Macros HC32F4A0 System Local Macros
 * @{
 */
#define HRC_16MHz_VALUE                 (16000000UL)  /*!< Internal high speed RC freq. */
#define HRC_20MHz_VALUE                 (20000000UL)  /*!< Internal high speed RC freq. */
/* HRC select */
#define HRC_FREQ_MON()                  (*((volatile uint32_t *)(0x40010684UL)))

/* Vector Table base offset field */
#ifndef VECT_TAB_OFFSET
#define VECT_TAB_OFFSET                 (0x0UL)     /*!< This value must be a multiple of 0x400. */
#endif
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Global_Variable
 * @{
 */

/*!< System clock frequency (Core clock) */
__NO_INIT uint32_t SystemCoreClock;
/*!< High speed RC frequency (HCR clock) */
__NO_INIT uint32_t HRC_VALUE;

/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Global_Functions
 * @{
 */

/**
 * @brief  Setup the microcontroller system. Initialize the System and update
 *         the SystemCoreClock variable.
 * @param  None
 * @retval None
 */
void SystemInit(void)
{
    /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 20) | (3UL << 22)); /* set CP10 and CP11 Full Access */
#endif
    SystemCoreClockUpdate();
#if defined (ROM_EXT_QSPI)
    SystemInit_QspiMem();
#endif /* ROM_EXT_QSPI */
    /* Configure the Vector Table relocation */
    SCB->VTOR = VECT_TAB_OFFSET;    /* Vector Table Relocation */
}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 * @param  None
 * @retval None
 */
void SystemCoreClockUpdate(void)
{
    uint8_t u8SysClkSrc;
    uint32_t plln;
    uint32_t pllp;
    uint32_t pllm;
    uint32_t u32PllSrcFreq;

    /* Select proper HRC_VALUE according to ICG1.HRCFREQSEL bit */
    if (1UL == (HRC_FREQ_MON() & 1UL)) {
        HRC_VALUE = HRC_16MHz_VALUE;
    } else {
        HRC_VALUE = HRC_20MHz_VALUE;
    }
    u8SysClkSrc = CM_CMU->CKSWR & CMU_CKSWR_CKSW;
    switch (u8SysClkSrc) {
        case 0x00U: /* use internal high speed RC */
            SystemCoreClock = HRC_VALUE;
            break;
        case 0x01U: /* use internal middle speed RC */
            SystemCoreClock = MRC_VALUE;
            break;
        case 0x02U: /* use internal low speed RC */
            SystemCoreClock = LRC_VALUE;
            break;
        case 0x03U: /* use external high speed OSC */
            SystemCoreClock = XTAL_VALUE;
            break;
        case 0x04U: /* use external low speed OSC */
            SystemCoreClock = XTAL32_VALUE;
            break;
        case 0x05U:  /* use PLLH */
            /* PLLCLK = ((pllsrc / pllm) * plln) / pllp */
            plln = (CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHN) >> CMU_PLLHCFGR_PLLHN_POS;
            pllp = (CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHP) >> CMU_PLLHCFGR_PLLHP_POS;
            pllm = (CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLHM) >> CMU_PLLHCFGR_PLLHM_POS;
            if (0UL == bCM_CMU->PLLHCFGR_b.PLLSRC) {    /* use external high speed OSC as PLL source */
                u32PllSrcFreq = XTAL_VALUE;
            } else {                                    /* use internal high RC as PLL source */
                u32PllSrcFreq = HRC_VALUE;
            }
            SystemCoreClock = u32PllSrcFreq / (pllm + 1UL) * (plln + 1UL) / (pllp + 1UL);
            break;
        default:
            break;
    }
}

#if defined (ROM_EXT_QSPI)
/**
 * @brief  Initialize the QSPI memory.
 * @param  None
 * @retval None
 */
__WEAKDEF void SystemInit_QspiMem(void)
{
    /* QSPI configure */
    CM_GPIO->PWPR = 0xA501U;
    /* High driver */
    CM_GPIO->PCRC7  = 0x0120U;
    CM_GPIO->PCRC6  = 0x0120U;
    CM_GPIO->PCRB13 = 0x0120U;
    CM_GPIO->PCRB12 = 0x0120U;
    CM_GPIO->PCRB10 = 0x0120U;
    CM_GPIO->PCRB2  = 0x0120U;
    /* Set function */
    CM_GPIO->PFSRC7  = 0x0012U;
    CM_GPIO->PFSRC6  = 0x0012U;
    CM_GPIO->PFSRB13 = 0x0012U;
    CM_GPIO->PFSRB12 = 0x0012U;
    CM_GPIO->PFSRB10 = 0x0012U;
    CM_GPIO->PFSRB2  = 0x0012U;
    /* qspi configure */
    CM_PWC->FCG1 &= ~0x00000008UL;
    CM_QSPI->CR   = 0x0002000D;
    CM_QSPI->CSCR = 0x00000001;
    CM_QSPI->FCR  = 0x00008332;
}
#endif /* ROM_EXT_QSPI */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
