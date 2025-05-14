 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file       drv/ecdsa.h
 * @brief      Header File for ECDSA Driver
 * @version    V1.0
 * @date       9. May 2023
 * @model      ecdsa
 ******************************************************************************/

#ifndef _DRV_ECDSA_H_
#define _DRV_ECDSA_H_

#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
\brief EC curve type
*/
typedef enum {
    CSI_CURVES_SECP256K1 =  0U, /* SECG curve over a 256 bit prime field */
    CSI_CURVES_SECP384R1,       /* NIST/SECG curve over a 384 bit prime field */
    CSI_CURVES_SECP521R1,       /* NIST/SECG curve over a 521 bit prime field */
    CSI_CURVES_BRAINPOOL256R1,  /* RFC 5639 curve over a 256 prime field */
    CSI_CURVES_BRAINPOOL256T1,  /* RFC 5639 curve over a 256 prime field */
    CSI_CURVES_BRAINPOOL512R1,  /* RFC 5639 curve over a 512 prime field */
    CSI_CURVES_BRAINPOOL512T1,  /* RFC 5639 curve over a 512 prime field */
} csi_curve_type_t;

/**
\brief ECDSA Ctrl Block
*/
typedef struct {
    csi_dev_t       dev;
    void            *priv;
} csi_ecdsa_t;

/**
  \brief       Initialize ECDSA interface. Initializes the resources needed for the ECDSA interface
  \param[in]   ecdsa    Handle to operate
  \param[in]   idx    Device id
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_ecdsa_init(csi_ecdsa_t *ecdsa, uint32_t idx);

/**
  \brief       De-initialize ECDSA interface. Stops operation and releases the software resources used by the interface
  \param[in]   ecdsa    Dandle to operate
  \return      None
*/
void csi_ecdsa_uninit(csi_ecdsa_t *ecdsa);

/**
  \brief       Load curve param to engin
  \param[in]   ecdsa      Handle to operate
  \param[in]   type       Pointer to \ref csi_curve_type_t
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_ecdsa_load_curve(csi_ecdsa_t *ecdsa, csi_curve_type_t type);

/**
  \brief       Ecdsa Sign
  \param[in]   ecdsa        Handle to operate
  \param[in]   prikey       Pointer to the private key buf
  \param[in]   prikey_len   The private key length
  \param[in]   dgst         Pointer to the digest buf
  \param[in]   dgst_len     The digest length
  \param[out]  sig          Pointer to the signature buf
  \param[out]  sig_len      The signature length
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_ecdsa_sign(csi_ecdsa_t *ecdsa,  const uint8_t *prikey,  uint32_t prikey_len,
                                const uint8_t *dgst, uint32_t dgst_len, uint8_t *sig, uint32_t *sig_len);

/**
  \brief       Ecdsa Verify
  \param[in]   ecdsa        Handle to operate
  \param[in]   pubkey       Pointer to the public key buf
  \param[in]   prikey_len   The public key length
  \param[in]   dgst         Pointer to the digest buf
  \param[in]   dgst_len     The digest length
  \param[in]   sig          Pointer to the signature buf
  \param[in]   sig_len      The signature length
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_ecdsa_verify(csi_ecdsa_t *ecdsa, const uint8_t *pubkey, uint32_t pubkey_len,
                                const uint8_t *dgst, uint32_t gst_len,  const uint8_t *sig,  uint32_t sig_len);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_ECDSA_H_ */
