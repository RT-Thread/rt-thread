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

//! @addtogroup diag_gpt
//! @{

/*!
 * @file gpt.h
 * @brief GPT driver public interface.
 */

#ifndef __GPT_H__
#define __GPT_H__

#include "imx_timer.h"
#include "sdk.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Possible events for the GPT.
//!
//! These constants are intended to be combined together to form a bitmask. Several
//! of the GPT driver APIs use such a bitmask. For instance, gpt_counter_enable()
//! accepts a bitmask that selects the events for which interrupts should be enabled.
//!
//! Note that the values of these enums happen to be the bitmasks for the respective
//! fields in the HW_GPT_SR and HW_GPT_IR registers, so a mask constructed from them
//! can be used directly with register values.
enum _gpt_events
{
    kGPTNoEvent = 0,               //!< No events enabled.
    kGPTRollover = 1 << 5,         //!< Rollover event.
    kGPTInputCapture1 = 1 << 3,    //!< Input capture 1 event.
    kGPTInputCapture2 = 1 << 4,    //!< Input capture 2 event.
    kGPTOutputCompare1 = 1 << 0,   //!< Output compare 1 event.
    kGPTOutputCompare2 = 1 << 1,   //!< Output compare 2 event.
    kGPTOutputCompare3 = 1 << 2,   //!< Output compare 3 event.
    
    //! Combined mask of all GPT events.
    kGPTAllEvents = kGPTRollover | kGPTInputCapture1 | kGPTInputCapture2
                    | kGPTOutputCompare1 | kGPTOutputCompare2 | kGPTOutputCompare3
};

//! @brief GPT counter modes.
enum _gpt_counter_mode
{
    RESTART_MODE = 0,
    FREE_RUN_MODE = 1
};

//! @brief Supported input capture modes.
enum _gpt_capture_modes
{
    INPUT_CAP_DISABLE = 0,      //!< input capture event disabled
    INPUT_CAP_RISING_EDGE = 1,  //!< input capture event on a rising edge
    INPUT_CAP_FALLING_EDGE = 2, //!< input capture event on a falling edge
    INPUT_CAP_BOTH_EDGE = 3     //!< input capture event on a both edge
};

//! @brief Supported output modes.
enum _gpt_compare_modes
{
    OUTPUT_CMP_DISABLE = 0,     //!< output disconnected from pad
    OUTPUT_CMP_TOGGLE = 1,      //!< output toggle mode
    OUTPUT_CMP_CLEAR = 2,       //!< output set low mode
    OUTPUT_CMP_SET = 3,         //!< output set high mode
    OUTPUT_CMP_LOWPULSE = 4     //!< output set high mode
};

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the GPT timer.
 *
 * @param   clock_src Source clock of the counter: CLKSRC_OFF, CLKSRC_IPG_CLK,
 *                      CLKSRC_PER_CLK, CLKSRC_CKIL, CLKSRC_CLKIN.
 * @param   prescaler Prescaler of the source clock from 1 to 4096.
 * @param   counter_mode Counter mode: FREE_RUN_MODE or RESTART_MODE.
 * @param   low_power_mode Low power during which the timer is enabled:
 *                           WAIT_MODE_EN and/or STOP_MODE_EN.
 */
void gpt_init(uint32_t clock_src, uint32_t prescaler, uint32_t counter_mode, uint32_t low_power_mode);

/*!
 * @brief Setup GPT interrupt.
 *
 * It enables or disables the related HW module interrupt, and attached the
 * related sub-routine into the vector table.
 *
 * @param   irq_subroutine the GPT interrupt interrupt routine.
 * @param   enableIt Pass true to enable the interrupt.
 */
void gpt_setup_interrupt(void (*irq_subroutine)(void), bool enableIt);

/*!
 * @brief Enable the GPT module.
 *
 * Used typically when the gpt_init is done, and other interrupt related settings are ready.
 *
 * If a value of #kGPTNoEvent is passed for @a irq_mode, then no interrupts will be enabled.
 * This effectively puts the timer into polling mode, where you must call gpt_get_x_event()
 * to check for an event having occurred.
 *
 * @param   irq_mode Mask of events to enable interrupts for, such as #kGPTRollover or
 *      #kGPTOutputCompare1. See the #_gpt_events enum for the complete list. Pass
 *      #kGPTNoEvent to prevent any interrupts from being enabled, which effectively puts
 *      the timer into polling mode.
 */
void gpt_counter_enable(uint32_t irq_mode);

/*!
 * @brief Disable the counter.
 *
 * It saves power when not used.
 *
 */
void gpt_counter_disable(void);

/*!
 * @brief Get rollover event flag and clear it if set.
 *
 * This function can typically be used for polling method, but
 * is also used to clear the status compare flag in IRQ mode.
 *
 * @return  Either 0 of kGPTRollover.
 */
uint32_t gpt_get_rollover_event(void);

/*!
 * @brief Get a captured value when an event occured, and clear the flag if set.
 *
 * Use this function to check for an input capture event having occurred, either in
 * the event ISR or to check manually in polling mode. Pass the input channel to check
 * in the @a flag parameter. If that channel fired, its captured timer value will be
 * read and placed in @a capture_val (if not NULL). The event that fired will be cleared
 * and its event mask returned as the return value from the function. If no event
 * occurred, the function returns 0.
 *
 * @param   flag Which channel to check, either #kGPTInputCapture1 or #kGPTInputCapture2.
 *      Only one channel may be specified.
 * @param   capture_val The capture register value is returned through this parameter if
 *      the specified event occurred. May be NULL if not required.
 * @return  Mask of input specified capture event that occurred, or 0 if no event occurred.
 */
uint32_t gpt_get_capture_event(uint8_t flag, uint32_t * capture_val);

/*!
 * @brief Set the input capture mode.
 *
 * @param   cap_input The input capture channel to configure, either #kGPTInputCapture1
 *      or #kGPTInputCapture2.
 * @param   cap_input_mode Capture input mode: #INPUT_CAP_DISABLE, #INPUT_CAP_BOTH_EDGE,
 *                            #INPUT_CAP_FALLING_EDGE, #INPUT_CAP_RISING_EDGE.
 */
void gpt_set_capture_event(uint8_t cap_input, uint8_t cap_input_mode);

/*!
 * @brief Get a compare event flag and clear it if set.
 *
 * This function can typically be used for polling method, but
 * is also used to clear the status compare flag in IRQ mode.
 *
 * @param   flag Checked compare event flag such GPTSR_OF1, GPTSR_OF2, GPTSR_OF3.
 * @return  The value of the compare event flag.
 */
uint32_t gpt_get_compare_event(uint8_t flag);

/*!
 * @brief Set a compare event by programming the compare register and 
 * compare output mode.
 *
 * @param   cmp_output The channel to configure. Must be one of #kGPTOutputCompare1,
 *      #kGPTOutputCompare2, or #kGPTOutputCompare3.
 * @param   cmp_output_mode Compare output mode: #OUTPUT_CMP_DISABLE, #OUTPUT_CMP_TOGGLE,
 *                            #OUTPUT_CMP_CLEAR, #OUTPUT_CMP_SET, #OUTPUT_CMP_LOWPULSE.
 * @param   cmp_value Compare value for the compare register.
 */
void gpt_set_compare_event(uint8_t cmp_output, uint8_t cmp_output_mode, uint32_t cmp_value);

#if defined(__cplusplus)
}
#endif

//! @}

#endif //__GPT_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
