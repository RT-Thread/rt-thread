/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#include <sbi/riscv_locks.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_platform.h>
#include <sbi/sbi_scratch.h>

static const struct sbi_console_device *console_dev = NULL;
static spinlock_t console_out_lock	       = SPIN_LOCK_INITIALIZER;

bool sbi_isprintable(char c)
{
	if (((31 < c) && (c < 127)) || (c == '\f') || (c == '\r') ||
	    (c == '\n') || (c == '\t')) {
		return TRUE;
	}
	return FALSE;
}

int sbi_getc(void)
{
	if (console_dev && console_dev->console_getc)
		return console_dev->console_getc();
	return -1;
}

void sbi_putc(char ch)
{
	if (console_dev && console_dev->console_putc) {
		if (ch == '\n')
			console_dev->console_putc('\r');
		console_dev->console_putc(ch);
	}
}

void sbi_puts(const char *str)
{
	spin_lock(&console_out_lock);
	while (*str) {
		sbi_putc(*str);
		str++;
	}
	spin_unlock(&console_out_lock);
}

void sbi_gets(char *s, int maxwidth, char endchar)
{
	int ch;
	char *retval = s;

	while ((ch = sbi_getc()) != endchar && ch >= 0 && maxwidth > 1) {
		*retval = (char)ch;
		retval++;
		maxwidth--;
	}
	*retval = '\0';
}

#define PAD_RIGHT 1
#define PAD_ZERO 2
#define PAD_ALTERNATE 4
#define PRINT_BUF_LEN 64

#define va_start(v, l) __builtin_va_start((v), l)
#define va_end __builtin_va_end
#define va_arg __builtin_va_arg
typedef __builtin_va_list va_list;

static void printc(char **out, u32 *out_len, char ch)
{
	if (out) {
		if (*out) {
			if (out_len && (0 < *out_len)) {
				**out = ch;
				++(*out);
				(*out_len)--;
			} else {
				**out = ch;
				++(*out);
			}
		}
	} else {
		sbi_putc(ch);
	}
}

static int prints(char **out, u32 *out_len, const char *string, int width,
		  int flags)
{
	int pc	     = 0;
	char padchar = ' ';

	if (width > 0) {
		int len = 0;
		const char *ptr;
		for (ptr = string; *ptr; ++ptr)
			++len;
		if (len >= width)
			width = 0;
		else
			width -= len;
		if (flags & PAD_ZERO)
			padchar = '0';
	}
	if (!(flags & PAD_RIGHT)) {
		for (; width > 0; --width) {
			printc(out, out_len, padchar);
			++pc;
		}
	}
	for (; *string; ++string) {
		printc(out, out_len, *string);
		++pc;
	}
	for (; width > 0; --width) {
		printc(out, out_len, padchar);
		++pc;
	}

	return pc;
}

static int printi(char **out, u32 *out_len, long long i, int b, int sg,
		  int width, int flags, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	char *s;
	int neg = 0, pc = 0;
	u64 t;
	unsigned long long u = i;

	if (sg && b == 10 && i < 0) {
		neg = 1;
		u   = -i;
	}

	s  = print_buf + PRINT_BUF_LEN - 1;
	*s = '\0';

	if (!u) {
		*--s = '0';
	} else {
		while (u) {
			t = u % b;
			u = u / b;
			if (t >= 10)
				t += letbase - '0' - 10;
			*--s = t + '0';
		}
	}

	if (flags & PAD_ALTERNATE) {
		if ((b == 16) && (letbase == 'A')) {
			*--s = 'X';
		} else if ((b == 16) && (letbase == 'a')) {
			*--s = 'x';
		}
		*--s = '0';
	}

	if (neg) {
		if (width && (flags & PAD_ZERO)) {
			printc(out, out_len, '-');
			++pc;
			--width;
		} else {
			*--s = '-';
		}
	}

	return pc + prints(out, out_len, s, width, flags);
}

static int print(char **out, u32 *out_len, const char *format, va_list args)
{
	int width, flags, acnt = 0;
	int pc = 0;
	char scr[2];
	unsigned long long tmp;

	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			width = flags = 0;
			if (*format == '\0')
				break;
			if (*format == '%')
				goto out;
			/* Get flags */
			if (*format == '-') {
				++format;
				flags = PAD_RIGHT;
			}
			if (*format == '#') {
				++format;
				flags |= PAD_ALTERNATE;
			}
			while (*format == '0') {
				++format;
				flags |= PAD_ZERO;
			}
			/* Get width */
			for (; *format >= '0' && *format <= '9'; ++format) {
				width *= 10;
				width += *format - '0';
			}
			if (*format == 's') {
				char *s = va_arg(args, char *);
				acnt += sizeof(char *);
				pc += prints(out, out_len, s ? s : "(null)",
					     width, flags);
				continue;
			}
			if ((*format == 'd') || (*format == 'i')) {
				pc += printi(out, out_len, va_arg(args, int),
					     10, 1, width, flags, '0');
				acnt += sizeof(int);
				continue;
			}
			if (*format == 'x') {
				pc += printi(out, out_len,
					     va_arg(args, unsigned int), 16, 0,
					     width, flags, 'a');
				acnt += sizeof(unsigned int);
				continue;
			}
			if (*format == 'X') {
				pc += printi(out, out_len,
					     va_arg(args, unsigned int), 16, 0,
					     width, flags, 'A');
				acnt += sizeof(unsigned int);
				continue;
			}
			if (*format == 'u') {
				pc += printi(out, out_len,
					     va_arg(args, unsigned int), 10, 0,
					     width, flags, 'a');
				acnt += sizeof(unsigned int);
				continue;
			}
			if (*format == 'p') {
				pc += printi(out, out_len,
					     va_arg(args, unsigned long), 16, 0,
					     width, flags, 'a');
				acnt += sizeof(unsigned long);
				continue;
			}
			if (*format == 'P') {
				pc += printi(out, out_len,
					     va_arg(args, unsigned long), 16, 0,
					     width, flags, 'A');
				acnt += sizeof(unsigned long);
				continue;
			}
			if (*format == 'l' && *(format + 1) == 'l') {
				while (acnt &
				       (sizeof(unsigned long long) - 1)) {
					va_arg(args, int);
					acnt += sizeof(int);
				}
				if (sizeof(unsigned long long) ==
				    sizeof(unsigned long)) {
					tmp = va_arg(args, unsigned long long);
					acnt += sizeof(unsigned long long);
				} else {
					((unsigned long *)&tmp)[0] =
						va_arg(args, unsigned long);
					((unsigned long *)&tmp)[1] =
						va_arg(args, unsigned long);
					acnt += 2 * sizeof(unsigned long);
				}
				if (*(format + 2) == 'u') {
					format += 2;
					pc += printi(out, out_len, tmp, 10, 0,
						     width, flags, 'a');
				} else if (*(format + 2) == 'x') {
					format += 2;
					pc += printi(out, out_len, tmp, 16, 0,
						     width, flags, 'a');
				} else if (*(format + 2) == 'X') {
					format += 2;
					pc += printi(out, out_len, tmp, 16, 0,
						     width, flags, 'A');
				} else {
					format += 1;
					pc += printi(out, out_len, tmp, 10, 1,
						     width, flags, '0');
				}
				continue;
			} else if (*format == 'l') {
				if (*(format + 1) == 'u') {
					format += 1;
					pc += printi(
						out, out_len,
						va_arg(args, unsigned long), 10,
						0, width, flags, 'a');
				} else if (*(format + 1) == 'x') {
					format += 1;
					pc += printi(
						out, out_len,
						va_arg(args, unsigned long), 16,
						0, width, flags, 'a');
					acnt += sizeof(unsigned long);
				} else if (*(format + 1) == 'X') {
					format += 1;
					pc += printi(
						out, out_len,
						va_arg(args, unsigned long), 16,
						0, width, flags, 'A');
					acnt += sizeof(unsigned long);
				} else {
					pc += printi(out, out_len,
						     va_arg(args, long), 10, 1,
						     width, flags, '0');
					acnt += sizeof(long);
				}
			}
			if (*format == 'c') {
				/* char are converted to int then pushed on the stack */
				scr[0] = va_arg(args, int);
				scr[1] = '\0';
				pc += prints(out, out_len, scr, width, flags);
				acnt += sizeof(int);
				continue;
			}
		} else {
		out:
			printc(out, out_len, *format);
			++pc;
		}
	}
	if (out)
		**out = '\0';

	return pc;
}

int sbi_sprintf(char *out, const char *format, ...)
{
	va_list args;
	int retval;

	va_start(args, format);
	retval = print(&out, NULL, format, args);
	va_end(args);

	return retval;
}

int sbi_snprintf(char *out, u32 out_sz, const char *format, ...)
{
	va_list args;
	int retval;

	va_start(args, format);
	retval = print(&out, &out_sz, format, args);
	va_end(args);

	return retval;
}

int sbi_printf(const char *format, ...)
{
	va_list args;
	int retval;

	spin_lock(&console_out_lock);
	va_start(args, format);
	retval = print(NULL, NULL, format, args);
	va_end(args);
	spin_unlock(&console_out_lock);

	return retval;
}

int sbi_dprintf(const char *format, ...)
{
	va_list args;
	int retval = 0;
	struct sbi_scratch *scratch = sbi_scratch_thishart_ptr();

	va_start(args, format);
	if (scratch->options & SBI_SCRATCH_DEBUG_PRINTS)
		retval = print(NULL, NULL, format, args);
	va_end(args);

	return retval;
}

const struct sbi_console_device *sbi_console_get_device(void)
{
	return console_dev;
}

void sbi_console_set_device(const struct sbi_console_device *dev)
{
	if (!dev || console_dev)
		return;

	console_dev = dev;
}

int sbi_console_init(struct sbi_scratch *scratch)
{
	return sbi_platform_console_init(sbi_platform_ptr(scratch));
}
