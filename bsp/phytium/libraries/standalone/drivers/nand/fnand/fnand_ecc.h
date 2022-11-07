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
 * FilePath: fnand_ecc.h
 * Date: 2022-05-12 11:17:42
 * LastEditTime: 2022-05-12 13:56:27
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef DRIVERS_NAND_FNAND_ECC_H
#define DRIVERS_NAND_FNAND_ECC_H

#include "ftypes.h"
#include "fnand_hw.h"
#include "stdio.h"

static inline void FNandEnableHwEcc(uintptr_t base_address)
{
    FNAND_SETBIT(base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_ECC_EN_MASK);
    // printf("base_address is %p ,value is 0x%x  \r\n",base_address,FNAND_READREG(base_address,FNAND_CTRL0_OFFSET));
}


static inline void FNandDisableHwEcc(uintptr_t base_address)
{
    FNAND_CLEARBIT(base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_ECC_EN_MASK);
}

u32 FNandGetEccTotalLength(u32 bytes_per_page, u32 ecc_strength);
s32 FNandCorrectEcc(uintptr_t base_address, u32 ecc_step_size, u32 hw_ecc_steps, u8 *buf, u32 length);
#endif
