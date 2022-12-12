/***************************************************************************//**
* \file cy_usb_dev_audio.h
* \version 2.10
*
* Provides Audio class-specific API declarations.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

/**
* \addtogroup group_usb_dev_audio
* This section provides API description for the Audio class.
* \{
*    \defgroup group_usb_dev_audio_macros          Macros
*    \defgroup group_usb_dev_audio_functions       Functions
*    \defgroup group_usb_dev_audio_data_structures Data Structures
* \}
*/

#if !defined(CY_USB_DEV_AUDIO_H)
#define CY_USB_DEV_AUDIO_H

#include "cy_usb_dev.h"

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*                          Enumerated Types
*******************************************************************************/


/*******************************************************************************
*                          Type Definitions
*******************************************************************************/

/**
* \addtogroup group_usb_dev_audio_data_structures
* \{
*/

/** Audio class context structure.
* All fields for the Audio context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the middleware in Audio function calls. Firmware
* must ensure that the defined instance of this structure remains in scope while
* the middleware is in use.
*/
typedef struct
{
    /** \cond INTERNAL*/

    /** Pointer to device context */
    cy_stc_usb_dev_context_t *devContext;

    /** Audio class functions pointers */
    cy_stc_usb_dev_class_t classObj;

    /** Audio class linked list item */
    cy_stc_usb_dev_class_ll_item_t classItem;

    /** \endcond */

} cy_stc_usb_dev_audio_context_t;

/** \} group_usb_dev_audio_data_structures */


/*******************************************************************************
*                          Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_usb_dev_audio_functions
* \{
*/
cy_en_usb_dev_status_t Cy_USB_Dev_Audio_Init(void const *config,
                                             cy_stc_usb_dev_audio_context_t      *context,
                                             cy_stc_usb_dev_context_t            *devContext);

__STATIC_INLINE void Cy_USB_Dev_Audio_RegisterUserCallback(cy_cb_usb_dev_request_received_t requestReceivedHandle,
                                                           cy_cb_usb_dev_request_cmplt_t    requestCompletedHandle,
                                                           cy_stc_usb_dev_audio_context_t   *context);

__STATIC_INLINE cy_stc_usb_dev_class_t * Cy_USB_Dev_Audio_GetClass(cy_stc_usb_dev_audio_context_t *context);
/** \} group_usb_dev_audio_functions */


/*******************************************************************************
*                         API Constants
*******************************************************************************/

/**
* \addtogroup group_usb_dev_audio_macros
* \{
*/
#define CY_USB_DEV_AUDIO_RQST_GET_CUR   (0x81u)     /**< GET_CUR Audio v1.0 request */
#define CY_USB_DEV_AUDIO_RQST_GET_MIN   (0x82u)     /**< GET_MIN Audio v1.0 request */
#define CY_USB_DEV_AUDIO_RQST_GET_MAX   (0x83u)     /**< GET_MAX Audio v1.0 request */
#define CY_USB_DEV_AUDIO_RQST_GET_RES   (0x84u)     /**< GET_RES Audio v1.0 request */
#define CY_USB_DEV_AUDIO_RQST_GET_MEM   (0x85u)     /**< GET_MEM Audio v1.0 request */
#define CY_USB_DEV_AUDIO_RQST_GET_STAT  (0xFFu)     /**< GET_STAT Audio v1.0 request */

#define CY_USB_DEV_AUDIO_RQST_SET_CUR   (0x01u)     /**< SET_CUR Audio v1.0 request */
#define CY_USB_DEV_AUDIO_RQST_SET_MIN   (0x02u)     /**< SET_MIN Audio v1.0 request */
#define CY_USB_DEV_AUDIO_RQST_SET_MAX   (0x03u)     /**< SET_MAX Audio v1.0 request */
#define CY_USB_DEV_AUDIO_RQST_SET_RES   (0x04u)     /**< SET_RES Audio v1.0 request */
#define CY_USB_DEV_AUDIO_RQST_SET_MEM   (0x05u)     /**< SET_STAT Audio v1.0 request */

#define CY_USB_DEV_AUDIO2_RQST_CUR      (0x01u)     /**< CUR Audio v2.0 request */
#define CY_USB_DEV_AUDIO2_RQST_RANGE    (0x02u)     /**< RANGE Audio v2.0 request */
#define CY_USB_DEV_AUDIO2_RQST_MEM      (0x03u)     /**< MEM Audio v2.0 request */

#define CY_USB_DEV_AUDIO_MASTER_CHANNEL (0U)        /**< Master channel */
#define CY_USB_DEV_AUDIO_VOLUME_MIN     (0x8001U)   /**< Volume minimum value */
#define CY_USB_DEV_AUDIO_VOLUME_MAX     (0x7FFFU)   /**< Volume maximum value */
#define CY_USB_DEV_AUDIO_VOLUME_SILENCE (0x8000U)   /**< Volume value that represent silence (CUR attribute only) */
#define CY_USB_DEV_AUDIO_VOLUME_MIN_MSB (0x80U)     /**< Volume minimum value MSB */
#define CY_USB_DEV_AUDIO_VOLUME_MIN_LSB (0x01U)     /**< Volume minimum value LSB */
#define CY_USB_DEV_AUDIO_VOLUME_MAX_MSB (0x7FU)     /**< Volume maximum value MSB */
#define CY_USB_DEV_AUDIO_VOLUME_MAX_LSB (0xFFU)     /**< Volume maximum value LSB */
/** \} group_usb_dev_audio_macros */


/*******************************************************************************
*                          Internal Constants
*******************************************************************************/


/*******************************************************************************
*                           In-line Function Implementation
*******************************************************************************/

/**
* \addtogroup group_usb_dev_audio_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_USB_Dev_Audio_RegisterUserCallback
****************************************************************************//**
*
* Registers the user callbacks to handle Audio class requests.
*
* \param requestReceivedHandle
* The pointer to a callback function.
* This function is called when setup packet was received from the USB Host but was
* not recognized. Therefore this might require Audio class processing.
* To remove the callback function, pass a NULL as the function pointer.
*
* \param requestCompletedHandle
* The pointer to a callback function.
* This function is called when the USB Device received data from the USB Host
* as part of current request processing. The requestReceivedHandle function
* must enable notification to trigger this event. This makes sense only when class
* request processing requires a data stage.
* To remove the callback function, pass a NULL as the function pointer.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the Audio Class operation for
* internal configuration and data retention. The user must not modify anything
* in this structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_Audio_RegisterUserCallback(cy_cb_usb_dev_request_received_t requestReceivedHandle,
                                                           cy_cb_usb_dev_request_cmplt_t    requestCompletedHandle,
                                                           cy_stc_usb_dev_audio_context_t   *context)
{
    Cy_USB_Dev_RegisterClassRequestRcvdCallback(requestReceivedHandle,   Cy_USB_Dev_Audio_GetClass(context));
    Cy_USB_Dev_RegisterClassRequestCmpltCallback(requestCompletedHandle, Cy_USB_Dev_Audio_GetClass(context));
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_Audio_GetClass
****************************************************************************//**
*
* Returns pointer to the class structure for Audio class.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the Audio Class operation for
* internal configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* Status pointer to the class \ref cy_stc_usb_dev_class_t.
*
*******************************************************************************/
__STATIC_INLINE cy_stc_usb_dev_class_t * Cy_USB_Dev_Audio_GetClass(cy_stc_usb_dev_audio_context_t *context)
{
    return &(context->classObj);
}

/** \} group_usb_dev_audio_functions */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */

#endif /* (CY_USB_DEV_AUDIO_H) */


/* [] END OF FILE */
