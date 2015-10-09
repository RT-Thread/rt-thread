/*
** ###################################################################
**     Processors:          MK80FN256CAx15
**                          MK80FN256VDC15
**                          MK80FN256VLL15
**                          MK80FN256VLQ15
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          GNU C Compiler - CodeSourcery Sourcery G++
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    K80P121M150SF5RM, Rev. 2, May 2015
**     Version:             rev. 2.1, 2015-05-28
**     Build:               b150626
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
**     - rev. 1.0 (2014-07-30)
**         Initial version
**     - rev. 1.1 (2014-08-28)
**         Update of startup files - possibility to override DefaultISR added.
**     - rev. 1.2 (2014-11-07)
**         Update according to the new version of reference manual Rev. 1 Draft A.
**     - rev. 2.0 (2015-04-01)
**         Update according to the new version of reference manual Rev. 1.
**     - rev. 2.1 (2015-05-28)
**         Update according to the reference manual Rev. 2.
**
** ###################################################################
*/

/*!
 * @file MK80F25615
 * @version 2.1
 * @date 2015-05-28
 * @brief Device specific configuration file for MK80F25615 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"



/*!
 * @brief Defines the structure to set the Bootloader Configuration Area
 *
 * This type of variable is used to set the Bootloader Configuration Area
 * of the chip.
 */
typedef struct SystemBootloaderConfig
{
  uint32_t      tag;                /*!< Magic number to verify bootloader configuration is valid. Must be set to 'kcfg'. */
  uint32_t      crcStartAddress;    /*!< Start address for application image CRC check. If the bits are all set then Kinetis bootloader by default will not perform any CRC check. */
  uint32_t      crcByteCount;       /*!< Byte count for application image CRC check. If the bits are all set then Kinetis bootloader by default will not prform any CRC check. */
  uint32_t      crcExpectedValue;   /*!< Expected CRC value for application CRC check. If the bits are all set then Kinetis bootloader by default will not perform any CRC check.*/
  uint8_t       enabledPeripherals; /*!< Bitfield of peripherals to enable.
                                         bit 0 - LPUART, bit 1 - I2C, bit 2 - SPI, bit 4 - USB
                                         Kinetis bootloader will enable the peripheral if corresponding bit is set to 1. */
  uint8_t       i2cSlaveAddress;    /*!< If not 0xFF, used as the 7-bit I2C slave address. If 0xFF, defaults to 0x10 for I2C slave address */
  uint16_t      peripheralDetectionTimeoutMs; /*!< Timeout in milliseconds for active peripheral detection. If 0xFFFF, defaults to 5 seconds. */
  uint16_t      usbVid;             /*!< Sets the USB Vendor ID reported by the device during enumeration. If 0xFFFF, it defaults to 0x15A2. */
  uint16_t      usbPid;             /*!< Sets the USB Product ID reported by the device during enumeration. */
  uint32_t      usbStringsPointer;  /*!< Sets the USB Strings reported by the device during enumeration. */
  uint8_t       clockFlags;         /*!< The flags in the clockFlags configuration field are enabled if the corresponding bit is cleared (0).
	                                       bit 0 - HighSpeed Enable high speed mode (i.e., 48 MHz).	*/
  uint8_t       clockDivider;       /*!< Inverted value of the divider to use for core and bus clocks when in high speed mode */
  uint8_t       bootFlags;          /*!< If bit 0 is cleared, then Kinetis bootloader will jump to either Quad SPI Flash or internal flash image depending on FOPT BOOTSRC_SEL bits.
	                                       If the bit is set, then Kinetis bootloader will prepare for host communication over serial peripherals. */
  uint8_t       RESERVED1;
  uint32_t      mmcauConfigPointer; /*!< A pointer to the MMCAU configuration structure in memory. */
  uint8_t       RESERVED2[12];
  uint32_t      qspiConfigBlockPtr; /*!< A pointer to the QSPI config block in internal flash array. */
  uint8_t       RESERVED3[12];
} system_bootloader_config_t;

#ifdef BOOTLOADER_CONFIG
/* Bootlader configuration area */
  #if defined(__IAR_SYSTEMS_ICC__)
/* Pragma to place the Bootloader Configuration Array on correct location defined in linker file. */
#pragma language=extended
#pragma location = "BootloaderConfig"
__root const system_bootloader_config_t BootloaderConfig @ "BootloaderConfig" =
  #elif defined(__GNUC__)
__attribute__ ((section (".BootloaderConfig"))) const system_bootloader_config_t BootloaderConfig =
  #elif defined(__CC_ARM)
__attribute__ ((section ("BootloaderConfig"))) const system_bootloader_config_t BootloaderConfig __attribute__((used)) =
  #else
    #error Unsupported compiler!
  #endif
{
    .tag                        = 0x6766636BU, /* Magic Number */
    .crcStartAddress            = 0xFFFFFFFFU, /* Disable CRC check */
    .crcByteCount               = 0xFFFFFFFFU, /* Disable CRC check */
    .crcExpectedValue           = 0xFFFFFFFFU, /* Disable CRC check */
    .enabledPeripherals         = 0x17,        /* Enable all peripherals */
    .i2cSlaveAddress            = 0xFF,        /* Use default I2C address */
    .peripheralDetectionTimeoutMs = 0xFFFFU,   /* Use default timeout */
    .usbVid                     = 0xFFFFU,     /* Use default USB Vendor ID */
    .usbPid                     = 0xFFFFU,     /* Use default USB Product ID */
    .usbStringsPointer          = 0xFFFFFFFFU, /* Use default USB Strings */
    .clockFlags                 = 0x01,        /* Enable High speed mode */
    .clockDivider               = 0xFF,        /* Use clock divider 1 */
    .bootFlags                  = 0x01,        /* Enable communication with host */
    .mmcauConfigPointer         = 0xFFFFFFFFU, /* No MMCAU configuration */
    .qspiConfigBlockPtr         = 0xFFFFFFFFU  /* No QSPI configuration */
};
#endif



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
  /* WDOG->UNLOCK: WDOGUNLOCK=0xC520 */
  WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xC520); /* Key 1 */
  /* WDOG->UNLOCK: WDOGUNLOCK=0xD928 */
  WDOG->UNLOCK = WDOG_UNLOCK_WDOGUNLOCK(0xD928); /* Key 2 */
  /* WDOG->STCTRLH: ?=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,?=0,?=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 */
  WDOG->STCTRLH = WDOG_STCTRLH_BYTESEL(0x00) |
                 WDOG_STCTRLH_WAITEN_MASK |
                 WDOG_STCTRLH_STOPEN_MASK |
                 WDOG_STCTRLH_ALLOWUPDATE_MASK |
                 WDOG_STCTRLH_CLKSRC_MASK |
                 0x0100U;
#endif /* (DISABLE_WDOG) */
#ifdef CLOCK_SETUP
  if((RCM->SRS0 & RCM_SRS0_WAKEUP_MASK) != 0x00U)
  {
    /* VLLSx recovery */
    if((PMC->REGSC & PMC_REGSC_ACKISO_MASK) != 0x00U)
    {
       PMC->REGSC |= PMC_REGSC_ACKISO_MASK; /* Release hold with ACKISO: Only has an effect if recovering from VLLSx.*/
    }
  } else {
    /* RTC initialization */
#ifdef SYSTEM_RTC_CR_VALUE
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
    if ((RTC->CR & RTC_CR_OSCE_MASK) == 0x00U) { /* Only if the OSCILLATOR is not already enabled */
      RTC->CR = (uint32_t)((RTC->CR & (uint32_t)~(uint32_t)(RTC_CR_SC2P_MASK | RTC_CR_SC4P_MASK | RTC_CR_SC8P_MASK | RTC_CR_SC16P_MASK)) | (uint32_t)SYSTEM_RTC_CR_VALUE);
      RTC->CR |= (uint32_t)RTC_CR_OSCE_MASK;
      RTC->CR &= (uint32_t)~(uint32_t)RTC_CR_CLKO_MASK;
    }
#endif
  }

  /* Power mode protection initialization */
#ifdef SYSTEM_SMC_PMPROT_VALUE
  SMC->PMPROT = SYSTEM_SMC_PMPROT_VALUE;
#endif

  /* High speed run mode enable */
#if (((SYSTEM_SMC_PMCTRL_VALUE) & SMC_PMCTRL_RUNM_MASK) == (0x03U << SMC_PMCTRL_RUNM_SHIFT))
  SMC->PMCTRL = (uint8_t)((SYSTEM_SMC_PMCTRL_VALUE) & (SMC_PMCTRL_RUNM_MASK)); /* Enable HSRUN mode */
  while(SMC->PMSTAT != 0x80U) {        /* Wait until the system is in HSRUN mode */
  }
#endif
  /* System clock initialization */
  /* Internal reference clock trim initialization */
#if defined(SLOW_TRIM_ADDRESS)
  if ( *((uint8_t*)SLOW_TRIM_ADDRESS) != 0xFFU) {                              /* Skip if non-volatile flash memory is erased */
    MCG->C3 = *((uint8_t*)SLOW_TRIM_ADDRESS);
#endif /* defined(SLOW_TRIM_ADDRESS) */
#if defined(SLOW_FINE_TRIM_ADDRESS)
    MCG->C4 = (MCG->C4 & ~(MCG_C4_SCFTRIM_MASK)) | ((*((uint8_t*) SLOW_FINE_TRIM_ADDRESS)) & MCG_C4_SCFTRIM_MASK);
#endif
#if defined(FAST_TRIM_ADDRESS)
    MCG->C4 = (MCG->C4 & ~(MCG_C4_FCTRIM_MASK)) |((*((uint8_t*) FAST_TRIM_ADDRESS)) & MCG_C4_FCTRIM_MASK);
#endif
#if defined(FAST_FINE_TRIM_ADDRESS)
    MCG->C2 = (MCG->C2 & ~(MCG_C2_FCFTRIM_MASK)) | ((*((uint8_t*)FAST_TRIM_ADDRESS)) & MCG_C2_FCFTRIM_MASK);
#endif /* defined(FAST_FINE_TRIM_ADDRESS) */
#if defined(SLOW_TRIM_ADDRESS)
  }
#endif /* defined(SLOW_TRIM_ADDRESS) */

  /* Set system prescalers and clock sources */
  SIM->CLKDIV1 = SYSTEM_SIM_CLKDIV1_VALUE; /* Set system prescalers */
  SIM->SOPT1 = ((SIM->SOPT1) & (uint32_t)(~(SIM_SOPT1_OSC32KSEL_MASK))) | ((SYSTEM_SIM_SOPT1_VALUE) & (SIM_SOPT1_OSC32KSEL_MASK)); /* Set 32 kHz clock source (ERCLK32K) */
  SIM->SOPT2 = ((SIM->SOPT2) & (uint32_t)(~(SIM_SOPT2_PLLFLLSEL_MASK))) | ((SYSTEM_SIM_SOPT2_VALUE) & (SIM_SOPT2_PLLFLLSEL_MASK)); /* Selects the high frequency clock for various peripheral clocking options. */
  SIM->SOPT2 = ((SIM->SOPT2) & (uint32_t)(~(SIM_SOPT2_TPMSRC_MASK))) | ((SYSTEM_SIM_SOPT2_VALUE) & (SIM_SOPT2_TPMSRC_MASK)); /* Selects the clock source for the TPM counter clock. */
#if ((MCG_MODE == MCG_MODE_FEI) || (MCG_MODE == MCG_MODE_FBI) || (MCG_MODE == MCG_MODE_BLPI))
  /* Set MCG and OSC */
#if  ((((SYSTEM_OSC_CR_VALUE) & OSC_CR_ERCLKEN_MASK) != 0x00U) || ((((SYSTEM_MCG_C5_VALUE) & MCG_C5_PLLCLKEN_MASK) != 0x00U) && (((SYSTEM_MCG_C7_VALUE) & MCG_C7_OSCSEL_MASK) == 0x00U)))
  /* SIM_SCGC5: PORTA=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA_PCR18 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  if (((SYSTEM_MCG_C2_VALUE) & MCG_C2_EREFS_MASK) != 0x00U) {
  /* PORTA_PCR19: ISF=0,MUX=0 */
  PORTA_PCR19 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  }
#endif
  MCG->SC = SYSTEM_MCG_SC_VALUE;       /* Set SC (fast clock internal reference divider) */
  MCG->C1 = SYSTEM_MCG_C1_VALUE;       /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
  /* Check that the source of the FLL reference clock is the requested one. */
  if (((SYSTEM_MCG_C1_VALUE) & MCG_C1_IREFS_MASK) != 0x00U) {
    while((MCG->S & MCG_S_IREFST_MASK) == 0x00U) {
    }
  } else {
    while((MCG->S & MCG_S_IREFST_MASK) != 0x00U) {
    }
  }
  MCG->C2 = (MCG->C2 & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (SYSTEM_MCG_C2_VALUE & (uint8_t)(~(MCG_C2_LP_MASK))); /* Set C2 (freq. range, ext. and int. reference selection etc. excluding trim bits; low power bit is set later) */
  MCG->C4 = ((SYSTEM_MCG_C4_VALUE) & (uint8_t)(~(MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK))) | (MCG->C4 & (MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK)); /* Set C4 (FLL output; trim values not changed) */
  OSC->CR = SYSTEM_OSC_CR_VALUE;       /* Set OSC_CR (OSCERCLK enable, oscillator capacitor load) */
  MCG->C7 = SYSTEM_MCG_C7_VALUE;       /* Set C7 (OSC Clock Select) */

#else /* MCG_MODE */
  /* Set MCG and OSC */
#if  (((SYSTEM_OSC_CR_VALUE) & OSC_CR_ERCLKEN_MASK) != 0x00U) || (((SYSTEM_MCG_C7_VALUE) & MCG_C7_OSCSEL_MASK) == 0x00U)
  /* SIM_SCGC5: PORTA=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA_PCR18 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  if (((SYSTEM_MCG_C2_VALUE) & MCG_C2_EREFS_MASK) != 0x00U) {
  /* PORTA_PCR19: ISF=0,MUX=0 */
  PORTA_PCR19 &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  }
#endif
  MCG->SC = SYSTEM_MCG_SC_VALUE;       /* Set SC (fast clock internal reference divider) */
  MCG->C2 = (MCG->C2 & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (SYSTEM_MCG_C2_VALUE & (uint8_t)(~(MCG_C2_LP_MASK))); /* Set C2 (freq. range, ext. and int. reference selection etc. excluding trim bits; low power bit is set later) */
  OSC->CR = SYSTEM_OSC_CR_VALUE;       /* Set OSC_CR (OSCERCLK enable, oscillator capacitor load) */
  MCG->C7 = SYSTEM_MCG_C7_VALUE;       /* Set C7 (OSC Clock Select) */
  #if (MCG_MODE == MCG_MODE_PEE)
  MCG->C1 = (SYSTEM_MCG_C1_VALUE) | MCG_C1_CLKS(0x02); /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) - PBE mode*/
  #else
  MCG->C1 = SYSTEM_MCG_C1_VALUE;       /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
  #endif
  if ((((SYSTEM_MCG_C2_VALUE) & MCG_C2_EREFS_MASK) != 0x00U) && (((SYSTEM_MCG_C7_VALUE) & MCG_C7_OSCSEL_MASK) == 0x00U)) {
    while((MCG->S & MCG_S_OSCINIT0_MASK) == 0x00U) { /* Check that the oscillator is running */
    }
  }
  /* Check that the source of the FLL reference clock is the requested one. */
  if (((SYSTEM_MCG_C1_VALUE) & MCG_C1_IREFS_MASK) != 0x00U) {
    while((MCG->S & MCG_S_IREFST_MASK) == 0x00U) {
    }
  } else {
    while((MCG->S & MCG_S_IREFST_MASK) != 0x00U) {
    }
  }
  MCG->C4 = ((SYSTEM_MCG_C4_VALUE)  & (uint8_t)(~(MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK))) | (MCG->C4 & (MCG_C4_FCTRIM_MASK | MCG_C4_SCFTRIM_MASK)); /* Set C4 (FLL output; trim values not changed) */
#endif /* MCG_MODE */

  /* Common for all MCG modes */

  /* PLL clock can be used to generate clock for some devices regardless of clock generator (MCGOUTCLK) mode. */
  MCG->C5 = (SYSTEM_MCG_C5_VALUE) & (uint8_t)(~(MCG_C5_PLLCLKEN_MASK)); /* Set C5 (PLL settings, PLL reference divider etc.) */
  MCG->C6 = (SYSTEM_MCG_C6_VALUE) & (uint8_t)~(MCG_C6_PLLS_MASK); /* Set C6 (PLL select, VCO divider etc.) */
  if ((SYSTEM_MCG_C5_VALUE) & MCG_C5_PLLCLKEN_MASK) {
    MCG->C5 |= MCG_C5_PLLCLKEN_MASK;   /* PLL clock enable in mode other than PEE or PBE */
  }

  /* BLPI and BLPE MCG mode specific */
#if ((MCG_MODE == MCG_MODE_BLPI) || (MCG_MODE == MCG_MODE_BLPE))
  MCG->C2 |= (MCG_C2_LP_MASK);         /* Disable FLL and PLL in bypass mode */
  /* PEE and PBE MCG mode specific */
#elif ((MCG_MODE == MCG_MODE_PBE) || (MCG_MODE == MCG_MODE_PEE))
  MCG->C6 |= (MCG_C6_PLLS_MASK);       /* Set C6 (PLL select, VCO divider etc.) */
  while((MCG->S & MCG_S_LOCK0_MASK) == 0x00U) { /* Wait until PLL is locked*/
  }
  #if (MCG_MODE == MCG_MODE_PEE)
  MCG->C1 &= (uint8_t)~(MCG_C1_CLKS_MASK);
  #endif
#endif

  /* Clock mode status check */
#if ((MCG_MODE == MCG_MODE_FEI) || (MCG_MODE == MCG_MODE_FEE))
  while((MCG->S & MCG_S_CLKST_MASK) != 0x00U) { /* Wait until output of the FLL is selected */
  }
  /* Use LPTMR to wait for 1ms for FLL clock stabilization */
  SIM->SCGC5 |= SIM_SCGC5_LPTMR_MASK;  /* Allow software control of LPMTR */
  LPTMR0->CMR = LPTMR_CMR_COMPARE(0);  /* Default 1 LPO tick */
  LPTMR0->CSR = (LPTMR_CSR_TCF_MASK | LPTMR_CSR_TPS(0x00));
  LPTMR0->PSR = (LPTMR_PSR_PCS(0x01) | LPTMR_PSR_PBYP_MASK); /* Clock source: LPO, Prescaler bypass enable */
  LPTMR0->CSR = LPTMR_CSR_TEN_MASK;    /* LPMTR enable */
  while((LPTMR0->CSR & LPTMR_CSR_TCF_MASK) == 0u) {
  }
  LPTMR0->CSR = 0x00;                  /* Disable LPTMR */
  SIM->SCGC5 &= (uint32_t)~(uint32_t)SIM_SCGC5_LPTMR_MASK;
#elif ((MCG_MODE == MCG_MODE_FBI) || (MCG_MODE == MCG_MODE_BLPI))
  while((MCG->S & MCG_S_CLKST_MASK) != 0x04U) { /* Wait until internal reference clock is selected as MCG output */
  }
#elif ((MCG_MODE == MCG_MODE_FBE) || (MCG_MODE == MCG_MODE_PBE) || (MCG_MODE == MCG_MODE_BLPE))
  while((MCG->S & MCG_S_CLKST_MASK) != 0x08U) { /* Wait until external reference clock is selected as MCG output */
  }
#elif (MCG_MODE == MCG_MODE_PEE)
  while((MCG->S & MCG_S_CLKST_MASK) != 0x0CU) { /* Wait until output of the PLL is selected */
  }
#endif

  /* Very-low-power run mode enable */
#if (((SYSTEM_SMC_PMCTRL_VALUE) & SMC_PMCTRL_RUNM_MASK) == (0x02U << SMC_PMCTRL_RUNM_SHIFT))
  SMC->PMCTRL = (uint8_t)((SYSTEM_SMC_PMCTRL_VALUE) & (SMC_PMCTRL_RUNM_MASK)); /* Enable VLPR mode */
  while(SMC->PMSTAT != 0x04U) {        /* Wait until the system is in VLPR mode */
  }
#endif

#if defined(SYSTEM_SIM_CLKDIV2_VALUE)
  SIM->CLKDIV2 = ((SIM->CLKDIV2) & (uint32_t)(~(SIM_CLKDIV2_USBFRAC_MASK | SIM_CLKDIV2_USBDIV_MASK))) | ((SYSTEM_SIM_CLKDIV2_VALUE) & (SIM_CLKDIV2_USBFRAC_MASK | SIM_CLKDIV2_USBDIV_MASK)); /* Selects the USB clock divider. */
#endif
#if defined(SYSTEM_SIM_CLKDIV3_VALUE)
  SIM->CLKDIV3 = ((SIM->CLKDIV3) & (uint32_t)(~(SIM_CLKDIV3_PLLFLLFRAC_MASK | SIM_CLKDIV3_PLLFLLDIV_MASK))) | ((SYSTEM_SIM_CLKDIV3_VALUE) & (SIM_CLKDIV3_PLLFLLFRAC_MASK | SIM_CLKDIV3_PLLFLLDIV_MASK)); /* Selects the PLLFLL clock divider. */
#endif

  /* PLL loss of lock interrupt request initialization */
  if (((SYSTEM_MCG_C6_VALUE) & MCG_C6_LOLIE0_MASK) != 0U) {
    NVIC_EnableIRQ(MCG_IRQn);          /* Enable PLL loss of lock interrupt request */
  }
#endif
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

  uint32_t MCGOUTClock;                /* Variable to store output clock frequency of the MCG module */
  uint16_t Divider;

  if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x00U) {
    /* Output of FLL or PLL is selected */
    if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x00U) {
      /* FLL is selected */
      if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x00U) {
        /* External reference clock is selected */
        switch (MCG->C7 & MCG_C7_OSCSEL_MASK) {
        case 0x00U:
          MCGOUTClock = CPU_XTAL_CLK_HZ; /* System oscillator drives MCG clock */
          break;
        case 0x01U:
          MCGOUTClock = CPU_XTAL32k_CLK_HZ; /* RTC 32 kHz oscillator drives MCG clock */
          break;
        case 0x02U:
        default:
          MCGOUTClock = CPU_INT_IRC_CLK_HZ; /* IRC 48MHz oscillator drives MCG clock */
          break;
        }
        if (((MCG->C2 & MCG_C2_RANGE_MASK) != 0x00U) && ((MCG->C7 & MCG_C7_OSCSEL_MASK) != 0x01U)) {
          switch (MCG->C1 & MCG_C1_FRDIV_MASK) {
          case 0x38U:
            Divider = 1536U;
            break;
          case 0x30U:
            Divider = 1280U;
            break;
          default:
            Divider = (uint16_t)(32LU << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
            break;
          }
        } else {/* ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x00U) */
          Divider = (uint16_t)(1LU << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
        }
        MCGOUTClock = (MCGOUTClock / Divider); /* Calculate the divided FLL reference clock */
      } else { /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x00U)) */
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ; /* The slow internal reference clock is selected */
      } /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x00U)) */
      /* Select correct multiplier to calculate the MCG output clock  */
      switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
        case 0x00U:
          MCGOUTClock *= 640U;
          break;
        case 0x20U:
          MCGOUTClock *= 1280U;
          break;
        case 0x40U:
          MCGOUTClock *= 1920U;
          break;
        case 0x60U:
          MCGOUTClock *= 2560U;
          break;
        case 0x80U:
          MCGOUTClock *= 732U;
          break;
        case 0xA0U:
          MCGOUTClock *= 1464U;
          break;
        case 0xC0U:
          MCGOUTClock *= 2197U;
          break;
        case 0xE0U:
          MCGOUTClock *= 2929U;
          break;
        default:
          break;
      }
    } else { /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x00U)) */
      /* PLL is selected */
      Divider = (((uint16_t)MCG->C5 & MCG_C5_PRDIV_MASK) + 0x01U);
      MCGOUTClock = (uint32_t)(CPU_XTAL_CLK_HZ / Divider); /* Calculate the PLL reference clock */
      Divider = (((uint16_t)MCG->C6 & MCG_C6_VDIV_MASK) + 16U);
      MCGOUTClock *= Divider;          /* Calculate the VCO output clock */
      MCGOUTClock /= 2;                /* Calculate the MCG output clock */
    } /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x00U)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40U) {
    /* Internal reference clock is selected */
    if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x00U) {
      MCGOUTClock = CPU_INT_SLOW_CLK_HZ; /* Slow internal reference clock selected */
    } else { /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x00U)) */
      Divider = (uint16_t)(0x01LU << ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT));
      MCGOUTClock = (uint32_t) (CPU_INT_FAST_CLK_HZ / Divider); /* Fast internal reference clock selected */
    } /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x00U)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80U) {
    /* External reference clock is selected */
    switch (MCG->C7 & MCG_C7_OSCSEL_MASK) {
    case 0x00U:
      MCGOUTClock = CPU_XTAL_CLK_HZ;   /* System oscillator drives MCG clock */
      break;
    case 0x01U:
      MCGOUTClock = CPU_XTAL32k_CLK_HZ; /* RTC 32 kHz oscillator drives MCG clock */
      break;
    case 0x02U:
    default:
      MCGOUTClock = CPU_INT_IRC_CLK_HZ; /* IRC 48MHz oscillator drives MCG clock */
      break;
    }
  } else { /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80U)) */
    /* Reserved value */
    return;
  } /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80U)) */
  SystemCoreClock = (MCGOUTClock / (0x01U + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));
}
