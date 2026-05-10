/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
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
 *                             f4-series only.
 * 2025-09-20     wdfk_prog    Implemented sendmsg_nonblocking op to support framework's async TX.
 * 2026-05-10     Codex        Reworked driver around BSP CAN/CANFD config selection.
 */

#include "drv_can.h"

#ifdef BSP_USING_CAN

#define LOG_TAG    "drv_can"
#include <drv_log.h>

#define CAN_TX_MB_INDEX     0U
#define CAN_RX_MB_INDEX     1U
#define CAN_MSG_OBJ_NUM     2U
#define RX_MB_COUNT         1U

struct ns800rt7_can_hw_config
{
    const char *name;
    FLEXCANREG_TypeDef *instance;
    IRQn_Type irqn1;
    IRQn_Type irqn2;
    GPIO_TypeDef *tx_port;
    GPIO_PinNum tx_pin;
    GPIO_AltFunc tx_mux;
    GPIO_TypeDef *rx_port;
    GPIO_PinNum rx_pin;
    GPIO_AltFunc rx_mux;
    uint8_t can_instance_idx;
    rt_bool_t support_canfd;
};

typedef struct
{
    ns800rt7_can base;
    const struct ns800rt7_can_hw_config *hw;
    FLEXCANDRV_MsgObjType rx_cache[RX_MB_COUNT];
    rt_uint8_t rx_ide[RX_MB_COUNT];
    rt_uint8_t rx_rtr[RX_MB_COUNT];
#ifdef RT_CAN_USING_CANFD
    rt_uint8_t rx_brs[RX_MB_COUNT];
#endif
} ns800rt7_can_device;

static void ns800_can_isr_txrx(ns800rt7_can_device *drv);
static void ns800_can_isr_err(ns800rt7_can_device *drv);

#ifdef BSP_USING_CAN1
void CAN1_1_IRQHandler(void);
void CAN1_2_IRQHandler(void);
static const struct ns800rt7_can_hw_config can1_hw =
{
    .name = "can1",
    .instance = (FLEXCANREG_TypeDef *)CAN1,
    .irqn1 = CAN1_1_IRQn,
    .irqn2 = CAN1_2_IRQn,
    .tx_port = GPIOA,
    .tx_pin = GPIO_PIN_4,
    .tx_mux = ALT6_FUNCTION,
    .rx_port = GPIOA,
    .rx_pin = GPIO_PIN_5,
    .rx_mux = ALT6_FUNCTION,
    .can_instance_idx = 0U,
    .support_canfd = RT_FALSE,
};
static ns800rt7_can_device can1_dev =
{
    .base =
    {
        .name = "can1",
        .irqn1 = CAN1_1_IRQn,
        .irqn2 = CAN1_2_IRQn,
    },
    .hw = &can1_hw,
};
#endif

#ifdef BSP_USING_CANFD1
void CANFD1_1_IRQHandler(void);
void CANFD1_2_IRQHandler(void);
static const struct ns800rt7_can_hw_config canfd1_hw =
{
    .name = "canfd1",
    .instance = (FLEXCANREG_TypeDef *)CANFD1,
    .irqn1 = CANFD1_1_IRQn,
    .irqn2 = CANFD1_2_IRQn,
    .tx_port = GPIOA,
    .tx_pin = GPIO_PIN_4,
    .tx_mux = ALT9_FUNCTION,
    .rx_port = GPIOA,
    .rx_pin = GPIO_PIN_10,
    .rx_mux = ALT9_FUNCTION,
    .can_instance_idx = 1U,
    .support_canfd = RT_TRUE,
};
static ns800rt7_can_device canfd1_dev =
{
    .base =
    {
        .name = "canfd1",
        .irqn1 = CANFD1_1_IRQn,
        .irqn2 = CANFD1_2_IRQn,
    },
    .hw = &canfd1_hw,
};
#endif

#ifdef BSP_USING_CANFD2
void CANFD2_1_IRQHandler(void);
void CANFD2_2_IRQHandler(void);
static const struct ns800rt7_can_hw_config canfd2_hw =
{
    .name = "canfd2",
    .instance = (FLEXCANREG_TypeDef *)CANFD2,
    .irqn1 = CANFD2_1_IRQn,
    .irqn2 = CANFD2_2_IRQn,
    .tx_port = GPIOB,
    .tx_pin = GPIO_PIN_9,
    .tx_mux = ALT5_FUNCTION,
    .rx_port = GPIOB,
    .rx_pin = GPIO_PIN_8,
    .rx_mux = ALT5_FUNCTION,
    .can_instance_idx = 1U,
    .support_canfd = RT_TRUE,
};
static ns800rt7_can_device canfd2_dev =
{
    .base =
    {
        .name = "canfd2",
        .irqn1 = CANFD2_1_IRQn,
        .irqn2 = CANFD2_2_IRQn,
    },
    .hw = &canfd2_hw,
};
#endif

static const struct ns800rt7_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud,   CAN1MBaud},
    {CAN800kBaud, CAN800kBaud},
    {CAN500kBaud, CAN500kBaud},
    {CAN250kBaud, CAN250kBaud},
    {CAN125kBaud, CAN125kBaud},
    {CAN100kBaud, CAN100kBaud},
    {CAN50kBaud,  CAN50kBaud},
    {CAN20kBaud,  CAN20kBaud},
    {CAN10kBaud,  CAN10kBaud},
};

static FLEXCANDRV_DataLenCodeType ns800_can_len_to_dlc(rt_uint8_t len)
{
    if (len <= 8U) return (FLEXCANDRV_DataLenCodeType)len;
    if (len <= 12U) return DLC_BYTE_12;
    if (len <= 16U) return DLC_BYTE_16;
    if (len <= 20U) return DLC_BYTE_20;
    if (len <= 24U) return DLC_BYTE_24;
    if (len <= 32U) return DLC_BYTE_32;
    if (len <= 48U) return DLC_BYTE_48;
    return DLC_BYTE_64;
}

static rt_uint8_t ns800_can_dlc_to_len(rt_uint8_t dlc, rt_bool_t is_canfd)
{
    if (!is_canfd)
    {
        return (dlc <= 8U) ? dlc : 8U;
    }

    switch (dlc)
    {
    case DLC_BYTE_12:
        return 12U;
    case DLC_BYTE_16:
        return 16U;
    case DLC_BYTE_20:
        return 20U;
    case DLC_BYTE_24:
        return 24U;
    case DLC_BYTE_32:
        return 32U;
    case DLC_BYTE_48:
        return 48U;
    case DLC_BYTE_64:
        return 64U;
    default:
        return (dlc <= 8U) ? dlc : 8U;
    }
}

static rt_uint8_t ns800_can_msg_buf_size(rt_bool_t use_canfd)
{
    return use_canfd ? FLEXCANDRV_MB_SIZE_BYTE_64 : FLEXCANDRV_MB_SIZE_BYTE_8;
}

static rt_bool_t ns800_can_is_supported_baud(rt_uint32_t baud)
{
    rt_size_t i;

    for (i = 0; i < sizeof(can_baud_rate_tab) / sizeof(can_baud_rate_tab[0]); i++)
    {
        if (can_baud_rate_tab[i].baud_rate == baud)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static void ns800_can_gpio_init(const struct ns800rt7_can_hw_config *hw)
{
    RT_ASSERT(hw != RT_NULL);

    GPIO_setPinConfig(hw->tx_port, hw->tx_pin, hw->tx_mux);
    GPIO_setAnalogMode(hw->tx_port, hw->tx_pin, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(hw->tx_port, hw->tx_pin, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(hw->tx_port, hw->tx_pin, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(hw->tx_port, hw->tx_pin, GPIO_DIR_MODE_OUT);

    GPIO_setPinConfig(hw->rx_port, hw->rx_pin, hw->rx_mux);
    GPIO_setAnalogMode(hw->rx_port, hw->rx_pin, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(hw->rx_port, hw->rx_pin, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(hw->rx_port, hw->rx_pin, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(hw->rx_port, hw->rx_pin, GPIO_DIR_MODE_IN);
}

static void ns800_can_wait_hxtl_ready(void)
{
    uint32_t wait_time = 5000000U;

    WRITE_REG(RCC->HXTLCR.WORDVAL, (HXTL_CONFIG | RCC_HXTLCR_KEY));
    RCC_enableHxtl();
    RCC_disableHxtlBypass();

    while ((RCC_readHxtlRdyFlag() != 1U) && (--wait_time != 0U))
    {
    }
}

static void ns800_can_clock_init(const struct ns800rt7_can_hw_config *hw)
{
    RT_ASSERT(hw != RT_NULL);

    RCC_unlockRccRegister();

    ns800_can_wait_hxtl_ready();
    RCC_enablePeriphKernalUseMirc2();
    RCC_enablePeriphKernalUseHxtl();

    if (hw->support_canfd)
    {
        RCC_selectCanfdOscClkSource((hw->instance == (FLEXCANREG_TypeDef *)CANFD2) ? RCC_CANFD2SEL : RCC_CANFD1SEL,
                                    RCC_CANFD_OSCCLK_SEL_HXTLKER);

        if (hw->instance == (FLEXCANREG_TypeDef *)CANFD2)
        {
            RCC_selectCanfd2PeripheralClkSource(RCC_CANFD2_PERIPHERAL_CLK_SEL_HCLK);
            RCC_enableCanfd2Clock();
        }
        else
        {
            RCC_selectCanfd1PeripheralClkSource(RCC_CANFD1_PERIPHERAL_CLK_SEL_HCLK);
            RCC_enableCanfd1Clock();
        }
    }
    else
    {
        RCC_selectCan1OscClkSource(RCC_CAN1_OSCCLK_SEL_HXTLKER);
        RCC_selectCan1PeripheralClkSource(RCC_CAN1_PERIPHERAL_CLK_SEL_HCLK);
        RCC_enableCan1Clock();
    }

    RCC_lockRccRegister();
}

static void ns800_can_init_filter_defaults(ns800rt7_can_device *drv)
{
    RT_ASSERT(drv != RT_NULL);

    rt_memset(drv->base.FilterConfig, 0, sizeof(drv->base.FilterConfig));

    drv->base.FilterConfig[CAN_TX_MB_INDEX].msgBufId = CAN_TX_MB_INDEX;
    drv->base.FilterConfig[CAN_TX_MB_INDEX].msgBufLen = 1U;
    drv->base.FilterConfig[CAN_TX_MB_INDEX].msgType = FLEXCANDRV_MSGTYPE_TX;
    drv->base.FilterConfig[CAN_TX_MB_INDEX].dlc = DLC_BYTE_8;
    drv->base.FilterConfig[CAN_TX_MB_INDEX].intEnable = true;
    drv->base.FilterConfig[CAN_TX_MB_INDEX].individualMask = 0xFFFFFFFFU;

    drv->base.FilterConfig[CAN_RX_MB_INDEX].msgBufId = CAN_RX_MB_INDEX;
    drv->base.FilterConfig[CAN_RX_MB_INDEX].msgBufLen = 1U;
    drv->base.FilterConfig[CAN_RX_MB_INDEX].msgType = FLEXCANDRV_MSGTYPE_RX;
    drv->base.FilterConfig[CAN_RX_MB_INDEX].dlc = DLC_BYTE_8;
    drv->base.FilterConfig[CAN_RX_MB_INDEX].intEnable = true;
    drv->base.FilterConfig[CAN_RX_MB_INDEX].individualMask = 0U;
    drv->base.FilterNum = CAN_MSG_OBJ_NUM;
}

static rt_bool_t ns800_can_use_canfd(ns800rt7_can_device *drv, const struct can_configure *cfg)
{
    RT_ASSERT(drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

#ifdef RT_CAN_USING_CANFD
    if (drv->hw->support_canfd && cfg->enable_canfd)
    {
        return RT_TRUE;
    }
#endif

    return RT_FALSE;
}

static void ns800_can_prepare_msg_cfg(ns800rt7_can_device *drv, const struct can_configure *cfg)
{
    rt_bool_t use_canfd;
    FLEXCANDRV_DataLenCodeType default_dlc;

    RT_ASSERT(drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    use_canfd = ns800_can_use_canfd(drv, cfg);
    default_dlc = use_canfd ? DLC_BYTE_64 : DLC_BYTE_8;

    drv->base.FilterConfig[CAN_TX_MB_INDEX].dlc = default_dlc;
    drv->base.FilterConfig[CAN_TX_MB_INDEX].isFd = use_canfd ? true : false;

    drv->base.FilterConfig[CAN_RX_MB_INDEX].dlc = default_dlc;
    drv->base.FilterConfig[CAN_RX_MB_INDEX].isFd = use_canfd ? true : false;
}

static rt_err_t ns800_can_hw_configure(ns800rt7_can_device *drv, struct can_configure *cfg)
{
    FLEXCANDRV_InitHwParType init_hw_par;
    uint32_t can_clk = HXTL_FREQ_VALUE;
    rt_bool_t use_canfd;

    RT_ASSERT(drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    if (!ns800_can_is_supported_baud(cfg->baud_rate))
    {
        return -RT_ERROR;
    }

#ifdef RT_CAN_USING_CANFD
    if (drv->hw->support_canfd && cfg->enable_canfd && !ns800_can_is_supported_baud(cfg->baud_rate_fd))
    {
        return -RT_ERROR;
    }
#endif

    ns800_can_gpio_init(drv->hw);
    ns800_can_clock_init(drv->hw);

    init_hw_par.canInstanceIdx = drv->hw->can_instance_idx;
    init_hw_par.canRamNum = 4U;

    FLEXCANDRV_Init(&drv->base.CanHandle, drv->hw->instance, &init_hw_par);
    FLEXCANDRV_GetDefaultCfg(&drv->base.CanCfg);

    use_canfd = ns800_can_use_canfd(drv, cfg);
    ns800_can_prepare_msg_cfg(drv, cfg);

    FLEXCANDRV_BitTimingCalc(&drv->base.CanCfg.bitTiming,
                             can_clk,
                             cfg->baud_rate,
                             7500U,
                             2500U,
                             0U);

    FLEXCANDRV_BitTimingCalc(&drv->base.CanCfg.fdBitTiming,
                             can_clk,
#ifdef RT_CAN_USING_CANFD
                             use_canfd ? cfg->baud_rate_fd : cfg->baud_rate,
#else
                             cfg->baud_rate,
#endif
                             7500U,
                             2500U,
                             use_canfd ? 1U : 0U);

    drv->base.CanCfg.clkSrc = FLEXCANDRV_CLKSRC_OSC;
    drv->base.CanCfg.msgNum = drv->base.FilterNum;
    drv->base.CanCfg.msgCfg = drv->base.FilterConfig;
    drv->base.CanCfg.individualMaskEnable = true;
    drv->base.CanCfg.rxMBGlobalMask = 0xFFFFFFFFU;
    drv->base.CanCfg.loopbackEnable = false;
    drv->base.CanCfg.listenMode = false;
    drv->base.CanCfg.msgBufDataLenSel = ns800_can_msg_buf_size(use_canfd);
    drv->base.CanCfg.fdEnable = use_canfd ? true : false;
    drv->base.CanCfg.fdISOEnable = use_canfd ? true : false;
    drv->base.CanCfg.errorIntEnable = true;
    drv->base.CanCfg.warningIntEnable = true;
    drv->base.CanCfg.busoffIntEnable = true;

    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        break;
    case RT_CAN_MODE_LISTEN:
        drv->base.CanCfg.listenMode = true;
        break;
    case RT_CAN_MODE_LOOPBACK:
        drv->base.CanCfg.loopbackEnable = true;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        drv->base.CanCfg.loopbackEnable = true;
        drv->base.CanCfg.listenMode = true;
        break;
    default:
        return -RT_ERROR;
    }

    FLEXCANDRV_Configure(&drv->base.CanHandle, &drv->base.CanCfg);
    rt_memset((void *)drv->base.mbState, StateIdle, sizeof(drv->base.mbState));

    return RT_EOK;
}

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    ns800rt7_can_device *drv;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    drv = (ns800rt7_can_device *)can->parent.user_data;
    RT_ASSERT(drv != RT_NULL);

    return ns800_can_hw_configure(drv, cfg);
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    ns800rt7_can_device *drv;
    rt_uint32_t argval;

    RT_ASSERT(can != RT_NULL);

    drv = (ns800rt7_can_device *)can->parent.user_data;
    RT_ASSERT(drv != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        FLEXCANDRV_DisableMsgObjInterrupt(&drv->base.CanHandle, CAN_TX_MB_INDEX);
        FLEXCANDRV_DisableMsgObjInterrupt(&drv->base.CanHandle, CAN_RX_MB_INDEX);
        Interrupt_disable(drv->base.irqn1);
        Interrupt_disable(drv->base.irqn2);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t)arg;
        if ((argval == RT_DEVICE_FLAG_INT_RX) || (argval == RT_DEVICE_FLAG_INT_TX))
        {
            FLEXCANDRV_EnableMsgObjInterrupt(&drv->base.CanHandle, CAN_TX_MB_INDEX);
            FLEXCANDRV_EnableMsgObjInterrupt(&drv->base.CanHandle, CAN_RX_MB_INDEX);

#ifdef BSP_USING_CAN1
            if (drv == &can1_dev)
            {
                Interrupt_register(drv->base.irqn1, CAN1_1_IRQHandler);
            }
#endif
#ifdef BSP_USING_CANFD1
            if (drv == &canfd1_dev)
            {
                Interrupt_register(drv->base.irqn1, CANFD1_1_IRQHandler);
            }
#endif
#ifdef BSP_USING_CANFD2
            if (drv == &canfd2_dev)
            {
                Interrupt_register(drv->base.irqn1, CANFD2_1_IRQHandler);
            }
#endif
            Interrupt_enable(drv->base.irqn1);
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
#ifdef BSP_USING_CAN1
            if (drv == &can1_dev)
            {
                Interrupt_register(drv->base.irqn2, CAN1_2_IRQHandler);
            }
#endif
#ifdef BSP_USING_CANFD1
            if (drv == &canfd1_dev)
            {
                Interrupt_register(drv->base.irqn2, CANFD1_2_IRQHandler);
            }
#endif
#ifdef BSP_USING_CANFD2
            if (drv == &canfd2_dev)
            {
                Interrupt_register(drv->base.irqn2, CANFD2_2_IRQHandler);
            }
#endif
            Interrupt_enable(drv->base.irqn2);
        }
        break;

    case RT_CAN_CMD_SET_FILTER:
        if (arg != RT_NULL)
        {
            struct rt_can_filter_config *filter_cfg = (struct rt_can_filter_config *)arg;

            if (filter_cfg->count > 0U)
            {
                const struct rt_can_filter_item *item = &filter_cfg->items[0];

                drv->base.FilterConfig[CAN_RX_MB_INDEX].msgId = item->id;
                drv->base.FilterConfig[CAN_RX_MB_INDEX].isExtMsgId = (item->ide == RT_CAN_EXTID) ? true : false;
                drv->base.FilterConfig[CAN_RX_MB_INDEX].individualMask = item->mask;
                drv->base.FilterConfig[CAN_RX_MB_INDEX].rtrfilter = (item->rtr == RT_CAN_RTR) ? true : false;

                return ns800_can_hw_configure(drv, &drv->base.device.config);
            }
        }
        break;

    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t)arg;
        if ((argval != RT_CAN_MODE_NORMAL) &&
            (argval != RT_CAN_MODE_LISTEN) &&
            (argval != RT_CAN_MODE_LOOPBACK) &&
            (argval != RT_CAN_MODE_LOOPBACKANLISTEN))
        {
            return -RT_ERROR;
        }

        if (argval != drv->base.device.config.mode)
        {
            drv->base.device.config.mode = argval;
            return ns800_can_hw_configure(drv, &drv->base.device.config);
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t)arg;
        if (!ns800_can_is_supported_baud(argval))
        {
            return -RT_ERROR;
        }

        if (argval != drv->base.device.config.baud_rate)
        {
            drv->base.device.config.baud_rate = argval;
            return ns800_can_hw_configure(drv, &drv->base.device.config);
        }
        break;

    case RT_CAN_CMD_SET_PRIV:
        drv->base.device.config.privmode = (rt_uint32_t)arg;
        break;

    case RT_CAN_CMD_GET_STATUS:
        drv->base.device.status.rcverrcnt = FLEXCANREG_GetEcrRxerrcnt(drv->base.CanHandle.flexCanReg);
        drv->base.device.status.snderrcnt = FLEXCANREG_GetEcrTxerrcnt(drv->base.CanHandle.flexCanReg);
        rt_memcpy(arg, &drv->base.device.status, sizeof(drv->base.device.status));
        break;

    case RT_CAN_CMD_START:
        return ns800_can_hw_configure(drv, &drv->base.device.config);

#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
        if (!drv->hw->support_canfd)
        {
            return -RT_ERROR;
        }

        drv->base.device.config.enable_canfd = ((rt_uint32_t)arg) ? 1U : 0U;
        return ns800_can_hw_configure(drv, &drv->base.device.config);

    case RT_CAN_CMD_SET_BAUD_FD:
        if (!drv->hw->support_canfd)
        {
            return -RT_ERROR;
        }

        argval = (rt_uint32_t)arg;
        if (!ns800_can_is_supported_baud(argval))
        {
            return -RT_ERROR;
        }

        drv->base.device.config.baud_rate_fd = argval;
        return ns800_can_hw_configure(drv, &drv->base.device.config);
#endif

    default:
        break;
    }

    return RT_EOK;
}

static rt_err_t ns800_can_send_common(ns800rt7_can_device *drv, const struct rt_can_msg *pmsg, rt_uint32_t box_num)
{
    FLEXCANDRV_MsgObjType msg_obj;
    uint32_t *msg_buf_ptr;
    rt_uint8_t len;
    rt_bool_t use_canfd;
    rt_bool_t msg_is_fd = RT_FALSE;

    RT_ASSERT(drv != RT_NULL);
    RT_ASSERT(pmsg != RT_NULL);

    if (box_num != CAN_TX_MB_INDEX)
    {
        return -RT_ERROR;
    }

    if (drv->base.mbState[box_num] != StateIdle)
    {
        return -RT_EBUSY;
    }

    use_canfd = ns800_can_use_canfd(drv, &drv->base.device.config);
    len = pmsg->len;

#ifdef RT_CAN_USING_CANFD
    msg_is_fd = (use_canfd && pmsg->fd_frame) ? RT_TRUE : RT_FALSE;
    if (len > 64U)
    {
        return -RT_ERROR;
    }
    if (!msg_is_fd && (len > 8U))
    {
        return -RT_ERROR;
    }
#else
    if (len > 8U)
    {
        return -RT_ERROR;
    }
#endif

    rt_memset(&msg_obj, 0, sizeof(msg_obj));
    msg_obj.msgBufId = (uint8_t)box_num;
    msg_obj.msgId = pmsg->id;
    msg_obj.dlc = (uint8_t)ns800_can_len_to_dlc(len);
    msg_obj.isFd = msg_is_fd ? true : false;

    rt_memcpy(msg_obj.data, pmsg->data, len);

    drv->base.mbState[box_num] = StateTxData;

    msg_buf_ptr = (uint32_t *)FLEXCANDRV_GetMsgBufStartAddr(&drv->base.CanHandle, (uint16_t)box_num);

    FLEXCANDRV_SetMsgType(msg_buf_ptr, FLEXCANDRV_MSGTYPE_TX);
    FLEXCANDRV_SetMsgId(msg_buf_ptr, pmsg->id, (pmsg->ide == RT_CAN_EXTID) ? true : false);
    FLEXCANDRV_SetMsgDLC(msg_buf_ptr, (FLEXCANDRV_DataLenCodeType)msg_obj.dlc);
    FLEXCANDRV_SetFDEnable(msg_buf_ptr, msg_obj.isFd ? true : false);

    if (pmsg->rtr == RT_CAN_RTR)
    {
        msg_buf_ptr[MESSAGE_BUFFER_CS_WORD_NUM] |= MESSAGE_BUFFER_CS_RTR_MASK;
    }
    else
    {
        msg_buf_ptr[MESSAGE_BUFFER_CS_WORD_NUM] &= ~MESSAGE_BUFFER_CS_RTR_MASK;
    }

#ifdef RT_CAN_USING_CANFD
    if (msg_obj.isFd && !pmsg->brs)
    {
        msg_buf_ptr[MESSAGE_BUFFER_CS_WORD_NUM] &= ~MESSAGE_BUFFER_CS_BRS_MASK;
    }
#endif

    FLEXCANDRV_SetTxMsg(&drv->base.CanHandle, &msg_obj);
    FLEXCANDRV_TransmitMsg(&drv->base.CanHandle, &msg_obj);

    return RT_EOK;
}

static rt_ssize_t _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    ns800rt7_can_device *drv;
    const struct rt_can_msg *pmsg;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    drv = (ns800rt7_can_device *)can->parent.user_data;
    pmsg = (const struct rt_can_msg *)buf;

    return ns800_can_send_common(drv, pmsg, box_num);
}

static rt_ssize_t _can_sendmsg_nonblocking(struct rt_can_device *can, const void *buf)
{
    ns800rt7_can_device *drv;
    const struct rt_can_msg *pmsg;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    drv = (ns800rt7_can_device *)can->parent.user_data;
    pmsg = (const struct rt_can_msg *)buf;

    return ns800_can_send_common(drv, pmsg, CAN_TX_MB_INDEX);
}

static rt_ssize_t _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    ns800rt7_can_device *drv;
    struct rt_can_msg *pmsg;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    drv = (ns800rt7_can_device *)can->parent.user_data;
    RT_ASSERT(drv != RT_NULL);

    if (fifo != CAN_RX_MB_INDEX)
    {
        return -1;
    }

    pmsg = (struct rt_can_msg *)buf;
    pmsg->id = drv->rx_cache[0].msgId;
    pmsg->ide = drv->rx_ide[0];
    pmsg->rtr = drv->rx_rtr[0];
    pmsg->hdr_index = 0;
    pmsg->rxfifo = 0;
#ifdef RT_CAN_USING_CANFD
    pmsg->fd_frame = drv->rx_cache[0].isFd ? 1U : 0U;
    pmsg->brs = drv->rx_brs[0];
    pmsg->len = ns800_can_dlc_to_len(drv->rx_cache[0].dlc, drv->rx_cache[0].isFd ? RT_TRUE : RT_FALSE);
#else
    pmsg->len = ns800_can_dlc_to_len(drv->rx_cache[0].dlc, RT_FALSE);
#endif
    rt_memcpy(pmsg->data, drv->rx_cache[0].data, pmsg->len);

    return sizeof(struct rt_can_msg);
}

static const struct rt_can_ops _can_ops =
{
    .configure = _can_config,
    .control = _can_control,
    .sendmsg = _can_sendmsg,
    .recvmsg = _can_recvmsg,
    .sendmsg_nonblocking = _can_sendmsg_nonblocking,
};

static uint32_t ns800_can_get_irq_flags(FLEXCANREG_TypeDef *obj)
{
    return obj->IFLAG1 | obj->IFLAG2 | obj->IFLAG3 | obj->IFLAG4;
}

static uint8_t ns800_can_get_irq_mask(FLEXCANREG_TypeDef *obj, uint32_t msg_buffer_idx)
{
    uint32_t temp;
    uint32_t bit = 0x00000001UL << (msg_buffer_idx % 32U);

    if (msg_buffer_idx > 95U)
    {
        temp = obj->IMASK4 & bit;
    }
    else if (msg_buffer_idx > 63U)
    {
        temp = obj->IMASK3 & bit;
    }
    else if (msg_buffer_idx > 31U)
    {
        temp = obj->IMASK2 & bit;
    }
    else
    {
        temp = obj->IMASK1 & bit;
    }

    return temp ? 1U : 0U;
}

static void ns800_can_isr_txrx(ns800rt7_can_device *drv)
{
    RT_ASSERT(drv != RT_NULL);

    while (ns800_can_get_irq_flags(drv->base.CanHandle.flexCanReg) != 0U)
    {
        uint32_t result;

        for (result = 0U; result < 128U; result++)
        {
            if ((FLEXCANDRV_GetMsgObjFlag(&drv->base.CanHandle, (uint8_t)result) != 0U) &&
                (ns800_can_get_irq_mask(drv->base.CanHandle.flexCanReg, result) != 0U))
            {
                break;
            }
        }

        if (result >= 128U)
        {
            break;
        }

        if (result == CAN_RX_MB_INDEX)
        {
            uint32_t *msg_buf_ptr;
            uint32_t cs_word;

            msg_buf_ptr = (uint32_t *)FLEXCANDRV_GetMsgBufStartAddr(&drv->base.CanHandle, (uint16_t)result);
            cs_word = msg_buf_ptr[MESSAGE_BUFFER_CS_WORD_NUM];

            drv->rx_cache[0].msgBufId = (uint8_t)result;
            FLEXCANDRV_GetRxMsg(&drv->base.CanHandle, &drv->rx_cache[0]);
            drv->rx_ide[0] = (cs_word & MESSAGE_BUFFER_CS_IDE_MASK) ? RT_CAN_EXTID : RT_CAN_STDID;
            drv->rx_rtr[0] = (cs_word & MESSAGE_BUFFER_CS_RTR_MASK) ? RT_CAN_RTR : RT_CAN_DTR;
#ifdef RT_CAN_USING_CANFD
            drv->rx_brs[0] = (cs_word & MESSAGE_BUFFER_CS_BRS_MASK) ? 1U : 0U;
#endif

            drv->base.mbState[result] = StateIdle;
            FLEXCANDRV_ClearMsgObjFlag(&drv->base.CanHandle, (uint8_t)result);
            rt_hw_can_isr(&drv->base.device, RT_CAN_EVENT_RX_IND | (result << 8));
        }
        else if (result == CAN_TX_MB_INDEX)
        {
            drv->base.mbState[result] = StateIdle;
            FLEXCANDRV_ClearMsgObjFlag(&drv->base.CanHandle, (uint8_t)result);
            rt_hw_can_isr(&drv->base.device, RT_CAN_EVENT_TX_DONE | (result << 8));
        }
        else
        {
            FLEXCANDRV_ClearMsgObjFlag(&drv->base.CanHandle, (uint8_t)result);
        }
    }
}

static void ns800_can_isr_err(ns800rt7_can_device *drv)
{
    RT_ASSERT(drv != RT_NULL);

    drv->base.device.status.rcverrcnt = FLEXCANREG_GetEcrRxerrcnt(drv->base.CanHandle.flexCanReg);
    drv->base.device.status.snderrcnt = FLEXCANREG_GetEcrTxerrcnt(drv->base.CanHandle.flexCanReg);
}

#ifdef BSP_USING_CAN1
void CAN1_1_IRQHandler(void)
{
    rt_interrupt_enter();
    ns800_can_isr_txrx(&can1_dev);
    rt_interrupt_leave();
}

void CAN1_2_IRQHandler(void)
{
    rt_interrupt_enter();
    ns800_can_isr_err(&can1_dev);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CANFD1
void CANFD1_1_IRQHandler(void)
{
    rt_interrupt_enter();
    ns800_can_isr_txrx(&canfd1_dev);
    rt_interrupt_leave();
}

void CANFD1_2_IRQHandler(void)
{
    rt_interrupt_enter();
    ns800_can_isr_err(&canfd1_dev);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CANFD2
void CANFD2_1_IRQHandler(void)
{
    rt_interrupt_enter();
    ns800_can_isr_txrx(&canfd2_dev);
    rt_interrupt_leave();
}

void CANFD2_2_IRQHandler(void)
{
    rt_interrupt_enter();
    ns800_can_isr_err(&canfd2_dev);
    rt_interrupt_leave();
}
#endif

static rt_err_t ns800_can_register(ns800rt7_can_device *drv)
{
    struct can_configure config = CANDEFAULTCONFIG;

    RT_ASSERT(drv != RT_NULL);

    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50U;
    config.sndboxnumber = 1U;
    config.msgboxsz = RX_MB_COUNT;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 1U;
#endif
#ifdef RT_CAN_USING_CANFD
    config.baud_rate_fd = CAN1MBaud;
    config.enable_canfd = drv->hw->support_canfd ? 1U : 0U;
#endif

    drv->base.device.config = config;
    drv->base.CanHandle.flexCanReg = drv->hw->instance;
    drv->base.irqn1 = drv->hw->irqn1;
    drv->base.irqn2 = drv->hw->irqn2;
    ns800_can_init_filter_defaults(drv);

    return rt_hw_can_register(&drv->base.device, drv->hw->name, &_can_ops, drv);
}

int rt_hw_can_init(void)
{
    int ret = RT_EOK;

#ifdef BSP_USING_CAN1
    ret = ns800_can_register(&can1_dev);
    if (ret != RT_EOK)
    {
        return ret;
    }
#endif

#ifdef BSP_USING_CANFD1
    ret = ns800_can_register(&canfd1_dev);
    if (ret != RT_EOK)
    {
        return ret;
    }
#endif

#ifdef BSP_USING_CANFD2
    ret = ns800_can_register(&canfd2_dev);
    if (ret != RT_EOK)
    {
        return ret;
    }
#endif

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */
