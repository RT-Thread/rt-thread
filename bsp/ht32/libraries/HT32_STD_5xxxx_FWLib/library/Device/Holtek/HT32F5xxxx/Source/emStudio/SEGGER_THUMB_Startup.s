// **********************************************************************
// *                    SEGGER Microcontroller GmbH                     *
// *                        The Embedded Experts                        *
// **********************************************************************
// *                                                                    *
// *            (c) 2014 - 2018 SEGGER Microcontroller GmbH             *
// *            (c) 2001 - 2018 Rowley Associates Limited               *
// *                                                                    *
// *           www.segger.com     Support: support@segger.com           *
// *                                                                    *
// **********************************************************************
// *                                                                    *
// * All rights reserved.                                               *
// *                                                                    *
// * Redistribution and use in source and binary forms, with or         *
// * without modification, are permitted provided that the following    *
// * conditions are met:                                                *
// *                                                                    *
// * - Redistributions of source code must retain the above copyright   *
// *   notice, this list of conditions and the following disclaimer.    *
// *                                                                    *
// * - Neither the name of SEGGER Microcontroller GmbH                  *
// *   nor the names of its contributors may be used to endorse or      *
// *   promote products derived from this software without specific     *
// *   prior written permission.                                        *
// *                                                                    *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
// * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
// * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
// * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
// * DISCLAIMED.                                                        *
// * IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR        *
// * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
// * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
// * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
// * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
// * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
// * DAMAGE.                                                            *
// *                                                                    *
// **********************************************************************
//                           Preprocessor Definitions
//                           ------------------------
//
// FULL_LIBRARY
//
//  If defined then 
//    - argc, argv are setup by the debug_getargs.
//    - the exit symbol is defined and executes on return from main.
//    - the exit symbol calls destructors, atexit functions and then debug_exit.
//  
//  If not defined then
//    - argc and argv are zero.
//    - the exit symbol is defined, executes on return from main and loops
//

  .syntax unified  

  .section .segger.init.__SEGGER_init_lzss, "ax"
  .code 16
  .balign 2
  .global __SEGGER_init_lzss
.thumb_func
__SEGGER_init_lzss:
  ldr  r0, [r4]      @ destination
  ldr  r1, [r4, #4]  @ source stream
  adds r4, r4, #8
2:
  ldrb r2, [r1]
  adds r1, r1, #1
  tst r2, r2
  beq  9f           @ 0 -> end of table
  cmp r2, #0x80
  bcc  1f           @ +ve -> literal run
//
// -ve -> copy run
//
// r0 = pointer to output stream
// r1 = pointer to input stream
// r2 = run length
// r3 = copy byte
// r4 = pointer to initialization table
//
3:
  subs r2, r2, #0x80 // convert to run length
  beq 10f
  ldrb r3, [r1]       // r3 = first byte of distance
  adds r1, r1, #1
  cmp r3, #0x80
  bcc 5f              // r3 < 128, short run
  subs r3, r3, #0x80  // Adjust to recover true run length high byte
  lsls r3, r3, #8     // Prepare to fuse
  ldrb r5, [r1]       // extract run length low byte
  adds r1, r1, #1
  adds r3, r3, r5     // construct run length
5:
  subs r5, r0, r3    // source of where to copy from
4:
  ldrb r3, [r5]     // source byte of run
  strb r3, [r0]     // store to destination
  adds r5, r5, #1
  adds r0, r0, #1
  subs r2, r2, #1
  bne  4b
  b    2b
//
// +ve -> literal run
//
// r0 = pointer to output stream
// r1 = pointer to input stream
// r2 = run length
// r3 = copy byte
// r4 = pointer to initialization table
//
1:
  ldrb r3, [r1]     // source byte of run
  adds r1, r1, #1
  strb r3, [r0]     // store to destination
  adds r0, r0, #1
  subs r2, r2, #1
  bne  1b
  b    2b
9:
  bx lr
10:
  b 10b

  .section .segger.init.__SEGGER_init_zero, "ax"
  .code 16
  .balign 2
  .global __SEGGER_init_zero
.thumb_func
__SEGGER_init_zero:
  ldr r0, [r4]      @ destination
  ldr r1, [r4, #4]  @ size
  adds r4, r4, #8
  tst r1, r1
  beq 2f
  movs r2, #0
1:
  strb r2, [r0]
  adds r0, r0, #1
  subs r1, r1, #1
  bne 1b
2:
  bx lr

  .section .segger.init.__SEGGER_init_copy, "ax"
  .code 16
  .balign 2
  .global __SEGGER_init_copy
.thumb_func
__SEGGER_init_copy:
  ldr r0, [r4]      @ destination
  ldr r1, [r4, #4]  @ source
  ldr r2, [r4, #8]  @ size
  adds r4, r4, #12
  tst r2, r2
  beq 2f
1:
  ldrb r3, [r1]
  strb r3, [r0]
  adds r0, r0, #1
  adds r1, r1, #1
  subs r2, r2, #1
  bne 1b
2:
  bx lr

  .section .segger.init.__SEGGER_init_pack, "ax"
  .code 16
  .balign 2
  .global __SEGGER_init_pack
.thumb_func
__SEGGER_init_pack:
  ldr  r0, [r4]      @ destination
  ldr  r1, [r4, #4]  @ source stream
  adds r4, r4, #8
1:
  ldrb r2, [r1]
  adds r1, r1, #1
  cmp  r2, #0x80
  beq  4f
  bcc  3f
  ldrb r3, [r1]      @ byte to replicate
  adds r1, r1, #1
  negs r2, r2
  adds r2, r2, #255
  adds r2, r2, #1
2:
  strb r3, [r0]
  adds r0, r0, #1
  subs r2, r2, #1
  bpl  2b
  b    1b

3:                   @ 1+n literal bytes
  ldrb r3, [r1]
  strb r3, [r0]
  adds r0, r0, #1
  adds r1, r1, #1
  subs r2, r2, #1
  bpl  3b
  b    1b
4:
  bx lr

  .section .segger.init.__SEGGER_init_zpak, "ax"
  .code 16
  .balign 2
  .global __SEGGER_init_zpak
.thumb_func
__SEGGER_init_zpak:
  ldr  r0, [r4]      @ destination
  ldr  r1, [r4, #4]  @ source stream
  ldr  r2, [r4, #8]  @ size
  adds r4, r4, #12   @ skip table entries
1:
  ldrb r3, [r1]      @ get control byte from source stream
  adds r1, r1, #1
  movs r6, #8
2:
  movs r5, #0        @ prepare zero filler
  lsrs r3, r3, #1    @ get byte control flag
  bcs  3f            @ carry set -> zero filler
  ldrb r5, [r1]      @ get literal byte from source stream
  adds r1, r1, #1
3:
  strb r5, [r0]      @ store initialization byte
  adds r0, r0, #1
  subs r2, r2, #1    @ size -= 1
  beq  4f            @ exit when destination filled
  subs r6, r6, #1    @ decrement bit count
  bne  2b            @ still within this control byte
  b    1b            @ get next control byte
4:
  bx   lr

#ifndef APP_ENTRY_POINT
#define APP_ENTRY_POINT main
#endif

#ifndef ARGSSPACE
#define ARGSSPACE 128
#endif  

  .global _start
  .extern APP_ENTRY_POINT
  .global exit
  .weak exit

#ifdef INITIALIZE_USER_SECTIONS
  .extern InitializeUserMemorySections
#endif

  .section .init, "ax"
  .code 16
  .align 1
  .thumb_func

_start:
  ldr r0, = __stack_end__
  mov sp, r0
  ldr r4, =__SEGGER_init_table__
1:  
  ldr r0, [r4]
  adds r4, r4, #4
  tst r0, r0
  beq 2f
  blx r0
  b 1b
2:  

  /* Initialize the heap */
  ldr r0, = __heap_start__
  ldr r1, = __heap_end__
  subs r1, r1, r0
  cmp r1, #8
  blt 1f
  movs r2, #0
  str r2, [r0]
  adds r0, r0, #4
  str r1, [r0]
1:

#ifdef INITIALIZE_USER_SECTIONS
  ldr r2, =InitializeUserMemorySections
  blx r2
#endif

  /* Call constructors */
  ldr r0, =__ctors_start__
  ldr r1, =__ctors_end__
ctor_loop:
  cmp r0, r1
  beq ctor_end
  ldr r2, [r0]
  adds r0, #4
  push {r0-r1}  
  blx r2
  pop {r0-r1}
  b ctor_loop
ctor_end:

  /* Setup initial call frame */
  movs r0, #0
  mov lr, r0
  mov r12, sp

  .type start, function
start:
  /* Jump to application entry point */
#ifdef FULL_LIBRARY
  movs r0, #ARGSSPACE
  ldr r1, =args
  ldr r2, =debug_getargs  
  blx r2
  ldr r1, =args
#else
  movs r0, #0
  movs r1, #0
#endif
  ldr r2, =APP_ENTRY_POINT
  blx r2

  .thumb_func
exit:
#ifdef FULL_LIBRARY  
  mov r5, r0 // save the exit parameter/return result

  /* Call destructors */
  ldr r0, =__dtors_start__
  ldr r1, =__dtors_end__
dtor_loop:
  cmp r0, r1
  beq dtor_end
  ldr r2, [r0]
  add r0, #4
  push {r0-r1}
  blx r2
  pop {r0-r1}
  b dtor_loop
dtor_end:

  /* Call atexit functions */
  ldr r2, =_execute_at_exit_fns  
  blx r2

  /* Call debug_exit with return result/exit parameter */
  mov r0, r5
  ldr r2, =debug_exit  
  blx r2
#endif

  /* Returned from application entry point, loop forever. */
exit_loop:
  b exit_loop

  // default C/C++ library helpers

.macro HELPER helper_name
  .section .text.\helper_name, "ax", %progbits
  .global \helper_name
  .align 1
  .weak \helper_name  
\helper_name:
  .thumb_func
.endm

.macro JUMPTO name
#if defined(__thumb__) && !defined(__thumb2__)
  mov r12, r0
  ldr r0, =\name
  push {r0}
  mov r0, r12
  pop {pc}
#else
  b \name
#endif
.endm

HELPER __aeabi_read_tp
  ldr r0, =__tbss_start__-8
  bx lr
HELPER abort
  b .
HELPER __assert
  b .
HELPER __aeabi_assert
  b .
HELPER __sync_synchronize
  bx lr
HELPER __getchar
  JUMPTO debug_getchar
HELPER __putchar
  JUMPTO debug_putchar
HELPER __open
  JUMPTO debug_fopen
HELPER __close
  JUMPTO debug_fclose
HELPER __write   
  mov r3, r0
  mov r0, r1
  movs r1, #1  
  JUMPTO debug_fwrite
HELPER __read  
  mov r3, r0
  mov r0, r1
  movs r1, #1 
  JUMPTO debug_fread
HELPER __seek
  push {r4, lr}
  mov r4, r0
  bl debug_fseek
  cmp r0, #0
  bne 1f
  mov r0, r4
  bl debug_ftell
  pop {r4, pc}
1:
  ldr r0, =-1
  pop {r4, pc}
  // char __user_locale_name_buffer[];
  .section .bss.__user_locale_name_buffer, "aw", %nobits
  .global __user_locale_name_buffer
  .weak __user_locale_name_buffer
  __user_locale_name_buffer:
  .word 0x0

#ifdef FULL_LIBRARY
  .bss
args:
  .space ARGSSPACE
#endif
