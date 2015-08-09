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

#ifndef _WRITE_SD_DATA_H
#define _WRITE_SD_DATA_H

#include "types.h"
#include "user_config.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define USB_CONTROLLER_ID       (0)

    #define LENGTH_OF_EACH_LAB              (512)
                                            /* length of each logical address block */
    #define TOTAL_LOGICAL_ADDRESS_BLOCKS    (0x010000)
                                            /* total number of logical blocks present */
    #define DISK_SIZE                       (LENGTH_OF_EACH_LAB * TOTAL_LOGICAL_ADDRESS_BLOCKS)
#define LOGICAL_UNIT_SUPPORTED              (1)
#define BUFER_SIZE BLOCK_SIZE

#pragma pack(1)

typedef struct _disk_variable_struct
{
    uint_8 app_controller_ID;
    boolean start_app;
    /* disk space reserved */
    uint_8 storage_disk[10];
    uint_8 disk_lock; 
}DISK_GLOBAL_VARIABLE_STRUCT, *PTR_DISK_GLOBAL_VARIABLE_STRUCT; 

#define  FLASH_IMAGE_SUCCESS    0
#define  FLASH_IMAGE_ERROR      1

/* Bootloader Status */
#define BootloaderReady         0
#define BootloaderS19Error      1
#define BootloaderFlashError    2
#define BootloaderSuccess       3
#define BootloaderStarted       4

/*****************************************************************************
 * Global variables
 *****************************************************************************/

/*****************************************************************************
 * Global Functions
 *****************************************************************************/
void Disk_App(void);
void USB_MSD_App_Callback(uint_8 controller_ID,uint_8 event_type,void* val);
void MSD_Event_Callback(uint_8 controller_ID,uint_8 event_type,void* val);

#endif 
