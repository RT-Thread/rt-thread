/***************************************************************************//**
* \file cy_crypto_core_hw_v1.h
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


#if !defined (CY_CRYPTO_CORE_HW_V1_H)
#define CY_CRYPTO_CORE_HW_V1_H

#include "cy_crypto_common.h"

#if defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V1_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#include "cy_crypto_core_hw.h"

/******************************************************************************/
#define CY_CRYPTO_V1_SET_REG1_OPC           (0x40u)
#define CY_CRYPTO_V1_SET_REG2_OPC           (0x41u)
#define CY_CRYPTO_V1_SET_REG3_OPC           (0x42u)
#define CY_CRYPTO_V1_SET_REG4_OPC           (0x43u)

#define CY_CRYPTO_V1_AES_BLOCK_OPC          (0x44u)
#define CY_CRYPTO_V1_AES_BLOCK_INV_OPC      (0x45u)
#define CY_CRYPTO_V1_AES_KEY_OPC            (0x46u)
#define CY_CRYPTO_V1_AES_KEY_INV_OPC        (0x47u)
#define CY_CRYPTO_V1_AES_XOR_OPC            (0x48u)

#define CY_CRYPTO_V1_SHA_OPC                (0x4cu)

#define CY_CRYPTO_V1_STR_MEMCPY_OPC         (0x50u)
#define CY_CRYPTO_V1_STR_MEMSET_OPC         (0x51u)
#define CY_CRYPTO_V1_STR_MEMCMP_OPC         (0x52u)
#define CY_CRYPTO_V1_STR_MEMXOR_OPC         (0x53u)

#define CY_CRYPTO_V1_CRC_OPC                (0x58u)

#define CY_CRYPTO_V1_PRNG_OPC               (0x5cu)

#define CY_CRYPTO_V1_TRNG_OPC               (0x60u)

#define CY_CRYPTO_V1_DES_BLOCK_OPC          (0x70u)
#define CY_CRYPTO_V1_DES_BLOCK_INV_OPC      (0x71u)

#define CY_CRYPTO_V1_TDES_BLOCK_OPC         (0x72u)
#define CY_CRYPTO_V1_TDES_BLOCK_INV_OPC     (0x73u)

#define CY_CRYPTO_V1_SYNC_OPC               (0x7fu)


void Cy_Crypto_SetReg1Instr(CRYPTO_Type *base, uint32_t data0);

void Cy_Crypto_SetReg2Instr(CRYPTO_Type *base, uint32_t data0, uint32_t data1);

void Cy_Crypto_SetReg3Instr(CRYPTO_Type *base, uint32_t data0, uint32_t data1, uint32_t data2);

void Cy_Crypto_SetReg4Instr(CRYPTO_Type *base, uint32_t data0, uint32_t data1, uint32_t data2, uint32_t data3);

void Cy_Crypto_Run0ParamInstr(CRYPTO_Type *base, uint8_t instr);

void Cy_Crypto_Run1ParamInstr(CRYPTO_Type *base, uint8_t instr, uint32_t rdst0Shift);

void Cy_Crypto_Run2ParamInstr(CRYPTO_Type *base, uint8_t instr, uint32_t rdst0Shift, uint32_t rdst1Shift);

void Cy_Crypto_Run3ParamInstr(CRYPTO_Type *base, uint8_t instr,
                            uint8_t rdst0Shift, uint8_t rdst1Shift, uint8_t rdst2Shift);

void Cy_Crypto_Run4ParamInstr(CRYPTO_Type *base, uint8_t instr,
                           uint32_t rdst0Shift, uint32_t rdst1Shift, uint32_t rdst2Shift, uint32_t rdst3Shift);


#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_IP_MXCRYPTO) && defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */

#endif /* #if !defined (CY_CRYPTO_CORE_HW_V1_H) */


/* [] END OF FILE */
