/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
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

#ifndef _USB_DEVICE_CONFIG_H_
#define _USB_DEVICE_CONFIG_H_

/*******************************************************************************
* Definitions
******************************************************************************/
/*!
 * @addtogroup usb_device_configuration
 * @{
 */

/*!
 * @name Hardware instance define
 * @{
 */

/*! @brief KHCI instance count */
#define USB_DEVICE_CONFIG_KHCI (0U)

/*! @brief EHCI instance count */
#define USB_DEVICE_CONFIG_EHCI (2U)

/*! @brief LPC USB IP3511 FS instance count */
#define USB_DEVICE_CONFIG_LPCIP3511FS (0U)

/*! @brief LPC USB IP3511 HS instance count */
#define USB_DEVICE_CONFIG_LPCIP3511HS (0U)

/*! @brief Device instance count, the sum of KHCI and EHCI instance counts*/
#define USB_DEVICE_CONFIG_NUM \
    (USB_DEVICE_CONFIG_KHCI + USB_DEVICE_CONFIG_EHCI + USB_DEVICE_CONFIG_LPCIP3511FS + USB_DEVICE_CONFIG_LPCIP3511HS)

/* @} */

/*!
 * @name class instance define
 * @{
 */

/*! @brief HID instance count */
#define USB_DEVICE_CONFIG_HID (0U)

/*! @brief CDC ACM instance count */
#define USB_DEVICE_CONFIG_CDC_ACM (1U)

/*! @brief MSC instance count */
#define USB_DEVICE_CONFIG_MSC (0U)

/*! @brief Audio instance count */
#define USB_DEVICE_CONFIG_AUDIO (0U)

/*! @brief PHDC instance count */
#define USB_DEVICE_CONFIG_PHDC (0U)

/*! @brief Video instance count */
#define USB_DEVICE_CONFIG_VIDEO (0U)

/*! @brief CCID instance count */
#define USB_DEVICE_CONFIG_CCID (0U)

/*! @brief Printer instance count */
#define USB_DEVICE_CONFIG_PRINTER (0U)

/*! @brief DFU instance count */
#define USB_DEVICE_CONFIG_DFU (0U)

/* @} */

/*! @brief Whether device is self power. 1U supported, 0U not supported */
#define USB_DEVICE_CONFIG_SELF_POWER (1U)

/*! @brief How many endpoints are supported in the stack. */
#define USB_DEVICE_CONFIG_ENDPOINTS (4U)

/*! @brief Whether the device task is enabled. */
#define USB_DEVICE_CONFIG_USE_TASK (0U)

/*! @brief How many the notification message are supported when the device task is enabled. */
#define USB_DEVICE_CONFIG_MAX_MESSAGES (8U)

/*! @brief Whether test mode enabled. */
#define USB_DEVICE_CONFIG_USB20_TEST_MODE (0U)

/*! @brief Whether device CV test is enabled. */
#define USB_DEVICE_CONFIG_CV_TEST (0U)

/*! @brief Whether device compliance test is enabled. If the macro is enabled,
    the test mode and CV test macroes will be set.*/
#define USB_DEVICE_CONFIG_COMPLIANCE_TEST (0U)

#if ((defined(USB_DEVICE_CONFIG_COMPLIANCE_TEST)) && (USB_DEVICE_CONFIG_COMPLIANCE_TEST > 0U))

/*! @brief Undefine the marco USB_DEVICE_CONFIG_USB20_TEST_MODE. */
#undef USB_DEVICE_CONFIG_USB20_TEST_MODE
/*! @brief Undefine the marco USB_DEVICE_CONFIG_CV_TEST. */
#undef USB_DEVICE_CONFIG_CV_TEST

/*! @brief enable the test mode. */
#define USB_DEVICE_CONFIG_USB20_TEST_MODE (1U)

/*! @brief enable the CV test */
#define USB_DEVICE_CONFIG_CV_TEST (1U)

#endif

#if ((defined(USB_DEVICE_CONFIG_KHCI)) && (USB_DEVICE_CONFIG_KHCI > 0U))

/*! @brief The MAX buffer length for the KHCI DMA workaround.*/
#define USB_DEVICE_CONFIG_KHCI_DMA_ALIGN_BUFFER_LENGTH (64U)
#endif

#if ((defined(USB_DEVICE_CONFIG_EHCI)) && (USB_DEVICE_CONFIG_EHCI > 0U))
/*! @brief How many the DTD are supported. */
#define USB_DEVICE_CONFIG_EHCI_MAX_DTD (16U)

/*! @brief Whether the EHCI ID pin detect feature enabled. */
#define USB_DEVICE_CONFIG_EHCI_ID_PIN_DETECT (0U)
#endif

/*! @brief Whether the keep alive feature enabled. */
#define USB_DEVICE_CONFIG_KEEP_ALIVE_MODE (0U)

/*! @brief Whether the transfer buffer is cache-enabled or not. */
#define USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE (1U)

/*! @brief Whether the low power mode is enabled or not. */
#define USB_DEVICE_CONFIG_LOW_POWER_MODE (0U)

#if ((defined(USB_DEVICE_CONFIG_LOW_POWER_MODE)) && (USB_DEVICE_CONFIG_LOW_POWER_MODE > 0U))
/*! @brief Whether device remote wakeup supported. 1U supported, 0U not supported */
#define USB_DEVICE_CONFIG_REMOTE_WAKEUP (0U)

/*! @brief Whether LPM is supported. 1U supported, 0U not supported */
#define USB_DEVICE_CONFIG_LPM_L1 (0U)
#else
/*! @brief The device remote wakeup is unsupported. */
#define USB_DEVICE_CONFIG_REMOTE_WAKEUP (0U)
#endif

/*! @brief Whether the device detached feature is enabled or not. */
#define USB_DEVICE_CONFIG_DETACH_ENABLE (0U)

/*! @brief Whether handle the USB bus error. */
#define USB_DEVICE_CONFIG_ERROR_HANDLING (0U)

/* @} */
/*! @brief rt-thread port alloc */
#include <rtthread.h>
#define USB_OSA_SR_ALLOC(...)
/*! @brief rt-thread port enter critical */
#define USB_OSA_ENTER_CRITICAL  rt_enter_critical
/*! @brief rt-thread port exit critical */
#define USB_OSA_EXIT_CRITICAL   rt_exit_critical

#endif /* _USB_DEVICE_CONFIG_H_ */
