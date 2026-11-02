;/*
; * Copyright (c) 2006-2020, YICHIP Development Team
; * @file     yc_flash_start_gcc.s
; * @brief    source file for setting flash_start_gcc
; *
; * Change Logs:
; * Date           Author             Version        Notes
; * 2020-11-06     wushengyan         V1.0.0         the first version
; */

.org 0x200
        .global Reset_Handler,HARD_FAULT_IRQHandler,SVC_IRQHandler,PENDSV_IRQHandler,SYSTICK_IRQHandler

vectors:
                .long     0x00030000
                .long     Reset_Handler             ;//reset  1
                .long     0x00000000                ;//NMI    2
                .long     hard_fault_handler     ;//HARD   3
                .long     0                         ;
                .long     0                         ;
                .long     0                         ;
                .long     0                         ;
                .long     0                         ;
                .long     0                         ;
                .long     0                         ;
                .long     svc_handler            ;//SVC     11
                .long     0                         ;
                .long     0                         ;
                .long     pendsv_handler         ;//PENDSV  14
                .long     systick_handler        ;//SYSTICK 15
                .long     USB_IRQHandler            ;//IQR0
                .long     I2C0_IRQHandler           ;//IQR1
                .long     I2C1_IRQHandler           ;//IQR2
                .long     QSPI_IRQHandler           ;//IQR3
                .long     SPI0_IRQHandler           ;//IQR4
                .long     SPI1_IRQHandler           ;
                .long     HSPI_IRQHandler           ;
                .long     SEC_IRQHandler            ;
                .long     UART0_IRQHandler          ;
                .long     UART1_IRQHandler          ;
                .long     UART2_IRQHandler          ;
                .long     UART3_IRQHandler          ;
                .long     MEMCP_IRQHandler          ;
                .long     SCI0_IRQHandler           ;
                .long     SCI1_IRQHandler           ;
                .long     MSR_IRQHandler            ;
                .long     GPIO_IRQHandler           ;
                .long     TMRG0_IRQHandler          ;
                .long     TMRG1_IRQHandler          ;
                .long     SDIO_IRQHandler           ;
                .long     PSARM_IRQHandler          ;
                .long     RSA_IRQHandler            ;
                .long     SM4_IRQHandler            ;
                .long     TRNG_IRQHandler           ;
                .long     WDT_IRQHandler            ;
                .long     DCMI_IRQHandler           ;
                .long     ADC_IRQHandler            ;
                .long     RTC_IRQHandler            ;
                .long     BIN_IRQHandler            ;
                .long     POWER_IRQHandler          ;
                .long     SOFTWARE_IRQHandler       ;
                .long     RISCV_IRQHandler          ;
                .thumb_func
isr:
        LDR R1,=0x1000200
        LDR R0,[R0,R1]
        BX  R0
        NOP
        NOP
        NOP
        .thumb_func
Reset_Handler:
	LDR R0,=SystemInit
	BLX R0
        LDR R0,=hardware_init
        BX  R0
		
hard_fault_handler:
			ldr r0,=HardFault_Handler       
			bx r0
		
svc_handler:      
			ldr r0,=SVC_IRQHandler
			bx r0

pendsv_handler:
			ldr r0,=PendSV_Handler
			bx r0
		
systick_handler:
			ldr r0,=SysTick_Handler
			bx r0

        .thumb
        .thumb_func
hardware_init:
        ldr r1, =__exidx_start
        ldr r2, =__data_start__
        ldr r3, =__data_end__

        sub r3, r2
        ble .L_loop1_done

    .L_loop1:
        sub r3, #4
        ldr r0, [r1,r3]
        str r0, [r2,r3]
        bgt .L_loop1

    .L_loop1_done:

;/*  Single BSS section scheme.
; *
; *  The BSS section is specified by following symbols
; *    _sbss: start of the BSS section.
; *    _ebss: end of the BSS section.
; *
; *  Both addresses must be aligned to 4 bytes boundary.
; */
        ldr    r1, =__bss_start__
        ldr    r2, =__bss_end__

        mov    r0, #0

        sub    r2, r1
        ble    .L_loop3_done

    .L_loop3:
        sub    r2, #4
        str    r0, [r1, r2]
        bgt    .L_loop3
    .L_loop3_done:
        ldr    r0,=0x12345
        ldr    r3,=0x1111
        bl    main

        .globl delay
        .syntax unified
delay:
        subs r0,#1
        bne delay
        nop
        bx lr

.align    1
.thumb_func
.weak    Default_Handler
.type    Default_Handler, %function

Default_Handler:
    b    .
    .size    Default_Handler, . - Default_Handler

/*  Macro to define default handlers. Default handler
 *  will be weak symbol and just dead loops. They can be
 *  overwritten by other handlers
 */
    .macro    def_irq_handler    handler_name
    .weak    \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler      HARD_FAULT_IRQHandler
    def_irq_handler      SVC_IRQHandler
    def_irq_handler      PENDSV_IRQHandler
    def_irq_handler      SYSTICK_IRQHandler
    def_irq_handler      EXTI0_IRQHandler
    def_irq_handler      EXTI1_IRQHandler
    def_irq_handler      EXTI2_IRQHandler
    def_irq_handler      EXTI3_IRQHandler
    def_irq_handler      EXTI4_IRQHandler
    def_irq_handler      TIMER0_IRQHandler
    def_irq_handler      TIMER1_IRQHandler
    def_irq_handler      TIMER2_IRQHandler
    def_irq_handler      TIMER3_IRQHandler
    def_irq_handler      TIMER4_IRQHandler
    def_irq_handler      TIMER5_IRQHandler
    def_irq_handler      TIMER6_IRQHandler
    def_irq_handler      TIMER7_IRQHandler
    def_irq_handler      TIMER8_IRQHandler
    def_irq_handler      CHGRIN_IRQHandler
    def_irq_handler      VBAT_IRQHandler
    def_irq_handler      USB_IRQHandler
    def_irq_handler      I2C0_IRQHandler
    def_irq_handler      I2C1_IRQHandler
    def_irq_handler      QSPI_IRQHandler
    def_irq_handler      SPI0_IRQHandler
    def_irq_handler      SPI1_IRQHandler
    def_irq_handler      HSPI_IRQHandler
    def_irq_handler      SEC_IRQHandler
    def_irq_handler      UART0_IRQHandler
    def_irq_handler      UART1_IRQHandler
    def_irq_handler      UART2_IRQHandler
    def_irq_handler      UART3_IRQHandler
    def_irq_handler      MEMCP_IRQHandler
    def_irq_handler      SCI0_IRQHandler
    def_irq_handler      SCI1_IRQHandler
    def_irq_handler      MSR_IRQHandler
    def_irq_handler      GPIO_IRQHandler
    def_irq_handler      TMRG0_IRQHandler
    def_irq_handler      TMRG1_IRQHandler
    def_irq_handler      SDIO_IRQHandler
    def_irq_handler      PSARM_IRQHandler
    def_irq_handler      RSA_IRQHandler
    def_irq_handler      SM4_IRQHandler
    def_irq_handler      TRNG_IRQHandler
    def_irq_handler      WDT_IRQHandler
    def_irq_handler      DCMI_IRQHandler
    def_irq_handler      ADC_IRQHandler
    def_irq_handler      RTC_IRQHandler
    def_irq_handler      BIN_IRQHandler
    def_irq_handler      POWER_IRQHandler
    def_irq_handler      SOFTWARE_IRQHandler
    def_irq_handler      RISCV_IRQHandler
