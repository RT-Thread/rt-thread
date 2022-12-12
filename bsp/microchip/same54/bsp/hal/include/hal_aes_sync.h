/**
 * \file
 *
 * \brief AES Advanced Encryption Standard(Sync) functionality declaration.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef HAL_AES_SYNC_H_INCLUDED
#define HAL_AES_SYNC_H_INCLUDED

#include <hpl_aes_sync.h>
#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup doc_driver_hal_crypto_aes_sync
 *
 * @{
 */

struct aes_sync_descriptor {
	struct _aes_sync_device dev; /*!< AES HPL device descriptor */
};

/**
 * \brief              Initialize AES Descriptor
 *
 * \param[in] desc     The AES descriptor to be initialized
 * \param[in] hw       The pointer to hardware instance
 */
int32_t aes_sync_init(struct aes_sync_descriptor *descr, void *const hw);

/**
 * \brief              Deinitialize AES Descriptor
 *
 * \param[in] desc     The AES descriptor to be deinitialized
 */
int32_t aes_sync_deinit(struct aes_sync_descriptor *desc);

/**
 * \brief              Enable AES
 *
 * \param[in] desc     The AES descriptor
 */
int32_t aes_sync_enable(struct aes_sync_descriptor *desc);

/**
 * \brief              Disable AES
 *
 * \param[in] desc     The AES descriptor
 */
int32_t aes_sync_disable(struct aes_sync_descriptor *desc);

/**
 * \brief              Set AES Key (encryption).
 *
 * \param[in] desc     The AES descriptor
 * \param[in] key      Encryption key
 * \param[in] size     Bit length of key
 */
int32_t aes_sync_set_encrypt_key(struct aes_sync_descriptor *descr, const uint8_t *key, const enum aes_keysize size);

/**
 * \brief              Set AES Key (decryption).
 *
 * \param[in] desc     The AES descriptor
 * \param[in] key      Decryption key
 * \param[in] size     Bit length of key
 */
int32_t aes_sync_set_decrypt_key(struct aes_sync_descriptor *descr, const uint8_t *key, const enum aes_keysize size);

/**
 * \brief              AES-ECB block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  input   16-byte input data
 * \param[out] output  16-byte output data
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_ecb_crypt(struct aes_sync_descriptor *descr, const enum aes_action enc, const uint8_t *input,
                           uint8_t *output);

/**
 * \brief              The AES-CBC block encryption/decryption
 *                     length should be a multiple of 16 bytes
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  input   16-byte input data
 * \param[out] output  16-byte output data
 * \param[in]  length  Byte length of the input data
 * \param[in, out] iv  Initialization vector (updated after use)
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_cbc_crypt(struct aes_sync_descriptor *descr, const enum aes_action enc, const uint8_t *input,
                           uint8_t *output, uint32_t length, uint8_t iv[16]);

/**
 * \brief              AES-CFB128 block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[out] length  Byte length of the input data
 * \param[in, out] iv  Initialization Vector (updated after use)
 * \param[in, out] iv_ofst  Offset in IV (updated after use)

 * \return             ERR_NONE if successful
 */
int32_t aes_sync_cfb128_crypt(struct aes_sync_descriptor *descr, const enum aes_action enc, const uint8_t *input,
                              uint8_t *output, uint32_t length, uint8_t *iv, uint32_t *iv_ofst);

/**
 * \brief              AES-CFB64 block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[out] length  Byte length of the input data
 * \param[in, out] iv      Initialization Vector (updated after use)
 * \param[in, out] iv_ofst  Offset in IV (updated after use)
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_cfb64_crypt(struct aes_sync_descriptor *descr, const enum aes_action enc, const uint8_t *input,
                             uint8_t *output, uint32_t length, uint8_t *iv, uint32_t *iv_ofst);

/**
 * \brief              AES-CFB32 block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[out] length  Byte length of the input data
 * \param[in, out] iv      Initialization Vector (updated after use)
 * \param[in, out] iv_ofst  Offset in IV (updated after use)
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_cfb32_crypt(struct aes_sync_descriptor *descr, const enum aes_action enc, const uint8_t *input,
                             uint8_t *output, uint32_t length, uint8_t *iv, uint32_t *iv_ofst);

/**
 * \brief              AES-CFB16 block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[out] length  Byte length of the input data
 * \param[in, out] iv      Initialization Vector (updated after use)
 * \param[in, out] iv_ofst  Offset in IV (updated after use)
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_cfb16_crypt(struct aes_sync_descriptor *descr, const enum aes_action enc, const uint8_t *input,
                             uint8_t *output, uint32_t length, uint8_t *iv, uint32_t *iv_ofst);

/**
 * \brief              AES-CFB8 block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[in, out] iv  Initialization Vector (updated after use)
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_cfb8_crypt(struct aes_sync_descriptor *descr, const enum aes_action enc, const uint8_t *input,
                            uint8_t *output, uint32_t length, uint8_t *iv);

/**
 * \brief              AES-OFB block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[out] length  Byte length of the input data
 * \param[in, out] iv      Initialization Vector (updated after use)
 * \param[in, out] iv_ofst  Offset in IV (updated after use)

 * \return             ERR_NONE if successful
 */
int32_t aes_sync_ofb_crypt(struct aes_sync_descriptor *descr, const uint8_t *input, uint8_t *output, uint32_t length,
                           uint8_t *iv, uint32_t *iv_ofst);

/**
 * \brief              AES-CTR block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[in]  length  Byte length of the input data
 * \param[in]  buffer  Stream block for resuming
 * \param[in]  nc      The 128-bit nonce and counter
 * \param[in]  nc_ofst  The offset in the current stream_block (for resuming
 *                     within current cipher stream). The offset pointer
 *                     should be 0 at the start of a stream.
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_ctr_crypt(struct aes_sync_descriptor *descr, const uint8_t *input, uint8_t *output, uint32_t length,
                           uint8_t buffer[16], uint8_t nc[16], uint32_t *nc_ofst);

/**
 * \brief              AES-GCM block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[in]  length  Byte length of the input data
 * \param[in]  iv      Initialization Vector
 * \param[in]  iv_len  Length of IV
 * \param[in]  aad     Additional data
 * \param[in]  aad_len Length of additional data
 * \param[out] tag     Buffer holding the input data
 * \param[in]  tag_len Length of tag
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_gcm_crypt_and_tag(struct aes_sync_descriptor *const descr, const enum aes_action enc,
                                   const uint8_t *input, uint8_t *output, uint32_t length, const uint8_t *iv,
                                   uint32_t iv_len, const uint8_t *aad, uint32_t aad_len, uint8_t *tag,
                                   uint32_t tag_len);
/**
 * \brief              AES-GCM block encryption
 *
 * \param[in] desc     The AES descriptor
 * \param[in] input    Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[in] length   Byte length of the input data
 * \param[in] iv       Initialization Vector
 * \param[in] iv_len   Length of IV
 * \param[in] aad      Additional data
 * \param[in] aad_len  Length of additional data
 * \param[in] tag      Buffer holding the input data
 * \param[in] tag_len  Length of tag
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_gcm_auth_decrypt(struct aes_sync_descriptor *const descr, const uint8_t *input, uint8_t *output,
                                  uint32_t length, const uint8_t *iv, uint32_t iv_len, const uint8_t *aad,
                                  uint32_t aad_len, const uint8_t *tag, uint32_t tag_len);

/**
 * \brief              AES-GCM block start
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  iv      Initialization Vector
 * \param[in]  iv_len  Length of the IV
 * \param[in]  aad     Additional data
 * \param[in]  aad_len Length of additional data
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_gcm_start(struct aes_sync_descriptor *const descr, const enum aes_action enc, const uint8_t *iv,
                           uint32_t iv_len, const uint8_t *aad, uint32_t aad_len);

/**
 * \brief              AES-GCM block update
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[in]  length  Byte length of the input data
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_gcm_update(struct aes_sync_descriptor *const descr, const uint8_t *input, uint8_t *output,
                            uint32_t length);

/**
 * \brief              AES-GCM block finish
 *
 * \param[in]  descr   The AES descriptor
 * \param[out] tag     Buffer holding the input data
 * \param[in]  tag_len Length of tag
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_gcm_finish(struct aes_sync_descriptor *const descr, uint8_t *tag, uint32_t tag_len);

/**
 * \brief              AES-CCM block encryption/decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  enc     AES_SYNC_ENCRYPT or AES_SYNC_DECRYPT
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[in]  length  Byte length of the input data
 * \param[in]  iv      Initialization Vector
 * \param[in]  iv_len  Length of IV
 * \param[in]  aad     Additional data
 * \param[in]  aad_len Length of additional data
 * \param[in]  tag     Buffer holding the input data
 * \param[in]  tag_len Length of tag
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_ccm_crypt_and_tag(struct aes_sync_descriptor *const descr, const enum aes_action enc,
                                   const uint8_t *input, uint8_t *output, uint32_t length, const uint8_t *iv,
                                   uint32_t iv_len, const uint8_t *aad, uint32_t aad_len, uint8_t *tag,
                                   uint32_t tag_len);

/**
 * \brief              AES-CCM block authenticated decryption
 *
 * \param[in]  descr   The AES descriptor
 * \param[in]  input   Buffer holding the input data
 * \param[out] output  Buffer holding the output data
 * \param[in]  length  Byte length of the input data
 * \param[in]  iv      Initialization Vector
 * \param[in]  iv_len  Length of IV
 * \param[in]  aad     Additional data
 * \param[in]  aad_len Length of additional data
 * \param[in]  tag     Buffer holding the input data
 * \param[in]  tag_len Length of tag
 *
 * \return             ERR_NONE if successful
 */
int32_t aes_sync_ccm_auth_decrypt(struct aes_sync_descriptor *const descr, const uint8_t *input, uint8_t *output,
                                  uint32_t length, const uint8_t *iv, uint32_t iv_len, const uint8_t *aad,
                                  uint32_t aad_len, const uint8_t *tag, uint32_t tag_len);

/**
 * \brief Retrieve the current driver version
 *
 * \return Current driver version.
 */
uint32_t aes_sync_get_version(void);
/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* HAL_AES_SYNC_H_INCLUDED */
