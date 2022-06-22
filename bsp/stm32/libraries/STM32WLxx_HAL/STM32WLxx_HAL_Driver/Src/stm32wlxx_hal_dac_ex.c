/**
  ******************************************************************************
  * @file    stm32wlxx_hal_dac_ex.c
  * @author  MCD Application Team
  * @brief   DAC HAL module driver.
  *          This file provides firmware functions to manage the extended
  *          functionalities of the DAC peripheral.
  *
  *
  @verbatim
  ==============================================================================
                      ##### How to use this driver #####
  ==============================================================================
    [..]
     *** Dual mode IO operation ***
     ==============================
      (+) When Dual mode is enabled (i.e. DAC Channel1 and Channel2 are used simultaneously) :
          Use HAL_DACEx_DualGetValue() to get digital data to be converted and use
          HAL_DACEx_DualSetValue() to set digital value to converted simultaneously in
          Channel 1 and Channel 2.

     *** Signal generation operation ***
     ===================================
      (+) Use HAL_DACEx_TriangleWaveGenerate() to generate Triangle signal.
      (+) Use HAL_DACEx_NoiseWaveGenerate() to generate Noise signal.

      (+) HAL_DACEx_SelfCalibrate to calibrate one DAC channel.
      (+) HAL_DACEx_SetUserTrimming to set user trimming value.
      (+) HAL_DACEx_GetTrimOffset to retrieve trimming value (factory setting
          after reset, user setting if HAL_DACEx_SetUserTrimming have been used
          at least one time after reset).

 @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"

/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

#ifdef HAL_DAC_MODULE_ENABLED

#if defined(DAC)

/** @defgroup DACEx DACEx
  * @brief DAC Extended HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup DACEx_Exported_Functions DACEx Exported Functions
  * @{
  */

/** @defgroup DACEx_Exported_Functions_Group2 IO operation functions
  *  @brief    Extended IO operation functions
  *
@verbatim
  ==============================================================================
                 ##### Extended features functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Start conversion.
      (+) Stop conversion.
      (+) Start conversion and enable DMA transfer.
      (+) Stop conversion and disable DMA transfer.
      (+) Get result of conversion.
      (+) Get result of dual mode conversion.

@endverbatim
  * @{
  */

/**
  * @brief  Enable or disable the selected DAC channel wave generation.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  * @param  Amplitude Select max triangle amplitude.
  *          This parameter can be one of the following values:
  *            @arg DAC_TRIANGLEAMPLITUDE_1: Select max triangle amplitude of 1
  *            @arg DAC_TRIANGLEAMPLITUDE_3: Select max triangle amplitude of 3
  *            @arg DAC_TRIANGLEAMPLITUDE_7: Select max triangle amplitude of 7
  *            @arg DAC_TRIANGLEAMPLITUDE_15: Select max triangle amplitude of 15
  *            @arg DAC_TRIANGLEAMPLITUDE_31: Select max triangle amplitude of 31
  *            @arg DAC_TRIANGLEAMPLITUDE_63: Select max triangle amplitude of 63
  *            @arg DAC_TRIANGLEAMPLITUDE_127: Select max triangle amplitude of 127
  *            @arg DAC_TRIANGLEAMPLITUDE_255: Select max triangle amplitude of 255
  *            @arg DAC_TRIANGLEAMPLITUDE_511: Select max triangle amplitude of 511
  *            @arg DAC_TRIANGLEAMPLITUDE_1023: Select max triangle amplitude of 1023
  *            @arg DAC_TRIANGLEAMPLITUDE_2047: Select max triangle amplitude of 2047
  *            @arg DAC_TRIANGLEAMPLITUDE_4095: Select max triangle amplitude of 4095
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DACEx_TriangleWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(Channel));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));

  /* Process locked */
  __HAL_LOCK(hdac);

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;

  /* Enable the triangle wave generation for the selected DAC channel */
  MODIFY_REG(hdac->Instance->CR, ((DAC_CR_WAVE1) | (DAC_CR_MAMP1)) << (Channel & 0x10UL), (DAC_CR_WAVE1_1 | Amplitude) << (Channel & 0x10UL));

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hdac);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Enable or disable the selected DAC channel wave generation.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  * @param  Amplitude Unmask DAC channel LFSR for noise wave generation.
  *          This parameter can be one of the following values:
  *            @arg DAC_LFSRUNMASK_BIT0: Unmask DAC channel LFSR bit0 for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS1_0: Unmask DAC channel LFSR bit[1:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS2_0: Unmask DAC channel LFSR bit[2:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS3_0: Unmask DAC channel LFSR bit[3:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS4_0: Unmask DAC channel LFSR bit[4:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS5_0: Unmask DAC channel LFSR bit[5:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS6_0: Unmask DAC channel LFSR bit[6:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS7_0: Unmask DAC channel LFSR bit[7:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS8_0: Unmask DAC channel LFSR bit[8:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS9_0: Unmask DAC channel LFSR bit[9:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS10_0: Unmask DAC channel LFSR bit[10:0] for noise wave generation
  *            @arg DAC_LFSRUNMASK_BITS11_0: Unmask DAC channel LFSR bit[11:0] for noise wave generation
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_DACEx_NoiseWaveGenerate(DAC_HandleTypeDef *hdac, uint32_t Channel, uint32_t Amplitude)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(Channel));
  assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(Amplitude));

  /* Process locked */
  __HAL_LOCK(hdac);

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_BUSY;

  /* Enable the noise wave generation for the selected DAC channel */
  MODIFY_REG(hdac->Instance->CR, ((DAC_CR_WAVE1) | (DAC_CR_MAMP1)) << (Channel & 0x10UL), (DAC_CR_WAVE1_0 | Amplitude) << (Channel & 0x10UL));

  /* Change DAC state */
  hdac->State = HAL_DAC_STATE_READY;

  /* Process unlocked */
  __HAL_UNLOCK(hdac);

  /* Return function status */
  return HAL_OK;
}


/**
  * @brief  Run the self calibration of one DAC channel.
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  sConfig DAC channel configuration structure.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  * @retval Updates DAC_TrimmingValue. , DAC_UserTrimming set to DAC_UserTrimming
  * @retval HAL status
  * @note   Calibration runs about 7 ms.
  */

HAL_StatusTypeDef HAL_DACEx_SelfCalibrate(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  __IO uint32_t tmp;
  uint32_t trimmingvalue;
  uint32_t delta;

  /* store/restore channel configuration structure purpose */
  uint32_t oldmodeconfiguration;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(Channel));

  /* Check the DAC handle allocation */
  /* Check if DAC running */
  if (hdac == NULL)
  {
    status = HAL_ERROR;
  }
  else if (hdac->State == HAL_DAC_STATE_BUSY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Process locked */
    __HAL_LOCK(hdac);

    /* Store configuration */
    oldmodeconfiguration = (hdac->Instance->MCR & (DAC_MCR_MODE1 << (Channel & 0x10UL)));

    /* Disable the selected DAC channel */
    CLEAR_BIT((hdac->Instance->CR), (DAC_CR_EN1 << (Channel & 0x10UL)));

    /* Set mode in MCR  for calibration */
    MODIFY_REG(hdac->Instance->MCR, (DAC_MCR_MODE1 << (Channel & 0x10UL)), 0U);

    /* Set DAC Channel1 DHR register to the middle value */
    tmp = (uint32_t)hdac->Instance;

    if (Channel == DAC_CHANNEL_1)
    {
      tmp += DAC_DHR12R1_ALIGNMENT(DAC_ALIGN_12B_R);
    }

    *(__IO uint32_t *) tmp = 0x0800UL;

    /* Enable the selected DAC channel calibration */
    /* i.e. set DAC_CR_CENx bit */
    SET_BIT((hdac->Instance->CR), (DAC_CR_CEN1 << (Channel & 0x10UL)));

    /* Init trimming counter */
    /* Medium value */
    trimmingvalue = 16UL;
    delta = 8UL;
    while (delta != 0UL)
    {
      /* Set candidate trimming */
      MODIFY_REG(hdac->Instance->CCR, (DAC_CCR_OTRIM1 << (Channel & 0x10UL)), (trimmingvalue << (Channel & 0x10UL)));

      /* tOFFTRIMmax delay x ms as per datasheet (electrical characteristics */
      /* i.e. minimum time needed between two calibration steps */
      HAL_Delay(1);

      if ((hdac->Instance->SR & (DAC_SR_CAL_FLAG1 << (Channel & 0x10UL))) == (DAC_SR_CAL_FLAG1 << (Channel & 0x10UL)))
      {
        /* DAC_SR_CAL_FLAGx is HIGH try higher trimming */
        trimmingvalue -= delta;
      }
      else
      {
        /* DAC_SR_CAL_FLAGx is LOW try lower trimming */
        trimmingvalue += delta;
      }
      delta >>= 1UL;
    }

    /* Still need to check if right calibration is current value or one step below */
    /* Indeed the first value that causes the DAC_SR_CAL_FLAGx bit to change from 0 to 1  */
    /* Set candidate trimming */
    MODIFY_REG(hdac->Instance->CCR, (DAC_CCR_OTRIM1 << (Channel & 0x10UL)), (trimmingvalue << (Channel & 0x10UL)));

    /* tOFFTRIMmax delay x ms as per datasheet (electrical characteristics */
    /* i.e. minimum time needed between two calibration steps */
    HAL_Delay(1U);

    if ((hdac->Instance->SR & (DAC_SR_CAL_FLAG1 << (Channel & 0x10UL))) == 0UL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvalue++;
      /* Set right trimming */
      MODIFY_REG(hdac->Instance->CCR, (DAC_CCR_OTRIM1 << (Channel & 0x10UL)), (trimmingvalue << (Channel & 0x10UL)));
    }

    /* Disable the selected DAC channel calibration */
    /* i.e. clear DAC_CR_CENx bit */
    CLEAR_BIT((hdac->Instance->CR), (DAC_CR_CEN1 << (Channel & 0x10UL)));

    sConfig->DAC_TrimmingValue = trimmingvalue;
    sConfig->DAC_UserTrimming = DAC_TRIMMING_USER;

    /* Restore configuration */
    MODIFY_REG(hdac->Instance->MCR, (DAC_MCR_MODE1 << (Channel & 0x10UL)), oldmodeconfiguration);

    /* Process unlocked */
    __HAL_UNLOCK(hdac);
  }

  return status;
}

/**
  * @brief  Set the trimming mode and trimming value (user trimming mode applied).
  * @param  hdac pointer to a DAC_HandleTypeDef structure that contains
  *         the configuration information for the specified DAC.
  * @param  sConfig DAC configuration structure updated with new DAC trimming value.
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  * @param  NewTrimmingValue DAC new trimming value
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_DACEx_SetUserTrimming(DAC_HandleTypeDef *hdac, DAC_ChannelConfTypeDef *sConfig, uint32_t Channel,
                                            uint32_t NewTrimmingValue)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(Channel));
  assert_param(IS_DAC_NEWTRIMMINGVALUE(NewTrimmingValue));

  /* Check the DAC handle allocation */
  if (hdac == NULL)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Process locked */
    __HAL_LOCK(hdac);

    /* Set new trimming */
    MODIFY_REG(hdac->Instance->CCR, (DAC_CCR_OTRIM1 << (Channel & 0x10UL)), (NewTrimmingValue << (Channel & 0x10UL)));

    /* Update trimming mode */
    sConfig->DAC_UserTrimming = DAC_TRIMMING_USER;
    sConfig->DAC_TrimmingValue = NewTrimmingValue;

    /* Process unlocked */
    __HAL_UNLOCK(hdac);
  }
  return status;
}

/**
  * @brief  Return the DAC trimming value.
  * @param  hdac DAC handle
  * @param  Channel The selected DAC channel.
  *          This parameter can be one of the following values:
  *            @arg DAC_CHANNEL_1: DAC Channel1 selected
  * @retval Trimming value : range: 0->31
  *
 */
uint32_t HAL_DACEx_GetTrimOffset(DAC_HandleTypeDef *hdac, uint32_t Channel)
{
  /* Check the parameter */
  assert_param(IS_DAC_CHANNEL(Channel));

  /* Retrieve trimming */
  return ((hdac->Instance->CCR & (DAC_CCR_OTRIM1 << (Channel & 0x10UL))) >> (Channel & 0x10UL));
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

#endif /* DAC */

#endif /* HAL_DAC_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
