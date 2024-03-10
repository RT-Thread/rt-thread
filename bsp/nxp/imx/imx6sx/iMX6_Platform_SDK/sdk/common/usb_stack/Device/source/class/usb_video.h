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
 * @file usb_video.h
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains USB stack Video class layer API header function.
 *
 *****************************************************************************/

#ifndef _USB_VIDEO_H
#define _USB_VIDEO_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_descriptor.h"
#include "usb_class.h"
#ifdef COMPOSITE_DEV
#include "usb_composite.h"
#endif
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define  KBI_STAT_MASK                  (0x0F)
#define  BUTTON_0                       (0x01) 
#define  BUTTON_1                       (0x02) 
#define  BUTTON_2                       (0x04) 
#define  BUTTON_3                       (0x08) 

#define MAX_QUEUE_ELEMS                 (4)


/* Code of bmRequest Type */
#define SET_REQUEST_ITF                 (0x21)
#define SET_REQUEST_EP                  (0x22)
#define GET_REQUEST_ITF                 (0xA1)
#define GET_REQUEST_EP                  (0xA2)

/******************************************************************************
 * Types
 *****************************************************************************/


 /* structure to hold a request in the endpoint queue */
typedef struct _usb_class_video_queue
{
    uint_8 controller_ID;   /* Controller ID*/
    uint_8 channel;         /* Endpoint number */
    uint_8_ptr app_buff;    /* Buffer to send */
    USB_PACKET_SIZE size;   /* Size of the transfer */
}USB_CLASS_VIDEO_QUEUE, *PTR_USB_CLASS_VIDEO_QUEUE;

/* USB class video endpoint data */
typedef struct _usb_class_video_endpoint
{
    uint_8 endpoint;        /* Endpoint number */
    uint_8 type;            /* Type of endpoint (interrupt,
                               bulk or isochronous) */
    uint_8 bin_consumer;    /* Num of queued elements */
    uint_8 bin_producer;    /* Num of de-queued elements */
    uint_8 queue_num;       /* Num of queue */
    USB_CLASS_VIDEO_QUEUE queue[MAX_QUEUE_ELEMS]; /* Queue data */
}USB_CLASS_VIDEO_ENDPOINT;

/* contains the endpoint data for non control endpoints */
typedef struct _usb_class_video_endpoint_data
{
    /* Num of non control endpoints */
    uint_8 count;
    /* contains the endpoint info */
#ifndef COMPOSITE_DEV
    USB_CLASS_VIDEO_ENDPOINT ep[VIDEO_DESC_ENDPOINT_COUNT];
#else
	USB_CLASS_VIDEO_ENDPOINT ep[COMPOSITE_DESC_ENDPOINT_COUNT];
#endif
}USB_CLASS_VIDEO_ENDPOINT_DATA, *PTR_USB_CLASS_VIDEO_ENDPOINT_DATA;

/******************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 kbi_stat; /*records the status of the buttons (PTG0-PTG3) */

extern uint_8 USB_Class_Video_Init (
    uint_8                          controller_ID,
    USB_CLASS_CALLBACK              video_class_callback,
    USB_REQ_FUNC                    vendor_req_callback,
    USB_CLASS_CALLBACK              param_callback
);

extern void USB_Class_Video_Event(
    uint_8 controller_ID,  
    uint_8 event,          
    void* val                
);

#ifdef COMPOSITE_DEV
uint_8 USB_Video_Other_Requests(uint_8 controller_ID,
                          USB_SETUP_STRUCT * setup_packet,
                          uint_8_ptr *data,
                          USB_PACKET_SIZE *size);
#endif

extern uint_8 USB_Class_Video_DeInit 
(
    uint_8 controller_ID              /* [IN] Controller ID */
); 						  
extern uint_8 USB_Class_Video_Send_Data (
    uint_8           controller_ID,
    uint_8           ep_num,
    uint_8_ptr       buff_ptr,
    USB_PACKET_SIZE  size
);

#define USB_Class_Video_Periodic_Task USB_Class_Periodic_Task

#endif
