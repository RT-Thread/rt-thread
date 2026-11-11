/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-12-23     CYFS         the first version.
 * 2026-07-05     WANGYU       add CAN-FD and loopback support.
 * 2026-11-10     wdfk-prog    Adapt FlexCAN to the asynchronous Generic CAN TX framework.
 */

#include <rtdevice.h>

#ifdef RT_USING_CAN

#include "fsl_common.h"
#include "fsl_clock.h"
#include "fsl_flexcan.h"

#define TX_MB_IDX      (0)
#define RX_MB_IDX      (1)
#define RX_MB_COUNT    (1)

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
    char *name;
    CAN_Type *base;
    IRQn_Type irqn;
    uint32_t instance;
    clock_div_name_t clock_div_name;
    clock_attach_id_t clock_attach_id;
    flexcan_handle_t handle;
    struct rt_can_device can_dev;
    flexcan_frame_t frame[RX_MB_COUNT];
#ifdef RT_CAN_USING_CANFD
    flexcan_fd_frame_t framefd[RX_MB_COUNT];
    rt_bool_t fd_enabled;
#endif
    rt_uint32_t filter_mask;
    rt_bool_t stopped; /**< SDK deinitialized; do not read MMIO after clock gating. */
    rt_bool_t configured; /**< All hardware initialization steps completed successfully. */
};

#ifdef RT_CAN_USING_CANFD
static rt_uint8_t _can_dlc2len(rt_uint8_t dlc)
{
    return (rt_uint8_t)DLC_LENGTH_DECODE(dlc);
}

static rt_uint8_t _can_len2dlc(rt_uint8_t len)
{
    static const rt_uint8_t table[] = {
        0,
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        9,
        9,
        9,
        10,
        10,
        10,
        10,
        11,
        11,
        11,
        11,
        12,
        12,
        12,
        12,
        13,
        13,
        13,
        13,
        13,
        13,
        13,
        13,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        14,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
    };

    if (len <= 64)
    {
        return table[len];
    }

    return 15;
}
#endif

static void _can_fill_classic_frame(flexcan_frame_t *frame, const struct rt_can_msg *msg)
{
    if (RT_CAN_STDID == msg->ide)
    {
        frame->id = FLEXCAN_ID_STD(msg->id);
        frame->format = kFLEXCAN_FrameFormatStandard;
    }
    else
    {
        frame->id = FLEXCAN_ID_EXT(msg->id);
        frame->format = kFLEXCAN_FrameFormatExtend;
    }

    frame->type = (RT_CAN_DTR == msg->rtr) ? kFLEXCAN_FrameTypeData : kFLEXCAN_FrameTypeRemote;
    frame->length = msg->len;
    frame->dataByte0 = msg->data[0];
    frame->dataByte1 = msg->data[1];
    frame->dataByte2 = msg->data[2];
    frame->dataByte3 = msg->data[3];
    frame->dataByte4 = msg->data[4];
    frame->dataByte5 = msg->data[5];
    frame->dataByte6 = msg->data[6];
    frame->dataByte7 = msg->data[7];
}

static void _can_parse_classic_frame(struct rt_can_msg *msg, const flexcan_frame_t *frame)
{
    if (frame->format == kFLEXCAN_FrameFormatStandard)
    {
        msg->ide = RT_CAN_STDID;
        msg->id = frame->id >> CAN_ID_STD_SHIFT;
    }
    else
    {
        msg->ide = RT_CAN_EXTID;
        msg->id = frame->id >> CAN_ID_EXT_SHIFT;
    }

    msg->rtr = (frame->type == kFLEXCAN_FrameTypeData) ? RT_CAN_DTR : RT_CAN_RTR;
    msg->len = frame->length;
    msg->data[0] = frame->dataByte0;
    msg->data[1] = frame->dataByte1;
    msg->data[2] = frame->dataByte2;
    msg->data[3] = frame->dataByte3;
    msg->data[4] = frame->dataByte4;
    msg->data[5] = frame->dataByte5;
    msg->data[6] = frame->dataByte6;
    msg->data[7] = frame->dataByte7;
}

struct imxrt_can flexcans[] = {
#ifdef BSP_USING_CAN0
    {
        .name = "can0",
        .base = CAN0,
        .instance = 0,
        .irqn = CAN0_IRQn,
        .clock_div_name = kCLOCK_DivFLEXCAN0,
        .clock_attach_id = kFRO_HF_DIV_to_FLEXCAN0,
    },
#endif
#ifdef BSP_USING_CAN1
    {
        .name = "can1",
        .base = CAN1,
        .instance = 1,
        .irqn = CAN1_IRQn,
        .clock_div_name = kCLOCK_DivFLEXCAN1,
        .clock_attach_id = kFRO_HF_DIV_to_FLEXCAN1,
    },
#endif
};

static rt_bool_t _can_is_loopback(const struct can_configure *cfg)
{
    return (cfg->mode == RT_CAN_MODE_LOOPBACK) ||
           (cfg->mode == RT_CAN_MODE_LOOPBACKANLISTEN);
}

static void _can_enable_periph_clock(struct imxrt_can *can)
{
    clock_ip_name_t can_clocks[] = FLEXCAN_CLOCKS;

    CLOCK_EnableClock(can_clocks[can->instance]);
    CLOCK_SetClockDiv(can->clock_div_name, 2u);
    CLOCK_AttachClk(can->clock_attach_id);
}

static void _can_safe_deinit(struct imxrt_can *can)
{
    CAN_Type *base = can->base;

    _can_enable_periph_clock(can);

    /* FLEXCAN_Reset() inside FLEXCAN_Deinit() requires MDIS cleared. */
    if (0U != (base->MCR & CAN_MCR_MDIS_MASK))
    {
        (void)FLEXCAN_Enable(base, true);
    }

    FLEXCAN_Deinit(base);
}

static void _can_setup_mode(flexcan_config_t *config, const struct can_configure *cfg)
{
    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        break;
    case RT_CAN_MODE_LISTEN:
        config->enableListenOnlyMode = true;
        break;
    case RT_CAN_MODE_LOOPBACK:
        config->enableLoopBack = true;
        config->disableSelfReception = false;
        config->enableIndividMask = false;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        config->enableLoopBack = true;
        config->enableListenOnlyMode = true;
        config->disableSelfReception = false;
        config->enableIndividMask = false;
        break;
    default:
        break;
    }
}

static void _can_start_rx(struct imxrt_can *can)
{
    flexcan_rx_mb_config_t mbConfig;
    flexcan_mb_transfer_t rxXfer;
    rt_uint8_t i, mailbox;

    mbConfig.format = kFLEXCAN_FrameFormatStandard;
    mbConfig.type = kFLEXCAN_FrameTypeData;
    mbConfig.id = FLEXCAN_ID_STD(0);

    FLEXCAN_SetRxMbGlobalMask(can->base, 0U);

    for (i = 0; i < RX_MB_COUNT; i++)
    {
        mailbox = RX_MB_IDX + i;
        FLEXCAN_SetRxIndividualMask(can->base, mailbox, 0U);

#ifdef RT_CAN_USING_CANFD
        if (can->fd_enabled)
        {
            FLEXCAN_SetFDRxMbConfig(can->base, mailbox, &mbConfig, true);
            rxXfer.framefd = &can->framefd[i];
            rxXfer.frame = RT_NULL;
            rxXfer.mbIdx = mailbox;
            FLEXCAN_TransferFDReceiveNonBlocking(can->base, &can->handle, &rxXfer);
        }
        else
#endif
        {
            FLEXCAN_SetRxMbConfig(can->base, mailbox, &mbConfig, true);
            rxXfer.frame = &can->frame[i];
#ifdef RT_CAN_USING_CANFD
            rxXfer.framefd = RT_NULL;
#endif
            rxXfer.mbIdx = mailbox;
            FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
        }
    }
}

/**
 * @brief Enable the shared FlexCAN NVIC line after the requested MB/error source is unmasked.
 * @param can FlexCAN instance whose IRQ line is being enabled.
 */
static void _can_enable_controller_irq(struct imxrt_can *can)
{
    EnableIRQ(can->irqn);
}

#ifdef BSP_USING_CAN0
void CAN0_IRQHandler(void)
{
    rt_interrupt_enter();
    FLEXCAN_TransferHandleIRQ(CAN0, &flexcans[CAN0_INDEX].handle);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CAN1
void CAN1_IRQHandler(void)
{
    rt_interrupt_enter();
    FLEXCAN_TransferHandleIRQ(CAN1, &flexcans[CAN1_INDEX].handle);
    rt_interrupt_leave();
}
#endif

/**
 * @brief Publish RX frames and completed MB0 transmissions through Generic CAN.
 *
 * SDK TxIdle means the hardware request has finished. An RTR request instead
 * transitions MB0 to RX; restore its TX role before publishing TX_DONE so the
 * next Generic owner cannot inherit a receive-configured mailbox.
 *
 * @param base FlexCAN register instance.
 * @param handle NXP transactional transfer handle.
 * @param status SDK transfer event.
 * @param result Hardware mailbox index for the handled RX/TX event.
 * @param userData Registered imxrt_can instance.
 */
static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint64_t result, void *userData)
{
    struct imxrt_can *can;
    flexcan_mb_transfer_t rxXfer;
    rt_uint8_t mb_idx;

    can = (struct imxrt_can *)userData;

    switch (status)
    {
    case kStatus_FLEXCAN_RxIdle:
        mb_idx = (rt_uint8_t)result;
        if (mb_idx != RX_MB_IDX)
        {
            break;
        }
        rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_RX_IND | mb_idx << 8);

#ifdef RT_CAN_USING_CANFD
        if (can->fd_enabled)
        {
            rxXfer.framefd = &can->framefd[mb_idx - RX_MB_IDX];
            rxXfer.frame = RT_NULL;
            rxXfer.mbIdx = mb_idx;
            FLEXCAN_TransferFDReceiveNonBlocking(can->base, &can->handle, &rxXfer);
        }
        else
#endif
        {
            rxXfer.frame = &can->frame[mb_idx - RX_MB_IDX];
#ifdef RT_CAN_USING_CANFD
            rxXfer.framefd = RT_NULL;
#endif
            rxXfer.mbIdx = mb_idx;
            FLEXCAN_TransferReceiveNonBlocking(can->base, &can->handle, &rxXfer);
        }
        break;

    case kStatus_FLEXCAN_TxSwitchToRx:
        if (result != TX_MB_IDX)
        {
            break;
        }
        /* An RTR TX becomes an RX MB in the SDK; restore MB0 before retiring TX ownership. */
#ifdef RT_CAN_USING_CANFD
        if (can->fd_enabled)
        {
            FLEXCAN_TransferFDAbortReceive(base, handle, TX_MB_IDX);
            FLEXCAN_SetFDTxMbConfig(base, TX_MB_IDX, true);
        }
        else
#endif /* RT_CAN_USING_CANFD */
        {
            FLEXCAN_TransferAbortReceive(base, handle, TX_MB_IDX);
            FLEXCAN_SetTxMbConfig(base, TX_MB_IDX, true);
        }
        rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_TX_DONE | TX_MB_IDX << 8);
        break;

    case kStatus_FLEXCAN_TxIdle:
        if (result == TX_MB_IDX)
        {
            rt_hw_can_isr(&can->can_dev, RT_CAN_EVENT_TX_DONE | TX_MB_IDX << 8);
        }
        break;
    default:
        break;
    }
}

/**
 * @brief Reconfigure FlexCAN and prepare MB0 TX and MB1 RX for Generic CAN.
 *
 * RX/TX mailbox interrupts remain masked until Generic publishes/reopens their
 * runtime gates. The SDK's error sources remain enabled when reconfiguring an
 * open device. Hardware filters are reset and may need reapplication.
 * BOFFREC is kept clear so the peripheral can recover Bus-Off after the
 * required recessive bus sequence; the Generic TX callback never blocks.
 * A failed reconfiguration remains invalid until a successful START(1);
 * if FD timing setup fails after SDK Init, deinitialize before reporting error.
 * SDK CreateHandle briefly enables CAN NVIC, which is remasked atomically
 * before mailbox setup and released only after Generic runtime publication.
 *
 * @param can_dev Generic CAN device.
 * @param cfg Requested CAN timing, mode and optional FD configuration.
 * @return RT_EOK after peripheral setup or -RT_ERROR on configuration failure.
 */
static rt_err_t _can_config(struct rt_can_device *can_dev, struct can_configure *cfg)
{
    struct imxrt_can *can = (struct imxrt_can *)can_dev->parent.user_data;
    flexcan_config_t config;
    flexcan_timing_config_t timing_config;
    rt_uint32_t clk_freq;
    rt_err_t res = RT_EOK;
    /* Preserve the caller's global IRQ mask while the SDK briefly enables CAN NVIC. */
    rt_base_t irq_level;

    /* A failed reconfiguration must not be mistaken for a runnable controller. */
    can->configured = RT_FALSE;
    /* No controller IRQ may run while the SDK handle and RX buffers are rebuilt. */
    DisableIRQ(can->irqn);
    _can_enable_periph_clock(can);
    clk_freq = CLOCK_GetFlexcanClkFreq(can->instance);
    if (clk_freq == 0U)
    {
        rt_kprintf("%s: flexcan clock is 0\n", can->name);
        return -RT_ERROR;
    }

    rt_kprintf("%s: flexcan clk=%u Hz, baud=%u\n", can->name, clk_freq, cfg->baud_rate);

    _can_safe_deinit(can);
    /* A completed Deinit, not configured=false, establishes hardware STOP. */
    can->stopped = RT_TRUE;

    FLEXCAN_GetDefaultConfig(&config);
    config.baudRate = cfg->baud_rate;
    config.maxMbNum = 8;
    config.enableIndividMask = false;
    config.enableSupervisorMode = false;
    config.disableSelfReception = !_can_is_loopback(cfg);
    _can_setup_mode(&config, cfg);

    if (_can_is_loopback(cfg)
#ifdef RT_CAN_USING_CANFD
        || (cfg->enable_canfd == 0)
#endif
    )
    {
        config.enableTransceiverDelayMeasure = false;
    }
    else
    {
        config.enableTransceiverDelayMeasure = true;
    }

    rt_memset(&timing_config, 0, sizeof(flexcan_timing_config_t));

#ifdef RT_CAN_USING_CANFD
    can->fd_enabled = (cfg->enable_canfd != 0) ? RT_TRUE : RT_FALSE;

    if (can->fd_enabled)
    {
        bool brs_enable = _can_is_loopback(cfg) ? false : (cfg->baud_rate_fd > cfg->baud_rate);
        bool timing_ok;

        config.bitRateFD = _can_is_loopback(cfg) ? config.baudRate : (cfg->baud_rate_fd ? cfg->baud_rate_fd : 2000000U);

        timing_ok = FLEXCAN_FDCalculateImprovedTimingValues(can->base, config.baudRate,
                                                            config.bitRateFD, clk_freq, &timing_config);
        if (timing_ok)
        {
            rt_memcpy(&(config.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
        }

        /* FDInit may activate hardware before fallback bit timing can fail. */
        can->stopped = RT_FALSE;
        FLEXCAN_FDInit(can->base, &config, clk_freq, kFLEXCAN_16BperMB, brs_enable);
        if (!timing_ok)
        {
            if (FLEXCAN_SetFDBitRate(can->base, clk_freq, config.baudRate, config.bitRateFD) != kStatus_Success)
            {
                rt_kprintf("%s: CAN FD timing setup failed, clk=%u\n", can->name, clk_freq);
                /* Roll back partially initialized hardware before reporting failure to Generic. */
                _can_safe_deinit(can);
                can->stopped = RT_TRUE;
                NVIC_ClearPendingIRQ(can->irqn);
                return -RT_ERROR;
            }
        }
    }
    else
#endif
    {
        if (FLEXCAN_CalculateImprovedTimingValues(can->base, config.baudRate, clk_freq, &timing_config))
        {
            rt_memcpy(&(config.timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
        }

        /* Classic Init may activate hardware; STOP must not skip Deinit. */
        can->stopped = RT_FALSE;
        FLEXCAN_Init(can->base, &config, clk_freq);
    }

    /* BOFFREC=0 enables hardware Bus-Off recovery without blocking Generic TX submission. */
    can->base->CTRL1 &= ~CAN_CTRL1_BOFFREC_MASK;

    can->filter_mask = 0;
    /* The SDK enables CAN NVIC inside CreateHandle; prevent an ISR before MB setup. */
    irq_level = rt_hw_interrupt_disable();
    FLEXCAN_TransferCreateHandle(can->base, &can->handle, flexcan_callback, can);
    DisableIRQ(can->irqn);
    rt_hw_interrupt_enable(irq_level);
#ifdef RT_CAN_USING_CANFD
    if (can->fd_enabled)
    {
        FLEXCAN_SetFDTxMbConfig(can->base, TX_MB_IDX, true);
    }
    else
#endif /* RT_CAN_USING_CANFD */
    {
        FLEXCAN_SetTxMbConfig(can->base, TX_MB_IDX, true);
    }
    _can_start_rx(can);
    /* Generic CAN publishes RX/TX runtimes before enabling individual IRQ sources. */
    FLEXCAN_DisableMbInterrupts(can->base, ((uint64_t)1U << TX_MB_IDX) | ((uint64_t)1U << RX_MB_IDX));
    NVIC_ClearPendingIRQ(can->irqn);
    /* Commit a staged configuration only after hardware setup succeeds. */
    can_dev->config = *cfg;
    can->stopped = RT_FALSE;
    can->configured = RT_TRUE;
    /* SDK error sources remain enabled across a Generic runtime reconfiguration. */
    if (can_dev->can_rx != RT_NULL || can_dev->can_tx != RT_NULL)
    {
        _can_enable_controller_irq(can);
    }

    return res;
}

/**
 * @brief Dispatch CAN setup commands and independently gate RX/TX/error IRQ sources.
 *
 * START(0) deinitializes FlexCAN and invalidates old hardware requests. SDK
 * Deinit may gate the clock, so a private flag replaces post-Deinit MMIO reads.
 * A separate configured flag prevents failed runtime reconfiguration from
 * being treated as an already-running controller on START(1).
 * Generic owns TX retirement; Abort-TX has no proven hardware terminal contract.
 *
 * @param can_dev Generic CAN device.
 * @param cmd RT-Thread device control or Generic CAN command.
 * @param arg Command-specific encoded value or pointer.
 * @return RT_EOK on success, or the corresponding negative RT-Thread error.
 */
static rt_err_t _can_control(struct rt_can_device *can_dev, int cmd, void *arg)
{
    struct imxrt_can *can;
    rt_uint32_t argval, mask;
    rt_err_t res = RT_EOK;
    flexcan_rx_mb_config_t mbConfig;
    struct rt_can_filter_config *cfg;
    struct rt_can_filter_item *item;
    rt_uint8_t i, count, index;

    RT_ASSERT(can_dev != RT_NULL);

    can = (struct imxrt_can *)can_dev->parent.user_data;
    RT_ASSERT(can != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
        if (can->stopped || !can->configured)
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
            /* The SDK enables the selected TX MB interrupt on submission. */
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            FLEXCAN_EnableInterrupts(can->base, (uint32_t)kFLEXCAN_BusOffInterruptEnable |
                                                (uint32_t)kFLEXCAN_ErrorInterruptEnable |
                                                (uint32_t)kFLEXCAN_RxWarningInterruptEnable |
                                                (uint32_t)kFLEXCAN_TxWarningInterruptEnable);
        }
        else
        {
            res = -RT_ERROR;
            break;
        }
        _can_enable_controller_irq(can);
        break;
    case RT_DEVICE_CTRL_CLR_INT:
        /* STOP or a failed configuration has no valid interrupt sources to disable. */
        if (can->stopped || !can->configured)
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
            FLEXCAN_DisableMbInterrupts(can->base, (uint64_t)1U << TX_MB_IDX);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            FLEXCAN_DisableInterrupts(can->base, (uint32_t)kFLEXCAN_BusOffInterruptEnable |
                                                 (uint32_t)kFLEXCAN_ErrorInterruptEnable |
                                                 (uint32_t)kFLEXCAN_RxWarningInterruptEnable |
                                                 (uint32_t)kFLEXCAN_TxWarningInterruptEnable);
        }
        else
        {
            res = -RT_ERROR;
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        if (can->stopped || !can->configured)
        {
            res = -RT_ERROR;
            break;
        }
        cfg = (struct rt_can_filter_config *)arg;
        item = cfg->items;
        count = cfg->count;

        if (can->filter_mask == 0xffffffff)
        {
            rt_kprintf("%s filter is full!\n", can->name);
            res = -RT_ERROR;
            break;
        }
        else if (can->filter_mask == 0)
        {
            for (i = 0; i < RX_MB_COUNT; i++)
            {
#ifdef RT_CAN_USING_CANFD
                if (can->fd_enabled)
                {
                    FLEXCAN_SetFDRxMbConfig(can->base, i + 1, RT_NULL, false);
                }
                else
#endif
                {
                    FLEXCAN_SetRxMbConfig(can->base, i + 1, RT_NULL, false);
                }
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

            mbConfig.type = item->rtr ? kFLEXCAN_FrameTypeRemote : kFLEXCAN_FrameTypeData;

            if (item->hdr_bank == -1)
            {
                for (i = 0; i < 32; i++)
                {
                    if (!(can->filter_mask & (1 << i)))
                    {
                        index = i;
                        break;
                    }
                }
            }
            else
            {
                if (can->filter_mask & (1 << item->hdr_bank))
                {
                    res = -RT_ERROR;
                    rt_kprintf("%s hdr%d filter already set!\n", can->name, item->hdr_bank);
                    break;
                }
                index = item->hdr_bank;
            }

            FLEXCAN_SetRxIndividualMask(can->base, index + 1, mask);
#ifdef RT_CAN_USING_CANFD
            if (can->fd_enabled)
            {
                FLEXCAN_SetFDRxMbConfig(can->base, index + 1, &mbConfig, true);
            }
            else
#endif
            {
                FLEXCAN_SetRxMbConfig(can->base, index + 1, &mbConfig, true);
            }
            can->filter_mask |= 1 << index;

            item++;
            count--;
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t)arg;
        if (argval != 0)
        {
            can->can_dev.config.baud_rate = argval;
            res = _can_config(can_dev, &can->can_dev.config);
        }
        else
        {
            res = -RT_ERROR;
        }
        break;
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t)arg;
        if (argval > RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            res = -RT_ERROR;
            break;
        }
        can->can_dev.config.mode = argval;
        res = _can_config(can_dev, &can->can_dev.config);
        break;
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
        argval = (rt_uint32_t)arg;
        can->can_dev.config.enable_canfd = argval ? 1 : 0;
        res = _can_config(can_dev, &can->can_dev.config);
        break;
    case RT_CAN_CMD_SET_BAUD_FD:
        argval = (rt_uint32_t)arg;
        if (argval != 0)
        {
            can->can_dev.config.baud_rate_fd = argval;
            res = _can_config(can_dev, &can->can_dev.config);
        }
        else
        {
            res = -RT_ERROR;
        }
        break;
#endif
    case RT_CAN_CMD_SET_PRIV:
        break;
    case RT_CAN_CMD_GET_STATUS:
        if (!can->stopped && can->configured)
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
            if (!can->stopped)
            {
                /* SDK Deinit resets all requests and may gate the peripheral clock. */
                _can_safe_deinit(can);
                can->stopped = RT_TRUE;
                can->configured = RT_FALSE;
            }
            NVIC_ClearPendingIRQ(can->irqn);
        }
        else if (can->stopped || !can->configured)
        {
            /* A prior reconfiguration failure must be retried, not reported as success. */
            res = _can_config(can_dev, &can_dev->config);
        }
        break;
    case RT_CAN_CMD_ABORT_TX:
        res = -RT_ENOSYS;
        break;
    default:
        res = -RT_ERROR;
        break;
    }

    return res;
}

#ifdef RT_CAN_USING_CANFD
static void _can_fill_fd_frame(flexcan_fd_frame_t *frame, const struct rt_can_msg *msg)
{
    rt_uint8_t dlc;
    rt_uint8_t data_len;

    rt_memset(frame, 0, sizeof(*frame));

    if (RT_CAN_STDID == msg->ide)
    {
        frame->id = FLEXCAN_ID_STD(msg->id);
        frame->format = kFLEXCAN_FrameFormatStandard;
    }
    else
    {
        frame->id = FLEXCAN_ID_EXT(msg->id);
        frame->format = kFLEXCAN_FrameFormatExtend;
    }

    frame->type = (RT_CAN_DTR == msg->rtr) ? kFLEXCAN_FrameTypeData : kFLEXCAN_FrameTypeRemote;
    frame->edl = 1;
    frame->brs = msg->brs ? 1 : 0;

    dlc = (msg->len <= 15) ? msg->len : _can_len2dlc((rt_uint8_t)msg->len);
    frame->length = dlc;
    data_len = _can_dlc2len(dlc);
    rt_memcpy(frame->dataWord, msg->data, data_len);
}

static void _can_parse_fd_frame(struct rt_can_msg *msg, const flexcan_fd_frame_t *frame)
{
    rt_uint8_t data_len;

    if (frame->format == kFLEXCAN_FrameFormatStandard)
    {
        msg->ide = RT_CAN_STDID;
        msg->id = frame->id >> CAN_ID_STD_SHIFT;
    }
    else
    {
        msg->ide = RT_CAN_EXTID;
        msg->id = frame->id >> CAN_ID_EXT_SHIFT;
    }

    msg->rtr = (frame->type == kFLEXCAN_FrameTypeData) ? RT_CAN_DTR : RT_CAN_RTR;
    msg->fd_frame = frame->edl ? 1 : 0;
    msg->brs = frame->brs ? 1 : 0;
    msg->len = frame->length;
    data_len = _can_dlc2len(frame->length);
    rt_memcpy(msg->data, frame->dataWord, data_len);
}
#endif

/**
 * @brief Submit one frame immediately to the sole hardware TX mailbox, without waiting.
 *
 * Generic owns slot zero until the SDK callback publishes the actual terminal;
 * this entry runs under Generic's IRQ-safe TX lock and must not sleep or report
 * a synthetic completion. The NXP SDK copies the local frame into MB0 on submit.
 *
 * @param can_dev Generic CAN device.
 * @param buf Frame to send.
 * @param boxno Required physical TX mailbox index (TX_MB_IDX).
 * @return RT_EOK if accepted, -RT_EBUSY if occupied, or a negative error.
 */
static rt_ssize_t _can_sendmsg(struct rt_can_device *can_dev, const void *buf, rt_uint32_t boxno)
{
    struct imxrt_can *can;
    /* Immutable request frame owned by the Generic CAN caller. */
    const struct rt_can_msg *msg;
    /* SDK descriptor and immediate hardware acceptance result. */
    flexcan_mb_transfer_t txXfer;
    status_t ret;

    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    if (boxno != TX_MB_IDX)
    {
        return -RT_EINVAL;
    }

    can = (struct imxrt_can *)can_dev->parent.user_data;
    if (can->stopped || !can->configured)
    {
        return -RT_ERROR;
    }
    msg = (const struct rt_can_msg *)buf;
    txXfer.mbIdx = TX_MB_IDX;

#ifdef RT_CAN_USING_CANFD
    if (can->fd_enabled && msg->fd_frame)
    {
        /* Stack-local FD payload copied into the hardware mailbox by the SDK call. */
        flexcan_fd_frame_t tx_frame;

        _can_fill_fd_frame(&tx_frame, msg);
        txXfer.framefd = &tx_frame;
        txXfer.frame = RT_NULL;
        ret = FLEXCAN_TransferFDSendNonBlocking(can->base, &can->handle, &txXfer);
    }
    else
#endif /* RT_CAN_USING_CANFD */
    {
        /* Stack-local classic payload copied into the hardware mailbox by the SDK call. */
        flexcan_frame_t tx_frame;

        _can_fill_classic_frame(&tx_frame, msg);
        txXfer.frame = &tx_frame;
#ifdef RT_CAN_USING_CANFD
        txXfer.framefd = RT_NULL;
#endif /* RT_CAN_USING_CANFD */
        ret = FLEXCAN_TransferSendNonBlocking(can->base, &can->handle, &txXfer);
    }

    if (ret == kStatus_FLEXCAN_TxBusy)
    {
        return -RT_EBUSY;
    }
    return (ret == kStatus_Success) ? RT_EOK : -RT_ERROR;
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can_dev, void *buf, rt_uint32_t boxno)
{
    struct imxrt_can *can;
    struct rt_can_msg *pmsg;
    rt_uint8_t index;

    RT_ASSERT(can_dev != RT_NULL);

    can = (struct imxrt_can *)can_dev->parent.user_data;
    pmsg = (struct rt_can_msg *)buf;
    index = (boxno >= RX_MB_IDX) ? (boxno - RX_MB_IDX) : 0;

#ifdef RT_CAN_USING_CANFD
    if (can->fd_enabled && can->framefd[index].edl)
    {
        _can_parse_fd_frame(pmsg, &can->framefd[index]);
    }
    else if (can->fd_enabled)
    {
        _can_parse_classic_frame(pmsg, (const flexcan_frame_t *)&can->framefd[index]);
        pmsg->fd_frame = 0;
        pmsg->brs = 0;
    }
    else
#endif
    {
        _can_parse_classic_frame(pmsg, &can->frame[index]);
    }

    pmsg->hdr_index = index;

    return 0;
}

/**
 * @brief Attempt one non-blocking hardware submission without a software TX queue.
 *
 * A blocking owner must retire before its mailbox may be selected again.
 * The SDK tracks active non-blocking hardware transfers in its MB0 state.
 *
 * @param can_dev Generic CAN device.
 * @param buf Frame to send.
 * @param mailbox Selected zero-based hardware mailbox on success only.
 * @return RT_EOK if accepted, -RT_EBUSY if unavailable, or a negative error.
 */
static rt_ssize_t _can_sendmsg_nonblocking(struct rt_can_device *can_dev, const void *buf, rt_uint32_t *mailbox)
{
    /* Immediate hardware acceptance result; not a bus-completion indication. */
    rt_ssize_t result;

    RT_ASSERT(can_dev != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    RT_ASSERT(mailbox != RT_NULL);

    /* A completed blocking owner may still be waiting to retire Generic slot 0. */
    if ((can_dev->status.sndchange & (1UL << TX_MB_IDX)) != 0U)
    {
        return -RT_EBUSY;
    }

    result = _can_sendmsg(can_dev, buf, TX_MB_IDX);
    if (result == RT_EOK)
    {
        *mailbox = TX_MB_IDX;
    }
    return result;
}

static struct rt_can_ops imxrt_can_ops = {
    .configure = _can_config,
    .control = _can_control,
    .sendmsg = _can_sendmsg,
    .recvmsg = _can_recvmsg,
    .sendmsg_nonblocking = _can_sendmsg_nonblocking
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
    config.maxhdr = RX_MB_COUNT;
#endif
#ifdef RT_CAN_USING_CANFD
    config.enable_canfd = 1;
    config.baud_rate_fd = 2000000;
#endif

    for (i = 0; i < sizeof(flexcans) / sizeof(flexcans[0]); i++)
    {
        flexcans[i].can_dev.config = config;
        flexcans[i].filter_mask = 0;
        _can_enable_periph_clock(&flexcans[i]);

        ret = rt_hw_can_register(&flexcans[i].can_dev, flexcans[i].name, &imxrt_can_ops, &flexcans[i]);
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* RT_USING_CAN */
