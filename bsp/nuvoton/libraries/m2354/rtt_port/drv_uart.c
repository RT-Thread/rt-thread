/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-6-7        Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_UART)

#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"
#include <drv_uart.h>

#if defined(RT_SERIAL_USING_DMA)
    #include <drv_pdma.h>
#endif

/* Private define ---------------------------------------------------------------*/
enum
{
    UART_START = -1,
#if defined(BSP_USING_UART0)
    UART0_IDX,
#endif
#if defined(BSP_USING_UART1)
    UART1_IDX,
#endif
#if defined(BSP_USING_UART2)
    UART2_IDX,
#endif
#if defined(BSP_USING_UART3)
    UART3_IDX,
#endif
#if defined(BSP_USING_UART4)
    UART4_IDX,
#endif
#if defined(BSP_USING_UART5)
    UART5_IDX,
#endif
    UART_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_uart
{
    rt_serial_t dev;
    char *name;
    UART_T *uart_base;
    uint32_t uart_rst;
    IRQn_Type uart_irq_n;

#if defined(RT_SERIAL_USING_DMA)
    uint32_t dma_flag;
    int16_t pdma_perp_tx;
    int8_t  pdma_chanid_tx;

    int16_t pdma_perp_rx;
    int8_t  pdma_chanid_rx;
    int32_t rx_write_offset;
    int32_t rxdma_trigger_len;
#endif

};
typedef struct nu_uart *nu_uart_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t nu_uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int nu_uart_send(struct rt_serial_device *serial, char c);
static int nu_uart_receive(struct rt_serial_device *serial);
static void nu_uart_isr(nu_uart_t serial);

#if defined(RT_SERIAL_USING_DMA)
    static rt_ssize_t nu_uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);
    static void nu_pdma_uart_rx_cb(void *pvOwner, uint32_t u32Events);
    static void nu_pdma_uart_tx_cb(void *pvOwner, uint32_t u32Events);
#endif

/* Public functions ------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/

static const struct rt_uart_ops nu_uart_ops =
{
    .configure = nu_uart_configure,
    .control = nu_uart_control,
    .putc = nu_uart_send,
    .getc = nu_uart_receive,
#if defined(RT_SERIAL_USING_DMA)
    .dma_transmit = nu_uart_dma_transmit
#else
    .dma_transmit = RT_NULL
#endif
};

static const struct serial_configure nu_uart_default_config =
        RT_SERIAL_CONFIG_DEFAULT;

static struct nu_uart nu_uart_arr [] =
{
#if defined(BSP_USING_UART0)
    {
        .name = "uart0",
        .uart_base = UART0,
        .uart_rst = UART0_RST,
        .uart_irq_n = UART0_IRQn,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART0_TX_DMA)
        .pdma_perp_tx = PDMA_UART0_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART0_RX_DMA)
        .pdma_perp_rx = PDMA_UART0_RX,
        .rx_write_offset = 0,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART1)
    {
        .name = "uart1",
        .uart_base = UART1,
        .uart_rst = UART1_RST,
        .uart_irq_n = UART1_IRQn,
#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART1_TX_DMA)
        .pdma_perp_tx = PDMA_UART1_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART1_RX_DMA)
        .pdma_perp_rx = PDMA_UART1_RX,
        .rx_write_offset = 0,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART2)
    {
        .name = "uart2",
        .uart_base = UART2,
        .uart_rst = UART2_RST,
        .uart_irq_n = UART2_IRQn,
#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART2_TX_DMA)
        .pdma_perp_tx = PDMA_UART2_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART2_RX_DMA)
        .pdma_perp_rx = PDMA_UART2_RX,
        .rx_write_offset = 0,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART3)
    {
        .name = "uart3",
        .uart_base = UART3,
        .uart_rst = UART3_RST,
        .uart_irq_n = UART3_IRQn,
#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART3_TX_DMA)
        .pdma_perp_tx = PDMA_UART3_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART3_RX_DMA)
        .pdma_perp_rx = PDMA_UART3_RX,
        .rx_write_offset = 0,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART4)
    {
        .name = "uart4",
        .uart_base = UART4,
        .uart_rst = UART4_RST,
        .uart_irq_n = UART4_IRQn,
#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART4_TX_DMA)
        .pdma_perp_tx = PDMA_UART4_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART4_RX_DMA)
        .pdma_perp_rx = PDMA_UART4_RX,
        .rx_write_offset = 0,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART5)
    {
        .name = "uart5",
        .uart_base = UART5,
        .uart_rst = UART5_RST,
        .uart_irq_n = UART5_IRQn,
#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART5_TX_DMA)
        .pdma_perp_tx = PDMA_UART5_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART5_RX_DMA)
        .pdma_perp_rx = PDMA_UART5_RX,
        .rx_write_offset = 0,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif
}; /* uart nu_uart */

/* Interrupt Handle Function  ----------------------------------------------------*/
#if defined(BSP_USING_UART0)
/* UART0 interrupt entry */
void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_uart_isr(&nu_uart_arr[UART0_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_UART1)
/* UART1 interrupt entry */
void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_uart_isr(&nu_uart_arr[UART1_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_UART2)
/* UART2 interrupt entry */
void UART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_uart_isr(&nu_uart_arr[UART2_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_UART3)
/* UART3 interrupt service routine */
void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_uart_isr(&nu_uart_arr[UART3_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_UART4)
/* UART4 interrupt entry */
void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_uart_isr(&nu_uart_arr[UART4_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_UART5)
/* UART5 interrupt entry */
void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_uart_isr(&nu_uart_arr[UART5_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

/**
 * All UART interrupt service routine
 */
static void nu_uart_isr(nu_uart_t serial)
{
    /* Get base address of uart register */
    UART_T *uart_base = serial->uart_base;

    /* Get interrupt event */
    uint32_t u32IntSts = uart_base->INTSTS;
    uint32_t u32FIFOSts = uart_base->FIFOSTS;

#if defined(RT_SERIAL_USING_DMA)
    if (u32IntSts & UART_INTSTS_HWRLSIF_Msk)
    {
        /* Drain RX FIFO to remove remain FEF frames in FIFO. */
        uart_base->FIFO |= UART_FIFO_RXRST_Msk;
        uart_base->FIFOSTS |= (UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk);
        return;
    }
#endif

    /* Handle RX event */
    if (u32IntSts & (UART_INTSTS_RDAINT_Msk | UART_INTSTS_RXTOINT_Msk))
    {
        rt_hw_serial_isr(&serial->dev, RT_SERIAL_EVENT_RX_IND);
    }
    uart_base->INTSTS = u32IntSts;
    uart_base->FIFOSTS = u32FIFOSts;
}

/**
 * Configure uart port
 */
static rt_err_t nu_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_err_t ret = RT_EOK;
    uint32_t uart_word_len = 0;
    uint32_t uart_stop_bit = 0;
    uint32_t uart_parity = 0;

    RT_ASSERT(serial);
    RT_ASSERT(cfg);

    /* Check baudrate */
    RT_ASSERT(cfg->baud_rate != 0);

    /* Get base address of uart register */
    UART_T *uart_base = ((nu_uart_t)serial)->uart_base;

    /* Check word len */
    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        uart_word_len = UART_WORD_LEN_5;
        break;

    case DATA_BITS_6:
        uart_word_len = UART_WORD_LEN_6;
        break;

    case DATA_BITS_7:
        uart_word_len = UART_WORD_LEN_7;
        break;

    case DATA_BITS_8:
        uart_word_len = UART_WORD_LEN_8;
        break;

    default:
        rt_kprintf("Unsupported data length\n");
        ret = -RT_EINVAL;
        goto exit_nu_uart_configure;
    }

    /* Check stop bit */
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart_stop_bit = UART_STOP_BIT_1;
        break;

    case STOP_BITS_2:
        uart_stop_bit = UART_STOP_BIT_2;
        break;

    default:
        rt_kprintf("Unsupported stop bit\n");
        ret = -RT_EINVAL;
        goto exit_nu_uart_configure;
    }

    /* Check parity */
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart_parity = UART_PARITY_NONE;
        break;

    case PARITY_ODD:
        uart_parity = UART_PARITY_ODD;
        break;

    case PARITY_EVEN:
        uart_parity = UART_PARITY_EVEN;
        break;

    default:
        rt_kprintf("Unsupported parity\n");
        ret = -RT_EINVAL;
        goto exit_nu_uart_configure;
    }

    /* Reset this module */
    SYS_ResetModule(((nu_uart_t)serial)->uart_rst);

    /* Open Uart and set UART Baudrate */
    UART_Open(uart_base, cfg->baud_rate);

    /* Set line configuration. */
    UART_SetLineConfig(uart_base, 0, uart_word_len, uart_parity, uart_stop_bit);

    /* Enable NVIC interrupt. */
    NVIC_EnableIRQ(((nu_uart_t)serial)->uart_irq_n);

exit_nu_uart_configure:

    if (ret != RT_EOK)
        UART_Close(uart_base);

    return -(ret);
}

#if defined(RT_SERIAL_USING_DMA)
static rt_err_t nu_pdma_uart_rx_config(struct rt_serial_device *serial, uint8_t *pu8Buf, int32_t i32TriggerLen)
{
    rt_err_t result = RT_EOK;

    /* Get base address of uart register */
    UART_T *uart_base = ((nu_uart_t)serial)->uart_base;

    result = nu_pdma_callback_register(((nu_uart_t)serial)->pdma_chanid_rx,
                                       nu_pdma_uart_rx_cb,
                                       (void *)serial,
                                       NU_PDMA_EVENT_TRANSFER_DONE | NU_PDMA_EVENT_TIMEOUT);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uart_rx_config;
    }

    result = nu_pdma_transfer(((nu_uart_t)serial)->pdma_chanid_rx,
                              8,
                              (uint32_t)uart_base,
                              (uint32_t)pu8Buf,
                              i32TriggerLen,
                              1000);  //Idle-timeout, 1ms
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uart_rx_config;
    }

    /* Enable Receive Line interrupt & Start DMA RX transfer. */
    UART_ENABLE_INT(uart_base, UART_INTEN_RLSIEN_Msk);
    UART_PDMA_ENABLE(uart_base, UART_INTEN_RXPDMAEN_Msk);

exit_nu_pdma_uart_rx_config:

    return result;
}

static void nu_pdma_uart_rx_cb(void *pvOwner, uint32_t u32Events)
{
    rt_size_t recv_len = 0;
    rt_size_t transferred_rxbyte = 0;
    struct rt_serial_device *serial = (struct rt_serial_device *)pvOwner;
    nu_uart_t puart = (nu_uart_t)serial;
    RT_ASSERT(serial);

    /* Get base address of uart register */
    UART_T *uart_base = puart->uart_base;

    transferred_rxbyte = nu_pdma_transferred_byte_get(puart->pdma_chanid_rx, puart->rxdma_trigger_len);

    if (u32Events & (NU_PDMA_EVENT_TRANSFER_DONE | NU_PDMA_EVENT_TIMEOUT))
    {
        if (u32Events & NU_PDMA_EVENT_TRANSFER_DONE)
        {
            if (serial->config.bufsz != 0)
            {
                struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

                nu_pdma_uart_rx_config(serial, &rx_fifo->buffer[0], puart->rxdma_trigger_len);     // Config & trigger next
            }
            else
            {
                UART_DISABLE_INT(uart_base, UART_INTEN_RLSIEN_Msk);
                UART_PDMA_DISABLE(uart_base, UART_INTEN_RXPDMAEN_Msk);
            }
            transferred_rxbyte = puart->rxdma_trigger_len;
        }
        else if ((u32Events & NU_PDMA_EVENT_TIMEOUT) && !UART_GET_RX_EMPTY(uart_base))
        {
            return;
        }

        recv_len = transferred_rxbyte - puart->rx_write_offset;

        if (recv_len > 0)
        {
            puart->rx_write_offset = transferred_rxbyte % puart->rxdma_trigger_len;
        }
    }

    if ((serial->config.bufsz == 0) && (u32Events & NU_PDMA_EVENT_TRANSFER_DONE))
    {
        recv_len = puart->rxdma_trigger_len;
    }

    if (recv_len > 0)
    {
        rt_hw_serial_isr(&puart->dev, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
}

static rt_err_t nu_pdma_uart_tx_config(struct rt_serial_device *serial)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(serial != RT_NULL);

    result = nu_pdma_callback_register(((nu_uart_t)serial)->pdma_chanid_tx,
                                       nu_pdma_uart_tx_cb,
                                       (void *)serial,
                                       NU_PDMA_EVENT_TRANSFER_DONE);

    return result;
}

static void nu_pdma_uart_tx_cb(void *pvOwner, uint32_t u32Events)
{
    nu_uart_t puart = (nu_uart_t)pvOwner;

    RT_ASSERT(puart);

    UART_PDMA_DISABLE(puart->uart_base, UART_INTEN_TXPDMAEN_Msk);// Stop DMA TX transfer

    if (u32Events & NU_PDMA_EVENT_TRANSFER_DONE)
    {
        rt_hw_serial_isr(&puart->dev, RT_SERIAL_EVENT_TX_DMADONE);
    }
}

/**
 * Uart DMA transfer
 */
static rt_ssize_t nu_uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    rt_err_t result = RT_EOK;
    nu_uart_t psNuUart = (nu_uart_t)serial;

    RT_ASSERT(serial);
    RT_ASSERT(buf);

    /* Get base address of uart register */
    UART_T *uart_base = psNuUart->uart_base;
    if (direction == RT_SERIAL_DMA_TX)
    {
        result = nu_pdma_transfer(psNuUart->pdma_chanid_tx,
                                  8,
                                  (uint32_t)buf,
                                  (uint32_t)uart_base,
                                  size,
                                  0);  // wait-forever
        // Start DMA TX transfer
        UART_PDMA_ENABLE(uart_base, UART_INTEN_TXPDMAEN_Msk);
    }
    else if (direction == RT_SERIAL_DMA_RX)
    {
        UART_DISABLE_INT(uart_base, UART_INTEN_RLSIEN_Msk);
        UART_PDMA_DISABLE(uart_base, UART_INTEN_RXPDMAEN_Msk);
        // If config.bufsz = 0, serial will trigger once.
        psNuUart->rxdma_trigger_len = size;
        psNuUart->rx_write_offset = 0;
        result = nu_pdma_uart_rx_config(serial, buf, size);
    }
    else
    {
        result = RT_ERROR;
    }

    return result;
}

static int nu_hw_uart_dma_allocate(nu_uart_t pusrt)
{
    RT_ASSERT(pusrt);

    /* Allocate UART_TX nu_dma channel */
    if (pusrt->pdma_perp_tx != NU_PDMA_UNUSED)
    {
        pusrt->pdma_chanid_tx = nu_pdma_channel_allocate(pusrt->pdma_perp_tx);
        if (pusrt->pdma_chanid_tx >= 0)
        {
            pusrt->dma_flag |= RT_DEVICE_FLAG_DMA_TX;
        }
    }

    /* Allocate UART_RX nu_dma channel */
    if (pusrt->pdma_perp_rx != NU_PDMA_UNUSED)
    {
        pusrt->pdma_chanid_rx = nu_pdma_channel_allocate(pusrt->pdma_perp_rx);
        if (pusrt->pdma_chanid_rx >= 0)
        {
            pusrt->dma_flag |= RT_DEVICE_FLAG_DMA_RX;
        }
    }

    return RT_EOK;
}
#endif

/**
 * Uart interrupt control
 */
static rt_err_t nu_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;
    rt_err_t result = RT_EOK;
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial);

    /* Get base address of uart register */
    UART_T *uart_base = psNuUart->uart_base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Disable INT-RX */
        {
            UART_DISABLE_INT(uart_base, UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_TOCNTEN_Msk);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) /* Disable DMA-RX */
        {
            /* Disable Receive Line interrupt & Stop DMA RX transfer. */
#if defined(RT_SERIAL_USING_DMA)
            if (psNuUart->dma_flag & RT_DEVICE_FLAG_DMA_RX)
            {
                nu_pdma_channel_terminate(psNuUart->pdma_chanid_rx);
            }
            UART_DISABLE_INT(uart_base, UART_INTEN_RLSIEN_Msk | UART_INTEN_RXPDMAEN_Msk);
#endif
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Enable INT-RX */
        {
            UART_ENABLE_INT(uart_base, UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_TOCNTEN_Msk);
        }
        break;

#if defined(RT_SERIAL_USING_DMA)
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) /* Configure and trigger DMA-RX */
        {
            struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
            psNuUart->rxdma_trigger_len = serial->config.bufsz;
            psNuUart->rx_write_offset = 0;

            result = nu_pdma_uart_rx_config(serial, &rx_fifo->buffer[0], psNuUart->rxdma_trigger_len);  // Config & trigger
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX) /* Configure DMA-TX */
        {
            result = nu_pdma_uart_tx_config(serial);
        }
        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:
        /* Disable NVIC interrupt. */
        NVIC_DisableIRQ(psNuUart->uart_irq_n);

#if defined(RT_SERIAL_USING_DMA)
        UART_DISABLE_INT(uart_base, UART_INTEN_RLSIEN_Msk | UART_INTEN_RXPDMAEN_Msk);
        UART_DISABLE_INT(uart_base, UART_INTEN_TXPDMAEN_Msk);

        if (psNuUart->dma_flag != 0)
        {
            nu_pdma_channel_terminate(psNuUart->pdma_chanid_tx);
            nu_pdma_channel_terminate(psNuUart->pdma_chanid_rx);
        }
#endif

        /* Close UART port */
        UART_Close(uart_base);

        break;

    default:
        result = -RT_EINVAL;
        break;

    }
    return result;
}

/**
 * Uart put char
 */
static int nu_uart_send(struct rt_serial_device *serial, char c)
{
    RT_ASSERT(serial);

    /* Get base address of uart register */
    UART_T *uart_base = ((nu_uart_t)serial)->uart_base;

    /* Waiting if TX-FIFO is full. */
    while (UART_IS_TX_FULL(uart_base));

    /* Put char into TX-FIFO */
    UART_WRITE(uart_base, c);

    return 1;
}

/**
 * Uart get char
 */
static int nu_uart_receive(struct rt_serial_device *serial)
{
    RT_ASSERT(serial);

    /* Get base address of uart register */
    UART_T *uart_base = ((nu_uart_t)serial)->uart_base;

    /* Return failure if RX-FIFO is empty. */
    if (UART_GET_RX_EMPTY(uart_base))
    {
        return -1;
    }

    /* Get char from RX-FIFO */
    return UART_READ(uart_base);
}

/**
 * Hardware UART Initialization
 */
rt_err_t rt_hw_uart_init(void)
{
    int i;
    rt_uint32_t flag;
    rt_err_t ret = RT_EOK;

    for (i = (UART_START + 1); i < UART_CNT; i++)
    {
        flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

        nu_uart_arr[i].dev.ops    = &nu_uart_ops;
        nu_uart_arr[i].dev.config = nu_uart_default_config;

#if defined(RT_SERIAL_USING_DMA)
        nu_uart_arr[i].dma_flag = 0;
        nu_hw_uart_dma_allocate(&nu_uart_arr[i]);
        flag |= nu_uart_arr[i].dma_flag;
#endif

        ret = rt_hw_serial_register(&nu_uart_arr[i].dev, nu_uart_arr[i].name, flag, NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return ret;
}

#endif //#if defined(BSP_USING_UART)
