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

                ; Exported function
                EXPORT STL_PcTest

;*******************************************************************************
; Function Name  : STL_PcTest
; Description    : Test PC
; Input          : None.
; Output         : Perform routine when detect failure at set of self test cases
; Return         : STL_OK (=0):test pass; STL_ERR (=1):test fail;
; WARNING        : all registers destroyed when exiting this function (including
;                  preserved registers R4 to R11) and excluding stack point R13)
;*******************************************************************************/

            SECTION .text:CODE(2)
            THUMB
STL_PcTest
            PUSH {R4-R7}            ; Save registers
            MOVS R0, #0
            MOVS R1, #0             ; clr R0,R1
            MOV  R3, LR

_subroutine_1
            LDR R0, =_return_pc_test_addr_1
            BL  _return_pc_test_addr_1
            CMP R0, R1              ; verify return address?
            BEQ _subroutine_2
            B _pc_test_fail

_subroutine_2
            LDR R0, =_return_pc_test_addr_2
            BL  _return_pc_test_addr_2
            CMP R0, R1              ; verify return address?
            BEQ _subroutine_3
            B _pc_test_fail

_subroutine_3
            LDR R0, =_return_pc_test_addr_3
            BL  _return_pc_test_addr_3
            CMP R0, R1              ; verify return address?
            BEQ _subroutine_4
            B _pc_test_fail

_subroutine_4
            LDR R0, =_return_pc_test_addr_4
            BL  _return_pc_test_addr_4
            CMP R0, R1              ; verify return address?
            BEQ _subroutine_5
            B _pc_test_fail

_subroutine_5
            LDR R0, =_return_pc_test_addr_5
            BL  _return_pc_test_addr_5
            CMP R0, R1              ; verify return address?
            BEQ _subroutine_6
            B _pc_test_fail

_subroutine_6
            LDR R0, =_return_pc_test_addr_6
            BL  _return_pc_test_addr_6
            CMP R0, R1              ; verify return address?
            BEQ _subroutine_7
            B _pc_test_fail

_subroutine_7
            LDR R0, =_return_pc_test_addr_7
            BL  _return_pc_test_addr_7
            CMP R0, R1              ; verify return address?
            BEQ _subroutine_8
            B _pc_test_fail

_subroutine_8
            LDR R0, =_return_pc_test_addr_8
            BL  _return_pc_test_addr_8
            CMP R0, R1              ; verify return address?
            BEQ _pc_test_pass
            B _pc_test_fail

_pc_test_fail
            ; when test fail, R0 will hold value 1
            MOVS R0, #0x1           ; STL_ERR
            B _pc_test_exit

_pc_test_pass
            ; when test pass, R0 will hold value 0
            MOVS R0, #0x0           ; STL_OK
            B _pc_test_exit

_pc_test_exit:
            POP {R4-R7}             ; Restore registers
            BX R3                   ; return

            SECTION .pctestaddr1:CODE(2)
_return_pc_test_addr_1
            LDR R1, =_return_pc_test_addr_1     ; store subrouitne address in R1
            BX LR

            SECTION .pctestaddr2:CODE(2)
_return_pc_test_addr_2
            LDR R1, =_return_pc_test_addr_2     ; store subrouitne address in R1
            BX LR

            SECTION .pctestaddr3:CODE(2)
_return_pc_test_addr_3
            LDR R1, =_return_pc_test_addr_3     ; store subrouitne address in R1
            BX LR

            SECTION .pctestaddr4:CODE(2)
_return_pc_test_addr_4
            LDR R1, =_return_pc_test_addr_4     ; store subrouitne address in R1
            BX LR

            SECTION .pctestaddr5:CODE(2)
_return_pc_test_addr_5
            LDR R1, =_return_pc_test_addr_5     ; store subrouitne address in R1
            BX LR

            SECTION .pctestaddr6:CODE(2)
_return_pc_test_addr_6
            LDR R1, =_return_pc_test_addr_6     ; store subrouitne address in R1
            BX LR

            SECTION .pctestaddr7:CODE(2)
_return_pc_test_addr_7
            LDR R1, =_return_pc_test_addr_7     ; store subrouitne address in R1
            BX LR

            SECTION .pctestaddr8:CODE(2)
_return_pc_test_addr_8
            LDR R1, =_return_pc_test_addr_8     ; store subrouitne address in R1
            BX LR

            END
