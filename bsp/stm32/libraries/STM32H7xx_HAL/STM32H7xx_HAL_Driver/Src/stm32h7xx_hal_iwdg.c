/**
  ******************************************************************************
  * @file    stm32h7xx_hal_iwdg.c
  * @author  MCD Application Team
  * @brief   IWDG HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Independent Watchdog (IWDG) peripheral:
  *           + Initialization and Start functions
  *           + IO operation functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                    ##### IWDG Generic features #####
  ==============================================================================
  [..]
    (+) The IWDG can be started by either software or hardware (configurable
        through option byte).

    (+) The IWDG is clocked by the Low-Speed Internal clock (LSI) and thus stays
        active even if the main clock fails.

    (+) Once the IWDG is started, the LSI is forced ON and both cannot be
        disabled. The counter starts counting down from the reset value (0xFFF).
        When it reaches the end of count value (0x000) a reset signal is
        generated (IWDG reset).

    (+) Whenever the key value 0x0000 AAAA is written in the IWDG_KR register,
        the IWDG_RLR value is reloaded into the counter and the watchdog reset
        is prevented.

    (+) The IWDG is implemented in the VDD voltage domain that is still functional
        in STOP and STANDBY mode (IWDG reset can wake up the CPU from STANDBY).
        IWDGRST flag in RCC_CSR register can be used to inform when an IWDG
        reset occurs.

    (+) Debug mode: When the microcontroller enters debug mode (core halted),
        the IWDG counter either continues to work normally or stops, depending
        on DBG_IWDG_STOP configuration bit in DBG module, accessible through
        __HAL_DBGMCU_FREEZE_IWDG1() or __HAL_DBGMCU_FREEZE2_IWDG2() and
        __HAL_DBGMCU_UnFreeze_IWDG1 or __HAL_DBGMCU_UnFreeze2_IWDG2() macros.

    [..] Min-max timeout value @32KHz (LSI): ~125us / ~32.7s
         The IWDG timeout may vary due to LSI clock frequency dispersion.
         STM32H7xx devices provide the capability to measure the LSI clock
         frequency (LSI clock is internally connected to TIM16 CH1 input capture).
         The measured value can be used to have an IWDG timeout with an
         acceptable accuracy.

    [..] Default timeout value (necessary for IWDG_SR status register update):
         Constant LSI_VALUE is defined based on the nominal LSI clock frequency.
         This frequency being subject to variations as mentioned above, the
         default timeout value (defined through constant HAL_IWDG_DEFAULT_TIMEOUT
         below) may become too short or too long.
         In such cases, this default timeout value can be tuned by redefining
         the constant LSI_VALUE at user-application level (based, for instance,
         on the measured LSI clock frequency as explained above).

                     ##### How to use this driver #####
  ==============================================================================
  [..]
    (#) Use IWDG using HAL_IWDG_Init() function to :
      (++) Enable instance by writing Start keyword in IWDG_KEY register. LSI
           clock is forced ON and IWDG counter starts counting down.
      (++) Enable write access to configuration registers:
          IWDG_PR, IWDG_RLR and IWDG_WINR.
      (++) Configure the IWDG prescaler and counter reload value. This reload
           value will be loaded in the IWDG counter each time the watchdog is
           reloaded, then the IWDG will start counting down from this value.
      (++) Depending on window parameter:
        (+++) If Window Init parameter is same as Window register value,
             nothing more is done but reload counter value in order to exit
             function with exact time base.
        (+++) Else modify Window register. This will automatically reload
             watchdog counter.
      (++) Wait for status flags to be reset.

    (#) Then the application program must refresh the IWDG counter at regular
        intervals during normal operation to prevent an MCU reset, using
        HAL_IWDG_Refresh() function.

     *** IWDG HAL driver macros list ***
     ====================================
     [..]
       Below the list of most used macros in IWDG HAL driver:
      (+) __HAL_IWDG_START: Enable the IWDG peripheral
      (+) __HAL_IWDG_RELOAD_COUNTER: Reloads IWDG counter with value defined in
          the reload register

  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

#ifdef HAL_IWDG_MODULE_ENABLED
/** @addtogroup IWDG
  * @brief IWDG HAL module driver.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup IWDG_Private_Defines IWDG Private Defines
  * @{
  */
/* Status register needs up to 5 LSI clock periods divided by the clock
   prescaler to be updated. The number of LSI clock periods is upper-rounded to
   6 for the timeout value calculation.
   The timeout value is calculated using the highest prescaler (256) and
   the LSI_VALUE constant. The value of this constant can be changed by the user
   to take into account possible LSI clock period variations.
   The timeout value is multiplied by 1000 to be converted in milliseconds.
   LSI startup time is also considered here by adding LSI_STARTUP_TIME
   converted in milliseconds. */
#define HAL_IWDG_DEFAULT_TIMEOUT        (((6UL * 256UL * 1000UL) / LSI_VALUE) + ((LSI_STARTUP_TIME / 1000UL) + 1UL))
#define IWDG_KERNEL_UPDATE_FLAGS        (IWDG_SR_WVU | IWDG_SR_RVU | IWDG_SR_PVU)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup IWDG_Exported_Functions
  * @{
  */

/** @addtogroup IWDG_Exported_Functions_Group1
  *  @brief    Initialization and Start functions.
  *
@verbatim
 ===============================================================================
          ##### Initialization and Start functions #####
 ===============================================================================
 [..]  This section provides functions allowing to:
      (+) Initialize the IWDG according to the specified parameters in the
          IWDG_InitTypeDef of associated handle.
      (+) Manage Window option.
      (+) Once initialization is performed in HAL_IWDG_Init function, Watchdog
          is reloaded in order to exit function with correct time base.

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the IWDG according to the specified parameters in the
  *         IWDG_InitTypeDef and start watchdog. Before exiting function,
  *         watchdog is refreshed in order to have correct time base.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Init(IWDG_HandleTypeDef *hiwdg)
{
  uint32_t tickstart;

  /* Check the IWDG handle allocation */
  if (hiwdg == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_IWDG_ALL_INSTANCE(hiwdg->Instance));
  assert_param(IS_IWDG_PRESCALER(hiwdg->Init.Prescaler));
  assert_param(IS_IWDG_RELOAD(hiwdg->Init.Reload));
  assert_param(IS_IWDG_WINDOW(hiwdg->Init.Window));

  /* Enable IWDG. LSI is turned on automatically */
  __HAL_IWDG_START(hiwdg);

  /* Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers by writing
  0x5555 in KR */
  IWDG_ENABLE_WRITE_ACCESS(hiwdg);

  /* Write to IWDG registers the Prescaler & Reload values to work with */
  hiwdg->Instance->PR = hiwdg->Init.Prescaler;
  hiwdg->Instance->RLR = hiwdg->Init.Reload;

  /* Check pending flag, if previous update not done, return timeout */
  tickstart = HAL_GetTick();

  /* Wait for register to be updated */
  while ((hiwdg->Instance->SR & IWDG_KERNEL_UPDATE_FLAGS) != 0x00u)
  {
    if ((HAL_GetTick() - tickstart) > HAL_IWDG_DEFAULT_TIMEOUT)
    {
      if ((hiwdg->Instance->SR & IWDG_KERNEL_UPDATE_FLAGS) != 0x00u)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* If window parameter is different than current value, modify window
  register */
  if (hiwdg->Instance->WINR != hiwdg->Init.Window)
  {
    /* Write to IWDG WINR the IWDG_Window value to compare with. In any case,
    even if window feature is disabled, Watchdog will be reloaded by writing
    windows register */
    hiwdg->Instance->WINR = hiwdg->Init.Window;
  }
  else
  {
    /* Reload IWDG counter with value defined in the reload register */
    __HAL_IWDG_RELOAD_COUNTER(hiwdg);
  }

  /* Return function status */
  return HAL_OK;
}


/**
  * @}
  */


/** @addtogroup IWDG_Exported_Functions_Group2
  *  @brief   IO operation functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..]  This section provides functions allowing to:
      (+) Refresh the IWDG.

@endverbatim
  * @{
  */

/**
  * @brief  Refresh the IWDG.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Refresh(IWDG_HandleTypeDef *hiwdg)
{
  /* Reload IWDG counter with value defined in the reload register */
  __HAL_IWDG_RELOAD_COUNTER(hiwdg);

  /* Return function status */
  return HAL_OK;
}


/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_IWDG_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
