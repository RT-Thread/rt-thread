/*!
    \file    usbh_standard_hid.h
    \brief   header file for usbh_standard_hid.c

    \version 2020-08-01, V3.0.0, firmware for GD32F4xx
    \version 2022-03-09, V3.1.0, firmware for GD32F4xx
    \version 2022-06-30, V3.2.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

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

#ifndef __USBH_STANDARD_HID_H
#define __USBH_STANDARD_HID_H

#include "usb_conf.h"
#include "usbh_hid_core.h"

//#define AZERTY_KEYBOARD
#define QWERTY_KEYBOARD

#define MOUSE_BUTTON_1                         0x01U
#define MOUSE_BUTTON_2                         0x02U
#define MOUSE_BUTTON_3                         0x04U

#define KBD_LEFT_CTRL                          0x01U
#define KBD_LEFT_SHIFT                         0x02U
#define KBD_LEFT_ALT                           0x04U
#define KBD_LEFT_GUI                           0x08U
#define KBD_RIGHT_CTRL                         0x10U
#define KBD_RIGHT_SHIFT                        0x20U
#define KBD_RIGHT_ALT                          0x40U
#define KBD_RIGHT_GUI                          0x80U

#define KBD_PRESSED_MAX_NUM                    6U

typedef struct _hid_mouse_info
{
    uint8_t x;
    uint8_t y;
    uint8_t buttons[3];
} hid_mouse_info;

typedef struct
{
    uint8_t state;
    uint8_t lctrl;
    uint8_t lshift;
    uint8_t lalt;
    uint8_t lgui;
    uint8_t rctrl;
    uint8_t rshift;
    uint8_t ralt;
    uint8_t rgui;
    uint8_t keys[6];
} hid_keybd_info;

/* function declarations */
/* initialize mouse */
void usr_mouse_init (void);
/* process mouse data */
void usr_mouse_process_data (hid_mouse_info *data);
/* initialize mouse function */
usbh_status usbh_hid_mouse_init (usb_core_driver *udev, usbh_host *uhost);
/* decode mouse information */
usbh_status usbh_hid_mouse_decode(uint8_t *data);

/* initialize keyboard */
void usr_keybrd_init (void);
/* process keyboard data */
void usr_keybrd_process_data (uint8_t pbuf);
/* initialize the keyboard function */
usbh_status usbh_hid_keybrd_init (usb_core_driver *udev, usbh_host *uhost);
/* decode keyboard information */
usbh_status usbh_hid_keybrd_decode (uint8_t *data);

#endif /* __USBH_STANDARD_HID_H */
