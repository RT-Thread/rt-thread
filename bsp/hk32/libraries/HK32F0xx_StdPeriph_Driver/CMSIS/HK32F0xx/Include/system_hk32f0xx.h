/**
  ******************************************************************************
  * @file    system_hk32f0xx.h 
  ****************************************************************************** 
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup hk32f0xx_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_HK32F0XX_H
#define __SYSTEM_HK32F0XX_H

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup HK32F0xx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup HK32F0xx_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */

/** @addtogroup HK32F0xx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup HK32F0xx_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup HK32F0xx_System_Exported_Functions
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

#endif /*__SYSTEM_HK32F0XX_H */

/**
  * @}
  */


