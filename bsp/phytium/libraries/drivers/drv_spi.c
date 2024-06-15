/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-11-10  liqiaozhong  first commit
 * 2023-03-08  liqiaozhong  support 4 spis and qspi working together
 *
 */
#include"rtconfig.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "interrupt.h"
#define LOG_TAG      "spi_drv"
#include "drv_log.h"
#include <string.h>
#include "fparameters.h"
#include "fcpu_info.h"
#include "fkernel.h"
#include "ftypes.h"
#ifdef RT_USING_SMART
    #include <ioremap.h>
#endif

#include <dfs_file.h>
#include "fspim.h"
#include "fspim_hw.h" /* include low-level header file for internal probe */
#include "drv_spi.h"
/************************** Constant Definitions *****************************/
/**************************** Type Definitions *******************************/
/************************** Variable Definitions *****************************/

typedef struct
{
    struct rt_spi_bus spi_bus;
    FSpim spim_instance;
    const char *name;
} phytium_spi_bus;

static struct rt_event rx_done_event;
/***************** Macros (Inline Functions) Definitions *********************/

#define EVENT_RX_DONE (1 << 1)
/*******************************Api Functions*********************************/
static rt_err_t spim_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_ssize_t spim_xfer(struct rt_spi_device *device, struct rt_spi_message *message);

static FError FSpimSetupInterrupt(FSpim *instance_p)
{
    FASSERT(instance_p);
    FSpimConfig *config_p = &instance_p->config;
    uintptr base_addr = config_p->base_addr;
    rt_uint32_t cpu_id = rt_hw_cpu_id();

    LOG_D("cpu_id is %d, irq_num is %d\n", cpu_id, config_p->irq_num);
    config_p->irq_prority = 0xd0;
    rt_hw_interrupt_set_target_cpus(config_p->irq_num, cpu_id);
    rt_hw_interrupt_set_priority(config_p->irq_num, config_p->irq_prority);

    /* register intr callback */
    rt_hw_interrupt_install(config_p->irq_num,
                            FSpimInterruptHandler,
                            instance_p,
                            NULL);

    /* enable tx fifo overflow / rx overflow / rx full */
    FSpimMaskIrq(base_addr, FSPIM_IMR_ALL_BITS);

    /* enable irq */
    rt_hw_interrupt_umask(config_p->irq_num);

    return FSPIM_SUCCESS;
}

static void rt_ft_send_event_done(void *instance_p, void *param)
{
    FASSERT(instance_p);
    rt_event_send(&rx_done_event, EVENT_RX_DONE);
    return;
}

static const struct rt_spi_ops spim_ops =
{
    .configure = spim_configure,
    .xfer = spim_xfer
};

static rt_err_t spim_configure(struct rt_spi_device *device,
                               struct rt_spi_configuration *configuration)
{
    FError ret = FSPIM_SUCCESS;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);
    phytium_spi_bus *user_data_cfg = device->parent.user_data;
    FSpimConfig input_cfg = *FSpimLookupConfig(user_data_cfg->spim_instance.config.instance_id);
#ifdef RT_USING_SMART
    input_cfg.base_addr = (uintptr)rt_ioremap((void *)input_cfg.base_addr, 0x1000);
#endif
    FSpimConfig *set_input_cfg = &input_cfg;

    /* set fspim device according to configuration */
    if (configuration->mode & RT_SPI_CPOL)
    {
        set_input_cfg->cpol = FSPIM_CPOL_HIGH;
    }
    else
    {
        set_input_cfg->cpol = FSPIM_CPOL_LOW;
    }
    if (configuration->mode & RT_SPI_CPHA)
    {
        set_input_cfg->cpha = FSPIM_CPHA_2_EDGE;
    }
    else
    {
        set_input_cfg->cpha = FSPIM_CPHA_1_EDGE;
    }

    if (configuration->data_width == 8)
    {
        set_input_cfg->n_bytes = FSPIM_1_BYTE;
    }
    else if (configuration->data_width == 16)
    {
        set_input_cfg->n_bytes = FSPIM_2_BYTE;
    }

    /* send spi_cfg to RT-Thread sys */
    ret = FSpimCfgInitialize(&user_data_cfg->spim_instance, &input_cfg);
    if (FSPIM_SUCCESS != ret)
    {
        return -RT_ERROR;
    }

    /* irq setting */
    ret = FSpimSetupInterrupt(&user_data_cfg->spim_instance);
    if (FSPIM_SUCCESS != ret)
    {
        return -RT_ERROR;
    }
    FSpimRegisterIntrruptHandler(&user_data_cfg->spim_instance, FSPIM_INTR_EVT_RX_DONE, rt_ft_send_event_done, NULL);

    return ret;
}

static rt_ssize_t spim_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);
    rt_ssize_t message_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;

    /* recv spi_cfg from RT-Thread sys */
    phytium_spi_bus *user_data_xfer = device->parent.user_data;
    FSpim *xfer_spim_instance = &user_data_xfer->spim_instance;

    FError tx_rx_result = FSPIM_SUCCESS;
    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;

    if (message->cs_take)
    {
        FSpimSetChipSelection(xfer_spim_instance, TRUE);
    }

    if (message_length > 0)
    {
        if (send_buf == RT_NULL && recv_buf != RT_NULL)
        {
            /* receive message */
            tx_rx_result = FSpimTransferByInterrupt(xfer_spim_instance, RT_NULL, recv_buf, message_length);
        }
        else if (send_buf != RT_NULL && recv_buf == RT_NULL)
        {
            /* send message */
            tx_rx_result = FSpimTransferByInterrupt(xfer_spim_instance, send_buf, RT_NULL, message_length);
        }
        else if (send_buf != RT_NULL && recv_buf != RT_NULL)
        {
            /* not supported yet */
            rt_kprintf("Do not support the situation that send_buf and recv_buf both not equal to 0.");
        }
    }

    if (FSPIM_SUCCESS != tx_rx_result)
    {
        rt_kprintf("FSpimTransferByInterrupt() fail!!!");
        message_length = 0;
    }

    if (rt_event_recv(&rx_done_event, (EVENT_RX_DONE),
                      (RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR),
                      RT_WAITING_FOREVER, RT_NULL) != RT_EOK)
    {
        rt_kprintf("Wait rx timeout!!!\n");
        message_length = 0;
    }

    if (message->cs_release)
    {
        FSpimSetChipSelection(xfer_spim_instance, FALSE);
    }

    return message_length;
}

static int spi_init(phytium_spi_bus *phytium_spi)
{
    rt_spi_bus_register(&phytium_spi->spi_bus, phytium_spi->name, &spim_ops);
    RT_ASSERT((struct rt_spi_device *)rt_device_find(phytium_spi->name));

    return 0;
}

#ifdef RT_USING_SPIM0
    static phytium_spi_bus spi0_bus;
#endif
#ifdef RT_USING_SPIM1
    static phytium_spi_bus spi1_bus;
#endif
#ifdef RT_USING_SPIM2
    static phytium_spi_bus spi2_bus;
#endif
#ifdef RT_USING_SPIM3
    static phytium_spi_bus spi3_bus;
#endif

int rt_hw_spi_init(void)
{
    /* event creat */
    if (RT_EOK != rt_event_init(&rx_done_event, "rx_done_event", RT_IPC_FLAG_FIFO))
    {
        rt_kprintf("Create event failed.\n");
        return -RT_ERROR;
    }
#ifdef RT_USING_SPIM0
    spi0_bus.name = "SPI0";
    spi0_bus.spim_instance.config.instance_id = FSPI0_ID;
    spi_init(&spi0_bus);
#endif
#ifdef RT_USING_SPIM1
    spi1_bus.name = "SPI1";
    spi1_bus.spim_instance.config.instance_id = FSPI1_ID;
    spi_init(&spi1_bus);
#endif
#ifdef RT_USING_SPIM2
    spi2_bus.name = "SPI2";
    spi2_bus.spim_instance.config.instance_id = FSPI2_ID;
    spi_init(&spi2_bus);
#endif
#ifdef RT_USING_SPIM3
    spi3_bus.name = "SPI3";
    spi3_bus.spim_instance.config.instance_id = FSPI3_ID;
    spi_init(&spi3_bus);
#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);
