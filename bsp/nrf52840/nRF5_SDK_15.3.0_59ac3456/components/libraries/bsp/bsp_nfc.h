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
/**@file
 *
 * @defgroup bsp_nfc NFC BSP Module
 * @{
 * @ingroup bsp
 *
 * @brief Module for setting the NFCT peripheral as a wakeup source.
 *
 * @details The application must notify this module before going into System OFF mode.
 * Based on this notification, the NFC BSP Module sets the NFCT peripheral as a wakeup source
 * through the Board Support Package. Additionally, any BSP Button can be configured to
 * generate BSP sleep events. This module is applicable only if NFCT is used exclusively for
 * wakeup. If NFCT is used for a different purpose, this module cannot be used.
 */

#ifndef BSP_NFC_H__
#define BSP_NFC_H__

#include <stdint.h>
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Function for initializing the NFC Button Module.
 *
 * Before calling this function, the BSP module must be initialized with buttons. The chosen
 * button is used to generate @ref BSP_EVENT_SLEEP events.
 *
 * @param[in]   sleep_button    Button ID used to generate @ref BSP_EVENT_SLEEP event.
 *
 * @retval      NRF_SUCCESS     If initialization was successful. Otherwise, a propagated error
 *                              code is returned.
 */
ret_code_t bsp_nfc_btn_init(uint32_t sleep_button);

/**@brief Function for deinitializing the NFC Button Module.
 *
 * Before calling this function, the BSP module must be initialized with buttons. The chosen
 * button is used to generate default @ref BSP_EVENT_DEFAULT events.
 *
 * @param[in]   sleep_button    Button ID used to restore default event generation.
 *
 * @retval      NRF_SUCCESS     If initialization was successful. Otherwise, a propagated error
 *                              code is returned.
 */
ret_code_t bsp_nfc_btn_deinit(uint32_t sleep_button);

/**@brief Function for setting up NFCT peripheral as wake-up source.
 *
 * This function must be called before going into System OFF mode.
 *
 * @note This function is only applicable if NFCT is used exclusively for wakeup.
 *       If NFCT is used for a different purpose, this function cannot be used.
 *
 * @retval      NRF_SUCCESS     If NFCT peripheral was prepared successfully. Otherwise,
 *                              a propagated error code is returned.
 */
ret_code_t bsp_nfc_sleep_mode_prepare(void);

#ifdef __cplusplus
}
#endif

#endif /* BSP_NFC_H__ */

/** @} */
