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
#include "ble_dtm_hw.h"
#include "ble_dtm.h"
#include <stdbool.h>
#include <string.h>
#include "nrf.h"


void dtm_turn_off_test()
{
    NRF_RADIO->TEST = 0;
}


void dtm_constant_carrier()
{
    NRF_RADIO->TEST = (RADIO_TEST_PLL_LOCK_Enabled << RADIO_TEST_PLL_LOCK_Pos) |
                      (RADIO_TEST_CONST_CARRIER_Enabled << RADIO_TEST_CONST_CARRIER_Pos);
}


uint32_t dtm_radio_validate(int32_t           m_tx_power, uint8_t           m_radio_mode)
{
    // Handle BLE Radio tuning parameters from production for DTM if required.
    // Only needed for DTM without SoftDevice, as the SoftDevice normally handles this.
    // PCN-083.
    if ( ((NRF_FICR->OVERRIDEEN) & FICR_OVERRIDEEN_BLE_1MBIT_Msk) == FICR_OVERRIDEEN_BLE_1MBIT_Override)
    {
        NRF_RADIO->OVERRIDE0 = NRF_FICR->BLE_1MBIT[0];
        NRF_RADIO->OVERRIDE1 = NRF_FICR->BLE_1MBIT[1];
        NRF_RADIO->OVERRIDE2 = NRF_FICR->BLE_1MBIT[2];
        NRF_RADIO->OVERRIDE3 = NRF_FICR->BLE_1MBIT[3];
        NRF_RADIO->OVERRIDE4 = NRF_FICR->BLE_1MBIT[4];
    }

    // Initializing code below is quite generic - for BLE, the values are fixed, and expressions
    // are constant. Non-constant values are essentially set in radio_prepare().
    if (!(m_tx_power == RADIO_TXPOWER_TXPOWER_0dBm     ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Pos4dBm  ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg30dBm ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg20dBm ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg16dBm ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg12dBm ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg8dBm  ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg4dBm
        ) ||
        (m_radio_mode > RADIO_MODE_MODE_Ble_1Mbit) // Values 0 - 2: Proprietary mode, 3 (last valid): BLE
       )
    {
        return DTM_ERROR_ILLEGAL_CONFIGURATION;
    }

    return DTM_SUCCESS;
}


bool dtm_hw_set_timer(NRF_TIMER_Type ** mp_timer, IRQn_Type * m_timer_irq, uint32_t new_timer)
{
    if (new_timer == 0)
    {
        *mp_timer    = NRF_TIMER0;
        *m_timer_irq = TIMER0_IRQn;
    }
    else if (new_timer == 1)
    {
        *mp_timer    = NRF_TIMER1;
        *m_timer_irq = TIMER1_IRQn;
    }
    else if (new_timer == 2)
    {
        *mp_timer    = NRF_TIMER2;
        *m_timer_irq = TIMER2_IRQn;
    }
    else
    {
        // Parameter error: Only TIMER 0, 1, 2 provided by nRF51
        return false;
    }
    // New timer has been selected:
    return true;
}

