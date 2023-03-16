/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-2-7        ChingI       First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_UUART)

#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"

#if defined(RT_SERIAL_USING_DMA)
    #include <drv_pdma.h>
#endif

/* Private define ---------------------------------------------------------------*/
enum
{
    UUART_START = -1,
#if defined(BSP_USING_UUART0)
    UUART0_IDX,
#endif
#if defined(BSP_USING_UUART1)
    UUART1_IDX,
#endif
    UUART_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_uuart
{
    rt_serial_t dev;
    char *name;
    UUART_T *uuart_base;
    uint32_t uuart_rst;
    IRQn_Type uuart_irq_n;
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
typedef struct nu_uuart *nu_uuart_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_uuart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t nu_uuart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int nu_uuart_send(struct rt_serial_device *serial, char c);
static int nu_uuart_receive(struct rt_serial_device *serial);
static void nu_uuart_isr(nu_uuart_t serial);

#if defined(RT_SERIAL_USING_DMA)
    static rt_ssize_t nu_uuart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);
    static void nu_pdma_uuart_rx_cb(void *pvOwner, uint32_t u32Events);
    static void nu_pdma_uuart_tx_cb(void *pvOwner, uint32_t u32Events);
#endif

/* Public functions ------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/

static const struct rt_uart_ops nu_uuart_ops =
{
    .configure = nu_uuart_configure,
    .control = nu_uuart_control,
    .putc = nu_uuart_send,
    .getc = nu_uuart_receive,
#if defined(RT_SERIAL_USING_DMA)
    .dma_transmit = nu_uuart_dma_transmit
#else
    .dma_transmit = RT_NULL
#endif
};

static const struct serial_configure nu_uuart_default_config =
        RT_SERIAL_CONFIG_DEFAULT;


static struct nu_uuart nu_uuart_arr [] =
{
#if defined(BSP_USING_UUART0)
    {
        .name = "uuart0",
        .uuart_base = UUART0,
        .uuart_rst = USCI0_RST,
        .uuart_irq_n = USCI0_IRQn,
#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UUART0_TX_DMA)
        .pdma_perp_tx = PDMA_USCI0_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UUART0_RX_DMA)
        .pdma_perp_rx = PDMA_USCI0_RX,
        .rx_write_offset = 0,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UUART1)
    {
        .name = "uuart1",
        .uuart_base = UUART1,
        .uuart_rst = USCI1_RST,
        .uuart_irq_n = USCI1_IRQn,
#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UUART1_TX_DMA)
        .pdma_perp_tx = PDMA_USCI1_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UUART1_RX_DMA)
        .pdma_perp_rx = PDMA_USCI1_RX,
        .rx_write_offset = 0,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

    {0}
}; /* uuart nu_uuart */

/* Interrupt Handle Function  ----------------------------------------------------*/
#if defined(BSP_USING_UUART0)
/* USCI0 interrupt entry */
void USCI0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_uuart_isr(&nu_uuart_arr[UUART0_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_UUART1)
/* USCI1 interrupt entry */
void USCI1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_uuart_isr(&nu_uuart_arr[UUART1_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif


/**
 * All UUART interrupt service routine
 */
static void nu_uuart_isr(nu_uuart_t serial)
{
    /* Get base address of uuart register */
    UUART_T *uuart_base = ((nu_uuart_t)serial)->uuart_base;

    /* Get interrupt event */
    uint32_t u32IntSts = uuart_base->PROTSTS;
    uint32_t u32FIFOSts = uuart_base->BUFSTS;

    if (u32IntSts & (UUART_PROTSTS_PARITYERR_Msk | UUART_PROTSTS_FRMERR_Msk | UUART_PROTSTS_BREAK_Msk))
    {
        uuart_base->PROTSTS |= (UUART_PROTSTS_PARITYERR_Msk | UUART_PROTSTS_FRMERR_Msk | UUART_PROTSTS_BREAK_Msk);
        return;
    }

    /* Handle RX event */
    if (u32IntSts & UUART_PROTSTS_RXENDIF_Msk)
    {
        rt_hw_serial_isr(&serial->dev, RT_SERIAL_EVENT_RX_IND);
    }
    uuart_base->PROTSTS = u32IntSts;
    uuart_base->BUFSTS = u32FIFOSts;
}

/**
 * Configure uuart port
 */
static rt_err_t nu_uuart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_err_t ret = RT_EOK;
    uint32_t uuart_word_len = 0;
    uint32_t uuart_stop_bit = 0;
    uint32_t uuart_parity = 0;

    /* Get base address of uuart register */
    UUART_T *uuart_base = ((nu_uuart_t)serial)->uuart_base;

    /* Check baud rate */
    RT_ASSERT(cfg->baud_rate != 0);

    /* Check word len */
    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        rt_kprintf("Unsupported data length");
        goto exit_nu_uuart_configure;

    case DATA_BITS_6:
        uuart_word_len = UUART_WORD_LEN_6;
        break;

    case DATA_BITS_7:
        uuart_word_len = UUART_WORD_LEN_7;
        break;

    case DATA_BITS_8:
        uuart_word_len = UUART_WORD_LEN_8;
        break;

    default:
        rt_kprintf("Unsupported data length");
        ret = -RT_EINVAL;
        goto exit_nu_uuart_configure;
    }

    /* Check stop bit */
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uuart_stop_bit = UUART_STOP_BIT_1;
        break;

    case STOP_BITS_2:
        uuart_stop_bit = UUART_STOP_BIT_2;
        break;

    default:
        rt_kprintf("Unsupported stop bit");
        ret = -RT_EINVAL;
        goto exit_nu_uuart_configure;
    }

    /* Check parity */
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uuart_parity = UUART_PARITY_NONE;
        break;

    case PARITY_ODD:
        uuart_parity = UUART_PARITY_ODD;
        break;

    case PARITY_EVEN:
        uuart_parity = UUART_PARITY_EVEN;
        break;

    default:
        rt_kprintf("Unsupported parity");
        ret = -RT_EINVAL;
        goto exit_nu_uuart_configure;
    }
    /* Reset this module */
    SYS_ResetModule(((nu_uuart_t)serial)->uuart_rst);

    /* Open UUart and set UUART baud rate */
    UUART_Open(uuart_base, cfg->baud_rate);

    /* Set line configuration. */
    UUART_SetLine_Config(uuart_base, 0, uuart_word_len, uuart_parity, uuart_stop_bit);

    /* Enable NVIC interrupt. */
    NVIC_EnableIRQ(((nu_uuart_t)serial)->uuart_irq_n);

exit_nu_uuart_configure:

    if (ret != RT_EOK)
        UUART_Close(uuart_base);

    return -(ret);
}

#if defined(RT_SERIAL_USING_DMA)
static rt_err_t nu_pdma_uuart_rx_config(struct rt_serial_device *serial, uint8_t *pu8Buf, int32_t i32TriggerLen)
{
    rt_err_t result = RT_EOK;

    /* Get base address of uuart register */
    UUART_T *uuart_base = ((nu_uuart_t)serial)->uuart_base;

    result = nu_pdma_callback_register(((nu_uuart_t)serial)->pdma_chanid_rx,
                                       nu_pdma_uuart_rx_cb,
                                       (void *)serial,
                                       NU_PDMA_EVENT_TRANSFER_DONE | NU_PDMA_EVENT_TIMEOUT);

    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uuart_rx_config;
    }

    result = nu_pdma_transfer(((nu_uuart_t)serial)->pdma_chanid_rx,
                              8,
                              (uint32_t)&uuart_base->RXDAT,
                              (uint32_t)pu8Buf,
                              i32TriggerLen,
                              1000);  //Idle-timeout, 1ms

    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uuart_rx_config;
    }

    //UUART PDMA reset
    UUART_PDMA_ENABLE(uuart_base, UUART_PDMACTL_PDMARST_Msk);

    /* Enable Receive Line interrupt & Start DMA RX transfer. */
    UUART_EnableInt(uuart_base, UUART_RLS_INT_MASK);
    UUART_PDMA_ENABLE(uuart_base, UUART_PDMACTL_RXPDMAEN_Msk | UUART_PDMACTL_PDMAEN_Msk);

exit_nu_pdma_uuart_rx_config:

    return result;
}

static void nu_pdma_uuart_rx_cb(void *pvOwner, uint32_t u32Events)
{
    rt_size_t recv_len = 0;
    rt_size_t transferred_rxbyte = 0;
    struct rt_serial_device *serial = (struct rt_serial_device *)pvOwner;
    nu_uuart_t puuart = (nu_uuart_t)serial;
    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uuart register */
    UUART_T *uuart_base = puuart->uuart_base;

    transferred_rxbyte = nu_pdma_transferred_byte_get(puuart->pdma_chanid_rx, puuart->rxdma_trigger_len);

    if (u32Events & (NU_PDMA_EVENT_TRANSFER_DONE | NU_PDMA_EVENT_TIMEOUT))
    {
        if (u32Events & NU_PDMA_EVENT_TRANSFER_DONE)
        {
            if (serial->config.bufsz != 0)
            {
                struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

                nu_pdma_uuart_rx_config(serial, &rx_fifo->buffer[0], puuart->rxdma_trigger_len);     // Config & trigger next
            }

            transferred_rxbyte = puuart->rxdma_trigger_len;
        }
        else if ((u32Events & NU_PDMA_EVENT_TIMEOUT) && !UUART_GET_RX_EMPTY(uuart_base))
        {
            return;
        }

        recv_len = transferred_rxbyte - puuart->rx_write_offset;

        puuart->rx_write_offset = transferred_rxbyte % puuart->rxdma_trigger_len;

    }

    if ((serial->config.bufsz == 0) && (u32Events & NU_PDMA_EVENT_TRANSFER_DONE))
    {
        recv_len = puuart->rxdma_trigger_len;
    }

    if (recv_len)
    {
        rt_hw_serial_isr(&puuart->dev, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
}

static rt_err_t nu_pdma_uuart_tx_config(struct rt_serial_device *serial)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(serial != RT_NULL);

    result = nu_pdma_callback_register(((nu_uuart_t)serial)->pdma_chanid_tx,
                                       nu_pdma_uuart_tx_cb,
                                       (void *)serial,
                                       NU_PDMA_EVENT_TRANSFER_DONE);

    return result;
}

static void nu_pdma_uuart_tx_cb(void *pvOwner, uint32_t u32Events)
{
    nu_uuart_t puuart = (nu_uuart_t)pvOwner;

    RT_ASSERT(puuart != RT_NULL);

    // Stop DMA TX transfer
    UUART_PDMA_DISABLE(puuart->uuart_base, UUART_PDMACTL_TXPDMAEN_Msk);

    if (u32Events & NU_PDMA_EVENT_TRANSFER_DONE)
    {
        rt_hw_serial_isr(&puuart->dev, RT_SERIAL_EVENT_TX_DMADONE);
    }
}

/**
 * UUart DMA transfer
 */
static rt_ssize_t nu_uuart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    /* Get base address of uuart register */
    UUART_T *uuart_base = ((nu_uuart_t)serial)->uuart_base;
    if (direction == RT_SERIAL_DMA_TX)
    {
        result = nu_pdma_transfer(((nu_uuart_t)serial)->pdma_chanid_tx,
                                  8,
                                  (uint32_t)buf,
                                  (uint32_t)&uuart_base->TXDAT,
                                  size,
                                  0);  // wait-forever
        // Start DMA TX transfer
        UUART_PDMA_ENABLE(uuart_base, UUART_PDMACTL_TXPDMAEN_Msk | UUART_PDMACTL_PDMAEN_Msk);
    }
    else if (direction == RT_SERIAL_DMA_RX)
    {
        // If config.bufsz = 0, serial will trigger once.
        ((nu_uuart_t)serial)->rxdma_trigger_len = size;
        ((nu_uuart_t)serial)->rx_write_offset = 0;
        result = nu_pdma_uuart_rx_config(serial, buf, size);
    }
    else
    {
        result = RT_ERROR;
    }

    return result;
}

static int nu_hw_uuart_dma_allocate(nu_uuart_t puuart)
{
    RT_ASSERT(puuart != RT_NULL);

    /* Allocate UUART_TX nu_dma channel */
    if (puuart->pdma_perp_tx != NU_PDMA_UNUSED)
    {
        puuart->pdma_chanid_tx = nu_pdma_channel_allocate(puuart->pdma_perp_tx);
        if (puuart->pdma_chanid_tx >= 0)
        {
            puuart->dma_flag |= RT_DEVICE_FLAG_DMA_TX;
        }
    }

    /* Allocate UUART_RX nu_dma channel */
    if (puuart->pdma_perp_rx != NU_PDMA_UNUSED)
    {
        puuart->pdma_chanid_rx = nu_pdma_channel_allocate(puuart->pdma_perp_rx);
        if (puuart->pdma_chanid_rx >= 0)
        {
            puuart->dma_flag |= RT_DEVICE_FLAG_DMA_RX;
        }
    }

    return RT_EOK;
}
#endif

/**
 * UUart interrupt control
 */
static rt_err_t nu_uuart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t flag = 0;
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uuart register */
    UUART_T *uuart_base = ((nu_uuart_t)serial)->uuart_base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Disable INT-RX */
        {
            flag = UUART_RXEND_INT_MASK;
            UUART_DisableInt(uuart_base, flag);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) /* Disable DMA-RX */
        {
            /* Disable Receive Line interrupt & Stop DMA RX transfer. */
            flag = UUART_RLS_INT_MASK;
            nu_pdma_channel_terminate(((nu_uuart_t)serial)->pdma_chanid_rx);
            UUART_PDMA_DISABLE(uuart_base, UUART_PDMACTL_RXPDMAEN_Msk);
            UUART_DisableInt(uuart_base, flag);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Enable INT-RX */
        {
            flag = UUART_RXEND_INT_MASK;
            UUART_EnableInt(uuart_base, flag);
        }
        break;

#if defined(RT_SERIAL_USING_DMA)
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) /* Configure and trigger DMA-RX */
        {
            struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
            ((nu_uuart_t)serial)->rxdma_trigger_len = serial->config.bufsz;
            ((nu_uuart_t)serial)->rx_write_offset = 0;
            result = nu_pdma_uuart_rx_config(serial, &rx_fifo->buffer[0], ((nu_uuart_t)serial)->rxdma_trigger_len);  // Config & trigger
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX) /* Configure DMA-TX */
        {
            result = nu_pdma_uuart_tx_config(serial);
        }
        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:
        /* Disable NVIC interrupt. */
        NVIC_DisableIRQ(((nu_uuart_t)serial)->uuart_irq_n);

#if defined(RT_SERIAL_USING_DMA)
        nu_pdma_channel_terminate(((nu_uuart_t)serial)->pdma_chanid_tx);
        nu_pdma_channel_terminate(((nu_uuart_t)serial)->pdma_chanid_rx);
#endif

        /* Reset this module */
        SYS_ResetModule(((nu_uuart_t)serial)->uuart_rst);

        /* Close UUART port */
        UUART_Close(uuart_base);

        break;
    default:
        result = -RT_EINVAL;
        break;
    }
    return result;
}

/**
 * UUart put char
 */
static int nu_uuart_send(struct rt_serial_device *serial, char c)
{
    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uuart register */
    UUART_T *uuart_base = ((nu_uuart_t)serial)->uuart_base;

    /* Waiting if TX-FIFO is full. */
    while (UUART_IS_TX_FULL(uuart_base)) {};

    /* Put char into TX-FIFO */
    UUART_WRITE(uuart_base, c);

    return 1;
}

/**
 * UUart get char
 */
static int nu_uuart_receive(struct rt_serial_device *serial)
{
    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uuart register */
    UUART_T *uuart_base = ((nu_uuart_t)serial)->uuart_base;

    /* Return failure if RX-FIFO is empty. */
    if (UUART_GET_RX_EMPTY(uuart_base) != 0)
    {
        return -1;
    }

    /* Get char from RX-FIFO */
    return UUART_READ(uuart_base);
}

/**
 * Hardware UUART Initialization
 */
static int rt_hw_uuart_init(void)
{
    int i;
    rt_uint32_t flag;
    rt_err_t ret = RT_EOK;

    for (i = (UUART_START + 1); i < UUART_CNT; i++)
    {
        flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

        nu_uuart_arr[i].dev.ops    = &nu_uuart_ops;
        nu_uuart_arr[i].dev.config = nu_uuart_default_config;

#if defined(RT_SERIAL_USING_DMA)
        nu_uuart_arr[i].dma_flag = 0;
        nu_hw_uuart_dma_allocate(&nu_uuart_arr[i]);
        flag |= nu_uuart_arr[i].dma_flag;
#endif

        ret = rt_hw_serial_register(&nu_uuart_arr[i].dev, nu_uuart_arr[i].name, flag, NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return (int)ret;
}

INIT_DEVICE_EXPORT(rt_hw_uuart_init);

#endif //#if defined(BSP_USING_UUART)
