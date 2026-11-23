/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "clock_config.h"

#include "fsl_clock.h"

void BOARD_InitBootClocks(void)
{
    BOARD_BootClockFROHF72M();
}

void BOARD_BootClockFROHF72M(void)
{
    /* One wait state is required before raising the core clock to 72 MHz. */
    FMU0->FCTRL = (FMU0->FCTRL & ~FMU_FCTRL_RWSC_MASK) | FMU_FCTRL_RWSC(1U);

    CLOCK_SetClockDiv(kCLOCK_DivFRO_LF, 1U);
    CLOCK_SetupFRO12MClocking();
    CLOCK_SetClockDiv(kCLOCK_DivFRO_HF, 1U);
    CLOCK_SetupFROHFClocking(BOARD_BOOTCLOCKFROHF72M_CORE_CLOCK);
    CLOCK_SetClockDiv(kCLOCK_DivAHBCLK, 1U);
    CLOCK_AttachClk(kFRO_HF_to_MAIN_CLK);

    SystemCoreClock = BOARD_BOOTCLOCKFROHF72M_CORE_CLOCK;
}
