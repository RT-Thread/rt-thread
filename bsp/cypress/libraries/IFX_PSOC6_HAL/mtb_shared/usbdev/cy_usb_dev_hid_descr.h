/***************************************************************************//**
* \file cy_usb_dev_hid_descr.h
* \version 2.10
*
* Provides HID class-specific descriptor defines.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USB_DEV_HID_DESCR_H)
#define CY_USB_DEV_HID_DESCR_H

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*                         API Constants
*******************************************************************************/

/** \cond INTERNAL */
/* Supported HID version */
#define CY_USB_DEV_HID_VERSION_1_11    (0x0111U)

/* HID Class */
#define CY_USB_DEV_HID_CLASS           (3U)
#define CY_USB_DEV_HID_SUBCLASS_NONE   (0U)
#define CY_USB_DEV_HID_PROTOCOL_NONE   (0U)

/* Descriptors */
#define CY_USB_DEV_HID_DESCRIPTOR         (33U)
#define CY_USB_DEV_HID_DESCRIPTOR_LENGTH  (9U)
#define CY_USB_DEV_HID_REPORT_DESCRIPTOR  (34U)
/** \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */

#endif /* (CY_USB_DEV_HID_DESCR_H) */


/* [] END OF FILE */
