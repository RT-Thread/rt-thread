/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#include "app_ble_gap_sec_keys.h"
#include "ser_config.h"
#include "nrf_error.h"
#include "nordic_common.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#if NRF_SD_BLE_API_VERSION >= 6
typedef struct {
    bool    active;
    uint8_t adv_handle;
    uint8_t * p_adv_data;
    uint8_t * p_scan_rsp_data;
} adv_set_t;

static adv_set_t m_adv_sets[4]; //todo configurable number of adv sets.

static ble_data_t m_scan_data = {0};
#endif
ser_ble_gap_app_keyset_t m_app_keys_table[SER_MAX_CONNECTIONS];

uint32_t app_ble_gap_sec_context_create(uint16_t conn_handle, uint32_t *p_index)
{
  uint32_t err_code = NRF_ERROR_NO_MEM;
  uint32_t i;

  for (i=0; i<SER_MAX_CONNECTIONS; i++ )
  {
    if ( ! m_app_keys_table[i].conn_active )
    {
        m_app_keys_table[i].conn_active = 1;
        m_app_keys_table[i].conn_handle = conn_handle;
        *p_index = i;
        err_code = NRF_SUCCESS;
        break;
    }
  }

  return err_code;
}

uint32_t app_ble_gap_sec_context_destroy(uint16_t conn_handle)
{
  uint32_t err_code = NRF_ERROR_NOT_FOUND;
  uint32_t i;

  for (i=0; i<SER_MAX_CONNECTIONS; i++ )
  {
    if (  m_app_keys_table[i].conn_handle == conn_handle )
    {
        m_app_keys_table[i].conn_active = 0;
        err_code = NRF_SUCCESS;
        break;
    }
  }

  return err_code;
}

uint32_t app_ble_gap_sec_context_find(uint16_t conn_handle, uint32_t *p_index)
{
  uint32_t err_code = NRF_ERROR_NOT_FOUND;
  uint32_t i;

  for (i=0; i<SER_MAX_CONNECTIONS; i++ )
  {
    if ( (m_app_keys_table[i].conn_handle == conn_handle) && (m_app_keys_table[i].conn_active == 1) )
    {
        *p_index = i;
        err_code = NRF_SUCCESS;
        break;
    }
  }

  return err_code;
}
#if NRF_SD_BLE_API_VERSION >= 6
uint32_t app_ble_gap_scan_data_set(ble_data_t const * p_data)
{
    if (m_scan_data.p_data)
    {
        return NRF_ERROR_BUSY;
    }
    else
    {
        memcpy(&m_scan_data, p_data, sizeof(ble_data_t));
        return NRF_SUCCESS;
    }
}


uint32_t app_ble_gap_scan_data_fetch_clear(ble_data_t * p_data)
{
    memcpy(p_data, &m_scan_data, sizeof(ble_data_t));
    if (m_scan_data.p_data)
    {
        m_scan_data.p_data = NULL;
        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_NOT_FOUND;
    }
}

uint32_t app_ble_gap_adv_set_register(uint8_t adv_handle, uint8_t * p_adv_data, uint8_t * p_scan_rsp_data)
{
    uint32_t err_code = NRF_ERROR_NO_MEM;
    uint32_t i;
    for (i = 0; i < ARRAY_SIZE(m_adv_sets); i++)
    {
        if (m_adv_sets[i].active == false)
        {
            m_adv_sets[i].active = true;
            m_adv_sets[i].adv_handle = adv_handle;
            m_adv_sets[i].p_adv_data = p_adv_data;
            m_adv_sets[i].p_scan_rsp_data = p_scan_rsp_data;
            err_code = NRF_SUCCESS;
            break;
        }
    }
    return err_code;
}

uint32_t app_ble_gap_adv_set_unregister(uint8_t adv_handle, uint8_t * * pp_adv_data, uint8_t **pp_scan_rsp_data)
{
    uint32_t err_code = NRF_ERROR_NOT_FOUND;
    uint32_t i;
    for (i = 0; i < ARRAY_SIZE(m_adv_sets); i++)
    {
        if ((m_adv_sets[i].active == true) && (m_adv_sets[i].adv_handle == adv_handle))
        {
            m_adv_sets[i].active = false;
            *pp_adv_data = m_adv_sets[i].p_adv_data;
            *pp_scan_rsp_data = m_adv_sets[i].p_scan_rsp_data;
            err_code = NRF_SUCCESS;
            break;
        }
    }
    return err_code;
}
#endif
