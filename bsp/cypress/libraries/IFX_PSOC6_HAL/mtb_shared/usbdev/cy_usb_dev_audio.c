/***************************************************************************//**
* \file cy_usb_dev_audio.c
* \version 2.10
*
* Provides Audio class-specific API implementation.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_usb_dev_audio.h"

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))

/*******************************************************************************
* Function Name: Cy_USB_Dev_Audio_Init
****************************************************************************//**
*
* Initializes the Audio class.
* This function must be called to enable USB Device Audio functionality.
*
* \param config
* Pass NULL as an argument (left for future purposes).
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_audio_context_t
* allocated by the user. The structure is used during the Audio Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \param devContext
* The pointer to the USB Device context structure \ref cy_stc_usb_dev_context_t.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_Audio_Init(void const *config,
                                             cy_stc_usb_dev_audio_context_t       *context,
                                             cy_stc_usb_dev_context_t             *devContext)
{
    /* Suppress a compiler warning about unused variables */
    (void) config;

    if ((NULL == context) || (NULL == devContext))
    {
        return CY_USB_DEV_BAD_PARAM;
    }

    /* Store device context */
    context->devContext = devContext;

    return Cy_USB_Dev_RegisterClass(&context->classItem, &context->classObj, context, devContext);
}

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */


/* [] END OF FILE */

