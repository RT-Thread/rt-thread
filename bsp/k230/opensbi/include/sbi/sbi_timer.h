/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_TIMER_H__
#define __SBI_TIMER_H__

#include <sbi/sbi_types.h>

/** Timer hardware device */
struct sbi_timer_device {
	/** Name of the timer operations */
	char name[32];

	/** Get free-running timer value */
	u64 (*timer_value)(void);

	/** Start timer event for current HART */
	void (*timer_event_start)(u64 next_event);

	/** Stop timer event for current HART */
	void (*timer_event_stop)(void);
};

struct sbi_scratch;

/** Get timer value for current HART */
u64 sbi_timer_value(void);

/** Get virtualized timer value for current HART */
u64 sbi_timer_virt_value(void);

/** Get timer delta value for current HART */
u64 sbi_timer_get_delta(void);

/** Set timer delta value for current HART */
void sbi_timer_set_delta(ulong delta);

/** Set upper 32-bits of timer delta value for current HART */
void sbi_timer_set_delta_upper(ulong delta_upper);

/** Start timer event for current HART */
void sbi_timer_event_start(u64 next_event);

/** Process timer event for current HART */
void sbi_timer_process(void);

/** Get current timer device */
const struct sbi_timer_device *sbi_timer_get_device(void);

/** Register timer device */
void sbi_timer_set_device(const struct sbi_timer_device *dev);

/* Initialize timer */
int sbi_timer_init(struct sbi_scratch *scratch, bool cold_boot);

/* Exit timer */
void sbi_timer_exit(struct sbi_scratch *scratch);

#endif
