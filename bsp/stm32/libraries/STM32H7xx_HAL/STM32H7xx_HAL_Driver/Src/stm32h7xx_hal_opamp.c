/**
  ******************************************************************************
  * @file    stm32h7xx_hal_opamp.c
  * @author  MCD Application Team
  * @brief   OPAMP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the operational amplifier(s) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
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
================================================================================
          ##### OPAMP Peripheral Features #####
================================================================================

  [..] The device integrates 2 operational amplifiers OPAMP1 & OPAMP2

       (#) The OPAMP(s) provides several exclusive running modes.
       (++) Standalone mode
       (++) Programmable Gain Amplifier (PGA) modes
       (++) Follower mode

       (#) Each OPAMP(s) can be configured in normal and high speed mode.

       (#) The OPAMP(s) provide(s) calibration capabilities.
       (++) Calibration aims at correcting some offset for running mode.
       (++) The OPAMP uses either factory calibration settings OR user defined
           calibration (trimming) settings (i.e. trimming mode).
       (++) The user defined settings can be figured out using self calibration
           handled by HAL_OPAMP_SelfCalibrate, HAL_OPAMPEx_SelfCalibrateAll
       (++) HAL_OPAMP_SelfCalibrate:
       (+++) Runs automatically the calibration in 2 steps.
            (90% of VDDA for NMOS transistors, 10% of VDDA for PMOS transistors).
            (As OPAMP is Rail-to-rail input/output, these 2 steps calibration is
             appropriate and enough in most cases).
       (+++) Runs automatically the calibration.
       (+++) Enables the user trimming mode
       (+++) Updates the init structure with trimming values with fresh calibration
            results.
            The user may store the calibration results for larger
            (ex monitoring the trimming as a function of temperature
            for instance)
       (+++) HAL_OPAMPEx_SelfCalibrateAll
            runs calibration of all OPAMPs in parallel to save search time.

       (#) Running mode: Standalone mode
       (++) Gain is set externally (gain depends on external loads).
       (++) Follower mode also possible externally by connecting the inverting input to
           the output.

       (#) Running mode: Follower mode
       (++) No Inverting Input is connected.

       (#) Running mode: Programmable Gain Amplifier (PGA) mode
           (Resistor feedback output)
       (#) The OPAMP(s) output(s) can be internally connected to resistor feedback
           output.
       (#) OPAMP gain can be selected as :

      (##) Gain of x2, x4, x8 or x16 for non inverting mode with:
      (+++) VREF- referenced.
      (+++) Filtering on VINM0, VREF- referenced.
      (+++) VINM0 node for bias voltage and VINP0 for input signal.
      (+++) VINM0 node for bias voltage and VINP0 for input signal, VINM1 node for filtering.

      (##) Gain of x-1, x-3, x-7 or x-15 for inverting mode with:
      (+++) VINM0 node for input signal and VINP0 for bias.
      (+++) VINM0 node for input signal and VINP0 for bias voltage, VINM1 node for filtering.

       (#) The OPAMPs inverting input can be selected according to the Reference Manual
           "OPAMP functional description" chapter.

       (#) The OPAMPs non inverting input can be selected according to the Reference Manual
           "OPAMP functional description" chapter.


            ##### How to use this driver #####
================================================================================
  [..]

    *** High speed / normal power mode ***
    ============================================
    [..]  To run in high speed mode:

      (#) Configure the OPAMP using HAL_OPAMP_Init() function:
      (++) Select OPAMP_POWERMODE_HIGHSPEED
      (++) Otherwise select OPAMP_POWERMODE_NORMAL

    *** Calibration ***
    ============================================
    [..]  To run the OPAMP calibration self calibration:

      (#) Start calibration using HAL_OPAMP_SelfCalibrate.
           Store the calibration results.

    *** Running mode ***
    ============================================

    [..]  To use the OPAMP, perform the following steps:

      (#) Fill in the HAL_OPAMP_MspInit() to
      (++) Enable the OPAMP Peripheral clock using macro __HAL_RCC_OPAMP_CLK_ENABLE()
      (++) Configure the OPAMP input AND output in analog mode using
           HAL_GPIO_Init() to map the OPAMP output to the GPIO pin.

      (#) Registrate Callbacks
      (++) The compilation define  USE_HAL_OPAMP_REGISTER_CALLBACKS when set to 1
           allows the user to configure dynamically the driver callbacks.

      (++) Use Functions HAL_OPAMP_RegisterCallback() to register a user callback,
           it allows to register following callbacks:
      (+++) MspInitCallback         : OPAMP MspInit.
      (+++) MspDeInitCallback       : OPAMP MspDeInit.
           This function takes as parameters the HAL peripheral handle, the Callback ID
           and a pointer to the user callback function.

      (++) Use function HAL_OPAMP_UnRegisterCallback() to reset a callback to the default
           weak (overridden) function. It allows to reset following callbacks:
      (+++) MspInitCallback         : OPAMP MspInit.
      (+++) MspDeInitCallback       : OPAMP MspDeInit.
      (+++) All Callbacks
      (#) Configure the OPAMP using HAL_OPAMP_Init() function:
      (++) Select the mode
      (++) Select the inverting input
      (++) Select the non-inverting input
      (++) If PGA mode is enabled, Select if inverting input is connected.
      (++) Select either factory or user defined trimming mode.
      (++) If the user-defined trimming mode is enabled, select PMOS & NMOS trimming values
          (typically values set by HAL_OPAMP_SelfCalibrate function).

      (#) Enable the OPAMP using HAL_OPAMP_Start() function.

      (#) Disable the OPAMP using HAL_OPAMP_Stop() function.

      (#) Lock the OPAMP in running mode using HAL_OPAMP_Lock() function.
          Caution: On STM32H7, HAL OPAMP lock is software lock only (not
          hardware lock as on some other STM32 devices)

      (#) If needed, unlock the OPAMP using HAL_OPAMPEx_Unlock() function.

    *** Running mode: change of configuration while OPAMP ON  ***
    ============================================
    [..] To Re-configure OPAMP when OPAMP is ON (change on the fly)
      (#) If needed, fill in the HAL_OPAMP_MspInit()
      (++) This is the case for instance if you wish to use new OPAMP I/O

      (#) Configure the OPAMP using HAL_OPAMP_Init() function:
      (++) As in configure case, select first the parameters you wish to modify.

      (#) Change from high speed mode to normal power mode (& vice versa) requires
          first HAL_OPAMP_DeInit() (force OPAMP OFF) and then HAL_OPAMP_Init().
          In other words, of OPAMP is ON, HAL_OPAMP_Init can NOT change power mode
          alone.

  @endverbatim
  ******************************************************************************
    Table 1.  OPAMPs inverting/non-inverting inputs for the STM32H7 devices:

    +------------------------------------------------------------------------|
    |                 |         | OPAMP1               | OPAMP2              |
    |-----------------|---------|----------------------|---------------------|
    | Inverting Input | VM_SEL  |   VINM0-> PC5        |    VINM0-> PE8      |
    |                 |         |   VINM1-> PA7        |    VINM1-> PG1      |
    |                 |         |   Internal:          |    Internal:        |
    |                 |         |     ADC1_IN9         |      OPAMP2_OUT     |
    |                 |         |     ADC2_IN9         |     PGA mode        |
    |                 |         |     OPAMP1_OUT       |                     |
    |                 |         |     PGA mode         |                     |
    |-----------------|---------|----------------------|---------------------|
    |  Non Inverting  | VP_SEL  |                      |                     |
    |                 |         |  VP0 -> PB0 (GPIO)   |  VP0 -> PE9 (GPIO)  |
    |                 |         |  Internal:           |  Internal:          |
    |    Input        |         |    DAC1_CH1_int      |   DAC1_CH2_int      |
    |                 |         |    ADC1_IN8          |   DAC2_CH1_int      |
    |                 |         |    ADC2_IN8          |   COMP2_INP         |
    |                 |         |    COMP1_INP         |                     |
    +------------------------------------------------------------------------|


   [..] Table 2.  OPAMPs outputs for the STM32H7 devices:

    +-------------------------------------------------------------------------
    |                 |        | OPAMP1                | OPAMP2              |
    |-----------------|--------|-----------------------|---------------------|
    | Output          |  VOUT  |  PC4                  |  PE7                |
    |                 |        |  & ADC1_IN4|          | & COMP2_INN7 if     |
    |                 |        |    ADC2_IN4           |connected internally |
    |                 |        |   COMP1_INN7 if       |                     |
    |                 |        |  connected internally |                     |
    |-----------------|--------|-----------------------|---------------------|
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @defgroup OPAMP OPAMP
  * @brief OPAMP module driver
  * @{
  */

#ifdef HAL_OPAMP_MODULE_ENABLED

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @addtogroup OPAMP_Private_Constants
  * @{
  */

/* CSR register reset value */
#define OPAMP_CSR_RESET_VALUE             0x00000000U

/* CSR Init masks */

#define OPAMP_CSR_INIT_MASK_PGA (OPAMP_CSR_OPAHSM | OPAMP_CSR_VMSEL | OPAMP_CSR_PGGAIN | OPAMP_CSR_PGGAIN  \
                                | OPAMP_CSR_VPSEL | OPAMP_CSR_USERTRIM)


#define OPAMP_CSR_INIT_MASK_FOLLOWER (OPAMP_CSR_OPAHSM | OPAMP_CSR_VMSEL| OPAMP_CSR_VPSEL \
                                    | OPAMP_CSR_USERTRIM)


#define OPAMP_CSR_INIT_MASK_STANDALONE (OPAMP_CSR_OPAHSM | OPAMP_CSR_VMSEL | OPAMP_CSR_VPSEL  \
                                       | OPAMP_CSR_VMSEL | OPAMP_CSR_USERTRIM)
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup OPAMP_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and Configuration functions
 *
@verbatim
  ==============================================================================
              ##### Initialization and de-initialization functions #####
  ==============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the OPAMP according to the specified
  *         parameters in the OPAMP_InitTypeDef and initialize the associated handle.
  * @note   If the selected opamp is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Init(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t updateotrlpotr;

  /* Check the OPAMP handle allocation and lock status */
  /* Init not allowed if calibration is ongoing */
  if(hopamp == NULL)
  {
    return HAL_ERROR;
  }
  else if(hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    return HAL_ERROR;
  }
  else if(hopamp->State == HAL_OPAMP_STATE_CALIBBUSY)
  {
    return HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    /* Set OPAMP parameters */
    assert_param(IS_OPAMP_POWERMODE(hopamp->Init.PowerMode));
    assert_param(IS_OPAMP_FUNCTIONAL_NORMALMODE(hopamp->Init.Mode));
    assert_param(IS_OPAMP_NONINVERTING_INPUT(hopamp->Init.NonInvertingInput));

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
    if(hopamp->State == HAL_OPAMP_STATE_RESET)
    {
      if(hopamp->MspInitCallback == NULL)
      {
        hopamp->MspInitCallback               = HAL_OPAMP_MspInit;
      }
    }
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */
    if ((hopamp->Init.Mode) == OPAMP_STANDALONE_MODE)
    {
      assert_param(IS_OPAMP_INVERTING_INPUT_STANDALONE(hopamp->Init.InvertingInput));
    }

    if ((hopamp->Init.Mode) == OPAMP_PGA_MODE)
    {
      assert_param(IS_OPAMP_PGA_GAIN(hopamp->Init.PgaGain));
      assert_param(IS_OPAMP_PGACONNECT(hopamp->Init.PgaConnect));
    }


    assert_param(IS_OPAMP_TRIMMING(hopamp->Init.UserTrimming));

    if ((hopamp->Init.UserTrimming) == OPAMP_TRIMMING_USER)
    {
      if (hopamp->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueP));
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueN));
      }
    else
      {
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValuePHighSpeed));
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueNHighSpeed));
      }
    }

    if(hopamp->State == HAL_OPAMP_STATE_RESET)
    {
      /* Allocate lock resource and initialize it */
      hopamp->Lock = HAL_UNLOCKED;
    }

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
    hopamp->MspInitCallback(hopamp);
#else
    /* Call MSP init function */
    HAL_OPAMP_MspInit(hopamp);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

    /* Set operating mode */
    CLEAR_BIT(hopamp->Instance->CSR, OPAMP_CSR_CALON);
    /* In PGA mode InvertingInput is Not Applicable  */
    if (hopamp->Init.Mode == OPAMP_PGA_MODE)
    {
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_INIT_MASK_PGA, \
                                        hopamp->Init.PowerMode | \
                                        hopamp->Init.Mode | \
                                        hopamp->Init.PgaGain | \
                                        hopamp->Init.PgaConnect | \
                                        hopamp->Init.NonInvertingInput | \
                                        hopamp->Init.UserTrimming);
    }

    if (hopamp->Init.Mode == OPAMP_FOLLOWER_MODE)
    {
  /* In Follower mode InvertingInput is Not Applicable  */
    MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_INIT_MASK_FOLLOWER, \
                                              hopamp->Init.PowerMode | \
                                              hopamp->Init.Mode | \
                                              hopamp->Init.NonInvertingInput | \
                                              hopamp->Init.UserTrimming);
    }

    if (hopamp->Init.Mode == OPAMP_STANDALONE_MODE)
    {
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_INIT_MASK_STANDALONE, \
                                        hopamp->Init.PowerMode | \
                                        hopamp->Init.Mode | \
                                        hopamp->Init.InvertingInput    | \
                                        hopamp->Init.NonInvertingInput | \
                                        hopamp->Init.UserTrimming);
    }

    if (hopamp->Init.UserTrimming == OPAMP_TRIMMING_USER)
    {
      /* Set power mode and associated calibration parameters */
      if (hopamp->Init.PowerMode != OPAMP_POWERMODE_HIGHSPEED)
      {
        /* OPAMP_POWERMODE_NORMAL */
        /* Set calibration mode (factory or user) and values for            */
        /* transistors differential pair high (PMOS) and low (NMOS) for     */
        /* normal mode.                                                     */
        updateotrlpotr = (((hopamp->Init.TrimmingValueP) << (OPAMP_INPUT_NONINVERTING)) \
                         | (hopamp->Init.TrimmingValueN));
        MODIFY_REG(hopamp->Instance->OTR, OPAMP_OTR_TRIMOFFSETN | OPAMP_OTR_TRIMOFFSETP, updateotrlpotr);
      }
      else
      {
        /* OPAMP_POWERMODE_HIGHSPEED*/
        /* transistors differential pair high (PMOS) and low (NMOS) for     */
        /* high speed mode.                                                     */
        updateotrlpotr = (((hopamp->Init.TrimmingValuePHighSpeed) << (OPAMP_INPUT_NONINVERTING)) \
                         | (hopamp->Init.TrimmingValueNHighSpeed));
        MODIFY_REG(hopamp->Instance->HSOTR, OPAMP_OTR_TRIMOFFSETN | OPAMP_OTR_TRIMOFFSETP, updateotrlpotr);
      }
    }

    /* Update the OPAMP state*/
    if (hopamp->State == HAL_OPAMP_STATE_RESET)
    {
      /* From RESET state to READY State */
      hopamp->State = HAL_OPAMP_STATE_READY;
    }
    /* else: remain in READY or BUSY state (no update) */
    return status;
  }
}

/**
  * @brief  DeInitialize the OPAMP peripheral
  * @note   Deinitialization can be performed if the OPAMP configuration is locked.
  *         (the lock is SW in H7)
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_DeInit(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* DeInit not allowed if calibration is on going */
  if(hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if(hopamp->State == HAL_OPAMP_STATE_CALIBBUSY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    /* Set OPAMP_CSR register to reset value */
    WRITE_REG(hopamp->Instance->CSR, OPAMP_CSR_RESET_VALUE);

    /* DeInit the low level hardware */
#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
    if(hopamp->MspDeInitCallback == NULL)
    {
      hopamp->MspDeInitCallback = HAL_OPAMP_MspDeInit;
    }
    /* DeInit the low level hardware */
    hopamp->MspDeInitCallback(hopamp);
#else
    HAL_OPAMP_MspDeInit(hopamp);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

    /* Update the OPAMP state*/
    hopamp->State = HAL_OPAMP_STATE_RESET;
    /* Process unlocked */
    __HAL_UNLOCK(hopamp);

  }

  return status;
}


/**
  * @brief  Initialize the OPAMP MSP.
  * @param  hopamp OPAMP handle
  * @retval None
  */
__weak void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef *hopamp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hopamp);

  /* NOTE : This function should not be modified, when the callback is needed,
            the function "HAL_OPAMP_MspInit()" must be implemented in the user file.
   */
}

/**
  * @brief  DeInitialize OPAMP MSP.
  * @param  hopamp OPAMP handle
  * @retval None
  */
__weak void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef *hopamp)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hopamp);
  /* NOTE : This function should not be modified, when the callback is needed,
            the function "HAL_OPAMP_MspDeInit()" must be implemented in the user file.
   */
}

/**
  * @}
  */


/** @defgroup OPAMP_Exported_Functions_Group2 IO operation functions
 *  @brief   IO operation functions
 *
@verbatim
 ===============================================================================
                        ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the OPAMP
    start, stop and calibration actions.

@endverbatim
  * @{
  */

/**
  * @brief  Start the OPAMP.
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Start(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  if(hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if(hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    if(hopamp->State == HAL_OPAMP_STATE_READY)
    {
      /* Enable the selected opamp */
      SET_BIT (hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);

      /* Update the OPAMP state*/
      /* From HAL_OPAMP_STATE_READY to HAL_OPAMP_STATE_BUSY */
      hopamp->State = HAL_OPAMP_STATE_BUSY;
    }
    else
    {
      status = HAL_ERROR;
    }

   }
  return status;
}

/**
  * @brief  Stop the OPAMP.
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Stop(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  /* Check if OPAMP calibration ongoing */
  if(hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if(hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    status = HAL_ERROR;
  }
  else if(hopamp->State == HAL_OPAMP_STATE_CALIBBUSY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    if(hopamp->State == HAL_OPAMP_STATE_BUSY)
    {
      /* Disable the selected opamp */
      CLEAR_BIT (hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);

      /* Update the OPAMP state*/
      /* From  HAL_OPAMP_STATE_BUSY to HAL_OPAMP_STATE_READY*/
      hopamp->State = HAL_OPAMP_STATE_READY;
    }
    else
    {
      status = HAL_ERROR;
    }
  }
  return status;
}

/**
  * @brief  Run the self calibration of one OPAMP.
  * @note   Calibration is performed in the mode specified in OPAMP init
  *         structure (mode normal or high-speed). To perform calibration for
  *         both modes, repeat this function twice after OPAMP init structure
  *         accordingly updated.
  * @param  hopamp handle
  * @retval Updated offset trimming values (PMOS & NMOS), user trimming is enabled
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_SelfCalibrate(OPAMP_HandleTypeDef *hopamp)
{

  HAL_StatusTypeDef status = HAL_OK;

  uint32_t trimmingvaluen;
  uint32_t trimmingvaluep;
  uint32_t delta;
  uint32_t opampmode;

  __IO uint32_t* tmp_opamp_reg_trimming;   /* Selection of register of trimming depending on power mode: OTR or HSOTR */

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  if(hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if(hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    status = HAL_ERROR;
  }
  else
  {

    /* Check if OPAMP in calibration mode and calibration not yet enable */
    if(hopamp->State ==  HAL_OPAMP_STATE_READY)
    {
      /* Check the parameter */
      assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
      assert_param(IS_OPAMP_POWERMODE(hopamp->Init.PowerMode));

      opampmode = READ_BIT(hopamp->Instance->CSR,OPAMP_CSR_VMSEL);

      /* Use of standalone mode */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_VMSEL, OPAMP_STANDALONE_MODE);
      /*  user trimming values are used for offset calibration */
      SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_USERTRIM);

      /* Select trimming settings depending on power mode */
      if (hopamp->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        tmp_opamp_reg_trimming = &hopamp->Instance->OTR;

      }
      else
      {
        /* high speed Mode */
        tmp_opamp_reg_trimming = &hopamp->Instance->HSOTR;
      }


      /* Enable calibration */
      SET_BIT (hopamp->Instance->CSR, OPAMP_CSR_CALON);

      /* Force internal reference on VP */
      SET_BIT (hopamp->Instance->CSR, OPAMP_CSR_FORCEVP);

      /* 1st calibration - N */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);

      /* Enable the selected opamp */
      SET_BIT (hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);

      /* Init trimming counter */
      /* Medium value */
      trimmingvaluen = 16U;
      delta = 8U;

      while (delta != 0U)
      {
        /* Set candidate trimming */
        /* OPAMP_POWERMODE_NORMAL */
        MODIFY_REG(*tmp_opamp_reg_trimming, OPAMP_OTR_TRIMOFFSETN, trimmingvaluen);

        /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
        /* Offset trim time: during calibration, minimum time needed between */
        /* two steps to have 1 mV accuracy */
        HAL_Delay(OPAMP_TRIMMING_DELAY);

        if (READ_BIT(hopamp->Instance->CSR, OPAMP_CSR_CALOUT) != 0U)
        {
          /* OPAMP_CSR_CALOUT is HIGH try higher trimming */
          trimmingvaluen += delta;
        }
        else
        {
          /* OPAMP_CSR_CALOUT is LOW try lower trimming */
          trimmingvaluen -= delta;
        }
        /* Divide range by 2 to continue dichotomy sweep */
        delta >>= 1;
      }

      /* Still need to check if right calibration is current value or one step below */
      /* Indeed the first value that causes the OUTCAL bit to change from 1  to 0  */

      MODIFY_REG(*tmp_opamp_reg_trimming, OPAMP_OTR_TRIMOFFSETN, trimmingvaluen);

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(OPAMP_TRIMMING_DELAY);

      if ((READ_BIT(hopamp->Instance->CSR, OPAMP_CSR_CALOUT)) != 0U)
      {
        /* Trimming value is actually one value more */
        trimmingvaluen++;
        /* Set right trimming */
        MODIFY_REG(*tmp_opamp_reg_trimming, OPAMP_OTR_TRIMOFFSETN, trimmingvaluen);
      }

      /* 2nd calibration - P */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);

      /* Init trimming counter */
      /* Medium value */
      trimmingvaluep = 16U;
      delta = 8U;

      while (delta != 0U)
      {
        /* Set candidate trimming */
        /* OPAMP_POWERMODE_NORMAL */
        MODIFY_REG(*tmp_opamp_reg_trimming, OPAMP_OTR_TRIMOFFSETP, (trimmingvaluep<<OPAMP_INPUT_NONINVERTING));

        /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
        /* Offset trim time: during calibration, minimum time needed between */
        /* two steps to have 1 mV accuracy */
        HAL_Delay(OPAMP_TRIMMING_DELAY);

        if (READ_BIT(hopamp->Instance->CSR, OPAMP_CSR_CALOUT)!= 0U)
        {
          /* OPAMP_CSR_CALOUT is HIGH try higher trimming */
          trimmingvaluep += delta;
        }
        else
        {
          /* OPAMP_CSR_CALOUT  is LOW try lower trimming */
          trimmingvaluep -= delta;
        }

        /* Divide range by 2 to continue dichotomy sweep */
        delta >>= 1U;
      }

      /* Still need to check if right calibration is current value or one step below */
      /* Indeed the first value that causes the OUTCAL bit to change from 1 to 0  */
      /* Set candidate trimming */
      MODIFY_REG(*tmp_opamp_reg_trimming, OPAMP_OTR_TRIMOFFSETP, (trimmingvaluep<<OPAMP_INPUT_NONINVERTING));

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(OPAMP_TRIMMING_DELAY);

      if (READ_BIT(hopamp->Instance->CSR, OPAMP_CSR_CALOUT) != 0U)
      {
        /* Trimming value is actually one value more */
        trimmingvaluep++;
        MODIFY_REG(*tmp_opamp_reg_trimming, OPAMP_OTR_TRIMOFFSETP, (trimmingvaluep<<OPAMP_INPUT_NONINVERTING));
      }

      /* Disable calibration & set normal mode (operating mode) */
      CLEAR_BIT (hopamp->Instance->CSR, OPAMP_CSR_CALON);

      /* Disable the OPAMP */
      CLEAR_BIT (hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);

      /* Set operating mode back */
      CLEAR_BIT(hopamp->Instance->CSR, OPAMP_CSR_FORCEVP);

      /* Self calibration is successful  */
      /* Store calibration(user trimming) results in init structure. */

      /* Set user trimming mode */
      hopamp->Init.UserTrimming = OPAMP_TRIMMING_USER;

      /* Affect calibration parameters depending on mode normal/high speed */
      if (hopamp->Init.PowerMode != OPAMP_POWERMODE_HIGHSPEED)
      {
        /* Write calibration result N */
        hopamp->Init.TrimmingValueN = trimmingvaluen;
        /* Write calibration result P */
        hopamp->Init.TrimmingValueP = trimmingvaluep;
      }
      else
      {
        /* Write calibration result N */
        hopamp->Init.TrimmingValueNHighSpeed = trimmingvaluen;
        /* Write calibration result P */
        hopamp->Init.TrimmingValuePHighSpeed = trimmingvaluep;
      }
    /* Restore OPAMP mode after calibration */
    MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_VMSEL, opampmode);
    }

    else
    {
      /* OPAMP can not be calibrated from this mode */
      status = HAL_ERROR;
    }
  }
  return status;
}

/**
  * @}
  */

/** @defgroup OPAMP_Exported_Functions_Group3 Peripheral Control functions
 *  @brief   Peripheral Control functions
 *
@verbatim
 ===============================================================================
                      ##### Peripheral Control functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to control the OPAMP data
    transfers.



@endverbatim
  * @{
  */

/**
  * @brief  Lock the selected OPAMP configuration.
  * @note   On STM32H7, HAL OPAMP lock is software lock only (in
  *         contrast of hardware lock available on some other STM32
  *         devices)
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Lock(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  /* OPAMP can be locked when enabled and running in normal mode */
  /*   It is meaningless otherwise */
  if(hopamp == NULL)
  {
    status = HAL_ERROR;
  }

  else if(hopamp->State != HAL_OPAMP_STATE_BUSY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

   /* OPAMP state changed to locked */
    hopamp->State = HAL_OPAMP_STATE_BUSYLOCKED;
  }
  return status;
}

/**
  * @brief  Return the OPAMP factory trimming value.
  * @note            On STM32H7 OPAMP, user can retrieve factory trimming if
  *                  OPAMP has never been set to user trimming before.
  *                  Therefore, this function must be called when OPAMP init
  *                  parameter "UserTrimming" is set to trimming factory,
  *                  and before OPAMP  calibration (function
  *                  "HAL_OPAMP_SelfCalibrate()").
  *                  Otherwise, factory trimming value cannot be retrieved and
  *                  error status is returned.
  * @param  hopamp  OPAMP handle
  * @param  trimmingoffset  Trimming offset (P or N)
  *         This parameter must be a value of @ref OPAMP_FactoryTrimming
  * @note   Calibration parameter retrieved is corresponding to the mode
  *         specified in OPAMP init structure (mode normal or high-speed).
  *         To retrieve calibration parameters for both modes, repeat this
  *         function after OPAMP init structure accordingly updated.
  * @retval Trimming value (P or N): range: 0->31
  *         or OPAMP_FACTORYTRIMMING_DUMMY if trimming value is not available
  *
  */
HAL_OPAMP_TrimmingValueTypeDef HAL_OPAMP_GetTrimOffset (OPAMP_HandleTypeDef *hopamp, uint32_t trimmingoffset)
{
  HAL_OPAMP_TrimmingValueTypeDef trimmingvalue;
  __IO uint32_t* tmp_opamp_reg_trimming;  /* Selection of register of trimming depending on power mode: OTR or LPOTR */

  /* Check the OPAMP handle allocation */
  /* Value can be retrieved in HAL_OPAMP_STATE_READY state */
  if(hopamp == NULL)
  {
    return OPAMP_FACTORYTRIMMING_DUMMY;
  }

  if(hopamp->State == HAL_OPAMP_STATE_READY)
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
    assert_param(IS_OPAMP_FACTORYTRIMMING(trimmingoffset));
    assert_param(IS_OPAMP_POWERMODE(hopamp->Init.PowerMode));

    /* Check the trimming mode */
    if (READ_BIT(hopamp->Instance->CSR,OPAMP_CSR_USERTRIM)!= 0U)
    {
      /* This function must called when OPAMP init parameter "UserTrimming"   */
      /* is set to trimming factory, and before OPAMP calibration (function   */
      /* "HAL_OPAMP_SelfCalibrate()").                                        */
      /* Otherwise, factory trimming value cannot be retrieved and error       */
      /* status is returned.                                                  */
      trimmingvalue = OPAMP_FACTORYTRIMMING_DUMMY;
    }
    else
    {
      /* Select trimming settings depending on power mode */
      if (hopamp->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        tmp_opamp_reg_trimming = &hopamp->Instance->OTR;
      }
      else
      {
        tmp_opamp_reg_trimming = &hopamp->Instance->HSOTR;
      }

      /* Get factory trimming  */
      if (trimmingoffset == OPAMP_FACTORYTRIMMING_P)
      {
        /* OPAMP_FACTORYTRIMMING_P */
        trimmingvalue = ((*tmp_opamp_reg_trimming) & OPAMP_OTR_TRIMOFFSETP) >> OPAMP_INPUT_NONINVERTING;
      }
      else
      {
        /* OPAMP_FACTORYTRIMMING_N */
        trimmingvalue = (*tmp_opamp_reg_trimming) & OPAMP_OTR_TRIMOFFSETN;
      }
    }
  }
  else
  {
    return OPAMP_FACTORYTRIMMING_DUMMY;
  }

  return trimmingvalue;
}

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User OPAMP Callback
  *         To be used instead of the weak (overridden) predefined callback
  * @param hopamp  OPAMP handle
  * @param CallbackId  ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_OPAMP_MSPINIT_CB_ID       OPAMP MspInit callback ID
  *          @arg @ref HAL_OPAMP_MSPDEINIT_CB_ID     OPAMP MspDeInit callback ID
  * @param pCallback  pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_OPAMP_RegisterCallback (OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackId, pOPAMP_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if(pCallback == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hopamp);

  if(hopamp->State == HAL_OPAMP_STATE_READY)
  {
    switch (CallbackId)
    {
    case HAL_OPAMP_MSPINIT_CB_ID :
      hopamp->MspInitCallback = pCallback;
      break;
    case HAL_OPAMP_MSPDEINIT_CB_ID :
      hopamp->MspDeInitCallback = pCallback;
      break;
    default :
      /* update return status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if (hopamp->State == HAL_OPAMP_STATE_RESET)
  {
    switch (CallbackId)
    {
    case HAL_OPAMP_MSPINIT_CB_ID :
      hopamp->MspInitCallback = pCallback;
      break;
    case HAL_OPAMP_MSPDEINIT_CB_ID :
      hopamp->MspDeInitCallback = pCallback;
      break;
    default :
      /* update return status */
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hopamp);
  return status;
}

/**
  * @brief  Unregister a User OPAMP Callback
  *         OPAMP Callback is redirected to the weak (overridden) predefined callback
  * @param hopamp  OPAMP handle
  * @param CallbackId  ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_OPAMP_MSPINIT_CB_ID    OPAMP MSP Init Callback ID
  *          @arg @ref HAL_OPAMP_MSPDEINIT_CB_ID  OPAMP MSP DeInit Callback ID
  *          @arg @ref HAL_OPAMP_ALL_CB_ID        OPAMP All Callbacks
  * @retval status
  */
HAL_StatusTypeDef HAL_OPAMP_UnRegisterCallback (OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackId)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hopamp);

  if(hopamp->State == HAL_OPAMP_STATE_READY)
  {
    switch (CallbackId)
    {
    case HAL_OPAMP_MSPINIT_CB_ID :
      hopamp->MspInitCallback = HAL_OPAMP_MspInit;
      break;
    case HAL_OPAMP_MSPDEINIT_CB_ID :
      hopamp->MspDeInitCallback = HAL_OPAMP_MspDeInit;
      break;
    case HAL_OPAMP_ALL_CB_ID :
      hopamp->MspInitCallback = HAL_OPAMP_MspInit;
      hopamp->MspDeInitCallback = HAL_OPAMP_MspDeInit;
      break;
    default :
      /* update return status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if (hopamp->State == HAL_OPAMP_STATE_RESET)
  {
    switch (CallbackId)
    {
    case HAL_OPAMP_MSPINIT_CB_ID :
      hopamp->MspInitCallback = HAL_OPAMP_MspInit;
      break;
    case HAL_OPAMP_MSPDEINIT_CB_ID :
      hopamp->MspDeInitCallback = HAL_OPAMP_MspDeInit;
      break;
    default :
      /* update return status */
      status =  HAL_ERROR;
      break;
    }
  }
  else
  {
    /* update return status */
    status =  HAL_ERROR;
  }

  /* Release Lock */
  __HAL_UNLOCK(hopamp);
  return status;
}

#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

/**
  * @}
  */


/** @defgroup OPAMP_Exported_Functions_Group4 Peripheral State functions
  *  @brief   Peripheral State functions
  *
@verbatim
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Return the OPAMP handle state.
  * @param  hopamp  OPAMP handle
  * @retval HAL state
  */
HAL_OPAMP_StateTypeDef HAL_OPAMP_GetState(OPAMP_HandleTypeDef *hopamp)
{
  /* Check the OPAMP handle allocation */
  if(hopamp == NULL)
  {
    return HAL_OPAMP_STATE_RESET;
  }

  /* Check the parameter */
  assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

  /* Return OPAMP handle state */
  return hopamp->State;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* HAL_OPAMP_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

