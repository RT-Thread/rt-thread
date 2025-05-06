;/*
; * Copyright (c) 2006-2018, RT-Thread Development Team
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Change Logs:
; * Date           Author       Notes
; * 2024-03-11    Wangyuqiang   first version
; */
;@-------------------------------------------------------------------------------
;@ sys_intvecs.asm
;@
;@ (c) Texas Instruments 2009-2013, All rights reserved.
;@

    ;SECTION .vectors:"ax"

;@-------------------------------------------------------------------------------
;@ import reference for interrupt routines

    IMPORT Reset_Handler
    IMPORT Undefined_Handler
    IMPORT SWI_Handler
    IMPORT SVC_Handler
    IMPORT Prefetch_Handler
    IMPORT Abort_Handler
    IMPORT Reserved_Handler
    IMPORT IRQ_Handler
    IMPORT FIQ_Handler

;/*
; * int system_vectors(void);
; */
    EXPORT system_vectors
    SECTION .intvec:CODE:NOROOT(2)
system_vectors:
        b   Reset_Handler
        b   Undefined_Handler
        b   SWI_Handler
        b   SVC_Handler
        b   Prefetch_Handler
        b   Abort_Handler
        b   Reserved_Handler
        b   IRQ_Handler
        b   FIQ_Handler
  END
