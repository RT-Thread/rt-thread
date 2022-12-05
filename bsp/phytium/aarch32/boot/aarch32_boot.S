/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 * 
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe       first commit 
 *
 */
 
.global _boot
.set FPEXC_EN,		0x40000000		/* FPU enable bit, (1 << 30) */
.org 0
.text

.section .boot,"ax"

/* switch from aarch64-el2 to aarch32-el1 */
_boot:
Startup_Aarch32:
    .long 0xd5384240 	/* mrs	x0, currentel                      */
    .long 0xd342fc00 	/* lsr	x0, x0, #2                         */
    .long 0x92400400 	/* and	x0, x0, #0x3                       */
    .long 0xf1000c1f 	/* cmp	x0, #0x3                           */
    .long 0x540003a1 	/* b.ne	1d0080c4 <el2_mode>                */

el3_mode:
    .long 0xd53ecca0 	/* mrs	x0, s3_6_c12_c12_5 - ICC_SRE_EL3   */
    .long 0xb2400c00 	/* orr	x0, x0, #0xf                       */
    .long 0xd51ecca0 	/* msr	s3_6_c12_c12_5, x0                 */
    .long 0xd5033fdf 	/* isb                                     */
    .long 0xd53cc9a0 	/* mrs	x0, s3_4_c12_c9_5 - ICC_SRE_EL2    */
    .long 0xb2400c00 	/* orr	x0, x0, #0xf                       */
    .long 0xd51cc9a0 	/* msr	s3_4_c12_c9_5, x0                  */
    .long 0xd5033fdf 	/* isb                                     */
    .long 0xd538cca0 	/* mrs	x0, s3_0_c12_c12_5 - ICC_SRE_EL1   */
    .long 0xb2400000 	/* orr	x0, x0, #0x1                       */
    .long 0xd518cca0 	/* msr	s3_0_c12_c12_5, x0                 */
    .long 0xd5033fdf 	/* isb                                     */

    .long 0xd2803620 	/* mov	x0, #0x1b1                         */
    .long 0xd51e1100 	/* msr	scr_el3, x0                        */
    .long 0xd2867fe0 	/* mov	x0, #0x33ff                        */
    .long 0xd51c1140 	/* msr	cptr_el2, x0                       */
    .long 0xd2810000 	/* mov	x0, #0x800                         */
    .long 0xf2a61a00 	/* movk	x0, #0x30d0, lsl #16               */
    .long 0xd5181000 	/* msr	sctlr_el1, x0                      */
    .long 0x910003e0 	/* mov	x0, sp                             */
    .long 0xd51c4100 	/* msr	sp_el1, x0                         */
    .long 0xd53ec000 	/* mrs	x0, vbar_el3                       */
    .long 0xd518c000 	/* msr	vbar_el1, x0                       */
    .long 0xd2803a60 	/* mov	x0, #0x1d3                         */
    .long 0xd51e4000 	/* msr	spsr_el3, x0                       */
    .long 0x10000500 	/* adr	x0, 1d008158 <el1_mode>            */
    .long 0xd51e4020 	/* msr	elr_el3, x0                        */
    .long 0xd69f03e0 	/* eret                                    */

el2_mode:
    .long 0xd53cc9a0 	/* mrs	x0, s3_4_c12_c9_5 - ICC_SRE_EL2    */
    .long 0xb2400c00 	/* orr	x0, x0, #0xf                       */
    .long 0xd51cc9a0 	/* msr	s3_4_c12_c9_5, x0                  */
    .long 0xd5033fdf 	/* isb                                     */
    .long 0xd538cca0 	/* mrs	x0, s3_0_c12_c12_5 - ICC_SRE_EL1   */
    .long 0xb2400000 	/* orr	x0, x0, #0x1                       */
    .long 0xd518cca0 	/* msr	s3_0_c12_c12_5, x0                 */
    .long 0xd5033fdf 	/* isb                                     */
    .long 0xd53ce100 	/* mrs	x0, cnthctl_el2                    */
    .long 0xb2400400 	/* orr	x0, x0, #0x3                       */
    .long 0xd51ce100 	/* msr	cnthctl_el2, x0                    */
    .long 0xd51ce07f 	/* msr	cntvoff_el2, xzr                   */
    .long 0xd5380000 	/* mrs	x0, midr_el1                       */
    .long 0xd53800a1 	/* mrs	x1, mpidr_el1                      */
    .long 0xd51c0000 	/* msr	vpidr_el2, x0                      */
    .long 0xd51c00a1 	/* msr	vmpidr_el2, x1                     */
    .long 0xd2867fe0 	/* mov	x0, #0x33ff                        */
    .long 0xd51c1140 	/* msr	cptr_el2, x0                       */
    .long 0xd51c117f 	/* msr	hstr_el2, xzr                      */
    .long 0xd2a00600 	/* mov	x0, #0x300000                      */
    .long 0xd5181040 	/* msr	cpacr_el1, x0                      */
    .long 0xd2800000 	/* mov	x0, #0x0                           */
    .long 0xb2630000 	/* orr	x0, x0, #0x20000000                */
    .long 0xd51c1100 	/* msr	hcr_el2, x0                        */
    .long 0xd53c1100 	/* mrs	x0, hcr_el2                        */
    .long 0xd2810000 	/* mov	x0, #0x800                         */
    .long 0xf2a61a00 	/* movk	x0, #0x30d0, lsl #16               */
    .long 0xd5181000 	/* msr	sctlr_el1, x0                      */
    .long 0x910003e0 	/* mov	x0, sp                             */
    .long 0xd51c4100 	/* msr	sp_el1, x0                         */
    .long 0xd53cc000 	/* mrs	x0, vbar_el2                       */
    .long 0xd518c000 	/* msr	vbar_el1, x0                       */
    .long 0xd2803a60 	/* mov	x0, #0x1d3                         */
    .long 0xd51c4000 	/* msr	spsr_el2, x0                       */
    .long 0x10000060 	/* adr	x0, 1d008158 <el1_mode>            */
    .long 0xd51c4020 	/* msr	elr_el2, x0                        */
    .long 0xd69f03e0 	/* eret                                    */

el1_mode:
    mov      r0, #0
    mov      r1, #0
    mov      r2, #0
    mov      r3, #0
    mov      r4, #0
    mov      r5, #0
    mov      r6, #0
    mov      r7, #0
    mov      r8, #0
    mov      r9, #0
    mov      r10, #0
    mov      r11, #0
    mov      r12, #0
    mcr      p15, 0, r0, c1, c0, 0  /* reset control register */
    isb

    /* enable vfp, therefore f_prink workable */
    vmrs	r1, FPEXC			/* read the exception register */
    orr	    r1,r1, #FPEXC_EN	/* set VFP enable bit, leave the others in orig state */
    vmsr	FPEXC, r1			/* write back the exception register */

    bl      system_vectors      /* jump to libcpu/arm/cortex-a/vector_gcc.S */

