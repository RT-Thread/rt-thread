/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2024-xx-xx     CDT                  first version
 */

#include "drv_mcan.h"
#include <drv_config.h>
#include <board_config.h>

#if defined(BSP_USING_MCAN)
#define LOG_TAG    "drv_mcan"

/****************************************************************************************
* Type definitions for MCAN RT driver
****************************************************************************************/
typedef struct hc32_mcan_config_struct
{
    char *name;                         /* MCAN instance name */
    CM_MCAN_TypeDef *instance;          /* MCAN instance */
    stc_mcan_init_t init_para;          /* MCAN initialisation parameters */

    uint32_t int0_sel;
    struct hc32_irq_config int0_cfg;    /* MCAN interrupt line 0 configuration */
    uint32_t int1_sel;
    struct hc32_irq_config int1_cfg;    /* MCAN interrupt line 1 configuration */
} hc32_mcan_config_t;

typedef struct hc32_mcan_driver_struct
{
    hc32_mcan_config_t mcan;            /* MCAN configuration */
    struct rt_can_device can_device;    /* inherit from rt can device */
    uint32_t tx_box_num;                /* current tx box number */
} hc32_mcan_driver_t;

typedef struct mcan_baud_rate_struct
{
    rt_uint32_t baud_rate;
    rt_uint32_t baud_rate_fd;
    stc_mcan_bit_time_config_t ll_bt;
} mcan_baud_rate_t;

/****************************************************************************************
* Parameter validity check
****************************************************************************************/
#if defined(BSP_USING_MCAN1) || defined(BSP_USING_MCAN2)
#define IS_RT_CAN_WORK_MODE(mode)           ((mode) <= RT_CAN_MODE_LOOPBACKANLISTEN)
#define IS_RT_CAN_PRIV_MODE(mode)           (((mode) == RT_CAN_MODE_PRIV) || ((mode) == RT_CAN_MODE_NOPRIV))
#define IS_MCAN_FD_MODE(mode)               (((mode) >= MCAN_FD_ARG_MIN) && ((mode) <= MCAN_FD_ARG_MAX))

#define IS_MCAN_CC_BAUD_RATE(baud)          ((baud) == (CAN10kBaud)  || \
                                             (baud) == (CAN20kBaud)  || \
                                             (baud) == (CAN50kBaud)  || \
                                             (baud) == (CAN125kBaud) || \
                                             (baud) == (CAN250kBaud) || \
                                             (baud) == (CAN500kBaud) || \
                                             (baud) == (CAN1MBaud))

#define IS_MCAN_NOMINAL_BAUD_RATE(baud)     ((baud) == (CAN500kBaud) || \
                                             (baud) == (CAN1MBaud))

#define IS_MCAN_DATA_BAUD_RATE(baud)        ((baud) == (MCANFD_DATA_BAUD_1M) || \
                                             (baud) == (MCANFD_DATA_BAUD_2M) || \
                                             (baud) == (MCANFD_DATA_BAUD_4M) || \
                                             (baud) == (MCANFD_DATA_BAUD_5M) || \
                                             (baud) == (MCANFD_DATA_BAUD_8M))

#define IS_CAN_VALID_ID(ide, id)            ((((ide) == 0) && ((id) <= MCAN_STD_ID_MASK)) || \
                                             (((ide) == 1) && ((id) <= MCAN_EXT_ID_MASK)))

/****************************************************************************************
* Interrupt definitions
****************************************************************************************/
#define MCAN_RX_INT                         (MCAN_INT_RX_FIFO0_NEW_MSG | MCAN_INT_RX_FIFO1_NEW_MSG | MCAN_INT_RX_BUF_NEW_MSG)
#define MCAN_TX_INT                         (MCAN_INT_TX_CPLT)
#define MCAN_ERR_INT                        (MCAN_INT_ARB_PHASE_ERROR | MCAN_INT_DATA_PHASE_ERROR | MCAN_INT_ERR_LOG_OVF | \
                                             MCAN_INT_ERR_PASSIVE | MCAN_INT_ERR_WARNING | MCAN_INT_BUS_OFF)
#define MCAN_INT0_SEL                       MCAN_RX_INT
#define MCAN_INT1_SEL                       (MCAN_TX_INT | MCAN_ERR_INT)

/****************************************************************************************
* Baud rate(bit timing) configuration based on 80MHz clock
****************************************************************************************/
#ifdef RT_CAN_USING_CANFD
static const mcan_baud_rate_t m_mcan_fd_baud_rate[] =
{
    {CAN500kBaud, MCANFD_DATA_BAUD_1M, MCAN_FD_CFG_500K_1M},
    {CAN500kBaud, MCANFD_DATA_BAUD_2M, MCAN_FD_CFG_500K_2M},
    {CAN500kBaud, MCANFD_DATA_BAUD_4M, MCAN_FD_CFG_500K_4M},
    {CAN500kBaud, MCANFD_DATA_BAUD_5M, MCAN_FD_CFG_500K_5M},
    {CAN500kBaud, MCANFD_DATA_BAUD_8M, MCAN_FD_CFG_500K_8M},
    {CAN1MBaud, MCANFD_DATA_BAUD_1M, MCAN_FD_CFG_1M_1M},
    {CAN1MBaud, MCANFD_DATA_BAUD_2M, MCAN_FD_CFG_1M_2M},
    {CAN1MBaud, MCANFD_DATA_BAUD_4M, MCAN_FD_CFG_1M_4M},
    {CAN1MBaud, MCANFD_DATA_BAUD_5M, MCAN_FD_CFG_1M_5M},
    {CAN1MBaud, MCANFD_DATA_BAUD_8M, MCAN_FD_CFG_1M_8M},
};
#endif

static const mcan_baud_rate_t m_mcan_cc_baud_rate[] =
{
    {CAN1MBaud,   0, MCAN_CC_CFG_1M},
    {CAN800kBaud, 0, MCAN_CC_CFG_800K},
    {CAN500kBaud, 0, MCAN_CC_CFG_500K},
    {CAN250kBaud, 0, MCAN_CC_CFG_250K},
    {CAN125kBaud, 0, MCAN_CC_CFG_125K},
    {CAN100kBaud, 0, MCAN_CC_CFG_100K},
    {CAN50kBaud,  0, MCAN_CC_CFG_50K},
    {CAN20kBaud,  0, MCAN_CC_CFG_20K},
    {CAN10kBaud,  0, MCAN_CC_CFG_10K},
};

/****************************************************************************************
* Constants
****************************************************************************************/
static const uint8_t m_mcan_data_size[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

static const rt_uint32_t m_mcan_tx_priv_mode[] = {MCAN_TX_FIFO_MD, MCAN_TX_QUEUE_MD};

static const rt_uint32_t m_mcan_work_mode[] = {MCAN_MD_NORMAL, MCAN_MD_BUS_MON, MCAN_MD_EXTERN_LOOPBACK, MCAN_MD_RESTRICTED_OP};

#ifdef RT_CAN_USING_CANFD
static const rt_uint32_t m_mcan_fd_mode[] = {MCAN_FRAME_CLASSIC, MCAN_FRAME_ISO_FD_NO_BRS, MCAN_FRAME_ISO_FD_BRS, \
                                             MCAN_FRAME_NON_ISO_FD_NO_BRS, MCAN_FRAME_NON_ISO_FD_BRS
                                            };
#endif

/****************************************************************************************
* Driver instance list
****************************************************************************************/
enum
{
#ifdef BSP_USING_MCAN1
    MCAN1_INDEX,
#endif
#ifdef BSP_USING_MCAN2
    MCAN2_INDEX,
#endif
    MCAN_DEV_CNT,
};

static hc32_mcan_driver_t m_mcan_driver_list[] =
{
#ifdef BSP_USING_MCAN1
    {
        {
            .name = MCAN1_NAME,
            .instance = CM_MCAN1,
            .init_para = {.stcBitTime = MCAN1_BAUD_RATE_CFG},
            .int0_sel = MCAN_INT0_SEL,
            .int0_cfg = {MCAN1_INT0_IRQn, BSP_MCAN1_INT0_IRQ_PRIO, INT_SRC_MCAN1_INT0},
            .int1_sel = MCAN_INT1_SEL,
            .int1_cfg = {MCAN1_INT1_IRQn, BSP_MCAN1_INT0_IRQ_PRIO, INT_SRC_MCAN1_INT1},
        }
    },
#endif
#ifdef BSP_USING_MCAN2
    {
        {
            .name = MCAN2_NAME,
            .instance = CM_MCAN2,
            .init_para = {.stcBitTime = MCAN2_BAUD_RATE_CFG},
            .int0_sel = MCAN_INT0_SEL,
            .int0_cfg = {MCAN2_INT0_IRQn, BSP_MCAN2_INT0_IRQ_PRIO, INT_SRC_MCAN2_INT0},
            .int1_sel = MCAN_INT1_SEL,
            .int1_cfg = {MCAN2_INT1_IRQn, BSP_MCAN2_INT1_IRQ_PRIO, INT_SRC_MCAN2_INT1},
        }
    },
#endif
};

#ifdef BSP_USING_MCAN1
    static stc_mcan_filter_t m_mcan1_std_filters[MCAN1_STD_FILTER_NUM];
    static stc_mcan_filter_t m_mcan1_ext_filters[MCAN1_EXT_FILTER_NUM];
#endif

#ifdef BSP_USING_MCAN2
    static stc_mcan_filter_t m_mcan2_std_filters[MCAN2_STD_FILTER_NUM];
    static stc_mcan_filter_t m_mcan2_ext_filters[MCAN2_EXT_FILTER_NUM];
#endif

/****************************************************************************************
* Driver operations
****************************************************************************************/
/**
 * @brief Configure CAN controller
 * @param [in/out] can CAN device pointer
 * @param [in] cfg CAN configuration pointer
 * @retval RT_EOK for valid configuration
 * @retval -RT_ERROR for invalid configuration
 */
static rt_err_t mcan_configure(struct rt_can_device *device, struct can_configure *cfg);

/**
 * @brief Control/Get CAN state
 *        including:interrupt, mode, priority, baudrate, filter, status
 * @param [in/out] can CAN device pointer
 * @param [in] cmd Control command
 * @param [in/out] arg Argument pointer
 * @retval RT_EOK for valid control command and arg
 * @retval -RT_ERROR for invalid control command or arg
 */
static rt_err_t mcan_control(struct rt_can_device *device, int cmd, void *arg);

/**
 * @brief Send out CAN message
 * @param [in] can CAN device pointer
 * @param [in] buf CAN message buffer
 * @param [in] boxno Mailbox number, it is not used in this porting
 * @retval RT_EOK No error
 * @retval -RT_ETIMEOUT timeout happened
 * @retval -RT_EFULL Transmission buffer is full
 */
static rt_ssize_t mcan_sendmsg(struct rt_can_device *device, const void *buf, rt_uint32_t boxno);

/**
 * @brief Receive message from CAN
 * @param [in] can CAN device pointer
 * @param [out] buf CAN receive buffer
 * @param [in] boxno Mailbox Number, it is not used in this porting
 * @retval RT_EOK no error
 * @retval -RT_ERROR Error happened during reading receive FIFO
 * @retval -RT_EMPTY no data in receive FIFO
 */
static rt_ssize_t mcan_recvmsg(struct rt_can_device *device, void *buf, rt_uint32_t boxno);

static const struct rt_can_ops m_mcan_ops =
{
    mcan_configure,
    mcan_control,
    mcan_sendmsg,
    mcan_recvmsg,
};

/****************************************************************************************
* mcan configure
****************************************************************************************/
static rt_err_t mcan_configure(struct rt_can_device *device, struct can_configure *cfg)
{
    rt_uint32_t i, len;
    rt_err_t rt_ret = RT_EOK;
    hc32_mcan_driver_t *driver;
    hc32_mcan_config_t *hard;
    stc_mcan_filter_t *std_filters, *ext_filters;

    RT_ASSERT(device);
    RT_ASSERT(cfg);
    driver = (hc32_mcan_driver_t *)device->parent.user_data;
    RT_ASSERT(driver);
    hard = &driver->mcan;

    RT_ASSERT(IS_RT_CAN_WORK_MODE(cfg->mode));
    RT_ASSERT(IS_RT_CAN_PRIV_MODE(cfg->privmode));

    hard->init_para.u32Mode = m_mcan_work_mode[cfg->mode];
    hard->init_para.u32FrameFormat = MCAN_FRAME_CLASSIC;
    hard->init_para.stcMsgRam.u32TxFifoQueueMode = m_mcan_tx_priv_mode[cfg->privmode];
#ifdef RT_CAN_USING_CANFD
    RT_ASSERT(IS_MCAN_FD_MODE(cfg->enable_canfd));
    hard->init_para.u32FrameFormat = m_mcan_fd_mode[cfg->enable_canfd];
    if (cfg->use_bit_timing)
    {
        hard->init_para.stcBitTime.u32NominalPrescaler = cfg->can_timing.prescaler;
        hard->init_para.stcBitTime.u32NominalTimeSeg1 = cfg->can_timing.num_seg1;
        hard->init_para.stcBitTime.u32NominalTimeSeg2 = cfg->can_timing.num_seg2;
        hard->init_para.stcBitTime.u32NominalSyncJumpWidth = cfg->can_timing.num_sjw;

        hard->init_para.stcBitTime.u32DataPrescaler = cfg->canfd_timing.prescaler;
        hard->init_para.stcBitTime.u32DataTimeSeg1 = cfg->canfd_timing.num_seg1;
        hard->init_para.stcBitTime.u32DataTimeSeg2 = cfg->canfd_timing.num_seg2;
        hard->init_para.stcBitTime.u32DataSyncJumpWidth = cfg->canfd_timing.num_sjw;
        hard->init_para.stcBitTime.u32SspOffset = cfg->canfd_timing.num_sspoff;

        cfg->use_bit_timing = 0;
    }
    else
    {
        RT_ASSERT(IS_MCAN_NOMINAL_BAUD_RATE(cfg->baud_rate));
        RT_ASSERT(IS_MCAN_DATA_BAUD_RATE(cfg->baud_rate_fd));

        len = sizeof(m_mcan_fd_baud_rate) / sizeof(m_mcan_fd_baud_rate[0]);
        for (i = 0; i < len; i++)
        {
            if ((cfg->baud_rate == m_mcan_fd_baud_rate[i].baud_rate) && \
                    (cfg->baud_rate_fd == m_mcan_fd_baud_rate[i].baud_rate_fd))
            {
                hard->init_para.stcBitTime = m_mcan_fd_baud_rate[i].ll_bt;
                break;
            }
        }
        if (i >= len)
        {
            rt_ret = -RT_ERROR;
        }
    }
#else
    RT_ASSERT(IS_MCAN_CC_BAUD_RATE(cfg->baud_rate));
    len = sizeof(m_mcan_cc_baud_rate) / sizeof(m_mcan_cc_baud_rate[0]);
    for (i = 0; i < len; i++)
    {
        if (cfg->baud_rate == m_mcan_cc_baud_rate[i].baud_rate)
        {
            hard->init_para.stcBitTime = m_mcan_cc_baud_rate[i].ll_bt;
            break;
        }
    }
    if (i >= len)
    {
        rt_ret = -RT_ERROR;
    }
#endif
    if (rt_ret == RT_EOK)
    {
        std_filters = hard->init_para.stcFilter.pstcStdFilterList;
        ext_filters = hard->init_para.stcFilter.pstcExtFilterList;
        hard->init_para.stcFilter.pstcStdFilterList = NULL;
        hard->init_para.stcFilter.pstcExtFilterList = NULL;
        if (MCAN_Init(hard->instance, &hard->init_para) != LL_OK)
        {
            hard->init_para.stcFilter.pstcStdFilterList = std_filters;
            hard->init_para.stcFilter.pstcExtFilterList = ext_filters;
            return -RT_ERROR;
        }
    }

    hard->init_para.stcFilter.pstcStdFilterList = std_filters;
    hard->init_para.stcFilter.pstcExtFilterList = ext_filters;
    for (i = 0; i < hard->init_para.stcMsgRam.u32StdFilterNum; i++)
    {
        if (MCAN_FilterConfig(hard->instance, &hard->init_para.stcFilter.pstcStdFilterList[i]) != LL_OK)
        {
            return -RT_ERROR;
        }
    }

    for (i = 0; i < hard->init_para.stcMsgRam.u32ExtFilterNum; i++)
    {
        if (MCAN_FilterConfig(hard->instance, &hard->init_para.stcFilter.pstcExtFilterList[i]) != LL_OK)
        {
            return -RT_ERROR;
        }
    }

    struct can_configure pre_config = driver->can_device.config;
    rt_memcpy(&driver->can_device.config, cfg, sizeof(struct can_configure));
    /* restore unmodifiable member */
    if ((driver->can_device.parent.open_flag & RT_DEVICE_OFLAG_OPEN) == RT_DEVICE_OFLAG_OPEN)
    {
        driver->can_device.config.msgboxsz = pre_config.msgboxsz;
        driver->can_device.config.ticks = pre_config.ticks;
    }
#ifdef RT_CAN_USING_HDR
    driver->can_device.config.maxhdr = pre_config.maxhdr;
#endif
    driver->can_device.config.sndboxnumber = pre_config.sndboxnumber;

    MCAN_Start(hard->instance);

    return RT_EOK;
}

/****************************************************************************************
* mcan control
****************************************************************************************/
static void mcan_control_set_int(hc32_mcan_driver_t *driver, int cmd, void *arg)
{
    en_functional_state_t new_state = DISABLE;
    rt_uint32_t int_flag = (rt_uint32_t)arg;
    hc32_mcan_config_t *hard = &driver->mcan;

    if (cmd == RT_DEVICE_CTRL_SET_INT)
    {
        new_state = ENABLE;
    }
    switch (int_flag)
    {
    case RT_DEVICE_FLAG_INT_RX:
        if (MCAN_RX_INT & hard->int0_sel)
        {
            MCAN_IntCmd(hard->instance, MCAN_RX_INT & hard->int0_sel, MCAN_INT_LINE0, new_state);
        }
        if (MCAN_RX_INT & hard->int1_sel)
        {
            MCAN_IntCmd(hard->instance, MCAN_RX_INT & hard->int1_sel, MCAN_INT_LINE1, new_state);
        }
        break;
    case RT_DEVICE_FLAG_INT_TX:
        rt_uint32_t tmp;
        tmp = hard->init_para.stcMsgRam.u32TxBufferNum + hard->init_para.stcMsgRam.u32TxFifoQueueNum;
        if (tmp >= 32)
        {
            tmp = 0xFFFFFFFF;
        }
        else
        {
            tmp = (1UL << tmp) - 1;
        }
        MCAN_TxBufferNotificationCmd(hard->instance, tmp, MCAN_INT_TX_CPLT, ENABLE);

        if (MCAN_TX_INT & hard->int0_sel)
        {
            MCAN_IntCmd(hard->instance, MCAN_TX_INT & hard->int0_sel, MCAN_INT_LINE0, new_state);
        }
        if (MCAN_TX_INT & hard->int1_sel)
        {
            MCAN_IntCmd(hard->instance, MCAN_TX_INT & hard->int1_sel, MCAN_INT_LINE1, new_state);
        }
        break;
    case RT_DEVICE_CAN_INT_ERR:
        if (MCAN_ERR_INT & hard->int0_sel)
        {
            MCAN_IntCmd(hard->instance, MCAN_ERR_INT & hard->int0_sel, MCAN_INT_LINE0, new_state);
        }
        if (MCAN_ERR_INT & hard->int1_sel)
        {
            MCAN_IntCmd(hard->instance, MCAN_ERR_INT & hard->int1_sel, MCAN_INT_LINE1, new_state);
        }
        break;
    default:
        break;
    }
}

static rt_err_t mcan_control_set_filter(hc32_mcan_driver_t *driver, int cmd, void *arg)
{
    //rt_uint8_t sf_cnt = 0, ef_cnt = 0;
    rt_uint8_t sf_default_idx = 0, ef_default_idx = 0;
    stc_mcan_filter_t ll_filter;
    hc32_mcan_config_t *hard = &driver->mcan;
    struct rt_can_filter_config *device_filter = (struct rt_can_filter_config *)arg;

    for (int i = 0; i < device_filter->count; i++)
    {
        RT_ASSERT(IS_CAN_VALID_ID(device_filter->items[i].ide, device_filter->items[i].id));
        RT_ASSERT((device_filter->items[i].rxfifo == CAN_RX_FIFO0) || (device_filter->items[i].rxfifo == CAN_RX_FIFO1));
        if (device_filter->items[i].rxfifo == CAN_RX_FIFO1)
        {
            RT_ASSERT(hard->init_para.stcMsgRam.u32RxFifo1Num > 0);
        }

        /* rt filter mode: 0 - list; 1 - mask  */
        static const rt_uint32_t mcan_filter_type[] = {MCAN_FILTER_RANGE, MCAN_FILTER_MASK};
        static const rt_uint32_t mcan_filter_config[] = {MCAN_FILTER_TO_RX_FIFO0, MCAN_FILTER_TO_RX_FIFO1};
        /* rt CAN filter to MCAN LL driver filter */
        ll_filter.u32IdType       = device_filter->items[i].ide;
        ll_filter.u32FilterType   = mcan_filter_type[device_filter->items[i].mode];
        ll_filter.u32FilterConfig = mcan_filter_config[device_filter->items[i].rxfifo];
        ll_filter.u32FilterId1    = device_filter->items[i].id;
        ll_filter.u32FilterId2    = device_filter->items[i].mask;

        if (device_filter->items[i].ide == RT_CAN_STDID)
        {
            ll_filter.u32FilterId1 &= MCAN_STD_ID_MASK;
            ll_filter.u32FilterId2 &= MCAN_STD_ID_MASK;
            if (device_filter->items[i].hdr_bank == -1)
            {
                ll_filter.u32FilterIndex = sf_default_idx;
                sf_default_idx++;
            }
            else
            {
                ll_filter.u32FilterIndex = device_filter->items[i].hdr_bank;
            }
            RT_ASSERT(ll_filter.u32FilterIndex < hard->init_para.stcMsgRam.u32StdFilterNum);
            m_mcan1_std_filters[ll_filter.u32FilterIndex] = ll_filter;
            //sf_cnt++;
        }
        else
        {
            ll_filter.u32FilterId1 &= MCAN_EXT_ID_MASK;
            ll_filter.u32FilterId2 &= MCAN_EXT_ID_MASK;
            if (device_filter->items[i].hdr_bank == -1)
            {
                ll_filter.u32FilterIndex = ef_default_idx;
                ef_default_idx++;
            }
            else
            {
                ll_filter.u32FilterIndex = device_filter->items[i].hdr_bank;
            }
            RT_ASSERT(ll_filter.u32FilterIndex < hard->init_para.stcMsgRam.u32ExtFilterNum);
            m_mcan1_ext_filters[ll_filter.u32FilterIndex] = ll_filter;
            //ef_cnt++;
        }
    }

    return RT_EOK;
}

static rt_err_t mcan_control_set_mode(hc32_mcan_driver_t *driver, int cmd, void *arg, struct can_configure *cfg)
{
    rt_uint32_t argval = (rt_uint32_t)arg;

    (void)cmd;
    RT_ASSERT(IS_RT_CAN_WORK_MODE(argval));
    if (!IS_RT_CAN_WORK_MODE(argval))
    {
        return -RT_ERROR;
    }
    if (argval == driver->can_device.config.mode)
    {
        return -RT_EOK;
    }
    cfg->mode = argval;
    return RT_EOK;
}

static rt_err_t mcan_control_set_priv(hc32_mcan_driver_t *driver, int cmd, void *arg, struct can_configure *cfg)
{
    rt_uint32_t argval = (rt_uint32_t)arg;
    //hc32_mcan_config_t *hard = &driver->mcan;

    (void)cmd;
    RT_ASSERT(IS_RT_CAN_PRIV_MODE(argval));
    if (!IS_RT_CAN_PRIV_MODE(argval))
    {
        return -RT_ERROR;
    }
    if (argval == driver->can_device.config.privmode)
    {
        return -RT_EPERM;
    }
    cfg->privmode = argval;
    return RT_EOK;
}

static void mcan_copy_bt_to_cfg(struct can_configure *cfg, const stc_mcan_bit_time_config_t *ll_bt)
{
    cfg->can_timing.prescaler = ll_bt->u32NominalPrescaler;
    cfg->can_timing.num_seg1 = ll_bt->u32NominalTimeSeg1;
    cfg->can_timing.num_seg2 = ll_bt->u32NominalTimeSeg2;
    cfg->can_timing.num_sjw = ll_bt->u32NominalSyncJumpWidth;

    cfg->canfd_timing.prescaler = ll_bt->u32DataPrescaler;
    cfg->canfd_timing.num_seg1 = ll_bt->u32DataTimeSeg1;
    cfg->canfd_timing.num_seg2 = ll_bt->u32DataTimeSeg2;
    cfg->canfd_timing.num_sjw = ll_bt->u32DataSyncJumpWidth;
    cfg->canfd_timing.num_sspoff = ll_bt->u32SspOffset;
}

static rt_err_t mcan_control_set_fd(hc32_mcan_driver_t *driver, int cmd, void *arg, struct can_configure *cfg)
{
    rt_uint32_t i, len;
    rt_uint32_t argval = (rt_uint32_t)arg;
    //hc32_mcan_config_t *hard = &driver->mcan;

    switch (cmd)
    {
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_BAUD:
    default:
        RT_ASSERT(IS_MCAN_NOMINAL_BAUD_RATE(argval));
        if (!IS_MCAN_NOMINAL_BAUD_RATE(argval))
        {
            return -RT_ERROR;
        }
        if (driver->can_device.config.baud_rate == argval)
        {
            return -RT_EPERM;
        }
        len = sizeof(m_mcan_fd_baud_rate) / sizeof(m_mcan_fd_baud_rate[0]);
        for (i = 0; i < len; i++)
        {
            if ((argval == m_mcan_fd_baud_rate[i].baud_rate) && \
                    (driver->can_device.config.baud_rate_fd == m_mcan_fd_baud_rate[i].baud_rate_fd))
            {
                cfg->baud_rate = argval;
                cfg->baud_rate_fd = driver->can_device.config.baud_rate_fd;
                mcan_copy_bt_to_cfg(cfg, &m_mcan_cc_baud_rate[i].ll_bt);
                return RT_EOK;
            }
        }
        return -RT_ERROR;

    case RT_CAN_CMD_SET_BAUD_FD:
        RT_ASSERT(IS_MCAN_DATA_BAUD_RATE(argval));
        if (!IS_MCAN_DATA_BAUD_RATE(argval))
        {
            return -RT_ERROR;
        }
        if (driver->can_device.config.baud_rate_fd == argval)
        {
            return RT_EOK;
        }
        len = sizeof(m_mcan_fd_baud_rate) / sizeof(m_mcan_fd_baud_rate[0]);
        for (i = 0; i < len; i++)
        {
            if ((argval == m_mcan_fd_baud_rate[i].baud_rate_fd) && \
                    (driver->can_device.config.baud_rate == m_mcan_fd_baud_rate[i].baud_rate))
            {
                cfg->baud_rate_fd = argval;
                cfg->baud_rate = driver->can_device.config.baud_rate;
                mcan_copy_bt_to_cfg(cfg, &m_mcan_cc_baud_rate[i].ll_bt);
                return RT_EOK;
            }
        }
        return -RT_ERROR;

    case RT_CAN_CMD_SET_BITTIMING:
        struct rt_can_bit_timing_config *timing_configs = (struct rt_can_bit_timing_config *)arg;
        RT_ASSERT(timing_configs != RT_NULL);
        RT_ASSERT(timing_configs->count == 1 || timing_configs->count == 2);
        if ((timing_configs == NULL) || ((timing_configs->count != 1) && (timing_configs->count != 2)))
        {
            return -RT_ERROR;
        }
        cfg->can_timing = timing_configs->items[0];
        if (timing_configs->count == 2)
        {
            cfg->canfd_timing = timing_configs->items[1];
        }
        cfg->use_bit_timing = timing_configs->count;
        return RT_EOK;

    case RT_CAN_CMD_SET_CANFD:
        RT_ASSERT(IS_MCAN_FD_MODE(argval));
        if (!IS_MCAN_FD_MODE(argval))
        {
            return -RT_ERROR;
        }
        if (argval == driver->can_device.config.enable_canfd)
        {
            return -RT_EPERM;
        }
        cfg->enable_canfd = argval;
        return RT_EOK;
#else
    case RT_CAN_CMD_SET_BAUD:
        RT_ASSERT(IS_MCAN_CC_BAUD_RATE(argval));
        if (!IS_MCAN_CC_BAUD_RATE(argval))
        {
            return -RT_ERROR;
        }
        if (argval == driver->can_device.config.baud_rate)
        {
            return -RT_EPERM;
        }

        len = sizeof(m_mcan_cc_baud_rate) / sizeof(m_mcan_cc_baud_rate[0]);
        for (i = 0; i < len; i++)
        {
            if (argval == m_mcan_cc_baud_rate[i].baud_rate)
            {
                cfg->baud_rate = argval;
                return RT_EOK;
            }
        }
        return -RT_ERROR;
    default:
        return -RT_ERROR;
#endif
    }

    return -RT_ERROR;
}

static void mcan_control_get_status(hc32_mcan_driver_t *driver, int cmd, void *arg)
{
    stc_mcan_protocol_status_t mcan_st;
    stc_mcan_error_counter_t mcan_err;
    struct rt_can_status *rt_can_stat = (struct rt_can_status *)arg;

    MCAN_GetProtocolStatus(driver->mcan.instance, &mcan_st);
    MCAN_GetErrorCounter(driver->mcan.instance, &mcan_err);
    rt_can_stat->rcverrcnt = mcan_err.u8RxErrorCount;
    rt_can_stat->snderrcnt = mcan_err.u8TxErrorCount;
    rt_can_stat->lasterrtype = mcan_st.u8LastErrorCode;
    rt_can_stat->errcode = mcan_st.u8LastErrorCode;
}

static rt_err_t mcan_control(struct rt_can_device *device, int cmd, void *arg)
{
    rt_err_t rt_ret = -RT_ERROR;
    struct can_configure new_cfg;
    hc32_mcan_driver_t *driver;
    RT_ASSERT(device);
    driver = (hc32_mcan_driver_t *)device->parent.user_data;
    RT_ASSERT(driver);

    new_cfg = device->config;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SET_INT:
    case RT_DEVICE_CTRL_CLR_INT:
        mcan_control_set_int(driver, cmd, arg);
        return RT_EOK;

#if defined(RT_CAN_USING_HDR)
    case RT_CAN_CMD_SET_FILTER:
        rt_ret = mcan_control_set_filter(driver, cmd, arg);
        break;
#endif
    case RT_CAN_CMD_SET_MODE:
        rt_ret = mcan_control_set_mode(driver, cmd, arg, &new_cfg);
        break;

    case RT_CAN_CMD_SET_PRIV:
        rt_ret = mcan_control_set_priv(driver, cmd, arg, &new_cfg);
        break;

    case RT_CAN_CMD_SET_BAUD:
#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
    case RT_CAN_CMD_SET_BAUD_FD:
    case RT_CAN_CMD_SET_BITTIMING:
#endif
        rt_ret = mcan_control_set_fd(driver, cmd, arg, &new_cfg);
        break;

    case RT_CAN_CMD_GET_STATUS:
        mcan_control_get_status(driver, cmd, arg);
        return RT_EOK;

    default:
        return -RT_EINVAL;
    }

    if (rt_ret == RT_EOK)
    {
        rt_ret = mcan_configure(device, &new_cfg);
    }

    return rt_ret;
}

/****************************************************************************************
* mcan send message
****************************************************************************************/
static rt_ssize_t mcan_sendmsg(struct rt_can_device *device, const void *buf, rt_uint32_t boxno)
{
    hc32_mcan_driver_t *driver;
    hc32_mcan_config_t *hard;
    stc_mcan_tx_msg_t ll_tx_msg = {0};
    struct rt_can_msg *tx_msg;

    RT_ASSERT(device);
    driver = (hc32_mcan_driver_t *)device->parent.user_data;
    RT_ASSERT(driver);
    hard = &driver->mcan;

    driver->tx_box_num = boxno;

    RT_ASSERT(buf);
    tx_msg = (struct rt_can_msg *)buf;

    /* Parameter validity check */
    RT_ASSERT(IS_CAN_VALID_ID(tx_msg->ide, tx_msg->id));
#ifdef RT_CAN_USING_CANFD
    RT_ASSERT(tx_msg->len <= MCAN_DLC64);
#else
    RT_ASSERT(tx_msg->len <= MCAN_DLC8);
#endif

    /* rt CAN Tx message to MCAN LL driver Tx message */
    ll_tx_msg.ID  = tx_msg->id;
    ll_tx_msg.IDE = tx_msg->ide;
    ll_tx_msg.RTR = tx_msg->rtr;
    ll_tx_msg.DLC = tx_msg->len;
#ifdef RT_CAN_USING_CANFD
    ll_tx_msg.FDF = tx_msg->fd_frame;
    ll_tx_msg.BRS = tx_msg->brs;
#endif

    rt_memcpy(ll_tx_msg.au8Data, tx_msg->data, m_mcan_data_size[ll_tx_msg.DLC]);
    if (MCAN_AddMsgToTxFifoQueue(hard->instance, &ll_tx_msg) != LL_OK)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

/****************************************************************************************
* mcan receive message
****************************************************************************************/
static rt_ssize_t mcan_recvmsg(struct rt_can_device *device, void *buf, rt_uint32_t boxno)
{
    hc32_mcan_driver_t *driver;
    hc32_mcan_config_t *hard;
    stc_mcan_rx_msg_t ll_rx_msg = {0};
    struct rt_can_msg *rx_msg;
    rt_uint32_t rx_location;

    RT_ASSERT(device);
    driver = (hc32_mcan_driver_t *)device->parent.user_data;
    RT_ASSERT(driver);
    hard = &driver->mcan;

    RT_ASSERT(buf);
    rx_msg = (struct rt_can_msg *)buf;

    if (boxno == CAN_RX_FIFO0)
    {
        rx_location = MCAN_RX_FIFO0;
    }
    else if (boxno == CAN_RX_FIFO1)
    {
        rx_location = MCAN_RX_FIFO1;
    }
    else
    {
        rx_location = boxno;
    }
    if (MCAN_GetRxMsg(hard->instance, rx_location, &ll_rx_msg) != LL_OK)
    {
        rt_kprintf("No available message in the specified RX location.\n");
        return -(RT_ERROR);
    }

    /* MCAN LL driver Rx message to rt CAN Rx message */
    rx_msg->id   = ll_rx_msg.ID;
    rx_msg->ide  = ll_rx_msg.IDE;
    rx_msg->rtr  = ll_rx_msg.RTR;
    rx_msg->len  = ll_rx_msg.u32DataSize;
    rx_msg->priv = 0;
#ifdef RT_CAN_USING_HDR
    /* Hardware filter messages are valid */
    rx_msg->hdr_index = ll_rx_msg.u32FilterIndex;
    device->hdr[rx_msg->hdr_index].connected = 1;
#endif

#ifdef RT_CAN_USING_CANFD
    rx_msg->fd_frame = ll_rx_msg.FDF;
    rx_msg->brs      = ll_rx_msg.BRS;
#endif

    if (rx_msg->len > 0)
    {
        rt_memcpy(&rx_msg->data[0], &ll_rx_msg.au8Data[0], rx_msg->len);
    }

    return RT_EOK;
}

/****************************************************************************************
* mcan isr
****************************************************************************************/
static rt_uint32_t mcan_get_rx_buffer_num(rt_uint32_t new_data)
{
    rt_uint32_t num = 0;
    while (new_data)
    {
        new_data = new_data & (new_data - 1);
        num++;
    }
    return num++;
}

rt_inline void mcan_isr(hc32_mcan_driver_t *driver)
{
    struct rt_can_device *device = &driver->can_device;
    CM_MCAN_TypeDef *MCANx = driver->mcan.instance;
    uint32_t ir_status = MCANx->IR;
    uint32_t psr = MCANx->PSR;
    uint32_t ndat1 = MCANx->NDAT1;
    uint32_t ndat2 = MCANx->NDAT2;
    int rx_buf_index;

    MCAN_ClearStatus(MCANx, ir_status);

    /* Check normal status flag */
    /* Transmission completed */
    if (ir_status & MCAN_FLAG_TX_CPLT)
    {
        rt_hw_can_isr(device, RT_CAN_EVENT_TX_DONE | (driver->tx_box_num << 8U));
    }

    /* Rx FIFO0 new message */
    if (ir_status & MCAN_FLAG_RX_FIFO0_NEW_MSG)
    {
        if (MCAN_GetRxFifoFillLevel(MCANx, MCAN_RX_FIFO0) <= 1)
        {
            MCAN_ClearStatus(MCANx, MCAN_FLAG_RX_FIFO0_NEW_MSG);
        }
        rt_hw_can_isr(device, RT_CAN_EVENT_RX_IND | (MCAN_RX_FIFO0 << 8));
    }

    /* Rx FIFO1 new message */
    if (ir_status & MCAN_FLAG_RX_FIFO1_NEW_MSG)
    {
        if (MCAN_GetRxFifoFillLevel(MCANx, MCAN_RX_FIFO1) <= 1)
        {
            MCAN_ClearStatus(MCANx, MCAN_FLAG_RX_FIFO1_NEW_MSG);
        }
        rt_hw_can_isr(device, RT_CAN_EVENT_RX_IND | (MCAN_RX_FIFO1 << 8));
    }

    /* Rx Buffer new message */
    if (ir_status & MCAN_FLAG_RX_BUF_NEW_MSG)
    {
        /* Set an invalid index. Then find out the first Rx buffer that received new message. */
        rx_buf_index = -1;
        if (ndat1 > 0)
        {
            rx_buf_index = __CLZ(__RBIT(ndat1));
        }
        else if (ndat2 > 0)
        {
            rx_buf_index = __CLZ(__RBIT(ndat2)) + 32;
        }
        else
        {
            /* rsvd */
        }
        ndat1 = mcan_get_rx_buffer_num(ndat1);
        ndat2 = mcan_get_rx_buffer_num(ndat2);
        if ((ndat1 + ndat2) <= 1)
        {
            MCAN_ClearStatus(MCANx, MCAN_FLAG_RX_BUF_NEW_MSG);
        }
        rt_hw_can_isr(device, RT_CAN_EVENT_RX_IND | (rx_buf_index << 8));
    }

    /* Rx FIFO0 lost message, handle as rx overflow */
    if (ir_status & MCAN_FLAG_RX_FIFO0_MSG_LOST)
    {
        rt_hw_can_isr(device, RT_CAN_EVENT_RXOF_IND | (MCAN_RX_FIFO0 << 8));
    }

    /* Rx FIFO1 lost message, handle as rx overflow */
    if (ir_status & MCAN_FLAG_RX_FIFO1_MSG_LOST)
    {
        rt_hw_can_isr(device, RT_CAN_EVENT_RXOF_IND | (MCAN_RX_FIFO1 << 8));
    }

    /* Error occurred during transmitting. Handle as tx failure. */
    if ((psr & MCAN_PSR_ACT) == MCAN_PSR_ACT)
    {
#if defined(RT_CAN_USING_CANFD)
        if (ir_status & (MCAN_FLAG_ARB_PHASE_ERROR | MCAN_FLAG_DATA_PHASE_ERROR))
        {
            rt_hw_can_isr(device, RT_CAN_EVENT_TX_FAIL | (driver->tx_box_num << 8U));
        }
#else
        if (ir_status & MCAN_FLAG_ARB_PHASE_ERROR)
        {
            rt_hw_can_isr(device, RT_CAN_EVENT_TX_FAIL | (driver->tx_box_num << 8U));
        }
#endif
    }

    /* Check bus-off status flag */
    if (psr & MCAN_PSR_BO)
    {
        /* The node is in bus-off state. */
        /* If the device goes Bus_Off, it will set CCCR.INIT of its own accord, stopping all bus activities.
           The application should clear CCCR.INIT, then the device can resume normal operation.
           Once CCCR.INIT has been cleared by the CPU, the device will then wait for 129 occurrences of
           Bus Idle(129 * 11 consecutive recessive bits) before resuming normal operation. */
        MCAN_Start(MCANx);
    }
}

/****************************************************************************************
* mcan irq handler
****************************************************************************************/
#if defined(HC32F448)
#if defined(BSP_USING_MCAN1)
void MCAN1_INT0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    mcan_isr(&m_mcan_driver_list[MCAN1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

void MCAN1_INT1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    mcan_isr(&m_mcan_driver_list[MCAN1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* #if defined(BSP_USING_MCAN1) */

#if defined(BSP_USING_MCAN2)
void MCAN2_INT0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    mcan_isr(&m_mcan_driver_list[MCAN2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

void MCAN2_INT1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    mcan_isr(&m_mcan_driver_list[MCAN2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* #if defined(BSP_USING_MCAN2) */
#endif /* #if defined(HC32F448) IRQ handler */

/****************************************************************************************
* mcan initialization configurations
****************************************************************************************/
static void mcan_irq_config(hc32_mcan_config_t *hard)
{
#if defined(HC32F448)
    if (hard->int0_sel != 0)
    {
        INTC_IntSrcCmd(hard->int0_cfg.int_src, ENABLE);

        NVIC_ClearPendingIRQ(hard->int0_cfg.irq_num);
        NVIC_SetPriority(hard->int0_cfg.irq_num, hard->int0_cfg.irq_prio);
        NVIC_EnableIRQ(hard->int0_cfg.irq_num);
    }

    if (hard->int1_sel != 0)
    {
        INTC_IntSrcCmd(hard->int1_cfg.int_src, ENABLE);

        NVIC_ClearPendingIRQ(hard->int1_cfg.irq_num);
        NVIC_SetPriority(hard->int1_cfg.irq_num, hard->int1_cfg.irq_prio);
        NVIC_EnableIRQ(hard->int1_cfg.irq_num);
    }
#endif /* #if defined(HC32F448) mcan_irq_config */
}

static void mcan_enable_periph_clock(void)
{
#if defined(HC32F448)
#if defined(BSP_USING_MCAN1)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_MCAN1, ENABLE);
#endif
#if defined(BSP_USING_MCAN2)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_MCAN2, ENABLE);
#endif
#endif

#if defined(HC32F334)
#if defined(BSP_USING_MCAN1) || defined(BSP_USING_MCAN2)
    FCG_Fcg1PeriphClockCmd(FCG1_PERIPH_MCAN1 | FCG1_PERIPH_MCAN2, ENABLE);
#endif
#endif
}

static void mcan_set_init_para(void)
{
    struct rt_can_device *device;
    stc_mcan_init_t *hard_init;
#if defined(BSP_USING_MCAN1)
    device = &m_mcan_driver_list[MCAN1_INDEX].can_device;
    hard_init = &m_mcan_driver_list[MCAN1_INDEX].mcan.init_para;
    device->config.mode = MCAN1_WORK_MODE;
    device->config.privmode = MCAN1_TX_PRIV_MODE;
    device->config.baud_rate = MCAN1_NOMINAL_BAUD_RATE;
#if defined(RT_CAN_USING_HDR)
    device->config.maxhdr = MCAN_TOTAL_FILTER_NUM;
#endif
#if defined(RT_CAN_USING_CANFD)
    device->config.baud_rate_fd = MCAN1_DATA_BAUD_RATE;
    device->config.enable_canfd = MCAN1_FD_SEL;
    hard_init->u32FrameFormat = m_mcan_fd_mode[MCAN1_FD_SEL];
#else
    hard_init->u32FrameFormat = MCAN_FRAME_CLASSIC;
#endif
    hard_init->u32Mode              = m_mcan_work_mode[device->config.mode];
    hard_init->u32AutoRetx          = MCAN_AUTO_RETX_ENABLE;
    hard_init->u32TxPause           = MCAN_TX_PAUSE_DISABLE;
    hard_init->u32ProtocolException = MCAN_PROTOCOL_EXP_ENABLE;
    /* Message RAM */
    hard_init->stcMsgRam.u32AddrOffset        = 0U;
    hard_init->stcMsgRam.u32StdFilterNum      = MCAN1_STD_FILTER_NUM;
    hard_init->stcMsgRam.u32ExtFilterNum      = MCAN1_EXT_FILTER_NUM;
    hard_init->stcMsgRam.u32RxFifo0Num        = MCAN1_RX_FIFO0_NUM;
    hard_init->stcMsgRam.u32RxFifo0DataSize   = MCAN1_RX_FIFO0_DATA_FIELD_SIZE;
    hard_init->stcMsgRam.u32RxFifo1Num        = 0U;
    hard_init->stcMsgRam.u32RxFifo1DataSize   = 0U;
    hard_init->stcMsgRam.u32RxBufferNum       = 0U;
    hard_init->stcMsgRam.u32RxBufferDataSize  = 0U;
    hard_init->stcMsgRam.u32TxEventNum        = 0U;
    hard_init->stcMsgRam.u32TxBufferNum       = 0U;
    hard_init->stcMsgRam.u32TxFifoQueueNum    = MCAN1_TX_FIFO_NUM;
    hard_init->stcMsgRam.u32TxFifoQueueMode   = m_mcan_tx_priv_mode[device->config.privmode];
    hard_init->stcMsgRam.u32TxDataSize        = MCAN1_TX_FIFO_DATA_FIELD_SIZE;
    /* Acceptance filter */
    hard_init->stcFilter.pstcStdFilterList     = m_mcan1_std_filters;
    hard_init->stcFilter.pstcExtFilterList     = m_mcan1_ext_filters;
    hard_init->stcFilter.u32StdFilterConfigNum = hard_init->stcMsgRam.u32StdFilterNum;
    hard_init->stcFilter.u32ExtFilterConfigNum = hard_init->stcMsgRam.u32ExtFilterNum;

#endif
#if defined(BSP_USING_MCAN2)
    device = &m_mcan_driver_list[MCAN2_INDEX].can_device;
    hard_init = &m_mcan_driver_list[MCAN2_INDEX].mcan.init_para;
    device->config.mode = MCAN2_WORK_MODE;
    device->config.privmode = MCAN2_TX_PRIV_MODE;
    device->config.baud_rate = MCAN2_NOMINAL_BAUD_RATE;
#if defined(RT_CAN_USING_HDR)
    device->config.maxhdr = MCAN_TOTAL_FILTER_NUM;
#endif
#if defined(RT_CAN_USING_CANFD)
    device->config.baud_rate_fd = MCAN2_DATA_BAUD_RATE;
    device->config.enable_canfd = MCAN2_FD_SEL;
    hard_init->u32FrameFormat = m_mcan_fd_mode[MCAN2_FD_SEL];
#else
    hard_init->u32FrameFormat = MCAN_FRAME_CLASSIC;
#endif
    hard_init->u32Mode              = m_mcan_work_mode[device->config.mode];
    hard_init->u32AutoRetx          = MCAN_AUTO_RETX_ENABLE;
    hard_init->u32TxPause           = MCAN_TX_PAUSE_DISABLE;
    hard_init->u32ProtocolException = MCAN_PROTOCOL_EXP_ENABLE;
    /* Message RAM */
    hard_init->stcMsgRam.u32AddrOffset        = 0U;
    hard_init->stcMsgRam.u32StdFilterNum      = MCAN2_STD_FILTER_NUM;
    hard_init->stcMsgRam.u32ExtFilterNum      = MCAN2_EXT_FILTER_NUM;
    hard_init->stcMsgRam.u32RxFifo0Num        = MCAN2_RX_FIFO0_NUM;
    hard_init->stcMsgRam.u32RxFifo0DataSize   = MCAN2_RX_FIFO0_DATA_FIELD_SIZE;
    hard_init->stcMsgRam.u32RxFifo1Num        = 0U;
    hard_init->stcMsgRam.u32RxFifo1DataSize   = 0U;
    hard_init->stcMsgRam.u32RxBufferNum       = 0U;
    hard_init->stcMsgRam.u32RxBufferDataSize  = 0U;
    hard_init->stcMsgRam.u32TxEventNum        = 0U;
    hard_init->stcMsgRam.u32TxBufferNum       = 0U;
    hard_init->stcMsgRam.u32TxFifoQueueNum    = MCAN2_TX_FIFO_NUM;
    hard_init->stcMsgRam.u32TxFifoQueueMode   = m_mcan_tx_priv_mode[device->config.privmode];
    hard_init->stcMsgRam.u32TxDataSize        = MCAN2_TX_FIFO_DATA_FIELD_SIZE;
    /* Acceptance filter */
    hard_init->stcFilter.pstcStdFilterList     = m_mcan2_std_filters;
    hard_init->stcFilter.pstcExtFilterList     = m_mcan2_ext_filters;
    hard_init->stcFilter.u32StdFilterConfigNum = hard_init->stcMsgRam.u32StdFilterNum;
    hard_init->stcFilter.u32ExtFilterConfigNum = hard_init->stcMsgRam.u32ExtFilterNum;
#endif
}

static void init_can_cfg(hc32_mcan_driver_t *driver)
{
    struct can_configure can_cfg = CANDEFAULTCONFIG;

    can_cfg.privmode = RT_CAN_MODE_NOPRIV;
    can_cfg.ticks = 50;
#ifdef RT_CAN_USING_HDR
    can_cfg.maxhdr = MCAN_TOTAL_FILTER_NUM;
#endif
#ifdef RT_CAN_USING_CANFD
    can_cfg.baud_rate_fd = MCANFD_DATA_BAUD_4M;
    can_cfg.enable_canfd = MCAN_FD_ISO_FD_NO_BRS;
#endif
    can_cfg.sndboxnumber = MCAN_TX_FIFO_NUM;
    driver->can_device.config = can_cfg;
}

extern rt_err_t rt_hw_board_can_init(CM_MCAN_TypeDef *MCANx);
extern void CanPhyEnable(void);
static rt_err_t rt_hw_mcan_init(void)
{
    rt_uint32_t i;
    rt_uint32_t tx_boxnum;
    hc32_mcan_config_t *hard;

    mcan_enable_periph_clock();
    mcan_set_init_para();

    for (i = 0; i < MCAN_DEV_CNT; i++)
    {
        hard = &m_mcan_driver_list[i].mcan;

        /* MCAN IRQ configuration */
        mcan_irq_config(hard);

        MCAN_Init(hard->instance, &hard->init_para);

        tx_boxnum = hard->init_para.stcMsgRam.u32TxBufferNum + hard->init_para.stcMsgRam.u32TxFifoQueueNum;
        if (tx_boxnum >= 32)
        {
            tx_boxnum = 0xFFFFFFFF;
        }
        else
        {
            tx_boxnum = (1UL << tx_boxnum) - 1;
        }

        MCAN_TxBufferNotificationCmd(hard->instance, tx_boxnum, MCAN_INT_TX_CPLT, ENABLE);
        MCAN_IntCmd(hard->instance, hard->int0_sel, MCAN_INT_LINE0, ENABLE);
        MCAN_IntCmd(hard->instance, hard->int1_sel, MCAN_INT_LINE1, ENABLE);

        if (i > 0)
        {
            hard->init_para.stcMsgRam.u32AddrOffset = \
                    m_mcan_driver_list[i - 1].mcan.init_para.stcMsgRam.u32AddrOffset + \
                    m_mcan_driver_list[i - 1].mcan.init_para.stcMsgRam.u32AllocatedSize;
        }

        init_can_cfg(&m_mcan_driver_list[i]);

        /* GPIO initialization */
        rt_hw_board_can_init(hard->instance);

        /* Register CAN device */
        rt_hw_can_register(&m_mcan_driver_list[i].can_device,
                           hard->name,
                           &m_mcan_ops,
                           &m_mcan_driver_list[i]);

        MCAN_Start(hard->instance);
    }

    /* Onboard CAN transceiver enable */
    CanPhyEnable();

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_mcan_init);
#endif

#endif /* BSP_USING_MCAN */

/************************** end of file ******************/

