/*
 * Copyright 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * 3. Neither the name of copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __USB_HOST_CONFIG_H__
#define __USB_HOST_CONFIG_H__

/* Host Controller Enable */
/*!
 * @brief host khci instance count, meantime it indicates khci enable or disabled.
 *        - if 0, host khci driver is disabled.
 *        - if greater than 0, host khci driver is enabled.
 */
#define USB_HOST_CONFIG_KHCI (0U)

/*!
 * @brief host ehci instance count, meantime it indicates ehci enable or disabled.
 *        - if 0, host ehci driver is disabled.
 *        - if greater than 0, host ehci driver is enabled.
 */
#define USB_HOST_CONFIG_EHCI (1U)

/*!
 * @brief host ohci instance count, meantime it indicates ohci enable or disabled.
 *        - if 0, host ohci driver is disabled.
 *        - if greater than 0, host ohci driver is enabled.
 */
#define USB_HOST_CONFIG_OHCI (0U)

/*!
 * @brief host ip3516hs instance count, meantime it indicates ohci enable or disabled.
 *        - if 0, host ip3516hs driver is disabled.
 *        - if greater than 0, host ip3516hs driver is enabled.
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
 * @brief hub pipe max count.
 * pipe is the host driver resource for device endpoint, one endpoint needs one pipe.
 * @remarks A HUB usually uses two pipes.
 */
#define USB_HOST_CONFIG_HUB_MAX_PIPES (2U)

/*!
 * @brief host pipe max count.
 * pipe is the host driver resource for device endpoint, one endpoint needs one pipe.
 * @remarks Depends on the total number of device interfaces and HUB usage.
 */
#define USB_HOST_CONFIG_MAX_PIPES (USB_HOST_CONFIG_HUB_MAX_PIPES + 2U * USB_HOST_CONFIG_INTERFACE_MAX_EP)

/*!
 * @brief host transfer max count.
 * transfer is the host driver resource for data transmission mission, one transmission mission needs one transfer.
 * @remarks Depends on the total number of device interfaces.
 */
#define USB_HOST_CONFIG_MAX_TRANSFERS (USB_HOST_CONFIG_MAX_PIPES)

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
 * Expressed in 2 mA units (i.e. 250 = 500 mA).
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
#define USB_HOST_CONFIG_COMPLIANCE_TEST (0U)

/*! @brief if 1, class driver clear stall automatically; if 0, class driver doesn't clear stall. */
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
 * @remarks Depends on the total number of device interfaces.
 */
#define USB_HOST_CONFIG_EHCI_MAX_QH (USB_HOST_CONFIG_MAX_PIPES)

/*!
 * @brief ehci QTD max count.
 */
#define USB_HOST_CONFIG_EHCI_MAX_QTD (USB_HOST_CONFIG_EHCI_MAX_QH)

/*!
 * @brief ehci ITD max count.
 */
#define USB_HOST_CONFIG_EHCI_MAX_ITD (USB_HOST_CONFIG_EHCI_MAX_SITD)

/*!
 * @brief ehci SITD max count.
 * @remarks Depends on the total number of device interfaces that can have isochronous endpoints.
 */
#define USB_HOST_CONFIG_EHCI_MAX_SITD (2U * USB_HOST_CONFIG_INTERFACE_MAX_EP)

#endif

/* OHCI configuration */
#if ((defined USB_HOST_CONFIG_OHCI) && (USB_HOST_CONFIG_OHCI))

/*!
 * @brief ohci ED max count.
 * @remarks Depends on the total number of device interfaces.
 */
#define USB_HOST_CONFIG_OHCI_MAX_ED (USB_HOST_CONFIG_MAX_PIPES)

/*!
 * @brief ohci GTD max count.
 */
#define USB_HOST_CONFIG_OHCI_MAX_GTD (USB_HOST_CONFIG_OHCI_MAX_ED)

/*!
 * @brief ohci ITD max count.
 * @remarks Depends on the total number of device interfaces that can have isochronous endpoints.
 */
#define USB_HOST_CONFIG_OHCI_MAX_ITD (2U * USB_HOST_CONFIG_INTERFACE_MAX_EP)

#endif

/* OHCI configuration */
#if ((defined USB_HOST_CONFIG_IP3516HS) && (USB_HOST_CONFIG_IP3516HS))

/*!
 * @brief ohci PIPE max count.
 * @remarks Depends on the total number of device interfaces.
 */
#define USB_HOST_CONFIG_IP3516HS_MAX_PIPE (USB_HOST_CONFIG_MAX_PIPES)

/*!
 * @brief ohci ED max count.
 */
#define USB_HOST_CONFIG_IP3516HS_MAX_ATL (32U)

/*!
 * @brief ohci GTD max count.
 */
#define USB_HOST_CONFIG_IP3516HS_MAX_INT (USB_HOST_CONFIG_IP3516HS_MAX_ATL)

/*!
 * @brief ohci ITD max count.
 * @remarks Depends on the existence of device interfaces that can have isochronous endpoints.
 */
#define USB_HOST_CONFIG_IP3516HS_MAX_ISO (USB_HOST_CONFIG_IP3516HS_MAX_ATL)

#endif

/*!
 * @brief host HUB class instance count, meantime it indicates HUB class enable or disabled.
 *        - if 0, host HUB class driver is disabled.
 *        - if greater than 0, host HUB class driver is enabled.
 */
#define USB_HOST_CONFIG_HUB (0U)

/*!
 * @brief host HID class instance count, meantime it indicates HID class enable or disabled.
 *        - if 0, host HID class driver is disabled.
 *        - if greater than 0, host HID class driver is enabled.
 */
#define USB_HOST_CONFIG_HID (0U)

/*!
 * @brief host MSD class instance count, meantime it indicates MSD class enable or disabled.
 *        - if 0, host MSD class driver is disabled.
 *        - if greater than 0, host MSD class driver is enabled.
 */
#define USB_HOST_CONFIG_MSD (0U)

/*!
 * @brief host CDC class instance count, meantime it indicates CDC class enable or disabled.
 *        - if 0, host CDC class driver is disabled.
 *        - if greater than 0, host CDC class driver is enabled.
 */
#define USB_HOST_CONFIG_CDC (1U)

/*!
 * @brief host AUDIO class instance count, meantime it indicates AUDIO class enable or disabled.
 *        - if 0, host AUDIO class driver is disabled.
 *        - if greater than 0, host AUDIO class driver is enabled.
 */
#define USB_HOST_CONFIG_AUDIO (0U)

/*!
 * @brief host PHDC class instance count, meantime it indicates PHDC class enable or disabled.
 *        - if 0, host PHDC class driver is disabled.
 *        - if greater than 0, host PHDC class driver is enabled.
 */
#define USB_HOST_CONFIG_PHDC (0U)

/*!
 * @brief host printer class instance count, meantime it indicates printer class enable or disabled.
 *        - if 0, host printer class driver is disabled.
 *        - if greater than 0, host printer class driver is enabled.
 */
#define USB_HOST_CONFIG_PRINTER (0U)

#endif /* __USB_HOST_CONFIG_H__ */
