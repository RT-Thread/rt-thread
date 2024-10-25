/*!
    \file    gd32e50x_cmp.h
    \brief   definitions for the CMP

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

#ifndef GD32E50X_CMP_H
#define GD32E50X_CMP_H

#include "gd32e50x.h"

#ifdef GD32E50X_CL

/* CMP definitions */
#define CMP                                      CMP_BASE                       /*!< CMP base address */

/* registers definitions */
#define CMP1_CS                                  REG32((CMP) + 0x00000020U)     /*!< CMP1 control and status register */
#define CMP3_CS                                  REG32((CMP) + 0x00000028U)     /*!< CMP3 control and status register */
#define CMP5_CS                                  REG32((CMP) + 0x00000030U)     /*!< CMP5 control and status register */

/* bits definitions */
/* CMPx_CS */
#define CMP_CS_CMPXEN                            BIT(0)                         /*!< CMPx enable */
#define CMP_CS_CMPXMSEL                          BITS(4,6)                      /*!< CMPx_IM input selection */
#define CMP_CS_CMPXOSEL                          BITS(10,13)                    /*!< CMPx output selection */
#define CMP_CS_CMPXPL                            BIT(15)                        /*!< CMPx output polarity */
#define CMP_CS_CMPXBLK                           BITS(18,20)                    /*!< CMPx output blanking source */
#define CMP_CS_CMPXMSEL_3                        BIT(22)                        /*!< bit3 of CMPx_CS_CMPxMSEL */
#define CMP_CS_CMPXO                             BIT(30)                        /*!< CMPx output */
#define CMP_CS_CMPXLK                            BIT(31)                        /*!< CMPx lock */

/* constants definitions */
/* CMP units */
typedef enum{
    CMP1,                                                                       /*!< comparator 1 */
    CMP3,                                                                       /*!< comparator 3 */
    CMP5                                                                        /*!< comparator 5 */
}cmp_enum;

/* CMP inverting input */
#define CS_CMPXMSEL(regval)                      (BITS(4,6) & ((uint32_t)(regval) << 4U))
#define CMP_INVERTING_INPUT_1_4VREFINT           CS_CMPXMSEL(0)                 /*!< CMP inverting input 1/4 Vrefint */
#define CMP_INVERTING_INPUT_1_2VREFINT           CS_CMPXMSEL(1)                 /*!< CMP inverting input 1/2 Vrefint */
#define CMP_INVERTING_INPUT_3_4VREFINT           CS_CMPXMSEL(2)                 /*!< CMP inverting input 3/4 Vrefint */
#define CMP_INVERTING_INPUT_VREFINT              CS_CMPXMSEL(3)                 /*!< CMP inverting input Vrefint */
#define CMP_INVERTING_INPUT_DAC0_OUT0            CS_CMPXMSEL(4)                 /*!< CMP inverting input DAC */
#define CMP_INVERTING_INPUT_PA5                  CS_CMPXMSEL(5)                 /*!< CMP inverting input PA5 */
#define CMP_INVERTING_INPUT_PA2                  CS_CMPXMSEL(6)                 /*!< CMP inverting input PA2 only for CMP1 */
#define CMP_INVERTING_INPUT_PB2_PB15             CS_CMPXMSEL(7)                 /*!< CMP inverting input PB2 for CMP3 or PB15 for CMP5 */

/* CMP output */
#define CS_CMPXOSEL(regval)                      (BITS(10,13) & ((uint32_t)(regval) << 10U))
#define CMP_OUTPUT_NONE                          CS_CMPXOSEL(0)                 /*!< CMP output none */
#define CMP_OUTPUT_TIMER0_BKIN                   CS_CMPXOSEL(1)                 /*!< CMP output TIMER0 break input */
#define CMP_OUTPUT_TIMER2_IC2                    CS_CMPXOSEL(6)                 /*!< CMP output TIMER2_CH2 input capture only for CMP3 */
#define CMP_OUTPUT_TIMER1_IC1                    CS_CMPXOSEL(6)                 /*!< CMP output TIMER1_CH1 input capture only for CMP5 */
#define CMP_OUTPUT_TIMER0_IC0                    CS_CMPXOSEL(7)                 /*!< CMP output TIMER0_CH0 input capture only for CMP1 */
#define CMP_OUTPUT_TIMER1_IC3                    CS_CMPXOSEL(8)                 /*!< CMP output TIMER1_CH3 input capture only for CMP1 */
#define CMP_OUTPUT_TIMER2_IC0                    CS_CMPXOSEL(10)                /*!< CMP output TIMER2_CH0 input capture only for CMP1 */

/* CMP output polarity*/
#define CS_CMPXPL(regval)                        (BIT(15) & ((uint32_t)(regval) << 15U))
#define CMP_OUTPUT_POLARITY_NONINVERTED          CS_CMPXPL(0)                   /*!< CMP output not inverted */
#define CMP_OUTPUT_POLARITY_INVERTED             CS_CMPXPL(1)                   /*!< CMP output inverted */

/* CMP blanking suorce */
#define CS_CMPXBLK(regval)                       (BITS(18,20) & ((uint32_t)(regval) << 18U))
#define CMP_BLANKING_NONE                        CS_CMPXBLK(0)                  /*!< CMP no blanking source */
#define CMP_BLANKING_TIMER2_OC3                  CS_CMPXBLK(1)                  /*!< CMP TIMER2_CH3 output compare signal selected as blanking source only for CMP3 */
#define CMP_BLANKING_TIMER1_OC2                  CS_CMPXBLK(2)                  /*!< CMP TIMER1_CH2 output compare signal selected as blanking source only for CMP1 */
#define CMP_BLANKING_TIMER2_OC2                  CS_CMPXBLK(3)                  /*!< CMP TIMER2_CH2 output compare signal selected as blanking source only for CMP1 */
#define CMP_BLANKING_TIMER1_OC3                  CS_CMPXBLK(3)                  /*!< CMP TIMER1_CH3 output compare signal selected as blanking source only for CMP5 */

/* CMP output level */
#define CMP_OUTPUTLEVEL_HIGH                     ((uint32_t)0x00000001U)        /*!< CMP output high */
#define CMP_OUTPUTLEVEL_LOW                      ((uint32_t)0x00000000U)        /*!< CMP output low */

/* function declarations */
/* initialization functions */
/* CMP deinit */
void cmp_deinit(cmp_enum cmp_periph);
/* CMP mode init */
void cmp_mode_init(cmp_enum cmp_periph, uint32_t inverting_input);
/* CMP output init */
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_selection, uint32_t output_polarity);
/* CMP output blanking function init */
void cmp_blanking_init(cmp_enum cmp_periph,uint32_t blanking_source_selection);

/* enable functions */
/* enable CMP */
void cmp_enable(cmp_enum cmp_periph);
/* disable CMP */
void cmp_disable(cmp_enum cmp_periph);
/* lock the CMP */
void cmp_lock_enable(cmp_enum cmp_periph);

/* get state related functions */
/* get output level */
uint32_t cmp_output_level_get(cmp_enum cmp_periph);

#endif /* GD32E50x_CL */
#endif /* GD32E50X_CMP_H */
