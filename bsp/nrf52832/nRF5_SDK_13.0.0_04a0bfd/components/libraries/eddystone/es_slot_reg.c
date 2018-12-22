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
#include "es_slot_reg.h"

#define ES_SLOT_NOT_CONFIGURED 0xab /** Value set in configured lists to indicate not configured slot. */

/**@brief Function updating 'tlm_configured' property of slot registry when slot is being cleared.
 *
 * @param[in] p_reg       Pointer to slot registry.
 * @param[in] slot_no     Slot number to be used.
 */
static void update_tlm_configured_on_clearing(es_slot_reg_t * p_reg, uint8_t slot_no)
{
    if (p_reg->tlm_configured && slot_no == p_reg->tlm_slot)
    {
        p_reg->tlm_configured = false;
    }
}


/**@brief Function updating 'num_configured_slots' and 'slots_configured' properties of slot registry when slot is being cleared.
 *
 * @param[in] p_configured              Pointer to list of configured slots.
 * @param[in] p_num_configured_slots    Pointer to number of configured slots.
 * @param[in] slot_no                   Slot number to clear.
 */
static void configured_slots_on_clear_update(uint8_t * p_configured, uint8_t * p_num_configured_slots, uint8_t slot_no)
{
    uint8_t index_of_last_configured_slot = *p_num_configured_slots - 1;

    for (uint32_t i = 0; i < APP_MAX_ADV_SLOTS; ++i)
    {
        if (p_configured[i] == slot_no)
        {
            // Copy all values 'to the right' of the cleared slot one step to the left.
            if (i < index_of_last_configured_slot)
            {
                for (uint32_t j = i; j < index_of_last_configured_slot; ++j)
                {
                    p_configured[j] = p_configured[j + 1];
                }
                // Write ES_SLOT_NOT_CONFIGURED to all rightmost not configured indexes.
                memset(&p_configured[index_of_last_configured_slot],
                       ES_SLOT_NOT_CONFIGURED,
                       APP_MAX_ADV_SLOTS - index_of_last_configured_slot);
            }

            else
            {
                // There are no values 'to the right', simply overwrite with ES_SLOT_NOT_CONFIGURED
                p_configured[i] = ES_SLOT_NOT_CONFIGURED;
            }

            *p_num_configured_slots -= 1;

            return;
        }
    }
}


bool es_slot_reg_etlm_required(const es_slot_reg_t * p_reg)
{
    return (p_reg->num_configured_eid_slots > 0 && p_reg->tlm_configured);
}


bool es_slot_reg_clear_slot(es_slot_reg_t * p_reg, uint8_t slot_no)
{
    bool eid_has_been_cleared = false;

    if (p_reg->slots[slot_no].configured)
    {
        update_tlm_configured_on_clearing(p_reg, slot_no);

        configured_slots_on_clear_update(p_reg->slots_configured,
                                         &p_reg->num_configured_slots,
                                         slot_no);

        if (p_reg->slots[slot_no].adv_frame.type == ES_FRAME_TYPE_EID)
        {
            configured_slots_on_clear_update(p_reg->eid_slots_configured,
                                             &p_reg->num_configured_eid_slots,
                                             slot_no);

            eid_has_been_cleared = true;
        }

        p_reg->slots[slot_no].configured = false;
    }

    memset(&p_reg->slots[slot_no], 0, sizeof(p_reg->slots[slot_no]));

    return eid_has_been_cleared;
}


void es_slot_reg_update_slot_list_info_on_add(es_slot_reg_t * p_reg,
                                              uint8_t         slot_no,
                                              es_frame_type_t frame_type,
                                              bool            init)
{
    if (frame_type == ES_FRAME_TYPE_TLM)
    {
        p_reg->tlm_configured = true;
        p_reg->tlm_slot       = slot_no;
    }

    if (!p_reg->slots[slot_no].configured || init)
    {
        p_reg->slots[slot_no].configured = true;

        // Note, we use 'num_configured_slots' before incrementing it, so it is pointing to the correct index.
        p_reg->slots_configured[p_reg->num_configured_slots] = slot_no;

        p_reg->num_configured_slots++;

        if (frame_type == ES_FRAME_TYPE_EID)
        {
            p_reg->eid_slots_configured[p_reg->num_configured_eid_slots] = slot_no;

            p_reg->num_configured_eid_slots++;
        }
    }

    // If an already configured slot has changed from anything TO an EID slot.
    else if (frame_type == ES_FRAME_TYPE_EID &&
             p_reg->slots[slot_no].adv_frame.type != ES_FRAME_TYPE_EID)
    {
        p_reg->eid_slots_configured[p_reg->num_configured_eid_slots] = slot_no;

        p_reg->num_configured_eid_slots++;
    }
}


void es_slot_reg_init(es_slot_reg_t * p_reg)
{
    p_reg->tlm_configured = false;
    memset(p_reg->slots_configured, ES_SLOT_NOT_CONFIGURED, APP_MAX_ADV_SLOTS);
    memset(p_reg->eid_slots_configured, ES_SLOT_NOT_CONFIGURED, APP_MAX_EID_SLOTS);
    p_reg->num_configured_eid_slots = 0;
    p_reg->num_configured_slots     = 0;
}
