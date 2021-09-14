////////////////////////////////////////////////////////////////////////////////
/// @file     hal_adc.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE ADC FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _HAL_ADC_C_

// Files includes
#include "hal_adc.h"
#include "hal_rcc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ADC_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ADC_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the adc peripheral registers to their default
///         reset values.
/// @param  adc: select the ADC peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_DeInit(ADC_TypeDef* adc)
{

    switch (*(vu32*)&adc) {

        case ADC1_BASE:
            exRCC_APB2PeriphReset(RCC_APB2ENR_ADC1);
            break;
        case ADC2_BASE:
            exRCC_APB2PeriphReset(RCC_APB2ENR_ADC2);
            break;
        case ADC3_BASE:
            exRCC_APB2PeriphReset(RCC_APB2ENR_ADC3);
            break;
        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the adc peripheral according to the specified parameters
///         in the init_struct, Please use this function if you want to be
///         compatible with older versions of the library.
/// @param  adc: select the ADC peripheral.
/// @param  init_struct: pointer to an ADC_InitTypeDef structure that contains
///         the configuration information for the specified ADC peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_Init(ADC_TypeDef* adc, ADC_InitTypeDef* init_struct)
{
    adc->ADCFG &= ~(ADC_CFGR_PRE | ADC_CFGR_RSLTCTL);
    adc->ADCFG |= (u32)(init_struct->ADC_PRESCARE) | init_struct->ADC_Resolution;

    adc->ADCR &= ~(ADC_CR_ALIGN | ADC_CR_MODE | ADC_CR_TRGSEL);
    adc->ADCR |= ((u32)init_struct->ADC_DataAlign) | init_struct->ADC_ExternalTrigConv | ((u32)init_struct->ADC_Mode);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Fills each init_struct member with its default value.
/// @param  init_struct : pointer to an ADC_InitTypeDef structure which will be
///         initialized.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_StructInit(ADC_InitTypeDef* init_struct)
{
    init_struct->ADC_Resolution         = ADC_Resolution_12b;
    init_struct->ADC_PRESCARE           = ADC_PCLK2_PRESCARE_2;
    init_struct->ADC_Mode               = ADC_CR_IMM;                           //ADC_Mode_Single;
    init_struct->ADC_ContinuousConvMode = DISABLE;                              // useless
    init_struct->ADC_ExternalTrigConv   = ADC1_ExternalTrigConv_T1_CC1;
    init_struct->ADC_DataAlign          = ADC_DataAlign_Right;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified ADC peripheral.
/// @param  adc:select the ADC peripheral.
/// @param  state: new state of the adc peripheral.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_Cmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ADCFG |= ADC_CFGR_ADEN) : (adc->ADCFG &= ~ADC_CFGR_ADEN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified ADC DMA request.
/// @param  adc: select the ADC peripheral.
/// @param  state: New state of the selected ADC DMA transfer.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_DMACmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ADCR |= ADC_CR_DMAEN) : (adc->ADCR &= ~ADC_CR_DMAEN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the specified ADC interrupts.
/// @param  adc: select the ADC peripheral.
/// @param  adc_interrupt: specifies the ADC interrupt sources to be enabled or disabled.
/// @param  state: New state of the specified ADC interrupts.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_ITConfig(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_interrupt, FunctionalState state)
{
    if (adc_interrupt == ADC_IT_EOC)
        (state) ? (adc->ADCR |= ADC_CR_ADIE) : (adc->ADCR &= ~ADC_CR_ADIE);
    else
        (state) ? (adc->ADCR |= ADC_CR_ADWIE) : (adc->ADCR &= ~ADC_CR_ADWIE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the selected ADC software start conversion .
/// @param  adc:  select the ADC peripheral.
/// @param  state: New state of the selected ADC software start conversion.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_SoftwareStartConvCmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ADCR |= ADC_CR_ADST) : (adc->ADCR &= ~ADC_CR_ADST);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Gets the selected ADC Software start conversion Status.
/// @param  adc: select the ADC peripheral.
/// @retval  The new state of ADC software start conversion (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* adc)
{
    return (((adc->ADCR & ADC_CR_ADST) != (u32)RESET) ? SET : RESET);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable the selected ADC channel and configure its sample time. Please
///         use this function if you want to be compatible with older versions
///         of the library.
/// @param  adc:  select the ADC peripheral.
/// @param  channel: the ADC channel to configure.
/// @param  sample_time: the ADC Channel n Sample time to configure.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_RegularChannelConfig(ADC_TypeDef* adc, u32 channel, u8 rank, u32 sample_time)    //ADCSAM_TypeDef
{

    u32 tempchan;
    sample_time = sample_time & 0xF;
    tempchan = channel;
    if(tempchan > 8) {
        tempchan = tempchan & 0xF;
        tempchan = tempchan - 8;
        adc->SMPR2 &= ~(0xF << tempchan);
        adc->SMPR2 |= (sample_time << tempchan);
    }
    else {
        adc->SMPR1 &= ~(0xF << tempchan);
        adc->SMPR1 |= (sample_time << tempchan);
    }
    adc->ADCHS &= ~(1 << channel);
    adc->ADCHS |=  (1 << channel);

    if (channel & ADC_CHSR_CHT)
        ADC_TempSensorVrefintCmd(ENABLE);
    else if (channel & ADC_CHSR_CHV)
        ADC_TempSensorVrefintCmd(ENABLE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the adc conversion through external trigger.
/// @param  adc: select the ADC peripheral.
/// @param  state: New state of the selected ADC external trigger.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_ExternalTrigConvCmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ADCR |= ADC_CR_TRGEN) : (adc->ADCR &= ~ADC_CR_TRGEN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the adc external trigger for injected channels conversion.
/// @param  adc:  select the ADC peripheral.
/// @param  adc_external_trig_source: Configuring the external trigger source
///         for the ADC.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_ExternalTrigConvConfig(ADC_TypeDef* adc, EXTERTRIG_TypeDef adc_external_trig_source)
{
    adc->ADCR &= ~ADC_CR_TRGSEL;
    adc->ADCR |=  adc_external_trig_source;
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the last adc conversion result data for regular channel.
/// @param  adc: select the ADC peripheral.
/// @retval The data conversion value.
////////////////////////////////////////////////////////////////////////////////
u16 ADC_GetConversionValue(ADC_TypeDef* adc)
{
    return (u16)adc->ADDATA;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Returns the last ADC conversion result data in dual mode.
/// @param  None
/// @retval The Data conversion value.
////////////////////////////////////////////////////////////////////////////////
u32 ADC_GetDualModeConversionValue()
{
    return (*(vu32*)ADC1_BASE);
}



////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the analog watchdog.
/// @param  adc:  to select the ADC peripheral.
/// @param  state: New state of the selected ADC analog watchdog.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_AnalogWatchdogCmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ADCFG |= ADC_CFGR_ADWEN) : (adc->ADCFG &= ~ADC_CFGR_ADWEN);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the high and low thresholds of the analog watchdog.
/// @param  adc:  select the ADC peripheral.
/// @param  high_threshold: the ADC analog watchdog High threshold value.
///         This parameter must be a 12bit value.
/// @param  low_threshold: the ADC analog watchdog Low threshold value.
///         This parameter must be a 12bit value.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* adc, u16 high_threshold, u16 low_threshold)
{
    u32 tempThreshold;
    tempThreshold = high_threshold;
    adc->ADCMPR    = (tempThreshold << 16) | low_threshold;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the analog watchdog guarded single channel
/// @param  adc: select the ADC peripheral.
/// @param  channel: the ADC channel to configure for the analog watchdog.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* adc, ADCCHANNEL_TypeDef channel)
{
    adc->ADCR &= ~ADC_CR_CMPCH;
    adc->ADCR |= (channel << ADC_CR_CMPCH_Pos);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the temperature sensor and Vrefint channel.
/// @param  state: New state of the temperature sensor.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_TempSensorVrefintCmd(FunctionalState state)
{
    (state) ? (ADC1->ADCFG |=  (ADC_CFGR_TEN | ADC_CFGR_VEN))
    : (ADC1->ADCFG &= ~(ADC_CFGR_TEN | ADC_CFGR_VEN));
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the temperature sensor .
/// @param  state: New state of the temperature sensor.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_TempSensorCmd(FunctionalState state)
{
    ADC_TempSensorVrefintCmd(state);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the Vrefint channel.
/// @param  state: New state of the Vrefint channel.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_VrefintCmd(FunctionalState state)
{
    ADC_TempSensorVrefintCmd(state);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the temperature sensor and Vrefint channel.
/// @param  chs: temperature sensor bit & Vrefint bit.
/// @param  state: New state of the temperature sensor.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exADC_TempSensorVrefintCmd(u32 chs, FunctionalState state)
{
    if (chs & ADC_CHSR_CHT) {
        (state) ? (ADC1->ADCFG |=  ADC_CFGR_TEN)
        : (ADC1->ADCFG &= ~ADC_CFGR_TEN);
    }
    else if (chs & ADC_CHSR_CHV) {
        (state) ? (ADC1->ADCFG |=  ADC_CFGR_VEN)
        : (ADC1->ADCFG &= ~ADC_CFGR_VEN);
    }

}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified ADC flag is set or not.
/// @param  adc: select the ADC peripheral.
/// @param  adc_flag: specifies the flag to check.
/// @retval The New state of adc_flag (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_flag)
{
    return (adc_flag == ADC_IT_EOC) ? ((adc->ADSTA & ADC_SR_ADIF) ? SET : RESET) : ((adc->ADSTA & ADC_SR_ADWIF) ? SET : RESET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the adc's pending flags.
/// @param  adc: select the ADC peripheral.
/// @param  adc_flag: specifies the flag to clear.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_ClearFlag(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_flag)
{
    (adc_flag == ADC_IT_EOC) ? (adc->ADSTA |= ADC_SR_ADIF) : (adc->ADSTA |= ADC_SR_ADWIF);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the specified adc's interrupt has occurred or not.
/// @param  adc: select the ADC peripheral.
/// @param  adc_interrupt: specifies the ADC interrupt source to check.
/// @retval The new state of adc_interrupt (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
ITStatus ADC_GetITStatus(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_interrupt)
{
    return (adc_interrupt == ADC_IT_EOC) ? ((adc->ADSTA & ADC_SR_ADIF) ? SET : RESET) : ((adc->ADSTA & ADC_SR_ADWIF) ? SET : RESET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears the adc's interrupt pending bits.
/// @param  adc: select the ADC peripheral.
/// @param  adc_interrupt: specifies the ADC interrupt pending bit to clear.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_ClearITPendingBit(ADC_TypeDef* adc, ADCFLAG_TypeDef adc_interrupt)
{
    (adc_interrupt == ADC_IT_EOC) ? (adc->ADSTA |= ADC_SR_ADIF) : (adc->ADSTA |= ADC_SR_ADWIF);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the adc any channels conversion rank and channel.
/// @param  adc: select the ADC peripheral.
/// @param  rank: rank can be 0x0~0xf for the convert sequence.
/// @param  adc_channel: Configuring the target channel to be converted.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_ANY_CH_Config(ADC_TypeDef* adc, u8 rank, ADCCHANNEL_TypeDef adc_channel)
{
    rank = rank & 0xF;
    if(rank < 8) {
        adc->CHANY0 &= ~(0x0F << (4 * rank));
        adc->CHANY0 |= (adc_channel << (4 * rank));
    }
    else {
        adc->CHANY1 &= ~(0x0F << (4 * (rank - 8)));
        adc->CHANY1 |= (adc_channel << (4 * (rank - 8)));
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the adc any channels conversion Max rank number
/// @param  adc: select the ADC peripheral.
/// @param  num: Configuring the max rank number for the ADC.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_ANY_NUM_Config(ADC_TypeDef* adc, u8 num)
{
    if(num > 15) num = 15;                                                      //15 ? 16 need to be confirmed
    adc->ANYCFG = num;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the ANY channel converter.
/// @param  state: enable or disable the ANY channel converter mode.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_ANY_Cmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ANYCR |= ADC1_CHANY_CR_MDEN) : (adc->ANYCR &= ~ADC1_CHANY_CR_MDEN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the selected ADC automatic injected group
///         conversion after regular one.
/// @param  adc: where x can be 1, 2 or 3 to select the ADC peripheral.
/// @param  state: new state of the selected ADC auto injected conversion
///   This parameter can be: ENABLE or DISABLE.
/// @retval None
////////////////////////////////////////////////////////////////////////////////
void ADC_AutoInjectedConvCmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ANYCR |= ADC_ANY_CR_JAUTO) : (adc->ANYCR &= ~ADC_ANY_CR_JAUTO);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the adc external trigger for injected channels conversion.
/// @param  adc: where x can be 1, 2 or 3 to select the ADC peripheral.
/// @param  ADC_ExtInjTrigSource: specifies the ADC trigger to start injected conversion.

/// @retval None
////////////////////////////////////////////////////////////////////////////////
void ADC_ExternalTrigInjectedConvertConfig(ADC_TypeDef* adc, EXTER_INJ_TRIG_TypeDef ADC_ExtInjTrigSource)
{
    u32 tmpreg = 0;
    // Get the old register value
    tmpreg = adc->ANYCR;
    // Clear the old external event selection for injected group
    tmpreg &= ADC_ANY_CR_JTRGSEL;
    // Set the external event selection for injected group
    tmpreg |= ADC_ExtInjTrigSource;
    // Store the new register value
    adc->ANYCR = tmpreg;
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the adc injected channels conversion through
///         external trigger
/// @param  adc: where x can be 1, 2 or 3 to select the ADC peripheral.
/// @param  state: new state of the selected ADC external trigger start of
///         injected conversion.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None
////////////////////////////////////////////////////////////////////////////////
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ANYCR |= ADC_ANY_CR_JTRGEN) : (adc->ANYCR &= ~ADC_ANY_CR_JTRGEN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the selected ADC start of the injected
///         channels conversion.
/// @param  adc: where x can be 1, 2 or 3 to select the ADC peripheral.
/// @param  state: new state of the selected ADC software start injected conversion.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None
////////////////////////////////////////////////////////////////////////////////
void ADC_InjectedConvCmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ANYCR |= ADC_ANY_CR_JCEN) : (adc->ANYCR &= ~ADC_ANY_CR_JCEN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the selected ADC start of the injected
///         channels conversion.
/// @param  adc: where x can be 1, 2 or 3 to select the ADC peripheral.
/// @param  NewState: new state of the selected ADC software start injected conversion.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None
////////////////////////////////////////////////////////////////////////////////
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* adc, FunctionalState state)
{
    (state) ? (adc->ANYCR |= ADC_ANY_CR_JADST) : (adc->ANYCR &= ~ADC_ANY_CR_JADST);
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable the selected ADC channel and configure its sample time. Please
///         use this function if you want to be compatible with older versions
///         of the library.
/// @param  adc:  select the ADC peripheral.
/// @param  event: the ADC external event to configure.
/// @param  sample_time: the ADC Channel n Sample time to configure.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_InjectedSequencerConfig(ADC_TypeDef* adc, u32 event, u32 sample_time)
{
    adc->ANYCR &= ~(ADC_ANY_CR_JCEN | ADC_ANY_CR_CHANY_MDEN | ADC_ANY_CR_JTRGSEL_EXTI12 \
                    | ADC_ANY_CR_JTRGSHIFT_512 | ADC_ANY_CR_JTRGEN);
    adc->ANYCR |= (ADC_ANY_CR_JCEN | ADC_ANY_CR_CHANY_MDEN | sample_time | event | ADC_ANY_CR_JTRGEN);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Injection channel length configuration.
/// @param  adc:  select the ADC peripheral.
/// @param  Length: Injection channel length.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* adc, ADC_INJ_SEQ_LEN_TypeDef Length)
{
    adc->JSQR &= ~(0x03 << ADC_JSQR_JL_Pos);
    adc->JSQR |= Length << ADC_JSQR_JL_Pos;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Injection channel  configuration.
/// @param  adc  :   select the ADC peripheral.
/// @param  off_addr :   Injection channel offset address.
/// @param  channel: The sampling channel.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_InjectedSequencerChannelConfig(ADC_TypeDef* adc, ADC_INJ_SEQ_Channel_TypeDef off_addr, ADCCHANNEL_TypeDef channel)
{
    adc->JSQR &= ~(0x1F << (off_addr >> 2) * 5);
    adc->JSQR |= (channel <<  (off_addr >> 2) * 5);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Injection channel  converted value.
/// @param  adc  :   select the ADC peripheral.
/// @param  off_addr :   Injection channel offset address.
/// @retval value.
////////////////////////////////////////////////////////////////////////////////
u16 ADC_GetInjectedConversionValue(ADC_TypeDef* adc, ADC_INJ_SEQ_Channel_TypeDef off_addr)
{
    u32 value;
    value = (*(vu32*)(*(vu32*)&adc + 0xB0 + off_addr)) - (*(vu32*)(*(vu32*)&adc + 0x7C + off_addr));

    return (u16)value;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Injection current converted value.
/// @param  adc  :   select the ADC peripheral.
/// @retval value. Returns the last adc conversion result data for injected channel.
////////////////////////////////////////////////////////////////////////////////
u16 ADC_GetInjectedCurrentConvertedValue(ADC_TypeDef* adc)
{
    return (u16)adc->JDATA;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Injection channel compensation configuration.
/// @param  adc         : select the ADC peripheral.
/// @param  off_addr    : Injection channel.
/// @param  value       : compensation value.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_SetInjectedOffset(ADC_TypeDef* adc, ADC_INJ_SEQ_Channel_TypeDef off_addr, u16 value)
{
    *(vu32*)(*(vu32*)&adc + 0x7C + off_addr) = value;
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Get channel convertion result.
/// @param  adc  :   select the ADC peripheral.
/// @param  channel :   Converted channel.
/// @retval The Data conversion value.
////////////////////////////////////////////////////////////////////////////////
u16 ADC_GetChannelConvertedValue(ADC_TypeDef* adc, ADCCHANNEL_TypeDef channel)
{
    return (u16)(*(vu32*) ((u32)adc + 0x18 + ((u32)channel << 2)));
}

/// @}

/// @}

/// @}

