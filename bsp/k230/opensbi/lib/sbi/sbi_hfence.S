/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 *   Atish Patra <anup.patel@wdc.com>
 */

	/*
	 * HFENCE.GVMA rs1, rs2
	 * HFENCE.GVMA zero, rs2
	 * HFENCE.GVMA rs1
	 * HFENCE.GVMA
	 *
	 * rs1!=zero and rs2!=zero ==> HFENCE.GVMA rs1, rs2
	 * rs1==zero and rs2!=zero ==> HFENCE.GVMA zero, rs2
	 * rs1!=zero and rs2==zero ==> HFENCE.GVMA rs1
	 * rs1==zero and rs2==zero ==> HFENCE.GVMA
	 *
	 * Instruction encoding of HFENCE.GVMA is:
	 * 0110001 rs2(5) rs1(5) 000 00000 1110011
	 */

	.align 3
	.global __sbi_hfence_gvma_vmid_gpa
__sbi_hfence_gvma_vmid_gpa:
	/*
	 * rs1 = a0 (GPA)
	 * rs2 = a1 (VMID)
	 * HFENCE.GVMA a0, a1
	 * 0110001 01011 01010 000 00000 1110011
	 */
	.word 0x62b50073
	ret

	.align 3
	.global __sbi_hfence_gvma_vmid
__sbi_hfence_gvma_vmid:
	/*
	 * rs1 = zero
	 * rs2 = a0 (VMID)
	 * HFENCE.GVMA zero, a0
	 * 0110001 01010 00000 000 00000 1110011
	 */
	.word 0x62a00073
	ret

	.align 3
	.global __sbi_hfence_gvma_gpa
__sbi_hfence_gvma_gpa:
	/*
	 * rs1 = a0 (GPA)
	 * rs2 = zero
	 * HFENCE.GVMA a0
	 * 0110001 00000 01010 000 00000 1110011
	 */
	.word 0x62050073
	ret

	.align 3
	.global __sbi_hfence_gvma_all
__sbi_hfence_gvma_all:
	/*
	 * rs1 = zero
	 * rs2 = zero
	 * HFENCE.GVMA
	 * 0110001 00000 00000 000 00000 1110011
	 */
	.word 0x62000073
	ret

	/*
	 * HFENCE.VVMA rs1, rs2
	 * HFENCE.VVMA zero, rs2
	 * HFENCE.VVMA rs1
	 * HFENCE.VVMA
	 *
	 * rs1!=zero and rs2!=zero ==> HFENCE.VVMA rs1, rs2
	 * rs1==zero and rs2!=zero ==> HFENCE.VVMA zero, rs2
	 * rs1!=zero and rs2==zero ==> HFENCE.VVMA rs1
	 * rs1==zero and rs2==zero ==> HFENCE.vVMA
	 *
	 * Instruction encoding of HFENCE.VVMA is:
	 * 0010001 rs2(5) rs1(5) 000 00000 1110011
	 */

	.align 3
	.global __sbi_hfence_vvma_asid_va
__sbi_hfence_vvma_asid_va:
	/*
	 * rs1 = a0 (VA)
	 * rs2 = a1 (ASID)
	 * HFENCE.VVMA a0, a1
	 * 0010001 01011 01010 000 00000 1110011
	 */
	.word 0x22b50073
	ret

	.align 3
	.global __sbi_hfence_vvma_asid
__sbi_hfence_vvma_asid:
	/*
	 * rs1 = zero
	 * rs2 = a0 (ASID)
	 * HFENCE.VVMA zero, a0
	 * 0010001 01010 00000 000 00000 1110011
	 */
	.word 0x22a00073
	ret

	.align 3
	.global __sbi_hfence_vvma_va
__sbi_hfence_vvma_va:
	/*
	 * rs1 = a0 (VA)
	 * rs2 = zero
	 * HFENCE.VVMA zero, a0
	 * 0010001 00000 01010 000 00000 1110011
	 */
	.word 0x22050073
	ret

	.align 3
	.global __sbi_hfence_vvma_all
__sbi_hfence_vvma_all:
	/*
	 * rs1 = zero
	 * rs2 = zero
	 * HFENCE.VVMA
	 * 0010001 00000 00000 000 00000 1110011
	 */
	.word 0x22000073
	ret
