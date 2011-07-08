/***************************************************************************//**
 * @file 		start_gcc.S
 * @brief 	Context switch functions
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	onelife
 * @version 	0.4 beta
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file 
 *  LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2010-12-21 	onelife 	Initial creation for EFM32
 * 2011-07-06 	onelife 	Modify to make use the start code in libraries
 ******************************************************************************/
 
/***************************************************************************//**
* @addtogroup cortex-m3
* @{
*******************************************************************************/
	.syntax unified
	.cpu 	cortex-m3
	.fpu 	softvfp
	.thumb

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

/***************************************************************************//**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval None
*******************************************************************************/
	.thumb
	.thumb_func
	.section	.cs3.init,"ax", %progbits
	.globl		_start
	.type		_start, %function
_start:  
	/* Copy the data segment initializers from flash to SRAM */  
	movs  r1, #0
	b  LoopCopyDataInit

CopyDataInit:
	ldr  r3, =_sidata
	ldr  r3, [r3, r1]
	str  r3, [r0, r1]
	adds  r1, r1, #4
    
LoopCopyDataInit:
	ldr  r0, =_sdata
	ldr  r3, =_edata
	adds  r2, r0, r1
	cmp  r2, r3
	bcc  CopyDataInit
	ldr  r2, =_sbss
	b  LoopFillZerobss

/* Zero fill the bss segment. */  
FillZerobss:
	movs  r3, #0
	str  r3, [r2], #4

LoopFillZerobss:
	ldr  r3, = _ebss
	cmp  r2, r3
	bcc  FillZerobss
	/* Call the application's entry point.*/
	bl  main
	bx  lr    
	.size _start, .-_start

/***************************************************************************//**
 * @}
*******************************************************************************/
