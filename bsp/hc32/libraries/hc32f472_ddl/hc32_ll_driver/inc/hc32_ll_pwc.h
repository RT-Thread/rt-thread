/**
 *******************************************************************************
 * @file  hc32_ll_pwc.h
 * @brief This file contains all the functions prototypes of the PWC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify group PWC_Stop_Type
   2023-09-30       CDT             Remove redundant macro definition
                                    Modify the PWC_LVD_Detection_Voltage_Sel comment
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
#ifndef __HC32_LL_PWC_H__
#define __HC32_LL_PWC_H__

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
 * @addtogroup LL_PWC
 * @{
 */

#if (LL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Types PWC Global Types
 * @{
 */
/**
 * @brief PWC LVD Init
 */
typedef struct {
    uint32_t u32State;              /*!< LVD function setting, @ref PWC_LVD_Config for details */
    uint32_t u32CompareOutputState; /*!< LVD compare output function setting, @ref PWC_LVD_CMP_Config for details */
    uint32_t u32ExceptionType;      /*!< LVD interrupt or reset selection, @ref PWC_LVD_Exception_Type_Sel for details */
    uint32_t u32Filter;             /*!< LVD digital filter function setting, @ref PWC_LVD_DF_Config for details */
    uint32_t u32FilterClock;        /*!< LVD digital filter clock setting, @ref PWC_LVD_DFS_Clk_Sel for details */
    uint32_t u32ThresholdVoltage;   /*!< LVD detect voltage setting, @ref PWC_LVD_Detection_Voltage_Sel for details */
    uint32_t u32TriggerEdge;        /*!< LVD trigger setting, @ref PWC_LVD_TRIG_Sel for details */
} stc_pwc_lvd_init_t;

/**
 * @brief PWC power down mode innit
 */
typedef struct {
    uint8_t u8Mode;         /*!< Power down mode, @ref PWC_PDMode_Sel for details. */
    uint8_t u8IOState;      /*!< IO state in power down mode, @ref PWC_PDMode_IO_Sel for details. */
} stc_pwc_pd_mode_config_t;

/**
 * @brief PWC Stop mode Init
 */
typedef struct {
    uint16_t u16Clock;          /*!< System clock setting after wake-up from stop mode,
                                    @ref PWC_STOP_CLK_Sel for details.        */
    uint16_t u16ExBusHold;      /*!< Expos status in stop mode,
                                    @ref PWC_STOP_EXBUS_Sel for details.      */
    uint16_t u16FlashWait;      /*!< Waiting flash stable after wake-up from stop mode,
                                    @ref PWC_STOP_Flash_Wait_Sel for details. */
} stc_pwc_stop_mode_config_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Macros PWC Global Macros
 * @{
 */

/**
 * @defgroup PWC_PDMode_Sel Power down mode selection
 * @{
 */
#define PWC_PD_MD1                      (0x00U)        /*!< Power down mode 1 */
#define PWC_PD_MD2                      (0x01U)        /*!< Power down mode 2 */
#define PWC_PD_MD3                      (0x02U)        /*!< Power down mode 3 */
#define PWC_PD_MD4                      (0x03U)        /*!< Power down mode 4 */
/**
 * @}
 */

/**
 * @defgroup PWC_PDMode_IO_Sel IO state config in Power down mode
 * @{
 */
#define PWC_PD_IO_KEEP1                 (0x00U)                 /*!< IO state retain in PD mode and configurable after wakeup */
#define PWC_PD_IO_KEEP2                 (PWC_PWRC0_IORTN_0)     /*!< IO state retain in PD mode and configurable after wakeup & set IORTN[1:0]=00b */
#define PWC_PD_IO_HIZ                   (PWC_PWRC0_IORTN_1)     /*!< IO state switch to HiZ */
/**
 * @}
 */

/**
 * @defgroup PWC_STOP_EXBUS_Sel ExBus status while enter stop mode
 * @{
 */
#define PWC_STOP_EXBUS_HIZ              (0x00U)                 /*!< Ex-Bus Hiz in stop mode */
#define PWC_STOP_EXBUS_HOLD             (PWC_STPMCR_EXBUSOE)    /*!< Ex-Bus keep in stop mode */
/**
 * @}
 */

/**
 * @defgroup PWC_STOP_CLK_Sel System clock setting after wake-up from stop mode
 * @{
 */
#define PWC_STOP_CLK_KEEP               (0x00U)                 /*!< Keep System clock setting after wake-up from stop mode */
#define PWC_STOP_CLK_MRC                (PWC_STPMCR_CKSMRC)     /*!< System clock switch to MRC after wake-up from stop mode */

/**
 * @}
 */

/**
 * @defgroup PWC_STOP_Flash_Wait_Sel Whether wait flash stable or not after wake-up from stop mode
 * @{
 */
#define PWC_STOP_FLASH_WAIT_ON          (0x00U)                 /*!< Wait flash stable after wake-up from stop mode */
#define PWC_STOP_FLASH_WAIT_OFF         (PWC_STPMCR_FLNWT)      /*!< Don't wait flash stable after wake-up from stop mode */
/**
 * @}
 */

/**
 * @defgroup PWC_Stop_Type PWC stop mode type.
 * @{
 */
#define PWC_STOP_WFI                    (0x00U)                 /*!< Enter stop mode by WFI, and wake-up by interrupt handle. */
#define PWC_STOP_WFE_INT                (0x01U)                 /*!< Enter stop mode by WFE, and wake-up by interrupt request. */
#define PWC_STOP_WFE_EVT                (0x02U)                 /*!< Enter stop mode by WFE, and wake-up by event. */
/**
 * @}
 */

/**
 * @defgroup PWC_Stop_Type PWC stop mode type.
 * @{
 */
#define PWC_SLEEP_WFI                   (0x00U)                 /*!< Enter sleep mode by WFI, and wake-up by interrupt handle. */
#define PWC_SLEEP_WFE_INT               (0x01U)                 /*!< Enter sleep mode by WFE, and wake-up by interrupt request. */
#define PWC_SLEEP_WFE_EVT               (0x02U)                 /*!< Enter sleep mode by WFE, and wake-up by event. */
/**
 * @}
 */

/**
 * @defgroup PWC_PD_Periph_Ram  Peripheral ram to power down
 * @{
 */
#define PWC_RAM_PD_CAN1                 (PWC_PRAMLPC_PRAMPDC0)
#define PWC_RAM_PD_CAN2_3               (PWC_PRAMLPC_PRAMPDC1)
#define PWC_RAM_PD_CACHE                (PWC_PRAMLPC_PRAMPDC2)
#define PWC_RAM_PD_USBFS                (PWC_PRAMLPC_PRAMPDC3)
#define PWC_RAM_PD_ALL                  (PWC_PRAMLPC_PRAMPDC0 | PWC_PRAMLPC_PRAMPDC1 | \
                                         PWC_PRAMLPC_PRAMPDC2 | PWC_PRAMLPC_PRAMPDC3)

/**
 * @}
 */

/**
 * @defgroup PWC_PD_Ram  Peripheral ram to power down
 * @{
 */
#define PWC_RAM_PD_SRAM0                (PWC_RAMPC0_RAMPDC0)    /*!< 0x20000000 ~ 0x20007FFF */
#define PWC_RAM_PD_SRAMH                (PWC_RAMPC0_RAMPDC10)   /*!< 0x1FFF8000 ~ 0x1FFFFFFF */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Channel PWC LVD channel
 * @{
 */
#define PWC_LVD_CH1                     (0x00U)
#define PWC_LVD_CH2                     (0x01U)

/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Config PWC LVD Config
 * @{
 */
#define PWC_LVD_ON                      (PWC_PVDCR0_PVD1EN)
#define PWC_LVD_OFF                     (0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Exception_Type_Sel PWC LVD Exception Type Select
 * @{
 */
#define PWC_LVD_EXP_TYPE_NONE           (0x00U)
#define PWC_LVD_EXP_TYPE_INT            (0x0101U)
#define PWC_LVD_EXP_TYPE_NMI            (0x0001U)
#define PWC_LVD_EXP_TYPE_RST            (PWC_PVDCR1_PVD1IRE | PWC_PVDCR1_PVD1IRS)

/**
 * @}
 */

/**
 * @defgroup PWC_LVD_CMP_Config PWC LVD Compare Config
 * @{
 */
#define PWC_LVD_CMP_OFF                 (0x00U)
#define PWC_LVD_CMP_ON                  (PWC_PVDCR1_PVD1CMPOE)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_DF_Config LVD digital filter ON or OFF
 * @{
 */
#define PWC_LVD_FILTER_ON               (0x00U)
#define PWC_LVD_FILTER_OFF              (0x01U)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_DFS_Clk_Sel LVD digital filter sample ability
 * @note     modified this value must when PWC_LVD_FILTER_OFF
 * @{
 */
#define PWC_LVD_FILTER_LRC_DIV4        (0x00UL << PWC_PVDFCR_PVD1NFCKS_POS)     /*!< 0.25 LRC cycle */
#define PWC_LVD_FILTER_LRC_DIV2        (0x01UL << PWC_PVDFCR_PVD1NFCKS_POS)     /*!< 0.5 LRC cycle  */
#define PWC_LVD_FILTER_LRC_DIV1        (0x02UL << PWC_PVDFCR_PVD1NFCKS_POS)     /*!< 1 LRC cycle    */
#define PWC_LVD_FILTER_LRC_MUL2        (0x03UL << PWC_PVDFCR_PVD1NFCKS_POS)     /*!< 2 LRC cycles   */

/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Detection_Voltage_Sel PWC LVD Detection voltage
 * @{
 * @note
 * @verbatim
 *       |  LVL0   |  LVL1   |  LVL2   |  LVL3   |  LVL4   |  LVL5   |  LVL6   |  LVL7   |  EXVCC |
 * LVD1  |  2.00V  |  2.10V  |  2.30V  |  2.55V  |  2.65V  |  2.75V  |  2.85V  |  2.95V  |   --   |
 * LVD2  |  2.10V  |  2.30V  |  2.55V  |  2.65V  |  2.75V  |  2.85V  |  2.95V  |  1.10V  |  EXVCC |
 * @endverbatim
 */
#define PWC_LVD_THRESHOLD_LVL0          (0x00U)
#define PWC_LVD_THRESHOLD_LVL1          (0x01U)
#define PWC_LVD_THRESHOLD_LVL2          (0x02U)
#define PWC_LVD_THRESHOLD_LVL3          (0x03U)
#define PWC_LVD_THRESHOLD_LVL4          (0x04U)
#define PWC_LVD_THRESHOLD_LVL5          (0x05U)
#define PWC_LVD_THRESHOLD_LVL6          (0x06U)
#define PWC_LVD_THRESHOLD_LVL7          (0x07U)
#define PWC_LVD_EXTVCC                  (0x07U)

/**
 * @}
 */

/**
 * @defgroup PWC_LVD_TRIG_Sel LVD trigger setting
 * @{
 */
#define PWC_LVD_TRIG_FALLING            (0x00UL << PWC_PVDICR_PVD1EDGS_POS)
#define PWC_LVD_TRIG_RISING             (0x01UL << PWC_PVDICR_PVD1EDGS_POS)
#define PWC_LVD_TRIG_BOTH               (0x02UL << PWC_PVDICR_PVD1EDGS_POS)

/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Flag LVD flag
 * @{
 */
#define PWC_LVD1_FLAG_DETECT            (PWC_PVDDSR_PVD1DETFLG)          /*!< VCC across VLVD1   */
#define PWC_LVD2_FLAG_DETECT            (PWC_PVDDSR_PVD2DETFLG)          /*!< VCC across VLVD2   */
#define PWC_LVD1_FLAG_MON               (PWC_PVDDSR_PVD1MON)             /*!< VCC > VLVD1        */
#define PWC_LVD2_FLAG_MON               (PWC_PVDDSR_PVD2MON)             /*!< VCC > VLVD2        */

/**
 * @}
 */

/**
 * @defgroup PWC_WKUP_Event_Sel Power down mode wakeup event selection
 * @{
 */
#define PWC_PD_WKUP0_POS                (0U)
#define PWC_PD_WKUP1_POS                (8U)
#define PWC_PD_WKUP2_POS                (16U)
#define PWC_PD_WKUP_WKUP00              (PWC_PDWKE0_WKE00 << PWC_PD_WKUP0_POS)
#define PWC_PD_WKUP_WKUP01              (PWC_PDWKE0_WKE01 << PWC_PD_WKUP0_POS)
#define PWC_PD_WKUP_WKUP02              (PWC_PDWKE0_WKE02 << PWC_PD_WKUP0_POS)
#define PWC_PD_WKUP_WKUP03              (PWC_PDWKE0_WKE03 << PWC_PD_WKUP0_POS)
#define PWC_PD_WKUP_WKUP10              (PWC_PDWKE0_WKE10 << PWC_PD_WKUP0_POS)
#define PWC_PD_WKUP_WKUP11              (PWC_PDWKE0_WKE11 << PWC_PD_WKUP0_POS)
#define PWC_PD_WKUP_WKUP12              (PWC_PDWKE0_WKE12 << PWC_PD_WKUP0_POS)
#define PWC_PD_WKUP_WKUP13              (PWC_PDWKE0_WKE13 << PWC_PD_WKUP0_POS)
#define PWC_PD_WKUP_WKUP20              (PWC_PDWKE1_WKE20 << PWC_PD_WKUP1_POS)
#define PWC_PD_WKUP_WKUP21              (PWC_PDWKE1_WKE21 << PWC_PD_WKUP1_POS)
#define PWC_PD_WKUP_WKUP22              (PWC_PDWKE1_WKE22 << PWC_PD_WKUP1_POS)
#define PWC_PD_WKUP_WKUP23              (PWC_PDWKE1_WKE23 << PWC_PD_WKUP1_POS)
#define PWC_PD_WKUP_WKUP30              (PWC_PDWKE1_WKE30 << PWC_PD_WKUP1_POS)
#define PWC_PD_WKUP_WKUP31              (PWC_PDWKE1_WKE31 << PWC_PD_WKUP1_POS)
#define PWC_PD_WKUP_WKUP32              (PWC_PDWKE1_WKE32 << PWC_PD_WKUP1_POS)
#define PWC_PD_WKUP_WKUP33              (PWC_PDWKE1_WKE33 << PWC_PD_WKUP1_POS)
#define PWC_PD_WKUP_LVD1                (PWC_PDWKE2_VD1WKE << PWC_PD_WKUP2_POS)
#define PWC_PD_WKUP_LVD2                (PWC_PDWKE2_VD2WKE << PWC_PD_WKUP2_POS)
#define PWC_PD_WKUP_RTCPRD              (PWC_PDWKE2_RTCPRDWKE << PWC_PD_WKUP2_POS)
#define PWC_PD_WKUP_RTCALM              (PWC_PDWKE2_RTCALMWKE << PWC_PD_WKUP2_POS)
#define PWC_PD_WKUP_WKTM                (PWC_PDWKE2_WKTMWKE << PWC_PD_WKUP2_POS)
/**
 * @}
 */

/**
 * @defgroup PWC_WKUP_Trigger_Event_Sel Power down mode wakeup event selection to set trigger edge.
 * @{
 */
#define PWC_PD_WKUP_TRIG_LVD1           (PWC_PDWKES_VD1EGS)
#define PWC_PD_WKUP_TRIG_LVD2           (PWC_PDWKES_VD2EGS)
#define PWC_PD_WKUP_TRIG_WKUP0          (PWC_PDWKES_WK0EGS)
#define PWC_PD_WKUP_TRIG_WKUP1          (PWC_PDWKES_WK1EGS)
#define PWC_PD_WKUP_TRIG_WKUP2          (PWC_PDWKES_WK2EGS)
#define PWC_PD_WKUP_TRIG_WKUP3          (PWC_PDWKES_WK3EGS)

#define PWC_PD_WKUP_TRIG_ALL            (PWC_PD_WKUP_TRIG_LVD1  | PWC_PD_WKUP_TRIG_LVD2  | PWC_PD_WKUP_TRIG_WKUP0 | \
                                         PWC_PD_WKUP_TRIG_WKUP1 | PWC_PD_WKUP_TRIG_WKUP2 | PWC_PD_WKUP_TRIG_WKUP3)
/**
 * @}
 */

/**
 * @defgroup PWC_WKUP_Trigger_Edge_Sel Power down mode wakeup trigger edge selection
 * @{
 */
#define PWC_PD_WKUP_TRIG_FALLING        (0x00U)
#define PWC_PD_WKUP_TRIG_RISING         (0x01U)
/**
 * @}
 */

/**
 * @defgroup PWC_WKUP_Event_Flag_Sel Power down mode wakeup Event status selection
 * @{
 */
#define PWC_PD_WKUP_FLAG0_POS           (0U)
#define PWC_PD_WKUP_FLAG1_POS           (8U)
#define PWC_PD_WKUP_FLAG_WKUP0          (PWC_PDWKF0_PTWK0F << PWC_PD_WKUP_FLAG0_POS)
#define PWC_PD_WKUP_FLAG_WKUP1          (PWC_PDWKF0_PTWK1F << PWC_PD_WKUP_FLAG0_POS)
#define PWC_PD_WKUP_FLAG_WKUP2          (PWC_PDWKF0_PTWK2F << PWC_PD_WKUP_FLAG0_POS)
#define PWC_PD_WKUP_FLAG_WKUP3          (PWC_PDWKF0_PTWK3F << PWC_PD_WKUP_FLAG0_POS)
#define PWC_PD_WKUP_FLAG_LVD1           (PWC_PDWKF0_VD1WKF << PWC_PD_WKUP_FLAG0_POS)
#define PWC_PD_WKUP_FLAG_LVD2           (PWC_PDWKF0_VD2WKF << PWC_PD_WKUP_FLAG0_POS)
#define PWC_PD_WKUP_FLAG_RTCPRD         (PWC_PDWKF1_RTCPRDWKF << PWC_PD_WKUP_FLAG1_POS)
#define PWC_PD_WKUP_FLAG_RTCALM         (PWC_PDWKF1_RTCALMWKF << PWC_PD_WKUP_FLAG1_POS)
#define PWC_PD_WKUP_FLAG_WKTM           (PWC_PDWKF1_WKTMWKF << PWC_PD_WKUP_FLAG1_POS)

#define PWC_PD_WKUP_FLAG_ALL            (PWC_PD_WKUP_FLAG_WKUP0  | PWC_PD_WKUP_FLAG_WKUP1  | PWC_PD_WKUP_FLAG_WKUP2 | \
                                         PWC_PD_WKUP_FLAG_WKUP3  | PWC_PD_WKUP_FLAG_LVD1   | PWC_PD_WKUP_FLAG_LVD2  | \
                                         PWC_PD_WKUP_FLAG_RTCPRD | PWC_PD_WKUP_FLAG_RTCALM | PWC_PD_WKUP_FLAG_WKTM)
/**
 * @}
 */

/**
 * @defgroup PWC_WKT_State PWC WKT State
 * @{
 */
#define PWC_WKT_OFF                    (0x00U)
#define PWC_WKT_ON                     (PWC_WKTCR_WKTCE)
/**
 * @}
 */

/**
 * @defgroup PWC_WKT_Clock_Source PWC WKT Clock Source
 * @{
 */
#define PWC_WKT_CLK_SRC_64HZ            ((0x00U << PWC_WKTCR_WKCKS_POS))   /*!< 64Hz Clock   */
#define PWC_WKT_CLK_SRC_XTAL32          ((0x01U << PWC_WKTCR_WKCKS_POS))   /*!< XTAL32 Clock */
#define PWC_WKT_CLK_SRC_LRC             ((0x02U << PWC_WKTCR_WKCKS_POS))   /*!< LRC Clock */

/**
 * @}
 */

/**
 * @defgroup PWC_Ldo_Sel PWC LDO Selection
 * @{
 */
#define PWC_LDO_HRC                     (PWC_PWRC1_VHRCSD)
#define PWC_LDO_PLL                     (PWC_PWRC1_VPLLSD)
#define PWC_LDO_MASK                    (PWC_LDO_HRC | PWC_LDO_PLL)
/**
 * @}
 */

/**
 * @defgroup PWC_Rtc_Clock_Sel PWC RTC clock selection
 * @{
 */
#define PWC_RTC_CLK_LRC                 (0x00U)             /*!< Rtc clock selects LRC */
#define PWC_RTC_CLK_XTAL_DIV            (0x01U)             /*!< Rtc clock selects XTAL div as 32.768KHz */
#define PWC_RTC_CLK_PIN                 (0x02U)             /*!< Rtc clock selects PIN input */
/**
 * @}
 */

/**
 * @defgroup PWC_Port_Reset_Sel PWC Port reset selection
 * @{
 */
#define PWC_PORT_RST_WDT                (PWC_PWRC6_WDRTNE)
#define PWC_PORT_RST_SW                 (PWC_PWRC6_SWRTNE)
#define PWC_PORT_RST_ALL                (PWC_PORT_RST_WDT | PWC_PORT_RST_SW)
/**
 * @}
 */

/**
 * @defgroup PWC_Dac_Reset_Sel PWC Port reset selection
 * @{
 */
#define PWC_DAC_RST_WDT                 (PWC_PWRC6_WDRDAC)
#define PWC_DAC_RST_SW                  (PWC_PWRC6_SWRDAC)
#define PWC_DAC_RST_ALL                 (PWC_DAC_RST_WDT | PWC_DAC_RST_SW)
/**
 * @}
 */

/**
 * @defgroup PWC_REG_Write_Unlock_Code PWC register unlock code.
 * @brief Lock/unlock Code for each module
 *        PWC_UNLOCK_CODE0:
 *          Below registers are locked in CLK module.
 *              XTALCFGR, XTALSTBCR, XTALCR, XTALSTDCR, XTALSTDSR, HRCTRM, HRCCR,
 *              MRCTRM, MRCCR, PLLCFGR, PLLCR, UPLLCFGR, UPLLCR, OSCSTBSR, CKSWR,
 *              SCFGR, USBCKCFGR, TPIUCKCFGR, MCO1CFGR, MCO2CFGR, XTAL32CR,
 *              XTALC32CFGR, XTAL32NFR, LRCCR, LRCTRM.
 *        PWC_UNLOCK_CODE1:
 *          Below registers are locked in PWC module.
 *              PWRC0, PWRC1, PWRC2, PWRC3, PDWKE0, PDWKE1, PDWKE2, PDWKES, PDWKF0,
 *              PDWKF1, PWCMR, PWR_STPMCR, RAMPC0, RAMOPM.
 *          Below registers are locked in CLK module.
 *              PERICKSEL, I2SCKSEL,
 *          Below register is locked in RMU module.
 *              RSTF0
 *        PWC_UNLOCK_CODE2:
 *          Below registers are locked in PWC module.
 *              PVDCR0, PVDCR1, PVDFCR, PVDLCR, PVDICR, PVDDSR
 * @{
 */
#define PWC_WRITE_ENABLE                (0xA500U)
#define PWC_UNLOCK_CODE0                (0xA501U)
#define PWC_UNLOCK_CODE1                (0xA502U)
#define PWC_UNLOCK_CODE2                (0xA508U)

/**
 * @brief PWC FCG0 Unlock/Lock code
 */
#define PWC_FCG0_REG_UNLOCK_KEY          (0xA5A50001UL)
#define PWC_FCG0_REG_LOCK_KEY            (0xA5A50000UL)

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
 * @addtogroup PWC_Global_Functions
 * @{
 */
/**
 * @brief  Lock PWC, CLK, RMU register.
 * @param  [in] u16Module Lock code for each module.
 *   @arg  PWC_UNLOCK_CODE0
 *   @arg  PWC_UNLOCK_CODE1
 *   @arg  PWC_UNLOCK_CODE2
 * @retval None
 */
__STATIC_INLINE void PWC_REG_Lock(uint16_t u16Module)
{
    CM_PWC->FPRC = (PWC_WRITE_ENABLE | (uint16_t)((uint16_t)(~u16Module) & (CM_PWC->FPRC)));
}

/**
 * @brief  Unlock PWC, CLK, RMU register.
 * @param  [in] u16Module Unlock code for each module.
 *   @arg  PWC_UNLOCK_CODE0
 *   @arg  PWC_UNLOCK_CODE1
 *   @arg  PWC_UNLOCK_CODE2
 * @retval None
 */
__STATIC_INLINE void PWC_REG_Unlock(uint16_t u16Module)
{
    SET_REG16_BIT(CM_PWC->FPRC, u16Module);
}

/**
 * @brief  Lock PWC_FCG0 register .
 * @param  None
 * @retval None
 */
__STATIC_INLINE void PWC_FCG0_REG_Lock(void)
{
    WRITE_REG32(CM_PWC->FCG0PC, PWC_FCG0_REG_LOCK_KEY);
}

/**
 * @brief  Unlock PWR_FCG0 register.
 * @param  None
 * @retval None
 * @note Call this function before FCG_Fcg0PeriphClockCmd()
 */
__STATIC_INLINE void PWC_FCG0_REG_Unlock(void)
{
    WRITE_REG32(CM_PWC->FCG0PC, PWC_FCG0_REG_UNLOCK_KEY);
}

/* PWC PD Function */
int32_t PWC_PD_Enter(void);
int32_t PWC_PD_StructInit(stc_pwc_pd_mode_config_t *pstcPDModeConfig);
int32_t PWC_PD_Config(const stc_pwc_pd_mode_config_t *pstcPDModeConfig);
void PWC_PD_SetIoState(uint8_t u8IoState);
void PWC_PD_SetMode(uint8_t u8PdMode);
void PWC_PD_WakeupCmd(uint32_t u32Event, en_functional_state_t enNewState);
void PWC_PD_SetWakeupTriggerEdge(uint8_t u8Event, uint8_t u8TrigEdge);
en_flag_status_t PWC_PD_GetWakeupStatus(uint16_t u16Flag);
void PWC_PD_ClearWakeupStatus(uint16_t u16Flag);
void PWC_PD_PeriphRamCmd(uint32_t u32PeriphRam, en_functional_state_t enNewState);
void PWC_PD_RamCmd(uint32_t u32Ram, en_functional_state_t enNewState);
void PWC_PD_VdrCmd(en_functional_state_t enNewState);

/* PWC WKTM Function */
void PWC_WKT_Config(uint16_t u16ClkSrc, uint16_t u16CmpVal);
void PWC_WKT_SetCompareValue(uint16_t u16CmpVal);
uint16_t PWC_WKT_GetCompareValue(void);
void PWC_WKT_Cmd(en_functional_state_t enNewState);
en_flag_status_t PWC_WKT_GetStatus(void);
void PWC_WKT_ClearStatus(void);

/* PWC Sleep Function */
void PWC_SLEEP_Enter(uint8_t u8SleepType);

/* PWC Stop Function */
void PWC_STOP_Enter(uint8_t u8StopType);
int32_t PWC_STOP_StructInit(stc_pwc_stop_mode_config_t *pstcStopConfig);
int32_t PWC_STOP_Config(const stc_pwc_stop_mode_config_t *pstcStopConfig);
void PWC_STOP_ClockSelect(uint8_t u8Clock);
void PWC_STOP_FlashWaitCmd(en_functional_state_t enNewState);

void PWC_STOP_ExBusHoldConfig(uint16_t u16ExBusHold);

/* PWC LDO Function */
void PWC_LDO_Cmd(uint16_t u16Ldo, en_functional_state_t enNewState);

/* PWC LVD/PVD Function */
int32_t PWC_LVD_Init(uint8_t u8Ch, const stc_pwc_lvd_init_t *pstcLvdInit);
void PWC_LVD_DeInit(uint8_t u8Ch);
int32_t PWC_LVD_StructInit(stc_pwc_lvd_init_t *pstcLvdInit);
void PWC_LVD_Cmd(uint8_t u8Ch, en_functional_state_t enNewState);
void PWC_LVD_ExtInputCmd(en_functional_state_t enNewState);
void PWC_LVD_CompareOutputCmd(uint8_t u8Ch, en_functional_state_t enNewState);
void PWC_LVD_DigitalFilterCmd(uint8_t u8Ch, en_functional_state_t enNewState);
void PWC_LVD_SetFilterClock(uint8_t u8Ch, uint32_t u32Clock);
void PWC_LVD_SetThresholdVoltage(uint8_t u8Ch, uint32_t u32Voltage);
void PWC_LVD_ClearStatus(uint8_t u8Flag);
en_flag_status_t PWC_LVD_GetStatus(uint8_t u8Flag);

/* PWC Power Monitor Function */
void PWC_PowerMonitorCmd(en_functional_state_t enNewState);

/* PWC RAM Function */

void PWC_XTAL32_PowerCmd(en_functional_state_t enNewState);
void PWC_RetSram_PowerCmd(en_functional_state_t enNewState);

void PWC_PortResetCmd(uint8_t u8Event, en_functional_state_t enNewState);
void PWC_DacResetCmd(uint8_t u8Event, en_functional_state_t enNewState);
void PWC_ReleasePort(void);
void PWC_SetRtcClock(uint8_t u8Clock);
/**
 * @}
 */

#endif /* LL_PWC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_PWC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
