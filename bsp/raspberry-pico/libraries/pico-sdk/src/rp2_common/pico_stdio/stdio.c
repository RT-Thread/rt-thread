/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "pico.h"
#include "pico/mutex.h"
#include "pico/printf.h"
#include "pico/stdio.h"
#include "pico/stdio/driver.h"
#include "pico/time.h"

#if PICO_STDIO_UART
#include "pico/stdio_uart.h"
#endif

#if PICO_STDIO_USB
#include "pico/stdio_usb.h"
#endif

#if PICO_STDIO_SEMIHOSTING
#include "pico/stdio_semihosting.h"
#endif

static stdio_driver_t *drivers;
static stdio_driver_t *filter;

#if PICO_STDOUT_MUTEX
auto_init_mutex(print_mutex);

bool stdout_serialize_begin() {
    int core_num = get_core_num();
    uint32_t owner;
    if (!mutex_try_enter(&print_mutex, &owner)) {
        if (owner == core_num) {
            return false;
        }
        // other core owns the mutex, so lets wait
        mutex_enter_blocking(&print_mutex);
    }
    return true;
}

void stdout_serialize_end() {
    mutex_exit(&print_mutex);
}

#else
static bool print_serialize_begin() {
    return true;
}
static void print_serialize_end() {
}
#endif

static void stdio_out_chars_crlf(stdio_driver_t *driver, const char *s, int len) {
#if PICO_STDIO_ENABLE_CRLF_SUPPORT
    if (!driver->crlf_enabled) {
        driver->out_chars(s, len);
        return;
    }
    int first_of_chunk = 0;
    static const char crlf_str[] = {'\r', '\n'};
    for (int i = 0; i < len; i++) {
        bool prev_char_was_cr = i > 0 ? s[i - 1] == '\r' : driver->last_ended_with_cr;
        if (s[i] == '\n' && !prev_char_was_cr) {
            if (i > first_of_chunk) {
                driver->out_chars(&s[first_of_chunk], i - first_of_chunk);
            }
            driver->out_chars(crlf_str, 2);
            first_of_chunk = i + 1;
        }
    }
    if (first_of_chunk < len) {
        driver->out_chars(&s[first_of_chunk], len - first_of_chunk);
    }
    if (len > 0) {
        driver->last_ended_with_cr = s[len - 1] == '\r';
    }
#else
    driver->out_chars(s, len);
#endif
}

static bool stdio_put_string(const char *s, int len, bool newline) {
    bool serialzed = stdout_serialize_begin();
    if (!serialzed) {
#if PICO_STDIO_IGNORE_NESTED_STDOUT
        return false;
#endif
    }
    if (len == -1) len = strlen(s);
    for (stdio_driver_t *driver = drivers; driver; driver = driver->next) {
        if (!driver->out_chars) continue;
        if (filter && filter != driver) continue;
        stdio_out_chars_crlf(driver, s, len);
        if (newline) {
            const char c = '\n';
            stdio_out_chars_crlf(driver, &c, 1);
        }
    }
    if (serialzed) {
        stdout_serialize_end();
    }
    return len;
}

static int stdio_get_until(char *buf, int len, absolute_time_t until) {
    do {
        // todo round robin might be nice on each call, but then again hopefully
        //  no source will starve the others
        for (stdio_driver_t *driver = drivers; driver; driver = driver->next) {
            if (filter && filter != driver) continue;
            if (driver->in_chars) {
                int read = driver->in_chars(buf, len);
                if (read > 0) {
                    return read;
                }
            }
        }
        // todo maybe a little sleep here?
    } while (!time_reached(until));
    return PICO_ERROR_TIMEOUT;
}

int WRAPPER_FUNC(putchar)(int c) {
    char cc = c;
    stdio_put_string(&cc, 1, false);
    return c;
}

int WRAPPER_FUNC(puts)(const char *s) {
    int len = strlen(s);
    stdio_put_string(s, len, true);
    stdio_flush();
    return len;
}

int _read(int handle, char *buffer, int length) {
    if (handle == 0) {
        return stdio_get_until(buffer, length, at_the_end_of_time);
    }
    return -1;
}

int _write(int handle, char *buffer, int length) {
    if (handle == 1) {
        stdio_put_string(buffer, length, false);
        return length;
    }
    return -1;
}

void stdio_set_driver_enabled(stdio_driver_t *driver, bool enable) {
    stdio_driver_t *prev = drivers;
    for (stdio_driver_t *d = drivers; d; d = d->next) {
        if (d == driver) {
            if (!enable) {
                prev->next = d->next;
                driver->next = NULL;
            }
            return;
        }
        prev = d;
    }
    if (enable) {
        if (prev) prev->next = driver;
        else drivers = driver;
    }
}

void stdio_flush() {
    for (stdio_driver_t *d = drivers; d; d = d->next) {
        if (d->out_flush) d->out_flush();
    }
}

typedef struct stdio_stack_buffer {
    uint used;
    char buf[PICO_STDIO_STACK_BUFFER_SIZE];
} stdio_stack_buffer_t;

static void stdio_stack_buffer_flush(stdio_stack_buffer_t *buffer) {
    if (buffer->used) {
        for (stdio_driver_t *d = drivers; d; d = d->next) {
            if (!d->out_chars) continue;
            if (filter && filter != d) continue;
            stdio_out_chars_crlf(d, buffer->buf, buffer->used);
        }
        buffer->used = 0;
    }
}

static void stdio_buffered_printer(char c, void *arg) {
    stdio_stack_buffer_t *buffer = (stdio_stack_buffer_t *)arg;
    if (buffer->used == PICO_STDIO_STACK_BUFFER_SIZE) {
        stdio_stack_buffer_flush(buffer);
    }
    buffer->buf[buffer->used++] = c;
}

int WRAPPER_FUNC(vprintf)(const char *format, va_list va) {
    bool serialzed = stdout_serialize_begin();
    if (!serialzed) {
#if PICO_STDIO_IGNORE_NESTED_STDOUT
        return 0;
#endif
    }
    int ret;
#if PICO_PRINTF_PICO
    struct stdio_stack_buffer buffer = {.used = 0};
    ret = vfctprintf(stdio_buffered_printer, &buffer, format, va);
    stdio_stack_buffer_flush(&buffer);
    stdio_flush();
#elif PICO_PRINTF_NONE
    extern void printf_none_assert();
    printf_none_assert();
#else
    extern int REAL_FUNC(vprintf)(const char *format, va_list va);
    ret = REAL_FUNC(vprintf)(format, va);
#endif
    if (serialzed) {
        stdout_serialize_end();
    }
    return ret;
}

int __printflike(1, 0) WRAPPER_FUNC(printf)(const char* format, ...)
{
    va_list va;
    va_start(va, format);
    int ret = vprintf(format, va);
    va_end(va);
    return ret;
}

void stdio_init_all() {
    // todo add explicit custom, or registered although you can call stdio_enable_driver explicitly anyway
    // These are well known ones
#if PICO_STDIO_UART
    stdio_uart_init();
#endif

#if PICO_STDIO_SEMIHOSTING
    stdio_semihosting_init();
#endif

#if PICO_STDIO_USB
    stdio_usb_init();
#endif
}

int WRAPPER_FUNC(getchar)() {
    char buf[1];
    if (0 == stdio_get_until(buf, sizeof(buf), at_the_end_of_time)) {
        return PICO_ERROR_TIMEOUT;
    }
    return (uint8_t)buf[0];
}

int getchar_timeout_us(uint32_t timeout_us) {
    char buf[1];
    int rc = stdio_get_until(buf, sizeof(buf), make_timeout_time_us(timeout_us));
    if (rc < 0) return rc;
    assert(rc);
    return (uint8_t)buf[0];
}

void stdio_filter_driver(stdio_driver_t *driver) {
    filter = driver;
}

void stdio_set_translate_crlf(stdio_driver_t *driver, bool enabled) {
#if PICO_STDIO_ENABLE_CRLF_SUPPORT
    if (enabled && !driver->crlf_enabled) {
        driver->last_ended_with_cr = false;
    }
    driver->crlf_enabled = enabled;
#else
    panic_unsupported();
#endif
}
