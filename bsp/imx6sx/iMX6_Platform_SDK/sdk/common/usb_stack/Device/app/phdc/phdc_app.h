/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file phdc_app.h
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains Macro's and functions needed by the PHDC Application
 *
 *****************************************************************************/

#ifndef _PHDC_APP_H
#define _PHDC_APP_H

#include "types.h"
#include "usb_phdc.h"
/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define  KBI_STAT_MASK      (0x0F)

#if(defined __MCF52259_H__) 
#if(defined(__MCF52259_DEMO_) || defined(__MCF52221_H__))
	 #define SEND_MEASUREMENT_INT     (0x02)
	 #define SEND_MEASUREMENT_BULK    (0x08) 
	 #define DISCONNECT               (0x04)
#else
	 #define SEND_MEASUREMENT_INT     (0x02)
	 #define SEND_MEASUREMENT_BULK    (0x04)
	 #define DISCONNECT               (0x08)
#endif
#else
 #define SEND_MEASUREMENT_INT     (0x01)
 #define SEND_MEASUREMENT_BULK    (0x02)
 #define DISCONNECT               (0x04)
#endif 

#define CONTROLLER_ID       (0)         /* Controller ID */

#define SELECT_TIMEOUT      3000    /* 3 Second Specialization Select Timeout*/

 /*****************************************************************************
 * Global variables
 *****************************************************************************/
extern uint_8 kbi_stat;
/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void TestApp_Init(void);
extern void TestApp_Task(void);
extern void PHD_Send_WSL_Measurements_to_Manager (
    uint_8 controller_ID,
    void* buffer_ptr,
    void* size
);

#endif
