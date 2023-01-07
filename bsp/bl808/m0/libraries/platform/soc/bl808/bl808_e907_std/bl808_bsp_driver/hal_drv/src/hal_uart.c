/**
 * @file hal_uart.c
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#include "hal_uart.h"
#include "hal_dma.h"
#include "bl808_uart.h"
#include "bl808_glb.h"
#include "uart_config.h"

#ifdef BSP_USING_UART0
void UART0_IRQ(void);
#endif
#ifdef BSP_USING_UART1
void UART1_IRQ(void);
#endif
#ifdef BSP_USING_UART2
void UART2_IRQ(void);
#endif
#ifdef BSP_USING_UART3
void UART3_IRQ(void);
#endif

uart_device_t uartx_device[UART_MAX_INDEX] = {
#ifdef BSP_USING_UART0
    UART0_CONFIG,
#endif
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
};

static const uint32_t uartAddr[] = { UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE };

/**
 * @brief
 *
 * @param dev
 * @param oflag
 * @return int
 */
int uart_open(struct device *dev, uint16_t oflag)
{
    uart_device_t *uart_device = (uart_device_t *)dev;
    UART_FifoCfg_Type fifoCfg = { 0 };
    UART_CFG_Type uart_cfg = { 0 };
    uint32_t uart_clk;

    /* disable all interrupt */
    UART_IntMask(uart_device->id, UART_INT_ALL, MASK);
    /* disable uart before config */
    UART_Disable(uart_device->id, UART_TXRX);

    uart_clk = Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_UART0 + uart_device->id);

    uart_cfg.baudRate = uart_device->baudrate;
    uart_cfg.dataBits = uart_device->databits;
    uart_cfg.stopBits = uart_device->stopbits;
    uart_cfg.parity = uart_device->parity;
    uart_cfg.uartClk = uart_clk;
    uart_cfg.ctsFlowControl = UART_CTS_FLOWCONTROL_ENABLE;
    uart_cfg.rtsSoftwareControl = UART_RTS_FLOWCONTROL_ENABLE;
    uart_cfg.byteBitInverse = UART_MSB_FIRST_ENABLE;
    uart_cfg.txSoftwareControl = UART_TX_SWCONTROL_ENABLE;
    uart_cfg.txLinMode = UART_TX_LINMODE_ENABLE;
    uart_cfg.rxLinMode = UART_RX_LINMODE_ENABLE;
    uart_cfg.txBreakBitCnt = UART_TX_BREAKBIT_CNT;

    /* uart init with default configuration */
    UART_Init(uart_device->id, &uart_cfg);

    /* Enable tx free run mode */
    UART_TxFreeRun(uart_device->id, ENABLE);

    /* Set rx time-out value */
    UART_SetRxTimeoutValue(uart_device->id, UART_DEFAULT_RTO_TIMEOUT);

    fifoCfg.txFifoDmaThreshold = uart_device->fifo_threshold;
    fifoCfg.txFifoDmaEnable = DISABLE;
    fifoCfg.rxFifoDmaThreshold = uart_device->fifo_threshold;
    fifoCfg.rxFifoDmaEnable = DISABLE;

    if (oflag & DEVICE_OFLAG_STREAM_TX) {
    }

    if ((oflag & DEVICE_OFLAG_INT_TX) || (oflag & DEVICE_OFLAG_INT_RX)) {
#ifdef BSP_USING_UART0
        if (uart_device->id == UART0_ID) {
            Interrupt_Handler_Register(UART0_IRQn, UART0_IRQ);
        }
#endif
#ifdef BSP_USING_UART1
        if (uart_device->id == UART1_ID) {
            Interrupt_Handler_Register(UART1_IRQn, UART1_IRQ);
        }
#endif
#ifdef BSP_USING_UART2
        if (uart_device->id == UART2_ID) {
            Interrupt_Handler_Register(UART2_IRQn, UART2_IRQ);
        }
#endif
#ifdef BSP_USING_UART3
        if (uart_device->id == UART0_MM_ID) {
            Interrupt_Handler_Register(UART3_IRQn, UART3_IRQ);
        }
#endif
    }

    if (oflag & DEVICE_OFLAG_DMA_TX) {
        fifoCfg.txFifoDmaEnable = ENABLE;
    }

    if (oflag & DEVICE_OFLAG_DMA_RX) {
        fifoCfg.rxFifoDmaEnable = ENABLE;
    }

    UART_FifoConfig(uart_device->id, &fifoCfg);

    UART_TxFifoClear(uart_device->id);
    UART_RxFifoClear(uart_device->id);

    /* enable uart */
    UART_Enable(uart_device->id, UART_TXRX);
    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @return int
 */
int uart_close(struct device *dev)
{
    uart_device_t *uart_device = (uart_device_t *)dev;

    UART_Disable(uart_device->id, UART_TXRX);
    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @param cmd
 * @param args
 * @return int
 */
int uart_control(struct device *dev, int cmd, void *args)
{
    uart_device_t *uart_device = (uart_device_t *)dev;

    switch (cmd) {
        case DEVICE_CTRL_SET_INT: {
            int offset = __builtin_ctz((uint32_t)(uintptr_t)args);

            while (offset < 9) {
                if ((uint32_t)(uintptr_t)args & (1 << offset)) {
                    UART_IntMask(uart_device->id, offset, UNMASK);
                }

                offset++;
            }

            if (uart_device->id == UART0_ID) {
                CPU_Interrupt_Enable(UART0_IRQn);
            } else if (uart_device->id == UART1_ID) {
                CPU_Interrupt_Enable(UART1_IRQn);
            } else if (uart_device->id == UART2_ID) {
                CPU_Interrupt_Enable(UART2_IRQn);
            } else if (uart_device->id == UART0_MM_ID) {
                CPU_Interrupt_Enable(UART3_IRQn);
            }

            break;
        }

        case DEVICE_CTRL_CLR_INT: {
            int offset = __builtin_ctz((uint32_t)(uintptr_t)args);

            while (offset < 9) {
                if ((uint32_t)(uintptr_t)args & (1 << offset)) {
                    UART_IntMask(uart_device->id, offset, MASK);
                }

                offset++;
            }

            if (uart_device->id == UART0_ID) {
                CPU_Interrupt_Disable(UART0_IRQn);
            } else if (uart_device->id == UART1_ID) {
                CPU_Interrupt_Disable(UART1_IRQn);
            } else if (uart_device->id == UART2_ID) {
                CPU_Interrupt_Disable(UART2_IRQn);
            } else if (uart_device->id == UART0_MM_ID) {
                CPU_Interrupt_Disable(UART3_IRQn);
            }

            break;
        }

        case DEVICE_CTRL_GET_INT:
            break;

        case DEVICE_CTRL_CONFIG: {
            uart_param_cfg_t *cfg = (uart_param_cfg_t *)args;
            UART_CFG_Type uart_cfg = { 0 };

            /* Disable uart before config */
            UART_Disable(uart_device->id, UART_TXRX);
            uint32_t uart_clk = Clock_Peripheral_Clock_Get(BL_PERIPHERAL_CLOCK_UART0);

            uart_cfg.uartClk = uart_clk;
            uart_cfg.baudRate = cfg->baudrate;
            uart_cfg.stopBits = cfg->stopbits;
            uart_cfg.parity = cfg->parity;
            uart_cfg.dataBits = cfg->databits;
            uart_cfg.ctsFlowControl = UART_CTS_FLOWCONTROL_ENABLE;
            uart_cfg.rtsSoftwareControl = UART_RTS_FLOWCONTROL_ENABLE;
            uart_cfg.byteBitInverse = UART_MSB_FIRST_ENABLE;
            uart_cfg.txSoftwareControl = UART_TX_SWCONTROL_ENABLE;
            uart_cfg.txLinMode = UART_TX_LINMODE_ENABLE;
            uart_cfg.rxLinMode = UART_RX_LINMODE_ENABLE;
            uart_cfg.txBreakBitCnt = UART_TX_BREAKBIT_CNT;
            UART_Init(uart_device->id, &uart_cfg);

            UART_TxFifoClear(uart_device->id);
            UART_RxFifoClear(uart_device->id);

            /* Enable uart */
            UART_Enable(uart_device->id, UART_TXRX);
            break;
        }

        case DEVICE_CTRL_GET_CONFIG:
            break;

        case DEVICE_CTRL_ATTACH_TX_DMA:
            uart_device->tx_dma = (struct device *)args;
            break;

        case DEVICE_CTRL_ATTACH_RX_DMA:
            uart_device->rx_dma = (struct device *)args;
            break;

        case DEVICE_CTRL_TX_DMA_SUSPEND: {
            uint32_t tmpVal = BL_RD_REG(uartAddr[uart_device->id], UART_FIFO_CONFIG_0);
            tmpVal = BL_CLR_REG_BIT(tmpVal, UART_DMA_TX_EN);
            BL_WR_REG(uartAddr[uart_device->id], UART_FIFO_CONFIG_0, tmpVal);
            dev->oflag &= ~DEVICE_OFLAG_DMA_TX;
            break;
        }

        case DEVICE_CTRL_RX_DMA_SUSPEND: {
            uint32_t tmpVal = BL_RD_REG(uartAddr[uart_device->id], UART_FIFO_CONFIG_0);
            tmpVal = BL_CLR_REG_BIT(tmpVal, UART_DMA_RX_EN);
            BL_WR_REG(uartAddr[uart_device->id], UART_FIFO_CONFIG_0, tmpVal);
            dev->oflag &= ~DEVICE_OFLAG_DMA_RX;
            break;
        }

        case DEVICE_CTRL_TX_DMA_RESUME: {
            uint32_t tmpVal = BL_RD_REG(uartAddr[uart_device->id], UART_FIFO_CONFIG_0);
            tmpVal = BL_SET_REG_BIT(tmpVal, UART_DMA_TX_EN);
            BL_WR_REG(uartAddr[uart_device->id], UART_FIFO_CONFIG_0, tmpVal);
            dev->oflag |= DEVICE_OFLAG_DMA_TX;
            break;
        }

        case DEVICE_CTRL_RX_DMA_RESUME: {
            uint32_t tmpVal = BL_RD_REG(uartAddr[uart_device->id], UART_FIFO_CONFIG_0);
            tmpVal = BL_SET_REG_BIT(tmpVal, UART_DMA_RX_EN);
            BL_WR_REG(uartAddr[uart_device->id], UART_FIFO_CONFIG_0, tmpVal);
            dev->oflag |= DEVICE_OFLAG_DMA_RX;
            break;
        }

        case DEVICE_CTRL_UART_GET_TX_FIFO:
            return UART_GetTxFifoCount(uart_device->id);

        case DEVICE_CTRL_UART_GET_RX_FIFO:
            return UART_GetRxFifoCount(uart_device->id);

        default:
            break;
    }

    return 0;
}
/**
 * @brief
 *
 * @param dev
 * @param pos
 * @param buffer
 * @param size
 * @return int
 */
int uart_write(struct device *dev, uint32_t pos, const void *buffer, uint32_t size)
{
    int ret = 0;
    uart_device_t *uart_device = (uart_device_t *)dev;
    if (dev->oflag & DEVICE_OFLAG_DMA_TX) {
        struct device *dma_ch = (struct device *)uart_device->tx_dma;
        if (!dma_ch)
            return -1;

        if (uart_device->id == 0) {
            ret = dma_reload(dma_ch, (uint32_t)(uintptr_t)buffer, (uint32_t)DMA_ADDR_UART0_TDR, size);
            dma_channel_start(dma_ch);
        } else if (uart_device->id == 1) {
            ret = dma_reload(dma_ch, (uint32_t)(uintptr_t)buffer, (uint32_t)DMA_ADDR_UART1_TDR, size);
            dma_channel_start(dma_ch);
        } else if (uart_device->id == 2) {
            ret = dma_reload(dma_ch, (uint32_t)(uintptr_t)buffer, (uint32_t)DMA_ADDR_UART2_TDR, size);
            dma_channel_start(dma_ch);
        } else if (uart_device->id == 3) {
            ret = dma_reload(dma_ch, (uint32_t)(uintptr_t)buffer, (uint32_t)DMA_ADDR_UART3_TDR, size);
            dma_channel_start(dma_ch);
        }
        return ret;
    } else if (dev->oflag & DEVICE_OFLAG_INT_TX) {
        return -2;
    } else
        return UART_SendData(uart_device->id, (uint8_t *)buffer, size);
}
/**
 * @brief
 *
 * @param dev
 * @param pos
 * @param buffer
 * @param size
 * @return int
 */
int uart_read(struct device *dev, uint32_t pos, void *buffer, uint32_t size)
{
    int ret = -1;
    uart_device_t *uart_device = (uart_device_t *)dev;
    if (dev->oflag & DEVICE_OFLAG_DMA_RX) {
        struct device *dma_ch = (struct device *)uart_device->rx_dma;
        if (!dma_ch)
            return -1;

        if (uart_device->id == 0) {
            ret = dma_reload(dma_ch, (uint32_t)DMA_ADDR_UART0_RDR, (uint32_t)(uintptr_t)buffer, size);
            dma_channel_start(dma_ch);
        } else if (uart_device->id == 1) {
            ret = dma_reload(dma_ch, (uint32_t)DMA_ADDR_UART1_RDR, (uint32_t)(uintptr_t)buffer, size);
            dma_channel_start(dma_ch);
        } else if (uart_device->id == 2) {
            ret = dma_reload(dma_ch, (uint32_t)DMA_ADDR_UART2_RDR, (uint32_t)(uintptr_t)buffer, size);
            dma_channel_start(dma_ch);
        } else if (uart_device->id == 3) {
            ret = dma_reload(dma_ch, (uint32_t)DMA_ADDR_UART3_RDR, (uint32_t)(uintptr_t)buffer, size);
            dma_channel_start(dma_ch);
        }
        return ret;
    } else if (dev->oflag & DEVICE_OFLAG_INT_RX) {
        return -2;
    } else {
        return UART_ReceiveData(uart_device->id, (uint8_t *)buffer, size);
    }
}
/**
 * @brief
 *
 * @param index
 * @param name
 * @param flag
 * @return int
 */
int uart_register(enum uart_index_type index, const char *name)
{
    struct device *dev;

    if (UART_MAX_INDEX == 0) {
        return -DEVICE_EINVAL;
    }

    dev = &(uartx_device[index].parent);

    dev->open = uart_open;
    dev->close = uart_close;
    dev->control = uart_control;
    dev->write = uart_write;
    dev->read = uart_read;

    dev->type = DEVICE_CLASS_UART;
    dev->handle = NULL;

    return device_register(dev, name);
}
/**
 * @brief
 *
 * @param handle
 */
void uart_isr(uart_device_t *handle)
{
    uint32_t tmpVal = 0;
    uint32_t maskVal = 0;
    uint32_t UARTx = uartAddr[handle->id];

    tmpVal = BL_RD_REG(UARTx, UART_INT_STS);
    maskVal = BL_RD_REG(UARTx, UART_INT_MASK);

    if (!handle->parent.callback) {
        return;
    }

    /* Length of uart tx data transfer arrived interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_UTX_END_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_UTX_END_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 0x1);
        handle->parent.callback(&handle->parent, NULL, 0, UART_EVENT_TX_END);
    }

    /* Length of uart rx data transfer arrived interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_END_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_END_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 0x2);
        handle->parent.callback(&handle->parent, NULL, 0, UART_EVENT_RX_END);
    }

    /* Tx fifo ready interrupt,auto-cleared when data is pushed */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_UTX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_UTX_FRDY_MASK)) {
        handle->parent.callback(&handle->parent, NULL, 0, UART_EVENT_TX_FIFO);
    }

    /* Rx fifo ready interrupt,auto-cleared when data is popped */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_FRDY_MASK)) {
        uint8_t buffer[UART_FIFO_MAX_LEN];
        uint8_t len = UART_ReceiveData(handle->id, buffer, UART_FIFO_MAX_LEN);

        if (len) {
            handle->parent.callback(&handle->parent, &buffer[0], len, UART_EVENT_RX_FIFO);
        }
    }

    /* Rx time-out interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_RTO_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_RTO_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 0x10);
        uint8_t buffer[UART_FIFO_MAX_LEN];
        uint8_t len = UART_ReceiveData(handle->id, buffer, UART_FIFO_MAX_LEN);

        if (len) {
            handle->parent.callback(&handle->parent, &buffer[0], len, UART_EVENT_RTO);
        }
    }

    /* Rx parity check error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_PCE_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_PCE_MASK)) {
        BL_WR_REG(UARTx, UART_INT_CLEAR, 0x20);
        handle->parent.callback(&handle->parent, NULL, 0, UART_PCE_IT);
    }

    /* Tx fifo overflow/underflow error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_UTX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_UTX_FER_MASK)) {
        handle->parent.callback(&handle->parent, NULL, 0, UART_TX_FER_IT);
    }

    /* Rx fifo overflow/underflow error interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal, UART_URX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal, UART_CR_URX_FER_MASK)) {
        handle->parent.callback(&handle->parent, NULL, 0, UART_RX_FER_IT);
    }
}

#ifdef BSP_USING_UART0
/**
 * @brief
 *
 */
void UART0_IRQ(void)
{
    uart_isr(&uartx_device[UART0_INDEX]);
}
#endif
#ifdef BSP_USING_UART1
/**
 * @brief
 *
 */
void UART1_IRQ(void)
{
    uart_isr(&uartx_device[UART1_INDEX]);
}
#endif
#ifdef BSP_USING_UART2
/**
 * @brief
 *
 */
void UART2_IRQ(void)
{
    uart_isr(&uartx_device[UART2_INDEX]);
}
#endif
#ifdef BSP_USING_UART3
/**
 * @brief
 *
 */
void UART3_IRQ(void)
{
    uart_isr(&uartx_device[UART3_INDEX]);
}
#endif
