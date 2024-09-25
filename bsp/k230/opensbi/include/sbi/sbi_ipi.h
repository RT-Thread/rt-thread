/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_IPI_H__
#define __SBI_IPI_H__

#include <sbi/sbi_types.h>

/* clang-format off */

#define SBI_IPI_EVENT_MAX			__riscv_xlen

/* clang-format on */

/** IPI hardware device */
struct sbi_ipi_device {
	/** Name of the IPI device */
	char name[32];

	/** Send IPI to a target HART */
	void (*ipi_send)(u32 target_hart);

	/** Clear IPI for a target HART */
	void (*ipi_clear)(u32 target_hart);
};

struct sbi_scratch;

/** IPI event operations or callbacks */
struct sbi_ipi_event_ops {
	/** Name of the IPI event operations */
	char name[32];

	/**
	 * Update callback to save/enqueue data for remote HART
	 * Note: This is an optional callback and it is called just before
	 * triggering IPI to remote HART.
	 */
	int (* update)(struct sbi_scratch *scratch,
			struct sbi_scratch *remote_scratch,
			u32 remote_hartid, void *data);

	/**
	 * Sync callback to wait for remote HART
	 * Note: This is an optional callback and it is called just after
	 * triggering IPI to remote HART.
	 */
	void (* sync)(struct sbi_scratch *scratch);

	/**
	 * Process callback to handle IPI event
	 * Note: This is a mandatory callback and it is called on the
	 * remote HART after IPI is triggered.
	 */
	void (* process)(struct sbi_scratch *scratch);
};

int sbi_ipi_send_many(ulong hmask, ulong hbase, u32 event, void *data);

int sbi_ipi_event_create(const struct sbi_ipi_event_ops *ops);

void sbi_ipi_event_destroy(u32 event);

int sbi_ipi_send_smode(ulong hmask, ulong hbase);

void sbi_ipi_clear_smode(void);

int sbi_ipi_send_halt(ulong hmask, ulong hbase);

void sbi_ipi_process(void);

void sbi_ipi_raw_send(u32 target_hart);

const struct sbi_ipi_device *sbi_ipi_get_device(void);

void sbi_ipi_set_device(const struct sbi_ipi_device *dev);

int sbi_ipi_init(struct sbi_scratch *scratch, bool cold_boot);

void sbi_ipi_exit(struct sbi_scratch *scratch);

#endif
