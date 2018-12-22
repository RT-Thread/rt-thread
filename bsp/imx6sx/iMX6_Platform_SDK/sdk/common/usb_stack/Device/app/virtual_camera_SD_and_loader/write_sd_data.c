/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file virtual_camera.c
 *
 * @author
 *
 * @version
 *
 * @date Jul-20-2010
 *
 * @brief The file emulates a virtual camerea
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "hidef.h"              /* for EnableInterrupts macro */
#include "derivative.h"         /* include peripheral declarations */
#include "types.h"              /* Contains User Defined Data Types */
#include "usb_msc.h"          /* USB MSD Class Header File */
#include "sci.h"                /* SCI Header File */
#include "FAT16.h"
#include "write_sd_data.h"

#if defined( __MCF52xxx_H__)
#include "SD_cfv2.h"
#elif defined(__MK_xxx_H__)
#include "SD_kinetis.h"
#elif defined(_MCF51MM256_H) || defined(MCU_mcf51jf128)
#include "SD_cfv1_plus.h"
#endif

/* skip the inclusion in dependency statge */
#ifndef __NO_SETJMP
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
void Read_data (void);
void MSD_Event_Callback(uint_8 controller_ID, uint_8 event_type, void* val);
/****************************************************************************
 * Global Variables
 ****************************************************************************/
#if (defined _MC9S08MM128_H)
#pragma CONST_SEG WAV
#endif

#if (defined _MC9S08MM128_H)
#pragma CONST_SEG DEFAULT
#endif

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
void USB_MSD_App_Callback(uint_8 controller_ID,
		uint_8 event_type, void* val);
static void Sd_Prepare_Data (uint_8_ptr data_ptr);

/*****************************************************************************
 * Local Variables
 *****************************************************************************/
#ifdef _MC9S08JS16_H
#pragma DATA_SEG APP_DATA
#endif

/* For MSD class */
uint_32         file_size;            /* bytes */ 
uint_8          new_file;  
uint_8          error=FLASH_IMAGE_SUCCESS;
boolean         boot_complete = FALSE; 

/* Add all the variables needed for disk.c to this structure */
DISK_GLOBAL_VARIABLE_STRUCT g_disk;
unsigned char BootloaderStatus = BootloaderReady;

static uint_32 block_position = 0;
static uint_8 info_flag=FALSE;
static uint_16 buff_postion = 0;
static uint_8 pre_data=0,cur_data=0,next_data=0;
static boolean video_flag = FALSE;
static uint_16 image_position = 0;
static uint_32 dwScale,dwRate;

extern LBA_APP_STRUCT lba_data;
extern uint_8 wav_buff[512];
extern uint_32 total_block;
extern uint_32 num_image, frame_rate;

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/******************************************************************************
 * 
 *    @name        USB_MSD_App_Callback
 *    
 *    @brief       This function handles the callback  
 *                  
 *    @param       controller_ID : To Identify the controller
 *    @param       event_type : value of the event
 *    @param       val : gives the configuration value 
 * 
 *    @return      None
 *
 *****************************************************************************/
void USB_MSD_App_Callback
(
		uint_8 controller_ID, 
		uint_8 event_type, 
		void* val
)
{
	/* Body */
	UNUSED (controller_ID)
    				UNUSED (val)
    				if(event_type == USB_APP_BUS_RESET) 
    				{
    					g_disk.start_app=FALSE;
    				}
    				else
    				{
    					if(event_type == USB_APP_ENUM_COMPLETE) 
    					{
    						g_disk.start_app=TRUE;
    					}
    					else
    					{
    						if(event_type == USB_APP_ERROR)
    						{
    							/* add user code for error handling */
    						} /* EndIf */
    					} /* EndIf */
    				} /* EndIf */
	return;
} /* EndBody */

/******************************************************************************
 * 
 *    @name        MSD_Event_Callback
 *    
 *    @brief       This function handles the callback  
 *                  
 *    @param       controller_ID : To Identify the controller
 *    @param       event_type : value of the event
 *    @param       val : gives the configuration value 
 * 
 *    @return      None
 *
 *****************************************************************************/
void MSD_Event_Callback(uint_8 controller_ID, 
		uint_8 event_type, 
		void* val) 
{
	/* Body */
	PTR_LBA_APP_STRUCT lba_data_ptr;
	uint_32 i;
	uint_32 count;
	uint_8_ptr prevent_removal_ptr, load_eject_start_ptr = 0;
	PTR_DEVICE_LBA_INFO_STRUCT device_lba_info_ptr;
	
	UNUSED (controller_ID)
	UNUSED(load_eject_start_ptr)
	  
	switch(event_type)
	{
	case USB_APP_DATA_RECEIVED :
		break;
	case USB_APP_SEND_COMPLETE :
		break;
	case USB_MSC_START_STOP_EJECT_MEDIA :
		load_eject_start_ptr = (uint_8_ptr)val;
		/* Code to be added by user for starting, stopping or 
            ejecting the disk drive. e.g. starting/stopping the motor in 
            case of CD/DVD*/
		break;
	case USB_MSC_DEVICE_READ_REQUEST :
		/* copy data from storage device before sending it on USB Bus 
            (Called before calling send_data on BULK IN endpoints)*/
		lba_data_ptr = (PTR_LBA_APP_STRUCT)val;
		/* read data from mass storage device to driver buffer */
		FATReadLBA(lba_data_ptr->offset>>9,lba_data_ptr->buff_ptr);
		break;
	case USB_MSC_DEVICE_WRITE_REQUEST :
		/* copy data from USb buffer to Storage device 
            (Called before after recv_data on BULK OUT endpoints)*/
		lba_data_ptr = (PTR_LBA_APP_STRUCT)val;
		if((lba_data_ptr->offset>>9)== FATTable0Sec0) 
		{
			/* write new file */
			new_file = TRUE;
		} /* EndIf */
		if(((lba_data_ptr->offset>>9)== FATRootDirSec0)&&(new_file == TRUE)) 
		{
			/* read file size of the file was received */
			/* search for the file entry was received */
			/* each file entry contain 32 bytes */ 
			for(i = lba_data_ptr->size -32; i>0; i -=32) 
			{
				if(*(lba_data_ptr->buff_ptr +i) != 0)
				{
					break;
				} /* EndIf */
			} /* Endfor */
			/* the file size field is offet 28 of file entry */
#if (defined __MK_xxx_H__)
			file_size = *(uint_32*)( lba_data_ptr->buff_ptr + i + 28);
#else
			file_size = BYTESWAP32(*(uint_32*)( lba_data_ptr->buff_ptr + i + 28));
#endif
			new_file = FALSE;
		} /* EndIf */
		if((lba_data_ptr->offset>>9)>= FATDataSec0) 
		{
			Sd_Prepare_Data(lba_data_ptr->buff_ptr);
		} /* EndIf */
		/* rest of file */ 
		if(((lba_data_ptr->offset>>9) - FATDataSec0) == ((file_size -1)/BLOCK_SIZE))
		{
			boot_complete=TRUE;     /*tranfer file done */           
			*((uint_32*)wav_buff) = ieee_htonl(total_block) ;
			*((uint_32*)(wav_buff+4))  = ieee_htonl(num_image);
			*((uint_32*)(wav_buff+8)) = ieee_htonl(frame_rate);
			for (count=12 ; count<BLOCK_SIZE ; count ++)
			{
				*(wav_buff+count) = 0xFF;   
			}
			lba_data.offset = 0x00010000;
			lba_data.size = 0x200;
			lba_data.buff_ptr = wav_buff;
			SD_Write_Block(&lba_data);
			BootloaderStatus = BootloaderSuccess;
		} /* EndIf */
		break;
	case USB_MSC_DEVICE_FORMAT_COMPLETE :
		break;
	case USB_MSC_DEVICE_REMOVAL_REQUEST :
		prevent_removal_ptr = (uint_8_ptr) val;
		if(SUPPORT_DISK_LOCKING_MECHANISM)
		{
			g_disk.disk_lock = *prevent_removal_ptr;
		}
		else 
		{
			if((!SUPPORT_DISK_LOCKING_MECHANISM)&&(!(*prevent_removal_ptr)))
			{
				/*there is no support for disk locking and removal of medium is enabled*/
				/* code to be added here for this condition, if required */ 
			} /* EndIf */
		} /* EndIf */
		break;
	case USB_MSC_DEVICE_GET_INFO :
		device_lba_info_ptr = (PTR_DEVICE_LBA_INFO_STRUCT)val;
		device_lba_info_ptr->total_lba_device_supports = TOTAL_LOGICAL_ADDRESS_BLOCKS;
		device_lba_info_ptr->length_of_each_lba_of_device = LENGTH_OF_EACH_LAB; 
		device_lba_info_ptr->num_lun_supported = LOGICAL_UNIT_SUPPORTED;
		break;
	default : 
		break;
	} /* EndSwitch */
	return;
}

/******************************************************************************
 * 
 *    @name       Disk_App
 *    
 *    @brief      
 *                  
 *    @param      None
 * 
 *    @return     None
 *    
 *****************************************************************************/
void Disk_App(void)
{
	/* Body */
	uint_32 i = 0;
	uint_32 j = 0;
	if(TRUE== boot_complete)
	{
		/* De-Init MSD device */
		for(i=0;i<1000;i++)
			for(j=0;j<1000;j++) ;
		USB_Class_MSC_DeInit(g_disk.app_controller_ID);
		boot_complete = FALSE;
		for(i=0;i<1000;i++)
			for(j=0;j<1000;j++) ;
		/* Re-enumerate MSD device */
		USB_Class_MSC_Init(g_disk.app_controller_ID,
				USB_MSD_App_Callback,NULL, MSD_Event_Callback);
	} /* EndIf */
	return;
} /* EndBody */

/******************************************************************************
 *  
 *   @name        Sd_Write
 * 
 *   @brief       This function is the entry for mouse (or other usuage)
 * 
 *   @param       data_ptr
 * 
 *   @return      None
 **                
 *****************************************************************************/
static void Sd_Write (uint_8_ptr data_ptr)
{      
	/* Body */
	lba_data.offset = 0x00011200 + BLOCK_SIZE*block_position;
	lba_data.size = 0x200;
	lba_data.buff_ptr = (uint_8_ptr)data_ptr;
	SD_Write_Block(&lba_data);
	block_position++;
} /* EndBody */

/******************************************************************************
 *  
 *   @name        Sd_Prepare_Data
 * 
 *   @brief       This function is the entry for mouse (or other usuage)
 * 
 *   @param       data_ptr
 * 
 *   @return      None
 **                
 *****************************************************************************/
static void Sd_Prepare_Data (uint_8_ptr data_ptr)
{
	/* Body */
	uint_8_ptr buffer;
	uint_16 j = 0;
	buffer = data_ptr;
	if(TRUE==info_flag)
	{
		/*The buffer isn't contain video header*/
		for(j= 0;j<LENGTH_OF_EACH_LAB;j++,buff_postion++)
		{
			pre_data=cur_data;
			cur_data=next_data;
			next_data= buffer[j];
			if(( 0xFF==cur_data)&&(0xD8==next_data))
			{
				video_flag = TRUE;
				num_image++; 
			}
			if(TRUE==video_flag )
			{
				if ((0xFF==pre_data)&&(0xD9==cur_data)) 
				{
					video_flag = FALSE;
				} /* EndIf */
				wav_buff[image_position++]= cur_data;  
			} /* EndIf */
			if ( BLOCK_SIZE==image_position)
			{
				Sd_Write(wav_buff);
				image_position = 0;
				total_block ++;
			} /* EndIf */
		} /* EndFor */
	}
	else
	{
		/*Read video header to get video infomation*/
		dwScale = (buffer[128])|(buffer[129]<<8)|(buffer[130]<<16)|(buffer[131]<<24);
		dwRate = (buffer[132])|(buffer[133]<<8)|(buffer[134]<<16)|(buffer[135]<<24);
		frame_rate=(uint_32)(dwRate/dwScale);
		info_flag=TRUE;
	} /* EndIf */
} /* EndBody */

/* EOF */
