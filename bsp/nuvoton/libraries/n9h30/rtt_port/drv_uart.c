/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-1-11       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_UART)

#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"
#include <drv_uart.h>
#include <drv_sys.h>


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
    UART_CNT
};

/* Private typedef --------------------------------------------------------------*/
struct nu_uart
{
    rt_serial_t dev;
    char *name;
    UART_T *uart_base;
    IRQn_Type irqn;
    E_SYS_IPRST rstidx;
    E_SYS_IPCLK clkidx;
};
typedef struct nu_uart *nu_uart_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t nu_uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int nu_uart_send(struct rt_serial_device *serial, char c);
static int nu_uart_receive(struct rt_serial_device *serial);

/* Public functions ------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/

static const struct rt_uart_ops nu_uart_ops =
{
    .configure = nu_uart_configure,
    .control = nu_uart_control,
    .putc = nu_uart_send,
    .getc = nu_uart_receive,
    .dma_transmit = RT_NULL
};

static const struct serial_configure nu_uart_default_config =
        RT_SERIAL_CONFIG_DEFAULT;

static struct nu_uart nu_uart_arr [] =
{
#if defined(BSP_USING_UART0)
    {
        .name = "uart0",
        .uart_base = UART0,
        .irqn = IRQ_UART0,
        .rstidx = UART0RST,
        .clkidx = UART0CKEN,
    },
#endif

#if defined(BSP_USING_UART1)
    {
        .name = "uart1",
        .uart_base = UART1,
        .irqn = IRQ_UART1,
        .rstidx = UART1RST,
        .clkidx = UART1CKEN,
    },
#endif

#if defined(BSP_USING_UART2)
    {
        .name = "uart2",
        .uart_base = UART2,
        .irqn = IRQ_UART2,
        .rstidx = UART2RST,
        .clkidx = UART2CKEN,
    },
#endif

#if defined(BSP_USING_UART3)
    {
        .name = "uart3",
        .uart_base = UART3,
        .irqn = IRQ_UART3,
        .rstidx = UART3RST,
        .clkidx = UART3CKEN,
    },
#endif

#if defined(BSP_USING_UART4)
    {
        .name = "uart4",
        .uart_base = UART4,
        .irqn = IRQ_UART4,
        .rstidx = UART4RST,
        .clkidx = UART4CKEN,
    },
#endif

#if defined(BSP_USING_UART5)
    {
        .name = "uart5",
        .uart_base = UART5,
        .irqn = IRQ_UART5,
        .rstidx = UART5RST,
        .clkidx = UART5CKEN,
    },
#endif

#if defined(BSP_USING_UART6)
    {
        .name = "uart6",
        .uart_base = UART6,
        .irqn = IRQ_UART6,
        .rstidx = UART6RST,
        .clkidx = UART6CKEN,
    },
#endif

#if defined(BSP_USING_UART7)
    {
        .name = "uart7",
        .uart_base = UART7,
        .irqn = IRQ_UART7,
        .rstidx = UART7RST,
        .clkidx = UART7CKEN,
    },
#endif

#if defined(BSP_USING_UART8)
    {
        .name = "uart8",
        .uart_base = UART8,
        .irqn = IRQ_UART8,
        .rstidx = UART8RST,
        .clkidx = UART8CKEN,
    },
#endif

#if defined(BSP_USING_UART9)
    {
        .name = "uart9",
        .uart_base = UART9,
        .irqn = IRQ_UART9,
        .rstidx = UART9RST,
        .clkidx = UART9CKEN,
    },
#endif

#if defined(BSP_USING_UART10)
    {
        .name = "uart10",
        .uart_base = UARTA,
        .irqn = IRQ_UART10,
        .rstidx = UART10RST,
        .clkidx = UART10CKEN,
    },
#endif

}; /* uart nu_uart */

/**
 * All UART interrupt service routine
 */
static void nu_uart_isr(int vector, void *param)
{
    /* Get base address of uart register */
    nu_uart_t serial = (nu_uart_t)param;
    UART_T *uart_base = ((nu_uart_t)serial)->uart_base;

    /* Get interrupt event */
    uint32_t u32IntSts = uart_base->INTSTS;
    uint32_t u32FIFOSts = uart_base->FIFOSTS;

    /* Handle RX event */
    if (u32IntSts & (UART_ISR_RDA_INT_Msk | UART_ISR_TOUT_INT_Msk))
    {
        rt_hw_serial_isr(&serial->dev, RT_SERIAL_EVENT_RX_IND);
    }
    uart_base->INTSTS = u32IntSts;
    uart_base->FIFOSTS = u32FIFOSts;
}

/**
 * Set RS-485 AUD mode
 */
void nu_uart_set_rs485aud(struct rt_serial_device *serial, rt_bool_t bRTSActiveLowLevel)
{
    UART_T *uart_base;
    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uart register */
    uart_base = ((nu_uart_t)serial)->uart_base;

    /* Set RTS as RS-485 phy direction controlling ping. */
    uart_base->FUNCSEL = UART_FUNCSEL_RS485;

    /* Set RS585 configuration */
    uart_base->ALTCTL &= ~(UART_ALT_CSR_RS485_NMM_Msk | UART_ALT_CSR_RS485_AAD_Msk | UART_ALT_CSR_RS485_AUD_Msk | UART_ALT_CSR_RS485_ADD_EN_Msk);
    uart_base->ALTCTL |= UART_ALT_CSR_RS485_AUD_Msk;

    if (bRTSActiveLowLevel)
    {
        /* Set direction pin as active-high. */
        uart_base->MODEM &= ~UART_MCR_LEV_RTS_Msk;
    }
    else
    {
        /* Set direction pin as active-low. */
        uart_base->MODEM |= UART_MCR_LEV_RTS_Msk;
    }

    rt_kprintf("Set %s to RS-485 AUD function mode. ActiveLowLevel-%s\n", ((nu_uart_t)serial)->name, bRTSActiveLowLevel ? "YES" : "NO");
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

    /* Get base address of uart register */
    UART_T *uart_base = ((nu_uart_t)serial)->uart_base;

    /* Check baudrate */
    RT_ASSERT(cfg->baud_rate != 0);

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
        rt_kprintf("Unsupported data length");
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
        rt_kprintf("Unsupported stop bit");
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
        rt_kprintf("Unsupported parity");
        ret = -RT_EINVAL;
        goto exit_nu_uart_configure;
    }

    nu_sys_ip_reset(((nu_uart_t)serial)->rstidx);

    /* Open Uart and set UART Baudrate */
    UART_Open(uart_base, cfg->baud_rate);

    /* Set line configuration. */
    UART_SetLineConfig(uart_base, 0, uart_word_len, uart_parity, uart_stop_bit);

    /* Enable interrupt. */
    rt_hw_interrupt_umask(((nu_uart_t)serial)->irqn);

exit_nu_uart_configure:

    if (ret != RT_EOK)
        UART_Close(uart_base);

    return -(ret);
}

/**
 * Uart interrupt control
 */
static rt_err_t nu_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;
    rt_err_t result = RT_EOK;
    rt_uint32_t flag;
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uart register */
    UART_T *uart_base = psNuUart->uart_base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Disable INT-RX */
        {
            flag = UART_IER_RDA_IEN_Msk | UART_IER_RTO_IEN_Msk | UART_IER_TIME_OUT_EN_Msk;
            UART_DISABLE_INT(uart_base, flag);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX) /* Disable DMA-RX */
        {
            /* Disable Receive Line interrupt & Stop DMA RX transfer. */
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Enable INT-RX */
        {
            flag = UART_IER_RDA_IEN_Msk | UART_IER_RTO_IEN_Msk | UART_IER_TIME_OUT_EN_Msk;
            UART_ENABLE_INT(uart_base, flag);
        }
        break;

    case RT_DEVICE_CTRL_CLOSE:
        /* Disable interrupt. */
        rt_hw_interrupt_mask(psNuUart->irqn);

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
    RT_ASSERT(serial != RT_NULL);

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
    RT_ASSERT(serial != RT_NULL);

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
    rt_uint32_t flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;
    rt_err_t ret = RT_EOK;

    for (i = (UART_START + 1); i < UART_CNT; i++)
    {
        nu_uart_arr[i].dev.ops    = &nu_uart_ops;
        nu_uart_arr[i].dev.config = nu_uart_default_config;

        rt_hw_interrupt_install(nu_uart_arr[i].irqn, nu_uart_isr, &nu_uart_arr[i], nu_uart_arr[i].name);

        nu_sys_ipclk_enable(nu_uart_arr[i].clkidx);

        ret = rt_hw_serial_register(&nu_uart_arr[i].dev, nu_uart_arr[i].name, flag, NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return ret;
}

#endif //#if defined(BSP_USING_UART)
