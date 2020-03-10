/**
 **************************************************************************
 * File Name    : at32f4xx_wwdg.h
 * Description  : at32f4xx WWDG header file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_WWDG_H
#define __AT32F4xx_WWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup WWDG
  * @{
  */

/** @defgroup WWDG_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup WWDG_Exported_Constants
  * @{
  */

/** @defgroup WWDG_Prescaler
  * @{
  */

#define WWDG_Psc_1                          ((uint32_t)0x00000000)
#define WWDG_Psc_2                          ((uint32_t)0x00000080)
#define WWDG_Psc_4                          ((uint32_t)0x00000100)
#define WWDG_Psc_8                          ((uint32_t)0x00000180)
#define IS_WWDG_PSC(PSC)                    (((PSC) == WWDG_Psc_1) || \
                                             ((PSC) == WWDG_Psc_2) || \
                                             ((PSC) == WWDG_Psc_4) || \
                                             ((PSC) == WWDG_Psc_8))
#define IS_WWDG_WCNTR(WCNTR)                ((WCNTR) <= 0x7F)
#define IS_WWDG_CNTR(CNTR)                  (((CNTR) >= 0x40) && ((CNTR) <= 0x7F))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup WWDG_Exported_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup WWDG_Exported_Functions
  * @{
  */

void WWDG_Reset(void);
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowCounter(uint8_t WindowValue);
void WWDG_EnableINT(void);
void WWDG_SetCounter(uint8_t Counter);
void WWDG_Enable(uint8_t Counter);
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* __AT32F4xx_WWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


