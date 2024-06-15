/**
 * \file
 *
 * \brief USB Device Stack CDC ACM Function Descriptor Setting.
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

#ifndef USBDF_CDC_ACM_DESC_H_
#define USBDF_CDC_ACM_DESC_H_

#include "usb_protocol.h"
#include "usb_protocol_cdc.h"
#include "usbd_config.h"

#define CDCD_ACM_DEV_DESC                                                                                              \
	USB_DEV_DESC_BYTES(CONF_USB_CDCD_ACM_BCDUSB,                                                                       \
	                   0x02,                                                                                           \
	                   0x00,                                                                                           \
	                   0x00,                                                                                           \
	                   CONF_USB_CDCD_ACM_BMAXPKSZ0,                                                                    \
	                   CONF_USB_CDCD_ACM_IDVENDER,                                                                     \
	                   CONF_USB_CDCD_ACM_IDPRODUCT,                                                                    \
	                   CONF_USB_CDCD_ACM_BCDDEVICE,                                                                    \
	                   CONF_USB_CDCD_ACM_IMANUFACT,                                                                    \
	                   CONF_USB_CDCD_ACM_IPRODUCT,                                                                     \
	                   CONF_USB_CDCD_ACM_ISERIALNUM,                                                                   \
	                   CONF_USB_CDCD_ACM_BNUMCONFIG)

#define CDCD_ACM_DEV_QUAL_DESC                                                                                         \
	USB_DEV_QUAL_DESC_BYTES(                                                                                           \
	    CONF_USB_CDCD_ACM_BCDUSB, 0x02, 0x00, 0x00, CONF_USB_CDCD_ACM_BMAXPKSZ0, CONF_USB_CDCD_ACM_BNUMCONFIG)

#define CDCD_ACM_CFG_DESC                                                                                              \
	USB_CONFIG_DESC_BYTES(67,                                                                                          \
	                      2,                                                                                           \
	                      CONF_USB_CDCD_ACM_BCONFIGVAL,                                                                \
	                      CONF_USB_CDCD_ACM_ICONFIG,                                                                   \
	                      CONF_USB_CDCD_ACM_BMATTRI,                                                                   \
	                      CONF_USB_CDCD_ACM_BMAXPOWER)

#define CDCD_ACM_OTH_SPD_CFG_DESC                                                                                      \
	USB_OTH_SPD_CFG_DESC_BYTES(67,                                                                                     \
	                           2,                                                                                      \
	                           CONF_USB_CDCD_ACM_BCONFIGVAL,                                                           \
	                           CONF_USB_CDCD_ACM_ICONFIG,                                                              \
	                           CONF_USB_CDCD_ACM_BMATTRI,                                                              \
	                           CONF_USB_CDCD_ACM_BMAXPOWER)

#define CDCD_ACM_COMM_IFACE_DESCES                                                                                     \
	USB_IFACE_DESC_BYTES(CONF_USB_CDCD_ACM_COMM_BIFCNUM,                                                               \
	                     CONF_USB_CDCD_ACM_COMM_BALTSET,                                                               \
	                     1,                                                                                            \
	                     0x2,                                                                                          \
	                     0x2,                                                                                          \
	                     0x0,                                                                                          \
	                     CONF_USB_CDCD_ACM_COMM_IIFC),                                                                 \
	    USB_CDC_HDR_DESC_BYTES(0x1001), USB_CDC_CALL_MGMT_DESC_BYTES(0x01, 0x00), USB_CDC_ACM_DESC_BYTES(0x02),        \
	    USB_CDC_UNION_DESC_BYTES(CONF_USB_CDCD_ACM_COMM_BIFCNUM, 0x01),                                                \
	    USB_ENDP_DESC_BYTES(CONF_USB_CDCD_ACM_COMM_INT_EPADDR,                                                         \
	                        3,                                                                                         \
	                        CONF_USB_CDCD_ACM_COMM_INT_MAXPKSZ,                                                        \
	                        CONF_USB_CDCD_ACM_COMM_INT_INTERVAL)

#define CDCD_ACM_DATA_IFACE_DESCES                                                                                     \
	USB_IFACE_DESC_BYTES(CONF_USB_CDCD_ACM_DATA_BIFCNUM,                                                               \
	                     CONF_USB_CDCD_ACM_DATA_BALTSET,                                                               \
	                     2,                                                                                            \
	                     0x0A,                                                                                         \
	                     0x0,                                                                                          \
	                     0x0,                                                                                          \
	                     CONF_USB_CDCD_ACM_DATA_IIFC),                                                                 \
	    USB_ENDP_DESC_BYTES(CONF_USB_CDCD_ACM_DATA_BULKOUT_EPADDR, 2, CONF_USB_CDCD_ACM_DATA_BULKOUT_MAXPKSZ, 0),      \
	    USB_ENDP_DESC_BYTES(CONF_USB_CDCD_ACM_DATA_BULKIN_EPADDR, 2, CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ, 0)

#define CDCD_ACM_DATA_IFACE_DESCES_HS                                                                                  \
	USB_IFACE_DESC_BYTES(CONF_USB_CDCD_ACM_DATA_BIFCNUM,                                                               \
	                     CONF_USB_CDCD_ACM_DATA_BALTSET,                                                               \
	                     2,                                                                                            \
	                     0x0A,                                                                                         \
	                     0x0,                                                                                          \
	                     0x0,                                                                                          \
	                     CONF_USB_CDCD_ACM_DATA_IIFC),                                                                 \
	    USB_ENDP_DESC_BYTES(CONF_USB_CDCD_ACM_DATA_BULKOUT_EPADDR, 2, CONF_USB_CDCD_ACM_DATA_BULKOUT_MAXPKSZ_HS, 0),   \
	    USB_ENDP_DESC_BYTES(CONF_USB_CDCD_ACM_DATA_BULKIN_EPADDR, 2, CONF_USB_CDCD_ACM_DATA_BULKIN_MAXPKSZ_HS, 0)

#define CDCD_ACM_STR_DESCES                                                                                            \
	CONF_USB_CDCD_ACM_LANGID_DESC                                                                                      \
	CONF_USB_CDCD_ACM_IMANUFACT_STR_DESC                                                                               \
	CONF_USB_CDCD_ACM_IPRODUCT_STR_DESC                                                                                \
	CONF_USB_CDCD_ACM_ISERIALNUM_STR_DESC                                                                              \
	CONF_USB_CDCD_ACM_ICONFIG_STR_DESC

/** USB Device descriptors and configuration descriptors */
#define CDCD_ACM_DESCES_LS_FS                                                                                          \
	CDCD_ACM_DEV_DESC, CDCD_ACM_CFG_DESC, CDCD_ACM_COMM_IFACE_DESCES, CDCD_ACM_DATA_IFACE_DESCES, CDCD_ACM_STR_DESCES

#define CDCD_ACM_HS_DESCES_LS_FS                                                                                       \
	CDCD_ACM_DEV_DESC, CDCD_ACM_DEV_QUAL_DESC, CDCD_ACM_CFG_DESC, CDCD_ACM_COMM_IFACE_DESCES,                          \
	    CDCD_ACM_DATA_IFACE_DESCES, CDCD_ACM_OTH_SPD_CFG_DESC, CDCD_ACM_COMM_IFACE_DESCES,                             \
	    CDCD_ACM_DATA_IFACE_DESCES_HS, CDCD_ACM_STR_DESCES

#define CDCD_ACM_HS_DESCES_HS                                                                                          \
	CDCD_ACM_CFG_DESC, CDCD_ACM_COMM_IFACE_DESCES, CDCD_ACM_DATA_IFACE_DESCES_HS, CDCD_ACM_OTH_SPD_CFG_DESC,           \
	    CDCD_ACM_COMM_IFACE_DESCES, CDCD_ACM_DATA_IFACE_DESCES

#endif /* USBDF_CDC_ACM_DESC_H_ */
