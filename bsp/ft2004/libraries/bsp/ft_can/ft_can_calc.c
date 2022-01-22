/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-05-06 09:30:51
 * @LastEditTime: 2021-05-25 16:41:10
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 */

#include "ft_can.h"

#include "ft_debug.h"
#include "string.h"

#ifndef max
#define max(x, y) (((x) < (y)) ? (y) : (x))
#endif

#ifndef min
#define min(x, y) (((x) < (y)) ? (x) : (y))
#endif

#define FT_CAN_DEBUG_TAG "FT_CAN"

#define FT_CAN_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_CAN_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_CAN_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FT_CAN_DEBUG_TAG, format, ##__VA_ARGS__)

#define CAN_CLK_FREQ 600000000
#define CAN_CALC_SYNC_SEG 1
#define FCAN_TSEG1_MIN 1
#define FCAN_TSEG1_MAX 8
#define FCAN_TSEG2_MIN 1
#define FCAN_TSEG2_MAX 8
#define FCAN_SJW_MAX 4
#define FCAN_BRP_MIN 1
#define FCAN_BRP_MAX 512
#define FCAN_BRP_INC 1
#define FCAN_CALC_SYNC_SEG 1
#define CAN_CALC_MAX_ERROR 50 /* in one-tenth of a percent */
#define BEST_BITRATE_ERROR (2147483647 * 2U + 1)

#define clamp(x, low, high) (min(max(low, x), high))

typedef struct can_bittiming_const
{
    char name[16]; /* Name of the CAN controller hardware */
    u32 tseg1_min; /* Time segement 1 = prop_seg + phase_seg1 */
    u32 tseg1_max;
    u32 tseg2_min; /* Time segement 2 = phase_seg2 */
    u32 tseg2_max;
    u32 sjw_max; /* Synchronisation jump width */
    u32 brp_min; /* Bit-rate prescaler */
    u32 brp_max;
    u32 brp_inc;
} FTCAN_BITTIMING_CONST;

static const struct can_bittiming_const ftcan_bittiming_const = {
    .name = "vxbftCan",
    .tseg1_min = 1,
    .tseg1_max = 8,
    .tseg2_min = 1,
    .tseg2_max = 8,
    .sjw_max = 4,
    .brp_min = 1,
    .brp_max = 512,
    .brp_inc = 1,
};

static int abs(
    int i /* integer for which to return absolute value */
)
{
    return (i >= 0 ? i : -i);
}

static u32 div64_32(u64 *n, u32 base)
{
    u64 rem = *n;
    u64 b = base;
    u64 res, d = 1;
    u32 high = rem >> 32;

    /* Reduce the thing a bit first */
    res = 0;
    if (high >= base)
    {
        high /= base;
        res = (u64)high << 32;
        rem -= (u64)(high * base) << 32;
    }

    while ((u64)b > 0 && b < rem)
    {
        b = b + b;
        d = d + d;
    }

    do
    {
        if (rem >= b)
        {
            rem -= b;
            res += d;
        }
        b >>= 1;
        d >>= 1;
    } while (d);

    *n = res;
    return rem;
}

s32 can_update_sample_point(const struct can_bittiming_const *btc,
                            u32 sample_point_nominal, u32 tseg,
                            u32 *tseg1_ptr, u32 *tseg2_ptr,
                            u32 *sample_point_error_ptr)
{
    u32 sample_point_error, best_sample_point_error = BEST_BITRATE_ERROR;
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
        *sample_point_error_ptr = best_sample_point_error;

    return best_sample_point;
}

ft_error_t FCan_CalcBittiming(struct FCan_Bittiming *Bt_p)
{
    u32 bitrate;       /* current bitrate */
    u32 bitrate_error; /* difference between current and nominal value */
    u32 best_bitrate_error = BEST_BITRATE_ERROR;
    u32 sample_point_error; /* difference between current and nominal value */
    u32 best_sample_point_error = BEST_BITRATE_ERROR;
    u32 sample_point_nominal; /* nominal sample point */
    u32 best_tseg = 0;        /* current best value for tseg */
    u32 best_brp = 0;         /* current best value for brp */
    u32 brp, tsegall, tseg, tseg1 = 0, tseg2 = 0;
    u64 v64;
    const struct can_bittiming_const *btc = &ftcan_bittiming_const;
    struct FCan_Bittiming *bt = Bt_p;

    if (bt->sample_point)
    {
        sample_point_nominal = bt->sample_point;
    }
    else
    {
        if (bt->bitrate > 800000)
            sample_point_nominal = 750;
        else if (bt->bitrate > 500000)
            sample_point_nominal = 800;
        else
            sample_point_nominal = 875;
    }

    for (tseg = (btc->tseg1_max + btc->tseg2_max) * 2 + 1;
         tseg >= (btc->tseg1_min + btc->tseg2_min) * 2; tseg--)
    {
        tsegall = CAN_CALC_SYNC_SEG + tseg / 2;

        /* Compute all possible tseg choices (tseg=tseg1+tseg2) */
        brp = CAN_CLK_FREQ / (tsegall * bt->bitrate) + tseg % 2;

        /* choose brp step which is possible in system */
        brp = (brp / btc->brp_inc) * btc->brp_inc;

        if ((brp < btc->brp_min) || (brp > btc->brp_max))
            continue;

        bitrate = CAN_CLK_FREQ / (brp * tsegall);

        bitrate_error = abs(bt->bitrate - bitrate);
        /* tseg brp biterror */
        if (bitrate_error > best_bitrate_error)
            continue;

        /* reset sample point error if we have a better bitrate */
        if (bitrate_error < best_bitrate_error)
            best_sample_point_error = BEST_BITRATE_ERROR;

        can_update_sample_point(btc, sample_point_nominal, tseg / 2, &tseg1, &tseg2, &sample_point_error);
        if (sample_point_error > best_sample_point_error)
            continue;

        best_sample_point_error = sample_point_error;
        best_bitrate_error = bitrate_error;
        best_tseg = tseg / 2;
        best_brp = brp;

        if (bitrate_error == 0 && sample_point_error == 0)
            break;
    }

    if (best_bitrate_error)
    {
        /* Error in one-tenth of a percent */
        v64 = (u64)best_bitrate_error * 1000;
        div64_32(&v64, bt->bitrate);
        bitrate_error = (u32)v64;
        if (bitrate_error > CAN_CALC_MAX_ERROR)
        {
            FT_CAN_DEBUG_E("bitrate error");
        }
        return FCAN_FAILURE;
        FT_CAN_DEBUG_E("bitrate error 2");
    }

    /* real sample point */
    bt->sample_point = can_update_sample_point(btc, sample_point_nominal, best_tseg,
                                               &tseg1, &tseg2, NULL);

    v64 = (u64)best_brp * 1000 * 1000 * 1000;
    div64_32(&v64, CAN_CLK_FREQ);
    bt->tq = (u64)v64;
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
            bt->sjw = btc->sjw_max;
        /* bt->sjw must not be higher than tseg2 */
        if (tseg2 < bt->sjw)
            bt->sjw = tseg2;
    }

    bt->brp = best_brp;

    /* real bitrate */
    bt->bitrate = CAN_CLK_FREQ / (bt->brp * (CAN_CALC_SYNC_SEG + tseg1 + tseg2));
    return FCAN_SUCCESS;
}
