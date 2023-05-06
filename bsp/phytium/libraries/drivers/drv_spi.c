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
#include <rtthread.h>
#include <rtdevice.h>
#include "interrupt.h"

#include <string.h>
#include "fdebug.h"

#if defined(TARGET_E2000)
#include "fparameters.h"
#endif

#include "fcpu_info.h"
#include "fkernel.h"
#include "ftypes.h"
#include "fsleep.h"

#ifdef RT_USING_SPI

#include <dfs_file.h>

#include "fspim.h"
#include "fspim_hw.h" /* include low-level header file for internal probe */
#include "drv_spi.h"
/************************** Constant Definitions *****************************/
/**************************** Type Definitions *******************************/
/************************** Variable Definitions *****************************/
#ifdef RT_USING_SPIM0
    static struct drv_spi _RTSpim0;
#endif

#ifdef RT_USING_SPIM1
    static struct drv_spi _RTSpim1;
#endif

#ifdef RT_USING_SPIM2
    static struct drv_spi _RTSpim2;
#endif

#ifdef RT_USING_SPIM3
    static struct drv_spi _RTSpim3;
#endif

static struct rt_spi_device *spi_device = RT_NULL;
static struct rt_event rx_done_event;
/***************** Macros (Inline Functions) Definitions *********************/
#define FSPIM_DEBUG_TAG "SPIM"
#define FSPIM_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_WARN(format, ...)   FT_DEBUG_PRINT_W(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_INFO(format, ...)    FT_DEBUG_PRINT_I(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)

#define EVENT_RX_DONE (1 << 1)
/*******************************Api Functions*********************************/
static rt_err_t spim_configure(struct rt_spi_device* device, struct rt_spi_configuration* configuration);
static rt_uint32_t spim_xfer(struct rt_spi_device* device, struct rt_spi_message* message);

static FError FSpimSetupInterrupt(FSpim *instance_p)
{
    FASSERT(instance_p);
    FSpimConfig *config_p = &instance_p->config;
    uintptr base_addr = config_p->base_addr;
    u32 cpu_id = 0;

    GetCpuId(&cpu_id);
    FSPIM_DEBUG("cpu_id is %d, irq_num is %d\n", cpu_id, config_p->irq_num);
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
    struct drv_spi *user_data_cfg = device->parent.user_data;
    FSpimConfig input_cfg = *FSpimLookupConfig(user_data_cfg->spi_id);
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
        return RT_ERROR;

    /* irq setting */
    ret = FSpimSetupInterrupt(&user_data_cfg->spim_instance);
    if (FSPIM_SUCCESS != ret)
        return RT_ERROR;
    FSpimRegisterIntrruptHandler(&user_data_cfg->spim_instance, FSPIM_INTR_EVT_RX_DONE, rt_ft_send_event_done, NULL);

    return ret;
}

static rt_uint32_t spim_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);
    rt_size_t message_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;

    /* recv spi_cfg from RT-Thread sys */
    struct drv_spi *user_data_xfer = device->parent.user_data;
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

int ft_spi_init(void)
{
    rt_err_t result;
    static struct rt_spi_bus spim_bus;

    /* event creat */
    if (RT_EOK != rt_event_init(&rx_done_event, "rx_done_event", RT_IPC_FLAG_FIFO))
    {
        rt_kprintf("Create event failed.\n");
        return RT_ERROR;
    }

    /* spi bus init */
    result = rt_spi_bus_register(&spim_bus, "spi0", &spim_ops);
    RT_ASSERT((struct rt_spi_device *)rt_device_find("spi0"));
    rt_kprintf("Spi bus spi0 init\n");

    /* spi device init and attach to bus */
    #ifdef RT_USING_SPIM0
        _RTSpim0.spi_id = FSPI0_ID;
        result = rt_spi_bus_attach_device(&_RTSpim0.device, "spi00", "spi0", &_RTSpim0);
        spi_device = (struct rt_spi_device *)rt_device_find("spi00");
        if (RT_NULL == spi_device)
        {
            rt_kprintf("Spi init failed -> can't find spi00 device!\n");
            return RT_ERROR;
        }
        rt_kprintf("Spi master device spi00 init.\n");
    #endif

    #ifdef RT_USING_SPIM1
        _RTSpim1.spi_id = FSPI1_ID;
        result = rt_spi_bus_attach_device(&_RTSpim1.device, "spi01", "spi0", &_RTSpim1);
        spi_device = (struct rt_spi_device *)rt_device_find("spi01");
        if (RT_NULL == spi_device)
        {
            rt_kprintf("Spi init failed -> can't find spi01 device!\n");
            return RT_ERROR;
        }
        rt_kprintf("Spi master device spi01 init.\n");
    #endif

    #ifdef RT_USING_SPIM2
        _RTSpim2.spi_id = FSPI2_ID;
        result = rt_spi_bus_attach_device(&_RTSpim2.device, "spi02", "spi0", &_RTSpim2);
        spi_device = (struct rt_spi_device *)rt_device_find("spi02");
        if (RT_NULL == spi_device)
        {
            rt_kprintf("Spi init failed -> can't find spi02 device!\n");
            return RT_ERROR;
        }
        rt_kprintf("Spi master device spi02 init.\n");
    #endif

    #ifdef RT_USING_SPIM3
        _RTSpim3.spi_id = FSPI3_ID;
        result = rt_spi_bus_attach_device(&_RTSpim3.device, "spi03", "spi0", &_RTSpim3);
        spi_device = (struct rt_spi_device *)rt_device_find("spi03");
        if (RT_NULL == spi_device)
        {
            rt_kprintf("Spi init failed -> can't find spi03 device!\n");
            return RT_ERROR;
        }
        rt_kprintf("Spi master device spi03 init.\n");
    #endif


    return result;
}
INIT_DEVICE_EXPORT(ft_spi_init);

/* spi test example */
static void fspim_test_sample(int argc, char *argv[])
{
    rt_uint8_t send_to_flash_id = 0x9f; /* Flash cmd */
    rt_uint8_t recv_from_falsh_id1[5] = {0};
    rt_uint8_t recv_from_falsh_id2[5] = {0};

    /* find the spi device to get the device handle */
    spi_device = (struct rt_spi_device *)rt_device_find("spi02");
    if (!spi_device)
    {
        rt_kprintf("fspim_test_sample run failed! can't find spi02 device!\n");
    }
    else
    {
        static struct rt_spi_message msg1, msg2;

        msg1.send_buf   = &send_to_flash_id;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = &msg2;

        msg2.send_buf   = RT_NULL;
        msg2.recv_buf   = recv_from_falsh_id2;
        msg2.length     = 5;
        msg2.cs_take    = 0;
        msg2.cs_release = 1;
        msg2.next       = RT_NULL;

        /* send the command to read the ID using rt_spi_send_then_recv() */
        rt_spi_send_then_recv(spi_device, &send_to_flash_id, 1, recv_from_falsh_id1, 5);
        rt_kprintf("use rt_spi_send_then_recv() read flash ID is:0x%x 0x%x 0x%x 0x%x 0x%x\n", recv_from_falsh_id1[0], recv_from_falsh_id1[1], recv_from_falsh_id1[2], recv_from_falsh_id1[3], recv_from_falsh_id1[4]);

        /* send the command to read the ID using rt_spi_transfer_message() */
        rt_spi_transfer_message(spi_device, &msg1);
        rt_kprintf("use rt_spi_transfer_message() read flash ID is:0x%x 0x%x 0x%x 0x%x 0x%x\n", recv_from_falsh_id2[0], recv_from_falsh_id2[1], recv_from_falsh_id2[2], recv_from_falsh_id2[3], recv_from_falsh_id2[4]);
    }
}
MSH_CMD_EXPORT(fspim_test_sample, "fspim test sample");
#endif
