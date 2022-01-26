/*!
    \file  gd32f3x0_dac.c
    \brief DAC driver

    \version 2017-06-06, V1.0.0, firmware for GD32F3x0
    \version 2019-06-01, V2.0.0, firmware for GD32F3x0
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

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

#ifdef GD32F350
#include "gd32f3x0_dac.h"

/*!
    \brief      deinitialize DAC
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_deinit(void)
{
    rcu_periph_reset_enable(RCU_DACRST);
    rcu_periph_reset_disable(RCU_DACRST);
}

/*!
    \brief      enable DAC
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_enable(void)
{
    DAC_CTL |= DAC_CTL_DEN;
}

/*!
    \brief      disable DAC
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_disable(void)
{
    DAC_CTL &= ~DAC_CTL_DEN;
}

/*!
    \brief      enable DAC DMA
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_dma_enable(void)
{
    DAC_CTL |= DAC_CTL_DDMAEN;
}

/*!
    \brief      disable DAC DMA
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_dma_disable(void)
{
    DAC_CTL &= ~DAC_CTL_DDMAEN;
}

/*!
    \brief      enable DAC output buffer
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_output_buffer_enable(void)
{
    DAC_CTL &= ~DAC_CTL_DBOFF;
}

/*!
    \brief      disable DAC output buffer
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_output_buffer_disable(void)
{
    DAC_CTL |= DAC_CTL_DBOFF;
}

/*!
    \brief      enable DAC trigger
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_trigger_enable(void)
{
    DAC_CTL |= DAC_CTL_DTEN;
}

/*!
    \brief      disable DAC trigger
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_trigger_disable(void)
{
    DAC_CTL &= ~DAC_CTL_DTEN;
}

/*!
    \brief      enable DAC software trigger
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_software_trigger_enable(void)
{
    DAC_SWT |= DAC_SWT_SWTR;
}

/*!
    \brief      disable DAC software trigger
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_software_trigger_disable(void)
{
    DAC_SWT &= ~DAC_SWT_SWTR;
}

/*!
    \brief      enable DAC interrupt(DAC DMA underrun interrupt)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_interrupt_enable(void)
{
    DAC_CTL |= DAC_CTL_DDUDRIE;
}

/*!
    \brief      disable DAC interrupt(DAC DMA underrun interrupt)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_interrupt_disable(void)
{
    DAC_CTL &= ~DAC_CTL_DDUDRIE;
}

/*!
    \brief      set DAC tgigger source
    \param[in]  triggersource: external triggers of DAC
      \arg        DAC_TRIGGER_T1_TRGO: trigger source is TIMER1 TRGO
      \arg        DAC_TRIGGER_T2_TRGO: trigger source is TIMER2 TRGO
      \arg        DAC_TRIGGER_T5_TRGO: trigger source is TIMER5 TRGO
      \arg        DAC_TRIGGER_T14_TRGO: trigger source is TIMER14 TRGO
      \arg        DAC_TRIGGER_EXTI_9: trigger source is EXTI interrupt line9 event
      \arg        DAC_TRIGGER_SOFTWARE: software trigger
    \param[out] none
    \retval     none
*/
void dac_trigger_source_config(uint32_t triggersource)
{
    DAC_CTL &= ~DAC_CTL_DTSEL;
    DAC_CTL |= triggersource;
}

/*!
    \brief      configure DAC wave mode
    \param[in]  wave_mode
      \arg        DAC_WAVE_DISABLE: wave disable
      \arg        DAC_WAVE_MODE_LFSR: LFSR noise mode
      \arg        DAC_WAVE_MODE_TRIANGLE: triangle noise mode
    \param[out] none
    \retval     none
*/
void dac_wave_mode_config(uint32_t wave_mode)
{
    DAC_CTL &= ~DAC_CTL_DWM;
    DAC_CTL |= wave_mode;
}

/*!
    \brief      configure DAC wave bit width
    \param[in]  bit_width
      \arg        DAC_WAVE_BIT_WIDTH_1: bit width of the wave signal is 1
      \arg        DAC_WAVE_BIT_WIDTH_2: bit width of the wave signal is 2
      \arg        DAC_WAVE_BIT_WIDTH_3: bit width of the wave signal is 3
      \arg        DAC_WAVE_BIT_WIDTH_4: bit width of the wave signal is 4
      \arg        DAC_WAVE_BIT_WIDTH_5: bit width of the wave signal is 5
      \arg        DAC_WAVE_BIT_WIDTH_6: bit width of the wave signal is 6
      \arg        DAC_WAVE_BIT_WIDTH_7: bit width of the wave signal is 7
      \arg        DAC_WAVE_BIT_WIDTH_8: bit width of the wave signal is 8
      \arg        DAC_WAVE_BIT_WIDTH_9: bit width of the wave signal is 9
      \arg        DAC_WAVE_BIT_WIDTH_10: bit width of the wave signal is 10
      \arg        DAC_WAVE_BIT_WIDTH_11: bit width of the wave signal is 11
      \arg        DAC_WAVE_BIT_WIDTH_12: bit width of the wave signal is 12
    \param[out] none
    \retval     none
*/
void dac_wave_bit_width_config(uint32_t bit_width)
{
    DAC_CTL &= ~DAC_CTL_DWBW;
    DAC_CTL |= bit_width;
}

/*!
    \brief      configure DAC LFSR noise mode
    \param[in]  unmask_bits
      \arg        DAC_LFSR_BIT0: unmask the LFSR bit0
      \arg        DAC_LFSR_BITS1_0: unmask the LFSR bits[1:0]
      \arg        DAC_LFSR_BITS2_0: unmask the LFSR bits[2:0]
      \arg        DAC_LFSR_BITS3_0: unmask the LFSR bits[3:0]
      \arg        DAC_LFSR_BITS4_0: unmask the LFSR bits[4:0]
      \arg        DAC_LFSR_BITS5_0: unmask the LFSR bits[5:0]
      \arg        DAC_LFSR_BITS6_0: unmask the LFSR bits[6:0]
      \arg        DAC_LFSR_BITS7_0: unmask the LFSR bits[7:0]
      \arg        DAC_LFSR_BITS8_0: unmask the LFSR bits[8:0]
      \arg        DAC_LFSR_BITS9_0: unmask the LFSR bits[9:0]
      \arg        DAC_LFSR_BITS10_0: unmask the LFSR bits[10:0]
      \arg        DAC_LFSR_BITS11_0: unmask the LFSR bits[11:0]
    \param[out] none
    \retval     none
*/
void dac_lfsr_noise_config(uint32_t unmask_bits)
{
    DAC_CTL &= ~DAC_CTL_DWBW;
    DAC_CTL |= unmask_bits;
}

/*!
    \brief      configure DAC triangle noise mode
    \param[in]  amplitude
      \arg        DAC_TRIANGLE_AMPLITUDE_1: triangle amplitude is 1
      \arg        DAC_TRIANGLE_AMPLITUDE_3: triangle amplitude is 3
      \arg        DAC_TRIANGLE_AMPLITUDE_7: triangle amplitude is 7
      \arg        DAC_TRIANGLE_AMPLITUDE_15: triangle amplitude is 15
      \arg        DAC_TRIANGLE_AMPLITUDE_31: triangle amplitude is 31
      \arg        DAC_TRIANGLE_AMPLITUDE_63: triangle amplitude is 63
      \arg        DAC_TRIANGLE_AMPLITUDE_127: triangle amplitude is 127
      \arg        DAC_TRIANGLE_AMPLITUDE_255: triangle amplitude is 255
      \arg        DAC_TRIANGLE_AMPLITUDE_511: triangle amplitude is 511
      \arg        DAC_TRIANGLE_AMPLITUDE_1023: triangle amplitude is 1023
      \arg        DAC_TRIANGLE_AMPLITUDE_2047: triangle amplitude is 2047
      \arg        DAC_TRIANGLE_AMPLITUDE_4095: triangle amplitude is 4095
    \param[out] none
    \retval     none
*/
void dac_triangle_noise_config(uint32_t amplitude)
{
    DAC_CTL &= ~DAC_CTL_DWBW;
    DAC_CTL |= amplitude;
}

/*!
    \brief      get DAC output value
    \param[in]  none
    \param[out] none
    \retval     DAC output data
*/
uint16_t dac_output_value_get(void)
{
    uint16_t data = 0U;
    data = (uint16_t)DAC_DO;
    return data;
}

/*!
    \brief      get the specified DAC flag(DAC DMA underrun flag)
    \param[in]  none
    \param[out] none
    \retval     the state of dac bit(SET or RESET)
*/
FlagStatus dac_flag_get(void)
{
    /* check the DMA underrun flag */
    if((uint8_t)RESET != (DAC_STAT & DAC_STAT_DDUDR)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear the specified DAC flag(DAC DMA underrun flag)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_flag_clear(void)
{
    DAC_STAT |= DAC_STAT_DDUDR;
}

/*!
    \brief      get the specified DAC interrupt flag(DAC DMA underrun interrupt flag)
    \param[in]  none
    \param[out] none
    \retval     the state of DAC interrupt flag(SET or RESET)
*/
FlagStatus dac_interrupt_flag_get(void)
{
    FlagStatus temp_flag = RESET;
    uint32_t ddudr_flag = 0U, ddudrie_flag = 0U;
    /* check the DMA underrun flag and DAC DMA underrun interrupt enable flag */
    ddudr_flag = DAC_STAT & DAC_STAT_DDUDR;
    ddudrie_flag = DAC_CTL & DAC_CTL_DDUDRIE;
        if((RESET != ddudr_flag) && (RESET != ddudrie_flag)){
        temp_flag = SET;
    }
    return temp_flag;
}

/*!
    \brief      clear the specified DAC interrupt flag(DAC DMA underrun interrupt flag)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dac_interrupt_flag_clear(void)
{
    DAC_STAT |= DAC_STAT_DDUDR;
}

/*!
    \brief      set DAC data holding register value
    \param[in]  dac_align
      \arg        DAC_ALIGN_8B_R: data right 8b alignment
      \arg        DAC_ALIGN_12B_R: data right 12b alignment
      \arg        DAC_ALIGN_12B_L: data left 12b alignment
    \param[in]  data: data to be loaded
    \param[out] none
    \retval     none
*/
void dac_data_set(uint32_t dac_align, uint16_t data)
{
    switch(dac_align){
        /* data right 12b alignment */
        case DAC_ALIGN_12B_R:
            DAC_R12DH = data;
            break;
        /* data left 12b alignment */
        case DAC_ALIGN_12B_L:
            DAC_L12DH = data;
            break;
        /* data right 8b alignment */
        case DAC_ALIGN_8B_R:
            DAC_R8DH = data;
            break;
        default:
            break;
    }
}
#endif /* GD32F350 */
