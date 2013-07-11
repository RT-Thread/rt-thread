/*
** ###################################################################
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    K60P144M150SF3RM, Rev. 2, Dec 2011
**     Version:             rev. 1.3, 2012-04-13
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright: 2012 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2011-08-24)
**         Initial version
**     - rev. 1.1 (2011-11-03)
**         Registers updated according to the new reference manual revision - Rev. 1, Oct 2011
**         Registers of the following modules have been updated - AXBS, CAN, I2S, MCG, MPU, NFC, RCM, RTC, SDHC, SIM, USBHS, WDOG
**         The following modules have been removed - DDR, DRY
**     - rev. 1.2 (2012-01-04)
**         Registers updated according to the new reference manual revision - Rev. 2, Dec 2011
**         EWM - INTEN bit in EWM_CTRL register has been added.
**         PDB - register PDB_PO0EN renamed to PRB_POEN.
**         PMC - BGEN bit in PMC_REGSC register has been removed.
**         SIM - several changes in SCGC registers. Bit USBHS in SOPT2 register removed.
**         UART - new bits RXOFE in regiter CFIFO and RXOF in register SFIFO.
**     - rev. 1.3 (2012-04-13)
**         Added new #define symbol MCU_MEM_MAP_VERSION_MINOR.
**         Added new #define symbols <peripheralType>_BASE_PTRS.
**
** ###################################################################
*/

/**
 * @file MK60F12
 * @version 1.3
 * @date 2012-04-13
 * @brief Device specific configuration file for MK60F12 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "MK60F12.h"

#define DISABLE_WDOG    1


#define CLOCK_SETUP     1
/* Predefined clock setups
   0 ... Multipurpose Clock Generator (MCG) in FLL Engaged Internal (FEI) mode
         Reference clock source for MCG module is the slow internal clock source 32.768kHz
         Core clock = 41.94MHz, BusClock = 41.94MHz
   1 ... Multipurpose Clock Generator (MCG) in PLL Engaged External (PEE) mode
         Reference clock source for MCG module is an external reference clock source 50MHz
         Core clock = 120MHz, BusClock = 60MHz
   2 ... Multipurpose Clock Generator (MCG) in Bypassed Low Power External (BLPE) mode
         Core clock/Bus clock derived directly from an external reference clock source 50MHz with no multiplication
         Core clock = 50MHz, BusClock = 50MHz
*/

/*----------------------------------------------------------------------------
  Define clock source values
 *----------------------------------------------------------------------------*/
#if (CLOCK_SETUP == 0)
    #define CPU_XTAL0_CLK_HZ                50000000u /* Value of the external crystal or oscillator clock frequency in Hz connected to System Oscillator 0 */
    #define CPU_XTAL1_CLK_HZ                8000000u  /* Value of the external crystal or oscillator clock frequency in Hz connected to System Oscillator 1 */
    #define CPU_XTAL32k_CLK_HZ              32768u    /* Value of the external 32k crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u    /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u  /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            41943040u /* Default System clock value */
#elif (CLOCK_SETUP == 1)
    #define CPU_XTAL0_CLK_HZ                50000000u /* Value of the external crystal or oscillator clock frequency in Hz connected to System Oscillator 0 */
    #define CPU_XTAL1_CLK_HZ                8000000u  /* Value of the external crystal or oscillator clock frequency in Hz connected to System Oscillator 1 */
    #define CPU_XTAL32k_CLK_HZ              32768u    /* Value of the external 32k crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u    /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u  /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            120000000u /* Default System clock value */
#elif (CLOCK_SETUP == 2)
    #define CPU_XTAL0_CLK_HZ                50000000u /* Value of the external crystal or oscillator clock frequency in Hz connected to System Oscillator 0 */
    #define CPU_XTAL1_CLK_HZ                8000000u  /* Value of the external crystal or oscillator clock frequency in Hz connected to System Oscillator 1 */
    #define CPU_XTAL32k_CLK_HZ              32768u    /* Value of the external 32k crystal or oscillator clock frequency in Hz */
    #define CPU_INT_SLOW_CLK_HZ             32768u    /* Value of the slow internal oscillator clock frequency in Hz  */
    #define CPU_INT_FAST_CLK_HZ             4000000u  /* Value of the fast internal oscillator clock frequency in Hz  */
    #define DEFAULT_SYSTEM_CLOCK            50000000u  /* Default System clock value */
#endif /* (CLOCK_SETUP == 2) */


/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */
#if (DISABLE_WDOG)
  /* Disable the WDOG module */
  /* WDOG_UNLOCK: WDOGUNLOCK=0xC520 */
  WDOG->UNLOCK = (uint16_t)0xC520u;     /* Key 1 */
  /* WDOG_UNLOCK : WDOGUNLOCK=0xD928 */
  WDOG->UNLOCK  = (uint16_t)0xD928u;    /* Key 2 */
  /* WDOG_STCTRLH: ??=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,??=0,STNDBYEN=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
  WDOG->STCTRLH = (uint16_t)0x01D2u;
#endif /* (DISABLE_WDOG) */

  /* System clock initialization */
#if (CLOCK_SETUP == 0)
  /* SIM_SCGC5: PORTA=1 */
  SIM->SCGC5 |= (uint32_t)0x0200UL;     /* Enable clock gate for ports to enable pin routing */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV3=1,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM->CLKDIV1 = (uint32_t)0x00110000UL; /* Update system prescalers */
  /* SIM_SOPT2: PLLFLLSEL=0 */
  SIM->SOPT2 &= (uint32_t)~0x00030000UL; /* Select FLL as a clock source for various peripherals */
  /* SIM_SOPT1: OSC32KSEL=0 */
  SIM->SOPT1 &= (uint32_t)~0x00080000UL; /* System oscillator drives 32 kHz clock for various peripherals */
  /* SIM_SCGC1: OSC1=1 */
  SIM->SCGC1 |= (uint32_t)0x20UL;
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA->PCR[18] &= (uint32_t)~0x01000700UL;
  /* Switch to FEI Mode */
  /* MCG_C1: CLKS=0,FRDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = (uint8_t)0x06U;
  /* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=0,LP=0,IRCS=0 */
  MCG->C2 = (uint8_t)0x20U;
  /* MCG_C4: DMX32=0,DRST_DRS=1 */
  MCG->C4 = (uint8_t)((MCG->C4 & (uint8_t)~(uint8_t)0xC0U) | (uint8_t)0x20U);
  /* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC0->CR = (uint8_t)0x80U;
  /* OSC1_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC1->CR = (uint8_t)0x80U;
  /* MCG_C7: OSCSEL=0 */
  MCG->C7 &= (uint8_t)~(uint8_t)0x01U;
  /* MCG_C5: PLLREFSEL0=0,PLLCLKEN0=0,PLLSTEN0=0,??=0,??=0,PRDIV0=0 */
  MCG->C5 = (uint8_t)0x00U;
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  MCG->C6 = (uint8_t)0x00U;             /* 3 */
  /* MCG_C11: PLLREFSEL1=0,PLLCLKEN1=0,PLLSTEN1=0,PLLCS=0,??=0,PRDIV1=0 */
  MCG->C11 = (uint8_t)0x00U;            /* 3 */
  /* MCG_C12: LOLIE1=0,??=0,CME2=0,VDIV1=0 */
  MCG->C12 = (uint8_t)0x00U;            /* 3 */
  while((MCG->S & MCG_S_IREFST_MASK) == 0x00U) { /* Check that the source of the FLL reference clock is the internal reference clock. */
  }
  while((MCG->S & 0x0CU) != 0x00U) {    /* Wait until output of the FLL is selected */
  }
#elif (CLOCK_SETUP == 1)
  /* SIM_SCGC5: PORTA=1 */
  SIM->SCGC5 |= (uint32_t)0x0200UL;     /* Enable clock gate for ports to enable pin routing */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=1,OUTDIV3=3,OUTDIV4=5,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM->CLKDIV1 = (uint32_t)0x01350000UL; /* Update system prescalers */
  /* SIM_SOPT2: PLLFLLSEL=1 */
  SIM->SOPT2 = (uint32_t)((SIM->SOPT2 & (uint32_t)~0x00020000UL) | (uint32_t)0x00010000UL); /* Select PLL 0 as a clock source for various peripherals */
  /* SIM_SOPT1: OSC32KSEL=0 */
  SIM->SOPT1 &= (uint32_t)~0x00080000UL; /* System oscillator drives 32 kHz clock for various peripherals */
  /* SIM_SCGC1: OSC1=1 */
  SIM->SCGC1 |= (uint32_t)0x20UL;
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA->PCR[18] &= (uint32_t)~0x01000700UL;
  /* Switch to FBE Mode */
  /* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC0->CR = (uint8_t)0x80U;
  /* OSC1_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC1->CR = (uint8_t)0x80U;
  /* MCG_C7: OSCSEL=0 */
  MCG->C7 &= (uint8_t)~(uint8_t)0x01U;
  /* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=0,LP=0,IRCS=0 */
  MCG->C2 = (uint8_t)0x20U;
  /* MCG_C1: CLKS=2,FRDIV=5,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = (uint8_t)0xAAU;
  /* MCG_C4: DMX32=0,DRST_DRS=0 */
  MCG->C4 &= (uint8_t)~(uint8_t)0xE0U;
  /* MCG_C5: PLLREFSEL0=0,PLLCLKEN0=0,PLLSTEN0=0,??=0,??=0,PRDIV0=4 */
  MCG->C5 = (uint8_t)0x04U;
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=8 */
  MCG->C6 = (uint8_t)0x08U;
  /* MCG_C11: PLLREFSEL1=0,PLLCLKEN1=0,PLLSTEN1=0,PLLCS=0,??=0,PRDIV1=0 */
  MCG->C11 = (uint8_t)0x00U;
  /* MCG_C12: LOLIE1=0,??=0,CME2=0,VDIV1=0 */
  MCG->C12 = (uint8_t)0x00U;
  while((MCG->S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
  }
  while((MCG->S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
  /* Switch to PBE Mode */
  /* MCG_C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=8 */
  MCG->C6 = (uint8_t)0x48U;
  while((MCG->S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
  while((MCG->S & MCG_S_LOCK0_MASK) == 0x00U) { /* Wait until PLL locked */
  }
  /* Switch to PEE Mode */
  /* MCG->C1: CLKS=0,FRDIV=5,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = (uint8_t)0x2AU;
  while((MCG->S & 0x0CU) != 0x0CU) {    /* Wait until output of the PLL is selected */
  }
#elif (CLOCK_SETUP == 2)
  /* SIM_SCGC5: PORTA=1 */
  SIM->SCGC5 |= (uint32_t)0x0200UL;     /* Enable clock gate for ports to enable pin routing */
  /* SIM_CLKDIV1: OUTDIV1=0,OUTDIV2=0,OUTDIV3=1,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SIM->CLKDIV1 = (uint32_t)0x00110000UL; /* Update system prescalers */
  /* SIM_SOPT2: PLLFLLSEL=0 */
  SIM->SOPT2 &= (uint32_t)~0x00030000UL; /* Select FLL as a clock source for various peripherals */
  /* SIM_SOPT1: OSC32KSEL=0 */
  SIM->SOPT1 &= (uint32_t)~0x00080000UL; /* System oscillator drives 32 kHz clock for various peripherals */
  /* SIM_SCGC1: OSC1=1 */
  SIM->SCGC1 |= (uint32_t)0x20UL;
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA->PCR[18] &= (uint32_t)~0x01000700UL;
  /* Switch to FBE Mode */
  /* OSC0_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC0->CR = (uint8_t)0x80U;
  /* OSC1_CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=0,SC4P=0,SC8P=0,SC16P=0 */
  OSC1->CR = (uint8_t)0x80U;
  /* MCG_C7: OSCSEL=0 */
  MCG->C7 &= (uint8_t)~(uint8_t)0x01U;
  /* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=0,LP=0,IRCS=0 */
  MCG->C2 = (uint8_t)0x20U;
  /* MCG_C1: CLKS=2,FRDIV=5,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
  MCG->C1 = (uint8_t)0xAAU;
  /* MCG_C4: DMX32=0,DRST_DRS=0 */
  MCG->C4 &= (uint8_t)~(uint8_t)0xE0U;
  /* MCG_C5: PLLREFSEL0=0,PLLCLKEN0=0,PLLSTEN0=0,??=0,??=0,PRDIV0=0 */
  MCG->C5 = (uint8_t)0x00U;
  /* MCG_C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
  MCG->C6 = (uint8_t)0x00U;
  /* MCG_C11: PLLREFSEL1=0,PLLCLKEN1=0,PLLSTEN1=0,PLLCS=0,??=0,PRDIV1=0 */
  MCG->C11 = (uint8_t)0x00U;
  /* MCG_C12: LOLIE1=0,??=0,CME2=0,VDIV1=0 */
  MCG->C12 = (uint8_t)0x00U;
  while((MCG->S & MCG_S_IREFST_MASK) != 0x00U) { /* Check that the source of the FLL reference clock is the external reference clock. */
  }
  while((MCG->S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
  /* Switch to BLPE Mode */
  /* MCG_C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=0,LP=1,IRCS=0 */
  MCG->C2 = (uint8_t)0x22U;
  while((MCG->S & 0x0CU) != 0x08U) {    /* Wait until external reference clock is selected as MCG output */
  }
#endif /* (CLOCK_SETUP == 2) */

  /* Disable MPU */
  MPU->CESR &= ~MPU_CESR_VLD_MASK;
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {
  uint32_t MCGOUTClock;                                                        /* Variable to store output clock frequency of the MCG module */
  uint8_t Divider;

  if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x0u) {
    /* Output of FLL or PLL is selected */
    if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u) {
      /* FLL is selected */
      if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u) {
        /* External reference clock is selected */
        if ((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u) {
          MCGOUTClock = CPU_XTAL0_CLK_HZ;                                       /* System oscillator 0 drives MCG clock */
        } else { /* (!((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u)) */
          MCGOUTClock = CPU_XTAL32k_CLK_HZ;                                    /* RTC 32 kHz oscillator drives MCG clock */
        } /* (!((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u)) */
        Divider = (uint8_t)(1u << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
        MCGOUTClock = (MCGOUTClock / Divider);  /* Calculate the divided FLL reference clock */
        if ((MCG->C2 & MCG_C2_RANGE0_MASK) != 0x0u) {
          MCGOUTClock /= 32u;                                                  /* If high range is enabled, additional 32 divider is active */
        } /* ((MCG->C2 & MCG_C2_RANGE0_MASK) != 0x0u) */
      } else { /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u)) */
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                     /* The slow internal reference clock is selected */
      } /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u)) */
      /* Select correct multiplier to calculate the MCG output clock  */
      switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
        case 0x0u:
          MCGOUTClock *= 640u;
          break;
        case 0x20u:
          MCGOUTClock *= 1280u;
          break;
        case 0x40u:
          MCGOUTClock *= 1920u;
          break;
        case 0x60u:
          MCGOUTClock *= 2560u;
          break;
        case 0x80u:
          MCGOUTClock *= 732u;
          break;
        case 0xA0u:
          MCGOUTClock *= 1464u;
          break;
        case 0xC0u:
          MCGOUTClock *= 2197u;
          break;
        case 0xE0u:
          MCGOUTClock *= 2929u;
          break;
        default:
          break;
      }
    } else { /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u)) */
      /* PLL is selected */
      if ((MCG->C11 & MCG_C11_PLLCS_MASK) != 0x0u) {
        /* PLL1 output is selected */
        if ((MCG->C11 & MCG_C11_PLLREFSEL1_MASK) != 0x0u) {
          /* OSC1 clock source used as an external reference clock */
          MCGOUTClock = CPU_XTAL1_CLK_HZ;
        } else { /* (!((MCG->C11 & MCG_C11_PLLREFSEL1_MASK) != 0x0u)) */
          /* OSC0 clock source used as an external reference clock */
          MCGOUTClock = CPU_XTAL0_CLK_HZ;
        } /* (!((MCG->C11 & MCG_C11_PLLREFSEL1_MASK) != 0x0u)) */
        Divider = (1u + (MCG->C11 & MCG_C11_PRDIV1_MASK));
        MCGOUTClock /= Divider;                                                  /* Calculate the PLL reference clock */
        Divider = ((MCG->C12 & MCG_C12_VDIV1_MASK) + 16u);
        MCGOUTClock = (MCGOUTClock * Divider) / 2u;                              /* Calculate the MCG output clock */
      } else { /* (!((MCG->C11 & MCG_C11_PLLCS_MASK) != 0x0u)) */
        /* PLL0 output is selected */
        if ((MCG->C5 & MCG_C5_PLLREFSEL0_MASK) != 0x0u) {
          /* OSC1 clock source used as an external reference clock */
          MCGOUTClock = CPU_XTAL1_CLK_HZ;
        } else { /* (!((MCG->C5 & MCG_C5_PLLREFSEL0_MASK) != 0x0u)) */
          /* OSC0 clock source used as an external reference clock */
          MCGOUTClock = CPU_XTAL0_CLK_HZ;
        } /* (!((MCG->C5 & MCG_C5_PLLREFSEL0_MASK) != 0x0u)) */
        Divider = (1u + (MCG->C5 & MCG_C5_PRDIV0_MASK));
        MCGOUTClock /= Divider;                                                  /* Calculate the PLL reference clock */
        Divider = ((MCG->C6 & MCG_C6_VDIV0_MASK) + 16u);
        MCGOUTClock = (MCGOUTClock * Divider) / 2u;                              /* Calculate the MCG output clock */
      } /* (!((MCG->C11 & MCG_C11_PLLCS_MASK) != 0x0u)) */
    } /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40u) {
    /* Internal reference clock is selected */
    if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u) {
      MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                       /* Slow internal reference clock selected */
    } else { /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u)) */
      MCGOUTClock = CPU_INT_FAST_CLK_HZ / (1 << ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT));  /* Fast internal reference clock selected */
    } /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u) {
    /* External reference clock is selected */
    if ((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u) {
      MCGOUTClock = CPU_XTAL0_CLK_HZ;                                           /* System oscillator drives MCG clock */
    } else { /* (!((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u)) */
      MCGOUTClock = CPU_XTAL32k_CLK_HZ;                                        /* RTC 32 kHz oscillator drives MCG clock */
    } /* (!((MCG->C7 & MCG_C7_OSCSEL_MASK) == 0x0u)) */
  } else { /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
    /* Reserved value */
    return;
  } /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
  SystemCoreClock = (MCGOUTClock / (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));
}
