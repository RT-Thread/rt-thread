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
 * @file usb_phdc.h
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains USB stack PHDC class layer API header function.
 *
 *****************************************************************************/

#ifndef _USB_PHDC_H
#define _USB_PHDC_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"
#include "usb_class.h"
#include "usb_descriptor.h"
#ifdef COMPOSITE_DEV
#include "usb_composite.h"
#endif

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/

#define MAX_QOS_BIN_ELEMS                 (4)
#define PHDC_RX_ENDPOINTS                 (1)/* the num of receive endpoints */
#ifndef _MC9S08JS16_H
#define PHDC_TX_ENDPOINTS                 (2)/* the num of transmit endpoints*/
#else
#define PHDC_TX_ENDPOINTS                 (1)/* the num of transmit endpoints*/
#endif
#define SET_FEATURE_REQUEST               (3)
#define CLEAR_FEATURE_REQUEST             (1)
#define GET_STATUS_REQUEST                (0)
#define INVALID_VAL                       (0xFF)

#define  USB_SET_REQUEST_MASK             (0x02)

#define USB_APP_META_DATA_PARAMS_CHANGED  (0xF2)
#define USB_APP_FEATURE_CHANGED           (0xF3)

#ifndef COMPOSITE_DEV
#if !(defined LITTLE_ENDIAN)
#define BYTE_SWAP16(a) (a)
#else
#define BYTE_SWAP16(a) (uint_16)((((uint_16)(a)&0xFF00)>>8) | \
                                    (((uint_16)(a)&0x00FF)<<8))
#endif
#endif

/******************************************************************************
 * Types
 *****************************************************************************/
#ifndef __HIWARE__
#pragma pack(1)
#endif

/* structure to hold a request in the endpoint QOS bin */
typedef struct _usb_class_phdc_qos_bin
{
    uint_8 controller_ID;   /* Controller ID*/
    uint_8 channel;         /* Endpoint number */
    boolean meta_data;      /* Packet is a meta data or not */
    uint_8 num_tfr;         /* Num of transfers that follow the meta
                               data packet.
                               used only when meta_data is TRUE */
    uint_8 qos;             /* Qos of the transfers that follow the meta
                               data packet */
    uint_8_ptr app_buff;    /* Buffer to send */
    USB_PACKET_SIZE size;   /* Size of the transfer */
}USB_CLASS_PHDC_QOS_BIN, *PTR_USB_CLASS_PHDC_QOS_BIN;

/* USB class phdc Transmit endpoint data */
typedef struct _usb_class_phdc_tx_endpoint
{
    uint_8 endpoint;                     /* from the application */
    uint_8 type;                         /* from the application */
    USB_PACKET_SIZE size;                /* from the application */
    uint_8 qos;                          /* from the application */
    uint_8 current_qos;                  /* from received meta data */
    uint_8 transfers_queued;             /* from application meta data */
    uint_8 bin_consumer;                 /* num of dequeued transfers */
    uint_8 bin_producer;                 /* num of queued transfers */
    uint_16 transfer_size;               /* Transfer Size */
    uint_16 current_offset;              /* Offset into Tranfer Size */
    USB_CLASS_PHDC_QOS_BIN qos_bin[MAX_QOS_BIN_ELEMS];
}USB_CLASS_PHDC_TX_ENDPOINT;

/* USB class phdc Receive endpoint data */
typedef struct _usb_class_phdc_rx_endpoint
{
    uint_8 endpoint;                     /* from the application */
    uint_8 type;                         /* from the application */
    USB_PACKET_SIZE size;                /* from the application */
    uint_8 qos;                          /* from the application */
    uint_8 current_qos;                  /* from received meta data */
    uint_8 transfers_left;               /* from received meta data */
    uint_16 buffer_size;                 /* Application Buffer Size */
    uint_8_ptr buff_ptr;                 /* Application Buffer Ptr */
    uint_16 transfer_size;               /* Transfer Size */
    uint_16 cur_offset;                  /* Offset into Transfer Size */
}USB_CLASS_PHDC_RX_ENDPOINT;

/* USB class phdc endpoint data */
typedef struct _usb_class_phdc_endpoint_data
{
    /* Number of recv non control endpoints */
    uint_8 count_rx;
    /* Number of send non control endpoints */
    uint_8 count_tx;
    /* Receive endpoint info structure */
    USB_CLASS_PHDC_RX_ENDPOINT ep_rx[PHDC_RX_ENDPOINTS];
    /* Send endpoint info structure */
    USB_CLASS_PHDC_TX_ENDPOINT ep_tx[PHDC_TX_ENDPOINTS];
}USB_CLASS_PHDC_ENDPOINT_DATA, *PTR_USB_CLASS_PHDC_ENDPOINT_DATA;

/* USB class phdc Transfer Size */
typedef struct _usb_class_phdc_xfer_size
{
    uint_8 direction;           /* Direction of Xfer */
    uint_8_ptr in_buff;         /* Pointer to Buffer */
    USB_PACKET_SIZE in_size;    /* Length of Buffer */
    uint_16 transfer_size;      /* Transfer Size */
#if USB_METADATA_SUPPORTED
    boolean meta_data_packet;   /* meta data packet flag */
#endif    
}USB_CLASS_PHDC_XFER_SIZE, *PTR_USB_CLASS_PHDC_XFER_SIZE;

/* USB class PHDC Receive Buffer  */
typedef struct _usb_class_phdc_rx_buff
{
    uint_8_ptr in_buff;  /* Pointer to input Buffer */
    USB_PACKET_SIZE in_size; /* Length of Input Buffer*/
    uint_16 out_size; /* Size of Output Buffer */
    uint_8_ptr out_buff; /* Pointer to Output Buffer */
    uint_16 transfer_size;
    uint_8 qos;             /* Tranfer QOS */
#if USB_METADATA_SUPPORTED
    boolean meta_data_packet;/* meta data packet flag */
#endif
}USB_CLASS_PHDC_RX_BUFF, *PTR_USB_CLASS_PHDC_RX_BUFF;

/* event structures */
typedef struct _usb_app_event_send_complete
{
    uint_8 qos;             /* Qos of the data sent */
    uint_8_ptr buffer_ptr;  /* Pointer to the buffer sent */
    USB_PACKET_SIZE size;   /* Size of the data sent */
}USB_APP_EVENT_SEND_COMPLETE, *PTR_USB_APP_EVENT_SEND_COMPLETE;

/* USB class PHDC Data Received */
typedef struct _usb_app_event_data_received
{
    uint_8 qos;             /* Qos of the data received */
    uint_8_ptr buffer_ptr;  /* Pointer to the data received */
    USB_PACKET_SIZE size;   /* Size of the data received */
    uint_16 transfer_size;  /* Total transfer Size */
}USB_APP_EVENT_DATA_RECEIVED, *PTR_USB_APP_EVENT_DATA_RECEIVED;

/* PHDC error codes */
typedef enum _usb_phdc_error
{
  USB_PHDC_SUCCESS = 0,
#if USB_METADATA_SUPPORTED
  USB_PHDC_METADATA_EXPECTED_NOT_RECEIVED = 256,
  USB_PHDC_METADATA_RECEIVED_NOT_EXPECTED = 257,
  USB_PHDC_CORRUPT_METADATA_PACKET_RECEIVED = 258,
#endif
}USB_PHDC_ERROR;

/* PHDC error structure */
typedef struct _usb_phdc_error_struct
{
    USB_PHDC_ERROR error_code;  /* PHDC Error Code */
    uint_8 qos;                 /* Tranfer QOS */
}USB_PHDC_ERROR_STRUCT, *PTR_USB_PHDC_ERROR_STRUCT;


#if USB_METADATA_SUPPORTED

#define METADATA_PREAMBLE_SIGNATURE     (16)
#define METADATA_QOSENCODING_VERSION    (1)
#define METADATA_HEADER_SIZE            (20)

/* structure for meta_data msg preamble */
typedef struct _usb_meta_data_msg_preamble
{
    /*Meta data string for verifiability*/
    char signature[METADATA_PREAMBLE_SIGNATURE];
    /* Number of transfers to follow the meta data packet */
    uint_8 num_tfr;
    /* QOS encoding version */
    uint_8 version;
    /* QOS of the transfers to follow */
    uint_8 qos;
    /* Size of the opaque meta data */
    uint_8 opaque_data_size;
    /* Opaque meta data */
    uint_8 opaque_data[1];
}USB_META_DATA_MSG_PREAMBLE, *PTR_USB_META_DATA_MSG_PREAMBLE;

/* USB class PHDC Metadata Params  */
typedef struct _usb_app_event_metadata_params
{
    uint_8 channel;             /* Endpoint number */
    uint_8 num_tfr;             /* Number of transfers */
    uint_8 qos;                 /* QOS of the data */
    uint_8_ptr metadata_ptr;    /* pointer to the meta data */
    USB_PACKET_SIZE size;       /* Size of the transfer */
}USB_APP_EVENT_METADATA_PARAMS, *PTR_USB_APP_EVENT_METADATA_PARAMS;
#endif

#if defined(__CWCC__)
#pragma options align=reset
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma pack()
#endif


/******************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_Class_PHDC_Init (
    uint_8              controller_ID,
    USB_CLASS_CALLBACK  phdc_class_callback,
    USB_REQ_FUNC        vendor_req_callback
);

extern uint_8 USB_Phdc_Other_Requests(uint_8 controller_ID,
                                    USB_SETUP_STRUCT*setup_packet,
                                    uint_8_ptr *data,
                                    USB_PACKET_SIZE *size);

#ifdef COMPOSITE_DEV                                    
extern void USB_Class_PHDC_Event (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event,           /* [IN] Event Type */
    void* val               /* [IN] Pointer to configuration Value */   
);
#endif

void USB_Class_PHDC_Endpoint_Service (
    PTR_USB_DEV_EVENT_STRUCT event  /* [IN] Pointer to USB Event Structure */
);

extern uint_8 USB_Class_PHDC_DeInit 
(
    uint_8 controller_ID              
);

extern uint_8 USB_Class_PHDC_Send_Data (
    uint_8           controller_ID,
    boolean          meta_data,
    uint_8           num_tfr,
    uint_8           current_qos,
    uint_8_ptr       app_buff,
    USB_PACKET_SIZE  size
);

#define USB_Class_PHDC_Periodic_Task    USB_Class_Periodic_Task
extern uint_8 USB_Class_PHDC_Recv_Data (
    uint_8           controller_ID,
    uint_8           current_qos,
    uint_8_ptr       app_buff,
    USB_PACKET_SIZE  size
);

#endif
