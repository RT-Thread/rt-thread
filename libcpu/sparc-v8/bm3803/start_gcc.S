/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#define PSR_INIT 0x10C0
#define PREGS 0x80000000
#define IMASK 0x90
#define ICLEAR 0x9c
#define NWINDOWS 8
#define CPU_INTERRUPT_FRAME_SIZE (0x60 + 0x50 + 34 * 4)
#define SPARC_PSR_PIL_MASK 0x00000F00
#define SPARC_PSR_ET_MASK 0x00000020
#define SPARC_PSR_CWP_MASK 0x07

.text

.globl system_vectors
.globl _reset
.globl _context_switch

_reset:
	mov %g0, %asr16
	mov %g0, %asr17
	nop
	nop
	nop
	
	set PSR_INIT, %g1
	mov %g1, %psr
	nop
	nop
	nop
	
	mov %g0, %wim
	nop
	nop
	nop
	
	mov %g0, %g1
	mov %g0, %g2
	mov %g0, %g3
	mov %g0, %g4
	mov %g0, %g5
	mov %g0, %g6
	mov %g0, %g7
	
	mov 0x8, %g1
1:
	mov %g0, %l0
	mov %g0, %l1
	mov %g0, %l2
	mov %g0, %l3
	mov %g0, %l4
	mov %g0, %l5
	mov %g0, %l6
	mov %g0, %l7
	mov %g0, %i0
	mov %g0, %i1
	mov %g0, %i2
	mov %g0, %i3
	mov %g0, %i4
	mov %g0, %i5
	mov %g0, %i6
	mov %g0, %i7
	subcc %g1, 1, %g1
	save
	bne 1b
	nop
	
	set 2, %g1
	mov %g1, %wim
	nop
	nop
	nop
	
	sethi %hi(system_vectors), %g1
	mov %g1, %tbr
	nop
	nop
	nop
	
	set PREGS, %g1
	set 0xffff, %g2
	st %g2, [%g1 + ICLEAR]
	st %g0, [%g1 + IMASK]
	
	set 0x7C47907F, %g2
	st %g2, [%g1 + 4]
	
	set PSR_INIT | 0x20, %g1
	mov %g1, %psr
	nop
	nop
	nop
	
	set _fsrinit, %g1
	ld [%g1], %fsr
	nop
	nop
	nop

	set _fpdata, %g1
	ldd [%g1], %f0
	ldd [%g1], %f2
	ldd [%g1], %f4
	ldd [%g1], %f6
	ldd [%g1], %f8
	ldd [%g1], %f10
	ldd [%g1], %f12
	ldd [%g1], %f14
	ldd [%g1], %f16
	ldd [%g1], %f18
	ldd [%g1], %f20
	ldd [%g1], %f22
	ldd [%g1], %f24
	ldd [%g1], %f26
	ldd [%g1], %f28
	ldd [%g1], %f30

	set __bss_start, %g2
	set __bss_end, %g3
	mov %g0, %g1
bss_loop:
	std %g0, [%g2]
	add %g2, 8, %g2
	cmp %g2, %g3
	bleu,a bss_loop
	nop
	
	set 0x401FFF00, %g1
	mov %g1, %sp

    /* start RT-Thread Kernel */
    call rtthread_startup
    nop
    
/*
l0 = psr
l1 = pc
l2 = npc
l3 = tbr
*/
.globl _ISR_Handler
_ISR_Handler:
	mov %g4, %l4
	mov %g5, %l5
	mov %wim, %g4
	srl %g4, %l0, %g5
	cmp %g5, 1
	bne dont_do_the_window
	nop
	srl %g4, 1, %g5
	sll %g4, NWINDOWS - 1, %g4
	or %g4, %g5, %g4
	save
	mov %g4, %wim
	nop
	nop
	nop
	
	std %l0, [%sp + 0x00]
	std %l2, [%sp + 0x08]
	std %l4, [%sp + 0x10]
	std %l6, [%sp + 0x18]

	std %i0, [%sp + 0x20]
	std %i2, [%sp + 0x28]
	std %i4, [%sp + 0x30]
	std %i6, [%sp + 0x38]
	
	restore
	nop

dont_do_the_window:
	sub %fp, CPU_INTERRUPT_FRAME_SIZE, %sp
	
	std %l0, [%sp + 0x60]
	st %l2, [%sp + 0x68]
	st %g1, [%sp + 0x6c]
	std %g2, [%sp + 0x70]
	std %l4, [%sp + 0x78]
	std %g6, [%sp + 0x80]
	
	std %i0, [%sp + 0x88]
	std %i2, [%sp + 0x90]
	std %i4, [%sp + 0x98]
	std %i6, [%sp + 0xA0]
	
	mov %y, %g1
	st %g1, [%sp + 0xA8]
	st %l6, [%sp + 0xAc]

	std %f0, [%sp + 0xB0 + 8 * 0x0]
	std %f2, [%sp + 0xB0 + 8 * 0x1]
	std %f4, [%sp + 0xB0 + 8 * 0x2]
	std %f6, [%sp + 0xB0 + 8 * 0x3]
	std %f8, [%sp + 0xB0 + 8 * 0x4]
	std %f10, [%sp + 0xB0 + 8 * 0x5]
	std %f12, [%sp + 0xB0 + 8 * 0x6]
	std %f14, [%sp + 0xB0 + 8 * 0x7]
	std %f16, [%sp + 0xB0 + 8 * 0x8]
	std %f18, [%sp + 0xB0 + 8 * 0x9]
	std %f20, [%sp + 0xB0 + 8 * 0xA]
	std %f22, [%sp + 0xB0 + 8 * 0xB]
	std %f24, [%sp + 0xB0 + 8 * 0xC]
	std %f26, [%sp + 0xB0 + 8 * 0xD]
	std %f28, [%sp + 0xB0 + 8 * 0xE]
	std %f30, [%sp + 0xB0 + 8 * 0xF]
	st %fsr, [%sp + 0xB0 + 8 * 0x10]
	
	mov %l0, %g5
	or %g5, SPARC_PSR_PIL_MASK, %g5
	wr %g5, SPARC_PSR_ET_MASK, %psr
	nop
	nop
	nop
	
	call rt_interrupt_enter
	nop
	
	and %l3, 0x0FF0, %l3
	srl %l3, 4, %o0
	mov %sp, %o1
	
	call rt_hw_trap
	nop
	
	call rt_interrupt_leave
	nop
	
	mov %l0, %psr
	nop
	nop
	nop
	
	ld [%sp + 0xA8], %l5
	mov %l5, %y
	ldd [%sp + 0x60], %l0
	ld [%sp + 0x68], %l2
	
	ld [%sp + 0x6c], %g1
	ldd [%sp + 0x70], %g2
	ldd [%sp + 0x78], %g4
	ldd [%sp + 0x80], %g6

	ldd [%sp + 0x88], %i0
	ldd [%sp + 0x90], %i2
	ldd [%sp + 0x98], %i4
	ldd [%sp + 0xA0], %i6

	ldd [%sp + 0xB0 + 8 * 0x0], %f0
	ldd [%sp + 0xB0 + 8 * 0x1], %f2
	ldd [%sp + 0xB0 + 8 * 0x2], %f4
	ldd [%sp + 0xB0 + 8 * 0x3], %f6
	ldd [%sp + 0xB0 + 8 * 0x4], %f8
	ldd [%sp + 0xB0 + 8 * 0x5], %f10
	ldd [%sp + 0xB0 + 8 * 0x6], %f12
	ldd [%sp + 0xB0 + 8 * 0x7], %f14
	ldd [%sp + 0xB0 + 8 * 0x8], %f16
	ldd [%sp + 0xB0 + 8 * 0x9], %f18
	ldd [%sp + 0xB0 + 8 * 0xA], %f20
	ldd [%sp + 0xB0 + 8 * 0xB], %f22
	ldd [%sp + 0xB0 + 8 * 0xC], %f24
	ldd [%sp + 0xB0 + 8 * 0xD], %f26
	ldd [%sp + 0xB0 + 8 * 0xE], %f28
	ldd [%sp + 0xB0 + 8 * 0xF], %f30
	ld [%sp + 0xB0 + 8 * 0x10], %fsr
	nop
	nop
	nop
	
	mov %wim, %l4
	add %l0, 1, %l6
	and %l6, SPARC_PSR_CWP_MASK, %l6
	srl %l4, %l6, %l5
	cmp %l5, 1
	bne good_task_window
	nop
	sll %l4, 1, %l5
	srl %l4, NWINDOWS - 1, %l4
	or %l4, %l5, %l4
	mov %l4, %wim
	nop
	nop
	nop
	
	restore
	ldd [%sp + 0], %l0             ! Restore window from the stack
	ldd [%sp + 8], %l2
	ldd [%sp + 16], %l4
	ldd [%sp + 24], %l6
	ldd [%sp + 32], %i0
	ldd [%sp + 40], %i2
	ldd [%sp + 48], %i4
	ldd [%sp + 56], %i6
	save
	
good_task_window:
	set rt_thread_switch_interrupt_flag, %l4
	ld [%l4], %l5
	cmp %l5, 1
	be rt_hw_context_switch_interrupt_do
	nop

	mov %l0, %psr
	nop
	nop
	nop
	
	jmp %l1
	rett %l2

rt_hw_context_switch_interrupt_do:
	st %g0, [%l4]
	
	sub %fp, 0x20, %sp
	std %g0, [%sp + 0x00]
	std %g2, [%sp + 0x08]
	std %g4, [%sp + 0x10]
	std %g6, [%sp + 0x18]
	
	mov %sp, %g3
	mov %l1, %g4
	mov %l2, %g5
	mov %l0, %g6
	mov %wim, %g7
	
	mov %g0, %wim
	nop
	nop
	nop
	set 0xFFFFFFF8, %g1
	and %g1, %g6, %g1
	mov %g1, %psr
	nop
	nop
	nop
	
	mov %g0, %g1
save_loop:
	save
	sub %g3, 0x40, %g3
	std %l0, [%g3 + 0x00]
	std %l2, [%g3 + 0x08]
	std %l4, [%g3 + 0x10]
	std %l6, [%g3 + 0x18]
	std %i0, [%g3 + 0x20]
	std %i2, [%g3 + 0x28]
	std %i4, [%g3 + 0x30]
	std %i6, [%g3 + 0x38]
	inc %g1
	cmp %g1, NWINDOWS
	bne save_loop
	nop
	
	sub %g3, 0x88, %g3
	std %f0, [%g3 + 0x00]
	std %f2, [%g3 + 0x08]
	std %f4, [%g3 + 0x10]
	std %f6, [%g3 + 0x18]
	std %f8, [%g3 + 0x20]
	std %f10, [%g3 + 0x28]
	std %f12, [%g3 + 0x30]
	std %f14, [%g3 + 0x38]
	std %f16, [%g3 + 0x40]
	std %f18, [%g3 + 0x48]
	std %f20, [%g3 + 0x50]
	std %f22, [%g3 + 0x58]
	std %f24, [%g3 + 0x60]
	std %f26, [%g3 + 0x68]
	std %f28, [%g3 + 0x70]
	std %f30, [%g3 + 0x78]
	mov %y, %g1
	st %g1, [%g3 + 0x80]
	st %fsr, [%g3 + 0x84]
	
	sub %g3, 0x10, %g3
	std %g4, [%g3 + 0x00]
	std %g6, [%g3 + 0x08]
	
	set rt_interrupt_from_thread, %g1
	ld [%g1], %g2
	st %g3, [%g2]
	
	set rt_interrupt_to_thread, %g1
	ld [%g1], %g1
	ld [%g1], %g3

	ldd [%g3 + 0x00], %g4
	ldd [%g3 + 0x08], %g6
	add %g3, 0x10, %g3
	
	ldd [%g3 + 0x00], %f0
	ldd [%g3 + 0x08], %f2
	ldd [%g3 + 0x10], %f4
	ldd [%g3 + 0x18], %f6
	ldd [%g3 + 0x20], %f8
	ldd [%g3 + 0x28], %f10
	ldd [%g3 + 0x30], %f12
	ldd [%g3 + 0x38], %f14
	ldd [%g3 + 0x40], %f16
	ldd [%g3 + 0x48], %f18
	ldd [%g3 + 0x50], %f20
	ldd [%g3 + 0x58], %f22
	ldd [%g3 + 0x60], %f24
	ldd [%g3 + 0x68], %f26
	ldd [%g3 + 0x70], %f28
	ldd [%g3 + 0x78], %f30
	ld [%g3 + 0x80], %g1
	mov %g1, %y
	ld [%g3 + 0x84], %fsr
	add %g3, 0x88, %g3
	
	set NWINDOWS - 1, %g1
	or %g1, %g6, %g1
	mov %g1, %psr
	nop
	nop
	nop
	
	mov %g0, %g1
restore_loop:
	restore
	ldd [%g3 + 0x00], %l0
	ldd [%g3 + 0x08], %l2
	ldd [%g3 + 0x10], %l4
	ldd [%g3 + 0x18], %l6 
	ldd [%g3 + 0x20], %i0
	ldd [%g3 + 0x28], %i2
	ldd [%g3 + 0x30], %i4
	ldd [%g3 + 0x38], %i6
	add %g3, 0x40, %g3
	inc %g1
	cmp %g1, NWINDOWS
	bne restore_loop
	nop
	
	mov %g6, %psr
	nop
	nop
	nop
	mov %g7, %wim
	nop
	nop
	nop
	
	mov %g4, %l1
	mov %g5, %l2
	mov %g3, %sp
	
	ldd [%sp + 0x00], %g0
	ldd [%sp + 0x08], %g2
	ldd [%sp + 0x10], %g4
	ldd [%sp + 0x18], %g6	
	add %sp, 0x20, %fp
	jmp %l1
	rett %l2

/*
l0 = psr
l1 = pc
l2 = npc
l3 = tbr
*/
_context_switch:
	mov %l2, %l1
	add %l2, 4, %l2
	
	mov %g4, %l4
	mov %g5, %l5
	mov %wim, %g4
	srl %g4, %l0, %g5
	cmp %g5, 1
	bne good_window
	nop
	srl %g4, 1, %g5
	sll %g4, NWINDOWS - 1, %g4
	or %g4, %g5, %g4
	save
	mov %g4, %wim
	nop
	nop
	nop
	
	std %l0, [%sp + 0x00]
	std %l2, [%sp + 0x08]
	std %l4, [%sp + 0x10]
	std %l6, [%sp + 0x18]

	std %i0, [%sp + 0x20]
	std %i2, [%sp + 0x28]
	std %i4, [%sp + 0x30]
	std %i6, [%sp + 0x38]
	
	restore
	nop

good_window:
	and %l3, 0x0FF0, %l3
	srl %l3, 4, %l4
	cmp %l4, 0x82
	bne switch_to
	nop
	
	sub %fp, 0x20, %sp
	std %g0, [%sp + 0x00]
	std %g2, [%sp + 0x08]
	std %g4, [%sp + 0x10]
	std %g6, [%sp + 0x18]
	
	mov %sp, %g3
	mov %l1, %g4
	mov %l2, %g5
	mov %l0, %g6
	mov %wim, %g7
	
	mov %g0, %wim
	nop
	nop
	nop
	set 0xFFFFFFF8, %g1
	and %g1, %g6, %g1
	mov %g1, %psr
	nop
	nop
	nop
	
	mov %g0, %g1
save_window:
	save
	sub %g3, 0x40, %g3
	std %l0, [%g3 + 0x00]
	std %l2, [%g3 + 0x08]
	std %l4, [%g3 + 0x10]
	std %l6, [%g3 + 0x18]
	std %i0, [%g3 + 0x20]
	std %i2, [%g3 + 0x28]
	std %i4, [%g3 + 0x30]
	std %i6, [%g3 + 0x38]
	inc %g1
	cmp %g1, NWINDOWS
	bne save_window
	nop
	
	sub %g3, 0x88, %g3
	std %f0, [%g3 + 0x00]
	std %f2, [%g3 + 0x08]
	std %f4, [%g3 + 0x10]
	std %f6, [%g3 + 0x18]
	std %f8, [%g3 + 0x20]
	std %f10, [%g3 + 0x28]
	std %f12, [%g3 + 0x30]
	std %f14, [%g3 + 0x38]
	std %f16, [%g3 + 0x40]
	std %f18, [%g3 + 0x48]
	std %f20, [%g3 + 0x50]
	std %f22, [%g3 + 0x58]
	std %f24, [%g3 + 0x60]
	std %f26, [%g3 + 0x68]
	std %f28, [%g3 + 0x70]
	std %f30, [%g3 + 0x78]
	mov %y, %g1
	st %g1, [%g3 + 0x80]
	st %fsr, [%g3 + 0x84]
	
	sub %g3, 0x10, %g3
	std %g4, [%g3 + 0x00]
	std %g6, [%g3 + 0x08]
	
	mov %g6, %psr
	nop
	nop
	nop
	
	st %g3, [%i0]
switch_to:
	mov %g0, %wim
	nop
	nop
	nop
	ld [%i1], %g3

	ldd [%g3 + 0x00], %g4
	ldd [%g3 + 0x08], %g6
	add %g3, 0x10, %g3
	
	ldd [%g3 + 0x00], %f0
	ldd [%g3 + 0x08], %f2
	ldd [%g3 + 0x10], %f4
	ldd [%g3 + 0x18], %f6
	ldd [%g3 + 0x20], %f8
	ldd [%g3 + 0x28], %f10
	ldd [%g3 + 0x30], %f12
	ldd [%g3 + 0x38], %f14
	ldd [%g3 + 0x40], %f16
	ldd [%g3 + 0x48], %f18
	ldd [%g3 + 0x50], %f20
	ldd [%g3 + 0x58], %f22
	ldd [%g3 + 0x60], %f24
	ldd [%g3 + 0x68], %f26
	ldd [%g3 + 0x70], %f28
	ldd [%g3 + 0x78], %f30
	ld [%g3 + 0x80], %g1
	mov %g1, %y
	ld [%g3 + 0x84], %fsr
	add %g3, 0x88, %g3
	
	set NWINDOWS - 1, %g1
	or %g1, %g6, %g1
	mov %g1, %psr
	nop
	nop
	nop
	
	mov %g0, %g1
restore_window:
	restore
	ldd [%g3 + 0x00], %l0
	ldd [%g3 + 0x08], %l2
	ldd [%g3 + 0x10], %l4
	ldd [%g3 + 0x18], %l6 
	ldd [%g3 + 0x20], %i0
	ldd [%g3 + 0x28], %i2
	ldd [%g3 + 0x30], %i4
	ldd [%g3 + 0x38], %i6
	add %g3, 0x40, %g3
	inc %g1
	cmp %g1, NWINDOWS
	bne restore_window
	nop
	
	mov %g6, %psr
	nop
	nop
	nop
	mov %g7, %wim
	nop
	nop
	nop
	
	mov %g4, %l1
	mov %g5, %l2
	mov %g3, %sp
	
	ldd [%sp + 0x00], %g0
	ldd [%sp + 0x08], %g2
	ldd [%sp + 0x10], %g4
	ldd [%sp + 0x18], %g6	
	add %sp, 0x20, %fp
	jmp %l1
	rett %l2
	
.data 
.align 8
_fpdata:
	.word 0, 0
_fsrinit:
	.word 0
