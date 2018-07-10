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
 * @file     drv_rsa.h
 * @brief    header file for rsa driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CSI_RSA_H_
#define _CSI_RSA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <drv_common.h>


/// definition for rsa handle.
typedef void *rsa_handle_t;

/****** RSA specific error codes *****/
typedef enum {
    RSA_ERROR_DATA_BITS                     ,     ///< Specified number of Data bits not supported
    RSA_ERROR_ENDIAN                              ///< Specified endian not supported
} drv_rsa_error_e;

/*----- RSA Control Codes: Mode Parameters: Data Bits -----*/
typedef enum {
    RSA_DATA_BITS_192             = 0,  ///< 192 Data bits
    RSA_DATA_BITS_256                ,  ///< 256 Data bits
    RSA_DATA_BITS_512                ,  ///< 512 Data bits
    RSA_DATA_BITS_1024               ,  ///< 1024 Data bits (default)
    RSA_DATA_BITS_2048                  ///< 2048 Data bits
} rsa_data_bits_e;

/*----- RSA Control Codes: Mode Parameters: Endian -----*/
typedef enum {
    RSA_ENDIAN_MODE_LITTLE        = 0,  ///< RSA Little Endian Mode
    RSA_ENDIAN_MODE_BIG                 ///< RSA Big Endian Mode
} rsa_endian_mode_e;

typedef enum {
    RSA_PADDING_MODE_PKCS1        = 1, ///< RSA PKCS1 Padding Mode
    RSA_PADDING_MODE_NO              , ///< RSA NO Padding Mode
    RSA_PADDING_MODE_SSLV23          , ///< RSA SSLV23 Padding Mode
    RSA_PADDING_MODE_PKCS1_OAEP      , ///< RSA PKCS1 OAEP Padding Mode
    RSA_PADDING_MODE_X931            , ///< RSA X931 Padding Mode
    RSA_PADDING_MODE_PSS               ///< RSA PSS Padding Mode
} rsa_padding_type_e;

typedef enum {
    RSA_HASH_TYPE_MD5            = 0,
    RSA_HASH_TYPE_SHA1               ,
    RSA_HASH_TYPE_SHA224             ,
    RSA_HASH_TYPE_SHA256             ,
    RSA_HASH_TYPE_SHA384             ,
    RSA_HASH_TYPE_SHA512
} rsa_hash_type_e;

/*----- RSA Control Codes: Mode Parameters: Padding mode -----*/
typedef struct {
    rsa_padding_type_e padding_type;
    rsa_hash_type_e    hash_type;
} rsa_padding_t;

/**
\brief RSA Status
*/
typedef struct {
    uint32_t busy             : 1;        ///< Calculate busy flag
} rsa_status_t;

/****** RSA Event *****/
typedef enum {
    RSA_EVENT_ENCRYPT_COMPLETE    = 0,   ///< Encrypt completed
    RSA_EVENT_DECRYPT_COMPLETE       ,   ///< Decrypt completed
    RSA_EVENT_SIGN_COMPLETE          ,   ///< Sign completed
    RSA_EVENT_VERIFY_COMPLETE        ,   ///< Verify completed
} rsa_event_e;

typedef void (*rsa_event_cb_t)(rsa_event_e event);   ///< Pointer to \ref rsa_event_cb_t : RSA Event call back.


/**
\brief RSA Device Driver Capabilities.
*/
typedef struct {
    uint32_t bits_192            : 1;      ///< supports 192bits modular length
    uint32_t bits_256            : 1;      ///< supports 256bits modular length
    uint32_t bits_512            : 1;      ///< supports 512bits modular length
    uint32_t bits_1024           : 1;      ///< supports 1024bits modular length
    uint32_t bits_2048           : 1;      ///< supports 2048bits modular length
} rsa_capabilities_t;


// Function documentation

/**
  \brief       get rsa handle count.
  \return      rsa handle count
*/
int32_t csi_rsa_get_instance_count(void);

/**
  \brief       Initialize RSA Interface. 1. Initializes the resources needed for the RSA interface 2.registers event callback function
  \param[in]   idx  must not exceed return value of csi_rsa_get_instance_count()
  \param[in]   cb_event  Pointer to \ref rsa_event_cb_t
  \return      pointer to rsa handle
*/
rsa_handle_t csi_rsa_initialize(int32_t idx, rsa_event_cb_t cb_event);

/**
  \brief       De-initialize RSA Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  rsa handle to operate.
  \return      error code
*/
int32_t csi_rsa_uninitialize(rsa_handle_t handle);

/**
  \brief       Get driver capabilities.
  \param[in]   handle rsa handle to operate.
  \return      \ref rsa_capabilities_t
*/
rsa_capabilities_t csi_rsa_get_capabilities(rsa_handle_t handle);

/**
  \brief       config rsa mode.
  \param[in]   handle  rsa handle to operate.
  \param[in]   data_bits \ref rsa_data_bits_e
  \param[in]   endian    \ref rsa_endian_mode_e
  \return      error code
*/
int32_t csi_rsa_config(rsa_handle_t handle,
                       rsa_data_bits_e data_bits,
                       rsa_endian_mode_e endian
                      );

/**
  \brief       encrypt
  \param[in]   handle  rsa handle to operate.
  \param[in]   n         Pointer to the public modulus
  \param[in]   e         Pointer to the public exponent
  \param[in]   src       Pointer to the source data.
  \param[in]   src_size  the source data len
  \param[out]  out       Pointer to the result buffer
  \param[out]  out_size  the result size
  \param[in]   padding   \ref  rsa_padding_t
  \return      error code
*/
int32_t csi_rsa_encrypt(rsa_handle_t handle, void *n, void *e, void *src, int32_t src_size, void *out, uint32_t *out_size, rsa_padding_t padding);


/**
  \brief       decrypt
  \param[in]   handle  rsa handle to operate.
  \param[in]   n         Pointer to the public modulus
  \param[in]   d         Pointer to the privte exponent
  \param[in]   src       Pointer to the source data.
  \param[in]   src_size  the source data len
  \param[out]  out       Pointer to the result buffer
  \param[out]  out_size  the result size
  \param[in]   padding   \ref rsa_padding_t
  \return      error code
*/
int32_t csi_rsa_decrypt(rsa_handle_t handle, void *n, void *d, void *src, uint32_t src_size, void *out, uint32_t *out_size, rsa_padding_t padding);

/**
  \brief       rsa sign
  \param[in]   handle  rsa handle to operate.
  \param[in]   n         Pointer to the public modulus
  \param[in]   d         Pointer to the privte exponent
  \param[in]   src       Pointer to the source data.
  \param[in]   src_size  the source data len
  \param[out]  signature Pointer to the signature
  \param[out]  sig_size  the signature size
  \param[in]   padding   \ref rsa_padding_t
  \return      error code
*/
int32_t csi_rsa_sign(rsa_handle_t handle, void *n, void *d, void *src, uint32_t src_size, void *signature, void *sig_size, rsa_padding_t padding);

/**
  \brief       rsa verify
  \param[in]   handle  rsa handle to operate.
  \param[in]   n         Pointer to the public modulus
  \param[in]   e         Pointer to the public exponent
  \param[in]   src       Pointer to the source data.
  \param[in]   src_size  the source data len
  \param[in]   signature Pointer to the signature
  \param[in]   sig_size  the signature size
  \param[out]  result    Pointer to the result
  \param[in]   padding   \ref rsa_padding_t
  \return      error code
*/
int32_t csi_rsa_verify(rsa_handle_t handle, void *n, void *e, void *src, uint32_t src_size, void *signature, uint32_t sig_size, void *result, rsa_padding_t padding);
/**
  \brief       Get RSA status.
  \param[in]   handle  rsa handle to operate.
  \return      RSA status \ref rsa_status_t
*/
rsa_status_t csi_rsa_get_status(rsa_handle_t handle);


#ifdef __cplusplus
}
#endif

#endif /* _CSI_RSA_H_ */
