/*!
    \file    gd32h7xx_cmp.h
    \brief   definitions for the CMP

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

#ifndef GD32H7XX_CMP_H
#define GD32H7XX_CMP_H

#include "gd32h7xx.h"

/* CMP definitions */
#define CMP                                      CMP_BASE                       /*!< CMP base address */

/* registers definitions */
#define CMP_STAT                                 REG32((CMP) + 0x00000000U)     /*!< CMP status register */
#define CMP_IFC                                  REG32((CMP) + 0x00000004U)     /*!< CMP interrupt flag clear register */
#define CMP_SR                                   REG32((CMP) + 0x00000008U)     /*!< CMP alternate select register */
#define CMP0_CS                                  REG32((CMP) + 0x0000000CU)     /*!< CMP0 control and status register */
#define CMP1_CS                                  REG32((CMP) + 0x00000010U)     /*!< CMP1 control and status register */

/* bits definitions */
/* CMP_STAT */
#define CMP_STAT_CMP0O                           BIT(0)                         /*!< CMP0 output */
#define CMP_STAT_CMP1O                           BIT(1)                         /*!< CMP1 output */
#define CMP_STAT_CMP0IF                          BIT(16)                        /*!< CMP0 interrupt flag */
#define CMP_STAT_CMP1IF                          BIT(17)                        /*!< CMP1 interrupt flag */

/* CMP_IFC */
#define CMP_IFC_CMP0IC                           BIT(16)                        /*!< CMP0 interrupt flag clear */
#define CMP_IFC_CMP1IC                           BIT(17)                        /*!< CMP1 interrupt flag clear */

/* CMP_SR */
#define CMP_SR_AFSE_PA6                          BITS(0,10)                     /*!< CMP selects alternate output ports PA6 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PA8                          BIT(1)                         /*!< PA8 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PB12                         BIT(2)                         /*!< PB12 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PE6                          BIT(3)                         /*!< PE6 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PE15                         BIT(4)                         /*!< PE15 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PG2                          BIT(5)                         /*!< PG2 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PG3                          BIT(6)                         /*!< PG3 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PG4                          BIT(7)                         /*!< PG4 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PK0                          BIT(8)                         /*!< PK0 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PK1                          BIT(9)                         /*!< PK1 alternate function select for CMPx_OUT */
#define CMP_SR_AFSE_PK2                          BIT(10)                        /*!< PK2 alternate function select for CMPx_OUT */

/* CMPx_CS */
#define CMP_CS_CMPXEN                            BIT(0)                         /*!< CMPx enable  */
#define CMP_CS_CMPXBEN                           BIT(1)                         /*!< CMPx scaler bridge enable bit */
#define CMP_CS_CMPXSEN                           BIT(2)                         /*!< CMPx voltage scaler enable bit */
#define CMP_CS_CMPXPL                            BIT(3)                         /*!< CMPx output polarity */
#define CMP_CS_WNDEN                             BIT(4)                         /*!< CMP Window mode enable */
#define CMP_CS_CMPXINTEN                         BIT(6)                         /*!< CMPx interrupt enable */
#define CMP_CS_CMPXHST                           BITS(8,9)                      /*!< CMPx hysteresis */
#define CMP_CS_CMPXM                             BITS(12,13)                    /*!< CMPx mode */
#define CMP_CS_CMPXMISEL                         BITS(16,18)                    /*!< CMP_IM input selection */
#define CMP_CS_CMPXPSEL                          BIT(20)                        /*!< CMP_IP input selection */
#define CMP_CS_CMPXBLK                           BITS(24,27)                    /*!< CMPx output blanking source */
#define CMP_CS_CMPXLK                            BIT(31)                        /*!< CMPx lock */


/* constants definitions */
/* CMP units */
typedef enum{
    CMP0,                                                                       /*!< comparator 0 */
    CMP1                                                                        /*!< comparator 1 */
}cmp_enum;

/* CMP operating mode */
#define CS_CMPXM(regval)                         (BITS(12,13) & ((uint32_t)(regval) << 12U))
#define CMP_MODE_HIGHSPEED                       CS_CMPXM(0)                    /*!< CMP mode high speed */
#define CMP_MODE_MIDDLESPEED                     CS_CMPXM(1)                    /*!< CMP mode middle speed */
#define CMP_MODE_VERYLOWSPEED                    CS_CMPXM(3)                    /*!< CMP mode very low speed */

/* CMP hysteresis */
#define CS_CMPXHST(regval)                       (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define CMP_HYSTERESIS_NO                        CS_CMPXHST(0)                  /*!< CMP output no hysteresis */
#define CMP_HYSTERESIS_LOW                       CS_CMPXHST(1)                  /*!< CMP output low hysteresis */
#define CMP_HYSTERESIS_MIDDLE                    CS_CMPXHST(2)                  /*!< CMP output middle hysteresis */
#define CMP_HYSTERESIS_HIGH                      CS_CMPXHST(3)                  /*!< CMP output high hysteresis */

/* CMP inverting input */
#define CS_CMPXMSEL(regval)                      (BITS(16,18) & ((uint32_t)(regval) << 16U))
#define CMP_INVERTING_INPUT_1_4VREFINT           CS_CMPXMSEL(0)                 /*!< CMP inverting input 1/4 Vrefint */
#define CMP_INVERTING_INPUT_1_2VREFINT           CS_CMPXMSEL(1)                 /*!< CMP inverting input 1/2 Vrefint */
#define CMP_INVERTING_INPUT_3_4VREFINT           CS_CMPXMSEL(2)                 /*!< CMP inverting input 3/4 Vrefint */
#define CMP_INVERTING_INPUT_VREFINT              CS_CMPXMSEL(3)                 /*!< CMP inverting input Vrefint */
#define CMP_INVERTING_INPUT_PA4                  CS_CMPXMSEL(4)                 /*!< CMP inverting input DAC0_OUT0 */
#define CMP_INVERTING_INPUT_PA5                  CS_CMPXMSEL(5)                 /*!< CMP inverting input DAC0_OUT1 */
#define CMP_INVERTING_INPUT_PB1_PE10             CS_CMPXMSEL(6)                 /*!< CMP inverting input PB1 for CMP0 or PE10 for CMP1 */
#define CMP_INVERTING_INPUT_PC4_PE7              CS_CMPXMSEL(7)                 /*!< CMP inverting input PC4 for CMP0 or PE7 for CMP1 */

/* CMP noninverting input*/
#define CS_CMPXPSEL(regval)                      (BIT(20) & ((uint32_t)(regval) << 20U))
#define CMP_NONINVERTING_INPUT_PB0_PE9           CS_CMPXPSEL(0)                 /*!< CMP noninverting input PB0 for CMP0 or PE9 for CMP1 */
#define CMP_NONINVERTING_INPUT_PB2_PE11          CS_CMPXPSEL(1)                 /*!< CMP noninverting input PB2 for CMP0 or PE11 for CMP1 */

/* CMP output polarity*/
#define CS_CMPXPL(regval)                        (BIT(3) & ((uint32_t)(regval) << 3U))
#define CMP_OUTPUT_POLARITY_NONINVERTED          CS_CMPXPL(0)                   /*!< CMP output not inverted */
#define CMP_OUTPUT_POLARITY_INVERTED             CS_CMPXPL(1)                   /*!< CMP output inverted */

/* CMP blanking suorce */
#define CS_CMPXBLK(regval)                       (BITS(24,27) & ((uint32_t)(regval) << 24U))
#define CMP_BLANKING_NONE                         CS_CMPXBLK(0)                 /*!< CMP no blanking source */
#define CMP_BLANKING_TIMER0_OC0                   CS_CMPXBLK(1)                 /*!< CMP TIMER0_CH0 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER1_OC2                   CS_CMPXBLK(2)                 /*!< CMP TIMER1_CH2 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER2_OC2                   CS_CMPXBLK(3)                 /*!< CMP TIMER2_CH2 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER2_OC3                   CS_CMPXBLK(4)                 /*!< CMP TIMER2_CH3 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER7_OC4                   CS_CMPXBLK(5)                 /*!< CMP TIMER7_CH0 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER14_OC0                  CS_CMPXBLK(6)                 /*!< CMP TIMER14_CH0 output compare signal selected as blanking source */

/* comparator output level */
#define CMP_OUTPUTLEVEL_HIGH                     ((uint32_t)0x00000001U)        /*!< comparator output high */
#define CMP_OUTPUTLEVEL_LOW                      ((uint32_t)0x00000000U)        /*!< comparator output low */

/* CMP alternate output ports */
#define SR_AFSE(regval)                          (BITS(0,10) & ((uint32_t)(regval) << 0U))
#define CMP_AFSE_GPIO_PA6                        SR_AFSE(0)                     /*!< CMP alternate GPIO PA6 */
#define CMP_AFSE_GPIO_PA8                        SR_AFSE(1)                     /*!< CMP alternate GPIO PA8 */
#define CMP_AFSE_GPIO_PB12                       SR_AFSE(2)                     /*!< CMP alternate GPIO PB12 */
#define CMP_AFSE_GPIO_PE6                        SR_AFSE(3)                     /*!< CMP alternate GPIO PE6 */
#define CMP_AFSE_GPIO_PE15                       SR_AFSE(4)                     /*!< CMP alternate GPIO PE15 */
#define CMP_AFSE_GPIO_PG2                        SR_AFSE(5)                     /*!< CMP alternate GPIO PG2 */
#define CMP_AFSE_GPIO_PG3                        SR_AFSE(6)                     /*!< CMP alternate GPIO PG3 */
#define CMP_AFSE_GPIO_PG4                        SR_AFSE(7)                     /*!< CMP alternate GPIO PG4 */
#define CMP_AFSE_GPIO_PK0                        SR_AFSE(8)                     /*!< CMP alternate GPIO PK0 */
#define CMP_AFSE_GPIO_PK1                        SR_AFSE(9)                     /*!< CMP alternate GPIO PK1*/
#define CMP_AFSE_GPIO_PK2                        SR_AFSE(10)                    /*!< CMP alternate GPIO PK2 */

/* CMP flag definitions */
#define CMP_FLAG_COMPARE                         CMP_STAT_CMP0IF                /*!< CMP compare flag */

/* CMP interrupt definitions */
#define CMP_INT_COMPARE                          CMP_CS_CMPXINTEN               /*!< CMP compare interrupt */

/* CMP interrupt flag */
#define CMP_INT_FLAG_COMPARE                     CMP_STAT_CMP0IF                /*!< CMP interrupt flag */

/* function declarations */
/* initialization functions */
/* CMP deinit */
void cmp_deinit(cmp_enum cmp_periph);
/* CMP mode init */
void cmp_mode_init(cmp_enum cmp_periph, uint32_t operating_mode, uint32_t inverting_input, uint32_t output_hysteresis);
/* CMP noninverting input select */
void cmp_noninverting_input_select(cmp_enum cmp_periph, uint32_t noninverting_input);
/* CMP output init */
void cmp_output_init(cmp_enum cmp_periph, uint32_t output_polarity);
/* config comparator output port */
void cmp_output_mux_config(cmp_enum cmp_periph, uint32_t cmp_output_sel);
/* CMP output blanking function init */
void cmp_blanking_init(cmp_enum cmp_periph,uint32_t blanking_source_selection);

/* enable functions */
/* enable CMP */
void cmp_enable(cmp_enum cmp_periph);
/* disable CMP */
void cmp_disable(cmp_enum cmp_periph);
/* enable the window mode */
void cmp_window_enable(void);
/* disable the window mode */
void cmp_window_disable(void);
/* lock the CMP */
void cmp_lock_enable(cmp_enum cmp_periph);
/* enable the voltage scaler */
void cmp_voltage_scaler_enable(cmp_enum cmp_periph);
/* disable the voltage scaler */
void cmp_voltage_scaler_disable(cmp_enum cmp_periph);
/* enable the scaler bridge */
void cmp_scaler_bridge_enable(cmp_enum cmp_periph);
/* disable the scaler bridge */
void cmp_scaler_bridge_disable(cmp_enum cmp_periph);

/* get state related functions */
/* get output level */
uint32_t cmp_output_level_get(cmp_enum cmp_periph);

/* flag and interrupt functions */
/* get CMP flag */
FlagStatus cmp_flag_get(cmp_enum cmp_periph, uint32_t flag);
/* clear CMP flag */
void cmp_flag_clear(cmp_enum cmp_periph, uint32_t flag);
/* enable CMP interrupt */
void cmp_interrupt_enable(cmp_enum cmp_periph, uint32_t interrupt);
/* disable CMP interrupt */
void cmp_interrupt_disable(cmp_enum cmp_periph, uint32_t interrupt);
/* get CMP interrupt flag */
FlagStatus cmp_interrupt_flag_get(cmp_enum cmp_periph, uint32_t flag);
/* clear CMP interrupt flag */
void cmp_interrupt_flag_clear(cmp_enum cmp_periph, uint32_t flag);

#endif /* GD32H7XX_CMP_H */
