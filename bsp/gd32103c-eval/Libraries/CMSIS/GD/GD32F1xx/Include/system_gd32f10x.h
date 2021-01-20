/**
  ******************************************************************************
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Header File.
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup GD32F10x_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_GD32F10X_H
#define __SYSTEM_GD32F10X_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup GD32F10x_System_Includes
  * @{
  */

/**
  * @}
  */

/** @addtogroup GD32F10x_System_Exported_types
  * @{
  */
extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */

/** @addtogroup GD32F10x_System_Exported_Functions
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

#endif /*__SYSTEM_GD32F10X_H */

/**
  * @}
  */

/**
  * @}
  */

