/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
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
 * @date May-2012
 *
 * @brief The file contains User Modifiable Macros for MSD Application
 * ****************************************************************************/
#include "derivative.h"

#if defined MCU_MK70F12
	#define  HIGH_SPEED_DEVICE				(0)
#elif defined __MCF52277_H__
	#define  HIGH_SPEED_DEVICE				(1)
#else
	#define  HIGH_SPEED_DEVICE				(0)
#endif

#if (defined MCU_MK20D7) || (defined MCU_MK40D7)
	#define MCGOUTCLK_72_MHZ
#endif

#if ((defined __MK_xxx_H__)||(defined MCU_mcf51jf128))
	/* 1s between simulated key press events */
	#define  KEY_PRESS_SIM_TMR_INTERVAL		(1000)
#else
	#ifdef __MCF52277_H__
		#define  BUTTON_PRESS_SIMULATION	(1)
		/* 2s between simulated key press events */
		#define  KEY_PRESS_SIM_TMR_INTERVAL	(2000)		
	#endif
#endif

#if (defined __MK_xxx_H__) || defined(__MCF52259_H__) || defined(__MCF52221_H__) || defined(__MCF52277_H__)

#if !defined (MCU_MK20D5)
  #define USE_SDCARD							(1)
#endif

#endif

#if USE_SDCARD
	#define RAM_DISK_APP				(0)
	#define SD_CARD_APP					(1)
#else
	#define RAM_DISK_APP				(1)
	#define SD_CARD_APP					(0)
#endif
#define LONG_SEND_TRANSACTION       /* support to send large data pkts */
#define LONG_RECEIVE_TRANSACTION    /* support to receive large data pkts */

#if (defined __MK_xxx_H__)
#define USE_SDHC_PROTOCOL					(0)
#define USE_SPI_PROTOCOL					(1)
// #define USB_LOWPOWERMODE /* This MACRO enables STOP3 Mode Transition */  
#elif defined(__MCF52259_H__) || defined(__MCF52221_H__) || defined(__MCF52277_H__)
#define USE_SDHC_PROTOCOL					(0)
#define USE_SPI_PROTOCOL					(1)
#endif

#define MAX_TIMER_OBJECTS					(5)

#define MSD_RECEIVE_BUFFER_SIZE				(512)
#define MSD_SEND_BUFFER_SIZE				(512)

/* Don't Change this definition*/
#define USB_PACKET_SIZE						uint_32 

#ifndef _MCF51JM128_H
/* Use double buffered endpoints 5 & 6. To be only used with S08 cores */
#define DOUBLE_BUFFERING_USED
#endif
