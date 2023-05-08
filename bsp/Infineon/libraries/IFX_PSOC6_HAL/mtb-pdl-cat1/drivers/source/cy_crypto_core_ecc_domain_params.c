/***************************************************************************//**
* \file cy_crypto_core_ecc_domain_params.c
* \version 2.70
*
* \brief
*  This file provides constant and parameters for the API for the ECC
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

#if defined (CY_CRYPTO_CFG_ECP_C)

/*******************************************************************************
* Function Name: Cy_Crypto_Core_ECC_GetCurveParams
****************************************************************************//**
*
* Get curve domain parameters if this curve is supported.
*
* \param curveId
* See \ref cy_en_crypto_ecc_curve_id_t.
*
* \return
* Pointer to curve domain parameters. See \ref cy_stc_crypto_ecc_dp_type.
*
*******************************************************************************/
cy_stc_crypto_ecc_dp_type *Cy_Crypto_Core_ECC_GetCurveParams(cy_en_crypto_ecc_curve_id_t curveId)
{
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED)
    /* P192 CURVE PARAMETERS */
    CY_ALIGN(4) static const uint8_t  eccP192Polynomial[CY_CRYPTO_ECC_P192_BYTE_SIZE] =
    {
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xfeu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
    };

    CY_ALIGN(4) static const uint8_t  eccP192PolyBarrett[CY_CRYPTO_ECC_P192_BYTE_SIZE + 1u] =
    {  /* pre-calculated */
       0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x01u
    };
    CY_ALIGN(4) static const uint8_t  eccP192Order[CY_CRYPTO_ECC_P192_BYTE_SIZE] =
    {
        0x31u, 0x28u, 0xD2u, 0xB4u, 0xB1u, 0xC9u, 0x6Bu, 0x14u,
        0x36u, 0xF8u, 0xDEu, 0x99u, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu
    };

    /* barrett_o: "1000000000000000000000000662107c9eb94364e4b2dd7cf" */
    CY_ALIGN(4) static const uint8_t  eccP192OrderBarrett[CY_CRYPTO_ECC_P192_BYTE_SIZE + 1u] =
    {   /* pre-calculated */
        0xcfu, 0xd7u, 0x2du, 0x4bu, 0x4eu, 0x36u, 0x94u, 0xebu,
        0xc9u, 0x07u, 0x21u, 0x66u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x01u
    };

    /* base point x: "188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012" */
    CY_ALIGN(4) static const uint8_t  eccP192BasePointX[CY_CRYPTO_ECC_P192_BYTE_SIZE] =
    {
        0x12u, 0x10u, 0xffu, 0x82u, 0xfdu, 0x0au, 0xffu, 0xf4u,
        0x00u, 0x88u, 0xa1u, 0x43u, 0xebu, 0x20u, 0xbfu, 0x7cu,
        0xf6u, 0x90u, 0x30u, 0xb0u, 0x0eu, 0xa8u, 0x8du, 0x18u
    };

    /* base point y: "07192B95FFC8DA78631011ED6B24CDD573F977A11E794811" */
    CY_ALIGN(4) static const uint8_t  eccP192BasePointY[CY_CRYPTO_ECC_P192_BYTE_SIZE] =
    {
        0x11u, 0x48u, 0x79u, 0x1eu, 0xa1u, 0x77u, 0xf9u, 0x73u,
        0xd5u, 0xcdu, 0x24u, 0x6bu, 0xedu, 0x11u, 0x10u, 0x63u,
        0x78u, 0xdau, 0xc8u, 0xffu, 0x95u, 0x2bu, 0x19u, 0x07u
    };
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED) */

#if defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED)
    /* P224 CURVE PARAMETERS */
    CY_ALIGN(4) static const uint8_t  eccP224Polynomial[CY_CRYPTO_ECC_P224_BYTE_SIZE] =
    {
       0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu
    };

    CY_ALIGN(4) static const uint8_t  eccP224PolyBarrett[CY_CRYPTO_ECC_P224_BYTE_SIZE + 1u] =
    {  /* pre-calculated */
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x01u
    };

    CY_ALIGN(4) static const uint8_t  eccP224Order[CY_CRYPTO_ECC_P224_BYTE_SIZE] =
    {
        0x3Du, 0x2Au, 0x5Cu, 0x5Cu, 0x45u, 0x29u, 0xDDu, 0x13u,
        0x3Eu, 0xF0u, 0xB8u, 0xE0u, 0xA2u, 0x16u, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu
    };
    /* barrett_o: "10000000000000000000000000000e95d1f470fc1ec22d6baa3a3d5c3" */
    CY_ALIGN(4) static const uint8_t  eccP224OrderBarrett[CY_CRYPTO_ECC_P224_BYTE_SIZE + 1u] =
    {   /* pre-calculated */
        0xc3u, 0xd5u, 0xa3u, 0xa3u, 0xbau, 0xd6u, 0x22u, 0xecu,
        0xc1u, 0x0fu, 0x47u, 0x1fu, 0x5du, 0xe9u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x01u
    };

    /* Gx - base point x: "B70E0CBD6BB4BF7F321390B94A03C1D356C21122343280D6115C1D21" */
    CY_ALIGN(4) static const uint8_t  eccP224BasePointX[CY_CRYPTO_ECC_P224_BYTE_SIZE] =
    {
        0x21u, 0x1du, 0x5cu, 0x11u, 0xd6u, 0x80u, 0x32u, 0x34u,
        0x22u, 0x11u, 0xc2u, 0x56u, 0xd3u, 0xc1u, 0x03u, 0x4au,
        0xb9u, 0x90u, 0x13u, 0x32u, 0x7fu, 0xbfu, 0xb4u, 0x6bu,
        0xbdu, 0x0cu, 0x0eu, 0xb7u
    };

    /* Gy - base point y: "BD376388B5F723FB4C22DFE6CD4375A05A07476444D5819985007E34" */
    CY_ALIGN(4) static const uint8_t  eccP224BasePointY[CY_CRYPTO_ECC_P224_BYTE_SIZE] =
    {
        0x34u, 0x7eu, 0x00u, 0x85u, 0x99u, 0x81u, 0xd5u, 0x44u,
        0x64u, 0x47u, 0x07u, 0x5au, 0xa0u, 0x75u, 0x43u, 0xcdu,
        0xe6u, 0xdfu, 0x22u, 0x4cu, 0xfbu, 0x23u, 0xf7u, 0xb5u,
        0x88u, 0x63u, 0x37u, 0xbdu
    };
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED) */


#if defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED)
    /* P256 CURVE PARAMETERS */
    /* prime: "FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF" */
    CY_ALIGN(4) static const uint8_t  eccP256Polynomial[CY_CRYPTO_ECC_P256_BYTE_SIZE] =
    {
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x01u, 0x00u, 0x00u, 0x00u, 0xffu, 0xffu, 0xffu, 0xffu
    };

    /* barrett_p: "100000000fffffffffffffffefffffffefffffffeffffffff0000000000000003" */
    CY_ALIGN(4) static const uint8_t  eccP256PolyBarrett[CY_CRYPTO_ECC_P256_BYTE_SIZE + 1u] =
    {  /* pre-calculated! */
       0x03u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0xffu, 0xffu, 0xffu, 0xffu, 0xfeu, 0xffu, 0xffu, 0xffu,
       0xfeu, 0xffu, 0xffu, 0xffu, 0xfeu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0x00u, 0x00u, 0x00u, 0x00u,
       0x01u
    };

    /* order: "FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551" */
    CY_ALIGN(4) static const uint8_t  eccP256Order[CY_CRYPTO_ECC_P256_BYTE_SIZE] =
    {
        0x51u, 0x25u, 0x63u, 0xfcu, 0xc2u, 0xcau, 0xb9u, 0xf3u,
        0x84u, 0x9eu, 0x17u, 0xa7u, 0xadu, 0xfau, 0xe6u, 0xbcu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0x00u, 0x00u, 0x00u, 0x00u, 0xffu, 0xffu, 0xffu, 0xffu
    };

    /* barrett_o: 100000000fffffffffffffffeffffffff43190552df1a6c21012ffd85eedf9bfe" */
    CY_ALIGN(4) static const uint8_t  eccP256OrderBarrett[CY_CRYPTO_ECC_P256_BYTE_SIZE + 1u] =
    {   /* pre-calculated */
        0xfeu, 0x9bu, 0xdfu, 0xeeu, 0x85u, 0xfdu, 0x2fu, 0x01u,
        0x21u, 0x6cu, 0x1au, 0xdfu, 0x52u, 0x05u, 0x19u, 0x43u,
        0xffu, 0xffu, 0xffu, 0xffu, 0xfeu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0x00u, 0x00u, 0x00u, 0x00u,
        0x01u
    };

    /* base point x: "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296" */
    CY_ALIGN(4) static const uint8_t  eccP256BasePointX[CY_CRYPTO_ECC_P256_BYTE_SIZE] =
    {
        0x96u, 0xc2u, 0x98u, 0xd8u, 0x45u, 0x39u, 0xa1u, 0xf4u,
        0xa0u, 0x33u, 0xebu, 0x2du, 0x81u, 0x7du, 0x03u, 0x77u,
        0xf2u, 0x40u, 0xa4u, 0x63u, 0xe5u, 0xe6u, 0xbcu, 0xf8u,
        0x47u, 0x42u, 0x2cu, 0xe1u, 0xf2u, 0xd1u, 0x17u, 0x6bu
    };

    /* base point y: "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5" */
    CY_ALIGN(4) static const uint8_t  eccP256BasePointY[CY_CRYPTO_ECC_P256_BYTE_SIZE] =
    {
        0xf5u, 0x51u, 0xbfu, 0x37u, 0x68u, 0x40u, 0xb6u, 0xcbu,
        0xceu, 0x5eu, 0x31u, 0x6bu, 0x57u, 0x33u, 0xceu, 0x2bu,
        0x16u, 0x9eu, 0x0fu, 0x7cu, 0x4au, 0xebu, 0xe7u, 0x8eu,
        0x9bu, 0x7fu, 0x1au, 0xfeu, 0xe2u, 0x42u, 0xe3u, 0x4fu,
    };
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED) */

#if defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED)
    /* prime: "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF" */
    CY_ALIGN(4) static const uint8_t  eccP384Polynomial[CY_CRYPTO_ECC_P384_BYTE_SIZE] =
    {
        0xffu, 0xffu, 0xffu, 0xffu, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0xffu, 0xffu, 0xffu, 0xffu,
        0xfeu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu
    };

    /* barrett_p: "1000000000000000000000000000000000000000000000000000000000000000100000000ffffffffffffffff00000001" */
    CY_ALIGN(4) static const uint8_t  eccP384PolyBarrett[CY_CRYPTO_ECC_P384_BYTE_SIZE + 1u] =
    {   /* pre-calculated */
        0x01u, 0x00u, 0x00u, 0x00u, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0x00u, 0x00u, 0x00u, 0x00u,
        0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x01u
    };

    /* order: "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973" */
    CY_ALIGN(4) static const uint8_t  eccP384Order[CY_CRYPTO_ECC_P384_BYTE_SIZE] =
    {
        0x73u, 0x29u, 0xC5u, 0xCCu, 0x6Au, 0x19u, 0xECu, 0xECu,
        0x7Au, 0xA7u, 0xB0u, 0x48u, 0xB2u, 0x0Du, 0x1Au, 0x58u,
        0xDFu, 0x2Du, 0x37u, 0xF4u, 0x81u, 0x4Du, 0x63u, 0xC7u,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu
    };

    /* barrett_o: "1000000000000000000000000000000000000000000000000389cb27e0bc8d220a7e5f24db74f58851313e695333ad68d" */
    CY_ALIGN(4) static const uint8_t  eccP384OrderBarrett[CY_CRYPTO_ECC_P384_BYTE_SIZE + 1u] =
    {   /* pre-calculated */
        0x8du, 0xd6u, 0x3au, 0x33u, 0x95u, 0xe6u, 0x13u, 0x13u,
        0x85u, 0x58u, 0x4fu, 0xb7u, 0x4du, 0xf2u, 0xe5u, 0xa7u,
        0x20u, 0xd2u, 0xc8u, 0x0bu, 0x7eu, 0xb2u, 0x9cu, 0x38u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x01u
    };

    /* base point x: "AA87CA22BE8B05378EB1C71EF320AD746E1D3B628BA79B9859F741E082542A385502F25DBF55296C3A545E3872760AB7" */
    CY_ALIGN(4) static const uint8_t  eccP384BasePointX[CY_CRYPTO_ECC_P384_BYTE_SIZE] =
    {
        0xb7u, 0x0au, 0x76u, 0x72u, 0x38u, 0x5eu, 0x54u, 0x3au,
        0x6cu, 0x29u, 0x55u, 0xbfu, 0x5du, 0xf2u, 0x02u, 0x55u,
        0x38u, 0x2au, 0x54u, 0x82u, 0xe0u, 0x41u, 0xf7u, 0x59u,
        0x98u, 0x9bu, 0xa7u, 0x8bu, 0x62u, 0x3bu, 0x1du, 0x6eu,
        0x74u, 0xadu, 0x20u, 0xf3u, 0x1eu, 0xc7u, 0xb1u, 0x8eu,
        0x37u, 0x05u, 0x8bu, 0xbeu, 0x22u, 0xcau, 0x87u, 0xaau
    };

    /* base point y: "3617DE4A96262C6F5D9E98BF9292DC29F8F41DBD289A147CE9DA3113B5F0B8C00A60B1CE1D7E819D7A431D7C90EA0E5F" */
    CY_ALIGN(4) static const uint8_t  eccP384BasePointY[CY_CRYPTO_ECC_P384_BYTE_SIZE] =
    {
        0x5fu, 0x0eu, 0xeau, 0x90u, 0x7cu, 0x1du, 0x43u, 0x7au,
        0x9du, 0x81u, 0x7eu, 0x1du, 0xceu, 0xb1u, 0x60u, 0x0au,
        0xc0u, 0xb8u, 0xf0u, 0xb5u, 0x13u, 0x31u, 0xdau, 0xe9u,
        0x7cu, 0x14u, 0x9au, 0x28u, 0xbdu, 0x1du, 0xf4u, 0xf8u,
        0x29u, 0xdcu, 0x92u, 0x92u, 0xbfu, 0x98u, 0x9eu, 0x5du,
        0x6fu, 0x2cu, 0x26u, 0x96u, 0x4au, 0xdeu, 0x17u, 0x36u
    };
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED) */

#if defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED)
    CY_ALIGN(4) static const uint8_t  eccP521Polynomial[CY_CRYPTO_ECC_P521_BYTE_SIZE] =
    {
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
       0xffu, 0x01u
    };

    CY_ALIGN(4) static const uint8_t  eccP521PolyBarrett[CY_CRYPTO_ECC_P521_BYTE_SIZE] =
    {  /* pre-calculated */
       0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
       0x00u, 0x02u
    };

    CY_ALIGN(4) static const uint8_t  eccP521Order[CY_CRYPTO_ECC_P521_BYTE_SIZE] =
    {
        0x09u, 0x64u, 0x38u, 0x91u, 0x1Eu, 0xB7u, 0x6Fu, 0xBBu,
        0xAEu, 0x47u, 0x9Cu, 0x89u, 0xB8u, 0xC9u, 0xB5u, 0x3Bu,
        0xD0u, 0xA5u, 0x09u, 0xF7u, 0x48u, 0x01u, 0xCCu, 0x7Fu,
        0x6Bu, 0x96u, 0x2Fu, 0xBFu, 0x83u, 0x87u, 0x86u, 0x51u,
        0xFAu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu, 0xffu,
        0xffu, 0x01u
    };

    /* barrett_o: "2000000000000000000000000000000000000000000000000000000000000000005ae79787c40d069948033feb708f65a2fc44a36477663b851449048e16ec79bf7" */
    CY_ALIGN(4) static const uint8_t  eccP521OrderBarrett[CY_CRYPTO_ECC_P521_BYTE_SIZE] =
    {   /* pre-calculated */
        0xf7u, 0x9bu, 0xc7u, 0x6eu, 0xe1u, 0x48u, 0x90u, 0x44u,
        0x51u, 0xb8u, 0x63u, 0x76u, 0x47u, 0x36u, 0x4au, 0xc4u,
        0x2fu, 0x5au, 0xf6u, 0x08u, 0xb7u, 0xfeu, 0x33u, 0x80u,
        0x94u, 0x69u, 0xd0u, 0x40u, 0x7cu, 0x78u, 0x79u, 0xaeu,
        0x05u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x02u
    };

    /* base point x: "00C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66" */
    CY_ALIGN(4) static const uint8_t  eccP521BasePointX[CY_CRYPTO_ECC_P521_BYTE_SIZE] =
    {
        0x66u, 0xbdu, 0xe5u, 0xc2u, 0x31u, 0x7eu, 0x7eu, 0xf9u,
        0x9bu, 0x42u, 0x6au, 0x85u, 0xc1u, 0xb3u, 0x48u, 0x33u,
        0xdeu, 0xa8u, 0xffu, 0xa2u, 0x27u, 0xc1u, 0x1du, 0xfeu,
        0x28u, 0x59u, 0xe7u, 0xefu, 0x77u, 0x5eu, 0x4bu, 0xa1u,
        0xbau, 0x3du, 0x4du, 0x6bu, 0x60u, 0xafu, 0x28u, 0xf8u,
        0x21u, 0xb5u, 0x3fu, 0x05u, 0x39u, 0x81u, 0x64u, 0x9cu,
        0x42u, 0xb4u, 0x95u, 0x23u, 0x66u, 0xcbu, 0x3eu, 0x9eu,
        0xcdu, 0xe9u, 0x04u, 0x04u, 0xb7u, 0x06u, 0x8eu, 0x85u,
        0xc6u, 0x00u
    };

    /* base point y: "011839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650" */
    CY_ALIGN(4) static const uint8_t  eccP521BasePointY[CY_CRYPTO_ECC_P521_BYTE_SIZE] =
    {
        0x50u, 0x66u, 0xd1u, 0x9fu, 0x76u, 0x94u, 0xbeu, 0x88u,
        0x40u, 0xc2u, 0x72u, 0xa2u, 0x86u, 0x70u, 0x3cu, 0x35u,
        0x61u, 0x07u, 0xadu, 0x3fu, 0x01u, 0xb9u, 0x50u, 0xc5u,
        0x40u, 0x26u, 0xf4u, 0x5eu, 0x99u, 0x72u, 0xeeu, 0x97u,
        0x2cu, 0x66u, 0x3eu, 0x27u, 0x17u, 0xbdu, 0xafu, 0x17u,
        0x68u, 0x44u, 0x9bu, 0x57u, 0x49u, 0x44u, 0xf5u, 0x98u,
        0xd9u, 0x1bu, 0x7du, 0x2cu, 0xb4u, 0x5fu, 0x8au, 0x5cu,
        0x04u, 0xc0u, 0x3bu, 0x9au, 0x78u, 0x6au, 0x29u, 0x39u,
        0x18u, 0x01u
    };
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED) */

    static const cy_stc_crypto_ecc_dp_type eccDomainParams[] =
    {
        {
            CY_CRYPTO_ECC_ECP_NONE,
            0u,
            NULL,
            CY_CRYPTO_NIST_P_CURVE_SPECIFIC_RED_ALG,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        }
        #if defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED)
        ,
        {
            CY_CRYPTO_ECC_ECP_SECP192R1,
            CY_CRYPTO_ECC_P192_SIZE,
            "NIST P-192",
            CY_CRYPTO_NIST_P_CURVE_SPECIFIC_RED_ALG,
            /* prime: "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF" */
            eccP192Polynomial,
            /* barrett_p: "1000000000000000000000000000000010000000000000001" */
            eccP192PolyBarrett,
            /* order: "FFFFFFFFFFFFFFFFFFFFFFFF99DEF836146BC9B1B4D22831" */
            eccP192Order,
            /* barrett_o: "1000000000000000000000000662107c9eb94364e4b2dd7cf" */
            eccP192OrderBarrett,
            /* base point x: "188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012" */
            eccP192BasePointX,
            /* base point y: "07192B95FFC8DA78631011ED6B24CDD573F977A11E794811" */
            eccP192BasePointY
        }
        #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED) */
        #if defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED)
        ,
        {
            CY_CRYPTO_ECC_ECP_SECP224R1,
            CY_CRYPTO_ECC_P224_SIZE,
            "NIST P-224",
            CY_CRYPTO_NIST_P_CURVE_SPECIFIC_RED_ALG,
            /* prime: "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001" */
            eccP224Polynomial,
            /* barrett_p: "100000000000000000000000000000000ffffffffffffffffffffffff" */
            eccP224PolyBarrett,
            /* order: "FFFFFFFFFFFFFFFFFFFFFFFFFFFF16A2E0B8F03E13DD29455C5C2A3D" */
            eccP224Order,
            /* barrett_o: "10000000000000000000000000000e95d1f470fc1ec22d6baa3a3d5c3" */
            eccP224OrderBarrett,
            /* Gx - base point x: "B70E0CBD6BB4BF7F321390B94A03C1D356C21122343280D6115C1D21" */
            eccP224BasePointX,
            /* Gy - base point y: "BD376388B5F723FB4C22DFE6CD4375A05A07476444D5819985007E34" */
            eccP224BasePointY
        }
        #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED) */
        #if defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED)
        ,
        {
            CY_CRYPTO_ECC_ECP_SECP256R1,
            CY_CRYPTO_ECC_P256_SIZE,
            "NIST P-256",
            CY_CRYPTO_NIST_P_BARRETT_RED_ALG,
            /* prime: "FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF" */
            eccP256Polynomial,
            /* barrett_p: "100000000fffffffffffffffefffffffefffffffeffffffff0000000000000003" */
            eccP256PolyBarrett,
            /* order: "FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551" */
            eccP256Order,
            /* barrett_o: "100000000fffffffffffffffeffffffff43190552df1a6c21012ffd85eedf9bfe" */
            eccP256OrderBarrett,
            /* Gx - base point x: "6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296" */
            eccP256BasePointX,
            /* Gy - base point y: "4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5" */
            eccP256BasePointY
        }
        #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED) */
        #if defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED)
        ,
        {
            CY_CRYPTO_ECC_ECP_SECP384R1,
            CY_CRYPTO_ECC_P384_SIZE,
            "NIST P-384",
            CY_CRYPTO_NIST_P_BARRETT_RED_ALG,
            /* prime: "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF" */
            eccP384Polynomial,
            /* barrett_p: "1000000000000000000000000000000000000000000000000000000000000000100000000ffffffffffffffff00000001" */
            eccP384PolyBarrett,
            /* order: "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973" */
            eccP384Order,
            /* barrett_o: "1000000000000000000000000000000000000000000000000389cb27e0bc8d220a7e5f24db74f58851313e695333ad68d" */
            eccP384OrderBarrett,
            /* base point x: "AA87CA22BE8B05378EB1C71EF320AD746E1D3B628BA79B9859F741E082542A385502F25DBF55296C3A545E3872760AB7" */
            eccP384BasePointX,
            /* base point y: "3617DE4A96262C6F5D9E98BF9292DC29F8F41DBD289A147CE9DA3113B5F0B8C00A60B1CE1D7E819D7A431D7C90EA0E5F" */
            eccP384BasePointY
        }
        #endif /*defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED) */
        #if defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED)
        ,
        {
            CY_CRYPTO_ECC_ECP_SECP521R1,
            CY_CRYPTO_ECC_P521_SIZE,
            "NIST P-521",
            CY_CRYPTO_NIST_P_CURVE_SPECIFIC_RED_ALG,
            /* prime: "1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" */
            eccP521Polynomial,
            /* barrett_p: "20000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001" */
            eccP521PolyBarrett,
            /* order: "1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409" */
            eccP521Order,
            /* barrett_o: "2000000000000000000000000000000000000000000000000000000000000000005ae79787c40d069948033feb708f65a2fc44a36477663b851449048e16ec79bf7" */
            eccP521OrderBarrett,
            /* base point x: "0C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66" */
            eccP521BasePointX,
            /* base point y: "11839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650" */
            eccP521BasePointY
        }
        #endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED) */
    };

    cy_stc_crypto_ecc_dp_type *tmpResult = NULL;

    if ((curveId > CY_CRYPTO_ECC_ECP_NONE) && (curveId < CY_CRYPTO_ECC_ECP_CURVES_CNT))
    {
        tmpResult = (cy_stc_crypto_ecc_dp_type *)&eccDomainParams[curveId];
    }

    return tmpResult;
}

#endif /* defined (CY_CRYPTO_CFG_ECP_C) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */


/* [] END OF FILE */
