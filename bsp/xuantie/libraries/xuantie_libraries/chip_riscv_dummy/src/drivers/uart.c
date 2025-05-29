 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     uart.c
 * @brief    CSI Source File for uart Driver
 * @version  V2.01
 * @date     2020-04-09
 ******************************************************************************/

#include <drv/uart.h>
#include <drv/dma.h>
#include <drv/irq.h>
#include <drv/pin.h>
#include <drv/porting.h>
#include <soc.h>
#include <dw_uart_ll.h>
#include <drv/tick.h>

#define UART_TIMEOUT    0x10000000U
#define UART_MAX_FIFO   0x10U

extern uint16_t uart_tx_hs_num[];
extern uint16_t uart_rx_hs_num[];
extern const csi_pinmap_t uart_pinmap[];

static uint8_t find_max_prime_num(uint32_t num)
{
    uint8_t ret;

    if (!(num % 8U)) {
        ret = 8U;
    } else if (!(num % 4U)) {
        ret = 4U;
    } else {
        ret = 1U;
    }

    return ret;
}

static void dw_uart_intr_recv_data(csi_uart_t *uart)
{
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);
    uint32_t rxfifo_num = 1;///<dw_uart_get_receive_fifo_waiting_data(uart_base);
    uint32_t rxdata_num = (rxfifo_num > uart->rx_size) ? uart->rx_size : rxfifo_num;

    if ((uart->rx_data == NULL) || (uart->rx_size == 0U)) {
        if (uart->callback) {
            uart->callback(uart, UART_EVENT_RECEIVE_FIFO_READABLE, uart->arg);
        } else {
            do {
                dw_uart_getchar(uart_base);
            } while (--rxfifo_num);
        }
    } else {
        do {
            *uart->rx_data = dw_uart_getchar(uart_base);
            uart->rx_size--;
            uart->rx_data++;
        } while (--rxdata_num);

        if (uart->rx_size == 0U) {
            uart->state.readable = 1U;

            if (uart->callback) {
                uart->callback(uart, UART_EVENT_RECEIVE_COMPLETE, uart->arg);
            }
        }
    }
}

static void uart_intr_send_data(csi_uart_t *uart)
{
    uint32_t i = 0U, trans_num = 0U;
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)uart->dev.reg_base;

    if (uart->tx_size > UART_MAX_FIFO) {
        trans_num = UART_MAX_FIFO;
    } else {
        trans_num = uart->tx_size;
    }

    for (i = 0U; i < trans_num; i++) {
        //dw_uart_putchar(uart_base, *uart->tx_data);
        csi_uart_putc(uart, *uart->tx_data);
        uart->tx_size--;
        uart->tx_data++;
    }

    if (uart->tx_size == 0U) {
        dw_uart_disable_trans_irq(uart_base);
        uart->state.writeable = 1U;

        if (uart->callback) {
            uart->callback(uart, UART_EVENT_SEND_COMPLETE, uart->arg);
        }
    }
}

static void uart_intr_line_error(csi_uart_t *uart)
{
    uint32_t uart_status;
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    uart->state.readable = 1U;
    uart->state.writeable = 1U;
    uart_status = dw_uart_get_line_status(uart_base);

    if (uart->callback) {
        if (uart_status & DW_UART_LSR_OE_ERROR) {
            uart->callback(uart, UART_EVENT_ERROR_OVERFLOW, uart->arg);
        }

        if (uart_status & DW_UART_LSR_PE_ERROR) {
            uart->callback(uart, UART_EVENT_ERROR_PARITY, uart->arg);
        }

        if (uart_status & DW_UART_LSR_FE_ERROR) {
            uart->callback(uart, UART_EVENT_ERROR_FRAMING, uart->arg);
        }

        if (uart_status & DW_UART_LSR_BI_SET) {
            uart->callback(uart, UART_ENENT_BREAK_INTR, uart->arg);
        }
    }
}

void dw_uart_irq_handler(void *arg)
{
    csi_uart_t *uart = (csi_uart_t *)arg;
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)uart->dev.reg_base;

    uint8_t intr_state;

    intr_state = (uint8_t)(uart_base->IIR & 0xfU);

    switch (intr_state) {
    case DW_UART_IIR_IID_RECV_LINE_STATUS:  /* interrupt source: Overrun/parity/framing errors or break interrupt */
        uart_intr_line_error(uart);
        break;

    case DW_UART_IIR_IID_THR_EMPTY:         /* interrupt source:sendter holding register empty */
        uart_intr_send_data(uart);
        break;

    case DW_UART_IIR_IID_RECV_DATA_AVAIL:   /* interrupt source:receiver data available or receiver fifo trigger level reached */
    case DW_UART_IIR_IID_CHARACTER_TIMEOUT:
        dw_uart_intr_recv_data(uart);
        break;

    default:
        break;
    }
}

csi_error_t csi_uart_init(csi_uart_t *uart, uint32_t idx)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    dw_uart_regs_t *uart_base;

    ret = target_get(DEV_DW_UART_TAG, idx, &uart->dev);

    if (ret == CSI_OK) {
        uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

        dw_uart_fifo_init(uart_base);

        uart->rx_size = 0U;
        uart->tx_size = 0U;
        uart->rx_data = NULL;
        uart->tx_data = NULL;
        uart->tx_dma  = NULL;
        uart->rx_dma  = NULL;
        dw_uart_disable_trans_irq(uart_base);
        dw_uart_disable_recv_irq(uart_base);
        dw_uart_disable_auto_flow_control(uart_base);
    }

    return ret;
}

void csi_uart_uninit(csi_uart_t *uart)
{
    CSI_PARAM_CHK_NORETVAL(uart);

    dw_uart_regs_t *uart_base;
    uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    uart->rx_size = 0U;
    uart->tx_size = 0U;
    uart->rx_data = NULL;
    uart->tx_data = NULL;

    dw_uart_disable_trans_irq(uart_base);
    dw_uart_disable_recv_irq(uart_base);
    csi_irq_disable((uint32_t)(uart->dev.irq_num));
    csi_irq_detach((uint32_t)(uart->dev.irq_num));
}

ATTRIBUTE_DATA csi_error_t csi_uart_baud(csi_uart_t *uart, uint32_t baud)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);

    int32_t ret = 0;
    csi_error_t csi_ret = CSI_OK;
    dw_uart_regs_t *uart_base;
    uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    ret = dw_uart_config_baudrate(uart_base, baud, soc_get_uart_freq((uint32_t)(uart->dev.idx)));

    if (ret == 0) {
        csi_ret = CSI_OK;
    } else {
        csi_ret = CSI_ERROR;
    }

    return csi_ret;
}

csi_error_t csi_uart_format(csi_uart_t *uart,  csi_uart_data_bits_t data_bits,
                            csi_uart_parity_t parity, csi_uart_stop_bits_t stop_bits)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);

    int32_t ret = 0;
    csi_error_t csi_ret = CSI_OK;
    dw_uart_regs_t *uart_base;
    uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    switch (data_bits) {
    case UART_DATA_BITS_5:
        ret = dw_uart_config_data_bits(uart_base, 5U);
        break;

    case UART_DATA_BITS_6:
        ret = dw_uart_config_data_bits(uart_base, 6U);
        break;

    case UART_DATA_BITS_7:
        ret = dw_uart_config_data_bits(uart_base, 7U);
        break;

    case UART_DATA_BITS_8:
        ret = dw_uart_config_data_bits(uart_base, 8U);
        break;

    default:
        ret = -1;
        break;
    }

    if (ret == 0) {
        switch (parity) {
        case UART_PARITY_NONE:
            ret = dw_uart_config_parity_none(uart_base);
            break;

        case UART_PARITY_ODD:
            ret = dw_uart_config_parity_odd(uart_base);
            break;

        case UART_PARITY_EVEN:
            ret = dw_uart_config_parity_even(uart_base);
            break;

        default:
            ret = -1;
            break;
        }

        if (ret == 0) {
            switch (stop_bits) {
            case UART_STOP_BITS_1:
                ret = dw_uart_config_stop_bits(uart_base, 1U);
                break;

            case UART_STOP_BITS_2:
                ret = dw_uart_config_stop_bits(uart_base, 2U);
                break;

            case UART_STOP_BITS_1_5:
                if (data_bits == UART_DATA_BITS_5) {
                    ret = dw_uart_config_stop_bits(uart_base, 2U);
                    break;
                }

            default:
                ret = -1;
                break;
            }

            if (ret != 0) {
                csi_ret = CSI_ERROR;
            }

        } else {
            csi_ret = CSI_ERROR;
        }

    } else {
        csi_ret = CSI_ERROR;
    }

    return csi_ret;
}

csi_error_t csi_uart_flowctrl(csi_uart_t *uart,  csi_uart_flowctrl_t flowctrl)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);
    csi_error_t csi_ret = CSI_OK;
    dw_uart_regs_t *uart_base;
    uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    switch (flowctrl) {
    case UART_FLOWCTRL_CTS:
        dw_uart_wait_idle(uart_base);
        dw_uart_enable_auto_flow_control(uart_base);
        break;

    case UART_FLOWCTRL_RTS_CTS:
        dw_uart_wait_idle(uart_base);
        dw_uart_enable_auto_flow_control(uart_base);
        break;

    case UART_FLOWCTRL_NONE:
        dw_uart_wait_idle(uart_base);
        break;

    case UART_FLOWCTRL_RTS:
    default:
        csi_ret = CSI_UNSUPPORTED;
        break;
    }

    return csi_ret;
}

void csi_uart_putc(csi_uart_t *uart, uint8_t ch)
{
    CSI_PARAM_CHK_NORETVAL(uart);

    volatile int i = 10;
    uint32_t timeout = UART_TIMEOUT;
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    while (!dw_uart_putready(uart_base) && timeout--);

    if (timeout) {
        //FIXME: fix print luanma on irq-mode sometimes. maybe hw bug
        while (i--);
        dw_uart_putchar(uart_base, ch);
    }
}

ATTRIBUTE_DATA uint8_t csi_uart_getc(csi_uart_t *uart)
{
    CSI_PARAM_CHK(uart, 0U);

    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    while (!dw_uart_getready(uart_base));

    return dw_uart_getchar(uart_base);
}

int32_t csi_uart_receive(csi_uart_t *uart, void *data, uint32_t size, uint32_t timeout)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);

    uint8_t *temp_data = (uint8_t *)data;
    int32_t recv_num = 0;
    uint32_t recv_start, timeout_flag = 0U;
    uint32_t intr_en_status;

    recv_start = csi_tick_get_ms();
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)uart->dev.reg_base;
    intr_en_status = dw_uart_get_intr_en_status(uart_base);
    dw_uart_disable_recv_irq(uart_base);

    while (recv_num < (int32_t)size) {
        while (!dw_uart_getready(uart_base)) {
            if ((csi_tick_get_ms() - recv_start) >= timeout) {
                timeout_flag = 1U;
                break;
            }
        };

        if (timeout_flag == 0U) {
            *temp_data = dw_uart_getchar(uart_base);
            temp_data++;
            recv_num++;
            recv_start = csi_tick_get_ms();
        } else {
            break;
        }
    }

    dw_uart_set_intr_en_status(uart_base, intr_en_status);

    return recv_num;
}

csi_error_t dw_uart_receive_intr(csi_uart_t *uart, void *data, uint32_t num)
{
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);
    uart->rx_data = (uint8_t *)data;
    uart->rx_size = num;

    dw_uart_enable_recv_irq(uart_base);

    return CSI_OK;
}

csi_error_t csi_uart_receive_async(csi_uart_t *uart, void *data, uint32_t size)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(uart->callback, CSI_ERROR);
    CSI_PARAM_CHK(uart->receive, CSI_ERROR);

    csi_error_t ret;

    ret = uart->receive(uart, data, size);

    if (ret == CSI_OK) {
        uart->state.readable = 0U;
    }

    return ret;
}

int32_t csi_uart_send(csi_uart_t *uart, const void *data, uint32_t size, uint32_t timeout)
{
    /* check data and uart */
    CSI_PARAM_CHK(uart, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(size, CSI_ERROR);

    dw_uart_regs_t *uart_base;
    uint8_t *ch = (uint8_t *)data;
    int32_t trans_num = 0;
    uint32_t send_start, timeout_flag = 0U;
    uint32_t intr_en_status;

    uart_base = (dw_uart_regs_t *)uart->dev.reg_base; // 串口地址 0x1900d000
    /* store the status of intr */
    intr_en_status = dw_uart_get_intr_en_status(uart_base);
    dw_uart_disable_trans_irq(uart_base);

    send_start = csi_tick_get_ms();

    while (trans_num < (int32_t)size) {
        while (!dw_uart_putready(uart_base)) {
            if ((csi_tick_get_ms() - send_start) >= timeout) {
                timeout_flag = 1U;
                break;
            }
        };

        if (timeout_flag == 0U) {
            dw_uart_putchar(uart_base, *ch++);
            /* update the timeout */
            send_start = csi_tick_get_ms();
            trans_num++;
        } else {
            break;
        }
    }

    dw_uart_set_intr_en_status(uart_base, intr_en_status);

    return trans_num;
}

csi_error_t dw_uart_send_intr(csi_uart_t *uart, const void *data, uint32_t size)
{
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)uart->dev.reg_base;

    uart->tx_data = (uint8_t *)data;
    uart->tx_size = size;
    dw_uart_enable_trans_irq(uart_base);

    return CSI_OK;
}

csi_error_t csi_uart_send_async(csi_uart_t *uart, const void *data, uint32_t size)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);
    CSI_PARAM_CHK(data, CSI_ERROR);
    CSI_PARAM_CHK(uart->callback, CSI_ERROR);
    CSI_PARAM_CHK(uart->send, CSI_ERROR);

    csi_error_t ret;
    ret = uart->send(uart, data, size);

    if (ret == CSI_OK) {
        uart->state.writeable = 0U;
    }

    return ret;
}

csi_error_t csi_uart_attach_callback(csi_uart_t *uart, void  *callback, void *arg)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);

    dw_uart_regs_t *uart_base;
    uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    uart->callback = callback;
    uart->arg = arg;
    uart->send = dw_uart_send_intr;
    uart->receive = dw_uart_receive_intr;
    csi_irq_attach((uint32_t)(uart->dev.irq_num), &dw_uart_irq_handler, &uart->dev);
    csi_irq_enable((uint32_t)(uart->dev.irq_num));
    dw_uart_enable_recv_irq(uart_base);

    return CSI_OK;
}

void csi_uart_detach_callback(csi_uart_t *uart)
{
    CSI_PARAM_CHK_NORETVAL(uart);

    dw_uart_regs_t *uart_base;
    uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    uart->callback  = NULL;
    uart->arg = NULL;
    uart->send = NULL;
    uart->receive = NULL;
    dw_uart_disable_recv_irq(uart_base);
    csi_irq_disable((uint32_t)(uart->dev.irq_num));
    csi_irq_detach((uint32_t)(uart->dev.irq_num));
}

csi_error_t csi_uart_get_state(csi_uart_t *uart, csi_state_t *state)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);
    CSI_PARAM_CHK(state, CSI_ERROR);

    *state = uart->state;

    return CSI_OK;
}

static void dw_uart_dma_event_cb(csi_dma_ch_t *dma, csi_dma_event_t event, void *arg)
{
    csi_uart_t *uart = (csi_uart_t *)dma->parent;
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);

    if (event == DMA_EVENT_TRANSFER_ERROR) {/* DMA transfer ERROR */
        if ((uart->tx_dma != NULL) && (uart->tx_dma->ch_id == dma->ch_id)) {
            csi_dma_ch_stop(dma);
            dw_uart_fifo_init(uart_base);

            uart->state.writeable = 1U;

            if (uart->callback) {
                uart->callback(uart, UART_EVENT_ERROR_OVERFLOW, uart->arg);
            }
        } else {
            csi_dma_ch_stop(dma);
            dw_uart_fifo_init(uart_base);
            /* enable received data available */
            dw_uart_enable_recv_irq(uart_base);

            uart->state.readable = 1U;

            if (uart->callback) {
                uart->callback(uart, UART_EVENT_ERROR_FRAMING, uart->arg);
            }
        }
    } else if (event == DMA_EVENT_TRANSFER_DONE) {/* DMA transfer complete */
        if ((uart->tx_dma != NULL) && (uart->tx_dma->ch_id == dma->ch_id)) {

            csi_dma_ch_stop(dma);
            dw_uart_fifo_init(uart_base);

            uart->state.writeable = 1U;

            if (uart->callback) {
                uart->callback(uart, UART_EVENT_SEND_COMPLETE, uart->arg);
            }
        } else {
            csi_dma_ch_stop(dma);
            dw_uart_fifo_init(uart_base);
            /* enable received data available */
            dw_uart_enable_recv_irq(uart_base);

            uart->state.readable = 1U;

            if (uart->callback) {
                uart->callback(uart, UART_EVENT_RECEIVE_COMPLETE, uart->arg);
            }
        }
    }
}

csi_error_t dw_uart_send_dma(csi_uart_t *uart, const void *data, uint32_t num)
{
    csi_dma_ch_config_t config;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));
    uint32_t fcr_reg = UART_FIFO_INIT_CONFIG;
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);
    csi_dma_ch_t *dma_ch = (csi_dma_ch_t *)uart->tx_dma;

    uart->tx_data = (uint8_t *)data;
    uart->tx_size = num;
    dw_uart_disable_recv_irq(uart_base);
    dw_uart_disable_trans_irq(uart_base);
    config.src_inc = DMA_ADDR_INC;
    config.dst_inc = DMA_ADDR_CONSTANT;
    config.src_tw = DMA_DATA_WIDTH_8_BITS;
    config.dst_tw = DMA_DATA_WIDTH_8_BITS;

    /* config for wj_dma */
    config.group_len = find_max_prime_num(num);
    config.trans_dir = DMA_MEM2PERH;

    /* config for etb */
    config.handshake = uart_tx_hs_num[uart->dev.idx];

    csi_dma_ch_config(dma_ch, &config);

    fcr_reg &= ~(DW_UART_FCR_TET_Msk);

    if (config.group_len >= (UART_MAX_FIFO / 2U)) {
        fcr_reg |= DW_UART_FCR_TET_FIFO_1_2_FULL;
    } else if (config.group_len >= (UART_MAX_FIFO / 4U)) {
        fcr_reg |= DW_UART_FCR_TET_FIFO_1_4_FULL;
    } else if (config.group_len >= (UART_MAX_FIFO / 8U)) {
        fcr_reg |= DW_UART_FCR_TET_FIFO_2_CHAR;
    } else {
        fcr_reg |= DW_UART_FCR_TET_FIFO_EMTPY;
    }

    soc_dcache_clean_invalid_range((unsigned long)uart->tx_data, uart->tx_size);
    dw_uart_set_fcr_reg(uart_base, fcr_reg);
    csi_dma_ch_start(uart->tx_dma, (void *)uart->tx_data, (uint8_t *) & (uart_base->THR), uart->tx_size);

    return CSI_OK;
}

csi_error_t dw_uart_receive_dma(csi_uart_t *uart, void *data, uint32_t num)
{
    csi_dma_ch_config_t config;
    memset(&config, 0, sizeof(csi_dma_ch_config_t));
    csi_error_t ret = CSI_OK;
    uint32_t fcr_reg = UART_FIFO_INIT_CONFIG;
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)HANDLE_REG_BASE(uart);
    csi_dma_ch_t *dma = (csi_dma_ch_t *)uart->rx_dma;

    dw_uart_disable_trans_irq(uart_base);
    dw_uart_disable_recv_irq(uart_base);
    uart->rx_data = (uint8_t *)data;
    uart->rx_size = num;
    config.src_inc = DMA_ADDR_CONSTANT;
    config.dst_inc = DMA_ADDR_INC;
    config.src_tw = DMA_DATA_WIDTH_8_BITS;
    config.dst_tw = DMA_DATA_WIDTH_8_BITS;
    config.group_len = find_max_prime_num(num);
    config.trans_dir = DMA_PERH2MEM;
    config.handshake = uart_rx_hs_num[uart->dev.idx];

    ret = csi_dma_ch_config(dma, &config);

    if (ret == CSI_OK) {

        fcr_reg &= ~(DW_UART_FCR_RT_Msk);

        if (config.group_len >= (UART_MAX_FIFO / 2U)) {
            fcr_reg |= DW_UART_FCR_RT_FIFO_1_2_FULL;
        } else if (config.group_len >= (UART_MAX_FIFO / 4U)) {
            fcr_reg |= DW_UART_FCR_RT_FIFO_1_4_FULL;
        } else {
            fcr_reg |= DW_UART_FCR_RT_FIFO_1_CHAR;
        }

        soc_dcache_clean_invalid_range((unsigned long)uart->rx_data, uart->rx_size);
        dw_uart_set_fcr_reg(uart_base, fcr_reg | DW_UART_FCR_RFIFOR_RESET);
        csi_dma_ch_start(uart->rx_dma, (uint8_t *) & (uart_base->RBR), (void *)uart->rx_data, uart->rx_size);
    }

    return ret;
}

csi_error_t csi_uart_link_dma(csi_uart_t *uart, csi_dma_ch_t *tx_dma, csi_dma_ch_t *rx_dma)
{
    CSI_PARAM_CHK(uart, CSI_ERROR);
    CSI_PARAM_CHK(uart->callback, CSI_ERROR);
    csi_error_t ret = CSI_OK;

    if (tx_dma != NULL) {
        tx_dma->parent = uart;
        ret = csi_dma_ch_alloc(tx_dma, -1, -1);

        if (ret == CSI_OK) {
            csi_dma_ch_attach_callback(tx_dma, dw_uart_dma_event_cb, NULL);
            uart->tx_dma = tx_dma;
            uart->send = dw_uart_send_dma;
        } else {
            tx_dma->parent = NULL;
        }
    } else {
        if (uart->tx_dma) {
            csi_dma_ch_detach_callback(uart->tx_dma);
            csi_dma_ch_free(uart->tx_dma);
            uart->tx_dma = NULL;
        }

        uart->send = dw_uart_send_intr;
    }

    if (ret != CSI_ERROR) {
        if (rx_dma != NULL) {
            rx_dma->parent = uart;
            ret = csi_dma_ch_alloc(rx_dma, -1, -1);

            if (ret == CSI_OK) {
                csi_dma_ch_attach_callback(rx_dma, dw_uart_dma_event_cb, NULL);
                uart->rx_dma = rx_dma;
                uart->receive = dw_uart_receive_dma;
            } else {
                rx_dma->parent = NULL;
            }
        } else {
            if (uart->rx_dma) {
                csi_dma_ch_detach_callback(uart->rx_dma);
                csi_dma_ch_free(uart->rx_dma);
                uart->rx_dma = NULL;
            }

            uart->receive = dw_uart_receive_intr;
        }
    }
    return ret;
}

#ifdef CONFIG_PM
csi_error_t dw_uart_pm_action(csi_dev_t *dev, csi_pm_dev_action_t action)
{
    CSI_PARAM_CHK(dev, CSI_ERROR);

    csi_error_t ret = CSI_OK;
    csi_pm_dev_t *pm_dev = &dev->pm_dev;
    dw_uart_regs_t *uart_base = (dw_uart_regs_t *)dev->reg_base;

    switch (action) {
    case PM_DEV_SUSPEND:
        dw_uart_fifo_disable(uart_base);
        dw_uart_fifo_enable(uart_base);
        dw_uart_wait_idle(uart_base);
        uart_base->LCR |= DW_UART_LCR_DLAB_EN;
        csi_pm_dev_save_regs(pm_dev->reten_mem, (uint32_t *)dev->reg_base, 2U);
        uart_base->LCR &= (~DW_UART_LCR_DLAB_EN);
        csi_pm_dev_save_regs(pm_dev->reten_mem + 2, (uint32_t *)(dev->reg_base + 4U), 1U);
        csi_pm_dev_save_regs(pm_dev->reten_mem + 2 + 1, (uint32_t *)(dev->reg_base + 12U), 2U);
        break;

    case PM_DEV_RESUME:
        dw_uart_fifo_disable(uart_base);
        dw_uart_fifo_enable(uart_base);
        dw_uart_wait_idle(uart_base);
        uart_base->LCR |= DW_UART_LCR_DLAB_EN;
        csi_pm_dev_restore_regs(pm_dev->reten_mem, (uint32_t *)dev->reg_base, 2U);
        uart_base->LCR &= (~DW_UART_LCR_DLAB_EN);
        csi_pm_dev_restore_regs(pm_dev->reten_mem + 2, (uint32_t *)(dev->reg_base + 4U), 1U);
        csi_pm_dev_restore_regs(pm_dev->reten_mem + 2 + 1, (uint32_t *)(dev->reg_base + 12U), 2U);
        break;

    default:
        ret = CSI_ERROR;
        break;
    }

    return ret;
}

csi_error_t csi_uart_enable_pm(csi_uart_t *uart)
{
    return csi_pm_dev_register(&uart->dev, dw_uart_pm_action, 20U, 0U);
}

void csi_uart_disable_pm(csi_uart_t *uart)
{
    csi_pm_dev_unregister(&uart->dev);
}
#endif

