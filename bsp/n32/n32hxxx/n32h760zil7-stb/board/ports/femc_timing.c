/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-07-10     ox-horse         first version
 */

#include "femc_timing.h"

#ifdef BSP_USING_NAND

/*
 * FEMC NAND timing configuration.
 *
 * All timing values below are in FEMC_CLK cycles.
 * Actual time (ns) = timing_value * FEMC_CLK_period (ns).
 *
 * Clock derivation (this board):
 *   RCC_ConfigFEMCM1Clk(RCC_FEMCCLK_SRC_AXIDIV, RCC_FEMCCLK_AXIDIV3)
 *   AXI_CLK = 300 MHz
 *   FEMC_CLK = AXI_CLK / 3 = 100 MHz
 *   FEMC_CLK period = 10 ns
 *
 * When porting to a different clock configuration or NAND part, recalculate
 * FEMC_CLK period from RCC_Configuration() and adjust all values below.
 *
 * ---------------------------------------------------------------------------
 *  NAND Interface Timing Parameters
 * ---------------------------------------------------------------------------
 *
 *  Trc     Read cycle time.
 *          Range: 2 .. 15.
 *
 *  Twc     Write cycle time.
 *          Range: 2 .. 15.
 *
 *  Tcere   NOE (read enable) assertion delay from NCE asserted.
 *          Range: 1 .. 7.
 *
 *  Twp     NWE (write enable) pulse width.
 *          Range: 1 .. 7.
 *
 *  Tpcclr  Extra cycles delay between a command being latched (CLE High)
 *          and the start (NCE asserted) of a data-phase command.
 *          Range: 0 .. 7.
 *
 *  Ttrar   Extra cycles delay between ALE falling and the start of a
 *          NWE data-phase command.
 *          Range: 0 .. 7.
 *
 *  Twerr   Delay cycles between a data-phase command and the assertion
 *          of the other data strobe.
 *          Range: 0 .. 15.
 * ---------------------------------------------------------------------------
 */
void FEMC_Nnad_Timing_Config(FEMC_TimingInitType *TimingCfg)
{
    /* 12-cycle * 10ns = 120ns */
    TimingCfg->Trc = 12;
    /* 12-cycle * 10ns = 120ns */
    TimingCfg->Twc = 12;
    /* 6-cycle * 10ns = 60ns */
    TimingCfg->Tcere = 6;
    /* 4-cycle * 10ns = 40ns */
    TimingCfg->Twp = 4;
    /* 2-cycle * 10ns = 20ns */
    TimingCfg->Tpcclr = 2;
    /* 2-cycle * 10ns = 20ns */
    TimingCfg->Ttrar = 2;
    /* 0-cycle * 10ns = 0ns */
    TimingCfg->Twerr = 0;
}

#endif /* BSP_USING_NAND */

