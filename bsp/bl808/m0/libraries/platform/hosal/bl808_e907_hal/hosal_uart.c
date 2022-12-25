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

//FIXME no BL808/BL606p header file including is Allowed here
#ifdef BL808
#include <bl808_uart.h>
#include <bl808_glb.h>
#elif defined(BL606P)
#include <bl606p_uart.h>
#include <bl606p_glb.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif


#include "bl_uart.h"
#include "bl_irq.h"
#include "hosal_uart.h"
#include "blog.h"

// static const uint32_t g_uart_addr[2] = {UART0_BASE, UART1_BASE};

static void gpio_init(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin)
{
    GLB_GPIO_Cfg_Type cfg;
    GLB_UART_SIG_FUN_Type tx_sigfun, rx_sigfun;

    cfg.drive = 1;
    cfg.smtCtrl = 1;
    cfg.gpioFun = 7;

    cfg.gpioPin = rx_pin;
    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_UP;
    GLB_GPIO_Init(&cfg);

    cfg.gpioPin = tx_pin;
    cfg.gpioMode = GPIO_MODE_AF;
    cfg.pullType = GPIO_PULL_UP;
    GLB_GPIO_Init(&cfg);

    /* select uart gpio function */
    if (id == 0) {
        tx_sigfun = GLB_UART_SIG_FUN_UART0_TXD;
        rx_sigfun = GLB_UART_SIG_FUN_UART0_RXD;
    } else {
        tx_sigfun = GLB_UART_SIG_FUN_UART1_TXD;
        rx_sigfun = GLB_UART_SIG_FUN_UART1_RXD;
    }

    // clk
    //GLB_Set_UART_CLK(1, HBN_UART_CLK_160M, 0);

    GLB_UART_Fun_Sel(tx_pin%12, tx_sigfun);
    GLB_UART_Fun_Sel(rx_pin%12, rx_sigfun);
}

static void __uart_rx_irq(void *p_arg)
{
    hosal_uart_dev_t *uart = (hosal_uart_dev_t *)p_arg;
    if (uart->rx_cb) {
        uart->rx_cb(uart->p_rxarg);
    }
}

static void __uart_tx_irq(void *p_arg)
{
    hosal_uart_dev_t *uart = (hosal_uart_dev_t *)p_arg;
    if (uart->tx_cb) {
        uart->tx_cb(uart->p_txarg);
    }
}
#if 0
static void __uart_rx_dma_irq(void *p_arg, uint32_t flag)
{
    hosal_uart_dev_t *uart = (hosal_uart_dev_t *)p_arg;

    if (flag != HOSAL_DMA_INT_TRANS_COMPLETE) {
    	blog_error("DMA RX TRANS ERROR\r\n");
    }

    if (uart->rxdma_cb) {
    	uart->rxdma_cb(uart->p_rxdma_arg);
    }
}

static void __uart_tx_dma_irq(void *p_arg, uint32_t flag)
{
    hosal_uart_dev_t *uart = (hosal_uart_dev_t *)p_arg;

    if (flag != HOSAL_DMA_INT_TRANS_COMPLETE) {
    	blog_error("DMA TX TRANS ERROR\r\n");
    }

    if (uart->txdma_cb) {
    	uart->txdma_cb(uart->p_txdma_arg);
    }
}

static int __uart_dma_txcfg(hosal_uart_dev_t *uart, hosal_uart_dma_cfg_t *dma_cfg)
{
	if (dma_cfg->dma_buf == NULL || dma_cfg->dma_buf_size == 0) {
		return -1;
	}
	DMA_Channel_Cfg_Type txchCfg = {
	    (uint32_t)dma_cfg->dma_buf,
		g_uart_addr[uart->port] + UART_FIFO_WDATA_OFFSET,
		dma_cfg->dma_buf_size,
	    DMA_TRNS_M2P,
		DMA_CH0,
	    DMA_TRNS_WIDTH_8BITS,
	    DMA_TRNS_WIDTH_8BITS,
	    DMA_BURST_SIZE_4,
	    DMA_BURST_SIZE_4,
	    DMA_MINC_ENABLE,
	    DMA_PINC_DISABLE,
	    DMA_REQ_NONE,
	    DMA_REQ_UART0_TX,
	};
    UART_FifoCfg_Type fifoCfg =
    {
        .txFifoDmaThreshold     = 0x10,
        .rxFifoDmaThreshold     = 0x10,
        .txFifoDmaEnable        = ENABLE,
        .rxFifoDmaEnable        = DISABLE,
    };

    if (uart->dma_tx_chan >= 0) {
    	DMA_Channel_Update_SrcMemcfg(uart->dma_tx_chan,
    			(uint32_t)dma_cfg->dma_buf, dma_cfg->dma_buf_size);
    	return 0;
    }

	uart->dma_tx_chan = hosal_dma_chan_request(0);
	if (uart->dma_tx_chan < 0) {
		blog_error("dma_tx_chan request failed !\r\n");
		return -1;
	}

	hosal_dma_chan_stop(uart->dma_tx_chan);

    /* FIFO Config*/
	fifoCfg.rxFifoDmaEnable = (uart->dma_rx_chan < 0) ? DISABLE : ENABLE;
    UART_FifoConfig(uart->port, &fifoCfg);

	txchCfg.ch = uart->dma_tx_chan;
	txchCfg.dstPeriph = (uart->port == 0) ? DMA_REQ_UART0_TX : DMA_REQ_UART1_TX;
	DMA_Channel_Init(&txchCfg);
	hosal_dma_irq_callback_set(uart->dma_tx_chan, __uart_tx_dma_irq, (void *)uart);

	return 0;
}

static int __uart_dma_rxcfg(hosal_uart_dev_t *uart, hosal_uart_dma_cfg_t *dma_cfg)
{
	if (dma_cfg->dma_buf == NULL || dma_cfg->dma_buf_size == 0) {
		return -1;
	}

	DMA_Channel_Cfg_Type rxchCfg = {
		g_uart_addr[uart->port] + UART_FIFO_RDATA_OFFSET,
		(uint32_t)dma_cfg->dma_buf,
		dma_cfg->dma_buf_size,
	    DMA_TRNS_P2M,
		DMA_CH0,
	    DMA_TRNS_WIDTH_8BITS,
	    DMA_TRNS_WIDTH_8BITS,
	    DMA_BURST_SIZE_16,
	    DMA_BURST_SIZE_16,
	    DMA_PINC_DISABLE,
	    DMA_MINC_ENABLE,
	    DMA_REQ_UART0_RX,
	    DMA_REQ_NONE,
	};
    UART_FifoCfg_Type fifoCfg =
    {
        .txFifoDmaThreshold     = 0x10,
        .rxFifoDmaThreshold     = 0x10,
        .txFifoDmaEnable        = DISABLE,
        .rxFifoDmaEnable        = ENABLE,
    };

    if (uart->dma_rx_chan >= 0) {
    	DMA_Channel_Update_DstMemcfg(uart->dma_rx_chan,
    			(uint32_t)dma_cfg->dma_buf, dma_cfg->dma_buf_size);
    	return 0;
    }

	uart->dma_rx_chan = hosal_dma_chan_request(0);
	if (uart->dma_rx_chan < 0) {
		blog_error("dma_rx_chan request failed !\r\n");
		return -1;
	}

	hosal_dma_chan_stop(uart->dma_rx_chan);

    /* FIFO Config*/
	fifoCfg.txFifoDmaEnable = (uart->dma_tx_chan < 0) ? DISABLE : ENABLE;
    UART_FifoConfig(uart->port, &fifoCfg);

	rxchCfg.ch = uart->dma_rx_chan;
	rxchCfg.srcPeriph = (uart->port == 0) ? DMA_REQ_UART0_RX : DMA_REQ_UART1_RX;

	DMA_Channel_Init(&rxchCfg);
	hosal_dma_irq_callback_set(uart->dma_rx_chan, __uart_rx_dma_irq, (void *)uart);

	return 0;
}
#endif
static void __uart_config_set(hosal_uart_dev_t *uart, const hosal_uart_config_t *cfg)
{
    const uint8_t uart_div = 3;
    uint8_t id = uart->port;

#if 0
    UART_CFG_Type uartCfg =
    {
        80*1000*1000,                                       /* UART clock */
        2000000,                                              /* UART Baudrate */
        UART_DATABITS_8,                                     /* UART data bits length */
        UART_STOPBITS_1,                                     /* UART data stop bits length */
        UART_PARITY_NONE,                                    /* UART no parity */
        DISABLE,                                             /* Disable auto flow control */
        DISABLE,                                             /* Disable rx input de-glitch function */
        DISABLE,                                             /* Disable RTS output SW control mode */
        UART_LSB_FIRST                                       /* UART each data byte is send out LSB-first */
    };

    uartCfg.baudRate = cfg->baud_rate;
    uartCfg.dataBits = (UART_DataBits_Type)cfg->data_width;
    uartCfg.parity = (UART_Parity_Type)cfg->parity;

    if (cfg->flow_control == HOSAL_FLOW_CONTROL_CTS) {
    	uartCfg.ctsFlowControl = 1;
    	uartCfg.rtsSoftwareControl = 0;
    } else if (cfg->flow_control == HOSAL_FLOW_CONTROL_RTS) {
    	uartCfg.ctsFlowControl = 0;
    	uartCfg.rtsSoftwareControl = 1;
    } else if (cfg->flow_control == HOSAL_FLOW_CONTROL_CTS_RTS) {
    	uartCfg.ctsFlowControl = 1;
    	uartCfg.rtsSoftwareControl = 1;
    } else {
    	uartCfg.ctsFlowControl = 0;
    	uartCfg.rtsSoftwareControl = 0;
    }

    //uartCfg.uartClk = (160 * 1000 * 1000) / (uart_div + 1);

    /* Disable uart before config */
    UART_Disable(id, UART_TXRX);

    /* UART init */
    UART_Init(id, &uartCfg);
#endif
    if (cfg->mode == HOSAL_UART_MODE_INT) {
    	bl_uart_int_tx_notify_register(uart->port, __uart_tx_irq, uart);
    	bl_uart_int_rx_notify_register(uart->port, __uart_rx_irq, uart);
    	bl_uart_int_enable(uart->port);
    	bl_uart_int_tx_disable(uart->port);
    } else {
    	bl_uart_int_disable(uart->port);
    }

    /* Enable uart */
    UART_Enable(id, UART_TXRX);
}

int hosal_uart_init(hosal_uart_dev_t *uart)
{
    static uint8_t uart_clk_init = 0;
    const uint8_t uart_div = 3;
    hosal_uart_config_t *cfg = &uart->config;
    uint8_t id;

    UART_CFG_Type uartCfg =
    {
        80*1000*1000,                                        /* UART clock */
        2000000,                                              /* UART Baudrate */
        UART_DATABITS_8,                                     /* UART data bits length */
        UART_STOPBITS_1,                                     /* UART data stop bits length */
        UART_PARITY_NONE,                                    /* UART no parity */
        DISABLE,                                             /* Disable auto flow control */
        DISABLE,                                             /* Disable rx input de-glitch function */
        DISABLE,                                             /* Disable RTS output SW control mode */
        UART_LSB_FIRST                                       /* UART each data byte is send out LSB-first */
    };
    UART_FifoCfg_Type fifoCfg =
    {
        .txFifoDmaThreshold     = 0x10,
        .rxFifoDmaThreshold     = 0x10,
        .txFifoDmaEnable        = DISABLE,
        .rxFifoDmaEnable        = DISABLE,
    };

    /* enable clk */

#if 0
    if (0 == uart_clk_init) {
        GLB_Set_UART_CLK(1, HBN_UART_CLK_160M, uart_div);
        uart_clk_init = 1;
    }
#endif

    uart->dma_rx_chan = -1;
    uart->dma_tx_chan = -1;
    id = cfg->uart_id;
    uart->port = cfg->uart_id;

    /* gpio init */
    //gpio_init(id, cfg->tx_pin, cfg->rx_pin, cfg->cts_pin, cfg->rts_pin);

    uartCfg.baudRate = cfg->baud_rate;
    uartCfg.dataBits = (UART_DataBits_Type)cfg->data_width;
    uartCfg.parity = (UART_Parity_Type)cfg->parity;

    if (cfg->flow_control == HOSAL_FLOW_CONTROL_CTS) {
    	uartCfg.ctsFlowControl = 1;
    	uartCfg.rtsSoftwareControl = 0;
    } else if (cfg->flow_control == HOSAL_FLOW_CONTROL_RTS) {
    	uartCfg.ctsFlowControl = 0;
    	uartCfg.rtsSoftwareControl = 1;
    } else if (cfg->flow_control == HOSAL_FLOW_CONTROL_CTS_RTS) {
    	uartCfg.ctsFlowControl = 1;
    	uartCfg.rtsSoftwareControl = 1;
    } else {
    	uartCfg.ctsFlowControl = 0;
    	uartCfg.rtsSoftwareControl = 0;
    }

    //uartCfg.uartClk = (40 * 1000 * 1000) / (uart_div + 1);

    /* Disable all interrupt */
    UART_IntMask(id, UART_INT_ALL, MASK);

    /* Disable uart before config */
    UART_Disable(id, UART_TXRX);

    if (UART_GetRxBusBusyStatus(id) == SET) {
        UART_DeInit(id);
    }

    /* UART init */
    UART_Init(id, &uartCfg);

    /* Enable tx free run mode */
    UART_TxFreeRun(id, ENABLE);

    /* FIFO Config*/
    UART_FifoConfig(id, &fifoCfg);

    if (cfg->mode == HOSAL_UART_MODE_INT) {
    	bl_uart_int_tx_notify_register(uart->port, __uart_tx_irq, uart);
    	bl_uart_int_rx_notify_register(uart->port, __uart_rx_irq, uart);
    	bl_uart_int_enable(uart->port);
    	bl_uart_int_tx_disable(uart->port);
    } else {
    	bl_uart_int_disable(uart->port);
    }

    /* Enable uart */
    UART_Enable(id, UART_TXRX);
    return 0;
}

int hosal_uart_receive(hosal_uart_dev_t *uart, void *data, uint32_t expect_size)
{
    int ch;
    uint32_t counter = 0;

    while (counter < expect_size) {
        if ((ch = bl_uart_data_recv(uart->port)) < 0) {
            break;
        }
        ((uint8_t*)data)[counter] = ch;
        counter++;
    }
    return counter;
}

int hosal_uart_send(hosal_uart_dev_t *uart, const void *data, uint32_t size)
{
    uint32_t i = 0;

    while (i < size) {
        bl_uart_data_send(uart->port, ((uint8_t*)data)[i]);
        i++;
    }
    return i;
}

int hosal_uart_ioctl(hosal_uart_dev_t *uart, int ctl, void *p_arg)
{
#if 0
	hosal_uart_dma_cfg_t *dma_cfg;
#endif

    switch (ctl) {
    case HOSAL_UART_BAUD_SET:
        uart->config.baud_rate = (uint32_t)p_arg;
        __uart_config_set(uart, &uart->config);
        break;
    case HOSAL_UART_BAUD_GET:
        if (p_arg) {
            *(uint32_t *)p_arg = uart->config.baud_rate;
        }
        break;
    case HOSAL_UART_DATA_WIDTH_SET:
        uart->config.data_width = (hosal_uart_data_width_t)p_arg;
        __uart_config_set(uart, &uart->config);
        break;
    case HOSAL_UART_DATA_WIDTH_GET:
        if (p_arg) {
            *(hosal_uart_data_width_t *)p_arg = uart->config.data_width;
        }
        break;
    case HOSAL_UART_STOP_BITS_SET:
        uart->config.stop_bits = (hosal_uart_stop_bits_t)p_arg;
        __uart_config_set(uart, &uart->config);
        break;
    case HOSAL_UART_STOP_BITS_GET:
        if (p_arg) {
            *(hosal_uart_stop_bits_t *)p_arg = uart->config.stop_bits;
        }
        break;
    case HOSAL_UART_FLOWMODE_SET:
        uart->config.flow_control = (hosal_uart_flow_control_t)p_arg;
        __uart_config_set(uart, &uart->config);
        break;
    case HOSAL_UART_FLOWSTAT_GET:
        if (p_arg) {
            *(hosal_uart_flow_control_t *)p_arg = uart->config.flow_control;
        }
        break;
    case HOSAL_UART_PARITY_SET:
        uart->config.parity = (hosal_uart_parity_t)p_arg;
        __uart_config_set(uart, &uart->config);
        break;
    case HOSAL_UART_PARITY_GET:
        if (p_arg) {
            *(hosal_uart_parity_t *)p_arg = uart->config.parity;
        }
        break;
    case HOSAL_UART_MODE_SET:
        uart->config.mode = (hosal_uart_mode_t)p_arg;
        __uart_config_set(uart, &uart->config);
        break;
    case HOSAL_UART_MODE_GET:
        if (p_arg) {
            *(hosal_uart_mode_t *)p_arg = uart->config.mode;
        }
        break;
    case HOSAL_UART_FREE_TXFIFO_GET:
        if (p_arg) {
            *(uint32_t *)p_arg = UART_GetTxFifoCount(uart->port);
        }
        break;
    case HOSAL_UART_FREE_RXFIFO_GET:
        if (p_arg) {
            *(uint32_t *)p_arg = UART_GetRxFifoCount(uart->port);
        }
        break;
    case HOSAL_UART_FLUSH:
        bl_uart_flush(uart->port);
        break;
    case HOSAL_UART_TX_TRIGGER_ON:
    	bl_uart_int_tx_enable(uart->port);
    	break;
    case HOSAL_UART_TX_TRIGGER_OFF:
    	bl_uart_int_tx_disable(uart->port);
    	break;
#if 0
    case HOSAL_UART_DMA_TX_START:
    	dma_cfg = (hosal_uart_dma_cfg_t *)p_arg;
    	if (__uart_dma_txcfg(uart, dma_cfg) != 0) {
    		return -1;
    	}
    	hosal_dma_chan_start(uart->dma_tx_chan);
    	break;
    case HOSAL_UART_DMA_RX_START:
    	dma_cfg = (hosal_uart_dma_cfg_t *)p_arg;
    	if (__uart_dma_rxcfg(uart, dma_cfg) != 0) {
    		return -1;
    	}
    	hosal_dma_chan_start(uart->dma_rx_chan);
    	break;
#endif
    default :
        return -1;
    }
    return 0;
}

int hosal_uart_callback_set(hosal_uart_dev_t *uart,
                          int callback_type,
                          hosal_uart_callback_t pfn_callback,
                          void *arg)
{
    if (callback_type == HOSAL_UART_TX_CALLBACK) {
        uart->tx_cb = pfn_callback;
        uart->p_txarg = arg;
    } else if (callback_type == HOSAL_UART_RX_CALLBACK) {
        uart->rx_cb = pfn_callback;
        uart->p_rxarg = arg;
    }
#if 0
    else if (callback_type == HOSAL_UART_TX_DMA_CALLBACK) {
        uart->txdma_cb = pfn_callback;
        uart->p_txdma_arg = arg;
    } else if (callback_type == HOSAL_UART_RX_DMA_CALLBACK) {
        uart->rxdma_cb = pfn_callback;
        uart->p_rxdma_arg = arg;
    }
#endif
    return 0;
}

int hosal_uart_finalize(hosal_uart_dev_t *uart)
{
    bl_uart_int_disable(uart->port);
    UART_Disable(uart->port, UART_TXRX);
#if 0
    if (uart->dma_rx_chan > 0) {
    	hosal_dma_chan_release(uart->dma_rx_chan);
    }
    if (uart->dma_tx_chan > 0) {
    	hosal_dma_chan_release(uart->dma_tx_chan);
    }
#endif
    return 0;
}
