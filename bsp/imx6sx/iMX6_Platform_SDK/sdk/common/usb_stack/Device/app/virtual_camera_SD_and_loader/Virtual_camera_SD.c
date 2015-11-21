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
#include "usb_video.h"          /* USB Video Class Header File */
#include "usb_msc.h"          /* USB MSD Class Header File */
#include "virtual_camera_sd.h"   /* Virtual camera Application Header File */
#include "sci.h"                /* SCI Header File */
#include "FAT16.h"
#include "write_sd_data.h"

#if defined( __MCF52xxx_H__)
#include "SD_cfv2.h"
#elif defined(__MK_xxx_H__)
#include "SD_kinetis.h"
#elif defined(MCU_mcf51jf128)
#include "SD_cfv1_plus.h"
#else
#include "SD.h"     
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
void TestApp_Init(void);
void TestApp_Task(void);
void USB_Prepare_Data(void);
void Read_data (void);
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
static void USB_VIDEO_App_Callback(uint_8 controller_ID,
		uint_8 event_type, void* val);
static void Sd_Prepare_Data (uint_8_ptr data_ptr);
static void GPIO_SD_init();

/*****************************************************************************
 * Local Variables
 *****************************************************************************/
#ifdef _MC9S08JS16_H
#pragma DATA_SEG APP_DATA
#endif

/* Virtual camera start Init Flag */
static volatile boolean start_video_app = FALSE, stop_video = FALSE;
static boolean start_video_send = TRUE;
static uint_8 video_data_SD[1024];
static uint_32 video_block_position = 0;
static uint_16 video_position =0;
static uint_8 odd_img=0;
static uint_16 buffer_size = 512, remain_bytes = 0;

uint_8 wav_buff[512];
uint_8 current_class = VIDEO_CLASS;
uint_16 video_packet_size=0;
uint_32 total_block=0;
uint_32 num_image, frame_rate;

LBA_APP_STRUCT lba_data;

extern DISK_GLOBAL_VARIABLE_STRUCT g_disk;

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/******************************************************************************
 *
 *   @name        TestApp_Init
 *
 *   @brief       This function is the entry for the Virtual camera application
 *
 *   @param       None
 *
 *   @return      None
 *****************************************************************************
 * This function starts the virtual camera application
 *****************************************************************************/
void GPIO_SD_init()
{
#if defined(MCU_MK60N512VMD100)  
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;      /* Enable clock gating to PORTA */

	/* set in put PORTA pin 19 */
	PORTA_PCR19 =  PORT_PCR_MUX(1);
	GPIOA_PDDR &= ~((uint_32)1 << 19);

	PORTA_PCR19 |= PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;   /* pull up*/
#endif
#if defined(MCU_MK21D5)  
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      /* Enable clock gating to PORTC */

	/* set in put PORTC pin 6 */
	PORTC_PCR6 =  PORT_PCR_MUX(1);
	GPIOC_PDDR &= ~((uint_32)1 << 6);

	PORTC_PCR6 |= PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;   /* pull up*/
#endif
#if defined(MCU_MK70F12)  
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;      /* Enable clock gating to PORTA */

	/* set in put PORTA pin 0 */
	PORTD_PCR0 =  PORT_PCR_MUX(1);
	GPIOD_PDDR &= ~((uint_32)1 << 0);

	PORTD_PCR0 |= PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;   /* pull up*/
#endif

#if defined(__MCF52259_H__)
	/* M52259TWR: SW1,  SW3 connected to PTA[0 - 1] */
	/* Configure PTA[0 - 1] as input */    
	MCF_GPIO_DDRTA &= ~(MCF_GPIO_DDRTA_DDRTA0 |
			MCF_GPIO_DDRTA_DDRTA1 );
#endif

#if defined(_MCF51MM256_H)
	/* M52259TWR: SW2,  SW4 connected to PTC[6] and PTE[4] */
	/* Configure PTE[4]  as input */    
	PTEPE |= 0x08;
	PTEDD &= 0xF7;
#endif
}
void TestApp_Init(void)
{
	/*Body*/
	uint_8   error;
	uint_32 i,j;
	volatile uint_32  temp = 1;

	DisableInterrupts;

#if defined(MCU_MK60N512VMD100)  
	GPIO_SD_init();
	temp =(uint_32) ((1<<19) & GPIOA_PDIR);               /* READ SW1 of TWK60 */
#endif
#if defined(MCU_MKL25Z4)  
	GPIO_SD_init();
	temp =(uint_32) ((1<<3) & GPIOC_PDIR);               /* READ SW3 of TWK25 */
#endif
#if defined(MCU_MK21D5)  
	GPIO_SD_init();
	temp =(uint_32) ((1<<6) & GPIOC_PDIR);               /* READ SW1 of TWK60 */
#endif
#if defined MCU_MK70F12
	temp =(uint_32) ((1<<0) & GPIOD_PDIR);               /* READ SW1 of TWK70 */
#endif

#if defined(__MCF52259_H__)
	GPIO_SD_init();
	temp=(MCF_GPIO_SETTA&1);
#endif

#if defined(_MCF51MM256_H)  
	GPIO_SD_init();
	temp=PTED_PTED4;
#endif
	for(i=0;i<10;i++)
	{
		if(!temp)
		{
			current_class = MSD_CLASS;
		}
	}
	for(i=0;i<100;i++)
		for(j=0;j<1000;j++); 

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
	usb_int_dis();
#endif

	sci_init();
	(void)SD_Init(); /* Initialize SD_CARD and SPI Interface */
	(void)SD_ReadCSD();

	if(VIDEO_CLASS== current_class) {
		/* Read the first block to get video information */
		lba_data.offset = 0x00010000;
		lba_data.size = 0x200;
		lba_data.buff_ptr = video_data_SD;
		SD_Read_Block(&lba_data);
		total_block= ieee_htonl(*((uint_32*)lba_data.buff_ptr)) ;
		num_image= ieee_htonl(*((uint_32*)(lba_data.buff_ptr + 4))) ;
		frame_rate= ieee_htonl(*((uint_32*)(lba_data.buff_ptr + 8))) ;
		if(num_image && frame_rate)
		{
			video_packet_size=(uint_16)((total_block* frame_rate)/(num_image*2));
		}
		else
		{
			printf("Card read error!\n");
			return;
		}
		/* Initialize the USB interface */
		error = USB_Class_Video_Init(CONTROLLER_ID,USB_VIDEO_App_Callback,
				NULL,NULL);
	} else {
		/* initialize the Global Variable Structure */
		USB_memzero(&g_disk, sizeof(DISK_GLOBAL_VARIABLE_STRUCT));
		g_disk.app_controller_ID = CONTROLLER_ID;

		error = USB_Class_MSC_Init(g_disk.app_controller_ID,
				USB_MSD_App_Callback,NULL, MSD_Event_Callback);
	}

	UNUSED(error);
	
#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
	usb_int_en();
#endif
	EnableInterrupts;
}/* EndBody*/

/******************************************************************************
 *
 *    @name        TestApp_Task
 *
 *    @brief       This function use to send data
 *
 *    @param       None
 *
 *    @return      None
 *
 *****************************************************************************
 * 
 *****************************************************************************/
void TestApp_Task(void)
{
	/*Body*/
	if (VIDEO_CLASS== current_class)
	{
		/*check whether enumeration is complete or not */
		if((start_video_app==TRUE) && (start_video_send==TRUE))
		{
			start_video_send = FALSE;
			USB_Prepare_Data();
			(void)USB_Class_Video_Send_Data(CONTROLLER_ID,VIDEO_ENDPOINT,wav_buff,video_packet_size) ;
		}/*EndIf*/
	}
	else
	{
		/*check whether enumeration is complete or not */
		if(g_disk.start_app==TRUE)
		{
			Disk_App(); 
		} /* EndIf */
	}
}/*EndBody*/

/******************************************************************************
 *
 *    @name        USB_VIDEO_App_Callback
 *
 *    @brief       This function handles Class callback
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : Value of the event
 *    @param       val              : gives the configuration value
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called from the class layer whenever reset occurs or enum
 * is completed. After the enum is completed this function sets a variable so
 * that the application can start.
 * This function also receives DATA Send and RECEIVED Events
 *****************************************************************************/
static void USB_VIDEO_App_Callback (
		uint_8 controller_ID,   /* [IN] Controller ID */
		uint_8 event_type,      /* [IN] value of the event */
		void* val               /* [IN] gives the configuration value */
)
{
	/*Body*/
	UNUSED (controller_ID)
    										UNUSED (val)
    										if ((event_type == USB_APP_BUS_RESET) || (event_type == USB_APP_CONFIG_CHANGED))
    										{
    											start_video_send=FALSE;   
    										}/*elseif*/
    										else if(event_type == USB_APP_ENUM_COMPLETE)
    										{
    											start_video_app=TRUE;
    											if (start_video_send==FALSE){
    												USB_Prepare_Data();
    												(void)USB_Class_Video_Send_Data(controller_ID, VIDEO_ENDPOINT, wav_buff,video_packet_size) ;
    											}/*EndIf*/
    											(void)printf("Virtual camera is working ...\r\n");
    										}/*EndElse*/
    										else if((event_type == USB_APP_SEND_COMPLETE) && (TRUE == start_video_app))
    										{    
    											if(( video_block_position >= total_block)&&(stop_video == TRUE))
    											{
    												video_block_position = 0;
    												remain_bytes = 0;
    												video_position = 0;
    											} /* EndIf */
    											USB_Prepare_Data();
    											(void)USB_Class_Video_Send_Data(controller_ID,VIDEO_ENDPOINT,wav_buff,video_packet_size);
    										}/*EndIf*/
	return;
}/*EndBody*/

/******************************************************************************
 *
 *   @name        USB_Prepare_Data
 *
 *   @brief       This function prepares data to send
 *
 *   @param       None
 *
 *   @return      None
 *****************************************************************************
 * This function prepare data before sending
 *****************************************************************************/
void USB_Prepare_Data(void)
{
	/* Body */
	uint_32 i;
	uint_8 j;
	uint_16  video_packet_size_tmp;
	video_packet_size_tmp = (uint_16)(video_packet_size -12);
	wav_buff[0]=0x0C;
	wav_buff[1]=odd_img;
	for(j=2;j<HEADER_PACKET_SIZE;j++)
	{
		wav_buff[j]=0x00;
	} /* EndFor */
	/* Prepare video data to send */
	if ((video_block_position == 0)||(remain_bytes < video_packet_size_tmp))
	{
		for(i=0;i<remain_bytes;i++)
		{
			video_data_SD[i] = video_data_SD[i+video_position]; 
		} /* EndFor */
		Read_data();
		buffer_size= (uint_16)(remain_bytes + BLOCK_SIZE);
		remain_bytes = 0;
		video_position = 0;
	} /* EndIf */
	for(i=0;i<video_packet_size_tmp;i++,video_position++)
	{
		/* Check image is complete */
		if((0xFF == video_data_SD[video_position]) && (0xD9 == video_data_SD[video_position+1]))
		{
			/* check video is complete */
			if (video_block_position >= total_block)
			{
				stop_video = TRUE;
				break;
			} /* EndIf */
			wav_buff[1]|=0x02;
			odd_img=(uint_8)(1-odd_img);
			wav_buff[i+12] = video_data_SD[video_position];
			video_position+=2;
			break;
		}
		else
		{
			wav_buff[i+12] = video_data_SD[video_position];
		}/*Endif*/
	}/*EndFor*/
	remain_bytes = (uint_16)(buffer_size - video_position);
}/* EndBody */

/******************************************************************************
 *
 *    @name        Read_data
 *
 *    @brief       This function use to read data from SD card
 *
 *    @param       None
 *
 *    @return      None
 *
 *****************************************************************************
 * 
 *****************************************************************************/
void Read_data (void)
{  
	/*Body*/
	/*Video_data start at 0x00011200*/
	lba_data.offset = 0x00011200 + video_block_position*BLOCK_SIZE;
	lba_data.buff_ptr = video_data_SD + remain_bytes;/* Connect data to end of remain data*/
	lba_data.size = BLOCK_SIZE;

	/* Read a video_data block from SD*/
	SD_Read_Block(&lba_data);
	video_block_position++;
}/*EndBody*/
/* EOF */
