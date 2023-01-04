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
 * FilePath: fadc_hw.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-25 11:45:05
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "fparameters.h"
#include "fadc_hw.h"
#include "stdio.h"

/**
 * @name: FAdcDump
 * @msg: debug register value for adc channel.
 * @param {uintptr} base_addr, base address of FADC controller
 * @param {u8} channel, adc channel number
 * @return {*}
 */
void FAdcDump(uintptr base_addr, u8 channel)
{
    printf("Off[0x%02x]: = 0x%08x\r\n", FADC_CTRL_REG_OFFSET, FADC_READ_REG32(base_addr, FADC_CTRL_REG_OFFSET));
    printf("Off[0x%02x]: = 0x%08x\r\n", FADC_INTER_REG_OFFSET, FADC_READ_REG32(base_addr, FADC_INTER_REG_OFFSET));
    printf("Off[0x%02x]: = 0x%08x\r\n", FADC_STATE_REG_OFFSET, FADC_READ_REG32(base_addr, FADC_STATE_REG_OFFSET));
    printf("Off[0x%02x]: = 0x%08x\r\n", FADC_INTRMASK_REG_OFFSET, FADC_READ_REG32(base_addr, FADC_INTRMASK_REG_OFFSET));
    printf("Off[0x%02x]: = 0x%08x\r\n", FADC_INTR_REG_OFFSET, FADC_READ_REG32(base_addr, FADC_INTR_REG_OFFSET));
    printf("Off[0x%02x]: = 0x%08x\r\n", FADC_COV_RESULT_REG_OFFSET(channel), FADC_READ_REG32(base_addr, FADC_COV_RESULT_REG_OFFSET(channel)));
    printf("Off[0x%02x]: = 0x%08x\r\n", FADC_FINISH_CNT_REG_OFFSET(channel), FADC_READ_REG32(base_addr, FADC_FINISH_CNT_REG_OFFSET(channel)));
    printf("Off[0x%02x]: = 0x%08x\r\n", FADC_HIS_LIMIT_REG_OFFSET(channel), FADC_READ_REG32(base_addr, FADC_HIS_LIMIT_REG_OFFSET(channel)));

    printf("\r\n");

}
