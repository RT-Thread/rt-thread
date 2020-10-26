/**************************************************************************//**
 *
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date            Author       Notes
 * 2020-7-21       Egbert       First version
 *
 ******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_SCUART)

#include <NuMicro.h>
#include <rtdevice.h>
#include <rthw.h>

/* Private definition
 * ---------------------------------------------------------------*/
#define LOG_TAG "drv.scuart"
#define DBG_ENABLE
#define DBG_SECTION_NAME "drv.scuart"
#define DBG_LEVEL DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

enum
{
    SCUART_START = -1,
#if defined(BSP_USING_SCUART0)
    SCUART0_IDX,
#endif
#if defined(BSP_USING_SCUART1)
    SCUART1_IDX,
#endif
#if defined(BSP_USING_SCUART2)
    SCUART2_IDX,
#endif
    SCUART_CNT
};

/* Private typedef
 * --------------------------------------------------------------*/
struct nu_scuart
{
    rt_serial_t dev;
    char *name;
    SC_T *scuart_base;
    uint32_t scuart_rst;
    IRQn_Type scuart_irq_n;
};
typedef struct nu_scuart *nu_scuart_t;

/* Private functions
 * ------------------------------------------------------------*/
static rt_err_t nu_scuart_configure(struct rt_serial_device *serial,
                                    struct serial_configure *cfg);
static rt_err_t nu_scuart_control(struct rt_serial_device *serial, int cmd,
                                  void *arg);
static int nu_scuart_send(struct rt_serial_device *serial, char c);
static int nu_scuart_receive(struct rt_serial_device *serial);
static void nu_scuart_isr(nu_scuart_t serial);

static const struct rt_uart_ops nu_scuart_ops =
{
    .configure = nu_scuart_configure,
    .control = nu_scuart_control,
    .putc = nu_scuart_send,
    .getc = nu_scuart_receive,
    .dma_transmit = RT_NULL /* not support DMA mode */
};

static const struct serial_configure nu_scuart_default_config =
        RT_SERIAL_CONFIG_DEFAULT;

static struct nu_scuart nu_scuart_arr[] =
{
#if defined(BSP_USING_SCUART0)
    {
        .name = "scuart0",
        .scuart_base = SC0,
        .scuart_rst = SC0_RST,
        .scuart_irq_n = SC0_IRQn,
    },
#endif

#if defined(BSP_USING_SCUART1)
    {
        .name = "scuart1",
        .scuart_base = SC1,
        .scuart_rst = SC1_RST,
        .scuart_irq_n = SC1_IRQn,
    },
#endif

#if defined(BSP_USING_SCUART2)
    {
        .name = "scuart2",
        .scuart_base = SC2,
        .scuart_rst = SC2_RST,
        .scuart_irq_n = SC2_IRQn,
    },
#endif

    {0}
}; /* scuart nu_scuart */

/* Interrupt Handle Function
 * ----------------------------------------------------*/
#if defined(BSP_USING_SCUART0)
/* SCUART0 interrupt entry */
void SC0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_scuart_isr(&nu_scuart_arr[SCUART0_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SCUART1)
/* SCUART1 interrupt entry */
void SC1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_scuart_isr(&nu_scuart_arr[SCUART1_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SCUART2)
/* SCUART2 interrupt entry */
void SC2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    nu_scuart_isr(&nu_scuart_arr[SCUART2_IDX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

/**
 * All SCUART interrupt service routine
 */
static void nu_scuart_isr(nu_scuart_t serial)
{
    /* Get base address of scuart register */
    SC_T *scuart_base = ((nu_scuart_t)serial)->scuart_base;

    /* Get interrupt event */
    uint32_t u32IntSts = scuart_base->INTSTS;

    /* Handle RX event */
    if (u32IntSts & (SC_INTSTS_RDAIF_Msk | SC_INTSTS_RXTOIF_Msk))
    {
        rt_hw_serial_isr(&serial->dev, RT_SERIAL_EVENT_RX_IND);

        // RDA is the only interrupt enabled in this driver, this status bit
        // automatically cleared after Rx FIFO empty. So no need to clear interrupt
        // status here.
        scuart_base->INTSTS = SC_INTSTS_RXTOIF_Msk;
    }
}

/**
 * Configure scuart port
 */
static rt_err_t nu_scuart_configure(struct rt_serial_device *serial,
                                    struct serial_configure *cfg)
{
    rt_err_t ret = RT_EOK;
    uint32_t scuart_word_len = 0;
    uint32_t scuart_stop_bit = 0;
    uint32_t scuart_parity = 0;

    /* Get base address of scuart register */
    SC_T *scuart_base = ((nu_scuart_t)serial)->scuart_base;

    /* Check baud rate */
    RT_ASSERT(cfg->baud_rate != 0);

    /* Check word len */
    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        scuart_word_len = SCUART_CHAR_LEN_5;
        break;

    case DATA_BITS_6:
        scuart_word_len = SCUART_CHAR_LEN_6;
        break;

    case DATA_BITS_7:
        scuart_word_len = SCUART_CHAR_LEN_7;
        break;

    case DATA_BITS_8:
        scuart_word_len = SCUART_CHAR_LEN_8;
        break;

    default:
        LOG_E("Unsupported data length");
        ret = RT_EINVAL;
        goto exit_nu_scuart_configure;
    }

    /* Check stop bit */
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        scuart_stop_bit = SCUART_STOP_BIT_1;
        break;

    case STOP_BITS_2:
        scuart_stop_bit = SCUART_STOP_BIT_2;
        break;

    default:
        LOG_E("Unsupported stop bit");
        ret = RT_EINVAL;
        goto exit_nu_scuart_configure;
    }

    /* Check parity */
    switch (cfg->parity)
    {
    case PARITY_NONE:
        scuart_parity = SCUART_PARITY_NONE;
        break;

    case PARITY_ODD:
        scuart_parity = SCUART_PARITY_ODD;
        break;

    case PARITY_EVEN:
        scuart_parity = SCUART_PARITY_EVEN;
        break;

    default:
        LOG_E("Unsupported parity");
        ret = RT_EINVAL;
        goto exit_nu_scuart_configure;
    }

    /* Reset this module */
    SYS_ResetModule(((nu_scuart_t)serial)->scuart_rst);

    /* Open SCUART and set SCUART baud rate */
    SCUART_Open(scuart_base, cfg->baud_rate);

    /* Set line configuration. */
    SCUART_SetLineConfig(scuart_base, 0, scuart_word_len, scuart_parity,
                         scuart_stop_bit);

    /* Enable NVIC interrupt. */
    NVIC_EnableIRQ(((nu_scuart_t)serial)->scuart_irq_n);

exit_nu_scuart_configure:

    if (ret != RT_EOK)
        SCUART_Close(scuart_base);

    return -(ret);
}

/**
 * SCUART interrupt control
 */
static rt_err_t nu_scuart_control(struct rt_serial_device *serial, int cmd,
                                  void *arg)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t flag;
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);

    /* Get base address of scuart register */
    SC_T *scuart_base = ((nu_scuart_t)serial)->scuart_base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Disable INT-RX */
        {
            flag = SC_INTEN_RDAIEN_Msk | SC_INTEN_RXTOIEN_Msk;
            SCUART_DISABLE_INT(scuart_base, flag);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Enable INT-RX */
        {
            flag = SC_INTEN_RDAIEN_Msk | SC_INTEN_RXTOIEN_Msk;
            SCUART_ENABLE_INT(scuart_base, flag);
        }
        break;

    case RT_DEVICE_CTRL_CLOSE:
        /* Disable NVIC interrupt. */
        NVIC_DisableIRQ(((nu_scuart_t)serial)->scuart_irq_n);

        /* Reset this module */
        SYS_ResetModule(((nu_scuart_t)serial)->scuart_rst);

        /* Close SCUART port */
        SCUART_Close(scuart_base);

        break;

    default:
        result = -RT_EINVAL;
        break;
    }
    return result;
}

/**
 * SCUART put char
 */
static int nu_scuart_send(struct rt_serial_device *serial, char c)
{
    RT_ASSERT(serial != RT_NULL);

    /* Get base address of scuart register */
    SC_T *scuart_base = ((nu_scuart_t)serial)->scuart_base;

    /* Waiting if TX-FIFO is full. */
    while (SCUART_IS_TX_FULL(scuart_base))
        ;

    /* Put char into TX-FIFO */
    SCUART_WRITE(scuart_base, c);

    return 1;
}

/**
 * SCUART get char
 */
static int nu_scuart_receive(struct rt_serial_device *serial)
{
    RT_ASSERT(serial != RT_NULL);

    /* Get base address of scuart register */
    SC_T *scuart_base = ((nu_scuart_t)serial)->scuart_base;

    /* Return failure if RX-FIFO is empty. */
    if (SCUART_GET_RX_EMPTY(scuart_base))
    {
        return -1;
    }

    /* Get char from RX-FIFO */
    return SCUART_READ(scuart_base);
}

/**
 * Hardware SCUART Initialization
 */
static int rt_hw_scuart_init(void)
{
    int i;
    rt_uint32_t flag;
    rt_err_t ret = RT_EOK;

    for (i = (SCUART_START + 1); i < SCUART_CNT; i++)
    {
        flag = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

        nu_scuart_arr[i].dev.ops = &nu_scuart_ops;
        nu_scuart_arr[i].dev.config = nu_scuart_default_config;

        ret = rt_hw_serial_register(&nu_scuart_arr[i].dev, nu_scuart_arr[i].name,
                                    flag, NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_scuart_init);
#endif //#if defined(BSP_USING_SCUART)
