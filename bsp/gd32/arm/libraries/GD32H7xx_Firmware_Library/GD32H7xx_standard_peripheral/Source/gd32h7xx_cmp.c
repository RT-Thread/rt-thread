/*!
    \file    gd32h7xx_cmp.c
    \brief   CMP driver

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

#include "gd32h7xx_cmp.h"

/*!
    \brief      CMP deinit
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[out] none
    \retval     none
*/
void cmp_deinit(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph)
    {
        CMP0_CS &= ((uint32_t)0x00000000U);
        CMP_IFC &= ((uint32_t)0xFFFEFFFFU);
        CMP_STAT &= ((uint32_t)0xFFFEFFFEU);
        CMP_SR &= ((uint32_t)0x00000000U);
    }else if(CMP1 == cmp_periph)
    {
        CMP1_CS &= ((uint32_t)0x00000000U);
        CMP_IFC &= ((uint32_t)0xFFFDFFFFU);
        CMP_STAT &= ((uint32_t)0xFFFDFFFDU);
        CMP_SR &= ((uint32_t)0x00000000U);
    }else{
    }
}

/*!
    \brief      CMP mode init
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  operating_mode
      \arg        CMP_MODE_HIGHSPEED: high speed mode
      \arg        CMP_MODE_MIDDLESPEED: medium speed mode
      \arg        CMP_MODE_VERYLOWSPEED: very-low speed mode
    \param[in]  inverting_input
      \arg        CMP_INVERTING_INPUT_1_4VREFINT: VREFINT *1/4 input
      \arg        CMP_INVERTING_INPUT_1_2VREFINT: VREFINT *1/2 input
      \arg        CMP_INVERTING_INPUT_3_4VREFINT: VREFINT *3/4 input
      \arg        CMP_INVERTING_INPUT_VREFINT: VREFINT input
      \arg        CMP_INVERTING_INPUT_DAC0_OUT0: PA4 (DAC) input
      \arg        CMP_INVERTING_INPUT_DAC0_OUT1: PA5 (DAC) input
      \arg        CMP_INVERTING_INPUT_PB1_PE10: PB1 for CMP0 or PE10 for CMP1 as inverting input
      \arg        CMP_INVERTING_INPUT_PC4_PE7: PC4 for CMP0 or PE7 for CMP1 as inverting input
    \param[in]  hysteresis
      \arg        CMP_HYSTERESIS_NO: output no hysteresis
      \arg        CMP_HYSTERESIS_LOW: output low hysteresis
      \arg        CMP_HYSTERESIS_MIDDLE: output middle hysteresis
      \arg        CMP_HYSTERESIS_HIGH: output high hysteresis
    \param[out] none
    \retval     none
*/
void cmp_mode_init(cmp_enum cmp_periph, uint32_t operating_mode, uint32_t inverting_input, uint32_t output_hysteresis)
{
    uint32_t temp = 0U;

    if(CMP0 == cmp_periph)
    {
        /* initialize comparator 0 mode */
        temp = CMP0_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXM | CMP_CS_CMPXMISEL | CMP_CS_CMPXHST);
        temp |= (uint32_t)(operating_mode | inverting_input | output_hysteresis);
        CMP0_CS = temp;
    }else if(CMP1 == cmp_periph)
    {
        /* initialize comparator 1 mode */
        temp = CMP1_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXM | CMP_CS_CMPXMISEL | CMP_CS_CMPXHST);
        temp |= (uint32_t)(operating_mode | inverting_input | output_hysteresis);
        CMP1_CS = temp;
    }else{
    }
}

/*!
    \brief      CMP noninverting input select
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  noninverting_input
      \arg        CMP_NONINVERTING_INPUT_PB0_PE9: CMP noninverting input PB0 for CMP0 or PE9 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PB2_PE12: CMP noninverting input PB2 for CMP0 or PE12 for CMP1
    \param[out] none
    \retval     none
*/
void cmp_noninverting_input_select(cmp_enum cmp_periph, uint32_t noninverting_input)
{
    uint32_t temp = 0U;

    if(CMP0 == cmp_periph)
    {
        temp = CMP0_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXPSEL;
        temp |= (uint32_t)noninverting_input;
        CMP0_CS = temp;
    }else if(CMP1 == cmp_periph)
    {
        temp = CMP1_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXPSEL;
        temp |= (uint32_t)noninverting_input;
        CMP1_CS = temp;
    }else{
    }
}

/*!
    \brief      CMP output init
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  output_polarity
      \arg        CMP_OUTPUT_POLARITY_INVERTED: output is inverted
      \arg        CMP_OUTPUT_POLARITY_NONINVERTED: output is not inverted
    \param[out] none
    \retval     none
*/
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_polarity)
{
    uint32_t temp = 0U;

    if(CMP0 == cmp_periph)
    {
        /* initialize comparator 0 output */
        temp = CMP0_CS;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity)
        {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        }else{
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP0_CS = temp;
    }else if(CMP1 == cmp_periph)
    {
        /* initialize comparator 1 output */
        temp = CMP1_CS;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity)
        {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        }else{
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP1_CS = temp;
    }else{
    }
}

/*!
    \brief      config comparator output port
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  cmp_output_sel
      \arg        CMP_AFSE_GPIO_PA6: CMP alternate GPIO PA6
      \arg        CMP_AFSE_GPIO_PA8: CMP alternate GPIO PA8
      \arg        CMP_AFSE_GPIO_PB12: CMP alternate GPIO PB12
      \arg        CMP_AFSE_GPIO_PE6: CMP alternate GPIO PE6
      \arg        CMP_AFSE_GPIO_PE15: CMP alternate GPIO PE15
      \arg        CMP_AFSE_GPIO_PG2: CMP alternate GPIO PG2
      \arg        CMP_AFSE_GPIO_PG3: CMP alternate GPIO PG3
      \arg        CMP_AFSE_GPIO_PG4: CMP alternate GPIO PG4
      \arg        CMP_AFSE_GPIO_PK0: CMP alternate GPIO PK0
      \arg        CMP_AFSE_GPIO_PK1: CMP alternate GPIO PK1
      \arg        CMP_AFSE_GPIO_PK2: CMP alternate GPIO PK2
    \param[out] none
    \retval     none
*/
void cmp_output_mux_config(cmp_enum cmp_periph, uint32_t cmp_output_sel)
{
    if(CMP0 == cmp_periph)
    {
        CMP_SR &= ~(uint32_t)cmp_output_sel;
    }else if(CMP1 == cmp_periph)
    {
        CMP_SR |= cmp_output_sel;
    }else{
    }
}

/*!
    \brief      CMP output blanking function init
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  blanking_source_selection
      \arg        CMP_BLANKING_NONE: CMP no blanking source
      \arg        CMP_BLANKING_TIMER0_OC0: CMP TIMER0_CH0 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER1_OC2: CMP TIMER1_CH2 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER2_OC2: CMP TIMER2_CH2 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER2_OC3: CMP TIMER2_CH3 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER7_OC0: CMP TIMER7_CH0 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER14_OC0: CMP TIMER14_CH0 output compare signal selected as blanking source
    \param[out] none
    \retval     none
*/
void cmp_blanking_init(cmp_enum cmp_periph, uint32_t blanking_source_selection)
{
    uint32_t temp = 0U;

    if(CMP0 == cmp_periph)
    {
        temp = CMP0_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXBLK;
        temp |= (uint32_t)blanking_source_selection;
        CMP0_CS = temp;
    }else if(CMP1 == cmp_periph)
    {
        temp = CMP1_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXBLK;
        temp |= (uint32_t)blanking_source_selection;
        CMP1_CS = temp;
    }else{
    }
}

/*!
    \brief      enable CMP
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[out] none
    \retval     none
*/
void cmp_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph)
    {
        CMP0_CS |= (uint32_t)CMP_CS_CMPXEN;
    }else if(CMP1 == cmp_periph)
    {
        CMP1_CS |= (uint32_t)CMP_CS_CMPXEN;
    }else{
    }
}

/*!
    \brief      disable CMP
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[out] none
    \retval     none
*/
void cmp_disable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph)
    {
        CMP0_CS &= ~(uint32_t)CMP_CS_CMPXEN;
    }else if(CMP1 == cmp_periph)
    {
        CMP1_CS &= ~(uint32_t)CMP_CS_CMPXEN;
    }else{
    }
}

/*!
    \brief      enable the window mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_window_enable(void)
{
    CMP1_CS |= (uint32_t)CMP_CS_WNDEN;
}

/*!
    \brief      disable the window mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_window_disable(void)
{
    CMP1_CS &= ~(uint32_t)CMP_CS_WNDEN;
}

/*!
    \brief      lock the comparator
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[out] none
    \retval     none
*/
void cmp_lock_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph)
    {
        /* lock CMP0 */
        CMP0_CS |= (uint32_t)CMP_CS_CMPXLK;
    }else if(CMP1 == cmp_periph)
    {
        /* lock CMP1 */
        CMP1_CS |= (uint32_t)CMP_CS_CMPXLK;
    }else{
    }
}

/*!
    \brief      enable the voltage scaler
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[out] none
    \retval     none
*/
void cmp_voltage_scaler_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph)
    {
        CMP0_CS |= (uint32_t)CMP_CS_CMPXSEN;
    }else if(CMP1 == cmp_periph)
    {
        CMP1_CS |= (uint32_t)CMP_CS_CMPXSEN;
    }else{
    }
}

/*!
    \brief      disable the voltage scaler
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[out] none
    \retval     none
*/
void cmp_voltage_scaler_disable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph)
    {
        CMP0_CS &= ~(uint32_t)CMP_CS_CMPXSEN;
    }else if(CMP1 == cmp_periph)
    {
        CMP1_CS &= ~(uint32_t)CMP_CS_CMPXSEN;
    }else{
    }
}

/*!
    \brief      enable the scaler bridge
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[out] none
    \retval     none
*/
void cmp_scaler_bridge_enable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph)
    {
        CMP0_CS |= (uint32_t)CMP_CS_CMPXBEN;
    }else if(CMP1 == cmp_periph)
    {
        CMP1_CS |= (uint32_t)CMP_CS_CMPXBEN;
    }else{
    }
}

/*!
    \brief      disable the scaler bridge
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[out] none
    \retval     none
*/
void cmp_scaler_bridge_disable(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph)
    {
        CMP0_CS &= ~(uint32_t)CMP_CS_CMPXBEN;
    }else if(CMP1 == cmp_periph)
    {
        CMP1_CS &= ~(uint32_t)CMP_CS_CMPXBEN;
    }else{
    }
}

/*!
    \brief      get output level
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[out] none
    \retval     the output level
*/
uint32_t cmp_output_level_get(cmp_enum cmp_periph)
{
    if(CMP0 == cmp_periph)
    {
        /* get output level of CMP0 */
        if((uint32_t)RESET != (CMP_STAT & CMP_STAT_CMP0O))
        {
            return CMP_OUTPUTLEVEL_HIGH;
        }else{
            return CMP_OUTPUTLEVEL_LOW;
        }
    }else{
        /* get output level of CMP1 */
        if((uint32_t)RESET != (CMP_STAT & CMP_STAT_CMP1O))
        {
            return CMP_OUTPUTLEVEL_HIGH;
        }else{
            return CMP_OUTPUTLEVEL_LOW;
        }
    }
}

/*!
    \brief      get CMP flag
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  flag: CMP flags
      \arg        CMP_FLAG_COMPARE: CMP compare flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cmp_flag_get(cmp_enum cmp_periph, uint32_t flag)
{
    FlagStatus reval = RESET;

    if(CMP0 == cmp_periph)
    {
        if(CMP_FLAG_COMPARE == flag)
        {
            if(0U != (CMP_STAT & CMP_STAT_CMP0IF))
            {
                reval = SET;
            }
        }
    }else if(CMP1 == cmp_periph)
    {
        if(CMP_FLAG_COMPARE == flag)
        {
            if(0U != (CMP_STAT & CMP_STAT_CMP1IF))
            {
                reval = SET;
            }
        }
    }
    return reval;
}

/*!
    \brief      clear CMP flag
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  flag: CMP flags
      \arg        CMP_FLAG_COMPARE: CMP compare flag
    \param[out] none
    \retval     none
*/
void cmp_flag_clear(cmp_enum cmp_periph, uint32_t flag)
{
    if(CMP0 == cmp_periph)
    {
        if(CMP_FLAG_COMPARE == flag)
        {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP0IC;
        }
    }else if(CMP1 == cmp_periph)
    {
        if(CMP_FLAG_COMPARE == flag)
        {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP1IC;
        }
    }else{
    }
}

/*!
    \brief      enable CMP interrupt
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  interrupt: CMP interrupt enable source
                only one parameter can be selected which is shown as below:
      \arg        CMP_INT_COMPARE: CMP compare interrupt
    \param[out] none
    \retval     none
*/
void cmp_interrupt_enable(cmp_enum cmp_periph, uint32_t interrupt)
{
    if(CMP0 == cmp_periph)
    {
        /* enable CMP0 interrupt */
        CMP0_CS |= (uint32_t)interrupt;
    }else if(CMP1 == cmp_periph)
    {
        /* enable CMP1 interrupt */
        CMP1_CS |= (uint32_t)interrupt;
    }else{
    }
}

/*!
    \brief      disable CMP interrupt
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  interrupt: CMP interrupt enable source
                only one parameter can be selected which is shown as below:
      \arg        CMP_INT_COMPARE: CMP compare interrupt
    \param[out] none
    \retval     none
*/
void cmp_interrupt_disable(cmp_enum cmp_periph, uint32_t interrupt)
{
    if(CMP0 == cmp_periph)
    {
        /* disable CMP0 interrupt */
        CMP0_CS &= ~(uint32_t)interrupt;
    }else if(CMP1 == cmp_periph)
    {
        /* disable CMP1 interrupt */
        CMP1_CS &= ~(uint32_t)interrupt;
    }else{
    }
}

/*!
    \brief      get CMP interrupt flag
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  flag: CMP interrupt flags
      \arg        CMP_INT_FLAG_COMPARE: CMP compare interrupt flag
    \param[out] none
    \retval     none
*/
FlagStatus cmp_interrupt_flag_get(cmp_enum cmp_periph, uint32_t flag)
{
    uint32_t intstatus = 0U, flagstatus = 0U;

    if(CMP0 == cmp_periph)
    {
        if(CMP_INT_FLAG_COMPARE == flag)
        {
            /* get the corresponding flag bit status */
            flagstatus = CMP_STAT & CMP_STAT_CMP0IF;
            /* get the interrupt enable bit status */
            intstatus = CMP0_CS & CMP_CS_CMPXINTEN;
        }
    }else if(CMP1 == cmp_periph)
    {
        if(CMP_INT_FLAG_COMPARE == flag)
        {
            /* get the corresponding flag bit status */
            flagstatus = CMP_STAT & CMP_STAT_CMP1IF;
            /* get the interrupt enable bit status */
            intstatus = CMP1_CS & CMP_CS_CMPXINTEN;
        }
    }else{
    }

    if((0U != flagstatus) && (0U != intstatus))
    {
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear CMP interrupt flag
    \param[in]  cmp_periph
      \arg        CMP0: comparator 0
      \arg        CMP1: comparator 1
    \param[in]  flag: CMP interrupt flags
      \arg        CMP_INT_FLAG_COMPARE: CMP compare interrupt flag
    \param[out] none
    \retval     none
*/
void cmp_interrupt_flag_clear(cmp_enum cmp_periph, uint32_t flag)
{
    /* clear CMP interrupt flag */
    if(CMP0 == cmp_periph)
    {
        if(CMP_INT_FLAG_COMPARE == flag)
        {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP0IC;
        }
    }else if(CMP1 == cmp_periph)
    {
        if(CMP_INT_FLAG_COMPARE == flag)
        {
            CMP_IFC |= (uint32_t)CMP_IFC_CMP1IC;
        }
    }else{
    }
}
