/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
 * @defgroup ipv6_medium_ble BLE IPv6 Medium Implementation
 * @{
 * @ingroup iot_sdk_common
 * @brief Bluetooth Low Energy implementation of the IPv6 medium interface.
 *
 * @details Type definitions for the BLE implementation of the IPv6 medium interface.
 *          This header also includes the header with BLE-specific configuration.
 */

#ifndef IPV6_MEDIUM_BLE_H__
#define IPV6_MEDIUM_BLE_H__

#include <stdint.h>
#include "ble.h"
#include "ble_advdata.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Structure for storing all GAP parameters. */
typedef struct
{
    uint16_t                  appearance;
    uint8_t const           * p_dev_name;
    uint16_t                  dev_name_len;
    ble_gap_conn_sec_mode_t   sec_mode;
    ble_gap_conn_params_t     gap_conn_params;
} ipv6_medium_ble_gap_params_t;

/**@brief Structure for storing all advertisement parameters. */
typedef struct
{
    ble_advdata_t            advdata;
    ble_advdata_manuf_data_t adv_man_specific_data;
    ble_advdata_t            srdata;
    ble_advdata_manuf_data_t sr_man_specific_data;
    ble_gap_adv_params_t     advparams;
} ipv6_medium_ble_adv_params_t;

/**@brief Structure of BLE-specific parameters of events passed to the parent layer by the IPv6 medium. */
typedef struct
{
    ble_evt_t * p_ble_evt;
} ipv6_medium_ble_cb_params_t;

/**@brief Structure of BLE-specific parameters of errors passed to the parent layer by the IPv6 medium. */
typedef struct
{
    uint8_t dummy_value; // Parameters to be added.
} ipv6_medium_ble_error_params_t;

#ifdef __cplusplus
}
#endif

#endif // IPV6_MEDIUM_BLE_H__

/** @} */
