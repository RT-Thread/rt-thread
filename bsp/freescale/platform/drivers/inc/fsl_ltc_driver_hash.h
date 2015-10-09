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

#ifndef __FSL_LTC_DRIVER_HASH_H__
#define __FSL_LTC_DRIVER_HASH_H__

/*!
 * @addtogroup ltc_driver_hash
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! Internal states of the HASH creation process */
typedef enum _ltc_drv_hash_algo_state {
    kLtcHashInit = 1u,        /*!< Key in the HASH context is the input key. */
    kLtcHashUpdate,           /*!< HASH context has algorithm specific context: MAC, K2 and K3 (XCBC-MAC) or MAC and L (CMAC). Key in the HASH context is the derived key. */
} ltc_drv_hash_algo_state;

/*! Supported cryptographic block cipher functions for HASH creation */
typedef enum _ltc_drv_hash_algo {
    kLtcXcbcMac = kLTCMode_XCBC_MAC,  /*!< XCBC-MAC (AES engine) */
    kLtcCMAC = kLTCMode_CMAC,         /*!< CMAC (AES engine) */
} ltc_drv_hash_algo;

/*! 16-byte block represented as byte array or four 32-bit words */
typedef union _ltc_drv_hash_block {
    uint8_t  b[16]; /*!< byte array */
    uint32_t w[4];  /*!< array of 32-bit words */
} ltc_drv_hash_block;

/*! Definitions of indexes into hash context array */
typedef enum _ltc_drv_hash_ctx_indexes {    
    kLtcHashCtxKeyStartIdx = 12, /*!< context word array index where key is stored */
    kLtcHashCtxKeySize = 20,  /*!< context word array index where key size is stored */
    kLtcHashCtxNumWords = 21, /*!< number of context array 32-bit words  */
} ltc_drv_hash_ctx_indexes;

/*!
 * @brief Data structure with hash context.
 * 
 * XCBC-MAC needs to store 48 bytes of context (MAC, K2 and K3) between message chunks processing. @n
 * CMAC needs less (32 bytes) of context (MAC and L) between message chunks processing. @n
 * @n
 * In both modes, also the derived AES key must be restored from the context. @n
 * @n 
 * If state of the hash software process is kLtcCmacInit, the context is defined as follows @n
 * word[20] = key_size = word[kLtcCmacCtxKeySize] @n
 * word[12-19] = init key @n
 * @n
 * If state of the hash software process is kLtcCmacUpdate, the context for kLtcXcbcMac hash is defined as follows @n
 * word[0-3] = mac @n
 * word[3-7] = k3 @n
 * word[8-11] = k2 @n
 * word[12-19] = k1 @n
 * word[20] = key_size = word[kLtcCmacCtxKeySize] @n
 * @n
 * If state of the hash software process is kLtcCmacUpdate, the context for kLtcCMAC hash is defined as follows @n
 * word[0-3] = mac @n
 * word[3-7] = L @n
 * word[12-19] = k1 @n
 * word[20] = key_size = word[kLtcCmacCtxKeySize] @n
 * @n
 * During hash updates we only process 16-byte blocks. If we have less data then keep them only in context.
 * The 'blk' memory buffer is flushed to LTC during hash finish.     
 */
typedef struct _ltc_drv_hash_ctx {
    ltc_drv_hash_block blk; /*!< memory buffer. only full 16-byte blocks are written to LTC during hash updates */
    uint32_t blksz;         /*!< number of valid bytes in memory buffer */
    uint32_t instance;      /*!< LTC module instance number */
    ltc_drv_hash_algo algo; /*!< selected algorithm from the set of supported algorithms in ltc_drv_hash_algo */
    ltc_drv_hash_algo_state state; /*!< finite machine state of the hash software process */
    uint32_t word[kLtcHashCtxNumWords]; /*!< LTC module context that needs to be saved/restored between LTC jobs */
} ltc_drv_hash_ctx;

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize HASH context
 *
 * This function initialize the HASH with a given key, and selects a block
 * cipher to use.
 *
 * For XCBC-MAC, the key length must be 16. For CMAC, the key length can be
 * the AES key lengths supported by AES engine.
 *
 * @param instance LTC module instance number.
 * @param[out] ctx Output hash context
 * @param algo Block cipher algorithm to use for HASH creation
 * @param key Input key
 * @param keySize Size of input key in bytes
 *
 * @return 0 on succes, or kFSLCryptErrInvalidKeyLength
 */
ltc_status_t LTC_DRV_hash_init(uint32_t instance,
                               ltc_drv_hash_ctx *ctx,
                               ltc_drv_hash_algo algo,
                               const uint8_t *key,
                               uint32_t keySize);

/*!
 * @brief Add data to current HASH
 *
 * Add data to current HASH. This can be called repeatedly with an arbitrary amount of data to be
 * hashed.
 *
 * @param[in,out] ctx HASH context
 * @param input Input data
 * @param inputSize Size of input data in bytes
 * @return Status of the hash update operation
 */
ltc_status_t LTC_DRV_hash_update(ltc_drv_hash_ctx *ctx,
                     const uint8_t *input,
                     uint32_t inputSize);

/*!
 * @brief Finalize hashing
 *
 * Outputs the final hash and erases the context.
 *
 * @param[in,out] ctx Input hash context
 * @param[out] output Output hash data
 * @param[out] outputSize Output param storing the size of the output hash in bytes
 * @return Status of the hash finish operation
 */
ltc_status_t LTC_DRV_hash_finish(ltc_drv_hash_ctx *ctx,
                                 uint8_t *output,
                                 uint32_t *outputSize);

/*!
 * @brief Create HASH on given data
 *
 * Peform the full keyed HASH in one function call.
 *
 * @param instance LTC module instance number.
 * @param algo Block cipher algorithm to use for CMAC creation
 * @param input Input data
 * @param inputSize Size of input data in bytes
 * @param key Input key
 * @param keySize Size of input key in bytes
 * @param[out] output Output hash data
 * @param[out] outputSize Output param storing the size of the output hash in bytes
 * @return Status of the one call hash operation.
 */
ltc_status_t LTC_DRV_hash(uint32_t instance, 
                          ltc_drv_hash_algo algo,
                          const uint8_t *input,
                          uint32_t inputSize,
                          const uint8_t *key,
                          uint32_t keySize,
                          uint8_t *output,
                          uint32_t *outputSize);

#if defined(__cplusplus)
}
#endif
/*!
 *@}
 */
#endif /* __FSL_LTC_DRIVER_HASH_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/
