/*
 * Copyright 2025 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.clock"
#endif

/* ROM initializes PLLs with default frequencies except audio/video/ext */
volatile uint32_t g_clockSourceFreq[kCLOCK_Ext + 1] = {
    24000000U,   /* kCLOCK_Osc24M          */
    2000000000U, /* kCLOCK_ArmPll          */
    2000000000U, /* kCLOCK_ArmPllOut       */
    1000000000U, /* kCLOCK_DramPll         */
    1000000000U, /* kCLOCK_DramPllOut      */
    4000000000U, /* kCLOCK_SysPll1         */
    1000000000U, /* kCLOCK_SysPll1Pfd0     */
    500000000U,  /* kCLOCK_SysPll1Pfd0Div2 */
    800000000U,  /* kCLOCK_SysPll1Pfd1     */
    400000000U,  /* kCLOCK_SysPll1Pfd1Div2 */
    625000000U,  /* kCLOCK_SysPll1Pfd2     */
    312500000U,  /* kCLOCK_SysPll1Pfd2Div2 */
    0U,          /* kCLOCK_AudioPll1       */
    0U,          /* kCLOCK_AudioPll1Out    */
    0U,          /* kCLOCK_VideoPll1       */
    0U,          /* kCLOCK_VideoPll1Out    */
    0U           /* kCLOCK_Ext             */
};

const clock_name_t s_clockSourceName[][4] = {
    /*SRC0,         SRC1,                   SRC2,                   SRC3,            */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Arm A55 Periph */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Arm A55 MTR BUS */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Arm A55 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* M33 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Sentinel */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Bus Wakeup */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Bus Aon */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Wakeup Axi */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Swo Trace */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* M33 Systick */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Flexio1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Flexio2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpit1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpit2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lptmr1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lptmr2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_AudioPll1Out, kCLOCK_Ext},                    /* Tpm1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_AudioPll1Out, kCLOCK_Ext},                    /* Tpm2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_AudioPll1Out, kCLOCK_Ext},                    /* Tpm3 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_AudioPll1Out, kCLOCK_Ext},                    /* Tpm4 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_AudioPll1Out, kCLOCK_Ext},                    /* Tpm5 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_AudioPll1Out, kCLOCK_Ext},                    /* Tpm6 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Flexspi1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Can1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Can2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpuart1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpuart2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpuart3 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpuart4 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpuart5 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpuart6 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpuart7 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpuart8 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpi2c1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpi2c2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpi2c3 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpi2c4 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpi2c5 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpi2c6 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpi2c7 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpi2c8 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpspi1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpspi2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpspi3 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpspi4 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpspi5 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpspi6 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpspi7 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Lpspi8 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* I3c1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* I3c2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Usdhc1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Usdhc2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Usdhc3 */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_Ext},                   /* Sai1 */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_Ext},                   /* Sai2 */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_Ext},                   /* Sai3 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_AudioPll1Out},            /* Ccm Cko1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_VideoPll1Out},            /* Ccm Cko2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_AudioPll1Out},            /* Ccm Cko3 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_VideoPll1Out},            /* Ccm Cko4 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Hsio */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Hsio Usb Test 60M */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Hsio Acscan 80M */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_SysPll1Pfd2},           /* Hsio Acscan 480M */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Nic */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Nic Apb */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Ml Apb */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Ml */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Media Axi */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Media Apb */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_SysPll1Pfd0},           /* Media Ldb */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_SysPll1Pfd0},           /* Media Disp Pix */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_SysPll1Pfd0},           /* Cam Pix */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_SysPll1Pfd0},           /* Mipi Test Byte */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_SysPll1Pfd0},           /* Mipi Phy Cfg */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0, kCLOCK_SysPll1Pfd1, kCLOCK_SysPll1Pfd2},             /* Dram Alt */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_SysPll1Pfd2Div2}, /* Dram Apb */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Adc */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_Ext},                   /* Pdm */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Tstmr1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Tstmr2 */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_Ext},                   /* Mqs1 */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_Ext},                   /* Mqs2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_SysPll1Pfd2Div2}, /* Audio XCVR */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_Ext},                   /* Spdif */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_SysPll1Pfd2Div2}, /* Enet */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Enet Timer1 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Enet Timer2 */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_SysPll1Pfd2Div2}, /* Enet Ref */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Enet Ref Phy */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* I3c1 Slow */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* I3c2 Slow */
    {kCLOCK_Osc24M, kCLOCK_SysPll1Pfd0Div2, kCLOCK_SysPll1Pfd1Div2, kCLOCK_VideoPll1Out},    /* Usb Phy Burunin */
    {kCLOCK_Osc24M, kCLOCK_AudioPll1Out, kCLOCK_VideoPll1Out, kCLOCK_SysPll1Pfd2}            /* Pal Came Scan */
};

uint32_t CLOCK_GetIpFreq(clock_root_t name)
{
    clock_name_t clock;
    uint32_t mux;
    uint32_t div;

    mux = CLOCK_GetRootClockMux(name);
    div = CLOCK_GetRootClockDiv(name);

    clock = CLOCK_GetRootClockSource(name, mux);
    assert(clock <= kCLOCK_Ext);

    return g_clockSourceFreq[clock] / div;
}
