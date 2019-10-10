/**
  ******************************************************************************
  * @file    stm32g4xx_hal_opamp.c
  * @author  MCD Application Team
  * @brief   OPAMP HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the operational amplifiers (OPAMP1,...OPAMP6)
  *          peripheral:
  *           + OPAMP Configuration
  *           + OPAMP calibration
  *          Thanks to
  *           + Initialization/de-initialization functions
  *           + I/O operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
================================================================================
          ##### OPAMP Peripheral Features #####
================================================================================

  [..] The device integrates up to 6 operational amplifiers OPAMP1, OPAMP2,
       OPAMP3, OPAMP4, OPAMP5 and OPAMP6:

       (#) The OPAMP(s) provides several exclusive running modes.
       (++) Standalone mode
       (++) Programmable Gain Amplifier (PGA) mode (Resistor feedback output)
       (++) Follower mode

       (#) The OPAMP(s) provide(s) calibration capabilities.
       (++) Calibration aims at correcting some offset for running mode.
       (++) The OPAMP uses either factory calibration settings OR user defined
           calibration (trimming) settings (i.e. trimming mode).
       (++) The user defined settings can be figured out using self calibration
           handled by HAL_OPAMP_SelfCalibrate, HAL_OPAMPEx_SelfCalibrateAll
       (++) HAL_OPAMP_SelfCalibrate:
       (++) Runs automatically the calibration in 2 steps.
            (90% of VDDA for NMOS transistors, 10% of VDDA for PMOS transistors).
            (As OPAMP is Rail-to-rail input/output, these 2 steps calibration is
            appropriate and enough in most cases).
       (++) Enables the user trimming mode
       (++) Updates the init structure with trimming values with fresh calibration
            results.
            The user may store the calibration results for larger
            (ex monitoring the trimming as a function of temperature
            for instance)
       (++) for STM32G4 devices having 6 OPAMPs
            HAL_OPAMPEx_SelfCalibrateAll
            runs calibration of 6 OPAMPs in parallel.

       (#) For any running mode, an additional Timer-controlled Mux (multiplexer)
           mode can be set on top.
       (++) Timer-controlled Mux mode allows Automatic switching of inputs
           configuration (inverting and non inverting).
       (++) Hence on top of defaults (primary) inverting and non-inverting inputs,
           the user shall select secondary inverting and non inverting inputs.
       (++) TIM1 OC6, TIM8 OC6 and TIM20 OC6 provides the alternate switching
           tempo between defaults (primary) and secondary inputs.
       (++) These 3 timers (TIM1, TIM8 and TIM20) can be combined to design a more
           complex switching scheme. So that any of the selected channel can initiate
           the configuration switch.

       (#) Running mode: Standalone mode
       (++) Gain is set externally (gain depends on external loads).
       (++) Follower mode also possible externally by connecting the inverting input to
           the output.

       (#) Running mode: Follower mode
       (++) Inverting Input is not connected.

       (#) Running mode: Programmable Gain Amplifier (PGA) mode
           (Resistor feedback output)
       (++) The OPAMP(s) output(s) can be internally connected to resistor feedback
           output.
       (++) The OPAMP inverting input can be "not" connected, signal to amplify is
           connected to non inverting input and gain is positive (2,4,8,16,32 or 64)
       (++) The OPAMP inverting input can be connected to VINM0:
           If signal is applied to non inverting input, gain is positive (2,4,8,16,32 or 64).
           If signal is applied to inverting input, gain is negative (-1,-3,-7,-15-,31 or -63).
           In both cases, the other input can be used as bias.


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
      (++) Configure the OPAMP input AND output in analog mode using
          HAL_GPIO_Init() to map the OPAMP output to the GPIO pin.

      (#) Registrate Callbacks
      (++) The compilation define  USE_HAL_OPAMP_REGISTER_CALLBACKS when set to 1
           allows the user to configure dynamically the driver callbacks.

      (++) Use Functions @ref HAL_OPAMP_RegisterCallback() to register a user callback,
           it allows to register following callbacks:
      (+++) MspInitCallback         : OPAMP MspInit.
      (+++) MspDeInitCallback       : OPAMP MspDeInit.
           This function takes as parameters the HAL peripheral handle, the Callback ID
           and a pointer to the user callback function.

      (++) Use function @ref HAL_OPAMP_UnRegisterCallback() to reset a callback to the default
           weak (surcharged) function. It allows to reset following callbacks:
      (+++) MspInitCallback         : OPAMP MspInit.
      (+++) MspDeInitCallback       : OPAMP MspDeInit.
      (+++) All Callbacks

      (#) Configure the OPAMP using HAL_OPAMP_Init() function:
      (++) Select the mode
      (++) Select the inverting input
      (++) Select the non-inverting input
      (++) Select if the internal ouput should be enabled/disabled (if enabled, regular I/O output is disabled)
      (++) Select if the Timer controlled Mux is disabled or enabled and controlled by specified timer(s)
      (++) If the Timer controlled Mux mode is enabled, select the secondary inverting input
      (++) If the Timer controlled Mux mode is enabled, Select the secondary non-inverting input
      (++) If PGA mode is enabled, Select if inverting input is connected.
      (++) If PGA mode is enabled, Select PGA gain to be used.
      (++) Select either factory or user defined trimming mode.
      (++) If the user defined trimming mode is enabled, select PMOS & NMOS trimming values
          (typ. settings returned by HAL_OPAMP_SelfCalibrate function).

      (#) Enable the OPAMP using HAL_OPAMP_Start() function.

      (#) Disable the OPAMP using HAL_OPAMP_Stop() function.

      (#) Lock the OPAMP in running mode using HAL_OPAMP_Lock() & HAL_OPAMP_TimerMuxLock functions.
          From then the configuration can only be modified
      (++) After HW reset
      (++) OR thanks to HAL_OPAMP_MspDeInit called (user defined) from HAL_OPAMP_DeInit.

    *** Running mode: change of configuration while OPAMP ON  ***
    ============================================
    [..]    To Re-configure OPAMP when OPAMP is ON (change on the fly)
      (#) If needed, fill in the HAL_OPAMP_MspInit()
      (++) This is the case for instance if you wish to use new OPAMP I/O

      (#) Configure the OPAMP using HAL_OPAMP_Init() function:
      (++) As in configure case, selects first the parameters you wish to modify.
      (++) If OPAMP control register is locked, it is not possible to modify any values
          on the fly (even the timer controlled mux parameters).
      (++) If OPAMP timer controlled mux mode register is locked, it is possible to modify any values
          of the control register but none on the timer controlled mux mode one.

      (#) Change from high speed mode to normal power mode (& vice versa) requires
          first HAL_OPAMP_DeInit() (force OPAMP OFF) and then HAL_OPAMP_Init().
          In other words, of OPAMP is ON, HAL_OPAMP_Init can NOT change power mode
          alone.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/*
  Additional Tables:
    The OPAMPs non inverting input (both default and secondary) can be
    selected among the list shown by table below.

    The OPAMPs non inverting input (both default and secondary) can be
    selected among the list shown by table below.

    Table 1.  OPAMPs inverting/non-inverting inputs for the STM32G4 devices:
    +--------------------------------------------------------------------------------------------+
    |                 |        | OPAMP1   | OPAMP2   | OPAMP3   | OPAMP4   | OPAMP5   | OPAMP6   |
    |-----------------|--------|----------|----------|----------|----------|----------|----------|
    |                 | No conn|  X       |  X       |  X       |  X       |  X       |  X       |
    | Inverting Input | VM0    | PA3      | PA5      | PB2      | PB10     | PB15     | PA1      |
    | (1)             | VM1    | PC5      | PC5      | PB10     | PD8      | PA3      | PB1      |
    |-----------------|--------|----------|----------|----------|----------|----------|----------|
    |                 | VP0    | PA1      | PA7      | PB0      | PB13     | PB14     | PB12     |
    |  Non Inverting  | VP1    | PA3      | PB14     | PB13     | PD11     | PD12     | PD9      |
    |    Input        | VP2    | PA7      | PB0      | PA1      | PB11     | PC3      | PB13     |
    |                 | VP3    | DAC3_CH1 | PD14     | DAC3_CH2 | DAC4_CH1 | DAC4_CH2 | DAC3_CH1 |
    +--------------------------------------------------------------------------------------------+
    (1): No connection in follower mode.

    Table 2.  OPAMPs outputs for the STM32G4 devices:
    +--------------------------------------------------------------------------------+
    |                 |        | OPAMP1 | OPAMP2 | OPAMP3 | OPAMP4 | OPAMP5 | OPAMP6 |
    |-----------------|--------|--------|--------|--------|--------|--------|--------|
    | Output          |        |  PA2   |  PA6   |  PB1   |  PB12  |  PA8   |  PB11  |
    |-----------------|--------|--------|--------|--------|--------|--------|--------+
    | Internal output |        |  ADC1  |  ADC2  |  ADC2  |  ADC5  |  ADC5  |  ADC4  |
    | to ADCs         |        |  CH13  |  CH16  |  CH18  |  CH5   |  CH3   |  CH17  |
    |                 |        |        |        |  ADC3  |        |        |        |
    |                 |        |        |        |  CH13  |        |        |        |
    |-----------------|--------|--------|--------|--------|--------|--------|--------+

*/

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

#ifdef HAL_OPAMP_MODULE_ENABLED

/** @defgroup OPAMP OPAMP
  * @brief OPAMP HAL module driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup OPAMP_Private_Define OPAMP Private Define
  * @{
  */
/* CSR register reset value */
#define OPAMP_CSR_RESET_VALUE             (0x00000000UL)
/* CSR register TRIM value upon reset are factory ones, filter them out from CSR register check */
#define OPAMP_CSR_RESET_CHECK_MASK        (~(OPAMP_CSR_TRIMOFFSETN | OPAMP_CSR_TRIMOFFSETP))
/* CSR init register Mask */
#define OPAMP_CSR_UPDATE_PARAMETERS_INIT_MASK (OPAMP_CSR_TRIMOFFSETN | OPAMP_CSR_TRIMOFFSETP \
                                               | OPAMP_CSR_HIGHSPEEDEN | OPAMP_CSR_OPAMPINTEN \
                                               | OPAMP_CSR_PGGAIN | OPAMP_CSR_VPSEL \
                                               | OPAMP_CSR_VMSEL | OPAMP_CSR_FORCEVP)
/* TCMR init register Mask */
#define OPAMP_TCMR_UPDATE_PARAMETERS_INIT_MASK (OPAMP_TCMR_T20CMEN | OPAMP_TCMR_T8CMEN \
                                                | OPAMP_TCMR_T1CMEN | OPAMP_TCMR_VPSSEL \
                                                | OPAMP_TCMR_VMSSEL)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup OPAMP_Exported_Functions OPAMP Exported Functions
  * @{
  */

/** @defgroup OPAMP_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization  functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the OPAMP according to the specified
  *         parameters in the OPAMP_InitTypeDef and initialize the associated handle.
  * @note   If the selected opamp is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Init(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation and lock status */
  /* Init not allowed if calibration is ongoing */
  if (hopamp == NULL)
  {
    return HAL_ERROR;
  }
  else if (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    return HAL_ERROR;
  }
  else if (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY)
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
    if (hopamp->State == HAL_OPAMP_STATE_RESET)
    {
      if (hopamp->MspInitCallback == NULL)
      {
        hopamp->MspInitCallback               = HAL_OPAMP_MspInit;
      }
    }
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

    if ((hopamp->Init.Mode) == OPAMP_STANDALONE_MODE)
    {
      assert_param(IS_OPAMP_INVERTING_INPUT(hopamp->Init.InvertingInput));
    }
    assert_param(IS_FUNCTIONAL_STATE(hopamp->Init.InternalOutput));

    assert_param(IS_OPAMP_TIMERCONTROLLED_MUXMODE(hopamp->Init.TimerControlledMuxmode));

    if ((hopamp->Init.TimerControlledMuxmode) != OPAMP_TIMERCONTROLLEDMUXMODE_DISABLE)
    {
      assert_param(IS_OPAMP_SEC_NONINVERTING_INPUT(hopamp->Init.NonInvertingInputSecondary));
      assert_param(IS_OPAMP_SEC_INVERTING_INPUT(hopamp->Init.InvertingInputSecondary));
    }

    if ((hopamp->Init.Mode) == OPAMP_PGA_MODE)
    {
      assert_param(IS_OPAMP_PGACONNECT(hopamp->Init.PgaConnect));
      assert_param(IS_OPAMP_PGA_GAIN(hopamp->Init.PgaGain));
    }

    assert_param(IS_OPAMP_TRIMMING(hopamp->Init.UserTrimming));
    if ((hopamp->Init.UserTrimming) == OPAMP_TRIMMING_USER)
    {
      assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueP));
      assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueN));
    }

    /* Init SYSCFG and the low level hardware to access opamp */
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    if (hopamp->State == HAL_OPAMP_STATE_RESET)
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

    /* Set OPAMP parameters */
    /*     Set  bits according to hopamp->hopamp->Init.Mode value                                 */
    /*     Set  bits according to hopamp->hopamp->Init.InvertingInput value                       */
    /*     Set  bits according to hopamp->hopamp->Init.NonInvertingInput value                    */
    /*     Set  bits according to hopamp->hopamp->Init.InternalOutput value                       */
    /*     Set  bits according to hopamp->hopamp->Init.TimerControlledMuxmode value               */
    /*     Set  bits according to hopamp->hopamp->Init.InvertingInputSecondary  value             */
    /*     Set  bits according to hopamp->hopamp->Init.NonInvertingInputSecondary value           */
    /*     Set  bits according to hopamp->hopamp->Init.PgaConnect value                           */
    /*     Set  bits according to hopamp->hopamp->Init.PgaGain value                              */
    /*     Set  bits according to hopamp->hopamp->Init.UserTrimming value                         */
    /*     Set  bits according to hopamp->hopamp->Init.TrimmingValueP value                       */
    /*     Set  bits according to hopamp->hopamp->Init.TrimmingValueN value                       */


    /* check if OPAMP_PGA_MODE & in Follower mode */
    /*   - InvertingInput                         */
    /* is Not Applicable                          */

    if ((hopamp->Init.Mode == OPAMP_PGA_MODE) || (hopamp->Init.Mode == OPAMP_FOLLOWER_MODE))
    {
      /* Update User Trim config first to be able to modify trimming value afterwards */
      MODIFY_REG(hopamp->Instance->CSR,
                 OPAMP_CSR_USERTRIM,
                 hopamp->Init.UserTrimming);
      MODIFY_REG(hopamp->Instance->CSR,
                 OPAMP_CSR_UPDATE_PARAMETERS_INIT_MASK,
                 hopamp->Init.PowerMode |
                 hopamp->Init.Mode |
                 hopamp->Init.NonInvertingInput |
                 ((hopamp->Init.InternalOutput == ENABLE) ? OPAMP_CSR_OPAMPINTEN : 0UL) |
                 hopamp->Init.PgaConnect |
                 hopamp->Init.PgaGain |
                 (hopamp->Init.TrimmingValueP << OPAMP_INPUT_NONINVERTING) |
                 (hopamp->Init.TrimmingValueN << OPAMP_INPUT_INVERTING));
    }
    else /* OPAMP_STANDALONE_MODE */
    {
      /* Update User Trim config first to be able to modify trimming value afterwards */
      MODIFY_REG(hopamp->Instance->CSR,
                 OPAMP_CSR_USERTRIM,
                 hopamp->Init.UserTrimming);
      MODIFY_REG(hopamp->Instance->CSR,
                 OPAMP_CSR_UPDATE_PARAMETERS_INIT_MASK,
                 hopamp->Init.PowerMode |
                 hopamp->Init.Mode |
                 hopamp->Init.InvertingInput    |
                 hopamp->Init.NonInvertingInput |
                 ((hopamp->Init.InternalOutput == ENABLE) ? OPAMP_CSR_OPAMPINTEN : 0UL) |
                 hopamp->Init.PgaConnect |
                 hopamp->Init.PgaGain |
                 (hopamp->Init.TrimmingValueP << OPAMP_INPUT_NONINVERTING) |
                 (hopamp->Init.TrimmingValueN << OPAMP_INPUT_INVERTING));
    }

    if ((READ_BIT(hopamp->Instance->TCMR, OPAMP_TCMR_LOCK)) == 0UL)
    {
      MODIFY_REG(hopamp->Instance->TCMR,
                 OPAMP_TCMR_UPDATE_PARAMETERS_INIT_MASK,
                 hopamp->Init.TimerControlledMuxmode |
                 hopamp->Init.InvertingInputSecondary  |
                 hopamp->Init.NonInvertingInputSecondary);
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
  * @brief  DeInitializes the OPAMP peripheral
  * @note   Deinitialization can't be performed if the OPAMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_DeInit(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* DeInit not allowed if calibration is ongoing */
  if (hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    /* Set OPAMP_CSR register to reset value */
    WRITE_REG(hopamp->Instance->CSR, OPAMP_CSR_RESET_VALUE);

    /* DeInit the low level hardware: GPIO, CLOCK and NVIC */
    /* When OPAMP is locked, unlocking can be achieved thanks to */
    /* __HAL_RCC_SYSCFG_CLK_DISABLE() call within HAL_OPAMP_MspDeInit */
    /* Note that __HAL_RCC_SYSCFG_CLK_DISABLE() also disables comparator */

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
    if (hopamp->MspDeInitCallback == NULL)
    {
      hopamp->MspDeInitCallback = HAL_OPAMP_MspDeInit;
    }
    /* DeInit the low level hardware */
    hopamp->MspDeInitCallback(hopamp);
#else
    HAL_OPAMP_MspDeInit(hopamp);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

    if (OPAMP_CSR_RESET_VALUE == (hopamp->Instance->CSR & OPAMP_CSR_RESET_CHECK_MASK))
    {
      /* Update the OPAMP state */
      hopamp->State = HAL_OPAMP_STATE_RESET;
    }
    else /* RESET STATE */
    {
      /* DeInit not complete */
      /* It can be the case if OPAMP was formerly locked */
      status = HAL_ERROR;

      /* The OPAMP state is NOT updated */
    }

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
            the HAL_OPAMP_MspInit could be implemented in the user file
   */

  /* Example */
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
            the HAL_OPAMP_MspDeInit could be implemented in the user file
   */

}

/**
  * @}
  */


/** @defgroup OPAMP_Exported_Functions_Group2 Input and Output operation functions
  *  @brief   Data transfers functions
  *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the OPAMP data
    transfers.

@endverbatim
  * @{
  */

/**
  * @brief  Start the opamp
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_OPAMP_Start(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  if (hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    if (hopamp->State == HAL_OPAMP_STATE_READY)
    {
      /* Enable the selected opamp */
      SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);

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
  * @brief  Stop the opamp
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Stop(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  /* Check if OPAMP calibration ongoing */
  if (hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    status = HAL_ERROR;
  }
  else if (hopamp->State == HAL_OPAMP_STATE_CALIBBUSY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    if (hopamp->State == HAL_OPAMP_STATE_BUSY)
    {
      /* Disable the selected opamp */
      CLEAR_BIT(hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);

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
  * @brief  Run the self calibration of one OPAMP
  * @note   Calibration is performed in the mode specified in OPAMP init
  *         structure (mode normal or high-speed).
  * @param  hopamp handle
  * @retval Updated offset trimming values (PMOS & NMOS), user trimming is enabled
  * @retval HAL status
  * @note   Calibration runs about 25 ms.
  */

HAL_StatusTypeDef HAL_OPAMP_SelfCalibrate(OPAMP_HandleTypeDef *hopamp)
{

  HAL_StatusTypeDef status = HAL_OK;

  uint32_t trimmingvaluen;
  uint32_t trimmingvaluep;
  uint32_t delta;

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  if (hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    status = HAL_ERROR;
  }
  else
  {

    /* Check if OPAMP in calibration mode and calibration not yet enable */
    if (hopamp->State ==  HAL_OPAMP_STATE_READY)
    {
      /* Check the parameter */
      assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

      /* Set Calibration mode */
      /* Non-inverting input connected to calibration reference voltage. */
      SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_FORCEVP);

      /*  user trimming values are used for offset calibration */
      SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_USERTRIM);

      /* Enable calibration */
      SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_CALON);

      /* 1st calibration - N */
      /* Select 90% VREF */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);

      /* Enable the selected opamp */
      SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);

      /* Init trimming counter */
      /* Medium value */
      trimmingvaluen = 16UL;
      delta = 8UL;

      while (delta != 0UL)
      {
        /* Set candidate trimming */
        MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen << OPAMP_INPUT_INVERTING);

        /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
        /* Offset trim time: during calibration, minimum time needed between */
        /* two steps to have 1 mV accuracy */
        HAL_Delay(2);

        if ((hopamp->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
        {
          /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
          trimmingvaluen += delta;
        }
        else
        {
          /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
          trimmingvaluen -= delta;
        }

        delta >>= 1;
      }

      /* Still need to check if righ calibration is current value or un step below */
      /* Indeed the first value that causes the OUTCAL bit to change from 1 to 0  */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen << OPAMP_INPUT_INVERTING);

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(2);

      if ((hopamp->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is actually one value more */
        trimmingvaluen++;
        /* Set right trimming */
        MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen << OPAMP_INPUT_INVERTING);
      }

      /* 2nd calibration - P */
      /* Select 10% VREF */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);

      /* Init trimming counter */
      /* Medium value */
      trimmingvaluep = 16UL;
      delta = 8UL;

      while (delta != 0UL)
      {
        /* Set candidate trimming */
        MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep << OPAMP_INPUT_NONINVERTING);

        /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
        /* Offset trim time: during calibration, minimum time needed between */
        /* two steps to have 1 mV accuracy */
        HAL_Delay(2);

        if ((hopamp->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
        {
          /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
          trimmingvaluep += delta;
        }
        else
        {
          trimmingvaluep -= delta;
        }

        delta >>= 1;
      }

      /* Still need to check if righ calibration is current value or un step below */
      /* Indeed the first value that causes the OUTCAL bit to change from 1 to 0U */
      /* Set candidate trimming */
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep << OPAMP_INPUT_NONINVERTING);

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(2);

      if ((hopamp->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is actually one value more */
        trimmingvaluep++;
        /* Set right trimming */
        MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep << OPAMP_INPUT_NONINVERTING);
      }

      /* Disable calibration */
      CLEAR_BIT(hopamp->Instance->CSR, OPAMP_CSR_CALON);

      /* Disable the OPAMP */
      CLEAR_BIT(hopamp->Instance->CSR, OPAMP_CSR_OPAMPxEN);

      /* Set operating mode  */
      /* Non-inverting input connected to calibration reference voltage. */
      CLEAR_BIT(hopamp->Instance->CSR, OPAMP_CSR_FORCEVP);

      /* Self calibration is successful  */
      /* Store calibration(user timming) results in init structure. */

      /* Write calibration result N */
      hopamp->Init.TrimmingValueN = trimmingvaluen;

      /* Write calibration result P */
      hopamp->Init.TrimmingValueP = trimmingvaluep;

      /* Select user timming mode */
      /* And updated with calibrated settings */
      hopamp->Init.UserTrimming = OPAMP_TRIMMING_USER;
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen << OPAMP_INPUT_INVERTING);
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
  * @brief  Lock the selected opamp configuration.
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
  if (hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (hopamp->State != HAL_OPAMP_STATE_BUSY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    /* Lock OPAMP */
    SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_LOCK);

    /* OPAMP state changed to locked */
    hopamp->State = HAL_OPAMP_STATE_BUSYLOCKED;
  }
  return status;
}

/**
  * @}
  */

/**
  * @brief  Lock the selected opamp timer controlled mux configuration.
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_LockTimerMux(OPAMP_HandleTypeDef *hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation                     */
  /* Check if OPAMP timer controlled mux is locked         */
  /* OPAMP timer controlled mux can be locked when enabled */
  /*   It is meaningless otherwise */
  if (hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  else if (hopamp->State == HAL_OPAMP_STATE_RESET)
  {
    status = HAL_ERROR;
  }
  else if (READ_BIT(hopamp->Instance->TCMR, OPAMP_TCMR_LOCK) == OPAMP_TCMR_LOCK)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

    /* Lock OPAMP */
    SET_BIT(hopamp->Instance->TCMR, OPAMP_TCMR_LOCK);
  }
  return status;
}

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
    This subsection permit to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Return the OPAMP state
  * @param  hopamp OPAMP handle
  * @retval HAL state
  */
HAL_OPAMP_StateTypeDef HAL_OPAMP_GetState(OPAMP_HandleTypeDef *hopamp)
{
  /* Check the OPAMP handle allocation */
  if (hopamp == NULL)
  {
    return HAL_OPAMP_STATE_RESET;
  }

  /* Check the parameter */
  assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

  return hopamp->State;
}

/**
  * @brief  Return the OPAMP factory trimming value
  * @param  hopamp OPAMP handle
  * @param  trimmingoffset Trimming offset (P or N)
  * @retval Trimming value (P or N): range: 0->31
  *         or OPAMP_FACTORYTRIMMING_DUMMY if trimming value is not available
 */

OPAMP_TrimmingValueTypeDef HAL_OPAMP_GetTrimOffset(OPAMP_HandleTypeDef *hopamp, uint32_t trimmingoffset)
{
  uint32_t oldusertrimming = 0UL;
  OPAMP_TrimmingValueTypeDef  oldtrimmingvaluep = 0UL, oldtrimmingvaluen = 0UL, trimmingvalue;

  /* Check the OPAMP handle allocation */
  /* Value can be retrieved in HAL_OPAMP_STATE_READY state */
  if (hopamp == NULL)
  {
    return OPAMP_FACTORYTRIMMING_DUMMY;
  }
  else if (hopamp->State != HAL_OPAMP_STATE_READY)
  {
    return OPAMP_FACTORYTRIMMING_DUMMY;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
    assert_param(IS_OPAMP_FACTORYTRIMMING(trimmingoffset));

    /* Check the trimming mode */
    if ((READ_BIT(hopamp->Instance->CSR, OPAMP_CSR_USERTRIM)) != 0UL)
    {
      /* User trimming is used */
      oldusertrimming = OPAMP_TRIMMING_USER;
      /* Store the TrimmingValueP & TrimmingValueN */
      oldtrimmingvaluep = (hopamp->Instance->CSR & OPAMP_CSR_TRIMOFFSETP) >> OPAMP_INPUT_NONINVERTING;
      oldtrimmingvaluen = (hopamp->Instance->CSR & OPAMP_CSR_TRIMOFFSETN) >> OPAMP_INPUT_INVERTING;
    }

    /* Set factory timming mode */
    CLEAR_BIT(hopamp->Instance->CSR, OPAMP_CSR_USERTRIM);

    /* Get factory trimming  */
    if (trimmingoffset == OPAMP_FACTORYTRIMMING_P)
    {
      /* Return TrimOffsetP */
      trimmingvalue = ((hopamp->Instance->CSR & OPAMP_CSR_TRIMOFFSETP) >> OPAMP_INPUT_NONINVERTING);
    }
    else
    {
      /* Return TrimOffsetN */
      trimmingvalue = ((hopamp->Instance->CSR & OPAMP_CSR_TRIMOFFSETN) >> OPAMP_INPUT_INVERTING);
    }

    /* Restore user trimming configuration if it was formerly set */
    /* Check if user trimming was used */
    if (oldusertrimming == OPAMP_TRIMMING_USER)
    {
      /* Restore user trimming */
      SET_BIT(hopamp->Instance->CSR, OPAMP_CSR_USERTRIM);
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, oldtrimmingvaluep << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, oldtrimmingvaluen << OPAMP_INPUT_INVERTING);
    }
  }
  return trimmingvalue;
}
/**
  * @}
  */

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User OPAMP Callback
  *         To be used instead of the weak (surcharged) predefined callback
  * @param hopamp : OPAMP handle
  * @param CallbackID : ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_OPAMP_MSP_INIT_CB_ID       OPAMP MspInit callback ID
  *          @arg @ref HAL_OPAMP_MSP_DEINIT_CB_ID     OPAMP MspDeInit callback ID
  * @param pCallback : pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_OPAMP_RegisterCallback(OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackId,
                                             pOPAMP_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    return HAL_ERROR;
  }

  /* Process locked */
  __HAL_LOCK(hopamp);

  if (hopamp->State == HAL_OPAMP_STATE_READY)
  {
    switch (CallbackId)
    {
      case HAL_OPAMP_MSP_INIT_CB_ID :
        hopamp->MspInitCallback = pCallback;
        break;
      case HAL_OPAMP_MSP_DEINIT_CB_ID :
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
      case HAL_OPAMP_MSP_INIT_CB_ID :
        hopamp->MspInitCallback = pCallback;
        break;
      case HAL_OPAMP_MSP_DEINIT_CB_ID :
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
  *         OPAMP Callback is redirected to the weak (surcharged) predefined callback
  * @param hopamp : OPAMP handle
  * @param CallbackID : ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_OPAMP_MSP_INIT_CB_ID              OPAMP MSP Init Callback ID
  *          @arg @ref HAL_OPAMP_MSP_DEINIT_CB_ID            OPAMP MSP DeInit Callback ID
  *          @arg @ref HAL_OPAMP_ALL_CB_ID                   OPAMP All Callbacks
  * @retval status
  */

HAL_StatusTypeDef HAL_OPAMP_UnRegisterCallback(OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackId)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hopamp);

  if (hopamp->State == HAL_OPAMP_STATE_READY)
  {
    switch (CallbackId)
    {
      case HAL_OPAMP_MSP_INIT_CB_ID :
        hopamp->MspInitCallback = HAL_OPAMP_MspInit;
        break;
      case HAL_OPAMP_MSP_DEINIT_CB_ID :
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
      case HAL_OPAMP_MSP_INIT_CB_ID :
        hopamp->MspInitCallback = HAL_OPAMP_MspInit;
        break;
      case HAL_OPAMP_MSP_DEINIT_CB_ID :
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

/**
  * @}
  */

#endif /* HAL_OPAMP_MODULE_ENABLED */
/**
  * @}
  */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
