/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PWM_IFC__
#define __PWM_IFC__

#include "sdk.h"

//! @addtogroup diag_pwm
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Available PWM interrupts.
enum _pwm_interrupts {
    kPwmFifoEmptyIrq = 1 << 0,  //!< FIFO empty interrupt.
    kPwmRolloverIrq = 1 << 1,   //!< Rollover interrupt. The counter has reached the period and reset.
    kPwmCompareIrq = 1 << 2     //!< Compare interrupt. The counter value matches the current sample value
};

//! @brief Clock sources for the PWM.
enum _pwm_clksrc {
    kPwmClockSourceNone = 0,
    kPwmClockSourceIpg = 1,
    kPwmClockSourceCkih = 2,
    kPwmClockSourceCkil = 3
};

struct pwm_parms {
    uint32_t clock;              //!< Input clock frequency.
    uint32_t smp_cnt;
    uint16_t prescale;
    uint16_t period;
    uint16_t *sample;
    uint8_t interrupt;
    uint8_t active_pol;
    uint8_t repeat;
};

struct pwm_interrupt_status {
    uint32_t instance;          //!< The number of this module instance. The first instance is number 1.
    uint8_t interrupt;           //!< PWM interrupt.
};

extern uint32_t g_pwm_test_end;
////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize PWM module.
 *
 * Sets up samples and pulse width.
 * - Pulse Width = (prescale * period) / Fsrc (second)
 * - Duty Cycle = sample[idx] / period
 *
 * @param instance the PWM instance number.
 * @param pwm pointer to the pwm setting parameters structure.
 *
 * @retval TRUE on success
 * @retval FALSE on fail
 */
int pwm_init(uint32_t instance, struct pwm_parms *pwm);

/*!
 * @brief Setup interrupt service routine.
 *
 * The @a mask parameter should be composed of one or more of the below:
 *    - #kPwmFifoEmptyIrq
 *    - #kPwmRolloverIrq
 *    - #kPwmCompareIrq
 *
 * @param instance the PWM instance number.
 * @param irq_subroutine the PWM interrupt interrupt routine.
 * @param mask mask of PWM interrupt bits to enable.
 */
void pwm_setup_interrupt(uint32_t instance, void (*irq_subroutine) (void), uint8_t mask);

/*!
 * @brief Free interrupt service.
 *
 * @param instance the PWM instance number.
 */
void pwm_free_interrupt(uint32_t instance);

/*!
 * @brief Clear status that will issue interrupt.
 *
 * The @a mask parameter should be composed of one or more of the below:
 *    - #kPwmFifoEmptyIrq
 *    - #kPwmRolloverIrq
 *    - #kPwmCompareIrq
 *
 * @param instance the PWM instance number.
 * @param mask mask of PWM interrupt status bits to clear.
 */
void pwm_clear_int_status(uint32_t instance, uint32_t mask);

/*!
 * @brief PWM interrupt routine of FIFO empty.
 *
 * FIFO empty interrupt will set the global variable test_end as TRUE,
 * which serves as a flag of ending PWM test.
 */
void pwm_isr_test_end(void);

/*!
 * @brief Enable PWM output.
 *
 * The PWM counter starts counting and the waveform is produced on the output
 * pin. Interrupts will be triggered upon fifo empty, compare and rollover.
 *
 * @param instance the PWM instance number.
 */
void pwm_enable(uint32_t instance);

/*!
 * @brief Disable PWM ouput.
 *
 * Stops the PWM counter.
 *
 * @param instance the PWM instance number.
 */
void pwm_disable(uint32_t instance);

/*!
 * @brief Get current frequency of corresponding PWM clock source.
 *
 * @param clock PWM clock souce. The @a clock parameter should be composed of one of the below:
 *    - #kPwmClockSourceIpg
 *    - #kPwmClockSourceCkih
 *    - #kPwmClockSourceCkil
 */
int pwm_get_clock_freq(uint32_t clock);

#if defined(__cplusplus)
}
#endif
//! @}
#endif
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
