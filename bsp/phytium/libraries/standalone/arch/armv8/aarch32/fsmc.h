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
 * FilePath: fsmc.h
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:30:49
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#ifndef BSP_ARCH_ARMV8_AARCH32_SMC_H
#define BSP_ARCH_ARMV8_AARCH32_SMC_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "ftypes.h"

typedef struct
{
    /* data */
    u32 function_identifier;
    u32 a1;
    u32 a2;
    u32 a3;
    u32 a4;
    u32 a5;
    u32 a6;

} FSmc_Data_t;

void FSmcCall(FSmc_Data_t *Input, FSmc_Data_t *Output);

#ifdef __cplusplus
}
#endif

#endif // !FT_SMC_H
