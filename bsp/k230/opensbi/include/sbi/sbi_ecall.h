/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_ECALL_H__
#define __SBI_ECALL_H__

#include <sbi/sbi_types.h>
#include <sbi/sbi_list.h>

#define SBI_ECALL_VERSION_MAJOR		0
#define SBI_ECALL_VERSION_MINOR		3
#define SBI_OPENSBI_IMPID		1

struct sbi_trap_regs;
struct sbi_trap_info;

struct sbi_ecall_extension {
	struct sbi_dlist head;
	unsigned long extid_start;
	unsigned long extid_end;
	int (* probe)(unsigned long extid, unsigned long *out_val);
	int (* handle)(unsigned long extid, unsigned long funcid,
		       const struct sbi_trap_regs *regs,
		       unsigned long *out_val,
		       struct sbi_trap_info *out_trap);
};

extern struct sbi_ecall_extension ecall_base;
extern struct sbi_ecall_extension ecall_legacy;
extern struct sbi_ecall_extension ecall_time;
extern struct sbi_ecall_extension ecall_rfence;
extern struct sbi_ecall_extension ecall_ipi;
extern struct sbi_ecall_extension ecall_vendor;
extern struct sbi_ecall_extension ecall_hsm;
extern struct sbi_ecall_extension ecall_srst;

u16 sbi_ecall_version_major(void);

u16 sbi_ecall_version_minor(void);

unsigned long sbi_ecall_get_impid(void);

void sbi_ecall_set_impid(unsigned long impid);

struct sbi_ecall_extension *sbi_ecall_find_extension(unsigned long extid);

int sbi_ecall_register_extension(struct sbi_ecall_extension *ext);

void sbi_ecall_unregister_extension(struct sbi_ecall_extension *ext);

int sbi_ecall_handler(struct sbi_trap_regs *regs);

int sbi_ecall_init(void);

#endif
