/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-07-10     ox-horse         first version
 */

#ifndef __FEMC_TIMING_H__
#define __FEMC_TIMING_H__

#include "board.h"

/*
 * FEMC_TimingInitType comes from the SoC SDK; pull in the peripheral header
 * itself instead of relying on board.h to have declared it.
 */
#if defined(SOC_SERIES_N32H7xx)
#include "n32h7xx_femc.h"
#elif defined(SOC_SERIES_N32H49x)
#include "n32h49x_femc.h"
#elif defined(SOC_SERIES_N32H47x_48x)
#include "n32h47x_48x_femc.h"
#endif

void FEMC_Nnad_Timing_Config(FEMC_TimingInitType *TimingCfg);

#ifdef __cplusplus
}
#endif

#endif /* __FEMC_TIMING_H__ */
