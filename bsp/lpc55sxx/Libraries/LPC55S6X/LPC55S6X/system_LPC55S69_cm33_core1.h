/*
** ###################################################################
**     Processors:          LPC55S69JBD100_cm33_core1
**                          LPC55S69JBD64_cm33_core1
**                          LPC55S69JEV98_cm33_core1
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC55S6x/LPC55S2x/LPC552x User manual(UM11126) Rev.1.3  16 May 2019
**     Version:             rev. 1.1, 2019-05-16
**     Build:               b220117
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2022 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-08-22)
**         Initial version based on v0.2UM
**     - rev. 1.1 (2019-05-16)
**         Initial A1 version based on v1.3UM
**
** ###################################################################
*/

/*!
 * @file LPC55S69_cm33_core1
 * @version 1.1
 * @date 2019-05-16
 * @brief Device specific configuration file for LPC55S69_cm33_core1 (header
 *        file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef _SYSTEM_LPC55S69_cm33_core1_H_
#define _SYSTEM_LPC55S69_cm33_core1_H_           /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DEFAULT_SYSTEM_CLOCK           12000000u           /* Default System clock value */
#define CLK_RTC_32K_CLK                   32768u           /* RTC oscillator 32 kHz output (32k_clk */
#define CLK_FRO_12MHZ                  12000000u           /* FRO 12 MHz (fro_12m) */
#define CLK_FRO_48MHZ                  48000000u           /* FRO 48 MHz (fro_48m) */
#define CLK_FRO_96MHZ                  96000000u           /* FRO 96 MHz (fro_96m) */
#define CLK_CLK_IN                     16000000u           /* Default CLK_IN pin clock */


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
 * @brief SystemInit function hook.
 *
 * This weak function allows to call specific initialization code during the
 * SystemInit() execution.This can be used when an application specific code needs
 * to be called as close to the reset entry as possible (for example the Multicore
 * Manager MCMGR_EarlyInit() function call).
 * NOTE: No global r/w variables can be used in this hook function because the
 * initialization of these variables happens after this function.
 */
void SystemInitHook (void);

#ifdef __cplusplus
}
#endif

#endif  /* _SYSTEM_LPC55S69_cm33_core1_H_ */
