/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#include "nrf_assert.h"
#include "app_error.h"
#include "ser_config.h"

#include "boards.h"

/** @file
 *
 * @defgroup ser_conn_error_handling Errors handling for the Connectivity Chip.
 * @{
 * @ingroup sdk_lib_serialization
 *
 * @brief   A module to handle the Connectivity Chip errors and warnings.
 *
 * @details This file contains definitions of functions used for handling the Connectivity Chip
 *          errors and warnings.
 */

/**@brief Function for handling the Connectivity Chip errors and warnings.
 *
 * @details This function will be called if the ASSERT macro in the connectivity application fails.
 *          Function declaration can be found in the app_error.h file.
 *
 * @param[in] error_code  Error code supplied to the handler.
 * @param[in] line_num    Line number where the handler is called.
 * @param[in] p_file_name Pointer to the file name.
 */

#include "app_util_platform.h"
#include "nrf_soc.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

// uint32_t m_error_code;
// uint32_t m_error_line_num;
// const uint8_t *m_p_error_file_name;

/*lint -save -e14 */
void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    // disable INTs
    CRITICAL_REGION_ENTER();

    NRF_LOG_ERROR("Fatal error");
    NRF_LOG_FINAL_FLUSH();

    #if LEDS_NUMBER > 0

    /* Light a LED on error or warning. */
    // nrf_gpio_cfg_output(SER_CONN_ASSERT_LED_PIN);
    // nrf_gpio_pin_set(SER_CONN_ASSERT_LED_PIN);

    #endif

    // m_p_error_file_name = p_file_name;
    // m_error_code = error_code;
    // m_error_line_num = line_num;

    /* Do not reset when warning. */
    if (SER_WARNING_CODE != id)
    {
        /* This call can be used for debug purposes during application development.
        * @note CAUTION: Activating code below will write the stack to flash on an error.
        * This function should NOT be used in a final product.
        * It is intended STRICTLY for development/debugging purposes.
        * The flash write will happen EVEN if the radio is active, thus interrupting any communication.
        * Use with care. Un-comment the line below to use. */

        /* ble_debug_assert_handler(error_code, line_num, p_file_name); */

#ifndef DEBUG
        /* Reset the chip. Should be used in the release version. */
        NVIC_SystemReset();
#else   /* Debug version. */
        /* To be able to see function parameters in a debugger. */
        uint32_t temp = 1;
        while (temp);
#endif

    }

    CRITICAL_REGION_EXIT();
}
/*lint -restore */


/**@brief Callback function for asserts in the SoftDevice.
 *
 * @details This function will be called if the ASSERT macro in the SoftDevice fails. Function
 *          declaration can be found in the nrf_assert.h file.
 *
 * @param[in] line_num    Line number of the failing ASSERT call.
 * @param[in] p_file_name File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(SER_SD_ERROR_CODE, line_num, p_file_name);
}
/** @} */
