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
#include "virtual_camera.h"   /* Virtual camera Application Header File */
#include "sci.h"                /* SCI Header File */

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

/****************************************************************************
 * Global Variables
 ****************************************************************************/
#if (defined _MC9S08MM128_H)
#pragma CONST_SEG WAV
#endif

extern const unsigned char video_data[];
extern const uint_32 video_size;

#if (defined _MC9S08MM128_H)
#pragma CONST_SEG DEFAULT
#endif

/*****************************************************************************
 * Local Types - None
 *****************************************************************************/

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void USB_App_Callback(uint_8 controller_ID,
                        uint_8 event_type, void* val);
/*****************************************************************************
 * Local Variables
 *****************************************************************************/
#ifdef _MC9S08JS16_H
#pragma DATA_SEG APP_DATA
#endif
/* Virtual camera start Init Flag */
static volatile boolean start_app = FALSE;
static boolean start_send = TRUE;

static uint_8 wav_buff[VIDEO_PACKET_SIZE];

static uint_32 video_position = 0;

static uint_8 odd_img=0;

static uint_32 frame_size;

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
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
    uint_16 k;
    uint_8 j;

    wav_buff[0]=0x0C;
    wav_buff[1]=odd_img;

	    for(j=2;j<HEADER_PACKET_SIZE;j++)
	    {
	   		wav_buff[j]=0x00;
	    }
	
    /* copy data to buffer */
  	for(k=HEADER_PACKET_SIZE;k<VIDEO_PACKET_SIZE;k++,video_position++)
  	{
  		if((0xff==video_data[video_position-1])&&(0xd9==video_data[video_position]))
  		{
  			wav_buff[1]|=0x02;
  			odd_img=(uint_8)(1-odd_img);
  			
  			video_position++;
			
  			break;
  		}
  		else
  		{
  			wav_buff[k]	= video_data[video_position];

  		}
  		
  	}
}

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

void TestApp_Init(void)
{
    uint_8   error;

    DisableInterrupts;

	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
     usb_int_dis();
    #endif

     //sci_init();

    /* Initialize the USB interface */
    error = USB_Class_Video_Init(CONTROLLER_ID,USB_App_Callback,
                                NULL,NULL);

	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
     usb_int_en();
    #endif
    EnableInterrupts;
}

/******************************************************************************
 *
 *    @name        USB_App_Callback
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

static void USB_App_Callback (
    uint_8 controller_ID,   /* [IN] Controller ID */
    uint_8 event_type,      /* [IN] value of the event */
    void* val               /* [IN] gives the configuration value */
)
{
    UNUSED (controller_ID)
    UNUSED (val)
    if ((event_type == USB_APP_BUS_RESET) || (event_type == USB_APP_CONFIG_CHANGED))
    {
        start_app=FALSE;
    }
    else if(event_type == USB_APP_ENUM_COMPLETE)
    {
        start_app=TRUE;

        if (start_send==FALSE){
          USB_Prepare_Data();
          (void)USB_Class_Video_Send_Data(controller_ID, VIDEO_ENDPOINT, wav_buff,VIDEO_PACKET_SIZE) ;
        };


        //(void)printf("Virtual camera is working ...\r\n");
    }
    else if((event_type == USB_APP_SEND_COMPLETE) && (TRUE == start_app))
    {	

		if(video_position > video_size)
		{
			video_position = 0;
		}
		
		USB_Prepare_Data();
		    	
    	(void)USB_Class_Video_Send_Data(controller_ID,VIDEO_ENDPOINT,wav_buff,VIDEO_PACKET_SIZE);
     }

    return;
}

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
    /*check whether enumeration is complete or not */
    if((start_app==TRUE) && (start_send==TRUE))
    {
      start_send = FALSE;

      USB_Prepare_Data();
 	(void)USB_Class_Video_Send_Data(CONTROLLER_ID,VIDEO_ENDPOINT,wav_buff,VIDEO_PACKET_SIZE) ;
    }
}

/* EOF */
