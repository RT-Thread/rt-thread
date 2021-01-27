/**
 **************************************************************************
 * File Name    : system_at32f4xx.h
 * Description  : CMSIS Cortex-M4 system header file.
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup at32f4xx_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_AT32F4xx_H
#define __SYSTEM_AT32F4xx_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup AT32F4xx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup AT32F4xx_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */

/** @addtogroup AT32F4xx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup AT32F4xx_System_Exported_Macros
  * @{
  */
#define HSE_STABLE_DELAY             (5000u)
#define PLL_STABLE_DELAY             (500u)
/**
  * @}
  */

/** @addtogroup AT32F4xx_System_Exported_Functions
  * @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_AT32F4xx_H */

/**
  * @}
  */

/**
  * @}
  */

