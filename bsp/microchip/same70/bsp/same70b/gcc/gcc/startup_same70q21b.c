/**
 * \file
 *
 * \brief GCC startup file for ATSAME70Q21B
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \license_stop
 *
 */

#include "same70q21b.h"

/* Initialize segments */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;

/** \cond DOXYGEN_SHOULD_SKIP_THIS */
int main(void);
/** \endcond */

void __libc_init_array(void);

/* Reset handler */
void Reset_Handler(void);

/* Default empty handler */
void Dummy_Handler(void);

/* Cortex-M7 core handlers */
void NonMaskableInt_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void MemoryManagement_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SVCall_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void DebugMonitor_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Dummy_Handler")));

/* Peripherals handlers */
void SUPC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void RSTC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void RTC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void RTT_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void WDT_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PMC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void EFC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIOA_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIOB_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIOC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void USART0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void USART1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void USART2_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIOD_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PIOE_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void HSMCI_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TWIHS0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TWIHS1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SPI0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SSC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC2_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC3_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC4_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC5_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void AFEC0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void DACC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PWM0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void ICM_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void ACC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void USBHS_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void MCAN0_INT0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void MCAN0_INT1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void MCAN1_INT0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void MCAN1_INT1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void GMAC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void AFEC1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TWIHS2_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SPI1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void QSPI_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART2_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART3_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void UART4_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC6_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC7_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC8_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC9_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC10_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TC11_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void AES_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void TRNG_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void XDMAC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void ISI_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void PWM1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void FPU_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void SDRAMC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void RSWDT_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void CCW_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void CCF_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void GMAC_Q1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void GMAC_Q2_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void IXC_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2SC0_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void I2SC1_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void GMAC_Q3_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void GMAC_Q4_Handler(void) __attribute__((weak, alias("Dummy_Handler")));
void GMAC_Q5_Handler(void) __attribute__((weak, alias("Dummy_Handler")));

/* Exception Table */
__attribute__((section(".vectors"))) const DeviceVectors exception_table = {

    /* Configure Initial Stack Pointer, using linker-generated symbols */
    .pvStack = (void *)(&_estack),

    .pfnReset_Handler            = (void *)Reset_Handler,
    .pfnNonMaskableInt_Handler   = (void *)NonMaskableInt_Handler,
    .pfnHardFault_Handler        = (void *)HardFault_Handler,
    .pfnMemoryManagement_Handler = (void *)MemoryManagement_Handler,
    .pfnBusFault_Handler         = (void *)BusFault_Handler,
    .pfnUsageFault_Handler       = (void *)UsageFault_Handler,
    .pvReservedC9                = (void *)(0UL), /* Reserved */
    .pvReservedC8                = (void *)(0UL), /* Reserved */
    .pvReservedC7                = (void *)(0UL), /* Reserved */
    .pvReservedC6                = (void *)(0UL), /* Reserved */
    .pfnSVCall_Handler           = (void *)SVCall_Handler,
    .pfnDebugMonitor_Handler     = (void *)DebugMonitor_Handler,
    .pvReservedC3                = (void *)(0UL), /* Reserved */
    .pfnPendSV_Handler           = (void *)PendSV_Handler,
    .pfnSysTick_Handler          = (void *)SysTick_Handler,

    /* Configurable interrupts */
    .pfnSUPC_Handler       = (void *)SUPC_Handler,   /* 0  Supply Controller */
    .pfnRSTC_Handler       = (void *)RSTC_Handler,   /* 1  Reset Controller */
    .pfnRTC_Handler        = (void *)RTC_Handler,    /* 2  Real-time Clock */
    .pfnRTT_Handler        = (void *)RTT_Handler,    /* 3  Real-time Timer */
    .pfnWDT_Handler        = (void *)WDT_Handler,    /* 4  Watchdog Timer */
    .pfnPMC_Handler        = (void *)PMC_Handler,    /* 5  Power Management Controller */
    .pfnEFC_Handler        = (void *)EFC_Handler,    /* 6  Embedded Flash Controller */
    .pfnUART0_Handler      = (void *)UART0_Handler,  /* 7  Universal Asynchronous Receiver Transmitter */
    .pfnUART1_Handler      = (void *)UART1_Handler,  /* 8  Universal Asynchronous Receiver Transmitter */
    .pvReserved9           = (void *)(0UL),          /* 9  Reserved */
    .pfnPIOA_Handler       = (void *)PIOA_Handler,   /* 10 Parallel Input/Output Controller */
    .pfnPIOB_Handler       = (void *)PIOB_Handler,   /* 11 Parallel Input/Output Controller */
    .pfnPIOC_Handler       = (void *)PIOC_Handler,   /* 12 Parallel Input/Output Controller */
    .pfnUSART0_Handler     = (void *)USART0_Handler, /* 13 Universal Synchronous Asynchronous Receiver Transmitter */
    .pfnUSART1_Handler     = (void *)USART1_Handler, /* 14 Universal Synchronous Asynchronous Receiver Transmitter */
    .pfnUSART2_Handler     = (void *)USART2_Handler, /* 15 Universal Synchronous Asynchronous Receiver Transmitter */
    .pfnPIOD_Handler       = (void *)PIOD_Handler,   /* 16 Parallel Input/Output Controller */
    .pfnPIOE_Handler       = (void *)PIOE_Handler,   /* 17 Parallel Input/Output Controller */
    .pfnHSMCI_Handler      = (void *)HSMCI_Handler,  /* 18 High Speed MultiMedia Card Interface */
    .pfnTWIHS0_Handler     = (void *)TWIHS0_Handler, /* 19 Two-wire Interface High Speed */
    .pfnTWIHS1_Handler     = (void *)TWIHS1_Handler, /* 20 Two-wire Interface High Speed */
    .pfnSPI0_Handler       = (void *)SPI0_Handler,   /* 21 Serial Peripheral Interface */
    .pfnSSC_Handler        = (void *)SSC_Handler,    /* 22 Synchronous Serial Controller */
    .pfnTC0_Handler        = (void *)TC0_Handler,    /* 23 Timer Counter */
    .pfnTC1_Handler        = (void *)TC1_Handler,    /* 24 Timer Counter */
    .pfnTC2_Handler        = (void *)TC2_Handler,    /* 25 Timer Counter */
    .pfnTC3_Handler        = (void *)TC3_Handler,    /* 26 Timer Counter */
    .pfnTC4_Handler        = (void *)TC4_Handler,    /* 27 Timer Counter */
    .pfnTC5_Handler        = (void *)TC5_Handler,    /* 28 Timer Counter */
    .pfnAFEC0_Handler      = (void *)AFEC0_Handler,  /* 29 Analog Front-End Controller */
    .pfnDACC_Handler       = (void *)DACC_Handler,   /* 30 Digital-to-Analog Converter Controller */
    .pfnPWM0_Handler       = (void *)PWM0_Handler,   /* 31 Pulse Width Modulation Controller */
    .pfnICM_Handler        = (void *)ICM_Handler,    /* 32 Integrity Check Monitor */
    .pfnACC_Handler        = (void *)ACC_Handler,    /* 33 Analog Comparator Controller */
    .pfnUSBHS_Handler      = (void *)USBHS_Handler,  /* 34 USB High-Speed Interface */
    .pfnMCAN0_INT0_Handler = (void *)MCAN0_INT0_Handler, /* 35 Controller Area Network */
    .pfnMCAN0_INT1_Handler = (void *)MCAN0_INT1_Handler, /* 36 Controller Area Network */
    .pfnMCAN1_INT0_Handler = (void *)MCAN1_INT0_Handler, /* 37 Controller Area Network */
    .pfnMCAN1_INT1_Handler = (void *)MCAN1_INT1_Handler, /* 38 Controller Area Network */
    .pfnGMAC_Handler       = (void *)GMAC_Handler,       /* 39 Gigabit Ethernet MAC */
    .pfnAFEC1_Handler      = (void *)AFEC1_Handler,      /* 40 Analog Front-End Controller */
    .pfnTWIHS2_Handler     = (void *)TWIHS2_Handler,     /* 41 Two-wire Interface High Speed */
    .pfnSPI1_Handler       = (void *)SPI1_Handler,       /* 42 Serial Peripheral Interface */
    .pfnQSPI_Handler       = (void *)QSPI_Handler,       /* 43 Quad Serial Peripheral Interface */
    .pfnUART2_Handler      = (void *)UART2_Handler,      /* 44 Universal Asynchronous Receiver Transmitter */
    .pfnUART3_Handler      = (void *)UART3_Handler,      /* 45 Universal Asynchronous Receiver Transmitter */
    .pfnUART4_Handler      = (void *)UART4_Handler,      /* 46 Universal Asynchronous Receiver Transmitter */
    .pfnTC6_Handler        = (void *)TC6_Handler,        /* 47 Timer Counter */
    .pfnTC7_Handler        = (void *)TC7_Handler,        /* 48 Timer Counter */
    .pfnTC8_Handler        = (void *)TC8_Handler,        /* 49 Timer Counter */
    .pfnTC9_Handler        = (void *)TC9_Handler,        /* 50 Timer Counter */
    .pfnTC10_Handler       = (void *)TC10_Handler,       /* 51 Timer Counter */
    .pfnTC11_Handler       = (void *)TC11_Handler,       /* 52 Timer Counter */
    .pvReserved53          = (void *)(0UL),              /* 53 Reserved */
    .pvReserved54          = (void *)(0UL),              /* 54 Reserved */
    .pvReserved55          = (void *)(0UL),              /* 55 Reserved */
    .pfnAES_Handler        = (void *)AES_Handler,        /* 56 Advanced Encryption Standard */
    .pfnTRNG_Handler       = (void *)TRNG_Handler,       /* 57 True Random Number Generator */
    .pfnXDMAC_Handler      = (void *)XDMAC_Handler,      /* 58 Extensible DMA Controller */
    .pfnISI_Handler        = (void *)ISI_Handler,        /* 59 Image Sensor Interface */
    .pfnPWM1_Handler       = (void *)PWM1_Handler,       /* 60 Pulse Width Modulation Controller */
    .pfnFPU_Handler        = (void *)FPU_Handler,        /* 61 Floating Point Unit */
    .pfnSDRAMC_Handler     = (void *)SDRAMC_Handler,     /* 62 SDRAM Controller */
    .pfnRSWDT_Handler      = (void *)RSWDT_Handler,      /* 63 Reinforced Safety Watchdog Timer */
    .pfnCCW_Handler        = (void *)CCW_Handler,        /* 64 System Control Block */
    .pfnCCF_Handler        = (void *)CCF_Handler,        /* 65 System Control Block */
    .pfnGMAC_Q1_Handler    = (void *)GMAC_Q1_Handler,    /* 66 Gigabit Ethernet MAC */
    .pfnGMAC_Q2_Handler    = (void *)GMAC_Q2_Handler,    /* 67 Gigabit Ethernet MAC */
    .pfnIXC_Handler        = (void *)IXC_Handler,        /* 68 Floating Point Unit */
    .pfnI2SC0_Handler      = (void *)I2SC0_Handler,      /* 69 Inter-IC Sound Controller */
    .pfnI2SC1_Handler      = (void *)I2SC1_Handler,      /* 70 Inter-IC Sound Controller */
    .pfnGMAC_Q3_Handler    = (void *)GMAC_Q3_Handler,    /* 71 Gigabit Ethernet MAC */
    .pfnGMAC_Q4_Handler    = (void *)GMAC_Q4_Handler,    /* 72 Gigabit Ethernet MAC */
    .pfnGMAC_Q5_Handler    = (void *)GMAC_Q5_Handler     /* 73 Gigabit Ethernet MAC */
};

int rtthread_startup(void);

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler(void)
{
	uint32_t *pSrc, *pDest;

	/* Initialize the relocate segment */
	pSrc  = &_etext;
	pDest = &_srelocate;

	if (pSrc != pDest) {
		for (; pDest < &_erelocate;) {
			*pDest++ = *pSrc++;
		}
	}

	/* Clear the zero segment */
	for (pDest = &_szero; pDest < &_ezero;) {
		*pDest++ = 0;
	}

	/* Set the vector table base address */
	pSrc      = (uint32_t *)&_sfixed;
	SCB->VTOR = ((uint32_t)pSrc & SCB_VTOR_TBLOFF_Msk);

	/* Initialize the C library */
	__libc_init_array();

	/* Branch to rtthread_startup function */
	rtthread_startup();

	/* Infinite loop */
	while (1)
		;
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void)
{
	while (1) {
	}
}
