/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2022-04-28     CDT                  first version
 * 2022-06-07     xiaoxiaolisunny      add hc32f460 series
 * 2022-06-08     CDT                  fix a bug of RT_CAN_CMD_SET_FILTER
 * 2022-06-15     lianghongquan        fix bug, FILTER_COUNT, RT_CAN_CMD_SET_FILTER, interrupt setup and processing.
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
    #define FILTER_COUNT                                    (16)
    #define CAN1_INT_SRC                                    (INT_SRC_CAN1_HOST)
    #define CAN2_INT_SRC                                    (INT_SRC_CAN2_HOST)
#endif

#if defined (HC32F460)
    #define FILTER_COUNT                                    (8)
    #define CAN1_INT_SRC                                    (INT_SRC_CAN_INT)
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

struct can_baud_rate_tab
{
    rt_uint32_t baud_rate;
    stc_can_bit_time_config_t ll_sbt;
};

static const struct can_baud_rate_tab g_baudrate_tab[] =
{
    {CAN1MBaud,   CAN_BIT_TIME_CONFIG_1M_BAUD},
    {CAN800kBaud, CAN_BIT_TIME_CONFIG_800K_BAUD},
    {CAN500kBaud, CAN_BIT_TIME_CONFIG_500K_BAUD},
    {CAN250kBaud, CAN_BIT_TIME_CONFIG_250K_BAUD},
    {CAN125kBaud, CAN_BIT_TIME_CONFIG_125K_BAUD},
    {CAN100kBaud, CAN_BIT_TIME_CONFIG_100K_BAUD},
    {CAN50kBaud,  CAN_BIT_TIME_CONFIG_50K_BAUD},
    {CAN20kBaud,  CAN_BIT_TIME_CONFIG_20K_BAUD},
    {CAN10kBaud,  CAN_BIT_TIME_CONFIG_10K_BAUD},
};

typedef struct
{
    struct rt_can_device rt_can;
    struct can_dev_init_params init;
    CM_CAN_TypeDef *instance;
    stc_can_init_t ll_init;
} can_device;

static can_device g_can_dev_array[] =
{
#if defined (HC32F4A0)
#ifdef BSP_USING_CAN1
    {
        {0},
        CAN1_INIT_PARAMS,
        .instance = CM_CAN1,
    },
#endif
#ifdef BSP_USING_CAN2
    {
        {0},
        CAN2_INIT_PARAMS,
        .instance = CM_CAN2,
    },
#endif
#endif

#if defined (HC32F460)
#ifdef BSP_USING_CAN1
    {
        {0},
        CAN1_INIT_PARAMS,
        .instance = CM_CAN,
    },
#endif
#endif
};

static rt_uint32_t _get_can_baud_index(rt_uint32_t baud)
{
    rt_uint32_t len, index;

    len = sizeof(g_baudrate_tab) / sizeof(g_baudrate_tab[0]);
    for (index = 0; index < len; index++)
    {
        if (g_baudrate_tab[index].baud_rate == baud)
            return index;
    }

    return 0; /* default baud is CAN1MBaud */
}

static rt_uint32_t _get_can_work_mode(rt_uint32_t mode)
{
    rt_uint32_t work_mode;
    switch (mode)
    {
    case RT_CAN_MODE_NORMAL:
        work_mode = CAN_WORK_MD_NORMAL;
        break;
    case RT_CAN_MODE_LISTEN:
        work_mode = CAN_WORK_MD_SILENT;
        break;
    case RT_CAN_MODE_LOOPBACK:
        work_mode = CAN_WORK_MD_ELB;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
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
    can_device *p_can_dev;
    rt_err_t rt_ret = RT_EOK;

    RT_ASSERT(can);
    RT_ASSERT(cfg);
    p_can_dev = (can_device *)rt_container_of(can, can_device, rt_can);
    RT_ASSERT(p_can_dev);

    p_can_dev->ll_init.u8WorkMode = _get_can_work_mode(cfg->mode);
    baud_index = _get_can_baud_index(cfg->baud_rate);
    p_can_dev->ll_init.stcBitCfg = g_baudrate_tab[baud_index].ll_sbt;

    /* init can */
    int32_t ret = CAN_Init(p_can_dev->instance, &p_can_dev->ll_init);
    if (ret != LL_OK)
    {
        rt_ret = -RT_EINVAL;
    }

    return rt_ret;
}

static uint16_t _get_filter_idx(struct rt_can_filter_config *filter_cfg)
{
    uint16_t u16FilterSelected = 0;

    for (int i = 0; i < filter_cfg->count; i++)
    {
        if (filter_cfg->items[i].hdr_bank != -1)
        {
            u16FilterSelected |= 1 << filter_cfg->items[i].hdr_bank;
        }
    }

    for (int i = 0; i < filter_cfg->count; i++)
    {
        if (filter_cfg->items[i].hdr_bank == -1)
        {
            for (int j = 0; j < FILTER_COUNT; j++)
            {
                if ((u16FilterSelected & 1 << j) == 0)
                {
                    filter_cfg->items[i].hdr_bank = j;
                    u16FilterSelected |= 1 << filter_cfg->items[i].hdr_bank;
                    break;
                }
            }
        }
    }

    return u16FilterSelected;
}

static rt_err_t _can_control(struct rt_can_device *can, int cmd, void *arg)
{
    can_device *p_can_dev;
    rt_uint32_t argval;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    p_can_dev = (can_device *)rt_container_of(can, can_device, rt_can);
    RT_ASSERT(p_can_dev);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        switch (argval)
        {
        case RT_DEVICE_FLAG_INT_RX:
            CAN_IntCmd(p_can_dev->instance, CAN_INT_RX, DISABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_RX_BUF_WARN, DISABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_RX_BUF_FULL, DISABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_RX_OVERRUN, DISABLE);
            break;
        case RT_DEVICE_FLAG_INT_TX:
            CAN_IntCmd(p_can_dev->instance, CAN_INT_STB_TX, DISABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_PTB_TX, DISABLE);
            break;
        case RT_DEVICE_CAN_INT_ERR:
            CAN_IntCmd(p_can_dev->instance, CAN_INT_ERR_INT, DISABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_ARBITR_LOST, DISABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_ERR_PASSIVE, DISABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_BUS_ERR, DISABLE);
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
            CAN_IntCmd(p_can_dev->instance, CAN_INT_RX, ENABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_RX_BUF_WARN, ENABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_RX_BUF_FULL, ENABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_RX_OVERRUN, ENABLE);
            break;
        case RT_DEVICE_FLAG_INT_TX:
            CAN_IntCmd(p_can_dev->instance, CAN_INT_STB_TX, ENABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_PTB_TX, ENABLE);
            break;
        case RT_DEVICE_CAN_INT_ERR:
            CAN_IntCmd(p_can_dev->instance, CAN_INT_ERR_INT, ENABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_ARBITR_LOST, ENABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_ERR_PASSIVE, ENABLE);
            CAN_IntCmd(p_can_dev->instance, CAN_INT_BUS_ERR, ENABLE);
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
            if (p_can_dev->ll_init.pstcFilter)
            {
                p_can_dev->ll_init.u16FilterSelect = _get_filter_idx(filter_cfg);
                for (int i = 0; i < filter_cfg->count; i++)
                {
                    p_can_dev->ll_init.pstcFilter[i].u32ID = filter_cfg->items[i].id & 0x1FFFFFFF;
                    /* rt-thread CAN mask, 1 mean filer, 0 mean ignore. *
                     * HDSC HC32 CAN mask, 0 mean filer, 1 mean ignore. */
                    p_can_dev->ll_init.pstcFilter[i].u32IDMask = (~filter_cfg->items[i].mask) & 0x1FFFFFFF;
                    switch (filter_cfg->items[i].ide)
                    {
                        case (RT_CAN_STDID):
                            p_can_dev->ll_init.pstcFilter[i].u32IDType = CAN_ID_STD;
                            break;
                        case (RT_CAN_EXTID):
                            p_can_dev->ll_init.pstcFilter[i].u32IDType = CAN_ID_EXT;
                            break;
                        default:
                            p_can_dev->ll_init.pstcFilter[i].u32IDType = CAN_ID_STD_EXT;
                            break;
                    }
                }
            }
            (void)CAN_Init(p_can_dev->instance, &p_can_dev->ll_init);
            break;
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
        if (argval != p_can_dev->rt_can.config.mode)
        {
            p_can_dev->rt_can.config.mode = argval;
            _can_config(can, &p_can_dev->rt_can.config);
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
        if (argval != p_can_dev->rt_can.config.baud_rate)
        {
            p_can_dev->rt_can.config.baud_rate = argval;
            _can_config(can, &p_can_dev->rt_can.config);
        }
        break;
    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t) arg;
        if (argval != RT_CAN_MODE_PRIV &&
                argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        if (argval != p_can_dev->rt_can.config.privmode)
        {
            p_can_dev->rt_can.config.privmode = argval;
            return _can_config(can, &p_can_dev->rt_can.config);
        }
        break;
    case RT_CAN_CMD_GET_STATUS:
    {
        struct rt_can_status *rt_can_stat = (struct rt_can_status *)arg;
        stc_can_error_info_t stcErr = {0};
        CAN_GetErrorInfo(p_can_dev->instance, &stcErr);
        rt_can_stat->rcverrcnt = stcErr.u8RxErrorCount;
        rt_can_stat->snderrcnt = stcErr.u8TxErrorCount;
        rt_can_stat->lasterrtype = stcErr.u8ErrorType;
        rt_can_stat->errcode = CAN_GetStatusValue(p_can_dev->instance);

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
    can_device *p_can_dev = (can_device *)rt_container_of(can, can_device, rt_can);
    RT_ASSERT(p_can_dev);

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
    /* Set up the IDE */
    stc_tx_frame.IDE = pmsg->ide;
    /* Set up the data field */
    rt_memcpy(&stc_tx_frame.au8Data, pmsg->data, sizeof(stc_tx_frame.au8Data));
    ll_ret = CAN_FillTxFrame(p_can_dev->instance, CAN_TX_BUF_PTB, &stc_tx_frame);
    if (ll_ret != LL_OK)
    {
        return RT_ERROR;
    }
    /* Request transmission */
    CAN_StartTx(p_can_dev->instance, CAN_TX_REQ_PTB);

    return RT_EOK;
}

static int _can_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    int32_t ll_ret;
    struct rt_can_msg *pmsg;
    stc_can_rx_frame_t ll_rx_frame;

    RT_ASSERT(can != RT_NULL);
    can_device *p_can_dev = (can_device *)rt_container_of(can, can_device, rt_can);
    RT_ASSERT(p_can_dev);

    pmsg = (struct rt_can_msg *) buf;
    /* get data */
    ll_ret = CAN_GetRxFrame(p_can_dev->instance, &ll_rx_frame);
    if (ll_ret != LL_OK)
        return -RT_ERROR;

    /* get id */
    if (0 == ll_rx_frame.IDE)
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
    /* get hdr_index */
    pmsg->hdr_index = 0;
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

static void _can_isr(can_device *p_can_dev)
{
    stc_can_error_info_t stcErr;

    (void)CAN_GetErrorInfo(p_can_dev->instance, &stcErr);

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_BUS_OFF) == SET)
    {
        /* BUS OFF. */
    }
    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_ERR_INT) == SET)
    {
        /* ERROR. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_ERR_INT);
    }
    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_BUS_ERR) == SET)
    {
        /* BUS ERROR. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_BUS_ERR);
    }
    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_ERR_PASSIVE) == SET)
    {
        /* error-passive to error-active or error-active to error-passive. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_ERR_PASSIVE);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_OVF) == SET)
    {
        /* RX overflow. */
        rt_hw_can_isr(&p_can_dev->rt_can, RT_CAN_EVENT_RXOF_IND);
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_OVF);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_TX_BUF_FULL) == SET)
    {
        /* TX buffer full. */
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_TX_ABORTED) == SET)
    {
        /* TX aborted. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_TX_ABORTED);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_ARBITR_LOST) == SET)
    {
        rt_hw_can_isr(&p_can_dev->rt_can, RT_CAN_EVENT_TX_FAIL);
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_ARBITR_LOST);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_STB_TX) == SET)
    {
        /* STB transmitted. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_STB_TX);
        rt_hw_can_isr(&p_can_dev->rt_can, RT_CAN_EVENT_TX_DONE);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_PTB_TX) == SET)
    {
        /* PTB transmitted. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_PTB_TX);
        rt_hw_can_isr(&p_can_dev->rt_can, RT_CAN_EVENT_TX_DONE);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX) == SET)
    {
        /* Received a frame. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX);
        rt_hw_can_isr(&p_can_dev->rt_can, RT_CAN_EVENT_RX_IND);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_WARN) == SET)
    {
        /* RX buffer warning. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_WARN);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_FULL) == SET)
    {
        /* RX buffer full. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX_BUF_FULL);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_RX_OVERRUN) == SET)
    {
        /* RX buffer overrun. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_RX_OVERRUN);
    }

    if (CAN_GetStatus(p_can_dev->instance, CAN_FLAG_TEC_REC_WARN) == SET)
    {
        /* TEC or REC reached warning limit. */
        CAN_ClearStatus(p_can_dev->instance, CAN_FLAG_TEC_REC_WARN);
    }

    if (CAN_TTC_GetStatus(p_can_dev->instance, CAN_TTC_FLAG_TIME_TRIG) == SET)
    {
        /* Time trigger interrupt. */
        CAN_TTC_ClearStatus(p_can_dev->instance, CAN_TTC_FLAG_TIME_TRIG);
    }

    if (CAN_TTC_GetStatus(p_can_dev->instance, CAN_TTC_FLAG_TRIG_ERR) == SET)
    {
        /* Trigger error interrupt. */
    }

    if (CAN_TTC_GetStatus(p_can_dev->instance, CAN_TTC_FLAG_WATCH_TRIG) == SET)
    {
        /* Watch trigger interrupt. */
        CAN_TTC_ClearStatus(p_can_dev->instance, CAN_TTC_FLAG_WATCH_TRIG);
    }
}
#if defined(BSP_USING_CAN1)
static void _can1_irq_handler(void)
{
    rt_interrupt_enter();
    _can_isr(&g_can_dev_array[CAN1_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_CAN2)
static void _can2_irq_handler(void)
{
    rt_interrupt_enter();
    _can_isr(&g_can_dev_array[CAN2_INDEX]);
    rt_interrupt_leave();
}
#endif

static void _can_clock_enable(void)
{
#if defined(HC32F4A0)
#if defined(BSP_USING_CAN1)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_CAN1, ENABLE);
#endif
#if   defined(BSP_USING_CAN2)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_CAN2, ENABLE);
#endif
#endif

#if defined(HC32F460)
#if defined(BSP_USING_CAN1)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_CAN, ENABLE);
#endif
#endif
}

static void _can_irq_config(void)
{
    struct hc32_irq_config irq_config;
#if defined(BSP_USING_CAN1)
    irq_config.irq_num = BSP_CAN1_IRQ_NUM;
    irq_config.int_src = CAN1_INT_SRC;
    irq_config.irq_prio = BSP_CAN1_IRQ_PRIO;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             _can1_irq_handler,
                             RT_TRUE);
#endif
#if defined(BSP_USING_CAN2)
    irq_config.irq_num = BSP_CAN2_IRQ_NUM;
    irq_config.int_src = CAN2_INT_SRC;
    irq_config.irq_prio = BSP_CAN2_IRQ_PRIO;
    /* register interrupt */
    hc32_install_irq_handler(&irq_config,
                             _can2_irq_handler,
                             RT_TRUE);
#endif
}

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

    _can_irq_config();
    _can_clock_enable();
    CanPhyEnable();
    int result = RT_EOK;
    uint32_t i = 0;
    for (; i < CAN_INDEX_MAX; i++)
    {
        CAN_StructInit(&g_can_dev_array[i].ll_init);
        if (g_can_dev_array[i].ll_init.pstcFilter == RT_NULL)
        {
            g_can_dev_array[i].ll_init.pstcFilter = (stc_can_filter_config_t *)rt_malloc(sizeof(stc_can_filter_config_t) * FILTER_COUNT);
        }
        RT_ASSERT((g_can_dev_array[i].ll_init.pstcFilter != RT_NULL));

        rt_memset(g_can_dev_array[i].ll_init.pstcFilter, 0, sizeof(stc_can_filter_config_t) * FILTER_COUNT);
        g_can_dev_array[i].ll_init.pstcFilter[0].u32ID = 0U;
        g_can_dev_array[i].ll_init.pstcFilter[0].u32IDMask = 0x1FFFFFFF;
        g_can_dev_array[i].ll_init.pstcFilter[0].u32IDType = CAN_ID_STD_EXT;
        g_can_dev_array[i].ll_init.u16FilterSelect = CAN_FILTER1;
        g_can_dev_array[i].rt_can.config = rt_can_config;

        /* register CAN device */
        rt_hw_board_can_init(g_can_dev_array[i].instance);
        rt_hw_can_register(&g_can_dev_array[i].rt_can,
                           g_can_dev_array[i].init.name,
                           &_can_ops,
                           &g_can_dev_array[i]);
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_can_init);

#endif /* BSP_USING_CAN */

/************************** end of file ******************/
