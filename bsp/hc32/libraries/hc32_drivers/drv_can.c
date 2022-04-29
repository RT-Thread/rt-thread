/*
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#include "drv_can.h"
#include <drv_config.h>
#include <board_config.h>

#ifdef BSP_USING_CAN
#define LOG_TAG    "drv_can"

#if !defined(BSP_USING_CAN1) && !defined(BSP_USING_CAN2)
    #error "Please define at least one BSP_USING_CANx"
#endif

#if defined (HC32F4A0)
    #define FILTER_COUNT    (16)
#endif

enum
{
#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
#ifdef BSP_USING_CAN2
    CAN2_INDEX,
#endif
    CAN_INDEX_MAX,
};

struct hc32_baud_rate_tab
{
    rt_uint32_t baud_rate;
    stc_can_bit_time_config_t ll_sbt;
};

#if defined (HC32F4A0)
static const struct hc32_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud,   {2, 16, 4, 4}},
    {CAN800kBaud, {2, 20, 5, 4}},
    {CAN500kBaud, {4, 16, 4, 4}},
    {CAN250kBaud, {8, 16, 4, 4}},
    {CAN125kBaud, {16, 16, 4, 4}},
    {CAN100kBaud, {20, 16, 4, 4}},
    {CAN50kBaud,  {40, 16, 4, 4}},
    {CAN20kBaud,  {100, 16, 4, 4}},
    {CAN10kBaud,  {200, 16, 4, 4}},
};
#endif

typedef struct
{
    struct rt_can_device rt_can;
    struct hc32_can_init_type init;
    CM_CAN_TypeDef *instance;
    stc_can_init_t ll_init;
    stc_can_filter_config_t *p_ll_can_filter_cfg;
} hc32_drv_can;

static hc32_drv_can drv_can[] =
{
#ifdef BSP_USING_CAN1
    {
        {0},
        CAN1_CONFIG,
        .instance = CM_CAN1,
    },
#endif
#ifdef BSP_USING_CAN2
    {
        {0},
        CAN2_CONFIG,
        .instance = CM_CAN2,
    },
#endif
};

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

static rt_uint32_t get_can_work_mode(rt_uint32_t mode)
{
    rt_uint32_t work_mode;
    switch (mode)
    {
    case RT_CAN_MODE_NORMAL:
        work_mode = CAN_WORK_MD_NORMAL;
        break;
    case RT_CAN_MODE_LISEN:
        work_mode = CAN_WORK_MD_SILENT;
        break;
    case RT_CAN_MODE_LOOPBACK:
        work_mode = CAN_WORK_MD_ELB;
        break;
    case RT_CAN_MODE_LOOPBACKANLISEN:
        work_mode = CAN_WORK_MD_ELB_SILENT;
        break;
    default:
        work_mode = CAN_WORK_MD_NORMAL;
        break;
    }

    return work_mode;
}

static rt_err_t _can_config(struct rt_can_device *can, struct can_configure *cfg)
{
    rt_uint32_t baud_index;
    hc32_drv_can *hc32_can;
    rt_err_t rt_ret = RT_EOK;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    hc32_can = (hc32_drv_can *)rt_container_of(can, hc32_drv_can, rt_can);
    RT_ASSERT(hc32_can);

    hc32_can->ll_init.u8WorkMode = get_can_work_mode(cfg->mode);
    baud_index = get_can_baud_index(cfg->baud_rate);
    hc32_can->ll_init.stcBitCfg = can_baud_rate_tab[baud_index].ll_sbt;

    /* init can */
    int32_t ret = CAN_Init(hc32_can->instance, &hc32_can->ll_init);
    if (ret != LL_OK)
    {
        rt_ret = RT_EINVAL;
    }

    return rt_ret;
}

static uint16_t get_filter_idx(struct rt_can_filter_config *filter_cfg)
{
    uint16_t u16FilterSelected = 0;

    for (int i = 0; i < filter_cfg->count; i++)
    {
        if (filter_cfg->items[i].hdr != -1)
        {
            u16FilterSelected |= 1 << filter_cfg->items[i].hdr;
        }
    }

    for (int i = 0; i < filter_cfg->count; i++)
    {
        if (filter_cfg->items[i].hdr == -1)
        {
            for (int j = 0; j < FILTER_COUNT; j++)
            {
                if ((u16FilterSelected & 1 << j) == 0)
                {
                    filter_cfg->items[i].hdr = j;
                    u16FilterSelected |= 1 << filter_cfg->items[i].hdr;
                    break;
                }
            }
        }
    }

    return u16FilterSelected;
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
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_RX, DISABLE);
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_RX_BUF_WARN, DISABLE);
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_RX_BUF_FULL, DISABLE);
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_RX_OVERRUN, DISABLE);
            break;
        case RT_DEVICE_FLAG_INT_TX:
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_STB_TX, DISABLE);
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_PTB_TX, DISABLE);
            break;
        case RT_DEVICE_CAN_INT_ERR:
            CAN_IntCmd(hc32_can->instance, CAN_INT_ERR_INT, DISABLE);
            CAN_IntCmd(hc32_can->instance, CAN_INT_ARBITR_LOST, DISABLE);
            CAN_IntCmd(hc32_can->instance, CAN_INT_ERR_PASSIVE, DISABLE);
            CAN_IntCmd(hc32_can->instance, CAN_INT_BUS_ERR, DISABLE);
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
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_RX, ENABLE);
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_RX_BUF_WARN, ENABLE);
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_RX_BUF_FULL, ENABLE);
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_RX_OVERRUN, ENABLE);
            break;
        case RT_DEVICE_FLAG_INT_TX:
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_STB_TX, ENABLE);
            CAN_IntCmd(hc32_can->instance, CAN_FLAG_PTB_TX, ENABLE);
            break;
        case RT_DEVICE_CAN_INT_ERR:
            CAN_IntCmd(hc32_can->instance, CAN_INT_ERR_INT, ENABLE);
            CAN_IntCmd(hc32_can->instance, CAN_INT_ARBITR_LOST, ENABLE);
            CAN_IntCmd(hc32_can->instance, CAN_INT_ERR_PASSIVE, ENABLE);
            CAN_IntCmd(hc32_can->instance, CAN_INT_BUS_ERR, ENABLE);
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
                hc32_can->ll_init.u16FilterSelect = get_filter_idx(filter_cfg);
                for (int i = 0; i < filter_cfg->count; i++)
                {
                    hc32_can->p_ll_can_filter_cfg[i].u32ID = filter_cfg->items[i].id;
                    hc32_can->p_ll_can_filter_cfg[i].u32IDMask = filter_cfg->items[i].mask;
                    hc32_can->p_ll_can_filter_cfg[i].u32IDType = filter_cfg->items[i].ide;
                }
            }
            (void)CAN_Init(hc32_can->instance, &hc32_can->ll_init);
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
        stc_can_error_info_t stcErr = {0};
        CAN_GetErrorInfo(hc32_can->instance, &stcErr);
        rt_can_stat->rcverrcnt = stcErr.u8RxErrorCount;
        rt_can_stat->snderrcnt = stcErr.u8TxErrorCount;
        rt_can_stat->lasterrtype = stcErr.u8ErrorType;
        rt_can_stat->errcode = CAN_GetStatusValue(hc32_can->instance);

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
    stc_can_tx_frame_t stc_tx_frame = {0};
    int32_t ll_ret;

    RT_ASSERT(can != RT_NULL);
    hc32_drv_can *hc32_can = (hc32_drv_can *)rt_container_of(can, hc32_drv_can, rt_can);
    RT_ASSERT(hc32_can);

    /*check select mailbox  is empty */
    stc_tx_frame.u32ID = pmsg->id;
    if (RT_CAN_DTR == pmsg->rtr)
    {
        stc_tx_frame.RTR = 0;
    }
    else
    {
        stc_tx_frame.RTR = 1;
    }
    /* Set up the DLC */
    stc_tx_frame.DLC = pmsg->len & 0x0FU;
    /* Set up the data field */
    rt_memcpy(&stc_tx_frame.au8Data, pmsg->data, sizeof(stc_tx_frame.au8Data));

    ll_ret = CAN_FillTxFrame(hc32_can->instance, CAN_TX_BUF_PTB, &stc_tx_frame);
    if (ll_ret != LL_OK)
    {
        return RT_ERROR;
    }
    /* Request transmission */
    CAN_StartTx(hc32_can->instance, CAN_TX_REQ_PTB);
    return RT_EOK;
}

static int _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    int32_t ll_ret;
    struct rt_can_msg *pmsg;
    stc_can_rx_frame_t ll_rx_frame;

    RT_ASSERT(can != RT_NULL);
    hc32_drv_can *hc32_can = (hc32_drv_can *)rt_container_of(can, hc32_drv_can, rt_can);
    RT_ASSERT(hc32_can);

    pmsg = (struct rt_can_msg *) buf;

    /* get data */
    ll_ret = CAN_GetRxFrame(hc32_can->instance, &ll_rx_frame);
    if (ll_ret != LL_OK)
        return -RT_ERROR;
    /* get id */
    if (CAN_ID_STD == ll_rx_frame.IDE)
    {
        pmsg->ide = RT_CAN_STDID;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
    }
    pmsg->id = ll_rx_frame.u32ID;
    /* get type */
    if (0 == ll_rx_frame.RTR)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }
    /* get len */
    pmsg->len = ll_rx_frame.DLC;
    /* get hdr */
    pmsg->hdr = 0;
    rt_memcpy(pmsg->data, &ll_rx_frame.au8Data, ll_rx_frame.DLC);

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
    stc_can_error_info_t stcErr;

    (void)CAN_GetErrorInfo(hc32_can->instance, &stcErr);

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_BUS_OFF) == SET)
    {
        DDL_Printf("BUS OFF.\r\n");
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_RX_BUF_OVF) == SET)
    {
        DDL_Printf("RX overflow.\r\n");
        rt_hw_can_isr(&hc32_can->rt_can, RT_CAN_EVENT_RXOF_IND);
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_RX_BUF_OVF);
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_TX_BUF_FULL) == SET)
    {
        DDL_Printf("TX buffer full.\r\n");
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_TX_ABORTED) == SET)
    {
        DDL_Printf("TX aborted.\r\n");
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_TX_ABORTED);
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_ARBITR_LOST) == SET)
    {
        rt_hw_can_isr(&hc32_can->rt_can, RT_CAN_EVENT_TX_FAIL);
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_ARBITR_LOST);
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_STB_TX) == SET)
    {
        DDL_Printf("STB transmitted.\r\n");
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_STB_TX);
        rt_hw_can_isr(&hc32_can->rt_can, RT_CAN_EVENT_TX_DONE);
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_PTB_TX) == SET)
    {
        DDL_Printf("PTB transmitted.\r\n");
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_PTB_TX);
        rt_hw_can_isr(&hc32_can->rt_can, RT_CAN_EVENT_TX_DONE);
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_RX) == SET)
    {
        /* Received frame can be read here. */
        DDL_Printf("Received a frame.\r\n");
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_RX);
        rt_hw_can_isr(&hc32_can->rt_can, RT_CAN_EVENT_RX_IND);
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_RX_BUF_WARN) == SET)
    {
        /* Received frames can be read here. */
        DDL_Printf("RX buffer warning.\r\n");
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_RX_BUF_WARN);
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_RX_BUF_FULL) == SET)
    {
        /* Received frames can be read here. */
        DDL_Printf("RX buffer full.\r\n");
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_RX_BUF_FULL);
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_RX_OVERRUN) == SET)
    {
        DDL_Printf("RX buffer overrun.\r\n");
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_RX_OVERRUN);
    }

    if (CAN_GetStatus(hc32_can->instance, CAN_FLAG_TEC_REC_WARN) == SET)
    {
        DDL_Printf("TEC or REC reached warning limit.\r\n");
        CAN_ClearStatus(hc32_can->instance, CAN_FLAG_TEC_REC_WARN);
    }

    if (CAN_TTC_GetStatus(hc32_can->instance, CAN_TTC_FLAG_TIME_TRIG) == SET)
    {
        DDL_Printf("Time trigger interrupt.\r\n");
        CAN_TTC_ClearStatus(hc32_can->instance, CAN_TTC_FLAG_TIME_TRIG);
    }

    if (CAN_TTC_GetStatus(hc32_can->instance, CAN_TTC_FLAG_TRIG_ERR) == SET)
    {
        DDL_Printf("Trigger error interrupt.\r\n");
    }

    if (CAN_TTC_GetStatus(hc32_can->instance, CAN_TTC_FLAG_WATCH_TRIG) == SET)
    {
        DDL_Printf("Watch trigger interrupt.\r\n");
        CAN_TTC_ClearStatus(hc32_can->instance, CAN_TTC_FLAG_WATCH_TRIG);
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

#if defined(BSP_USING_CAN2)
static void can2_irq_handler(void)
{
    rt_interrupt_enter();
    can_isr(&drv_can[CAN2_INDEX]);
    rt_interrupt_leave();
}
#endif

extern rt_err_t rt_hw_board_can_init(CM_CAN_TypeDef *CANx);
extern void CanPhyEnable(void);
int rt_hw_can_init(void)
{
    struct can_configure rt_can_config  = CANDEFAULTCONFIG;
    rt_can_config.privmode = RT_CAN_MODE_NOPRIV;
    rt_can_config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    rt_can_config.maxhdr = FILTER_COUNT;
#endif

    struct hc32_irq_config irq_config;
#if defined(BSP_USING_CAN1)
    irq_config.irq_num = CAN1_INT_IRQn;
    irq_config.int_src = CAN1_INT_SRC;
    irq_config.irq_prio = CAN1_INT_PRIO;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             can1_irq_handler,
                             RT_TRUE);
#endif
#if defined(BSP_USING_CAN2)
    irq_config.irq_num = CAN2_INT_IRQn;
    irq_config.int_src = CAN2_INT_SRC;
    irq_config.irq_prio = CAN2_INT_PRIO;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             can2_irq_handler,
                             RT_TRUE);
#endif

#if defined(HC32F4A0)
#if defined(BSP_USING_CAN1)
    CLK_SetCANClockSrc(CLK_CAN1, CLK_CANCLK_SYSCLK_DIV6);
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_CAN1, ENABLE);
#endif
#if   defined(BSP_USING_CAN2)
    CLK_SetCANClockSrc(CLK_CAN2, CLK_CANCLK_SYSCLK_DIV6);
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_CAN2, ENABLE);
#endif
#endif

    CanPhyEnable();
    int result = RT_EOK;
    uint32_t i = 0;
    for (; i < CAN_INDEX_MAX; i++)
    {
        if (drv_can[i].p_ll_can_filter_cfg == RT_NULL)
        {
            drv_can[i].p_ll_can_filter_cfg = (stc_can_filter_config_t *)rt_malloc(sizeof(stc_can_filter_config_t) * FILTER_COUNT);
        }
        RT_ASSERT((drv_can[i].p_ll_can_filter_cfg != RT_NULL));

        rt_memset(drv_can[i].p_ll_can_filter_cfg, 0, sizeof(stc_can_filter_config_t) * FILTER_COUNT);
        drv_can[i].p_ll_can_filter_cfg[0].u32ID = 0U;
        drv_can[i].p_ll_can_filter_cfg[0].u32IDMask = 0x1FFFFFFF;
        drv_can[i].p_ll_can_filter_cfg[0].u32IDType = CAN_ID_STD;
        CAN_StructInit(&drv_can[i].ll_init);
        drv_can[i].ll_init.pstcFilter =  &drv_can[i].p_ll_can_filter_cfg[0];
        drv_can[i].ll_init.u16FilterSelect = CAN_FILTER1;
        drv_can[i].rt_can.config = rt_can_config;

        /* register CAN1 device */
        rt_hw_board_can_init(drv_can[i].instance);
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
