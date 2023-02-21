/***************************************************************************//**
* \file cy_usb_dev.c
* \version 2.10
*
* Provides API implementation of the USBFS device middleware.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_usb_dev.h"

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))


/*******************************************************************************
*                             Internal Macro
*******************************************************************************/

#define GET_CFG_WORD(addr)      CY_USB_DEV_GET_CFG_WORD(addr)
#define VAL2IDX(val)            ( (uint32_t) (val) - 1U)
#define GET_UINT16(lsb, msb)    ((lsb) | (uint16_t) (((uint16_t) (msb)) << 8UL))

/* Decode setup request bmRequestType */
#define SETUP_RQST_RCPT_Pos  (0)
#define SETUP_RQST_RCPT_Msk  (0x1FU)
#define SETUP_RQST_TYPE_Pos  (5)
#define SETUP_RQST_TYPE_Msk  (0x60u)
#define SETUP_RQST_DIR_Pos   (7)
#define SETUP_RQST_DIR_Msk   (0x80U)

/* Setup request layout in the buffer */
#define SETUP_RQST_POS         (0)
#define SETUP_RQST_TYPE_POS    (1)
#define SETUP_VALUE_LSB_POS    (2)
#define SETUP_VALUE_MSB_POS    (3)
#define SETUP_INDEX_LSB_POS    (4)
#define SETUP_INDEX_MSB_POS    (5)
#define SETUP_LENGTH_LSB_POS   (6)
#define SETUP_LENGTH_MSB_POS   (7)

/* Field position in the descriptors */
#define CONFIG_DESCR_LENGTH_LSB_POS     (2)     /* Configuration descriptor length (LSB) byte position */
#define CONFIG_DESCR_LENGTH_MSB_POS     (3)     /* Configuration descriptor length (MSB) byte position */
#define BOS_DESCR_LENGTH_LSB_POS        (2)     /* BOS descriptor length (LSB) byte position */
#define BOS_DESCR_LENGTH_MSB_POS        (3)     /* BOS descriptor length (MSB) byte position */
#define CONFIG_DESCR_ATTRIB_POS         (7)     /* Configuration descriptor attribute byte position */
#define DEVICE_DESCR_ISN_STRING_POS     (16)    /* Position of Serial Number in Device Descriptor */
#define STRING_DESCR_LENGTH_POS         (0)     /* Position inside string descriptor where length is stored */
#define STRING_DESCR_TYPE_POS           (1)     /* Position inside string descriptor where type is stored */

/* bmAttributes in configuration descriptor */
#define CONFIG_ATTR_SELF_POWERED_MASK   (0x40U) /* Configuration attribute Self-Powered mask */
#define CONFIG_ATTR_REMOTE_WAKEUP_MASK  (0x20U) /* Configuration attribute Remote Wakeup mask */

/* Fixed string descriptor indexes */
#define STRING_LANGID_INDEX   (0U)
#define STRING_IMSOS_INDEX    (0xEEU)
#define EXT_OS_DESC_LENGTH_BYTE0_POS    (0x0U)
#define EXT_OS_DESC_LENGTH_BYTE1_POS    (0x1U)
#define EXT_OS_DESC_LENGTH_BYTE2_POS    (0x2U)
#define EXT_OS_DESC_LENGTH_BYTE3_POS    (0x3U)


/*******************************************************************************
*                            Static Functions Prototypes
*******************************************************************************/

static int32_t HandleTimeout(int32_t milliseconds);

#if defined(CY_IP_MXUSBFS)
static void InitSerialNumberString(cy_stc_usb_dev_context_t *context);
#endif /* defined(CY_IP_MXUSBFS)  */

static cy_en_usb_dev_status_t ConvertEndpointStateToStatus(cy_en_usb_dev_ep_state_t epState);

static void BusResetCallback(USBFS_Type *base, struct cy_stc_usbfs_dev_drv_context *drvContext);
static void Ep0SetupCallback(USBFS_Type *base, struct cy_stc_usbfs_dev_drv_context *drvContext);
static void Ep0InCallback   (USBFS_Type *base, struct cy_stc_usbfs_dev_drv_context *drvContext);
static void Ep0OutCallback  (USBFS_Type *base, struct cy_stc_usbfs_dev_drv_context *drvContext);

static cy_en_usb_dev_status_t HandleSetup(cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t HandleIn   (cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t HandleOut  (cy_stc_usb_dev_context_t *context);

static void DecodeSetupPacket (uint8_t const *data, cy_stc_usb_dev_setup_packet_t *packet);

static cy_en_usb_dev_status_t HandleStandardRequests (cy_stc_usb_dev_control_transfer_t *transfer,
                                                      cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t GetDescriptorRequest   (cy_stc_usb_dev_control_transfer_t *transfer,
                                                      cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t GetConfigurationRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                      cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t GetInterfaceRequest    (cy_stc_usb_dev_control_transfer_t *transfer,
                                                      cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t GetStatusRequest       (cy_stc_usb_dev_control_transfer_t *transfer,
                                                      cy_stc_usb_dev_context_t const *context);
static cy_en_usb_dev_status_t ClearFeatureRequest    (cy_stc_usb_dev_control_transfer_t const *transfer,
                                                      cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t SetAddressRequest      (cy_stc_usb_dev_control_transfer_t const *transfer,
                                                      cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t SetConfigurationRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                      cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t SetInterfaceRequest    (cy_stc_usb_dev_control_transfer_t const *transfer,
                                                      cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t SetFeatureRequest      (cy_stc_usb_dev_control_transfer_t const *transfer,
                                                      cy_stc_usb_dev_context_t *context);

static cy_en_usb_dev_status_t HandleClassRequests(cy_stc_usb_dev_class_ll_item_t    *curItem,
                                                  cy_stc_usb_dev_control_transfer_t *transfer,
                                                  cy_stc_usb_dev_context_t          *context);
static cy_en_usb_dev_status_t HandleClassRequestsCompleted(cy_stc_usb_dev_class_ll_item_t    *curItem,
                                                           cy_stc_usb_dev_control_transfer_t *transfer,
                                                           cy_stc_usb_dev_context_t          *context);

static cy_en_usb_dev_status_t GetExtOsStringDescriptors(cy_stc_usb_dev_ms_os_string_t const *msOsString,
                                                        cy_stc_usb_dev_control_transfer_t *transfer);
static cy_en_usb_dev_status_t HandleVendorRequests(cy_stc_usb_dev_control_transfer_t *transfer,
                                                   cy_stc_usb_dev_context_t *context);
static cy_en_usb_dev_status_t HandleVendorRequestsCompleted(cy_stc_usb_dev_control_transfer_t *transfer,
                                                            cy_stc_usb_dev_context_t *context);

static cy_en_usb_dev_status_t CallSetInterfaceCallbacks(uint32_t interface,
                                                        uint32_t alternate,
                                                        cy_stc_usb_dev_class_ll_item_t *curItem,
                                                        cy_stc_usb_dev_context_t *context);

static cy_en_usb_dev_status_t ConfigureDataEndpoints(uint32_t config, cy_stc_usb_dev_context_t *context);

static cy_en_usb_dev_status_t InterfaceRemoveDataEndpoints(uint32_t numEndpoints,
                                          cy_stc_usb_dev_endpoint_t const * const *epsPool,
                                          cy_stc_usb_dev_context_t   *context);

static cy_en_usb_dev_status_t InterfaceAddDataEndpoints(uint32_t numEndpoints,
                                       cy_stc_usb_dev_endpoint_t const * const *epsPool,
                                       cy_stc_usb_dev_context_t   *context);


/*******************************************************************************
* Function Name: Cy_USB_Dev_Init
****************************************************************************//**
*
* Initialize the USB Device stack and underneath USBFS hardware driver.
*
* \param base
* The pointer to the USBFS instance.
*
* \param drvConfig
* The pointer to the USBFS driver configuration structure.
*
* \param drvContext
* The pointer to the USBFS driver context structure allocated by the user.
* The structure is used during the USBFS driver operation for internal
* configuration and data retention. The user must not modify anything in
* this structure.
*
* \param device
* The pointer to the device structure \ref cy_stc_usb_dev_device_t.
*
* \param config
* The pointer to the driver configuration structure \ref cy_stc_usb_dev_config_t.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for
* internal configuration and data retention. The user must not modify anything
* in this structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
* \note
* The configuration of USB clocks, pins, and interrupts is not handled by this
* function and must be done on the application level.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_Init(USBFS_Type *base,
                                       struct cy_stc_usbfs_dev_drv_config const *drvConfig,
                                       struct cy_stc_usbfs_dev_drv_context      *drvContext,
                                       cy_stc_usb_dev_device_t  const *device,
                                       cy_stc_usb_dev_config_t  const *config,
                                       cy_stc_usb_dev_context_t       *context)
{
    /* Input parameters verification */
    if ((NULL == device) || (NULL == config)    || (NULL == context) ||
        (NULL == base)   || (NULL == drvConfig) || (NULL == drvContext))
    {
        return CY_USB_DEV_BAD_PARAM;
    }

    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_DRV_HW_ERROR;

    /* Store driver information in device */
    context->drvBase    = base;
    context->drvContext = drvContext;

    /* Set default state */
    context->state   = CY_USB_DEV_DISABLED;
    context->configuration = 0U;
    context->classRoot = NULL;

    /* Configure endpoint 0 buffer */
    context->ControlTransfer.buffer  = config->ep0Buffer;
    context->ControlTransfer.bufferSize = config->ep0BufferSize;

    /* Store link to descriptors */
    context->devDescriptors = device;

    /* Initialize delay function */
    context->handleTimeout = &HandleTimeout;

    /* Initialize event callback */
    context->eventsCallback = NULL;

#if defined(CY_IP_MXUSBFS)

    /* Initialize serial string descriptor and set pointer */
    InitSerialNumberString(context);

#endif /* defined(CY_IP_MXUSBFS)  */

    context->getSerialNumString = NULL;

    /* Initialize vendor-specific callbacks */
    context->vndRequestReceived  = NULL;
    context->vndRequestCompleted = NULL;

    /* Link driver and device context */
    Cy_USBFS_Dev_Drv_SetDevContext(base, context, drvContext);

    /* Configure driver */
    retStatus = (cy_en_usb_dev_status_t) Cy_USBFS_Dev_Drv_Init(base, drvConfig, drvContext);

    if (CY_USB_DEV_SUCCESS == retStatus)
    {
        /* Hook device handlers to be called by driver */
        Cy_USBFS_Dev_Drv_RegisterServiceCallback(base, CY_USB_DEV_BUS_RESET, &BusResetCallback, drvContext);
        Cy_USBFS_Dev_Drv_RegisterServiceCallback(base, CY_USB_DEV_EP0_SETUP, &Ep0SetupCallback, drvContext);
        Cy_USBFS_Dev_Drv_RegisterServiceCallback(base, CY_USB_DEV_EP0_IN,    &Ep0InCallback,    drvContext);
        Cy_USBFS_Dev_Drv_RegisterServiceCallback(base, CY_USB_DEV_EP0_OUT,   &Ep0OutCallback,   drvContext);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_DeInit
****************************************************************************//**
*
* De-initialize the USB Device stack and underneath hardware driver.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
void Cy_USB_Dev_DeInit(cy_stc_usb_dev_context_t *context)
{
    Cy_USBFS_Dev_Drv_DeInit(context->drvBase, context->drvContext);

    /* IDe-initialize all callbacks */
    context->classRoot = NULL;
    context->eventsCallback = NULL;
    context->getSerialNumString  = NULL;
    context->vndRequestReceived  = NULL;
    context->vndRequestCompleted = NULL;
}


/*******************************************************************************
* Function Name: HandleTimeout
****************************************************************************//**
*
* Waits for 1 millisecond and returns updated number of milliseconds that remain
* to wait before timeout expires.
*
* \param milliseconds
* Number of milliseconds that remain to wait before timeout expires.
*
* \return
* Updated number of milliseconds remain to wait.
*
*******************************************************************************/
static int32_t HandleTimeout(int32_t milliseconds)
{
    Cy_SysLib_Delay(1U); /* Wait for 1 millisecond */

    return (milliseconds - 1);
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_Connect
****************************************************************************//**
*
* Enables pull-up on D+ (hardware supports only full-speed device) line to
* signal USB Device connection on USB Bus.
*
* \param blocking
* Wait until device is configured.
*
* \param timeout
* Defines in milliseconds the time for which this function can block.
* If that time expires, the USB Device is disconnected and the function returns.
* To wait forever, pass \ref CY_USB_DEV_WAIT_FOREVER.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_Connect(bool blocking, int32_t timeout, cy_stc_usb_dev_context_t *context)
{
    /* Returns SUCCESS except timeout when timeout is used */
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_SUCCESS;

    context->state = CY_USB_DEV_POWERED;
    Cy_USBFS_Dev_Drv_Enable(context->drvBase, context->drvContext);

    if (blocking)
    {
        if (CY_USB_DEV_WAIT_FOREVER == timeout)
        {
            /* Wait until device is configured */
            while (CY_USB_DEV_CONFIGURED != context->state)
            {
                (void) context->handleTimeout(timeout);
            }
        }
        else
        {
            /* Wait until device is configured or timeout */
            while ((CY_USB_DEV_CONFIGURED != context->state) && (timeout > 0))
            {
                timeout = context->handleTimeout(timeout);
            }

            /* Timeout expired disconnect USB Device */
            if (0 == timeout)
            {
                Cy_USB_Dev_Disconnect(context);
                retStatus = CY_USB_DEV_TIMEOUT;
            }
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_Disconnect
****************************************************************************//**
*
* Disables pull-up on D+ (hardware supports only full-speed device) line to
* signal USB Device disconnection on USB Bus.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
void Cy_USB_Dev_Disconnect(cy_stc_usb_dev_context_t *context)
{
    Cy_USBFS_Dev_Drv_Disable(context->drvBase, context->drvContext);

    /* Set device in the default state */
    context->state   = CY_USB_DEV_DISABLED;
    context->configuration  = 0U;
}


/*******************************************************************************
* Function Name: ConvertEndpointStateToStatus
****************************************************************************//**
*
* Converts endpoint state to the USB Device status code.
*
* \param epState
* Endpoint state cy_en_usb_dev_ep_state_t.
* The state CY_USB_DEV_EP_IDLE converted to \ref CY_USB_DEV_DRV_HW_DISABLED
* to indicate that current endpoint configuration was changed.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
static cy_en_usb_dev_status_t ConvertEndpointStateToStatus(cy_en_usb_dev_ep_state_t epState)
{
    cy_en_usb_dev_status_t retStatus;

    switch(epState)
    {
        case CY_USB_DEV_EP_COMPLETED:
            retStatus = CY_USB_DEV_SUCCESS;
        break;

        case CY_USB_DEV_EP_PENDING:
            retStatus = CY_USB_DEV_DRV_HW_BUSY;
        break;

        case CY_USB_DEV_EP_IDLE: /* Endpoint configuration is changed */
        case CY_USB_DEV_EP_STALLED:
            retStatus = CY_USB_DEV_DRV_HW_DISABLED;
        break;

        case CY_USB_DEV_EP_INVALID:
        case CY_USB_DEV_EP_DISABLED:
            retStatus = CY_USB_DEV_BAD_PARAM;
        break;

        default:
            retStatus = CY_USB_DEV_BAD_PARAM;
        break;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_AbortEpTransfer
****************************************************************************//**
*
* Aborts pending read or write endpoint operation.
* If there is any bus activity after abort operation requested the function
* waits for its completion or timeout. The timeout is time to transfer
* bulk or interrupt packet of maximum playload size. If this bus activity is
* a transfer to the aborting endpoint the received data is lost and endpoint
* transfer completion callbacks is not invoked.
* After function returns new read or write endpoint operation can be submitted.
*
* \param endpoint
* The data endpoint number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
* \note
* The abort operation is not supported for ISOC endpoints because
* these endpoints do not have handshake and are always accessible by the
* USB Host. Therefore, abort can cause unexpected behavior.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_AbortEpTransfer(uint32_t endpoint,
                                                  cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus;

    /* Request abort operation, on exit abort complete */
    retStatus = (cy_en_usb_dev_status_t) Cy_USBFS_Dev_Drv_Abort(context->drvBase, endpoint, context->drvContext);

    if (CY_USB_DEV_SUCCESS != retStatus)
    {
        retStatus = CY_USB_DEV_DRV_HW_ERROR;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_StartReadEp
****************************************************************************//**
*
* Start a reading on a certain endpoint.
*
* \param endpoint
* The OUT data endpoint number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
* \note
* The read is not allowed for OUT endpoints after SET_CONFIGURATION or
* SET_INTERFACE request therefore this function must be called before reading data
* from OUT endpoints.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_StartReadEp(uint32_t endpoint, cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t   retStatus;
    cy_en_usb_dev_ep_state_t epState;

    epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);

    /* Check that endpoint is ready for read operation */
    if ((CY_USB_DEV_EP_IDLE == epState) || (CY_USB_DEV_EP_COMPLETED == epState))
    {
        /* Enable endpoint to be written by host */
        Cy_USBFS_Dev_Drv_EnableOutEndpoint(context->drvBase, endpoint, context->drvContext);

        retStatus = CY_USB_DEV_SUCCESS;
    }
    else
    {
        /* Use endpoint state to get status */
        retStatus = ConvertEndpointStateToStatus(epState);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_ReadEpBlocking
****************************************************************************//**
*
* Read data received from USB Host from a certain endpoint. Before calling
* this function, \ref Cy_USB_Dev_StartReadEp must be called.
* This function is blocking and returns after successful USB Host transfer,
* or an error or timeout occurred.
*
* \param endpoint
* The OUT data endpoint number.
*
* \param buffer
* The pointer to buffer that stores data that was read. \n
* Allocate buffer using \ref CY_USB_DEV_ALLOC_ENDPOINT_BUFFER macro to make
* it USBFS driver configuration independent (See \ref group_usb_dev_ep_buf_alloc
* for more information).
*
* \param size
* The number of bytes to read.
* This value must be less or equal to endpoint maximum packet size.
*
* \param actSize
* The number of bytes that were actually read.
*
* \param timeout
* Defines in milliseconds the time for which this function can block.
* If that time expires the function returns.
* To wait forever pass \ref CY_USB_DEV_WAIT_FOREVER.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_ReadEpBlocking(uint32_t endpoint, uint8_t *buffer,
                                                 uint32_t size, uint32_t *actSize, int32_t timeout,
                                                 cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t   retStatus = CY_USB_DEV_SUCCESS;
    cy_en_usb_dev_ep_state_t epState;

    /* Get endpoint state before check it */
    epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);

    if (CY_USB_DEV_WAIT_FOREVER == timeout)
    {
        /* Wait until transfer is completed */
        while (CY_USB_DEV_EP_PENDING == epState)
        {
            (void) context->handleTimeout(timeout);

            /* Update endpoint state */
            epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);
        }
    }
    else
    {
        /* Wait until transfer is completed or for timeout */
        while ((CY_USB_DEV_EP_PENDING == epState) && (timeout > 0))
        {
            timeout = context->handleTimeout(timeout);

            /* Update endpoint state */
            epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);
        }

        /* Timeout expired */
        if (0 == timeout)
        {
            /* Abort write operation */
            (void) Cy_USB_Dev_AbortEpTransfer(endpoint, context);
            retStatus = CY_USB_DEV_TIMEOUT;
        }
    }

    /* Clear actual number of read bytes */
    *actSize = 0U;

    /* Read data from endpoint buffer after completion */
    if (CY_USB_DEV_EP_COMPLETED == epState)
    {
        retStatus = (cy_en_usb_dev_status_t)
                        Cy_USBFS_Dev_Drv_ReadOutEndpoint(context->drvBase,
                            endpoint, buffer, size, actSize, context->drvContext);

        if (CY_USB_DEV_SUCCESS != retStatus)
        {
            retStatus = CY_USB_DEV_DRV_HW_ERROR;
        }
    }

    if ((CY_USB_DEV_TIMEOUT != retStatus) && (CY_USB_DEV_DRV_HW_ERROR != retStatus))
    {
        /* Use endpoint state to get status */
        retStatus = ConvertEndpointStateToStatus(epState);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_ReadEpNonBlocking
****************************************************************************//**
*
* Read data received from USB Host from a certain endpoint. Before calling
* this function, \ref Cy_USB_Dev_StartReadEp must be called.
*
* \param endpoint
* The OUT data endpoint number.
*
* \param buffer
* The pointer to buffer that stores data that was read. \n
* Allocate buffer using \ref CY_USB_DEV_ALLOC_ENDPOINT_BUFFER macro to make
* it USBFS driver configuration independent (See \ref group_usb_dev_ep_buf_alloc
* for more information).
*
* \param size
* The number of bytes to read.
* This value must be less than or equal to endpoint maximum packet size.
*
* \param actSize
* The number of bytes that were actually read.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_ReadEpNonBlocking(uint32_t endpoint, uint8_t *buffer,
                                                    uint32_t size, uint32_t *actSize, cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t   retStatus;
    cy_en_usb_dev_ep_state_t epState;

    epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);

    /* Read data from endpoint buffer after completion */
    if (CY_USB_DEV_EP_COMPLETED == epState)
    {
        retStatus = (cy_en_usb_dev_status_t)
                        Cy_USBFS_Dev_Drv_ReadOutEndpoint(context->drvBase,
                            endpoint, buffer, size, actSize, context->drvContext);

        if (CY_USB_DEV_SUCCESS != retStatus)
        {
            retStatus = CY_USB_DEV_DRV_HW_ERROR;
        }
    }
    else
    {
        /* Clear actual number of read bytes */
        *actSize = 0U;

        /* Use endpoint state to get status */
        retStatus = ConvertEndpointStateToStatus(epState);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_WriteEpBlocking
****************************************************************************//**
*
* Write data to be transferred to USB Host from a certain endpoint.
* This function is blocking and returns after successful USB Host transfer,
* or an error or timeout occurred.
*
* \param endpoint
* The IN data endpoint number.
*
* \param buffer
* The pointer to the buffer containing data bytes to write. \n
* Allocate buffer using \ref CY_USB_DEV_ALLOC_ENDPOINT_BUFFER macro to make
* it USBFS driver configuration independent (See \ref group_usb_dev_ep_buf_alloc
* for more information).
*
* \param size
* The number of bytes to write.
* This value must be less than or equal to endpoint maximum packet size.
*
* \param timeout
* Defines in milliseconds the time for which this function can block.
* If that time expires, the function returns.
* To wait forever, pass \ref CY_USB_DEV_WAIT_FOREVER.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_WriteEpBlocking(uint32_t endpoint, uint8_t const *buffer,
                                                  uint32_t size, int32_t timeout, cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t   retStatus = CY_USB_DEV_BAD_PARAM;
    cy_en_usb_dev_ep_state_t epState;

    epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);

    /* Check that endpoint is ready for write operation */
    if ((CY_USB_DEV_EP_IDLE == epState) || (CY_USB_DEV_EP_COMPLETED == epState))
    {
        retStatus = (cy_en_usb_dev_status_t) Cy_USBFS_Dev_Drv_LoadInEndpoint(context->drvBase,
                                                endpoint, buffer, size, context->drvContext);

        /* Check endpoint load status */
        if (CY_USB_DEV_SUCCESS == retStatus)
        {
            /* Update endpoint state after load operation */
            epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);

            if (CY_USB_DEV_WAIT_FOREVER == timeout)
            {
                /* Wait until transfer is completed */
                while (CY_USB_DEV_EP_PENDING == epState)
                {
                    (void) context->handleTimeout(timeout);

                    /* Update endpoint state */
                    epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);
                }
            }
            else
            {
                /* Wait until transfer is completed or for timeout */
                while ((CY_USB_DEV_EP_PENDING == epState) && (timeout > 0))
                {
                    timeout = context->handleTimeout(timeout);

                    /* Update endpoint state */
                    epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);
                }

                /* Timeout expired */
                if (0 == timeout)
                {
                    /* Abort write operation */
                    (void) Cy_USB_Dev_AbortEpTransfer(endpoint, context);
                    retStatus = CY_USB_DEV_TIMEOUT;
                }
            }
        }
        else
        {
            retStatus = CY_USB_DEV_DRV_HW_ERROR;
        }
    }

    if ((CY_USB_DEV_TIMEOUT != retStatus) && (CY_USB_DEV_DRV_HW_ERROR != retStatus))
    {
        /* Use endpoint state to get status */
        retStatus = ConvertEndpointStateToStatus(epState);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_WriteEpNonBlocking
****************************************************************************//**
*
* Write data to be transferred to USB Host from a certain endpoint.
*
* \param endpoint
* The IN data endpoint number.
*
* \param buffer
* The pointer to the buffer containing data bytes to write. \n
* Allocate buffer using \ref CY_USB_DEV_ALLOC_ENDPOINT_BUFFER macro to make
* it USBFS driver configuration independent (See \ref group_usb_dev_ep_buf_alloc
* for more information).
*
* \param size
* The number of bytes to write.
* This value must be less than or equal to endpoint maximum packet size.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_WriteEpNonBlocking(uint32_t endpoint, uint8_t const *buffer,
                                                     uint32_t size, cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t   retStatus;
    cy_en_usb_dev_ep_state_t epState;

    epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);

    /* Check that endpoint is ready for operation */
    if ((CY_USB_DEV_EP_IDLE == epState) || (CY_USB_DEV_EP_COMPLETED == epState))
    {
        retStatus = (cy_en_usb_dev_status_t)
                        Cy_USBFS_Dev_Drv_LoadInEndpoint(context->drvBase,
                            endpoint, buffer, size, context->drvContext);

        /* Write data into the endpoint buffer */
        if (CY_USB_DEV_SUCCESS != retStatus)

        {
             retStatus = CY_USB_DEV_DRV_HW_ERROR;
        }
    }
    else
    {
        retStatus = ConvertEndpointStateToStatus(epState);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: BusResetCallback
****************************************************************************//**
*
* Handles Bus Reset interrupt.
*
* \param base
* The pointer to the USBFS instance.
*
* \param drvContext
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
static void BusResetCallback(USBFS_Type *base, struct cy_stc_usbfs_dev_drv_context *drvContext)
{
    /* Get device context from the driver context */
    cy_stc_usb_dev_context_t *context = (cy_stc_usb_dev_context_t *) Cy_USBFS_Dev_Drv_GetDevContext(base, drvContext);

    /* Get linked list of classes */
    cy_stc_usb_dev_class_ll_item_t *curItem = context->classRoot;

    /* Set device in the DEFAULT state */
    context->state   = CY_USB_DEV_DEFAULT;
    context->status  = 0U; /* Reset remote wakeup and power state */
    context->configuration = 0U;

    /* Notify Bus Reset event for device instance */
    if (NULL != context->eventsCallback)
    {
        /* Input parameters are zeros. Ignore return for Bus Reset event. */
        (void) context->eventsCallback(CY_USB_DEV_EVENT_BUS_RESET, 0UL, 0UL, context);
    }

    /* Notify Bus Reset event for all class instances */
    while (NULL != curItem)
    {
        if (NULL != curItem->classObj->busReset)
        {
            /* Execute callback */
            curItem->classObj->busReset(curItem->classData, context);
        }

        /* Move to next element */
        curItem = curItem->next;
    }
}


/*******************************************************************************
* Function Name: DecodeSetupPacket
****************************************************************************//**
*
* Decodes setup packet (populates \ref cy_stc_usb_dev_setup_packet_t).
*
* \param data
* The pointer to buffer with setup packet (raw data).
*
* \param packet
* The pointer to structure that holds setup packet.
*
*******************************************************************************/
static void DecodeSetupPacket(uint8_t const *data, cy_stc_usb_dev_setup_packet_t *packet)
{
    /* Fill elements of setup packet structure from raw data */
    packet->bmRequestType.direction = (uint8_t) _FLD2VAL(SETUP_RQST_DIR,  data[SETUP_RQST_POS]);
    packet->bmRequestType.type      = (uint8_t) _FLD2VAL(SETUP_RQST_TYPE, data[SETUP_RQST_POS]);
    packet->bmRequestType.recipient = (uint8_t) _FLD2VAL(SETUP_RQST_RCPT, data[SETUP_RQST_POS]);
    packet->bRequest                = (uint8_t) data[SETUP_RQST_TYPE_POS];
    packet->wValue   = GET_UINT16(data[SETUP_VALUE_LSB_POS],  data[SETUP_VALUE_MSB_POS]);
    packet->wIndex   = GET_UINT16(data[SETUP_INDEX_LSB_POS],  data[SETUP_INDEX_MSB_POS]);
    packet->wLength  = GET_UINT16(data[SETUP_LENGTH_LSB_POS], data[SETUP_LENGTH_MSB_POS]);
}


/*******************************************************************************
* Function Name: HandleSetup
****************************************************************************//**
*
* Handles setup packet received event (generated from Endpoint 0 Interrupt).
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleSetup(cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    cy_stc_usb_dev_control_transfer_t *transfer = &context->ControlTransfer;

    /* Get setup packet from hardware */
    Cy_USBFS_Dev_Drv_Ep0GetSetup(context->drvBase, transfer->buffer, context->drvContext);

    /* Decode setup packet */
    DecodeSetupPacket(transfer->buffer, &transfer->setup);

    /* Prepare for new transfer */
    transfer->ptr       = NULL;
    transfer->remaining = 0U;
    transfer->size      = 0U;
    transfer->direction = transfer->setup.bmRequestType.direction;
    transfer->zlp       = false;
    transfer->notify    = false;

    /* Handle Setup request depends on type */
    switch (transfer->setup.bmRequestType.type)
    {
        case CY_USB_DEV_STANDARD_TYPE:
        case CY_USB_DEV_CLASS_TYPE:
        {
            if (CY_USB_DEV_STANDARD_TYPE == transfer->setup.bmRequestType.type)
            {
                /* Handle Standard requests */
                retStatus = HandleStandardRequests(transfer, context);
            }

            /* Try handle by Class requests handler */
            if (CY_USB_DEV_SUCCESS != retStatus)
            {
                retStatus = HandleClassRequests(context->classRoot, transfer, context);
            }
        }
        break;

        case CY_USB_DEV_VENDOR_TYPE:
            retStatus = HandleVendorRequests(transfer, context);
        break;

        default:
            /* Unknown request type: CY_USB_DEV_REQUEST_NOT_HANDLED */
        break;
    }

    /* Process standard requests */

    /* Continue processing if request was handled */
    if (CY_USB_DEV_SUCCESS == retStatus)
    {
        retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

        /* Check transfer setup before continue transfer */
        if (transfer->setup.bmRequestType.direction == transfer->direction)
        {
            /* Check transfer length */
            if (transfer->setup.wLength > 0U)
            {
                if (CY_USB_DEV_DIR_DEVICE_TO_HOST == transfer->direction)
                {
                    /* IN data stage is required */

                    /* Transfer must be less than or equal to the size requested by the host */
                    if (transfer->remaining > transfer->setup.wLength)
                    {
                        transfer->remaining = transfer->setup.wLength;
                    }

                    retStatus = CY_USB_DEV_SUCCESS;
                }
                else
                {
                    /* OUT data stage is required */

                    /* Transfer must be equal to the size requested by the Host and
                    * buffer for data must be large enough
                    */
                    if ((transfer->remaining == transfer->setup.wLength) &&
                        (transfer->remaining <= transfer->bufferSize))
                    {
                        retStatus = CY_USB_DEV_SUCCESS;
                    }
                }
            }
            else
            {
                /* No data stage: transfer size must be zero */
                if (0U == transfer->remaining)
                {
                    retStatus = CY_USB_DEV_SUCCESS;
                }
            }
        }

        /* Execute transfer if transfer setup correctly */
        if (CY_USB_DEV_SUCCESS == retStatus)
        {
            if (transfer->setup.wLength > 0U)
            {
                /* Data or retStatus stage if applicable */
                if (CY_USB_DEV_DIR_DEVICE_TO_HOST == transfer->direction)
                {
                    /* Define whether send zero length packet at the end of transfer */
                    if (transfer->setup.wLength > transfer->remaining)
                    {
                        /* Transfer is a multiple of EP0 max packet size */
                        transfer->zlp = (0U == (transfer->remaining % Cy_USBFS_Dev_Drv_GetEp0MaxPacket(context->drvBase)));
                    }

                    /* Handle data stage (IN direction) */
                    (void) HandleIn(context);
                }
                else
                {
                    /* Set buffer to accept Host data */
                    transfer->ptr = transfer->buffer;

                    /* Start data stage (OUT direction) */
                    (void) Cy_USBFS_Dev_Drv_Ep0Read(context->drvBase, transfer->ptr, (uint32_t) transfer->remaining, context->drvContext);
                }
            }
            else
            {
                /* No data state: move to status stage (IN direction) */
                (void) Cy_USBFS_Dev_Drv_Ep0Write(context->drvBase, NULL, 0U, context->drvContext);
            }
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: HandleIn
****************************************************************************//**
*
* Handles IN packet received event (generated from Endpoint 0 Interrupt).
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleIn(cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    cy_stc_usb_dev_control_transfer_t *transfer = &context->ControlTransfer;

    if (CY_USB_DEV_DIR_DEVICE_TO_HOST == transfer->direction)
    {
        /* Data stage (direction IN) */

        /* Send data packet or zero length packet. Skip processing after zero length is sent */
        if (false == ((0U == transfer->remaining) && (!transfer->zlp)))
        {
            if ((transfer->remaining == 0U) && (transfer->zlp))
            {
                /* Zero length packet is send by code below */
                transfer->zlp = false;
            }

            /* Write to endpoint 0 */
            uint16_t packetSize = (uint16_t) Cy_USBFS_Dev_Drv_Ep0Write(context->drvBase,
                                                                       transfer->ptr,
                                                                       (uint32_t) transfer->remaining,
                                                                       context->drvContext);

            /* Update transfer */
            transfer->ptr       += packetSize;
            transfer->remaining -= packetSize;

            /* After last packet has been written move to move to status stage.
            * Do not wait for the next IN event because it can be dropped if
            * ACK from host is corrupted.
            * For more info on this see section 8.5.3.3 of the USB2.0 specification.
            * */
            if ((0U == transfer->remaining) && (transfer->zlp == false))
            {
                /* Data stage completed: move to status stage (direction OUT) */
                (void) Cy_USBFS_Dev_Drv_Ep0Read(context->drvBase, NULL, 0UL, context->drvContext);
            }
        }

        retStatus = CY_USB_DEV_SUCCESS;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: HandleOut
****************************************************************************//**
*
* Handles OUT packet received event (generated from Endpoint 0 Interrupt).
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleOut(cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    cy_stc_usb_dev_control_transfer_t *transfer = &context->ControlTransfer;

    if (CY_USB_DEV_DIR_HOST_TO_DEVICE == transfer->direction)
    {
        /* Control transfer: DATA stage (direction OUT) */

        /* Read from endpoint 0 */
        uint16_t packetSize = (uint16_t) Cy_USBFS_Dev_Drv_Ep0ReadResult(context->drvBase, context->drvContext);

        /* Check whether transfer size is valid */
        if (packetSize <= transfer->remaining)
        {
            /* Update transfer counters */
            transfer->ptr       += packetSize;
            transfer->size      += packetSize;
            transfer->remaining -= packetSize;

            /* Check whether all bytes received */
            if (transfer->remaining > 0U)
            {
                /* Continue: there are more bytes to receive */
                Cy_USBFS_Dev_Drv_Ep0Read(context->drvBase,
                                         transfer->ptr,
                                         (uint32_t) transfer->remaining,
                                         context->drvContext);

                retStatus = CY_USB_DEV_SUCCESS;
            }
            else
            {
                /* Notify class layer DATA stage completed */
                if (transfer->notify)
                {
                    /* Clear notify and reset buffer pointer */
                    transfer->notify = false;
                    transfer->ptr    = transfer->buffer;

                    /* Handle Setup request depends on type */
                    switch(transfer->setup.bmRequestType.type)
                    {
                        case CY_USB_DEV_STANDARD_TYPE:
                            /* Return CY_USB_DEV_REQUEST_NOT_HANDLED because
                            * Standard request handler does not use notification.
                            */
                        break;

                        case CY_USB_DEV_CLASS_TYPE:
                            retStatus = HandleClassRequestsCompleted(context->classRoot, transfer, context);
                        break;

                        case CY_USB_DEV_VENDOR_TYPE:
                            retStatus = HandleVendorRequestsCompleted(transfer, context);
                        break;

                        default:
                            /* Unknown request type: return CY_USB_DEV_REQUEST_NOT_HANDLED */
                        break;
                    }
                }

                if (CY_USB_DEV_SUCCESS == retStatus)
                {
                    /* Move to STATUS stage (direction IN) */
                    (void) Cy_USBFS_Dev_Drv_Ep0Write(context->drvBase, NULL, 0U, context->drvContext);
                }
            }
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Ep0SetupCallback
****************************************************************************//**
*
* Implements callback for setup received event (generated from Endpoint 0
* Interrupt). The Endpoint 0 is STALLED if processing was successful.
*
* \param base
* The pointer to the USBFS instance.
*
* \param drvContext
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
static void Ep0SetupCallback(USBFS_Type *base, struct cy_stc_usbfs_dev_drv_context *drvContext)
{
    /* Get device context from the driver context */
    cy_stc_usb_dev_context_t *context = (cy_stc_usb_dev_context_t *) Cy_USBFS_Dev_Drv_GetDevContext(base, drvContext);

    /* Endpoint 0 setup event */
    if (CY_USB_DEV_SUCCESS != HandleSetup(context))
    {
        /* Protocol stall */
        Cy_USBFS_Dev_Drv_Ep0Stall(base);
    }
}


/*******************************************************************************
* Function Name: Ep0InCallback
****************************************************************************//**
*
* Implements callback for IN packet received event (generated from Endpoint 0
* Interrupt). The Endpoint 0 is STALLED if processing was successful.
*
* \param base
* The pointer to the USBFS instance.
*
* \param drvContext
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
static void Ep0InCallback(USBFS_Type *base, struct cy_stc_usbfs_dev_drv_context *drvContext)
{
    /* Get device context from the driver context */
    cy_stc_usb_dev_context_t *context = (cy_stc_usb_dev_context_t *) Cy_USBFS_Dev_Drv_GetDevContext(base, drvContext);

    /* Endpoint 0 IN packet received event */
    if (CY_USB_DEV_SUCCESS != HandleIn(context))
    {
        /* Protocol stall */
        Cy_USBFS_Dev_Drv_Ep0Stall(base);
    }
}


/*******************************************************************************
* Function Name: Ep0OutCallback
****************************************************************************//**
*
* Implements callback for OUT packet received event (generated from Endpoint 0
* Interrupt). The Endpoint 0 is STALLED if processing was successful.
*
* \param base
* The pointer to the USBFS instance.
*
* \param drvContext
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
static void Ep0OutCallback(USBFS_Type *base, struct cy_stc_usbfs_dev_drv_context *drvContext)
{
    /* Get device context from the driver context */
    cy_stc_usb_dev_context_t *context = (cy_stc_usb_dev_context_t *) Cy_USBFS_Dev_Drv_GetDevContext(base, drvContext);

    /* Endpoint 0 OUT packet received */
    if (CY_USB_DEV_SUCCESS != HandleOut(context))
    {
        /* Protocol stall */
        Cy_USBFS_Dev_Drv_Ep0Stall(base);
    }
}

#if defined(CY_IP_MXUSBFS)
/*******************************************************************************
* Function Name: InitSerialNumberString
****************************************************************************//**
*
* Initializes serial number string using silicon ID.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
static void InitSerialNumberString(cy_stc_usb_dev_context_t *context)
{
    const uint8_t hex[] = "0123456789ABCDEF";
    uint8_t *strDescr = context->serialNumDescr;
    uint8_t *id;
    uint32_t i = 0U;
    uint32_t j = 0U;
    uint64_t tmp;

    /* Place header: length and type */
    strDescr[STRING_DESCR_LENGTH_POS] = CY_USB_DEV_SN_STRING_DESR_LENGTH;
    strDescr[STRING_DESCR_TYPE_POS]   = CY_USB_DEV_STRING_DESCR;

    /* Get unique ID - 8 bytes */
    tmp = Cy_SysLib_GetUniqueId();

    /* Get start address of uint64_t */
    id = (uint8_t *) &tmp;

    /* Fill descriptor using unique silicon ID */
    for (i = 2U; i < CY_USB_DEV_SN_STRING_DESR_LENGTH; i += 4U)
    {
        strDescr[i + 0U] = hex[(id[j] & 0x0FU)];
        strDescr[i + 1U] = 0U;
        strDescr[i + 2U] = hex[(id[j] >> 4U)];
        strDescr[i + 3U] = 0U;
        ++j;
    }
}
#endif /* defined(CY_IP_MXUSBFS)  */

/*******************************************************************************
* Function Name: GetDescriptorRequest
****************************************************************************//**
*
* Handles GET_DESCRIPTOR standard request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetDescriptorRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                   cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    switch (CY_USB_DEV_GET_DESCR_TYPE(transfer->setup.wValue))
    {
        case CY_USB_DEV_DEVICE_DESCR:
        {
            /* Return device descriptor */
            transfer->ptr       = (uint8_t *) context->devDescriptors->deviceDescriptor;
            transfer->remaining = CY_USB_DEV_DEVICE_DESCR_LENGTH;

            retStatus = CY_USB_DEV_SUCCESS;
        }
        break;

        case CY_USB_DEV_CONFIG_DESCR:
        {
            /* Get configuration index */
            uint32_t idx = CY_USB_DEV_GET_DESCR_IDX(transfer->setup.wValue);

            /* Check whether requested configuration descriptor exists */
            if (idx < context->devDescriptors->numConfigurations)
            {
                uint8_t *configDescr = (uint8_t *) context->devDescriptors->configurations[idx]->configDescriptor;

                /* Return configuration descriptor */
                transfer->ptr = configDescr;
                transfer->remaining = GET_UINT16(configDescr[CONFIG_DESCR_LENGTH_LSB_POS],
                                                 configDescr[CONFIG_DESCR_LENGTH_MSB_POS]);

                retStatus = CY_USB_DEV_SUCCESS;
            }
        }
        break;

        case CY_USB_DEV_BOS_DESCR:
        {
            uint8_t *bosDescr = (uint8_t *) context->devDescriptors->bosDescriptor;

            /* Check if BOS descriptor exists */
            if (NULL != bosDescr)
            {
                /* Return BOS descriptor */
                transfer->ptr       = bosDescr;
                transfer->remaining = GET_UINT16(bosDescr[BOS_DESCR_LENGTH_LSB_POS],
                                                 bosDescr[BOS_DESCR_LENGTH_MSB_POS]);

                retStatus = CY_USB_DEV_SUCCESS;
            }
        }
        break;

        case CY_USB_DEV_STRING_DESCR:
        {
            uint8_t *strDescr = NULL;

            /* Get string index */
            uint32_t idx = CY_USB_DEV_GET_DESCR_IDX(transfer->setup.wValue);

            /* Get pool of strings */
            cy_stc_usb_dev_string_t const *descr = context->devDescriptors->strings;

            /* Special case: Microsoft OS Descriptors String descriptor */
            if (idx == STRING_IMSOS_INDEX)
            {
                if (NULL != descr->osStringDescriptors)
                {
                    /* Get string */
                    strDescr = (uint8_t *) descr->osStringDescriptors->msOsDescriptor;

                    retStatus = CY_USB_DEV_SUCCESS;
                }
            }
            /* Other string descriptors (included serial number string) */
            else
            {
                /* Check that string exists */
                if ((NULL != descr->stringDescriptors) && (descr->numStrings > 0U) && (idx < descr->numStrings))
                {
                    /* Get string from descriptors */
                    strDescr = (uint8_t *) descr->stringDescriptors[idx];

                    /* Check whether requested string is serial number */
                    if ((idx != STRING_LANGID_INDEX) &&
                        (idx == context->devDescriptors->deviceDescriptor[DEVICE_DESCR_ISN_STRING_POS]))
                    {
                        /* Check options for serial string */
                        if (strDescr != NULL)
                        {
                            /* Serial number is part of device descriptor */
                            retStatus = CY_USB_DEV_SUCCESS;
                        }
                        else
                        {
                            if (context->getSerialNumString != NULL)
                            {
                                /* Get serial number using callback */
                                strDescr = context->getSerialNumString();
                                if (strDescr != NULL)
                                {
                                    retStatus = CY_USB_DEV_SUCCESS;
                                }
                            }
                            else
                            {
                                /* Get serial number using silicon ID */
                                strDescr = &context->serialNumDescr[0];
                                retStatus = CY_USB_DEV_SUCCESS;
                            }
                        }
                    }
                    else
                    {
                        retStatus = CY_USB_DEV_SUCCESS;
                    }
                }
            }

            /* Return string if it was found */
            if (CY_USB_DEV_SUCCESS == retStatus)
            {
                /* User defined descriptor */
                transfer->ptr       = strDescr;
                transfer->remaining = strDescr[STRING_DESCR_LENGTH_POS];
            }
        }
        break;

        case CY_USB_DEV_INTERFACE_DESCR:
        case CY_USB_DEV_ENDPOINT_DESCR:
            /* These descriptor types are not supported */
        break;

        default:
            /* The descriptor type was not recognized */
        break;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: GetConfigurationRequest
****************************************************************************//**
*
* Handles SET_CONFIGURATION standard request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetConfigurationRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                      cy_stc_usb_dev_context_t *context)
{
    /* Send the device configuration */
    transfer->ptr       = (uint8_t *) &context->configuration;
    transfer->remaining = (uint16_t)sizeof(context->configuration);

    return CY_USB_DEV_SUCCESS;
}


/*******************************************************************************
* Function Name: GetInterfaceRequest
****************************************************************************//**
*
* Handles GET_INTERFACE standard request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetInterfaceRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                  cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    uint32_t interface = transfer->setup.wIndex;

    if (CY_USB_DEV_CONFIGURED != context->state)
    {
        return CY_USB_DEV_REQUEST_NOT_HANDLED;
    }

    /* Check whether interface exists in current configuration */
    if (interface < context->devDescriptors->configurations[VAL2IDX(context->configuration)]->numInterfaces)
    {
        /* Return current alternate setting for an interface */
        transfer->ptr       = (uint8_t *) &context->alternate[interface];
        transfer->remaining = (uint16_t)sizeof(context->alternate[interface]);

        retStatus = CY_USB_DEV_SUCCESS;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: GetStatusRequest
****************************************************************************//**
*
* Handles GET_STATUS standard request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetStatusRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                               cy_stc_usb_dev_context_t const *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    uint16_t response;

    /* Endpoint or interface must be zero if device is not configured */
    if (context->state != CY_USB_DEV_CONFIGURED)
    {
        if (0U != transfer->setup.wIndex)
        {
            return CY_USB_DEV_REQUEST_NOT_HANDLED;
        }
    }

    /* Find request recipient */
    switch (transfer->setup.bmRequestType.recipient)
    {
        case CY_USB_DEV_RECIPIENT_DEVICE:
        {
            /* Return device status: powered or remote wakeup */
            response = (uint16_t) context->status;
            retStatus   = CY_USB_DEV_SUCCESS;
        }
        break;

        case CY_USB_DEV_RECIPIENT_INTERFACE:
        {
            /* All status bits are Reserved (Reset to zero) */
            response = 0U;
            retStatus   = CY_USB_DEV_SUCCESS;
        }
        break;

        case CY_USB_DEV_RECIPIENT_ENDPOINT:
        {
            uint32_t endpoint = CY_USB_DEV_EPADDR2EP(transfer->setup.wIndex);

            cy_en_usb_dev_ep_state_t epState = Cy_USBFS_Dev_Drv_GetEndpointState(context->drvBase, endpoint, context->drvContext);

            /* Check that valid endpoint is requested */
            if ((CY_USB_DEV_EP_INVALID != epState) && (CY_USB_DEV_EP_DISABLED != epState))
            {
                /* Get endpoint state */
                response  = (CY_USB_DEV_EP_STALLED == epState) ? CY_USB_DEV_ENDPOINT_STATUS_HALT : 0U;
                retStatus = CY_USB_DEV_SUCCESS;
            }
        }
        break;

        default:
        {
            /* Do nothing. */
            break;
        }
    }

    /* Put response into the buffer */
    if (CY_USB_DEV_SUCCESS == retStatus)
    {
        /* Send the status to host */
        transfer->buffer[0U] = CY_LO8(response);
        transfer->buffer[1U] = CY_HI8(response);

        transfer->ptr       = transfer->buffer;
        transfer->remaining = (uint16_t)sizeof(response);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: ClearFeatureRequest
****************************************************************************//**
*
* Handles CLEAR_FEATURE standard request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t ClearFeatureRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                  cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    /* Endpoint or interface must be zero if device is not configured */
    if (context->state != CY_USB_DEV_CONFIGURED)
    {
        if (transfer->setup.wIndex != 0U)
        {
            return CY_USB_DEV_REQUEST_NOT_HANDLED;
        }
    }

    /* Find request recipient */
    switch (transfer->setup.bmRequestType.recipient)
    {
        case CY_USB_DEV_RECIPIENT_DEVICE:
        {
            /* Check feature selector: TEST_MODE is not supported */
            if (transfer->setup.wValue == CY_USB_DEV_DEVICE_REMOTE_WAKEUP)
            {
                context->status &= (uint8_t) ~CY_USB_DEV_STATUS_REMOTE_WAKEUP_MASK;

                retStatus = CY_USB_DEV_SUCCESS;
            }
        }
        break;

        case CY_USB_DEV_RECIPIENT_INTERFACE:
            /* There is no feature selector this recipient */
        break;

        case CY_USB_DEV_RECIPIENT_ENDPOINT:
        {
            /* Check that feature selector is ENDPOINT_HALT */
            if (transfer->setup.wValue == CY_USB_DEV_ENDPOINT_HALT)
            {
                uint32_t endpoint = CY_USB_DEV_EPADDR2EP(transfer->setup.wIndex);

                /* Only enabled and data endpoints can be STALLED */
                retStatus = (cy_en_usb_dev_status_t)
                            Cy_USBFS_Dev_Drv_UnStallEndpoint(context->drvBase,
                                endpoint, context->drvContext);

                if (CY_USB_DEV_SUCCESS != retStatus)
                {
                    retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;
                }
            }
        }
        break;

        default:
            /* Unknown recipient */
        break;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: SetAddressRequest
****************************************************************************//**
*
* Handles SET_ADDRESS standard request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t SetAddressRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                cy_stc_usb_dev_context_t *context)
{
    uint8_t devAddress = CY_LO8(transfer->setup.wValue);

    /* Request to change address after status status */
    Cy_USBFS_Dev_Drv_SetAddress(context->drvBase, devAddress, context->drvContext);

    /* Set device state depends on address value */
    context->state = (0U != devAddress) ? CY_USB_DEV_ADDRESSED : CY_USB_DEV_DEFAULT;

    return CY_USB_DEV_SUCCESS;
}


/*******************************************************************************
* Function Name: ConfigureDataEndpoints
****************************************************************************//**
*
* Configures data endpoints that belong to a certain configuration.
*
* \param config
* Configuration index (configuration value - 1).
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of executed operation \ref cy_en_usb_dev_status_t.
* CY_USB_DEV_SUCCESS is returned if no data endpoints are to be configured.
*
*******************************************************************************/
static cy_en_usb_dev_status_t ConfigureDataEndpoints(uint32_t config, cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_SUCCESS;

    uint32_t intf, alt, ep;

    uint32_t numIntr = context->devDescriptors->configurations[config]->numInterfaces;
    cy_stc_usb_dev_interface_t const **descr = context->devDescriptors->configurations[config]->interfaces;

    /* Go through all interfaces that belong to configuration */
    for (intf = 0U; intf < numIntr; ++intf)
    {
        uint32_t mask = context->devDescriptors->configurations[config]->interfaces[intf]->endpointsMask;
        uint32_t endpoint = 1UL;

        /* Use mask to find only endpoints that belong to interface */
        while (0U != mask)
        {
            /* Configure enabled endpoint */
            if (0U != (mask & 0x01U))
            {
                bool configured = false;

                cy_stc_usb_dev_ep_config_t epConfig = {0};

                epConfig.enableEndpoint = false;
                epConfig.allocBuffer    = true;

                /* Go through all alternate */
                for (alt = 0U; alt < descr[intf]->numAlternates; ++alt)
                {
                    /* Go thorough all endpoints that belong to alternate */
                    for (ep = 0U; ep < descr[intf]->alternates[alt]->numEndpoints; ++ep)
                    {
                        cy_stc_usbdev_endpoint_descr_t const *epDescr = (cy_stc_usbdev_endpoint_descr_t const *) ((const void *)(descr[intf]->alternates[alt]->endpoints[ep]->endpointDescriptor));

                        /* Find endpoint that needs to be configured */
                        if (CY_USB_DEV_EPADDR2EP(epDescr->bEndpointAddress) == endpoint)
                        {
                            if (false == configured)
                            {
                                /* Enable endpoint that belongs to alternate 0 */
                                if (0U == alt)
                                {
                                    epConfig.enableEndpoint = true;
                                }

                                /* Initialize endpoint configuration structure */
                                epConfig.endpointAddr   = epDescr->bEndpointAddress;
                                epConfig.attributes     = epDescr->bmAttributes;
                                epConfig.maxPacketSize  = GET_CFG_WORD(&epDescr->wMaxPacketSize);
                                epConfig.bufferSize     = GET_CFG_WORD(&epDescr->wMaxPacketSize);

                                /* Set configuration of the 1st endpoint instance */
                                configured = true;
                            }
                            else
                            {
                                /* Find maximum packet size for this endpoint in all alternates */
                                if (epConfig.bufferSize < GET_CFG_WORD(&epDescr->wMaxPacketSize))
                                {
                                    epConfig.bufferSize = GET_CFG_WORD(&epDescr->wMaxPacketSize);
                                }
                            }

                            break;
                        }
                    }
                }

                /* Add endpoint */
                retStatus = (cy_en_usb_dev_status_t)
                            Cy_USBFS_Dev_Drv_AddEndpoint(context->drvBase,
                                &epConfig, context->drvContext);

                /* Check operation result */
                if (CY_USB_DEV_SUCCESS != retStatus)
                {
                    retStatus = CY_USB_DEV_DRV_HW_ERROR;
                    break;
                }
            }

            mask >>= 1U;
            ++endpoint;
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: SetConfigurationRequest
****************************************************************************//**
*
* Handles SET_CONFIGURATION standard request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t SetConfigurationRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                      cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    uint32_t config = (uint32_t) transfer->setup.wValue;

    if (0U == config)
    {
        /* Disable all data endpoints */
        Cy_USBFS_Dev_Drv_UnConfigureDevice(context->drvBase, context->drvContext);

        /* Store configuration and move to configured state */
        context->configChanged = true;
        context->configuration = (uint8_t) config;
        context->state  = CY_USB_DEV_ADDRESSED;

        retStatus = CY_USB_DEV_SUCCESS;
    }
    else
    {
        /* Check whether configuration is valid */
        if (config <= context->devDescriptors->numConfigurations)
        {
            uint32_t configIdx = VAL2IDX(config);

            /* Clear context fields that keep configuration related data */
            (void) memset((void *) context->alternate, 0, CY_USB_DEV_NUM_INTERFACES_MAX);

            /* Set device endpoints into the default state before configure them */
            Cy_USBFS_Dev_Drv_UnConfigureDevice(context->drvBase, context->drvContext);

            /* Configure endpoints */
            retStatus = ConfigureDataEndpoints(configIdx, context);

            if (CY_USB_DEV_SUCCESS == retStatus)
            {
                /* Notify Bus Reset event for device instance */
                if (NULL != context->eventsCallback)
                {
                    /* Input parameters are zeros. Ignore return for Bus Reset event. */
                    retStatus = context->eventsCallback(CY_USB_DEV_EVENT_SET_CONFIG, config, 0UL, context);
                }

                if (CY_USB_DEV_SUCCESS == retStatus)
                {
                    /* Get linked list of classes */
                    cy_stc_usb_dev_class_ll_item_t *curItem = context->classRoot;

                    /* Call Set Configuration callback for all class instances */
                    while (NULL != curItem)
                    {
                        if (NULL != curItem->classObj->setConfiguration)
                        {
                            /* Execute callback */
                            retStatus = curItem->classObj->setConfiguration(config, curItem->classData, context);

                            if (CY_USB_DEV_SUCCESS != retStatus)
                            {
                                /* Operation failed break the loop */
                                break;
                            }
                        }

                        /* Move to next element */
                        curItem = curItem->next;
                    }
                }
            }

            if (CY_USB_DEV_SUCCESS == retStatus)
            {
                const uint32_t attribute = context->devDescriptors->configurations[configIdx]->configDescriptor[CONFIG_DESCR_ATTRIB_POS];

                /* Complete device configuration (endpoints were configured) */
                Cy_USBFS_Dev_Drv_ConfigDevice(context->drvBase, context->drvContext);

                /* Set power status (remote wakeup status was cleared on bus reset) */
                if (0U != (attribute & CONFIG_ATTR_SELF_POWERED_MASK))
                {
                    context->status |= (uint8_t) CY_USB_DEV_STATUS_SELF_POWERED_MASK;
                }
                else
                {
                    context->status &= (uint8_t) ~CY_USB_DEV_STATUS_SELF_POWERED_MASK;
                }

                /* Store configuration and move to configured state */
                context->configChanged = true;
                context->configuration = (uint8_t) config;
                context->state  = CY_USB_DEV_CONFIGURED;
            }
            else
            {
                /* Set configuration failed, remain in current state */
                Cy_USBFS_Dev_Drv_UnConfigureDevice(context->drvBase, context->drvContext);

                retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;
            }
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: InterfaceRemoveDataEndpoints
****************************************************************************//**
*
* Disables data endpoints that belong to a certain interface.
*
* \param numEndpoints
* The number of data endpoints.
*
* \param epsPool
* The pointer to pointer to the array of the endpoints.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of executed operation \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
static cy_en_usb_dev_status_t InterfaceRemoveDataEndpoints(uint32_t numEndpoints,
                                             cy_stc_usb_dev_endpoint_t const * const *epsPool,
                                             cy_stc_usb_dev_context_t   *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;
    uint32_t endpoint;

    if (0U == numEndpoints)
    {
        /* Interface with zero endpoints return success */
        return CY_USB_DEV_SUCCESS;
    }

    /* Remove endpoints that are available in pool */
    for (endpoint = 0UL; endpoint < numEndpoints; ++endpoint)
    {
        /* Get endpoint parsed endpoint descriptor */
        cy_stc_usbdev_endpoint_descr_t const *epDescr = (cy_stc_usbdev_endpoint_descr_t const *)((const void *) (epsPool[endpoint]->endpointDescriptor));

        /* Remove endpoint */
        retStatus = (cy_en_usb_dev_status_t)
                    Cy_USBFS_Dev_Drv_RemoveEndpoint(context->drvBase, (uint32_t) epDescr->bEndpointAddress,
                                                    context->drvContext);

        if (CY_USB_DEV_SUCCESS != retStatus)
        {
            /* Remove operation failed */
            retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;
            break;
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: InterfaceAddDataEndpoints
****************************************************************************//**
*
* Configures data endpoints that belong to a certain interface to operate.
*
* \param numEndpoints
* The number of data endpoints.
*
* \param epsPool
* The pointer to pointer to the array of the endpoints.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
static cy_en_usb_dev_status_t InterfaceAddDataEndpoints(uint32_t numEndpoints,
                                          cy_stc_usb_dev_endpoint_t const *const *epsPool,
                                          cy_stc_usb_dev_context_t   *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;
    uint32_t endpoint;

    if (0U == numEndpoints)
    {
        /* Interface with zero endpoints return success */
        return CY_USB_DEV_SUCCESS;
    }

    /* Add endpoints that are available the pool */
    for (endpoint = 0UL; endpoint < numEndpoints; ++endpoint)
    {
        cy_stc_usbdev_endpoint_descr_t const *epDescr = (cy_stc_usbdev_endpoint_descr_t const *)((const void *) (epsPool[endpoint]->endpointDescriptor));
        cy_stc_usb_dev_ep_config_t epConfig;

        /* Setup configuration structure */
        epConfig.allocBuffer    = false;
        epConfig.enableEndpoint = true;
        epConfig.endpointAddr   = epDescr->bEndpointAddress;
        epConfig.attributes     = epDescr->bmAttributes;
        epConfig.maxPacketSize  = GET_CFG_WORD(&epDescr->wMaxPacketSize);

        /* Add endpoint */
        retStatus = (cy_en_usb_dev_status_t)
                    Cy_USBFS_Dev_Drv_AddEndpoint(context->drvBase, &epConfig,
                        context->drvContext);

        if (CY_USB_DEV_SUCCESS != retStatus)
        {
            /* Add operation failed */
            retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;
            break;
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: CallSetInterfaceCallbacks
****************************************************************************//**
*
* Calls Class callbacks for SET_INTERFACE standard request.
*
* \param interface
* The interface number.
*
* \param alternate
* The alternate setting for the interface.
*
* \param curItem
* The pointer to class linked list element.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t CallSetInterfaceCallbacks(uint32_t interface,
                                                        uint32_t alternate,
                                  cy_stc_usb_dev_class_ll_item_t *curItem,
                                        cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_SUCCESS;

    /* Call registered Set Interface callbacks for all class instances */
    while (NULL != curItem)
    {
        /* Execute callback */
        if (NULL != curItem->classObj->setInterface)
        {
            retStatus = curItem->classObj->setInterface(interface, alternate,
                                                        curItem->classData, context);

            if (CY_USB_DEV_SUCCESS != retStatus)
            {
                break;
            }
        }

        /* Move to next element */
        curItem = curItem->next;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: SetInterfaceRequest
****************************************************************************//**
*
* Handles SET_INTERFACE standard request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t SetInterfaceRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                  cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    uint32_t cfg  = (uint32_t) VAL2IDX(context->configuration);
    uint32_t intf = (uint32_t) transfer->setup.wIndex;
    uint32_t alt  = (uint32_t) transfer->setup.wValue;

    /* Not supported when configuration is set */
    if (CY_USB_DEV_CONFIGURED != context->state)
    {
        return CY_USB_DEV_REQUEST_NOT_HANDLED;
    }

    /* Check whether interface exists */
    if (intf < context->devDescriptors->configurations[cfg]->numInterfaces)
    {
        /* Check whether alternate for this interface exists */
        if (alt < context->devDescriptors->configurations[cfg]->interfaces[intf]->numAlternates)
        {
            /* Get pointer to interface descriptor structure */
            const cy_stc_usb_dev_interface_t *descr = context->devDescriptors->configurations[cfg]->interfaces[intf];

            /* If alternate settings are not changed, do nothing with current alternate */
            if (alt != context->alternate[intf])
            {
                /* Remove endpoints used by current alternate (old) */
                uint32_t altOld = context->alternate[intf];

                retStatus = InterfaceRemoveDataEndpoints((uint32_t) descr->alternates[altOld]->numEndpoints,
                        (cy_stc_usb_dev_endpoint_t const * const *) descr->alternates[altOld]->endpoints,
                                                          context);

                /* Add endpoints used by new alternate (received) */
                if (CY_USB_DEV_SUCCESS == retStatus)
                {
                    /* Add endpoints used by new alternate (received) */
                    retStatus = InterfaceAddDataEndpoints((uint32_t) descr->alternates[alt]->numEndpoints,
                         (cy_stc_usb_dev_endpoint_t const * const *) descr->alternates[alt]->endpoints,
                                                           context);
                }

                if (CY_USB_DEV_SUCCESS == retStatus)
                {
                    /* Notify Bus Reset event for device instance */
                    if (NULL != context->eventsCallback)
                    {
                        /* Input parameters are zeros. Ignore return for Bus Reset event. */
                        retStatus = context->eventsCallback(CY_USB_DEV_EVENT_SET_INTERFACE, alt, intf, context);
                    }

                    if (CY_USB_DEV_SUCCESS == retStatus)
                    {
                        /* Call Set Interface callbacks for a Class */
                        retStatus = CallSetInterfaceCallbacks(intf, alt, context->classRoot, context);
                    }
                }

                /* Check request complete status */
                if (CY_USB_DEV_SUCCESS == retStatus)
                {
                    /* Store current alternate settings */
                    context->configChanged   = true;
                    context->alternate[intf] = (uint8_t) alt;
                }
            }
            else
            {
                /* Do nothing: current alternate is already set */
                retStatus = CY_USB_DEV_SUCCESS;
            }
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: SetFeatureRequest
****************************************************************************//**
*
* Handles SET_FEATURE standard request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t SetFeatureRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    /* Endpoint or interface must be zero if device is not configured */
    if (CY_USB_DEV_CONFIGURED != context->state)
    {
        if (0U != transfer->setup.wIndex)
        {
            return CY_USB_DEV_REQUEST_NOT_HANDLED;
        }
    }

    /* Find request recipient */
    switch (transfer->setup.bmRequestType.recipient)
    {
        case CY_USB_DEV_RECIPIENT_DEVICE:
        {
            /* Check feature selector: TEST_MODE is not supported */
            if (CY_USB_DEV_DEVICE_REMOTE_WAKEUP == transfer->setup.wValue)
            {
                context->status |= CY_USB_DEV_STATUS_REMOTE_WAKEUP_MASK;
                retStatus = CY_USB_DEV_SUCCESS;
            }
        }
        break;

        case CY_USB_DEV_RECIPIENT_INTERFACE:
            /* There is no feature selector this recipient */
        break;

        case CY_USB_DEV_RECIPIENT_ENDPOINT:
        {
            /* Check that feature selector is ENDPOINT_HALT */
            if (CY_USB_DEV_ENDPOINT_HALT == transfer->setup.wValue)
            {
                uint32_t endpoint = CY_USB_DEV_EPADDR2EP(transfer->setup.wIndex);

                /* Only enabled and data endpoints can be STALLED */
                retStatus = (cy_en_usb_dev_status_t)
                            Cy_USBFS_Dev_Drv_StallEndpoint(context->drvBase,
                                endpoint, context->drvContext);

                if (CY_USB_DEV_SUCCESS != retStatus)
                {
                    retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;
                }
            }
        }
        break;

        default:
            /* Unknown recipient */
            break;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: HandleStandardRequests
****************************************************************************//**
*
* Handles supported standard requests.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleStandardRequests(cy_stc_usb_dev_control_transfer_t *transfer,
                                                     cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    /* Direction is Device to Host: DATA stage direction is IN */
    if (CY_USB_DEV_DIR_DEVICE_TO_HOST == transfer->direction)
    {
        switch (transfer->setup.bRequest)
        {
            case CY_USB_DEV_RQST_GET_DESCRIPTOR:
                retStatus = GetDescriptorRequest(transfer, context);
            break;

            case CY_USB_DEV_RQST_GET_CONFIGURATION:
                retStatus = GetConfigurationRequest(transfer, context);
            break;

            case CY_USB_DEV_RQST_GET_INTERFACE:
                retStatus = GetInterfaceRequest(transfer, context);
            break;

            case CY_USB_DEV_RQST_GET_STATUS:
                retStatus = GetStatusRequest(transfer, context);
            break;

            default:
            /* Do nothing. */
            break;
        }
    }
    /* Direction is Host to Device: DATA stage direction is OUT or no DATA stage */
    else
    {
        switch (transfer->setup.bRequest)
        {
            case CY_USB_DEV_RQST_SET_ADDRESS:
                retStatus = SetAddressRequest(transfer, context);
            break;

            case CY_USB_DEV_RQST_SET_DESCRIPTOR:
                /* This request is optional and not supported */
            break;

            case CY_USB_DEV_RQST_SET_CONFIGURATION:
                retStatus = SetConfigurationRequest(transfer, context);
            break;

            case CY_USB_DEV_RQST_SET_INTERFACE:
                retStatus = SetInterfaceRequest(transfer, context);
            break;

            case CY_USB_DEV_RQST_CLEAR_FEATURE:
                retStatus = ClearFeatureRequest(transfer, context);
            break;

            case CY_USB_DEV_RQST_SET_FEATURE:
                retStatus = SetFeatureRequest(transfer, context);
            break;

            default:
            /* Do nothing. */
            break;
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: HandleClassRequests
****************************************************************************//**
*
* Handles supported class requests.
*
* \param curItem
* The pointer to class linked list element.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleClassRequests(cy_stc_usb_dev_class_ll_item_t    *curItem,
                                                  cy_stc_usb_dev_control_transfer_t *transfer,
                                                  cy_stc_usb_dev_context_t          *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    /* Call Request Received callback for all class instances */
    while (NULL != curItem)
    {
        /* Execute callback */
        if (NULL != curItem->classObj->requestReceived)
        {
            retStatus = curItem->classObj->requestReceived(transfer, curItem->classData, context);

            if (CY_USB_DEV_SUCCESS == retStatus)
            {
                /* Request is handled, exit loop */
                break;
            }
        }

        /* Move to next element */
        curItem = curItem->next;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: HandleClassRequestsComplete
****************************************************************************//**
*
* Handles supported class requests completion stage (data was
* received from the USB Host).
*
* \param curItem
* The pointer to class linked list element.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleClassRequestsCompleted(cy_stc_usb_dev_class_ll_item_t    *curItem,
                                                           cy_stc_usb_dev_control_transfer_t *transfer,
                                                           cy_stc_usb_dev_context_t          *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    /* Call Request Complete callback for all class instances */
    while (NULL != curItem)
    {
        /* Execute callback */
        if (NULL != curItem->classObj->requestCompleted)
        {
            retStatus = curItem->classObj->requestCompleted(transfer, curItem->classData, context);

            if (CY_USB_DEV_SUCCESS == retStatus)
            {
                /* Request is handled, exit loop */
                break;
            }
        }

        /* Move to next element */
        curItem = curItem->next;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: GetExtOsStringDescriptors
****************************************************************************//**
*
* Handles supported vendor-specific requests.
*
* \param msOsString
* The pointer to the MS OS String structure \ref cy_stc_usb_dev_ms_os_string_t.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetExtOsStringDescriptors(cy_stc_usb_dev_ms_os_string_t const *msOsString,
                                                        cy_stc_usb_dev_control_transfer_t   *transfer)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    /* Direction is Device to Host: DATA stage direction is IN */
    if (CY_USB_DEV_DIR_DEVICE_TO_HOST == transfer->direction)
    {
        if (transfer->setup.bRequest == msOsString->msVendorCode)
        {
            switch(transfer->setup.wIndex)
            {
                case CY_USB_DEV_MS_OS_STRING_EXT_COMPAT_ID:
                case CY_USB_DEV_MS_OS_STRING_EXT_PROPERTEIS:
                {
                    /* Get Extended Compat ID / Properties OS Descriptor (ignores wValue) */
                    uint8_t *strDescr = (uint8_t *) ((CY_USB_DEV_MS_OS_STRING_EXT_COMPAT_ID == transfer->setup.wIndex) ?
                                                  msOsString->extCompatIdDescriptor : msOsString->extPropertiesDescriptor);

                    if (NULL != strDescr)
                    {
                        transfer->ptr = strDescr;
                        transfer->remaining = GET_UINT16(strDescr[EXT_OS_DESC_LENGTH_BYTE0_POS],
                                                         strDescr[EXT_OS_DESC_LENGTH_BYTE1_POS]);

                        retStatus = CY_USB_DEV_SUCCESS;
                    }
                }
                break;

                default:
                /* Do nothing. */
                    break;
            }
        }
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: HandleVendorRequests
****************************************************************************//**
*
* Handles supported vendor-specific requests.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleVendorRequests(cy_stc_usb_dev_control_transfer_t *transfer,
                                                   cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    /* Get pointer to MS OS String descriptor structure */
    const cy_stc_usb_dev_ms_os_string_t *msOsString = context->devDescriptors->strings->osStringDescriptors;

    if (NULL != msOsString)
    {
        retStatus = GetExtOsStringDescriptors(msOsString, transfer);
    }

    if ((CY_USB_DEV_SUCCESS != retStatus) && (NULL != context->vndRequestReceived))
    {
        /* There is no classContext for vendor-specific callbacks */
        retStatus = context->vndRequestReceived(transfer, NULL, context);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: HandleVendorRequestsComplete
****************************************************************************//**
*
* Handles supported vendor-specific requests completion stage (data was
* received from the USB Host).
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t HandleVendorRequestsCompleted(cy_stc_usb_dev_control_transfer_t *transfer,
                                                            cy_stc_usb_dev_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    if (NULL != context->vndRequestCompleted)
    {
        /* There is no classContext for vendor-specific callbacks */
        retStatus = context->vndRequestCompleted(transfer, NULL, context);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_RegisterClass
****************************************************************************//**
*
* Registers device class that will be supported by USB Device.
* The USB Device provides a hooks to implement required class support.
*
* \param classItem
* The pointer to class linked list element.
*
* \param classObj
* The pointer to the class structure.
*
* \param classContext
* The pointer to the context class structure allocated by the user.
* The structure is used during the custom class operation for internal
* configuration and data retention.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
cy_en_usb_dev_status_t Cy_USB_Dev_RegisterClass(cy_stc_usb_dev_class_ll_item_t *classItem,
                                                cy_stc_usb_dev_class_t *classObj,
                                                void *classContext,
                                                cy_stc_usb_dev_context_t *context)
{
    if ((NULL == classItem) || (NULL == classObj))
    {
        return CY_USB_DEV_BAD_PARAM;
    }

    /* Get linked list of classes */
    cy_stc_usb_dev_class_ll_item_t *curItem = context->classRoot;

    /* Store data members */
    classItem->classObj  = classObj;
    classItem->classData = classContext;
    classItem->next      = NULL;

    if (NULL == curItem)
    {
        /* Add 1st element */
        context->classRoot = classItem;
    }
    else
    {
        /* Find last element */
        while (NULL != curItem->next)
        {
            curItem = curItem->next;
        }

        /* Add current item to the end of the list */
        curItem->next = classItem;
    }

    return CY_USB_DEV_SUCCESS;
}

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */


/* [] END OF FILE */
