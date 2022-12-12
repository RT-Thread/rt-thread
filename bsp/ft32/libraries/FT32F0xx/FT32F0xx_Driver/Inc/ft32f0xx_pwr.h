/**
  ******************************************************************************
  * @file               ft32f0xx_pwr.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the PWR firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2021-07-01
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F0XX_PWR_H
#define __FT32F0XX_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx.h"



/** @addtogroup PWR
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants
  * @{
  */

/** @defgroup PWR_PVD_detection_level
  * @brief
  * @{
  */

#define PWR_PVDLevel_0                  PWR_CR_PLS_LEV0
#define PWR_PVDLevel_1                  PWR_CR_PLS_LEV1
#define PWR_PVDLevel_2                  PWR_CR_PLS_LEV2
#define PWR_PVDLevel_3                  PWR_CR_PLS_LEV3
#define PWR_PVDLevel_4                  PWR_CR_PLS_LEV4
#define PWR_PVDLevel_5                  PWR_CR_PLS_LEV5
#define PWR_PVDLevel_6                  PWR_CR_PLS_LEV6
#define PWR_PVDLevel_7                  PWR_CR_PLS_LEV7
#define PWR_PVDLevel_8                  PWR_CR_PLS_LEV8
#define PWR_PVDLevel_9                  PWR_CR_PLS_LEV9
#define PWR_PVDLevel_10                 PWR_CR_PLS_LEV10
#define PWR_PVDLevel_11                 PWR_CR_PLS_LEV11
#define PWR_PVDLevel_12                 PWR_CR_PLS_LEV12
#define PWR_PVDLevel_13                 PWR_CR_PLS_LEV13
#define PWR_PVDLevel_14                 PWR_CR_PLS_LEV14
#define PWR_PVDLevel_15                 PWR_CR_PLS_LEV15

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLevel_0) || ((LEVEL) == PWR_PVDLevel_1)|| \
                                 ((LEVEL) == PWR_PVDLevel_2) || ((LEVEL) == PWR_PVDLevel_3)|| \
                                 ((LEVEL) == PWR_PVDLevel_4) || ((LEVEL) == PWR_PVDLevel_5)|| \
                                 ((LEVEL) == PWR_PVDLevel_6) || ((LEVEL) == PWR_PVDLevel_7)|| \
                                 ((LEVEL) == PWR_PVDLevel_8) || ((LEVEL) == PWR_PVDLevel_9)|| \
                                 ((LEVEL) == PWR_PVDLevel_10) || ((LEVEL) == PWR_PVDLevel_11)|| \
                                 ((LEVEL) == PWR_PVDLevel_12) || ((LEVEL) == PWR_PVDLevel_13)|| \
                                 ((LEVEL) == PWR_PVDLevel_14) || ((LEVEL) == PWR_PVDLevel_15))
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Pins
  * @{
  */

#define PWR_WakeUpPin_1                 PWR_CSR_EWUP1
#define PWR_WakeUpPin_2                 PWR_CSR_EWUP2
#define PWR_WakeUpPin_3                 PWR_CSR_EWUP3
#define PWR_WakeUpPin_4                 PWR_CSR_EWUP4
#define PWR_WakeUpPin_5                 PWR_CSR_EWUP5
#define PWR_WakeUpPin_6                 PWR_CSR_EWUP6
#define PWR_WakeUpPin_7                 PWR_CSR_EWUP7
#define PWR_WakeUpPin_8                 PWR_CSR_EWUP8
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WakeUpPin_1) || ((PIN) == PWR_WakeUpPin_2) || \
                                ((PIN) == PWR_WakeUpPin_3) || ((PIN) == PWR_WakeUpPin_4) || \
                                ((PIN) == PWR_WakeUpPin_5) || ((PIN) == PWR_WakeUpPin_6) || \
                                ((PIN) == PWR_WakeUpPin_7) || ((PIN) == PWR_WakeUpPin_8))
/**
  * @}
  */


/** @defgroup PWR_Regulator_state_is_Sleep_STOP_mode
  * @{
  */

#define PWR_Regulator_ON                ((uint32_t)0x00000000)
#define PWR_Regulator_LowPower          PWR_CR_LPSDSR
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_Regulator_ON) || \
                                     ((REGULATOR) == PWR_Regulator_LowPower))
/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry
  * @{
  */

#define PWR_SLEEPEntry_WFI              ((uint8_t)0x01)
#define PWR_SLEEPEntry_WFE              ((uint8_t)0x02)
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPEntry_WFI) || ((ENTRY) == PWR_SLEEPEntry_WFE))

/**
  * @}
  */

/** @defgroup PWR_STOP_mode_entry
  * @{
  */

#define PWR_STOPEntry_WFI               ((uint8_t)0x01)
#define PWR_STOPEntry_WFE               ((uint8_t)0x02)
#define PWR_STOPEntry_SLEEPONEXIT       ((uint8_t)0x03)
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPEntry_WFI) || ((ENTRY) == PWR_STOPEntry_WFE) ||\
                                  ((ENTRY) == PWR_STOPEntry_SLEEPONEXIT))

/**
  * @}
  */

/** @defgroup PWR_Flag
  * @{
  */

#define PWR_FLAG_WU                     PWR_CSR_WUF
#define PWR_FLAG_SB                     PWR_CSR_SBF
#define PWR_FLAG_PVDO                   PWR_CSR_PVDO
#define PWR_FLAG_VREFINTRDY             PWR_CSR_VREFINTRDYF

#define IS_PWR_GET_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB) || \
                               ((FLAG) == PWR_FLAG_PVDO) || ((FLAG) == PWR_FLAG_VREFINTRDY))

#define IS_PWR_CLEAR_FLAG(FLAG) (((FLAG) == PWR_FLAG_WU) || ((FLAG) == PWR_FLAG_SB))
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

/* Backup Domain Access function **********************************************/
void PWR_BackupAccessCmd(FunctionalState NewState);

/* PVD configuration functions ************************************************/
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_PVDCmd(FunctionalState NewState);

/* WakeUp pins configuration functions ****************************************/
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPin, FunctionalState NewState);

/* Low Power modes configuration functions ************************************/
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);

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
