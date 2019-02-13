/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     dw_usart.c
 * @brief    CSI Source File for usart Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include <stdbool.h>
#include "csi_core.h"
#include "drv_usart.h"
#include "dw_usart.h"
#include "soc.h"

#define ERR_USART(errno) (CSI_DRV_ERRNO_USART_BASE | errno)

/*
 * setting config may be accessed when the USART is not
 * busy(USR[0]=0) and the DLAB bit(LCR[7]) is set.
 */

#define WAIT_USART_IDLE(addr)\
    do {                       \
        int32_t timecount = 0;  \
        while ((addr->USR & USR_UART_BUSY) && (timecount < UART_BUSY_TIMEOUT)) {\
            timecount++;\
        }\
        if (timecount >= UART_BUSY_TIMEOUT) {\
            return ERR_USART(EDRV_TIMEOUT);\
        }                                   \
    } while(0)

#define USART_NULL_PARAM_CHK(para)                   \
    do {                                        \
        if (para == NULL) {                     \
            return ERR_USART(EDRV_PARAMETER);   \
        }                                       \
    } while (0)


typedef struct {
    uint32_t base;
    uint32_t irq;
    usart_event_cb_t cb_event;           ///< Event callback
    void *cb_arg;
    uint32_t rx_total_num;
    uint32_t tx_total_num;
    uint8_t *rx_buf;
    uint8_t *tx_buf;
    volatile uint32_t rx_cnt;
    volatile uint32_t tx_cnt;
    volatile uint32_t tx_busy;
    volatile uint32_t rx_busy;
} dw_usart_priv_t;

static dw_usart_priv_t usart_instance[CONFIG_USART_NUM];

static const usart_capabilities_t usart_capabilities = {
    .asynchronous = 1,          /* supports USART (Asynchronous) mode */
    .synchronous_master = 0,    /* supports Synchronous Master mode */
    .synchronous_slave = 0,     /* supports Synchronous Slave mode */
    .single_wire = 0,           /* supports USART Single-wire mode */
    .event_tx_complete = 1,     /* Transmit completed event */
    .event_rx_timeout = 0,      /* Signal receive character timeout event */
};

/**
  \brief       set the bautrate of usart.
  \param[in]   addr  usart base to operate.
  \param[in]   baudrate.
  \param[in]   apbfreq the frequence of the apb.
  \return      error code
*/
static int32_t dw_usart_set_baudrate(dw_usart_reg_t *addr, uint32_t baudrate, uint32_t apbfreq)
{
    WAIT_USART_IDLE(addr);

    /* baudrate=(seriak clock freq)/(16*divisor); algorithm :rounding*/
    uint32_t divisor = ((apbfreq  * 10) / baudrate) >> 4;

    if ((divisor % 10) >= 5) {
        divisor = (divisor / 10) + 1;
    } else {
        divisor = divisor / 10;
    }

    addr->LCR |= LCR_SET_DLAB;
    /* DLL and DLH is lower 8-bits and higher 8-bits of divisor.*/
    addr->DLL = divisor & 0xff;
    addr->DLH = (divisor >> 8) & 0xff;
    /*
     * The DLAB must be cleared after the baudrate is setted
     * to access other registers.
     */
    addr->LCR &= (~LCR_SET_DLAB);

    return 0;
}

/**
  \brief       enable or disable parity.
  \param[in]   addr  usart base to operate.
  \param[in]   parity ODD=8, EVEN=16, or NONE=0.
  \return      error code
*/

static int32_t dw_usart_set_parity(dw_usart_reg_t *addr, usart_parity_e parity)
{
    WAIT_USART_IDLE(addr);

    switch (parity) {
        case USART_PARITY_NONE:
            /*CLear the PEN bit(LCR[3]) to disable parity.*/
            addr->LCR &= (~LCR_PARITY_ENABLE);
            break;

        case USART_PARITY_ODD:
            /* Set PEN and clear EPS(LCR[4]) to set the ODD parity. */
            addr->LCR |= LCR_PARITY_ENABLE;
            addr->LCR &= LCR_PARITY_ODD;
            break;

        case USART_PARITY_EVEN:
            /* Set PEN and EPS(LCR[4]) to set the EVEN parity.*/
            addr->LCR |= LCR_PARITY_ENABLE;
            addr->LCR |= LCR_PARITY_EVEN;
            break;

        default:
            return ERR_USART(EDRV_USART_PARITY);
    }

    return 0;
}

/**
  \brief       set the stop bit.
  \param[in]   addr  usart base to operate.
  \param[in]   stopbit two possible value: USART_STOP_BITS_1 and USART_STOP_BITS_2.
  \return      error code
*/
static int32_t dw_usart_set_stopbit(dw_usart_reg_t *addr, usart_stop_bits_e stopbit)
{
    WAIT_USART_IDLE(addr);

    switch (stopbit) {
        case USART_STOP_BITS_1:
            /* Clear the STOP bit to set 1 stop bit*/
            addr->LCR &= LCR_STOP_BIT1;
            break;

        case USART_STOP_BITS_2:
            /*
            * If the STOP bit is set "1",we'd gotten 1.5 stop
            * bits when DLS(LCR[1:0]) is zero, else 2 stop bits.
            */
            addr->LCR |= LCR_STOP_BIT2;
            break;

        default:
            return ERR_USART(EDRV_USART_STOP_BITS);
    }

    return 0;
}

/**
  \brief       the transmit data length,and we have four choices:5, 6, 7, and 8 bits.
  \param[in]   addr  usart base to operate.
  \param[in]   databits the data length that user decides.
  \return      error code
*/
static int32_t dw_usart_set_databit(dw_usart_reg_t *addr, usart_data_bits_e databits)
{
    WAIT_USART_IDLE(addr);
   /* The word size decides by the DLS bits(LCR[1:0]), and the
    * corresponding relationship between them is:
    *   DLS   word size
    *       00 -- 5 bits
    *       01 -- 6 bits
    *       10 -- 7 bits
    *       11 -- 8 bits
    */

    switch (databits) {
        case USART_DATA_BITS_5:
            addr->LCR &= LCR_WORD_SIZE_5;
            break;

        case USART_DATA_BITS_6:
            addr->LCR &= 0xfd;
            addr->LCR |= LCR_WORD_SIZE_6;
            break;

        case USART_DATA_BITS_7:
            addr->LCR &= 0xfe;
            addr->LCR |= LCR_WORD_SIZE_7;
            break;

        case USART_DATA_BITS_8:
            addr->LCR |= LCR_WORD_SIZE_8;
            break;

        default:
            return ERR_USART(EDRV_USART_DATA_BITS);
    }

    return 0;
}

/**
  \brief       get character in query mode.
  \param[in]   instance  usart instance to operate.
  \param[in]   the pointer to the recieve charater.
  \return      error code
*/
int32_t dw_usart_getchar(usart_handle_t handle, uint8_t *ch)
{
    dw_usart_priv_t *usart_priv = handle;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);

    while (!(addr->LSR & LSR_DATA_READY));

    *ch = addr->RBR;

    return 0;
}

/**
  \brief       get character in query mode.
  \param[in]   instance  usart instance to operate.
  \param[in]   the pointer to the recieve charater.
  \return      error code
*/
int32_t dw_usart_getchar_no_poll(usart_handle_t handle, uint8_t *ch)
{
    dw_usart_priv_t *usart_priv = handle;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);

    if (addr->LSR & LSR_DATA_READY)
    {
        *ch = addr->RBR;
        return 0;
    }
    else
    {
        return -1;
    }
}

int32_t dw_usart_set_int_flag(usart_handle_t handle,uint32_t flag)
{
    dw_usart_priv_t *usart_priv = handle;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);

    addr->IER |= flag;

    return 0;
}

int32_t dw_usart_clr_int_flag(usart_handle_t handle,uint32_t flag)
{
    dw_usart_priv_t *usart_priv = handle;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);

    addr->IER &= ~flag;

    return 0;
}

/**
  \brief       transmit character in query mode.
  \param[in]   instance  usart instance to operate.
  \param[in]   ch  the input charater
  \return      error code
*/
int32_t dw_usart_putchar(usart_handle_t handle, uint8_t ch)
{
    dw_usart_priv_t *usart_priv = handle;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);

    while ((!(addr->LSR & DW_LSR_TRANS_EMPTY)));

	if (ch == '\n')
	{
		addr->THR = '\r';

		while ((!(addr->LSR & DW_LSR_TRANS_EMPTY))) ;
	}

    addr->THR = ch;

    return 0;

}

/**
  \brief       interrupt service function for transmitter holding register empty.
  \param[in]   usart_priv usart private to operate.
*/
static void dw_usart_intr_threshold_empty(dw_usart_priv_t *usart_priv)
{
    if (usart_priv->tx_total_num == 0) {
        return;
    }

    uint8_t remain_txdata = usart_priv->tx_total_num - usart_priv->tx_cnt;

    uint8_t txdata_num = (remain_txdata > UART_MAX_FIFO) ? UART_MAX_FIFO : remain_txdata;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);
    uint8_t i = 0u;

    for (i = 0; i < txdata_num; i++) {
        addr->THR = *((uint8_t *)usart_priv->tx_buf);
        usart_priv->tx_cnt++;
        usart_priv->tx_buf++;
    }

    if (usart_priv->tx_cnt >= usart_priv->tx_total_num) {
        addr->IER &= (~IER_THRE_INT_ENABLE);

        while ((!(addr->LSR & DW_LSR_TEMT)));

        usart_priv->tx_cnt = 0;
        usart_priv->tx_busy = 0;
        usart_priv->tx_buf = NULL;
        usart_priv->tx_total_num = 0;

        if (usart_priv->cb_event) {
            usart_priv->cb_event(USART_EVENT_SEND_COMPLETE, usart_priv->cb_arg);
        }
    }

}

/**
  \brief        interrupt service function for receiver data available.
  \param[in]   usart_priv usart private to operate.
*/
static void dw_usart_intr_recv_data(dw_usart_priv_t *usart_priv)
{
    if (usart_priv->cb_event && (usart_priv->rx_total_num == 0)) {
        usart_priv->cb_event(USART_EVENT_RECEIVED, usart_priv->cb_arg);
        return;
    }

    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);
    uint8_t data = addr->RBR;

    if ((usart_priv->rx_total_num == 0) || (usart_priv->rx_buf == NULL)) {
        return;
    }

    *((uint8_t *)usart_priv->rx_buf) = data;
    usart_priv->rx_cnt++;
    usart_priv->rx_buf++;

    if (usart_priv->rx_cnt >= usart_priv->rx_total_num) {
        usart_priv->rx_cnt = 0;
        usart_priv->rx_buf = NULL;
        usart_priv->rx_busy = 0;
        usart_priv->rx_total_num = 0;

        if (usart_priv->cb_event) {
            usart_priv->cb_event(USART_EVENT_RECEIVE_COMPLETE, usart_priv->cb_arg);
        }
    }

}

/**
  \brief       the interrupt service function.
  \param[in]   index of usart instance.
*/
void dw_usart_irqhandler(int32_t idx)
{
    dw_usart_priv_t *usart_priv = &usart_instance[idx];
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);

    uint8_t intr_state = addr->IIR & 0xf;

    switch (intr_state) {
        case DW_IIR_THR_EMPTY:       /* interrupt source:transmitter holding register empty */
            dw_usart_intr_threshold_empty(usart_priv);
            break;

        case DW_IIR_RECV_DATA:       /* interrupt source:receiver data available or receiver fifo trigger level reached */
            dw_usart_intr_recv_data(usart_priv);
            break;

        default:
            break;
    }
}

int32_t __attribute__((weak)) target_usart_init(pin_t tx, pin_t rx, uint32_t *base, uint32_t *irq)
{
    return -1;
}

/**
  \brief       Get driver capabilities.
  \param[in]   handle  usart handle to operate.
  \return      \ref usart_capabilities_t
*/
usart_capabilities_t csi_usart_get_capabilities(usart_handle_t handle)
{
    return usart_capabilities;
}

/**
  \brief       Initialize USART Interface. 1. Initializes the resources needed for the USART interface 2.registers event callback function
  \param[in]   usart pin of tx
  \param[in]   usart pin of rx
  \param[in]   cb_event  Pointer to \ref usart_event_cb_t
  \return      return usart handle if success
*/
usart_handle_t csi_usart_initialize(pin_t tx, pin_t rx, usart_event_cb_t cb_event, void *cb_arg)
{
    uint32_t base = 0u;
    uint32_t irq = 0u;

    int32_t idx = target_usart_init(tx, rx, &base, &irq);

    if (idx < 0 || idx >= CONFIG_USART_NUM) {
        return NULL;
    }

    dw_usart_priv_t *usart_priv = &usart_instance[idx];
    usart_priv->base = base;
    usart_priv->irq = irq;
    usart_priv->cb_event = cb_event;
    usart_priv->cb_arg = cb_arg;

    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);
    /* FIFO enable */
    addr->FCR = DW_FCR_FIFOE;
//    /* enable received data available */
//    addr->IER = IER_RDA_INT_ENABLE;
    drv_nvic_enable_irq(usart_priv->irq);

    return usart_priv;
}

/**
  \brief       De-initialize UART Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  usart handle to operate.
  \return      error code
*/
int32_t csi_usart_uninitialize(usart_handle_t handle)
{
    USART_NULL_PARAM_CHK(handle);

    dw_usart_priv_t *usart_priv = handle;

    drv_nvic_disable_irq(usart_priv->irq);
    usart_priv->cb_event   = NULL;

    return 0;
}

/**
  \brief       config usart mode.
  \param[in]   handle  usart handle to operate.
  \param[in]   sysclk    configured system clock.
  \param[in]   mode      \ref usart_mode_e
  \param[in]   parity    \ref usart_parity_e
  \param[in]   stopbits  \ref usart_stop_bits_e
  \param[in]   bits      \ref usart_data_bits_e
  \param[in]   baud      configured baud
  \return      error code
*/
int32_t csi_usart_config(usart_handle_t handle,
                         uint32_t sysclk,
                         uint32_t baud,
                         usart_mode_e mode,
                         usart_parity_e parity,
                         usart_stop_bits_e stopbits,
                         usart_data_bits_e bits)
{
    USART_NULL_PARAM_CHK(handle);
    dw_usart_priv_t *usart_priv = handle;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);

    /* control the data_bit of the usart*/
    int32_t ret = dw_usart_set_baudrate(addr, baud, sysclk);

    if (ret < 0) {
        return ret;
    }

    /* control the parity of the usart*/
    ret = dw_usart_set_parity(addr, parity);

    if (ret < 0) {
        return ret;
    }

    /* control the stopbit of the usart*/
    ret = dw_usart_set_stopbit(addr, stopbits);

    if (ret < 0) {
        return ret;
    }

    ret = dw_usart_set_databit(addr, bits);

    if (ret < 0) {
        return ret;
    }

    return 0;
}
/**
  \brief       config usart default tx value. used in syn mode
  \param[in]   handle  usart handle to operate.
  \param[in]   value  default tx value
  \return      error code
*/
int32_t csi_usart_set_default_tx_value(usart_handle_t handle, uint32_t value)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(EDRV_UNSUPPORTED);
}

/**
  \brief       Start sending data to UART transmitter,(received data is ignored).
               The function is non-blocking,UART_EVENT_TRANSFER_COMPLETE is signaled when transfer completes.
               csi_usart_get_status can indicates if transmission is still in progress or pending
  \param[in]   handle  usart handle to operate.
  \param[in]   data  Pointer to buffer with data to send to UART transmitter. data_type is : uint8_t for 1..8 data bits, uint16_t for 9..16 data bits,uint32_t for 17..32 data bits,
  \param[in]   num   Number of data items to send
  \return      error code
*/
int32_t csi_usart_send(usart_handle_t handle, const void *data, uint32_t num)
{
    USART_NULL_PARAM_CHK(handle);
    USART_NULL_PARAM_CHK(data);

    if (num == 0) {
        return ERR_USART(EDRV_PARAMETER);
    }

    dw_usart_priv_t *usart_priv = handle;
    uint8_t *source = NULL;
    source = (uint8_t *)data;

    usart_priv->tx_buf = (uint8_t *)data;
    usart_priv->tx_total_num = num;
    usart_priv->tx_cnt = 0;
    usart_priv->tx_busy = 1;

    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);
    /* enable the interrupt*/
    addr->IER |= IER_THRE_INT_ENABLE;
    return 0;
}

/**
  \brief       Abort Send data to UART transmitter
  \param[in]   handle  usart handle to operate.
  \return      error code
*/
int32_t csi_usart_abort_send(usart_handle_t handle)
{
    USART_NULL_PARAM_CHK(handle);
    dw_usart_priv_t *usart_priv = handle;

    usart_priv->tx_cnt = usart_priv->tx_total_num;
    return 0;
}

/**
  \brief       Start receiving data from UART receiver.transmits the default value as specified by csi_usart_set_default_tx_value
  \param[in]   handle  usart handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from UART receiver
  \param[in]   num   Number of data items to receive
  \return      error code
*/
int32_t csi_usart_receive(usart_handle_t handle, void *data, uint32_t num)
{
    USART_NULL_PARAM_CHK(handle);
    USART_NULL_PARAM_CHK(data);

    uint8_t *dest = NULL;
    dw_usart_priv_t *usart_priv = handle;
    dest = (uint8_t *)data;

    usart_priv->rx_buf = (uint8_t *)data;   // Save receive buffer usart
    usart_priv->rx_total_num = num;         // Save number of data to be received
    usart_priv->rx_cnt = 0;
    usart_priv->rx_busy = 1;

    return 0;

}

/**
  \brief       query data from UART receiver FIFO.
  \param[in]   handle  usart handle to operate.
  \param[out]  data  Pointer to buffer for data to receive from UART receiver
  \param[in]   num   Number of data items to receive
  \return      receive fifo data num
*/
int32_t csi_usart_receive_query(usart_handle_t handle, void *data, uint32_t num)
{
    USART_NULL_PARAM_CHK(handle);
    USART_NULL_PARAM_CHK(data);

    dw_usart_priv_t *usart_priv = handle;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);
    int32_t recv_num = 0;

    while (addr->LSR & 0x1) {
        *((uint8_t *)data++) = addr->RBR;
        recv_num++;

        if (recv_num >= num) {
            break;
        }
    }

    return recv_num;

}

/**
  \brief       Abort Receive data from UART receiver
  \param[in]   handle  usart handle to operate.
  \return      error code
*/
int32_t csi_usart_abort_receive(usart_handle_t handle)
{
    USART_NULL_PARAM_CHK(handle);
    dw_usart_priv_t *usart_priv = handle;

    usart_priv->rx_cnt = usart_priv->rx_total_num;
    return 0;
}

/**
  \brief       Start sending/receiving data to/from UART transmitter/receiver.
  \param[in]   handle  usart handle to operate.
  \param[in]   data_out  Pointer to buffer with data to send to USART transmitter
  \param[out]  data_in   Pointer to buffer for data to receive from USART receiver
  \param[in]   num       Number of data items to transfer
  \return      error code
*/
int32_t csi_usart_transfer(usart_handle_t handle, const void *data_out, void *data_in, uint32_t num)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(EDRV_UNSUPPORTED);
}

/**
  \brief       abort sending/receiving data to/from USART transmitter/receiver.
  \param[in]   handle  usart handle to operate.
  \return      error code
*/
int32_t csi_usart_abort_transfer(usart_handle_t handle)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(EDRV_UNSUPPORTED);
}

/**
  \brief       Get USART status.
  \param[in]   handle  usart handle to operate.
  \return      USART status \ref usart_status_t
*/
usart_status_t csi_usart_get_status(usart_handle_t handle)
{
    usart_status_t usart_status;
    dw_usart_priv_t *usart_priv = handle;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);
    uint32_t line_status_reg    = addr->LSR;

    usart_status.tx_busy = usart_priv->tx_busy;
    usart_status.rx_busy = usart_priv->rx_busy;

    if (line_status_reg & DW_LSR_BI) {
        usart_status.rx_break = 1;
    }

    if (line_status_reg & DW_LSR_FE) {
        usart_status.rx_framing_error = 1;
    }

    if (line_status_reg & DW_LSR_PE) {
        usart_status.rx_parity_error = 1;
    }

    return usart_status;
}

/**
  \brief       control the transmit.
  \param[in]   handle  usart handle to operate.
  \param[in]   enable the transmitter.
  \return      error code
*/
int32_t csi_usart_control_tx(usart_handle_t handle, bool enable)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(EDRV_UNSUPPORTED);
}

/**
  \brief       control the receive.
  \param[in]   handle  usart handle to operate.
  \param[in]   enable the receive.
  \return      error code
*/
int32_t csi_usart_control_rx(usart_handle_t handle, bool enable)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(EDRV_UNSUPPORTED);
}

/**
  \brief       control the break.
  \param[in]   handle  usart handle to operate.
  \param[in]   enable the break.
  \return      error code
*/
int32_t csi_usart_control_break(usart_handle_t handle, bool enable)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(EDRV_UNSUPPORTED);
}

/**
  \brief       flush receive/send data.
  \param[in]   handle usart handle to operate.
  \param[in]   type \ref usart_flush_type_e.
  \return      error code
*/
int32_t csi_usart_flush(usart_handle_t handle, usart_flush_type_e type)
{
    USART_NULL_PARAM_CHK(handle);

    dw_usart_priv_t *usart_priv = handle;
    dw_usart_reg_t *addr = (dw_usart_reg_t *)(usart_priv->base);

    if (type == USART_FLUSH_WRITE) {
        addr->FCR |= DW_FCR_XFIFOR;
    } else if (type == USART_FLUSH_READ) {
        addr->FCR |= DW_FCR_RFIFOR;
    } else {
        return ERR_USART(EDRV_PARAMETER);
    }

    return 0;
}
