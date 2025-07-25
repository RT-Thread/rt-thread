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
 * @file       drv/des.h
 * @brief      Header File for DES Driver
 * @version    V1.0
 * @date       24. Oct 2022
 * @model      des
 ******************************************************************************/

#ifndef _DRV_DES_H_
#define _DRV_DES_H_

#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
\brief DES key-len-bits type
*/
typedef enum {
    DES_KEY_LEN_BITS_64        = 0,        /*64 Data bits*/
    DES_KEY_LEN_BITS_128,                  /*128 Data bits*/
    DES_KEY_LEN_BITS_192,                  /*192 Data bits*/
} csi_des_key_bits_t;

/**
\brief DES Ctrl Block
*/
typedef struct {
    csi_dev_t               dev;
    void                    *priv;
} csi_des_t;

/**
  \brief       Initialize DES interface. Initializes the resources needed for the DES interface
  \param[in]   des    Handle to operate
  \param[in]   idx    Device id
  \return      Error code \ref csi_error_t
*/
csi_error_t csi_des_init(csi_des_t *des, uint32_t idx);

/**
  \brief       De-initialize DES interface. Stops operation and releases the software resources used by the interface
  \param[in]   des    Dandle to operate
  \return      None
*/
void csi_des_uninit(csi_des_t *des);

/**
  \brief       Set encrypt key
  \param[in]   des        Handle to operate
  \param[in]   key        Pointer to the key buf
  \param[in]   key_len    Pointer to \ref csi_des_key_bits_t
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_des_set_encrypt_key(csi_des_t *des, void *key, csi_des_key_bits_t key_len);

/**
  \brief       Set decrypt key
  \param[in]   des        Handle to operate
  \param[in]   key        Pointer to the key buf
  \param[in]   key_len    Pointer to \ref csi_des_key_bits_t
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_des_set_decrypt_key(csi_des_t *des, void *key, csi_des_key_bits_t key_len);

/**
  \brief       DES ecb encrypt
  \param[in]   des     Handle to operate
  \param[in]   in      Pointer to the source data
  \param[out]  out     Pointer to the result data
  \param[in]   size    The source data size
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_des_ecb_encrypt(csi_des_t *des, void *in, void *out, uint32_t size);

/**
  \brief       DES ecb decrypt
  \param[in]   des     Handle to operate
  \param[in]   in      Pointer to the source data
  \param[out]  out     Pointer to the result data
  \param[in]   size    The source data size
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_des_ecb_decrypt(csi_des_t *des, void *in, void *out, uint32_t size);

/**
  \brief       DES cbc encrypt
  \param[in]   des     Handle to operate
  \param[in]   in      Pointer to the source data
  \param[out]  out     Pointer to the result data
  \param[in]   size    The source data size
  \param[in]   iv      Init vector
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_des_cbc_encrypt(csi_des_t *des, void *in, void *out, uint32_t size, void *iv) ;

/**
  \brief       DES cbc decrypt
  \param[in]   des     Handle to operate
  \param[in]   in      Pointer to the source data
  \param[out]  out     Pointer to the result data
  \param[in]   size    The source data size
  \param[in]   iv      Init vector
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_des_cbc_decrypt(csi_des_t *des, void *in, void *out, uint32_t size, void *iv);

/**
  \brief       TDES ecb encrypt
  \param[in]   des     Handle to operate
  \param[in]   in      Pointer to the source data
  \param[out]  out     Pointer to the result data
  \param[in]   size    The source data size
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_tdes_ecb_encrypt(csi_des_t *des, void *in, void *out, uint32_t size);

/**
  \brief       TDES ecb decrypt
  \param[in]   des     Handle to operate
  \param[in]   in      Pointer to the source data
  \param[out]  out     Pointer to the result data
  \param[in]   size    The source data size
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_tdes_ecb_decrypt(csi_des_t *des, void *in, void *out, uint32_t size);

/**
  \brief       TDES cbc encrypt
  \param[in]   des     Handle to operate
  \param[in]   in      Pointer to the source data
  \param[out]  out     Pointer to the result data
  \param[in]   size    The source data size
  \param[in]   iv      Init vector
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_tdes_cbc_encrypt(csi_des_t *des, void *in, void *out, uint32_t size, void *iv) ;

/**
  \brief       TDES cbc decrypt
  \param[in]   des     Handle to operate
  \param[in]   in      Pointer to the source data
  \param[out]  out     Pointer to the result data
  \param[in]   size    The source data size
  \param[in]   iv      Init vector
  \return      Error code \ref Csi_error_t
*/
csi_error_t csi_tdes_cbc_decrypt(csi_des_t *des, void *in, void *out, uint32_t size, void *iv);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_DES_H_ */
