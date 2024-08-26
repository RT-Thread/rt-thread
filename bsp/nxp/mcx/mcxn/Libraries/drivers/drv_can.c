/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-24     YangXi       the first version.
 */

#include <rtdevice.h>

#ifdef RT_USING_CAN

#include "fsl_common.h"
#include "fsl_flexcan.h"

#define TX_MB_IDX       (6)
#define RX_MB_COUNT     (1)
static flexcan_frame_t frame[RX_MB_COUNT];    /* one frame buffer per RX MB */
static rt_uint32_t filter_mask = 0;


enum
{
#ifdef BSP_USING_CAN0
    CAN0_INDEX,
#endif
#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
};

struct imxrt_can
{
    char                    *name;
    CAN_Type                *base;
    IRQn_Type               irqn;
    uint32_t                instance;
    clock_div_name_t        clock_div_name;
    clock_attach_id_t       clock_attach_id;
    flexcan_handle_t        handle;
    struct rt_can_device    can_dev;
};

struct imxrt_can flexcans[] =
{
#ifdef BSP_USING_CAN0
    {
        .name = "can0",
        .base = CAN0,
        .instance = 0,
        .irqn = CAN0_IRQn,
        .clock_div_name = kCLOCK_DivFlexcan0Clk,
        .clock_attach_id = kFRO_HF_to_FLEXCAN0,
    },
#endif
#ifdef BSP_USING_CAN1
    {
        .name = "can1",
        .base = CAN1,
        .instance = 1,
        .irqn = CAN1_IRQn,
        .clock_div_name = kCLOCK_DivFlexcan1Clk,
        .clock_attach_id = kFRO_HF_to_FLEXCAN1,
    },
#endif
};



static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint64_t result, void *userData)
{
    struct imxrt_can *can;
    flexcan_mb_transfer_t rxXfer;

    can = (struct imxrt_can *)userData;

    switch (status)
    {
        case kStatus_FLEXCAN_RxIdle:
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_RX_IND | result << 8);
            rxXfer.frame = &frame[result - 1];
            rxXfer.mbIdx = result;
            FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
            break;

        case kStatus_FLEXCAN_TxIdle:
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_TX_DONE | result << 8);
            break;
        default:
            break;
    }
}


static rt_err_t can_cfg(struct rt_can_device *can_dev, struct can_configure *cfg)
{
    struct imxrt_can *can =  (struct imxrt_can *)can_dev->parent.user_data;
    flexcan_config_t config;
    rt_uint32_t res = RT_EOK;
    flexcan_rx_mb_config_t mbConfig;
    flexcan_mb_transfer_t rxXfer;
    rt_uint8_t i, mailbox;

    FLEXCAN_GetDefaultConfig(&config);
    config.baudRate = cfg->baud_rate;
    config.enableIndividMask = true;    /* one filter per MB */
    config.disableSelfReception = true;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        /* default mode */
        break;
    case RT_CAN_MODE_LISTEN:
        break;
    case RT_CAN_MODE_LOOPBACK:
        config.enableLoopBack = true;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        break;
    }

    flexcan_timing_config_t timing_config;
    rt_memset(&timing_config, 0, sizeof(flexcan_timing_config_t));

    if(FLEXCAN_CalculateImprovedTimingValues(can->base, config.baudRate, CLOCK_GetFlexcanClkFreq(can->instance), &timing_config))
    {
        /* Update the improved timing configuration*/
        rt_memcpy(&(config.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
    }
    else
    {
        //rt_kprintf("No found Improved Timing Configuration. Just used default configuration\n");
    }

    FLEXCAN_Init(can->base, &config, CLOCK_GetFlexcanClkFreq(can->instance));
    FLEXCAN_TransferCreateHandle(can->base, &can->handle, flexcan_callback, can);

    /* init RX_MB_COUNT RX MB to default status */
    mbConfig.format = kFLEXCAN_FrameFormatStandard;  /* standard ID */
    mbConfig.type = kFLEXCAN_FrameTypeData;          /* data frame */
    mbConfig.id = FLEXCAN_ID_STD(0);                 /* default ID is 0 */
    for (i = 0; i < RX_MB_COUNT; i++)
    {
        /* the used MB index from 1 to RX_MB_COUNT */
        mailbox = i + 1;

        /* all ID bit in the filter is "don't care" */
        FLEXCAN_SetRxIndividualMask(can->base, mailbox, FLEXCAN_RX_MB_STD_MASK(0, 0, 0));
        FLEXCAN_SetRxMbConfig(can->base, mailbox, &mbConfig, true);
        /* one frame buffer per MB */
        rxXfer.frame = &frame[i];
        rxXfer.mbIdx = mailbox;
        FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
    }

    return res;
}


static rt_err_t can_control(struct rt_can_device *can_dev, int cmd, void *arg)
{
    struct imxrt_can *can;
    rt_uint32_t argval, mask;
    rt_uint32_t res = RT_EOK;
    flexcan_rx_mb_config_t mbConfig;
    struct rt_can_filter_config  *cfg;
    struct rt_can_filter_item *item;
    rt_uint8_t i, count, index;

    RT_ASSERT(can_dev != RT_NULL);

    can = (struct imxrt_can *)can_dev->parent.user_data;
    RT_ASSERT(can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            mask = kFLEXCAN_RxWarningInterruptEnable;
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            mask = kFLEXCAN_TxWarningInterruptEnable;
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            mask = kFLEXCAN_ErrorInterruptEnable;
        }
        FLEXCAN_EnableInterrupts(can->base, mask);
        NVIC_SetPriority(can->irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
        EnableIRQ(can->irqn);
        break;
    case RT_DEVICE_CTRL_CLR_INT:
        /* each CAN device have one IRQ number. */
        DisableIRQ(can->irqn);
        break;
    case RT_CAN_CMD_SET_FILTER:
        cfg = (struct rt_can_filter_config *)arg;
        item = cfg->items;
        count = cfg->count;

        if (filter_mask == 0xffffffff)
        {
            rt_kprintf("%s filter is full!\n", can->name);
            res = -RT_ERROR;
            break;
        }
        else if (filter_mask == 0)
        {
            /* deinit all init RX MB */
            for (i = 0; i < RX_MB_COUNT; i++)
            {
                FLEXCAN_SetRxMbConfig(can->base, i + 1, RT_NULL, false);
            }
        }

        while (count)
        {
            if (item->ide)
            {
                mbConfig.format = kFLEXCAN_FrameFormatExtend;
                mbConfig.id = FLEXCAN_ID_EXT(item->id);
                mask = FLEXCAN_RX_MB_EXT_MASK(item->mask, 0, 0);
            }
            else
            {
                mbConfig.format = kFLEXCAN_FrameFormatStandard;
                mbConfig.id = FLEXCAN_ID_STD(item->id);
                mask = FLEXCAN_RX_MB_STD_MASK(item->mask, 0, 0);
            }

            if (item->rtr)
            {
                mbConfig.type = kFLEXCAN_FrameTypeRemote;
            }
            else
            {
                mbConfig.type = kFLEXCAN_FrameTypeData;
            }

            /* user does not specify hdr index,set hdr_bank from RX MB 1 */
            if (item->hdr_bank == -1)
            {

                for (i = 0; i < 32; i++)
                {
                    if (!(filter_mask & (1 << i)))
                    {
                        index = i;
                        break;
                    }
                }
            }
            else    /* use user specified hdr_bank */
            {
                if (filter_mask & (1 << item->hdr_bank))
                {
                    res = -RT_ERROR;
                    rt_kprintf("%s hdr%d filter already set!\n", can->name, item->hdr_bank);
                    break;
                }
                else
                {
                    index = item->hdr_bank;
                }
            }

            /* RX MB index from 1 to 32,hdr index 0~31 map RX MB index 1~32. */
            FLEXCAN_SetRxIndividualMask(can->base, index + 1, mask);
            FLEXCAN_SetRxMbConfig(can->base, index + 1, &mbConfig, true);
            filter_mask |= 1 << index;

            item++;
            count--;
        }

        break;

    case RT_CAN_CMD_SET_BAUD:
        {
            struct can_configure *cfg = (struct can_configure *)arg;
            if (cfg != RT_NULL)
            {
                can->can_dev.config = *cfg;
                can_cfg(can_dev, cfg);
                res = RT_EOK;
            }
            else
            {
                res = -RT_ERROR;
            }
            break;
        }
    case RT_CAN_CMD_SET_MODE:
        res = -RT_ERROR;
        break;

    case RT_CAN_CMD_SET_PRIV:
        res = -RT_ERROR;
        break;
    case RT_CAN_CMD_GET_STATUS:
        FLEXCAN_GetBusErrCount(can->base, (rt_uint8_t *)(&can->can_dev.status.snderrcnt), (rt_uint8_t *)(&can->can_dev.status.rcverrcnt));
        rt_memcpy(arg, &can->can_dev.status, sizeof(can->can_dev.status));
        break;
    default:
        res = -RT_ERROR;
        break;
    }

    return res;
}

static rt_ssize_t can_send(struct rt_can_device *can_dev, const void *buf, rt_uint32_t boxno)
{
    struct imxrt_can *can;
    struct rt_can_msg *msg;
    status_t ret;
    flexcan_frame_t frame;
    flexcan_mb_transfer_t txXfer;

    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    can = (struct imxrt_can *)can_dev->parent.user_data;
    msg = (struct rt_can_msg *) buf;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(msg != RT_NULL);

    FLEXCAN_SetTxMbConfig(can->base, boxno, true);

    if (RT_CAN_STDID == msg->ide)
    {
        frame.id = FLEXCAN_ID_STD(msg->id);
        frame.format = kFLEXCAN_FrameFormatStandard;
    }
    else if (RT_CAN_EXTID == msg->ide)
    {
        frame.id = FLEXCAN_ID_EXT(msg->id);
        frame.format = kFLEXCAN_FrameFormatExtend;
    }

    if (RT_CAN_DTR == msg->rtr)
    {
        frame.type = kFLEXCAN_FrameTypeData;
    }
    else if (RT_CAN_RTR == msg->rtr)
    {
        frame.type = kFLEXCAN_FrameTypeRemote;
    }

    frame.length = msg->len;
    frame.dataByte0 = msg->data[0];
    frame.dataByte1 = msg->data[1];
    frame.dataByte2 = msg->data[2];
    frame.dataByte3 = msg->data[3];
    frame.dataByte4 = msg->data[4];
    frame.dataByte5 = msg->data[5];
    frame.dataByte6 = msg->data[6];
    frame.dataByte7 = msg->data[7];

    txXfer.mbIdx = boxno;
    txXfer.frame = &frame;

    ret = FLEXCAN_TransferSendNonBlocking(can->base, &can->handle, &txXfer);
    switch (ret)
    {
    case kStatus_Success:
        ret = RT_EOK;
        break;
    case kStatus_Fail:
        ret = -RT_ERROR;
        break;
    case kStatus_FLEXCAN_TxBusy:
        ret = -RT_EBUSY;
        break;
    }

    return (rt_ssize_t)ret;
}

static rt_ssize_t can_recv(struct rt_can_device *can_dev, void *buf, rt_uint32_t boxno)
{
    struct imxrt_can *can;
    struct rt_can_msg *pmsg;
    rt_uint8_t index;

    RT_ASSERT(can_dev != RT_NULL);

    can = (struct imxrt_can *)can_dev->parent.user_data;
    pmsg = (struct rt_can_msg *) buf;
    RT_ASSERT(can != RT_NULL);

    index = boxno - 1;

    if (frame[index].format == kFLEXCAN_FrameFormatStandard)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = frame[index].id >> CAN_ID_STD_SHIFT;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = frame[index].id >> CAN_ID_EXT_SHIFT;
    }

    if (frame[index].type == kFLEXCAN_FrameTypeData)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else if (frame[index].type == kFLEXCAN_FrameTypeRemote)
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    pmsg->hdr_index = index;      /* one hdr filter per MB */
    pmsg->len = frame[index].length;
    pmsg->data[0] = frame[index].dataByte0;
    pmsg->data[1] = frame[index].dataByte1;
    pmsg->data[2] = frame[index].dataByte2;
    pmsg->data[3] = frame[index].dataByte3;
    pmsg->data[4] = frame[index].dataByte4;
    pmsg->data[5] = frame[index].dataByte5;
    pmsg->data[6] = frame[index].dataByte6;
    pmsg->data[7] = frame[index].dataByte7;

    return 0;
}



static struct rt_can_ops imxrt_can_ops =
{
    .configure    = can_cfg,
    .control      = can_control,
    .sendmsg      = can_send,
    .recvmsg      = can_recv,
};


int rt_hw_can_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    struct can_configure config = CANDEFAULTCONFIG;

    config.privmode = 0;
    config.ticks = 50;
    config.sndboxnumber = 1;
    config.msgboxsz = RX_MB_COUNT;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = RX_MB_COUNT;          /* filter count,one filter per MB */
#endif

    for (i = 0; i < sizeof(flexcans) / sizeof(flexcans[0]); i++)
    {
        flexcans[i].can_dev.config = config;
        CLOCK_SetClkDiv(flexcans[i].clock_div_name, 1u);
        CLOCK_AttachClk(flexcans[i].clock_attach_id);

        ret = rt_hw_can_register(&flexcans[i].can_dev, flexcans[i].name, &imxrt_can_ops, &flexcans[i]);
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /*RT_USING_CAN */
