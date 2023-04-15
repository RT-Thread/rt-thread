/***************************************************************************//**
* \file cy_smif_memslot.h
* \version 2.40
*
* \brief
*  This file provides the constants and parameter values for the memory-level
*  APIs of the SMIF driver.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2016-2022 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#if !defined (CY_SMIF_MEMORYSLOT_H)
#define CY_SMIF_MEMORYSLOT_H

#include "cy_device.h"

#if defined (CY_IP_MXSMIF)

#include <stdint.h>
#include <stdbool.h>
#include "cy_syslib.h"
#include "cy_smif.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_smif_macros_status
* \{
*/

/***************************************
*            Constants
****************************************/
#define CY_SMIF_DEVICE_BUSY        (1U)    /**< The external memory is busy */
#define CY_SMIF_DEVICE_READY       (0U)    /**< The external memory is ready */

/** \} group_smif_macros_status */

/**
* \addtogroup group_smif_macros_cmd
* \{
*/
#define CY_SMIF_CMD_WITHOUT_PARAM  (0U)    /**< No parameter */
#define CY_SMIF_TX_LAST_BYTE       (1U)    /**< The last byte in the command transmission
                                            * (SS is set high after the transmission)
                                            */
#define CY_SMIF_TX_NOT_LAST_BYTE   (0U)     /**< Not the last byte in the command transmission
                                            * (SS remains low after the transmission)
                                            */
#define CY_SMIF_READ_ONE_BYTE      (1U)     /**< Read 1 byte */
#define CY_SMIF_WRITE_ONE_BYTE     (1U)     /**< Write 1 byte */
#define CY_SMIF_WRITE_TWO_BYTES    (2U)     /**< Write 2 bytes */
#define CY_SMIF_ONE_WORD           (4U)     /**< 4 bytes */

#define CY_SMIF_DUAL_QUAD_DISABLED (0U)     /**< The dual quad transmission mode is disabled */
#define CY_SMIF_DUAL_QUAD_ENABLED  (1U)     /**< The dual quad transmission mode is enabled */


/** \} group_smif_macros_status */

/**
* \addtogroup group_smif_macros_flags
* \{
*/

#define CY_SMIF_FLAG_ALL_DISABLED       (0U) /**< All memory configuration flags are disabled */
/** Enables the write capability for the memory slave in the memory-mapped
 * mode. Valid when the memory-mapped mode is enabled */
#define CY_SMIF_FLAG_WRITE_ENABLE       (1U)
/** Determines if the device is memory-mapped. If enabled, this memory slot will
 * be initialized in System init */
#define CY_SMIF_FLAG_MEMORY_MAPPED      (2U)
#define CY_SMIF_FLAG_DETECT_SFDP        (4U) /**< Enables the Autodetect using the SFDP */
/** Enables the crypto support for this memory slave. All access to the
* memory device goes through the encryption/decryption
* Valid when the memory-mapped mode is enabled */
#define CY_SMIF_FLAG_CRYPTO_ENABLE      (8U)

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
/**
* \note
* This macro is available for CAT1B, CAT1C and CAT1D devices.
**/
/** Enables IP version 3 features such as octal SPI/DDR mode/ 2 byte addressing
*/
#define CY_SMIF_FLAG_SMIF_REV_3      (16U)

/** Continuous transfer merge enable.
* This skips the overhead (command, address, mode, dummy cycles) for a continuous
* (linear sequential) transfer. */
#define CY_SMIF_FLAG_MERGE_ENABLE     (32U)

#endif /* CY_IP_MXSMIF_VERSION */

/** \} group_smif_macros_flags */

/**
* \addtogroup group_smif_macros_sfdp
* \{
*/

/***************************************
*            SFDP constants
****************************************/
#define CY_SMIF_SFDP_ADDRESS_LENGTH                 (0x03U)                 /**< The length of the SFDP address */
#define CY_SMIF_SFDP_PARAM_HEADER_LENGTH            (0x8U)                  /**< The length of the Parameter header */
#define CY_SMIF_SFDP_PARAMETER_TABLE_LENGTH         (0x80U)                 /**< The length of the Parameter table */
#define CY_SMIF_SFDP_LENGTH                         (CY_SMIF_SFDP_PARAMETER_TABLE_LENGTH) /**< The length of the SFDP */
#define CY_SMIF_SFDP_SIGNATURE_BYTE_00              (0x00U)                 /**< The SFDP Signature byte 0x00. Should be "S" */
#define CY_SMIF_SFDP_SIGNATURE_BYTE_01              (0x01U)                 /**< The SFDP Signature byte 0x01. Should be "F" */
#define CY_SMIF_SFDP_SIGNATURE_BYTE_02              (0x02U)                 /**< The SFDP Signature byte 0x02. Should be "D" */
#define CY_SMIF_SFDP_SIGNATURE_BYTE_03              (0x03U)                 /**< The SFDP Signature byte 0x03. Should be "P" */
#define CY_SMIF_SFDP_MINOR_REV                      (0x04U)                 /**< The SFDP Header byte 0x04. Defines the JEDEC JESD216 Revision */
#define CY_SMIF_SFDP_MAJOR_REV                      (0x05U)                 /**< The SFDP Header byte 0x05. Defines the SFDP Major Revision */
#define CY_SMIF_SFDP_MAJOR_REV_1                    (0x01U)                 /**< The SFDP Major Revision is 1 */
#define CY_SMIF_SFDP_JEDEC_REV_0                    (0x00U)                 /**< The JEDEC JESD216 Revision is 0 */
#define CY_SMIF_SFDP_JEDEC_REV_B                    (0x06U)                 /**< The JEDEC JESD216 Revision is B */
#define CY_SMIF_SFDP_PARAM_TABLE_PTR                (0x0CU)                 /**< Specifies the start of the JEDEC Basic Flash
                                                                            * Parameter Table in the SFDP structure
                                                                            */
#define CY_SMIF_SFDP_THREE_BYTES_ADDR_CODE          (0x00U)                 /**< Code for the SFDP Address Bytes Number 3 */
#define CY_SMIF_SFDP_THREE_OR_FOUR_BYTES_ADDR_CODE  (0x01U)                 /**< Code for the SFDP Address Bytes Number 3 or 4 */
#define CY_SMIF_SFDP_FOUR_BYTES_ADDR_CODE           (0x02U)                 /**< Code for the SFDP Address Bytes Number 4 */
#define CY_SMIF_THREE_BYTES_ADDR                    (0x03U)                 /**< The address Bytes Number is 3 */
#define CY_SMIF_FOUR_BYTES_ADDR                     (0x04U)                 /**< The address Bytes Number is 4 */
#define CY_SMIF_READ_MODE_BYTE                      (0x5AU)                 /**< The mode byte for the SMIF read */
#define CY_SMIF_WRITE_STATUS_REG1_CMD               (0x01U)                 /**< The write status register 1 command */
#define CY_SMIF_SINGLE_PROGRAM_CMD                  (0x02U)                 /**< The command for a single SMIF program */
#define CY_SMIF_SINGLE_READ_CMD                     (0x03U)                 /**< The command for a single SMIF read */
#define CY_SMIF_WRITE_DISABLE_CMD                   (0x04U)                 /**< The Write Disable command */
#define CY_SMIF_READ_STATUS_REG1_CMD                (0x05U)                 /**< The read status register 1 command */
#define CY_SMIF_WRITE_ENABLE_CMD                    (0x06U)                 /**< The Write Enable command */
#define CY_SMIF_READ_STATUS_REG2_T1_CMD             (0x35U)                 /**< The read status register 2 type 1 command */
#define CY_SMIF_WRITE_STATUS_REG2_T1_CMD            (0x3EU)                 /**< The write status register 2 type 1 command */
#define CY_SMIF_WRITE_STATUS_REG2_T2_CMD            (0x31U)                 /**< The write status register 2 type 2 command */
#define CY_SMIF_READ_STATUS_REG2_T2_CMD             (0x3FU)                 /**< The read status register 2 type 2 command */
#define CY_SMIF_CHIP_ERASE_CMD                      (0x60U)                 /**< The Chip Erase command */
#define CY_SMIF_POWER_DOWN_CMD                      (0xB9U)                 /**< The Power-down command */
#define CY_SMIF_RELEASE_POWER_DOWN_CMD              (0xABU)                 /**< The Release Power-down command */
#define CY_SMIF_QE_BIT_STATUS_REG2_T1               (0x02U)                 /**< The QE bit is in status register 2 type 1.
                                                                            * It should be written as the second byte.
                                                                            */
#define CY_SMIF_FAST_READ_4_BYTES_CMD_1S_1S_1S      (0x0CU)                 /**< The command for a 1S-1S-1S SMIF fast read with 4-byte addressing */
#define CY_SMIF_FAST_READ_4_BYTES_CMD_1S_1S_2S      (0x3CU)                 /**< The command for a 1S-1S-2S SMIF fast read with 4-byte addressing */
#define CY_SMIF_FAST_READ_4_BYTES_CMD_1S_2S_2S      (0xBCU)                 /**< The command for a 1S-2S-2S SMIF fast read with 4-byte addressing */
#define CY_SMIF_FAST_READ_4_BYTES_CMD_1S_1S_4S      (0x6CU)                 /**< The command for a 1S-1S-4S SMIF fast read with 4-byte addressing */
#define CY_SMIF_FAST_READ_4_BYTES_CMD_1S_4S_4S      (0xECU)                 /**< The command for a 1S-4S-4S SMIF fast read with 4-byte addressing */
#define CY_SMIF_FAST_READ_4_BYTES_CMD_1S_1S_8S      (0x7CU)                 /**< The command for a 1S-1S-8S SMIF fast read with 4-byte addressing */
#define CY_SMIF_FAST_READ_4_BYTES_CMD_1S_8S_8S      (0xCCU)                 /**< The command for a 1S-8S-8S SMIF fast read with 4-byte addressing */

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
/**
* \note
* This macro is available for CAT1B, CAT1C and CAT1D devices.
**/
#define CY_SMIF_FAST_READ_4_BYTES_CMD_1S_4D_4D      (0xEEU)                 /**< The command for a 1S-4D-4D SMIF fast read with 4-byte addressing */
#define CY_SMIF_FAST_READ_4_BYTES_CMD_1S_8D_8D      (0xFDU)                 /**< The command for a 1S-8D-8D SMIF fast read with 4-byte addressing */
#endif /* CY_IP_MXSMIF_VERSION */

#define CY_SMIF_PAGE_PROGRAM_4_BYTES_CMD_1S_1S_1S   (0x12U)                 /**< The command for a 1S-1S-1S SMIF page program with 4-byte addressing */
#define CY_SMIF_PAGE_PROGRAM_4_BYTES_CMD_1S_1S_4S   (0x34U)                 /**< The command for a 1S-1S-4S SMIF page program with 4-byte addressing */
#define CY_SMIF_PAGE_PROGRAM_4_BYTES_CMD_1S_4S_4S   (0x3EU)                 /**< The command for a 1S-4S-4S SMIF page program with 4-byte addressing */
#define CY_SMIF_PAGE_PROGRAM_4_BYTES_CMD_1S_1S_8S   (0x84U)                 /**< The command for a 1S-1S-8S SMIF page program with 4-byte addressing */
#define CY_SMIF_PAGE_PROGRAM_4_BYTES_CMD_1S_8S_8S   (0x8EU)                 /**< The command for a 1S-8S-8S SMIF page program with 4-byte addressing */

#define CY_SMIF_BRWR_EXTADD_MASK                    (0x80U)                 /**< The Extended Address Enable (EXTADD) mask */

#define CY_SMIF_SFDP_ERASE_TIME_1MS                 (1U)                    /**< Units of Erase Typical Time in ms */
#define CY_SMIF_SFDP_ERASE_TIME_16MS                (16U)                   /**< Units of Erase Typical Time in ms */
#define CY_SMIF_SFDP_ERASE_TIME_128MS               (128U)                  /**< Units of Erase Typical Time in ms */
#define CY_SMIF_SFDP_ERASE_TIME_1S                  (1000U)                 /**< Units of Erase Typical Time in ms */

#define CY_SMIF_SFDP_CHIP_ERASE_TIME_16MS           (16U)                   /**< Units of Chip Erase Typical Time in ms */
#define CY_SMIF_SFDP_CHIP_ERASE_TIME_256MS          (256U)                  /**< Units of Chip Erase Typical Time in ms */
#define CY_SMIF_SFDP_CHIP_ERASE_TIME_4S             (4000U)                 /**< Units of Chip Erase Typical Time in ms */
#define CY_SMIF_SFDP_CHIP_ERASE_TIME_64S            (64000U)                /**< Units of Chip Erase Typical Time in ms */

#define CY_SMIF_SFDP_PROG_TIME_8US                  (8U)                    /**< Units of Page Program Typical Time in us */
#define CY_SMIF_SFDP_PROG_TIME_64US                 (64U)                   /**< Units of Page Program Typical Time in us */

#define CY_SMIF_SFDP_PROG_TIME_DEFAULT              (100000U)               /**< Default Page Program Time in us - 100 ms */
#define CY_SMIF_SFDP_PAGE_SIZE_DEFAULT              (256U)                  /**< Default Page size used for SFDP 1.0 devices */

#define CY_SMIF_SFDP_UNIT_0                         (0U)                    /**< Units of Basic Flash Parameter Table Time Parameters */
#define CY_SMIF_SFDP_UNIT_1                         (1U)                    /**< Units of Basic Flash Parameter Table Time Parameters */
#define CY_SMIF_SFDP_UNIT_2                         (2U)                    /**< Units of Basic Flash Parameter Table Time Parameters */
#define CY_SMIF_SFDP_UNIT_3                         (3U)                    /**< Units of Basic Flash Parameter Table Time Parameters */


#define CY_SMIF_STATUS_REG_BUSY_MASK                (0x01U)                 /**< The busy mask for the status registers */
#define CY_SMIF_NO_COMMAND_OR_MODE                  (0xFFFFFFFFUL)          /**< No command or mode present */
#define CY_SMIF_SFDP_QE_BIT_1_OF_SR_2               (0x02UL)                /**< The QE is bit 1 of the status register 2 */
#define CY_SMIF_SFDP_QE_BIT_6_OF_SR_1               (0x40UL)                /**< The QE is bit 6 of the status register 1 */
#define CY_SMIF_SFDP_QE_BIT_7_OF_SR_2               (0x80UL)                /**< The QE is bit 7 of the status register 2 */
#define CY_SMIF_SFDP_BFPT_BYTE_02                   (0x02U)                 /**< The byte 0x02 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_04                   (0x04U)                 /**< The byte 0x04 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_05                   (0x05U)                 /**< The byte 0x05 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_06                   (0x06U)                 /**< The byte 0x06 of the JEDEC Basic Flash Parameter Table:
                                                                             * number of Parameter Headers (zero based, 05h = 6 parameters)
                                                                             */
#define CY_SMIF_SFDP_BFPT_BYTE_08                   (0x08U)                 /**< The byte 0x08 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_09                   (0x09U)                 /**< The byte 0x09 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_0A                   (0x0AU)                 /**< The byte 0x0A of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_0B                   (0x0BU)                 /**< The byte 0x0B of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_0C                   (0x0CU)                 /**< The byte 0x0C of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_0D                   (0x0DU)                 /**< The byte 0x0D of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_0E                   (0x0EU)                 /**< The byte 0x0E of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_0F                   (0x0FU)                 /**< The byte 0x0F of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_1C                   (0x1CU)                 /**< The byte 0x1C of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_1D                   (0x1DU)                 /**< The byte 0x1D of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_23                   (0x23U)                 /**< The byte 0x23 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_28                   (0x28U)                 /**< The byte 0x28 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_3A                   (0x3AU)                 /**< The byte 0x3A of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_3C                   (0x3CU)                 /**< The byte 0x3C of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_3F                   (0x3FU)                 /**< The byte 0x3F of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_40                   (0x40U)                 /**< The byte 0x40 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_41                   (0x41U)                 /**< The byte 0x41 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_42                   (0x42U)                 /**< The byte 0x42 of the JEDEC Basic Flash Parameter Table */
#define CY_SMIF_SFDP_BFPT_BYTE_43                   (0x43U)                 /**< The byte 0x43 of the JEDEC Basic Flash Parameter Table */

#define CY_SMIF_SFDP_BFPT_ERASE_BYTE                (36U)                   /**< The byte 36 of the JEDEC Basic Flash Parameter Table */

#define CY_SMIF_JEDEC_BFPT_10TH_DWORD               (9U)                    /**< Offset to JEDEC Basic Flash Parameter Table: 10th DWORD  */
#define CY_SMIF_JEDEC_BFPT_11TH_DWORD               (10U)                   /**< Offset to JEDEC Basic Flash Parameter Table: 11th DWORD  */

#define CY_SMIF_SFDP_SCCR_MAP_BYTE_3B               (0x3BU)                 /**< DWORD-16 of SCCR Map SPI table */
#define CY_SMIF_SFDP_OCTAL_ENABLE_WRITE_CMD_Pos     (0U)                    /**< SCCR Map DWORD-16 Octal mode enable write command position */
#define CY_SMIF_SFDP_OCTAL_ENABLE_WRITE_CMD_Msk     (0xFFU)                 /**< SCCR Map DWORD-16 Octal mode enable write command mask */
#define CY_SMIF_SFDP_OCTAL_ENABLE_READ_CMD_Pos      (8U)                    /**< SCCR Map DWORD-16 Octal mode enable read command position */
#define CY_SMIF_SFDP_OCTAL_ENABLE_READ_CMD_Msk      (0xFF00U)               /**< SCCR Map DWORD-16 Octal mode enable read command mask */
#define CY_SMIF_SFDP_OCTAL_ENABLE_REG_ADDR_Pos      (16U)                   /**< SCCR Map DWORD-16 Octal mode enable register address position */
#define CY_SMIF_SFDP_OCTAL_ENABLE_REG_ADDR_Msk      (0xFF0000U)             /**< SCCR Map DWORD-16 Octal mode enable register address mask */
#define CY_SMIF_SFDP_OCTAL_ENABLE_BIT_Pos           (24U)                   /**< SCCR Map DWORD-16 Octal mode enable bit position */
#define CY_SMIF_SFDP_OCTAL_ENABLE_BIT_Msk           (0x7000000U)            /**< SCCR Map DWORD-16 Octal mode enable bit mask */
#define CY_SMIF_SFDP_OCTAL_ENABLE_USE_ADDRESS_Pos   (28U)                   /**< SCCR Map DWORD-16 Octal mode enable uses address to set/clear position */
#define CY_SMIF_SFDP_OCTAL_ENABLE_USE_ADDRESS_Msk   (0x10000000U)           /**< SCCR Map DWORD-16 Octal mode enable uses address to set/clear mask */
#define CY_SMIF_SFDP_OCTAL_ENABLE_BIT_SUPPORT_Pos   (31U)                   /**< SCCR Map DWORD-16 Octal mode enable bit support position */
#define CY_SMIF_SFDP_OCTAL_ENABLE_BIT_SUPPORT_Msk   (0x80000000U)           /**< SCCR Map DWORD-16 Octal mode enable bit support mask */

#define CY_SMIF_SFDP_SECTOR_MAP_CMD_OFFSET          (1UL)    /**< The offset for the detection command instruction in the Sector Map command descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_ADDR_LEN_OFFSET     (2UL)    /**< The offset for the detection command address length in the Sector Map command descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_REG_MSK_OFFSET      (3UL)    /**< The offset for the read data mask in the Sector Map command descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_REG_ADDR_OFFSET     (4UL)    /**< The offset for the detection command address in the Sector Map command descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_REGION_COUNT_OFFSET (2UL)    /**< The offset for the regions count in the Sector Map descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_CONFIG_ID_OFFSET    (2UL)    /**< The offset for the configuration ID in the Sector Map descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_SUPPORTED_ET_MASK   (0xFU)   /**< The mask for the supported erase type code in the Sector Map descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_ADDR_BYTES_Msk      (0xC0UL) /**< The mask for the configuration detection command address bytes in the Sector Map descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_ADDR_BYTES_Pos      (6UL)    /**< The position of the configuration detection command address bytes in the Sector Map descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_DUMMY_CYCLES_Msk    (0xFUL)  /**< The mask for the configuration detection command read latency cycles in the Sector Map descriptor */
#define CY_SMIF_SFDP_SECTOR_MAP_DUMMY_CYCLES_Pos    (0UL)    /**< The position of the configuration detection command read latency cycles in the Sector Map descriptor */

#define FOUR_BYTE_ADDRESS_TABLE_BYTE_0              (0U)     /**< Byte 0x00 of the JEDEC 4-byte Address Instruction Table */
#define FOUR_BYTE_ADDRESS_TABLE_BYTE_1              (1U)     /**< Byte 0x01 of the JEDEC 4-byte Address Instruction Table */


/* ----------------------------  1st DWORD  ---------------------------- */
#define CY_SMIF_SFDP_FAST_READ_1_1_4_Pos            (6UL)                   /**< The SFDP 1-1-4 fast read support (Bit 6)               */
#define CY_SMIF_SFDP_FAST_READ_1_1_4_Msk            (0x40UL)                /**< The SFDP 1-1-4 fast read support (Bitfield-Mask: 0x01) */
#define CY_SMIF_SFDP_FAST_READ_1_4_4_Pos            (5UL)                   /**< The SFDP 1-4-4 fast read support (Bit 5)               */
#define CY_SMIF_SFDP_FAST_READ_1_4_4_Msk            (0x20UL)                /**< The SFDP 1-4-4 fast read support (Bitfield-Mask: 0x01) */
#define CY_SMIF_SFDP_FAST_READ_1_2_2_Pos            (4UL)                   /**< The SFDP 1-2-2 fast read support (Bit 4)               */
#define CY_SMIF_SFDP_FAST_READ_1_2_2_Msk            (0x10UL)                /**< The SFDP 1-2-2 fast read support (Bitfield-Mask: 0x01) */

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
/**
* \note
* This macro is available for CAT1B, CAT1C and CAT1D devices.
**/
#define CY_SMIF_SFDP_DTR_SUPPORT_Pos                  (3UL)                   /**< The SFDP DTR support (Bit 3)                           */
/**
* \note
* This macro is available for CAT1B, CAT1C and CAT1D devices.
**/
#define CY_SMIF_SFDP_DTR_SUPPORT_Msk                  (0x08UL)                /**< The SFDP DTR support (Bitfield-Mask: 0x08)             */
#endif /* CY_IP_MXSMIF_VERSION */

#define CY_SMIF_SFDP_ADDRESS_BYTES_Pos              (1UL)                   /**< The SFDP number of address bytes (Bit 1)               */
#define CY_SMIF_SFDP_ADDRESS_BYTES_Msk              (0x06UL)                /**< The SFDP number of address bytes (Bitfield-Mask: 0x03) */
#define CY_SMIF_SFDP_FAST_READ_1_1_2_Pos            (0UL)                   /**< The SFDP 1-1-2 fast read support (Bit 0)               */
#define CY_SMIF_SFDP_FAST_READ_1_1_2_Msk            (0x01UL)                /**< The SFDP 1-1-2 fast read support (Bitfield-Mask: 0x01) */

/* ----------------------------  2nd DWORD  ---------------------------- */
#define CY_SMIF_SFDP_SIZE_ABOVE_4GB_Msk             (0x80000000UL)          /**< Flash memory density bit define if it >= 4 Gbit  or <= 2Gbit */

/* ----------------------------  3rd DWORD  ---------------------------- */
#define CY_SMIF_SFDP_1_4_4_DUMMY_CYCLES_Pos         (0UL)                   /**< The SFDP number of 1-4-4 fast read dummy cycles (Bit 0)               */
#define CY_SMIF_SFDP_1_4_4_DUMMY_CYCLES_Msk         (0x1FUL)                /**< The SFDP number of 1-4-4 fast read dummy cycles (Bitfield-Mask: 0x1F) */
#define CY_SMIF_SFDP_1_4_4_MODE_CYCLES_Pos          (5UL)                   /**< The SFDP number of 1-4-4 fast read mode cycles (Bit 5)                */
#define CY_SMIF_SFDP_1_4_4_MODE_CYCLES_Msk          (0xE0UL)                /**< The SFDP number of 1-4-4 fast read mode cycles (Bitfield-Mask: 0x07)  */
#define CY_SMIF_SFDP_1_1_4_DUMMY_CYCLES_Pos         (0UL)                   /**< The SFDP number of 1-1-4 fast read dummy cycles (Bit 0)               */
#define CY_SMIF_SFDP_1_1_4_DUMMY_CYCLES_Msk         (0x1FUL)                /**< The SFDP number of 1-1-4 fast read dummy cycles (Bitfield-Mask: 0x1F) */
#define CY_SMIF_SFDP_1_1_4_MODE_CYCLES_Pos          (5UL)                   /**< The SFDP number of 1-1-4 fast read mode cycles (Bit 5)                */
#define CY_SMIF_SFDP_1_1_4_MODE_CYCLES_Msk          (0xE0UL)                /**< The SFDP number of 1-1-4 fast read mode cycles (Bitfield-Mask: 0x07)  */

/* ----------------------------  4th DWORD  ---------------------------- */
#define CY_SMIF_SFDP_1_1_2_DUMMY_CYCLES_Pos         (0UL)                   /**< The SFDP number of 1_1_2 fast read dummy cycles (Bit 0)               */
#define CY_SMIF_SFDP_1_1_2_DUMMY_CYCLES_Msk         (0x1FUL)                /**< The SFDP number of 1_1_2 fast read dummy cycles (Bitfield-Mask: 0x1F) */
#define CY_SMIF_SFDP_1_1_2_MODE_CYCLES_Pos          (5UL)                   /**< The SFDP number of 1_1_2 fast read mode cycles (Bit 5)                */
#define CY_SMIF_SFDP_1_1_2_MODE_CYCLES_Msk          (0xE0UL)                /**< The SFDP number of 1_1_2 fast read mode cycles (Bitfield-Mask: 0x07)  */
#define CY_SMIF_SFDP_1_2_2_DUMMY_CYCLES_Pos         (0UL)                   /**< The SFDP number of 1_2_2 fast read dummy cycles (Bit 0)               */
#define CY_SMIF_SFDP_1_2_2_DUMMY_CYCLES_Msk         (0x1FUL)                /**< The SFDP number of 1_2_2 fast read dummy cycles (Bitfield-Mask: 0x1F) */
#define CY_SMIF_SFDP_1_2_2_MODE_CYCLES_Pos          (5UL)                   /**< The SFDP number of 1_2_2 fast read mode cycles (Bit 5)                */
#define CY_SMIF_SFDP_1_2_2_MODE_CYCLES_Msk          (0xE0UL)                /**< The SFDP number of 1_2_2 fast read mode cycles (Bitfield-Mask: 0x07)  */

/* ----------------------------  10th DWORD  --------------------------- */
#define CY_SMIF_SFDP_ERASE_T1_COUNT_Pos             (4UL)                   /**< Erase Type 1 Erase, Typical time: count (Bits 8:4) */
#define CY_SMIF_SFDP_ERASE_T1_COUNT_Msk             (0x1F0UL)               /**< Erase Type 1 Erase, Typical time: count (Bitfield-Mask ) */
#define CY_SMIF_SFDP_ERASE_T1_UNITS_Pos             (9UL)                   /**< Erase Type 1 Erase, Typical time: units (Bits 10:9) */
#define CY_SMIF_SFDP_ERASE_T1_UNITS_Msk             (0x600UL)               /**< Erase Type 1 Erase, Typical time: units (Bitfield-Mask ) */
#define CY_SMIF_SFDP_ERASE_MUL_COUNT_Pos            (0UL)                   /**< Multiplier from typical erase time to maximum erase time (Bits 3:0) */
#define CY_SMIF_SFDP_ERASE_MUL_COUNT_Msk            (0x0FUL)                /**< Multiplier from typical erase time to maximum erase time (Bitfield-Mask ) */


/* ----------------------------  11th DWORD  --------------------------- */
#define CY_SMIF_SFDP_PAGE_SIZE_Pos                  (4UL)                   /**< The SFDP page size (Bit 4)                                    */
#define CY_SMIF_SFDP_PAGE_SIZE_Msk                  (0xF0UL)                /**< The SFDP page size (Bitfield-Mask: 0x0F)                      */
#define CY_SMIF_SFDP_PAGE_PROG_COUNT_Pos            (8UL)                   /**< The SFDP Chip Page Program Typical time: count (Bits 12:8)    */
#define CY_SMIF_SFDP_PAGE_PROG_COUNT_Msk            (0x1F00UL)              /**< The SFDP Chip Page Program Typical time: count (Bitfield-Mask)*/
#define CY_SMIF_SFDP_PAGE_PROG_UNITS_Pos            (13UL)                  /**< The SFDP Chip Page Program Typical time: units (Bit 13)       */
#define CY_SMIF_SFDP_PAGE_PROG_UNITS_Msk            (0x2000UL)              /**< The SFDP Chip Page Program Typical time: units (Bitfield-Mask)*/
#define CY_SMIF_SFDP_CHIP_ERASE_COUNT_Pos           (24UL)                  /**< The SFDP Chip Erase Typical time: count (Bits 28:24)          */
#define CY_SMIF_SFDP_CHIP_ERASE_COUNT_Msk           (0x1F000000UL)          /**< The SFDP Chip Erase Typical time: count (Bitfield-Mask)       */
#define CY_SMIF_SFDP_CHIP_ERASE_UNITS_Pos           (29UL)                  /**< The SFDP Chip Erase Typical time: units (Bits 29:30)          */
#define CY_SMIF_SFDP_CHIP_ERASE_UNITS_Msk           (0x60000000UL)          /**< The SFDP Chip Erase Typical time: units (Bitfield-Mask)       */
#define CY_SMIF_SFDP_PROG_MUL_COUNT_Pos             (0UL)                   /**< Multiplier from typical time to max time for Page or byte program (Bits 3:0)          */
#define CY_SMIF_SFDP_PROG_MUL_COUNT_Msk             (0x0FUL)                /**< Multiplier from typical time to max time for Page or byte program (Bitfield-Mask)       */

/* ----------------------------  15th DWORD  --------------------------- */
#define CY_SMIF_SFDP_QE_REQUIREMENTS_Pos            (4UL)                   /**< The SFDP quad enable requirements field (Bit 4)               */
#define CY_SMIF_SFDP_QE_REQUIREMENTS_Msk            (0x70UL)                /**< The SFDP quad enable requirements field (Bitfield-Mask: 0x07) */


/* ----------------------------  16th DWORD  --------------------------- */
#define CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_B7 (1U)                            /**< Issue 0xB7 instruction */
#define CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_WR_EN_B7 (2U)                      /**< Issue write enable instruction followed with 0xB7 */
#define CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_ALWAYS_4_BYTE (0x40U)              /**< Memory always operates in 4-byte mode */
#define CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_B7_CMD (0xB7U)                     /**< The instruction required to enter 4-byte addressing mode */
#define CY_SMIF_SFDP_ENTER_4_BYTE_METHOD_SUPPORTED_MASK (0x7FU)              /**< Mask indicating 4-byte address mode entry supported */

/* ----------------------------  17th DWORD  --------------------------- */
#define CY_SMIF_SFDP_FAST_READ_1_1_8_Pos            (0UL)                  /**< The SFDP 1-1-8 fast read support (Bitfield 24:31)               */
#define CY_SMIF_SFDP_FAST_READ_1_1_8_Msk            (0xFFUL)          /**< The SFDP 1-1-8 fast read support (Bitfield-Mask: 0xFF) */
#define CY_SMIF_SFDP_1_1_8_MODE_CYCLES_Pos          (5UL)                  /**< The SFDP number of 1-1-8 fast read mode cycles (Bitfield 21:23)                */
#define CY_SMIF_SFDP_1_1_8_MODE_CYCLES_Msk          (0xE0UL)            /**< The SFDP number of 1-1-8 fast read mode cycles (Bitfield-Mask: 0xE)  */
#define CY_SMIF_SFDP_1_1_8_DUMMY_CYCLES_Pos         (0UL)                  /**< The SFDP number of 1_1_8 fast read dummy cycles (Bit 16:19)               */
#define CY_SMIF_SFDP_1_1_8_DUMMY_CYCLES_Msk         (0x1FUL)            /**< The SFDP number of 1_1_8 fast read dummy cycles (Bitfield-Mask: 0x1F) */
#define CY_SMIF_SFDP_FAST_READ_1_8_8_Pos            (0UL)                   /**< The SFDP 1-8-8 fast read support (Bitfield 8:15)               */
#define CY_SMIF_SFDP_FAST_READ_1_8_8_Msk            (0xFFUL)              /**< The SFDP 1-8-8 fast read support (Bitfield-Mask: 0xFF) */
#define CY_SMIF_SFDP_1_8_8_MODE_CYCLES_Pos          (5UL)                   /**< The SFDP number of 1-8-8 fast read mode cycles (Bitfield 5:7)                */
#define CY_SMIF_SFDP_1_8_8_MODE_CYCLES_Msk          (0xE0UL)                /**< The SFDP number of 1-8-8 fast read mode cycles (Bitfield-Mask: 0xE)  */
#define CY_SMIF_SFDP_1_8_8_DUMMY_CYCLES_Pos         (0UL)                   /**< The SFDP number of 1_8_8 fast read dummy cycles (Bit 0:4)               */
#define CY_SMIF_SFDP_1_8_8_DUMMY_CYCLES_Msk         (0x1FUL)                 /**< The SFDP number of 1_8_8 fast read dummy cycles (Bitfield-Mask: 0x1F) */

/* ----------------------------  19th DWORD  --------------------------- */
#define CY_SMIF_SFDP_OCTAL_ENABE_BIT_Pos            (20UL)                  /**< Octal Enable bit present in the flash or not (Bitfiled 20:22)*/
#define CY_SMIF_SFDP_OCTAL_ENABE_BIT_Msk            (0x700000)              /**< Octal Enable bit present Mask (Bitfiled-Mask 0x7)*/

/* ---------------------------- xSPI Profile 1.0 ------------------------ */
#define XSPI_PROFILE_1_TABLE_BYTE_0        (0U)           /**< Byte 0x00 of the JEDEC xSPI Profile 1.0 */
#define XSPI_PROFILE_1_TABLE_BYTE_1        (1U)           /**< Byte 0x01 of the JEDEC xSPI Profile 1.0 */
#define XSPI_PROFILE_1_TABLE_BYTE_16       (0x10U)        /**< DWORD 5 => Byte 16 of the JEDEC xSPI Profile 1.0 */

/* ----------------------------  1st DWORD  --------------------------- */
#define CY_SMIF_SFDP_OCTAL_DDR_READ_CMD_Pos         (0UL)                  /**< Octal DDR 8D-8D-8D read command support position (Bitfield 8:15) */
#define CY_SMIF_SFDP_OCTAL_DDR_READ_CMD_Msk         (0xFFUL)               /**< Octal DDR 8D-8D-8D read command support Mask Bitfield-Mask: 0xFF00) */
#define CY_SMIF_SFDP_ODDR_166MHZ_DUMMY_CYCLES_Pos   (27UL)                 /**< Octal DDR 8D-8D-8D dummy cycles for 166 Mhz (Bitfield 27:31) */
#define CY_SMIF_SFDP_ODDR_166MHZ_DUMMY_CYCLES_Msk   (0xF8000000UL)         /**< Octal DDR 8D-8D-8D dummy cycles for 166 Mhz Mask */
#define CY_SMIF_SFDP_ODDR_200MHZ_DUMMY_CYCLES_Pos   (7UL)                  /**< Octal DDR 8D-8D-8D dummy cycles for 200 Mhz (Bitfield 7:11) */
#define CY_SMIF_SFDP_ODDR_200MHZ_DUMMY_CYCLES_Msk   (0xF80UL)               /**< Octal DDR 8D-8D-8D dummy cycles for 200 Mhz Mask */

/* ---------------------------- Command Sequence to Change to Octal DDR ------------------------ */
#define CMD_SEQ_OCTAL_DDR_CMD1_LEN_BYTE_OFFSET      (3U)                   /**< Octal DDR enable command 1 sequence length byte offset */
#define CMD_SEQ_OCTAL_DDR_CMD2_LEN_BYTE_OFFSET      (11U)                  /**< Octal DDR enable command 1 sequence length byte offset */
#define CY_SMIF_SFDP_ODDR_CMD_SEQ_MAX_LEN           (8U)                   /**< Octal DDR enable command sequence maximum length */

/** \cond INTERNAL */
/*******************************************************************************
* These are legacy constants and API. They are left here just
* for backward compatibility.
* Do not use them in new designs.
*******************************************************************************/

#define CY_SMIF_FLAG_WR_EN                          CY_SMIF_FLAG_WRITE_ENABLE
#define CY_SMIF_FLAG_CRYPTO_EN                      CY_SMIF_FLAG_CRYPTO_ENABLE
#define CY_SMIF_SFDP_SING_BYTE_00                   CY_SMIF_SFDP_SIGNATURE_BYTE_00
#define CY_SMIF_SFDP_SING_BYTE_01                   CY_SMIF_SFDP_SIGNATURE_BYTE_01
#define CY_SMIF_SFDP_SING_BYTE_02                   CY_SMIF_SFDP_SIGNATURE_BYTE_02
#define CY_SMIF_SFDP_SING_BYTE_03                   CY_SMIF_SFDP_SIGNATURE_BYTE_03
#define CY_SMIF_WR_STS_REG1_CMD                     CY_SMIF_WRITE_STATUS_REG1_CMD
#define CY_SMIF_WR_DISABLE_CMD                      CY_SMIF_WRITE_DISABLE_CMD
#define CY_SMIF_RD_STS_REG1_CMD                     CY_SMIF_READ_STATUS_REG1_CMD
#define CY_SMIF_WR_ENABLE_CMD                       CY_SMIF_WRITE_ENABLE_CMD
#define CY_SMIF_RD_STS_REG2_T1_CMD                  CY_SMIF_READ_STATUS_REG2_T1_CMD
#define CY_SMIF_WR_STS_REG2_CMD                     CY_SMIF_WRITE_STATUS_REG2_CMD
#define CY_SMIF_RD_STS_REG2_T2_CMD                  CY_SMIF_READ_STATUS_REG2_T2_CMD
#define CY_SMIF_QE_BIT_STS_REG2_T1                  CY_SMIF_QE_BIT_STATUS_REG2_T1
#define CY_SMIF_STS_REG_BUSY_MASK                   CY_SMIF_STATUS_REG_BUSY_MASK

#define Cy_SMIF_Memslot_Init                        Cy_SMIF_MemInit
#define Cy_SMIF_Memslot_DeInit                      Cy_SMIF_MemDeInit
#define Cy_SMIF_Memslot_CmdWriteEnable              Cy_SMIF_MemCmdWriteEnable
#define Cy_SMIF_Memslot_CmdWriteDisable             Cy_SMIF_MemCmdWriteDisable
#define Cy_SMIF_Memslot_IsBusy                      Cy_SMIF_MemIsBusy
#define Cy_SMIF_Memslot_QuadEnable                  Cy_SMIF_MemQuadEnable
#define Cy_SMIF_Memslot_CmdReadSts                  Cy_SMIF_MemCmdReadStatus
#define Cy_SMIF_Memslot_CmdWriteSts                 Cy_SMIF_MemCmdWriteStatus
#define Cy_SMIF_Memslot_CmdChipErase                Cy_SMIF_MemCmdChipErase
#define Cy_SMIF_Memslot_CmdSectorErase              Cy_SMIF_MemCmdSectorErase
#define Cy_SMIF_Memslot_SfdpDetect                  Cy_SMIF_MemSfdpDetect
#define Cy_SMIF_Memslot_CmdProgram                  Cy_SMIF_MemCmdProgram
#define Cy_SMIF_Memslot_CmdRead                     Cy_SMIF_MemCmdRead

#define PARAM_ID_MSB_OFFSET                         (0x08U)  /* The offset of Parameter ID MSB */
#define PARAM_ID_LSB_MASK                           (0xFFUL) /* The mask of Parameter ID LSB */
#define MEM_ADDR_VALID(addr, size) (0U == ((addr)%(size)))  /* This address must be a multiple of
                                                             * the SMIF XIP memory size
                                                             */
#define MEM_MAPPED_SIZE_VALID(size) (((size) >= 0x10000U) && (0U == ((size)&((size)-1U))) )
#define MEM_ADDR_SIZE_VALID(addrSize)  ((0U < (addrSize)) && ((addrSize) <= CY_SMIF_FOUR_BYTES_ADDR))

/** \endcond */
/** \} group_smif_macros_sfdp */


/**
* \addtogroup group_smif_data_structures_memslot
* \{
*/

/** This command structure is used to store the Read/Write command
 * configuration. */
typedef struct
{
    uint32_t command;                       /**< The 8-bit command. This value is 0xFFFFFFFF when there is no command present */
    cy_en_smif_txfr_width_t cmdWidth;       /**< The width of the command transfer */
    cy_en_smif_txfr_width_t addrWidth;      /**< The width of the address transfer */
    uint32_t mode;                          /**< The 8-bit mode byte. This value is 0xFFFFFFFF when there is no mode present */
    cy_en_smif_txfr_width_t modeWidth;      /**< The width of the mode transfer */
    uint32_t dummyCycles;                   /**< The number of the dummy cycles. A zero value suggests no dummy cycles */
    cy_en_smif_txfr_width_t dataWidth;      /**< The width of the data transfer */
#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_data_rate_t dataRate;           /**< The Data rate of data */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_field_presence_t dummyCyclesPresence;   /**< This specifies the presence of the dummy field */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_field_presence_t modePresence;  /**< This specifies the presence of the mode field */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    uint32_t modeH;                            /**< The 8-bit command. This value is 0x0 when there is no higher byte mode present */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_data_rate_t modeRate;           /**< The Data rate of mode */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_data_rate_t addrRate;           /**< The Data rate of address */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_field_presence_t cmdPresence;   /**< This specifies the presence of the command field */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    uint32_t commandH;                         /**< The 8-bit command. This value is 0x0 when there is no higher byte command present */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_data_rate_t cmdRate;            /**< The Data rate of command */
#endif /* CY_IP_MXSMIF_VERSION */
} cy_stc_smif_mem_cmd_t;

/** This structure specifies data used for memory with hybrid sectors */
typedef struct
{
    uint32_t regionAddress;                 /**< This specifies the address where a region starts */
    uint32_t sectorsCount;                  /**< This specifies the number of sectors in the region */
    uint32_t eraseCmd;                      /**< This specifies the region specific erase instruction */
    uint32_t eraseSize;                     /**< This specifies the size of one sector */
    uint32_t eraseTime;                     /**< Max time for sector erase type 1 cycle time in ms */
} cy_stc_smif_hybrid_region_info_t;

#if(CY_IP_MXSMIF_VERSION>=2)
/** This structure specifies data used for memory with hybrid sectors */
typedef struct
{
    uint8_t cmdSeq1Len;                                   /**< This specifies command sequence 1 length. */
    uint8_t cmdSeq2Len;                                   /**< This specifies command sequence 2 length. */
    uint8_t cmdSeq1[CY_SMIF_SFDP_ODDR_CMD_SEQ_MAX_LEN];   /**< This specifies command sequence 1. */
    uint8_t cmdSeq2[CY_SMIF_SFDP_ODDR_CMD_SEQ_MAX_LEN];   /**< This specifies command sequence 2. */
} cy_stc_smif_octal_ddr_en_seq_t;
#endif

/**
*
* This configuration structure of the SMIF memory device is used to store
* device-specific parameters.
* These parameters are used to set up the memory mode initialization and the
* memory API.
*/
typedef struct
{
    uint32_t numOfAddrBytes;                              /**< This specifies the number of address bytes used by the
                                                          * memory slave device, valid values 1-4 */
    uint32_t memSize;                                     /**< The memory size: For densities of 2 gigabits or less - the size in bytes;
                                                          * For densities 4 gigabits and above - bit-31 is set to 1b to define that
                                                          * this memory is 4 gigabits and above; and other 30:0 bits define N where
                                                          * the density is computed as 2^N bytes.
                                                          * For example, 0x80000021 corresponds to 2^30 = 1 gigabyte.
                                                          */
    cy_stc_smif_mem_cmd_t* readCmd;                       /**< This specifies the Read command */
    cy_stc_smif_mem_cmd_t* writeEnCmd;                    /**< This specifies the Write Enable command */
    cy_stc_smif_mem_cmd_t* writeDisCmd;                   /**< This specifies the Write Disable command */
    cy_stc_smif_mem_cmd_t* eraseCmd;                      /**< This specifies the Erase command */
    uint32_t eraseSize;                                   /**< This specifies the sector size of each Erase */
    cy_stc_smif_mem_cmd_t* chipEraseCmd;                  /**< This specifies the Chip Erase command */
    cy_stc_smif_mem_cmd_t* programCmd;                    /**< This specifies the Program command */
    uint32_t programSize;                                 /**< This specifies the page size for programming */
    cy_stc_smif_mem_cmd_t* readStsRegWipCmd;              /**< This specifies the command to read the WIP-containing status register  */
    cy_stc_smif_mem_cmd_t* readStsRegQeCmd;               /**< This specifies the command to read the QE-containing status register */
    cy_stc_smif_mem_cmd_t* writeStsRegQeCmd;              /**< This specifies the command to write into the QE-containing status register */
    cy_stc_smif_mem_cmd_t* readSfdpCmd;                   /**< This specifies the read SFDP command */
    uint32_t stsRegBusyMask;                              /**< The Busy mask for the status registers */
    uint32_t stsRegQuadEnableMask;                        /**< The QE mask for the status registers */
    uint32_t eraseTime;                                   /**< Max time for erase type 1 cycle time in ms */
    uint32_t chipEraseTime;                               /**< Max time for chip erase cycle time in ms */
    uint32_t programTime;                                 /**< Max time for page program cycle time in us */
    uint32_t hybridRegionCount;                           /**< This specifies the number of regions for memory with hybrid sectors */
    cy_stc_smif_hybrid_region_info_t** hybridRegionInfo;  /**< This specifies data for memory with hybrid sectors */
    cy_stc_smif_mem_cmd_t* readLatencyCmd;                   /**< This specifies the command to read variable latency cycles configuration register */
    cy_stc_smif_mem_cmd_t* writeLatencyCmd;               /**< This specifies the command to write variable latency cycles configuration register */
    uint32_t latencyCyclesRegAddr;                        /**< This specifies the address for variable latency cycle address */
    uint32_t latencyCyclesMask;                           /**< This specifies variable latency cycles Mask */
#if(CY_IP_MXSMIF_VERSION>=2)
    cy_stc_smif_octal_ddr_en_seq_t* octalDDREnableSeq;    /**< This specifies data for memory with hybrid sectors */
    cy_stc_smif_mem_cmd_t* readStsRegOeCmd;               /**< This specifies the command to read the OE-containing status register */
    cy_stc_smif_mem_cmd_t* writeStsRegOeCmd;              /**< This specifies the command to write into the OE-containing status register */
    uint32_t stsRegOctalEnableMask;                       /**< The QE mask for the status registers */
    uint32_t octalEnableRegAddr;                          /**< Octal enable register address */
    cy_en_smif_interface_freq_t freq_of_operation;        /**< Frequency of operation used in Octal mode */
#endif
} cy_stc_smif_mem_device_cfg_t;


/**
*
* This SMIF memory configuration structure is used to store the memory configuration for the memory mode of operation.
* This data structure is stored in a fixed location in the flash. The data structure is required
* for the initialization of the SMIF in the SystemInit.
*/
typedef struct
{
    /** Determines the slave select where the memory device is placed */
    cy_en_smif_slave_select_t slaveSelect;
    /** Determines if the device is memory-mapped, enables the Autodetect
     * using the SFDP, enables the write capability, or enables the crypto
     * support for this memory slave */
    uint32_t flags;
    /** The data-line selection options for a slave device */
    cy_en_smif_data_select_t dataSelect;
    /** The base address the memory slave is mapped to in the PSoC memory map.
     * This address must be a multiple of the SMIF XIP memory size/capacity. The
     * SMIF XIP memory region should NOT overlap with other memory regions
     * (with exception to dual quad mode). Valid when the memory-mapped mode is
     * enabled.
     */
    uint32_t baseAddress;
    /** The size/capacity allocated in the PSoC memory map for the memory slave
     * device. The capacity is allocated from the base address. The capacity
     * must be a power of 2 and greater or equal than 64 KB. Valid when
     * memory-mapped mode is enabled
     */
    uint32_t memMappedSize;
    /** Defines if this memory device is one of the devices in the dual quad SPI
     * configuration. Equals the sum of the slave-slot numbers.  */
    uint32_t dualQuadSlots;
    cy_stc_smif_mem_device_cfg_t* deviceCfg;   /**< The configuration of the device */
#if(CY_IP_MXSMIF_VERSION>=2)
    /** Continuous transfer merge timeout.
     * After this period the memory device is deselected. A later transfer, even from a
     * continuous address, starts with the overhead phases (command, address, mode, dummy cycles).
     * This configuration parameter is available for CAT1B, CAT1C and CAT1D devices. */
    cy_en_smif_merge_timeout_t mergeTimeout;
#endif /* CY_IP_MXSMIF_VERSION */

} cy_stc_smif_mem_config_t;


/**
*
* This SMIF memory configuration structure is used to store the memory configuration for the memory mode of operation.
* This data structure is stored in a fixed location in the flash. The data structure is required
* for the initialization of the SMIF in the SystemInit.
*/
typedef struct
{
    uint32_t memCount;                         /**< The number of SMIF memory defined  */
    cy_stc_smif_mem_config_t** memConfig;      /**< The pointer to the array of the memory configuration structures of size Memory_count */
    uint32_t majorVersion;                     /**< The version of the SMIF driver */
    uint32_t minorVersion;                     /**< The version of the SMIF Driver */
} cy_stc_smif_block_config_t;


/** \} group_smif_data_structures_memslot */


/**
* \addtogroup group_smif_mem_slot_functions
* \{
*/
cy_en_smif_status_t    Cy_SMIF_MemInit(SMIF_Type *base,
                                cy_stc_smif_block_config_t const * blockConfig,
                                cy_stc_smif_context_t *context);
void        Cy_SMIF_MemDeInit(SMIF_Type *base);
cy_en_smif_status_t    Cy_SMIF_MemCmdWriteEnable( SMIF_Type *base,
                                        cy_stc_smif_mem_config_t const *memDevice,
                                        cy_stc_smif_context_t const *context);
cy_en_smif_status_t    Cy_SMIF_MemCmdWriteDisable(SMIF_Type *base,
                                         cy_stc_smif_mem_config_t const *memDevice,
                                         cy_stc_smif_context_t const *context);
bool Cy_SMIF_MemIsBusy(SMIF_Type *base, cy_stc_smif_mem_config_t const *memDevice,
                                    cy_stc_smif_context_t const *context);
cy_en_smif_status_t    Cy_SMIF_MemQuadEnable(SMIF_Type *base,
                                        cy_stc_smif_mem_config_t const *memDevice,
                                        cy_stc_smif_context_t const *context);
#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
cy_en_smif_status_t Cy_SMIF_MemOctalEnable(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_en_smif_data_rate_t dataRate,
                                    cy_stc_smif_context_t const *context);
#endif

cy_en_smif_status_t Cy_SMIF_MemCmdReadStatus(SMIF_Type *base,
                                        cy_stc_smif_mem_config_t const *memDevice,
                                        uint8_t *status, uint8_t command,
                                        cy_stc_smif_context_t const *context);
cy_en_smif_status_t    Cy_SMIF_MemCmdWriteStatus(SMIF_Type *base,
                                        cy_stc_smif_mem_config_t const *memDevice,
                                        void const *status, uint8_t command,
                                        cy_stc_smif_context_t const *context);
cy_en_smif_status_t    Cy_SMIF_MemCmdChipErase(SMIF_Type *base,
                                        cy_stc_smif_mem_config_t const *memDevice,
                                        cy_stc_smif_context_t const *context);
cy_en_smif_status_t    Cy_SMIF_MemCmdSectorErase(SMIF_Type *base,
                                            cy_stc_smif_mem_config_t const *memDevice,
                                            uint8_t const *sectorAddr,
                                            cy_stc_smif_context_t const *context);
cy_en_smif_status_t    Cy_SMIF_MemCmdProgram(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    uint8_t const *addr,
                                    uint8_t const *writeBuff,
                                    uint32_t size,
                                    cy_smif_event_cb_t cmdCompleteCb,
                                    cy_stc_smif_context_t *context);
cy_en_smif_status_t    Cy_SMIF_MemCmdRead(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    uint8_t const *addr,
                                    uint8_t *readBuff,
                                    uint32_t size,
                                    cy_smif_event_cb_t cmdCompleteCb,
                                    cy_stc_smif_context_t *context);
cy_en_smif_status_t    Cy_SMIF_MemSfdpDetect(SMIF_Type *base,
                                    cy_stc_smif_mem_device_cfg_t *device,
                                    cy_en_smif_slave_select_t slaveSelect,
                                    cy_en_smif_data_select_t dataSelect,
                                    cy_stc_smif_context_t *context);

cy_en_smif_status_t Cy_SMIF_MemInitSfdpMode(SMIF_Type *base,
                                    const cy_stc_smif_mem_config_t *memCfg,
                                    cy_en_smif_txfr_width_t maxdataWidth,
                                    cy_en_smif_qer_t qer_id,
                                    cy_stc_smif_context_t *context);

cy_en_smif_status_t Cy_SMIF_MemIsReady(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                       uint32_t timeoutUs, cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_MemIsQuadEnabled(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                             bool *isQuadEnabled, cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_MemEnableQuadMode(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                              uint32_t timeoutUs, cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_MemRead(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                    uint32_t address, uint8_t rxBuffer[],
                                    uint32_t length, cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_MemWrite(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                     uint32_t address, uint8_t const txBuffer[],
                                     uint32_t length, cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_MemEraseSector(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                           uint32_t address, uint32_t length,
                                           cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_MemEraseChip(SMIF_Type *base, cy_stc_smif_mem_config_t const *memConfig,
                                         cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_MemLocateHybridRegion(cy_stc_smif_mem_config_t const *memDevice,
                                               cy_stc_smif_hybrid_region_info_t** regionInfo, uint32_t address);
void Cy_SMIF_SetReadyPollingDelay(uint16_t pollTimeoutUs,
                                  cy_stc_smif_context_t *context);
cy_en_smif_status_t Cy_SMIF_MemCmdPowerDown(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_stc_smif_context_t const *context);

cy_en_smif_status_t Cy_SMIF_MemCmdReleasePowerDown(SMIF_Type *base,
                                    cy_stc_smif_mem_config_t const *memDevice,
                                    cy_stc_smif_context_t const *context);

/** \} group_smif_mem_slot_functions */

__STATIC_INLINE void SfdpGetQuadEnableParameters(cy_stc_smif_mem_device_cfg_t *device,
                                                       cy_en_smif_qer_t qerId);
__STATIC_INLINE void XipRegInit(SMIF_DEVICE_Type volatile *dev, cy_stc_smif_mem_config_t const * memCfg);

__STATIC_INLINE cy_en_smif_status_t ReadAnyReg(SMIF_Type *base,
                                            cy_en_smif_slave_select_t  slaveSelect,
                                            uint8_t *value,
                                            uint8_t command,
                                            uint8_t dummyCycles,
                                            uint8_t const *address,
                                            uint32_t addressSize,
                                            cy_stc_smif_context_t const *context);
__STATIC_INLINE void ValueToByteArray(uint32_t value, uint8_t *byteArray, uint32_t startPos, uint32_t size);
__STATIC_INLINE uint32_t ByteArrayToValue(uint8_t const *byteArray, uint32_t size);

/*******************************************************************************
* Function Name: SfdpGetQuadEnableParameters
****************************************************************************//**
*
* Gets the Quad Enable parameters.
*
* \param device
* The device structure instance declared by the user. This is where the detected
* parameters are stored and returned.
*
* \param qerId
* quad enable requirement ID
*
*******************************************************************************/
__STATIC_INLINE void SfdpGetQuadEnableParameters(cy_stc_smif_mem_device_cfg_t *device,
                                                   cy_en_smif_qer_t qerId)
{
    CY_ASSERT_L1(NULL != device->readStsRegQeCmd);
    CY_ASSERT_L1(NULL != device->writeStsRegQeCmd);

    /* The command transfer width */
    device->writeStsRegQeCmd->cmdWidth = CY_SMIF_WIDTH_SINGLE;

    /* The QE mask for the status registers */
    switch (qerId)
    {
        case CY_SMIF_SFDP_QER_0:
            device->stsRegQuadEnableMask = CY_SMIF_NO_COMMAND_OR_MODE;
            device->writeStsRegQeCmd->command  = CY_SMIF_NO_COMMAND_OR_MODE;
            device->readStsRegQeCmd->command  = CY_SMIF_NO_COMMAND_OR_MODE;
#if (CY_IP_MXSMIF_VERSION>=2)
            device->writeStsRegQeCmd->cmdPresence  = CY_SMIF_NOT_PRESENT;
            device->readStsRegQeCmd->cmdPresence  = CY_SMIF_NOT_PRESENT;
#endif /* CY_IP_MXSMIF_VERSION */
            break;
        case CY_SMIF_SFDP_QER_1:
        case CY_SMIF_SFDP_QER_4:
        case CY_SMIF_SFDP_QER_5:
            device->stsRegQuadEnableMask = CY_SMIF_SFDP_QE_BIT_1_OF_SR_2;

            /* The command to write into the QE-containing status register */
            /* The 8-bit command. QE WRSR */
            device->writeStsRegQeCmd->command  = CY_SMIF_WRITE_STATUS_REG1_CMD;
            device->readStsRegQeCmd->command  = CY_SMIF_READ_STATUS_REG2_T1_CMD;
#if (CY_IP_MXSMIF_VERSION>=2)
            device->writeStsRegQeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
            device->readStsRegQeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
            break;
        case CY_SMIF_SFDP_QER_2:
            device->stsRegQuadEnableMask = CY_SMIF_SFDP_QE_BIT_6_OF_SR_1;

            /* The command to write into the QE-containing status register */
            /* The 8-bit command. QE WRSR */
            device->writeStsRegQeCmd->command  = CY_SMIF_WRITE_STATUS_REG1_CMD;
            device->readStsRegQeCmd->command  = CY_SMIF_READ_STATUS_REG1_CMD;
#if (CY_IP_MXSMIF_VERSION>=2)
            device->writeStsRegQeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
            device->readStsRegQeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
            break;
        case CY_SMIF_SFDP_QER_3:
            device->stsRegQuadEnableMask = CY_SMIF_SFDP_QE_BIT_7_OF_SR_2;

            /* The command to write into the QE-containing status register */
            /* The 8-bit command. QE WRSR */
            device->writeStsRegQeCmd->command  = CY_SMIF_WRITE_STATUS_REG2_T1_CMD;
            device->readStsRegQeCmd->command  = CY_SMIF_READ_STATUS_REG2_T2_CMD;
#if (CY_IP_MXSMIF_VERSION>=2)
            device->writeStsRegQeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
            device->readStsRegQeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
            break;
        case CY_SMIF_SFDP_QER_6:
            device->stsRegQuadEnableMask = CY_SMIF_SFDP_QE_BIT_1_OF_SR_2;

            /* The command to write into the QE-containing status register */
            /* The 8-bit command. QE WRSR */
            device->writeStsRegQeCmd->command  = CY_SMIF_WRITE_STATUS_REG2_T2_CMD;
            device->readStsRegQeCmd->command  = CY_SMIF_READ_STATUS_REG2_T1_CMD;
#if (CY_IP_MXSMIF_VERSION>=2)
            device->writeStsRegQeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
            device->readStsRegQeCmd->cmdPresence  = CY_SMIF_PRESENT_1BYTE;
#endif /* CY_IP_MXSMIF_VERSION */
            break;
        default:
            /* Unsupported quad enable requirement */
            break;
    }
}

/*******************************************************************************
* Function Name: XipRegInit
****************************************************************************//**
*
* \internal
* This function initializes the memory device registers used for the XIP mode of
* the specified device.
*
* \param dev
* The SMIF memory device registers structure. \ref SMIF_DEVICE_Type
*
* \param memCfg
* The memory configuration structure that configures the SMIF memory device to
*  map into the PSoC memory map. \ref cy_stc_smif_mem_config_t
*
*******************************************************************************/
__STATIC_INLINE void XipRegInit(SMIF_DEVICE_Type volatile *dev, cy_stc_smif_mem_config_t const * memCfg)
{
    cy_stc_smif_mem_device_cfg_t const * devCfg = memCfg->deviceCfg;
    cy_stc_smif_mem_cmd_t const * read = devCfg->readCmd;
    cy_stc_smif_mem_cmd_t const * prog = devCfg->programCmd;

    SMIF_DEVICE_ADDR(dev) = (SMIF_DEVICE_ADDR_ADDR_Msk & memCfg->baseAddress);

    /* Convert the size in the mask */
    SMIF_DEVICE_MASK(dev)= (SMIF_DEVICE_MASK_MASK_Msk & (~(memCfg->memMappedSize) + 1UL));

#if (CY_IP_MXSMIF_VERSION>=2)
    SMIF_DEVICE_ADDR_CTL(dev) = _VAL2FLD(SMIF_DEVICE_ADDR_CTL_SIZE3, (devCfg->numOfAddrBytes - 1UL)) |
                                ((0UL != memCfg->dualQuadSlots)? SMIF_DEVICE_ADDR_CTL_DIV2_Msk: 0UL);

    if((memCfg->flags & CY_SMIF_FLAG_SMIF_REV_3) != 0UL)
    {
        if(NULL != read)
        {
            SMIF_DEVICE_RD_CMD_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != read->command) ?
                                        (_VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_CODE,    (uint32_t)read->command)  |
                                        _VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_CODEH,    (uint32_t)read->commandH)  |
                                        _VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_DDR_MODE,  (uint32_t)read->cmdRate)  |
                                        _VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_WIDTH, (uint32_t)read->cmdWidth) |
                                        _VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_PRESENT2, (uint32_t)read->cmdPresence))
                                        : 0U;
            SMIF_DEVICE_RD_ADDR_CTL(dev) = _VAL2FLD(SMIF_DEVICE_RD_ADDR_CTL_WIDTH, (uint32_t)read->addrWidth) |
                                           _VAL2FLD(SMIF_DEVICE_RD_ADDR_CTL_DDR_MODE, (uint32_t)read->addrRate);

            SMIF_DEVICE_RD_MODE_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != read->mode) ?
                                        (_VAL2FLD(SMIF_DEVICE_RD_MODE_CTL_CODE,  (uint32_t)read->mode)       |
                                            _VAL2FLD(SMIF_DEVICE_RD_MODE_CTL_CODEH, (uint32_t)read->modeH) |
                                            _VAL2FLD(SMIF_DEVICE_RD_MODE_CTL_WIDTH, (uint32_t)read->modeWidth) |
                                            _VAL2FLD(SMIF_DEVICE_RD_MODE_CTL_DDR_MODE, (uint32_t)read->modeRate) |
                                            _VAL2FLD(SMIF_DEVICE_RD_MODE_CTL_PRESENT2, read->modePresence))
                                        : 0U;

            SMIF_DEVICE_RD_DUMMY_CTL(dev) = (0UL != read->dummyCycles)?
                                            (_VAL2FLD(SMIF_DEVICE_RD_DUMMY_CTL_SIZE5, (read->dummyCycles - 1UL)) |
                                            _VAL2FLD(SMIF_DEVICE_RD_DUMMY_CTL_PRESENT2,read->dummyCyclesPresence))
                                            : 0U;

            SMIF_DEVICE_RD_DATA_CTL(dev) = _VAL2FLD(SMIF_DEVICE_RD_DATA_CTL_WIDTH, (uint32_t)read->dataWidth) |
                                           _VAL2FLD(SMIF_DEVICE_RD_DATA_CTL_DDR_MODE, (uint32_t)read->dataRate);
        }

        if(NULL != prog)
        {
            SMIF_DEVICE_WR_CMD_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != prog->command) ?
                                        _VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_CODE,  (uint32_t)prog->command) |
                                        _VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_CODEH,    (uint32_t)prog->commandH) |
                                        _VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_DDR_MODE,  (uint32_t)prog->cmdRate) |
                                        _VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_WIDTH, (uint32_t)prog->cmdWidth) |
                                        _VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_PRESENT2, prog->cmdPresence)
                                        : 0U;

            SMIF_DEVICE_WR_ADDR_CTL(dev) = _VAL2FLD(SMIF_DEVICE_WR_ADDR_CTL_WIDTH, (uint32_t)prog->addrWidth) |
                                                          _VAL2FLD(SMIF_DEVICE_WR_ADDR_CTL_DDR_MODE, (uint32_t)prog->addrRate);

            SMIF_DEVICE_WR_MODE_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != prog->mode) ?
                                            _VAL2FLD(SMIF_DEVICE_WR_MODE_CTL_CODE,    (uint32_t)prog->mode)      |
                                            _VAL2FLD(SMIF_DEVICE_WR_MODE_CTL_CODEH,  (uint32_t)prog->modeH)     |
                                            _VAL2FLD(SMIF_DEVICE_WR_MODE_CTL_WIDTH, (uint32_t)prog->modeWidth) |
                                            _VAL2FLD(SMIF_DEVICE_WR_MODE_CTL_DDR_MODE, (uint32_t)prog->modeRate) |
                                            _VAL2FLD(SMIF_DEVICE_WR_MODE_CTL_PRESENT2, prog->modePresence)
                                            : 0UL;

            SMIF_DEVICE_WR_DUMMY_CTL(dev) = (0UL != prog->dummyCycles) ?
                                            (_VAL2FLD(SMIF_DEVICE_WR_DUMMY_CTL_SIZE5, (prog->dummyCycles - 1UL)) |
                                            (_VAL2FLD(SMIF_DEVICE_WR_DUMMY_CTL_PRESENT2, prog->dummyCyclesPresence)))
                                            : 0U;

            SMIF_DEVICE_WR_DATA_CTL(dev) = _VAL2FLD(SMIF_DEVICE_WR_DATA_CTL_WIDTH, (uint32_t)prog->dataWidth) |
                                                          _VAL2FLD(SMIF_DEVICE_WR_DATA_CTL_DDR_MODE, (uint32_t)prog->dataRate);
        }
    }
    else
    {
        if(NULL != read)
        {
            SMIF_DEVICE_RD_CMD_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != read->command) ?
                                        (_VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_CODE,    (uint32_t)read->command)  |
                                        _VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_WIDTH, (uint32_t)read->cmdWidth) |
                                        _VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_PRESENT2, 1UL))
                                        : 0U;

            SMIF_DEVICE_RD_ADDR_CTL(dev) = _VAL2FLD(SMIF_DEVICE_RD_ADDR_CTL_WIDTH, (uint32_t)read->addrWidth);

            SMIF_DEVICE_RD_MODE_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != read->mode) ?
                                        (_VAL2FLD(SMIF_DEVICE_RD_MODE_CTL_CODE,  (uint32_t)read->mode)       |
                                            _VAL2FLD(SMIF_DEVICE_RD_MODE_CTL_WIDTH, (uint32_t)read->modeWidth)|
                                            _VAL2FLD(SMIF_DEVICE_RD_MODE_CTL_PRESENT2, 1UL))
                                        : 0U;

            SMIF_DEVICE_RD_DUMMY_CTL(dev) = (0UL != read->dummyCycles)?
                                            (_VAL2FLD(SMIF_DEVICE_RD_DUMMY_CTL_SIZE5, (read->dummyCycles - 1UL)) |
                                            _VAL2FLD(SMIF_DEVICE_RD_DUMMY_CTL_PRESENT2, 1UL))
                                            : 0U;

            SMIF_DEVICE_RD_DATA_CTL(dev) = _VAL2FLD(SMIF_DEVICE_RD_DATA_CTL_WIDTH, (uint32_t)read->dataWidth);
        }

        if(NULL != prog)
        {
            SMIF_DEVICE_WR_CMD_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != prog->command) ?
                                        (_VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_CODE,    (uint32_t)prog->command) |
                                        _VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_WIDTH, (uint32_t)prog->cmdWidth)|
                                        _VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_PRESENT2, 1UL))
                                        : 0U;

            SMIF_DEVICE_WR_ADDR_CTL(dev) = _VAL2FLD(SMIF_DEVICE_WR_ADDR_CTL_WIDTH, (uint32_t)prog->addrWidth);

            SMIF_DEVICE_WR_MODE_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != prog->mode) ?
                                            (_VAL2FLD(SMIF_DEVICE_WR_MODE_CTL_CODE,  (uint32_t)prog->mode)       |
                                            _VAL2FLD(SMIF_DEVICE_WR_MODE_CTL_WIDTH, (uint32_t)prog->modeWidth)|
                                            _VAL2FLD(SMIF_DEVICE_WR_MODE_CTL_PRESENT2, 1UL))
                                            : 0UL;

            SMIF_DEVICE_WR_DUMMY_CTL(dev) = (0UL != prog->dummyCycles) ?
                                            (_VAL2FLD(SMIF_DEVICE_WR_DUMMY_CTL_SIZE5, (prog->dummyCycles - 1UL)) |
                                            (_VAL2FLD(SMIF_DEVICE_WR_DUMMY_CTL_PRESENT2, 1UL)))
                                            : 0U;

            SMIF_DEVICE_WR_DATA_CTL(dev) = _VAL2FLD(SMIF_DEVICE_WR_DATA_CTL_WIDTH, (uint32_t)prog->dataWidth);
        }
    }
#else
    SMIF_DEVICE_ADDR_CTL(dev) = _VAL2FLD(SMIF_DEVICE_ADDR_CTL_SIZE2, (devCfg->numOfAddrBytes - 1UL)) |
                                ((0UL != memCfg->dualQuadSlots)? SMIF_DEVICE_ADDR_CTL_DIV2_Msk: 0UL);

    if(NULL != read)
    {
        SMIF_DEVICE_RD_CMD_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != read->command) ?
                                    (_VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_CODE,    (uint32_t)read->command)  |
                                    _VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_WIDTH, (uint32_t)read->cmdWidth) |
                                    SMIF_DEVICE_RD_CMD_CTL_PRESENT_Msk)
                                    : 0U;

        SMIF_DEVICE_RD_ADDR_CTL(dev) = _VAL2FLD(SMIF_DEVICE_RD_ADDR_CTL_WIDTH, (uint32_t)read->addrWidth);

        SMIF_DEVICE_RD_MODE_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != read->mode) ?
                                    (_VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_CODE,    (uint32_t)read->mode)      |
                                        _VAL2FLD(SMIF_DEVICE_RD_CMD_CTL_WIDTH, (uint32_t)read->modeWidth)|
                                        SMIF_DEVICE_RD_CMD_CTL_PRESENT_Msk)
                                    : 0U;

        SMIF_DEVICE_RD_DUMMY_CTL(dev) = (0UL != read->dummyCycles)?
                                        (_VAL2FLD(SMIF_DEVICE_RD_DUMMY_CTL_SIZE5, (read->dummyCycles - 1UL)) |
                                        SMIF_DEVICE_RD_DUMMY_CTL_PRESENT_Msk)
                                        : 0U;

        SMIF_DEVICE_RD_DATA_CTL(dev) = _VAL2FLD(SMIF_DEVICE_RD_DATA_CTL_WIDTH, (uint32_t)read->dataWidth);
    }

    if(NULL != prog)
    {
        SMIF_DEVICE_WR_CMD_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != prog->command) ?
                                    (_VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_CODE,    (uint32_t)prog->command) |
                                    _VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_WIDTH, (uint32_t)prog->cmdWidth)|
                                    SMIF_DEVICE_WR_CMD_CTL_PRESENT_Msk)
                                    : 0U;

        SMIF_DEVICE_WR_ADDR_CTL(dev) = _VAL2FLD(SMIF_DEVICE_WR_ADDR_CTL_WIDTH, (uint32_t)prog->addrWidth);

        SMIF_DEVICE_WR_MODE_CTL(dev) = (CY_SMIF_NO_COMMAND_OR_MODE != prog->mode) ?
                                        (_VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_CODE,    (uint32_t)prog->mode)      |
                                        _VAL2FLD(SMIF_DEVICE_WR_CMD_CTL_WIDTH, (uint32_t)prog->modeWidth)|
                                        SMIF_DEVICE_WR_CMD_CTL_PRESENT_Msk)
                                        : 0UL;

        SMIF_DEVICE_WR_DUMMY_CTL(dev) = (0UL != prog->dummyCycles) ?
                                        (_VAL2FLD(SMIF_DEVICE_WR_DUMMY_CTL_SIZE5, (prog->dummyCycles - 1UL)) |
                                        SMIF_DEVICE_WR_DUMMY_CTL_PRESENT_Msk)
                                        : 0U;

        SMIF_DEVICE_WR_DATA_CTL(dev) = _VAL2FLD(SMIF_DEVICE_WR_DATA_CTL_WIDTH, (uint32_t)prog->dataWidth);
    }
#endif /* CY_IP_MXSMIF_VERSION */
}
/*******************************************************************************
* Function Name: ReadAnyReg
****************************************************************************//**
*
* This function reads any registers by address. This function is a blocking
* function, it will block the execution flow until the status register is read.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param slaveSelect
* The slave select line for the device.
*
* \param value
* The value of the register.
*
* \param command
* The command required to read the status/configuration register.
*
* \param dummyCycles
* Number of latency cycles to be issue after sending register address.
*
* \param address
* The register address array.
*
* \param addressSize
* The size of the address array.
*
* \param context
* This is the pointer to the context structure \ref cy_stc_smif_context_t
* allocated by the user. The structure is used during the SMIF
* operation for internal configuration and data retention. The user must not
* modify anything in this structure.
*
* \return A status of the command reception.
*        - \ref CY_SMIF_SUCCESS
*        - \ref CY_SMIF_CMD_FIFO_FULL
*        - \ref CY_SMIF_EXCEED_TIMEOUT
*        - \ref CY_SMIF_CMD_NOT_FOUND
*
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t ReadAnyReg(SMIF_Type *base,
                                    cy_en_smif_slave_select_t  slaveSelect,
                                    uint8_t *value,
                                    uint8_t command,
                                    uint8_t dummyCycles,
                                    uint8_t const *address,
                                    uint32_t addressSize,
                                    cy_stc_smif_context_t const *context)
{
    cy_en_smif_status_t result = CY_SMIF_CMD_NOT_FOUND;

    /* Read the memory register */
    result = Cy_SMIF_TransmitCommand(base, command, CY_SMIF_WIDTH_SINGLE,
                address, addressSize,
                CY_SMIF_WIDTH_SINGLE, slaveSelect,
                CY_SMIF_TX_NOT_LAST_BYTE, context);

    if ((CY_SMIF_SUCCESS == result) && (dummyCycles != 0U))
    {
        result = Cy_SMIF_SendDummyCycles(base, dummyCycles);
    }

    if (CY_SMIF_SUCCESS == result)
    {
        result = Cy_SMIF_ReceiveDataBlocking( base, value,
                    CY_SMIF_READ_ONE_BYTE, CY_SMIF_WIDTH_SINGLE, context);
    }

    return(result);
}
/*******************************************************************************
* Function Name: ValueToByteArray
****************************************************************************//**
*
* Unpacks 0-numBytes from a 4-byte value into the byte array byteArray.
*
* \param value
*  The 4-byte value to unpack.
*
* \param byteArray
* The byte array to fill.
*
* \param startPos
* The start position of the array to begin filling from.
*
* \param size
* The size of the array.
*
*
*******************************************************************************/
static void ValueToByteArray(uint32_t value, uint8_t *byteArray, uint32_t startPos, uint32_t size)
{
    do
    {
        size--;
        byteArray[size + startPos] = (uint8_t)(value & PARAM_ID_LSB_MASK);
        value >>= PARAM_ID_MSB_OFFSET; /* Shift to get the next byte */
    } while (size > 0U);
}


/*******************************************************************************
* Function Name: ByteArrayToValue
****************************************************************************//**
*
* Packs the byte array into a single value.
*
* \param byteArray
* The byte array to unpack.
*
* \param size
* The size of the array.
*
* \return
* The 4-byte value filled from the array.
*
*
*******************************************************************************/
static uint32_t ByteArrayToValue(uint8_t const *byteArray, uint32_t size)
{
    uint32_t value = 0UL;
    uint32_t idx = 0UL;
    for (idx = 0UL; idx < size; idx++)
    {
        value <<= 8;
        value |= ((uint32_t) byteArray[idx]);
    }
    return value;
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXSMIF */

#endif /* (CY_SMIF_MEMORYSLOT_H) */


/* [] END OF FILE */
