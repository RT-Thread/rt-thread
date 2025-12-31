/**
  ******************************************************************************
  * @file               ft32f4xx_pwr.h
  * @author             Rwang
  * @brief              This file contains all the functions prototypes for the PWR firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2025-03-24
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_PWR_H
#define __FT32F4XX_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"



/** @addtogroup PWR
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants
  * @{
  */

/** @defgroup PWR_Vbat_charge_Resistance_Choose
  * @{
  */

#define PWR_Vbat_Charge_5k                 ((uint32_t)0x00000000)
#define PWR_Vbat_Charge_1point5k           ((uint32_t)0x00000001)

#define IS_PWR_VBAT_RES(RES)               (((RES) == PWR_Vbat_Charge_5k)  || \
                                            ((RES) == PWR_Vbat_Charge_1point5k)   )
/**
  * @}
  */

/** @defgroup PWR_Vos_Level_Choose
  * @{
  */

#define PWR_VosLevel_0                     PWR_CR_VOS_0
#define PWR_VosLevel_1                     PWR_CR_VOS_1
#define PWR_VosLevel_2                     PWR_CR_VOS_2
#define PWR_VosLevel_3                     PWR_CR_VOS_3
#define IS_PWR_VOS_LEVEL(LEVEL)            (((LEVEL) == PWR_VosLevel_0) || \
                                            ((LEVEL) == PWR_VosLevel_1) || \
                                            ((LEVEL) == PWR_VosLevel_2) || \
                                            ((LEVEL) == PWR_VosLevel_3)  )
/**
  * @}
  */

/** @defgroup PWR_PVDR_detection_level
  * @brief
  * @{
  */
#define PWR_PVDRLevel_0                  PWR_CR_PLSR_0
#define PWR_PVDRLevel_1                  PWR_CR_PLSR_1
#define PWR_PVDRLevel_2                  PWR_CR_PLSR_2
#define PWR_PVDRLevel_3                  PWR_CR_PLSR_3
#define PWR_PVDRLevel_4                  PWR_CR_PLSR_4
#define PWR_PVDRLevel_5                  PWR_CR_PLSR_5
#define PWR_PVDRLevel_6                  PWR_CR_PLSR_6
#define PWR_PVDRLevel_7                  PWR_CR_PLSR_7

#define IS_PWR_PVDR_LEVEL(LEVEL) (((LEVEL) == PWR_PVDRLevel_0) || ((LEVEL) == PWR_PVDRLevel_1)|| \
                                  ((LEVEL) == PWR_PVDRLevel_2) || ((LEVEL) == PWR_PVDRLevel_3)|| \
                                  ((LEVEL) == PWR_PVDRLevel_4) || ((LEVEL) == PWR_PVDRLevel_5)|| \
                                  ((LEVEL) == PWR_PVDRLevel_6) || ((LEVEL) == PWR_PVDRLevel_7)   )
/**
  * @}
  */

/** @defgroup PWR_PVDF_detection_level
  * @brief
  * @{
  */
#define PWR_PVDFLevel_0                  PWR_CR_PLSF_0
#define PWR_PVDFLevel_1                  PWR_CR_PLSF_1
#define PWR_PVDFLevel_2                  PWR_CR_PLSF_2
#define PWR_PVDFLevel_3                  PWR_CR_PLSF_3
#define PWR_PVDFLevel_4                  PWR_CR_PLSF_4
#define PWR_PVDFLevel_5                  PWR_CR_PLSF_5
#define PWR_PVDFLevel_6                  PWR_CR_PLSF_6
#define PWR_PVDFLevel_7                  PWR_CR_PLSF_7

#define IS_PWR_PVDF_LEVEL(LEVEL) (((LEVEL) == PWR_PVDFLevel_0) || ((LEVEL) == PWR_PVDFLevel_1)|| \
                                  ((LEVEL) == PWR_PVDFLevel_2) || ((LEVEL) == PWR_PVDFLevel_3)|| \
                                  ((LEVEL) == PWR_PVDFLevel_4) || ((LEVEL) == PWR_PVDFLevel_5)|| \
                                  ((LEVEL) == PWR_PVDFLevel_6) || ((LEVEL) == PWR_PVDFLevel_7)   )
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Pins
  * @{
  */

#define PWR_WakeUpPin_1                 PWR_CSR_EWUP_PA0
#define PWR_WakeUpPin_2                 PWR_CSR_EWUP_PC13
#define PWR_WakeUpPin_3                 PWR_CSR_EWUP_PA2
#define IS_PWR_WAKEUP_PIN(PIN)    (((PIN) == PWR_WakeUpPin_1) || ((PIN) == PWR_WakeUpPin_2) || \
                                   ((PIN) == PWR_WakeUpPin_3))
/**
  * @}
  */

/** @defgroup PWR_Regulator_state_is_Sleep_STOP_mode
  * @{
  */
#define PWR_Regulator_ON                ((uint32_t)0x00000000)
#define PWR_Regulator_LowPower          PWR_CR_LPDS
#define IS_PWR_REGULATOR(REGULATOR)     (((REGULATOR) == PWR_Regulator_ON) || \
                                         ((REGULATOR) == PWR_Regulator_LowPower))
/**
  * @}
  */


/** @defgroup PWR_Sleep_mode_entry
  * @{
  */
#define PWR_SleepEntry_WFI              ((uint8_t)0x01)
#define PWR_SleepEntry_WFE              ((uint8_t)0x02)
#define PWR_SleepEntry_SLEEPONEXIT      ((uint8_t)0x03)
#define IS_PWR_SLEEP_ENTRY(ENTRY)       (((ENTRY) == PWR_SleepEntry_WFI) || ((ENTRY) == PWR_SleepEntry_WFE) || \
                                         ((ENTRY) == PWR_SleepEntry_SLEEPONEXIT))
/**
  * @}
  */

/** @defgroup PWR_Stop_mode_entry
  * @{
  */
#define PWR_StopEntry_WFI               ((uint8_t)0x01)
#define PWR_StopEntry_WFE               ((uint8_t)0x02)
#define IS_PWR_STOP_ENTRY(ENTRY)        (((ENTRY) == PWR_StopEntry_WFI) || ((ENTRY) == PWR_StopEntry_WFE))
/**
  * @}
  */

/** @defgroup PWR_Standby_mode_entry
  * @{
  */
#define PWR_StandbyEntry_WFI            ((uint8_t)0x01)
#define PWR_StandbyEntry_WFE            ((uint8_t)0x02)
#define IS_PWR_STANDBY_ENTRY(ENTRY)    (((ENTRY) == PWR_StandbyEntry_WFI) || ((ENTRY) == PWR_StandbyEntry_WFE))
/**
  * @}
  */



/** @defgroup PWR_Flag
  * @{
  */
#define PWR_FLAG_WU                     PWR_CSR_WUF
#define PWR_FLAG_SB                     PWR_CSR_SBF
#define PWR_FLAG_PVDO                   PWR_CSR_PVDO
#define PWR_FLAG_BRR                    PWR_CSR_BRR
#define PWR_FLAG_VREFINTRDY             PWR_CSR_VOSRDY
#define IS_PWR_GET_FLAG(FLAG)           (((FLAG) == PWR_FLAG_WU)   || ((FLAG) == PWR_FLAG_SB)  || \
                                         ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_FLAG_BRR) || \
                                         ((FLAG) == PWR_FLAG_VREFINTRDY))
/**
  * @}
  */

/** @defgroup PWR_Flag_Clear
  * @{
  */
#define PWR_FLAG_CWU                    PWR_CR_CWUF
#define PWR_FLAG_CSB                    PWR_CR_CSBF
#define IS_PWR_CLEAR_FLAG(FLAG)         (((FLAG) == PWR_FLAG_CWU)  || \
                                         ((FLAG) == PWR_FLAG_CSB))
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the PWR configuration to the default reset state ******/
void PWR_DeInit(void);

/* Vbat charge and charge resistance choose function ******/
void PWR_VbatCharge(FunctionalState NewState);
void PWR_VbatResConfig(uint32_t PWR_VbatRes);

/* Main Voltage Regulator choose function ******/
void PWR_VosLevelConfig(uint32_t PWR_VosLevel);

/* Backup Domain Access function **********************************************/
void PWR_BackupAccessCmd(FunctionalState NewState);

/* PVD configuration functions ************************************************/
void PWR_PVDEnable(FunctionalState NewState);
void PWR_PVDRLevelConfig(uint32_t PWR_PVDRLevel);
void PWR_PVDFLevelConfig(uint32_t PWR_PVDFLevel);

/* PDROFF enable functions ************************************************/
void PWR_PdroffEnable(FunctionalState NewState);

/* WakeUp pins configuration functions ****************************************/
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState);

/* Backup Regulator Enable ************************************************/
void PWR_BreEnable(FunctionalState NewState);

/* Low Power modes configuration functions ************************************/
void PWR_EnterSleepMode(uint8_t PWR_SleepEntry);
void PWR_EnterStopMode(uint32_t PWR_Regulator, uint8_t PWR_StopEntry);
void PWR_EnterStandbyMode(uint8_t PWR_StandbyEntry);

/* Flags management functions *************************************************/
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __FT32F0XX_PWR_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
