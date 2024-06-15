/********************************** (C) COPYRIGHT *******************************
* File Name          : startup_gcc.s
* Author             : WCH
* Version            : V1.0
* Date               : 2020/07/31
* Description        : CH56x vector table for eclipse toolchain.
*******************************************************************************/

	.section	.init,"ax",@progbits
	.global	_start
	.align	1
_start:
	j	handle_reset

    .section    .vector,"ax",@progbits
    .align  1
_vector_base:
    .option norvc;
    .word   0
    .word   0
        j   nmi_handler
        j   hardfault_handler
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
        j   systick_handler
    .word   0
        j   swi_handler
    .word   0
    /* External Interrupts */
        j   wdog_irq_handler
        j   tmr0_irq_handler
        j   gpio_irq_handler
        j   spi0_irq_handler
        j   usbss_irq_handler
        j   link_irq_handler
        j   tmr1_irq_handler
        j   tmr2_irq_handler
        j   uart0_irq_handler
        j   usbhs_irq_handler
        j   emmc_irq_handler
        j   dvp_irq_handler
        j   hspi_irq_handler
        j   spi1_irq_handler
        j   uart1_irq_handler
        j   uart2_irq_handler
        j   uart3_irq_handler
        j   serdes_irq_handler
        j   eth_irq_handler
        j   pmt_irq_handler
        j   ecdc_irq_handler

    .option rvc;

    .section    .text.vector_handler,"ax", @prsocogbits

    .weak   nmi_handler
    .weak   hardfault_handler
    .weak   systick_handler
    .weak   swi_handler
    .weak   wdog_irq_handler
    .weak   tmr0_irq_handler
    .weak   gpio_irq_handler
    .weak   spi0_irq_handler
    .weak   usbss_irq_handler
    .weak   link_irq_handler
    .weak   tmr1_irq_handler
    .weak   tmr2_irq_handler
    .weak   uart0_irq_handler
    .weak   usbhs_irq_handler
    .weak   emmc_irq_handler
    .weak   dvp_irq_handler
    .weak   hspi_irq_handler
    .weak   spi1_irq_handler
    .weak   uart1_irq_handler
    .weak   uart2_irq_handler
    .weak   uart3_irq_handler
    .weak   serdes_irq_handler
    .weak   eth_irq_handler
    .weak   pmt_irq_handler
    .weak   ecdc_irq_handler

nmi_handler:
hardfault_handler:
systick_handler:
swi_handler:
wdog_irq_handler:
tmr0_irq_handler:
gpio_irq_handler:
spi0_irq_handler:
usbss_irq_handler:
link_irq_handler:
tmr1_irq_handler:
tmr2_irq_handler:
uart0_irq_handler:
usbhs_irq_handler:
emmc_irq_handler:
dvp_irq_handler:
hspi_irq_handler:
spi1_irq_handler:
uart1_irq_handler:
uart2_irq_handler:
uart3_irq_handler:
serdes_irq_handler:
eth_irq_handler:
pmt_irq_handler:
ecdc_irq_handler:
    j .L_rip

.L_rip:
    csrr t0, mepc
    csrr t1, mstatus
    csrr t2, mcause
    csrr t3, mtval
    csrr t4, mscratch
1:  j 1b

	.section	.text.handle_reset,"ax",@progbits
	.weak	handle_reset
	.align	1
handle_reset:
    .option push 
    .option	norelax 
	la gp, __global_pointer$
    .option	pop 
1:
	la sp, _eusrstack 

/* Load data section from flash to RAM */
2:	
	la a0, _data_lma
	la a1, _data_vma
	la a2, _edata
	bgeu a1, a2, 2f
1:
	lw t0, (a0)
	sw t0, (a1)
	addi a0, a0, 4
	addi a1, a1, 4
	bltu a1, a2, 1b
/* clear bss section */
2:
	la a0, _sbss
	la a1, _ebss
	bgeu a0, a1, 2f
1:
	sw zero, (a0)
	addi a0, a0, 4
	bltu a0, a1, 1b

/* clear dmadata section */
2:
    la a0, _dmadata_start
    la a1, _dmadata_end
    bgeu a0, a1, 2f
1:
    sw zero, (a0)
    addi a0, a0, 4
    bltu a0, a1, 1b

2:
	/* leave all interrupt disabled */
    li t0, 0x1800
    csrw mstatus, t0
	la t0, _vector_base
    ori t0, t0, 1
	csrw mtvec, t0
	la t0, entry
	csrw mepc, t0
	mret
