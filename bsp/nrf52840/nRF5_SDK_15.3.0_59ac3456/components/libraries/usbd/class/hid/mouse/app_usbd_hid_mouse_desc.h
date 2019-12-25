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
#ifndef APP_USBD_HID_MOUSE_DESC_H__
#define APP_USBD_HID_MOUSE_DESC_H__

/**
 * @defgroup app_usbd_hid_mouse_desc USB HID mouse descriptors
 * @ingroup app_usbd_hid_mouse
 *
 * @brief @tagAPI52840 Module with types, definitions, and API used by the HID mouse class.
 * @{
 */

/**
 * @brief Initializer of interface descriptor for HID mouse class.
 *
 * @param interface_number Interface number.
 */
#define APP_USBD_HID_MOUSE_INTERFACE_DSC(interface_number)      \
        APP_USBD_HID_INTERFACE_DSC(interface_number,            \
                                   1,                           \
                                   APP_USBD_HID_SUBCLASS_BOOT,  \
                                   APP_USBD_HID_PROTO_MOUSE)

/**
 * @brief Initializer of HID descriptor for HID mouse class.
 *
 * @param ... Descriptor list.
 */
#define APP_USBD_HID_MOUSE_HID_DSC(...)     \
        APP_USBD_HID_HID_DSC(__VA_ARGS__)

/**
 * @brief Initializer of endpoint descriptor for HID mouse class.
 *
 * @param endpoint_number Endpoint number.
 */
#define APP_USBD_HID_MOUSE_EP_DSC(endpoint_number)  \
        APP_USBD_HID_EP_DSC(endpoint_number, 8, 1)



/**
 * @brief Example of USB HID mouse report descriptor for n button mouse.
 *
 * @param bcnt  Button count. Allowed values from 1 to 8.
 */
#define APP_USBD_HID_MOUSE_REPORT_DSC_BUTTON(bcnt) {                \
    0x05, 0x01,       /* Usage Page (Generic Desktop),       */     \
    0x09, 0x02,       /* Usage (Mouse),                      */     \
    0xA1, 0x01,       /*  Collection (Application),          */     \
    0x09, 0x01,       /*   Usage (Pointer),                  */     \
    0xA1, 0x00,       /*  Collection (Physical),             */     \
    0x05, 0x09,       /*     Usage Page (Buttons),           */     \
    0x19, 0x01,       /*     Usage Minimum (01),             */     \
    0x29, bcnt,       /*     Usage Maximum (bcnt),           */     \
    0x15, 0x00,       /*     Logical Minimum (0),            */     \
    0x25, 0x01,       /*     Logical Maximum (1),            */     \
    0x75, 0x01,       /*     Report Size (1),                */     \
    0x95, bcnt,       /*     Report Count (bcnt),            */     \
    0x81, 0x02,       /*     Input (Data, Variable, Absolute)*/     \
    0x75, (8-(bcnt)), /*     Report Size (8-(bcnt)),         */     \
    0x95, 0x01,       /*     Report Count (1),               */     \
    0x81, 0x01,       /*     Input (Constant),               */     \
    0x05, 0x01,       /*     Usage Page (Generic Desktop),   */     \
    0x09, 0x30,       /*     Usage (X),                      */     \
    0x09, 0x31,       /*     Usage (Y),                      */     \
    0x09, 0x38,       /*     Usage (Scroll),                 */     \
    0x15, 0x81,       /*     Logical Minimum (-127),         */     \
    0x25, 0x7F,       /*     Logical Maximum (127),          */     \
    0x75, 0x08,       /*     Report Size (8),                */     \
    0x95, 0x03,       /*     Report Count (3),               */     \
    0x81, 0x06,       /*     Input (Data, Variable, Relative)*/     \
    0xC0,         /*  End Collection,                        */     \
    0xC0,         /* End Collection                          */     \
}

 /** @} */

#endif /* APP_USBD_HID_MOUSE_DESC_H__ */
