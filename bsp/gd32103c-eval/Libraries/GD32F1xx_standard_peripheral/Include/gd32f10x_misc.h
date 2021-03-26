/**
  ******************************************************************************
  * @brief   MISC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_MISC_H
#define __GD32F10X_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup MISC
  * @{
  */

/** @defgroup MISC_Exported_Types
  * @{
  */

/**
  * @brief  MISC Initial Parameters
  */
typedef struct {
    uint8_t NVIC_IRQ;                    /*!< The IRQ type,detailed in @ref IRQn_Type */

    uint8_t NVIC_IRQPreemptPriority;     /*!< The pre-emption priority of NVIC_IRQ, detailed in @ref NVIC_Priority_Table */

    uint8_t NVIC_IRQSubPriority;         /*!< The  SubPriority  of NVIC_IRQ, detailed in @ref NVIC_Priority_Table */

    TypeState NVIC_IRQEnable;            /*!< Enable or disable the IRQ,this parameter can be ENABLE or DISABLE */

} NVIC_InitPara;

/**
  * @}
  */

/** @defgroup MISC_Exported_Constants
  * @{
  */

/** @defgroup MISC_System_Low_Power
  * @{
  */
#define NVIC_VECTTAB_RAM                    ((uint32_t)0x20000000)
#define NVIC_VECTTAB_FLASH                  ((uint32_t)0x08000000)
#define NVIC_LOWPOWER_SEVONPEND             ((uint8_t)0x10)
#define NVIC_LOWPOWER_SLEEPDEEP             ((uint8_t)0x04)
#define NVIC_LOWPOWER_SLEEPONEXIT           ((uint8_t)0x02)

/**
  * @}
  */

/** @defgroup MISC_Preemption_Priority_Group
  * @{
  */

/* Preemption Priority Group -------------------------------------------------*/
#define NVIC_PRIGROUP_0                     ((uint32_t)0x700) /*!< 0 bits for pre-emption priority 4 bits for subpriority */
#define NVIC_PRIGROUP_1                     ((uint32_t)0x600) /*!< 1 bits for pre-emption priority 3 bits for subpriority */
#define NVIC_PRIGROUP_2                     ((uint32_t)0x500) /*!< 2 bits for pre-emption priority 2 bits for subpriority */
#define NVIC_PRIGROUP_3                     ((uint32_t)0x400) /*!< 3 bits for pre-emption priority 1 bits for subpriority */
#define NVIC_PRIGROUP_4                     ((uint32_t)0x300) /*!< 4 bits for pre-emption priority 0 bits for subpriority */

/**
  * @}
  */

/** @defgroup MISC_SysTick_clock_source
  * @{
  */
#define SYSTICK_CKSOURCE_HCLK_DIV8          ((uint32_t)0xFFFFFFFB)
#define SYSTICK_CKSOURCE_HCLK               ((uint32_t)0x00000004)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup MISC_Exported_Functions
  * @{
  */
void NVIC_Init(NVIC_InitPara *NVIC_InitStruct);
void NVIC_SystemLowPowerConfig(uint8_t LowPowerMode, TypeState NewValue);
void SysTick_CKSource_Enable(uint32_t SysTick_CKSource);
void NVIC_VectTableSet(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_PRIGroup_Enable(uint32_t NVIC_PRIGroup);

#ifdef __cplusplus
}
#endif

#endif /*__GD32F10X_MISC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

