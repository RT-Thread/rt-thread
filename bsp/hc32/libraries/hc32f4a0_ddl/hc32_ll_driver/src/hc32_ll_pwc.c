/**
 *******************************************************************************
 * @file  hc32_ll_pwc.c
 * @brief This file provides firmware functions to manage the Power Control(PWC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Refine API PWC_STOP_Enter()
   2022-10-31       CDT             Modify API PWC_HighSpeedToLowSpeed() base umRev1.13
   2023-01-15       CDT             Optimize API PWC_STOP_ClockSelect() & comment
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
#define PWC_BKRx(x)                     ((uint32_t)(&(CM_PWC->BKR0)) + ((uint32_t)(x) << 2U))

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

#define PWC_RAM_MASK                    (PWC_RAMPC0_RAMPDC0 | PWC_RAMPC0_RAMPDC1 |  \
                                         PWC_RAMPC0_RAMPDC2 | PWC_RAMPC0_RAMPDC3 |  \
                                         PWC_RAMPC0_RAMPDC4 | PWC_RAMPC0_RAMPDC5 |  \
                                         PWC_RAMPC0_RAMPDC6 | PWC_RAMPC0_RAMPDC7 |  \
                                         PWC_RAMPC0_RAMPDC8 | PWC_RAMPC0_RAMPDC9 |  \
                                         PWC_RAMPC0_RAMPDC10)

#define PWC_PRAM_MASK                   (PWC_RAM_PD_CAN1    | PWC_RAM_PD_CAN2  |    \
                                         PWC_RAM_PD_ETHERRX | PWC_RAM_PD_CACHE |    \
                                         PWC_RAM_PD_SDIO1   | PWC_RAM_PD_USBFS |    \
                                         PWC_RAM_PD_SDIO2   | PWC_RAM_PD_USBHS |    \
                                         PWC_RAM_PD_NFC     | PWC_RAM_PD_ETHERTX)

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
/* Parameter validity check for EFM lock status. */
#define IS_PWC_EFM_UNLOCKED()           (CM_EFM->FAPRT == 0x00000001UL)

/* Parameter validity check for stop type */
#define IS_PWC_STOP_TYPE(x)                                                     \
(   ((x) == PWC_STOP_WFI)                           ||                          \
    ((x) == PWC_STOP_WFE_INT)                       ||                          \
    ((x) == PWC_STOP_WFE_EVT))

/* Parameter validity check for internal RAM setting of power mode control */
#define IS_PWC_RAM_CONTROL(x)                                                   \
(   ((x) != 0x00UL)                                 &&                          \
    (((x) | PWC_RAM_MASK) == PWC_RAM_MASK))

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

/* Parameter validity check for ex-bus setting in stop mode. */
#define IS_PWC_STOP_EXBUS(x)                                                    \
(   ((x)== PWC_STOP_EXBUS_HIZ)                      ||                          \
    ((x)== PWC_STOP_EXBUS_HOLD))

/*  Parameter validity check for power monitor sel. */
#define IS_PWC_PWR_MON_SEL(x)                                                   \
(   ((x) == PWC_PWR_MON_IREF)                       ||                          \
    ((x) == PWC_PWR_MON_VBAT_DIV2))

/* Parameter validity check for VBAT Reference Voltage. */
#define IS_PWC_VBAT_REF_VOL(x)                                                  \
(   ((x) == PWC_VBAT_REF_VOL_2P1V)                  ||                          \
    ((x) == PWC_VBAT_REF_VOL_1P8V))

/* Parameter validity check for BACKUP RAM Flag. */
#define IS_PWC_BACKUP_RAM_FLAG(x)                                               \
(   0U != ((x) & (PWC_BACKUP_RAM_FLAG_RAMPDF | PWC_BACKUP_RAM_FLAG_RAMVALID)))

/* Parameter validity check for Backup Register Number. */
#define IS_PWC_BACKUP_REGISTER_NUMBER(x)            ((x) <= 127U)

#define IS_PWC_LDO_SEL(x)                                                       \
(   ((x) != 0x00U)                                  &&                          \
    (((x) | PWC_LDO_MASK) == PWC_LDO_MASK))

/* Parameter validity check for WKT Clock Source. */
#define IS_PWC_WKT_CLK_SRC(x)                                                   \
(   ((x)== PWC_WKT_CLK_SRC_64HZ)                    ||                          \
    ((x)== PWC_WKT_CLK_SRC_XTAL32)                  ||                          \
    ((x)== PWC_WKT_CLK_SRC_RTCLRC))

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
 * @retval None
 */
void PWC_PD_Enter(void)
{
    WRITE_REG16(CM_PWC->FPRC, PWC_UNLOCK_CODE1);

    CLR_REG8_BIT(CM_PWC->PVDCR1, PWC_PVDCR1_PVD1IRS | PWC_PVDCR1_PVD2IRS);
    SET_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);

    SET_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_PWDN);

    __WFI();
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
 * @note   PWC_LVD1_FLAG_DETECT could clear both LVD1 & LVD2 flag
 */
void PWC_LVD_ClearStatus(uint8_t u8Flag)
{
    DDL_ASSERT(IS_PWC_LVD_UNLOCKED());
    DDL_ASSERT(IS_PWC_LVD_CLR_FLAG(u8Flag));

    if (PWC_LVD2_FLAG_DETECT == u8Flag) {
        u8Flag = PWC_PVDDSR_PVD1DETFLG;
    }
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

    CLR_REG8_BIT(CM_PWC->PWRC2, PWC_PWRC2_DDAS);
    WRITE_REG8(CM_PWC->PWRC3, 0x00UL);
    MODIFY_REG8(CM_PWC->PWRC2, PWC_PWRC2_DVS, PWC_PWRC2_DVS_1);

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
    SET_REG8_BIT(CM_PWC->PWRC2, PWC_PWRC2_DDAS);
    WRITE_REG8(CM_PWC->PWRC3, 0xFFUL);
    SET_REG8_BIT(CM_PWC->PWRC2, PWC_PWRC2_DVS);

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
        CM_PWC->RAMPC0 |= u32Ram;
    } else {
        CM_PWC->RAMPC0 &= ~u32Ram;
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
        CM_PWC->PRAMLPC |= u32PeriphRam;
    } else {
        CM_PWC->PRAMLPC &= ~u32PeriphRam;
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
        MODIFY_REG8(CM_PWC->PWRC1, PWC_PWRC1_PDTS, pstcPDModeConfig->u8VcapCtrl << PWC_PWRC1_PDTS_POS);
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
        DDL_ASSERT(IS_PWC_STOP_FLASH_WAIT(pstcStopConfig->u16FlashWait));
        DDL_ASSERT(IS_PWC_STOP_EXBUS(pstcStopConfig->u16ExBusHold));
        DDL_ASSERT(IS_PWC_STOP_DRV(pstcStopConfig->u8StopDrv));
        MODIFY_REG8(CM_PWC->PWRC1, PWC_PWRC1_STPDAS, pstcStopConfig->u8StopDrv);
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
        pstcStopConfig->u8StopDrv = PWC_STOP_DRV_HIGH;
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
        SET_REG8_BIT(CM_PWC->PWRC4, PWC_PWRC4_ADBUFE);
    } else {
        CLR_REG8_BIT(CM_PWC->PWRC4, PWC_PWRC4_ADBUFE);
    }

}

/**
 * @brief  PWC power monitor voltage config.
 * @param  [in] u8VoltageSrc   PWC power monitor voltage config @ref PWC_Monitor_Power.
 *         This parameter can be one of the following values
 *  @arg    PWC_PWR_MON_IREF
 *  @arg    PWC_PWR_MON_TSENSOR or PWC_PWR_MON_VBAT_DIV2
 * @retval None
 * @note   This monitor power is used for ADC and output to REGC pin.
 *         PWC_PWR_MON_VBAT_DIV2 is only valid while HC32F4A0.
 */
void PWC_SetPowerMonitorVoltageSrc(uint8_t u8VoltageSrc)
{
    DDL_ASSERT(IS_PWC_PWR_MON_SEL(u8VoltageSrc));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    MODIFY_REG8(CM_PWC->PWRC4, PWC_PWRC4_ADBUFS, u8VoltageSrc);
}

/**
 * @brief  VBAT monitor reference voltage selection.
 * @param  [in] u8RefVoltage                VBAT monitor reference voltage.
 *         This parameter can be one of the following values:
 *  @arg    PWC_VBAT_REF_VOL_1P8V:  Vbat reference voltage is 1.8V
 *  @arg    PWC_VBAT_REF_VOL_2P1V:  Vbat reference voltage is 2.1V
 * @retval None
 */
void PWC_VBAT_SetMonitorVoltage(uint8_t u8RefVoltage)
{
    /* Check parameters */
    DDL_ASSERT(IS_PWC_VBAT_REF_VOL(u8RefVoltage));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bCM_PWC->PWRC4_b.VBATREFSEL, u8RefVoltage);
}

/**
 * @brief  ENABLE or DISABLE VBAT monitor.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_VBAT_MonitorCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bCM_PWC->PWRC4_b.VBATME, enNewState);
}

/**
 * @brief  Get VBAT voltage status.
 * @param  None
 * @retval An @ref en_flag_status_t enumeration type value.
 *         - SET: Flag is set, VBAT < VBATREF
 *         - RESET: Flag is reset, VBAT > VBATREF
 */
en_flag_status_t PWC_VBAT_GetVoltageStatus(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    return ((0UL != READ_REG32(bCM_PWC->PWRC4_b.VBATMON)) ? SET : RESET);
}

/**
 * @brief  ENABLE or DISABLE VBAT voltage divide monitor.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_VBAT_VoltageDivMonitorCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bCM_PWC->VBATCR_b.VBATDIVMONE, enNewState);
}

/**
 * @brief  RESET the VBAT area.
 * @param  None
 * @retval None
 */
void PWC_VBAT_Reset(void)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());
    WRITE_REG8(CM_PWC->VBATRSTR, 0xA5U);
}

/**
 * @brief  ENABLE or DISABLE VBAT power.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_VBAT_PowerCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    WRITE_REG32(bCM_PWC->VBATCR_b.CSDIS, enNewState);
}

/**
 * @brief  ENABLE or DISABLE Backup RAM power.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PWC_BKR_PowerCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    if (ENABLE == enNewState) {
        WRITE_REG32(bCM_PWC->VBATCR_b.VBTRSD, 0UL);
    } else {
        WRITE_REG32(bCM_PWC->VBATCR_b.VBTRSD, 1UL);
    }
}

/**
 * @brief  Get Backup RAM flag.
 * @param  [in] u8Flag                  Backup RAM flag.
 *         This parameter can be one or any combination of the following values:
 *  @arg    PWC_BACKUP_RAM_FLAG_RAMPDF:   Backup RAM power down flag
 *  @arg    PWC_BACKUP_RAM_FLAG_RAMVALID: Backup RAM read/write flag
 * @retval  An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t PWC_BKR_GetStatus(uint8_t u8Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_PWC_BACKUP_RAM_FLAG(u8Flag));

    DDL_ASSERT(IS_PWC_UNLOCKED());
    if (0U != (READ_REG8_BIT(CM_PWC->VBATCR, u8Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Write Backup register.
 * @param  [in] u8RegNum                Backup register number.
 *  @arg    This parameter can be a number between Min_Data = 0 and Max_Data = 127.
 * @param  [in] u8RegVal                Value written to register
 * @retval None
 */
void PWC_BKR_Write(uint8_t u8RegNum, uint8_t u8RegVal)
{
    __IO uint8_t *BKR;

    /* Check parameters */
    DDL_ASSERT(IS_PWC_BACKUP_REGISTER_NUMBER(u8RegNum));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    BKR = (__IO uint8_t *)PWC_BKRx(u8RegNum);
    WRITE_REG8(*BKR, u8RegVal);
}

/**
 * @brief  Read Backup register.
 * @param  [in] u8RegNum                Backup register number.
 *  @arg    This parameter can be a number between Min_Data = 0 and Max_Data = 127.
 * @retval uint8_t                      Register value
 */
uint8_t PWC_BKR_Read(uint8_t u8RegNum)
{
    uint8_t u8RegVal;

    /* Check parameters */
    DDL_ASSERT(IS_PWC_BACKUP_REGISTER_NUMBER(u8RegNum));
    DDL_ASSERT(IS_PWC_UNLOCKED());

    u8RegVal = READ_REG8(*((__IO uint8_t *)PWC_BKRx(u8RegNum)));

    return u8RegVal;
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

    MODIFY_REG8(CM_PWC->WKTC2, PWC_WKTC2_WKCKS, u16ClkSrc);
    WRITE_REG8(CM_PWC->WKTC0, (u16CmpVal & PWC_WKTC0_WKTMCMP));
    WRITE_REG8(CM_PWC->WKTC1, ((u16CmpVal >> 8U) & PWC_WKTC1_WKTMCMP));
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
    WRITE_REG8(CM_PWC->WKTC0, (u16CmpVal & PWC_WKTC0_WKTMCMP));
    WRITE_REG8(CM_PWC->WKTC1, ((u16CmpVal >> 8U) & PWC_WKTC1_WKTMCMP));
}

/**
 * @brief  Get WKT Timer compare value.
 * @param  None
 * @retval uint16_t                     WKT Compare value
 */
uint16_t PWC_WKT_GetCompareValue(void)
{
    uint16_t u16CmpVal;

    u16CmpVal  = (uint16_t)(READ_REG16_BIT(CM_PWC->WKTC1, PWC_WKTC1_WKTMCMP) << 8U);
    u16CmpVal |= READ_REG8(CM_PWC->WKTC0);

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

    WRITE_REG32(bCM_PWC->WKTC2_b.WKTCE, enNewState);
}

/**
 * @brief  Get WKT Timer count match flag.
 * @param  None
 * @retval An @ref en_flag_status_t enumeration type value. enumeration value:
 */
en_flag_status_t PWC_WKT_GetStatus(void)
{
    en_flag_status_t enFlagState;

    enFlagState = (0U != READ_REG8_BIT(CM_PWC->WKTC2, PWC_WKTC2_WKOVF)) ? SET : RESET;

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
    CLR_REG8_BIT(CM_PWC->WKTC2, PWC_WKTC2_WKOVF);
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
