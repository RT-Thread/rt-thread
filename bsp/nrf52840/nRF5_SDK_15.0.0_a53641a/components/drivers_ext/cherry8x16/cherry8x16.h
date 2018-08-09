/**
 * Copyright (c) 2009 - 2018, Nordic Semiconductor ASA
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
#ifndef CHERRY8x16_H
#define CHERRY8x16_H

/*lint ++flb "Enter library region" */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @file
* @brief Cherry 8x16 keyboard matrix driver
*
*
* @defgroup nrf_drivers_cherry8x16 Cherry 8x16 keyboard matrix driver
* @{
* @ingroup ext_drivers
* @brief Cherry 8x16 keyboard matrix driver.
*/

#define CHERRY8x16_MAX_NUM_OF_PRESSED_KEYS 6 //!< Maximum number of pressed keys kept in buffers
#define CHERRY8x16_DEFAULT_KEY_LOOKUP_MATRIX (const uint8_t*)0 //!< If passed to @ref cherry8x16_init, default lookup matrix will be used

#define KEY_PACKET_MODIFIER_KEY_INDEX (0) //!< Index in the key packet where modifier keys such as ALT and Control are stored
#define KEY_PACKET_RESERVED_INDEX (1) //!< Index in the key packet where OEMs can store information
#define KEY_PACKET_KEY_INDEX (2) //!< Start index in the key packet where pressed keys are stored
#define KEY_PACKET_MAX_KEYS (6) //!< Maximum number of keys that can be stored into the key packet
#define KEY_PACKET_SIZE (KEY_PACKET_KEY_INDEX + KEY_PACKET_MAX_KEYS) //!< Total size of the key packet in bytes
#define KEY_PACKET_NO_KEY (0) //!< Value to be stored to key index to indicate no key is pressed


/**
 * Describes return values for:
 * @ref cherry8x16_init
 */
typedef enum
{
  CHERRY8x16_OK, /*!< Operation was succesful. */
  CHERRY8x16_NOT_DETECTED, /*!< Product/Revision ID was not what was expected */
  CHERRY8x16_INVALID_PARAMETER /*!< Given parameters were not valid */
} cherry8x16_status_t;

/**
 * @brief Function for initializing the driver.
 *
 * @note Before calling this function, setup row_port as IO inputs with pulldowns enabled and column_port as IO outputs.
 *
 * @param row_port Pointer to GPIO port address that is used as key matrix row input.
 * @param column_port Pointer to GPIO port address that is used as key matrix column output.
 * @param key_lookup_matrix If NULL, use a default key lookup matrix. Otherwise pointer to a 128 (8x16) element array containing HID keycodes.
 * @return
 * @retval CHERRY8X16_OK Peripheral was initialized succesfully.
 * @retval CHERRY8X16_NOT_DETECTED Could not detect the peripheral.
 */
cherry8x16_status_t cherry8x16_init(const uint8_t volatile * row_port, uint16_t * column_port, const uint8_t * key_lookup_matrix);

/**
 * @brief Function for creating a new key packet if new data is available and key ghosting is not detected.
 *
 * @param p_key_packet Array that will hold the created key packet. Previously created packet will be discarded.
 * @param p_key_packet_size Key packet size in bytes.
 * @return
 * @retval true If new packet was created.
 * @retval false  If packet was not created.
 */
bool cherry8x16_new_packet(const uint8_t ** p_key_packet, uint8_t *p_key_packet_size);

/**
 *@}
 **/

/*lint --flb "Leave library region" */

#ifdef __cplusplus
}
#endif

#endif
