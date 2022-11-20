/****************************************************************************//**
 * @file     startup_ma35d1_subm.S
 * @brief    CMSIS Cortex-M4 Core Device Startup File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
    .syntax unified
    .cpu cortex-m4
    .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word   _sidata
/* start address for the .data section. defined in linker script */
.word   _sdata
/* end address for the .data section. defined in linker script */
.word   _edata
/* start address for the .bss section. defined in linker script */
.word   _sbss
/* end address for the .bss section. defined in linker script */
.word   _ebss

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

    .section    .text.Reset_Handler
    .weak   Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:

#ifndef __NO_SYSTEM_INIT
    bl SystemInit
#endif

/* Copy the data segment initializers from flash to SRAM */
    movs  r1, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r3, =_sidata
    ldr r3, [r3, r1]
    str r3, [r0, r1]
    adds    r1, r1, #4

LoopCopyDataInit:
    ldr r0, =_sdata
    ldr r3, =_edata
    adds    r2, r0, r1
    cmp r2, r3
    bcc CopyDataInit
    ldr r2, =_sbss
    b   LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
    movs    r3, #0
    str r3, [r2], #4

LoopFillZerobss:
    ldr r3, = _ebss
    cmp r2, r3
    bcc FillZerobss

/* Call the application's entry point.*/
    bl  entry
    bx  lr
.size   Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None
 * @retval None
*/
    .section    .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b   Infinite_Loop
    .size   Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M4.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
    .section    .isr_vector,"a",%progbits
    .type   g_pfnVectors, %object
    .size   g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
	.word   _estack               /* Top of Stack */
	.word	Reset_Handler         /* Reset Handler */
	.word	NMI_Handler           /* NMI Handler */
	.word	HardFault_Handler     /* Hard Fault Handler */
	.word	MemManage_Handler     /* MPU Fault Handler */
	.word	BusFault_Handler      /* Bus Fault Handler */
	.word	UsageFault_Handler    /* Usage Fault Handler */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	0                     /* Reserved */
	.word	SVC_Handler           /* SVCall Handler */
	.word	DebugMon_Handler      /* Debug Monitor Handler */
	.word	0                     /* Reserved */
	.word	PendSV_Handler        /* PendSV Handler */
	.word	SysTick_Handler       /* SysTick Handler */

	/* External interrupts */
	.word	LVD_IRQHandler        /*   0      */
	.word	0                     /*   1      */
	.word	PWRWU_IRQHandler      /*   2      */
	.word	HWSEM0_IRQHandler     /*   3      */
	.word	CKFAIL_IRQHandler     /*   4      */
	.word	WHC0_IRQHandler       /*   5      */
	.word	RTC_IRQHandler        /*   6      */
	.word	TAMPER_IRQHandler     /*   7      */
	.word	WDT2_IRQHandler       /*   8      */
	.word	WWDT2_IRQHandler      /*   9      */
	.word	EINT0_IRQHandler      /*  10      */
	.word	EINT1_IRQHandler      /*  11      */
	.word	EINT2_IRQHandler      /*  12      */
	.word	EINT3_IRQHandler      /*  13      */
	.word	0                     /*  14      */
	.word	0                     /*  15      */
	.word	GPA_IRQHandler        /*  16      */
	.word	GPB_IRQHandler        /*  17      */
	.word	GPC_IRQHandler        /*  18      */
	.word	GPD_IRQHandler        /*  19      */
	.word	0                     /*  20      */
	.word	0                     /*  21      */
	.word	TMR2_IRQHandler       /*  22      */
	.word	TMR3_IRQHandler       /*  23      */
	.word	BRAKE0_IRQHandler     /*  24      */
	.word	EPWM0P0_IRQHandler    /*  25      */
	.word	EPWM0P1_IRQHandler    /*  26      */
	.word	EPWM0P2_IRQHandler    /*  27      */
	.word	QEI0_IRQHandler       /*  28      */
	.word	ECAP0_IRQHandler      /*  29      */
	.word	0                     /*  30      */
	.word	QSPI1_IRQHandler      /*  31      */
	.word	0                     /*  32      */
	.word	0                     /*  33      */
	.word	0                     /*  34      */
	.word	UART1_IRQHandler      /*  35      */
	.word	UART2_IRQHandler      /*  36      */
	.word	UART3_IRQHandler      /*  37      */
	.word	UART4_IRQHandler      /*  38      */
	.word	UART5_IRQHandler      /*  39      */
	.word	EADC00_IRQHandler     /*  40      */
	.word	EADC01_IRQHandler     /*  41      */
	.word	EADC02_IRQHandler     /*  42      */
	.word	EADC03_IRQHandler     /*  43      */
	.word	0                     /*  44      */
	.word	I2C1_IRQHandler       /*  45      */
	.word	I2S0_IRQHandler       /*  46      */
	.word	MCAN00_IRQHandler     /*  47      */
	.word	SC0_IRQHandler        /*  48      */
	.word	GPE_IRQHandler        /*  49      */
	.word	GPF_IRQHandler        /*  50      */
	.word	GPG_IRQHandler        /*  51      */
	.word	GPH_IRQHandler        /*  52      */
	.word	GPI_IRQHandler        /*  53      */
	.word	GPJ_IRQHandler        /*  54      */
	.word	TMR4_IRQHandler       /*  55      */
	.word	TMR5_IRQHandler       /*  56      */
	.word	TMR6_IRQHandler       /*  57      */
	.word	TMR7_IRQHandler       /*  58      */
	.word	BRAKE1_IRQHandler     /*  59      */
	.word	EPWM1P0_IRQHandler    /*  60      */
	.word	EPWM1P1_IRQHandler    /*  61      */
	.word	EPWM1P2_IRQHandler    /*  62      */
	.word	QEI1_IRQHandler       /*  63      */
	.word	ECAP1_IRQHandler      /*  64      */
	.word	SPI0_IRQHandler       /*  65      */
	.word	SPI1_IRQHandler       /*  66      */
	.word	PDMA2_IRQHandler      /*  67      */
	.word	PDMA3_IRQHandler      /*  68      */
	.word	UART6_IRQHandler      /*  69      */
	.word	UART7_IRQHandler      /*  70      */
	.word	UART8_IRQHandler      /*  71      */
	.word	UART9_IRQHandler      /*  72      */
	.word	UART10_IRQHandler     /*  73      */
	.word	UART11_IRQHandler     /*  74      */
	.word	I2C2_IRQHandler       /*  75      */
	.word	I2C3_IRQHandler       /*  76      */
	.word	I2S1_IRQHandler       /*  77      */
	.word	MACN10_IRQHandler     /*  78      */
	.word	SC1_IRQHandler        /*  79      */
	.word	GPK_IRQHandler        /*  80      */
	.word	GPL_IRQHandler        /*  81      */
	.word	GPM_IRQHandler        /*  82      */
	.word	GPN_IRQHandler        /*  83      */
	.word	TMR8_IRQHandler       /*  84      */
	.word	TMR9_IRQHandler       /*  85      */
	.word	TMR10_IRQHandler      /*  86      */
	.word	TMR11_IRQHandler      /*  87      */
	.word	BRAKE2_IRQHandler     /*  88      */
	.word	EPWM2P0_IRQHandler    /*  89      */
	.word	EPWM2P1_IRQHandler    /*  90      */
	.word	EPWM2P2_IRQHandler    /*  91      */
	.word	QEI2_IRQHandler       /*  92      */
	.word	ECAP2_IRQHandler      /*  93      */
	.word	SPI2_IRQHandler       /*  94      */
	.word	SPI3_IRQHandler       /*  95      */
	.word	UART12_IRQHandler     /*  96      */
	.word	UART13_IRQHandler     /*  97      */
	.word	UART14_IRQHandler     /*  98      */
	.word	UART15_IRQHandler     /*  99      */
	.word	UART16_IRQHandler     /* 100      */
	.word	I2C4_IRQHandler       /* 101      */
	.word	I2C5_IRQHandler       /* 102      */
	.word	MCAN20_IRQHandler     /* 103      */
	.word	MCAN30_IRQHandler     /* 104      */
	.word	KPI_IRQHandler        /* 105      */
	.word	MCAN01_IRQHandler     /* 106      */
	.word	MCAN11_IRQHandler     /* 107      */
	.word	MCAN21_IRQHandler     /* 108      */
	.word	MCAN31_IRQHandler     /* 109      */
	.word	ADC0_IRQHandler       /* 110      */


/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
	.endm

	def_irq_handler	NMI_Handler
	def_irq_handler	HardFault_Handler
	def_irq_handler	MemManage_Handler
	def_irq_handler	BusFault_Handler
	def_irq_handler	UsageFault_Handler
	def_irq_handler	SVC_Handler
	def_irq_handler	DebugMon_Handler
	def_irq_handler	PendSV_Handler
	def_irq_handler	SysTick_Handler

	def_irq_handler	LVD_IRQHandler
	def_irq_handler	PWRWU_IRQHandler
	def_irq_handler	HWSEM0_IRQHandler
	def_irq_handler	CKFAIL_IRQHandler
	def_irq_handler	WHC0_IRQHandler
	def_irq_handler	RTC_IRQHandler
	def_irq_handler	TAMPER_IRQHandler
	def_irq_handler	WDT2_IRQHandler
	def_irq_handler	WWDT2_IRQHandler
	def_irq_handler	EINT0_IRQHandler
	def_irq_handler	EINT1_IRQHandler
	def_irq_handler	EINT2_IRQHandler
	def_irq_handler	EINT3_IRQHandler
	def_irq_handler	GPA_IRQHandler
	def_irq_handler	GPB_IRQHandler
	def_irq_handler	GPC_IRQHandler
	def_irq_handler	GPD_IRQHandler
	def_irq_handler	TMR2_IRQHandler
	def_irq_handler	TMR3_IRQHandler
	def_irq_handler	BRAKE0_IRQHandler
	def_irq_handler	EPWM0P0_IRQHandler
	def_irq_handler	EPWM0P1_IRQHandler
	def_irq_handler	EPWM0P2_IRQHandler
	def_irq_handler	QEI0_IRQHandler
	def_irq_handler	ECAP0_IRQHandler
	def_irq_handler	QSPI1_IRQHandler
	def_irq_handler	UART1_IRQHandler
	def_irq_handler	UART2_IRQHandler
	def_irq_handler	UART3_IRQHandler
	def_irq_handler	UART4_IRQHandler
	def_irq_handler	UART5_IRQHandler
	def_irq_handler	EADC00_IRQHandler
	def_irq_handler	EADC01_IRQHandler
	def_irq_handler	EADC02_IRQHandler
	def_irq_handler	EADC03_IRQHandler
	def_irq_handler	I2C1_IRQHandler
	def_irq_handler	I2S0_IRQHandler
	def_irq_handler	MCAN00_IRQHandler
	def_irq_handler	SC0_IRQHandler
	def_irq_handler	GPE_IRQHandler
	def_irq_handler	GPF_IRQHandler
	def_irq_handler	GPG_IRQHandler
	def_irq_handler	GPH_IRQHandler
	def_irq_handler	GPI_IRQHandler
	def_irq_handler	GPJ_IRQHandler
	def_irq_handler	TMR4_IRQHandler
	def_irq_handler	TMR5_IRQHandler
	def_irq_handler	TMR6_IRQHandler
	def_irq_handler	TMR7_IRQHandler
	def_irq_handler	BRAKE1_IRQHandler
	def_irq_handler	EPWM1P0_IRQHandler
	def_irq_handler	EPWM1P1_IRQHandler
	def_irq_handler	EPWM1P2_IRQHandler
	def_irq_handler	QEI1_IRQHandler
	def_irq_handler	ECAP1_IRQHandler
	def_irq_handler	SPI0_IRQHandler
	def_irq_handler	SPI1_IRQHandler
	def_irq_handler	PDMA2_IRQHandler
	def_irq_handler	PDMA3_IRQHandler
	def_irq_handler	UART6_IRQHandler
	def_irq_handler	UART7_IRQHandler
	def_irq_handler	UART8_IRQHandler
	def_irq_handler	UART9_IRQHandler
	def_irq_handler	UART10_IRQHandler
	def_irq_handler	UART11_IRQHandler
	def_irq_handler	I2C2_IRQHandler
	def_irq_handler	I2C3_IRQHandler
	def_irq_handler	I2S1_IRQHandler
	def_irq_handler	MACN10_IRQHandler
	def_irq_handler	SC1_IRQHandler
	def_irq_handler	GPK_IRQHandler
	def_irq_handler	GPL_IRQHandler
	def_irq_handler	GPM_IRQHandler
	def_irq_handler	GPN_IRQHandler
	def_irq_handler	TMR8_IRQHandler
	def_irq_handler	TMR9_IRQHandler
	def_irq_handler	TMR10_IRQHandler
	def_irq_handler	TMR11_IRQHandler
	def_irq_handler	BRAKE2_IRQHandler
	def_irq_handler	EPWM2P0_IRQHandler
	def_irq_handler	EPWM2P1_IRQHandler
	def_irq_handler	EPWM2P2_IRQHandler
	def_irq_handler	QEI2_IRQHandler
	def_irq_handler	ECAP2_IRQHandler
	def_irq_handler	SPI2_IRQHandler
	def_irq_handler	SPI3_IRQHandler
	def_irq_handler	UART12_IRQHandler
	def_irq_handler	UART13_IRQHandler
	def_irq_handler	UART14_IRQHandler
	def_irq_handler	UART15_IRQHandler
	def_irq_handler	UART16_IRQHandler
	def_irq_handler	I2C4_IRQHandler
	def_irq_handler	I2C5_IRQHandler
	def_irq_handler	MCAN20_IRQHandler
	def_irq_handler	MCAN30_IRQHandler
	def_irq_handler	KPI_IRQHandler
	def_irq_handler	MCAN01_IRQHandler
	def_irq_handler	MCAN11_IRQHandler
	def_irq_handler	MCAN21_IRQHandler
	def_irq_handler	MCAN31_IRQHandler
	def_irq_handler	ADC0_IRQHandler
	.end
