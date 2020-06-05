;-------------------------------------------------------------------------------
; (c) Copyright 2007-2013 Microsemi SoC Products Group. All rights reserved.
; 
; Interrupt disabling/restoration for critical section protection.
;
; SVN $Revision: 5261 $
; SVN $Date: 2013-03-21 19:52:41 +0530 (Thu, 21 Mar 2013) $
;
    AREA    |.text|, CODE, READONLY
    EXPORT HAL_disable_interrupts
    EXPORT HAL_restore_interrupts

;-------------------------------------------------------------------------------
; 
;
HAL_disable_interrupts \
    PROC
    mrs r0, PRIMASK
    cpsid I
    bx lr
    ENDP

;-------------------------------------------------------------------------------
;
;
HAL_restore_interrupts \
    PROC
    msr PRIMASK, r0
    bx lr
    ENDP

    END
