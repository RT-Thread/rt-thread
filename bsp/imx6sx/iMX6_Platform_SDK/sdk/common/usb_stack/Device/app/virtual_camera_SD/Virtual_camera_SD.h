/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file virtual_camera.h
 *
 * @author 
 *
 * @version 
 *
 * @date Jul-20-2010
 *
 * @brief The file contains Macro's and functions required for Virtual Camera
 *        Loopback Application
 *
 *****************************************************************************/

#ifndef _VIRTUAL_CAMERA_H
#define _VIRTUAL_CAMERA_H

#include "types.h"
#include "user_config.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define  CONTROLLER_ID      (0)   /* ID to identify USB CONTROLLER */ 

#define  KBI_STAT_MASK      (0x0F)

/*****************************************************************************
 * Global variables
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void TestApp_Init(void);

#define HEADER_PACKET_SIZE 12

#endif
