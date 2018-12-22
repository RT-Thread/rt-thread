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
 * @file usb_audio.h
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains USB stack Audio class layer API header function.
 *
 *****************************************************************************/

#ifndef _USB_AUDIO_H
#define _USB_AUDIO_H

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
#define  KBI_STAT_MASK              (0x0F)
#define  BUTTON_0                   (0x01)
#define  BUTTON_1                   (0x02)
#define  BUTTON_2                   (0x04) 
#define  BUTTON_3                   (0x08)

#define MAX_QUEUE_ELEMS             (4)

/* class specific requests */
#define USB_AUDIO_SET_REQUEST_INTF  (0x21)
#define USB_AUDIO_GET_REQUEST_INTF  (0xA1)

#define REQEUST_CODE_UNDEFINED      (0x00)
#define SET_CUR                     (0x01)
#define GET_CUR                     (0x81)
#define SET_MIN                     (0x02)
#define GET_MIN                     (0x82)
#define SET_MAX                     (0x03)
#define GET_MAX                     (0x83)
#define SET_RES                     (0x04)
#define GET_RES                     (0x84)
#define SET_MEM                     (0x05)
#define GET_MEM                     (0x85)
#define GET_STAT                    (0xFF)


#define MUTE_CONTROL                (0x01)
#define VOLUME_CONTROL              (0x02)
/* for class specific requests */
#define HIGH_BYTE_SHIFT             (8)
#define MSB_MASK                    (0xFF00)
#define USB_AUDIO_REQUEST_DIR_MASK  (0x08)
#define USB_AUDIO_REQUEST_TYPE_MASK (0x01)
#define REPORT_SIZE                 (4)
#define CLASS_REQ_DATA_SIZE         (0x01)

/* Code of bmRequest Type */
#define SET_REQUEST_ITF             (0x21)  /* for Entities */
#define SET_REQUEST_EP              (0x22)  /* for Endpoints */
#define GET_REQUEST_ITF             (0xA1)  /* for Entities */
#define GET_REQUEST_EP              (0xA2)  /* for Endpoints */


/* Audio Interface Class Code */
#define AUDIO                       (0x01)

/* Audio Interface Subclass Codes */
#define  AUDIOCONTROL               (0x01)
#define  AUDIOSTREAMING             (0x02)
#define  MIDISTRAMING               (0x03)

/* Audio Interface Protocol codes */
#define PR_PROTOCOL_UNDEFINED       (0x00)

/* Audio Class Specific Descriptor Types */
#define CS_UNDEFINED                (0x20)
#define CS_DEVICE                   (0x21)
#define CS_CONFIGURATION            (0x22)
#define CS_STRING                   (0x23)
#define CS_INTERFACE                (0x24)
#define CS_ENDPOINT                 (0x25)

/* Audio Class Specific AC Interface Descriptor */
#define HEADER                      (0x01)
#define INPUT_TERMINAL              (0x02)
#define OUTPUT_TERMINAL             (0x03)
#define MIXER_UNIT                  (0x04)
#define SELECTOR_UNIT               (0x05) 
#define FEATURE_UNIT                (0x06)
#define PROCESSING_UNIT             (0x07)
#define EXTENSION_UNIT              (0x08)

/* Audio Class Specific AS Interface Descriptor Subtypes */
#define AS_GENERAL                  (0x01)
#define FORMAT_TYPE                 (0x02)
#define FORMAT_SPECIFIC             (0x03)


/* Audio Class Specific Endpoint Descriptor subtypes */
#define  EP_GENRAL                  (0x01)

/* Audio Class Specific Request Codes */
#define  SET_CUR                    (0x01)
#define  GET_CUR                    (0x81)
#define  SET_MIN                    (0x02)
#define  GET_MIN                    (0x82)
#define  SET_MAX                    (0x03)
#define  GET_MAX                    (0x83)
#define  SET_RES                    (0x04)
#define  GET_RES                    (0x84)
#define  SET_MEM                    (0x05)
#define  GET_MEM                    (0x85)
#define  GET_STAT                   (0xFF)

/* Terminal Control Selector codes  */
#define COPY_PROTECT_CONTROL        (0x01)

/* Feature Unit Control Selector codes */
#define MUTE_CONTROL                (0x01)
#define VOLUME_CONTROL              (0x02)
#define BASS_CONTROL                (0x03)
#define MID_CONTROL                 (0x04)
#define TREBLE_CONTROL              (0x05)
#define GRAPHIC_EQUALIZER_CONTROL   (0x06)
#define AUTOMATIC_GAIN_CONTROL      (0x07)
#define DELAY_CONTROL               (0x08)
#define BASS_BOOST_CONTROL          (0x09)
#define LOUDNESS_CONTROL            (0x0A)

/* Endpoint Definition */
#define SAMPLING_FREQ_CONTROL       (0x01)
#define PITCH_CONTROL               (0x02)

/*  Definition Size */

#define SIZE_COPY_PROTECT_CONTROL   (1)

#if AUDIO_CLASS_2_0
/* Clock Source Control Selectors(A.17.1) */
#define CS_CONTROL_UNDEFINED        (0x00)
#define CS_SAM_FREQ_CONTROL         (0x01)
#define CS_CLOCK_VALID_CONTROL      (0x02)
#endif /* AUDIO_CLASS_2_0 */

/******************************************************************************
 * Types
 *****************************************************************************/

/* structure to hold a request in the endpoint queue */
typedef struct _usb_class_audio_queue
{
    uint_8 controller_ID;   /* Controller ID*/
    uint_8 channel;         /* Endpoint number */
    uint_8_ptr app_buff;    /* Buffer to send */
    USB_PACKET_SIZE size;   /* Size of the transfer */
}USB_CLASS_AUDIO_QUEUE, *PTR_USB_CLASS_AUDIO_QUEUE;

/* USB class Audio endpoint data */
typedef struct _usb_class_audio_endpoint
{
    uint_8 endpoint;        /* Endpoint number */
    uint_8 type;            /* Type of endpoint (interrupt,
                               bulk or isochronous) */
    uint_8 bin_consumer;    /* Num of queued elements */
    uint_8 bin_producer;    /* Num of de-queued elements */
    uint_8 queue_num;       /* Num of queue */
    USB_CLASS_AUDIO_QUEUE queue[MAX_QUEUE_ELEMS]; /* Queue data */
}USB_CLASS_AUDIO_ENDPOINT;

/* contains the endpoint data for non control endpoints */
typedef struct _usb_class_audio_endpoint_data
{
    /* Num of non control endpoints */
    uint_8 count;
    /* contains the endpoint info */
#ifndef COMPOSITE_DEV
    USB_CLASS_AUDIO_ENDPOINT ep[AUDIO_DESC_ENDPOINT_COUNT];
#else
	USB_CLASS_AUDIO_ENDPOINT ep[COMPOSITE_DESC_ENDPOINT_COUNT];
#endif
}USB_CLASS_AUDIO_ENDPOINT_DATA, *PTR_USB_CLASS_AUDIO_ENDPOINT_DATA;

/******************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 kbi_stat; /*records the status of the buttons (PTG0-PTG3) */

extern uint_8 USB_Class_Audio_Init (
    uint_8                          controller_ID,
    USB_CLASS_CALLBACK              Audio_class_callback,
    USB_REQ_FUNC                    vendor_req_callback,
    USB_CLASS_CALLBACK              param_callback
);

uint_8 USB_Class_Audio_DeInit 
(
    uint_8 controller_ID              
);

extern uint_8 USB_Class_Audio_Send_Data (
    uint_8           controller_ID,
    uint_8           ep_num,
    uint_8_ptr       buff_ptr,
    USB_PACKET_SIZE  size
);

extern uint_8 USB_Class_Audio_Recv_Data (
    uint_8           controller_ID,
    uint_8           ep_num,
    uint_8_ptr       buff_ptr,
    USB_PACKET_SIZE  size
);

extern void USB_Class_Audio_Event (
    uint_8 controller_ID,  
    uint_8 event,          
    void* val              
);

#ifdef COMPOSITE_DEV
uint_8 USB_Audio_Other_Requests(uint_8 controller_ID,
    USB_SETUP_STRUCT * setup_packet,
    uint_8_ptr *data,
    USB_PACKET_SIZE *size);
#endif
#define USB_Class_Audio_Periodic_Task USB_Class_Periodic_Task

/*****************************************************************************
 * Local Functions
 *****************************************************************************/

void USB_Service_Audio_Status_Interrupt(PTR_USB_DEV_EVENT_STRUCT event);
void USB_Service_Audio_Isochronous_IN(PTR_USB_DEV_EVENT_STRUCT event);
void USB_Service_Audio_Isochronous_OUT(PTR_USB_DEV_EVENT_STRUCT event);

#endif
