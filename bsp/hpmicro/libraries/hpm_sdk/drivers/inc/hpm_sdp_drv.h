/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SDP_DRV_H
#define HPM_SDP_DRV_H

/**
 * @brief SDP driver APIs
 * @defgroup sdp_interface SDP driver APIs
 * @ingroup sdp_interfaces
 * @{
 *
 */

#include "hpm_common.h"
#include "hpm_sdp_regs.h"
#include "hpm_soc_feature.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/**
 * @brief SDP AES key bit options
 */
typedef enum {
    sdp_aes_keybits_128 = 0,                    /**< 128 bit AES key */
    sdp_aes_keybits_256 = 1,                    /**< 256 bit AES key */
#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
    sdp_sm4_keybits_128 = sdp_aes_keybits_128, /* SM4 Key bits */
#endif
} sdp_crypto_key_bits_t;

typedef sdp_crypto_key_bits_t sdp_aes_key_bits_t;

typedef sdp_crypto_key_bits_t sdp_sm4_key_bits_t;

/**
 * @brief Crypto operation option
 */
typedef enum {
    sdp_aes_op_encrypt,                         /**< AES Encrypt operation */
    sdp_aes_op_decrypt,                         /**< AES Decrypt operation */
#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
    sdp_sm4_op_encrypt = sdp_aes_op_encrypt,    /**< SM4 Encrypt operation */
    sdp_sm4_op_decrypt = sdp_aes_op_decrypt,    /**< SM4 Decrypt operation */
#endif
} sdp_crypto_op_t;

typedef sdp_crypto_op_t sdp_aes_op_t;

#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)

typedef sdp_crypto_op_t sdp_sm4_op_t;

#endif

/**
 * @brief  SDP Crypto algorithms
 *
 */
typedef enum {
    sdp_crypto_alg_aes, /**< AES */
#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
    sdp_crypto_alg_sm4, /**< SM4 */
#endif
} sdp_crypto_alg_t;

/**
 * @brief SDP HASH algorithm definitions
 */
typedef enum {
    sdp_hash_alg_sha1 = 0,                  /**< SDP SHA1 */
    sdp_hash_alg_crc32 = 1,                 /**< SDP CRC32 */
    sdp_hash_alg_sha256 = 2,                /**< SDP SHA256 */
#if defined(SDP_HAS_SM3_SUPPORT) && (SDP_HAS_SM3_SUPPORT == 1)
    sdp_hash_alg_sm3 = 8,                   /**< SDP SM3 */
    sdp_hash_alg_max = sdp_hash_alg_sm3,
#else
    sdp_hash_alg_max = sdp_hash_alg_sha256,
#endif
} sdp_hash_alg_t;

#define HASH_BLOCK_SIZE (64U)               /**< Hash block size in bytes */
#define AES_BLOCK_SIZE (16U)                /**< AES block size in bytes */
#define AES_128_KEY_SIZE (0x10U)            /**< AES 128-bit key size in bytes */
#define AES_256_KEY_SIZE (0x20U)            /**< AES 256-bit key size in bytes */

#define SM4_BLOCK_SIZE (AES_BLOCK_SIZE)     /**< SM4 block size in bytes */
#define SM4_KEY_SIZE (AES_128_KEY_SIZE)     /**< SM4 Key size in bytes */

/**
 * @brief Bitfield definitions for the PKT_CTRL
 */
#define SDP_PKT_CTRL_DERSEMA_MASK (1U << 2)
#define SDP_PKT_CTRL_CHAIN_MASK (1U << 3)
#define SDP_PKT_CTRL_HASHINIT_MASK (1U << 4)
#define SDP_PKT_CTRL_HASHFINISH_MASK (1U << 5)
#define SDP_PKT_CTRL_CIPHIV_MASK (1U << 6)

/**
 * @brief SDP packet data structure
 */
typedef struct _sdp_packet_struct {
    struct _sdp_packet_struct *next_cmd;
    union {
        struct {
            uint32_t RESERVED0: 1;
            uint32_t PKTINT: 1;     /**< Packet interrupt flag */
            uint32_t DCRSEMA: 1;    /**< Descrement Semaphore flag */
            uint32_t CHAIN: 1;      /**< Chain Packet flag */
            uint32_t HASHINIT: 1;   /**< Hash initialize flag */
            uint32_t HASHFINISH: 1; /**< Hash finish flag */
            uint32_t CIPHIV: 1;     /**< Cipher IV flag */
            uint32_t RESERVED1: 17;
            uint32_t PKTTAG: 8; /**< Packet tag flag, not used */
        };
        uint32_t PKT_CTRL; /**< Packet control word */
    } pkt_ctrl;
    uint32_t src_addr; /**< Source address */
    uint32_t dst_addr; /**< Destination address */
    uint32_t buf_size; /**< Data buffer size in bytes */
    uint32_t reserved[3];
} sdp_pkt_struct_t;

/**
 * @brief SDP AES context structure
 */
typedef struct {
    uint8_t key_idx;  /**< AES key index */
    uint8_t key_bits; /**< AES key bits */
    uint16_t crypto_algo;
    sdp_pkt_struct_t sdp_pkt;                         /**< SDP packet for AES operation */
    uint32_t buf0[AES_BLOCK_SIZE / sizeof(uint32_t)]; /**< buf0 */
    uint32_t buf1[AES_BLOCK_SIZE / sizeof(uint32_t)]; /**< buf1 */
    uint32_t buf2[AES_BLOCK_SIZE / sizeof(uint32_t)]; /**< buf2 */
    uint32_t buf3[AES_BLOCK_SIZE / sizeof(uint32_t)]; /**< buf3 */
} sdp_crypto_ctx_t;

typedef sdp_crypto_ctx_t sdp_aes_ctx_t;

#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
typedef sdp_crypto_ctx_t sdp_sm4_ctx_t;
#endif

/**
 * @brief SDP DMA context
 */
typedef struct {
    sdp_pkt_struct_t sdp_pkt; /**< SDP packet for DMA operation (memset/memcpy) */
} sdp_dma_ctx_t;

/**
 * @brief SDP HASH context
 */
typedef struct {
    sdp_pkt_struct_t sdp_pkt; /**< SDP packet for HASH operation */
    uint32_t internal[64];    /**< internal buffer */
} sdp_hash_ctx_t;

/**
 * @brief SDP error status definitions
 */
enum {
    status_sdp_no_crypto_support = MAKE_STATUS(status_group_sdp, 0), /**< The crypto algorithm is not supported */
    status_sdp_no_hash_support = MAKE_STATUS(status_group_sdp, 1),   /**< The hash algorithm is not supported */
    status_sdp_invalid_key_src = MAKE_STATUS(status_group_sdp, 2),   /**< Invalid AES key source */
    status_sdp_error_packet = MAKE_STATUS(status_group_sdp, 3),      /**< Error packet */
    status_sdp_aes_busy = MAKE_STATUS(status_group_sdp, 4),          /**< AES engine is busy */
    status_sdp_hash_busy = MAKE_STATUS(status_group_sdp, 5),         /**< HASH engine is busy */
    status_sdp_error_setup = MAKE_STATUS(status_group_sdp, 6),       /**< Error setup in SDP IP */
    status_sdp_error_src = MAKE_STATUS(status_group_sdp, 7),         /**< Error source address */
    status_sdp_error_dst = MAKE_STATUS(status_group_sdp, 8),         /**< Error destination address */
    status_sdp_error_hash = MAKE_STATUS(status_group_sdp, 9),        /**< Error Hash digest */
    status_sdp_error_chain = MAKE_STATUS(status_group_sdp, 10),      /**< Error packet chain */
    status_sdp_error_invalid_mac = MAKE_STATUS(status_group_sdp, 11),/**< Inavlid Message Athenticaion Code (MAC) */
    status_sdp_invalid_alg = MAKE_STATUS(status_group_sdp, 12),      /**< Invalid algorithm */

};

#ifdef __cplusplus
extern "C"
{
#endif


/***********************************************************************************************************************
 * Prototypes
 **********************************************************************************************************************/
/**
 * @brief Initialize the SDP controller
 * @param [in] base SDP base address
 * @retval API execution status.
 */
hpm_stat_t sdp_init(SDP_Type *base);

/**
 * @brief De-initialize the SDP controller
 * @param [in] base SDP base address
 * @retval API execution status.
 */
hpm_stat_t sdp_deinit(SDP_Type *base);

/**
 * @brief Set the AES key for the SDP AES operation
 * @param [in] base SDP base address
 * @param [in] aes_ctx AES operation context
 * @param [in] key AES key
 * @param [in] key_bits AES key-bit option
 * @param [in] key_idx AES key index
 * @retval API execution status.
 */
hpm_stat_t sdp_aes_set_key(SDP_Type *base,
                           sdp_aes_ctx_t *aes_ctx,
                           const uint8_t *key,
                           sdp_aes_key_bits_t key_bits,
                           uint32_t key_idx);

#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
/**
 * @brief Set the SM4 key for the SDP SM4 operation
 * @param [in] base SDP base address
 * @param [in] sm4_ctx AES operation context
 * @param [in] key SM4 key
 * @param [in] key_bits SM4 key-bit option
 * @param [in] key_idx AES key index
 * @retval API execution status.
 */
hpm_stat_t sdp_sm4_set_key(SDP_Type *base,
                           sdp_sm4_ctx_t *sm4_ctx,
                           const uint8_t *key,
                           sdp_sm4_key_bits_t key_bits,
                           uint32_t key_idx);
#endif

/**
 * @brief Perform the basic AES ECB operation
 * @param [in] base SDP base address
 * @param [in] aes_ctx AES operation context
 * @param [in] op AES operation option
 * @param [in] len AES data length in bytes
 * @param [in] in Input buffer
 * @param [out] out Output buffer
 * @retval API execution status.
 */
hpm_stat_t sdp_aes_crypt_ecb(SDP_Type *base,
                             sdp_aes_ctx_t *aes_ctx,
                             sdp_aes_op_t op,
                             uint32_t len,
                             const uint8_t *in,
                             uint8_t *out);

#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
/**
 * @brief Perform the basic SM4 ECB operation
 * @param [in] base SDP base address
 * @param [in] sm4_ctx SM4 operation context
 * @param [in] op SM4 operation option
 * @param [in] len SM4 data length in bytes
 * @param [in] in Input buffer
 * @param [out] out Output buffer
 * @retval API execution status.
 */
#define sdp_sm4_crypt_ecb sdp_aes_crypt_ecb
#endif

/**
 * @brief Perform the AES CBC operation
 * @param [in] base SDP base address
 * @param [in] aes_ctx AES operation context
 * @param [in] op AES operation option
 * @param [in] length AES data length in bytes
 * @param [in] iv Initial vector/nonce
 * @param [in] input Input buffer
 * @param [out] output Output buffer
 * @retval API execution status.
 */
hpm_stat_t sdp_aes_crypt_cbc(SDP_Type *base,
                             sdp_aes_ctx_t *aes_ctx,
                             sdp_aes_op_t op,
                             uint32_t length,
                             const uint8_t iv[16],
                             const uint8_t *input,
                             uint8_t *output);

#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
/**
 * @brief Perform the SM4 CBC operation
 * @param [in] base SM4 base address
 * @param [in] sm4_ctx SM4 operation context
 * @param [in] op SM4 operation option
 * @param [in] length SM4 data length in bytes
 * @param [in] iv Initial vector/nonce
 * @param [in] input Input buffer
 * @param [out] output Output buffer
 * @retval API execution status.
 */
#define sdp_sm4_crypt_cbc sdp_aes_crypt_cbc
#endif

/**
 * @brief Perform the AES-CTR operation
 *        See NIST Special Publication800-38A for more details
 * @param [in] base SDP base address
 * @param [in] aes_ctx AES operation context
 * @param [in] nonce_counter AES-CTR nounce/counter
 * @param [in] input Input buffer
 * @param [out] output Output buffer
 * @param [in] length Length of data for AES-CTR operation
 * @retval API execution status.
 */
hpm_stat_t sdp_aes_crypt_ctr(SDP_Type *base,
                             sdp_aes_ctx_t *aes_ctx,
                             uint8_t *nonce_counter,
                             uint8_t *input,
                             uint8_t *output,
                             uint32_t length);

#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
/**
 * @brief Perform the SM4-CTR operation
 * @param [in] base SDP base address
 * @param [in] sm4_ctx SM4 operation context
 * @param [in] nonce_counter SM4-CTR nounce/counter
 * @param [in] input Input buffer
 * @param [out] output Output buffer
 * @param [in] length Length of data for SM4-CTR operation
 * @retval API execution status.
 */
#define sdp_sm4_crypt_ctr sdp_aes_crypt_ctr
#endif

/**
 * @brief Perform the AES-CCM generate and encrypt
 *        See NIST Special Publication 800-38C for more details
 * @param [in] base SDP base address
 * @param [in] aes_ctx AES operation context
 * @param [in] input_len Input data length in bytes
 * @param [in] iv Initial vector
 * @param [in] iv_len Initial vector length in bytes
 * @param [in] aad Additional Authentication data
 * @param [in] aad_len Additional authentication data size
 * @param [in] input Input data buffer
 * @param [out] output Output buffer
 * @param [out] tag MAC buffer
 * @param [in] tag_len Tag/MAC size in bytes
 * @retval API execution status.
 */
hpm_stat_t sdp_aes_ccm_generate_encrypt(SDP_Type *base,
                                        sdp_aes_ctx_t *aes_ctx,
                                        uint32_t input_len,
                                        const uint8_t *iv,
                                        uint32_t iv_len,
                                        const uint8_t *aad,
                                        uint32_t aad_len,
                                        const uint8_t *input,
                                        uint8_t *output,
                                        uint8_t *tag,
                                        uint32_t tag_len);

#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
/**
 * @brief Perform the SM4-CCM generate and encrypt
 *        See NIST Special Publication 800-38C for more details
 * @param [in] base SDP base address
 * @param [in] sm4_ctx SM4 operation context
 * @param [in] input_len Input data length in bytes
 * @param [in] iv Initial vector
 * @param [in] iv_len Initial vector length in bytes
 * @param [in] aad Additional Authentication data
 * @param [in] aad_len Additional authentication data size
 * @param [in] input Input data buffer
 * @param [out] output Output buffer
 * @param [out] tag MAC buffer
 * @param [in] tag_len Tag/MAC size in bytes
 * @retval API execution status.
 */
#define sdp_sm4_ccm_generate_encrypt sdp_aes_ccm_generate_encrypt
#endif

/**
 * @brief Perform the AES-CCM decrypt and verify
 *        See NIST Special Publication 800-38C for more details
 * @param [in] base SDP base address
 * @param [in] aes_ctx AES operation context
 * @param [in] input_len Input data length in bytes
 * @param [in] iv Initial vector
 * @param [in] iv_len Initial vector length in bytes
 * @param [in] aad Additional Authentication data
 * @param [in] aad_len Additional authentication data size
 * @param [in] input Input data buffer
 * @param [out] output Output buffer
 * @param [in] tag MAC buffer
 * @param [in] tag_len Tag/MAC size in bytes
 * @retval API execution status.
 */
hpm_stat_t sdp_aes_ccm_decrypt_verify(SDP_Type *base,
                                      sdp_aes_ctx_t *aes_ctx,
                                      uint32_t input_len,
                                      const uint8_t *iv,
                                      uint32_t iv_len,
                                      const uint8_t *aad,
                                      uint32_t aad_len,
                                      const uint8_t *input,
                                      uint8_t *output,
                                      const uint8_t *tag,
                                      uint32_t tag_len);

#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
/**
 * @brief Perform the SM4-CCM decrypt and verify
 * @param [in] base SDP base address
 * @param [in] sm4_ctx SM4 operation context
 * @param [in] input_len Input data length in bytes
 * @param [in] iv Initial vector
 * @param [in] iv_len Initial vector length in bytes
 * @param [in] aad Additional Authentication data
 * @param [in] aad_len Additional authentication data size
 * @param [in] input Input data buffer
 * @param [out] output Output buffer
 * @param [in] tag MAC buffer
 * @param [in] tag_len Tag/MAC size in bytes
 * @retval API execution status.
 */
#define sdp_sm4_ccm_decrypt_verify sdp_aes_ccm_decrypt_verify
#endif
/**
 * @brief Perform the DMA accelerated memcpy
 * @param [in] base SDP base address
 * @param [in] sdp_ctx SDP DMA context
 * @param [out] dst Destination address for memcpy operation
 * @param [in] src Source address for memcpy operation
 * @param [in] length Length of the data to be copied
 * @retval API execution status.
 */
hpm_stat_t sdp_memcpy(SDP_Type *base, sdp_dma_ctx_t *sdp_ctx, void *dst, const void *src, uint32_t length);

/**
 * @brief Perform the DMA accelerated memset
 * @param [in] base SDP base address
 * @param [in] sdp_ctx SDP DMA context
 * @param [out] dst SDP destination address for memset operation
 * @param [in] pattern pattern for memset operation
 * @param [in] length length of the memory for memset operation
 * @retval API execution status.
 */
hpm_stat_t sdp_memset(SDP_Type *base, sdp_dma_ctx_t *sdp_ctx, void *dst, uint8_t pattern, uint32_t length);

/**
 * @brief Initialize the HASH engine
 * @param [in] base SDP base address
 * @param [in] hash_ctx HASH operation context
 * @param [in] alg Hash algorithm
 * @retval API execution status. status_success or status_invalid_argument
 */
hpm_stat_t sdp_hash_init(SDP_Type *base, sdp_hash_ctx_t *hash_ctx, sdp_hash_alg_t alg);

/**
 * @brief Compute the HASH digest
 * @param [in] base SDP base address
 * @param [in] hash_ctx HASH operation context
 * @param [in] data Data for HASH computing
 * @param [in] length Data size for HASH computing
 * @retval API execution status.
 */
hpm_stat_t sdp_hash_update(SDP_Type *base, sdp_hash_ctx_t *hash_ctx, const uint8_t *data, uint32_t length);

/**
 * @brief Finish the HASH calculation and output the digest
 * @param [in] base SDP base address
 * @param [in] hash_ctx HASH operation context
 * @param [out] digest  Digest buffer
 * @retval API execution status.
 */
hpm_stat_t sdp_hash_finish(SDP_Type *base, sdp_hash_ctx_t *hash_ctx, uint8_t *digest);

/**
 * @brief Wait until the SDP operation gets done
 * @retval API execution status.
 */
hpm_stat_t sdp_wait_done(SDP_Type *base);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* HPM_SDP_DRV_H */
