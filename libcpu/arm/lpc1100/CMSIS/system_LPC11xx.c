/**************************************************************************//**
 * @file     system_LPC11xx.c
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File
 *           for the NXP LPC11xx Device Series
 * @version  V1.00
 * @date     17. November 2009
 *
 * @note
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/


#include <stdint.h>
#include "LPC11xx.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//
// <e> Clock Configuration
//   <e1> System Clock Setup
//     <e2> System Oscillator Enable
//       <o3.1> Select System Oscillator Frequency Range
//                     <0=> 1 - 20 MHz
//                     <1=> 15 - 25 MHz
//     </e2>
//     <e4> Watchdog Oscillator Enable
//       <o5.0..4> Select Divider for Fclkana
//                     <0=>   2 <1=>   4 <2=>   6 <3=>   8
//                     <4=>  10 <5=>  12 <6=>  14 <7=>  16
//                     <8=>  18 <9=>  20 <10=> 22 <11=> 24
//                     <12=> 26 <13=> 28 <14=> 30 <15=> 32
//                     <16=> 34 <17=> 36 <18=> 38 <19=> 40
//                     <20=> 42 <21=> 44 <22=> 46 <23=> 48
//                     <24=> 50 <25=> 52 <26=> 54 <27=> 56
//                     <28=> 58 <29=> 60 <30=> 62 <31=> 64
//       <o5.5..8> Select Watchdog Oscillator Analog Frequency (Fclkana)
//                     <0=> Disabled
//                     <1=> 0.5 MHz
//                     <2=> 0.8 MHz
//                     <3=> 1.1 MHz
//                     <4=> 1.4 MHz
//                     <5=> 1.6 MHz
//                     <6=> 1.8 MHz
//                     <7=> 2.0 MHz
//                     <8=> 2.2 MHz
//                     <9=> 2.4 MHz
//                     <10=> 2.6 MHz
//                     <11=> 2.7 MHz
//                     <12=> 2.9 MHz
//                     <13=> 3.1 MHz
//                     <14=> 3.2 MHz
//                     <15=> 3.4 MHz
//     </e4>
//     <o6> Select Input Clock for sys_pllclkin (Register: SYSPLLCLKSEL)
//                     <0=> IRC Oscillator
//                     <1=> System Oscillator
//                     <2=> WDT Oscillator
//                     <3=> Invalid
//     <e7> Use System PLL
//                     <i> F_pll = M * F_in
//                     <i> F_in must be in the range of 10 MHz to 25 MHz
//       <o8.0..4>   M: PLL Multiplier Selection
//                     <1-32><#-1>
//       <o8.5..6>   P: PLL Divider Selection
//                     <0=> 2
//                     <1=> 4
//                     <2=> 8
//                     <3=> 16
//       <o8.7>      DIRECT: Direct CCO Clock Output Enable
//       <o8.8>      BYPASS: PLL Bypass Enable
//     </e7>
//     <o9> Select Input Clock for Main clock (Register: MAINCLKSEL)
//                     <0=> IRC Oscillator
//                     <1=> Input Clock to System PLL
//                     <2=> WDT Oscillator
//                     <3=> System PLL Clock Out
//   </e1>
//   <o10.0..7> System AHB Divider <0-255>
//                     <i> 0 = is disabled
//   <o11.0>   SYS Clock Enable
//   <o11.1>   ROM Clock Enable
//   <o11.2>   RAM Clock Enable
//   <o11.3>   FLASHREG Flash Register Interface Clock Enable
//   <o11.4>   FLASHARRAY Flash Array Access Clock Enable
//   <o11.5>   I2C Clock Enable
//   <o11.6>   GPIO Clock Enable
//   <o11.7>   CT16B0 Clock Enable
//   <o11.8>   CT16B1 Clock Enable
//   <o11.9>   CT32B0 Clock Enable
//   <o11.10>  CT32B1 Clock Enable
//   <o11.11>  SSP0 Clock Enable
//   <o11.12>  UART Clock Enable
//   <o11.13>  ADC Clock Enable
//   <o11.15>  WDT Clock Enable
//   <o11.16>  IOCON Clock Enable
//   <o11.18>  SSP1 Clock Enable
//
//   <o12.0..7> SSP0 Clock Divider <0-255>
//                     <i> 0 = is disabled
//   <o13.0..7> UART Clock Divider <0-255>
//                     <i> 0 = is disabled
//   <o14.0..7> SSP1 Clock Divider <0-255>
//                     <i> 0 = is disabled
// </e>
*/
#define CLOCK_SETUP           1
#define SYSCLK_SETUP          1
#define SYSOSC_SETUP          1
#define SYSOSCCTRL_Val        0x00000000
#define WDTOSC_SETUP          0
#define WDTOSCCTRL_Val        0x000000A0
#define SYSPLLCLKSEL_Val      0x00000001
#define SYSPLL_SETUP          1
#define SYSPLLCTRL_Val        0x00000023
#define MAINCLKSEL_Val        0x00000003
#define SYSAHBCLKDIV_Val      0x00000001
#define AHBCLKCTRL_Val        0x0001005F
#define SSP0CLKDIV_Val        0x00000001
#define UARTCLKDIV_Val        0x00000001
#define SSP1CLKDIV_Val        0x00000001

/*--------------------- Memory Mapping Configuration -------------------------
//
// <e> Memory Mapping
//   <o1.0..1> System Memory Remap (Register: SYSMEMREMAP)
//                     <0=> Bootloader mapped to address 0
//                     <1=> RAM mapped to address 0
//                     <2=> Flash mapped to address 0
//                     <3=> Flash mapped to address 0
// </e>
*/
#define MEMMAP_SETUP          0
#define SYSMEMREMAP_Val       0x00000001

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*----------------------------------------------------------------------------
  Check the register settings
 *----------------------------------------------------------------------------*/
#define CHECK_RANGE(val, min, max)                ((val < min) || (val > max))
#define CHECK_RSVD(val, mask)                     (val & mask)

/* Clock Configuration -------------------------------------------------------*/
#if (CHECK_RSVD((SYSOSCCTRL_Val),  ~0x00000003))
   #error "SYSOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((WDTOSCCTRL_Val),  ~0x000001FF))
   #error "WDTOSCCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSPLLCLKSEL_Val), 0, 2))
   #error "SYSPLLCLKSEL: Value out of range!"
#endif

#if (CHECK_RSVD((SYSPLLCTRL_Val),  ~0x000001FF))
   #error "SYSPLLCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((MAINCLKSEL_Val),  ~0x00000003))
   #error "MAINCLKSEL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SYSAHBCLKDIV_Val), 0, 255))
   #error "SYSAHBCLKDIV: Value out of range!"
#endif

#if (CHECK_RSVD((AHBCLKCTRL_Val),  ~0x0001FFFF))
   #error "AHBCLKCTRL: Invalid values of reserved bits!"
#endif

#if (CHECK_RANGE((SSP0CLKDIV_Val), 0, 255))
   #error "SSP0CLKDIV: Value out of range!"
#endif

#if (CHECK_RANGE((UARTCLKDIV_Val), 0, 255))
   #error "UARTCLKDIV: Value out of range!"
#endif

#if (CHECK_RANGE((SSP1CLKDIV_Val), 0, 255))
   #error "SSP1CLKDIV: Value out of range!"
#endif

#if (CHECK_RSVD((SYSMEMREMAP_Val), ~0x00000003))
   #error "SYSMEMREMAP: Invalid values of reserved bits!"
#endif


/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/
    
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __XTAL            (12000000UL)    /* Oscillator frequency             */
#define __SYS_OSC_CLK     (    __XTAL)    /* Main oscillator frequency        */
#define __IRC_OSC_CLK     (12000000UL)    /* Internal RC oscillator frequency */


#define __FREQSEL   ((WDTOSCCTRL_Val >> 5) & 0x0F)
#define __DIVSEL   (((WDTOSCCTRL_Val & 0x1F) << 1) + 2)

#if (CLOCK_SETUP)                         /* Clock Setup              */
  #if (SYSCLK_SETUP)                      /* System Clock Setup       */
    #if (WDTOSC_SETUP)                    /* Watchdog Oscillator Setup*/
        #if  (__FREQSEL ==  0)
          #define __WDT_OSC_CLK        ( 400000 / __DIVSEL)
        #elif (__FREQSEL ==  1)
          #define __WDT_OSC_CLK        ( 500000 / __DIVSEL)
        #elif (__FREQSEL ==  2)
          #define __WDT_OSC_CLK        ( 800000 / __DIVSEL)
        #elif (__FREQSEL ==  3)
          #define __WDT_OSC_CLK        (1100000 / __DIVSEL)
        #elif (__FREQSEL ==  4)
          #define __WDT_OSC_CLK        (1400000 / __DIVSEL)
        #elif (__FREQSEL ==  5)
          #define __WDT_OSC_CLK        (1600000 / __DIVSEL)
        #elif (__FREQSEL ==  6)
          #define __WDT_OSC_CLK        (1800000 / __DIVSEL)
        #elif (__FREQSEL ==  7)
          #define __WDT_OSC_CLK        (2000000 / __DIVSEL)
        #elif (__FREQSEL ==  8)
          #define __WDT_OSC_CLK        (2200000 / __DIVSEL)
        #elif (__FREQSEL ==  9)
          #define __WDT_OSC_CLK        (2400000 / __DIVSEL)
        #elif (__FREQSEL == 10)
          #define __WDT_OSC_CLK        (2600000 / __DIVSEL)
        #elif (__FREQSEL == 11)
          #define __WDT_OSC_CLK        (2700000 / __DIVSEL)
        #elif (__FREQSEL == 12)
          #define __WDT_OSC_CLK        (2900000 / __DIVSEL)
        #elif (__FREQSEL == 13)
          #define __WDT_OSC_CLK        (3100000 / __DIVSEL)
        #elif (__FREQSEL == 14)
          #define __WDT_OSC_CLK        (3200000 / __DIVSEL)
        #else
          #define __WDT_OSC_CLK        (3400000 / __DIVSEL)
        #endif
    #else
          #define __WDT_OSC_CLK        (1600000 / 2)
    #endif  // WDTOSC_SETUP

    /* sys_pllclkin calculation */
    #if   ((SYSPLLCLKSEL_Val & 0x03) == 0)
      #define __SYS_PLLCLKIN           (__IRC_OSC_CLK)
    #elif ((SYSPLLCLKSEL_Val & 0x03) == 1)
      #define __SYS_PLLCLKIN           (__SYS_OSC_CLK)
    #elif ((SYSPLLCLKSEL_Val & 0x03) == 2)
      #define __SYS_PLLCLKIN           (__WDT_OSC_CLK)
    #else
      #define __SYS_PLLCLKIN           (0)
    #endif

    #if (SYSPLL_SETUP)                    /* System PLL Setup         */
      #define  __SYS_PLLCLKOUT         (__SYS_PLLCLKIN * ((SYSPLLCTRL_Val & 0x01F) + 1))
    #else
      #define  __SYS_PLLCLKOUT         (__SYS_PLLCLKIN * (1))
    #endif  // SYSPLL_SETUP

    /* main clock calculation */
    #if   ((MAINCLKSEL_Val & 0x03) == 0)
      #define __MAIN_CLOCK             (__IRC_OSC_CLK)
    #elif ((MAINCLKSEL_Val & 0x03) == 1)
      #define __MAIN_CLOCK             (__SYS_PLLCLKIN)
    #elif ((MAINCLKSEL_Val & 0x03) == 2)
      #define __MAIN_CLOCK             (__WDT_OSC_CLK)
    #elif ((MAINCLKSEL_Val & 0x03) == 3)
      #define __MAIN_CLOCK             (__SYS_PLLCLKOUT)
    #else
      #define __MAIN_CLOCK             (0)
    #endif

    #define __SYSTEM_CLOCK             (__MAIN_CLOCK / SYSAHBCLKDIV_Val)         

  #else // SYSCLK_SETUP
    #if (SYSAHBCLKDIV_Val == 0)
      #define __SYSTEM_CLOCK           (0)
    #else
      #define __SYSTEM_CLOCK           (__XTAL / SYSAHBCLKDIV_Val)
    #endif
  #endif // SYSCLK_SETUP

#else
  #define __SYSTEM_CLOCK               (__XTAL)
#endif  // CLOCK_SETUP 


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = __SYSTEM_CLOCK;/*!< System Clock Frequency (Core Clock)*/


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  uint32_t wdt_osc = 0;

  /* Determine clock frequency according to clock register values             */
  switch ((LPC_SYSCON->WDTOSCCTRL >> 5) & 0x0F) {
    case 0:  wdt_osc =  400000; break;
    case 1:  wdt_osc =  500000; break;
    case 2:  wdt_osc =  800000; break;
    case 3:  wdt_osc = 1100000; break;
    case 4:  wdt_osc = 1400000; break;
    case 5:  wdt_osc = 1600000; break;
    case 6:  wdt_osc = 1800000; break;
    case 7:  wdt_osc = 2000000; break;
    case 8:  wdt_osc = 2200000; break;
    case 9:  wdt_osc = 2400000; break;
    case 10: wdt_osc = 2600000; break;
    case 11: wdt_osc = 2700000; break;
    case 12: wdt_osc = 2900000; break;
    case 13: wdt_osc = 3100000; break;
    case 14: wdt_osc = 3200000; break;
    case 15: wdt_osc = 3400000; break;
  }
  wdt_osc /= ((LPC_SYSCON->WDTOSCCTRL & 0x1F) << 1) + 2;
 
  switch (LPC_SYSCON->MAINCLKSEL & 0x03) {
    case 0:                             /* Internal RC oscillator             */
      SystemCoreClock = __IRC_OSC_CLK;
      break;
    case 1:                             /* Input Clock to System PLL          */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                       /* Internal RC oscillator             */
            SystemCoreClock = __IRC_OSC_CLK;
            break;
          case 1:                       /* System oscillator                  */
            SystemCoreClock = __SYS_OSC_CLK;
            break;
          case 2:                       /* WDT Oscillator                     */
            SystemCoreClock = wdt_osc;
            break;
          case 3:                       /* Reserved                           */
            SystemCoreClock = 0;
            break;
      }
      break;
    case 2:                             /* WDT Oscillator                     */
      SystemCoreClock = wdt_osc;
      break;
    case 3:                             /* System PLL Clock Out               */
      switch (LPC_SYSCON->SYSPLLCLKSEL & 0x03) {
          case 0:                       /* Internal RC oscillator             */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = __IRC_OSC_CLK;
            } else {
              SystemCoreClock = __IRC_OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 1:                       /* System oscillator                  */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = __SYS_OSC_CLK;
            } else {
              SystemCoreClock = __SYS_OSC_CLK * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 2:                       /* WDT Oscillator                     */
            if (LPC_SYSCON->SYSPLLCTRL & 0x180) {
              SystemCoreClock = wdt_osc;
            } else {
              SystemCoreClock = wdt_osc * ((LPC_SYSCON->SYSPLLCTRL & 0x01F) + 1);
            }
            break;
          case 3:                       /* Reserved                           */
            SystemCoreClock = 0;
            break;
      }
      break;
  }

  SystemCoreClock /= LPC_SYSCON->SYSAHBCLKDIV;  

}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
#if (CLOCK_SETUP)                                 /* Clock Setup              */
#if (SYSCLK_SETUP)                                /* System Clock Setup       */
#if (SYSOSC_SETUP)                                /* System Oscillator Setup  */
  uint32_t i;

  LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          /* Power-up System Osc      */
  LPC_SYSCON->SYSOSCCTRL    = SYSOSCCTRL_Val;
  for (i = 0; i < 200; i++) __NOP();
  LPC_SYSCON->SYSPLLCLKSEL  = SYSPLLCLKSEL_Val;   /* Select PLL Input         */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;               /* Update Clock Source      */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
  while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));     /* Wait Until Updated       */
#if (SYSPLL_SETUP)                                /* System PLL Setup         */
  LPC_SYSCON->SYSPLLCTRL    = SYSPLLCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          /* Power-up SYSPLL          */
  while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      /* Wait Until PLL Locked    */
#endif
#endif
#if (WDTOSC_SETUP)                                /* Watchdog Oscillator Setup*/
  LPC_SYSCON->WDTOSCCTRL    = WDTOSCCTRL_Val;
  LPC_SYSCON->PDRUNCFG     &= ~(1 << 6);          /* Power-up WDT Clock       */
#endif
  LPC_SYSCON->MAINCLKSEL    = MAINCLKSEL_Val;     /* Select PLL Clock Output  */
  LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
  LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
#endif

  LPC_SYSCON->SYSAHBCLKDIV  = SYSAHBCLKDIV_Val;
  LPC_SYSCON->SYSAHBCLKCTRL = AHBCLKCTRL_Val;
  LPC_SYSCON->SSP0CLKDIV    = SSP0CLKDIV_Val;
  LPC_SYSCON->UARTCLKDIV    = UARTCLKDIV_Val;
  LPC_SYSCON->SSP1CLKDIV    = SSP1CLKDIV_Val;
#endif


#if (MEMMAP_SETUP || MEMMAP_INIT)       /* Memory Mapping Setup               */
  LPC_SYSCON->SYSMEMREMAP = SYSMEMREMAP_Val;
#endif
}
