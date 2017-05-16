/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef ES_SLOT_H__
#define ES_SLOT_H__

#include <stdint.h>
#include "es_app_config.h"
#include "nrf_ble_escs.h"

/**
 * @file
 * @defgroup eddystone_slot Slots
 * @brief Types and functions for handling Eddystone slots.
 * @ingroup eddystone
 * @{
 */

/**@brief Advertisable frame types that can be passed in to the advertising
 *        data during non-connectable slot advertising. */

typedef struct
{
    union
    {
        es_uid_frame_t  uid;  //!< UID frame.
        es_url_frame_t  url;  //!< URL frame.
        es_tlm_frame_t  tlm;  //!< TLM frame.
        es_eid_frame_t  eid;  //!< EID frame.
        es_etlm_frame_t etlm; //!< eTLM frame.
    }               frame;
    es_frame_type_t type;     //!< Type defined twice for convenience (because the other one is inside a union).
    uint8_t         length;
}es_adv_frame_t;

/**@brief Slot. */
typedef struct
{
    uint8_t                     slot_no;              //!< Identifier for the slot, indexed at 0.
    nrf_ble_escs_radio_tx_pwr_t radio_tx_pwr;         //!< Radio TX power (in dB).
    nrf_ble_escs_eid_id_key_t   encrypted_eid_id_key; //!< EID key for the slot.
    es_adv_frame_t              adv_frame;            //!< Frame structure to be passed in for advertising data.
    bool                        adv_custom_tx_power;  //!< Flag that specifies if the client has written to the 'Advertised TX Power' field of this slot.
    nrf_ble_escs_radio_tx_pwr_t custom_tx_power;      //!< Custom TX power to advertise (only if @ref adv_custom_tx_power is true).
    bool                        configured;           //!< Is this slot configured and active.
    uint8_t                     k_scaler;
    uint32_t                    seconds;
    uint8_t                     ik[ESCS_AES_KEY_SIZE];
} es_slot_t;

/**@brief Slot registry. */
typedef struct
{
    es_slot_t slots[APP_MAX_ADV_SLOTS];
    uint8_t   num_configured_slots;
    uint8_t   num_configured_eid_slots;
    uint8_t   slots_configured[APP_MAX_ADV_SLOTS];
    uint8_t   eid_slots_configured[APP_MAX_EID_SLOTS];
    uint8_t   tlm_slot;
    bool      tlm_configured;
    uint8_t   scaler_k;
    uint8_t   enc_key[ESCS_AES_KEY_SIZE];
} es_slot_reg_t;

/**@brief Function for initializing the Eddystone slots with default values.
 *
 * @details This function synchronizes all slots with the initial values.
 *
 * @param[in]   p_default_slot   Pointer to the default parameters for a slot.
 */
void es_slots_init(const es_slot_t * p_default_slot);

/**@brief Function for setting the advertising interval of the specified slot.
 *
 * For compatibility with the Eddystone specifications, @p p_adv_interval must point to
 * a 16-bit big endian value (coming from the characteristic write request),
 * which is then converted to a little endian value inside the function before
 * it is written into the variable in the slot.
 *
 * @parameternoteslot
 * @parameternoteadv
 *
 * @param[in]       slot_no         The index of the slot.
 * @param[in,out]   p_adv_interval  Pointer to the advertisement interval (in ms) to set.
 * @param[in]       global          Flag that should be set if the beacon does not support variable advertising intervals.
 */
void es_slot_adv_interval_set(uint8_t                       slot_no,
                              nrf_ble_escs_adv_interval_t * p_adv_interval,
                              bool                          global);

/**@brief Function for setting the TX power of the specified slot.
 *
 * @parameternoteslot
 * @parameternotetxpower
 *
 * @param[in]       slot_no         The index of the slot.
 * @param[in,out]   radio_tx_pwr    TX power value to set.
 */
void es_slot_radio_tx_pwr_set(uint8_t slot_no, nrf_ble_escs_radio_tx_pwr_t radio_tx_pwr);

/**@brief Function for setting the R/W ADV of the specified slot.
 *
 * @parameternoteslot
 *
 * @param[in]       slot_no         The index of the slot.
 * @param[in,out]   length          The length of the data written or read.
 * @param[in,out]   p_frame_data    Pointer to the data.
 *
 */
void es_slot_on_write(uint8_t slot_no, uint8_t length, uint8_t * p_frame_data);

/**@brief Function for writing the slot's configuration to flash.
 *
 * @param[in] slot_no The index of the slot.
 */
ret_code_t es_slot_write_to_flash(uint8_t slot_no);

/**@brief Function for setting the slot's encrypted EID Identity Key to be displayed in the EID Identity Key characteristic.
 *
 * @parameternoteslot
 *
 * @param[in]       slot_no         The index of the slot.
 * @param[in,out]   p_eid_id_key    Pointer to a @ref nrf_ble_escs_eid_id_key_t structure from where the key will be written.
 */
void es_slot_encrypted_eid_id_key_set(uint8_t slot_no, nrf_ble_escs_eid_id_key_t * p_eid_id_key);

/**@brief Function for marking an EID slot as ready for populating.
 *
 * @details Call this function when an EID has been generated and the advertisement frame can be populated with the EID.
 *
 * @param[in] slot_no The index of the slot.
 */
void es_slot_eid_ready(uint8_t slot_no);

/**@brief Function for updating the TLM slot with updated data. */
void es_slot_tlm_update(void);

/**@brief Function for updating the TLM slot with eTLM data.
 *
 * @details This function uses the EID identity key from the given EID slot number to update the TLM slot.
 *
 * @param[in] eid_slot_no     EID slot to get EID identity key from.
 */
void es_slot_etlm_update(uint8_t eid_slot_no);

/**@brief Function for getting a pointer to the slot registry.
 *
 * @return  A pointer to the slot registry.
 */
const es_slot_reg_t * es_slot_get_registry(void);

/**@brief Function for setting a custom advertisement TX power for a given slot.
 *
 * @parameternoteslot
 * @parameternotetxpower
 *
 * @param[in]       slot_no         The index of the slot.
 * @param[in]       tx_pwr          Advertised TX power to be set.
 */
void es_slot_set_adv_custom_tx_power(uint8_t slot_no, nrf_ble_escs_adv_tx_pwr_t tx_pwr);

/**
 * @}
 */

#endif // ES_SLOT_H__
