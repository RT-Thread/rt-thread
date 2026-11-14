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
#include "ft_can_hw.h"
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
    rt_hw_can_isr(&drv_can->device, RT_CAN_EVENT_RX_IND);
}

static void rt_hw_inner_can_isr(int irqno, void *param)
{
    /* This IRQ belongs to one controller instance and its MMIO register base. */
    struct ft2004_can *drv_can = (struct ft2004_can *)param;
    rt_uint32_t base = drv_can->can_handle.Config.CanBaseAddress;
    /* Snapshot simultaneous TX/RX causes; RX count bounds the ISR drain loop. */
    rt_uint32_t irq = FCan_ReadReg(base, FCAN_INTR_OFFSET);
    rt_uint32_t rx_count;

    (void)irqno;

    if (irq & FCAN_INTR_TEIS_MASK)
    {
        FCan_SetBit(base, FCAN_INTR_OFFSET, FCAN_INTR_TEIC_MASK);
#ifdef BSP_USING_CAN0_DEBUG
        if (drv_can->can_handle.TxFifoCnt > 0U)
        {
            /* FCan_SendByIrq() is still used only by the legacy CAN0 diagnostic. */
            drv_can->can_handle.TxFifoCnt--;
        }
        else
#endif /* BSP_USING_CAN0_DEBUG */
        {
            rt_hw_can_isr(&drv_can->device, RT_CAN_EVENT_TX_DONE);
        }
    }

    if (irq & FCAN_INTR_REIS_MASK)
    {
        FCan_ClearBit(base, FCAN_INTR_OFFSET, FCAN_INTR_REIE_MASK);
#ifdef BSP_USING_CAN0_DEBUG
        /* One wake allows the diagnostic thread to drain the FIFO itself. */
        RTHW_CAN_SEND(drv_can);
#endif /* BSP_USING_CAN0_DEBUG */
        /* Drain the RX FIFO before acknowledging the frame-end indication. */
        rx_count = FCan_ReadReg(base, FCAN_FIFO_CNT_OFFSET) & 0x3fU;
        while (rx_count > 0U)
        {
            _can_recv_irq(drv_can);
            rx_count--;
        }
        FCan_SetBit(base, FCAN_INTR_OFFSET, FCAN_INTR_REIC_MASK);
        FCan_SetBit(base, FCAN_INTR_OFFSET, FCAN_INTR_REIE_MASK);
    }

    if (irq & (FCAN_INTR_EIS_MASK | FCAN_INTR_RFIS_MASK |
               FCAN_INTR_BOIS_MASK | FCAN_INTR_PEIS_MASK | FCAN_INTR_PWIS_MASK))
    {
        FCan_SetBit(base, FCAN_INTR_OFFSET, FCAN_INTR_EIC_MASK | FCAN_INTR_RFIC_MASK |
                    FCAN_INTR_BOIC_MASK | FCAN_INTR_PEIC_MASK | FCAN_INTR_PWIC_MASK);
    }
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

    bit_timing.bitrate = cfg->baud_rate;

    if (FCan_CalcBittiming(&bit_timing) != FCAN_SUCCESS)
    {
        LOG_E("Setting baud rate %x is not valid \r\n", bit_timing.bitrate);
        return -RT_ERROR;
    }

    FCan_SetTiming(&drv_can->can_handle, &bit_timing);

    rt_hw_interrupt_set_priority(drv_can->can_handle.Config.IrqNum, 16);
    rt_hw_interrupt_install(drv_can->can_handle.Config.IrqNum, rt_hw_inner_can_isr, drv_can, drv_can->name);
    rt_hw_interrupt_umask(drv_can->can_handle.Config.IrqNum);

    FCan_Enable(&drv_can->can_handle);

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    return RT_EOK;
}

static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    struct ft2004_can *drv_can;
    const struct rt_can_msg *pmsg = (const struct rt_can_msg *)buf;
    /* CAN ID, DLC and payload words use the SDK's TX FIFO wire layout. */
    rt_uint32_t id, dlc, send_buffer = 0;
    /* MMIO base for this instance, kept separate from Generic logical mailbox 0. */
    rt_uint32_t base;

    RT_ASSERT(can);
    drv_can = (struct ft2004_can *)can->parent.user_data;
    RT_ASSERT(drv_can);

    if (box_num != 0U || pmsg->len > 8U)
    {
        return -RT_EINVAL;
    }

    base = drv_can->can_handle.Config.CanBaseAddress;
    if (FCan_ReadReg(base, FCAN_FIFO_CNT_OFFSET) & FCAN_FIFO_CNT_TFN_MASK)
    {
        return -RT_EBUSY;
    }

    /* Do not use FCan_SendByIrq(): with no wait callback it spins on TxFifoCnt. */
    FCan_ClearBit(base, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
    FCan_ClearBit(base, FCAN_CTRL_OFFSET, FCAN_CTRL_TXREQ_MASK);
    FCan_SetBit(base, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
    FCan_SetBit(base, FCAN_INTR_OFFSET, FCAN_INTR_TEIC_MASK);

    if (RT_CAN_STDID == pmsg->ide)
    {
        id = ((pmsg->id & CAN_SFF_MASK) << FCAN_IDR_ID1_SHIFT) & FCAN_IDR_ID1_MASK;
        if (RT_CAN_RTR == pmsg->rtr)
        {
            id |= FCAN_IDR_SRR_MASK;
        }
        dlc = (pmsg->len << FCAN_IDR_SDLC_SHIFT) | FCAN_IDR_PAD_MASK;
        FCan_WriteReg(base, FCAN_TX_FIFO_OFFSET, FT_SWAP32(id | dlc));
    }
    else
    {
        id = ((pmsg->id & CAN_EFF_MASK) << FCAN_IDR_ID2_SHIFT) & FCAN_IDR_ID2_MASK;
        id |= (((pmsg->id & CAN_EFF_MASK) >> (CAN_EFF_ID_BITS - CAN_SFF_ID_BITS))
               << FCAN_IDR_ID1_SHIFT) & FCAN_IDR_ID1_MASK;
        id |= FCAN_IDR_IDE_MASK | FCAN_IDR_SRR_MASK;
        if (RT_CAN_RTR == pmsg->rtr)
        {
            id |= FCAN_IDR_RTR_MASK;
        }
        dlc = pmsg->len << FCAN_IDR_EDLC_SHIFT;
        FCan_WriteReg(base, FCAN_TX_FIFO_OFFSET, FT_SWAP32(id));
        FCan_WriteReg(base, FCAN_TX_FIFO_OFFSET, FT_SWAP32(dlc));
    }

    if (RT_CAN_DTR == pmsg->rtr)
    {
        if (pmsg->len > 0U)
        {
            memcpy(&send_buffer, pmsg->data, sizeof(send_buffer));
            FCan_WriteReg(base, FCAN_TX_FIFO_OFFSET, send_buffer);
        }
        if (pmsg->len > 4U)
        {
            memcpy(&send_buffer, &pmsg->data[4], sizeof(send_buffer));
            FCan_WriteReg(base, FCAN_TX_FIFO_OFFSET, send_buffer);
        }
    }

    /* One frame per Generic mailbox; only TEIS releases its ownership. */
    FCan_ClearBit(base, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
    FCan_SetBit(base, FCAN_CTRL_OFFSET, FCAN_CTRL_TXREQ_MASK);
    FCan_SetBit(base, FCAN_CTRL_OFFSET, FCAN_CTRL_TXREQ_MASK | FCAN_CTRL_XFER_MASK);

    return RT_EOK;
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct ft2004_can *drv_can;
    struct rt_can_msg *pmsg = (struct rt_can_msg *)buf;
    struct FCan_Frame recv_frame = {0};

    RT_ASSERT(can);
    drv_can = (struct ft2004_can *)can->parent.user_data;
    RT_ASSERT(drv_can);
    (void)fifo;

    /* The RX ISR must never wait for a semaphore or another RX interrupt. */
    if (FCan_RecvByIrq(&drv_can->can_handle, &recv_frame, 1) == 0U)
    {
        return -RT_ERROR;
    }

    if (CAN_EFF_FLAG & recv_frame.CanId)
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = recv_frame.CanId & CAN_EFF_MASK;
    }
    else
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = recv_frame.CanId & CAN_SFF_MASK;
    }

    pmsg->rtr = (CAN_RTR_FLAG & recv_frame.CanId) ? RT_CAN_RTR : RT_CAN_DTR;
    pmsg->len = recv_frame.CanDlc;
    if (pmsg->rtr == RT_CAN_DTR)
    {
        memcpy(pmsg->data, recv_frame.data, pmsg->len);
    }

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
    {
        _can_config,
        _can_control,
        _can_sendmsg,
        _can_recvmsg,
        RT_NULL,
};

int rt_hw_can_init(void)
{
#ifdef BSP_USING_CAN0
    drv_can0.can_handle.Config.InstanceId = 0;
    rt_sem_init(&drv_can0.recv_semaphore, "can0_recv", 0, RT_IPC_FLAG_FIFO);
    drv_can0.device.config.ticks = 20000;
    drv_can0.device.config.baud_rate = 1000000;
    drv_can0.device.config.sndboxnumber = 1;
    drv_can0.device.config.msgboxsz = RT_CANMSG_BOX_SZ;
    rt_hw_can_register(&drv_can0.device,
                       drv_can0.name,
                       &_can_ops,
                       &drv_can0);

#endif

#ifdef BSP_USING_CAN1
    drv_can1.can_handle.Config.InstanceId = 1;
    drv_can1.device.config.ticks = 20000;
    drv_can1.device.config.baud_rate = 1000000;
    drv_can1.device.config.sndboxnumber = 1;
    drv_can1.device.config.msgboxsz = RT_CANMSG_BOX_SZ;
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
