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
/**@file
 *
 * @defgroup bsp_btn_ant BSP: ANT Button Module
 * @{
 * @ingroup bsp
 *
 * @brief Module for controlling ANT behavior through button actions.
 *
 * @details The application must propagate ANT events to the ANT Button Module.
 * Based on these events, the ANT Button Module configures the Board Support Package
 * to generate BSP events for certain button actions. These BSP events should then be
 * handled by the application's BSP event handler.
 *
 */

#ifndef BSP_BTN_ANT_H__
#define BSP_BTN_ANT_H__

#include <stdint.h>
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

 /**@brief Function for initializing the ANT Button Module.
 *
 * Before calling this function, the BSP module must be initialized with buttons.
 *
 * @param[in] channel       ANT channel number.
 * @param[in] channel_type  ANT channel type (see Assign Channel Parameters in ant_parameters.h: @ref ant_parameters).
 *
 * @retval NRF_SUCCESS  If initialization was successful. Otherwise, a propagated error code is
 *                      returned.
 */
ret_code_t bsp_btn_ant_init(uint8_t channel, uint8_t channel_type);

/**@brief Function for setting up wakeup buttons before going into sleep mode.
 *
 * @retval NRF_SUCCESS  If the buttons were prepared successfully. Otherwise, a propagated error
 *                      code is returned.
 */
ret_code_t bsp_btn_ant_sleep_mode_prepare(void);


#ifdef __cplusplus
}
#endif

#endif /* BSP_BTN_ANT_H__ */

/** @} */
