/**
 *******************************************************************************
 * @file  hc32_ll_pwc.c
 * @brief This file provides firmware functions to manage the Power Control(PWC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Refine API PWC_STOP_Enter()
   2022-10-31       CDT             Bug fixed# PWC_PD_VdrCmd() and disable VDDR when enter PD3/4
   2023-01-15       CDT             Optimize API PWC_STOP_ClockSelect() & comment
                                    Modify API PWC_HighSpeedToLowSpeed() & PWC_HighPerformanceToLowSpeed() base um_Rev1.42
   2023-06-30       CDT             Modify typo
                                    Add api PWC_LVD_DeInit()
                                    Modify API PWC_STOP_Enter() & add assert IS_PWC_STOP_TYPE()
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
#include "hc32_ll_pwc.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_PWC PWC
 * @brief Power Control Driver Library
 * @{
 */

#if (LL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PWC_Local_Macros PWC Local Macros
 * @{
 */

/* Get the backup register address of PWC */

#define PWC_SYSCLK_SRC_HRC              (0U)
#define PWC_SYSCLK_SRC_PLL              (5U)

#define PWC_MD_SWITCH_TIMEOUT           (30UL)
#define PWC_MD_SWITCH_TIMEOUT2          (0x1000UL)
#define PWC_MD_SWITCH_CMD               (0x10U)

#define PWC_LVD_EN_REG                  (CM_PWC->PVDCR0)
#define PWC_LVD_EN_BIT                  (PWC_PVDCR0_PVD1EN)
#define PWC_LVD_EXT_INPUT_EN_REG        (CM_PWC->PVDCR0)
#define PWC_LVD_EXT_INPUT_EN_BIT        (PWC_PVDCR0_EXVCCINEN)
#define PWC_LVD_CMP_OUTPUT_EN_REG       (CM_PWC->PVDCR1)
#define PWC_LVD_CMP_OUTPUT_EN_BIT       (PWC_PVDCR1_PVD1CMPOE)
#define PWC_LVD_FILTER_EN_REG           (CM_PWC->PVDFCR)
#define PWC_LVD_FILTER_EN_BIT           (PWC_PVDFCR_PVD1NFDIS)
#define PWC_LVD_STATUS_REG              (CM_PWC->PVDDSR)

#define PWC_LVD2_POS                    (4U)
#define PWC_LVD_BIT_OFFSET(x)           ((uint8_t)((x) * PWC_LVD2_POS))
#define PWC_LVD_EN_BIT_OFFSET(x)        (x)

#define PWC_PRAM_MASK                   (PWC_RAM_PD_SRAM1   | PWC_RAM_PD_SDIO0 |    \
                                         PWC_RAM_PD_SRAM2   | PWC_RAM_PD_SDIO1 |    \
                                         PWC_RAM_PD_SRAM3   | PWC_RAM_PD_CAN   |    \
                                         PWC_RAM_PD_SRAMH   | PWC_RAM_PD_CACHE |    \
                                         PWC_RAM_PD_USBFS)

#define PWC_LVD_FLAG_MASK               (PWC_LVD1_FLAG_MON | PWC_LVD1_FLAG_DETECT | \
                                         PWC_LVD2_FLAG_MON | PWC_LVD2_FLAG_DETECT)

#define PWC_LVD_EXP_NMI_POS             (8U)

/**
 * @defgroup PWC_Check_Parameters_Validity PWC Check Parameters Validity
 * @{
 */
/* Check CLK register lock status. */
#define IS_PWC_CLK_UNLOCKED()           ((CM_PWC->FPRC & PWC_FPRC_FPRCB0) == PWC_FPRC_FPRCB0)

/* Check PWC register lock status. */
#define IS_PWC_UNLOCKED()               ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)
/* Check PWC LVD register lock status. */
#define IS_PWC_LVD_UNLOCKED()           ((CM_PWC->FPRC & PWC_FPRC_FPRCB3) == PWC_FPRC_FPRCB3)
/* Parameter validity check for EFM lock status. */
#define IS_PWC_EFM_UNLOCKED()           (CM_EFM->FAPRT == 0x00000001UL)

/* Parameter validity check for stop type */
#define IS_PWC_STOP_TYPE(x)                                                     \
(   ((x) == PWC_STOP_WFI)                           ||                          \
    ((x) == PWC_STOP_WFE_INT)                       ||                          \
    ((x) == PWC_STOP_WFE_EVT))

/* Parameter validity check for stop wake-up source */
#define IS_PWC_STOP_WKUP_SRC(x)                                                 \
(   ((x) == INT_SRC_USART1_WUPI)                    ||                          \
    ((x) == INT_SRC_TMR0_1_CMP_A)                   ||                          \
    ((x) == INT_SRC_RTC_ALM)                        ||                          \
    ((x) == INT_SRC_RTC_PRD)                        ||                          \
    ((x) == INT_SRC_WKTM_PRD)                       ||                          \
    ((x) == INT_SRC_CMP1)                           ||                          \
    ((x) == INT_SRC_LVD1)                           ||                          \
    ((x) == INT_SRC_LVD2)                           ||                          \
    ((x) == INT_SRC_SWDT_REFUDF)                    ||                          \
    ((x) == INT_SRC_PORT_EIRQ0)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ1)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ2)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ3)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ4)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ5)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ6)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ7)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ8)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ9)                     ||                          \
    ((x) == INT_SRC_PORT_EIRQ10)                    ||                          \
    ((x) == INT_SRC_PORT_EIRQ11)                    ||                          \
    ((x) == INT_SRC_PORT_EIRQ12)                    ||                          \
    ((x) == INT_SRC_PORT_EIRQ13)                    ||                          \
    ((x) == INT_SRC_PORT_EIRQ14)                    ||                          \
    ((x) == INT_SRC_PORT_EIRQ15))

/* Parameter validity check for peripheral RAM setting of power mode control */
#define IS_PWC_PRAM_CONTROL(x)                                                  \
(   ((x) != 0x00UL)                                 &&                          \
    (((x) | PWC_PRAM_MASK) == PWC_PRAM_MASK))

/* Parameter validity check for RAM setting of MCU operating mode */
#define IS_PWC_RAM_MD(x)                                                        \
(   ((x) == PWC_RAM_HIGH_SPEED)                     ||                          \
    ((x) == PWC_RAM_ULOW_SPEED))

/* Parameter validity check for LVD channel. */
#define IS_PWC_LVD_CH(x)                                                        \
(   ((x) == PWC_LVD_CH1)                            ||                          \
    ((x) == PWC_LVD_CH2))

/* Parameter validity check for LVD function setting. */
#define IS_PWC_LVD_EN(x)                                                        \
(   ((x) == PWC_LVD_ON)                             ||                          \
    ((x) == PWC_LVD_OFF))

/* Parameter validity check for LVD compare output setting. */
#define IS_PWC_LVD_CMP_EN(x)                                                    \
(   ((x) == PWC_LVD_CMP_ON)                         ||                          \
    ((x) == PWC_LVD_CMP_OFF))

/*  Parameter validity check for PWC LVD exception type. */
#define IS_PWC_LVD_EXP_TYPE(x)                                                  \
(   ((x) == PWC_LVD_EXP_TYPE_NONE)                  ||                          \
    ((x) == PWC_LVD_EXP_TYPE_INT)                   ||                          \
    ((x) == PWC_LVD_EXP_TYPE_NMI)                   ||                          \
    ((x) == PWC_LVD_EXP_TYPE_RST))

/* Parameter validity check for LVD digital noise filter function setting. */
#define IS_PWC_LVD_FILTER_EN(x)                                                 \
(   ((x) == PWC_LVD_FILTER_ON)                      ||                          \
    ((x) == PWC_LVD_FILTER_OFF))

/* Parameter validity check for LVD digital noise filter clock setting. */
#define IS_PWC_LVD_FILTER_CLK(x)                                                \
(   ((x) == PWC_LVD_FILTER_LRC_DIV1)                ||                          \
    ((x) == PWC_LVD_FILTER_LRC_DIV2)                ||                          \
    ((x) == PWC_LVD_FILTER_LRC_DIV4)                ||                          \
    ((x) == PWC_LVD_FILTER_LRC_MUL2))

/* Parameter validity check for LVD detect voltage setting. */
#define IS_PWC_LVD_THRESHOLD_VOLTAGE(x)                                         \
(   ((x) == PWC_LVD_THRESHOLD_LVL0)                 ||                          \
    ((x) == PWC_LVD_THRESHOLD_LVL1)                 ||                          \
    ((x) == PWC_LVD_THRESHOLD_LVL2)                 ||                          \
    ((x) == PWC_LVD_THRESHOLD_LVL3)                 ||                          \
    ((x) == PWC_LVD_THRESHOLD_LVL4)                 ||                          \
    ((x) == PWC_LVD_THRESHOLD_LVL5)                 ||                          \
    ((x) == PWC_LVD_THRESHOLD_LVL6)                 ||                          \
    ((x) == PWC_LVD_THRESHOLD_LVL7))

/* Parameter validity check for LVD NMI function setting. */
#define IS_PWC_LVD_NMI(x)                                                       \
(   ((x) == PWC_LVD_INT_MASK)                       ||                          \
    ((x) == PWC_LVD_INT_NONMASK))

/* Parameter validity check for LVD trigger setting. */
#define IS_PWC_LVD_TRIG_EDGE(x)                                                 \
(   ((x) == PWC_LVD_TRIG_FALLING)                   ||                          \
    ((x) == PWC_LVD_TRIG_RISING)                    ||                          \
    ((x) == PWC_LVD_TRIG_BOTH))

/* Parameter validity check for LVD trigger setting. */
#define IS_PWC_LVD_CLR_FLAG(x)                                                  \
(   ((x) == PWC_LVD1_FLAG_DETECT)                   ||                          \
    ((x) == PWC_LVD2_FLAG_DETECT))

/* Parameter validity check for LVD flag. */
#define IS_PWC_LVD_GET_FLAG(x)                                                  \
(   ((x) != 0x00U)                                  &&                          \
    (((x) | PWC_LVD_FLAG_MASK) == PWC_LVD_FLAG_MASK))

/* Parameter validity check for power down mode wake up event with trigger. */
#define IS_PWC_WAKEUP_TRIG_EVT(x)                                               \
(   ((x) != 0x00U)                                  &&                          \
    (((x) | PWC_PD_WKUP_TRIG_ALL) == PWC_PD_WKUP_TRIG_ALL))

/* Parameter validity check for power down mode wake up trigger edge. */
#define IS_PWC_WAKEUP_TRIG(x)                                                   \
(   ((x) == PWC_PD_WKUP_TRIG_FALLING)               ||                          \
    ((x) == PWC_PD_WKUP_TRIG_RISING))

/* Parameter validity check for wake up flag. */
#define IS_PWC_WKUP_FLAG(x)                                                     \
(   ((x) != 0x00U)                                  &&                          \
    (((x) | PWC_PD_WKUP_FLAG_ALL) == PWC_PD_WKUP_FLAG_ALL))

/* Parameter validity check for stop mode drive capacity. */
#define IS_PWC_STOP_DRV(drv)                                                    \
(   ((drv) == PWC_STOP_DRV_HIGH)                    ||                          \
    ((drv) == PWC_STOP_DRV_LOW))

/* Parameter validity check for clock setting after wake-up from stop mode. */
#define IS_PWC_STOP_CLK(x)                                                      \
(   ((x) == PWC_STOP_CLK_KEEP)                      ||                          \
    ((x) == PWC_STOP_CLK_MRC))

/* Parameter validity check for flash wait setting after wake-up from stop mode. */
#define IS_PWC_STOP_FLASH_WAIT(x)                                               \
(   ((x)== PWC_STOP_FLASH_WAIT_ON)                  ||                          \
    ((x)== PWC_STOP_FLASH_WAIT_OFF))

#define IS_PWC_LDO_SEL(x)                                                       \
(   ((x) != 0x00U)                                  &&                          \
    (((x) | PWC_LDO_MASK) == PWC_LDO_MASK))

/* Parameter validity check for WKT Clock Source. */
#define IS_PWC_WKT_CLK_SRC(x)                                                   \
(   ((x)== PWC_WKT_CLK_SRC_64HZ)                    ||                          \
    ((x)== PWC_WKT_CLK_SRC_XTAL32)                  ||                          \
    ((x)== PWC_WKT_CLK_SRC_LRC))

/* Parameter validity check for WKT Comparision Value. */
#define IS_PWC_WKT_COMPARISION_VALUE(x)             ((x) <= 0x0FFFU)

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup PWC_Local_Variables PWC Local Variables
 * @{
 */
static uint32_t NVIC_ISER_BAK[5];
static uint8_t  m_u8HrcState = 0U;
static uint8_t  m_u8MrcState = 0U;
static uint8_t  m_u8WkupIntCount = 0U;
static uint8_t  m_u8StopFlag = 0U;
static uint8_t  m_u8SysClockSource = 1U;
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup PWC_Local_Functions PWC Local Functions
 * @{
 */

/**
 * @brief  Select system clock source.
 * @param  u8SysSrc     The system clock source.
 * @retval None
 * @note   Must close all of the fcg register before switch system clock source.
 **        This function only be called in func. PWC_ClockBackup and
 **        PWC_ClockRecover.
 **        If need to switch system clock please call CLK_SetSysClkSource.
 */
static void PWC_SetSysClk(uint8_t u8SysSrc)
{
    __IO uint32_t fcg0 = CM_PWC->FCG0;
    __IO uint32_t fcg1 = CM_PWC->FCG1;
    __IO uint32_t fcg2 = CM_PWC->FCG2;
    __IO uint32_t fcg3 = CM_PWC->FCG3;

    DDL_ASSERT(IS_PWC_CLK_UNLOCKED());

    /* Only current system clock source or target system clock source is MPLL
    need to close fcg0~fcg3 and open fcg0~fcg3 during switch system clock source.
    We need to backup fcg0~fcg3 before close them. */
    if ((PWC_SYSCLK_SRC_PLL == (CM_CMU->CKSWR & CMU_CKSWR_CKSW)) || (PWC_SYSCLK_SRC_PLL == u8SysSrc)) {
        /* Close fcg0~fcg3. */
        CM_PWC->FCG0 = 0xFFFFFAEEUL;
        CM_PWC->FCG1 = 0xFFFFFFFFUL;
        CM_PWC->FCG2 = 0xFFFFFFFFUL;
        CM_PWC->FCG3 = 0xFFFFFFFFUL;

        DDL_DelayUS(1UL);
    }

    WRITE_REG8(CM_CMU->CKSWR, u8SysSrc);

    /* update system clock frequency. */
    SystemCoreClockUpdate();

    DDL_DelayUS(1UL);

    /* Open fcg0~fcg3. */
    CM_PWC->FCG0 = fcg0;
    CM_PWC->FCG1 = fcg1;
    CM_PWC->FCG2 = fcg2;
    CM_PWC->FCG3 = fcg3;

    DDL_DelayUS(1UL);
}

/**
 * @brief  Backup HRC/MRC state and system clock , enable HRC/MRC ,set MRC as
 *         system clock before enter stop mode.
 * @param  None
 * @retval None
 */
static void PWC_ClockBackup(void)
{
    __IO uint32_t timeout = 0UL;
    uint8_t u8State;

    DDL_ASSERT(IS_PWC_CLK_UNLOCKED());

    /* HRC state backup. */
    m_u8HrcState = READ_REG8_BIT(CM_CMU->HRCCR, CMU_HRCCR_HRCSTP);
    /* System clock backup*/
    m_u8SysClockSource = CM_CMU->CKSWR & CMU_CKSWR_CKSW;

    /* Enable HRC  before enter stop mode. */
    if (0U != m_u8HrcState) {
        CM_CMU->HRCCR = 0U;
        do {
            u8State = READ_REG8_BIT(CM_CMU->OSCSTBSR, CMU_OSCSTBSR_HRCSTBF);
            timeout++;
        } while ((timeout < 0x1000UL) && (u8State != CMU_OSCSTBSR_HRCSTBF));
    }

    /* When system clock source is HRC or MPLL, set MRC as system clock. . */
    if ((PWC_SYSCLK_SRC_HRC == m_u8SysClockSource) || (PWC_SYSCLK_SRC_PLL == m_u8SysClockSource)) {
        if (0U == READ_REG8_BIT(CM_PWC->STPMCR, PWC_STPMCR_CKSMRC)) {
            /* MRC state backup. */
            m_u8MrcState = READ_REG(CM_CMU->MRCCR);
            if (0x80U != m_u8MrcState) {
                CM_CMU->MRCCR = 0x80U;
                __NOP();
                __NOP();
                __NOP();
                __NOP();
                __NOP();
            }
        }
        PWC_SetSysClk(1U);
    }
}

/**
 * @brief  Recover HRC/MRC state and system clock after wake up stop mode.
 * @param  None
 * @retval None
 */
static void PWC_ClockRecover(void)
{
    DDL_ASSERT(IS_PWC_CLK_UNLOCKED());

    if (0U == READ_REG8_BIT(CM_PWC->STPMCR, PWC_STPMCR_CKSMRC)) {
        if ((PWC_SYSCLK_SRC_HRC == m_u8SysClockSource) || (PWC_SYSCLK_SRC_PLL == m_u8SysClockSource)) {
            /* Recover MRC state & system clock source. */
            PWC_SetSysClk(m_u8SysClockSource);
            WRITE_REG8(CM_CMU->MRCCR, m_u8MrcState);
        }
        /* Recover HRC state after wake up stop mode. */
        WRITE_REG8(CM_CMU->HRCCR, m_u8HrcState);
    }
    /* Update system clock */
    SystemCoreClockUpdate();
}
/**
 * @}
 */

/**
 * @defgroup PWC_Global_Functions PWC Global Functions
 * @{
 */
/**
 * @brief  Enter power down mode.
 * @param  None
 * @retval None
 */
__RAM_FUNC void PWC_PD_Enter(void)
{
    WRITE_REG16(CM_PWC->FPRC, PWC_UNLOCK_CODE1);

    if (PWC_PWRC0_PDMDS_1 == READ_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_PDMDS_1)) {
        SET_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_VVDRSD);
    }

    CLR_REG8_BIT(CM_PWC->PVDCR1, PWC_PVDCR1_PVD1IRS | PWC_PVDCR1_PVD2IRS);
    SET_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);

    __disable_irq();
    SET_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_PWDN);
    for (uint8_t i = 0U; i < 10U; i++) {
        __NOP();
    }
    __enable_irq();

    __WFI();
}

/**
 * @brief  NVIC backup and disable before entry from stop mode
 * @param  None
 * @retval None
 */
void PWC_STOP_NvicBackup(void)
{
    uint8_t u8Count;
    __IO uint32_t *INTC_SELx;
    uint32_t u32WakeupSrc;

    /* Backup NVIC set enable register for IRQ0~143*/
    for (u8Count = 0U; u8Count < sizeof(NVIC_ISER_BAK) / sizeof(uint32_t); u8Count++) {
        NVIC_ISER_BAK[u8Count] = NVIC->ISER[u8Count];
    }

    /* Disable share vector */
    for (u8Count = 128U; u8Count < 144U; u8Count++) {
        NVIC_DisableIRQ((IRQn_Type)u8Count);
    }

    for (u8Count = 0U; u8Count < 128U; u8Count++) {
        INTC_SELx = (__IO uint32_t *)((uint32_t)(&CM_INTC->SEL0) + (4UL * u8Count));
        /* Disable NVIC if it is the wake up-able source from stop mode */
        u32WakeupSrc = (uint32_t)(*INTC_SELx) & INTC_SEL_INTSEL;
        if (IS_PWC_STOP_WKUP_SRC((en_int_src_t)u32WakeupSrc)) {
            switch (u32WakeupSrc) {
                case INT_SRC_USART1_WUPI:
                    if (0UL == bCM_INTC->WUPEN_b.RXWUEN) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_TMR0_1_CMP_A:
                    if (0UL == bCM_INTC->WUPEN_b.TMR0WUEN) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_RTC_ALM:
                    if (0UL == bCM_INTC->WUPEN_b.RTCALMWUEN) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_RTC_PRD:
                    if (0UL == bCM_INTC->WUPEN_b.RTCPRDWUEN) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_WKTM_PRD:
                    if (0UL == bCM_INTC->WUPEN_b.WKTMWUEN) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_CMP1:
                    if (0UL == bCM_INTC->WUPEN_b.CMPI0WUEN) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_LVD1:
                    if (0UL == bCM_INTC->WUPEN_b.PVD1WUEN) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_LVD2:
                    if (0UL == bCM_INTC->WUPEN_b.PVD2WUEN) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_SWDT_REFUDF:
                    if (0UL == bCM_INTC->WUPEN_b.SWDTWUEN) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ0:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN0) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ1:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN1) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ2:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN2) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ3:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN3) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ4:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN4) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ5:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN5) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ6:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN6) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ7:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN7) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ8:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN8) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ9:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN9) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ10:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN10) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ11:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN11) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ12:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN12) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ13:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN13) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ14:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN14) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                case INT_SRC_PORT_EIRQ15:
                    if (0UL == bCM_INTC->WUPEN_b.EIRQWUEN15) {
                        NVIC_DisableIRQ((IRQn_Type)u8Count);
                    }
                    break;
                default:
                    break;
            }
        } else if ((uint32_t)INT_SRC_MAX != u32WakeupSrc) {
            /* Disable NVIC for all none-wake up source */
            NVIC_DisableIRQ((IRQn_Type)u8Count);
        } else {
            ;
        }
    }
}

/**
 * @brief  NVIC recover after wake up from stop mode
 * @param  None
 * @retval None
 */
void PWC_STOP_NvicRecover(void)
{
    uint8_t u8Count;

    for (u8Count = 0U; u8Count < sizeof(NVIC_ISER_BAK) / sizeof(uint32_t); u8Count++) {
        NVIC->ISER[u8Count] = NVIC_ISER_BAK[u8Count];
    }
}

/**
 * @brief  Clock backup before enter stop mode and mark it.
 * @param  None
 * @retval None
 */
void PWC_STOP_ClockBackup(void)
{
    /* Disable all interrupt to ensure the following operation continued. */
    __disable_irq();

    /* HRC/MRC backup and switch system clock as MRC before entry from stop mode. */
    PWC_ClockBackup();

    /* Mark the system clock has been switch as MRC, and will enter the stop mode. */
    m_u8StopFlag = 1U;

    /* Enable all interrupt. */
    __enable_irq();
}

/**
 * @brief  Clock recover after wake up stop mode.
 * @param  None
 * @retval None
 */
void PWC_STOP_ClockRecover(void)
{
    /* Disable all interrupt to ensure the following operation continued. */
    __disable_irq();

    /* Mark the system clock will be switch as MRC, and has waked_up from stop mode. */
    m_u8StopFlag = 0U;

    /* Recover HRC/MRC state and system clock after wake up stop mode. */
    PWC_ClockRecover();

    /* Enable all interrupt. */
    __enable_irq();
}

/**
 * @brief  Clock backup before exit wake up interrupt.
 * @param  None
 * @retval None
 */
void PWC_STOP_IrqClockBackup(void)
{
    if ((1UL == m_u8StopFlag) && (1UL == m_u8WkupIntCount)) {
        /* HRC/MRC backup and switch system clock as MRC. */
        PWC_ClockBackup();
    }
    m_u8WkupIntCount--;
}

/**
 * @brief  Clock recover after enter wake up interrupt.
 * @param  None
 * @retval None
 */
void PWC_STOP_IrqClockRecover(void)
{
    /* The variable to display how many waked_up interrupt has been occurred
       simultaneously and to decided whether backup clock before exit wake_up
       interrupt. */
    m_u8WkupIntCount++;

    if (1UL == m_u8StopFlag) {
        /* Recover HRC/MRC state and system clock. */
        PWC_ClockRecover();
    }
}

/**
 * @brief  Enter stop mode.
 * @param  [in] u8StopType specifies the XTAL initial config.
 *   @arg  PWC_STOP_WFI             Enter stop mode by WFI, and wake-up by interrupt handle.
 *   @arg  PWC_STOP_WFE_INT         Enter stop mode by WFE, and wake-up by interrupt request.
 *   @arg  PWC_STOP_WFE_EVT         Enter stop mode by WFE, and wake-up by event.
 * @retval None
 */
void PWC_STOP_Enter(uint8_t u8StopType)
{

    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_STOP_TYPE(u8StopType));

    /* NVIC backup and disable before entry from stop mode.*/
    PWC_STOP_NvicBackup();
    /* Clock backup and switch system clock as MRC before entry from stop mode. */
    PWC_STOP_ClockBackup();

    SET_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);
    CLR_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_PWDN);
    if (PWC_STOP_WFI == u8StopType) {
        __WFI();
    } else {
        if (PWC_STOP_WFE_INT == u8StopType) {
            SET_REG32_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
        } else {
            CLR_REG32_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
        }
        __SEV();
        __WFE();
        __WFE();
    }
    /* Recover HRC/MRC state and system clock after wake up from stop mode. */
    PWC_STOP_ClockRecover();
    /* NVIC recover after wake up from stop mode. */
    PWC_STOP_NvicRecover();
}

/**
 * @brief  Enter sleep mode.
 * @param  None
 * @retval None
 */
void PWC_SLEEP_Enter(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    CLR_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);
    CLR_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_PWDN);

    __WFI();
}

/**
 * @brief  Configure ram run mode.
 * @param  [in] u16Mode  Specifies the mode to run.
 *  @arg    PWC_RAM_HIGH_SPEED
 *  @arg    PWC_RAM_ULOW_SPEED
 * @retval None
 */
void PWC_RamModeConfig(uint16_t u16Mode)
{
    DDL_ASSERT(IS_PWC_RAM_MD(u16Mode));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG16(CM_PWC->RAMOPM, u16Mode);
}

/**
 * @brief  Initialize LVD config structure. Fill each pstcLvdInit with default value
 * @param  [in] pstcLvdInit Pointer to a stc_pwc_lvd_init_t structure that contains configuration information.
 * @retval int32_t:
 *          - LL_OK: LVD structure initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t PWC_LVD_StructInit(stc_pwc_lvd_init_t *pstcLvdInit)
{
    int32_t i32Ret = LL_OK;
    /* Check if pointer is NULL */
    if (NULL == pstcLvdInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* RESET LVD init structure parameters values */
        pstcLvdInit->u32State              = PWC_LVD_OFF;
        pstcLvdInit->u32CompareOutputState = PWC_LVD_CMP_OFF;
        pstcLvdInit->u32ExceptionType      = PWC_LVD_EXP_TYPE_NONE;
        pstcLvdInit->u32Filter             = PWC_LVD_FILTER_OFF;
        pstcLvdInit->u32FilterClock        = PWC_LVD_FILTER_LRC_MUL2;
        pstcLvdInit->u32ThresholdVoltage   = PWC_LVD_THRESHOLD_LVL0;
    }
    return i32Ret;
}

/**
 * @brief LVD configuration.
 * @param [in] u8Ch LVD channel @ref PWC_LVD_Channel.
 * @param [in] pstcLvdInit Pointer to a stc_pwc_lvd_init_t structure that contains configuration information.
 * @retval int32_t:
 *          - LL_OK: LVD initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t PWC_LVD_Init(uint8_t u8Ch, const stc_pwc_lvd_init_t *pstcLvdInit)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcLvdInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_PWC_LVD_UNLOCKED());
        DDL_ASSERT(IS_PWC_LVD_CH(u8Ch));
        DDL_ASSERT(IS_PWC_LVD_EN(pstcLvdInit->u32State));
        DDL_ASSERT(IS_PWC_LVD_EXP_TYPE(pstcLvdInit->u32ExceptionType));
        DDL_ASSERT(IS_PWC_LVD_CMP_EN(pstcLvdInit->u32CompareOutputState));
        DDL_ASSERT(IS_PWC_LVD_FILTER_EN(pstcLvdInit->u32Filter));
        DDL_ASSERT(IS_PWC_LVD_FILTER_CLK(pstcLvdInit->u32FilterClock));
        DDL_ASSERT(IS_PWC_LVD_THRESHOLD_VOLTAGE(pstcLvdInit->u32ThresholdVoltage));

        /* disable filter function in advance */
        SET_REG8_BIT(CM_PWC->PVDFCR, (PWC_PVDFCR_PVD1NFDIS << PWC_LVD_BIT_OFFSET(u8Ch)));
        MODIFY_REG8(CM_PWC->PVDFCR, (PWC_PVDFCR_PVD1NFDIS | PWC_PVDFCR_PVD1NFCKS) << PWC_LVD_BIT_OFFSET(u8Ch), \
                    (pstcLvdInit->u32Filter | pstcLvdInit->u32FilterClock) << PWC_LVD_BIT_OFFSET(u8Ch));
        /* Config LVD threshold voltage */
        MODIFY_REG8(CM_PWC->PVDLCR, PWC_PVDLCR_PVD1LVL << PWC_LVD_BIT_OFFSET(u8Ch), \
                    pstcLvdInit->u32ThresholdVoltage << PWC_LVD_BIT_OFFSET(u8Ch));
        /* Enable LVD */
        MODIFY_REG8(CM_PWC->PVDCR0, PWC_PVDCR0_PVD1EN << u8Ch, pstcLvdInit->u32State << u8Ch);
        /* Enable compare output */
        MODIFY_REG8(CM_PWC->PVDCR1, PWC_PVDCR1_PVD1CMPOE << PWC_LVD_BIT_OFFSET(u8Ch), \
                    pstcLvdInit->u32CompareOutputState << PWC_LVD_BIT_OFFSET(u8Ch));
        /* config PVDIRE & PWC_PVDCR1_PVD1IRS while PVDEN & PVDCMPOE enable */
        MODIFY_REG8(CM_PWC->PVDCR1, (PWC_PVDCR1_PVD1IRE | PWC_PVDCR1_PVD1IRS) << PWC_LVD_BIT_OFFSET(u8Ch), \
                    (pstcLvdInit->u32ExceptionType & 0xFFU) << PWC_LVD_BIT_OFFSET(u8Ch));
        MODIFY_REG8(CM_PWC->PVDICR, PWC_PVDICR_PVD1NMIS <<  PWC_LVD_BIT_OFFSET(u8Ch), \
                    ((pstcLvdInit->u32ExceptionType >> PWC_LVD_EXP_NMI_POS) & 0xFFU) << PWC_LVD_BIT_OFFSET(u8Ch));

    }
    return i32Ret;
}

/**
 * @brief De-initialize PWC LVD.
 * @param [in] u8Ch LVD channel @ref PWC_LVD_Channel.
 * @retval None
 */
void PWC_LVD_DeInit(uint8_t u8Ch)
{
    DDL_ASSERT(IS_PWC_LVD_CH(u8Ch));
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());

    /* Disable LVD */
    CLR_REG_BIT(CM_PWC->PVDCR0, PWC_PVDCR0_PVD1EN << u8Ch);
    /* Disable Ext-Vcc */
    if (PWC_LVD_CH2 == u8Ch) {
        CLR_REG8_BIT(CM_PWC->PVDCR0, PWC_PVDCR0_EXVCCINEN);
    } else {
        /* rsvd */
    }
    /* Reset filter */
    CLR_REG8_BIT(CM_PWC->PVDFCR, (PWC_PVDFCR_PVD1NFDIS | PWC_PVDFCR_PVD1NFCKS)  << PWC_LVD_BIT_OFFSET(u8Ch));
    /* Reset configure */
    CLR_REG8_BIT(CM_PWC->PVDCR1, (PWC_PVDCR1_PVD1IRE | PWC_PVDCR1_PVD1IRS | PWC_PVDCR1_PVD1CMPOE) << \
                 PWC_LVD_BIT_OFFSET(u8Ch));
    CLR_REG8_BIT(CM_PWC->PVDICR, PWC_PVDICR_PVD1NMIS << PWC_LVD_BIT_OFFSET(u8Ch));
    /* Reset threshold voltage */
    CLR_REG8_BIT(CM_PWC->PVDLCR, PWC_PVDLCR_PVD1LVL << PWC_LVD_BIT_OFFSET(u8Ch));
}

/**
 * @brief  Enable or disable LVD.
 * @param  [in] u8Ch Specifies which channel to operate. @ref PWC_LVD_Channel.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_LVD_Cmd(uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_LVD_CH(u8Ch));
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());

    if (ENABLE == enNewState) {
        SET_REG_BIT(PWC_LVD_EN_REG, PWC_LVD_EN_BIT << PWC_LVD_EN_BIT_OFFSET(u8Ch));
    } else {
        CLR_REG_BIT(PWC_LVD_EN_REG, PWC_LVD_EN_BIT << PWC_LVD_EN_BIT_OFFSET(u8Ch));
    }
}

/**
 * @brief  Enable or disable LVD external input.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note   While enable external input, should choose PWC_LVD_CH2 to initialize and threshold voltage must set PWC_LVD_EXTVCC
 */
void PWC_LVD_ExtInputCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());

    if (ENABLE == enNewState) {
        SET_REG_BIT(PWC_LVD_EXT_INPUT_EN_REG, PWC_LVD_EXT_INPUT_EN_BIT);
    } else {
        CLR_REG_BIT(PWC_LVD_EXT_INPUT_EN_REG, PWC_LVD_EXT_INPUT_EN_BIT);
    }
}

/**
 * @brief  Enable or disable LVD compare output.
 * @param  [in] u8Ch Specifies which channel to operate. @ref PWC_LVD_Channel.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_LVD_CompareOutputCmd(uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_LVD_CH(u8Ch));
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());

    if (ENABLE == enNewState) {
        SET_REG_BIT(PWC_LVD_CMP_OUTPUT_EN_REG, PWC_LVD_CMP_OUTPUT_EN_BIT << PWC_LVD_BIT_OFFSET(u8Ch));
    } else {
        CLR_REG_BIT(PWC_LVD_CMP_OUTPUT_EN_REG, PWC_LVD_CMP_OUTPUT_EN_BIT << PWC_LVD_BIT_OFFSET(u8Ch));
    }
}

/**
 * @brief  Enable or disable LVD digital filter.
 * @param  [in] u8Ch Specifies which channel to operate. @ref PWC_LVD_Channel.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_LVD_DigitalFilterCmd(uint8_t u8Ch, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_LVD_CH(u8Ch));
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());

    if (ENABLE == enNewState) {
        CLR_REG_BIT(PWC_LVD_FILTER_EN_REG, PWC_LVD_FILTER_EN_BIT << PWC_LVD_BIT_OFFSET(u8Ch));
    } else {
        SET_REG_BIT(PWC_LVD_FILTER_EN_REG, PWC_LVD_FILTER_EN_BIT << PWC_LVD_BIT_OFFSET(u8Ch));
    }
}

/**
 * @brief  Enable or disable LVD compare output.
 * @param  [in] u8Ch Specifies which channel to operate. @ref PWC_LVD_Channel.
 * @param  [in] u32Clock Specifies filter clock. @ref PWC_LVD_DFS_Clk_Sel
 * @retval None
 */
void PWC_LVD_SetFilterClock(uint8_t u8Ch, uint32_t u32Clock)
{
    DDL_ASSERT(IS_PWC_LVD_CH(u8Ch));
    DDL_ASSERT(IS_PWC_LVD_FILTER_CLK(u32Clock));
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());
    MODIFY_REG8(CM_PWC->PVDFCR, PWC_PVDFCR_PVD1NFCKS << PWC_LVD_BIT_OFFSET(u8Ch), \
                u32Clock << PWC_LVD_BIT_OFFSET(u8Ch));
}

/**
 * @brief Set LVD threshold voltage.
 * @param  [in] u8Ch        Specifies which channel to operate. @ref PWC_LVD_Channel.
 * @param  [in] u32Voltage  Specifies threshold voltage. @ref PWC_LVD_Detection_Voltage_Sel
 * @retval None
 * @note    While PWC_LVD_CH2, PWC_LVD_EXTVCC only valid while EXTINPUT enable.
 */
void PWC_LVD_SetThresholdVoltage(uint8_t u8Ch, uint32_t u32Voltage)
{
    DDL_ASSERT(IS_PWC_LVD_CH(u8Ch));
    DDL_ASSERT(IS_PWC_LVD_THRESHOLD_VOLTAGE(u32Voltage));
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());

    MODIFY_REG8(CM_PWC->PVDLCR, (PWC_PVDLCR_PVD1LVL << PWC_LVD_BIT_OFFSET(u8Ch)), \
                u32Voltage << PWC_LVD_BIT_OFFSET(u8Ch));
}

/**
 * @brief  Get LVD flag.
 * @param  [in] u8Flag LVD flag to be get @ref PWC_LVD_Flag
 * @retval An @ref en_flag_status_t enumeration value
 * @note   PVDxDETFLG is available when PVDCR0.PVDxEN and PVDCR1.PVDxCMPOE are set to '1'
 */
en_flag_status_t PWC_LVD_GetStatus(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_LVD_GET_FLAG(u8Flag));
    return ((0x00U != READ_REG8_BIT(PWC_LVD_STATUS_REG, u8Flag)) ? SET : RESET);
}

/**
 * @brief  Clear LVD flag.
 * @param  [in] u8Flag LVD flag to be get @ref PWC_LVD_Flag
 *  @arg      PWC_LVD1_FLAG_DETECT
 *  @arg      PWC_LVD2_FLAG_DETECT
 * @retval None
 * @note   PWC_LVD2_FLAG_DETECT only valid
 */
void PWC_LVD_ClearStatus(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());
    DDL_ASSERT(IS_PWC_LVD_CLR_FLAG(u8Flag));

    u8Flag = u8Flag >> PWC_PVDDSR_PVD1DETFLG_POS;
    CLR_REG8_BIT(PWC_LVD_STATUS_REG, u8Flag);
}

/**
 * @brief  LDO(HRC & PLL) command.
 * @param  [in] u16Ldo  Specifies the ldo to command.
 *  @arg    PWC_LDO_PLL
 *  @arg    PWC_LDO_HRC
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_LDO_Cmd(uint16_t u16Ldo, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_LDO_SEL(u16Ldo));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        CLR_REG8_BIT(CM_PWC->PWRC1, u16Ldo);
    } else {
        SET_REG8_BIT(CM_PWC->PWRC1, u16Ldo);
    }
}

/**
 * @brief  Switch high speed to ultra low speed, set the drive ability.
 * @param  None
 * @retval int32_t:
 *          - LL_OK: Mode switch successful.
 *          - LL_ERR: Mode switch failure, check whether EFM was unlocked please.
 * @note   Before calling this API, please switch system clock to the required
 *         low speed frequency in advance, and make sure NO any flash program
 *         or erase operation background.
 */
int32_t PWC_HighSpeedToLowSpeed(void)
{
    uint32_t u32To = PWC_MD_SWITCH_TIMEOUT2;

    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_EFM_UNLOCKED());

    WRITE_REG32(bCM_EFM->FRMC_b.LVM, ENABLE);
    WRITE_REG16(CM_PWC->RAMOPM, PWC_RAM_ULOW_SPEED);

    while (PWC_RAM_ULOW_SPEED != READ_REG16(CM_PWC->RAMOPM)) {
        WRITE_REG16(CM_PWC->RAMOPM, PWC_RAM_ULOW_SPEED);
        if (0UL == u32To--) {
            return LL_ERR;
        }
    }

    u32To = PWC_MD_SWITCH_TIMEOUT2;
    while (0UL == READ_REG32(bCM_EFM->FRMC_b.LVM)) {
        WRITE_REG32(bCM_EFM->FRMC_b.LVM, ENABLE);
        if (0UL == u32To--) {
            return LL_ERR;
        }
    }

    MODIFY_REG8(CM_PWC->PWRC2, PWC_PWRC2_DDAS | PWC_PWRC2_DVS, PWC_PWRC2_DDAS_3 | PWC_PWRC2_DVS_1);
    WRITE_REG8(CM_PWC->MDSWCR, PWC_MD_SWITCH_CMD);

    /* Delay 30uS*/
    DDL_DelayUS(PWC_MD_SWITCH_TIMEOUT);

    return LL_OK;
}

/**
 * @brief  Switch ultra low speed to high speed, set the drive ability.
 * @param  None
 * @retval int32_t:
 *          - LL_OK: Mode switch successful.
 *          - LL_ERR: Mode switch failure, check whether EFM was unlocked please.
 * @note   After calling this API, the system clock is able to switch high frequency.
 */
/**
 * @brief  Switch ultra low speed to high speed, set the drive ability.
 * @param  None
 * @retval int32_t:
 *          - LL_OK: Mode switch successful.
 *          - LL_ERR: Mode switch failure, check whether EFM was unlocked please.
 * @note   After calling this API, the system clock is able to switch high frequency.
 */
int32_t PWC_LowSpeedToHighSpeed(void)
{
    uint32_t u32To = PWC_MD_SWITCH_TIMEOUT2;

    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_EFM_UNLOCKED());
    SET_REG8_BIT(CM_PWC->PWRC2, PWC_PWRC2_DDAS | PWC_PWRC2_DVS);
    WRITE_REG8(CM_PWC->MDSWCR, PWC_MD_SWITCH_CMD);

    /* Delay 30uS*/
    DDL_DelayUS(PWC_MD_SWITCH_TIMEOUT);

    WRITE_REG32(bCM_EFM->FRMC_b.LVM, DISABLE);
    WRITE_REG16(CM_PWC->RAMOPM, PWC_RAM_HIGH_SPEED);

    while (PWC_RAM_HIGH_SPEED != READ_REG16(CM_PWC->RAMOPM)) {
        WRITE_REG16(CM_PWC->RAMOPM, PWC_RAM_HIGH_SPEED);
        if (0UL == u32To--) {
            return LL_ERR;
        }
    }

    u32To = PWC_MD_SWITCH_TIMEOUT2;
    while (0UL != READ_REG32(bCM_EFM->FRMC_b.LVM)) {
        WRITE_REG32(bCM_EFM->FRMC_b.LVM, DISABLE);
        if (0UL == u32To--) {
            return LL_ERR;
        }
    }

    return LL_OK;
}

/**
 * @brief  Switch high speed to high performance, set the drive ability.
 * @param  None
 * @retval int32_t:
 *          - LL_OK: Mode switch successful.
 *          - LL_ERR: Mode switch failure, check whether EFM was unlocked please.
 * @note   After calling this API, the system clock is able to switch high frequency..
 */
int32_t PWC_HighSpeedToHighPerformance(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG8(CM_PWC->PWRC2, PWC_PWRC2_DDAS | PWC_PWRC2_DVS, PWC_PWRC2_DDAS);
    WRITE_REG8(CM_PWC->MDSWCR, PWC_MD_SWITCH_CMD);

    /* Delay 30uS*/
    DDL_DelayUS(PWC_MD_SWITCH_TIMEOUT);

    return LL_OK;
}

/**
 * @brief  Switch high performance to high speed, set the drive ability.
 * @param  None
 * @retval int32_t:
 *          - LL_OK: Mode switch successful.
 *          - LL_ERR: Mode switch failure, check whether EFM was unlocked please.
 * @note   Before calling this API, please switch system clock to the required
 *         low speed frequency in advance, and make sure NO any flash program
 *         or erase operation background.
 */
int32_t PWC_HighPerformanceToHighSpeed(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG8(CM_PWC->PWRC2, PWC_PWRC2_DDAS | PWC_PWRC2_DVS, PWC_PWRC2_DDAS | PWC_PWRC2_DVS);
    WRITE_REG8(CM_PWC->MDSWCR, PWC_MD_SWITCH_CMD);

    /* Delay 30uS*/
    DDL_DelayUS(PWC_MD_SWITCH_TIMEOUT);

    return LL_OK;
}

/**
 * @brief  Switch low speed to high performance, set the drive ability.
 * @param  None
 * @retval int32_t:
 *          - LL_OK: Mode switch successful.
 *          - LL_ERR: Mode switch failure, check whether EFM was unlocked please.
 * @note   After calling this API, the system clock is able to switch high frequency..
 */
int32_t PWC_LowSpeedToHighPerformance(void)
{
    uint32_t u32To;

    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_EFM_UNLOCKED());

    MODIFY_REG8(CM_PWC->PWRC2, PWC_PWRC2_DDAS | PWC_PWRC2_DVS, PWC_PWRC2_DDAS);
    WRITE_REG8(CM_PWC->MDSWCR, PWC_MD_SWITCH_CMD);

    /* Delay 30uS*/
    DDL_DelayUS(PWC_MD_SWITCH_TIMEOUT);

    WRITE_REG32(bCM_EFM->FRMC_b.LVM, DISABLE);
    WRITE_REG16(CM_PWC->RAMOPM, PWC_RAM_HIGH_SPEED);

    u32To = PWC_MD_SWITCH_TIMEOUT2;
    while (PWC_RAM_HIGH_SPEED != READ_REG16(CM_PWC->RAMOPM)) {
        WRITE_REG16(CM_PWC->RAMOPM, PWC_RAM_HIGH_SPEED);
        if (0UL == u32To--) {
            return LL_ERR;
        }
    }

    u32To = PWC_MD_SWITCH_TIMEOUT2;
    while (0UL != READ_REG32(bCM_EFM->FRMC_b.LVM)) {
        WRITE_REG32(bCM_EFM->FRMC_b.LVM, DISABLE);
        if (0UL == u32To--) {
            return LL_ERR;
        }
    }

    return LL_OK;
}

/**
 * @brief  Switch high performance to low speed, set the drive ability.
 * @param  None
 * @retval int32_t:
 *          - LL_OK: Mode switch successful.
 *          - LL_ERR: Mode switch failure, check whether EFM was unlocked please.
 * @note   Before calling this API, please switch system clock to the required
 *         low speed frequency in advance, and make sure NO any flash program
 *         or erase operation background..
 */
int32_t PWC_HighPerformanceToLowSpeed(void)
{
    uint32_t u32To;

    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_EFM_UNLOCKED());

    WRITE_REG32(bCM_EFM->FRMC_b.LVM, ENABLE);
    WRITE_REG16(CM_PWC->RAMOPM, PWC_RAM_ULOW_SPEED);

    u32To = PWC_MD_SWITCH_TIMEOUT2;
    while (PWC_RAM_ULOW_SPEED != READ_REG16(CM_PWC->RAMOPM)) {
        WRITE_REG16(CM_PWC->RAMOPM, PWC_RAM_ULOW_SPEED);
        if (0UL == u32To--) {
            return LL_ERR;
        }
    }

    u32To = PWC_MD_SWITCH_TIMEOUT2;
    while (0UL == READ_REG32(bCM_EFM->FRMC_b.LVM)) {
        WRITE_REG32(bCM_EFM->FRMC_b.LVM, ENABLE);
        if (0UL == u32To--) {
            return LL_ERR;
        }
    }

    MODIFY_REG8(CM_PWC->PWRC2, PWC_PWRC2_DDAS | PWC_PWRC2_DVS, PWC_PWRC2_DDAS_3 | PWC_PWRC2_DVS_1);
    WRITE_REG8(CM_PWC->MDSWCR, PWC_MD_SWITCH_CMD);

    /* Delay 30uS*/
    DDL_DelayUS(PWC_MD_SWITCH_TIMEOUT);

    return LL_OK;
}

/**
 * @brief  VDR area power down command.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 *  @arg    ENABLE:      Power down mode
 *  @arg    DISABLE:     Run mode
 * @retval None
 */
void PWC_PD_VdrCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        CLR_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_VVDRSD);
    } else {
        SET_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_VVDRSD);
    }
}

/**
 * @brief  Ram area power down command.
 * @param  [in] u32PeriphRam Specifies which ram to operate. @ref PWC_PD_Periph_Ram
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 *  @arg    ENABLE:      Power down mode
 *  @arg    DISABLE:     Run mode
 * @retval None
 */
void PWC_PD_PeriphRamCmd(uint32_t u32PeriphRam, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_PRAM_CONTROL(u32PeriphRam));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        CM_PWC->RAMPC0 |= u32PeriphRam;
    } else {
        CM_PWC->RAMPC0 &= ~u32PeriphRam;
    }
}

/**
 * @brief  Initialize Power down mode config structure. Fill each pstcPDModeConfig with default value
 * @param  [in] pstcPDModeConfig Pointer to a stc_pwc_pd_mode_config_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *          - LL_OK: Power down mode structure initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t PWC_PD_StructInit(stc_pwc_pd_mode_config_t *pstcPDModeConfig)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcPDModeConfig) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcPDModeConfig->u8IOState = PWC_PD_IO_KEEP1;
        pstcPDModeConfig->u8Mode = PWC_PD_MD1;
        pstcPDModeConfig->u8VcapCtrl = PWC_PD_VCAP_0P1UF;
    }
    return i32Ret;
}

/**
 * @brief  Power down mode config structure.
 * @param  [in] pstcPDModeConfig Pointer to a stc_pwc_pd_mode_config_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *          - LL_OK: Power down mode config successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t PWC_PD_Config(const stc_pwc_pd_mode_config_t *pstcPDModeConfig)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcPDModeConfig) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_PWC_UNLOCKED());

        MODIFY_REG8(CM_PWC->PWRC0, (PWC_PWRC0_IORTN | PWC_PWRC0_PDMDS),         \
                    (pstcPDModeConfig->u8IOState | pstcPDModeConfig->u8Mode));
        MODIFY_REG8(CM_PWC->PWRC3, PWC_PWRC3_PDTS, pstcPDModeConfig->u8VcapCtrl << PWC_PWRC3_PDTS_POS);
    }
    return i32Ret;
}

/**
 * @brief  Power down mode wake up event config.
 * @param  [in] u32Event Wakeup Event. @ref PWC_WKUP_Event_Sel
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_PD_WakeupCmd(uint32_t u32Event, en_functional_state_t enNewState)
{
    uint8_t u8Event0 = (uint8_t)u32Event;
    uint8_t u8Event1 = (uint8_t)(u32Event >> PWC_PD_WKUP1_POS);
    uint8_t u8Event2 = (uint8_t)(u32Event >> PWC_PD_WKUP2_POS);
    if (ENABLE == enNewState) {
        SET_REG8_BIT(CM_PWC->PDWKE0, u8Event0);
        SET_REG8_BIT(CM_PWC->PDWKE1, u8Event1);
        SET_REG8_BIT(CM_PWC->PDWKE2, u8Event2);
    } else {
        CLR_REG8_BIT(CM_PWC->PDWKE0, u8Event0);
        CLR_REG8_BIT(CM_PWC->PDWKE1, u8Event1);
        CLR_REG8_BIT(CM_PWC->PDWKE2, u8Event2);
    }
}

/**
 * @brief  Power down mode wake up event trigger config.
 * @param  [in] u8Event PVD and wake up pin. @ref PWC_WKUP_Trigger_Event_Sel
 * @param  [in] u8TrigEdge The trigger edge.
 *  @arg PWC_PD_WKUP_TRIG_FALLING
 *  @arg PWC_PD_WKUP_TRIG_RISING
 * @retval None
 */
void PWC_PD_SetWakeupTriggerEdge(uint8_t u8Event, uint8_t u8TrigEdge)
{
    DDL_ASSERT(IS_PWC_WAKEUP_TRIG_EVT(u8Event));
    DDL_ASSERT(IS_PWC_WAKEUP_TRIG(u8TrigEdge));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (PWC_PD_WKUP_TRIG_RISING == u8TrigEdge) {
        SET_REG8_BIT(CM_PWC->PDWKES, u8Event);
    } else {
        CLR_REG8_BIT(CM_PWC->PDWKES, u8Event);
    }
}

/**
 * @brief  Get wake up event flag.
 * @param  [in] u16Flag Wake up event. @ref PWC_WKUP_Event_Flag_Sel
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t PWC_PD_GetWakeupStatus(uint16_t u16Flag)
{
    uint8_t u8Flag0;
    uint8_t u8Flag1;

    DDL_ASSERT(IS_PWC_WKUP_FLAG(u16Flag));

    u8Flag0 = READ_REG8_BIT(CM_PWC->PDWKF0, u16Flag);
    u8Flag1 = READ_REG8_BIT(CM_PWC->PDWKF1, (u16Flag >> PWC_PD_WKUP_FLAG1_POS));

    return (((0U != u8Flag0) || (0U != u8Flag1)) ? SET : RESET);
}

/**
 * @brief  Clear wake up event flag.
 * @param  [in] u16Flag Wake up event. @ref PWC_WKUP_Event_Flag_Sel
 * @retval None
 */
void PWC_PD_ClearWakeupStatus(uint16_t u16Flag)
{
    uint8_t u8Flag0;
    uint8_t u8Flag1;

    DDL_ASSERT(IS_PWC_WKUP_FLAG(u16Flag));

    u8Flag0 = (uint8_t)u16Flag;
    u8Flag1 = (uint8_t)(u16Flag >> PWC_PD_WKUP_FLAG1_POS);

    CLR_REG8_BIT(CM_PWC->PDWKF0, u8Flag0);
    CLR_REG8_BIT(CM_PWC->PDWKF1, u8Flag1);
}

/**
 * @brief Stop mode config.
 * @param [in] pstcStopConfig Chip config before entry stop mode.
 *  @arg    u8StopDrv, MCU from which speed mode entry stop mode.
 *  @arg    u16Clock, System clock setting after wake-up from stop mode.
 *  @arg    u16FlashWait, Whether wait flash stable after wake-up from stop mode.
 *  @arg    u16ExBusHold, ExBus status in stop mode.
 * @retval int32_t:
 *          - LL_OK: Stop mode config successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t PWC_STOP_Config(const stc_pwc_stop_mode_config_t *pstcStopConfig)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcStopConfig) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {

        DDL_ASSERT(IS_PWC_UNLOCKED());

        DDL_ASSERT(IS_PWC_STOP_CLK(pstcStopConfig->u16Clock));
        DDL_ASSERT(IS_PWC_STOP_DRV(pstcStopConfig->u8StopDrv));
        DDL_ASSERT(IS_PWC_STOP_FLASH_WAIT(pstcStopConfig->u16FlashWait));
        MODIFY_REG8(CM_PWC->PWRC1, PWC_PWRC1_STPDAS, pstcStopConfig->u8StopDrv);
        MODIFY_REG16(CM_PWC->STPMCR, (PWC_STPMCR_CKSMRC | PWC_STPMCR_FLNWT), \
                     (pstcStopConfig->u16Clock | pstcStopConfig->u16FlashWait));

    }
    return i32Ret;
}

/**
 * @brief  Initialize stop mode config structure. Fill each pstcStopConfig with default value
 * @param  [in] pstcStopConfig Pointer to a stc_pwc_stop_mode_config_t structure that
 *                            contains configuration information.
 * @retval int32_t:
 *          - LL_OK: Stop down mode structure initialize successful
 *          - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t PWC_STOP_StructInit(stc_pwc_stop_mode_config_t *pstcStopConfig)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcStopConfig) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcStopConfig->u16Clock = PWC_STOP_CLK_KEEP;
        pstcStopConfig->u8StopDrv = PWC_STOP_DRV_HIGH;
        pstcStopConfig->u16FlashWait = PWC_STOP_FLASH_WAIT_ON;
    }
    return i32Ret;
}

/**
 * @brief Stop mode wake up clock config.
 * @param [in] u8Clock System clock setting after wake-up from stop mode. @ref PWC_STOP_CLK_Sel
 * @retval None
 */
void PWC_STOP_ClockSelect(uint8_t u8Clock)
{
    DDL_ASSERT(IS_PWC_STOP_CLK(u8Clock));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG16(CM_PWC->STPMCR, PWC_STPMCR_CKSMRC, (uint16_t)u8Clock);

}

/**
 * @brief  Stop mode wake up flash wait config.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_STOP_FlashWaitCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        CLR_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_FLNWT);
    } else {
        SET_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_FLNWT);
    }
}

/**
 * @brief Stop mode driver capacity config.
 * @param [in] u8StopDrv Drive capacity while enter stop mode.
 *  @arg    PWC_STOP_DRV_HIGH
 *  @arg    PWC_STOP_DRV_LOW
 * @retval None
 */
void PWC_STOP_SetDrv(uint8_t u8StopDrv)
{
    DDL_ASSERT(IS_PWC_STOP_DRV(u8StopDrv));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG8(CM_PWC->PWRC1, PWC_PWRC1_STPDAS, u8StopDrv);
}

/**
 * @brief  PWC power monitor command.
 * @param  [in] enNewState      An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note   This monitor power is used for ADC and output to REGC pin.
 */
void PWC_PowerMonitorCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());
    if (ENABLE == enNewState) {
        SET_REG8_BIT(CM_PWC->PWCMR, PWC_PWCMR_ADBUFE);
    } else {
        CLR_REG8_BIT(CM_PWC->PWCMR, PWC_PWCMR_ADBUFE);
    }

}

/**
 * @brief  WKT Timer Initialize.
 * @param  [in] u16ClkSrc                Clock source.
 *         This parameter can be one of the values @ref PWC_WKT_Clock_Source.
 * @param  [in] u16CmpVal               Comparison value of the Counter.
 *  @arg    This parameter can be a number between Min_Data = 0 and Max_Data = 0xFFF.
 * @retval None
 */
void PWC_WKT_Config(uint16_t u16ClkSrc, uint16_t u16CmpVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_PWC_WKT_CLK_SRC(u16ClkSrc));
    DDL_ASSERT(IS_PWC_WKT_COMPARISION_VALUE(u16CmpVal));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG16(CM_PWC->WKTCR, (uint16_t)(u16ClkSrc | (u16CmpVal & PWC_WKTCR_WKTMCMP)));
}

/**
 * @brief  SET WKT Timer compare value.
 * @param  [in] u16CmpVal               Comparison value of the Counter.
 *  @arg    This parameter can be a number between Min_Data = 0 and Max_Data = 0xFFF.
 * @retval None
 */
void PWC_WKT_SetCompareValue(uint16_t u16CmpVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_PWC_WKT_COMPARISION_VALUE(u16CmpVal));
    DDL_ASSERT(IS_PWC_UNLOCKED());
    MODIFY_REG16(CM_PWC->WKTCR, PWC_WKTCR_WKTMCMP, u16CmpVal);
}

/**
 * @brief  Get WKT Timer compare value.
 * @param  None
 * @retval uint16_t                     WKT Compare value
 */
uint16_t PWC_WKT_GetCompareValue(void)
{
    uint16_t u16CmpVal;

    u16CmpVal = READ_REG16_BIT(CM_PWC->WKTCR, PWC_WKTCR_WKTMCMP);

    return u16CmpVal;
}

/**
 * @brief  ENABLE or DISABLE WKT Timer.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_WKT_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        MODIFY_REG16(CM_PWC->WKTCR, PWC_WKTCR_WKTCE, PWC_WKT_ON);
    } else {
        MODIFY_REG16(CM_PWC->WKTCR, PWC_WKTCR_WKTCE, PWC_WKT_OFF);
    }

}

/**
 * @brief  Get WKT Timer count match flag.
 * @param  None
 * @retval An @ref en_flag_status_t enumeration type value. enumeration value:
 */
en_flag_status_t PWC_WKT_GetStatus(void)
{
    en_flag_status_t enFlagState;

    enFlagState = (0U != READ_REG16_BIT(CM_PWC->WKTCR, PWC_WKTCR_WKOVF)) ? SET : RESET;

    return enFlagState;
}

/**
 * @brief  Clear WKT Timer count match flag.
 * @param  None
 * @retval None
 */
void PWC_WKT_ClearStatus(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());
    CLR_REG16_BIT(CM_PWC->WKTCR, PWC_WKTCR_WKOVF);
}

/**
 * @brief  ENABLE or DISABLE XTAL32 power.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 *  @arg    ENABLE:      Power on
 *  @arg    DISABLE:     Power off
 * @retval None
 */
void PWC_XTAL32_PowerCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        CLR_REG8_BIT(CM_PWC->XTAL32CS, PWC_XTAL32CS_CSDIS);
    } else {
        SET_REG_BIT(CM_PWC->XTAL32CS, PWC_XTAL32CS_CSDIS);
    }
}

/**
 * @brief  Ret_Sram area power command.
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 *  @arg    ENABLE:      Power on
 *  @arg    DISABLE:     Power off
 * @retval None
 */
void PWC_RetSram_PowerCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        CLR_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_RETRAMSD);
    } else {
        SET_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_RETRAMSD);
    }
}

/**
 * @}
 */

#endif  /* LL_PWC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
