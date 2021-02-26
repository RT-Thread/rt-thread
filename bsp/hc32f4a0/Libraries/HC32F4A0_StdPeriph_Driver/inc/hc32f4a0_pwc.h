/**
 *******************************************************************************
 * @file  hc32f4a0_pwc.h
 * @brief This file contains all the functions prototypes of the PWC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
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
#ifndef __HC32F4A0_PWC_H__
#define __HC32F4A0_PWC_H__

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
 * @addtogroup DDL_PWC
 * @{
 */

#if (DDL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Types PWC Global Types
 * @{
 */
typedef struct
{
    uint32_t u32RamCtrl;    /*!< Internal RAM power setting. */
    uint32_t u32PRamCtrl;   /*!< Peripheral RAM power setting. */
    uint16_t u16RamMode;    /*!< RAM setting for Operating mode, @ref PWC_RAM_Config for details */
} stc_pwc_ram_config_t;

typedef struct
{
    uint8_t u8PvdEn;        /*!< PVD function setting, @ref PWC_PVD_Config for details */
    uint8_t u8Pvd2ExtInEn;  /*!< PVD2 ext. pin input function setting, @ref PWC_PVD2_ExtIn_Config */
    uint8_t u8PvdCmpOutEn;  /*!< PVD compare output function setting, @ref PWC_PVD_CMP_Config for details */
    uint8_t u8PvdIntRstSel; /*!< PVD interrupt or reset selection, @ref PWC_PVD_IntRst_Sel for details */
    uint8_t u8PvdIntRstEn;  /*!< PVD interrupt or reset function setting, @ref PWC_PVD_IR_Config for details */
    uint8_t u8FilterEn;     /*!< PVD digital filter function setting, @ref PWC_PVD_DF_Config for details */
    uint8_t u8FilterClk;    /*!< PVD digital filter clock setting, @ref PWC_PVD_DFS_Clk_Sel for details */
    uint8_t u8PvdVoltage;   /*!< PVD detect voltage setting, @ref PWC_PVD_detection_Vol for details */
    uint8_t u8PvdNmiEn;     /*!< PVD NMI function setting, @ref PWC_PVD_Int_Mode_Config for details */
    uint8_t u8PvdTrigger;   /*!< PVD trigger setting, @ref PWC_PVD_Trigger_Sel for details */
} stc_pwc_pvd_config_t;

typedef struct
{
    uint8_t u8PDMode;       /*!< Power down mode, @ref PWC_PDMode_Sel for details. */
    uint8_t u8IOState;      /*!< IO state in power down mode, @ref PWC_PDMode_IO_Sel for details. */
    uint8_t u8WkUpSpeed;    /*!< Wakeup speed selection, @ref PWC_PDMode_WKUP_TIME_Sel for details. */
}stc_pwc_pd_mode_config_t;

typedef struct
{
    uint8_t u8StopDrv;      /*!< Stop mode drive capacity, @ref PWC_STOP_DRV_Sel for details. */
    uint16_t u16ExBusHold;  /*!< Exbus status in stop mode, @ref PWC_STOP_EXBUS_Sel for details. */
    uint16_t u16ClkKeep;    /*!< System clock setting after wake-up from stop mode,
                                 @ref PWC_STOP_CLK_Sel for details. */
    uint16_t u16FlashWait;  /*!< Waiting flash stable after wake-up from stop mode,
                                 @ref STOP_FLASH_WAIT_Sel for details. */
} stc_pwc_stop_mode_config;

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
#define PWC_PD_MODE1                (0x00U)        /*!< Power down mode 0 */
#define PWC_PD_MODE2                (0x01U)        /*!< Power down mode 1 */
#define PWC_PD_MODE3                (0x02U)        /*!< Power down mode 2 */
#define PWC_PD_MODE4                (0x03U)        /*!< Power down mode 3 */
/**
 * @}
 */

/**
 * @defgroup PWC_PDMode_IO_Sel IO state config in Power down mode
 * @{
 */
#define PWC_PD_IO_STATE1            (0x00U)                 /*!< IO state retain in PD mode and configurable after wakeup */
#define PWC_PD_IO_STATE2            (PWC_PWRC0_IORTN_0)     /*!< IO state retain in PD mode and configurable after wakeup & set IORTN[1:0]=00b */
#define PWC_PD_IO_STATE3            (PWC_PWRC0_IORTN_1)     /*!< IO state switch to HiZ */
/**
 * @}
 */

/**
 * @defgroup PWC_STOP_DRV_Sel Drive capacity while enter stop mode
 * @{
 */
#define PWC_STOP_DRV_HIGH           (0x00U)                 /*!< Enter stop mode from high speed mode */
#define PWC_STOP_DRV_LOW            (PWC_PWRC1_STPDAS)      /*!< Enter stop mode from ultra low speed mode */
/**
 * @}
 */

/**
 * @defgroup PWC_STOP_EXBUS_Sel ExBus status while enter stop mode
 * @{
 */
#define PWC_STOP_EXBUS_HIZ          (0x00U)                 /*!< Ex-Bus Hiz in stop mode */
#define PWC_STOP_EXBUS_HOLD         (PWC_STPMCR_EXBUSOE)    /*!< Ex-Bus keep in stop mode */
/**
 * @}
 */

/**
 * @defgroup PWC_STOP_CLK_Sel System clock setting after wake-up from stop mode
 * @{
 */
#define PWC_STOP_CLK_KEEP           (0x00U)                 /*!< Keep System clock setting after wake-up from stop mode */
#define PWC_STOP_CLK_MRC            (PWC_STPMCR_CKSMRC)     /*!< System clock switch to MRC after wake-up from stop mode */
/**
 * @}
 */

/**
 * @defgroup STOP_FLASH_WAIT_Sel Whether wait flash stable or not after wake-up from stop mode
 * @{
 */
#define PWC_STOP_FLASH_WAIT         (0x00U)                 /*!< Wait flash stable after wake-up from stop mode */
#define PWC_STOP_FLASH_NOWAIT       (PWC_STPMCR_FLNWT)      /*!< Don't wait flash stable after wake-up from stop mode */
/**
 * @}
 */

/**
 * @defgroup PWC_PWR_DRV_Sel Drive capacity selection
 * @{
 */
#define PWC_NOR_DRV_HIGH            (PWC_PWRC2_DVS)         /*!< Drive capacity in high speed operation */
#define PWC_NOR_DRV_LOW             (PWC_PWRC2_DVS_1)       /*!< Drive capacity in ultra low speed operation */
/**
 * @}
 */

/**
 * @defgroup PWC_PDMode_WKUP_TIME_Sel Wakeup speed config in Power down mode
 * @{
 */
#define PWC_PD_WKUP_SLOW            (0x00U)        /*!< VCAP1/VCAP2 = 0.1uF x2 or 0.22uF x1 */
#define PWC_PD_WKUP_FAST            (0x01U)        /*!< VCAP1/VCAP2 = 0.047uF x2 or 0.1uF x1 */
/**
 * @}
 */

/**
 * @defgroup PWC_RAM_Config Operating mode for RAM Config
 * @{
 */
#define PWC_RAM_HIGH                (0x8043U)     /*!< MCU operating under high frequency (lower than 240MHz) */
#define PWC_RAM_LOW                 (0x9062U)     /*!< MCU operating under ultra low frequency (lower than 8MHz) */
/**
 * @}
 */

/**
 * @defgroup PWC_PWMON_Config PWC Power Monitor Config
 * @{
 */
#define PWC_PWRMON_ON                (PWC_PWRC_PWMONE)
#define PWC_PWRMON_OFF               (0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_PWMON_Sel PWC Power Monitor Selection
 * @{
 */
#define PWC_PWRMON_VINREF           (0x00U)                 /*!< Internal reference voltage */
#define PWC_PWRMON_VOTS             (PWC_PWRC_PWMONSEL)     /*!< temperature sensor voltage */
/**
 * @}
 */

/**
 * @defgroup PWC_DRV_Sel PWC Driver ability selection
 * @{
 */
#define PWC_DRV_LOW                 (0x00U)       /*!< system clock = 32kHz */
#define PWC_DRV_HIGH                (0x07U)       /*!< system clock < 48Mhz */
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_Channel PWC PVD channel
 * @{
 */
#define PWC_PVD_CH1                 (0x00U)
#define PWC_PVD_CH2                 (0x01U)
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_Config PWC PVD Config
 * @{
 */
#define PWC_PVD_ON          (0x01U)
#define PWC_PVD_OFF         (0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_PVD2_ExtIn_Config PWC PVD2 external input Config
 * @{
 */
#define PWC_PVD2_EXINP_ON   (PWC_PVDCR0_EXVCCINEN)
#define PWC_PVD2_EXINP_OFF  (0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_IR_Config PWC PVD Interrupt/Reset Config
 * @{
 */
#define PWC_PVD_IR_ON       (PWC_PVDCR1_PVD1IRE)
#define PWC_PVD_IR_OFF      (0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_IntRst_Sel set PVD to interrupt or reset
 * @{
 */
#define PWC_PVD_INT         (0x00U)
#define PWC_PVD_RST         (PWC_PVDCR1_PVD1IRS)
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_CMP_Config PWC PVD Compare Config
 * @{
 */
#define PWC_PVD_CMP_ON      (PWC_PVDCR1_PVD1CMPOE)
#define PWC_PVD_CMP_OFF     (0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_DF_Config PVD digital filter ON or OFF
 * @{
 */
#define PWC_PVD_DF_ON       (0x00U)
#define PWC_PVD_DF_OFF      (PWC_PVDFCR_PVD1NFDIS)
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_DFS_Clk_Sel PVD digital filter sample ability
 * @note     modified this value must when PWC_PVD_DF_OFF
 * @{
 */
#define PWC_PVD_DFS_DIV4            (0x00U)                                             /*!< 0.25 LRC cycle */
#define PWC_PVD_DFS_DIV2            (PWC_PVDFCR_PVD1NFCKS_0)                            /*!< 0.5 LRC cycle */
#define PWC_PVD_DFS_DIV1            (PWC_PVDFCR_PVD1NFCKS_1)                            /*!< 1 LRC cycle */
#define PWC_PVD_DFS_MUL2            (PWC_PVDFCR_PVD1NFCKS)                              /*!< 2 LRC cycles */
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_detection_Vol PWC PVD Detection voltage
 * @{
 */
#define PWC_PVD1_2V0_PVD2_2V1        (0x00U)     /*!< Specifies the voltage of PVD1 is 2.0V or PVD2 is 2.0V. */
#define PWC_PVD1_2V1_PVD2_2V3        (0x01U)     /*!< Specifies the voltage of PVD1 is 2.1V or PVD2 is 2.1V. */
#define PWC_PVD1_2V3_PVD2_2V5        (0x02U)     /*!< Specifies the voltage of PVD1 is 2.3V or PVD2 is 2.3V. */
#define PWC_PVD1_2V5_PVD2_2V6        (0x03U)     /*!< Specifies the voltage of PVD1 is 2.5V or PVD2 is 2.5V. */
#define PWC_PVD1_2V6_PVD2_2V7        (0x04U)     /*!< Specifies the voltage of PVD1 is 2.6V or PVD2 is 2.6V. */
#define PWC_PVD1_2V7_PVD2_2V8        (0x05U)     /*!< Specifies the voltage of PVD1 is 2.7V or PVD2 is 2.7V. */
#define PWC_PVD1_2V8_PVD2_2V9        (0x06U)     /*!< Specifies the voltage of PVD1 is 2.8V or PVD2 is 2.8V. */
#define PWC_PVD1_2V9_PVD2_1V1        (0x07U)     /*!< Specifies the voltage of PVD1 is 2.9V or PVD2 is 1.1V (only ext. input). */
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_Int_Mode_Config PVD interrupt set to maskable or non_maskable
 * @{
 */
#define PWC_PVD_INT_MASK            (PWC_PVDICR_PVD1NMIS)
#define PWC_PVD_INT_NONMASK         (0x00U)
/**
 * @}
 */

/**
 * @defgroup PWC_PVD_Trigger_Sel PVD trigger setting
 * @{
 */
#define PWC_PVD_TRIGGER_FALLING    (0x00U)
#define PWC_PVD_TRIGGER_RISING     (PWC_PVDICR_PVD1EDGS_0)
#define PWC_PVD_TRIGGER_BOTH       (PWC_PVDICR_PVD1EDGS_1)
/**
 * @}
 */

/**
 * @defgroup PWC_WKUP_Event_Sel Power down mode wakeup event selection
 * @{
 */
#define PWC_PD_WKUP_TRIG_PVD1       (PWC_PDWKES_VD1EGS)
#define PWC_PD_WKUP_TRIG_PVD2       (PWC_PDWKES_VD2EGS)
#define PWC_PD_WKUP_TRIG_WKP0       (PWC_PDWKES_WK0EGS)
#define PWC_PD_WKUP_TRIG_WKP1       (PWC_PDWKES_WK1EGS)
#define PWC_PD_WKUP_TRIG_WKP2       (PWC_PDWKES_WK2EGS)
#define PWC_PD_WKUP_TRIG_WKP3       (PWC_PDWKES_WK3EGS)
#define PWC_PD_WKUP_TRIG_MASK       (PWC_PDWKES_VD1EGS | PWC_PDWKES_VD2EGS |    \
                                    PWC_PDWKES_WK0EGS  | PWC_PDWKES_WK1EGS |    \
                                    PWC_PDWKES_WK2EGS  | PWC_PDWKES_WK3EGS)
/**
 * @}
 */

/**
 * @defgroup PWC_WKUP_Trigger_Edge_Sel Power down mode wakeup trigger edge selection
 * @{
 */
#define PWC_PD_WKUP_FALLING         (0x00U)
#define PWC_PD_WKUP_RISING          (0x01U)
/**
 * @}
 */

/**
 * @defgroup PWC_DBGC_config PWC Debug Config
 * @{
 */
#define PWC_AD_INTERN_REF           (0x00U)
#define PWC_AD_VBAT_DIV2            (0x01U)
/**
 * @}
 */

/**
 * @defgroup PWC_VBAT_Voltage_Status PWC VBAT Voltage Status
 * @{
 */
#define PWC_VOL_VBAT_MORE_THAN_VBATREF        (0x00U)  /*!< Vbat > VbatREF */
#define PWC_VOL_VBAT_LESS_THAN_VBATREF        (0x01U)  /*!< Vbat < VbatREF */
/**
 * @}
 */

/**
 * @defgroup PWC_VBAT_Reference_Voltage PWC VBAT Reference Voltage
 * @{
 */
#define PWC_VBAT_REF_VOL_1P8V                 (0x00U)  /*!< Vbat reference voltage is 1.8V */
#define PWC_VBAT_REF_VOL_2P0V                 (0x01U)  /*!< Vbat reference voltage is 2.0V */
/**
 * @}
 */

/**
 * @defgroup PWC_BACKUP_RAM_Flag PWC Backup RAM Flag
 * @{
 */
#define PWC_BACKUP_RAM_FLAG_RAMPDF            (PWC_VBATCR_RAMPDF)     /*!< Backup RAM power down flag */
#define PWC_BACKUP_RAM_FLAG_RAMVALID          (PWC_VBATCR_RAMVALID)   /*!< Backup RAM read/write flag */
/**
 * @}
 */

/**
 * @defgroup PWC_WKT_Clock_Source PWC WKT Clock Source
 * @{
 */
#define PWC_WKT_CLK_SRC_64HZ                  (0U)                  /*!< 64Hz Clock   */
#define PWC_WKT_CLK_SRC_XTAL32                (PWC_WKTC2_WKCKS_0)   /*!< XTAL32 Clock */
#define PWC_WKT_CLK_SRC_RTCLRC                (PWC_WKTC2_WKCKS_1)   /*!< RTCLRC Clock    */
/**
 * @}
 */

/**
 * @defgroup PWC_REG_Write_Unlock_Code PWC register unlock code.
 * @brief Lock/unlock Code for each module
 *        PWC_UNLOCK_CODE_0:
 *          Below registers are locked in CLK module.
 *              XTALCFGR, XTALSTBCR, XTALCR, XTALSTDCR, XTALSTDSR, HRCTRM, HRCCR,
 *              MRCTRM, MRCCR, PLLCFGR, PLLCR, UPLLCFGR, UPLLCR, OSCSTBSR, CKSWR,
 *              SCFGR, UFSCKCFGR, TPIUCKCFGR, MCO1CFGR, MCO2CFGR, XTAL32CR,
 *              XTALC32CFGR, XTAL32NFR, LRCCR, LRCTRM.
 *        PWC_UNLOCK_CODE_1:
 *          Below registers are locked in PWC module.
 *              PWRC0, PWRC1, PWRC2, PWRC3, PDWKE0, PDWKE1, PDWKE2, PDWKES, PDWKF0,
 *              PDWKF1, PWCMR, PWR_STPMCR, RAMPC0, RAMOPM.
 *          Below registers are locked in CLK module.
 *              PERICKSEL, I2SCKSEL,
 *          Below register is locked in RMU module.
 *              RSTF0
 *        PWC_UNLOCK_CODE_2:
 *          Below registers are locked in PWC module.
 *              PVDCR0, PVDCR1, PVDFCR, PVDLCR, PVDICR, PVDDSR
 * @{
 */
#define PWC_UNLOCK_CODE_0           (0xA501U)
#define PWC_UNLOCK_CODE_1           (0xA502U)
#define PWC_UNLOCK_CODE_2           (0xA508U)
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
 *   @arg  PWC_UNLOCK_CODE_0:
 *          Below registers are locked in CLK module.
 *              XTALCFGR, XTALSTBCR, XTALCR, XTALSTDCR, XTALSTDSR, HRCTRM, HRCCR,
 *              MRCTRM, MRCCR, PLLCFGR, PLLCR, UPLLCFGR, UPLLCR, OSCSTBSR, CKSWR,
 *              SCFGR, UFSCKCFGR, TPIUCKCFGR, MCO1CFGR, MCO2CFGR, XTAL32CR,
 *              XTALC32CFGR, XTAL32NFR, LRCCR, LRCTRM.
 *   @arg  PWC_UNLOCK_CODE_1:
 *          Below registers are locked in PWC module.
 *              PWRC0, PWRC1, PWRC2, PWRC3, PDWKE0, PDWKE1, PDWKE2, PDWKES, PDWKF0,
 *              PDWKF1, PWCMR, PWR_STPMCR, RAMPC0, RAMOPM.
 *          Below registers are locked in VBAT module.
 *              RSTR, BATCR0, VBTBKR0~VBTBK127. 
 *          Below registers are locked in CLK module.
 *              PERICKSEL, I2SCKSEL,
 *          Below register is locked in RMU module.
 *              RSTF0
 *   @arg  PWC_UNLOCK_CODE_2:
 *          Below registers are locked in PWC module.
 *              PVDCR0, PVDCR1, PVDFCR, PVDLCR, PVDICR, PVDDSR
 * @retval None
 */
__STATIC_INLINE void PWC_Lock(uint16_t u16Module)
{
    M4_PWC->FPRC = (0xA500U | (uint16_t)((uint16_t)(~u16Module) & (M4_PWC->FPRC)));
}

/**
 * @brief  Unlock PWC, CLK, RMU register.
 * @param  [in] u16Module Unlock code for each module.
 *   @arg  PWC_UNLOCK_CODE_0:
 *          Below registers are unlocked in CLK module.
 *              XTALCFGR, XTALSTBCR, XTALCR, XTALSTDCR, XTALSTDSR, HRCTRM, HRCCR,
 *              MRCTRM, MRCCR, PLLCFGR, PLLCR, UPLLCFGR, UPLLCR, OSCSTBSR, CKSWR,
 *              SCFGR, UFSCKCFGR, TPIUCKCFGR, MCO1CFGR, MCO2CFGR, XTAL32CR,
 *              XTALC32CFGR, XTAL32NFR, LRCCR, LRCTRM.
 *   @arg  PWC_UNLOCK_CODE_1:
 *          Below registers are unlocked in PWC module.
 *              PWRC0, PWRC1, PWRC2, PWRC3, PDWKE0, PDWKE1, PDWKE2, PDWKES, PDWKF0,
 *              PDWKF1, PWCMR, PWR_STPMCR, RAMPC0, RAMOPM.
 *          Below registers are unlocked in VBAT module.
 *              RSTR, BATCR0, VBTBKR0~VBTBK127. 
 *          Below registers are unlocked in CLK module.
 *              PERICKSEL, I2SCKSEL,
 *          Below register is unlocked in RMU module.
 *              RSTF0
 *   @arg  PWC_UNLOCK_CODE_2:
 *          Below registers are unlocked in PWC module.
 *              PVDCR0, PVDCR1, PVDFCR, PVDLCR, PVDICR, PVDDSR
 * @retval None
 */
__STATIC_INLINE void PWC_Unlock(uint16_t u16Module)
{
    SET_REG16_BIT(M4_PWC->FPRC, u16Module);
}

/**
 * @brief  Lock PWC_FCG0 register .
 * @param  None
 * @retval None
 */
__STATIC_INLINE void PWC_FCG0_Lock(void)
{
    WRITE_REG32(M4_PWC->FCG0PC, 0xA5A50000UL);
}

/**
 * @brief  Unlock PWR_FCG0 register.
 * @param  None
 * @retval None
 * @note Call this function before PWC_Fcg0PeriphClockCmd()
 */
__STATIC_INLINE void PWC_FCG0_Unlock(void)
{
    WRITE_REG32(M4_PWC->FCG0PC, 0xA5A50001UL);
}

en_result_t PWC_PowerDownStructInit(stc_pwc_pd_mode_config_t *pstcPDModeConfig);
en_result_t PWC_PowerDownConfig(const stc_pwc_pd_mode_config_t *pstcPDModeConfig);
void PWC_EnterPowerDownMode(void);
void PWC_EnterStopMode(void);
void PWC_EnterSleepMode(void);

en_result_t PWC_StopStructInit(stc_pwc_stop_mode_config *pstcStopConfig);
en_result_t PWC_StopConfig(const stc_pwc_stop_mode_config *pstcStopConfig);
void PWC_StopDrvConfig(uint8_t u8StopDrv);
void PWC_StopClockKeepConfig(uint16_t u16ClkKeep);
void PWC_StopFlashWaitConfig(uint16_t u16FlashWait);
void PWC_StopExBusHoldConfig(uint16_t u16ExBusHold);

en_result_t PWC_HighSpeedToLowSpeed(void);
en_result_t PWC_LowSpeedToHighSpeed(void);

void PWC_HrcPwrCmd(en_functional_state_t enNewState);
void PWC_PllPwrCmd(en_functional_state_t enNewState);

void PWC_Fcg0PeriphClockCmd(uint32_t u32Fcg0Periph, en_functional_state_t enNewState);
void PWC_Fcg1PeriphClockCmd(uint32_t u32Fcg1Periph, en_functional_state_t enNewState);
void PWC_Fcg2PeriphClockCmd(uint32_t u32Fcg2Periph, en_functional_state_t enNewState);
void PWC_Fcg3PeriphClockCmd(uint32_t u32Fcg3Periph, en_functional_state_t enNewState);

en_result_t PWC_RamConfig(const stc_pwc_ram_config_t *pstcRamConfig);
en_result_t PWC_PVD_Init(uint8_t u8Ch, const stc_pwc_pvd_config_t *pstcPvdConfig);
en_result_t PWC_PVD_StructInit(stc_pwc_pvd_config_t *pstcPvdConfig);
en_flag_status_t PWC_PVD_GetStatus(uint8_t u8Flag);
void PWC_PVD_ClearStatus(void);

void PWC_PdWakeup0Cmd(uint8_t u8Wkup0Evt, en_functional_state_t enNewState);
void PWC_PdWakeup1Cmd(uint8_t u8Wkup1Evt, en_functional_state_t enNewState);
void PWC_PdWakeup2Cmd(uint8_t u8Wkup2Evt, en_functional_state_t enNewState);
void PWC_PdWakeupTrigConfig(uint8_t u8WkupEvt, uint8_t u8TrigEdge);
en_flag_status_t PWC_GetWakeup0Status(uint8_t u8Flag);
en_flag_status_t PWC_GetWakeup1Status(uint8_t u8Flag);

void PWC_AdcBufCmd(en_functional_state_t enNewState);
void PWC_AdcInternVolSel(uint8_t u8AdcInternVol);

void PWC_VBAT_MonitorVolSel(uint8_t u8RefVol);
void PWC_VBAT_MonitorCmd(en_functional_state_t enNewState);
uint8_t PWC_VBAT_GetVolStatus(void);
void PWC_VBAT_MeasureVolCmd(en_functional_state_t enNewState);
void PWC_VBAT_Reset(void);
void PWC_VBAT_PwrCmd(en_functional_state_t enNewState);

void PWC_BkRamPwrCmd(en_functional_state_t enNewState);
en_flag_status_t PWC_GetBkRamStatus(uint8_t u8Flag);
void PWC_WriteBackupReg(uint8_t u8RegNum, uint8_t u8RegVal);
uint8_t PWC_ReadBackupReg(uint8_t u8RegNum);

void PWC_WKT_Init(uint8_t u8ClkSrc, uint16_t u16CmpVal);
void PWC_WKT_SetCompareValue(uint16_t u16CmpVal);
uint16_t PWC_WKT_GetCompareValue(void);
void PWC_WKT_Cmd(en_functional_state_t enNewState);
en_flag_status_t PWC_WKT_GetStatus(void);
void PWC_WKT_ClearStatus(void);

/**
 * @}
 */

#endif /* DDL_PWC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_PWC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
