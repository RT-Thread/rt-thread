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
#include <device/vfs_uart.h>
#include <vfs_err.h>
#include <vfs_register.h>
#include <hal/soc/uart.h>
#include <aos/kernel.h>

#include "bl_uart.h"
#include "hal_uart.h"

#include <blog.h>

typedef struct uart_priv_data {
    aos_mutex_t    mutex;
} uart_priv_data_t;

static int8_t inited;
static uart_dev_t *dev_uart0 = NULL;
static uart_dev_t *dev_uart1 = NULL;
static uart_dev_t *dev_uart2 = NULL;
static uart_dev_t *dev_uart3 = NULL;

static int uart_dev_malloc(uart_dev_t **pdev)
{
    if (*pdev) {
        blog_error("arg err.\r\n");
        return -1;
    }

    *pdev = pvPortMalloc(sizeof(uart_dev_t));
    if (*pdev == 0) {
        blog_error("mem err.\r\n");
        return -1;
    }
    memset(*pdev, 0, sizeof(uart_dev_t));

    (*pdev)->read_block_flag = UART_READ_CFG_NOBLOCK;
    (*pdev)->priv = NULL;
    (*pdev)->priv = pvPortMalloc(sizeof(uart_priv_data_t));
    if ((*pdev)->priv == NULL) {
        blog_error("mem err.\r\n");
        return -1;
    }
    memset((*pdev)->priv, 0, sizeof(uart_priv_data_t));

    return 0;
}

static void uart_dev_setdef(uart_dev_t **pdev, uint8_t id)
{
    if (*pdev == NULL) {
        blog_error("mem err.\r\n");
        return;
    }

    (*pdev)->port = id;
    (*pdev)->read_block_flag = UART_READ_CFG_NOBLOCK;
    
    (*pdev)->config.baud_rate = 2000000;
    (*pdev)->config.data_width = DATA_WIDTH_8BIT;
    (*pdev)->config.parity = NO_PARITY;
    (*pdev)->config.stop_bits = STOP_BITS_1;
    (*pdev)->config.flow_control = FLOW_CONTROL_DISABLED;
    (*pdev)->config.mode = MODE_TX_RX;
}

static int dev_uart_init(uint8_t id, const char *path, uint32_t rx_buf_size, uint32_t tx_buf_size)
{
    uart_dev_t **pdev = NULL;
    int ret;

    if ((id >= 4) || (path == 0)) {
        blog_error("arg err.\r\n");
        return -1;
    }

    switch (id) {
        case 0:
        {
            pdev = &dev_uart0;
        } break;
        case 1:
        {
            pdev = &dev_uart1;
        } break;
        case 2:
        {
            pdev = &dev_uart2;
        } break;
        case 3:
        {
            pdev = &dev_uart3;
        } break;
        default:
        {
            blog_error("err.\r\n");
            return -1;
        } break;
    }

    if (uart_dev_malloc(pdev) != 0) {
        return -1;
    }
    (*pdev)->rx_buf_size = rx_buf_size;
    (*pdev)->tx_buf_size = tx_buf_size;
   // (*pdev)->ring_rx_buffer = pvPortMalloc((*pdev)->rx_buf_size);
   // (*pdev)->ring_tx_buffer = pvPortMalloc((*pdev)->tx_buf_size);

   // if ((*pdev)->ring_rx_buffe == NULL || (*pdev)->ring_rx_buffe == NULL ) {
   //     return -1;
   // }

    uart_dev_setdef(pdev, id);
    ret = aos_register_driver(path, &uart_ops, *pdev);
    if (ret != VFS_SUCCESS) {
        return ret;
    }

    return 0;
}

int32_t hal_uart_send_trigger(uart_dev_t *uart)
{
    bl_uart_int_tx_enable(uart->port);
    return 0;
}

int32_t hal_uart_send_trigger_off(uart_dev_t *uart)
{
    bl_uart_int_tx_disable(uart->port);
    return 0;
}

int32_t hal_uart_init(uart_dev_t *uart)
{
    uart_priv_data_t *data;
    uint8_t parity;

    data = uart->priv;
    if (aos_mutex_new(&(data->mutex))) {
        /*we should assert here?*/
        return -1;
    }

    bl_uart_getdefconfig(uart->port, &parity);

    if (parity == UART_PARITY_NONE) {
        uart->config.parity = NO_PARITY;
    } else if (parity == UART_PARITY_ODD) {
        uart->config.parity = ODD_PARITY;
    } else {
        uart->config.parity = EVEN_PARITY;
    }

    bl_uart_int_enable(uart->port);

    return 0;
}

int vfs_uart_init_simple_mode(uint8_t id, uint8_t pin_tx, uint8_t pin_rx, int baudrate, const char *path)
{
    //bl_uart_flush(id);

    bl_uart_init(id, pin_tx, pin_rx, 255, 255, baudrate);

    if (dev_uart_init(id, path, 128, 128) != 0) {
        blog_error("dev_uart_init err.\r\n");
    }

    return 0;
}

int vfs_uart_init(uint32_t fdt, uint32_t dtb_uart_offset)
{
    dev_uart_init(0, "/dev/ttyS0", 512, 512);
    return 0;
}

int32_t hal_uart_recv_II(uart_dev_t *uart, void *data, uint32_t expect_size, uint32_t *recv_size, uint32_t timeout)
{
    int ch;
    uint32_t counter = 0;

    while (counter < expect_size && (ch = bl_uart_data_recv(uart->port)) >= 0) {
        ((uint8_t*)data)[counter] = ch;
        counter++;
    }

    *recv_size = counter;
    return 0;
}

int32_t hal_uart_send(uart_dev_t *uart, const void *data, uint32_t size, uint32_t timeout)
{
    uint32_t i = 0;

    while (i < size) {
        bl_uart_data_send(uart->port, ((uint8_t*)data)[i]);
        i++;
    }
    return 0;
}

int32_t hal_uart_send_flush(uart_dev_t *uart, uint32_t timeout)
{
    bl_uart_flush(uart->port);                                                                                                                                                                 
    return 0;
}

void hal_uart_setbaud(uart_dev_t *uart, uint32_t baud)
{
    bl_uart_setbaud(uart->port, baud);
}

void hal_uart_setconfig(uart_dev_t *uart, uint32_t baud, hal_uart_parity_t parity)
{
    bl_uart_setconfig(uart->port, baud, parity);
}

int32_t hal_uart_finalize(uart_dev_t *uart)
{
    uart_priv_data_t *data;

    data = uart->priv;
    bl_uart_int_disable(uart->port);
    aos_mutex_free(&(data->mutex));
    return 0;
}

/*TODO better glue for ring buffer?*/
int32_t hal_uart_notify_register(uart_dev_t *uart, hal_uart_int_t type, void (*cb)(void *arg))
{
    if (type == UART_TX_INT) {
        bl_uart_int_tx_notify_register(uart->port, cb, uart);
    } else if (type == UART_RX_INT) {
        bl_uart_int_rx_notify_register(uart->port, cb, uart);
    } else {
        return -1;
    }

    return 0;
}

int32_t hal_uart_notify_unregister(uart_dev_t *uart, hal_uart_int_t type, void (*cb)(void *arg))
{
    if (type == UART_TX_INT) {
        bl_uart_int_tx_notify_unregister(uart->port, cb, uart);
    } else if (type == UART_RX_INT) {
        bl_uart_int_rx_notify_unregister(uart->port, cb, uart);
    } else {
        return -1;
    }

    return 0;
}

