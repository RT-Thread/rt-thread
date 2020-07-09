/*!
    \file  gd32e230_cmp.h
    \brief definitions for the CMP

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

#ifndef GD32E230_CMP_H
#define GD32E230_CMP_H

#include "gd32e230.h"

/* CMP definitions */
#define CMP                                      CMP_BASE                       /*!< CMP base address */  

/* registers definitions */
#define CMP_CS                                   REG32((CMP) + 0x00U)           /*!< CMP control and status register */

/* CMP_CS bits definitions */
#define CMP_CS_CMPEN                             BIT(0)                         /*!< CMP enable  */
#define CMP_CS_CMPSW                             BIT(1)                         /*!< CMP switch */
#define CMP_CS_CMPM                              BITS(2,3)                      /*!< CMP mode */
#define CMP_CS_CMPMSEL                           BITS(4,6)                      /*!< COMP_M input selection */
#define CMP_CS_CMPOSEL                           BITS(8,10)                     /*!< CMP output selection */
#define CMP_CS_CMPPL                             BIT(11)                        /*!< polarity of CMP output */
#define CMP_CS_CMPHST                            BITS(12,13)                    /*!< CMP hysteresis */
#define CMP_CS_CMPO                              BIT(14)                        /*!< CMP output */
#define CMP_CS_CMPLK                             BIT(15)                        /*!< CMP lock */

/* consts definitions */
/* operating mode */
typedef enum{
    CMP_HIGHSPEED = 0,                                                          /*!< high speed mode */
    CMP_MIDDLESPEED,                                                            /*!< medium speed mode */
    CMP_LOWSPEED,                                                               /*!< low speed mode */
    CMP_VERYLOWSPEED                                                            /*!< very-low speed mode */
}operating_mode_enum;

/* inverting input */
typedef enum{
    CMP_1_4VREFINT = 0,                                                         /*!< VREFINT /4 input */
    CMP_1_2VREFINT,                                                             /*!< VREFINT /2 input */
    CMP_3_4VREFINT,                                                             /*!< VREFINT *3/4 input */
    CMP_VREFINT,                                                                /*!< VREFINT input */
    CMP_PA4,                                                                    /*!< PA4 input */
    CMP_PA5,                                                                    /*!< PA5 input */
    CMP_PA0,                                                                    /*!< PA0 input */
    CMP_PA2                                                                     /*!< PA2 input */
}inverting_input_enum;

/* hysteresis */
typedef enum{
    CMP_HYSTERESIS_NO = 0,                                                      /*!< output no hysteresis */
    CMP_HYSTERESIS_LOW,                                                         /*!< output low hysteresis */
    CMP_HYSTERESIS_MIDDLE,                                                      /*!< output middle hysteresis */
    CMP_HYSTERESIS_HIGH                                                         /*!< output high hysteresis */
}cmp_hysteresis_enum;

/* output */  
typedef enum{
    CMP_OUTPUT_NONE = 0x0U,                                                     /*!< output no selection */
    CMP_OUTPUT_TIMER0BKIN = 0x1U,                                               /*!< TIMER 0 break input */
    CMP_OUTPUT_TIMER0IC0 = 0x2U,                                                /*!< TIMER 0 channel0 input capture */
    CMP_OUTPUT_TIMER0OCPRECLR = 0x3U,                                           /*!< TIMER 0 OCPRE_CLR input */
    CMP_OUTPUT_TIMER2IC0 = 0x06U,                                               /*!< TIMER 2 channel0 input capture */
    CMP_OUTPUT_TIMER2OCPRECLR = 0x7U                                            /*!< TIMER 2 OCPRE_CLR input */
}cmp_output_enum;

/* CMP mode */
#define CS_CMPM(regval)                         (BITS(2,3) & ((uint32_t)(regval) << 2))
#define CS_CMPM_HIGHSPEED                       CS_CMPM(0)                      /*!< CMP mode high speed */
#define CS_CMPM_MIDDLESPEED                     CS_CMPM(1)                      /*!< CMP mode middle speed */
#define CS_CMPM_LOWSPEED                        CS_CMPM(2)                      /*!< CMP mode low speed */
#define CS_CMPM_VERYLOWSPEED                    CS_CMPM(3)                      /*!< CMP mode very low speed */

/* comparator inverting input */
#define CS_CMPMSEL(regval)                      (BITS(4,6) & ((uint32_t)(regval) << 4))
#define CS_CMPMSEL_1_4VREFINT                   CS_CMPMSEL(0)                   /*!< CMP inverting input 1/4 Vrefint */
#define CS_CMPMSEL_1_2VREFINT                   CS_CMPMSEL(1)                   /*!< CMP inverting input 1/2 Vrefint */
#define CS_CMPMSEL_3_4VREFINT                   CS_CMPMSEL(2)                   /*!< CMP inverting input 3/4 Vrefint */
#define CS_CMPMSEL_VREFINT                      CS_CMPMSEL(3)                   /*!< CMP inverting input Vrefint */
#define CS_CMPMSEL_PA4                          CS_CMPMSEL(4)                   /*!< CMP inverting input PA4*/
#define CS_CMPMSEL_PA5                          CS_CMPMSEL(5)                   /*!< CMP inverting input PA5*/
#define CS_CMPMSEL_PA0                          CS_CMPMSEL(6)                   /*!< CMP inverting input PA0*/
#define CS_CMPMSEL_PA2                          CS_CMPMSEL(7)                   /*!< CMP inverting input PA2*/

/* CMP output */
#define CS_CMPOSEL(regval)                      (BITS(8,10) & ((uint32_t)(regval) << 8))
#define CS_CMPOSEL_OUTPUT_NONE                  CS_CMPOSEL(0)                   /*!< CMP output none  */
#define CS_CMPOSEL_OUTPUT_TIMER0BKIN            CS_CMPOSEL(1)                   /*!< CMP output TIMER 0 break input */
#define CS_CMPOSEL_OUTPUT_TIMER0IC0             CS_CMPOSEL(2)                   /*!< CMP output TIMER 0 channel 0 input capture */
#define CS_CMPOSEL_OUTPUT_TIMER0OCPRECLR        CS_CMPOSEL(3)                   /*!< CMP output TIMER 0 ocpreclear input */ 
#define CS_CMPOSEL_OUTPUT_TIMER2IC0             CS_CMPOSEL(6)                   /*!< CMP output TIMER 2 channle 0 input capture */
#define CS_CMPOSEL_OUTPUT_TIMER2OCPRECLR        CS_CMPOSEL(7)                   /*!< CMP output TIMER 2 ocpreclear input */

/* CMP hysteresis */
#define CS_CMPHST(regval)                       (BITS(12,13) & ((uint32_t)(regval) << 12))
#define CS_CMPHST_HYSTERESIS_NO                 CS_CMPHST(0)                    /*!< CMP output no hysteresis */
#define CS_CMPHST_HYSTERESIS_LOW                CS_CMPHST(1)                    /*!< CMP output low hysteresis */
#define CS_CMPHST_HYSTERESIS_MIDDLE             CS_CMPHST(2)                    /*!< CMP output middle hysteresis */
#define CS_CMPHST_HYSTERESIS_HIGH               CS_CMPHST(3)                    /*!< CMP output high hysteresis */

/* CMP output level */
#define CMP_OUTPUTLEVEL_HIGH                     ((uint32_t)0x00000001)         /*!< comparator output high */
#define CMP_OUTPUTLEVEL_LOW                      ((uint32_t)0x00000000)         /*!< comparator output low */

/* output polarity of comparator */
#define CMP_OUTPUT_POLARITY_INVERTED             ((uint32_t)0x00000001)         /*!< output is inverted */
#define CMP_OUTPUT_POLARITY_NOINVERTED           ((uint32_t)0x00000000)         /*!< output is not inverted */

/* function declarations */

/* initialization functions */
/* CMP deinit */
void cmp_deinit(void);
/* CMP mode init */
void cmp_mode_init(operating_mode_enum operating_mode, inverting_input_enum inverting_input, cmp_hysteresis_enum output_hysteresis);
/* CMP output init */
void cmp_output_init(cmp_output_enum output_slection, uint32_t output_polarity);
/* enable CMP */
void cmp_enable(void);
/* disable CMP */
void cmp_disable(void);
/* enable CMP switch */
void cmp_switch_enable(void);
/* disable CMP switch */
void cmp_switch_disable(void);
/* get output level */
uint32_t cmp_output_level_get(void);
/* lock the CMP */
void cmp_lock_enable(void);

#endif /* GD32E230_CMP_H */
