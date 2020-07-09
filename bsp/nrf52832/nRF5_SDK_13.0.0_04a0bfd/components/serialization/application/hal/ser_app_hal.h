/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
/**@file
 *
 * @defgroup ser_app_hal Serialization Application Hardware Abstraction Layer (HAL)
 * @{
 * @ingroup ble_sdk_lib_serialization
 *
 * @brief Functions that set up hardware on Application Board and perform the reset of the Connectivity Board.
 */

#ifndef SER_APP_HAL_H_
#define SER_APP_HAL_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef void (*ser_app_hal_flash_op_done_handler_t)(bool success);
/**@brief Function for initializing hardware modules.
 *
 * @details Function can initialize hardware modules on the Application Chip. It is optional to
 * implement. It is called once the Connectivity Chip is initialized.
 *
 * @param handler Flash operation event handler.
 *
 * @return @ref NRF_SUCCESS HAL initialized successfully.
 * @return @ref nrf_error "NRF_ERROR_..." HAL initialization failed.
 *
 */
uint32_t ser_app_hal_hw_init(ser_app_hal_flash_op_done_handler_t handler);

/**@brief Function for waiting for a given amount of time.
 *
 * @param[in] ms Number of milliseconds to wait.
 *
 */
void ser_app_hal_delay(uint32_t ms);

/**@brief Function for clearing the Connectivity Chip reset pin.
 *
 */
void ser_app_hal_nrf_reset_pin_clear(void);

/**@brief Function for setting the Connectivity Chip reset pin.
 *
 */
void ser_app_hal_nrf_reset_pin_set(void);


/**@brief Function for setting the SoftDevice event interrupt priority that serves the events incoming
 * from the Connectivity Chip.
 *
 * @note Serialization solution on the application side mimics a SoC solution where events are handled in
 * the interrupt context in two ways: either directly in the interrupt context or with a message being posted to
 * the scheduler. However, it is possible that the Application Chip does not use a dedicated interrupt
 * for connectivity events. In that case, this function can be left empty and
 * \ref ser_app_hal_nrf_evt_pending will directly call an interrupt handler function.
 */
void ser_app_hal_nrf_evt_irq_priority_set(void);

/**@brief Function for setting a pending interrupt for serving events incoming from the Connectivity Chip.
 *
 * @note The interrupt used for event from the Connectivity Chip mimics behavior of SoC and it is not
 * intended to be triggered by any hardware event. This function should be the only source of
 * interrupt triggering.
 */
void ser_app_hal_nrf_evt_pending(void);



#ifdef __cplusplus
}
#endif

#endif /* SER_APP_HAL_H_ */
/** @} */
