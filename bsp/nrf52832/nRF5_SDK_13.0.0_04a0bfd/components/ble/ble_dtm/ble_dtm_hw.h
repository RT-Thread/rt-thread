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
/** @file
 *
 * @defgroup ble_dtm_hw Direct Test Mode HW
 * @{
 * @ingroup ble_sdk_lib
 * @brief Module contains hardware related function for testing RF/PHY using DTM commands.
 */

#ifndef BLE_DTM_HW_H__
#define BLE_DTM_HW_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Function for selecting a timer resource.
 *        This function may be called directly, or through dtm_cmd() specifying
 *        DTM_PKT_VENDORSPECIFIC as payload, SELECT_TIMER as length, and the timer as freq
 *
 * @param[out] mp_timer      Pointer to timer instance used in dtm source file.
 * @param[out] m_timer_irq   Pointer to timer interrupt related to mp_timer.
 * @param[in]  new_timer     Timer id for the timer to use.
 *
 * @retval true  if the timer was successfully changed.
 * @retval false if the error occurs.
 */

bool dtm_hw_set_timer(NRF_TIMER_Type ** mp_timer, IRQn_Type * m_timer_irq, uint32_t new_timer);


/**@brief Function for turning off radio test.
 *        This function is platform depending. For now only nRF51 requieres this special function.
 */
void dtm_turn_off_test(void);


/**@brief Function for setting constant carrier in radio settings.
 *        This function is used to handle vendor specific command testing continous carrier without
 *        a modulated signal.
 */
void dtm_constant_carrier(void);


/**@brief Function for validating tx power and radio move settings.
 * @param[in] m_tx_power    TX power for transmission test.
 * @param[in] m_radio_mode  Radio mode value.
 *
 * @retval DTM_SUCCESS                     if input parameters values are correct.
 * @retval DTM_ERROR_ILLEGAL_CONFIGURATION if input parameters values are not correct.
 */
uint32_t dtm_radio_validate(int32_t m_tx_power, uint8_t m_radio_mode);

#ifdef __cplusplus
}
#endif

#endif // BLE_DTM_HW_H__

/** @} */
