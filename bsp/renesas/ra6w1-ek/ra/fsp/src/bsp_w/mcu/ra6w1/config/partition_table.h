/**
 ****************************************************************************************
 *
 * @file ra6w1/config/partition_table.h
 *
 * @brief Partition table selection. Image partition's size definition.
 *
 * Copyright (c) 2023 Renesas Electronics. All rights reserved.
 *
 * This software ("Software") is owned by Renesas Electronics.
 *
 * By using this Software you agree that Renesas Electronics retains all
 * intellectual property and proprietary rights in and to this Software and any
 * use, reproduction, disclosure or distribution of the Software without express
 * written permission or a license agreement from Renesas Electronics is
 * strictly prohibited. This Software is solely for use on or in conjunction
 * with Renesas Electronics products.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE
 * SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. EXCEPT AS OTHERWISE
 * PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * RENESAS ELECTRONICS BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 *
 ****************************************************************************************
 */

/*
 * When partition_table is not overridden by adding a custom partition_table.h file to a project
 * then this file is used to select partition table by macro definition.
 *
 * To use layout other than SDK one, add include path into the project settings that will point
 * to a folder with the custom partition_table file.
 */

#if ((DEVICE_FAMILY == DA1640X))

 #if defined(RENESAS_AT25SL_8MB_OTA)
  #include "8MB/at25sl/suota/partition_table.h"
 #elif defined(RENESAS_AT25SL_8MB)
  #include "8MB/at25sl/partition_table.h"
 #elif defined(NORMAL_4MB_OTA)
  #include "4MB/suota/partition_table.h"
 #elif defined(NORMAL_4MB)
  #include "4MB/partition_table.h"
 #elif defined(NORMAL_8MB_OTA)
  #include "8MB/suota/partition_table.h"
 #elif defined(NORMAL_8MB)
  #include "8MB/partition_table.h"
 #else
  #if defined OS_BAREMETAL
   #include "4MB/default_partition_table.h"
  #else
   #error "Not defined SFLASH partition !!!"
  #endif
 #endif

#else

 #include "4MB/partition_table.h"      // Temporary ... for FPGA

#endif /* DEVICE_FAMILY */

/*
 * Define a maximal size of the image which could be written to QSPI - based on the partition sizes.
 */

#if defined(NVMS_FW_EXEC_PART_SIZE) && defined(NVMS_FW_UPDATE_PART_SIZE) // for dual image by OTA

 #if (NVMS_FW_EXEC_PART_SIZE < NVMS_FW_UPDATE_PART_SIZE)
  #define IMAGE_PARTITION_SIZE    NVMS_FW_EXEC_PART_SIZE
 #else
  #define IMAGE_PARTITION_SIZE    NVMS_FW_UPDATE_PART_SIZE
 #endif                                /* NVMS_FW_EXEC_PART_SIZE < NVMS_FW_UPDATE_PART_SIZE */

#elif defined(NVMS_FIRMWARE_PART_SIZE) // for single image

 #define IMAGE_PARTITION_SIZE     NVMS_FIRMWARE_PART_SIZE

#else
 #error "At least one partition where application could be placed should be defined!"
#endif                                 /* defined(NVMS_FW_EXEC_PART_SIZE) && defined(NVMS_FW_UPDATE_PART_SIZE) */

/* EOF */
