/*!
    \file    gd32h7xx_adc.c
    \brief   ADC driver

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32h7xx_adc.h"

/* discontinuous mode macro */
#define ADC_CHANNEL_LENGTH_SUBTRACT_ONE            ((uint8_t)1U)

/* ADC regular channel macro */
#define ADC_REGULAR_CHANNEL_RANK_ONE               ((uint8_t)1U)
#define ADC_REGULAR_CHANNEL_RANK_THREE             ((uint8_t)3U)
#define ADC_REGULAR_CHANNEL_RANK_FIVE              ((uint8_t)5U)
#define ADC_REGULAR_CHANNEL_RANK_SEVEN             ((uint8_t)7U)
#define ADC_REGULAR_CHANNEL_RANK_NINE              ((uint8_t)9U)
#define ADC_REGULAR_CHANNEL_RANK_ELEVEN            ((uint8_t)11U)
#define ADC_REGULAR_CHANNEL_RANK_THIRTEEN          ((uint8_t)13U)
#define ADC_REGULAR_CHANNEL_RANK_FIFTEEN           ((uint8_t)15U)
#define ADC_REGULAR_CHANNEL_RANK_SIXTEEN           ((uint8_t)16U)
#define ADC_REGULAR_CHANNEL_SHIFT_LENGTH           ((uint8_t)16U)

/* ADC inserted channel macro */
#define ADC_INSERTED_CHANNEL_RANK_ONE              ((uint8_t)1U)
#define ADC_INSERTED_CHANNEL_RANK_THREE            ((uint8_t)3U)
#define ADC_INSERTED_CHANNEL_RANK_FOUR             ((uint8_t)4U)
#define ADC_INSERTED_CHANNEL_SHIFT_LENGTH          ((uint8_t)16U)

/* ADC inserted channel offset macro */
#define ADC_OFFSET_LENGTH                          ((uint8_t)3U)
#define ADC_OFFSET_SHIFT_LENGTH                    ((uint8_t)4U)

/* ADC IOFF0 reg offset address macro */
#define ADC_IOFF0_OFFSET                           ((uint32_t)0x0000000CU)

/* external trigger mode macro */
#define REGULAR_TRIGGER_MODE                       ((uint8_t)28U)
#define INSERTED_TRIGGER_MODE                      ((uint8_t)20U)

/*!
    \brief      reset ADC
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_deinit(uint32_t adc_periph)
{
    switch(adc_periph)
    {
        case ADC0:
            rcu_periph_reset_enable(RCU_ADC0RST);
            rcu_periph_reset_disable(RCU_ADC0RST);
            break;
        case ADC1:
            rcu_periph_reset_enable(RCU_ADC1RST);
            rcu_periph_reset_disable(RCU_ADC1RST);
            break;
        case ADC2:
            rcu_periph_reset_enable(RCU_ADC2RST);
            rcu_periph_reset_disable(RCU_ADC2RST);
            break;
        default:
            break;
    }
}

/*!
    \brief      configure the ADC clock
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  prescaler: configure ADCs prescaler ratio
                only one parameter can be selected which is shown as below:
      \arg        ADC_CLK_SYNC_HCLK_DIV2: ADC sync clock mode HCLK div2
      \arg        ADC_CLK_SYNC_HCLK_DIV4: ADC sync clock mode HCLK div4
      \arg        ADC_CLK_SYNC_HCLK_DIV8: ADC sync clock mode HCLK div8
      \arg        ADC_CLK_SYNC_HCLK_DIV10: ADC sync clock mode HCLK div10
      \arg        ADC_CLK_SYNC_HCLK_DIV12: ADC sync clock mode HCLK div12
      \arg        ADC_CLK_SYNC_HCLK_DIV14: ADC sync clock mode HCLK div14
      \arg        ADC_CLK_SYNC_HCLK_DIV16: ADC sync clock mode HCLK div16
      \arg        ADC_CLK_ASYNC_DIV1: ADC async clock mode div1
      \arg        ADC_CLK_ASYNC_DIV2: ADC async clock mode div2
      \arg        ADC_CLK_ASYNC_DIV4: ADC async clock mode div4
      \arg        ADC_CLK_ASYNC_DIV6: ADC async clock mode div6
      \arg        ADC_CLK_ASYNC_DIV8: ADC async clock mode div8
      \arg        ADC_CLK_ASYNC_DIV10: ADC async clock mode div10
      \arg        ADC_CLK_ASYNC_DIV12: ADC async clock mode div12
      \arg        ADC_CLK_ASYNC_DIV16: ADC async clock mode div16
      \arg        ADC_CLK_ASYNC_DIV32: ADC async clock mode div32
      \arg        ADC_CLK_ASYNC_DIV64: ADC async clock mode div64
      \arg        ADC_CLK_ASYNC_DIV128: ADC async clock mode div128
      \arg        ADC_CLK_ASYNC_DIV256: ADC async clock mode div256
    \param[out] none
    \retval     none
*/
void adc_clock_config(uint32_t adc_periph, uint32_t prescaler)
{
    if(ADC2 == adc_periph)
    {
        ADC_SYNCCTL(ADC2) &= ~((uint32_t)(ADC_SYNCCTL_ADCCK | ADC_SYNCCTL_ADCSCK));
        ADC_SYNCCTL(ADC2) |= (uint32_t)prescaler;
    } else {
        ADC_SYNCCTL(ADC0) &= ~((uint32_t)(ADC_SYNCCTL_ADCCK | ADC_SYNCCTL_ADCSCK));
        ADC_SYNCCTL(ADC0) |= (uint32_t)prescaler;
    }
}

/*!
    \brief      enable or disable ADC special function
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  function: the function to config
                only one parameter can be selected which is shown as below:
      \arg        ADC_SCAN_MODE: scan mode select
      \arg        ADC_INSERTED_CHANNEL_AUTO: inserted channel group convert automatically
      \arg        ADC_CONTINUOUS_MODE: continuous mode select
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_special_function_config(uint32_t adc_periph, uint32_t function, ControlStatus newvalue)
{
    if(ENABLE == newvalue)
    {
        if(RESET != (function & ADC_SCAN_MODE))
        {
            /* enable scan mode */
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_SCAN_MODE;
        }
        if(RESET != (function & ADC_INSERTED_CHANNEL_AUTO))
        {
            /* enable inserted channel group convert automatically */
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_INSERTED_CHANNEL_AUTO;
        }
        if(RESET != (function & ADC_CONTINUOUS_MODE))
        {
            /* enable continuous mode */
            ADC_CTL1(adc_periph) |= (uint32_t)ADC_CONTINUOUS_MODE;
        }
    } else {
        if(RESET != (function & ADC_SCAN_MODE))
        {
            /* disable scan mode */
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_SCAN_MODE);
        }
        if(RESET != (function & ADC_INSERTED_CHANNEL_AUTO))
        {
            /* disable inserted channel group convert automatically */
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_INSERTED_CHANNEL_AUTO);
        }
        if(RESET != (function & ADC_CONTINUOUS_MODE))
        {
            /* disable continuous mode */
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CONTINUOUS_MODE);
        }
    }
}

/*!
    \brief      configure ADC data alignment
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  data_alignment: data alignment select
                only one parameter can be selected which is shown as below:
      \arg        ADC_DATAALIGN_RIGHT: LSB alignment
      \arg        ADC_DATAALIGN_LEFT: MSB alignment
    \param[out] none
    \retval     none
*/
void adc_data_alignment_config(uint32_t adc_periph, uint32_t data_alignment)
{
    if(ADC_DATAALIGN_RIGHT == data_alignment)
    {
        /* LSB alignment */
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DAL);
    } else if(ADC_DATAALIGN_LEFT == data_alignment)
    {
        /* MSB alignment */
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_DAL;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable ADC interface
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_enable(uint32_t adc_periph)
{
    if(RESET == (ADC_CTL1(adc_periph) & ADC_CTL1_ADCON))
    {
        /* enable ADC */
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_ADCON;
    }
}

/*!
    \brief      disable ADC interface
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_disable(uint32_t adc_periph)
{
    /* disable ADC */
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ADCON);
}

/*!
    \brief      configure ADC calibration mode
    \param[in]  adc_periph: ADCx, x=0,1
    \param[in]  clb_mode: calibration mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_CALIBRATION_OFFSET_MISMATCH: ADC calibration offset and mismatch mode
      \arg        ADC_CALIBRATION_OFFSET: ADC calibration offset mode
    \param[out] none
    \retval     none
*/
void adc_calibration_mode_config(uint32_t adc_periph, uint32_t clb_mode)
{
    if(ADC_CALIBRATION_OFFSET_MISMATCH == clb_mode)
    {
        /* offset and mismatch mode */
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_CALMOD);
    } else if(ADC_CALIBRATION_OFFSET == clb_mode)
    {
        /* offset mode */
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_CALMOD;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure ADC calibration number
    \param[in]  adc_periph: ADCx, x=0,1
    \param[in]  clb_num: calibration number
                only one parameter can be selected which is shown as below:
      \arg        ADC_CALIBRATION_NUM1: calibrate once
      \arg        ADC_CALIBRATION_NUM2: calibrate twice
      \arg        ADC_CALIBRATION_NUM4: calibrate 4 times
      \arg        ADC_CALIBRATION_NUM8: calibrate 8 times
      \arg        ADC_CALIBRATION_NUM16: calibrate 16 times
      \arg        ADC_CALIBRATION_NUM32: calibrate 32 times
    \param[out] none
    \retval     none
*/
void adc_calibration_number(uint32_t adc_periph, uint32_t clb_num)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_CALNUM);
    ADC_CTL1(adc_periph) |= (uint32_t)clb_num;
}

/*!
    \brief      ADC calibration and reset calibration
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_calibration_enable(uint32_t adc_periph)
{
    /* reset the selected ADC calibration registers */
    ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_RSTCLB;
    /* check the RSTCLB bit state */
    while(RESET != (ADC_CTL1(adc_periph) & ADC_CTL1_RSTCLB))
    {
    }
    /* enable ADC calibration process */
    ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_CLB;
    /* check the CLB bit state */
    while(RESET != (ADC_CTL1(adc_periph) & ADC_CTL1_CLB))
    {
    }
}

/*!
    \brief      configure ADC resolution
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  resolution: ADC resolution
                only one parameter can be selected which is shown as below:
      \arg        ADC_RESOLUTION_14B: 14-bit ADC resolution, for ADC0/ADC1
      \arg        ADC_RESOLUTION_12B: 12-bit ADC resolution, for all ADCs
      \arg        ADC_RESOLUTION_10B: 10-bit ADC resolution, for all ADCs
      \arg        ADC_RESOLUTION_8B: 8-bit ADC resolution, for all ADCs
      \arg        ADC_RESOLUTION_6B: 6-bit ADC resolution, only for ADC2
    \param[out] none
    \retval     none
*/
void adc_resolution_config(uint32_t adc_periph, uint32_t resolution)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DRES);

    if(ADC2 == adc_periph)
    {
        if(ADC_RESOLUTION_14B == resolution)
        {
            /* illegal parameters */
        } else {
            ADC_CTL0(adc_periph) |= (uint32_t)CTL0_DRES(resolution - 1U);
        }
    } else {
        if(ADC_RESOLUTION_6B == resolution)
        {
            /* illegal parameters */
        } else {
            ADC_CTL0(adc_periph) |= (uint32_t)CTL0_DRES(resolution);
        }
    }
}

/*!
    \brief      enable or disable ADC internal channels
    \param[in]  internal_channel: the internal channels
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INTERNAL_TEMPSENSOR: temperature sensor channel
      \arg        ADC_CHANNEL_INTERNAL_VREFINT: vrefint channel
      \arg        ADC_CHANNEL_INTERNAL_VBAT: vbat channel
      \arg        ADC_CHANNEL_INTERNAL_HP_TEMPSENSOR: high-precision temperature sensor channel
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_internal_channel_config(uint32_t internal_channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue)
    {
        ADC_CTL1(ADC2) |= (uint32_t)internal_channel;
    } else {
        ADC_CTL1(ADC2) &= ~((uint32_t)internal_channel);
    }
}

/*!
    \brief      enable DMA request
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_dma_mode_enable(uint32_t adc_periph)
{
    /* enable DMA request */
    ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_DMA;
}

/*!
    \brief      disable DMA request
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_dma_mode_disable(uint32_t adc_periph)
{
    /* disable DMA request */
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DMA);
}

/*!
    \brief      when DMA=1, the DMA engine issues a request at end of each regular conversion
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_enable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_DDM;
}

/*!
    \brief      the DMA engine is disabled after the end of transfer signal from DMA controller is detected
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_disable(uint32_t adc_periph)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DDM);
}

/*!
    \brief      enable hpdf mode
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_hpdf_mode_enable(uint32_t adc_periph)
{
    /* enable hpdf mode */
    ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_HPDFCFG;
}

/*!
    \brief      disable hpdf mode
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_hpdf_mode_disable(uint32_t adc_periph)
{
    /* disable hpdf mode */
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_HPDFCFG);
}

/*!
    \brief      configure ADC discontinuous mode
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel_group: select the channel group
                only one parameter can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
      \arg        ADC_CHANNEL_DISCON_DISABLE: disable discontinuous mode of regular & inserted channel
    \param[in]  length: number of conversions in discontinuous mode, the number can be 1..8
                        for regular channel, the number has no effect for inserted channel
    \param[out] none
    \retval     none
*/
void adc_discontinuous_mode_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t length)
{
    /* disable discontinuous mode of regular & inserted channel */
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_DISRC | ADC_CTL0_DISIC));
    switch(adc_channel_group)
    {
        case ADC_REGULAR_CHANNEL:
            /* config the number of conversions in discontinuous mode  */
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DISNUM);
            if((length <= 8U) && (length >= 1U))
            {
                ADC_CTL0(adc_periph) |= CTL0_DISNUM((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
            }
            /* enable regular channel group discontinuous mode */
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISRC;
            break;
        case ADC_INSERTED_CHANNEL:
            /* enable inserted channel group discontinuous mode */
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISIC;
            break;
        case ADC_CHANNEL_DISCON_DISABLE:
        /* disable discontinuous mode of regular & inserted channel */
        default:
            break;
    }
}

/*!
    \brief      configure the length of regular channel group or inserted channel group
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel_group: select the channel group
                only one parameter can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  length: the length of the channel
                        regular channel 1-16
                        inserted channel 1-4
    \param[out] none
    \retval     none
*/
void adc_channel_length_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t length)
{
    switch(adc_channel_group)
    {
        case ADC_REGULAR_CHANNEL:
            if((length >= 1U) && (length <= 16U))
            {
                ADC_RSQ0(adc_periph) &= ~((uint32_t)ADC_RSQ0_RL);
                ADC_RSQ0(adc_periph) |= RSQ0_RL((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
            }
            break;
        case ADC_INSERTED_CHANNEL:
            if((length >= 1U) && (length <= 4U))
            {
                ADC_ISQ0(adc_periph) &= ~((uint32_t)ADC_ISQ0_IL);
                ADC_ISQ0(adc_periph) |= ISQ0_IL((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
            }
            break;
        default:
            break;
    }
}

/*!
    \brief      configure ADC regular channel
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  rank: the regular group sequencer rank,this parameter must be between 0 to 15
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x(x=0..20): ADC Channelx
    \param[in]  sample_time: the sample time value, 0..809 for ADC0/ADC1, 0..638 for ADC2
    \param[out] none
    \retval     none
*/
void adc_regular_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel, uint32_t sample_time)
{
    uint32_t rsq;

    /* configure ADC regular sequence */
    if(rank < ADC_REGULAR_CHANNEL_RANK_ONE)
    {
        /* the regular group sequence rank is smaller than one */
        rsq = ADC_RSQ8(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH * rank)));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                   rank));
        ADC_RSQ8(adc_periph) = rsq;
    } else if(rank < ADC_REGULAR_CHANNEL_RANK_THREE)
    {
        /* the regular group sequence rank is smaller than three */
        rsq = ADC_RSQ7(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                 (rank - ADC_REGULAR_CHANNEL_RANK_ONE))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                   (rank - ADC_REGULAR_CHANNEL_RANK_ONE)));
        ADC_RSQ7(adc_periph) = rsq;
    } else if(rank < ADC_REGULAR_CHANNEL_RANK_FIVE)
    {
        /* the regular group sequence rank is smaller than five */
        rsq = ADC_RSQ6(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                 (rank - ADC_REGULAR_CHANNEL_RANK_THREE))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                   (rank - ADC_REGULAR_CHANNEL_RANK_THREE)));
        ADC_RSQ6(adc_periph) = rsq;
    } else if(rank < ADC_REGULAR_CHANNEL_RANK_SEVEN)
    {
        /* the regular group sequence rank is smaller than seven */
        rsq = ADC_RSQ5(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                 (rank - ADC_REGULAR_CHANNEL_RANK_FIVE))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                   (rank - ADC_REGULAR_CHANNEL_RANK_FIVE)));
        ADC_RSQ5(adc_periph) = rsq;
    } else if(rank < ADC_REGULAR_CHANNEL_RANK_NINE)
    {
        /* the regular group sequence rank is smaller than nine */
        rsq = ADC_RSQ4(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                 (rank - ADC_REGULAR_CHANNEL_RANK_SEVEN))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                   (rank - ADC_REGULAR_CHANNEL_RANK_SEVEN)));
        ADC_RSQ4(adc_periph) = rsq;
    } else if(rank < ADC_REGULAR_CHANNEL_RANK_ELEVEN)
    {
        /* the regular group sequence rank is smaller than eleven */
        rsq = ADC_RSQ3(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                 (rank - ADC_REGULAR_CHANNEL_RANK_NINE))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                   (rank - ADC_REGULAR_CHANNEL_RANK_NINE)));
        ADC_RSQ3(adc_periph) = rsq;
    } else if(rank < ADC_REGULAR_CHANNEL_RANK_THIRTEEN)
    {
        /* the regular group sequence rank is smaller than thirteen */
        rsq = ADC_RSQ2(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                 (rank - ADC_REGULAR_CHANNEL_RANK_ELEVEN))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                   (rank - ADC_REGULAR_CHANNEL_RANK_ELEVEN)));
        ADC_RSQ2(adc_periph) = rsq;
    } else if(rank < ADC_REGULAR_CHANNEL_RANK_FIFTEEN)
    {
        /* the regular group sequence rank is smaller than fifteen */
        rsq = ADC_RSQ1(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                 (rank - ADC_REGULAR_CHANNEL_RANK_THIRTEEN))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                   (rank - ADC_REGULAR_CHANNEL_RANK_THIRTEEN)));
        ADC_RSQ1(adc_periph) = rsq;
    } else if(rank < ADC_REGULAR_CHANNEL_RANK_SIXTEEN)
    {
        /* the regular group sequence rank is smaller than sixteen */
        rsq = ADC_RSQ0(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                 (rank - ADC_REGULAR_CHANNEL_RANK_FIFTEEN))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_REGULAR_CHANNEL_SHIFT_LENGTH *
                                                                   (rank - ADC_REGULAR_CHANNEL_RANK_FIFTEEN)));
        ADC_RSQ0(adc_periph) = rsq;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure ADC inserted channel
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  rank: the inserted group sequencer rank,this parameter must be between 0 to 3
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x(x=0..20): ADC Channelx
    \param[in]  sample_time: The sample time value, 0..809 for ADC0/ADC1, 0..638 for ADC2
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel, uint32_t sample_time)
{
    uint8_t inserted_length, rankx;
    uint32_t isq;

    /* get inserted channel group length */
    inserted_length = (uint8_t)GET_BITS(ADC_ISQ0(adc_periph), 20U, 21U);
    rankx = ADC_OFFSET_LENGTH - inserted_length + rank;

    /* configure ADC inserted sequence */
    if(rankx < ADC_INSERTED_CHANNEL_RANK_ONE)
    {
        /* the inserted group sequence rank is smaller than one */
        isq = ADC_ISQ2(adc_periph);
        isq &= ~((uint32_t)((ADC_ISQX_ISMPN | ADC_ISQX_ISQN) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH * rankx)));
        isq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH * rankx));
        ADC_ISQ2(adc_periph) = isq;
    } else if(rankx < ADC_INSERTED_CHANNEL_RANK_THREE)
    {
        /* the inserted group sequence rank is smaller than three */
        isq = ADC_ISQ1(adc_periph);
        isq &= ~((uint32_t)((ADC_ISQX_ISMPN | ADC_ISQX_ISQN) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                                                                 (rankx - ADC_INSERTED_CHANNEL_RANK_ONE))));
        isq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                                                                   (rankx - ADC_INSERTED_CHANNEL_RANK_ONE)));
        ADC_ISQ1(adc_periph) = isq;
    } else if(rankx < ADC_INSERTED_CHANNEL_RANK_FOUR)
    {
        /* the inserted group sequence rank is smaller than four */
        isq = ADC_ISQ0(adc_periph);
        isq &= ~((uint32_t)((ADC_ISQX_ISMPN | ADC_ISQX_ISQN) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                                                                 (rankx - ADC_INSERTED_CHANNEL_RANK_THREE))));
        isq |= ((uint32_t)(SQX_SMP(sample_time) | adc_channel) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                                                                   (rankx - ADC_INSERTED_CHANNEL_RANK_THREE)));
        ADC_ISQ0(adc_periph) = isq;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure ADC inserted channel offset
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  inserted_channel : insert channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_CHANNEL_0: inserted channel0
      \arg        ADC_INSERTED_CHANNEL_1: inserted channel1
      \arg        ADC_INSERTED_CHANNEL_2: inserted channel2
      \arg        ADC_INSERTED_CHANNEL_3: inserted channel3
    \param[in]  offset : the offset data
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_offset_config(uint32_t adc_periph, uint8_t inserted_channel, uint32_t offset)
{
    uint8_t inserted_length;
    uint32_t num = 0U;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ0(adc_periph), 20U, 21U);
    num = ((uint32_t)ADC_OFFSET_LENGTH - ((uint32_t)inserted_length - (uint32_t)inserted_channel));

    if(num <= ADC_OFFSET_LENGTH)
    {
        /* calculate the offset of the register */
        num = num * ADC_OFFSET_SHIFT_LENGTH;
        /* config the offset of the selected channels */
        REG32((adc_periph) + ADC_IOFF0_OFFSET + num) = IOFFX_IOFF((uint32_t)offset);
    }
}

/*!
    \brief      configure differential mode for ADC channel
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel: the channel use differential mode
                one or more parameters can be selected which is shown as below:
      \arg        ADC_DIFFERENTIAL_MODE_CHANNEL_x(x=0..21), ADC_DIFFERENTIAL_MODE_CHANNEL_ALL: ADC channel for differential mode
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_channel_differential_mode_config(uint32_t adc_periph, uint32_t adc_channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue)
    {
        ADC_DIFCTL(adc_periph) |= (uint32_t)adc_channel;
    } else {
        ADC_DIFCTL(adc_periph) &= ~((uint32_t)adc_channel);
    }
}

/*!
    \brief      enable ADC external trigger
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel_group: select the channel group
                only one parameter can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[in]  trigger_mode: external trigger mode
                only one parameter can be selected which is shown as below:
      \arg        EXTERNAL_TRIGGER_DISABLE: external trigger disable
      \arg        EXTERNAL_TRIGGER_RISING: rising edge of external trigger
      \arg        EXTERNAL_TRIGGER_FALLING: falling edge of external trigger
      \arg        EXTERNAL_TRIGGER_RISING_FALLING: rising and falling edge of external trigger
    \param[out] none
    \retval     none
*/
void adc_external_trigger_config(uint32_t adc_periph, uint8_t adc_channel_group, uint32_t trigger_mode)
{
    switch(adc_channel_group)
    {
        case ADC_REGULAR_CHANNEL:
            /* configure ADC regular channel group external trigger mode */
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ETMRC);
            ADC_CTL1(adc_periph) |= (uint32_t)(trigger_mode << REGULAR_TRIGGER_MODE);
            break;
        case ADC_INSERTED_CHANNEL:
            /* configure ADC inserted channel group external trigger mode */
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ETMIC);
            ADC_CTL1(adc_periph) |= (uint32_t)(trigger_mode << INSERTED_TRIGGER_MODE);
            break;
        default:
            break;
    }
}

/*!
    \brief      enable ADC software trigger
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel_group: select the channel group
                only one parameter can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
    \param[out] none
    \retval     none
*/
void adc_software_trigger_enable(uint32_t adc_periph, uint8_t adc_channel_group)
{
    /* enable regular group channel software trigger */
    if(RESET != (adc_channel_group & ADC_REGULAR_CHANNEL))
    {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_SWRCST;
    }
    /* enable inserted channel group software trigger */
    if(RESET != (adc_channel_group & ADC_INSERTED_CHANNEL))
    {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_SWICST;
    }
}

/*!
    \brief      configure end of conversion mode
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  end_selection: end of conversion mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_EOC_SET_SEQUENCE: only at the end of a sequence of regular conversions, the EOC bit is set. Overflow detection is disabled unless DMA=1.
      \arg        ADC_EOC_SET_CONVERSION: at the end of each regular conversion, the EOC bit is set. Overflow is detected automatically.
    \param[out] none
    \retval     none
*/
void adc_end_of_conversion_config(uint32_t adc_periph, uint32_t end_selection)
{
    if(ADC_EOC_SET_SEQUENCE == end_selection)
    {
        /* only at the end of a sequence of regular conversions, the EOC bit is set */
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_EOCM);
    } else if(ADC_EOC_SET_CONVERSION == end_selection)
    {
        /* at the end of each regular conversion, the EOC bit is set. Overflow is detected automatically */
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_EOCM;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      read ADC regular group data register
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  none
    \param[out] none
    \retval     the conversion value
*/
uint32_t adc_regular_data_read(uint32_t adc_periph)
{
    return (uint32_t)(ADC_RDATA(adc_periph));
}

/*!
    \brief      read ADC inserted group data register
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  inserted_channel : insert channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_CHANNEL_0: inserted Channel0
      \arg        ADC_INSERTED_CHANNEL_1: inserted channel1
      \arg        ADC_INSERTED_CHANNEL_2: inserted Channel2
      \arg        ADC_INSERTED_CHANNEL_3: inserted Channel3
    \param[out] none
    \retval     the conversion value
*/
uint32_t adc_inserted_data_read(uint32_t adc_periph, uint8_t inserted_channel)
{
    uint32_t idata;
    /* read the data of the selected channel */
    switch(inserted_channel)
    {
        case ADC_INSERTED_CHANNEL_0:
            /* read the data of channel 0 */
            idata = ADC_IDATA0(adc_periph);
            break;
        case ADC_INSERTED_CHANNEL_1:
            /* read the data of channel 1 */
            idata = ADC_IDATA1(adc_periph);
            break;
        case ADC_INSERTED_CHANNEL_2:
            /* read the data of channel 2 */
            idata = ADC_IDATA2(adc_periph);
            break;
        case ADC_INSERTED_CHANNEL_3:
            /* read the data of channel 3 */
            idata = ADC_IDATA3(adc_periph);
            break;
        default:
            idata = 0U;
            break;
    }
    return (uint32_t)idata;
}

/*!
    \brief      configure ADC analog watchdog 0 single channel
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x: ADC Channelx(x=0..20)
    \param[out] none
    \retval     none
*/
void adc_watchdog0_single_channel_enable(uint32_t adc_periph, uint8_t adc_channel)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC |
                                         ADC_CTL0_WD0CHSEL));

    ADC_CTL0(adc_periph) |= (uint32_t)adc_channel;
    ADC_CTL0(adc_periph) |= (uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC);
}

/*!
    \brief      configure ADC analog watchdog 0 group channel
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel_group: the channel group use analog watchdog 0
                only one parameter can be selected which is shown as below:
      \arg        ADC_REGULAR_CHANNEL: regular channel group
      \arg        ADC_INSERTED_CHANNEL: inserted channel group
      \arg        ADC_REGULAR_INSERTED_CHANNEL: both regular and inserted group
    \param[out] none
    \retval     none
*/
void adc_watchdog0_group_channel_enable(uint32_t adc_periph, uint8_t adc_channel_group)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC));
    /* select the group */
    switch(adc_channel_group)
    {
        case ADC_REGULAR_CHANNEL:
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_RWD0EN;
            break;
        case ADC_INSERTED_CHANNEL:
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_IWD0EN;
            break;
        case ADC_REGULAR_INSERTED_CHANNEL:
            ADC_CTL0(adc_periph) |= (uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN);
            break;
        default:
            break;
    }
}

/*!
    \brief      disable ADC analog watchdog 0
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_watchdog0_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC |
                                         ADC_CTL0_WD0CHSEL));
}

/*!
    \brief      configure ADC analog watchdog 1 channel
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  selection_channel: the channel use analog watchdog 1
                one or more parameters can be selected which is shown as below:
      \arg        ADC_AWD1_2_SELECTION_CHANNEL_x, ADC_AWD1_2_SELECTION_CHANNEL_ALL: ADC channel analog watchdog 1/2 selection
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_watchdog1_channel_config(uint32_t adc_periph, uint32_t selection_channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue)
    {
        ADC_WD1SR(adc_periph) |= (uint32_t)selection_channel;
    } else {
        ADC_WD1SR(adc_periph) &= ~((uint32_t)selection_channel);
    }
}

/*!
    \brief      configure ADC analog watchdog 2 channel
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  selection_channel: the channel use analog watchdog 2
                one or more parameters can be selected which is shown as below:
      \arg        ADC_AWD1_2_SELECTION_CHANNEL_x, ADC_AWD1_2_SELECTION_CHANNEL_ALL: ADC channel analog watchdog 1/2 selection
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_watchdog2_channel_config(uint32_t adc_periph, uint32_t selection_channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue)
    {
        ADC_WD2SR(adc_periph) |= (uint32_t)selection_channel;
    } else {
        ADC_WD2SR(adc_periph) &= ~((uint32_t)selection_channel);
    }
}

/*!
    \brief      disable ADC analog watchdog 1
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_watchdog1_disable(uint32_t adc_periph)
{
    ADC_WD1SR(adc_periph) &= ~((uint32_t)ADC_WD1SR_AWD1CS);
}

/*!
    \brief      disable ADC analog watchdog 2
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_watchdog2_disable(uint32_t adc_periph)
{
    ADC_WD2SR(adc_periph) &= ~((uint32_t)ADC_WD2SR_AWD2CS);
}

/*!
    \brief      configure ADC analog watchdog 0 threshold
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  low_threshold: analog watchdog 0 low threshold, 0..0xFFFFFF for ADC0/ADC1, 0..0xFFF for ADC2
    \param[in]  high_threshold: analog watchdog 0 high threshold, 0..0xFFFFFF for ADC0/ADC1, 0..0xFFF for ADC2
    \param[out] none
    \retval     none
*/
void adc_watchdog0_threshold_config(uint32_t adc_periph, uint32_t low_threshold, uint32_t high_threshold)
{
    ADC_WDLT0(adc_periph) = (uint32_t)WDLT0_WDLT0(low_threshold);
    ADC_WDHT0(adc_periph) = (uint32_t)WDHT0_WDHT0(high_threshold);
}

/*!
    \brief      configure ADC analog watchdog 1 threshold
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  low_threshold: analog watchdog 1 low threshold, 0..0xFFFFFF for ADC0/ADC1, 0..0xFF for ADC2
    \param[in]  high_threshold: analog watchdog 1 high threshold, 0..0xFFFFFF for ADC0/ADC1, 0..0xFF for ADC2
    \param[out] none
    \retval     none
*/
void adc_watchdog1_threshold_config(uint32_t adc_periph, uint32_t low_threshold, uint32_t high_threshold)
{
    ADC_WDLT1(adc_periph) = (uint32_t)WDLT1_WDLT1(low_threshold);
    ADC_WDHT1(adc_periph) = (uint32_t)WDHT1_WDHT1(high_threshold);
}

/*!
    \brief      configure ADC analog watchdog 2 threshold
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  low_threshold: analog watchdog 2 low threshold, 0..0xFFFFFF for ADC0/ADC1, 0..0xFF for ADC2
    \param[in]  high_threshold: analog watchdog 2 high threshold, 0..0xFFFFFF for ADC0/ADC1, 0..0xFF for ADC2
    \param[out] none
    \retval     none
*/
void adc_watchdog2_threshold_config(uint32_t adc_periph, uint32_t low_threshold, uint32_t high_threshold)
{
    ADC_WDLT2(adc_periph) = (uint32_t)WDLT2_WDLT2(low_threshold);
    ADC_WDHT2(adc_periph) = (uint32_t)WDHT2_WDHT2(high_threshold);
}

/*!
    \brief      configure ADC oversample mode
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  mode: ADC oversampling mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_OVERSAMPLING_ALL_CONVERT: all oversampled conversions for a channel are done consecutively after a trigger
      \arg        ADC_OVERSAMPLING_ONE_CONVERT: each oversampled conversion for a channel needs a trigger
    \param[in]  shift: ADC oversampling shift
                only one parameter can be selected which is shown as below:
      \arg        ADC_OVERSAMPLING_SHIFT_NONE: no oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_1B: 1-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_2B: 2-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_3B: 3-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_4B: 4-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_5B: 5-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_6B: 6-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_7B: 7-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_8B: 8-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_9B: 9-bit oversampling shift, available for ADC0/ADC1
      \arg        ADC_OVERSAMPLING_SHIFT_10B: 10-bit oversampling shift, available for ADC0/ADC1
      \arg        ADC_OVERSAMPLING_SHIFT_11B: 11-bit oversampling shift, available for ADC0/ADC1
    \param[in]  ratio: ADC oversampling ratio, 0..1023 for ADC0/ADC1, 0..255 for ADC2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_config(uint32_t adc_periph, uint32_t mode, uint16_t shift, uint16_t ratio)
{
    if(ADC_OVERSAMPLING_ALL_CONVERT == mode)
    {
        /* all oversampled conversions for a channel are done consecutively after a trigger */
        ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_TOVS);
    } else if(ADC_OVERSAMPLING_ONE_CONVERT == mode)
    {
        /* each oversampled conversion for a channel needs a trigger */
        ADC_OVSAMPCTL(adc_periph) |= (uint32_t)ADC_OVSAMPCTL_TOVS;
    } else {
        /* illegal parameters */
    }
    /* config the shift and ratio */
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)(ADC_OVSAMPCTL_OVSR | ADC_OVSAMPCTL_OVSS));
    ADC_OVSAMPCTL(adc_periph) |= ((uint32_t)shift | (uint32_t)OVSCR_OVSR(ratio));
}

/*!
    \brief      enable ADC oversample mode
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_enable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) |= (uint32_t)ADC_OVSAMPCTL_OVSEN;
}

/*!
    \brief      disable ADC oversample mode
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_disable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_OVSEN);
}

/*!
    \brief      get the ADC flag bits
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  flag: the adc flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_WDE0: analog watchdog 0 event flag
      \arg        ADC_FLAG_EOC: end of group conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted group conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted channel group
      \arg        ADC_FLAG_STRC: start flag of regular channel group
      \arg        ADC_FLAG_ROVF: regular data register overflow flag
      \arg        ADC_FLAG_WDE1: analog watchdog 1 event flag
      \arg        ADC_FLAG_WDE2: analog watchdog 2 event flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_flag_get(uint32_t adc_periph, uint32_t flag)
{
    FlagStatus reval = RESET;
    if(ADC_STAT(adc_periph) & flag)
    {
        reval = SET;
    }
    return reval;
}

/*!
    \brief      clear the ADC flag bits
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  flag: the adc flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_WDE0: analog watchdog 0 event flag
      \arg        ADC_FLAG_EOC: end of group conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted group conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted channel group
      \arg        ADC_FLAG_STRC: start flag of regular channel group
      \arg        ADC_FLAG_ROVF: regular data register overflow flag
      \arg        ADC_FLAG_WDE1: analog watchdog 1 event flag
      \arg        ADC_FLAG_WDE2: analog watchdog 2 event flag
    \param[out] none
    \retval     none
*/
void adc_flag_clear(uint32_t adc_periph, uint32_t flag)
{
    ADC_STAT(adc_periph) = ~((uint32_t)flag);
}

/*!
    \brief      enable ADC interrupt
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_interrupt: the adc interrupt
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_WDE0: analog watchdog 0 interrupt
      \arg        ADC_INT_EOC: end of group conversion interrupt
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt
      \arg        ADC_INT_ROVF: regular data register overflow interrupt
      \arg        ADC_INT_WDE1: analog watchdog 1 interrupt
      \arg        ADC_INT_WDE2: analog watchdog 2 interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_enable(uint32_t adc_periph, uint32_t interrupt)
{
    ADC_CTL0(adc_periph) |= (uint32_t)interrupt;
}

/*!
    \brief      disable ADC interrupt
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_interrupt: the adc interrupt
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_WDE0: analog watchdog 0 interrupt
      \arg        ADC_INT_EOC: end of group conversion interrupt
      \arg        ADC_INT_EOIC: end of inserted group conversion interrupt
      \arg        ADC_INT_ROVF: regular data register overflow interrupt
      \arg        ADC_INT_WDE1: analog watchdog 1 interrupt
      \arg        ADC_INT_WDE2: analog watchdog 2 interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_disable(uint32_t adc_periph, uint32_t interrupt)
{
    ADC_CTL0(adc_periph) &= ~(uint32_t)interrupt;
}

/*!
    \brief      get the ADC interrupt bits
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  int_flag: the adc interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WDE0: analog watchdog 0 interrupt
      \arg        ADC_INT_FLAG_EOC: end of group conversion interrupt
      \arg        ADC_INT_FLAG_EOIC: end of inserted group conversion interrupt
      \arg        ADC_INT_FLAG_ROVF: regular data register overflow interrupt
      \arg        ADC_INT_FLAG_WDE1: analog watchdog 1 interrupt
      \arg        ADC_INT_FLAG_WDE2: analog watchdog 2 interrupt
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph, uint32_t int_flag)
{
    FlagStatus reval = RESET;
    uint32_t state;
    /* check the interrupt bits */
    switch(int_flag)
    {
        case ADC_INT_FLAG_WDE0:
            /* get the ADC analog watchdog 0 interrupt bits */
            state = ADC_STAT(adc_periph) & ADC_STAT_WDE0;
            if((ADC_CTL0(adc_periph) & ADC_CTL0_WDE0IE) && state)
            {
                reval = SET;
            }
            break;
        case ADC_INT_FLAG_EOC:
            /* get the ADC end of group conversion interrupt bits */
            state = ADC_STAT(adc_periph) & ADC_STAT_EOC;
            if((ADC_CTL0(adc_periph) & ADC_CTL0_EOCIE) && state)
            {
                reval = SET;
            }
            break;
        case ADC_INT_FLAG_EOIC:
            /* get the ADC end of inserted group conversion interrupt bits */
            state = ADC_STAT(adc_periph) & ADC_STAT_EOIC;
            if((ADC_CTL0(adc_periph) & ADC_CTL0_EOICIE) && state)
            {
                reval = SET;
            }
            break;
        case ADC_INT_FLAG_ROVF:
            /* get the ADC regular data register overflow interrupt bits */
            state = ADC_STAT(adc_periph) & ADC_STAT_ROVF;
            if((ADC_CTL0(adc_periph) & ADC_CTL0_ROVFIE) && state)
            {
                reval = SET;
            }
            break;
        case ADC_INT_FLAG_WDE1:
            /* get the ADC analog watchdog 1 interrupt bits */
            state = ADC_STAT(adc_periph) & ADC_STAT_WDE1;
            if((ADC_CTL0(adc_periph) & ADC_CTL0_WDE1IE) && state)
            {
                reval = SET;
            }
            break;
        case ADC_INT_FLAG_WDE2:
            /* get the ADC analog watchdog 2 interrupt bits */
            state = ADC_STAT(adc_periph) & ADC_STAT_WDE2;
            if((ADC_CTL0(adc_periph) & ADC_CTL0_WDE2IE) && state)
            {
                reval = SET;
            }
            break;
        default:
            break;
    }
    return reval;
}

/*!
    \brief      clear the ADC flag
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  int_flag: the adc interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WDE0: analog watchdog 0 interrupt flag
      \arg        ADC_INT_FLAG_EOC: end of group conversion interrupt flag
      \arg        ADC_INT_FLAG_EOIC: end of inserted group conversion interrupt flag
      \arg        ADC_INT_FLAG_ROVF: regular data register overflow interrupt flag
      \arg        ADC_INT_FLAG_WDE1: analog watchdog 1 interrupt flag
      \arg        ADC_INT_FLAG_WDE2: analog watchdog 2 interrupt flag
    \param[out] none
    \retval     none
*/
void adc_interrupt_flag_clear(uint32_t adc_periph, uint32_t int_flag)
{
    ADC_STAT(adc_periph) = ~((uint32_t)int_flag);
}

/*!
    \brief      configure the ADC sync mode
    \param[in]  sync_mode: ADC sync mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_SYNC_MODE_INDEPENDENT: all the ADCs work independently
      \arg        ADC_DAUL_REGULAL_PARALLEL_INSERTED_PARALLEL: combined regular parallel & inserted parallel mode
      \arg        ADC_DAUL_REGULAL_PARALLEL_INSERTED_ROTATION: combined regular parallel & trigger rotation mode
      \arg        ADC_DAUL_INSERTED_PARALLEL: inserted parallel mode
      \arg        ADC_DAUL_REGULAL_PARALLEL: regular parallel mode
      \arg        ADC_DAUL_REGULAL_FOLLOW_UP: follow-up mode
      \arg        ADC_DAUL_INSERTED_TRIGGER_ROTATION: trigger rotation mode
    \param[out] none
    \retval     none
*/
void adc_sync_mode_config(uint32_t sync_mode)
{
    ADC_SYNCCTL(ADC0) &= ~((uint32_t)ADC_SYNCCTL_SYNCM);
    ADC_SYNCCTL(ADC0) |= (uint32_t)sync_mode;
}

/*!
    \brief      configure the delay between 2 sampling phases in ADC sync modes
    \param[in]  sample_delay:  the delay between 2 sampling phases in ADC sync modes
                only one parameter can be selected which is shown as below:
      \arg        ADC_SYNC_DELAY_xCYCLE: x=5..20,the delay between 2 sampling phases in ADC sync modes is x ADC clock cycles
    \param[out] none
    \retval     none
*/
void adc_sync_delay_config(uint32_t sample_delay)
{
    ADC_SYNCCTL(ADC0) &= ~((uint32_t)ADC_SYNCCTL_SYNCDLY);
    ADC_SYNCCTL(ADC0) |= (uint32_t)sample_delay;
}

/*!
    \brief      configure ADC sync DMA mode selection
    \param[in]  dma_mode:  ADC sync DMA mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_SYNC_DMA_DISABLE: ADC sync DMA disabled
      \arg        ADC_SYNC_DMA_MODE0: ADC sync DMA mode 0
      \arg        ADC_SYNC_DMA_MODE1: ADC sync DMA mode 1
    \param[out] none
    \retval     none
*/
void adc_sync_dma_config(uint32_t dma_mode)
{
    ADC_SYNCCTL(ADC0) &= ~((uint32_t)ADC_SYNCCTL_SYNCDMA);
    ADC_SYNCCTL(ADC0) |= (uint32_t)dma_mode;
}

/*!
    \brief      configure ADC sync DMA engine issues requests according to the SYNCDMA bits
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sync_dma_request_after_last_enable(void)
{
    ADC_SYNCCTL(ADC0) |= (uint32_t)ADC_SYNCCTL_SYNCDDM;
}

/*!
    \brief      configure ADC sync DMA engine is disabled after the end of transfer signal from DMA controller is detected
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sync_dma_request_after_last_disable(void)
{
    ADC_SYNCCTL(ADC0) &= ~((uint32_t)ADC_SYNCCTL_SYNCDDM);
}

/*!
    \brief      read ADC sync master adc regular data register 0
    \param[in]  none
    \param[out] none
    \retval     sync regular data 0
*/
uint32_t adc_sync_master_adc_regular_data0_read(void)
{
    return (uint32_t)(ADC_SYNCDATA0 & ADC_SYNCDATA0_SYNCDATA0);
}

/*!
    \brief      read ADC sync slave adc regular data register 0
    \param[in]  none
    \param[out] none
    \retval     sync regular data 0
*/
uint32_t adc_sync_slave_adc_regular_data0_read(void)
{
    return (uint32_t)(ADC_SYNCDATA0 & ADC_SYNCDATA0_SYNCDATA1) >> 16;
}

/*!
    \brief      read ADC sync regular data register 1
    \param[in]  none
    \param[out] none
    \retval     sync regular data 1
*/
uint32_t adc_sync_regular_data1_read(void)
{
    return (uint32_t)ADC_SYNCDATA1;
}
