/**
 * \file
 *
 * \brief USB Device Stack Core Layer Definition.
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

#ifndef _USB_USBDC_H_
#define _USB_USBDC_H_

#include "usb_includes.h"
#include "usb_protocol.h"
#include "hal_usb_device.h"
#include "usbd_config.h"

/** USB device states. */
enum usbd_state {
	USBD_S_OFF     = 0,
	USBD_S_POWER   = 1,
	USBD_S_DEFAULT = 2,
	USBD_S_ADDRESS = 3,
	USBD_S_CONFIG  = 4,
	USBD_S_SUSPEND = 0x10
};

/** USB device core handler type. */
enum usbdc_handler_type { USBDC_HDL_SOF, USBDC_HDL_REQ, USBDC_HDL_CHANGE };

/** USB device core change notification type. */
enum usbdc_change_type {
	/** Change of connection, detected by vbus. */
	USBDC_C_CONN,
	/** Change of state, by RESET, SetAddress(), SetConfig(). */
	USBDC_C_STATE,
	/** Change of power. */
	USBDC_C_POWER,
	/** Change of remote wakeup setting. */
	USBDC_C_REMOTE_WAKEUP
};

/** Power change. */
enum usbdc_power_type { USBDC_ACTIVE, USBDC_SLEEP, USBDC_SUSPEND };

/** USB device general function control code. */
enum usbdf_control {
	/** Enable the function.
	 *  int32_t ctrl(usbdf, USBDF_ENABLE, struct usbd_descriptors *desc);
	 *  Parameter holds interface descriptor and
	 *  configuration descriptor end position.
	 */
	USBDF_ENABLE,
	/** Disable the function.
	 *  int32_t ctrl(usbdf, USBDF_DISABLE, struct usbd_descriptors *desc);
	 *  Parameter holds interface descriptor and
	 *  configuration descriptor end position.
	 *  Input NULL to force disable the function anyway.
	 */
	USBDF_DISABLE,
	/** Get interface alternate setting.
	 *  int32_t ctrl(usbdf, USBDF_GET_IFACE, struct usb_req *req);
	 *  Parameter holds interface number who should return
	 *  the alternate setting.
	 */
	USBDF_GET_IFACE
};

/** Describes a list of USB descriptors. */
struct usbd_descriptors {
	/** Pointer to Start of Descriptors. */
	uint8_t *sod;
	/** Pointer to End of Descriptors. */
	uint8_t *eod;
};

/** Describes the USB device core descriptors. */
struct usbdc_descriptors {
	struct usbd_descriptors *ls_fs;
#if CONF_USBD_HS_SP
	struct usbd_descriptors *hs;
#endif
};

/** Describes a list of core handler descriptor. */
struct usbdc_handler {
	/** Pointer to next handler. */
	struct usbdc_handler *next;
	/** Pointer to handler function. */
	FUNC_PTR func;
};

/** Forward declaration for USB device function driver. */
struct usbdf_driver;

/** SOF handling function. */
typedef void (*usbdc_sof_cb_t)(void);

/** REQ handling function. */
typedef int32_t (*usbdc_req_cb_t)(uint8_t ep, struct usb_req *req, enum usb_ctrl_stage stage);

/** Change notification callback function. */
typedef void (*usbdc_change_cb_t)(enum usbdc_change_type change, uint32_t value);

/** Control function for USB device general function driver. */
typedef int32_t (*usbdf_control_cb_t)(struct usbdf_driver *drv, enum usbdf_control ctrl, void *param);

/** USB device general function driver descriptor. */
struct usbdf_driver {
	/** Pointer to next function.*/
	struct usbdf_driver *next;
	/** Pointer to control function.*/
	usbdf_control_cb_t ctrl;
	/** Pointer to function driver specific data. */
	void *func_data;
};

/**
 * \brief Register the handler
 * \param[in] type USB device core handler type.
 * \param[in] h Pointer to usb device core handler.
 */
void usbdc_register_handler(enum usbdc_handler_type type, const struct usbdc_handler *h);

/**
 * \brief Unregister the handler
 * \param[in] type USB device core handler type.
 * \param[in] h Pointer to usb device core handler.
 */
void usbdc_unregister_handler(enum usbdc_handler_type type, const struct usbdc_handler *h);

/**
 * \brief Initialize the USB device core driver
 * \param[in] ctrl_buf Pointer to a buffer to be used by usb device ctrl endpoint
 *  Note: the size of ctrl_buf should not be less than the size of EP0
 * \return Operation status.
 */
int32_t usbdc_init(uint8_t *ctrl_buf);

/**
 * \brief Deinitialize the USB device core driver
 * \return Operation status.
 */
int32_t usbdc_deinit(void);

/**
 * \brief Register function support of a USB device function
 * \param[in] func Pointer to usb device function driver structure
 */
void usbdc_register_function(struct usbdf_driver *func);

/**
 * \brief Unregister function support of a USB device function
 * \param[in] func Pointer to usb device function driver structure
 */
void usbdc_unregister_function(struct usbdf_driver *func);

/**
 * \brief Validate the descriptors
 * \param[in] desces Pointer to usb device core descriptors
 * \return Operation status.
 */
int32_t usbdc_validate_desces(struct usbd_descriptors *desces);

/**
 * \brief Issue USB device data transfer
 * \param[in] ep endpointer address.
 * \param[in] buf Pointer to data transfer buffer.
 * \param[in] size the size of data transfer.
 * \param[in] zlp flag to indicate zero length packet.
 * \return Operation status.
 */
int32_t usbdc_xfer(uint8_t ep, uint8_t *buf, uint32_t size, bool zlp);

/**
 * \brief Start the USB device driver with specific descriptors set
 * \param[in] desces Pointer to usb device core descriptors (FS/LS),
 *                   or pointer to array of core descriptors (HS), the
 *                   very first one includes device descriptor, FS/LS
 *                   configuration descriptor, string descriptor, and
 *                   may include device qualifier and other speed
 *                   configuration descriptor; the second one includes
 *                   high speed used descriptors.
 *                   Note that string descriptor should be included in
 *                   first place.
 * \return Operation status.
 */
int32_t usbdc_start(struct usbd_descriptors *desces);

/**
 * \brief Stop the USB device driver
 * \return Operation status.
 */
int32_t usbdc_stop(void);

/**
 * \brief Attach the USB device to host
 */
void usbdc_attach(void);

/**
 * \brief Detach the USB device from host
 */
void usbdc_detach(void);

/**
 * \brief Send remote wakeup to host
 */
void usbdc_remotewakeup(void);

/**
 * \brief Return USB device ctrl end pointer buffer start address
 */
uint8_t *usbdc_get_ctrl_buffer(void);

/**
 * \brief Return current USB state
 */
uint8_t usbdc_get_state(void);

/**
 * \brief Return version
 */
uint32_t usbdc_get_version(void);

#endif /* USBDC_H_ */
