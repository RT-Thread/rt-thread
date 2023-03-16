/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_UART)

#include <rthw.h>
#include "drv_uart.h"
#include "drv_sys.h"
#include "drv_common.h"

#if defined(RT_SERIAL_USING_DMA)
    #include <drv_pdma.h>
#endif

#define LOG_TAG    "drv.uart"
//#undef  DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL      LOG_LVL_INFO
#define DBG_COLOR
#include <rtdbg.h>

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
#if defined(BSP_USING_UART6)
    UART6_IDX,
#endif
#if defined(BSP_USING_UART7)
    UART7_IDX,
#endif
#if defined(BSP_USING_UART8)
    UART8_IDX,
#endif
#if defined(BSP_USING_UART9)
    UART9_IDX,
#endif
#if defined(BSP_USING_UART10)
    UART10_IDX,
#endif
#if defined(BSP_USING_UART11)
    UART11_IDX,
#endif
#if defined(BSP_USING_UART12)
    UART12_IDX,
#endif
#if defined(BSP_USING_UART13)
    UART13_IDX,
#endif
#if defined(BSP_USING_UART14)
    UART14_IDX,
#endif
#if defined(BSP_USING_UART15)
    UART15_IDX,
#endif
#if defined(BSP_USING_UART16)
    UART16_IDX,
#endif
    UART_CNT
};

struct nu_rxbuf_ctx
{
    void * pvRxBuf;
    uint32_t bufsize;
    uint32_t wrote_offset;
    uint32_t reserved;
};
typedef struct nu_rxbuf_ctx *nu_rxbuf_ctx_t;

/* Private typedef --------------------------------------------------------------*/
struct nu_uart
{
    rt_serial_t dev;
    char *name;
    UART_T *base;
    IRQn_Type irqn;
    uint32_t rstidx;

#if defined(RT_SERIAL_USING_DMA)
    uint32_t dma_flag;
    int16_t pdma_perp_tx;
    int8_t  pdma_chanid_tx;

    int16_t pdma_perp_rx;
    int8_t  pdma_chanid_rx;

    nu_pdma_desc_t pdma_rx_desc;

    struct nu_rxbuf_ctx dmabuf;
    struct nu_rxbuf_ctx userbuf;
#endif

};
typedef struct nu_uart *nu_uart_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t nu_uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int nu_uart_send(struct rt_serial_device *serial, char c);
static int nu_uart_receive(struct rt_serial_device *serial);

#if defined(RT_SERIAL_USING_DMA)
    static rt_ssize_t nu_uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);
    static void nu_pdma_uart_rx_cb(void *pvOwner, uint32_t u32Events);
    static void nu_pdma_uart_tx_cb(void *pvOwner, uint32_t u32Events);
    static uint32_t nu_uart_flush(nu_uart_t psNuUart, uint32_t pdma_new_rxsize);
#endif

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
        .base = UART0,
        .irqn = UART0_IRQn,
        .rstidx = UART0_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART0_TX_DMA)
        .pdma_perp_tx = PDMA_UART0_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART0_RX_DMA)
        .pdma_perp_rx = PDMA_UART0_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART1)
    {
        .name = "uart1",
        .base = UART1,
        .irqn = UART1_IRQn,
        .rstidx = UART1_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART1_TX_DMA)
        .pdma_perp_tx = PDMA_UART1_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART1_RX_DMA)
        .pdma_perp_rx = PDMA_UART1_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART2)
    {
        .name = "uart2",
        .base = UART2,
        .irqn = UART2_IRQn,
        .rstidx = UART2_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART2_TX_DMA)
        .pdma_perp_tx = PDMA_UART2_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART2_RX_DMA)
        .pdma_perp_rx = PDMA_UART2_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART3)
    {
        .name = "uart3",
        .base = UART3,
        .irqn = UART3_IRQn,
        .rstidx = UART3_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART3_TX_DMA)
        .pdma_perp_tx = PDMA_UART3_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART3_RX_DMA)
        .pdma_perp_rx = PDMA_UART3_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART4)
    {
        .name = "uart4",
        .base = UART4,
        .irqn = UART4_IRQn,
        .rstidx = UART4_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART4_TX_DMA)
        .pdma_perp_tx = PDMA_UART4_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART4_RX_DMA)
        .pdma_perp_rx = PDMA_UART4_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART5)
    {
        .name = "uart5",
        .base = UART5,
        .irqn = UART5_IRQn,
        .rstidx = UART5_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART5_TX_DMA)
        .pdma_perp_tx = PDMA_UART5_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART5_RX_DMA)
        .pdma_perp_rx = PDMA_UART5_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART6)
    {
        .name = "uart6",
        .base = UART6,
        .irqn = UART6_IRQn,
        .rstidx = UART6_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART6_TX_DMA)
        .pdma_perp_tx = PDMA_UART6_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART6_RX_DMA)
        .pdma_perp_rx = PDMA_UART6_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART7)
    {
        .name = "uart7",
        .base = UART7,
        .irqn = UART7_IRQn,
        .rstidx = UART7_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART7_TX_DMA)
        .pdma_perp_tx = PDMA_UART7_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART7_RX_DMA)
        .pdma_perp_rx = PDMA_UART7_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART8)
    {
        .name = "uart8",
        .base = UART8,
        .irqn = UART8_IRQn,
        .rstidx = UART8_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART8_TX_DMA)
        .pdma_perp_tx = PDMA_UART8_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART8_RX_DMA)
        .pdma_perp_rx = PDMA_UART8_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART9)
    {
        .name = "uart9",
        .base = UART9,
        .irqn = UART9_IRQn,
        .rstidx = UART9_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART9_TX_DMA)
        .pdma_perp_tx = PDMA_UART9_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART9_RX_DMA)
        .pdma_perp_rx = PDMA_UART9_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART10)
    {
        .name = "uart10",
        .base = UART10,
        .irqn = UART10_IRQn,
        .rstidx = UART10_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART10_TX_DMA)
        .pdma_perp_tx = PDMA_UART10_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART10_RX_DMA)
        .pdma_perp_rx = PDMA_UART10_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART11)
    {
        .name = "uart11",
        .base = UART11,
        .irqn = UART11_IRQn,
        .rstidx = UART11_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART11_TX_DMA)
        .pdma_perp_tx = PDMA_UART11_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART11_RX_DMA)
        .pdma_perp_rx = PDMA_UART11_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART12)
    {
        .name = "uart12",
        .base = UART12,
        .irqn = UART12_IRQn,
        .rstidx = UART12_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART12_TX_DMA)
        .pdma_perp_tx = PDMA_UART12_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART12_RX_DMA)
        .pdma_perp_rx = PDMA_UART12_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART13)
    {
        .name = "uart13",
        .base = UART13,
        .irqn = UART13_IRQn,
        .rstidx = UART13_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART13_TX_DMA)
        .pdma_perp_tx = PDMA_UART13_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART13_RX_DMA)
        .pdma_perp_rx = PDMA_UART13_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART14)
    {
        .name = "uart14",
        .base = UART14,
        .irqn = UART14_IRQn,
        .rstidx = UART14_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART14_TX_DMA)
        .pdma_perp_tx = PDMA_UART14_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART14_RX_DMA)
        .pdma_perp_rx = PDMA_UART14_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART15)
    {
        .name = "uart15",
        .base = UART15,
        .irqn = UART15_IRQn,
        .rstidx = UART15_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART15_TX_DMA)
        .pdma_perp_tx = PDMA_UART15_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART15_RX_DMA)
        .pdma_perp_rx = PDMA_UART15_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

#if defined(BSP_USING_UART16)
    {
        .name = "uart16",
        .base = UART16,
        .irqn = UART16_IRQn,
        .rstidx = UART16_RST,

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_USING_UART16_TX_DMA)
        .pdma_perp_tx = PDMA_UART16_TX,
#else
        .pdma_perp_tx = NU_PDMA_UNUSED,
#endif
#if defined(BSP_USING_UART16_RX_DMA)
        .pdma_perp_rx = PDMA_UART16_RX,
#else
        .pdma_perp_rx = NU_PDMA_UNUSED,
#endif
#endif
    },
#endif

}; /* uart nu_uart */

/**
 * All UART interrupt service routine
 */
static void nu_uart_isr(int vector, void *param)
{
    /* Get base address of uart register */
    nu_uart_t psNuUart = (nu_uart_t)param;
    UART_T *base = psNuUart->base;

    /* Get interrupt event */
    uint32_t u32IntSts = base->INTSTS;
    uint32_t u32FIFOSts = base->FIFOSTS;

#if defined(RT_SERIAL_USING_DMA)
    if (u32IntSts & UART_INTSTS_PRLSIF_Msk)
    {
        /* Drain RX FIFO to remove remain FEF frames in FIFO. */
        base->FIFO |= UART_FIFO_RXRST_Msk;
        base->FIFOSTS |= (UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk);
        return;
    }

    if (u32IntSts & UART_INTSTS_PTOIF_Msk)
    {
        nu_uart_flush(psNuUart, 0);
        return;
    }
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
        LOG_E("Unsupported stop bit.");
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
        LOG_E("Unsupported parity.");
        ret = -RT_EINVAL;
        goto exit_nu_uart_configure;
    }

    /* Reset this module */
    nu_sys_ip_reset(psNuUart->rstidx);

    /* Open Uart and set UART Baudrate */
    UART_Open(base, cfg->baud_rate);

    /* Set line configuration. */
    UART_SetLineConfig(base, 0, uart_word_len, uart_parity, uart_stop_bit);

    /* Enable interrupt. */
    rt_hw_interrupt_umask(psNuUart->irqn);

exit_nu_uart_configure:

    if (ret != RT_EOK)
        UART_Close(base);

    return -(ret);
}

#if defined(RT_SERIAL_USING_DMA)

static uint32_t nu_uart_flush_sync(
    uint8_t *dst_buf_start,
    uint8_t *dst_buf_put,
    uint8_t *src_buf_start,
    uint8_t *src_buf_put,
    uint32_t bufsize,
    uint32_t sync_len)
{
    uint32_t count = 0;

    /* Copy bytes in Source's ring-buffer to Destination's ring-buffer. */
    while ( count < sync_len )
    {
        if ( dst_buf_put >= (dst_buf_start + bufsize) )
        {
            dst_buf_put = dst_buf_start;
        }

        if ( src_buf_put >= (src_buf_start + bufsize) )
        {
            src_buf_put = src_buf_start;
        }

        *dst_buf_put = *src_buf_put;

        src_buf_put++;
        dst_buf_put++;

        count++;
    }

    return count;
}

static uint32_t nu_uart_flush(nu_uart_t psNuUart, uint32_t pdma_new_rxsize)
{
    uint32_t recv_len;
    UART_T *base = psNuUart->base;
    uint8_t tempbuf[64];

    /* Disable Receive Line interrupt first. */
    UART_DISABLE_INT(base, UART_INTEN_RXPDMAEN_Msk);

    /* Pick up RX bytes in PDMA RX BUFFER. */
    if ( pdma_new_rxsize > 0 )
    {
        nu_pdma_desc_t psDesc = nu_pdma_get_channel_desc(psNuUart->pdma_chanid_rx);
        #if !defined(USE_MA35D1_SUBM)
            uint8_t *pu8DmaBuf_noncache = (uint8_t *)(psDesc->DA + UNCACHEABLE);
        #else
            uint8_t *pu8DmaBuf_noncache = (uint8_t *)(psDesc->DA);
        #endif

        /* Update wrote offset of user buffer. */
        psNuUart->userbuf.wrote_offset += nu_uart_flush_sync( psNuUart->userbuf.pvRxBuf,
                                                              (uint8_t *)psNuUart->userbuf.pvRxBuf + psNuUart->userbuf.wrote_offset,
                                                              pu8DmaBuf_noncache,
                                                              pu8DmaBuf_noncache + psNuUart->dmabuf.wrote_offset,
                                                              psNuUart->userbuf.bufsize,
                                                              pdma_new_rxsize );
        psNuUart->userbuf.wrote_offset %= psNuUart->userbuf.bufsize;
    }

    /* Pick up RX bytes in UART FIFO. */
    recv_len = 0;
    while (!UART_GET_RX_EMPTY(base))
    {
        tempbuf[recv_len] = UART_READ(base);
        recv_len++;
        RT_ASSERT( recv_len < sizeof(tempbuf) );
    }
    if ( recv_len > 0 )
    {
        /* Update wrote offset of user buffer. */
        psNuUart->userbuf.wrote_offset += nu_uart_flush_sync( psNuUart->userbuf.pvRxBuf,
                                                              psNuUart->userbuf.pvRxBuf + psNuUart->userbuf.wrote_offset,
                                                              tempbuf,
                                                              tempbuf,
                                                              psNuUart->userbuf.bufsize,
                                                              recv_len );
        psNuUart->userbuf.wrote_offset %= psNuUart->userbuf.bufsize;
    }

    /* Report received bytes = UART_FIFO_RXSIZE + PDMA_NEW_RXSIZE */
    recv_len += pdma_new_rxsize;
    if (recv_len > 0)
    {
        LOG_D("%d(Received) = %d(PDMA) + %d(FIFO)",
                        recv_len - pdma_new_rxsize,
                        pdma_new_rxsize,
                        recv_len);

        LOG_D("User: [%08x] bufsize=%d, wrote_offset=%d",
                        psNuUart->userbuf.pvRxBuf,
                        psNuUart->userbuf.bufsize,
                        psNuUart->userbuf.wrote_offset);

        LOG_D("DMA: [%08x] bufsize=%d, put=%d",
                        psNuUart->dmabuf.pvRxBuf,
                        psNuUart->dmabuf.bufsize,
                        psNuUart->dmabuf.wrote_offset);

        rt_hw_serial_isr(&psNuUart->dev, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }

    /* Enable Receive Line interrupt first. */
    UART_ENABLE_INT(base, UART_INTEN_RXPDMAEN_Msk);

    return recv_len;
}

static void nu_pdma_uart_rxbuf_free(nu_uart_t psNuUart)
{
    psNuUart->userbuf.pvRxBuf = RT_NULL;
    psNuUart->userbuf.bufsize = 0;
    psNuUart->userbuf.wrote_offset = 0;

    if (psNuUart->dmabuf.pvRxBuf)
        rt_free_align(psNuUart->dmabuf.pvRxBuf);

    psNuUart->dmabuf.pvRxBuf = RT_NULL;
    psNuUart->dmabuf.bufsize = 0;
    psNuUart->dmabuf.wrote_offset = 0;
}

static rt_err_t nu_pdma_uart_rx_config(nu_uart_t psNuUart, uint8_t *pu8Buf, int32_t i32TriggerLen)
{
    rt_err_t result = RT_EOK;
    struct nu_pdma_chn_cb sChnCB;

    /* Get base address of uart register */
    UART_T *base = psNuUart->base;

    /* Register ISR callback function */
    sChnCB.m_eCBType = eCBType_Event;
    sChnCB.m_pfnCBHandler = nu_pdma_uart_rx_cb;
    sChnCB.m_pvUserData = (void *)psNuUart;

    nu_pdma_filtering_set(psNuUart->pdma_chanid_rx, NU_PDMA_EVENT_TRANSFER_DONE | NU_PDMA_EVENT_TIMEOUT);
    result = nu_pdma_callback_register(psNuUart->pdma_chanid_rx, &sChnCB);

    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uart_rx_config;
    }

    /* Store user buffer context */
    psNuUart->userbuf.pvRxBuf = pu8Buf;
    psNuUart->userbuf.bufsize = i32TriggerLen;
    psNuUart->userbuf.wrote_offset = 0;

    psNuUart->dmabuf.pvRxBuf = rt_malloc_align(i32TriggerLen, 64);
    psNuUart->dmabuf.bufsize = 0;
    if (psNuUart->dmabuf.pvRxBuf == RT_NULL)
    {
        LOG_E("Failed to allocate dma memory %d.", i32TriggerLen);
        goto exit_nu_pdma_uart_rx_config;
    }
    psNuUart->dmabuf.bufsize = i32TriggerLen;
    psNuUart->dmabuf.wrote_offset = 0;

    /* Disable Receive Line interrupt & Start DMA RX transfer. */
    UART_DISABLE_INT(base, UART_INTEN_RLSIEN_Msk | UART_INTEN_RXPDMAEN_Msk | UART_INTEN_RXTOIEN_Msk);

    /* For Serial RX FIFO - Single buffer recycle SG trigger */
    result = nu_pdma_desc_setup(psNuUart->pdma_chanid_rx,
                                psNuUart->pdma_rx_desc,
                                8,
                                (uint32_t)base,
                                (uint32_t)psNuUart->dmabuf.pvRxBuf,
                                psNuUart->dmabuf.bufsize,
                                psNuUart->pdma_rx_desc,
                                0);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uart_rx_config;
    }

    /* Assign head descriptor & go */
    result = nu_pdma_sg_transfer(psNuUart->pdma_chanid_rx, psNuUart->pdma_rx_desc, 500);
    if (result != RT_EOK)
    {
        goto exit_nu_pdma_uart_rx_config;
    }

    UART_SetTimeoutCnt(base, 255);

    /* Enable Receive Line interrupt & Start DMA RX transfer. */
    UART_ENABLE_INT(base, UART_INTEN_RLSIEN_Msk | UART_INTEN_RXPDMAEN_Msk | UART_INTEN_RXTOIEN_Msk);

exit_nu_pdma_uart_rx_config:

    return result;
}

static void nu_pdma_uart_rx_cb(void *pvOwner, uint32_t u32Events)
{
    nu_uart_t psNuUart = (nu_uart_t)pvOwner;
    RT_ASSERT(psNuUart);

    if (u32Events & (NU_PDMA_EVENT_TRANSFER_DONE | NU_PDMA_EVENT_TIMEOUT))
    {
        rt_size_t pdma_rxsize = 0;

        if (u32Events & NU_PDMA_EVENT_TRANSFER_DONE)
        {
            pdma_rxsize = psNuUart->dmabuf.bufsize;
        }
        else
        {
            pdma_rxsize = nu_pdma_transferred_byte_get(psNuUart->pdma_chanid_rx, psNuUart->dmabuf.bufsize);
        }

        nu_uart_flush(psNuUart, pdma_rxsize - psNuUart->dmabuf.wrote_offset);

        /* Update rxdma buffer wrote index */
        psNuUart->dmabuf.wrote_offset = (psNuUart->dmabuf.wrote_offset + pdma_rxsize) % psNuUart->dmabuf.bufsize;
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

    UART_DISABLE_INT(psNuUart->base, UART_INTEN_TXPDMAEN_Msk);// Stop DMA TX transfer

    if (u32Events & NU_PDMA_EVENT_TRANSFER_DONE)
    {
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
        UART_DISABLE_INT(base, UART_INTEN_TXPDMAEN_Msk);
        /* <16 PDMA TX case. */
        if (size < 16)
        {
            int i = 0;
            UART_T *base = psNuUart->base;

            while (i < size)
            {
                /* Waiting if TX-FIFO is full. */
                while (UART_IS_TX_FULL(base));
                /* Put char into TX-FIFO */
                UART_WRITE(base, buf[i]);
                i++;
            }
            rt_hw_serial_isr(&psNuUart->dev, RT_SERIAL_EVENT_TX_DMADONE);
        }
        else
        {
            result = nu_pdma_transfer(psNuUart->pdma_chanid_tx,
                                  8,
                                  (uint32_t)buf,
                                  (uint32_t)base,
                                  size,
                                  0);  // wait-forever
            // Start DMA TX transfer
            UART_ENABLE_INT(base, UART_INTEN_TXPDMAEN_Msk);
        }
    }
    else if (direction == RT_SERIAL_DMA_RX)
    {
        UART_DISABLE_INT(base, UART_INTEN_RLSIEN_Msk | UART_INTEN_RXPDMAEN_Msk | UART_INTEN_TOCNTEN_Msk);

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

    /* Allocate UART_RX nu_dma channel */
    if (psNuUart->pdma_perp_rx != NU_PDMA_UNUSED)
    {
        psNuUart->pdma_chanid_rx = nu_pdma_channel_allocate(psNuUart->pdma_perp_rx);
        if (psNuUart->pdma_chanid_rx >= 0)
        {
            rt_err_t ret = RT_EOK;
            psNuUart->dma_flag |= RT_DEVICE_FLAG_DMA_RX;
            ret = nu_pdma_sgtbls_allocate(&psNuUart->pdma_rx_desc, 1);
            RT_ASSERT(ret == RT_EOK);
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
            UART_DISABLE_INT(base, UART_INTEN_RLSIEN_Msk | UART_INTEN_RXPDMAEN_Msk | UART_INTEN_TOCNTEN_Msk);
#endif
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Enable INT-RX */
        {
            UART_ENABLE_INT(base, UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk);
        }
        break;

#if defined(RT_SERIAL_USING_DMA)
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) /* Configure and trigger DMA-RX */
        {
            struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
            result = nu_pdma_uart_rx_config(psNuUart, &rx_fifo->buffer[0], serial->config.bufsz);  // Config & trigger
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_TX) /* Configure DMA-TX */
        {
            result = nu_pdma_uart_tx_config(psNuUart);
        }
        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:
        /* Disable interrupt. */
        rt_hw_interrupt_mask(psNuUart->irqn);

#if defined(RT_SERIAL_USING_DMA)
        UART_DISABLE_INT(base, UART_INTEN_RLSIEN_Msk | UART_INTEN_RXPDMAEN_Msk | UART_INTEN_TOCNTEN_Msk);
        UART_DISABLE_INT(base, UART_INTEN_TXPDMAEN_Msk);

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

    /* Get char from RX-FIFO */
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
#endif

        rt_hw_interrupt_install(nu_uart_arr[i].irqn, nu_uart_isr, &nu_uart_arr[i], nu_uart_arr[i].name);

        ret = rt_hw_serial_register(&nu_uart_arr[i].dev, nu_uart_arr[i].name, flag, NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return ret;
}

#endif //#if defined(BSP_USING_UART)
