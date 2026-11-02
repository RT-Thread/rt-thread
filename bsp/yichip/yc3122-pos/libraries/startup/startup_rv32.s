/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_startup_yc3122.s
 * @brief    source file for setting startup_yc3122
 *
 * Change Logs:
 * Date           Author             Version        Notes
 * 2020-11-06     wushengyan         V1.0.0         the first version
 */

#define REGBYTES (4)
/* Enable interrupts when returning from the handler */
#define MSTATUS_PRV1 0x1880
#define MSTATUS_MIE  0x00000008
#define MSTATUS_FS   0x00006000

	.equ __stack_size,0x9000

	.text
	.globl flash_start
	.globl delay
	.globl __stack_size
	.section .text.startup
flash_start:
	la sp, _stack

	/* set exception and irq mtvec */
	la a0,trap
	ori a0,a0,1
	csrw mtvec,a0

	/* enable fs */
	li t0,MSTATUS_FS
	csrs mstatus,t0
	csrw fcsr,x0

	/* Load data section */
	la a0, _sidata
	la a1, _sdata
	la a2, _edata
	bgeu a1,a2,2f
1:      
	lw t0, (a0)
	sw t0, (a1)
	addi a0,a0,4
	addi a1,a1,4
	bltu a1,a2,1b
2: 
	/* clear bss section */
	la a0,_sbss
	la a1,_ebss
	bgeu a0,a1,2f
1:
	sw zero,(a0)
	addi a0,a0,4
	bltu a0,a1,1b
2:
	/*clear heap/statck*/
	la a0,_ebss
	la a1,_stack
	bgeu a0,a1,2f
1:
	sw zero,(a0)
	addi a0,a0,4
	bltu a0,a1,1b
2:

#ifndef __NO_SYSTEM_INIT
//        jal systeminit
#endif

#ifndef __NO_BOARD_INIT
//        jal board_init
#endif
	li t0, 0x00000800
	csrs 0x304,t0

	li t0, MSTATUS_MIE
	csrs mstatus, t0

	jal main

        /* never retch here*/
__exit:
	j __exit






.macro DISABLE_MIE
    csrc mstatus, MSTATUS_MIE
.endm

.macro ENABLE_MIE
    csrs mstatus, MSTATUS_MIE
.endm

.macro GET_IRQ_NUM
    li t1,0x000E4004
    lw t1,0(t1)
    li t3,0x01
    li t5,0x00
get_irq_num_loop:
    and t4, t1, t3
    blt  x0, t4, get_irq_num_end
    addi t5, t5, 1
    slli t3, t3, 1
    j get_irq_num_loop
get_irq_num_end:
    mv   t1,  t5
.endm



.macro SAVE_CONTEXT
    addi sp,sp,-40*4
    sw x1 , 0 *REGBYTES(sp) /* ra */
    sw x4 , 1 *REGBYTES(sp) /* tp */
    sw x5 , 2 *REGBYTES(sp) /* t0 */
    sw x6 , 3 *REGBYTES(sp) /* t1 */
    sw x7 , 4 *REGBYTES(sp) /* t2 */
    sw x10, 5 *REGBYTES(sp) /* a0 */
    sw x11, 6 *REGBYTES(sp) /* a1 */
    sw x12, 7 *REGBYTES(sp) /* a2 */
    sw x13, 8 *REGBYTES(sp) /* a3 */
    sw x14, 9 *REGBYTES(sp) /* a4 */
    sw x15, 10*REGBYTES(sp) /* a5 */
    sw x16, 11*REGBYTES(sp) /* a6 */
    sw x17, 12*REGBYTES(sp) /* a7 */
    sw x28, 13*REGBYTES(sp) /* t3 */
    sw x29, 14*REGBYTES(sp) /* t4 */
    sw x30, 15*REGBYTES(sp) /* t5 */
    sw x31, 16*REGBYTES(sp) /* t6 */

    fsw f0, 17*REGBYTES(sp) /* ft0 */
    fsw f1, 18*REGBYTES(sp) /* ft1 */
    fsw f2, 19*REGBYTES(sp) /* ft2 */
    fsw f3, 20*REGBYTES(sp) /* ft3 */
    fsw f4, 21*REGBYTES(sp) /* ft4 */
    fsw f5, 22*REGBYTES(sp) /* ft5 */
    fsw f6, 23*REGBYTES(sp) /* ft6 */
    fsw f7, 24*REGBYTES(sp) /* ft7 */
    fsw f10,25*REGBYTES(sp) /* fa0 */
    fsw f11,26*REGBYTES(sp) /* fa1 */
    fsw f12,27*REGBYTES(sp) /* fa2 */
    fsw f13,28*REGBYTES(sp) /* fa3 */
    fsw f14,29*REGBYTES(sp) /* fa4 */
    fsw f15,30*REGBYTES(sp) /* fa5 */
    fsw f16,31*REGBYTES(sp) /* fa6 */
    fsw f17,32*REGBYTES(sp) /* fa7 */
    fsw f28,33*REGBYTES(sp) /* ft8 */
    fsw f29,34*REGBYTES(sp) /* ft9 */
    fsw f30,35*REGBYTES(sp) /* ft10*/
    fsw f31,36*REGBYTES(sp) /* ft11*/
.endm

.macro RESTORE_CONTEXT
    lw x1 , 0 *REGBYTES(sp) /* ra */
    lw x4 , 1 *REGBYTES(sp) /* tp */
    lw x5 , 2 *REGBYTES(sp) /* t0 */
    lw x6 , 3 *REGBYTES(sp) /* t1 */
    lw x7 , 4 *REGBYTES(sp) /* t2 */
    lw x10, 5 *REGBYTES(sp) /* a0 */
    lw x11, 6 *REGBYTES(sp) /* a1 */
    lw x12, 7 *REGBYTES(sp) /* a2 */
    lw x13, 8 *REGBYTES(sp) /* a3 */
    lw x14, 9 *REGBYTES(sp) /* a4 */
    lw x15, 10*REGBYTES(sp) /* a5 */
    lw x16, 11*REGBYTES(sp) /* a6 */
    lw x17, 12*REGBYTES(sp) /* a7 */
    lw x28, 13*REGBYTES(sp) /* t3 */
    lw x29, 14*REGBYTES(sp) /* t4 */
    lw x30, 15*REGBYTES(sp) /* t5 */
    lw x31, 16*REGBYTES(sp) /* t6 */

    flw f0, 17*REGBYTES(sp) /* ft0 */
    flw f1, 18*REGBYTES(sp) /* ft1 */
    flw f2, 19*REGBYTES(sp) /* ft2 */
    flw f3, 20*REGBYTES(sp) /* ft3 */
    flw f4, 21*REGBYTES(sp) /* ft4 */
    flw f5, 22*REGBYTES(sp) /* ft5 */
    flw f6, 23*REGBYTES(sp) /* ft6 */
    flw f7, 24*REGBYTES(sp) /* ft7 */
    flw f10,25*REGBYTES(sp) /* fa0 */
    flw f11,26*REGBYTES(sp) /* fa1 */
    flw f12,27*REGBYTES(sp) /* fa2 */
    flw f13,28*REGBYTES(sp) /* fa3 */
    flw f14,29*REGBYTES(sp) /* fa4 */
    flw f15,30*REGBYTES(sp) /* fa5 */
    flw f16,31*REGBYTES(sp) /* fa6 */
    flw f17,32*REGBYTES(sp) /* fa7 */
    flw f28,33*REGBYTES(sp) /* ft8 */
    flw f29,34*REGBYTES(sp) /* ft9 */
    flw f30,35*REGBYTES(sp) /* ft10*/
    flw f31,36*REGBYTES(sp) /* ft11*/
    addi sp, sp, 40*REGBYTES
.endm

.macro SAVE_CSR_CONTEXT
    csrr t0,mepc
    csrr t1,mcause
    sw   t0,37*REGBYTES(sp) /* mepc */
    sw   t1,38*REGBYTES(sp) /* mcause */
.endm

.macro RESTORE_CSR_CONTEXT
    lw   t0,37*REGBYTES(sp) /* mepc */
    lw   t1,38*REGBYTES(sp) /* mcause */
    csrw mcause, t1
    csrw mepc,   t0
.endm



    .align 2
    .global Default_IRQHandler
    .weak   Default_IRQHandler
    .type   Default_IRQHandler, %function
Default_IRQHandler:

    SAVE_CONTEXT

    SAVE_CSR_CONTEXT

    /* get irq */
    la t0,isr_table
//    GET_IRQ_NUM    		/* t1: irq num */
    li t1,0x000E4004		/* t1: irq num */
    lw t1,0(t1)
    slli t2, t1, 2
    add t0, t0, t2
    lw t2, (t0)
    sw t1,39*REGBYTES(sp)


    ENABLE_MIE

    jalr t2         /* jump to irq */

    DISABLE_MIE

    /* clear pending mask*/
    lw t1,39*REGBYTES(sp)
    li t0,0x000E4004
    sw t1,(t0)

    /* enable pri mie*/
    li      t0, MSTATUS_PRV1
    csrs    mstatus, t0

    RESTORE_CSR_CONTEXT

    RESTORE_CONTEXT

    mret


/* trap start*/
.section .text.trap
/* In CLIC mode, the exeception entry must be 64bytes aligned */
.align 6
.global trap
.weak trap
.type trap, %function
trap:
    /* check for interrupt */
    addi sp,sp,-4
    sw   t0,0x0(sp)
    csrr t0,mcause
    blt  t0,x0, .Interrupt /* go to Interrupt*/
    addi sp,sp,4

    /* save regs */
    addi sp,sp,-22*4
    sw   x1 , 0 *REGBYTES(sp)
    sw   x2 , 1 *REGBYTES(sp)
    sw   x3 , 2 *REGBYTES(sp)
    sw   x4 , 3 *REGBYTES(sp)
    sw   x5 , 4 *REGBYTES(sp)
    sw   x6 , 5 *REGBYTES(sp)
    sw   x7 , 6 *REGBYTES(sp)
    sw   x8 , 7 *REGBYTES(sp)
    sw   x9 , 8 *REGBYTES(sp)
    sw   x10, 9 *REGBYTES(sp)
    sw   x11, 10*REGBYTES(sp)
    sw   x12, 11*REGBYTES(sp)
    sw   x13, 12*REGBYTES(sp)
    sw   x14, 13*REGBYTES(sp)
    sw   x15, 14*REGBYTES(sp)
    sw   x16, 15*REGBYTES(sp)
    sw   x17, 16*REGBYTES(sp)
    sw   x28, 17*REGBYTES(sp)
    sw   x29, 18*REGBYTES(sp)
    sw   x30, 19*REGBYTES(sp)
    sw   x31, 20*REGBYTES(sp)
    
    csrr a0,  mepc
    sw   a0,  21*REGBYTES(sp)
    csrr a0,  mstatus
    sw   a0,  22*REGBYTES(sp)
    mv   a0,  sp


    jal trap_c

    /*never reatch here */
    j .

.Interrupt:
    lw    t0, 0x0(sp)
    addi  sp, sp, 4

    j    Default_IRQHandler
/* trap end*/



	.global trap_c
	.weak trap_c
	.type trap_c,%function
trap_c:
	j trap_c


    .align  6
    .weak   Default_Handler
    .global Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    j       Default_Handler
    .size   Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro  def_irq_handler handler_name
    .weak   \handler_name
    .globl  \handler_name
    .set    \handler_name, Default_Handler
    .endm


    def_irq_handler USB_IRQHandler
    def_irq_handler I2C0_IRQHandler
    def_irq_handler I2C1_IRQHandler
    def_irq_handler QSPI_IRQHandler
    def_irq_handler SPI0_IRQHandler
    def_irq_handler SPI1_IRQHandler
    def_irq_handler HSPI_IRQHandler
    def_irq_handler SEC_IRQHandler
    def_irq_handler UART0_IRQHandler
    def_irq_handler UART1_IRQHandler
    def_irq_handler UART2_IRQHandler
    def_irq_handler UART3_IRQHandler
    def_irq_handler MEMCP_IRQHandler
    def_irq_handler SCI0_IRQHandler
    def_irq_handler SCI1_IRQHandler
    def_irq_handler MSR_IRQHandler
    def_irq_handler GPIO_IRQHandler
    def_irq_handler TMRG0_IRQHandler
    def_irq_handler TMRG1_IRQHandler
    def_irq_handler SDIO_IRQHandler
    def_irq_handler PSARM_IRQHandler
    def_irq_handler RSA_IRQHandler
    def_irq_handler SM4_IRQHandler
    def_irq_handler TRNG_IRQHandler
    def_irq_handler WDT_IRQHandler
    def_irq_handler DCMI_IRQHandler
    def_irq_handler ADC_IRQHandler
    def_irq_handler RTC_IRQHandler
    def_irq_handler BIN_IRQHandler
    def_irq_handler POWER_IRQHandler
    def_irq_handler SOFTWARE_IRQHandler
    def_irq_handler IPC_IRQHandler
    def_irq_handler QR_IRQHandler
    def_irq_handler ONE_BIN_IRQHandler
    def_irq_handler SYSTICK_IRQHandler
    def_irq_handler VBAT_IRQHandler
    def_irq_handler EXTI0_IRQHandler
    def_irq_handler EXTI1_IRQHandler
    def_irq_handler EXTI2_IRQHandler
    def_irq_handler EXTI3_IRQHandler
    def_irq_handler EXTI4_IRQHandler

    .align 4
isr_table:
    .long USB_IRQHandler
    .long I2C0_IRQHandler
    .long I2C1_IRQHandler
    .long QSPI_IRQHandler
    .long SPI0_IRQHandler
    .long SPI1_IRQHandler
    .long HSPI_IRQHandler
    .long SEC_IRQHandler
    .long UART0_IRQHandler
    .long UART1_IRQHandler
    .long UART2_IRQHandler
    .long UART3_IRQHandler
    .long MEMCP_IRQHandler
    .long SCI0_IRQHandler
    .long SCI1_IRQHandler
    .long MSR_IRQHandler
    .long GPIO_IRQHandler
    .long TMRG0_IRQHandler
    .long TMRG1_IRQHandler
    .long SDIO_IRQHandler
    .long PSARM_IRQHandler
    .long RSA_IRQHandler
    .long SM4_IRQHandler
    .long TRNG_IRQHandler
    .long WDT_IRQHandler
    .long DCMI_IRQHandler
    .long ADC_IRQHandler
    .long RTC_IRQHandler
    .long BIN_IRQHandler
    .long POWER_IRQHandler
    .long SOFTWARE_IRQHandler
    .long IPC_IRQHandler
    .long QR_IRQHandler
    .long ONE_BIN_IRQHandler
    .long SYSTICK_IRQHandler
