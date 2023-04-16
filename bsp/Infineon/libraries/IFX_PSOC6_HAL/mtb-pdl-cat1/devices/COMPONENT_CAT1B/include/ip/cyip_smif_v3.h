/***************************************************************************//**
* \file cyip_smif_v3.h
*
* \brief
* SMIF IP definitions
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
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

#ifndef _CYIP_SMIF_V3_H_
#define _CYIP_SMIF_V3_H_

#include "cyip_headers.h"

/*******************************************************************************
*                                     SMIF
*******************************************************************************/

#define SMIF_SMIF_CRYPTO_SECTION_SIZE           0x00000080UL
#define SMIF_DEVICE_SECTION_SIZE                0x00000080UL
#define SMIF_MPC_SECTION_SIZE                   0x00001000UL
#define SMIF_SECTION_SIZE                       0x00010000UL

/**
  * \brief Cryptography registers (one set for each key) (SMIF_SMIF_CRYPTO)
  */
typedef struct {
  __IOM uint32_t CRYPTO_CMD;                    /*!< 0x00000000 Cryptography command */
  __IOM uint32_t CRYPTO_ADDR;                   /*!< 0x00000004 Cryptography base address */
  __IOM uint32_t CRYPTO_MASK;                   /*!< 0x00000008 Cryptography mask */
  __IOM uint32_t CRYPTO_SUBREGION;              /*!< 0x0000000C Cryptography subregion disable */
   __IM uint32_t RESERVED[4];
  __IOM uint32_t CRYPTO_INPUT0;                 /*!< 0x00000020 Cryptography input 0 */
  __IOM uint32_t CRYPTO_INPUT1;                 /*!< 0x00000024 Cryptography input 1 */
  __IOM uint32_t CRYPTO_INPUT2;                 /*!< 0x00000028 Cryptography input 2 */
  __IOM uint32_t CRYPTO_INPUT3;                 /*!< 0x0000002C Cryptography input 3 */
   __IM uint32_t RESERVED1[4];
   __OM uint32_t CRYPTO_KEY0;                   /*!< 0x00000040 Cryptography key 0 */
   __OM uint32_t CRYPTO_KEY1;                   /*!< 0x00000044 Cryptography key 1 */
   __OM uint32_t CRYPTO_KEY2;                   /*!< 0x00000048 Cryptography key 2 */
   __OM uint32_t CRYPTO_KEY3;                   /*!< 0x0000004C Cryptography key 3 */
   __IM uint32_t RESERVED2[4];
  __IOM uint32_t CRYPTO_OUTPUT0;                /*!< 0x00000060 Cryptography output 0 */
  __IOM uint32_t CRYPTO_OUTPUT1;                /*!< 0x00000064 Cryptography output 1 */
  __IOM uint32_t CRYPTO_OUTPUT2;                /*!< 0x00000068 Cryptography output 2 */
  __IOM uint32_t CRYPTO_OUTPUT3;                /*!< 0x0000006C Cryptography output 3 */
   __IM uint32_t RESERVED3[4];
} SMIF_SMIF_CRYPTO_Type;                        /*!< Size = 128 (0x80) */

/**
  * \brief Device (only used for XIP acceses) (SMIF_DEVICE)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control */
   __IM uint32_t RESERVED;
  __IOM uint32_t ADDR;                          /*!< 0x00000008 Device region base address */
  __IOM uint32_t MASK;                          /*!< 0x0000000C Device region mask */
   __IM uint32_t RESERVED1[4];
  __IOM uint32_t ADDR_CTL;                      /*!< 0x00000020 Address control */
   __IM uint32_t RESERVED2[2];
  __IOM uint32_t DELAY_TAP_SEL;                 /*!< 0x0000002C RX Clock Delay Tap Select Register */
   __IM uint32_t RD_STATUS;                     /*!< 0x00000030 Read status */
   __IM uint32_t RESERVED3[3];
  __IOM uint32_t RD_CMD_CTL;                    /*!< 0x00000040 Read command control */
  __IOM uint32_t RD_ADDR_CTL;                   /*!< 0x00000044 Read address control */
  __IOM uint32_t RD_MODE_CTL;                   /*!< 0x00000048 Read mode control */
  __IOM uint32_t RD_DUMMY_CTL;                  /*!< 0x0000004C Read dummy control */
  __IOM uint32_t RD_DATA_CTL;                   /*!< 0x00000050 Read data control */
  __IOM uint32_t RD_CRC_CTL;                    /*!< 0x00000054 Read Bus CRC control */
  __IOM uint32_t RD_BOUND_CTL;                  /*!< 0x00000058 Read boundary control */
   __IM uint32_t RESERVED4;
  __IOM uint32_t WR_CMD_CTL;                    /*!< 0x00000060 Write command control */
  __IOM uint32_t WR_ADDR_CTL;                   /*!< 0x00000064 Write address control */
  __IOM uint32_t WR_MODE_CTL;                   /*!< 0x00000068 Write mode control */
  __IOM uint32_t WR_DUMMY_CTL;                  /*!< 0x0000006C Write dummy control */
  __IOM uint32_t WR_DATA_CTL;                   /*!< 0x00000070 Write data control */
  __IOM uint32_t WR_CRC_CTL;                    /*!< 0x00000074 Write Bus CRC control */
   __IM uint32_t RESERVED5[2];
} SMIF_DEVICE_Type;                             /*!< Size = 128 (0x80) */

/**
  * \brief MPC Memory Protection Controller registers (SMIF_MPC)
  */
typedef struct {
  __IOM uint32_t CFG;                           /*!< 0x00000000 Config register with error response, RegionID PPC_MPC_MAIN is
                                                                the security owner PC. The error response configuration is
                                                                located in CFG.RESPONSE, only one such configuration exists
                                                                applying to all protection contexts in the system. */
   __IM uint32_t RESERVED[3];
  __IOM uint32_t INTR;                          /*!< 0x00000010 Interrupt */
  __IOM uint32_t INTR_SET;                      /*!< 0x00000014 Interrupt set */
  __IOM uint32_t INTR_MASK;                     /*!< 0x00000018 Interrupt mask */
   __IM uint32_t INTR_MASKED;                   /*!< 0x0000001C Interrupt masked */
   __IM uint32_t INTR_INFO1;                    /*!< 0x00000020 Infor about violation */
   __IM uint32_t INTR_INFO2;                    /*!< 0x00000024 Infor about violation */
   __IM uint32_t RESERVED1[54];
  __IOM uint32_t CTRL;                          /*!< 0x00000100 Control register with lock bit and auto-increment only
                                                                (Separate CTRL for each PC depends on access_pc) */
   __IM uint32_t BLK_MAX;                       /*!< 0x00000104 Max value of block-based index register */
   __IM uint32_t BLK_CFG;                       /*!< 0x00000108 Block size & initialization in progress */
  __IOM uint32_t BLK_IDX;                       /*!< 0x0000010C Index of 32-block group accessed through BLK_LUT (Separate IDX
                                                                for each PC depending on access_pc) */
  __IOM uint32_t BLK_LUT;                       /*!< 0x00000110 NS status for 32 blocks at BLK_IDX with PC=<access_pc> */
   __IM uint32_t RESERVED2[59];
  __IOM uint32_t ROT_CTRL;                      /*!< 0x00000200 Control register with lock bit and auto-increment only */
  __IOM uint32_t ROT_CFG;                       /*!< 0x00000204 Sets block-size to match memory size (external memory only) */
   __IM uint32_t ROT_BLK_MAX;                   /*!< 0x00000208 Max value of block-based index register for ROT */
   __IM uint32_t ROT_BLK_CFG;                   /*!< 0x0000020C Same as BLK_CFG */
  __IOM uint32_t ROT_BLK_IDX;                   /*!< 0x00000210 Index of 8-block group accessed through ROT_BLK_LUT_* */
  __IOM uint32_t ROT_BLK_PC;                    /*!< 0x00000214 Protection context of 8-block group accesses through
                                                                ROT_BLK_LUT */
  __IOM uint32_t ROT_BLK_LUT;                   /*!< 0x00000218 (R,W,NS) bits for 8 blocks at ROT_BLK_IDX for PC=ROT_BKL_PC */
   __IM uint32_t RESERVED3[889];
} SMIF_MPC_Type;                                /*!< Size = 4096 (0x1000) */

/**
  * \brief Serial Memory Interface (SMIF)
  */
typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control */
   __IM uint32_t STATUS;                        /*!< 0x00000004 Status */
   __IM uint32_t RESERVED[2];
  __IOM uint32_t INT_CLOCK_DELAY_TAP_SEL0;      /*!< 0x00000010 Internal Clocking Delay Tap Select Register 0 */
  __IOM uint32_t INT_CLOCK_DELAY_TAP_SEL1;      /*!< 0x00000014 Internal Clocking Delay Tap Select Register 1 */
  __IOM uint32_t DL_CTL;                        /*!< 0x00000018 Data Learning Control Register */
   __IM uint32_t RESERVED1;
   __IM uint32_t DL_STATUS0;                    /*!< 0x00000020 Data Learning Status Register 0 */
   __IM uint32_t DL_STATUS1;                    /*!< 0x00000024 Data Learning Status Register 1 */
   __IM uint32_t RESERVED2[7];
   __IM uint32_t TX_CMD_FIFO_STATUS;            /*!< 0x00000044 Transmitter command FIFO status */
   __IM uint32_t TX_CMD_MMIO_FIFO_STATUS;       /*!< 0x00000048 Transmitter command MMIO FIFO status */
   __IM uint32_t RESERVED3;
   __OM uint32_t TX_CMD_MMIO_FIFO_WR;           /*!< 0x00000050 Transmitter command MMIO FIFO write */
   __IM uint32_t RESERVED4[11];
  __IOM uint32_t TX_DATA_MMIO_FIFO_CTL;         /*!< 0x00000080 Transmitter data MMIO FIFO control */
   __IM uint32_t TX_DATA_FIFO_STATUS;           /*!< 0x00000084 Transmitter data FIFO status */
   __IM uint32_t TX_DATA_MMIO_FIFO_STATUS;      /*!< 0x00000088 Transmitter data MMIO FIFO status */
   __IM uint32_t RESERVED5;
   __OM uint32_t TX_DATA_MMIO_FIFO_WR1;         /*!< 0x00000090 Transmitter data MMIO FIFO write */
   __OM uint32_t TX_DATA_MMIO_FIFO_WR2;         /*!< 0x00000094 Transmitter data MMIO FIFO write */
   __OM uint32_t TX_DATA_MMIO_FIFO_WR4;         /*!< 0x00000098 Transmitter data MMIO FIFO write */
   __OM uint32_t TX_DATA_MMIO_FIFO_WR1ODD;      /*!< 0x0000009C Transmitter data MMIO FIFO write */
   __IM uint32_t RESERVED6[8];
  __IOM uint32_t RX_DATA_MMIO_FIFO_CTL;         /*!< 0x000000C0 Receiver data MMIO FIFO control */
   __IM uint32_t RX_DATA_MMIO_FIFO_STATUS;      /*!< 0x000000C4 Receiver data MMIO FIFO status */
   __IM uint32_t RX_DATA_FIFO_STATUS;           /*!< 0x000000C8 Receiver data FIFO status */
   __IM uint32_t RESERVED7;
   __IM uint32_t RX_DATA_MMIO_FIFO_RD1;         /*!< 0x000000D0 Receiver data MMIO FIFO read */
   __IM uint32_t RX_DATA_MMIO_FIFO_RD2;         /*!< 0x000000D4 Receiver data MMIO FIFO read */
   __IM uint32_t RX_DATA_MMIO_FIFO_RD4;         /*!< 0x000000D8 Receiver data MMIO FIFO read */
   __IM uint32_t RESERVED8;
   __IM uint32_t RX_DATA_MMIO_FIFO_RD1_SILENT;  /*!< 0x000000E0 Receiver data MMIO FIFO silent read */
   __IM uint32_t RESERVED9[7];
  __IOM uint32_t SLOW_CA_CTL;                   /*!< 0x00000100 Slow cache control */
   __IM uint32_t RESERVED10;
  __IOM uint32_t SLOW_CA_CMD;                   /*!< 0x00000108 Slow cache command */
   __IM uint32_t RESERVED11[29];
  __IOM uint32_t FAST_CA_CTL;                   /*!< 0x00000180 Fast cache control */
   __IM uint32_t RESERVED12;
  __IOM uint32_t FAST_CA_CMD;                   /*!< 0x00000188 Fast cache command */
   __IM uint32_t RESERVED13[29];
        SMIF_SMIF_CRYPTO_Type SMIF_CRYPTO_BLOCK[8]; /*!< 0x00000200 Cryptography registers (one set for each key) */
  __IOM uint32_t CRC_CMD;                       /*!< 0x00000600 CRC Command */
   __IM uint32_t RESERVED14[7];
  __IOM uint32_t CRC_INPUT0;                    /*!< 0x00000620 CRC input 0 */
  __IOM uint32_t CRC_INPUT1;                    /*!< 0x00000624 CRC input 1 */
   __IM uint32_t RESERVED15[6];
   __IM uint32_t CRC_OUTPUT;                    /*!< 0x00000640 CRC output */
   __IM uint32_t RESERVED16[95];
  __IOM uint32_t INTR;                          /*!< 0x000007C0 Interrupt register */
  __IOM uint32_t INTR_SET;                      /*!< 0x000007C4 Interrupt set register */
  __IOM uint32_t INTR_MASK;                     /*!< 0x000007C8 Interrupt mask register */
   __IM uint32_t INTR_MASKED;                   /*!< 0x000007CC Interrupt masked register */
   __IM uint32_t INTR_CAUSE;                    /*!< 0x000007D0 Distinguishes normal vs. MPC interrupt */
   __IM uint32_t RESERVED17[11];
        SMIF_DEVICE_Type DEVICE[4];             /*!< 0x00000800 Device (only used for XIP acceses) */
   __IM uint32_t RESERVED18[384];
        SMIF_MPC_Type MPC[1];                   /*!< 0x00001000 MPC Memory Protection Controller registers */
} SMIF_Type;                                    /*!< Size = 8192 (0x2000) */


/* SMIF_SMIF_CRYPTO.CRYPTO_CMD */
#define SMIF_SMIF_CRYPTO_CRYPTO_CMD_START_Pos   0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_CMD_START_Msk   0x1UL
/* SMIF_SMIF_CRYPTO.CRYPTO_ADDR */
#define SMIF_SMIF_CRYPTO_CRYPTO_ADDR_ADDR_Pos   8UL
#define SMIF_SMIF_CRYPTO_CRYPTO_ADDR_ADDR_Msk   0xFFFFFF00UL
/* SMIF_SMIF_CRYPTO.CRYPTO_MASK */
#define SMIF_SMIF_CRYPTO_CRYPTO_MASK_MASK_Pos   8UL
#define SMIF_SMIF_CRYPTO_CRYPTO_MASK_MASK_Msk   0xFFFFFF00UL
/* SMIF_SMIF_CRYPTO.CRYPTO_SUBREGION */
#define SMIF_SMIF_CRYPTO_CRYPTO_SUBREGION_SUBREGION_DISABLE_Pos 0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_SUBREGION_SUBREGION_DISABLE_Msk 0xFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_INPUT0 */
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT0_INPUT_LSB_Pos 0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT0_INPUT_LSB_Msk 0xFUL
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT0_INPUT_MSB_Pos 4UL
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT0_INPUT_MSB_Msk 0xFFFFFFF0UL
/* SMIF_SMIF_CRYPTO.CRYPTO_INPUT1 */
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT1_INPUT_Pos 0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT1_INPUT_Msk 0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_INPUT2 */
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT2_INPUT_Pos 0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT2_INPUT_Msk 0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_INPUT3 */
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT3_INPUT_Pos 0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_INPUT3_INPUT_Msk 0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_KEY0 */
#define SMIF_SMIF_CRYPTO_CRYPTO_KEY0_KEY_Pos    0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_KEY0_KEY_Msk    0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_KEY1 */
#define SMIF_SMIF_CRYPTO_CRYPTO_KEY1_KEY_Pos    0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_KEY1_KEY_Msk    0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_KEY2 */
#define SMIF_SMIF_CRYPTO_CRYPTO_KEY2_KEY_Pos    0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_KEY2_KEY_Msk    0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_KEY3 */
#define SMIF_SMIF_CRYPTO_CRYPTO_KEY3_KEY_Pos    0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_KEY3_KEY_Msk    0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_OUTPUT0 */
#define SMIF_SMIF_CRYPTO_CRYPTO_OUTPUT0_OUTPUT_Pos 0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_OUTPUT0_OUTPUT_Msk 0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_OUTPUT1 */
#define SMIF_SMIF_CRYPTO_CRYPTO_OUTPUT1_OUTPUT_Pos 0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_OUTPUT1_OUTPUT_Msk 0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_OUTPUT2 */
#define SMIF_SMIF_CRYPTO_CRYPTO_OUTPUT2_OUTPUT_Pos 0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_OUTPUT2_OUTPUT_Msk 0xFFFFFFFFUL
/* SMIF_SMIF_CRYPTO.CRYPTO_OUTPUT3 */
#define SMIF_SMIF_CRYPTO_CRYPTO_OUTPUT3_OUTPUT_Pos 0UL
#define SMIF_SMIF_CRYPTO_CRYPTO_OUTPUT3_OUTPUT_Msk 0xFFFFFFFFUL


/* SMIF_DEVICE.CTL */
#define SMIF_DEVICE_CTL_WR_EN_Pos               0UL
#define SMIF_DEVICE_CTL_WR_EN_Msk               0x1UL
#define SMIF_DEVICE_CTL_CRYPTO_EN_Pos           4UL
#define SMIF_DEVICE_CTL_CRYPTO_EN_Msk           0x10UL
#define SMIF_DEVICE_CTL_DATA_SEL_Pos            8UL
#define SMIF_DEVICE_CTL_DATA_SEL_Msk            0x300UL
#define SMIF_DEVICE_CTL_MERGE_TIMEOUT_Pos       12UL
#define SMIF_DEVICE_CTL_MERGE_TIMEOUT_Msk       0x7000UL
#define SMIF_DEVICE_CTL_MERGE_EN_Pos            15UL
#define SMIF_DEVICE_CTL_MERGE_EN_Msk            0x8000UL
#define SMIF_DEVICE_CTL_TOTAL_TIMEOUT_Pos       16UL
#define SMIF_DEVICE_CTL_TOTAL_TIMEOUT_Msk       0x3FFF0000UL
#define SMIF_DEVICE_CTL_TOTAL_TIMEOUT_EN_Pos    30UL
#define SMIF_DEVICE_CTL_TOTAL_TIMEOUT_EN_Msk    0x40000000UL
#define SMIF_DEVICE_CTL_ENABLED_Pos             31UL
#define SMIF_DEVICE_CTL_ENABLED_Msk             0x80000000UL
/* SMIF_DEVICE.ADDR */
#define SMIF_DEVICE_ADDR_ADDR_Pos               8UL
#define SMIF_DEVICE_ADDR_ADDR_Msk               0xFFFFFF00UL
/* SMIF_DEVICE.MASK */
#define SMIF_DEVICE_MASK_MASK_Pos               8UL
#define SMIF_DEVICE_MASK_MASK_Msk               0xFFFFFF00UL
/* SMIF_DEVICE.ADDR_CTL */
#define SMIF_DEVICE_ADDR_CTL_SIZE3_Pos          0UL
#define SMIF_DEVICE_ADDR_CTL_SIZE3_Msk          0x7UL
#define SMIF_DEVICE_ADDR_CTL_DIV2_Pos           8UL
#define SMIF_DEVICE_ADDR_CTL_DIV2_Msk           0x100UL
/* SMIF_DEVICE.DELAY_TAP_SEL */
#define SMIF_DEVICE_DELAY_TAP_SEL_SEL_Pos       0UL
#define SMIF_DEVICE_DELAY_TAP_SEL_SEL_Msk       0xFFUL
/* SMIF_DEVICE.RD_STATUS */
#define SMIF_DEVICE_RD_STATUS_FS_STATUS_Pos     0UL
#define SMIF_DEVICE_RD_STATUS_FS_STATUS_Msk     0xFFUL
/* SMIF_DEVICE.RD_CMD_CTL */
#define SMIF_DEVICE_RD_CMD_CTL_CODE_Pos         0UL
#define SMIF_DEVICE_RD_CMD_CTL_CODE_Msk         0xFFUL
#define SMIF_DEVICE_RD_CMD_CTL_CODEH_Pos        8UL
#define SMIF_DEVICE_RD_CMD_CTL_CODEH_Msk        0xFF00UL
#define SMIF_DEVICE_RD_CMD_CTL_WIDTH_Pos        16UL
#define SMIF_DEVICE_RD_CMD_CTL_WIDTH_Msk        0x30000UL
#define SMIF_DEVICE_RD_CMD_CTL_DDR_MODE_Pos     18UL
#define SMIF_DEVICE_RD_CMD_CTL_DDR_MODE_Msk     0x40000UL
#define SMIF_DEVICE_RD_CMD_CTL_PRESENT2_Pos     30UL
#define SMIF_DEVICE_RD_CMD_CTL_PRESENT2_Msk     0xC0000000UL
/* SMIF_DEVICE.RD_ADDR_CTL */
#define SMIF_DEVICE_RD_ADDR_CTL_WIDTH_Pos       16UL
#define SMIF_DEVICE_RD_ADDR_CTL_WIDTH_Msk       0x30000UL
#define SMIF_DEVICE_RD_ADDR_CTL_DDR_MODE_Pos    18UL
#define SMIF_DEVICE_RD_ADDR_CTL_DDR_MODE_Msk    0x40000UL
/* SMIF_DEVICE.RD_MODE_CTL */
#define SMIF_DEVICE_RD_MODE_CTL_CODE_Pos        0UL
#define SMIF_DEVICE_RD_MODE_CTL_CODE_Msk        0xFFUL
#define SMIF_DEVICE_RD_MODE_CTL_CODEH_Pos       8UL
#define SMIF_DEVICE_RD_MODE_CTL_CODEH_Msk       0xFF00UL
#define SMIF_DEVICE_RD_MODE_CTL_WIDTH_Pos       16UL
#define SMIF_DEVICE_RD_MODE_CTL_WIDTH_Msk       0x30000UL
#define SMIF_DEVICE_RD_MODE_CTL_DDR_MODE_Pos    18UL
#define SMIF_DEVICE_RD_MODE_CTL_DDR_MODE_Msk    0x40000UL
#define SMIF_DEVICE_RD_MODE_CTL_PRESENT2_Pos    30UL
#define SMIF_DEVICE_RD_MODE_CTL_PRESENT2_Msk    0xC0000000UL
/* SMIF_DEVICE.RD_DUMMY_CTL */
#define SMIF_DEVICE_RD_DUMMY_CTL_SIZE5_Pos      0UL
#define SMIF_DEVICE_RD_DUMMY_CTL_SIZE5_Msk      0x1FUL
#define SMIF_DEVICE_RD_DUMMY_CTL_PRESENT2_Pos   30UL
#define SMIF_DEVICE_RD_DUMMY_CTL_PRESENT2_Msk   0xC0000000UL
/* SMIF_DEVICE.RD_DATA_CTL */
#define SMIF_DEVICE_RD_DATA_CTL_WIDTH_Pos       16UL
#define SMIF_DEVICE_RD_DATA_CTL_WIDTH_Msk       0x30000UL
#define SMIF_DEVICE_RD_DATA_CTL_DDR_MODE_Pos    18UL
#define SMIF_DEVICE_RD_DATA_CTL_DDR_MODE_Msk    0x40000UL
/* SMIF_DEVICE.RD_CRC_CTL */
#define SMIF_DEVICE_RD_CRC_CTL_STATUS_CHECK_MASK_Pos 0UL
#define SMIF_DEVICE_RD_CRC_CTL_STATUS_CHECK_MASK_Msk 0xFFUL
#define SMIF_DEVICE_RD_CRC_CTL_STATUS_ERROR_POL_Pos 8UL
#define SMIF_DEVICE_RD_CRC_CTL_STATUS_ERROR_POL_Msk 0xFF00UL
#define SMIF_DEVICE_RD_CRC_CTL_DATA_CRC_INPUT_SIZE_Pos 16UL
#define SMIF_DEVICE_RD_CRC_CTL_DATA_CRC_INPUT_SIZE_Msk 0xFF0000UL
#define SMIF_DEVICE_RD_CRC_CTL_CMD_ADDR_CRC_WIDTH_Pos 24UL
#define SMIF_DEVICE_RD_CRC_CTL_CMD_ADDR_CRC_WIDTH_Msk 0x3000000UL
#define SMIF_DEVICE_RD_CRC_CTL_CMD_ADDR_CRC_DDR_MODE_Pos 26UL
#define SMIF_DEVICE_RD_CRC_CTL_CMD_ADDR_CRC_DDR_MODE_Msk 0x4000000UL
#define SMIF_DEVICE_RD_CRC_CTL_CMD_ADDR_CRC_INPUT_Pos 27UL
#define SMIF_DEVICE_RD_CRC_CTL_CMD_ADDR_CRC_INPUT_Msk 0x8000000UL
#define SMIF_DEVICE_RD_CRC_CTL_DATA_CRC_CHECK_Pos 28UL
#define SMIF_DEVICE_RD_CRC_CTL_DATA_CRC_CHECK_Msk 0x10000000UL
#define SMIF_DEVICE_RD_CRC_CTL_CMD_ADDR_CRC_PRESENT_Pos 30UL
#define SMIF_DEVICE_RD_CRC_CTL_CMD_ADDR_CRC_PRESENT_Msk 0x40000000UL
#define SMIF_DEVICE_RD_CRC_CTL_DATA_CRC_PRESENT_Pos 31UL
#define SMIF_DEVICE_RD_CRC_CTL_DATA_CRC_PRESENT_Msk 0x80000000UL
/* SMIF_DEVICE.RD_BOUND_CTL */
#define SMIF_DEVICE_RD_BOUND_CTL_SIZE5_Pos      0UL
#define SMIF_DEVICE_RD_BOUND_CTL_SIZE5_Msk      0x1FUL
#define SMIF_DEVICE_RD_BOUND_CTL_SUB_PAGE_SIZE_Pos 16UL
#define SMIF_DEVICE_RD_BOUND_CTL_SUB_PAGE_SIZE_Msk 0x30000UL
#define SMIF_DEVICE_RD_BOUND_CTL_SUB_PAGE_NR_Pos 20UL
#define SMIF_DEVICE_RD_BOUND_CTL_SUB_PAGE_NR_Msk 0x300000UL
#define SMIF_DEVICE_RD_BOUND_CTL_SUBSEQ_BOUND_EN_Pos 28UL
#define SMIF_DEVICE_RD_BOUND_CTL_SUBSEQ_BOUND_EN_Msk 0x10000000UL
#define SMIF_DEVICE_RD_BOUND_CTL_PRESENT_Pos    31UL
#define SMIF_DEVICE_RD_BOUND_CTL_PRESENT_Msk    0x80000000UL
/* SMIF_DEVICE.WR_CMD_CTL */
#define SMIF_DEVICE_WR_CMD_CTL_CODE_Pos         0UL
#define SMIF_DEVICE_WR_CMD_CTL_CODE_Msk         0xFFUL
#define SMIF_DEVICE_WR_CMD_CTL_CODEH_Pos        8UL
#define SMIF_DEVICE_WR_CMD_CTL_CODEH_Msk        0xFF00UL
#define SMIF_DEVICE_WR_CMD_CTL_WIDTH_Pos        16UL
#define SMIF_DEVICE_WR_CMD_CTL_WIDTH_Msk        0x30000UL
#define SMIF_DEVICE_WR_CMD_CTL_DDR_MODE_Pos     18UL
#define SMIF_DEVICE_WR_CMD_CTL_DDR_MODE_Msk     0x40000UL
#define SMIF_DEVICE_WR_CMD_CTL_PRESENT2_Pos     30UL
#define SMIF_DEVICE_WR_CMD_CTL_PRESENT2_Msk     0xC0000000UL
/* SMIF_DEVICE.WR_ADDR_CTL */
#define SMIF_DEVICE_WR_ADDR_CTL_WIDTH_Pos       16UL
#define SMIF_DEVICE_WR_ADDR_CTL_WIDTH_Msk       0x30000UL
#define SMIF_DEVICE_WR_ADDR_CTL_DDR_MODE_Pos    18UL
#define SMIF_DEVICE_WR_ADDR_CTL_DDR_MODE_Msk    0x40000UL
/* SMIF_DEVICE.WR_MODE_CTL */
#define SMIF_DEVICE_WR_MODE_CTL_CODE_Pos        0UL
#define SMIF_DEVICE_WR_MODE_CTL_CODE_Msk        0xFFUL
#define SMIF_DEVICE_WR_MODE_CTL_CODEH_Pos       8UL
#define SMIF_DEVICE_WR_MODE_CTL_CODEH_Msk       0xFF00UL
#define SMIF_DEVICE_WR_MODE_CTL_WIDTH_Pos       16UL
#define SMIF_DEVICE_WR_MODE_CTL_WIDTH_Msk       0x30000UL
#define SMIF_DEVICE_WR_MODE_CTL_DDR_MODE_Pos    18UL
#define SMIF_DEVICE_WR_MODE_CTL_DDR_MODE_Msk    0x40000UL
#define SMIF_DEVICE_WR_MODE_CTL_PRESENT2_Pos    30UL
#define SMIF_DEVICE_WR_MODE_CTL_PRESENT2_Msk    0xC0000000UL
/* SMIF_DEVICE.WR_DUMMY_CTL */
#define SMIF_DEVICE_WR_DUMMY_CTL_SIZE5_Pos      0UL
#define SMIF_DEVICE_WR_DUMMY_CTL_SIZE5_Msk      0x1FUL
#define SMIF_DEVICE_WR_DUMMY_CTL_RWDS_EN_Pos    17UL
#define SMIF_DEVICE_WR_DUMMY_CTL_RWDS_EN_Msk    0x20000UL
#define SMIF_DEVICE_WR_DUMMY_CTL_PRESENT2_Pos   30UL
#define SMIF_DEVICE_WR_DUMMY_CTL_PRESENT2_Msk   0xC0000000UL
/* SMIF_DEVICE.WR_DATA_CTL */
#define SMIF_DEVICE_WR_DATA_CTL_WIDTH_Pos       16UL
#define SMIF_DEVICE_WR_DATA_CTL_WIDTH_Msk       0x30000UL
#define SMIF_DEVICE_WR_DATA_CTL_DDR_MODE_Pos    18UL
#define SMIF_DEVICE_WR_DATA_CTL_DDR_MODE_Msk    0x40000UL
/* SMIF_DEVICE.WR_CRC_CTL */
#define SMIF_DEVICE_WR_CRC_CTL_DATA_CRC_INPUT_SIZE_Pos 16UL
#define SMIF_DEVICE_WR_CRC_CTL_DATA_CRC_INPUT_SIZE_Msk 0xFF0000UL
#define SMIF_DEVICE_WR_CRC_CTL_CMD_ADDR_CRC_WIDTH_Pos 24UL
#define SMIF_DEVICE_WR_CRC_CTL_CMD_ADDR_CRC_WIDTH_Msk 0x3000000UL
#define SMIF_DEVICE_WR_CRC_CTL_CMD_ADDR_CRC_DDR_MODE_Pos 26UL
#define SMIF_DEVICE_WR_CRC_CTL_CMD_ADDR_CRC_DDR_MODE_Msk 0x4000000UL
#define SMIF_DEVICE_WR_CRC_CTL_CMD_ADDR_CRC_INPUT_Pos 27UL
#define SMIF_DEVICE_WR_CRC_CTL_CMD_ADDR_CRC_INPUT_Msk 0x8000000UL
#define SMIF_DEVICE_WR_CRC_CTL_CMD_ADDR_CRC_PRESENT_Pos 30UL
#define SMIF_DEVICE_WR_CRC_CTL_CMD_ADDR_CRC_PRESENT_Msk 0x40000000UL
#define SMIF_DEVICE_WR_CRC_CTL_DATA_CRC_PRESENT_Pos 31UL
#define SMIF_DEVICE_WR_CRC_CTL_DATA_CRC_PRESENT_Msk 0x80000000UL


/* SMIF_MPC.CFG */
#define SMIF_MPC_CFG_RESPONSE_Pos               4UL
#define SMIF_MPC_CFG_RESPONSE_Msk               0x10UL
/* SMIF_MPC.INTR */
#define SMIF_MPC_INTR_VIOLATION_Pos             0UL
#define SMIF_MPC_INTR_VIOLATION_Msk             0x1UL
/* SMIF_MPC.INTR_SET */
#define SMIF_MPC_INTR_SET_VIOLATION_Pos         0UL
#define SMIF_MPC_INTR_SET_VIOLATION_Msk         0x1UL
/* SMIF_MPC.INTR_MASK */
#define SMIF_MPC_INTR_MASK_VIOLATION_Pos        0UL
#define SMIF_MPC_INTR_MASK_VIOLATION_Msk        0x1UL
/* SMIF_MPC.INTR_MASKED */
#define SMIF_MPC_INTR_MASKED_VIOLATION_Pos      0UL
#define SMIF_MPC_INTR_MASKED_VIOLATION_Msk      0x1UL
/* SMIF_MPC.INTR_INFO1 */
#define SMIF_MPC_INTR_INFO1_VALUE_Pos           0UL
#define SMIF_MPC_INTR_INFO1_VALUE_Msk           0xFFFFFFFFUL
/* SMIF_MPC.INTR_INFO2 */
#define SMIF_MPC_INTR_INFO2_HMASTER_Pos         0UL
#define SMIF_MPC_INTR_INFO2_HMASTER_Msk         0xFFFFUL
#define SMIF_MPC_INTR_INFO2_HNONSEC_Pos         16UL
#define SMIF_MPC_INTR_INFO2_HNONSEC_Msk         0x10000UL
#define SMIF_MPC_INTR_INFO2_CFG_NS_Pos          17UL
#define SMIF_MPC_INTR_INFO2_CFG_NS_Msk          0x20000UL
#define SMIF_MPC_INTR_INFO2_HWRITE_Pos          18UL
#define SMIF_MPC_INTR_INFO2_HWRITE_Msk          0x40000UL
#define SMIF_MPC_INTR_INFO2_HAUSER_Pos          24UL
#define SMIF_MPC_INTR_INFO2_HAUSER_Msk          0xF000000UL
#define SMIF_MPC_INTR_INFO2_SECURITY_VIOLATION_Pos 30UL
#define SMIF_MPC_INTR_INFO2_SECURITY_VIOLATION_Msk 0x40000000UL
#define SMIF_MPC_INTR_INFO2_ACCESS_VIOLATION_Pos 31UL
#define SMIF_MPC_INTR_INFO2_ACCESS_VIOLATION_Msk 0x80000000UL
/* SMIF_MPC.CTRL */
#define SMIF_MPC_CTRL_AUTO_INC_Pos              8UL
#define SMIF_MPC_CTRL_AUTO_INC_Msk              0x100UL
#define SMIF_MPC_CTRL_LOCK_Pos                  31UL
#define SMIF_MPC_CTRL_LOCK_Msk                  0x80000000UL
/* SMIF_MPC.BLK_MAX */
#define SMIF_MPC_BLK_MAX_VALUE_Pos              0UL
#define SMIF_MPC_BLK_MAX_VALUE_Msk              0xFFFFFFFFUL
/* SMIF_MPC.BLK_CFG */
#define SMIF_MPC_BLK_CFG_BLOCK_SIZE_Pos         0UL
#define SMIF_MPC_BLK_CFG_BLOCK_SIZE_Msk         0xFUL
#define SMIF_MPC_BLK_CFG_INIT_IN_PROGRESS_Pos   31UL
#define SMIF_MPC_BLK_CFG_INIT_IN_PROGRESS_Msk   0x80000000UL
/* SMIF_MPC.BLK_IDX */
#define SMIF_MPC_BLK_IDX_VALUE_Pos              0UL
#define SMIF_MPC_BLK_IDX_VALUE_Msk              0xFFFFFFFFUL
/* SMIF_MPC.BLK_LUT */
#define SMIF_MPC_BLK_LUT_ATTR_NS0_Pos           0UL
#define SMIF_MPC_BLK_LUT_ATTR_NS0_Msk           0x1UL
#define SMIF_MPC_BLK_LUT_ATTR_NS1_Pos           1UL
#define SMIF_MPC_BLK_LUT_ATTR_NS1_Msk           0x2UL
#define SMIF_MPC_BLK_LUT_ATTR_NS2_Pos           2UL
#define SMIF_MPC_BLK_LUT_ATTR_NS2_Msk           0x4UL
#define SMIF_MPC_BLK_LUT_ATTR_NS3_Pos           3UL
#define SMIF_MPC_BLK_LUT_ATTR_NS3_Msk           0x8UL
#define SMIF_MPC_BLK_LUT_ATTR_NS4_Pos           4UL
#define SMIF_MPC_BLK_LUT_ATTR_NS4_Msk           0x10UL
#define SMIF_MPC_BLK_LUT_ATTR_NS5_Pos           5UL
#define SMIF_MPC_BLK_LUT_ATTR_NS5_Msk           0x20UL
#define SMIF_MPC_BLK_LUT_ATTR_NS6_Pos           6UL
#define SMIF_MPC_BLK_LUT_ATTR_NS6_Msk           0x40UL
#define SMIF_MPC_BLK_LUT_ATTR_NS7_Pos           7UL
#define SMIF_MPC_BLK_LUT_ATTR_NS7_Msk           0x80UL
#define SMIF_MPC_BLK_LUT_ATTR_NS8_Pos           8UL
#define SMIF_MPC_BLK_LUT_ATTR_NS8_Msk           0x100UL
#define SMIF_MPC_BLK_LUT_ATTR_NS9_Pos           9UL
#define SMIF_MPC_BLK_LUT_ATTR_NS9_Msk           0x200UL
#define SMIF_MPC_BLK_LUT_ATTR_NS10_Pos          10UL
#define SMIF_MPC_BLK_LUT_ATTR_NS10_Msk          0x400UL
#define SMIF_MPC_BLK_LUT_ATTR_NS11_Pos          11UL
#define SMIF_MPC_BLK_LUT_ATTR_NS11_Msk          0x800UL
#define SMIF_MPC_BLK_LUT_ATTR_NS12_Pos          12UL
#define SMIF_MPC_BLK_LUT_ATTR_NS12_Msk          0x1000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS13_Pos          13UL
#define SMIF_MPC_BLK_LUT_ATTR_NS13_Msk          0x2000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS14_Pos          14UL
#define SMIF_MPC_BLK_LUT_ATTR_NS14_Msk          0x4000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS15_Pos          15UL
#define SMIF_MPC_BLK_LUT_ATTR_NS15_Msk          0x8000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS16_Pos          16UL
#define SMIF_MPC_BLK_LUT_ATTR_NS16_Msk          0x10000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS17_Pos          17UL
#define SMIF_MPC_BLK_LUT_ATTR_NS17_Msk          0x20000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS18_Pos          18UL
#define SMIF_MPC_BLK_LUT_ATTR_NS18_Msk          0x40000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS19_Pos          19UL
#define SMIF_MPC_BLK_LUT_ATTR_NS19_Msk          0x80000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS20_Pos          20UL
#define SMIF_MPC_BLK_LUT_ATTR_NS20_Msk          0x100000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS21_Pos          21UL
#define SMIF_MPC_BLK_LUT_ATTR_NS21_Msk          0x200000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS22_Pos          22UL
#define SMIF_MPC_BLK_LUT_ATTR_NS22_Msk          0x400000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS23_Pos          23UL
#define SMIF_MPC_BLK_LUT_ATTR_NS23_Msk          0x800000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS24_Pos          24UL
#define SMIF_MPC_BLK_LUT_ATTR_NS24_Msk          0x1000000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS25_Pos          25UL
#define SMIF_MPC_BLK_LUT_ATTR_NS25_Msk          0x2000000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS26_Pos          26UL
#define SMIF_MPC_BLK_LUT_ATTR_NS26_Msk          0x4000000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS27_Pos          27UL
#define SMIF_MPC_BLK_LUT_ATTR_NS27_Msk          0x8000000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS28_Pos          28UL
#define SMIF_MPC_BLK_LUT_ATTR_NS28_Msk          0x10000000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS29_Pos          29UL
#define SMIF_MPC_BLK_LUT_ATTR_NS29_Msk          0x20000000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS30_Pos          30UL
#define SMIF_MPC_BLK_LUT_ATTR_NS30_Msk          0x40000000UL
#define SMIF_MPC_BLK_LUT_ATTR_NS31_Pos          31UL
#define SMIF_MPC_BLK_LUT_ATTR_NS31_Msk          0x80000000UL
/* SMIF_MPC.ROT_CTRL */
#define SMIF_MPC_ROT_CTRL_AUTO_INC_Pos          8UL
#define SMIF_MPC_ROT_CTRL_AUTO_INC_Msk          0x100UL
#define SMIF_MPC_ROT_CTRL_LOCK_Pos              31UL
#define SMIF_MPC_ROT_CTRL_LOCK_Msk              0x80000000UL
/* SMIF_MPC.ROT_CFG */
#define SMIF_MPC_ROT_CFG_BLOCK_SIZE_Pos         0UL
#define SMIF_MPC_ROT_CFG_BLOCK_SIZE_Msk         0xFUL
/* SMIF_MPC.ROT_BLK_MAX */
#define SMIF_MPC_ROT_BLK_MAX_VALUE_Pos          0UL
#define SMIF_MPC_ROT_BLK_MAX_VALUE_Msk          0xFFFFFFFFUL
/* SMIF_MPC.ROT_BLK_CFG */
#define SMIF_MPC_ROT_BLK_CFG_BLOCK_SIZE_Pos     0UL
#define SMIF_MPC_ROT_BLK_CFG_BLOCK_SIZE_Msk     0xFUL
#define SMIF_MPC_ROT_BLK_CFG_INIT_IN_PROGRESS_Pos 31UL
#define SMIF_MPC_ROT_BLK_CFG_INIT_IN_PROGRESS_Msk 0x80000000UL
/* SMIF_MPC.ROT_BLK_IDX */
#define SMIF_MPC_ROT_BLK_IDX_VALUE_Pos          0UL
#define SMIF_MPC_ROT_BLK_IDX_VALUE_Msk          0xFFFFFFFFUL
/* SMIF_MPC.ROT_BLK_PC */
#define SMIF_MPC_ROT_BLK_PC_PC_Pos              0UL
#define SMIF_MPC_ROT_BLK_PC_PC_Msk              0xFUL
/* SMIF_MPC.ROT_BLK_LUT */
#define SMIF_MPC_ROT_BLK_LUT_ATTR0_Pos          0UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR0_Msk          0x7UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR1_Pos          4UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR1_Msk          0x70UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR2_Pos          8UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR2_Msk          0x700UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR3_Pos          12UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR3_Msk          0x7000UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR4_Pos          16UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR4_Msk          0x70000UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR5_Pos          20UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR5_Msk          0x700000UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR6_Pos          24UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR6_Msk          0x7000000UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR7_Pos          28UL
#define SMIF_MPC_ROT_BLK_LUT_ATTR7_Msk          0x70000000UL


/* SMIF.CTL */
#define SMIF_CTL_XIP_MODE_Pos                   0UL
#define SMIF_CTL_XIP_MODE_Msk                   0x1UL
#define SMIF_CTL_CLOCK_IF_TX_SEL_Pos            4UL
#define SMIF_CTL_CLOCK_IF_TX_SEL_Msk            0x10UL
#define SMIF_CTL_DELAY_LINE_SEL_Pos             5UL
#define SMIF_CTL_DELAY_LINE_SEL_Msk             0xE0UL
#define SMIF_CTL_DELAY_TAP_ENABLED_Pos          8UL
#define SMIF_CTL_DELAY_TAP_ENABLED_Msk          0x100UL
#define SMIF_CTL_INT_CLOCK_DL_ENABLED_Pos       9UL
#define SMIF_CTL_INT_CLOCK_DL_ENABLED_Msk       0x200UL
#define SMIF_CTL_INT_CLOCK_CAPTURE_CYCLE_Pos    10UL
#define SMIF_CTL_INT_CLOCK_CAPTURE_CYCLE_Msk    0xC00UL
#define SMIF_CTL_CLOCK_IF_RX_SEL_Pos            12UL
#define SMIF_CTL_CLOCK_IF_RX_SEL_Msk            0x7000UL
#define SMIF_CTL_DESELECT_DELAY_Pos             16UL
#define SMIF_CTL_DESELECT_DELAY_Msk             0x70000UL
#define SMIF_CTL_SELECT_SETUP_DELAY_Pos         20UL
#define SMIF_CTL_SELECT_SETUP_DELAY_Msk         0x300000UL
#define SMIF_CTL_SELECT_HOLD_DELAY_Pos          22UL
#define SMIF_CTL_SELECT_HOLD_DELAY_Msk          0xC00000UL
#define SMIF_CTL_BLOCK_Pos                      24UL
#define SMIF_CTL_BLOCK_Msk                      0x1000000UL
#define SMIF_CTL_CLOCK_IF_SEL_Pos               25UL
#define SMIF_CTL_CLOCK_IF_SEL_Msk               0x2000000UL
#define SMIF_CTL_ENABLED_Pos                    31UL
#define SMIF_CTL_ENABLED_Msk                    0x80000000UL
/* SMIF.STATUS */
#define SMIF_STATUS_BUSY_Pos                    31UL
#define SMIF_STATUS_BUSY_Msk                    0x80000000UL
/* SMIF.INT_CLOCK_DELAY_TAP_SEL0 */
#define SMIF_INT_CLOCK_DELAY_TAP_SEL0_DATA_BIT0_Pos 0UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL0_DATA_BIT0_Msk 0xFFUL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL0_DATA_BIT1_Pos 8UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL0_DATA_BIT1_Msk 0xFF00UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL0_DATA_BIT2_Pos 16UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL0_DATA_BIT2_Msk 0xFF0000UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL0_DATA_BIT3_Pos 24UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL0_DATA_BIT3_Msk 0xFF000000UL
/* SMIF.INT_CLOCK_DELAY_TAP_SEL1 */
#define SMIF_INT_CLOCK_DELAY_TAP_SEL1_DATA_BIT4_Pos 0UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL1_DATA_BIT4_Msk 0xFFUL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL1_DATA_BIT5_Pos 8UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL1_DATA_BIT5_Msk 0xFF00UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL1_DATA_BIT6_Pos 16UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL1_DATA_BIT6_Msk 0xFF0000UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL1_DATA_BIT7_Pos 24UL
#define SMIF_INT_CLOCK_DELAY_TAP_SEL1_DATA_BIT7_Msk 0xFF000000UL
/* SMIF.DL_CTL */
#define SMIF_DL_CTL_DLP_Pos                     0UL
#define SMIF_DL_CTL_DLP_Msk                     0xFFFFUL
#define SMIF_DL_CTL_DLP_SIZE_Pos                16UL
#define SMIF_DL_CTL_DLP_SIZE_Msk                0xF0000UL
#define SMIF_DL_CTL_DL_WARNING_LEVEL_Pos        24UL
#define SMIF_DL_CTL_DL_WARNING_LEVEL_Msk        0xF000000UL
/* SMIF.DL_STATUS0 */
#define SMIF_DL_STATUS0_DATA_BIT0_Pos           0UL
#define SMIF_DL_STATUS0_DATA_BIT0_Msk           0xFFUL
#define SMIF_DL_STATUS0_DATA_BIT1_Pos           8UL
#define SMIF_DL_STATUS0_DATA_BIT1_Msk           0xFF00UL
#define SMIF_DL_STATUS0_DATA_BIT2_Pos           16UL
#define SMIF_DL_STATUS0_DATA_BIT2_Msk           0xFF0000UL
#define SMIF_DL_STATUS0_DATA_BIT3_Pos           24UL
#define SMIF_DL_STATUS0_DATA_BIT3_Msk           0xFF000000UL
/* SMIF.DL_STATUS1 */
#define SMIF_DL_STATUS1_DATA_BIT4_Pos           0UL
#define SMIF_DL_STATUS1_DATA_BIT4_Msk           0xFFUL
#define SMIF_DL_STATUS1_DATA_BIT5_Pos           8UL
#define SMIF_DL_STATUS1_DATA_BIT5_Msk           0xFF00UL
#define SMIF_DL_STATUS1_DATA_BIT6_Pos           16UL
#define SMIF_DL_STATUS1_DATA_BIT6_Msk           0xFF0000UL
#define SMIF_DL_STATUS1_DATA_BIT7_Pos           24UL
#define SMIF_DL_STATUS1_DATA_BIT7_Msk           0xFF000000UL
/* SMIF.TX_CMD_FIFO_STATUS */
#define SMIF_TX_CMD_FIFO_STATUS_USED4_Pos       0UL
#define SMIF_TX_CMD_FIFO_STATUS_USED4_Msk       0xFUL
/* SMIF.TX_CMD_MMIO_FIFO_STATUS */
#define SMIF_TX_CMD_MMIO_FIFO_STATUS_USED4_Pos  0UL
#define SMIF_TX_CMD_MMIO_FIFO_STATUS_USED4_Msk  0xFUL
/* SMIF.TX_CMD_MMIO_FIFO_WR */
#define SMIF_TX_CMD_MMIO_FIFO_WR_DATA27_Pos     0UL
#define SMIF_TX_CMD_MMIO_FIFO_WR_DATA27_Msk     0x7FFFFFFUL
/* SMIF.TX_DATA_MMIO_FIFO_CTL */
#define SMIF_TX_DATA_MMIO_FIFO_CTL_TX_TRIGGER_LEVEL_Pos 0UL
#define SMIF_TX_DATA_MMIO_FIFO_CTL_TX_TRIGGER_LEVEL_Msk 0x7UL
/* SMIF.TX_DATA_FIFO_STATUS */
#define SMIF_TX_DATA_FIFO_STATUS_USED4_Pos      0UL
#define SMIF_TX_DATA_FIFO_STATUS_USED4_Msk      0xFUL
/* SMIF.TX_DATA_MMIO_FIFO_STATUS */
#define SMIF_TX_DATA_MMIO_FIFO_STATUS_USED4_Pos 0UL
#define SMIF_TX_DATA_MMIO_FIFO_STATUS_USED4_Msk 0xFUL
/* SMIF.TX_DATA_MMIO_FIFO_WR1 */
#define SMIF_TX_DATA_MMIO_FIFO_WR1_DATA0_Pos    0UL
#define SMIF_TX_DATA_MMIO_FIFO_WR1_DATA0_Msk    0xFFUL
/* SMIF.TX_DATA_MMIO_FIFO_WR2 */
#define SMIF_TX_DATA_MMIO_FIFO_WR2_DATA0_Pos    0UL
#define SMIF_TX_DATA_MMIO_FIFO_WR2_DATA0_Msk    0xFFUL
#define SMIF_TX_DATA_MMIO_FIFO_WR2_DATA1_Pos    8UL
#define SMIF_TX_DATA_MMIO_FIFO_WR2_DATA1_Msk    0xFF00UL
/* SMIF.TX_DATA_MMIO_FIFO_WR4 */
#define SMIF_TX_DATA_MMIO_FIFO_WR4_DATA0_Pos    0UL
#define SMIF_TX_DATA_MMIO_FIFO_WR4_DATA0_Msk    0xFFUL
#define SMIF_TX_DATA_MMIO_FIFO_WR4_DATA1_Pos    8UL
#define SMIF_TX_DATA_MMIO_FIFO_WR4_DATA1_Msk    0xFF00UL
#define SMIF_TX_DATA_MMIO_FIFO_WR4_DATA2_Pos    16UL
#define SMIF_TX_DATA_MMIO_FIFO_WR4_DATA2_Msk    0xFF0000UL
#define SMIF_TX_DATA_MMIO_FIFO_WR4_DATA3_Pos    24UL
#define SMIF_TX_DATA_MMIO_FIFO_WR4_DATA3_Msk    0xFF000000UL
/* SMIF.TX_DATA_MMIO_FIFO_WR1ODD */
#define SMIF_TX_DATA_MMIO_FIFO_WR1ODD_DATA0_Pos 0UL
#define SMIF_TX_DATA_MMIO_FIFO_WR1ODD_DATA0_Msk 0xFFUL
/* SMIF.RX_DATA_MMIO_FIFO_CTL */
#define SMIF_RX_DATA_MMIO_FIFO_CTL_RX_TRIGGER_LEVEL_Pos 0UL
#define SMIF_RX_DATA_MMIO_FIFO_CTL_RX_TRIGGER_LEVEL_Msk 0x7UL
/* SMIF.RX_DATA_MMIO_FIFO_STATUS */
#define SMIF_RX_DATA_MMIO_FIFO_STATUS_USED4_Pos 0UL
#define SMIF_RX_DATA_MMIO_FIFO_STATUS_USED4_Msk 0xFUL
/* SMIF.RX_DATA_FIFO_STATUS */
#define SMIF_RX_DATA_FIFO_STATUS_USED4_Pos      0UL
#define SMIF_RX_DATA_FIFO_STATUS_USED4_Msk      0xFUL
#define SMIF_RX_DATA_FIFO_STATUS_RX_SR_USED_Pos 8UL
#define SMIF_RX_DATA_FIFO_STATUS_RX_SR_USED_Msk 0x100UL
/* SMIF.RX_DATA_MMIO_FIFO_RD1 */
#define SMIF_RX_DATA_MMIO_FIFO_RD1_DATA0_Pos    0UL
#define SMIF_RX_DATA_MMIO_FIFO_RD1_DATA0_Msk    0xFFUL
/* SMIF.RX_DATA_MMIO_FIFO_RD2 */
#define SMIF_RX_DATA_MMIO_FIFO_RD2_DATA0_Pos    0UL
#define SMIF_RX_DATA_MMIO_FIFO_RD2_DATA0_Msk    0xFFUL
#define SMIF_RX_DATA_MMIO_FIFO_RD2_DATA1_Pos    8UL
#define SMIF_RX_DATA_MMIO_FIFO_RD2_DATA1_Msk    0xFF00UL
/* SMIF.RX_DATA_MMIO_FIFO_RD4 */
#define SMIF_RX_DATA_MMIO_FIFO_RD4_DATA0_Pos    0UL
#define SMIF_RX_DATA_MMIO_FIFO_RD4_DATA0_Msk    0xFFUL
#define SMIF_RX_DATA_MMIO_FIFO_RD4_DATA1_Pos    8UL
#define SMIF_RX_DATA_MMIO_FIFO_RD4_DATA1_Msk    0xFF00UL
#define SMIF_RX_DATA_MMIO_FIFO_RD4_DATA2_Pos    16UL
#define SMIF_RX_DATA_MMIO_FIFO_RD4_DATA2_Msk    0xFF0000UL
#define SMIF_RX_DATA_MMIO_FIFO_RD4_DATA3_Pos    24UL
#define SMIF_RX_DATA_MMIO_FIFO_RD4_DATA3_Msk    0xFF000000UL
/* SMIF.RX_DATA_MMIO_FIFO_RD1_SILENT */
#define SMIF_RX_DATA_MMIO_FIFO_RD1_SILENT_DATA0_Pos 0UL
#define SMIF_RX_DATA_MMIO_FIFO_RD1_SILENT_DATA0_Msk 0xFFUL
/* SMIF.SLOW_CA_CTL */
#define SMIF_SLOW_CA_CTL_WAY_Pos                16UL
#define SMIF_SLOW_CA_CTL_WAY_Msk                0x30000UL
#define SMIF_SLOW_CA_CTL_SET_ADDR_Pos           24UL
#define SMIF_SLOW_CA_CTL_SET_ADDR_Msk           0x3000000UL
#define SMIF_SLOW_CA_CTL_PREF_EN_Pos            30UL
#define SMIF_SLOW_CA_CTL_PREF_EN_Msk            0x40000000UL
#define SMIF_SLOW_CA_CTL_ENABLED_Pos            31UL
#define SMIF_SLOW_CA_CTL_ENABLED_Msk            0x80000000UL
/* SMIF.SLOW_CA_CMD */
#define SMIF_SLOW_CA_CMD_INV_Pos                0UL
#define SMIF_SLOW_CA_CMD_INV_Msk                0x1UL
/* SMIF.FAST_CA_CTL */
#define SMIF_FAST_CA_CTL_WAY_Pos                16UL
#define SMIF_FAST_CA_CTL_WAY_Msk                0x30000UL
#define SMIF_FAST_CA_CTL_SET_ADDR_Pos           24UL
#define SMIF_FAST_CA_CTL_SET_ADDR_Msk           0x3000000UL
#define SMIF_FAST_CA_CTL_PREF_EN_Pos            30UL
#define SMIF_FAST_CA_CTL_PREF_EN_Msk            0x40000000UL
#define SMIF_FAST_CA_CTL_ENABLED_Pos            31UL
#define SMIF_FAST_CA_CTL_ENABLED_Msk            0x80000000UL
/* SMIF.FAST_CA_CMD */
#define SMIF_FAST_CA_CMD_INV_Pos                0UL
#define SMIF_FAST_CA_CMD_INV_Msk                0x1UL
/* SMIF.CRC_CMD */
#define SMIF_CRC_CMD_START_Pos                  0UL
#define SMIF_CRC_CMD_START_Msk                  0x1UL
#define SMIF_CRC_CMD_CONTINUE_Pos               1UL
#define SMIF_CRC_CMD_CONTINUE_Msk               0x2UL
/* SMIF.CRC_INPUT0 */
#define SMIF_CRC_INPUT0_INPUT_Pos               0UL
#define SMIF_CRC_INPUT0_INPUT_Msk               0xFFFFFFFFUL
/* SMIF.CRC_INPUT1 */
#define SMIF_CRC_INPUT1_INPUT_Pos               0UL
#define SMIF_CRC_INPUT1_INPUT_Msk               0xFFFFFFFFUL
/* SMIF.CRC_OUTPUT */
#define SMIF_CRC_OUTPUT_CRC_OUTPUT_Pos          0UL
#define SMIF_CRC_OUTPUT_CRC_OUTPUT_Msk          0xFFUL
/* SMIF.INTR */
#define SMIF_INTR_TR_TX_REQ_Pos                 0UL
#define SMIF_INTR_TR_TX_REQ_Msk                 0x1UL
#define SMIF_INTR_TR_RX_REQ_Pos                 1UL
#define SMIF_INTR_TR_RX_REQ_Msk                 0x2UL
#define SMIF_INTR_XIP_ALIGNMENT_ERROR_Pos       2UL
#define SMIF_INTR_XIP_ALIGNMENT_ERROR_Msk       0x4UL
#define SMIF_INTR_TX_CMD_FIFO_OVERFLOW_Pos      3UL
#define SMIF_INTR_TX_CMD_FIFO_OVERFLOW_Msk      0x8UL
#define SMIF_INTR_TX_DATA_FIFO_OVERFLOW_Pos     4UL
#define SMIF_INTR_TX_DATA_FIFO_OVERFLOW_Msk     0x10UL
#define SMIF_INTR_RX_DATA_MMIO_FIFO_UNDERFLOW_Pos 5UL
#define SMIF_INTR_RX_DATA_MMIO_FIFO_UNDERFLOW_Msk 0x20UL
#define SMIF_INTR_DL_FAIL_Pos                   8UL
#define SMIF_INTR_DL_FAIL_Msk                   0x100UL
#define SMIF_INTR_DL_WARNING_Pos                12UL
#define SMIF_INTR_DL_WARNING_Msk                0x1000UL
#define SMIF_INTR_CRC_ERROR_Pos                 16UL
#define SMIF_INTR_CRC_ERROR_Msk                 0x10000UL
#define SMIF_INTR_FS_STATUS_ERROR_Pos           17UL
#define SMIF_INTR_FS_STATUS_ERROR_Msk           0x20000UL
/* SMIF.INTR_SET */
#define SMIF_INTR_SET_TR_TX_REQ_Pos             0UL
#define SMIF_INTR_SET_TR_TX_REQ_Msk             0x1UL
#define SMIF_INTR_SET_TR_RX_REQ_Pos             1UL
#define SMIF_INTR_SET_TR_RX_REQ_Msk             0x2UL
#define SMIF_INTR_SET_XIP_ALIGNMENT_ERROR_Pos   2UL
#define SMIF_INTR_SET_XIP_ALIGNMENT_ERROR_Msk   0x4UL
#define SMIF_INTR_SET_TX_CMD_FIFO_OVERFLOW_Pos  3UL
#define SMIF_INTR_SET_TX_CMD_FIFO_OVERFLOW_Msk  0x8UL
#define SMIF_INTR_SET_TX_DATA_FIFO_OVERFLOW_Pos 4UL
#define SMIF_INTR_SET_TX_DATA_FIFO_OVERFLOW_Msk 0x10UL
#define SMIF_INTR_SET_RX_DATA_MMIO_FIFO_UNDERFLOW_Pos 5UL
#define SMIF_INTR_SET_RX_DATA_MMIO_FIFO_UNDERFLOW_Msk 0x20UL
#define SMIF_INTR_SET_DL_FAIL_Pos               8UL
#define SMIF_INTR_SET_DL_FAIL_Msk               0x100UL
#define SMIF_INTR_SET_DL_WARNING_Pos            12UL
#define SMIF_INTR_SET_DL_WARNING_Msk            0x1000UL
#define SMIF_INTR_SET_CRC_ERROR_Pos             16UL
#define SMIF_INTR_SET_CRC_ERROR_Msk             0x10000UL
#define SMIF_INTR_SET_FS_STATUS_ERROR_Pos       17UL
#define SMIF_INTR_SET_FS_STATUS_ERROR_Msk       0x20000UL
/* SMIF.INTR_MASK */
#define SMIF_INTR_MASK_TR_TX_REQ_Pos            0UL
#define SMIF_INTR_MASK_TR_TX_REQ_Msk            0x1UL
#define SMIF_INTR_MASK_TR_RX_REQ_Pos            1UL
#define SMIF_INTR_MASK_TR_RX_REQ_Msk            0x2UL
#define SMIF_INTR_MASK_XIP_ALIGNMENT_ERROR_Pos  2UL
#define SMIF_INTR_MASK_XIP_ALIGNMENT_ERROR_Msk  0x4UL
#define SMIF_INTR_MASK_TX_CMD_FIFO_OVERFLOW_Pos 3UL
#define SMIF_INTR_MASK_TX_CMD_FIFO_OVERFLOW_Msk 0x8UL
#define SMIF_INTR_MASK_TX_DATA_FIFO_OVERFLOW_Pos 4UL
#define SMIF_INTR_MASK_TX_DATA_FIFO_OVERFLOW_Msk 0x10UL
#define SMIF_INTR_MASK_RX_DATA_MMIO_FIFO_UNDERFLOW_Pos 5UL
#define SMIF_INTR_MASK_RX_DATA_MMIO_FIFO_UNDERFLOW_Msk 0x20UL
#define SMIF_INTR_MASK_DL_FAIL_Pos              8UL
#define SMIF_INTR_MASK_DL_FAIL_Msk              0x100UL
#define SMIF_INTR_MASK_DL_WARNING_Pos           12UL
#define SMIF_INTR_MASK_DL_WARNING_Msk           0x1000UL
#define SMIF_INTR_MASK_CRC_ERROR_Pos            16UL
#define SMIF_INTR_MASK_CRC_ERROR_Msk            0x10000UL
#define SMIF_INTR_MASK_FS_STATUS_ERROR_Pos      17UL
#define SMIF_INTR_MASK_FS_STATUS_ERROR_Msk      0x20000UL
/* SMIF.INTR_MASKED */
#define SMIF_INTR_MASKED_TR_TX_REQ_Pos          0UL
#define SMIF_INTR_MASKED_TR_TX_REQ_Msk          0x1UL
#define SMIF_INTR_MASKED_TR_RX_REQ_Pos          1UL
#define SMIF_INTR_MASKED_TR_RX_REQ_Msk          0x2UL
#define SMIF_INTR_MASKED_XIP_ALIGNMENT_ERROR_Pos 2UL
#define SMIF_INTR_MASKED_XIP_ALIGNMENT_ERROR_Msk 0x4UL
#define SMIF_INTR_MASKED_TX_CMD_FIFO_OVERFLOW_Pos 3UL
#define SMIF_INTR_MASKED_TX_CMD_FIFO_OVERFLOW_Msk 0x8UL
#define SMIF_INTR_MASKED_TX_DATA_FIFO_OVERFLOW_Pos 4UL
#define SMIF_INTR_MASKED_TX_DATA_FIFO_OVERFLOW_Msk 0x10UL
#define SMIF_INTR_MASKED_RX_DATA_MMIO_FIFO_UNDERFLOW_Pos 5UL
#define SMIF_INTR_MASKED_RX_DATA_MMIO_FIFO_UNDERFLOW_Msk 0x20UL
#define SMIF_INTR_MASKED_DL_FAIL_Pos            8UL
#define SMIF_INTR_MASKED_DL_FAIL_Msk            0x100UL
#define SMIF_INTR_MASKED_DL_WARNING_Pos         12UL
#define SMIF_INTR_MASKED_DL_WARNING_Msk         0x1000UL
#define SMIF_INTR_MASKED_CRC_ERROR_Pos          16UL
#define SMIF_INTR_MASKED_CRC_ERROR_Msk          0x10000UL
#define SMIF_INTR_MASKED_FS_STATUS_ERROR_Pos    17UL
#define SMIF_INTR_MASKED_FS_STATUS_ERROR_Msk    0x20000UL
/* SMIF.INTR_CAUSE */
#define SMIF_INTR_CAUSE_NORMAL_Pos              0UL
#define SMIF_INTR_CAUSE_NORMAL_Msk              0x1UL
#define SMIF_INTR_CAUSE_MPC_Pos                 1UL
#define SMIF_INTR_CAUSE_MPC_Msk                 0x2UL


#endif /* _CYIP_SMIF_V3_H_ */


/* [] END OF FILE */
