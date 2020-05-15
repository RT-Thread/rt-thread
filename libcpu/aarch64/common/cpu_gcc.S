/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei    the first version
 */
 
.text
.globl rt_hw_get_current_el
rt_hw_get_current_el:
	MRS		X0, CurrentEL
	CMP		X0, 0xc
	B.EQ	3f
	CMP		X0, 0x8
	B.EQ	2f
	CMP		X0, 0x4
	B.EQ	1f
	
	LDR		X0, =0
	B		0f
3:
	LDR		X0, =3
	B		0f
2:
	LDR		X0, =2
	B		0f
1:
	LDR		X0, =1
	B		0f
0:
	RET


.globl rt_hw_set_current_vbar
rt_hw_set_current_vbar:
	MRS		X1, CurrentEL
	CMP		X1, 0xc
	B.EQ	3f
	CMP		X1, 0x8
	B.EQ	2f
	CMP		X1, 0x4
	B.EQ	1f
	B		0f
3:
	MSR		VBAR_EL3,X0
	B		0f
2:
	MSR		VBAR_EL2,X0
	B		0f
1:
	MSR		VBAR_EL1,X0
	B		0f
0:
	RET

    
.globl rt_hw_set_elx_env
rt_hw_set_elx_env:
	MRS		X1, CurrentEL
	CMP		X1, 0xc
	B.EQ	3f
	CMP		X1, 0x8
	B.EQ	2f
	CMP		X1, 0x4
	B.EQ	1f
	B		0f
3:
	MRS		X0, SCR_EL3
	ORR		X0, X0, #0xF			/* SCR_EL3.NS|IRQ|FIQ|EA */
	MSR		SCR_EL3, X0
	B		0f
2:
	MRS	X0, HCR_EL2
	ORR	X0, X0, #0x38
	MSR	HCR_EL2, X0
	B		0f
1:
	B		0f
0:
	RET
