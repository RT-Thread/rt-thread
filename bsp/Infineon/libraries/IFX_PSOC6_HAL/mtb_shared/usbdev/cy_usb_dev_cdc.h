/***************************************************************************//**
* \file cy_usb_dev_cdc.h
* \version 2.10
*
* Provides CDC class-specific API declarations.
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
* \addtogroup group_usb_dev_cdc
* This section provides API description for the CDC class.
*
* \{
*    \defgroup group_usb_dev_cdc_macros          Macros
*    \defgroup group_usb_dev_cdc_functions       Functions
*    \defgroup group_usb_dev_cdc_data_structures Data Structures
*    \defgroup group_usb_dev_cdc_enums           Enumerated Types
* \}
*/


#if !defined(CY_USB_DEV_CDC_H)
#define CY_USB_DEV_CDC_H

#include "cy_usb_dev.h"

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*                          API Constants
*******************************************************************************/

/**
* \addtogroup group_usb_dev_cdc_macros
* \{
*/
/** Number of supported COM ports */
#define CY_USB_DEV_CDC_COMPORT_NUMBER   (2U)

/* CDC Class requests */
#define CY_USB_DEV_CDC_RQST_SET_LINE_CODING         (0x20U)   /**< SetLineCoding CDC class request */
#define CY_USB_DEV_CDC_RQST_GET_LINE_CODING         (0x21U)   /**< GetLineCoding CDC class request */
#define CY_USB_DEV_CDC_RQST_SET_CONTROL_LINE_STATE  (0x22U)   /**< SetControlLineState CDC class request */
/** \} group_usb_dev_cdc_macros */


/*******************************************************************************
*                          Internal Constants
*******************************************************************************/

/** \cond INTERNAL */
#define CY_USB_DEV_CDC_SERIAL_STATE_SIZE            (10U)
#define CY_USB_DEV_CDC_LINE_CODING_CHAR_FORMAT_POS  (4U)
#define CY_USB_DEV_CDC_LINE_CODING_SIZE             (7U)
#define CY_USB_DEV_CDC_LINE_CODING_PARITY_BITS_POS  (5U)
#define CY_USB_DEV_CDC_LINE_CODING_DATA_BITS_POS    (6U)

#define CY_USB_DEV_CDC_IS_COM_VALID(com)    ((com) <= CY_USB_DEV_CDC_COMPORT_NUMBER)
/** \endcond */


/*******************************************************************************
*                          Enumerated Types
*******************************************************************************/

/**
* \addtogroup group_usb_dev_cdc_enums
* \{
*/

/** CDC Stop bit */
typedef enum
{
    CY_USB_DEV_CDC_STOPBIT_1,    /**< 1 stop bit */
    CY_USB_DEV_CDC_STOPBITS_1_5, /**< 1.5 stop bits */
    CY_USB_DEV_CDC_STOPBITS_2,   /**< 2 stop bits */
} cy_en_usb_dev_cdc_stop_bit_t;

/** CDC Parity type */
typedef enum
{
    CY_USB_DEV_CDC_PARITY_NONE,   /**< None parity */
    CY_USB_DEV_CDC_PARITY_ODD,    /**< Odd parity */
    CY_USB_DEV_CDC_PARITY_EVEN,   /**< Even parity */
    CY_USB_DEV_CDC_PARITY_MARK,   /**< Mark */
    CY_USB_DEV_CDC_PARITY_SPACE,  /**< Space */
} cy_en_usb_dev_cdc_parity_type_t;

/** \} group_usb_dev_cdc_enums */


/*******************************************************************************
*                          Type Definitions
*******************************************************************************/

/**
* \addtogroup group_usb_dev_cdc_data_structures
* \{
*/
/** CDC class configuration structure  */
typedef struct
{
    /** The pointers to the buffers to store received data by COM port 0 and 1
    * appropriately. The buffer is mandatory to for \ref Cy_USB_Dev_CDC_GetData
    * and \ref Cy_USB_Dev_CDC_GetChar function operation. If these functions
    * will not be used by the application pass NULL as a pointer. \n
    * Allocate buffer using \ref CY_USB_DEV_ALLOC_ENDPOINT_BUFFER macro to make
    * it USBFS driver configuration independent (See \ref group_usb_dev_ep_buf_alloc
    * for more information).
    */
    uint8_t *buffer[CY_USB_DEV_CDC_COMPORT_NUMBER];

    /** Size of provided buffers to for the COM port 0 and 1 appropriately.
    * The buffer size must be equal to the maximum packet size of CDC Data
    * interface IN endpoint that belongs to the COM port.
    * Pass zero size if the pointer to the buffer is NULL.
    */
    uint32_t bufferSize[CY_USB_DEV_CDC_COMPORT_NUMBER];


} cy_stc_usb_dev_cdc_config_t;

/** \cond INTERNAL: CDC COM port properties structure */
typedef struct
{
    /** Defines whether port is valid for usage */
    volatile bool valid;

    /** Buffer for byte read organization */
    uint8_t *buffer;

    /** Size of buffer */
    uint32_t bufferSize;

    /** Number of occupied bytes in buffer */
    uint32_t writeBufIdx;

    /** Number of occupied bytes in buffer */
    uint32_t readBufIdx;

    /** Contains the interface number used to define port number in requests. */
    volatile uint8_t interfaceNum;

    /**
      * Contains the data IN endpoint size. It is initialized after a
      * SET_CONFIGURATION request based on a user descriptor. It is used
      * in CDC functions to send data to the Host.
      */
    volatile uint16_t dataInEpSize;

    /**
      * Contains the data OUT endpoint size. It is initialized after a
      * SET_CONFIGURATION request based on user descriptor. It is used in
      * CDC functions to receive data from the Host.
      */
    volatile uint16_t dataOutEpSize;

    /**
      * Contains the IN interrupt endpoint size used for sending serial
      * state notification to the Host. It is initialized after a
      * SET_CONFIGURATION request based on a user descriptor. It is used
      * in the CDC function SendSerialState().
      */
    volatile uint16_t commEpSize;

    /**
      * Contains the current line coding structure. The Host sets it using
      * a SET_LINE_CODING request and returns it to the user code using
      * the GetDTERate(), GetCharFormat(), GetParityType(), and
      * GetDataBits() functions.
      */
    volatile uint8_t  linesCoding[CY_USB_DEV_CDC_LINE_CODING_SIZE];
    /**
      * Used as a flag for the IsLineChanged() function, to inform it that
      * the host has been sent a request to change line coding or control
      * bitmap.
      */
    volatile uint8_t linesChanged;

    /**
      * Contains the current control-signal bitmap. The Host sets it using
      * a SET_CONTROL_LINE request and returns it to the user code using
      * the GetLineControl() function.
      */
    volatile uint8_t linesControlBitmap;

    /**
      * Contains the 16-bit serial state value that was sent using the
      * SendSerialState() function.
      */
    volatile uint16_t serialStateBitmap;

    /**
      * Contains the 16-bit serial state value that was sent using the
      * SendSerialState() function.
      */
    volatile uint8_t serialStateNotification[CY_USB_DEV_CDC_SERIAL_STATE_SIZE];

    /**
      * Contains the data IN endpoint number. It is initialized after a
      * SET_CONFIGURATION request based on a user descriptor. It is used
      * in CDC functions to send data to the host.
      */
    volatile uint8_t dataInEp;

    /**
      * Contains the data OUT endpoint number. It is initialized after a
      * SET_CONFIGURATION request based on user descriptor. It is used in
      * CDC functions to receive data from the Host.
      */
    volatile uint8_t dataOutEp;

    /**
      * Contains the IN interrupt endpoint number used for sending serial
      * state notification to the host. It is initialized after a
      * SET_CONFIGURATION request based on a user descriptor. It is used
      * in the CDC function SendSerialState().
      */
    volatile uint8_t commEp;

} cy_stc_usb_dev_cdc_comport_t;
/** \endcond */

/** CDC class context structure.
* All fields for the CDC context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the middleware in CDC function calls. Firmware
* must ensure that the defined instance of this structure remains in scope while
* the middleware is in use.
*/
typedef struct
{
    /** \cond INTERNAL*/

    /** COM port description array */
    cy_stc_usb_dev_cdc_comport_t port[CY_USB_DEV_CDC_COMPORT_NUMBER];

    /** CDC class functions pointers */
    cy_stc_usb_dev_class_t classObj;

    /** CDC class linked list item */
    cy_stc_usb_dev_class_ll_item_t classItem;

    /** Device context */
    cy_stc_usb_dev_context_t *devContext;

    /**
    * Called after setupRequest was received (before internal processing).
    * Returns status of the event processing.
    */
    cy_cb_usb_dev_request_received_t requestReceived;

    /**
    * Called after setupRequest was received (before internal processing).
    * Returns status of the event processing.
    */
    cy_cb_usb_dev_request_cmplt_t requestCompleted;

    /** \endcond */

} cy_stc_usb_dev_cdc_context_t;
/** \} group_usb_dev_cdc_data_structures */


/*******************************************************************************
*                          Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_usb_dev_cdc_functions
* \{
*/
cy_en_usb_dev_status_t Cy_USB_Dev_CDC_Init(cy_stc_usb_dev_cdc_config_t  const *config,
                                           cy_stc_usb_dev_cdc_context_t       *context,
                                           cy_stc_usb_dev_context_t           *devContext);

cy_en_usb_dev_status_t Cy_USB_Dev_CDC_PutData(uint32_t port, uint8_t const *buffer, uint32_t size,
                                              cy_stc_usb_dev_cdc_context_t *context);

cy_en_usb_dev_status_t Cy_USB_Dev_CDC_PutString(uint32_t port, char_t const *string, int32_t timeout,
                                                cy_stc_usb_dev_cdc_context_t  *context);

__STATIC_INLINE cy_en_usb_dev_status_t Cy_USB_Dev_CDC_PutChar(uint32_t port, char_t ch,
                                                              cy_stc_usb_dev_cdc_context_t *context);

uint32_t Cy_USB_Dev_CDC_GetCount(uint32_t port, cy_stc_usb_dev_cdc_context_t *context);

bool Cy_USB_Dev_CDC_IsDataReady(uint32_t port, cy_stc_usb_dev_cdc_context_t *context);

bool Cy_USB_Dev_CDC_IsReady(uint32_t port, cy_stc_usb_dev_cdc_context_t *context);

uint32_t Cy_USB_Dev_CDC_GetData(uint32_t port, uint8_t *buffer, uint32_t  size,
                                cy_stc_usb_dev_cdc_context_t  *context);

uint32_t Cy_USB_Dev_CDC_GetAll(uint32_t port, uint8_t *buffer,  uint32_t maxSize,
                               cy_stc_usb_dev_cdc_context_t *context);

char_t Cy_USB_Dev_CDC_GetChar(uint32_t port, cy_stc_usb_dev_cdc_context_t *context);

__STATIC_INLINE uint32_t Cy_USB_Dev_CDC_IsLineChanged(uint32_t port, cy_stc_usb_dev_cdc_context_t *context);

__STATIC_INLINE uint32_t Cy_USB_Dev_CDC_GetLineControl(uint32_t port, cy_stc_usb_dev_cdc_context_t const *context);

uint32_t Cy_USB_Dev_CDC_GetDTERate(uint32_t port, cy_stc_usb_dev_cdc_context_t *context);

__STATIC_INLINE cy_en_usb_dev_cdc_stop_bit_t Cy_USB_Dev_CDC_GetCharFormat(uint32_t port,
                                                                          cy_stc_usb_dev_cdc_context_t const *context);

__STATIC_INLINE cy_en_usb_dev_cdc_parity_type_t Cy_USB_Dev_CDC_GetParity(uint32_t port, cy_stc_usb_dev_cdc_context_t const *context);

__STATIC_INLINE uint32_t Cy_USB_Dev_CDC_GetDataBits(uint32_t port, cy_stc_usb_dev_cdc_context_t const *context);

cy_en_usb_dev_status_t Cy_USB_Dev_CDC_SendSerialState(uint32_t port, uint32_t serialState,
                                                      cy_stc_usb_dev_cdc_context_t *context);

bool Cy_USB_Dev_CDC_IsNotificationReady(uint32_t port, cy_stc_usb_dev_cdc_context_t *context);

__STATIC_INLINE void Cy_USB_Dev_CDC_RegisterUserCallbacks(cy_cb_usb_dev_request_received_t requestReceivedHandle,
                                                          cy_cb_usb_dev_request_cmplt_t    requestCompletedHandle,
                                                          cy_stc_usb_dev_cdc_context_t     *context);

__STATIC_INLINE cy_stc_usb_dev_class_t * Cy_USB_Dev_CDC_GetClass(cy_stc_usb_dev_cdc_context_t *context);

__STATIC_INLINE uint32_t Cy_USB_Dev_CDC_GetSerialState(uint32_t port, cy_stc_usb_dev_cdc_context_t const *context);
/** \} group_usb_dev_cdc_functions */


/*******************************************************************************
*                         API Constants
*******************************************************************************/

/**
* \addtogroup group_usb_dev_cdc_macros
* \{
*/

/**
* Indicates that a DTR signal is present. This signal corresponds to V.24
* signal 108/2 and RS232 signal DTR.
*/
#define CY_USB_DEV_CDC_LINE_CONTROL_DTR       (0x1U)

/**
* Carrier control for half-duplex modems. This signal corresponds to V.24
* signal 105 and RS232 signal RTS.
*/
#define CY_USB_DEV_CDC_LINE_CONTROL_RTS       (0x2U)

#define CY_USB_DEV_CDC_LINE_NOT_CHANGED       (0U)    /**< No line coding/line control changes */
#define CY_USB_DEV_CDC_LINE_CODING_CHANGED    (1U)    /**< Line coding changed */
#define CY_USB_DEV_CDC_LINE_CONTROL_CHANGED   (2U)    /**< Line control changed */

/** \} group_usb_dev_cdc_macros */


/*******************************************************************************
*                           In-line Function Implementation
*******************************************************************************/

/**
* \addtogroup group_usb_dev_cdc_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_RegisterUserCallbacks
****************************************************************************//**
*
* Registering user callback to handle CDC class requests that are not supported
* by provided CDC request handler.
*
* \param requestReceivedHandle
* The pointer to a callback function.
* This function is called when setup packet was received from USB Host but was
* not recognized, therefore might require the user class processing.
* To remove callback function pass NULL as function pointer.
*
* \param requestCompletedHandle
* The pointer to a callback function.
* This function is called when USB Device received data from the USB Host
* as part of current request processing. The requestReceivedHandle function
* must enable notification to trigger this event. This makes sense only when CDC
* request processing requires a data stage.
* To remove callback function pass NULL as function pointer.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the Audio Class operation for
* internal configuration and data retention. The user must not modify anything
* in this structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_CDC_RegisterUserCallbacks(cy_cb_usb_dev_request_received_t requestReceivedHandle,
                                                          cy_cb_usb_dev_request_cmplt_t    requestCompletedHandle,
                                                          cy_stc_usb_dev_cdc_context_t     *context)
{
    context->requestReceived  = requestReceivedHandle;
    context->requestCompleted = requestCompletedHandle;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetClass
****************************************************************************//**
*
* Returns pointer to the CDC class structure.
* This function is useful to override class event handlers using
* \ref group_usb_dev_functions_class_support.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* The pointer to the CDC class structure.
*
*******************************************************************************/
__STATIC_INLINE cy_stc_usb_dev_class_t * Cy_USB_Dev_CDC_GetClass(cy_stc_usb_dev_cdc_context_t *context)
{
    return &context->classObj;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetSerialState
****************************************************************************//**
*
* Returns the current serial state value for the COM port.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* 16-bit serial state value. Refer to revision 1.2 of the CDC PSTN Subclass
* specification for bit field definitions of the 16-bit serial state value.
* Zero in case COM port is invalid.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USB_Dev_CDC_GetSerialState(uint32_t port, cy_stc_usb_dev_cdc_context_t const *context)
{
    CY_ASSERT_L1(CY_USB_DEV_CDC_IS_COM_VALID(port));

    uint32_t retState = (context->port[port].valid) ?
                         context->port[port].serialStateBitmap : 0U;
    return retState;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_IsLineChanged
****************************************************************************//**
*
* Returns the clear-on-read status of the COM port.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* * \ref CY_USB_DEV_CDC_LINE_CODING_CHANGED when SET_LINE_CODING request is
*    received.
* * \ref CY_USB_DEV_CDC_LINE_CONTROL_CHANGED when CDC_SET_CONTROL_LINE_STATE
*    request is received.
* * \ref CY_USB_DEV_CDC_LINE_NOT_CHANGED when there were no request since last
*    call.
*
* \note
* This function is not interrupt-protected and to prevent a race condition,
* it should be protected from the USBFS interruption in the place where it
* is called.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USB_Dev_CDC_IsLineChanged(uint32_t port, cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(CY_USB_DEV_CDC_IS_COM_VALID(port));

    uint32_t retState = context->port[port].linesChanged;
    context->port[port].linesChanged = CY_USB_DEV_CDC_LINE_NOT_CHANGED;

    return retState;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetCharFormat
****************************************************************************//**
*
* Returns the number of stop bits for the COM port.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Number of stop bits \ref cy_en_usb_dev_cdc_stop_bit_t.
*
*******************************************************************************/
__STATIC_INLINE cy_en_usb_dev_cdc_stop_bit_t Cy_USB_Dev_CDC_GetCharFormat(uint32_t port, cy_stc_usb_dev_cdc_context_t const *context)
{
    CY_ASSERT_L1(CY_USB_DEV_CDC_IS_COM_VALID(port));

    return (cy_en_usb_dev_cdc_stop_bit_t) context->port[port].linesCoding[CY_USB_DEV_CDC_LINE_CODING_CHAR_FORMAT_POS];
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_PutChar
****************************************************************************//**
*
* Sends a single character to the USB Host.
* Call \ref Cy_USB_Dev_CDC_IsReady function to ensure that the COM port
* (CDC Data interface) is ready for sending data to the USB Host before calling
* this function.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param ch
* Character to be sent.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
__STATIC_INLINE cy_en_usb_dev_status_t Cy_USB_Dev_CDC_PutChar(uint32_t port, char_t ch,
                                              cy_stc_usb_dev_cdc_context_t *context)
{
    /* Put data into the aligned buffer to work with 8-bit and 16-bit access type */
    uint16_t chBuffer = (uint16_t) ch;

    return Cy_USB_Dev_CDC_PutData(port, (uint8_t*) &chBuffer, 1U, context);
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetParity
****************************************************************************//**
*
* Returns the parity type for the COM port.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Parity type \ref cy_en_usb_dev_cdc_parity_type_t.
*
*******************************************************************************/
__STATIC_INLINE cy_en_usb_dev_cdc_parity_type_t Cy_USB_Dev_CDC_GetParity(uint32_t port, cy_stc_usb_dev_cdc_context_t const *context)
{
    CY_ASSERT_L1(CY_USB_DEV_CDC_IS_COM_VALID(port));

    return (cy_en_usb_dev_cdc_parity_type_t) context->port[port].linesCoding[CY_USB_DEV_CDC_LINE_CODING_PARITY_BITS_POS];
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetDataBits
****************************************************************************//**
*
* Returns the number of data bits for the COM port.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data keeping. The user must not modify
* anything in this structure.
*
* \return
* Number of data bits, which can be 5, 6, 7, 8, or 16.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USB_Dev_CDC_GetDataBits(uint32_t port, cy_stc_usb_dev_cdc_context_t const *context)
{
    CY_ASSERT_L1(CY_USB_DEV_CDC_IS_COM_VALID(port));

    return (uint32_t) context->port[port].linesCoding[CY_USB_DEV_CDC_LINE_CODING_DATA_BITS_POS];
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetLineControl
****************************************************************************//**
*
* Returns the line control bitmap for the COM port.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Line control bitmap \ref CY_USB_DEV_CDC_LINE_CONTROL_DTR and
* \ref CY_USB_DEV_CDC_LINE_CONTROL_RTS.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USB_Dev_CDC_GetLineControl(uint32_t port, cy_stc_usb_dev_cdc_context_t const *context)
{
    CY_ASSERT_L1(CY_USB_DEV_CDC_IS_COM_VALID(port));

    return (uint32_t) context->port[port].linesControlBitmap;
}

/** \} group_usb_dev_cdc_functions */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */

#endif /* (CY_USB_DEV_CDC_H) */


/* [] END OF FILE */
