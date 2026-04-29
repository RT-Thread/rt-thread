/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_UART)

#include "NuMicro.h"
#include "drv_pdma.h"
#include "drv_uart.h"
#include "rtdbg.h"
#include "rtdevice.h"
#include "rthw.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.uart"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL      LOG_LVL_INFO
#define DBG_COLOR
#define UART_BUS_IDLE_TIMEOUT_ENABLE(uart)      (UART_ENABLE_INT(uart, UART_INTEN_TOCNTEN_Msk))
#define UART_BUS_IDLE_TIMEOUT_DISABLE(uart)     (UART_DISABLE_INT(uart, UART_INTEN_TOCNTEN_Msk))
#define CONFIG_UART_USE_IDLE_TIMER

#if defined(CONFIG_UART_USE_IDLE_TIMER)
    #define CONFIG_PDMA_USE_IT               (NU_PDMA_EVENT_TRANSFER_DONE)
    #define CONFIG_UART_USE_RXDMA_IT         (UART_INTEN_RLSIEN_Msk | UART_INTEN_RXPDMAEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_TOCNTEN_Msk)
    #define CONFIG_UART_IDLE_TIMEOUT_VALUE   (50)
    #define CONFIG_PDMA_IDLE_TIMEOUT_VALUE   (0)
#else
    #define CONFIG_PDMA_USE_IT               (NU_PDMA_EVENT_TRANSFER_DONE | NU_PDMA_EVENT_TIMEOUT)
    #define CONFIG_UART_USE_RXDMA_IT         (UART_INTEN_RLSIEN_Msk | UART_INTEN_RXPDMAEN_Msk)
    #define CONFIG_PDMA_IDLE_TIMEOUT_VALUE   (1000000 * 10 * (1 + psNuUart->dev.config.data_bits + (psNuUart->dev.config.stop_bits + 1)) / psNuUart->dev.config.baud_rate)
#endif
#define CONFIG_UART_USE_TXDMA_IT             (UART_INTEN_TXPDMAEN_Msk)
#define MAKE_UART_NAME(x)         #x
#define MAKE_PDMA_UART_TX(x)      PDMA_UART##x##_TX
#define MAKE_PDMA_UART_RX(x)      PDMA_UART##x##_RX

#if defined(RT_SERIAL_USING_DMA)
#define MAKE_UART_INSTANCE(x, t, r) \
    { \
        .name = MAKE_UART_NAME(uart##x), \
        .base = UART##x, \
        .rst  = UART##x##_RST, \
        .irqn = UART##x##_IRQn, \
        .pdma_perp_tx = t, \
        .pdma_perp_rx = r, \
    },
#else
#define MAKE_UART_INSTANCE(x, t, r) \
    { \
        .name = MAKE_UART_NAME(uart##x), \
        .base = UART##x, \
        .rst  = UART##x##_RST, \
        .irqn = UART##x##_IRQn, \
    },
#endif

/* Types / Structures ---------------------------------------------------------*/
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
    UART_CNT
};

struct nu_rxbuf_ctx
{
    uint8_t *pu8RxBuf;
    uint32_t bufsize;
    uint32_t put_index;
    uint32_t reserved;
};
typedef struct nu_rxbuf_ctx *nu_rxbuf_ctx_t;
struct nu_uart
{
    rt_serial_t dev;
    char *name;
    UART_T *base;
    uint32_t rst;
    IRQn_Type irqn;
#if defined(RT_SERIAL_USING_DMA)
    uint32_t dma_flag;
    uint32_t pdma_perp_tx;
    uint32_t pdma_chanid_tx;

    uint32_t pdma_perp_rx;
    uint32_t pdma_chanid_rx;

    nu_pdma_desc_t pdma_rx_desc;
    struct nu_rxbuf_ctx dmabuf;
#endif

};
typedef struct nu_uart *nu_uart_t;

/* Static Function Prototypes ------------------------------------------------*/
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

/* Static Variables ----------------------------------------------------------*/
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
    MAKE_UART_INSTANCE(0,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART0_TX_DMA)
                       MAKE_PDMA_UART_TX(0),
#else
                       NU_PDMA_UNUSED,
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART0_RX_DMA)
                       MAKE_PDMA_UART_RX(0)
#else
                       NU_PDMA_UNUSED
#endif
                      )
#endif

#if defined(BSP_USING_UART1)
    MAKE_UART_INSTANCE(1,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART1_TX_DMA)
                       MAKE_PDMA_UART_TX(1),
#else
                       NU_PDMA_UNUSED,
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART1_RX_DMA)
                       MAKE_PDMA_UART_RX(1)
#else
                       NU_PDMA_UNUSED
#endif
                      )
#endif

#if defined(BSP_USING_UART2)
    MAKE_UART_INSTANCE(2,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART2_TX_DMA)
                       MAKE_PDMA_UART_TX(2),
#else
                       NU_PDMA_UNUSED,
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART2_RX_DMA)
                       MAKE_PDMA_UART_RX(2)
#else
                       NU_PDMA_UNUSED
#endif
                      )
#endif

#if defined(BSP_USING_UART3)
    MAKE_UART_INSTANCE(3,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART3_TX_DMA)
                       MAKE_PDMA_UART_TX(3),
#else
                       NU_PDMA_UNUSED,
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART3_RX_DMA)
                       MAKE_PDMA_UART_RX(3)
#else
                       NU_PDMA_UNUSED
#endif
                      )
#endif

#if defined(BSP_USING_UART4)
    MAKE_UART_INSTANCE(4,
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART4_TX_DMA)
                       MAKE_PDMA_UART_TX(4),
#else
                       NU_PDMA_UNUSED,
#endif
#if defined(RT_SERIAL_USING_DMA) && defined(BSP_USING_UART4_RX_DMA)
                       MAKE_PDMA_UART_RX(4)
#else
                       NU_PDMA_UNUSED
#endif
                      )
#endif
    {
        0
    }
};

/* Functions Implementation --------------------------------------------------*/
#define MAKE_UART_ISR(x) \
    void UART##x##_IRQHandler(void) \
    { \
       rt_interrupt_enter(); \
       nu_uart_isr(&nu_uart_arr[UART##x##_IDX]); \
       rt_interrupt_leave(); \
    }
#if defined(BSP_USING_UART0)
    MAKE_UART_ISR(0);
#endif

#if defined(BSP_USING_UART1)
    MAKE_UART_ISR(1);
#endif

#if defined(BSP_USING_UART2)
    MAKE_UART_ISR(2);
#endif

#if defined(BSP_USING_UART3)
    MAKE_UART_ISR(3);
#endif

#if defined(BSP_USING_UART4)
    MAKE_UART_ISR(4);
#endif

/**
 * All UART interrupt service routine
 */
static void nu_uart_isr(nu_uart_t psNuUart)
{
    /* Get base address of uart register */
    UART_T *base = psNuUart->base;

    /* Get interrupt event */
    uint32_t u32IntSts = base->INTSTS;
    uint32_t u32FIFOSts = base->FIFOSTS;
#if defined(RT_SERIAL_USING_DMA)
    if (u32IntSts & UART_INTSTS_HWRLSIF_Msk)
    {
        /* Drain RX FIFO to remove remain FEF frames in FIFO. */
        base->FIFO |= UART_FIFO_RXRST_Msk;
        base->FIFOSTS |= (UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk);
        return;
    }
#if defined(CONFIG_UART_USE_IDLE_TIMER)
    if (u32IntSts & UART_INTSTS_HWTOIF_Msk)
    {
        /* In UART RX PDMA mode, bus idle timeout occurred. */
        nu_pdma_uart_rx_cb((void *)psNuUart, NU_PDMA_EVENT_TIMEOUT);

        /* clear int flag */
        base->INTSTS = u32IntSts;
        return;
    }
#endif

#endif

    /* Handle RX event */
    if (u32IntSts & (UART_INTSTS_RDAINT_Msk | UART_INTSTS_RXTOINT_Msk))
    {
        rt_hw_serial_isr(&psNuUart->dev, RT_SERIAL_EVENT_RX_IND);
    }

    base->INTSTS = u32IntSts;
    base->FIFOSTS = u32FIFOSts;
}

/**
 * Set RS-485 AUD mode
 */
void nu_uart_set_rs485aud(struct rt_serial_device *serial, rt_bool_t bRTSActiveLowLevel)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;
    UART_T *base;
    RT_ASSERT(serial);

    /* Get base address of uart register */
    base = ((nu_uart_t)serial)->base;

    /* Set RTS as RS-485 phy direction controlling ping. */
    UART_SelectRS485Mode(base, UART_ALTCTL_RS485AUD_Msk, 0);

    if (bRTSActiveLowLevel)
    {
        /* Set direction pin as active-low. */
        base->MODEM |= UART_MODEM_RTSACTLV_Msk;
    }
    else
    {
        /* Set direction pin as active-high. */
        base->MODEM &= ~UART_MODEM_RTSACTLV_Msk;
    }

    LOG_I("Set %s to RS-485 AUD function mode. ActiveLowLevel-%s", psNuUart->name, bRTSActiveLowLevel ? "YES" : "NO");
}

/**
 * Configure uart port
 */
static rt_err_t nu_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;
    rt_err_t ret = RT_EOK;
    uint32_t uart_word_len, uart_stop_bit, uart_parity;

    RT_ASSERT(serial);
    RT_ASSERT(cfg);

    /* Check baudrate */
    RT_ASSERT(cfg->baud_rate != 0);

    uart_word_len = uart_stop_bit = uart_parity = 0;

    /* Get base address of uart register */
    UART_T *base = psNuUart->base;

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
        LOG_E("Unsupported data length.");
        ret = RT_EINVAL;
        goto exit_nu_uart_configure;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart_stop_bit = UART_STOP_BIT_1;
        break;

    case STOP_BITS_2:
        uart_stop_bit = UART_STOP_BIT_2;
        break;

    default:
        LOG_E("Unsupported stop bit.");
        ret = RT_EINVAL;
        goto exit_nu_uart_configure;
    }
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
        LOG_E("Unsupported parity.");
        ret = RT_EINVAL;
        goto exit_nu_uart_configure;
    }
    SYS_ResetModule(psNuUart->rst);

    /* Open Uart and set UART Baudrate */
    UART_Open(base, cfg->baud_rate);

    /* Set line configuration. */
    UART_SetLineConfig(base, 0, uart_word_len, uart_parity, uart_stop_bit);

    /* Enable NVIC interrupt. */
    NVIC_EnableIRQ(psNuUart->irqn);

exit_nu_uart_configure:

    if (ret != RT_EOK)
        UART_Close(base);

    return -(ret);
}
#if defined(RT_SERIAL_USING_DMA)

static void nu_pdma_uart_rxbuf_free(nu_uart_t psNuUart)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)psNuUart;

    if ((serial->config.bufsz > 0) && psNuUart->dmabuf.pu8RxBuf)
        rt_free_align(psNuUart->dmabuf.pu8RxBuf);

    psNuUart->dmabuf.pu8RxBuf = RT_NULL;
    psNuUart->dmabuf.bufsize = 0;
    psNuUart->dmabuf.put_index = 0;
}

static rt_err_t nu_pdma_uart_rx_config(nu_uart_t psNuUart, uint8_t *pu8Buf, int32_t i32TriggerLen)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)psNuUart;

    rt_err_t result = RT_EOK;
    struct nu_pdma_chn_cb sChnCB;

    uint32_t u32IdleTimeoutInUs = 1500;

    /* Get base address of uart register */
    UART_T *base = psNuUart->base;

    /* Register ISR callback function */
    sChnCB.m_eCBType = eCBType_Event;
    sChnCB.m_pfnCBHandler = nu_pdma_uart_rx_cb;
    sChnCB.m_pvUserData = (void *)psNuUart;

    nu_pdma_filtering_set(psNuUart->pdma_chanid_rx, CONFIG_PDMA_USE_IT);
    result = nu_pdma_callback_register(psNuUart->pdma_chanid_rx, &sChnCB);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uart_rx_config;
    }
#if defined(CONFIG_UART_USE_IDLE_TIMER)
    LOG_I("[%s] Set UART bus idle time to %d bit time.", psNuUart->name, CONFIG_UART_IDLE_TIMEOUT_VALUE);
#else
    LOG_I("[%s] Set PDMA idle time out %d us", psNuUart->name, CONFIG_PDMA_IDLE_TIMEOUT_VALUE);
#endif

    LOG_I("[%s] bufsz: %d B", psNuUart->name, serial->config.bufsz);

    if (serial->config.bufsz == 0)
    {
        psNuUart->dmabuf.bufsize = i32TriggerLen;
        psNuUart->dmabuf.put_index = 0;
        psNuUart->dmabuf.pu8RxBuf = pu8Buf;

        result = nu_pdma_transfer(psNuUart->pdma_chanid_rx,
                                  8,
                                  (uint32_t)&base->DAT,
                                  (uint32_t)pu8Buf,
                                  i32TriggerLen,
                                  CONFIG_PDMA_IDLE_TIMEOUT_VALUE);  //Idle-timeout
        if (result != RT_EOK)
        {
            goto exit_nu_pdma_uart_rx_config;
        }
    }
    else
    {
        struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
#if defined(RT_USING_CACHE)
        /* Allocate aligned and align-up DMA buffer for cache coherence. */
        psNuUart->dmabuf.pu8RxBuf = rt_malloc_align(RT_ALIGN(i32TriggerLen, 32), 32);
        psNuUart->dmabuf.bufsize = 0;
        if (psNuUart->dmabuf.pu8RxBuf == RT_NULL)
        {
            LOG_E("Failed to allocate dma memory %d.", i32TriggerLen);
            goto exit_nu_pdma_uart_rx_config;
        }
        rx_fifo->buffer = (rt_uint8_t *) psNuUart->dmabuf.pu8RxBuf;
        rt_memset(rx_fifo->buffer, 0, i32TriggerLen);
#endif
        psNuUart->dmabuf.bufsize = i32TriggerLen;
        psNuUart->dmabuf.put_index = 0;

        /* For Serial RX FIFO - Single buffer recycle SG trigger */
        result = nu_pdma_desc_setup(psNuUart->pdma_chanid_rx,
                                    psNuUart->pdma_rx_desc,
                                    8,
                                    (uint32_t)&base->DAT,
                                    (uint32_t)rx_fifo->buffer,
                                    i32TriggerLen,
                                    psNuUart->pdma_rx_desc,
                                    0);
        if (result != RT_EOK)
        {
            goto exit_nu_pdma_uart_rx_config;
        }
        result = nu_pdma_sg_transfer(psNuUart->pdma_chanid_rx, psNuUart->pdma_rx_desc, CONFIG_PDMA_IDLE_TIMEOUT_VALUE);
        if (result != RT_EOK)
        {
            goto exit_nu_pdma_uart_rx_config;
        }
    }
#if defined(CONFIG_UART_USE_IDLE_TIMER)
    UART_SetTimeoutCnt(base, CONFIG_UART_IDLE_TIMEOUT_VALUE);
    UART_BUS_IDLE_TIMEOUT_ENABLE(base);
#endif

    /* Enable Receive Line interrupt & Start DMA RX transfer. */
    UART_ENABLE_INT(base, CONFIG_UART_USE_RXDMA_IT);

exit_nu_pdma_uart_rx_config:

    return result;
}

static void nu_pdma_uart_rx_cb(void *pvOwner, uint32_t u32Events)
{
    nu_uart_t psNuUart = (nu_uart_t)pvOwner;
    struct rt_serial_device *serial = (struct rt_serial_device *)psNuUart;
    rt_size_t recv_len = 0;
    uint32_t dma_put_index = 0;

    RT_ASSERT(psNuUart);

    /* Get base address of uart register */
    UART_T *base = psNuUart->base;
    nu_rxbuf_ctx_t psNuRxBufCtx = &psNuUart->dmabuf;

    dma_put_index = nu_pdma_transferred_byte_get(psNuUart->pdma_chanid_rx, psNuRxBufCtx->bufsize);
    if (u32Events & (NU_PDMA_EVENT_TRANSFER_DONE | NU_PDMA_EVENT_TIMEOUT))
    {
        if (u32Events & NU_PDMA_EVENT_TRANSFER_DONE)
        {
            dma_put_index = psNuRxBufCtx->bufsize;
        }
        else if ((u32Events & NU_PDMA_EVENT_TIMEOUT) && !UART_GET_RX_EMPTY(base))
        {
            return;
        }

        recv_len = dma_put_index - psNuRxBufCtx->put_index;

        if (recv_len > 0)
        {
            psNuRxBufCtx->put_index = dma_put_index % psNuRxBufCtx->bufsize;
        }
    }

    if ((serial->config.bufsz == 0) && (u32Events & NU_PDMA_EVENT_TRANSFER_DONE))
    {
        recv_len = psNuRxBufCtx->bufsize;
    }

    if (recv_len > 0)
    {
        rt_hw_serial_isr(&psNuUart->dev, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
}

static rt_err_t nu_pdma_uart_tx_config(nu_uart_t psNuUart)
{
    struct nu_pdma_chn_cb sChnCB;
    RT_ASSERT(psNuUart);

    /* Register ISR callback function */
    sChnCB.m_eCBType = eCBType_Event;
    sChnCB.m_pfnCBHandler = nu_pdma_uart_tx_cb;
    sChnCB.m_pvUserData = (void *)psNuUart;

    nu_pdma_filtering_set(psNuUart->pdma_chanid_tx, NU_PDMA_EVENT_TRANSFER_DONE);
    return nu_pdma_callback_register(psNuUart->pdma_chanid_tx, &sChnCB);
}

static void nu_pdma_uart_tx_cb(void *pvOwner, uint32_t u32Events)
{
    nu_uart_t psNuUart = (nu_uart_t)pvOwner;
    RT_ASSERT(psNuUart);

    UART_DISABLE_INT(psNuUart->base, CONFIG_UART_USE_TXDMA_IT);// Stop DMA TX transfer

    if (u32Events & NU_PDMA_EVENT_TRANSFER_DONE)
    {
        /* Get base address of uart register */
        UART_T *base = psNuUart->base;

        /* Waiting if TX-FIFO is empty. */
        while (!(UART_IS_TX_EMPTY(base)));

        rt_hw_serial_isr(&psNuUart->dev, RT_SERIAL_EVENT_TX_DMADONE);
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
    UART_T *base = psNuUart->base;
    if (direction == RT_SERIAL_DMA_TX)
    {
        result = nu_pdma_transfer(psNuUart->pdma_chanid_tx,
                                  8,
                                  (uint32_t)buf,
                                  (uint32_t)base,
                                  size,
                                  0);  // wait-forever
        // Start DMA TX transfer
        UART_ENABLE_INT(base, CONFIG_UART_USE_TXDMA_IT);
    }
    else if (direction == RT_SERIAL_DMA_RX)
    {
        UART_DISABLE_INT(base, CONFIG_UART_USE_RXDMA_IT);

        // If config.bufsz = 0, serial will trigger once.
        result = nu_pdma_uart_rx_config(psNuUart, buf, size);
    }
    else
    {
        result = RT_ERROR;
    }

    return result;
}

static int nu_hw_uart_dma_allocate(nu_uart_t psNuUart)
{
    RT_ASSERT(psNuUart);

    /* Allocate UART_TX nu_dma channel */
    if (psNuUart->pdma_perp_tx != NU_PDMA_UNUSED)
    {
        psNuUart->pdma_chanid_tx = nu_pdma_channel_allocate(psNuUart->pdma_perp_tx);
        if (psNuUart->pdma_chanid_tx >= 0)
        {
            psNuUart->dma_flag |= RT_DEVICE_FLAG_DMA_TX;
        }
    }
    if (psNuUart->pdma_perp_rx != NU_PDMA_UNUSED)
    {
        psNuUart->pdma_chanid_rx = nu_pdma_channel_allocate(psNuUart->pdma_perp_rx);
        if (psNuUart->pdma_chanid_rx >= 0)
        {
            rt_err_t ret = RT_EOK;
            psNuUart->dma_flag |= RT_DEVICE_FLAG_DMA_RX;
            ret = nu_pdma_sgtbls_allocate(psNuUart->pdma_chanid_rx, &psNuUart->pdma_rx_desc, 1);
            RT_ASSERT(ret == RT_EOK);
        }
    }

    return RT_EOK;
}

int8_t nu_uart_get_rx_pdma_chnid(struct rt_serial_device *serial)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;

    RT_ASSERT(serial);

    return psNuUart->pdma_chanid_rx;
}

struct nu_rxbuf_ctx *nu_uart_get_rx_pdma_bufaddr(struct rt_serial_device *serial)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;

    RT_ASSERT(serial);

    return &psNuUart->dmabuf;
}

int8_t nu_uart_get_tx_pdma_chnid(struct rt_serial_device *serial)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;

    RT_ASSERT(serial);

    return psNuUart->pdma_chanid_tx;
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
    UART_T *base = psNuUart->base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Disable INT-RX */
        {
            UART_DISABLE_INT(base, UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_TOCNTEN_Msk);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) /* Disable DMA-RX */
        {
            /* Disable Receive Line interrupt & Stop DMA RX transfer. */
#if defined(RT_SERIAL_USING_DMA)
            if (psNuUart->dma_flag & RT_DEVICE_FLAG_DMA_RX)
            {
                nu_pdma_channel_terminate(psNuUart->pdma_chanid_rx);
                nu_pdma_uart_rxbuf_free(psNuUart);
            }
            UART_DISABLE_INT(base, CONFIG_UART_USE_RXDMA_IT);
#if defined(CONFIG_UART_USE_IDLE_TIMER)
            UART_BUS_IDLE_TIMEOUT_DISABLE(base);
#endif

#endif
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Enable INT-RX */
        {
            UART_ENABLE_INT(base, UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_TOCNTEN_Msk);
        }
        break;
#if defined(RT_SERIAL_USING_DMA)
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) /* Configure and trigger DMA-RX */
        {
            struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
            result = nu_pdma_uart_rx_config(psNuUart, rx_fifo->buffer, serial->config.bufsz);  // Config & trigger
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX) /* Configure DMA-TX */
        {
            result = nu_pdma_uart_tx_config(psNuUart);
        }
        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:
        /* Disable NVIC interrupt. */
        NVIC_DisableIRQ(psNuUart->irqn);
#if defined(RT_SERIAL_USING_DMA)

#if defined(CONFIG_UART_USE_IDLE_TIMER)
        UART_BUS_IDLE_TIMEOUT_DISABLE(base);
#endif

        UART_DISABLE_INT(base, CONFIG_UART_USE_RXDMA_IT);
        UART_DISABLE_INT(base, CONFIG_UART_USE_TXDMA_IT);

        if (psNuUart->dma_flag != 0)
        {
            nu_pdma_channel_terminate(psNuUart->pdma_chanid_tx);
            nu_pdma_channel_terminate(psNuUart->pdma_chanid_rx);
            nu_pdma_uart_rxbuf_free(psNuUart);
        }
#endif

        /* Close UART port */
        UART_Close(base);

        break;

    default:
        /* Flush TX FIFO */
        UART_WAIT_TX_EMPTY(base);
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
    nu_uart_t psNuUart = (nu_uart_t)serial;

    RT_ASSERT(serial);

    /* Get base address of uart register */
    UART_T *base = psNuUart->base;

    /* Waiting if TX-FIFO is full. */
    while (UART_IS_TX_FULL(base));

    /* Put char into TX-FIFO */
    UART_WRITE(base, c);

    return 1;
}

/**
 * Uart get char
 */
static int nu_uart_receive(struct rt_serial_device *serial)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;

    RT_ASSERT(serial);

    /* Get base address of uart register */
    UART_T *base = psNuUart->base;

    /* Return failure if RX-FIFO is empty. */
    if (UART_GET_RX_EMPTY(base))
    {
        return -1;
    }
    return UART_READ(base);
}

void nu_uart_set_loopback(struct rt_serial_device *serial, rt_bool_t bOn)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;

    RT_ASSERT(serial);

    /* Get base address of uart register */
    UART_T *base = psNuUart->base;

    bOn ? (base->MODEM |= 0x10) : (base->MODEM &= ~0x10);
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
        rt_memset(&nu_uart_arr[i].dmabuf, 0, sizeof(struct nu_rxbuf_ctx));
#endif

        ret = rt_hw_serial_register(&nu_uart_arr[i].dev, nu_uart_arr[i].name, flag, NULL);
        RT_ASSERT(ret == RT_EOK);

    }

    return ret;
}
#endif //#if defined(BSP_USING_UART)
