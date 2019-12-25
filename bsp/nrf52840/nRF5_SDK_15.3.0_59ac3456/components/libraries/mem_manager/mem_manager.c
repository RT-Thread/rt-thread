/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(MEM_MANAGER)
#include "mem_manager.h"
#include "nrf_assert.h"

#define NRF_LOG_MODULE_NAME mem_mngr

#if MEM_MANAGER_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       MEM_MANAGER_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  MEM_MANAGER_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR MEM_MANAGER_CONFIG_DEBUG_COLOR
#else //MEM_MANAGER_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //MEM_MANAGER_CONFIG_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**
 * @defgroup memory_manager_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently the SDK does not use mutexes but
 *          framework is provided in case need arises to use an alternative architecture.
 * @{
 */
#define MM_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_mm_mutex)                                                /**< Lock module using mutex. */
#define MM_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_mm_mutex)                                              /**< Unlock module using mutex. */
/** @} */

#undef NULL_PARAM_CHECK
#undef NULL_PARAM_CHECK_VOID
#undef VERIFY_MODULE_INITIALIZED
#undef VERIFY_MODULE_INITIALIZED_VOID
#undef VERIFY_REQUESTED_SIZE
#undef VERIFY_REQUESTED_SIZE_VOID

#if (MEM_MANAGER_DISABLE_API_PARAM_CHECK == 0)

/**
 * @brief Macro for verifying NULL parameters.
 *        Returning with an appropriate error code on failure.
 *
 * @param[in] PARAM Parameter checked for NULL.
 *
 * @retval (NRF_ERROR_NULL | NRF_ERROR_MEMORY_MANAGER_ERR_BASE) when @ref PARAM is NULL.
 */
#define NULL_PARAM_CHECK(PARAM)                            \
    if ((PARAM) == NULL)                                   \
    {                                                      \
        return (NRF_ERROR_NULL | NRF_ERROR_MEMORY_MANAGER_ERR_BASE); \
    }

/**
 * @brief Macro for verifying NULL parameters are not passed to API and returning on failure.
 *
 * @param[in] PARAM Parameter checked for NULL.
 */
#define NULL_PARAM_CHECK_VOID(PARAM)                       \
    if ((PARAM) == NULL)                                   \
    {                                                      \
        return;                                            \
    }


/**
 * @brief Macro for verifying module's initialization status.
 *        Returning with an appropriate error code on failure.
 *
 * @retval (NRF_ERROR_INVALID_STATE | NRF_ERROR_MEMORY_MANAGER_ERR_BASE) module is uninitialized.
 */
#define VERIFY_MODULE_INITIALIZED()                                     \
    do                                                                  \
    {                                                                   \
        if (!m_module_initialized)                                      \
        {                                                               \
            return (NRF_ERROR_INVALID_STATE | NRF_ERROR_MEMORY_MANAGER_ERR_BASE); \
        }                                                               \
    } while (0)

/**
 * @brief Macro for verifying module's initialization status and returning on failure.
 */
#define VERIFY_MODULE_INITIALIZED_VOID()                                \
    do                                                                  \
    {                                                                   \
        if (!m_module_initialized)                                      \
        {                                                               \
            return;                                                     \
        }                                                               \
    } while (0)


/**
 * @brief Macro for verifying requested size of memory does not exceed maximum block
 *       size supported by the module. Returning with appropriate error code on failure.
 *
 * @param[in] SIZE Requested size to be allocated.
 *
 * @retval (NRF_ERROR_INVALID_PARAM | NRF_ERROR_MEMORY_MANAGER_ERR_BASE) if requested size is greater
 *         than the largest block size managed by the module.
 */
#define VERIFY_REQUESTED_SIZE(SIZE)                                     \
    do                                                                  \
    {                                                                   \
        if (((SIZE) == 0) ||((SIZE) >  MAX_MEM_SIZE))                   \
        {                                                               \
            return (NRF_ERROR_INVALID_PARAM | NRF_ERROR_MEMORY_MANAGER_ERR_BASE); \
        }                                                               \
    } while (0)


/**
 * @brief Macro for verifying requested size of memory does not exceed maximum block
 *       size supported by the module. Returns on failure.
 *
 * @param[in] SIZE Requested size to be allocated.
 */
#define VERIFY_REQUESTED_SIZE_VOID(SIZE)                                \
    do                                                                  \
    {                                                                   \
        if (((SIZE) == 0) ||((SIZE) >  MAX_MEM_SIZE))                   \
        {                                                               \
            return;                                                     \
        }                                                               \
    } while (0)


/**@} */
#else  //MEM_MANAGER_DISABLE_API_PARAM_CHECK

#define NULL_PARAM_CHECK(PARAM)
#define VERIFY_MODULE_INITIALIZED()
#define VERIFY_REQUESTED_SIZE(SIZE)

#endif //MEM_MANAGER_DISABLE_API_PARAM_CHECK


/**@brief Setting defaults in case XXSmall block not used by application. */
#ifndef MEMORY_MANAGER_XXSMALL_BLOCK_COUNT
    #define MEMORY_MANAGER_XXSMALL_BLOCK_COUNT 0
    #define MEMORY_MANAGER_XXSMALL_BLOCK_SIZE  0
    #define XXSMALL_BLOCK_START                0
    #define XXSMALL_BLOCK_END                  0
    #define XXSMALL_MEMORY_START               0
#endif // MEMORY_MANAGER_XXSMALL_BLOCK_SIZE


/**@brief Setting defaults in case XSmall block not used by application. */
#ifndef MEMORY_MANAGER_XSMALL_BLOCK_COUNT
   #define MEMORY_MANAGER_XSMALL_BLOCK_COUNT   0
   #define MEMORY_MANAGER_XSMALL_BLOCK_SIZE    0
   #define XSMALL_BLOCK_START                  0
   #define XSMALL_BLOCK_END                    0
   #define XSMALL_MEMORY_START                 0
#endif // MEMORY_MANAGER_XSMALL_BLOCK_SIZE


/**@brief Setting defaults in case Small block not used by application. */
#ifndef MEMORY_MANAGER_SMALL_BLOCK_COUNT
   #define MEMORY_MANAGER_SMALL_BLOCK_COUNT    0
   #define MEMORY_MANAGER_SMALL_BLOCK_SIZE     0
   #define SMALL_BLOCK_START                   0
   #define SMALL_BLOCK_END                     0
   #define SMALL_MEMORY_START                  0
#endif // MEMORY_MANAGER_SMALL_BLOCK_COUNT


/**@brief Setting defaults in case Medium block not used by application. */
#ifndef MEMORY_MANAGER_MEDIUM_BLOCK_COUNT
   #define MEMORY_MANAGER_MEDIUM_BLOCK_COUNT   0
   #define MEMORY_MANAGER_MEDIUM_BLOCK_SIZE    0
   #define MEDIUM_BLOCK_START                  0
   #define MEDIUM_BLOCK_END                    0
   #define MEDIUM_MEMORY_START                 0
#endif // MEMORY_MANAGER_MEDIUM_BLOCK_COUNT


/**@brief Setting defaults in case Large block not used by application. */
#ifndef MEMORY_MANAGER_LARGE_BLOCK_COUNT
   #define MEMORY_MANAGER_LARGE_BLOCK_COUNT    0
   #define MEMORY_MANAGER_LARGE_BLOCK_SIZE     0
   #define LARGE_BLOCK_START                   0
   #define LARGE_BLOCK_END                     0
   #define LARGE_MEMORY_START                  0
#endif // MEMORY_MANAGER_LARGE_BLOCK_COUNT


/**@brief Setting defaults in case XLarge block not used by application. */
#ifndef MEMORY_MANAGER_XLARGE_BLOCK_COUNT
   #define MEMORY_MANAGER_XLARGE_BLOCK_COUNT   0
   #define MEMORY_MANAGER_XLARGE_BLOCK_SIZE    0
   #define XLARGE_BLOCK_START                  0
   #define XLARGE_BLOCK_END                    0
   #define XLARGE_MEMORY_START                 0
#endif // MEMORY_MANAGER_XLARGE_BLOCK_COUNT


/**@brief Setting defaults in case XXLarge block not used by application. */
#ifndef MEMORY_MANAGER_XXLARGE_BLOCK_COUNT
   #define MEMORY_MANAGER_XXLARGE_BLOCK_COUNT  0
   #define MEMORY_MANAGER_XXLARGE_BLOCK_SIZE   0
   #define XXLARGE_BLOCK_START                 0
   #define XXLARGE_BLOCK_END                   0
   #define XXLARGE_MEMORY_START                0
#endif // MEMORY_MANAGER_XXLARGE_BLOCK_COUNT


/**@brief  Based on which blocks are defined, MAX_MEM_SIZE is determined.
 *
 * @note   Also, in case none of these are defined, a compile time error is indicated.
 */
#if (MEMORY_MANAGER_XXLARGE_BLOCK_COUNT != 0)
    #define MAX_MEM_SIZE MEMORY_MANAGER_XXLARGE_BLOCK_SIZE
#elif (MEMORY_MANAGER_XLARGE_BLOCK_COUNT != 0)
    #define MAX_MEM_SIZE MEMORY_MANAGER_XLARGE_BLOCK_SIZE
#elif (MEMORY_MANAGER_LARGE_BLOCK_COUNT != 0)
    #define MAX_MEM_SIZE MEMORY_MANAGER_LARGE_BLOCK_SIZE
#elif (MEMORY_MANAGER_MEDIUM_BLOCK_COUNT != 0)
    #define MAX_MEM_SIZE MEMORY_MANAGER_MEDIUM_BLOCK_SIZE
#elif (MEMORY_MANAGER_SMALL_BLOCK_COUNT != 0)
    #define MAX_MEM_SIZE MEMORY_MANAGER_SMALL_BLOCK_SIZE
#elif (MEMORY_MANAGER_XSMALL_BLOCK_COUNT != 0)
    #define MAX_MEM_SIZE MEMORY_MANAGER_XSMALL_BLOCK_SIZE
#elif (MEMORY_MANAGER_XXSMALL_BLOCK_COUNT != 0)
    #define MAX_MEM_SIZE MEMORY_MANAGER_XXSMALL_BLOCK_SIZE
#else
    #err "One of MEMORY_MANAGER_SMALL_BLOCK_COUNT, MEMORY_MANAGER_MEDIUM_BLOCK_COUNT or \
         or MEMORY_MANAGER_LARGE_BLOCK_COUNT should be defined."
#endif

/**@brief XXSmall block start index in case XXSmall Block is defined. */
#ifndef XXSMALL_BLOCK_START
#define XXSMALL_BLOCK_START   0
#endif // XXSMALL_BLOCK_START


/**@brief XSmall block start index in case XSmall Block is defined. */
#ifndef XSMALL_BLOCK_START
#define XSMALL_BLOCK_START    (XXSMALL_BLOCK_START + MEMORY_MANAGER_XXSMALL_BLOCK_COUNT)
#endif // XSMALL_BLOCK_START


/**@brief Small block start index in case Small Block is defined. */
#ifndef SMALL_BLOCK_START
#define SMALL_BLOCK_START     (XSMALL_BLOCK_START  + MEMORY_MANAGER_XSMALL_BLOCK_COUNT)
#endif // SMALL_BLOCK_START


/**@brief Medium block start index in case Medium Block is defined. */
#ifndef MEDIUM_BLOCK_START
#define MEDIUM_BLOCK_START    (SMALL_BLOCK_START   + MEMORY_MANAGER_SMALL_BLOCK_COUNT)
#endif // MEDIUM_BLOCK_START


/**@brief Large block start index in case Large Block is defined. */
#ifndef LARGE_BLOCK_START
#define LARGE_BLOCK_START     (MEDIUM_BLOCK_START  + MEMORY_MANAGER_MEDIUM_BLOCK_COUNT)
#endif // LARGE_BLOCK_START


/**@brief XLarge block start index in case XLarge Block is defined. */
#ifndef XLARGE_BLOCK_START
#define XLARGE_BLOCK_START    (LARGE_BLOCK_START   + MEMORY_MANAGER_LARGE_BLOCK_COUNT)
#endif // XLARGE_BLOCK_START

/**@brief XXLarge block start index in case XXLarge Block is defined. */
#ifndef XXLARGE_BLOCK_START
#define XXLARGE_BLOCK_START   (XLARGE_BLOCK_START  + MEMORY_MANAGER_XLARGE_BLOCK_COUNT)
#endif //XXLARGE_BLOCK_START


/**@brief XXSmall block end index in case XXSmall Block is defined. */
#ifndef XXSMALL_BLOCK_END
#define XXSMALL_BLOCK_END   (XXSMALL_BLOCK_START   + MEMORY_MANAGER_XXSMALL_BLOCK_COUNT)
#endif // XXSMALL_BLOCK_END

/**@brief XSmall block end index in case XSmall Block is defined. */
#ifndef XSMALL_BLOCK_END
#define XSMALL_BLOCK_END    (XSMALL_BLOCK_START    + MEMORY_MANAGER_XSMALL_BLOCK_COUNT)
#endif // XSMALL_BLOCK_END


/**@brief Small block end index in case Small Block is defined. */
#ifndef SMALL_BLOCK_END
#define SMALL_BLOCK_END     (SMALL_BLOCK_START     + MEMORY_MANAGER_SMALL_BLOCK_COUNT)
#endif // SMALL_BLOCK_END


/**@brief Medium block end index in case Medium Block is defined. */
#ifndef MEDIUM_BLOCK_END
#define MEDIUM_BLOCK_END    (MEDIUM_BLOCK_START    + MEMORY_MANAGER_MEDIUM_BLOCK_COUNT)
#endif // MEDIUM_BLOCK_END


/**@brief Large block end index in case Large Block is defined. */
#ifndef LARGE_BLOCK_END
#define LARGE_BLOCK_END     (LARGE_BLOCK_START    + MEMORY_MANAGER_LARGE_BLOCK_COUNT)
#endif // LARGE_BLOCK_END


/**@brief XLarge block end index in case XLarge Block is defined. */
#ifndef XLARGE_BLOCK_END
#define XLARGE_BLOCK_END    (XLARGE_BLOCK_START   + MEMORY_MANAGER_XLARGE_BLOCK_COUNT)
#endif // XLARGE_BLOCK_END


/**@brief XXLarge block end index in case XXLarge Block is defined. */
#ifndef XXLARGE_BLOCK_END
#define XXLARGE_BLOCK_END   (XXLARGE_BLOCK_START  + MEMORY_MANAGER_XXLARGE_BLOCK_COUNT)
#endif //XXLARGE_BLOCK_END


#define XXSMALL_MEMORY_SIZE (MEMORY_MANAGER_XXSMALL_BLOCK_COUNT * MEMORY_MANAGER_XXSMALL_BLOCK_SIZE)
#define XSMALL_MEMORY_SIZE  (MEMORY_MANAGER_XSMALL_BLOCK_COUNT  * MEMORY_MANAGER_XSMALL_BLOCK_SIZE)
#define SMALL_MEMORY_SIZE   (MEMORY_MANAGER_SMALL_BLOCK_COUNT   * MEMORY_MANAGER_SMALL_BLOCK_SIZE)
#define MEDIUM_MEMORY_SIZE  (MEMORY_MANAGER_MEDIUM_BLOCK_COUNT  * MEMORY_MANAGER_MEDIUM_BLOCK_SIZE)
#define LARGE_MEMORY_SIZE   (MEMORY_MANAGER_LARGE_BLOCK_COUNT   * MEMORY_MANAGER_LARGE_BLOCK_SIZE)
#define XLARGE_MEMORY_SIZE  (MEMORY_MANAGER_XLARGE_BLOCK_COUNT  * MEMORY_MANAGER_XLARGE_BLOCK_SIZE)
#define XXLARGE_MEMORY_SIZE (MEMORY_MANAGER_XXLARGE_BLOCK_COUNT * MEMORY_MANAGER_XXLARGE_BLOCK_SIZE)


/**@brief XXSmall memory start index in case XXSmall Block is defined. */
#ifndef XXSMALL_MEMORY_START
#define XXSMALL_MEMORY_START  0
#endif // XXSMALL_MEMORY_START


/**@brief XSmall memory start index in case XSmall Block is defined. */
#ifndef XSMALL_MEMORY_START
#define XSMALL_MEMORY_START  (XXSMALL_MEMORY_START + XXSMALL_MEMORY_SIZE)
#endif // XSMALL_MEMORY_START


/**@brief Small memory start index in case Small Block is defined. */
#ifndef SMALL_MEMORY_START
#define SMALL_MEMORY_START  (XSMALL_MEMORY_START + XSMALL_MEMORY_SIZE)
#endif // SMALL_MEMORY_START


/**@brief Medium memory start index in case Medium Block is defined. */
#ifndef MEDIUM_MEMORY_START
#define MEDIUM_MEMORY_START  (SMALL_MEMORY_START + SMALL_MEMORY_SIZE)
#endif // MEDIUM_MEMORY_START


/**@brief Large memory start index in case Large Block is defined. */
#ifndef LARGE_MEMORY_START
#define LARGE_MEMORY_START  (MEDIUM_MEMORY_START + MEDIUM_MEMORY_SIZE)
#endif // LARGE_MEMORY_START


/**@brief XLarge memory start index in case XLarge Block is defined. */
#ifndef XLARGE_MEMORY_START
#define XLARGE_MEMORY_START  (LARGE_MEMORY_START + LARGE_MEMORY_SIZE)
#endif // XLARGE_MEMORY_START


/**@brief XXLarge memory start index in case XXLarge Block is defined. */
#ifndef XXLARGE_MEMORY_START
#define XXLARGE_MEMORY_START  (XLARGE_MEMORY_START + XLARGE_MEMORY_SIZE)
#endif // XLARGE_MEMORY_START


/**@brief Total count of block managed by the module. */
#define TOTAL_BLOCK_COUNT (MEMORY_MANAGER_XXSMALL_BLOCK_COUNT +                                     \
                           MEMORY_MANAGER_XSMALL_BLOCK_COUNT  +                                     \
                           MEMORY_MANAGER_SMALL_BLOCK_COUNT   +                                     \
                           MEMORY_MANAGER_MEDIUM_BLOCK_COUNT  +                                     \
                           MEMORY_MANAGER_LARGE_BLOCK_COUNT   +                                     \
                           MEMORY_MANAGER_XLARGE_BLOCK_COUNT  +                                     \
                           MEMORY_MANAGER_XXLARGE_BLOCK_COUNT)


/**@brief Total memory managed by the module. */
#define TOTAL_MEMORY_SIZE (XXSMALL_MEMORY_SIZE +                                                    \
                           XSMALL_MEMORY_SIZE  +                                                    \
                           SMALL_MEMORY_SIZE   +                                                    \
                           MEDIUM_MEMORY_SIZE  +                                                    \
                           LARGE_MEMORY_SIZE   +                                                    \
                           XLARGE_MEMORY_SIZE  +                                                    \
                           XXLARGE_MEMORY_SIZE)


#define BLOCK_CAT_COUNT                7                                                            /**< Block category count is 7 (xxsmall, xsmall, small, medium, large, xlarge, xxlarge). Having one of the block count to zero has no impact on this count. */
#define BLOCK_CAT_XXS                  0                                                            /**< Extra Extra Small category identifier. */
#define BLOCK_CAT_XS                   1                                                            /**< Extra Small category identifier. */
#define BLOCK_CAT_SMALL                2                                                            /**< Small category identifier. */
#define BLOCK_CAT_MEDIUM               3                                                            /**< Medium category identifier. */
#define BLOCK_CAT_LARGE                4                                                            /**< Large category identifier. */
#define BLOCK_CAT_XL                   5                                                            /**< Extra Large category identifier. */
#define BLOCK_CAT_XXL                  6                                                            /**< Extra Extra Large category identifier. */

#define BITMAP_SIZE                    32                                                           /**< Bitmap size for each word used to contain block information. */
#define BLOCK_BITMAP_ARRAY_SIZE        CEIL_DIV(TOTAL_BLOCK_COUNT, BITMAP_SIZE)                     /**< Determines number of blocks needed for book keeping availability status of all blocks. */


/**@brief Lookup table for maximum memory size per block category. */
static const uint32_t m_block_size[BLOCK_CAT_COUNT] =
{
    MEMORY_MANAGER_XXSMALL_BLOCK_SIZE,
    MEMORY_MANAGER_XSMALL_BLOCK_SIZE,
    MEMORY_MANAGER_SMALL_BLOCK_SIZE,
    MEMORY_MANAGER_MEDIUM_BLOCK_SIZE,
    MEMORY_MANAGER_LARGE_BLOCK_SIZE,
    MEMORY_MANAGER_XLARGE_BLOCK_SIZE,
    MEMORY_MANAGER_XXLARGE_BLOCK_SIZE
};

/**@brief Lookup table for block start index for each block category. */
static const uint32_t m_block_start[BLOCK_CAT_COUNT] =
{
    XXSMALL_BLOCK_START,
    XSMALL_BLOCK_START,
    SMALL_BLOCK_START,
    MEDIUM_BLOCK_START,
    LARGE_BLOCK_START,
    XLARGE_BLOCK_START,
    XXLARGE_BLOCK_START
};

/**@brief Lookup table for last block index for each block category. */
static const uint32_t m_block_end[BLOCK_CAT_COUNT] =
{
    XXSMALL_BLOCK_END,
    XSMALL_BLOCK_END,
    SMALL_BLOCK_END,
    MEDIUM_BLOCK_END,
    LARGE_BLOCK_END,
    XLARGE_BLOCK_END,
    XXLARGE_BLOCK_END
};

/**@brief Lookup table for memory start range for each block category. */
static const uint32_t m_block_mem_start[BLOCK_CAT_COUNT] =
{
    XXSMALL_MEMORY_START,
    XSMALL_MEMORY_START,
    SMALL_MEMORY_START,
    MEDIUM_MEMORY_START,
    LARGE_MEMORY_START,
    XLARGE_MEMORY_START,
    XXLARGE_MEMORY_START
};

static uint8_t  m_memory[TOTAL_MEMORY_SIZE];                                                        /**< Memory managed by the module. */
static uint32_t m_mem_pool[BLOCK_BITMAP_ARRAY_SIZE];                                                /**< Bitmap used for book-keeping availability of all blocks managed by the module.  */

#ifdef MEM_MANAGER_ENABLE_DIAGNOSTICS

/**@brief Lookup table for descriptive strings for each block category. */
static const char * m_block_desc_str[BLOCK_CAT_COUNT] =
{
    "XXSmall",
    "XSmall",
    "Small",
    "Medium",
    "Large",
    "XLarge",
    "XXLarge"
};

/**@brief Table for book keeping smallest size allocated in each block range. */
static uint32_t m_min_size[BLOCK_CAT_COUNT]  =
{
    MEMORY_MANAGER_XXSMALL_BLOCK_SIZE,
    MEMORY_MANAGER_XSMALL_BLOCK_SIZE,
    MEMORY_MANAGER_SMALL_BLOCK_SIZE,
    MEMORY_MANAGER_MEDIUM_BLOCK_SIZE,
    MEMORY_MANAGER_LARGE_BLOCK_SIZE,
    MEMORY_MANAGER_XLARGE_BLOCK_SIZE,
    MEMORY_MANAGER_XXLARGE_BLOCK_SIZE
};

/**@brief Table for book keeping largest size allocated in each block range. */
static uint32_t m_max_size[BLOCK_CAT_COUNT];

/**@brief Global pointing to minimum size holder for block type being allocated. */
static uint32_t * p_min_size;

/**@brief Global pointing to maximum size holder for block type being allocated. */
static uint32_t * p_max_size;

/**@brief Lookup table for count of block available in each block category. */
static uint32_t m_block_count[BLOCK_CAT_COUNT] =
{
    MEMORY_MANAGER_XXSMALL_BLOCK_COUNT,
    MEMORY_MANAGER_XSMALL_BLOCK_COUNT,
    MEMORY_MANAGER_SMALL_BLOCK_COUNT,
    MEMORY_MANAGER_MEDIUM_BLOCK_COUNT,
    MEMORY_MANAGER_LARGE_BLOCK_COUNT,
    MEMORY_MANAGER_XLARGE_BLOCK_COUNT,
    MEMORY_MANAGER_XXLARGE_BLOCK_COUNT
};

#endif // MEM_MANAGER_ENABLE_DIAGNOSTICS

SDK_MUTEX_DEFINE(m_mm_mutex)                                                                        /**< Mutex variable. Currently unused, this declaration does not occupy any space in RAM. */
#if (MEM_MANAGER_DISABLE_API_PARAM_CHECK == 0)
static bool     m_module_initialized = false;                                                       /**< State indicating if module is initialized or not. */
#endif // MEM_MANAGER_DISABLE_API_PARAM_CHECK


/**@brief Function to get X and Y coordinates.
 *
 * @details Function to get X and Y co-ordinates for the block identified by index.
 *          Here, X determines relevant word for the block. Y determines the actual bit in the word.
 *
 * @param[in]  index Identifies the block.
 * @param[out] p_x   Points to the word that contains the bit representing the block.
 * @param[out] p_y   Contains the bitnumber in the the word 'X' relevant to the block.
 */
static __INLINE void get_block_coordinates(uint32_t block_index, uint32_t * p_x, uint32_t * p_y)
{
    // Determine position of the block in the bitmap.
    // X determines relevant word for the block. Y determines the actual bit in the word.
    const uint32_t x = block_index / BITMAP_SIZE;
    const uint32_t y = (block_index - x * BITMAP_SIZE);

    (*p_x) = x;
    (*p_y) = y;
}


/**@brief Initializes the block by setting it to be free. */
static void block_init (uint32_t block_index)
{
    uint32_t x;
    uint32_t y;

    // Determine position of the block in the bitmap.
    // X determines relevant word for the block. Y determines the actual bit in the word.
    get_block_coordinates(block_index, &x, &y);

    // Set bit related to the block to indicate that the block is free.
    SET_BIT(m_mem_pool[x], y);
}


/**@brief Function to get the category of the block of size 'size' or block number 'block_index'.*/
static __INLINE uint32_t get_block_cat(uint32_t size, uint32_t block_index)
{
    for (uint32_t block_cat = 0; block_cat < BLOCK_CAT_COUNT; block_cat++)
    {
        if (((size != 0) && (size <= m_block_size[block_cat]) &&
            (m_block_end[block_cat] != m_block_start[block_cat])) ||
            (block_index < m_block_end[block_cat]))
        {
            return block_cat;
        }
    }

    return 0;
}


/**@brief Function to get the size of the block number 'block_index'. */
static __INLINE uint32_t get_block_size(uint32_t block_index)
{
    const uint32_t block_cat = get_block_cat(0, block_index);

    #ifdef MEM_MANAGER_ENABLE_DIAGNOSTICS
        p_min_size = &m_min_size[block_cat];
        p_max_size = &m_max_size[block_cat];
    #endif // MEM_MANAGER_ENABLE_DIAGNOSTICS

    return m_block_size[block_cat];
}


/**@brief Function to free the block identified by block number 'block_index'. */
static bool is_block_free(uint32_t block_index)
{
    uint32_t x;
    uint32_t y;

    // Determine position of the block in the bitmap.
    // X determines relevant word for the block. Y determines the actual bit in the word.
    get_block_coordinates(block_index, &x, &y);

    return IS_SET(m_mem_pool[x], y);
}


/**@brief Function to allocate the block identified by block number 'block_index'. */
static void block_allocate(uint32_t block_index)
{
    uint32_t x;
    uint32_t y;

    // Determine position of the block in the bitmap.
    // X determines relevant word for the block. Y determines the actual bit in the word.
    get_block_coordinates(block_index, &x, &y);

    CLR_BIT(m_mem_pool[x], y);
}


uint32_t nrf_mem_init(void)
{
    NRF_LOG_DEBUG(">> %s.", (uint32_t)__func__);

    SDK_MUTEX_INIT(m_mm_mutex);

    MM_MUTEX_LOCK();

    uint32_t block_index = 0;

    for (block_index = 0; block_index < TOTAL_BLOCK_COUNT; block_index++)
    {
        block_init(block_index);
    }

#if (MEM_MANAGER_DISABLE_API_PARAM_CHECK == 0)
    m_module_initialized = true;
#endif // MEM_MANAGER_DISABLE_API_PARAM_CHECK

#ifdef MEM_MANAGER_ENABLE_DIAGNOSTICS
    nrf_mem_diagnose();
#endif // MEM_MANAGER_ENABLE_DIAGNOSTICS

    MM_MUTEX_UNLOCK();

    NRF_LOG_DEBUG("<< %s.", (uint32_t)__func__);

    return NRF_SUCCESS;
}


uint32_t nrf_mem_reserve(uint8_t ** pp_buffer, uint32_t * p_size)
{
    VERIFY_MODULE_INITIALIZED();
    NULL_PARAM_CHECK(pp_buffer);
    NULL_PARAM_CHECK(p_size);

    const uint32_t requested_size = (*p_size);

    VERIFY_REQUESTED_SIZE(requested_size);

    NRF_LOG_DEBUG(">> %s, size 0x%04lX.", (uint32_t)__func__, requested_size);

    MM_MUTEX_LOCK();

    const uint32_t block_cat    = get_block_cat(requested_size, TOTAL_BLOCK_COUNT);
    uint32_t       block_index  = m_block_start[block_cat];
    uint32_t       memory_index = m_block_mem_start[block_cat];
    uint32_t       err_code     = (NRF_ERROR_NO_MEM | NRF_ERROR_MEMORY_MANAGER_ERR_BASE);

    NRF_LOG_DEBUG("Start index for the pool = 0x%08lX, total block count 0x%08X",
           block_index,
           TOTAL_BLOCK_COUNT);

    for (; block_index < TOTAL_BLOCK_COUNT; block_index++)
    {
        uint32_t block_size = get_block_size(block_index);

        if (is_block_free(block_index) == true)
        {
            NRF_LOG_DEBUG("Reserving block 0x%08lX", block_index);

            // Search succeeded, found free block.
            err_code     = NRF_SUCCESS;

            // Allocate block.
            block_allocate(block_index);

            (*pp_buffer) = &m_memory[memory_index];
            (*p_size)    = block_size;

            #ifdef MEM_MANAGER_ENABLE_DIAGNOSTICS
                (*p_min_size) = MIN((*p_min_size), requested_size);
                (*p_max_size) = MAX((*p_max_size), requested_size);
            #endif // MEM_MANAGER_ENABLE_DIAGNOSTICS

            break;
        }
        memory_index += block_size;
    }
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_DEBUG("Memory reservation result %d, memory %p, size %d!",
                err_code,
                (uint32_t)(*pp_buffer),
                (*p_size));

        #ifdef MEM_MANAGER_ENABLE_DIAGNOSTICS
        nrf_mem_diagnose();
        #endif // MEM_MANAGER_ENABLE_DIAGNOSTICS
    }

    MM_MUTEX_UNLOCK();

    NRF_LOG_DEBUG("<< %s %p, result 0x%08lX.", (uint32_t)__func__,
                 (uint32_t)(*pp_buffer), err_code);

    return err_code;
}


void * nrf_malloc(uint32_t size)
{
    uint8_t * buffer = NULL;
    uint32_t allocated_size = size;

    uint32_t retval = nrf_mem_reserve(&buffer, &allocated_size);

    if (retval != NRF_SUCCESS)
    {
        buffer = NULL;
    }

    return buffer;
}


void * nrf_calloc(uint32_t count, uint32_t size)
{
    uint8_t * buffer = NULL;
    uint32_t allocated_size = (size * count);

    NRF_LOG_DEBUG("[%s]: Requested size %d, count %d", (uint32_t)__func__, allocated_size, count);

    uint32_t retval = nrf_mem_reserve(&buffer, &allocated_size);
    if (retval == NRF_SUCCESS)
    {
        NRF_LOG_DEBUG("[%s]: buffer %p, total size %d", (uint32_t)__func__, (uint32_t)buffer, allocated_size);
        memset(buffer,0, allocated_size);
    }
    else
    {
        NRF_LOG_DEBUG("[%s]: Failed to allocate memory %d", (uint32_t)__func__, allocated_size);
        buffer = NULL;
    }

    return buffer;
}


void nrf_free(void * p_mem)
{
    VERIFY_MODULE_INITIALIZED_VOID();
    NULL_PARAM_CHECK_VOID(p_mem);

    NRF_LOG_DEBUG(">> %s %p.", (uint32_t)__func__, (uint32_t)p_mem);

    MM_MUTEX_LOCK();

    uint32_t index;
    uint32_t memory_index = 0;

    for (index = 0; index < TOTAL_BLOCK_COUNT; index++)
    {
        if (&m_memory[memory_index] == p_mem)
        {
            // Found a free block of memory, assign.
            NRF_LOG_DEBUG("<< Freeing block %d.", index);
            block_init(index);
            break;
        }
        memory_index += get_block_size(index);
    }

    MM_MUTEX_UNLOCK();

    NRF_LOG_DEBUG("<< %s.", (uint32_t)__func__);
    return;
}


void * nrf_realloc(void * p_mem, uint32_t size)
{
    return p_mem;
}


#ifdef MEM_MANAGER_ENABLE_DIAGNOSTICS

/**@brief Function to format and print information with respect to each block.
 *
 * @details Internal function that formats and prints information related to the block category
 *          identified by 'block_cat'. This function also appends the number of bytes in use to
 *          p_mem_in_use based on current count of block in the category.
 *
 * @param[in]  block_cat    Identifies the category of block.
 * @param[out] p_mem_in_use Updates the memory in use based on count in use.
 */
void print_block_info(uint32_t block_cat, uint32_t * p_mem_in_use)
{
    #define PRINT_COLUMN_WIDTH      13
    #define PRINT_BUFFER_SIZE       80
    #define ASCII_VALUE_FOR_SPACE   32

    char           print_buffer[PRINT_BUFFER_SIZE];
    const uint32_t total_count   = (m_block_start[block_cat] + m_block_count[block_cat]);
    uint32_t       in_use        = 0;
    uint32_t       num_of_blocks = 0;
    uint32_t       index         = m_block_start[block_cat];
    uint32_t       column_number;

    // No statistic provided in case block category is not included.
    if (m_block_count[block_cat] != 0)
    {
        memset(print_buffer, ASCII_VALUE_FOR_SPACE, PRINT_BUFFER_SIZE);

        for (; index < total_count; index++)
        {
            if (is_block_free(index) == false)
            {
                num_of_blocks++;
                in_use += m_block_size[block_cat];
            }
        }

        column_number = 0;
        snprintf(&print_buffer[column_number * PRINT_COLUMN_WIDTH],
                 PRINT_COLUMN_WIDTH,
                 "| %s",
                 m_block_desc_str[block_cat]);

        column_number++;
        snprintf(&print_buffer[column_number * PRINT_COLUMN_WIDTH],
                 PRINT_COLUMN_WIDTH,
                 "| %d",
                 m_block_size[block_cat]);

        column_number++;
        snprintf(&print_buffer[column_number * PRINT_COLUMN_WIDTH],
                 PRINT_COLUMN_WIDTH,
                 "| %d",
                 m_block_count[block_cat]);

        column_number++;
        snprintf(&print_buffer[column_number * PRINT_COLUMN_WIDTH],
                 PRINT_COLUMN_WIDTH,
                 "| %d",
                 num_of_blocks);

        column_number++;
        snprintf(&print_buffer[column_number * PRINT_COLUMN_WIDTH],
                 PRINT_COLUMN_WIDTH,
                 "| %d",
                 m_min_size[block_cat]);

        column_number++;
        snprintf(&print_buffer[column_number * PRINT_COLUMN_WIDTH],
                 PRINT_COLUMN_WIDTH,
                 "| %d",
                 m_max_size[block_cat]);

        column_number++;
        const uint32_t column_end = (column_number * PRINT_COLUMN_WIDTH);

        for (int j = 0; j < column_end; j ++)
        {
            if (print_buffer[j] == 0)
            {
                print_buffer[j] = 0x20;
            }
        }
        snprintf(&print_buffer[column_end], 2, "|");

        NRF_LOG_BYTES_DEBUG(print_buffer, strlen(print_buffer));

        (*p_mem_in_use) += in_use;
    }
}


void nrf_mem_diagnose(void)
{
    uint32_t in_use = 0;

    NRF_LOG_DEBUG("");
    NRF_LOG_DEBUG("+------------+------------+------------+------------+------------+------------+");
    NRF_LOG_DEBUG("| Block      | Size       | Total      | In Use     | Min Alloc  | Max Alloc  |");
    NRF_LOG_DEBUG("+------------+------------+------------+------------+------------+------------+");

    print_block_info(BLOCK_CAT_XXS, &in_use);
    print_block_info(BLOCK_CAT_XS, &in_use);
    print_block_info(BLOCK_CAT_SMALL, &in_use);
    print_block_info(BLOCK_CAT_MEDIUM, &in_use);
    print_block_info(BLOCK_CAT_LARGE, &in_use);
    print_block_info(BLOCK_CAT_XL, &in_use);
    print_block_info(BLOCK_CAT_XXL, &in_use);

    NRF_LOG_DEBUG("+------------+------------+------------+------------+------------+------------+");
    NRF_LOG_DEBUG("| Total      | %d      | %d        | %d",
            TOTAL_MEMORY_SIZE, TOTAL_BLOCK_COUNT,in_use);
    NRF_LOG_DEBUG("+------------+------------+------------+------------+------------+------------+");
}

#endif // MEM_MANAGER_ENABLE_DIAGNOSTICS
/** @} */
#endif //NRF_MODULE_ENABLED(MEM_MANAGER)
