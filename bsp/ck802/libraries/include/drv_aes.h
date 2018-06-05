/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv_aes.h
 * @brief    Header File for AES Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CSI_AES_H_
#define _CSI_AES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drv_common.h>
#include <drv_errno.h>


/// definition for aes handle.
typedef void *aes_handle_t;

/****** AES specific error codes *****/
typedef enum {
    AES_ERROR_MODE  = (EDRV_SPECIFIC + 1)   ,     ///< Specified Mode not supported
    AES_ERROR_DATA_BITS                     ,     ///< Specified number of Data bits not supported
    AES_ERROR_ENDIAN                              ///< Specified endian not supported
} drv_aes_error_e;

/*----- AES Control Codes: Mode -----*/
typedef enum {
    AES_MODE_ECB                  = 0,   ///< ECB Mode
    AES_MODE_CBC                     ,   ///< CBC Mode
    AES_MODE_CFB                     ,   ///< CFB Mode
    AES_MODE_OFB                     ,   ///< OFB Mode
    AES_MODE_CTR                         ///< CTR Mode
} aes_mode_e;

/*----- AES Control Codes: Crypto Mode -----*/
typedef enum {
    AES_CRYPTO_MODE_ENCRYPT                  = 0,   ///< encrypt Mode
    AES_CRYPTO_MODE_DECRYPT                     ,   ///< decrypt Mode
} aes_crypto_mode_e;

/*----- AES Control Codes: Padding Mode -----*/
typedef enum {
    AES_PADDING_MODE_NO     = 0,        ///< NO-PADDING
    AES_PADDING_MODE_ZERO      ,        ///< ZERO-PADDING
    AES_PADDING_MODE_PKCS5              ///< PKCS5-PADDING
} aes_padding_mode_e;

/*----- AES Control Codes: Mode Parameters: Key length -----*/
typedef enum {
    AES_KEY_LEN_BITS_128        = 0,      ///< 128 Data bits
    AES_KEY_LEN_BITS_192           ,      ///< 192 Data bits
    AES_KEY_LEN_BITS_256                  ///< 256 Data bits
} aes_key_len_bits_e;

/*----- AES Control Codes: Mode Parameters: Endian -----*/
typedef enum {
    AES_ENDIAN_LITTLE          = 0,       ///< Little Endian
    AES_ENDIAN_BIG                        ///< Big Endian
} aes_endian_mode_e;

/**
\brief AES Status
*/
typedef struct {
    uint32_t busy             : 1;        ///< busy flag
} aes_status_t;

/****** AES Event *****/
typedef enum {
    AES_EVENT_CRYPTO_COMPLETE    = 0   ///< Encrypt completed
} aes_event_e;
typedef void (*aes_event_cb_t)(aes_event_e event);   ///< Pointer to \ref aes_event_cb_t : AES Event call back.


/**
\brief AES Device Driver Capabilities.
*/
typedef struct {
    uint32_t ecb_mode           : 1;      ///< supports ECB mode
    uint32_t cbc_mode           : 1;      ///< supports CBC mode
    uint32_t cfb_mode           : 1;      ///< supports CFB mode
    uint32_t ofb_mode           : 1;      ///< supports OFB mode
    uint32_t ctr_mode           : 1;      ///< supports CTR mode
    uint32_t bits_128           : 1;      ///< supports 128bits key length
    uint32_t bits_192           : 1;      ///< supports 192bits key length
    uint32_t bits_256           : 1;      ///< supports 256bits key length
} aes_capabilities_t;


// Function documentation

/**
  \brief       get aes instance count.
  \return      aes handle count
*/
int32_t csi_aes_get_instance_count(void);

/**
  \brief       Initialize AES Interface. 1. Initializes the resources needed for the AES interface 2.registers event callback function
  \param[in]   idx must not exceed return value of csi_aes_get_instance_count().
  \param[in]   cb_event  Pointer to \ref aes_event_cb_t
  \return      return aes handle if success
*/
aes_handle_t csi_aes_initialize(int32_t idx, aes_event_cb_t cb_event);

/**
  \brief       De-initialize AES Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  aes handle to operate.
  \return      error code
*/
int32_t csi_aes_uninitialize(aes_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle  aes handle to operate.
  \return      \ref aes_capabilities_t
*/
aes_capabilities_t csi_aes_get_capabilities(aes_handle_t handle);

/**
  \brief       config aes mode.
  \param[in]   handle  aes handle to operate.
  \param[in]   mode      \ref aes_mode_e
  \param[in]   keylen_bits \ref aes_key_len_bits_e
  \param[in]   endian    \ref aes_endian_mode_e
  \param[in]   arg       Pointer to the iv address when mode is cbc_mode
  \return      error code
*/
int32_t csi_aes_config(aes_handle_t handle,
                       aes_mode_e mode,
                       aes_key_len_bits_e keylen_bits,
                       aes_endian_mode_e endian,
                       uint32_t arg
                      );

/**
  \brief       set crypto key.
  \param[in]   handle    aes handle to operate.
  \param[in]   context   aes information context(NULL when hardware implementation)
  \param[in]   key       Pointer to the key buf
  \param[in]   key_len    the key len
  \param[in]   enc       \ref aes_crypto_mode_e
  \return      error code
*/
int32_t csi_aes_set_key(aes_handle_t handle, void *context, void *key, uint32_t key_len, aes_crypto_mode_e enc);

/**
  \brief       encrypt or decrypt
  \param[in]   handle  aes handle to operate.
  \param[in]   context aes information context(NULL when hardware implementation)
  \param[in]   in   Pointer to the Source data
  \param[out]  out  Pointer to the Result data.
  \param[in]   len  the Source data len.
  \param[in]   padding \ref aes_padding_mode_e.
  \return      error code
*/
int32_t csi_aes_crypto(aes_handle_t handle, void *context, void *in, void *out, uint32_t len, aes_padding_mode_e padding);

/**
  \brief       Get AES status.
  \param[in]   handle  aes handle to operate.
  \return      AES status \ref aes_status_t
*/
aes_status_t csi_aes_get_status(aes_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* _CSI_AES_H_ */
