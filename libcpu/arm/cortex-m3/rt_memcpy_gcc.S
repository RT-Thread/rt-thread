/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author    Notes
 * 2020-12-23   Meco Man  porting to RT-Thread
 */

@********************************************************************************************************
@                    Copyright 2004-2020 Silicon Laboratories Inc. www.silabs.com
@
@                                 SPDX-License-Identifier: APACHE-2.0
@
@               This software is subject to an open source license and is distributed by
@                Silicon Laboratories Inc. pursuant to the terms of the Apache License,
@                    Version 2.0 available at www.apache.org/licenses/LICENSE-2.0.
@********************************************************************************************************


@********************************************************************************************************
@                                           PUBLIC FUNCTIONS
@********************************************************************************************************

.global  rt_memcpy


@********************************************************************************************************
@                                      CODE GENERATION DIRECTIVES
@********************************************************************************************************

.text
.align 2
.thumb
.syntax unified

@********************************************************************************************************
@                                             rt_memcpy()
@
@ Description : Copy data octets from one buffer to another buffer.
@
@ Argument(s) : pdest       Pointer to destination memory buffer.
@
@               psrc        Pointer to source      memory buffer.
@
@               size        Number of data buffer octets to copy.
@
@ Return(s)   : pdest       Pointer to destination memory buffer.
@
@ Caller(s)   : Application.
@
@ Note(s)     : (1) Null copies allowed (i.e. 0-octet size).
@
@               (2) Memory buffers NOT checked for overlapping.
@
@               (3) Modulo arithmetic is used to determine whether a memory buffer starts on a 'CPU_ALIGN'
@                   address boundary.
@
@               (4) ARM Cortex-M3 processors use a subset of the ARM Thumb-2 instruction set which does
@                   NOT support 16-bit conditional branch instructions but ONLY supports 8-bit conditional
@                   branch instructions.
@
@                   Therefore, branches exceeding 8-bit, signed, relative offsets :
@
@                   (a) CANNOT be implemented with     conditional branches@ but ...
@                   (b) MUST   be implemented with non-conditional branches.
@********************************************************************************************************

@ void  rt_memcpy (void        *pdest,       @  ==>  R0
@                  void        *psrc,        @  ==>  R1
@                  rt_ubase_t   count)       @  ==>  R2

.thumb_func
rt_memcpy:
        CMP         R0, #0
        BNE         rt_memcpy_1
        BX          LR                      @ return if pdest == NULL

rt_memcpy_1:
        CMP         R1, #0
        BNE         rt_memcpy_2
        BX          LR                      @ return if psrc  == NULL

rt_memcpy_2:
        CMP         R2, #0
        BNE         rt_memcpy_3
        BX          LR                      @ return if size  == 0

rt_memcpy_3:
        STMFD       SP!, {R3-R12}           @ save registers on stack
        PUSH        {R0}                    @ save pdest 

Chk_Align_32:                               @ check if both dest & src 32-bit aligned
        AND         R3, R0, #0x03
        AND         R4, R1, #0x03
        CMP         R3, R4
        BNE         chk_align_16            @ not 32-bit aligned, check for 16-bit alignment

        RSB         R3, R3, #0x04           @ compute 1-2-3 pre-copy bytes (to align to the next 32-bit boundary)
        AND         R3, R3, #0x03

pre_copy_1:
        CMP         R3, #1                  @ copy 1-2-3 bytes (to align to the next 32-bit boundary)
        BCC         copy_32_1               @ start real 32-bit copy
        CMP         R2, #1                  @ check if any more data to copy
        BCS         pre_copy_1_cont
        B           rt_memcpy_end           @ no more data to copy (see Note #4b)

pre_copy_1_cont:
        LDRB        R4, [R1], #1
        STRB        R4, [R0], #1
        SUB         R3, R3, #1
        SUB         R2, R2, #1
        B           pre_copy_1


chk_align_16:                               @ check if both dest & src 16-bit aligned
        AND         R3, R0, #0x01
        AND         R4, R1, #0x01
        CMP         R3, R4
        BEQ         pre_copy_2
        B           copy_08_1               @ not 16-bit aligned, start 8-bit copy (see Note #4b)

pre_copy_2:
        CMP         R3, #1                  @ copy 1 byte (to align to the next 16-bit boundary)
        BCC         copy_16_1               @ start real 16-bit copy

        LDRB        R4, [R1], #1
        STRB        R4, [R0], #1
        SUB         R3, R3, #1
        SUB         R2, R2, #1
        B           pre_copy_2


copy_32_1:
        CMP         R2, #360                @ Copy 9 chunks of 10 32-bit words (360 octets per loop)
        BCC         copy_32_2
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        SUB         R2, R2, #360
        B           copy_32_1

copy_32_2:
        CMP         R2, #(04*10*01)         @ Copy chunks of 10 32-bit words (40 octets per loop)
        BCC         copy_32_3
        LDMIA       R1!, {R3-R12}
        STMIA       R0!, {R3-R12}
        SUB         R2, R2, #(04*10*01)
        B           copy_32_2

copy_32_3:
        CMP         R2, #(04*01*01)         @ Copy remaining 32-bit words
        BCC         copy_16_1
        LDR         R3, [R1], #4
        STR         R3, [R0], #4
        SUB         R2, R2, #(04*01*01)
        B           copy_32_3

copy_16_1:
        CMP         R2, #(02*01*16)         @ Copy chunks of 16 16-bit words (32 bytes per loop)
        BCC         copy_16_2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        SUB         R2, R2, #(02*01*16)
        B           copy_16_1

copy_16_2:
        CMP         R2, #(02*01*01)         @ Copy remaining 16-bit words
        BCC         copy_08_1
        LDRH        R3, [R1], #2
        STRH        R3, [R0], #2
        SUB         R2, R2, #(02*01*01)
        B           copy_16_2

copy_08_1:
        CMP         R2, #(01*01*16)         @ Copy chunks of 16 8-bit words (16 bytes per loop)
        BCC         copy_08_2
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        SUB         R2, R2, #(01*01*16)
        B           copy_08_1

copy_08_2:
        CMP         R2, #(01*01*01)         @ Copy remaining 8-bit words
        BCC         rt_memcpy_end
        LDRB        R3, [R1], #1
        STRB        R3, [R0], #1
        SUB         R2, R2, #(01*01*01)
        B           copy_08_2


rt_memcpy_end:
        POP         {R0}                    @ pop pdest
        LDMFD       SP!, {R3-R12}           @ restore registers from stack
        BX          LR                      @ return


.end
