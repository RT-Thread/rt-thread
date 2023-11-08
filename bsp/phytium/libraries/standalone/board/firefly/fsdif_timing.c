/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fsdif_timing.c
 * Date: 2023-07-25 14:53:42
 * LastEditTime: 2023-07-25 08:25:29
 * Description:  This file is for sdif timing function
 *
 * Modify History:
 *  Ver   Who        Date       Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/9/25   init commit
 */

#include "fparameters.h"
#include "fiopad.h"
#include "fsdif_timing.h"
#include "fio_mux.h"

#define FSDIF_0_SD_CCLK_OUT_DELAY     FIOPAD_AJ49_REG1_OFFSET
#define FSDIF_1_SD_CCLK_OUT_DELAY     FIOPAD_J57_REG1_OFFSET

extern FIOPadCtrl iopad_ctrl;

static void FSdifSetSDIFDelay(u32 sdif_id)
{
    /*
        for SD-0: 0x32b31120 = 0x1f00
            SD-1: 0x32b31178 = 0x1f00
    */

    u32 reg;

    if (FSDIF0_ID == sdif_id)
        reg = FSDIF_0_SD_CCLK_OUT_DELAY;
    else
        reg = FSDIF_1_SD_CCLK_OUT_DELAY;

    FIOPadSetDelay(&iopad_ctrl, reg, FIOPAD_OUTPUT_DELAY, FIOPAD_DELAY_COARSE_TUNING, FIOPAD_DELAY_1);
    FIOPadSetDelay(&iopad_ctrl, reg, FIOPAD_OUTPUT_DELAY, FIOPAD_DELAY_FINE_TUNING, FIOPAD_DELAY_7);
    FIOPadSetDelayEn(&iopad_ctrl, reg, FIOPAD_OUTPUT_DELAY, TRUE);
}

static void FSdifUnsetSDIFDelay(u32 sdif_id)
{
    /*
        for SD-0: 0x32b31120 = 0x0
            SD-1: 0x32b31178 = 0x0
    */
    FASSERT(iopad_ctrl.is_ready);
    u32 reg;

    if (FSDIF0_ID == sdif_id)
        reg = FSDIF_0_SD_CCLK_OUT_DELAY;
    else
        reg = FSDIF_1_SD_CCLK_OUT_DELAY;

    FIOPadSetDelay(&iopad_ctrl, reg, FIOPAD_OUTPUT_DELAY, FIOPAD_DELAY_COARSE_TUNING, FIOPAD_DELAY_NONE);
    FIOPadSetDelay(&iopad_ctrl, reg, FIOPAD_OUTPUT_DELAY, FIOPAD_DELAY_FINE_TUNING, FIOPAD_DELAY_NONE);
    FIOPadSetDelayEn(&iopad_ctrl, reg, FIOPAD_OUTPUT_DELAY, FALSE);
}

/* default timing settings in e2000q demo board */
static FSdifTiming mmc_sd_400khz = 
{
    .use_hold = 1,
    .clk_div = 0x7e7dfa,
    .clk_src = 0x000502,
    .shift   = 0x0,
    .pad_delay = FSdifUnsetSDIFDelay,
};

static FSdifTiming sd_25mhz = 
{
    .use_hold = 1,
    .clk_div = 0x030204,
    .clk_src = 0x000302,
    .shift   = 0x0,
    .pad_delay = FSdifUnsetSDIFDelay,
};

static FSdifTiming sd_50mhz = 
{
    .use_hold = 0,
    .clk_div = 0x050408,
    .clk_src = 0x000502,
    .shift   = 0x0,
    .pad_delay = FSdifSetSDIFDelay
};

static FSdifTiming sd_100mhz =
{
    .use_hold = 0,
    .clk_div = 0x010002,
    .clk_src = 0x000202,
    .shift   = 0x0,
    .pad_delay = FSdifSetSDIFDelay,
};

static FSdifTiming mmc_26mhz =
{
    .use_hold = 1,
    .clk_div = 0x030204,
    .clk_src = 0x000302,
    .shift   = 0x0,
    .pad_delay = FSdifSetSDIFDelay,
};

static FSdifTiming mmc_52mhz = 
{
    .use_hold = 0,
    .clk_div = 0x030204,
    .clk_src = 0x000202,
    .shift   = 0x0,
    .pad_delay = FSdifSetSDIFDelay,
};

const FSdifTiming *FSdifGetTimingSetting(FSdifClkSpeed clock_freq, boolean non_removable)
{
    const FSdifTiming * tuning = NULL;

    if (clock_freq == FSDIF_CLK_SPEED_400KHZ)
    {
        return &mmc_sd_400khz;
    }

    if (non_removable)
    {
        /* for emmc card */
        switch (clock_freq)
        {
            case FSDIF_CLK_SPEED_26_MHZ:
                tuning = &mmc_26mhz;
                break;
            case FSDIF_CLK_SPEED_52_MHZ:
                tuning = &mmc_52mhz;
                break;
            /* TODO: more clock freq for tuning */
        }
    }
    else
    {
        /* for sd card */
        switch (clock_freq)
        {
            case FSDIF_CLK_SPEED_25_MHZ:
                tuning = &sd_25mhz;
                break;
            case FSDIF_CLK_SPEED_50_MHZ:
                tuning = &sd_50mhz;
                break;
            case FSDIF_CLK_SPEED_100_MHZ:
                tuning = &sd_100mhz;
                break;
            /* TODO: more clock freq for tuning */
        }
    }

    return tuning;
}

void FSdifTimingInit(void)
{
    FIOMuxInit();
}

void FSdifTimingDeinit(void)
{
    FIOMuxDeInit();
}