/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file phdc_app.c
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief When the device is connected using continua manager it comes into
 *        operating state and the device specialization is Weighing Scale.
 *        Measurements can be sent by pressing PTG1 button on the demo board.
 *        Device specialization can be changed by pressing PTG3.
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "hidef.h"          /* for EnableInterrupts macro */
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* User Defined Data Types */
#include "phdc_app.h"       /* PHDC Application Header File */
#include "phd_com_model.h"  /* IEEE11073 Header File */
#include "phd_device_spec.h"
#include "realtimercounter.h"
/* skip the inclusion in dependency statge */
#ifndef __NO_SETJMP
   #include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>			

#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
#include "exceptions.h"
#endif
/*****************************************************************************
 * Constant and Macro's - None
 *****************************************************************************/

/*****************************************************************************
 * Global Functions Prototypes
 *****************************************************************************/
void TestApp_Init(void);
extern void display_led(uint_8 val);
/****************************************************************************
 * Global Variables 
 ****************************************************************************/
extern uint_8 g_phd_selected_configuration;
/*****************************************************************************
 * Local Types - None
 *****************************************************************************/
#if HIGH_SPEED_DEVICE
static uint_8 g_phdcBuffer[PHDC_BULK_OUT_EP_SIZE>>1];
#endif

/*****************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/
static void USB_App_Callback(uint_8 controller_ID, uint_8 event_type);
static void Button_Pressed(void);
static void App_Display(uint_8 val);
#ifdef TIMER_CALLBACK_ARG
static void SelectTimerCallback(void * arg);
#else
static void SelectTimerCallback(void);
#endif
/*****************************************************************************
 * Local Variables
 *****************************************************************************/
static uint_8 event=APP_PHD_UNINITIALISED;

uint_8 g_app_timer = INVALID_TIMER_VALUE;
/*****************************************************************************
 * Local Functions
 *****************************************************************************/
/******************************************************************************
 *
 *    @name        USB_App_Callback
 *
 *    @brief       This function handles the callback
 *
 *    @param       controller_ID    : Controller ID
 *    @param       event_type       : Value of the event
 *
 *    @return      None
 *
 *****************************************************************************
 * This function is called from the lower layer whenever an event occurs.
 * This sets a variable according to the event_type
 *****************************************************************************/
static void USB_App_Callback(
      uint_8 controller_ID, /* [IN] Controller ID */
      uint_8 event_type     /* [IN] Value of the event */
)
{
    UNUSED (controller_ID)
    /* Remove Timer if any */
    if(g_app_timer != INVALID_TIMER_VALUE)
    {
        (void)RemoveTimerQ(g_app_timer);
        g_app_timer = INVALID_TIMER_VALUE;
    }
    switch(event_type)
    {
        case APP_PHD_UNINITIALISED:
        case APP_PHD_INITIALISED:
		    App_Display((uint_8)g_phd_selected_configuration);

        case APP_PHD_CONNECTED_TO_HOST:
#if HIGH_SPEED_DEVICE
    	// prepare for the next receive event
    	_usb_device_recv_data(&controller_ID, 
    			PHDC_BULK_OUT_EP,
    			g_phdcBuffer,
    			PHDC_BULK_OUT_EP_SIZE);
#endif
        case APP_PHD_ERROR:
            scanReportNo = 0; /* Initialize with 0 each time the Agent is associated to the manager */
            event = event_type;
            break;
        case APP_PHD_MEASUREMENT_SENT:
            event = APP_PHD_CONNECTED_TO_HOST;
            break;
        case APP_PHD_DISCONNECTED_FROM_HOST:
#if HIGH_SPEED_DEVICE
    	// prepare for the next receive event
    	_usb_device_recv_data(&controller_ID, 
    			PHDC_BULK_OUT_EP,
    			g_phdcBuffer,
    			PHDC_BULK_OUT_EP_SIZE);
#endif
        case APP_PHD_ASSOCIATION_TIMEDOUT:
            event = APP_PHD_INITIALISED;
        	break;
    }   
    return;
}
/******************************************************************************
 *
 *   @name        Button_Pressed
 *
 *   @brief       This funtion checks for any button pressed on the demo board
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * This function sends measurements, dissociation request or changes the device
 * specialization depending on the button pressed
 *****************************************************************************/
 static void Button_Pressed(void)
 {
    if(kbi_stat > 0)
    {
        switch(kbi_stat & KBI_STAT_MASK)
        {
            case SEND_MEASUREMENT: 
                /* 
                    PTG1 is pressed, used to send
                    measurements 
                */
                if(event == APP_PHD_CONNECTED_TO_HOST)
                {
    		        /* 
    		            Send measurements only when the device is in the 
    		            operating state 
    		        */
    		        event = APP_PHD_MEASUREMENT_SENDING;
                    PHD_Send_Measurements_to_Manager(CONTROLLER_ID);
                }
                break;

            case DISCONNECT:  
             #ifndef BUTTON_PRESS_SIMULATION
                /* 
                    PTG2 is pressed, to disconnect(dis-associate)
                    from the host 
                */
                if(event == APP_PHD_CONNECTED_TO_HOST)
                {
                    event = APP_PHD_DISCONNECTING;
                    PHD_Disconnect_from_Manager(CONTROLLER_ID);
                }
#endif
      break;

            case SELECT_DEVICE_SPEC:
			{
			    uint_8 index;
			    /*
			        Remove Timer if any 
			    */
                (void)RemoveTimerQ(g_app_timer);
                if(event == APP_PHD_SELECT_TIMER_STARTED)
                {
                    /* 
                        If the device is not associated, start a timer to wait 
                        for another select device key press 
                    */
                    TIMER_OBJECT TimerObject;
                    TimerObject.msCount = SELECT_TIMEOUT;
                    TimerObject.pfnTimerCallback = SelectTimerCallback;

                    g_app_timer = AddTimerQ(&TimerObject);
                } 
                else if (event == APP_PHD_CONNECTED_TO_HOST)
                {
                    /* 
                        If the device is associated, send association release
                        request, so that the new specialization can be 
                        associated 
                    */
                    event = APP_PHD_DISCONNECTING;
                    PHD_Disconnect_from_Manager(CONTROLLER_ID);
                }
                    
                index = g_phd_selected_configuration;
                index = (uint_8)((index + 1) % MAX_DEV_SPEC_SUPPORTED);
                g_phd_selected_configuration = index;
                App_Display((uint_8)g_phd_selected_configuration);
			}
                break;
               
            default:
                break; /* otherwise */
        }
        kbi_stat = 0x00;
    }
 }
/******************************************************************************
 *
 *   @name        TestApp_Init
 *
 *   @brief       This function is the entry for the PHDC Multi Specialization
 *                Application 
 *
 *   @param       None
 *
 *   @return      None
 *
 *****************************************************************************
 * This function starts the PHDC (Multi Specialization demo) application
 *****************************************************************************/
void TestApp_Init(void)
{
    uint_8 error;

    DisableInterrupts;
	#if (defined _MCF51MM256_H) || (defined _MCF51JE256_H)
     usb_int_dis();
    #endif	

    /* Initialize the USB interface */
    error = PHD_Transport_Init(CONTROLLER_ID, USB_App_Callback);

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
        
        /* Check for any button pressed */
        Button_Pressed();
        
        switch (event)
        {
            case APP_PHD_INITIALISED:
                {
                    /* 
                        Start a timer so that the user has enough time to 
                        select the device specialization 
                    */
                    TIMER_OBJECT TimerObject;
                    TimerObject.msCount = SELECT_TIMEOUT;
                    TimerObject.pfnTimerCallback = SelectTimerCallback;
                 
                    event = APP_PHD_SELECT_TIMER_STARTED;
                    g_app_timer = AddTimerQ(&TimerObject);
                }
                break;
            case APP_PHD_DISCONNECTED_FROM_HOST:
                /* 
                    transition to initialised state so the association 
                    procedure can start again 
                */
                event = APP_PHD_INITIALISED;
                break;

            case APP_PHD_MEASUREMENT_SENT:
                /* 
                    enters here each time we receive a response to the
                    measurements sent 
                */
                event = APP_PHD_CONNECTED_TO_HOST;
                break;
            case APP_PHD_SELECT_TIMER_OFF:
                /* 
                    Start the association procedure once the select timer 
                    fires 
                */
                event = APP_PHD_INITIATED;
                /* connect to the manager */
                PHD_Connect_to_Manager(CONTROLLER_ID);                  
                break;
                  
          default:
              break;
    
        }

}

/******************************************************************************
 *
 *   @name        App_Display
 *
 *   @brief       This function displays the leds on the demo board 
 *                corressponding to the device specialization currently running
 *
 *   @param       val   : Value to display
 *
 *   @return      None
 *
 *****************************************************************************
 * This funtions displays the LEDs on the board so that user knows which 
 * device specialization is active
 *****************************************************************************/
static void App_Display (
    uint_8 val      /* [IN] Value to display */
)
{
#ifndef _MC9S08JS16_H
    /* LED Display Code */
    display_led((uint_8)(0x1<<val));
#else
    /* JS16 Specific LED Display Code */
    display_led(val);
#endif
}
/******************************************************************************
 *
 *   @name        SelectTimerCallback
 *
 *   @brief       This function is called when the timer used for selecting the
 *                the device specialization fires
 *
 *   @param       arg   : Argument passed by Timer ISR (optional)
 *
 *   @return      None
 *
 *****************************************************************************
 * This function when called initiates the association procedure for the 
 * selected device specialization
 *****************************************************************************/
#ifdef TIMER_CALLBACK_ARG
static void SelectTimerCallback(void * arg)
#else
static void SelectTimerCallback(void)
#endif
{
#ifdef TIMER_CALLBACK_ARG
    UNUSED (arg)
#endif
    g_app_timer = INVALID_TIMER_VALUE;
    event = APP_PHD_SELECT_TIMER_OFF;
}