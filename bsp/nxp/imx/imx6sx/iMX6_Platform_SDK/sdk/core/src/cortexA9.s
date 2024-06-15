/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file cortexA9.s
 * @brief This file contains cortexA9 functions
 *
 */
 
    .code 32
    .section ".text","ax"

/*
 * bool arm_set_interrupt_state(bool enable)
 */
    .global arm_set_interrupt_state
    .func arm_set_interrupt_state
arm_set_interrupt_state:
    mrs             r2,CPSR            @ read CPSR (Current Program Status Register)
    teq     r0,#0
    bicne   r1,r2,#0xc0        @ disable IRQ and FIQ
    orreq   r1,r2,#0xc0        @ enable IRQ and FIQ
    msr     CPSR_c,r1
    tst     r2,#0x80
    movne   r0,#0
    moveq   r0,#1
    bx      lr
    .endfunc

  .global cpu_get_current
  @ int cpu_get_current(void)@
  @ get current CPU ID
  .func cpu_get_current
cpu_get_current: 
    mrc   p15, 0, r0, c0, c0, 5
    and   r0, r0, #3
	BX	  lr
  .endfunc    @cpu_get_current()@

  .global enable_neon_fpu
  .func enable_neon_fpu
enable_neon_fpu:
	/* set NSACR, both Secure and Non-secure access are allowed to NEON */
	MRC p15, 0, r0, c1, c1, 2
	ORR r0, r0, #(0x3<<10) @ enable fpu/neon
	MCR p15, 0, r0, c1, c1, 2
	/* Set the CPACR for access to CP10 and CP11*/
	LDR r0, =0xF00000
	MCR p15, 0, r0, c1, c0, 2
	/* Set the FPEXC EN bit to enable the FPU */
	MOV r3, #0x40000000 
	@VMSR FPEXC, r3
	MCR p10, 7, r3, c8, c0, 0
  .endfunc

  .global disable_strict_align_check
  .func disable_strict_align_check
disable_strict_align_check:
  	/*Ray's note: disable strict alignment fault checking.
 	without disabling this, data abort will happen when accessing
	the BPB structure of file system since it is packed.*/
    
  	push	{r0, lr}
	
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #(0x1<<1) @clear A bit of SCTLR 
	mcr p15, 0, r0, c1, c0, 0

    pop {r0, pc}
  .endfunc

  .global disable_L1_cache
  .func disable_L1_cache
disable_L1_cache:
    push	{r0-r6, lr}

	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #(0x1<<12) 
	bic r0, r0, #(0x1<<11) 
	bic r0, r0, #(0x1<<2) 
	bic r0, r0, #(0x1<<0) 
	mcr p15, 0, r0, c1, c0, 0

    pop {r0-r6, pc}

  .endfunc

  .global get_arm_private_peripheral_base
  @ uint32_t get_arm_private_peripheral_base(void)@
  .func get_arm_private_peripheral_base
get_arm_private_peripheral_base: 

  @ Get base address of private perpherial space
  mrc     p15, 4, r0, c15, c0, 0  @ Read periph base address
  bx      lr
  
  .endfunc    @get_arm_private_peripheral_base()@

@ ------------------------------------------------------------
@ TLB
@ ------------------------------------------------------------

  .global arm_unified_tlb_invalidate
  @ void arm_unified_tlb_invalidate(void)@
  .func arm_unified_tlb_invalidate
arm_unified_tlb_invalidate:
  mov     r0, #1
  mcr     p15, 0, r0, c8, c7, 0                 @ TLBIALL - Invalidate entire unified TLB
  dsb
  bx      lr
  .endfunc

  .global arm_unified_tlb_invalidate_is
  @ void arm_unified_tlb_invalidate_is(void)@
  .func arm_unified_tlb_invalidate_is
arm_unified_tlb_invalidate_is:
  mov     r0, #1
  mcr     p15, 0, r0, c8, c3, 0                 @ TLBIALLIS - Invalidate entire unified TLB Inner Shareable
  dsb
  bx      lr
  .endfunc

@ ------------------------------------------------------------
@ Branch Prediction
@ ------------------------------------------------------------

  .global arm_branch_prediction_enable
  @ void arm_branch_prediction_enable(void)
  .func arm_branch_prediction_enable
arm_branch_prediction_enable:
  mrc     p15, 0, r0, c1, c0, 0                 @ Read SCTLR
  orr     r0, r0, #(1 << 11)                    @ Set the Z bit (bit 11)
  mcr     p15, 0,r0, c1, c0, 0                  @ Write SCTLR
  bx      lr
  .endfunc

  .global arm_branch_prediction_disable
  @ void arm_branch_prediction_disable(void)
  .func arm_branch_prediction_disable
arm_branch_prediction_disable:
  mrc     p15, 0, r0, c1, c0, 0                 @ Read SCTLR
  bic     r0, r0, #(1 << 11)                    @ Clear the Z bit (bit 11)
  mcr     p15, 0,r0, c1, c0, 0                  @ Write SCTLR
  bx      lr
  .endfunc
  
  .global arm_branch_target_cache_invalidate
  @ void arm_branch_target_cache_invalidate(void)
  .func arm_branch_target_cache_invalidate
arm_branch_target_cache_invalidate:
  mov     r0, #0
  mcr     p15, 0, r0, c7, c5, 6                 @ BPIALL - Invalidate entire branch predictor array
  bx      lr
  .endfunc

  .global arm_branch_target_cache_invalidate_is
  @ void arm_branch_target_cache_invalidate_is(void)
  .func arm_branch_target_cache_invalidate_is
arm_branch_target_cache_invalidate_is:
  mov     r0, #0
  mcr     p15, 0, r0, c7, c1, 6                 @ BPIALLIS - Invalidate entire branch predictor array Inner Shareable
  bx      lr
  .endfunc

@ ------------------------------------------------------------
@ SCU
@ ------------------------------------------------------------

  @ SCU offset from base of private peripheral space --> 0x000

  .global scu_enable
  @ void scu_enable(void)
  @ Enables the SCU
  .func scu_enable
scu_enable:

  mrc     p15, 4, r0, c15, c0, 0  @ Read periph base address

  ldr     r1, [r0, #0x0]          @ Read the SCU Control Register
  orr     r1, r1, #0x1            @ Set bit 0 (The Enable bit)
  str     r1, [r0, #0x0]          @ Write back modifed value

  bx      lr
  .endfunc

@ ------------------------------------------------------------

  .global  scu_join_smp
  @ void scu_join_smp(void)
  @ Set this CPU as participating in SMP
  .func scu_join_smp
scu_join_smp:

  @ SMP status is controlled by bit 6 of the CP15 Aux Ctrl Reg

  mrc     p15, 0, r0, c1, c0, 1   @ Read ACTLR
  orr     r0, r0, #0x040          @ Set bit 6
  mcr     p15, 0, r0, c1, c0, 1   @ Write ACTLR

  bx      lr
  .endfunc

@ ------------------------------------------------------------

  .global scu_leave_smp
  @ void scu_leave_smp(void)
  @ Set this CPU as NOT participating in SMP
  .func scu_leave_smp
scu_leave_smp:

  @ SMP status is controlled by bit 6 of the CP15 Aux Ctrl Reg

  mrc     p15, 0, r0, c1, c0, 1   @ Read ACTLR
  bic     r0, r0, #0x040          @ Clear bit 6
  mcr     p15, 0, r0, c1, c0, 1   @ Write ACTLR

  bx      lr
  .endfunc

@ ------------------------------------------------------------

  .global scu_get_cpus_in_smp
  @ unsigned int scu_get_cpus_in_smp(void)
  @ The return value is 1 bit per core:
  @ bit 0 - CPU 0
  @ bit 1 - CPU 1
  @ etc...
  .func scu_get_cpus_in_smp
scu_get_cpus_in_smp:

  mrc     p15, 4, r0, c15, c0, 0  @ Read periph base address

  ldr     r0, [r0, #0x004]        @ Read SCU Configuration register
  mov     r0, r0, lsr #4          @ Bits 7:4 gives the cores in SMP mode, shift then mask
  and     r0, r0, #0x0F

  bx      lr
  .endfunc

@ ------------------------------------------------------------

  .global scu_enable_maintenance_broadcast
  @ void scu_enable_maintenance_broadcast(void)
  @ Enable the broadcasting of cache & TLB maintenance operations
  @ When enabled AND in SMP, broadcast all "inner sharable"
  @ cache and TLM maintenance operations to other SMP cores
  .func scu_enable_maintenance_broadcast
scu_enable_maintenance_broadcast:
  mrc     p15, 0, r0, c1, c0, 1   @ Read Aux Ctrl register
  orr     r0, r0, #0x01           @ Set the FW bit (bit 0)
  mcr     p15, 0, r0, c1, c0, 1   @ Write Aux Ctrl register

  bx      lr
  .endfunc

@ ------------------------------------------------------------

  .global scu_disable_maintenance_broadcast
  @ void scu_disable_maintenance_broadcast(void)
  @ Disable the broadcasting of cache & TLB maintenance operations
  .func scu_disable_maintenance_broadcast
scu_disable_maintenance_broadcast:
  mrc     p15, 0, r0, c1, c0, 1   @ Read Aux Ctrl register
  bic     r0, r0, #0x01           @ Clear the FW bit (bit 0)
  mcr     p15, 0, r0, c1, c0, 1   @ Write Aux Ctrl register

  bx      lr
  .endfunc

@ ------------------------------------------------------------

  .global scu_secure_invalidate
  @ void scu_secure_invalidate(unsigned int cpu, unsigned int ways)
  @ cpu: 0x0=CPU 0 0x1=CPU 1 etc...
  @ This function invalidates the SCU copy of the tag rams
  @ for the specified core.  typically only done at start-up.
  @ Possible flow:
  @ - Invalidate L1 caches
  @ - Invalidate SCU copy of TAG RAMs
  @ - Join SMP
  .func scu_secure_invalidate
scu_secure_invalidate:
  and     r0, r0, #0x03           @ Mask off unused bits of CPU ID
  mov     r0, r0, lsl #2          @ Convert into bit offset (four bits per core)
  
  and     r1, r1, #0x0F           @ Mask off unused bits of ways
  mov     r1, r1, lsl r0          @ Shift ways into the correct CPU field

  mrc     p15, 4, r2, c15, c0, 0  @ Read periph base address

  str     r1, [r2, #0x0C]         @ Write to SCU Invalidate All in Secure State
  
  bx      lr

  .endfunc

@ ------------------------------------------------------------
@ End of cortexA9.s
@ ------------------------------------------------------------
    .end
