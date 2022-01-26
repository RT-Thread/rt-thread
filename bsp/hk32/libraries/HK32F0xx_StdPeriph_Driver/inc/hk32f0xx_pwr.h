/**
  ******************************************************************************
  * @file    hk32f0xx_pwr.h 
  * @version V1.0.1
  * @date    2019-08-15
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F0XX_PWR_H
#define __HK32F0XX_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f0xx.h"

/** @addtogroup HK32F0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants
  * @{
  */ 

/** @defgroup PWR_PVD_detection_level 
  * @brief    This parameters are only applicable for HK32F051 and HK32F072 devices
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

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLevel_0) || ((LEVEL) == PWR_PVDLevel_1)|| \
                                 ((LEVEL) == PWR_PVDLevel_2) || ((LEVEL) == PWR_PVDLevel_3)|| \
                                 ((LEVEL) == PWR_PVDLevel_4) || ((LEVEL) == PWR_PVDLevel_5)|| \
                                 ((LEVEL) == PWR_PVDLevel_6) || ((LEVEL) == PWR_PVDLevel_7))
/**
  * @}
  */

/** @defgroup PWR_WakeUp_Pins 
  * @{
  */

#define PWR_WakeUpPin_1                 PWR_CSR_EWUP1
#define PWR_WakeUpPin_2                 PWR_CSR_EWUP2
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WakeUpPin_1) || ((PIN) == PWR_WakeUpPin_2) )
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

#endif /* __HK32F0XX_PWR_H */

/**
  * @}
  */

/**
  * @}
  */

