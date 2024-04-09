/**
  ******************************************************************************
  * @file    stm32h7rsxx_ll_cortex.h
  * @author  MCD Application Team
  * @brief   Header file of CORTEX LL module.
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
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL CORTEX driver contains a set of generic APIs that can be
    used by user:
      (+) SYSTICK configuration used by @ref LL_mDelay and @ref LL_Init1msTick
          functions
      (+) Low power mode configuration (SCB register of Cortex-MCU)
      (+) API to access to MCU info (CPUID register)
      (+) API to enable fault handler (SHCSR accesses)
      (+) API to enable and disable the MPU
      (+) API to configure the region of MPU
      (+) API to configure the attributes region of MPU

  @endverbatim
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_LL_CORTEX_H
#define STM32H7RSxx_LL_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx.h"

/** @addtogroup STM32H7RSxx_LL_Driver
  * @{
  */

/** @defgroup CORTEX_LL CORTEX
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Constants CORTEX LL Exported Constants
  * @{
  */

/** @defgroup CORTEX_LL_EC_CLKSOURCE_HCLK CORTEX LL SYSTICK Clock Source
  * @{
  */
#define LL_SYSTICK_CLKSOURCE_HCLK_DIV8     0U                          /*!< AHB clock divided by 8 selected as SysTick
                                                                            clock source */
#define LL_SYSTICK_CLKSOURCE_HCLK          SysTick_CTRL_CLKSOURCE_Msk  /*!< AHB clock selected as SysTick
                                                                            clock source */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_FAULT CORTEX LL Handler Fault type
  * @{
  */
#define LL_HANDLER_FAULT_USG               SCB_SHCSR_USGFAULTENA_Msk              /*!< Usage fault */
#define LL_HANDLER_FAULT_BUS               SCB_SHCSR_BUSFAULTENA_Msk              /*!< Bus fault */
#define LL_HANDLER_FAULT_MEM               SCB_SHCSR_MEMFAULTENA_Msk              /*!< Memory management fault */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_CTRL_HFNMI_PRIVDEF CORTEX LL MPU HFNMI and PRIVILEGED Access control
  * @{
  */
#define LL_MPU_CTRL_HFNMI_PRIVDEF_NONE     0U                                                /*!< Disable NMI and privileged SW access */
#define LL_MPU_CTRL_HARDFAULT_NMI          MPU_CTRL_HFNMIENA_Msk                             /*!< Enables the operation of MPU during hard fault, NMI, and FAULTMASK handlers */
#define LL_MPU_CTRL_PRIVILEGED_DEFAULT     MPU_CTRL_PRIVDEFENA_Msk                           /*!< Enable privileged software access to default memory map */
#define LL_MPU_CTRL_HFNMI_PRIVDEF          (MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk) /*!< Enable NMI and privileged SW access */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_REGION CORTEX LL MPU Region Number
  * @{
  */
#define LL_MPU_REGION_NUMBER0              0U  /*!< REGION Number 0  */
#define LL_MPU_REGION_NUMBER1              1U  /*!< REGION Number 1  */
#define LL_MPU_REGION_NUMBER2              2U  /*!< REGION Number 2  */
#define LL_MPU_REGION_NUMBER3              3U  /*!< REGION Number 3  */
#define LL_MPU_REGION_NUMBER4              4U  /*!< REGION Number 4  */
#define LL_MPU_REGION_NUMBER5              5U  /*!< REGION Number 5  */
#define LL_MPU_REGION_NUMBER6              6U  /*!< REGION Number 6  */
#define LL_MPU_REGION_NUMBER7              7U  /*!< REGION Number 7  */
#define LL_MPU_REGION_NUMBER8              8U  /*!< REGION Number 8  */
#define LL_MPU_REGION_NUMBER9              9U  /*!< REGION Number 9  */
#define LL_MPU_REGION_NUMBER10             10U /*!< REGION Number 10 */
#define LL_MPU_REGION_NUMBER11             11U /*!< REGION Number 11 */
#define LL_MPU_REGION_NUMBER12             12U /*!< REGION Number 12 */
#define LL_MPU_REGION_NUMBER13             13U /*!< REGION Number 13 */
#define LL_MPU_REGION_NUMBER14             14U /*!< REGION Number 14 */
#define LL_MPU_REGION_NUMBER15             15U /*!< REGION Number 15 */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_REGION_SIZE CORTEX LL MPU Region Size
  * @{
  */
#define LL_MPU_REGION_SIZE_32B             (0x04UL << MPU_RASR_SIZE_Pos) /*!< 32B Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_64B             (0x05UL << MPU_RASR_SIZE_Pos) /*!< 64B Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_128B            (0x06UL << MPU_RASR_SIZE_Pos) /*!< 128B Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_256B            (0x07UL << MPU_RASR_SIZE_Pos) /*!< 256B Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_512B            (0x08UL << MPU_RASR_SIZE_Pos) /*!< 512B Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_1KB             (0x09UL << MPU_RASR_SIZE_Pos) /*!< 1KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_2KB             (0x0AUL << MPU_RASR_SIZE_Pos) /*!< 2KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_4KB             (0x0BUL << MPU_RASR_SIZE_Pos) /*!< 4KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_8KB             (0x0CUL << MPU_RASR_SIZE_Pos) /*!< 8KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_16KB            (0x0DUL << MPU_RASR_SIZE_Pos) /*!< 16KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_32KB            (0x0EUL << MPU_RASR_SIZE_Pos) /*!< 32KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_64KB            (0x0FUL << MPU_RASR_SIZE_Pos) /*!< 64KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_128KB           (0x10UL << MPU_RASR_SIZE_Pos) /*!< 128KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_256KB           (0x11UL << MPU_RASR_SIZE_Pos) /*!< 256KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_512KB           (0x12UL << MPU_RASR_SIZE_Pos) /*!< 512KB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_1MB             (0x13UL << MPU_RASR_SIZE_Pos) /*!< 1MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_2MB             (0x14UL << MPU_RASR_SIZE_Pos) /*!< 2MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_4MB             (0x15UL << MPU_RASR_SIZE_Pos) /*!< 4MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_8MB             (0x16UL << MPU_RASR_SIZE_Pos) /*!< 8MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_16MB            (0x17UL << MPU_RASR_SIZE_Pos) /*!< 16MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_32MB            (0x18UL << MPU_RASR_SIZE_Pos) /*!< 32MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_64MB            (0x19UL << MPU_RASR_SIZE_Pos) /*!< 64MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_128MB           (0x1AUL << MPU_RASR_SIZE_Pos) /*!< 128MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_256MB           (0x1BUL << MPU_RASR_SIZE_Pos) /*!< 256MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_512MB           (0x1CUL << MPU_RASR_SIZE_Pos) /*!< 512MB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_1GB             (0x1DUL << MPU_RASR_SIZE_Pos) /*!< 1GB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_2GB             (0x1EUL << MPU_RASR_SIZE_Pos) /*!< 2GB Size of the MPU protection region */
#define LL_MPU_REGION_SIZE_4GB             (0x1FUL << MPU_RASR_SIZE_Pos) /*!< 4GB Size of the MPU protection region */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_REGION_PRIVILEDGES CORTEX LL MPU Region Privileges
  * @{
  */
#define LL_MPU_REGION_NO_ACCESS            (0U << MPU_RASR_AP_Pos) /*!< No access*/
#define LL_MPU_REGION_PRIV_RW              (1U << MPU_RASR_AP_Pos) /*!< RW privileged (privileged access only)*/
#define LL_MPU_REGION_PRIV_RW_URO          (2U << MPU_RASR_AP_Pos) /*!< RW privileged - RO user (Write in a user program generates a fault) */
#define LL_MPU_REGION_FULL_ACCESS          (3U << MPU_RASR_AP_Pos) /*!< RW privileged & user (Full access) */
#define LL_MPU_REGION_PRIV_RO              (5U << MPU_RASR_AP_Pos) /*!< RO privileged (privileged read only)*/
#define LL_MPU_REGION_PRIV_RO_URO          (6U << MPU_RASR_AP_Pos) /*!< RO privileged & user (read only) */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_TEX CORTEX LL MPU TEX Level
  * @{
  */
#define LL_MPU_TEX_LEVEL0                  (0U << MPU_RASR_TEX_Pos) /*!< b000 for TEX bits */
#define LL_MPU_TEX_LEVEL1                  (1U << MPU_RASR_TEX_Pos) /*!< b001 for TEX bits */
#define LL_MPU_TEX_LEVEL2                  (2U << MPU_RASR_TEX_Pos) /*!< b010 for TEX bits */
#define LL_MPU_TEX_LEVEL4                  (4U << MPU_RASR_TEX_Pos) /*!< b100 for TEX bits */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_INSTRUCTION_ACCESS CORTEX LL MPU Instruction Access
  * @{
  */
#define LL_MPU_INSTRUCTION_ACCESS_ENABLE   0U               /*!< Instruction fetches enabled */
#define LL_MPU_INSTRUCTION_ACCESS_DISABLE  MPU_RASR_XN_Msk  /*!< Instruction fetches disabled*/
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_SHAREABLE_ACCESS CORTEX LL MPU Shareable Access
  * @{
  */
#define LL_MPU_ACCESS_SHAREABLE            MPU_RASR_S_Msk   /*!< Shareable memory attribute */
#define LL_MPU_ACCESS_NOT_SHAREABLE        0U               /*!< Not Shareable memory attribute */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_CACHEABLE_ACCESS CORTEX LL MPU Cacheable Access
  * @{
  */
#define LL_MPU_ACCESS_CACHEABLE            MPU_RASR_C_Msk   /*!< Cacheable memory attribute */
#define LL_MPU_ACCESS_NOT_CACHEABLE        0U               /*!< Not Cacheable memory attribute */
/**
  * @}
  */

/** @defgroup CORTEX_LL_EC_BUFFERABLE_ACCESS CORTEX LL MPU Bufferable Access
  * @{
  */
#define LL_MPU_ACCESS_BUFFERABLE           MPU_RASR_B_Msk   /*!< Bufferable memory attribute */
#define LL_MPU_ACCESS_NOT_BUFFERABLE       0U               /*!< Not Bufferable memory attribute */
/**
  * @}
  */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup CORTEX_LL_Exported_Functions CORTEX LL Exported Functions
  * @{
  */

/** @defgroup CORTEX_LL_EF_SYSTICK CORTEX LL SYSTICK
  * @brief CORTEX SYSTICK LL module driver
  * @{
  */

/**
  * @brief  This function checks if the Systick counter flag is active or not.
  * @note   It can be used in timeout function on application side.
  * @rmtoll STK_CTRL     COUNTFLAG     LL_SYSTICK_IsActiveCounterFlag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSTICK_IsActiveCounterFlag(void)
{
  return (((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Configures the SysTick clock source
  * @rmtoll STK_CTRL     CLKSOURCE     LL_SYSTICK_SetClkSource
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK_DIV8
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK
  * @retval None
  */
__STATIC_INLINE void LL_SYSTICK_SetClkSource(uint32_t Source)
{
  MODIFY_REG(SysTick->CTRL, LL_SYSTICK_CLKSOURCE_HCLK, Source);
}

/**
  * @brief  Get the SysTick clock source
  * @rmtoll STK_CTRL     CLKSOURCE     LL_SYSTICK_GetClkSource
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK_DIV8
  *         @arg @ref LL_SYSTICK_CLKSOURCE_HCLK
  */
__STATIC_INLINE uint32_t LL_SYSTICK_GetClkSource(void)
{
  return READ_BIT(SysTick->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
}

/**
  * @brief  Enable SysTick exception request
  * @rmtoll STK_CTRL     TICKINT       LL_SYSTICK_EnableIT
  * @retval None
  */
__STATIC_INLINE void LL_SYSTICK_EnableIT(void)
{
  SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Disable SysTick exception request
  * @rmtoll STK_CTRL     TICKINT       LL_SYSTICK_DisableIT
  * @retval None
  */
__STATIC_INLINE void LL_SYSTICK_DisableIT(void)
{
  CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

/**
  * @brief  Checks if the SYSTICK interrupt is enabled or disabled.
  * @rmtoll STK_CTRL     TICKINT       LL_SYSTICK_IsEnabledIT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSTICK_IsEnabledIT(void)
{
  return ((READ_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk) == (SysTick_CTRL_TICKINT_Msk)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup CORTEX_LL_EF_LOW_POWER_MODE CORTEX LL LOW POWER MODE
  * @{
  */

/**
  * @brief  Processor uses sleep as its low power mode
  * @rmtoll SCB_SCR      SLEEPDEEP     LL_LPM_EnableSleep
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableSleep(void)
{
  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);
}

/**
  * @brief  Processor uses deep sleep as its low power mode
  * @rmtoll SCB_SCR      SLEEPDEEP     LL_LPM_EnableDeepSleep
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableDeepSleep(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);
}

/**
  * @brief  Configures sleep-on-exit when returning from Handler mode to Thread mode.
  * @note   Setting this bit to 1 enables an interrupt-driven application to avoid returning to an
  *         empty main application.
  * @rmtoll SCB_SCR      SLEEPONEXIT   LL_LPM_EnableSleepOnExit
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableSleepOnExit(void)
{
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Do not sleep when returning to Thread mode.
  * @rmtoll SCB_SCR      SLEEPONEXIT   LL_LPM_DisableSleepOnExit
  * @retval None
  */
__STATIC_INLINE void LL_LPM_DisableSleepOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Enabled events and all interrupts, including disabled interrupts, can wakeup the
  *         processor.
  * @rmtoll SCB_SCR      SEVEONPEND    LL_LPM_EnableEventOnPend
  * @retval None
  */
__STATIC_INLINE void LL_LPM_EnableEventOnPend(void)
{
  /* Set SEVEONPEND bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Only enabled interrupts or events can wakeup the processor, disabled interrupts are
  *         excluded
  * @rmtoll SCB_SCR      SEVEONPEND    LL_LPM_DisableEventOnPend
  * @retval None
  */
__STATIC_INLINE void LL_LPM_DisableEventOnPend(void)
{
  /* Clear SEVEONPEND bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Clear pending events.
  * @retval None
  */
__STATIC_INLINE void LL_LPM_ClearEvent(void)
{
  __SEV();
  __WFE();
}
/**
  * @}
  */

/** @defgroup CORTEX_LL_EF_HANDLER CORTEX LL HANDLER
  * @{
  */

/**
  * @brief  Enable a fault in System handler control register (SHCSR)
  * @rmtoll SCB_SHCSR    USGFAULTENA     LL_HANDLER_EnableFault\n
  *         SCB_SHCSR    BUSFAULTENA     LL_HANDLER_EnableFault\n
  *         SCB_SHCSR    MEMFAULTENA     LL_HANDLER_EnableFault
  * @param  Fault This parameter can be a combination of the following values:
  *         @arg @ref LL_HANDLER_FAULT_USG
  *         @arg @ref LL_HANDLER_FAULT_BUS
  *         @arg @ref LL_HANDLER_FAULT_MEM
  * @retval None
  */
__STATIC_INLINE void LL_HANDLER_EnableFault(uint32_t Fault)
{
  /* Enable the system handler fault */
  SET_BIT(SCB->SHCSR, Fault);
}

/**
  * @brief  Disable a fault in System handler control register (SHCSR)
  * @rmtoll SCB_SHCSR    USGFAULTENA     LL_HANDLER_DisableFault\n
  *         SCB_SHCSR    BUSFAULTENA     LL_HANDLER_DisableFault\n
  *         SCB_SHCSR    MEMFAULTENA     LL_HANDLER_DisableFault
  * @param  Fault This parameter can be a combination of the following values:
  *         @arg @ref LL_HANDLER_FAULT_USG
  *         @arg @ref LL_HANDLER_FAULT_BUS
  *         @arg @ref LL_HANDLER_FAULT_MEM
  * @retval None
  */
__STATIC_INLINE void LL_HANDLER_DisableFault(uint32_t Fault)
{
  /* Disable the system handler fault */
  CLEAR_BIT(SCB->SHCSR, Fault);
}

/**
  * @}
  */

/** @defgroup CORTEX_LL_EF_MCU_INFO CORTEX LL MCU INFO
  * @{
  */

/**
  * @brief  Get Implementer code
  * @rmtoll SCB_CPUID    IMPLEMENTER   LL_CPUID_GetImplementer
  * @retval Value should be equal to 0x41 for ARM
  */
__STATIC_INLINE uint32_t LL_CPUID_GetImplementer(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_IMPLEMENTER_Msk) >> SCB_CPUID_IMPLEMENTER_Pos);
}

/**
  * @brief  Get Variant number (The r value in the rnpn product revision identifier)
  * @rmtoll SCB_CPUID    VARIANT       LL_CPUID_GetVariant
  * @retval Value between 0 and 255 (0x0: revision 0)
  */
__STATIC_INLINE uint32_t LL_CPUID_GetVariant(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_VARIANT_Msk) >> SCB_CPUID_VARIANT_Pos);
}

/**
  * @brief  Get Architecture version
  * @rmtoll SCB_CPUID    ARCHITECTURE  LL_CPUID_GetArchitecture
  * @retval Value should be equal to 0xF for Cortex-M7
  */
__STATIC_INLINE uint32_t LL_CPUID_GetArchitecture(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_ARCHITECTURE_Msk) >> SCB_CPUID_ARCHITECTURE_Pos);
}

/**
  * @brief  Get Part number
  * @rmtoll SCB_CPUID    PARTNO        LL_CPUID_GetParNo
  * @retval Value should be equal to 0xC27 for Cortex-M7
  */
__STATIC_INLINE uint32_t LL_CPUID_GetParNo(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_PARTNO_Msk) >> SCB_CPUID_PARTNO_Pos);
}

/**
  * @brief  Get Revision number (The p value in the rnpn product revision identifier, indicates patch release)
  * @rmtoll SCB_CPUID    REVISION      LL_CPUID_GetRevision
  * @retval Value between 0 and 255 (0x1: patch 1)
  */
__STATIC_INLINE uint32_t LL_CPUID_GetRevision(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_REVISION_Msk) >> SCB_CPUID_REVISION_Pos);
}

/**
  * @}
  */

/** @defgroup CORTEX_LL_EF_MPU CORTEX LL MPU
  * @{
  */

/**
  * @brief  Enable MPU with input options
  * @rmtoll MPU_CTRL     ENABLE        LL_MPU_Enable
  * @param  MPU_Control This parameter can be one of the following values:
  *         @arg @ref LL_MPU_CTRL_HFNMI_PRIVDEF_NONE
  *         @arg @ref LL_MPU_CTRL_HARDFAULT_NMI
  *         @arg @ref LL_MPU_CTRL_PRIVILEGED_DEFAULT
  *         @arg @ref LL_MPU_CTRL_HFNMI_PRIVDEF
  * @retval None
  */
__STATIC_INLINE void LL_MPU_Enable(uint32_t MPU_Control)
{
  __DMB(); /* Force any outstanding transfers to complete before enabling MPU */

  /* Enable the MPU*/
  WRITE_REG(MPU->CTRL, (MPU_Control | MPU_CTRL_ENABLE_Msk));

  /* Ensure MPU settings take effects */
  __DSB();
  __ISB();
}

/**
  * @brief  Disable MPU
  * @rmtoll MPU_CTRL     ENABLE        LL_MPU_Disable
  * @retval None
  */
__STATIC_INLINE void LL_MPU_Disable(void)
{
  /* Make sure outstanding transfers are done */
  __DMB();

  /* Disable the MPU and clear the control register */
  WRITE_REG(MPU->CTRL, 0U);
}

/**
  * @brief  Check if MPU is enabled or not
  * @rmtoll MPU_CTRL     ENABLE        LL_MPU_IsEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MPU_IsEnabled(void)
{
  return ((READ_BIT(MPU->CTRL, MPU_CTRL_ENABLE_Msk) == (MPU_CTRL_ENABLE_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Enable a MPU region
  * @rmtoll MPU_RASR     ENABLE        LL_MPU_EnableRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @retval None
  */
__STATIC_INLINE void LL_MPU_EnableRegion(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Enable the MPU region */
  SET_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
}

/**
  * @brief  Check if MPU region is enabled or not
  * @rmtoll MPU_RNR     ENABLE        LL_MPU_IsEnabled_Region
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_MPU_IsEnabled_Region(uint32_t Region)
{
  /* Set region index */
  WRITE_REG(MPU->RNR, Region);

  /* Return MPU region status */
  return ((READ_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk) == (MPU_RASR_ENABLE_Msk)) ? 1UL : 0UL);
}

/**
  * @brief  Configure and enable a MPU region
  * @rmtoll MPU_RNR      REGION        LL_MPU_ConfigRegion\n
  *         MPU_RBAR     REGION        LL_MPU_ConfigRegion\n
  *         MPU_RBAR     ADDR          LL_MPU_ConfigRegion\n
  *         MPU_RASR     XN            LL_MPU_ConfigRegion\n
  *         MPU_RASR     AP            LL_MPU_ConfigRegion\n
  *         MPU_RASR     S             LL_MPU_ConfigRegion\n
  *         MPU_RASR     C             LL_MPU_ConfigRegion\n
  *         MPU_RASR     B             LL_MPU_ConfigRegion\n
  *         MPU_RASR     SIZE          LL_MPU_ConfigRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @param  Address Value of region base address
  * @param  SubRegionDisable Sub-region disable value between Min_Data = 0x00 and Max_Data = 0xFF
  * @param  Attributes This parameter can be a combination of the following values:
  *         @arg @ref LL_MPU_REGION_SIZE_32B or @ref LL_MPU_REGION_SIZE_64B or @ref LL_MPU_REGION_SIZE_128B
  *           or @ref LL_MPU_REGION_SIZE_256B or @ref LL_MPU_REGION_SIZE_512B
  *           or @ref LL_MPU_REGION_SIZE_1KB or @ref LL_MPU_REGION_SIZE_2KB or @ref LL_MPU_REGION_SIZE_4KB
  *           or @ref LL_MPU_REGION_SIZE_8KB or @ref LL_MPU_REGION_SIZE_16KB
  *           or @ref LL_MPU_REGION_SIZE_32KB or @ref LL_MPU_REGION_SIZE_64KB or @ref LL_MPU_REGION_SIZE_128KB
  *           or @ref LL_MPU_REGION_SIZE_256KB or @ref LL_MPU_REGION_SIZE_512KB
  *           or @ref LL_MPU_REGION_SIZE_1MB or @ref LL_MPU_REGION_SIZE_2MB or @ref LL_MPU_REGION_SIZE_4MB
  *           or @ref LL_MPU_REGION_SIZE_8MB or @ref LL_MPU_REGION_SIZE_16MB
  *           or @ref LL_MPU_REGION_SIZE_32MB or @ref LL_MPU_REGION_SIZE_64MB or @ref LL_MPU_REGION_SIZE_128MB
  *           or @ref LL_MPU_REGION_SIZE_256MB or @ref LL_MPU_REGION_SIZE_512MB
  *           or @ref LL_MPU_REGION_SIZE_1GB or @ref LL_MPU_REGION_SIZE_2GB or @ref LL_MPU_REGION_SIZE_4GB
  *         @arg @ref LL_MPU_REGION_NO_ACCESS or @ref LL_MPU_REGION_PRIV_RW or @ref LL_MPU_REGION_PRIV_RW_URO
  *           or @ref LL_MPU_REGION_FULL_ACCESS or @ref LL_MPU_REGION_PRIV_RO or @ref LL_MPU_REGION_PRIV_RO_URO
  *         @arg @ref LL_MPU_TEX_LEVEL0 or @ref LL_MPU_TEX_LEVEL1 or @ref LL_MPU_TEX_LEVEL2 or @ref LL_MPU_TEX_LEVEL4
  *         @arg @ref LL_MPU_INSTRUCTION_ACCESS_ENABLE or  @ref LL_MPU_INSTRUCTION_ACCESS_DISABLE
  *         @arg @ref LL_MPU_ACCESS_SHAREABLE or @ref LL_MPU_ACCESS_NOT_SHAREABLE
  *         @arg @ref LL_MPU_ACCESS_CACHEABLE or @ref LL_MPU_ACCESS_NOT_CACHEABLE
  *         @arg @ref LL_MPU_ACCESS_BUFFERABLE or @ref LL_MPU_ACCESS_NOT_BUFFERABLE
  * @retval None
  */
__STATIC_INLINE void LL_MPU_ConfigRegion(uint32_t Region, uint32_t SubRegionDisable, uint32_t Address,
                                         uint32_t Attributes)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Set base address */
  WRITE_REG(MPU->RBAR, (Address & 0xFFFFFFE0U));

  /* Configure MPU */
  WRITE_REG(MPU->RASR, (MPU_RASR_ENABLE_Msk | Attributes | (SubRegionDisable << MPU_RASR_SRD_Pos)));
}

/**
  * @brief  Disable a MPU region
  * @rmtoll MPU_RNR      REGION        LL_MPU_DisableRegion\n
  *         MPU_RASR     ENABLE        LL_MPU_DisableRegion
  * @param  Region This parameter can be one of the following values:
  *         @arg @ref LL_MPU_REGION_NUMBER0
  *         @arg @ref LL_MPU_REGION_NUMBER1
  *         @arg @ref LL_MPU_REGION_NUMBER2
  *         @arg @ref LL_MPU_REGION_NUMBER3
  *         @arg @ref LL_MPU_REGION_NUMBER4
  *         @arg @ref LL_MPU_REGION_NUMBER5
  *         @arg @ref LL_MPU_REGION_NUMBER6
  *         @arg @ref LL_MPU_REGION_NUMBER7
  *         @arg @ref LL_MPU_REGION_NUMBER8
  *         @arg @ref LL_MPU_REGION_NUMBER9
  *         @arg @ref LL_MPU_REGION_NUMBER10
  *         @arg @ref LL_MPU_REGION_NUMBER11
  *         @arg @ref LL_MPU_REGION_NUMBER12
  *         @arg @ref LL_MPU_REGION_NUMBER13
  *         @arg @ref LL_MPU_REGION_NUMBER14
  *         @arg @ref LL_MPU_REGION_NUMBER15
  * @retval None
  */
__STATIC_INLINE void LL_MPU_DisableRegion(uint32_t Region)
{
  /* Set Region number */
  WRITE_REG(MPU->RNR, Region);

  /* Disable the MPU region */
  CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
}

/**
  * @}
  */

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

#endif /* STM32H7RSxx_LL_CORTEX_H */
