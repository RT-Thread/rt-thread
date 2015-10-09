/*
** ###################################################################
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          GNU C Compiler - CodeSourcery Sourcery G++
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    MKW01xxRM, Rev.1, December 2013
**     Version:             rev. 1.1, 2015-01-13
**     Build:               b150129
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
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
**     - rev. 1.0 (2013-11-22)
**         Initial version.
**     - rev. 1.1 (2015-01-13)
**         Update of the copyright.
**         Update of the clock setup.
**
** ###################################################################
*/

/*!
 * @file MKW01Z4
 * @version 1.1
 * @date 2015-01-13
 * @brief Device specific configuration file for MKW01Z4 (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef SYSTEM_MKW01Z4_H_
#define SYSTEM_MKW01Z4_H_                        /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#ifndef DISABLE_WDOG
  #define DISABLE_WDOG                 1
#endif
#ifndef RTC_CLKIN_USED
  #define RTC_CLKIN_USED               1
#endif

#define ACK_ISOLATION                  1


/* MCG mode constants */

#define MCG_MODE_FEI                   0U
#define MCG_MODE_FBI                   1U
#define MCG_MODE_BLPI                  2U
#define MCG_MODE_FEE                   3U
#define MCG_MODE_FBE                   4U
#define MCG_MODE_BLPE                  5U
#define MCG_MODE_PBE                   6U
#define MCG_MODE_PEE                   7U

/* Predefined clock setups
   0 ... Default part configuration
         Multipurpose Clock Generator (MCG) in FEI mode.
         Reference clock source for MCG module: Slow internal reference clock
         Core clock = 20.97152MHz
         Bus clock  = 20.97152MHz
   1 ... Maximum achievable clock frequency configuration. Chip externally clocked from crystal 32.768 kHz on the board
         Multipurpose Clock Generator (MCG) in FEE mode.
         Reference clock source for MCG module: System oscillator reference clock
         Core clock = 48MHz
         Bus clock  = 24MHz
   2 ... Chip internally clocked, ready for Very Low Power Run mode
         Multipurpose Clock Generator (MCG) in BLPI mode.
         Reference clock source for MCG module: Fast internal reference clock
         Core clock = 4MHz
         Bus clock  = 0.8MHz
   3 ... Chip externally clocked, ready for Very Low Power Run mode
         Multipurpose Clock Generator (MCG) in BLPE mode.
         Reference clock source for MCG module: System oscillator reference clock
         Core clock = 1MHz
         Bus clock  = 0.5MHz
   4 ... Chip externally clocked from Sub 1 GHz Low Power Transceiver with 32 MHz crystal
         Multipurpose Clock Generator (MCG) in PEE mode.
         Reference clock source for MCG module: System oscillator reference clock
         Core clock = 48MHz
         Bus clock  = 24MHz
   5 ... Chip externally clocked from Sub 1 GHz Low Power Transceiver with 30 MHz crystal
         Multipurpose Clock Generator (MCG) in PEE mode.
         Reference clock source for MCG module: System oscillator reference clock
         Core clock = 48MHz
         Bus clock  = 24MHz
*/

/* Define clock source values */

#define CPU_INT_SLOW_CLK_HZ            32768U              /* Value of the slow internal oscillator clock frequency in Hz */
#define CPU_INT_FAST_CLK_HZ            4000000U            /* Value of the fast internal oscillator clock frequency in Hz */
#if defined(MRB_KW01_9030JA)
  #define CPU_MODEM_XTAL_CLK_HZ        3000000U            /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
#else
  #define CPU_MODEM_XTAL_CLK_HZ        3200000U            /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
#endif

/* RTC oscillator setting */

/* Low power mode enable */
/* SMC_PMPROT: AVLP=1,ALLS=1,AVLLS=1 */
#define SYSTEM_SMC_PMPROT_VALUE        0x2AU               /* SMC_PMPROT */

/* Define address of modem prescaler register */
#define SYSTEM_MODEM_CLK_OUT_CTRL_ADDRESS 0xA6U            /* Modem_CLK_OUT_CTRL register value used to configure CLKOUT frequency */

/* Internal reference clock trim */
/* #undef SLOW_TRIM_ADDRESS */                             /* Slow oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef SLOW_FINE_TRIM_ADDRESS */                        /* Slow oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef FAST_TRIM_ADDRESS */                             /* Fast oscillator not trimmed. Commented out for MISRA compliance. */
/* #undef FAST_FINE_TRIM_ADDRESS */                        /* Fast oscillator not trimmed. Commented out for MISRA compliance. */

#ifdef CLOCK_SETUP
#if (CLOCK_SETUP == 0)
  #define CPU_XTAL_CLK_HZ              1000000U            /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
  #define SYSTEM_EXTCLK_INIT           CPU_XTAL_CLK_HZ     /* Perform initialization of the wireless modem */
  #define DEFAULT_SYSTEM_CLOCK         20971520U           /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_FEI        /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x06U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0x24U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE         0x80U               /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=0 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00U               /* SIM_CLKDIV1 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=3 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x000C0000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: UART0SRC=0,TPMSRC=1,USBSRC=0,PLLFLLSEL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01000000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 1)
  #define CPU_XTAL_CLK_HZ              32768U              /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
  #define DEFAULT_SYSTEM_CLOCK         48000000U           /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_FEE        /* Clock generator mode */
  /* MCG_C1: CLKS=0,FRDIV=0,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x02U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE0=0,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0x04U               /* MCG_C2 */
  /* MCG_C4: DMX32=1,DRST_DRS=1,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0xA0U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE         0x80U               /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=1 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00010000U         /* SIM_CLKDIV1 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=0 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x00000000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: UART0SRC=0,TPMSRC=1,USBSRC=0,PLLFLLSEL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01000000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 2)
  #define CPU_XTAL_CLK_HZ              1000000U            /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
  #define SYSTEM_EXTCLK_INIT           CPU_XTAL_CLK_HZ     /* Perform initialization of the wireless modem */
  #define DEFAULT_SYSTEM_CLOCK         4000000U            /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_BLPI /* Clock generator mode */
  /* MCG_C1: CLKS=1,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x46U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE0=2,HGO0=0,EREFS0=1,LP=1,IRCS=1 */
  #define SYSTEM_MCG_C2_VALUE          0x27U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE         0x80U               /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=4 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00040000U         /* SIM_CLKDIV1 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=3 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x000C0000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: UART0SRC=0,TPMSRC=2,USBSRC=0,PLLFLLSEL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x02000000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 3)
  #define CPU_XTAL_CLK_HZ              1000000U            /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
  #define SYSTEM_EXTCLK_INIT           CPU_XTAL_CLK_HZ     /* Perform initialization of the wireless modem */
  #define DEFAULT_SYSTEM_CLOCK         1000000U            /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_BLPE       /* Clock generator mode */
  /* MCG_C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x9AU               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE0=1,HGO0=0,EREFS0=0,LP=1,IRCS=1 */
  #define SYSTEM_MCG_C2_VALUE          0x13U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=0 */
  #define SYSTEM_MCG_C5_VALUE          0x00U               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  #define SYSTEM_MCG_C6_VALUE          0x00U               /* MCG_C6 */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE         0x80U               /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=1,OUTDIV4=3 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x10030000U         /* SIM_CLKDIV1 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=3 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x000C0000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: UART0SRC=0,TPMSRC=2,USBSRC=0,PLLFLLSEL=0,CLKOUTSEL=0,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x02000000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 4)
  #define CPU_XTAL_CLK_HZ              32000000U           /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
  #define SYSTEM_EXTCLK_INIT           CPU_XTAL_CLK_HZ     /* Perform initialization of the wireless modem */
  #define DEFAULT_SYSTEM_CLOCK         48000000U           /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_PEE        /* Clock generator mode */
  #define SYSTEM_MODEM_CLK_OUT_CTRL_VALUE   0x00U          /* Modem_CLK_OUT_CTRL register address for write */
  /* MCG_C1: CLKS=0,FRDIV=0,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x02U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE0=2,HGO0=0,EREFS0=0,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0xA0U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=16 */
  #define SYSTEM_MCG_C5_VALUE          0x0FU               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
  #define SYSTEM_MCG_C6_VALUE          0x40U               /* MCG_C6 */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE         0x80U               /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=1 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00010000U         /* SIM_CLKDIV1 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=3 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x000C0000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: UART0SRC=0,TPMSRC=1,USBSRC=0,PLLFLLSEL=1,CLKOUTSEL=2,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01010000U         /* SIM_SOPT2 */
#elif (CLOCK_SETUP == 5)
  #define CPU_XTAL_CLK_HZ              30000000U           /* Value of the external crystal or oscillator clock frequency of the system oscillator (OSC) in Hz */
  #define SYSTEM_EXTCLK_INIT           CPU_XTAL_CLK_HZ     /* Perform initialization of the wireless modem */
  #define DEFAULT_SYSTEM_CLOCK         48000000U           /* Default System clock value */
  #define MCG_MODE                     MCG_MODE_PEE        /* Clock generator mode */
  #define SYSTEM_MODEM_CLK_OUT_CTRL_VALUE   0x00U          /* Modem_CLK_OUT_CTRL register address for write */
  /* MCG_C1: CLKS=0,FRDIV=0,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  #define SYSTEM_MCG_C1_VALUE          0x02U               /* MCG_C1 */
  /* MCG_C2: LOCRE0=0,FCFTRIM=0,RANGE0=2,HGO0=0,EREFS0=0,LP=0,IRCS=0 */
  #define SYSTEM_MCG_C2_VALUE          0xA0U               /* MCG_C2 */
  /* MCG_C4: DMX32=0,DRST_DRS=0,FCTRIM=0,SCFTRIM=0 */
  #define SYSTEM_MCG_C4_VALUE          0x00U               /* MCG_C4 */
  /* MCG_SC: ATME=0,ATMS=0,ATMF=0,FLTPRSRV=0,FCRDIV=0,LOCS0=0 */
  #define SYSTEM_MCG_SC_VALUE          0x00U               /* MCG_SC */
  /* MCG_C5: PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=15 */
  #define SYSTEM_MCG_C5_VALUE          0x0EU               /* MCG_C5 */
  /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
  #define SYSTEM_MCG_C6_VALUE          0x40U               /* MCG_C6 */
  /* OSC0_CR: ERCLKEN=1,EREFSTEN=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  #define SYSTEM_OSC0_CR_VALUE         0x80U               /* OSC0_CR */
  /* SMC_PMCTRL: RUNM=0,STOPA=0,STOPM=0 */
  #define SYSTEM_SMC_PMCTRL_VALUE      0x00U               /* SMC_PMCTRL */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV4=1 */
  #define SYSTEM_SIM_CLKDIV1_VALUE     0x00010000U         /* SIM_CLKDIV1 */
  /* SIM_SOPT1: USBREGEN=0,USBSSTBY=0,USBVSTBY=0,OSC32KSEL=3 */
  #define SYSTEM_SIM_SOPT1_VALUE       0x000C0000U         /* SIM_SOPT1 */
  /* SIM_SOPT2: UART0SRC=0,TPMSRC=1,USBSRC=0,PLLFLLSEL=1,CLKOUTSEL=2,RTCCLKOUTSEL=0 */
  #define SYSTEM_SIM_SOPT2_VALUE       0x01010000U         /* SIM_SOPT2 */
#endif
#else //#ifdef CLOCK_SETUP
  #define CPU_XTAL_CLK_HZ              1000000U
  #define DEFAULT_SYSTEM_CLOCK         20971520U           /* Default System clock value */
#endif //#ifdef CLOCK_SETUP



/**
 * @brief Configure the external clock source
 *
 * The wireless modem present in the system can supply clock which can be used
 * as a clock source for the whole system. This function is defined as weak.
 *
 */
extern uint8_t ExtClk_Setup_HookUp(uint32_t clk_out_value);
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

#endif  /* #if !defined(SYSTEM_MKW01Z4_H_) */
