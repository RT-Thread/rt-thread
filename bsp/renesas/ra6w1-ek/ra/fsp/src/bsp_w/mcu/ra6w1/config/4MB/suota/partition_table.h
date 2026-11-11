/**
 ****************************************************************************************
 *
 * @file 4MB/suota/partition_table.h
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

/* $code_snippet START suota_4MB_flash_partition_table */

#define NVMS_PRODUCT_HEADER_PART_START    SF_BASE_ADDR
#define NVMS_PRODUCT_HEADER_PART_SIZE     (SF_PRODUCT_HDR_SIZE * 2) // Header + Header-Backup
#define NVMS_FW_EXEC_PART_START           SF_RTOS_0                 /* Alignment to 512KB is dictated by the default FLASH_REGION_SIZE. */
#define NVMS_FW_EXEC_PART_SIZE            SF_RTOS_SIZE

#define NVMS_LOG_PART_START               SF_TLS_CERT_BASE_ADDR
#define NVMS_LOG_PART_SIZE                SF_TLS_AREA_SIZE

#define NVMS_GENERIC_PART_START           SF_NVRAM_AREA
#define NVMS_GENERIC_PART_SIZE            (SF_NVRAM_SIZE * AD_NVMS_VES_MULTIPLIER)

/* +------------------ 2 MB ---------------------+ */

#define NVMS_FW_UPDATE_PART_START         SF_RTOS_1 /* Alignment to 512KB is dictated by the default FLASH_REGION_SIZE. */
#define NVMS_FW_UPDATE_PART_SIZE          SF_RTOS_SIZE
#define NVMS_BIN_PART_START               SF_USER_AREA
#define NVMS_BIN_PART_SIZE                SF_USER_AREA_SIZE

#define NVMS_PARTITION_TABLE_START        SF_PARTITION_TBL
#define NVMS_PARTITION_TABLE_SIZE         SF_PARTITION_TBL_SIZE /* Recommended location, 4KB before the end of the flash. */

/* +------------------ 4 MB ---------------------+ */

/*
 * Partition information
 */
PARTITION2(NVMS_PRODUCT_HEADER_PART, 0)                    // Product Header
PARTITION2(NVMS_FW_EXEC_PART, 0)                           // RTOS #0
PARTITION2(NVMS_LOG_PART, 0)                               // User Area #0 or TLS certificates
PARTITION2(NVMS_GENERIC_PART, PARTITION_FLAG_VES)          // NVRAM
PARTITION2(NVMS_FW_UPDATE_PART, 0)                         // RTOS #1
PARTITION2(NVMS_BIN_PART, 0)                               // User Area #1
PARTITION2(NVMS_PARTITION_TABLE, PARTITION_FLAG_READ_ONLY) // Partition Table

/* $code_snippet END */
