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
 * 2023-07-27  zhugengyu     flush cache in aarch64-el2 
 *
 */
 
.global _boot
.set FPEXC_EN,		0x40000000		/* FPU enable bit, (1 << 30) */
.org 0
.text

.section .boot,"ax"

_boot:
 	/* hard code aarch64 instruction to flush dcache, refer to rt-thread __asm_flush_dcache_all */
	.long 0xd2800000	/* mov	x0, #0x0 // clean and invaildate d-cache */
	.long 0x1400001a	/* b	<InvalidateFlushDcaches> */

InvalidateFlushDcacheLevel:
	.long 0xd37ff80c	/* lsl	x12, x0, #1 */
	.long 0xd51a000c	/* msr	csselr_el1, x12 */
	.long 0xd5033fdf	/* isb */
	.long 0xd5390006	/* mrs	x6, ccsidr_el1 */
	.long 0x924008c2	/* and	x2, x6, #0x7 */
	.long 0x91001042	/* add	x2, x2, #0x4 */
	.long 0xd2807fe3	/* mov	x3, #0x3ff */
	.long 0x8a460c63	/* and	x3, x3, x6, lsr #3 */
	.long 0x5ac01065	/* clz	w5, w3 */
	.long 0xd28fffe4	/* mov	x4, #0x7fff */
	.long 0x8a463484	/* and	x4, x4, x6, lsr #13 */

InvalidateFlushCacheSet:
	.long 0xaa0303e6	/* mov	x6, x3 */

InvalidateFlushCacheWay:
	.long 0x9ac520c7	/* lsl	x7, x6, x5 */
	.long 0xaa070189	/* orr	x9, x12, x7 */
	.long 0x9ac22087	/* lsl	x7, x4, x2 */
	.long 0xaa070129	/* orr	x9, x9, x7 */
	.long 0x36000061	/* tbz	w1, #0, <InvalidateFlushCacheWay+0x1c> */
	.long 0xd5087649	/* dc	isw, x9 */
	.long 0x14000002	/* b	<InvalidateFlushCacheWay+0x20> */
	.long 0xd5087e49	/* dc	cisw, x9 */
	.long 0xf10004c6	/* subs	x6, x6, #0x1 */
	.long 0x54fffeea	/* b.ge	 <InvalidateFlushCacheWay> */
	.long 0xf1000484	/* subs	x4, x4, #0x1 */
	.long 0x54fffe8a	/* b.ge	 <InvalidateFlushCacheSet> */
	.long 0xd65f03c0	/* ret */

InvalidateFlushDcaches:
	.long 0xaa0003e1	/* mov	x1, x0 */
	.long 0xd5033f9f	/* dsb	sy */
	.long 0xd539002a	/* mrs	x10, clidr_el1 */
	.long 0xd358fd4b	/* lsr	x11, x10, #24 */
	.long 0x9240096b	/* and	x11, x11, #0x7 */
	.long 0xb400024b	/* cbz	x11, <InvalidateFlushDcacheEnd> */
	.long 0xaa1e03ef	/* mov	x15, x30 */
	.long 0xd2800000	/* mov	x0, #0x0 */

InvalidateFlushCachesLoopLevel:
	.long 0xd37ff80c	/* lsl	x12, x0, #1 */
	.long 0x8b00018c	/* add	x12, x12, x0 */
	.long 0x9acc254c	/* lsr	x12, x10, x12 */
	.long 0x9240098c	/* and	x12, x12, #0x7 */
	.long 0xf100099f	/* cmp	x12, #0x2 */
	.long 0x5400004b	/* b.lt	<InvalidateFlushCachesSkipLevel> */
	.long 0x97ffffd9	/* bl	<InvalidateFlushDcacheLevel> */

InvalidateFlushCachesSkipLevel:
	.long 0x91000400	/* add	x0, x0, #0x1 */
	.long 0xeb00017f	/* cmp	x11, x0 */
	.long 0x54fffeec	/* b.gt	<InvalidateFlushCachesLoopLevel> */
	.long 0xd2800000	/* mov	x0, #0x0 */
	.long 0xd51a0000	/* msr	csselr_el1, x0 */
	.long 0xd5033f9f	/* dsb	sy */
	.long 0xd5033fdf	/* isb */
	.long 0xaa0f03fe	/* mov	x30, x15 */

InvalidateFlushDcacheEnd:
/***************************************************************/

/* switch from aarch64-el2 to aarch32-el1 */
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

