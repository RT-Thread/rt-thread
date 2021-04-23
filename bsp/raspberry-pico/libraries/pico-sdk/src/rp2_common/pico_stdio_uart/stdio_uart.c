/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdio/driver.h"
#include "pico/stdio_uart.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"

static uart_inst_t *uart_instance;

#if PICO_NO_BI_STDIO_UART
#define stdio_bi_decl_if_func_used(x)
#else
#define stdio_bi_decl_if_func_used bi_decl_if_func_used
#endif

void stdio_uart_init() {
    int tx_pin = -1;
    int rx_pin = -1;
#if defined(PICO_DEFAULT_UART_TX_PIN) && PICO_DEFAULT_UART_TX_PIN != -1
    tx_pin = PICO_DEFAULT_UART_TX_PIN;
#if defined(PICO_DEFAULT_UART_RX_PIN) && PICO_DEFAULT_UART_RX_PIN != -1
    rx_pin = PICO_DEFAULT_UART_RX_PIN;
    stdio_bi_decl_if_func_used(bi_program_feature("UART stdin / stdout"));
    bi_decl_if_func_used(bi_2pins_with_func(PICO_DEFAULT_UART_RX_PIN, PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART));
#else
    stdio_bi_decl_if_func_used(bi_program_feature("UART stdout"));
    bi_decl_if_func_used(bi_1pin_with_func(PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART));
#endif
#elif defined(PICO_DEFAULT_UART_RX_PIN) && PICO_DEFAULT_UART_RX_PIN != -1
    rx_pin = PICO_DEFAULT_UART_RX_PIN;
    stdio_bi_decl_if_func_used(bi_program_feature("UART stdin"));
    bi_decl_if_func_used(bi_1pin_with_func(PICO_DEFAULT_UART_RX_PIN, GPIO_FUNC_UART));
#endif
#if !defined(PICO_DEFAULT_UART_BAUD_RATE) || !defined(uart_default)
    panic("UART baud rate undefined");
#else
    stdio_uart_init_full(uart_default, PICO_DEFAULT_UART_BAUD_RATE, tx_pin, rx_pin);
#endif
}

void stdout_uart_init() {
#ifdef PICO_DEFAULT_UART_TX_PIN
    bi_decl_if_func_used(bi_1pin_with_func(PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART));
#if !defined(PICO_DEFAULT_UART_BAUD_RATE) || !defined(uart_default)
    panic("UART baud rate undefined");
#else
    stdio_bi_decl_if_func_used(bi_program_feature("UART stdout"));
    stdio_uart_init_full(uart_default, PICO_DEFAULT_UART_BAUD_RATE, PICO_DEFAULT_UART_TX_PIN, -1);
#endif
#endif
}

void stdin_uart_init() {
#ifdef PICO_DEFAULT_UART_RX_PIN
    bi_decl_if_func_used(bi_1pin_with_func(PICO_DEFAULT_UART_RX_PIN, GPIO_FUNC_UART));
#if !defined(PICO_DEFAULT_UART_BAUD_RATE) || !defined(uart_default)
    panic("UART baud rate undefined");
#else
    stdio_bi_decl_if_func_used(bi_program_feature("UART stdin"));
    stdio_uart_init_full(uart_default, PICO_DEFAULT_UART_BAUD_RATE, -1, PICO_DEFAULT_UART_RX_PIN);
#endif
#endif
}

void stdio_uart_init_full(struct uart_inst *uart, uint baud_rate, int tx_pin, int rx_pin) {
    uart_instance = uart;
    uart_init(uart_instance, baud_rate);
    if (tx_pin != -1) gpio_set_function(tx_pin, GPIO_FUNC_UART);
    if (rx_pin != -1) gpio_set_function(rx_pin, GPIO_FUNC_UART);
    stdio_set_driver_enabled(&stdio_uart, true);
}

static void stdio_uart_out_chars(const char *buf, int length) {
    for (uint i = 0; i <length; i++) {
        uart_putc(uart_default, buf[i]);
    }
}

int stdio_uart_in_chars(char *buf, int length) {
    int i=0;
    while (i<length && uart_is_readable(uart_default)) {
        buf[i++] = uart_getc(uart_default);
    }
    return i ? i : PICO_ERROR_NO_DATA;
}

stdio_driver_t stdio_uart = {
    .out_chars = stdio_uart_out_chars,
    .in_chars = stdio_uart_in_chars,
#if PICO_STDIO_ENABLE_CRLF_SUPPORT
    .crlf_enabled = PICO_STDIO_UART_DEFAULT_CRLF
#endif
};
