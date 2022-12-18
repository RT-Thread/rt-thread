/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_RUN_BOOTLOADER_H_
#define _FSL_RUN_BOOTLOADER_H_

#include "fsl_common.h"

/*!
 * @addtogroup runbootloader
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*   API prototype fields definition.
| 31 : 24  	|    23 : 20    	|     19 : 16        |  15 : 12             |  11 : 8     |  7 ： 0  |
    |     Tag  	|   Boot mode   	| bootloader periphal|  Instance            |  Image Index| Reserved  |
|           | 			    	|					 |  Used For Boot mode 0|             |           |
|			| 0: Passive mode   | 0 - Auto detection |            		    |             |           |
|			| 1: ISP mode   	| 1 - USB-HID        |            		    |             |           |
|			|					| 2 - UART           |            		    |             |           |
|			|					| 3 - SPI            |            		    |             |           |
|			|					| 4 - I2C            |            		    |             |           |
|			|					| 5 - CAN		     |            		    |             |           |
*/

typedef struct
{
    union
    {
        struct
        {
            uint32_t reserved : 8;
            uint32_t boot_image_index : 4;
            uint32_t instance : 4;
            uint32_t boot_interface : 4;
            uint32_t mode : 4;
            uint32_t tag : 8;
        } B;
        uint32_t U;
    } option;
} user_app_boot_invoke_option_t;

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Run the Bootloader API  to force into the ISP mode base on the user arg
 *
 * @param arg Indicates API prototype fields definition. Refer to the above user_app_boot_invoke_option_t structure
 */
void bootloader_user_entry(void *arg);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _FSL_RUN_BOOTLOADER_H_ */
