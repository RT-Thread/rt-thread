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
#include <stdbool.h>
#include <stdint.h>
#include "cgms_db.h"

typedef struct
{
    bool           in_use_flag;
    ble_cgms_rec_t record;
} database_entry_t;

static database_entry_t m_database[CGMS_DB_MAX_RECORDS];
static uint8_t          m_database_crossref[CGMS_DB_MAX_RECORDS];
static uint16_t         m_num_records;


ret_code_t cgms_db_init(void)
{
    int i;

    for (i = 0; i < CGMS_DB_MAX_RECORDS; i++)
    {
        m_database[i].in_use_flag = false;
        m_database_crossref[i]    = 0xFF;
    }

    m_num_records = 0;

    return NRF_SUCCESS;
}


uint16_t cgms_db_num_records_get(void)
{
    return m_num_records;
}


ret_code_t cgms_db_record_get(uint8_t record_num, ble_cgms_rec_t * p_rec)
{
    if (record_num >= m_num_records)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    // copy record to the specified memory
    *p_rec = m_database[m_database_crossref[record_num]].record;

    return NRF_SUCCESS;
}


ret_code_t cgms_db_record_add(ble_cgms_rec_t * p_rec)
{
    int i;

    if (m_num_records == CGMS_DB_MAX_RECORDS)
    {
        return NRF_ERROR_NO_MEM;
    }

    // find next available database entry
    for (i = 0; i < CGMS_DB_MAX_RECORDS; i++)
    {
        if (!m_database[i].in_use_flag)
        {
            m_database[i].in_use_flag = true;
            m_database[i].record      = *p_rec;

            m_database_crossref[m_num_records] = i;
            m_num_records++;

            return NRF_SUCCESS;
        }
    }

    return NRF_ERROR_NO_MEM;
}


ret_code_t cgms_db_record_delete(uint8_t record_num)
{
    int i;

    if (record_num >= m_num_records)
    {
        // Deleting a non-existent record is not an error
        return NRF_SUCCESS;
    }

    // free entry
    m_database[m_database_crossref[record_num]].in_use_flag = false;

    // decrease number of records
    m_num_records--;

    // remove cross reference index
    for (i = record_num; i < m_num_records; i++)
    {
        m_database_crossref[i] = m_database_crossref[i + 1];
    }

    return NRF_SUCCESS;
}


