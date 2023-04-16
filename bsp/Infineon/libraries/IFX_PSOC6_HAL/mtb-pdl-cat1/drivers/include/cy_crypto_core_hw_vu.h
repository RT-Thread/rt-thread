/***************************************************************************//**
* \file cy_crypto_core_hw_vu.h
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


#if !defined (CY_CRYPTO_CORE_HW_VU_H)
#define CY_CRYPTO_CORE_HW_VU_H

#include "cy_crypto_core_hw.h"

#if defined (CY_IP_MXCRYPTO)

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 14.3', 23, \
'Since value of CY_CRYPTO_V1 is decided by PDL device agnostic / hardware specific model, controlling expression will not have an invariant value.');

#if (CPUSS_CRYPTO_VU == 1)

/***************************************
*        Crypto IP opcodes
***************************************/

#define CY_CRYPTO_VU_HW_REG0            (0u)
#define CY_CRYPTO_VU_HW_REG1            (1u)
#define CY_CRYPTO_VU_HW_REG2            (2u)
#define CY_CRYPTO_VU_HW_REG3            (3u)
#define CY_CRYPTO_VU_HW_REG4            (4u)
#define CY_CRYPTO_VU_HW_REG5            (5u)
#define CY_CRYPTO_VU_HW_REG6            (6u)
#define CY_CRYPTO_VU_HW_REG7            (7u)
#define CY_CRYPTO_VU_HW_REG8            (8u)
#define CY_CRYPTO_VU_HW_REG9            (9u)
#define CY_CRYPTO_VU_HW_REG10           (10u)
#define CY_CRYPTO_VU_HW_REG11           (11u)
#define CY_CRYPTO_VU_HW_REG12           (12u)
#define CY_CRYPTO_VU_HW_REG13           (13u)
#define CY_CRYPTO_VU_HW_REG14           (14u)
#define CY_CRYPTO_VU_HW_REG15           (15u)

/* Crypto IP condition codes (vector unit) */
#define CY_CRYPTO_VU_COND_ALWAYS        (0x00u)
#define CY_CRYPTO_VU_COND_EQ            (0x01u)
#define CY_CRYPTO_VU_COND_NE            (0x02u)
#define CY_CRYPTO_VU_COND_CS            (0x03u)
#define CY_CRYPTO_VU_COND_CC            (0x04u)
#define CY_CRYPTO_VU_COND_HI            (0x05u)
#define CY_CRYPTO_VU_COND_LS            (0x06u)
#define CY_CRYPTO_VU_COND_EVEN          (0x07u)
#define CY_CRYPTO_VU_COND_ODD           (0x08u)
#define CY_CRYPTO_VU_COND_MASK          (0x1FFu)

/* Crypto IP status (vector unit) */
#define CY_CRYPTO_VU_STATUS_CARRY       (0u)
#define CY_CRYPTO_VU_STATUS_EVEN        (1u)
#define CY_CRYPTO_VU_STATUS_ZERO        (2u)
#define CY_CRYPTO_VU_STATUS_ONE         (3u)
#define CY_CRYPTO_VU_STATUS_CARRY_BIT   (uint32_t)(((uint32_t)1u) << CY_CRYPTO_VU_STATUS_CARRY)
#define CY_CRYPTO_VU_STATUS_EVEN_BIT    (uint32_t)(((uint32_t)1u) << CY_CRYPTO_VU_STATUS_EVEN)
#define CY_CRYPTO_VU_STATUS_ZERO_BIT    (uint32_t)(((uint32_t)1u) << CY_CRYPTO_VU_STATUS_ZERO)
#define CY_CRYPTO_VU_STATUS_ONE_BIT     (uint32_t)(((uint32_t)1u) << CY_CRYPTO_VU_STATUS_ONE)
#define CY_CRYPTO_VU_STATUS_MASK        (uint32_t)(CY_CRYPTO_VU_STATUS_CARRY_BIT | CY_CRYPTO_VU_STATUS_EVEN_BIT \
                                                   CY_CRYPTO_VU_STATUS_ZERO_BIT | CY_CRYPTO_VU_STATUS_ONE_BIT)

#define CY_CRYPTO_VU_REG_BIT(nreg)      (((uint32_t)1u) << (nreg))

/* Crypto registers field processing (vector unit) */
#define CY_CRYPTO_VU_GET_REG_DATA(data)       (((data) >> 16U) & 0x00003fffUL)
#define CY_CRYPTO_VU_GET_REG_SIZE(data)       ((data) & 0x00000fffUL)

#define CY_CRYPTO_VU_SIZE_FLD_MASK            (0x00001fffuL)
#define CY_CRYPTO_VU_DATA_FLD_MASK            (0x00003fffuL)
#define CY_CRYPTO_VU_DATA_FLD_POS             (16u)

/* Vector Unit instructions */
#define CY_CRYPTO_VU_ALLOC_MEM_OPC            (0x12u)
#define CY_CRYPTO_VU_FREE_MEM_OPC             (0x13u)

/* Instructions with register operand only, category I */
#define CY_CRYPTO_VU_SET_REG_OPC              (0x80u)

#define CY_CRYPTO_VU_LD_REG_OPC               (0x00u)
#define CY_CRYPTO_VU_ST_REG_OPC               (0x01u)
#define CY_CRYPTO_VU_MOV_REG_OPC              (0x02u)

/* Instructions with register operand only, category III */
#define CY_CRYPTO_VU_SWAP_REG_OPC             (0x03u)

/* Instructions with register operand only, category IV */
#define CY_CRYPTO_VU_MOV_REG_TO_STATUS_OPC    (0x04u)

/* Instructions with register operand only, category V */
#define CY_CRYPTO_VU_MOV_STATUS_TO_REG_OPC    (0x05u)

#define CY_CRYPTO_VU2_MOV_IMM_TO_STATUS_OPC   (0x0Fu)

/* Instructions with register operand only, category VI */
#define CY_CRYPTO_VU_PUSH_REG_OPC             (0x10u)
#define CY_CRYPTO_VU_POP_REG_OPC              (0x11u)

/* Instructions with register operand only, category VII */
#define CY_CRYPTO_VU_ADD_REG_OPC              (0x06u)
#define CY_CRYPTO_VU_SUB_REG_OPC              (0x07u)
#define CY_CRYPTO_VU_OR_REG_OPC               (0x08u)
#define CY_CRYPTO_VU_AND_REG_OPC              (0x09u)
#define CY_CRYPTO_VU_XOR_REG_OPC              (0x0Au)
#define CY_CRYPTO_VU_NOR_REG_OPC              (0x0Bu)
#define CY_CRYPTO_VU_NAND_REG_OPC             (0x0Cu)
#define CY_CRYPTO_VU_MIN_REG_OPC              (0x0Du)
#define CY_CRYPTO_VU_MAX_REG_OPC              (0x0Eu)

/* Instructions with mixed operands, category I */
#define CY_CRYPTO_VU_LSL_OPC                  (0x20u)
#define CY_CRYPTO_VU1_LSR_OPC                 (0x24u)
#define CY_CRYPTO_VU2_LSR_OPC                 (0x23u)

/* Instructions with mixed operands, category II */
#define CY_CRYPTO_VU_LSL1_OPC                 (0x21u)
#define CY_CRYPTO_VU_LSL1_WITH_CARRY_OPC      (0x22u)

#define CY_CRYPTO_VU1_LSR1_OPC                (0x25u)
#define CY_CRYPTO_VU1_LSR1_WITH_CARRY_OPC     (0x26u)
#define CY_CRYPTO_VU2_LSR1_OPC                (0x24u)
#define CY_CRYPTO_VU2_LSR1_WITH_CARRY_OPC     (0x25u)

/* Instructions with mixed operands, category III */
#define CY_CRYPTO_VU1_SET_BIT_OPC             (0x2Cu)
#define CY_CRYPTO_VU1_CLR_BIT_OPC             (0x2Du)
#define CY_CRYPTO_VU1_INV_BIT_OPC             (0x2Eu)

#define CY_CRYPTO_VU2_SET_BIT_OPC             (0x28u)
#define CY_CRYPTO_VU2_CLR_BIT_OPC             (0x29u)
#define CY_CRYPTO_VU2_INV_BIT_OPC             (0x2Au)

/* Instructions with mixed operands, category IV */
#define CY_CRYPTO_VU1_GET_BIT_OPC             (0x2Fu)
#define CY_CRYPTO_VU2_GET_BIT_OPC             (0x2Bu)

/* Instructions with mixed operands, category V */
#define CY_CRYPTO_VU1_CLSAME_OPC              (0x28u)
#define CY_CRYPTO_VU1_CTSAME_OPC              (0x29u)

#define CY_CRYPTO_VU2_CLSAME_OPC              (0x26u)
#define CY_CRYPTO_VU2_CTSAME_OPC              (0x27u)

/* Instructions with memory buffer operands, category I */
#define CY_CRYPTO_VU_SET_TO_ZERO_OPC          (0x34u)
#define CY_CRYPTO_VU_SET_TO_ONE_OPC           (0x35u)

/* Instructions with memory buffer operands, category II */
#define CY_CRYPTO_VU_MOV_OPC                  (0x30u)
#define CY_CRYPTO_VU_XSQUARE_OPC              (0x31u)
#define CY_CRYPTO_VU2_USQUARE_OPC             (0x2Fu)

/* Instructions with memory buffer operands, category III */
#define CY_CRYPTO_VU_CMP_SUB_OPC              (0x3Du)
#define CY_CRYPTO_VU_CMP_DEGREE_OPC           (0x3Eu)

/* Instructions with memory buffer operands, category IV */
#define CY_CRYPTO_VU_TST_OPC                  (0x3fu)

/* Instructions with memory buffer operands, category V */
#define CY_CRYPTO_VU_XMUL_OPC                 (0x32u)
#define CY_CRYPTO_VU_UMUL_OPC                 (0x33u)
#define CY_CRYPTO_VU_ADD_OPC                  (0x36u)
#define CY_CRYPTO_VU_SUB_OPC                  (0x37u)
#define CY_CRYPTO_VU_OR_OPC                   (0x38u)
#define CY_CRYPTO_VU_AND_OPC                  (0x39u)
#define CY_CRYPTO_VU_XOR_OPC                  (0x3Au)
#define CY_CRYPTO_VU_NOR_OPC                  (0x3Bu)
#define CY_CRYPTO_VU_NAND_OPC                 (0x3Cu)

/* Instructions with memory buffer operands, category VI */
#define CY_CRYPTO_VU2_SET_BIT_IMM_OPC         (0x2Cu)
#define CY_CRYPTO_VU2_CLR_BIT_IMM_OPC         (0x2Du)
#define CY_CRYPTO_VU2_INV_BIT_IMM_OPC         (0x2Eu)

#define CY_CRYPTO_VU1_WAIT_FOR_COMPLETE(base)  do { ; } while (0uL != _FLD2VAL(CRYPTO_STATUS_VU_BUSY, REG_CRYPTO_STATUS(base)))
#define CY_CRYPTO_VU_READ_SP_REG(base)         CY_CRYPTO_VU_GET_REG_DATA(REG_CRYPTO_VU_RF_DATA(base, 15u))

__STATIC_INLINE void CY_CRYPTO_VU_SAVE_REG (CRYPTO_Type *base, uint32_t rsrc, uint32_t *data);
__STATIC_INLINE void CY_CRYPTO_VU_RESTORE_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t data);
__STATIC_INLINE void CY_CRYPTO_VU_SET_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t data, uint32_t size);


__STATIC_INLINE void CY_CRYPTO_VU_COND_MOV_REG_TO_STATUS (CRYPTO_Type *base, uint32_t cc, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_MOV_REG_TO_STATUS_OPC,
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rsrc));
}

__STATIC_INLINE void CY_CRYPTO_VU_MOV_REG_TO_STATUS (CRYPTO_Type *base, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_MOV_REG_TO_STATUS (base, CY_CRYPTO_VU_COND_ALWAYS, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_MOV_STATUS_TO_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_MOV_STATUS_TO_REG_OPC,
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_MOV_STATUS_TO_REG (CRYPTO_Type *base, uint32_t rdst)
{
    CY_CRYPTO_VU_COND_MOV_STATUS_TO_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_MOV_IMM_TO_STATUS (CRYPTO_Type *base, uint32_t cc, uint32_t imm4)
{
    if (CY_CRYPTO_V1)
    {
        /******* V1 *********/
        uint32_t tmpReg = CY_CRYPTO_VU_HW_REG14;
        uint32_t tmpData;

        CY_CRYPTO_VU_SAVE_REG(base, tmpReg, &tmpData);

        /* Load 4 bit immediate value */
        CY_CRYPTO_VU_SET_REG(base, tmpReg, imm4, 4u);
        CY_CRYPTO_VU_COND_MOV_REG_TO_STATUS(base, cc, tmpReg);

        CY_CRYPTO_VU1_WAIT_FOR_COMPLETE(base);

        CY_CRYPTO_VU_RESTORE_REG(base, tmpReg, tmpData);
    }
    else
    {
        /******* V2 *********/
            Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU2_MOV_IMM_TO_STATUS_OPC,
                                        ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)imm4 << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_MOV_IMM_TO_STATUS (CRYPTO_Type *base, uint32_t imm4)
{
    CY_CRYPTO_VU_COND_MOV_IMM_TO_STATUS (base, CY_CRYPTO_VU_COND_ALWAYS, imm4);
}

/*******************************************************************************/
__STATIC_INLINE void CY_CRYPTO_VU_SET_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t data, uint32_t size)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                            (uint32_t)CY_CRYPTO_VU_SET_REG_OPC,
                           ((uint32_t)rdst << CY_CRYPTO_RSRC26_SHIFT) |
                           ((uint32_t)data << ((CY_CRYPTO_V1) ? CY_CRYPTO_RSRC12_SHIFT : CY_CRYPTO_RSRC13_SHIFT)) |
                           (((uint32_t)size - 1u) << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_LD_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                            (uint32_t)CY_CRYPTO_VU_LD_REG_OPC,
                           ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                           ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT) |
                           ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_LD_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_LD_REG(base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_ST_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                            (uint32_t)CY_CRYPTO_VU_ST_REG_OPC,
                           ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                           ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT) |
                           ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_ST_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_ST_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_MOV_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_MOV_REG_TO_STATUS_OPC,
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_MOV_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_MOV_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_SWAP_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_SWAP_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_SWAP_REG (CRYPTO_Type *base, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_SWAP_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_ADD_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_ADD_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_ADD_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_ADD_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_SUB_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_SUB_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_SUB_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_SUB_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_OR_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_OR_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_OR_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_OR_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_AND_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_AND_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_AND_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_AND_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_XOR_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_XOR_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_XOR_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_XOR_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_NOR_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_NOR_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_NOR_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_NOR_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_NAND_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_NAND_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_NAND_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_NAND_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_MIN_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_MIN_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_MIN_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_MIN_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_MAX_REG (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_MAX_REG_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_MAX_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_MAX_REG (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_PUSH_REG (CRYPTO_Type *base, uint32_t cc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                    (uint32_t)CY_CRYPTO_VU_PUSH_REG_OPC,
                                   ((uint32_t)cc << CY_CRYPTO_RSRC20_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_PUSH_REG (CRYPTO_Type *base)
{
    CY_CRYPTO_VU_COND_PUSH_REG (base, CY_CRYPTO_VU_COND_ALWAYS);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_POP_REG (CRYPTO_Type *base, uint32_t cc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                    (uint32_t)CY_CRYPTO_VU_POP_REG_OPC,
                                   ((uint32_t)cc << CY_CRYPTO_RSRC20_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_POP_REG (CRYPTO_Type *base)
{
    CY_CRYPTO_VU_COND_POP_REG (base, CY_CRYPTO_VU_COND_ALWAYS);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_ALLOC_MEM (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t size)
{
    CY_ASSERT_L1( (uint32_t)(CY_CRYPTO_VU_READ_SP_REG(base) * 4u) >= CY_CRYPTO_BYTE_SIZE_OF_BITS(size) );

    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
          (uint32_t)CY_CRYPTO_VU_ALLOC_MEM_OPC,
         ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
         ((uint32_t)rdst << ((CY_CRYPTO_V1) ? CY_CRYPTO_RSRC12_SHIFT : CY_CRYPTO_RSRC16_SHIFT)) |
        (((uint32_t)size - 1u)  << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_ALLOC_MEM (CRYPTO_Type *base, uint32_t rdst, uint32_t size)
{
    CY_CRYPTO_VU_COND_ALLOC_MEM (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, size);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_FREE_MEM (CRYPTO_Type *base, uint32_t cc, uint32_t reg_mask)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_FREE_MEM_OPC,
                                    ((uint32_t)cc << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)reg_mask));
}

__STATIC_INLINE void CY_CRYPTO_VU_FREE_MEM (CRYPTO_Type *base, uint32_t reg_mask)
{
    CY_CRYPTO_VU_COND_FREE_MEM (base, CY_CRYPTO_VU_COND_ALWAYS, reg_mask);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_LSL (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    if ((CY_CRYPTO_V1) && (0u == REG_CRYPTO_VU_RF_DATA(base, rsrc0)))
    {
        CY_CRYPTO_VU_COND_XOR_REG(base, cc, rdst, rsrc1, rsrc0);
    }
    else
    {

        Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                        (uint32_t)CY_CRYPTO_VU_LSL_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                        ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                        ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_LSL (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_LSL (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_LSL1 (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1)
{
    if (CY_CRYPTO_V1)
    {
        /******* V1 *********/
        Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU_LSL1_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                        ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT));
    }
    else
    {
        /******* V2 *********/
        Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU_LSL1_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                        ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                        ((uint32_t)CY_CRYPTO_VU_HW_REG15 << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_LSL1 (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1)
{
    CY_CRYPTO_VU_COND_LSL1 (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_LSL1_WITH_CARRY (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1)
{
    if (CY_CRYPTO_V1)
    {
        /******* V1 *********/
        Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU_LSL1_WITH_CARRY_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                        ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT));
    }
    else
    {
        /******* V2 *********/
        Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU_LSL1_WITH_CARRY_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                        ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                        ((uint32_t)CY_CRYPTO_VU_HW_REG15 << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_LSL1_WITH_CARRY (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1)
{
    CY_CRYPTO_VU_COND_LSL1_WITH_CARRY (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_LSR (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{

    if ((CY_CRYPTO_V1) && (0u == REG_CRYPTO_VU_RF_DATA(base, rsrc0)))
    {
        CY_CRYPTO_VU_COND_XOR_REG(base, cc, rdst, rsrc1, rsrc0);
    }
    else
    {
         Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)((CY_CRYPTO_V1) ? CY_CRYPTO_VU1_LSR_OPC : CY_CRYPTO_VU2_LSR_OPC),
                                    ((uint32_t)cc       << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst     << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1    << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0    << CY_CRYPTO_RSRC0_SHIFT));

    }
}

__STATIC_INLINE void CY_CRYPTO_VU_LSR (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_LSR (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_LSR1 (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1)
{
    if (CY_CRYPTO_V1)
    {
        /******* V1 *********/
        Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU1_LSR1_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                        ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT));
    }
    else
    {
        /******* V2 *********/
        Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU2_LSR1_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                        ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                        ((uint32_t)CY_CRYPTO_VU_HW_REG15 << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_LSR1 (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1)
{
    CY_CRYPTO_VU_COND_LSR1(base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_LSR1_WITH_CARRY (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1)
{
    if (CY_CRYPTO_V1)
    {
        /******* V1 *********/
        Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU1_LSR1_WITH_CARRY_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT));
    }
    else
    {
        /******* V2 *********/
        Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU2_LSR1_WITH_CARRY_OPC,
                                        ((uint32_t)cc      << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst    << CY_CRYPTO_RSRC12_SHIFT) |
                                        ((uint32_t)rsrc1   << CY_CRYPTO_RSRC4_SHIFT)  |
                                        ((uint32_t)CY_CRYPTO_VU_HW_REG15 << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_LSR1_WITH_CARRY (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1)
{
    CY_CRYPTO_VU_COND_LSR1_WITH_CARRY (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_CLSAME (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)((CY_CRYPTO_V1) ? CY_CRYPTO_VU1_CLSAME_OPC : CY_CRYPTO_VU2_CLSAME_OPC),
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_CLSAME (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_CLSAME (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_CTSAME (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)((CY_CRYPTO_V1) ? CY_CRYPTO_VU1_CTSAME_OPC : CY_CRYPTO_VU2_CTSAME_OPC),
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_CTSAME (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_CTSAME (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_SET_BIT (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)((CY_CRYPTO_V1) ? CY_CRYPTO_VU1_SET_BIT_OPC : CY_CRYPTO_VU2_SET_BIT_OPC),
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
 }

__STATIC_INLINE void CY_CRYPTO_VU_SET_BIT (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_SET_BIT (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_CLR_BIT (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)((CY_CRYPTO_V1) ? CY_CRYPTO_VU1_CLR_BIT_OPC : CY_CRYPTO_VU2_CLR_BIT_OPC),
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_CLR_BIT (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_CLR_BIT (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_INV_BIT (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)((CY_CRYPTO_V1) ? CY_CRYPTO_VU1_INV_BIT_OPC : CY_CRYPTO_VU2_INV_BIT_OPC),
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_INV_BIT (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_INV_BIT (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_GET_BIT (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)((CY_CRYPTO_V1) ? CY_CRYPTO_VU1_GET_BIT_OPC : CY_CRYPTO_VU2_GET_BIT_OPC),
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_GET_BIT (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_GET_BIT (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

/******************************************************************************/
__STATIC_INLINE void CY_CRYPTO_VU_COND_SET_BIT_IMM (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t imm13)
{
    if (CY_CRYPTO_V1)
    {
        /******** V1 ********/
        uint32_t tmpReg = (rdst != CY_CRYPTO_VU_HW_REG14) ? CY_CRYPTO_VU_HW_REG14 : CY_CRYPTO_VU_HW_REG13;
        uint32_t tmpData;
        CY_CRYPTO_VU_SAVE_REG(base, tmpReg, &tmpData);

        /* Load 13 bit immediate value */
        CY_CRYPTO_VU_SET_REG(base, tmpReg, imm13, 13u);
        CY_CRYPTO_VU_COND_SET_BIT(base, cc, rdst, tmpReg);

        CY_CRYPTO_VU1_WAIT_FOR_COMPLETE(base);

        CY_CRYPTO_VU_RESTORE_REG(base, tmpReg, tmpData);
    }
    else
    {
        /******** V2 ********/
            Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU2_SET_BIT_IMM_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC16_SHIFT) |
                                        ((uint32_t)imm13 << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_SET_BIT_IMM (CRYPTO_Type *base, uint32_t rdst, uint32_t imm13)
{
    CY_CRYPTO_VU_COND_SET_BIT_IMM(base, CY_CRYPTO_VU_COND_ALWAYS, rdst, imm13);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_CLR_BIT_IMM (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t imm13)
{
    if (CY_CRYPTO_V1)
    {
        /******** V1 ********/
        uint32_t tmpReg = (rdst != CY_CRYPTO_VU_HW_REG14) ? CY_CRYPTO_VU_HW_REG14 : CY_CRYPTO_VU_HW_REG13;
        uint32_t tmpData;
        CY_CRYPTO_VU_SAVE_REG(base, tmpReg, &tmpData);

        /* Load 13 bit immediate value */
        CY_CRYPTO_VU_SET_REG(base, tmpReg, imm13, 13u);
        CY_CRYPTO_VU_COND_CLR_BIT(base, cc, rdst, tmpReg);

        CY_CRYPTO_VU1_WAIT_FOR_COMPLETE(base);

        CY_CRYPTO_VU_RESTORE_REG(base, tmpReg, tmpData);
    }
    else
    {
        /******** V2 ********/
            Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU2_CLR_BIT_IMM_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC16_SHIFT) |
                                        ((uint32_t)imm13 << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_CLR_BIT_IMM (CRYPTO_Type *base, uint32_t rdst, uint32_t imm13)
{
    CY_CRYPTO_VU_COND_CLR_BIT_IMM(base, CY_CRYPTO_VU_COND_ALWAYS, rdst, imm13);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_INV_BIT_IMM (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t imm13)
{
    if (CY_CRYPTO_V1)
    {
        /******** V1 ********/
        uint32_t tmpReg = (rdst != CY_CRYPTO_VU_HW_REG14) ? CY_CRYPTO_VU_HW_REG14 : CY_CRYPTO_VU_HW_REG13;
        uint32_t tmpData;
        CY_CRYPTO_VU_SAVE_REG(base, tmpReg, &tmpData);

        /* Load 13 bit immediate value */
        CY_CRYPTO_VU_SET_REG(base, tmpReg, imm13, 13u);
        CY_CRYPTO_VU_COND_INV_BIT(base, cc, rdst, tmpReg);

        CY_CRYPTO_VU1_WAIT_FOR_COMPLETE(base);

        CY_CRYPTO_VU_RESTORE_REG(base, tmpReg, tmpData);
    }
    else
    {
        /******** V2 ********/
            Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                         (uint32_t)CY_CRYPTO_VU2_INV_BIT_IMM_OPC,
                                        ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                        ((uint32_t)rdst  << CY_CRYPTO_RSRC16_SHIFT) |
                                        ((uint32_t)imm13 << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_INV_BIT_IMM (CRYPTO_Type *base, uint32_t rdst, uint32_t imm13)
{
    CY_CRYPTO_VU_COND_INV_BIT_IMM(base, CY_CRYPTO_VU_COND_ALWAYS, rdst, imm13);
}

/******************************************************************************/
__STATIC_INLINE void CY_CRYPTO_VU_COND_TST (CRYPTO_Type *base, uint32_t cc, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_TST_OPC,
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_TST (CRYPTO_Type *base, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_TST (base, CY_CRYPTO_VU_COND_ALWAYS, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_MOV (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_MOV_OPC,
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_MOV (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_MOV (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_XSQUARE (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_XSQUARE_OPC,
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_XSQUARE (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_XSQUARE (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_XMUL (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_XMUL_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_XMUL (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_XMUL (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}


__STATIC_INLINE void CY_CRYPTO_VU_COND_UMUL (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_UMUL_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_UMUL (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_UMUL (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_USQUARE (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc)
{
    if (CY_CRYPTO_V1)
    {
        /***** V1 *******/
        CY_CRYPTO_VU_COND_UMUL(base, cc, rdst, rsrc, rsrc);
    }
    else
    {
        /***** V2 *******/
            Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU2_USQUARE_OPC,
                                        ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc << CY_CRYPTO_RSRC0_SHIFT));
    }
}

__STATIC_INLINE void CY_CRYPTO_VU_USQUARE (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc)
{
    CY_CRYPTO_VU_COND_USQUARE(base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_SET_TO_ZERO (CRYPTO_Type *base, uint32_t cc, uint32_t rdst)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_SET_TO_ZERO_OPC,
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_SET_TO_ZERO (CRYPTO_Type *base, uint32_t rdst)
{
    CY_CRYPTO_VU_COND_SET_TO_ZERO (base, CY_CRYPTO_VU_COND_ALWAYS, rdst);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_SET_TO_ONE (CRYPTO_Type *base, uint32_t cc, uint32_t rdst)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_SET_TO_ONE_OPC,
                                    ((uint32_t)cc   << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst << CY_CRYPTO_RSRC12_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_SET_TO_ONE (CRYPTO_Type *base, uint32_t rdst)
{
    CY_CRYPTO_VU_COND_SET_TO_ONE (base, CY_CRYPTO_VU_COND_ALWAYS, rdst);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_ADD (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_ADD_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_ADD (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_SUB (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING, (uint32_t)CY_CRYPTO_VU_SUB_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_SUB (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_OR (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_OR_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_OR (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_OR (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_AND (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_AND_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_AND (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_AND (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_XOR (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING, (uint32_t)CY_CRYPTO_VU_XOR_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_XOR (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_XOR (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_NOR (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_NOR_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_NOR (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_NOR (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_NAND (CRYPTO_Type *base, uint32_t cc, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_NAND_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rdst  << CY_CRYPTO_RSRC12_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_NAND (CRYPTO_Type *base, uint32_t rdst, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_NAND (base, CY_CRYPTO_VU_COND_ALWAYS, rdst, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_CMP_SUB (CRYPTO_Type *base, uint32_t cc, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_CMP_SUB_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_CMP_SUB (CRYPTO_Type *base, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_ALWAYS, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_COND_CMP_DEGREE (CRYPTO_Type *base, uint32_t cc, uint32_t rsrc1, uint32_t rsrc0)
{
    Cy_Crypto_Core_Vu_RunInstr(base, CY_CRYPTO_SYNC_NON_BLOCKING,
                                     (uint32_t)CY_CRYPTO_VU_CMP_DEGREE_OPC,
                                    ((uint32_t)cc    << CY_CRYPTO_RSRC20_SHIFT) |
                                    ((uint32_t)rsrc1 << CY_CRYPTO_RSRC4_SHIFT)  |
                                    ((uint32_t)rsrc0 << CY_CRYPTO_RSRC0_SHIFT));
}

__STATIC_INLINE void CY_CRYPTO_VU_CMP_DEGREE (CRYPTO_Type *base, uint32_t rsrc1, uint32_t rsrc0)
{
    CY_CRYPTO_VU_COND_CMP_DEGREE (base, CY_CRYPTO_VU_COND_ALWAYS, rsrc1, rsrc0);
}

__STATIC_INLINE void CY_CRYPTO_VU_SAVE_REG (CRYPTO_Type *base, uint32_t rsrc, uint32_t *data)
{
    *data = REG_CRYPTO_VU_RF_DATA(base, rsrc);
}

__STATIC_INLINE void CY_CRYPTO_VU_RESTORE_REG (CRYPTO_Type *base, uint32_t rdst, uint32_t data)
{
    CY_CRYPTO_VU_SET_REG(base, rdst, CY_CRYPTO_VU_GET_REG_DATA(data), CY_CRYPTO_VU_GET_REG_SIZE(data) + 1u);
}


#endif /* #if (CPUSS_CRYPTO_VU == 1) */

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 14.3');

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */


#endif /* #if !defined (CY_CRYPTO_CORE_HW_VU_H) */
