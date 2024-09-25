/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_UNPRIV_H__
#define __SBI_UNPRIV_H__

#include <sbi/sbi_types.h>

struct sbi_scratch;
struct sbi_trap_info;

#define DECLARE_UNPRIVILEGED_LOAD_FUNCTION(type)           \
	type sbi_load_##type(const type *addr,             \
			     struct sbi_trap_info *trap);

#define DECLARE_UNPRIVILEGED_STORE_FUNCTION(type)          \
	void sbi_store_##type(type *addr, type val,        \
			      struct sbi_trap_info *trap);

DECLARE_UNPRIVILEGED_LOAD_FUNCTION(u8)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(u16)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(s8)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(s16)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(s32)
DECLARE_UNPRIVILEGED_STORE_FUNCTION(u8)
DECLARE_UNPRIVILEGED_STORE_FUNCTION(u16)
DECLARE_UNPRIVILEGED_STORE_FUNCTION(u32)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(u32)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(u64)
DECLARE_UNPRIVILEGED_STORE_FUNCTION(u64)
DECLARE_UNPRIVILEGED_LOAD_FUNCTION(ulong)

ulong sbi_get_insn(ulong mepc, struct sbi_trap_info *trap);

#endif
