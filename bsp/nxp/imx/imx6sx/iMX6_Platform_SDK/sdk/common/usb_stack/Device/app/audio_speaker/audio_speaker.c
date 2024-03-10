/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file audio_speaker.c
 *
 * @author
 *
 * @version
 *
 * @date 
 *
 * @brief  The file emulates a audio speaker.
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "hidef.h"          /* for EnableInterrupts macro */
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* Contains User Defined Data Types */
#include "usb_audio.h"        /* USB AUDIO Class Header File */
#include "audio_speaker.h"    /* AUDIO Speaker Application Header File */
#include "sci.h"
#include "audio_pwm.h"
#if  (defined MCU_mcf51jf128)
	#include "audio_ftm_cfv1_plus.h"
#endif
#if  (defined __MCF52xxx_H__)
	#include "audio_pit1_cfv2.h"
#endif
#if  (defined __MK_xxx_H__)
	#include "audio_pit1_kinetis.h"
#endif
#if (defined _MC9S08JM60_H) || (defined _MC9S08JM16_H) || (defined _MC9S08JS16_H)
	#include "audio_rtc.h"
#else
	#include "audio_cmt.h"
#endif
#include "usb_framework.h"   /* USB device Header File */

/* skip the inclusion in dependency stage */
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

/****************************************************************************
 * Global Variables
 ****************************************************************************/
	uint_8 audio_sample;
	uint_8 audio_event;
 uint_8 audio_data_recv[DATA_BUFF_SIZE];
#ifdef USE_FEEDBACK_ENDPOINT
	extern uint_32 feedback_data;
	extern uint_32 gNrSamples;
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
/* Audio speaker Application start Init Flag */
static volatile boolean start_app = FALSE;
#ifdef USE_FEEDBACK_ENDPOINT
static boolean start_send = TRUE;
#endif /* USE_FEEDBACK_ENDPOINT */
/* Receive Buffer */
static uint_8 g_curr_recv_buf[DATA_BUFF_SIZE];

/*****************************************************************************
 * Local Functions
 *****************************************************************************/
 /******************************************************************************
 *
 *   @name        TestApp_Init
 *
 *   @brief       This function is the entry for Audio Speaker application
 *
 *   @param       None
 *
 *   @return      None
 *****************************************************************************
 * This function starts the Audio Speaker application
 *****************************************************************************/

void TestApp_Init(void)
{
    uint_8   error;
    
    DisableInterrupts;
#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
    usb_int_dis();
#endif
    
#if !(defined _MC9S08JS16_H)
#if (defined MCU_mcf51jf128)
    sci1_init();
#elif defined MCU_MK70F12
    sci2_init();
#else
    sci_init();
#endif
#endif /* _MC9S08JS16_H */
    
#if  ((defined __MCF52xxx_H__) || (defined __MK_xxx_H__))
    pit1_init();
#elif (defined _MC9S08JM60_H) || (defined _MC9S08JM16_H) || (defined _MC9S08JS16_H)
    rtc_init();
#elif (defined MCU_mcf51jf128)
    ftm0_init();
#else
    cmt_init();
#endif
    
    pwm_init();
    /* Initialize the USB interface */
    error = USB_Class_Audio_Init(CONTROLLER_ID,USB_App_Callback,
                                 NULL,NULL);
    UNUSED(error);
    
    EnableInterrupts;
#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
    usb_int_en();
#endif
}

/******************************************************************************
 *
 *   @name        TestApp_Task
 *
 *   @brief       Application task function. It is called from the main loop
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * Application task function. It is called from the main loop
 *****************************************************************************/
void TestApp_Task(void)
{
#ifdef USE_FEEDBACK_ENDPOINT
	if((start_app == TRUE) && (start_send == TRUE))
	{   
		
		start_send = FALSE;
		feedback_data = 8<<14;	// 10.14 format (8 bytes/frame)
		(void)USB_Class_Audio_Send_Data(CONTROLLER_ID, 
										2, 
										(uint_8_ptr)&feedback_data,
										3);
	}
#endif
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
    static APP_DATA_STRUCT* data_receive;
      
    if(event_type == USB_APP_BUS_RESET)
    {
        start_app=FALSE;
    }
    else if(event_type == USB_APP_ENUM_COMPLETE)
    {
        start_app=TRUE;

        #if (!(defined _MC9S08JS16_H))
        	(void)printf("Audio Speaker is working ... \r\n");
        #endif

#ifdef USE_FEEDBACK_ENDPOINT
        // Send initial rate control feedback (48Khz)
        USB_Class_Audio_Send_Data(controller_ID, AUDIO_FEEDBACK_ENDPOINT,
        		(uint_8_ptr)&feedback_data, AUDIO_FEEDBACK_ENDPOINT_PACKET_SIZE);
#endif // USE_FEEDBACK_ENDPOINT

#if HIGH_SPEED_DEVICE
        // Start by receiving data to audio buffer
        USB_Class_Audio_Recv_Data(controller_ID, AUDIO_ENDPOINT,
        		(uint_8_ptr) g_curr_recv_buf, AUDIO_ENDPOINT_PACKET_SIZE);
#endif
    }
    else if ((event_type == USB_APP_DATA_RECEIVED) && (TRUE == start_app))
    {
        (void)USB_Class_Audio_Recv_Data(controller_ID, AUDIO_ENDPOINT, 
        		(uint_8_ptr)g_curr_recv_buf, AUDIO_ENDPOINT_PACKET_SIZE);
        		
        audio_event = USB_APP_DATA_RECEIVED;
        data_receive = (APP_DATA_STRUCT*)val;

        (void)memcpy(audio_data_recv, data_receive->data_ptr, data_receive->data_size);
        /*for(i=0;i<data_receive->data_size;i++){
        	audio_data_recv[i] = data_receive->data_ptr[i];
        }*/
    }
#ifdef USE_FEEDBACK_ENDPOINT
    else if((event_type == USB_APP_SEND_COMPLETE) && (TRUE == start_app))
    {
    	feedback_data <<= 14;	// 10.14 format
    	(void)USB_Class_Audio_Send_Data(controller_ID, 
    			AUDIO_FEEDBACK_ENDPOINT, 
				(uint_8_ptr)&feedback_data,
				AUDIO_FEEDBACK_ENDPOINT_PACKET_SIZE);
										
    }
#endif
    
    return;
}

/* EOF */
