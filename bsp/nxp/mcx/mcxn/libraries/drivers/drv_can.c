/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-24     YangXi       the first version.
 * 2026-11-11     wdfk-prog    support three FlexCAN TX mailboxes in Generic CAN.
 */

#include <rtdevice.h>

#ifdef RT_USING_CAN

#include "fsl_common.h"
#include "fsl_flexcan.h"

/** @brief First physical FlexCAN TX MB, mapped to Generic TX slot 0. */
#define TX_MB_IDX       (6U)
/** @brief Number of independent hardware TX MBs visible to Generic CAN. */
#define TX_MB_COUNT     (3U)
/** @brief First physical RX MB, kept outside the TX mailbox range. */
#define RX_MB_IDX       (1U)
/** @brief Number of hardware RX MBs used by this Classic CAN driver. */
#define RX_MB_COUNT     (1U)


enum
{
#ifdef BSP_USING_CAN0
    CAN0_INDEX,
#endif
#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
};

/**
 * @brief Per-controller FlexCAN resources and receive/filter runtime state.
 */
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
    flexcan_frame_t         frame[RX_MB_COUNT]; /**< RX frames retained until Generic reads them in ISR. */
    rt_uint32_t             filter_mask;       /**< RX filter allocation bitmap, reset by configure. */
    rt_bool_t               configured;        /**< True only while FlexCAN hardware has been initialized. */
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


/**
 * @brief Deinitialize one FlexCAN controller and suppress all previous TX terminals.
 * @param can Controller instance owning the SDK handle and physical MBs.
 * @return RT_EOK on confirmed hardware stop, or -RT_ERROR when hardware cannot be enabled for reset.
 */
static rt_err_t can_stop_hw(struct imxrt_can *can)
{
    if (!can->configured)
    {
        return RT_EOK;
    }
    /* Deinit requires MDIS cleared; otherwise old TX ownership must be retained. */
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

/**
 * @brief Forward RX, TX completion and controller error events to Generic CAN.
 *
 * TX events identify Generic slots 0..2 rather than the physical FlexCAN MBs 6..8.
 * A remote transmit switches its physical MB to RX; its TX role must be restored
 * before publishing the only TX_DONE terminal for that logical slot.
 * ErrorStatus reports protocol errors from the SDK ESR1 snapshot individually;
 * controller-level warnings do not terminate or release any TX mailbox.
 *
 * @param base FlexCAN register base returned by the SDK.
 * @param handle SDK transactional transfer handle.
 * @param status Transaction completion or controller status.
 * @param result Physical MB index for RX/TX, or ESR1 status flags for ErrorStatus.
 * @param userData Pointer to the controller instance.
 */
static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint64_t result, void *userData)
{
    struct imxrt_can *can;
    flexcan_mb_transfer_t rxXfer;

    can = (struct imxrt_can *)userData;

    switch (status)
    {
    case kStatus_FLEXCAN_RxIdle:
        if (result < RX_MB_IDX || result >= RX_MB_IDX + RX_MB_COUNT)
        {
            break;
        }
        rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_RX_IND | ((rt_uint32_t)result << 8));
        rxXfer.frame = &can->frame[result - RX_MB_IDX];
        rxXfer.mbIdx = (rt_uint8_t)result;
        FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
        break;

    case kStatus_FLEXCAN_TxSwitchToRx:
        if (result < TX_MB_IDX || result >= TX_MB_IDX + TX_MB_COUNT)
        {
            break;
        }
        FLEXCAN_TransferAbortReceive(base, handle, (rt_uint8_t)result);
        FLEXCAN_SetTxMbConfig(base, (rt_uint8_t)result, true);
        /* A remote TX changes its MB to RX; restore the TX role before retirement. */
        /* fall through */
    case kStatus_FLEXCAN_TxIdle:
        if (result >= TX_MB_IDX && result < TX_MB_IDX + TX_MB_COUNT)
        {
            rt_hw_can_isr(&can->can_dev,
                          RT_CAN_EVENT_TX_DONE | ((rt_uint32_t)(result - TX_MB_IDX) << 8));
        }
        break;
    case kStatus_FLEXCAN_ErrorStatus:
    {
        /* The SDK supplies an ESR1 snapshot, not a mailbox completion index. */
        rt_uint32_t error_flags = (rt_uint32_t)result;

        if ((error_flags & kFLEXCAN_StuffingError) != 0U)
        {
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_ERR | (RT_CAN_BUS_BIT_PAD_ERR << 8));
        }
        if ((error_flags & kFLEXCAN_FormError) != 0U)
        {
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_ERR | (RT_CAN_BUS_FORMAT_ERR << 8));
        }
        if ((error_flags & kFLEXCAN_AckError) != 0U)
        {
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_ERR | (RT_CAN_BUS_ACK_ERR << 8));
        }
        if ((error_flags & kFLEXCAN_Bit1Error) != 0U)
        {
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_ERR | (RT_CAN_BUS_IMPLICIT_BIT_ERR << 8));
        }
        if ((error_flags & kFLEXCAN_Bit0Error) != 0U)
        {
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_ERR | (RT_CAN_BUS_EXPLICIT_BIT_ERR << 8));
        }
        if ((error_flags & kFLEXCAN_CrcError) != 0U)
        {
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_ERR | (RT_CAN_BUS_CRC_ERR << 8));
        }
        if ((error_flags & (kFLEXCAN_StuffingError | kFLEXCAN_FormError |
                            kFLEXCAN_AckError | kFLEXCAN_Bit1Error |
                            kFLEXCAN_Bit0Error | kFLEXCAN_CrcError)) == 0U)
        {
            /* Bus-off/warning status does not establish a per-MB TX failure. */
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_ERR);
        }
        break;
    }
    default:
        break;
    }
}


/**
 * @brief Configure one Classic FlexCAN controller with three TX MBs and one RX MB.
 *
 * Controller reconfiguration is allowed only after Generic CAN has quiesced TX
 * and RX; the SDK handle is rebuilt with controller IRQ masked. Hardware filter
 * programming is reset and must be reapplied by the application when needed.
 *
 * @param can_dev Generic CAN device containing the current runtime state.
 * @param cfg Requested configuration; hardware TX slot count is fixed at three.
 * @return RT_EOK on success, -RT_EINVAL on unsupported layout, or a negative hardware error.
 */
static rt_err_t can_cfg(struct rt_can_device *can_dev, struct can_configure *cfg)
{
    struct imxrt_can *can = (struct imxrt_can *)can_dev->parent.user_data;
    flexcan_config_t config;
    flexcan_timing_config_t timing_config;
    flexcan_rx_mb_config_t mbConfig;
    flexcan_mb_transfer_t rxXfer;
    /* Protocol clock used for bit timing and FlexCAN initialization. */
    rt_uint32_t clk_freq;
    rt_uint8_t i, mailbox;
    /* Preserve the previous global IRQ mask while SDK handle creation runs. */
    rt_base_t irq_level;
    /* Hardware-stop result; an unsuccessful stop must not be reported as safe. */
    rt_err_t ret;
    /* Active FlexCAN error IRQ sources, independent of the shared NVIC enable. */
    rt_uint32_t error_irq_mask = 0U;

    if (cfg == RT_NULL || cfg->sndboxnumber != TX_MB_COUNT)
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
    ret = can_stop_hw(can);
    if (ret != RT_EOK)
    {
        return ret;
    }

    CLOCK_SetClkDiv(can->clock_div_name, 1u);
    CLOCK_AttachClk(can->clock_attach_id);
    clk_freq = CLOCK_GetFlexcanClkFreq(can->instance);
    if (clk_freq == 0U)
    {
        return -RT_ERROR;
    }

    FLEXCAN_GetDefaultConfig(&config);
    config.baudRate = cfg->baud_rate;
    /* MAXMB covers the last physical TX buffer MB8 (zero-based). */
    config.maxMbNum = TX_MB_IDX + TX_MB_COUNT;
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

    rt_memset(&timing_config, 0, sizeof(timing_config));
    if (FLEXCAN_CalculateImprovedTimingValues(can->base, config.baudRate, clk_freq, &timing_config))
    {
        rt_memcpy(&config.timingConfig, &timing_config, sizeof(timing_config));
    }

    FLEXCAN_Init(can->base, &config, clk_freq);

    /* The SDK temporarily enables NVIC when creating the transfer handle. */
    irq_level = rt_hw_interrupt_disable();
    FLEXCAN_TransferCreateHandle(can->base, &can->handle, flexcan_callback, can);
    DisableIRQ(can->irqn);
    rt_hw_interrupt_enable(irq_level);

    /* SetTxMbConfig aborts existing TX; do it only during controller initialization. */
    for (i = 0; i < TX_MB_COUNT; i++)
    {
        FLEXCAN_SetTxMbConfig(can->base, TX_MB_IDX + i, true);
    }

    mbConfig.format = kFLEXCAN_FrameFormatStandard;
    mbConfig.type = kFLEXCAN_FrameTypeData;
    mbConfig.id = FLEXCAN_ID_STD(0);
    for (i = 0; i < RX_MB_COUNT; i++)
    {
        mailbox = RX_MB_IDX + i;
        FLEXCAN_SetRxIndividualMask(can->base, mailbox, FLEXCAN_RX_MB_STD_MASK(0, 0, 0));
        FLEXCAN_SetRxMbConfig(can->base, mailbox, &mbConfig, true);
        rxXfer.frame = &can->frame[i];
        rxXfer.mbIdx = mailbox;
        FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
    }

    /* Re-init resets CTRL1; restore only error sources enabled before reconfigure. */
    if (error_irq_mask != 0U)
    {
        FLEXCAN_EnableInterrupts(can->base, error_irq_mask);
    }
    /* Generic RX/TX runtimes are published before their MB IRQ sources open. */
    FLEXCAN_DisableMbInterrupts(can->base,
                                (((uint64_t)1U << TX_MB_COUNT) - 1U) << TX_MB_IDX |
                                ((uint64_t)1U << RX_MB_IDX));
    NVIC_ClearPendingIRQ(can->irqn);
    can->filter_mask = 0;
    can->configured = RT_TRUE;
    can_dev->config = *cfg;
    if (can_dev->can_rx != RT_NULL || can_dev->can_tx != RT_NULL)
    {
        EnableIRQ(can->irqn);
    }

    return RT_EOK;
}


/**
 * @brief Dispatch CAN management, per-source IRQ control and explicit START/STOP.
 *
 * RX MB1, TX MB6..MB8 and error interrupts must be masked independently: the
 * controller uses a shared NVIC line. STOP deinitializes the peripheral, while
 * aborting an individual TX remains unsupported without a TX_FAIL terminal.
 *
 * @param can_dev Generic CAN device.
 * @param cmd RT-Thread device or CAN control command.
 * @param arg Command-dependent encoded value or configuration pointer.
 * @return RT_EOK when accepted, otherwise a negative RT-Thread error.
 */
static rt_err_t can_control(struct rt_can_device *can_dev, int cmd, void *arg)
{
    struct imxrt_can *can;
    rt_uint32_t argval, mask;
    rt_err_t res = RT_EOK;
    flexcan_rx_mb_config_t mbConfig;
    /* Descriptor for rearming the dedicated RX MB after filter replacement. */
    flexcan_mb_transfer_t rxXfer;
    struct rt_can_filter_config *cfg;
    struct rt_can_filter_item *item;
    /* Physical interrupt-bit mask of TX MB6, MB7 and MB8. */
    uint64_t tx_mask = (((uint64_t)1U << TX_MB_COUNT) - 1U) << TX_MB_IDX;

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
            FLEXCAN_EnableMbInterrupts(can->base, (uint64_t)1U << RX_MB_IDX);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            /* The SDK enables the selected TX MB interrupt when submitting. */
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
            FLEXCAN_DisableMbInterrupts(can->base, (uint64_t)1U << RX_MB_IDX);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            FLEXCAN_DisableMbInterrupts(can->base, tx_mask);
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
        if (cfg != RT_NULL)
        {
            if (cfg->count == 0U)
            {
                break;
            }
            if (cfg->count != RX_MB_COUNT || cfg->items == RT_NULL || can->filter_mask != 0U)
            {
                res = -RT_EINVAL;
                break;
            }
            item = cfg->items;
            if (item->hdr_bank != -1 && item->hdr_bank != 0)
            {
                res = -RT_EINVAL;
                break;
            }
            mbConfig.format = item->ide ? kFLEXCAN_FrameFormatExtend : kFLEXCAN_FrameFormatStandard;
            mbConfig.id = item->ide ? FLEXCAN_ID_EXT(item->id) : FLEXCAN_ID_STD(item->id);
            mbConfig.type = item->rtr ? kFLEXCAN_FrameTypeRemote : kFLEXCAN_FrameTypeData;
            mask = item->ide ? FLEXCAN_RX_MB_EXT_MASK(item->mask, 0, 0) :
                               FLEXCAN_RX_MB_STD_MASK(item->mask, 0, 0);
        }
        else
        {
            mbConfig.format = kFLEXCAN_FrameFormatStandard;
            mbConfig.id = FLEXCAN_ID_STD(0);
            mbConfig.type = kFLEXCAN_FrameTypeData;
            mask = FLEXCAN_RX_MB_STD_MASK(0, 0, 0);
        }

        /* Only RX MB1 may be used for filters; MB6..MB8 belong to TX. */
        FLEXCAN_TransferAbortReceive(can->base, &can->handle, RX_MB_IDX);
        FLEXCAN_SetRxIndividualMask(can->base, RX_MB_IDX, mask);
        FLEXCAN_SetRxMbConfig(can->base, RX_MB_IDX, &mbConfig, true);
        rxXfer.frame = &can->frame[0];
        rxXfer.mbIdx = RX_MB_IDX;
        FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
        FLEXCAN_DisableMbInterrupts(can->base, (uint64_t)1U << RX_MB_IDX);
        can->filter_mask = cfg == RT_NULL ? 0U : 1U;
        break;

    case RT_CAN_CMD_SET_BAUD:
        if (arg == RT_NULL)
        {
            res = -RT_EINVAL;
        }
        else
        {
            res = can_cfg(can_dev, (struct can_configure *)arg);
        }
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
            /* ESR1 read-to-clear errors and Generic counters need the SDK IRQ excluded. */
            rt_base_t irq_level;
            /* ESR1 fault confinement is current state; BOFFINT is only historical. */
            rt_uint32_t status_flags;
            /* Two-bit FlexCAN fault confinement: 0 active, 1 passive, 2/3 bus-off. */
            rt_uint32_t fault_state;

            irq_level = rt_hw_interrupt_disable();
            status_flags = (rt_uint32_t)FLEXCAN_GetStatusFlags(can->base);
            fault_state = (status_flags & CAN_ESR1_FLTCONF_MASK) >> CAN_ESR1_FLTCONF_SHIFT;

            /* Forward any read-cleared protocol bits before the SDK IRQ can consume the next error. */
            if ((status_flags & (kFLEXCAN_StuffingError | kFLEXCAN_FormError |
                                 kFLEXCAN_AckError | kFLEXCAN_Bit1Error |
                                 kFLEXCAN_Bit0Error | kFLEXCAN_CrcError)) != 0U)
            {
                flexcan_callback(can->base, &can->handle, kStatus_FLEXCAN_ErrorStatus,
                                 (uint64_t)status_flags, can);
            }
            FLEXCAN_GetBusErrCount(can->base, (rt_uint8_t *)(&can_dev->status.snderrcnt),
                                   (rt_uint8_t *)(&can_dev->status.rcverrcnt));
            if (fault_state >= 2U)
            {
                can_dev->status.errcode = BUSOFF;
            }
            else if (fault_state == 1U)
            {
                can_dev->status.errcode = ERRPASSIVE;
            }
            else if (can_dev->status.snderrcnt >= 96U || can_dev->status.rcverrcnt >= 96U)
            {
                can_dev->status.errcode = ERRWARNING;
            }
            else
            {
                can_dev->status.errcode = NORMAL;
            }
            rt_memcpy(arg, &can_dev->status, sizeof(can_dev->status));
            rt_hw_interrupt_enable(irq_level);
        }
        else
        {
            rt_memcpy(arg, &can_dev->status, sizeof(can_dev->status));
        }
        break;
    case RT_CAN_CMD_START:
        /* Only confirmed deinit permits Generic FORCE_STOP to retire old owners. */
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
        /* SDK abort requests do not provide a guaranteed TX_FAIL terminal event. */
        res = -RT_ENOSYS;
        break;
    default:
        res = -RT_ERROR;
        break;
    }

    return res;
}


/**
 * @brief Submit a Classic CAN frame to one selected physical FlexCAN TX MB.
 *
 * The logical slot 0..2 maps to MB6..MB8. This function never resets a busy
 * mailbox, waits for completion, or publishes a synchronous TX terminal.
 *
 * @param can_dev Generic CAN device.
 * @param buf CAN message to submit.
 * @param boxno Zero-based Generic TX slot selected by the caller.
 * @return RT_EOK on SDK acceptance, -RT_EBUSY if that MB is busy, otherwise a negative error.
 */
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

    txXfer.mbIdx = TX_MB_IDX + boxno;
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

/**
 * @brief Decode the frame saved in this controller's physical RX mailbox.
 * @param can_dev Generic CAN device.
 * @param buf Destination CAN message.
 * @param boxno Physical receive MB index supplied by the SDK callback.
 * @return Zero after copying the received frame.
 */
static rt_ssize_t can_recv(struct rt_can_device *can_dev, void *buf, rt_uint32_t boxno)
{
    struct imxrt_can *can;
    struct rt_can_msg *pmsg;
    rt_uint8_t index;

    RT_ASSERT(can_dev != RT_NULL);

    can = (struct imxrt_can *)can_dev->parent.user_data;
    pmsg = (struct rt_can_msg *) buf;
    RT_ASSERT(can != RT_NULL);

    index = boxno - RX_MB_IDX;

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
 * @brief Attempt one non-blocking send on an unowned hardware TX mailbox.
 *
 * The SDK supplies physical MB busy state; sndchange separately protects a
 * completed blocking slot until its owner returns from Generic's wait path.
 * No software queuing or retry occurs after all three candidates are busy.
 *
 * @param can_dev Generic CAN device with a three-slot TX runtime.
 * @param buf CAN message to submit.
 * @param mailbox Output Generic slot index on successful hardware acceptance.
 * @return RT_EOK on acceptance, -RT_EBUSY when all TX MBs are unavailable, or a negative error.
 */
static rt_ssize_t can_send_nonblocking(struct rt_can_device *can_dev, const void *buf, rt_uint32_t *mailbox)
{
    /* Candidate zero-based Generic TX slot. */
    rt_uint32_t i;
    /* Immediate SDK submit result for the selected slot. */
    rt_ssize_t result;

    if (mailbox == RT_NULL)
    {
        return -RT_EINVAL;
    }

    for (i = 0; i < TX_MB_COUNT; i++)
    {
        /* Completed blocking owners keep sndchange set until their waiter retires. */
        if ((can_dev->status.sndchange & (1UL << i)) != 0U)
        {
            continue;
        }
        result = can_send(can_dev, buf, i);
        if (result == RT_EOK)
        {
            *mailbox = i;
            return RT_EOK;
        }
        if (result != -RT_EBUSY)
        {
            return result;
        }
    }

    return -RT_EBUSY;
}

static struct rt_can_ops imxrt_can_ops =
{
    .configure    = can_cfg,
    .control      = can_control,
    .sendmsg      = can_send,
    .recvmsg      = can_recv,
    .sendmsg_nonblocking = can_send_nonblocking,
};


/**
 * @brief Register MCX N FlexCAN controllers with three hardware-backed TX slots each.
 * @return The result of the final device registration attempt.
 */
int rt_hw_can_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;
    struct can_configure config = CANDEFAULTCONFIG;

    config.privmode = 0;
    config.ticks = 50;
    config.sndboxnumber = TX_MB_COUNT;
    config.msgboxsz = RX_MB_COUNT;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = RX_MB_COUNT;          /* filter count,one filter per MB */
#endif /* RT_CAN_USING_HDR */

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
