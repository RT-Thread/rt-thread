/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#define TRAPL(H) mov %g0, %l0; sethi %hi(H), %l4; jmp %l4 + %lo(H); nop;
#define TRAP(H) mov %psr, %l0; sethi %hi(H), %l4; jmp %l4 + %lo(H); nop;
#define TRAP_ENTRY(H) mov %psr, %l0; sethi %hi(H), %l4; jmp %l4 + %lo(H); mov %tbr, %l3;
#define BAD_TRAP ta 0; nop; nop; nop;
#define SOFT_TRAP BAD_TRAP
#define NWINDOWS 8

.section .vectors, "ax"

.globl _ISR_Handler
.globl _window_overflow
.globl _window_underflow
.globl _reset
.globl _context_switch

.globl system_vectors
system_vectors:
    TRAPL(_reset);       ! 00 reset trap
    BAD_TRAP;			 ! 01 instruction_access_exception
    BAD_TRAP;			 ! 02 illegal_instruction
    BAD_TRAP;			 ! 03 priveleged_instruction
    BAD_TRAP;
    TRAP(_window_overflow);	            ! 05 window_overflow
    TRAP(_window_underflow);	        ! 06 window_underflow
    BAD_TRAP;			 ! 07 memory_add0ress_not_aligned
    BAD_TRAP;			 ! 08 fp_exception
    BAD_TRAP;			 ! 09 data_access_exception
    BAD_TRAP;			 ! 0A tag_overflow
    BAD_TRAP;			 ! 0B undefined
    BAD_TRAP;			 ! 0C undefined
    BAD_TRAP;			 ! 0D undefined
    BAD_TRAP;			 ! 0E undefined
    BAD_TRAP;			 ! 0F undefined
    BAD_TRAP;			 ! 10 undefined

    /* Interrupt entries */
    TRAP_ENTRY(_ISR_Handler) 	       ! 11 interrupt level 1
    TRAP_ENTRY(_ISR_Handler) 		   ! 12 interrupt level 2
    TRAP_ENTRY(_ISR_Handler) 		   ! 13 interrupt level 3
    TRAP_ENTRY(_ISR_Handler) 		   ! 14 interrupt level 4
    TRAP_ENTRY(_ISR_Handler) 		   ! 15 interrupt level 5
    TRAP_ENTRY(_ISR_Handler) 		   ! 16 interrupt level 6
    TRAP_ENTRY(_ISR_Handler) 		   ! 17 interrupt level 7
    TRAP_ENTRY(_ISR_Handler) 		   ! 18 interrupt level 8
    TRAP_ENTRY(_ISR_Handler) 		   ! 19 interrupt level 9
    TRAP_ENTRY(_ISR_Handler) 		   ! 1A interrupt level 1
    TRAP_ENTRY(_ISR_Handler) 		   ! 1B interrupt level 11
    TRAP_ENTRY(_ISR_Handler) 		   ! 1C interrupt level 12
    TRAP_ENTRY(_ISR_Handler) 		   ! 1D interrupt level 13
    TRAP_ENTRY(_ISR_Handler) 		   ! 1E interrupt level 14
    TRAP_ENTRY(_ISR_Handler) 		   ! 1F interrupt level 15

    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 20 - 23 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;		! 24 - 27 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;     ! 28 - 2B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 2C - 2F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 30 - 33 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 34 - 37 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 38 - 3B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 3C - 3F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 40 - 43 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 44 - 47 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 48 - 4B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 4C - 4F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 50 - 53 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 54 - 57 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 58 - 5B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 5C - 5F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 60 - 63 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 64 - 67 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 68 - 6B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 6C - 6F undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 70 - 73 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 74 - 77 undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 78 - 7B undefined
    BAD_TRAP; BAD_TRAP; BAD_TRAP; BAD_TRAP;	    ! 7C - 7F undefined

    /* Software traps */
    SOFT_TRAP; SOFT_TRAP; TRAP_ENTRY(_context_switch); TRAP_ENTRY(_context_switch) ! 80 - 83
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 84 - 87
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 88 - 8B
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 8C - 8F
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 90 - 93
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 94 - 97
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 98 - 9B
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! 9C - 9F
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! A0 - A3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! A4 - A7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! A8 - AB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! AC - AF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! B0 - B3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! B4 - B7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! B8 - BB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! BC - BF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! C0 - C3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! C4 - C7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! C8 - CB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! CC - CF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! D0 - D3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! D4 - D7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! D8 - DB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! DC - DF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! E0 - E3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! E4 - E7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! E8 - EB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! EC - EF
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! F0 - F3
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! F4 - F7
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! F8 - FB
    SOFT_TRAP; SOFT_TRAP; SOFT_TRAP; SOFT_TRAP;	! FC - FF
    
_window_overflow:
	mov %wim, %l3                   ! Calculate next WIM
	mov %g1, %l7
	srl %l3, 1, %g1
	sll %l3, NWINDOWS - 1, %l4
	or %l4, %g1, %g1
	save                             ! Get into window to be saved.
	mov %g1, %wim
	nop
	nop
	nop
	std %l0, [%sp + 0]
	std %l2, [%sp + 8]
	std %l4, [%sp + 16]
	std %l6, [%sp + 24]
	std %i0, [%sp + 32]
	std %i2, [%sp + 40]
	std %i4, [%sp + 48]
	std %i6, [%sp + 56]
	restore                          ! Go back to trap window.
	mov %l7, %g1
	jmp %l1                         ! Re-execute save.
	rett %l2
	
_window_underflow:
	mov %wim, %l3                   ! Calculate next WIM
	sll %l3, 1, %l4
	srl %l3, NWINDOWS - 1, %l5
	or %l5, %l4, %l5
	mov %l5, %wim
	nop
	nop
	nop
	restore                          ! Two restores to get into the
	restore                          ! window to restore
	ldd [%sp + 0], %l0             ! Restore window from the stack
	ldd [%sp + 8], %l2
	ldd [%sp + 16], %l4
	ldd [%sp + 24], %l6
	ldd [%sp + 32], %i0
	ldd [%sp + 40], %i2
	ldd [%sp + 48], %i4
	ldd [%sp + 56], %i6
	save                             ! Get back to the trap window.
	save
	jmp %l1                         ! Re-execute restore.
	rett %l2
