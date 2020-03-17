/**
  ******************************************************************************
  * @file    stm32l1xx_hal_opamp.c
  * @author  MCD Application Team
  * @brief   OPAMP HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the operational amplifier(s) peripheral:
  *           + OPAMP configuration
  *           + OPAMP calibration
  *          Thanks to
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *         
  @verbatim
================================================================================
          ##### OPAMP Peripheral Features #####
================================================================================
  [..] The device integrates up to 3 operational amplifiers OPAMP1, OPAMP2,
       OPAMP3 (OPAMP3 availability depends on device category)
       
       (#) The OPAMP(s) provide(s) several exclusive running modes.
       (++) Standalone mode
       (++) Follower mode

       (#) All OPAMP (same for all OPAMPs) can operate in
       (++) Either Low range (VDDA < 2.4V) power supply
       (++) Or High range (VDDA > 2.4V) power supply

       (#) Each OPAMP(s) can be configured in normal and low power mode.

       (#) The OPAMP(s) provide(s) calibration capabilities.  
       (++) Calibration aims at correcting some offset for running mode.
       (++) The OPAMP uses either factory calibration settings OR user defined 
           calibration (trimming) settings (i.e. trimming mode).
       (++) The user defined settings can be figured out using self calibration 
           handled by HAL_OPAMP_SelfCalibrate, HAL_OPAMPEx_SelfCalibrateAll
       (++) HAL_OPAMP_SelfCalibrate:
       (+++) Runs automatically the calibration in 2 steps: for transistors 
            differential pair high (PMOS) or low (NMOS)
       (+++) Enables the user trimming mode
       (+++) Updates the init structure with trimming values with fresh calibration 
            results.
            The user may store the calibration results for larger 
            (ex monitoring the trimming as a function of temperature 
            for instance)
       (+++) For devices having several OPAMPs, HAL_OPAMPEx_SelfCalibrateAll
            runs calibration of all OPAMPs in parallel to save search time.
            
       (#) Running mode: Standalone mode 
       (++) Gain is set externally (gain depends on external loads).
       (++) Follower mode also possible externally by connecting the inverting input to
           the output.
       
       (#) Running mode: Follower mode
       (++) No Inverting Input is connected.
       (++) The OPAMP(s) output(s) are internally connected to inverting input.
        
            ##### How to use this driver #####
================================================================================
  [..] 

    *** Power supply range ***
    ============================================
    [..] To run in low power mode:

      (#) Configure the OPAMP using HAL_OPAMP_Init() function:
      (++) Select OPAMP_POWERSUPPLY_LOW (VDDA lower than 2.4V)
      (++) Otherwise select OPAMP_POWERSUPPLY_HIGH (VDDA higher than 2.4V)

    *** Low / normal power mode ***
    ============================================
    [..] To run in low power mode:

      (#) Configure the OPAMP using HAL_OPAMP_Init() function:
      (++) Select OPAMP_POWERMODE_LOWPOWER
      (++) Otherwise select OPAMP_POWERMODE_NORMAL

    *** Calibration ***
    ============================================
    [..] To run the OPAMP calibration self calibration:

      (#) Start calibration using HAL_OPAMP_SelfCalibrate. 
           Store the calibration results.

    *** Running mode ***
    ============================================
      
    [..] To use the OPAMP, perform the following steps:
            
      (#) Fill in the HAL_OPAMP_MspInit() to
      (++) Enable the OPAMP Peripheral clock using macro __HAL_RCC_OPAMP_CLK_ENABLE()
      (++) Configure the OPAMP input AND output in analog mode using
           HAL_GPIO_Init() to map the OPAMP output to the GPIO pin.

      (#) Registrate Callbacks
      (++) The compilation define  USE_HAL_OPAMP_REGISTER_CALLBACKS when set to 1
           allows the user to configure dynamically the driver callbacks.

      (++) Use Functions @ref HAL_OPAMP_RegisterCallback() to register a user callback,
           it allows to register following callbacks:
      (+++) MspInitCallback         : OPAMP MspInit.
      (+++) MspDeInitCallback       : OPAMP MspFeInit.
           This function takes as parameters the HAL peripheral handle, the Callback ID
           and a pointer to the user callback function.

      (++) Use function @ref HAL_OPAMP_UnRegisterCallback() to reset a callback to the default
           weak (surcharged) function. It allows to reset following callbacks:
      (+++) MspInitCallback         : OPAMP MspInit.
      (+++) MspDeInitCallback       : OPAMP MspdeInit.
      (+++) All Callbacks
  
      (#) Configure the OPAMP using HAL_OPAMP_Init() function:
      (++) Select the mode
      (++) Select the inverting input
      (++) Select the non-inverting input 
      (++) Select either factory or user defined trimming mode.
      (++) If the user-defined trimming mode is enabled, select PMOS & NMOS trimming values
          (typically values set by HAL_OPAMP_SelfCalibrate function).
      
      (#) Enable the OPAMP using HAL_OPAMP_Start() function.
           
      (#) Disable the OPAMP using HAL_OPAMP_Stop() function.
      
      (#) Lock the OPAMP in running mode using HAL_OPAMP_Lock() function.
          Caution: On STM32L1, HAL OPAMP lock is software lock only (not 
          hardware lock as on some other STM32 devices)

      (#) If needed, unlock the OPAMP using HAL_OPAMPEx_Unlock() function.

    *** Running mode: change of configuration while OPAMP ON  ***
    ============================================
    [..] To Re-configure OPAMP when OPAMP is ON (change on the fly)
      (#) If needed, fill in the HAL_OPAMP_MspInit()
      (++) This is the case for instance if you wish to use new OPAMP I/O

      (#) Configure the OPAMP using HAL_OPAMP_Init() function:
      (++) As in configure case, select first the parameters you wish to modify.
      
      (#) Change from low power mode to normal power mode (& vice versa) requires  
          first HAL_OPAMP_DeInit() (force OPAMP OFF) and then HAL_OPAMP_Init(). 
          In other words, of OPAMP is ON, HAL_OPAMP_Init can NOT change power mode
          alone.

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
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
  Additionnal remark:
    The OPAMPs inverting input can be selected among the list shown by table below.
    The OPAMPs non inverting input can be selected among the list shown by table below.
       
    Table 1.  OPAMPs inverting/non-inverting inputs for STM32L1 devices:
    +--------------------------------------------------------------------------+
    |                | HAL param  |    OPAMP1    |    OPAMP2    |   OPAMP3(4)  |
    |                |   name     |              |              |              |
    |----------------|------------|--------------|--------------|--------------|
    |   Inverting    |    VM0     |     PA2      |     PA7      |     PC2      |
    |    input (1)   |    VM1     | VINM pin (2) | VINM pin (2) | VINM pin (2) |
    |----------------|------------|--------------|--------------|--------------|
    |  Non Inverting |    VP0     |     PA1      |     PA6      |     PC1      |
    |    input       | DAC_CH1 (3)|   DAC_CH1    |   DAC_CH1    |     ---      |
    |                | DAC_CH2 (3)|     ---      |   DAC_CH2    |   DAC_CH2    |
    +--------------------------------------------------------------------------+
    (1): NA in follower mode.
    (2): OPAMP input OPAMPx_VINM are dedicated OPAMP pins, their availability
         depends on device package.
    (3): DAC channels 1 and 2 are connected internally to OPAMP. Nevertheless,
         I/O pins connected to DAC can still be used as DAC output (pins PA4 
         and PA5).
    (4): OPAMP3 availability depends on device category.

    Table 2.  OPAMPs outputs for STM32L1 devices:
    +--------------------------------------------------------+
    |                 |   OPAMP1   |   OPAMP2   |  OPAMP3(4) |
    |-----------------|------------|------------|------------|
    | Output          |    PA3     |    PB0     |    PC3     |
    +--------------------------------------------------------+
    (4) : OPAMP3 availability depends on device category
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
    
/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup OPAMP OPAMP
  * @brief OPAMP module driver
  * @{
  */

#ifdef HAL_OPAMP_MODULE_ENABLED

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L151xDX) || defined (STM32L152xE) || defined (STM32L152xDX) || defined (STM32L162xE) || defined (STM32L162xDX) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
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
   [..]  This section provides functions allowing to:
 
@endverbatim
  * @{
  */

/**
  * @brief  Initializes the OPAMP according to the specified
  *         parameters in the OPAMP_InitTypeDef and create the associated handle.
  * @note   If the selected opamp is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Init(OPAMP_HandleTypeDef* hopamp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmp_csr;       /* Temporary variable to update register CSR, except bits ANAWSSELx, S7SEL2, OPA_RANGE, OPAxCALOUT */
  
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
    assert_param(IS_OPAMP_POWER_SUPPLY_RANGE(hopamp->Init.PowerSupplyRange));
    assert_param(IS_OPAMP_POWERMODE(hopamp->Init.PowerMode));
    assert_param(IS_OPAMP_FUNCTIONAL_NORMALMODE(hopamp->Init.Mode));
    assert_param(IS_OPAMP_NONINVERTING_INPUT_CHECK_INSTANCE(hopamp, hopamp->Init.NonInvertingInput));
    assert_param(IS_OPAMP_TRIMMING(hopamp->Init.UserTrimming));

    if(hopamp->State == HAL_OPAMP_STATE_RESET)
    {  
#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
    if(hopamp->MspInitCallback == NULL)
    {
      hopamp->MspInitCallback               = HAL_OPAMP_MspInit;
    } 
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */
    }


    if (hopamp->Init.Mode != OPAMP_FOLLOWER_MODE)
    {
      assert_param(IS_OPAMP_INVERTING_INPUT(hopamp->Init.InvertingInput));
    }
    
    if (hopamp->Init.UserTrimming == OPAMP_TRIMMING_USER)
    {
      if (hopamp->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueP));
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueN));
      }
      else
      {
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValuePLowPower));
        assert_param(IS_OPAMP_TRIMMINGVALUE(hopamp->Init.TrimmingValueNLowPower));
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

    /* Set OPAMP parameters                                                   */
    /* - Set internal switches in function of:                                */
    /*   - OPAMP selected mode: standalone or follower.                       */
    /*   - Non-inverting input connection                                     */
    /*   - Inverting input connection                                         */
    /* - Set power supply range                                               */
    /* - Set power mode and associated calibration parameters                 */
    
    /* Get OPAMP CSR register into temporary variable */
    /* Note: OPAMP register CSR is written directly, independently of OPAMP   */
    /*       instance, because all OPAMP settings are dispatched in the same  */
    /*       register.                                                        */
    /*       Settings of bits for each OPAMP instances are managed case by    */
    /*       case using macro (OPAMP_CSR_S3SELX(), OPAMP_CSR_ANAWSELX(), ...) */
    tmp_csr = OPAMP->CSR;
    
    /* Open all switches on non-inverting input, inverting input and output   */
    /* feedback.                                                              */
    CLEAR_BIT(tmp_csr, OPAMP_CSR_ALL_SWITCHES(hopamp));
    
    /* Set internal switches in function of OPAMP mode selected: standalone   */
    /* or follower.                                                           */
    /* If follower mode is selected, feedback switch S3 is closed and         */
    /* inverting inputs switches are let opened.                              */
    /* If standalone mode is selected, feedback switch S3 is let opened and   */
    /* the selected inverting inputs switch is closed.                        */
    if (hopamp->Init.Mode == OPAMP_FOLLOWER_MODE)
    {
      /* Follower mode: Close switches S3 and SanB */
      SET_BIT(tmp_csr, OPAMP_CSR_S3SELX(hopamp));
    }
    else
    {
      /* Set internal switches in function of inverting input selected:       */
      /* Close switch to connect OPAMP inverting input to the selected        */
      /* input: dedicated IO pin or alternative IO pin available on some      */
      /* device packages.                                                     */
      if (hopamp->Init.InvertingInput == OPAMP_INVERTINGINPUT_IO0)
      {
        /* Close switch to connect OPAMP non-inverting input to               */
        /* dedicated IO pin low-leakage.                                      */
        SET_BIT(tmp_csr, OPAMP_CSR_S4SELX(hopamp));
      }
      else
      {
        /* Close switch to connect OPAMP inverting input to alternative       */
        /* IO pin available on some device packages.                          */
        SET_BIT(tmp_csr, OPAMP_CSR_ANAWSELX(hopamp));
      }
    }
    
    /* Set internal switches in function of non-inverting input selected:     */
    /* Close switch to connect OPAMP non-inverting input to the selected      */
    /* input: dedicated IO pin or DAC channel.                                */
    if (hopamp->Init.NonInvertingInput == OPAMP_NONINVERTINGINPUT_IO0)
    {
      /* Close switch to connect OPAMP non-inverting input to                 */
      /* dedicated IO pin low-leakage.                                        */
      SET_BIT(tmp_csr, OPAMP_CSR_S5SELX(hopamp));
    }
    else if (hopamp->Init.NonInvertingInput == OPAMP_NONINVERTINGINPUT_DAC_CH1)
    {
      
      /* Particular case for connection to DAC channel 1:                     */
      /* OPAMP_NONINVERTINGINPUT_DAC_CH1 available on OPAMP1 and OPAMP2 only  */
      /* (OPAMP3 availability depends on device category).                    */
      if ((hopamp->Instance == OPAMP1) || (hopamp->Instance == OPAMP2))
      {
        /* Close switch to connect OPAMP non-inverting input to               */
        /* DAC channel 1.                                                     */
        SET_BIT(tmp_csr, OPAMP_CSR_S6SELX(hopamp));
      }
      else
      {
        /* Set HAL status to error if another OPAMP instance as OPAMP1 or     */
        /* OPAMP2 is intended to be connected to DAC channel 2.               */
        status = HAL_ERROR;
      }
    }
    else /* if (hopamp->Init.NonInvertingInput ==                             */
         /*     OPAMP_NONINVERTINGINPUT_DAC_CH2  )                            */
    {
      /* Particular case for connection to DAC channel 2:                     */
      /* OPAMP_NONINVERTINGINPUT_DAC_CH2 available on OPAMP2 and OPAMP3 only  */
      /* (OPAMP3 availability depends on device category).                    */
      if (hopamp->Instance == OPAMP2)
      {
        /* Close switch to connect OPAMP non-inverting input to               */
        /* DAC channel 2.                                                     */
        SET_BIT(tmp_csr, OPAMP_CSR_S7SEL2);
      }
      /* If OPAMP3 is selected (if available) */
      else if (hopamp->Instance != OPAMP1)
      {
        /* Close switch to connect OPAMP non-inverting input to               */
        /* DAC channel 2.                                                     */
        SET_BIT(tmp_csr, OPAMP_CSR_S6SELX(hopamp));
      }
      else
      {
        /* Set HAL status to error if another OPAMP instance as OPAMP2 or     */
        /* OPAMP3 (if available) is intended to be connected to DAC channel 2.*/
        status = HAL_ERROR;
      }
    }
    
    /* Continue OPAMP configuration if settings of switches are correct */
    if (status != HAL_ERROR)
    {
      /* Set power mode and associated calibration parameters */
      if (hopamp->Init.PowerMode != OPAMP_POWERMODE_LOWPOWER)
      {
        /* Set normal mode */
        CLEAR_BIT(tmp_csr, OPAMP_CSR_OPAXLPM(hopamp));
        
        if (hopamp->Init.UserTrimming == OPAMP_TRIMMING_USER)
        {
          /* Set calibration mode (factory or user) and values for            */
          /* transistors differential pair high (PMOS) and low (NMOS) for     */
          /* normal mode.                                                     */
          MODIFY_REG(OPAMP->OTR, OPAMP_OTR_OT_USER                                                                     |
                                 OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_N, OPAMP_TRIM_VALUE_MASK)       |
                                 OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_P, OPAMP_TRIM_VALUE_MASK)        ,
                                 hopamp->Init.UserTrimming                                                             |
                                 OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_N, hopamp->Init.TrimmingValueN) |
                                 OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_P, hopamp->Init.TrimmingValueP)  );
        }
        else
        {
          /* Set calibration mode to factory */
          CLEAR_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);
        }
        
      }
      else
      {
        /* Set low power mode */
        SET_BIT(tmp_csr, OPAMP_CSR_OPAXLPM(hopamp));
        
        if (hopamp->Init.UserTrimming == OPAMP_TRIMMING_USER)
        {
          /* Set calibration mode to user trimming */
          SET_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);
          
          /* Set values for transistors differential pair high (PMOS) and low */
          /* (NMOS) for low power mode.                                       */
          MODIFY_REG(OPAMP->LPOTR, OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_N, OPAMP_TRIM_VALUE_MASK)               |
                                   OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_P, OPAMP_TRIM_VALUE_MASK)                ,
                                   OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_N, hopamp->Init.TrimmingValueNLowPower) |
                                   OPAMP_OFFSET_TRIM_SET(hopamp, OPAMP_FACTORYTRIMMING_P, hopamp->Init.TrimmingValuePLowPower)  );
        }
        else
        {
          /* Set calibration mode to factory trimming */
          CLEAR_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);
        }
        
      }
      
      
      /* Configure the power supply range */
      MODIFY_REG(tmp_csr, OPAMP_CSR_AOP_RANGE,
                          hopamp->Init.PowerSupplyRange);
      
      /* Set OPAMP CSR register from temporary variable */
      /* This allows to apply all changes on one time, in case of update on   */
      /* the fly with OPAMP previously set and running:                       */
      /*  - to avoid hazardous transient switches settings (risk of short     */
      /*    circuit)                                                          */
      /*  - to avoid interruption of input signal                             */
      OPAMP->CSR = tmp_csr;

                
      /* Update the OPAMP state */
      /* If coming from state reset: Update from state RESET to state READY */
      if (hopamp->State == HAL_OPAMP_STATE_RESET)
      {
        hopamp->State = HAL_OPAMP_STATE_READY;
      }
      /* else: OPAMP state remains READY or BUSY state (no update) */
    }
  }
  
  return status;
}

/**
  * @brief  DeInitializes the OPAMP peripheral 
  * @note   Deinitialization can be performed if the OPAMP configuration is locked.
  *         (the OPAMP lock is SW in STM32L1)
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_DeInit(OPAMP_HandleTypeDef* hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Check the OPAMP handle allocation */
  /* DeInit not allowed if calibration is ongoing */
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
    
    /* Disable the selected opamp */
    SET_BIT (OPAMP->CSR, OPAMP_CSR_OPAXPD(hopamp));
    
    /* Open all switches on non-inverting input, inverting input and output   */
    /* feedback.                                                              */
    /* Note: OPAMP register CSR is written directly, independently of OPAMP   */
    /*       instance, because all OPAMP settings are dispatched in the same  */
    /*       register.                                                        */
    /*       Settings of bits for each OPAMP instances are managed case by    */
    /*       case using macro (OPAMP_CSR_S3SELX(), OPAMP_CSR_ANAWSELX(), ...) */
    CLEAR_BIT(OPAMP->CSR, OPAMP_CSR_ALL_SWITCHES(hopamp));

    /* Note: Registers and bits shared with other OPAMP instances are kept    */
    /*       unchanged, to not impact other OPAMP while operating on the      */
    /*       selected OPAMP.                                                  */
    /*       Unchanged: bit OPAMP_OTR_OT_USER (parameter "UserTrimming")      */
    /*                  bit OPAMP_CSR_AOP_RANGE (parameter "PowerSupplyRange")*/

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
  if(hopamp->MspDeInitCallback == NULL)
  {
    hopamp->MspDeInitCallback = HAL_OPAMP_MspDeInit;
  }
  /* DeInit the low level hardware */
  hopamp->MspDeInitCallback(hopamp);
#else
    /* DeInit the low level hardware: GPIO, CLOCK and NVIC */
    HAL_OPAMP_MspDeInit(hopamp);
#endif /* USE_HAL_OPAMP_REGISTER_CALLBACKS */

    /* Update the OPAMP state*/
    hopamp->State = HAL_OPAMP_STATE_RESET;
  }
  
  /* Process unlocked */
  __HAL_UNLOCK(hopamp);
  
  return status;
}

/**
  * @brief  Initialize the OPAMP MSP.
  * @param  hopamp OPAMP handle
  * @retval None
  */
__weak void HAL_OPAMP_MspInit(OPAMP_HandleTypeDef* hopamp)
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
__weak void HAL_OPAMP_MspDeInit(OPAMP_HandleTypeDef* hopamp)
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
  * @brief   IO operation functions 
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

HAL_StatusTypeDef HAL_OPAMP_Start(OPAMP_HandleTypeDef* hopamp)
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
      CLEAR_BIT (OPAMP->CSR, OPAMP_CSR_OPAXPD(hopamp));
      
      /* Update the OPAMP state */
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
HAL_StatusTypeDef HAL_OPAMP_Stop(OPAMP_HandleTypeDef* hopamp)
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
      SET_BIT (OPAMP->CSR, OPAMP_CSR_OPAXPD(hopamp));
      
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
  * @note   Trimming values (PMOS & NMOS) are updated and user trimming is 
  *         enabled if calibration is succesful.
  * @note   Calibration is performed in the mode specified in OPAMP init
  *         structure (mode normal or low-power). To perform calibration for
  *         both modes, repeat this function twice after OPAMP init structure
  *         accordingly updated.
  * @note   Calibration runs about 10 ms.
  * @param  hopamp handle
  * @retval Updated offset trimming values (PMOS & NMOS), user trimming is enabled
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_SelfCalibrate(OPAMP_HandleTypeDef* hopamp)
{ 
  HAL_StatusTypeDef status = HAL_OK;
  
  uint32_t* opamp_trimmingvalue;
  uint32_t opamp_trimmingvaluen = 0;
  uint32_t opamp_trimmingvaluep = 0;
  
  uint32_t trimming_diff_pair;               /* Selection of differential transistors pair high or low */

  __IO uint32_t* tmp_opamp_reg_trimming;     /* Selection of register of trimming depending on power mode: OTR or LPOTR */
  uint32_t tmp_opamp_otr_otuser;             /* Selection of bit OPAMP_OTR_OT_USER depending on trimming register pointed: OTR or LPOTR */

  uint32_t tmp_Opaxcalout_DefaultSate;       /* Bit OPAMP_CSR_OPAXCALOUT default state when trimming value is 00000b. Used to detect the bit toggling */

  uint32_t tmp_OpaxSwitchesContextBackup;
  
  uint8_t trimming_diff_pair_iteration_count;          /* For calibration loop algorithm: to repeat the calibration loop for both differential transistors pair high and low */
  uint8_t delta;                                       /* For calibration loop algorithm: Variable for dichotomy steps value */
  uint8_t final_step_check = 0x0U;                        /* For calibration loop algorithm: Flag for additional check of last trimming step */
  
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
    if(hopamp->State == HAL_OPAMP_STATE_READY)
    {
      /* Check the parameter */
      assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
      assert_param(IS_OPAMP_POWERMODE(hopamp->Init.PowerMode));
      
      /* Update OPAMP state */
      hopamp->State = HAL_OPAMP_STATE_CALIBBUSY;
      
      /* Backup of switches configuration to restore it at the end of the     */
      /* calibration.                                                         */
      tmp_OpaxSwitchesContextBackup = READ_BIT(OPAMP->CSR, OPAMP_CSR_ALL_SWITCHES(hopamp));
  
      /* Open all switches on non-inverting input, inverting input and output */
      /* feedback.                                                            */
      CLEAR_BIT(OPAMP->CSR, OPAMP_CSR_ALL_SWITCHES(hopamp));

      /* Set calibration mode to user programmed trimming values */
      SET_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);

      
      /* Select trimming settings depending on power mode */
      if (hopamp->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        tmp_opamp_otr_otuser = OPAMP_OTR_OT_USER;
        tmp_opamp_reg_trimming = &OPAMP->OTR;
      }
      else
      {
        tmp_opamp_otr_otuser = 0x00000000U;
        tmp_opamp_reg_trimming = &OPAMP->LPOTR;
      }

      
      /* Enable the selected opamp */
      CLEAR_BIT (OPAMP->CSR, OPAMP_CSR_OPAXPD(hopamp));

      /* Perform trimming for both differential transistors pair high and low */
      for (trimming_diff_pair_iteration_count = 0U; trimming_diff_pair_iteration_count <=1U; trimming_diff_pair_iteration_count++)
      {
        if (trimming_diff_pair_iteration_count == 0U)
        {
          /* Calibration of transistors differential pair high (NMOS) */
          trimming_diff_pair = OPAMP_FACTORYTRIMMING_N;
          opamp_trimmingvalue = &opamp_trimmingvaluen;
          
          /* Set bit OPAMP_CSR_OPAXCALOUT default state when trimming value   */
          /* is 00000b. Used to detect the bit toggling during trimming.      */
          tmp_Opaxcalout_DefaultSate = 0U;

          /* Enable calibration for N differential pair */
          MODIFY_REG(OPAMP->CSR, OPAMP_CSR_OPAXCAL_L(hopamp),
                                 OPAMP_CSR_OPAXCAL_H(hopamp) );
        }
        else /* (trimming_diff_pair_iteration_count == 1) */
        {
          /* Calibration of transistors differential pair low (PMOS) */
          trimming_diff_pair = OPAMP_FACTORYTRIMMING_P;
          opamp_trimmingvalue = &opamp_trimmingvaluep;
          
          /* Set bit OPAMP_CSR_OPAXCALOUT default state when trimming value   */
          /* is 00000b. Used to detect the bit toggling during trimming.      */
          tmp_Opaxcalout_DefaultSate = OPAMP_CSR_OPAXCALOUT(hopamp);
          
          /* Enable calibration for P differential pair */
          MODIFY_REG(OPAMP->CSR, OPAMP_CSR_OPAXCAL_H(hopamp),
                                 OPAMP_CSR_OPAXCAL_L(hopamp) );
        }
        
      
        /* Perform calibration parameter search by dichotomy sweep */
        /*  - Delta initial value 16: for 5 dichotomy steps: 16 for the       */
        /*    initial range, then successive delta sweeps (8, 4, 2, 1).       */
        /*    can extend the search range to +/- 15 units.                    */
        /*  - Trimming initial value 15: search range will go from 0 to 30    */
        /*    (Trimming value 31 is forbidden).                               */
        /* Note: After dichotomy sweep, the trimming result is determined.    */
        /*       However, the final trimming step is deduced from previous    */
        /*       trimming steps tested but is not effectively tested.         */
        /*       An additional test step (using variable "final_step_check")  */
        /*       allow to Test the final trimming step.                       */
        *opamp_trimmingvalue = 15U;
        delta = 16U;

        while ((delta != 0U) || (final_step_check == 1U))
        {
          /* Set candidate trimming */
          MODIFY_REG(*tmp_opamp_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                              OPAMP_OFFSET_TRIM_SET(hopamp, trimming_diff_pair, *opamp_trimmingvalue) | tmp_opamp_otr_otuser);
          
          /* Offset trimming time: during calibration, minimum time needed    */
          /* between two steps to have 1 mV accuracy.                         */
          HAL_Delay(OPAMP_TRIMMING_DELAY);

          /* Set flag for additional check of last trimming step equal to     */
          /* dichotomy step before its division by 2 (equivalent to previous  */
          /* value of dichotomy step).                                        */
          final_step_check = delta;
          
          /* Divide range by 2 to continue dichotomy sweep */
          delta >>= 1;
            
          /* Set trimming values for next iteration in function of trimming   */
          /* result toggle (versus initial state).                            */
          /* Note: on the last trimming loop, delta is equal to 0 and         */
          /*       therefore has no effect.                                   */
          if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp)) != tmp_Opaxcalout_DefaultSate)
          {
            /* If calibration output is has toggled, try lower trimming */
            *opamp_trimmingvalue -= delta;
          }
          else
          {
            /* If calibration output is has not toggled, try higher trimming */
            *opamp_trimmingvalue += delta;
          }

        }
        
        /* Check trimming result of the selected step and perform final fine  */
        /* trimming.                                                          */
        /*  - If calibration output is has toggled: the current step is       */
        /*    already optimized.                                              */
        /*  - If calibration output is has not toggled: the current step can  */
        /*    be optimized by incrementing it of one step.                    */
        if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp)) == tmp_Opaxcalout_DefaultSate)
        {
          *opamp_trimmingvalue += 1U;
          
          /* Set final fine trimming */
          MODIFY_REG(*tmp_opamp_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                              OPAMP_OFFSET_TRIM_SET(hopamp, trimming_diff_pair, *opamp_trimmingvalue) | tmp_opamp_otr_otuser);
        }
        
      }

      
      /* Disable calibration for P and N differential pairs */
      /* Disable the selected opamp */
      CLEAR_BIT (OPAMP->CSR, (OPAMP_CSR_OPAXCAL_H(hopamp) | 
                              OPAMP_CSR_OPAXCAL_L(hopamp) |
                              OPAMP_CSR_OPAXPD(hopamp))    );

      /* Backup of switches configuration to restore it at the end of the     */
      /* calibration.                                                         */
      SET_BIT(OPAMP->CSR, tmp_OpaxSwitchesContextBackup);
      
      /* Self calibration is successful */
      /* Store calibration (user trimming) results in init structure. */
      
      /* Set user trimming mode */  
      hopamp->Init.UserTrimming = OPAMP_TRIMMING_USER;
      
      /* Affect calibration parameters depending on mode normal/low power */
      if (hopamp->Init.PowerMode != OPAMP_POWERMODE_LOWPOWER)
      {
        /* Write calibration result N */
        hopamp->Init.TrimmingValueN = opamp_trimmingvaluen;
        /* Write calibration result P */
        hopamp->Init.TrimmingValueP = opamp_trimmingvaluep;
      }
      else
      {
        /* Write calibration result N */
        hopamp->Init.TrimmingValueNLowPower = opamp_trimmingvaluen;
        /* Write calibration result P */
        hopamp->Init.TrimmingValuePLowPower = opamp_trimmingvaluep;
      }
      
      /* Update OPAMP state */
      hopamp->State = HAL_OPAMP_STATE_READY;

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
  *         Caution: On STM32L1, HAL OPAMP lock is software lock only
  *         (not hardware lock as available on some other STM32 devices)
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMP_Lock(OPAMP_HandleTypeDef* hopamp)
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
  else if(hopamp->State == HAL_OPAMP_STATE_BUSY)
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
  
   /* OPAMP state changed to locked */
    hopamp->State = HAL_OPAMP_STATE_BUSYLOCKED;
  }
  else
  {
    status = HAL_ERROR;
  }
  return status; 
}

/**
  * @brief  Return the OPAMP factory trimming value
  *         Caution: On STM32L1 OPAMP, user can retrieve factory trimming if 
  *                  OPAMP has never been set to user trimming before.
  *                  Therefore, this fonction must be called when OPAMP init  
  *                  parameter "UserTrimming" is set to trimming factory, 
  *                  and before OPAMP  calibration (function 
  *                  "HAL_OPAMP_SelfCalibrate()").
  *                  Otherwise, factory triming value cannot be retrieved and 
  *                  error status is returned.
  * @param  hopamp  OPAMP handle
  * @param  trimmingoffset  Trimming offset (P or N)
  *         This parameter must be a value of @ref OPAMP_FactoryTrimming
  * @note   Calibration parameter retrieved is corresponding to the mode 
  *         specified in OPAMP init structure (mode normal or low-power). 
  *         To retrieve calibration parameters for both modes, repeat this 
  *         function after OPAMP init structure accordingly updated.
  * @retval Trimming value (P or N) range: 0->31
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

  /* Check the OPAMP handle allocation */
  /* Value can be retrieved in HAL_OPAMP_STATE_READY state */
  if(hopamp->State == HAL_OPAMP_STATE_READY)
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));
    assert_param(IS_OPAMP_FACTORYTRIMMING(trimmingoffset));
    assert_param(IS_OPAMP_POWERMODE(hopamp->Init.PowerMode));
    
    /* Check the trimming mode */
    if (hopamp->Init.UserTrimming == OPAMP_TRIMMING_USER) 
    {
      /* This fonction must called when OPAMP init parameter "UserTrimming"   */
      /* is set to trimming factory, and before OPAMP calibration (function   */
      /* "HAL_OPAMP_SelfCalibrate()").                                        */
      /* Otherwise, factory triming value cannot be retrieved and error       */
      /* status is returned.                                                  */
      trimmingvalue = OPAMP_FACTORYTRIMMING_DUMMY;
    }
    else
    {
      /* Select trimming settings depending on power mode */
      if (hopamp->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        tmp_opamp_reg_trimming = &OPAMP->OTR;
      }
      else
      {
        tmp_opamp_reg_trimming = &OPAMP->LPOTR;
      }
      
      /* Get factory trimming  */
      trimmingvalue = ((*tmp_opamp_reg_trimming >> OPAMP_OFFSET_TRIM_BITSPOSITION(hopamp, trimmingoffset)) & OPAMP_TRIM_VALUE_MASK);
    }
  }
  else
  {
    return OPAMP_FACTORYTRIMMING_DUMMY;
  }  
  return trimmingvalue;
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
    This subsection permits to get in run-time the status of the peripheral.

@endverbatim
  * @{
  */

/**
  * @brief  Return the OPAMP handle state.
  * @param  hopamp OPAMP handle
  * @retval HAL state
  */
HAL_OPAMP_StateTypeDef HAL_OPAMP_GetState(OPAMP_HandleTypeDef* hopamp)
{
  /* Check the OPAMP handle allocation */
  if(hopamp == NULL)
  {
    return HAL_OPAMP_STATE_RESET;
  }

  /* Check the parameter */
  assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

  return hopamp->State;
}

#if (USE_HAL_OPAMP_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register a User OPAMP Callback
  *         To be used instead of the weak (surcharged) predefined callback 
  * @param hopamp OPAMP handle
  * @param CallbackID ID of the callback to be registered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_OPAMP_MSPINIT_CB_ID       OPAMP MspInit callback ID 
  *          @arg @ref HAL_OPAMP_MSPDEINIT_CB_ID     OPAMP MspDeInit callback ID  
  * @param pCallback pointer to the Callback function
  * @retval status
  */
HAL_StatusTypeDef HAL_OPAMP_RegisterCallback (OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackID, pOPAMP_CallbackTypeDef pCallback)
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
    switch (CallbackID)
    {
    case HAL_OPAMP_MSPINIT_CB_ID :
      hopamp->MspInitCallback = pCallback;
      break;
    case HAL_OPAMP_MSPDEINIT_CB_ID :
      hopamp->MspDeInitCallback = pCallback;
      break;
    default :
      /* Update the error code */
      // hopamp->ErrorCode |= HAL_OPAMP_ERROR_INVALID_CALLBACK; 
      /* update return status */
      status =  HAL_ERROR;
      break;
    }
  }
  else if (hopamp->State == HAL_OPAMP_STATE_RESET)
  {
    switch (CallbackID)
    {
    case HAL_OPAMP_MSPINIT_CB_ID :
      hopamp->MspInitCallback = pCallback;
      break;
    case HAL_OPAMP_MSPDEINIT_CB_ID :
      hopamp->MspDeInitCallback = pCallback;
      break;
    default :
      /* Update the error code */
      // hopamp->ErrorCode |= HAL_OPAMP_ERROR_INVALID_CALLBACK; 
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
  * @param hopamp OPAMP handle
  * @param CallbackID ID of the callback to be unregistered
  *        This parameter can be one of the following values:
  *          @arg @ref HAL_OPAMP_MSPINIT_CB_ID              OPAMP MSP Init Callback ID
  *          @arg @ref HAL_OPAMP_MSPDEINIT_CB_ID            OPAMP MSP DeInit Callback ID
  *          @arg @ref HAL_OPAMP_ALL_CB_ID                   OPAMP All Callbacks
  * @retval status
  */

HAL_StatusTypeDef HAL_OPAMP_UnRegisterCallback (OPAMP_HandleTypeDef *hopamp, HAL_OPAMP_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Process locked */
  __HAL_LOCK(hopamp);
  
  if(hopamp->State == HAL_OPAMP_STATE_READY)
  {
    switch (CallbackID)
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
    switch (CallbackID)
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

/**
  * @}
  */

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L151xDX || STM32L152xE || STM32L152xDX || STM32L162xE || STM32L162xDX || STM32L162xC || STM32L152xC || STM32L151xC */

#endif /* HAL_OPAMP_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
