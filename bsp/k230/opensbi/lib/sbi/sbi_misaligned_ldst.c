/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_encoding.h>
#include <sbi/riscv_fp.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_misaligned_ldst.h>
#include <sbi/sbi_trap.h>
#include <sbi/sbi_unpriv.h>

union reg_data {
	u8 data_bytes[8];
	ulong data_ulong;
	u64 data_u64;
};

int sbi_misaligned_load_handler(ulong addr, ulong tval2, ulong tinst,
				struct sbi_trap_regs *regs)
{
	ulong insn, insn_len;
	union reg_data val;
	struct sbi_trap_info uptrap;
	int i, fp = 0, shift = 0, len = 0;

	if (tinst & 0x1) {
		/*
		 * Bit[0] == 1 implies trapped instruction value is
		 * transformed instruction or custom instruction.
		 */
		insn = tinst | INSN_16BIT_MASK;
		insn_len = (tinst & 0x2) ? INSN_LEN(insn) : 2;
	} else {
		/*
		 * Bit[0] == 0 implies trapped instruction value is
		 * zero or special value.
		 */
		insn = sbi_get_insn(regs->mepc, &uptrap);
		if (uptrap.cause) {
			uptrap.epc = regs->mepc;
			return sbi_trap_redirect(regs, &uptrap);
		}
		insn_len = INSN_LEN(insn);
	}

	if ((insn & INSN_MASK_LW) == INSN_MATCH_LW) {
		len   = 4;
		shift = 8 * (sizeof(ulong) - len);
#if __riscv_xlen == 64
	} else if ((insn & INSN_MASK_LD) == INSN_MATCH_LD) {
		len   = 8;
		shift = 8 * (sizeof(ulong) - len);
	} else if ((insn & INSN_MASK_LWU) == INSN_MATCH_LWU) {
		len = 4;
#endif
#ifdef __riscv_flen
	} else if ((insn & INSN_MASK_FLD) == INSN_MATCH_FLD) {
		fp  = 1;
		len = 8;
	} else if ((insn & INSN_MASK_FLW) == INSN_MATCH_FLW) {
		fp  = 1;
		len = 4;
#endif
	} else if ((insn & INSN_MASK_LH) == INSN_MATCH_LH) {
		len   = 2;
		shift = 8 * (sizeof(ulong) - len);
	} else if ((insn & INSN_MASK_LHU) == INSN_MATCH_LHU) {
		len = 2;
#if __riscv_xlen >= 64
	} else if ((insn & INSN_MASK_C_LD) == INSN_MATCH_C_LD) {
		len   = 8;
		shift = 8 * (sizeof(ulong) - len);
		insn  = RVC_RS2S(insn) << SH_RD;
	} else if ((insn & INSN_MASK_C_LDSP) == INSN_MATCH_C_LDSP &&
		   ((insn >> SH_RD) & 0x1f)) {
		len   = 8;
		shift = 8 * (sizeof(ulong) - len);
#endif
	} else if ((insn & INSN_MASK_C_LW) == INSN_MATCH_C_LW) {
		len   = 4;
		shift = 8 * (sizeof(ulong) - len);
		insn  = RVC_RS2S(insn) << SH_RD;
	} else if ((insn & INSN_MASK_C_LWSP) == INSN_MATCH_C_LWSP &&
		   ((insn >> SH_RD) & 0x1f)) {
		len   = 4;
		shift = 8 * (sizeof(ulong) - len);
#ifdef __riscv_flen
	} else if ((insn & INSN_MASK_C_FLD) == INSN_MATCH_C_FLD) {
		fp   = 1;
		len  = 8;
		insn = RVC_RS2S(insn) << SH_RD;
	} else if ((insn & INSN_MASK_C_FLDSP) == INSN_MATCH_C_FLDSP) {
		fp  = 1;
		len = 8;
#if __riscv_xlen == 32
	} else if ((insn & INSN_MASK_C_FLW) == INSN_MATCH_C_FLW) {
		fp   = 1;
		len  = 4;
		insn = RVC_RS2S(insn) << SH_RD;
	} else if ((insn & INSN_MASK_C_FLWSP) == INSN_MATCH_C_FLWSP) {
		fp  = 1;
		len = 4;
#endif
#endif
	} else {
		uptrap.epc = regs->mepc;
		uptrap.cause = CAUSE_MISALIGNED_LOAD;
		uptrap.tval = addr;
		uptrap.tval2 = tval2;
		uptrap.tinst = tinst;
		return sbi_trap_redirect(regs, &uptrap);
	}

	val.data_u64 = 0;
	for (i = 0; i < len; i++) {
		val.data_bytes[i] = sbi_load_u8((void *)(addr + i),
						&uptrap);
		if (uptrap.cause) {
			uptrap.epc = regs->mepc;
			return sbi_trap_redirect(regs, &uptrap);
		}
	}

	if (!fp)
		SET_RD(insn, regs, ((long)(val.data_ulong << shift)) >> shift);
#ifdef __riscv_flen
	else if (len == 8)
		SET_F64_RD(insn, regs, val.data_u64);
	else
		SET_F32_RD(insn, regs, val.data_ulong);
#endif

	regs->mepc += insn_len;

	return 0;
}

int sbi_misaligned_store_handler(ulong addr, ulong tval2, ulong tinst,
				 struct sbi_trap_regs *regs)
{
	ulong insn, insn_len;
	union reg_data val;
	struct sbi_trap_info uptrap;
	int i, len = 0;

	if (tinst & 0x1) {
		/*
		 * Bit[0] == 1 implies trapped instruction value is
		 * transformed instruction or custom instruction.
		 */
		insn = tinst | INSN_16BIT_MASK;
		insn_len = (tinst & 0x2) ? INSN_LEN(insn) : 2;
	} else {
		/*
		 * Bit[0] == 0 implies trapped instruction value is
		 * zero or special value.
		 */
		insn = sbi_get_insn(regs->mepc, &uptrap);
		if (uptrap.cause) {
			uptrap.epc = regs->mepc;
			return sbi_trap_redirect(regs, &uptrap);
		}
		insn_len = INSN_LEN(insn);
	}

	val.data_ulong = GET_RS2(insn, regs);

	if ((insn & INSN_MASK_SW) == INSN_MATCH_SW) {
		len = 4;
#if __riscv_xlen == 64
	} else if ((insn & INSN_MASK_SD) == INSN_MATCH_SD) {
		len = 8;
#endif
#ifdef __riscv_flen
	} else if ((insn & INSN_MASK_FSD) == INSN_MATCH_FSD) {
		len	     = 8;
		val.data_u64 = GET_F64_RS2(insn, regs);
	} else if ((insn & INSN_MASK_FSW) == INSN_MATCH_FSW) {
		len	       = 4;
		val.data_ulong = GET_F32_RS2(insn, regs);
#endif
	} else if ((insn & INSN_MASK_SH) == INSN_MATCH_SH) {
		len = 2;
#if __riscv_xlen >= 64
	} else if ((insn & INSN_MASK_C_SD) == INSN_MATCH_C_SD) {
		len	       = 8;
		val.data_ulong = GET_RS2S(insn, regs);
	} else if ((insn & INSN_MASK_C_SDSP) == INSN_MATCH_C_SDSP &&
		   ((insn >> SH_RD) & 0x1f)) {
		len	       = 8;
		val.data_ulong = GET_RS2C(insn, regs);
#endif
	} else if ((insn & INSN_MASK_C_SW) == INSN_MATCH_C_SW) {
		len	       = 4;
		val.data_ulong = GET_RS2S(insn, regs);
	} else if ((insn & INSN_MASK_C_SWSP) == INSN_MATCH_C_SWSP &&
		   ((insn >> SH_RD) & 0x1f)) {
		len	       = 4;
		val.data_ulong = GET_RS2C(insn, regs);
#ifdef __riscv_flen
	} else if ((insn & INSN_MASK_C_FSD) == INSN_MATCH_C_FSD) {
		len	     = 8;
		val.data_u64 = GET_F64_RS2S(insn, regs);
	} else if ((insn & INSN_MASK_C_FSDSP) == INSN_MATCH_C_FSDSP) {
		len	     = 8;
		val.data_u64 = GET_F64_RS2C(insn, regs);
#if __riscv_xlen == 32
	} else if ((insn & INSN_MASK_C_FSW) == INSN_MATCH_C_FSW) {
		len	       = 4;
		val.data_ulong = GET_F32_RS2S(insn, regs);
	} else if ((insn & INSN_MASK_C_FSWSP) == INSN_MATCH_C_FSWSP) {
		len	       = 4;
		val.data_ulong = GET_F32_RS2C(insn, regs);
#endif
#endif
	} else {
		uptrap.epc = regs->mepc;
		uptrap.cause = CAUSE_MISALIGNED_STORE;
		uptrap.tval = addr;
		uptrap.tval2 = tval2;
		uptrap.tinst = tinst;
		return sbi_trap_redirect(regs, &uptrap);
	}

	for (i = 0; i < len; i++) {
		sbi_store_u8((void *)(addr + i), val.data_bytes[i],
			     &uptrap);
		if (uptrap.cause) {
			uptrap.epc = regs->mepc;
			return sbi_trap_redirect(regs, &uptrap);
		}
	}

	regs->mepc += insn_len;

	return 0;
}
