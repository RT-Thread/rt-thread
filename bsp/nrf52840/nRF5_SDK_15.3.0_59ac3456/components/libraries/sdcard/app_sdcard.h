/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
/**@file
 *
 * @defgroup app_sdcard SD card library
 * @{
 * @ingroup app_common
 *
 * @brief Asynchronous Secure Digital card (SDC) and MultiMedia card (MMC) library.
 */


#ifndef APP_SDCARD_H_
#define APP_SDCARD_H_

#include "app_util_platform.h"
#include "sdk_config.h"

#define SDC_SECTOR_SIZE             512     ///< Size of a single SD card block in bytes.

#define APP_SDCARD_CONFIG(MOSI_PIN, MISO_PIN, SCK_PIN, CS_PIN) {    \
            .mosi_pin = MOSI_PIN,                                   \
            .miso_pin = MISO_PIN,                                   \
            .sck_pin  = SCK_PIN,                                    \
            .cs_pin   = CS_PIN                                      \
        }

/**
 * @brief SDC operation result.
 */
typedef enum {
    SDC_SUCCESS = 0,            ///< Operation successful.
    SDC_ERROR_NOT_RESPONDING,   ///< Card is not responding or not present.
    SDC_ERROR_TIMEOUT,          ///< Card response timeout.
    SDC_ERROR_NOT_SUPPORTED,    ///< Operation not supported.
    SDC_ERROR_COMMUNICATION,    ///< Communication error.
    SDC_ERROR_DATA,             ///< Data read/write error.
    SDC_ERROR_INTERNAL,         ///< Internal error.
} sdc_result_t;

/**
 * @brief SDC event type.
 */
typedef enum {
    SDC_EVT_INIT = 0,       ///< Initialization procedure.
    SDC_EVT_READ,           ///< Data read procedure.
    SDC_EVT_WRITE           ///< Data write procedure.
} sdc_evt_type_t;

/**
 * @brief SDC event structure.
 */
typedef struct {
    sdc_evt_type_t type;    ///< Event type.
    sdc_result_t   result;  ///< Operation result.
} sdc_evt_t;

/**
 * @brief SDC type and version.
 */
typedef enum {
    SDC_TYPE_UNKNOWN = 0,   ///< Unknown / uninitialized card.
    SDC_TYPE_MMCV3,         ///< MultiMedia card (MMC) version 3.
    SDC_TYPE_SDV1,          ///< Secure Digital card (SDC) version 1.0.
    SDC_TYPE_SDV2           ///< Secure Digital card (SDC) version 2.0.
} sdc_version_t;

/**
 * @brief SDC type information structure.
 */
typedef struct {
    sdc_version_t version : 3;  ///< Card type and version (SD or MMC).
    uint8_t       sdhc    : 1;  ///< Standard Capacity or High Capacity card.
} sdc_type_t;

/**
 * @brief SDC configuration structure.
 */
typedef struct {
    uint8_t mosi_pin;           ///< Serial data in (MOSI / DI) pin number.
    uint8_t miso_pin;           ///< Serial data out (MISO / DO) pin number.
    uint8_t sck_pin;            ///< Serial clock (SCK) pin number.
    uint8_t cs_pin;             ///< Chip select (CS) pin number.
} app_sdc_config_t;

/**
 * @brief SDC information structure.
 */
typedef struct {
    uint32_t    num_blocks;     ///< Number of available data blocks.
    uint16_t    block_len;      ///< Length (in bytes) of a single data block.
    sdc_type_t  type;           ///< Card type information structure.
} app_sdc_info_t;

/**
 * @brief SDC event handler type.
 */
typedef void (*sdc_event_handler_t)(sdc_evt_t const * p_event);


/**
 * @brief Function for initializing the card.
 *
 * @param[in] p_config          Pointer to the SDC configuration structure.
 * @param[in] event_handler     Pointer to the event handler function.
 *
 * @retval NRF_SUCCESS              If initialization process was started succesfully.
 * @retval NRF_ERROR_INVALID_STATE  If the card is already initialized or the initialization is in progress.
 * @retval NRF_ERROR_INVALID_PARAM  If invalid parameters were specified.
 */
ret_code_t app_sdc_init(app_sdc_config_t const * const p_config, sdc_event_handler_t event_handler);


/**
 * @brief Function for uninitializing the card.
 *
 * @retval NRF_SUCCESS              If card was uninitialized succesfully.
 * @retval NRF_ERROR_INVALID_STATE  If the card is not initialized.
 * @retval NRF_ERROR_BUSY           If there is an operation in progress.
 */
ret_code_t app_sdc_uninit(void);


/**
 * @brief Function for retrieving the card busy state.
 *
 * @retval true             If there is an operation in progress.
 * @retval false            If the card is in idle state.
 */
bool app_sdc_busy_check(void);


/**
 * @brief Function for reading the data blocks from the card.
 *
 * @param[out] p_buf            Pointer to the data buffer. Must not be null.
 * @param[in] block_address     Number of the first block to be read.
 * @param[in] block_count       Number of blocks to read. Must be greater than 0.
 *
 * @retval NRF_SUCCESS              If block read operation was started succesfully.
 * @retval NRF_ERROR_INVALID_STATE  If the card is not initialized.
 * @retval NRF_ERROR_BUSY           If there is already an operation active.
 * @retval NRF_ERROR_INVALID_PARAM  If invalid parameters were specified.
 */
ret_code_t app_sdc_block_read(uint8_t * p_buf, uint32_t block_address, uint16_t block_count);


/**
 * @brief Function for writing the data blocks to the card.
 *
 * @param[out] p_buf            Pointer to the data to be written. Must not be null.
 * @param[in] block_address     Number of the first block to write.
 * @param[in] block_count       Number of blocks to write. Must be greater than 0.
 *
 * @retval NRF_SUCCESS              If block write operation was started succesfully.
 * @retval NRF_ERROR_INVALID_STATE  If the card is not initialized.
 * @retval NRF_ERROR_BUSY           If there is already an operation active.
 * @retval NRF_ERROR_INVALID_PARAM  If invalid parameters were specified.
 */
ret_code_t app_sdc_block_write(uint8_t const * p_buf, uint32_t block_address, uint16_t block_count);


/**
 * @brief Function for retrieving the card information structure.
 *
 * @return Pointer to the card information structure or NULL if card is not initialized.
 */
app_sdc_info_t const * app_sdc_info_get(void);


#endif //APP_SDC_H_
/** @} */
