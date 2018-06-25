;#**************************************************************************/
;#* FILE NAME: intc_sw_handlers.s            COPYRIGHT (c) Freescale 2016  */
  ;#*                                                All Rights Reserved     */
;#* DESCRIPTION:                                                           */
    ;#*        This file creates prolog, epilog for C ISR and enables nested   */
;#*        interrupts.                                                     */
;#* WARNING:  This stack frame does not save the SPEs Accumulator, which   */
              ;#*           is required if SPE instructions are used in ISRs.   If SPE   */
;#*           instructions are used, the stack frame must include the      */
;#*           accumulator, and prologue and epilogue must be modified.     */
;#=========================================================================*/
#if 0
#define SPRG0	0x110	/* Special Purpose Register General 0 */
#define SPRG1	0x111	/* Special Purpose Register General 1 */

.globl rt_hw_interrupt_disable
.globl rt_hw_interrupt_enable
.globl rt_hw_context_switch
.globl rt_hw_context_switch_to
.globl rt_hw_context_switch_interrupt
.globl rt_hw_systemcall_entry
.globl rt_interrupt_enter
.globl rt_interrupt_leave


.globl   IVOR4_Handler

#ifdef __ghs__
.section    .vletext, axv
.vle
#endif

.equ  INTC_IACKR, 0xFFF48010  ;# Interrupt Acknowledge Register address
.equ  INTC_EOIR,  0xFFF48018   ;# End Of Interrupt Register address

.align 4

IVOR4_Handler:
    prologue:
			e_stwu      r1,-0x50 (r1)           ;# Create stack frame and store back chain
			e_stmvsrrw      0x0c (r1)           ;# Save SRR[0-1] (must be done before enabling MSR[EE])
			se_stw      r3, 0x08 (r1)           ;# Save working register (r3)
			e_lis       r3, INTC_IACKR@ha       ;# Save address  of INTC_IACKR in r3
			e_lwz       r3, INTC_IACKR@l(r3)    ;# Save contents of INTC_IACKR in r3 (this is vector table address)
			wrteei      1                       ;# Set MSR[EE] (must wait a couple clocks after reading IACKR)
			se_lwz      r3, 0x0(r3)             ;# Read ISR address from Interrupt Vector Table using pointer
			e_stmvsprw      0x14 (r1)           ;# Save CR, LR, CTR, XER
			se_mtLR     r3                      ;# Copy ISR address (from IACKR) to LR for next branch
			e_stmvgprw      0x24 (r1)           ;# Save GPRs, r[0,3-12]
			se_blrl                             ;# Branch to ISR, with return to next instruction (epilogue)

			e_lis     r3,rt_thread_switch_interrput_flag@h
			e_or2i    r3,rt_thread_switch_interrput_flag@l
			e_lwz     r4,0(r3)//获取切换标志
			e_cmpi    cr0,r4,0x0      //By Snikeguo                  /* whether is 0     */
			e_beq     epilogue                          /* no switch, exit  */
			/*rt_thread_switch_interrput_flag等于1的情况下开始切换上下文，这里就是更新*/
			e_li      r4,0x0                              /* set rt_thread_switch_interrput_flag to 0 */
			e_stw     r4,0(r3)

			e_lis     r4,rt_interrupt_to_thread@h
			e_or2i    r4,rt_interrupt_to_thread@l
			e_lwz     r1,0(r4)
			e_lwz     r1,0(r1)

	 epilogue:
			    e_lmvsprw       0x14 (r1)           ;# Restore CR, LR, CTR, XER
			e_lmvgprw       0x24 (r1)           ;# Restore GPRs, r[0,3-12]
			e_lis       r3, INTC_EOIR@ha        ;# Load upper half of INTC_EOIR address to r3
			mbar                                ;# Ensure prior clearing of interrupt flag conmpleted.
			wrteei      0                       ;# Disable interrupts
			e_stw       r3, INTC_EOIR@l(r3)     ;# Load lower half of INTC_EOIR address to r3 and
			;# write contents of r3 to INTC_EOIR
			se_lwz      r3, 0x08 (r1)           ;# Restore working register (r3) (original value)
			e_lmvsrrw       0x0c (r1)           ;# Restore SRR[0-1]
			e_add16i    r1, r1, 0x50            ;# Reclaim stack space
			se_rfi                              ;# End of Interrupt Handler - re-enables interrupts
#endif


