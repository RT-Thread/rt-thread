/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-20     zhangyan     first version
 *
 */

#include "drv_can.h"
#include "sdkconfig.h"

#ifdef RT_USING_CAN
#include "fdebug.h"
#include "fpinctrl.h"

#define FCAN_TEST_DEBUG_TAG "FCAN_TEST"
#define FCAN_TEST_DEBUG(format, ...) FT_DEBUG_PRINT_D(FCAN_TEST_DEBUG_TAG, format, ##__VA_ARGS__)
#define FCAN_TEST_INFO(format, ...) FT_DEBUG_PRINT_I(FCAN_TEST_DEBUG_TAG, format, ##__VA_ARGS__)
#define FCAN_TEST_WARN(format, ...) FT_DEBUG_PRINT_W(FCAN_TEST_DEBUG_TAG, format, ##__VA_ARGS__)
#define FCAN_TEST_ERROR(format, ...) FT_DEBUG_PRINT_E(FCAN_TEST_DEBUG_TAG, format, ##__VA_ARGS__)

struct phytium_can
{
    const char *name;
    FCanCtrl can_handle;
    FCanIdMaskConfig filter;
    struct rt_can_device device; /* inherit from can device */
};

static struct phytium_can drv_can[FCAN_NUM] =
{
{
    .name = "CAN0",
    .can_handle.config.instance_id = 0,
},
{
    .name = "CAN1",
    .can_handle.config.instance_id = 1,
},
#if defined(CONFIG_TARGET_F2000_4) || defined(CONFIG_TARGET_D2000)
{
    .name = "CAN2",
    .can_handle.config.instance_id = 2,
},
#endif
};

static void CanRxIrqCallback(void *args)
{
    FCanCtrl *instance_p = (FCanCtrl *)args;
    rt_hw_can_isr(&drv_can[instance_p->config.instance_id].device, RT_CAN_EVENT_RX_IND);
    FCAN_TEST_DEBUG("CAN%d irq recv frame callback.", instance_p->config.instance_id);
}

static void CanErrorCallback(void *args)
{
    FCanCtrl *instance_p = (FCanCtrl *)args;
    uintptr base_addr = instance_p->config.base_address;
    FCAN_TEST_DEBUG("CAN %d is under error.", instance_p->config.instance_id);
    FCAN_TEST_DEBUG("error_status is %x.", FCAN_READ_REG32(base_addr, FCAN_INTR_OFFSET));
    FCAN_TEST_DEBUG("rxerr_cnt is %x.", FCAN_ERR_CNT_RFN_GET(FCAN_READ_REG32(base_addr, FCAN_ERR_CNT_OFFSET)));
    FCAN_TEST_DEBUG("txerr_cnt is %x.", FCAN_ERR_CNT_TFN_GET(FCAN_READ_REG32(base_addr, FCAN_ERR_CNT_OFFSET)));
}

static void CanTxIrqCallback(void *args)
{
    FCanCtrl *instance_p = (FCanCtrl *)args;
    rt_hw_can_isr(&drv_can[instance_p->config.instance_id].device, RT_CAN_EVENT_TX_DONE);
    FCAN_TEST_DEBUG("CAN%d irq send frame callback.", instance_p->config.instance_id);
}

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    RT_ASSERT(can);
    RT_ASSERT(cfg);
    struct phytium_can *drv_can;
    drv_can = (struct phytium_can *)can->parent.user_data;
    RT_ASSERT(drv_can);
    FError status = FT_SUCCESS;
    rt_kprintf("CAN%d begin to config.\n", drv_can->can_handle.config.instance_id);

#if defined(CONFIG_TARGET_F2000_4) || defined(CONFIG_TARGET_D2000)
    if(drv_can->can_handle.config.instance_id == FCAN_INSTANCE_0)
    {
        FPinSetFunc(FIOCTRL_TJTAG_TDI_PAD, FPIN_FUNC1); /* can0-tx: func 1 */
        FPinSetFunc(FIOCTRL_SWDITMS_SWJ_PAD, FPIN_FUNC1); /* can0-rx: func 1 */
    }
    else if(drv_can->can_handle.config.instance_id == FCAN_INSTANCE_1)
    {
        FPinSetFunc(FIOCTRL_NTRST_SWJ_PAD, FPIN_FUNC1); /* can1-tx: func 1 */
        FPinSetFunc(FIOCTRL_SWDO_SWJ_PAD, FPIN_FUNC1); /* can1-rx: func 1 */
    }
    else
    {
        FCAN_TEST_ERROR("CAN id is under error.");
        return RT_ERROR;
    }
#elif defined(CONFIG_TARGET_E2000)
    FIOPadSetCanMux(drv_can->can_handle.config.instance_id);
#endif

    /*CAN config init*/
    status = FCanCfgInitialize(&(drv_can->can_handle), FCanLookupConfig(drv_can->can_handle.config.instance_id));
    if (status != FT_SUCCESS)
    {
        FCAN_TEST_DEBUG("CAN %d initialize error, status = %#x.", drv_can->can_handle.config.instance_id, status);
        return RT_ERROR;
    }

    /*Set the baudrate*/
    FCanBaudrateConfig arb_segment_config;
    FCanBaudrateConfig data_segment_config;
    memset(&arb_segment_config, 0, sizeof(arb_segment_config));
    memset(&data_segment_config, 0, sizeof(data_segment_config));
#if defined(RT_CAN_USING_CANFD)
    arb_segment_config.auto_calc = TRUE;
    arb_segment_config.baudrate = CAN1MBaud; /*CANFD arb baud defaults to 1M ,allowed to be modified*/
    arb_segment_config.segment = FCAN_ARB_SEGMENT;
    status = FCanBaudrateSet(&(drv_can->can_handle), &arb_segment_config);
    if (status != RT_EOK)
    {
        FCAN_TEST_DEBUG("CAN%d set arb segment baudrate failed.", drv_can->can_handle.config.instance_id);
        return RT_ERROR;
    }
    data_segment_config.auto_calc = TRUE;
    data_segment_config.baudrate = cfg->baud_rate_fd;
    data_segment_config.segment = FCAN_DATA_SEGMENT;
    status = FCanBaudrateSet(&(drv_can->can_handle), &data_segment_config);
    if (status != RT_EOK)
    {
        FCAN_TEST_DEBUG("CAN%d set data segment baudrate failed.", drv_can->can_handle.config.instance_id);
        return RT_ERROR;
    }
#else
    arb_segment_config.auto_calc = TRUE;
    arb_segment_config.baudrate = cfg->baud_rate;
    arb_segment_config.segment = FCAN_ARB_SEGMENT;
    status = FCanBaudrateSet(&(drv_can->can_handle), &arb_segment_config);
    if (status != FT_SUCCESS)
    {
        FCAN_TEST_DEBUG("CAN%d set arb segment baudrate failed.", drv_can->can_handle.config.instance_id);
        return RT_ERROR;
    }
    data_segment_config.auto_calc = TRUE;
    data_segment_config.baudrate = cfg->baud_rate;
    data_segment_config.segment = FCAN_DATA_SEGMENT;
    status = FCanBaudrateSet(&(drv_can->can_handle), &data_segment_config);
    if (status != FT_SUCCESS)
    {
        FCAN_TEST_DEBUG("CAN%d set data segment baudrate failed.", drv_can->can_handle.config.instance_id);
        return RT_ERROR;
    }
#endif

    /*CAN filter function init*/
    for (int i = 0; i < FCAN_ACC_ID_REG_NUM; i++)
    {
        drv_can->filter.filter_index = i;
        drv_can->filter.id = 0;
        drv_can->filter.mask = FCAN_ACC_IDN_MASK;
        status |= FCanIdMaskFilterSet(&(drv_can->can_handle), &(drv_can->filter));
    }
    if (status != FT_SUCCESS)
    {
        FCAN_TEST_ERROR("CAN%d set mask filter failed.", drv_can->can_handle.config.instance_id);
        return RT_ERROR;
    }
    /* Identifier mask enable */
    FCanIdMaskFilterEnable(&(drv_can->can_handle));
    /* Transmit mode init , the default setting is normal mode */
    FCanSetMode(&(drv_can->can_handle), FCAN_PROBE_NORMAL_MODE);
    /* enable can transfer */
    FCanEnable(&(drv_can->can_handle), RT_TRUE);

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    RT_ASSERT(can);
    rt_uint32_t argval;
    struct phytium_can *drv_can;
    drv_can = (struct phytium_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);
    rt_uint32_t cpu_id;
    FCanIntrEventConfig intr_event;
    FError status = FT_SUCCESS;

#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_config *filter_cfg;
#endif

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
        GetCpuId(&cpu_id);
        rt_hw_interrupt_set_target_cpus(drv_can->can_handle.config.irq_num, cpu_id);
        argval = (rt_uint32_t) arg;
        /*Open different interrupts*/
        if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            intr_event.type = FCAN_INTR_EVENT_ERROR;
            intr_event.handler = CanErrorCallback;
            intr_event.param = (void *)(&(drv_can->can_handle));
            FCanRegisterInterruptHandler(&(drv_can->can_handle), &intr_event);
            FCanInterruptEnable(&(drv_can->can_handle), intr_event.type);
        }
        if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            intr_event.type = FCAN_INTR_EVENT_SEND;
            intr_event.handler = CanTxIrqCallback;
            intr_event.param = (void *)(&(drv_can->can_handle));
            FCanRegisterInterruptHandler(&(drv_can->can_handle), &intr_event);
            FCanInterruptEnable(&(drv_can->can_handle), intr_event.type);
        }
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            intr_event.type = FCAN_INTR_EVENT_RECV;
            intr_event.handler = CanRxIrqCallback;
            intr_event.param = (void *)(&(drv_can->can_handle));
            FCanRegisterInterruptHandler(&(drv_can->can_handle), &intr_event);
            FCanInterruptEnable(&(drv_can->can_handle), intr_event.type);
        }
        rt_hw_interrupt_set_priority(drv_can->can_handle.config.irq_num, 16);
        rt_hw_interrupt_install(drv_can->can_handle.config.irq_num, FCanIntrHandler, &(drv_can->can_handle), drv_can->name);
        rt_hw_interrupt_umask(drv_can->can_handle.config.irq_num);
        break;

    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        FCanEnable(&(drv_can->can_handle), RT_FALSE);
        if (argval == RT_CAN_MODE_LISTEN)
        {
            FCanSetMode(&(drv_can->can_handle), FCAN_PROBE_MONITOR_MODE);
            drv_can->device.config.mode = RT_CAN_MODE_LISTEN;
        }
        else if (argval == RT_CAN_MODE_NORMAL)
        {
            FCanSetMode(&(drv_can->can_handle), FCAN_PROBE_NORMAL_MODE);
            drv_can->device.config.mode = RT_CAN_MODE_NORMAL;
        }
        FCanEnable(&(drv_can->can_handle), RT_TRUE);
        break;

    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if (argval != CAN1MBaud   &&
            argval != CAN800kBaud &&
            argval != CAN500kBaud &&
            argval != CAN250kBaud &&
            argval != CAN125kBaud &&
            argval != CAN100kBaud &&
            argval != CAN50kBaud  &&
            argval != CAN20kBaud  &&
            argval != CAN10kBaud)
        {
            return RT_ERROR;
        }
        if (argval != drv_can->device.config.baud_rate)
        {
            FCanBaudrateConfig arb_segment_config;
            FCanBaudrateConfig data_segment_config;
            memset(&arb_segment_config, 0, sizeof(arb_segment_config));
            memset(&data_segment_config, 0, sizeof(data_segment_config));
            drv_can->device.config.baud_rate = argval;
            FCanEnable(&(drv_can->can_handle), RT_FALSE);
            arb_segment_config.auto_calc = TRUE;
            arb_segment_config.baudrate = drv_can->device.config.baud_rate;
            arb_segment_config.segment = FCAN_ARB_SEGMENT;
            status = FCanBaudrateSet(&(drv_can->can_handle), &arb_segment_config);
            if (status != FT_SUCCESS)
            {
                FCAN_TEST_DEBUG("CAN%d set arb segment baudrate failed.", drv_can->can_handle.config.instance_id);
                return RT_ERROR;
            }
            data_segment_config.auto_calc = TRUE;
            data_segment_config.baudrate = drv_can->device.config.baud_rate;
            data_segment_config.segment = FCAN_DATA_SEGMENT;
            status = FCanBaudrateSet(&(drv_can->can_handle), &data_segment_config);
            if (status != FT_SUCCESS)
            {
                FCAN_TEST_DEBUG("CAN%d set data segment baudrate failed.", drv_can->can_handle.config.instance_id);
                return RT_ERROR;
            }
            FCanEnable(&(drv_can->can_handle), RT_TRUE);
        }
        break;

    case RT_CAN_CMD_SET_BAUD_FD:
    #if defined RT_CAN_USING_CANFD
        argval = (rt_uint32_t) arg;
        if (argval != drv_can->device.config.baud_rate_fd)
        {
            FCanBaudrateConfig arb_segment_config;
            FCanBaudrateConfig data_segment_config;
            memset(&arb_segment_config, 0, sizeof(arb_segment_config));
            memset(&data_segment_config, 0, sizeof(data_segment_config));
            drv_can->device.config.baud_rate = argval;
            FCanEnable(&(drv_can->can_handle), RT_FALSE);
            arb_segment_config.auto_calc = TRUE;
            arb_segment_config.baudrate = CAN1MBaud;
            arb_segment_config.segment = FCAN_ARB_SEGMENT;
            status = FCanBaudrateSet(&(drv_can->can_handle), &arb_segment_config);
            if (status != FT_SUCCESS)
            {
                FCAN_TEST_DEBUG("CAN%d set arb segment baudrate failed.", drv_can->can_handle.config.instance_id);
                return RT_ERROR;
            }
            data_segment_config.auto_calc = TRUE;
            data_segment_config.baudrate = drv_can->device.config.baud_rate_fd;
            data_segment_config.segment = FCAN_DATA_SEGMENT;
            status = FCanBaudrateSet(&(drv_can->can_handle), &data_segment_config);
            if (status != FT_SUCCESS)
            {
                FCAN_TEST_DEBUG("CAN%d set data segment baudrate failed.", drv_can->can_handle.config.instance_id);
                return RT_ERROR;
            }
            FCanEnable(&(drv_can->can_handle), RT_TRUE);
        }
    #endif
    break;

    case RT_CAN_CMD_SET_FILTER:
    #ifdef RT_CAN_USING_HDR
        filter_cfg = (struct rt_can_filter_config *)arg;
        FCanEnable(&(drv_can->can_handle), RT_FALSE);
        for (int i = 0; i < filter_cfg->count; i++)
        {
            drv_can->filter.filter_index = i;
            drv_can->filter.mask = filter_cfg->items[i].mask;
            drv_can->filter.id = filter_cfg->items[i].id;
            drv_can->filter.type = FCAN_STANDARD_FRAME;
            status = FCanIdMaskFilterSet(&(drv_can->can_handle), &(drv_can->filter));
            if (status != FT_SUCCESS)
            {
                FCAN_TEST_ERROR("CAN%d set mask filter failed.", drv_can->can_handle.config.instance_id);
                return RT_ERROR;
            }
        }
        FCanEnable(&(drv_can->can_handle), RT_TRUE);
    #endif
        break;
    }

    return RT_EOK;
}

static int _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    RT_ASSERT(can);
    RT_ASSERT(buf);
    struct phytium_can *drv_can;
    drv_can = (struct phytium_can *)can->parent.user_data;
    RT_ASSERT(drv_can);
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;
    FCanFrame can_frame = {0};

    /* Check the parameters */
    RT_ASSERT(pmsg->len <= 8U);

    if (RT_CAN_STDID == pmsg->ide)
    {
        can_frame.canid = pmsg->id;
    }
    else
    {
        can_frame.canid = pmsg->id;
        can_frame.canid |= CAN_EFF_FLAG;
    }
    if (RT_CAN_DTR == pmsg->rtr)
    {

    }
    else
    {
        can_frame.canid |= CAN_RTR_FLAG;
    }

    can_frame.candlc = pmsg->len ;

    memcpy(can_frame.data, pmsg->data, 8);
    return (FCanSend(&drv_can->can_handle, &can_frame) == RT_EOK) ? RT_EOK : -RT_ERROR;
}

static int _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    RT_ASSERT(can);
    RT_ASSERT(buf);
    struct phytium_can *drv_can;
    drv_can = (struct phytium_can *)can->parent.user_data;
    RT_ASSERT(drv_can);
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;
    FCanFrame recv_frame;
    FError status = FT_SUCCESS;

    status = FCanRecv(&(drv_can->can_handle), &recv_frame);
    if (status != FT_SUCCESS)
    {
        FCAN_TEST_DEBUG("CAN%d recv data failed.", drv_can->can_handle.config.instance_id);
        return RT_ERROR;
    }
    if (CAN_EFF_FLAG & recv_frame.canid)
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = (recv_frame.canid & ~(RT_CAN_EXTID));
    }
    else
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = recv_frame.canid;
    }

    if (CAN_RTR_FLAG & recv_frame.canid)
    {
        pmsg->id &= ~CAN_RTR_FLAG;
        pmsg->rtr = RT_CAN_RTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_DTR;
    }

    /* get len */
    pmsg->len = recv_frame.candlc;
    for (int i = 0; i < pmsg->len; i++)
    {
        pmsg->data[i] = recv_frame.data[i];
    }
    /* get hdr */
    pmsg->hdr = 0;

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
{
    _can_config,
    _can_control,
    _can_sendmsg,
    _can_recvmsg,
};

int rt_hw_can_init(void)
{
    rt_err_t ret = RT_EOK;
    for (int i = 0; i < (u32)FCAN_NUM; i++)
    {
        drv_can[i].device.config.ticks = 20000;
        drv_can[i].device.config.baud_rate = 800000;
    #ifdef RT_CAN_USING_CANFD
        drv_can[i].device.config.baud_rate_fd = 800000;
    #endif
        drv_can[i].device.config.mode = RT_CAN_MODE_NORMAL;
        drv_can[i].device.config.sndboxnumber = 1;
        drv_can[i].device.config.msgboxsz = 1;
    #ifdef RT_CAN_USING_HDR
        drv_can[i].device.config.maxhdr = 1;
    #endif
        ret = rt_hw_can_register(&drv_can[i].device,
                       drv_can[i].name,
                       &_can_ops,
                       &drv_can[i]);
        RT_ASSERT(ret == RT_EOK);
    }
    return (int)ret;
}
INIT_BOARD_EXPORT(rt_hw_can_init);

/*can test example*/
static rt_device_t can_dev;            /* CAN device handle */
static struct rt_semaphore rx_sem;
static rt_err_t can_rx_call(rt_device_t dev, rt_size_t size)
{
    /* The CAN generates an interrupt after receiving data, calls this callback function, and then sends the received semaphore */
    rt_sem_release(&rx_sem);
    return RT_EOK;
}
static void can_rx_thread(void *parameter)
{
    int i;
    rt_err_t res = RT_EOK;
    struct rt_can_msg rxmsg = {0};
    rt_device_set_rx_indicate(can_dev, can_rx_call);
    while (1)
    {
        /* The hdr value is - 1, which means reading data directly from the uselist */
        rxmsg.hdr = -1;
        /* Blocking waiting to receive semaphore */
        res = rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        RT_ASSERT(res == RT_EOK);
        /* Read a frame of data from CAN */
        rt_device_read(can_dev, 0, &rxmsg, sizeof(rxmsg));
        /* Print data ID and conten */
        rt_kprintf("ID:%x\n", rxmsg.id);
        rt_kprintf("DATA: ");
        for (i = 0; i < 8; i++)
        {
            rt_kprintf("%2x ", rxmsg.data[i]);
        }

        rt_kprintf("\n");
    }
}

int can_sample(int argc, char *argv[])
{
    struct rt_can_msg msg = {0};
    rt_err_t res = RT_EOK;;
    rt_size_t  size;
    rt_thread_t thread;
    char can_name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(can_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(can_name, "CAN0", RT_NAME_MAX);
    }
    /* Find CAN device */
    can_dev = rt_device_find(can_name);
    if (!can_dev)
    {
        rt_kprintf("Find %s failed.\n", can_name);
        return RT_ERROR;
    }

    /* Initialize CAN receive signal quantity */
    res = rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(res == RT_EOK);

    /* Open the CAN device in the way of interrupt reception and transmission */
    res = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    rt_device_control(can_dev,RT_CAN_CMD_SET_BAUD, CAN1MBaud);
    RT_ASSERT(res == RT_EOK);

    #ifdef RT_CAN_USING_HDR
    struct rt_can_filter_item items[4] =
    {
        RT_CAN_FILTER_ITEM_INIT(0x3, 0, 0, 0, 0, RT_NULL, RT_NULL),
        RT_CAN_FILTER_ITEM_INIT(0x3, 0, 0, 0, 0, RT_NULL, RT_NULL),
        RT_CAN_FILTER_ITEM_INIT(0x3, 0, 0, 0, 0, RT_NULL, RT_NULL),
        RT_CAN_FILTER_ITEM_INIT(0x3, 0, 0, 0, 0, RT_NULL, RT_NULL)

    };
    struct rt_can_filter_config cfg = {4, 1, items}; /* There are 4 filter tables in total */

    /* Set the hardware filter table. After setting, only frames with id=0x03 can be received*/
    res = rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
    RT_ASSERT(res == RT_EOK);
    #endif

    /* Create data receiving thread */
    thread = rt_thread_create("can_rx", can_rx_thread, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        res = rt_thread_startup(thread);
        RT_ASSERT(res == RT_EOK);
    }
    else
    {
        rt_kprintf("Create can_rx thread failed.\n");
    }

    msg.id = 0x78;              /* ID = 0x78 */
    msg.ide = RT_CAN_STDID;     /* Standard format */
    msg.rtr = RT_CAN_RTR;       /* Data frame */
    msg.len = 8;                /* Data length is 8 */
    /* Send CAN data */
    for (int i = 0; i < 10; i++)
    {
    /* 8-byte data to be sent */
        msg.data[0] = 0x00+i;
        msg.data[1] = 0x11+i;
        msg.data[2] = 0x22+i;
        msg.data[3] = 0x33+i;
        msg.data[4] = 0x44+i;
        msg.data[5] = 0x55+i;
        msg.data[6] = 0x66+i;
        msg.data[7] = 0x77+i;
        rt_device_write(can_dev, 0, &msg, sizeof(msg));
    }

    return res;
}
/* Enter can_sample command for testing */
MSH_CMD_EXPORT(can_sample, can device sample);
#endif
