/*
 * Copyright (C) 2022, xiaoxiaolisunny
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2022-05-13     xiaoxiaolisunny    first version
 */

#include "drv_can.h"
#include <drv_config.h>
#include <board_config.h>
#include "drv_irq.h"

#define DBG_TAG             "drv.can"
#define DBG_LVL             DBG_INFO

#include <rtdbg.h>

#ifdef BSP_USING_CAN
#define LOG_TAG    "drv_can"

#if !defined(BSP_USING_CAN1)
    #error "Please define at least one BSP_USING_CANx"
#endif

#if defined (HC32F460)
    #define FILTER_COUNT    (8)
#endif

enum
{
#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
    CAN_INDEX_MAX,
};

struct hc32_baud_rate_tab
{
    rt_uint32_t baud_rate;
    stc_can_bt_t ll_sbt;
};

#if defined (HC32F460)
static const struct hc32_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud,   {3, 2, 2, 0}},
    {CAN800kBaud, {4, 3, 3, 0}},
    {CAN500kBaud, {3, 2, 2, 1}},
    {CAN250kBaud, {3, 2, 2, 3}},
    {CAN125kBaud, {3, 2, 2, 7}},
    {CAN100kBaud, {3, 2, 2, 9}},
    {CAN50kBaud,  {3, 2, 2, 19}},
    {CAN20kBaud,  {3, 2, 2, 49}},
    {CAN10kBaud,  {3, 2, 2, 99}},
};
#endif

typedef struct
{
    struct rt_can_device rt_can;
    struct hc32_can_init_type init;
    M4_CAN_TypeDef *instance;
    stc_can_init_config_t ll_init;
    stc_can_filter_t *p_ll_can_filter_cfg;
} hc32_drv_can;

static hc32_drv_can drv_can[] =
{
#ifdef BSP_USING_CAN1
    {
        {0},
        CAN1_CONFIG,
        .instance = M4_CAN,
    },
#endif
};

typedef struct
{
    rt_bool_t int_rx_flag;
    rt_bool_t int_tx_flag;
    rt_bool_t int_err_flag;
}irq_flag;
irq_flag can_irq_flag;

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

static en_can_mode_t get_can_work_mode(rt_uint32_t mode)
{
    en_can_mode_t work_mode;
    switch (mode)
    {
    case RT_CAN_MODE_NORMAL:
        work_mode = CanTxSignalPrimaryMode;
        break;
    case RT_CAN_MODE_LISEN:
        work_mode = CanListenOnlyMode;
        break;
    case RT_CAN_MODE_LOOPBACK:
        work_mode = CanInternalLoopBackMode;
        break;
    case RT_CAN_MODE_LOOPBACKANLISEN:
        work_mode = CanTxSignalPrimaryMode;
        LOG_E("No LOOPBackMode.");
        break;
    default:
        work_mode = CanTxSignalPrimaryMode;
        break;
    }

    return work_mode;
}

#if defined(BSP_USING_CAN1)
static void can1_irq_handler(void);
#endif
static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    rt_uint32_t baud_index;
    hc32_drv_can *hc32_can;
    rt_err_t rt_ret = RT_EOK;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    hc32_can = (hc32_drv_can *)rt_container_of(can, hc32_drv_can, rt_can);
    RT_ASSERT(hc32_can);

    baud_index = get_can_baud_index(cfg->baud_rate);
    hc32_can->ll_init.stcCanBt = can_baud_rate_tab[baud_index].ll_sbt;
    hc32_can->ll_init.stcWarningLimit.CanErrorWarningLimitVal = 10u;
    hc32_can->ll_init.stcWarningLimit.CanWarningLimitVal = 16u - 1u;

    hc32_can->ll_init.enCanRxBufAll = CanRxNormal;
    hc32_can->ll_init.enCanRxBufMode = CanRxBufNotStored;
    hc32_can->ll_init.enCanSAck = CanSelfAckEnable;
    hc32_can->ll_init.enCanSTBMode = CanSTBFifoMode;

    /* init can */
    CAN_Init(&hc32_can->ll_init);
    CAN_FilterConfig(hc32_can->p_ll_can_filter_cfg, Enable);
    CAN_ModeConfig(get_can_work_mode(cfg->mode), Enable);

    /*If interrupt enabled, must use CAN_IrqCmd to enable the interrupt
    again, after user CAN_Init.*/
    if(can_irq_flag.int_rx_flag == Enable)
    {
        CAN_IrqCmd(CanRxIrqEn, Enable);
        CAN_IrqCmd(CanRxBufAlmostFullIrqEn, Enable);
        CAN_IrqCmd(CanRxBufFullIrqEn, Enable);
        CAN_IrqCmd(CanRxOverIrqEn, Enable);
    }
    if(can_irq_flag.int_tx_flag == Enable)
    {
        CAN_IrqCmd(CanTxPrimaryIrqEn, Enable);
        CAN_IrqCmd(CanTxSecondaryIrqEn, Enable);
    }
    if(can_irq_flag.int_err_flag == Enable)
    {
        CAN_IrqCmd(CanErrorIrqEn, Enable);
        CAN_IrqCmd(CanArbiLostIrqEn, Enable);
        CAN_IrqCmd(CanErrorPassiveIrqEn, Enable);
        CAN_IrqCmd(CanBusErrorIrqEn, Enable);
    }

    return rt_ret;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    hc32_drv_can *hc32_can;
    rt_uint32_t argval;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    hc32_can = (hc32_drv_can *)rt_container_of(can, hc32_drv_can, rt_can);
    RT_ASSERT(hc32_can);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        switch (argval)
        {
        case RT_DEVICE_FLAG_INT_RX:
            CAN_IrqCmd(CanRxIrqEn, Disable);
            CAN_IrqCmd(CanRxBufAlmostFullIrqEn, Disable);
            CAN_IrqCmd(CanRxBufFullIrqEn, Disable);
            CAN_IrqCmd(CanRxOverIrqEn, Disable);
            can_irq_flag.int_rx_flag = Disable;
            break;
        case RT_DEVICE_FLAG_INT_TX:
            CAN_IrqCmd(CanTxPrimaryIrqEn, Disable);
            CAN_IrqCmd(CanTxSecondaryIrqEn, Disable);
            can_irq_flag.int_tx_flag = Disable;
            break;
        case RT_DEVICE_CAN_INT_ERR:
            CAN_IrqCmd(CanErrorIrqEn, Disable);
            CAN_IrqCmd(CanArbiLostIrqEn, Disable);
            CAN_IrqCmd(CanErrorPassiveIrqEn, Disable);
            CAN_IrqCmd(CanBusErrorIrqEn, Disable);
            can_irq_flag.int_err_flag = Disable;
            break;
        default:
            break;
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;
        switch (argval)
        {
        case RT_DEVICE_FLAG_INT_RX:
            CAN_IrqCmd(CanRxIrqEn, Enable);
            CAN_IrqCmd(CanRxBufAlmostFullIrqEn, Enable);
            CAN_IrqCmd(CanRxBufFullIrqEn, Enable);
            CAN_IrqCmd(CanRxOverIrqEn, Enable);
            can_irq_flag.int_rx_flag = Enable;
            break;
        case RT_DEVICE_FLAG_INT_TX:
            CAN_IrqCmd(CanTxPrimaryIrqEn, Enable);
            CAN_IrqCmd(CanTxSecondaryIrqEn, Enable);
            can_irq_flag.int_tx_flag = Enable;
            break;
        case RT_DEVICE_CAN_INT_ERR:
            CAN_IrqCmd(CanErrorIrqEn, Enable);
            CAN_IrqCmd(CanArbiLostIrqEn, Enable);
            CAN_IrqCmd(CanErrorPassiveIrqEn, Enable);
            CAN_IrqCmd(CanBusErrorIrqEn, Enable);
            can_irq_flag.int_err_flag = Enable;
            break;
        default:
            break;
        }
        break;
    case RT_CAN_CMD_SET_FILTER:
        if (RT_NULL != arg)
        {
            filter_cfg = (struct rt_can_filter_config *)arg;

            if (filter_cfg->count == 0)
            {
                return -RT_EINVAL;
            }
            RT_ASSERT(filter_cfg->count <= FILTER_COUNT);

            /* get default filter */
            if (hc32_can->p_ll_can_filter_cfg)
            {
                for (int i = 0; i < filter_cfg->count; i++)
                {
                    hc32_can->p_ll_can_filter_cfg[i].u32CODE = filter_cfg->items[i].id;
                    hc32_can->p_ll_can_filter_cfg[i].u32MASK = filter_cfg->items[i].mask;
                    hc32_can->p_ll_can_filter_cfg[i].enAcfFormat = filter_cfg->items[i].ide + 2;
                }
            }
            CAN_FilterConfig(hc32_can->p_ll_can_filter_cfg, Enable);
            break;
        }
    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_NORMAL &&
                argval != RT_CAN_MODE_LISEN &&
                argval != RT_CAN_MODE_LOOPBACK &&
                argval != RT_CAN_MODE_LOOPBACKANLISEN)
        {
            return -RT_ERROR;
        }
        if (argval != hc32_can->rt_can.config.mode)
        {
            hc32_can->rt_can.config.mode = argval;
            _can_config(can, &hc32_can->rt_can.config);
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
        if (argval != hc32_can->rt_can.config.baud_rate)
        {
            hc32_can->rt_can.config.baud_rate = argval;
            _can_config(can, &hc32_can->rt_can.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
                argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != hc32_can->rt_can.config.privmode)
        {
            hc32_can->rt_can.config.privmode = argval;
            return _can_config(can, &hc32_can->rt_can.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        struct rt_can_status *rt_can_stat = (struct rt_can_status *)arg;
        rt_can_stat->errcode = CAN_ErrorStatusGet();

    }
    break;
    default:
        break;
    }
    return RT_EOK;
}

static int _can_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_num)
{
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    stc_can_txframe_t stc_tx_frame = {0};
    int32_t ll_ret;

    RT_ASSERT(can != RT_NULL);
    hc32_drv_can *hc32_can = (hc32_drv_can *)rt_container_of(can, hc32_drv_can, rt_can);
    RT_ASSERT(hc32_can);

    /*check select mailbox  is empty */
    stc_tx_frame.StdID = pmsg->id;
    if (RT_CAN_DTR == pmsg->rtr)
    {
        stc_tx_frame.Control_f.RTR = 0;
    }
    else
    {
        stc_tx_frame.Control_f.RTR = 1;
    }
    /* Set up the DLC */
    stc_tx_frame.Control_f.DLC = pmsg->len & 0x0FU;
    /* Set up the IDE */
    stc_tx_frame.Control_f.IDE = pmsg->ide;
    /* Set up the data field */
    rt_memcpy(&stc_tx_frame.Data, pmsg->data, sizeof(stc_tx_frame.Data));

    CAN_SetFrame(&stc_tx_frame);
    ll_ret = CAN_TransmitCmd(CanPTBTxCmd);

    if (ll_ret != CanTxBufEmpty)
    {
        return RT_ERROR;
    }
    return RT_EOK;
}

static int _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    int32_t ll_ret;
    struct rt_can_msg *pmsg;
    stc_can_rxframe_t ll_rx_frame;

    RT_ASSERT(can != RT_NULL);
    hc32_drv_can *hc32_can = (hc32_drv_can *)rt_container_of(can, hc32_drv_can, rt_can);
    RT_ASSERT(hc32_can);

    pmsg = (struct rt_can_msg *) buf;

    /* get data */
    ll_ret = CAN_Receive(&ll_rx_frame);
    if (ll_ret != CanRxBufEmpty)
        return -RT_ERROR;
    /* get id */
    if (0 == ll_rx_frame.Cst.Control_f.IDE)
    {
        pmsg->ide = RT_CAN_STDID;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
    }
    pmsg->id = ll_rx_frame.StdID;
    /* get type */
    if (0 == ll_rx_frame.Cst.Control_f.RTR)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    /* get len */
    pmsg->len = ll_rx_frame.Cst.Control_f.DLC;
    /* get hdr */
    pmsg->hdr = 0;
    rt_memcpy(pmsg->data, &ll_rx_frame.Data, ll_rx_frame.Cst.Control_f.DLC);

    return RT_EOK;
}

static const struct rt_can_ops _can_ops =
{
    _can_config,
    _can_control,
    _can_sendmsg,
    _can_recvmsg,
};

static void can_isr(hc32_drv_can *hc32_can)
{
    CAN_ErrorStatusGet();

    if (CAN_StatusGet(CanBusoff) == Set)
    {
        LOG_E("BUS OFF.");
    }
    if(true == CAN_IrqFlgGet(CanRxIrqFlg))
    {
        LOG_D("Received.");
        CAN_IrqFlgClr(CanRxIrqFlg);
        rt_hw_can_isr(&hc32_can->rt_can, RT_CAN_EVENT_RX_IND);
    }
    if(true == CAN_IrqFlgGet(CanTxPrimaryIrqFlg))
    {
        LOG_D("Transmitted.");
        CAN_IrqFlgClr(CanTxPrimaryIrqFlg);
        rt_hw_can_isr(&hc32_can->rt_can,RT_CAN_EVENT_TX_DONE);
    }
    if(true == CAN_IrqFlgGet(CanTxSecondaryIrqFlg))
    {
        LOG_D("Transmitted.");
        CAN_IrqFlgClr(CanTxSecondaryIrqFlg);
        rt_hw_can_isr(&hc32_can->rt_can,RT_CAN_EVENT_TX_DONE);
    }
    if(true == CAN_IrqFlgGet(CanErrorIrqFlg))
    {
        LOG_E("Error.");
        CAN_IrqFlgClr(CanErrorIrqFlg);
    }
    if(true == CAN_IrqFlgGet(CanAbortIrqFlg))
    {
        LOG_E("Abort.");
        CAN_IrqFlgClr(CanAbortIrqFlg);
    }
    if(true == CAN_IrqFlgGet(CanRxOverIrqFlg))
    {
        LOG_E("Overrun.");
        CAN_IrqFlgClr(CanRxOverIrqFlg);
    }
    if(true == CAN_IrqFlgGet(CanRxBufFullIrqFlg))
    {
        LOG_E("RB full.");
        CAN_IrqFlgClr(CanRxBufFullIrqFlg);
    }
    if(true == CAN_IrqFlgGet(CanRxBufAlmostFullIrqFlg))
    {
        LOG_E("RB almost full.");
        CAN_IrqFlgClr(CanRxBufAlmostFullIrqFlg);
    }
//    if(true == CAN_IrqFlgGet(CanErrorWarningIrqFlg))
//    {
//        LOG_E("Error warning limit reached.\r\n");
//        CAN_IrqFlgClr(CanErrorWarningIrqFlg);
//    }
//    if(true == CAN_IrqFlgGet(CanErrorPassivenodeIrqFlg))
//    {
//        LOG_E("Error passive mode active.\r\n");
//        CAN_IrqFlgClr(CanErrorPassivenodeIrqFlg);
//    }
    if(true == CAN_IrqFlgGet(CanErrorPassiveIrqFlg))
    {
        LOG_E("Error passive.");
        CAN_IrqFlgClr(CanErrorPassiveIrqFlg);
    }
    if(true == CAN_IrqFlgGet(CanArbiLostIrqFlg))
    {
        LOG_E("Arbitration lost.");
        CAN_IrqFlgClr(CanArbiLostIrqFlg);
    }
    if(true == CAN_IrqFlgGet(CanBusErrorIrqFlg))
    {
        LOG_E("Bus error.");
        CAN_IrqFlgClr(CanBusErrorIrqFlg);
    }
}
#if defined(BSP_USING_CAN1)
static void can1_irq_handler(void)
{
    rt_interrupt_enter();
    can_isr(&drv_can[CAN1_INDEX]);
    rt_interrupt_leave();
}
#endif

extern rt_err_t rt_hw_board_can_init(M4_CAN_TypeDef *CANx);
extern void CanPhyEnable(void);
int rt_hw_can_init(void)
{
    struct can_configure rt_can_config = CANDEFAULTCONFIG;
    rt_can_config.privmode = RT_CAN_MODE_NOPRIV;
    rt_can_config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    rt_can_config.maxhdr = FILTER_COUNT;
#endif

    /*Enable can peripheral clock and buffer(ram)*/
#if defined(HC32F460)
#if defined(BSP_USING_CAN1)
    PWC_RamOpMdConfig(HighSpeedMd);
    PWC_RamPwrdownCmd(PWC_RAMPWRDOWN_CAN, Enable);
    PWC_Fcg1PeriphClockCmd(PWC_FCG1_PERIPH_CAN, Enable);
#endif
#endif

    int result = RT_EOK;
    uint32_t i = 0;
    for (; i < CAN_INDEX_MAX; i++)
    {
        rt_hw_board_can_init(drv_can[i].instance);

        if (drv_can[i].p_ll_can_filter_cfg == RT_NULL)
        {
            drv_can[i].p_ll_can_filter_cfg = (stc_can_filter_t *)rt_malloc(sizeof(stc_can_filter_t) * FILTER_COUNT);
        }
        RT_ASSERT((drv_can[i].p_ll_can_filter_cfg != RT_NULL));

        rt_memset(drv_can[i].p_ll_can_filter_cfg, 0, sizeof(stc_can_filter_t) * FILTER_COUNT);
        drv_can[i].p_ll_can_filter_cfg[0].u32CODE = 0U;
        drv_can[i].p_ll_can_filter_cfg[0].u32MASK = 0x1FFFFFFF;
        drv_can[i].p_ll_can_filter_cfg[0].enFilterSel = CanFilterSel1;
        drv_can[i].p_ll_can_filter_cfg[0].enAcfFormat = CanAllFrames;
        drv_can[i].rt_can.config = rt_can_config;

        rt_uint32_t baud_index;
        baud_index = get_can_baud_index(rt_can_config.baud_rate);
        drv_can[i].ll_init.stcCanBt = can_baud_rate_tab[baud_index].ll_sbt;
        drv_can[i].ll_init.stcWarningLimit.CanErrorWarningLimitVal = 10u;
        drv_can[i].ll_init.stcWarningLimit.CanWarningLimitVal = 16u - 1u;

        drv_can[i].ll_init.enCanRxBufAll = CanRxNormal;
        drv_can[i].ll_init.enCanRxBufMode = CanRxBufNotStored;
        drv_can[i].ll_init.enCanSAck = CanSelfAckEnable;
        drv_can[i].ll_init.enCanSTBMode = CanSTBFifoMode;
        CAN_Init(&drv_can[i].ll_init);
        CAN_FilterConfig(drv_can[i].p_ll_can_filter_cfg, Disable);

        struct hc32_irq_config irq_config;
        #if defined(BSP_USING_CAN1)
        irq_config.irq = CAN1_INT_IRQn;
        irq_config.int_src = CAN1_INT_SRC;
        irq_config.irq_prio = CAN1_INT_PRIO;

        /* register interrupt */
        hc32_install_irq_handler(&irq_config,
                                 can1_irq_handler,
                                 RT_TRUE);
        CAN_IrqCmd(CanRxIrqEn, Enable);
        CAN_IrqCmd(CanTxPrimaryIrqEn, Enable);
        #endif

        /* register CAN1 device */
        rt_hw_can_register(&drv_can[i].rt_can,
                            drv_can[i].init.name,
                            &_can_ops,
                            &drv_can[i]);
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/
