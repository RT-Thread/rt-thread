/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#ifndef NRF_DFU_TRIGGER_USB_H
#define NRF_DFU_TRIGGER_USB_H

#include "sdk_errors.h"

/**
 * @defgroup nrf_dfu_trigger_usb USB DFU trigger library
 * @ingroup app_common
 *
 * @brief @tagAPI52840 USB DFU trigger library is used to enter the bootloader and read the firmware version.
 *
 * @details See @ref lib_dfu_trigger_usb for additional documentation.
 * @{
 */

/**
 * @brief Function for initializing the USB DFU trigger library.
 *
 * @note  If the USB is also used for other purposes, then this function must be called after USB is
 *        initialized but before it is enabled. In this case, the configuration flag @ref
 *        NRF_DFU_TRIGGER_USB_USB_SHARED must be set to 1.
 *
 * @note  Calling this again after the first success has no effect and returns @ref NRF_SUCCESS.
 *
 * @note  If @ref APP_USBD_CONFIG_EVENT_QUEUE_ENABLE is on (1), USB events must be handled manually.
 *        See @ref app_usbd_event_queue_process.
 *
 * @retval NRF_SUCCESS  On successful initialization.
 * @return An error code on failure, for example if called at a wrong time.
 */
ret_code_t nrf_dfu_trigger_usb_init(void);

/** @} */

#endif //NRF_DFU_TRIGGER_USB_H
