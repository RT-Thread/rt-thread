/** ----------------------------------------------------------------------------
 *         Nationz Technology Software Support  -  NATIONZ  -
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022, Nationz Corporation  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the disclaimer below in the documentation and/or
 * other materials provided with the distribution.
 *
 * Nationz's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONZ "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
 * -----------------------------------------------------------------------------
 */

/** ****************************************************************************
 * @copyright      Nationz Co.,Ltd
 *                 Copyright (c) 2019 All Rights Reserved
 *******************************************************************************
 * @file     n32l43x_lptim.c
 * @author
 * @date
 * @version  v1.2.0
 * @brief
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "n32l43x_lptim.h"
#include "n32l43x_rcc.h"

/** @addtogroup n32l43x_StdPeriph_Driver
  * @{
  */

/** @defgroup LPTIM
  * @brief LPTIM driver modules
  * @{
  */

/** @defgroup LPTIM_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */
//#define LPTIM
//#if defined (LPTIM)//LPTIM

/** @defgroup RCC_EC_LPTIM1 Peripheral LPTIM get clock source
  * @{
  */
#define RCC_LPTIM_CLKSOURCE              ((uint32_t)0x00000007)/*!< LPTIM1 clock source selection bits */
/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup LPTIM_Private_Macros
  * @{
  */
#define IS_LPTIM_CLOCK_SOURCE(__VALUE__) (((__VALUE__) == LPTIM_CLK_SOURCE_INTERNAL) \
                                       || ((__VALUE__) == LPTIM_CLK_SOURCE_EXTERNAL))

#define IS_LPTIM_CLOCK_PRESCALER(__VALUE__) (((__VALUE__) == LPTIM_PRESCALER_DIV1)   \
                                          || ((__VALUE__) == LPTIM_PRESCALER_DIV2)   \
                                          || ((__VALUE__) == LPTIM_PRESCALER_DIV4)   \
                                          || ((__VALUE__) == LPTIM_PRESCALER_DIV8)   \
                                          || ((__VALUE__) == LPTIM_PRESCALER_DIV16)  \
                                          || ((__VALUE__) == LPTIM_PRESCALER_DIV32)  \
                                          || ((__VALUE__) == LPTIM_PRESCALER_DIV64)  \
                                          || ((__VALUE__) == LPTIM_PRESCALER_DIV128))

#define IS_LPTIM_WAVEFORM(__VALUE__) (((__VALUE__) == LPTIM_OUTPUT_WAVEFORM_PWM) \
                                   || ((__VALUE__) == LPTIM_OUTPUT_WAVEFORM_SETONCE))

#define IS_LPTIM_OUTPUT_POLARITY(__VALUE__) (((__VALUE__) == LPTIM_OUTPUT_POLARITY_REGULAR) \
                                          || ((__VALUE__) == LPTIM_OUTPUT_POLARITY_INVERSE))
/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup LPTIM_Private_Functions LPTIM Private Functions
  * @{
  */
/**
  * @}
  */
/* Exported functions --------------------------------------------------------*/
/** @addtogroup LPTIM_Exported_Functions
  * @{
  */

/** @addtogroup LPTIM_EF_Init
  * @{
  */

/**
  * @brief  Set LPTIMx registers to their reset values.
  * @param  LPTIMx LP Timer instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: LPTIMx registers are de-initialized
  *          - ERROR: invalid LPTIMx instance
  */
void LPTIM_DeInit(LPTIM_Module* LPTIMx)
{
  if (LPTIMx == LPTIM)
  {
    RCC_EnableRETPeriphReset(RCC_RET_PERIPH_LPTIM,ENABLE);
    RCC_EnableRETPeriphReset(RCC_RET_PERIPH_LPTIM,DISABLE);
  }
}

/**
  * @brief  Set each fields of the LPTIM_InitStruct structure to its default
  *         value.
  * @param  LPTIM_InitStruct pointer to a @ref LPTIM_InitType structure
  * @retval None
  */
void LPTIM_StructInit(LPTIM_InitType* LPTIM_InitStruct)
{
  /* Set the default configuration */
  LPTIM_InitStruct->ClockSource = LPTIM_CLK_SOURCE_INTERNAL;
  LPTIM_InitStruct->Prescaler   = LPTIM_PRESCALER_DIV1;
  LPTIM_InitStruct->Waveform    = LPTIM_OUTPUT_WAVEFORM_PWM;
  LPTIM_InitStruct->Polarity    = LPTIM_OUTPUT_POLARITY_REGULAR;
}

/**
  * @brief  Configure the LPTIMx peripheral according to the specified parameters.
  * @note LPTIM_Init can only be called when the LPTIM instance is disabled.
  * @note LPTIMx can be disabled using unitary function @ref LPTIM_Disable().
  * @param  LPTIMx LP Timer Instance
  * @param  LPTIM_InitStruct pointer to a @ref LPTIM_InitType structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: LPTIMx instance has been initialized
  *          - ERROR: LPTIMx instance hasn't been initialized
  */
ErrorStatus LPTIM_Init(LPTIM_Module * LPTIMx, LPTIM_InitType* LPTIM_InitStruct)
{
  ErrorStatus result = SUCCESS;
  /* Check the parameters */
  assert_param(IS_LPTIM_CLOCK_SOURCE(LPTIM_InitStruct->ClockSource));
  assert_param(IS_LPTIM_CLOCK_PRESCALER(LPTIM_InitStruct->Prescaler));
  assert_param(IS_LPTIM_WAVEFORM(LPTIM_InitStruct->Waveform));
  assert_param(IS_LPTIM_OUTPUT_POLARITY(LPTIM_InitStruct->Polarity));

  /* The LPTIMx_CFG register must only be modified when the LPTIM is disabled
     (ENABLE bit is reset to 0).
  */
  if (LPTIM_IsEnabled(LPTIMx) == 1UL)
  {
    result = ERROR;
  }
  else
  {
  /* Set CKSEL bitfield according to ClockSource value */
  /* Set PRESC bitfield according to Prescaler value */
  /* Set WAVE bitfield according to Waveform value */
  /* Set WAVEPOL bitfield according to Polarity value */
  MODIFY_REG(LPTIMx->CFG,
             (LPTIM_CFG_CLKSEL | LPTIM_CFG_CLKPOL | LPTIM_CFG_WAVE| LPTIM_CFG_WAVEPOL),
             LPTIM_InitStruct->ClockSource | \
             LPTIM_InitStruct->Prescaler | \
             LPTIM_InitStruct->Waveform | \
             LPTIM_InitStruct->Polarity);
  }

  return result;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @brief  Disable the LPTIM instance
  * @rmtoll CR           ENABLE        LPTIM_Disable
  * @param  LPTIMx Low-Power Timer instance
  * @note
  * @retval None
  */
void LPTIM_Disable(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->CTRL, LPTIM_CTRL_LPTIMEN);
}

/** @defgroup LPTIM_EF_LPTIM_Configuration LPTIM Configuration
  * @{
  */

/**
  * @brief  Enable the LPTIM instance
  * @note After setting the ENABLE bit, a delay of two counter clock is needed
  *       before the LPTIM instance is actually enabled.
  * @rmtoll CR           ENABLE        LPTIM_Enable
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_Enable(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->CTRL, LPTIM_CTRL_LPTIMEN);
}

/**
  * @brief  Indicates whether the LPTIM instance is enabled.
  * @rmtoll CR           ENABLE        LPTIM_IsEnabled
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabled(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->CTRL, LPTIM_CTRL_LPTIMEN) == LPTIM_CTRL_LPTIMEN)? 1UL : 0UL));
}

/**
  * @brief  Starts the LPTIM counter in the desired mode.
  * @note LPTIM instance must be enabled before starting the counter.
  * @note It is possible to change on the fly from One Shot mode to
  *       Continuous mode.
  * @rmtoll CR           CNTSTRT       LPTIM_StartCounter\n
  *         CR           SNGSTRT       LPTIM_StartCounter
  * @param  LPTIMx Low-Power Timer instance
  * @param  OperatingMode This parameter can be one of the following values:
  *         @arg @ref LPTIM_OPERATING_MODE_CONTINUOUS
  *         @arg @ref LPTIM_OPERATING_MODE_ONESHOT
  * @retval None
  */
void LPTIM_StartCounter(LPTIM_Module *LPTIMx, uint32_t OperatingMode)
{
  MODIFY_REG(LPTIMx->CTRL, LPTIM_CTRL_TSTCM | LPTIM_CTRL_SNGMST, OperatingMode);
}

/**
  * @brief  Set the LPTIM registers update mode (enable/disable register preload)
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll CFG         PRELOAD       LPTIM_SetUpdateMode
  * @param  LPTIMx Low-Power Timer instance
  * @param  UpdateMode This parameter can be one of the following values:
  *         @arg @ref LPTIM_UPDATE_MODE_IMMEDIATE
  *         @arg @ref LPTIM_UPDATE_MODE_ENDOFPERIOD
  * @retval None
  */
void LPTIM_SetUpdateMode(LPTIM_Module *LPTIMx, uint32_t UpdateMode)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_RELOAD, UpdateMode);
}

/**
  * @brief  Get the LPTIM registers update mode
  * @rmtoll CFG         PRELOAD       LPTIM_GetUpdateMode
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_UPDATE_MODE_IMMEDIATE
  *         @arg @ref LPTIM_UPDATE_MODE_ENDOFPERIOD
  */
uint32_t LPTIM_GetUpdateMode(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_RELOAD));
}

/**
  * @brief  Set the auto reload value
  * @note The LPTIMx_ARR register content must only be modified when the LPTIM is enabled
  * @note After a write to the LPTIMx_ARR register a new write operation to the
  *       same register can only be performed when the previous write operation
  *       is completed. Any successive write before  the ARROK flag be set, will
  *       lead to unpredictable results.
  * @note autoreload value be strictly greater than the compare value.
  * @rmtoll ARR          ARR           LPTIM_SetAutoReload
  * @param  LPTIMx Low-Power Timer instance
  * @param  AutoReload Value between Min_Data=0x00 and Max_Data=0xFFFF
  * @retval None
  */
void LPTIM_SetAutoReload(LPTIM_Module *LPTIMx, uint32_t AutoReload)
{
  MODIFY_REG(LPTIMx->ARR, LPTIM_ARR_ARRVAL, AutoReload);
}

/**
  * @brief  Get actual auto reload value
  * @rmtoll ARR          ARR           LPTIM_GetAutoReload
  * @param  LPTIMx Low-Power Timer instance
  * @retval AutoReload Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
uint32_t LPTIM_GetAutoReload(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->ARR, LPTIM_ARR_ARRVAL));
}

/**
  * @brief  Set the compare value
  * @note After a write to the LPTIMx_CMP register a new write operation to the
  *       same register can only be performed when the previous write operation
  *       is completed. Any successive write before the CMPOK flag be set, will
  *       lead to unpredictable results.
  * @rmtoll CMP          CMP           LPTIM_SetCompare
  * @param  LPTIMx Low-Power Timer instance
  * @param  CompareValue Value between Min_Data=0x00 and Max_Data=0xFFFF
  * @retval None
  */
void LPTIM_SetCompare(LPTIM_Module *LPTIMx, uint32_t CompareValue)
{
  MODIFY_REG(LPTIMx->COMPx, LPTIM_COMP_CMPVAL, CompareValue);
}

/**
  * @brief  Get actual compare value
  * @rmtoll CMP          CMP           LPTIM_GetCompare
  * @param  LPTIMx Low-Power Timer instance
  * @retval CompareValue Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
uint32_t LPTIM_GetCompare(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->COMPx, LPTIM_COMP_CMPVAL));
}

/**
  * @brief  Get actual counter value
  * @note When the LPTIM instance is running with an asynchronous clock, reading
  *       the LPTIMx_CNT register may return unreliable values. So in this case
  *       it is necessary to perform two consecutive read accesses and verify
  *       that the two returned values are identical.
  * @rmtoll CNT          CNT           LPTIM_GetCounter
  * @param  LPTIMx Low-Power Timer instance
  * @retval Counter value
  */
uint32_t LPTIM_GetCounter(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CNT, LPTIM_CNT_CNTVAL));
}

/**
  * @brief  Set the counter mode (selection of the LPTIM counter clock source).
  * @note The counter mode can be set only when the LPTIM instance is disabled.
  * @rmtoll CFG         COUNTMODE     LPTIM_SetCounterMode
  * @param  LPTIMx Low-Power Timer instance
  * @param  CounterMode This parameter can be one of the following values:
  *         @arg @ref LPTIM_COUNTER_MODE_INTERNAL
  *         @arg @ref LPTIM_COUNTER_MODE_EXTERNAL
  * @retval None
  */
void LPTIM_SetCounterMode(LPTIM_Module *LPTIMx, uint32_t CounterMode)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CNTMEN, CounterMode);
}

/**
  * @brief  Get the counter mode
  * @rmtoll CFG         COUNTMODE     LPTIM_GetCounterMode
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_COUNTER_MODE_INTERNAL
  *         @arg @ref LPTIM_COUNTER_MODE_EXTERNAL
  */
uint32_t LPTIM_GetCounterMode(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CNTMEN));
}

/**
  * @brief  Configure the LPTIM instance output (LPTIMx_OUT)
  * @note This function must be called when the LPTIM instance is disabled.
  * @note Regarding the LPTIM output polarity the change takes effect
  *       immediately, so the output default value will change immediately after
  *       the polarity is re-configured, even before the timer is enabled.
  * @rmtoll CFG         WAVE          LPTIM_ConfigOutput\n
  *         CFG         WAVPOL        LPTIM_ConfigOutput
  * @param  LPTIMx Low-Power Timer instance
  * @param  Waveform This parameter can be one of the following values:
  *         @arg @ref LPTIM_OUTPUT_WAVEFORM_PWM
  *         @arg @ref LPTIM_OUTPUT_WAVEFORM_SETONCE
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref LPTIM_OUTPUT_POLARITY_REGULAR
  *         @arg @ref LPTIM_OUTPUT_POLARITY_INVERSE
  * @retval None
  */
void LPTIM_ConfigOutput(LPTIM_Module *LPTIMx, uint32_t Waveform, uint32_t Polarity)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_WAVE | LPTIM_CFG_WAVEPOL, Waveform | Polarity);
}

/**
  * @brief  Set  waveform shape
  * @rmtoll CFG         WAVE          LPTIM_SetWaveform
  * @param  LPTIMx Low-Power Timer instance
  * @param  Waveform This parameter can be one of the following values:
  *         @arg @ref LPTIM_OUTPUT_WAVEFORM_PWM
  *         @arg @ref LPTIM_OUTPUT_WAVEFORM_SETONCE
  * @retval None
  */
void LPTIM_SetWaveform(LPTIM_Module *LPTIMx, uint32_t Waveform)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_WAVE, Waveform);
}

/**
  * @brief  Get actual waveform shape
  * @rmtoll CFG         WAVE          LPTIM_GetWaveform
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_OUTPUT_WAVEFORM_PWM
  *         @arg @ref LPTIM_OUTPUT_WAVEFORM_SETONCE
  */
uint32_t LPTIM_GetWaveform(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_WAVE));
}

/**
  * @brief  Set  output polarity
  * @rmtoll CFG         WAVPOL        LPTIM_SetPolarity
  * @param  LPTIMx Low-Power Timer instance
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref LPTIM_OUTPUT_POLARITY_REGULAR
  *         @arg @ref LPTIM_OUTPUT_POLARITY_INVERSE
  * @retval None
  */
void LPTIM_SetPolarity(LPTIM_Module *LPTIMx, uint32_t Polarity)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_WAVEPOL, Polarity);
}

/**
  * @brief  Get actual output polarity
  * @rmtoll CFG         WAVPOL        LPTIM_GetPolarity
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_OUTPUT_POLARITY_REGULAR
  *         @arg @ref LPTIM_OUTPUT_POLARITY_INVERSE
  */
uint32_t LPTIM_GetPolarity(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_WAVEPOL));
}

/**
  * @brief  Set actual prescaler division ratio.
  * @note This function must be called when the LPTIM instance is disabled.
  * @note When the LPTIM is configured to be clocked by an internal clock source
  *       and the LPTIM counter is configured to be updated by active edges
  *       detected on the LPTIM external Input1, the internal clock provided to
  *       the LPTIM must be not be prescaled.
  * @rmtoll CFG         PRESC         LPTIM_SetPrescaler
  * @param  LPTIMx Low-Power Timer instance
  * @param  Prescaler This parameter can be one of the following values:
  *         @arg @ref LPTIM_PRESCALER_DIV1
  *         @arg @ref LPTIM_PRESCALER_DIV2
  *         @arg @ref LPTIM_PRESCALER_DIV4
  *         @arg @ref LPTIM_PRESCALER_DIV8
  *         @arg @ref LPTIM_PRESCALER_DIV16
  *         @arg @ref LPTIM_PRESCALER_DIV32
  *         @arg @ref LPTIM_PRESCALER_DIV64
  *         @arg @ref LPTIM_PRESCALER_DIV128
  * @retval None
  */
void LPTIM_SetPrescaler(LPTIM_Module *LPTIMx, uint32_t Prescaler)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CLKPRE, Prescaler);
}

/**
  * @brief  Get actual prescaler division ratio.
  * @rmtoll CFG         PRESC         LPTIM_GetPrescaler
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_PRESCALER_DIV1
  *         @arg @ref LPTIM_PRESCALER_DIV2
  *         @arg @ref LPTIM_PRESCALER_DIV4
  *         @arg @ref LPTIM_PRESCALER_DIV8
  *         @arg @ref LPTIM_PRESCALER_DIV16
  *         @arg @ref LPTIM_PRESCALER_DIV32
  *         @arg @ref LPTIM_PRESCALER_DIV64
  *         @arg @ref LPTIM_PRESCALER_DIV128
  */
uint32_t LPTIM_GetPrescaler(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKPRE));
}

/**
  * @}
  */

/** @defgroup LPTIM_EF_Trigger_Configuration Trigger Configuration
  * @{
  */

/**
  * @brief  Enable the timeout function
  * @note This function must be called when the LPTIM instance is disabled.
  * @note The first trigger event will start the timer, any successive trigger
  *       event will reset the counter and the timer will restart.
  * @note The timeout value corresponds to the compare value; if no trigger
  *       occurs within the expected time frame, the MCU is waked-up by the
  *       compare match event.
  * @rmtoll CFG         TIMOUT        LPTIM_EnableTimeout
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableTimeout(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->CFG, LPTIM_CFG_TIMOUTEN);
}

/**
  * @brief  Disable the timeout function
  * @note This function must be called when the LPTIM instance is disabled.
  * @note A trigger event arriving when the timer is already started will be
  *       ignored.
  * @rmtoll CFG         TIMOUT        LPTIM_DisableTimeout
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_DisableTimeout(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->CFG, LPTIM_CFG_TIMOUTEN);
}

/**
  * @brief  Indicate whether the timeout function is enabled.
  * @rmtoll CFG         TIMOUT        LPTIM_IsEnabledTimeout
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabledTimeout(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->CFG, LPTIM_CFG_TIMOUTEN) == LPTIM_CFG_TIMOUTEN)? 1UL : 0UL));
}

/**
  * @brief  Start the LPTIM counter
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll CFG         TRIGEN        LPTIM_TrigSw
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_TrigSw(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->CFG, LPTIM_CFG_TRGEN);
}

/**
  * @brief  Configure the external trigger used as a trigger event for the LPTIM.
  * @note This function must be called when the LPTIM instance is disabled.
  * @note An internal clock source must be present when a digital filter is
  *       required for the trigger.
  * @rmtoll CFG         TRIGSEL       LPTIM_ConfigTrigger\n
  *         CFG         TRGFLT        LPTIM_ConfigTrigger\n
  *         CFG         TRIGEN        LPTIM_ConfigTrigger
  * @param  LPTIMx Low-Power Timer instance
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref LPTIM_TRIG_SOURCE_GPIO
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCALARMA
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCALARMB
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCTAMP1 (*)
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCTAMP2
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCTAMP3 (*)
  *         @arg @ref LPTIM_TRIG_SOURCE_COMP1
  *         @arg @ref LPTIM_TRIG_SOURCE_COMP2
  *
  *         (*)  Value not defined in all devices. \n
  *
  * @param  Filter This parameter can be one of the following values:
  *         @arg @ref LPTIM_TRIG_FILTER_NONE
  *         @arg @ref LPTIM_TRIG_FILTER_2
  *         @arg @ref LPTIM_TRIG_FILTER_4
  *         @arg @ref LPTIM_TRIG_FILTER_8
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref LPTIM_TRIG_POLARITY_RISING
  *         @arg @ref LPTIM_TRIG_POLARITY_FALLING
  *         @arg @ref LPTIM_TRIG_POLARITY_RISING_FALLING
  * @retval None
  */
void LPTIM_ConfigTrigger(LPTIM_Module *LPTIMx, uint32_t Source, uint32_t Filter, uint32_t Polarity)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_TRGSEL | LPTIM_CFG_TRIGFLT | LPTIM_CFG_TRGEN, Source | Filter | Polarity);
}

/**
  * @brief  Get actual external trigger source.
  * @rmtoll CFG         TRIGSEL       LPTIM_GetTriggerSource
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_TRIG_SOURCE_GPIO
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCALARMA
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCALARMB
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCTAMP1 (*)
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCTAMP2
  *         @arg @ref LPTIM_TRIG_SOURCE_RTCTAMP3 (*)
  *         @arg @ref LPTIM_TRIG_SOURCE_COMP1
  *         @arg @ref LPTIM_TRIG_SOURCE_COMP2
  *
  *         (*)  Value not defined in all devices. \n
  *
  */
uint32_t LPTIM_GetTriggerSource(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_TRGSEL));
}

/**
  * @brief  Get actual external trigger filter.
  * @rmtoll CFG         TRGFLT        LPTIM_GetTriggerFilter
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_TRIG_FILTER_NONE
  *         @arg @ref LPTIM_TRIG_FILTER_2
  *         @arg @ref LPTIM_TRIG_FILTER_4
  *         @arg @ref LPTIM_TRIG_FILTER_8
  */
uint32_t LPTIM_GetTriggerFilter(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_TRIGFLT));
}

/**
  * @brief  Get actual external trigger polarity.
  * @rmtoll CFG         TRIGEN        LPTIM_GetTriggerPolarity
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_TRIG_POLARITY_RISING
  *         @arg @ref LPTIM_TRIG_POLARITY_FALLING
  *         @arg @ref LPTIM_TRIG_POLARITY_RISING_FALLING
  */
uint32_t LPTIM_GetTriggerPolarity(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_TRGEN));
}

/**
  * @}
  */

/** @defgroup LPTIM_EF_Clock_Configuration Clock Configuration
  * @{
  */

/**
  * @brief  Set the source of the clock used by the LPTIM instance.
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll CFG         CKSEL         LPTIM_SetClockSource
  * @param  LPTIMx Low-Power Timer instance
  * @param  ClockSource This parameter can be one of the following values:
  *         @arg @ref LPTIM_CLK_SOURCE_INTERNAL
  *         @arg @ref LPTIM_CLK_SOURCE_EXTERNAL
  * @retval None
  */
void LPTIM_SetClockSource(LPTIM_Module *LPTIMx, uint32_t ClockSource)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CLKSEL, ClockSource);
}

/**
  * @brief  Get actual LPTIM instance clock source.
  * @rmtoll CFG         CKSEL         LPTIM_GetClockSource
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_CLK_SOURCE_INTERNAL
  *         @arg @ref LPTIM_CLK_SOURCE_EXTERNAL
  */
uint32_t LPTIM_GetClockSource(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKSEL));
}

/**
  * @brief  Configure the active edge or edges used by the counter when the LPTIM is clocked by an external clock source.
  * @note This function must be called when the LPTIM instance is disabled.
  * @note When both external clock signal edges are considered active ones,
  *       the LPTIM must also be clocked by an internal clock source with a
  *       frequency equal to at least four times the external clock frequency.
  * @note An internal clock source must be present when a digital filter is
  *       required for external clock.
  * @rmtoll CFG         CKFLT         LPTIM_ConfigClock\n
  *         CFG         CKPOL         LPTIM_ConfigClock
  * @param  LPTIMx Low-Power Timer instance
  * @param  ClockFilter This parameter can be one of the following values:
  *         @arg @ref LPTIM_CLK_FILTER_NONE
  *         @arg @ref LPTIM_CLK_FILTER_2
  *         @arg @ref LPTIM_CLK_FILTER_4
  *         @arg @ref LPTIM_CLK_FILTER_8
  * @param  ClockPolarity This parameter can be one of the following values:
  *         @arg @ref LPTIM_CLK_POLARITY_RISING
  *         @arg @ref LPTIM_CLK_POLARITY_FALLING
  *         @arg @ref LPTIM_CLK_POLARITY_RISING_FALLING
  * @retval None
  */
void LPTIM_ConfigClock(LPTIM_Module *LPTIMx, uint32_t ClockFilter, uint32_t ClockPolarity)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CLKFLT | LPTIM_CFG_CLKPOL, ClockFilter | ClockPolarity);
}

/**
  * @brief  Get actual clock polarity
  * @rmtoll CFG         CKPOL         LPTIM_GetClockPolarity
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_CLK_POLARITY_RISING
  *         @arg @ref LPTIM_CLK_POLARITY_FALLING
  *         @arg @ref LPTIM_CLK_POLARITY_RISING_FALLING
  */
uint32_t LPTIM_GetClockPolarity(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKPOL));
}

/**
  * @brief  Get actual clock digital filter
  * @rmtoll CFG         CKFLT         LPTIM_GetClockFilter
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_CLK_FILTER_NONE
  *         @arg @ref LPTIM_CLK_FILTER_2
  *         @arg @ref LPTIM_CLK_FILTER_4
  *         @arg @ref LPTIM_CLK_FILTER_8
  */
uint32_t LPTIM_GetClockFilter(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKFLT));
}

/**
  * @}
  */

/** @defgroup LPTIM_EF_Encoder_Mode Encoder Mode
  * @{
  */

/**
  * @brief  Configure the encoder mode.
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll CFG         CKPOL         LPTIM_SetEncoderMode
  * @param  LPTIMx Low-Power Timer instance
  * @param  EncoderMode This parameter can be one of the following values:
  *         @arg @ref LPTIM_ENCODER_MODE_RISING
  *         @arg @ref LPTIM_ENCODER_MODE_FALLING
  *         @arg @ref LPTIM_ENCODER_MODE_RISING_FALLING
  * @retval None
  */
void LPTIM_SetEncoderMode(LPTIM_Module *LPTIMx, uint32_t EncoderMode)
{
  MODIFY_REG(LPTIMx->CFG, LPTIM_CFG_CLKPOL, EncoderMode);
}

/**
  * @brief  Get actual encoder mode.
  * @rmtoll CFG         CKPOL         LPTIM_GetEncoderMode
  * @param  LPTIMx Low-Power Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LPTIM_ENCODER_MODE_RISING
  *         @arg @ref LPTIM_ENCODER_MODE_FALLING
  *         @arg @ref LPTIM_ENCODER_MODE_RISING_FALLING
  */
uint32_t LPTIM_GetEncoderMode(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(READ_BIT(LPTIMx->CFG, LPTIM_CFG_CLKPOL));
}

/**
  * @brief  Enable the encoder mode
  * @note This function must be called when the LPTIM instance is disabled.
  * @note In this mode the LPTIM instance must be clocked by an internal clock
  *       source. Also, the prescaler division ratio must be equal to 1.
  * @note LPTIM instance must be configured in continuous mode prior enabling
  *       the encoder mode.
  * @rmtoll CFG         ENC           LPTIM_EnableEncoderMode
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableEncoderMode(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->CFG, LPTIM_CFG_ENC);
}
/**
  * @brief  Enable the encoder mode
  * @note This function must be called when the LPTIM instance is disabled.
  * @note In this mode the LPTIM instance must be clocked by an internal clock
  *       source. Also, the prescaler division ratio must be equal to 1.
  * @note LPTIM instance must be configured in continuous mode prior enabling
  *       the encoder mode.
  * @rmtoll CFG         ENC           LPTIM_EnableEncoderMode
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableNoEncoderMode(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->CFG, LPTIM_CFG_NENC);
}
/**
  * @brief  Disable the encoder mode
  * @note This function must be called when the LPTIM instance is disabled.
  * @rmtoll CFG         ENC           LPTIM_DisableEncoderMode
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_DisableEncoderMode(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->CFG, LPTIM_CFG_ENC);
}

/**
  * @brief  Indicates whether the LPTIM operates in encoder mode.
  * @rmtoll CFG         ENC           LPTIM_IsEnabledEncoderMode
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabledEncoderMode(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->CFG, LPTIM_CFG_ENC) == LPTIM_CFG_ENC)? 1UL : 0UL));
}

/**
  * @}
  */

/** @defgroup LPTIM_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Clear the compare match flag (CMPMCF)
  * @rmtoll ICR          CMPMCF        LPTIM_ClearFLAG_CMPM
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_ClearFLAG_CMPM(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTCLR, LPTIM_INTCLR_CMPMCF);
}

/**
  * @brief  Inform application whether a compare match interrupt has occurred.
  * @rmtoll ISR          CMPM          LPTIM_IsActiveFlag_CMPM
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsActiveFlag_CMPM(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTSTS,LPTIM_INTSTS_CMPM) ==LPTIM_INTSTS_CMPM)? 1UL : 0UL));
}

/**
  * @brief  Clear the autoreload match flag (ARRMCF)
  * @rmtoll ICR          ARRMCF        LPTIM_ClearFLAG_ARRM
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_ClearFLAG_ARRM(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTCLR, LPTIM_INTCLR_ARRMCF);
}

/**
  * @brief  Inform application whether a autoreload match interrupt has occured.
  * @rmtoll ISR          ARRM          LPTIM_IsActiveFlag_ARRM
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsActiveFlag_ARRM(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTSTS,LPTIM_INTSTS_ARRM) ==LPTIM_INTSTS_ARRM)? 1UL : 0UL));
}

/**
  * @brief  Clear the external trigger valid edge flag(EXTTRIGCF).
  * @rmtoll ICR          EXTTRIGCF     LPTIM_ClearFlag_EXTTRIG
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_ClearFlag_EXTTRIG(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTCLR, LPTIM_INTCLR_EXTRIGCF);
}

/**
  * @brief  Inform application whether a valid edge on the selected external trigger input has occurred.
  * @rmtoll ISR          EXTTRIG       LPTIM_IsActiveFlag_EXTTRIG
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsActiveFlag_EXTTRIG(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTSTS,LPTIM_INTSTS_EXTRIG) ==LPTIM_INTSTS_EXTRIG)? 1UL : 0UL));
}

/**
  * @brief  Clear the compare register update interrupt flag (CMPOKCF).
  * @rmtoll ICR          CMPOKCF       LPTIM_ClearFlag_CMPOK
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_ClearFlag_CMPOK(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTCLR, LPTIM_INTCLR_CMPUPDCF);
}

/**
  * @brief  Informs application whether the APB bus write operation to the LPTIMx_CMP register has been successfully completed. If so, a new one can be initiated.
  * @rmtoll ISR          CMPOK         LPTIM_IsActiveFlag_CMPOK
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsActiveFlag_CMPOK(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTSTS,LPTIM_INTSTS_CMPUPD) ==LPTIM_INTSTS_CMPUPD)? 1UL : 0UL));
}

/**
  * @brief  Clear the autoreload register update interrupt flag (ARROKCF).
  * @rmtoll ICR          ARROKCF       LPTIM_ClearFlag_ARROK
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_ClearFlag_ARROK(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTCLR, LPTIM_INTCLR_ARRUPDCF);
}

/**
  * @brief  Informs application whether the APB bus write operation to the LPTIMx_ARR register has been successfully completed. If so, a new one can be initiated.
  * @rmtoll ISR          ARROK         LPTIM_IsActiveFlag_ARROK
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsActiveFlag_ARROK(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTSTS,LPTIM_INTSTS_ARRUPD) ==LPTIM_INTSTS_ARRUPD)? 1UL : 0UL));
}

/**
  * @brief  Clear the counter direction change to up interrupt flag (UPCF).
  * @rmtoll ICR          UPCF          LPTIM_ClearFlag_UP
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_ClearFlag_UP(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTCLR, LPTIM_INTCLR_UPCF);
}

/**
  * @brief  Informs the application whether the counter direction has changed from down to up (when the LPTIM instance operates in encoder mode).
  * @rmtoll ISR          UP            LPTIM_IsActiveFlag_UP
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsActiveFlag_UP(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTSTS, LPTIM_INTSTS_UP) == LPTIM_INTSTS_UP)? 1UL : 0UL));
}

/**
  * @brief  Clear the counter direction change to down interrupt flag (DOWNCF).
  * @rmtoll ICR          DOWNCF        LPTIM_ClearFlag_DOWN
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_ClearFlag_DOWN(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTCLR, LPTIM_INTCLR_DOWNCF);
}

/**
  * @brief  Informs the application whether the counter direction has changed from up to down (when the LPTIM instance operates in encoder mode).
  * @rmtoll ISR          DOWN          LPTIM_IsActiveFlag_DOWN
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsActiveFlag_DOWN(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTSTS,LPTIM_INTSTS_DOWN) ==LPTIM_INTSTS_DOWN)? 1UL : 0UL));
}

/**
  * @}
  */

/** @defgroup LPTIM_EF_IT_Management Interrupt Management
  * @{
  */

/**
  * @brief  Enable compare match interrupt (CMPMIE).
  * @rmtoll IER          CMPMIE        LPTIM_EnableIT_CMPM
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableIT_CMPM(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTEN, LPTIM_INTEN_CMPMIE);
}

/**
  * @brief  Disable compare match interrupt (CMPMIE).
  * @rmtoll IER          CMPMIE        LPTIM_DisableIT_CMPM
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_DisableIT_CMPM(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->INTEN, LPTIM_INTEN_CMPMIE);
}

/**
  * @brief  Indicates whether the compare match interrupt (CMPMIE) is enabled.
  * @rmtoll IER          CMPMIE        LPTIM_IsEnabledIT_CMPM
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabledIT_CMPM(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTEN, LPTIM_INTEN_CMPMIE) == LPTIM_INTEN_CMPMIE)? 1UL : 0UL));
}

/**
  * @brief  Enable autoreload match interrupt (ARRMIE).
  * @rmtoll IER          ARRMIE        LPTIM_EnableIT_ARRM
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableIT_ARRM(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTEN, LPTIM_INTEN_ARRMIE);
}

/**
  * @brief  Disable autoreload match interrupt (ARRMIE).
  * @rmtoll IER          ARRMIE        LPTIM_DisableIT_ARRM
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_DisableIT_ARRM(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->INTEN, LPTIM_INTEN_ARRMIE);
}

/**
  * @brief  Indicates whether the autoreload match interrupt (ARRMIE) is enabled.
  * @rmtoll IER          ARRMIE        LPTIM_IsEnabledIT_ARRM
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabledIT_ARRM(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTEN, LPTIM_INTEN_ARRMIE) == LPTIM_INTEN_ARRMIE)? 1UL : 0UL));
}

/**
  * @brief  Enable external trigger valid edge interrupt (EXTTRIGIE).
  * @rmtoll IER          EXTTRIGIE     LPTIM_EnableIT_EXTTRIG
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableIT_EXTTRIG(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTEN, LPTIM_INTEN_EXTRIGIE);
}

/**
  * @brief  Disable external trigger valid edge interrupt (EXTTRIGIE).
  * @rmtoll IER          EXTTRIGIE     LPTIM_DisableIT_EXTTRIG
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_DisableIT_EXTTRIG(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->INTEN, LPTIM_INTEN_EXTRIGIE);
}

/**
  * @brief  Indicates external trigger valid edge interrupt (EXTTRIGIE) is enabled.
  * @rmtoll IER          EXTTRIGIE     LPTIM_IsEnabledIT_EXTTRIG
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabledIT_EXTTRIG(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTEN, LPTIM_INTEN_EXTRIGIE) == LPTIM_INTEN_EXTRIGIE)? 1UL : 0UL));
}

/**
  * @brief  Enable compare register write completed interrupt (CMPOKIE).
  * @rmtoll IER          CMPOKIE       LPTIM_EnableIT_CMPOK
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableIT_CMPOK(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTEN, LPTIM_INTEN_CMPUPDIE);
}

/**
  * @brief  Disable compare register write completed interrupt (CMPOKIE).
  * @rmtoll IER          CMPOKIE       LPTIM_DisableIT_CMPOK
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_DisableIT_CMPOK(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->INTEN, LPTIM_INTEN_CMPUPDIE);
}

/**
  * @brief  Indicates whether the compare register write completed interrupt (CMPOKIE) is enabled.
  * @rmtoll IER          CMPOKIE       LPTIM_IsEnabledIT_CMPOK
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabledIT_CMPOK(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTEN, LPTIM_INTEN_CMPUPDIE) == LPTIM_INTEN_CMPUPDIE)? 1UL : 0UL));
}

/**
  * @brief  Enable autoreload register write completed interrupt (ARROKIE).
  * @rmtoll IER          ARROKIE       LPTIM_EnableIT_ARROK
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableIT_ARROK(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTEN, LPTIM_INTEN_ARRUPDIE);
}

/**
  * @brief  Disable autoreload register write completed interrupt (ARROKIE).
  * @rmtoll IER          ARROKIE       LPTIM_DisableIT_ARROK
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_DisableIT_ARROK(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->INTEN, LPTIM_INTEN_ARRUPDIE);
}

/**
  * @brief  Indicates whether the autoreload register write completed interrupt (ARROKIE) is enabled.
  * @rmtoll IER          ARROKIE       LPTIM_IsEnabledIT_ARROK
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabledIT_ARROK(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTEN, LPTIM_INTEN_ARRUPDIE) == LPTIM_INTEN_ARRUPDIE)? 1UL : 0UL));
}

/**
  * @brief  Enable direction change to up interrupt (UPIE).
  * @rmtoll IER          UPIE          LPTIM_EnableIT_UP
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableIT_UP(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTEN, LPTIM_INTEN_UPIE);
}

/**
  * @brief  Disable direction change to up interrupt (UPIE).
  * @rmtoll IER          UPIE          LPTIM_DisableIT_UP
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_DisableIT_UP(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->INTEN, LPTIM_INTEN_UPIE);
}

/**
  * @brief  Indicates whether the direction change to up interrupt (UPIE) is enabled.
  * @rmtoll IER          UPIE          LPTIM_IsEnabledIT_UP
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabledIT_UP(LPTIM_Module *LPTIMx)
{
  return (((READ_BIT(LPTIMx->INTEN, LPTIM_INTEN_UPIE) == LPTIM_INTEN_UPIE)? 1UL : 0UL));
}

/**
  * @brief  Enable direction change to down interrupt (DOWNIE).
  * @rmtoll IER          DOWNIE        LPTIM_EnableIT_DOWN
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_EnableIT_DOWN(LPTIM_Module *LPTIMx)
{
  SET_BIT(LPTIMx->INTEN, LPTIM_INTEN_DOWNIE);
}

/**
  * @brief  Disable direction change to down interrupt (DOWNIE).
  * @rmtoll IER          DOWNIE        LPTIM_DisableIT_DOWN
  * @param  LPTIMx Low-Power Timer instance
  * @retval None
  */
void LPTIM_DisableIT_DOWN(LPTIM_Module *LPTIMx)
{
  CLEAR_BIT(LPTIMx->INTEN, LPTIM_INTEN_DOWNIE);
}

/**
  * @brief  Indicates whether the direction change to down interrupt (DOWNIE) is enabled.
  * @rmtoll IER          DOWNIE        LPTIM_IsEnabledIT_DOWN
  * @param  LPTIMx Low-Power Timer instance
  * @retval State of bit (1 or 0).
  */
uint32_t LPTIM_IsEnabledIT_DOWN(LPTIM_Module *LPTIMx)
{
  return ((READ_BIT(LPTIMx->INTEN, LPTIM_INTEN_DOWNIE) == LPTIM_INTEN_DOWNIE)? 1UL : 0UL);
}

/**
  * @}
  */


//#endif /* LPTIM */

/**
  * @}
  */

/**
  * @}
  */


/******************* (C) COPYRIGHT 2019 NATIONZ *****END OF FILE****/

