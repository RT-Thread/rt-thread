//*****************************************************************************
//
// uip-conf.h - uIP configuration for the boot loader.
//
// Copyright (c) 2007-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#ifndef __UIP_CONF_H__
#define __UIP_CONF_H__

//*****************************************************************************
//
// This typedef defines the 8-bit type used throughout uIP.
//
//*****************************************************************************
typedef unsigned char   u8_t;

//*****************************************************************************
//
// This typedef defines the 16-bit type used throughout uIP.
//
//*****************************************************************************
typedef unsigned short   u16_t;

//*****************************************************************************
//
// This typedef defines the dataype used for keeping statistics in uIP.
//
//*****************************************************************************
typedef unsigned short uip_stats_t;

//*****************************************************************************
//
// Turn off TCP support.
//
//*****************************************************************************
#define UIP_CONF_TCP            0

//*****************************************************************************
//
// Turn on UDP support.
//
//*****************************************************************************
#define UIP_CONF_UDP            1

//*****************************************************************************
//
// Only support a single UDP connection.
//
//*****************************************************************************
#define UIP_CONF_UDP_CONNS      1

//*****************************************************************************
//
// Only support a single entry in the ARP table.
//
//*****************************************************************************
#define UIP_CONF_ARPTAB_SIZE    1

//*****************************************************************************
//
// Set the size of the uIP packet data buffer.
//
//*****************************************************************************
#define UIP_CONF_BUFFER_SIZE    1600//700

//*****************************************************************************
//
// Enable UDP broadcast support.
//
//*****************************************************************************
#define UIP_CONF_BROADCAST      1

//*****************************************************************************
//
// Define a data type for the UDP application state.  This is not used, but
// must be defined for uIP.
//
//*****************************************************************************
typedef unsigned int uip_udp_appstate_t;
typedef unsigned int uip_tcp_appstate_t;

//*****************************************************************************
//
// The name of the function to be called when UDP packets arrive, or when the
// UDP periodic timer expires.
//
//*****************************************************************************
extern char BOOTPThread(void);
extern char NULLThread(void);
#define UIP_UDP_APPCALL         BOOTPThread
#define UIP_APPCALL             NULLThread

#endif // __UIP_CONF_H__
