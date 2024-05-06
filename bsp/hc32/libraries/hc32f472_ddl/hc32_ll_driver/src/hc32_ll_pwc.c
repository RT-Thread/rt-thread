/**
 *******************************************************************************
 * @file  hc32_ll_pwc.c
 * @brief This file provides firmware functions to manage the Power Control(PWC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2022-10-31       CDT             Bug fixed# PWC_PD_VdrCmd() and disable VDDR when enter PD3/4
   2023-06-30       CDT             Modify typo
                                    Add api PWC_LVD_DeInit()
                                    Add assert to API PWC_STOP_Enter()
                                    Modify API PWC_STOP_Enter() & add assert IS_PWC_STOP_TYPE()
   2023-12-15       CDT             Remove redundant assert
                                    Modify API PWC_PD_Enter() #use assert to replace the unlock, and add return value
                                    Refine PWC_SLEEP_Enter()
                                    Add API PWC_PD_SetIoState() & PWC_PD_SetMode()
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

#define PWC_MD_SWITCH_TIMEOUT           (30UL)
#define PWC_MD_SWITCH_TIMEOUT2          (0x1000UL)

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

#define PWC_RAM_MASK                    (PWC_RAMPC0_RAMPDC0 | PWC_RAMPC0_RAMPDC10)

#define PWC_PRAM_MASK                   (PWC_RAM_PD_CAN1  | PWC_RAM_PD_CAN2_3  |    \
                                         PWC_RAM_PD_CACHE | PWC_RAM_PD_USBFS)

#define PWC_LVD_FLAG_MASK               (PWC_LVD1_FLAG_MON | PWC_LVD1_FLAG_DETECT | \
                                         PWC_LVD2_FLAG_MON | PWC_LVD2_FLAG_DETECT)

#define PWC_LVD_EXP_NMI_POS             (8U)

/**
 * @defgroup PWC_Check_Parameters_Validity PWC Check Parameters Validity
 * @{
 */

/* Check PWC register lock status. */
#define IS_PWC_UNLOCKED()               ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)
/* Check PWC LVD register lock status. */
#define IS_PWC_LVD_UNLOCKED()           ((CM_PWC->FPRC & PWC_FPRC_FPRCB3) == PWC_FPRC_FPRCB3)

/* Parameter validity check for stop type */
#define IS_PWC_STOP_TYPE(x)                                                     \
(   ((x) == PWC_STOP_WFI)                           ||                          \
    ((x) == PWC_STOP_WFE_INT)                       ||                          \
    ((x) == PWC_STOP_WFE_EVT))

/* Parameter validity check for sleep type */
#define IS_PWC_SLEEP_TYPE(x)                                                    \
(   ((x) == PWC_SLEEP_WFI)                          ||                          \
    ((x) == PWC_SLEEP_WFE_INT)                      ||                          \
    ((x) == PWC_SLEEP_WFE_EVT))

/* Parameter validity check for internal RAM setting of power mode control */
#define IS_PWC_RAM_CONTROL(x)                                                   \
(   ((x) != 0x00UL)                                 &&                          \
    (((x) | PWC_RAM_MASK) == PWC_RAM_MASK))

/* Parameter validity check for peripheral RAM setting of power mode control */
#define IS_PWC_PRAM_CONTROL(x)                                                  \
(   ((x) != 0x00UL)                                 &&                          \
    (((x) | PWC_PRAM_MASK) == PWC_PRAM_MASK))

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

/* Parameter validity check for power down mode. */
#define IS_PWC_PD_MD(x)                                                         \
(   ((x) == PWC_PD_MD1)                             ||                          \
    ((x) == PWC_PD_MD2)                             ||                          \
    ((x) == PWC_PD_MD3)                             ||                          \
    ((x) == PWC_PD_MD4))

/* Parameter validity check for IO state while power down mode. */
#define IS_PWC_PD_IO_STATE(x)                                                   \
(   ((x) == PWC_PD_IO_KEEP1)                        ||                          \
    ((x) == PWC_PD_IO_KEEP2)                        ||                          \
    ((x) == PWC_PD_IO_HIZ))

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

/* Parameter validity check for clock setting after wake-up from stop mode. */
#define IS_PWC_STOP_CLK(x)                                                      \
(   ((x) == PWC_STOP_CLK_KEEP)                      ||                          \
    ((x) == PWC_STOP_CLK_MRC))

/* Parameter validity check for flash wait setting after wake-up from stop mode. */
#define IS_PWC_STOP_FLASH_WAIT(x)                                               \
(   ((x)== PWC_STOP_FLASH_WAIT_ON)                  ||                          \
    ((x)== PWC_STOP_FLASH_WAIT_OFF))

/* Parameter validity check for ex-bus setting in stop mode. */
#define IS_PWC_STOP_EXBUS(x)                                                    \
(   ((x)== PWC_STOP_EXBUS_HIZ)                      ||                          \
    ((x)== PWC_STOP_EXBUS_HOLD))

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

/* Parameter validity check for port reset event. */
#define IS_PWC_PORT_RST_EVT(x)                                                  \
(   ((x) != 0x00U)                                  &&                          \
    (((x) | PWC_PORT_RST_ALL) == PWC_PORT_RST_ALL))

/* Parameter validity check for DAC reset event. */
#define IS_PWC_DAC_RST_EVT(x)                                                   \
(   ((x) != 0x00U)                                  &&                          \
    (((x) | PWC_DAC_RST_ALL) == PWC_DAC_RST_ALL))

/* Parameter validity check for RTC clock selection. */
#define IS_PWC_RTC_CLK_SEL(x)                                                   \
(   ((x) == PWC_RTC_CLK_LRC)                        ||                          \
    ((x) == PWC_RTC_CLK_PIN)                        ||                          \
    ((x) == PWC_RTC_CLK_XTAL_DIV))

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

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup PWC_Global_Functions PWC Global Functions
 * @{
 */

/**
 * @brief  Enter power down mode.
 * @param  None
 * @retval int32_t:
 *          - LL_ERR_TIMEOUT:   Enter PD mode timeout
 * @note   Not return LL_OK because if enter PD mode ok, the MCU will shut down, and reset after woken-up.
 */
int32_t PWC_PD_Enter(void)
{
    int32_t i32Ret;
    uint32_t u32Timeout = 0UL;

    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());

    /* Ensure pvd not reset exception */
    CLR_REG8_BIT(CM_PWC->PVDCR1, PWC_PVDCR1_PVD1IRS | PWC_PVDCR1_PVD2IRS);
    for (; ;) {
        SET_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);
        SET_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_PWDN);
        __WFI();
        u32Timeout++;
        if (u32Timeout > 1000UL) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief  Enter stop mode.
 * @param  [in] u8StopType specifies the type of enter stop's command.
 *   @arg  PWC_STOP_WFI             Enter stop mode by WFI, and wake-up by interrupt handle.
 *   @arg  PWC_STOP_WFE_INT         Enter stop mode by WFE, and wake-up by interrupt request.
 *   @arg  PWC_STOP_WFE_EVT         Enter stop mode by WFE, and wake-up by event.
 * @retval None
 */
void PWC_STOP_Enter(uint8_t u8StopType)
{

    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_STOP_TYPE(u8StopType));
    DDL_ASSERT(0U == (CM_PWC->PWRC0 & PWC_PWRC0_PDMDS));

    SET_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);
    CLR_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_PWDN);
    if (PWC_STOP_WFI == u8StopType) {
        __WFI();
    } else {
        if (PWC_STOP_WFE_INT == u8StopType) {
            SET_REG32_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
        }
        __SEV();
        __WFE();
        __WFE();
    }

}

/**
 * @brief  Enter sleep mode.
 * @param  [in] u8SleepType specifies the type of enter sleep's command.
 *   @arg  PWC_SLEEP_WFI            Enter sleep mode by WFI, and wake-up by interrupt handle.
 *   @arg  PWC_SLEEP_WFE_INT        Enter sleep mode by WFE, and wake-up by interrupt request.
 *   @arg  PWC_SLEEP_WFE_EVT        Enter sleep mode by WFE, and wake-up by event.

 * @retval None
 */
void PWC_SLEEP_Enter(uint8_t u8SleepType)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_SLEEP_TYPE(u8SleepType));

    CLR_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);
    CLR_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_PWDN);

    if (PWC_SLEEP_WFI == u8SleepType) {
        __WFI();
    } else {
        if (PWC_SLEEP_WFE_INT == u8SleepType) {
            SET_REG32_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
        }
        __SEV();
        __WFE();
        __WFE();
    }
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
        pstcLvdInit->u32TriggerEdge        = PWC_LVD_TRIG_FALLING;
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
        DDL_ASSERT(IS_PWC_LVD_TRIG_EDGE(pstcLvdInit->u32TriggerEdge));

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
        MODIFY_REG8(CM_PWC->PVDICR, PWC_PVDICR_PVD1EDGS <<  PWC_LVD_BIT_OFFSET(u8Ch), \
                    pstcLvdInit->u32TriggerEdge << PWC_LVD_BIT_OFFSET(u8Ch));
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
    CLR_REG8_BIT(CM_PWC->PVDICR, (PWC_PVDICR_PVD1NMIS | PWC_PVDICR_PVD1EDGS) << PWC_LVD_BIT_OFFSET(u8Ch));
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
 */
void PWC_LVD_ClearStatus(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());
    DDL_ASSERT(IS_PWC_LVD_CLR_FLAG(u8Flag));

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
 * @brief  Switch ultra low speed to high speed, set the drive ability.
 * @param  None
 * @retval int32_t:
 *          - LL_OK: Mode switch successful.
 *          - LL_ERR: Mode switch failure, check whether EFM was unlocked please.
 * @note   After calling this API, the system clock is able to switch high frequency.
 */

/**
 * @brief  Ram area power down command.
 * @param  [in] u32Ram Specifies which ram to operate. @ref PWC_PD_Ram
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 *  @arg    ENABLE:      Power down mode
 *  @arg    DISABLE:     Run mode
 * @retval None
 */
void PWC_PD_RamCmd(uint32_t u32Ram, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_RAM_CONTROL(u32Ram));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        SET_REG8_BIT(CM_PWC->RAMPC0, u32Ram);
    } else {
        CLR_REG8_BIT(CM_PWC->RAMPC0, u32Ram);
    }
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
        CLR_REG8_BIT(CM_PWC->PWRC5, PWC_PWRC5_VVDRSD);
    } else {
        SET_REG8_BIT(CM_PWC->PWRC5, PWC_PWRC5_VVDRSD);
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
        SET_REG8_BIT(CM_PWC->PRAMLPC, u32PeriphRam);
    } else {
        CLR_REG8_BIT(CM_PWC->PRAMLPC, u32PeriphRam);
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
        DDL_ASSERT(IS_PWC_PD_IO_STATE(pstcPDModeConfig->u8IOState));
        DDL_ASSERT(IS_PWC_PD_MD(pstcPDModeConfig->u8Mode));

        MODIFY_REG8(CM_PWC->PWRC0, (PWC_PWRC0_IORTN | PWC_PWRC0_PDMDS),         \
                    (pstcPDModeConfig->u8IOState | pstcPDModeConfig->u8Mode));
    }
    return i32Ret;
}

/**
 * @brief  Set IO state while PD mode.
 * @param  [in] u8IoState IO state while power down mode
 *   @arg  PWC_PD_IO_KEEP1
 *   @arg  PWC_PD_IO_KEEP2
 *   @arg  PWC_PD_IO_HIZ
 * @retval None
 */
void PWC_PD_SetIoState(uint8_t u8IoState)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_PD_IO_STATE(u8IoState));

    MODIFY_REG8(CM_PWC->PWRC0, PWC_PWRC0_IORTN, u8IoState);
}

/**
 * @brief  Set power down mode.
 * @param  [in] u8PdMode Power down mode
 *   @arg  PWC_PD_MD1       Power down mode 1
 *   @arg  PWC_PD_MD2       Power down mode 2
 *   @arg  PWC_PD_MD3       Power down mode 3
 *   @arg  PWC_PD_MD4       Power down mode 4
 * @retval None
 */
void PWC_PD_SetMode(uint8_t u8PdMode)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());
    DDL_ASSERT(IS_PWC_PD_MD(u8PdMode));

    MODIFY_REG8(CM_PWC->PWRC0, PWC_PWRC0_PDMDS, u8PdMode);
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
        DDL_ASSERT(IS_PWC_STOP_FLASH_WAIT(pstcStopConfig->u16FlashWait));
        DDL_ASSERT(IS_PWC_STOP_EXBUS(pstcStopConfig->u16ExBusHold));
        MODIFY_REG16(CM_PWC->STPMCR, (PWC_STPMCR_EXBUSOE | PWC_STPMCR_CKSMRC | PWC_STPMCR_FLNWT), \
                     (pstcStopConfig->u16ExBusHold | pstcStopConfig->u16Clock | pstcStopConfig->u16FlashWait));

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
        pstcStopConfig->u16FlashWait = PWC_STOP_FLASH_WAIT_ON;
        pstcStopConfig->u16ExBusHold = PWC_STOP_EXBUS_HIZ;
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
 * @brief Stop mode ex-bus status config.
 * @param [in] u16ExBusHold ExBus status in stop mode.
 *  @arg   PWC_STOP_EXBUS_HIZ
 *  @arg   PWC_STOP_EXBUS_HOLD
 * @retval None
 */
void PWC_STOP_ExBusHoldConfig(uint16_t u16ExBusHold)
{
    DDL_ASSERT(IS_PWC_STOP_EXBUS(u16ExBusHold));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG16(CM_PWC->STPMCR, PWC_STPMCR_EXBUSOE, u16ExBusHold);
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
        SET_REG8_BIT(CM_PWC->PWRC4, PWC_PWRC4_ADBUFE);
    } else {
        CLR_REG8_BIT(CM_PWC->PWRC4, PWC_PWRC4_ADBUFE);
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
        CLR_REG8_BIT(CM_PWC->PWRC5, PWC_PWRC5_CSDIS);
    } else {
        SET_REG_BIT(CM_PWC->PWRC5, PWC_PWRC5_CSDIS);
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
        CLR_REG8_BIT(CM_PWC->PWRC5, PWC_PWRC5_RETRAMSD);
    } else {
        SET_REG8_BIT(CM_PWC->PWRC5, PWC_PWRC5_RETRAMSD);
    }
}

/**
 * @brief  Port reset event config.
 * @param  [in] u8Event Reset event. @ref PWC_Port_Reset_Sel
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_PortResetCmd(uint8_t u8Event, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_PORT_RST_EVT(u8Event));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        CLR_REG8_BIT(CM_PWC->PWRC6, u8Event);
    } else {
        SET_REG8_BIT(CM_PWC->PWRC6, u8Event);
    }
}

/**
 * @brief  Release port status.
 * @param  None
 * @retval None
 */
void PWC_ReleasePort(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    SET_REG8_BIT(CM_PWC->PWRC6, PWC_PWRC6_IORTNCLR);
}

/**
 * @brief  DAC reset event config.
 * @param  [in] u8Event Reset event. @ref PWC_Dac_Reset_Sel
 * @param  [in] enNewState An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_DacResetCmd(uint8_t u8Event, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_DAC_RST_EVT(u8Event));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        CLR_REG8_BIT(CM_PWC->PWRC6, u8Event);
    } else {
        SET_REG8_BIT(CM_PWC->PWRC6, u8Event);
    }
}

/**
 * @brief  Set RTC clock.
 * @param  [in] u8Clock Reset event. @ref PWC_Rtc_Clock_Sel
 * @retval None
 */
void PWC_SetRtcClock(uint8_t u8Clock)
{
    DDL_ASSERT(IS_PWC_RTC_CLK_SEL(u8Clock));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG8(CM_PWC->PWRC6, PWC_PWRC6_RTCCKSEL, u8Clock);
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
