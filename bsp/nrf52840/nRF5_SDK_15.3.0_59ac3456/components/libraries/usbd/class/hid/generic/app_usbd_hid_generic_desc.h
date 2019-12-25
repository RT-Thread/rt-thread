/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#ifndef APP_USBD_HID_GENERIC_DESC_H__
#define APP_USBD_HID_GENERIC_DESC_H__

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup app_usbd_hid_generic_desc USB HID generic descriptors
 * @ingroup app_usbd_hid_generic
 *
 * @brief @tagAPI52840 Module with descriptors used by the HID generic class.
 * @{
 */

/**
 * @brief Initializer of interface descriptor for HID generic class.
 *
 * @param interface_number  Interface number.
 * @param endpoints_num     Number of endpoints.
 * @param subclass          Subclass type @ref app_usbd_hid_subclass_t.
 * @param protocol          Protocol type @ref app_usbd_hid_protocol_t.
 */
#define APP_USBD_HID_GENERIC_INTERFACE_DSC(interface_number,        \
                                           endpoints_num,           \
                                           subclass,                \
                                           protocol)                \
        APP_USBD_HID_INTERFACE_DSC(interface_number,                \
                                   endpoints_num,                   \
                                   subclass,                        \
                                   protocol)                        \

/**
 * @brief Initializer of HID descriptor for HID generic class.
 *
 * @param ...   Report descriptor item.
 */
#define APP_USBD_HID_GENERIC_HID_DSC(...)   \
        APP_USBD_HID_HID_DSC(__VA_ARGS__)
/**
 * @brief Initializer of endpoint descriptor for HID generic class.
 *
 * @param endpoint  Endpoint number.
 */
#define APP_USBD_HID_GENERIC_EP_DSC(endpoint) \
        APP_USBD_HID_EP_DSC(endpoint, NRF_DRV_USBD_EPSIZE, 1)



/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_HID_GENERIC_DESC_H__ */
