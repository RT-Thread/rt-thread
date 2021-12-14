/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-13     Eran         the first version.
 */
 
.extern rt_interrupt_to_thread
.extern rt_interrupt_from_thread
.extern rt_thread_switch_interrupt_flag


;
; rt_base_t rt_hw_interrupt_disable();
;
.section CODE_SECTION,"ax",@progbits
.global rt_hw_interrupt_disable
.ceva_prof rt_hw_interrupt_disable, 3
.func rt_hw_interrupt_disable
.p2align  8
rt_hw_interrupt_disable:
    mov #0x8, r1.ui
    nop
    nop
    nop
    nop
    nop
    movp {supervisor} csr.ui, r0.ui
    nop
    and r0.us2, r1.us2, r0.us2
    nop
    nop
    nop
    nop
    dint
    nop
    ret
.rt_hw_interrupt_disable_END:   
.endfunc
.size rt_hw_interrupt_disable, .rt_hw_interrupt_disable_END-rt_hw_interrupt_disable

;
; rt_hw_interrupt_enable(rt_base_t level);
;
.section CODE_SECTION,"ax",@progbits
.global rt_hw_interrupt_enable
.ceva_prof rt_hw_interrupt_enable, 3
.func rt_hw_interrupt_enable
.p2align  8
rt_hw_interrupt_enable:
    mov #0x8, r1.ui
    nop
    brrcmp{neq} r0.ui, r1.ui, #do_not_enable
    eint
    nop
do_not_enable:    
    ret
.rt_hw_interrupt_enable_END:   
.endfunc
.size rt_hw_interrupt_enable, .rt_hw_interrupt_enable_END-rt_hw_interrupt_enable


;
; rt_hw_context_switch_to(rt_uint32 to);
;
.section CODE_SECTION,"ax",@progbits
.global rt_hw_context_switch_to
.ceva_prof rt_hw_context_switch_to, 3
.func rt_hw_context_switch_to
.p2align  8
rt_hw_context_switch_to:
    dint
    nop
    mov #0x0, r1.ui || mov #0x1, r2.ui || ld (r0.ui).ui, r0.ui
    nop
    nop
    st r0.ui, (#rt_interrupt_to_thread).ui
    st r1.ui, (#rt_interrupt_from_thread).ui
    st r2.ui, (#rt_thread_switch_interrupt_flag).ui
    nop
    pintr{t0}
    nop
    eint
    nop
    ret
.rt_hw_context_switch_to_END:   
.endfunc
.size rt_hw_context_switch_to, .rt_hw_context_switch_to_END-rt_hw_context_switch_to

;
; rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
;
.section CODE_SECTION,"ax",@progbits
.global rt_hw_context_switch
.ceva_prof rt_hw_context_switch, 3
.func rt_hw_context_switch
.p2align  8
rt_hw_context_switch:
    dint
    nop
    ld (r0.ui).ui, r0.ui
    ld (r1.ui).ui, r1.ui
    ld (#rt_thread_switch_interrupt_flag).ui, r2.ui || mov #0x0, r3.ui || mov #0x1, r4.ui
    nop
    cmpmov{neq} r2.ui, #0x1, r0.ui, r3.ui
    nop
    st r4.ui, (#rt_thread_switch_interrupt_flag).ui
    st r3.ui, (#rt_interrupt_from_thread).ui
    st r1.ui, (#rt_interrupt_to_thread).ui
    nop
    pintr{t0}
    nop
    eint
    nop  
    ret
.rt_hw_context_switch_END:   
.endfunc
.size rt_hw_context_switch, .rt_hw_context_switch_END-rt_hw_context_switch

;
; rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
;
.section CODE_SECTION,"ax",@progbits
.global rt_hw_context_switch_interrupt
.ceva_prof rt_hw_context_switch_interrupt, 3
.func rt_hw_context_switch_interrupt
.p2align  8
rt_hw_context_switch_interrupt:
    dint
    nop
    ld (r0.ui).ui, r0.ui
    ld (r1.ui).ui, r1.ui
    ld (#rt_thread_switch_interrupt_flag).ui, r2.ui || mov #0x0, r3.ui || mov #0x1, r4.ui
    nop
    cmpmov{neq} r2.ui, #0x1, r0.ui, r3.ui
    nop
    st r4.ui, (#rt_thread_switch_interrupt_flag).ui
    st r3.ui, (#rt_interrupt_from_thread).ui
    st r1.ui, (#rt_interrupt_to_thread).ui
    nop
    pintr{t0}
    nop
    eint
    nop  
    ret
.rt_hw_context_switch_interrupt_END:   
.endfunc
.size rt_hw_context_switch_interrupt, .rt_hw_context_switch_interrupt_END-rt_hw_context_switch_interrupt

;
; interrupt_thread_switch( void );
;
.section POSTED_INTERRUPT_SEC,"ax",@progbits
.global interrupt_thread_switch
.ceva_prof interrupt_thread_switch, 3
.func interrupt_thread_switch
.p2align  8
interrupt_thread_switch:
    dint
    nop
    ld (#rt_thread_switch_interrupt_flag).ui, r0.ui || mov #0x0, r1.ui || mov #0x1, r2.ui 
    nop
    brrcmp{neq} r0.ui, r2.ui, #exit_interrupt_thread_switch
    st r1.ui, (#rt_thread_switch_interrupt_flag).ui || ld (#rt_interrupt_from_thread).ui, r0.ui
    nop
    brrcmp{eq} r0.ui, r1.ui, #restore_interrupt_thread_switch
    push{in4} r20.di,r21.di,r22.di,r23.di           ; Push r20 - r23
    push{in4} r16.di,r17.di,r18.di,r19.di           ; Push r16 - r19
    push{in4} r12.di,r13.di,r14.di,r15.di           ; Push r12 - r15
    push{in4} r8.di ,r9.di ,r10.di,r11.di           ; Push r8 - r11
    push{in2} fba.ui, iba.ui                        ; Push special address modes and status
    push{in2} samr.ui, alc.ui                       ; Store arithmetic modes and status registers
    push{in2} sasr.ui, sfpsr.ui                     ;
    movp{supervisor} retregi.ui, r3.ui              ; Place retregi
    movp{supervisor} retregn.ui, r1.ui              ; Place retregn
    movp{supervisor} retregb.ui, r2.ui              ; Place retregb
    push{in1} r2.ui                                 ; Push retregb
    push{in1} r1.ui                                 ; Push retregn
    push{in2} retreg_p1.ui, iopr.ui                 ; Push retreg_p1 & iopr
    nop
    nop
    movp{supervisor} ntcsr.ui, r2.ui                ; Get ntcsr
    movp{supervisor} cecsr.ui, r1.ui                ; Get cecsr
    movp{supervisor} dcsr.ui , r0.ui                ; Get dcsr
    nop
    nop
    push{in1} r0.ui                                 ; Push dcsr
    || mov #0x0, r0.ui
    push{in1} r1.ui                                 ; Push cecsr
    push{in1} r2.ui                                 ; Push normal interrupt status (ntcsr)  
    push{in2} prdr.ui, retreg.ui                    ; Push retreg & prdr
    push{in1} r3.ui                                 ; Push retregi
    push{in1} r0.ui                                 ; push argument
    mov sp.ui, r0.ui
    st r0.ui, (#rt_interrupt_from_thread).ui
restore_interrupt_thread_switch:
    ld (#rt_interrupt_to_thread).ui, r0.ui
    nop
    mov r0.ui, sp.ui
    nop #0x4
    nop #0x2
    pop{in1}    r0.ui                               ; pop argument
    pop{in1}    r3.ui                               ; Pop retregi
    pop{in2}    prdr.ui, retreg.ui                  ; Pop retreg & prdr
    pop{in1}    r4.ui                               ; Pop normal interrupt status
    pop{in1}    r1.ui                               ; Pop cecsr
    pop{in1}    r2.ui                               ; Pop dcsr
    pop{in2}    retreg_p1.ui, iopr.ui               ; pop retreg_p1 & iopr
    nop         #0x4
    movp{supervisor} r4.ui, ntcsr.ui                ; Place normal interrupt status
    || pop{in1} r4.ui                               ; pop retregn
    pop{in1}    r5.ui                               ; pop retregb
    || movp{supervisor} r1.ui, cecsr.ui             ; Place cecsr
    pop{in2}    sasr.ui, sfpsr.ui
    || movp{supervisor} r2.ui, dcsr.ui              ; Place dcsr
    pop{in2}    samr.ui, alc.ui
    pop{in2}    fba.ui, iba.ui                      ; Pop special address modes and status
    nop         #0x2
    movp{supervisor} r3.ui,retregi.ui               ; Place retregi
    movp{supervisor} r4.ui,retregn.ui               ; Place retregn
    movp{supervisor} r5.ui,retregb.ui               ; Place retregb
    nop         #0x3
    pop{in4}    r8.di,r9.di,r10.di,r11.di           ; Pop r8 - r11
    pop{in4}    r12.di,r13.di,r14.di,r15.di         ; Pop r12 - r15
    pop{in4}    r16.di,r17.di,r18.di,r19.di         ; Pop r16 - r19
    pop{in4}    r20.di,r21.di,r22.di,r23.di         ; Pop r20 - r23
exit_interrupt_thread_switch:
    eint
    nop
    reti    
.interrupt_thread_switch_END:   
.endfunc
.size interrupt_thread_switch, .interrupt_thread_switch_END-interrupt_thread_switch

;
; rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit);
;
.section CODE_SECTION,"ax",@progbits
.global rt_hw_stack_init
.ceva_prof rt_hw_stack_init, 3
.func rt_hw_stack_init
.p2align  8
rt_hw_stack_init:
    mov r2.ui, r5.ui
    mov sp.ui, r24.ui
    add r5.ui, #8, r5.ui                            ; Align stack address to 4B
    and r5.s2, #0xFFFFFFF0, r5.s2                   ;
    mov r5.ui, sp.ui
    nop #0x4
    nop
    mov #0xdeadbeef, r4.ui
    push{in4} r4.di,r4.di,r4.di,r4.di               ; Push r20 - r23
    push{in4} r4.di,r4.di,r4.di,r4.di               ; Push r16 - r19
    push{in4} r4.di,r4.di,r4.di,r4.di               ; Push r12 - r15
    push{in4} r4.di ,r4.di ,r4.di,r4.di             ; Push r8 - r11
    push{in2} fba.ui, iba.ui                        ; Push special address modes and status
    push{in2} samr.ui, alc.ui                       ; Store arithmetic modes and status registers
    push{in2} sasr.ui, sfpsr.ui                     ;
    movp{supervisor} retregn.ui, r5.ui              ; Place retregn
    movp{supervisor} retregb.ui, r6.ui              ; Place retregb
    push{in1} r6.ui                                 ; Push retregb
    push{in1} r5.ui                                 ; Push retregn
    push{in2} retreg_p1.ui, iopr.ui                 ; Push retreg_p1 & iopr
    nop
    nop
    mov #0x8, r5.ui                                 ; Set ntcsr
    movp{supervisor} cecsr.ui, r6.ui                ; Get cecsr
    movp{supervisor} dcsr.ui , r7.ui                ; Get dcsr
    nop
    nop
    push{in1} r7.ui                                 ; Push dcsr
    push{in1} r6.ui                                 ; Push cecsr
    push{in1} r5.ui                                 ; Push normal interrupt status (ntcsr)  
    push      prdr.ui                               ; Push prdr
    push{in1} r3.ui                                 ; Push retreg
    push{in1} r0.ui                                 ; Push retregi
    push{in1} r1.ui                                 ; push argument
    mov sp.ui, r0.ui
    mov r24.ui, sp.ui
    nop #0x4
    nop #0x2
    ret
.rt_hw_stack_init_END:   
.endfunc
.size rt_hw_stack_init, .rt_hw_stack_init_END-rt_hw_stack_init
