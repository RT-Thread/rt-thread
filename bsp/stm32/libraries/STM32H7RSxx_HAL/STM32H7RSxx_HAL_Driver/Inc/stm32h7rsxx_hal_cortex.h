/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_cortex.h
  * @author  MCD Application Team
  * @brief   Header file of CORTEX HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_CORTEX_H
#define STM32H7RSxx_HAL_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @defgroup CORTEX CORTEX
  * @brief CORTEX HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Types CORTEX Exported Types
  * @{
  */

/** @defgroup CORTEX_MPU_Region_Initialization_Structure_definition MPU Region Initialization Structure Definition
  * @brief  MPU Region initialization structure
  * @{
  */
typedef struct
{
  uint8_t  Enable;                /*!< Specifies the status of the region.
                                       This parameter can be a value of @ref CORTEX_MPU_Region_Enable                 */
  uint8_t  Number;                /*!< Specifies the number of the region to protect.
                                       This parameter can be a value of @ref CORTEX_MPU_Region_Number                 */
  uint32_t BaseAddress;           /*!< Specifies the base address of the region to protect.
                                                                                                                      */
  uint8_t  Size;                  /*!< Specifies the size of the region to protect.
                                       This parameter can be a value of @ref CORTEX_MPU_Region_Size                   */
  uint8_t  SubRegionDisable;      /*!< Specifies the number of the subregion protection to disable.
                                       This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF    */
  uint8_t  TypeExtField;          /*!< Specifies the TEX field level.
                                       This parameter can be a value of @ref CORTEX_MPU_TEX_Levels                    */
  uint8_t  AccessPermission;      /*!< Specifies the region access permission type.
                                       This parameter can be a value of @ref CORTEX_MPU_Region_Permission_Attributes  */
  uint8_t  DisableExec;           /*!< Specifies the instruction access status.
                                       This parameter can be a value of @ref CORTEX_MPU_Instruction_Access            */
  uint8_t  IsShareable;           /*!< Specifies the shareability status of the protected region.
                                       This parameter can be a value of @ref CORTEX_MPU_Access_Shareable              */
  uint8_t  IsCacheable;           /*!< Specifies the cacheable status of the region protected.
                                       This parameter can be a value of @ref CORTEX_MPU_Access_Cacheable              */
  uint8_t  IsBufferable;          /*!< Specifies the bufferable status of the protected region.
                                       This parameter can be a value of @ref CORTEX_MPU_Access_Bufferable             */
} MPU_Region_InitTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup CORTEX_Exported_Constants CORTEX Exported Constants
  * @{
  */

/** @defgroup CORTEX_Preemption_Priority_Group CORTEX Preemption Priority Group
  * @{
  */
#define NVIC_PRIORITYGROUP_0            7U  /*!< 0 bit  for pre-emption priority,
                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1            6U  /*!< 1 bit  for pre-emption priority,
                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2            5U  /*!< 2 bits for pre-emption priority,
                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3            4U  /*!< 3 bits for pre-emption priority,
                                                 1 bit for subpriority  */
#define NVIC_PRIORITYGROUP_4            3U  /*!< 4 bits for pre-emption priority,
                                                 0 bit for subpriority  */
/**
  * @}
  */

/** @defgroup CORTEX_SysTick_clock_source CORTEX SysTick clock source
  * @{
  */
#define SYSTICK_CLKSOURCE_HCLK_DIV8     0U
#define SYSTICK_CLKSOURCE_HCLK          SysTick_CTRL_CLKSOURCE_Msk

/**
  * @}
  */

/** @defgroup CORTEX_MPU_HFNMI_PRIVDEF_Control CORTEX MPU HFNMI and PRIVILEGED Access control
  * @{
  */
#define  MPU_HFNMI_PRIVDEF_NONE         0U
#define  MPU_HARDFAULT_NMI              MPU_CTRL_HFNMIENA_Msk
#define  MPU_PRIVILEGED_DEFAULT         MPU_CTRL_PRIVDEFENA_Msk
#define  MPU_HFNMI_PRIVDEF              (MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk)
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Enable CORTEX MPU Region Enable
  * @{
  */
#define  MPU_REGION_ENABLE              1U
#define  MPU_REGION_DISABLE             0U
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Instruction_Access CORTEX MPU Instruction Access
  * @{
  */
#define  MPU_INSTRUCTION_ACCESS_ENABLE  0U
#define  MPU_INSTRUCTION_ACCESS_DISABLE 1U
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Shareable CORTEX MPU Instruction Access Shareable
  * @{
  */
#define  MPU_ACCESS_NOT_SHAREABLE       0U
#define  MPU_ACCESS_SHAREABLE           1U
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Cacheable CORTEX MPU Instruction Access Cacheable
  * @{
  */
#define MPU_ACCESS_CACHEABLE            1U
#define MPU_ACCESS_NOT_CACHEABLE        0U
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Access_Bufferable CORTEX MPU Instruction Access Bufferable
  * @{
  */
#define MPU_ACCESS_BUFFERABLE           1U
#define MPU_ACCESS_NOT_BUFFERABLE       0U
/**
  * @}
  */

/** @defgroup CORTEX_MPU_TEX_Levels CORTEX MPU TEX Levels
  * @{
  */
#define MPU_TEX_LEVEL0                  0U
#define MPU_TEX_LEVEL1                  1U
#define MPU_TEX_LEVEL2                  2U
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Size CORTEX MPU Region Size
  * @{
  */
#define MPU_REGION_SIZE_32B             0x04U
#define MPU_REGION_SIZE_64B             0x05U
#define MPU_REGION_SIZE_128B            0x06U
#define MPU_REGION_SIZE_256B            0x07U
#define MPU_REGION_SIZE_512B            0x08U
#define MPU_REGION_SIZE_1KB             0x09U
#define MPU_REGION_SIZE_2KB             0x0AU
#define MPU_REGION_SIZE_4KB             0x0BU
#define MPU_REGION_SIZE_8KB             0x0CU
#define MPU_REGION_SIZE_16KB            0x0DU
#define MPU_REGION_SIZE_32KB            0x0EU
#define MPU_REGION_SIZE_64KB            0x0FU
#define MPU_REGION_SIZE_128KB           0x10U
#define MPU_REGION_SIZE_256KB           0x11U
#define MPU_REGION_SIZE_512KB           0x12U
#define MPU_REGION_SIZE_1MB             0x13U
#define MPU_REGION_SIZE_2MB             0x14U
#define MPU_REGION_SIZE_4MB             0x15U
#define MPU_REGION_SIZE_8MB             0x16U
#define MPU_REGION_SIZE_16MB            0x17U
#define MPU_REGION_SIZE_32MB            0x18U
#define MPU_REGION_SIZE_64MB            0x19U
#define MPU_REGION_SIZE_128MB           0x1AU
#define MPU_REGION_SIZE_256MB           0x1BU
#define MPU_REGION_SIZE_512MB           0x1CU
#define MPU_REGION_SIZE_1GB             0x1DU
#define MPU_REGION_SIZE_2GB             0x1EU
#define MPU_REGION_SIZE_4GB             0x1FU
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Permission_Attributes CORTEX MPU Region Permission Attributes
  * @{
  */
#define MPU_REGION_NO_ACCESS            0U
#define MPU_REGION_PRIV_RW              1U
#define MPU_REGION_PRIV_RW_URO          2U
#define MPU_REGION_FULL_ACCESS          3U
#define MPU_REGION_PRIV_RO              5U
#define MPU_REGION_PRIV_RO_URO          6U
/**
  * @}
  */

/** @defgroup CORTEX_MPU_Region_Number CORTEX MPU Region Number
  * @{
  */
#define  MPU_REGION_NUMBER0              0U
#define  MPU_REGION_NUMBER1              1U
#define  MPU_REGION_NUMBER2              2U
#define  MPU_REGION_NUMBER3              3U
#define  MPU_REGION_NUMBER4              4U
#define  MPU_REGION_NUMBER5              5U
#define  MPU_REGION_NUMBER6              6U
#define  MPU_REGION_NUMBER7              7U
#define  MPU_REGION_NUMBER8              8U
#define  MPU_REGION_NUMBER9              9U
#define  MPU_REGION_NUMBER10             10U
#define  MPU_REGION_NUMBER11             11U
#define  MPU_REGION_NUMBER12             12U
#define  MPU_REGION_NUMBER13             13U
#define  MPU_REGION_NUMBER14             14U
#define  MPU_REGION_NUMBER15             15U
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup CORTEX_Exported_Functions CORTEX Exported Functions
  * @{
  */

/** @defgroup CORTEX_Exported_Functions_Group1 Initialization and Configuration functions
  * @brief    Initialization and Configuration functions
  * @{
  */
/* Initialization and Configuration functions *****************************/
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);
/**
  * @}
  */

/** @defgroup CORTEX_Exported_Functions_Group2 Peripheral Control functions
  * @brief   Cortex control functions
  * @{
  */
/* Peripheral Control functions ***********************************************/
uint32_t HAL_NVIC_GetPriorityGrouping(void);
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t *pPreemptPriority, uint32_t *pSubPriority);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);
void HAL_MPU_Enable(uint32_t MPU_Control);
void HAL_MPU_Disable(void);
void HAL_MPU_EnableRegion(uint32_t RegionNumber);
void HAL_MPU_DisableRegion(uint32_t RegionNumber);
void HAL_MPU_ConfigRegion(const MPU_Region_InitTypeDef *pMPU_RegionInit);
void HAL_CORTEX_ClearEvent(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup CORTEX_Private_Macros CORTEX Private Macros
  * @{
  */
#define IS_NVIC_PRIORITY_GROUP(__GROUP__)             (((__GROUP__) == NVIC_PRIORITYGROUP_0) || \
                                                       ((__GROUP__) == NVIC_PRIORITYGROUP_1) || \
                                                       ((__GROUP__) == NVIC_PRIORITYGROUP_2) || \
                                                       ((__GROUP__) == NVIC_PRIORITYGROUP_3) || \
                                                       ((__GROUP__) == NVIC_PRIORITYGROUP_4))

#define IS_NVIC_PREEMPTION_PRIORITY(__PRIO__, __PRIOGRP__)   (((__PRIO__) < (1uL << __NVIC_PRIO_BITS)) && \
                                                              ((__PRIO__) < (0x1uL << (0x07u - __PRIOGRP__))))

#define IS_NVIC_SUB_PRIORITY(__PRIO__, __PRIOGRP__) \
  ((__PRIOGRP__ < (0x07u - __NVIC_PRIO_BITS)) ?\
   ((__PRIO__) < (1u)): \
   ((__PRIO__) < (0x1uL << (__PRIOGRP__ - (0x07u - __NVIC_PRIO_BITS)))))

#define IS_NVIC_DEVICE_IRQ(__IRQ__)                   ((__IRQ__) > SysTick_IRQn)

#define IS_NVIC_PRIO_INTERRUPT(__IT__)                (((__IT__) > HardFault_IRQn) && ((__IT__) != DebugMonitor_IRQn))

#define IS_SYSTICK_CLK_SOURCE(__SOURCE__)             (((__SOURCE__) == SYSTICK_CLKSOURCE_HCLK) || \
                                                       ((__SOURCE__) == SYSTICK_CLKSOURCE_HCLK_DIV8))

#define IS_MPU_REGION_ENABLE(__STATE__)               (((__STATE__) == MPU_REGION_ENABLE) || \
                                                       ((__STATE__) == MPU_REGION_DISABLE))

#define IS_MPU_INSTRUCTION_ACCESS(__STATE__)          (((__STATE__) == MPU_INSTRUCTION_ACCESS_ENABLE) || \
                                                       ((__STATE__) == MPU_INSTRUCTION_ACCESS_DISABLE))

#define IS_MPU_ACCESS_SHAREABLE(__STATE__)            (((__STATE__) == MPU_ACCESS_SHAREABLE) || \
                                                       ((__STATE__) == MPU_ACCESS_NOT_SHAREABLE))

#define IS_MPU_ACCESS_CACHEABLE(__STATE__)            (((__STATE__) == MPU_ACCESS_CACHEABLE) || \
                                                       ((__STATE__) == MPU_ACCESS_NOT_CACHEABLE))

#define IS_MPU_ACCESS_BUFFERABLE(__STATE__)           (((__STATE__) == MPU_ACCESS_BUFFERABLE) || \
                                                       ((__STATE__) == MPU_ACCESS_NOT_BUFFERABLE))

#define IS_MPU_TEX_LEVEL(__TYPE__)                    (((__TYPE__) == MPU_TEX_LEVEL0)  || \
                                                       ((__TYPE__) == MPU_TEX_LEVEL1)  || \
                                                       ((__TYPE__) == MPU_TEX_LEVEL2))

#define IS_MPU_REGION_PERMISSION_ATTRIBUTE(__TYPE__)  (((__TYPE__) == MPU_REGION_NO_ACCESS)   || \
                                                       ((__TYPE__) == MPU_REGION_PRIV_RW)     || \
                                                       ((__TYPE__) == MPU_REGION_PRIV_RW_URO) || \
                                                       ((__TYPE__) == MPU_REGION_FULL_ACCESS) || \
                                                       ((__TYPE__) == MPU_REGION_PRIV_RO)     || \
                                                       ((__TYPE__) == MPU_REGION_PRIV_RO_URO))

#define IS_MPU_REGION_NUMBER(__NUMBER__)              ((__NUMBER__) <= MPU_REGION_NUMBER15)

#define IS_MPU_REGION_SIZE(__SIZE__)                  (((__SIZE__) == MPU_REGION_SIZE_32B)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_64B)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_128B)  || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_256B)  || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_512B)  || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_1KB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_2KB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_4KB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_8KB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_16KB)  || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_32KB)  || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_64KB)  || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_128KB) || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_256KB) || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_512KB) || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_1MB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_2MB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_4MB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_8MB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_16MB)  || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_32MB)  || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_64MB)  || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_128MB) || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_256MB) || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_512MB) || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_1GB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_2GB)   || \
                                                       ((__SIZE__) == MPU_REGION_SIZE_4GB))

#define IS_MPU_SUB_REGION_DISABLE(__SUBREGION__)      ((__SUBREGION__) < (uint16_t)0x00FFU)

#define IS_MPU_ADDRESS_MULTIPLE_SIZE(__ADDRESS__, __SIZE__) (((__ADDRESS__) & ((1<<(__SIZE__+1U))- 1U)) == 0U)

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_CORTEX_H */
