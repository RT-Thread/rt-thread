/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __ICCRISCV__
#include <sys/stat.h>
#endif
#include "hpm_debug_console.h"
#include "hpm_uart_drv.h"

static UART_Type* g_console_uart = NULL;

hpm_stat_t console_init(console_config_t *cfg)
{
    hpm_stat_t stat = status_fail;

    if (cfg->type == CONSOLE_TYPE_UART) {
        uart_config_t config = {0};
        uart_default_config((UART_Type *)cfg->base, &config);
        config.src_freq_in_hz = cfg->src_freq_in_hz;
        config.baudrate = cfg->baudrate;
        stat = uart_init((UART_Type *)cfg->base, &config);
        if (status_success == stat) {
            g_console_uart = (UART_Type *)cfg->base;
        }
    }

    return stat;
}

uint8_t console_receive_byte(void)
{
    uint8_t c;
    while (status_success != uart_receive_byte(g_console_uart, &c)) {
    };
    return c;
}

uint8_t console_try_receive_byte(void)
{
    uint8_t c = 0;

    uart_try_receive_byte(g_console_uart, &c);

    return c;
}

void console_send_byte(uint8_t c)
{
    while (status_success != uart_send_byte(g_console_uart, c)) {
    }
}

#ifdef __SEGGER_RTL_VERSION
#include <stdio.h>
#include "__SEGGER_RTL_Int.h"
static int _stdin_ungot  = EOF;
struct __SEGGER_RTL_FILE_impl { /* NOTE: Provides implementation for FILE */
    int stub; /* only needed so impl has size != 0. */
};

static FILE __SEGGER_RTL_stdin_file  = { 0 };  /* stdin reads from UART */
static FILE __SEGGER_RTL_stdout_file = { 0 };  /* stdout writes to UART */
static FILE __SEGGER_RTL_stderr_file = { 0 };  /* stderr writes to UART */

FILE *stdin  = &__SEGGER_RTL_stdin_file;  /* NOTE: Provide implementation of stdin for RTL. */
FILE *stdout = &__SEGGER_RTL_stdout_file; /* NOTE: Provide implementation of stdout for RTL. */
FILE *stderr = &__SEGGER_RTL_stderr_file; /* NOTE: Provide implementation of stderr for RTL. */

int __SEGGER_RTL_X_file_write(__SEGGER_RTL_FILE *file, const char *data, unsigned int size)
{
    unsigned int count;
    (void)file;
    for (count = 0; count < size; count++) {
        if (data[count] == '\n') {
            while (status_success != uart_send_byte(g_console_uart, '\r')) {
            }
        }
        while (status_success != uart_send_byte(g_console_uart, data[count])) {
        }
    }
    while (status_success != uart_flush(g_console_uart)) {
    }
    return count;

}

int __SEGGER_RTL_X_file_read(__SEGGER_RTL_FILE *file, char *s, unsigned int size)
{
    (void)file;
    (void) size;
    while (status_success != uart_receive_byte(g_console_uart, (uint8_t *)s)) {
    }
    return 1;
}

int __SEGGER_RTL_X_file_stat(__SEGGER_RTL_FILE *stream)
{
    (void) stream;
    return 0;
}

int __SEGGER_RTL_X_file_bufsize(__SEGGER_RTL_FILE *stream)
{
    (void) stream;
    return 1;
}

int __SEGGER_RTL_X_file_unget(__SEGGER_RTL_FILE *stream, int c)
{
    if (stream == stdin) {
        if (c != EOF && _stdin_ungot == EOF) {
            _stdin_ungot = c;
        } else {
            c = EOF;
        }
    } else {
        c = EOF;
    }
    return c;
}

int  __SEGGER_RTL_X_file_flush(__SEGGER_RTL_FILE *__stream)
{
    (void) __stream;
    return 1;
}

#endif

int _write(int file, char *data, int size)
{
    int count;
    (void)file;
    for (count = 0; count < size; count++) {
        if (data[count] == '\n') {
            while (status_success != uart_send_byte(g_console_uart, '\r')) {
            }
        }
        while (status_success != uart_send_byte(g_console_uart, data[count])) {
        }
    }
    while (status_success != uart_flush(g_console_uart)) {
    }
    return count;
}

int _read(int file, char *s, int size)
{
    (void)file;
    (void) size;
    while (status_success != uart_receive_byte(g_console_uart, (uint8_t *)s)) {
    }
    return 1;
}

#ifndef __ICCRISCV__
int _fstat(int file, struct stat *s)
{
    (void) file;
    s->st_mode = S_IFCHR;
    return 0;
}
#else

#ifndef _DLIB_FILE_DESCRIPTOR
#define _DLIB_FILE_DESCRIPTOR 0
#endif

int __write(int file, char *data, int size)
{
    return _write(file, data, size);
}

int __read(int file, char *s, int size)
{
    return _read(file, s, size);
}
#endif
