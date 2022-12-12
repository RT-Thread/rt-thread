;/*****************************************************************************
; * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
; *
; * This software component is licensed by XHSC under BSD 3-Clause license
; * (the "License"); You may not use this file except in compliance with the
; * License. You may obtain a copy of the License at:
; *                    opensource.org/licenses/BSD-3-Clause
; *
; */
;/****************************************************************************/
;/*  Test for IAR                                                            */
;/*  Version     V1.0                                                        */
;/*  Date        2022-03-31                                                  */
;/****************************************************************************/

            SECTION constdata:CONST(2)
data0xAAAAAAAA       DCD     0xAAAAAAAA
data0x55555555       DCD     0x55555555

            ; Exported function
            EXPORT STL_CpuTestRuntime

;*******************************************************************************
; Function Name  : STL_CpuTestRuntime
; Description    : Test CPU at run-time
; Input          : None.
; Output         : Perform routine when detect failure at set of self test cases
; Return         : STL_OK (=0):test pass; STL_ERR (=1):test fail;
; WARNING        : all registers destroyed when exiting this function (including
;                  preserved registers R4 to R11) and excluding stack point R13)
;*******************************************************************************/
            THUMB
            SECTION .text:CODE(2)
STL_CpuTestRuntime:
            PUSH {R4-R7}              ; Save registers

            ; Register R1
            LDR R0, =data0xAAAAAAAA
            LDR R1, [R0]
            LDR R0, [R0]
            CMP R0, R1
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R1, [R0]
            LDR R0, [R0]
            CMP R0, R1
            BNE _test_cpu_fail
            MOVS R1, #0x1

            ; Register R2
            LDR R0, =data0xAAAAAAAA
            LDR R2, [R0]
            LDR R0, [R0]
            CMP R0, R2
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R2, [R0]
            LDR R0, [R0]
            CMP R0, R2
            BNE _test_cpu_fail
            MOVS R2, #0x2

            ; Register R3
            LDR R0, =data0xAAAAAAAA
            LDR R3, [R0]
            LDR R0, [R0]
            CMP R0, R3
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R3, [R0]
            LDR R0, [R0]
            CMP R0, R3
            BNE _test_cpu_fail
            MOVS R3, #0x3

            ; Register R4
            LDR R0, =data0xAAAAAAAA
            LDR R4, [R0]
            LDR R0, [R0]
            CMP R0, R4
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R4, [R0]
            LDR R0, [R0]
            CMP R0, R4
            BNE _test_cpu_fail
            MOVS R4, #0x4

            ; Register R5
            LDR R0, =data0xAAAAAAAA
            LDR R5, [R0]
            LDR R0, [R0]
            CMP R0, R5
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R5, [R0]
            LDR R0, [R0]
            CMP R0, R5
            BNE _test_cpu_fail
            MOVS R5, #0x5

            ; Register R6
            LDR R0, =data0xAAAAAAAA
            LDR R6, [R0]
            LDR R0, [R0]
            CMP R0, R6
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R6, [R0]
            LDR R0, [R0]
            CMP R0, R6
            BNE _test_cpu_fail
            MOVS R6, #0x6

            ; Register R7
            LDR R0, =data0xAAAAAAAA
            LDR R7, [R0]
            LDR R0, [R0]
            CMP R0, R7
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R7, [R0]
            LDR R0, [R0]
            CMP R0, R7
            BNE _test_cpu_fail
            MOVS R7, #0x7

            ; Register R8
            LDR R0, =data0xAAAAAAAA
            LDR R0, [R0]
            MOV R8, R0
            CMP R0, R8
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R0, [R0]
            MOV R8, R0
            CMP R0, R8
            BNE _test_cpu_fail
            MOVS R0, #0x08
            MOV R8, R0

            BAL _test_cpu_continue

_test_cpu_fail
            ; test fail, R0 will hold value 1
            MOVS R0, #0x1       ; STL_ERR
            B _test_exit

_test_cpu_continue
            ; Register R9
            LDR R0, =data0xAAAAAAAA
            LDR R0, [R0]
            MOV R9, R0
            CMP R0, R9
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R0, [R0]
            MOV R9, R0
            CMP R0, R9
            BNE _test_cpu_fail
            MOVS R0, #0x09
            MOV R9, R0

            ; Register R10
            LDR R0, =data0xAAAAAAAA
            LDR R0, [R0]
            MOV R10, R0
            CMP R0, R10
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R0, [R0]
            MOV R10, R0
            CMP R0, R10
            BNE _test_cpu_fail
            MOVS R0, #0x0A
            MOV R10, R0

            ; Register R11
            LDR R0, =data0xAAAAAAAA
            LDR R0, [R0]
            MOV R11, R0
            CMP R0, R11
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R0, [R0]
            MOV R11, R0
            CMP R0, R11
            BNE _test_cpu_fail
            MOVS R0, #0x0B
            MOV R11, R0

            ; Register R12
            LDR R0, =data0xAAAAAAAA
            LDR R0, [R0]
            MOV R12, R0
            CMP R0, R12
            BNE _test_cpu_fail
            LDR R0, =data0x55555555
            LDR R0, [R0]
            MOV R12, R0
            CMP R0, R12
            BNE _test_cpu_fail
            MOVS R0, #0x0C
            MOV R12, R0
            LDR R0, =_test_cpu_continue

            ; pattern verification  (R0 is not tested)
            CMP R1, #0x01
            BNE _test_cpu_fail
            CMP R2, #0x02
            BNE _test_cpu_fail
            CMP R3, #0x03
            BNE _test_cpu_fail
            CMP R4, #0x04
            BNE _test_cpu_fail
            CMP R5, #0x05
            BNE _test_cpu_fail
            CMP R6, #0x06
            BNE _test_cpu_fail
            CMP R7, #0x07
            BNE _test_cpu_fail
            MOVS R0, #0x08
            CMP R0, R8
            BNE _test_cpu_fail
            MOVS R0, #0x09
            CMP R0, R9
            BNE _test_cpu_fail
            MOVS R0, #0x0A
            CMP R0, R10
            BNE _test_cpu_fail
            MOVS R0, #0x0B
            CMP R0, R11
            BNE _test_cpu_fail
            MOVS R0, #0x0C
            CMP R0, R12
            BNE _test_cpu_fail

            ; Link register R14
            ; test pass, R0 will hold value 0
            MOVS R0, #0x0       ; STL_OK
_test_exit
            POP {R4-R7}         ; Restore registers
            BX LR               ; return

            END
