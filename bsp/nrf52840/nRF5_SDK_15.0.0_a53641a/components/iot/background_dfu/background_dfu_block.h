/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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

/** @file
 *
 * @defgroup background_dfu_block background_dfu_block.H
 * @{
 * @ingroup background_dfu
 * @brief Background DFU block handling.
 *
 */

#ifndef BACKGROUND_DFU_BLOCK_H_
#define BACKGROUND_DFU_BLOCK_H_

#include <stdint.h>
#include <stdbool.h>

#include "app_util_platform.h"
#include "sdk_config.h"

/** @brief Macro for calculating the number of blocks that fits in particular size. */
#define BLOCKS_PER_SIZE(SIZE)   ((SIZE + DEFAULT_BLOCK_SIZE - 1) / DEFAULT_BLOCK_SIZE)

/** @brief Default block size for background DFU blocks. */
#define DEFAULT_BLOCK_SIZE      BACKGROUND_DFU_DEFAULT_BLOCK_SIZE

/** @brief Number of blocks in superblock. */
#define BLOCKS_PER_BUFFER       BACKGROUND_DFU_BLOCKS_PER_BUFFER

/** @brief Size of the block buffer. Shall be a multiply of @ref DEFAULT_BLOCK_SIZE. */
#define BLOCK_BUFFER_SIZE       (BLOCKS_PER_BUFFER * DEFAULT_BLOCK_SIZE)

/** @brief Size of the bitmap reflecting the state of the blocks in a superblock. */
#define BITMAP_SIZE             ((BLOCKS_PER_BUFFER + 7) / 8)

/** @brief Default size of DFU object. Shall be a multiply of @ref DEFAULT_BLOCK_SIZE. */
#define DEFAULT_DFU_OBJECT_SIZE 4096

/** @brief Number of blocks in DFU object. */
#define BLOCKS_PER_DFU_OBJECT   (BLOCKS_PER_SIZE(DEFAULT_DFU_OBJECT_SIZE))

/** @brief Value of invalid block number (for example to indicate that no block is being stored). */
#define INVALID_BLOCK_NUMBER    (-1)

/** @brief Result of a DFU block operation. */
typedef enum
{
    BACKGROUND_DFU_BLOCK_SUCCESS,       /**< Block operation completed successfully. */
    BACKGROUND_DFU_BLOCK_IGNORE,        /**< Block was ignored in current DFU context (i.e. duplicated block). */
    BACKGROUND_DFU_BLOCK_INVALID,       /**< Block is invalid in current context, indicates that DFU shall be aborted. */
    BACKGROUND_DFU_BLOCK_STORE_ERROR    /**< Block was not stored due to internal store error. */
} background_dfu_block_result_t;

/**@brief A function that module can register to receive block manager error notifications. */
typedef void (* block_manager_result_notify_t)(background_dfu_block_result_t result,
                                               void                        * p_context);

/**@brief Block information structure. */
typedef struct
{
    uint16_t  size;                     /**< Size of the block in bytes. */
    uint32_t  number;                   /**< Block number. */
    uint8_t * p_payload;                /**< Block payload. */
} background_dfu_block_t;

/**@brief Block manager structure.
 *
 * Block manager keeps track of received blocks, ensuring that they are written into flash in
 * a correct order, and updates the missing blocks bitmap, so that they could be requested from
 * the server.
 */
typedef struct
{
    uint32_t                      image_size;                /**< Size of currently stored image. */
    uint32_t                      image_type;                /**< Image type (init command or firmware). */
    int32_t                       last_block_stored;         /**< Number of the last block written in the flash. */
    int32_t                       current_block;             /**< Last received (or expected) block. */
    uint8_t                       data[BLOCK_BUFFER_SIZE];   /**< Block buffer. */
    uint8_t                       bitmap[BITMAP_SIZE];       /**< A bitmap indicating which blocks have been received. */
    block_manager_result_notify_t result_handler;            /**< A callback function for error notification. */
    void                        * p_context;                 /**< A context for result notification.*/
    int32_t                       currently_stored_block;    /**< Number of block that is currently being stored. */
} background_dfu_block_manager_t;

/**@brief Bitmap structure used in bitmap requests. */
typedef struct
{
    uint16_t size;                      /**< Size of the bitmap, in bytes.*/
    uint16_t offset;                    /**< Bitmap offset, indicating which block is referenced by first bit in bitmap. */
    uint8_t  bitmap[BITMAP_SIZE];       /**< Bitmap itself. One in specific bit indicates which block is missing. */
} background_dfu_request_bitmap_t;

/**@brief Initialize block manager.
 *
 * @param[inout] p_bm          A pointer to the block manager.
 * @param[in]    object_type   Type of the image to store.
 * @param[in]    object_size   Size of the image to store.
 * @param[in]    initial_block Number of the first block to receive. Typically it would be 0, but
 *                             in case DFU restarted in the middle, it may differ.
 * @param[in]    error_handler A callback for error notification.
 * @param[in]    p_context     A context for error notification.
 */
void block_manager_init(background_dfu_block_manager_t * p_bm,
                        uint32_t                         object_type,
                        uint32_t                         object_size,
                        int32_t                          initial_block,
                        block_manager_result_notify_t    result_handler,
                        void                           * p_context);

/**@brief Process a single block.
 *
 * @param[inout] p_bm      A pointer to the block manager.
 * @param[in]    p_block   A pointer to the block structure containing information about the block.
 *
 * @retval BACKGROUND_DFU_BLOCK_SUCCESS     Block stored successfully.
 * @retval BACKGROUND_DFU_BLOCK_IGNORE      Invalid block size or block already stored in flash.
 * @retval BACKGROUND_DFU_BLOCK_INVALID     Block number indicates that too many blocks were missed.
 * @retval BACKGROUND_DFU_BLOCK_STORE_ERROR Block store in flash failed.
 */
background_dfu_block_result_t block_manager_block_process(background_dfu_block_manager_t * p_bm,
                                                          const background_dfu_block_t   * p_block);

/**@brief Check if an image managed by a block manager is complete.
 *
 * @param[in] p_bm A pointer to the block manager.
 *
 * @return True if image is complete, false otherwise.
 */
bool block_manager_is_image_complete(const background_dfu_block_manager_t * p_bm);

/**@brief Get current block bitmap.
 *
 * @param[in]  p_bm      A pointer to the block manager.
 * @param[out] p_req_bmp A pointer to the block bitmap structure.
 *
 * @return True if non-empty bitmap was generated, false otherwise.
 */
bool block_manager_request_bitmap_get(const background_dfu_block_manager_t * p_bm,
                                      background_dfu_request_bitmap_t      * p_req_bmp);

/**@brief Increment current block, in case no blocks were received and block timeout shot.
 *
 * @param[in]  p_bm      A pointer to the block manager.
 *
 * @return True if block was incremented, false if block manager is already on a last block of the image.
 */
bool block_manager_increment_current_block(background_dfu_block_manager_t * p_bm);

/**@brief Get current block number that block manager received/expects.
 *
 * @param[in]  p_bm      A pointer to the block manager.
 *
 * @return Current block number.
 */
int32_t block_manager_get_current_block(const background_dfu_block_manager_t * p_bm);

#endif /* BACKGROUND_DFU_BLOCK_H_ */

/** @} */
