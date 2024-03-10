/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file user_config.h
 *
 * @author
 *
 * @version
 *
 * @date
 *
 * @brief The file contains User Modifiable Macros for PHDC Application
 *
 *****************************************************************************/
#include "derivative.h"

#if (defined MCU_MK70F12) || (defined __MCF52277_H__)
	#define  HIGH_SPEED_DEVICE	(1)
#else
	#define  HIGH_SPEED_DEVICE	(0)
#endif

#if (defined MCU_MK20D7) || (defined MCU_MK40D7)
	#define MCGOUTCLK_72_MHZ
#endif

#if ((defined __MK_xxx_H__)||(defined MCU_mcf51jf128))
    #define  KEY_PRESS_SIM_TMR_INTERVAL		(1000)        /* 2s between simulated key press events */
#else
	#ifdef __MCF52277_H__
		#define  BUTTON_PRESS_SIMULATION	(1)
		#define  KEY_PRESS_SIM_TMR_INTERVAL	(5000)        /* 2s between simulated key press events */
	#endif
#endif

 /* Below two MACROS are required for PHDC Application to execute */
#define LONG_SEND_TRANSACTION       /* support to send large data pkts */
#define LONG_RECEIVE_TRANSACTION    /* support to receive large data pkts */

/* 
   Size of PHD Buffer. This buffer is used by PHDC COM MODEL to transmit user 
   data to the Host. This buffer should be greater than or equal to the 
   maximum data to be transferred.
*/
#define PHD_BUFF_SIZE               114


/* 
   Maximum Device Specialization Supported 
   User needs to ensure that g_phd_cnf_param array contains 
   MAX_DEV_SPEC_SUPPORTED elements 
*/
#define MAX_DEV_SPEC_SUPPORTED	    4

#ifndef _MC9S08JS16_H
#define USB_PACKET_SIZE  uint_16    /* support 16/32 bit packet size */
/* User Defined MACRO to set number of Timer Objects */
#define MAX_TIMER_OBJECTS		        5
#else
#define USB_PACKET_SIZE  uint_8     /* support 8 bit packet size */
/* User Defined MACRO to set number of Timer Objects */
#define MAX_TIMER_OBJECTS		        3
#endif
#if !(defined(_MCF51JM128_H) || defined(_MCF51MM256_H) || (defined _MCF51JE256_H))
/* Use double buffered endpoints 5 & 6. To be only used with S08 cores */
//#define DOUBLE_BUFFERING_USED
#endif

#if MAX_TIMER_OBJECTS
/* When Enabled Timer Callback is invoked with an argument */
/*
#define TIMER_CALLBACK_ARG 
*/
#endif

