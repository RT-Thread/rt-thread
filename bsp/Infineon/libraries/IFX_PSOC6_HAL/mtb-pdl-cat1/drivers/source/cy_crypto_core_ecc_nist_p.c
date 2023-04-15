/***************************************************************************//**
* \file cy_crypto_core_ecc_nist_p.c
* \version 2.70
*
* \brief
*  This file provides Elliptic Curve (EC) Scalar Multiplication using (X,Y)-only,
*  Co-Z arithmetic in the Crypto driver.
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

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_core_ecc_nist_p.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined (CY_CRYPTO_CFG_ECP_C)

#include "cy_crypto_core_vu.h"

/*******************************************************************************
* Elliptic Curve (EC) Scalar Multiplication using (X,Y)-only, Co-Z arithmetic
*
* Theoretic and algorithmic references:
* Algorithms and Co-Z arithmetic theory: 'Fast and Regular Algorithms for Scalar
* Multiplication over Elliptic Curves', Matthieu Rivain NIST P-curves
* (parameters and curve-specific modular reduction):
* 'RECOMMENDED ELLIPTIC CURVES FOR FEDERAL GOVERNMENT USE', NIST, 1999
*
* Useful resources:
* Large number calculator and converter:
* - http://www.mobilefish.com/services/big_number/big_number.php
* - https://www.mobilefish.com/services/big_number_equation/big_number_equation.php
*
* - ECC curves and test vectors: http://point-at-infinity.org/ecc/nisttv
*
* Valid values for scalar multiplier, 2 < d < (order-1)
*
*******************************************************************************/


/***************************************************************
*                   Global Variables
***************************************************************/
static cy_en_crypto_ecc_curve_id_t eccMode;

static cy_en_crypto_ecc_red_mul_algs_t mul_red_alg_select = CY_CRYPTO_NIST_P_BARRETT_RED_ALG;

/***************************************************************
* Collection of multiplication reduction algorithms
* Method 1: (Crypto_EC_CS_MUL_Red_Pxxx): curve specific
*           reduction as proposed by NIST
* Method 2: (Crypto_EC_SM_MUL_Red_Pxxx): curve specific
*           reduction based on Mersenne prime reduction approach
* Method 3: generic Barrett reduction
***************************************************************/
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED)
static void Cy_Crypto_Core_EC_CS_MUL_Red_P192(CRYPTO_Type *base, uint32_t z, uint32_t x);
static void Cy_Crypto_Core_EC_SM_MUL_Red_P192(CRYPTO_Type *base, uint32_t z, uint32_t x);
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED) */

#if defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED)
static void Cy_Crypto_Core_EC_CS_MUL_Red_P224(CRYPTO_Type *base, uint32_t z, uint32_t x);
static void Cy_Crypto_Core_EC_SM_MUL_Red_P224(CRYPTO_Type *base, uint32_t z, uint32_t x);
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED) */

#if defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED)
static void Cy_Crypto_Core_EC_CS_MUL_Red_P256(CRYPTO_Type *base, uint32_t z, uint32_t x);
static void Cy_Crypto_Core_EC_SM_MUL_Red_P256(CRYPTO_Type *base, uint32_t z, uint32_t x);
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED) */

#if defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED)
static void Cy_Crypto_Core_EC_CS_MUL_Red_P384(CRYPTO_Type *base, uint32_t z, uint32_t x);
static void Cy_Crypto_Core_EC_SM_MUL_Red_P384(CRYPTO_Type *base, uint32_t z, uint32_t x);
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED) */

#if defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED)
static void Cy_Crypto_Core_EC_CS_MUL_Red_P521(CRYPTO_Type *base, uint32_t z, uint32_t x);
static void Cy_Crypto_Core_EC_SM_MUL_Red_P521(CRYPTO_Type *base, uint32_t z, uint32_t x);
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED) */

static void Cy_Crypto_Core_EC_CS_MulRed(CRYPTO_Type *base, uint32_t z, uint32_t x, uint32_t size);
static void Cy_Crypto_Core_EC_SM_MulRed(CRYPTO_Type *base, uint32_t z, uint32_t x, uint32_t size);
static void Cy_Crypto_Core_EC_MulRed(CRYPTO_Type *base, uint32_t z, uint32_t x, uint32_t size);


/***************************************************************
*    Curve-specific multiplication reduction algorithms
***************************************************************/

#if defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_CS_MUL_Red_P192
****************************************************************************//**
*
* Curve-specific multiplication modular reduction for P192.
* 0 <= a, b < P192
* a5..a0 * b5..b0 % P192 = t11..t0 % P192
* P192 = 2^192-2^64-1
* t11..t0 % 2^192-2^64-1
* t11..t6 * 2^192 + t5..t0 % 2^192-2^64-1
* t11..t6 * 2^192-2^64-1 + t11..t6 * 2^64 + t11..t6 + t5..t0 % 2^192-2^64-1
* t11..t6 * 2^64 + t11..t6 + t5..t0 % 2^192-2^64-1
* t11..t10 * 2^192 + t9..t6 * 2^64 + t11..t6 + t5..t0 % 2^192-2^64-1
* t11..t10 * 2^192-2^64-1 + t11..t10 * 2^64 + t11..t10 + t9..t6 * 2^64 + t11..t6 + t5..t0 % 2^192-2^64-1
* t11..t10 * 2^64 + t11..t10 + t9..t6 * 2^64 + t11..t6 + t5..t0 % 2^192-2^64-1
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Product = a*b [2*192 bits].
*
* \param x
* Result = x mod P = a*b mod P [192 bits].
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_CS_MUL_Red_P192(CRYPTO_Type *base, uint32_t z, uint32_t x)
{
   uint32_t sh   = 0u;
   uint32_t t1   = 2u;     /* 128 */
   uint32_t t2   = 3u;     /* 192 */
   uint32_t my_z = 4u;
   uint32_t my_x = 5u;

   CY_CRYPTO_VU_PUSH_REG (base);

   CY_CRYPTO_VU_LD_REG (base, my_z, z);
   CY_CRYPTO_VU_LD_REG (base, my_x, x);

   CY_CRYPTO_VU_ALLOC_MEM (base, t1, 128u);
   CY_CRYPTO_VU_ALLOC_MEM (base, t2, 192u);

   CY_CRYPTO_VU_SET_REG (base, sh, 192u, 1u);
   CY_CRYPTO_VU_LSR (base, my_z, my_x, sh);     /* t11..t6 */

   CY_CRYPTO_VU_SET_REG (base, sh, 128u, 1u);
   CY_CRYPTO_VU_LSR (base, t1, my_z, sh);       /* t11..t10 */
   CY_CRYPTO_VU_SET_REG (base, sh, 64u, 1u);
   CY_CRYPTO_VU_LSL (base, t2, my_z, sh);       /* t9..t6 * 2^64 */


   CY_CRYPTO_VU_ADD (base, my_z, my_z, my_x);   /* t11..t6 + t5..t0 */
   CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);  /* C = (z >= VR_P) */
   CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);

   CY_CRYPTO_VU_ADD (base, my_z, my_z, t2);     /* t9..t6 * 2^64 + t11..t6 + t5..t0 */
   CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);  /* C = (z >= VR_P) */
   CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);

   CY_CRYPTO_VU_LSL (base, t2, t1, sh);         /* t11..t10 * 2^64 */
   CY_CRYPTO_VU_OR (base, t1, t1, t2);          /* t11..t10 * 2^64 + t11..t10 */

   CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);     /* t11..t10 * 2^64 + t11..t10 + t9..t6 * 2^64 + t11..t6 + t5..t0 */
   CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);  /* C = (z >= VR_P) */
   CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);

   CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t1) | CY_CRYPTO_VU_REG_BIT(t2));
   CY_CRYPTO_VU_POP_REG (base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED) */


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_CS_MUL_Red_P224
****************************************************************************//**
*
* Curve-specific multiplication modular reduction for P224.
* 0 <= a, b < P224
* a6..a0 * b6..b0 % P224 = t13..t0 % P224
* P224 = 2^224 - 2^96 - 1
* t6..t0 + t10..t7*2^96 + t13..t11*2^96 - t13..t7 - t13..t11 % 2^224 - 2^96 - 1
* t13..t11*2^96 + t6..t0 - t13..t7 - t13..t11 + t10..t7*2^96 % 2^224 - 2^96 - 1
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = x mod P = a*b mod P [224 bits].
*
* \param x
* Product = a*b [2*224 bits].
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_CS_MUL_Red_P224(CRYPTO_Type *base, uint32_t z, uint32_t x)
{
   uint32_t sh   = 0u;
   uint32_t t1   = 1u;     /* 224 */
   uint32_t t2   = 2u;     /* 224 */
   uint32_t t3   = 3u;     /* 224 */
   uint32_t my_z = 4u;
   uint32_t my_x = 5u;

   CY_CRYPTO_VU_PUSH_REG (base);

   CY_CRYPTO_VU_LD_REG (base, my_z, z);
   CY_CRYPTO_VU_LD_REG (base, my_x, x);

   CY_CRYPTO_VU_ALLOC_MEM (base, t1, CY_CRYPTO_ECC_P224_SIZE);  /* 224 */
   CY_CRYPTO_VU_ALLOC_MEM (base, t2, CY_CRYPTO_ECC_P224_SIZE);  /* 224 */
   CY_CRYPTO_VU_ALLOC_MEM (base, t3, CY_CRYPTO_ECC_P224_SIZE);  /* 224 */

   CY_CRYPTO_VU_SET_REG (base, sh, CY_CRYPTO_ECC_P224_SIZE, 1u); /* sh   = 224 */
   CY_CRYPTO_VU_LSR (base, my_z, my_x, sh); /* z = t13..t7 */

   CY_CRYPTO_VU_SET_REG (base, sh, 128u, 1u);
   CY_CRYPTO_VU_LSR (base, t1, my_z, sh);   /* t1 = t13..t11 */

   CY_CRYPTO_VU_SET_REG (base, sh, 96u, 1u);
   CY_CRYPTO_VU_LSL (base, t2, t1, sh);     /* t2 = t13..t11*2^96 */

   CY_CRYPTO_VU_SET_REG (base, sh, 96u, 1u);
   CY_CRYPTO_VU_LSL (base, t3, my_z, sh);   /* t3 = t10..t7*2^96 */

   CY_CRYPTO_VU_ADD (base, t2, t2, my_x);   /* t2 = t13..t11*2^96 + t6..t0 */
   CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, t2, VR_P);    /* C    = (t2 >= VR_P) */
   CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, t2, t2, VR_P);    /* t2 = t2 - p, if C==1 (Carry is set) */

   CY_CRYPTO_VU_SUB (base, t2, t2, my_z);   /* t2 = (t13..t11*2^96 + t6..t0) - t13..t7 */
   CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, t2, t2, VR_P);    /* t2 = t2 + p, if C==0 (Carry is clear) */

   CY_CRYPTO_VU_SUB (base, t2, t2, t1);     /* t2 = (t13..t11*2^96 + t6..t0 - t13..t7) - t13..t11 */
   CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, t2, t2, VR_P);    /* t2 = t2 + p, if C==0 (Carry is clear) */

   CY_CRYPTO_VU_ADD (base, my_z, t2, t3);   /* z = (t13..t11*2^96 + t6..t0 - t13..t7 - t13..t11) + t10..t7*2^96 */
   CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);  /* C    = (z >= VR_P) */
   CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);    /* z = z - p, if C==1 (Carry is set) */

   CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t1) | CY_CRYPTO_VU_REG_BIT(t2) | CY_CRYPTO_VU_REG_BIT(t3));

   CY_CRYPTO_VU_POP_REG (base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED) */


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_CS_MUL_Red_P256
****************************************************************************//**
*
* Curve-specific multiplication modular reduction for P256.
* 0 <= a, b < P256
* a7..a0 * b7..b0 % P256 = t15..t0 % P256
* P224 = 2^256 - 2^224 + 2^192 + 2^96 - 1
* t7..t0 + 2*t15..t11*2^96 + 2*t15..t12*2^96 + (t15..t14*2^192 + t10..t8)
* + (t8*2^224 + t13*2^192 + t15..t9) - (t10*2^224 + t8*2^192 + t13..t11)
* - (t11*2^224 + t9*2^192 + t15..t12) - (t12*2^224 + t10..t8*2^96 + t15..t13)
* - (t13*2^224 + t11..t9*2^96 + t15..t14) % 2^256 - 2^224 + 2^192 + 2^96 - 1
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = x mod P = a*b mod P [256 bits].
*
* \param x
* Product = a*b [2*256 bits].
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_CS_MUL_Red_P256(CRYPTO_Type *base, uint32_t z, uint32_t x)
{
    uint32_t sh     = 0u;   /* Variable values */
    uint32_t sh32   = 1u;
    uint32_t sh96   = 2u;
    uint32_t sh192  = 3u;
    uint32_t sh224  = 4u;
    uint32_t t0     = 5u;   /* 256 */
    uint32_t t1     = 6u;   /* 256 */
    uint32_t t2     = 7u;   /* 256 */
    uint32_t t3     = 8u;   /* 32 */
    uint32_t t4     = 9u;   /* 96 */
    uint32_t my_z   = 10u;
    uint32_t my_x   = 11u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG (base, my_z, z);
    CY_CRYPTO_VU_LD_REG (base, my_x, x);

    CY_CRYPTO_VU_ALLOC_MEM (base, t0, CY_CRYPTO_ECC_P256_SIZE); /* 256 */
    CY_CRYPTO_VU_ALLOC_MEM (base, t1, CY_CRYPTO_ECC_P256_SIZE); /* 256 */
    CY_CRYPTO_VU_ALLOC_MEM (base, t2, CY_CRYPTO_ECC_P256_SIZE); /* 256 */
    CY_CRYPTO_VU_ALLOC_MEM (base, t3, 32u);      /* 32 */
    CY_CRYPTO_VU_ALLOC_MEM (base, t4, 96u);      /* 96 */

    CY_CRYPTO_VU_SET_REG (base, sh, CY_CRYPTO_ECC_P256_SIZE, 1u);    /* sh = 256 */
    CY_CRYPTO_VU_SET_REG (base, sh32, 32u, 1u);   /* sh = 32 */
    CY_CRYPTO_VU_SET_REG (base, sh96, 96u, 1u);   /* sh = 96 */
    CY_CRYPTO_VU_SET_REG (base, sh192, 192u, 1u); /* sh = 192 */
    CY_CRYPTO_VU_SET_REG (base, sh224, 224u, 1u); /* sh = 224 */

    CY_CRYPTO_VU_LSR (base, t0, my_x, sh);      /* t0 = t15..t8 */
    CY_CRYPTO_VU_LSR (base, my_z, t0, sh96);    /* z = t15..t11 */
    CY_CRYPTO_VU_LSR (base, t1, my_z, sh32);    /* t1 = t15..t12 */
    CY_CRYPTO_VU_LSR (base, t3, my_z, sh32);    /* t3 = t12 */

    /* 2*S1 -- 2*t15..t11*2^96 */
    CY_CRYPTO_VU_LSL (base, my_z, my_z, sh96);  /* z = t15..t11*2^96 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, my_z);  /* z = 2*t15..t11*2^96 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D3 (a) -- t12*2^224 */
    CY_CRYPTO_VU_LSL (base, t2, t3, sh224);     /* t2 = t12*2^224 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t12*2^224 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* 2*S2 -- 2*t15..t12*2^96 */
    CY_CRYPTO_VU_LSL (base, t2, t1, sh96);      /* t2 = t15..t12*2^96 */

    CY_CRYPTO_VU_ADD (base, my_z, my_z, t2);    /* z = z + t15..t12*2^96 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    CY_CRYPTO_VU_ADD (base, my_z, my_z, t2);    /* z = z + 2*t15..t12*2^96 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D4 (c) -- t15..t14 */
    CY_CRYPTO_VU_LSR (base, t2, t0, sh192);     /* t2 = t15..t14 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t15..t14 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* S3 (a) -- t15..t14*2^192 */
    CY_CRYPTO_VU_LSL (base, t2, t2, sh192);     /* t2 = t15..t14*2^192 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t2);    /* z = z + t15..t14*2^192 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D2 (c) -- t15..t12 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t1);    /* z = z - t15..t12 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* S4 (b) -- t13*2^192 */
    CY_CRYPTO_VU_LSR (base, t3, t1, sh32);      /* t3 = t13 */
    CY_CRYPTO_VU_LSL (base, t2, t3, sh192);     /* t2 = t13*2^192 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t2);    /* z = z + t13*2^192 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D4 (a) -- t13*2^224 */
    CY_CRYPTO_VU_LSL (base, t2, t2, sh32);      /* t2 = t13*2^224 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t13*2^224 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* D3 (c) -- t15..t13 */
    CY_CRYPTO_VU_LSR (base, t1, t1, sh32);      /* t1 = t15..t13 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t1);    /* z = z - t15..t13 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* S4 (c) -- t15..t13*2^96 */
    CY_CRYPTO_VU_LSL (base, t2, t1, sh96);      /* t2 = t15..t13*2^96 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t2);    /* z = z + t15..t13*2^96 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D2 (a) -- t11*2^224 */
    CY_CRYPTO_VU_LSR (base, t3, t0, sh96);      /* t3 = t11 */
    CY_CRYPTO_VU_LSL (base, t2, t3, sh224);     /* t2 = t11*2^224 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t11*2^224 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* D2 (b) -- t9*2^192 */
    CY_CRYPTO_VU_LSR (base, t3, t0, sh32);      /* t3 = t9 */
    CY_CRYPTO_VU_LSL (base, t2, t3, sh192);     /* t2 = t9*2^192 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t9*2^192 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* D1 (c) -- t13..t11 */
    CY_CRYPTO_VU_LSR (base, t4, t0, sh96);      /* t4 = t13..t11 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t4);    /* z = z - t13..t11 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* S4 (d) -- t11..t9 */
    CY_CRYPTO_VU_LSR (base, t4, t0, sh32);      /* t4 = t11..t9 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t4);    /* z = z + t11..t9 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D1 (a) -- t10*2^224 */
    CY_CRYPTO_VU_LSR (base, t3, t4, sh32);      /* t3 = t10 */
    CY_CRYPTO_VU_LSL (base, t2, t3, sh224);     /* t2 = t10*2^224 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t10*2^224 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */


    /* D4 (b) -- t11..t9*2^96 */
    CY_CRYPTO_VU_LSL (base, t2, t4, sh96);      /* t2 = t11..t9*2^96 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t11..t9*2^96 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    CY_CRYPTO_VU_SET_REG (base, sh, 0u, 1u);      /* sh = 0; */

    /* S3 (b) -- t10..t8 */
    CY_CRYPTO_VU_LSR (base, t4, t0, sh);        /* t4 = t10..t8 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t4);    /* z = z + t10..t8 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D3 (b) -- t10..t8*2^96 */
    CY_CRYPTO_VU_LSL (base, t2, t4, sh96);      /* t4 = t10..t8*2^96 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t10..t8*2^96 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* S4 (a) -- t8*2^224 */
    CY_CRYPTO_VU_LSL (base, t2, t0, sh224);     /* t2 = t8*2^224 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t2);    /* z = z + t8*2^224 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D1 (b) -- t8*2^192 */
    CY_CRYPTO_VU_LSR (base, t2, t2, sh32);      /* t2 = t8*2^192 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t8*2^192 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* T -- t7..t0 */
    CY_CRYPTO_VU_LSR (base, t2, my_x, sh);      /* t2 = t8*2^192 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t2);    /* z = z + t7..t0 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t0) | CY_CRYPTO_VU_REG_BIT(t1) |
                                 CY_CRYPTO_VU_REG_BIT(t2) | CY_CRYPTO_VU_REG_BIT(t3) | CY_CRYPTO_VU_REG_BIT(t4));
    CY_CRYPTO_VU_POP_REG (base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED) */


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_CS_MUL_Red_P384
****************************************************************************//**
*
* Curve-specific multiplication modular reduction for P384.
* 0 <= a, b < P384
* a11..a0 * b11..b0 % P384 = t23..t0 % P384
* P384 = 2^384 - 2^128 - 2*96 + 2*32 - 1
* t11..t0 + 2*t23..t21*2^128 + t23..t12 + (t20..t12*2^96 + t23..t21)
* + (t19..t12*2^128 + t20*2^96 +t23*2^32) + t23..t20*2^128 + (t23..t21*2^96 + t20)
* - (t22..t12*2^32 + t23) - t23..t20*2^32 - (t23*2^128 + t23*2^96) % P384
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = x mod P = a*b mod P [384 bits]
*
* \param x
* Product = a*b [2*384 bits]
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_CS_MUL_Red_P384(CRYPTO_Type *base, uint32_t z, uint32_t x)
{
    uint32_t sh32   = 0u;
    uint32_t sh64   = 1u;
    uint32_t sh96   = 2u;
    uint32_t sh128  = 3u;
    uint32_t sh256  = 4u;
    uint32_t sh384  = 5u;
    uint32_t t0     = 6u;   /* 384 */
    uint32_t t1     = 7u;   /* 384 */
    uint32_t t2     = 8u;   /*  32 */
    uint32_t my_z   = 9u;
    uint32_t my_x   = 10u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG (base, my_z, z);
    CY_CRYPTO_VU_LD_REG (base, my_x, x);

    CY_CRYPTO_VU_ALLOC_MEM (base, t0, CY_CRYPTO_ECC_P384_SIZE); /* 384 */
    CY_CRYPTO_VU_ALLOC_MEM (base, t1, CY_CRYPTO_ECC_P384_SIZE); /* 384 */
    CY_CRYPTO_VU_ALLOC_MEM (base, t2, 32u);  /* 32 */

    CY_CRYPTO_VU_SET_REG (base, sh32, 32u, 1u);   /* sh32  = 32 */
    CY_CRYPTO_VU_SET_REG (base, sh64, 64u, 1u);   /* sh64  = 64 */
    CY_CRYPTO_VU_SET_REG (base, sh96, 96u, 1u);   /* sh96  = 96 */
    CY_CRYPTO_VU_SET_REG (base, sh128, 128u, 1u); /* sh128 = 128 */
    CY_CRYPTO_VU_SET_REG (base, sh256, 256u, 1u); /* sh256 = 256 */
    CY_CRYPTO_VU_SET_REG (base, sh384, CY_CRYPTO_ECC_P384_SIZE, 1u);         /* sh384 = 384 */

    CY_CRYPTO_VU_LSR (base, t0, my_x, sh384);   /* t0 = t23..t12 */

    /* T + S2 -- t11..t0 + t23..t12 */
    CY_CRYPTO_VU_ADD (base, my_z, t0, my_x);    /* z = t23..t12 + t11..t0 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* S6 (b) -- t_20 */
    CY_CRYPTO_VU_LSR (base, t2, t0, sh256);     /* t2 = t20 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t2);    /* z = z + t20 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* S4 (b) -- t20*2^96 */
    CY_CRYPTO_VU_LSL (base, t1, t2, sh96);      /* t1 = t20*2^96 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);    /* z = z + t20*2^96 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* S5 -- t23..t20*2^128 */
    CY_CRYPTO_VU_LSR (base, t1, t0, sh256);     /* t1 = t23..t20 */
    CY_CRYPTO_VU_LSL (base, t1, t1, sh128);     /* t1 = t23..t20*2^128 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);    /* z = z + t23..t20*2^128 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D2 -- t23..t20*2^32 */
    CY_CRYPTO_VU_LSR (base, t1, t1, sh96);      /* t1 = t23..t20*2^32 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t1);    /* z = z - t23..t20*2^32 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* S3 (b) -- t23..t21 */
    CY_CRYPTO_VU_LSR (base, t1, t1, sh64);      /* t1 = t23..t21 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);    /* z = z + t23..t21 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D1 (b) -- t23 */
    CY_CRYPTO_VU_LSR (base, t2, t1, sh64);      /* t2 = t23 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t2);    /* z = z - t23 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* S6 (a) -- t23..t21*2^96 */
    CY_CRYPTO_VU_LSL (base, t1, t1, sh96);      /* t1 = t23..t21*2^96 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);    /* z = z + t23..t21*2^96 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* 2*S1 -- 2*t23..t21*2^128 */
    CY_CRYPTO_VU_LSL (base, t1, t1, sh32);      /* t1 = t23..t21*2^128 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);    /* z = z + t23..t21*2^128 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);    /* z = z + t20..t12*2^128 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* S4 (c) -- t23*2^32 */
    CY_CRYPTO_VU_LSL (base, t1, t2, sh32);      /* t1 = t23*2^32 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);    /* z = z + t23*2^32 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* D3 (b) -- t23*2^96 */
    CY_CRYPTO_VU_LSL (base, t1, t1, sh64);      /* t1 = t23*2^96 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t1);    /* z = z - t23*2^96 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* D3 (a) -- t23*2^128 */
    CY_CRYPTO_VU_LSL (base, t1, t1, sh32);      /* t1 = t23*2^128 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t1);    /* z = z - t23*2^128 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* D1 (a) -- t22..t12*2^32 */
    CY_CRYPTO_VU_LSL (base, t1, t0, sh32);      /* t1 = t22..t12*2^32 */
    CY_CRYPTO_VU_SUB (base, my_z, my_z, t1);    /* z = z - t22..t12*2^32 */
    CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, my_z, my_z, VR_P);   /* z = z + p, if C==0 (Carry is clear) */

    /* S3 (a) -- t20..t12*2^96 */
    CY_CRYPTO_VU_LSL (base, t1, t1, sh64);      /* t1 = t20..t12*2^96 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);    /* z = z + t20..t12*2^96 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    /* S4 (a) -- t19..t12*2^128 */
    CY_CRYPTO_VU_LSL (base, t1, t1, sh32);      /* t1 = t19..t12*2^128 */
    CY_CRYPTO_VU_ADD (base, my_z, my_z, t1);    /* z = z + t19..t12*2^128 */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* z = z - p, if C==1 (Carry is set) */

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t0) | CY_CRYPTO_VU_REG_BIT(t1) | CY_CRYPTO_VU_REG_BIT(t2));
    CY_CRYPTO_VU_POP_REG (base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED) */


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_CS_MUL_Red_P521
****************************************************************************//**
*
* Curve-specific multiplication modular reduction for P521.
* 0 <= a, b < P521
* P521 = 2^521 - 1
* a*b = T = T1*2^521 + T0
* T1 = t1041..t521
* T0 = t520..t0
* T mod p521 = T0 + T1 mod P521
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = x mod P = a*b mod P [521 bits]
*
* \param x
* Product = a*b [2*521 bits]
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_CS_MUL_Red_P521(CRYPTO_Type *base, uint32_t z, uint32_t x)
{
    uint32_t sh521   = 0u;
    uint32_t t0      = 1u;
    uint32_t my_z    = 2u;
    uint32_t my_x    = 3u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG (base, my_z, z);
    CY_CRYPTO_VU_LD_REG (base, my_x, x);

    CY_CRYPTO_VU_ALLOC_MEM (base, t0, CY_CRYPTO_ECC_P521_SIZE); /* 521 */

    CY_CRYPTO_VU_SET_REG (base, sh521, 521u, 1u);                 /* sh521  = 521 */

    CY_CRYPTO_VU_LSR (base, my_z, my_x, sh521);                 /* z = T1 */

    CY_CRYPTO_VU_ADD (base, my_z, my_z, my_x);                  /* z = T1 + T0 */

    /* T0 + T1 mod p */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (t2 >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* t2 = t2 - p, if C==1 (Carry is set) */

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t0));

    CY_CRYPTO_VU_POP_REG (base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED) */


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_CS_MulRed
****************************************************************************//**
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result.
*
* \param x
* Product.
*
* \param size
* Size.
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_CS_MulRed(CRYPTO_Type *base, uint32_t z, uint32_t x, uint32_t size)
{
    (void)size; /* Suppress warning */

    switch (eccMode)
    {
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP192R1:
            Cy_Crypto_Core_EC_CS_MUL_Red_P192(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED) */
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP224R1:
            Cy_Crypto_Core_EC_CS_MUL_Red_P224(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED) */
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP256R1:
            Cy_Crypto_Core_EC_CS_MUL_Red_P256(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED) */
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP384R1:
            Cy_Crypto_Core_EC_CS_MUL_Red_P384(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED) */
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP521R1:
            Cy_Crypto_Core_EC_CS_MUL_Red_P521(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED) */
        default:
        /* Unsupported Eliptic Curve ID */
            break;
    }
}


/**********************************************************************
*  Shift-multiply, curve-specific multiplication reduction algorithms
**********************************************************************/


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_SM_MUL_Red_P192
****************************************************************************//**
*
* Shift-multiply multiplication modular reduction for P192.
* a[CURVE_SIZE-1:0] * b[CURVE_SIZE-1:0] mod p[CURVE_SIZE-1:0]
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = x mod P = a*b mod P [192 bits].
*
* \param x
* Product = a*b [2*192 bits].
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_SM_MUL_Red_P192(CRYPTO_Type *base, uint32_t z, uint32_t x)
{
   /* Setup */
   uint32_t partial  = 0u;
   uint32_t hi       = 1u;
   uint32_t sh64     = 2u;
   uint32_t sh192    = 3u;
   uint32_t my_z     = 4u;
   uint32_t my_x     = 5u;

   CY_CRYPTO_VU_PUSH_REG (base);

   CY_CRYPTO_VU_LD_REG (base, my_z, z);
   CY_CRYPTO_VU_LD_REG (base, my_x, x);

   CY_CRYPTO_VU_ALLOC_MEM (base, partial, CY_CRYPTO_ECC_P192_SIZE + 65u);
   CY_CRYPTO_VU_ALLOC_MEM (base, hi, CY_CRYPTO_ECC_P192_SIZE + 64u);

   CY_CRYPTO_VU_SET_REG (base, sh64, 64u, 1u);
   CY_CRYPTO_VU_SET_REG (base, sh192, 192u, 1u);

   /* Step 2: 1st round of shift-multiply
    * (Separate hi and lo (LSR hi>>CURVE_SIZE), multiply hi (LSL hi and add 1) and add shifted hi to lo)
    * hi * (2^{64} + 1) + lo
    */
   CY_CRYPTO_VU_LSR (base, hi, my_x, sh192);    /* hi = prod >> CURVE_SIZE = prod[383:192] */
   CY_CRYPTO_VU_MOV (base, my_z, my_x);         /* z == lo = prod[191:0] */

   CY_CRYPTO_VU_ADD (base, partial, hi, my_z);  /* partial = (hi*1) + lo */

   CY_CRYPTO_VU_LSL (base, hi, hi, sh64);       /* hi = hi << 64 = hi*2^{64} */

   CY_CRYPTO_VU_ADD (base, partial, partial, hi);   /* partial = hi*(2^{64}+1) + lo */

   /* Step 3: 2nd round of shift-multiply */
   CY_CRYPTO_VU_LSR (base, hi, partial, sh192); /* hi = partial >> CURVE_SIZE = partial[383:192] */

   CY_CRYPTO_VU_ADD (base, my_z, hi, partial);  /* z = (hi*1) + lo (Note: partial == lo, since it will be cut to CURVE_SIZE since z = CURVE_SIZE) */

   CY_CRYPTO_VU_LSL (base, hi, hi, sh64);       /* hi = hi << 64 = hi*2^{64} */

   CY_CRYPTO_VU_ADD (base, my_z, my_z, hi);     /* z = hi*(2^{64}+1) + lo */

   /* Step 4: Final reduction (compare to P-192 and reduce if necessary, based on CARRY flag) */
   CY_CRYPTO_VU_CMP_SUB (base, my_z, VR_P);     /* C = (z >= VR_P) */
   CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);

   CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(partial) | CY_CRYPTO_VU_REG_BIT(hi));
   CY_CRYPTO_VU_POP_REG (base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED) */


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_SM_MUL_Red_P224
****************************************************************************//**
*
* Curve-specific multiplication modular reduction for P224.
*  0 <= a, b < P224
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = x mod P = a*b mod P [224 bits].
*
* \param x
* Product = a*b [2*224 bits].
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_SM_MUL_Red_P224(CRYPTO_Type *base, uint32_t z, uint32_t x)
{

    /* Setup */
    uint32_t partial = 0u;
    uint32_t hi      = 1u;
    uint32_t sh96    = 2u;
    uint32_t sh224   = 3u;
    uint32_t my_z    = 4u;
    uint32_t my_x    = 5u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG (base, my_z, z);
    CY_CRYPTO_VU_LD_REG (base, my_x, x);

    CY_CRYPTO_VU_ALLOC_MEM (base, partial, CY_CRYPTO_ECC_P224_SIZE + 97u);
    CY_CRYPTO_VU_ALLOC_MEM (base, hi, CY_CRYPTO_ECC_P224_SIZE + 96u);

    CY_CRYPTO_VU_SET_REG (base, sh96, 96u, 1u);
    CY_CRYPTO_VU_SET_REG (base, sh224, 224u, 1u);

    /* Step 2: 1st round of shift-multiply
     * (Separate hi and lo (LSR hi>>CURVE_SIZE), multiply hi (LSL hi<<96 and subtract 1) and add shifted hi to lo)
     * hi * (2^{96} + 1) + lo
     */
    CY_CRYPTO_VU_LSR (base, hi, my_x, sh224);       /* hi = prod >> CURVE_SIZE = prod[447:224] */
    CY_CRYPTO_VU_MOV (base, my_z, my_x);            /* z == lo = prod[223:0] */

    CY_CRYPTO_VU_SUB (base, partial, my_z, hi);     /* partial = lo - (hi*1) */

    CY_CRYPTO_VU_LSL (base, hi, hi, sh96);          /* hi = hi << 96 = hi*2^{96} */

    CY_CRYPTO_VU_ADD (base, partial, partial, hi);  /* partial = hi*(2^{96}-1) + lo */

    /* Step 3: 2nd round of shift-multiply */
    CY_CRYPTO_VU_LSR (base, hi, partial, sh224);    /* hi = partial>>CURVE_SIZE = partial[447:224] */

    CY_CRYPTO_VU_SUB (base, my_z, partial, hi);     /* z = lo - (hi*1) (Note: partial == lo, since it will be cut to CURVE_SIZE since z = CURVE_SIZE) */

    CY_CRYPTO_VU_LSL (base, hi, hi, sh96);          /* hi = hi<<96 = hi*2^{96} */

    CY_CRYPTO_VU_ADD (base, my_z, my_z, hi);        /* z = hi*(2^{96}-1) + lo */

    /* Step 4: Final reduction (compare to P-224 and reduce if necessary, based on CARRY flag) */
    CY_CRYPTO_VU_CMP_SUB (base, my_z, VR_P);        /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(partial) | CY_CRYPTO_VU_REG_BIT(hi));
    CY_CRYPTO_VU_POP_REG (base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED) */


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_SM_MUL_Red_P256
****************************************************************************//**
*
* Shift-multiply modular reduction algorithm.
* a*b mod p
* 0 <= a, b < P256
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result.
*
* \param x
* Product.
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_SM_MUL_Red_P256(CRYPTO_Type *base, uint32_t z, uint32_t x)
{
    /* Pre-computed coefficient for shift-multiply modular reduction for P256 */
    const uint8_t P256_ShMul_COEFF[] = {
        0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
        0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
        0xFEu, 0xFFu, 0xFFu, 0xFFu
    };

    /* Setup */
    uint32_t partial = 0u;
    uint32_t hi      = 1u;
    uint32_t sh256   = 2u;
    uint32_t my_z    = 3u;
    uint32_t my_x    = 4u;
    uint32_t coeff   = 5u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG (base, my_z, z);
    CY_CRYPTO_VU_LD_REG (base, my_x, x);

    CY_CRYPTO_VU_ALLOC_MEM (base, coeff, 224u);
    CY_CRYPTO_VU_ALLOC_MEM (base, partial, CY_CRYPTO_ECC_P256_SIZE + 224u);
    CY_CRYPTO_VU_ALLOC_MEM (base, hi, CY_CRYPTO_ECC_P256_SIZE);

    CY_CRYPTO_VU_SET_REG (base, sh256, 256u, 1u);

    Cy_Crypto_Core_Vu_SetMemValue (base, coeff, P256_ShMul_COEFF, 224u);

    /* Step 2: 1st round of shift-multiply:
     * - separate hi and lo (LSR hi >> CURVE_SIZE),
     * - multiply hi * coeff,
     * - add hi * coeff + lo
     */
    CY_CRYPTO_VU_LSR  (base, hi, my_x, sh256);           /* hi = prod >> CURVE_SIZE = prod[511:256] */
    CY_CRYPTO_VU_MOV  (base, my_z, my_x);                /* z == lo = prod[255:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);        /* partial = hi * coeff */
    CY_CRYPTO_VU_ADD  (base, partial, partial, my_z);    /* partial = hi * coeff + lo */

    /* Step 3: 2nd round of shift-multiply */
    CY_CRYPTO_VU_LSR  (base, hi, partial, sh256);        /* hi = partial >> CURVE_SIZE = partial[511:256] */
    CY_CRYPTO_VU_MOV  (base, my_z, partial);             /* z == lo = partial[255:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);        /* partial = hi * coeff */
    CY_CRYPTO_VU_ADD  (base, partial, partial, my_z);    /* z = hi * coeff + lo  */

    /* Step 4: 3rd round of shift-multiply */
    CY_CRYPTO_VU_LSR  (base, hi, partial, sh256);        /* hi = partial >> CURVE_SIZE = partial[511:256] */
    CY_CRYPTO_VU_MOV  (base, my_z, partial);             /* z == lo = partial[255:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);        /* partial = hi * coeff */
    CY_CRYPTO_VU_ADD  (base, partial, partial, my_z);    /* z = hi * coeff + lo  */

    /* Step 5: 4th round of shift-multiply */
    CY_CRYPTO_VU_LSR  (base, hi, partial, sh256);        /* hi = partial >> CURVE_SIZE = partial[511:256] */
    CY_CRYPTO_VU_MOV  (base, my_z, partial);             /* z == lo = partial[255:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);        /* partial = hi * coeff */
    CY_CRYPTO_VU_ADD  (base, partial, partial, my_z);    /* z = hi * coeff + lo  */

    /* Step 6: 5th round of shift-multiply */
    CY_CRYPTO_VU_LSR  (base, hi, partial, sh256);        /* hi = partial >> CURVE_SIZE = partial[511:256] */
    CY_CRYPTO_VU_MOV  (base, my_z, partial);             /* z == lo = partial[255:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);        /* partial = hi * coeff */
    CY_CRYPTO_VU_ADD  (base, partial, partial, my_z);    /* z = hi * coeff + lo  */

    /* Step 7: 6th round of shift-multiply */
    CY_CRYPTO_VU_LSR  (base, hi, partial, sh256);        /* hi = partial >> CURVE_SIZE = partial[511:256] */
    CY_CRYPTO_VU_MOV  (base, my_z, partial);             /* z == lo = partial[255:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);        /* partial = hi * coeff */
    CY_CRYPTO_VU_ADD  (base, partial, partial, my_z);    /* z = hi * coeff + lo  */

    /* Step 8: 7th round of shift-multiply */
    CY_CRYPTO_VU_LSR  (base, hi, partial, sh256);        /* hi = partial >> CURVE_SIZE = partial[511:256] */
    CY_CRYPTO_VU_MOV  (base, my_z, partial);             /* z == lo = partial[255:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);        /* partial = hi * coeff */
    CY_CRYPTO_VU_ADD  (base, partial, partial, my_z);    /* z = hi * coeff + lo  */

    /* Step 9: 8th round of shift-multiply */
    CY_CRYPTO_VU_LSR  (base, hi, partial, sh256);        /* hi = partial >> CURVE_SIZE = partial[511:256] */
    CY_CRYPTO_VU_MOV  (base, my_z, partial);             /* z == lo = partial[255:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);        /* partial = hi * coeff */
    CY_CRYPTO_VU_ADD  (base, partial, partial, my_z);    /* z = hi * coeff + lo  */

    /* Step 10: 9th round of shift-multiply */
    CY_CRYPTO_VU_LSR  (base, hi, partial, sh256);        /* hi = partial >> CURVE_SIZE = partial[511:256] */
    CY_CRYPTO_VU_MOV  (base, my_z, partial);             /* z == lo = partial[255:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);        /* partial = hi * coeff */
    CY_CRYPTO_VU_ADD  (base, my_z, partial, my_z);       /* z = hi * coeff + lo  */

    /* Step 11: Final reduction (compare to P-256 and reduce if necessary, based on CARRY flag) */
    CY_CRYPTO_VU_CMP_SUB  (base, my_z, VR_P);            /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);

    CY_CRYPTO_VU_FREE_MEM(base, CY_CRYPTO_VU_REG_BIT(partial) | CY_CRYPTO_VU_REG_BIT(hi) | CY_CRYPTO_VU_REG_BIT(coeff));
    CY_CRYPTO_VU_POP_REG(base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED) */


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_SM_MUL_Red_P384
****************************************************************************//**
*
* Shift-multiply modular reduction algorithm.
* a*b mod p
* 0 <= a, b < P384
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result.
*
* \param x
* Product.
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_SM_MUL_Red_P384(CRYPTO_Type *base, uint32_t z, uint32_t x)
{
    /* Pre-computed coefficient for shift-multiply modular reduction for P384 */
    const uint8_t P384_ShMul_COEFF[] = {
        0x01u, 0x00u, 0x00u, 0x00u, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
        0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u, 0x00u,
        0x01u
    };

    /* Setup */
    uint32_t partial = 0u;
    uint32_t hi      = 1u;
    uint32_t sh96    = 2u;
    uint32_t sh384   = 3u;
    uint32_t my_z    = 4u;
    uint32_t my_x    = 5u;
    uint32_t coeff   = 6u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG (base, my_z, z);
    CY_CRYPTO_VU_LD_REG (base, my_x, x);

    CY_CRYPTO_VU_ALLOC_MEM (base, partial, CY_CRYPTO_ECC_P384_SIZE + 129u);
    CY_CRYPTO_VU_ALLOC_MEM (base, hi, CY_CRYPTO_ECC_P384_SIZE + 96u);
    CY_CRYPTO_VU_ALLOC_MEM (base, coeff, 129u);

    CY_CRYPTO_VU_SET_REG (base, sh96, 96u, 1u);
    CY_CRYPTO_VU_SET_REG (base, sh384, 384u, 1u);

    Cy_Crypto_Core_Vu_SetMemValue (base, coeff, P384_ShMul_COEFF, 129u);

    /* Step 2: 1st round of shift-multiply
    * (Separate hi and lo (LSR hi>>CURVE_SIZE), multiply hi*c and add hi*coeff + lo)
    * hi*coeff + lo
    */
    CY_CRYPTO_VU_LSR (base, hi, my_x, sh384);           /* hi = prod >> CURVE_SIZE = prod[767:384] */
    CY_CRYPTO_VU_MOV (base, my_z, my_x);                /* z == lo = prod[383:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);       /* partial = hi*coeff */
    CY_CRYPTO_VU_ADD (base, partial, partial, my_z);    /* partial = hi*coeff + lo */

    /* Step 3: 2nd round of shift-multiply */
    CY_CRYPTO_VU_LSR (base, hi, partial, sh384);        /* hi = partial>>CURVE_SIZE = partial[767:384] */
    CY_CRYPTO_VU_MOV (base, my_z, partial);             /* z == lo = partial[383:0] */

    CY_CRYPTO_VU_UMUL (base, partial, hi, coeff);       /* partial = hi*coeff */
    CY_CRYPTO_VU_ADD (base, my_z, partial, my_z);       /* z = hi*coeff + lo */

    /* Step 4: Final reduction (compare to P-384 and reduce if necessary, based on CARRY flag) */
    CY_CRYPTO_VU_CMP_SUB  (base, my_z, VR_P);           /* C = (z >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(partial) | CY_CRYPTO_VU_REG_BIT(hi) | CY_CRYPTO_VU_REG_BIT(coeff));
    CY_CRYPTO_VU_POP_REG (base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED) */


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_SM_MUL_Red_P521
****************************************************************************//**
*
* Curve-specific multiplication modular reduction for P521; equivalent to shift-multiply method for P521.
* 0 <= a, b < P521
* P521 = 2^521 - 1
* a*b = T = T1*2^521 + T0
* T1 = t1041..t521
* T0 = t520..t0
* T mod p521 = T0 + T1 mod P521
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = x mod P = a*b mod P [521 bits].
*
* \param x
* Product = a*b [2*521 bits].
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_SM_MUL_Red_P521(CRYPTO_Type *base, uint32_t z, uint32_t x)
{
    uint32_t sh521   = 0u;
    uint32_t t0      = 1u;
    uint32_t my_z    = 2u;
    uint32_t my_x    = 3u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG (base, my_z, z);
    CY_CRYPTO_VU_LD_REG (base, my_x, x);

    CY_CRYPTO_VU_ALLOC_MEM (base, t0, CY_CRYPTO_ECC_P521_SIZE);     /* 521 */

    CY_CRYPTO_VU_SET_REG (base, sh521, 521u, 1u);       /* sh521  = 521 */

    CY_CRYPTO_VU_LSR (base, my_z, my_x, sh521);         /* z = T1 */

    CY_CRYPTO_VU_ADD (base, my_z, my_z, my_x);          /* z = T1 + T0 */

    /* T0 + T1 mod p */
    CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, my_z, VR_P);     /* C = (t2 >= VR_P) */
    CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, my_z, my_z, VR_P);   /* t2 = t2 - p, if C==1 (Carry is set) */

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t0));
    CY_CRYPTO_VU_POP_REG (base);
}
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED) */


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_SM_MulRed
****************************************************************************//**
*
*
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result.
*
* \param x
* Product.
*
* \param size
* Size.
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_SM_MulRed(CRYPTO_Type *base, uint32_t z, uint32_t x, uint32_t size)
{
    (void)size; /* Suppress warning */

    switch (eccMode)
    {
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP192R1:
            Cy_Crypto_Core_EC_SM_MUL_Red_P192(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED) */
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP224R1:
            Cy_Crypto_Core_EC_SM_MUL_Red_P224(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED) */
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP256R1:
            Cy_Crypto_Core_EC_SM_MUL_Red_P256(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED) */
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP384R1:
            Cy_Crypto_Core_EC_SM_MUL_Red_P384(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED) */
    #if defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED)
        case CY_CRYPTO_ECC_ECP_SECP521R1:
            Cy_Crypto_Core_EC_SM_MUL_Red_P521(base, z, x);
            break;
    #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED) */
        default:
        /* Unsupported Eliptic Curve ID */
            break;
    }
}


/***************************************************************
*           Generic Barrett modular reduction
***************************************************************/


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_Bar_MulRed
****************************************************************************//**
*
* Barrett multiplication modular reduction.
* t[b-1:0] = z_double >> size
* t = t * VR_BARRETT
* t = t + ((z_double >> size) << size)  - for leading '1' Barrett bit.
* t = t >> size
* t = t * mod                           - r2 (not reduced)
* u = z_double - t                      - r = r1 - r2 (not reduced)
*
* u = IF (u >= mod) u = u - mod         - reduce r using mod
* u = IF (u >= mod) u = u - mod
*
* z = a_double % mod
*
* Leaf function.
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Register index for Barrett reduced value.
*
* \param x
* Register index for non reduced value.
*
* \param size
* Bit size.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_Bar_MulRed(CRYPTO_Type *base,
    uint32_t z,
    uint32_t x,
    uint32_t size)
{

    uint32_t sh          = 0u;
    uint32_t t1          = 1u;
    uint32_t t1_plus2    = 1u;
    uint32_t t2_plus2    = 0u;
    uint32_t t_double    = 2u;
    uint32_t z_double    = 3u;
    uint32_t my_z        = 4u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG (base, my_z, z);
    CY_CRYPTO_VU_LD_REG (base, z_double, x);

    CY_CRYPTO_VU_ALLOC_MEM (base, t_double, 2u * size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t1, size);

    CY_CRYPTO_VU_SET_REG (base, sh, size, 1u);              /* sh = k (k \equiv size) */
    CY_CRYPTO_VU_LSR (base, my_z, z_double, sh);            /* a/b^{k} (q1*b) */

    CY_CRYPTO_VU_UMUL (base, t_double, my_z, VR_BARRETT);   /* a/b^{k}*VR_BARRETT (q2*b) */
    CY_CRYPTO_VU_LSR (base, t1, t_double, sh);              /* q2*b/b^{k} = q2/b^{k-1} */

    CY_CRYPTO_VU_UMUL (base, t_double, t1, VR_P);

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t1));

    CY_CRYPTO_VU_ALLOC_MEM (base, t1_plus2, size + 2u);
    CY_CRYPTO_VU_ALLOC_MEM (base, t2_plus2, size + 2u);

    CY_CRYPTO_VU_SUB (base, t2_plus2, z_double, t_double);

    CY_CRYPTO_VU_SUB (base, t1_plus2, t2_plus2, VR_P);
    CY_CRYPTO_VU_COND_SWAP_REG (base, CY_CRYPTO_VU_COND_CC, t1_plus2, t2_plus2);

    CY_CRYPTO_VU_SUB (base, t2_plus2, t1_plus2, VR_P);
    CY_CRYPTO_VU_COND_MOV (base, CY_CRYPTO_VU_COND_CC, my_z, t1_plus2);
    CY_CRYPTO_VU_COND_MOV (base, CY_CRYPTO_VU_COND_CS, my_z, t2_plus2);

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t2_plus2) |
                                 CY_CRYPTO_VU_REG_BIT(t1_plus2) |
                                 CY_CRYPTO_VU_REG_BIT(t_double));
    CY_CRYPTO_VU_POP_REG (base);
}


/***************************************************************
*       Multiplication reduction algorithm select
***************************************************************/


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_MulRed
****************************************************************************//**
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = x mod P = a*b mod P [224 bits].
*
* \param x
* Product = a*b [2*224 bits].
*
* \param size
* Bit size.
*
*******************************************************************************/
static void Cy_Crypto_Core_EC_MulRed(CRYPTO_Type *base, uint32_t z, uint32_t x, uint32_t size)
{
    switch (mul_red_alg_select)
    {
        case CY_CRYPTO_NIST_P_CURVE_SPECIFIC_RED_ALG:
                /* Curve-specific multiplication reduction algorithms */
                Cy_Crypto_Core_EC_CS_MulRed(base, z, x, size);
            break;
        case CY_CRYPTO_NIST_P_SHIFT_MUL_RED_ALG:
                /* Shift-multiply, curve-specific multiplication reduction algorithms */
                Cy_Crypto_Core_EC_SM_MulRed(base, z, x, size);
            break;
        default:
                /* Generic Barrett modular reduction */
                Cy_Crypto_Core_EC_Bar_MulRed(base, z, x, size);
            break;
    }
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_MulMod
****************************************************************************//**
*
* Modular multiplication in GF(VR_P).
* Leaf function.
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = a * b % mod. Register index for product value.
*
* \param a
* Register index for multiplicand value.
*
* \param b
* Register index for multiplier value.
*
* \param size
* Bit size.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_MulMod( CRYPTO_Type *base,
    uint32_t z,
    uint32_t a,
    uint32_t b,
    uint32_t size)
{
    uint32_t ab_double       = 0u;
    uint32_t my_z            = 1u;
    uint32_t my_a            = 2u;
    uint32_t my_b            = 3u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG(base, my_z, z);
    CY_CRYPTO_VU_LD_REG(base, my_a, a);
    CY_CRYPTO_VU_LD_REG(base, my_b, b);

    CY_CRYPTO_VU_ALLOC_MEM (base, ab_double, 2u * size);

    CY_CRYPTO_VU_UMUL (base, ab_double, my_a, my_b);
    Cy_Crypto_Core_Vu_WaitForComplete(base);

    /* Modular Reduction: Barrett reduction or curve-specific or shift-multiply */
    Cy_Crypto_Core_EC_MulRed(base, my_z, ab_double, size);

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(ab_double));

    CY_CRYPTO_VU_POP_REG (base);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_AddMod
****************************************************************************//**
*
* Modular addition in GF(VR_P).
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = a + b % mod. Register index for sum value
*
* \param a
* Register index for augend a value.
*
* \param b
* Register index for addend b value.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_AddMod( CRYPTO_Type *base, uint32_t z, uint32_t a, uint32_t b)
{
   CY_CRYPTO_VU_ADD (base, z, a, b);                                /* C = (sum >= 2^n) */
   CY_CRYPTO_VU_COND_CMP_SUB (base, CY_CRYPTO_VU_COND_CC, z, VR_P); /* C = (sum >= mod) */
   CY_CRYPTO_VU_COND_SUB (base, CY_CRYPTO_VU_COND_CS, z, z, VR_P);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_SubMod
****************************************************************************//**
*
* Modular subtraction in GF(VR_P).
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = a - b % mod. Register index for difference value.
*
* \param a
* Register index for minuend a value.
*
* \param b
* RRegister index for subtrahend b value.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_SubMod( CRYPTO_Type *base, uint32_t z, uint32_t a, uint32_t b)
{
   CY_CRYPTO_VU_SUB (base, z, a, b);       /* C = (a >= b) */
   CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_CC, z, z, VR_P);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_HalfMod
****************************************************************************//**
*
* Modular halving in GF(VR_P).
* Leaf function.
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = a / 2 % mod. Register index for result value.
*
* \param a
* Register index for value to be halved.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_HalfMod( CRYPTO_Type *base, uint32_t z, uint32_t a)
{
   CY_CRYPTO_VU_TST (base, a);
   CY_CRYPTO_VU_COND_ADD (base, CY_CRYPTO_VU_COND_ODD, a, a, VR_P);
   CY_CRYPTO_VU_LSR1_WITH_CARRY (base, z, a);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_SquareMod
****************************************************************************//**
*
* Modular squaring in GF(VR_P).
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = a * a % mod. Register index for product value.
*
* \param a
* Register index for multiplicand and multiplier value.
*
* \param size
* Bit size.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_SquareMod( CRYPTO_Type *base,
    uint32_t z,
    uint32_t a,
    uint32_t size)
{
    Cy_Crypto_Core_EC_MulMod( base, z, a, a, size);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_DivMod
****************************************************************************//**
*
* Modular division in GF(VR_P).
* This algorithm works when "dividend" and "divisor" are relatively prime,
* Reference: "From Euclid's GCD to Montgomery Multiplication to the Great Divide",
* S.C. Schantz
*
* \param base
* The pointer to a Crypto instance.
*
* \param z
* Result = a / b % mod. Register index for quotient value.
*
* \param a
* Register index for dividend value.
*
* \param b
* Register index for divisor value.
*
* \param size
* Bit size.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_DivMod( CRYPTO_Type *base,
    uint32_t z,
    uint32_t a,
    uint32_t b,
    uint32_t size)
{
    uint32_t my_dividend = 7u;
    uint32_t my_divisor  = 8u;
    uint32_t my_a        = 9u;
    uint32_t my_b        = 10u;
    uint32_t my_u        = 11u;
    uint32_t my_v        = 12u;

    uint32_t zero;
    uint32_t carry;
    uint32_t a_even;
    uint32_t b_even;

    uint32_t status0;
    uint32_t status1;
    uint32_t status2;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG(base, my_dividend, a);
    CY_CRYPTO_VU_LD_REG(base, my_divisor, b);
    CY_CRYPTO_VU_LD_REG(base, my_u, z);

    CY_CRYPTO_VU_ALLOC_MEM (base, my_a, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, my_b, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, my_v, size);

    CY_CRYPTO_VU_MOV (base, my_a, my_divisor);
    CY_CRYPTO_VU_MOV (base, my_b, VR_P);
    CY_CRYPTO_VU_MOV (base, my_u, my_dividend);

    CY_CRYPTO_VU_SET_TO_ZERO (base, my_v);

    while (true)
    {
        CY_CRYPTO_VU_CMP_SUB (base, my_a, my_b);
        status0 = Cy_Crypto_Core_Vu_StatusRead(base);

        CY_CRYPTO_VU_TST (base, my_a);
        status1 = Cy_Crypto_Core_Vu_StatusRead(base);

        CY_CRYPTO_VU_TST (base, my_b);
        status2 = Cy_Crypto_Core_Vu_StatusRead(base);

        zero    = status0 & CY_CRYPTO_VU_STATUS_ZERO_BIT;  /* a == b */
        carry   = status0 & CY_CRYPTO_VU_STATUS_CARRY_BIT; /* a >= b */
        a_even  = status1 & CY_CRYPTO_VU_STATUS_EVEN_BIT;
        b_even  = status2 & CY_CRYPTO_VU_STATUS_EVEN_BIT;

        if (0u != zero)
        {
            break;
        }

        if (0u != a_even)
        {
            CY_CRYPTO_VU_LSR1 (base, my_a, my_a);
            Cy_Crypto_Core_EC_HalfMod( base, my_u, my_u);
        }
        else if (0u != b_even)
        {
            CY_CRYPTO_VU_LSR1 (base, my_b, my_b);
            Cy_Crypto_Core_EC_HalfMod( base, my_v, my_v);
        }
        else if (0u != carry)
        { /* (a >= b) */
            CY_CRYPTO_VU_SUB  (base, my_a, my_a, my_b);
            CY_CRYPTO_VU_LSR1 (base, my_a, my_a);

            Cy_Crypto_Core_EC_SubMod(  base, my_u, my_u, my_v);
            Cy_Crypto_Core_EC_HalfMod( base, my_u, my_u);
        }
        else
        {
            CY_CRYPTO_VU_SUB  (base, my_b, my_b, my_a);
            CY_CRYPTO_VU_LSR1 (base, my_b, my_b);

            Cy_Crypto_Core_EC_SubMod(  base, my_v, my_v, my_u);
            Cy_Crypto_Core_EC_HalfMod( base, my_v, my_v);
        }
    }

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(my_a) | CY_CRYPTO_VU_REG_BIT(my_b) | CY_CRYPTO_VU_REG_BIT(my_v));

    CY_CRYPTO_VU_POP_REG (base);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_JacobianTransform
****************************************************************************//**
*
* Transformation from affine coordinates to Jacobian projective coordinates in GF(VR_P).
*
* \param base
* The pointer to a Crypto instance.
*
* \param s_x
* Register index for affine X coordinate and Jacobian projective X coordinate.
*
* \param s_y
* Register index for affine Y coordinate and Jacobian projective Y coordinate.
*
* \param s_z
* Register index for Jacobian projective Z coordinate.
*
*******************************************************************************/
void Cy_Crypto_Core_JacobianTransform(CRYPTO_Type *base, uint32_t s_x, uint32_t s_y, uint32_t s_z)
{
    (void)s_x; /* Suppress warning */
    (void)s_y; /* Suppress warning */
    CY_CRYPTO_VU_SET_TO_ONE (base, s_z);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_JacobianInvTransform
****************************************************************************//**
*
* Transformation from Jacobian projective coordinates to affine coordinates in GF(VR_P).
* (s_x, s_y, s_z) -> (p_x, p_y), where p_x = s_x/s_z^2, p_y = s_y/s_z^3
*
* \param base
* The pointer to a Crypto instance.
*
* \param s_x
* Register index for affine X coordinate and Jacobian projective X coordinate.
*
* \param s_y
* Register index for affine Y coordinate and Jacobian projective Y coordinate.
*
* \param s_z
* Register index for Jacobian projective Z coordinate.
*
* \param size
* Bit size.
*
*******************************************************************************/
void Cy_Crypto_Core_JacobianInvTransform(CRYPTO_Type *base, uint32_t s_x, uint32_t s_y, uint32_t s_z, uint32_t size)
{

    uint32_t t1     = 7u;
    uint32_t t2     = 8u;
    uint32_t t3     = 9u;
    uint32_t my_s_x = 10u;
    uint32_t my_s_y = 11u;
    uint32_t my_s_z = 12u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG(base, my_s_x, s_x);
    CY_CRYPTO_VU_LD_REG(base, my_s_y, s_y);
    CY_CRYPTO_VU_LD_REG(base, my_s_z, s_z);

    CY_CRYPTO_VU_ALLOC_MEM (base, t1, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t2, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t3, size);

    CY_CRYPTO_VU_SET_TO_ONE (base, t1);                     /* t1 = 1 */
    Cy_Crypto_Core_EC_DivMod( base, t2, t1, my_s_z, size);  /* t2 = 1/Z */

    Cy_Crypto_Core_EC_SquareMod( base, t1, t2, size);       /* t1 = 1/Z^2 */
    Cy_Crypto_Core_EC_MulMod( base, my_s_x, my_s_x, t1, size);  /* my_s_x = X/Z^2 */

    Cy_Crypto_Core_EC_MulMod( base, t3, my_s_y, t1, size);  /* t3 = Y/Z^2 */
    Cy_Crypto_Core_EC_MulMod( base, my_s_y, t3, t2, size);  /* my_s_y = Y/Z^3 */

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t1) | CY_CRYPTO_VU_REG_BIT(t2) | CY_CRYPTO_VU_REG_BIT(t3));

    CY_CRYPTO_VU_POP_REG (base);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_JacobianEcAdd
****************************************************************************//**
*
* Elliptic curve point addition on mixed Jacobian projective (s) / affine (t) coordinates in GF(VR_P).
* Reference: "fast and regular algorithms for scalar multiplication over elliptic curves", M. Rivain.
* Upper case register variables refer to Jacobian projective coordinate values.
* Lower case register variables refer to affine coordinate values.
*
* \param base
* The pointer to a Crypto instance.
*
* \param s_x
* Register index for Jacobian projective X coordinate.
*
* \param s_y
* Register index for Jacobian projective Y coordinate.
*
* \param s_z
* Register index for Jacobian projective Z coordinate.
*
* \param t_x
* Register index for affine X coordinate.
*
* \param t_y
* Register index for affine Y coordinate.
*
* \param size
* Bit size.
*
*******************************************************************************/
void Cy_Crypto_Core_JacobianEcAdd(CRYPTO_Type *base,
    uint32_t s_x,
    uint32_t s_y,
    uint32_t s_z,
    uint32_t t_x,
    uint32_t t_y,
    uint32_t size
)
{

    uint32_t t6     = 4u;
    uint32_t t7     = 5u;
    uint32_t t8     = 6u;
    uint32_t t9     = 7u;
    uint32_t my_s_x = 8u;
    uint32_t my_s_y = 9u;
    uint32_t my_s_z = 10u;
    uint32_t my_t_x = 11u;
    uint32_t my_t_y = 12u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG(base, my_s_x, s_x);
    CY_CRYPTO_VU_LD_REG(base, my_s_y, s_y);
    CY_CRYPTO_VU_LD_REG(base, my_s_z, s_z);
    CY_CRYPTO_VU_LD_REG(base, my_t_x, t_x);
    CY_CRYPTO_VU_LD_REG(base, my_t_y, t_y);

    CY_CRYPTO_VU_ALLOC_MEM (base, t6, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t7, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t8, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t9, size);

    Cy_Crypto_Core_EC_SquareMod( base, t6, my_s_z, size);       /* t6 = ZZ */
    Cy_Crypto_Core_EC_MulMod( base, t8, my_t_x, t6, size);      /* t8 = xZZ = B */
    Cy_Crypto_Core_EC_MulMod( base, t7, my_t_y, my_s_z, size);  /* t7 = yZ */
    Cy_Crypto_Core_EC_SubMod( base, my_s_x, my_s_x, t8);        /* my_s_x = X - B = E */

    Cy_Crypto_Core_EC_MulMod( base, my_s_z, my_s_x, my_s_z, size);  /* my_s_z = E*Z = Z3 */
    Cy_Crypto_Core_EC_MulMod( base, t9, t7, t6, size);          /* t9 = yZZZ = D */
    Cy_Crypto_Core_EC_SubMod( base, my_s_y, my_s_y, t9);        /* my_s_y = Y - D = F */
    Cy_Crypto_Core_EC_SquareMod( base, t6, my_s_x, size);       /* t6 = EE */

    Cy_Crypto_Core_EC_MulMod( base, t7, t8, t6, size);          /* t7 = B*EE */
    Cy_Crypto_Core_EC_MulMod( base, t8, t6, my_s_x, size);      /* t8 = EEE */
    Cy_Crypto_Core_EC_MulMod( base, t6, t9, t8, size);          /* t6 = D*EEE */
    Cy_Crypto_Core_EC_SquareMod( base, my_s_x, my_s_y, size);   /* my_s_x = FF */
    Cy_Crypto_Core_EC_SubMod( base, my_s_x, my_s_x, t8);        /* my_s_x = FF - EEE */
    Cy_Crypto_Core_EC_AddMod( base, t9, t7, t7);                /* t9 = 2*B*EE */
    Cy_Crypto_Core_EC_SubMod( base, my_s_x, my_s_x, t9);        /* my_s_x = FF - EEE - 2*B*EE = X3 */
    Cy_Crypto_Core_EC_SubMod( base, t7, t7, my_s_x);            /* t7 = B*EE - X3 */
    Cy_Crypto_Core_EC_MulMod( base, my_s_y, my_s_y, t7, size);  /* my_s_y = F*(B*EE - X3) */
    Cy_Crypto_Core_EC_SubMod( base, my_s_y, my_s_y, t6);        /* my_s_y = F*(3*B*EE - FF + EEE) - D*EEE = Y3 */

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t6) | CY_CRYPTO_VU_REG_BIT(t7) |
                                 CY_CRYPTO_VU_REG_BIT(t8) | CY_CRYPTO_VU_REG_BIT(t9));

    CY_CRYPTO_VU_POP_REG (base);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_JacobianEcDouble
****************************************************************************//**
*
* Elliptic curve point doubling on Jacobian projective coordinates in GF(VR_P).
*
* \param base
* The pointer to a Crypto instance.
*
* \param s_x
* Register index for Jacobian projective X coordinate.
*
* \param s_y
* Register index for Jacobian projective Y coordinate.
*
* \param s_z
* Register index for Jacobian projective Z coordinate.
*
* \param size
* Bit size.
*
*******************************************************************************/
void Cy_Crypto_Core_JacobianEcDouble(CRYPTO_Type *base,
    uint32_t s_x,
    uint32_t s_y,
    uint32_t s_z,
    uint32_t size
)
/* 4M + 4S + 10A */
{
    uint32_t t1     = 1u;
    uint32_t t2     = 2u;
    uint32_t t3     = 3u;
    uint32_t t4     = 4u;
    uint32_t my_s_x = 5u;
    uint32_t my_s_y = 6u;
    uint32_t my_s_z = 7u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG(base, my_s_x, s_x);
    CY_CRYPTO_VU_LD_REG(base, my_s_y, s_y);
    CY_CRYPTO_VU_LD_REG(base, my_s_z, s_z);

    CY_CRYPTO_VU_ALLOC_MEM (base, t1, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t2, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t3, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t4, size);

    Cy_Crypto_Core_EC_SquareMod( base, t4, my_s_y, size);       /* t4 = Y^2 */
    Cy_Crypto_Core_EC_SquareMod( base, t3, my_s_z, size);       /* t3 = Z^2 */
    Cy_Crypto_Core_EC_MulMod( base, my_s_z, my_s_y, my_s_z, size);  /* my_s_z = Y*Z */

    Cy_Crypto_Core_EC_MulMod( base, my_s_y, my_s_x, t4, size);  /* my_s_y = X*Y^2 = A */
    Cy_Crypto_Core_EC_AddMod( base, my_s_x, my_s_x, t3);        /* my_s_x = X + Z^2 */
    Cy_Crypto_Core_EC_AddMod( base, t3, t3, t3);                /* t3 = 2*Z^2 */
    Cy_Crypto_Core_EC_SubMod( base, t3, my_s_x, t3);            /* t3 = (X + Z^2) - 2*Z^2 = X - Z^2 */
    Cy_Crypto_Core_EC_MulMod( base, t1, my_s_x, t3, size);      /* t1 = (X + Z^2) * (X - Z^2) = X^2 - Z^4 */

    Cy_Crypto_Core_EC_AddMod( base, t3, t1, t1);                /* t3 = 2*(X^2 - Z^4) */
    Cy_Crypto_Core_EC_AddMod( base, t1, t1, t3);                /* t1 = 3*(X^2 - Z^4) */
    Cy_Crypto_Core_EC_HalfMod( base, t1, t1);                   /* t1 = 3/2*(X^2 - Z^4) = B */
    Cy_Crypto_Core_EC_SquareMod( base, t3, t1, size);           /* t3 = 9/4*(X^2 - Z^4) = B^2 */

    Cy_Crypto_Core_EC_SubMod( base, t3, t3, my_s_y);            /* t3 = B^2 - A */
    Cy_Crypto_Core_EC_SubMod( base, my_s_x, t3, my_s_y);        /* my_s_x =  B^2 - 2*A */
    Cy_Crypto_Core_EC_SubMod( base, my_s_y, my_s_y, my_s_x);    /* my_s_y = A - (B^2 - 2*A) = 3*A - B^2 */
    Cy_Crypto_Core_EC_MulMod( base, t2, t1, my_s_y, size);      /* t2 = B*(3*A - B^2) */

    Cy_Crypto_Core_EC_SquareMod( base, t1, t4, size);           /* t1 = Y^4 */
    Cy_Crypto_Core_EC_SubMod( base, my_s_y, t2, t1);            /* my_s_y = B*(3*A - B^2) - Y^4 */

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(t1) | CY_CRYPTO_VU_REG_BIT(t2) |
                                 CY_CRYPTO_VU_REG_BIT(t3) | CY_CRYPTO_VU_REG_BIT(t4));
    CY_CRYPTO_VU_POP_REG (base);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_JacobianEcScalarMul
****************************************************************************//**
*
* Elliptic curve point multiplication on Jacobian projective coordinates in GF(VR_P).
*
* \param base
* The pointer to a Crypto instance.
*
* \param s_x
* Register index for affine X coordinate.
*
* \param s_y
* Register index for affine Y coordinate.
*
* \param d
* Register index for multiplication/exponentiation value.
*
* \param size
* Bit size.
*
*******************************************************************************/
void Cy_Crypto_Core_JacobianEcScalarMul(CRYPTO_Type *base, uint32_t s_x, uint32_t s_y, uint32_t d, uint32_t size)
{
    int32_t i;
    uint32_t status;
    uint32_t carry;
    uint16_t clsame;

    uint32_t clr     = 5u;
    uint32_t t       = 6u;
    uint32_t my_s_x  = 7u;
    uint32_t my_s_y  = 8u;
    uint32_t my_s_z  = 9u;
    uint32_t my_t_x  = 10u;
    uint32_t my_t_y  = 11u;
    uint32_t my_d    = 12u;

    CY_CRYPTO_VU_PUSH_REG (base);

    CY_CRYPTO_VU_LD_REG(base, my_s_x, s_x);
    CY_CRYPTO_VU_LD_REG(base, my_s_y, s_y);
    CY_CRYPTO_VU_LD_REG(base, my_d, d);

    CY_CRYPTO_VU_ALLOC_MEM (base, clr, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, t, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, my_s_z, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, my_t_x, size);
    CY_CRYPTO_VU_ALLOC_MEM (base, my_t_y, size);

    /* my_t_x has the same initial value of my_s_x, but does not point to the
    * same address in memory as my_s_x, i.e. different value after point doubling
    * my_t_x and my_t_y do not change from (original Jacobian projective coordinates of)
    * original base point
    */
    CY_CRYPTO_VU_MOV (base, my_t_x, my_s_x);
    CY_CRYPTO_VU_MOV (base, my_t_y, my_s_y);

    /* Affine-to-Jacobian Transform. */
    CY_CRYPTO_VU_SET_TO_ONE (base, my_s_z);

    /* EC scalar multiplication (irregular) operation. */
    CY_CRYPTO_VU_SET_TO_ZERO (base, clr);
    CY_CRYPTO_VU_CLSAME (base, t, my_d, clr);

    /* This is needed, otherwise clsame is wrong */
    Cy_Crypto_Core_Vu_WaitForComplete(base);

    clsame = Cy_Crypto_Core_Vu_RegDataPtrRead (base, t);

    CY_CRYPTO_VU_LSL  (base, my_d, my_d, t); /* Get rid of leading '0's */
    CY_CRYPTO_VU_LSL1 (base, my_d, my_d);    /* Get rid of leading '1' */

    /* Binary left-to-right algorithm
    * Perform point addition and point doubling to implement scalar multiplication
    * Scan the bits of the scalar from left to right; perform point doubling for each bit,
    * and perform point addition when the bit is set.
    * Carry set if current bit is equal to 1 (hence, perform point addition - point
    * doubling is always performed)
    */
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to int32_t because result of composite expression can be negative');
    for (i = 0; i < ((int32_t)(size - clsame - 1u)); i++)
    {
        /* Carry set if current bit is equal to 1 (hence, perform point addition - point
        * doubling is always performed)
        */
        CY_CRYPTO_VU_LSL1 (base, my_d, my_d);
        status = Cy_Crypto_Core_Vu_StatusRead(base);

        carry = status & CY_CRYPTO_VU_STATUS_CARRY_BIT;

        Cy_Crypto_Core_JacobianEcDouble (base, my_s_x, my_s_y, my_s_z, size);

        if (carry != 0U)
        {
            Cy_Crypto_Core_JacobianEcAdd (base, my_s_x, my_s_y, my_s_z, my_t_x, my_t_y, size);
        }
    }

    /* Inverse transform */
    Cy_Crypto_Core_JacobianInvTransform(base, my_s_x, my_s_y, my_s_z, size);

    CY_CRYPTO_VU_FREE_MEM (base, CY_CRYPTO_VU_REG_BIT(my_s_z) |
                                 CY_CRYPTO_VU_REG_BIT(my_t_x) | CY_CRYPTO_VU_REG_BIT(my_t_y) |
                                 CY_CRYPTO_VU_REG_BIT(clr)    | CY_CRYPTO_VU_REG_BIT(t));

    CY_CRYPTO_VU_POP_REG (base);
}

/***************************************************************
*                   Test methods
***************************************************************/


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_NistP_SetMode
****************************************************************************//**
*
* Enable some curve specific features.
*
* \param bitsize
* bitsize of the used NIST P curve.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_NistP_SetMode(uint32_t bitsize)
{
    switch (bitsize)
    {
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED)
        case CY_CRYPTO_ECC_P192_SIZE:
            eccMode = CY_CRYPTO_ECC_ECP_SECP192R1;
            break;
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED) */
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED)
        case CY_CRYPTO_ECC_P224_SIZE:
            eccMode = CY_CRYPTO_ECC_ECP_SECP224R1;
            break;
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED) */
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED)
        case CY_CRYPTO_ECC_P256_SIZE:
            eccMode = CY_CRYPTO_ECC_ECP_SECP256R1;
            break;
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED) */
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED)
        case CY_CRYPTO_ECC_P384_SIZE:
            eccMode = CY_CRYPTO_ECC_ECP_SECP384R1;
            break;
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED) */
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED)
        case CY_CRYPTO_ECC_P521_SIZE:
            eccMode = CY_CRYPTO_ECC_ECP_SECP521R1;
            break;
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED) */
        default:
            eccMode = CY_CRYPTO_ECC_ECP_NONE;
            break;
    }
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_NistP_SetRedAlg
****************************************************************************//**
*
* Select which reduction algorithm has to be used.
*
* \param alg
* one of {CURVE_SPECIFIC_RED_ALG, SHIFT_MUL_RED_ALG, BARRETT_RED_ALG}.
* See \ref cy_en_crypto_ecc_red_mul_algs_t.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_NistP_SetRedAlg(cy_en_crypto_ecc_red_mul_algs_t alg)
{
    mul_red_alg_select = alg;
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_NistP_PointMul
****************************************************************************//**
*
* Elliptic curve point multiplication in GF(p).
*
* \param base
* The pointer to a Crypto instance.
*
* \param p_x
* Register index for affine X coordinate of base point.
*
* \param p_y
* Register index for affine Y coordinate of base point.
*
* \param p_d
* Register index for multiplication value.
*
* \param p_order
* Register index for order value..
*
* \param bitsize
* Bit size of the used curve.
*
*******************************************************************************/
void Cy_Crypto_Core_EC_NistP_PointMul(CRYPTO_Type *base, uint32_t p_x, uint32_t p_y, uint32_t p_d, uint32_t p_order, uint32_t bitsize)
{
    (void)p_order; /* Suppress warning */
    Cy_Crypto_Core_JacobianEcScalarMul (base, p_x, p_y, p_d, bitsize);
    Cy_Crypto_Core_Vu_WaitForComplete(base);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_EC_NistP_PointMultiplication
****************************************************************************//**
*
* Elliptic curve point multiplication in GF(p).
*
* \param base
* The pointer to a Crypto instance.
*
* \param curveID
* See \ref cy_en_crypto_ecc_curve_id_t.
*
* \param ecpGX
* Register index for affine X coordinate of base point.
*
* \param ecpGY
* Register index for affine Y coordinate of base point.
*
* \param ecpD
* Register index for multiplication value.
*
* \param ecpQX
* Register index for affine X coordinate of result point.
*
* \param ecpQY
* Register index for affine Y coordinate of result point.
*
* \return status code. See \ref cy_en_crypto_status_t.
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_EC_NistP_PointMultiplication(CRYPTO_Type *base,
    cy_en_crypto_ecc_curve_id_t curveID,
    const uint8_t *ecpGX,
    const uint8_t *ecpGY,
    const uint8_t *ecpD,
    uint8_t *ecpQX,
    uint8_t *ecpQY)
{
    /* N.b. If using test vectors from "http://point-at-infinity.org/ecc/nisttv",
     * the 'k' values on the website are in decimal form, while the (x,y) result
     * coordinates are in hexadecimal form
     * Input format for 'd' scalar multiplier in this test is in hexadecimal form.
     * Hence, convert k_{dec} to d_{hex} for comparison of test values
     */

    /* Setup additional registers */
    uint32_t VR_ORDER = 9u;

    const uint8_t *p_polynomial = NULL;
    const uint8_t *p_barrett = NULL;

    cy_stc_crypto_ecc_dp_type *eccDp = Cy_Crypto_Core_ECC_GetCurveParams(curveID);

    cy_en_crypto_status_t myStatus = CY_CRYPTO_NOT_SUPPORTED;

    if (eccDp != NULL)
    {
        /* Setup curve specific parameters depending on mode */
        uint32_t bitsize;

        p_polynomial = eccDp->prime;
        p_barrett    = eccDp->barrett_p;
        bitsize      = eccDp->size;

        /* use Barrett reduction algorithm for operations modulo n (order of the base point) */
        Cy_Crypto_Core_EC_NistP_SetRedAlg(eccDp->algo);
        Cy_Crypto_Core_EC_NistP_SetMode(eccDp->size);

        myStatus = CY_CRYPTO_BAD_PARAMS;

        if ((NULL != ecpGX) && (NULL != ecpGY) && (NULL != ecpD) && (NULL != ecpQX) && (NULL != ecpQY))
        {
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
            /* Flush the cache */
            SCB_CleanDCache_by_Addr((volatile void *)ecpGX, (int32_t)CY_CRYPTO_BYTE_SIZE_OF_BITS(bitsize));
            SCB_CleanDCache_by_Addr((volatile void *)ecpGY, (int32_t)CY_CRYPTO_BYTE_SIZE_OF_BITS(bitsize));
            SCB_CleanDCache_by_Addr((volatile void *)ecpD, (int32_t)CY_CRYPTO_BYTE_SIZE_OF_BITS(bitsize));
#endif
            /* Public parameters and characteristics of elliptic curve */
            CY_CRYPTO_VU_ALLOC_MEM (base, VR_D, bitsize);        /* Scalar factor */
            CY_CRYPTO_VU_ALLOC_MEM (base, VR_S_X, bitsize);
            CY_CRYPTO_VU_ALLOC_MEM (base, VR_S_Y, bitsize);
            CY_CRYPTO_VU_ALLOC_MEM (base, VR_P, bitsize);
            CY_CRYPTO_VU_ALLOC_MEM (base, VR_BARRETT, bitsize + 1u);
            CY_CRYPTO_VU_ALLOC_MEM (base, VR_ORDER, bitsize);

            Cy_Crypto_Core_Vu_SetMemValue (base, VR_P, p_polynomial, bitsize);

            /* Preparation (either use precalculated or calculated). */
            Cy_Crypto_Core_Vu_SetMemValue (base, VR_BARRETT, p_barrett, bitsize + 1u);

            Cy_Crypto_Core_Vu_SetMemValue (base, VR_S_X, ecpGX, bitsize);
            Cy_Crypto_Core_Vu_SetMemValue (base, VR_S_Y, ecpGY, bitsize);
            Cy_Crypto_Core_Vu_SetMemValue (base, VR_D, ecpD, bitsize);

            /* ECC calculation: d * G mod p */
            Cy_Crypto_Core_EC_NistP_PointMul(base, VR_S_X, VR_S_Y, VR_D, VR_ORDER, bitsize);

            /* Get result P = (X,Y) = d.G from EC scalar multiplication */
            Cy_Crypto_Core_Vu_GetMemValue (base, ecpQX, VR_S_X, bitsize);
            Cy_Crypto_Core_Vu_GetMemValue (base, ecpQY, VR_S_Y, bitsize);
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
            SCB_InvalidateDCache_by_Addr(ecpQX, (int32_t)CY_CRYPTO_BYTE_SIZE_OF_BITS(bitsize));
            SCB_InvalidateDCache_by_Addr(ecpQY, (int32_t)CY_CRYPTO_BYTE_SIZE_OF_BITS(bitsize));
#endif
            /* Free memory */
            CY_CRYPTO_VU_FREE_MEM (base,
                                    CY_CRYPTO_VU_REG_BIT(VR_ORDER) |
                                    CY_CRYPTO_VU_REG_BIT(VR_BARRETT) |
                                    CY_CRYPTO_VU_REG_BIT(VR_P) |
                                    CY_CRYPTO_VU_REG_BIT(VR_S_Y) |
                                    CY_CRYPTO_VU_REG_BIT(VR_S_X) |
                                    CY_CRYPTO_VU_REG_BIT(VR_D));

            myStatus = CY_CRYPTO_SUCCESS;
        }
    }

    return myStatus;
}

#endif /* defined (CY_CRYPTO_CFG_ECP_C) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */


/* [] END OF FILE */
