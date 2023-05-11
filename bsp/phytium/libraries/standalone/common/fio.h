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
 * FilePath: fio.h
 * Date: 2021-04-07 09:53:07
 * LastEditTime: 2022-02-18 08:24:01
 * Description:  This file is for general reigster io functions
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu   2021/04/07  init
 * 1.1  zhugengyu   2022/02/18  add Phytium Public License 1.0
 */

#ifndef FIO_H
#define FIO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ftypes.h"

static _INLINE u8 FtIn8(uintptr addr)
{
    return *(volatile u8 *)addr;
}

static _INLINE u16 FtIn16(uintptr addr)
{
    return *(volatile u16 *)addr;
}

static _INLINE u32 FtIn32(uintptr addr)
{
    return *(volatile u32 *)addr;
}

static _INLINE u64 FtIn64(uintptr addr)
{
    return *(volatile u64 *)addr;
}

static _INLINE void FtOut8(uintptr addr, u8 value)
{
    volatile u8 *local_addr = (volatile u8 *)addr;
    *local_addr = value;
}

static _INLINE void FtOut16(uintptr addr, u16 value)
{
    volatile u16 *local_addr = (volatile u16 *)addr;
    *local_addr = value;
}

static _INLINE void FtOut32(uintptr addr, u32 value)
{
    volatile u32 *local_addr = (volatile u32 *)addr;
    *local_addr = value;
}

static _INLINE void FtOut64(uintptr addr, u64 value)
{
    volatile u64 *local_addr = (volatile u64 *)addr;
    *local_addr = value;
}

static _INLINE void FtSetBit32(uintptr addr, u32 value)
{
    volatile u32 last_value;
    last_value = FtIn32(addr);
    last_value |= value;
    FtOut32(addr, last_value);
}

static _INLINE void FtClearBit32(uintptr addr, u32 value)
{
    volatile u32 last_value;
    last_value = FtIn32(addr);
    last_value &= ~value;
    FtOut32(addr, last_value);
}

static _INLINE void FtToggleBit32(uintptr addr, u32 toggle_pos)
{
    volatile u32 value;
    value = FtIn32(addr);
    value ^= (1 << toggle_pos);
    FtOut32(addr, value);
}

static _INLINE u16 FtEndianSwap16(u16 data)
{
    return (u16)(((data & 0xFF00U) >> 8U) | ((data & 0x00FFU) << 8U));
}
#define FT_WRITE32(_reg, _val) (*(volatile uint32_t *)&_reg = _val)
#define FT_READ32(_reg) (*(volatile uint32_t *)&_reg)

#ifdef __cplusplus
}
#endif

#endif // !
