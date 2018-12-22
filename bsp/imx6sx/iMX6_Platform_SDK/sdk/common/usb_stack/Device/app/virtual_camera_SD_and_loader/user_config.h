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
 * @brief The file contains User Modifiable Macros for Generator Application
 *
 *****************************************************************************/
#include "derivative.h"

#if defined( __MCF52277_H__) || defined( MCU_mcf51jf128)
#define  HIGH_SPEED_DEVICE            (1) 
#define  BUTTON_PRESS_SIMULATION      (1)
#define  KEY_PRESS_SIM_TMR_INTERVAL   (2000)    /* 2s between simulated key press events */
#else
#define  HIGH_SPEED_DEVICE            (0)
#endif

#define MULTIPLE_DEVICES

/* Below two MACROS are required for Generator Application to execute */
#define LONG_SEND_TRANSACTION       /* support to send large data pkts */
#define LONG_RECEIVE_TRANSACTION    /* support to receive large data pkts */

/* User Defined MACRO to set number of Timer Objects */
#define MAX_TIMER_OBJECTS           3

#if MAX_TIMER_OBJECTS
/* When Enabled Timer Callback is invoked with an argument */
#define TIMER_CALLBACK_ARG
#undef TIMER_CALLBACK_ARG
#endif

#if defined (__MK_xxx_H__) || defined(__MCF52259_H__) || defined(__MCF52221_H__) || defined(__MCF52277_H__)
#define USE_SDHC_PROTOCOL					(0)
#define USE_SPI_PROTOCOL					(1)
#endif

#ifndef _MC9S08JS16_H
#define USB_PACKET_SIZE  uint_32    /* support 16/32 bit packet size */
#else
#define USB_PACKET_SIZE  uint_8     /* support 8 bit packet size */
#endif
#ifndef _MCF51JM128_H
/* Use double buffered endpoints 5 & 6. To be only used with S08 cores */
#define DOUBLE_BUFFERING_USED
#endif

#define MSD_RECEIVE_BUFFER_SIZE       (512)
#define MSD_SEND_BUFFER_SIZE          (512)

/* Select video data source */
#define USE_TERMINATOR_VIDEO 1
#define USE_SKI_VIDEO        0

