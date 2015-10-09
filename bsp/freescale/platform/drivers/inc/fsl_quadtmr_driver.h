/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
#ifndef __FSL_QUADTMR_DRIVER_H__
#define __FSL_QUADTMR_DRIVER_H__

#include "fsl_quadtmr_hal.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_TMR_COUNT

/*!
 * @addtogroup quadtmr_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Table of base addresses for Quad Timer instances. */
extern TMR_Type * const g_quadtmrBase[TMR_INSTANCE_COUNT];

/*! @brief Table to save Quad Timer IRQ enumeration numbers defined in the CMSIS header file. */
extern const IRQn_Type g_quadtmrIrqId[TMR_INSTANCE_COUNT];

/*! @brief Quad timer IP bus clock options to run the counter */
typedef enum _quadtmr_ip_bus_clock_source
{
    kQuadTmrIpBusClkDiv1 = 0, /*!< IP Bus clock Div 1 */
    kQuadTmrIpBusClkDiv2,     /*!< IP Bus clock Div 2 */
    kQuadTmrIpBusClkDiv4,     /*!< IP Bus clock Div 4 */
    kQuadTmrIpBusClkDiv8,     /*!< IP Bus clock Div 8 */
    kQuadTmrIpBusClkDiv16,    /*!< IP Bus clock Div 16 */
    kQuadTmrIpBusClkDiv32,    /*!< IP Bus clock Div 32 */
    kQuadTmrIpBusClkDiv64,    /*!< IP Bus clock Div 64 */
    kQuadTmrIpBusClkDiv128    /*!< IP Bus clock Div 128 */
}quadtmr_ip_bus_clock_source_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the Quad Timer driver.
 *
 * Initializes the Quad Timer registers, ungates the module clock, and enables Quad Timer
 * interrupt in the system interrupt controller.
 *
 * @param instance The Quad Timer peripheral instance number.
 * @return kStatusQuadTmrSuccess means success; Otherwise means failed.
 */
quadtmr_status_t QUADTMR_DRV_Init(uint32_t instance);

/*!
 * @brief Shuts down the Quad Timer driver.
 *
 * Gates the module clock and disables the interrupt in the system interrupt controller.
 *
 * @param instance The Quad Timer peripheral instance number.
 */
void QUADTMR_DRV_Deinit(uint32_t instance);

/*!
 * @brief Provides a 64-bit counter.
 *
 * The user can choose which source clock is used by the counter.
 * The user must ensure that the QUADTMR_DRV_Init() function is called on all timer instances because
 * all timer instances are used in this mode. Timer 0 is clocked via the source clock and Timers 1, 2, and 3
 * are set up in the cascade mode. All 4 counters  count up to 0xFFFF, then roll-over and continue
 * counting.
 *
 * @param clk Source clock that feeds timer 0 counter.
 */
void QUADTMR_DRV_Start64BitCounter(quadtmr_pri_count_source_t clk);

/*!
 * @brief Gets the current count value when running in 64-bit mode.
 *
 * The function reads all 4 timer values and returns the value.
 *
 * @return The current value of all 4 counters is concatenated to a 64-bit value.
 */
uint64_t QUADTMR_DRV_Get64BitCountVal(void);

/*!
 * @brief Provides the PWM signal.
 *
 * The user provides the input clock source which is derived from the IP Bus clock. The user also
 * provides the desired PWM signal's period in microseconds and the pulse width in microseconds.
 * This function enables the pre-load function for each compare register to allow updating
 * the PWM signal characteristics at a later time.
 *
 * @param instance The Quad timer peripheral instance number.
 * @param clockSrc Counter source clock, options available in quadtmr_ip_bus_clock_source_t enumeration
 * @param pwmPulsePeriod PWM period specified in microseconds
 * @param pulseWidthPeriod PWM pulse width specified in microseconds
 */
void QUADTMR_DRV_SetupFlexPwm(uint32_t instance, quadtmr_ip_bus_clock_source_t clockSrc,
                                          uint32_t pwmPulsePeriod, uint32_t pulseWidthPeriod);

/*!
 * @brief Provides a way to update the current PWM signal.
 *
 * Prior to calling this function, call the QUADTMR_DRV_SetupFlexPwm() function to start outputting a
 * PWM signal. Call this function to update the PWM's period and/or pulse width.
 * The PWM continues to be derived from the clock source provided during setup.
 *
 * @param instance  The Quad timer peripheral instance number.
 * @param pwmPulsePeriod Updated PWM period specified in microseconds
 * @param pulseWidthPeriod Updated PWM pulse width specified in microseconds

 */
void QUADTMR_DRV_UpdatePwm(uint32_t instance, uint32_t pwmPulsePeriod, uint32_t pulseWidthPeriod);

/*!
 * @brief Action to take when a Quad Timer interrupt is triggered.
 *
 * The timer comparison flags are checked and cleared if set.
 *
 * @param instance   The Quad Timer peripheral instance number.
 */
void QUADTMR_DRV_IRQHandler(uint32_t instance);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_TMR_COUNT */

#endif /* __FSL_QUADTMR_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

