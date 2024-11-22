/*!
    \file    gd32e50x_cmp.c
    \brief   CMP driver

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#include "gd32e50x_cmp.h"

#ifdef GD32E50X_CL

/*!
    \brief      CMP deinit
    \param[in]  cmp_periph
      \arg        CMP1: comparator 1
      \arg        CMP3: comparator 3
      \arg        CMP5: comparator 5
    \param[out] none
    \retval     none
*/
void cmp_deinit(cmp_enum cmp_periph)
{
    if(CMP1 == cmp_periph)
    {
        CMP1_CS &= ((uint32_t)0x00000000U);
    }else if(CMP3 == cmp_periph)
    {
        CMP3_CS &= ((uint32_t)0x00000000U);
    }else if(CMP5 == cmp_periph)
    {
        CMP5_CS &= ((uint32_t)0x00000000U);
    }else{
    }

}

/*!
    \brief      CMP mode init
    \param[in]  cmp_periph
      \arg        CMP1: comparator 1
      \arg        CMP3: comparator 3
      \arg        CMP5: comparator 5
    \param[in]  inverting_input
      \arg        CMP_INVERTING_INPUT_1_4VREFINT: VREFINT *1/4 input
      \arg        CMP_INVERTING_INPUT_1_2VREFINT: VREFINT *1/2 input
      \arg        CMP_INVERTING_INPUT_3_4VREFINT: VREFINT *3/4 input
      \arg        CMP_INVERTING_INPUT_VREFINT: VREFINT input
      \arg        CMP_INVERTING_INPUT_DAC0_OUT0: PA4 (DAC) input
      \arg        CMP_INVERTING_INPUT_PA5: PA5 input
      \arg        CMP_INVERTING_INPUT_PA2: PA2 only for CMP1
      \arg        CMP_INVERTING_INPUT_PB2_PB15: PB2 for CMP3 or PB15 for CMP5 as inverting input
    \param[out] none
    \retval     none
*/
void cmp_mode_init(cmp_enum cmp_periph, uint32_t inverting_input)
{
    uint32_t temp = 0U;

    if(CMP1 == cmp_periph)
    {
        /* initialize comparator 1 mode */
        temp = CMP1_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXMSEL);
        temp |= (uint32_t)(inverting_input);
        CMP1_CS = temp;
    }else if(CMP3 == cmp_periph)
    {
        /* initialize comparator 3 mode */
        temp = CMP3_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXMSEL);
        temp |= (uint32_t)(inverting_input);
        CMP3_CS = temp;
    }else if(CMP5 == cmp_periph)
    {
        /* initialize comparator 5 mode */
        temp = CMP5_CS;
        temp &= ~(uint32_t)(CMP_CS_CMPXMSEL);
        temp |= (uint32_t)(inverting_input);
        CMP5_CS = temp;
    }else{
    }
}

/*!
    \brief      CMP output init
    \param[in]  cmp_periph
      \arg        CMP1: comparator 1
      \arg        CMP3: comparator 3
      \arg        CMP5: comparator 5
    \param[in]  output_selection
      \arg        CMP_OUTPUT_NONE: CMP output none
      \arg        CMP_OUTPUT_TIMER0_BKIN: CMP output TIMER0 break input
      \arg        CMP_OUTPUT_TIMER2_IC2: CMP output TIMER2_CH2 input capture only for CMP3
      \arg        CMP_OUTPUT_TIMER1_IC1: CMP output TIMER1_CH1 input capture only for CMP5
      \arg        CMP_OUTPUT_TIMER0_IC0: CMP output TIMER0_CH0 input capture only for CMP1
      \arg        CMP_OUTPUT_TIMER1_IC3: CMP output TIMER1_CH3 input capture only for CMP1
      \arg        CMP_OUTPUT_TIMER2_IC0: CMP output TIMER2_CH0 input capture only for CMP1
    \param[in]  output_polarity
      \arg        CMP_OUTPUT_POLARITY_INVERTED: output is inverted
      \arg        CMP_OUTPUT_POLARITY_NONINVERTED: output is not inverted
    \param[out] none
    \retval     none
*/
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_selection, uint32_t output_polarity)
{
    uint32_t temp = 0U;

    if(CMP1 == cmp_periph)
    {
        /* initialize comparator 1 output */
        temp = CMP1_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXOSEL;
        temp |= (uint32_t)output_selection;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity)
        {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        }else{
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP1_CS = temp;
    }else if(CMP3 == cmp_periph)
    {
        /* initialize comparator 3 output */
        temp = CMP3_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXOSEL;
        temp |= (uint32_t)output_selection;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity)
        {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        }else{
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP3_CS = temp;
    }else if(CMP5 == cmp_periph)
    {
        /* initialize comparator 5 output */
        temp = CMP5_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXOSEL;
        temp |= (uint32_t)output_selection;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity)
        {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        }else{
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP5_CS = temp;
    }else{
    }
}

/*!
    \brief      CMP output blanking function init
    \param[in]  cmp_periph
      \arg        CMP1: comparator 1
      \arg        CMP3: comparator 3
      \arg        CMP5: comparator 5
    \param[in]  blanking_source_selection
      \arg        CMP_BLANKING_NONE: CMP no blanking source
      \arg        CMP_BLANKING_TIMER2_OC3: CMP TIMER2_CH3 output compare signal selected as blanking source only for CMP3
      \arg        CMP_BLANKING_TIMER1_OC2: CMP TIMER1_CH2 output compare signal selected as blanking source only for CMP1
      \arg        CMP_BLANKING_TIMER2_OC2: CMP TIMER2_CH2 output compare signal selected as blanking source only for CMP1
      \arg        CMP_BLANKING_TIMER1_OC3: CMP TIMER1_CH3 output compare signal selected as blanking source only for CMP5
    \param[out] none
    \retval     none
*/
void cmp_blanking_init(cmp_enum cmp_periph, uint32_t blanking_source_selection)
{
    uint32_t temp = 0U;

    if(CMP1 == cmp_periph)
    {
        temp = CMP1_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXBLK;
        temp |= (uint32_t)blanking_source_selection;
        CMP1_CS = temp;
    }else if(CMP3 == cmp_periph)
    {
        temp = CMP3_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXBLK;
        temp |= (uint32_t)blanking_source_selection;
        CMP3_CS = temp;
    }else if(CMP5 == cmp_periph)
    {
        temp = CMP5_CS;
        temp &= ~(uint32_t)CMP_CS_CMPXBLK;
        temp |= (uint32_t)blanking_source_selection;
        CMP5_CS = temp;
    }else{
    }
}

/*!
    \brief      enable CMP
    \param[in]  cmp_periph
      \arg        CMP1: comparator 1
      \arg        CMP3: comparator 3
      \arg        CMP5: comparator 5
    \param[out] none
    \retval     none
*/
void cmp_enable(cmp_enum cmp_periph)
{
    if(CMP1 == cmp_periph)
    {
        CMP1_CS |= (uint32_t)CMP_CS_CMPXEN;
    }else if(CMP3 == cmp_periph)
    {
        CMP3_CS |= (uint32_t)CMP_CS_CMPXEN;
    }else if(CMP5 == cmp_periph)
    {
        CMP5_CS |= (uint32_t)CMP_CS_CMPXEN;
    }else{
    }
}

/*!
    \brief      disable CMP
    \param[in]  cmp_periph
      \arg        CMP1: comparator 1
      \arg        CMP3: comparator 3
      \arg        CMP5: comparator 5
    \param[out] none
    \retval     none
*/
void cmp_disable(cmp_enum cmp_periph)
{
    if(CMP1 == cmp_periph)
    {
        CMP1_CS &= ~(uint32_t)CMP_CS_CMPXEN;
    }else if(CMP3 == cmp_periph)
    {
        CMP3_CS &= ~(uint32_t)CMP_CS_CMPXEN;
    }else if(CMP5 == cmp_periph)
    {
        CMP5_CS &= ~(uint32_t)CMP_CS_CMPXEN;
    }else{
    }
}

/*!
    \brief      lock the CMP
    \param[in]  cmp_periph
      \arg        CMP1: comparator 1
      \arg        CMP3: comparator 3
      \arg        CMP5: comparator 5
    \param[out] none
    \retval     none
*/
void cmp_lock_enable(cmp_enum cmp_periph)
{
    if(CMP1 == cmp_periph)
    {
        /* lock CMP1 */
        CMP1_CS |= (uint32_t)CMP_CS_CMPXLK;
    }else if(CMP3 == cmp_periph)
    {
        /* lock CMP3 */
        CMP3_CS |= (uint32_t)CMP_CS_CMPXLK;
    }else if(CMP5 == cmp_periph)
    {
        /* lock CMP5 */
        CMP5_CS |= (uint32_t)CMP_CS_CMPXLK;
    }else{
    }
}

/*!
    \brief      get output level
    \param[in]  cmp_periph
      \arg        CMP1: comparator 1
      \arg        CMP3: comparator 3
      \arg        CMP5: comparator 5
    \param[out] none
    \retval     the output level
*/
uint32_t cmp_output_level_get(cmp_enum cmp_periph)
{
    if(CMP1 == cmp_periph)
    {
        /* get output level of CMP1 */
        if((uint32_t)RESET != (CMP1_CS & CMP_CS_CMPXO))
        {
            return CMP_OUTPUTLEVEL_HIGH;
        }else{
            return CMP_OUTPUTLEVEL_LOW;
        }
    }else if(CMP3 == cmp_periph)
    {
        /* get output level of CMP3 */
        if((uint32_t)RESET != (CMP3_CS & CMP_CS_CMPXO))
        {
            return CMP_OUTPUTLEVEL_HIGH;
        }else{
            return CMP_OUTPUTLEVEL_LOW;
        }
    }else{
        /* get output level of CMP5 */
        if((uint32_t)RESET != (CMP5_CS & CMP_CS_CMPXO))
        {
            return CMP_OUTPUTLEVEL_HIGH;
        }else{
            return CMP_OUTPUTLEVEL_LOW;
        }
    }
}

#endif /* GD32E50x_CL */
