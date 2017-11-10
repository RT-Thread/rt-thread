/*
 * Copyright (C) 2011-2012, Freescale Semiconductor, Inc. All Rights Reserved
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
*/

/*!
 * @file functions.h
 * @brief This header file contains functions info.
 *
 */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//----------------------------------------------------------------------
//  Some Genaral Macros
//----------------------------------------------------------------------
//#define FALSE 0
//#define TRUE  1

#define DUMMY_INFO 0xf00f00

#define reg8_read(addr)       *((BYTE *)(addr))
#define reg16_read(addr)      *((HALF *)(addr))
#define reg32_read(addr)      *(WORD *)((addr))

#define reg32_read_bit(addr,bitpos) (reg32_read(addr) & (1<<(bitpos)))

#define reg8_write(addr,val)  *((BYTE *)(addr)) = (val)
#define reg16_write(addr,val) *((HALF *)(addr)) = (val)
#define reg32_write(addr,val) *((WORD *)(addr)) = (val)

#define mem8_read(addr)       *((BYTE *)(addr))
#define mem16_read(addr)      *((HALF *)(addr))
#define mem32_read(addr)      *(WORD *)((addr))

#define mem8_write(addr,val)  *((BYTE *)(addr)) = (val)
#define mem16_write(addr,val) *((HALF *)(addr)) = (val)
#define mem32_write(addr,val) *((WORD *)(addr)) = (val)

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

// #####   EXPORTED TYPE DEFINITIONS   ################################################# {{{1

typedef volatile unsigned long WORD;
typedef volatile unsigned short HALF;
typedef volatile unsigned char BYTE;

//----------------------------------------------------------------------
//  Write With Mask (write only certain bits)
//----------------------------------------------------------------------
void reg8_write_mask(WORD addr, BYTE wdata, BYTE mask);
void reg16_write_mask(WORD addr, HALF wdata, HALF mask);
void reg32_write_mask(WORD addr, WORD wdata, WORD mask);

#endif //FUNCTIONS_H
