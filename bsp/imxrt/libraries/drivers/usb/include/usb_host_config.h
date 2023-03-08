/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _USB_HOST_CONFIG_H_
#define _USB_HOST_CONFIG_H_

/* Host Controller Enable */
/*!
 * @brief host khci instance count, meantime it indicates khci enable or disable.
 *        - if 0, host khci driver is disable.
 *        - if greater than 0, host khci driver is enable.
 */
#define USB_HOST_CONFIG_KHCI (0U)

/*!
 * @brief host ehci instance count, meantime it indicates ehci enable or disable.
 *        - if 0, host ehci driver is disable.
 *        - if greater than 0, host ehci driver is enable.
 */
#define USB_HOST_CONFIG_EHCI (1U)

/*!
 * @brief host ohci instance count, meantime it indicates ohci enable or disable.
 *        - if 0, host ohci driver is disable.
 *        - if greater than 0, host ohci driver is enable.
 */
#define USB_HOST_CONFIG_OHCI (0U)

/*!
 * @brief host ip3516hs instance count, meantime it indicates ohci enable or disable.
 *        - if 0, host ip3516hs driver is disable.
 *        - if greater than 0, host ip3516hs driver is enable.
 */
#define USB_HOST_CONFIG_IP3516HS (0U)

/* Common configuration macros for all controllers */

/*!
 * @brief host driver instance max count.
 * for example: 2 - one for khci, one for ehci.
 */
#define USB_HOST_CONFIG_MAX_HOST \
    (USB_HOST_CONFIG_KHCI + USB_HOST_CONFIG_EHCI + USB_HOST_CONFIG_OHCI + USB_HOST_CONFIG_IP3516HS)

/*!
 * @brief host pipe max count.
 * pipe is the host driver resource for device endpoint, one endpoint need one pipe.
 */
#define USB_HOST_CONFIG_MAX_PIPES (16U)

/*!
 * @brief host transfer max count.
 * transfer is the host driver resource for data transmission mission, one transmission mission need one transfer.
 */
#define USB_HOST_CONFIG_MAX_TRANSFERS (16U)

/*!
 * @brief the max endpoint for one interface.
 * the max endpoint descriptor number that one interface descriptor contain.
 */
#define USB_HOST_CONFIG_INTERFACE_MAX_EP (4U)

/*!
 * @brief the max interface for one configuration.
 * the max interface descriptor number that one configuration descriptor can contain.
 */
#define USB_HOST_CONFIG_CONFIGURATION_MAX_INTERFACE (5U)

/*!
 * @brief the max power for one device.
 * the max power the host can provide for one device.
 */
#define USB_HOST_CONFIG_MAX_POWER (250U)

/*!
 * @brief the max retries for enumeration.
 * retry time when enumeration fail.
 */
#define USB_HOST_CONFIG_ENUMERATION_MAX_RETRIES (3U)

/*!
 * @brief the max retries for enumeration setup stall.
 * the max times for one transfer can stall.
 */
#define USB_HOST_CONFIG_ENUMERATION_MAX_STALL_RETRIES (1U)

/*!
 * @brief the max NAK count for one transaction.
 * when nak count reach to the value, the transaction fail.
 */
#define USB_HOST_CONFIG_MAX_NAK (3000U)

/*! @brief Whether the transfer buffer is cache-enabled or not. */
#ifndef USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE
#define USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE (0U)
#endif
/*! @brief if 1, enable usb compliance test codes; if 0, disable usb compliance test codes. */
#ifndef USB_HOST_CONFIG_COMPLIANCE_TEST
#define USB_HOST_CONFIG_COMPLIANCE_TEST (0U)
#endif

/*! @brief if 1, class driver clear stall automatically; if 0, class driver don't clear stall. */
#define USB_HOST_CONFIG_CLASS_AUTO_CLEAR_STALL (0U)

/* KHCI configuration */
#if ((defined USB_HOST_CONFIG_KHCI) && (USB_HOST_CONFIG_KHCI))

/*!
 * @brief khci dma align fix buffer size.
 */
#define USB_HOST_CONFIG_KHCI_DMA_ALIGN_BUFFER (64U)

#endif

/* EHCI configuration */
#if ((defined USB_HOST_CONFIG_EHCI) && (USB_HOST_CONFIG_EHCI))

/*!
 * @brief ehci periodic frame list size.
 * the value can be 1024, 512, 256, 128, 64, 32, 16 or 8.
 */
#define USB_HOST_CONFIG_EHCI_FRAME_LIST_SIZE (1024U)

/*!
 * @brief ehci QH max count.
 */
#define USB_HOST_CONFIG_EHCI_MAX_QH (8U)

/*!
 * @brief ehci QTD max count.
 */
#define USB_HOST_CONFIG_EHCI_MAX_QTD (8U)

/*!
 * @brief ehci ITD max count.
 */
#define USB_HOST_CONFIG_EHCI_MAX_ITD (0U)

/*!
 * @brief ehci SITD max count.
 */
#define USB_HOST_CONFIG_EHCI_MAX_SITD (0U)

#endif

/* OHCI configuration */
#if ((defined USB_HOST_CONFIG_OHCI) && (USB_HOST_CONFIG_OHCI))

/*!
 * @brief ohci ED max count.
 */
#define USB_HOST_CONFIG_OHCI_MAX_ED (16U)

/*!
 * @brief ohci GTD max count.
 */
#define USB_HOST_CONFIG_OHCI_MAX_GTD (16U)

/*!
 * @brief ohci ITD max count.
 */
#define USB_HOST_CONFIG_OHCI_MAX_ITD (8U)

#endif

/* OHCI configuration */
#if ((defined USB_HOST_CONFIG_IP3516HS) && (USB_HOST_CONFIG_IP3516HS))

#define USB_HOST_CONFIG_IP3516HS_MAX_PIPE (32U)

/*!
 * @brief ohci ED max count.
 */
#define USB_HOST_CONFIG_IP3516HS_MAX_ATL (32U)

/*!
 * @brief ohci GTD max count.
 */
#define USB_HOST_CONFIG_IP3516HS_MAX_INT (32U)

/*!
 * @brief ohci ITD max count.
 */
#define USB_HOST_CONFIG_IP3516HS_MAX_ISO (0U)

#endif

/*!
 * @brief host HUB class instance count, meantime it indicates HUB class enable or disable.
 *        - if 0, host HUB class driver is disable.
 *        - if greater than 0, host HUB class driver is enable.
 */
#define USB_HOST_CONFIG_HUB (0U)

/*!
 * @brief host HID class instance count, meantime it indicates HID class enable or disable.
 *        - if 0, host HID class driver is disable.
 *        - if greater than 0, host HID class driver is enable.
 */
#define USB_HOST_CONFIG_HID (0U)

/*!
 * @brief host MSD class instance count, meantime it indicates MSD class enable or disable.
 *        - if 0, host MSD class driver is disable.
 *        - if greater than 0, host MSD class driver is enable.
 */
#define USB_HOST_CONFIG_MSD (0U)

/*!
 * @brief host CDC class instance count, meantime it indicates CDC class enable or disable.
 *        - if 0, host CDC class driver is disable.
 *        - if greater than 0, host CDC class driver is enable.
 */
#define USB_HOST_CONFIG_CDC (0U)

/*!
 * @brief host AUDIO class instance count, meantime it indicates AUDIO class enable or disable.
 *        - if 0, host AUDIO class driver is disable.
 *        - if greater than 0, host AUDIO class driver is enable.
 */
#define USB_HOST_CONFIG_AUDIO (0U)

/*!
 * @brief host PHDC class instance count, meantime it indicates PHDC class enable or disable.
 *        - if 0, host PHDC class driver is disable.
 *        - if greater than 0, host PHDC class driver is enable.
 */
#define USB_HOST_CONFIG_PHDC (0U)

/*!
 * @brief host printer class instance count, meantime it indicates printer class enable or disable.
 *        - if 0, host printer class driver is disable.
 *        - if greater than 0, host printer class driver is enable.
 */
#define USB_HOST_CONFIG_PRINTER (0U)

/*!
 * @brief host charger detect enable or disable. It is only supported on RT600 currently.
 *        - if 0, host charger detect is disable.
 *        - if greater than 0, host charger detect is enable.
 */
#define USB_HOST_CONFIG_BATTERY_CHARGER (0U)
#endif /* _USB_HOST_CONFIG_H_ */
