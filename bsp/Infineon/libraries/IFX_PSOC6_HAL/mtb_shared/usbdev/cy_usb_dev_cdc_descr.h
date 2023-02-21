/***************************************************************************//**
* \file cy_usb_dev_cdc_descr.h
* \version 2.10
*
* Provides CDC class-specific descriptor defines.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USB_DEV_CDC_DESCR_H)
#define CY_USB_DEV_CDC_DESCR_H

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*                         API Constants
*******************************************************************************/

/** \cond INTERNAL */
/* CDC class */
#define CY_USB_DEV_CDC_CLASS        (0x02U)
#define CY_USB_DEV_CDC_CLASS_DATA   (0x0AU)
/** \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */

#endif /* (CY_USB_DEV_CDC_DESCR_H) */


/* [] END OF FILE */
