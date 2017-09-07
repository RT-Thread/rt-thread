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
 * @date
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

#define SEND_MEASUREMENT    (0x02)
#ifndef __MCF52221_H__
	#define DISCONNECT          (0x04)
	#define SELECT_DEVICE_SPEC  (0x08)
#else
	#define SELECT_DEVICE_SPEC  (0x04)
	#define DISCONNECT          (0x08)
#endif

#define CONTROLLER_ID       (0)         /* Controller ID */

#define SELECT_TIMEOUT      800    /* 3 Second Specialization Select Timeout*/

 /*****************************************************************************
 * Global variables
 *****************************************************************************/
extern uint_8 kbi_stat;
/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void TestApp_Init(void);
extern void TestApp_Task(void);

#endif
