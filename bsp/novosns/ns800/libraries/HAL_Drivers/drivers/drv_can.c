/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-05     Xeon Xu      the first version
 * 2019-01-22     YLZ          port from stm324xx-HAL to bsp stm3210x-HAL
 * 2019-02-19     YLZ          add support EXTID RTR Frame. modify send, recv functions.
 *                             fix bug.port to BSP [stm32]
 * 2019-03-27     YLZ          support double can channels, support stm32F4xx (only Legacy mode).
 * 2019-06-17     YLZ          port to new STM32F1xx HAL V1.1.3.
 * 2021-02-02     YuZhe XU     fix bug in filter config
 * 2021-8-25      SVCHAO       The baud rate is configured according to the different APB1 frequencies.
                               f4-series only.
 * 2025-09-20     wdfk_prog    Implemented sendmsg_nonblocking op to support framework's async TX.
 * 2026-02-02     wdfk_prog    Drain multiple RX frames per ISR with a bounded limit.
 * 2026-05-30     hu.tang   Add CAN-FD full support: dynamic MB size, FD data path,
 *                             FD control commands, sendmsg_nonblocking, fix hdr_index bug.
 */

#include "drv_can.h"

#ifdef BSP_USING_CAN

#define LOG_TAG    "drv_can"
#include <drv_log.h>


#define RX_MB_COUNT     (2)
static FLEXCANDRV_MsgObjType frame[RX_MB_COUNT];    /* one frame buffer per RX MB */

void CAN_Handler(void);
void CAN_Err_Handler(void);


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
    .CanHandle.flexCanReg = (FLEXCANREG_TypeDef *)CAN1,
    .irqn1 = CAN1_1_IRQn,
    .irqn2 = CAN1_2_IRQn,
};
#endif

#ifdef BSP_USING_CANFD1
static ns800rt7_can drv_can1 =
{
    .name = "canfd1",
    .CanHandle.flexCanReg = (FLEXCANREG_TypeDef *)CANFD1,
    .irqn1 = CANFD1_1_IRQn,
    .irqn2 = CANFD1_2_IRQn,
};
#endif

#ifdef BSP_USING_CANFD2
static ns800rt7_can drv_can1 =
{
    .name = "canfd2",
    .CanHandle.flexCanReg = (FLEXCANREG_TypeDef *)CANFD2,
    .irqn1 = CANFD2_1_IRQn,
    .irqn2 = CANFD2_2_IRQn,
};
#endif

static void _can_gpio_init(void)
{
#ifdef BSP_USING_CAN1
    GPIO_setAnalogMode(GPIO_4, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(GPIO_10, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_4_CANFD1_TX);
    GPIO_setPinConfig(GPIO_10_CANFD1_RX);
#endif

#ifdef BSP_USING_CANFD1
    GPIO_setAnalogMode(GPIO_4, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(GPIO_10, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_4_CANFD1_TX);
    GPIO_setPinConfig(GPIO_10_CANFD1_RX);
#endif

#ifdef BSP_USING_CANFD2
    GPIO_setAnalogMode(GPIO_4, GPIO_ANALOG_DISABLED);
    GPIO_setAnalogMode(GPIO_10, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_4_CANFD1_TX);
    GPIO_setPinConfig(GPIO_10_CANFD1_RX);
#endif
}

static void _can_clock_init(void)
{
    /* unlock RCC register access */
    RCC_unlockRccRegister();

#if CAN_CLOCK_SELECTION == CAN_USING_EXTERNAL_OSC

    /* setup external OSC if selected */
    /* configure HXTL */
    WRITE_REG(RCC->HXTLCR.WORDVAL, (HXTL_CONFIG | RCC_HXTLCR_KEY));
    RCC_enableHxtl();
    RCC_disableHxtlBypass();

    uint32_t wait_time = 5000000;
    while ((RCC_readHxtlRdyFlag() != 1) && (--wait_time));
    while (wait_time == 0)
    {
    }

    /* enable MIRC2 and HXTL kernal func */
    RCC_enablePeriphKernalUseMirc2();
    RCC_enablePeriphKernalUseHxtl();
    /* select the HXTL as the working clocks for CANFD1 */
     RCC_selectCanfdOscClkSource(RCC_CANFD1SEL, RCC_CANFD_OSCCLK_SEL_HXTLKER);
#elif CAN_CLOCK_SELECTION == CAN_USING_INTERNAL_CLOCK

    /* enable MIRC2 kernal func */
    RCC_enableKernalUseMirc2();
    /* select the HXTL as the working clocks for CANFD1 */
    RCC_selectCanfdOscClkSource(RCC_CANFD1SEL, RCC_CANFD_OSCCLK_SEL_MIRC2KER);
#endif

    /* enable CANFD clocks */
    RCC_enableCanfd1Clock();

    /* lock RCC register access */
    RCC_lockRccRegister();
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
                                   rt_uint32_t msg_id, rt_uint8_t is_ext_id)
{
    /* Check if Message Buffer is idle. */
    if (StateIdle == base->mbState[TxMsgObj->msgBufId])
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
        /* Also re-apply FD enable (EDL/BRS bits) per-frame.
         * The hardware may modify CS bits after TX completion. */
        FLEXCANDRV_SetFDEnable(msgBufPtr, TxMsgObj->isFd);

        FLEXCANDRV_SetTxMsg(&base->CanHandle, TxMsgObj);
        /* transmit canfd Tx message */
        FLEXCANDRV_TransmitMsg(&base->CanHandle, TxMsgObj);

        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    ns800rt7_can *drv_can;
    rt_uint32_t baud_index;
    uint32_t FlexcanClockFreq = HXTL_FREQ_VALUE;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    drv_can = (ns800rt7_can *)can->parent.user_data;
    RT_ASSERT(drv_can);

    _can_gpio_init();
    _can_clock_init();

    FLEXCANDRV_InitHwParType initHwPar;
    initHwPar.canRamNum = 4;
    initHwPar.canInstanceIdx = 1;
    FLEXCANDRV_Init(&(drv_can->CanHandle), drv_can->CanHandle.flexCanReg, &initHwPar);

    /* get FLEXCAN controller default configuration */
    FLEXCANDRV_GetDefaultCfg(&(drv_can->CanCfg));

    /* --- Nominal (arbitration phase) bit timing --- */
    baud_index = get_can_baud_index(cfg->baud_rate);

    FLEXCANDRV_BitTimingCalc(&(drv_can->CanCfg.bitTiming),
                             FlexcanClockFreq,
                             BAUD_DATA(baud_index),
                             7500,       /* sample point: 75% */
                             2500,       /* SJW: 25% */
                             0);         /* classic CAN bit timing */

    /* --- CAN-FD data phase bit timing --- */
#ifdef RT_CAN_USING_CANFD
    if (cfg->enable_canfd)
    {
        rt_uint32_t fd_baud;

        /* Use FD data phase baud rate if specified, otherwise same as nominal */
        if (cfg->baud_rate_fd > 0)
        {
            fd_baud = cfg->baud_rate_fd;
        }
        else
        {
            fd_baud = BAUD_DATA(baud_index);
        }

        FLEXCANDRV_BitTimingCalc(&(drv_can->CanCfg.fdBitTiming),
                                 FlexcanClockFreq,
                                 fd_baud,
                                 7500,       /* sample point: 75% */
                                 2500,       /* SJW: 25% */
                                 1);         /* CANFD bit timing */

        drv_can->CanCfg.fdEnable        = true;
        drv_can->CanCfg.fdISOEnable     = true;
        drv_can->CanCfg.msgBufDataLenSel = FLEXCANDRV_MB_SIZE_BYTE_64;
    }
    else
#endif /* RT_CAN_USING_CANFD */
    {
        /* Classic CAN mode: 8-byte MB.
         * NOTE: fdEnable and fdISOEnable must stay TRUE the NS800
         * FLEXCAN controller requires FD mode to be enabled at the
         * controller level even for classic CAN operation.  Individual
         * MBs are configured as classic CAN via isFd=false / dlc=DLC_BYTE_8
         * in the FilterConfig sync below. */
        FLEXCANDRV_BitTimingCalc(&(drv_can->CanCfg.fdBitTiming),
                                 FlexcanClockFreq,
                                 BAUD_DATA(baud_index),
                                 7500, 2500,
                                 1);         /* still need a valid fdBitTiming even in classic mode */

        drv_can->CanCfg.fdEnable        = true;
        drv_can->CanCfg.fdISOEnable     = true;
        drv_can->CanCfg.msgBufDataLenSel = FLEXCANDRV_MB_SIZE_BYTE_8;
    }

    drv_can->CanCfg.clkSrc                  = FLEXCANDRV_CLKSRC_OSC;
    drv_can->CanCfg.msgNum                  = drv_can->FilterNum;
    drv_can->CanCfg.msgCfg                  = drv_can->FilterConfig;
    drv_can->CanCfg.individualMaskEnable    = true;
    drv_can->CanCfg.rxMBGlobalMask          = 0xFFFFFFFF;
    drv_can->CanCfg.loopbackEnable          = false;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        /* default mode */
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
    }

    /* --- Sync FilterConfig with controller settings BEFORE Configure --- */
    {
        rt_uint8_t i;
        rt_uint8_t use_fd;
#ifdef RT_CAN_USING_CANFD
        use_fd = cfg->enable_canfd;
#else
        use_fd = 0;
#endif
        for (i = 0; i < drv_can->FilterNum; i++)
        {
            drv_can->FilterConfig[i].isFd = use_fd;
#ifdef RT_CAN_USING_CANFD
            if (use_fd)
            {
                drv_can->FilterConfig[i].dlc = DLC_BYTE_64;
            }
            else
#endif
            {
                drv_can->FilterConfig[i].dlc = DLC_BYTE_8;
            }
        }
    }
    /* init can */
    /* initialize FLEXCAN module */
    FLEXCANDRV_Configure(&(drv_can->CanHandle), &(drv_can->CanCfg));

    /* Sync config back to device subsequent SET_MODE/SET_BAUD/SET_FILTER
     * calls use drv_can->device.config to determine FD vs classic mode. */
    drv_can->device.config.enable_canfd = cfg->enable_canfd;
    drv_can->device.config.baud_rate_fd = cfg->baud_rate_fd;

    /* Reset MB state tracking the hardware controller has been
     * reconfigured, so all mailboxes are now idle. */
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
            Interrupt_register(drv_can->irqn1, &CAN_Handler);
            Interrupt_enable(drv_can->irqn1);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            Interrupt_register(drv_can->irqn2, &CAN_Err_Handler);
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

            if (filter_cfg->count > CAN_FILTER_NUM_MAX)
            {
                return -RT_ERROR;
            }

            for (i = 0; i < filter_cfg->count; i++)
            {
                struct rt_can_filter_item *item = &filter_cfg->items[i];

                drv_can->FilterConfig[i].msgBufId  = (uint16_t)(item->hdr_bank >= 0 ? item->hdr_bank : i);
                drv_can->FilterConfig[i].msgBufLen = 1;
                drv_can->FilterConfig[i].msgId     = item->id;
                drv_can->FilterConfig[i].isExtMsgId = (item->ide == RT_CAN_EXTID);
                drv_can->FilterConfig[i].msgType    = FLEXCANDRV_MSGTYPE_RX; /* default RX */
                drv_can->FilterConfig[i].dlc        = DLC_BYTE_8;
                drv_can->FilterConfig[i].isFd       = drv_can->device.config.enable_canfd;
                drv_can->FilterConfig[i].intEnable  = true;
                drv_can->FilterConfig[i].individualMask = item->mask;
                drv_can->FilterConfig[i].rtrmask    = false;
                drv_can->FilterConfig[i].rtrfilter  = false;
            }

            drv_can->FilterNum = filter_cfg->count;
        }
        break;
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

            /* Apply arbitration phase timing (items[0]) */
            if (timing_cfg->count >= 1)
            {
                rt_timing = &timing_cfg->items[0];
                drv_can->CanCfg.bitTiming.prescalerDiv    = rt_timing->prescaler;
                drv_can->CanCfg.bitTiming.resyncJumpWidth = rt_timing->num_sjw;
                drv_can->CanCfg.bitTiming.phaseSeg2       = rt_timing->num_seg2;
                drv_can->CanCfg.bitTiming.propSeg         = rt_timing->num_seg1 - rt_timing->num_seg2;
                drv_can->CanCfg.bitTiming.phaseSeg1       = rt_timing->num_seg2;
            }

            /* Apply data phase timing (items[1]) */
            if (timing_cfg->count >= 2)
            {
                rt_timing = &timing_cfg->items[1];
                drv_can->CanCfg.fdBitTiming.prescalerDiv    = rt_timing->prescaler;
                drv_can->CanCfg.fdBitTiming.resyncJumpWidth = rt_timing->num_sjw;
                drv_can->CanCfg.fdBitTiming.phaseSeg2       = rt_timing->num_seg2;
                drv_can->CanCfg.fdBitTiming.propSeg         = rt_timing->num_seg1 - rt_timing->num_seg2;
                drv_can->CanCfg.fdBitTiming.phaseSeg1       = rt_timing->num_seg2;
            }

            /* Re-configure with custom bit timing */
            drv_can->device.config.use_bit_timing = 1;
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

/* DLC validation helper classic CAN vs CAN-FD */
#ifdef RT_CAN_USING_CANFD
#ifndef CANFD_MAX_DLC
#define CANFD_MAX_DLC            15U     /* per ISO 11898-1 */
#endif
#define IS_CAN_DLC_VALID(DLC)    (((DLC) & 0x0FU) <= CANFD_MAX_DLC)

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

/**
 * @brief Convert CAN-FD DLC code to data byte length (per ISO 11898-1).
 */
static rt_uint8_t _can_dlc_to_len(rt_uint8_t dlc)
{
    static const rt_uint8_t dlc2len[16] =
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8,  /* DLC 0-8: direct mapping */
        12, 16, 20, 24, 32, 48, 64   /* DLC 9-15: FD sizes */
    };
    return dlc2len[dlc & 0x0FU];
}
#else
#define IS_CAN_DLC_VALID(DLC)    (((DLC) & 0x0FU) <= 0x08U)
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

    /* Validate DLC */
    RT_ASSERT(IS_CAN_DLC_VALID(pmsg->len));

    rt_memset(&fdTxMsgObj, 0, sizeof(fdTxMsgObj));
    fdTxMsgObj.msgBufId = box_no;

    /* Set up the DLC */
    fdTxMsgObj.dlc = pmsg->len & 0x0FU;

    /* Determine data length from DLC */
#ifdef RT_CAN_USING_CANFD
    data_len = _can_dlc_to_len((rt_uint8_t)(pmsg->len & 0x0FU));
    fdTxMsgObj.isFd = (pmsg->fd_frame != 0) ? true : false;
#else
    data_len = (rt_uint8_t)(pmsg->len & 0x0FU);
    if (data_len > 8) { data_len = 8; }
#endif

    /* Copy payload */
    rt_memcpy(fdTxMsgObj.data, pmsg->data, data_len);

    status = _can_sendBlocking(hcan, &fdTxMsgObj,
                               pmsg->id, (pmsg->ide == RT_CAN_EXTID) ? 1 : 0);

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

    /* Validate DLC */
    if (!IS_CAN_DLC_VALID(pmsg->len))
    {
        return -RT_ERROR;
    }

    rt_memset(&fdTxMsgObj, 0, sizeof(fdTxMsgObj));
    fdTxMsgObj.msgBufId = 0;  /* MB0 is the dedicated TX mailbox */

    fdTxMsgObj.dlc = pmsg->len & 0x0FU;

#ifdef RT_CAN_USING_CANFD
    data_len = _can_dlc_to_len((rt_uint8_t)(pmsg->len & 0x0FU));
    fdTxMsgObj.isFd = (pmsg->fd_frame != 0) ? true : false;
#else
    data_len = (rt_uint8_t)(pmsg->len & 0x0FU);
    if (data_len > 8) { data_len = 8; }
#endif

    rt_memcpy(fdTxMsgObj.data, pmsg->data, data_len);

    return _can_sendBlocking(hcan, &fdTxMsgObj,
                             pmsg->id, (pmsg->ide == RT_CAN_EXTID) ? 1 : 0);
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct rt_can_msg *pmsg;
    rt_uint8_t data_len;
    rt_uint8_t frame_idx;

    RT_ASSERT(can);

    pmsg = (struct rt_can_msg *) buf;

    /* Zero out the message, then fill from hardware frame buffer */
    rt_memset(pmsg, 0, sizeof(struct rt_can_msg));
    pmsg->hdr_index = -1;
    pmsg->rxfifo    = (rt_uint32_t)fifo;

    /* Select the correct frame buffer: MB1:frame[0], MB2:frame[1] */
    frame_idx = (fifo >= 1 && fifo <= RX_MB_COUNT) ? (rt_uint8_t)(fifo - 1) : 0;

    /* frame[N].dlc is already converted from DLC code to byte length
     * by FLEXCANDRV_DLC2DataLen() inside FLEXCANDRV_GetRxMsg().
     * Convert back to DLC code for the RT-Thread message len field. */
    pmsg->id  = frame[frame_idx].msgId;
#ifdef RT_CAN_USING_CANFD
    pmsg->len = _can_len_to_dlc((rt_uint8_t)frame[frame_idx].dlc);
#else
    pmsg->len = (rt_uint8_t)frame[frame_idx].dlc;
    if (pmsg->len > 8) { pmsg->len = 8; }
#endif

    /* Copy frame metadata */
#ifdef RT_CAN_USING_CANFD
    pmsg->fd_frame = frame[frame_idx].isFd ? 1 : 0;
    /* BRS is not available from FLEXCANDRV_GetRxMsg()  set to 1 for FD frames */
    pmsg->brs      = frame[frame_idx].isFd ? 1 : 0;
#endif

    /* Determine actual byte length to copy */
    data_len = (rt_uint8_t)frame[frame_idx].dlc;
    if (data_len > sizeof(pmsg->data))
    {
        data_len = sizeof(pmsg->data);
    }

    /* Bulk copy payload from frame buffer */
    rt_memcpy(pmsg->data, frame[frame_idx].data, data_len);

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

static uint32_t FLEXCANREG_GetMsgBufInterruptFlagAll(FLEXCANREG_TypeDef *obj)
{
    return obj->IFLAG1 | obj->IFLAG2 | obj->IFLAG3 | obj->IFLAG4;
}

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
    RT_ASSERT(can);
    ns800rt7_can *hcan;
    hcan = (ns800rt7_can *) can->parent.user_data;
    FLEXCANDRV_MsgObjType msgObj;

    /* Assertion. */
    RT_ASSERT(hcan);

    uint32_t result;

    do
    {
        /* For this implementation, we solve the Message with lowest MB index first. */
        for (result = 0; result < 128; result++)
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
        if (result == 128)
        {
            break;
        }

        /* Get current State of Message Buffer. */
        switch (result)
        {
            /* Solve Rx Data Frame. */
            case 1: /* MB1: standard frame RX */
            case 2: /* MB2: extended frame RX */
                msgObj.msgBufId = result;
                FLEXCANDRV_GetRxMsg(&hcan->CanHandle, &msgObj);
                FLEXCANDRV_ClearMsgObjFlag(&hcan->CanHandle, result);
                memcpy(&frame[result - 1], &msgObj, sizeof(msgObj));
                rt_hw_can_isr(can, RT_CAN_EVENT_RX_IND | result << 8);
                hcan->mbState[result] = StateIdle;
                break;

            /* Solve Tx Data Frame. */
            case 0:
                rt_hw_can_isr(can, RT_CAN_EVENT_TX_DONE | result << 8);
                hcan->mbState[result] = StateIdle;
                break;

            default:
                break;
        }

        /* Clear resolved Message Buffer IRQ. */
        FLEXCANDRV_ClearMsgObjFlag(&(hcan->CanHandle), result);
    }
    while((0 != FLEXCANREG_GetMsgBufInterruptFlagAll(hcan->CanHandle.flexCanReg)));
}

static void _can_err_isr(struct rt_can_device *can)
{
    RT_ASSERT(can);
    ns800rt7_can *hcan = (ns800rt7_can *)can->parent.user_data;

    /* Read error status from hardware to clear interrupt flags */
    FLEXCANDRV_ErrStatusType errStatus;
    FLEXCANDRV_GetErrorStatusFlag(&hcan->CanHandle, &errStatus);

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
/**
 * @brief This function handles CAN1 RX0 interrupts.
 */
void CAN1_1_IRQHandler(void)
{
    rt_interrupt_enter();
#if 0
    if()
    {
        _can_rx_isr(&drv_can1.device);
    }
    else
    {
        _can_tx_isr(&drv_can1.device);
    }
#endif
    rt_interrupt_leave();
}

/**
 * @brief This function handles CAN1 RX1 interrupts.
 */
void CAN1_2_IRQHandler(void)
{
    rt_interrupt_enter();
#if 0
    if()
    {
        _can_rx_isr(&drv_can1.device);
    }
    else
    {
        _can_tx_isr(&drv_can1.device);
    }
#endif
    rt_interrupt_leave();
}

#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CANFD1
void CAN_Handler(void)
{
    rt_interrupt_enter();
    _can_tx_rx_isr(&drv_can1.device);
    rt_interrupt_leave();
}

void CAN_Err_Handler(void)
{
    rt_interrupt_enter();
    _can_err_isr(&drv_can1.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CANFD1 */

#ifdef BSP_USING_CANFD2
void CANFD2_1_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_sce_isr(&drv_can1.device);
    rt_interrupt_leave();
}

void CANFD2_2_IRQHandler(void)
{
    rt_interrupt_enter();
    _can_sce_isr(&drv_can1.device);
    rt_interrupt_leave();
}
#endif /* BSP_USING_CANFD2 */

int rt_hw_can_init(void)
{
    int ret = RT_EOK;
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;

    config.ticks = 50;
    config.sndboxnumber = 1;
    config.msgboxsz = RX_MB_COUNT;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = RX_MB_COUNT;          /* filter count,one filter per MB */
#endif

#ifdef RT_CAN_USING_CANFD
    /* Enable CAN-FD by default when compiled with FD support */
    config.enable_canfd = 1;
#endif

    /* config default filter */
    drv_can1.FilterConfig[0].msgBufId  = 0;
    drv_can1.FilterConfig[0].msgBufLen = 1;
    drv_can1.FilterConfig[0].msgId     = 0x78;
    drv_can1.FilterConfig[0].isExtMsgId = false;
    drv_can1.FilterConfig[0].msgType   = FLEXCANDRV_MSGTYPE_TX;
    drv_can1.FilterConfig[0].dlc       = DLC_BYTE_8;
#ifdef RT_CAN_USING_CANFD
    drv_can1.FilterConfig[0].isFd      = true;
#else
    drv_can1.FilterConfig[0].isFd      = false;
#endif
    drv_can1.FilterConfig[0].intEnable  = true;
    drv_can1.FilterConfig[0].individualMask = 0xFFFFFFFF;
    drv_can1.FilterConfig[0].rtrmask   = false;
    drv_can1.FilterConfig[0].rtrfilter = false;

    drv_can1.FilterConfig[1].msgBufId  = 1;
    drv_can1.FilterConfig[1].msgBufLen = 1;
    drv_can1.FilterConfig[1].msgId     = 0x400;
    drv_can1.FilterConfig[1].isExtMsgId = false;
    drv_can1.FilterConfig[1].msgType   = FLEXCANDRV_MSGTYPE_RX;
    drv_can1.FilterConfig[1].dlc       = DLC_BYTE_8;
#ifdef RT_CAN_USING_CANFD
    drv_can1.FilterConfig[1].isFd      = true;
#else
    drv_can1.FilterConfig[1].isFd      = false;
#endif
    drv_can1.FilterConfig[1].intEnable  = true;
    drv_can1.FilterConfig[1].individualMask = 0;
    drv_can1.FilterConfig[1].rtrmask   = false;
    drv_can1.FilterConfig[1].rtrfilter = false;

    /* MB2: RX extended frame accept all 29-bit IDs */
    drv_can1.FilterConfig[2].msgBufId  = 2;
    drv_can1.FilterConfig[2].msgBufLen = 1;
    drv_can1.FilterConfig[2].msgId     = 0x20000000;
    drv_can1.FilterConfig[2].isExtMsgId = true;
    drv_can1.FilterConfig[2].msgType   = FLEXCANDRV_MSGTYPE_RX;
    drv_can1.FilterConfig[2].dlc       = DLC_BYTE_8;
#ifdef RT_CAN_USING_CANFD
    drv_can1.FilterConfig[2].isFd      = true;
#else
    drv_can1.FilterConfig[2].isFd      = false;
#endif
    drv_can1.FilterConfig[2].intEnable  = true;
    drv_can1.FilterConfig[2].individualMask = 0;
    drv_can1.FilterConfig[2].rtrmask   = false;
    drv_can1.FilterConfig[2].rtrfilter = false;

    drv_can1.FilterNum = 3;

#ifdef BSP_USING_CANFD1
    drv_can1.device.config = config;
    /* register CANFD1 device */
    ret = rt_hw_can_register(&drv_can1.device,
                       drv_can1.name,
                       &_can_ops,
                       &drv_can1);
#endif /* BSP_USING_CANFD1 */

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/

