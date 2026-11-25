/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-02-27     yeml           the first version
 */

#define RT_USING_CAN
#ifdef RT_USING_CAN

#include "drv_can.h"

enum
{
#ifdef BSP_USING_CAN0
    CAN0_INDEX,
#endif
#ifdef BSP_USING_CAN1
    CAN1_INDEX,
#endif
    CAN_INDEX_MAX
};


#define BSP_USING_CAN0
static struct tae32_can can_obj[CAN_INDEX_MAX] =
{
#ifdef BSP_USING_CAN0
    {
        .name = "can0",
        .Instance = CAN0,
    }
#endif

#ifdef BSP_USING_CAN1
    {
        .name = "can1",
        .Instance = CAN1,
    }
#endif
};


#define CAN_FILTER_COUNT (CAN_ACCEPT_FILT_SLOT_NUMS)

struct tae32_can_bit_timing
{
    rt_uint8_t prescaler;
    rt_uint8_t num_seg1;
    rt_uint8_t num_seg2;
    rt_uint8_t num_sjw;
};

struct tae32_baud_rate_tab
{
    rt_uint32_t baud_rate;
    struct tae32_can_bit_timing bit_timing;
};

static const struct tae32_baud_rate_tab can_baud_rate_tab[] =
{
    {CAN1MBaud,   CAN_BIT_TIME_CONFIG_1M_BAUD  },
    {CAN800kBaud, CAN_BIT_TIME_CONFIG_800K_BAUD},
    {CAN500kBaud, CAN_BIT_TIME_CONFIG_500K_BAUD},
    {CAN250kBaud, CAN_BIT_TIME_CONFIG_250K_BAUD},
    {CAN125kBaud, CAN_BIT_TIME_CONFIG_125K_BAUD},
    {CAN100kBaud, CAN_BIT_TIME_CONFIG_100K_BAUD},
    {CAN50kBaud,  CAN_BIT_TIME_CONFIG_50K_BAUD },
    {CAN20kBaud,  CAN_BIT_TIME_CONFIG_20K_BAUD },
    {CAN10kBaud,  CAN_BIT_TIME_CONFIG_10K_BAUD },
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

static rt_err_t tae32_can_filter_reset(struct rt_can_device *can)
{
    struct tae32_can *pCanObj;
    pCanObj = rt_container_of(can, struct tae32_can, rt_can);

    for (rt_uint8_t i = 0; i < CAN_FILTER_COUNT; i++)
    {
        /* CAN acceptance filter Code and Mask config */
        __LL_CAN_AcceptFilAddr_Set(pCanObj->Instance, i);
        __LL_CAN_AcceptFilContentSel_Mask(pCanObj->Instance);
        __LL_CAN_AcceptFilCodeOrMaskVal_Set(pCanObj->Instance, 0);
        __LL_CAN_AcceptFilRxFrm_Set(pCanObj->Instance, CAN_ACCEPT_FILT_FRM_STD_EXT);
        __LL_CAN_AcceptFilContentSel_Code(pCanObj->Instance);
        __LL_CAN_AcceptFilCodeOrMaskVal_Set(pCanObj->Instance, 0);

        __LL_CAN_AcceptMode_Set(pCanObj->Instance, CAN_ACCEPT_MODE_AND);
        __LL_CAN_AcceptCtrl_Set(pCanObj->Instance, CAN_ACCEPT_CTRL_STORE_PRB);

        /* CAN acceptance filter disable */
        __LL_CAN_AcceptFil_Dis(pCanObj->Instance, ((uint8_t)i));
    }
}

static rt_err_t tae32_can_filter_cfg(struct rt_can_device *can)
{
    struct tae32_can *pCanObj;
    pCanObj = rt_container_of(can, struct tae32_can, rt_can);
    for (rt_uint8_t i = 0; i < pCanObj->config.accept_fil_cfg_num; i++)
    {
        /* CAN acceptance filter Code and Mask config */
        __LL_CAN_AcceptFilAddr_Set(pCanObj->Instance, pCanObj->config.accept_fil_cfg_ptr[i].slot);
        __LL_CAN_AcceptFilContentSel_Mask(pCanObj->Instance);
        __LL_CAN_AcceptFilCodeOrMaskVal_Set(pCanObj->Instance, pCanObj->config.accept_fil_cfg_ptr[i].mask_val);
        __LL_CAN_AcceptFilRxFrm_Set(pCanObj->Instance, pCanObj->config.accept_fil_cfg_ptr[i].rx_frm);
        __LL_CAN_AcceptFilContentSel_Code(pCanObj->Instance);
        __LL_CAN_AcceptFilCodeOrMaskVal_Set(pCanObj->Instance, pCanObj->config.accept_fil_cfg_ptr[i].code_val);

        __LL_CAN_AcceptMode_Set(pCanObj->Instance, CAN_ACCEPT_MODE_AND);
        __LL_CAN_AcceptCtrl_Set(pCanObj->Instance, CAN_ACCEPT_CTRL_STORE_PRB);

        /* CAN acceptance filter enable */
        __LL_CAN_AcceptFil_En(pCanObj->Instance, ((uint8_t)pCanObj->config.accept_fil_cfg_ptr[i].slot));
    }
}


static LL_StatusETypeDef ll_can_transmitPTB(CAN_TypeDef *Instance, CAN_TxBufFormatTypeDef *buf_fmt, uint32_t *buf)
{
    uint8_t dat_len;

    assert_param(IS_CAN_ALL_INSTANCE(Instance));
    assert_param(buf_fmt != NULL);

    /* Check last frame transmit complete or not */
    if (__LL_CAN_TxPriEn_Get(Instance))
    {
        return LL_ERROR;
    }

    /* TX buffer select PTB*/
    __LL_CAN_TxBufSel_PTB(Instance);

    /* Write buffer format data */
    __LL_CAN_TxBufReg_ID_Write(Instance, *((uint32_t *)buf_fmt));
    __LL_CAN_TxBufReg_Ctrl_Write(Instance, *(((uint32_t *)buf_fmt) + 1));

    /* Write data to TX buffer */
    if (buf != NULL)
    {
        dat_len = LL_CAN_DatLen_Get(Instance, buf_fmt->data_len_code);

        for (uint32_t i = 0; i < (dat_len + 3) / 4; i++)
        {
            __LL_CAN_TxBufReg_Data_Write(Instance, i, *buf++);
        }
    }
    /* TX primary enable */
    __LL_CAN_TxPriEn_Set(Instance);

    return LL_OK;
}

static  rt_err_t tae32_can_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    struct tae32_can *pCanObj;
    rt_uint32_t baud_ss_index;
    rt_uint32_t baud_fs_index;
    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    CAN_UserCfgTypeDef can_init;
    rt_memset(&can_init, 0, sizeof(can_init));

    pCanObj = rt_container_of(can, struct tae32_can, rt_can);

    LL_CAN_MspInit(pCanObj->Instance);
    __LL_CAN_Reset_Set(pCanObj->Instance);
    __LL_CAN_AllIntLine_Clr(pCanObj->Instance);

    baud_ss_index = get_can_baud_index(cfg->baud_rate);

    pCanObj->config.func_clk_freq = CAN_CLOCK;
    pCanObj->config.baudrate_ss = can_baud_rate_tab[baud_ss_index].baud_rate;
    pCanObj->config.bit_timing_seg1_ss = can_baud_rate_tab[baud_ss_index].bit_timing.num_seg1;
    pCanObj->config.bit_timing_seg2_ss = can_baud_rate_tab[baud_ss_index].bit_timing.num_seg2;
    pCanObj->config.bit_timing_sjw_ss = can_baud_rate_tab[baud_ss_index].bit_timing.num_sjw;

    baud_ss_index = get_can_baud_index(cfg->baud_rate);
    __LL_CAN_SS_Prescaler_Set(pCanObj->Instance, can_baud_rate_tab[baud_ss_index].bit_timing.prescaler - 1);
    __LL_CAN_SS_BitTimingSeg1_Set(pCanObj->Instance, pCanObj->config.bit_timing_seg1_ss);
    __LL_CAN_SS_BitTimingSeg2_Set(pCanObj->Instance, pCanObj->config.bit_timing_seg2_ss);
    __LL_CAN_SS_SyncJumpWidth_Set(pCanObj->Instance, pCanObj->config.bit_timing_sjw_ss);

    pCanObj->config.fd_en = 0;
    can_init.fd_iso_en = 0;
    __LL_CAN_FD_Dis(pCanObj->Instance);
    __LL_CAN_FD_ISO_Dis(pCanObj->Instance);

#ifdef RT_CAN_USING_CANFD

    if (cfg->enable_canfd)
    {
        pCanObj->config.fd_en = 1;
        __LL_CAN_FD_En(pCanObj->Instance);

#ifdef BSP_USING_CAN0
        if ((CAN0_CAN_FD_MODE) && (pCanObj->Instance == CAN0))
        {
            pCanObj->config.fd_iso_en = 1;
            __LL_CAN_FD_ISO_En(pCanObj->Instance);
        }
#endif
#ifdef BSP_USING_CAN1
        if ((CAN1_CAN_FD_MODE) && (pCanObj->Instance == CAN1))
        {
            pCanObj->config.fd_iso_en = 1;
            __LL_CAN_FD_ISO_En(pCanObj->Instance);
        }
#endif
        if (pCanObj->rt_can.config.use_bit_timing)
        {
            pCanObj->config.baudrate_ss = cfg->baud_rate;
            pCanObj->config.bit_timing_seg1_ss = cfg->can_timing.num_seg1;
            pCanObj->config.bit_timing_seg2_ss = cfg->can_timing.num_seg2;
            pCanObj->config.bit_timing_sjw_ss = cfg->can_timing.num_sjw;

            pCanObj->config.baudrate_fs = cfg->baud_rate_fd;
            pCanObj->config.bit_timing_seg1_fs = cfg->canfd_timing.num_seg1;
            pCanObj->config.bit_timing_seg2_fs = cfg->canfd_timing.num_seg2;
            pCanObj->config.bit_timing_sjw_fs = cfg->canfd_timing.num_sjw;

            __LL_CAN_SS_Prescaler_Set(pCanObj->Instance, cfg->can_timing.prescaler - 1);
            __LL_CAN_FS_Prescaler_Set(pCanObj->Instance, cfg->canfd_timing.prescaler - 1);
        }
        else
        {
            baud_ss_index = get_can_baud_index(cfg->baud_rate);
            pCanObj->config.baudrate_ss = can_baud_rate_tab[baud_ss_index].baud_rate;
            pCanObj->config.bit_timing_seg1_ss = can_baud_rate_tab[baud_ss_index].bit_timing.num_seg1;
            pCanObj->config.bit_timing_seg2_ss = can_baud_rate_tab[baud_ss_index].bit_timing.num_seg2;
            pCanObj->config.bit_timing_sjw_ss = can_baud_rate_tab[baud_ss_index].bit_timing.num_sjw;
            __LL_CAN_SS_Prescaler_Set(pCanObj->Instance, can_baud_rate_tab[baud_ss_index].bit_timing.prescaler - 1);

            baud_fs_index = get_can_baud_index(cfg->baud_rate_fd);
            pCanObj->config.baudrate_fs = can_baud_rate_tab[baud_fs_index].baud_rate;
            pCanObj->config.bit_timing_seg1_fs = can_baud_rate_tab[baud_fs_index].bit_timing.num_seg1;
            pCanObj->config.bit_timing_seg2_fs = can_baud_rate_tab[baud_fs_index].bit_timing.num_seg2;
            pCanObj->config.bit_timing_sjw_fs = can_baud_rate_tab[baud_fs_index].bit_timing.num_sjw;
            __LL_CAN_FS_Prescaler_Set(pCanObj->Instance, can_baud_rate_tab[baud_fs_index].bit_timing.prescaler - 1);
        }
        __LL_CAN_SS_BitTimingSeg1_Set(pCanObj->Instance, pCanObj->config.bit_timing_seg1_ss);
        __LL_CAN_SS_BitTimingSeg2_Set(pCanObj->Instance, pCanObj->config.bit_timing_seg2_ss);
        __LL_CAN_SS_SyncJumpWidth_Set(pCanObj->Instance, pCanObj->config.bit_timing_sjw_ss);
        __LL_CAN_FS_BitTimingSeg1_Set(pCanObj->Instance, pCanObj->config.bit_timing_seg1_fs);
        __LL_CAN_FS_BitTimingSeg2_Set(pCanObj->Instance, pCanObj->config.bit_timing_seg2_fs);
        __LL_CAN_FS_SyncJumpWidth_Set(pCanObj->Instance, pCanObj->config.bit_timing_sjw_fs);

#endif
        switch (cfg->mode)
        {
        case RT_CAN_MODE_NORMAL:
            __LL_CAN_ListenOnlyMode_Dis(pCanObj->Instance);
            __LL_CAN_LoopBackModeInternal_Dis(pCanObj->Instance);
            __LL_CAN_LoopBackModeExt_Dis(pCanObj->Instance);
            break;

        case RT_CAN_MODE_LISTEN:
            __LL_CAN_ListenOnlyMode_En(pCanObj->Instance);
            __LL_CAN_LoopBackModeInternal_Dis(pCanObj->Instance);
            __LL_CAN_LoopBackModeExt_Dis(pCanObj->Instance);

            break;
        case RT_CAN_MODE_LOOPBACK:
            __LL_CAN_LoopBackModeInternal_En(pCanObj->Instance);
            __LL_CAN_ListenOnlyMode_Dis(pCanObj->Instance);
            __LL_CAN_LoopBackModeExt_Dis(pCanObj->Instance);
            break;

        case RT_CAN_MODE_LOOPBACKANLISTEN:
            __LL_CAN_LoopBackModeExt_En(pCanObj->Instance);
            __LL_CAN_ListenOnlyMode_Dis(pCanObj->Instance);
            __LL_CAN_LoopBackModeInternal_Dis(pCanObj->Instance);
            break;
        }
    }
    __LL_CAN_Reset_Clr(pCanObj->Instance);
    return RT_EOK;
}

rt_err_t tae32_can_control(struct rt_can_device * can, int cmd, void *arg)
{
    rt_uint32_t argval;
    struct tae32_can *pCanObj;
    struct rt_can_filter_config *pFilterCfg = (struct rt_can_filter_config *)arg;
    struct rt_can_bit_timing_config *timing_configs = (struct rt_can_bit_timing_config*)argval;

    CAN_AcceptFilCfgTypeDef can_acpt_fil_cfg[CAN_FILTER_COUNT];

    RT_ASSERT(can != RT_NULL);
    pCanObj = rt_container_of(can, struct tae32_can, rt_can);
    RT_ASSERT(pCanObj != RT_NULL);
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t) arg;
        if (0 == pCanObj->intOpenCnt)
        {
            if (pCanObj->Instance == CAN0)
            {
                LL_NVIC_DisableIRQ(CAN0_IRQn);
            }
#ifdef BSP_USING_CAN1
            if (pCanObj->Instance == CAN1)
            {
                LL_NVIC_DisableIRQ(CAN1_IRQn);
            }
#endif
        }

        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            pCanObj->intOpenCnt &= ~(1 << 0);
            __LL_CAN_Rx_INT_Dis(pCanObj->Instance);
            __LL_CAN_RxBufOver_INT_Dis(pCanObj->Instance);
            __LL_CAN_RxBufFull_INT_Dis(pCanObj->Instance);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            pCanObj->intOpenCnt &= ~(1 << 1);
            __LL_CAN_TxPri_INT_En(pCanObj->Instance);
        }

        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            pCanObj->intOpenCnt &= ~(1 << 2);
            __LL_CAN_Err_INT_Dis(pCanObj->Instance);
            __LL_CAN_ArbLost_INT_Dis(pCanObj->Instance);
            __LL_CAN_ErrPassive_INT_Dis(pCanObj->Instance);
            __LL_CAN_BusErr_INT_Dis(pCanObj->Instance);
        }
        break;
    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t) arg;

        if (0 == pCanObj->intOpenCnt)
        {
            if (pCanObj->Instance == CAN0)
            {
                pCanObj->Instance->INTRLS = 0;
                LL_NVIC_EnableIRQ(CAN0_IRQn);
            }
#ifdef BSP_USING_CAN1
            if (pCanObj->Instance == CAN1)
            {
                pCanObj->Instance->INTRLS = 0;
                LL_NVIC_EnableIRQ(CAN1_IRQn);
            }
#endif
        }

        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            pCanObj->intOpenCnt |= (1 << 0);
            __LL_CAN_Rx_INT_En(pCanObj->Instance);
            __LL_CAN_RxBufOver_INT_En(pCanObj->Instance);
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            pCanObj->intOpenCnt |= (1 << 1);
            __LL_CAN_TxPri_INT_En(pCanObj->Instance); /* PTB */
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            pCanObj->intOpenCnt |= (1 << 2);
            __LL_CAN_Err_INT_En(pCanObj->Instance);
            __LL_CAN_ArbLost_INT_En(pCanObj->Instance);
            __LL_CAN_ErrPassive_INT_En(pCanObj->Instance);
            __LL_CAN_BusErr_INT_En(pCanObj->Instance);
        }
        break;

    case  RT_CAN_CMD_SET_FILTER:
        rt_memset(can_acpt_fil_cfg, 0, sizeof(can_acpt_fil_cfg));
        if (pFilterCfg->count > CAN_FILTER_COUNT)
        {
            return RT_FALSE;
        }

        for (rt_size_t i = 0; i < pFilterCfg->count; i++)
        {
            if (pFilterCfg->items[i].hdr_bank != -1)
            {
                can_acpt_fil_cfg[i].slot = pFilterCfg->items[i].hdr_bank;
            }
            else
            {
                can_acpt_fil_cfg[i].slot = i;

            }
            can_acpt_fil_cfg[i].code_val = pFilterCfg->items[i].id;

            /* tae32 CAN mask, 0 mean filter, 1 mean ignore. */
            if (pFilterCfg->items[i].mode)
            {
                /* rtt can device filter list mode */
                can_acpt_fil_cfg[i].mask_val = 0;
            }
            else
            {
                /* rtt can device filter mask mode，mask=0 mean ignore, mask=1 mean filter */
                can_acpt_fil_cfg[i].mask_val = (~pFilterCfg->items[i].mask) & 0x1FFFFFFF;
            }

            switch (pFilterCfg->items[i].ide)
            {
            case RT_CAN_STDID:
                can_acpt_fil_cfg[i].rx_frm = CAN_ACCEPT_FILT_FRM_STD;
                break;
            case RT_CAN_EXTID:
                can_acpt_fil_cfg[i].rx_frm = CAN_ACCEPT_FILT_FRM_EXT;
                break;
            }
        }
        pCanObj->config.accept_fil_cfg_ptr = can_acpt_fil_cfg;
        pCanObj->config.accept_fil_cfg_num = pFilterCfg->count;

        tae32_can_filter_reset(can);
        tae32_can_filter_cfg(can);
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
        if (argval != pCanObj->rt_can.config.mode)
        {
            pCanObj->rt_can.config.mode = argval;
            return tae32_can_configure(&pCanObj->rt_can, &pCanObj->rt_can.config);
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
        if (argval != pCanObj->rt_can.config.baud_rate)
        {
            pCanObj->rt_can.config.baud_rate = argval;
            return tae32_can_configure(&pCanObj->rt_can, &pCanObj->rt_can.config);
        }
        break;

#ifdef RT_CAN_USING_CANFD
    case RT_CAN_CMD_SET_CANFD:
        argval = (uint32_t) arg;
        if (argval != pCanObj->rt_can.config.enable_canfd)
        {
            pCanObj->rt_can.config.enable_canfd = argval;
            tae32_can_configure(can, &pCanObj->rt_can.config);
        }
        break;
    case RT_CAN_CMD_SET_BAUD_FD:
        argval = (uint32_t) arg;
        if (argval != pCanObj->rt_can.config.baud_rate_fd)
        {
            pCanObj->rt_can.config.baud_rate_fd = argval;
            tae32_can_configure(can, &pCanObj->rt_can.config);
        }
        break;
    case RT_CAN_CMD_SET_BITTIMING:

        if ((timing_configs == RT_NULL) || (timing_configs->count < 1) || (timing_configs->count > 2))
        {
            return -RT_ERROR;
        }
        if (timing_configs->count != 0U)
        {
            pCanObj->rt_can.config.can_timing = timing_configs->items[0];
        }
        if (timing_configs->count == 2)
        {
            pCanObj->rt_can.config.canfd_timing = timing_configs->items[1];
        }
        tae32_can_configure(can, &pCanObj->rt_can.config);
        break;
#endif
    case RT_CAN_CMD_SET_PRIV:
        pCanObj->rt_can.config.privmode = argval;
        break;
    case RT_CAN_CMD_GET_STATUS:
        pCanObj->rt_can.status.rcverrcnt = __LL_CAN_RxErrCnt_Get(pCanObj->Instance);
        pCanObj->rt_can.status.snderrcnt = __LL_CAN_TxErrCnt_Get(pCanObj->Instance);
        pCanObj->rt_can.status.lasterrtype = __LL_CAN_ErrCode_Get(pCanObj->Instance);
        pCanObj->rt_can.status.errcode = 0;
        if (__LL_CAN_IsErrWarnLimitReached(pCanObj->Instance))
        {
            pCanObj->rt_can.status.errcode |= ERRWARNING;
        }
        if (__LL_CAN_IsErrPassiveModeActive(pCanObj->Instance))
        {
            pCanObj->rt_can.status.errcode |= ERRPASSIVE;
        }
        if (__LL_CAN_IsBusOff(pCanObj->Instance))
        {
            pCanObj->rt_can.status.errcode |= BUSOFF;
        }
        rt_memcpy(arg, &pCanObj->rt_can.status, sizeof(pCanObj->rt_can.status));
        break;

        /* case RT_CAN_CMD_START:break; */
    }
    return RT_EOK;
}

static rt_ssize_t tae32_can_sendmsg(struct rt_can_device * can, const void *buf, rt_uint32_t boxno)
{
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    struct tae32_can *pCanObj;

    CAN_TxBufFormatTypeDef buf_fmt;

    RT_ASSERT(can != RT_NULL);
    pCanObj = rt_container_of(can, struct tae32_can, rt_can);
    RT_ASSERT(pCanObj != RT_NULL);

    rt_memset((void *)(&buf_fmt), 0, sizeof(buf_fmt));

    /* Set up the Id */
    buf_fmt.id = pmsg->id;

    /* Set up the IDE */
    buf_fmt.id_extension = pmsg->ide;

    buf_fmt.remote_tx_req = pmsg->rtr;

#ifdef RT_CAN_USING_CANFD
    if (pmsg->fd_frame != 0)
    {
        RT_ASSERT(pmsg->len <= 64);
    }
    else
    {
        RT_ASSERT(pmsg->len <= 8);
    }

    buf_fmt.bit_rate_switch = pmsg->brs;
    buf_fmt.extended_data_len = pmsg->fd_frame;

#endif
    /* Set up the DLC */
    buf_fmt.data_len_code = LL_CAN_DatLenCode_Get(pCanObj->Instance, pmsg->len);

    /* Request transmission */
    if (ll_can_transmitPTB(pCanObj->Instance, &buf_fmt, (rt_uint32_t *)pmsg->data) != LL_OK)
    {
        return RT_ERROR;
    }

    return RT_EOK;
}

static rt_ssize_t tae32_can_recvmsg(struct rt_can_device * can, void *buf, rt_uint32_t fifo)
{
    struct rt_can_msg *pmsg = (struct rt_can_msg *) buf;
    struct tae32_can *pCanObj;

    CAN_RxBufFormatTypeDef buf_fmt;

    RT_ASSERT(can != RT_NULL);
    pCanObj = rt_container_of(can, struct tae32_can, rt_can);
    RT_ASSERT(pCanObj != RT_NULL);

    *((uint32_t *)(&buf_fmt) + 0) = __LL_CAN_RxBufReg_ID_Read(pCanObj->Instance);
    *((uint32_t *)(&buf_fmt) + 1) = __LL_CAN_RxBufReg_Ctrl_Read(pCanObj->Instance);

    if (&(pmsg->data) != NULL)
    {
        rt_memcpy((void *)pmsg->data, (void *)pCanObj->Instance->RBUFDT, LL_CAN_DatLen_Get(pCanObj->Instance, buf_fmt.data_len_code));
    }
    /* RxFIFO Release(Clear) */
    __LL_CAN_RxBufRelease(pCanObj->Instance);

    /* get id */
    if (0 == buf_fmt.id_extension)
    {
        pmsg->ide = RT_CAN_STDID;
    }
    else
    {
        pmsg->ide = RT_CAN_EXTID;
    }
    pmsg->id = buf_fmt.id;

    /* get type */
    if (0 == buf_fmt.remote_tx_req)
    {
        pmsg->rtr = RT_CAN_DTR;
    }
    else
    {
        pmsg->rtr = RT_CAN_RTR;
    }

#ifdef RT_CAN_USING_CANFD
    pmsg->fd_frame = buf_fmt.extended_data_len;
    pmsg->brs = buf_fmt.bit_rate_switch;
#endif
    /* get len */
    pmsg->len = LL_CAN_DatLen_Get(pCanObj->Instance, buf_fmt.data_len_code);

    /* get hdr_index */
    pmsg->hdr_index = buf_fmt.acceptance_data;
    pCanObj->rt_can.hdr[pmsg->hdr_index].connected = 1;

    return RT_EOK;
}

static void tae32_can_isr(struct rt_can_device * can)
{
    struct tae32_can *pCanObj;
    uint32_t int_en, int_pending;

    RT_ASSERT(can != RT_NULL);

    pCanObj = rt_container_of(can, struct tae32_can, rt_can);
    RT_ASSERT(pCanObj != RT_NULL);

    /* All Interrupt Enalbe and Pending Get */
    int_en = __LL_CAN_AllIntEn_Get(pCanObj->Instance);
    int_pending = __LL_CAN_AllIntPnd_Get(pCanObj->Instance);


    /* Rx Interrupt Handler */
    if ((int_en & CAN0_INTREN_RIE_Msk) && (int_pending & CAN0_INTRST_RIF_Msk))
    {
        __LL_CAN_RxIntPnd_Clr(pCanObj->Instance);
        rt_hw_can_isr(&pCanObj->rt_can, RT_CAN_EVENT_RX_IND | (0UL << 8));
    }

    /* Rx Overrun Interrupt Handler */
    if ((int_en & CAN0_INTREN_ROIE_Msk) && (int_pending & CAN0_INTRST_ROIF_Msk))
    {
        __LL_CAN_RxOverIntPnd_Clr(pCanObj->Instance);
        rt_hw_can_isr(&pCanObj->rt_can, RT_CAN_EVENT_RXOF_IND | (0UL << 8));
    }

    /* Transmission Primary Interrupt Handler */
    if ((int_en & CAN0_INTREN_TPIE_Msk) && (int_pending & CAN0_INTRST_TPIF_Msk))
    {
        __LL_CAN_TxPriIntPnd_Clr(pCanObj->Instance);
        rt_hw_can_isr(&pCanObj->rt_can, RT_CAN_EVENT_TX_DONE | (0UL << 8));
    }

    /* Error Passive Interrupt Handler */
    if ((int_en & CAN0_INTREN_EPIE_Msk) && (int_pending & CAN0_INTRST_EPIF_Msk))
    {
        __LL_CAN_ErrPassiveIntPnd_Clr(pCanObj->Instance);
    }

    /* Arbitration Lost Interrupt Handler */
    if ((int_en & CAN0_INTREN_ALIE_Msk) && (int_pending & CAN0_INTRST_ALIF_Msk))
    {
        rt_hw_can_isr(&pCanObj->rt_can, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        __LL_CAN_ArbLostIntPnd_Clr(pCanObj->Instance);
    }

    /* Bus Error Interrupt Handler */
    if ((int_en & CAN0_INTREN_BEIE_Msk) && (int_pending & CAN0_INTRST_BEIF_Msk))
    {
        rt_hw_can_isr(&pCanObj->rt_can, RT_CAN_EVENT_TX_FAIL | 0 << 8);
        __LL_CAN_BusErrIntPnd_Clr(pCanObj->Instance);
    }

    /* Error Interrupt Handler */
    if ((int_en & CAN0_INTREN_EIE_Msk) && (int_pending & CAN0_INTRST_EIF_Msk))
    {
        __LL_CAN_ErrIntPnd_Clr(pCanObj->Instance);
        rt_hw_can_isr(&pCanObj->rt_can, RT_CAN_EVENT_TX_FAIL | 0 << 8);
    }
}

#ifdef BSP_USING_CAN0
void CAN0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    tae32_can_isr(&can_obj[CAN0_INDEX].rt_can);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_CAN1
void CAN1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    tae32_can_isr(&can_obj[CAN1_INDEX].rt_can);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif


static const struct rt_can_ops tae32_can_ops =
{
    tae32_can_configure,
    tae32_can_control,
    tae32_can_sendmsg,
    tae32_can_recvmsg,
};


int rt_hw_can_init(void)
{
    int result = RT_EOK;
    struct can_configure config = CANDEFAULTCONFIG;
    config.privmode = RT_CAN_MODE_NOPRIV;
    config.ticks = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = CAN_FILTER_COUNT;
#endif

    for (rt_uint32_t i = 0; i < CAN_INDEX_MAX; i++)
    {
        can_obj[i].rt_can.config = config;
        rt_memset(&can_obj[i].config, 0, sizeof(can_obj[i].config));
        /* register CAN device */
        result = rt_hw_can_register(&can_obj[i].rt_can,
                                    can_obj[i].name,
                                    &tae32_can_ops,
                                    NULL);
    }
    return result;
}

INIT_DEVICE_EXPORT(rt_hw_can_init);

#endif /* RT_USING_CAN */
