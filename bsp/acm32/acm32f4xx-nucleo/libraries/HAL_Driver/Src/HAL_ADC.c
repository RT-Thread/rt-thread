/*
  ******************************************************************************
  * @file    HAL_ADC.c
  * @version V1.0.0
  * @date    2020
  * @brief   ADC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Analog to Digital Converter (ADC) peripheral:
  *           @ Initialization  functions
  *           @ IO operation functions
  ******************************************************************************
*/
#include "ACM32Fxx_HAL.h"

extern ADC_HandleTypeDef ADC_Handle;

/************************************************************************
 * function   : HAL_ADC_IRQHandler
 * Description: This function handles SPI interrupt request.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 ************************************************************************/
__weak void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc)
{
    __IO uint32_t Status;
    
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return;
    if(!IS_ADC_ALL_CONCONVMODE(hadc->Init.ConConvMode)) return;  
  
    Status = hadc->Instance->SR;
    /************ Check End of Conversion flag for injected ************/
    if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IE_JEOCIE))
    {
        if((Status & ADC_SR_JEOC) == ADC_SR_JEOC)
        {
            if(__HAL_ADC_CHECK_TRIG_INJECTED(hadc, ADC_SOFTWARE_START)     || 
                ((__HAL_ADC_CHECK_TRIG_REGULAR(hadc, ADC_SOFTWARE_START))  &&
                (hadc->Init.ConConvMode == 0)))
            {
                /* Disable ADC end of conversion interrupt on group injected */
                __HAL_ADC_DISABLE_IT(hadc, ADC_IE_JEOCIE);

            }

            /* Conversion complete callback */ 
            if (NULL != hadc->InjectedConvCpltCallback)
                hadc->InjectedConvCpltCallback(hadc);
      
            /* Clear injected group conversion flag */
            __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_JEOC);
        }
    }

    /************ Check Conversion flag for regular group ************/
    if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IE_EOCIE))
    {
        if((Status & ADC_SR_EOC) == ADC_SR_EOC)
        {      
            /* Conversion complete callback */
            if (NULL != hadc->ConvCpltCallback)
                hadc->ConvCpltCallback(hadc);
      
            /* Clear conversion flag */
            __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_EOC);
        }
    }

    /************ Check Analog watchdog flags ************/
    if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IE_AWDIE))
    {
        if((Status & ADC_SR_AWD) == ADC_SR_AWD)
        {
            /* Level out of window callback */ 
            if (NULL != hadc->LevelOutOfWindowCallback)
                hadc->LevelOutOfWindowCallback(hadc);

            /* Clear the ADC analog watchdog flag */
            __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_AWD);
        }
    }  
    
    /************ Check End of Conversion flag for regular group ************/
    if(__HAL_ADC_GET_IT_SOURCE(hadc, ADC_IE_EOGIE))
    {
        if((Status & ADC_SR_EOG) == ADC_SR_EOG)
        {      
            if((__HAL_ADC_CHECK_TRIG_REGULAR(hadc, ADC_SOFTWARE_START)) && 
             (hadc->Init.ConConvMode == 0))
            {
                /* Disable ADC end of conversion interrupt on group regular */
                __HAL_ADC_DISABLE_IT(hadc, ADC_IE_EOGIE);
            }
      
            /* Conversion complete callback */
            if (NULL != hadc->GroupCpltCallback)
                hadc->GroupCpltCallback(hadc);

            /* Clear regular group conversion flag */
            __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_EOG);
        }
    }
}

/************************************************************************
 * function   : HAL_ADC_MspInit
 * Description: 
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : none
 ************************************************************************/
__weak void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    uint32_t i;
    uint32_t ADC_Pin_Map[][3] =
    {
        { ADC_CHANNEL_0_EN, GPIOC, GPIO_PIN_5 }, 
        { ADC_CHANNEL_1_EN, GPIOA, GPIO_PIN_7 },
        { ADC_CHANNEL_2_EN, GPIOA, GPIO_PIN_5 },
        { ADC_CHANNEL_3_EN, GPIOA, GPIO_PIN_3 },
        { ADC_CHANNEL_4_EN, GPIOC, GPIO_PIN_3 },
        { ADC_CHANNEL_5_EN, GPIOC, GPIO_PIN_1 },
        { ADC_CHANNEL_6_EN, GPIOA, GPIO_PIN_0 },
        { ADC_CHANNEL_8_EN, GPIOC, GPIO_PIN_4 },
        { ADC_CHANNEL_9_EN, GPIOA, GPIO_PIN_6 },
        { ADC_CHANNEL_10_EN, GPIOA, GPIO_PIN_4 },
        { ADC_CHANNEL_11_EN, GPIOA, GPIO_PIN_2 },
        { ADC_CHANNEL_12_EN, GPIOC, GPIO_PIN_2 },
        { ADC_CHANNEL_13_EN, GPIOC, GPIO_PIN_0 },
        { ADC_CHANNEL_VBAT_EN, GPIOA, GPIO_PIN_1 },
        { ADC_CHANNEL_EXT2_EN, GPIOB, GPIO_PIN_1 },
        { ADC_CHANNEL_EXT3_EN, GPIOB, GPIO_PIN_2 },
        { 0xffffffff, 0 }, //结束标志
    };    
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */
    GPIO_InitTypeDef GPIO_Handle; 

    //Set gpio to analog.
    for(i = 0; ADC_Pin_Map[i][0] != 0xffffffff; i++)
    {
        if(hadc->Init.ChannelEn & ADC_Pin_Map[i][0])
        {
            GPIO_Handle.Pin            = ADC_Pin_Map[i][2];
            GPIO_Handle.Mode           = GPIO_MODE_ANALOG;
            GPIO_Handle.Pull           = GPIO_NOPULL;
            HAL_GPIO_Init(ADC_Pin_Map[i][1], &GPIO_Handle);             
        }
    }
    
    /* Enable ADC Clock */
    System_Module_Enable(EN_ADC);
    
    /* Clear Pending Interrupt */
    NVIC_ClearPendingIRQ(ADC_IRQn);
    
    /* Enable External Interrupt */
    NVIC_EnableIRQ(ADC_IRQn);
}

/************************************************************************
 * function   : HAL_ADC_MspDeInit
 * Description: 
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : none
 ************************************************************************/
__weak void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{    
    /* 
      NOTE : This function should be modified by the user.
    */
    
    /* For Example */    
    if(hadc->Init.DMAMode)
    {
        HAL_DMA_DeInit(hadc->DMA_Handle);

        hadc->DMA_Handle = NULL;
    }
    
    /* Disable ADC Clock */
    System_Module_Disable(EN_ADC);
    
    /* Clear Pending Interrupt */
    NVIC_ClearPendingIRQ(ADC_IRQn);
    
    /* Disable External Interrupt */
    NVIC_DisableIRQ(ADC_IRQn);
}

/************************************************************************
 * function   : HAL_ADC_Init
 * Description: Init the ADC module
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc)
{
    /* Check the ADC handle allocation */
    if (hadc == NULL)
    {
        return HAL_ERROR;
    }
    
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
    if(!IS_ADC_ALL_CONCONVMODE(hadc->Init.ConConvMode)) return HAL_ERROR;
    if(!IS_ADC_ALL_JCHANNELMODE(hadc->Init.JChannelMode)) return HAL_ERROR;
    if(!IS_ADC_ALL_DIFFMODE(hadc->Init.DiffMode)) return HAL_ERROR;
    if(!IS_ADC_ALL_DMAMODE(hadc->Init.DMAMode)) return HAL_ERROR;
    if(!IS_ADC_ALL_OVERMODE(hadc->Init.OverMode)) return HAL_ERROR;
    if(!IS_ADC_ALL_OVERSAMPMODE(hadc->Init.OverSampMode)) return HAL_ERROR;    
    if(!IS_ADC_ALL_OVSR(hadc->Init.Oversampling.Ratio)) return HAL_ERROR;    
    if(!IS_ADC_ALL_OVSS(hadc->Init.Oversampling.RightBitShift)) return HAL_ERROR;    
    if(!IS_ADC_ALL_ANALOGWDGEN(hadc->Init.AnalogWDGEn)) return HAL_ERROR;
    if(!IS_ADC_ALL_CLOCKDIV(hadc->Init.ClockDiv)) return HAL_ERROR;   
    if(!IS_ADC_ALL_CHANNELEN(hadc->Init.ChannelEn)) return HAL_ERROR;
    if(!IS_ADC_ALL_TRIG(hadc->Init.ExTrigMode.ExTrigSel)) return HAL_ERROR;
    if(!IS_ADC_ALL_CHANNELEN(hadc->Init.ExTrigMode.JExTrigSel)) return HAL_ERROR;
    
    /* Init the low level hardware : GPIO, CLOCK, NVIC, DMA */
    HAL_ADC_MspInit(hadc);
    
   //Reset AFE.
    SET_BIT(hadc->Instance->CR2,ADC_CR2_AFE_RSTN);
   //Set Clock DIV.
    MODIFY_REG(hadc->Instance->CR2,ADC_CR2_DIV_MASK,hadc->Init.ClockDiv<<ADC_CR2_DIV_POS);
    
    //Set continued convert mode
    if(hadc->Init.ConConvMode)
        SET_BIT(hadc->Instance->CR1,ADC_CR1_CONT);
    else
        CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_CONT);
        
    //Overflow
    if(hadc->Init.OverMode == ADC_OVERMODE_ENABLE)
        SET_BIT(hadc->Instance->CR2,ADC_CR2_OVRMOD);
    else
        CLEAR_BIT(hadc->Instance->CR2,ADC_CR2_OVRMOD);
    
    //Over Sample Set
    if(hadc->Init.OverSampMode)
    {
        if(hadc->Init.JChannelMode)
        {
            SET_BIT(hadc->Instance->CR2,ADC_CR2_JOVSE); // Inject channel over sample en.
            if(hadc->Init.Oversampling.TriggeredMode)
                SET_BIT(hadc->Instance->CR2,ADC_CR2_JTOVS); // N times sample every trig.
            else
                CLEAR_BIT(hadc->Instance->CR2,ADC_CR2_JTOVS); // 1 time sample every trig.
        }
        
        MODIFY_REG(hadc->Instance->CR2,ADC_CR2_OVSR_MASK,hadc->Init.Oversampling.Ratio<<ADC_CR2_OVSR_POS);   //over sample rate
        MODIFY_REG(hadc->Instance->CR2,ADC_CR2_OVSS_MASK,hadc->Init.Oversampling.RightBitShift<<ADC_CR2_OVSS_POS); //over sample right shift.
        SET_BIT(hadc->Instance->CR2,ADC_CR2_OVSE); // Regular channel over sample en.
    }
    
    //ExTrigSel set
    MODIFY_REG(hadc->Instance->CR1,ADC_CR1_EXTSEL_MASK,hadc->Init.ExTrigMode.ExTrigSel<<ADC_CR1_EXTSEL_POS);
    if(hadc->Init.JChannelMode)
    {
        /* Enable the inject channel */
        SET_BIT(hadc->Instance->CR1, ADC_CR1_JEN);
        //JExTrigSel set
        MODIFY_REG(hadc->Instance->CR1,ADC_CR1_JEXTSEL_MASK,hadc->Init.ExTrigMode.JExTrigSel<<ADC_CR1_JEXTSEL_POS);        
    }

    //Clear the sequence length.
    CLEAR_BIT(hadc->Instance->SQR1,ADC_SQR1_L); //Clear the sequence length.
    
    return  HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_DeInit
 * Description: DeInit the ADC module
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc)
{
    /* Check the ADC handle allocation */
    if (hadc == NULL)
    {
        return HAL_ERROR;
    }
    
    HAL_ADC_MspDeInit(hadc);
    
    hadc->ChannelNum = 0;
    hadc->ConvCpltCallback = NULL;
    hadc->InjectedConvCpltCallback = NULL;
    hadc->LevelOutOfWindowCallback = NULL;
    memset(&hadc->Init, 0, sizeof(hadc->Init));
    
    return  HAL_OK;
}
    
/************************************************************************
 * function   : HAL_ADC_ConfigChannel
 * Description: Config the regular channel
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 *              sConfig : pointer to a ADC_ChannelConfTypeDef structure that contains
 *                     the configuration information for ADC channel
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig)
{    
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
    if(!IS_ADC_ALL_CHANNEL(sConfig->Channel)) return HAL_ERROR;
    if(!IS_ADC_ALL_SMPCLOCK(sConfig->Smp)) return HAL_ERROR;
    if(!IS_ADC_ALL_SEQUENCE(sConfig->Sq)) return HAL_ERROR;

    /* Differential mode set*/
    if(hadc->Init.DiffMode)
    {
        if(sConfig->Channel < 8)
        {
            SET_BIT(hadc->Instance->DIFF,1<<sConfig->Channel);
            SET_BIT(hadc->Instance->SIGN,1<<sConfig->Channel);     //If define differential mode ,set as sign resault
        }
        else
            return HAL_ERROR;
    }
    else if(sConfig->Channel < 8)
    {
        CLEAR_BIT(hadc->Instance->DIFF,1<<sConfig->Channel);
        CLEAR_BIT(hadc->Instance->SIGN,1<<sConfig->Channel);   //If define differential mode ,set as unsign resault
    }

    if((sConfig->Channel >= 8) && (hadc->Instance->DIFF & (1<<(sConfig->Channel-8)))) return HAL_ERROR;

    if(sConfig->RjMode == 0)
    {
        if((sConfig->Sq >= 1)&&(sConfig->Sq <= 5)) 
            MODIFY_REG(hadc->Instance->SQR1,(ADC_CH_MASK << (5*sConfig->Sq )),(sConfig->Channel << (5*sConfig->Sq )));
        else if((sConfig->Sq >= 6)&&(sConfig->Sq <= 11))
            MODIFY_REG(hadc->Instance->SQR2,(ADC_CH_MASK << (5*(sConfig->Sq-6))),(sConfig->Channel << (5*(sConfig->Sq-6))));
        else if((sConfig->Sq >= 12)&&(sConfig->Sq <= 16))
            MODIFY_REG(hadc->Instance->SQR3,(ADC_CH_MASK << (5*(sConfig->Sq-12))),(sConfig->Channel << (5*(sConfig->Sq-12))));
        else
            return HAL_ERROR;
    }
    else
    { 
        /* Inject channel */
        MODIFY_REG(hadc->Instance->JSQR,ADC_CH_MASK,sConfig->Channel);
    }
    
    MODIFY_REG(hadc->Instance->SQR1,ADC_SQR1_L,(ADC_Handle.ChannelNum-1));

    /* Set the SMPR to every register*/
    if(sConfig->Channel <= ADC_CHANNEL_7) 
        MODIFY_REG(hadc->Instance->SMPR1,(ADC_SMPR_CH_MASK << (4*sConfig->Channel )),(sConfig->Smp << (4*sConfig->Channel )));
    else if((sConfig->Channel >= ADC_CHANNEL_8)&&(sConfig->Channel <= ADC_CHANNEL_15))
        MODIFY_REG(hadc->Instance->SMPR2,(ADC_SMPR_CH_MASK << (4*(sConfig->Channel-8))),(sConfig->Smp << (4*(sConfig->Channel-8))));
    else if((sConfig->Channel >= ADC_CHANNEL_TEMP)&&(sConfig->Channel <= ADC_CHANNEL_EXT3))
        MODIFY_REG(hadc->Instance->SMPR3,(ADC_SMPR_CH_MASK << (4*(sConfig->Channel-16))),(sConfig->Smp << (4*(sConfig->Channel-16))));
    else
        return HAL_ERROR;
    
    if(hadc->Init.ChannelEn & ADC_CHANNEL_TEMP_EN)
    {
        SET_BIT(hadc->Instance->TSREF,ADC_TSREF_EN_TS);//Enable the temperature sensor
        System_Delay(1000);
    }    
    
    if(hadc->Init.ChannelEn & (ADC_CHANNEL_VBGR_EN | ADC_CHANNEL_EXT2_EN | ADC_CHANNEL_EXT3_EN))
    {
        SET_BIT(hadc->Instance->CR2,ADC_CR2_EN_BUF);//Enable the buffer
        System_Delay(1000);
    }
    
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_AnalogWDGConfig
 * Description: Config the analog watchdog
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 *              AnalogWDGConfig : pointer to a ADC_AnalogWDGConfTypeDef structure that contains
 *                     the configuration information for ADC analog watchdog
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig)
{                                 
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
    if(!IS_ADC_ALL_CHANNEL(AnalogWDGConfig->Channel)) return HAL_ERROR;
    
    if (hadc->Init.AnalogWDGEn)
    {
        switch(AnalogWDGConfig->WatchdogMode)
        {
                /* AWDSGL:0; AWDEN:1; JAWDEN:0 */
            case ADC_ANALOGWATCHDOG_RCH_ALL:
                CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_AWDSGL);
                SET_BIT(hadc->Instance->CR1,ADC_CR1_AWDEN);
                CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_JAWDEN);
                break;
                /* AWDSGL:0; AWDEN:0; JAWDEN:1 */
            case ADC_ANALOGWATCHDOG_JCH_ALL:
                CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_AWDSGL);
                CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_AWDEN);
                SET_BIT(hadc->Instance->CR1,ADC_CR1_JAWDEN);
                break;
                /* AWDSGL:0; AWDEN:1; JAWDEN:1 */
            case ADC_ANALOGWATCHDOG_RCH_AND_JCH_ALL:
                CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_AWDSGL);
                SET_BIT(hadc->Instance->CR1,ADC_CR1_AWDEN);
                SET_BIT(hadc->Instance->CR1,ADC_CR1_JAWDEN);
                break;
                /* AWDSGL:1; AWDEN:1; JAWDEN:0 */
            case ADC_ANALOGWATCHDOG_RCH_SINGLE:
                SET_BIT(hadc->Instance->CR1,ADC_CR1_AWDSGL);
                SET_BIT(hadc->Instance->CR1,ADC_CR1_AWDEN);
                CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_JAWDEN);
                MODIFY_REG(hadc->Instance->CR1,ADC_CH_MASK,AnalogWDGConfig->Channel);  //The regular watchdog channel set
                break;
                /* AWDSGL:1; AWDEN:0; JAWDEN:1 */
            case ADC_ANALOGWATCHDOG_JCH_SINGLE:
                SET_BIT(hadc->Instance->CR1,ADC_CR1_AWDSGL);
                CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_AWDEN);
                SET_BIT(hadc->Instance->CR1,ADC_CR1_JAWDEN);   
                MODIFY_REG(hadc->Instance->CR1,(ADC_CH_MASK<<27),AnalogWDGConfig->Channel<<27);  //The inject watchdog channel set
                break;
                /* AWDSGL:1; AWDEN:1; JAWDEN:1 */
            case ADC_ANALOGWATCHDOG_RCH_OR_JCH_SINGLE:
                SET_BIT(hadc->Instance->CR1,ADC_CR1_AWDSGL);
                SET_BIT(hadc->Instance->CR1,ADC_CR1_AWDEN);
                SET_BIT(hadc->Instance->CR1,ADC_CR1_JAWDEN);
                MODIFY_REG(hadc->Instance->CR1,ADC_CH_MASK,AnalogWDGConfig->Channel);  //The regular watchdog channel set
                MODIFY_REG(hadc->Instance->CR1,(ADC_CH_MASK<<27),AnalogWDGConfig->Channel<<27);  //The inject watchdog channel set
                break;

                /* AWDSGL:x; AWDEN:0; JAWDEN:0 */
            default: /* ADC_ANALOGWATCHDOG_NONE */
                CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_AWDEN);
                CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_JAWDEN);
                break;
        }
      
          /* Configure ADC analog watchdog interrupt */
        if(AnalogWDGConfig->ITMode)
            __HAL_ADC_ENABLE_IT(hadc,ADC_IE_AWDIE);
        else
            __HAL_ADC_DISABLE_IT(hadc,ADC_IE_AWDIE);
    }
    
    if(hadc->Init.DiffMode)
    {
        hadc->Instance->HTR = AnalogWDGConfig->HighThreshold<<16;
        hadc->Instance->LTR = AnalogWDGConfig->LowThreshold<<16;
    }
    else
    {
        hadc->Instance->HTR = AnalogWDGConfig->HighThreshold;
        hadc->Instance->LTR = AnalogWDGConfig->LowThreshold;
    }
    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_Start
 * Description: Enable and start the ADC convertion
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
    
    /* check the total number of the enabled channels */
    if((READ_BIT(hadc->Instance->SQR1,ADC_SQR1_L)+1) != hadc->ChannelNum) return HAL_ERROR;
    
    /* Enable the ADC */
    __HAL_ADC_ENABLE(hadc);

    /* Clear the SR register */
    __HAL_ADC_CLEAR_FLAG(hadc,ADC_SR_AWD | ADC_SR_OVERF | ADC_SR_EOG | ADC_SR_JEOC | ADC_SR_EOC | ADC_SR_ADRDY);

    /* Wait ADC ready */
    while(!(hadc->Instance->SR & ADC_SR_ADRDY));
    
    if(__HAL_ADC_CHECK_TRIG_REGULAR(hadc, ADC_SOFTWARE_START))
    {
        /* Start covertion */
        SET_BIT(hadc->Instance->CR1,ADC_CR1_SWSTART);
    }
    
    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_Stop
 * Description: Stop ADC conversion of regular group (and injected channels in 
 *              case of auto_injection mode), disable ADC peripheral.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc)
{
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
  
    if(hadc->Init.ConConvMode)
    {
        /* Set stop flag */
        SET_BIT(hadc->Instance->CR2, ADC_CR2_ADC_STP);        
        /* Waitting stop flag be cleared */    
        while(READ_BIT(hadc->Instance->CR2, ADC_CR2_ADC_STP));
    }
    
    /* Disable the ADC peripheral */
    __HAL_ADC_DISABLE(hadc);

    /* Clear the SR register */
    __HAL_ADC_CLEAR_FLAG(hadc,ADC_SR_AWD | ADC_SR_OVERF | ADC_SR_EOG | ADC_SR_JEOC | ADC_SR_EOC | ADC_SR_ADRDY);

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_Start_IT
 * Description: Enable ADC, start conversion of regular group with interruption.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc)
{  
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
      
    /* Enable the ADC */
    __HAL_ADC_ENABLE(hadc);

    /* Clear the SR register */
    __HAL_ADC_CLEAR_FLAG(hadc,ADC_SR_AWD | ADC_SR_OVERF | ADC_SR_EOG | ADC_SR_JEOC | ADC_SR_EOC | ADC_SR_ADRDY);      
      
    /* Disable all interruptions before enabling the desired ones */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IE_EOCIE | ADC_IE_EOGIE | ADC_IE_OVERFIE | ADC_IE_JEOCIE);  
    
    __HAL_ADC_ENABLE_IT(hadc, ADC_IE_EOCIE | ADC_IE_EOGIE);
    
      
    /* Enable ADC overrun interrupt */
    /* If hadc->Init.OverMode is set to ADC_OVERMODE_DISABLE, only then is
     ADC_IE_OVERFIE enabled; otherwise data overwrite is considered as normal
     behavior and no CPU time is lost for a non-processed interruption */
    if (hadc->Init.OverMode == ADC_OVERMODE_DISABLE)
    {
        __HAL_ADC_ENABLE_IT(hadc, ADC_IE_OVERFIE);
    }
      
    if(__HAL_ADC_CHECK_TRIG_REGULAR(hadc, ADC_SOFTWARE_START))
    {
        /* Start covertion */
        SET_BIT(hadc->Instance->CR1,ADC_CR1_SWSTART);
    }
  
    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_Stop_IT
 * Description: Stop ADC conversion of regular group (and injected group in 
 *              case of auto_injection mode), disable interrution of 
 *              end-of-conversion, disable ADC peripheral.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc)
{
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
  
    if(hadc->Init.ConConvMode)
    {
        /* Set stop flag */
        SET_BIT(hadc->Instance->CR2, ADC_CR2_ADC_STP);        
        /* Waitting stop flag be cleared */    
        while(READ_BIT(hadc->Instance->CR2, ADC_CR2_ADC_STP));
    }
 
    /* Disable the ADC peripheral */
    __HAL_ADC_DISABLE(hadc);

    /* Disable all interruptions before enabling the desired ones */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IE_EOCIE | ADC_IE_EOGIE | ADC_IE_OVERFIE | ADC_IE_JEOCIE);  

    /* Clear the SR register */
    __HAL_ADC_CLEAR_FLAG(hadc,ADC_SR_AWD | ADC_SR_OVERF | ADC_SR_EOG | ADC_SR_JEOC | ADC_SR_EOC | ADC_SR_ADRDY);

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_Start_DMA
 * Description: Enable ADC, start conversion of regular group and transfer result through DMA.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 *            : pData : Destination Buffer address.
 *            : Length : Number of data to be transferred from ADC peripheral to memory.
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length)
{
    HAL_StatusTypeDef tmp_hal_status;
  
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
      
    /* Specific case for first call occurrence of this function (DMA transfer */
    /* not activated and ADC disabled), DMA transfer must be activated        */
    /* with ADC disabled.                                                     */
    if (READ_BIT(hadc->Instance->CR1,ADC_CR1_DMA) == 0UL)
    {
      if(READ_BIT(hadc->Instance->CR2, ADC_CR2_ADC_EN))
      {
        /* Disable ADC */
        __HAL_ADC_DISABLE(hadc);
      }
      
      /* Enable ADC DMA mode */
      SET_BIT(hadc->Instance->CR1,ADC_CR1_DMA);
    }
    
    /* Enable the ADC peripheral */
    __HAL_ADC_ENABLE(hadc);
    
    /* Clear the SR register */
    __HAL_ADC_CLEAR_FLAG(hadc,ADC_SR_AWD | ADC_SR_OVERF | ADC_SR_EOG | ADC_SR_JEOC | ADC_SR_EOC | ADC_SR_ADRDY);      
      
    /* Disable all interruptions before enabling the desired ones */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IE_EOCIE | ADC_IE_EOGIE | ADC_IE_OVERFIE | ADC_IE_JEOCIE);  
           
    /* Start the DMA channel */
    tmp_hal_status = HAL_DMA_Start_IT(hadc->DMA_Handle, (uint32_t)&hadc->Instance->DR, (uint32_t)pData, Length);

    /* Enable conversion of regular group.                                  */
    /* If software start has been selected, conversion starts immediately.  */
    /* If external trigger has been selected, conversion will start at next */
    /* trigger event.                                                       */
    
    /* Start ADC group regular conversion */
    if(__HAL_ADC_CHECK_TRIG_REGULAR(hadc, ADC_SOFTWARE_START))
    {
        /* Start covertion */
        SET_BIT(hadc->Instance->CR1,ADC_CR1_SWSTART);
    }
  
    /* Return function status */
    return tmp_hal_status;
}

/************************************************************************
 * function   : HAL_ADC_Stop_DMA
 * Description: Stop ADC conversion of regular group (and injected group in 
 *              case of auto_injection mode), disable ADC DMA transfer, disable 
 *              ADC peripheral.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc)
{  
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
    
    if(hadc->Init.ConConvMode)
    {
        /* Set stop flag */
        SET_BIT(hadc->Instance->CR2, ADC_CR2_ADC_STP);        
        /* Waitting stop flag be cleared */    
        while(READ_BIT(hadc->Instance->CR2, ADC_CR2_ADC_STP));
    }
    
    /* Waitting stop flag be cleared */    
    while(READ_BIT(hadc->Instance->CR2, ADC_CR2_ADC_STP));

    /* Disable the DMA channel (in case of DMA in circular mode or stop       */
    /* while DMA transfer is on going)                                        */
    HAL_DMA_Abort(hadc->DMA_Handle);
    
    /* Disable ADC overrun interrupt */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IE_OVERFIE);
    
    /* 2. Disable the ADC peripheral */
    /* Update "tmp_hal_status" only if DMA channel disabling passed, to keep  */
    /* in memory a potential failing status.                                  */

    /* Disable the ADC peripheral */
    __HAL_ADC_DISABLE(hadc);

    /* Disable all interruptions before enabling the desired ones */
    __HAL_ADC_DISABLE_IT(hadc, ADC_IE_EOCIE | ADC_IE_EOGIE | ADC_IE_OVERFIE | ADC_IE_JEOCIE);  

    /* Clear the SR register */
    __HAL_ADC_CLEAR_FLAG(hadc,ADC_SR_AWD | ADC_SR_OVERF | ADC_SR_EOG | ADC_SR_JEOC | ADC_SR_EOC | ADC_SR_ADRDY);

    /* Disable ADC DMA (ADC DMA configuration of continuous requests is kept) */
    CLEAR_BIT(hadc->Instance->CR1,ADC_CR1_DMA);

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_GetValue
 * Description: ADC retrieve conversion value intended to be used with polling or interruption
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : uint32_t the ADC covert result.
 ************************************************************************/
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc)
{
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
    
    return (hadc->Instance->DR);
}

/************************************************************************
 * function   : HAL_ADC_PollForEvent
 * Description: Poll for ADC event.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 *            : EventType: the ADC event type. can be ：ADC_SR_AWD,ADC_SR_OVERF,ADC_SR_EOG,ADC_SR_JEOC,ADC_SR_EOC
 *            : Timeout : Polling timeout.
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout)
{
    __IO uint32_t uiTimeout;
    
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
    if(!IS_ADC_EVENT_TYPE(EventType)) return HAL_ERROR;

    uiTimeout = Timeout;
    /* Check selected event flag */
    while (__HAL_ADC_GET_FLAG(hadc, EventType) == 0UL)
    {
        /* Check if timeout is disabled (set to infinite wait) */
        if(uiTimeout)
        {
            uiTimeout--;
            if(uiTimeout == 0)
                return HAL_TIMEOUT;
        }
    }

    if(EventType == ADC_SR_OVERF)
    {
        __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_OVERF);
        if (hadc->Init.OverMode == ADC_OVERMODE_ENABLE)
        {
            /* Clear ADC Overrun flag only if Overrun is set to ADC_OVERMODE_ENABLE(Over written) */
            return HAL_ERROR;
        }
    }
    else
    {
        __HAL_ADC_CLEAR_FLAG(hadc, EventType);
    }

    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_InjectedStart_IT
 * Description: Enable ADC, start conversion of injected channel with interruption.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_InjectedStart_IT(ADC_HandleTypeDef* hadc)
{  
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;

    /* Clear the SR register */
    __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_JEOC);      
            
    __HAL_ADC_ENABLE_IT(hadc, ADC_IE_JEOCIE);    
      
    /* Enable ADC overrun interrupt */
    /* If hadc->Init.OverMode is set to ADC_OVERMODE_DISABLE, only then is
     ADC_IE_OVERFIE enabled; otherwise data overwrite is considered as normal
     behavior and no CPU time is lost for a non-processed interruption */
    if (hadc->Init.OverMode == ADC_OVERMODE_DISABLE)
    {
        __HAL_ADC_ENABLE_IT(hadc, ADC_IE_OVERFIE);
    }
      
    if(__HAL_ADC_CHECK_TRIG_INJECTED(hadc, ADC_SOFTWARE_START))
    {
        /* Start covertion */
        SET_BIT(hadc->Instance->CR1,ADC_CR1_JSWSTART);
    }
  
    /* Return function status */
    return HAL_OK;
}

/************************************************************************
 * function   : HAL_ADC_InjectedStop_IT
 * Description: Stop ADC conversion of injected channel, disable interrution of 
 *              end-of-conversion, disable ADC peripheral.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_InjectedStop_IT(ADC_HandleTypeDef* hadc)
{
    /* Return function status */
    return (HAL_ADC_Stop_IT(hadc));
}

/************************************************************************
 * function   : HAL_ADC_InjectedGetValue
 * Description: ADC retrieve injected channel conversion value intended to be used with polling or interruption
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 * return     : uint32_t the ADC covert result.
 ************************************************************************/
uint32_t HAL_ADC_InjectedGetValue(ADC_HandleTypeDef *hadc)
{
    /* Check the parameters */
    if(!IS_ADC_ALL_INSTANCE(hadc->Instance)) return HAL_ERROR;
    
    return (hadc->Instance->JDR);
}

/************************************************************************
 * function   : HAL_ADC_Polling
 * Description: Polling to get the results of the ADC converter.
 * input      : hadc : pointer to a ADC_HandleTypeDef structure that contains
 *                     the configuration information for ADC module
 *            : pData : Destination Buffer address.
 *            : Length : Number of data to be transferred from ADC peripheral to memory.
 *            : Timeout : Polling timeout.
 * return     : HAL_StatusTypeDef
 ************************************************************************/
HAL_StatusTypeDef HAL_ADC_Polling(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length, uint32_t Timeout)
{
    uint32_t tmp_hal_status;
    __IO uint32_t uiTimeout;    

    if(HAL_ADC_Start(hadc) != HAL_OK)  return HAL_ERROR; 
    if(!pData)  return HAL_ERROR;
    
    hadc->AdcResults = pData;
    uiTimeout = Timeout;
    
    while(Length)
    {
        tmp_hal_status = hadc->Instance->SR;
        if(tmp_hal_status & ADC_SR_EOC)
        {
            *hadc->AdcResults = hadc->Instance->DR | HAL_ADC_EOC_FLAG;
             __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_EOC);
       
            hadc->AdcResults++;
            Length--;
        }
        if(tmp_hal_status & ADC_SR_JEOC)
        {
            *hadc->AdcResults = hadc->Instance->JDR | HAL_ADC_JEOC_FLAG;
             __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_JEOC);
            hadc->AdcResults++;
            Length--;
        }
        if(tmp_hal_status & ADC_SR_OVERF)
        {
            __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_OVERF);
        }        
        if(tmp_hal_status & ADC_SR_EOG)
        {
            __HAL_ADC_CLEAR_FLAG(hadc, ADC_SR_EOG);
            break;
        }
        
        if(uiTimeout)
        {
            uiTimeout--;
            if(uiTimeout == 0)
                return HAL_TIMEOUT;
        }
    }
    
    HAL_ADC_Stop(hadc); 
    
    return HAL_OK;
}
