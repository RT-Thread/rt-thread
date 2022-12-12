/***************************************************************************//**
* \file cy_usb_dev_hid.c
* \version 2.10
*
* Provides HID class-specific API implementation.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "cy_usb_dev_hid.h"

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))


/*******************************************************************************
*                             Internal Macro
*******************************************************************************/

/* Get Idle request response length */
#define HID_IDLE_RATE_LENGTH        (1U)

/* Get Protocol request response length */
#define HID_PROTOCOL_LENGTH         (1U)

/* Set protocol mask */
#define HID_PROTOCOL_MASK           (0x01U)

/* Set default idle rate */
#define HID_IDLE_RATE_INDEFINITE    (0U)


/*******************************************************************************
* Internal Functions Prototypes
*******************************************************************************/

static void HandleBusReset(void *classContext, cy_stc_usb_dev_context_t *devContext);

static cy_en_usb_dev_status_t HandleRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                            void *classContext,
                                            cy_stc_usb_dev_context_t *devContext);

static cy_en_usb_dev_status_t HandleRequestComplete(cy_stc_usb_dev_control_transfer_t *transfer,
                                                    void *classContext,
                                                    cy_stc_usb_dev_context_t *devContext);

static cy_en_usb_dev_status_t GetDescriptorHidReportRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                            cy_stc_usb_dev_hid_t const *hid);

static cy_en_usb_dev_status_t GetDescriptorHidClassRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                           cy_stc_usb_dev_hid_t const *hid);

static cy_en_usb_dev_status_t GetReportRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                               cy_stc_usb_dev_hid_context_t const *context);

static cy_en_usb_dev_status_t GetProtocolRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                   cy_stc_usb_dev_hid_context_t *context);

static cy_en_usb_dev_status_t GetIdleRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                             cy_stc_usb_dev_hid_t const *hid,
                                             cy_stc_usb_dev_hid_context_t *context);

static cy_en_usb_dev_status_t SetReportRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                               cy_stc_usb_dev_hid_context_t const *context);

static cy_en_usb_dev_status_t SetReportRequestComplete(cy_stc_usb_dev_control_transfer_t *transfer,
                                                       cy_stc_usb_dev_hid_context_t const *context);

static cy_en_usb_dev_status_t SetProtocolRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                 cy_stc_usb_dev_hid_context_t *context);

static void UpdateIdleRateTimer(uint32_t idx, cy_stc_usb_dev_hid_context_t *context);

static cy_en_usb_dev_status_t SetIdleRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                             cy_stc_usb_dev_hid_t const *hid,
                                             cy_stc_usb_dev_hid_context_t *context);

static cy_stc_usb_dev_hid_t const * GetHidStruct(uint32_t intf,
                                                cy_stc_usb_dev_context_t *devContext);

static cy_en_usb_dev_status_t GetInputReportIdx(uint32_t reportId, uint32_t *idx,
                                                cy_stc_usb_dev_hid_t const *hid,
                                                cy_stc_usb_dev_hid_context_t const *context);


/*******************************************************************************
* Function Name: Cy_USB_Dev_HID_Init
****************************************************************************//**
*
* Initializes the HID class.
* This function must be called to enable USB Device HID functionality.
*
* \param config
* The pointer to the HID configuration
* structure \ref cy_stc_usb_dev_hid_config_t.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
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
cy_en_usb_dev_status_t Cy_USB_Dev_HID_Init(cy_stc_usb_dev_hid_config_t const *config,
                                           cy_stc_usb_dev_hid_context_t      *context,
                                           cy_stc_usb_dev_context_t          *devContext)
{
    /* Input parameters verification */
    if ((NULL == config) || (NULL == context) || (NULL == devContext))
    {
        return CY_USB_DEV_BAD_PARAM;
    }

    /* SETUP data storage */
    context->idleRate  = config->timers;
    context->idleTimer = &config->timers[config->timersNum];
    context->timersNum = config->timersNum;

    /* Remove custom handlers */
    context->handleGetReport = NULL;
    context->handleSetReport = NULL;

    /* Store device context */
    context->devContext = devContext;

    /* Register HID handlers */
    Cy_USB_Dev_RegisterClassBusResetCallback(&HandleBusReset, Cy_USB_Dev_HID_GetClass(context));
    Cy_USB_Dev_RegisterClassRequestRcvdCallback(&HandleRequest, Cy_USB_Dev_HID_GetClass(context));
    Cy_USB_Dev_RegisterClassRequestCmpltCallback(&HandleRequestComplete, Cy_USB_Dev_HID_GetClass(context));

    return Cy_USB_Dev_RegisterClass(&context->classItem, &context->classObj, context, devContext);
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_HID_UpdateTimer
****************************************************************************//**
*
* Updates the HID Report idle timer and returns the status of the timer. This
* function also reloads the timer if it expires.
*
* \param interface
* Contains the interface number that contains the HID descriptor whose HID timer
* needs to be updated.
*
* \param reportId
* Report ID whose HID timer needs to be updated.
* Pass 0 if report ID is not used.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* The state of the HID timer \ref cy_en_usb_dev_hid_timer_state_t
*
*******************************************************************************/
cy_en_usb_dev_hid_timer_state_t Cy_USB_Dev_HID_UpdateTimer(uint32_t  interface,
                                                           uint32_t  reportId,
                                        cy_stc_usb_dev_hid_context_t *context)
{
    cy_en_usb_dev_hid_timer_state_t retState = CY_USB_DEV_HID_TIMER_INDEFINITE;

    cy_stc_usb_dev_hid_t const *hidStruct = GetHidStruct(interface, context->devContext);

    /* Check that HID exists for given interface */
    CY_ASSERT_L1(NULL != hidStruct);

    if (NULL != hidStruct)
    {
        uint32_t idx;
        cy_en_usb_dev_status_t locStatus = GetInputReportIdx(reportId, &idx, hidStruct, context);

        /* Check that Report ID exists for given interface */
        CY_ASSERT_L1(CY_USB_DEV_SUCCESS == locStatus);

        if (CY_USB_DEV_SUCCESS == locStatus)
        {
            /* Protect from race condition between SET_IDLE request and timer update */
            uint32_t intrState = Cy_SysLib_EnterCriticalSection();

            /* Check if duration is defined */
            if (context->idleRate[idx] != HID_IDLE_RATE_INDEFINITE)
            {
                /* Run timer */
                if (context->idleTimer[idx] > 0U)
                {
                    context->idleTimer[idx]--;
                    retState = CY_USB_DEV_HID_TIMER_RUNNING;
                }
                else
                {
                    context->idleTimer[idx] = context->idleRate[idx];
                    retState = CY_USB_DEV_HID_TIMER_EXPIRED;
                }
            }

            Cy_SysLib_ExitCriticalSection(intrState);
        }
    }

    return retState;
}


/*******************************************************************************
* Function Name: HandleBusReset
****************************************************************************//**
*
* Handles Bus Reset event: clears HID protocol and idle rate timers.
*
* \param classContext
* Contains the interface number that contains the HID descriptor whose HID timer
* needs to be updated.
*
* \param devContext
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
*
*******************************************************************************/
static void HandleBusReset(void *classContext, cy_stc_usb_dev_context_t *devContext)
{
    /* Suppress a compiler warning about unused variables */
    (void) devContext;

    cy_stc_usb_dev_hid_context_t *context = (cy_stc_usb_dev_hid_context_t *) classContext;

    /* Set protocol to default */
    (void) memset((void *) context->protocol, (int32_t) CY_USB_DEV_HID_PROTOCOL_REPORT, (uint32_t) CY_USB_DEV_NUM_INTERFACES_MAX);

    /* Set idle rate to default */
    (void) memset(context->idleRate,  (int32_t) HID_IDLE_RATE_INDEFINITE, (uint32_t) context->timersNum);
    (void) memset(context->idleTimer, (int32_t) HID_IDLE_RATE_INDEFINITE, (uint32_t) context->timersNum);
}


/*******************************************************************************
* Function Name: HandleRequest
****************************************************************************//**
*
* Handles HID class requests (SETUP packet received event).
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param classContext
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
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

    /* Get HID pointer for this interface (all HID requests using wIndex to pass interface) */
    cy_stc_usb_dev_hid_t const *hidStruct = GetHidStruct((uint32_t) transfer->setup.wIndex, devContext);

    if (NULL == hidStruct)
    {
        return CY_USB_DEV_REQUEST_NOT_HANDLED;
    }

    /* Process standard requests */
    if (CY_USB_DEV_STANDARD_TYPE == transfer->setup.bmRequestType.type)
    {
        if (CY_USB_DEV_RQST_GET_DESCRIPTOR == transfer->setup.bRequest)
        {
            switch (CY_USB_DEV_GET_DESCR_TYPE(transfer->setup.wValue))
            {
                case CY_USB_DEV_HID_REPORT_DESCRIPTOR:
                    retStatus = GetDescriptorHidReportRequest(transfer, hidStruct);
                break;

                case CY_USB_DEV_HID_DESCRIPTOR:
                    retStatus = GetDescriptorHidClassRequest(transfer, hidStruct);
                break;

                default:
                    /* The request was not recognized */
                break;
            }
        }
    }
    /* Process class-specific requests */
    else if (CY_USB_DEV_CLASS_TYPE == transfer->setup.bmRequestType.type)
    {
        /* Get HID context */
        cy_stc_usb_dev_hid_context_t *context = (cy_stc_usb_dev_hid_context_t *) classContext;

        if (transfer->direction == CY_USB_DEV_DIR_DEVICE_TO_HOST)
        {
            switch (transfer->setup.bRequest)
            {
                case CY_USB_DEV_HID_RQST_GET_REPORT:
                    retStatus = GetReportRequest(transfer, context);
                break;

                case CY_USB_DEV_HID_RQST_GET_PROTOCOL:
                    retStatus = GetProtocolRequest(transfer, context);
                break;

                case CY_USB_DEV_HID_RQST_GET_IDLE:
                    retStatus = GetIdleRequest(transfer, hidStruct, context);
                break;

                default:
                    /* The request was not recognized */
                break;
            }
        }
        else
        {
            switch (transfer->setup.bRequest)
            {
                case CY_USB_DEV_HID_RQST_SET_REPORT:
                    retStatus = SetReportRequest(transfer, context);
                break;

                case CY_USB_DEV_HID_RQST_SET_PROTOCOL:
                    retStatus = SetProtocolRequest(transfer, context);
                break;

                case CY_USB_DEV_HID_RQST_SET_IDLE:
                    retStatus = SetIdleRequest(transfer, hidStruct, context);
                break;

                default:
                    /* The request was not recognized */
                break;
            }
        }
    }
    else
    {
        /* The request was not recognized */
    }

    return (retStatus);
}


/*******************************************************************************
* Function Name: HandleRequestComplete
****************************************************************************//**
*
* Completes handling HID class requests that expects data from the host.
* Involved when data from the host was received.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param classContext
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
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

    /* Suppress a compiler warning about unused variables */
    (void) devContext;

    if (CY_USB_DEV_HID_RQST_SET_REPORT == transfer->setup.bRequest)
    {
        retStatus = SetReportRequestComplete(transfer, (cy_stc_usb_dev_hid_context_t *) classContext);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: GetDescriptorHidReportRequest
****************************************************************************//**
*
* Handles GET_DESCRIPOR HID Report request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param hid
* The pointer to the the structure that holds HID Class information.
*
* \return
* Returns \ref CY_USB_DEV_SUCCESS.
* The HandleRequest function checks that HID structure exist for the
* specified interface before calling GetDescriptorHidReportRequest function.
* Therefore GetDescriptorHidReportRequest successfully access to
* the HID structure.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetDescriptorHidReportRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                            cy_stc_usb_dev_hid_t const *hid)
{
    /* SETUP control transfer */
    transfer->ptr       = (uint8_t *) hid->reportDescriptor;
    transfer->remaining = hid->reportDescriptorSize;

    return CY_USB_DEV_SUCCESS;
}


/*******************************************************************************
* Function Name: GetDescriptorHidClassRequest
****************************************************************************//**
*
* Handles GET_DESCRIPOR HID Class request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param hid
* The pointer to the the structure that holds HID Class information.
*
* \return
* Returns \ref CY_USB_DEV_SUCCESS.
* The HandleRequest function checks that HID structure exist for the
* specified interface before calling GetDescriptorHidClassRequest function.
* Therefore GetDescriptorHidClassRequest successfully access to
* the HID structure.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetDescriptorHidClassRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                           cy_stc_usb_dev_hid_t const *hid)
{
    /* SETUP control transfer */
    transfer->ptr       = (uint8_t *) hid->hidDescriptor;
    transfer->remaining = CY_USB_DEV_HID_DESCRIPTOR_LENGTH;

    return CY_USB_DEV_SUCCESS;
}


/*******************************************************************************
* Function Name: GetReportRequest
****************************************************************************//**
*
* Handles GET_REPORT HID Class request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetReportRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                               cy_stc_usb_dev_hid_context_t const *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    if (NULL != context->handleGetReport)
    {
        uint32_t rptSize;

        /* Get from the user report to send */
        retStatus = context->handleGetReport(
                                (uint32_t) transfer->setup.wIndex,         /* Interface */
                                (uint32_t) CY_HI8(transfer->setup.wValue), /* Report Type */
                                (uint32_t) CY_LO8(transfer->setup.wValue), /* Report ID */
                                &(transfer->ptr),
                                &rptSize);

        transfer->remaining = (uint16_t) rptSize;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: GetProtocolRequest
****************************************************************************//**
*
* Handles GET_PROTOCOL HID Class request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetProtocolRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                                 cy_stc_usb_dev_hid_context_t *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    uint32_t interface = transfer->setup.wIndex;

    if (interface < CY_USB_DEV_NUM_INTERFACES_MAX)
    {
        /* SETUP control transfer */
        transfer->ptr       = (uint8_t *) &context->protocol[interface];
        transfer->remaining = HID_PROTOCOL_LENGTH;

        retStatus = CY_USB_DEV_SUCCESS;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: GetIdleRequest
****************************************************************************//**
*
* Handles GET_IDLE HID Class request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param hid
* The pointer to the the structure that holds HID Class information.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetIdleRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                             cy_stc_usb_dev_hid_t const        *hid,
                                             cy_stc_usb_dev_hid_context_t      *context)
{
    cy_en_usb_dev_status_t retStatus;
    uint32_t idx;

    retStatus = GetInputReportIdx((uint32_t) transfer->setup.wValue, &idx, hid, context);

    if (CY_USB_DEV_SUCCESS == retStatus)
    {
        /* SETUP control transfer */
        transfer->ptr       = &context->idleRate[idx];
        transfer->remaining = HID_IDLE_RATE_LENGTH;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: SetReportRequest
****************************************************************************//**
*
* Handles SET_REPORT HID Class request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t SetReportRequest(cy_stc_usb_dev_control_transfer_t *transfer,
                                               cy_stc_usb_dev_hid_context_t const *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    if (NULL != context->handleSetReport)
    {
        /* SETUP control transfer */
        transfer->remaining = transfer->setup.wLength;
        transfer->notify    = true;

        retStatus = CY_USB_DEV_SUCCESS;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: SetReportRequestComplete
****************************************************************************//**
*
* Completes handling SET_REPORT HID Class request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t SetReportRequestComplete(cy_stc_usb_dev_control_transfer_t *transfer,
                                                       cy_stc_usb_dev_hid_context_t const *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    if (NULL != context->handleSetReport)
    {
        /* Provide the user with report data */
        retStatus = context->handleSetReport(
                                (uint32_t) transfer->setup.wIndex,         /* Interface */
                                (uint32_t) CY_HI8(transfer->setup.wValue), /* Report Type */
                                (uint32_t) CY_LO8(transfer->setup.wValue), /* Report ID */
                                transfer->ptr,
                                (uint32_t) transfer->size);
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: SetProtocolRequest
****************************************************************************//**
*
* Handles SET_PROTOCOL HID Class request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t SetProtocolRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                 cy_stc_usb_dev_hid_context_t      *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    uint32_t interface = transfer->setup.wIndex;

    if (interface < CY_USB_DEV_NUM_INTERFACES_MAX)
    {
        context->protocol[interface] = (uint8_t) (transfer->setup.wValue & HID_PROTOCOL_MASK);

        /* SETUP control transfer, no data stage */
        retStatus = CY_USB_DEV_SUCCESS;
    }

    return retStatus;
}


/*******************************************************************************
* Function Name: UpdateIdleRateTimer
****************************************************************************//**
*
* Updates Idle Rate timer after SET_IDLE request was received.
*
* \param idx
* Idle Rate timer index.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
*******************************************************************************/
static void UpdateIdleRateTimer(uint32_t idx, cy_stc_usb_dev_hid_context_t *context)
{
    /* Reset timer if Idle rate indefinite */
    if (HID_IDLE_RATE_INDEFINITE == context->idleRate[idx])
    {
        context->idleTimer[idx] = 0U;
    }
    else
    {
        /* HID spec: Set_Idle request Latency */
        if (context->idleTimer[idx] >= context->idleRate[idx])
        {
            /* Reload the timer: wait new period */
            context->idleTimer[idx] = context->idleRate[idx];
        }
        else
        {
            if (context->idleTimer[idx] >= 1U)
            {
                /* If the current period has gone past the newly prescribed
                * time duration, then a report will be generated immediately.
                * Clear timer to return TIMER_EXPIRED on next HID_UpdateTimer call.
                */
                context->idleTimer[idx] = 0U;
            }
            else
            {
                /* A new request will be executed as if it were issued
                * immediately after the last report, if the new request
                * is received at least 4 milliseconds before the end of
                * the currently executing period. If the new request is
                * received within 4 milliseconds of the end of the
                * current period, then the new request will have no
                * effect until after the report
                */

                /* Do nothing: let HID_UpdateTimer continue to counting
                * and return TIMER_EXPIRED status.
                */
            }
        }
    }
}


/*******************************************************************************
* Function Name: SetIdleRequest
****************************************************************************//**
*
* Handles SET_IDLE HID Class request.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param hid
* The pointer to the the structure that holds HID Class information.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Status of request processing: \ref CY_USB_DEV_SUCCESS or
* \ref CY_USB_DEV_REQUEST_NOT_HANDLED.
*
*******************************************************************************/
static cy_en_usb_dev_status_t SetIdleRequest(cy_stc_usb_dev_control_transfer_t const *transfer,
                                             cy_stc_usb_dev_hid_t const        *hid,
                                             cy_stc_usb_dev_hid_context_t      *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    uint32_t reportId = CY_LO8(transfer->setup.wValue);
    uint32_t idx;

    /* Get report ID index */
    retStatus = GetInputReportIdx(reportId, &idx, hid, context);

    if (CY_USB_DEV_SUCCESS == retStatus)
    {
        if (reportId > 0U)
        {
            /* Set IdleRate for defined report ID then update idle timers */
            context->idleRate[idx] = CY_HI8(transfer->setup.wValue);
            UpdateIdleRateTimer(idx, context);
        }
        else
        {
            /* Set IdleRate to all Report IDs for this HID interface */
            (void) memset(&context->idleRate[idx], (int32_t) CY_HI8(transfer->setup.wValue), (uint32_t) hid->numInputReports);

            /* Update idle timers */
            for(;idx < hid->numInputReports; ++idx)
            {
                UpdateIdleRateTimer(idx, context);
            }
        }
    }

    /* SETUP control transfer, no data stage */

    return retStatus;
}


/*******************************************************************************
* Function Name: GetHidStruct
****************************************************************************//**
*
* Returns the pointer to the structure that holds HID Class information
* for a certain interface.
*
* \param intf
* Interface number.
*
* \param devContext
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t allocated
* by the user.
*
* \return
* The pointer to HID interface structure \ref cy_stc_usb_dev_hid_t.
* If interface protocol is not HID the NULL pointer is returned.
*
*******************************************************************************/
static cy_stc_usb_dev_hid_t const * GetHidStruct(uint32_t intf, cy_stc_usb_dev_context_t *devContext)
{
    uint32_t cfg = Cy_USB_Dev_GetConfigurationIdx(devContext);

    cy_stc_usb_dev_hid_t const *hidStruct = NULL;

    /* Check if interface is valid */
    if (intf < devContext->devDescriptors->configurations[cfg]->numInterfaces)
    {
        uint32_t alt = Cy_USB_Dev_GetAlternateSettings(intf, devContext);

        /* Get report descriptor */
        hidStruct = devContext->devDescriptors->configurations[cfg]->interfaces[intf]->alternates[alt]->hid;
    }

    return hidStruct;
}


/*******************************************************************************
* Function Name: GetInputReportIdx
****************************************************************************//**
*
* Finds idle rate timer index for a certain report ID.
*
* \param reportId
* Report ID. If there is no report ID, zero must be passed.
*
* \param idx
* Idle rate timer index.
*
* \param hid
* The pointer to the the structure that holds HID Class information.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_hid_context_t
* allocated by the user. The structure is used during the HID Class operation
* for internal configuration and data retention. The user must not modify
* anything in this structure.
*
* \return
* Status code of the function execution \ref cy_en_usb_dev_status_t.
*
*******************************************************************************/
static cy_en_usb_dev_status_t GetInputReportIdx(uint32_t reportId, uint32_t *idx,
                                                cy_stc_usb_dev_hid_t const   *hid,
                                                cy_stc_usb_dev_hid_context_t const *context)
{
    cy_en_usb_dev_status_t retStatus = CY_USB_DEV_REQUEST_NOT_HANDLED;

    if (0U == reportId)
    {
        /* Return start index in idleTimer array */
        *idx = hid->inputReportPos;
        retStatus = CY_USB_DEV_SUCCESS;
    }
    else
    {
        /* Check that input report ID exists */
        if (reportId < hid->inputReportIdxSize)
        {
            /* Get report ID index in timers array */
            uint32_t tmpIdx = (uint32_t) hid->inputReportIdx[reportId];

            /* Check that index value is valid (0 is free location) */
            if ((tmpIdx > 0U) && (tmpIdx <= context->timersNum))
            {
                /* Return index in idleTimer array for report ID */
                *idx = (tmpIdx - 1U);
                retStatus = CY_USB_DEV_SUCCESS;
            }
        }
    }

    return retStatus;
}

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */


/* [] END OF FILE */
