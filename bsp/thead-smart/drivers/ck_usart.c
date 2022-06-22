/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      CSI Source File for usart Driver
 */

#include <csi_config.h>
#include <stdbool.h>
#include <string.h>
#include <drv_irq.h>
#include <drv_usart.h>
#include <ck_usart.h>
#include <soc.h>
#include <csi_core.h>

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
            return ERR_USART(DRV_ERROR_TIMEOUT);\
        }                                   \
    } while(0)

#define USART_NULL_PARAM_CHK(para) HANDLE_PARAM_CHK(para, ERR_USART(DRV_ERROR_PARAMETER))

typedef struct
{
    uint32_t base;
    uint32_t irq;
    usart_event_cb_t cb_event;           ///< Event callback
    uint32_t rx_total_num;
    uint32_t tx_total_num;
    uint8_t *rx_buf;
    uint8_t *tx_buf;
    volatile uint32_t rx_cnt;
    volatile uint32_t tx_cnt;
    volatile uint32_t tx_busy;
    volatile uint32_t rx_busy;
    uint32_t last_tx_num;
    uint32_t last_rx_num;
    int32_t idx;
} ck_usart_priv_t;

extern int32_t target_usart_init(int32_t idx, uint32_t *base, uint32_t *irq, void **handler);

static ck_usart_priv_t usart_instance[CONFIG_USART_NUM];

static const usart_capabilities_t usart_capabilities =
{
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
  \return      error code
*/
int32_t csi_usart_config_baudrate(usart_handle_t handle, uint32_t baud)
{
    USART_NULL_PARAM_CHK(handle);
    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);


    WAIT_USART_IDLE(addr);

    /* baudrate=(seriak clock freq)/(16*divisor); algorithm :rounding*/
    uint32_t divisor = ((drv_get_usart_freq(usart_priv->idx)  * 10) / baud) >> 4;

    if ((divisor % 10) >= 5)
    {
        divisor = (divisor / 10) + 1;
    } else
    {
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
  \brief       config usart mode.
  \param[in]   handle  usart handle to operate.
  \param[in]   mode    \ref usart_mode_e
  \return      error code
*/
int32_t csi_usart_config_mode(usart_handle_t handle, usart_mode_e mode)
{
    USART_NULL_PARAM_CHK(handle);

    if (mode == USART_MODE_ASYNCHRONOUS)
    {
        return 0;
    }

    return ERR_USART(USART_ERROR_MODE);
}

/**
  \brief       config usart parity.
  \param[in]   handle  usart handle to operate.
  \param[in]   parity    \ref usart_parity_e
  \return      error code
*/
int32_t csi_usart_config_parity(usart_handle_t handle, usart_parity_e parity)
{
    USART_NULL_PARAM_CHK(handle);
    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    WAIT_USART_IDLE(addr);

    switch (parity)
    {
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
            return ERR_USART(USART_ERROR_PARITY);
    }

    return 0;
}

/**
  \brief       config usart stop bit number.
  \param[in]   handle  usart handle to operate.
  \param[in]   stopbits  \ref usart_stop_bits_e
  \return      error code
*/
int32_t csi_usart_config_stopbits(usart_handle_t handle, usart_stop_bits_e stopbit)
{
    USART_NULL_PARAM_CHK(handle);
    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    WAIT_USART_IDLE(addr);

    switch (stopbit)
    {
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
            return ERR_USART(USART_ERROR_STOP_BITS);
    }

    return 0;
}

/**
  \brief       config usart data length.
  \param[in]   handle  usart handle to operate.
  \param[in]   databits      \ref usart_data_bits_e
  \return      error code
*/
int32_t csi_usart_config_databits(usart_handle_t handle, usart_data_bits_e databits)
{
    USART_NULL_PARAM_CHK(handle);
    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    WAIT_USART_IDLE(addr);
    /* The word size decides by the DLS bits(LCR[1:0]), and the
     * corresponding relationship between them is:
     *   DLS   word size
     *       00 -- 5 bits
     *       01 -- 6 bits
     *       10 -- 7 bits
     *       11 -- 8 bits
     */

    switch (databits)
    {
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
            return ERR_USART(USART_ERROR_DATA_BITS);
    }

    return 0;
}


int32_t ck_usart_set_int_flag(usart_handle_t handle,uint32_t flag)
{
    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    addr->IER |= flag;

    return 0;
}

int32_t ck_usart_clr_int_flag(usart_handle_t handle,uint32_t flag)
{
    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    addr->IER &= ~flag;

    return 0;
}


/**
  \brief       get character in query mode.
  \param[in]   instance  usart instance to operate.
  \param[in]   the pointer to the recieve charater.
  \return      error code
*/
int32_t csi_usart_getchar(usart_handle_t handle, uint8_t *ch)
{
    USART_NULL_PARAM_CHK(handle);
    USART_NULL_PARAM_CHK(ch);

    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

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
int csi_uart_getchar(usart_handle_t handle)
{
    volatile int ch;
    USART_NULL_PARAM_CHK(handle);

    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    ch = -1;

    if (addr->LSR & LSR_DATA_READY)
    {
        ch = addr->RBR & 0xff;
    }

    return ch;
}


/**
  \brief       transmit character in query mode.
  \param[in]   instance  usart instance to operate.
  \param[in]   ch  the input charater
  \return      error code
*/
int32_t csi_usart_putchar(usart_handle_t handle, uint8_t ch)
{
    USART_NULL_PARAM_CHK(handle);
    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);
    uint32_t timecount = 0;

    while ((!(addr->LSR & DW_LSR_TRANS_EMPTY)))
    {
        timecount++;

        if (timecount >= UART_BUSY_TIMEOUT)
        {
            return ERR_USART(DRV_ERROR_TIMEOUT);
        }
    }

    addr->THR = ch;

    return 0;

}

/**
  \brief       interrupt service function for transmitter holding register empty.
  \param[in]   usart_priv usart private to operate.
*/
void ck_usart_intr_threshold_empty(int32_t idx, ck_usart_priv_t *usart_priv)
{
    if (usart_priv->tx_total_num == 0)
    {
        return;
    }

    volatile int i = 500;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    if (usart_priv->tx_cnt >= usart_priv->tx_total_num)
    {
        addr->IER &= (~IER_THRE_INT_ENABLE);
        usart_priv->last_tx_num = usart_priv->tx_total_num;

        /* fix hardware bug */
        while (addr->USR & USR_UART_BUSY);

        i = 500;

        while (i--);

        usart_priv->tx_cnt = 0;
        usart_priv->tx_busy = 0;
        usart_priv->tx_buf = NULL;
        usart_priv->tx_total_num = 0;

        if (usart_priv->cb_event)
        {
            usart_priv->cb_event(idx, USART_EVENT_SEND_COMPLETE);
        }
    } else
    {
        /* fix hardware bug */
        while (addr->USR & USR_UART_BUSY);

        i = 500;

        while (i--);

        addr->THR = *((uint8_t *)usart_priv->tx_buf);
        usart_priv->tx_cnt++;
        usart_priv->tx_buf++;
    }
}

/**
  \brief        interrupt service function for receiver data available.
  \param[in]   usart_priv usart private to operate.
*/
static void ck_usart_intr_recv_data(int32_t idx, ck_usart_priv_t *usart_priv)
{
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);
    uint8_t data = addr->RBR;

    *((uint8_t *)usart_priv->rx_buf) = data;
    usart_priv->rx_cnt++;
    usart_priv->rx_buf++;

    if (usart_priv->rx_cnt >= usart_priv->rx_total_num)
    {
        usart_priv->last_rx_num = usart_priv->rx_total_num;
        usart_priv->rx_cnt = 0;
        usart_priv->rx_buf = NULL;
        usart_priv->rx_busy = 0;
        usart_priv->rx_total_num = 0;

        if (usart_priv->cb_event)
        {
            usart_priv->cb_event(idx, USART_EVENT_RECEIVE_COMPLETE);
        }
    }

}

/**
  \brief        interrupt service function for receiver line.
  \param[in]   usart_priv usart private to operate.
*/
static void ck_usart_intr_recv_line(int32_t idx, ck_usart_priv_t *usart_priv)
{
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);
    uint32_t lsr_stat = addr->LSR;

    addr->IER &= (~IER_THRE_INT_ENABLE);

    uint32_t timecount = 0;

    while (addr->LSR & 0x1)
    {
        addr->RBR;
        timecount++;

        if (timecount >= UART_BUSY_TIMEOUT)
        {
            if (usart_priv->cb_event)
            {
                usart_priv->cb_event(idx, USART_EVENT_RX_TIMEOUT);
            }

            return;
        }
    }

    /** Break Interrupt bit. This is used to indicate the detection of a
      * break sequence on the serial input data.
      */
    if (lsr_stat & DW_LSR_BI)
    {
        if (usart_priv->cb_event)
        {
            usart_priv->cb_event(idx, USART_EVENT_RX_BREAK);
        }

        return;
    }

    /** Framing Error bit. This is used to indicate the occurrence of a
      * framing error in the receiver. A framing error occurs when the receiver
      * does not detect a valid STOP bit in the received data.
      */
    if (lsr_stat & DW_LSR_FE)
    {
        if (usart_priv->cb_event)
        {
            usart_priv->cb_event(idx, USART_EVENT_RX_FRAMING_ERROR);
        }

        return;
    }

    /** Framing Error bit. This is used to indicate the occurrence of a
      * framing error in the receiver. A framing error occurs when the
      * receiver does not detect a valid STOP bit in the received data.
      */
    if (lsr_stat & DW_LSR_PE)
    {
        if (usart_priv->cb_event)
        {
            usart_priv->cb_event(idx, USART_EVENT_RX_PARITY_ERROR);
        }

        return;
    }

    /** Overrun error bit. This is used to indicate the occurrence of an overrun error.
      * This occurs if a new data character was received before the previous data was read.
      */
    if (lsr_stat & DW_LSR_OE)
    {
        if (usart_priv->cb_event)
        {
            usart_priv->cb_event(idx, USART_EVENT_RX_OVERFLOW);
        }

        return;
    }
}
/**
  \brief        interrupt service function for character timeout.
  \param[in]   usart_priv usart private to operate.
*/
static void ck_usart_intr_char_timeout(int32_t idx, ck_usart_priv_t *usart_priv)
{
    if ((usart_priv->rx_total_num != 0) && (usart_priv->rx_buf != NULL))
    {
        ck_usart_intr_recv_data(idx, usart_priv);
        return;
    }

    if (usart_priv->cb_event)
    {
        usart_priv->cb_event(idx, USART_EVENT_RECEIVED);
    } else
    {
        ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

        uint32_t timecount = 0;

        while (addr->LSR & 0x1)
        {
            addr->RBR;
            timecount++;

            if (timecount >= UART_BUSY_TIMEOUT)
            {
                if (usart_priv->cb_event)
                {
                    usart_priv->cb_event(idx, USART_EVENT_RX_TIMEOUT);
                }

                return;
            }
        }
    }
}

/**
  \brief       the interrupt service function.
  \param[in]   index of usart instance.
*/
void ck_usart_irqhandler(int32_t idx)
{
    ck_usart_priv_t *usart_priv = &usart_instance[idx];
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    uint8_t intr_state = addr->IIR & 0xf;

    switch (intr_state)
    {
        case DW_IIR_THR_EMPTY:       /* interrupt source:transmitter holding register empty */
            ck_usart_intr_threshold_empty(idx, usart_priv);
            break;

        case DW_IIR_RECV_DATA:       /* interrupt source:receiver data available or receiver fifo trigger level reached */
            ck_usart_intr_char_timeout(idx, usart_priv);
            //ck_usart_intr_recv_data(idx, usart_priv);
            break;

        case DW_IIR_RECV_LINE:
            ck_usart_intr_recv_line(idx, usart_priv);
            break;

        case DW_IIR_CHAR_TIMEOUT:
            ck_usart_intr_char_timeout(idx, usart_priv);
            break;

        default:
            break;
    }
}

/**
  \brief       Get driver capabilities.
  \param[in]   idx usart index
  \return      \ref usart_capabilities_t
*/
usart_capabilities_t csi_usart_get_capabilities(int32_t idx)
{
    if (idx < 0 || idx >= CONFIG_USART_NUM)
    {
        usart_capabilities_t ret;
        memset(&ret, 0, sizeof(usart_capabilities_t));
        return ret;
    }

    return usart_capabilities;
}

/**
  \brief       Initialize USART Interface. 1. Initializes the resources needed for the USART interface 2.registers event callback function
  \param[in]   idx usart index
  \param[in]   cb_event  Pointer to \ref usart_event_cb_t
  \return      return usart handle if success
*/
usart_handle_t csi_usart_initialize(int32_t idx, usart_event_cb_t cb_event)
{
    uint32_t base = 0u;
    uint32_t irq = 0u;
    void *handler;

    int32_t ret = target_usart_init(idx, &base, &irq, &handler);

    if (ret < 0 || ret >= CONFIG_USART_NUM)
    {
        return NULL;
    }

    ck_usart_priv_t *usart_priv = &usart_instance[idx];
    usart_priv->base = base;
    usart_priv->irq = irq;
    usart_priv->cb_event = cb_event;
    usart_priv->idx = idx;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    /* enable received data available */
    addr->IER = IER_RDA_INT_ENABLE | IIR_RECV_LINE_ENABLE;
    drv_irq_register(usart_priv->irq, handler);
    drv_irq_enable(usart_priv->irq);

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

    ck_usart_priv_t *usart_priv = handle;

    drv_irq_disable(usart_priv->irq);
    drv_irq_unregister(usart_priv->irq);
    usart_priv->cb_event   = NULL;

    return 0;
}

/**
  \brief       config usart mode.
  \param[in]   handle  usart handle to operate.
  \param[in]   baud      baud rate
  \param[in]   mode      \ref usart_mode_e
  \param[in]   parity    \ref usart_parity_e
  \param[in]   stopbits  \ref usart_stop_bits_e
  \param[in]   bits      \ref usart_data_bits_e
  \return      error code
*/
int32_t csi_usart_config(usart_handle_t handle,
                         uint32_t baud,
                         usart_mode_e mode,
                         usart_parity_e parity,
                         usart_stop_bits_e stopbits,
                         usart_data_bits_e bits)
{
    int32_t ret;

    /* control the data_bit of the usart*/
    ret = csi_usart_config_baudrate(handle, baud);

    if (ret < 0)
    {
        return ret;
    }

    /* control mode of the usart*/
    ret = csi_usart_config_mode(handle, mode);

    if (ret < 0)
    {
        return ret;
    }

    /* control the parity of the usart*/
    ret = csi_usart_config_parity(handle, parity);

    if (ret < 0)
    {
        return ret;
    }

    /* control the stopbit of the usart*/
    ret = csi_usart_config_stopbits(handle, stopbits);

    if (ret < 0)
    {
        return ret;
    }

    ret = csi_usart_config_databits(handle, bits);

    if (ret < 0)
    {
        return ret;
    }

    return 0;
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

    if (num == 0)
    {
        return ERR_USART(DRV_ERROR_PARAMETER);
    }

    ck_usart_priv_t *usart_priv = handle;

    usart_priv->tx_buf = (uint8_t *)data;
    usart_priv->tx_total_num = num;
    usart_priv->tx_cnt = 0;
    usart_priv->tx_busy = 1;
    usart_priv->last_tx_num = 0;

    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);
    ck_usart_intr_threshold_empty(usart_priv->idx, usart_priv);
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
    ck_usart_priv_t *usart_priv = handle;

    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);
    addr->IER &= (~IER_THRE_INT_ENABLE);

    usart_priv->tx_cnt = usart_priv->tx_total_num;
    usart_priv->tx_cnt = 0;
    usart_priv->tx_busy = 0;
    usart_priv->tx_buf = NULL;
    usart_priv->tx_total_num = 0;
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

    ck_usart_priv_t *usart_priv = handle;

    usart_priv->rx_buf = (uint8_t *)data;   // Save receive buffer usart
    usart_priv->rx_total_num = num;         // Save number of data to be received
    usart_priv->rx_cnt = 0;
    usart_priv->rx_busy = 1;
    usart_priv->last_rx_num = 0;

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

    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);
    int32_t recv_num = 0;
    uint8_t *dest = (uint8_t *)data;

    while (addr->LSR & 0x1)
    {
        *dest++ = addr->RBR;
        recv_num++;

        if (recv_num >= num)
        {
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
    ck_usart_priv_t *usart_priv = handle;

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
    return ERR_USART(DRV_ERROR_UNSUPPORTED);
}

/**
  \brief       abort sending/receiving data to/from USART transmitter/receiver.
  \param[in]   handle  usart handle to operate.
  \return      error code
*/
int32_t csi_usart_abort_transfer(usart_handle_t handle)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(DRV_ERROR_UNSUPPORTED);
}

/**
  \brief       Get USART status.
  \param[in]   handle  usart handle to operate.
  \return      USART status \ref usart_status_t
*/
usart_status_t csi_usart_get_status(usart_handle_t handle)
{
    usart_status_t usart_status;

    memset(&usart_status, 0, sizeof(usart_status_t));

    if (handle == NULL)
    {
        return usart_status;
    }

    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);
    uint32_t line_status_reg    = addr->LSR;

    usart_status.tx_busy = usart_priv->tx_busy;
    usart_status.rx_busy = usart_priv->rx_busy;

    if (line_status_reg & DW_LSR_BI)
    {
        usart_status.rx_break = 1;
    }

    if (line_status_reg & DW_LSR_FE)
    {
        usart_status.rx_framing_error = 1;
    }

    if (line_status_reg & DW_LSR_PE)
    {
        usart_status.rx_parity_error = 1;
    }

    usart_status.tx_enable  = 1;
    usart_status.rx_enable  = 1;

    return usart_status;
}

/**
  \brief       control the transmit.
  \param[in]   handle  usart handle to operate.
  \param[in]   1 - enable the transmitter. 0 - disable the transmitter
  \return      error code
*/
int32_t csi_usart_control_tx(usart_handle_t handle, uint32_t enable)
{
    USART_NULL_PARAM_CHK(handle);
    return 0;
}

/**
  \brief       control the receive.
  \param[in]   handle  usart handle to operate.
  \param[in]   1 - enable the receiver. 0 - disable the receiver
  \return      error code
*/
int32_t csi_usart_control_rx(usart_handle_t handle, uint32_t enable)
{
    USART_NULL_PARAM_CHK(handle);
    return 0;
}

/**
  \brief       control the break.
  \param[in]   handle  usart handle to operate.
  \param[in]   1- Enable continuous Break transmission,0 - disable continuous Break transmission
  \return      error code
*/
int32_t csi_usart_control_break(usart_handle_t handle, uint32_t enable)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(DRV_ERROR_UNSUPPORTED);
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

    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    uint32_t timecount = 0;

    if (type == USART_FLUSH_WRITE) {
        while ((!(addr->LSR & DW_LSR_TEMT)))
        {
            timecount++;

            if (timecount >= UART_BUSY_TIMEOUT)
            {
                return ERR_USART(DRV_ERROR_TIMEOUT);
            }
        }
    } else if (type == USART_FLUSH_READ)
    {
        while (addr->LSR & 0x1) {
            timecount++;

            if (timecount >= UART_BUSY_TIMEOUT)
            {
                return ERR_USART(DRV_ERROR_TIMEOUT);
            }
        }
    } else
    {
        return ERR_USART(DRV_ERROR_PARAMETER);
    }

    return 0;
}

/**
  \brief       set interrupt mode.
  \param[in]   handle usart handle to operate.
  \param[in]   type \ref usart_intr_type_e.
  \param[in]   flag 0-OFF, 1-ON.
  \return      error code
*/
int32_t csi_usart_set_interrupt(usart_handle_t handle, usart_intr_type_e type, int32_t flag)
{
    USART_NULL_PARAM_CHK(handle);

    ck_usart_priv_t *usart_priv = handle;
    ck_usart_reg_t *addr = (ck_usart_reg_t *)(usart_priv->base);

    switch (type)
    {
        case USART_INTR_WRITE:
            if (flag == 0)
            {
                addr->IER &= ~IER_THRE_INT_ENABLE;
            } else if (flag == 1)
            {
                addr->IER |= IER_THRE_INT_ENABLE;
            } else
            {
                return ERR_USART(DRV_ERROR_PARAMETER);
            }

            break;

        case USART_INTR_READ:
            if (flag == 0)
            {
                addr->IER &= ~IER_RDA_INT_ENABLE;
            } else if (flag == 1)
            {
                addr->IER |= IER_RDA_INT_ENABLE;
            } else
            {
                return ERR_USART(DRV_ERROR_PARAMETER);
            }

            break;

        default:
            return ERR_USART(DRV_ERROR_PARAMETER);

    }

    return 0;
}

/**
  \brief       Get usart send data count.
  \param[in]   handle  usart handle to operate.
  \return      number of currently transmitted data bytes
*/
uint32_t csi_usart_get_tx_count(usart_handle_t handle)
{
    USART_NULL_PARAM_CHK(handle);

    ck_usart_priv_t *usart_priv = handle;

    if (usart_priv->tx_busy)
    {
        return usart_priv->tx_cnt;
    } else
    {
        return usart_priv->last_tx_num;
    }
}

/**
  \brief       Get usart receive data count.
  \param[in]   handle  usart handle to operate.
  \return      number of currently received data bytes
*/
uint32_t csi_usart_get_rx_count(usart_handle_t handle)
{
    USART_NULL_PARAM_CHK(handle);
    ck_usart_priv_t *usart_priv = handle;

    if (usart_priv->rx_busy)
    {
        return usart_priv->rx_cnt;
    } else
    {
        return usart_priv->last_rx_num;
    }
}

/**
  \brief       control usart power.
  \param[in]   handle  usart handle to operate.
  \param[in]   state   power state.\ref csi_power_stat_e.
  \return      error code
*/
int32_t csi_usart_power_control(usart_handle_t handle, csi_power_stat_e state)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(DRV_ERROR_UNSUPPORTED);
}

/**
  \brief       config usart flow control type.
  \param[in]   handle  usart handle to operate.
  \param[in]   flowctrl_type   flow control type.\ref usart_flowctrl_type_e.
  \return      error code
*/
int32_t csi_usart_config_flowctrl(usart_handle_t handle,
                                  usart_flowctrl_type_e flowctrl_type)
{
    USART_NULL_PARAM_CHK(handle);

    switch (flowctrl_type)
    {
        case USART_FLOWCTRL_CTS:
            return ERR_USART(DRV_ERROR_UNSUPPORTED);

        case USART_FLOWCTRL_RTS:
            return ERR_USART(DRV_ERROR_UNSUPPORTED);

        case USART_FLOWCTRL_CTS_RTS:
            return ERR_USART(DRV_ERROR_UNSUPPORTED);
            break;

        case USART_FLOWCTRL_NONE:
            return ERR_USART(DRV_ERROR_UNSUPPORTED);
            break;

        default:
            return ERR_USART(DRV_ERROR_UNSUPPORTED);
    }

    return 0;
}


/**
  \brief       config usart clock Polarity and Phase.
  \param[in]   handle  usart handle to operate.
  \param[in]   cpol    Clock Polarity.\ref usart_cpol_e.
  \param[in]   cpha    Clock Phase.\ref usart_cpha_e.
  \return      error code
*/
int32_t csi_usart_config_clock(usart_handle_t handle, usart_cpol_e cpol, usart_cpha_e cpha)
{
    USART_NULL_PARAM_CHK(handle);
    return ERR_USART(DRV_ERROR_UNSUPPORTED);
}

