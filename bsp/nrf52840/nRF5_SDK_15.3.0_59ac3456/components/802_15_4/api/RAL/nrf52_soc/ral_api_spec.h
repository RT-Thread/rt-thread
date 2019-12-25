/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
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
#ifndef RAL_API_SPEC_H_INCLUDED
#define RAL_API_SPEC_H_INCLUDED

#include <stdbool.h>

/**
 * @defgroup ral_api_spec RAL Special API
 * @ingroup ral_api
 * @{
 */

/**@brief   Specific CCA MODE for FPGA RAL
 */
#define RAL_TRX_CCA_MODE4                   4

/**@brief   Maximum available value of CCA MODE for FPGA RAL
 */
#define RAL_TRX_CCA_MODE_MAX                RAL_TRX_CCA_MODE4

/**@brief   Maximum duration of CCA algorithm including a task scheduling
 */
#define RAL_LONGEST_CCA_DURATION_US         500

/**@brief   Maximum transmit power in dBm
 */
#define RAL_MAXIMUM_TX_POWER                9

/**@brief   Maximum tolerance of transmit power in dBm
 */
#define RAL_TX_POWER_TOLERANCE              PHY_TX_POWER_TOLERANCE_6DB

/**@brief Value of RF signal power (in dBm) for RSSI equals zero.
 */
#define RSSI_BASE_VAL           90

/**@brief Values above this shouldn't appear in RSSI register result.*/
#define RSSI_REG_MAX_VAL        20


/**@brief Controls whether radio module will automatically calculate Frame
 * Control Sequence field.
 *
 * @param auto_fcs_enabled if set to true, automatically generated FCS will
 *                         replace the last two bytes of PHY service data unit.
 */
void ral_auto_fcs_set(bool auto_fcs_enabled);

/**@brief Controls whether radio module will enter channel jamming mode.
 *
 * @param jamming_enabled if set to true, radio will perform jamming on current
 *                        channel and energy. No data transmission can be done
 *                        while jamming is enabled.
 */
void ral_jam_control_set(bool jamming_enabled);

/** @} */

#endif// RAL_API_SPEC_H_INCLUDED
