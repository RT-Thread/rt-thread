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
 * FilePath: fgpio_selftest.c
 * Date: 2022-06-17 14:32:12
 * LastEditTime: 2022-06-17 14:32:12
 * Description:  This files is for dumping gpio register info 
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/3/1     init commit
 * 2.0   zhugengyu  2022/7/1     support e2000
 */
/***************************** Include Files *********************************/
#include "fdrivers_port.h"
#include "fassert.h"

#include "fgpio_hw.h"
#include "fgpio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGPIO_DEBUG_TAG "FGPIO-TEST"
#define FGPIO_ERROR(format, ...) FT_DEBUG_PRINT_E(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGPIO_WARN(format, ...)  FT_DEBUG_PRINT_W(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGPIO_INFO(format, ...)  FT_DEBUG_PRINT_I(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGPIO_DEBUG(format, ...) FT_DEBUG_PRINT_D(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)

#define FGPIO_DUMPER(base_addr, reg_off, reg_name) \
    FGPIO_DEBUG("\t\t[%s]@0x%x\t=\t0x%x", reg_name, (reg_off), FGpioReadReg32((base_addr), (reg_off)))
/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/

/**
 * @name: FGpioDumpRegisters
 * @msg: 打印GPIO控制寄存器信息
 * @return {NONE}
 * @param {uintptr} base_addr, GPIO控制器基地址
 */
void FGpioDumpRegisters(uintptr base_addr)
{
    FASSERT(0 != base_addr);

    FGPIO_DEBUG("Dump register info @0x%x", base_addr);
    FGPIO_DUMPER(base_addr, FGPIO_SWPORTA_DR_OFFSET, "dr");
    FGPIO_DUMPER(base_addr, FGPIO_SWPORTA_DDR_OFFSET, "ddr");
    FGPIO_DUMPER(base_addr, FGPIO_EXT_PORTA_OFFSET, "ext_porta");
#if defined(FGPIO_VERSION_1) /* D2000 FT2000/4 */
    FGPIO_DUMPER(base_addr, FGPIO_SWPORTB_DR_OFFSET, "portb_dr");
    FGPIO_DUMPER(base_addr, FGPIO_SWPORTB_DDR_OFFSET, "portb_ddr");
    FGPIO_DUMPER(base_addr, FGPIO_EXT_PORTB_OFFSET, "ext_portb");
#endif
    FGPIO_DUMPER(base_addr, FGPIO_INTEN_OFFSET, "inten");
    FGPIO_DUMPER(base_addr, FGPIO_INTMASK_OFFSET, "intmask");
    FGPIO_DUMPER(base_addr, FGPIO_INTTYPE_LEVEL_OFFSET, "intr_level");
    FGPIO_DUMPER(base_addr, FGPIO_INT_POLARITY_OFFSET, "intr_polarity");
    FGPIO_DUMPER(base_addr, FGPIO_INTSTATUS_OFFSET, "intr_status");
    FGPIO_DUMPER(base_addr, FGPIO_RAW_INTSTATUS_OFFSET, "raw_int_status");
    FGPIO_DUMPER(base_addr, FGPIO_LS_SYNC_OFFSET, "ls_sync");
    FGPIO_DUMPER(base_addr, FGPIO_DEBOUNCE_OFFSET, "debounce");
    FGPIO_DUMPER(base_addr, FGPIO_PORTA_EOI_OFFSET, "porta_eoi");

    return;
}
