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
 * @file       drv/ecdh.h
 * @brief      Header File for ECDH Driver
 * @version    V1.0
 * @date       9. May 2023
 * @model      ecdh
 ******************************************************************************/

#ifndef _DRV_ECDH_H_
#define _DRV_ECDH_H_

#include <drv/common.h>
#include <drv/ecdsa.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
\brief ECDH Ctrl Block
*/
typedef struct {
    csi_dev_t       dev;
    void            *priv;
} csi_ecdh_t;

/**
  \brief       Initialize ECDH interface. Initializes the resources needed for the ECDH interface
  \param[in]   ecdh    Handle to operate
  \param[in]   idx    Device id
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_ecdh_init(csi_ecdh_t *ecdh, uint32_t idx);

/**
  \brief       De-initialize ECDH interface. Stops operation and releases the software resources used by the interface
  \param[in]   ecdh    Dandle to operate
  \return      None
*/
void csi_ecdh_uninit(csi_ecdh_t *ecdh);

/**
  \brief       Load curve param to engin
  \param[in]   ecdh      Handle to operate
  \param[in]   type       Pointer to \ref csi_curve_type_t
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_ecdh_load_curve(csi_ecdh_t *ecdh, csi_curve_type_t type);

/**
  \brief       ECDH generate key pair
  \param[in]   ecdh        Handle to operate
  \param[out]  prikey      Pointer to the private key buf
  \param[out]  pubkey      Pointer to the public key buf
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_ecdh_gen_keypair(csi_ecdh_t *ecdh, uint8_t *prikey, uint8_t *pubkey);

/**
  \brief       ECDH generate secret key
  \param[in]   ecdh        Handle to operate
  \param[in]   prikey      Pointer to the private key buf
  \param[in]   pubkey      Pointer to the public key buf
  \param[out]  sk          Pointer to the secret key buf
  \param[out]  sk_len      The secret key length
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_ecdh_calc_secret(csi_ecdh_t *ecdh, const uint8_t *privkey, const uint8_t *pubkey, uint8_t *sk, uint32_t *sk_len);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_ECDH_H_ */
