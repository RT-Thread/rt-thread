/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-08-25     ox-horse         first version
 */

#ifndef __FEMC_TIMING_H__
#define __FEMC_TIMING_H__

#include "board.h"

/*
 * Configure FEMC NAND timing parameters (N32H49x).
 *
 * This fills the timing-related fields of the NAND init structures:
 *   - timing: SET/WAIT/HOLD/HIZ (then linked to nandInit's
 *     CommSpaceTimingStruct / AttrSpaceTimingStruct)
 *   - nandInit: TCLRSetTime / TARSetTime (CLE/ALE to RE delay)
 *
 * @note  structures are of type FEMC_NandInitType / FEMC_NandTimingInitType
 *        (N32H49x SDK), which differ from N32H7xx FEMC_TimingInitType.
 */
void FEMC_Nand_Timing_Config(FEMC_NandInitType *nandInit,
                             FEMC_NandTimingInitType *timing);

#ifdef __cplusplus
}
#endif

#endif /* __FEMC_TIMING_H__ */
