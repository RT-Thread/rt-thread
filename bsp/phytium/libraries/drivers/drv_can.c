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

#include "rtconfig.h"
#include <rtdevice.h>
#include "drv_can.h"
#define LOG_TAG      "can_drv"
#include "drv_log.h"
#include "fcan.h"
#include "fio_mux.h"
#include "interrupt.h"
#include "fcpu_info.h"
#ifdef RT_USING_SMART
    #include <ioremap.h>
#endif

struct phytium_can
{
    const char *name;
    FCanCtrl can_handle;
    FCanIdMaskConfig filter;
    struct rt_can_device device; /* inherit from can device */
};

#if defined(RT_USING_CAN0)
    static struct phytium_can drv_can0;
#endif
#if defined(RT_USING_CAN1)
    static struct phytium_can drv_can1;
#endif

static void CanRxIrqCallback(void *args)
{
    struct phytium_can *drv_can = (struct phytium_can *)args;

    rt_hw_can_isr(&(drv_can->device), RT_CAN_EVENT_RX_IND);

    LOG_D("CAN%d irq recv frame callback.", drv_can->can_handle.config.instance_id);
}

static void CanTxIrqCallback(void *args)
{
    struct phytium_can *drv_can = (struct phytium_can *)args;

    rt_hw_can_isr(&(drv_can->device), RT_CAN_EVENT_TX_DONE);

    LOG_D("CAN%d irq send frame callback.", drv_can->can_handle.config.instance_id);
}

static void CanErrorCallback(void *args)
{
    FCanCtrl *instance_p = (FCanCtrl *)args;
    uintptr base_addr = instance_p->config.base_address;
    LOG_D("CAN %d is under error.", instance_p->config.instance_id);
    LOG_D("error_status is %x.", FCAN_READ_REG32(base_addr, FCAN_INTR_OFFSET));
    LOG_D("rxerr_cnt is %x.", FCAN_ERR_CNT_RFN_GET(FCAN_READ_REG32(base_addr, FCAN_ERR_CNT_OFFSET)));
    LOG_D("txerr_cnt is %x.", FCAN_ERR_CNT_TFN_GET(FCAN_READ_REG32(base_addr, FCAN_ERR_CNT_OFFSET)));
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

    FIOPadSetCanMux(drv_can->can_handle.config.instance_id);
    FCanConfig *config_p;
    config_p = FCanLookupConfig(drv_can->can_handle.config.instance_id);
#ifdef RT_USING_SMART
    config_p->base_address = (uintptr)rt_ioremap((void *)config_p->base_address, 0x1000);
#endif
    /*CAN config init*/
    status = FCanCfgInitialize(&(drv_can->can_handle), config_p);
    if (status != FT_SUCCESS)
    {
        LOG_D("CAN %d initialize error, status = %#x.", drv_can->can_handle.config.instance_id, status);
        return -RT_ERROR;
    }
    /*Set the baudrate*/
    FCanBaudrateConfig arb_segment_config;
    FCanBaudrateConfig data_segment_config;
    rt_memset(&arb_segment_config, 0, sizeof(arb_segment_config));
    rt_memset(&data_segment_config, 0, sizeof(data_segment_config));
#if defined(RT_CAN_USING_CANFD)
    FCanFdEnable(&(drv_can->can_handle), TRUE);
    arb_segment_config.auto_calc = TRUE;
    arb_segment_config.baudrate = CAN1MBaud; /*CANFD arb baud defaults to 1M ,allowed to be modified*/
    arb_segment_config.segment = FCAN_ARB_SEGMENT;
    status = FCanBaudrateSet(&(drv_can->can_handle), &arb_segment_config);
    if (status != RT_EOK)
    {
        LOG_D("CAN%d set arb segment baudrate failed.", drv_can->can_handle.config.instance_id);
        return -RT_ERROR;
    }
    data_segment_config.auto_calc = TRUE;
    data_segment_config.baudrate = cfg->baud_rate_fd;
    data_segment_config.segment = FCAN_DATA_SEGMENT;
    status = FCanBaudrateSet(&(drv_can->can_handle), &data_segment_config);
    if (status != RT_EOK)
    {
        LOG_D("CAN%d set data segment baudrate failed.", drv_can->can_handle.config.instance_id);
        return -RT_ERROR;
    }
#else
    arb_segment_config.auto_calc = TRUE;
    arb_segment_config.baudrate = cfg->baud_rate;
    arb_segment_config.segment = FCAN_ARB_SEGMENT;
    status = FCanBaudrateSet(&(drv_can->can_handle), &arb_segment_config);
    if (status != FT_SUCCESS)
    {
        LOG_D("CAN%d set arb segment baudrate failed.", drv_can->can_handle.config.instance_id);
        return -RT_ERROR;
    }
    data_segment_config.auto_calc = TRUE;
    data_segment_config.baudrate = cfg->baud_rate;
    data_segment_config.segment = FCAN_DATA_SEGMENT;
    status = FCanBaudrateSet(&(drv_can->can_handle), &data_segment_config);
    if (status != FT_SUCCESS)
    {
        LOG_D("CAN%d set data segment baudrate failed.", drv_can->can_handle.config.instance_id);
        return -RT_ERROR;
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
        LOG_E("CAN%d set mask filter failed.", drv_can->can_handle.config.instance_id);
        return -RT_ERROR;
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
    rt_uint32_t cpu_id = rt_hw_cpu_id();
    FCanIntrEventConfig intr_event;
    FError status = FT_SUCCESS;

#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_config *filter_cfg;
#endif

    switch (cmd)
    {
        case RT_DEVICE_CTRL_SET_INT:
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
                intr_event.param = (void *)(drv_can);
                FCanRegisterInterruptHandler(&(drv_can->can_handle), &intr_event);
                FCanInterruptEnable(&(drv_can->can_handle), intr_event.type);
            }
            if (argval == RT_DEVICE_FLAG_INT_RX)
            {
                intr_event.type = FCAN_INTR_EVENT_RECV;
                intr_event.handler = CanRxIrqCallback;
                intr_event.param = (void *)(drv_can);
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
                return -RT_ERROR;
            }
            if (argval != drv_can->device.config.baud_rate)
            {
                FCanBaudrateConfig arb_segment_config;
                FCanBaudrateConfig data_segment_config;
                rt_memset(&arb_segment_config, 0, sizeof(arb_segment_config));
                rt_memset(&data_segment_config, 0, sizeof(data_segment_config));
                drv_can->device.config.baud_rate = argval;
                FCanEnable(&(drv_can->can_handle), RT_FALSE);
                arb_segment_config.auto_calc = TRUE;
                arb_segment_config.baudrate = drv_can->device.config.baud_rate;
                arb_segment_config.segment = FCAN_ARB_SEGMENT;
                status = FCanBaudrateSet(&(drv_can->can_handle), &arb_segment_config);
                if (status != FT_SUCCESS)
                {
                    LOG_D("CAN%d set arb segment baudrate failed.", drv_can->can_handle.config.instance_id);
                    return -RT_ERROR;
                }
                data_segment_config.auto_calc = TRUE;
                data_segment_config.baudrate = drv_can->device.config.baud_rate;
                data_segment_config.segment = FCAN_DATA_SEGMENT;
                status = FCanBaudrateSet(&(drv_can->can_handle), &data_segment_config);
                if (status != FT_SUCCESS)
                {
                    LOG_D("CAN%d set data segment baudrate failed.", drv_can->can_handle.config.instance_id);
                    return -RT_ERROR;
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
                rt_memset(&arb_segment_config, 0, sizeof(arb_segment_config));
                rt_memset(&data_segment_config, 0, sizeof(data_segment_config));
                drv_can->device.config.baud_rate = argval;
                FCanEnable(&(drv_can->can_handle), RT_FALSE);
                arb_segment_config.auto_calc = TRUE;
                arb_segment_config.baudrate = CAN1MBaud;
                arb_segment_config.segment = FCAN_ARB_SEGMENT;
                status = FCanBaudrateSet(&(drv_can->can_handle), &arb_segment_config);
                if (status != FT_SUCCESS)
                {
                    LOG_D("CAN%d set arb segment baudrate failed.", drv_can->can_handle.config.instance_id);
                    return -RT_ERROR;
                }
                data_segment_config.auto_calc = TRUE;
                data_segment_config.baudrate = drv_can->device.config.baud_rate_fd;
                data_segment_config.segment = FCAN_DATA_SEGMENT;
                status = FCanBaudrateSet(&(drv_can->can_handle), &data_segment_config);
                if (status != FT_SUCCESS)
                {
                    LOG_D("CAN%d set data segment baudrate failed.", drv_can->can_handle.config.instance_id);
                    return -RT_ERROR;
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
                    LOG_E("CAN%d set mask filter failed.", drv_can->can_handle.config.instance_id);
                    return -RT_ERROR;
                }
            }
            FCanEnable(&(drv_can->can_handle), RT_TRUE);
#endif
            break;
    }

    return RT_EOK;
}

static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
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

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
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
        LOG_D("CAN%d recv data failed.", drv_can->can_handle.config.instance_id);
        return -RT_ERROR;
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
    pmsg->hdr_index = 0;

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
{
    _can_config,
    _can_control,
    _can_sendmsg,
    _can_recvmsg,
};

static int can_init(struct phytium_can *drv_can)
{
    rt_err_t ret = RT_EOK;

    drv_can->device.config.ticks = 20000;
    /*can default baud_rate*/
    drv_can->device.config.baud_rate = CAN800kBaud;
#ifdef RT_CAN_USING_CANFD
    /*canfd default baud_rate 1M+800K*/
    drv_can->device.config.baud_rate_fd = CAN800kBaud;
#endif
    drv_can->device.config.mode = RT_CAN_MODE_NORMAL;
    drv_can->device.config.sndboxnumber = 1;
    drv_can->device.config.msgboxsz = 1;
#ifdef RT_CAN_USING_HDR
    drv_can->device.config.maxhdr = 1;
#endif
    ret = rt_hw_can_register(&drv_can->device,
                             drv_can->name,
                             &_can_ops,
                             drv_can);
    RT_ASSERT(ret == RT_EOK);

    return ret;
}

int rt_hw_can_init(void)
{
#if defined(RT_USING_CAN0)
    drv_can0.name = "CAN0";
    drv_can0.can_handle.config.instance_id = FCAN0_ID;
    can_init(&drv_can0);
#endif
#if defined(RT_USING_CAN1)
    drv_can1.name = "CAN1";
    drv_can1.can_handle.config.instance_id = FCAN1_ID;
    can_init(&drv_can1);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_can_init);
