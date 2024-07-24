/*!
    \file    gd32h7xx_trigsel.c
    \brief   TRIGSEL driver

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

#include "gd32h7xx_trigsel.h"

/* TRIGSEL target register redefine */
#define TRIGSEL_TARGET_REG(target_periph)           (REG32(TRIGSEL + ((uint32_t)(target_periph) & BITS(2,31))))            /*!< target peripheral register */
#define TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)  (((uint32_t)(target_periph) & BITS(0,1)) << 3U)                        /*!< bit offset in target peripheral register */
#define TRIGSEL_TARGET_PERIPH_MASK(target_periph)   ((uint32_t)(BITS(0,7) << TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)))  /*!< bit mask in target peripheral register */

/*!
    \brief      deinitialize TRIGSEL
    \param[in]  none
    \param[out] none
    \retval     none
*/
void trigsel_deinit(void)
{
    rcu_periph_reset_enable(RCU_TRIGSELRST);
    rcu_periph_reset_disable(RCU_TRIGSELRST);
}

/*!
    \brief      set the trigger input signal for target peripheral
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_ADC0_REGTRG: output target peripheral ADC0_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC1_REGTRG: output target peripheral ADC1_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC2_REGTRG: output target peripheral ADC2_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg        TRIGSEL_OUTPUT_DAC_OUT0_EXTRG: output target peripheral DAC_OUT0_EXTRG
      \arg        TRIGSEL_OUTPUT_DAC_OUT1_EXTRG: output target peripheral DAC_OUT1_EXTRG
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER14_BRKIN0: output target peripheral TIMER14_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER15_BRKIN0: output target peripheral TIMER15_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER16_BRKIN0: output target peripheral TIMER16_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER40_BRKIN0: output target peripheral TIMER40_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER41_BRKIN0: output target peripheral TIMER41_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER42_BRKIN0: output target peripheral TIMER42_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER43_BRKIN0: output target peripheral TIMER43_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER44_BRKIN0: output target peripheral TIMER44_BRKIN0
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_LPDTS_TRG: output target peripheral LPDTS_TRG
      \arg        TRIGSEL_OUTPUT_TIMER0_ETI: output target peripheral TIMER0_ETI
      \arg        TRIGSEL_OUTPUT_TIMER1_ETI: output target peripheral TIMER1_ETI
      \arg        TRIGSEL_OUTPUT_TIMER2_ETI: output target peripheral TIMER2_ETI
      \arg        TRIGSEL_OUTPUT_TIMER3_ETI: output target peripheral TIMER3_ETI
      \arg        TRIGSEL_OUTPUT_TIMER4_ETI: output target peripheral TIMER4_ETI
      \arg        TRIGSEL_OUTPUT_TIMER7_ETI: output target peripheral TIMER7_ETI
      \arg        TRIGSEL_OUTPUT_TIMER22_ETI: output target peripheral TIMER22_ETI
      \arg        TRIGSEL_OUTPUT_TIMER23_ETI: output target peripheral TIMER23_ETI
      \arg        TRIGSEL_OUTPUT_TIMER30_ETI: output target peripheral TIMER30_ETI
      \arg        TRIGSEL_OUTPUT_TIMER31_ETI: output target peripheral TIMER31_ETI
      \arg        TRIGSEL_OUTPUT_EDOUT_TRG: output target peripheral EDOUT_TRG
      \arg        TRIGSEL_OUTPUT_HPDF_ITRG: output target peripheral HPDF_ITR
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI14: output target peripheral TIMER0_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI14: output target peripheral TIMER1_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI14: output target peripheral TIMER2_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER3_ITI14: output target peripheral TIMER3_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER4_ITI14: output target peripheral TIMER4_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI14: output target peripheral TIMER7_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER14_ITI14: output target peripheral TIMER14_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER22_ITI14: output target peripheral TIMER22_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER23_ITI14: output target peripheral TIMER23_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER30_ITI14: output target peripheral TIMER30_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER31_ITI14: output target peripheral TIMER31_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER40_ITI14: output target peripheral TIMER40_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER41_ITI14: output target peripheral TIMER41_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER42_ITI14: output target peripheral TIMER42_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER43_ITI14: output target peripheral TIMER43_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER44_ITI14: output target peripheral TIMER44_ITI14
    \param[in]  trigger_source: trigger source value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_INPUT_0: trigger input source 0
      \arg        TRIGSEL_INPUT_1: trigger input source 1
      \arg        TRIGSEL_INPUT_TRIGSEL_IN0: trigger input source TRIGSEL_IN0 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN1: trigger input source TRIGSEL_IN1 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN2: trigger input source TRIGSEL_IN2 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN3: trigger input source TRIGSEL_IN3 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN4: trigger input source TRIGSEL_IN4 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN5: trigger input source TRIGSEL_IN5 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN6: trigger input source TRIGSEL_IN6 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN7: trigger input source TRIGSEL_IN7 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN8: trigger input source TRIGSEL_IN8 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN9: trigger input source TRIGSEL_IN9 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN10: trigger input source TRIGSEL_IN10 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN11: trigger input source TRIGSEL_IN11 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN12: trigger input source TRIGSEL_IN12 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN13: trigger input source TRIGSEL_IN13 pin
      \arg        TRIGSEL_INPUT_LXTAL_TRG: trigger input source LXTAL_TRG
      \arg        TRIGSEL_INPUT_TIMER0_TRGO0: trigger input source TIMER0 TRGO0
      \arg        TRIGSEL_INPUT_TIMER0_TRGO1: trigger input source TIMER0 TRGO1
      \arg        TRIGSEL_INPUT_TIMER0_CH0: trigger input source TIMER0 CH0
      \arg        TRIGSEL_INPUT_TIMER0_CH1: trigger input source TIMER0 CH1
      \arg        TRIGSEL_INPUT_TIMER0_CH2: trigger input source TIMER0 CH2
      \arg        TRIGSEL_INPUT_TIMER0_CH3: trigger input source TIMER0 CH3
      \arg        TRIGSEL_INPUT_TIMER0_MCH0: trigger input source TIMER0 MCH0
      \arg        TRIGSEL_INPUT_TIMER0_MCH1: trigger input source TIMER0 MCH1
      \arg        TRIGSEL_INPUT_TIMER0_MCH2: trigger input source TIMER0 MCH2
      \arg        TRIGSEL_INPUT_TIMER0_MCH3: trigger input source TIMER0 MCH3
      \arg        TRIGSEL_INPUT_TIMER0_BRKIN0: trigger input source TIMER0 BRKIN0
      \arg        TRIGSEL_INPUT_TIMER0_BRKIN1: trigger input source TIMER0 BRKIN1
      \arg        TRIGSEL_INPUT_TIMER0_BRKIN2: trigger input source TIMER0 BRKIN2
      \arg        TRIGSEL_INPUT_TIMER0_ETI: trigger input source TIMER0 ETI
      \arg        TRIGSEL_INPUT_TIMER1_TRGO0: trigger input source TIMER1 TRGO0
      \arg        TRIGSEL_INPUT_TIMER1_CH0: trigger input source TIMER1 CH0
      \arg        TRIGSEL_INPUT_TIMER1_CH1: trigger input source TIMER1 CH1
      \arg        TRIGSEL_INPUT_TIMER1_CH2: trigger input source TIMER1 CH2
      \arg        TRIGSEL_INPUT_TIMER1_CH3: trigger input source TIMER1 CH2
      \arg        TRIGSEL_INPUT_TIMER1_ETI: trigger input source TIMER1 ETI
      \arg        TRIGSEL_INPUT_TIMER2_TRGO0: trigger input source TIMER2 TRGO0
      \arg        TRIGSEL_INPUT_TIMER2_CH0: trigger input source TIMER2 CH0
      \arg        TRIGSEL_INPUT_TIMER2_CH1: trigger input source TIMER2 CH1
      \arg        TRIGSEL_INPUT_TIMER2_CH2: trigger input source TIMER2 CH2
      \arg        TRIGSEL_INPUT_TIMER2_CH3: trigger input source TIMER2 CH3
      \arg        TRIGSEL_INPUT_TIMER2_ETI: trigger input source TIMER2 ETI
      \arg        TRIGSEL_INPUT_TIMER3_TRGO0: trigger input source TIMER3 TRGO0
      \arg        TRIGSEL_INPUT_TIMER3_CH0: trigger input source TIMER3 CH0
      \arg        TRIGSEL_INPUT_TIMER3_CH1: trigger input source TIMER3 CH1
      \arg        TRIGSEL_INPUT_TIMER3_CH2: trigger input source TIMER3 CH2
      \arg        TRIGSEL_INPUT_TIMER3_CH3: trigger input source TIMER3 CH3
      \arg        TRIGSEL_INPUT_TIMER3_ETI: trigger input source TIMER3 ETI
      \arg        TRIGSEL_INPUT_TIMER4_TRGO0: trigger input source TIMER4 TRGO0
      \arg        TRIGSEL_INPUT_TIMER4_CH0: trigger input source TIMER4 CH0
      \arg        TRIGSEL_INPUT_TIMER4_CH1: trigger input source TIMER4 CH1
      \arg        TRIGSEL_INPUT_TIMER4_CH2: trigger input source TIMER4 CH2
      \arg        TRIGSEL_INPUT_TIMER4_CH3: trigger input source TIMER4 CH3
      \arg        TRIGSEL_INPUT_TIMER4_ETI: trigger input source TIMER4 ETI
      \arg        TRIGSEL_INPUT_TIMER5_TRGO0: trigger input source TIMER5 TRGO0
      \arg        TRIGSEL_INPUT_TIMER6_TRGO0: trigger input source TIMER6 TRGO0
      \arg        TRIGSEL_INPUT_TIMER7_TRGO0: trigger input source TIMER7 TRGO0
      \arg        TRIGSEL_INPUT_TIMER7_TRGO1: trigger input source TIMER7 TRGO1
      \arg        TRIGSEL_INPUT_TIMER7_CH0: trigger input source TIMER7 CH0
      \arg        TRIGSEL_INPUT_TIMER7_CH1: trigger input source TIMER7 CH1
      \arg        TRIGSEL_INPUT_TIMER7_CH2: trigger input source TIMER7 CH2
      \arg        TRIGSEL_INPUT_TIMER7_CH3: trigger input source TIMER7 CH3
      \arg        TRIGSEL_INPUT_TIMER7_MCH0: trigger input source TIMER7 MCH0
      \arg        TRIGSEL_INPUT_TIMER7_MCH1: trigger input source TIMER7 MCH1
      \arg        TRIGSEL_INPUT_TIMER7_MCH2: trigger input source TIMER7 MCH2
      \arg        TRIGSEL_INPUT_TIMER7_MCH3: trigger input source TIMER7 MCH3
      \arg        TRIGSEL_INPUT_TIMER7_BRKIN0: trigger input source TIMER7 BRKIN0
      \arg        TRIGSEL_INPUT_TIMER7_BRKIN1: trigger input source TIMER7 BRKIN1
      \arg        TRIGSEL_INPUT_TIMER7_BRKIN2: trigger input source TIMER7 BRKIN2
      \arg        TRIGSEL_INPUT_TIMER7_ETI: trigger input source TIMER7 ETI
      \arg        TRIGSEL_INPUT_TIMER14_TRGO0: trigger input source TIMER14 TRGO0
      \arg        TRIGSEL_INPUT_TIMER14_CH0: trigger input source TIMER14 CH0
      \arg        TRIGSEL_INPUT_TIMER14_CH1: trigger input source TIMER14 CH1
      \arg        TRIGSEL_INPUT_TIMER14_MCH0: trigger input source TIMER14 MCH0
      \arg        TRIGSEL_INPUT_TIMER14_BRKIN: trigger input source TIMER14 BRKIN
      \arg        TRIGSEL_INPUT_TIMER15_CH0: trigger input source TIMER15 CH0
      \arg        TRIGSEL_INPUT_TIMER15_MCH0: trigger input source TIMER15 MCH0
      \arg        TRIGSEL_INPUT_TIMER15_BRKIN: trigger input source TIMER15 BRKIN
      \arg        TRIGSEL_INPUT_TIMER16_CH0: trigger input source TIMER16 CH0
      \arg        TRIGSEL_INPUT_TIMER16_MCH0: trigger input source TIMER16 MCH0
      \arg        TRIGSEL_INPUT_TIMER16_BRKIN: trigger input source TIMER16 BRKIN
      \arg        TRIGSEL_INPUT_TIMER22_TRGO0: trigger input source TIMER22 TRGO0
      \arg        TRIGSEL_INPUT_TIMER22_CH0: trigger input source TIMER22 CH0
      \arg        TRIGSEL_INPUT_TIMER22_CH1: trigger input source TIMER22 CH1
      \arg        TRIGSEL_INPUT_TIMER22_CH2: trigger input source TIMER22 CH2
      \arg        TRIGSEL_INPUT_TIMER22_CH3: trigger input source TIMER22 CH3
      \arg        TRIGSEL_INPUT_TIMER22_ETI: trigger input source TIMER22 ETI
      \arg        TRIGSEL_INPUT_TIMER23_TRGO0: trigger input source TIMER23 TRGO0
      \arg        TRIGSEL_INPUT_TIMER23_CH0: trigger input source TIMER23 CH0
      \arg        TRIGSEL_INPUT_TIMER23_CH1: trigger input source TIMER23 CH1
      \arg        TRIGSEL_INPUT_TIMER23_CH2: trigger input source TIMER23 CH2
      \arg        TRIGSEL_INPUT_TIMER23_CH3: trigger input source TIMER23 CH3
      \arg        TRIGSEL_INPUT_TIMER23_ETI: trigger input source TIMER23 ETI
      \arg        TRIGSEL_INPUT_TIMER30_TRGO0: trigger input source TIMER30 TRGO0
      \arg        TRIGSEL_INPUT_TIMER30_CH0: trigger input source TIMER30 CH0
      \arg        TRIGSEL_INPUT_TIMER30_CH1: trigger input source TIMER30 CH1
      \arg        TRIGSEL_INPUT_TIMER30_CH2: trigger input source TIMER30 CH2
      \arg        TRIGSEL_INPUT_TIMER30_CH3: trigger input source TIMER30 CH3
      \arg        TRIGSEL_INPUT_TIMER30_ETI: trigger input source TIMER30 ETI
      \arg        TRIGSEL_INPUT_TIMER31_TRGO0: trigger input source TIMER31 TRGO0
      \arg        TRIGSEL_INPUT_TIMER31_CH0: trigger input source TIMER31 CH0
      \arg        TRIGSEL_INPUT_TIMER31_CH1: trigger input source TIMER31 CH1
      \arg        TRIGSEL_INPUT_TIMER31_CH2: trigger input source TIMER31 CH2
      \arg        TRIGSEL_INPUT_TIMER31_CH3: trigger input source TIMER31 CH3
      \arg        TRIGSEL_INPUT_TIMER31_ETI: trigger input source TIMER31 ETI
      \arg        TRIGSEL_INPUT_TIMER40_TRGO0: trigger input source TIMER40 TRGO0
      \arg        TRIGSEL_INPUT_TIMER40_CH0: trigger input source TIMER40 CH0
      \arg        TRIGSEL_INPUT_TIMER40_CH1: trigger input source TIMER40 CH1
      \arg        TRIGSEL_INPUT_TIMER40_MCH0: trigger input source TIMER40 MCH0
      \arg        TRIGSEL_INPUT_TIMER40_BRKIN: trigger input source TIMER40 BRKIN
      \arg        TRIGSEL_INPUT_TIMER41_TRGO0: trigger input source TIMER41 TRGO0
      \arg        TRIGSEL_INPUT_TIMER41_CH0: trigger input source TIMER41 CH0
      \arg        TRIGSEL_INPUT_TIMER41_CH1: trigger input source TIMER41 CH1
      \arg        TRIGSEL_INPUT_TIMER41_MCH0: trigger input source TIMER41 MCH0
      \arg        TRIGSEL_INPUT_TIMER41_BRKIN: trigger input source TIMER41 BRKIN
      \arg        TRIGSEL_INPUT_TIMER42_TRGO0: trigger input source TIMER42 TRGO0
      \arg        TRIGSEL_INPUT_TIMER42_CH0: trigger input source TIMER42 CH0
      \arg        TRIGSEL_INPUT_TIMER42_CH1: trigger input source TIMER42 CH1
      \arg        TRIGSEL_INPUT_TIMER42_MCH0: trigger input source TIMER42 MCH0
      \arg        TRIGSEL_INPUT_TIMER42_BRKIN: trigger input source TIMER42 BRKIN
      \arg        TRIGSEL_INPUT_TIMER43_TRGO0: trigger input source TIMER43 TRGO0
      \arg        TRIGSEL_INPUT_TIMER43_CH0: trigger input source TIMER43 CH0
      \arg        TRIGSEL_INPUT_TIMER43_CH1: trigger input source TIMER43 CH1
      \arg        TRIGSEL_INPUT_TIMER43_MCH0: trigger input source TIMER43 MCH0
      \arg        TRIGSEL_INPUT_TIMER43_BRKIN: trigger input source TIMER43 BRKIN
      \arg        TRIGSEL_INPUT_TIMER44_TRGO0: trigger input source TIMER44 TRGO0
      \arg        TRIGSEL_INPUT_TIMER44_CH0: trigger input source TIMER44 CH0
      \arg        TRIGSEL_INPUT_TIMER44_CH1: trigger input source TIMER44 CH1
      \arg        TRIGSEL_INPUT_TIMER44_MCH0: trigger input source TIMER44 MCH0
      \arg        TRIGSEL_INPUT_TIMER44_BRKIN: trigger input source TIMER44 BRKIN
      \arg        TRIGSEL_INPUT_TIMER50_TRGO0: trigger input source TIMER50 TRGO0
      \arg        TRIGSEL_INPUT_TIMER51_TRGO0: trigger input source TIMER51 TRGO0
      \arg        TRIGSEL_INPUT_RTC_ALARM: trigger input source RTC alarm
      \arg        TRIGSEL_INPUT_RTC_TPTS: trigger input source RTC TPTS
      \arg        TRIGSEL_INPUT_ADC0_WD0_OUT: trigger input source ADC0 watchdog0 output
      \arg        TRIGSEL_INPUT_ADC0_WD1_OUT: trigger input source ADC0 watchdog1 output
      \arg        TRIGSEL_INPUT_ADC0_WD2_OUT: trigger input source ADC0 watchdog2 output
      \arg        TRIGSEL_INPUT_ADC1_WD0_OUT: trigger input source ADC1 watchdog0 output
      \arg        TRIGSEL_INPUT_ADC1_WD1_OUT: trigger input source ADC1 watchdog1 output
      \arg        TRIGSEL_INPUT_ADC1_WD2_OUT: trigger input source ADC1 watchdog2 output
      \arg        TRIGSEL_INPUT_ADC2_WD0_OUT: trigger input source ADC2 watchdog0 output
      \arg        TRIGSEL_INPUT_ADC2_WD1_OUT: trigger input source ADC2 watchdog1 output
      \arg        TRIGSEL_INPUT_ADC2_WD2_OUT: trigger input source ADC2 watchdog2 output
      \arg        TRIGSEL_INPUT_CMP0_OUT: trigger input source CMP0_OUT
      \arg        TRIGSEL_INPUT_CMP1_OUT: trigger input source CMP1_OUT
      \arg        TRIGSEL_INPUT_SAI0_AFS_OUT: trigger input source SAI0_AFS_OUT
      \arg        TRIGSEL_INPUT_SAI0_BFS_OUT: trigger input source SAI0_BFS_OUT
      \arg        TRIGSEL_INPUT_SAI2_AFS_OUT: trigger input source SAI2_AFS_OUT
      \arg        TRIGSEL_INPUT_SAI2_BFS_OUT: trigger input source SAI2_BFS_OUT
    \param[out] none
    \retval     none
*/
void trigsel_init(trigsel_periph_enum target_periph, trigsel_source_enum trigger_source)
{
    /* if register write is enabled, set trigger source to target peripheral */
    if (RESET == trigsel_register_lock_get(target_periph))
    {
        TRIGSEL_TARGET_REG(target_periph) &= ~TRIGSEL_TARGET_PERIPH_MASK(target_periph);
        TRIGSEL_TARGET_REG(target_periph) |= ((uint32_t)trigger_source << TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)) & TRIGSEL_TARGET_PERIPH_MASK(target_periph);
    }
}

/*!
    \brief      get the trigger input signal for target peripheral
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_ADC0_REGTRG: output target peripheral ADC0_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC1_REGTRG: output target peripheral ADC1_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC2_REGTRG: output target peripheral ADC2_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg        TRIGSEL_OUTPUT_DAC_OUT0_EXTRG: output target peripheral DAC_OUT0_EXTRG
      \arg        TRIGSEL_OUTPUT_DAC_OUT1_EXTRG: output target peripheral DAC_OUT1_EXTRG
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER14_BRKIN0: output target peripheral TIMER14_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER15_BRKIN0: output target peripheral TIMER15_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER16_BRKIN0: output target peripheral TIMER16_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER40_BRKIN0: output target peripheral TIMER40_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER41_BRKIN0: output target peripheral TIMER41_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER42_BRKIN0: output target peripheral TIMER42_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER43_BRKIN0: output target peripheral TIMER43_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER44_BRKIN0: output target peripheral TIMER44_BRKIN0
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_LPDTS_TRG: output target peripheral LPDTS_TRG
      \arg        TRIGSEL_OUTPUT_TIMER0_ETI: output target peripheral TIMER0_ETI
      \arg        TRIGSEL_OUTPUT_TIMER1_ETI: output target peripheral TIMER1_ETI
      \arg        TRIGSEL_OUTPUT_TIMER2_ETI: output target peripheral TIMER2_ETI
      \arg        TRIGSEL_OUTPUT_TIMER3_ETI: output target peripheral TIMER3_ETI
      \arg        TRIGSEL_OUTPUT_TIMER4_ETI: output target peripheral TIMER4_ETI
      \arg        TRIGSEL_OUTPUT_TIMER7_ETI: output target peripheral TIMER7_ETI
      \arg        TRIGSEL_OUTPUT_TIMER22_ETI: output target peripheral TIMER22_ETI
      \arg        TRIGSEL_OUTPUT_TIMER23_ETI: output target peripheral TIMER23_ETI
      \arg        TRIGSEL_OUTPUT_TIMER30_ETI: output target peripheral TIMER30_ETI
      \arg        TRIGSEL_OUTPUT_TIMER31_ETI: output target peripheral TIMER31_ETI
      \arg        TRIGSEL_OUTPUT_EDOUT_TRG: output target peripheral EDOUT_TRG
      \arg        TRIGSEL_OUTPUT_HPDF_ITRG: output target peripheral HPDF_ITR
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI14: output target peripheral TIMER0_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI14: output target peripheral TIMER1_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI14: output target peripheral TIMER2_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER3_ITI14: output target peripheral TIMER3_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER4_ITI14: output target peripheral TIMER4_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI14: output target peripheral TIMER7_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER14_ITI14: output target peripheral TIMER14_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER22_ITI14: output target peripheral TIMER22_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER23_ITI14: output target peripheral TIMER23_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER30_ITI14: output target peripheral TIMER30_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER31_ITI14: output target peripheral TIMER31_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER40_ITI14: output target peripheral TIMER40_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER41_ITI14: output target peripheral TIMER41_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER42_ITI14: output target peripheral TIMER42_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER43_ITI14: output target peripheral TIMER43_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER44_ITI14: output target peripheral TIMER44_ITI14
    \param[out] none
    \retval  trigger_source: trigger source value(0~177)
*/
trigsel_source_enum trigsel_trigger_source_get(trigsel_periph_enum target_periph)
{
    trigsel_source_enum trigger_source;

    trigger_source = (trigsel_source_enum)((TRIGSEL_TARGET_REG(target_periph) & TRIGSEL_TARGET_PERIPH_MASK(target_periph)) >> TRIGSEL_TARGET_PERIPH_SHIFT(target_periph));

    return trigger_source;
}

/*!
    \brief      lock the trigger register
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_ADC0_REGTRG: output target peripheral ADC0_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC1_REGTRG: output target peripheral ADC1_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC2_REGTRG: output target peripheral ADC2_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg        TRIGSEL_OUTPUT_DAC_OUT0_EXTRG: output target peripheral DAC_OUT0_EXTRG
      \arg        TRIGSEL_OUTPUT_DAC_OUT1_EXTRG: output target peripheral DAC_OUT1_EXTRG
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER14_BRKIN0: output target peripheral TIMER14_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER15_BRKIN0: output target peripheral TIMER15_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER16_BRKIN0: output target peripheral TIMER16_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER40_BRKIN0: output target peripheral TIMER40_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER41_BRKIN0: output target peripheral TIMER41_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER42_BRKIN0: output target peripheral TIMER42_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER43_BRKIN0: output target peripheral TIMER43_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER44_BRKIN0: output target peripheral TIMER44_BRKIN0
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_LPDTS_TRG: output target peripheral LPDTS_TRG
      \arg        TRIGSEL_OUTPUT_TIMER0_ETI: output target peripheral TIMER0_ETI
      \arg        TRIGSEL_OUTPUT_TIMER1_ETI: output target peripheral TIMER1_ETI
      \arg        TRIGSEL_OUTPUT_TIMER2_ETI: output target peripheral TIMER2_ETI
      \arg        TRIGSEL_OUTPUT_TIMER3_ETI: output target peripheral TIMER3_ETI
      \arg        TRIGSEL_OUTPUT_TIMER4_ETI: output target peripheral TIMER4_ETI
      \arg        TRIGSEL_OUTPUT_TIMER7_ETI: output target peripheral TIMER7_ETI
      \arg        TRIGSEL_OUTPUT_TIMER22_ETI: output target peripheral TIMER22_ETI
      \arg        TRIGSEL_OUTPUT_TIMER23_ETI: output target peripheral TIMER23_ETI
      \arg        TRIGSEL_OUTPUT_TIMER30_ETI: output target peripheral TIMER30_ETI
      \arg        TRIGSEL_OUTPUT_TIMER31_ETI: output target peripheral TIMER31_ETI
      \arg        TRIGSEL_OUTPUT_EDOUT_TRG: output target peripheral EDOUT_TRG
      \arg        TRIGSEL_OUTPUT_HPDF_ITRG: output target peripheral HPDF_ITR
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI14: output target peripheral TIMER0_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI14: output target peripheral TIMER1_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI14: output target peripheral TIMER2_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER3_ITI14: output target peripheral TIMER3_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER4_ITI14: output target peripheral TIMER4_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI14: output target peripheral TIMER7_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER14_ITI14: output target peripheral TIMER14_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER22_ITI14: output target peripheral TIMER22_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER23_ITI14: output target peripheral TIMER23_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER30_ITI14: output target peripheral TIMER30_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER31_ITI14: output target peripheral TIMER31_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER40_ITI14: output target peripheral TIMER40_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER41_ITI14: output target peripheral TIMER41_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER42_ITI14: output target peripheral TIMER42_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER43_ITI14: output target peripheral TIMER43_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER44_ITI14: output target peripheral TIMER44_ITI14
    \param[out] none
    \retval     none
*/
void trigsel_register_lock_set(trigsel_periph_enum target_periph)
{
    /*!< lock target peripheral register */
    TRIGSEL_TARGET_REG(target_periph) |= TRIGSEL_TARGET_LK;
}

/*!
    \brief      get the trigger register lock status
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_ADC0_REGTRG: output target peripheral ADC0_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC0_INSTRG: output target peripheral ADC0_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC1_REGTRG: output target peripheral ADC1_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC1_INSTRG: output target peripheral ADC1_INSTRG
      \arg        TRIGSEL_OUTPUT_ADC2_REGTRG: output target peripheral ADC2_REGTRG
      \arg        TRIGSEL_OUTPUT_ADC2_INSTRG: output target peripheral ADC2_INSTRG
      \arg        TRIGSEL_OUTPUT_DAC_OUT0_EXTRG: output target peripheral DAC_OUT0_EXTRG
      \arg        TRIGSEL_OUTPUT_DAC_OUT1_EXTRG: output target peripheral DAC_OUT1_EXTRG
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER14_BRKIN0: output target peripheral TIMER14_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER15_BRKIN0: output target peripheral TIMER15_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER16_BRKIN0: output target peripheral TIMER16_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER40_BRKIN0: output target peripheral TIMER40_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER41_BRKIN0: output target peripheral TIMER41_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER42_BRKIN0: output target peripheral TIMER42_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER43_BRKIN0: output target peripheral TIMER43_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER44_BRKIN0: output target peripheral TIMER44_BRKIN0
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_LPDTS_TRG: output target peripheral LPDTS_TRG
      \arg        TRIGSEL_OUTPUT_TIMER0_ETI: output target peripheral TIMER0_ETI
      \arg        TRIGSEL_OUTPUT_TIMER1_ETI: output target peripheral TIMER1_ETI
      \arg        TRIGSEL_OUTPUT_TIMER2_ETI: output target peripheral TIMER2_ETI
      \arg        TRIGSEL_OUTPUT_TIMER3_ETI: output target peripheral TIMER3_ETI
      \arg        TRIGSEL_OUTPUT_TIMER4_ETI: output target peripheral TIMER4_ETI
      \arg        TRIGSEL_OUTPUT_TIMER7_ETI: output target peripheral TIMER7_ETI
      \arg        TRIGSEL_OUTPUT_TIMER22_ETI: output target peripheral TIMER22_ETI
      \arg        TRIGSEL_OUTPUT_TIMER23_ETI: output target peripheral TIMER23_ETI
      \arg        TRIGSEL_OUTPUT_TIMER30_ETI: output target peripheral TIMER30_ETI
      \arg        TRIGSEL_OUTPUT_TIMER31_ETI: output target peripheral TIMER31_ETI
      \arg        TRIGSEL_OUTPUT_EDOUT_TRG: output target peripheral EDOUT_TRG
      \arg        TRIGSEL_OUTPUT_HPDF_ITRG: output target peripheral HPDF_ITR
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI14: output target peripheral TIMER0_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI14: output target peripheral TIMER1_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI14: output target peripheral TIMER2_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER3_ITI14: output target peripheral TIMER3_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER4_ITI14: output target peripheral TIMER4_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI14: output target peripheral TIMER7_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER14_ITI14: output target peripheral TIMER14_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER22_ITI14: output target peripheral TIMER22_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER23_ITI14: output target peripheral TIMER23_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER30_ITI14: output target peripheral TIMER30_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER31_ITI14: output target peripheral TIMER31_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER40_ITI14: output target peripheral TIMER40_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER41_ITI14: output target peripheral TIMER41_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER42_ITI14: output target peripheral TIMER42_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER43_ITI14: output target peripheral TIMER43_ITI14
      \arg        TRIGSEL_OUTPUT_TIMER44_ITI14: output target peripheral TIMER44_ITI14
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus trigsel_register_lock_get(trigsel_periph_enum target_periph)
{
    if(RESET != (TRIGSEL_TARGET_REG(target_periph) & TRIGSEL_TARGET_LK))
    {
        return SET;
    }else{
        return RESET;
    }
}
