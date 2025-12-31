/**
  ******************************************************************************
  * @file               ft32f4xx_lptim.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Serial peripheral interface (LPTIM):
  *                 + Initialization and Configuration
  *                 + Read CNT/ARR/CMP Register functions
  *                 + Write ARR/CMP Register functions
  *                 + PWM Mode Start/Stop
  *                 + Onepulse Mode Start/Stop
  *                 + Setonce Mode Start/Stop
  *                 + Encoder Mode Start/Stop
  *                 + Timeout Mode Start/Stop
  *                 + Counter Mode Start/Stop
  *                 + CNT reset management
  *                 + Interrupts and flags management
  * @version            V1.0.0
  * @data                   2025-03-31
    ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_lptim.h"
#include "ft32f4xx_rcc.h"

/* LPTIM registers Masks */
#define CFGR_CLEAR_MASK      ((uint32_t)0x20ebeedf)
//#define SPI_CTRLR0_CLEAR_MASK  ((uint32_t)0x0c03033f)


/* Private function prototypes -----------------------------------------------*/
void LPTIM_Start_Continuous(void);
void LPTIM_Start_Single(void);
void LPTIM_Disable(void);
/* Exported functions --------------------------------------------------------*/

/** @defgroup LPTIM_Exported_Functions_Group1 Initialization/de-initialization functions
 *  @brief    Initialization and Configuration functions.
 *
@verbatim
  ==============================================================================
              ##### Initialization and de-initialization functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the LPTIM according to the specified parameters in the
          LPTIM_InitTypeDef and initialize the associated handle.
      (+) DeInitialize the LPTIM peripheral.

@endverbatim
  * @{
  */


/**
  * @brief  Deinitializes the LPTIM peripheral registers to their default
  *         reset values.
  */
void LPTIM_DeInit(void)
{

    /* Enable LPTIM reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_LPTIM, ENABLE);
    /* Release LPTIM from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_LPTIM, DISABLE);
}

/**
  * @brief  Fills each LPTIM_InitStruct member with its default value.
  * @param  LPTIM_InitStruct: pointer to a LPTIM_InitTypeDef structure which will be initialized.
  * @retval None
  */
void LPTIM_StructInit(LPTIM_InitTypeDef *LPTIM_InitStruct)
{
    /*--------------- Reset LPTIM init structure parameters values -----------------*/
    /* Initialize the LPTIM clock source member */
    LPTIM_InitStruct->Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
    /* Initialize the LPTIM clock prescaler member */
    LPTIM_InitStruct->Prescaler = LPTIM_PRESCALER_DIV1;
    /* Initialize the LPTIM polarity of the active edge member */
    LPTIM_InitStruct->Polarity = LPTIM_CLOCKPOLARITY_RISING;
    /* Initialize the LPTIM Clock_SampleTime member */
    LPTIM_InitStruct->Clock_SampleTime = LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION;
    /* Initialize the LPTIM Trigger_Source member */
    LPTIM_InitStruct->Trigger_Source = LPTIM_TRIGSOURCE_0;
    /* Initialize the LPTIM Trigegr_ActiveEdge member */
    LPTIM_InitStruct->Trigegr_ActiveEdge = LPTIM_SOFTWARE;
    /* Initialize the LPTIM Trigg_SampleTime member */
    LPTIM_InitStruct->Trigg_SampleTime = LPTIM_TRIGSAMPLETIME_DIRECTTRANSITION;
    /* Initialize the LPTIM OutputPolarity member */
    LPTIM_InitStruct->OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
    /* Initialize the LPTIM UpdateMode member */
    LPTIM_InitStruct->UpdateMode = LPTIM_UPDATE_IMMEDIATE;
    /*Initialize the LPTIM CounterSource member*/
    LPTIM_InitStruct->CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
    /*Initialize the LPTIM Input1Source member*/
    LPTIM_InitStruct->Input1Source = LPTIM_INPUT1SOURCE_GPIO;
    /*Initialize the LPTIM Input2Source member*/
    LPTIM_InitStruct->Input2Source = LPTIM_INPUT2SOURCE_GPIO;

}

/**
  * @brief  Initializes the LPTIM peripheral according to the specified
  *         parameters in the LPTIM_InitStruct.
  * @param  LPTIM_InitStruct: pointer to a LPTIM_InitTypeDef structure that
  *         contains the configuration information for the specified LPTIM peripheral.
  * @retval None
  */
void LPTIM_Init(LPTIM_InitTypeDef *LPTIM_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the LPTIM parameters */
    assert_param(IS_LPTIM_CLOCK_SOURCE(LPTIM_InitStruct->Source));
    assert_param(IS_LPTIM_CLOCK_PRESCALER(LPTIM_InitStruct->Prescaler));
    assert_param(IS_LPTIM_CLOCK_POLARITY(LPTIM_InitStruct->Polarity));
    assert_param(IS_LPTIM_CLOCK_SAMPLE_TIME(LPTIM_InitStruct->Clock_SampleTime));
    assert_param(IS_LPTIM_TRG_SOURCE(LPTIM_InitStruct->Trigger_Source));
    assert_param(IS_LPTIM_EXT_TRG_POLARITY(LPTIM_InitStruct->Trigegr_ActiveEdge));
    assert_param(IS_LPTIM_TRIG_SAMPLE_TIME(LPTIM_InitStruct->Trigg_SampleTime));
    assert_param(IS_LPTIM_OUTPUT_POLARITY(LPTIM_InitStruct->OutputPolarity));
    assert_param(IS_LPTIM_UPDATE_MODE(LPTIM_InitStruct->UpdateMode));
    assert_param(IS_LPTIM_COUNTER_SOURCE(LPTIM_InitStruct->CounterSource));
    assert_param(IS_LPTIM_INPUT1_SOURCE(LPTIM_InitStruct->Input1Source));
    assert_param(IS_LPTIM_INPUT2_SOURCE(LPTIM_InitStruct->Input2Source));

    /*---------------------------- LPTIM CFGR Configuration ------------------------*/
    /* Get the LPTIM CFGR value */
    tmpreg = LPTIM->CFGR;
    /* Clear TRIGSEL[3:0],COUNTMODE.PRELOAD,WAVPOL,TRIGEN[1:0],PRESC[2:0],TRGFLT,CKFLT,CKPOL,CKSEL bits */
    tmpreg &= ~CFGR_CLEAR_MASK;
    /* Configure LPTIM CFGR register*/
    tmpreg |= (uint32_t)((uint32_t)LPTIM_InitStruct->Source            | LPTIM_InitStruct->Prescaler           |
                         LPTIM_InitStruct->Polarity          | LPTIM_InitStruct->Clock_SampleTime    |
                         LPTIM_InitStruct->Trigger_Source    | LPTIM_InitStruct->Trigegr_ActiveEdge  |
                         LPTIM_InitStruct->Trigg_SampleTime  | LPTIM_InitStruct->OutputPolarity     |
                         LPTIM_InitStruct->CounterSource);
    /* Write to LPTIM CFGR */
    LPTIM->CFGR = tmpreg;

    /*-------------------------LPTIM OR Configuration -----------------------*/
    /* Clear OR register */
    tmpreg = 0;
    /* Configure LPTIM IN1[2:0], IN2[2:0]  */
    tmpreg |= (uint32_t)((uint32_t)(LPTIM_InitStruct->Input1Source)  | LPTIM_InitStruct->Input2Source);
    /* Write to LPTIM OR */
    LPTIM->OR = tmpreg;

}

/**
  * @}
  */


/** @defgroup LPTIM_Exported_Functions_Group2 LPTIM Start-Stop operation functions
 *  @brief   Start-Stop operation functions.
 *
@verbatim
  ==============================================================================
                ##### LPTIM Start Stop operation functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Start the PWM mode.
      (+) Stop the PWM mode.
      (+) Start the One pulse mode.
      (+) Stop the One pulse mode.
      (+) Start the Set once mode.
      (+) Stop the Set once mode.
      (+) Start the Encoder mode.
      (+) Stop the Encoder mode.
      (+) Start the Timeout mode.
      (+) Stop the Timeout mode.
      (+) Start the Counter mode.
      (+) Stop the Counter mode.


@endverbatim
  * @{
  */

/**
  * @brief  Start the LPTIM PWM generation.
  * @param  Period Specifies the Autoreload value.
  *         This parameter must be a value between 0x0000 and 0xFFFF.
  * @param  Pulse Specifies the compare value.
  *         This parameter must be a value between 0x0000 and 0xFFFF.
  */

void LPTIM_PWM_Start(uint32_t Period, uint32_t Pulse)
{
    /* Check the parameters */
    assert_param(IS_LPTIM_PERIOD(Period));
    assert_param(IS_LPTIM_PULSE(Pulse));

    /* Reset WAVE bit to set PWM mode */
    LPTIM->CFGR &= ~LPTIM_CFGR_WAVE;

    /* Enable the Peripheral */
    LPTIM->CR   |= LPTIM_CR_ENABLE;

    /* Write the ARR register value*/
    LPTIM_Write_ARRRegister(Period);

    /* Write the CMP register value*/
    LPTIM_Write_CMPRegister(Pulse);

    /* Start timer in continuous mode */
    LPTIM_Start_Continuous();

}

/**
  * @brief  Stop the LPTIM PWM generation.
  */
void LPTIM_PWM_Stop(void)
{
    /* Disable the Peripheral */
    LPTIM_Disable();
}
/**
  * @brief  Start the LPTIM One pulse generation.
  * @param  Period Specifies the Autoreload value.
  *         This parameter must be a value between 0x0000 and 0xFFFF.
  * @param  Pulse Specifies the compare value.
  *         This parameter must be a value between 0x0000 and 0xFFFF.
  */
void LPTIM_OnePulse_Start(uint32_t Period, uint32_t Pulse)
{

    /* Check the parameters */
    assert_param(IS_LPTIM_PERIOD(Period));
    assert_param(IS_LPTIM_PULSE(Pulse));

    /* Reset WAVE bit to set one pulse mode */
    LPTIM->CFGR &= ~LPTIM_CFGR_WAVE;

    /* Enable the Peripheral */
    LPTIM->CR   |= LPTIM_CR_ENABLE;

    /* Write the ARR register value*/
    LPTIM_Write_ARRRegister(Period);

    /* Write the CMP register value*/
    LPTIM_Write_CMPRegister(Pulse);

    /* Start timer in single mode */
    LPTIM_Start_Single();

}

/**
  * @brief  Stop the LPTIM OnePulse generation.
  */
void LPTIM_OnePulse_Stop(void)
{
    /* Disable the Peripheral */
    LPTIM_Disable();
}

/**
  * @brief  Start the LPTIM in Set once mode.
  * @param  Period Specifies the Autoreload value.
  *         This parameter must be a value between 0x0000 and 0xFFFF.
  * @param  Pulse Specifies the compare value.
  *         This parameter must be a value between 0x0000 and 0xFFFF.
  */
void LPTIM_SetOnce_Start(uint32_t Period, uint32_t Pulse)
{

    /* Check the parameters */
    assert_param(IS_LPTIM_PERIOD(Period));
    assert_param(IS_LPTIM_PULSE(Pulse));

    /* Set WAVE bit to enable the set once mode */
    LPTIM->CFGR |= LPTIM_CFGR_WAVE;

    /* Enable the Peripheral */
    LPTIM->CR   |= LPTIM_CR_ENABLE;

    /* Write the ARR register value*/
    LPTIM_Write_ARRRegister(Period);

    /* Write the CMP register value*/
    LPTIM_Write_CMPRegister(Pulse);

    /* Start timer in single mode */
    LPTIM_Start_Single();

}

/**
  * @brief  Stop the LPTIM SetOnce generation.
  */
void LPTIM_SetOnce_Stop(void)
{
    /* Disable the Peripheral */
    LPTIM_Disable();
}


/**
  * @brief  Start the Encoder interface.
  * @param  Period Specifies the Autoreload value.
  *         This parameter must be a value between 0x0000 and 0xFFFF.
  */
void LPTIM_Encoder_Start(uint32_t Period)
{

    /* Check the parameters */
    assert_param(IS_LPTIM_PERIOD(Period));

    /* Set ENC bit to enable the encoder interface */
    LPTIM->CFGR |= LPTIM_CFGR_ENC;

    LPTIM_Counter_Start(Period);
    ///* Enable the Peripheral */
    //LPTIM->CR   |= LPTIM_CR_ENABLE;

    ///* Write the ARR register value*/
    //LPTIM_Write_ARRRegister(Period);

    ///* Start timer in continuous mode */
    //LPTIM_Start_Continuous();

}


/**
  * @brief  Stop the LPTIM Encoder generation.
  */
void LPTIM_Encoder_Stop(void)
{
    /* Disable the Peripheral */
    LPTIM_Disable();
    /* Reset ENC bit to disable the encoder function */
    LPTIM->CFGR &= ~LPTIM_CFGR_ENC;
}


void LPTIM_TimeOut_Start(uint32_t Period, uint32_t Timeout)
{

    /* Check the parameters */
    assert_param(IS_LPTIM_PERIOD(Period));
    assert_param(IS_LPTIM_PULSE(Timeout));

    /* Set TIMOUT bit to enable the timeout function */
    LPTIM->CFGR |= LPTIM_CFGR_TIMOUT;

    /* Enable the Peripheral */
    LPTIM->CR   |= LPTIM_CR_ENABLE;

    /* Write the ARR register value*/
    LPTIM_Write_ARRRegister(Period);

    /* Write the CMP register value*/
    LPTIM_Write_CMPRegister(Timeout);

    /* Start timer in continuous mode */
    LPTIM_Start_Continuous();

}

/**
  * @brief  Stop the LPTIM TimeOut generation.
  */
void LPTIM_TimeOut_Stop(void)
{
    /* Disable the Peripheral */
    LPTIM_Disable();

    /* Reset TIMOUT bit to disable the timeout function */
    LPTIM->CFGR &= ~LPTIM_CFGR_TIMOUT;
}

/**
  * @brief  Start the Counter mode.
  * @param  Period Specifies the Autoreload value.
  *         This parameter must be a value between 0x0000 and 0xFFFF.
  */
void LPTIM_Counter_Start(uint32_t Period)
{
    /* Check the parameters */
    assert_param(IS_LPTIM_PERIOD(Period));

    /* If clock source is not ULPTIM clock and counter source is external, then it must not be prescaled */
    if ((LPTIM->CFGR & (LPTIM_CFGR_CKSEL | LPTIM_CFGR_COUNTMODE)) == LPTIM_CFGR_COUNTMODE)
    {
        /* Check if clock is prescaled */
        /* Set clock prescaler to 0 */
        LPTIM->CFGR &= ~LPTIM_CFGR_PRESC;
    }

    /* Enable the Peripheral */
    LPTIM->CR   |= LPTIM_CR_ENABLE;

    /* Write the ARR register value*/
    LPTIM_Write_ARRRegister(Period);

    /* Start timer in continuous mode */
    LPTIM_Start_Continuous();

}

/**
  * @brief  Stop the LPTIM Counter generation.
  */
void LPTIM_Counter_Stop(void)
{
    /* Disable the Peripheral */
    LPTIM_Disable();

}

void LPTIM_Disable(void)
{
    uint32_t tmpclksource = 0;
    uint32_t tmpIER;
    uint32_t tmpCFGR;
    uint32_t tmpCMP;
    uint32_t tmpARR;
    uint32_t tmpOR;

    //__disable_irq();

    /*********** Save LPTIM Config ***********/
    /* Save LPTIM source clock */
    tmpclksource = (RCC->CCIPR & RCC_CCIPR_LPTIMSEL);

    /* Save LPTIM configuration registers */
    tmpIER = LPTIM->IER;
    tmpCFGR = LPTIM->CFGR;
    tmpCMP = LPTIM->CMP;
    tmpARR = LPTIM->ARR;
    tmpOR = LPTIM->OR;

    /*********** Reset LPTIM ***********/
    RCC_APB2PeriphResetCmd(RCC_APB2PeriphRst_LPTIM, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PeriphRst_LPTIM, DISABLE);

    /*********** Restore LPTIM Config ***********/
    /* Force LPTIM source kernel clock from APB */
    RCC_LPTIMCLKConfig(RCC_LPTIMCLK_PCLK);

    /* Restore CMP register (LPTIM should be enabled first) */
    LPTIM->CR |= LPTIM_CR_ENABLE;
    LPTIM_Write_CMPRegister(tmpCMP);

    /* Restore ARR register (LPTIM should be enabled first) */
    LPTIM->CR |= LPTIM_CR_ENABLE;
    LPTIM_Write_ARRRegister(tmpARR);

    /* Restore LPTIM source kernel clock */
    RCC_LPTIMCLKConfig(tmpclksource);

    /* Restore configuration registers (LPTIM should be disabled first) */
    LPTIM->CR &= ~(LPTIM_CR_ENABLE);
    LPTIM->IER = tmpIER;
    LPTIM->CFGR = tmpCFGR;
    LPTIM->OR = tmpOR;

    //__enable_irq();

}
/**
  * @}
  */


/** @defgroup LPTIM_Exported_Functions_Group3 LPTIM Read operation functions
 *  @brief  Read operation functions.
 *
@verbatim
  ==============================================================================
                  ##### LPTIM Read/Write operation functions #####
  ==============================================================================
[..]  This section provides LPTIM Reading functions.
      (+) Read the counter value.
      (+) Read the period (Auto-reload) value.
      (+) Read the pulse (Compare)value.
      (+) Write the period (Auto-reload) value.
      (+) Write the pulse (Compare)value.
@endverbatim
  * @{
  */

/**
  * @brief  Return the current counter value.
  * @retval Counter value.
  */

uint32_t LPTIM_ReadCounter(void)
{
    return (LPTIM->CNT);
}

/**
  * @brief  Return the current Autoreload (Period) value.
  * @retval Autoreload value.
  */

uint32_t LPTIM_ReadAutoReload(void)
{
    return (LPTIM->ARR);
}

/**
  * @brief  Return the current Compare (Pulse) value.
  * @retval Compare value.
  */

uint32_t LPTIM_ReadCompare(void)
{
    return (LPTIM->CMP);
}

/**
  * @brief  LPTimer Write ARR register
  * @param  Period  the ARR value
  */

void LPTIM_Write_ARRRegister(uint32_t Period)
{
    /* Clear ARROK flag */
    LPTIM->ICR   = LPTIM_ICR_ARROKCF ;

    /* Load the period value in the autoreload register*/
    LPTIM->ARR   = Period ;

    /* Wait for the completion of the write operation to the LPTIM_ARR register */
    while (LPTIM_GetStatus(LPTIM_ISR_ARROK) != LPTIM_ISR_ARROK);
}

/**
  * @brief  LPTimer Write CMP register
  * @param  Pulse  the CMP value
  */

void LPTIM_Write_CMPRegister(uint32_t Pulse)
{
    /* Clear CMPOK flag */
    LPTIM->ICR   = LPTIM_ICR_CMPOKCF ;

    /* Load the pulse value in the compare register*/
    LPTIM->CMP   = Pulse ;

    /* Wait for the completion of the write operation to the LPTIM_CMP register */
    while (LPTIM_GetStatus(LPTIM_ISR_CMPOK) != LPTIM_ISR_CMPOK);
}

/**
  * @brief  Enables or disables LPTIM PRELOAD bit
  * @param  NewState: new state of the PRELOAD bit.
  *         This parameter can be: ENABLE or DISABLE.
  */
void LPTIM_Preload_Config(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set PRELOAD bit*/
        LPTIM->CFGR |= LPTIM_CFGR_PRELOAD ;
    }
    else
    {
        /* Clear PRELOAD bit*/
        LPTIM->CFGR &= ~LPTIM_CFGR_PRELOAD ;
    }
}
/**
  * @}
  */


/**
  * @brief  LPTimer Start in Continuous mode
  */
void LPTIM_Start_Continuous(void)
{
    /* Set CNTSTRT bits*/
    LPTIM->CR |= LPTIM_CR_CNTSTRT ;
}

/**
  * @brief  LPTimer Start in single mode
  */
void LPTIM_Start_Single(void)
{
    /* Set SNGSTRT bits*/
    LPTIM->CR |= LPTIM_CR_SNGSTRT ;
}

/**
  * @brief  Enables or disables LPTIM reset cnt after read cnt
  * @param  NewState: new state of the RSTARE bits.
  *         This parameter can be: ENABLE or DISABLE.
  */
void LPTIM_RSTARE(FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set RSTARE bits*/
        LPTIM->CR |= LPTIM_CR_RSTARE ;
    }
    else
    {
        /* Clear RSTARE bits*/
        LPTIM->CR &= ~LPTIM_CR_RSTARE ;
    }
}

void LPTIM_COUNTRST(void)
{

    /* Set COUNTRST bits*/
    LPTIM->CR |= LPTIM_CR_COUNTRST ;

}
/**
  * @brief  LPTimer interrupt enable
  * @param  LPTIM_IT   The lptim interrupt enable
  * @param  NewState: new state of the LPTIM interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  */
void LPTIM_ITConfig(uint32_t LPTIM_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set the IT enable bits*/
        LPTIM->IER |= LPTIM_IT ;
    }
    else
    {
        /* Disable the IT enable bits*/
        LPTIM->IER &= ~LPTIM_IT ;
    }
}

/**
  * @brief  LPTimer Wait for flag set
  * @param  LPTIM_SR_FLAG   The lptim flag
  */
uint32_t LPTIM_GetStatus(uint32_t LPTIM_ISR_FLAG)
{
    /* Get the QSPI status */
    return (uint32_t)(LPTIM->ISR & LPTIM_ISR_FLAG);

}

/**
  * @brief  LPTimer clear interrupt flag
  * @param  flag   The lptim interrupt clear bit
  */
void LPTIM_ClearFlag(uint32_t flag)
{
    /* Write ICR register to clear ISR bits*/
    LPTIM->ICR = flag ;
}
/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
