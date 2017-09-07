/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file audio_generator.c
 *
 * @author
 *
 * @version
 *
 * @date Jul-20-2010
 *
 * @brief  The file emulates a audio generator.
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "hidef.h"              /* for EnableInterrupts macro */
#include "derivative.h"         /* include peripheral declarations */
#include "types.h"              /* Contains User Defined Data Types */
#include "usb_audio.h"          /* USB Audio Class Header File */
#include "audio_generator.h"   /* Audio generator Application Header File */
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

extern const unsigned char wav_data[];
extern const uint_16 wav_size;

#if (defined _MC9S08MM128_H)
#pragma CONST_SEG DEFAULT
#endif

uint_8 audio_sample;
uint_8 audio_event;
uint_8 audio_data_recv[8];
extern uint_8 g_cur_mute[USB_MAX_SUPPORTED_INTERFACES];

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
/* Audio speaker Application start Init Flag */
static volatile boolean start_app = FALSE;
static boolean start_send = TRUE;
static uint_8 wav_buff[8];
static uint_32 audio_position = 0;

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
    uint_8 k;
    if (g_cur_mute[0] == 0)
    {
		/* copy data to buffer */
		for(k=0;k<8;k++,audio_position++)
		{
			wav_buff[k]	= wav_data[audio_position];
		}
    }
    else
    {
		/* copy data to buffer */
		for(k=0;k<8;k++,audio_position++)
		{
			wav_buff[k]	= 0;
		}
    }
}

 /******************************************************************************
 *
 *   @name        TestApp_Init
 *
 *   @brief       This function is the entry for the Audio generator application
 *
 *   @param       None
 *
 *   @return      None
 *****************************************************************************
 * This function starts the audio generator application
 *****************************************************************************/

void TestApp_Init(void)
{
    uint_8   error;

    DisableInterrupts;
    
	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
     usb_int_dis();
    #endif
     
     /* Initialize SCI */
	#if (defined MCU_mcf51jf128)
		 sci1_init();
	#elif defined MCU_MK70F12
		sci2_init();
	#else
		 sci_init();
	#endif
     
    /* Initialize the USB interface */
    error = USB_Class_Audio_Init(CONTROLLER_ID,USB_App_Callback,
                                NULL,NULL);
    UNUSED(error);
                                
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
        if (start_send == FALSE)
        {
          USB_Prepare_Data();     		
          (void)USB_Class_Audio_Send_Data(CONTROLLER_ID, AUDIO_ENDPOINT, wav_buff,(sizeof(wav_buff)/sizeof(wav_buff[0]))) ;
        }
#if (!(defined _MC9S08MM128_H) && !(defined _MC9S08JE128_H))
        (void)printf("Audio generator is working ...\r\n");
#endif
    }
    else if((event_type == USB_APP_SEND_COMPLETE) && (TRUE == start_app))
    {	
        	if(audio_position > wav_size)
        	{
        		audio_position = 0;
        	}
          USB_Prepare_Data();
        	(void)USB_Class_Audio_Send_Data(controller_ID, AUDIO_ENDPOINT, wav_buff,(sizeof(wav_buff)/sizeof(wav_buff[0])));
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
	/* Check whether enumeration is complete or not */
	if((start_app == TRUE) && (start_send == TRUE))
	{
		start_send = FALSE;
		USB_Prepare_Data();
		(void)USB_Class_Audio_Send_Data(CONTROLLER_ID, AUDIO_ENDPOINT, wav_buff,(sizeof(wav_buff)/sizeof(wav_buff[0]))) ;
	}
}

/* EOF */
