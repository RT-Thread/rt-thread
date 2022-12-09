/***************************************************************************//**
* \file cy_usb_dev_hid.h
* \version 2.10
*
* Provides HID class-specific API declarations.
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
* \addtogroup group_usb_dev_hid
* This section provides the API description for the HID class.
* \{
*    \defgroup group_usb_dev_hid_macros Macros
*    \defgroup group_usb_dev_hid_functions Functions
*    \defgroup group_usb_dev_hid_data_structures Data Structures
*    \defgroup group_usb_dev_hid_enums Enumerated Types
* \}
*/


#if !defined(CY_USB_DEV_HID_H)
#define CY_USB_DEV_HID_H

#include "cy_usb_dev.h"

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*                          Enumerated Types
*******************************************************************************/

/**
* \addtogroup group_usb_dev_hid_enums
* \{
*/

/** Timer state */
typedef enum
{
    CY_USB_DEV_HID_TIMER_EXPIRED,     /**< Timer expired */
    CY_USB_DEV_HID_TIMER_RUNNING,     /**< Timer is running */
    CY_USB_DEV_HID_TIMER_INDEFINITE,  /**< Report is sent when data or state changes */
} cy_en_usb_dev_hid_timer_state_t;

/** \} group_usb_dev_hid_enums */



/*******************************************************************************
*                          Type Definitions
*******************************************************************************/

/**
* \addtogroup group_usb_dev_hid_data_structures
* \{
*/

/** Handler for GET_REPORT request received */
typedef cy_en_usb_dev_status_t (* cy_cb_usbfs_dev_hid_get_report_t)
                                    (uint32_t intf, uint32_t type, uint32_t id,
                                     uint8_t **report, uint32_t *size);

/** Handler for SET_REPORT request completed. The Host sent report data to Device. */
typedef cy_en_usb_dev_status_t (* cy_cb_usbfs_dev_hid_set_report_t)
                                    (uint32_t intf, uint32_t type, uint32_t id,
                                     uint8_t *report, uint32_t size);

/** HID class configuration structure  */
typedef struct
{
    /** The pointer to the HID idle rate timers array. The array size must be 2
    * times greater than number of HID idle rate timers.
    */
    uint8_t *timers;

    /** Number of HID idle rate timers (equal to number of report IDs, if
    * report ID is not used report consumes 1 idle rate timer).
    */
    uint8_t timersNum;

} cy_stc_usb_dev_hid_config_t;

/** HID class context structure.
* All fields for the HID context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the middleware in HID function calls. Firmware
* must ensure that the defined instance of this structure remains in scope while
* the middleware is in use.
*/
typedef struct
{
    /** \cond INTERNAL */

    /** Pointer to device context */
    cy_stc_usb_dev_context_t *devContext;

    /** Class functions pointers */
    cy_stc_usb_dev_class_t classObj;

    /** Class linked list item */
    cy_stc_usb_dev_class_ll_item_t classItem;

    /** HID boot protocol options */
    volatile uint8_t protocol[CY_USB_DEV_NUM_INTERFACES_MAX];

    /** HID idle rates array */
    uint8_t *idleRate;

    /** HID idle rate timers array */
    uint8_t *idleTimer;

    /** Number of HID idle rate timers (equal to number of report IDs) */
    uint8_t timersNum;

    /** Pointer to function that handles GET_REPORT requests */
    cy_cb_usbfs_dev_hid_get_report_t handleGetReport;

    /** Pointer to function that handles SET_REPORT requests */
    cy_cb_usbfs_dev_hid_set_report_t handleSetReport;
    /** \endcond */

} cy_stc_usb_dev_hid_context_t;

/** \} group_usb_dev_hid_data_structures */


/*******************************************************************************
*                          Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_usb_dev_hid_functions
* \{
*/
cy_en_usb_dev_status_t Cy_USB_Dev_HID_Init(cy_stc_usb_dev_hid_config_t  const *config,
                                           cy_stc_usb_dev_hid_context_t       *context,
                                           cy_stc_usb_dev_context_t           *devContext);

cy_en_usb_dev_hid_timer_state_t Cy_USB_Dev_HID_UpdateTimer(uint32_t interface,
                                                           uint32_t reportId,
                                         cy_stc_usb_dev_hid_context_t *context);

__STATIC_INLINE uint32_t Cy_USB_Dev_HID_GetProtocol(uint32_t interface,
                                                    cy_stc_usb_dev_hid_context_t const *context);

__STATIC_INLINE void Cy_USB_Dev_HID_RegisterGetReportCallback(cy_cb_usbfs_dev_hid_get_report_t callback,
                                                              cy_stc_usb_dev_hid_context_t     *context);

__STATIC_INLINE void Cy_USB_Dev_HID_RegisterSetReportCallback(cy_cb_usbfs_dev_hid_set_report_t callback,
                                                              cy_stc_usb_dev_hid_context_t     *context);

__STATIC_INLINE cy_stc_usb_dev_class_t * Cy_USB_Dev_HID_GetClass(cy_stc_usb_dev_hid_context_t *context);

/** \} group_usb_dev_hid_functions */


/*******************************************************************************
*                         API Constants
*******************************************************************************/

/**
* \addtogroup group_usb_dev_hid_macros
* \{
*/
/** Protocol options */
#define CY_USB_DEV_HID_PROTOCOL_BOOT      (0U)    /**< Boot Protocol  */
#define CY_USB_DEV_HID_PROTOCOL_REPORT    (1U)    /**< Report Protocol */

/** Report types */
#define CY_USB_DEV_HID_REPORT_TYPE_INPUT      (1U)    /**< Input report type */
#define CY_USB_DEV_HID_REPORT_TYPE_OUTPUT     (2U)    /**< Output report type */
#define CY_USB_DEV_HID_REPORT_TYPE_FEATURE    (3U)    /**< Feature report type */

/** HID Class Requests */
#define CY_USB_DEV_HID_RQST_GET_REPORT     (0x1U)   /**< GET_REPORT HID Class Request */
#define CY_USB_DEV_HID_RQST_GET_IDLE       (0x2U)   /**< GET_IDLE HID Class Request */
#define CY_USB_DEV_HID_RQST_GET_PROTOCOL   (0x3U)   /**< GET_PROTOCOL HID Class Request */
#define CY_USB_DEV_HID_RQST_SET_REPORT     (0x9U)   /**< SET_REPORT HID Class Request */
#define CY_USB_DEV_HID_RQST_SET_IDLE       (0xAU)   /**< SET_IDLE HID Class Request */
#define CY_USB_DEV_HID_RQST_SET_PROTOCOL   (0xBU)   /**< SET_PROTOCOL HID Class Request */
/** \} group_usb_dev_hid_functions */


/*******************************************************************************
*                           In-line Function Implementation
*******************************************************************************/

/**
* \addtogroup group_usb_dev_hid_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_USB_Dev_HID_RegisterGetReportCallback
****************************************************************************//**
*
* Registers a callback function that handles a GET_REPORT request.
* The GET_REPORT request is STALLed if the callback function is not registered
* or returns an error.
* To remove the callback function, pass NULL as the function pointer.
*
* \param callback
* The pointer to a callback function.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_HID_RegisterGetReportCallback(cy_cb_usbfs_dev_hid_get_report_t callback,
                                                              cy_stc_usb_dev_hid_context_t     *context)
{
    context->handleGetReport = callback;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_HID_RegisterSetReportCallback
****************************************************************************//**
*
* Registers a callback function that handles SET_REPORT request. This function
* is called when data stage of control transfer was completed (USB Device
* received report data from the USB Host). The SET_REPORT request is STALLed
* if the callback function is not registered or returns an error.
* To remove handler, set the handle parameter to NULL and call this function.
*
* \param callback
* The pointer to a callback function.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_HID_RegisterSetReportCallback(cy_cb_usbfs_dev_hid_set_report_t callback,
                                                              cy_stc_usb_dev_hid_context_t     *context)
{
    context->handleSetReport = callback;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_HID_GetClass
****************************************************************************//**
*
* Returns pointer to the HID class structure.
* This function is useful to override class event handlers using
* \ref group_usb_dev_functions_class_support.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* The pointer to the HID class structure.
*
*******************************************************************************/
__STATIC_INLINE cy_stc_usb_dev_class_t * Cy_USB_Dev_HID_GetClass(cy_stc_usb_dev_hid_context_t *context)
{
    return &context->classObj;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_HID_GetProtocol
****************************************************************************//**
*
* Returns the HID protocol value for a certain interface.
*
* \param interface
* Interface number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Supported protocol: \ref CY_USB_DEV_HID_PROTOCOL_BOOT or
* \ref CY_USB_DEV_HID_PROTOCOL_REPORT.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USB_Dev_HID_GetProtocol(uint32_t  interface,
                                                    cy_stc_usb_dev_hid_context_t const *context)
{
    return ((interface < CY_USB_DEV_NUM_INTERFACES_MAX) ?
                            context->protocol[interface] : (uint32_t) -1);
}

/** \} group_usb_dev_hid_functions */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */

#endif /* (CY_USB_DEV_HID_H) */


/* [] END OF FILE */
