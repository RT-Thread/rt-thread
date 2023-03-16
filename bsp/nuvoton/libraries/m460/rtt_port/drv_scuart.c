/**************************************************************************//**
 *
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date            Author       Notes
 * 2022-3-16       Wayne        First version
 *
 ******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_SCUART)

#include "NuMicro.h"
#include <rtdevice.h>
#include <rthw.h>
#include <drv_sys.h>

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
    SC_T *base;
    IRQn_Type irqn;
    uint32_t rstidx;
    uint32_t modid;
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
static void nu_scuart_isr(nu_scuart_t psNuSCUart);

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
        .name = "scuart0", .base = SC0, .irqn = SC0_IRQn, .rstidx = SC0_RST, .modid = SC0_MODULE,
    },
#endif
#if defined(BSP_USING_SCUART1)
    {
        .name = "scuart1", .base = SC1, .irqn = SC1_IRQn, .rstidx = SC1_RST, .modid = SC1_MODULE,
    },
#endif
#if defined(BSP_USING_SCUART2)
    {
        .name = "scuart2", .base = SC2, .irqn = SC2_IRQn, .rstidx = SC2_RST, .modid = SC2_MODULE,
    },
#endif
}; /* scuart nu_scuart */

#if defined(BSP_USING_SCUART0)
void SC0_IRQHandler(void)
{
    rt_interrupt_enter();

    nu_scuart_isr((void *)&nu_scuart_arr[SCUART0_IDX]);

    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SCUART1)
void SC1_IRQHandler(void)
{
    rt_interrupt_enter();

    nu_scuart_isr((void *)&nu_scuart_arr[SCUART1_IDX]);

    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SCUART2)
void SC2_IRQHandler(void)
{
    rt_interrupt_enter();

    nu_scuart_isr((void *)&nu_scuart_arr[SCUART2_IDX]);

    rt_interrupt_leave();
}
#endif

/**
 * All SCUART interrupt service routine
 */
static void nu_scuart_isr(nu_scuart_t psNuSCUart)
{
    /* Handle RX event */
    if (SCUART_GET_INT_FLAG(psNuSCUart->base, SC_INTSTS_RXTOIF_Msk) ||
            SCUART_GET_INT_FLAG(psNuSCUart->base, SC_INTSTS_RDAIF_Msk))
    {
        rt_hw_serial_isr(&psNuSCUart->dev, RT_SERIAL_EVENT_RX_IND);

        // RDA is the only interrupt enabled in this driver, this status bit
        // automatically cleared after Rx FIFO empty. So no need to clear interrupt
        // status here.
        SCUART_CLR_INT_FLAG(psNuSCUart->base, SC_INTSTS_RXTOIF_Msk);
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
    nu_scuart_t psNuSCUart = (nu_scuart_t)serial;
    RT_ASSERT(psNuSCUart != RT_NULL);

    /* Check baud rate */    RT_ASSERT(cfg->baud_rate != 0);

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
        LOG_E("Unsupported data length\n");
        ret = -RT_EINVAL;
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
        LOG_E("Unsupported stop bit\n");
        ret = -RT_EINVAL;
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
        LOG_E("Unsupported parity\n");
        ret = -RT_EINVAL;
        goto exit_nu_scuart_configure;
    }

    SYS_ResetModule(psNuSCUart->rstidx);

    /* Open SCUART and set SCUART baud rate */
    SCUART_Open(psNuSCUart->base, cfg->baud_rate);

    /* Set line configuration. */
    SCUART_SetLineConfig(psNuSCUart->base, 0, scuart_word_len, scuart_parity,
                         scuart_stop_bit);

    /* Enable interrupt. */
    NVIC_EnableIRQ(psNuSCUart->irqn);

exit_nu_scuart_configure:

    if (ret != RT_EOK)
        SCUART_Close(psNuSCUart->base);

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
    nu_scuart_t psNuSCUart = (nu_scuart_t)serial;
    RT_ASSERT(psNuSCUart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:

        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Disable INT-RX */
        {
            flag = SC_INTEN_RDAIEN_Msk | SC_INTEN_RXTOIEN_Msk;
            SCUART_DISABLE_INT(psNuSCUart->base, flag);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:

        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX) /* Enable INT-RX */
        {
            flag = SC_INTEN_RDAIEN_Msk | SC_INTEN_RXTOIEN_Msk;
            SCUART_ENABLE_INT(psNuSCUart->base, flag);
        }
        break;

    case RT_DEVICE_CTRL_CLOSE:

        /* Disable interrupt. */
        NVIC_DisableIRQ(psNuSCUart->irqn);

        /* Close SCUART port */
        SCUART_Close(psNuSCUart->base);

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
    nu_scuart_t psNuSCUart = (nu_scuart_t)serial;
    RT_ASSERT(psNuSCUart != RT_NULL);

    /* Waiting if TX-FIFO is full. */
    while (SCUART_IS_TX_FULL(psNuSCUart->base)) ;

    /* Put char into TX-FIFO */
    SCUART_WRITE(psNuSCUart->base, c);

    return 1;
}

/**
 * SCUART get char
 */
static int nu_scuart_receive(struct rt_serial_device *serial)
{
    nu_scuart_t psNuSCUart = (nu_scuart_t)serial;
    RT_ASSERT(psNuSCUart != RT_NULL);

    /* Return failure if RX-FIFO is empty. */
    if (SCUART_GET_RX_EMPTY(psNuSCUart->base))
    {
        return -1;
    }

    /* Get char from RX-FIFO */
    return SCUART_READ(psNuSCUart->base);
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

        CLK_EnableModuleClock(nu_scuart_arr[i].modid);
        SYS_ResetModule(nu_scuart_arr[i].rstidx);

        ret = rt_hw_serial_register(&nu_scuart_arr[i].dev, nu_scuart_arr[i].name, flag, NULL);
        RT_ASSERT(ret == RT_EOK);
    }

    return (int)ret;
}
INIT_DEVICE_EXPORT(rt_hw_scuart_init);
#endif //#if defined(BSP_USING_SCUART)
