/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-06-27     misonyo     the first version.
 * 2022-09-01     xjy198903   add support for imxrt1170
 * 2026-08-13     nxp-ran     add support for imxrt1180 (SOC_IMXRT1180_SERIES)
 * 2026-11-11     wdfk-prog   adapt FlexCAN to the Generic CAN framework
 */

#include <rtthread.h>
#ifdef BSP_USING_CAN

#include <rtdevice.h>
#include "drv_can.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_flexcan.h"

#define LOG_TAG "drv.can"
#include <drv_log.h>

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
#error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

#define RX_MB_COUNT 32
/** @brief Number of independent Classic CAN TX mailboxes exposed to Generic CAN. */
#define TX_MB_COUNT 16
/** @brief RX interrupt bits for physical FlexCAN MB1..MB32. */
#define RX_MB_IRQ_MASK ((((uint64_t)1U << RX_MB_COUNT) - 1U) << 1U)
/** @brief TX interrupt bits for physical FlexCAN MB48..MB63. */
#define TX_MB_IRQ_MASK ((((uint64_t)1U << TX_MB_COUNT) - 1U) << (64U - TX_MB_COUNT))

#if defined(SOC_IMXRT1170_SERIES) || defined(SOC_IMXRT1180_SERIES)
#define USE_IMPROVED_TIMING_CONFIG (1U)
#endif

enum
{
#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
#ifdef BSP_USING_CAN2
    CAN2_INDEX,
#endif
#ifdef BSP_USING_CAN3
    CAN3_INDEX,
#endif
};

/** @brief Per-controller hardware handle, RX storage, and filter/STOP state. */
struct imxrt_can
{
    char *name;
    CAN_Type *base;
    IRQn_Type irqn;
    flexcan_handle_t handle;
    struct rt_can_device can_dev;
    flexcan_frame_t frame[RX_MB_COUNT]; /**< Frames held until the corresponding RX ISR copies them. */
    rt_uint32_t filter_mask;            /**< Allocated RX filter banks, local to this controller. */
    rt_bool_t configured;               /**< True only after a successful hardware configuration. */
};

struct imxrt_can flexcans[] = {
#ifdef BSP_USING_CAN1
    {
        .name = "can1",
        .base = CAN1,
        .irqn = CAN1_IRQn,
    },
#endif
#ifdef BSP_USING_CAN2
    {
        .name = "can2",
        .base = CAN2,
        .irqn = CAN2_IRQn,
    },
#endif
#ifdef BSP_USING_CAN3
    {
        .name = "can3",
        .base = CAN3,
        .irqn = CAN3_IRQn,
    },
#endif
};

uint32_t GetCanSrcFreq(CAN_Type *can_base)
{
    uint32_t freq;
#if defined(SOC_IMXRT1170_SERIES) || defined(SOC_IMXRT1180_SERIES)
    uint32_t base = (uint32_t)can_base;
    switch (base)
    {
    case CAN1_BASE:
        freq = (CLOCK_GetRootClockFreq(kCLOCK_Root_Can1) / 100000U) * 100000U;
        break;
    case CAN2_BASE:
        freq = (CLOCK_GetRootClockFreq(kCLOCK_Root_Can2) / 100000U) * 100000U;
        break;
    case CAN3_BASE:
        freq = (CLOCK_GetRootClockFreq(kCLOCK_Root_Can3) / 100000U) * 100000U;
        break;
    default:
        freq = (CLOCK_GetRootClockFreq(kCLOCK_Root_Can3) / 100000U) * 100000U;
        break;
    }
#else
    freq = (CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 6) / (CLOCK_GetDiv(kCLOCK_CanDiv) + 1U);
#endif
    return freq;
}

/**
 * @brief Deinitialize one FlexCAN controller after TX/RX have been quiesced.
 * @param can Controller instance whose outstanding hardware TX must be stopped.
 * @return RT_EOK after SDK deinitialization, or -RT_ERROR if MDIS cannot be cleared.
 */
static rt_err_t can_stop_hw(struct imxrt_can *can)
{
    if (!can->configured)
    {
        return RT_EOK;
    }

    if ((can->base->MCR & CAN_MCR_MDIS_MASK) != 0U)
    {
        (void)FLEXCAN_Enable(can->base, true);
        if ((can->base->MCR & CAN_MCR_MDIS_MASK) != 0U)
        {
            return -RT_ERROR;
        }
    }

    FLEXCAN_Deinit(can->base);
    can->configured = RT_FALSE;
    return RT_EOK;
}

#if defined(SOC_IMXRT1170_SERIES) || defined(SOC_IMXRT1180_SERIES)
static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint64_t result, void *userData)
#else
static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint32_t result, void *userData)
#endif
{
    struct imxrt_can *can;
    flexcan_mb_transfer_t rxXfer;

    can = (struct imxrt_can *)userData;
    switch (status)
    {
    case kStatus_FLEXCAN_RxIdle:
        if (result < 1U || result > RX_MB_COUNT)
        {
            break;
        }
        rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_RX_IND | ((rt_uint32_t)result << 8));
        rxXfer.frame = &can->frame[result - 1U];
        rxXfer.mbIdx = (rt_uint8_t)result;
        FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
        break;

    case kStatus_FLEXCAN_TxSwitchToRx:
        if (result < 64U - TX_MB_COUNT || result > 63U)
        {
            break;
        }
        /* An RTR request turns the MB into RX; restore TX before releasing its slot. */
        FLEXCAN_TransferAbortReceive(base, handle, (rt_uint8_t)result);
        FLEXCAN_SetTxMbConfig(base, (rt_uint8_t)result, true);
        /* fall through */
    case kStatus_FLEXCAN_TxIdle:
        if (result >= 64U - TX_MB_COUNT && result <= 63U)
        {
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_TX_DONE | ((rt_uint32_t)(63U - result) << 8));
        }
        break;

    case kStatus_FLEXCAN_ErrorStatus:
    {
        /* SDK result is an ESR1 status snapshot, never a TX mailbox index. */
        rt_uint32_t error_flags = (rt_uint32_t)result;
        rt_uint32_t error_type = 0U;

        /* A Generic error event holds one type; drain all set ESR1 protocol bits. */
        do
        {
            error_type = 0U;
            if ((error_flags & kFLEXCAN_StuffingError) != 0U)
            {
                error_type = RT_CAN_BUS_BIT_PAD_ERR;
                error_flags &= ~kFLEXCAN_StuffingError;
            }
            else if ((error_flags & kFLEXCAN_FormError) != 0U)
            {
                error_type = RT_CAN_BUS_FORMAT_ERR;
                error_flags &= ~kFLEXCAN_FormError;
            }
            else if ((error_flags & kFLEXCAN_AckError) != 0U)
            {
                error_type = RT_CAN_BUS_ACK_ERR;
                error_flags &= ~kFLEXCAN_AckError;
            }
            else if ((error_flags & kFLEXCAN_Bit1Error) != 0U)
            {
                error_type = RT_CAN_BUS_IMPLICIT_BIT_ERR;
                error_flags &= ~kFLEXCAN_Bit1Error;
            }
            else if ((error_flags & kFLEXCAN_Bit0Error) != 0U)
            {
                error_type = RT_CAN_BUS_EXPLICIT_BIT_ERR;
                error_flags &= ~kFLEXCAN_Bit0Error;
            }
            else if ((error_flags & kFLEXCAN_CrcError) != 0U)
            {
                error_type = RT_CAN_BUS_CRC_ERR;
                error_flags &= ~kFLEXCAN_CrcError;
            }

            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_ERR | (error_type << 8));
        } while ((error_flags & (kFLEXCAN_StuffingError | kFLEXCAN_FormError |
                                 kFLEXCAN_AckError | kFLEXCAN_Bit1Error |
                                 kFLEXCAN_Bit0Error | kFLEXCAN_CrcError)) != 0U);
        break;
    }

    case kStatus_FLEXCAN_WakeUp:
    default:
        break;
    }
}

static rt_err_t can_cfg(struct rt_can_device *can_dev, struct can_configure *cfg)
{
    struct imxrt_can *can;
    flexcan_config_t config;
    rt_err_t res;
    flexcan_rx_mb_config_t mbConfig;
    flexcan_mb_transfer_t rxXfer;
    rt_uint8_t i, mailbox;
    /* Prevent SDK handle creation from exposing interrupts before initialization finishes. */
    rt_base_t irq_level;
    /* Preserve controller error IRQ enables across a quiesced reconfiguration. */
    rt_uint32_t error_irq_mask = 0U;

    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    can = (struct imxrt_can *)can_dev->parent.user_data;
    RT_ASSERT(can != RT_NULL);

    if (cfg->sndboxnumber != TX_MB_COUNT)
    {
        return -RT_EINVAL;
    }
#ifdef RT_CAN_USING_HDR
    if (cfg->maxhdr > RX_MB_COUNT)
    {
        return -RT_EINVAL;
    }
#endif /* RT_CAN_USING_HDR */
#ifdef RT_CAN_USING_CANFD
    if (cfg->enable_canfd != 0U)
    {
        return -RT_ENOSYS;
    }
#endif /* RT_CAN_USING_CANFD */

    if (can->configured)
    {
        error_irq_mask = can->base->CTRL1 &
                         (kFLEXCAN_BusOffInterruptEnable | kFLEXCAN_ErrorInterruptEnable |
                          kFLEXCAN_RxWarningInterruptEnable | kFLEXCAN_TxWarningInterruptEnable);
    }
    DisableIRQ(can->irqn);
    res = can_stop_hw(can);
    if (res != RT_EOK)
    {
        return res;
    }

    FLEXCAN_GetDefaultConfig(&config);
    config.baudRate = cfg->baud_rate;
    config.maxMbNum = 64;               /* all series have 64 MB */
    config.enableIndividMask = true;    /* one filter per MB */
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

#if defined(SOC_IMXRT1170_SERIES) || defined(SOC_IMXRT1180_SERIES)
    flexcan_timing_config_t timing_config;
    rt_memset(&timing_config, 0, sizeof(flexcan_timing_config_t));

    if (FLEXCAN_CalculateImprovedTimingValues(can->base, config.baudRate, GetCanSrcFreq(can->base), &timing_config))
    {
        /* Update the improved timing configuration */
        rt_memcpy(&(config.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
    }
    else
    {
        LOG_E("No found Improved Timing Configuration. Just used default configuration\n");
    }
#endif

    FLEXCAN_Init(can->base, &config, GetCanSrcFreq(can->base));
    /* The SDK can enable NVIC while creating its handle; keep it masked until ready. */
    irq_level = rt_hw_interrupt_disable();
    FLEXCAN_TransferCreateHandle(can->base, &can->handle, flexcan_callback, can);
    DisableIRQ(can->irqn);
    rt_hw_interrupt_enable(irq_level);

    /* Configure TX MBs once; the send path must never reset an occupied MB. */
    for (i = 0; i < TX_MB_COUNT; i++)
    {
        FLEXCAN_SetTxMbConfig(can->base, 63U - i, true);
    }

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
        rxXfer.frame = &can->frame[i];
        rxXfer.mbIdx = mailbox;
        FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
    }

    /* Generic owns RX admission; SDK TX submits will enable their own MB IRQs. */
    FLEXCAN_DisableMbInterrupts(can->base, RX_MB_IRQ_MASK | TX_MB_IRQ_MASK);
    if (error_irq_mask != 0U)
    {
        FLEXCAN_EnableInterrupts(can->base, error_irq_mask);
    }
    NVIC_ClearPendingIRQ(can->irqn);
    can->filter_mask = 0U;
    can->configured = RT_TRUE;
    can_dev->config = *cfg;
    if (can_dev->can_rx != RT_NULL || can_dev->can_tx != RT_NULL)
    {
        EnableIRQ(can->irqn);
    }

    return RT_EOK;
}

static rt_err_t can_control(struct rt_can_device *can_dev, int cmd, void *arg)
{
    struct imxrt_can *can;
    rt_uint32_t argval, mask;
    rt_err_t res = RT_EOK;
    flexcan_rx_mb_config_t mbConfig;
    /* Re-arm selected RX MBs after replacing their hardware filters. */
    flexcan_mb_transfer_t rxXfer;
    struct rt_can_filter_config *cfg;
    struct rt_can_filter_item *item;
    rt_uint8_t i, count, index;

    RT_ASSERT(can_dev != RT_NULL);

    can = (struct imxrt_can *)can_dev->parent.user_data;
    RT_ASSERT(can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
        if (!can->configured)
        {
            res = -RT_ERROR;
            break;
        }
        argval = (rt_uint32_t)(rt_ubase_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            FLEXCAN_EnableMbInterrupts(can->base, RX_MB_IRQ_MASK);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            /* The SDK enables the selected TX MB interrupt on hardware acceptance. */
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            mask = kFLEXCAN_BusOffInterruptEnable | kFLEXCAN_ErrorInterruptEnable |
                   kFLEXCAN_RxWarningInterruptEnable | kFLEXCAN_TxWarningInterruptEnable;
            FLEXCAN_EnableInterrupts(can->base, mask);
        }
        else
        {
            res = -RT_ERROR;
            break;
        }
        NVIC_SetPriority(can->irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
        EnableIRQ(can->irqn);
        break;

    case RT_DEVICE_CTRL_CLR_INT:
        if (!can->configured)
        {
            break;
        }
        argval = (rt_uint32_t)(rt_ubase_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            FLEXCAN_DisableMbInterrupts(can->base, RX_MB_IRQ_MASK);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            FLEXCAN_DisableMbInterrupts(can->base, TX_MB_IRQ_MASK);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            mask = kFLEXCAN_BusOffInterruptEnable | kFLEXCAN_ErrorInterruptEnable |
                   kFLEXCAN_RxWarningInterruptEnable | kFLEXCAN_TxWarningInterruptEnable;
            FLEXCAN_DisableInterrupts(can->base, mask);
        }
        else
        {
            res = -RT_ERROR;
        }
        break;

    case RT_CAN_CMD_SET_FILTER:
        if (!can->configured)
        {
            res = -RT_ERROR;
            break;
        }
        cfg = (struct rt_can_filter_config *)arg;
        if (cfg == RT_NULL || (cfg->count != 0U && cfg->items == RT_NULL))
        {
            res = -RT_EINVAL;
            break;
        }
        item = cfg->items;
        count = cfg->count;

        if (count != 0U && can->filter_mask == 0xffffffffU)
        {
            LOG_E("%s filter is full!\n", can->name);
            res = -RT_ERROR;
            break;
        }
        else if (count != 0U && can->filter_mask == 0U)
        {
            /* Stop the default RX transfers before programming explicit filters. */
            for (i = 0; i < RX_MB_COUNT; i++)
            {
                FLEXCAN_TransferAbortReceive(can->base, &can->handle, i + 1U);
                FLEXCAN_SetRxMbConfig(can->base, i + 1U, RT_NULL, false);
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
                index = RX_MB_COUNT;
                for (i = 0; i < RX_MB_COUNT; i++)
                {
                    if (!(can->filter_mask & (1UL << i)))
                    {
                        index = i;
                        break;
                    }
                }
                if (index >= RX_MB_COUNT)
                {
                    res = -RT_ERROR;
                    break;
                }
            }
            else    /* use user specified hdr_bank */
            {
                if (item->hdr_bank < 0 || item->hdr_bank >= RX_MB_COUNT)
                {
                    res = -RT_EINVAL;
                    break;
                }
                if (can->filter_mask & (1UL << item->hdr_bank))
                {
                    res = -RT_ERROR;
                    LOG_E("%s hdr%d filter already set!\n", can->name, item->hdr_bank);
                    break;
                }
                index = (rt_uint8_t)item->hdr_bank;
            }

            /* RX MB index from 1 to 32,hdr index 0~31 map RX MB index 1~32. */
            FLEXCAN_SetRxIndividualMask(can->base, index + 1U, mask);
            FLEXCAN_SetRxMbConfig(can->base, index + 1U, &mbConfig, true);
            rxXfer.frame = &can->frame[index];
            rxXfer.mbIdx = index + 1U;
            FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
            /* Generic resumes RX only after its software routing state is published. */
            FLEXCAN_DisableMbInterrupts(can->base, (uint64_t)1U << (index + 1U));
            can->filter_mask |= 1UL << index;

            item++;
            count--;
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
        res = -RT_ERROR;
        break;
    case RT_CAN_CMD_SET_MODE:
        res = -RT_ERROR;
        break;

    case RT_CAN_CMD_SET_PRIV:
        res = -RT_ERROR;
        break;
    case RT_CAN_CMD_GET_STATUS:
        if (can->configured)
        {
            FLEXCAN_GetBusErrCount(can->base, (rt_uint8_t *)(&can->can_dev.status.snderrcnt),
                                   (rt_uint8_t *)(&can->can_dev.status.rcverrcnt));
        }
        rt_memcpy(arg, &can->can_dev.status, sizeof(can->can_dev.status));
        break;
    case RT_CAN_CMD_START:
        if ((rt_ubase_t)arg == 0U)
        {
            DisableIRQ(can->irqn);
            res = can_stop_hw(can);
            if (res == RT_EOK)
            {
                NVIC_ClearPendingIRQ(can->irqn);
            }
        }
        else if (!can->configured)
        {
            res = can_cfg(can_dev, &can_dev->config);
        }
        break;
    case RT_CAN_CMD_ABORT_TX:
        /* The SDK abort request cannot guarantee a later per-mailbox TX_FAIL. */
        res = -RT_ENOSYS;
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
    rt_uint8_t sendMB;

    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    can = (struct imxrt_can *)can_dev->parent.user_data;
    msg = (struct rt_can_msg *)buf;
    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(msg != RT_NULL);

    if (boxno >= TX_MB_COUNT)
    {
        return -RT_EINVAL;
    }
    if (!can->configured)
    {
        return -RT_ERROR;
    }
#ifdef RT_CAN_USING_CANFD
    if (msg->fd_frame != 0U)
    {
        return -RT_ENOSYS;
    }
#endif /* RT_CAN_USING_CANFD */
    if (msg->len > 8U)
    {
        return -RT_EINVAL;
    }

    /* Logical slots 0..15 map to physical TX MB63..48. */
    sendMB = 63U - boxno;

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

    txXfer.mbIdx = sendMB;
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
    default:
        ret = -RT_ERROR;
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
    pmsg = (struct rt_can_msg *)buf;
    RT_ASSERT(can != RT_NULL);

    if (boxno < 1U || boxno > RX_MB_COUNT)
    {
        return -RT_EINVAL;
    }
    index = boxno - 1U;

    if (can->frame[index].format == kFLEXCAN_FrameFormatStandard)
    {
        pmsg->ide = RT_CAN_STDID;
        pmsg->id = can->frame[index].id >> CAN_ID_STD_SHIFT;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
        pmsg->id = can->frame[index].id >> CAN_ID_EXT_SHIFT;
    }

    if (can->frame[index].type == kFLEXCAN_FrameTypeData)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else if (can->frame[index].type == kFLEXCAN_FrameTypeRemote)
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    pmsg->hdr_index = index;      /* one hdr filter per MB */
    pmsg->len = can->frame[index].length;
    pmsg->data[0] = can->frame[index].dataByte0;
    pmsg->data[1] = can->frame[index].dataByte1;
    pmsg->data[2] = can->frame[index].dataByte2;
    pmsg->data[3] = can->frame[index].dataByte3;
    pmsg->data[4] = can->frame[index].dataByte4;
    pmsg->data[5] = can->frame[index].dataByte5;
    pmsg->data[6] = can->frame[index].dataByte6;
    pmsg->data[7] = can->frame[index].dataByte7;

    return 0;
}

/**
 * @brief Attempt one immediate TX on a free physical FlexCAN mailbox.
 *
 * The SDK guards in-flight hardware MBs; sndchange also prevents reusing a
 * completed blocking slot before Generic has finished retiring its waiter.
 *
 * @param can_dev Generic CAN device with 16 TX slots.
 * @param buf Classic CAN frame to submit.
 * @param mailbox Output logical TX slot on successful hardware acceptance.
 * @return RT_EOK on acceptance, -RT_EBUSY when all slots are occupied, or another error.
 */
static rt_ssize_t can_send_nonblocking(struct rt_can_device *can_dev, const void *buf, rt_uint32_t *mailbox)
{
    /* Candidate Generic TX slot, mapped to physical MB63..MB48 by can_send(). */
    rt_uint32_t boxno;
    /* Immediate SDK submission outcome; completion is reported only in IRQ context. */
    rt_ssize_t ret;

    if (mailbox == RT_NULL)
    {
        return -RT_EINVAL;
    }

    for (boxno = 0; boxno < can_dev->config.sndboxnumber && boxno < TX_MB_COUNT; boxno++)
    {
        /* Blocking slot ownership outlives a TX completion until its waiter retires. */
        if ((can_dev->status.sndchange & (1UL << boxno)) != 0U)
        {
            continue;
        }
        ret = can_send(can_dev, buf, boxno);
        if (ret == RT_EOK)
        {
            *mailbox = boxno;
            return RT_EOK;
        }
        if (ret != -RT_EBUSY)
        {
            return ret;
        }
    }

    return -RT_EBUSY;
}

static struct rt_can_ops imxrt_can_ops = {
    .configure = can_cfg,
    .control = can_control,
    .sendmsg = can_send,
    .recvmsg = can_recv,
    .sendmsg_nonblocking = can_send_nonblocking,
};

int rt_hw_can_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    struct can_configure config = CANDEFAULTCONFIG;

    config.privmode = 0;
    config.ticks = 50;
    config.sndboxnumber = TX_MB_COUNT;             /* send Mailbox count */
    config.msgboxsz = RX_MB_COUNT;        /* RX msg buffer count */
#ifdef RT_CAN_USING_HDR
    config.maxhdr = RX_MB_COUNT;          /* filter count,one filter per MB */
#endif

    for (i = 0; i < sizeof(flexcans) / sizeof(flexcans[0]); i++)
    {
        flexcans[i].can_dev.config = config;
        ret = rt_hw_can_register(&flexcans[i].can_dev, flexcans[i].name, &imxrt_can_ops, &flexcans[i]);
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */
