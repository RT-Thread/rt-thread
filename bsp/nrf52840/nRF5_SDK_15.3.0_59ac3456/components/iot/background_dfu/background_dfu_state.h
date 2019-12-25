/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
 * @defgroup background_dfu_state background_dfu_state.h
 * @{
 * @ingroup background_dfu
 * @brief Background DFU state management.
 *
 */

#ifndef BACKGROUND_DFU_STATE_H_
#define BACKGROUND_DFU_STATE_H_

#include <stdint.h>
#include <stdbool.h>

#include "background_dfu_block.h"
#include "nrf_dfu_req_handler.h"

/** @brief DFU client state ID.
 *
 * We reuse DFU object type IDs as DFU process states IDs,
 * so that current state can be used as the object type in
 * function which expect one.
 */
typedef enum
{
    BACKGROUND_DFU_DOWNLOAD_INIT_CMD = NRF_DFU_OBJ_TYPE_COMMAND,
    BACKGROUND_DFU_DOWNLOAD_FIRMWARE = NRF_DFU_OBJ_TYPE_DATA,
    BACKGROUND_DFU_DOWNLOAD_TRIG,
    BACKGROUND_DFU_WAIT_FOR_RESET,
    BACKGROUND_DFU_IDLE,
    BACKGROUND_DFU_ERROR,
} background_dfu_state_t;

/** @brief DFU event definitions. */
typedef enum
{
    BACKGROUND_DFU_EVENT_TRANSFER_COMPLETE,
    BACKGROUND_DFU_EVENT_TRANSFER_CONTINUE,
    BACKGROUND_DFU_EVENT_TRANSFER_ERROR,
    BACKGROUND_DFU_EVENT_PROCESSING_ERROR,
} background_dfu_event_t;

/** @brief DFU mode definitions. */
typedef enum
{
    BACKGROUND_DFU_MODE_UNICAST,
    BACKGROUND_DFU_MODE_MULTICAST
} background_dfu_mode_t;

/** @brief Trigger packet structure. */
typedef PACKED_STRUCT 
{
    uint8_t  flags;         /**< Trigger message flags. Bits 7:4 (oldest) - trigger version, bit 3 - DFU mode, bits 2:0 - reserved. */
    uint32_t init_length;
    uint32_t init_crc;
    uint32_t image_length;
    uint32_t image_crc;
} background_dfu_trigger_t;

/**@brief Structure with DFU diagnostic information. */
typedef PACKED_STRUCT background_dfu_diagnostic
{
    uint32_t build_id;                      /**< Build identifier, based on compilation time. */
    uint8_t  state;                         /**< Current DFU state. */
    uint8_t  prev_state;                    /**< Previous DFU state. */
    uint16_t init_blocks_requested;         /**< Number of requested missing init blocks. */
    uint16_t image_blocks_requested;        /**< Number of requested missing image blocks. */
    uint16_t triggers_received;             /**< Number of triggers received. */
    uint16_t total_init_blocks_received;    /**< Total number of init blocks received, including retransmitted ones. */
    uint16_t total_image_blocks_received;   /**< Total number of image blocks received, including retransmitted ones. */
} background_dfu_diagnostic_t;

/** @brief DFU client state. */
typedef struct dfu_context
{
    background_dfu_state_t         dfu_state;       /**< Current DFU client state. */
    background_dfu_mode_t          dfu_mode;        /**< Current DFU mode. */
    bool                           reset_suppress;  /**< If set then device won't automatically reset after
                                                         downloading firmware. */
    background_dfu_diagnostic_t    dfu_diag;        /**< DFU diagnostic information. */

    uint32_t                       init_cmd_size;   /**< Current init command size. */
    uint32_t                       init_cmd_crc;    /**< Current init command checksum. */
    uint32_t                       firmware_size;   /**< Current firmware command size. */
    uint32_t                       firmware_crc;    /**< Current firmware command checksum. */
    uint32_t                       max_obj_size;    /**< Maximum size of the DFU object. */
    uint32_t                       remaining_size;  /**< Remaining size, in bytes, of the resource which
                                                         is being downloaded. */
    /* TODO Move the block num to the block manager. */
    uint32_t                       block_num;       /**< Currently requested block number. */
    uint32_t      *                p_resource_size; /**< Downloaded resource size. */
    background_dfu_block_manager_t block_manager;   /**< An entity managing block reception and storage. */
    uint8_t                        retry_count;     /**< Number of remaining retires. */
} background_dfu_context_t;

/**@brief Check if payload contains valid trigger.
 *
 * @param[inout] p_dfu_ctx   DFU context.
 * @param[in]    p_payload   A pointer to the message payload.
 * @param[in[    payload_len Payload length.
 *
 * @return True if trigger was valid, false otherwise.
 */
bool background_dfu_validate_trigger(background_dfu_context_t * p_dfu_ctx,
                                     const uint8_t            * p_payload,
                                     uint32_t                   payload_len);

/**@brief Process a payload with a DFU trigger.
 *
 * @param[inout] p_dfu_ctx   DFU context.
 * @param[in]    p_payload   A pointer to the message payload.
 * @param[in[    payload_len Payload length.
 *
 * @return True if trigger was successfully processed, false otherwise.
 */
bool background_dfu_process_trigger(background_dfu_context_t * p_dfu_ctx,
                                    const uint8_t            * p_payload,
                                    uint32_t                   payload_len);

/**@brief Process the block and return CoAP result code corresponding to the result of operation.
 *
 * @param[inout] p_dfu_ctx DFU context.
 * @param[in]    p_block   A pointer to the block structure.
 *
 * @return True if init command is valid, false otherwise.
 *
 * @retval BACKGROUND_DFU_BLOCK_SUCCESS        The block was processed correctly.
 * @retval BACKGROUND_DFU_BLOCK_IGNORE         The block was incorrect for this node, but did not
 *                                             indicate that the DFU shall be stopped.
 * @retval BACKGROUND_DFU_BLOCK_INVALID        The block indicated that the node would not catch-up with the DFU
 *                                             transfer or other error occured. Node aborted DFU.
 * @retval BACKGROUND_DFU_BLOCK_STORE_ERROR    DFU store error.
 */
background_dfu_block_result_t background_dfu_process_block(background_dfu_context_t     * p_dfu_ctx,
                                                           const background_dfu_block_t * p_block);

/**@brief DFU state machine handler.
 *
 * @param[in] p_dfu_ctx DFU context.
 * @param[in] event     DFU event.
 *
 * @return NRF_SUCCESS or error code
 */
uint32_t background_dfu_handle_event(background_dfu_context_t * p_dfu_ctx,
                                     background_dfu_event_t     event);

/**@brief Reset state machine state.
 *
 * @param[in] p_dfu_ctx A pointer to DFU client context.
 */
void background_dfu_reset_state(background_dfu_context_t * p_dfu_ctx);

/**@brief Initialize state machine state.
 *
 * @param[in] p_dfu_ctx A pointer to DFU client context.
 */
void background_dfu_state_init(background_dfu_context_t * p_dfu_ctx);

/**@brief Convert a DFU event enum value to a string description.
 *
 * @param[in] event A DFU event.
 *
 * @return String representing the event.
 */
const char * background_dfu_event_to_string(const background_dfu_event_t event);

/**@brief Convert a DFU state enum value to a string description.
 *
 * @param[in] event A DFU state.
 *
 * @return String representing the state.
 */
const char * background_dfu_state_to_string(const background_dfu_state_t state);

#endif /* BACKGROUND_DFU_STATE_H_ */
