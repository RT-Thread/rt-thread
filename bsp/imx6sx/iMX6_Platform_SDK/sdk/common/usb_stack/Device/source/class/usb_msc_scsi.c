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
 * @file usb_msc_scsi.c
 *
 * @author
 *
 * @version
 *
 * @date May-08-2009
 *
 * @brief The file contains USB Mass Storage SCSI command set.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
 #include "usb_msc_scsi.h"
#if (defined MCU_MKL25Z4)
#include "string.h"
#endif

#if (defined __MCF52xxx_H__)||(defined LITTLE_ENDIAN)
/* Put CFV2 descriptors in RAM */
#define USB_DESC_CONST
#else
#define USB_DESC_CONST	const
#endif

 /*****************************************************************************
 * Constant and Macro's
 *****************************************************************************/
 USB_DESC_CONST INQUIRY_DATA_STRUCT inquiry_info =
 {
    (PERIPHERAL_QUALIFIER<<PERIPHERAL_QUALIFIER_SHIFT)|PERIPHERAL_DEVICE_TYPE,
    (uint_8)REMOVABLE_MEDIUM_BIT<<REMOVABLE_MEDIUM_BIT_SHIFT,
    SPC_VERSION, 0x02,ADDITIONAL_LENGTH,0x00,0x00,0x00,
    {'F', 'S', 'L', ' ', ' ', ' ', ' ',' '},
    {'F','R','E','E','S','C','A','L','E',' ','M','S','D',' ',' ',' '},
    {'0', '0', '0', '1'}
};

USB_DESC_CONST MODE_PARAMETER_HEADER_STRUCT mode_param_header =
    {
      0x0000,/*no following data available because of reason given below*/
      0x00,/* 0x00 indicates current/default medium */
      0x00,/* for write_protect and DPOFUA - no write protection available*/
      0x00,0x00,0x00,0x00 /* reserved bytes are always to be set to zero */
    };

static uint_8 response_data_array[192];
/* max required size is 192, though host seldom calls for this much data*/
/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
/****************************************************************************
 * Global Variables
 ****************************************************************************/
/* Add all the variables needed for usb_msc.c to this structure */
MSC_SCSI_GLOBAL_VARIABLE_STRUCT g_msc_scsi;
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
 uint_8 msc_thirteen_cases_check(PTR_MSC_THIRTEEN_CASE_STRUCT msc_check_event);
/*****************************************************************************
 * Local Variables
 *****************************************************************************/

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/**************************************************************************//*!
 *
 * @name  msc_thirteen_cases_check
 *
 * @brief The function checks for thirteen error case of MSC and takes action 
 *        appropriately
 *
 * @param msc_check_event: structure containing all necessary parameter to 
 *        evaluate error scenarios
 *
 * @return error
 *                 
 *****************************************************************************/
uint_8 msc_thirteen_cases_check(PTR_MSC_THIRTEEN_CASE_STRUCT msc_check_event)
{
	uint_8 error;
#if (defined MCU_MKL25Z4)
	uint_32 csw_residue;
#endif
    if(!msc_check_event->host_expected_data_len)
	{	/* host expects no data transfer */
	/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
		memset(msc_check_event->csw_residue_ptr, 0, 4); /* set the value to 0 */
#else
		*(msc_check_event->csw_residue_ptr) = 0;
#endif
		if(!msc_check_event->device_expected_data_len)
		{	/* CASE 1: Device intends no data transfer : Thin Diagonal Case*/
			*(msc_check_event->csw_status_ptr) = COMMAND_PASSED;
		}
		else 
		{	/* if(msc_check_event->device_expected_direction) :
		       	CASE 2: Device intends to send data to host
		       else
		     	CASE 3: Device intends to receive data from host */        
			*(msc_check_event->csw_status_ptr) = PHASE_ERROR;
		}		
	}
	else if(msc_check_event->host_expected_direction)
	{	/* host expects to receive data from device (USB_SEND direction)*/
		if(!msc_check_event->device_expected_data_len)
		{	/* CASE 4:  Device intends no data transfer */
		/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
			csw_residue = msc_check_event->host_expected_data_len - 
					msc_check_event->device_expected_data_len;
			memcpy((uint_8 *)msc_check_event->csw_residue_ptr,(uint_8*)&csw_residue, 4);
#else
				*(msc_check_event->csw_residue_ptr) = 
				msc_check_event->host_expected_data_len - 
				msc_check_event->device_expected_data_len;
#endif
			/* sending zero bytes of data */
			error = USB_MSC_Bulk_Send_Data(msc_check_event->controller_ID,
				msc_check_event->buffer_ptr,
				msc_check_event->device_expected_data_len);	
			
			if(error == USB_OK)
			{
				*(msc_check_event->csw_status_ptr) = COMMAND_PASSED;	
			}
			else
			{
				*(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
		        g_msc_scsi.request_sense.sense_key = MEDIUM_ERROR;
		        g_msc_scsi.request_sense.add_sense_code = UNRECOVERED_READ_ERROR;
			}
			
			/* BULK IN PIPE TO BE STALLED for status phase */
			error = USBERR_ENDPOINT_STALLED;	
		}
		else if(msc_check_event->device_expected_direction)
		{	/* device intends to send data to host */
			if(msc_check_event->host_expected_data_len > 
				msc_check_event->device_expected_data_len)
			{	/* CASE 5: Host intends more data to receive than device 
						   intends to send*/
			/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
				csw_residue = msc_check_event->host_expected_data_len - 
									msc_check_event->device_expected_data_len;
				memcpy((uint_8 *)msc_check_event->csw_residue_ptr,(uint_8*)&csw_residue, 4);
#else
				*(msc_check_event->csw_residue_ptr) = 
				msc_check_event->host_expected_data_len - 
				msc_check_event->device_expected_data_len;
#endif
				if(g_msc_scsi.thirteen_case_struct.lba_txrx_select == TRUE)	
				{
					error = USB_MSC_LBA_Transfer(msc_check_event->controller_ID,USB_SEND,
						&msc_check_event->lba_info);
				}
				else
				{
					error = USB_MSC_Bulk_Send_Data(msc_check_event->controller_ID,
						msc_check_event->buffer_ptr,
						msc_check_event->device_expected_data_len);	
				}

				if(msc_check_event->device_expected_data_len% 
					BULK_IN_ENDP_PACKET_SIZE == 0)
				{   /*need to send zero bytes of data to tell host that 
				      device does not have any more data. This is needed
				      only if the bytes send to host are integral multiple
				      of max packet size of Bulk In endpoint */
					error |= USB_MSC_Bulk_Send_Data(msc_check_event->controller_ID,
						msc_check_event->buffer_ptr,0);									
				}
				
				
				if(error == USB_OK)
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_PASSED;	
				}
				else
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
			        g_msc_scsi.request_sense.sense_key = MEDIUM_ERROR;
			        g_msc_scsi.request_sense.add_sense_code = UNRECOVERED_READ_ERROR;
				}
			}
			else if(msc_check_event->host_expected_data_len == 
				msc_check_event->device_expected_data_len)
			{	/* CASE 6: Host intends exact amount of data to receive 
			               as device intends to send : Thin Diagonal Case*/
			/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
				memset(msc_check_event->csw_residue_ptr, 0, 4); 
#else
				*(msc_check_event->csw_residue_ptr) = 0;
#endif

				if(g_msc_scsi.thirteen_case_struct.lba_txrx_select == TRUE)	
				{
					error = USB_MSC_LBA_Transfer(msc_check_event->controller_ID,USB_SEND,
						&msc_check_event->lba_info);
				}
				else
				{
					error = USB_MSC_Bulk_Send_Data(msc_check_event->controller_ID,
						msc_check_event->buffer_ptr,
						msc_check_event->device_expected_data_len);						
				}

				if(error == USB_OK)
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_PASSED;	
				}
				else
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
			        g_msc_scsi.request_sense.sense_key = MEDIUM_ERROR;
			        g_msc_scsi.request_sense.add_sense_code = UNRECOVERED_READ_ERROR;
				}
			}
			else
			{
				/* CASE 7: Host intends less data to receive than device 
						   intends to send*/
				/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
				memset(msc_check_event->csw_residue_ptr, 0, 4); 
#else
				*(msc_check_event->csw_residue_ptr) = 0;
#endif
				
				if(g_msc_scsi.thirteen_case_struct.lba_txrx_select == TRUE)	
				{
					error = USB_MSC_LBA_Transfer(msc_check_event->controller_ID,USB_SEND,
						&msc_check_event->lba_info);
				}
				else
				{
					error = USB_MSC_Bulk_Send_Data(msc_check_event->controller_ID,
						msc_check_event->buffer_ptr,
						msc_check_event->host_expected_data_len);					
				}
				
				if(error == USB_OK)
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_PASSED;	
				}
				else
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
			        g_msc_scsi.request_sense.sense_key = MEDIUM_ERROR;
			        g_msc_scsi.request_sense.add_sense_code = UNRECOVERED_READ_ERROR;
				}
			}								
		}
		else
		{	/* CASE 8: Device intends to receive data from host */
		/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
			csw_residue = msc_check_event->host_expected_data_len;
			memcpy((uint_8 *)msc_check_event->csw_residue_ptr,(uint_8*)&csw_residue, 4); 
#else
				*(msc_check_event->csw_residue_ptr) = 
				msc_check_event->host_expected_data_len;
#endif
			/* device has no data to send */
			error = USB_MSC_Bulk_Send_Data(msc_check_event->controller_ID,
				msc_check_event->buffer_ptr,0);
			*(msc_check_event->csw_status_ptr) = PHASE_ERROR;
			/* BULK IN PIPE TO BE STALLED for status phase */
			error = USBERR_ENDPOINT_STALLED;																			   
		}
	}
	else
	{	/* host expects to send data to device (USB_RECV direction)*/
		if(!msc_check_event->device_expected_data_len)
		{	/* CASE 9:  Device intends no data transfer */
	    uint_8 component = BULK_OUT_ENDPOINT | 
	        	(USB_RECV<<COMPONENT_PREPARE_SHIFT);	        
			(void)_usb_device_set_status(&(msc_check_event->controller_ID),
				(uint_8)(component|USB_STATUS_ENDPOINT),
				(uint_16)USB_STATUS_STALLED);
				/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
			csw_residue = msc_check_event->host_expected_data_len;
			memcpy((uint_8 *)msc_check_event->csw_residue_ptr,(uint_8*)&csw_residue, 4); 
#else
				*(msc_check_event->csw_residue_ptr) = 
				msc_check_event->host_expected_data_len;
#endif
			*(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
			/* BULK OUT PIPE STALLED */
			error = USBERR_ENDPOINT_STALLED;					
		}
		else if(msc_check_event->device_expected_direction)
		{	/*CASE10: device intends to send data to host */		
	       	uint_8 component = BULK_OUT_ENDPOINT | 
        		(USB_RECV<<COMPONENT_PREPARE_SHIFT);
	       	/* now, stalling the status phase - CASE 5th of THIRTEEN CASES*/           
			(void)_usb_device_set_status(&(msc_check_event->controller_ID),
				(uint_8)(component|USB_STATUS_ENDPOINT),
				(uint_16)USB_STATUS_STALLED);
				/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
			csw_residue = msc_check_event->host_expected_data_len;
			memcpy((uint_8 *)msc_check_event->csw_residue_ptr,(uint_8*)&csw_residue, 4); 
#else
				*(msc_check_event->csw_residue_ptr) = 
				msc_check_event->host_expected_data_len;
#endif
			*(msc_check_event->csw_status_ptr) = PHASE_ERROR;
			/* BULK OUT PIPE STALLED */
			error = USBERR_ENDPOINT_STALLED;
		}
		else
		{	/*Device intends to receive data from host */
			if(msc_check_event->host_expected_data_len > 
				msc_check_event->device_expected_data_len)
			{	/* CASE 11: Host intends more data to send than device 
						    intends to receive*/
			/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
			csw_residue = msc_check_event->host_expected_data_len 
						- msc_check_event->device_expected_data_len;
			memcpy((uint_8 *)msc_check_event->csw_residue_ptr,(uint_8*)&csw_residue, 4);
#else
					*(msc_check_event->csw_residue_ptr) = 
					msc_check_event->host_expected_data_len - 
					msc_check_event->device_expected_data_len;
#endif
				
				if(g_msc_scsi.thirteen_case_struct.lba_txrx_select == TRUE)	
				{
					error = USB_MSC_LBA_Transfer(msc_check_event->controller_ID,USB_RECV,
						&msc_check_event->lba_info);
				}
				else
				{
					error = USB_MSC_Bulk_Recv_Data(&(msc_check_event->controller_ID),
						msc_check_event->buffer_ptr,
						msc_check_event->device_expected_data_len);										
				}				
				
				if(error == USB_OK)
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_PASSED;	
				}
				else
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
			        g_msc_scsi.request_sense.sense_key = MEDIUM_ERROR;
			        g_msc_scsi.request_sense.add_sense_code = WRITE_FAULT;
				}
				/* BULK OUT PIPE TO BE STALLED for status phase */
				error = USBERR_ENDPOINT_STALLED;					
			}
			else if(msc_check_event->host_expected_data_len == 
				msc_check_event->device_expected_data_len)
			{	/* CASE 12: Host intends exact amount of data to send 
			                as device intends to receive : Thin Diagonal Case*/
			/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
				memset(msc_check_event->csw_residue_ptr, 0, 4); 	
#else
				*(msc_check_event->csw_residue_ptr) = 0;
#endif				
				

				if(g_msc_scsi.thirteen_case_struct.lba_txrx_select == TRUE)	
				{
					error = USB_MSC_LBA_Transfer(msc_check_event->controller_ID,USB_RECV,
						&msc_check_event->lba_info);
				}
				else
				{
					error = USB_MSC_Bulk_Recv_Data(&(msc_check_event->controller_ID),
						msc_check_event->buffer_ptr,
						msc_check_event->device_expected_data_len);	
				}
				
				if(error == USB_OK)
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_PASSED;	
				}
				else
				{
					*(msc_check_event->csw_status_ptr) = COMMAND_FAILED;
			        g_msc_scsi.request_sense.sense_key = MEDIUM_ERROR;
			        g_msc_scsi.request_sense.add_sense_code = WRITE_FAULT;
				}
			}
			else
			{
				/* CASE 13: Host intends less data to send than device 
						    intends to receive*/
				/* for platforms don't support writing more than 1 byte to memory not aligned */
#if (defined MCU_MKL25Z4)
				memset(msc_check_event->csw_residue_ptr, 0, 4); 	
#else
				*(msc_check_event->csw_residue_ptr) = 0;
#endif	
				
				if(g_msc_scsi.thirteen_case_struct.lba_txrx_select == TRUE)	
				{
					msc_check_event->lba_info.lba_transfer_num = 
					  msc_check_event->host_expected_data_len / 
					    g_msc_scsi.device_info.length_of_each_lba_of_device;   
					error = USB_MSC_LBA_Transfer(msc_check_event->controller_ID,USB_RECV,
						&msc_check_event->lba_info);
				}
				else
				{
					error = USB_MSC_Bulk_Recv_Data(&(msc_check_event->controller_ID),
						msc_check_event->buffer_ptr,
						msc_check_event->host_expected_data_len);
				}
				if(error != USB_OK)
				{
			        g_msc_scsi.request_sense.sense_key = MEDIUM_ERROR;
			        g_msc_scsi.request_sense.add_sense_code = WRITE_FAULT;
				}
				*(msc_check_event->csw_status_ptr) = PHASE_ERROR;						    
			}								
		}		
	}
	return error;
}

/*****************************************************************************
 * Global Functions
 *****************************************************************************/

/**************************************************************************//*!
 *
 * @name  USB_MSC_SCSI_Init
 *
 * @brief The funtion initializes the SCSI parameters and callbacks
 *
 * @param controller_ID:        To identify the controller :       
 * @param class_callback:       event callback
 *
 * @return status
 *         USB_OK           : When Successfull
 *         Others           : Errors
 *
 *****************************************************************************/
uint_8 USB_MSC_SCSI_Init
(
     uint_8  controller_ID,
     USB_CLASS_CALLBACK callback
)
{
    UNUSED(controller_ID)
    /* initialize the Global Variable Structure */
	USB_memzero(&g_msc_scsi, sizeof(MSC_SCSI_GLOBAL_VARIABLE_STRUCT));

    /* save input parameters */
    g_msc_scsi.scsi_callback = callback;

    /* no need to initialize other structure fields as g_resquest_sense has
       been declared as static */
    g_msc_scsi.request_sense.valid_error_code = REQ_SENSE_VALID_ERROR_CODE;
    g_msc_scsi.request_sense.add_sense_len = REQ_SENSE_ADDITIONAL_SENSE_LEN;
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;    
    
    if(g_msc_scsi.scsi_callback != NULL) 
    {				
		    g_msc_scsi.scsi_callback(controller_ID, USB_MSC_DEVICE_GET_INFO, 
			    &g_msc_scsi.device_info);	
    }
    
    return USB_OK;
}

/**************************************************************************//*!
 *
 * @name  msc_request_sense_command
 *
 * @brief command instructs the Device to transfer sense data to host computer
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return NONE
 *
 *****************************************************************************/
uint_8 msc_request_sense_command 
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 error; 
       
    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = REQ_SENSE_DATA_LENGTH;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = (uint_8_ptr)&g_msc_scsi.request_sense;
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;
    
    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));
    
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_inquiry_command
 *
 * @brief It requests that information regarding parameters of the Device be
 *        sent to the Host Computer
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_inquiry_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 error = USBERR_TX_FAILED;
    PTR_INQUIRY_COMMAND_STRUCT inquiry_cmd_ptr =
    	(PTR_INQUIRY_COMMAND_STRUCT)(cbw_ptr->command_block);
	
	UNUSED(inquiry_cmd_ptr)

    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;
    
    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
        (uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = INQUIRY_ALLOCATION_LENGTH;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = (uint_8_ptr)&inquiry_info;
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));
    
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_read_command
 *
 * @brief command requests that device transfer data to the host computer
 *        (read (10) command)
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_read_command 
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_32 lba = 0;
    uint_32 num_lba_tx = 0;
    uint_8 error = USBERR_TX_FAILED;

    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;
    
    lba  = ((uint_32)cbw_ptr->command_block[2] << 24);
    lba |= ((uint_32)cbw_ptr->command_block[3] << 16);
    lba |= ((uint_32)cbw_ptr->command_block[4] << 8);
    lba |= ((uint_32)cbw_ptr->command_block[5]);

    if(cbw_ptr->command_block[0] == READ_10_COMMAND)
    {
    	num_lba_tx = (uint_16)((uint_16)cbw_ptr->command_block[7] << 8);
    	num_lba_tx |= (uint_16)cbw_ptr->command_block[8];
    }
    else if(cbw_ptr->command_block[0] == READ_12_COMMAND)
    {
		num_lba_tx  = ((uint_32)cbw_ptr->command_block[6] << 24);
        num_lba_tx |= ((uint_32)cbw_ptr->command_block[7] << 16);
        num_lba_tx |= ((uint_32)cbw_ptr->command_block[8] << 8);
        num_lba_tx |= ((uint_32)cbw_ptr->command_block[9]);
    }
    
    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr; 
    
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = 
		g_msc_scsi.device_info.length_of_each_lba_of_device * num_lba_tx;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = NULL;

    g_msc_scsi.thirteen_case_struct.lba_txrx_select = TRUE;
	g_msc_scsi.thirteen_case_struct.lba_info.starting_lba = lba;
	g_msc_scsi.thirteen_case_struct.lba_info.lba_transfer_num = num_lba_tx;
	
	error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_write_command
 *
 * @brief command requests that the Device write the data transferred by the
 *        Host Computer to the medium.
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_write_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_32 lba = 0;
    uint_32 num_lba_rx = 0;
    uint_8 error = USBERR_RX_FAILED;

    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    lba  = ((uint_32)cbw_ptr->command_block[2] << 24);
    lba |= ((uint_32)cbw_ptr->command_block[3] << 16);
    lba |= ((uint_32)cbw_ptr->command_block[4] << 8);
    lba |= ((uint_32)cbw_ptr->command_block[5]);


    if(cbw_ptr->command_block[0] == WRITE_10_COMMAND)
    {
    	num_lba_rx = (uint_16)((uint_16)cbw_ptr->command_block[7] << 8);
    	num_lba_rx |= (uint_16)cbw_ptr->command_block[8];
    }
    else if(cbw_ptr->command_block[0] == WRITE_12_COMMAND)
    {
		num_lba_rx  = ((uint_32)cbw_ptr->command_block[6] << 24);
        num_lba_rx |= ((uint_32)cbw_ptr->command_block[7] << 16);
        num_lba_rx |= ((uint_32)cbw_ptr->command_block[8] << 8);
        num_lba_rx |= ((uint_32)cbw_ptr->command_block[9]);
    }
        
    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;    
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_RECV;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = NULL;

    if(_usb_device_get_transfer_status(&controller_ID,
        BULK_OUT_ENDPOINT, USB_RECV) != USB_STATUS_IDLE)
    {
        (void)_usb_device_cancel_transfer(&controller_ID,BULK_OUT_ENDPOINT,
        	USB_RECV);
    }
    
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = 
    	g_msc_scsi.device_info.length_of_each_lba_of_device * num_lba_rx;
    
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = TRUE;
	  g_msc_scsi.thirteen_case_struct.lba_info.starting_lba = lba;
	  g_msc_scsi.thirteen_case_struct.lba_info.lba_transfer_num = num_lba_rx;
	
	  error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));
    
    return error;    
}

/**************************************************************************//*!
 *
 * @name  msc_test_unit_ready_command
 *
 * @brief It provides a means to check if the device is ready
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_test_unit_ready_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 error;
    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;    
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
        (uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
	
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = 0;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = NULL;

    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));
    								      								  
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_verify_command
 *
 * @brief requests that device verifies the data on medium
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_verify_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 error;
    /* Our Device has no mechanism to verify the blocks, 
       so just returning success status to host*/
    
    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;    
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
	
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = 0;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = NULL;
    
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;

    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));
    								      								  
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_mode_sense_command
 *
 * @brief command provides a means for a Device to report parameters to Host
 *        Computer.It is a complementary command to the MODE SELECT command.
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_mode_sense_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 error = USBERR_TX_FAILED;
    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    /* irrespective of DBD(Disable block descriptor) bit in Command Block
       Wrapper we are not returning any block descriptors in the returned mode
       sense data.Presently, we are just returning Mode Parameter Header */

	  g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = sizeof(mode_param_header);
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = (uint_8_ptr)&mode_param_header;
    
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;
    
    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_mode_select_command
 *
 * @brief command provides a means for a Device to report parameters to Host
 *        Computer.It is a complementary command to the MODE SENSE command.
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_mode_select_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 error = USBERR_TX_FAILED;

    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    								  
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = sizeof(mode_param_header);
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = (uint_8_ptr)&mode_param_header;
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;
    
    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));
   
    if(cbw_ptr->command_block[1] & 0x01)/* checking Save Pages Bit in command*/
    {
    	g_msc_scsi.request_sense.sense_key = ILLEGAL_REQUEST;
        g_msc_scsi.request_sense.add_sense_code = INVALID_FIELD_IN_COMMAND_PKT;
        /*logical unit does not implement save mode pages in our case*/
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_read_capacity_command
 *
 * @brief command provides a means for the host computer to request information
 *        regarding the capacity of the installed medium of the device.
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_read_capacity_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    READ_CAPACITY_DATA_STRUCT read_capacity;
    uint_8 error = USBERR_TX_FAILED;
#if (!defined LITTLE_ENDIAN)
    read_capacity.last_logical_block_address = g_msc_scsi.device_info.total_lba_device_supports -1;
    read_capacity.block_size = (uint_32)g_msc_scsi.device_info.length_of_each_lba_of_device;
#else
    read_capacity.last_logical_block_address = BYTESWAP32(g_msc_scsi.device_info.total_lba_device_supports -1);
    read_capacity.block_size = BYTESWAP32((uint_32)g_msc_scsi.device_info.length_of_each_lba_of_device);
#endif
    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    								  
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = READ_CAPACITY_DATA_LENGTH;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = (uint_8_ptr)&read_capacity;
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;    
    
    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_read_format_capacity_command
 *
 * @brief allows the host to request a list of the possible capacities that
 *        can be formatted on the currently installed medium
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_read_format_capacity_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 i; /* general variable for counting in loop */
    uint_8 error = USBERR_TX_FAILED;
    /* size of data to be sent in data phase for this command*/
    uint_32 response_size;  
    uint_16 allocation_length = (uint_16)((cbw_ptr->command_block[7] << 8) |
    	cbw_ptr->command_block[8]);
	  uint_8_ptr response_data_ptr;/* pointer to data to be sent in data
    												  phase for this command*/
    uint_8 num_formattable_cap_desc = (uint_8)(g_msc_scsi.formatted_disk ?
    	(IMPLEMENTING_DISK_DRIVE?0x02:0x03):0x00);
    /* gives the number of Formattable Capacity Descriptor to be sent by device
    in response to read format capacities command */
    /* 0x03 is number of formattable capacity desc. for HD while for DD its 2 if
    formatted drive is there */

    CAPACITY_LIST_HEADER_STRUCT capacity_list_header = {0x00,0x00,0x00,0x00};
    											/* Initializing all fields */
    CURR_MAX_CAPACITY_DESC_STRUCT curr_max_cap_header;
    FORMATTABLE_CAP_DESC formattable_cap_descriptor;

    uint_32 desc_code = (uint_32)(g_msc_scsi.formatted_disk?FORMATTED_MEDIA:
        UNFORMATTED_MEDIA);

#if (!defined LITTLE_ENDIAN)
    formattable_cap_descriptor.num_blocks = g_msc_scsi.device_info.total_lba_device_supports;
  	formattable_cap_descriptor.block_len = g_msc_scsi.device_info.length_of_each_lba_of_device;    
#else
    formattable_cap_descriptor.num_blocks = BYTESWAP32(g_msc_scsi.device_info.total_lba_device_supports);
  	formattable_cap_descriptor.block_len = BYTESWAP32(g_msc_scsi.device_info.length_of_each_lba_of_device);
#endif
  	
    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;
    								  
    capacity_list_header.capacity_list_len = (uint_8)(num_formattable_cap_desc * 8);
#if (!defined LITTLE_ENDIAN)
    curr_max_cap_header.num_blocks = g_msc_scsi.device_info.total_lba_device_supports;
    curr_max_cap_header.desc_code_and_block_len = (desc_code << 24)| g_msc_scsi.device_info.length_of_each_lba_of_device;    
#else    
    curr_max_cap_header.num_blocks = BYTESWAP32(g_msc_scsi.device_info.total_lba_device_supports);
    curr_max_cap_header.desc_code_and_block_len = BYTESWAP32((desc_code << 24)| g_msc_scsi.device_info.length_of_each_lba_of_device);
#endif    
    response_size = sizeof(capacity_list_header) + sizeof(curr_max_cap_header)+
    	sizeof(formattable_cap_descriptor) * num_formattable_cap_desc;

    if(response_size > allocation_length)
    {   /* comparing the length of data available with allocation length value
          sent in CBW which indicates the length of buffer host has reserved
          for data phase of this command */
    	response_size = allocation_length;
    }

    /* reserving memory for response data */
    response_data_ptr = (uint_8_ptr)response_data_array;

    USB_memcopy(&capacity_list_header, response_data_ptr,
    	sizeof(capacity_list_header));
    USB_memcopy(&curr_max_cap_header, response_data_ptr +
    	sizeof(capacity_list_header),sizeof(curr_max_cap_header));

    if(g_msc_scsi.formatted_disk)
    {
    	for(i = 0; i < num_formattable_cap_desc; i++)
    	{
    		USB_memcopy(&formattable_cap_descriptor, response_data_ptr +
    			sizeof(capacity_list_header) + sizeof(curr_max_cap_header)+
    			sizeof(formattable_cap_descriptor) * i,
    			sizeof(formattable_cap_descriptor));
    	}
    }
    
    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
		(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = response_size;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = response_data_ptr;
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;    
    
    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_format_unit_command
 *
 * @brief host sends the FORMAT UNIT command to physically format a floppy disk
 *        according to selected options
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_format_unit_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 error;
    *csw_residue_ptr = 0;
    /* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;    
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = 0;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = NULL;
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;    
    
    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));
    
    if(*csw_status_ptr != PHASE_ERROR)
    {
	    /* FmtData = 1, CmpList = 0, Defect List Format = 7 */
	    if((cbw_ptr->command_block[1] & 0x1F) == 0x17)
	    {
	        *csw_status_ptr = COMMAND_PASSED;
	    }
	    else
	    {
	        *csw_status_ptr = COMMAND_FAILED;
	        g_msc_scsi.request_sense.sense_key = ILLEGAL_REQUEST;
	        g_msc_scsi.request_sense.add_sense_code = INVALID_FIELD_IN_COMMAND_PKT;
	    }    	
    }
    
    if(g_msc_scsi.scsi_callback != NULL)
    {
    	g_msc_scsi.scsi_callback(controller_ID, USB_MSC_DEVICE_FORMAT_COMPLETE, NULL);
    }
    
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_prevent_allow_medium_removal
 *
 * @brief command tells the UFI device to enable or disable the removal of the
 *        medium in the logical unit.
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_prevent_allow_medium_removal
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 error;
    uint_8 prevent_removal = 0;
    /* masking to obtain value of last bit */
    prevent_removal = (uint_8)(cbw_ptr->command_block[4] &
        PREVENT_ALLOW_REMOVAL_MASK);
	/* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);      
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = 0;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = NULL;
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;
    
    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));

    if(*csw_status_ptr != PHASE_ERROR)
    {
		  if((!SUPPORT_DISK_LOCKING_MECHANISM)&&(prevent_removal))
	    {/*there is no support for disk locking and removal of medium is disabled*/
	        g_msc_scsi.request_sense.sense_key = ILLEGAL_REQUEST;
	        g_msc_scsi.request_sense.add_sense_code = INVALID_FIELD_IN_COMMAND_PKT;
	        *csw_status_ptr = COMMAND_FAILED;
	    }
    }
    
    if(g_msc_scsi.scsi_callback != NULL)
	  {
    	g_msc_scsi.scsi_callback(controller_ID, USB_MSC_DEVICE_REMOVAL_REQUEST, 
    		&prevent_removal);
    }

    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_start_stop_unit_command
 *
 * @brief command instructs device to enable or disable media access operations
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_start_stop_unit_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    uint_8 error;
    uint_8 load_eject_start;
    /* masking to obtain value of last bit */
    load_eject_start = (uint_8)(cbw_ptr->command_block[4] &
        LOAD_EJECT_START_MASK);
	/* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);      
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = 0;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = NULL;
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;
    
    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));

    if(*csw_status_ptr != PHASE_ERROR)
    {
      if(g_msc_scsi.scsi_callback != NULL)
	    {
    	  g_msc_scsi.scsi_callback(controller_ID, USB_MSC_START_STOP_EJECT_MEDIA, 
    		  &load_eject_start);
      }
    }
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_send_diagnostic_command
 *
 * @brief requests the device to perform self test
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_send_diagnostic_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    /* No Self Test Procedure available */
    uint_8 error;
	/* initialize sense code values */
    g_msc_scsi.request_sense.sense_key = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code = NO_SENSE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    g_msc_scsi.thirteen_case_struct.controller_ID = controller_ID;
    g_msc_scsi.thirteen_case_struct.host_expected_data_len = cbw_ptr->data_length;
    g_msc_scsi.thirteen_case_struct.host_expected_direction = 
    	(uint_8)(cbw_ptr->flag >> USB_CBW_DIRECTION_SHIFT);	
    g_msc_scsi.thirteen_case_struct.device_expected_data_len = 0;
    g_msc_scsi.thirteen_case_struct.device_expected_direction = USB_SEND;
    g_msc_scsi.thirteen_case_struct.csw_status_ptr = csw_status_ptr;
    g_msc_scsi.thirteen_case_struct.csw_residue_ptr = csw_residue_ptr;
    g_msc_scsi.thirteen_case_struct.buffer_ptr = NULL;
    g_msc_scsi.thirteen_case_struct.lba_txrx_select = FALSE;
    
    error = msc_thirteen_cases_check(&(g_msc_scsi.thirteen_case_struct));
   
    return error;
}

/**************************************************************************//*!
 *
 * @name  msc_unsupported_command
 *
 * @brief Responds appropriately to unsupported commands
 *
 * @param controller_ID:        To identify the controller 
 * @param cbw_ptr        : pointer to Command Block Wrapper sent by host
 * @param csw_residue_ptr: pointer to dCSWDataResidue of Command Status Wrapper
 * @param csw_status_ptr : pointer to bCSWStatus  of Command Status Wrapper
 *
 * @return error
 *
 *****************************************************************************/
uint_8 msc_unsupported_command
(
	uint_8 controller_ID,
	PTR_CBW cbw_ptr,
    uint_32* csw_residue_ptr,
    uint_8* csw_status_ptr
)
{
    UNUSED(controller_ID)
    UNUSED(cbw_ptr)

    *csw_residue_ptr = 0;
    *csw_status_ptr = COMMAND_FAILED;
    								      								  
    g_msc_scsi.request_sense.sense_key = ILLEGAL_REQUEST;
    g_msc_scsi.request_sense.add_sense_code = INVALID_COMMAND_OPCODE;
    g_msc_scsi.request_sense.add_sense_code_qual = NO_SENSE;

    return USB_OK;
}

/* EOF */
