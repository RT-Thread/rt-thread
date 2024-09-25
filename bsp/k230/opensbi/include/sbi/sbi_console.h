/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_CONSOLE_H__
#define __SBI_CONSOLE_H__

#include <sbi/sbi_types.h>

struct sbi_console_device {
	/** Name of the console device */
	char name[32];

	/** Write a character to the console output */
	void (*console_putc)(char ch);

	/** Read a character from the console input */
	int (*console_getc)(void);
};

#define __printf(a, b) __attribute__((format(printf, a, b)))

bool sbi_isprintable(char ch);

int sbi_getc(void);

void sbi_putc(char ch);

void sbi_puts(const char *str);

void sbi_gets(char *s, int maxwidth, char endchar);

int __printf(2, 3) sbi_sprintf(char *out, const char *format, ...);

int __printf(3, 4) sbi_snprintf(char *out, u32 out_sz, const char *format, ...);

int __printf(1, 2) sbi_printf(const char *format, ...);

int __printf(1, 2) sbi_dprintf(const char *format, ...);

const struct sbi_console_device *sbi_console_get_device(void);

void sbi_console_set_device(const struct sbi_console_device *dev);

struct sbi_scratch;

int sbi_console_init(struct sbi_scratch *scratch);

#endif
