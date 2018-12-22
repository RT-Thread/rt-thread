/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file virtual_com.h
 *
 * @author 
 *
 * @version 
 *
 * @date May-28-2009
 *
 * @brief The file contains Macro's and functions required for Virtual COM  
 *        Loopback Application
 *
 *****************************************************************************/

#ifndef _VIRTUAL_COM_H
#define _VIRTUAL_COM_H

#include "types.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define  CONTROLLER_ID      (0)   /* ID to identify USB CONTROLLER */ 

#define  KBI_STAT_MASK      (0x0F)

/* 
   DATA_BUFF_SIZE should be greater than or equal to the endpoint buffer size, 
   otherwise there will be data loss. For MC9S08JS16, maximum DATA_BUFF_SIZE 
   supported is 16 Bytes
*/
#ifndef _MC9S08JS16_H
#define  DATA_BUFF_SIZE     (64)
#else
#define  DATA_BUFF_SIZE     (16)
#endif

/*****************************************************************************
 * Global variables
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void TestApp_Init(void);
extern void TestApp_Task(void);

#endif 
