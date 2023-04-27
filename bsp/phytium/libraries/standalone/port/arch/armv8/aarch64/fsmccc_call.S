/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: fsmccc-call.S
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:31:23
 * Description:  This file is for initiating SMC call 
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe     2021/7/3     first release
 */

.macro SMCCC instr
	\instr	#0
	ldr	x4, [sp]
	stp	x0, x1, [x4, #0]
	stp	x2, x3, [x4, #16]
	ldr	x4, [sp, #8]
	cbz	x4, 1f /* no quirk structure */
	ldr	x9, [x4, #0]
	cmp	x9, #1
	b.ne	1f
	str	x6, [x4, 4]
1:	ret
.endm SMCCC instr

/*
 * void arm_smccc_smc(unsigned long a0, unsigned long a1, unsigned long a2,
 *		  unsigned long a3, unsigned long a4, unsigned long a5,
 *		  unsigned long a6, unsigned long a7, struct arm_smccc_res *res,
 *		  struct arm_smccc_quirk *quirk)
 */
    .globl __arm_smccc_smc
.type __arm_smccc_smc, "function"
	.cfi_startproc
__arm_smccc_smc:
	SMCCC	smc
	.cfi_endproc
