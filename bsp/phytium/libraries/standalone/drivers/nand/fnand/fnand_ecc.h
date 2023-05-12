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
 * Description:  This file is for ecc validation related api
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */

#ifndef FNAND_ECC_H
#define FNAND_ECC_H

#include "ftypes.h"
#include "fnand_hw.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C"
{
#endif

static inline void FNandEnableHwEcc(uintptr_t base_address)
{
    FNAND_SETBIT(base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_ECC_EN_MASK);
    
}


static inline void FNandDisableHwEcc(uintptr_t base_address)
{
    FNAND_CLEARBIT(base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_ECC_EN_MASK);
}

u32 FNandGetEccTotalLength(u32 bytes_per_page, u32 ecc_strength);
s32 FNandCorrectEcc(uintptr_t base_address, u32 ecc_step_size, u32 hw_ecc_steps, u8 *buf, u32 length);

#ifdef __cplusplus
}
#endif

#endif
