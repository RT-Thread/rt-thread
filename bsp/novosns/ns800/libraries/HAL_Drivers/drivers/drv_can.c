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
 */

#include "drv_can.h"

#ifdef BSP_USING_CAN

#define LOG_TAG    "drv_can"
#include <drv_log.h>


#define RX_MB_COUNT     (1)
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

static rt_err_t _can_sendBlocking(ns800rt7_can *base, FLEXCANDRV_MsgObjType *TxMsgObj)
{
    /* Check if Message Buffer is idle. */
    if (StateIdle == base->mbState[TxMsgObj->msgBufId])
    {
        base->mbState[TxMsgObj->msgBufId] = StateTxData;

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

static rt_err_t _can_receiveNonBlocking(ns800rt7_can *base, FLEXCANDRV_MsgObjType *RxMsgObj)
{
    /* Check if Message Buffer is idle. */
    if (StateIdle == base->mbState[RxMsgObj->msgBufId])
    {
        base->mbState[RxMsgObj->msgBufId] = StateRxData;

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

    baud_index = get_can_baud_index(cfg->baud_rate);

    FLEXCANDRV_BitTimingCalc(&(drv_can->CanCfg.bitTiming),
                             FlexcanClockFreq,        /* module clock source*/
                             BAUD_DATA(baud_index),   /* baudrate: 500K */
                             7500,                    /* sample point: 75% */
                             2500,                    /* SJW: 25% */
                             0);                      /* classic CAN bit timing */

    FLEXCANDRV_BitTimingCalc(&(drv_can->CanCfg.fdBitTiming),
                             FlexcanClockFreq,        /* module clock source*/
                             BAUD_DATA(baud_index),   /* baudrate: 500K */
                             7500,                    /* sample point: 75% */
                             2500,                    /* SJW: 25% */
                             1);                      /* CANFD bit timing */

    drv_can->CanCfg.clkSrc                  = FLEXCANDRV_CLKSRC_OSC;
    drv_can->CanCfg.msgNum                  = drv_can->FilterNum;
    drv_can->CanCfg.msgCfg                  = drv_can->FilterConfig;
    drv_can->CanCfg.individualMaskEnable    = true;
    drv_can->CanCfg.rxMBGlobalMask          = 0xFFFFFFFF;
    drv_can->CanCfg.loopbackEnable          = false;
    drv_can->CanCfg.msgBufDataLenSel        = FLEXCANDRV_MB_SIZE_BYTE_8;
    drv_can->CanCfg.fdEnable                = true;
    drv_can->CanCfg.fdISOEnable             = true;

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
        break;
    }

    /* init can */
    /* initialize FLEXCAN module */
    FLEXCANDRV_Configure(&(drv_can->CanHandle), &(drv_can->CanCfg));

    return RT_EOK;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t argval;
    ns800rt7_can *drv_can;
    struct rt_can_filter_config *filter_cfg;
    struct rt_can_filter_item *item;
    rt_uint8_t i, count, index;

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

#define IS_CAN_DLC(DLC)                         ((DLC) <= ((uint8_t)0x08))

/**
 * @internal
 * @brief Low-level function to send a CAN message to a specific hardware mailbox.
 *
 * This function is part of the **blocking** send mechanism. It is called by
 * `_can_int_tx` after a hardware mailbox has already been acquired. Its role is
 * to format the message according to the STM32 hardware requirements and place
 * it into the specified mailbox for transmission.
 *
 * @param[in] can     A pointer to the CAN device structure.
 * @param[in] buf     A pointer to the `rt_can_msg` to be sent.
 * @param[in] box_num The specific hardware mailbox index (0, 1, or 2) to use for this tran
 *
 * @return `RT_EOK` on success, or an error code on failure.
 */
static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    rt_ssize_t status;
    ns800rt7_can *hcan;
    hcan = (ns800rt7_can *) can->parent.user_data;
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    FLEXCANDRV_MsgObjType fdTxMsgObj;

    /* Check the parameters */
    RT_ASSERT(IS_CAN_DLC(pmsg->len));

    fdTxMsgObj.msgBufId = box_num;

    /* Set up the DLC */
    fdTxMsgObj.dlc = pmsg->len & 0x0FU;
    /* Set up the data field */
    for(uint8_t i=0u; i<8u; i++)
    {
        fdTxMsgObj.data[i] = pmsg->data[i];
    }

    status = _can_sendBlocking(hcan, &fdTxMsgObj);

    return status;
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    FLEXCANDRV_Type *hcan;
    struct rt_can_msg *pmsg;

    RT_ASSERT(can);

    hcan = &(((ns800rt7_can *)can->parent.user_data)->CanHandle);
    pmsg = (struct rt_can_msg *) buf;

    rt_uint8_t index;

    pmsg->hdr_index = index;      /* one hdr filter per MB */
    pmsg->len = frame[0].dlc;
    pmsg->id = frame[0].msgId;
    pmsg->data[0] = frame[0].data[0];
    pmsg->data[1] = frame[0].data[1];
    pmsg->data[2] = frame[0].data[2];
    pmsg->data[3] = frame[0].data[3];
    pmsg->data[4] = frame[0].data[4];
    pmsg->data[5] = frame[0].data[5];
    pmsg->data[6] = frame[0].data[6];
    pmsg->data[7] = frame[0].data[7];

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
{
    .configure  = _can_config,
    .control    = _can_control,
    .sendmsg    = _can_sendmsg,
    .recvmsg    = _can_recvmsg,
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
            case 1:
                msgObj.msgBufId = result;
                FLEXCANDRV_GetRxMsg(&hcan->CanHandle, &msgObj);
                FLEXCANDRV_ClearMsgObjFlag(&hcan->CanHandle, result);
                memcpy(&frame[0], &msgObj, sizeof(msgObj));
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
    /* config default filter */
    FLEXCANDRV_MsgCfgType fdMsgCfgObj[2] = {0};

    drv_can1.FilterConfig[0].msgBufId = 0;
    drv_can1.FilterConfig[0].msgBufLen = 1;
    drv_can1.FilterConfig[0].msgId = 0x78;
    drv_can1.FilterConfig[0].isExtMsgId = false;
    drv_can1.FilterConfig[0].msgType = FLEXCANDRV_MSGTYPE_TX;
    drv_can1.FilterConfig[0].dlc = DLC_BYTE_8;
    drv_can1.FilterConfig[0].isFd = false;
    drv_can1.FilterConfig[0].intEnable = true;
    drv_can1.FilterConfig[0].individualMask = 0xFFFFFFFF;
    drv_can1.FilterConfig[0].rtrmask = false;
    drv_can1.FilterConfig[0].rtrfilter = false;

    drv_can1.FilterConfig[1].msgBufId = 1;
    drv_can1.FilterConfig[1].msgBufLen = 1;
    drv_can1.FilterConfig[1].msgId = 0x400;
    drv_can1.FilterConfig[1].isExtMsgId = false;
    drv_can1.FilterConfig[1].msgType = FLEXCANDRV_MSGTYPE_RX;
    drv_can1.FilterConfig[1].dlc = DLC_BYTE_8;
    drv_can1.FilterConfig[1].isFd = false;
    drv_can1.FilterConfig[1].intEnable = true;
    drv_can1.FilterConfig[1].individualMask = 0;
    drv_can1.FilterConfig[1].rtrmask = false;
    drv_can1.FilterConfig[1].rtrfilter = false;

    drv_can1.FilterNum = 2;

#ifdef BSP_USING_CANFD1
    drv_can1.device.config = config;
    /* register CAN1 device */
    ret = rt_hw_can_register(&drv_can1.device,
                       drv_can1.name,
                       &_can_ops,
                       &drv_can1);
#endif /* BSP_USING_CAN1 */

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/

