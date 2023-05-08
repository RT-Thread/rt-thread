/***************************************************************************//**
* \file cy_crypto_core_ecc_ecdsa.c
* \version 2.70
*
* \brief
*  This file provides constant and parameters for the API for the ECC ECDSA
*  in the Crypto driver.
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

#include "cy_crypto_core_ecc.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(CY_CRYPTO_CFG_ECDSA_C)

#include "cy_crypto_core_ecc_nist_p.h"
#include "cy_crypto_core_mem.h"
#include "cy_crypto_core_vu.h"

#if defined(CY_CRYPTO_CFG_ECDSA_SIGN_C)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_ECC_SignHash
****************************************************************************//**
*
* Sign a message digest.
*
* For CAT1C devices when D-Cache is enabled parameters hash, sign, messageKey and key( k, x&y of pubkey) must align and end in 32 byte boundary.
*
* \param base
* The pointer to a Crypto instance.
*
* \param hash
* The message digest to sign. Provided as is in data buffer.
*
* \param hashlen
* The length of the digest in bytes.
*
* \param sig
* [out] The destination for the signature, 'r' followed by 's'.
*
* \param key
* Key used for signature generation. See \ref cy_stc_crypto_ecc_key.
*
* \param messageKey
* Message key.
*
* \return status code. See \ref cy_en_crypto_status_t.
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_ECC_SignHash(CRYPTO_Type *base, const uint8_t *hash, uint32_t hashlen, uint8_t *sig,
        const cy_stc_crypto_ecc_key *key, const uint8_t *messageKey)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;

    cy_stc_crypto_ecc_key ephKey;

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
    CY_SECTION_SHAREDMEM
    CY_ALIGN(__SCB_DCACHE_LINE_SIZE) static uint8_t myKGX[CY_CRYPTO_ECC_MAX_BYTE_SIZE];
    CY_SECTION_SHAREDMEM
    CY_ALIGN(__SCB_DCACHE_LINE_SIZE) static uint8_t myKGY[CY_CRYPTO_ECC_MAX_BYTE_SIZE];
#else
    uint8_t myKGX[CY_CRYPTO_ECC_MAX_BYTE_SIZE];
    uint8_t myKGY[CY_CRYPTO_ECC_MAX_BYTE_SIZE];
#endif



    const cy_stc_crypto_ecc_dp_type *eccDp;
    uint32_t mallocMask = 0U;


    /* NULL parameters checking */
    if ((hash != NULL) && (0u != hashlen) && (sig != NULL) && (key != NULL) && (messageKey != NULL))
    {
        tmpResult = CY_CRYPTO_NOT_SUPPORTED;

        eccDp = Cy_Crypto_Core_ECC_GetCurveParams(key->curveID);

        if (eccDp != NULL)
        {
            uint32_t bitsize  = eccDp->size;
            uint32_t bytesize = CY_CRYPTO_BYTE_SIZE_OF_BITS(eccDp->size);
            uint32_t datasize = hashlen;

#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
            /* Flush the cache */
            SCB_CleanDCache_by_Addr((volatile void *)hash,(int32_t)hashlen);
            SCB_CleanDCache_by_Addr((volatile void *)key->k, (int32_t)bytesize);
            SCB_CleanDCache_by_Addr((volatile void *)messageKey,(int32_t)bytesize);
#endif

            /* make ephemeral key pair */
            ephKey.pubkey.x = myKGX;
            ephKey.pubkey.y = myKGY;

            tmpResult = Cy_Crypto_Core_ECC_MakePublicKey(base, key->curveID, messageKey, &ephKey);

            if (CY_CRYPTO_SUCCESS == tmpResult)
            {
                tmpResult = CY_CRYPTO_BAD_PARAMS;

                uint32_t dividend =  0U;   /* for whatever reason Crypto_EC_DivMod only works if dividend is in register 0 */
                uint32_t p_temp   =  8U;
                uint32_t p_r      =  9U;
                uint32_t p_s      = 10U;
                uint32_t p_d      = 11U;
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
                /* Flush the cache */
                SCB_CleanDCache_by_Addr((volatile void *)ephKey.pubkey.x,(int32_t)bytesize);
                SCB_CleanDCache_by_Addr((volatile void *)ephKey.pubkey.y, (int32_t)bytesize);
#endif
                /* load values needed for reduction modulo order of the base point */
                CY_CRYPTO_VU_ALLOC_MEM (base, VR_P, bitsize);
                Cy_Crypto_Core_Vu_SetMemValue (base, VR_P, (uint8_t *)eccDp->order, bitsize);

                CY_CRYPTO_VU_ALLOC_MEM (base, VR_BARRETT, bitsize + 1U);
                Cy_Crypto_Core_Vu_SetMemValue (base, VR_BARRETT, (uint8_t *)eccDp->barrett_o, bitsize);

                CY_CRYPTO_VU_ALLOC_MEM (base, p_r, bitsize);
                CY_CRYPTO_VU_ALLOC_MEM (base, p_s, bitsize);
                Cy_Crypto_Core_Vu_SetMemValue (base, p_r, (uint8_t *)ephKey.pubkey.x, bitsize);

                mallocMask = CY_CRYPTO_VU_REG_BIT(VR_P) | CY_CRYPTO_VU_REG_BIT(VR_BARRETT) |
                             CY_CRYPTO_VU_REG_BIT(p_r)  | CY_CRYPTO_VU_REG_BIT(p_s);

                if (!Cy_Crypto_Core_Vu_IsRegZero(base, p_r))
                {
                    tmpResult = CY_CRYPTO_SUCCESS;

                    CY_CRYPTO_VU_ALLOC_MEM (base, p_temp, bitsize);
                    CY_CRYPTO_VU_ALLOC_MEM (base, p_d, datasize * 8u);

                    /* check that x1 is smaller than the order of the base point */
                    if (!Cy_Crypto_Core_Vu_IsRegLess(base, p_r, VR_P))
                    {
                        /* x1 >= order, needs reduction */
                        CY_CRYPTO_VU_MOV(base, p_temp, p_r);
                        Cy_Crypto_Core_Vu_WaitForComplete(base);

                        /* z = x % mod */
                        Cy_Crypto_Core_EC_Bar_MulRed(base, p_r, p_temp, bitsize);

                        /* r = x1 mod n */
                        Cy_Crypto_Core_Vu_GetMemValue (base, sig, p_r, bitsize);

                        if (Cy_Crypto_Core_Vu_IsRegZero(base, p_r))
                        {
                            /* R is zero!!! */
                            tmpResult = CY_CRYPTO_HW_ERROR;
                        }
                    }
                    else
                    {
                        /* carry is clear, i. e. x1 < order, r = x1 */
                        Cy_Crypto_Core_Vu_GetMemValue(base, sig, p_r, bitsize);
                    }

                    if (CY_CRYPTO_SUCCESS == tmpResult)
                    {
                        /* find s = (e + d*r)/k */
                        /* load signing private key */
                        Cy_Crypto_Core_Vu_SetMemValue (base, p_temp, (uint8_t *)key->k, bitsize);

                        /* use Barrett reduction algorithm for operations modulo n (order of the base point) */
                        Cy_Crypto_Core_EC_NistP_SetRedAlg(CY_CRYPTO_NIST_P_BARRETT_RED_ALG);

                        /* d*r mod n */
                        Cy_Crypto_Core_EC_MulMod(base, p_s, p_temp, p_r, bitsize);    /* z = a * b % mod */

                        /* load message hash, truncate it if needed. */
                        Cy_Crypto_Core_Vu_SetMemValue (base, p_d, (uint8_t *)hash, datasize * 8u);
                        Cy_Crypto_Core_VU_RegInvertEndianness(base, p_d);

                        if ((datasize * 8u) > bitsize)
                        {
                            CY_CRYPTO_VU_SET_REG(base, dividend, (datasize * 8u) - bitsize, 1u);
                            CY_CRYPTO_VU_LSR(base, p_d, p_d, dividend);
                        }

                        /* check that the prepared hash value is smaller than the order of base point */
                        if (!Cy_Crypto_Core_Vu_IsRegLess(base, p_d, VR_P))
                        {
                            CY_CRYPTO_VU_MOV(base, p_temp, p_d);
                            Cy_Crypto_Core_Vu_WaitForComplete(base);

                            /* z = x % mod */
                            Cy_Crypto_Core_EC_Bar_MulRed(base, p_d, p_temp, bitsize);
                        }

                        /* Use p_r as temporary register */
                        Cy_Crypto_Core_Vu_SetMemValue (base, p_r, messageKey, bitsize);

                        /* e + d*r mod n */
                        Cy_Crypto_Core_EC_AddMod (base, p_s, p_d, p_s);      /* z = a + b % mod */

                        /* (e + d*r)/k mod n */
                        CY_CRYPTO_VU_ALLOC_MEM (base, dividend, bitsize);

                        CY_CRYPTO_VU_MOV(base, dividend, p_s);
                        Cy_Crypto_Core_Vu_WaitForComplete(base);

                        /* z = a / b % mod */
                        Cy_Crypto_Core_EC_DivMod(base, p_s, dividend, p_r, bitsize);

                        CY_CRYPTO_VU_FREE_MEM(base, CY_CRYPTO_VU_REG_BIT(dividend));

                        if (!Cy_Crypto_Core_Vu_IsRegZero(base, p_s))
                        {
                            /* S is not zero!!! */
                            Cy_Crypto_Core_Vu_GetMemValue (base, &sig[bytesize], p_s, bitsize);
                        }
                        else
                        {
                            tmpResult = CY_CRYPTO_HW_ERROR;
                        }
                    }

                    CY_CRYPTO_VU_FREE_MEM(base, CY_CRYPTO_VU_REG_BIT(p_d) | CY_CRYPTO_VU_REG_BIT(p_temp));
                }

                CY_CRYPTO_VU_FREE_MEM(base, mallocMask);
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
                CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to int32_t.');
                SCB_InvalidateDCache_by_Addr(sig, (int32_t)(bytesize*2U));
#endif
            }
        }
    }

    return (tmpResult);
}
#endif /* defined(CY_CRYPTO_CFG_ECDSA_SIGN_C) */

#if defined(CY_CRYPTO_CFG_ECDSA_VERIFY_C)
/*******************************************************************************
* Function Name: Cy_Crypto_Core_ECC_VerifyHash
****************************************************************************//**
*
* Verify an ECC signature.
*
* For CAT1C devices when D-Cache is enabled parameters sig, hash and key( x&y of pubkey) must align and end in 32 byte boundary.
*
* \param base
* The pointer to a Crypto instance.
*
* \param sig
* The signature to verify, 'R' followed by 'S'.
*
* \param hash
* The hash (message digest) that was signed.
*
* \param hashlen
* The length of the hash (octets).
*
* \param stat
* Result of signature, 1==valid, 0==invalid.
*
* \param key
* The corresponding public ECC key. See \ref cy_stc_crypto_ecc_key.
*
* \return status code. See \ref cy_en_crypto_status_t.
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_ECC_VerifyHash(CRYPTO_Type *base,
                            const uint8_t *sig, const uint8_t *hash, uint32_t hashlen,
                            uint8_t *stat, const cy_stc_crypto_ecc_key *key)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_BAD_PARAMS;

    const cy_stc_crypto_ecc_dp_type *eccDp;

    uint32_t mallocMask = 0U;
    bool isHashZero = false;


    /* NULL parameters checking */
    if ((sig != NULL) && (hash != NULL) && (0u != hashlen) && (stat != NULL) && (key != NULL))
    {
        tmpResult = CY_CRYPTO_NOT_SUPPORTED;

        eccDp = Cy_Crypto_Core_ECC_GetCurveParams(key->curveID);

        if (eccDp != NULL)
        {
            tmpResult = CY_CRYPTO_SUCCESS;

            uint32_t bitsize  = eccDp->size;
            uint32_t bytesize = CY_CRYPTO_BYTE_SIZE_OF_BITS(eccDp->size);
            uint32_t datasize = hashlen;

            uint32_t dividend = 0u;   /* for whatever reason Crypto_EC_DivMod only works if dividend is in register 0 */
            uint32_t p_r  = 4U;
            uint32_t p_s  = 5U;
            uint32_t p_u1 = 6U;
            uint32_t p_u2 = 7U;
            uint32_t p_o  = 8U;
            uint32_t p_gx = 9U;
            uint32_t p_gy = 10U;
            uint32_t p_qx = 11U;
            uint32_t p_qy = 12U;
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
            /* Flush the cache */
            SCB_CleanDCache_by_Addr((volatile void *)hash,(int32_t)hashlen);
            SCB_CleanDCache_by_Addr((volatile void *)key->pubkey.x, (int32_t)bytesize);
            SCB_CleanDCache_by_Addr((volatile void *)key->pubkey.y, (int32_t)bytesize);
            CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to int32_t.');
            SCB_CleanDCache_by_Addr((volatile void *)sig,(int32_t)(2u*bytesize));
            SCB_CleanDCache_by_Addr((volatile void *)eccDp->order,(int32_t)bytesize);
            SCB_CleanDCache_by_Addr((volatile void *)eccDp->Gx,(int32_t)bytesize);
            SCB_CleanDCache_by_Addr((volatile void *)eccDp->Gy,(int32_t)bytesize);
            SCB_CleanDCache_by_Addr((volatile void *)eccDp->prime,(int32_t)bytesize);
            CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to int32_t.');
            SCB_CleanDCache_by_Addr((volatile void *)eccDp->barrett_o,(int32_t)(bytesize+1u));
            CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to int32_t.');
            SCB_CleanDCache_by_Addr((volatile void *)eccDp->barrett_p,(int32_t)(bytesize+1u));
#endif
            /* use Barrett reduction algorithm for operations modulo n (order of the base point) */
            Cy_Crypto_Core_EC_NistP_SetRedAlg(CY_CRYPTO_NIST_P_BARRETT_RED_ALG);
            Cy_Crypto_Core_EC_NistP_SetMode(bitsize);

            /*******************************************************************************/
            /* load values needed for reduction modulo order of the base point             */
            CY_CRYPTO_VU_ALLOC_MEM (base, VR_P, bitsize);
            Cy_Crypto_Core_Vu_SetMemValue (base, VR_P, (uint8_t *)eccDp->order, bitsize);

            CY_CRYPTO_VU_ALLOC_MEM (base, VR_BARRETT, bitsize + 1U);
            Cy_Crypto_Core_Vu_SetMemValue (base, VR_BARRETT, (uint8_t *)eccDp->barrett_o, bitsize + 1U);

            /*******************************************************************************/
            /* check that R and S are within the valid range, i.e. 0 < R < n and 0 < S < n */
            CY_CRYPTO_VU_ALLOC_MEM (base, p_r, bitsize);
            CY_CRYPTO_VU_ALLOC_MEM (base, p_s, bitsize);
            Cy_Crypto_Core_Vu_SetMemValue (base, p_r, (uint8_t *)sig, bitsize);
            Cy_Crypto_Core_Vu_SetMemValue (base, p_s, (uint8_t *)&sig[bytesize], bitsize);

            mallocMask = CY_CRYPTO_VU_REG_BIT(VR_P) | CY_CRYPTO_VU_REG_BIT(VR_BARRETT) |
                         CY_CRYPTO_VU_REG_BIT(p_r)  | CY_CRYPTO_VU_REG_BIT(p_s);

            /* Check R and S range */
            if (Cy_Crypto_Core_Vu_IsRegZero(base, p_r))
            {
                /* R is zero!!! */
                tmpResult = CY_CRYPTO_BAD_PARAMS;
            }
            if (!Cy_Crypto_Core_Vu_IsRegLess(base, p_r, VR_P))
            {
                /* R is not less than n!!! */
                tmpResult = CY_CRYPTO_BAD_PARAMS;
            }
            if (Cy_Crypto_Core_Vu_IsRegZero(base, p_s))
            {
                /* S is zero!!! */
                tmpResult = CY_CRYPTO_BAD_PARAMS;
            }
            if (!Cy_Crypto_Core_Vu_IsRegLess(base, p_s, VR_P))
            {
                /* S is not less than n!!! */
                tmpResult = CY_CRYPTO_BAD_PARAMS;
            }

            if (CY_CRYPTO_SUCCESS == tmpResult)
            {
                CY_CRYPTO_VU_ALLOC_MEM (base, p_u1, bitsize);
                CY_CRYPTO_VU_ALLOC_MEM (base, p_u2, bitsize);

                CY_CRYPTO_VU_ALLOC_MEM (base, p_gx, bitsize);
                CY_CRYPTO_VU_ALLOC_MEM (base, p_gy, bitsize);
                CY_CRYPTO_VU_ALLOC_MEM (base, p_qx, bitsize);
                CY_CRYPTO_VU_ALLOC_MEM (base, p_qy, bitsize);

                mallocMask |= CY_CRYPTO_VU_REG_BIT(dividend) |
                              CY_CRYPTO_VU_REG_BIT(p_u1) | CY_CRYPTO_VU_REG_BIT(p_u2) |
                              CY_CRYPTO_VU_REG_BIT(p_gx) | CY_CRYPTO_VU_REG_BIT(p_gy) |
                              CY_CRYPTO_VU_REG_BIT(p_qx) | CY_CRYPTO_VU_REG_BIT(p_qy);

                /* load message hash, truncate it if needed */
                CY_CRYPTO_VU_SET_TO_ZERO(base, p_u1);

                /* load message hash, truncate it if needed. */
                CY_CRYPTO_VU_ALLOC_MEM (base, p_o,  datasize * 8u);

                CY_CRYPTO_VU_SET_TO_ZERO(base, p_o);
                Cy_Crypto_Core_Vu_SetMemValue (base, p_o, (uint8_t *)hash, datasize * 8u);
                Cy_Crypto_Core_VU_RegInvertEndianness(base, p_o);

                /* Check if message hash is zero */
                if(Cy_Crypto_Core_Vu_IsRegZero(base, p_o))
                {
                    isHashZero = true;
                }

                if ((datasize * 8u) > bitsize)
                {
                    CY_CRYPTO_VU_SET_REG(base, dividend, (datasize * 8u) - bitsize, 1u);
                    CY_CRYPTO_VU_LSR(base, p_o, p_o, dividend);
                }

                /* Use p_o as temporary register */
                CY_CRYPTO_VU_MOV(base, p_u1, p_o);

                CY_CRYPTO_VU_FREE_MEM(base, CY_CRYPTO_VU_REG_BIT(p_o));
                CY_CRYPTO_VU_ALLOC_MEM (base, p_o, bitsize);
                CY_CRYPTO_VU_ALLOC_MEM (base, dividend, bitsize);

                /* check that the prepared hash value is smaller than the order of base point */
                if (!Cy_Crypto_Core_Vu_IsRegLess(base, p_u1, VR_P))
                {
                    /* Use p_o as temporary register */
                    CY_CRYPTO_VU_MOV(base, p_o, p_u1);
                    Cy_Crypto_Core_Vu_WaitForComplete(base);

                    /* z = x % mod */
                    Cy_Crypto_Core_EC_Bar_MulRed(base, p_u1, p_o, bitsize);
                }

                /* w = s^-1 mod n */
                CY_CRYPTO_VU_SET_TO_ONE(base, dividend);
                Cy_Crypto_Core_EC_DivMod(base, p_s, dividend, p_s, bitsize);

                /* u1 = e*w mod n */
                Cy_Crypto_Core_EC_MulMod(base, p_u1, p_u1, p_s, bitsize);

                /* u2 = r*w mod n */
                Cy_Crypto_Core_EC_MulMod(base, p_u2, p_r, p_s, bitsize);

                /* Initialize point multiplication */
                Cy_Crypto_Core_EC_NistP_SetRedAlg(eccDp->algo);

                /* load prime, order and Barrett coefficient */
                Cy_Crypto_Core_Vu_SetMemValue (base, VR_P, (uint8_t *)eccDp->prime, bitsize);
                Cy_Crypto_Core_Vu_SetMemValue (base, VR_BARRETT, (uint8_t *)eccDp->barrett_p, bitsize + 1U);

                /* load base Point G */
                Cy_Crypto_Core_Vu_SetMemValue (base, p_gx, (uint8_t *)eccDp->Gx, bitsize);
                Cy_Crypto_Core_Vu_SetMemValue (base, p_gy, (uint8_t *)eccDp->Gy, bitsize);

                /* load public key Qa */
                Cy_Crypto_Core_Vu_SetMemValue (base, p_qx, (uint8_t *)key->pubkey.x, bitsize);
                Cy_Crypto_Core_Vu_SetMemValue (base, p_qy, (uint8_t *)key->pubkey.y, bitsize);

                /* u1 * G */
                Cy_Crypto_Core_EC_NistP_PointMul(base, p_gx, p_gy, p_u1, p_o, bitsize);

                /* u2 * Qa */
                Cy_Crypto_Core_EC_NistP_PointMul(base, p_qx, p_qy, p_u2, p_o, bitsize);

                if(isHashZero)
                {
                    /* GECC 3.22 */
                    CY_CRYPTO_VU_MOV(base, p_s, p_qx);
                }
                else
                {
                    /* P = u1 * G + u2 * Qa. Only Px is needed */
                    Cy_Crypto_Core_EC_SubMod(base, dividend, p_qy, p_gy);            /* (y2-y1) */
                    Cy_Crypto_Core_EC_SubMod(base, p_s, p_qx, p_gx);                /* (x2-x1) */
                    Cy_Crypto_Core_EC_DivMod(base, p_s, dividend, p_s, bitsize);    /* s = (y2-y1)/(x2-x1) */

                    Cy_Crypto_Core_EC_SquareMod (base, p_s, p_s, bitsize);           /* s^2 */
                    Cy_Crypto_Core_EC_SubMod    (base, p_s, p_s, p_gx);            /* s^2 - x1 */
                    Cy_Crypto_Core_EC_SubMod    (base, p_s, p_s, p_qx);            /* s^2 - x1 - x2 which is Px mod n */
                }

                CY_CRYPTO_VU_FREE_MEM(base, CY_CRYPTO_VU_REG_BIT(p_o));

                if (Cy_Crypto_Core_Vu_IsRegEqual(base, p_s, p_r))
                {
                    *stat = 1u;
                }
                else
                {
                    *stat = 0u;
                }
            }

            CY_CRYPTO_VU_FREE_MEM(base, mallocMask);
        }
    }

    return (tmpResult);
}
#endif /* defined(CY_CRYPTO_CFG_ECDSA_VERIFY_C) */

#endif /* defined(CY_CRYPTO_CFG_ECDSA_C) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */


/* [] END OF FILE */
