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
#include "rtconfig.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "interrupt.h"
#define LOG_TAG  "spi_msg_drv"
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
#include "fspim_msg.h"
#include "fspim_msg_hw.h" /* include low-level header file for internal probe */
#include "drv_spi_msg.h"
/************************** Constant Definitions *****************************/
/**************************** Type Definitions *******************************/
/************************** Variable Definitions *****************************/
typedef struct
{
    struct rt_spi_bus spi_bus;
    FSpiMsgCtrl spim_msg_instance;
    const char *name;
} phytium_spi_bus;
/***************** Macros (Inline Functions) Definitions *********************/
#define EVENT_RX_DONE (1 << 1)
/*******************************Api Functions*********************************/
static rt_err_t spim_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_ssize_t spim_xfer(struct rt_spi_device *device, struct rt_spi_message *message);

static const struct rt_spi_ops spim_ops =
{
    .configure = spim_configure,
    .xfer = spim_xfer
};

static rt_err_t spim_configure(struct rt_spi_device *device,
                               struct rt_spi_configuration *configuration)
{
    FError ret = 0;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);
    phytium_spi_bus *user_data_cfg = device->parent.user_data;
    FSpiMsgConfig *set_input_cfg = &user_data_cfg->spim_msg_instance.spi_msg_config;

    /* set fspim device according to configuration */
    /* Modifying the CPOL and CPHA parameters requires support from relevant documentation*/
    if (configuration->data_width == 8)
    {
        set_input_cfg->n_bytes = FSPIM_1_BYTE;
    }

    /* send spi_cfg to RT-Thread sys */
    ret = FSpiMsgCfgInitialize(&user_data_cfg->spim_msg_instance, set_input_cfg);
    if (0 != ret)
    {
        return -RT_ERROR;
    }

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
    FSpiMsgCtrl *xfer_spim_msg_instance = &user_data_xfer->spim_msg_instance;

    FError tx_rx_result = 0;
    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;

    if (message->cs_take)
    {
        FSpiMsgSetChipSelection(xfer_spim_msg_instance, 1);
    }

    if (message_length > 0)
    {
        if (send_buf == RT_NULL && recv_buf != RT_NULL)
        {
            /* receive message */
            tx_rx_result = FSpiMsgTransfer(xfer_spim_msg_instance, RT_NULL, recv_buf, message_length);
        }
        else if (send_buf != RT_NULL && recv_buf == RT_NULL)
        {
            /* send message */
            tx_rx_result = FSpiMsgTransfer(xfer_spim_msg_instance, send_buf, RT_NULL, message_length);
        }
        else if (send_buf != RT_NULL && recv_buf != RT_NULL)
        {
            /* send and recv */
            tx_rx_result = FSpiMsgTransfer(xfer_spim_msg_instance, send_buf, recv_buf, message_length);
        }
    }

    if (0 != tx_rx_result)
    {
        rt_kprintf("FSpimTransferByInterrupt() fail!!!");
        message_length = 0;
    }

    if (message->cs_release)
    {
        FSpiMsgSetChipSelection(xfer_spim_msg_instance, 0);
    }

    return message_length;
}

static void FSpiMsgIntrInit(FSpiMsgCtrl *ctrl, const FSpiMsgConfig *config)
{
    rt_uint32_t cpu_id = rt_hw_cpu_id();
    rt_hw_interrupt_set_target_cpus(config->irq_num, cpu_id);
    rt_hw_interrupt_set_priority(config->irq_num, config->irq_priority);

    ctrl->cmd_completion = CMD_MSG_NOT_COMPLETION;

    rt_hw_interrupt_install(config->irq_num, FSpiMsgInterruptHandler, ctrl, NULL);
    rt_hw_interrupt_umask(config->irq_num);
}

static int spi_init(phytium_spi_bus *spi_bus)
{
    FError ret = 0;
    FSpiMsgConfig input_cfg = *FSpiMsgLookupConfig(spi_bus->spim_msg_instance.spi_msg_config.instance_id);
#ifdef RT_USING_SMART
    input_cfg.spi_msg.regfile = (uintptr)rt_ioremap((void *)input_cfg.spi_msg.regfile, 0x1000);
    input_cfg.spi_msg.shmem = (uintptr)rt_ioremap((void *)input_cfg.spi_msg.shmem, 0x1000);
#endif

    FSpiMsgIntrInit(&spi_bus->spim_msg_instance, &input_cfg);

    /* send spi_cfg to RT-Thread sys */
    ret = FSpiMsgCfgInitialize(&spi_bus->spim_msg_instance, &input_cfg);
    if (0 != ret)
    {
        return -RT_ERROR;
    }

    rt_spi_bus_register(&spi_bus->spi_bus, spi_bus->name, &spim_ops);
    RT_ASSERT((struct rt_spi_device *)rt_device_find(spi_bus->name));

    return 0;
}

#ifdef RT_USING_SPIM0_MSG
    static phytium_spi_bus spi0_bus;
#endif
#ifdef RT_USING_SPIM1_MSG
    static phytium_spi_bus spi1_bus;
#endif
#ifdef RT_USING_SPIM2_MSG
    static phytium_spi_bus spi2_bus;
#endif
#ifdef RT_USING_SPIM3_MSG
    static phytium_spi_bus spi3_bus;
#endif

int rt_hw_spi_init(void)
{
#ifdef RT_USING_SPIM0_MSG
    spi0_bus.name = "SPI0";
    spi0_bus.spim_msg_instance.spi_msg_config.instance_id = FSPI0_MSG_ID;
    FIOPadSetSpimMux(FSPI0_MSG_ID);
    spi_init(&spi0_bus);
#endif
#ifdef RT_USING_SPIM1_MSG
    spi1_bus.name = "SPI1";
    spi1_bus.spim_msg_instance.spi_msg_config.instance_id = FSPI1_MSG_ID;
    FIOPadSetSpimMux(FSPI1_MSG_ID);
    spi_init(&spi1_bus);
#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);