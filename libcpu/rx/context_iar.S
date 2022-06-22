#include "cpuconfig.h"

//#include "iorx62n.h"
    EXTERN _rt_thread_switch_interrupt_flag
    EXTERN _rt_interrupt_from_thread
    EXTERN _rt_interrupt_to_thread
    EXTERN _rt_hw_hard_fault_exception
    EXTERN _rt_hw_cpu_shutdown 
    
    /*PUBLIC _Interrupt_SWINT*/
    PUBLIC ___interrupt_27
    PUBLIC ___interrupt_0
    RSEG CODE:CODE(4)

;/*
; * rt_base_t rt_hw_interrupt_disable();
; */
    PUBLIC _rt_hw_interrupt_disable
_rt_hw_interrupt_disable:
     MVTIPL      #MAX_SYSCALL_INTERRUPT_PRIORITY
     RTS

;/*
; * void rt_hw_interrupt_enable(rt_base_t level);
; */
    PUBLIC  _rt_hw_interrupt_enable
_rt_hw_interrupt_enable:
     MVTIPL     #KERNEL_INTERRUPT_PRIORITY
     RTS

; r0 --> switch from thread stack
; r1 --> switch to thread stack
; psr, pc, lr, r12, r3, r2, r1, r0 are pushed into [from] stack
___interrupt_27:

/* enable interrupt because enter the interrupt,it will be clear */
    SETPSW   I
    MVTIPL   #MAX_SYSCALL_INTERRUPT_PRIORITY
    PUSH.L   R15

/* justage if it should switch thread*/
    MOV.L    #_rt_thread_switch_interrupt_flag, R15
    MOV.L    [ R15 ], R15
    CMP      #0, R15
    BEQ      notask_exit
/* clean the flag*/
    MOV.L    #_rt_thread_switch_interrupt_flag, R15
    MOV.L    #0, [ R15 ]

/* justage if it should save the register*/
    MOV.L    #_rt_interrupt_from_thread, R15
    MOV.L    [ R15 ], R15
    CMP      #0, R15
    BEQ      need_modify_isp
    /*save register*/
    MVFC     USP, R15
    SUB      #12, R15
    MVTC     R15, USP
    MOV.L    [ R0 ], [ R15 ] ;PSW
    MOV.L    4[ R0 ], 4[ R15 ];PC
    MOV.L    8[ R0 ], 8[ R15 ] ;R15
    ADD      #12, R0
    SETPSW   U
    PUSHM    R1-R14
    MVFC     FPSW, R15
    PUSH.L   R15
    MVFACHI  R15
    PUSH.L   R15
    MVFACMI  R15 ; Middle order word.
    SHLL     #16, R15 ; Shifted left as it is restored to the low orde  r w
    PUSH.L   R15
    /*save thread stack pointer and switch to new thread*/
    MOV.L    #_rt_interrupt_from_thread, R15
    MOV.L    [ R15 ], R15
    MOV.L    R0, [ R15 ]
    BRA      switch_to_thread
need_modify_isp:
    MVFC     ISP, R15                
    ADD      #12, R15
    MVTC     R15, ISP
switch_to_thread:
    SETPSW   U
    MOV.L    #_rt_interrupt_to_thread, R15
    MOV.L    [ R15 ], R15
    MOV.L    [ R15 ], R0
    POP      R15
    MVTACLO  R15
    POP      R15
    MVTACHI  R15
    POP      R15
    MVTC     R15, FPSW
    POPM     R1-R15
    BRA      pendsv_exit
notask_exit:
    POP     R15
pendsv_exit:

     MVTIPL     #KERNEL_INTERRUPT_PRIORITY
     RTE
     NOP
     NOP
/*exception interrupt*/ 
___interrupt_0:
    PUSH.L   R15
    /*save the register for infomation*/
    MVFC     USP, R15
    SUB      #12, R15
    MVTC     R15, USP
    MOV.L    [ R0 ], [ R15 ] ;PSW
    MOV.L    4[ R0 ], 4[ R15 ];PC
    MOV.L    8[ R0 ], 8[ R15 ] ;R15
    ADD      #12, R0
    SETPSW   U
    PUSHM    R1-R14
    MVFC     FPSW, R15
    PUSH.L   R15
    MVFACHI  R15
    PUSH.L   R15
    MVFACMI  R15 ; Middle order word.
    SHLL     #16, R15 ; Shifted left as it is restored to the low orde  r w
    PUSH.L   R15
    /*save the exception infomation add R1 as a parameter of
	* function rt_hw_hard_fault_exception
	*/
     MOV.L    R0, R1
     BRA _rt_hw_hard_fault_exception   
     BRA _rt_hw_cpu_shutdown 
     RTE
     NOP
     NOP
     END

