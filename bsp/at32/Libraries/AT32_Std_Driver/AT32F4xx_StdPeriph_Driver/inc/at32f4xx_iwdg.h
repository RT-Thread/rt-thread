/**
 **************************************************************************
 * File Name    : at32f4xx_iwdg.h
 * Description  : at32f4xx IWDG header file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_IWDG_H
#define __AT32F4xx_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup IWDG
  * @{
  */

/** @defgroup IWDG_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Exported_Constants
  * @{
  */

/** @defgroup IWDG_WriteAccess
  * @{
  */

#define IWDG_KeyRegWrite_Enable             ((uint16_t)0x5555)
#define IWDG_KeyRegWrite_Disable            ((uint16_t)0x0000)
#define IS_IWDG_KEY_REG_WRITE(WRITE)        (((WRITE) == IWDG_KeyRegWrite_Enable) || \
                                             ((WRITE) == IWDG_KeyRegWrite_Disable))
/**
  * @}
  */

/** @defgroup IWDG_prescaler
  * @{
  */

#define IWDG_Psc_4                          ((uint8_t)0x00)
#define IWDG_Psc_8                          ((uint8_t)0x01)
#define IWDG_Psc_16                         ((uint8_t)0x02)
#define IWDG_Psc_32                         ((uint8_t)0x03)
#define IWDG_Psc_64                         ((uint8_t)0x04)
#define IWDG_Psc_128                        ((uint8_t)0x05)
#define IWDG_Psc_256                        ((uint8_t)0x06)
#define IS_IWDG_PSC(PSC)                    (((PSC) == IWDG_Psc_4)  || \
                                             ((PSC) == IWDG_Psc_8)  || \
                                             ((PSC) == IWDG_Psc_16) || \
                                             ((PSC) == IWDG_Psc_32) || \
                                             ((PSC) == IWDG_Psc_64) || \
                                             ((PSC) == IWDG_Psc_128)|| \
                                             ((PSC) == IWDG_Psc_256))
/**
  * @}
  */

/** @defgroup IWDG_Flag
  * @{
  */

#define IWDG_FLAG_PSCF                      ((uint16_t)0x0001)
#define IWDG_FLAG_RLDF                      ((uint16_t)0x0002)
#define IS_IWDG_FLAG(FLAG)                  (((FLAG) == IWDG_FLAG_PSCF) || ((FLAG) == IWDG_FLAG_RLDF))
#define IS_IWDG_RLD(RLD)                      ((RLD) <= 0xFFF)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup IWDG_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Exported_Functions
  * @{
  */

void IWDG_KeyRegWrite(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_IWDG_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


