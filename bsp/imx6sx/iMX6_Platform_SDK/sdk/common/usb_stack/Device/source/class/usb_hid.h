/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
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
 * @file usb_hid.h
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains USB stack HID class layer API header function.
 *
 *****************************************************************************/

#ifndef _USB_HID_H
#define _USB_HID_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_descriptor.h"
#include "usb_class.h"
#ifdef COMPOSITE_DEV
	#include "usb_composite.h"
#endif
#include "usb_devapi.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define MAX_QUEUE_ELEMS                 (4)

 /* class specific requests */
#define USB_HID_GET_REPORT_REQUEST      (0x01)
#define USB_HID_GET_IDLE_REQUEST        (0x02)
#define USB_HID_GET_PROTOCOL_REQUEST    (0x03)
#define USB_HID_SET_REPORT_REQUEST      (0x09)
#define USB_HID_SET_IDLE_REQUEST        (0x0A)
#define USB_HID_SET_PROTOCOL_REQUEST    (0x0B)

/* for class specific requests */
#define HIGH_BYTE_SHIFT                 (8)
#define MSB_MASK                        (0xFF00)
#define USB_HID_REQUEST_DIR_MASK        (0x08)
#define USB_HID_REQUEST_TYPE_MASK       (0x01)
#define REPORT_SIZE                     (4)
#define CLASS_REQ_DATA_SIZE             (0x01)

#define HID_ENDPOINT (1)

/******************************************************************************
 * Types
 *****************************************************************************/

 /* structure to hold a request in the endpoint queue */
typedef struct _usb_class_hid_queue
{
    uint_8 controller_ID;   /* Controller ID*/
    uint_8 channel;         /* Endpoint number */
    uint_8_ptr app_buff;    /* Buffer to send */
    USB_PACKET_SIZE size;   /* Size of the transfer */
}USB_CLASS_HID_QUEUE, *PTR_USB_CLASS_HID_QUEUE;

/* USB class hid endpoint data */
typedef struct _usb_class_hid_endpoint
{
    uint_8 endpoint;        /* Endpoint number */
    uint_8 type;            /* Type of endpoint (interrupt,
                               bulk or isochronous) */
    uint_8 bin_consumer;    /* Num of queued elements */
    uint_8 bin_producer;    /* Num of de-queued elements */
    uint_8 queue_num;       /* HIGH SPEED: Num of queue */
    USB_CLASS_HID_QUEUE queue[MAX_QUEUE_ELEMS]; /* Queue data */
}USB_CLASS_HID_ENDPOINT;

/* contains the endpoint data for non control endpoints */
typedef struct _usb_class_hid_endpoint_data
{
    /* Num of non control endpoints */
    uint_8 count;
    /* contains the endpoint info */
#ifndef COMPOSITE_DEV
    USB_CLASS_HID_ENDPOINT ep[USB_MAX_SUPPORTED_ENDPOINTS]; //HID_DESC_ENDPOINT_COUNT];
#else
	USB_CLASS_HID_ENDPOINT ep[COMPOSITE_DESC_ENDPOINT_COUNT];
#endif
}USB_CLASS_HID_ENDPOINT_DATA, *PTR_USB_CLASS_HID_ENDPOINT_DATA;

/******************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_Class_HID_Init (
    uint_8                          controller_ID,
    USB_CLASS_CALLBACK              hid_class_callback,
    USB_REQ_FUNC                    vendor_req_callback,
    USB_CLASS_SPECIFIC_HANDLER_FUNC param_callback
);

extern void USB_Class_Hid_Event (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event,           /* [IN] Event Type */
    void* val               /* [IN] Pointer to configuration Value */  
);

#ifdef COMPOSITE_DEV
extern uint_8 USB_HID_Other_Requests(uint_8 controller_ID,
                          USB_SETUP_STRUCT * setup_packet,
                          uint_8_ptr *data,
                          USB_PACKET_SIZE *size);
#endif
extern uint_8 USB_Class_HID_DeInit 
(
    uint_8 controller_ID             
);

extern uint_8 USB_Class_HID_Send_Data (
    uint_8           controller_ID,
    uint_8           ep_num,
    uint_8_ptr       buff_ptr,
    USB_PACKET_SIZE  size
);

#define USB_Class_HID_Periodic_Task USB_Class_Periodic_Task

void USB_Service_Hid (PTR_USB_DEV_EVENT_STRUCT event);

#endif
