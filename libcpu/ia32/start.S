/*
 * File      : start.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        The first version
 */

#define __ASM__
#include <grub.h>

#define CONFIG_STACKSIZE 8192

/**
 * @addtogroup I386
 */
/*@{*/

.section .init, "ax"
.text
	
/* the system entry */
.globl _start
_start:
	jmp	multiboot_entry
	
	/* Align 32 bits boundary.  */
	.align	4
	
	/* multiboot header.  */
multiboot_header:
	/* magic */
	.long	MULTIBOOT_HEADER_MAGIC
	/* flags */
	.long	MULTIBOOT_HEADER_FLAGS
	/* checksum */
	.long	-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
	
multiboot_entry:
	movl	$(_end + 0x1000),%esp
	
	/* reset eflags.  */
	pushl	$0
	popf
	
	/*rebuild globe describe table*/
	lgdt	mygdtdesc
	
	movl	$0x10,%eax
	movw	%ax,%ds
	movw	%ax,%es
	movw	%ax,%ss
	ljmp	$0x08, $relocated
	
relocated:
	/* push the pointer to the multiboot information structure.  */
	pushl	%ebx
	
	/* push the magic value.  */
	pushl	%eax
	
	call	rtthread_startup
	
	/* never get here */
spin:
	hlt
	jmp	spin

.data
.p2align	2
mygdt:
	.word	0,0,0,0

	.word	0x07FF		/* 8Mb - limit=2047 */
	.word	0x0000
	.word	0x9A00		/* code read/exec */
	.word	0x00C0

	.word	0x07FF		/* 8Mb - limit=2047 */
	.word	0x0000
	.word	0x9200		/* data read/write */
	.word	0x00C0

mygdtdesc:
	.word	0x17		
	.long	mygdt

/*@}*/
