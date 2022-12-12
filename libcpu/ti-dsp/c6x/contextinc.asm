;
; Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
;
; SPDX-License-Identifier: Apache-2.0
;
; Change Logs:
; Date           Author       Notes
; 2021-11-16     Dystopia     the first version
;

;-----------------------------------------------------------
;                       extern variable
;-----------------------------------------------------------
    .ref rt_system_stack_top

;-----------------------------------------------------------
;                     macro definition
;-----------------------------------------------------------
SAVE_ALL    .macro  __rp, __tsr
    STW .D2T2   B0,*SP--[2]             ; save original B0
    MVKL    .S2 rt_system_stack_top,B0
    MVKH    .S2 rt_system_stack_top,B0
    LDW .D2T2   *B0,B1                  ; system stack

    NOP 3
    STW .D2T2   B1,*+SP[1]              ; save original B1
    XOR .D2 SP,B1,B0                    ; check current stack types
    LDW .D2T2   *+SP[1],B1              ; restore B0/B1
    LDW .D2T2   *++SP[2],B0
    SHR .S2 B0,12,B0                    ; 0 if already using system stack
 [B0]   STDW    .D2T2   SP:DP,*--B1[1]  ; thread: save thread sp/dp system stack
 [B0]   MV  .S2 B1,SP                   ; and switch to system stack
||[!B0] STDW    .D2T2   SP:DP,*--SP[1]  ; kernel: nest interrupt save(not support)

    SUBAW   .D2 SP,2,SP

    ADD .D1X    SP,-8,A15
 || STDW    .D2T1   A15:A14,*SP--[16]   ; save A15:A14

    STDW    .D2T2   B13:B12,*SP--[1]
 || STDW    .D1T1   A13:A12,*A15--[1]
 || MVC .S2 __rp,B13
    STDW    .D2T2   B11:B10,*SP--[1]
 || STDW    .D1T1   A11:A10,*A15--[1]
 || MVC .S2 CSR,B12

    STDW    .D2T2   B9:B8,*SP--[1]
 || STDW    .D1T1   A9:A8,*A15--[1]
 || MVC .S2 RILC,B11
    STDW    .D2T2   B7:B6,*SP--[1]
 || STDW    .D1T1   A7:A6,*A15--[1]
 || MVC .S2 ILC,B10
    STDW    .D2T2   B5:B4,*SP--[1]
 || STDW    .D1T1   A5:A4,*A15--[1]
    STDW    .D2T2   B3:B2,*SP--[1]
 || STDW    .D1T1   A3:A2,*A15--[1]
 || MVC .S2 __tsr,B5
    STDW    .D2T2   B1:B0,*SP--[1]
 || STDW    .D1T1   A1:A0,*A15--[1]
 || MV  .S1X    B5,A5

    STDW    .D2T2   B31:B30,*SP--[1]
 || STDW    .D1T1   A31:A30,*A15--[1]
 || MVKL    1,A4

    STDW    .D2T2   B29:B28,*SP--[1]
 || STDW    .D1T1   A29:A28,*A15--[1]
    STDW    .D2T2   B27:B26,*SP--[1]
 || STDW    .D1T1   A27:A26,*A15--[1]
    STDW    .D2T2   B25:B24,*SP--[1]
 || STDW    .D1T1   A25:A24,*A15--[1]
    STDW    .D2T2   B23:B22,*SP--[1]
 || STDW    .D1T1   A23:A22,*A15--[1]
    STDW    .D2T2   B21:B20,*SP--[1]
 || STDW    .D1T1   A21:A20,*A15--[1]
    STDW    .D2T2   B19:B18,*SP--[1]
 || STDW    .D1T1   A19:A18,*A15--[1]
    STDW    .D2T2   B17:B16,*SP--[1]
 || STDW    .D1T1   A17:A16,*A15--[1]

    STDW    .D2T2   B13:B12,*SP--[1]    ; save PC and CSR
    STDW    .D2T2   B11:B10,*SP--[1]    ; save RILC and ILC
    STDW    .D2T1   A5:A4,*SP--[1]      ; save TSR and  orig A4(stack type)
            .endm

RESTORE_ALL .macro  __rp, __tsr
    LDDW    .D2T2   *++SP[1],B9:B8      ; get TSR (B9)
    LDDW    .D2T2   *++SP[1],B11:B10    ; get RILC (B11) and ILC (B10)
    LDDW    .D2T2   *++SP[1],B13:B12    ; get PC (B13) and CSR (B12)

    ADDAW   .D1X    SP,30,A15

    LDDW    .D1T1   *++A15[1],A17:A16
 || LDDW    .D2T2   *++SP[1],B17:B16
    LDDW    .D1T1   *++A15[1],A19:A18
 || LDDW    .D2T2   *++SP[1],B19:B18
    LDDW    .D1T1   *++A15[1],A21:A20
 || LDDW    .D2T2   *++SP[1],B21:B20
    LDDW    .D1T1   *++A15[1],A23:A22
 || LDDW    .D2T2   *++SP[1],B23:B22
    LDDW    .D1T1   *++A15[1],A25:A24
 || LDDW    .D2T2   *++SP[1],B25:B24
    LDDW    .D1T1   *++A15[1],A27:A26
 || LDDW    .D2T2   *++SP[1],B27:B26
    LDDW    .D1T1   *++A15[1],A29:A28
 || LDDW    .D2T2   *++SP[1],B29:B28
    LDDW    .D1T1   *++A15[1],A31:A30
 || LDDW    .D2T2   *++SP[1],B31:B30

    LDDW    .D1T1   *++A15[1],A1:A0
 || LDDW    .D2T2   *++SP[1],B1:B0
    LDDW    .D1T1   *++A15[1],A3:A2
 || LDDW    .D2T2   *++SP[1],B3:B2
 || MVC .S2 B9,__tsr
    LDDW    .D1T1   *++A15[1],A5:A4
 || LDDW    .D2T2   *++SP[1],B5:B4
 || MVC .S2 B11,RILC
    LDDW    .D1T1   *++A15[1],A7:A6
 || LDDW    .D2T2   *++SP[1],B7:B6
 || MVC .S2 B10,ILC
    LDDW    .D1T1   *++A15[1],A9:A8
 || LDDW    .D2T2   *++SP[1],B9:B8
 || MVC .S2 B13,__rp

    LDDW    .D1T1   *++A15[1],A11:A10
 || LDDW    .D2T2   *++SP[1],B11:B10
 || MVC .S2 B12,CSR
    LDDW    .D1T1   *++A15[1],A13:A12
 || LDDW    .D2T2   *++SP[1],B13:B12

    MV  .D2X    A15,SP
 || MVKL    .S1 rt_system_stack_top,A15
    MVKH    .S1 rt_system_stack_top,A15
 || ADDAW   .D1X    SP,6,A14
    STW .D1T1   A14,*A15                ; save system stack pointer

    LDDW    .D2T1   *++SP[1],A15:A14
    LDDW    .D2T2   *+SP[1],SP:DP
    NOP     4
            .endm

THREAD_SAVE_ALL .macro  __rp, __tsr
    STDW    .D2T2   SP:DP,*--SP[1]
    SUBAW   .D2 SP,2,SP

    ADD .D1X    SP,-8,A15
 || STDW    .D2T1   A15:A14,*SP--[16]   ; save A15:A14

    STDW    .D2T2   B13:B12,*SP--[1]
 || STDW    .D1T1   A13:A12,*A15--[1]
 || MVC .S2 __rp,B13
    STDW    .D2T2   B11:B10,*SP--[1]
 || STDW    .D1T1   A11:A10,*A15--[1]
 || MVC .S2 CSR,B12

    STDW    .D2T2   B9:B8,*SP--[1]
 || STDW    .D1T1   A9:A8,*A15--[1]
 || MVC .S2 RILC,B11
    STDW    .D2T2   B7:B6,*SP--[1]
 || STDW    .D1T1   A7:A6,*A15--[1]
 || MVC .S2 ILC,B10
    STDW    .D2T2   B5:B4,*SP--[1]
 || STDW    .D1T1   A5:A4,*A15--[1]
    STDW    .D2T2   B3:B2,*SP--[1]
 || STDW    .D1T1   A3:A2,*A15--[1]
 || MVC .S2 __tsr,B5
    STDW    .D2T2   B1:B0,*SP--[1]
 || STDW    .D1T1   A1:A0,*A15--[1]
 || MV  .S1X    B5,A5

    STDW    .D2T2   B31:B30,*SP--[1]
 || STDW    .D1T1   A31:A30,*A15--[1]
 || MVKL    1,A4
    STDW    .D2T2   B29:B28,*SP--[1]
 || STDW    .D1T1   A29:A28,*A15--[1]
    STDW    .D2T2   B27:B26,*SP--[1]
 || STDW    .D1T1   A27:A26,*A15--[1]
    STDW    .D2T2   B25:B24,*SP--[1]
 || STDW    .D1T1   A25:A24,*A15--[1]
    STDW    .D2T2   B23:B22,*SP--[1]
 || STDW    .D1T1   A23:A22,*A15--[1]
    STDW    .D2T2   B21:B20,*SP--[1]
 || STDW    .D1T1   A21:A20,*A15--[1]
    STDW    .D2T2   B19:B18,*SP--[1]
 || STDW    .D1T1   A19:A18,*A15--[1]
    STDW    .D2T2   B17:B16,*SP--[1]
 || STDW    .D1T1   A17:A16,*A15--[1]

    STDW    .D2T2   B13:B12,*SP--[1]    ; save PC and CSR
    STDW    .D2T2   B11:B10,*SP--[1]    ; save RILC and ILC
    STDW    .D2T1   A5:A4,*SP--[1]      ; save TSR and orig A4(stack type)
                .endm
