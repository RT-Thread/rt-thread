/**
  ******************************************************************************
  * @brief   ADC functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_adc.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup ADC
  * @brief ADC driver modules
  * @{
  */

/** @defgroup ADC_Private_Defines
  * @{
  */

/* ADC CTLR1_DISNUM mask */
#define CTLR1_DISNUM_RESET              ((uint32_t)0xFFFF1FFF)

/* ADC CTLR1_DISRC mask */
#define CTLR1_DISRC_SET                 ((uint32_t)0x00000800)

/* ADC CTLR1_ICA mask */
#define CTLR1_ICA_SET                   ((uint32_t)0x00000400)

/* ADC CTLR1_DISIC mask */
#define CTLR1_DISIC_SET                 ((uint32_t)0x00001000)

/* ADC CTLR1_AWCS mask */
#define CTLR1_AWCS_RESET                ((uint32_t)0xFFFFFFE0)

/* ADC CTLR1_AWDMode mask */
#define CTLR1_AWDMODE_RESET             ((uint32_t)0xFF3FFDFF)

/* CTLR1 register mask */
#define CTLR1_BITS_CLEAR                ((uint32_t)0xFFF0FEFF)

/* ADC CTLR2_ADCON mask */
#define CTLR2_ADCON_SET                 ((uint32_t)0x00000001)

/* ADC CTLR2_DMA mask */
#define CTLR2_DMA_SET                   ((uint32_t)0x00000100)

/* ADC CTLR2_RSTCLB mask */
#define CTLR2_RSTCLB_SET                ((uint32_t)0x00000008)

/* ADC CTLR2_CLB mask */
#define CTLR2_CLB_SET                   ((uint32_t)0x00000004)

/* ADC CTLR2_SWRCST mask */
#define CTLR2_SWRCST_SET                ((uint32_t)0x00400000)

/* ADC CTLR2_ETERC mask */
#define CTLR2_ETERC_SET                 ((uint32_t)0x00100000)

/* ADC CTLR2_ETERC_SWRCST mask */
#define CTLR2_ETERC_SWRCST_SET          ((uint32_t)0x00500000)

/* ADC CTLR2_ETSIC mask */
#define CTLR2_ETSIC_RESET               ((uint32_t)0xFFFF8FFF)

/* ADC CTLR2_ETEIC mask */
#define CTLR2_ETEIC_SET                 ((uint32_t)0x00008000)

/* ADC CTLR2_SWICST mask */
#define CTLR2_SWICST_SET                ((uint32_t)0x00200000)

/* ADC CTLR2_ETEIC_SWICST mask */
#define CTLR2_ETEIC_SWICST_SET          ((uint32_t)0x00208000)

/* ADC CTLR2_TSVREN mask */
#define CTLR2_TSVREN_SET                ((uint32_t)0x00800000)

/* CTLR2 register mask */
#define CTLR2_BITS_CLEAR                ((uint32_t)0xFFF1F7FD)

/* ADC RSQx mask */
#define RSQ3_RSQ_SET                    ((uint32_t)0x0000001F)
#define RSQ2_RSQ_SET                    ((uint32_t)0x0000001F)
#define RSQ1_RSQ_SET                    ((uint32_t)0x0000001F)

/* RSQ1 register mask */
#define RSQ1_BITS_CLEAR                 ((uint32_t)0xFF0FFFFF)

/* ADC ISQx mask */
#define ISQ_ISQ_SET                     ((uint32_t)0x0000001F)

/* ADC IL mask */
#define ISQ_IL_SET                      ((uint32_t)0x00300000)

/* ADC SPTx mask */
#define SPT1_SPT_SET                    ((uint32_t)0x00000007)
#define SPT2_SPT_SET                    ((uint32_t)0x00000007)

/* ADC IDTRx registers offset */
#define IDTR_OFFSET                     ((uint8_t)0x28)

/* ADC0 RDTR register base address */
#define RDTR_ADDRESS                    ((uint32_t)0x4001244C)

/**
  * @}
  */

/** @defgroup ADC_Private_Functions
  * @{
  */

/**
  * @brief  Reset the ADC interface and init the sturct ADC_InitPara.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_InitParaStruct : the sturct ADC_InitPara pointer.
  * @retval None
  */
void ADC_DeInit(ADC_TypeDef *ADCx, ADC_InitPara *ADC_InitParaStruct)
{
    if (ADCx == ADC0) {
        /* Enable ADC0 reset state */
        RCC_APB2PeriphReset_Enable(RCC_APB2PERIPH_ADC0RST, ENABLE);
        /* Release ADC0 from reset state */
        RCC_APB2PeriphReset_Enable(RCC_APB2PERIPH_ADC0RST, DISABLE);
    } else if (ADCx == ADC1) {
        /* Enable ADC1 reset state */
        RCC_APB2PeriphReset_Enable(RCC_APB2PERIPH_ADC1RST, ENABLE);
        /* Release ADC1 from reset state */
        RCC_APB2PeriphReset_Enable(RCC_APB2PERIPH_ADC1RST, DISABLE);
    }
    /* Initialize the ADC_Mode member,independent mode */
    ADC_InitParaStruct->ADC_Mode = ADC_MODE_INDEPENDENT;
    /* Initialize the ADC_Mode_Scan member,disable scan mode */
    ADC_InitParaStruct->ADC_Mode_Scan = DISABLE;
    /* Initialize the ADC_Mode_Continuous member,disable continuous mode */
    ADC_InitParaStruct->ADC_Mode_Continuous = DISABLE;
    /* Initialize the ADC_Trig_External member,choose T1 CC1 as external trigger */
    ADC_InitParaStruct->ADC_Trig_External = ADC_EXTERNAL_TRIGGER_MODE_T1_CC1;
    /* Initialize the ADC_Data_Align member,specifies the ADC data alignment right */
    ADC_InitParaStruct->ADC_Data_Align = ADC_DATAALIGN_RIGHT;
    /* Initialize the ADC_Channel_Number member,only 1 channel */
    ADC_InitParaStruct->ADC_Channel_Number = 1;
}

/**
  * @brief  Initialize the ADCx interface parameters.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_InitParaStruct: the sturct ADC_InitPara pointer.
  * @retval None
  */
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitPara *ADC_InitParaStruct)
{
    uint32_t temp1 = 0;
    uint8_t temp2 = 0;
    /* ADCx CTLR1 Configuration */
    /* Get the ADCx CTLR1 previous value */
    temp1 = ADCx->CTLR1;
    /* Clear SM bits */
    temp1 &= CTLR1_BITS_CLEAR;
    /* Configure ADCx: Dual mode and scan conversion mode */
    /* Set DUALMOD bits according to ADC_Mode value */
    /* Configure SCAN bit according to ADC_Mode_Scan value */
    temp1 |= (uint32_t)(ADC_InitParaStruct->ADC_Mode | ((uint32_t)ADC_InitParaStruct->ADC_Mode_Scan << 8));
    /* Write new value to ADCx CTLR1 */
    ADCx->CTLR1 = temp1;

    /* ADCx CTLR2 Configuration */
    /* Get the ADCx CTLR2 previous value */
    temp1 = ADCx->CTLR2;
    /* Clear CTN, DAL and ETSRC bits */
    temp1 &= CTLR2_BITS_CLEAR;
    /* Configure ADCx: select external trigger mode and continuous conversion mode */
    /* Configure DAL bit according to ADC_Data_Align value */
    /* Configure ETSRC bits according to ADC_Trig_External value */
    /* Configure CTN bit according to ADC_Mode_Continuous value */
    temp1 |= (uint32_t)(ADC_InitParaStruct->ADC_Data_Align | ADC_InitParaStruct->ADC_Trig_External |
                        ((uint32_t)ADC_InitParaStruct->ADC_Mode_Continuous << 1));
    /* Write new value to ADCx CTLR2 */
    ADCx->CTLR2 = temp1;

    /* ADCx RSQ1 Configuration */
    /* Get the ADCx RSQ1 previous value */
    temp1 = ADCx->RSQ1;
    /* Clear RL bits */
    temp1 &= RSQ1_BITS_CLEAR;
    /* Configure ADCx: regular channel sequence length */
    /* Configure RL bits according to ADC_Channel_Number value */
    temp2 |= (uint8_t)(ADC_InitParaStruct->ADC_Channel_Number - (uint8_t)1);
    temp1 |= (uint32_t)temp2 << 20;
    /* Write new value to ADCx RSQ1 */
    ADCx->RSQ1 = temp1;
}

/**
  * @brief  Enable or disable the ADCx interface.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  NewValue: New state of the ADCx interface.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Enable(ADC_TypeDef *ADCx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the ADCx interface */
        ADCx->CTLR2 |= CTLR2_ADCON_SET;
    } else {
        /* Disable the ADCx interface */
        ADCx->CTLR2 &= ~CTLR2_ADCON_SET;
    }
}

/**
  * @brief  Enable or disable the ADCx DMA request.
  * @param  ADCx: the ADC interface where x can be 1..3.
  *   Note: ADC1 doesn't support DMA function.
  * @param  NewValue: New state of ADCx DMA transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DMA_Enable(ADC_TypeDef *ADCx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable ADCx DMA request */
        ADCx->CTLR2 |= CTLR2_DMA_SET;
    } else {
        /* Disable ADCx DMA request */
        ADCx->CTLR2 &= ~CTLR2_DMA_SET;
    }
}

/**
  * @brief  Enable or disable ADCx interrupts.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_INT: ADCx interrupt sources.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_INT_EOC: Regular conversion over interrupt mask
  *     @arg ADC_INT_AWE: Analog watchdog interrupt mask
  *     @arg ADC_INT_EOIC: Inserted conversion over interrupt mask
  * @param  NewValue: ADCx interrupts state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_INTConfig(ADC_TypeDef *ADCx, uint16_t ADC_INT, TypeState NewValue)
{
    uint8_t temp_it = 0;
    /* ADCx INT old state */
    temp_it = (uint8_t)ADC_INT;
    if (NewValue != DISABLE) {
        /* Enable the ADCx interrupt */
        ADCx->CTLR1 |= temp_it;
    } else {
        /* Disable the ADCx interrupt */
        ADCx->CTLR1 &= (~(uint32_t)temp_it);
    }
}

/**
  * @brief  ADCx calibration.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @retval None
  */
void ADC_Calibration(ADC_TypeDef *ADCx)
{
    /* Reset the selected ADCx calibration registers */
    ADCx->CTLR2 |= CTLR2_RSTCLB_SET;
    /* Check the RSTCLB bit state */
    while ((ADCx->CTLR2 & CTLR2_RSTCLB_SET));
    /* Enable ADCx calibration process */
    ADCx->CTLR2 |= CTLR2_CLB_SET;
    /* Check the CLB bit state */
    while ((ADCx->CTLR2 & CTLR2_CLB_SET) != (uint32_t)RESET);
}

/**
  * @brief  Enable or disable ADCx software start conversion.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  NewValue: ADCx software start conversion state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SoftwareStartConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* ADCx software conversion start */
        ADCx->CTLR2 |= CTLR2_ETERC_SWRCST_SET;
    } else {
        /* ADCx software conversion stop */
        ADCx->CTLR2 &= ~CTLR2_ETERC_SWRCST_SET;
    }
}

/**
  * @brief  Get the bit state of ADCx software start conversion.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @retval ADCx software start conversion state(SET or RESET).
  */
TypeState ADC_GetSoftwareStartConvBitState(ADC_TypeDef *ADCx)
{
    /* Check the SWRCST bit state*/
    if ((ADCx->CTLR2 & CTLR2_SWRCST_SET) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Configure the ADCx channel discontinuous mode.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  Number: the count value of discontinuous mode regular channel.
  *         This number must be 1~8.
  * @retval None
  */
void ADC_DiscModeChannelCount_Config(ADC_TypeDef *ADCx, uint8_t Number)
{
    uint32_t temp1 = 0;
    uint32_t temp2 = 0;
    /* Get the old value of CTLR1 */
    temp1 = ADCx->CTLR1;
    /* Clear discontinuous mode channel count */
    temp1 &= CTLR1_DISNUM_RESET;
    /* Set the discontinuous mode channel count */
    temp2 = Number - 1;
    temp1 |= temp2 << 13;
    /* Write new value to CTLR1 */
    ADCx->CTLR1 = temp1;
}

/**
  * @brief  Enable or disable the discontinuous mode.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  NewValue: ADCx discontinuous mode state.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DiscMode_Enable(ADC_TypeDef *ADCx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable ADCx regular discontinuous mode */
        ADCx->CTLR1 |= CTLR1_DISRC_SET;
    } else {
        /* Disable ADCx regular discontinuous mode */
        ADCx->CTLR1 &= ~CTLR1_DISRC_SET;
    }
}

/**
  * @brief  Configure array and sample time.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_Channel: the selected ADC channel.
  *   This parameter can be as follows:
  *     @arg ADC_CHANNEL_0: ADC Channel0
  *     @arg ADC_CHANNEL_1: ADC Channel1
  *     @arg ADC_CHANNEL_2: ADC Channel2
  *     @arg ADC_CHANNEL_3: ADC Channel3
  *     @arg ADC_CHANNEL_4: ADC Channel4
  *     @arg ADC_CHANNEL_5: ADC Channel5
  *     @arg ADC_CHANNEL_6: ADC Channel6
  *     @arg ADC_CHANNEL_7: ADC Channel7
  *     @arg ADC_CHANNEL_8: ADC Channel8
  *     @arg ADC_CHANNEL_9: ADC Channel9
  *     @arg ADC_CHANNEL_10: ADC Channel10
  *     @arg ADC_CHANNEL_11: ADC Channel11
  *     @arg ADC_CHANNEL_12: ADC Channel12
  *     @arg ADC_CHANNEL_13: ADC Channel13
  *     @arg ADC_CHANNEL_14: ADC Channel14
  *     @arg ADC_CHANNEL_15: ADC Channel15
  *     @arg ADC_CHANNEL_16: ADC Channel16
  *     @arg ADC_CHANNEL_17: ADC Channel17
  * @param  Array: The regular group sequencer rank. This parameter must be between 1 to 16.
  * @param  ADC_SampleTime: The sample time value.
  *   This parameter can be one of the following values:
  *     @arg ADC_SAMPLETIME_1POINT5: 1.5 cycles
  *     @arg ADC_SAMPLETIME_7POINT5: 7.5 cycles
  *     @arg ADC_SAMPLETIME_13POINT5: 13.5 cycles
  *     @arg ADC_SAMPLETIME_28POINT5: 28.5 cycles
  *     @arg ADC_SAMPLETIME_41POINT5: 41.5 cycles
  *     @arg ADC_SAMPLETIME_55POINT5: 55.5 cycles
  *     @arg ADC_SAMPLETIME_71POINT5: 71.5 cycles
  *     @arg ADC_SAMPLETIME_239POINT5: 239.5 cycles
  * @retval None
  */
void ADC_RegularChannel_Config(ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Array, uint8_t ADC_SampleTime)
{
    uint32_t temp1 = 0, temp2 = 0;

    /* if ADC_Channel is between 10 to 17 */
    if (ADC_Channel > ADC_CHANNEL_9) {
        /* Get SPT1 value */
        temp1 = ADCx->SPT1;
        /* Calculate the mask to clear */
        temp2 = SPT1_SPT_SET << (3 * (ADC_Channel - 10));
        /* Clear sample time */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
        /* Configure sample time */
        temp1 |= temp2;
        /* Write to SPT1 */
        ADCx->SPT1 = temp1;
    } else { /* ADC_Channel is between 0 to 9 */
        /* Get SPT2 value */
        temp1 = ADCx->SPT2;
        /* Calculate the mask to clear */
        temp2 = SPT2_SPT_SET << (3 * ADC_Channel);
        /* Clear sample time */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
        /* Set sample time */
        temp1 |= temp2;
        /* Write to SPT2 */
        ADCx->SPT2 = temp1;
    }
    /* For Array 1 to 6 */
    if (Array < 7) {
        /* Get RSQ3 value */
        temp1 = ADCx->RSQ3;
        /* Calculate the mask to clear */
        temp2 = RSQ3_RSQ_SET << (5 * (Array - 1));
        /* Clear RSQ3 bits */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_Channel << (5 * (Array - 1));
        /* Configure the RSQ3 bits */
        temp1 |= temp2;
        /* Write to RSQ3 */
        ADCx->RSQ3 = temp1;
    }
    /* For Array 7 to 12 */
    else if (Array < 13) {
        /* Get RSQ2 value */
        temp1 = ADCx->RSQ2;
        /* Calculate the mask to clear */
        temp2 = RSQ2_RSQ_SET << (5 * (Array - 7));
        /* Clear the old RSQ2 bits */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_Channel << (5 * (Array - 7));
        /* Set the RSQ2 bits  */
        temp1 |= temp2;
        /* Write to RSQ2 */
        ADCx->RSQ2 = temp1;
    }
    /* For Array 13 to 16 */
    else {
        /* Get RSQ1 value */
        temp1 = ADCx->RSQ1;
        /* Calculate the mask to clear */
        temp2 = RSQ1_RSQ_SET << (5 * (Array - 13));
        /* Clear the old RSQ1 bits */
        temp1 &= ~temp2;
        /* Calculate the mask to set */
        temp2 = (uint32_t)ADC_Channel << (5 * (Array - 13));
        /* Set the RSQ1 bits */
        temp1 |= temp2;
        /* Write to RSQ1 */
        ADCx->RSQ1 = temp1;
    }
}

/**
  * @brief  Enable or disable the ADCx external conversion.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  NewValue: ADCx external trigger state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ExternalTrigConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable external trigger conversion */
        ADCx->CTLR2 |= CTLR2_ETERC_SET;
    } else {
        /* Disable external trigger conversion */
        ADCx->CTLR2 &= ~CTLR2_ETERC_SET;
    }
}

/**
  * @brief  Return the ADCx regular channel conversion data.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @retval conversion data.
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef *ADCx)
{
    /* Return ADCx conversion data */
    return (uint16_t) ADCx->RDTR;
}

/**
  * @brief  Return the last ADC0 and ADC1 conversion result data in dual mode.
  * @retval The Data conversion value.
  */
uint32_t ADC_GetDualModeConversionValue(void)
{
    /* Return conversion value */
    return (*(__IO uint32_t *) RDTR_ADDRESS);
}
/**
  * @brief  Enable or disable ADCx automatic inserted conversion.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  NewValue: ADCx auto inserted conversion state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AutoInsertedConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable ADCx automatic inserted conversion */
        ADCx->CTLR1 |= CTLR1_ICA_SET;
    } else {
        /* Disable ADCx automatic inserted conversion */
        ADCx->CTLR1 &= ~CTLR1_ICA_SET;
    }
}

/**
  * @brief  Enable or disable the discontinuous mode for ADCx inserted group channel.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  NewValue: ADCx discontinuous mode state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_InsertedDiscMode_Enable(ADC_TypeDef *ADCx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the inserted discontinuous mode of the selected ADC channel */
        ADCx->CTLR1 |= CTLR1_DISIC_SET;
    } else {
        /* Disable the inserted discontinuous mode of the selected ADC channel */
        ADCx->CTLR1 &= ~CTLR1_DISIC_SET;
    }
}

/**
  * @brief  Configure the ADCx inserted channels external trigger conversion.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_ExternalTrigInsertConv: ADC inserted conversion trigger.
  *   This parameter can be as follows:
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T1_TRGO: Timer1 TRIG event (used in ADC0, ADC1 and ADC2)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T1_CC4: Timer1 capture compare4 (used in ADC0, ADC1 and ADC2)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T2_TRGO: Timer2 TRIG event (used in ADC0 and ADC1)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T2_CC1: Timer2 capture compare1 (used in ADC0 and ADC1)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T3_CC4: Timer3 capture compare4 (used in ADC0 and ADC1)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T4_TRGO: Timer4 TRIG event (used in ADC0 and ADC1)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_EXT_IT15_T8_CC4: External interrupt line 15 or Timer8
  *          capture compare4 (used in ADC0 and ADC1)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T4_CC3: Timer4 capture compare3 (used in ADC2)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T8_CC2: Timer8 capture compare2 (used in ADC2)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T8_CC4: Timer8 capture compare4 (used in ADC2)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T5_TRGO: Timer5 TRIG event (used in ADC2)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_T5_CC4: Timer5 capture compare4 (used in ADC2)
  *     @arg ADC_EXTERNAL_TRIG_INSERTCONV_NONE: Inserted conversion started by software (used in ADC0, ADC1 and ADC2)
  * @retval None
  */
void ADC_ExternalTrigInsertedConv_Config(ADC_TypeDef *ADCx, uint32_t ADC_ExternalTrigInsertConv)
{
    uint32_t temp = 0;
    /* Get CRLR2 value */
    temp = ADCx->CTLR2;
    /* Clear inserted external event */
    temp &= CTLR2_ETSIC_RESET;
    /* Configure inserted external event */
    temp |= ADC_ExternalTrigInsertConv;
    /* Write to CTLR2 */
    ADCx->CTLR2 = temp;
}

/**
  * @brief  Enable or disable the ADCx inserted channels conversion through
  *         external trigger
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  NewValue: ADCx external trigger start of inserted conversion state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ExternalTrigInsertedConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable external event */
        ADCx->CTLR2 |= CTLR2_ETEIC_SET;
    } else {
        /* Disable external event */
        ADCx->CTLR2 &= ~CTLR2_ETEIC_SET;
    }
}

/**
  * @brief  Enable or disable ADCx inserted channels conversion start.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  NewValue: ADC software start inserted conversion state.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SoftwareStartInsertedConv_Enable(ADC_TypeDef *ADCx, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Start ADCx inserted conversion */
        ADCx->CTLR2 |= CTLR2_ETEIC_SWICST_SET;
    } else {
        /* Stop ADCx inserted conversion */
        ADCx->CTLR2 &= ~CTLR2_ETEIC_SWICST_SET;
    }
}

/**
  * @brief  Get ADC Software start inserted conversion State.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @retval ADC software start inserted conversion state(SET or RESET).
  */
TypeState ADC_GetSoftwareStartInsertedConvCmdBitState(ADC_TypeDef *ADCx)
{
    /* Check SWICST bit */
    if ((ADCx->CTLR2 & CTLR2_SWICST_SET) != (uint32_t)RESET) {
        /* Set SWICST bit */
        return SET;
    } else {
        /* Reset SWICST bit */
        return RESET;
    }
}

/**
  * @brief  Configure Array and sample time for the selected ADC inserted channel.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_Channel: the selected ADC channel.
  *   This parameter can be as follows:
  *     @arg ADC_CHANNEL_0: ADC Channel0
  *     @arg ADC_CHANNEL_1: ADC Channel1
  *     @arg ADC_CHANNEL_2: ADC Channel2
  *     @arg ADC_CHANNEL_3: ADC Channel3
  *     @arg ADC_CHANNEL_4: ADC Channel4
  *     @arg ADC_CHANNEL_5: ADC Channel5
  *     @arg ADC_CHANNEL_6: ADC Channel6
  *     @arg ADC_CHANNEL_7: ADC Channel7
  *     @arg ADC_CHANNEL_8: ADC Channel8
  *     @arg ADC_CHANNEL_9: ADC Channel9
  *     @arg ADC_CHANNEL_10: ADC Channel10
  *     @arg ADC_CHANNEL_11: ADC Channel11
  *     @arg ADC_CHANNEL_12: ADC Channel12
  *     @arg ADC_CHANNEL_13: ADC Channel13
  *     @arg ADC_CHANNEL_14: ADC Channel14
  *     @arg ADC_CHANNEL_15: ADC Channel15
  *     @arg ADC_CHANNEL_16: ADC Channel16
  *     @arg ADC_CHANNEL_17: ADC Channel17
  * @param  Array: The inserted group sequencer Array. This parameter must be between 1 and 4.
  * @param  ADC_SampleTime: The sample time of the selected channel.
  *   This parameter can be as follows:
  *     @arg ADC_SAMPLETIME_1POINT5: 1.5 cycles
  *     @arg ADC_SAMPLETIME_7POINT5: 7.5 cycles
  *     @arg ADC_SAMPLETIME_13POINT5: 13.5 cycles
  *     @arg ADC_SAMPLETIME_28POINT5: 28.5 cycles
  *     @arg ADC_SAMPLETIME_41POINT5: 41.5 cycles
  *     @arg ADC_SAMPLETIME_55POINT5: 55.5 cycles
  *     @arg ADC_SAMPLETIME_71POINT5: 71.5 cycles
  *     @arg ADC_SAMPLETIME_239POINT5: 239.5 cycles
  * @retval None
  */
void ADC_InsertedChannel_Config(ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Array, uint8_t ADC_SampleTime)
{
    uint32_t temp1 = 0, temp2 = 0, temp3 = 0;

    /* if ADC_Channel is between 10 to 17 */
    if (ADC_Channel > ADC_CHANNEL_9) {
        /* Get SPT1 value */
        temp1 = ADCx->SPT1;
        /* Calculate the sample time mask */
        temp2 = SPT1_SPT_SET << (3 * (ADC_Channel - 10));
        /* Clear sample time */
        temp1 &= ~temp2;
        /* Calculate the sample time mask */
        temp2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
        /* Set sample time */
        temp1 |= temp2;
        /* Write to SPT1 */
        ADCx->SPT1 = temp1;
    } else { /* ADC_Channel is between 0 to 9 */
        /* Get SPT2 value */
        temp1 = ADCx->SPT2;
        /* Calculate the sample time mask */
        temp2 = SPT2_SPT_SET << (3 * ADC_Channel);
        /* Clear sample time */
        temp1 &= ~temp2;
        /* Calculate the sample time mask */
        temp2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
        /* Set sample time */
        temp1 |= temp2;
        /* Write to SPT2 */
        ADCx->SPT2 = temp1;
    }
    /* Array configuration */
    /* Get ISQ value */
    temp1 = ADCx->ISQ;
    /* Get IL value: Number = IL+1 */
    temp3 = (temp1 & ISQ_IL_SET) >> 20;
    /* Calculate the ISQ mask : ((Array-1)+(4-IL-1)) */
    temp2 = ISQ_ISQ_SET << (5 * (uint8_t)((Array + 3) - (temp3 + 1)));
    /* Clear ISQx bits */
    temp1 &= ~temp2;
    /* Calculate the ISQ mask: ((Array-1)+(4-IL-1)) */
    temp2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Array + 3) - (temp3 + 1)));
    /* Set ISQx bits  */
    temp1 |= temp2;
    /* Write to ISQ */
    ADCx->ISQ = temp1;
}

/**
  * @brief  Configure the sequencer length of inserted channels
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  Length: The sequencer length.
  *   This parameter must be a number between 1 to 4.
  * @retval None
  */
void ADC_InsertedSequencerLength_Config(ADC_TypeDef *ADCx, uint8_t Length)
{
    uint32_t temp1 = 0;
    uint32_t temp2 = 0;
    /* Get ISQ value */
    temp1 = ADCx->ISQ;
    /* Clear IL bits */
    temp1 &= ~ISQ_IL_SET;
    /* Set IL bits */
    temp2 = Length - 1;
    temp1 |= temp2 << 20;
    /* Write to ISQ */
    ADCx->ISQ = temp1;
}

/**
  * @brief  Set the offset of the inserted channels conversion value.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_InsertedChannel: one of the four inserted channels to set its offset.
  *   This parameter can be one of the following values:
  *     @arg ADC_INSERTEDCHANNEL_1: Inserted Channel1
  *     @arg ADC_INSERTEDCHANNEL_2: Inserted Channel2
  *     @arg ADC_INSERTEDCHANNEL_3: Inserted Channel3
  *     @arg ADC_INSERTEDCHANNEL_4: Inserted Channel4
  * @param  Offset: the offset value of the selected ADC inserted channel
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_SetInsertedOffset(ADC_TypeDef *ADCx, uint8_t ADC_InsertedChannel, uint16_t Offset)
{
    __IO uint32_t temp = 0;
    temp = (uint32_t)ADCx;
    temp += ADC_InsertedChannel;

    /* Set the offset of the selected inserted channel */
    *(__IO uint32_t *) temp = (uint32_t)Offset;
}

/**
  * @brief  Get the ADC inserted channel conversion result
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_InsertedChannel: ADC inserted channel.
  *   This parameter can be one of the following values:
  *     @arg ADC_INSERTEDCHANNEL_1: Inserted Channel1
  *     @arg ADC_INSERTEDCHANNEL_2: Inserted Channel2
  *     @arg ADC_INSERTEDCHANNEL_3: Inserted Channel3
  *     @arg ADC_INSERTEDCHANNEL_4: Inserted Channel4
  * @retval The conversion value.
  */
uint16_t ADC_GetInsertedConversionValue(ADC_TypeDef *ADCx, uint8_t ADC_InsertedChannel)
{
    __IO uint32_t temp = 0;
    temp = (uint32_t)ADCx;
    temp += ADC_InsertedChannel + IDTR_OFFSET;

    /* Return the result of the selected inserted channel conversion */
    return (uint16_t)(*(__IO uint32_t *)  temp);
}

/**
  * @brief  Enable or disable the analog watchdog.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_AnalogWatchdog: the ADC analog watchdog configuration.
  *   This parameter can be one of the following values:
  *     @arg ADC_ANALOGWATCHDOG_SINGLEREGENABLE: single regular channel
  *     @arg ADC_ANALOGWATCHDOG_SINGLEINSERTENABLE: single inserted channel
  *     @arg ADC_ANALOGWATCHDOG_SINGLEREGORINSERTENABLE: single regular or inserted channel
  *     @arg ADC_ANALOGWATCHDOG_ALLREGENABLE: all regular channel
  *     @arg ADC_ANALOGWATCHDOG_ALLINSERTENABLE: all inserted channel
  *     @arg ADC_ANALOGWATCHDOG_ALLREGALLINSERTENABLE: all regular and inserted channels
  *     @arg ADC_ANALOGWATCHDOG_NONE: No channel
  * @retval None
  */
void ADC_AnalogWatchdog_Enable(ADC_TypeDef *ADCx, uint32_t ADC_AnalogWatchdog)
{
    uint32_t temp = 0;
    /* Get CTLR1 value */
    temp = ADCx->CTLR1;
    /* Clear AWDEN, AWDENJ and AWDSGL bits */
    temp &= CTLR1_AWDMODE_RESET;
    /* Set the analog watchdog mode */
    temp |= ADC_AnalogWatchdog;
    /* Write to CTLR1 */
    ADCx->CTLR1 = temp;
}

/**
  * @brief  Configure the high and low thresholds of the analog watchdog.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *   This parameter must be a 12bit value.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *   This parameter must be a 12bit value.
  * @retval None
  */
void ADC_AnalogWatchdogThresholds_Config(ADC_TypeDef *ADCx, uint16_t HighThreshold,
        uint16_t LowThreshold)
{
    /* Set the ADCx high threshold */
    ADCx->AWHT = HighThreshold;
    /* Set the ADCx low threshold */
    ADCx->AWLT = LowThreshold;
}

/**
  * @brief  Configure the analog watchdog on single channel mode.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_Channel: ADC channel.
  *   This parameter can be as follows:
  *     @arg ADC_CHANNEL_0: ADC Channel0
  *     @arg ADC_CHANNEL_1: ADC Channel1
  *     @arg ADC_CHANNEL_2: ADC Channel2
  *     @arg ADC_CHANNEL_3: ADC Channel3
  *     @arg ADC_CHANNEL_4: ADC Channel4
  *     @arg ADC_CHANNEL_5: ADC Channel5
  *     @arg ADC_CHANNEL_6: ADC Channel6
  *     @arg ADC_CHANNEL_7: ADC Channel7
  *     @arg ADC_CHANNEL_8: ADC Channel8
  *     @arg ADC_CHANNEL_9: ADC Channel9
  *     @arg ADC_CHANNEL_10: ADC Channel10
  *     @arg ADC_CHANNEL_11: ADC Channel11
  *     @arg ADC_CHANNEL_12: ADC Channel12
  *     @arg ADC_CHANNEL_13: ADC Channel13
  *     @arg ADC_CHANNEL_14: ADC Channel14
  *     @arg ADC_CHANNEL_15: ADC Channel15
  *     @arg ADC_CHANNEL_16: ADC Channel16
  *     @arg ADC_CHANNEL_17: ADC Channel17
  * @retval None
  */
void ADC_AnalogWatchdogSingleChannel_Config(ADC_TypeDef *ADCx, uint8_t ADC_Channel)
{
    uint32_t temp = 0;
    /* Get CTLR1 value */
    temp = ADCx->CTLR1;
    /* Clear AWCS */
    temp &= CTLR1_AWCS_RESET;
    /* Set the Analog watchdog channel */
    temp |= ADC_Channel;
    /* Write to CTLR1 */
    ADCx->CTLR1 = temp;
}

/**
  * @brief  Enable or disable the temperature sensor and Vrefint channel.
  * @param  NewValue: the state of the temperature sensor.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_TempSensorVrefint_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the temperature sensor and Vrefint channel*/
        ADC0->CTLR2 |= CTLR2_TSVREN_SET;
    } else {
        /* Disable the temperature sensor and Vrefint channel*/
        ADC0->CTLR2 &= ~CTLR2_TSVREN_SET;
    }
}

/**
  * @brief  Check the ADC flag.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_FLAG: the flag to check.
  *   This parameter can be as follows:
  *     @arg ADC_FLAG_AWE: The flag of the analog watchdog
  *     @arg ADC_FLAG_EOC: The flag of the end of conversion
  *     @arg ADC_FLAG_EOIC: The flag of the end of inserted group conversion
  *     @arg ADC_FLAG_STIC: The flag of the start of inserted group conversion
  *     @arg ADC_FLAG_STRC: The flag of the start of regular group conversion
  * @retval ADC_FLAG state(SET or RESET).
  */
TypeState ADC_GetBitState(ADC_TypeDef *ADCx, uint8_t ADC_FLAG)
{
    /* Check the specified ADC flag state */
    if ((ADCx->STR & ADC_FLAG) != (uint8_t)RESET) {
        /* ADC_FLAG is set */
        return SET;
    } else {
        /* ADC_FLAG is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the ADCx's pending flags.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_FLAG: the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_FLAG_AWE: The flag of the analog watchdog
  *     @arg ADC_FLAG_EOC: The flag of the end of conversion
  *     @arg ADC_FLAG_EOIC: The flag of the end of inserted group conversion
  *     @arg ADC_FLAG_STIC: The flag of the start of inserted group conversion
  *     @arg ADC_FLAG_STRC: The flag of the start of regular group conversion
  * @retval None
  */
void ADC_ClearBitState(ADC_TypeDef *ADCx, uint8_t ADC_FLAG)
{
    /* Clear the selected ADC flags */
    ADCx->STR = ~(uint32_t)ADC_FLAG;
}

/**
  * @brief  Check the specified ADC interrupt.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_INT: ADC interrupt source.
  *   This parameter can be one of the following values:
  *     @arg ADC_INT_EOC: The interrupt mask of the end of conversion
  *     @arg ADC_INT_AWE: The interrupt mask of the analog watchdog
  *     @arg ADC_INT_EOIC: The interrupt mask of the end of inserted conversion
  * @retval The new value of ADC_INT (SET or RESET).
  */
TypeState ADC_GetIntState(ADC_TypeDef *ADCx, uint16_t ADC_INT)
{
    uint32_t temp_it = 0, temp_enable = 0;
    /* Get the ADC interrupt mask index */
    temp_it = ADC_INT >> 8;
    /* Get the ADC_INT enable bit state */
    temp_enable = (ADCx->CTLR1 & (uint8_t)ADC_INT) ;
    /* Check the state of the specified ADC interrupt */
    if (((ADCx->STR & temp_it) != (uint32_t)RESET) && temp_enable) {
        /* ADC_INT is set */
        return SET;
    } else {
        /* ADC_INT is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the ADCx's interrupt pending bits.
  * @param  ADCx: the ADC interface where x can be 1..3.
  * @param  ADC_INT: the ADC interrupt pending bit.
  *   This parameter can be any combination of the following values:
  *     @arg ADC_INT_EOC: The interrupt mask of the end of conversion
  *     @arg ADC_INT_AWE: The interrupt mask of the analog watchdog
  *     @arg ADC_INT_EOIC: The interrupt mask of the end of inserted conversion
  * @retval None
  */
void ADC_ClearIntBitState(ADC_TypeDef *ADCx, uint16_t ADC_INT)
{
    uint8_t temp_it = 0;
    /* Get the ADC interrupt mask index */
    temp_it = (uint8_t)(ADC_INT >> 8);
    /* Clear ADCx interrupt pending bits */
    ADCx->STR = ~(uint32_t)temp_it;
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
