/*!
    \file    usbh_standard_hid.h
    \brief   header file for usbh_standard_hid.c

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef USBH_STANDARD_HID_H
#define USBH_STANDARD_HID_H

#include "usbh_hid_core.h"

//#define AZERTY_KEYBOARD
#define QWERTY_KEYBOARD

#define MOUSE_BUTTON_1                         0x01U                          /*!< mouse button 1 */
#define MOUSE_BUTTON_2                         0x02U                          /*!< mouse button 2 */
#define MOUSE_BUTTON_3                         0x04U                          /*!< mouse button 3 */

#define KBD_LEFT_CTRL                          0x01U                          /*!< keyboard left ctrl key */
#define KBD_LEFT_SHIFT                         0x02U                          /*!< keyboard left shift key */
#define KBD_LEFT_ALT                           0x04U                          /*!< keyboard left alt key */
#define KBD_LEFT_GUI                           0x08U                          /*!< keyboard left gui key */
#define KBD_RIGHT_CTRL                         0x10U                          /*!< keyboard right ctrl key */
#define KBD_RIGHT_SHIFT                        0x20U                          /*!< keyboard right shift key */
#define KBD_RIGHT_ALT                          0x40U                          /*!< keyboard right alt key */
#define KBD_RIGHT_GUI                          0x80U                          /*!< keyboard right gui key */

#define KBD_PRESSED_MAX_NUM                    6U                             /*!< keyboard pressed maximum number */

typedef struct _mouse_report_data {
    uint8_t x;                                                                /*!< X coordinate value */
    uint8_t y;                                                                /*!< Y coordinate value */
    uint8_t buttons[3];                                                       /*!< button buff */
} mouse_report_data;

typedef struct {
    uint8_t state;                                                            /*!< keyboard state */
    uint8_t lctrl;                                                            /*!< keyboard left ctrl */
    uint8_t lshift;                                                           /*!< keyboard left shift */
    uint8_t lalt;                                                             /*!< keyboard left alt */
    uint8_t lgui;                                                             /*!< keyboard left gui */
    uint8_t rctrl;                                                            /*!< keyboard right ctrl */
    uint8_t rshift;                                                           /*!< keyboard right shift */
    uint8_t ralt;                                                             /*!< keyboard right alt */
    uint8_t rgui;                                                             /*!< keyboard right gui */
    uint8_t keys[6];                                                          /*!< keyboard keys buff */
} hid_keybd_info;

/* function declarations */
/* initialize mouse */
void usr_mouse_init(void);
/* process mouse data */
void usr_mouse_process_data(mouse_report_data *data);
/* initialize mouse function */
usbh_status usbh_hid_mouse_init(usb_core_driver *udev, usbh_host *uhost);
/* decode mouse information */
usbh_status usbh_hid_mouse_decode(uint8_t *data);

/* initialize keyboard */
void usr_keybrd_init(void);
/* process keyboard data */
void usr_keybrd_process_data(uint8_t pbuf);
/* initialize the keyboard function */
usbh_status usbh_hid_keybrd_init(usb_core_driver *udev, usbh_host *uhost);
/* decode keyboard information */
usbh_status usbh_hid_keybrd_decode(uint8_t *data);

#endif /* USBH_STANDARD_HID_H */
