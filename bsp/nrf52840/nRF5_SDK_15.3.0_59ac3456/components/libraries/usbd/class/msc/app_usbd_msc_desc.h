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
#ifndef APP_USBD_MSC_DESC_H__
#define APP_USBD_MSC_DESC_H__

#include "app_usbd_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_msc_desc USB MSC descriptors
 * @ingroup app_usbd_msc
 *
 * @brief @tagAPI52840 Descriptors for the USB MSC class.
 * @{
 */

/**
 * @brief Initializer of interface descriptor for MSC class.
 *
 * @param interface_number Interface number.
 * @param subclass         Subclass, @ref app_usbd_msc_subclass_t
 * @param protocol         Protocol, @ref app_usbd_msc_protocol_t
 * */
#define APP_USBD_MSC_INTERFACE_DSC(interface_number, subclass, protocol)                \
    /*.bLength =            */ sizeof(app_usbd_descriptor_iface_t),                     \
    /*.bDescriptorType =    */ APP_USBD_DESCRIPTOR_INTERFACE,                           \
    /*.bInterfaceNumber =   */ interface_number,                                        \
    /*.bAlternateSetting =  */ 0x00,                                                    \
    /*.bNumEndpoints =      */ 2,                                                       \
    /*.bInterfaceClass =    */ APP_USBD_MSC_CLASS,                                      \
    /*.bInterfaceSubClass = */ subclass,                                                \
    /*.bInterfaceProtocol = */ protocol,                                                \
    /*.iInterface = 0,      */ 0x00,                                                    \


/**
 * @brief Initializer of endpoint descriptors for MSC class.
 *
 * @param endpoint_in   IN endpoint.
 * @param endpoint_out  OUT endpoint.
 * @param ep_size       Endpoint size.
 * */
#define APP_USBD_MSC_EP_DSC(endpoint_in, endpoint_out, ep_size)               \
    /*.bLength =          */ sizeof(app_usbd_descriptor_ep_t),                \
    /*.bDescriptorType =  */ APP_USBD_DESCRIPTOR_ENDPOINT,                    \
    /*.bEndpointAddress = */ endpoint_in,                                     \
    /*.bmAttributes =     */ APP_USBD_DESCRIPTOR_EP_ATTR_TYPE_BULK,           \
    /*.wMaxPacketSize =   */ APP_USBD_U16_TO_RAW_DSC(ep_size),                \
    /*.bInterval =        */ 0,                                               \
    /*.bLength =          */ sizeof(app_usbd_descriptor_ep_t),                \
    /*.bDescriptorType =  */ APP_USBD_DESCRIPTOR_ENDPOINT,                    \
    /*.bEndpointAddress = */ endpoint_out,                                    \
    /*.bmAttributes =     */ APP_USBD_DESCRIPTOR_EP_ATTR_TYPE_BULK,           \
    /*.wMaxPacketSize =   */ APP_USBD_U16_TO_RAW_DSC(ep_size),                \
    /*.bInterval =        */ 0,                                               \


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_MSC_DESC_H__ */
