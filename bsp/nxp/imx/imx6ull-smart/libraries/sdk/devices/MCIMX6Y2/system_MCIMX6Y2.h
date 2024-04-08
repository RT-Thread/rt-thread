/*
** ###################################################################
**     Processors:          MCIMX6Y2CVM05
**                          MCIMX6Y2CVM08
**                          MCIMX6Y2DVM05
**                          MCIMX6Y2DVM09
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    IMX6ULLRM, Rev. 1, Feb. 2017
**     Version:             rev. 3.0, 2017-02-28
**     Build:               b170410
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2015-12-18)
**         Initial version.
**     - rev. 2.0 (2016-08-02)
**         Rev.B Header GA
**     - rev. 3.0 (2017-02-28)
**         Rev.1 Header GA
**
** ###################################################################
*/

/*!
 * @file MCIMX6Y2
 * @version 3.0
 * @date 2017-02-28
 * @brief Device specific configuration file for MCIMX6Y2 (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef _SYSTEM_MCIMX6Y2_H_
#define _SYSTEM_MCIMX6Y2_H_                      /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DEFAULT_SYSTEM_CLOCK           528000000u            /* Default System clock value */

typedef void (*system_irq_handler_t) (uint32_t giccIar, void *param);
/**
 * @brief IRQ handle for specific IRQ
 */
typedef struct _sys_irq_handle
{
    system_irq_handler_t irqHandler; /**< IRQ handler for specific IRQ */
    void *userParam;                 /**< User param for handler callback */
} sys_irq_handle_t;

/**
 * @brief System clock frequency (core clock)
 *
 * The system clock frequency supplied to the SysTick timer and the processor
 * core clock. This variable can be used by the user application to setup the
 * SysTick timer or configure other parameters. It may also be used by debugger to
 * query the frequency of the debug timer or configure the trace clock speed
 * SystemCoreClock is initialized with a correct predefined value.
 */
extern uint32_t SystemCoreClock;

/**
 * @brief Setup the microcontroller system.
 *
 * Typically this function configures the oscillator (PLL) that is part of the
 * microcontroller device. For systems with variable clock speed it also updates
 * the variable SystemCoreClock. SystemInit is called from startup_device file.
 */
void SystemInit (void);

/**
 * @brief Updates the SystemCoreClock variable.
 *
 * It must be called whenever the core clock is changed during program
 * execution. SystemCoreClockUpdate() evaluates the clock register settings and calculates
 * the current core clock.
 */
void SystemCoreClockUpdate (void);

/**
 * @brief Initialize IRQ table, set default handlers
 */
void SystemInitIrqTable (void);

/**
 * @brief Install IRQ handler for specific IRQ
 *
 * It can't be called at interrupt context to avoid IRQ table corrupt during interrupt preemption
 *
 * @param irq IRQ number corresponds to the installed handler
 * @param handler IRQ handler for the IRQ number
 * @param userParam User specified parameter for IRQ handler callback
 */
void SystemInstallIrqHandler (IRQn_Type irq, system_irq_handler_t handler, void *userParam);

/**
 * @brief System IRQ handler which dispatches specific IRQ to corresponding registered handler.
 *
 * It is called from IRQ exception context and dispatches to registered handler according to
 * GICC_IAR interrupt number.
 * The default implementation is weak and user can override this function with his own SystemIrqHandler.
 *
 * @param giccIar IRQ acknowledge value read from GICC_IAR
 */
void SystemIrqHandler (uint32_t giccIar);

/**
 * @brief Get IRQ nesting level of current context.
 *
 * If the return value is 0, then the context is not ISR, otherwise the context is ISR.
 *
 * @return IRQ nesting level
 */
uint32_t SystemGetIRQNestingLevel (void);

/**
 * @brief Setup systick for RTOS system.
 *
 * @param tickRateHz Tick number per second
 * @param tickHandler IRQ callback handler for tick
 * @param intPriority IRQ interrupt priority (the smaller, the higher priority)
 */
void SystemSetupSystick (uint32_t tickRateHz, void *tickHandler, uint32_t intPriority);

/**
 * @brief Clear systick flag status so that next tick interrupt may occur.
 */
void SystemClearSystickFlag (void);
#ifdef __cplusplus
}
#endif

#endif  /* _SYSTEM_MCIMX6Y2_H_ */
