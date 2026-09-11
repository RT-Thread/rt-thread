/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-08-25     ox-horse         first version
 */

#include "femc_timing.h"

#ifdef BSP_USING_NAND

/*
 * FEMC NAND timing configuration (N32H49x).
 *
 * Timing values are in HCLK cycles, taken from the Nsing FEMC Nand_Flash
 * demo (FEMC_Nand_Init): SET=4, WAIT=6, HOLD=5, HIZ=5,
 * TCLR/TAR = CLE/ALE delay of 1 HCLK.
 *
 * Actual time (ns) = value * HCLK_period (ns). When porting to a different
 * system clock, recalculate HCLK period from RCC_Configuration() and adjust
 * all values below to satisfy the NAND datasheet timing.
 *
 * Registers written by FEMC_InitNand():
 *   FEMC_NCTRLx     <- WaitFeatureEnable | MemDataWidth | EccEnable |
 *                      EccPageSize | TCLRSetTime | TARSetTime
 *   FEMC_NCMEMTMx   <- CommSpaceTimingStruct (timing)
 *   FEMC_NATTMEMTMx <- AttrSpaceTimingStruct (timing)
 */
void FEMC_Nand_Timing_Config(FEMC_NandInitType *nandInit,
                             FEMC_NandTimingInitType *timing)
{
    /* Address setup time: 4 HCLK */
    timing->SetTime = FEMC_NAND_SETUP_TIME(0x4);
    /* Command assert width: 6 HCLK */
    timing->WaitSetTime = FEMC_NAND_WAIT_TIME(0x6);
    /* Address/data hold time: 5 HCLK */
    timing->HoldSetTime = FEMC_NAND_HOLD_TIME(0x5);
    /* Data bus HiZ time: 5 HCLK */
    timing->HiZSetTime = FEMC_NAND_HIZ_TIME(0x5);

    nandInit->CommSpaceTimingStruct = timing;
    nandInit->AttrSpaceTimingStruct = timing;

    /* CLE to RE delay (TCLR): 1 HCLK */
    nandInit->TCLRSetTime = FEMC_NAND_CLE_DELAY_1HCLK;
    /* ALE to RE delay (TAR): 1 HCLK */
    nandInit->TARSetTime = FEMC_NAND_ALE_DELAY_1HCLK;
}

#endif /* BSP_USING_NAND */
