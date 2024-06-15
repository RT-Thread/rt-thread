/**
 * \file
 *
 * \brief USB protocol implementation.
 *
 * This file contains the USB definitions and data structures provided by the
 * USB 2.0 specification.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 */

#define CONF_NO_ASSERT_CHECK

#include "usb_protocol.h"

#ifdef CONF_NO_ASSERT_CHECK
#define _param_error_check(cond)
#define _desc_len_check()                                                                                              \
	if (usb_desc_len(desc) < 2) {                                                                                      \
		/* Encounter an invalid descriptor. */                                                                         \
		return NULL;                                                                                                   \
	}
#else
#define _param_error_check(cond) ASSERT(cond)
#define _desc_len_check() ASSERT(usb_desc_len(desc) >= 2)
#endif

uint8_t *usb_find_desc(uint8_t *desc, uint8_t *eof, uint8_t type)
{
	_param_error_check(desc && eof && (desc < eof));

	while (desc < eof) {
		_desc_len_check();
		if (type == usb_desc_type(desc)) {
			return desc;
		}
		desc = usb_desc_next(desc);
	}
	return NULL;
}

uint8_t *usb_find_iface_after(uint8_t *desc, uint8_t *eof, uint8_t iface_n)
{
	_param_error_check(desc && eof && (desc < eof));

	while (desc < eof) {
		_desc_len_check();
		if (USB_DT_INTERFACE == usb_desc_type(desc)) {
			if (iface_n != desc[2]) {
				return desc;
			}
		}
		desc = usb_desc_next(desc);
	}
	return eof;
}

uint8_t *usb_find_ep_desc(uint8_t *desc, uint8_t *eof)
{
	_param_error_check(desc && eof && (desc < eof));

	while (desc < eof) {
		_desc_len_check();
		if (USB_DT_INTERFACE == usb_desc_type(desc)) {
			break;
		}
		if (USB_DT_ENDPOINT == usb_desc_type(desc)) {
			return desc;
		}
		desc = usb_desc_next(desc);
	}
	return NULL;
}

uint8_t *usb_find_cfg_desc(uint8_t *desc, uint8_t *eof, uint8_t cfg_value)
{
	_param_error_check(desc && eof && (desc < eof));

	desc = usb_find_desc(desc, eof, USB_DT_CONFIG);
	if (!desc) {
		return NULL;
	}
	while (desc < eof) {
		_desc_len_check();
		if (desc[1] != USB_DT_CONFIG) {
			break;
		}
		if (desc[5] == cfg_value) {
			return desc;
		}
		desc = usb_cfg_desc_next(desc);
	}
	return NULL;
}

uint8_t *usb_find_othspdcfg_desc(uint8_t *desc, uint8_t *eof, uint8_t cfg_value)
{
	_param_error_check(desc && eof && (desc < eof));

	desc = usb_find_desc(desc, eof, USB_DT_OTHER_SPEED_CONFIG);
	if (!desc) {
		return NULL;
	}
	while (desc < eof) {
		_desc_len_check();
		if (desc[1] != USB_DT_OTHER_SPEED_CONFIG) {
			break;
		}
		if (desc[5] == cfg_value) {
			return desc;
		}
		desc = usb_cfg_desc_next(desc);
	}
	return NULL;
}

uint8_t *usb_find_str_desc(uint8_t *desc, uint8_t *eof, uint8_t str_index)
{
	uint8_t i;

	_param_error_check(desc && eof && (desc < eof));

	for (i = 0; desc < eof;) {
		desc = usb_find_desc(desc, eof, USB_DT_STRING);
		if (desc) {
			_desc_len_check();
			if (i == str_index) {
				return desc;
			}
			i++;
			desc = usb_desc_next(desc);
		} else {
			return NULL;
		}
	}
	return NULL;
}
