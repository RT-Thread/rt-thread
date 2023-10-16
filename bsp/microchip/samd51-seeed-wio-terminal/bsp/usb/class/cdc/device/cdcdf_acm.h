/**
 * \file
 *
 * \brief USB Device Stack CDC ACM Function Definition.
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

#ifndef USBDF_CDC_ACM_SER_H_
#define USBDF_CDC_ACM_SER_H_

#include "usbdc.h"
#include "usb_protocol_cdc.h"

/** CDC ACM Class Callback Type */
enum cdcdf_acm_cb_type { CDCDF_ACM_CB_READ, CDCDF_ACM_CB_WRITE, CDCDF_ACM_CB_LINE_CODING_C, CDCDF_ACM_CB_STATE_C };

/** CDC ACM Notify Line State Callback. */
typedef void (*cdcdf_acm_notify_state_t)(uint16_t);

/** CDC ACM Set Line Coding Callback. */
typedef bool (*cdcdf_acm_set_line_coding_t)(struct usb_cdc_line_coding *);

/**
 * \brief Initialize the USB CDC ACM Function Driver
 * \return Operation status.
 */
int32_t cdcdf_acm_init(void);

/**
 * \brief Deinitialize the USB CDC ACM Function Driver
 * \return Operation status.
 */
void cdcdf_acm_deinit(void);

/**
 * \brief USB CDC ACM Function Read Data
 * \param[in] buf Pointer to the buffer which receives data
 * \param[in] size the size of data to be received
 * \return Operation status.
 */
int32_t cdcdf_acm_read(uint8_t *buf, uint32_t size);

/**
 * \brief USB CDC ACM Function Write Data
 * \param[in] buf Pointer to the buffer which stores data
 * \param[in] size the size of data to be sent
 * \return Operation status.
 */
int32_t cdcdf_acm_write(uint8_t *buf, uint32_t size);

/**
 * \brief USB CDC ACM Stop the currnet data transfer
 */
void cdcdf_acm_stop_xfer(void);

/**
 * \brief USB CDC ACM Function Register Callback
 * \param[in] cb_type Callback type of CDC ACM Function
 * \param[in] func Pointer to callback function
 * \return Operation status.
 */
int32_t cdcdf_acm_register_callback(enum cdcdf_acm_cb_type cb_type, FUNC_PTR func);

/**
 * \brief Check whether CDC ACM Function is enabled
 * \return Operation status.
 * \return true CDC ACM Function is enabled
 * \return false CDC ACM Function is disabled
 */
bool cdcdf_acm_is_enabled(void);

/**
 * \brief Return the CDC ACM line coding structure start address
 * \return Pointer to USB CDC ACM line coding data.
 */
const struct usb_cdc_line_coding *cdcdf_acm_get_line_coding(void);

/**
 * \brief Return version
 */
uint32_t cdcdf_acm_get_version(void);

#endif /* USBDF_CDC_ACM_SER_H_ */
