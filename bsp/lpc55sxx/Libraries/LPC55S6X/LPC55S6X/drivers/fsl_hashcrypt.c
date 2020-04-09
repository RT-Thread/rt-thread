/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_hashcrypt.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.hashcrypt"
#endif

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*!< SHA-1 and SHA-256 block size  */
#define SHA_BLOCK_SIZE 64
/*!< max number of blocks that can be proccessed in one run (master mode) */
#define SHA_MASTER_MAX_BLOCKS 2048

/*!< Use standard C library memcpy  */
#define hashcrypt_memcpy memcpy

/*! Internal states of the HASH creation process */
typedef enum _hashcrypt_sha_algo_state
{
    kHASHCRYPT_HashInit = 1u, /*!< Init state, the NEW bit in SHA Control register has not been written yet. */
    kHASHCRYPT_HashUpdate, /*!< Update state, DIGEST registers contain running hash, NEW bit in SHA control register has
                              been written. */
} hashcrypt_sha_algo_state_t;

/*! 64-byte block represented as byte array of 16 32-bit words */
typedef union _sha_hash_block
{
    uint32_t w[SHA_BLOCK_SIZE / 4]; /*!< array of 32-bit words */
    uint8_t b[SHA_BLOCK_SIZE];      /*!< byte array */
} hashcrypt_sha_block_t;

/*! internal sha context structure */
typedef struct _hashcrypt_sha_ctx_internal
{
    hashcrypt_sha_block_t blk; /*!< memory buffer. only full 64-byte blocks are written to SHA during hash updates */
    size_t blksz;              /*!< number of valid bytes in memory buffer */
    hashcrypt_algo_t algo;     /*!< selected algorithm from the set of supported algorithms */
    hashcrypt_sha_algo_state_t state;  /*!< finite machine state of the hash software process */
    size_t fullMessageSize;            /*!< track message size during SHA_Update(). The value is used for padding. */
    uint32_t remainingBlcks;           /*!< number of remaining blocks to process in AHB master mode */
    hashcrypt_callback_t hashCallback; /*!< pointer to HASH callback function */
    void
        *userData; /*!< user data to be passed as an argument to callback function, once callback is invoked from isr */
} hashcrypt_sha_ctx_internal_t;

/*!< SHA-1 and SHA-256 digest length in bytes  */
enum _hashcrypt_sha_digest_len
{
    kHASHCRYPT_OutLenSha1   = 20u,
    kHASHCRYPT_OutLenSha256 = 32u,
};

/*!< pointer to hash context structure used by isr */
static hashcrypt_hash_ctx_t *s_ctx;

/*!< macro for checking build time condition. It is used to assure the hashcrypt_sha_ctx_internal_t can fit into
 * hashcrypt_hash_ctx_t */
#define BUILD_ASSERT(condition, msg) extern int msg[1 - 2 * (!(condition))] __attribute__((unused))

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Swap bytes withing 32-bit word.
 *
 * This function changes endianess of a 32-bit word.
 *
 * @param in 32-bit unsigned integer
 * @return 32-bit unsigned integer with different endianess (big endian to little endian and vice versa).
 */

#define swap_bytes(in) __REV(in)

/*!
 * @brief Increment a 16 byte integer.
 *
 * This function increments by one a 16 byte integer.
 *
 * @param input Pointer to a 16 byte integer to be incremented by one.
 */
static void ctrIncrement(uint8_t *input)
{
    int i = 15;
    while (input[i] == (uint8_t)0xFFu)
    {
        input[i] = (uint8_t)0x00u;
        i--;
        if (i < 0)
        {
            return;
        }
    }

    if (i >= 0)
    {
        input[i] += (uint8_t)1u;
    }
}

/*!
 * @brief Reads an unaligned word.
 *
 * This function creates a 32-bit word from an input array of four bytes.
 *
 * @param src Input array of four bytes. The array can start at any address in memory.
 * @return 32-bit unsigned int created from the input byte array.
 */

/* Force lower optimization for Keil, otherwise it replaces inline LDR with LDM */
#if defined(__CC_ARM)
#pragma push
#pragma O0
#endif

static inline uint32_t hashcrypt_get_word_from_unaligned(const uint8_t *srcAddr)
{
#if (!(defined(__CORTEX_M)) || (defined(__CORTEX_M) && (__CORTEX_M == 0)))
    register const uint8_t *src = srcAddr;
    /* Cortex M0 does not support misaligned loads */
    if (0U != ((uint32_t)src & 0x3u))
    {
        union _align_bytes_t
        {
            uint32_t word;
            uint8_t byte[sizeof(uint32_t)];
        } my_bytes;

        my_bytes.byte[0] = *src;
        my_bytes.byte[1] = src[1];
        my_bytes.byte[2] = src[2];
        my_bytes.byte[3] = src[3];
        return my_bytes.word;
    }
    else
    {
        /* addr aligned to 0-modulo-4 so it is safe to type cast */
        return *((const uint32_t *)(uint32_t)src);
    }
#elif defined(__CC_ARM)
    /* -O3 optimization in Keil 5.15 and 5.16a uses LDM instruction here (LDM r4!, {r0})
     *    which is wrong, because srcAddr might be unaligned.
     *    LDM on unaligned address causes hard-fault. in contrary,
     *    LDR supports unaligned address on Cortex M4 */

    register uint32_t retVal;
    __asm
    {
        LDR retVal, [srcAddr]
    }
    return retVal;
#else
    return *((const uint32_t *)srcAddr);
#endif
}

/* End lower optimization */
#if defined(__CC_ARM)
#pragma pop
#endif

static status_t hashcrypt_get_key_from_unaligned_src(uint8_t *dest, const uint8_t *src, size_t size)
{
    status_t retVal = kStatus_InvalidArgument;
    uint32_t i;

    /* destination is SDK driver internal workspace and it must be aligned */
    assert(0x0 == ((uint32_t)dest & 0x1u));
    if ((uint32_t)dest & 0x1u)
    {
        return retVal;
    }

    for (i = 0; i < ((uint32_t)size / 4u); i++)
    {
        ((uint32_t *)dest)[i] = hashcrypt_get_word_from_unaligned(&src[i * sizeof(uint32_t)]);
    }

    return kStatus_Success;
}

/*!
 * @brief LDM to SHA engine INDATA and ALIAS registers.
 *
 * This function writes 16 words starting from the src address (must be word aligned)
 * to the dst address. Dst address does not increment (destination is peripheral module register INDATA).
 * Src address increments to load 16 consecutive words.
 *
 * @param dst peripheral register address (word aligned)
 * @param src address of the input 512-bit block (16 words) (word aligned)
 *
 */
__STATIC_FORCEINLINE void hashcrypt_sha_ldm_stm_16_words(HASHCRYPT_Type *base, const uint32_t *src)
{
    /*
    typedef struct _one_block
    {
        uint32_t a[8];
    } one_block_t;

    volatile one_block_t *ldst = (void *)(uintptr_t)(&base->INDATA);
    one_block_t *lsrc = (void *)(uintptr_t)src;
    *ldst = lsrc[0];
    *ldst = lsrc[1];
    */
    base->MEMADDR = HASHCRYPT_MEMADDR_BASE(src);
    base->MEMCTRL = HASHCRYPT_MEMCTRL_MASTER(1) | HASHCRYPT_MEMCTRL_COUNT(1);
}

/*!
 * @brief Loads data to Hashcrypt engine INDATA register.
 *
 * This function writes desired number of bytes starting from the src address (must be word aligned)
 * to the dst address. Dst address does not increment (destination is peripheral module register INDATA).
 * Src address increments to load consecutive words.
 *
 * @param dst peripheral register address (word aligned)
 * @param src address of the input block (word aligned)
 * @param size number of bytes to write (word aligned)
 *
 */
__STATIC_INLINE void hashcrypt_load_data(HASHCRYPT_Type *base, const uint32_t *src, size_t size)
{
    if (size >= sizeof(uint32_t))
    {
        base->INDATA = src[0];
        size -= sizeof(uint32_t);
    }

    for (int i = 0; i < size / 4; i++)
    {
        base->ALIAS[i] = src[i + 1];
    }
}

/*!
 * @brief Read OUTDATA registers.
 *
 * This function copies OUTDATA to output buffer.
 *
 * @param base Hachcrypt peripheral base address.
 * @param[out] output Output buffer.
 * @param Number of bytes to copy.
 */
static void hashcrypt_get_data(HASHCRYPT_Type *base, uint32_t *output, size_t outputSize)
{
    uint32_t digest[8];

    while (0 == (base->STATUS & HASHCRYPT_STATUS_DIGEST_AKA_OUTDATA_MASK))
    {
    }

    for (int i = 0; i < 8; i++)
    {
        digest[i] = swap_bytes(base->OUTDATA0[i]);
    }

    if (outputSize > sizeof(digest))
    {
        outputSize = sizeof(digest);
    }
    hashcrypt_memcpy(output, digest, outputSize);
}

/*!
 * @brief Initialize the Hashcrypt engine for new operation.
 *
 * This function sets NEW and MODE fields in Hashcrypt Control register to start new operation.
 *
 * @param base Hashcrypt peripheral base address.
 * @param hashcrypt_algo_t Internal context.
 */
static void hashcrypt_engine_init(HASHCRYPT_Type *base, hashcrypt_algo_t algo)
{
    /* NEW bit must be set before we switch from previous mode otherwise new mode will not work correctly */
    base->CTRL = HASHCRYPT_CTRL_NEW_HASH(1);
    base->CTRL = HASHCRYPT_CTRL_MODE(algo) | HASHCRYPT_CTRL_NEW_HASH(1);
}

/*!
 * @brief Loads user key to INDATA register.
 *
 * This function writes user key stored in handle into HashCrypt INDATA register.
 *
 * @param base Hashcrypt peripheral base address.
 * @param handle Handle used for this request.
 */
static void hashcrypt_aes_load_userKey(HASHCRYPT_Type *base, hashcrypt_handle_t *handle)
{
    size_t keySize = 0;

    switch (handle->keySize)
    {
        case kHASHCRYPT_Aes128:
            keySize = 16;
            break;
        case kHASHCRYPT_Aes192:
            keySize = 24;
            break;
        case kHASHCRYPT_Aes256:
            keySize = 32;
            break;
        default:
            break;
    }
    if (keySize == 0)
    {
        return;
    }
    hashcrypt_load_data(base, &handle->keyWord[0], keySize);
}

/*!
 * @brief Performs AES encryption/decryption of one data block.
 *
 * This function encrypts/decrypts one block of data with specified size.
 *
 * @param base Hashcrypt peripheral base address.
 * @param input input data
 * @param output output data
 * @param size size of data block to process in bytes (must be 16bytes multiple).
 */
static status_t hashcrypt_aes_one_block(HASHCRYPT_Type *base, const uint8_t *input, uint8_t *output, size_t size)
{
    status_t status = kStatus_Fail;
    int idx         = 0;

    /* we use AHB master mode as much as possible */
    /* however, it can work only with aligned input data */
    /* so, if unaligned, we do memcpy to temp buffer on stack, which is aligned, and use AHB mode to read data in */
    /* then we read data back to it and do memcpy to the output buffer */
    if (((uint32_t)input & 0x3u) || ((uint32_t)output & 0x3u))
    {
        uint32_t temp[256 / sizeof(uint32_t)];
        int cnt = 0;
        while (size)
        {
            size_t actSz     = size >= 256u ? 256u : size;
            size_t actSzOrig = actSz;
            memcpy(temp, input + 256 * cnt, actSz);
            size -= actSz;
            base->MEMADDR = HASHCRYPT_MEMADDR_BASE(temp);
            base->MEMCTRL = HASHCRYPT_MEMCTRL_MASTER(1) | HASHCRYPT_MEMCTRL_COUNT(actSz / 16);
            int outidx    = 0;
            while (actSz)
            {
                while (0 == (base->STATUS & HASHCRYPT_STATUS_DIGEST_AKA_OUTDATA_MASK))
                {
                }
                for (int i = 0; i < 4; i++)
                {
                    (temp + outidx)[i] = swap_bytes(base->OUTDATA0[i]);
                }
                outidx += HASHCRYPT_AES_BLOCK_SIZE / 4;
                actSz -= HASHCRYPT_AES_BLOCK_SIZE;
            }
            memcpy(output + 256 * cnt, temp, actSzOrig);
            cnt++;
        }
    }
    else
    {
        base->MEMADDR = HASHCRYPT_MEMADDR_BASE(input);
        base->MEMCTRL = HASHCRYPT_MEMCTRL_MASTER(1) | HASHCRYPT_MEMCTRL_COUNT(size / 16);
        while (size >= HASHCRYPT_AES_BLOCK_SIZE)
        {
            /* Get result */
            while (0 == (base->STATUS & HASHCRYPT_STATUS_DIGEST_AKA_OUTDATA_MASK))
            {
            }

            for (int i = 0; i < 4; i++)
            {
                ((uint32_t *)output + idx)[i] = swap_bytes(base->OUTDATA0[i]);
            }

            idx += HASHCRYPT_AES_BLOCK_SIZE / 4;
            size -= HASHCRYPT_AES_BLOCK_SIZE;
        }
    }

    if (0 == (base->STATUS & HASHCRYPT_STATUS_ERROR_MASK))
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * @brief Check validity of algoritm.
 *
 * This function checks the validity of input argument.
 *
 * @param algo Tested algorithm value.
 * @return kStatus_Success if valid, kStatus_InvalidArgument otherwise.
 */
static status_t hashcrypt_sha_check_input_alg(HASHCRYPT_Type *base, hashcrypt_algo_t algo)
{
    if ((algo == kHASHCRYPT_Sha1) || (algo == kHASHCRYPT_Sha256))
    {
        return kStatus_Success;
    }

    if ((algo == kHASHCRYPT_Sha512) && (base->CONFIG & HASHCRYPT_CONFIG_SHA512_MASK))
    {
        return kStatus_Success;
    }

    return kStatus_InvalidArgument;
}

/*!
 * @brief Check validity of input arguments.
 *
 * This function checks the validity of input arguments.
 *
 * @param base SHA peripheral base address.
 * @param ctx Memory buffer given by user application where the SHA_Init/SHA_Update/SHA_Finish store context.
 * @param algo Tested algorithm value.
 * @return kStatus_Success if valid, kStatus_InvalidArgument otherwise.
 */
static status_t hashcrypt_sha_check_input_args(HASHCRYPT_Type *base, hashcrypt_hash_ctx_t *ctx, hashcrypt_algo_t algo)
{
    /* Check validity of input algorithm */
    if (kStatus_Success != hashcrypt_sha_check_input_alg(base, algo))
    {
        return kStatus_InvalidArgument;
    }

    if ((NULL == ctx) || (NULL == base))
    {
        return kStatus_InvalidArgument;
    }

    return kStatus_Success;
}

/*!
 * @brief Check validity of internal software context.
 *
 * This function checks if the internal context structure looks correct.
 *
 * @param ctxInternal Internal context.
 * @return kStatus_Success if valid, kStatus_InvalidArgument otherwise.
 */
static status_t hashcrypt_sha_check_context(HASHCRYPT_Type *base, hashcrypt_sha_ctx_internal_t *ctxInternal)
{
    if ((NULL == ctxInternal) || (kStatus_Success != hashcrypt_sha_check_input_alg(base, ctxInternal->algo)))
    {
        return kStatus_InvalidArgument;
    }
    return kStatus_Success;
}

/*!
 * @brief Load 512-bit block (16 words) into SHA engine.
 *
 * This function aligns the input block and moves it into SHA engine INDATA.
 * CPU polls the WAITING bit and then moves data by using LDM and STM instructions.
 *
 * @param base SHA peripheral base address.
 * @param blk 512-bit block
 */
static void hashcrypt_sha_one_block(HASHCRYPT_Type *base, const uint8_t *blk)
{
    uint32_t temp[SHA_BLOCK_SIZE / sizeof(uint32_t)];
    const uint32_t *actBlk;

    /* make sure the 512-bit block is word aligned */
    if ((uintptr_t)blk & 0x3u)
    {
        hashcrypt_memcpy(temp, blk, SHA_BLOCK_SIZE);
        actBlk = (const uint32_t *)(uintptr_t)temp;
    }
    else
    {
        actBlk = (const uint32_t *)(uintptr_t)blk;
    }

    /* poll waiting. */
    while (0 == (base->STATUS & HASHCRYPT_STATUS_WAITING_MASK))
    {
    }
    /* feed INDATA (and ALIASes). use STM instruction. */
    hashcrypt_sha_ldm_stm_16_words(base, actBlk);
}

/*!
 * @brief Adds message to current hash.
 *
 * This function merges the message to fill the internal buffer, empties the internal buffer if
 * it becomes full, then process all remaining message data.
 *
 *
 * @param base SHA peripheral base address.
 * @param ctxInternal Internal context.
 * @param message Input message.
 * @param messageSize Size of input message in bytes.
 * @return kStatus_Success.
 */
static status_t hashcrypt_sha_process_message_data(HASHCRYPT_Type *base,
                                                   hashcrypt_sha_ctx_internal_t *ctxInternal,
                                                   const uint8_t *message,
                                                   size_t messageSize)
{
    /* first fill the internal buffer to full block */
    if (ctxInternal->blksz)
    {
        size_t toCopy = SHA_BLOCK_SIZE - ctxInternal->blksz;
        hashcrypt_memcpy(&ctxInternal->blk.b[ctxInternal->blksz], message, toCopy);
        message += toCopy;
        messageSize -= toCopy;

        /* process full internal block */
        hashcrypt_sha_one_block(base, &ctxInternal->blk.b[0]);
    }

    /* process all full blocks in message[] */
    if (messageSize >= SHA_BLOCK_SIZE)
    {
        if ((uintptr_t)message & 0x3u)
        {
            while (messageSize >= SHA_BLOCK_SIZE)
            {
                hashcrypt_sha_one_block(base, message);
                message += SHA_BLOCK_SIZE;
                messageSize -= SHA_BLOCK_SIZE;
            }
        }
        else
        {
            /* poll waiting. */
            while (0 == (base->STATUS & HASHCRYPT_STATUS_WAITING_MASK))
            {
            }
            uint32_t blkNum   = (messageSize >> 6); /* div by 64 bytes */
            uint32_t blkBytes = blkNum * 64u;       /* number of bytes in 64 bytes blocks */
            base->MEMADDR     = HASHCRYPT_MEMADDR_BASE(message);
            base->MEMCTRL     = HASHCRYPT_MEMCTRL_MASTER(1) | HASHCRYPT_MEMCTRL_COUNT(blkNum);
            message += blkBytes;
            messageSize -= blkBytes;
            while (0 == (base->STATUS & HASHCRYPT_STATUS_DIGEST_AKA_OUTDATA_MASK))
            {
            }
        }
    }

    /* copy last incomplete message bytes into internal block */
    hashcrypt_memcpy(&ctxInternal->blk.b[0], message, messageSize);
    ctxInternal->blksz = messageSize;
    return kStatus_Success;
}

/*!
 * @brief Finalize the running hash to make digest.
 *
 * This function empties the internal buffer, adds padding bits, and generates final digest.
 *
 * @param base SHA peripheral base address.
 * @param ctxInternal Internal context.
 * @return kStatus_Success.
 */
static status_t hashcrypt_sha_finalize(HASHCRYPT_Type *base, hashcrypt_sha_ctx_internal_t *ctxInternal)
{
    hashcrypt_sha_block_t lastBlock;

    memset(&lastBlock, 0, sizeof(hashcrypt_sha_block_t));

    /* this is last call, so need to flush buffered message bytes along with padding */
    if (ctxInternal->blksz <= 55u)
    {
        /* last data is 440 bits or less. */
        hashcrypt_memcpy(&lastBlock.b[0], &ctxInternal->blk.b[0], ctxInternal->blksz);
        lastBlock.b[ctxInternal->blksz]     = (uint8_t)0x80U;
        lastBlock.w[SHA_BLOCK_SIZE / 4 - 1] = swap_bytes(8u * ctxInternal->fullMessageSize);
        hashcrypt_sha_one_block(base, &lastBlock.b[0]);
    }
    else
    {
        if (ctxInternal->blksz < SHA_BLOCK_SIZE)
        {
            ctxInternal->blk.b[ctxInternal->blksz] = (uint8_t)0x80U;
            for (uint32_t i = ctxInternal->blksz + 1u; i < SHA_BLOCK_SIZE; i++)
            {
                ctxInternal->blk.b[i] = 0;
            }
        }
        else
        {
            lastBlock.b[0] = (uint8_t)0x80U;
        }

        hashcrypt_sha_one_block(base, &ctxInternal->blk.b[0]);
        lastBlock.w[SHA_BLOCK_SIZE / 4 - 1] = swap_bytes(8u * ctxInternal->fullMessageSize);
        hashcrypt_sha_one_block(base, &lastBlock.b[0]);
    }
    /* poll wait for final digest */
    while (0 == (base->STATUS & HASHCRYPT_STATUS_DIGEST_AKA_OUTDATA_MASK))
    {
    }
    return kStatus_Success;
}

status_t HASHCRYPT_SHA(HASHCRYPT_Type *base,
                       hashcrypt_algo_t algo,
                       const uint8_t *input,
                       size_t inputSize,
                       uint8_t *output,
                       size_t *outputSize)
{
    hashcrypt_hash_ctx_t hashCtx;
    status_t status;

    status = HASHCRYPT_SHA_Init(base, &hashCtx, algo);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = HASHCRYPT_SHA_Update(base, &hashCtx, input, inputSize);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = HASHCRYPT_SHA_Finish(base, &hashCtx, output, outputSize);

    return status;
}

status_t HASHCRYPT_SHA_Init(HASHCRYPT_Type *base, hashcrypt_hash_ctx_t *ctx, hashcrypt_algo_t algo)
{
    status_t status;

    hashcrypt_sha_ctx_internal_t *ctxInternal;
    /* compile time check for the correct structure size */
    BUILD_ASSERT(sizeof(hashcrypt_hash_ctx_t) >= sizeof(hashcrypt_sha_ctx_internal_t), hashcrypt_hash_ctx_t_size);

    status = hashcrypt_sha_check_input_args(base, ctx, algo);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* set algorithm in context struct for later use */
    ctxInternal        = (hashcrypt_sha_ctx_internal_t *)ctx;
    ctxInternal->algo  = algo;
    ctxInternal->blksz = 0u;
#ifdef HASHCRYPT_SHA_DO_WIPE_CONTEXT
    for (int i = 0; i < sizeof(ctxInternal->blk.w) / sizeof(ctxInternal->blk.w[0]); i++)
    {
        ctxInternal->blk.w[i] = 0u;
    }
#endif /* HASHCRYPT_SHA_DO_WIPE_CONTEXT */
    ctxInternal->state           = kHASHCRYPT_HashInit;
    ctxInternal->fullMessageSize = 0;
    return kStatus_Success;
}

status_t HASHCRYPT_SHA_Update(HASHCRYPT_Type *base, hashcrypt_hash_ctx_t *ctx, const uint8_t *input, size_t inputSize)
{
    bool isUpdateState;
    status_t status;
    hashcrypt_sha_ctx_internal_t *ctxInternal;
    size_t blockSize;

    if (inputSize == 0)
    {
        return kStatus_Success;
    }

    ctxInternal = (hashcrypt_sha_ctx_internal_t *)ctx;
#ifdef HASHCRYPT_SHA_DO_CHECK_CONTEXT
    status = hashcrypt_sha_check_context(base, ctxInternal);
    if (kStatus_Success != status)
    {
        return status;
    }
#endif /* HASHCRYPT_SHA_DO_CHECK_CONTEXT */

    ctxInternal->fullMessageSize += inputSize;
    blockSize = SHA_BLOCK_SIZE;
    /* if we are still less than 64 bytes, keep only in context */
    if ((ctxInternal->blksz + inputSize) <= blockSize)
    {
        hashcrypt_memcpy((&ctxInternal->blk.b[0]) + ctxInternal->blksz, input, inputSize);
        ctxInternal->blksz += inputSize;
        return kStatus_Success;
    }
    else
    {
        isUpdateState = ctxInternal->state == kHASHCRYPT_HashUpdate;
        if (!isUpdateState)
        {
            /* start NEW hash */
            hashcrypt_engine_init(base, ctxInternal->algo);
            ctxInternal->state = kHASHCRYPT_HashUpdate;
        }
    }

    /* process message data */
    status = hashcrypt_sha_process_message_data(base, ctxInternal, input, inputSize);
    return status;
}

status_t HASHCRYPT_SHA_Finish(HASHCRYPT_Type *base, hashcrypt_hash_ctx_t *ctx, uint8_t *output, size_t *outputSize)
{
    size_t algOutSize = 0;
    status_t status;
    hashcrypt_sha_ctx_internal_t *ctxInternal;
#ifdef HASHCRYPT_SHA_DO_CHECK_CONTEXT
    uint32_t *ctxW;
    uint32_t i;
#endif /* HASHCRYPT_SHA_DO_CHECK_CONTEXT */

    if (output == NULL)
    {
        return kStatus_InvalidArgument;
    }

    ctxInternal = (hashcrypt_sha_ctx_internal_t *)ctx;
#ifdef HASHCRYPT_SHA_DO_CHECK_CONTEXT
    status = hashcrypt_sha_check_context(base, ctxInternal);
    if (kStatus_Success != status)
    {
        return status;
    }
#endif /* HASHCRYPT_SHA_DO_CHECK_CONTEXT */

    if (ctxInternal->state == kHASHCRYPT_HashInit)
    {
        hashcrypt_engine_init(base, ctxInternal->algo);
    }

    size_t outSize = 0u;

    /* compute algorithm output length */
    switch (ctxInternal->algo)
    {
        case kHASHCRYPT_Sha1:
            outSize = kHASHCRYPT_OutLenSha1;
            break;
        case kHASHCRYPT_Sha256:
            outSize = kHASHCRYPT_OutLenSha256;
            break;
        default:
            break;
    }
    algOutSize = outSize;

    /* flush message last incomplete block, if there is any, and add padding bits */
    status = hashcrypt_sha_finalize(base, ctxInternal);

    if (outputSize)
    {
        if (algOutSize < *outputSize)
        {
            *outputSize = algOutSize;
        }
        else
        {
            algOutSize = *outputSize;
        }
    }

    hashcrypt_get_data(base, (uint32_t *)output, algOutSize);

#ifdef HASHCRYPT_SHA_DO_WIPE_CONTEXT
    ctxW = (uint32_t *)ctx;
    for (i = 0; i < HASHCRYPT_HASH_CTX_SIZE; i++)
    {
        ctxW[i] = 0u;
    }
#endif /* HASHCRYPT_SHA_DO_WIPE_CONTEXT */
    return status;
}

void HASHCRYPT_SHA_SetCallback(HASHCRYPT_Type *base,
                               hashcrypt_hash_ctx_t *ctx,
                               hashcrypt_callback_t callback,
                               void *userData)
{
    hashcrypt_sha_ctx_internal_t *ctxInternal;

    s_ctx                     = ctx;
    ctxInternal               = (hashcrypt_sha_ctx_internal_t *)ctx;
    ctxInternal->hashCallback = callback;
    ctxInternal->userData     = userData;

    EnableIRQ(HASHCRYPT_IRQn);
}

status_t HASHCRYPT_SHA_UpdateNonBlocking(HASHCRYPT_Type *base,
                                         hashcrypt_hash_ctx_t *ctx,
                                         const uint8_t *input,
                                         size_t inputSize)
{
    hashcrypt_sha_ctx_internal_t *ctxInternal;
    uint32_t numBlocks;
    status_t status;

    if (inputSize == 0)
    {
        return kStatus_Success;
    }

    if ((uintptr_t)input & 0x3U)
    {
        return kStatus_Fail;
    }

    ctxInternal = (hashcrypt_sha_ctx_internal_t *)ctx;
    status      = hashcrypt_sha_check_context(base, ctxInternal);
    if (kStatus_Success != status)
    {
        return status;
    }

    ctxInternal->fullMessageSize = inputSize;
    ctxInternal->remainingBlcks  = inputSize / SHA_BLOCK_SIZE;
    ctxInternal->blksz           = inputSize % SHA_BLOCK_SIZE;

    /* copy last incomplete block to context */
    if ((ctxInternal->blksz > 0) && (ctxInternal->blksz <= SHA_BLOCK_SIZE))
    {
        hashcrypt_memcpy((&ctxInternal->blk.b[0]), input + SHA_BLOCK_SIZE * ctxInternal->remainingBlcks,
                         ctxInternal->blksz);
    }

    if (ctxInternal->remainingBlcks >= SHA_MASTER_MAX_BLOCKS)
    {
        numBlocks = SHA_MASTER_MAX_BLOCKS - 1;
    }
    else
    {
        numBlocks = ctxInternal->remainingBlcks;
    }
    /* update remainingBlks so that ISR can run another hash if necessary */
    ctxInternal->remainingBlcks -= numBlocks;

    /* compute hash using AHB Master mode for full blocks */
    if (numBlocks > 0)
    {
        ctxInternal->state = kHASHCRYPT_HashUpdate;
        hashcrypt_engine_init(base, ctxInternal->algo);

        /* Enable digest and error interrupts and start hash */
        base->INTENSET = HASHCRYPT_INTENCLR_DIGEST_MASK | HASHCRYPT_INTENCLR_ERROR_MASK;
        base->MEMADDR  = HASHCRYPT_MEMADDR_BASE(input);
        base->MEMCTRL  = HASHCRYPT_MEMCTRL_MASTER(1) | HASHCRYPT_MEMCTRL_COUNT(numBlocks);
    }
    /* no full blocks, invoke callback directly */
    else
    {
        ctxInternal->hashCallback(HASHCRYPT, ctx, status, ctxInternal->userData);
    }

    return status;
}

status_t HASHCRYPT_AES_SetKey(HASHCRYPT_Type *base, hashcrypt_handle_t *handle, const uint8_t *key, size_t keySize)
{
    status_t retVal = kStatus_InvalidArgument;

    switch (keySize)
    {
        case 16:
            handle->keySize = kHASHCRYPT_Aes128;
            break;
        case 24:
            handle->keySize = kHASHCRYPT_Aes192;
            break;
        case 32:
            handle->keySize = kHASHCRYPT_Aes256;
            break;
        default:
            handle->keySize = kHASHCRYPT_InvalidKey;
            break;
    }

    if (handle->keySize == kHASHCRYPT_InvalidKey)
    {
        return retVal;
    }

    if (handle->keyType == kHASHCRYPT_SecretKey)
    {
        /* for kHASHCRYPT_SecretKey just return Success */
        retVal = kStatus_Success;
    }
    else if (handle->keyType == kHASHCRYPT_UserKey)
    {
        retVal = hashcrypt_get_key_from_unaligned_src((uint8_t *)&handle->keyWord[0], key, keySize);
    }
    else
    {
        retVal = kStatus_InvalidArgument;
    }

    return retVal;
}

status_t HASHCRYPT_AES_EncryptEcb(
    HASHCRYPT_Type *base, hashcrypt_handle_t *handle, const uint8_t *plaintext, uint8_t *ciphertext, size_t size)
{
    status_t status = kStatus_Fail;

    if ((size % 16u) || (handle->keySize == kHASHCRYPT_InvalidKey))
    {
        return kStatus_InvalidArgument;
    }

    uint32_t keyType = (handle->keyType == kHASHCRYPT_UserKey) ? 0 : 1u;
    base->CRYPTCFG   = HASHCRYPT_CRYPTCFG_AESMODE(kHASHCRYPT_AesEcb) | HASHCRYPT_CRYPTCFG_AESDECRYPT(AES_ENCRYPT) |
                     HASHCRYPT_CRYPTCFG_AESSECRET(keyType) | HASHCRYPT_CRYPTCFG_AESKEYSZ(handle->keySize) |
                     HASHCRYPT_CRYPTCFG_MSW1ST_OUT(1) | HASHCRYPT_CRYPTCFG_SWAPKEY(1) | HASHCRYPT_CRYPTCFG_SWAPDAT(1) |
                     HASHCRYPT_CRYPTCFG_MSW1ST(1);

    hashcrypt_engine_init(base, kHASHCRYPT_Aes);

    /* load key if kHASHCRYPT_UserKey is selected */
    if (handle->keyType == kHASHCRYPT_UserKey)
    {
        hashcrypt_aes_load_userKey(base, handle);
    }

    /* load message and get result */
    status = hashcrypt_aes_one_block(base, plaintext, ciphertext, size);

    return status;
}

status_t HASHCRYPT_AES_DecryptEcb(
    HASHCRYPT_Type *base, hashcrypt_handle_t *handle, const uint8_t *ciphertext, uint8_t *plaintext, size_t size)
{
    status_t status = kStatus_Fail;

    if ((size % 16u) || (handle->keySize == kHASHCRYPT_InvalidKey))
    {
        return kStatus_InvalidArgument;
    }

    uint32_t keyType = (handle->keyType == kHASHCRYPT_UserKey) ? 0 : 1u;
    base->CRYPTCFG   = HASHCRYPT_CRYPTCFG_AESMODE(kHASHCRYPT_AesEcb) | HASHCRYPT_CRYPTCFG_AESDECRYPT(AES_DECRYPT) |
                     HASHCRYPT_CRYPTCFG_AESSECRET(keyType) | HASHCRYPT_CRYPTCFG_AESKEYSZ(handle->keySize) |
                     HASHCRYPT_CRYPTCFG_MSW1ST_OUT(1) | HASHCRYPT_CRYPTCFG_SWAPKEY(1) | HASHCRYPT_CRYPTCFG_SWAPDAT(1) |
                     HASHCRYPT_CRYPTCFG_MSW1ST(1);

    hashcrypt_engine_init(base, kHASHCRYPT_Aes);

    /* load key if kHASHCRYPT_UserKey is selected */
    if (handle->keyType == kHASHCRYPT_UserKey)
    {
        hashcrypt_aes_load_userKey(base, handle);
    }

    /* load message and get result */
    status = hashcrypt_aes_one_block(base, ciphertext, plaintext, size);

    return status;
}

status_t HASHCRYPT_AES_EncryptCbc(HASHCRYPT_Type *base,
                                  hashcrypt_handle_t *handle,
                                  const uint8_t *plaintext,
                                  uint8_t *ciphertext,
                                  size_t size,
                                  const uint8_t iv[16])
{
    status_t status = kStatus_Fail;

    if ((size % 16u) || (handle->keySize == kHASHCRYPT_InvalidKey))
    {
        return kStatus_InvalidArgument;
    }

    uint32_t keyType = (handle->keyType == kHASHCRYPT_UserKey) ? 0 : 1u;
    base->CRYPTCFG   = HASHCRYPT_CRYPTCFG_AESMODE(kHASHCRYPT_AesCbc) | HASHCRYPT_CRYPTCFG_AESDECRYPT(AES_ENCRYPT) |
                     HASHCRYPT_CRYPTCFG_AESSECRET(keyType) | HASHCRYPT_CRYPTCFG_AESKEYSZ(handle->keySize) |
                     HASHCRYPT_CRYPTCFG_MSW1ST_OUT(1) | HASHCRYPT_CRYPTCFG_SWAPKEY(1) | HASHCRYPT_CRYPTCFG_SWAPDAT(1) |
                     HASHCRYPT_CRYPTCFG_MSW1ST(1);

    hashcrypt_engine_init(base, kHASHCRYPT_Aes);

    /* load key if kHASHCRYPT_UserKey is selected */
    if (handle->keyType == kHASHCRYPT_UserKey)
    {
        hashcrypt_aes_load_userKey(base, handle);
    }

    /* load 16b iv */
    hashcrypt_load_data(base, (uint32_t *)iv, 16);

    /* load message and get result */
    status = hashcrypt_aes_one_block(base, plaintext, ciphertext, size);

    return status;
}

status_t HASHCRYPT_AES_DecryptCbc(HASHCRYPT_Type *base,
                                  hashcrypt_handle_t *handle,
                                  const uint8_t *ciphertext,
                                  uint8_t *plaintext,
                                  size_t size,
                                  const uint8_t iv[16])
{
    status_t status = kStatus_Fail;

    if ((size % 16u) || (handle->keySize == kHASHCRYPT_InvalidKey))
    {
        return kStatus_InvalidArgument;
    }

    uint32_t keyType = (handle->keyType == kHASHCRYPT_UserKey) ? 0 : 1u;
    base->CRYPTCFG   = HASHCRYPT_CRYPTCFG_AESMODE(kHASHCRYPT_AesCbc) | HASHCRYPT_CRYPTCFG_AESDECRYPT(AES_DECRYPT) |
                     HASHCRYPT_CRYPTCFG_AESSECRET(keyType) | HASHCRYPT_CRYPTCFG_AESKEYSZ(handle->keySize) |
                     HASHCRYPT_CRYPTCFG_MSW1ST_OUT(1) | HASHCRYPT_CRYPTCFG_SWAPKEY(1) | HASHCRYPT_CRYPTCFG_SWAPDAT(1) |
                     HASHCRYPT_CRYPTCFG_MSW1ST(1);

    hashcrypt_engine_init(base, kHASHCRYPT_Aes);

    /* load key if kHASHCRYPT_UserKey is selected */
    if (handle->keyType == kHASHCRYPT_UserKey)
    {
        hashcrypt_aes_load_userKey(base, handle);
    }

    /* load iv */
    hashcrypt_load_data(base, (uint32_t *)iv, 16);

    /* load message and get result */
    status = hashcrypt_aes_one_block(base, ciphertext, plaintext, size);

    return status;
}

status_t HASHCRYPT_AES_CryptCtr(HASHCRYPT_Type *base,
                                hashcrypt_handle_t *handle,
                                const uint8_t *input,
                                uint8_t *output,
                                size_t size,
                                uint8_t counter[HASHCRYPT_AES_BLOCK_SIZE],
                                uint8_t counterlast[HASHCRYPT_AES_BLOCK_SIZE],
                                size_t *szLeft)
{
    uint32_t lastSize;
    uint8_t lastBlock[HASHCRYPT_AES_BLOCK_SIZE] = {0};
    uint8_t *lastEncryptedCounter;
    status_t status = kStatus_Fail;

    if (handle->keySize == kHASHCRYPT_InvalidKey)
    {
        return kStatus_InvalidArgument;
    }

    uint32_t keyType = (handle->keyType == kHASHCRYPT_UserKey) ? 0 : 1u;
    base->CRYPTCFG   = HASHCRYPT_CRYPTCFG_AESMODE(kHASHCRYPT_AesCtr) | HASHCRYPT_CRYPTCFG_AESDECRYPT(AES_ENCRYPT) |
                     HASHCRYPT_CRYPTCFG_AESSECRET(keyType) | HASHCRYPT_CRYPTCFG_AESKEYSZ(handle->keySize) |
                     HASHCRYPT_CRYPTCFG_MSW1ST_OUT(1) | HASHCRYPT_CRYPTCFG_SWAPKEY(1) | HASHCRYPT_CRYPTCFG_SWAPDAT(1) |
                     HASHCRYPT_CRYPTCFG_MSW1ST(1);

    hashcrypt_engine_init(base, kHASHCRYPT_Aes);

    /* load key if kHASHCRYPT_UserKey is selected */
    if (handle->keyType == kHASHCRYPT_UserKey)
    {
        hashcrypt_aes_load_userKey(base, handle);
    }

    /* load nonce */
    hashcrypt_load_data(base, (uint32_t *)counter, 16);

    lastSize = size % HASHCRYPT_AES_BLOCK_SIZE;
    size -= lastSize;

    /* encrypt full 16byte blocks */
    hashcrypt_aes_one_block(base, input, output, size);

    while (size)
    {
        ctrIncrement(counter);
        size -= 16u;
        input += 16;
        output += 16;
    }

    if (lastSize)
    {
        if (counterlast)
        {
            lastEncryptedCounter = counterlast;
        }
        else
        {
            lastEncryptedCounter = lastBlock;
        }

        /* Perform encryption with all zeros to get last counter. XOR with zeros doesn't change. */
        status = hashcrypt_aes_one_block(base, lastBlock, lastEncryptedCounter, HASHCRYPT_AES_BLOCK_SIZE);
        if (status != kStatus_Success)
        {
            return status;
        }
        /* remain output = input XOR counterlast */
        for (uint32_t i = 0; i < lastSize; i++)
        {
            output[i] = input[i] ^ lastEncryptedCounter[i];
        }
        /* Increment counter parameter */
        ctrIncrement(counter);
    }
    else
    {
        lastSize = HASHCRYPT_AES_BLOCK_SIZE;
        /* no remaining bytes in couterlast so clearing it */
        if (counterlast)
        {
            memset(counterlast, 0, HASHCRYPT_AES_BLOCK_SIZE);
        }
    }

    if (szLeft)
    {
        *szLeft = HASHCRYPT_AES_BLOCK_SIZE - lastSize;
    }

    return kStatus_Success;
}

void HASHCRYPT_IRQHandler(void)
{
    hashcrypt_sha_ctx_internal_t *ctxInternal;
    HASHCRYPT_Type *base = HASHCRYPT;
    uint32_t numBlocks;
    status_t status;

    ctxInternal = (hashcrypt_sha_ctx_internal_t *)s_ctx;

    if (0 == (base->STATUS & HASHCRYPT_STATUS_ERROR_MASK))
    {
        if (ctxInternal->remainingBlcks > 0)
        {
            if (ctxInternal->remainingBlcks >= SHA_MASTER_MAX_BLOCKS)
            {
                numBlocks = SHA_MASTER_MAX_BLOCKS - 1;
            }
            else
            {
                numBlocks = ctxInternal->remainingBlcks;
            }
            /* some blocks still remaining, update remainingBlcks for next ISR and start another hash */
            ctxInternal->remainingBlcks -= numBlocks;
            base->MEMCTRL = HASHCRYPT_MEMCTRL_MASTER(1) | HASHCRYPT_MEMCTRL_COUNT(numBlocks);
            return;
        }
        /* no full blocks left, disable interrupts and AHB master mode */
        base->INTENCLR = HASHCRYPT_INTENCLR_DIGEST_MASK | HASHCRYPT_INTENCLR_ERROR_MASK;
        base->MEMCTRL  = HASHCRYPT_MEMCTRL_MASTER(0);
        status         = kStatus_Success;
    }
    else
    {
        status = kStatus_Fail;
    }

    /* Invoke callback if there is one */
    if (NULL != ctxInternal->hashCallback)
    {
        ctxInternal->hashCallback(HASHCRYPT, s_ctx, status, ctxInternal->userData);
    }
}

void HASHCRYPT_Init(HASHCRYPT_Type *base)
{
    RESET_PeripheralReset(kHASHCRYPT_RST_SHIFT_RSTn);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_HashCrypt);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void HASHCRYPT_Deinit(HASHCRYPT_Type *base)
{
    RESET_SetPeripheralReset(kHASHCRYPT_RST_SHIFT_RSTn);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(kCLOCK_HashCrypt);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
