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
 * @file     drv/tee.h
 * @brief    Header File for TEE Driver
 * @version  V1.0
 * @date     12 Sep 2020
 * @model    tee
 ******************************************************************************/
#ifndef _DRV_TEE_H_
#define _DRV_TEE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/****** TEE AES mode *****/
typedef enum {
    TEE_AES_MODE_ECB = 0,    ///< TEE AES ECB mode
    TEE_AES_MODE_CBC = 1,    ///< TEE AES CBC mode
    TEE_AES_MODE_MAX,        ///< invaild mode
}
tee_aes_mode_e;

/**
  \brief       TEE AES encrypt
  \note        Length should be a multiple of the block size (16 bytes)
               After calling this function, the content of iv is updated.
  \param[in]   in      Pointer to plaintext buffer
  \param[in]   in_len  Plaintext buffer length
  \param[in]   key     Pointer to secret key
  \param[in]   key_len Secret key size,must be 16 bytes for AES128,24 bytes for AES192 or 32byes for AES256
  \param[out]  out     Pointer to ciphertext buffer
  \param[in]   mode    \ref tee_aes_mode_e
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_aes_encrypt(const uint8_t *in, uint32_t in_len,
                            const uint8_t *key, uint32_t key_len,
                            uint8_t iv[16],
                            uint8_t *out,
                            tee_aes_mode_e mode);

/**
  \brief       TEE AES decrypt
  \note        Length should be a multiple of the block size (16 bytes)
               After calling this function, the content of iv is updated.
  \param[in]   in      Pointer to ciphertext buffer
  \param[in]   in_len  Ciphertext buffer length
  \param[in]   key     Pointer to secret key
  \param[in]   key_len Secret key size,must be 16 bytes for AES128,24 bytes for AES192 or 32byes for AES256
  \param[out]  out     Pointer to plaintext buffer
  \param[in]   mode    \ref tee_aes_mode_e
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_aes_decrypt(const uint8_t *in, uint32_t in_len,
                            const uint8_t *key, uint32_t key_len,
                            uint8_t iv[16],
                            uint8_t *out,
                            uint32_t mode);

/**
  \brief       TEE AES ECB encrypt
  \note        Length should be a multiple of the block size (16 bytes)
               After calling this function, the content of iv is updated.
  \param[in]   in      Pointer to plaintext buffer
  \param[in]   in_len  Plaintext buffer length
  \param[in]   key     Pointer to secret key
  \param[in]   key_len Secret key size,must be 16 bytes for AES128,24 bytes for AES192 or 32byes for AES256
  \param[out]  out     Pointer to ciphertext buffer
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_aes_encrypt_ecb(in, in_len, key, key_len, out) \
    csi_tee_aes_encrypt(in, in_len, key, key_len, NULL, out, TEE_AES_MODE_ECB)

/**
  \brief       TEE AES ECB decrypt
  \note        Length should be a multiple of the block size (16 bytes)
               After calling this function, the content of iv is updated.
  \param[in]   in      Pointer to ciphertext buffer
  \param[in]   in_len  Ciphertext buffer length
  \param[in]   key     Pointer to secret key
  \param[in]   key_len Secret key size,must be 16 bytes for AES128,24 bytes for AES192 or 32byes for AES256
  \param[out]  out     Pointer to plaintext buffer
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_aes_decrypt_ecb(in, in_len, key, key_len, out) \
    csi_tee_aes_decrypt(in, in_len, key, key_len, NULL, out, TEE_AES_MODE_ECB)

/**
  \brief       TEE AES CBC encrypt
  \note        Length should be a multiple of the block size (16 bytes)
               After calling this function, the content of iv is updated.
  \param[in]   in      Pointer to ciphertext buffer
  \param[in]   in_len  Ciphertext buffer length
  \param[in]   key     Pointer to secret key
  \param[in]   key_len Secret key size,must be 16 bytes for AES128,24 bytes for AES192 or 32byes for AES256
  \param[out]  out     Pointer to plaintext buffer
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_aes_encrypt_cbc(in, in_len, key, key_len, iv, out) \
    csi_tee_aes_encrypt(in, in_len, key, key_len, iv, out, TEE_AES_MODE_CBC)

/**
  \brief       TEE AES CBC decrypt
  \note        Length should be a multiple of the block size (16 bytes)
               After calling this function, the content of iv is updated.
  \param[in]   in      Pointer to ciphertext buffer
  \param[in]   in_len  Ciphertext buffer length
  \param[in]   key     Pointer to secret key
  \param[in]   key_len Secret key size,must be 16 bytes for AES128,24 bytes for AES192 or 32byes for AES256
  \param[out]  out     Pointer to plaintext buffer
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_aes_decrypt_cbc(in, in_len, key, key_len, iv, out) \
    csi_tee_aes_decrypt(in, in_len, key, key_len, iv, out, TEE_AES_MODE_CBC)

/**
  \brief       TEE BASE64 encode/decode
  \param[in]   in        Pointer to input data buffer
  \param[in]   in_len    Input data buffer length
  \param[out]  out       Pointer to output data buffer
  \param[out]  out_len   Output data buffer length
  \param[in]   is_encode 1 encode 0 decode
  \param[in]   wsafe     Base64 websafe feature,set 1, replace "+/" with "-_"
  \return      Return 0 if successful,otherwise error code
*/
int32_t csi_tee_base64(const uint8_t *in, uint32_t in_len,
                       uint8_t *out, uint32_t *out_len,
                       uint32_t is_encode,
                       uint32_t wsafe);

/**
  \brief       TEE BASE64 encode
  \param[in]   in        Pointer to input data buffer
  \param[in]   in_len    Input data buffer length
  \param[out]  out       Pointer to output data buffer
  \param[out]  out_len   Output data buffer length
  \return      Return 0 if successful,otherwise error code
*/
#define csi_tee_base64_encode(in,in_len,out,out_len) \
    csi_tee_base64(in,in_len,out,out_len,1,0)

/**
  \brief       TEE BASE64 decode
  \param[in]   in        Pointer to input data buffer
  \param[in]   in_len    Input data buffer length
  \param[out]  out       Pointer to output data buffer
  \param[out]  out_len   Output data buffer length
  \return      Return 0 if successful,otherwise error code
*/
#define csi_tee_base64_decode(in,in_len,out,out_len) \
    csi_tee_base64(in,in_len,out,out_len,0,0)

/**
  \brief       TEE BASE64 web safe encode
  \param[in]   in        Pointer to input data buffer
  \param[in]   in_len    Input data buffer length
  \param[out]  out       Pointer to output data buffer
  \param[out]  out_len   Output data buffer length
  \return      Return 0 if successful,otherwise error code
*/
#define csi_tee_base64_websafe_encode(in,in_len,out,out_len) \
    csi_tee_base64(in,in_len,out,out_len,1,1)

/**
  \brief       TEE BASE64 web safe decode
  \param[in]   in        Pointer to input data buffer
  \param[in]   in_len    Input data buffer length
  \param[out]  out       Pointer to output data buffer
  \param[out]  out_len   Output data buffer length
  \return      Return 0 if successful,otherwise error code
*/
#define csi_tee_base64_websafe_decode(in,in_len,out,out_len) \
    csi_tee_base64(in,in_len,out,out_len,0,1)

/**
  \brief       TEE obtain CID from Key Provisioning
  \param[out]  out       Pointer to cid buffer
  \param[out]  out_len   CID buffer length,if cid obtain successfully,
                         out_len is updated to actual cid sizes
  \return      Return 0 if successful,otherwise error code
*/
int32_t csi_tee_get_cid(uint8_t *out, uint32_t *out_len);

/****** lpm mode *****/
typedef enum {
    TEE_LPM_MODE_WAIT = 0,   ///< lpm wait
    TEE_LPM_MODE_DOZE = 1,   ///< lpm doze
    TEE_LPM_MODE_STOP = 2,   ///< lpm stop
    TEE_LPM_MODE_STANDBY = 3, ///< lpm standby
    TEE_LPM_MODE_CLOCK = 4,  ///< lpm clock gate
    TEE_LPM_MODE_MAX,
} tee_lpm_mode_e;

/**
  \brief       TEE set low power mode
  \param[in]   gate  Not use for now
  \param[in]   irqid Not use for now
  \param[in]   mode  \ref tee_lpm_mode_e
  \return      Return 0 if successful,otherwise error code
*/
int32_t csi_tee_enter_lpm(uint32_t gate, uint32_t irqid, tee_lpm_mode_e mode);

/**
  \brief       TEE obtain manifest info from manifest table
  \note        call csi_tee_get_sys_img_info, csi_tee_get_sys_os_version or csi_tee_get_sys_partition is better
  \param[out]  out     Pointer to info buffer
  \param[out]  out_len Info buffer length,if info obtain successfully,
                       out_len is updated to actual sizes
  \param[in]   name    info name
  \return      Return 0 if successful,otherwise error code
*/
int32_t csi_tee_get_manifest_info(uint8_t *out, uint32_t *out_len, char *name);

/**
  \brief       TEE obtain image buffer from manifest table
  \param[out]  out      Pointer to image buffer
  \param[out]  out_len  Image buffer length,if info obtain successfully,
                        out_len is updated to actual image buffer sizes
  \param[in]   img_name Image name
  \return      Return 0 if successful,otherwise error code
*/
#define csi_tee_get_sys_img_info(out,out_len,img_name) \
    csi_tee_get_manifest_info(out,out_len,img_name)

/**
  \brief       TEE obtain os version from manifest table
  \param[out]  out     Pointer to os version buffer
  \param[out]  out_len OS version buffer length,if info obtain successfully,
                       out_len is updated to actual os version buffer sizes
  \return      Return 0 if successful,otherwise error code
*/
#define csi_tee_get_sys_os_version(out,out_len) \
    csi_tee_get_manifest_info(out,out_len,"os_v")

/**
  \brief       TEE obtain partition buffer from manifest table
  \param[out]  out     Pointer to partition buffer
  \param[out]  out_len Partition buffer length,if info obtain successfully,
                       out_len is updated to actual partition buffer sizes
  \return      Return 0 if successful,otherwise error code
*/
#define csi_tee_get_sys_partition(out,out_len) \
    csi_tee_get_manifest_info(out,out_len,"sys_p")

/**
  \brief       TEE set random seed
  \param[in]   Seed random sedd
  \return      Return 0 if successful,otherwise error code
*/
int32_t csi_tee_rand_seed(uint32_t seed);

/**
  \brief       TEE ramdom date generation
  \param[out]  out     Pointer to random data buffer
  \param[in]   out_len Data buffer length
  \return      Return 0 if successful,otherwise error code
*/
int32_t csi_tee_rand_generate(uint8_t *out, uint32_t out_len);

/****** TEE RSA sign type *****/
typedef enum {
    TEE_RSA_MD5    = 0,     ///< MD5
    TEE_RSA_SHA1   = 1,     ///< SHA1
    TEE_RSA_SHA256 = 3,     ///< SHA256
    TEE_RSA_SIGN_TYPE_MAX,  ///< invailed type
} tee_rsa_sign_type_e;

/**
  \brief       TEE RSA sign with private key
  \param[in]   in       Pointer to digest buffer
  \param[in]   in_len   Digest buffer length
  \param[in]   key      Pointer to private key,key contains n, e, d
  \param[in]   key_len  Private key size,must be 128*3 = 384 bytes for RSA1024, 256*3 = 768 bytes for RSA2048
  \param[out]  sign     Pointer to sign buffer
  \param[out]  sign_len Sign buffer length
  \param[in]   type     \ref tee_rsa_sign_type_e
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_rsa_sign(const uint8_t *in, uint32_t in_len,
                         const uint8_t *key, uint32_t key_len,
                         uint8_t *sign, uint32_t *sign_len,
                         tee_rsa_sign_type_e type);

/**
  \brief       TEE RSA verify with public key
  \param[in]   in       Pointer to digest buffer
  \param[in]   in_len   Digest buffer length
  \param[in]   key      Pointer to public key,key contains n, e
  \param[in]   key_len  Public key size,must be 128*2 = 256 bytes for RSA1024, 256*2 = 512 bytes for RSA2048
  \param[in]   sign     Pointer to sign buffer
  \param[in]   sign_len Sign buffer length
  \param[in]   type     \ref tee_rsa_sign_type_e
  \return      Return  0 if verify successful,otherwise error code
*/
int32_t csi_tee_rsa_verify(const uint8_t *in, uint32_t in_len,
                           const uint8_t *key, uint32_t key_len,
                           uint8_t *sign, uint32_t sign_len,
                           tee_rsa_sign_type_e type);

/****** TEE RSA padding mode *****/
typedef enum {
    TEE_RSA_PKCS1_PADDING = 0x01,     ///< RSA PKCS padding mode
    TEE_RSA_NO_PADDING    = 0x02,     ///< RSA no padding mode
} tee_rsa_padding_mode_e;

/**
  \brief       TEE RSA encrypt with public key
  \param[in]   in       Pointer to plaintext buffer
  \param[in]   in_len   Plaintext buffer length
  \param[in]   key      Pointer to public key,key contains n, e
  \param[in]   key_len  Public key size, must be 128*2 = 256 bytes for RSA1024, 256*2 = 512 bytes for RSA2048
  \param[in]   out      Pointer to ciphertext buffer
  \param[in]   out_len  Ciphertext buffer length
  \param[in]   padding  \ref tee_rsa_padding_mode_e
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_rsa_encrypt(const uint8_t *in, uint32_t in_len,
                            const uint8_t *key, uint32_t key_len,
                            uint8_t *out, uint32_t *out_len,
                            tee_rsa_padding_mode_e padding);
/**
  \brief       TEE RSA decrypt with private key
  \param[in]   in       Pointer to ciphertext buffer
  \param[in]   in_len   Ciphertext buffer length
  \param[in]   key      Pointer to private key,key contains n, e, d
  \param[in]   key_len  Private key size,must be 128*3 = 384 bytes for RSA1024, 256*3 = 768 bytes for RSA2048
  \param[in]   out      Pointer to plaintext buffer
  \param[in]   out_len  Plaintext buffer length
  \param[in]   padding  \ref tee_rsa_padding_mode_e
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_rsa_decrypt(const uint8_t *in, uint32_t in_len,
                            const uint8_t *key, uint32_t key_len,
                            uint8_t *out, uint32_t *out_len,
                            tee_rsa_padding_mode_e padding);

/**
  \brief       TEE RSA sign with internal private key
  \note        Only use if key provisioning exist
  \param[in]   in       Pointer to digest buffer
  \param[in]   in_len   Digest buffer length
  \param[out]  sign     Pointer to sign buffer
  \param[out]  sign_len Sign buffer length
  \param[in]   type     \ref tee_rsa_sign_type_e
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_cid_rsa_sign(in,in_len,sign,sign_len,type) \
    csi_tee_rsa_sign(in,in_len,NULL,0,sign,sign_len,type)

/**
  \brief       TEE RSA verify with internal public key
  \note        Only use if key provisioning exist
  \param[in]   in       Pointer to digest buffer
  \param[in]   in_len   Digest buffer length
  \param[in]   sign     Pointer to sign buffer
  \param[in]   sign_len Sign buffer length
  \param[in]   type     \ref tee_rsa_sign_type_e
  \return      Return  0 if verify successful,otherwise error code
*/
#define csi_tee_cid_rsa_verify(in,in_len,sign,sign_len,type) \
    csi_tee_rsa_verify(in,in_len,NULL,0,sign,sign_len,type)

/**
  \brief       TEE RSA encrypt with internal public key
  \note        Only use if key provisioning exist
  \param[in]   in       Pointer to plaintext buffer
  \param[in]   in_len   Plaintext buffer length
  \param[in]   out      Pointer to ciphertext buffer
  \param[in]   out_len  Ciphertext buffer length
  \param[in]   padding  \ref tee_rsa_padding_mode_e
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_cid_rsa_encrypt(in,in_len,out,out_len,padding) \
    csi_tee_rsa_encrypt(in,in_len,NULL,0,out,out_len,padding)

/**
  \brief       TEE RSA decrypt with internal private key
  \note        Only use if key provisioning exist
  \param[in]   in       Pointer to ciphertext buffer
  \param[in]   in_len   Ciphertext buffer length
  \param[in]   key      Pointer to private key,key contains n, e, d
  \param[in]   key_len  Private key size,must be 128*3 = 384 bytes for RSA1024, 256*3 = 768 bytes for RSA2048
  \param[in]   out      Pointer to plaintext buffer
  \param[in]   out_len  Plaintext buffer length
  \param[in]   padding  \ref tee_rsa_padding_mode_e
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_cid_rsa_decrypt(in,in_len,out,out_len,padding) \
    csi_tee_rsa_decrypt(in,in_len,NULL,0,out,out_len,padding)

/**
  \brief       verify boot image with boot public key
  \note        Only use if key provisioning exist
  \param[in]   in       Pointer to digest buffer
  \param[in]   in_len   Digest buffer length
  \param[in]   sign     Pointer to sign buffer
  \param[in]   sign_len Sign buffer length
  \param[in]   type     \ref tee_rsa_sign_type_e
  \return      Return  0 if verify successful,otherwise error code
*/
int32_t csi_tee_img_rsa_verify(const uint8_t *in, uint32_t in_len,
                               uint8_t *sign, uint32_t sign_len,
                               tee_rsa_sign_type_e type);

/****** TEE HASH operation mode *****/
typedef enum {
    TEE_HASH_OP_NONE = 0,     ///< No operation
    TEE_HASH_OP_START = 1,    ///< HASH init
    TEE_HASH_OP_UPDATA = 2,   ///< HASH update
    TEE_HASH_OP_FINISH = 3,   ///< HASH finish
    TEE_HASH_OP_MAX,          ///< invailed operation
} tee_hash_op_e;

/****** TEE HMAC type *****/
typedef enum {
    TEE_HMAC_SHA1 = 1,    ///< HMAC with SHA1
} tee_hmac_type_e;

/**
  \brief       TEE HAMC
  \note        Call csi_tee_hmac_digest is better
               out buffer size must be large enough according to type, eg. 20 bytes for TEE_HMAC_SHA1
  \param[in]   in       Pointer to input data buffer
  \param[in]   in_len   Input data buffer length
  \param[in]   key      Pointer to key buffer
  \param[in]   key_len  Key buffer size
  \param[out]  out      Pointer to output date buffer
  \param[in]   type     \ref tee_hmac_type_e
  \param[in]   hash_op  \ref tee_hash_op_e
  \param[in]   ctx      Pointer to context of hmac
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_hmac(const uint8_t *in, uint32_t  in_len,
                     const uint8_t *key, uint32_t key_len,
                     uint8_t *out,
                     tee_hmac_type_e type,
                     tee_hash_op_e hash_op,
                     uint32_t *ctx);

/**
  \brief       TEE HAMC digest
  \note        out buffer size must be large enough according to type, eg. 20 bytes for TEE_HMAC_SHA1
  \param[in]   in       Pointer to input data buffer
  \param[in]   in_len   Input data buffer length
  \param[in]   key      Pointer to key buffer
  \param[in]   key_len  Key buffer size
  \param[out]  out      Pointer to output date buffer
  \param[in]   type     \ref tee_hmac_type_e
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_hmac_digest(in,in_len,key,key_len,out,type) \
    csi_tee_hmac(in,in_len,key,key_len,out,type,TEE_HASH_OP_NONE,NULL)

/****** TEE SHA type *****/
typedef enum {
    TEE_SHA1 = 0,   ///< SHA1
    TEE_SHA256 = 1, ///< SHA256
    TEE_SHA224 = 2, ///< SHA224
    TEE_SHA384 = 3, ///< SHA384
    TEE_SHA512 = 4, ///< SHA512
    TEE_SHA_MAX,    ///< invaild sha type
} tee_sha_type_t;

/**
  \brief       TEE SHA
  \note        Call csi_tee_sha_digest, csi_tee_sha_start, csi_tee_sha_update or csi_tee_sha_finish is better
               out buffer size must be large enough according to type, eg. 20 bytes for TEE_SHA1, 32 bytes for TEE_SHA256
  \param[in]   in       Pointer to input data buffer
  \param[in]   in_len   Input data buffer length
  \param[out]  out      Pointer to output date buffer
  \param[in]   type     \ref tee_sha_type_t
  \param[in]   hash_op  \ref tee_hash_op_e
  \param[in]   ctx      Pointer to context of sha
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_sha(const uint8_t *in, uint32_t in_len,
                    uint8_t *out,
                    tee_sha_type_t type,
                    tee_hash_op_e hash_op,
                    void *ctx);

/**
  \brief       TEE SHA digest
  \note        out buffer size must be large enough according to type, eg. 20 bytes for TEE_SHA1, 32 bytes for TEE_SHA256
  \param[in]   in       Pointer to input data buffer
  \param[in]   in_len   Input data buffer length
  \param[out]  out      Pointer to output date buffer
  \param[in]   type     \ref tee_sha_type_t
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_sha_digest(in,in_len,out,type) \
    csi_tee_sha(in,in_len,out,type,TEE_HASH_OP_NONE,NULL);

/**
  \brief       TEE SHA start, initial sha
  \param[in]   type     \ref tee_sha_type_t
  \param[in]   ctx      Pointer to context of sha
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_sha_start(type,ctx) \
    csi_tee_sha(NULL,0,NULL,type,TEE_HASH_OP_START,ctx);

/**
  \brief       TEE SHA update, update data
  \param[in]   in       Pointer to input data buffer
  \param[in]   in_len   Input data buffer length
  \param[in]   ctx      Pointer to context of sha
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_sha_update(in,in_len,ctx) \
    csi_tee_sha(in,in_len,NULL,0,TEE_HASH_OP_UPDATA,ctx);

/**
  \brief       TEE SHA digest, get sha digest
  \note        out buffer size must be large enough according to type, eg. 20 bytes for TEE_SHA1, 32 bytes for TEE_SHA256
  \param[out]  out      Pointer to output date buffer
  \param[in]   ctx      Pointer to context of sha
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_sha_finish(out,ctx) \
    csi_tee_sha(NULL,0,out,0,TEE_HASH_OP_FINISH,ctx);

/**
  \brief       TEE get device name and product key
  \param[in]   name_encrypted             Pointer to device name ciphertext
  \param[in]   name_encrypted_len         device name ciphertext length
  \param[in]   product_key_encrypted      Pointer to device product key ciphertext
  \param[in]   product_key_encrypted_len  Device product key ciphertext length
  \param[out]  name                       Pointer to device name
  \param[out]  name_len                   Device name length
  \param[out]  product_key                Pointer to device product key
  \param[out]  product_key_len            Device product key length
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_dev_info_get(const uint8_t *name_encrypted, uint32_t name_encrypted_len,
                             const uint8_t *product_key_encrypted, uint32_t product_key_encrypted_len,
                             const uint8_t *name, uint32_t *name_len,
                             const uint8_t *product_key, uint32_t *product_key_len);

/**
  \brief       TEE device info sign
  \param[in]   in                 Pointer to input date buffer
  \param[in]   in_len             Input data buffer length
  \param[in]   device_secret      Pointer to device secret ciphertext
  \param[in]   device_secret_len  Device secret ciphertext length
  \param[out]  sign               Pointer to signed buffer
  \param[out]  sign_len           Signed buffer length
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_dev_info_sign(const uint8_t *in, uint32_t in_len,
                              const uint8_t *device_secret, uint32_t device_secret_len,
                              const uint8_t *sign, uint32_t *sign_len);

/**
  \brief       TEE device info encrypt/decrypt
  \param[in]   in                 Pointer to input date buffer
  \param[in]   in_len             Input data buffer length
  \param[in]   out                Pointer to output date buffer
  \param[in]   out_len            Onput data buffer length
  \param[in]   is_enc             1 incrypt 0 decrypt
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_dev_info_crypt(const uint8_t *in, uint32_t in_len,
                               uint8_t *out, uint32_t *out_len,
                               uint8_t is_enc);

/**
  \brief       TEE device info encrypt
  \param[in]   in                 Pointer to input date buffer
  \param[in]   in_len             Input data buffer length
  \param[in]   out                Pointer to output date buffer
  \param[in]   out_len            Onput data buffer length
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_dev_info_encrypt(in, in_len, out, out_len) \
    csi_tee_dev_info_crypt(in, in_len, out, out_len, 1)

/**
  \brief       TEE device info decrypt
  \param[in]   in                 Pointer to input date buffer
  \param[in]   in_len             Input data buffer length
  \param[in]   out                Pointer to output date buffer
  \param[in]   out_len            Onput data buffer length
  \return      Return  0 if successful,otherwise error code
*/
#define csi_tee_dev_info_decrypt(in, in_len, out, out_len) \
    csi_tee_dev_info_crypt(in, in_len, out, out_len, 0)

/**
  \brief       Set system frequence
  \param[in]   clk_src      Indicate clock source type
  \param[in]   clk_val      System freqence to be set
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_set_sys_freq(uint32_t clk_src, uint32_t clk_val);

/**
  \brief       Get system frequence
  \param[in]   clk_val      Value address to store system freqence
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_get_sys_freq(uint32_t *clk_val);

/**
  \brief        Read system register
  \param[in]    addr        Indicate register address
  \param[out]   val         Value to read from the address
  \return       Return  0 if successful,otherwise error code
*/
int32_t csi_tee_read_reg(uint32_t addr, uint32_t *val);

/**
  \brief        Wrte system register
  \param[in]    addr        Indicate register address
  \param[in]    val         Value to be written into the address
  \return      Return  0 if successful,otherwise error code
*/
int32_t csi_tee_write_reg(uint32_t addr, uint32_t val);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_TEE_H_ */
