#include "macdefs.inc"

    name OS_Core 

    COMMON INTVEC:CODE 
 
;******************************************************************** 
; 
;	function: 
;	description:	Trap 0x10 vector used for context switch 
;		Right now, all TRAPs to $1x are trated the same way 
; 
    org 50h 
    jr OSCtxSW 
 
 
;******************************************************************** 
; 
;	function: 
;	description:    Timer 40 compare match interrupt used for system 
;                   tick interrupt 
; 
    org 0x220
    jr OSTickIntr 

    org 0x0520
    jr uarta1_int_r
  
    RSEG        CODE(1)

    EXTERN    rt_thread_switch_interrupt_flag
    EXTERN    rt_interrupt_from_thread
    EXTERN    rt_interrupt_to_thread

    EXTERN    rt_interrupt_enter        
    EXTERN    rt_interrupt_leave
    EXTERN    rt_tick_increase
    EXTERN    uarta1_receive_handler
        
    PUBLIC    rt_hw_interrupt_disable
    PUBLIC    rt_hw_interrupt_enable 
    PUBLIC    rt_hw_context_switch_to
    PUBLIC    OSCtxSW
    PUBLIC    OS_Restore_CPU_Context    

rt_hw_interrupt_disable:
    stsr psw, r1    
    di
    jmp [lp]

rt_hw_interrupt_enable:
    ldsr r1, psw
    jmp [lp]
    
OS_Restore_CPU_Context: 
    mov sp, ep 
    sld.w 4[ep], r2 
	sld.w 8[ep], r5 
	sld.w 12[ep],r6 
	sld.w 16[ep],r7 
	sld.w 20[ep],r8 
	sld.w 24[ep],r9 
	sld.w 28[ep],r10 
	sld.w 32[ep],r11 
	sld.w 36[ep],r12 
	sld.w 40[ep],r13 
	sld.w 44[ep],r14 
	sld.w 48[ep],r15 
	sld.w 52[ep],r16 
 
    ;See what was the latest interruption (trap or interrupt) 
    stsr ecr, r17                   ;Move ecr to r17 
    mov 0x050,r1 
    cmp r1, r17                     ;If latest break was due to TRAP, set EP 
    be _SetEP 
 
_ClrEP: 
    mov 0x20, r17                   ;Set only ID 
	ldsr r17, psw 
 
	;Restore caller address 
	sld.w 56[ep], r1 
	ldsr r1, EIPC 
	;Restore PSW 
	sld.w 60[ep], r1 
    andi 0xffdf,r1,r1 
	ldsr r1, EIPSW 
    sld.w 0[ep], r1 
	dispose (8+(4*14)),{r23,r24,r25,r26,r27,r28,r29,r30,r31} 
 
	;Return from interrupt starts new task! 
    reti 
 
_SetEP: 
    mov 0x60, r17                   ;Set both EIPC and ID bits 
	ldsr r17, psw 
 
	;Restore caller address 
	sld.w 56[ep], r1 
	ldsr r1, EIPC 
	;Restore PSW 
	sld.w 60[ep], r1 
    andi 0xffdf,r1,r1 
    ldsr r1, EIPSW 
    sld.w 0[ep], r1 
	dispose (8+(4*14)),{r23,r24,r25,r26,r27,r28,r29,r30,r31} 
 
	;Return from interrupt starts new task! 
	reti 
    
//rseg CODE:CODE
//public rt_hw_context_switch_to
rt_hw_context_switch_to:
	;Load stack pointer of the task to run 
    ld.w 0[r1], sp					;load sp from struct 
 
	;Restore all Processor registers from stack and return from interrupt 
    jr OS_Restore_CPU_Context

OSCtxSW:
    SAVE_CPU_CTX                    ;Save all CPU registers 

	mov rt_interrupt_from_thread, r21 
	ld.w 0[r21], r21 
	st.w sp, 0[r21] 
    
    mov    rt_interrupt_to_thread, r1
    ld.w 0[r1], r1
    ld.w 0[r1], sp 

    ;Restore all Processor registers from stack and return from interrupt 
	jr OS_Restore_CPU_Context 

rt_hw_context_switch_interrupt_do:
    mov rt_thread_switch_interrupt_flag, r8
    mov    0, r9
    st.b r9, 0[r8]
    
	mov rt_interrupt_from_thread, r21 
	ld.w 0[r21], r21 
	st.w sp, 0[r21]    
    
    mov    rt_interrupt_to_thread, r1
    ld.w 0[r1], r1
    ld.w 0[r1], sp 
    jr OS_Restore_CPU_Context
    
OSTickIntr:
    SAVE_CPU_CTX                    ;Save current task's registers
    jarl    rt_interrupt_enter,lp
    jarl    rt_tick_increase,lp
    jarl    rt_interrupt_leave,lp

    mov rt_thread_switch_interrupt_flag, r8
    ld.w 0[r8],r9
    cmp    1, r9
    be      rt_hw_context_switch_interrupt_do
    
    jr OS_Restore_CPU_Context
    
uarta1_int_r:
    SAVE_CPU_CTX                    ;Save current task's registers
    jarl    rt_interrupt_enter,lp
    jarl    uarta1_receive_handler,lp
    jarl    rt_interrupt_leave,lp

    mov rt_thread_switch_interrupt_flag, r8
    ld.w   0[r8],r9
    cmp    1, r9
    be     rt_hw_context_switch_interrupt_do
    
    jr OS_Restore_CPU_Context
    
    END
