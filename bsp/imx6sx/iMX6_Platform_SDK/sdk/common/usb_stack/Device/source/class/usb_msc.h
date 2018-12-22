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
 * @file usb_msc.h
 *
 * @author 
 *
 * @version 
 *
 * @date May-08-2009
 *
 * @brief The file contains USB stack MSC class layer api header function.
 *
 *****************************************************************************/

#ifndef _USB_MSC_H
#define _USB_MSC_H 1

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "usb_devapi.h"  
#include "usb_descriptor.h" 
#include "usb_class.h"
#include "usb_framework.h"
#ifdef COMPOSITE_DEV
#include "usb_composite.h"
#endif

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define COMPONENT_PREPARE_SHIFT             (0x07)

#define USB_MSC_DEVICE_READ_REQUEST		(0x81)
#define USB_MSC_DEVICE_WRITE_REQUEST    (0x82) 
#define USB_MSC_DEVICE_FORMAT_COMPLETE  (0x83)
#define USB_MSC_DEVICE_REMOVAL_REQUEST  (0x84)
#define USB_MSC_DEVICE_GET_INFO			(0x85)
#define USB_MSC_START_STOP_EJECT_MEDIA  (0x86) 

/* Class specific request Codes */
#define BULK_ONLY_MASS_STORAGE_RESET          (0xFF)
#define GET_MAX_LUN                           (0xFE)
#define PUT_REQUESTS                          (0xFD)
#define GET_REQUESTS                          (0xFC)

/* Events to the Application */ /* 0 to 4 are reserved for class events */

/* other macros */
#if (defined LITTLE_ENDIAN)
#define  USB_DCBWSIGNATURE       (0x43425355) /*little endian : 0x43425355 */
#define  USB_DCSWSIGNATURE       (0x53425355) /*little endian : 0x53425355 */
#else
#define  USB_DCBWSIGNATURE       (0x55534243) /*big endian : 0x55534243 */
#define  USB_DCSWSIGNATURE       (0x55534253) /*big endian : 0x55534253 */
#endif

#define  USB_CBW_DIRECTION_BIT   (0x80)
#define  USB_CBW_DIRECTION_SHIFT (7)
#define  MSC_CBW_LENGTH          (31)
#define  MSC_CSW_LENGTH          (13)

#define  MSC_RECV_DATA_BUFF_SIZE		 (MSD_RECEIVE_BUFFER_SIZE)
#define  MSC_SEND_DATA_BUFF_SIZE		 (MSD_SEND_BUFFER_SIZE)

#define COMMAND_PASSED                (0x00)
#define COMMAND_FAILED                (0x01)
#define PHASE_ERROR                   (0x02)
/* macros for queuing */
 #define MAX_QUEUE_ELEMS  (4)

/* MACROS FOR COMMANDS SUPPORTED */
 #define INQUIRY_COMMAND                    (0x12)
 #define READ_10_COMMAND                    (0x28)
 #define READ_12_COMMAND                    (0xA8)
 #define REQUEST_SENSE_COMMAND              (0x03)
 #define TEST_UNIT_READY_COMMAND            (0x00)
 #define WRITE_10_COMMAND                   (0x2A)
 #define WRITE_12_COMMAND                   (0xAA)
 #define PREVENT_ALLOW_MEDIUM_REM_COMMAND   (0x1E)
 #define FORMAT_UNIT_COMMAND                (0x04)
 #define READ_CAPACITY_10_COMMAND           (0x25)
 #define READ_FORMAT_CAPACITIES_COMMAND     (0x23)
 #define MODE_SENSE_10_COMMAND              (0x5A) 
 #define MODE_SENSE_6_COMMAND               (0x1A)
 #define MODE_SELECT_10_COMMAND             (0x55)
 #define MODE_SELECT_6_COMMAND              (0x15)
 #define SEND_DIAGNOSTIC_COMMAND            (0x1D)
 #define VERIFY_COMMAND                     (0x2F)
 #define START_STOP_UNIT_COMMAND            (0x1B)
/*****************************************************************************
 * Local Functions
 *****************************************************************************/
void USB_Service_Bulk_In(PTR_USB_DEV_EVENT_STRUCT event);
void USB_Service_Bulk_Out(PTR_USB_DEV_EVENT_STRUCT event);

void USB_Class_MSC_Event(uint_8 controller_ID, uint_8 event, void* val);
/******************************************************************************
 * Types
 *****************************************************************************/
#ifndef __HIWARE__
#pragma pack(1)
#endif

/* structure to hold a request in the endpoint queue */
typedef struct _usb_class_msc_queue 
{
    uint_8 controller_ID;
    uint_8 channel;       
    APP_DATA_STRUCT app_data;  
}USB_CLASS_MSC_QUEUE, *PTR_USB_CLASS_MSC_QUEUE;
 
/* USB class msc endpoint data */
typedef struct _usb_class_msc_endpoint 
{
    uint_8 endpoint; /* endpoint num */                    
    uint_8 type;     /* type of endpoint (interrupt, bulk or isochronous) */   
    uint_8 bin_consumer;/* the num of queued elements */
    uint_8 bin_producer;/* the num of de-queued elements */
    USB_CLASS_MSC_QUEUE queue[MAX_QUEUE_ELEMS]; /* queue data */  
}USB_CLASS_MSC_ENDPOINT;

typedef struct _usb_msc_cbw   /* Command Block Wrapper -- 31 bytes */
{
    uint_32 signature;        /*0-3  : dCBWSignature*/
    uint_32 tag;              /*4-7  : dCBWTag*/
    uint_32 data_length;      /*8-11 : dCBWDataTransferLength*/
    uint_8  flag;             /*12   : bmCBWFlags*/
    uint_8  lun;              /*13   : bCBWLUN(bits 3 to 0)*/
    uint_8  cb_length;        /*14   : bCBWCBLength*/
    uint_8  command_block[16];/*15-30 : CBWCB*/
}CBW, *PTR_CBW ;

typedef struct _usb_msc_csw   /* Command Status Wrapper -- 13 bytes */
{
    uint_32 signature; /*0-3  : dCSWSignature*/
    uint_32 tag;       /*4-7 : dCSWTag*/
    uint_32 residue;   /*8-11 : dCSWDataResidue*/
    uint_8 csw_status; /*12 : bCSWStatus*/
}CSW, *PTR_CSW;

typedef struct _lba_info_struct
{
    uint_32 starting_lba;/* LBA to start transfering with */
    uint_32 lba_transfer_num;/* number of LBAs to transfer */    
}LBA_INFO_STRUCT, * PTR_LBA_INFO_STRUCT;

typedef struct _lba_app_struct
{
	uint_32 offset;
	uint_32 size;
	uint_8_ptr buff_ptr;
}LBA_APP_STRUCT, * PTR_LBA_APP_STRUCT;

typedef struct _device_lba_info_struct
{
 	uint_32 total_lba_device_supports;/* lba : LOGICAL BLOCK ADDRESS */ 
 	uint_32 length_of_each_lba_of_device;
 	uint_8 num_lun_supported; 
}DEVICE_LBA_INFO_STRUCT, * PTR_DEVICE_LBA_INFO_STRUCT;

typedef struct _msc_thirteen_case_check
{
	uint_8 controller_ID;
	uint_32 host_expected_data_len;
	uint_8 host_expected_direction;
	uint_32 device_expected_data_len;
	uint_8 device_expected_direction;
        uint_8_ptr csw_status_ptr;
        uint_32_ptr csw_residue_ptr;
        uint_8_ptr buffer_ptr;
        boolean lba_txrx_select;
        LBA_INFO_STRUCT lba_info;
}MSC_THIRTEEN_CASE_STRUCT, *PTR_MSC_THIRTEEN_CASE_STRUCT;

typedef struct _msc_variable_struct
{
 	USB_CLASS_CALLBACK msc_callback;
 	USB_REQ_FUNC       vendor_callback;            
 	USB_CLASS_CALLBACK param_callback; 
 	uint_8 msc_lba_send_buff[MSC_SEND_DATA_BUFF_SIZE];
 	uint_8 msc_lba_recv_buff[MSC_RECV_DATA_BUFF_SIZE];
 	 /* contains the endpoint info */
#ifndef COMPOSITE_DEV
 	USB_CLASS_MSC_ENDPOINT ep[MSC_DESC_ENDPOINT_COUNT];
#else
 	USB_CLASS_MSC_ENDPOINT ep[COMPOSITE_DESC_ENDPOINT_COUNT];
#endif
 	 /* macro configuired by user*/
 	 /* LUN can have value only from 0 to 15 decimal */
 	uint_8 lun; 	
 	/* flag to track bulk out data processing after CBW if needed*/
 	boolean out_flag; 
 	/* flag to track bulk in data processing before CSW if needed*/
 	boolean in_flag; 
 	/* flag to track if there is need to stall BULK IN ENDPOINT 
 	   because of BULK COMMAND*/
 	boolean in_stall_flag; 
 	/* flag to track if there is need to stall BULK OUT ENDPOINT
 	   because of BULK COMMAND */
 	boolean out_stall_flag; 
 	/* flag to validate CBW */
 	boolean cbw_valid_flag;  	
 	boolean re_stall_flag;
 	DEVICE_LBA_INFO_STRUCT device_info;
 	/* global structure for command block wrapper */
 	CBW cbw_struct;        
 	/* global structure for command status wrapper */
 	CSW csw_struct;                     
}MSC_GLOBAL_VARIABLE_STRUCT, * PTR_MSC_GLOBAL_VARIABLE_STRUCT; 

#if defined(__CWCC__)
#pragma options align=reset
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma pack()
#endif
/******************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 USB_Class_MSC_Init
(
    uint_8                  controller_ID,
    USB_CLASS_CALLBACK      msc_class_callback,
    USB_REQ_FUNC            vendor_req_callback,
    USB_CLASS_CALLBACK      param_callback
);

extern void USB_Class_MSC_Event (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event,           /* [IN] Event Type */
    void* val               /* [IN] Pointer to configuration Value */   
);

#ifdef COMPOSITE_DEV
extern uint_8 USB_MSC_Other_Requests(uint_8 controller_ID,
						  USB_SETUP_STRUCT * setup_packet, 
              uint_8_ptr *data, 
              uint_32 *size);
#endif

extern uint_8 USB_Class_MSC_DeInit 
(
    uint_8 controller_ID             
);

extern uint_8 USB_MSC_SCSI_Init
(
    uint_8 controller_ID, 
    USB_CLASS_CALLBACK callback
);

extern uint_8 USB_MSC_LBA_Transfer
(
	uint_8 controller_ID,
	boolean direction,
	PTR_LBA_INFO_STRUCT lba_info_ptr
);

extern uint_8 USB_Class_MSC_Send_Data
(
    uint_8              controller_ID,
    uint_8              ep_num,
    uint_8_ptr          buff_ptr,      /* [IN] buffer to send */      
    uint_32             size           /* [IN] length of the transfer */
);

#define USB_MSC_Bulk_Send_Data(a,b,c)  USB_Class_MSC_Send_Data(a,BULK_IN_ENDPOINT,b,c)
#define USB_MSC_Bulk_Recv_Data(a,b,c)  _usb_device_recv_data(a,BULK_OUT_ENDPOINT,b,c)

#define USB_MSC_Periodic_Task USB_Class_Periodic_Task 

/* Sub Class Functions */
extern uint_8 msc_inquiry_command (uint_8 controller_ID,
								                   PTR_CBW cbw_ptr, 
                                   uint_32* csw_residue_ptr, 
                                   uint_8* csw_status_ptr);

extern uint_8 msc_read_command (uint_8 controller_ID,
								                PTR_CBW cbw_ptr, 
                                uint_32* csw_residue_ptr, 
                                uint_8* csw_status_ptr); 
                                                                   
extern uint_8 msc_request_sense_command(uint_8 controller_ID,
										                    PTR_CBW cbw_ptr, 
                                        uint_32* csw_residue_ptr, 
                                        uint_8* csw_status_ptr); 
                                                                   
extern uint_8 msc_test_unit_ready_command(uint_8 controller_ID,
										                      PTR_CBW cbw_ptr, 
                                          uint_32* csw_residue_ptr, 
                                          uint_8* csw_status_ptr); 

extern uint_8 msc_verify_command(uint_8 controller_ID,
								                  PTR_CBW cbw_ptr,
                                 uint_32* csw_residue_ptr,
                                 uint_8* csw_status_ptr);                                         
                                                                   
extern uint_8 msc_mode_sense_command(uint_8 controller_ID,
									                    PTR_CBW cbw_ptr, 
                                     uint_32* csw_residue_ptr, 
                                     uint_8* csw_status_ptr);

extern uint_8 msc_mode_select_command(uint_8 controller_ID,
									                    PTR_CBW cbw_ptr, 
                                      uint_32* csw_residue_ptr, 
                                      uint_8* csw_status_ptr);                                     
                                                                   
extern uint_8 msc_read_capacity_command(uint_8 controller_ID,
										                    PTR_CBW cbw_ptr, 
                                        uint_32* csw_residue_ptr, 
                                        uint_8* csw_status_ptr); 
                                                                                                                                      
extern uint_8 msc_format_unit_command(uint_8 controller_ID,
									                    PTR_CBW cbw_ptr, 
                                      uint_32* csw_residue_ptr, 
                                      uint_8* csw_status_ptr); 
                                                                                                                                      
extern uint_8 msc_write_command (uint_8 controller_ID,
								                 PTR_CBW cbw_ptr, 
                                 uint_32* csw_residue_ptr, 
                                 uint_8* csw_status_ptr); 
                                                                                                                                      
extern uint_8 msc_prevent_allow_medium_removal(uint_8 controller_ID,
											                          PTR_CBW cbw_ptr, 
                                               uint_32* csw_residue_ptr, 
                                               uint_8* csw_status_ptr); 

extern uint_8 msc_read_format_capacity_command(uint_8 controller_ID,
											                          PTR_CBW cbw_ptr, 
                                               uint_32* csw_residue_ptr, 
                                               uint_8* csw_status_ptr);  

extern uint_8 msc_send_diagnostic_command(uint_8 controller_ID,
										                      PTR_CBW cbw_ptr, 
                                          uint_32* csw_residue_ptr, 
                                          uint_8* csw_status_ptr);                                             

extern uint_8 msc_start_stop_unit_command(uint_8 controller_ID,
										                      PTR_CBW cbw_ptr, 
                                          uint_32* csw_residue_ptr, 
                                          uint_8* csw_status_ptr);                                             
                                                                   
extern uint_8 msc_unsupported_command(uint_8 controller_ID,
									  PTR_CBW cbw_ptr, 
                                      uint_32* csw_residue_ptr, 
                                      uint_8* csw_status_ptr);
extern void USB_BYTE_SWAP4(uint_32 a, uint_32* b);
extern void USB_memzero(void* ptr, uint_32 size); 
extern void USB_memcopy(void* src, void* dst, uint_32 size);

#endif

/* EOF */      
