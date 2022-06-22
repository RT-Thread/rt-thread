/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-07     thread-liu   first version
 */

#ifndef __DRV_DFSDM_H__
#define __DRV_DFSDM_H__

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SaturaLH(N, L, H) (((N)<(L))?(L):(((N)>(H))?(H):(N)))

#ifdef __cplusplus
}
#endif

#endif
