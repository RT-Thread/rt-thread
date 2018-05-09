/*
 * Copyright (c) 2008-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file io.h
 * @brief Register access macros.
 *
 * @ingroup diag_init
 */
#ifndef __IO_H__
#define __IO_H__

#include "sdk_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdk.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @name Register read functions
//@{
#define reg8_read(addr)       *((volatile uint8_t *)(addr))
#define reg16_read(addr)      *((volatile uint16_t *)(addr))
#define reg32_read(addr)      *((volatile uint32_t *)(addr))
//@}

//! @name Register write functions
//@{
#define reg8_write(addr,val)  *((volatile uint8_t *)(addr)) = (val)
#define reg16_write(addr,val) *((volatile uint16_t *)(addr)) = (val)
#define reg32_write(addr,val) *((volatile uint32_t *)(addr)) = (val)
//@}

//! @name Memory read functions
//@{
#define mem8_read(addr)       *((volatile uint8_t *)(addr))
#define mem16_read(addr)      *((volatile uint16_t *)(addr))
#define mem32_read(addr)      *((volatile uint32_t *)(addr))
//@}

//! @name Memory write functions
//@{
#define mem8_write(addr,val)  *((volatile uint8_t *)(addr)) = (val)
#define mem16_write(addr,val) *((volatile uint16_t *)(addr)) = (val)
#define mem32_write(addr,val) *((volatile uint32_t *)(addr)) = (val)
//@}

//! @name Read functions
//@{
#define readb(a)        reg8_read(a)
#define readw(a)        reg16_read(a)
#define readl(a)        reg32_read(a)
//@}

//! @name Write functrions
//!
//! The prefered method to access registers.
//@{
#define writeb(v, a)    reg8_write(a, v)
#define writew(v, a)    reg16_write(a, v)
#define writel(v, a)    reg32_write(a, v)
//@}

//! @name Bit set/clear functions
//@{
#define  reg8setbit(addr,bitpos) \
         reg8_write((addr),(reg8_read((addr)) | (1<<(bitpos))))

#define  reg16setbit(addr,bitpos) \
         reg16_write((addr),(reg16_read((addr)) | (1<<(bitpos))))

#define  reg32setbit(addr,bitpos) \
         reg32_write((addr),(reg32_read((addr)) | (1<<(bitpos))))

#define  reg8clrbit(addr,bitpos) \
         reg8_write((addr),(reg8_read((addr)) & (0xFF ^ (1<<(bitpos)))))

#define  reg16clrbit(addr,bitpos) \
         reg16_write((addr),(reg16_read((addr)) & (0xFFFF ^ (1<<(bitpos)))))

#define  reg32clrbit(addr,bitpos) \
         reg32_write((addr),(reg32_read((addr)) & (0xFFFFFFFF ^ (1<<(bitpos)))))
//@}

//! @name Masked write functions
//@{
#define reg8_write_mask(addr, data, mask) \
        reg8_write((addr),((reg8_read(addr) & (~mask)) | (mask & data)))

#define reg16_write_mask(addr, data, mask) \
        reg16_write((addr),((reg16_read(addr) & (~mask)) | (mask & data)))

#define reg32_write_mask(addr, data, mask) \
        reg32_write((addr),((reg32_read(addr) & (~mask)) | (mask & data)))

#define gen_msk32(start, end)	((0xFFFFFFFF << (start)) ^ (0xFFFFFFFF << ((end + 1))))
#define reg32_set_field(addr, start, end, val) \
		reg32_write_mask(addr, (val) << (start), gen_msk32((start, end)))
//@}

/*!
 * This macro is used to get certain bit field from a number
 */
#define GET_FIELD(val, len, sh)          ((val >> sh) & ((1 << len) - 1))

/*!
 * This macro is used to set certain bit field inside a number
 */
#define SET_FIELD(val, len, sh, nval)    ((val & ~(((1 << len) - 1) << sh)) | (nval << sh))

#endif // __IO_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
