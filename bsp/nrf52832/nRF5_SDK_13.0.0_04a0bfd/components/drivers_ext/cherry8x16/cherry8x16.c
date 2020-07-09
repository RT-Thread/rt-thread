/**
 * Copyright (c) 2009 - 2017, Nordic Semiconductor ASA
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
#include <stdint.h>
#include <stdbool.h>

#include "cherry8x16.h"
#include "nrf.h"

#define CHERRY8x16_NUM_OF_COLUMNS 16 // !< Number of columns in the keyboard matrix
#define CHERRY8x16_NUM_OF_ROWS    8  // !< Number of rows in the keyboard matrix

#define MODIFIER_HID_START 0xE0
#define MODIFIER_HID_END   0xE7
static uint8_t m_currently_pressed_keys[CHERRY8x16_MAX_NUM_OF_PRESSED_KEYS]; //!< Array holding currently pressed keys. Filled up from index 0. Values are
static uint8_t m_transmitted_keys[CHERRY8x16_MAX_NUM_OF_PRESSED_KEYS];       //!< Array holding the keys that have already been transmitted.
static uint8_t m_num_of_currently_pressed_keys;                              //!< Number of keys in m_currently_pressed_keys
static uint8_t m_number_of_transmitted_keys;                                 //!< Number of keys in m_transmitted_keys

static uint8_t m_key_packet[KEY_PACKET_SIZE]; //!< Stores last created key packet. One byte is used for modifier keys, one for OEMs. Key values are USB HID keycodes.

static const uint8_t volatile * m_row_port;    //!< Pointer to location where row IO can be read
static uint16_t volatile      * m_column_port; //!< Pointer to location where column IO can be written
static const uint8_t          * matrix_lookup; //!< Pointer to the key lookup matrix in use

/** Table containing the mapping between the key matrix and the HID Usage codes for each key. */
static const uint8_t default_matrix_lookup[CHERRY8x16_NUM_OF_COLUMNS * CHERRY8x16_NUM_OF_ROWS] =
{
    0xE7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xE3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xE1, 0xE6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xE2, 0xE5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x29, 0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x3F, 0x40,
    0x1E, 0x23, 0x22, 0x21, 0x20, 0x1F, 0x24, 0x25,
    0x4F, 0x43, 0x47, 0x53, 0x46, 0x48, 0x42, 0x41,
    0x51, 0x2D, 0x2E, 0x2A, 0x00, 0x4A, 0x27, 0x26,
    0x52, 0x13, 0x2F, 0x30, 0x00, 0x4B, 0x12, 0x0C,
    0x50, 0x33, 0x34, 0x32, 0x28, 0x4E, 0x0F, 0x0E,
    0x2C, 0x38, 0x4C, 0x49, 0x65, 0x4D, 0x37, 0x36,
    0x35, 0x05, 0x19, 0x06, 0x1B, 0x1D, 0x11, 0x10,
    0x39, 0x0A, 0x09, 0x07, 0x16, 0x04, 0x0B, 0x0D,
    0x2B, 0x17, 0x15, 0x08, 0x1A, 0x14, 0x1C, 0x18
};

static bool cherry8x16_have_keys_changed(const uint8_t * state_now,
                                         uint8_t         number_of_now_pressed_keys,
                                         const uint8_t * state_before,
                                         uint8_t         number_of_before_pressed_keys);
static bool cherry8x16_keymatrix_read(uint8_t * pressed_keys, uint8_t * number_of_pressed_keys);
static void cherry8x16_keypacket_addkey(uint8_t key);
static void cherry8x16_keypacket_create(uint8_t * key_packet, uint8_t key_packet_size);
static void cherry8x16_remap_fn_keys(uint8_t * keys, uint8_t number_of_keys);
static uint8_t cherry8x16_row_read(void);

cherry8x16_status_t cherry8x16_init(const uint8_t volatile * row_port,
                                    uint16_t               * column_port,
                                    const uint8_t          * key_lookup_matrix)
{
    cherry8x16_status_t status = CHERRY8x16_OK;

    if (row_port == 0 || column_port == 0)
    {
        status = CHERRY8x16_INVALID_PARAMETER;
    }
    else
    {
        m_row_port    = row_port;
        m_column_port = column_port;

        *m_column_port = 0x0000;
        if (*m_row_port != 0x00)
        {
            status = CHERRY8x16_NOT_DETECTED;
        }
        else
        {
            m_num_of_currently_pressed_keys = 0;
            m_number_of_transmitted_keys    = 0;

            for (uint_fast8_t i = CHERRY8x16_MAX_NUM_OF_PRESSED_KEYS; i--;)
            {
                m_currently_pressed_keys[i] = 0;
                m_transmitted_keys[i]       = 0;
            }
        }

        if (key_lookup_matrix == CHERRY8x16_DEFAULT_KEY_LOOKUP_MATRIX)
        {
            matrix_lookup = default_matrix_lookup;
        }
        else
        {
            matrix_lookup = key_lookup_matrix;
        }
    }

    return status;
}

bool cherry8x16_new_packet(const uint8_t ** p_key_packet, uint8_t * p_key_packet_size)
{
    bool new_packet_prepared;

    // Save currently pressed keys
    for (uint_fast8_t i = CHERRY8x16_MAX_NUM_OF_PRESSED_KEYS; i--; )
    {
        m_transmitted_keys[i] = m_currently_pressed_keys[i];
    }
    m_number_of_transmitted_keys = m_num_of_currently_pressed_keys;

    // Create a new packet if key states have changed and there are no keys blocking each other (ghosting/phantom keys)
    if (cherry8x16_keymatrix_read(m_currently_pressed_keys, &m_num_of_currently_pressed_keys))
    {
        if (cherry8x16_have_keys_changed(m_currently_pressed_keys, m_num_of_currently_pressed_keys,
                                         m_transmitted_keys, m_number_of_transmitted_keys))
        {
            cherry8x16_keypacket_create(&m_key_packet[0], KEY_PACKET_SIZE);
            *p_key_packet       = &m_key_packet[0];
            *p_key_packet_size  = KEY_PACKET_SIZE;
            new_packet_prepared = true;
        }
        else
        {
            // The same keys are still pressed, no need to create a new packet
            new_packet_prepared = false;
        }
    }
    else
    {
        // Ghosting detected. Don't create a packet.
        new_packet_prepared = false;
    }

    return new_packet_prepared;
}


/**
 * @brief Function for reading and returning keyboard matrix row state.
 *
 * @return uint8_t Row state
 */
static uint8_t cherry8x16_row_read(void)
{
    return *m_row_port;
}


/**
 * @brief Function for reading the keyboard matrix state and stores the pressed keys to an array.
 *
 * This function resolves keys from the matrix and finds their corresponding HID usage codes
 * If there are any ghost key conditions the packet will be discarded
 * @param pressed_keys Array holding pressed keys. Must be at least CHERRY8x16_MAX_NUM_OF_PRESSED_KEYS in size.
 * @param number_of_pressed_keys Pointer to variable where number of pressed keys will be stored.
 * @return
 * @retval true If no keys were blocking each other.
 * @retval false If some keys were blocking each other o rno key is pressed.
 */
static bool cherry8x16_keymatrix_read(uint8_t * pressed_keys, uint8_t * number_of_pressed_keys)
{
    uint_fast8_t row_state[CHERRY8x16_NUM_OF_COLUMNS];
    uint_fast8_t blocking_mask = 0;

    *number_of_pressed_keys = 0;

    for (uint_fast8_t column = CHERRY8x16_NUM_OF_COLUMNS; column--;)
    {
        // drive column under test
        *m_column_port    = (uint16_t)(1UL << column);
        row_state[column] = cherry8x16_row_read();

        // Check if any keys are pressed
        if (row_state[column] != 0)
        {
            uint_fast8_t detected_keypresses_on_column = 0;

            // Loop through rows, check for active rows and add pressed keys to the array
            for (uint_fast8_t row = CHERRY8x16_NUM_OF_ROWS; row--;)
            {
                if (row_state[column] & (1U << row))
                {
                    if (*number_of_pressed_keys < CHERRY8x16_MAX_NUM_OF_PRESSED_KEYS)
                    {
                        *pressed_keys = matrix_lookup[column * CHERRY8x16_NUM_OF_ROWS + row];
                        pressed_keys++;
                        (*number_of_pressed_keys)++;
                    }
                    detected_keypresses_on_column++;
                }
            }

            if (detected_keypresses_on_column > 1)
            {
                if (blocking_mask & row_state[column])
                {
                    // Cannot determine reliably all pressed keys, two or more keys are blocking each other.
                    return false;
                }
            }
            blocking_mask |= row_state[column];
        }
    }

    return true;
}


/**
 * @brief Function for remapping the keypad, F11 and F12 keys in case when Fn key is pressed.
 *
 * @param keys Array holding pressed keys.
 * @param number_of_keys Number of elements if 'keys' array.
 */
static void cherry8x16_remap_fn_keys(uint8_t * keys, uint8_t number_of_keys)
{

    /*lint -e845 -save // A zero has been given as right argument to operator '<<'" */
    /*lint -e778 -save // Constant expression evaluates to zero */

#define MODIFIER_LEFT_CONTROL_HID 0xE0
#define MODIFER_RIGHT_CONTROL_HID 0xE4
    // Check if Fn key is pressed along with any other modifier key (only usage now is Fn + Left_Ctrl = Right Ctrl)
    // So we modify the modifier byte if Fn + Left_Ctrl is pressed, HID for left_Ctrl = 0xE0
    if ( keys[0] & (1UL << (MODIFIER_LEFT_CONTROL_HID - MODIFIER_HID_START)) )
    {
        keys[0] &= ~(1UL << (MODIFIER_LEFT_CONTROL_HID - MODIFIER_HID_START));
        keys[0] |= (1UL << (MODIFER_RIGHT_CONTROL_HID - MODIFIER_HID_START));
    }

    /*lint -restore */
    /*lint -restore */

    for (uint_fast8_t i = 2; i < number_of_keys; i++)
    {
        switch (keys[i])
        {
            case 0x10:          // 'M'
                keys[i] = 0x62; // Keypad 0
                break;

            case 0x37:          // '>'
                keys[i] = 0x63; // Keypad .
                break;

            case 0x38:          // '/'
                keys[i] = 0x54; // Keypad /
                break;

            case 0x0D:          // 'J'
                keys[i] = 0x59; // Keypad 1
                break;

            case 0x0E:          // 'K'
                keys[i] = 0x5A; // Keypad 2
                break;

            case 0x0F:          // 'L'
                keys[i] = 0x5B; // Keypad 3
                break;

            case 0x33:          // ''
                keys[i] = 0x57; // Keypad +
                break;

            case 0x28:          // 'Enter'
                keys[i] = 0x58; // Keypad enter
                break;

            case 0x18:          // 'U'
                keys[i] = 0x5C; // Keypad 4
                break;

            case 0x0C:          // 'I'
                keys[i] = 0x5D; // Keypad 5
                break;

            case 0x12:          // 'O'
                keys[i] = 0x5E; // Keypad 6
                break;

            case 0x13:          // 'P'
                keys[i] = 0x56; // Keypad -
                break;

            case 0x24:          // '7'
                keys[i] = 0x5F; // Keypad 7
                break;

            case 0x25:          // '8'
                keys[i] = 0x60; // Keypad 8
                break;

            case 0x26:          // '9'
                keys[i] = 0x61; // Keypad 9
                break;

            case 0x27:          // '0'
                keys[i] = 0x55; // Keypad *
                break;

            case 0x3A:          // 'F1'
                keys[i] = 0x44; // 'F11'
                break;

            case 0x3B:          // 'F2'
                keys[i] = 0x45; // 'F12'
                break;

            default:
                break;
        }
    }
}


/**
 * @brief Function for determining whether the keyboard matrix state has changed compared to the state before.
 *
 * @param state_now List of pressed keys in current state
 * @param number_of_now_pressed_keys Number of pressed keys in current state
 * @param state_before List of pressed keys in previous state
 * @param number_of_before_pressed_keys Number of pressed keys in previous state
 * @return
 * @retval true If keyboard matrix is different compared to state before.
 * @retval false If keyboard matrix is the same compared to state before.
 */
static bool cherry8x16_have_keys_changed(const uint8_t * state_now,
                                         uint8_t         number_of_now_pressed_keys,
                                         const uint8_t * state_before,
                                         uint8_t         number_of_before_pressed_keys)
{
    if (number_of_now_pressed_keys != number_of_before_pressed_keys)
    {
        return true;
    }
    else
    {
        for (uint_fast8_t i = number_of_now_pressed_keys; i--;)
        {
            if (state_now[i] != state_before[i])
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Function for adding a key to the key packet.
 *
 * If key is found to be in the packet, it will not be added twice.
 * Attempts to add more keys than the buffer capacity allows will be silently ignored.
 *
 * @param key Key to add
 */
static void cherry8x16_keypacket_addkey(uint8_t key)
{
    for (uint_fast8_t i = KEY_PACKET_KEY_INDEX; i < KEY_PACKET_SIZE; i++)
    {
        if (m_key_packet[i] == key)
        {
            return;
        }
    }

    for (uint_fast8_t i = KEY_PACKET_KEY_INDEX; i < KEY_PACKET_SIZE; i++)
    {
        if (m_key_packet[i] == KEY_PACKET_NO_KEY)
        {
            m_key_packet[i] = key;
            return;
        }
    }
}

/**
 * @brief Function for creating a new key packet.
 *
 * This function uses @ref m_currently_pressed_keys to determine pressed keys.
 * Priority is given to those keys that were found in the previous packet.
 * All modifier keys can be found in all packets.
 * If Fn key is detected to be pressed, some keys are remapped to different functions.
 *
 * @param key_packet Pointer to location where packet contents will be put
 * @param key_packet_size Key packet size in bytes
 */
static void cherry8x16_keypacket_create(uint8_t * key_packet, uint8_t key_packet_size)
{
    // Clear key_packet contents
    for (uint_fast8_t i = KEY_PACKET_KEY_INDEX; i < key_packet_size; i++)
    {
        key_packet[i] = KEY_PACKET_NO_KEY;
    }
    key_packet[KEY_PACKET_MODIFIER_KEY_INDEX] = 0;
    key_packet[KEY_PACKET_RESERVED_INDEX]     = 0;

    // Give priority to keys that were already pressed when we transmitted them the last time.
    for (uint_fast8_t i = 0; i < m_number_of_transmitted_keys; i++)
    {
        for (uint_fast8_t j = 0; j < m_num_of_currently_pressed_keys; j++)
        {
            if (m_transmitted_keys[i] == m_currently_pressed_keys[j])
            {
                cherry8x16_keypacket_addkey(m_currently_pressed_keys[j]);
                break;
            }
        }
    }

    bool fn_key_is_set = false;

    // Detect if Fn is pressed, detect modifier keys, and add rest of the keys to the packet
    for (uint_fast8_t i = 0; i < m_num_of_currently_pressed_keys; i++)
    {
        if (m_currently_pressed_keys[i] == 0xFF) // Pressing Fn key changes function of certain keys and it must handled by the firmware
        {
            fn_key_is_set = true;
        }
        // Modifier HID usage codes are from 0xE0 to 0xE7
        else if (m_currently_pressed_keys[i] >= MODIFIER_HID_START && m_currently_pressed_keys[i] <= MODIFIER_HID_END) // Detect and set modifier keys
        {
            key_packet[KEY_PACKET_MODIFIER_KEY_INDEX] |= (uint8_t)(1U << (m_currently_pressed_keys[i] - MODIFIER_HID_START));
        }
        else if (m_currently_pressed_keys[i] != 0)
        {
            cherry8x16_keypacket_addkey(m_currently_pressed_keys[i]);
        }
    }

    if (fn_key_is_set)
    {
        cherry8x16_remap_fn_keys(&key_packet[0], KEY_PACKET_MAX_KEYS);
    }
}
