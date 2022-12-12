/**
 * \file
 *
 * Copyright (c) 2018 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#include "samc21.h"

typedef void (*intfunc)(void);
typedef union {
	intfunc __fun;
	void *  __ptr;
} intvec_elem;

void __iar_program_start(void);
int  __low_level_init(void);

/* Default empty handler */
void Dummy_Handler(void);

/* Cortex-M0+ core handlers */
#pragma weak NonMaskableInt_Handler = Dummy_Handler
#pragma weak HardFault_Handler      = Dummy_Handler
#pragma weak SVCall_Handler         = Dummy_Handler
#pragma weak PendSV_Handler         = Dummy_Handler
#pragma weak SysTick_Handler        = Dummy_Handler

/* Peripherals handlers */
#pragma weak SYSTEM_Handler = Dummy_Handler /* MCLK, OSC32KCTRL, OSCCTRL, PAC, PM, SUPC, TAL */
#pragma weak WDT_Handler    = Dummy_Handler
#pragma weak RTC_Handler    = Dummy_Handler
#pragma weak EIC_Handler    = Dummy_Handler
#pragma weak FREQM_Handler  = Dummy_Handler
#ifdef ID_TSENS
#pragma weak TSENS_Handler = Dummy_Handler
#endif
#pragma weak NVMCTRL_Handler = Dummy_Handler
#pragma weak DMAC_Handler    = Dummy_Handler
#pragma weak EVSYS_Handler   = Dummy_Handler
#pragma weak SERCOM0_Handler = Dummy_Handler
#pragma weak SERCOM1_Handler = Dummy_Handler
#pragma weak SERCOM2_Handler = Dummy_Handler
#pragma weak SERCOM3_Handler = Dummy_Handler
#ifdef ID_SERCOM4
#pragma weak SERCOM4_Handler = Dummy_Handler
#endif
#ifdef ID_SERCOM5
#pragma weak SERCOM5_Handler = Dummy_Handler
#endif
#ifdef ID_CAN0
#pragma weak CAN0_Handler = Dummy_Handler
#endif
#ifdef ID_CAN1
#pragma weak CAN1_Handler = Dummy_Handler
#endif
#pragma weak TCC0_Handler = Dummy_Handler
#ifdef ID_TCC1
#pragma weak TCC1_Handler = Dummy_Handler
#endif
#ifdef ID_TCC2
#pragma weak TCC2_Handler = Dummy_Handler
#endif
#pragma weak TC0_Handler = Dummy_Handler
#pragma weak TC1_Handler = Dummy_Handler
#pragma weak TC2_Handler = Dummy_Handler
#pragma weak TC3_Handler = Dummy_Handler
#pragma weak TC4_Handler = Dummy_Handler
#ifdef ID_ADC0
#pragma weak ADC0_Handler = Dummy_Handler
#endif
#ifdef ID_ADC1
#pragma weak ADC1_Handler = Dummy_Handler
#endif
#ifdef ID_AC
#pragma weak AC_Handler = Dummy_Handler
#endif
#ifdef ID_DAC
#pragma weak DAC_Handler = Dummy_Handler
#endif
#ifdef ID_SDADC
#pragma weak SDADC_Handler = Dummy_Handler
#endif
#ifdef ID_PTC
#pragma weak PTC_Handler = Dummy_Handler
#endif

/* Exception Table */
#pragma language = extended
#pragma segment  = "CSTACK"

/* The name "__vector_table" has special meaning for C-SPY: */
/* it is where the SP start value is found, and the NVIC vector */
/* table register (VTOR) is initialized to this address if != 0 */

#pragma section                      = ".intvec"
#pragma location                     = ".intvec"
const DeviceVectors __vector_table[] = {
    (void *)__sfe("CSTACK"),
    (void *)Reset_Handler,
    (void *)NonMaskableInt_Handler,
    (void *)HardFault_Handler,
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)SVCall_Handler,
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)PendSV_Handler,
    (void *)SysTick_Handler,

    /* Configurable interrupts */
    (void *)SYSTEM_Handler, /*  0 Main Clock, 32k Oscillators Control, Oscillators Control, Peripheral Access
                               Controller, Power Manager, Supply Controller, Trigger Allocator */
    (void *)WDT_Handler,    /*  1 Watchdog Timer */
    (void *)RTC_Handler,    /*  2 Real-Time Counter */
    (void *)EIC_Handler,    /*  3 External Interrupt Controller */
    (void *)FREQM_Handler,  /*  4 Frequency Meter */
#ifdef ID_TSENS
    (void *)TSENS_Handler, /*  5 Temperature Sensor */
#else
    (void *)(0UL), /*  5 Reserved */
#endif
    (void *)NVMCTRL_Handler, /*  6 Non-Volatile Memory Controller */
    (void *)DMAC_Handler,    /*  7 Direct Memory Access Controller */
    (void *)EVSYS_Handler,   /*  8 Event System Interface */
    (void *)SERCOM0_Handler, /*  9 Serial Communication Interface 0 */
    (void *)SERCOM1_Handler, /* 10 Serial Communication Interface 1 */
    (void *)SERCOM2_Handler, /* 11 Serial Communication Interface 2 */
    (void *)SERCOM3_Handler, /* 12 Serial Communication Interface 3 */
#ifdef ID_SERCOM4
    (void *)SERCOM4_Handler, /* 13 Serial Communication Interface 4 */
#else
    (void *)(0UL), /* 13 Reserved */
#endif
#ifdef ID_SERCOM5
    (void *)SERCOM5_Handler, /* 14 Serial Communication Interface 5 */
#else
    (void *)(0UL), /* 14 Reserved */
#endif
#ifdef ID_CAN0
    (void *)CAN0_Handler, /* 15 Control Area Network 0 */
#else
    (void *)(0UL), /* 15 Reserved */
#endif
#ifdef ID_CAN1
    (void *)CAN1_Handler, /* 16 Control Area Network 1 */
#else
    (void *)(0UL), /* 16 Reserved */
#endif
    (void *)TCC0_Handler, /* 17 Timer Counter Control 0 */
#ifdef ID_TCC1
    (void *)TCC1_Handler, /* 18 Timer Counter Control 1 */
#else
    (void *)(0UL), /* 18 Reserved */
#endif
#ifdef ID_TCC2
    (void *)TCC2_Handler, /* 19 Timer Counter Control 2 */
#else
    (void *)(0UL), /* 19 Reserved */
#endif
    (void *)TC0_Handler, /* 20 Basic Timer Counter 0 */
    (void *)TC1_Handler, /* 21 Basic Timer Counter 1 */
    (void *)TC2_Handler, /* 22 Basic Timer Counter 2 */
    (void *)TC3_Handler, /* 23 Basic Timer Counter 3 */
    (void *)TC4_Handler, /* 24 Basic Timer Counter 4 */
#ifdef ID_ADC0
    (void *)ADC0_Handler, /* 25 Analog Digital Converter 0 */
#else
    (void *)(0UL), /* 25 Reserved */
#endif
#ifdef ID_ADC1
    (void *)ADC1_Handler, /* 26 Analog Digital Converter 1 */
#else
    (void *)(0UL), /* 26 Reserved */
#endif
#ifdef ID_AC
    (void *)AC_Handler, /* 27 Analog Comparators */
#else
    (void *)(0UL), /* 27 Reserved */
#endif
#ifdef ID_DAC
    (void *)DAC_Handler, /* 28 Digital Analog Converter */
#else
    (void *)(0UL), /* 28 Reserved */
#endif
#ifdef ID_SDADC
    (void *)SDADC_Handler, /* 29 Sigma-Delta Analog Digital Converter */
#else
    (void *)(0UL), /* 29 Reserved */
#endif
#ifdef ID_PTC
    (void *)PTC_Handler /* 30 Peripheral Touch Controller */
#else
    (void *)(0UL)  /* 30 Reserved */
#endif
};

/**------------------------------------------------------------------------------
 * This is the code that gets called on processor reset. To initialize the
 * device.
 *------------------------------------------------------------------------------*/
int __low_level_init(void)
{
	uint32_t *pSrc = __section_begin(".intvec");

	SCB->VTOR = ((uint32_t)pSrc & SCB_VTOR_TBLOFF_Msk);

	return 1; /* if return 0, the data sections will not be initialized */
}

/**------------------------------------------------------------------------------
 * This is the code that gets called on processor reset. To initialize the
 * device.
 *------------------------------------------------------------------------------*/
void Reset_Handler(void)
{
	__iar_program_start();
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void)
{
	while (1) {
	}
}
