.cpu cortex-m4
.syntax unified
.thumb
.text

.global DebugMon_Handler
.type DebugMon_Handler, %function
DebugMon_Handler:
    mrs     r0,psp                  ;// Get process stack
    sub     r1,r0,#(4*13)           ;// Make space for saved state
    msr     psp,r1                  ;// Ensure PSP is up to date

    mov     r12,r0                  ;// R12 = stack
    mov     r1,#1                   ;// R1 = exception state type
    mrs     r2,ipsr                 ;// R2 = vector number
    mrs     r3,basepri              ;// R3 = basepri
    stmfd   r0!,{r1-r12,lr}         ;// Push type, vector, basepri, r4-11 

    mov     r4,r0                   ;// R4 = saved state pointer
    bl      rt_hw_debugmon_exception

    mov     r0,r4                   ;// R4 = saved state pointer
    ldmfd   r0!,{r1-r12,lr}         ;// Pop type, vec, basepri, registers and LR
    msr     psp,r0                  ;// Restore PSP
    msr     basepri,r3              ;// Restore basepri

    bx      lr                      ;// Return
