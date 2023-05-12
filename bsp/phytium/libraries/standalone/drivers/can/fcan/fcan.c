/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fcan.c
 * Date: 2021-04-29 10:21:53
 * LastEditTime: 2022-02-18 08:29:20
 * Description:  This files is for the can functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/5/26  first release
 * 1.1   wangxiaodong  2022/9/23  improve functions
 * 1.2   zhangyan      2022/12/7  improve functions
 */

#include "string.h"
#include <limits.h>
#include <stdlib.h>
#include "fkernel.h"
#include "fcan.h"
#include "fcan_hw.h"
#include "fassert.h"
#include "fdebug.h"
#include "fswap.h"
#include "fparameters.h"
#include "fsleep.h"


#define FT_CAN_DEBUG_TAG "FT_CAN"
#define FCAN_DEBUG(format, ...) FT_DEBUG_PRINT_D(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)
#define FCAN_INFO(format, ...) FT_DEBUG_PRINT_I(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)
#define FCAN_WARN(format, ...) FT_DEBUG_PRINT_W(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)
#define FCAN_ERROR(format, ...) FT_DEBUG_PRINT_E(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)

typedef struct
{
    u32 tseg1_min; /* Time segement 1 = prop_seg + phase_seg1 */
    u32 tseg1_max;
    u32 tseg2_min; /* Time segement 2 = phase_seg2 */
    u32 tseg2_max;
    u32 sjw_max; /* Synchronisation jump width */
    u32 brp_min; /* Bit-rate prescaler */
    u32 brp_max;
    u32 brp_inc;
} FCanBittimingConst;

/* 仲裁段速率默认值 */
static const FCanBittimingConst FCanArbBitConst =
{
    .tseg1_min = FCAN_ARB_TSEG1_MIN, /* Time segement 1 = prop_seg + phase_seg1 */
    .tseg1_max = FCAN_ARB_TSEG1_MAX,
    .tseg2_min = FCAN_ARB_TSEG2_MIN, /* Time segement 2 = phase_seg2 */
    .tseg2_max = FCAN_ARB_TSEG2_MAX,
    .sjw_max = FCAN_ARB_SJW_MAX, /* Synchronisation jump width */
    .brp_min = FCAN_ARB_BRP_MIN, /* Bit-rate prescaler */
    .brp_max = FCAN_ARB_BRP_MAX,
    .brp_inc = FCAN_ARB_BRP_INC,
};

/* 数据段速率默认值 */
static const FCanBittimingConst FCanDataBitConst =
{
    .tseg1_min = FCAN_DATA_TSEG1_MIN, /* Time segement 1 = prop_seg + phase_seg1 */
    .tseg1_max = FCAN_DATA_TSEG1_MAX,
    .tseg2_min = FCAN_DATA_TSEG2_MIN, /* Time segement 2 = phase_seg2 */
    .tseg2_max = FCAN_DATA_TSEG2_MAX,
    .sjw_max = FCAN_DATA_SJW_MAX, /* Synchronisation jump width */
    .brp_min = FCAN_DATA_BRP_MIN, /* Bit-rate prescaler */
    .brp_max = FCAN_DATA_BRP_MAX,
    .brp_inc = FCAN_DATA_BRP_INC,
};

/* calculate the can sample point */
static s32 FCanUpdateSamplePoint(const FCanBittimingConst *btc,
                                 u32 sample_point_nominal, u32 tseg,
                                 u32 *tseg1_ptr, u32 *tseg2_ptr,
                                 u32 *sample_point_error_ptr)
{
    u32 sample_point_error, best_sample_point_error = UINT_MAX;
    u32 sample_point, best_sample_point = 0;
    u32 tseg1, tseg2;
    s32 i;

    for (i = 0; i <= 1; i++)
    {
        tseg2 = tseg + CAN_CALC_SYNC_SEG - (sample_point_nominal * (tseg + CAN_CALC_SYNC_SEG)) / 1000 - i;
        tseg2 = clamp(tseg2, btc->tseg2_min, btc->tseg2_max);
        tseg1 = tseg - tseg2;
        if (tseg1 > btc->tseg1_max)
        {
            tseg1 = btc->tseg1_max;
            tseg2 = tseg - tseg1;
        }

        sample_point = 1000 * (tseg + CAN_CALC_SYNC_SEG - tseg2) / (tseg + CAN_CALC_SYNC_SEG);
        sample_point_error = abs(sample_point_nominal - sample_point);

        if ((sample_point <= sample_point_nominal) && (sample_point_error < best_sample_point_error))
        {
            best_sample_point = sample_point;
            best_sample_point_error = sample_point_error;
            *tseg1_ptr = tseg1;
            *tseg2_ptr = tseg2;
        }
    }

    if (sample_point_error_ptr)
    {
        *sample_point_error_ptr = best_sample_point_error;
    }

    return best_sample_point;
}

/**
 * @name: FCanCalcBittiming
 * @msg:  This routine calculate Bit timing
 * @param {structFCanBittiming} *bt_p is is a structure that contains the CAN baud rate configuration parameter , The user needs to fill in the baudrate first
 * @param {u32} target_baudrate, parameters of target baudrate
 * @param {u32} target_sample_point, parameters of target sample point, 0 means the general configuration is used
 * @param {FCanSegmentType} target_segment, specifies which target is to be selected. followed by FCAN_ARB_SEGMENT or FCAN_DATA_SEGMENT
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed
 */
static FError FCanCalcBittiming(FCanBaudrateConfig *bt_p, u32 target_baudrate, u32 target_sample_point, FCanSegmentType target_segment)
{
    u32 baudrate;       /* current baudrate */
    u32 baudrate_error; /* difference between current and nominal value */
    u32 best_baudrate_error = UINT_MAX;
    u32 sample_point_error; /* difference between current and nominal value */
    u32 best_sample_point_error = UINT_MAX;
    u32 sample_point_nominal; /* nominal sample point */
    u32 best_tseg = 0;        /* current best value for tseg */
    u32 best_brp = 0;         /* current best value for brp */
    u32 brp, tsegall, tseg, tseg1 = 0, tseg2 = 0;
    u64 v64;

    u32 reg_val;

    const FCanBittimingConst *btc;
    FCanBaudrateConfig *bt = bt_p;
    FASSERT(bt_p != NULL);
    FASSERT(target_segment < FCAN_SEGMENT_TYPE_NUM);

    if (target_segment == FCAN_DATA_SEGMENT)
    {
        btc = &FCanDataBitConst;
    }
    else
    {
        btc = &FCanArbBitConst;
    }

    if (target_sample_point)
    {
        sample_point_nominal = target_sample_point;
    }
    else
    {
        if (target_baudrate > 4000000)
        {
            sample_point_nominal = 650;
        }
        else if (target_baudrate > 2000000)
        {
            sample_point_nominal = 680;
        }
        else if (target_baudrate > 1000000)
        {
            sample_point_nominal = 725;
        }
        else if (target_baudrate > 800000)
        {
            sample_point_nominal = 750;
        }
        else if (target_baudrate > 500000)
        {
            sample_point_nominal = 800;
        }
        else
        {
            sample_point_nominal = 875;
        }
    }

    for (tseg = (btc->tseg1_max + btc->tseg2_max) * 2 + 1;
         tseg >= (btc->tseg1_min + btc->tseg2_min) * 2; tseg--)
    {
        tsegall = CAN_CALC_SYNC_SEG + tseg / 2;

        /* Compute all possible tseg choices (tseg=tseg1+tseg2) */
        brp = FCAN_CLK_FREQ_HZ / (tsegall * target_baudrate) + tseg % 2;

        /* choose brp step which is possible in system */
        brp = (brp / btc->brp_inc) * btc->brp_inc;

        if ((brp < btc->brp_min) || (brp > btc->brp_max))
        {
            continue;
        }

        baudrate = FCAN_CLK_FREQ_HZ / (brp * tsegall);
        baudrate_error = abs(target_baudrate - baudrate);

        /* tseg brp biterror */
        if (baudrate_error > best_baudrate_error)
        {
            continue;
        }

        /* reset sample point error if we have a better baudrate */
        if (baudrate_error < best_baudrate_error)
        {
            best_sample_point_error = UINT_MAX;
        }

        FCanUpdateSamplePoint(btc, sample_point_nominal, tseg / 2, &tseg1, &tseg2, &sample_point_error);

        FCAN_DEBUG("target_segment=%d, brp=%d, tseg=%d, tseg1=%d, tseg2=%d, sample_point_nominal=%d",
                   target_segment, brp, tseg, tseg1, tseg2, sample_point_nominal);

        u32 prop_seg = tseg1 / 2;
        u32 phase_seg1 = tseg1 - prop_seg;
        u32 phase_seg2 = tseg2;
        u32 sjw = 1;

        /* Setting Baud Rate prescalar value in BRPR Register */
        reg_val = (brp - 1) << 16;
        reg_val |= (prop_seg - 1) << 2;
        reg_val |= (phase_seg1 - 1) << 5;
        reg_val |= (phase_seg2 - 1) << 8;
        reg_val |= (sjw - 1);
        FCAN_DEBUG("reg_val=%#x\n", reg_val);

        if (sample_point_error > best_sample_point_error)
        {
            continue;
        }

        best_sample_point_error = sample_point_error;
        best_baudrate_error = baudrate_error;
        best_tseg = tseg / 2;
        best_brp = brp;

        if (baudrate_error == 0 && sample_point_error == 0)
        {
            break;
        }
    }

    if (best_baudrate_error)
    {
        /* Error in one-tenth of a percent */
        v64 = (u64)best_baudrate_error * 1000;
        do_div(v64, target_baudrate);
        baudrate_error = (u32)v64;
        if (baudrate_error > CAN_CALC_MAX_ERROR)
        {
            FCAN_ERROR("Baudrate error.");
            return FCAN_FAILURE;
        }
    }

    /* real sample point */
    FCanUpdateSamplePoint(btc, sample_point_nominal, best_tseg,
                          &tseg1, &tseg2, NULL);
    FCAN_DEBUG("tseg1=%d, tseg2=%d, sample_point_nominal=%d", tseg1, tseg2, sample_point_nominal);

    bt->prop_seg = tseg1 / 2;
    bt->phase_seg1 = tseg1 - bt->prop_seg;
    bt->phase_seg2 = tseg2;

    /* check for sjw user settings */
    if (!bt->sjw || !btc->sjw_max)
    {
        bt->sjw = 1;
    }
    else
    {
        /* bt->sjw is at least 1 -> sanitize upper bound to sjw_max */
        if (bt->sjw > btc->sjw_max)
        {
            bt->sjw = btc->sjw_max;
        }
        /* bt->sjw must not be higher than tseg2 */
        if (tseg2 < bt->sjw)
        {
            bt->sjw = tseg2;
        }
    }

    bt->brp = best_brp;

    /* real baudrate */
    if (target_baudrate != FCAN_CLK_FREQ_HZ / (bt->brp * (CAN_CALC_SYNC_SEG + tseg1 + tseg2)))
    {
        FCAN_ERROR("Target baudrate calculate timing failed.");
        return FCAN_FAILURE;
    }

    FCAN_DEBUG("bt->prop_seg=%d, bt->phase_seg1=%d, bt->phase_seg2=%d, bt->sjw=%d, bt->brp=%d",
               bt->prop_seg, bt->phase_seg1, bt->phase_seg2, bt->sjw, bt->brp);

    return FCAN_SUCCESS;
}

static u32 FCanGetDlcLen(u32 dlc)
{
    u32 dlc_len = 0;
    if (dlc == 0)
    {
        dlc_len = 8;
    }

    switch (dlc)
    {
        case 1:
            dlc_len = 1;
            break;
        case 2:
            dlc_len = 2;
            break;
        case 3:
            dlc_len = 3;
            break;
        case 4:
            dlc_len = 4;
            break;
        case 5:
            dlc_len = 5;
            break;
        case 6:
            dlc_len = 6;
            break;
        case 7:
            dlc_len = 7;
            break;
        case 8:
            dlc_len = 8;
            break;
        case 9:
            dlc_len = 12;
            break;
        case 10:
            dlc_len = 16;
            break;
        case 11:
            dlc_len = 20;
            break;
        case 12:
            dlc_len = 24;
            break;
        case 13:
            dlc_len = 32;
            break;
        case 14:
            dlc_len = 48;
            break;
        case 15:
            dlc_len = 64;
            break;
        default :
            dlc_len = 0;
            break;
    }

    return dlc_len;

}

static u32 FCanSetDlcLen(u32 len)
{
    if (len <= 8)
    {
        return len;
    }
    else if (len <= 12)
    {
        return 9;
    }
    else if (len <= 16)
    {
        return 10;
    }
    else if (len <= 20)
    {
        return 11;
    }
    else if (len <= 24)
    {
        return 12;
    }
    else if (len <= 32)
    {
        return 13;
    }
    else if (len <= 48)
    {
        return 14;
    }
    else if (len <= 64)
    {
        return 15;
    }
    else
    {
        return 0;
    }
}

/**
 * @name: FCanReset
 * @msg: reset a specific can instance
 * @param {FCanCtrl} *pctrl, instance of FCan controller
 * @return {*}
 */
void FCanReset(FCanCtrl *instance_p)
{
    u32 reg_value;
    FCanConfig *config_p;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    config_p = &instance_p->config;

    FCAN_WRITE_REG32(config_p->base_address, FCAN_CTRL_OFFSET, 0);
    reg_value = FCAN_READ_REG32(config_p->base_address, FCAN_CTRL_OFFSET);
    if (reg_value & FCAN_CTRL_XFER_MASK)
    {
        FCAN_ERROR("Can is not in configration mode.");
        return;
    }

    /* reset can */
    FCAN_WRITE_REG32(config_p->base_address, FCAN_CTRL_OFFSET, FCAN_CTRL_RST_MASK);
}

/**
 * @name: FCanDeInitialize
 * @msg: Deinitializes a specific can instance
 * @param {FCanCtrl} *pctrl, instance of FCan controller
 * @return {*}
 */
void FCanDeInitialize(FCanCtrl *instance_p)
{
    FASSERT(instance_p);
    instance_p->is_ready = 0;
    memset(instance_p, 0, sizeof(*instance_p));
    return;
}

/**
 * @name: FCanCfgInitialize
 * @msg:  Initializes a specific instance such that it is ready to be used.
 * @param {FCanCtrl} *instance_p, instance of FCanCtrl controller
 * @param {FCanConfig} *input_config_p, configuration parameters of FCanCtrl
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed
 */
FError FCanCfgInitialize(FCanCtrl *instance_p, const FCanConfig *input_config_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(input_config_p != NULL);

    FError ret = FCAN_SUCCESS;
    /*
    * If the device is started, disallow the initialize and return a Status
    * indicating it is started.  This allows the user to de-initialize the device
    * and reinitialize, but prevents a user from inadvertently
    * initializing.
    */
    if (FT_COMPONENT_IS_READY == instance_p->is_ready)
    {
        FCAN_WARN("Device is already initialized.");
    }

    /*Set default values and configuration data */
    FCanDeInitialize(instance_p);

    instance_p->config = *input_config_p;

    instance_p->is_ready = FT_COMPONENT_IS_READY;

    FCanReset(instance_p);

    return ret;
}

/**
 * @name: FCanStatusGet
 * @msg: read can status, include transfer status, error and fifo count.
 * @param {FCanCtrl} *instance_p, pointer to a FCanCtrl structure that contains
 *                the configuration information for the specified can module.
 * @param {FCanStatus} *status_p, pointer to can status, include send and receive, error and fifo count .
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed.
 */
FError FCanStatusGet(FCanCtrl *instance_p, FCanStatus *status_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(status_p != NULL);
    uintptr base_address = instance_p->config.base_address;

    u32 reg_val = 0;
    reg_val = FCAN_READ_REG32(base_address, FCAN_XFER_STS_OFFSET);

    status_p->xfer_status.xfers = FCAN_XFER_STS_XFERS_GET(reg_val);
    status_p->xfer_status.rs = FCAN_XFER_STS_RS_GET(reg_val);
    status_p->xfer_status.ts = FCAN_XFER_STS_TS_GET(reg_val);
    status_p->xfer_status.fies = FCAN_XFER_STS_FIES_GET(reg_val);
    status_p->xfer_status.fras = FCAN_XFER_STS_FRAS_GET(reg_val);

    reg_val = FCAN_READ_REG32(base_address, FCAN_ERR_CNT_OFFSET);
    status_p->rx_err_cnt = FCAN_ERR_CNT_RFN_GET(reg_val);
    status_p->tx_err_cnt = FCAN_ERR_CNT_TFN_GET(reg_val);

    reg_val = FCAN_READ_REG32(base_address, FCAN_FIFO_CNT_OFFSET);
    status_p->tx_fifo_cnt = FCAN_FIFO_CNT_TFN_GET(reg_val);
    status_p->rx_fifo_cnt = FCAN_FIFO_CNT_RFN_GET(reg_val);

    return FCAN_SUCCESS;
}

/**
 * @name: FCanRecv
 * @msg: receive can message by specific can instance.
 * @param {FCanCtrl} *instance_p, pointer to a FCanCtrl structure that contains
 *                the configuration information for the specific can module.
 * @param {FCanFrame} *frame_p, can message receive struct.
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed.
 */
FError FCanRecv(FCanCtrl *instance_p, FCanFrame *frame_p)
{
    u32 canid;
    u32 dlc;
    int i = 0, j = 0;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(frame_p != NULL);
    uintptr base_address = instance_p->config.base_address;

    memset(frame_p, 0, sizeof(FCanFrame));

    /* Read a frame from Phytium CAN */
    canid = FCAN_READ_REG32(base_address, FCAN_RX_FIFO_OFFSET);
    /* if canid is big-endian ,use swap change to little-endian */
    canid = be32_to_cpu(canid);

    FCAN_DEBUG("FCanRecv canid = %#x\n", canid);

    /* identifier extension */
    if (canid & FCAN_IDR_IDE_MASK)
    {
        dlc = FCAN_READ_REG32(base_address, FCAN_RX_FIFO_OFFSET);
        dlc = be32_to_cpu(dlc);
        FCAN_DEBUG("FCanRecv dlc = %#x\n", dlc);

        if (dlc & FTCANFD_ID2_FDL_MASK)
        {
            if (dlc & FTCANFD_ID2_BRS_MASK)
            {
                frame_p->flags |= CANFD_BRS;
            }

            if (dlc & FTCANFD_ID2_ESI_MASK)
            {
                frame_p->flags |= CANFD_ESI;
            }
            dlc = FTCANFD_ID2_EDLC_GET(dlc);
        }
        else
        {
            dlc = FCAN_IDR_EDLC_GET(dlc);
        }

        frame_p->canid = FCAN_IDR_ID1_GET(canid) << FCAN_ACC_IDN_SHIFT;
        frame_p->canid |= FCAN_IDR_ID2_GET(canid);
        frame_p->canid |= CAN_EFF_FLAG;

        if (canid & FCAN_IDR_RTR_MASK)
        {
            frame_p->canid |= CAN_RTR_FLAG;
        }
    }
    else
    {
        if (canid & FTCANFD_ID1_FDL_MASK)
        {
            if (canid & FTCANFD_ID1_BRS_MASK)
            {
                frame_p->flags |= CANFD_BRS;
            }

            if (canid & FTCANFD_ID1_ESI_MASK)
            {
                frame_p->flags |= CANFD_ESI;
            }
            dlc = FTCANFD_ID1_SDLC_GET(canid);
        }
        else
        {
            dlc = FCAN_IDR_DLC_GET(canid);
        }

        /* The received frame is a standard format frame */
        frame_p->canid = FCAN_IDR_ID1_GET(canid);
        if (canid & FCAN_IDR_SRR_MASK)
        {
            frame_p->canid |= CAN_RTR_FLAG;
        }
    }

    frame_p->candlc = FCanGetDlcLen(dlc);
    FCAN_DEBUG("FCanRecv frame_p->candlc = %d\n", frame_p->candlc);

    if (!(frame_p->canid & CAN_RTR_FLAG))
    {
        j = 0;
        for (i = frame_p->candlc; i > 0; i -= 4)
        {
            *(u32 *)(frame_p->data + j) = FCAN_READ_REG32(base_address, FCAN_RX_FIFO_OFFSET);
            j += 4;
        }

        if (i > 0)
        {
            *(u32 *)(frame_p->data + j) = FCAN_READ_REG32(base_address, FCAN_RX_FIFO_OFFSET);
        }
    }

    return FCAN_SUCCESS;
}

/**
 * @name: FCanSend
 * @msg: send can message by specific can instance.
 * @param {FCanCtrl} *instance_p, pointer to a FCanCtrl structure that contains
 *                the configuration information for the specific can module.
 * @param {FCanFrame} *frame_p, can message send struct.
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed.
 */
FError FCanSend(FCanCtrl *instance_p, FCanFrame *frame_p)
{
    u32 id, dlc;

    int i = 0, j = 0;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    uintptr base_address = instance_p->config.base_address;

    while (FCAN_TX_FIFO_FULL(instance_p));

    u32 can_send_dlc = FCanSetDlcLen(frame_p->candlc);

    if (frame_p->canid & CAN_EFF_FLAG)
    {
        /* Extended CAN id format */
        id = FCAN_IDR_ID2_SET(frame_p->canid & CAN_EFF_MASK);
        id |= FCAN_IDR_ID1_SET((frame_p->canid & CAN_EFF_MASK) >>
                               (CAN_EFF_ID_BITS - CAN_SFF_ID_BITS));

        /* The substibute remote TX request bit should be "1"
         * for extended frames as in the Phytium CAN datasheet
         */
        id |= FCAN_IDR_IDE_MASK | FCAN_IDR_SRR_MASK;
        if (frame_p->canid & CAN_RTR_FLAG)
        {
            id |= FCAN_IDR_RTR_MASK;
        }

        if (instance_p->use_canfd == TRUE)
        {
            dlc = can_send_dlc << FCANFD_IDR_EDLC_SHIFT;
            dlc |= FTCANFD_ID2_FDL_MASK;

            /* enable brs-Bit Rate Switch  */
            frame_p->flags |= CANFD_BRS;

            if (frame_p->flags & CANFD_BRS)
            {
                dlc |= FTCANFD_ID2_BRS_MASK;
            }

            if (frame_p->flags & CANFD_ESI)
            {
                dlc |= FTCANFD_ID2_ESI_MASK;
            }
        }
        else
        {
            dlc = can_send_dlc << FCAN_IDR_EDLC_SHIFT;
        }

        FCAN_DEBUG("FCanSend id = %#x\n", id);
        FCAN_DEBUG("FCanSend dlc = %#x\n", dlc);
        FCAN_WRITE_REG32(base_address, FCAN_TX_FIFO_OFFSET, be32_to_cpu(id));
        FCAN_WRITE_REG32(base_address, FCAN_TX_FIFO_OFFSET, be32_to_cpu(dlc));
    }
    else
    {
        /* Standard CAN id format */
        id = FCAN_IDR_ID1_SET(frame_p->canid & CAN_SFF_MASK);

        if (frame_p->canid & CAN_RTR_FLAG)
        {
            id |= FCAN_IDR_SRR_MASK;
        }

        FCAN_DEBUG("instance_p->use_canfd = %d, can_send_dlc = %d \n",
                   instance_p->use_canfd, can_send_dlc);

        if (instance_p->use_canfd == TRUE)
        {
            dlc = ((can_send_dlc << FCANFD_IDR1_SDLC_SHIFT) | FTCANFD_IDR_PAD_MASK);

            dlc |= FTCANFD_ID1_FDL_MASK;

            /* enable brs-Bit Rate Switch  */
            frame_p->flags |= CANFD_BRS;

            if (frame_p->flags & CANFD_BRS)
            {
                dlc |= FTCANFD_ID1_BRS_MASK;
            }

            if (frame_p->flags & CANFD_ESI)
            {
                dlc |= FTCANFD_ID1_ESI_MASK;
            }
        }
        else
        {
            dlc = ((can_send_dlc << FCAN_IDR_SDLC_SHIFT) | FCAN_IDR_PAD_MASK);
        }

        id |= dlc;
        FCAN_DEBUG("FCanSend id = %#x\n", id);
        FCAN_WRITE_REG32(base_address, FCAN_TX_FIFO_OFFSET, be32_to_cpu(id));

    }

    if (!(frame_p->canid & CAN_RTR_FLAG))
    {
        j = 0;
        FCAN_DEBUG("frame_p->canid=%#x, frame_p->candlc = %d\n", frame_p->canid, frame_p->candlc);
        for (i = frame_p->candlc; i > 0; i -= 4)
        {
            FCAN_WRITE_REG32(base_address, FCAN_TX_FIFO_OFFSET, *(u32 *)(frame_p->data + j));
            j += 4;
        }

        if (i > 0)
        {
            FCAN_WRITE_REG32(base_address, FCAN_TX_FIFO_OFFSET, *(u32 *)(frame_p->data + j));
        }

    }

    /* triggers tranmission */
    if (FCAN_READ_REG32(base_address, FCAN_CTRL_OFFSET) & FCAN_CTRL_TXREQ_MASK)
    {
        FCAN_CLEARBIT(base_address, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
        FCAN_SETBIT(base_address, FCAN_CTRL_OFFSET, FCAN_CTRL_TXREQ_MASK | FCAN_CTRL_XFER_MASK);
        return FCAN_SUCCESS;
    }
    else
    {
        FCAN_WARN("Monitoring mode cannot send message!!!");
        return FCAN_FAILURE;
    }

}

/**
 * @name: FCan_SetTiming
 * @msg:  This routine sets Bit time
 * @param {FCanCtrl} *instance_p is a pointer to the FCanCtrl instance.
 * @param {FCanBaudrateConfig} *bittiming_p, parameters of arbitration or data segment baudrate
 * @param {FCanSegmentType} target_segment, specifies which target is to be selected. followed by FCAN_ARB_SEGMENT or FCAN_DATA_SEGMENT
 * @out param:
 * @return {*}
 */
static FError FCanSetTiming(FCanCtrl *instance_p, FCanBaudrateConfig *bittiming_p, FCanSegmentType target_segment)
{
    u32 reg_val = 0;
    u32 transfer_enable;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(target_segment < FCAN_SEGMENT_TYPE_NUM);
    uintptr base_address = instance_p->config.base_address;

    FASSERT(bittiming_p->brp != 0);
    FASSERT(bittiming_p->prop_seg != 0);
    FASSERT(bittiming_p->phase_seg1 != 0);
    FASSERT(bittiming_p->phase_seg2 != 0);

    FCAN_DEBUG("brp=%d, prop_seg=%d, phase_seg1=%d, phase_seg2=%d, sjw=%d",
               bittiming_p->brp, bittiming_p->prop_seg, bittiming_p->phase_seg1,
               bittiming_p->phase_seg2, bittiming_p->sjw);

    /* Setting Baud Rate prescalar value in BRPR Register */
    reg_val = (bittiming_p->brp - 1) << 16;
    reg_val |= (bittiming_p->prop_seg - 1) << 2;
    reg_val |= (bittiming_p->phase_seg1 - 1) << 5;
    reg_val |= (bittiming_p->phase_seg2 - 1) << 8;
    reg_val |= (bittiming_p->sjw - 1);

    transfer_enable = (FCAN_READ_REG32(base_address, FCAN_CTRL_OFFSET) & FCAN_CTRL_XFER_MASK);
    if (transfer_enable)
    {
        FCAN_CLEARBIT(base_address, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
    }

    if (reg_val)
    {
        if (target_segment == FCAN_DATA_SEGMENT)
        {
            FCAN_WRITE_REG32(base_address, FCAN_DAT_RATE_CTRL_OFFSET, reg_val);
        }
        else
        {
            FCAN_WRITE_REG32(base_address, FCAN_ARB_RATE_CTRL_OFFSET, reg_val);
        }
    }
    else
    {
        FCAN_ERROR("FCanSetTiming reg_val failed");
        return FCAN_FAILURE;
    }

    return FCAN_SUCCESS;
}

/**
 * @name: FCanBaudrateSet
 * @msg:  Set the fcan baudrate by FCanBaudrateConfig parameters.
 * @param {FCanCtrl} *instance_p, instance of FCanCtrl controller
 * @param {FCanBaudrateConfig} *baudrate_p, parameters of arbitration or data segment baudrate
 *        include baudrate, parameters of target baudrate
 *        include sample_point, parameters of target sample point, 0 means the general configuration is used.
 *        The value is the percentage of sampling points multiplied by 1000.
 *        For example, if sample point is 0.75, set target_sample_point = 750.
 *        Or manual config baudrate parameters.
 * @param {FCanSegmentType} segment, specifies data segment or arbitration segment is selected. followed by FCAN_ARB_SEGMENT or FCAN_DATA_SEGMENT
 * @return err code information, FQSPI_SUCCESS indicates success，others indicates failed
 * @note this function is to set arb and data segment baudrate, according to the prop_seg,
 * phase_seg1, phase_seg2 ,brp and sjw parameters, users can use this function to set can baudrate.
 * A formula to calculate baudrate is:
 * baudrate = FCAN_CLK_FREQ_HZ/(brp*(sjw+prop_seg+phase_seg1++phase_seg2))
 * sample point = (sjw+prop_seg+phase_seg1)/(sjw+prop_seg+phase_seg1++phase_seg2)
 * Recommended sample point :
 * 75.0% : baudrate > 800000
 * 80.0% : baudrate > 500000
 * 87.5% : baudrate <= 500000
 */
FError FCanBaudrateSet(FCanCtrl *instance_p, FCanBaudrateConfig *baudrate_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FCanSegmentType segment = baudrate_p->segment;
    FASSERT(segment < FCAN_SEGMENT_TYPE_NUM);
    u32 baudrate = baudrate_p->baudrate;
    u32 sample_point = baudrate_p->sample_point;
    if (baudrate_p->auto_calc == TRUE)
    {
#if defined(CONFIG_TARGET_F2000_4) || defined(CONFIG_TARGET_D2000)
        if ((segment == FCAN_ARB_SEGMENT) && ((baudrate > FCAN_BAUDRATE_1000K) || (baudrate < FCAN_BAUDRATE_50K)))
        {
            FCAN_ERROR("FCanBaudrateSet FCAN_ARB_SEGMENT baudrate = %d invalid", baudrate);
            return FCAN_INVAL_PARAM;
        }
        if ((segment == FCAN_DATA_SEGMENT) && ((baudrate > FCAN_BAUDRATE_1000K) || (baudrate < FCAN_BAUDRATE_50K)))
        {
            FCAN_ERROR("FCanBaudrateSet FCAN_DATA_SEGMENT baudrate = %d invalid", baudrate);
            return FCAN_INVAL_PARAM;
        }
#elif defined(CONFIG_TARGET_E2000) || defined(TARDIGRADE)
        if ((segment == FCAN_ARB_SEGMENT) && ((baudrate > FCAN_BAUDRATE_1000K) || (baudrate < FCAN_BAUDRATE_10K)))
        {
            FCAN_ERROR("FCanBaudrateSet FCAN_ARB_SEGMENT baudrate = %d invalid", baudrate);
            return FCAN_INVAL_PARAM;
        }
        if ((segment == FCAN_DATA_SEGMENT) && ((baudrate > FCAN_BAUDRATE_5000K) || (baudrate < FCAN_BAUDRATE_10K)))
        {
            FCAN_ERROR("FCanBaudrateSet FCAN_DATA_SEGMENT baudrate = %d invalid", baudrate);
            return FCAN_INVAL_PARAM;
        }
#endif
    }

    FError ret = FCAN_SUCCESS;
    FCanBaudrateConfig timing_config;
    memset(&timing_config, 0, sizeof(timing_config));

    /* Automatically calculate parameters based on baudrate and sample point */
    if (baudrate_p->auto_calc == TRUE)
    {
        ret = FCanCalcBittiming(&timing_config, baudrate, sample_point, segment);
        if (ret != FCAN_SUCCESS)
        {
            FCAN_ERROR("FCanCalcBittiming %d failed", segment);
            return FCAN_FAILURE;
        }

        ret = FCanSetTiming(instance_p, &timing_config, segment);
        if (ret != FCAN_SUCCESS)
        {
            FCAN_ERROR("FCanSetTiming %d failed", segment);
            return FCAN_FAILURE;
        }
    }
    else
    {
        ret = FCanSetTiming(instance_p, baudrate_p, segment);
        if (ret != FCAN_SUCCESS)
        {
            FCAN_ERROR("FCanSetTiming failed");
            return FCAN_FAILURE;
        }
    }

    return ret;
}

/**
 * @name: FCanFdEnable
 * @msg:  Enable or disable can.
 * @param {FCanCtrl} *instance_p, instance of FCanCtrl controller
 * @param {boolean} enable, TRUE-enable canfd, FALSE-disable canfd.
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed
 */
FError FCanEnable(FCanCtrl *instance_p, boolean enable)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    uintptr base_addr = instance_p->config.base_address;
    if (enable == TRUE)
    {
        FCAN_SETBIT(base_addr, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
    }
    else
    {
        FCAN_CLEARBIT(base_addr, FCAN_CTRL_OFFSET, FCAN_CTRL_XFER_MASK);
    }
    return FCAN_SUCCESS;
}

/**
 * @name: FCanIdMaskFilterSet
 * @msg:  Set the can mask and umask id.
 * @param {FCanCtrl} *instance_p, instance of FCanCtrl controller
 * @param {FCanIdMaskConfig} *id_mask_p, include filter register index, umask id and mask id
 *  id indicates a specific ID can receive
 *  mask indicates mask the corresponding bit of the id
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed
 */
FError FCanIdMaskFilterSet(FCanCtrl *instance_p, FCanIdMaskConfig *id_mask_p)
{
    FASSERT(instance_p);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FASSERT(id_mask_p);
    u32 filter_index = id_mask_p->filter_index;
    FASSERT(filter_index < FCAN_ACC_ID_REG_NUM);
    uintptr base_address = instance_p->config.base_address;
    u32 id_reg_offset = 0;
    u32 mask_reg_offset = 0;
    u32 id = 0;
    u32 mask = 0;

    switch (filter_index)
    {
        case 0:
            id_reg_offset = FCAN_ACC_ID0_OFFSET;
            mask_reg_offset = FCAN_ACC_ID0_MASK_OFFSET;
            break;
        case 1:
            id_reg_offset = FCAN_ACC_ID1_OFFSET;
            mask_reg_offset = FCAN_ACC_ID1_MASK_OFFSET;
            break;
        case 2:
            id_reg_offset = FCAN_ACC_ID2_OFFSET;
            mask_reg_offset = FCAN_ACC_ID2_MASK_OFFSET;
            break;
        case 3:
            id_reg_offset = FCAN_ACC_ID3_OFFSET;
            mask_reg_offset = FCAN_ACC_ID3_MASK_OFFSET;
            break;
        default:
            return FCAN_FAILURE;
    }

    if (id_mask_p->type == FCAN_STANDARD_FRAME)
    {
        id = id_mask_p->id << FCAN_ACC_IDN_SHIFT;
        mask = id_mask_p->mask << FCAN_ACC_IDN_SHIFT;
    }

    FCAN_WRITE_REG32(base_address, id_reg_offset, id);
    FCAN_WRITE_REG32(base_address, mask_reg_offset, mask);

    return FCAN_SUCCESS;
}

/**
 * @name: FCanIdMaskFilterEnable
 * @msg:  Set the can id mask filter enable.
 * @param {FCanCtrl} *instance_p, instance of FCanCtrl controller
 * @return {*}
 */
void FCanIdMaskFilterEnable(FCanCtrl *instance_p)
{
    FCanConfig *config_p;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    config_p = &instance_p->config;
    FCAN_SETBIT(config_p->base_address, FCAN_CTRL_OFFSET, FCAN_CTRL_AIME_MASK);
}

/**
 * @name: FCanIdMaskFilterDisable
 * @msg:  Set the can id mask filter disable.
 * @param {FCanCtrl} *instance_p, instance of FCanCtrl controller
 * @return {*}
 */
void FCanIdMaskFilterDisable(FCanCtrl *instance_p)
{
    FCanConfig *config_p;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    config_p = &instance_p->config;
    FCAN_CLEARBIT(config_p->base_address, FCAN_CTRL_OFFSET, FCAN_CTRL_AIME_MASK);
}

/**
 * @name: FCanInterruptEnable
 * @msg:  Enable can interrupt.
 * @param {FCanCtrl} *instance_p, instance of FCanCtrl controller
 * @param {FCanIntrEventType} event_type, interrupt event type
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed
 */
FError FCanInterruptEnable(FCanCtrl *instance_p, FCanIntrEventType event_type)
{
    FASSERT(instance_p != NULL);
    FASSERT(FT_COMPONENT_IS_READY == instance_p->is_ready);

    uintptr base_addr = instance_p->config.base_address;
    u32 reg_val = 0;
    reg_val = FCAN_READ_REG32(base_addr, FCAN_INTR_OFFSET);

    switch (event_type)
    {
        case FCAN_INTR_EVENT_SEND:
            reg_val |= FCAN_INTR_TEIE_MASK;
            break;

        case FCAN_INTR_EVENT_RECV:
            reg_val |= FCAN_INTR_REIE_MASK;
            break;

        case FCAN_INTR_EVENT_ERROR:
            reg_val |= FCAN_INTR_EIE_MASK;
            break;

        case FCAN_INTR_EVENT_BUSOFF:
            reg_val |= FCAN_INTR_BOIE_MASK;
            break;

        case FCAN_INTR_EVENT_PERROE:
            reg_val |= FCAN_INTR_PEIE_MASK;
            break;

        case FCAN_INTR_EVENT_PWARN:
            reg_val |= FCAN_INTR_PWIE_MASK;
            break;

        case FCAN_INTR_EVENT_FIFOFULL:
            reg_val |= FCAN_INTR_RFIE_MASK;
            break;

        case FCAN_INTR_EVENT_FIFOEMPTY:
            reg_val |= FCAN_INTR_TFIE_MASK;
            break;
        default:
            break;
    }

    FCAN_WRITE_REG32(base_addr, FCAN_INTR_OFFSET, reg_val);

    return FCAN_SUCCESS;
}

/**
 * @name: FCanFdEnable
 * @msg:  Enable or disable can fd.
 * @param {FCanCtrl} *instance_p, instance of FCanCtrl controller
 * @param {boolean} enable, TRUE-enable canfd, FALSE-disable canfd.
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed
 */
FError FCanFdEnable(FCanCtrl *instance_p, boolean enable)
{
    FASSERT(instance_p != NULL);
    FASSERT(FT_COMPONENT_IS_READY == instance_p->is_ready);
    uintptr base_addr = instance_p->config.base_address;

    if (enable == TRUE)
    {
        instance_p->use_canfd = TRUE;
        FCAN_SETBIT(base_addr, FCAN_CTRL_OFFSET, FCAN_CTRL_FDCRC_MASK | FCAN_CTRL_IOF_MASK);
    }
    else
    {
        instance_p->use_canfd = FALSE;
        FCAN_SETBIT(base_addr, FCAN_CTRL_OFFSET, FCAN_CTRL_IOF_MASK);
        FCAN_CLEARBIT(base_addr, FCAN_CTRL_OFFSET, FCAN_CTRL_FDCRC_MASK);
    }

    return FCAN_SUCCESS;
}

/**
 * @name: FCanSetMode
 * @msg:  Set the transmit mode, Monitor or Normal
 * @param {FCanCtrl} *instance_p, instance of FCanCtrl controller
 * @param {u32} tran_mode,parameters of target mode,0 Monitor mode,1 Normal mode
 * @return err code information, FCAN_SUCCESS indicates success，others indicates failed
 */
FError FCanSetMode(FCanCtrl *instance_p, u32 tran_mode)
{
    FASSERT(instance_p != NULL);
    FASSERT(FT_COMPONENT_IS_READY == instance_p->is_ready);
    uintptr base_addr = instance_p->config.base_address;

    if (tran_mode == FCAN_PROBE_MONITOR_MODE)
    {
        FCAN_CLEARBIT(base_addr, FCAN_CTRL_OFFSET, FCAN_CTRL_TXREQ_MASK);
    }
    if (tran_mode == FCAN_PROBE_NORMAL_MODE)
    {
        FCAN_SETBIT(base_addr, FCAN_CTRL_OFFSET, FCAN_CTRL_TXREQ_MASK);
    }

    return FCAN_SUCCESS;
}

