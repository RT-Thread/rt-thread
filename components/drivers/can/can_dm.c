/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "can_dm.h"

static const rt_uint8_t dlc2len[] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
};

rt_uint8_t can_dlc2len(rt_uint8_t can_dlc)
{
    return dlc2len[can_dlc & 0x0F];
}

static const rt_uint8_t len2dlc[] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8,      /* 0 - 8 */
    9, 9, 9, 9,                     /* 9 - 12 */
    10, 10, 10, 10,                 /* 13 - 16 */
    11, 11, 11, 11,                 /* 17 - 20 */
    12, 12, 12, 12,                 /* 21 - 24 */
    13, 13, 13, 13, 13, 13, 13, 13, /* 25 - 32 */
    14, 14, 14, 14, 14, 14, 14, 14, /* 33 - 40 */
    14, 14, 14, 14, 14, 14, 14, 14, /* 41 - 48 */
    15, 15, 15, 15, 15, 15, 15, 15, /* 49 - 56 */
    15, 15, 15, 15, 15, 15, 15, 15, /* 57 - 64 */
};

rt_uint8_t can_len2dlc(rt_uint8_t len)
{
    if (len <= 64)
    {
        return len2dlc[len];
    }

    return 0xf;
}
