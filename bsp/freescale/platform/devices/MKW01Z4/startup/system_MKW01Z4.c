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
 * @brief Device specific configuration file for MKW01Z4 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"


/* ----------------------------------------------------------------------------
   -- ExtClk_Setup_HookUp()
   ---------------------------------------------------------------------------- */

#pragma weak ExtClk_Setup_HookUp
uint8_t ExtClk_Setup_HookUp(uint32_t clk_out_value) {
  uint8_t result = 0;
  switch (clk_out_value) {
  case 937500U:
  case 1000000U:
    /* No initialization, modem is in the default state */
    result =  1U;  /*  The output was set successfully */
    break;
#if defined(SYSTEM_MODEM_CLK_OUT_CTRL_VALUE)
  case 1875000U:
  case 3750000U:
  case 7500000U:
  case 15000000U:
  case 30000000U:    /*  For the japanese version of the board with 30MHz external crystal */
  case 2000000U:
  case 4000000U:
  case 8000000U:
  case 16000000U:
  case 32000000U:    /*  For the european and american version of the board */
    SIM->SCGC5 |= (uint32_t)SIM_SCGC5_PORTE_MASK; /* PORTE clock gate enable */
    /* Modem RESET pin initialization (MCU PTE30) */
    /* GPIOE_PDDR: PDD|=0x40000000 */
    GPIOE->PDDR |= GPIO_PDDR_PDD(0x40000000); /* Set PTE30 as output */
    /* Set PTE30 as GPIO */
    /* PORTE_PCR30: ISF=0,MUX=1 */
    PORTE_PCR30 = (uint32_t)((PORTE_PCR30 & (uint32_t)~(uint32_t)(
                   PORT_PCR_ISF_MASK |
                   PORT_PCR_MUX(0x06)
                  )) | (uint32_t)(
                   PORT_PCR_MUX(0x01)
                  ));
    /* GPIOE_PSOR: PTSO=0x40000000 */
    GPIOE->PSOR = GPIO_PSOR_PTSO(0x40000000); /* Set PTE30 output to 1 */
    
    /* Use LPTMR to wait for >100us */
    MCG->C1 |= MCG_C1_IRCLKEN_MASK;
    SIM->SCGC5 |= SIM_SCGC5_LPTMR_MASK;  /* Allow software control of LPMTR */
    LPTMR0->CMR = LPTMR_CMR_COMPARE(2);  /* number of MCGIRCLK ticks */
    LPTMR0->CSR = (LPTMR_CSR_TCF_MASK | LPTMR_CSR_TPS(0x00));
    LPTMR0->PSR = (LPTMR_PSR_PCS(0x00) | LPTMR_PSR_PBYP_MASK); /* Clock source: MCGIRCLK, Prescaler bypass enable */
    LPTMR0->CSR = LPTMR_CSR_TEN_MASK;    /* LPMTR enable */
    while((LPTMR0->CSR & LPTMR_CSR_TCF_MASK) == 0u) {
    }
    LPTMR0->CSR = 0x00;                  /* Disable LPTMR */
    
    /* Release RESET pin */
    /* GPIOE_PCOR: PTCO=0x40000000 */
    GPIOE->PCOR = GPIO_PCOR_PTCO(0x40000000); /* Set PTE30 output to 0 */
    
    /* Use LPTMR to wait for 5ms */
    LPTMR0->CMR = LPTMR_CMR_COMPARE(165);  /* number of MCGIRCLK ticks */
    LPTMR0->CSR = (LPTMR_CSR_TCF_MASK | LPTMR_CSR_TPS(0x00));
    LPTMR0->CSR = LPTMR_CSR_TEN_MASK;    /* LPMTR enable */
    while((LPTMR0->CSR & LPTMR_CSR_TCF_MASK) == 0u) {
    }
    LPTMR0->CSR = 0x00;                  /* Disable LPTMR */
    SIM->SCGC5 &= (uint32_t)~(uint32_t)SIM_SCGC5_LPTMR_MASK;
    SIM->SCGC5 &= (uint32_t)~(uint32_t)SIM_SCGC5_PORTE_MASK;
    MCG->C1 &= ~MCG_C1_IRCLKEN_MASK;
        
    /* Check clock on CLKOUT pin  */
    SIM->SCGC5 |= (uint32_t)SIM_SCGC5_PORTA_MASK;
    PORTA_PCR18 = (uint32_t)((PORTA_PCR18 & (uint32_t)~(uint32_t)(
                   PORT_PCR_ISF_MASK |
                   PORT_PCR_MUX(0x06)
                  )) | (uint32_t)(
                   PORT_PCR_MUX(0x01)
                  ));
    while((GPIOA->PDIR & 0x40000) == 0u) {}
    SIM->SCGC5 &= (uint32_t)~(uint32_t)SIM_SCGC5_PORTA_MASK;
    
    /* Initialize SPI0 interface for communication with modem */
    /* SIM_SCGC5: PORTD=1,PORTC=1 */
    SIM->SCGC5 |= (SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTC_MASK); /* PORTC and PORTD clock gate enable */
    SIM->SCGC4 |= (uint32_t)SIM_SCGC4_SPI0_MASK; /* SPI0 clock gate enable */
    /* Pin routing of modem interface */
    /* Modem MOSI pin routing */
    /* PORTC_PCR6: ISF=0,MUX=2 */
    PORTC_PCR6 = (uint32_t)((PORTC_PCR6 & (uint32_t)~(uint32_t)(
                  PORT_PCR_ISF_MASK |
                  PORT_PCR_MUX(0x05)
                 )) | (uint32_t)(
                  PORT_PCR_MUX(0x02)
                 ));
    /* Modem MISO pin routing */
    /* PORTC_PCR7: ISF=0,MUX=2 */
    PORTC_PCR7 = (uint32_t)((PORTC_PCR7 & (uint32_t)~(uint32_t)(
                  PORT_PCR_ISF_MASK |
                  PORT_PCR_MUX(0x05)
                 )) | (uint32_t)(
                  PORT_PCR_MUX(0x02)
                 ));
    /* Modem SCLK pin routing */
    /* PORTC_PCR5: ISF=0,MUX=2 */
    PORTC_PCR5 = (uint32_t)((PORTC_PCR5 & (uint32_t)~(uint32_t)(
                  PORT_PCR_ISF_MASK |
                  PORT_PCR_MUX(0x05)
                 )) | (uint32_t)(
                  PORT_PCR_MUX(0x02)
                 ));
    /* Modem CS0 pin routing */
    /* PORTD_PCR0: ISF=0,MUX=2 */
    PORTD_PCR0 = (uint32_t)((PORTD_PCR0 & (uint32_t)~(uint32_t)(
                  PORT_PCR_ISF_MASK |
                  PORT_PCR_MUX(0x05)
                 )) | (uint32_t)(
                  PORT_PCR_MUX(0x02)
                 ));
    /* Initialize SPI0 */
    /* SPI0_BR: SPPR=0,SPR=1 */
    SPI0->BR = (SPI_BR_SPPR(0x00) | SPI_BR_SPR(0x01)); /* Configure SPI baud rate to 5.24288 MHz */
    /* SPI0_C2: SPMIE=0,SPIMODE=1,TXDMAE=0,MODFEN=1,BIDIROE=0,RXDMAE=0,SPISWAI=0,SPC0=0 */
    SPI0->C2 = (SPI_C2_SPIMODE_MASK | SPI_C2_MODFEN_MASK);
    /* SPI0_C1: SPIE=0,SPE=1,SPTIE=0,MSTR=1,CPOL=0,CPHA=0,SSOE=1,LSBFE=0 */
    SPI0->C1 = (SPI_C1_SPE_MASK | SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK); /* Enable SPI as master with slave select pin used */
    /* Set Modem_CLK_OUT_CTRL register */
    while ((SPI0_S & SPI_S_SPTEF_MASK) == 0U) {} /* Wait until send data operation is available */
    SPI0->DH = SYSTEM_MODEM_CLK_OUT_CTRL_ADDRESS; /* Set CLK_OUT_CTRL register address */
    SPI0->DL = SYSTEM_MODEM_CLK_OUT_CTRL_VALUE; /* Set CLK_OUT_CTRL register value */
    while ((SPI0_S & SPI_S_SPRF_MASK) == 0U) {} /* Wait until data from slave are received confirming data transfer finished */
    /* SPI is returned back to its initialization state  */
    /* SPI0_C1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=1,SSOE=0,LSBFE=0 */
    SPI0->C1 = SPI_C1_CPHA_MASK;
    /* SPI0_C2: SPMIE=0,SPIMODE=0,TXDMAE=0,MODFEN=0,BIDIROE=0,RXDMAE=0,SPISWAI=0,SPC0=0 */
    SPI0->C2 = 0x00U;
    /* SPI0_BR: SPPR=0,SPR=0 */
    SPI0->BR = (SPI_BR_SPPR(0x00) | SPI_BR_SPR(0x00));
    SIM->SCGC4 &= (uint32_t)~(uint32_t)SIM_SCGC4_SPI0_MASK; /* SPI0 clock gate disable */
    SIM->SCGC5 &= (uint32_t)~(uint32_t)SIM_SCGC5_PORTC_MASK;
    SIM->SCGC5 &= (uint32_t)~(uint32_t)SIM_SCGC5_PORTD_MASK;
    result = 1U;  /*  The output was set successfully */
    break;
#endif
  case 0U:
    /* No initialization, modem remains in the reset state */
    result = 1U;  /*  The output was set successfully */
    break;
  default:
    result = 0U; /* Requested value cannot be set */
    break;
  }
  return result;
}


/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {

#if (ACK_ISOLATION)
  if(PMC->REGSC &  PMC_REGSC_ACKISO_MASK) {
    PMC->REGSC |= PMC_REGSC_ACKISO_MASK; /* VLLSx recovery */
  }
#endif

#if (DISABLE_WDOG)
  /* SIM_COPC: COPT=0,COPCLKS=0,COPW=0 */
  SIM->COPC = (uint32_t)0x00u;
#endif /* (DISABLE_WDOG) */

#ifdef CLOCK_SETUP
  /* RTC_CLKIN route */
#if (RTC_CLKIN_USED)
  /* SIM_SCGC5: PORTC=1 */
  SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
  /* PORTC_PCR1: ISF=0,MUX=1 */
  PORTC->PCR[1] = (uint32_t)((PORTC->PCR[1] & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x06)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x01)
               ));
#endif /* (RTC_CLKIN_USED) */

  /* Wake-up from VLLSx? */
  if((RCM->SRS0 & RCM_SRS0_WAKEUP_MASK) != 0x00U)
  {
    /* VLLSx recovery */
    if((PMC->REGSC & PMC_REGSC_ACKISO_MASK) != 0x00U)
    {
       PMC->REGSC |= PMC_REGSC_ACKISO_MASK; /* Release hold with ACKISO: Only has an effect if recovering from VLLSx.*/
    }
  }

#if defined(SYSTEM_EXTCLK_INIT)
  /* Perform initialization of the wirelless modem clock output */
  if (ExtClk_Setup_HookUp (SYSTEM_EXTCLK_INIT) != 1U) {
    /* If the initialization was not sucesfull, do not continue with clock setup */
    return;
  }
#endif

  /* Power mode protection initialization */
#ifdef SYSTEM_SMC_PMPROT_VALUE
  SMC->PMPROT = SYSTEM_SMC_PMPROT_VALUE;
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
  SIM->CLKDIV1 = SYSTEM_SIM_CLKDIV1_VALUE;    /* Set system prescalers */
  SIM->SOPT1 = ((SIM->SOPT1) & (uint32_t)(~(SIM_SOPT1_OSC32KSEL_MASK))) | ((SYSTEM_SIM_SOPT1_VALUE) & (SIM_SOPT1_OSC32KSEL_MASK)); /* Set 32 kHz clock source (ERCLK32K) */
  SIM->SOPT2 = ((SIM->SOPT2) & (uint32_t)(~(
                 SIM_SOPT2_TPMSRC_MASK |
                 SIM_SOPT2_UART0SRC_MASK |
                 SIM_SOPT2_PLLFLLSEL_MASK
                 ))) | ((SYSTEM_SIM_SOPT2_VALUE) & (
                 SIM_SOPT2_TPMSRC_MASK |
                 SIM_SOPT2_UART0SRC_MASK |
                 SIM_SOPT2_PLLFLLSEL_MASK
                 ));   /* Select TPM, LPUARTs clock sources. */
#if ((MCG_MODE == MCG_MODE_FEI) || (MCG_MODE == MCG_MODE_FBI) || (MCG_MODE == MCG_MODE_BLPI))
  /* Set MCG and OSC */
#if  ((((SYSTEM_OSC0_CR_VALUE) & OSC_CR_ERCLKEN_MASK) != 0x00U) || (((SYSTEM_MCG_C5_VALUE) & MCG_C5_PLLCLKEN0_MASK) != 0x00U))
  /* SIM_SCGC5: PORTA=1 */
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA->PCR[18] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  if (((SYSTEM_MCG_C2_VALUE) & MCG_C2_EREFS0_MASK) != 0x00U) {
    /* PORTA_PCR19: ISF=0,MUX=0 */
    PORTA->PCR[19] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
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
  OSC0->CR = SYSTEM_OSC0_CR_VALUE;     /* Set OSC_CR (OSCERCLK enable, oscillator capacitor load) */

#else /* MCG_MODE */
  /* Set MCG and OSC */
  /* SIM_SCGC5: PORTA=1 */
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
  /* PORTA_PCR18: ISF=0,MUX=0 */
  PORTA->PCR[18] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  if (((SYSTEM_MCG_C2_VALUE) & MCG_C2_EREFS0_MASK) != 0x00U) {
    /* PORTA_PCR19: ISF=0,MUX=0 */
    PORTA->PCR[19] &= (uint32_t)~(uint32_t)((PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x07)));
  }
  MCG->SC = SYSTEM_MCG_SC_VALUE;       /* Set SC (fast clock internal reference divider) */
  MCG->C2 = (MCG->C2 & (uint8_t)(~(MCG_C2_FCFTRIM_MASK))) | (SYSTEM_MCG_C2_VALUE & (uint8_t)(~(MCG_C2_LP_MASK))); /* Set C2 (freq. range, ext. and int. reference selection etc. excluding trim bits; low power bit is set later) */
  OSC0->CR = SYSTEM_OSC0_CR_VALUE;     /* Set OSC_CR (OSCERCLK enable, oscillator capacitor load) */
  #if (MCG_MODE == MCG_MODE_PEE)
  MCG->C1 = (SYSTEM_MCG_C1_VALUE) | MCG_C1_CLKS(0x02); /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) - PBE mode*/
  #else
  MCG->C1 = SYSTEM_MCG_C1_VALUE;       /* Set C1 (clock source selection, FLL ext. reference divider, int. reference enable etc.) */
  #endif
  if (((SYSTEM_MCG_C2_VALUE) & MCG_C2_EREFS0_MASK) != 0x00U) {
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
  MCG->C5 = (SYSTEM_MCG_C5_VALUE) & (uint8_t)(~(MCG_C5_PLLCLKEN0_MASK)); /* Set C5 (PLL settings, PLL reference divider etc.) */
  MCG->C6 = (SYSTEM_MCG_C6_VALUE) & (uint8_t)~(MCG_C6_PLLS_MASK); /* Set C6 (PLL select, VCO divider etc.) */
  if ((SYSTEM_MCG_C5_VALUE) & MCG_C5_PLLCLKEN0_MASK) {
    MCG->C5 |= MCG_C5_PLLCLKEN0_MASK;  /* PLL clock enable in mode other than PEE or PBE */
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

  /* PLL loss of lock interrupt request initialization */
  if (((SYSTEM_MCG_C6_VALUE) & MCG_C6_LOLIE0_MASK) != 0U) {
    NVIC_EnableIRQ(MCG_IRQn);          /* Enable PLL loss of lock interrupt request */
  }
#endif //#ifdef CLOCK_SETUP

}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

  uint32_t MCGOUTClock;                                                        /* Variable to store output clock frequency of the MCG module */
  uint16_t Divider;

  if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x00U) {
    /* Output of FLL or PLL is selected */
    if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x00U) {
      /* FLL is selected */
      if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x00U) {
        /* External reference clock is selected */
        MCGOUTClock = CPU_XTAL_CLK_HZ;                                       /* System oscillator drives MCG clock */
        if ((MCG->C2 & MCG_C2_RANGE0_MASK) != 0x00U) {
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
        MCGOUTClock = (MCGOUTClock / Divider);  /* Calculate the divided FLL reference clock */
      } else { /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x00U)) */
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                     /* The slow internal reference clock is selected */
      } /* (!((MCG->C1 & MCG_C1_IREFS_MASK) == 0x00U)) */
      /* Select correct multiplier to calculate the MCG output clock  */
      switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
        case 0x00U:
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
    } else { /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x00U)) */
      /* PLL is selected */
      Divider = (((uint16_t)MCG->C5 & MCG_C5_PRDIV0_MASK) + 0x01U);
      MCGOUTClock = (uint32_t)(CPU_XTAL_CLK_HZ / Divider);                     /* Calculate the PLL reference clock */
      Divider = (((uint16_t)MCG->C6 & MCG_C6_VDIV0_MASK) + 24U);
      MCGOUTClock *= Divider;                       /* Calculate the MCG output clock */
    } /* (!((MCG->C6 & MCG_C6_PLLS_MASK) == 0x00U)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40u) {
    /* Internal reference clock is selected */
    if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x00U) {
      MCGOUTClock = CPU_INT_SLOW_CLK_HZ;                                       /* Slow internal reference clock selected */
    } else { /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x00U)) */
      Divider = (uint16_t)(0x01LU << ((MCG->SC & MCG_SC_FCRDIV_MASK) >> MCG_SC_FCRDIV_SHIFT));
      MCGOUTClock = (uint32_t) (CPU_INT_FAST_CLK_HZ / Divider); /* Fast internal reference clock selected */
    } /* (!((MCG->C2 & MCG_C2_IRCS_MASK) == 0x00U)) */
  } else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u) {
    /* External reference clock is selected */
    MCGOUTClock = CPU_XTAL_CLK_HZ;                                           /* System oscillator drives MCG clock */
  } else { /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
    /* Reserved value */
    return;
  } /* (!((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u)) */
  SystemCoreClock = (MCGOUTClock / (0x01U + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));

}
