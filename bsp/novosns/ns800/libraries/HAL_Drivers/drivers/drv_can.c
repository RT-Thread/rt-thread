/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-05-30     hu.tang      Add CAN-FD full support: dynamic MB size, FD data path,
 *                             FD control commands, sendmsg_nonblocking, fix hdr_index bug.
 */

#include "drv_can.h"
#include "drv_config.h"

#ifdef BSP_USING_CAN

#define LOG_TAG    "drv_can"
#include <drv_log.h>


#define RX_MB_COUNT     NS800RT7_CAN_RX_MB_COUNT
#define TX_MB_COUNT     NS800RT7_CAN_TX_MB_COUNT  /* MB0 is dedicated TX */
#define TOTAL_MB_COUNT  NS800RT7_CAN_TOTAL_MB_COUNT

#if !defined(BSP_USING_CAN1) && !defined(BSP_USING_CANFD1) && !defined(BSP_USING_CANFD2)
#error "BSP_USING_CAN requires at least one CAN instance"
#endif

#ifdef BSP_USING_CAN1
void CAN1_1_IRQHandler(void);
void CAN1_2_IRQHandler(void);
#endif

#ifdef BSP_USING_CANFD1
void CANFD1_1_IRQHandler(void);
void CANFD1_2_IRQHandler(void);
#endif

#ifdef BSP_USING_CANFD2
void CANFD2_1_IRQHandler(void);
void CANFD2_2_IRQHandler(void);
#endif


static const struct ns800rt7_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud,   1000000},
    {CAN800kBaud, 800000},
    {CAN500kBaud, 500000},
    {CAN250kBaud, 250000},
    {CAN125kBaud, 125000},
    {CAN100kBaud, 100000},
    {CAN50kBaud,  50000},
    {CAN20kBaud,  20000},
    {CAN10kBaud,  10000}
};

#ifdef BSP_USING_CAN1
static ns800rt7_can drv_can1 =
{
    .name = "can1",
    .instance = NS800RT7_CAN_INSTANCE_CAN1,
    .CanHandle.flexCanReg = (FLEXCANREG_TypeDef *)CAN1,
    .irqn1 = CAN1_1_IRQn,
    .irqn2 = CAN1_2_IRQn,
    .irq_handler = CAN1_1_IRQHandler,
    .err_irq_handler = CAN1_2_IRQHandler,
    .tx_pin = {BSP_CAN1_TX_PIN},
    .rx_pin = {BSP_CAN1_RX_PIN},
    .can_instance_idx = 0U,
    .can_ram_num = 1U,
    .fd_capable = RT_FALSE,
};
#endif

#ifdef BSP_USING_CANFD1
static ns800rt7_can drv_canfd1 =
{
    .name = "canfd1",
    .instance = NS800RT7_CAN_INSTANCE_CANFD1,
    .CanHandle.flexCanReg = (FLEXCANREG_TypeDef *)CANFD1,
    .irqn1 = CANFD1_1_IRQn,
    .irqn2 = CANFD1_2_IRQn,
    .irq_handler = CANFD1_1_IRQHandler,
    .err_irq_handler = CANFD1_2_IRQHandler,
    .tx_pin = {BSP_CANFD1_TX_PIN},
    .rx_pin = {BSP_CANFD1_RX_PIN},
    .can_instance_idx = 1U,
    .can_ram_num = 4U,
    .fd_capable = RT_TRUE,
};
#endif

#ifdef BSP_USING_CANFD2
static ns800rt7_can drv_canfd2 =
{
    .name = "canfd2",
    .instance = NS800RT7_CAN_INSTANCE_CANFD2,
    .CanHandle.flexCanReg = (FLEXCANREG_TypeDef *)CANFD2,
    .irqn1 = CANFD2_1_IRQn,
    .irqn2 = CANFD2_2_IRQn,
    .irq_handler = CANFD2_1_IRQHandler,
    .err_irq_handler = CANFD2_2_IRQHandler,
    .tx_pin = {BSP_CANFD2_TX_PIN},
    .rx_pin = {BSP_CANFD2_RX_PIN},
    .can_instance_idx = 2U,
    .can_ram_num = 4U,
    .fd_capable = RT_TRUE,
};
#endif

static ns800rt7_can * const can_devices[] =
{
#ifdef BSP_USING_CAN1
    &drv_can1,
#endif
#ifdef BSP_USING_CANFD1
    &drv_canfd1,
#endif
#ifdef BSP_USING_CANFD2
    &drv_canfd2,
#endif
};

static void _can_gpio_init(ns800rt7_can *drv_can)
{
    GPIO_setAnalogMode(drv_can->tx_pin.port, drv_can->tx_pin.pin, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(drv_can->rx_pin.port, drv_can->rx_pin.pin, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(drv_can->tx_pin.port, drv_can->tx_pin.pin, drv_can->tx_pin.alt_func);
    GPIO_setPinConfig(drv_can->rx_pin.port, drv_can->rx_pin.pin, drv_can->rx_pin.alt_func);
    GPIO_setQualificationMode(drv_can->rx_pin.port, drv_can->rx_pin.pin, GPIO_QUAL_ASYNC);
}

static rt_err_t _can_clock_init(ns800rt7_can *drv_can)
{
    rt_err_t ret = RT_EOK;

    RCC_unlockRccRegister();

#if CAN_CLOCK_SELECTION == CAN_USING_EXTERNAL_OSC
    WRITE_REG(RCC->HXTLCR.WORDVAL, (HXTL_CONFIG | RCC_HXTLCR_KEY));
    RCC_enableHxtl();
    RCC_disableHxtlBypass();

    {
        uint32_t wait_time = 5000000;

        while ((RCC_readHxtlRdyFlag() != 1U) && (--wait_time))
        {
        }

        if (wait_time == 0U)
        {
            ret = -RT_ETIMEOUT;
            goto __exit;
        }
    }

    RCC_enablePeriphKernalUseMirc2();
    RCC_enablePeriphKernalUseHxtl();
    drv_can->clock_freq = HXTL_FREQ_VALUE;
#elif CAN_CLOCK_SELECTION == CAN_USING_INTERNAL_CLOCK
    RCC_enablePeriphKernalUseMirc2();
    drv_can->clock_freq = MIRC2_FREQ_VALUE;
#else
#error "Unsupported CAN_CLOCK_SELECTION"
#endif

    switch (drv_can->instance)
    {
    case NS800RT7_CAN_INSTANCE_CAN1:
#if CAN_CLOCK_SELECTION == CAN_USING_EXTERNAL_OSC
        RCC_selectCan1OscClkSource(RCC_CAN1_OSCCLK_SEL_HXTLKER);
#else
        RCC_selectCan1OscClkSource(RCC_CAN1_OSCCLK_SEL_MIRC2KER);
#endif
        RCC_enableCan1Clock();
        RCC_resetCan1Module();
        RCC_releaseCan1Module();
        break;
    case NS800RT7_CAN_INSTANCE_CANFD1:
#if CAN_CLOCK_SELECTION == CAN_USING_EXTERNAL_OSC
        RCC_selectCanfdOscClkSource(RCC_CANFD1SEL, RCC_CANFD_OSCCLK_SEL_HXTLKER);
#else
        RCC_selectCanfdOscClkSource(RCC_CANFD1SEL, RCC_CANFD_OSCCLK_SEL_MIRC2KER);
#endif
        RCC_enableCanfd1Clock();
        RCC_resetCanfd1Module();
        RCC_releaseCanfd1Module();
        break;
    case NS800RT7_CAN_INSTANCE_CANFD2:
#if CAN_CLOCK_SELECTION == CAN_USING_EXTERNAL_OSC
        RCC_selectCanfdOscClkSource(RCC_CANFD2SEL, RCC_CANFD_OSCCLK_SEL_HXTLKER);
#else
        RCC_selectCanfdOscClkSource(RCC_CANFD2SEL, RCC_CANFD_OSCCLK_SEL_MIRC2KER);
#endif
        RCC_enableCanfd2Clock();
        RCC_resetCanfd2Module();
        RCC_releaseCanfd2Module();
        break;
    default:
        ret = -RT_ERROR;
        break;
    }

__exit:
    RCC_lockRccRegister();
    return ret;
}

static rt_uint32_t get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (can_baud_rate_tab[index].baud_rate == baud)
            return index;
    }

    return 0; /* default baud is CAN1MBaud */
}

static rt_err_t _can_sendBlocking(ns800rt7_can *base, FLEXCANDRV_MsgObjType *TxMsgObj,
                                   rt_uint32_t msg_id, rt_uint8_t is_ext_id,
                                   rt_uint8_t brs)
{
    /* Check if Message Buffer is idle.
     * In loopback mode the controller may generate a spurious TX-done event
     * right after FLEXCANDRV_Configure, leaving the software state in limbo.
     * If the MB is not idle, wait briefly for the ISR to catch up. */
    if (StateIdle != base->mbState[TxMsgObj->msgBufId])
    {
        rt_uint32_t retry;
        for (retry = 0; retry < 50; retry++)
        {
            rt_thread_mdelay(1);
            if (StateIdle == base->mbState[TxMsgObj->msgBufId])
            {
                break;
            }
        }

        if (StateIdle != base->mbState[TxMsgObj->msgBufId])
        {
            LOG_E("sendBlocking: MB%u not idle, state=%u",
                  (unsigned int)TxMsgObj->msgBufId,
                  (unsigned int)base->mbState[TxMsgObj->msgBufId]);
            return -RT_EBUSY;
        }
    }

    {
        base->mbState[TxMsgObj->msgBufId] = StateTxData;

        /* Update MB CS and ID words before sending.
         * FLEXCANDRV_SetTxMsg() only copies data bytes; it does NOT write
         * the message ID or DLC.  Those are set once during
         * FLEXCANDRV_CfgMsgObj() and never touched again without this
         * step every frame goes out with the same ID (0x78). */
        uint32_t *msgBufPtr = (uint32_t *)FLEXCANDRV_GetMsgBufStartAddr(
                                   &base->CanHandle, TxMsgObj->msgBufId);
        FLEXCANDRV_SetMsgId(msgBufPtr, msg_id, (bool)is_ext_id);
        FLEXCANDRV_SetMsgDLC(msgBufPtr, (FLEXCANDRV_DataLenCodeType)TxMsgObj->dlc);

        /* Set FD/EDL and BRS bits independently in the CS word.
         * FLEXCANDRV_SetFDEnable() forces BRS=1 when fdEnable=true,
         * which prevents sending FD frames with BRS=0.
         * Direct CS-word manipulation allows per-frame BRS control. */
        if (TxMsgObj->isFd)
        {
            msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] |= MESSAGE_BUFFER_CS_EDL_MASK;
            if (brs)
            {
                msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] |= MESSAGE_BUFFER_CS_BRS_MASK;
            }
            else
            {
                msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] &= ~MESSAGE_BUFFER_CS_BRS_MASK;
            }
        }
        else
        {
            msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM] &= ~(MESSAGE_BUFFER_CS_EDL_MASK
                                                       | MESSAGE_BUFFER_CS_BRS_MASK);
        }

        FLEXCANDRV_SetTxMsg(&base->CanHandle, TxMsgObj);
        /* transmit canfd Tx message */
        FLEXCANDRV_TransmitMsg(&base->CanHandle, TxMsgObj);

        return RT_EOK;
    }
}

static void _can_apply_bit_timing(FLEXCANDRV_BitTimingType *dst,
                                  const struct rt_can_bit_timing *src)
{
    dst->prescalerDiv    = src->prescaler;
    dst->resyncJumpWidth = src->num_sjw;
    dst->phaseSeg2       = src->num_seg2;

    if (src->num_seg1 > src->num_seg2)
    {
        dst->propSeg   = src->num_seg1 - src->num_seg2;
        dst->phaseSeg1 = src->num_seg2;
    }
    else
    {
        dst->propSeg   = 0U;
        dst->phaseSeg1 = src->num_seg1;
    }
}

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    ns800rt7_can *drv_can;
    rt_uint32_t baud_index;
    uint32_t flexcan_clock_freq;
    rt_uint8_t use_fd = 0U;
    rt_err_t ret;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    drv_can = (ns800rt7_can *)can->parent.user_data;
    RT_ASSERT(drv_can);

#ifdef RT_CAN_USING_CANFD
    use_fd = (cfg->enable_canfd && drv_can->fd_capable) ? 1U : 0U;
    if (cfg->enable_canfd && !drv_can->fd_capable)
    {
        LOG_E("%s does not support CAN-FD", drv_can->name);
        return -RT_ERROR;
    }
#endif

    _can_gpio_init(drv_can);
    ret = _can_clock_init(drv_can);
    if (ret != RT_EOK)
    {
        return ret;
    }
    flexcan_clock_freq = drv_can->clock_freq ? drv_can->clock_freq : BSP_CAN_CLOCK_FREQ;

    {
        FLEXCANDRV_InitHwParType initHwPar;

        initHwPar.canRamNum = drv_can->can_ram_num;
        initHwPar.canInstanceIdx = drv_can->can_instance_idx;
        FLEXCANDRV_Init(&(drv_can->CanHandle), drv_can->CanHandle.flexCanReg, &initHwPar);
    }

    FLEXCANDRV_GetDefaultCfg(&(drv_can->CanCfg));

    baud_index = get_can_baud_index(cfg->baud_rate);

#ifdef RT_CAN_USING_CANFD
    if (cfg->use_bit_timing)
    {
        _can_apply_bit_timing(&(drv_can->CanCfg.bitTiming), &(cfg->can_timing));
    }
    else
#endif
    {
        FLEXCANDRV_BitTimingCalc(&(drv_can->CanCfg.bitTiming),
                                 flexcan_clock_freq,
                                 BAUD_DATA(baud_index),
                                 7500,
                                 2500,
                                 0);
    }

    if (use_fd)
    {
#ifdef RT_CAN_USING_CANFD
        if (cfg->use_bit_timing)
        {
            _can_apply_bit_timing(&(drv_can->CanCfg.fdBitTiming), &(cfg->canfd_timing));
        }
        else
        {
            rt_uint32_t fd_baud = cfg->baud_rate_fd ? cfg->baud_rate_fd : BAUD_DATA(baud_index);

            FLEXCANDRV_BitTimingCalc(&(drv_can->CanCfg.fdBitTiming),
                                     flexcan_clock_freq,
                                     fd_baud,
                                     7500,
                                     2500,
                                     1);
        }
#endif
        drv_can->CanCfg.fdEnable         = true;
        drv_can->CanCfg.fdISOEnable      = true;
        drv_can->CanCfg.msgBufDataLenSel = FLEXCANDRV_MB_SIZE_BYTE_64;
    }
    else
    {
        if (drv_can->fd_capable)
        {
            FLEXCANDRV_BitTimingCalc(&(drv_can->CanCfg.fdBitTiming),
                                     flexcan_clock_freq,
                                     BAUD_DATA(baud_index),
                                     7500,
                                     2500,
                                     1);
            drv_can->CanCfg.fdEnable    = true;
            drv_can->CanCfg.fdISOEnable = true;
        }
        else
        {
            drv_can->CanCfg.fdEnable    = false;
            drv_can->CanCfg.fdISOEnable = false;
        }
        drv_can->CanCfg.msgBufDataLenSel = FLEXCANDRV_MB_SIZE_BYTE_8;
    }

    drv_can->CanCfg.clkSrc               = FLEXCANDRV_CLKSRC_OSC;
    drv_can->CanCfg.msgNum               = drv_can->FilterNum;
    drv_can->CanCfg.msgCfg               = drv_can->FilterConfig;
    drv_can->CanCfg.individualMaskEnable = true;
    drv_can->CanCfg.rxMBGlobalMask       = 0xFFFFFFFF;
    drv_can->CanCfg.loopbackEnable       = false;
    drv_can->CanCfg.listenMode           = false;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        break;
    case RT_CAN_MODE_LISTEN:
        drv_can->CanCfg.listenMode = true;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv_can->CanCfg.loopbackEnable = true;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        drv_can->CanCfg.listenMode = true;
        drv_can->CanCfg.loopbackEnable = true;
        break;
    default:
        return -RT_ERROR;
    }

    {
        rt_uint8_t i;

        for (i = 0; i < drv_can->FilterNum; i++)
        {
            drv_can->FilterConfig[i].isFd = use_fd;
            drv_can->FilterConfig[i].dlc = use_fd ? DLC_BYTE_64 : DLC_BYTE_8;
        }
    }

    FLEXCANDRV_Configure(&(drv_can->CanHandle), &(drv_can->CanCfg));

#ifdef RT_CAN_USING_CANFD
    drv_can->device.config.enable_canfd = use_fd;
    drv_can->device.config.baud_rate_fd = cfg->baud_rate_fd;
    drv_can->device.config.use_bit_timing = cfg->use_bit_timing;
    drv_can->device.config.can_timing = cfg->can_timing;
    drv_can->device.config.canfd_timing = cfg->canfd_timing;
#endif

    {
        rt_uint8_t k;

        for (k = 0; k < sizeof(drv_can->mbState) / sizeof(drv_can->mbState[0]); k++)
        {
            drv_can->mbState[k] = StateIdle;
        }
    }

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    ns800rt7_can *drv_can;

    RT_ASSERT(can != RT_NULL);
    drv_can = (ns800rt7_can *)can->parent.user_data;
    RT_ASSERT(drv_can != RT_NULL);
    FLEXCANREG_TypeDef *canReg = drv_can->CanHandle.flexCanReg;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        Interrupt_disable(drv_can->irqn1);
        Interrupt_disable(drv_can->irqn2);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        if (argval == RT_DEVICE_FLAG_INT_RX || argval == RT_DEVICE_FLAG_INT_TX)
        {
            Interrupt_register(drv_can->irqn1, drv_can->irq_handler);
            Interrupt_enable(drv_can->irqn1);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            Interrupt_register(drv_can->irqn2, drv_can->err_irq_handler);
            Interrupt_enable(drv_can->irqn2);
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        {
            struct rt_can_filter_config *filter_cfg;
            rt_uint8_t i;

            filter_cfg = (struct rt_can_filter_config *)arg;
            if (filter_cfg == RT_NULL)
            {
                return -RT_ERROR;
            }

            if (filter_cfg->actived != 1)
            {
                /* Deactivate filter: do nothing for now */
                return RT_EOK;
            }

            if (filter_cfg->count > RX_MB_COUNT)
            {
                return -RT_ERROR;
            }

            /* Write user filters starting from FilterConfig[TX_MB_COUNT],
             * preserving FilterConfig[0] which is the TX mailbox (MB0).
             * This prevents TX MB configuration from being overwritten
             * by RX filter settings. */
            for (i = 0; i < filter_cfg->count; i++)
            {
                struct rt_can_filter_item *item = &filter_cfg->items[i];
                rt_uint8_t idx = (rt_uint8_t)(TX_MB_COUNT + i);

                if (item->hdr_bank < -1 || item->hdr_bank >= (rt_int32_t)RX_MB_COUNT)
                {
                    return -RT_ERROR;
                }

                /* Map user hdr_bank to hardware MB index, offsetting past TX MB0.
                 * hdr_bank=-1 → auto-assign sequentially (MB1, MB2, ...)
                 * hdr_bank=N  → explicit hardware MB index (N still maps
                 *                to FilterConfig idx, via offset) */
                drv_can->FilterConfig[idx].msgBufId  =
                    (uint16_t)(item->hdr_bank >= 0
                               ? (rt_uint32_t)(TX_MB_COUNT + (rt_uint16_t)item->hdr_bank)
                               : idx);
                drv_can->FilterConfig[idx].msgBufLen = 1;
                drv_can->FilterConfig[idx].msgId     = item->id;
                drv_can->FilterConfig[idx].isExtMsgId = (item->ide == RT_CAN_EXTID);
                drv_can->FilterConfig[idx].msgType    = FLEXCANDRV_MSGTYPE_RX; /* default RX */
                drv_can->FilterConfig[idx].dlc        = DLC_BYTE_8;
#ifdef RT_CAN_USING_CANFD
                drv_can->FilterConfig[idx].isFd       =
                    drv_can->fd_capable ? drv_can->device.config.enable_canfd : 0U;
#else
                drv_can->FilterConfig[idx].isFd       = 0U;
#endif
                drv_can->FilterConfig[idx].intEnable  = true;
                /* FLEXCAN stores standard IDs at ID-word bits 18-28,
                 * extended IDs at bits 0-28.  The RXIMR mask register
                 * is bit-aligned with the ID word, so standard-frame
                 * masks must be shifted left by 18 bits. */
                if (item->ide == RT_CAN_EXTID)
                {
                    drv_can->FilterConfig[idx].individualMask =
                        item->mask & 0x1FFFFFFFUL;
                }
                else
                {
                    drv_can->FilterConfig[idx].individualMask =
                        (item->mask & 0x7FFUL) << MESSAGE_BUFFER_ID_STD_ID_SHIFT;
                }
                drv_can->FilterConfig[idx].rtrmask    = false;
                drv_can->FilterConfig[idx].rtrfilter  = false;
            }

            /* Update FilterNum to include TX MB + user filters */
            drv_can->FilterNum = (rt_uint8_t)(TX_MB_COUNT + filter_cfg->count);

            return _can_config(&drv_can->device, &drv_can->device.config);
        }
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
                argval != RT_CAN_MODE_LISTEN &&
                argval != RT_CAN_MODE_LOOPBACK &&
                argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }

        if (argval != drv_can->device.config.mode)
        {
            drv_can->device.config.mode = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t) arg;
        if (argval != CAN1MBaud &&
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
            drv_can->device.config.baud_rate = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
        argval = (rt_uint32_t) arg;
        if (argval > 1)
        {
            return -RT_ERROR;
        }

        if (argval && !drv_can->fd_capable)
        {
            return -RT_ERROR;
        }

        if ((rt_uint32_t)drv_can->device.config.enable_canfd != argval)
        {
            drv_can->device.config.enable_canfd = (rt_uint8_t)argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD_FD:
        argval = (rt_uint32_t) arg;
        if (argval == 0)
        {
            return -RT_ERROR;
        }

        if (!drv_can->fd_capable)
        {
            return -RT_ERROR;
        }

        if (argval != drv_can->device.config.baud_rate_fd)
        {
            drv_can->device.config.baud_rate_fd = argval;
            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
    case RT_CAN_CMD_SET_BITTIMING:
        {
            struct rt_can_bit_timing_config *timing_cfg;
            struct rt_can_bit_timing *rt_timing;

            timing_cfg = (struct rt_can_bit_timing_config *)arg;
            if (timing_cfg == RT_NULL || timing_cfg->items == RT_NULL)
            {
                return -RT_ERROR;
            }

            if (timing_cfg->count < 1 || (!drv_can->fd_capable && timing_cfg->count > 1))
            {
                return -RT_ERROR;
            }

            if (drv_can->device.config.enable_canfd && timing_cfg->count < 2)
            {
                return -RT_ERROR;
            }

            drv_can->device.config.use_bit_timing = 1;

            if (timing_cfg->count >= 1)
            {
                rt_timing = &timing_cfg->items[0];
                drv_can->device.config.can_timing = *rt_timing;
            }

            if (timing_cfg->count >= 2)
            {
                rt_timing = &timing_cfg->items[1];
                drv_can->device.config.canfd_timing = *rt_timing;
            }

            return _can_config(&drv_can->device, &drv_can->device.config);
        }
        break;
#endif /* RT_CAN_USING_CANFD */
    case RT_CAN_CMD_START:
        /* Controller starts automatically during _can_config().
         * For a true start/stop, re-init would be needed.
         * This command is a no-op for this driver. */
        break;
    case RT_CAN_CMD_SET_PRIV:
        return -RT_ERROR;
        break;
    case RT_CAN_CMD_GET_STATUS:
        drv_can->device.status.rcverrcnt = FLEXCANREG_GetEcrRxerrcnt(canReg);
        drv_can->device.status.snderrcnt = FLEXCANREG_GetEcrTxerrcnt(canReg);
        /* drv_can->device.status.lasterrtype = errtype & 0x70; */
        /* drv_can->device.status.errcode = errtype & 0x07; */

        rt_memcpy(arg, &drv_can->device.status, sizeof(drv_can->device.status));
        break;
    }

    return RT_EOK;
}

/* DLC / byte-length validation helpers classic CAN vs CAN-FD */
#ifdef RT_CAN_USING_CANFD
#ifndef CANFD_MAX_DLC
#define CANFD_MAX_DLC            15U     /* per ISO 11898-1 */
#endif

/**
 * @brief Convert data byte length to CAN-FD DLC code (per ISO 11898-1).
 *        Based on the standard can_len2dlc() lookup in can_dm.c.
 */
static rt_uint8_t _can_len_to_dlc(rt_uint8_t len)
{
    static const rt_uint8_t len2dlc[65] =
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8,  /* 0-8   bytes  DLC 0-8 */
        9, 9, 9, 9,                  /* 9-12  bytes DLC 9 */
        10, 10, 10, 10,              /* 13-16 bytes  DLC 10 */
        11, 11, 11, 11,              /* 17-20 bytes  DLC 11 */
        12, 12, 12, 12,              /* 21-24 bytes  DLC 12 */
        13, 13, 13, 13, 13, 13, 13, 13, /* 25-32 bytes  DLC 13 */
        14, 14, 14, 14, 14, 14, 14, 14, /* 33-48 bytes  DLC 14 */
        14, 14, 14, 14, 14, 14, 14, 14, /* (continued) */
        15, 15, 15, 15, 15, 15, 15, 15, /* 49-64 bytes  DLC 15 */
        15, 15, 15, 15, 15, 15, 15, 15  /* (continued) */
    };
    return len < 65 ? len2dlc[len] : (rt_uint8_t)CANFD_MAX_DLC;
}

#define IS_CAN_LEN_VALID(LEN)    ((LEN) <= 64U)
#else
#define IS_CAN_LEN_VALID(LEN)    ((LEN) <= 8U)
#endif

/**
 * @internal
 * @brief Low-level function to send a CAN message to a specific hardware mailbox.
 *
 * This function is part of the **blocking** send mechanism. It is called by
 * `_can_int_tx` after a hardware mailbox has already been acquired.
 *
 * @param[in] can     A pointer to the CAN device structure.
 * @param[in] buf     A pointer to the `rt_can_msg` to be sent.
 * @param[in] box_no  The specific hardware mailbox index to use for this
 *                    transmission.
 *
 * @return `RT_EOK` on success, or an error code on failure.
 */
static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_no)
{
    rt_ssize_t status;
    ns800rt7_can *hcan;
    struct rt_can_msg *pmsg;
    FLEXCANDRV_MsgObjType fdTxMsgObj;
    rt_uint8_t data_len;

    hcan = (ns800rt7_can *) can->parent.user_data;
    pmsg = (struct rt_can_msg *) buf;

    if (box_no >= TX_MB_COUNT || !IS_CAN_LEN_VALID(pmsg->len))
    {
        return -RT_ERROR;
    }

#ifdef RT_CAN_USING_CANFD
    if (pmsg->fd_frame && (!hcan->fd_capable || !hcan->device.config.enable_canfd))
    {
        return -RT_ERROR;
    }

    if (!pmsg->fd_frame && pmsg->len > 8U)
    {
        return -RT_ERROR;
    }
#endif

    rt_memset(&fdTxMsgObj, 0, sizeof(fdTxMsgObj));
    fdTxMsgObj.msgBufId = box_no;

    /* Convert byte length to hardware DLC code and determine payload size */
    data_len = pmsg->len;
#ifdef RT_CAN_USING_CANFD
    fdTxMsgObj.dlc = _can_len_to_dlc(pmsg->len);
    fdTxMsgObj.isFd = (pmsg->fd_frame != 0 && hcan->device.config.enable_canfd) ? true : false;
#else
    fdTxMsgObj.dlc = pmsg->len;  /* classic CAN: DLC == byte length (0-8) */
#endif

    /* Copy payload */
    rt_memcpy(fdTxMsgObj.data, pmsg->data, data_len);

    status = _can_sendBlocking(hcan, &fdTxMsgObj,
                               pmsg->id, (pmsg->ide == RT_CAN_EXTID) ? 1 : 0,
#ifdef RT_CAN_USING_CANFD
                               (rt_uint8_t)(pmsg->brs != 0 ? 1 : 0));
#else
                               0U);
#endif

    return status;
}

/**
 * @internal
 * @brief Low-level non-blocking send. Places message into hardware mailbox
 *        directly without waiting if the mailbox is idle.
 *
 * @param[in] can A pointer to the CAN device structure.
 * @param[in] buf A pointer to the `rt_can_msg` to be sent.
 *
 * @return `RT_EOK` on success, `-RT_EBUSY` if TX mailbox is busy,
 *         or other error code on failure.
 */
static rt_ssize_t _can_sendmsg_nonblocking(struct rt_can_device *can, const void *buf)
{
    ns800rt7_can *hcan;
    struct rt_can_msg *pmsg;
    FLEXCANDRV_MsgObjType fdTxMsgObj;
    rt_uint8_t data_len;

    RT_ASSERT(can);
    RT_ASSERT(buf);
    hcan = (ns800rt7_can *)can->parent.user_data;
    pmsg = (struct rt_can_msg *)buf;

    /* Check if TX MB (MB0) is idle */
    if (StateIdle != hcan->mbState[0])
    {
        return -RT_EBUSY;
    }

    /* Validate payload byte length */
    if (!IS_CAN_LEN_VALID(pmsg->len))
    {
        return -RT_ERROR;
    }

#ifdef RT_CAN_USING_CANFD
    if (pmsg->fd_frame && (!hcan->fd_capable || !hcan->device.config.enable_canfd))
    {
        return -RT_ERROR;
    }

    if (!pmsg->fd_frame && pmsg->len > 8U)
    {
        return -RT_ERROR;
    }
#endif

    rt_memset(&fdTxMsgObj, 0, sizeof(fdTxMsgObj));
    fdTxMsgObj.msgBufId = 0;  /* MB0 is the dedicated TX mailbox */

    /* Convert byte length to hardware DLC code */
    data_len = pmsg->len;
#ifdef RT_CAN_USING_CANFD
    fdTxMsgObj.dlc = _can_len_to_dlc(pmsg->len);
    fdTxMsgObj.isFd = (pmsg->fd_frame != 0 && hcan->device.config.enable_canfd) ? true : false;
#else
    fdTxMsgObj.dlc = pmsg->len;
#endif

    rt_memcpy(fdTxMsgObj.data, pmsg->data, data_len);

    return _can_sendBlocking(hcan, &fdTxMsgObj,
                             pmsg->id, (pmsg->ide == RT_CAN_EXTID) ? 1 : 0,
#ifdef RT_CAN_USING_CANFD
                             (rt_uint8_t)(pmsg->brs != 0 ? 1 : 0));
#else
                             0U);
#endif
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct rt_can_msg *pmsg;
    ns800rt7_can *hcan;
    rt_uint8_t data_len;
    rt_uint8_t frame_idx;
    rt_uint8_t mb_idx;

    RT_ASSERT(can);
    hcan = (ns800rt7_can *)can->parent.user_data;
    pmsg = (struct rt_can_msg *) buf;

    /* Zero out the message, then fill from hardware frame buffer */
    rt_memset(pmsg, 0, sizeof(struct rt_can_msg));
    pmsg->rxfifo    = (rt_uint32_t)fifo;

    /* Select the correct frame buffer: MB1:rx_frame[0], MB2:rx_frame[1] */
    frame_idx = (fifo >= TX_MB_COUNT && fifo < TOTAL_MB_COUNT) ?
                (rt_uint8_t)(fifo - TX_MB_COUNT) : 0U;
    mb_idx   = (rt_uint8_t)fifo;  /* hardware MB index (1 or 2) */

    /* Set hdr_index to the filter bank index (0 for MB1, 1 for MB2).
     * When RT_CAN_USING_HDR is enabled, rt_hw_can_isr() asserts
     * hdr_index >= 0 and hdr_index < maxhdr.  -1 would trigger
     * an assertion failure. */
    pmsg->hdr_index = (rt_int8_t)frame_idx;

    /* rx_frame[N].dlc is already converted from DLC code to byte length
     * by FLEXCANDRV_DLC2DataLen() inside FLEXCANDRV_GetRxMsg().
     * Store as byte length in the RT-Thread message len field. */
    pmsg->id  = hcan->rx_frame[frame_idx].msgId;
    data_len = (rt_uint8_t)hcan->rx_frame[frame_idx].dlc;
    if (data_len > sizeof(pmsg->data))
    {
        data_len = sizeof(pmsg->data);
    }
    pmsg->len = data_len;

    /* Read IDE, RTR, and BRS from the hardware MB CS word.
     * FLEXCANDRV_GetRxMsg() does not report these fields individually,
     * but they are available in the CS word of the received frame.
     * CS word bits: 31=EDL(FD), 30=BRS, 21=IDE, 20=RTR */
    {
        uint32_t *msgBufPtr = (uint32_t *)FLEXCANDRV_GetMsgBufStartAddr(
                                   &hcan->CanHandle, mb_idx);
        uint32_t cs_word = msgBufPtr[MESSAGE_BUFFER_CS_WORD_NUM];
        pmsg->ide = (cs_word & MESSAGE_BUFFER_CS_IDE_MASK)
                        ? RT_CAN_EXTID : RT_CAN_STDID;
        pmsg->rtr = (cs_word & MESSAGE_BUFFER_CS_RTR_MASK)
                        ? RT_CAN_RTR : RT_CAN_DTR;
#ifdef RT_CAN_USING_CANFD
        pmsg->fd_frame = (cs_word & MESSAGE_BUFFER_CS_EDL_MASK) ? 1 : 0;
        pmsg->brs      = (cs_word & MESSAGE_BUFFER_CS_BRS_MASK) ? 1 : 0;
#endif
    }

    /* Bulk copy payload from frame buffer */
    rt_memcpy(pmsg->data, hcan->rx_frame[frame_idx].data, data_len);

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
{
    .configure             = _can_config,
    .control               = _can_control,
    .sendmsg               = _can_sendmsg,
    .recvmsg               = _can_recvmsg,
    .sendmsg_nonblocking   = _can_sendmsg_nonblocking,
};

static uint8_t FLEXCANREG_GetMsgBufInterruptMask (FLEXCANREG_TypeDef *obj, uint32_t msgBufferIdx)
{
    uint32_t temp, temp1 = 0;

    temp1 = msgBufferIdx % 32;
    temp  = 0x00000001UL << temp1;

    if (msgBufferIdx > 95)
    {
        temp &= obj->IMASK4;
    }
    else if (msgBufferIdx > 63)
    {
        temp &= obj->IMASK3;
    }
    else if (msgBufferIdx > 31)
    {
        temp &= obj->IMASK2;
    }
    else
    {
        temp &= obj->IMASK1;
    }

    if (temp)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

static void _can_tx_rx_isr(struct rt_can_device *can)
{
    uint8_t flag, mask;
    ns800rt7_can *hcan;
    FLEXCANDRV_MsgObjType msgObj;
    uint32_t result;

    RT_ASSERT(can);
    hcan = (ns800rt7_can *) can->parent.user_data;
    RT_ASSERT(hcan);

    while (RT_TRUE)
    {
        /* For this implementation, we solve the Message with lowest MB index first. */
        for (result = 0; result < TOTAL_MB_COUNT; result++)
        {
            flag = FLEXCANDRV_GetMsgObjFlag(&(hcan->CanHandle), result);
            mask = FLEXCANREG_GetMsgBufInterruptMask(hcan->CanHandle.flexCanReg, result);
            /* Get the lowest unhandled Message Buffer */
            if ((flag != 0) && (mask != 0))
            {
                break;
            }
        }

        /* Does not find Message to deal with. */
        if (result == TOTAL_MB_COUNT)
        {
            break;
        }

        if (result == 0U)
        {
            hcan->mbState[result] = StateIdle;
            rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | (result << 8));
        }
        else if (result >= TX_MB_COUNT && result < TOTAL_MB_COUNT)
        {
            rt_uint8_t frame_idx = (rt_uint8_t)(result - TX_MB_COUNT);

            msgObj.msgBufId = result;
            FLEXCANDRV_GetRxMsg(&hcan->CanHandle, &msgObj);
            rt_memcpy(&hcan->rx_frame[frame_idx], &msgObj, sizeof(msgObj));
            hcan->mbState[result] = StateIdle;
            rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | (result << 8));
        }

        FLEXCANDRV_ClearMsgObjFlag(&(hcan->CanHandle), result);
    }
}

static void _can_err_isr(struct rt_can_device *can)
{
    RT_ASSERT(can);
    ns800rt7_can *hcan = (ns800rt7_can *)can->parent.user_data;

    /* Read error status from hardware to clear interrupt flags */
    FLEXCANDRV_ErrStatusType errStatus;
    rt_memset(&errStatus, 0, sizeof(errStatus));
    FLEXCANDRV_GetErrorStatusFlag(&hcan->CanHandle, &errStatus);
    FLEXCANDRV_ClearErrStatusFlag(&hcan->CanHandle, FLEXCANDRV_ERR_STATUS_MASK_ALL);

    /* Update device error counters */
    FLEXCANREG_TypeDef *canReg = hcan->CanHandle.flexCanReg;
    can->status.rcverrcnt = FLEXCANREG_GetEcrRxerrcnt(canReg);
    can->status.snderrcnt = FLEXCANREG_GetEcrTxerrcnt(canReg);

#ifdef RT_CAN_USING_CANFD
    /* Accumulate FD-specific error counters */
    can->status.biterrcnt  += errStatus.bit1FastErr;
    can->status.biterrcnt  += errStatus.bit0FastErr;
    can->status.crcerrcnt  += errStatus.crcFastErr;
    can->status.formaterrcnt += errStatus.formFastErr;
    can->status.bitpaderrcnt += errStatus.stuffFastErr;
#endif
    can->status.ackerrcnt  += errStatus.ackErr;
    can->status.crcerrcnt  += errStatus.crcErr;
    can->status.formaterrcnt += errStatus.formErr;
    can->status.bitpaderrcnt += errStatus.stuffErr;
    can->status.biterrcnt  += errStatus.bit1Err + errStatus.bit0Err;
}

#ifdef BSP_USING_CAN1
void CAN1_1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_tx_rx_isr(&drv_can1.device);
    rt_interrupt_leave();
}

void CAN1_2_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_err_isr(&drv_can1.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CANFD1
void CANFD1_1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_tx_rx_isr(&drv_canfd1.device);
    rt_interrupt_leave();
}

void CANFD1_2_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_err_isr(&drv_canfd1.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CANFD1 */

#ifdef BSP_USING_CANFD2
void CANFD2_1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_tx_rx_isr(&drv_canfd2.device);
    rt_interrupt_leave();
}

void CANFD2_2_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_err_isr(&drv_canfd2.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CANFD2 */

static void _can_default_filter_init(ns800rt7_can *drv_can, rt_uint8_t use_fd)
{
    rt_memset(drv_can->FilterConfig, 0, sizeof(drv_can->FilterConfig));

    drv_can->FilterConfig[0].msgBufId       = 0;
    drv_can->FilterConfig[0].msgBufLen      = 1;
    drv_can->FilterConfig[0].msgId          = 0x78;
    drv_can->FilterConfig[0].isExtMsgId     = false;
    drv_can->FilterConfig[0].msgType        = FLEXCANDRV_MSGTYPE_TX;
    drv_can->FilterConfig[0].dlc            = use_fd ? DLC_BYTE_64 : DLC_BYTE_8;
    drv_can->FilterConfig[0].isFd           = use_fd;
    drv_can->FilterConfig[0].intEnable      = true;
    drv_can->FilterConfig[0].individualMask = 0xFFFFFFFF;
    drv_can->FilterConfig[0].rtrmask        = false;
    drv_can->FilterConfig[0].rtrfilter      = false;

    drv_can->FilterConfig[1].msgBufId       = 1;
    drv_can->FilterConfig[1].msgBufLen      = 1;
    drv_can->FilterConfig[1].msgId          = 0;
    drv_can->FilterConfig[1].isExtMsgId     = false;
    drv_can->FilterConfig[1].msgType        = FLEXCANDRV_MSGTYPE_RX;
    drv_can->FilterConfig[1].dlc            = use_fd ? DLC_BYTE_64 : DLC_BYTE_8;
    drv_can->FilterConfig[1].isFd           = use_fd;
    drv_can->FilterConfig[1].intEnable      = true;
    drv_can->FilterConfig[1].individualMask = 0;
    drv_can->FilterConfig[1].rtrmask        = false;
    drv_can->FilterConfig[1].rtrfilter      = false;

    drv_can->FilterConfig[2].msgBufId       = 2;
    drv_can->FilterConfig[2].msgBufLen      = 1;
    drv_can->FilterConfig[2].msgId          = 0;
    drv_can->FilterConfig[2].isExtMsgId     = true;
    drv_can->FilterConfig[2].msgType        = FLEXCANDRV_MSGTYPE_RX;
    drv_can->FilterConfig[2].dlc            = use_fd ? DLC_BYTE_64 : DLC_BYTE_8;
    drv_can->FilterConfig[2].isFd           = use_fd;
    drv_can->FilterConfig[2].intEnable      = true;
    drv_can->FilterConfig[2].individualMask = 0;
    drv_can->FilterConfig[2].rtrmask        = false;
    drv_can->FilterConfig[2].rtrfilter      = false;

    drv_can->FilterNum = TOTAL_MB_COUNT;
}

int rt_hw_can_init(void)
{
    int ret = RT_EOK;
    struct can_configure config = CANDEFAULTCONFIG;
    rt_uint32_t i;

    config.privmode = RT_CAN_MODE_NOPRIV;

    config.ticks = 50;
    config.sndboxnumber = TX_MB_COUNT;
    config.msgboxsz = RX_MB_COUNT;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = RX_MB_COUNT;          /* filter count,one filter per MB */
#endif

    for (i = 0; i < sizeof(can_devices) / sizeof(can_devices[0]); i++)
    {
        ns800rt7_can *drv_can = can_devices[i];
        struct can_configure dev_config = config;

#ifdef RT_CAN_USING_CANFD
        dev_config.enable_canfd = drv_can->fd_capable ? 1U : 0U;
#endif
        _can_default_filter_init(drv_can,
#ifdef RT_CAN_USING_CANFD
                                 dev_config.enable_canfd
#else
                                 0U
#endif
                                );

        drv_can->device.config = dev_config;
        ret = rt_hw_can_register(&drv_can->device, drv_can->name, &_can_ops, drv_can);
        if (ret != RT_EOK)
        {
            break;
        }
    }

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/
