/*
 ****************************************************************************
**
**  File        : startup_mb9bf61x.c
**
**  Abstract    : This file contains interrupt vector and startup code.
**
**  Functions   : Reset_Handler
**
**  Target      : Fujitsu FM3 microcontrollers
**
**  Environment : Atollic TrueSTUDIO(R)
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Atollic TrueSTUDIO(R) toolchain.
**
 ****************************************************************************
*/

/**
**===========================================================================
**  Revisions
**===========================================================================
**       Date        Modification
**       2011-08-18  First issue.
**===========================================================================
*/

/**
**===========================================================================
**  External declarations
**===========================================================================
*/
extern unsigned long _sdata, _edata, _sidata, _sbss, _ebss, _isr_vector;
extern unsigned long _estack;
extern void __libc_init_array();
extern void SystemInit();
extern void main();

/**
**===========================================================================
**  Default interrupt handler
**===========================================================================
*/
void Default_Handler()
{
	/* Hang here */
	while(1)
	{
	}
}

/**
**===========================================================================
**  Reset handler
**===========================================================================
*/
__attribute__((naked)) void Reset_Handler()
{
	/* Data and BSS variables */
	unsigned long *srcdata, *dstdata, *sbss;

	/* Set up the stack pointer */
	asm("ldr sp,=_estack\n\t");

    /* Set up vector table offset register */
	dstdata = (unsigned long *)0xe000ed08;
	*dstdata = (unsigned long)&_isr_vector;

	srcdata = &_sidata;
	dstdata = &_sdata;
	sbss = &_sbss;

	/* Copy data */
	while(dstdata != &_edata)
	{
		*(dstdata++) = *(srcdata++);
	}

	/* Clear BSS */
	while(sbss != &_ebss)
	{
		*(sbss++) = '\0';
	}

	/* Run static constructors */
	//__libc_init_array();

	/* Call the clock system initialization function.*/
	SystemInit();

	/* Jump to main */
	main();

	/* In case main returns, use default handler */
	Default_Handler();
}

/**
**===========================================================================
**  Weak definitions of handlers point to Default_Handler if not implemented
**===========================================================================
*/
void NMI_Handler() __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler() __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DebugMonitor_Handler() __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler() __attribute__ ((weak, alias("Default_Handler")));

void CSV_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SWDT_Handler() __attribute__ ((weak, alias("Default_Handler")));
void LVD_Handler() __attribute__ ((weak, alias("Default_Handler")));
void MFT_WG_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void INT0_7_Handler() __attribute__ ((weak, alias("Default_Handler")));
void INT8_31_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DT_Handler() __attribute__ ((weak, alias("Default_Handler")));
void MFS0RX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS0TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS1RX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS1TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS2RX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS2TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS3RX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS3TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS4RX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS4TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS5RX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS5TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS6RX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS6TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS7RX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFS7TX_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PPG_Handler() __attribute__ ((weak, alias("Default_Handler")));
void TIM_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ADC0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ADC1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ADC2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFT_FRT_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFT_IPC_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MFT_OPC_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void BT0_7_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ETHER_MAC0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ETHER_MAC1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void USB0F_Handler() __attribute__ ((weak, alias("Default_Handler")));
void USB0_Handler() __attribute__ ((weak, alias("Default_Handler")));
void USB1F_Handler() __attribute__ ((weak, alias("Default_Handler")));
void USB1_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DMAC0_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DMAC1_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DMAC2_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DMAC3_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DMAC4_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DMAC5_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DMAC6_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DMAC7_Handler() __attribute__ ((weak, alias("Default_Handler")));
void BT8_15_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));


/**
**===========================================================================
**  Interrupt Vector Table
**===========================================================================
*/
void (* const InterruptVector[])() __attribute__ ((section(".isr_vector"))) = {
		/* Processor exceptions */
		(void (*)(void))&_estack, /* 0 - Stack pointer */
		Reset_Handler,            /* 1 - Reset */
		NMI_Handler,              /* 2 - NMI  */
		HardFault_Handler,        /* 3 - Hard fault */
		MemManage_Handler,        /* 4 - Memory management fault */
		BusFault_Handler,         /* 5 - Bus fault */
		UsageFault_Handler,       /* 6 - Usage fault */
		0,                        /* 7 - Reserved */
		0,                        /* 8 - Reserved */
		0,                        /* 9 - Reserved */
		0,                        /* 10 - Reserved */
		SVC_Handler,              /* 11 - SVCall */
		DebugMonitor_Handler,     /* 12 - Reserved for Debug */
		0,                        /* 13 - Reserved */
		PendSV_Handler,           /* 14 - PendSV */
		SysTick_Handler,          /* 15 - Systick */

		/* External Interrupts */
		CSV_Handler,              /* 0: Clock Super Visor */
		SWDT_Handler,             /* 1: Software Watchdog Timer */
		LVD_Handler,              /* 2: Low Voltage Detector */
		MFT_WG_IRQHandler,        /* 3: Wave Form Generator / DTIF */
		INT0_7_Handler,           /* 4: External Interrupt Request ch.0 to ch.7 */
		INT8_31_Handler,          /* 5: External Interrupt Request ch.8 to ch.31 */
		DT_Handler,               /* 6: Dual Timer / Quad Decoder */
		MFS0RX_IRQHandler,        /* 7: MultiFunction Serial ch.0 */
		MFS0TX_IRQHandler,        /* 8: MultiFunction Serial ch.0 */
		MFS1RX_IRQHandler,        /* 9: MultiFunction Serial ch.1 */
		MFS1TX_IRQHandler,        /* 10: MultiFunction Serial ch.1 */
		MFS2RX_IRQHandler,        /* 11: MultiFunction Serial ch.2 */
		MFS2TX_IRQHandler,        /* 12: MultiFunction Serial ch.2 */
		MFS3RX_IRQHandler,        /* 13: MultiFunction Serial ch.3 */
		MFS3TX_IRQHandler,        /* 14: MultiFunction Serial ch.3 */
		MFS4RX_IRQHandler,        /* 15: MultiFunction Serial ch.4 */
		MFS4TX_IRQHandler,        /* 16: MultiFunction Serial ch.4 */
		MFS5RX_IRQHandler,        /* 17: MultiFunction Serial ch.5 */
		MFS5TX_IRQHandler,        /* 18: MultiFunction Serial ch.5 */
		MFS6RX_IRQHandler,        /* 19: MultiFunction Serial ch.6 */
		MFS6TX_IRQHandler,        /* 20: MultiFunction Serial ch.6 */
		MFS7RX_IRQHandler,        /* 21: MultiFunction Serial ch.7 */
		MFS7TX_IRQHandler,        /* 22: MultiFunction Serial ch.7 */
		PPG_Handler,              /* 23: PPG */
		TIM_IRQHandler,           /* 24: OSC / PLL / Watch Counter */
		ADC0_IRQHandler,          /* 25: ADC0 */
		ADC1_IRQHandler,          /* 26: ADC1 */
		ADC2_IRQHandler,          /* 27: ADC2 */
		MFT_FRT_IRQHandler,       /* 28: Free-run Timer */
		MFT_IPC_IRQHandler,       /* 29: Input Capture */
		MFT_OPC_IRQHandler,       /* 30: Output Compare */
		BT0_7_IRQHandler,         /* 31: Base Timer ch.0 to ch.7 */
		ETHER_MAC0_IRQHandler,    /* 32: Ethernet MAC ch.0 */
		ETHER_MAC1_IRQHandler,    /* 33: Ethernet MAC ch.1 */
		USB0F_Handler,            /* 34: USB0 Function */
		USB0_Handler,             /* 35: USB0 Function / USB0 HOST */
		USB1F_Handler,            /* 36: USB1 Function */
		USB1_Handler,             /* 37: USB1 Function / USB1 HOST */
		DMAC0_Handler,            /* 38: DMAC ch.0 */
		DMAC1_Handler,            /* 39: DMAC ch.1 */
		DMAC2_Handler,            /* 40: DMAC ch.2 */
		DMAC3_Handler,            /* 41: DMAC ch.3 */
		DMAC4_Handler,            /* 42: DMAC ch.4 */
		DMAC5_Handler,            /* 43: DMAC ch.5 */
		DMAC6_Handler,            /* 44: DMAC ch.6 */
		DMAC7_Handler,            /* 45: DMAC ch.7 */
		BT8_15_IRQHandler,        /* 46: Base Timer ch.8 to ch.15 */
		Default_Handler           /* 47: Reserved */
};
