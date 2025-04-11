/*!
    \file    usbh_standard_hid.c
    \brief   USB host HID keyboard and mouse driver

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

#include "usbh_standard_hid.h"

mouse_report_data mouse_info;
hid_keybd_info keybd_info;

__ALIGN_BEGIN uint8_t hid_mouse_info[8] __ALIGN_END = {0U};
__ALIGN_BEGIN uint32_t keybd_report_data[2] __ALIGN_END;

/* local constants */
static const uint8_t kbd_codes[] = {
    0,      0,      0,      0,      31,     50,     48,     33,
    19,     34,     35,     36,     24,     37,     38,     39,         /* 0x00 - 0x0F */
    52,     51,     25,     26,     17,     20,     32,     21,
    23,     49,     18,     47,     22,     46,     2,      3,          /* 0x10 - 0x1F */
    4,      5,      6,      7,      8,      9,      10,     11,
    43,     110,    15,     16,     61,     12,     13,     27,         /* 0x20 - 0x2F */
    28,     29,     42,     40,     41,     1,      53,     54,
    55,     30,     112,    113,    114,    115,    116,    117,        /* 0x30 - 0x3F */
    118,    119,    120,    121,    122,    123,    124,    125,
    126,    75,     80,     85,     76,     81,     86,     89,         /* 0x40 - 0x4F */
    79,     84,     83,     90,     95,     100,    105,    106,
    108,    93,     98,     103,    92,     97,     102,    91,         /* 0x50 - 0x5F */
    96,     101,    99,     104,    45,     129,    0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,          /* 0x60 - 0x6F */
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,          /* 0x70 - 0x7F */
    0,      0,      0,      0,      0,      107,    0,      56,
    0,      0,      0,      0,      0,      0,      0,      0,          /* 0x80 - 0x8F */
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,          /* 0x90 - 0x9F */
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,          /* 0xA0 - 0xAF */
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,          /* 0xB0 - 0xBF */
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,          /* 0xC0 - 0xCF */
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,          /* 0xD0 - 0xDF */
    58,     44,     60,     127,    64,     57,     62,     128         /* 0xE0 - 0xE7 */
};

#ifdef QWERTY_KEYBOARD

static const int8_t kbd_key[] = {
    '\0',   '`',    '1',    '2',    '3',    '4',    '5',    '6',
    '7',    '8',    '9',    '0',    '-',    '=',    '\0',   '\r',
    '\t',   'q',    'w',    'e',    'r',    't',    'y',    'u',
    'i',    'o',    'p',    '[',    ']',    '\\',
    '\0',   'a',    's',    'd',    'f',    'g',    'h',    'j',
    'k',    'l',    ';',    '\'',   '\0',   '\n',
    '\0',   '\0',   'z',    'x',    'c',    'v',    'b',    'n',
    'm',    ',',    '.',    '/',    '\0',   '\0',
    '\0',   '\0',   '\0',   ' ',    '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\r',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '7',    '4',    '1',
    '\0',   '/',    '8',    '5',    '2',
    '0',    '*',    '9',    '6',    '3',
    '.',    '-',    '+',    '\0',   '\n',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0'
};

static const int8_t kbd_key_shift[] = {
    '\0',   '~',    '!',    '@',    '#',    '$',    '%',    '^',    '&',    '*',    '(',    ')',
    '_',    '+',    '\0',   '\0',   '\0',   'Q',    'W',    'E',    'R',    'T',    'Y',    'U',
    'I',    'O',    'P',    '{',    '}',    '|',    '\0',   'A',    'S',    'D',    'F',    'G',
    'H',    'J',    'K',    'L',    ':',    '"',    '\0',   '\n',   '\0',   '\0',   'Z',    'X',
    'C',    'V',    'B',    'N',    'M',    '<',    '>',    '?',    '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0'
};

#else

static const int8_t kbd_key[] = {
    '\0',   '`',    '1',    '2',    '3',    '4',    '5',    '6',    '7',    '8',    '9',    '0',
    '-',    '=',    '\0',   '\r',   '\t',   'a',    'z',    'e',    'r',    't',    'y',    'u',
    'i',    'o',    'p',    '[',    ']',    '\\',   '\0',   'q',    's',    'd',    'f',    'g',
    'h',    'j',    'k',    'l',    'm',    '\0',   '\0',   '\n',   '\0',   '\0',   'w',    'x',
    'c',    'v',    'b',    'n',    ',',    ';',    ':',    '!',    '\0',   '\0',   '\0',   '\0',
    '\0',   ' ',    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\r',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '7',    '4',    '1',    '\0',   '/',
    '8',    '5',    '2',    '0',    '*',    '9',    '6',    '3',    '.',    '-',    '+',    '\0',
    '\n',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0'
};

static const int8_t kbd_key_shift[] = {
    '\0',   '~',    '!',    '@',    '#',    '$',    '%',    '^',    '&',    '*',    '(',    ')',    '_',
    '+',    '\0',   '\0',   '\0',   'A',    'Z',    'E',    'R',    'T',    'Y',    'U',    'I',    'O',
    'P',    '{',    '}',    '*',    '\0',   'Q',    'S',    'D',    'F',    'G',    'H',    'J',    'K',
    'L',    'M',    '%',    '\0',   '\n',   '\0',   '\0',   'W',    'X',    'C',    'V',    'B',    'N',
    '?',    '.',    '/',    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',
    '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0',   '\0'
};

#endif /* QWERTY_KEYBOARD */

/*!
    \brief      initialize the mouse function
    \param[in]  udev: pointer to USB core instance
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     none
*/
usbh_status usbh_hid_mouse_init(usb_core_driver *udev, usbh_host *uhost)
{
    usbh_hid_handler *hid = (usbh_hid_handler *)uhost->active_class->class_data;

    mouse_info.x = 0U;
    mouse_info.y = 0U;
    mouse_info.buttons[0] = 0U;
    mouse_info.buttons[1] = 0U;
    mouse_info.buttons[2] = 0U;

    if(hid->len > sizeof(hid_mouse_info)) {
        hid->len = sizeof(hid_mouse_info);
    }

    hid->pdata = (uint8_t *)(void *)hid_mouse_info;

    usr_mouse_init();

    return USBH_OK;
}

/*!
    \brief      decode mouse information
    \param[in]  data: pointer to input data
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_hid_mouse_decode(uint8_t *data)
{
    mouse_info.buttons[0] = data[0] & MOUSE_BUTTON_1;
    mouse_info.buttons[1] = data[0] & MOUSE_BUTTON_2;
    mouse_info.buttons[2] = data[0] & MOUSE_BUTTON_3;

    mouse_info.x = data[1];
    mouse_info.y = data[2];

    /* handle mouse data position */
    usr_mouse_process_data(&mouse_info);

    return USBH_FAIL;
}

/*!
    \brief      initialize the keyboard function
    \param[in]  udev: pointer to USB core instance
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_hid_keybrd_init(usb_core_driver *udev, usbh_host *uhost)
{
    usbh_hid_handler *hid = (usbh_hid_handler *)uhost->active_class->class_data;

    keybd_info.lctrl = keybd_info.lshift = 0U;
    keybd_info.lalt  = keybd_info.lgui   = 0U;
    keybd_info.rctrl = keybd_info.rshift = 0U;
    keybd_info.ralt  = keybd_info.rgui   = 0U;

    for(uint32_t x = 0U; x < (sizeof(keybd_report_data) / sizeof(uint32_t)); x++) {
        keybd_report_data[x] = 0U;
    }

    if(hid->len > (sizeof(keybd_report_data) / sizeof(uint32_t))) {
        hid->len = (sizeof(keybd_report_data) / sizeof(uint32_t));
    }

    hid->pdata = (uint8_t *)(void *)keybd_report_data;

    /* call user initialization*/
    usr_keybrd_init();

    return USBH_OK;
}

/*!
    \brief      get ASCII code
    \param[in]  info: keyboard information
    \param[out] none
    \retval     output
*/
uint8_t usbh_hid_ascii_code_get(hid_keybd_info *info)
{
    uint8_t output = 0U;

    if((1U == info->lshift) || (info->rshift)) {
        output = kbd_key_shift[kbd_codes[info->keys[0]]];
    } else {
        output = kbd_key[kbd_codes[info->keys[0]]];
    }

    return output;
}

/*!
    \brief      decode keyboard information
    \param[in]  udev: pointer to USB core instance
    \param[in]  uhost: pointer to USB host
    \param[out] none
    \retval     operation status
*/
usbh_status usbh_hid_keybrd_decode(uint8_t *data)
{
    uint8_t output = 0U;

    keybd_info.lshift = data[0] & KBD_LEFT_SHIFT;
    keybd_info.rshift = data[0] & KBD_RIGHT_SHIFT;

    keybd_info.keys[0] = data[2];

    if(keybd_info.lshift || keybd_info.rshift) {
        output = kbd_key_shift[kbd_codes[keybd_info.keys[0]]];
    } else {
        output = kbd_key[kbd_codes[keybd_info.keys[0]]];
    }

    if(0U != output) {
        usr_keybrd_process_data(output);
    }

    return USBH_OK;
}
