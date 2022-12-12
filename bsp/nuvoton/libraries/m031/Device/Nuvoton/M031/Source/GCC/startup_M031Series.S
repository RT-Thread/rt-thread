/**************************************************************************//**
 * @file     startup_m031series.s
 * @version  V2.00
 * $Revision: 6 $
 * $Date: 18/04/12 4:44p $
 * @brief    CMSIS Cortex-M0 Core Device Startup File for M031
 *
 * @note
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

  .syntax unified
  .cpu cortex-m0
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section. 
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */  
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

    .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
/*  Unlock Register */
	ldr	r0, =0x40000100
	ldr	r1, =0x59
	str	r1, [r0]
	ldr	r1, =0x16
	str	r1, [r0]
	ldr	r1, =0x88
	str	r1, [r0]

#if 1
/* Init POR */
	ldr	r0, =0x40000024
	ldr	r1, =0x00005AA5
	str	r1, [r0]
	
/* Init LDO_RDY */
	ldr	r0, =0x40000280
	ldr	r1, =0x00000001
	str	r1, [r0]	
#endif
   /* Copy the data segment initializers from flash to SRAM */  
    movs r1, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r3, =_sidata
    ldr r3, [r3, r1]
    str r3, [r0, r1]
    adds r1, r1, #4

LoopCopyDataInit:
    ldr r0, =_sdata
    ldr r3, =_edata
    adds r2, r0, r1
    cmp r2, r3
    bcc CopyDataInit
    ldr r2, =_sbss
    b LoopFillZerobss

/* Zero fill the bss segment. */  
FillZerobss:
    movs r3, #0
    str r3, [r2, #4]
    adds r2, r2, #4

LoopFillZerobss:
    ldr r3, = _ebss
    cmp r2, r3
    bcc FillZerobss
    /* Call the clock system intitialization function.*/
    bl  SystemInit

/* Lock register */
    ldr	r0, =0x40000100
    ldr	r1, =0
    str	r1, [r0]

/* Call the application entry point.*/

    bl  entry
    bx  lr

.size   Reset_Handler, . - Reset_Handler
/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
        b Infinite_Loop

	.size	Default_Handler, .-Default_Handler
/*******************************************************************************
*
* The minimal vector table for a Cortex M0. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*******************************************************************************/


        .section .isr_vector,"a",%progbits
        .type g_pfnVectors, %object
        .size g_pfnVectors, .-g_pfnVectors
 
g_pfnVectors:
	.long	_estack               /* Top of Stack */
	.long	Reset_Handler         /* Reset Handler */
	.long	NMI_Handler           /* NMI Handler */
	.long	HardFault_Handler     /* Hard Fault Handler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	SVC_Handler           /* SVCall Handler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	PendSV_Handler        /* PendSV Handler */
	.long	SysTick_Handler       /* SysTick Handler */

	/* External interrupts */
	.long	BOD_IRQHandler        /*  0: BOD                        */
	.long	WDT_IRQHandler        /*  1: WDT                        */
	.long	EINT024_IRQHandler    /*  2: EINT0                      */
	.long	EINT135_IRQHandler    /*  3: EINT1                      */
	.long	GPABGH_IRQHandler     /*  4: GPAB                       */
	.long	GPCDEF_IRQHandler     /*  5: GPCDEF                     */
	.long	PWM0_IRQHandler       /*  6: PWM0                       */
	.long	PWM1_IRQHandler       /*  7: PWM1                       */
	.long	TMR0_IRQHandler       /*  8: TIMER0                     */
	.long	TMR1_IRQHandler       /*  9: TIMER1                     */
	.long	TMR2_IRQHandler       /* 10: TIMER2                     */
	.long	TMR3_IRQHandler       /* 11: TIMER3                     */
	.long	UART02_IRQHandler     /* 12: UART02                     */
	.long	UART13_IRQHandler     /* 13: UART13                     */
	.long	SPI0_IRQHandler       /* 14: SPI0                       */
	.long	QSPI0_IRQHandler      /* 15: QSPI0                      */
	.long	ISP_IRQHandler        /* 16: Reserved                   */
	.long	UART57_IRQHandler     /* 17: UART57                     */
	.long	I2C0_IRQHandler       /* 18: I2C0                       */
	.long	I2C1_IRQHandler       /* 19: I2C1                       */
	.long	BPWM0_IRQHandler      /* 20: BPWM0                      */
	.long	BPWM1_IRQHandler      /* 21: BPWM1                      */
	.long	USCI01_IRQHandler     /* 22: USCI01                     */
	.long	USBD_IRQHandler       /* 23: USBD                       */
	.long	Default_Handler       /* 24: Reserved                   */
	.long	ACMP01_IRQHandler     /* 25: ACMP01                     */
	.long	PDMA_IRQHandler       /* 26: PDMA                       */
	.long	UART46_IRQHandler     /* 27: UART46                     */
	.long	PWRWU_IRQHandler      /* 28: PWRWU                      */
	.long	ADC_IRQHandler        /* 29: ADC                        */
	.long	CKFAIL_IRQHandler     /* 30: CLK Fail Detect            */
	.long	RTC_IRQHandler        /* 31: RTC                        */
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler. 
* As they are weak aliases, any function with the same name will override 
* this definition.
*
*******************************************************************************/


	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
	.endm

    def_irq_handler	NMI_Handler
    def_irq_handler	HardFault_Handler
    def_irq_handler	SVC_Handler
    def_irq_handler	PendSV_Handler
    def_irq_handler	SysTick_Handler
    def_irq_handler	BOD_IRQHandler
    def_irq_handler	WDT_IRQHandler
    def_irq_handler	EINT024_IRQHandler
    def_irq_handler	EINT135_IRQHandler
    def_irq_handler	GPABGH_IRQHandler
    def_irq_handler	GPCDEF_IRQHandler
    def_irq_handler	PWM0_IRQHandler
    def_irq_handler	PWM1_IRQHandler
    def_irq_handler	TMR0_IRQHandler
    def_irq_handler	TMR1_IRQHandler
    def_irq_handler	TMR2_IRQHandler
    def_irq_handler	TMR3_IRQHandler
    def_irq_handler	UART02_IRQHandler
    def_irq_handler	UART13_IRQHandler
    def_irq_handler	SPI0_IRQHandler
    def_irq_handler	QSPI0_IRQHandler
    def_irq_handler	ISP_IRQHandler
    def_irq_handler	UART57_IRQHandler
    def_irq_handler	I2C0_IRQHandler
    def_irq_handler	I2C1_IRQHandler
    def_irq_handler	BPWM0_IRQHandler
    def_irq_handler	BPWM1_IRQHandler
    def_irq_handler	USCI01_IRQHandler
    def_irq_handler	USBD_IRQHandler
    def_irq_handler	ACMP01_IRQHandler
    def_irq_handler	PDMA_IRQHandler
    def_irq_handler	UART46_IRQHandler
    def_irq_handler	PWRWU_IRQHandler
    def_irq_handler	ADC_IRQHandler
    def_irq_handler	CKFAIL_IRQHandler
    def_irq_handler	RTC_IRQHandler



    .end
