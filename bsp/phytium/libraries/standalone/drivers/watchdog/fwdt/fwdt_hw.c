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
 * FilePath: fwdt_hw.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:23:08
 * Description:  This file is for wdt register implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/15   init commit
 */

/***************************** Include Files *********************************/
#include <stdio.h>
#include "fparameters.h"
#include "fwdt_hw.h"
#include "fdebug.h"


/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

#define FWDT_DEBUG_TAG "FWDT_HW"
#define FWDT_ERROR(format, ...)   FT_DEBUG_PRINT_E(FWDT_DEBUG_TAG, format, ##__VA_ARGS__)
#define FWDT_WARN(format, ...)   FT_DEBUG_PRINT_W(FWDT_DEBUG_TAG, format, ##__VA_ARGS__)
#define FWDT_INFO(format, ...) FT_DEBUG_PRINT_I(FWDT_DEBUG_TAG, format, ##__VA_ARGS__)
#define FWDT_DEBUG(format, ...) FT_DEBUG_PRINT_D(FWDT_DEBUG_TAG, format, ##__VA_ARGS__)

/**
 * @name: FWdtDump
 * @msg: debug register value for wdt.
 * @param {uintptr} base_addr, base address of FWDT controller
 * @return {*}
 */
void FWdtDump(uintptr base_addr)
{
	FWDT_DEBUG("Off[0x%x]: = 0x%08x\r\n", base_addr + FWDT_GWDT_WRR, FWDT_READ_REG32(base_addr, FWDT_GWDT_WRR));
	FWDT_DEBUG("Off[0x%x]: = 0x%08x\r\n", base_addr + FWDT_GWDT_W_IIR, FWDT_READ_REG32(base_addr, FWDT_GWDT_W_IIR));

    base_addr = FWDT_CONTROL_BASE_ADDR(base_addr);
	FWDT_DEBUG("Off[0x%x]: = 0x%08x\r\n", base_addr + FWDT_GWDT_WCS, FWDT_READ_REG32(base_addr, FWDT_GWDT_WCS));
	FWDT_DEBUG("Off[0x%x]: = 0x%08x\r\n", base_addr + FWDT_GWDT_WOR, FWDT_READ_REG32(base_addr, FWDT_GWDT_WOR));
	FWDT_DEBUG("Off[0x%x]: = 0x%08x\r\n", base_addr + FWDT_GWDT_WCVL, FWDT_READ_REG32(base_addr, FWDT_GWDT_WCVL));
	FWDT_DEBUG("Off[0x%x]: = 0x%08x\r\n", base_addr + FWDT_GWDT_WCVH, FWDT_READ_REG32(base_addr, FWDT_GWDT_WCVH));

	FWDT_DEBUG("\r\n");
   
}
