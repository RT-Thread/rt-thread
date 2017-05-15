/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef RAL_FSM_PRIVATE_H_INCLUDED
#define RAL_FSM_PRIVATE_H_INCLUDED

#include "nrf52840.h"
#include "nrf52840_bitfields.h"

/** @brief Private RAL function. Sets radio module into TRX_OFF mode if
 * it was in RX or TX mode. */
void ral_fsm_a_trx_off(void * p_data);

/** @brief Private RAL function. Sets radio module into TRX_OFF mode if
 * it was in BUSY_RX or BUSY_TX mode. */
void ral_fsm_a_force_trx_off(void * p_data);

/** @brief Private RAL function. Switches radio module from TRX_OFF
 * to TX_ON mode. */
void ral_fsm_a_tx_on(void * p_data);

/** @brief Private RAL function. Switches radio module from TRX_OFF
 * to RX_ON mode. */
void ral_fsm_a_rx_on(void * p_data);

/** @brief Private RAL function. Switches radio module from TX_ON
 * to RX_ON mode. */
void ral_fsm_a_tx_to_rx(void * p_data);

/** @brief Private RAL function. Switches radio module from RX_ON
 * to TX_ON mode. */
void ral_fsm_a_rx_to_tx(void * p_data);

/** @brief Private RAL function. Prepares RX frame buffer for the next received frame. */
void ral_rx_frame_buffer_prepare(void);


#endif /* RAL_FSM_PRIVATE_H_INCLUDED */
