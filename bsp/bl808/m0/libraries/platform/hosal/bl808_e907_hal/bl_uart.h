/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __BL_UART_H__
#define __BL_UART_H__
#include <stdint.h>
#define BL_UART_BUFFER_SIZE_MIN   (128)
#define BL_UART_BUFFER_SIZE_MASK  (128 - 1)

typedef void (*cb_uart_notify_t)(void *arg);
int bl_uart_gpio_init(uint8_t id, uint8_t tx, uint8_t rx, uint8_t rts, uint8_t cts, int baudrate);
int bl_uart_init(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin, uint32_t baudrate);
int bl_uart_simple_init(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin, uint32_t baudrate);
int bl_uart_debug_early_init(uint32_t baudrate);
int bl_uart_early_init(uint8_t id, uint8_t tx_pin, uint32_t baudrate);

int bl_uart_int_rx_enable(uint8_t id);
int bl_uart_int_rx_disable(uint8_t id);
int bl_uart_int_tx_enable(uint8_t id);
int bl_uart_int_tx_disable(uint8_t id);
int bl_uart_string_send(uint8_t id, char *data);
int bl_uart_flush(uint8_t id);
void bl_uart_getdefconfig(uint8_t id, uint8_t *parity);
//FIXME fix bl_uart_setconfig
//void bl_uart_setconfig(uint8_t id, uint32_t baudrate, UART_Parity_Type parity);
void bl_uart_setbaud(uint8_t id, uint32_t baud);
int bl_uart_data_send(uint8_t id, uint8_t data);
int bl_uart_datas_send(uint8_t id, uint8_t *data, int len);
int bl_uart_data_recv(uint8_t id);
int bl_uart_int_enable(uint8_t id);
int bl_uart_int_disable(uint8_t id);
int bl_uart_int_rx_notify_register(uint8_t id, cb_uart_notify_t cb, void *arg);
int bl_uart_int_tx_notify_register(uint8_t id, cb_uart_notify_t cb, void *arg);
int bl_uart_int_rx_notify_unregister(uint8_t id, cb_uart_notify_t cb, void *arg);
int bl_uart_int_tx_notify_unregister(uint8_t id, cb_uart_notify_t cb, void *arg);
#endif
