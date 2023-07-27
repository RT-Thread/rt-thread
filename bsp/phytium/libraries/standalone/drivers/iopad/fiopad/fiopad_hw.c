/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * FilePath: fiopad_hw.c
 * Date: 2021-04-29 10:21:53
 * LastEditTime: 2022-02-18 08:29:20
 * Description:  This files is for the iopad register related functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhangyan   2023/7/3    first release
 */

/***************************** Include Files *********************************/
#include "fparameters.h"
#include "fiopad_hw.h"
#include "fdebug.h"

#define FIOPAD_DEBUG_TAG "FIOPAD_HW"
#define FIOPAD_ERROR(format, ...)   FT_DEBUG_PRINT_E(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_WARN(format, ...)    FT_DEBUG_PRINT_W(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_INFO(format, ...)    FT_DEBUG_PRINT_I(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)
#define FIOPAD_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FIOPAD_DEBUG_TAG, format, ##__VA_ARGS__)

/**
 * @name: FIOPadDump
 * @msg: print information of all iopad
 * @return {*}
 */
void FIOPadDump(uintptr base_addr)
{
    uintptr beg_off = 0x0000U;
    uintptr end_off = 0x024CU;
    uintptr off;
    FIOPadFunc pin_func;
    FIOPadDrive pin_drv;
    FIOPadPull pin_pull;
    u32 pin_reg_off;
    const char *pull_state[FIOPAD_NUM_OF_PULL] = {"none", "down", "up"};

    FIOPAD_DEBUG("Pad Func Info...");
    for (off = beg_off; off <= end_off; off += 4U)
    {
        pin_reg_off = off;
        u32 reg_val = FIOPAD_READ_REG32(base_addr, pin_reg_off);
        pin_func = FIOPAD_REG0_FUNC_GET(reg_val);
        pin_pull = FIOPAD_REG0_PULL_GET(reg_val);
        pin_drv = FIOPAD_REG0_DRIVE_GET(reg_val);

        FIOPAD_DEBUG("  [0x%x] func: %d, ds: %d, pull: %s ",
                     pin_reg_off,
                     pin_func,
                     pin_drv,
                     pull_state[pin_pull]);
    }

    return;
}