/***********************************************************************
 * Filename    : hal_lpuart.c
 * Description : lpuart driver source file
 * Author(s)   : xwl
 * version     : V1.0
 * Modify date : 2019-11-19
 ***********************************************************************/
#include "ACM32Fxx_HAL.h"

static void TIMER_ETR_SetConfig(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler,
                       uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);
static void TIMER_TI1FP1_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter);
static void TIMER_TI2FP2_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter);
static void TIMER_IC1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t filter);
static void TIMER_IC2_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t filter);
static void TIMER_IC3_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t filter);
static void TIMER_IC4_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t filter);

/*********************************************************************************
* Function    : HAL_TIMER_MSP_Init
* Description : MSP init, mainly about clock, nvic
* Input       : timer handler
* Output      : 0: success; else:error
* Author      : xwl
**********************************************************************************/
__weak uint32_t HAL_TIMER_MSP_Init(TIM_HandleTypeDef * htim)
{
    uint32_t Timer_Instance;

    if (0 == IS_TIMER_INSTANCE(htim->Instance))
    {
        return HAL_ERROR; //instance error
    }

    Timer_Instance = (uint32_t)(htim->Instance);

    switch(Timer_Instance)
    {
        case TIM1_BASE:
        System_Module_Reset(RST_TIM1);
        System_Module_Enable(EN_TIM1);
        NVIC_ClearPendingIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
        NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
        break;

        case TIM3_BASE:
        System_Module_Reset(RST_TIM3);
        System_Module_Enable(EN_TIM3);
        NVIC_ClearPendingIRQ(TIM3_IRQn);
        NVIC_EnableIRQ(TIM3_IRQn);
        break;

        case TIM6_BASE:
        System_Module_Reset(RST_TIM6);
        System_Module_Enable(EN_TIM6);
        NVIC_ClearPendingIRQ(TIM6_IRQn);
        NVIC_EnableIRQ(TIM6_IRQn);
        break;

        case TIM14_BASE:
        System_Module_Reset(RST_TIM14);
        System_Module_Enable(EN_TIM14);
        NVIC_ClearPendingIRQ(TIM14_IRQn);
        NVIC_EnableIRQ(TIM14_IRQn);
        break;

        case TIM15_BASE:
        System_Module_Reset(RST_TIM15);
        System_Module_Enable(EN_TIM15);
        NVIC_ClearPendingIRQ(TIM15_IRQn);
        NVIC_EnableIRQ(TIM15_IRQn);
        break;

        case TIM16_BASE:
        System_Module_Reset(RST_TIM16);
        System_Module_Enable(EN_TIM16);
        NVIC_ClearPendingIRQ(TIM16_IRQn);
        NVIC_EnableIRQ(TIM16_IRQn);
        break;

        case TIM17_BASE:
        System_Module_Reset(RST_TIM17);
        System_Module_Enable(EN_TIM17);
        NVIC_ClearPendingIRQ(TIM17_IRQn);
        NVIC_EnableIRQ(TIM17_IRQn);
        break;

        default:
        return HAL_ERROR;
    }

    return HAL_OK;
}


__weak uint32_t HAL_TIMER_Base_MspDeInit(TIM_HandleTypeDef * htim)
{
    uint32_t Timer_Instance;

    if (0 == IS_TIMER_INSTANCE(htim->Instance))
    {
        return HAL_ERROR; //instance error
    }

    Timer_Instance = (uint32_t)(htim->Instance);

    switch(Timer_Instance)
    {
        case TIM1_BASE:
        System_Module_Disable(EN_TIM1);
        NVIC_ClearPendingIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
        NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
        break;



        case TIM3_BASE:
        System_Module_Disable(EN_TIM3);
        NVIC_ClearPendingIRQ(TIM3_IRQn);
        NVIC_DisableIRQ(TIM3_IRQn);
        break;



        case TIM6_BASE:
        System_Module_Disable(EN_TIM6);
        NVIC_ClearPendingIRQ(TIM6_IRQn);
        NVIC_DisableIRQ(TIM6_IRQn);
        break;



        case TIM14_BASE:
        System_Module_Disable(EN_TIM14);
        NVIC_ClearPendingIRQ(TIM14_IRQn);
        NVIC_DisableIRQ(TIM14_IRQn);
        break;

        case TIM15_BASE:
        System_Module_Disable(EN_TIM15);
        NVIC_ClearPendingIRQ(TIM15_IRQn);
        NVIC_DisableIRQ(TIM15_IRQn);
        break;

        case TIM16_BASE:
        System_Module_Disable(EN_TIM16);
        NVIC_ClearPendingIRQ(TIM16_IRQn);
        NVIC_DisableIRQ(TIM16_IRQn);
        break;

        case TIM17_BASE:
        System_Module_Disable(EN_TIM17);
        NVIC_ClearPendingIRQ(TIM17_IRQn);
        NVIC_DisableIRQ(TIM17_IRQn);
        break;

        default:
        return HAL_ERROR;
    }

    return HAL_OK;
}
/*********************************************************************************
* Function    : HAL_TIMER_Slave_Mode_Config
* Description : configure timer in slave mode
* Input       :
              htim: timer handler
              sSlaveConfig: slave mode parameter strcture
                            SlaveMode: TIM_SLAVE_MODE_DIS, TIM_SLAVE_MODE_ENC1...
                            InputTrigger: TIM_TRIGGER_SOURCE_ITR0, TIM_TRIGGER_SOURCE_ITR1...
                            TriggerPolarity: TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...
                            TriggerPrescaler: TIM_ETR_PRESCALER_1, TIM_ETR_PRESCALER_2...
* Output      : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIMER_Slave_Mode_Config(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *sSlaveConfig)
{
    if (0 == IS_TIM_SLAVE_INSTANCE(htim->Instance) )
    {
        return 1;  // not supported
    }
    /*reset SMS and TS bits*/
    htim->Instance->SMCR &= (~(BIT0|BIT1|BIT2|BIT4|BIT5|BIT6));
    /*SET SMS bits*/
    htim->Instance->SMCR |= (sSlaveConfig->SlaveMode & (BIT0|BIT1|BIT2) );
    /*SET TS bits*/
    htim->Instance->SMCR |= (sSlaveConfig->InputTrigger & (BIT4|BIT5|BIT6) );

    switch (sSlaveConfig->InputTrigger)
    {
        case TIM_TRIGGER_SOURCE_TI1FP1:
        TIMER_TI1FP1_ConfigInputStage(htim->Instance, sSlaveConfig->TriggerPolarity, sSlaveConfig->TriggerFilter);
        break;

        case TIM_TRIGGER_SOURCE_TI2FP2:
        TIMER_TI2FP2_ConfigInputStage(htim->Instance, sSlaveConfig->TriggerPolarity, sSlaveConfig->TriggerFilter);
        break;

        case TIM_TRIGGER_SOURCE_ETRF:
        TIMER_ETR_SetConfig(htim->Instance, sSlaveConfig->TriggerPrescaler, sSlaveConfig->TriggerPolarity, sSlaveConfig->TriggerFilter);
        break;

        case TIM_TRIGGER_SOURCE_ITR0:
        case TIM_TRIGGER_SOURCE_ITR1:
        case TIM_TRIGGER_SOURCE_ITR2:
        case TIM_TRIGGER_SOURCE_ITR3:
        // don't need do anything here
        break;

        default:
        return 1;
    }

    return 0;
}

/*********************************************************************************
* Function    : HAL_TIMER_Master_Mode_Config
* Description : configure timer in master mode
* Input       :
              TIMx: timer instance
              sMasterConfig: master mode parameter structure
                             MasterSlaveMode: TIM_TRGO_RESET, TIM_TRGO_ENABLE...
                             MasterOutputTrigger: TIM_MASTERSLAVEMODE_DISABLE, TIM_MASTERSLAVEMODE_ENABLE
* Output      : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIMER_Master_Mode_Config(TIM_TypeDef *TIMx, TIM_MasterConfigTypeDef * sMasterConfig)
{
    /*reset bits*/
    TIMx->SMCR &= (~BIT7);
    TIMx->CR2  &= (~(BIT4|BIT5|BIT6));

    TIMx->SMCR |= sMasterConfig->MasterSlaveMode;
    TIMx->CR2  |= sMasterConfig->MasterOutputTrigger;

    return 0;
}

/*********************************************************************************
* Function    : HAL_TIMER_Output_Config
* Description : configure output parameter
* Input       :
              TIMx: timer instance
              Output_Config: output configration parameter structure
                             OCMode: OUTPUT_MODE_FROZEN, OUTPUT_MODE_MATCH_HIGH...
                             Pulse: write to ccrx register
                             OCPolarity: OC channel output polarity: OUTPUT_POL_ACTIVE_HIGH, OUTPUT_POL_ACTIVE_LOW
                             OCNPolarity: OCN channel output polarity: OUTPUT_POL_ACTIVE_HIGH, OUTPUT_POL_ACTIVE_LOW
                             OCFastMode: OUTPUT_FAST_MODE_DISABLE, OUTPUT_FAST_MODE_ENABLE
                             OCIdleState: OC channel idle state, OUTPUT_IDLE_STATE_0, OUTPUT_IDLE_STATE_1
                             OCNIdleState: OCN channel idle state, OUTPUT_IDLE_STATE_0, OUTPUT_IDLE_STATE_1
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIMER_Output_Config(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef * Output_Config, uint32_t Channel)
{
    if (0 == IS_TIM_CCX_INSTANCE(TIMx, Channel) )
    {
        return 1;  // error parameter
    }

    switch(Channel)
    {
        case TIM_CHANNEL_1:
        TIMx->CCER &= (~BIT0);  //disable OC1
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT1);
        }
        else
        {
            TIMx->CCER |= (BIT1);
        }

        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER &= (~BIT2);  //disable OC1N

            if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCNPolarity)
            {
                TIMx->CCER &= (~BIT3);
            }
            else
            {
                TIMx->CCER |= (BIT3);
            }
        }

        TIMx->CCMR1 &= (~0x00FFU); // reset low 8 bits
        TIMx->CCR1 = Output_Config->Pulse;
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)
        {
            TIMx->CCMR1 |= (BIT2);
        }
        TIMx->CCMR1 |= (BIT3);  // preload enable

        if (IS_TIM_BREAK_INSTANCE(TIMx))
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT8);
            }
            else
            {
                TIMx->CR2 |= BIT8;
            }

            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCNIdleState)
            {
                TIMx->CR2 &= (~BIT9);
            }
            else
            {
                TIMx->CR2 |= BIT9;
            }

        }
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT4|BIT5|BIT6))) | (Output_Config->OCMode << 4);
        break;

        case TIM_CHANNEL_2:
        TIMx->CCER &= (~BIT4);  //disable OC2
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT5);
        }
        else
        {
            TIMx->CCER |= (BIT5);
        }

        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER &= (~BIT6);  //disable OC2N

            if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCNPolarity)
            {
                TIMx->CCER &= (~BIT7);
            }
            else
            {
                TIMx->CCER |= (BIT7);
            }
        }

        TIMx->CCMR1 &= (~0xFF00U); // reset high 8 bits
        TIMx->CCR2 = Output_Config->Pulse;   // write value to ccr before preload enable
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)
        {
            TIMx->CCMR1 |= (BIT10);
        }
        TIMx->CCMR1 |= (BIT11);  // preload enable

        if (IS_TIM_BREAK_INSTANCE(TIMx))
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT10);
            }
            else
            {
                TIMx->CR2 |= BIT10;
            }

            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCNIdleState)
            {
                TIMx->CR2 &= (~BIT11);
            }
            else
            {
                TIMx->CR2 |= BIT11;
            }

        }
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT12|BIT13|BIT14))) | (Output_Config->OCMode << 12);
        break;

        case TIM_CHANNEL_3:
        TIMx->CCER &= (~BIT8);  //disable OC3
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT9);
        }
        else
        {
            TIMx->CCER |= (BIT9);
        }

        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER &= (~BIT10);  //disable OC3N

            if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCNPolarity)
            {
                TIMx->CCER &= (~BIT11);
            }
            else
            {
                TIMx->CCER |= (BIT11);
            }
        }

        TIMx->CCMR2 &= (~0x00FF); // reset low 8 bits
        TIMx->CCMR2 |= (BIT3);  // preload enable
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)
        {
            TIMx->CCMR2 |= (BIT2);
        }

        TIMx->CCR3 = Output_Config->Pulse;
        if (IS_TIM_BREAK_INSTANCE(TIMx))
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT12);
            }
            else
            {
                TIMx->CR2 |= BIT12;
            }

            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCNIdleState)
            {
                TIMx->CR2 &= (~BIT13);
            }
            else
            {
                TIMx->CR2 |= BIT13;
            }

        }
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT4|BIT5|BIT6))) | (Output_Config->OCMode << 4);
        break;

        case TIM_CHANNEL_4:
        TIMx->CCER &= (~BIT12);  //disable OC4
        if (OUTPUT_POL_ACTIVE_HIGH == Output_Config->OCPolarity)
        {
            TIMx->CCER &= (~BIT13);
        }
        else
        {
            TIMx->CCER |= (BIT13);
        }

        TIMx->CCMR2 &= (~0xFF00); // reset high 8 bits
        TIMx->CCR4 = Output_Config->Pulse;
        if (OUTPUT_FAST_MODE_ENABLE == Output_Config->OCFastMode)
        {
            TIMx->CCMR2 |= (BIT10);  // fast mode
        }
        TIMx->CCMR2 |= (BIT11);  // preload enable

        if (IS_TIM_BREAK_INSTANCE(TIMx))
        {
            if (OUTPUT_IDLE_STATE_0 == Output_Config->OCIdleState)
            {
                TIMx->CR2 &= (~BIT14);
            }
            else
            {
                TIMx->CR2 |= BIT14;
            }

        }
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT12|BIT13|BIT14))) | (Output_Config->OCMode << 12);
        break;

        default:
            return 1; // error parameter
    }

    return 0;
}


/*********************************************************************************
* Function    : HAL_TIMER_Capture_Config
* Description : configure capture parameters
* Input       :
              TIMx: timer instance
              Capture_Config: capture configuration parameter strcture
                            ICPolarity: TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...
                            ICSelection: TIM_ICSELECTION_DIRECTTI, TIM_ICSELECTION_INDIRECTTI
                            ICFilter: TIM_IC1_FILTER_LVL(x), TIM_IC2_FILTER_LVL(x), x:0-15
                            ICPrescaler: TIM_IC1_PRESCALER_1, TIM_IC2_PRESCALER_1...
              Channel: channel id, TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIMER_Capture_Config(TIM_TypeDef *TIMx, TIM_IC_InitTypeDef * Capture_Config, uint32_t Channel)
{
    switch(Channel)
    {
        case TIM_CHANNEL_1:
        TIMER_IC1_SetConfig(TIMx, Capture_Config->ICPolarity, Capture_Config->ICSelection, Capture_Config->TIFilter);

        /* Reset the IC1PSC Bits */
        TIMx->CCMR1 &= (~BIT2|BIT3);
        /* Set the IC1PSC value */
        TIMx->CCMR1 |= Capture_Config->ICPrescaler;
        break;

        case TIM_CHANNEL_2:
        TIMER_IC2_SetConfig(TIMx, Capture_Config->ICPolarity, Capture_Config->ICSelection, Capture_Config->TIFilter);


        /* Reset the IC2PSC Bits */
        TIMx->CCMR1 &= (~BIT10|BIT11);
        /* Set the IC2PSC value */
        TIMx->CCMR1 |= Capture_Config->ICPrescaler;
        break;

        case TIM_CHANNEL_3:
        TIMER_IC3_SetConfig(TIMx, Capture_Config->ICPolarity, Capture_Config->ICSelection, Capture_Config->TIFilter);

        /* Reset the IC3PSC Bits */
        TIMx->CCMR2 &= (~BIT2|BIT3);
        /* Set the IC3PSC value */
        TIMx->CCMR2 |= Capture_Config->ICPrescaler;

        break;

        case TIM_CHANNEL_4:
        TIMER_IC4_SetConfig(TIMx, Capture_Config->ICPolarity, Capture_Config->ICSelection, Capture_Config->TIFilter);

        /* Reset the IC4PSC Bits */
        TIMx->CCMR2 &= (~BIT10|BIT11);
        /* Set the IC4PSC value */
        TIMx->CCMR2 |= Capture_Config->ICPrescaler;
        break;

        default:
        return 1;
    }

    return 0;
}



/*********************************************************************************
* Function    : HAL_TIMER_SelectClockSource
* Description : select timer counter source, internal or external
* Input:
  htim : timer handler
  sClockSourceConfig: configuration parameters, includes following members:
                      ClockSource: TIM_CLOCKSOURCE_INT,  TIM_CLOCKSOURCE_ETR...
                      ClockPolarity: TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...
                      ClockPrescaler: TIM_ETR_PRESCALER_1, TIM_ETR_PRESCALER_2...
                      ClockFilter: TIM_ETR_FILTER_LVL(x), TIM_IC1_FILTER_LVL(x), TIM_IC2_FILTER_LVL(x)
* Output      : HAL_ERROR:error, HAL_OK:OK
* Author      : xwl
**********************************************************************************/
HAL_StatusTypeDef HAL_TIMER_SelectClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef * sClockSourceConfig)
{
  htim->Instance->SMCR &= (~(BIT0|BIT1|BIT2));

  switch (sClockSourceConfig->ClockSource)
  {
    case TIM_CLOCKSOURCE_INT:
    {
        // do nothing here
        break;
    }

    case TIM_CLOCKSOURCE_ETR:
    {

      /* Configure the ETR Clock source */
      TIMER_ETR_SetConfig(htim->Instance,
                        sClockSourceConfig->ClockPrescaler,
                        sClockSourceConfig->ClockPolarity,
                        sClockSourceConfig->ClockFilter);
      /* Enable the External clock mode2 */
      htim->Instance->SMCR |= BIT14;  // ECE=1,external clock mode 2
      break;
    }

    case TIM_CLOCKSOURCE_TI1FP1:
    {

      TIMER_TI1FP1_ConfigInputStage(htim->Instance,
                               sClockSourceConfig->ClockPolarity,
                               sClockSourceConfig->ClockFilter);

      htim->Instance->SMCR &= (~(BIT4|BIT5|BIT6));  // trigger selection
      htim->Instance->SMCR |= (5  << 4);   // Trigger select TI1FP1

      htim->Instance->SMCR |= (BIT0|BIT1|BIT2);  // select external clock mode 1
      break;
    }

    case TIM_CLOCKSOURCE_TI2FP2:
    {
      TIMER_TI2FP2_ConfigInputStage(htim->Instance,
                               sClockSourceConfig->ClockPolarity,
                               sClockSourceConfig->ClockFilter);

      htim->Instance->SMCR &= (~(BIT4|BIT5|BIT6));  // trigger selection
      htim->Instance->SMCR |= (6  << 4);   // Trigger select TI2FP2

      htim->Instance->SMCR |= (BIT0|BIT1|BIT2);  // select external clock mode 1
      break;
    }

    case TIM_CLOCKSOURCE_ITR0:
    case TIM_CLOCKSOURCE_ITR1:
    case TIM_CLOCKSOURCE_ITR2:
    case TIM_CLOCKSOURCE_ITR3:
    {
        htim->Instance->SMCR &= (~(BIT4|BIT5|BIT6));
        htim->Instance->SMCR |= ( (sClockSourceConfig->ClockSource - TIM_CLOCKSOURCE_ITR0) << 4);

        htim->Instance->SMCR |= (BIT0|BIT1|BIT2);  // select external clock mode 1
        break;
    }

    default:
      return HAL_ERROR;
  }

  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIMER_Base_Init
* Description : timer base initiation
* Input       : timer handler
* Output      : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIMER_Base_Init(TIM_HandleTypeDef * htim)
{
    if (0 == IS_TIMER_INSTANCE(htim->Instance))
    {
        return 1; //instance error
    }

    htim->Instance->CR1 = BIT2;  // CEN=0, URS=1, OPM = 0

    if (htim->Init.ARRPreLoadEn)
    {
        htim->Instance->CR1 |= (BIT7);
    }
    else
    {
        htim->Instance->CR1 &= (~BIT7);
    }
    htim->Instance->ARR = htim->Init.Period;
    htim->Instance->PSC = htim->Init.Prescaler;
    if (IS_TIM_REPETITION_COUNTER_INSTANCE(htim->Instance))
    {
        htim->Instance->RCR = htim->Init.RepetitionCounter;
    }
    htim->Instance->EGR = BIT0;     // no UIF generated because URS=1

    if (IS_TIM_CLOCK_DIVISION_INSTANCE(htim->Instance))
    {
        htim->Instance->CR1 = (htim->Instance->CR1 & (~(BIT8|BIT9))) | ((htim->Init.ClockDivision) & (BIT8|BIT9));
    }
    //up/down/center mode
    htim->Instance->CR1 = (htim->Instance->CR1 & (~(BIT4|BIT5|BIT6))) | ((htim->Init.CounterMode) & (BIT4|BIT5|BIT6));

    htim->Instance->CR1 &= (~BIT2); //URS = 0

    return 0;
}

/*********************************************************************************
* Function    : HAL_TIMER_Base_DeInit
* Description : timer base deinitiation, disable Timer, turn off module clock and nvic
* Input       : timer handler
* Output      : HAL_OK: success; HAL_ERROR:error
* Author      : xwl
**********************************************************************************/
HAL_StatusTypeDef HAL_TIMER_Base_DeInit(TIM_HandleTypeDef *htim)
{
  htim->Instance->CR1 &= (~BIT0);

  HAL_TIMER_Base_MspDeInit(htim);

  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIMER_Base_Start
* Description : start timer
* Input       : timer instance
* Output      : none
* Author      : xwl
**********************************************************************************/
void HAL_TIMER_Base_Start(TIM_TypeDef *TIMx)
{
    if (0 == IS_TIM_SLAVE_INSTANCE(TIMx) )
    {
        TIMx->CR1 |= BIT0;
        return;
    }

    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )
    {
        TIMx->CR1 |= BIT0;
        return;
    }

    return;
}

/*********************************************************************************
* Function    : HAL_TIMER_Base_Stop
* Description : stop timer
* Input       : timer handler
* Output      : none
* Author      : xwl
**********************************************************************************/
HAL_StatusTypeDef HAL_TIMER_Base_Stop(TIM_TypeDef *TIMx)
{
    TIMx->CR1 &= (~BIT0);
    HAL_TIM_DISABLE_IT_EX(TIMx, TIM_IT_UPDATE);

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIMER_OnePulse_Init
* Description : start timer with one pulse mode
* Input       :
              htim: timer handler
              mode: 0 means normal mode, 1 means one pulse mode
* Output      : HAL_OK, success; HAL_ERROR, fail
* Author      : xwl
**********************************************************************************/
HAL_StatusTypeDef HAL_TIMER_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t mode)
{
    /* Check the TIM handle allocation */
    if(htim == NULL)
    {
        return HAL_ERROR;
    }

    HAL_TIMER_Base_Init(htim);

    /*reset  the OPM Bit */
    htim->Instance->CR1 &= (~BIT3);
    if (0 != mode)
    {
        /*set  the OPM Bit */
        htim->Instance->CR1 |= BIT3;
    }

    return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIM_PWM_Output_Start
* Description : start timer output
* Input       :
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIM_PWM_Output_Start(TIM_TypeDef *TIMx, uint32_t Channel)
{
    if (0 == IS_TIM_CCX_INSTANCE(TIMx, Channel) )
    {
        return 1;  // error parameter
    }

    switch(Channel)
    {
        case TIM_CHANNEL_1:
        TIMx->CCER |= BIT0;
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER |= BIT2;
        }
        break;

        case TIM_CHANNEL_2:
        TIMx->CCER |= BIT4;
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER |= BIT6;
        }
        break;

        case TIM_CHANNEL_3:
        TIMx->CCER |= BIT8;
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER |= BIT10;
        }
        break;

        case TIM_CHANNEL_4:
        TIMx->CCER |= BIT12;
        break;

        default:
            return 1;
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)
    {
        /* Enable the main output */
        TIMx->BDTR |= BIT15;
    }

    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )
    {
        TIMx->CR1 |= BIT0;
    }

    return 0;
}
/*********************************************************************************
* Function    : HAL_TIM_PWM_Output_Stop
* Description : stop timer pwm output
* Input       :
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : : 0: success; else:error
* Author      : xwl
**********************************************************************************/
HAL_StatusTypeDef HAL_TIM_PWM_Output_Stop(TIM_TypeDef *TIMx, uint32_t Channel)
{
    if (0 == IS_TIM_CCX_INSTANCE(TIMx, Channel) )
    {
        return HAL_ERROR;  // error parameter
    }

    switch(Channel)
    {
        case TIM_CHANNEL_1:
        TIMx->CCER &= (~(BIT0 | BIT2));
        break;

        case TIM_CHANNEL_2:
        TIMx->CCER &= (~(BIT4 | BIT6));
        break;

        case TIM_CHANNEL_3:
        TIMx->CCER &= (~(BIT8 | BIT10));
        break;

        case TIM_CHANNEL_4:
        TIMx->CCER &= (~(BIT12));
        break;

        default:
            return HAL_ERROR;
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)
    {
        /* Enable the main output */
        TIMx->BDTR &= (~BIT15);
    }

    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )
    {
        TIMx->CR1 &= (~BIT0);
    }

  /* Return function status */
  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIMER_OC_Start
* Description : start timer output
* Input       :
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIMER_OC_Start(TIM_TypeDef *TIMx, uint32_t Channel)
{
    if (0 == IS_TIM_CCX_INSTANCE(TIMx, Channel) )
    {
        return 1;  // error parameter
    }

    switch(Channel)
    {
        case TIM_CHANNEL_1:
        TIMx->CCER |= BIT0;
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER |= BIT2;
        }
        break;

        case TIM_CHANNEL_2:
        TIMx->CCER |= BIT4;
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER |= BIT6;
        }
        break;

        case TIM_CHANNEL_3:
        TIMx->CCER |= BIT8;
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER |= BIT10;
        }
        break;

        case TIM_CHANNEL_4:
        TIMx->CCER |= BIT12;
        break;

        default:
            return 1;
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)
    {
        /* Enable the main output */
        TIMx->BDTR |= BIT15;
    }

    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )
    {
        TIMx->CR1 |= BIT0;
    }

    return 0;
}

/*********************************************************************************
* Function    : HAL_TIMER_OCxN_Start
* Description : start timer OCxN output
* Input       :
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIMER_OCxN_Start(TIM_TypeDef *TIMx, uint32_t Channel)
{
    if (0 == IS_TIM_CCX_INSTANCE(TIMx, Channel) )
    {
        return 1;  // error parameter
    }

    switch(Channel)
    {
        case TIM_CHANNEL_1:
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER |= BIT2;
        }
        break;

        case TIM_CHANNEL_2:
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER |= BIT6;
        }
        break;

        case TIM_CHANNEL_3:
        if (IS_TIM_CCXN_INSTANCE(TIMx, Channel) )
        {
            TIMx->CCER |= BIT10;
        }
        break;

        case TIM_CHANNEL_4:
        TIMx->CCER |= BIT12;
        break;

        default:
            return 1;
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)
    {
        /* Enable the main output */
        TIMx->BDTR |= BIT15;
    }

    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )
    {
        TIMx->CR1 |= BIT0;
    }

    return 0;
}

/*********************************************************************************
* Function    : HAL_TIMER_OC_Stop
* Description : stop timer output
* Input       :
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : : 0: success; else:error
* Author      : xwl
**********************************************************************************/
HAL_StatusTypeDef HAL_TIMER_OC_Stop(TIM_TypeDef *TIMx, uint32_t Channel)
{
    if (0 == IS_TIM_CCX_INSTANCE(TIMx, Channel) )
    {
        return HAL_ERROR;  // error parameter
    }

    switch(Channel)
    {
        case TIM_CHANNEL_1:
        TIMx->CCER &= (~(BIT0 | BIT2));
        break;

        case TIM_CHANNEL_2:
        TIMx->CCER &= (~(BIT4 | BIT6));
        break;

        case TIM_CHANNEL_3:
        TIMx->CCER &= (~(BIT8 | BIT10));
        break;

        case TIM_CHANNEL_4:
        TIMx->CCER &= (~(BIT12));
        break;

        default:
            return HAL_ERROR;
    }

    if(IS_TIM_BREAK_INSTANCE(TIMx) != 0)
    {
        /* Enable the main output */
        TIMx->BDTR &= (~BIT15);
    }

    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )
    {
        TIMx->CR1 &= (~BIT0);
    }

  /* Return function status */
  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIM_Capture_Start
* Description : start timer capture
* Input       :
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIM_Capture_Start(TIM_TypeDef *TIMx, uint32_t Channel)
{
    if (0 == IS_TIM_CCX_INSTANCE(TIMx, Channel) )
    {
        return 1;  // error parameter
    }

    switch(Channel)
    {
        case TIM_CHANNEL_1:
        TIMx->CCER |= BIT0;
        break;

        case TIM_CHANNEL_2:
        TIMx->CCER |= BIT4;
        break;

        case TIM_CHANNEL_3:
        TIMx->CCER |= BIT8;
        break;

        case TIM_CHANNEL_4:
        TIMx->CCER |= BIT12;
        break;

        default:
            return 1;
    }

    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )
    {
        TIMx->CR1 |= BIT0;
    }

    return 0;
}


/*********************************************************************************
* Function    : HAL_TIM_Capture_Stop
* Description : stop timer capture
* Input       :
              TIMx: timer instance
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : : 0: success; else:error
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIM_Capture_Stop(TIM_TypeDef *TIMx, uint32_t Channel)
{
    if (0 == IS_TIM_CCX_INSTANCE(TIMx, Channel) )
    {
        return 1;  // error parameter
    }

    switch(Channel)
    {
        case TIM_CHANNEL_1:
        TIMx->CCER &= (~BIT0);
        break;

        case TIM_CHANNEL_2:
        TIMx->CCER &= (~BIT4);
        break;

        case TIM_CHANNEL_3:
        TIMx->CCER &= (~BIT8);
        break;

        case TIM_CHANNEL_4:
        TIMx->CCER &= (~BIT12);
        break;

        default:
            return 1;
    }

    if (TIM_SLAVE_MODE_TRIG != (TIMx->SMCR & (BIT0|BIT1|BIT2) ) )
    {
        TIMx->CR1 &= (~BIT0);
    }

    return 0;
}


/*********************************************************************************
* Function    : HAL_TIMEx_ETRSelection
* Description : select ETR signal, it can ben GPIO, COMP1_OUT, COMP2_OUT, ADC analog watchdog output
* Input       :
              htim: timer handler
              ETRSelection: ETR_SELECT_GPIO, ETR_SELECT_COMP1_OUT...
* Output      : HAL_OK, Success; HAL_ERROR:Fail
* Author      : xwl
**********************************************************************************/
HAL_StatusTypeDef  HAL_TIMEx_ETRSelection(TIM_HandleTypeDef *htim, uint32_t ETRSelection)
{
    HAL_StatusTypeDef status = HAL_OK;

    htim->Instance->AF1 &= (~ETR_SELECT_MASK);
    htim->Instance->AF1 |= ETRSelection;

    return status;
}

/*********************************************************************************
* Function    : HAL_TIMER_ReadCapturedValue
* Description : read capture value as channel
* Input       :
              htim: timer handler
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : capture value
* Author      : xwl
**********************************************************************************/
uint32_t HAL_TIMER_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  uint32_t capture_data = 0U;

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {
      /* Return the capture 1 value */
      capture_data =  htim->Instance->CCR1;
      break;
    }
    case TIM_CHANNEL_2:
    {
      /* Return the capture 2 value */
      capture_data =   htim->Instance->CCR2;
      break;
    }
    case TIM_CHANNEL_3:
    {
      /* Return the capture 3 value */
      capture_data =   htim->Instance->CCR3;
      break;
    }
    case TIM_CHANNEL_4:
    {
      /* Return the capture 4 value */
      capture_data =   htim->Instance->CCR4;
      break;
    }
    default:
      break;
  }

  return capture_data;
}

/*********************************************************************************
* Function    : HAL_TIMER_GenerateEvent
* Description : Generate event by software
* Input:
  htim : timer handler
  EventSource: TIM_EVENTSOURCE_UPDATE, TIM_EVENTSOURCE_CC1...
* Output      : HAL_ERROR:error, HAL_OK:OK
* Author      : xwl
**********************************************************************************/
HAL_StatusTypeDef HAL_TIMER_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource)
{
  htim->Instance->EGR = EventSource;

  return HAL_OK;
}

/*********************************************************************************
* Function    : HAL_TIMER_Clear_Capture_Flag
* Description : clear capture flag as channel id
* Input       :
              htim: timer handler
              Channel: TIM_CHANNEL_1, TIM_CHANNEL_2...
* Output      : capture value
* Author      : xwl
**********************************************************************************/
void HAL_TIMER_Clear_Capture_Flag(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    switch (Channel)
    {
        case TIM_CHANNEL_1:
        {
            htim->Instance->SR &= (~(BIT1|BIT9));
            break;
        }
        case TIM_CHANNEL_2:
        {
            htim->Instance->SR &= (~(BIT2|BIT10));
            break;
        }
        case TIM_CHANNEL_3:
        {
            htim->Instance->SR &= (~(BIT3|BIT11));
            break;
        }
        case TIM_CHANNEL_4:
        {
            htim->Instance->SR &= (~(BIT4|BIT12));
            break;
        }
        default:
        break;
    }
}

/*********************************************************************************
* Function    : TIMER_ETR_SetConfig
* Description : configure ETR channel polarity, prescaler and filter
* Input:
  TIMx : timer instance
  TIM_ExtTRGPrescaler: TIM_ETR_PRESCALER_1, TIM_ETR_PRESCALER_2...
  TIM_ExtTRGPolarity:  TIM_ETR_POLAIRTY_HIGH, TIM_ETR_POLAIRTY_LOW
  ExtTRGFilter:  TIM_ETR_FILTER_LVL(x), x=0-15
* Output      : none
* Author      : xwl
**********************************************************************************/
static void TIMER_ETR_SetConfig(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler, uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
  /* Reset the ETR Bits */
  TIMx->SMCR &= (~0xFF00U);

  /* Set the Prescaler, the Filter value and the Polarity */
  TIMx->SMCR |= (TIM_ExtTRGPrescaler | TIM_ExtTRGPolarity | ExtTRGFilter);
}

/*********************************************************************************
* Function    : TIMER_TI1FP1_ConfigInputStage
* Description : configure TI1FP1 channel polarity and filter
* Input:
  TIMx : timer instance
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...
  Filter:  TIM_TI1_FILTER_LVL(x), x=0-15
* Output      : none
* Author      : xwl
**********************************************************************************/
static void TIMER_TI1FP1_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t Filter)
{
    TIMx->CCER &= (~BIT0);  //Disable the Channel 1: Reset the CC1E Bit
    TIMx->CCMR1 = ((TIMx->CCMR1 & (~(BIT0|BIT1))) | BIT0);    // CH1 as input

    TIMx->CCMR1 &= (~0xF0U); // reset TI1 filter
    TIMx->CCMR1 |= Filter;

    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_RISING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_FALLING;
    }
    else
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_BOTH;
    }
}

/*********************************************************************************
* Function    : TIMER_TI2FP2_ConfigInputStage
* Description : configure TI2FP2 channel polarity and filter
* Input:
  TIMx : timer instance
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...
  Filter:  TIM_TI2_FILTER_LVL(x), x=0-15
* Output      : none
* Author      : xwl
**********************************************************************************/
static void TIMER_TI2FP2_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t Filter)
{
    TIMx->CCER &= (~BIT4);  //Disable the Channel 2: Reset the CC2E Bit
    TIMx->CCMR1 = ((TIMx->CCMR1 & (~(BIT8|BIT9))) | BIT8);    // CH2 as input

    TIMx->CCMR1 &= (~0xF000U); // reset TI2 filter
    TIMx->CCMR1 |= Filter;

    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_RISING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_FALLING;
    }
    else
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_BOTH;
    }
}

/*********************************************************************************
* Function    : TIMER_IC1_SetConfig
* Description : configure TI1FP1 or TI2FP1 channel polarity and filter
* Input:
  TIMx : timer instance
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...
  Filter:  TIM_TI1_FILTER_LVL(x), x=0-15
* Output      : none
* Author      : xwl
**********************************************************************************/
void TIMER_IC1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t Filter)
{
    /* Disable the Channel 1: Reset the CC1E Bit */
    TIMx->CCER &= (~BIT0);

    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_RISING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_FALLING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC1_SLAVE_CAPTURE_POL_BOTH;
    }

    if(TIM_ICSELECTION_DIRECTTI == TIM_ICSelection)
    {
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT0|BIT1))) | BIT0;
        TIMx->CCMR1 &= (~0xF0U);
    }
    else
    {
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT0|BIT1))) | BIT1;
        TIMx->CCMR1 &= (~0xF000U);
    }

    TIMx->CCMR1 |= Filter;

}

/*********************************************************************************
* Function    : TIMER_IC2_SetConfig
* Description : configure TI1FP2 or TI2FP2 channel polarity and filter
* Input:
  TIMx : timer instance
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...
  Filter:  TIM_TI2_FILTER_LVL(x), x=0-15
* Output      : none
* Author      : xwl
**********************************************************************************/
static void TIMER_IC2_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t Filter)
{
    /* Disable the Channel 2, Reset the CC2E Bit */
    TIMx->CCER &= (~BIT4);
    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_RISING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_FALLING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC2_SLAVE_CAPTURE_POL_BOTH;
    }

    if(TIM_ICSELECTION_DIRECTTI == TIM_ICSelection)
    {
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT8|BIT9))) | BIT8;
        TIMx->CCMR1 &= (~0xF000U);
    }
    else
    {
        TIMx->CCMR1 = (TIMx->CCMR1 & (~(BIT8|BIT9))) | BIT9;
        TIMx->CCMR1 &= (~0xF0U);
    }

    TIMx->CCMR1 |= Filter;

}

/*********************************************************************************
* Function    : TIMER_IC3_SetConfig
* Description : configure TI3FP3 or TI4FP3 channel polarity and filter
* Input:
  TIMx : timer instance
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...
  Filter:  TIM_TI3_FILTER_LVL(x), x=0-15
* Output      : none
* Author      : xwl
**********************************************************************************/
static void TIMER_IC3_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t Filter)
{
    /* Disable the Channel 3, Reset the CC3E Bit */
    TIMx->CCER &= (~BIT8);

    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC3_SLAVE_CAPTURE_POL_RISING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC3_SLAVE_CAPTURE_POL_FALLING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC3_SLAVE_CAPTURE_POL_BOTH;
    }

    if(TIM_ICSELECTION_DIRECTTI == TIM_ICSelection)
    {
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT0|BIT1))) | BIT0;
        TIMx->CCMR2 &= (~0xF0U);
    }
    else
    {
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT0|BIT1))) | BIT1;
        TIMx->CCMR2 &= (~0xF000U);
    }


    TIMx->CCMR2 |= Filter;
}


/*********************************************************************************
* Function    : TIMER_IC4_SetConfig
* Description : configure TI3FP4 or TI4FP4 channel polarity and filter
* Input:
  TIMx : timer instance
  TIM_ICPolarity:  TIM_SLAVE_CAPTURE_ACTIVE_RISING, TIM_SLAVE_CAPTURE_ACTIVE_FALLING...
  Filter:  TIM_TI4_FILTER_LVL(x), x=0-15
* Output      : none
* Author      : xwl
**********************************************************************************/
static void TIMER_IC4_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t Filter)
{
     /* Disable the Channel 3, Reset the CC3E Bit */
    TIMx->CCER &= (~BIT12);

    if(TIM_SLAVE_CAPTURE_ACTIVE_RISING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC4_SLAVE_CAPTURE_POL_RISING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC4_SLAVE_CAPTURE_POL_FALLING;
    }
    else if (TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING == TIM_ICPolarity)
    {
        TIMx->CCER |= TIM_CC4_SLAVE_CAPTURE_POL_BOTH;
    }

    if(TIM_ICSELECTION_DIRECTTI == TIM_ICSelection)
    {
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT8|BIT9))) | BIT8;
        TIMx->CCMR2 &= (~0xF000U);
    }
    else
    {
        TIMx->CCMR2 = (TIMx->CCMR2 & (~(BIT8|BIT9))) | BIT9;
        TIMx->CCMR2 &= (~0xF0U);
    }

    TIMx->CCMR2 |= Filter;

}


