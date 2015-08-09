/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 **************************************************************************//*!
 *
 * @file disk.h
 *
 * @author 
 *
 * @version 
 *
 * @date May-08-2009
 *
 * @brief The file contains Macro's and functions needed by the disk 
 *        application
 *
 *****************************************************************************/


#ifndef _DISK_H
#define _DISK_H  1

#include "user_config.h"
#include "usb_msc.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define USB_CONTROLLER_ID       (0)

    #define LENGTH_OF_EACH_LAB              (512)
                                            /* length of each logical address block */
    #define TOTAL_LOGICAL_ADDRESS_BLOCKS    (0x080000)
                                            /* total number of logical blocks present */
    #define DISK_SIZE                       (LENGTH_OF_EACH_LAB * TOTAL_LOGICAL_ADDRESS_BLOCKS)


#define LOGICAL_UNIT_SUPPORTED              (1)

/* Bootloader Status */
#define BootloaderReady         0
#define BootloaderS19Error      1
#define BootloaderFlashError    2
#define BootloaderSuccess       3
#define BootloaderStarted       4

#define  FLASH_IMAGE_SUCCESS    0
#define  FLASH_IMAGE_ERROR      1
/*****************************************************************************
 * Global variables
 *****************************************************************************/
 
/******************************************************************************
 * Types
 *****************************************************************************/
#pragma pack(1)

typedef struct _disk_variable_struct
{
    uint_8 app_controller_ID;
    boolean start_app;
    /* disk space reserved */ 
    uint_8 storage_disk[512]; 
    uint_8 disk_lock;
}DISK_GLOBAL_VARIABLE_STRUCT, *PTR_DISK_GLOBAL_VARIABLE_STRUCT; 

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern void TestApp_Init(void);
extern void TestApp_Task(void);
extern void Disk_App(void);

#endif
extern uint_8 S19FileDone;
extern unsigned char BootloaderStatus;
extern unsigned char ReEnumerateNow;
/************************************************************************************
*************************************************************************************
*                                    Functions                                      *
*************************************************************************************
************************************************************************************/

/* EOF */
