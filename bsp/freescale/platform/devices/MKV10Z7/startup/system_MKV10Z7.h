/*
** ###################################################################
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          GNU C Compiler - CodeSourcery Sourcery G++
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    KV10P48M75RM Rev.6, June 2014
**     Version:             rev. 1.2, 2014-08-28
**     Build:               b141218
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright (c) 2014 Freescale Semiconductor, Inc.
**     All rights reserved.
**
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
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2013-05-09)
**         Initial version.
**     - rev. 1.1 (2014-02-20)
**         ADC module - removed PGA registers
**         UART0 module - removed CEA709.1 registers
**     - rev. 1.2 (2014-08-28)
**         Update of system files - default clock configuration changed.
**         Update of startup files - possibility to override DefaultISR added.
**
** ###################################################################
*/

/*!
 * @file MKV10Z7
 * @version 1.2
 * @date 2014-08-28
 * @brief Device specific configuration file for MKV10Z7 (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef SYSTEM_MKV10Z7_H_
#define SYSTEM_MKV10Z7_H_                        /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#ifndef DISABLE_WDOG
  #define DISABLE_WDOG                 1
#endif

/* MCG mode constants */

#define MCG_MODE_FEI                   0U
#define MCG_MODE_FBI                   1U
#define MCG_MODE_BLPI                  2U
#define MCG_MODE_FEE                   3U
#define MCG_MODE_FBE                   4U
#define MCG_MODE_BLPE                  5U

/* Predefined clock setups
   0 ... Default part configuration
         Multipurpose Clock Generator (MCG) in FEI mode.
         Reference clock source for MCG module: Slow internal reference clock
         Core clock = 20.97152MHz
         Bus clock  = 20.97152MHz
   1 ... Maximum achievable clock frequency configuration
         Multipurpose Clock Generator (MCG) in FEE mode.
         Reference clock source for MCG module: System oscillator reference clock
         Core clock = 75MHz
         Bus clock  = 25MHz
   2 ... Chip internally clocked, ready for Very Low Power Run mode
         Multipurpose Clock Generator (MCG) in BLPI mode.
         Reference clock source for MCG module: Fast internal reference clock
         Core clock = 4MHz
         Bus clock  = 0.8MHz
   3 ... Chip externally clocked, ready for Very Low Power Run mode
         Multipurpose Clock Generator (MCG) in BLPE mode.
         Reference clock source for MCG module: System oscillator reference clock
         Core clock = 3.333333333333MHz
         Bus clock  = 0.833333333333MHz
*/

/* Define clock source values */

#define CPU_XTAL_CLK_HZ                10000000u           /* Value of the external crystal or oscillator clock frequency in Hz */
#define CPU_INT_SLOW_CLK_HZ            32768u              /* Value of the slow internal oscillator clock frequency in Hz  */
#define CPU_INT_FAST_CLK_HZ            4000000u            /* Value of the fast internal oscillator clock frequency in Hz  */
#define CPU_INT_IRC_CLK_HZ             48000000u           /* Value of the 48M internal oscillator clock frequency in Hz  */

/* Low power mode enable */

/* SMC_PMPROT: ?=0,?=0,AVLP=1,?=0,?=0,?=0,AVLLS=1,?=0 */
#define SYSTEM_SMC_PMPROT_VALUE        (SMC_PMPROT_AVLP_MASK | SMC_PMPROT_AVLLS_MASK) /* Mask of allowed low power modes used to initialize power modes protection register */

/* Internal reference clock trim */

/* #undef SLOW_TRIM_ADDRESS */                             /* Slow oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef SLOW_FINE_TRIM_ADDRESS */                        /* Slow oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef FAST_TRIM_ADDRESS */                             /* Fast oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef FAST_FINE_TRIM_ADDRESS */                        /* Fast oscillator not trimmed. Commented out for MISRA compliance. */

/* System clock */

#ifdef CLOCK_SETUP
#if (CLOCK_SETUP == 0)
  #define DEFAULT_SYSTEM_CLOCK          20971520UL         /* Default System clock value */
  #define MCG_MODE                      MCG_MODE_FEI       /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE           0x06U              /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE           0x24U              /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE           0x00U              /* MCG_C4 */
  /* MCG_C6: CME=0 */
  #define SYSTEM_MCG_C6_VALUE           0x00U              /* MCG_C6 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE           0x00U              /* MCG_SC */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE          0x80U              /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_SOPT1: OSC32KSEL=3 */
  #define SYSTEM_SIM_SOPT1_VALUE        0x000C0000UL       /* SIM_SOPT1 */
  /* SIM_SOPT2: FTMFFCLKSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE        0x00UL             /* SIM_SOPT2 */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=0,OUTDIV5EN=0,OUTDIV5=0 */
  #define SYSTEM_SIM_CLKDIV1_VALUE      0x00UL             /* SIM_CLKDIV1 */
#elif (CLOCK_SETUP == 1)
  #define DEFAULT_SYSTEM_CLOCK          75000000UL         /* Default System clock value */
  #define MCG_MODE                      MCG_MODE_FEE       /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE           0x1AU              /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE           0x24U              /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=2,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE           0x40U              /* MCG_C4 */
  /* MCG_C6: CME=0 */
  #define SYSTEM_MCG_C6_VALUE           0x00U              /* MCG_C6 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE           0x00U              /* MCG_SC */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE          0x80U              /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_SOPT1: OSC32KSEL=3 */
  #define SYSTEM_SIM_SOPT1_VALUE        0x000C0000UL       /* SIM_SOPT1 */
  /* SIM_SOPT2: FTMFFCLKSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE        0x00UL             /* SIM_SOPT2 */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=2,OUTDIV5EN=0,OUTDIV5=0 */
  #define SYSTEM_SIM_CLKDIV1_VALUE      0x00020000UL       /* SIM_CLKDIV1 */
#elif (CLOCK_SETUP == 2)
  #define DEFAULT_SYSTEM_CLOCK          4000000UL          /* Default System clock value */
  #define MCG_MODE                      MCG_MODE_BLPI      /* Clock generator mode */
  /* MCG_C1: CLKS=1,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE           0x46U              /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=1,IRCS=1 */
  #define SYSTEM_MCG_C2_VALUE           0x27U              /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE           0x00U              /* MCG_C4 */
  /* MCG_C6: CME=0 */
  #define SYSTEM_MCG_C6_VALUE           0x00U              /* MCG_C6 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE           0x00U              /* MCG_SC */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE          0x80U              /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_SOPT1: OSC32KSEL=3 */
  #define SYSTEM_SIM_SOPT1_VALUE        0x000C0000UL       /* SIM_SOPT1 */
  /* SIM_SOPT2: FTMFFCLKSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE        0x00UL             /* SIM_SOPT2 */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=4,OUTDIV5EN=0,OUTDIV5=0 */
  #define SYSTEM_SIM_CLKDIV1_VALUE      0x00040000UL       /* SIM_CLKDIV1 */
#elif (CLOCK_SETUP == 3)
  #define DEFAULT_SYSTEM_CLOCK          3333333UL          /* Default System clock value */
  #define MCG_MODE                      MCG_MODE_BLPE      /* Clock generator mode */
  /* MCG_C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE           0x9AU              /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE=2,HGO=0,EREFS=1,LP=1,IRCS=1 */
  #define SYSTEM_MCG_C2_VALUE           0x27U              /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE           0x00U              /* MCG_C4 */
  /* MCG_C6: CME=0 */
  #define SYSTEM_MCG_C6_VALUE           0x00U              /* MCG_C6 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE           0x00U              /* MCG_SC */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE          0x80U              /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_SOPT1: OSC32KSEL=3 */
  #define SYSTEM_SIM_SOPT1_VALUE        0x000C0000UL       /* SIM_SOPT1 */
  /* SIM_SOPT2: FTMFFCLKSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE        0x00UL             /* SIM_SOPT2 */
  /* SIM_CLKDIV1: OUTDIV1=2,OUTDIV4=3,OUTDIV5EN=0,OUTDIV5=0 */
  #define SYSTEM_SIM_CLKDIV1_VALUE      0x20030000UL       /* SIM_CLKDIV1 */
#endif
#else
  #define DEFAULT_SYSTEM_CLOCK          20971520UL         /* Default System clock value */
#endif


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

#ifdef __cplusplus
}
#endif

#endif  /* #if !defined(SYSTEM_MKV10Z7_H_) */
