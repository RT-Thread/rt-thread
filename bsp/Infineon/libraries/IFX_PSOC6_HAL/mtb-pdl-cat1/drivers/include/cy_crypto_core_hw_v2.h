/***************************************************************************//**
* \file cy_crypto_core_hw_v2.h
* \version 2.70
*
* \brief
*  This file provides constants and function prototypes
*  for the Vector Unit functions in the Crypto block driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/


#if !defined (CY_CRYPTO_CORE_HW_V2_H)
#define CY_CRYPTO_CORE_HW_V2_H

#include "cy_crypto_core_hw.h"

#if defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V2_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 3, \
'CRYPTO_Type will typecast to either CRYPTO_V1_Type or CRYPTO_V2_Type but not both on PDL initialization based on the target device at compile time.');

/*
 Register buffer block identifiers:
    "0": block0[127:0] = reg_buff[0*128+127:0*128]
    "1": block1[127:0] = reg_buff[1*128+127:1*128]
    "2": block2[127:0] = reg_buff[2*128+127:2*128]
    "3": block3[127:0] = reg_buff[3*128+127:3*128]
    "4": block4[127:0] = reg_buff[4*128+127:4*128]
    "5": block5[127:0] = reg_buff[5*128+127:5*128]
    "6": block6[127:0] = reg_buff[6*128+127:6*128]
    "7": block7[127:0] = reg_buff[7*128+127:7*128]
    "8": load  FIFO 0
    "9": load  FIFO 1
   "12": store FIFO
*/

#define CY_CRYPTO_V2_RB_BLOCK0             (0u)
#define CY_CRYPTO_V2_RB_BLOCK1             (1u)
#define CY_CRYPTO_V2_RB_BLOCK2             (2u)
#define CY_CRYPTO_V2_RB_BLOCK3             (3u)
#define CY_CRYPTO_V2_RB_BLOCK4             (4u)
#define CY_CRYPTO_V2_RB_BLOCK5             (5u)
#define CY_CRYPTO_V2_RB_BLOCK6             (6u)
#define CY_CRYPTO_V2_RB_BLOCK7             (7u)

#define CY_CRYPTO_V2_RB_FF_LOAD0           (8u)
#define CY_CRYPTO_V2_RB_FF_LOAD1           (9u)
#define CY_CRYPTO_V2_RB_FF_STORE           (12u)

#define CY_CRYPTO_V2_RB_KEY0               (CY_CRYPTO_V2_RB_BLOCK4)
#define CY_CRYPTO_V2_RB_KEY1               (CY_CRYPTO_V2_RB_BLOCK5)
#define CY_CRYPTO_V2_RB_KEY2               (CY_CRYPTO_V2_RB_BLOCK6)
#define CY_CRYPTO_V2_RB_KEY3               (CY_CRYPTO_V2_RB_BLOCK7)

#define CY_CRYPTO_V2_FF_START_OPC          (0x70u)
#define CY_CRYPTO_V2_FF_CONTINUE_OPC       (0x71u)
#define CY_CRYPTO_V2_FF_STOP_OPC           (0x72u)

#define CY_CRYPTO_V2_RB_CLEAR_OPC          (0x64u)
#define CY_CRYPTO_V2_RB_SWAP_OPC           (0x65u)
#define CY_CRYPTO_V2_RB_XOR_OPC            (0x66u)
#define CY_CRYPTO_V2_RB_STORE_OPC          (0x67u)
#define CY_CRYPTO_V2_RB_BYTE_SET_OPC       (0x68u)

#define CY_CRYPTO_V2_BLOCK_MOV_OPC         (0x40u)
#define CY_CRYPTO_V2_BLOCK_XOR_OPC         (0x41u)
#define CY_CRYPTO_V2_BLOCK_SET_OPC         (0x42u)
#define CY_CRYPTO_V2_BLOCK_CMP_OPC         (0x43u)

#define CY_CRYPTO_V2_BLOCK_GCM_OPC         (0x57u)

#define CY_CRYPTO_V2_AES_OPC               (0x50u)
#define CY_CRYPTO_V2_AES_INV_OPC           (0x51u)

#define CY_CRYPTO_V2_CHACHA_OPC            (0x56u)

#define CY_CRYPTO_V2_SHA1_OPC              (0x69u)
#define CY_CRYPTO_V2_SHA2_256_OPC          (0x6au)
#define CY_CRYPTO_V2_SHA2_512_OPC          (0x6bu)
#define CY_CRYPTO_V2_SHA3_OPC              (0x6cu)

#define CY_CRYPTO_V2_CRC_OPC               (0x58u)

#define CY_CRYPTO_V2_DES_OPC               (0x52u)
#define CY_CRYPTO_V2_DES_INV_OPC           (0x53u)
#define CY_CRYPTO_V2_TDES_OPC              (0x54u)
#define CY_CRYPTO_V2_TDES_INV_OPC          (0x55u)

#define CY_CRYPTO_V2_SYNC_OPC              (0x7fu)

#define CY_CRYPTO_MERGE_BYTES(a, b, c, d)  (uint32_t)( \
                                                (((uint32_t)((uint32_t)(a) & 0xffu)) << 24u) | \
                                                (((uint32_t)((uint32_t)(b) & 0xffu)) << 16u) | \
                                                (((uint32_t)((uint32_t)(c) & 0xffu)) <<  8u) | \
                                                (((uint32_t)((uint32_t)(d) & 0xffu))) )

#define CY_CRYPTO_SEL_BYTE3(a) (((a) >> 24u) & 0xffu)
#define CY_CRYPTO_SEL_BYTE2(a) (((a) >> 16u) & 0xffu)
#define CY_CRYPTO_SEL_BYTE1(a) (((a) >>  8u) & 0xffu)
#define CY_CRYPTO_SEL_BYTE0(a) (((a) >>  0u) & 0xffu)

__STATIC_INLINE void Cy_Crypto_Core_V2_FFLoad0Sync(CRYPTO_Type *base)
{
    /* Wait until the FIFO_LOAD0 operations is complete */
    while (0uL != _FLD2VAL(CRYPTO_V2_LOAD0_FF_STATUS_BUSY, REG_CRYPTO_LOAD0_FF_STATUS(base)))
    {
    }
}

__STATIC_INLINE void Cy_Crypto_Core_V2_FFLoad1Sync(CRYPTO_Type *base)
{
    /* Wait until the FIFO_LOAD1 operations is complete */
    while (0uL != _FLD2VAL(CRYPTO_V2_LOAD1_FF_STATUS_BUSY, REG_CRYPTO_LOAD1_FF_STATUS(base)))
    {
    }
}

__STATIC_INLINE void Cy_Crypto_Core_V2_FFStoreSync(CRYPTO_Type *base)
{
    /* Wait until the FIFO_STORE operations is complete */
    while (0uL != _FLD2VAL(CRYPTO_V2_STORE_FF_STATUS_BUSY, REG_CRYPTO_STORE_FF_STATUS(base)))
    {
    }
}

__STATIC_INLINE void Cy_Crypto_Core_V2_Sync(CRYPTO_Type *base)
{
    /* Wait until the instruction is complete */
    while (0uL != (REG_CRYPTO_STATUS(base)))
    {
    }
}

__STATIC_INLINE void Cy_Crypto_Core_V2_FFStart(CRYPTO_Type *base,
                                            uint32_t ff_idx, const uint8_t* p_mem, uint32_t size)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 3u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = ((uint32_t)CY_CRYPTO_V2_FF_START_OPC << CY_CRYPTO_OPCODE_POS) |
                                   (ff_idx << CY_CRYPTO_RSRC0_SHIFT);
    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)  p_mem;
    REG_CRYPTO_INSTR_FF_WR(base) = size;
}

__STATIC_INLINE void Cy_Crypto_Core_V2_FFContinue(CRYPTO_Type *base,
                                               uint32_t ff_idx, const uint8_t* p_mem, uint32_t size)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 3u))
    {
    }

    /* Wait for previous loading has been completed. */
    (CY_CRYPTO_V2_RB_FF_LOAD0 == ff_idx) ? Cy_Crypto_Core_V2_FFLoad0Sync(base) : Cy_Crypto_Core_V2_FFLoad1Sync(base);

    REG_CRYPTO_INSTR_FF_WR(base) = ((uint32_t)CY_CRYPTO_V2_FF_CONTINUE_OPC << CY_CRYPTO_OPCODE_POS) |
                                   (ff_idx << CY_CRYPTO_RSRC0_SHIFT);
    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t) p_mem;
    REG_CRYPTO_INSTR_FF_WR(base) = size;
}

__STATIC_INLINE void Cy_Crypto_Core_V2_FFStop(CRYPTO_Type *base, uint32_t ff_idx)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_FF_STOP_OPC << CY_CRYPTO_OPCODE_POS) |
                                              (ff_idx << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void Cy_Crypto_Core_V2_BlockMov(CRYPTO_Type *base,
                                            uint32_t dst_idx, uint32_t src_idx, uint32_t size)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_BLOCK_MOV_OPC << CY_CRYPTO_OPCODE_POS)
                                        | (size    << CY_CRYPTO_RSRC16_SHIFT)
                                        | (dst_idx << CY_CRYPTO_RSRC12_SHIFT)
                                        | (src_idx << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void Cy_Crypto_Core_V2_BlockMov_Reflect(CRYPTO_Type *base,
                                            uint32_t dst_idx, uint32_t src_idx, uint32_t size)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_BLOCK_MOV_OPC << CY_CRYPTO_OPCODE_POS)
                                        | (1UL     << CY_CRYPTO_RSRC23_SHIFT)
                                        | (size    << CY_CRYPTO_RSRC16_SHIFT)
                                        | (dst_idx << CY_CRYPTO_RSRC12_SHIFT)
                                        | (src_idx << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void Cy_Crypto_Core_V2_BlockSet(CRYPTO_Type *base,
                                            uint32_t dst_idx, uint8_t data, uint32_t size)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_BLOCK_SET_OPC << CY_CRYPTO_OPCODE_POS)
                                        | (size << CY_CRYPTO_RSRC16_SHIFT)
                                        | (dst_idx << CY_CRYPTO_RSRC12_SHIFT)
                                        | ((uint32_t)(data) << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void Cy_Crypto_Core_V2_BlockCmp(CRYPTO_Type *base,
                                            uint32_t src0_idx, uint32_t src1_idx, uint32_t size)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_BLOCK_CMP_OPC << CY_CRYPTO_OPCODE_POS)
                                         | (size     << CY_CRYPTO_RSRC16_SHIFT)
                                         | (src1_idx << CY_CRYPTO_RSRC4_SHIFT)
                                         | (src0_idx << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void Cy_Crypto_Core_V2_BlockXor(CRYPTO_Type *base,
                                            uint32_t dst_idx, uint32_t src0_idx, uint32_t src1_idx, uint32_t size)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_BLOCK_XOR_OPC << CY_CRYPTO_OPCODE_POS)
                                         | (size     << CY_CRYPTO_RSRC16_SHIFT)
                                         | (dst_idx  << CY_CRYPTO_RSRC12_SHIFT)
                                         | (src1_idx << CY_CRYPTO_RSRC4_SHIFT)
                                         | (src0_idx << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void Cy_Crypto_Core_V2_BlockGcm(CRYPTO_Type *base)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)((uint32_t)CY_CRYPTO_V2_BLOCK_GCM_OPC << CY_CRYPTO_OPCODE_POS);
}

__STATIC_INLINE void Cy_Crypto_Core_V2_Run(CRYPTO_Type *base, uint32_t opc)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)((opc & 0xFFUL) << CY_CRYPTO_OPCODE_POS);
}

__STATIC_INLINE void Cy_Crypto_Core_V2_RBClear(CRYPTO_Type *base)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)((uint32_t)CY_CRYPTO_V2_RB_CLEAR_OPC << CY_CRYPTO_OPCODE_POS);
}

__STATIC_INLINE void Cy_Crypto_Core_V2_RBSwap(CRYPTO_Type *base)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)((uint32_t)CY_CRYPTO_V2_RB_SWAP_OPC << CY_CRYPTO_OPCODE_POS);
}

__STATIC_INLINE void Cy_Crypto_Core_V2_RBXor(CRYPTO_Type *base, uint32_t offset, uint32_t size)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_RB_XOR_OPC << CY_CRYPTO_OPCODE_POS) |
                                             (offset << CY_CRYPTO_RSRC8_SHIFT) |
                                             (size   << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void Cy_Crypto_Core_V2_RBStore(CRYPTO_Type *base, uint32_t offset, uint32_t size)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_RB_STORE_OPC << CY_CRYPTO_OPCODE_POS) |
                                             (offset << CY_CRYPTO_RSRC8_SHIFT) |
                                             (size   << CY_CRYPTO_RSRC0_SHIFT));}

__STATIC_INLINE void Cy_Crypto_Core_V2_RBSetByte(CRYPTO_Type *base, uint32_t offset, uint8_t  byte)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_RB_BYTE_SET_OPC << CY_CRYPTO_OPCODE_POS) |
                                             (offset << CY_CRYPTO_RSRC8_SHIFT) |
                                             ((uint32_t)(byte) << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void Cy_Crypto_Core_V2_RunAes(CRYPTO_Type *base)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)((uint32_t)CY_CRYPTO_V2_AES_OPC << CY_CRYPTO_OPCODE_POS);
}

__STATIC_INLINE void Cy_Crypto_Core_V2_RunAesInv(CRYPTO_Type *base)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)((uint32_t)CY_CRYPTO_V2_AES_INV_OPC << CY_CRYPTO_OPCODE_POS);
}

__STATIC_INLINE void Cy_Crypto_Core_V2_RunChacha(CRYPTO_Type *base, uint8_t roundNum)
{
    /* Check whether FIFO has enough space for 1 instruction */
    while(Cy_Crypto_Core_GetFIFOUsed(base) >= (CY_CRYPTO_INSTR_FIFODEPTH - 1u))
    {
    }

    REG_CRYPTO_INSTR_FF_WR(base) = (uint32_t)(((uint32_t)CY_CRYPTO_V2_CHACHA_OPC << CY_CRYPTO_OPCODE_POS) |
                                              ((uint32_t)(roundNum) << CY_CRYPTO_RSRC0_SHIFT));
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */

#endif /* #if !defined (CY_CRYPTO_CORE_HW_V2_H) */


/* [] END OF FILE */
