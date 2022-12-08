
/***************************************************************************//**
* \file cy_usb_dev_cdc.c
* \version 2.10
*
* Provides Class Specific API implementation.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_usb_dev_cdc.h"
#include "cy_usb_dev_cdc_descr.h"

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))


/*******************************************************************************
*                                Internal Constants
*******************************************************************************/

#define COM1        (0U)
#define COM2        (1U)
#define INVALID_COM (0xFFU)
#define IS_COM_VALID(com)   CY_USB_DEV_CDC_IS_COM_VALID(com)

#define SET_LINE_CODING_LENGTH                  (7U)
#define LINE_CODING_RATE_OFFSET                 (0U)

#define SERIAL_STATE_REQUEST_TYPE               (0xA1U)
#define SERIAL_STATE                            (0x20U)
#define SERIAL_STATE_LENGTH                     (0x2U)

#define SERIAL_STATE_WINDEX_OFFSET              (4U)
#define SERIAL_STATE_WSERIALSTATE_LSB_OFFSET    (8U)
#define SERIAL_STATE_WSERIALSTATE_MSB_OFFSET    (9U)

#define SINGLE_COM_PORT_EP_NUM                  (3U)
#define DUAL_COM_PORT_EP_NUM                    (6U)

#define INTERFACE_CLASS_POS                     (5U)

#define INIT_LINES_CODING \
{                         \
    /* dwDTERate: Data terminal rate, in bits per second */ \
    0x00U, 0xC2U, 0x01U, 0x00U, \
    /* bCharFormat (Stop bits): 0 - 1bit, 1 - 1.5bits, 2 - 2bits */ \
    0x00U, \
    /* bParityType: Parity 0 - None, 1 - Odd, 2 - Even, 3 - Mark, 4 - Space */ \
    0x00U, \
    /*  Data bits (5, 6, 7, 8 or 16) */ \
    0x08U \
}

#define INIT_SERIAL_STATE \
{                         \
    SERIAL_STATE_REQUEST_TYPE,/* bRequestType    */ \
    SERIAL_STATE,             /* bNotification   */ \
    0U,                       /* wValue          */ \
    0U,                       /* wValueMSB       */ \
    0U,                       /* wIndex          */ \
    0U,                       /* wIndexMSB       */ \
    SERIAL_STATE_LENGTH,      /* wLength         */ \
    0u,                       /* wLengthMSB      */ \
    0U,                       /* wSerialState    */ \
    0U,                       /* wSerialStateMSB */ \
}


/*******************************************************************************
*                            Internal Functions
*******************************************************************************/

static cy_en_usb_dev_status_t HandleRequest(cy_stc_usb_dev_control_transfer_t *transfer, void *classContext,
                                            cy_stc_usb_dev_context_t *devContext);

static cy_en_usb_dev_status_t HandleRequestComplete(cy_stc_usb_dev_control_transfer_t *transfer,
                                                      void *classContext,
                                                      cy_stc_usb_dev_context_t *devContext);

static cy_en_usb_dev_status_t HandleSetConfig(uint32_t configuration,
                                              void *classContext,
                                              cy_stc_usb_dev_context_t *devContext);

static uint32_t GetInterfaceComPort(uint32_t interface, cy_stc_usb_dev_cdc_context_t const *context);

static uint32_t ReadInternalBuffer(cy_stc_usb_dev_cdc_comport_t* port, uint8_t *buffer,
                                   uint32_t size);

static bool IsEndpointReady(uint32_t endpoint, cy_stc_usb_dev_context_t const *context);

static cy_stc_usb_dev_cdc_comport_t* GetCom(uint32_t port, cy_stc_usb_dev_cdc_context_t *context);


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_Init
****************************************************************************//**
*
* Initializes the CDC class.
* This function must be called to enable USB Device CDC functionality.
*
* \param config
* The pointer to the CDC configuration
* structure \ref cy_stc_usb_dev_cdc_config_t.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
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
cy_en_usb_dev_status_t Cy_USB_Dev_CDC_Init(cy_stc_usb_dev_cdc_config_t  const *config,
                                           cy_stc_usb_dev_cdc_context_t       *context,
                                           cy_stc_usb_dev_context_t           *devContext)
{
    if ((NULL == context) || (NULL == devContext))
    {
        return CY_USB_DEV_BAD_PARAM;
    }

    uint32_t portIndex;

    for (portIndex = 0UL; (portIndex < CY_USB_DEV_CDC_COMPORT_NUMBER); portIndex++)
    {
        /* Default value for Lines Coding and Serial State notification */
        const uint8_t initLinesCoding[CY_USB_DEV_CDC_LINE_CODING_SIZE]  = INIT_LINES_CODING;
        const uint8_t initSerialState[CY_USB_DEV_CDC_SERIAL_STATE_SIZE] = INIT_SERIAL_STATE;

        /* Get COM port */
        cy_stc_usb_dev_cdc_comport_t* com = &context->port[portIndex];

        /* Initialize default values: lines coding and serial state */
        (void) memcpy((void *) com->linesCoding, (const void *)initLinesCoding, CY_USB_DEV_CDC_LINE_CODING_SIZE);
        (void) memcpy((void *) com->serialStateNotification, (const void *)initSerialState, CY_USB_DEV_CDC_SERIAL_STATE_SIZE);

        /* Set COM port disable */
        com->valid = false;
        com->writeBufIdx  = 0U;
        com->readBufIdx   = 0U;
        com->linesChanged = CY_USB_DEV_CDC_LINE_NOT_CHANGED;

        /* Copy data from configuration */
        com->buffer     = (NULL != config) ? config->buffer[portIndex] : NULL;
        com->bufferSize = (NULL != config) ? config->bufferSize[portIndex] : 0U;
    }

    /* Remove custom handlers */
    context->requestCompleted = NULL;
    context->requestReceived  = NULL;

    /* Store device context */
    context->devContext = devContext;

    /* Register CDC handlers */
    Cy_USB_Dev_RegisterClassSetConfigCallback(&HandleSetConfig, Cy_USB_Dev_CDC_GetClass(context));
    Cy_USB_Dev_RegisterClassRequestRcvdCallback(&HandleRequest, Cy_USB_Dev_CDC_GetClass(context));
    Cy_USB_Dev_RegisterClassRequestCmpltCallback(&HandleRequestComplete, Cy_USB_Dev_CDC_GetClass(context));

    return Cy_USB_Dev_RegisterClass(&context->classItem, &context->classObj, context, devContext);
}


/*******************************************************************************
* Function Name: HandleSetConfig
****************************************************************************//**
*
* Handles SET_CONFIGURATION request event. This function finds COM ports
* information for a certain configuration: CDC interfaces and CDC endpoints.
* This information is used to call any CDC function.
*
* \param configuration
* The CDC configuration index.
*
* \param classContext
* The pointer to the context structure of the Class
* \ref cy_stc_usb_dev_cdc_context_t allocated by the user.
*
* \param devContext
* The pointer to the context structure of the Device
* \ref cy_stc_usb_dev_context_t allocated by the user.
*
* \return
* Returns \ref CY_USB_DEV_SUCCESS.
* The configuration is still valid if COM port is not found.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleSetConfig(uint32_t configuration,
                                              void *classContext,
                                              cy_stc_usb_dev_context_t *devContext)
{
    /* Get CDC context */
    cy_stc_usb_dev_cdc_context_t *context = (cy_stc_usb_dev_cdc_context_t *) classContext;

    /* Invalidate COM ports */
    context->port[COM1].valid = false;
    context->port[COM2].valid = false;

    if (configuration > 0U)
    {
        /* Get current configuration */
        cy_stc_usb_dev_configuration_t const *config = devContext->devDescriptors->configurations[configuration - 1U];

        uint32_t intf;
        uint32_t portInt  = 0U;
        uint32_t portData = 0U;
        uint32_t cdcEpNum = 0U;

        for (intf = 0U; intf < config->numInterfaces; ++intf)
        {
            /* CDC does not support alternate settings */
            uint32_t alt = 0U;

            /* Get alternate settings that belong to this interface */
            cy_stc_usb_dev_alternate_t const **altStructs = config->interfaces[intf]->alternates;

            /* Get pointer to current alternate descriptor */
            cy_stc_usbdev_interface_descr_t const *curAlternate = (cy_stc_usbdev_interface_descr_t const *)
                                                                   ((const void *)(altStructs[alt]->interfaceDescriptor));

            /* Check interface class */
            if (CY_USB_DEV_CDC_CLASS == curAlternate->bInterfaceClass)
            {
                /* Get endpoint descriptor */
                cy_stc_usbdev_endpoint_descr_t const *ep = (cy_stc_usbdev_endpoint_descr_t const *)
                                                            ((const void *)(altStructs[alt]->endpoints[0U]->endpointDescriptor));

                context->port[portInt].interfaceNum = (uint8_t) intf;

                context->port[portInt].commEp       = (uint8_t) CY_USB_DEV_EPADDR2EP(ep->bEndpointAddress);
                context->port[portInt].commEpSize   = CY_USB_DEV_GET_CFG_WORD(&ep->wMaxPacketSize);
                context->port[portInt].serialStateNotification[SERIAL_STATE_WINDEX_OFFSET] = (uint8_t) intf;

                portInt = 1U;
                cdcEpNum++;
            }
            else if (CY_USB_DEV_CDC_CLASS_DATA == curAlternate->bInterfaceClass)
            {
                uint32_t endpoint;

                /* Check all endpoints that belong to interface */
                for (endpoint = 0U; endpoint < altStructs[alt]->numEndpoints; ++endpoint)
                {
                    /* Get endpoint descriptor */
                    cy_stc_usbdev_endpoint_descr_t const *ep = (cy_stc_usbdev_endpoint_descr_t const *)
                                                                ((const void *)(altStructs[alt]->endpoints[endpoint]->endpointDescriptor));

                    if (CY_USB_DEV_IS_EP_DIR_IN(ep->bEndpointAddress))
                    {
                        context->port[portData].dataInEp     = (uint8_t) CY_USB_DEV_EPADDR2EP(ep->bEndpointAddress);
                        context->port[portData].dataInEpSize = CY_USB_DEV_GET_CFG_WORD(&ep->wMaxPacketSize);
                    }
                    else
                    {
                        context->port[portData].dataOutEp     = (uint8_t) CY_USB_DEV_EPADDR2EP(ep->bEndpointAddress);
                        context->port[portData].dataOutEpSize = CY_USB_DEV_GET_CFG_WORD(&ep->wMaxPacketSize);

                        /* Enable endpoint to receive data from Host.
                        * Discard status after set configuration is safe.
                        */
                        (void) Cy_USB_Dev_StartReadEp((uint32_t) context->port[portData].dataOutEp, devContext);
                    }

                    cdcEpNum++;
                }

                portData = 1U;
            }
            else
            {
                /* Skip: Interface Class is not CDC */
            }
        }

        context->port[COM1].valid = (cdcEpNum >= SINGLE_COM_PORT_EP_NUM);
        context->port[COM2].valid = (DUAL_COM_PORT_EP_NUM == cdcEpNum);
    }

    /* If comport is not found, it is marked not valid */
    return CY_USB_DEV_SUCCESS;
}


/*******************************************************************************
* Function Name: HandleRequest
****************************************************************************//**
*
* Handles CDC class requests (SETUP packet received event).
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param classContext
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \param devContext
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for
* internal configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                            void *classContext,
                                            cy_stc_usb_dev_context_t *devContext)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    /* Process CDC Class requests */
    if (CY_USB_DEV_CLASS_TYPE == transfer->setup.bmRequestType.type)
    {
        cy_stc_usb_dev_cdc_context_t *context = (cy_stc_usb_dev_cdc_context_t *) classContext;

        uint32_t portNum = GetInterfaceComPort((uint32_t) transfer->setup.wIndex, context);

        if (IS_COM_VALID(portNum))
        {
            switch (transfer->setup.bRequest)
            {
                case CY_USB_DEV_CDC_RQST_SET_LINE_CODING:
                {
                    transfer->remaining = SET_LINE_CODING_LENGTH;
                    transfer->notify    = true;
                    retStatus = CY_USB_DEV_SUCCESS;
                }
                break;

                case CY_USB_DEV_CDC_RQST_GET_LINE_CODING:
                {
                    transfer->ptr       = (uint8_t *) context->port[portNum].linesCoding;
                    transfer->remaining = SET_LINE_CODING_LENGTH;
                    retStatus = CY_USB_DEV_SUCCESS;
                }
                break;

                case CY_USB_DEV_CDC_RQST_SET_CONTROL_LINE_STATE:
                {
                    context->port[portNum].linesControlBitmap = (uint8_t) transfer->setup.wValue;
                    context->port[portNum].linesChanged |= CY_USB_DEV_CDC_LINE_CONTROL_CHANGED;
                    retStatus = CY_USB_DEV_SUCCESS; /* There is Data stage */
                }
                break;

                default:
                {
                    /* Request was not recognized. Try custom request handler. */
                    if (NULL != context->requestReceived)
                    {
                        retStatus = context->requestReceived(transfer, context, devContext);
                    }
                }
                break;
            }
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: HandleRequestComplete
****************************************************************************//**
*
* Completes handling CDC class requests that expect data from the Host.
* Involved when data from the Host has been received.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param classContext
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \param devContext
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for
* internal configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleRequestComplete(cy_stc_usb_dev_control_transfer_t *transfer,
                                                    void *classContext,
                                                    cy_stc_usb_dev_context_t *devContext)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    /* Process CDC Class requests */
    if (CY_USB_DEV_CLASS_TYPE == transfer->setup.bmRequestType.type)
    {
        cy_stc_usb_dev_cdc_context_t *context = (cy_stc_usb_dev_cdc_context_t *) classContext;

        uint32_t portNum = GetInterfaceComPort((uint32_t) transfer->setup.wIndex, context);

        if (IS_COM_VALID(portNum))
        {
            switch (transfer->setup.bRequest)
            {
                case CY_USB_DEV_CDC_RQST_SET_LINE_CODING:
                {
                    /* Copy received data */
                    (void) memcpy((void *) context->port[portNum].linesCoding, (const void *)transfer->ptr, CY_USB_DEV_CDC_LINE_CODING_SIZE);

                    context->port[portNum].linesChanged |= CY_USB_DEV_CDC_LINE_CODING_CHANGED;

                    retStatus = CY_USB_DEV_SUCCESS;
                }
                break;

                default:
                {
                    /* Request was not recognized. Try custom request handler. */
                    if (NULL != context->requestCompleted)
                    {
                        retStatus = context->requestCompleted(transfer, context, devContext);
                    }
                }
                break;
            }
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: GetInterfaceComPort
****************************************************************************//**
*
* Returns number of COM port number that belong to a certain CDC interface.
*
* \param interface
* Interface number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* COM port number (COM1 or COM2). INVALID_COM if COM port does not exist.
*
*******************************************************************************/
static uint32_t GetInterfaceComPort(uint32_t interface, cy_stc_usb_dev_cdc_context_t const *context)
{
    uint32_t portNum;
    uint32_t locInterface = (uint32_t) CY_LO8(interface);

    if (context->port[COM1].interfaceNum == locInterface)
    {
        portNum = COM1;
    }
    else if (context->port[COM2].interfaceNum == locInterface)
    {
        portNum = COM2;
    }
    else
    {
        portNum = INVALID_COM;
    }

    return (portNum);
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_PutData
****************************************************************************//**
*
* Sends a specified number of bytes to USB Host.
* Call \ref Cy_USB_Dev_CDC_IsReady function to ensure that the COM port
* (CDC Data interface) is ready for sending data to the USB Host before calling
* this function.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param buffer
* The pointer to the buffer containing data bytes to be sent. \n
* Allocate buffer using \ref CY_USB_DEV_ALLOC_ENDPOINT_BUFFER macro to make
* it USBFS driver configuration independent (See \ref group_usb_dev_ep_buf_alloc
* for more information).
*
* \param size
* The number of bytes to send.
* This value must be less than or equal to the maximum packet size of the
* CDC Data interface IN endpoint that belongs to the specified COM port.
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
cy_en_usb_dev_status_t Cy_USB_Dev_CDC_PutData(uint32_t port, uint8_t const *buffer, uint32_t size,
                                              cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_BAD_PARAM;
    cy_stc_usb_dev_cdc_comport_t* com = GetCom(port, context);

    if (com->valid)
    {
        retStatus = Cy_USB_Dev_WriteEpNonBlocking((uint32_t) com->dataInEp, buffer, size, context->devContext);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_PutString
****************************************************************************//**
*
* Sends a null terminated string to the USB Host. This function is blocking and
* returns after successful USB Host transfer, or an error or timeout occurred.
* Call \ref Cy_USB_Dev_CDC_IsReady function to ensure that the COM port
* (CDC Data interface) is ready for sending data to the USB Host before calling
* this function.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param string
* The pointer to the string to be sent. \n
* The string must be allocated following rules in the section
* \ref group_usb_dev_ep_buf_alloc to be USBFS driver configuration
* independent.
*
* \param timeout
* Defines in milliseconds the time for which this function can block.
* If that time expires, the function returns.
* To wait forever, pass \ref CY_USB_DEV_WAIT_FOREVER.
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
* \note
* If string parameter is a constant string (example: "USBUART"), it is stored
* in the stack and aligned to 4 bytes boundary what makes it USBFS
* driver configuration independent.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_CDC_PutString(uint32_t port, char_t const *string, int32_t timeout,
                                                cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_BAD_PARAM;
    cy_stc_usb_dev_cdc_comport_t* com = GetCom(port, context);

    if (com->valid)
    {
        uint32_t endpoint = com->dataInEp;
        uint32_t stringLen = strlen(string);
        uint32_t sendLen = 0U;
        uint32_t sendIndex = 0U;
        uint32_t bufSize = com->dataInEpSize;

        do
        {
            /* Send size equal to endpoint max packet sizes */
            sendLen = (stringLen > bufSize) ? bufSize : stringLen;

            retStatus = Cy_USB_Dev_WriteEpBlocking(endpoint, (uint8_t const *) &string[sendIndex],
                                                   sendLen, timeout, context->devContext);
            stringLen -= sendLen;
            sendIndex += sendLen;
        }
        while ((stringLen > 0U) && (CY_USB_DEV_SUCCESS == retStatus));

        /* If last packet is exactly maximum packet size, it shall be followed
        * by a zero-length packet to assure the end of segment is properly
        * identified by the terminal.
        */
        if ((sendLen == bufSize) && (CY_USB_DEV_SUCCESS == retStatus))
        {
            uint8_t dummyByte = 0U;
            retStatus = Cy_USB_Dev_WriteEpBlocking(endpoint, &dummyByte,
                                                   0U, timeout, context->devContext);
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetCount
****************************************************************************//**
*
* Returns the number of bytes that were received from the USB Host and can be
* read using \ref Cy_USB_Dev_CDC_GetData or \ref Cy_USB_Dev_CDC_GetChar
* functions.
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
* Returns the number of bytes that were received.
*
*******************************************************************************/
uint32_t Cy_USB_Dev_CDC_GetCount(uint32_t port, cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    uint32_t count = 0U;
    cy_stc_usb_dev_cdc_comport_t *com = GetCom(port, context);

    if (com->valid)
    {
        /* Read number of bytes in local buffer */
        count = com->writeBufIdx;

        /* Local buffer is empty. Check if there is data in the endpoint buffer */
        if (0U == count)
        {
            if (IsEndpointReady((uint32_t) com->dataOutEp, context->devContext))
            {
                /* Update count if Host wrote anything into the endpoint */
                count = Cy_USB_Dev_GetEpNumToRead((uint32_t) com->dataOutEp, context->devContext);
            }
        }
    }

    return count;
}


/*******************************************************************************
* Function Name: GetCom
****************************************************************************//**
*
* Returns pointer to port structure cy_stc_usb_dev_cdc_comport_t
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
* Pointer to port structure cy_stc_usb_dev_cdc_comport_t
*
*******************************************************************************/
static cy_stc_usb_dev_cdc_comport_t* GetCom(uint32_t port, cy_stc_usb_dev_cdc_context_t *context)
{
    return &context->port[port];
}


/*******************************************************************************
* Function Name: IsEndpointReady
****************************************************************************//**
*
* Check if endpoint state is IDLE or COMPLETED.
*
* \param endpoint
* The endpoint number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* True - endpoint is ready. False - endpoint is not ready.
*
*******************************************************************************/
static bool IsEndpointReady(uint32_t endpoint, cy_stc_usb_dev_context_t const *context)
{
    cy_en_usb_dev_ep_state_t epState;

    epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase,
                                                endpoint,
                                                context->drvContext);

    return ((CY_USB_DEV_EP_IDLE == epState) || (CY_USB_DEV_EP_COMPLETED == epState));
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_IsDataReady
****************************************************************************//**
*
* Returns status if the COM port (CDC Data interface) received data from the
* USB Host (including zero-length packet).
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
* * True - the COM port (CDC Data interface) received data from the USB Host.
* * False - the COM port (CDC Data interface) is waiting for data from the
*           USB Host.
*
*******************************************************************************/
bool Cy_USB_Dev_CDC_IsDataReady(uint32_t port, cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    bool retStatus = false;
    cy_stc_usb_dev_cdc_comport_t* com = GetCom(port, context);

    if (com->valid)
    {
        retStatus = IsEndpointReady((uint32_t) com->dataOutEp, context->devContext);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_IsReady
****************************************************************************//**
*
* Returns status if the COM port (CDC Data interface) is ready for sending
* new data.
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
* * True - the COM port (CDC Data interface) is ready for sending new data.
* * False - the COM port (CDC Data interface) is waiting for the USB Host to
*           read previous data.
*
*******************************************************************************/
bool Cy_USB_Dev_CDC_IsReady(uint32_t port, cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    bool retStatus = false;
    cy_stc_usb_dev_cdc_comport_t* com = GetCom(port, context);

    if (com->valid)
    {
        retStatus = IsEndpointReady((uint32_t) com->dataInEp, context->devContext);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: ReadInternalBuffer
****************************************************************************//**
*
* Internal function used for copy data from internal buffer
*
* \param port
* Pointer to the port structure.
*
* \param buffer
* Pointer to the data array where data will be placed.
*
* \param size
* Number of bytes to read into the data array from the RX buffer. The maximum
* length is limited by the number of received bytes.
*
* \return
* Number of copied bytes.
*
*******************************************************************************/
static uint32_t ReadInternalBuffer(cy_stc_usb_dev_cdc_comport_t* port, uint8_t *buffer,
                         uint32_t size)
{
    uint32_t numBytes = port->writeBufIdx;
    uint32_t idx = port->readBufIdx;
    uint32_t numToCopy = (size > numBytes) ? numBytes : size;

    /* Copy data from internal buffer to the user buffer */
    (void) memcpy(buffer, &port->buffer[idx], numToCopy);
    numBytes -= numToCopy;

    /* Adjust buffer pointers */
    if (0U == numBytes)
    {
        port->readBufIdx  = 0U;
        port->writeBufIdx = 0U;
    }
    else
    {
        port->readBufIdx  += numToCopy;
        port->writeBufIdx -= numToCopy;
    }

    return numToCopy;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetData
****************************************************************************//**
*
* Read a specified number of data bytes received from USB Host by the COM port
* (CDC Data interface).
* Call \ref Cy_USB_Dev_CDC_IsDataReady function to ensure that
* data is received from the USB Host before calling this function.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param buffer
* The pointer to buffer that stores data that was read. \n
* Allocate buffer using \ref CY_USB_DEV_ALLOC_ENDPOINT_BUFFER macro to make
* it USBFS driver configuration independent (See \ref group_usb_dev_ep_buf_alloc
* for more information).
*
* \param size
* The number of bytes to read.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data keeping. The user must not modify
* anything in this structure.
*
* \return
* The number of bytes that were actually read.
*
*******************************************************************************/
uint32_t Cy_USB_Dev_CDC_GetData(uint32_t port, uint8_t *buffer, uint32_t size,
                                    cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    uint32_t actSize = 0U;
    cy_stc_usb_dev_cdc_comport_t * com = GetCom(port, context);

    if ((com->valid) &&
        (NULL != com->buffer) && (com->bufferSize == com->dataOutEpSize))
    {
        /* Check whether buffer has some data */
        if (com->writeBufIdx > 0U)
        {
            actSize = ReadInternalBuffer(com, buffer, size);
        }
        else
        {
            cy_en_usb_dev_status_t locStatus;
            locStatus = Cy_USB_Dev_ReadEpNonBlocking((uint32_t) com->dataOutEp, com->buffer, com->bufferSize,
                                                     &com->writeBufIdx, context->devContext);

            if (CY_USB_DEV_SUCCESS == locStatus)
            {
                actSize = ReadInternalBuffer(com, buffer, size);

                /* ReadEpNonBlocking returned success therefore safe to discard status */
                (void) Cy_USB_Dev_StartReadEp((uint32_t) com->dataOutEp, context->devContext);
            }
        }
    }

    return actSize;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetAll
****************************************************************************//**
*
* Read all data received from USB Host by the COM port (CDC Data interface).
* Call \ref Cy_USB_Dev_CDC_IsDataReady function to ensure that
* data is received from the USB Host before calling this function.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param buffer
* The pointer to buffer that stores data that was read. \n
* Allocate buffer using \ref CY_USB_DEV_ALLOC_ENDPOINT_BUFFER macro to make
* it USBFS driver configuration independent (See \ref group_usb_dev_ep_buf_alloc
* for more information).
*
* \param maxSize
* The size of buffer to read data into.
* This value must be not be less then CDC Data interface OUT endpoint maximum
* packet size that belongs to specified COM port.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_cdc_context_t
* allocated by the user. The structure is used during the CDC Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* The number of bytes that were actually read.
*
*******************************************************************************/
uint32_t Cy_USB_Dev_CDC_GetAll(uint32_t port, uint8_t *buffer, uint32_t maxSize,
                               cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    uint32_t actSize = 0U;
    cy_stc_usb_dev_cdc_comport_t * com = GetCom(port, context);

    if (com->valid)
    {
        cy_en_usb_dev_status_t locStatus;

        locStatus = Cy_USB_Dev_ReadEpNonBlocking((uint32_t) com->dataOutEp, buffer, maxSize, &actSize,
                                                 context->devContext);

        /* Start read endpoint after read completed */
        if (CY_USB_DEV_SUCCESS == locStatus)
        {
            /* ReadEpNonBlocking returned success therefore safe to discard status */
            (void) Cy_USB_Dev_StartReadEp((uint32_t) com->dataOutEp, context->devContext);
        }
    }

    return actSize;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetChar
****************************************************************************//**
*
* Reads one byte of received data.
* Call \ref Cy_USB_Dev_CDC_IsDataReady function to ensure that
* data is received from the USB Host before calling this function.
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
* Received one character or zero value to indicate there is no data.
*
*******************************************************************************/
char_t Cy_USB_Dev_CDC_GetChar(uint32_t port, cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    uint8_t  data = 0U;
    uint32_t number = Cy_USB_Dev_CDC_GetData(port, &data, 1U, context);

    if (0U == number)
    {
        data = 0U;
    }

    return (char_t) data;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_SendSerialState
****************************************************************************//**
*
* Sends the serial state notification to the host using the COM port
* (CDC interface) IN interrupt endpoint.
* Call \ref Cy_USB_Dev_CDC_IsNotificationReady function to ensure that
* COM port (CDC interface) is ready send notification before calling this
* function.
*
* \param port
* COM port number. Valid ports are 0 and 1.
*
* \param serialState
* 16-bit value that will be sent from the USB Device to the USB Host as
* SERIAL_STATE notification using the CDC interface IN interrupt endpoint.
* Refer to revision 1.2 of the CDC PSTN Subclass specification for bit field
* definitions of the 16-bit serial state value.
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
* \note
* The maximum packet size of the CDC interface IN interrupt endpoint
* (that belongs to specified COM port) must be at least 10 bytes to send
* serial state notifications.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_CDC_SendSerialState(uint32_t port, uint32_t serialState,
                                                      cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_BAD_PARAM;
    cy_stc_usb_dev_cdc_comport_t* com = GetCom(port, context);

    if ((com->valid) &&
        (CY_USB_DEV_CDC_SERIAL_STATE_SIZE <= com->commEpSize))
    {
        /* Update serial state */
        com->serialStateBitmap = (uint16_t) serialState;

        com->serialStateNotification[SERIAL_STATE_WSERIALSTATE_LSB_OFFSET] = CY_LO8(serialState);
        com->serialStateNotification[SERIAL_STATE_WSERIALSTATE_MSB_OFFSET] = CY_HI8(serialState);

        retStatus = Cy_USB_Dev_WriteEpNonBlocking((uint32_t)  com->commEp,
                                                  (uint8_t *) com->serialStateNotification,
                                                  CY_USB_DEV_CDC_SERIAL_STATE_SIZE,
                                                  context->devContext);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_IsNotificationReady
****************************************************************************//**
*
* Returns if the COM port (CDC interface) is ready to send notification to
* the USB Host.
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
* * True - the COM port (CDC interface) is ready for sending new notification.
* * False - the COM port (CDC interface) is waiting for the USB Host to read
* previous notification.
*
*******************************************************************************/
bool Cy_USB_Dev_CDC_IsNotificationReady(uint32_t port, cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    bool retStatus = false;
    cy_stc_usb_dev_cdc_comport_t* com = GetCom(port, context);

    if (com->valid)
    {
        retStatus = IsEndpointReady((uint32_t) com->commEp, context->devContext);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_CDC_GetDTERate
****************************************************************************//**
*
* Returns the data terminal rate set for this port in bits per second.
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
* Data rate in bits per second.
*
*******************************************************************************/
uint32_t Cy_USB_Dev_CDC_GetDTERate(uint32_t port, cy_stc_usb_dev_cdc_context_t *context)
{
    CY_ASSERT_L1(IS_COM_VALID(port));

    cy_stc_usb_dev_cdc_comport_t* com = GetCom(port, context);

    uint32_t rate = com->linesCoding[LINE_CODING_RATE_OFFSET + 3U];

    rate = (rate << 8U) | com->linesCoding[LINE_CODING_RATE_OFFSET + 2U];
    rate = (rate << 8U) | com->linesCoding[LINE_CODING_RATE_OFFSET + 1U];
    rate = (rate << 8U) | com->linesCoding[LINE_CODING_RATE_OFFSET];

    return rate;
}

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */


/* [] END OF FILE */
