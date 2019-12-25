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
#ifndef ESCS_DEFS_H__
#define ESCS_DEFS_H__

#include "es.h"

/*@file Contains definitions specific to the Eddystone Configuration Service */

#define ESCS_LOCK_STATE_NEW_LOCK_CODE_WRITE_LENGTH 17

#define ESCS_UID_READ_LENGTH          (ES_UID_LENGTH)
#define ESCS_UID_WRITE_LENGTH         (ES_UID_NAMESPACE_LENGTH + \
                                       ES_UID_INSTANCE_LENGTH + ES_FRAME_TYPE_LENGTH)

#define ESCS_TLM_READ_LENGTH          (ESCS_TLM_READ_LENGTH)
#define ESCS_TLM_WRITE_LENGTH         (ES_FRAME_TYPE_LENGTH)

#define ESCS_EID_READ_LENGTH            (14)
#define ESCS_EID_WRITE_ECDH_LENGTH      (34)
#define ESCS_EID_WRITE_PUB_KEY_INDEX    (1)
#define ESCS_EID_WRITE_ENC_ID_KEY_INDEX (1)
#define ESCS_EID_WRITE_IDK_LENGTH       (18)

#define ESCS_LOCK_STATE_READ_LENGTH     (1)

#define ESCS_URL_MIN_WRITE_LENGTH       (4)
#define ESCS_URL_WRITE_LENGTH           (19)

#ifdef NRF52_SERIES
#define ESCS_NUM_OF_SUPPORTED_TX_POWER  (9)
/**@brief TX power levels, based on nRF52 specifications. */
#define ESCS_SUPPORTED_TX_POWER         {-40, -20, -16, -12,  -8,  -4,  0,  3,  4}
#elif NRF51
/**@brief TX power levels, based on nRF51 specifications. */
#define ESCS_NUM_OF_SUPPORTED_TX_POWER  (8)
#define ESCS_SUPPORTED_TX_POWER         {-30, -20, -16, -12,  -8,  -4,  0,  4}
#else
#error MISSING TX POWER
#endif

// Defined in Eddystone Specifications
#define ESCS_AES_KEY_SIZE               (16)
#define ESCS_ECDH_KEY_SIZE              (32)

#define ESCS_ADV_SLOT_CHAR_LENGTH_MAX   (34) // Corresponds to when the slots is configured as an EID slot

// Characteristic: Broadcast Capabilities

// Field: nrf_ble_escs_init_params_t.broadcast_cap.cap_bitfield
#define ESCS_BROADCAST_VAR_ADV_SUPPORTED_Yes          (1) // Set if the beacon supports individual per-slot adv intervals
#define ESCS_BROADCAST_VAR_ADV_SUPPORTED_No           (0)
#define ESCS_BROADCAST_VAR_ADV_SUPPORTED_Pos          (0)
#define ESCS_BROADCAST_VAR_ADV_SUPPORTED_Msk          (1 << ESCS_BROADCAST_VAR_ADV_SUPPORTED_Pos)
#define ESCS_BROADCAST_VAR_TX_POWER_SUPPORTED_Yes     (1) // Set if the beacon supports individual per-slot TX intervals
#define ESCS_BROADCAST_VAR_TX_POWER_SUPPORTED_No      (0)
#define ESCS_BROADCAST_VAR_TX_POWER_SUPPORTED_Pos     (1)
#define ESCS_BROADCAST_VAR_TX_POWER_SUPPORTED_Msk     (1 << ESCS_BROADCAST_VAR_TX_POWER_SUPPORTED_Pos)
#define ESCS_BROADCAST_VAR_RFU_MASK                   (0x03) // AND Mask to guarantee that bits 0x04 to 0x80 (RFU) are cleared

// Field: nrf_ble_escs_init_params_t.broadcast_cap.supp_frame_types
#define ESCS_FRAME_TYPE_UID_SUPPORTED_Yes             (1)
#define ESCS_FRAME_TYPE_UID_SUPPORTED_No              (0)
#define ESCS_FRAME_TYPE_UID_SUPPORTED_Pos             (0)
#define ESCS_FRAME_TYPE_UID_SUPPORTED_Msk             (1 << ESCS_FRAME_TYPE_UID_SUPPORTED_Pos)

#define ESCS_FRAME_TYPE_URL_SUPPORTED_Yes             (1)
#define ESCS_FRAME_TYPE_URL_SUPPORTED_No              (0)
#define ESCS_FRAME_TYPE_URL_SUPPORTED_Pos             (1)
#define ESCS_FRAME_TYPE_URL_SUPPORTED_Msk             (1 << ESCS_FRAME_TYPE_URL_SUPPORTED_Pos)

#define ESCS_FRAME_TYPE_TLM_SUPPORTED_Yes             (1)
#define ESCS_FRAME_TYPE_TLM_SUPPORTED_No              (0)
#define ESCS_FRAME_TYPE_TLM_SUPPORTED_Pos             (2)
#define ESCS_FRAME_TYPE_TLM_SUPPORTED_Msk             (1 << ESCS_FRAME_TYPE_TLM_SUPPORTED_Pos)

#define ESCS_FRAME_TYPE_EID_SUPPORTED_Yes             (1)
#define ESCS_FRAME_TYPE_EID_SUPPORTED_No              (0)
#define ESCS_FRAME_TYPE_EID_SUPPORTED_Pos             (3)
#define ESCS_FRAME_TYPE_EID_SUPPORTED_Msk             (1 << ESCS_FRAME_TYPE_EID_SUPPORTED_Pos)

#define ESCS_FRAME_TYPE_RFU_MASK                      (0x000F) // AND Mask to guarantee that bits 0x0010 to 0x8000 (RFU) are cleared

// Characteristic: Lock State: Lock State (READ)
#define ESCS_LOCK_STATE_LOCKED                        (0x00)
#define ESCS_LOCK_STATE_UNLOCKED                      (0x01)
#define ESCS_LOCK_STATE_UNLOCKED_AUTO_RELOCK_DISABLED (0x02)

// Characteristic: Lock State: Lock Byte (WRITE)
#define ESCS_LOCK_BYTE_LOCK                           (0x00)
#define ESCS_LOCK_BYTE_DISABLE_AUTO_RELOCK            (0x02)


// Charcteristic: Remain Connectable
#define ESCS_FUNCT_REMAIN_CONNECTABLE_SUPPORTED_Yes   (0x01)
#define ESCS_FUNCT_REMAIN_CONNECTABLE_SUPPORTED_No    (0x00)

#endif // ESCS_DEFS_H__
