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
#include <bl808.h>
#include <bl808_uart.h>
#include <bl808_glb.h>
#elif defined(BL606P)
#include <bl606p.h>
#include <bl606p_uart.h>
#include <bl606p_glb.h>
#else
#error "Use CHIP BL808/BL606P for this module"
#endif

#include "bl_uart.h"
#include "bl_irq.h"

#ifdef BFLB_USE_HAL_DRIVER
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
void UART3_IRQHandler(void);
#endif

//TODO Do in std driver
#define UART_NUMBER_SUPPORTED   4
#define UART_FIFO_TX_CNT        (32)
#define FIFO_TX_SIZE_BURST      (32)
static const uint32_t uartAddr[4] = {UART0_BASE, UART1_BASE, UART2_BASE, UART3_BASE};

typedef struct bl_uart_notify {
    cb_uart_notify_t rx_cb;
    void            *rx_cb_arg;

    cb_uart_notify_t tx_cb;
    void            *tx_cb_arg;
} bl_uart_notify_t;

static bl_uart_notify_t g_uart_notify_arg[UART_NUMBER_SUPPORTED];


static void uart_init_demo(uint8_t id)
{
    static UART_CFG_Type uartCfg = {
        80*1000*1000,                                        /* UART clock */
        2000000,                                             /* UART Baudrate */
        UART_DATABITS_8,                                     /* UART data bits length */
        UART_STOPBITS_1,                                     /* UART data stop bits length */
        UART_PARITY_NONE,                                    /* UART no parity */
        DISABLE,                                             /* Disable auto flow control */
        DISABLE,                                             /* Disable rx input de-glitch function */
        DISABLE,                                             /* Disable RTS output SW control mode */
        DISABLE,                                             /* Disable tx output SW control mode */
        DISABLE,                                             /* Disable tx lin mode */
        DISABLE,                                             /* Disable rx lin mode */
        0,                                                   /* Tx break bit count for lin mode */
        UART_LSB_FIRST                                       /* UART each data byte is send out LSB-first */
    };

    /* Disable all interrupt */
    UART_IntMask(id, UART_INT_ALL,MASK);

    /* Disable uart before config */
    UART_Disable(id, UART_TXRX);

    /* UART init */
    UART_Init(id, &uartCfg);

    /* Enable tx free run mode */
    UART_TxFreeRun(id, ENABLE);

    /* Enable uart */
    UART_Enable(id, UART_TXRX);
}

static int uart_signal_get(uint8_t pin)
{
    //TODO no magic number is allowed here
    if (pin >= 12 && pin <=23) {
        return (pin + 6) % 12;
    } else if (pin >= 36 && pin <=45) {
        return (pin + 6) % 12;
    }
    return (pin % 12);
}

static int uart_func_get(uint8_t id, GLB_UART_SIG_FUN_Type uartfunc)
{
    switch (id) {
        case 0:
            return uartfunc;
        case 1:
            return (GLB_UART_SIG_FUN_UART1_RTS - GLB_UART_SIG_FUN_UART0_RTS) * 1 + uartfunc;
        case 2:
            return (GLB_UART_SIG_FUN_UART1_RTS - GLB_UART_SIG_FUN_UART0_RTS) * 1 + uartfunc;
        default:
            /*empty here*/
            //TODO should assert here?
            return uartfunc;
    }
}

static void uart_gpio_demo(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin)
{
    GLB_GPIO_Cfg_Type gpio_cfg;
    uint8_t uart_func, uart_sig;

    //FIXME SWAP set is NOT put here
    GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO12_GPIO23, 1);
    GLB_UART_Sig_Swap_Set(GLB_UART_SIG_SWAP_GRP_GPIO36_GPIO45, 1);

    //common GPIO cfg
    gpio_cfg.drive = 0;
    gpio_cfg.smtCtrl = 1;
    gpio_cfg.gpioMode = GPIO_MODE_AF;
    gpio_cfg.pullType = GPIO_PULL_UP;
    gpio_cfg.gpioFun = GPIO_FUN_UART;
    //cfg for UART Tx
    gpio_cfg.gpioPin = GLB_GPIO_PIN_0 + tx_pin;
    uart_func = uart_func_get(id, GLB_UART_SIG_FUN_UART0_TXD);
    uart_sig = uart_signal_get(gpio_cfg.gpioPin);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_sig, (GLB_UART_SIG_FUN_Type)uart_func);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_func, (GLB_UART_SIG_FUN_Type)uart_sig);
    GLB_GPIO_Init(&gpio_cfg);
    //cfg for UART Rx
    gpio_cfg.gpioPin = GLB_GPIO_PIN_0 + rx_pin;
    uart_func = uart_func_get(id, GLB_UART_SIG_FUN_UART0_RXD);
    uart_sig = uart_signal_get(gpio_cfg.gpioPin);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_sig, (GLB_UART_SIG_FUN_Type)uart_func);
    GLB_UART_Fun_Sel((GLB_UART_SIG_Type)uart_func, (GLB_UART_SIG_FUN_Type)uart_sig);
    GLB_GPIO_Init(&gpio_cfg);

    //Enable UART clock
    GLB_Set_UART_CLK(1, 0, 0);
}

int bl_uart_init(uint8_t id, uint8_t tx_pin, uint8_t rx_pin, uint8_t cts_pin, uint8_t rts_pin, uint32_t baudrate)
{
    UART_CFG_Type uart_dbg_cfg = {
    //   32 * 1000 * 1000, /*UART clock*/
      80*1000*1000, /*UART clock from XTAL*/
      2000000,          /* baudrate  */
      UART_DATABITS_8,  /* data bits  */
      UART_STOPBITS_1,  /* stop bits */
      UART_PARITY_NONE, /* parity  */
      DISABLE,          /* Disable auto flow control */
      DISABLE,          /* Disable rx input de-glitch function */
      DISABLE,          /* Disable RTS output SW control mode */
      DISABLE,          /* Disable tx output SW control mode */
      DISABLE,          /* Disable tx lin mode */
      DISABLE,          /* Disable rx lin mode */
      0,                /* Tx break bit count for lin mode */
      UART_LSB_FIRST,   /* UART each data byte is send out LSB-first */
    };

    UART_FifoCfg_Type fifoCfg = {
      16,      /* TX FIFO threshold */
      16,      /* RX FIFO threshold */
      DISABLE, /* Disable tx dma req/ack interface */
      DISABLE  /* Disable rx dma req/ack interface */
    };

    /* init debug uart gpio first */
    uart_gpio_demo(id, tx_pin, rx_pin, cts_pin, rts_pin);
    uart_init_demo(id);

    /* disable all interrupt */
    UART_IntMask(id, UART_INT_ALL, MASK);

    /* disable uart before config */
    UART_Disable(id, UART_TXRX);

    /* uart init with default configuration */
    UART_Init(id, &uart_dbg_cfg);

    /* UART fifo configuration */
    UART_FifoConfig(id, &fifoCfg);

    /* Enable tx free run mode */
    UART_TxFreeRun(id, ENABLE);

    /* Set rx time-out value */
    UART_SetRxTimeoutValue(id, 80);

    /* enable uart */
    UART_AutoBaudDetection(id, 0);
    UART_Enable(id, UART_TXRX);

    return 0;
}

/*This function is NOT thread safe*/
int bl_uart_data_send(uint8_t id, uint8_t data)
{

//    UART_SendData(id, &data,1);
    uint32_t UARTx = uartAddr[id];

    /* Wait for FIFO */
    while (UART_GetTxFifoCount(id) == 0) {
    }

    BL_WR_BYTE(UARTx + UART_FIFO_WDATA_OFFSET, data);

    return 0;
}

int bl_uart_data_recv(uint8_t id)
{
    int ret;
    uint32_t UARTx = uartAddr[id];

    /* Receive data */
    if (UART_GetRxFifoCount(id) > 0) {
        ret  = BL_RD_BYTE(UARTx + UART_FIFO_RDATA_OFFSET);
    } else {
        ret = -1;
    }

    return ret;
}

int bl_uart_int_rx_enable(uint8_t id)
{
    UART_SetRxTimeoutValue((UART_ID_Type)id, 24);
    UART_IntMask((UART_ID_Type)id, UART_INT_RX_FIFO_REQ, UNMASK);
    UART_IntMask((UART_ID_Type)id, UART_INT_RX_END, UNMASK);
    UART_IntMask((UART_ID_Type)id, UART_INT_RTO, UNMASK);
    return 0;
}

int bl_uart_int_rx_disable(uint8_t id)
{
    UART_IntMask((UART_ID_Type)id, UART_INT_RX_FIFO_REQ, MASK);
    UART_IntMask((UART_ID_Type)id, UART_INT_RX_END, MASK);
    UART_IntMask((UART_ID_Type)id, UART_INT_RTO, MASK);
    return 0;
}

int bl_uart_int_tx_enable(uint8_t id)
{
    UART_IntMask((UART_ID_Type)id, UART_INT_TX_FIFO_REQ, UNMASK);
    return 0;
}

int bl_uart_int_tx_disable(uint8_t id)
{
    UART_IntMask((UART_ID_Type)id, UART_INT_TX_FIFO_REQ, MASK);
    return 0;
}

int bl_uart_flush(uint8_t id)
{
    /* Wait for FIFO */
    while (UART_FIFO_TX_CNT != UART_GetTxFifoCount(id)) {
    }

    return 0;
}

void bl_uart_getdefconfig(uint8_t id, uint8_t *parity)
{
    if (NULL == parity) {
        return;
    }

    //*baudrate = 115200;/* not support set no baud */
    *parity = (uint8_t)UART_PARITY_NONE;
}

void bl_uart_setbaud(uint8_t id, uint32_t baud)
{
    //FIXME
    puts("uart is NOT implemented\r\n");
    while (1) {
    }
}

int bl_uart_int_enable(uint8_t id)
{
    switch (id) {
        case 0:
        {
            bl_uart_int_rx_enable(0);
            // bl_uart_int_tx_enable(0);
            bl_irq_register(UART0_IRQn, UART0_IRQHandler);
            bl_irq_enable(UART0_IRQn);
        }
        break;
        case 1:
        {
            bl_uart_int_rx_enable(1);
            // bl_uart_int_tx_enable(1);
            bl_irq_register(UART1_IRQn, UART1_IRQHandler);
            bl_irq_enable(UART1_IRQn);
        }
        break;
        case 2:
        {
            bl_uart_int_rx_enable(2);
            // bl_uart_int_tx_enable(2);
            bl_irq_register(UART2_IRQn, UART2_IRQHandler);
            bl_irq_enable(UART2_IRQn);
        }
        break;
        case 3:
        {
            bl_uart_int_rx_enable(3);
            // bl_uart_int_tx_enable(3);
            bl_irq_register(UART3_IRQn, UART3_IRQHandler);
            bl_irq_enable(UART3_IRQn);
        }
        break;
        default:
        {
            return -1;
        }
    }

    return 0;
}

int bl_uart_int_disable(uint8_t id)
{
    switch (id) {
        case 0:
        {
            bl_uart_int_rx_disable(0);
            bl_uart_int_tx_disable(0);
            bl_irq_unregister(UART0_IRQn, UART0_IRQHandler);
            bl_irq_disable(UART0_IRQn);
        }
        break;
        case 1:
        {
            bl_uart_int_rx_disable(1);
            bl_uart_int_tx_disable(1);
            bl_irq_unregister(UART1_IRQn, UART1_IRQHandler);
            bl_irq_disable(UART1_IRQn);
        }
        break;
        case 2:
        {
            bl_uart_int_rx_disable(2);
            bl_uart_int_tx_disable(2);
            bl_irq_unregister(UART2_IRQn, UART2_IRQHandler);
            bl_irq_disable(UART2_IRQn);
        }
        break;
        case 3:
        {
            bl_uart_int_rx_disable(3);
            bl_uart_int_tx_disable(3);
            bl_irq_unregister(UART3_IRQn, UART3_IRQHandler);
            bl_irq_disable(UART3_IRQn);
        }
        break;
        default:
        {
            return -1;
        }
    }

    return 0;
}

int bl_uart_int_rx_notify_register(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }

    g_uart_notify_arg[id].rx_cb = cb;
    g_uart_notify_arg[id].rx_cb_arg = arg;

    return 0;
}

int bl_uart_int_tx_notify_register(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }

    g_uart_notify_arg[id].tx_cb = cb;
    g_uart_notify_arg[id].tx_cb_arg = arg;

    return 0;
}

int bl_uart_int_rx_notify_unregister(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }
    g_uart_notify_arg[id].rx_cb = NULL;
    g_uart_notify_arg[id].rx_cb_arg = NULL;

    return 0;
}

int bl_uart_int_tx_notify_unregister(uint8_t id, cb_uart_notify_t cb, void *arg)
{
    if (!(id < UART_NUMBER_SUPPORTED)) {
        /*UART ID overflow*/
        return -1;
    }
    g_uart_notify_arg[id].tx_cb = NULL;
    g_uart_notify_arg[id].tx_cb_arg = NULL;

    return 0;
}

static inline void uart_generic_notify_handler(uint8_t id)
{
    cb_uart_notify_t cb;
    void *arg;
    uint32_t tmpVal = 0;
    uint32_t maskVal = 0;
    uint32_t UARTx = uartAddr[id];

    tmpVal = BL_RD_REG(UARTx,UART_INT_STS);
    maskVal = BL_RD_REG(UARTx,UART_INT_MASK);

    /* Length of uart tx data transfer arrived interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_UTX_END_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_UTX_END_MASK)){
        BL_WR_REG(UARTx,UART_INT_CLEAR,0x1);
    }

    /* Length of uart rx data transfer arrived interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_END_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_END_MASK)){
        BL_WR_REG(UARTx,UART_INT_CLEAR,0x2);

        /*Receive Data ready*/
        cb = g_uart_notify_arg[id].rx_cb;
        arg = g_uart_notify_arg[id].rx_cb_arg;

        if (cb) {
            /*notify up layer*/
            cb(arg);
        }
    }

    /* Tx fifo ready interrupt,auto-cleared when data is pushed */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_UTX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_UTX_FRDY_MASK)){
        /* Transmit data request interrupt */
        cb = g_uart_notify_arg[id].tx_cb;
        arg = g_uart_notify_arg[id].tx_cb_arg;

        if (cb) {
            /*notify up layer*/
            cb(arg);
        }
    }

    /* Rx fifo ready interrupt,auto-cleared when data is popped */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_FRDY_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_FRDY_MASK)){
        /*Receive Data ready*/

        cb = g_uart_notify_arg[id].rx_cb;
        arg = g_uart_notify_arg[id].rx_cb_arg;

        if (cb) {
            /*notify up layer*/
            cb(arg);
        }
    }

    /* Rx time-out interrupt */
    if (BL_IS_REG_BIT_SET(tmpVal,UART_URX_RTO_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_RTO_MASK)){
        BL_WR_REG(UARTx,UART_INT_CLEAR,0x10);

        /*Receive Data ready*/
        cb = g_uart_notify_arg[id].rx_cb;
        arg = g_uart_notify_arg[id].rx_cb_arg;

        if (cb) {
            /*notify up layer*/
            cb(arg);
        }
    }

    /* Rx parity check error interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_PCE_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_PCE_MASK)){
        BL_WR_REG(UARTx,UART_INT_CLEAR,0x20);
    }

    /* Tx fifo overflow/underflow error interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_UTX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_UTX_FER_MASK)){
    }

    /* Rx fifo overflow/underflow error interrupt */
    if(BL_IS_REG_BIT_SET(tmpVal,UART_URX_FER_INT) && !BL_IS_REG_BIT_SET(maskVal,UART_CR_URX_FER_MASK)){
    }

    return;
}

#ifdef BFLB_USE_HAL_DRIVER
void UART0_IRQHandler(void)
{
    uart_generic_notify_handler(0);
}

void UART1_IRQHandler(void)
{
    uart_generic_notify_handler(1);
}

void UART2_IRQHandler(void)
{
    uart_generic_notify_handler(2);
}

void UART3_IRQHandler(void)
{
    uart_generic_notify_handler(3);
}
#endif

