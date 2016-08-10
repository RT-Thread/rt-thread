/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_LTC_DRIVER_AES_H__
#define __FSL_LTC_DRIVER_AES_H__

/*!
 * @addtogroup ltc_driver_aes
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! AES block size in bytes */
#define LTC_AES_BLOCK_SIZE 16

/*! AES IV size in bytes */
#define LTC_AES_IV_SIZE 16

/*! LTC module FIFO size in bytes aligned down to the AES block boundary */
#define FSL_LTC_FIFO_SZ_MAX_DOWN_ALGN (0xff0u)

/*! For CCM encryption, the encrypted final MAC is written to the context word 8-11 */
#define FSL_LTC_CCM_TAG_IDX 8

/*! For GCM encryption, the encrypted final MAC is written to the context word 0-3 */
#define FSL_LTC_GCM_TAG_IDX 0

/*! @brief Type of AES key for ECB and CBC decrypt operations. */
typedef enum _ltc_drv_aes_key_t {
    kLtcEncryptKey      = 0U,  /*!< Input key is an encrypt key (the same key which has been used for encrypt operation) */
    kLtcDecryptKey      = 1U,  /*!< Input key is a decrypt key (the key has been obtained from LTC_DRV_aes_generate_decrypt_key()). */
} ltc_drv_aes_key_t;

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

#if FSL_FEATURE_LTC_HAS_DPAMS
/*!
 * @brief Sets the DPA Mask Seed register.
 *
 * The DPA Mask Seed register reseeds the mask that provides resistance against DPA attacks on AES keys.
 *
 * Differential Power Analysis Mask (DPA) resistance uses a randomly changing mask that introduces
 * "noise" into the power consumed by the AESA. This reduces the signal-to-noise ratio that differential
 * power analysis attacks use to "guess" bits of the AES key. This randomly changing mask should be
 * seeded at POR, and continues to provide DPA resistance from that point on. However, to provide even more
 * DPA protection it is recommended that the DPA mask be reseeded after every 50,000 AESA blocks have
 * been processed. At that time, software can opt to write a new seed (preferably obtained from an RNG)
 * into the DPA Mask Seed register (DPAMS), or software can opt to provide the new seed earlier or
 * later, or not at all. DPA resistance continues even if the DPA mask is never reseeded.
 *
 * @param instance LTC module instance number. 
 * @param mask The DPA mask seed.
 */
void LTC_DRV_SetDPAMaskSeed(uint32_t instance, uint32_t mask);
#endif
                             
/*!
 * @brief Transforms an AES encrypt key (forward AES) into the decrypt key (inverse AES).
 *
 * Transforms the AES encrypt key (forward AES) into the decrypt key (inverse AES).
 * The key derived by this function can be used as a direct load decrypt key
 * for AES ECB and CBC decryption operations (keyType argument).
 *
 * @param instance LTC module instance number. 
 * @param encryptKey Input key for decrypt key transformation
 * @param[out] decryptKey Output key, the decrypt form of the AES key.
 * @param keySize Size of the input key and output key in bytes. Must be 16, 24, or 32.
 * @return Status from key generation operation
 */
ltc_status_t LTC_DRV_aes_generate_decrypt_key(uint32_t instance, 
                                              const uint8_t *encryptKey,
                                              uint8_t *decryptKey,
                                              uint32_t keySize);

/*!
 * @brief Encrypts AES using the ECB block mode.
 *
 * Encrypts AES using the ECB block mode.
 *
 * @param instance LTC module instance number.
 * @param plaintext Input single block (128-bits) of plain text to encrypt
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32. 
 * @param[out] ciphertext Ouput single block (128-bits) of cipher text 
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t LTC_DRV_aes_encrypt_ecb(uint32_t instance, 
                                     const uint8_t plaintext[16],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     uint8_t ciphertext[16]);

/*!
 * @brief Decrypts AES using ECB block mode.
 *
 * Decrypts AES using ECB block mode.
 *
 * @param instance LTC module instance number.
 * @param ciphertext Input single block (128-bits) of cipher text to decrypt
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param keyType Input type of the key (allows to directly load decrypt key for AES ECB decrypt operation.)
 * @param[out] plaintext Output single block (128-bits) of plain text
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t LTC_DRV_aes_decrypt_ecb(uint32_t instance,
                                     const uint8_t ciphertext[16],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     ltc_drv_aes_key_t keyType,
                                     uint8_t plaintext[16]);

/*!
 * @brief Encrypts AES using CBC block mode.
 *
 * LTC_DRV_aes_encrypt_cbc
 *
 * @param instance LTC module instance number.
 * @param plaintext Input plain text to encrypt
 * @param inputSize Size of input data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] ciphertext Output cipher text
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t LTC_DRV_aes_encrypt_cbc(uint32_t instance,
                                     const uint8_t *plaintext,
                                     uint32_t inputSize,
                                     uint8_t iv[LTC_AES_IV_SIZE],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     uint8_t *ciphertext);

/*!
 * @brief Decrypts AES using CBC block mode.
 *
 * LTC_DRV_aes_decrypt_cbc
 *
 * @param instance LTC module instance number.
 * @param ciphertext Input cipher text to decrypt
 * @param inputSize Size of input data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param keyType Input type of the key (allows to directly load decrypt key for AES CBC decrypt operation.)
 * @param[out] plaintext Output plain text
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t LTC_DRV_aes_decrypt_cbc(uint32_t instance,
                                     const uint8_t *ciphertext,
                                     uint32_t inputSize,
                                     uint8_t iv[LTC_AES_IV_SIZE],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     ltc_drv_aes_key_t keyType,
                                     uint8_t *plaintext);

/*! AES CTR decrypt is mapped to the AES CTR generic operation */
#define LTC_DRV_aes_decrypt_ctr(instance, input, inputSize, counter, key, keySize, output, counterlast, szLeft) \
        LTC_DRV_aes_ctr(instance, input, inputSize, counter, key, keySize, output, counterlast, szLeft)
        
/*! AES CTR encrypt is mapped to the AES CTR generic operation */
#define LTC_DRV_aes_encrypt_ctr(instance, input, inputSize, counter, key, keySize, output, counterlast, szLeft) \
        LTC_DRV_aes_ctr(instance, input, inputSize, counter, key, keySize, output, counterlast, szLeft)
                                     
/*!
 * @brief Encrypts or decrypts AES using CTR block mode.
 *
 * Encrypts or decrypts AES using CTR block mode.
 * AES CTR mode uses only forward AES cipher and same algorithm for encryption and decryption.
 * The only difference between encryption and decryption is that, for encryption, the input argument
 * is plain text and the output argument is cipher text. For decryption, the input argument is cipher text
 * and the output argument is plain text.
 *
 * @param instance LTC module instance number.
 * @param input Input data for CTR block mode
 * @param inputSize Size of input data in bytes
 * @param[in,out] counter Input counter (updates on return)
 * @param key Input key to use for forward AES cipher
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] output Output data for CTR block mode
 * @param[out] counterlast Output cipher of last counter, for chained CTR calls. NULL can be passed if chained calls are not used.
 * @param[out] szLeft Output number of bytes in left unused in counterlast block. NULL can be passed if chained calls are not used.
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t LTC_DRV_aes_ctr(uint32_t instance,
                             const uint8_t *input,
                             uint32_t inputSize,
                             uint8_t counter[16],
                             const uint8_t *key,
                             uint32_t keySize,
                             uint8_t *output,
                             uint8_t counterlast[16],
                             uint32_t *szLeft);

#if FSL_FEATURE_LTC_HAS_GCM                                     
/*!
 * @brief Encrypts AES using GCM block mode.
 *
 * Encrypts AES using GCM block mode. If plaintext is NULL, only the GHASH is calculated and output in the 'tag' field.
 *
 * @param instance LTC module instance number.
 * @param plaintext Input plain text to encrypt
 * @param inputSize Size of input data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] ciphertext Output cipher text.
 * @param[out] tag Output hash tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4,8,12,13,14,15 or 16. 
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t LTC_DRV_aes_encrypt_tag_gcm(uint32_t instance, 
                                         const uint8_t *plaintext,
                                         uint32_t inputSize,
                                         const uint8_t *iv,
                                         uint32_t ivSize,
                                         const uint8_t *aad,
                                         uint32_t aadSize,
                                         const uint8_t *key,
                                         uint32_t keySize,
                                         uint8_t *ciphertext,
                                         uint8_t *tag,
                                         uint32_t tagSize);

/*!
 * @brief Decrypts AES using GCM block mode.
 *
 * Decrypts AES using GCM block mode. If ciphertext is NULL, only the GHASH is calculated and compared with the received GHASH in 'tag' field.
 *
 * @param instance LTC module instance number.
 * @param ciphertext Input cipher text to decrypt
 * @param inputSize Size of input data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32. 
 * @param[out] plaintext Output plain text. 
 * @param tag Input hash tag to compare. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag, in bytes. Must be 4, 8, 12, 13, 14, 15, or 16.
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t LTC_DRV_aes_decrypt_tag_gcm(uint32_t instance, 
                                         const uint8_t *ciphertext,
                                         uint32_t inputSize,
                                         const uint8_t *iv,
                                         uint32_t ivSize,
                                         const uint8_t *aad,
                                         uint32_t aadSize,
                                         const uint8_t *key,
                                         uint32_t keySize,
                                         uint8_t *plaintext,
                                         const uint8_t *tag,
                                         uint32_t tagSize);
#endif /* FSL_FEATURE_LTC_HAS_GCM */

/*!
 * @brief Encrypts AES using CCM block mode.
 *
 * Encrypts AES using CCM block mode.
 *
 * @param instance LTC module instance number.
 * @param plaintext Input plain text to encrypt
 * @param inputSize Size of input data in bytes. Zero means authentication only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication skipped).
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] ciphertext Output cipher text.
 * @param[out] tag Generated output tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4, 6, 8, 10, 12, 14, or 16.
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t LTC_DRV_aes_encrypt_tag_ccm(uint32_t instance, 
                                         const uint8_t *plaintext,
                                         uint32_t inputSize,
                                         const uint8_t *iv,
                                         uint32_t ivSize,
                                         const uint8_t *aad,
                                         uint32_t aadSize,
                                         const uint8_t *key,
                                         uint32_t keySize,
                                         uint8_t *ciphertext,
                                         uint8_t *tag,
                                         uint32_t tagSize);

/*!
 * @brief Decrypts AES using CCM block mode.
 *
 * Decrypts AES using CCM block mode.
 *
 * @param instance LTC module instance number.
 * @param ciphertext Input cipher text to decrypt
 * @param inputSize Size of input data in bytes. Zero means authentication only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication skipped). 
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] plaintext Output plain text. 
 * @param tag Received tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the received tag to compare with the computed tag, in bytes. Must be 4, 6, 8, 10, 12, 14, or 16.
 * @return Status from encrypt/decrypt operation
 */
ltc_status_t LTC_DRV_aes_decrypt_tag_ccm(uint32_t instance, 
                                         const uint8_t *ciphertext,
                                         uint32_t inputSize,
                                         const uint8_t *iv,
                                         uint32_t ivSize,
                                         const uint8_t *aad,
                                         uint32_t aadSize,
                                         const uint8_t *key,
                                         uint32_t keySize,
                                         uint8_t *plaintext,
                                         const uint8_t *tag,
                                         uint32_t tagSize);

#if defined(__cplusplus)
}
#endif
/*!
 *@}
 */
#endif /* __FSL_LTC_DRIVER_AES_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/
