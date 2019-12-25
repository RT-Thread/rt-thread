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
#ifndef APP_USBD_HID_KBD_DESC_H__
#define APP_USBD_HID_KBD_DESC_H__

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup app_usbd_hid_kbd_desc USB HID keyboard descriptors
 * @ingroup app_usbd_hid_kbd
 *
 * @brief @tagAPI52840 Module with types, definitions, and API used by the HID keyboard class.
 * @{
 */

/**
 * @brief Initializer of interface descriptor for HID keyboard class.
 *
 * @param interface_number  Interface number.
 */
#define APP_USBD_HID_KBD_INTERFACE_DSC(interface_number)            \
        APP_USBD_HID_INTERFACE_DSC(interface_number,                \
                                   1,                               \
                                   APP_USBD_HID_SUBCLASS_BOOT,      \
                                   APP_USBD_HID_PROTO_KEYBOARD)

/**
 * @brief Initializer of HID descriptor for HID keyboard class.
 *
 * @param ...   Report descriptor item.
 */
#define APP_USBD_HID_KBD_HID_DSC(...)       \
        APP_USBD_HID_HID_DSC(__VA_ARGS__)
/**
 * @brief Initializer of endpoint descriptor for HID keyboard class.
 *
 * @param endpoint  Endpoint number.
 */
#define APP_USBD_HID_KBD_EP_DSC(endpoint)   \
        APP_USBD_HID_EP_DSC(endpoint, 8, 1)


/**
 * @brief Example of USB HID keyboard report descriptor.
 *
 */
#define APP_USBD_HID_KBD_REPORT_DSC() {                                                    \
        0x05, 0x01,                    /* USAGE_PAGE (Generic Desktop)                   */\
        0x09, 0x06,                    /* USAGE (Keyboard)                               */\
        0xa1, 0x01,                    /* COLLECTION (Application)                       */\
        0x05, 0x07,                    /*   USAGE_PAGE (Keyboard)                        */\
        0x19, 0xe0,                    /*   USAGE_MINIMUM (Keyboard LeftControl)         */\
        0x29, 0xe7,                    /*   USAGE_MAXIMUM (Keyboard Right GUI)           */\
        0x15, 0x00,                    /*   LOGICAL_MINIMUM (0)                          */\
        0x25, 0x01,                    /*   LOGICAL_MAXIMUM (1)                          */\
        0x75, 0x01,                    /*   REPORT_SIZE (1)                              */\
        0x95, 0x08,                    /*   REPORT_COUNT (8)                             */\
        0x81, 0x02,                    /*   INPUT (Data,Var,Abs)                         */\
        0x95, 0x01,                    /*   REPORT_COUNT (1)                             */\
        0x75, 0x08,                    /*   REPORT_SIZE (8)                              */\
        0x81, 0x03,                    /*   INPUT (Cnst,Var,Abs)                         */\
        0x95, 0x05,                    /*   REPORT_COUNT (5)                             */\
        0x75, 0x01,                    /*   REPORT_SIZE (1)                              */\
        0x05, 0x08,                    /*   USAGE_PAGE (LEDs)                            */\
        0x19, 0x01,                    /*   USAGE_MINIMUM (Num Lock)                     */\
        0x29, 0x05,                    /*   USAGE_MAXIMUM (Kana)                         */\
        0x91, 0x02,                    /*   OUTPUT (Data,Var,Abs)                        */\
        0x95, 0x01,                    /*   REPORT_COUNT (1)                             */\
        0x75, 0x03,                    /*   REPORT_SIZE (3)                              */\
        0x91, 0x03,                    /*   OUTPUT (Cnst,Var,Abs)                        */\
        0x95, 0x06,                    /*   REPORT_COUNT (6)                             */\
        0x75, 0x08,                    /*   REPORT_SIZE (8)                              */\
        0x15, 0x00,                    /*   LOGICAL_MINIMUM (0)                          */\
        0x25, 0x65,                    /*   LOGICAL_MAXIMUM (101)                        */\
        0x05, 0x07,                    /*   USAGE_PAGE (Keyboard)                        */\
        0x19, 0x00,                    /*   USAGE_MINIMUM (Reserved (no event indicated))*/\
        0x29, 0x65,                    /*   USAGE_MAXIMUM (Keyboard Application)         */\
        0x81, 0x00,                    /*   INPUT (Data,Ary,Abs)                         */\
        0xc0                           /* END_COLLECTION                                 */\
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_HID_KBD_DESC_H__ */
