/*!
    \file    gd32e230_cmp.c
    \brief   CMP driver

    \version 2018-06-19, V1.0.0, firmware for GD32E230
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#include "gd32e230_cmp.h"

/*!
    \brief      deinitialize comparator 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_deinit(void)
{
    CMP_CS = ((uint32_t)0x00000000U);
}

/*!
    \brief      initialize comparator mode 
    \param[in]  operating_mode
      \arg        CMP_HIGHSPEED: high speed mode
      \arg        CMP_MIDDLESPEED: medium speed mode
      \arg        CMP_LOWSPEED: low speed mode
      \arg        CMP_VERYLOWSPEED: very-low speed mode
    \param[in]  inverting_input 
      \arg        CMP_1_4VREFINT: VREFINT *1/4 input
      \arg        CMP_1_2VREFINT: VREFINT *1/2 input
      \arg        CMP_3_4VREFINT: VREFINT *3/4 input
      \arg        CMP_VREFINT: VREFINT input
      \arg        CMP_PA4: PA4 input
      \arg        CMP_PA5: PA5 input
      \arg        CMP_PA0: PA0 input
      \arg        CMP_PA2: PA2 input
    \param[in]  hysteresis
      \arg        CMP_HYSTERESIS_NO: output no hysteresis
      \arg        CMP_HYSTERESIS_LOW: output low hysteresis
      \arg        CMP_HYSTERESIS_MIDDLE: output middle hysteresis
      \arg        CMP_HYSTERESIS_HIGH: output high hysteresis
    \param[out] none
    \retval     none
*/
void cmp_mode_init(operating_mode_enum operating_mode, inverting_input_enum inverting_input, cmp_hysteresis_enum output_hysteresis)
{
    /* initialize comparator mode */
    CMP_CS |= CS_CMPM(operating_mode) | CS_CMPMSEL(inverting_input) | CS_CMPHST(output_hysteresis);
  
}

/*!
    \brief      initialize comparator output
    \param[in]  output_slection 
      \arg        CMP_OUTPUT_NONE: output no selection
      \arg        CMP_OUTPUT_TIMER0BKIN: TIMER 0 break input
      \arg        CMP_OUTPUT_TIMER0IC0: TIMER 0 channel0 input capture 
      \arg        CMP_OUTPUT_TIMER0OCPRECLR: TIMER 0 OCPRE_CLR input
      \arg        CMP_OUTPUT_TIMER2IC0: TIMER 2 channel0 input capture
      \arg        CMP_OUTPUT_TIMER2OCPRECLR: TIMER 2 OCPRE_CLR input
    \param[in]  output_polarity 
      \arg        CMP_OUTPUT_POLARITY_INVERTED: output is inverted
      \arg        CMP_OUTPUT_POLARITY_NOINVERTED: output is not inverted
    \param[out] none
    \retval     none
*/
void cmp_output_init(cmp_output_enum output_slection, uint32_t output_polarity)
{
    /* initialize comparator output */

    CMP_CS |= CS_CMPOSEL(output_slection);
    /* output polarity */
    if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity){
         CMP_CS |= CMP_CS_CMPPL;
    }else{ 
         CMP_CS &= ~CMP_CS_CMPPL;
    }

}

/*!
    \brief      enable comparator 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_enable(void)
{
    CMP_CS |= CMP_CS_CMPEN;
}

/*!
    \brief      disable comparator 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_disable(void)
{
    CMP_CS &= ~CMP_CS_CMPEN;
}

/*!
    \brief      enable comparator switch
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_switch_enable(void)
{
    CMP_CS |= CMP_CS_CMPSW;
}

/*!
    \brief      disable comparator switch
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_switch_disable(void)
{
    CMP_CS &= ~CMP_CS_CMPSW;
}

/*!
    \brief      get output level
    \param[in]  none
    \param[out] none
    \retval     the output level
*/
uint32_t cmp_output_level_get(void)
{
    if(CMP_CS & CMP_CS_CMPO){
        return CMP_OUTPUTLEVEL_HIGH;
    }else{
        return CMP_OUTPUTLEVEL_LOW;
    }
    
}

/*!
    \brief      lock the comparator
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cmp_lock_enable(void)
{
    CMP_CS |= CMP_CS_CMPLK;
}

