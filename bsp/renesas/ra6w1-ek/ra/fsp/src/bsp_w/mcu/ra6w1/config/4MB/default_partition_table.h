/**
 ****************************************************************************************
 *
 * @file ra6w1/config/4MB/default_partition_table.h
 *
 * @brief Partition map for RA6W1 4MB SFLASH
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

/* $code_snippet START table_partition */

#define NVMS_PRODUCT_HEADER_PART_START     0x000000
#define NVMS_PRODUCT_HEADER_PART_SIZE      0x002000
#define NVMS_FIRMWARE_PART_START           0x002000 /* Alignment to 512KB is dictated by the default FLASH_REGION_SIZE. */
#define NVMS_FIRMWARE_PART_SIZE            0x1FE000

/* +------------------2MB---------------------+ */

#define NVMS_GENERIC_PART_START            0x200000
#define NVMS_GENERIC_PART_SIZE             0x020000
#define NVMS_PLATFORM_PARAMS_PART_START    0x220000
#define NVMS_PLATFORM_PARAMS_PART_SIZE     0x07F000
#define NVMS_PARAM_PART_START              0x29F000
#define NVMS_PARAM_PART_SIZE               0x001000 /* Recommended location, 4KB before the end of the 1st flash section. */

/* +------------------2MB---------------------+ */

#define NVMS_LOG_PART_START                0x2A0000
#define NVMS_LOG_PART_SIZE                 0x070000
#define NVMS_BIN_PART_START                0x310000
#define NVMS_BIN_PART_SIZE                 0x0EF000
#define NVMS_PARTITION_TABLE_START         0x3FF000
#define NVMS_PARTITION_TABLE_SIZE          0x001000 /* Recommended location, 4KB before the end of the flash. */
#ifdef NVMS_QSPI_TEST_PART
 #define NVMS_QSPI_TEST_PART_START         (QSPI_MEM1_VIRTUAL_BASE_ADDR + 0x000000)
 #define NVMS_QSPI_TEST_PART_SIZE          0x080000
#endif  /* NVMS_QSPI_TEST_PART */

PARTITION2(NVMS_PRODUCT_HEADER_PART, 0)
PARTITION2(NVMS_FIRMWARE_PART, 0)
PARTITION2(NVMS_GENERIC_PART, PARTITION_FLAG_VES)
PARTITION2(NVMS_PLATFORM_PARAMS_PART, PARTITION_FLAG_READ_ONLY)
PARTITION2(NVMS_PARAM_PART, 0)
PARTITION2(NVMS_LOG_PART, 0)
PARTITION2(NVMS_BIN_PART, 0)
PARTITION2(NVMS_PARTITION_TABLE, PARTITION_FLAG_READ_ONLY)
#ifdef NVMS_QSPI_TEST_PART
PARTITION2(NVMS_QSPI_TEST_PART, PARTITION_FLAG_VES)
#endif                                 /* NVMS_QSPI_TEST_PART */

/* $code_snippet END */
