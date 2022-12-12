/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:29:06
 * @Description:  This files is for general reigster io functions
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_IO_H
#define FT_IO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"

#if defined(__GNUC__) || defined(__ICCARM__) || defined(__MICROBLAZE__)
#define INLINE inline
#else
#define INLINE __inline
#endif

    /**
     * @name: Ft_in8
     * @msg:  Read byte value
     * @in param {UINTPTR}: Addr 需要读取的地址
     * @return {u8} Byte Value
     */
    static INLINE u8 Ft_in8(FT_IN UINTPTR Addr)
    {
        return *(volatile u8 *)Addr;
    }

    /**
     * @name: Ft_in16
     * @msg:  Read half-word value
     * @in param {UINTPTR}: Addr 需要读取的地址
     * @return {u16} Half-word Value
     */
    static INLINE u16 Ft_in16(FT_IN UINTPTR Addr)
    {
        return *(volatile u16 *)Addr;
    }

    /**
     * @name: Ft_in32
     * @msg:  Read word value
     * @in param {UINTPTR}: Addr 需要读取的地址
     * @return {u16} Word Value
     */
    static INLINE u32 Ft_in32(FT_IN UINTPTR Addr)
    {
        return *(volatile u32 *)Addr;
    }

    /**
     * @name: Ft_in64
     * @msg:  Read u64 value
     * @in param {UINTPTR}: Addr 需要读取的地址
     * @return {u16} u64 Value
     */
    static INLINE u64 Ft_in64(FT_IN UINTPTR Addr)
    {
        return *(volatile u64 *)Addr;
    }

    /**
     * @name: Ft_out8
     * @msg:  write byte value
     * @in param {UINTPTR}: Addr 需要写入的地址
     * @in param {u8}: Need write value
     * @return {*}
     */
    static INLINE void Ft_out8(FT_IN UINTPTR Addr, FT_IN u8 Value)
    {
        volatile u8 *LocalAddr = (volatile u8 *)Addr;
        *LocalAddr = Value;
    }

    /**
     * @name: Ft_out16
     * @msg: write half-word value
     * @in param {UINTPTR}: Addr 需要写入的地址
     * @in param {u16}: Need write value
     * @return {*}
     */
    static INLINE void Ft_out16(FT_IN UINTPTR Addr, FT_IN u16 Value)
    {
        volatile u16 *LocalAddr = (volatile u16 *)Addr;
        *LocalAddr = Value;
    }

    /**
     * @name: Ft_out32
     * @msg: write half-word value
     * @in param {UINTPTR}: Addr 需要写入的地址
     * @in param {u32}: Need write value
     * @return {*}
     */
    static INLINE void Ft_out32(FT_IN UINTPTR Addr, FT_IN u32 Value)
    {
        volatile u32 *LocalAddr = (volatile u32 *)Addr;
        *LocalAddr = Value;
    }

    /**
     * @name: Ft_out64
     * @msg: write u64 value
     * @in param {UINTPTR}: Addr 需要写入的地址
     * @in param {u64}: Need write value
     * @return {*}
     */
    static INLINE void Ft_out64(FT_IN UINTPTR Addr, FT_IN u64 Value)
    {
        volatile u64 *LocalAddr = (volatile u64 *)Addr;
        *LocalAddr = Value;
    }

    /**
     * @name: Ft_setBit32
     * @msg:
     * @in param {FT_INUINTPTR} addr
     * @in param {FT_INu32} offset
     * @in param {FT_INu32} value
     */
    static INLINE void Ft_setBit32(FT_IN UINTPTR addr, FT_IN u32 value)
    {
        u32 lastValue;
        lastValue = Ft_in32(addr);
        lastValue |= value;
        Ft_out32(addr, lastValue);
    }

    /**
     * @name: Ft_clearBit32
     * @msg:
     * @in param:
     * @inout param:
     * @out param:
     * @return {*}
     * @param {FT_INUINTPTR} addr
     * @param {FT_INu32} value
     */
    static INLINE void Ft_clearBit32(FT_IN UINTPTR addr, FT_IN u32 value)
    {
        u32 lastValue;
        lastValue = Ft_in32(addr);
        lastValue &= ~value;
        Ft_out32(addr, lastValue);
    }

#ifdef __cplusplus
}
#endif

#endif // !
