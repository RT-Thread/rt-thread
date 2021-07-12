/*!
    \file  gd32f3x0_cmp.h
    \brief definitions for the CMP

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

#ifndef GD32F3X0_CMP_H
#define GD32F3X0_CMP_H

#include "gd32f3x0.h"

/* CMP definitions */
#define CMP                                      CMP_BASE                       /*!< CMP base address */  

/* registers definitions */
#define CMP_CS                                   REG32((CMP) + 0x00000000U)     /*!< CMP control and status register */

/* CMP_CS bits definitions */
#define CMP_CS_CMP0EN                            BIT(0)                         /*!< CMP0 enable  */
#define CMP_CS_CMP0SW                            BIT(1)                         /*!< CMP0 switch */
#define CMP_CS_CMP0M                             BITS(2,3)                      /*!< CMP0 mode */
#define CMP_CS_CMP0MSEL                          BITS(4,6)                      /*!< COMP0_M input selection */
#define CMP_CS_CMP0OSEL                          BITS(8,10)                     /*!< CMP0 output selection */
#define CMP_CS_CMP0PL                            BIT(11)                        /*!< polarity of CMP0 output */
#define CMP_CS_CMP0HST                           BITS(12,13)                    /*!< CMP0 hysteresis */
#define CMP_CS_CMP0O                             BIT(14)                        /*!< CMP0 output */
#define CMP_CS_CMP0LK                            BIT(15)                        /*!< CMP0 lock */
#define CMP_CS_CMP1EN                            BIT(16)                        /*!< CMP1 enable */
#define CMP_CS_CMP1M                             BITS(18,19)                    /*!< CMP1 mode */
#define CMP_CS_CMP1MSEL                          BITS(20,22)                    /*!< CMP1_M input selection */
#define CMP_CS_WNDEN                             BIT(23)                        /*!< window mode enable */
#define CMP_CS_CMP1OSEL                          BITS(24,26)                    /*!< CMP1 output selection */
#define CMP_CS_CMP1PL                            BIT(27)                        /*!< polarity of CMP1 output */
#define CMP_CS_CMP1HST                           BITS(28,29)                    /*!< CMP1 hysteresis */
#define CMP_CS_CMP1O                             BIT(30)                        /*!< CMP1 output */
#define CMP_CS_CMP1LK                            BIT(31)                        /*!< CMP1 lock */

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
    CMP_DAC,                                                                    /*!< PA4 (DAC) input */
    CMP_PA5,                                                                    /*!< PA5 input */
    CMP_PA_0_2                                                                  /*!< PA0 or PA2 input */
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
    CMP_OUTPUT_NONE = 0,                                                        /*!< output no selection */
    CMP_OUTPUT_TIMER0BKIN,                                                      /*!< TIMER 0 break input */
    CMP_OUTPUT_TIMER0IC0,                                                       /*!< TIMER 0 channel0 input capture */
    CMP_OUTPUT_TIMER0OCPRECLR,                                                  /*!< TIMER 0 OCPRE_CLR input */
    CMP_OUTPUT_TIMER1IC3,                                                       /*!< TIMER 1 channel3 input capture */
    CMP_OUTPUT_TIMER1OCPRECLR,                                                  /*!< TIMER 1 OCPRE_CLR input */
    CMP_OUTPUT_TIMER2IC0,                                                       /*!< TIMER 2 channel0 input capture */
    CMP_OUTPUT_TIMER2OCPRECLR                                                   /*!< TIMER 2 OCPRE_CLR input */
}cmp_output_enum;

/* CMP0 mode */
#define CS_CMP0M(regval)                         (BITS(2,3) & ((uint32_t)(regval) << 2))
#define CS_CMP0M_HIGHSPEED                       CS_CMP0M(0)                    /*!< CMP0 mode high speed */
#define CS_CMP0M_MIDDLESPEED                     CS_CMP0M(1)                    /*!< CMP0 mode middle speed */
#define CS_CMP0M_LOWSPEED                        CS_CMP0M(2)                    /*!< CMP0 mode low speed */
#define CS_CMP0M_VERYLOWSPEED                    CS_CMP0M(3)                    /*!< CMP0 mode very low speed */

/* comparator 0 inverting input */
#define CS_CMP0MSEL(regval)                      (BITS(4,6) & ((uint32_t)(regval) << 4))
#define CS_CMP0MSEL_1_4VREFINT                   CS_CMP0MSEL(0)                 /*!< CMP0 inverting input 1/4 Vrefint */
#define CS_CMP0MSEL_1_2VREFINT                   CS_CMP0MSEL(1)                 /*!< CMP0 inverting input 1/2 Vrefint */
#define CS_CMP0MSEL_3_4VREFINT                   CS_CMP0MSEL(2)                 /*!< CMP0 inverting input 3/4 Vrefint */
#define CS_CMP0MSEL_VREFINT                      CS_CMP0MSEL(3)                 /*!< CMP0 inverting input Vrefint */
#define CS_CMP0MSEL_DAC                          CS_CMP0MSEL(4)                 /*!< CMP0 inverting input DAC*/
#define CS_CMP0MSEL_PA5                          CS_CMP0MSEL(5)                 /*!< CMP0 inverting input PA5*/
#define CS_CMP0MSEL_PA0                          CS_CMP0MSEL(6)                 /*!< CMP0 inverting input PA0*/

/* CMP0 output */
#define CS_CMP0OSEL(regval)                      (BITS(8,10) & ((uint32_t)(regval) << 8))
#define CS_CMP0OSEL_OUTPUT_NONE                  CS_CMP0OSEL(0)                 /*!< CMP0 output none  */
#define CS_CMP0OSEL_OUTPUT_TIMER0BKIN            CS_CMP0OSEL(1)                 /*!< CMP0 output TIMER 0 break input */
#define CS_CMP0OSEL_OUTPUT_TIMER0IC0             CS_CMP0OSEL(2)                 /*!< CMP0 output TIMER 0 channel 0 input capture */
#define CS_CMP0OSEL_OUTPUT_TIMER0OCPRECLR        CS_CMP0OSEL(3)                 /*!< CMP0 output TIMER 0 ocpreclear input */ 
#define CS_CMP0OSEL_OUTPUT_TIMER1IC3             CS_CMP0OSEL(4)                 /*!< CMP0 output TIMER 1 channel 3 input capture */
#define CS_CMP0OSEL_OUTPUT_TIMER1OCPRECLR        CS_CMP0OSEL(5)                 /*!< CMP0 output TIMER 1 ocpreclear input */
#define CS_CMP0OSEL_OUTPUT_TIMER2IC0             CS_CMP0OSEL(6)                 /*!< CMP0 output TIMER 2 channle 0 input capture */
#define CS_CMP0OSEL_OUTPUT_TIMER2OCPRECLR        CS_CMP0OSEL(7)                 /*!< CMP0 output TIMER 2 ocpreclear input */

/* CMP0 hysteresis */
#define CS_CMP0HST(regval)                       (BITS(12,13) & ((uint32_t)(regval) << 12))
#define CS_CMP0HST_HYSTERESIS_NO                 CS_CMP0HST(0)                  /*!< CMP0 output no hysteresis */
#define CS_CMP0HST_HYSTERESIS_LOW                CS_CMP0HST(1)                  /*!< CMP0 output low hysteresis */
#define CS_CMP0HST_HYSTERESIS_MIDDLE             CS_CMP0HST(2)                  /*!< CMP0 output middle hysteresis */
#define CS_CMP0HST_HYSTERESIS_HIGH               CS_CMP0HST(3)                  /*!< CMP0 output high hysteresis */

/* CMP1 mode */
#define CS_CMP1M(regval)                         (BITS(18,19) & ((uint32_t)(regval) << 18))
#define CS_CMP1M_HIGHSPEED                       CS_CMP1M(0)                    /*!< CMP1 mode high speed */
#define CS_CMP1M_MIDDLESPEED                     CS_CMP1M(1)                    /*!< CMP1 mode middle speed */
#define CS_CMP1M_LOWSPEED                        CS_CMP1M(2)                    /*!< CMP1 mode low speed */
#define CS_CMP1M_VERYLOWSPEED                    CS_CMP1M(3)                    /*!< CMP1 mode very low speed */

/* CMP1 inverting input */
#define CS_CMP1MSEL(regval)                      (BITS(20,22) & ((uint32_t)(regval) << 20))
#define CS_CMP1MSEL_1_4VREFINT                   CS_CMP1MSEL(0)                 /*!< CMP1 inverting input 1/4 Vrefint */
#define CS_CMP1MSEL_1_2VREFINT                   CS_CMP1MSEL(1)                 /*!< CMP1 inverting input 1/2 Vrefint */
#define CS_CMP1MSEL_3_4VREFINT                   CS_CMP1MSEL(2)                 /*!< CMP1 inverting input 3/4 Vrefint */
#define CS_CMP1MSEL_VREFINT                      CS_CMP1MSEL(3)                 /*!< CMP1 inverting input Vrefint */
#define CS_CMP1MSEL_DAC                          CS_CMP1MSEL(4)                 /*!< CMP1 inverting input DAC */
#define CS_CMP1MSEL_PA5                          CS_CMP1MSEL(5)                 /*!< CMP1 inverting input PA5 */
#define CS_CMP1MSEL_PA2                          CS_CMP1MSEL(6)                 /*!< CMP1 inverting input PA2 */

/* CMP1 output */
#define CS_CMP1OSEL(regval)                      (BITS(24,26) & ((uint32_t)(regval) << 24))
#define CS_CMP1OSEL_OUTPUT_NONE                  CS_CMP1OSEL(0)                 /*!< CMP1 output none  */
#define CS_CMP1OSEL_OUTPUT_TIMER0BKIN            CS_CMP1OSEL(1)                 /*!< CMP1 output TIMER 0 break input */
#define CS_CMP1OSEL_OUTPUT_TIMER0IC0             CS_CMP1OSEL(2)                 /*!< CMP1 output TIMER 0 channel 0 input capture */
#define CS_CMP1OSEL_OUTPUT_TIMER0OCPRECLR        CS_CMP1OSEL(3)                 /*!< CMP1 output TIMER 0 ocpreclear input */ 
#define CS_CMP1OSEL_OUTPUT_TIMER1IC3             CS_CMP1OSEL(4)                 /*!< CMP1 output TIMER 1 channel 3 input capture */
#define CS_CMP1OSEL_OUTPUT_TIMER1OCPRECLR        CS_CMP1OSEL(5)                 /*!< CMP1 output TIMER 1 ocpreclear input */
#define CS_CMP1OSEL_OUTPUT_TIMER2IC0             CS_CMP1OSEL(6)                 /*!< CMP1 output TIMER 2 channle 0 input capture */
#define CS_CMP1OSEL_OUTPUT_TIMER2OCPRECLR        CS_CMP1OSEL(7)                 /*!< CMP1 output TIMER 2 ocpreclear input */

/* CMP1 hysteresis */
#define CS_CMP1HST(regval)                       (BITS(28,29) & ((uint32_t)(regval) << 28))
#define CS_CMP1HST_HSTHYSTERESIS_NO              CS_CMP1HST(0)                  /*!< CMP1 output no hysteresis */
#define CS_CMP1HST_HYSTERESIS_LOW                CS_CMP1HST(1)                  /*!< CMP1 output low hysteresis */
#define CS_CMP1HST_HYSTERESIS_MIDDLE             CS_CMP1HST(2)                  /*!< CMP1 output middle hysteresis */
#define CS_CMP1HST_HYSTERESIS_HIGH               CS_CMP1HST(3)                  /*!< CMP1 output high hysteresis */

/* comparator x definitions */
#define CMP0                                     ((uint32_t)0x00000000)          /*!< comparator 0 */
#define CMP1                                     ((uint32_t)0x00000010)          /*!< comparator 1 */

/* comparator output level */
#define CMP_OUTPUTLEVEL_HIGH                     ((uint32_t)0x00000001)          /*!< comparator output high */
#define CMP_OUTPUTLEVEL_LOW                      ((uint32_t)0x00000000)          /*!< comparator output low */

/* output polarity of comparator */
#define CMP_OUTPUT_POLARITY_INVERTED             ((uint32_t)0x00000001)          /*!< output is inverted */
#define CMP_OUTPUT_POLARITY_NOINVERTED           ((uint32_t)0x00000000)          /*!< output is not inverted */

/* function declarations */

/* initialization functions */
/* CMP deinit */
void cmp_deinit(void);
/* CMP mode init */
void cmp_mode_init(uint32_t cmp_periph, operating_mode_enum operating_mode, inverting_input_enum inverting_input, cmp_hysteresis_enum output_hysteresis);
/* CMP output init */
void cmp_output_init(uint32_t cmp_periph, cmp_output_enum output_slection, uint32_t output_polarity);

/* enable functions */
/* enable CMP */
void cmp_enable(uint32_t cmp_periph);
/* disable CMP */
void cmp_disable(uint32_t cmp_periph);
/* enable CMP switch */
void cmp_switch_enable(void);
/* disable CMP switch */
void cmp_switch_disable(void);
/* enable the window mode */
void cmp_window_enable(void);
/* disable the window mode */
void cmp_window_disable(void);
/* lock the CMP */
void cmp_lock_enable(uint32_t cmp_periph);

/* output functions */
/* get output level */
uint32_t cmp_output_level_get(uint32_t cmp_periph);

#endif /* GD32F3X0_CMP_H */
