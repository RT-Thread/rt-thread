/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file usb_driver.c
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains S08 USB stack device layer implementation.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_devapi.h" /* USB Device Layer API Header File */
#include "usb_dciapi.h" /* USB Controller API Header File */
#ifdef _MK_xxx_H_
	#include "usb_dci_kinetis.h"
#endif
#ifndef MULTIPLE_DEVICES
	#include "USB_Config.h"
#endif

/*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/


/****************************************************************************
 * Global Variables
 ****************************************************************************/
extern void USB_Control_Service (PTR_USB_DEV_EVENT_STRUCT event );
extern void USB_Reset_Service (PTR_USB_DEV_EVENT_STRUCT event );
extern void USB_Sof_Service (PTR_USB_DEV_EVENT_STRUCT event );
extern void USB_Resume_Service (PTR_USB_DEV_EVENT_STRUCT event );
extern void USB_Suspend_Service (PTR_USB_DEV_EVENT_STRUCT event );
extern void USB_Error_Service (PTR_USB_DEV_EVENT_STRUCT event );
extern void USB_Stall_Service (PTR_USB_DEV_EVENT_STRUCT event );
extern void USB_NULL_CALLBACK (PTR_USB_DEV_EVENT_STRUCT event);

/* Array of USB Service pointers */
#ifdef MULTIPLE_DEVICES
	static USB_SERVICE_CALLBACK g_usb_CB[USB_SERVICE_MAX];
#else
	static USB_SERVICE_CALLBACK g_usb_CB[USB_SERVICE_MAX] = {
		USB_EP0_CALLBACK,
		USB_EP1_CALLBACK,
		USB_EP2_CALLBACK,
		USB_EP3_CALLBACK,
		USB_EP4_CALLBACK,
		USB_EP5_CALLBACK,
		USB_EP6_CALLBACK,
		USB_EP7_CALLBACK,
		USB_EP8_CALLBACK,
		USB_EP9_CALLBACK,
		USB_EP10_CALLBACK,
		USB_EP11_CALLBACK,
		USB_EP12_CALLBACK,
		USB_EP13_CALLBACK,
		USB_EP14_CALLBACK,
		USB_EP15_CALLBACK,
		USB_BUS_RESET_CALLBACK,
		USB_SUSPEND_CALLBACK,
		USB_SOF_CALLBACK,
		USB_RESUME_CALLBACK,
		USB_SLEEP_CALLBACK,
		USB_SPEED_DETECTION_CALLBACK,
		USB_ERROR_CALLBACK,
		USB_STALL_CALLBACK
};
#endif
/* Array of USB Component Status */
/* Test mode is the last service */
static uint_8 g_usb_component_status[USB_STATUS_TEST_MODE];
/* Array of USB Endpoint Status */
static uint_8 g_usb_ep_status[MAX_SUPPORTED_ENDPOINTS];
/* Current un-initialized non CONTROL Endpoint */
static uint_8 g_EPn=0;
/* Maximum number of Non CONTROL Endpoint required by upper layer */
static uint_8 g_EPn_max=0;

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes - None
 *****************************************************************************/
static void USB_Device_Init_Params(void);

/*****************************************************************************
 * Local Variables - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
#if (defined(_MC9S08MM128_H) || defined(_MC9S08JE128_H))
#pragma CODE_SEG DEFAULT
#endif

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_DCI_Init (
    uint_8    controller_ID,
    uint_8    bVregEn
);
extern uint_8 USB_DCI_DeInit(void);

/**************************************************************************//*!
 *
 * @name  USB_Device_Init_Params
 *
 * @brief The function initializes the Device Layer Structures
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************
 * Initializes USB Device Layer Structures
 *****************************************************************************/
static void USB_Device_Init_Params(void)
{
    uint_8 loop_index=0;

    g_EPn= g_EPn_max; /* 1 control endpoint */

    /*
       Initialize USB_STATUS_DEVICE_STATE, USB_STATUS_INTERFACE,
       USB_STATUS_ADDRESS, USB_STATUS_CURRENT_CONFIG, USB_STATUS_SOF_COUNT
       and USB_STATUS_DEVICE to USB_STATUS_UNKNOWN
    */
    for(loop_index = 0; loop_index < USB_STATUS_TEST_MODE; loop_index++)
    {
        #ifdef OTG_BUILD
         if(loop_index != (USB_STATUS_OTG-1)) /* Do not initialize the OTG status with 0xFFFF */
        #endif
         {
          g_usb_component_status[loop_index] = USB_STATUS_UNKNOWN;
         }
    }

    /* Initialize status of All Endpoints to USB_STATUS_DISABLED */
    for(loop_index = 0; loop_index < MAX_SUPPORTED_ENDPOINTS; loop_index++)
    {
        g_usb_ep_status[loop_index] = USB_STATUS_DISABLED;
    }
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/


/**************************************************************************//*!
 *
 * @name  _usb_device_init
 *
 * @brief The function initializes the Device and Controller layer
 *
 * @param device_number       : USB Device controller to initialize
 * @param handle              : pointer to USB Device handle
 * @param number_of_endpoints : Endpoint count of the application
 *
 * @return status
 *         USB_OK                              : When Successfull
 *         USBERR_INVALID_NUM_OF_ENDPOINTS     : When endpoints > max Supported
 ******************************************************************************
 * This function initializes the Device layer and the Controller layer of the
 * S08 USB stack. It initializes the variables used for this layer and then
 * calls the controller layer initialize function
 *****************************************************************************/
uint_8 _usb_device_init (
    uint_8    device_number,			/* [IN] USB Device controller to initialize */
    _usb_device_handle _PTR_  handle,	/* [IN] Pointer to USB Device handle */
    uint_8    number_of_endpoints,		/* [IN] Number of endpoints to initialize */
    uint_8    bVregEn        			/* Enables or disables internal regulator */
)
{
	UNUSED(handle);

    /* validate endpoints param */
    if((number_of_endpoints > MAX_SUPPORTED_ENDPOINTS) ||
      (number_of_endpoints < MIN_SUPPORTED_ENDPOINTS))
    {
        return USBERR_INVALID_NUM_OF_ENDPOINTS;
    }

    /* init variables */
    g_EPn_max = (uint_8)(number_of_endpoints - 1);

    USB_Device_Init_Params();

#ifdef MULTIPLE_DEVICES
    /* Initialize all services to null value */
    Clear_Mem((uint_8_ptr)g_usb_CB,
        (uint_32)(sizeof(USB_SERVICE_CALLBACK) * USB_SERVICE_MAX), (uint_8)0);
#endif
    /* Call controller layer initialization function */
    return USB_DCI_Init(device_number, bVregEn);

}

/**************************************************************************//*!
 *
 * @name  _usb_device_deinit
 *
 * @brief The function de-initializes the Device and Controller layer
 *
 * @return status
 *         USB_OK                              : When Successfull
 *         USBERR_INVALID_NUM_OF_ENDPOINTS     : When endpoints > max Supported
 ******************************************************************************
 * This function de-initializes the Device layer and the Controller layer
 *****************************************************************************/
uint_8 _usb_device_deinit(void)
{
	g_EPn_max = 0;
	/* Call controller layer de-initialization function */
	return USB_DCI_DeInit();
}

/**************************************************************************//*!
 *
 * @name  _usb_device_init_endpoint
 *
 * @brief The function initializes the endpoint
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param max_packet_size : Maximum packet size (in bytes) for the endpoint
 * @param direction       : Direction of transfer
 * @param endpoint_type   : Type of endpoint
 * @param flag            : Zero termination flag
 *
 * @return status
 *         USB_OK                              : When Successfull
 *         USBERR_EP_INIT_FAILED     : When endpoints > max Supported
 ******************************************************************************
 *
 * This function initializes an endpoint the Device layer and the Controller
 * layer in the S08 USB stack. It validate whether all endpoints have already
 * been initialized or not and then calls the controller layer endpoint
 *  initialize function
 *
 *****************************************************************************/
uint_8 _usb_device_init_endpoint (
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number*/	
    uint_16               max_packet_size,    /* [IN] Maximum packet size (in bytes) for the endpoint */		
    uint_8                direction,          /* [IN] Direction of transfer */
    uint_8                endpoint_type,      /* [IN] Type of endpoint */
    uint_8                flag                /* [IN] Zero termination flag */
)
{
	USB_EP_STRUCT ep_str;
		
    uint_8 status = USB_OK;

    /* check if all endpoint have already been initialised */
    if((g_EPn == 0) && (endpoint_number != CONTROL_ENDPOINT))
    {
        return USBERR_EP_INIT_FAILED;
    }

    ep_str.direction = direction;
    ep_str.ep_num = endpoint_number;
    
#ifndef _MC9S08JS16_H    
    ep_str.size = max_packet_size;
#else
    ep_str.size = (char)max_packet_size;
#endif    
    ep_str.type = endpoint_type;

    /* call controller layer for initiazation */
    status = USB_DCI_Init_EndPoint(*((uint_8*)handle), &ep_str, flag);

    /* if endpoint successfully initialised update counter */
    if ((ep_str.ep_num != CONTROL_ENDPOINT) && (status == USB_OK))
    {
        g_EPn--;
    }

    return status;
}


/**************************************************************************//*!
 *
 * @name  _usb_device_deinit_endpoint
 *
 * @brief The function de-initializes the endpoint
 *
 * @param handle          : USB Device handle
 * @param endpoint_number : Endpoint number
 * @param direction       : Endpoint direction
 *
 * @return status
 *         USB_OK                              : When Successfull
 *         USBERR_EP_DEINIT_FAILED     : When endpoints > max Supported
 ******************************************************************************
 *
 * This function deinitializes an endpoint the Device layer and the Controller
 * layer in the S08 USB stack. It validate whether all endpoints have already
 * been deinitialized or not and then calls the controller layer endpoint
 * deinitialize function
 *
 *****************************************************************************/
uint_8 _usb_device_deinit_endpoint (
    _usb_device_handle    handle,             /* [IN] USB Device handle */
    uint_8                endpoint_number,    /* [IN] Endpoint number */
    uint_8                direction           /* [IN] Direction */
)
{
    uint_8 status=USB_OK;

    /* check if all endpoint have already been initialised */
    if((g_EPn == g_EPn_max) && (endpoint_number != CONTROL_ENDPOINT))
    {
        return USBERR_EP_DEINIT_FAILED;
    }

    /* call controller layer for initiazation */
    status = USB_DCI_Deinit_EndPoint(*((uint_8*)handle), endpoint_number, direction);

    /* if endpoint successfully deinitialised update counter */
    if ((endpoint_number != CONTROL_ENDPOINT) && (status == USB_OK))
    {
        g_EPn++;
    }

    return status;
}

/**************************************************************************//*!
 *
 * @name  _usb_device_get_status
 *
 * @brief The function retrieves various endpoint as well as USB component status
 *
 * @param handle        : USB Device handle
 * @param component     : USB component
 * @param status        : Pointer to 16 bit return value
 *
 * @return status
 *         USB_OK                : When Successfull
 *         USBERR_BAD_STATUS     : When error
 *
 ******************************************************************************
 * This function retrieves the endpoint as well USB component status which is
 * stored by calling USB_Device_Set_Status. This function can be called by Ap-
 * plication as well as the DCI layer.
 *****************************************************************************/
uint_8 _usb_device_get_status (
    _usb_device_handle    handle,       /* [IN]  USB Device handle */
    uint_8                component,    /* [IN]  USB component */
    uint_8_ptr            status        /* [OUT] Pointer to 16 bit return value */
)
{
    /* get the endpoint number from component input variable */
    uint_8 ep_num = (uint_8)(component & USB_STATUS_ENDPOINT_NUMBER_MASK);
    UNUSED (handle)

    if((component <= USB_STATUS_TEST_MODE) &&
        (component >= USB_STATUS_DEVICE_STATE))
    {
        /* Get the corresponding component status
           -1 as components start from 1 */
        *status = g_usb_component_status[component-1];
    }
    else if ((component & USB_STATUS_ENDPOINT) &&
        (ep_num < MAX_SUPPORTED_ENDPOINTS))
    {
        /* Get the corresponding endpoint status */
        *status = g_usb_ep_status[ep_num];
    }
    else
    {
        return USBERR_BAD_STATUS;
    }

    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  _usb_device_set_status
 *
 * @brief The function saves status of endpoints as well as USB components.
 *
 * @param handle    : USB Device handle
 * @param component : USB component
 * @param setting   : Value to be set
 *
 * @return status
 *         USB_OK                : When Successfull
 *         USBERR_BAD_STATUS     : When error
 *
 ******************************************************************************
 * This function sets the endpoint as well USB component status which can be
 * retrieved by calling _usb_device_get_status. This function can be called by
 * Application as well as the DCI layer.
 *****************************************************************************/
uint_8 _usb_device_set_status(
    _usb_device_handle    handle,       /* [IN] USB Device handle */
    uint_8                component,    /* [IN] USB Component status to set */
    uint_8                setting       /* [IN] Status to set */
)
{
    /* get the endpoint number from component input variable */
    uint_8 ep_num = (uint_8)(component & USB_STATUS_ENDPOINT_NUMBER_MASK);
    UNUSED (handle)

    if((component <= USB_STATUS_TEST_MODE) &&
        (component >= USB_STATUS_DEVICE_STATE))
    {
        /*
           Set the corresponding component setting
           -1 as components start from 1
        */
        g_usb_component_status[component-1] = setting;
    }
    else if ((component & USB_STATUS_ENDPOINT) &&
        (ep_num < MAX_SUPPORTED_ENDPOINTS))
    {
        uint_8 direction =
            (uint_8)((component >> USB_COMPONENT_DIRECTION_SHIFT) &
            USB_COMPONENT_DIRECTION_MASK);
        /* HALT Endpoint */
        if(setting == USB_STATUS_STALLED)
        {
        	_usb_device_stall_endpoint(handle, ep_num, direction);
        }
        else if((setting == USB_STATUS_IDLE) &&
            (g_usb_ep_status[ep_num] == USB_STATUS_STALLED))
        {
        	_usb_device_unstall_endpoint(handle, ep_num, direction);

            if(ep_num == CONTROL_ENDPOINT)
            {
                direction = (uint_8)((direction == USB_SEND)?
                    (USB_RECV):(USB_SEND));
                _usb_device_unstall_endpoint(handle, ep_num, direction);
            }
        }
        /* Set the corresponding endpoint setting */
        g_usb_ep_status[ep_num] = setting;
    }
    else
    {
        return USBERR_BAD_STATUS;
    }
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  _usb_device_register_service
 *
 * @brief The function registers a callback function from the Application layer
 *
 * @param controller_ID : Controller ID
 * @param type          : event type or endpoint number
 * @param service       : callback function pointer
 *
 * @return status
 *         USB_OK                   : When Successfull
 *         USBERR_ALLOC_SERVICE     : When invalid type or already registered
 *
 ******************************************************************************
 * This function registers a callback function from the application if it is
 * called not already registered so that the registered callback function can
 * be if the event of that type occurs
 *****************************************************************************/
uint_8 _usb_device_register_service(
    uint_8                    controller_ID, /* [IN] Controller ID           */
    uint_8                    type,          /* [IN] type of event or endpoint
                                                     number to service       */
    USB_SERVICE_CALLBACK      service        /* [IN] pointer to callback
                                                     function                */
)
{
    UNUSED (controller_ID)
    UNUSED (service)
#ifdef MULTIPLE_DEVICES
    /* check if the type is valid and callback for the type
       is not already registered */
    if(((type  <= USB_SERVICE_MAX_EP) ||
        ((type < USB_SERVICE_MAX) && (type >= USB_SERVICE_BUS_RESET))) &&
       (g_usb_CB[type] == NULL))
    {

        /* register the callback function */
        g_usb_CB[type] = service;
        return USB_OK;
    }
    else
    {
        return USBERR_ALLOC_SERVICE;
    }
#else
    UNUSED(type);
    return USB_OK;
#endif
    
}

/**************************************************************************//*!
 *
 * @name  _usb_device_unregister_service
 *
 * @brief The function unregisters an event or endpoint callback function
 *
 * @param handle         : USB Device handle
 * @param event_endpoint : event type or endpoint number
 *
 * @return status
 *         USB_OK                   : When Successfull
 *         USBERR_UNKNOWN_ERROR     : When invalid type or not registered
 *
 *****************************************************************************
 * This function un registers a callback function which has been previously
 * registered by the application layer
 *****************************************************************************/
uint_8 _usb_device_unregister_service(
    _usb_device_handle    handle,           /* [IN] USB Device handle */
    uint_8                event_endpoint    /* [IN] Endpoint (0 through 15) or event to service */
)
{
    UNUSED (handle)
    /* check if the type is valid and callback for the type
       is already registered */
    if(((event_endpoint  <= USB_SERVICE_MAX_EP) ||
        ((event_endpoint < USB_SERVICE_MAX) && (event_endpoint >= USB_SERVICE_BUS_RESET))) &&
       (g_usb_CB[event_endpoint] != NULL))
    {
#ifdef MULTIPLE_DEVICES
        /* unregister the callback */
        g_usb_CB[event_endpoint] = NULL;
#endif
        return USB_OK;
    }
    else
    {
        return USBERR_UNKNOWN_ERROR;
    }
}

/**************************************************************************//*!
 *
 * @name  USB_Device_Call_Service
 *
 * @brief The function is a device layer event handler
 *
 * @param type  : Type of service or endpoint
 * @param event : Pointer to event structure
 *
 * @return status
 *         USB_OK      : Always
 *
 *****************************************************************************
 *
 * This function calls the registered service callback function of the applic-
 * ation layer based on the type of event received. This function is called
 * from the DCI layer.
 *
 *****************************************************************************/
uint_8 USB_Device_Call_Service(
    uint_8                    type,    /* [IN] Type of service or endpoint */
    PTR_USB_DEV_EVENT_STRUCT  event    /* [IN] Pointer to event structure  */
)
{

    if(type == USB_SERVICE_BUS_RESET)
    {    /* if it is an reset interrupt then reset all status structures */
       USB_Device_Init_Params();
    }

    /* check if the callback is registered or not */
    if(g_usb_CB[type] != NULL)
    {
        /* call the callback function */
        g_usb_CB[type](event);
    }

    return USB_OK;
}

void USB_NULL_CALLBACK (PTR_USB_DEV_EVENT_STRUCT event)
{
	UNUSED(event)
	
	#if (defined(__CWCC__) || defined(__IAR_SYSTEMS_ICC__) || defined(__GNUC__))
		asm("nop");
	#elif defined (__CC_ARM)
		__nop();
	#endif	   
}
