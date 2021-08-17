/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-11     Carl        the first version
 */

#include "drv_can.h"
#include "interrupt.h"
#include <string.h>

#ifdef BSP_USE_CAN

#define LOG_TAG "drv_can"
#include <drv_log.h>

#define _CAN0_NAME "can0"
#define _CAN1_NAME "can1"

#define RTHW_CAN_WAIT(_can) rt_sem_take(&_can->recv_semaphore, RT_WAITING_FOREVER);
#define RTHW_CAN_SEND(_can) rt_sem_release(&_can->recv_semaphore);

#ifdef BSP_USING_CAN0
struct ft2004_can drv_can0 =
    {
        .name = _CAN0_NAME,
        .can_handle.Config.InstanceId = 0};
#endif

#ifdef BSP_USING_CAN1
struct ft2004_can drv_can1 =
    {
        .name = _CAN1_NAME,
        .can_handle.Config.InstanceId = 1};
#endif

static void _can_recv_irq(void *args)
{
    struct ft2004_can *drv_can = (struct ft2004_can *)args;
    RTHW_CAN_SEND(drv_can);
}

static void rt_hw_inner_can_isr(int irqno, void *param)
{
    FCan_IntrHandler(param);
}

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    struct FCan_Bittiming bit_timing = {0};
    struct ft2004_can *drv_can;
    RT_ASSERT(can);
    RT_ASSERT(cfg);
    drv_can = (struct ft2004_can *)can->parent.user_data;
    RT_ASSERT(drv_can);

    FCan_CfgInitialize(&drv_can->can_handle, FCan_LookupConfig(drv_can->can_handle.Config.InstanceId));

    FCan_SetHandler(&drv_can->can_handle, FCAN_HANDLER_RECV, _can_recv_irq, drv_can);

    bit_timing.bitrate = cfg->baud_rate;

    if (FCan_CalcBittiming(&bit_timing) != FCAN_SUCCESS)
    {
        LOG_E("Setting baud rate %x is not valid \r\n", bit_timing.bitrate);
        return -RT_ERROR;
    }

    FCan_SetTiming(&drv_can->can_handle, &bit_timing);

    rt_hw_interrupt_set_priority(drv_can->can_handle.Config.IrqNum, 16);
    rt_hw_interrupt_install(drv_can->can_handle.Config.IrqNum, rt_hw_inner_can_isr, &drv_can->can_handle, drv_can->name);
    rt_hw_interrupt_umask(drv_can->can_handle.Config.IrqNum);

    FCan_Enable(&drv_can->can_handle);

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    return RT_EOK;
}

static int _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    struct ft2004_can *drv_can;
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;
    struct FCan_Frame can_frame = {0};
    RT_ASSERT(can);
    drv_can = (struct ft2004_can *)can->parent.user_data;
    RT_ASSERT(drv_can);

    /* Check the parameters */
    RT_ASSERT(pmsg->len <= 8U);

    if (RT_CAN_STDID == pmsg->ide)
    {
        can_frame.CanId = pmsg->id;
    }
    else
    {
        can_frame.CanId = pmsg->id;
        can_frame.CanId |= CAN_EFF_FLAG;
    }

    if (RT_CAN_DTR == pmsg->rtr)
    {
    }
    else
    {
        can_frame.CanId |= CAN_RTR_FLAG;
    }

    can_frame.CanDlc = pmsg->len & 0x0FU;
    memcpy(can_frame.data, pmsg->data, 8);

    return (FCan_SendByIrq(&drv_can->can_handle, &can_frame, 1, RT_NULL) == 1) ? RT_EOK : -RT_ERROR;
}

static int _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct ft2004_can *drv_can;
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;
    RT_ASSERT(can);
    struct FCan_Frame recv_frame = {0};
    drv_can = (struct ft2004_can *)can->parent.user_data;
    RT_ASSERT(drv_can);

    RTHW_CAN_WAIT(drv_can);

    if (FCan_RecvByIrq(&drv_can->can_handle, &recv_frame, 1) == 0)
    {
        LOG_E("rx msg is error");
        return -RT_ERROR;
    }

    if (CAN_EFF_FLAG & recv_frame.CanId)
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = (recv_frame.CanId & ~(RT_CAN_EXTID));
    }
    else
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = recv_frame.CanId;
    }

    if (CAN_RTR_FLAG & recv_frame.CanId)
    {
        pmsg->id &= ~CAN_RTR_FLAG;
        pmsg->rtr = RT_CAN_RTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_DTR;
    }

    /* get len */
    pmsg->len = recv_frame.CanDlc;
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
#ifdef BSP_USING_CAN0
    drv_can0.can_handle.Config.InstanceId = 0;
    rt_sem_init(&drv_can0.recv_semaphore, "can0_recv", 0, RT_IPC_FLAG_FIFO);
    drv_can0.device.config.ticks = 20000;
    drv_can0.device.config.baud_rate = 1000000;
    rt_hw_can_register(&drv_can0.device,
                       drv_can0.name,
                       &_can_ops,
                       &drv_can0);

#endif

#ifdef BSP_USING_CAN1
    drv_can1.can_handle.Config.InstanceId = 1;
    drv_can1.device.config.ticks = 20000;
    drv_can1.device.config.baud_rate = 1000000;
    rt_sem_init(&drv_can1.recv_semaphore, "can1_recv", 0, RT_IPC_FLAG_FIFO);
    rt_hw_can_register(&drv_can1.device,
                       drv_can1.name,
                       &_can_ops,
                       &drv_can1);

#endif
    return 0;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#ifdef BSP_USING_CAN0_DEBUG

struct can_test_struct
{
    const char *name;
    struct rt_can_filter_config *filter;
    rt_device_t candev;
    struct rt_semaphore _sem;
};

static struct can_test_struct can0_test_obj = {
    .name = _CAN0_NAME};

void can_recv_irq(void *param)
{
    struct can_test_struct *_can_obj = (struct can_test_struct *)param;
    rt_kprintf("can_recv_iqr \r\n");
    rt_sem_release(&_can_obj->_sem);
}

static void rt_can_test_loopback_thread_entry(void *param)
{
    struct can_test_struct *_can_obj = (struct can_test_struct *)param;
    struct FCan_Frame recv_frame;
    struct ft2004_can *drv_can;
    rt_uint32_t i;
    _can_obj->candev = rt_device_find(_can_obj->name);
    RT_ASSERT(_can_obj->candev);
    drv_can = (struct ft2004_can *)_can_obj->candev->user_data;
    rt_sem_init(&_can_obj->_sem, "canrx_wait", 0, RT_IPC_FLAG_FIFO);
    rt_device_open(_can_obj->candev, RT_DEVICE_OFLAG_RDWR);

    while (1)
    {
        rt_kprintf(" start to wait  loopback \r\n");
        RTHW_CAN_WAIT(drv_can);
        while (0 != FCan_RecvByIrq(&drv_can->can_handle, &recv_frame, 1))
        {
            rt_kprintf("CanId %x \r\n", recv_frame.CanId);
            rt_kprintf("CanDlc %x \r\n", recv_frame.CanDlc);
            for (i = 0; i < recv_frame.CanDlc; i++)
            {
                rt_kprintf("data [%d] %x \r\n", i, recv_frame.data[i]);
            }
            FCan_SendByIrq(&drv_can->can_handle, &recv_frame, 1, RT_NULL);
        }
    }
}

int rt_can0_test(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("can0_loopback",
                           rt_can_test_loopback_thread_entry, &can0_test_obj,
                           1024, 16, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

INIT_APP_EXPORT(rt_can0_test);

#endif

#endif
