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
 * @file usb_devapi.h
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief This file contains S08 USB stack device layer API header function.
 *
 *****************************************************************************/

#ifndef _USB_DEVAPI_H
#define _USB_DEVAPI_H

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "types.h"          /* User Defined Data Types */
#include "hidef.h"          /* for EnableInterrupts macro */
#include "derivative.h"     /* include peripheral declarations */
#include "user_config.h"    /* User Configuration File */
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#ifndef _MC9S08JS16_H
#define USB_MAX_EP_BUFFER_SIZE     (512)
#else
#define USB_MAX_EP_BUFFER_SIZE     (255)
#endif

#ifndef CONTROL_ENDPOINT
#define CONTROL_ENDPOINT		(0)
#endif

#define USB_SETUP_PKT_SIZE  (8)     /* Setup Packet Size */

/* Error codes */
#define  USB_OK                              (0x00)
#define  USBERR_ALLOC                        (0x81)
#define  USBERR_BAD_STATUS                   (0x82)
#define  USBERR_CLOSED_SERVICE               (0x83)
#define  USBERR_OPEN_SERVICE                 (0x84)
#define  USBERR_TRANSFER_IN_PROGRESS         (0x85)
#define  USBERR_ENDPOINT_STALLED             (0x86)
#define  USBERR_ALLOC_STATE                  (0x87)
#define  USBERR_DRIVER_INSTALL_FAILED        (0x88)
#define  USBERR_DRIVER_NOT_INSTALLED         (0x89)
#define  USBERR_INSTALL_ISR                  (0x8A)
#define  USBERR_INVALID_DEVICE_NUM           (0x8B)
#define  USBERR_ALLOC_SERVICE                (0x8C)
#define  USBERR_INIT_FAILED                  (0x8D)
#define  USBERR_SHUTDOWN                     (0x8E)
#define  USBERR_INVALID_PIPE_HANDLE          (0x8F)
#define  USBERR_OPEN_PIPE_FAILED             (0x90)
#define  USBERR_INIT_DATA                    (0x91)
#define  USBERR_SRP_REQ_INVALID_STATE        (0x92)
#define  USBERR_TX_FAILED                    (0x93)
#define  USBERR_RX_FAILED                    (0x94)
#define  USBERR_EP_INIT_FAILED               (0x95)
#define  USBERR_EP_DEINIT_FAILED             (0x96)
#define  USBERR_TR_FAILED                    (0x97)
#define  USBERR_BANDWIDTH_ALLOC_FAILED       (0x98)
#define  USBERR_INVALID_NUM_OF_ENDPOINTS     (0x99)
#define  USBERR_NOT_SUPPORTED                (0x9A)

#define  USBERR_DEVICE_NOT_FOUND             (0xC0)
#define  USBERR_DEVICE_BUSY                  (0xC1)
#define  USBERR_NO_DEVICE_CLASS              (0xC3)
#define  USBERR_UNKNOWN_ERROR                (0xC4)
#define  USBERR_INVALID_BMREQ_TYPE           (0xC5)
#define  USBERR_GET_MEMORY_FAILED            (0xC6)
#define  USBERR_INVALID_MEM_TYPE             (0xC7)
#define  USBERR_NO_DESCRIPTOR                (0xC8)
#define  USBERR_NULL_CALLBACK                (0xC9)
#define  USBERR_NO_INTERFACE                 (0xCA)
#define  USBERR_INVALID_CFIG_NUM             (0xCB)
#define  USBERR_INVALID_ANCHOR               (0xCC)
#define  USBERR_INVALID_REQ_TYPE             (0xCD)

/* Pipe Types */
#define  USB_CONTROL_PIPE                    (0x00)
#define  USB_ISOCHRONOUS_PIPE                (0x01)
#define  USB_BULK_PIPE                       (0x02)
#define  USB_INTERRUPT_PIPE                  (0x03)

/* Device States */
#define  USB_STATE_UNKNOWN                   (0xff)
#define  USB_STATE_PENDING_ADDRESS           (0x04)
#define  USB_STATE_POWERED                   (0x03)
#define  USB_STATE_DEFAULT                   (0x02)
#define  USB_STATE_ADDRESS                   (0x01)
#define  USB_STATE_CONFIG                    (0x00)
#define  USB_STATE_SUSPEND                   (0x80)

/* Get_Status Request information for DEVICE */
#define  USB_SELF_POWERED                    (0x01)
#define  USB_REMOTE_WAKEUP                   (0x02)

/* Get_Status Request information for OTG (WINDEX = 0xF000) */
#ifdef OTG_BUILD
#define  USB_OTG_HOST_REQUEST_FLAG           (0x01)
#endif

/* Bus Control values */
#define  USB_NO_OPERATION                    (0x00)
#define  USB_ASSERT_BUS_RESET                (0x01)
#define  USB_DEASSERT_BUS_RESET              (0x02)
#define  USB_ASSERT_RESUME                   (0x03)
#define  USB_DEASSERT_RESUME                 (0x04)
#define  USB_SUSPEND_SOF                     (0x05)
#define  USB_RESUME_SOF                      (0x06)

/* possible values of Status */
#define  USB_STATUS_IDLE                     (0)
#define  USB_STATUS_TRANSFER_ACCEPTED        (6)
#define  USB_STATUS_TRANSFER_PENDING         (2)
#define  USB_STATUS_TRANSFER_IN_PROGRESS     (3)
#define  USB_STATUS_ERROR                    (4)
#define  USB_STATUS_DISABLED                 (5)
#define  USB_STATUS_STALLED                  (1)
#define  USB_STATUS_TRANSFER_QUEUED          (7)

#define  USB_STATUS_UNKNOWN                  (0xFF)

#define  USB_CONTROL_ENDPOINT     (0)

#define  USB_RECV                 (0)
#define  USB_SEND                 (1)

#define  USB_DEVICE_DONT_ZERO_TERMINATE      (0x1)

#define  USB_SETUP_DATA_XFER_DIRECTION       (0x80)

#define  USB_SPEED_FULL                      (0)
#define  USB_SPEED_LOW                       (1)
#define  USB_SPEED_HIGH                      (2)

#define  USB_MAX_PKTS_PER_UFRAME             (0x6)

#define  USB_TEST_MODE_TEST_PACKET           (0x0400)

/* Available service types */
/* Services 0 through 15 are reserved for endpoints */
#define  USB_SERVICE_EP0                     (0x00)
#define  USB_SERVICE_EP1                     (0x01)
#define  USB_SERVICE_EP2                     (0x02)
#define  USB_SERVICE_EP3                     (0x03)
#define  USB_SERVICE_EP4                     (0x04)
#define  USB_SERVICE_EP5                     (0x05)
#define  USB_SERVICE_EP6                     (0x06)
#define  USB_SERVICE_EP7                     (0x07)
#define  USB_SERVICE_EP8                     (0x08)
#define  USB_SERVICE_EP9                     (0x09)
#define  USB_SERVICE_EP10                    (0x0a)
#define  USB_SERVICE_EP11                    (0x0b)
#define  USB_SERVICE_EP12                    (0x0c)
#define  USB_SERVICE_EP13                    (0x0d)
#define  USB_SERVICE_EP14                    (0x0e)
#define  USB_SERVICE_EP15                    (0x0f)

#define  USB_SERVICE_BUS_RESET               (0x10)
#define  USB_SERVICE_SUSPEND                 (0x11)
#define  USB_SERVICE_SOF                     (0x12)
#define  USB_SERVICE_RESUME                  (0x13)
#define  USB_SERVICE_SLEEP                   (0x14)
#define  USB_SERVICE_SPEED_DETECTION         (0x15)
#define  USB_SERVICE_ERROR                   (0x16)
#define  USB_SERVICE_STALL                   (0x17)
#define  USB_SERVICE_MAX                     (0x18)

#if (defined(_MCF51JM128_H) ||defined(_MCF51MM256_H) || (defined _MCF51JE256_H))
	#define  USB_SERVICE_MAX_EP         USB_SERVICE_EP15
#else
	#ifdef  DOUBLE_BUFFERING_USED
		#define  USB_SERVICE_MAX_EP         USB_SERVICE_EP6
	#else
		#define  USB_SERVICE_MAX_EP         USB_SERVICE_EP4
	#endif
#endif

/* Informational Request/Set Types */
/* component parameter in USB_Device_Get/Set_Status */
#define USB_COMPONENT_DIRECTION_SHIFT        (7)
#define USB_COMPONENT_DIRECTION_MASK         (0x01)
#define  USB_STATUS_DEVICE_STATE             (0x01)
#define  USB_STATUS_INTERFACE                (0x02)
#define  USB_STATUS_ADDRESS                  (0x03)
#define  USB_STATUS_CURRENT_CONFIG           (0x04)
#define  USB_STATUS_SOF_COUNT                (0x05)
#define  USB_STATUS_DEVICE                   (0x06)

// Endpoint attributes
#define EP_TRANSFER_TYPE_CONTROL		(0x0<<0)
#define EP_TRANSFER_TYPE_ISOCHRONOUS	(0x1<<0)
#define EP_TRANSFER_TYPE_BULK			(0x2<<0)
#define EP_TRANSFER_TYPE_INTERRUPT		(0x3<<0)

/* Standard Request Code */
#define GET_STATUS         0x0
#define CLEAR_FEATURE      0x1
#define SET_FEATURE        0x3
#define SET_ADDRESS        0x5
#define GET_DESCRIPTOR     0x6
#define SET_DESCRIPTOR     0x7
#define GET_CONFIGURATION  0x8
#define SET_CONFIGURATION  0x9
#define GET_INTERFACE      0xA
#define SET_INTERFACE      0xB
#define SYNCH_FRAME        0xC

#ifdef OTG_BUILD
	#define  USB_STATUS_OTG                      (0x07)
	#define  USB_STATUS_TEST_MODE                (0x08)
#else
	#define  USB_STATUS_TEST_MODE                (0x07)
#endif

#define  USB_STATUS_ENDPOINT                 (0x10)
#define  USB_STATUS_ENDPOINT_NUMBER_MASK     (0x0F)

#define UNINITIALISED_VAL                    (0xffffffff)

#if (defined MCU_MK40N512VMD100) || (defined MCU_MK53N512CMD100) || (defined MCU_MK60N512VMD100) || (defined MCU_MK70F12)
	#define USB_DEVICE_ASSERT_RESUME()		USB0_CTL |= USB_CTL_RESUME_MASK;
	#define USB_DEVICE_DEASSERT_RESUME()	USB0_CTL &= ~USB_CTL_RESUME_MASK;
#elif (defined _MC9S08JE128_H) || (defined _MC9S08JM16_H) || defined(_MC9S08JM60_H) || (defined _MC9S08JS16_H) || (defined _MC9S08MM128_H)
	#define USB_DEVICE_ASSERT_RESUME()		CTL_CRESUME = 1;
	#define USB_DEVICE_DEASSERT_RESUME()	CTL_CRESUME = 0;
#elif (defined _MCF51JE256_H) || (defined MCU_mcf51jf128) || defined(_MCF51MM256_H)
	#define USB_DEVICE_ASSERT_RESUME()		USBTRC0_USBRESMEN = 1;
	#define USB_DEVICE_DEASSERT_RESUME()	USBTRC0_USBRESMEN = 0;
#elif (defined __MCF52221_H__) || (defined __MCF52259_H__)
	#define USB_DEVICE_ASSERT_RESUME()		CTL |= MCF_USB_OTG_CTL_RESUME;
	#define USB_DEVICE_DEASSERT_RESUME()	CTL &= ~MCF_USB_OTG_CTL_RESUME;
#endif

#define USB_PROCESS_PENDING()               ((gu8ProcessPendingFlag != 0) || (gtUSBEPEventFlags != 0))


/******************************************************************************
 * Types
 *****************************************************************************/
typedef void _PTR_ _usb_device_handle;
typedef uint_8   T_EP_BITFIELD;

#if !(defined _MC9S08JE128_H) && !(defined _MC9S08JM16_H) && !defined(_MC9S08JM60_H) && !(defined _MC9S08JS16_H) && !(defined _MC9S08MM128_H)
#pragma pack	(1)  		/* Enforce 1 byte struct alignment */
#endif

#ifdef __MK_xxx_H__
	#if (defined(__CWCC__) || defined(__GNUC__))		
    	#define ALIGN  __attribute__ ((packed))		
	#elif((defined  __IAR_SYSTEMS_ICC__) || (defined __CC_ARM))		
		#define ALIGN
    #else
        #define ALIGN
	#endif
#else    
	#define ALIGN
#endif

typedef struct _USB_DEV_EVENT_STRUCT
{
	uint_8          controller_ID;      /* controller ID           */
	uint_8          ep_num;
	boolean         setup;              /* is setup packet         */
	boolean         direction;          /* direction of endpoint   */
	uint_8*         buffer_ptr;         /* pointer to buffer       */
	uint_8          errors;             /* Any errors              */
	USB_PACKET_SIZE len;                /* buffer size of endpoint */	
}ALIGN USB_DEV_EVENT_STRUCT, *PTR_USB_DEV_EVENT_STRUCT;

// Same endpoint can have multiple function assignments in g_usb_CB, depending on user input
#ifndef MULTIPLE_DEVICES
	typedef void(_CODE_PTR_ const USB_SERVICE_CALLBACK)(PTR_USB_DEV_EVENT_STRUCT);
#else
	typedef void(_CODE_PTR_ USB_SERVICE_CALLBACK)(PTR_USB_DEV_EVENT_STRUCT);
#endif

typedef struct _USB_EP_STRUCT
{
	uint_8          ep_num;      /* endpoint number         */
	uint_8          type;        /* type of endpoint        */
	uint_8          direction;   /* direction of endpoint   */
    USB_PACKET_SIZE	size ALIGN;  /* buffer size of endpoint */
}ALIGN USB_EP_STRUCT, *USB_EP_STRUCT_PTR;

#if (defined(__CWCC__)||defined(__GNUC__))
	#pragma options align = reset
#elif defined(__IAR_SYSTEMS_ICC__) || defined(__CC_ARM)
	#pragma pack()
#endif


extern volatile uint_8 gu8ProcessPendingFlag;
extern volatile T_EP_BITFIELD gtUSBEPEventFlags;

/******************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 _usb_device_init (
		uint_8                      device_number,
		_usb_device_handle _PTR_    handle,
		uint_8                      number_of_endpoints,
		uint_8    					bVregEn
);

extern uint_8 _usb_device_deinit(void);

extern uint_8 _usb_device_init_endpoint(
		_usb_device_handle      handle,
		uint_8                  endpoint_number,
		uint_16                 max_packet_size,
		uint_8                  direction,
		uint_8                  endpoint_type,
		uint_8                  flag
);

extern uint_8 _usb_device_cancel_transfer (
		_usb_device_handle      handle,
		uint_8                  endpoint_number,
		uint_8                  direction
);

extern uint_8 _usb_device_deinit_endpoint (
		_usb_device_handle      handle,
		uint_8                  endpoint_number,
		uint_8                  direction
);

extern uint_8 _usb_device_recv_data (
		_usb_device_handle      handle,
		uint_8                  endpoint_number,
		uchar_ptr               buffer_ptr,
		uint_32                 size
);

extern uint_8 _usb_device_send_data (
		_usb_device_handle      handle,
		uint_8                  endpoint_number,
		uchar_ptr               buffer_ptr,
		uint_32                 size
);

extern uint_8 _usb_device_get_send_buffer (
    uint_8           controller_ID, /* [IN] Controller ID */
    uint_8           ep_num,        /* [IN] Endpoint number */
    uint_8_ptr       *buff_ptr,     /* [OUT] Buffer for IN endpoint */
    USB_PACKET_SIZE  *size          /* [OUT] Size of IN endpoint */
);

extern void _usb_device_shutdown (
		_usb_device_handle      handle
);

extern void _usb_device_stall_endpoint (
		_usb_device_handle      handle,
		uint_8                  endpoint_number,
		uint_8                  direction
);

extern void _usb_device_unstall_endpoint (
		_usb_device_handle      handle,
		uint_8                  endpoint_number,
		uint_8                  direction
);

extern void _usb_device_read_setup_data (
		_usb_device_handle      handle,
		uint_8                  endpoint_number,
		uint_8_ptr              buffer_ptr
);

extern uint_8 _usb_device_get_status (
		_usb_device_handle      handle,
		uint_8                  component,
		uint_8_ptr              status
);

extern uint_8 _usb_device_set_status (
		_usb_device_handle      handle,
		uint_8                  component,
		uint_8                  setting
);

extern void _usb_device_assert_resume (
		_usb_device_handle      handle
);

extern uint_8 _usb_device_register_service (
		uint_8                  controller_ID,
		uint_8                  type,
		USB_SERVICE_CALLBACK    service
);

extern uint_8 _usb_device_unregister_service (
		_usb_device_handle      handle,
		uint_8                  event_endpoint
);

extern uint_8 _usb_device_get_transfer_status (
		_usb_device_handle      handle,
		uint_8                  endpoint_number,
		uint_8                  direction
);

extern void  _usb_device_set_address (
		_usb_device_handle      handle,
		uint_8                  address
);

extern uint_8 USB_Device_Call_Service(
		uint_8                      type,
		PTR_USB_DEV_EVENT_STRUCT    event
);

extern void USB_Engine(void);

#endif
