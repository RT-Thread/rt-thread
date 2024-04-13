/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal.c
  * @author  MCD Application Team
  * @brief   HAL module driver.
  *          This is the common part of the HAL initialization
  *
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
    The common HAL driver contains a set of generic and common APIs that can be
    used by the PPP peripheral drivers and the user to start using the HAL.
    [..]
    The HAL contains two APIs' categories:
         (+) Common HAL APIs (Version, Init, Tick)
         (+) Services HAL APIs (DBGMCU, SBS)

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @defgroup HAL HAL
  * @brief HAL module driver
  * @{
  */

#ifdef HAL_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define VREFBUF_TIMEOUT_VALUE     (uint32_t)10   /* 10 ms  */

/* Value used to increment hide protection level */
#define SBS_HDPL_INCREMENT_VALUE  (uint8_t)0x6A

/* Value used to lock/unlock debug functionalities */
#define SBS_DEBUG_LOCK_VALUE      (uint8_t)0xC3
#define SBS_DEBUG_UNLOCK_VALUE    (uint8_t)0xB4

/* Mask for SBS_BKLOCKR register update */
#define SBS_BKLOCKR_MASK          (SBS_BKLOCKR_PVD_BL      | \
                                   SBS_BKLOCKR_FLASHECC_BL | \
                                   SBS_BKLOCKR_CM7LCKUP_BL | \
                                   SBS_BKLOCKR_BKRAMECC_BL | \
                                   SBS_BKLOCKR_DTCMECC_BL  | \
                                   SBS_BKLOCKR_ITCMECC_BL  | \
                                   SBS_BKLOCKR_ARAM3ECC_BL | \
                                   SBS_BKLOCKR_ARAM1ECC_BL)

/* Private macro -------------------------------------------------------------*/
/** @defgroup SBS_Private_Macros Private Macros
  * @{
  */
#define IS_SBS_TIMER_BREAK_INPUT(__VALUE__) \
  ((((__VALUE__) & SBS_BKLOCKR_MASK) != 0U) && \
   (((__VALUE__) & ~SBS_BKLOCKR_MASK) == 0U))

#define IS_SBS_IO_COMPENSATION_CODE(__VALUE__) \
  (((__VALUE__) == SBS_IO_CELL_CODE) || \
   ((__VALUE__) == SBS_IO_REGISTER_CODE))

#define IS_SBS_IO_COMPENSATION_CELL_PMOS_VALUE(__VALUE__) (((__VALUE__) < 16U))
#define IS_SBS_IO_COMPENSATION_CELL_NMOS_VALUE(__VALUE__) (((__VALUE__) < 16U))

#define IS_SBS_ETHERNET_PHY(__VALUE__) \
  (((__VALUE__) == SBS_ETHERNET_PHY_GMII_OR_MII) || \
   ((__VALUE__) == SBS_ETHERNET_PHY_RMII))

#define IS_SBS_AXISRAM_WS(__VALUE__) \
  (((__VALUE__) == SBS_AXISRAM_WS_0) || \
   ((__VALUE__) == SBS_AXISRAM_WS_1))
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/** @defgroup HAL_Exported_Variables HAL Exported Variables
  * @{
  */
__IO uint32_t uwTick;
uint32_t uwTickPrio            = (1UL << __NVIC_PRIO_BITS); /* Invalid priority */
HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;  /* 1KHz */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup HAL_Exported_Functions HAL Exported Functions
  * @{
  */

/** @defgroup HAL_Exported_Functions_Group1 Initialization and de-initialization Functions
  *  @brief    Initialization and de-initialization functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the Flash interface the NVIC allocation and initial time base
          clock configuration.
      (+) De-initialize common part of the HAL.
      (+) Configure the time base source to have 1ms time base with a dedicated
          Tick interrupt priority.
        (++) SysTick timer is used by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
        (++) Time base configuration function (HAL_InitTick ()) is called automatically
             at the beginning of the program after reset by HAL_Init() or at any time
             when clock is configured, by HAL_RCC_ClockConfig().
        (++) Source of time base is configured  to generate interrupts at regular
             time intervals. Care must be taken if HAL_Delay() is called from a
             peripheral ISR process, the Tick interrupt line must have higher priority
            (numerically lower) than the peripheral interrupt. Otherwise the caller
            ISR process will be blocked.
       (++) functions affecting time base configurations are declared as __weak
             to make  override possible  in case of other  implementations in user file.
@endverbatim
  * @{
  */

/**
  * @brief  Configure the time base source, NVIC and any required global low level hardware
  *         by calling the HAL_MspInit() callback function to be optionally defined in user file
  *         stm32h7rsxx_hal_msp.c.
  *
  * @note   HAL_Init() function is called at the beginning of program after reset and before
  *         the clock configuration.
  *
  * @note   In the default implementation the System Timer (Systick) is used as source of time base.
  *         The Systick configuration is based on HSI clock, as HSI is the clock
  *         used after a system Reset and the NVIC configuration is set to Priority group 4.
  *         Once done, time base tick starts incrementing: the tick variable counter is incremented
  *         each 1ms in the SysTick_Handler() interrupt handler.
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_Init(void)
{
  HAL_StatusTypeDef  status = HAL_OK;

  /* Set Interrupt Group Priority */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* Use SysTick as time base source and configure 1ms tick */
  if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Init the low level hardware */
    HAL_MspInit();
  }

  /* Return function status */
  return status;
}

/**
  * @brief De-initialize common part of the HAL and stop the source of time base.
  * @note This function is optional.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DeInit(void)
{
  /* Reset of all peripherals */
  __HAL_RCC_APB1_FORCE_RESET();
  __HAL_RCC_APB1_RELEASE_RESET();

  __HAL_RCC_APB2_FORCE_RESET();
  __HAL_RCC_APB2_RELEASE_RESET();

  __HAL_RCC_APB4_FORCE_RESET();
  __HAL_RCC_APB4_RELEASE_RESET();

  __HAL_RCC_APB5_FORCE_RESET();
  __HAL_RCC_APB5_RELEASE_RESET();

  __HAL_RCC_AHB1_FORCE_RESET();
  __HAL_RCC_AHB1_RELEASE_RESET();

  __HAL_RCC_AHB2_FORCE_RESET();
  __HAL_RCC_AHB2_RELEASE_RESET();

  __HAL_RCC_AHB3_FORCE_RESET();
  __HAL_RCC_AHB3_RELEASE_RESET();

  __HAL_RCC_AHB4_FORCE_RESET();
  __HAL_RCC_AHB4_RELEASE_RESET();

  __HAL_RCC_AHB5_FORCE_RESET();
  __HAL_RCC_AHB5_RELEASE_RESET();

  /* De-Init the low level hardware */
  HAL_MspDeInit();

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initialize the MSP.
  * @retval None
  */
__weak void HAL_MspInit(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_MspInit could be implemented in the user file
   */
}

/**
  * @brief  DeInitialize the MSP.
  * @retval None
  */
__weak void HAL_MspDeInit(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_MspDeInit could be implemented in the user file
   */
}

/**
  * @brief This function configures the source of the time base:
  *        The time source is configured to have 1ms time base with a dedicated
  *        Tick interrupt priority.
  * @note This function is called  automatically at the beginning of program after
  *       reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig().
  * @note In the default implementation, SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals.
  *       Care must be taken if HAL_Delay() is called from a peripheral ISR process,
  *       The SysTick interrupt must have higher priority (numerically lower)
  *       than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  *       The function is declared as __weak  to be overwritten  in case of other
  *       implementation  in user file.
  * @param TickPriority  Tick interrupt priority.
  * @retval HAL status
  */
__weak HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  HAL_StatusTypeDef  status = HAL_OK;

  /* Check uwTickFreq for MisraC 2012 (even if uwTickFreq is a enum type that doesn't take the value zero)*/
  if ((uint32_t)uwTickFreq != 0U)
  {
    /*Configure the SysTick to have interrupt in 1ms time basis*/
    if (HAL_SYSTICK_Config(SystemCoreClock / (1000U / (uint32_t)uwTickFreq)) == 0U)
    {
      /* Configure the SysTick IRQ priority */
      if (TickPriority < (1UL << __NVIC_PRIO_BITS))
      {
        HAL_NVIC_SetPriority(SysTick_IRQn, TickPriority, 0U);
        uwTickPrio = TickPriority;
      }
      else
      {
        status = HAL_ERROR;
      }
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  else
  {
    status = HAL_ERROR;
  }

  /* Return function status */
  return status;
}

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group2 HAL Control functions
  *  @brief    HAL Control functions
  *
@verbatim
 ===============================================================================
                      ##### HAL Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Provide a tick value in millisecond
      (+) Provide a blocking delay in millisecond
      (+) Suspend the time base source interrupt
      (+) Resume the time base source interrupt
      (+) Get the HAL API driver version
      (+) Get the device identifier
      (+) Get the device revision identifier

@endverbatim
  * @{
  */

/**
  * @brief This function is called to increment a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @note This function is declared as __weak to be overwritten in case of other
  *      implementations in user file.
  * @retval None
  */
__weak void HAL_IncTick(void)
{
  uwTick += (uint32_t)uwTickFreq;
}

/**
  * @brief Provide a tick value in millisecond.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
__weak uint32_t HAL_GetTick(void)
{
  return uwTick;
}

/**
  * @brief This function returns a tick priority.
  * @retval tick priority
  */
uint32_t HAL_GetTickPrio(void)
{
  return uwTickPrio;
}

/**
  * @brief Set new tick Freq.
  * @param Freq tick frequency
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq)
{
  HAL_StatusTypeDef status  = HAL_OK;
  HAL_TickFreqTypeDef prevTickFreq;

  if (uwTickFreq != Freq)
  {
    /* Back up uwTickFreq frequency */
    prevTickFreq = uwTickFreq;

    /* Update uwTickFreq global variable used by HAL_InitTick() */
    uwTickFreq = Freq;

    /* Apply the new tick Freq  */
    status = HAL_InitTick(uwTickPrio);
    if (status != HAL_OK)
    {
      /* Restore previous tick frequency */
      uwTickFreq = prevTickFreq;
    }
  }

  return status;
}

/**
  * @brief Return tick frequency.
  * @retval Tick frequency.
  *         Value of @ref HAL_TickFreqTypeDef.
  */
HAL_TickFreqTypeDef HAL_GetTickFreq(void)
{
  return uwTickFreq;
}

/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay  specifies the delay time length, in milliseconds.
  * @retval None
  */
__weak void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a period to ensure minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)uwTickFreq;
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval None
  */
__weak void HAL_SuspendTick(void)
{
  /* Disable SysTick Interrupt */
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval None
  */
__weak void HAL_ResumeTick(void)
{
  /* Enable SysTick Interrupt */
  SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief  Return the HAL revision.
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t HAL_GetHalVersion(void)
{
  return STM32H7RSXX_HAL_VERSION;
}

/**
  * @brief  Return the device revision identifier.
  * @retval Device revision identifier
  */
uint32_t HAL_GetREVID(void)
{
  return ((DBGMCU->IDCODE & DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @brief  Return the device identifier.
  * @retval Device identifier
  */
uint32_t HAL_GetDEVID(void)
{
  return (DBGMCU->IDCODE & DBGMCU_IDCODE_DEV_ID);
}

/**
  * @brief  Return the first word of the unique device identifier (UID based on 96 bits)
  * @note   The read address belongs to an area which may contain virgin data generating
  *         double ECC error (as never programmed). Thus, in case of cache activation
  *         the address range 0x08FFF000-0x08FFFFFF should be defined as non-cacheable
  *         through the MPU.
  * @retval Device identifier
  */
uint32_t HAL_GetUIDw0(void)
{
  return (READ_REG(*((uint32_t *)UID_BASE)));
}

/**
  * @brief  Return the second word of the unique device identifier (UID based on 96 bits)
  * @note   The read address belongs to an area which may contain virgin data generating
  *         double ECC error (as never programmed). Thus, in case of cache activation
  *         the address range 0x08FFF000-0x08FFFFFF should be defined as non-cacheable
  *         through the MPU.
  * @retval Device identifier
  */
uint32_t HAL_GetUIDw1(void)
{
  return (READ_REG(*((uint32_t *)(UID_BASE + 4U))));
}

/**
  * @brief  Return the third word of the unique device identifier (UID based on 96 bits)
  * @note   The read address belongs to an area which may contain virgin data generating
  *         double ECC error (as never programmed). Thus, in case of cache activation
  *         the address range 0x08FFF000-0x08FFFFFF should be defined as non-cacheable
  *         through the MPU.
  * @retval Device identifier
  */
uint32_t HAL_GetUIDw2(void)
{
  return (READ_REG(*((uint32_t *)(UID_BASE + 8U))));
}
/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group3 HAL Debug functions
  *  @brief    HAL Debug functions
  *
@verbatim
 ===============================================================================
                      ##### HAL Debug functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Enable/Disable Debug module during SLEEP mode
      (+) Enable/Disable Debug module during STOP mode
      (+) Enable/Disable Debug module during STANDBY mode

@endverbatim
  * @{
  */

/**
  * @brief  Enable the Debug Module during SLEEP mode.
  * @retval None
  */
void HAL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the Debug Module during SLEEP mode.
  * @retval None
  */
void HAL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Enable the Debug Module during STOP mode.
  * @retval None
  */
void HAL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode.
  * @retval None
  */
void HAL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode.
  * @retval None
  */
void HAL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode.
  * @retval None
  */
void HAL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group4 HAL SBS configuration functions
  *  @brief    HAL SBS configuration functions
  *
@verbatim
 ===============================================================================
                      ##### HAL SBS configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Increment/get the HDPL value
      (+) Configure the debug access
      (+) Configure timer break inputs
      (+) Enable/Disable the I/O analog switch voltage booster
      (+) Enable/Disable the I/O analog switch supplied by VDD
      (+) Configure/Enable/Disable the compensation cell (IO, XSPI1, XSPI2)

@endverbatim
  * @{
  */

/**
  * @brief  Get the boot address holding the initial vector table for Cortex-M7.
  * @retval Physical boot address used by the Cortex-M7 after reset
  */
uint32_t HAL_SBS_GetBootAddress(void)
{
  return SBS->BOOTSR;
}

/**
  * @brief  Increment hise protection level.
  * @retval None
  */
void HAL_SBS_IncrementHDPLValue(void)
{
  MODIFY_REG(SBS->HDPLCR, SBS_HDPLCR_INCR_HDPL, SBS_HDPL_INCREMENT_VALUE);
}

/**
  * @brief  Get the current value of the hide protection level.
  * @retval Current hide protection level
  *            This value is one of @ref SBS_HDPL_Value
  */
uint32_t HAL_SBS_GetHDPLValue(void)
{
  return (SBS->HDPLSR & SBS_HDPLSR_HDPL);
}

/**
  * @brief  Open the device access port.
  * @note   This function can be only used when device state is Closed.
  * @retval None
  */
void HAL_SBS_OpenAccessPort(void)
{
  MODIFY_REG(SBS->DBGCR, SBS_DBGCR_AP_UNLOCK, SBS_DEBUG_UNLOCK_VALUE);
}

/**
  * @brief  Open the debug when the hide protection level is authorized.
  * @note   This function can be only used when device state is Closed.
  * @retval None
  */
void HAL_SBS_OpenDebug(void)
{
  MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_UNLOCK, (SBS_DEBUG_UNLOCK_VALUE << SBS_DBGCR_DBG_UNLOCK_Pos));
}

/**
  * @brief  Configure the authenticated debug hide protection level.
  * @note   This function can be only used when device state is Closed.
  * @param  Level Hide protection level where the authenticated debug opens
  *            This value is one of @ref SBS_HDPL_Value (except SBS_HDPL_VALUE_0)
  * @retval HAL_OK if parameter is correct
  *         HAL_ERROR otherwise
  */
HAL_StatusTypeDef HAL_SBS_ConfigDebugLevel(uint32_t Level)
{
  /* Check the parameter */
  assert_param(IS_SBS_HDPL(Level));

  if (Level != SBS_HDPL_VALUE_0)
  {
    MODIFY_REG(SBS->DBGCR, SBS_DBGCR_DBG_AUTH_HDPL, (Level << SBS_DBGCR_DBG_AUTH_HDPL_Pos));
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}

/**
  * @brief  Get the current value of the hide protection level.
  * @note   This function can be only used when device state is Closed.
  * @retval Current hide protection level
  *            This value is one of @ref SBS_HDPL_Value
  */
uint32_t HAL_SBS_GetDebugLevel(void)
{
  return ((SBS->DBGCR & SBS_DBGCR_DBG_AUTH_HDPL) >> SBS_DBGCR_DBG_AUTH_HDPL_Pos);
}

/**
  * @brief  Unlock the access to the debug control register.
  * @note   This function can be only used when device state is Closed.
  * @retval None
  */
void HAL_SBS_UnlockDebugConfig(void)
{
  MODIFY_REG(SBS->DBGLOCKR, SBS_DBGLOCKR_DBGCFG_LOCK, SBS_DEBUG_UNLOCK_VALUE);
}

/**
  * @brief  Lock the access to the debug control register.
  * @note   This function can be only used when device state is Closed.
  * @retval None
  */
void HAL_SBS_LockDebugConfig(void)
{
  MODIFY_REG(SBS->DBGLOCKR, SBS_DBGLOCKR_DBGCFG_LOCK, SBS_DEBUG_LOCK_VALUE);
}

/**
  * @brief  Configure the command passed to the RSS for execution at next reset.
  * @param  Cmd Command passed to the RSS for execution at next reset
  *            This value is between 0 and 0xFFFF
  * @retval None
  */
void HAL_SBS_ConfigRSSCommand(uint32_t Cmd)
{
  MODIFY_REG(SBS->RSSCMDR, SBS_RSSCMDR_RSSCMD, Cmd);
}

/**
  * @brief  Get the command passed to the RSS for execution at next reset.
  * @retval Command passed to the RSS for execution at next reset
  */
uint32_t HAL_SBS_GetRSSCommand(void)
{
  return (SBS->RSSCMDR & SBS_RSSCMDR_RSSCMD);
}

/**
  * @brief  Enable the I/O analog switch voltage booster
  * @note   Insure low VDDA voltage operation with I/O analog switch control
  * @retval None
  */
void HAL_SBS_EnableIOAnalogBooster(void)
{
  MODIFY_REG(SBS->PMCR, (SBS_PMCR_BOOSTEN | SBS_PMCR_BOOSTVDDSEL), SBS_PMCR_BOOSTEN);
}

/**
  * @brief  Disable the I/O analog switch voltage booster
  * @retval None
  */
void HAL_SBS_DisableIOAnalogBooster(void)
{
  CLEAR_BIT(SBS->PMCR, SBS_PMCR_BOOSTEN);
}

/**
  * @brief  Enable the I/O analog switch supplied by VDD
  * @note   To be used when I/O analog switch voltage booster is not enabled
  * @retval None
  */
void HAL_SBS_EnableIOAnalogSwitchVdd(void)
{
  MODIFY_REG(SBS->PMCR, (SBS_PMCR_BOOSTEN | SBS_PMCR_BOOSTVDDSEL), SBS_PMCR_BOOSTVDDSEL);
}

/**
  * @brief  Disable the I/O analog switch supplied by VDD
  * @retval None
  */
void HAL_SBS_DisableIOAnalogSwitchVdd(void)
{
  CLEAR_BIT(SBS->PMCR, SBS_PMCR_BOOSTVDDSEL);
}

/**
  * @brief  Configure the Ethernet PHY interface
  * @param  Config  specifies the Ethernet PHY interface
  *         This parameter can be one of the following values:
  *            @arg SBS_ETHERNET_PHY_GMII_OR_MII GMMI or MII selection
  *            @arg SBS_ETHERNET_PHY_RMII RMII selection
  * @retval None
  */
void HAL_SBS_ConfigEthernetPHY(uint32_t Config)
{
  /* Check the parameter */
  assert_param(IS_SBS_ETHERNET_PHY(Config));

  MODIFY_REG(SBS->PMCR, SBS_PMCR_ETH_PHYSEL, Config);
}

/**
  * @brief  Configure the ECC AXISRAMs wait state when ECC=0
  * @param  Config  specifies the number of wait state
  *         This parameter can be one of the following values:
  *            @arg SBS_AXISRAM_WS_0 0 wait state selection
  *            @arg SBS_AXISRAM_WS_1 1 wait state selection
  * @retval None
  */
void HAL_SBS_ConfigAXISRAMWaitState(uint32_t Config)
{
  /* Check the parameter */
  assert_param(IS_SBS_AXISRAM_WS(Config));

  MODIFY_REG(SBS->PMCR, SBS_PMCR_AXISRAM_WS, Config);
}

/**
  * @brief  Enable the compensation cell
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can the combination of the following values:
  *            @arg SBS_IO_ANALOG_CELL Compensation cell for the I/O analog switches
  *            @arg SBS_IO_XSPI1_CELL Compensation cell for the I/O of the XSPI1
  *            @arg SBS_IO_XSPI2_CELL Compensation cell for the I/O of the XSPI2
  * @retval None
  */
void HAL_SBS_EnableCompensationCell(uint32_t Selection)
{
  /* Check the parameter */
  assert_param(IS_SBS_COMPENSATION_CELL(Selection));

  SET_BIT(SBS->CCCSR, Selection);
}

/**
  * @brief  Disable the compensation cell
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can the combination of the following values:
  *            @arg SBS_IO_ANALOG_CELL Compensation cell for the I/O analog switches
  *            @arg SBS_IO_XSPI1_CELL Compensation cell for the I/O of the XSPI1
  *            @arg SBS_IO_XSPI2_CELL Compensation cell for the I/O of the XSPI2
  * @retval None
  */
void HAL_SBS_DisableCompensationCell(uint32_t Selection)
{
  /* Check the parameter */
  assert_param(IS_SBS_COMPENSATION_CELL(Selection));

  MODIFY_REG(SBS->CCCSR, Selection, 0U);
}

/**
  * @brief  Get the compensation cell ready status
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can one of the following values:
  *            @arg SBS_IO_ANALOG_CELL_READY Compensation cell for the I/O analog switches
  *            @arg SBS_IO_XSPI1_CELL_READY Compensation cell for the I/O of the XSPI1
  *            @arg SBS_IO_XSPI2_CELL_READY Compensation cell for the I/O of the XSPI2
  * @retval Ready status (1 or 0)
  */
uint32_t HAL_SBS_GetCompensationCellReadyStatus(uint32_t Selection)
{
  /* Check the parameter */
  assert_param(IS_SBS_COMPENSATION_CELL_READY(Selection));

  return (((SBS->CCCSR & Selection) == 0U) ? 0UL : 1UL);
}

/**
  * @brief  Configure the code selection for the compensation cell
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can one of the following values:
  *            @arg SBS_IO_ANALOG_CELL Compensation cell for the I/O analog switches
  *            @arg SBS_IO_XSPI1_CELL Compensation cell for the I/O of the XSPI1
  *            @arg SBS_IO_XSPI2_CELL Compensation cell for the I/O of the XSPI2
  * @param  Code code selection to be applied for the I/O compensation cell
  *         This parameter can be one of the following values:
  *            @arg SBS_IO_CELL_CODE  Code from the cell (available in the SBS_CCVALR)
  *            @arg SBS_IO_REGISTER_CODE Code from the compensation cell code register (SBS_CCSWVALR)
  * @param  NmosValue In case SBS_IO_REGISTER_CODE is selected, it  provides the Nmos value
  *                   to apply in range 0 to 15 else this parameter is not used
  * @param  PmosValue In case SBS_IO_REGISTER_CODE is selected, it  provides the Pmos value
  *                   to apply in range 0 to 15 else this parameter is not used
  * @retval None
  */
void HAL_SBS_ConfigCompensationCell(uint32_t Selection, uint32_t Code, uint32_t NmosValue, uint32_t PmosValue)
{
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_SBS_COMPENSATION_CELL(Selection));
  assert_param(IS_SBS_IO_COMPENSATION_CODE(Code));

  if (Code == SBS_IO_REGISTER_CODE)
  {
    /* Check the parameters */
    assert_param(IS_SBS_IO_COMPENSATION_CELL_NMOS_VALUE(NmosValue));
    assert_param(IS_SBS_IO_COMPENSATION_CELL_PMOS_VALUE(PmosValue));

    offset = ((Selection == SBS_IO_ANALOG_CELL) ? 0U : ((Selection == SBS_IO_XSPI1_CELL) ? 8U : 16U));

    MODIFY_REG(SBS->CCSWVALR, (0xFFU << offset), ((NmosValue << offset) | (PmosValue << (offset + 4U))));
  }

  MODIFY_REG(SBS->CCCSR, (Selection << 1U), (Code << (POSITION_VAL(Selection) + 1U)));
}

/**
  * @brief  Get the code selection for the compensation cell
  * @param  Selection specifies the concerned compensation cell
  *         This parameter can one of the following values:
  *            @arg SBS_IO_ANALOG_CELL Compensation cell for the I/O analog switches
  *            @arg SBS_IO_XSPI1_CELL Compensation cell for the I/O of the XSPI1
  *            @arg SBS_IO_XSPI2_CELL Compensation cell for the I/O of the XSPI2
  * @param  pCode pointer code selection
  *         This parameter can be one of the following values:
  *            @arg SBS_IO_CELL_CODE  Code from the cell (available in the SBS_CCVALR)
  *            @arg SBS_IO_REGISTER_CODE Code from the compensation cell code register (SBS_CCSWVALR)
  * @param  pNmosValue pointer to the Nmos value in range 0 to 15
  * @param  pPmosValue pointer to the Pmos value in range 0 to 15
  * @retval  HAL_OK (all values available) or HAL_ERROR (check parameters)
  */
HAL_StatusTypeDef HAL_SBS_GetCompensationCell(uint32_t Selection, uint32_t *pCode, uint32_t *pNmosValue,
                                              uint32_t *pPmosValue)
{
  uint32_t reg;
  uint32_t offset;
  HAL_StatusTypeDef status = HAL_ERROR;

  /* Check parameters */
  if ((pCode != NULL) && (pNmosValue != NULL) && (pPmosValue != NULL))
  {
    *pCode = ((SBS->CCCSR & (Selection << 1U)) == 0U) ? SBS_IO_CELL_CODE : SBS_IO_REGISTER_CODE;

    reg = (*pCode == SBS_IO_CELL_CODE) ? (SBS->CCVALR) : (SBS->CCSWVALR);
    offset = ((Selection == SBS_IO_ANALOG_CELL) ? 0U : ((Selection == SBS_IO_XSPI1_CELL) ? 8U : 16U));

    *pNmosValue = ((reg >> offset) & 0xFU);
    *pPmosValue = ((reg >> (offset + 4U)) & 0xFU);

    status = HAL_OK;
  }
  return status;
}

/**
  * @brief  Enable the high speed at low voltage
  * @param  Selection specifies the concerned IOs
  *         This parameter can the combination of the following values:
  *            @arg SBS_IO_ANALOG_HSLV High speed at low voltage for the I/O analog switches
  *            @arg SBS_IO_XSPI1_HSLV High speed at low voltage for the I/O of the XSPI1
  *            @arg SBS_IO_XSPI2_HSLV High speed at low voltage for the I/O of the XSPI2
  * @retval None
  */
void HAL_SBS_EnableIOSpeedOptimize(uint32_t Selection)
{
  /* Check the parameter */
  assert_param(IS_SBS_IOHSLV(Selection));

  SET_BIT(SBS->CCCSR, Selection);
}

/**
  * @brief  Disable the high speed at low voltage
  * @param  Selection specifies the concerned IOs
  *         This parameter can the combination of the following values:
  *            @arg SBS_IO_ANALOG_HSLV High speed at low voltage for the I/O analog switches
  *            @arg SBS_IO_XSPI1_HSLV High speed at low voltage for the I/O of the XSPI1
  *            @arg SBS_IO_XSPI2_HSLV High speed at low voltage for the I/O of the XSPI2
  * @retval None
  */
void HAL_SBS_DisableIOSpeedOptimize(uint32_t Selection)
{
  /* Check the parameter */
  assert_param(IS_SBS_IOHSLV(Selection));

  MODIFY_REG(SBS->CCCSR, Selection, 0U);
}

/**
  * @brief  Configure the Timer Break input for error flag(s).
  * @note   When a configuration is set, only a system reset can reset it.
  * @param  Input input configuration
  *              This parameter can be one or a combinartion of the following values:
  *                @arg SBS_TIMER_BREAK_LOCK_PVD      PVD flag
  *                @arg SBS_TIMER_BREAK_LOCK_FLASH    FLASH double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_CORE     M7 LOCKUP (Hardfault) output
  *                @arg SBS_TIMER_BREAK_LOCK_ITCM     ITCM double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_DTCM     DTCM double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_AXISRAM1 AXISRAM1 double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_AXISRAM3 AXISRAM3 double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_BKPRAM   Backup SRAM double ECC error flag
  * @retval None
  */
void HAL_SBS_ConfigTimerBreakInput(uint32_t Input)
{
  /* Check the parameter */
  assert_param(IS_SBS_TIMER_BREAK_INPUT(Input));

  SET_BIT(SBS->BKLOCKR, Input);
}

/**
  * @brief  Get the Timer Break input configuration.
  * @note   When a configuration is set, only a system reset can reset it.
  * @retval Timer break input configuration
  *              This return value can be one or a combinartion of the following values:
  *                @arg SBS_TIMER_BREAK_LOCK_PVD      PVD flag
  *                @arg SBS_TIMER_BREAK_LOCK_FLASH    FLASH double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_CORE     M7 LOCKUP (Hardfault) output
  *                @arg SBS_TIMER_BREAK_LOCK_ITCM     ITCM double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_DTCM     DTCM double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_AXISRAM1 AXISRAM1 double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_AXISRAM3 AXISRAM3 double ECC error flag
  *                @arg SBS_TIMER_BREAK_LOCK_BKPRAM   Backup SRAM double ECC error flag
  */
uint32_t HAL_SBS_GetTimerBreakInputConfig(void)
{
  return (SBS->BKLOCKR & SBS_BKLOCKR_MASK);
}

/**
  * @brief  Configure the source input used for EXTI.
  * @param  Exti EXTI event to be configured
  *              This parameter should be between 0 and 15
  * @param  Port Port whom pin is used
  *              This parameter can be one of the following values:
  *                @arg SBS_EXTI_PIN_PORTA Port A pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTB Port B pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTC Port C pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTD Port D pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTE Port E pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTF Port F pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTG Port G pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTH Port H pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTM Port M pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTN Port N pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTO Port O pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTP Port P pin input of EXTI event detection
  * @retval None
  */
void HAL_SBS_EXTIConfig(uint32_t Exti, uint32_t Port)
{
  uint32_t reg;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_SBS_EXTI_INPUT(Exti));
  assert_param(IS_SBS_EXTI_PIN(Port));

  reg = (Exti / 4U);
  offset = (4U * (Exti % 4U));

  MODIFY_REG(SBS->EXTICR[reg], (0xFU << offset), (Port << offset));
}

/**
  * @brief  Get the source input used for EXTI.
  * @param  Exti EXTI configuration requested
  *              This parameter should be between 0 and 15
  * @retval Return value is port whom pin is used
  *              This return value can be one of the following values:
  *                @arg SBS_EXTI_PIN_PORTA Port A pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTB Port B pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTC Port C pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTD Port D pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTE Port E pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTF Port F pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTG Port G pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTH Port H pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTM Port M pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTN Port N pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTO Port O pin input of EXTI event detection
  *                @arg SBS_EXTI_PIN_PORTP Port P pin input of EXTI event detection
  */
uint32_t HAL_SBS_GetEXTIConfig(uint32_t Exti)
{
  uint32_t reg;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_SBS_EXTI_INPUT(Exti));

  reg = (Exti / 4U);
  offset = (4U * (Exti % 4U));

  return ((SBS->EXTICR[reg] & (0xFUL << offset)) >> offset);
}
/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group5 VREFBUF Control functions
  *  @brief    HAL Control functions
  *
@verbatim
 ===============================================================================
                      ##### HAL Control functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the internal voltage reference buffer voltage scale
      (+) Configure the internal voltage reference buffer high impedance mode
      (+) Tune the Internal Voltage Reference buffer
      (+) Enable the Internal Voltage Reference buffer
      (+) Disable the Internal Voltage Reference buffer

@endverbatim
  * @{
  */

/**
  * @brief Configure the internal voltage reference buffer voltage scale.
  * @param VoltageScaling  specifies the output voltage to achieve
  *          This parameter can be one of the following values:
  *            @arg VREFBUF_VOLTAGE_SCALE0: VREF_OUT1 around 2.5 V.
  *                                                This requires VDDA equal to or higher than 2.8 V.
  *            @arg VREFBUF_VOLTAGE_SCALE1: VREF_OUT2 around 2.048 V.
  *                                                This requires VDDA equal to or higher than 2.4 V.
  *            @arg VREFBUF_VOLTAGE_SCALE2: VREF_OUT3 around 1.8 V.
  *                                                This requires VDDA equal to or higher than 2.1 V.
  *            @arg VREFBUF_VOLTAGE_SCALE3: VREF_OUT4 around 1.5 V.
  *                                                This requires VDDA equal to or higher than 1.8 V.
  * @retval None
  */
void HAL_VREFBUF_VoltageScalingConfig(uint32_t VoltageScaling)
{
  /* Check the parameters */
  assert_param(IS_VREFBUF_VOLTAGE_SCALE(VoltageScaling));

  MODIFY_REG(VREFBUF->CSR, VREFBUF_CSR_VRS, VoltageScaling);
}

/**
  * @brief Configure the internal voltage reference buffer high impedance mode.
  * @param Mode  specifies the high impedance mode
  *          This parameter can be one of the following values:
  *            @arg VREFBUF_HIGH_IMPEDANCE_DISABLE: VREF+ pin is internally connect to VREFINT output.
  *            @arg VREFBUF_HIGH_IMPEDANCE_ENABLE: VREF+ pin is high impedance.
  * @retval None
  */
void HAL_VREFBUF_HighImpedanceConfig(uint32_t Mode)
{
  /* Check the parameters */
  assert_param(IS_VREFBUF_HIGH_IMPEDANCE(Mode));

  MODIFY_REG(VREFBUF->CSR, VREFBUF_CSR_HIZ, Mode);
}

/**
  * @brief  Tune the Internal Voltage Reference buffer (VREFBUF).
  * @retval None
  */
void HAL_VREFBUF_TrimmingConfig(uint32_t TrimmingValue)
{
  /* Check the parameters */
  assert_param(IS_VREFBUF_TRIMMING(TrimmingValue));

  MODIFY_REG(VREFBUF->CCR, VREFBUF_CCR_TRIM, TrimmingValue);
}

/**
  * @brief  Enable the Internal Voltage Reference buffer (VREFBUF).
  * @retval HAL_OK/HAL_TIMEOUT
  */
HAL_StatusTypeDef HAL_VREFBUF_Enable(void)
{
  uint32_t  tickstart;

  SET_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);

  /* Get Start Tick*/
  tickstart = HAL_GetTick();

  /* Wait for VRR bit  */
  while (READ_BIT(VREFBUF->CSR, VREFBUF_CSR_VRR) == 0UL)
  {
    if ((HAL_GetTick() - tickstart) > VREFBUF_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Disable the Internal Voltage Reference buffer (VREFBUF).
  *
  * @retval None
  */
void HAL_VREFBUF_Disable(void)
{
  CLEAR_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);
}
/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group6 HAL AXIM configuration functions
  *  @brief    HAL AXI Interconnect Matrix (AXIM) configuration functions
  *
@verbatim
 ===============================================================================
                      ##### HAL AXIM configuration functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configures ASIB (AMBA slave interface blocks) and AMIB (AMBA master interface blocks) parameters,
          such as the QoS (quality of service) level.
@endverbatim
  * @{
  */

/**
  * @brief Enable packing for ASIB.
  * @note  Normal operation, Enable packing of beats to match the output data width.
  * @param AsibInstance  specifies the ASIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_ASIB_1 : ASIB 1 connected to AHB master
  *            @arg AXIM_ASIB_2 : ASIB 2 connected to SDMMC1 master
  * @retval None
  */
void HAL_AXIM_ASIB_EnablePacking(AXIM_ASIB_TypeDef *AsibInstance)
{
  /* Check the parameters */
  assert_param(IS_AXIM_ASIB_ALL_INSTANCE(AsibInstance));

  /* Apply packing configuration for the selected ASIB */
  WRITE_REG(AsibInstance->FNMOD2, 0U);
}

/**
  * @brief Disable packing for ASIB.
  * @note  Network does not perform any packing of beats to match the output data width.
  * @note  Unaligned transactions are not realigned to the input data word boundary.
  * @param AsibInstance  specifies the ASIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_ASIB_1 : ASIB 1 connected to AHB master
  *            @arg AXIM_ASIB_2 : ASIB 2 connected to SDMMC1 master
  * @retval None
  */
void HAL_AXIM_ASIB_DisablePacking(AXIM_ASIB_TypeDef *AsibInstance)
{
  /* Check the parameters */
  assert_param(IS_AXIM_ASIB_ALL_INSTANCE(AsibInstance));

  /* Apply packing configuration for the selected ASIB */
  WRITE_REG(AsibInstance->FNMOD2, AXIM_ASIB_FNMOD2_BYPASS_MERGE);
}

/**
  * @brief Configure ASIB read/write issuing capability.
  * @param AsibInstance  specifies the ASIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_ASIB_1  : ASIB 1 connected to AHB master
  *            @arg AXIM_ASIB_2  : ASIB 2 connected to SDMMC1 master
  *            @arg AXIM_ASIB_3  : ASIB 3 connected to HPDMA master
  *            @arg AXIM_ASIB_4  : ASIB 4 connected to C-M7 master
  *            @arg AXIM_ASIB_5  : ASIB 5 connected to GPU master
  *            @arg AXIM_ASIB_6  : ASIB 6 connected to GPU master
  *            @arg AXIM_ASIB_7  : ASIB 7 connected to GPU master
  *            @arg AXIM_ASIB_8  : ASIB 8 connected to DCMIPP master
  *            @arg AXIM_ASIB_9  : ASIB 9 connected to GFXMMU master
  *            @arg AXIM_ASIB_10 : ASIB 10 connected to LTDC master
  *            @arg AXIM_ASIB_11 : ASIB 11 connected to DMA2D master
  * @param ReadIssuing  specifies the Read issuing capability to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_ASIB_READ_ISS_NORMAL    : Normal issuing capability, default value.
  *            @arg AXIM_ASIB_READ_ISS_FORCE_TO_1: Force issuing capability to 1.
  * @param WriteIssuing  specifies the write issuing capability to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_ASIB_WRITE_ISS_NORMAL    : Normal issuing capability, default value.
  *            @arg AXIM_ASIB_WRITE_ISS_FORCE_TO_1: Force issuing capability to 1.
  * @retval None
  */
void HAL_AXIM_ASIB_IssuingConfig(AXIM_ASIB_TypeDef *AsibInstance, uint32_t ReadIssuing, uint32_t WriteIssuing)
{
  /* Check the parameters */
  assert_param(IS_AXIM_ASIB_ALL_INSTANCE(AsibInstance));
  assert_param(IS_AXIM_ASIB_READ_ISS(ReadIssuing));
  assert_param(IS_AXIM_ASIB_WRITE_ISS(WriteIssuing));

  /* Apply read/write issuing configuration for the selected ASIB */
  WRITE_REG(AsibInstance->FNMOD, (ReadIssuing | WriteIssuing));
}

/**
  * @brief Configure ASIB read QOS priority.
  * @param AsibInstance  specifies the ASIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_ASIB_1  : ASIB 1 connected to AHB master
  *            @arg AXIM_ASIB_2  : ASIB 2 connected to SDMMC1 master
  *            @arg AXIM_ASIB_3  : ASIB 3 connected to HPDMA master
  *            @arg AXIM_ASIB_4  : ASIB 4 connected to C-M7 master
  *            @arg AXIM_ASIB_5  : ASIB 5 connected to GPU master
  *            @arg AXIM_ASIB_6  : ASIB 6 connected to GPU master
  *            @arg AXIM_ASIB_7  : ASIB 7 connected to GPU master
  *            @arg AXIM_ASIB_8  : ASIB 8 connected to DCMIPP master
  *            @arg AXIM_ASIB_9  : ASIB 9 connected to GFXMMU master
  *            @arg AXIM_ASIB_10 : ASIB 10 connected to LTDC master
  *            @arg AXIM_ASIB_11 : ASIB 11 connected to DMA2D master
  * @param QosPriority  specifies read channel QoS setting
  *          This parameter can be a value between 0 to 15.
  *            With 0 value (default value) for the lowest priority and 15 value for Highest priority.
  * @retval None
  */
void HAL_AXIM_ASIB_ReadQoSConfig(AXIM_ASIB_TypeDef *AsibInstance, uint32_t QosPriority)
{
  /* Check the parameters */
  assert_param(IS_AXIM_ASIB_ALL_INSTANCE(AsibInstance));
  assert_param(IS_AXIM_QOS(QosPriority));

  /* Apply read QOS priority setting for the selected ASIB */
  WRITE_REG(AsibInstance->READQOS, QosPriority);
}

/**
  * @brief Configure ASIB write QOS priority.
  * @param AsibInstance  specifies the ASIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_ASIB_1  : ASIB 1 connected to AHB master
  *            @arg AXIM_ASIB_2  : ASIB 2 connected to SDMMC1 master
  *            @arg AXIM_ASIB_3  : ASIB 3 connected to HPDMA master
  *            @arg AXIM_ASIB_4  : ASIB 4 connected to C-M7 master
  *            @arg AXIM_ASIB_5  : ASIB 5 connected to GPU master
  *            @arg AXIM_ASIB_6  : ASIB 6 connected to GPU master
  *            @arg AXIM_ASIB_7  : ASIB 7 connected to GPU master
  *            @arg AXIM_ASIB_8  : ASIB 8 connected to DCMIPP master
  *            @arg AXIM_ASIB_9  : ASIB 9 connected to GFXMMU master
  *            @arg AXIM_ASIB_10 : ASIB 10 connected to LTDC master
  *            @arg AXIM_ASIB_11 : ASIB 11 connected to DMA2D master
  * @param QosPriority  specifies write channel QoS setting
  *          This parameter can be a value between 0 to 15.
  *          With 0 value (default value) for the lowest priority and 15 value for highest priority.
  *
  * @retval None
  */
void HAL_AXIM_ASIB_WriteQoSConfig(AXIM_ASIB_TypeDef *AsibInstance, uint32_t QosPriority)
{
  /* Check the parameters */
  assert_param(IS_AXIM_ASIB_ALL_INSTANCE(AsibInstance));
  assert_param(IS_AXIM_QOS(QosPriority));

  /* Apply write QOS priority setting for the selected ASIB */
  WRITE_REG(AsibInstance->WRITEQOS, QosPriority);
}

/**
  * @brief Enable Packing for AMIB.
  * @note  Normal operation, Enable packing of beats to match the output data width.
  * @param AmibInstance  specifies the AMIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_2 : AMIB 2 connected to AHB Sram slave
  * @retval None
  */
void HAL_AXIM_AMIB_EnablePacking(AXIM_AMIB_TypeDef *AmibInstance)
{
  /* Check the parameters */
  assert_param(IS_AXIM_AMIB_ALL_INSTANCE(AmibInstance));

  /* Apply packing configuration for the selected AMIB */
  WRITE_REG(AmibInstance->FNMOD2, 0U);
}

/**
  * @brief Disable Packing for AMIB.
  * @note  Network does not perform any packing of beats to match the output data width.
  * @note  Unaligned transactions are not realigned to the input data word boundary.
  * @param AmibInstance  specifies the AMIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_2 : AMIB 2 connected to AHB Sram slave
  * @retval None
  */
void HAL_AXIM_AMIB_DisablePacking(AXIM_AMIB_TypeDef *AmibInstance)
{
  /* Check the parameters */
  assert_param(IS_AXIM_AMIB_ALL_INSTANCE(AmibInstance));

  /* Apply packing configuration for the selected AMIB */
  WRITE_REG(AmibInstance->FNMOD2, AXIM_AMIB_FNMOD2_BYPASS_MERGE);
}

/**
  * @brief Configure AMIB read/write issuing capability.
  * @param AmibInstance  specifies the AMIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_1  : AMIB 1 connected to GFXMMU slave
  *            @arg AXIM_AMIB_2  : AMIB 2 connected to AHB Sram slave
  *            @arg AXIM_AMIB_3  : AMIB 3 connected to FMC slave
  *            @arg AXIM_AMIB_4  : AMIB 4 connected to XSPI1 slave
  *            @arg AXIM_AMIB_5  : AMIB 5 connected to XSPI2 slave
  *            @arg AXIM_AMIB_6  : AMIB 6 connected to AXI SRAM4 slave
  *            @arg AXIM_AMIB_7  : AMIB 7 connected to AXI SRAM3 slave
  *            @arg AXIM_AMIB_8  : AMIB 8 connected to AXI SRAM2 slave
  *            @arg AXIM_AMIB_9  : AMIB 9 connected to AXI SRAM1 slave
  *            @arg AXIM_AMIB_10 : AMIB 10 connected to FLASH slave
  * @param ReadIssuing  specifies the Read issuing capability to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_READ_ISS_NORMAL    : Normal issuing capability, default value.
  *            @arg AXIM_AMIB_READ_ISS_FORCE_TO_1: Force issuing capability to 1.
  * @param WriteIssuing  specifies the write issuing capability to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_WRITE_ISS_NORMAL    : Normal issuing capability, default value.
  *            @arg AXIM_AMIB_WRITE_ISS_FORCE_TO_1: Force issuing capability to 1.
  * @retval None
  */
void HAL_AXIM_AMIB_IssuingConfig(AXIM_AMIB_TypeDef *AmibInstance, uint32_t ReadIssuing, uint32_t WriteIssuing)
{
  /* Check the parameters */
  assert_param(IS_AXIM_AMIB_ALL_INSTANCE(AmibInstance));
  assert_param(IS_AXIM_AMIB_READ_ISS(ReadIssuing));
  assert_param(IS_AXIM_AMIB_WRITE_ISS(WriteIssuing));

  /* Apply read/write issuing configuration for the selected AMIB */
  WRITE_REG(AmibInstance->FNMOD, (ReadIssuing | WriteIssuing));
}

/**
  * @brief Configure AMIB read/write issuing bus matrix capability.
  * @param AmibInstance  specifies the AMIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_1  : AMIB 1 connected to GFXMMU slave
  *            @arg AXIM_AMIB_2  : AMIB 2 connected to AHB Sram slave
  *            @arg AXIM_AMIB_3  : AMIB 3 connected to FMC slave
  *            @arg AXIM_AMIB_4  : AMIB 4 connected to XSPI1 slave
  *            @arg AXIM_AMIB_5  : AMIB 5 connected to XSPI2 slave
  *            @arg AXIM_AMIB_6  : AMIB 6 connected to AXI SRAM4 slave
  *            @arg AXIM_AMIB_7  : AMIB 7 connected to AXI SRAM3 slave
  *            @arg AXIM_AMIB_8  : AMIB 8 connected to AXI SRAM2 slave
  *            @arg AXIM_AMIB_9  : AMIB 9 connected to AXI SRAM1 slave
  *            @arg AXIM_AMIB_10 : AMIB 10 connected to FLASH slave
  * @param ReadIssuing  specifies the Read issuing capability to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_READ_ISS_NORMAL    : Normal issuing capability, default value.
  *            @arg AXIM_AMIB_READ_ISS_FORCE_TO_1: Force issuing capability to 1.
  * @param WriteIssuing  specifies the write issuing capability to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_WRITE_ISS_NORMAL    : Normal issuing capability, default value.
  *            @arg AXIM_AMIB_WRITE_ISS_FORCE_TO_1: Force issuing capability to 1.
  * @retval None
  */
void HAL_AXIM_AMIB_IssuingConfigBusMatrix(AXIM_AMIB_TypeDef *AmibInstance, uint32_t ReadIssuing, uint32_t WriteIssuing)
{
  /* Check the parameters */
  assert_param(IS_AXIM_AMIB_ALL_INSTANCE(AmibInstance));
  assert_param(IS_AXIM_AMIB_READ_ISS_BM(ReadIssuing));
  assert_param(IS_AXIM_AMIB_WRITE_ISS_BM(WriteIssuing));

  /* Apply read/write issuing configuration for the selected AMIB */
  WRITE_REG(AmibInstance->FNMODBMISS, (ReadIssuing | WriteIssuing));
}

/**
  * @brief Enable Long burst for AMIB.
  * @note  Long bursts can be generated at the output of the AMIB.
  * @param AmibInstance  specifies the AMIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_2 : AMIB 2 connected to AHB Sram slave
  * @retval None
  */
void HAL_AXIM_AMIB_EnableLongBurst(AXIM_AMIB_TypeDef *AmibInstance)
{
  /* Check the parameters */
  assert_param(IS_AXIM_AMIB_ALL_INSTANCE(AmibInstance));

  /* Apply Long burst configuration for the selected AMIB */
  WRITE_REG(AmibInstance->FNMODLB, AXIM_AMIB_FNMODLB_LONG_BURST);
}

/**
  * @brief Disable Long burst for AMIB.
  * @note  Long bursts can not be generated at the output of the AMIB.
  * @param AmibInstance  specifies the AMIB to configure
  *          This parameter can be one of the following values:
  *            @arg AXIM_AMIB_2 : AMIB 2 connected to AHB Sram slave
  * @retval None
  */
void HAL_AXIM_AMIB_DisableLongBurst(AXIM_AMIB_TypeDef *AmibInstance)
{
  /* Check the parameters */
  assert_param(IS_AXIM_AMIB_ALL_INSTANCE(AmibInstance));

  /* Apply Long burst configuration for the selected AMIB */
  WRITE_REG(AmibInstance->FNMODLB, 0U);
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
