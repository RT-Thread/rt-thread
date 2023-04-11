/*******************************************************************************
* \file cy_sd_host.c
* \version 2.1
*
* \brief
*  This file provides the driver code to the API for the SD Host Controller
*  driver.
*
********************************************************************************
* \copyright
* Copyright 2018-2021 Cypress Semiconductor Corporation
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

#include "cy_device.h"

#if defined (CY_IP_MXSDHC)

#include "cy_sd_host.h"
#include <string.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.1', 11, \
            'Checked manually, base pointer will not exceed register range.');

/** \cond internal */

/* Timeouts. */
#define CY_SD_HOST_INT_CLK_STABLE_TIMEOUT_MS (150U)  /* The Internal Clock Stable timeout. */
#define CY_SD_HOST_1_8_REG_STABLE_TIME_MS   (30UL)   /* The 1.8 voltage regulator stable time. */
#define CY_SD_HOST_SUPPLY_RAMP_UP_TIME_MS   (35UL)   /* The host supply ramp up time. */
#define CY_SD_HOST_BUS_RAMP_UP_TIME_MS      (1000UL) /* The host bus voltage ramp up time. */

#define CY_SD_HOST_EMMC_CMD6_TIMEOUT_MULT   (10UL)   /* The 10x multiplier of GENERIC_CMD6_TIME[248]. */
#define CY_SD_HOST_RETRY_TIME               (1000UL) /* The number loops to make the timeout in msec. */
#define CY_SD_HOST_VOLTAGE_CHECK_RETRY      (2UL)    /* The number loops for voltage check. */
#define CY_SD_HOST_SDIO_CMD5_TIMEOUT_MS     (1000U)  /* The SDIO CMD5 timeout. */
#define CY_SD_HOST_ACMD41_TIMEOUT_MS        (1000U)  /* The ACMD41 timeout. */
#define CY_SD_HOST_CMD1_TIMEOUT_MS          (1000U)  /* The eMMC device timeout to complete its initialization. */
#define CY_SD_HOST_CMD_TIMEOUT_MS           (3U)     /* The Command complete timeout. */
#define CY_SD_HOST_BUFFER_RDY_TIMEOUT_MS    (150U)   /* The Buffer read ready timeout. */
#define CY_SD_HOST_RD_WR_ENABLE_TIMEOUT     (1U)     /* The valid data in the Host buffer timeout. */
#define CY_SD_HOST_READ_TIMEOUT_MS          (100U)   /* The Read timeout for one block. */
#define CY_SD_HOST_WRITE_TIMEOUT_MS         (250U)   /* The Write timeout for one block. */
#define CY_SD_HOST_MAX_TIMEOUT              (0x0EU)  /* The data max timeout for TOUT_CTRL_R. */
#define CY_SD_HOST_NCC_MIN_CYCLES           (8U)     /* The period (clock cycles) between an end bit
                                                      * of the command and a start bit of the next command.
                                                      */
#define CY_SD_HOST_NCC_MIN_US               ((1000U * CY_SD_HOST_NCC_MIN_CYCLES) / CY_SD_HOST_INIT_CLK_FREQUENCY_KHZ)

/* Commands codes. */
#define CY_SD_HOST_SD_CMD0                  (0UL)
#define CY_SD_HOST_SD_CMD1                  (1UL)
#define CY_SD_HOST_SD_CMD2                  (2UL)
#define CY_SD_HOST_SD_CMD3                  (3UL)
#define CY_SD_HOST_SD_CMD5                  (5UL)
#define CY_SD_HOST_SD_CMD6                  (6UL)
#define CY_SD_HOST_SD_CMD7                  (7UL)
#define CY_SD_HOST_SD_CMD8                  (8UL)
#define CY_SD_HOST_SD_CMD9                  (9UL)
#define CY_SD_HOST_SD_CMD10                 (10UL)
#define CY_SD_HOST_SD_CMD11                 (11UL)
#define CY_SD_HOST_SD_CMD12                 (12UL)
#define CY_SD_HOST_SD_CMD13                 (13UL)

#define CY_SD_HOST_SD_CMD16                 (16UL)
#define CY_SD_HOST_SD_CMD17                 (17UL)
#define CY_SD_HOST_SD_CMD18                 (18UL)

#define CY_SD_HOST_SD_CMD23                 (23UL)
#define CY_SD_HOST_SD_CMD24                 (24UL)
#define CY_SD_HOST_SD_CMD25                 (25UL)

#define CY_SD_HOST_SD_CMD27                 (27UL)
#define CY_SD_HOST_SD_CMD28                 (28UL)
#define CY_SD_HOST_SD_CMD29                 (29UL)
#define CY_SD_HOST_SD_CMD30                 (30UL)

#define CY_SD_HOST_SD_CMD32                 (32UL)
#define CY_SD_HOST_SD_CMD33                 (33UL)
#define CY_SD_HOST_SD_CMD35                 (35UL)
#define CY_SD_HOST_SD_CMD36                 (36UL)
#define CY_SD_HOST_SD_CMD38                 (38UL)

#define CY_SD_HOST_SD_CMD42                 (42UL)
#define CY_SD_HOST_SD_CMD52                 (52UL)

#define CY_SD_HOST_SD_CMD55                 (55UL)

#define CY_SD_HOST_MMC_CMD_TAG              (0x80UL)
#define CY_SD_HOST_MMC_CMD8                 (0x8UL | CY_SD_HOST_MMC_CMD_TAG)

#define CY_SD_HOST_SD_ACMD_OFFSET           (0x40UL)
#define CY_SD_HOST_SD_ACMD6                 (CY_SD_HOST_SD_ACMD_OFFSET + 6UL)
#define CY_SD_HOST_SD_ACMD13                (CY_SD_HOST_SD_ACMD_OFFSET + 13UL)
#define CY_SD_HOST_SD_ACMD41                (CY_SD_HOST_SD_ACMD_OFFSET + 41UL)
#define CY_SD_HOST_SD_ACMD51                (CY_SD_HOST_SD_ACMD_OFFSET + 51UL)

/* CMD5/CMD8/ACMD41 constants. */
#define CY_SD_HOST_CMD5_IO_NUM_MASK         (0x70000000UL) /* The Number of IO functions mask. */
#define CY_SD_HOST_CMD5_MP_MASK             (0x08000000UL) /* The Memory Present mask. */
#define CY_SD_HOST_IO_OCR_MASK              (0x00FFFFFFUL) /* The IO OCR register mask. */
#define CY_SD_HOST_IO_OCR_C                 (0x80000000UL) /* The IO power up status (IORDY). */
#define CY_SD_HOST_MIN_SDXC_SECTORS         (67108864UL) /* Minimum sectors for SDXC: 32 Gbytes / 512. */
#define CY_SD_HOST_MMC_LEGACY_SIZE_BYTES    (0x200000UL)
#define CY_SD_HOST_CMD8_VHS_27_36           (0x100UL) /* CMD8 voltage supplied 2.7-3.6 V. */
#define CY_SD_HOST_CMD8_PATTERN_MASK        (0xFFUL)
#define CY_SD_HOST_CMD8_CHECK_PATTERN       (0xAAUL)
#define CY_SD_HOST_ACMD41_S18R              (1UL << 24U) /* The 1.8 V request. */
#define CY_SD_HOST_ACMD41_HCS               (1UL << 30U) /* SDHC or SDXC supported. */
#define CY_SD_HOST_OCR_S18A                 (1UL << 24U) /* The 1.8 V accepted. */
#define CY_SD_HOST_OCR_35_36_V              (1UL << 23U) /* The 3.5 - 3.6 voltage window. */
#define CY_SD_HOST_OCR_34_35_V              (1UL << 22U) /* The 3.4 - 3.5 voltage window. */
#define CY_SD_HOST_OCR_33_34_V              (1UL << 21U) /* The 3.3 - 3.4 voltage window. */
#define CY_SD_HOST_OCR_32_33_V              (1UL << 20U) /* The 3.2 - 3.3 voltage window. */
#define CY_SD_HOST_OCR_31_32_V              (1UL << 19U) /* The 3.1 - 3.2 voltage window. */
#define CY_SD_HOST_OCR_30_31_V              (1UL << 18U) /* The 3.0 - 3.1 voltage window. */
#define CY_SD_HOST_OCR_29_30_V              (1UL << 17U) /* The 2.9 - 3.0 voltage window. */
#define CY_SD_HOST_OCR_28_29_V              (1UL << 16U) /* The 2.8 - 2.9 voltage window. */
#define CY_SD_HOST_OCR_27_28_V              (1UL << 15U) /* The 2.7 - 2.8 voltage window. */
#define CY_SD_HOST_ACMD41_VOLTAGE_MASK      (CY_SD_HOST_OCR_35_36_V |\
                                             CY_SD_HOST_OCR_34_35_V |\
                                             CY_SD_HOST_OCR_33_34_V |\
                                             CY_SD_HOST_OCR_32_33_V |\
                                             CY_SD_HOST_OCR_31_32_V |\
                                             CY_SD_HOST_OCR_30_31_V |\
                                             CY_SD_HOST_OCR_29_30_V |\
                                             CY_SD_HOST_OCR_28_29_V |\
                                             CY_SD_HOST_OCR_27_28_V)
#define CY_SD_HOST_ARG_ACMD41_BUSY          (0x80000000UL)
#define CY_SD_HOST_OCR_BUSY_BIT             (0x80000000UL) /* The Card power up status bit (busy). */
#define CY_SD_HOST_OCR_CAPACITY_MASK        (0x40000000UL) /* The OCR sector access mode bit. */
#define CY_SD_HOST_ACMD_OFFSET_MASK         (0x3FUL)
#define CY_SD_HOST_EMMC_DUAL_VOLTAGE        (0x00000080UL)
#define CY_SD_HOST_EMMC_VOLTAGE_WINDOW      (CY_SD_HOST_OCR_CAPACITY_MASK |\
                                             CY_SD_HOST_EMMC_DUAL_VOLTAGE |\
                                             CY_SD_HOST_ACMD41_VOLTAGE_MASK)

/* Other constants. */
#define CY_SD_HOST_SWITCH_FUNCTION_BIT      (31U)
#define CY_SD_HOST_DEFAULT_SPEED            (0UL)
#define CY_SD_HOST_HIGH_SPEED               (1UL)
#define CY_SD_HOST_SDR12_SPEED              (0UL)  /* The SDR12/Legacy speed. */
#define CY_SD_HOST_SDR25_SPEED              (1UL)  /* The SDR25/High Speed SDR speed. */
#define CY_SD_HOST_SDR50_SPEED              (2UL)  /* The SDR50 speed. */
#define CY_SD_HOST_DDR50_SPEED              (4UL)  /* The DDR50 speed. */
#define CY_SD_HOST_SDR12_OUT_DELAY          (0UL)
#define CY_SD_HOST_SDR25_OUT_DELAY          (1UL)
#define CY_SD_HOST_DDR50_OUT_DELAY          (3UL)
#define CY_SD_HOST_SDR12_IN_DELAY           (0UL)
#define CY_SD_HOST_SDR25_IN_DELAY           (1UL)
#define CY_SD_HOST_HIGH_SPEED_IN_DELAY      (2UL)
#define CY_SD_HOST_DDR50_IN_DELAY           (3UL)
#define CY_SD_HOST_EMMC_BUS_WIDTH_ADDR      (0xB7UL)
#define CY_SD_HOST_EMMC_HS_TIMING_ADDR      (0xB9UL)
#define CY_SD_HOST_CMD23_BLOCKS_NUM_MASK    (0xFFFFUL)
#define CY_SD_HOST_CMD23_RELIABLE_WRITE_POS (31U)
#define CY_SD_HOST_RCA_SHIFT                (16U)
#define CY_SD_HOST_RESPONSE_SIZE            (4U)
#define CY_SD_HOST_CID_SIZE                 (4U)
#define CY_SD_HOST_CSD_SIZE                 (4U)
#define CY_SD_HOST_SCR_BLOCKS               (8UL)
#define CY_SD_HOST_CSD_BLOCKS               (16UL)
#define CY_SD_HOST_SD_STATUS_BLOCKS         (64UL)
#define CY_SD_HOST_SWITCH_STATUS_LEN        (16UL)
#define CY_SD_HOST_PERI_FREQUENCY           (100000000UL)
#define CY_SD_HOST_FREQ_SEL_MSK             (0xFFUL)
#define CY_SD_HOST_UPPER_FREQ_SEL_POS       (8U)

/* CMD6 SWITCH command bitfields. */
#define CY_SD_HOST_EMMC_CMD6_ACCESS_OFFSET  (24U)
#define CY_SD_HOST_EMMC_CMD6_IDX_OFFSET     (16U)
#define CY_SD_HOST_EMMC_CMD6_VALUE_OFFSET   (8U)
#define CY_SD_HOST_EMMC_CMD6_CMD_SET_OFFSET (0U)

/* EMMC EXTCSD register bitfields. */
#define CY_SD_HOST_EXTCSD_SEC_COUNT         (53U)
#define CY_SD_HOST_EXTCSD_GENERIC_CMD6_TIME (62U)
#define CY_SD_HOST_EXTCSD_GENERIC_CMD6_TIME_MSK (0xFFUL)
#define CY_SD_HOST_EXTCSD_SIZE              (128U)

/* CSD register masks/positions. */
#define CY_SD_HOST_CSD_V1_C_SIZE_MSB_MASK   (0x00000003UL)
#define CY_SD_HOST_CSD_V1_C_SIZE_ISB_MASK   (0xFF000000UL)
#define CY_SD_HOST_CSD_V1_C_SIZE_LSB_MASK   (0x00C00000UL)
#define CY_SD_HOST_CSD_V1_C_SIZE_MSB_POS    (0U)
#define CY_SD_HOST_CSD_V1_C_SIZE_ISB_POS    (24U)
#define CY_SD_HOST_CSD_V1_C_SIZE_LSB_POS    (22U)
#define CY_SD_HOST_CSD_V1_C_SIZE_MSB_MULT   (10U)
#define CY_SD_HOST_CSD_V1_C_SIZE_ISB_MULT   (2U)
#define CY_SD_HOST_CSD_V1_C_SIZE_MULT_MASK  (0x00000380UL)
#define CY_SD_HOST_CSD_V1_C_SIZE_MULT_POS   (7U)
#define CY_SD_HOST_CSD_V1_READ_BL_LEN_MASK  (0x00000F00UL)
#define CY_SD_HOST_CSD_V1_READ_BL_LEN_POS   (8U)
#define CY_SD_HOST_CSD_V1_BL_LEN_512        (9UL)
#define CY_SD_HOST_CSD_V1_BL_LEN_1024       (10UL)
#define CY_SD_HOST_CSD_V1_BL_LEN_2048       (11UL)
#define CY_SD_HOST_CSD_V1_1024_SECT_FACTOR  (2UL)
#define CY_SD_HOST_CSD_V1_2048_SECT_FACTOR  (4UL)
#define CY_SD_HOST_CSD_V2_C_SIZE_POS        (8U)
#define CY_SD_HOST_CSD_V2_SECTOR_MULT       (10U)
#define CY_SD_HOST_CSD_TEMP_WRITE_PROTECT   (20U)
#define CY_SD_HOST_CSD_PERM_WRITE_PROTECT   (21U)
#define CY_SD_HOST_CSD_LSB_MASK             (0x000000FFUL)
#define CY_SD_HOST_CSD_ISBR_MASK            (0x0000FF00UL)
#define CY_SD_HOST_CSD_ISBL_MASK            (0x00FF0000UL)
#define CY_SD_HOST_CSD_MSB_MASK             (0xFF000000UL)
#define CY_SD_HOST_CSD_ISB_SHIFT            (16U)

/* CMD6 EXT_CSD access mode. */
#define CY_SD_HOST_EMMC_ACCESS_COMMAND_SET  (0x0U)
#define CY_SD_HOST_EMMC_ACCESS_SET_BITS     (0x1U)
#define CY_SD_HOST_EMMC_ACCESS_CLEAR_BITS   (0x2U)
#define CY_SD_HOST_EMMC_ACCESS_WRITE_BYTE   (0x3UL)

/* CCCR register values. */
#define CY_SD_HOST_CCCR_SPEED_CONTROL       (0x00013UL)
#define CY_SD_HOST_CCCR_IO_ABORT            (0x00006UL)
#define CY_SD_HOST_CCCR_SPEED_SHS_MASK      (0x1UL)
#define CY_SD_HOST_CCCR_SPEED_EHS_MASK      (0x2UL)
#define CY_SD_HOST_CCCR_SPEED_BSS0_MASK     (0x2UL)
#define CY_SD_HOST_CCCR_SPEED_BSS1_MASK     (0x4UL)
#define CY_SD_HOST_CCCR_SPEED_BSS2_MASK     (0x8UL)
#define CY_SD_HOST_CCCR_BUS_INTERFACE_CTR   (0x00007UL)
#define CY_SD_HOST_CCCR_BUS_WIDTH_0         (0x1UL)
#define CY_SD_HOST_CCCR_BUS_WIDTH_1         (0x2UL)
#define CY_SD_HOST_CCCR_S8B                 (0x4UL)

/* SDMA constants. */
#define CY_SD_HOST_SDMA_BUF_BYTES_4K        (0x0U) /* 4K bytes SDMA Buffer Boundary. */
#define CY_SD_HOST_SDMA_BUF_BYTES_8K        (0x1U) /* 8K bytes SDMA Buffer Boundary. */
#define CY_SD_HOST_SDMA_BUF_BYTES_16K       (0x2U) /* 16K bytes SDMA Buffer Boundary. */
#define CY_SD_HOST_SDMA_BUF_BYTES_32K       (0x3U) /* 32K bytes SDMA Buffer Boundary. */
#define CY_SD_HOST_SDMA_BUF_BYTES_64K       (0x4U) /* 64K bytes SDMA Buffer Boundary. */
#define CY_SD_HOST_SDMA_BUF_BYTES_128K      (0x5U) /* 128K bytes SDMA Buffer Boundary. */
#define CY_SD_HOST_SDMA_BUF_BYTES_256K      (0x6U) /* 256K bytes SDMA Buffer Boundary. */
#define CY_SD_HOST_SDMA_BUF_BYTES_512K      (0x7U) /* 512K bytes SDMA Buffer Boundary. */

/* CMD38 arguments. */
#define CY_SD_HOST_ERASE                    (0x00000000UL)  /* The SD/eMMC Erase. */
#define CY_SD_HOST_SD_DISCARD               (0x00000001UL)  /* The SD Discard. */
#define CY_SD_HOST_SD_FULE                  (0x00000002UL)  /* The SD FULE. */
#define CY_SD_HOST_EMMC_DISCARD             (0x00000003UL)  /* The eMMC Discard. */
#define CY_SD_HOST_EMMC_SECURE_ERASE        (0x80000000UL)  /* The eMMC Secure Erase. */
#define CY_SD_HOST_EMMC_SECURE_TRIM_STEP_2  (0x80008000UL)  /* The eMMC Secure Trim Step 2. */
#define CY_SD_HOST_EMMC_SECURE_TRIM_STEP_1  (0x80000001UL)  /* The eMMC Secure Trim Step 1. */
#define CY_SD_HOST_EMMC_TRIM                (0x00000001UL)  /* The eMMC Trim. */

/* CMD52 constants. */
#define CY_SD_HOST_CMD52_RWFLAG_POS         (31U)          /* The CMD52 RW Flag position. */
#define CY_SD_HOST_CMD52_FUNCT_NUM_POS      (28U)          /* The CMD52 Function Number position. */
#define CY_SD_HOST_CMD52_FUNCT_NUM_MSK      (0x07UL)       /* The CMD52 Function Number mask. */
#define CY_SD_HOST_CMD52_RAWFLAG_POS        (27U)          /* The CMD52 Raw Flag position. */
#define CY_SD_HOST_CMD52_REG_ADDR_POS       (9U)           /* The CMD52 Register Address position. */
#define CY_SD_HOST_CMD52_REG_ADDR_MSK       (0x1FFFFUL)    /* The CMD52 Register Address mask. */
#define CY_SD_HOST_CMD52_DATA_MSK           (0xFFUL)       /* The CMD52 data mask. */

/* Interrupt masks. */
#define CY_SD_HOST_NORMAL_INT_MSK           (0x1FFFU)  /* The enabled Normal Interrupts. */
#define CY_SD_HOST_ERROR_INT_MSK            (0x07FFU)  /* The enabled Error Interrupts. */

/* SD output clock. */
#define CY_SD_HOST_CLK_400K                 (400UL * 1000UL)    /* 400 kHz. */
#define CY_SD_HOST_CLK_10M                  (10UL * 1000UL * 1000UL) /* 10 MHz. */
#define CY_SD_HOST_CLK_20M                  (20UL * 1000UL * 1000UL) /* 20 MHz. */

/** \endcond */

/** \cond PARAM_CHECK_MACROS */

#define CY_SD_HOST_FREQ_MAX                 (50000000UL)  /* The maximum clk frequency. */
#define CY_SD_HOST_IS_FREQ_VALID(frequency) ((0UL < (frequency)) && (CY_SD_HOST_FREQ_MAX >= (frequency)))

#define CY_SD_HOST_IS_SD_BUS_WIDTH_VALID(width)         ((CY_SD_HOST_BUS_WIDTH_1_BIT == (width)) || \
                                                         (CY_SD_HOST_BUS_WIDTH_4_BIT == (width)))

#define CY_SD_HOST_IS_EMMC_BUS_WIDTH_VALID(width)       ((CY_SD_HOST_BUS_WIDTH_1_BIT == (width)) || \
                                                         (CY_SD_HOST_BUS_WIDTH_4_BIT == (width)) || \
                                                         (CY_SD_HOST_BUS_WIDTH_8_BIT == (width)))

#define CY_SD_HOST_IS_BUS_WIDTH_VALID(width, cardType)  ((CY_SD_HOST_EMMC == (cardType)) ? \
                                                         CY_SD_HOST_IS_EMMC_BUS_WIDTH_VALID(width) : \
                                                         CY_SD_HOST_IS_SD_BUS_WIDTH_VALID(width))

#define CY_SD_HOST_IS_AUTO_CMD_VALID(cmd)               ((CY_SD_HOST_AUTO_CMD_NONE == (cmd)) || \
                                                         (CY_SD_HOST_AUTO_CMD_12 == (cmd)) || \
                                                         (CY_SD_HOST_AUTO_CMD_23 == (cmd)) || \
                                                         (CY_SD_HOST_AUTO_CMD_AUTO == (cmd)))

#define CY_SD_HOST_IS_TIMEOUT_VALID(timeout)            (CY_SD_HOST_MAX_TIMEOUT >= (timeout))

#define CY_SD_HOST_BLK_SIZE_MAX                         (2048UL)  /* The maximum block size. */
/* Macro to check that block size is less than 2048 bytes and block size is even if DDR50 mode is selected */
#define CY_SD_HOST_IS_BLK_SIZE_VALID(size, speedMode)   ((CY_SD_HOST_BLK_SIZE_MAX >= (size)) ? \
                                                         (((speedMode) == 0x4UL) ? (((size) % 2UL) == 0UL) : true) : false)

#define CY_SD_HOST_IS_ERASE_VALID(eraseType)            ((CY_SD_HOST_ERASE_ERASE == (eraseType)) || \
                                                         (CY_SD_HOST_ERASE_DISCARD == (eraseType)) || \
                                                         (CY_SD_HOST_ERASE_FULE == (eraseType)) || \
                                                         (CY_SD_HOST_ERASE_SECURE == (eraseType)) || \
                                                         (CY_SD_HOST_ERASE_SECURE_TRIM_STEP_2 == (eraseType)) || \
                                                         (CY_SD_HOST_ERASE_SECURE_TRIM_STEP_1 == (eraseType)) || \
                                                         (CY_SD_HOST_ERASE_TRIM == (eraseType)))

#define CY_SD_HOST_IS_CMD_IDX_VALID(cmd)                (0UL == ((cmd) & (uint32_t)~(CY_SD_HOST_ACMD_OFFSET_MASK | \
                                                                                     CY_SD_HOST_MMC_CMD_TAG | \
                                                                                     CY_SD_HOST_SD_ACMD_OFFSET)))

#define CY_SD_HOST_IS_DMA_VALID(dmaType)                ((CY_SD_HOST_DMA_SDMA == (dmaType)) || \
                                                         (CY_SD_HOST_DMA_ADMA2 == (dmaType)) || \
                                                         (CY_SD_HOST_DMA_ADMA2_ADMA3 == (dmaType)))

#define CY_SD_HOST_IS_SPEED_MODE_VALID(speedMode)       ((CY_SD_HOST_BUS_SPEED_DEFAULT == (speedMode)) || \
                                                         (CY_SD_HOST_BUS_SPEED_HIGHSPEED == (speedMode)) || \
                                                         (CY_SD_HOST_BUS_SPEED_SDR12_5 == (speedMode)) || \
                                                         (CY_SD_HOST_BUS_SPEED_SDR25 == (speedMode)) || \
                                                         (CY_SD_HOST_BUS_SPEED_SDR50 == (speedMode)) || \
                                                         (CY_SD_HOST_BUS_SPEED_DDR50 == (speedMode)) || \
                                                         (CY_SD_HOST_BUS_SPEED_EMMC_LEGACY == (speedMode)) || \
                                                         (CY_SD_HOST_BUS_SPEED_EMMC_HIGHSPEED_SDR == (speedMode)))

#define CY_SD_HOST_IS_DMA_WR_RD_VALID(dmaType)          ((CY_SD_HOST_DMA_SDMA == (dmaType)) || \
                                                         (CY_SD_HOST_DMA_ADMA2 == (dmaType)))

#define CY_SD_HOST_IS_CMD_TYPE_VALID(cmdType)            ((CY_SD_HOST_CMD_NORMAL == (cmdType)) || \
                                                         (CY_SD_HOST_CMD_SUSPEND == (cmdType)) || \
                                                         (CY_SD_HOST_CMD_RESUME == (cmdType)) || \
                                                         (CY_SD_HOST_CMD_ABORT == (cmdType)))

#define CY_SD_HOST_IS_RELIABLE_WRITE(cardType, rw)      ((CY_SD_HOST_EMMC != (cardType)) && \
                                                          (false == (rw)))

/** \endcond */

__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_eMMC_InitCard(SDHC_Type *base,
                                             cy_stc_sd_host_sd_card_config_t const *config,
                                             cy_stc_sd_host_context_t *context);
static cy_en_sd_host_status_t Cy_SD_Host_CmdRxData(SDHC_Type *base, cy_stc_sd_host_data_config_t *pcmd);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_CmdTxData(SDHC_Type *base, cy_stc_sd_host_data_config_t *pcmd);
static cy_en_sd_host_status_t Cy_SD_Host_OpsGoIdle(SDHC_Type *base);
static cy_en_sd_host_status_t Cy_SD_Host_OpsVoltageSwitch(SDHC_Type *base,
                                                          cy_stc_sd_host_context_t const *context);
static cy_en_sd_host_status_t Cy_SD_Host_OpsSwitchFunc(SDHC_Type *base,
                                                       uint32_t cmdArgument);
static cy_en_sd_host_status_t Cy_SD_Host_SdCardSwitchFunc(SDHC_Type *base, uint32_t cmdArgument,
                                                                     cy_en_sd_host_card_type_t cardType);
static cy_en_sd_host_bus_speed_mode_t Cy_SD_Host_FindBusSpeedMode(SDHC_Type *base, bool lowVoltageSignaling,
                                                            cy_en_sd_host_card_type_t cardType);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_OpsSetBlockCount(SDHC_Type *base,
                                                                   bool reliableWrite,
                                                                   uint32_t blockNum);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_OpsProgramCsd(SDHC_Type *base,
                                                                uint32_t csd,
                                                                cy_stc_sd_host_context_t *context);
static cy_en_sd_host_status_t Cy_SD_Host_OpsSelectCard(SDHC_Type *base,
                                                      cy_stc_sd_host_context_t const *context);
static cy_en_sd_host_status_t Cy_SD_Host_OpsSendIoRwDirectCmd(SDHC_Type *base,
                                                            uint32_t rwFlag,
                                                            uint32_t functionNumber,
                                                            uint32_t rawFlag,
                                                            uint32_t registerAddress,
                                                            uint32_t data);
static cy_en_sd_host_status_t Cy_SD_Host_OpsSendAppCmd(SDHC_Type *base,
                                                       cy_stc_sd_host_context_t const *context);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_OpsSendIfCond(SDHC_Type *base,
                                                       uint32_t cmdArgument,
                                                       bool noResponse);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_OpsSetSdBusWidth(SDHC_Type *base,
                                                        uint32_t cmdArgument,
                                                        cy_stc_sd_host_context_t const *context);
static cy_en_sd_host_status_t Cy_SD_Host_OpsSdioSendOpCond(SDHC_Type *base,
                                                           uint32_t *ocrReg,
                                                           uint32_t cmdArgument);
static cy_en_sd_host_status_t Cy_SD_Host_OpsSdSendOpCond(SDHC_Type *base,
                                                        uint32_t *ocrReg,
                                                        uint32_t cmdArgument,
                                                        cy_stc_sd_host_context_t const *context);
static cy_en_sd_host_status_t Cy_SD_Host_MmcOpsSendOpCond(SDHC_Type *base,
                                                        uint32_t *ocrReg,
                                                        uint32_t cmdArgument);
static cy_en_sd_host_status_t Cy_SD_Host_SdCardChangeClock(SDHC_Type *base, uint32_t frequency);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollBufferReadReady(SDHC_Type *base);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollBufferWriteReady(SDHC_Type *base);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollCmdComplete(SDHC_Type *base);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollTransferComplete(SDHC_Type *base);
static void Cy_SD_Host_ErrorReset(SDHC_Type *base);
static void Cy_SD_Host_NormalReset(SDHC_Type *base);
__STATIC_INLINE bool Cy_SD_Host_VoltageCheck(SDHC_Type *base);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_IoOcr(SDHC_Type *base,
                                      bool lowVoltageSignaling,
                                      uint32_t *s18aFlag,
                                      uint32_t *sdioFlag,
                                      bool *mpFlag,
                                      uint32_t *ocrReg);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_SdOcr(SDHC_Type *base,
                                      bool lowVoltageSignaling,
                                      uint32_t *s18aFlag,
                                      bool *mpFlag,
                                      bool f8Flag,
                                      uint32_t *ocrReg,
                                      cy_stc_sd_host_context_t *context);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollCmdLineFree(SDHC_Type const *base);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollDataLineNotInhibit(SDHC_Type const *base);
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollDataLineFree(SDHC_Type const *base);

/* High-level section */

/*******************************************************************************
* Function Name: Cy_SD_Host_eMMC_InitCard
****************************************************************************//**
*
*  Initializes the eMMC card.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *config
*     The pointer to the SD card configuration structure.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_eMMC_InitCard(SDHC_Type *base,
                                                       cy_stc_sd_host_sd_card_config_t const *config,
                                                       cy_stc_sd_host_context_t *context)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_SUCCESS;
    cy_en_sd_host_bus_speed_mode_t speedMode = CY_SD_HOST_BUS_SPEED_EMMC_LEGACY;
    uint32_t retry;
    uint32_t ocrReg; /* The Operation Condition register. */
    uint32_t cidReg[CY_SD_HOST_CID_SIZE];  /* The Device Identification register. */
    uint32_t extCsd[CY_SD_HOST_EXTCSD_SIZE] = { 0UL };
    uint32_t genericCmd6Time;
    uint32_t csdReg[CY_SD_HOST_CSD_SIZE]; /* The Card-Specific Data register. */

    /* Reset Card (CMD0). */
    ret = Cy_SD_Host_OpsGoIdle(base); /* The Idle state. */

    /* Software reset for the CMD line */
    Cy_SD_Host_SoftwareReset(base, CY_SD_HOST_RESET_DATALINE);
    Cy_SD_Host_SoftwareReset(base, CY_SD_HOST_RESET_CMD_LINE);

    retry = CY_SD_HOST_RETRY_TIME;
    while (retry > 0UL)
    {
        /* Get OCR (CMD1). */
        ret = Cy_SD_Host_MmcOpsSendOpCond(base, &ocrReg, CY_SD_HOST_EMMC_VOLTAGE_WINDOW);

        context->cardCapacity = CY_SD_HOST_EMMC_LESS_2G;

        /* Check if the eMMC capacity is greater than 2GB */
        if (CY_SD_HOST_OCR_CAPACITY_MASK == (ocrReg & CY_SD_HOST_OCR_CAPACITY_MASK))
        {
            context->cardCapacity = CY_SD_HOST_EMMC_GREATER_2G;
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            break;
        }
        else
        {
            Cy_SD_Host_ErrorReset(base);

            Cy_SysLib_DelayUs(CY_SD_HOST_CMD1_TIMEOUT_MS); /* The CMD1 timeout. */
        }
        retry--;
    }

    /* The low voltage operation check. */
    if ((true == config->lowVoltageSignaling) &&
        (CY_SD_HOST_EMMC_DUAL_VOLTAGE == (ocrReg & CY_SD_HOST_EMMC_DUAL_VOLTAGE)))
    {
        /* Power down the MMC bus */
        Cy_SD_Host_DisableCardVoltage(base);

        Cy_SysLib_Delay(CY_SD_HOST_1_8_REG_STABLE_TIME_MS);

        /* Switch the bus to 1.8 V */
        Cy_SD_Host_ChangeIoVoltage(base, CY_SD_HOST_IO_VOLT_1_8V);

        Cy_SD_Host_EnableCardVoltage(base);
        (void)Cy_SD_Host_SdCardChangeClock(base, CY_SD_HOST_CLK_400K);

        /* Wait 10 ms */
        Cy_SysLib_Delay(CY_SD_HOST_1_8_REG_STABLE_TIME_MS);

        retry = CY_SD_HOST_RETRY_TIME;
        while (retry > 0UL)
        {
            /* Get OCR (CMD1). */
            ret = Cy_SD_Host_MmcOpsSendOpCond(base, &ocrReg, CY_SD_HOST_EMMC_VOLTAGE_WINDOW);

            Cy_SD_Host_ErrorReset(base);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                break;
            }

            Cy_SysLib_DelayUs(CY_SD_HOST_CMD1_TIMEOUT_MS); /* The CMD1 timeout. */
            retry--;
        }
    }

    if (CY_SD_HOST_SUCCESS == ret) /* The ready state. */
    {
        /* Get CID (CMD2). */
        ret = Cy_SD_Host_GetCid(base, cidReg);

        Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

        if (CY_SD_HOST_SUCCESS == ret) /* The Identification state. */
        {
            /* Get RCA (CMD3) */
            context->RCA = Cy_SD_Host_GetRca(base);

            /* The stand-by state. */

            /* Get CSD (CMD9)  */
            ret = Cy_SD_Host_GetCsd(base, csdReg, context);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Select the card (CMD7). */
                ret = Cy_SD_Host_OpsSelectCard(base, context);

                if (CY_SD_HOST_SUCCESS == ret) /* The transfer state. */
                {
                    /* Get Ext CSD (CMD8).
                    * Capacity Type and Max Sector Num are in the context.
                    */
                    ret = Cy_SD_Host_GetExtCsd(base, extCsd, context);

                    /* Get GENERIC_CMD6_TIME [248] of the EXTCSD register */
                    genericCmd6Time = CY_SD_HOST_EMMC_CMD6_TIMEOUT_MULT *
                                      (extCsd[CY_SD_HOST_EXTCSD_GENERIC_CMD6_TIME] &
                                       CY_SD_HOST_EXTCSD_GENERIC_CMD6_TIME_MSK);

                    if ((CY_SD_HOST_SUCCESS == ret) &&
                        (CY_SD_HOST_BUS_WIDTH_1_BIT != config->busWidth))
                    {
                            /* Set Bus Width (CMD6) */
                            ret = Cy_SD_Host_SetBusWidth(base,
                                                         config->busWidth,
                                                         context);

                            Cy_SysLib_Delay(genericCmd6Time); /* The CMD6 timeout. */
                    }

                    if (CY_SD_HOST_SUCCESS == ret)
                    {
                        /* Set Bus Speed Mode (CMD6). */
                        ret = Cy_SD_Host_SetBusSpeedMode(base,
                                                         speedMode,
                                                         context);
                        if (CY_SD_HOST_SUCCESS == ret)
                        {
                            (void)Cy_SD_Host_SdCardChangeClock(base, CY_SD_HOST_CLK_25M);
                        }
                        Cy_SysLib_Delay(CY_SD_HOST_CLK_RAMP_UP_TIME_MS);
                    }
                }
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_InitCard
****************************************************************************//**
*
*  Initializes a card if it is connected.
*  After this function is called, the card is in the transfer state.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *config
*     The pointer to the SD card configuration structure.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
* \note When lowVoltageSignaling is True, this function negotiates with
* the card to change the bus signaling level to 1.8V.
* The dedicated io_volt_sel pin is used to change the regulator supplying voltage
* to the VDDIO of the SD block in order to operate at 1.8V. To configure
* the custom IO pin in order to control (using the GPIO driver) the regulator
* supplying voltage, the user must implement weak Cy_SD_Host_ChangeIoVoltage().
* Also, this function must set the SIGNALING_EN bit of the SDHC_CORE_HOST_CTRL2_R
* register when ioVoltage = CY_SD_HOST_IO_VOLT_1_8V.
*
* \note lowVoltageSignaling is not supported for CAT1C devices.
*
* \note After calling this function, the SD Host is configured in
* highest supported bus speed mode (for the SD card, irrespective of
* the value of lowVoltageSignaling), or eMMC legacy (for the eMMC card)
* with SD clock = 25 MHz. The Power Limit and Driver Strength functions of
* the CMD6 command are set into the default state (0.72 W and Type B).
* It is the user's responsibility to set Power Limit and Driver Strength
* depending on the capacitance load of the host system.
* To change Speed mode, the user must call the Cy_SD_Host_SetBusSpeedMode()
* and Cy_SD_Host_SdCardChangeClock() functions.
* Additionally, SD SDR25, SD SDR50, eMMC High Speed SDR modes require
* settings CLOCK_OUT_DLY and CLOCK_IN_DLY bit-fields of the GP_OUT_R register.
* For more information about Speed modes, refer to Part 1 Physical Layer
* SD Specification.
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_InitCard(SDHC_Type *base,
                                           cy_stc_sd_host_sd_card_config_t *config,
                                           cy_stc_sd_host_context_t *context)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    cy_en_sd_host_bus_speed_mode_t speedMode = CY_SD_HOST_BUS_SPEED_DEFAULT;
    uint32_t ocrReg; /* The Operation Condition register. */
    uint32_t cidReg[CY_SD_HOST_CID_SIZE]; /* The Device Identification register. */
    uint32_t csdReg[CY_SD_HOST_CSD_SIZE]; /* The Card-Specific Data register. */
    uint32_t sdioFlag = 0UL; /* The IO flag. */
    uint32_t s18aFlag = 0UL; /* The S18A flag. */
    bool f8Flag = false; /* The CMD8 flag. */
    bool mpFlag = false; /* The MEM flag. */

    if ((NULL != base) && (NULL != context) && (NULL != config))
    {
        CY_ASSERT_L3(CY_SD_HOST_IS_BUS_WIDTH_VALID(config->busWidth, context->cardType));

        /* Wait until the card is stable and check if it is connected. */
        if ((true == Cy_SD_Host_IsCardConnected(base)) ||
            (CY_SD_HOST_EMMC == context->cardType))
        {
            Cy_SD_Host_EnableCardVoltage(base);

            Cy_SD_Host_ChangeIoVoltage(base, CY_SD_HOST_IO_VOLT_3_3V);

            /* Set the host bus width to 1 bit. */
            (void)Cy_SD_Host_SetHostBusWidth(base, CY_SD_HOST_BUS_WIDTH_1_BIT);

            /* Change the host SD clock to 400 kHz. */
            (void)Cy_SD_Host_SdCardChangeClock(base, CY_SD_HOST_CLK_400K);

            /* Wait until the voltage and clock are stable. */
            Cy_SysLib_Delay(CY_SD_HOST_BUS_RAMP_UP_TIME_MS);

            context->RCA = 0UL;

            if (CY_SD_HOST_EMMC != context->cardType)
            {
                /* Send CMD0 and CMD8 commands. */
                f8Flag = Cy_SD_Host_VoltageCheck(base);

                /* Set SDHC can be supported. */
                if (f8Flag)
                {
                    context->cardCapacity = CY_SD_HOST_SDHC;
                }

                /* Clear the insert event */
                Cy_SD_Host_NormalReset(base);
                Cy_SysLib_Delay(1);

                /* Send CMD5 to get IO OCR */
                ret = Cy_SD_Host_IoOcr(base,
                                       config->lowVoltageSignaling,
                                       &s18aFlag,
                                       &sdioFlag,
                                       &mpFlag,
                                       &ocrReg);

                /* Check if CMD5 has no response or MP = 1.
                *  This means we have a SD memory card or Combo card.
                */
                if (mpFlag || (0UL == sdioFlag))
                {
                    /* Send ACMD41 */
                    ret = Cy_SD_Host_SdOcr(base,
                                           config->lowVoltageSignaling,
                                           &s18aFlag,
                                           &mpFlag,
                                           f8Flag,
                                           &ocrReg,
                                           context);
                }

                /* Set the card type */
                if (CY_SD_HOST_ERROR_UNUSABLE_CARD != ret) /* The Ready state. */
                {
                    if (true == mpFlag)
                    {
                        if (0UL != sdioFlag)
                        {
                            context->cardType = CY_SD_HOST_COMBO;
                        }
                        else
                        {
                            context->cardType = CY_SD_HOST_SD;
                        }
                    }
                    else if (0UL != sdioFlag)
                    {
                        context->cardType = CY_SD_HOST_SDIO;
                    }
                    else
                    {
                        /* The unusable card */
                        ret = CY_SD_HOST_ERROR_UNUSABLE_CARD;

                        context->cardType = CY_SD_HOST_UNUSABLE;
                    }

                    if (CY_SD_HOST_ERROR_UNUSABLE_CARD != ret)
                    {
                        if ((1UL == s18aFlag) && (config->lowVoltageSignaling))
                        {
                            /* Voltage switch (CMD11). */
                            ret =  Cy_SD_Host_OpsVoltageSwitch(base, context);

                            if (CY_SD_HOST_SUCCESS != ret)  /* Initialize again at 3.3 V. */
                            {
                                Cy_SD_Host_ChangeIoVoltage(base, CY_SD_HOST_IO_VOLT_3_3V);

                                /* Wait until the voltage and clock are stable. */
                                Cy_SysLib_Delay(CY_SD_HOST_BUS_RAMP_UP_TIME_MS);

                                /* Send CMD0 and CMD8 commands. */
                                f8Flag = Cy_SD_Host_VoltageCheck(base);

                                if (0UL < sdioFlag)
                                {
                                    /* Send CMD5 to get IO OCR. */
                                    ret = Cy_SD_Host_IoOcr(base,
                                                           config->lowVoltageSignaling,
                                                           &s18aFlag,
                                                           &sdioFlag,
                                                           &mpFlag,
                                                           &ocrReg);
                                }

                                if (mpFlag)
                                {
                                    /* Send ACMD41 */
                                    ret = Cy_SD_Host_SdOcr(base,
                                                           config->lowVoltageSignaling,
                                                           &s18aFlag,
                                                           &mpFlag,
                                                           f8Flag,
                                                           &ocrReg,
                                                           context);
                                }

                                s18aFlag = 0UL;
                            }
                        }

                        if (CY_SD_HOST_SDIO != context->cardType)
                        {
                            /* Get CID (CMD2).  */
                            ret = Cy_SD_Host_GetCid(base, cidReg);

                            Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);
                        }                                       /* The Identification state. */

                        /* Get RCA (CMD3). */
                        context->RCA = Cy_SD_Host_GetRca(base);

                        Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

                        if (CY_SD_HOST_SDIO != context->cardType) /* The stand-by state. */
                        {
                            /* Get CSD (CMD9) to save
                             * Max Sector Number in the context.
                             */
                            ret = Cy_SD_Host_GetCsd(base, csdReg, context);

                            if (CY_SD_HOST_MIN_SDXC_SECTORS <= context->maxSectorNum)
                            {
                               context->cardCapacity = CY_SD_HOST_SDXC;
                            }

                            Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);
                        }

                        if (CY_SD_HOST_SUCCESS == ret) /* The Standby state. */
                        {
                            /* Select the card (CMD7). */
                            ret = Cy_SD_Host_OpsSelectCard(base, context);
                        }

                        if ((CY_SD_HOST_SUCCESS == ret) &&
                            (CY_SD_HOST_SDIO != context->cardType)) /* The Transition state. */
                        {
                            /* Set Bus Width (ACMD6). */
                            if (CY_SD_HOST_BUS_WIDTH_1_BIT != config->busWidth)
                            {
                                ret = Cy_SD_Host_SetBusWidth(base,
                                                             CY_SD_HOST_BUS_WIDTH_4_BIT,
                                                             context);
                                Cy_SysLib_Delay(CY_SD_HOST_READ_TIMEOUT_MS);
                            }

                            if (CY_SD_HOST_SUCCESS == ret)
                            {
                                /* Find Highest Supported Bus Speed Mode (CMD6). */
                                speedMode = Cy_SD_Host_FindBusSpeedMode(base, ((bool)s18aFlag && config->lowVoltageSignaling), context->cardType);
                                Cy_SysLib_Delay(CY_SD_HOST_READ_TIMEOUT_MS);


                                /* Set Bus Speed Mode (CMD6). */
                                ret = Cy_SD_Host_SetBusSpeedMode(base,
                                                                 speedMode,
                                                                 context);
                                Cy_SysLib_Delay(CY_SD_HOST_READ_TIMEOUT_MS);

                                if (CY_SD_HOST_SUCCESS == ret)
                                {
                                    (void)Cy_SD_Host_SdCardChangeClock(base,
                                                                       CY_SD_HOST_CLK_25M);
                                }
                                Cy_SysLib_Delay(CY_SD_HOST_CLK_RAMP_UP_TIME_MS);
                            }
                        }
                    }
                }
            }
            else
            {
                ret = Cy_SD_Host_eMMC_InitCard(base, config, context);
            }

            *config->rca = context->RCA;
            *config->cardType = context->cardType;
            *config->cardCapacity = context->cardCapacity;
        }
        else
        {
            /* The SD card is disconnected or an embedded card. */
            ret = CY_SD_HOST_ERROR_DISCONNECTED;
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_Read
****************************************************************************//**
*
*  Reads single- or multiple-block data from the SD card / eMMC. If DMA is not used
*  this function blocks until all data is read.
*  If DMA is used all data is read when the Transfer complete event is set.
*  It is the user responsibility to check and reset the transfer complete event
*  (using \ref Cy_SD_Host_GetNormalInterruptStatus and
*  \ref Cy_SD_Host_ClearNormalInterruptStatus functions).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *config
*     The pointer to the SD card read-write structure.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_Read(SDHC_Type *base,
                                       cy_stc_sd_host_write_read_config_t *config,
                                       cy_stc_sd_host_context_t const *context)
{
    cy_en_sd_host_status_t       ret  = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    cy_stc_sd_host_cmd_config_t  cmd;
    cy_stc_sd_host_data_config_t dataConfig;
    uint32_t                     dataAddress;
    uint32_t aDmaDescriptTbl[CY_SD_HOST_ADMA2_DESCR_SIZE]; /* The ADMA2 descriptor table. */
    uint32_t length; /* The length of data to transfer for a descriptor. */

    if ((NULL != context) && (NULL != config) && (NULL != config->data))
    {
        CY_ASSERT_L3(CY_SD_HOST_IS_AUTO_CMD_VALID(config->autoCommand));
        CY_ASSERT_L2(CY_SD_HOST_IS_TIMEOUT_VALID(config->dataTimeout));
        CY_ASSERT_L3(CY_SD_HOST_IS_DMA_WR_RD_VALID(context->dmaType));

        dataAddress = config->address;
        /* 0 < maxSectorNum check is needed for legacy cards. */
        if (!((0UL < context->maxSectorNum) &&
             ((context->maxSectorNum - dataAddress) < config->numberOfBlocks)))
        {
            if (CY_SD_HOST_SDSC == context->cardCapacity)
            {
                dataAddress = dataAddress << CY_SD_HOST_SDSC_ADDR_SHIFT;
            }

            if (1UL < config->numberOfBlocks)
            {
                cmd.commandIndex = CY_SD_HOST_SD_CMD18;
                dataConfig.enableIntAtBlockGap = true;
            }
            else
            {
                cmd.commandIndex = CY_SD_HOST_SD_CMD17;
                dataConfig.enableIntAtBlockGap = false;
            }

            dataConfig.blockSize = CY_SD_HOST_BLOCK_SIZE;
            dataConfig.numberOfBlock = config->numberOfBlocks;
            dataConfig.enableDma = config->enableDma;
            dataConfig.autoCommand = config->autoCommand;
            dataConfig.read = true;
            dataConfig.dataTimeout = config->dataTimeout;
            dataConfig.enReliableWrite = config->enReliableWrite;

            if ((true == dataConfig.enableDma) &&
                (CY_SD_HOST_DMA_ADMA2 == context->dmaType))
            {
                length = CY_SD_HOST_BLOCK_SIZE * config->numberOfBlocks;

                aDmaDescriptTbl[0] = (1UL << CY_SD_HOST_ADMA_ATTR_VALID_POS) | /* Attr Valid */
                                     (1UL << CY_SD_HOST_ADMA_ATTR_END_POS) |   /* Attr End */
                                     (0UL << CY_SD_HOST_ADMA_ATTR_INT_POS) |   /* Attr Int */
                                     (CY_SD_HOST_ADMA_TRAN << CY_SD_HOST_ADMA_ACT_POS) |
                                     (length << CY_SD_HOST_ADMA_LEN_POS);     /* Len */

                aDmaDescriptTbl[1] = (uint32_t)config->data;

                /* The address of the ADMA2 descriptor table. */
                dataConfig.data = (uint32_t*)&aDmaDescriptTbl[0];
            }
            else
            {
                /* SDMA mode. */
                dataConfig.data = (uint32_t*)config->data;
            }

            ret = Cy_SD_Host_InitDataTransfer(base, &dataConfig);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                cmd.commandArgument = dataAddress;
                cmd.dataPresent     = true;
                cmd.enableAutoResponseErrorCheck = false;
                cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
                cmd.enableCrcCheck  = true;
                cmd.enableIdxCheck  = true;
                cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

                ret = Cy_SD_Host_SendCommand(base, &cmd);

                if (CY_SD_HOST_SUCCESS == ret)
                {
                    /* Wait for the Command Complete event. */
                    ret = Cy_SD_Host_PollCmdComplete(base);
                }

                if ((CY_SD_HOST_SUCCESS == ret) &&
                    (false == dataConfig.enableDma))
                {
                    /* DMA is not used - wait until all data is read. */
                    ret = Cy_SD_Host_CmdRxData(base, &dataConfig);
                }
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_Write
****************************************************************************//**
*
*  Writes single- or multiple-block data to the SD card / eMMC. If DMA is not
*  used this function blocks until all data is written.
*  If DMA is used all data is written when the Transfer complete event is set.
*  It is the user responsibility to check and reset the transfer complete event
*  (using \ref Cy_SD_Host_GetNormalInterruptStatus and
*  \ref Cy_SD_Host_ClearNormalInterruptStatus functions).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *config
*     The pointer to the SD card read-write structure.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_Write(SDHC_Type *base,
                                        cy_stc_sd_host_write_read_config_t *config,
                                        cy_stc_sd_host_context_t const *context)
{
    cy_en_sd_host_status_t       ret  = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    cy_stc_sd_host_cmd_config_t  cmd;
    cy_stc_sd_host_data_config_t dataConfig;
    uint32_t                     dataAddress;
    uint32_t aDmaDescriptTbl[CY_SD_HOST_ADMA2_DESCR_SIZE]; /* The ADMA2 descriptor table. */
    uint32_t length;  /* The length of data to transfer for a descriptor. */

    if ((NULL != context) && (NULL != config) && (NULL != config->data))
    {
        CY_ASSERT_L3(CY_SD_HOST_IS_AUTO_CMD_VALID(config->autoCommand));
        CY_ASSERT_L2(CY_SD_HOST_IS_TIMEOUT_VALID(config->dataTimeout));
        CY_ASSERT_L3(CY_SD_HOST_IS_DMA_WR_RD_VALID(context->dmaType));

        dataAddress = config->address;

        /* 0 < maxSectorNum check is needed for legacy cards */
        if (!((0UL < context->maxSectorNum) &&
             ((context->maxSectorNum - dataAddress) < config->numberOfBlocks)))
        {
            if (CY_SD_HOST_SDSC == context->cardCapacity)
            {
                /* The SDSC card uses a byte-unit address, multiply by 512 */
                dataAddress = dataAddress << CY_SD_HOST_SDSC_ADDR_SHIFT;
            }

            if (1UL < config->numberOfBlocks)
            {
                cmd.commandIndex = CY_SD_HOST_SD_CMD25;
                dataConfig.enableIntAtBlockGap = true;
            }
            else
            {
                cmd.commandIndex = CY_SD_HOST_SD_CMD24;
                dataConfig.enableIntAtBlockGap = false;
            }

            dataConfig.blockSize = CY_SD_HOST_BLOCK_SIZE;
            dataConfig.numberOfBlock = config->numberOfBlocks;
            dataConfig.enableDma = config->enableDma;
            dataConfig.autoCommand = config->autoCommand;
            dataConfig.read = false;
            dataConfig.data = (uint32_t*)config->data;
            dataConfig.dataTimeout = config->dataTimeout;
            dataConfig.enReliableWrite = config->enReliableWrite;

            if ((true == dataConfig.enableDma) &&
                (CY_SD_HOST_DMA_ADMA2 == context->dmaType))
            {
                length = CY_SD_HOST_BLOCK_SIZE * config->numberOfBlocks;

                aDmaDescriptTbl[0] = (1UL << CY_SD_HOST_ADMA_ATTR_VALID_POS) | /* Attr Valid */
                                     (1UL << CY_SD_HOST_ADMA_ATTR_END_POS) |   /* Attr End */
                                     (0UL << CY_SD_HOST_ADMA_ATTR_INT_POS) |   /* Attr Int */
                                     (CY_SD_HOST_ADMA_TRAN << CY_SD_HOST_ADMA_ACT_POS) |
                                     (length << CY_SD_HOST_ADMA_LEN_POS);     /* Len */

                aDmaDescriptTbl[1] = (uint32_t)config->data;

                /* The address of the ADMA descriptor table. */
                dataConfig.data = (uint32_t*)&aDmaDescriptTbl[0];
            }
            else
            {
                dataConfig.data = (uint32_t*)config->data;
            }

            ret = Cy_SD_Host_InitDataTransfer(base, &dataConfig);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                cmd.commandArgument = dataAddress;
                cmd.dataPresent     = true;
                cmd.enableAutoResponseErrorCheck = false;
                cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
                cmd.enableCrcCheck  = true;
                cmd.enableIdxCheck  = true;
                cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

                ret = Cy_SD_Host_SendCommand(base, &cmd);

                if (CY_SD_HOST_SUCCESS == ret)
                {
                    /* Wait for the Command Complete event. */
                    ret = Cy_SD_Host_PollCmdComplete(base);
                }

                if ((CY_SD_HOST_SUCCESS == ret) &&
                    (false == dataConfig.enableDma))
                {
                    /* DMA is not used - wait until all data is written. */
                    ret = Cy_SD_Host_CmdTxData(base, &dataConfig);
                }
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_Erase
****************************************************************************//**
*
*  Erases the number block data of the SD card / eMMC.
*
* \note This function starts the erase operation end exits.
* It is the user's responsibility to check when the erase operation completes.
* The erase operation completes when \ref Cy_SD_Host_GetCardStatus returns
* the status value where both ready-for-data (CY_SD_HOST_CMD13_READY_FOR_DATA)
* and card-transition (CY_SD_HOST_CARD_TRAN) bits are set.
* Also it is the user's responsibility to clear the CY_SD_HOST_CMD_COMPLETE flag
* after calling this function.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param startAddr
*     The address to start erasing from.
*
* \param endAddr
*     The address to stop erasing.
*
* \param eraseType
*     Specifies the erase type (FULE, DISCARD).
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_Erase(SDHC_Type *base,
                                        uint32_t startAddr,
                                        uint32_t endAddr,
                                        cy_en_sd_host_erase_type_t eraseType,
                                        cy_stc_sd_host_context_t const *context)
{
    cy_en_sd_host_status_t      ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    cy_stc_sd_host_cmd_config_t cmd;

    if ((NULL != context) && (NULL != base))
    {
        /* 0<maxSectorNum check is needed for legacy EMMC cards */
        if (!((0UL < context->maxSectorNum) &&
              ((context->maxSectorNum < (startAddr)) ||
               (context->maxSectorNum < (endAddr)))))
        {
            /* Initialize the command parameters */
            cmd.dataPresent    = false;
            cmd.enableAutoResponseErrorCheck = false;
            cmd.respType       = CY_SD_HOST_RESPONSE_LEN_48;
            cmd.enableCrcCheck = true;
            cmd.enableIdxCheck = true;
            cmd.cmdType        = CY_SD_HOST_CMD_NORMAL;

            /* EraseStartAddr (CMD32) */
            if (CY_SD_HOST_SDSC == context->cardCapacity)
            {
                /* The SDSC card uses a byte-unit address, multiply by 512 */
                startAddr = startAddr << CY_SD_HOST_SDSC_ADDR_SHIFT;
            }

            if (CY_SD_HOST_EMMC == context->cardType)
            {
                cmd.commandIndex = CY_SD_HOST_SD_CMD35;
            }
            else
            {
                cmd.commandIndex = CY_SD_HOST_SD_CMD32;
            }
            cmd.commandArgument = startAddr;

            ret = Cy_SD_Host_SendCommand(base, &cmd);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Wait for the Command Complete event. */
                ret = Cy_SD_Host_PollCmdComplete(base);
            }

            if (CY_SD_HOST_SUCCESS != ret)
            {
                return ret;
            }

            /* EraseEndAddr (CMD33) */
            if (CY_SD_HOST_SDSC == context->cardCapacity)
            {
                /* The SDSC card uses a byte-unit address, multiply by 512 */
                endAddr = endAddr << CY_SD_HOST_SDSC_ADDR_SHIFT;
            }

            if (CY_SD_HOST_EMMC == context->cardType)
            {
                cmd.commandIndex = CY_SD_HOST_SD_CMD36;
            }
            else
            {
                cmd.commandIndex = CY_SD_HOST_SD_CMD33;
            }
            cmd.commandArgument = endAddr;

            ret = Cy_SD_Host_SendCommand(base, &cmd);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Wait for the Command Complete event. */
                ret = Cy_SD_Host_PollCmdComplete(base);
            }

            /* Erase (CMD38) */
            cmd.commandIndex = CY_SD_HOST_SD_CMD38;

            switch (eraseType)
            {
                case CY_SD_HOST_ERASE_ERASE:
                    cmd.commandArgument = CY_SD_HOST_ERASE;
                    break;
                case CY_SD_HOST_ERASE_DISCARD:
                    if (CY_SD_HOST_EMMC == context->cardType)
                    {
                        cmd.commandArgument = CY_SD_HOST_EMMC_DISCARD;
                    }
                    else
                    {
                        cmd.commandArgument = CY_SD_HOST_SD_DISCARD;
                    }
                    break;
                case CY_SD_HOST_ERASE_FULE:
                    cmd.commandArgument = CY_SD_HOST_SD_FULE;
                    break;
                case CY_SD_HOST_ERASE_SECURE:
                    cmd.commandArgument = CY_SD_HOST_EMMC_SECURE_ERASE;
                    break;
                case CY_SD_HOST_ERASE_SECURE_TRIM_STEP_2:
                    cmd.commandArgument = CY_SD_HOST_EMMC_SECURE_TRIM_STEP_2;
                    break;
                case CY_SD_HOST_ERASE_SECURE_TRIM_STEP_1:
                    cmd.commandArgument = CY_SD_HOST_EMMC_SECURE_TRIM_STEP_1;
                    break;
                case CY_SD_HOST_ERASE_TRIM:
                    cmd.commandArgument = CY_SD_HOST_EMMC_TRIM;
                    break;
                default:
                    ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                    break;
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
               ret = Cy_SD_Host_SendCommand(base, &cmd);
            }
        }
    }

    return ret;
}

/* The commands low level section */

/*******************************************************************************
* Function Name: Cy_SD_Host_PollCmdLineFree
****************************************************************************//**
*
*  Waits for the command line free.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollCmdLineFree(SDHC_Type const *base)
{
    cy_en_sd_host_status_t ret   = CY_SD_HOST_ERROR_TIMEOUT;
    uint32_t               retry = CY_SD_HOST_RETRY_TIME;
    bool                   commandInhibit;

    while (retry > 0UL)
    {
        commandInhibit = _FLD2BOOL(SDHC_CORE_PSTATE_REG_CMD_INHIBIT,
                                   SDHC_CORE_PSTATE_REG(base));

        if (false == commandInhibit)
        {
            ret = CY_SD_HOST_SUCCESS;
            break;
        }

        Cy_SysLib_DelayUs(CY_SD_HOST_CMD_TIMEOUT_MS);
        retry--;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_PollDataLineNotInhibit
****************************************************************************//**
*
*  Waits for the data line is not inhibit.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollDataLineNotInhibit(SDHC_Type const *base)
{
    cy_en_sd_host_status_t ret   = CY_SD_HOST_ERROR_TIMEOUT;
    uint32_t               retry = CY_SD_HOST_RETRY_TIME;
    bool                   dataInhibit;

    while (retry > 0UL)
    {
        dataInhibit = _FLD2BOOL(SDHC_CORE_PSTATE_REG_CMD_INHIBIT_DAT,
                                SDHC_CORE_PSTATE_REG(base));

        if (false == dataInhibit)
        {
            ret = CY_SD_HOST_SUCCESS;
            break;
        }

        Cy_SysLib_DelayUs(CY_SD_HOST_CMD_TIMEOUT_MS);
        retry--;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_PollDataLineFree
****************************************************************************//**
*
*  Waits for the data line free.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollDataLineFree(SDHC_Type const *base)
{
    cy_en_sd_host_status_t ret   = CY_SD_HOST_SUCCESS;
    uint32_t               retry = CY_SD_HOST_RETRY_TIME;

    while ((true == _FLD2BOOL(SDHC_CORE_PSTATE_REG_DAT_LINE_ACTIVE, SDHC_CORE_PSTATE_REG(base))) &&
           (retry > 0UL))
    {
        Cy_SysLib_DelayUs(CY_SD_HOST_WRITE_TIMEOUT_MS);
        retry--;
    }

    if (true == _FLD2BOOL(SDHC_CORE_PSTATE_REG_DAT_LINE_ACTIVE, SDHC_CORE_PSTATE_REG(base)))
    {
        ret = CY_SD_HOST_ERROR_TIMEOUT;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_PollBufferReadReady
****************************************************************************//**
*
*  Waits for the Buffer Read ready event.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollBufferReadReady(SDHC_Type *base)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_TIMEOUT;
    uint32_t               retry = CY_SD_HOST_RETRY_TIME;

    while (retry > 0UL)
    {
        /* Check the Buffer Read ready */
        if (true == _FLD2BOOL(SDHC_CORE_NORMAL_INT_STAT_R_BUF_RD_READY,
                             SDHC_CORE_NORMAL_INT_STAT_R(base)))
        {
            /* Clear the interrupt flag */
             SDHC_CORE_NORMAL_INT_STAT_R(base) = CY_SD_HOST_BUF_RD_READY;

            ret = CY_SD_HOST_SUCCESS;
            break;
        }

        Cy_SysLib_DelayUs(CY_SD_HOST_BUFFER_RDY_TIMEOUT_MS);
        retry--;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_PollBufferWriteReady
****************************************************************************//**
*
*  Waits for the Buffer Write ready event.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollBufferWriteReady(SDHC_Type *base)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_TIMEOUT;
    uint32_t               retry = CY_SD_HOST_RETRY_TIME;

    while (retry > 0UL)
    {
        /* Check the Buffer Write ready */
        if (true == _FLD2BOOL(SDHC_CORE_NORMAL_INT_STAT_R_BUF_WR_READY,
                              SDHC_CORE_NORMAL_INT_STAT_R(base)))
        {
            /* Clear the interrupt flag */
             SDHC_CORE_NORMAL_INT_STAT_R(base) = CY_SD_HOST_BUF_WR_READY;

            ret = CY_SD_HOST_SUCCESS;
            break;
        }

        Cy_SysLib_DelayUs(CY_SD_HOST_BUFFER_RDY_TIMEOUT_MS);
        retry--;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_PollCmdComplete
****************************************************************************//**
*
*  Waits for the Command Complete event.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollCmdComplete(SDHC_Type *base)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_TIMEOUT;
    uint32_t               retry = CY_SD_HOST_RETRY_TIME;

    while (retry > 0UL)
    {
        /* Command Complete */
        if (true == _FLD2BOOL(SDHC_CORE_NORMAL_INT_STAT_R_CMD_COMPLETE,
                             SDHC_CORE_NORMAL_INT_STAT_R(base)))
        {
            /* Clear the interrupt flag */
             SDHC_CORE_NORMAL_INT_STAT_R(base) = CY_SD_HOST_CMD_COMPLETE;

            ret = CY_SD_HOST_SUCCESS;
            break;
        }

        Cy_SysLib_DelayUs(CY_SD_HOST_CMD_TIMEOUT_MS);
        retry--;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_PollTransferComplete
****************************************************************************//**
*
*  Waits for the Transfer Complete event.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_PollTransferComplete(SDHC_Type *base)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_TIMEOUT;
    uint32_t               retry = CY_SD_HOST_RETRY_TIME;

    while (retry > 0UL)
    {
        /* Transfer Complete */
        if (true == _FLD2BOOL(SDHC_CORE_NORMAL_INT_STAT_R_XFER_COMPLETE,
                             SDHC_CORE_NORMAL_INT_STAT_R(base)))
        {
            /* Clear the interrupt flag */
            SDHC_CORE_NORMAL_INT_STAT_R(base) = CY_SD_HOST_XFER_COMPLETE;

            ret = CY_SD_HOST_SUCCESS;
            break;
        }

        Cy_SysLib_DelayUs(CY_SD_HOST_WRITE_TIMEOUT_MS);
        retry--;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_CmdRxData
****************************************************************************//**
*
*  Reads the command data using a non-DMA data transfer.
*  This function is blocking (it exits after all data is read).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *pcmd
*     The pointer to the current command data structure.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_CmdRxData(SDHC_Type *base,
                                                   cy_stc_sd_host_data_config_t *pcmd)
{
    cy_en_sd_host_status_t ret;
    uint32_t               blkSize;
    uint32_t               blkCnt;
    uint32_t               i;
    uint32_t               retry;

    blkCnt = pcmd->numberOfBlock;
    blkSize = pcmd->blockSize;

    while (blkCnt > 0UL)
    {
        /* Wait for the Buffer Read ready. */
        ret = Cy_SD_Host_PollBufferReadReady(base);

        if (CY_SD_HOST_SUCCESS != ret)
        {
            break;
        }

        for ( i = blkSize >> 2UL; i != 0UL; i-- )
        {
            /* Wait if valid data exists in the Host buffer. */
            retry = CY_SD_HOST_RETRY_TIME;
            while ((false == _FLD2BOOL(SDHC_CORE_PSTATE_REG_BUF_RD_ENABLE,
                                      SDHC_CORE_PSTATE_REG(base))) &&
                   (retry > 0UL))
            {
                Cy_SysLib_DelayUs(CY_SD_HOST_RD_WR_ENABLE_TIMEOUT);
                retry--;
            }

            if (false == _FLD2BOOL(SDHC_CORE_PSTATE_REG_BUF_RD_ENABLE,
                                   SDHC_CORE_PSTATE_REG(base)))
            {
                break;
            }

            /* Read data from the Host buffer. */
            *pcmd->data = Cy_SD_Host_BufferRead(base);
            pcmd->data++;
        }
        blkCnt--;
    }

    /* Wait for the Transfer Complete. */
    ret = Cy_SD_Host_PollTransferComplete(base);

    (void)Cy_SD_Host_PollCmdLineFree(base);
    (void)Cy_SD_Host_PollDataLineNotInhibit(base);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_CmdTxData
****************************************************************************//**
*
*  Writes the command data using a non-DMA data transfer.
*  This function is blocking (it exits after all data is written).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *pcmd
*     The pointer to the current command data structure.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_CmdTxData(SDHC_Type *base,
                                                   cy_stc_sd_host_data_config_t *pcmd)
{
    cy_en_sd_host_status_t ret;
    uint32_t               blkSize;
    uint32_t               blkCnt;
    uint32_t               i;
    uint32_t               retry;

    blkCnt = pcmd->numberOfBlock;
    blkSize = pcmd->blockSize;

    while (0UL < blkCnt)
    {
        /* Wait for the Buffer Write ready. */
        ret = Cy_SD_Host_PollBufferWriteReady(base);

        if (CY_SD_HOST_SUCCESS != ret)
        {
            break;
        }

        for ( i = blkSize >> 2UL; i != 0UL; i-- )
        {
            /* Wait if space is available for writing data. */
            retry = CY_SD_HOST_RETRY_TIME;
            while ((false == _FLD2BOOL(SDHC_CORE_PSTATE_REG_BUF_WR_ENABLE,
                                      SDHC_CORE_PSTATE_REG(base))) &&
                   (retry > 0UL))
            {
                Cy_SysLib_DelayUs(CY_SD_HOST_RD_WR_ENABLE_TIMEOUT);
                retry--;
            }

            if (false == _FLD2BOOL(SDHC_CORE_PSTATE_REG_BUF_WR_ENABLE,
                                   SDHC_CORE_PSTATE_REG(base)))
            {
                break;
            }

            /* Write data to the Host buffer. */
            (void)Cy_SD_Host_BufferWrite(base, *pcmd->data);
            pcmd->data++;
        }
        blkCnt--;
    }

    ret = Cy_SD_Host_PollTransferComplete(base);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Check if DAT line is active. */
        ret = Cy_SD_Host_PollDataLineFree(base);
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SendCommand
****************************************************************************//**
*
*  Starts sending a command on the SD bus. If the command uses the data lines
*  Cy_SD_Host_InitDataTransfer() must be call first.
*  This function returns before the command completes.
*  To determine if the command is done, read the Normal Interrupt Status register
*  and check the CMD_COMPLETE flag. To determine if the entire transfer is done
*  check the XFER_COMPLETE flag. Also the interrupt is used and flags are set
*  on these events in an ISR.
* \note It is the user's responsibility to clear the CY_SD_HOST_CMD_COMPLETE flag
*  after calling this function.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *config
*  The configuration structure for the command.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_SendCommand(SDHC_Type *base,
                                              cy_stc_sd_host_cmd_config_t const *config)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_SUCCESS;

    if ((NULL != base) && (NULL != config))
    {
        CY_ASSERT_L2(CY_SD_HOST_IS_CMD_IDX_VALID(config->commandIndex));
        CY_ASSERT_L3(CY_SD_HOST_IS_CMD_TYPE_VALID(config->cmdType));

        ret = Cy_SD_Host_PollCmdLineFree(base);
        if (CY_SD_HOST_SUCCESS == ret)
        {
            if ((true == config->dataPresent) && (CY_SD_HOST_CMD_ABORT != config->cmdType))
            {
                /* Check the DAT line inhibits only commands with the DAT line is used
                * and when the command is not the ABORT type.
                */
                ret = Cy_SD_Host_PollDataLineNotInhibit(base);
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Set the commandArgument directly to the hardware register. */
                SDHC_CORE_ARGUMENT_R(base) = config->commandArgument;

                /* Update the command hardware register (the command is sent)
                * according to the spec, this register should be written only once.
                */
                SDHC_CORE_CMD_R(base) = (uint16_t)(_VAL2FLD(SDHC_CORE_CMD_R_CMD_TYPE, 0U) |
                                   _VAL2FLD(SDHC_CORE_CMD_R_RESP_TYPE_SELECT, (uint32_t)config->respType) |
                                   _VAL2FLD(SDHC_CORE_CMD_R_CMD_TYPE, (uint32_t)config->cmdType) |
                                   _VAL2FLD(SDHC_CORE_CMD_R_DATA_PRESENT_SEL, ((true == config->dataPresent) ? 1U : 0U)) |
                                   _VAL2FLD(SDHC_CORE_CMD_R_CMD_IDX_CHK_ENABLE, ((true == config->enableIdxCheck) ? 1U : 0U)) |
                                   _VAL2FLD(SDHC_CORE_CMD_R_CMD_CRC_CHK_ENABLE, ((true == config->enableCrcCheck) ? 1U : 0U)) |
                                   _VAL2FLD(SDHC_CORE_CMD_R_CMD_INDEX, config->commandIndex & CY_SD_HOST_ACMD_OFFSET_MASK));
            }
        }
    }
    else
    {
        ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SetBusWidth
****************************************************************************//**
*
*  Sends out the SD bus width changing command.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param width
*     The width of the data bus.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_SetBusWidth(SDHC_Type *base,
                                              cy_en_sd_host_bus_width_t width,
                                              cy_stc_sd_host_context_t const *context)
{
    cy_en_sd_host_status_t    ret = CY_SD_HOST_SUCCESS;
    uint32_t                  cmdArgument = 0UL;

    if ((NULL != base) && (NULL != context))
    {
        if (CY_SD_HOST_SD == context->cardType)
        {
            switch (width)
            {
                case CY_SD_HOST_BUS_WIDTH_1_BIT:
                    cmdArgument = 0UL;  /* 0 = 1bit */
                    break;
                case CY_SD_HOST_BUS_WIDTH_4_BIT:
                    cmdArgument = 2UL;  /* 2 = 4bit */
                    break;
                default:
                    ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                    break;
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                ret = Cy_SD_Host_OpsSetSdBusWidth(base, cmdArgument, context);
            }
        }
        else if (CY_SD_HOST_EMMC == context->cardType)
        {
            switch (width)
            {
                /* The CMD6 Argument data structure:
                 * [ACCESS:2]<<24 | [EXT_CSD IDX:8]<<16
                 * |[Value:8]<<8 | [CMD set:2]<<0
                 */
                case CY_SD_HOST_BUS_WIDTH_1_BIT:
                    cmdArgument = (CY_SD_HOST_EMMC_ACCESS_WRITE_BYTE << CY_SD_HOST_EMMC_CMD6_ACCESS_OFFSET) |
                                      (CY_SD_HOST_EMMC_BUS_WIDTH_ADDR << CY_SD_HOST_EMMC_CMD6_IDX_OFFSET) |
                                      (0x0UL << CY_SD_HOST_EMMC_CMD6_VALUE_OFFSET) |
                                      (0x0UL << CY_SD_HOST_EMMC_CMD6_CMD_SET_OFFSET);
                    break;
                case CY_SD_HOST_BUS_WIDTH_4_BIT:
                    cmdArgument = (CY_SD_HOST_EMMC_ACCESS_WRITE_BYTE << CY_SD_HOST_EMMC_CMD6_ACCESS_OFFSET) |
                                      (CY_SD_HOST_EMMC_BUS_WIDTH_ADDR << CY_SD_HOST_EMMC_CMD6_IDX_OFFSET) |
                                      (0x1UL << CY_SD_HOST_EMMC_CMD6_VALUE_OFFSET) |
                                      (0x0UL << CY_SD_HOST_EMMC_CMD6_CMD_SET_OFFSET);
                    break;
                case CY_SD_HOST_BUS_WIDTH_8_BIT:
                    cmdArgument = (CY_SD_HOST_EMMC_ACCESS_WRITE_BYTE << CY_SD_HOST_EMMC_CMD6_ACCESS_OFFSET) |
                                      (CY_SD_HOST_EMMC_BUS_WIDTH_ADDR << CY_SD_HOST_EMMC_CMD6_IDX_OFFSET) |
                                      (0x2UL << CY_SD_HOST_EMMC_CMD6_VALUE_OFFSET) |
                                      (0x0UL << CY_SD_HOST_EMMC_CMD6_CMD_SET_OFFSET);
                    break;
                default:
                    ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                    break;
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Send CMD6 */
                ret = Cy_SD_Host_OpsSwitchFunc(base, cmdArgument);
            }
        }
        else if (CY_SD_HOST_SDIO == context->cardType)
        {
            switch (width)
            {
                case CY_SD_HOST_BUS_WIDTH_1_BIT:
                    cmdArgument = 0UL;
                    break;
                case CY_SD_HOST_BUS_WIDTH_4_BIT:
                    cmdArgument = CY_SD_HOST_CCCR_BUS_WIDTH_1;
                    break;
                case CY_SD_HOST_BUS_WIDTH_8_BIT:
                    cmdArgument = CY_SD_HOST_CCCR_BUS_WIDTH_0 |
                                  CY_SD_HOST_CCCR_BUS_WIDTH_1 |
                                  CY_SD_HOST_CCCR_S8B;
                    break;
                default:
                    ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                    break;
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                ret = Cy_SD_Host_OpsSendIoRwDirectCmd(base,
                                                      1UL,
                                                      0UL,
                                                      0UL,
                                                      CY_SD_HOST_CCCR_BUS_INTERFACE_CTR,
                                                      cmdArgument);
            }
        }
        else
        {
           ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Update the host side setting. */
            ret = Cy_SD_Host_SetHostBusWidth(base, width);
        }
    }
    else
    {
       ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsGoIdle
****************************************************************************//**
*
*  Send CMD0 (Go idle).
*
* \param *base
*     The SD host registers structure pointer.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_OpsGoIdle(SDHC_Type *base)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD0;
    cmd.commandArgument = 0UL;
    cmd.enableCrcCheck  = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_NONE;
    cmd.enableIdxCheck  = false;
    cmd.dataPresent     = false;
    cmd.cmdType         = CY_SD_HOST_CMD_ABORT;

    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsVoltageSwitch
****************************************************************************//**
*
*  Send CMD11 (Signal Voltage Switch to 1.8 V).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_OpsVoltageSwitch(SDHC_Type *base,
                                                          cy_stc_sd_host_context_t const *context)
{
    (void) context;
    cy_en_sd_host_status_t      ret;
    cy_stc_sd_host_cmd_config_t cmd;
    uint32_t                    pState;

    /* Voltage switch (CMD11). */
    cmd.commandIndex                 = CY_SD_HOST_SD_CMD11;
    cmd.commandArgument              = 0UL;
    cmd.enableCrcCheck               = true;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType                     = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableIdxCheck               = true;
    cmd.dataPresent                  = false;
    cmd.cmdType                      = CY_SD_HOST_CMD_NORMAL;

    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Disable providing the SD Clock. */
        Cy_SD_Host_DisableSdClk(base);

        pState = Cy_SD_Host_GetPresentState(base) & SDHC_CORE_PSTATE_REG_DAT_3_0_Msk;

        /* Check DAT[3:0]. */
        if (0UL == pState)
        {
            /* Switch the bus to 1.8 V (Set the IO_VOLT_SEL pin to low)*/
            Cy_SD_Host_ChangeIoVoltage(base, CY_SD_HOST_IO_VOLT_1_8V);

            /* Wait 10 ms to 1.8 voltage regulator to be stable. */
            Cy_SysLib_Delay(CY_SD_HOST_1_8_REG_STABLE_TIME_MS);

            /* Check the 1.8V signaling enable. */
            if (true == _FLD2BOOL(SDHC_CORE_HOST_CTRL2_R_SIGNALING_EN,
                                  SDHC_CORE_HOST_CTRL2_R(base)))
            {
                /* Enable providing the SD Clock. */
                Cy_SD_Host_EnableSdClk(base);

                /* Wait for the stable CLK */
                Cy_SysLib_Delay(CY_SD_HOST_CLK_RAMP_UP_TIME_MS);

                pState = Cy_SD_Host_GetPresentState(base) & SDHC_CORE_PSTATE_REG_DAT_3_0_Msk;

                /* Check DAT[3:0]. */
                if (SDHC_CORE_PSTATE_REG_DAT_3_0_Msk != pState)
                {
                    ret = CY_SD_HOST_ERROR_UNUSABLE_CARD;
                }
            }
            else
            {
                ret = CY_SD_HOST_ERROR_UNUSABLE_CARD;
            }
        }
        else
        {
            ret = CY_SD_HOST_ERROR_UNUSABLE_CARD;
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsSendIoRwDirectCmd
****************************************************************************//**
*
*  Sends CMD52 (Reads/writes 1 byte to the SDIO register).
*
* \param *base
*     The SD host registers structure pointer.
* \param rwFlag
* \param functionNumber
* \param rawFlag
* \param registerAddress
* \param data
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_OpsSendIoRwDirectCmd(SDHC_Type *base,
                                                uint32_t rwFlag,
                                                uint32_t functionNumber,
                                                uint32_t rawFlag,
                                                uint32_t registerAddress,
                                                uint32_t data)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD52;
    cmd.commandArgument = ((rwFlag & 0x01UL) << CY_SD_HOST_CMD52_RWFLAG_POS) |
                          ((functionNumber & CY_SD_HOST_CMD52_FUNCT_NUM_MSK) << CY_SD_HOST_CMD52_FUNCT_NUM_POS) |
                          ((rawFlag & 0x01UL) << CY_SD_HOST_CMD52_RAWFLAG_POS) |
                          ((registerAddress & CY_SD_HOST_CMD52_REG_ADDR_MSK) << CY_SD_HOST_CMD52_REG_ADDR_POS) |
                          (data & CY_SD_HOST_CMD52_DATA_MSK);

    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48B;
    cmd.enableCrcCheck  = true;
    cmd.enableIdxCheck  = true;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsSendAppCmd
****************************************************************************//**
*
*  Sends CMD55 (Sends the application command).
* If no response of CMD55 received, the card is not the SD card.
* The CMD55 response may have an error because some SD card does not support the CMD8
* command.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_OpsSendAppCmd(SDHC_Type *base,
                                                       cy_stc_sd_host_context_t const *context)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD55;
    cmd.commandArgument = context->RCA << CY_SD_HOST_RCA_SHIFT;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = true;
    cmd.enableIdxCheck  = true;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsSendIfCond
****************************************************************************//**
*
*  Send CMD8 (Send application command).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param cmdArgument
*     The command argument.
*
* \param noResponse
*     No response if true, false - a 48 bit response with CRC and IDX check.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_OpsSendIfCond(SDHC_Type *base,
                                                uint32_t cmdArgument,
                                                bool noResponse)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD8;
    cmd.commandArgument = cmdArgument;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;
    if (noResponse)
    {
        cmd.respType        = CY_SD_HOST_RESPONSE_NONE;
        cmd.enableCrcCheck  = false;
        cmd.enableIdxCheck  = false;
    }
    else
    {
        cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
        cmd.enableCrcCheck  = true;
        cmd.enableIdxCheck  = true;
    }

    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsSelectCard
****************************************************************************//**
*
*  Send CMD7 (Send select card command).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_OpsSelectCard(SDHC_Type *base,
                                                       cy_stc_sd_host_context_t const *context)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD7;
    cmd.commandArgument = context->RCA << CY_SD_HOST_RCA_SHIFT;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48B;
    cmd.enableCrcCheck  = false;
    cmd.enableIdxCheck  = false;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }
    if (CY_SD_HOST_SUCCESS == ret)
    {
        Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

        /* The R1b response requires sending an optional busy
        * signal to the DAT line. The transfer complete event
        *  should be checked and reset.
        */
        ret = Cy_SD_Host_PollTransferComplete(base);
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsSetSdBusWidth
****************************************************************************//**
*
*  Sends ACMD6 (Send set bus width command).
*
* \param *base
*     The SD host registers structure pointer.

* \param cmdArgument
*     The command argument.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_OpsSetSdBusWidth(SDHC_Type *base,
                                                 uint32_t cmdArgument,
                                                 cy_stc_sd_host_context_t const *context)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret;

    cmd.commandIndex    = CY_SD_HOST_SD_ACMD6;
    cmd.commandArgument = cmdArgument;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = false;
    cmd.enableIdxCheck  = false;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    ret = Cy_SD_Host_OpsSendAppCmd(base, context);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        ret = Cy_SD_Host_SendCommand(base, &cmd);

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Wait for the Command Complete event. */
            ret = Cy_SD_Host_PollCmdComplete(base);
        }

        Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsSwitchFunc
****************************************************************************//**
*
*  Sends CMD6 (Sends the Switch function command).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param cmdArgument
*     The command argument.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_OpsSwitchFunc(SDHC_Type *base, uint32_t cmdArgument)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD6;
    cmd.commandArgument = cmdArgument;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = true;
    cmd.enableIdxCheck  = true;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SdCardSwitchFunc
****************************************************************************//**
*
*  Sends CMD6 (Switch Function Command) and parses the 512 bits wide
*  response on the DAT lines.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param cmdArgument
*     The command argument.
*
* \param cardType
*     The type of card.
*
* \note
*     This function is applicable only for \ref CY_SD_HOST_SD &
*     \ref CY_SD_HOST_COMBO card types
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_SdCardSwitchFunc(SDHC_Type *base,
                                                                     uint32_t cmdArgument,
                                                                     cy_en_sd_host_card_type_t cardType)
{
    cy_stc_sd_host_cmd_config_t  cmd;
    cy_en_sd_host_status_t       ret;
    cy_stc_sd_host_data_config_t dataConfig;
    uint32_t status[CY_SD_HOST_SWITCH_STATUS_LEN];

    cmd.commandIndex    = CY_SD_HOST_SD_CMD6;
    cmd.commandArgument = cmdArgument;
    cmd.dataPresent     = true;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = true;
    cmd.enableIdxCheck  = true;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    dataConfig.blockSize           = CY_SD_HOST_SD_STATUS_BLOCKS;
    dataConfig.numberOfBlock       = 1UL;
    dataConfig.enableDma           = false;
    dataConfig.autoCommand         = CY_SD_HOST_AUTO_CMD_NONE;
    dataConfig.read                = true;
    dataConfig.data                = status;
    dataConfig.dataTimeout         = CY_SD_HOST_MAX_TIMEOUT;
    dataConfig.enableIntAtBlockGap = false;
    dataConfig.enReliableWrite     = false;

    if ((cardType == CY_SD_HOST_SD) || (cardType == CY_SD_HOST_COMBO))
    {
        (void)Cy_SD_Host_InitDataTransfer(base, &dataConfig);

        ret = Cy_SD_Host_SendCommand(base, &cmd);

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Wait for the Command Complete event. */
            ret = Cy_SD_Host_PollCmdComplete(base);
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Wait for the response on the DAT lines. */
            ret = Cy_SD_Host_CmdRxData(base, &dataConfig);
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Parse the response on DAT lines. */
            if ((((status[4] >> 4UL) & 0xFUL) == 0xFUL)   || /* Function group 1 (376-379) */
                ((status[4] & 0xFUL) == 0xFUL)            || /* Function group 2 (380-383) */
                (((status[3] >> 28UL)  & 0xFUL) == 0xFUL) || /* Function group 3 (384-387) */
                (((status[3] >> 24UL) & 0xFUL) == 0xFUL)  || /* Function group 4 (388-391) */
                (((status[3] >> 20UL) & 0xFUL) == 0xFUL)  || /* Function group 5 (392-395) */
                (((status[3] >> 16UL) & 0xFUL) == 0xFUL))    /* Function group 6 (396-399) */
            {
                ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
            }
        }

        Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);
    }
    else
    {
        ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsSetBlockCount
****************************************************************************//**
*
*  Sends CMD23 (Sends the Set Block Count command).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param reliableWrite
*     For EMMC enables the reliable write.
*
* \param blockNum
*     The number of blocks to send.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_OpsSetBlockCount(SDHC_Type *base,
                                                                   bool reliableWrite,
                                                                   uint32_t blockNum)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret;
    uint32_t                    cmdArgument;

    cmdArgument = (blockNum & CY_SD_HOST_CMD23_BLOCKS_NUM_MASK) |
                  (reliableWrite ? (1UL << CY_SD_HOST_CMD23_RELIABLE_WRITE_POS) : 0UL);

    cmd.commandIndex    = CY_SD_HOST_SD_CMD23;
    cmd.commandArgument = cmdArgument;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = true;
    cmd.enableIdxCheck  = true;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsProgramCsd
****************************************************************************//**
*
*  Sends CMD27 (Sends the Program CSD command).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param csd
*     The Card-Specific Data register value.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_OpsProgramCsd(SDHC_Type *base,
                                                                uint32_t csd,
                                                                cy_stc_sd_host_context_t *context)
{
    cy_en_sd_host_status_t       ret;
    cy_stc_sd_host_cmd_config_t  cmd;
    cy_stc_sd_host_data_config_t dataConfig;
    uint32_t                     i;
    uint32_t                     blkSize = CY_SD_HOST_CSD_BLOCKS;
    uint32_t                     csdTepm;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD27;
    cmd.commandArgument = context->RCA << CY_SD_HOST_RCA_SHIFT;
    cmd.dataPresent     = true;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = true;
    cmd.enableIdxCheck  = true;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    dataConfig.blockSize            = CY_SD_HOST_CSD_BLOCKS;
    dataConfig.numberOfBlock        = 1UL;
    dataConfig.enableDma            = false;
    dataConfig.autoCommand          = CY_SD_HOST_AUTO_CMD_NONE;
    dataConfig.read                 = false;
    dataConfig.data                 = context->csd;
    dataConfig.dataTimeout          = CY_SD_HOST_MAX_TIMEOUT;
    dataConfig.enableIntAtBlockGap  = false;
    dataConfig.enReliableWrite      = false;

    /* The CSD register is sent using DAT lines. Initialize a data transfer in Non-DMA mode. */
    (void)Cy_SD_Host_InitDataTransfer(base, &dataConfig);

    /* Send the program CSD command (CMD27) */
    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait when buffer is read ready. */
        ret = Cy_SD_Host_PollBufferWriteReady(base);

        for (i = (blkSize >> 2UL); i != 0UL; i--)
        {
            /* The CSD register is sent a using usual data (8-bit width) type of the Data packet format.
             * The usual data (8-bit width) is sent in the LSB (Least Significant Byte) first,
             * MSB (Most Significant Byte) last. The bytes in each context->csd[] element
             * should be reordered and shifted right to one byte.
             */
            csdTepm = ((context->csd[i-1UL] & CY_SD_HOST_CSD_ISBL_MASK) >> CY_SD_HOST_CSD_ISB_SHIFT) |
                      (context->csd[i-1UL] & CY_SD_HOST_CSD_ISBR_MASK) |
                      ((context->csd[i-1UL] & CY_SD_HOST_CSD_LSB_MASK) << CY_SD_HOST_CSD_ISB_SHIFT);

            if (i > 1UL)
            {
                csdTepm |= (context->csd[i-2UL] & CY_SD_HOST_CSD_MSB_MASK);
            }
            else
            {
                csdTepm &= ~((1UL << CY_SD_HOST_CSD_TEMP_WRITE_PROTECT) | /* Clear TMP_WRITE_PROTECT bit in the CSD register. */
                             CY_SD_HOST_CSD_MSB_MASK);
                csdTepm |= csd; /* Set writable bits of the CSD register. */
            }

            (void)Cy_SD_Host_BufferWrite(base, csdTepm);
        }

        /* Wait for the transfer complete */
        ret = Cy_SD_Host_PollTransferComplete(base);

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Check if the data line is free. */
            ret = Cy_SD_Host_PollDataLineFree(base);
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsSdioSendOpCond
****************************************************************************//**
*
*  Send CMD5 (Send SDIO operation condition command).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *ocrReg
*     The Operation Condition register (OCR).
*
* \param cmdArgument
*     The command argument.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_OpsSdioSendOpCond(SDHC_Type *base,
                                                           uint32_t *ocrReg,
                                                           uint32_t cmdArgument)
{
    cy_en_sd_host_status_t      ret;
    cy_stc_sd_host_cmd_config_t cmd;
    uint32_t                    response = 0UL;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD5;
    cmd.commandArgument = cmdArgument;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = false;
    cmd.enableIdxCheck  = false;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    /* Send the SDIO operation condition command (CMD5) */
    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    (void)Cy_SD_Host_GetResponse(base, (uint32_t *)&response, false);

    *ocrReg = response;

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_OpsSdSendOpCond
****************************************************************************//**
*
*  Send ACMD41 (Send SD operation condition command).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *ocrReg
*     The Operation Condition register (OCR).
*
* \param cmdArgument
*     The command argument.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_OpsSdSendOpCond(SDHC_Type *base,
                                                  uint32_t *ocrReg,
                                                  uint32_t cmdArgument,
                                                  cy_stc_sd_host_context_t const *context)
{
    cy_en_sd_host_status_t      ret;
    cy_stc_sd_host_cmd_config_t cmd;
    uint32_t                    response = 0UL;

    cmd.commandIndex    = CY_SD_HOST_SD_ACMD41;
    cmd.commandArgument = cmdArgument;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = false;
    cmd.enableIdxCheck  = false;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    /* Send the application command (CMD55) */
    ret = Cy_SD_Host_OpsSendAppCmd(base, context);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        ret = Cy_SD_Host_SendCommand(base, &cmd);

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Wait for the Command Complete event. */
            ret = Cy_SD_Host_PollCmdComplete(base);
        }

        Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

        (void)Cy_SD_Host_GetResponse(base, (uint32_t *)&response, false);

        *ocrReg = response;

        if (0x0UL == cmdArgument)
        {
            /* Voltage window = 0 */
        }
        else if (0UL == (response & CY_SD_HOST_ARG_ACMD41_BUSY))
        {
            /* Set an error */
            ret = CY_SD_HOST_OPERATION_INPROGRESS;
        }
        else
        {
            /* Success */
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_MmcOpsSendOpCond
****************************************************************************//**
*
*  Send CMD1 (Send MMC operation condition command).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *ocrReg
*     The Operation Condition register (OCR).
*
* \param cmdArgument
*     The command argument.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_MmcOpsSendOpCond(SDHC_Type *base,
                                                   uint32_t *ocrReg,
                                                   uint32_t cmdArgument)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret;
    uint32_t                    response = 0UL;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD1;
    cmd.commandArgument = cmdArgument;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48; /* R3 response */
    cmd.enableCrcCheck  = false;
    cmd.enableIdxCheck  = false;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    ret = Cy_SD_Host_SendCommand(base, &cmd);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Wait for the Command Complete event. */
        ret = Cy_SD_Host_PollCmdComplete(base);
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    /* Get the OCR register */
    (void)Cy_SD_Host_GetResponse(base, (uint32_t *)&response, false);

    *ocrReg = response;

    if (CY_SD_HOST_OCR_BUSY_BIT != (CY_SD_HOST_OCR_BUSY_BIT & response))
    {
        ret = CY_SD_HOST_OPERATION_INPROGRESS;
    }

    return ret;
}

/* The SD driver low-level section */

/*******************************************************************************
* Function Name: Cy_SD_Host_SdCardChangeClock
****************************************************************************//**
*
*  Changes the Host controller SD clock.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param frequency
*     The frequency in Hz.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
static cy_en_sd_host_status_t Cy_SD_Host_SdCardChangeClock(SDHC_Type *base, uint32_t frequency)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    uint32_t               clkDiv;
    uint32_t               clockInput = CY_SD_HOST_PERI_FREQUENCY;

    CY_ASSERT_L2(CY_SD_HOST_IS_FREQ_VALID(frequency));

    if (NULL != base)
    {
        clkDiv = (clockInput / frequency) >> 1UL;
        Cy_SD_Host_DisableSdClk(base);
        ret = Cy_SD_Host_SetSdClkDiv(base, (uint16_t)clkDiv);
        Cy_SD_Host_EnableSdClk(base);
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_Init
****************************************************************************//**
*
*  Initializes the SD host module.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param config
*     The SD host module configuration.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_Init(SDHC_Type *base,
                      const cy_stc_sd_host_init_config_t *config,
                      cy_stc_sd_host_context_t *context)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_SUCCESS;

    /* Check for the NULL pointer. */
    if ((NULL != base) && (NULL != config) && (NULL != context))
    {
        CY_ASSERT_L3(CY_SD_HOST_IS_DMA_VALID(config->dmaType));

        SDHC_CORE_GP_OUT_R(base) = _VAL2FLD(SDHC_CORE_GP_OUT_R_IO_VOLT_SEL_OE, 1u) | /* The IO voltage selection signal. */
                              _VAL2FLD(SDHC_CORE_GP_OUT_R_CARD_MECH_WRITE_PROT_EN, 1u) | /* The mechanical write protection. */
                              _VAL2FLD(SDHC_CORE_GP_OUT_R_LED_CTRL_OE, config->enableLedControl ? 1u : 0u) | /* The LED Control. */
                              _VAL2FLD(SDHC_CORE_GP_OUT_R_CARD_CLOCK_OE, 1u) | /* The Sd Clk. */
                              _VAL2FLD(SDHC_CORE_GP_OUT_R_CARD_IF_PWR_EN_OE, 1u) | /* Enable the card_if_pwr_en. */
                              _VAL2FLD(SDHC_CORE_GP_OUT_R_CARD_DETECT_EN, 1u); /* Enable the card detection. */

        SDHC_CORE_XFER_MODE_R(base) = 0U;

        context->dmaType = config->dmaType;

        if (config->emmc)
        {
            /* Save the card type. */
            context->cardType = CY_SD_HOST_EMMC;

            /* Set the eMMC Card present. */
            SDHC_CORE_EMMC_CTRL_R(base) = (uint16_t)_CLR_SET_FLD16U(SDHC_CORE_EMMC_CTRL_R(base),
                                          SDHC_CORE_EMMC_CTRL_R_CARD_IS_EMMC,
                                          1U);

        }
        else
        {
            /* Save the card type. */
            context->cardType = CY_SD_HOST_NOT_EMMC;
        }

        if (config->enableLedControl)
        {
            /* LED Control. */
            SDHC_CORE_HOST_CTRL1_R(base) = (uint8_t)_CLR_SET_FLD8U(SDHC_CORE_HOST_CTRL1_R(base),
                                          SDHC_CORE_HOST_CTRL1_R_LED_CTRL,
                                          1U);
        }

        /* Select ADMA or not. */
        SDHC_CORE_HOST_CTRL1_R(base) = (uint8_t)_CLR_SET_FLD8U(SDHC_CORE_HOST_CTRL1_R(base),
                                      SDHC_CORE_HOST_CTRL1_R_DMA_SEL,
                                      config->dmaType);

        /* Set the data timeout to the max. */
        SDHC_CORE_TOUT_CTRL_R(base) = _CLR_SET_FLD8U(SDHC_CORE_TOUT_CTRL_R(base),
                                                SDHC_CORE_TOUT_CTRL_R_TOUT_CNT,
                                                CY_SD_HOST_MAX_TIMEOUT);

        /* Enable all statuses. */
        Cy_SD_Host_SetNormalInterruptEnable(base, CY_SD_HOST_NORMAL_INT_MSK);
        Cy_SD_Host_SetErrorInterruptEnable(base, CY_SD_HOST_ERROR_INT_MSK);

        /* Enable Host Version 4. */
        SDHC_CORE_HOST_CTRL2_R(base) = (uint16_t)_CLR_SET_FLD16U(SDHC_CORE_HOST_CTRL2_R(base),
                                      SDHC_CORE_HOST_CTRL2_R_HOST_VER4_ENABLE,
                                      1U);

        /* Wait for the Host stable voltage. */
        Cy_SysLib_Delay(CY_SD_HOST_SUPPLY_RAMP_UP_TIME_MS);

        /* Reset normal events. */
        Cy_SD_Host_NormalReset(base);
    }
    else
    {
        ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_DeInit
****************************************************************************//**
*
* Restores the SD Host block registers back to default.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
void Cy_SD_Host_DeInit(SDHC_Type *base)
{
    /* Check for the NULL pointer. */
    if (NULL != base)
    {
        (void)Cy_SD_Host_PollCmdLineFree(base);
        (void)Cy_SD_Host_PollDataLineNotInhibit(base);

        Cy_SD_Host_SoftwareReset(base, CY_SD_HOST_RESET_ALL);

        /* Disable the SDHC block. */
        SDHC_WRAP_CTL(base) = _CLR_SET_FLD32U(SDHC_WRAP_CTL(base),
                                              SDHC_WRAP_CTL_ENABLE,
                                              0UL);
    }
}


/*******************************************************************************
* Function Name: Cy_SD_Host_AbortTransfer
****************************************************************************//**
*
*  Calling this function causes abortion of the currently executing command with
*  data. It doesn't issue a reset, that is the users responsibility.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t  Cy_SD_Host_AbortTransfer(SDHC_Type *base,
                                                 cy_stc_sd_host_context_t const *context)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    uint32_t                    response = 0UL;
    uint32_t                    retry;

    /* Check for the NULL pointer. */
    if ((NULL != base) && (NULL != context))
    {
        /* Check the card - Memory or SDIO? */
        if (CY_SD_HOST_SDIO == context->cardType)
        {
            ret = Cy_SD_Host_OpsSendIoRwDirectCmd(base,
                                                  1UL,
                                                  0UL,
                                                  0UL,
                                                  CY_SD_HOST_CCCR_IO_ABORT,
                                                  1UL);
        }
        else
        {
            cmd.commandArgument = context->RCA << CY_SD_HOST_RCA_SHIFT;
            cmd.dataPresent = false;
            cmd.enableAutoResponseErrorCheck = false;
            cmd.enableCrcCheck = true;
            cmd.enableIdxCheck = true;

            /* Issue CMD12. */
            cmd.respType = CY_SD_HOST_RESPONSE_LEN_48B;
            cmd.commandIndex = CY_SD_HOST_SD_CMD12;
            cmd.cmdType      = CY_SD_HOST_CMD_ABORT;
            ret = Cy_SD_Host_SendCommand(base, &cmd);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Wait for the Command Complete event. */
                ret = Cy_SD_Host_PollCmdComplete(base);
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

                ret = CY_SD_HOST_ERROR_TIMEOUT;
                retry = CY_SD_HOST_RETRY_TIME;

                /* Waiting for DAT0 deassertion in scope of R1b response */
                while (retry > 0UL)
                {
                    /* Command Complete */
                    if ((Cy_SD_Host_GetPresentState(base) & CY_SD_HOST_DAT_0_Msk) == CY_SD_HOST_DAT_0_Msk)
                    {
                        ret = CY_SD_HOST_SUCCESS;
                        break;
                    }

                    Cy_SysLib_DelayUs(CY_SD_HOST_CMD_TIMEOUT_MS);
                    retry--;
                }
            }

            if (CY_SD_HOST_SUCCESS != ret)
            {
                return ret;
            }

            Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

            Cy_SD_Host_ErrorReset(base);

            /* Issue CMD13. */
            cmd.respType = CY_SD_HOST_RESPONSE_LEN_48;
            cmd.commandIndex = CY_SD_HOST_SD_CMD13;
            cmd.cmdType      = CY_SD_HOST_CMD_NORMAL;
            ret = Cy_SD_Host_SendCommand(base, &cmd);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Wait for the Command Complete event. */
                ret = Cy_SD_Host_PollCmdComplete(base);
            }

            if (CY_SD_HOST_SUCCESS != ret)
            {
                return ret;
            }

            Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

            /* Get R1 */
            (void)Cy_SD_Host_GetResponse(base, (uint32_t *)&response, false);

            /* Check if the card is in the transition state. */
            if ((CY_SD_HOST_CARD_TRAN << CY_SD_HOST_CMD13_CURRENT_STATE) !=
                (response & CY_SD_HOST_CMD13_CURRENT_STATE_MSK))
            {
                /* Issue CMD12 */
                cmd.respType = CY_SD_HOST_RESPONSE_LEN_48B;
                cmd.commandIndex = CY_SD_HOST_SD_CMD12;
                cmd.cmdType       = CY_SD_HOST_CMD_ABORT;
                ret = Cy_SD_Host_SendCommand(base, &cmd);

                if (CY_SD_HOST_SUCCESS == ret)
                {
                    /* Wait for the Command Complete event. */
                    ret = Cy_SD_Host_PollCmdComplete(base);
                }

                if (CY_SD_HOST_SUCCESS == ret)
                {
                    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

                    ret = CY_SD_HOST_ERROR_TIMEOUT;
                    retry = CY_SD_HOST_RETRY_TIME;

                    /* Waiting for DAT0 deassertion in scope of R1b response */
                    while (retry > 0UL)
                    {
                        /* Command Complete */
                        if ((Cy_SD_Host_GetPresentState(base) & CY_SD_HOST_DAT_0_Msk) == CY_SD_HOST_DAT_0_Msk)
                        {
                            ret = CY_SD_HOST_SUCCESS;
                            break;
                        }

                        Cy_SysLib_DelayUs(CY_SD_HOST_CMD_TIMEOUT_MS);
                        retry--;
                    }
                }

                if (CY_SD_HOST_SUCCESS != ret)
                {
                    return ret;
                }

                Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

                Cy_SD_Host_ErrorReset(base);

                /* Issue CMD13. */
                cmd.respType = CY_SD_HOST_RESPONSE_LEN_48;
                cmd.commandIndex = CY_SD_HOST_SD_CMD13;
                cmd.cmdType      = CY_SD_HOST_CMD_NORMAL;
                ret = Cy_SD_Host_SendCommand(base, &cmd);

                if (CY_SD_HOST_SUCCESS == ret)
                {
                    /* Wait for the Command Complete event. */
                    ret = Cy_SD_Host_PollCmdComplete(base);
                }
                if (CY_SD_HOST_SUCCESS == ret)
                {
                    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

                    /* Get R1. */
                    (void)Cy_SD_Host_GetResponse(base, (uint32_t *)&response, false);

                    /* Check if the card is in the transition state. */
                    if ((CY_SD_HOST_CARD_TRAN << CY_SD_HOST_CMD13_CURRENT_STATE) !=
                        (response & CY_SD_HOST_CMD13_CURRENT_STATE_MSK))
                    {
                       ret = CY_SD_HOST_ERROR;
                    }
                }
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_WriteProtect
****************************************************************************//**
*
*  Write protects the blocks of data from the SD card.
*  This function should only be called after Cy_SD_Host_SDCard_Init()/eMMC_Init().
*
* \param *base
*     The SD host registers structure pointer.
*
* \param writeProtect
*     \ref cy_en_sd_host_write_protect_t.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_WriteProtect(SDHC_Type *base,
                                               cy_en_sd_host_write_protect_t writeProtect,
                                               cy_stc_sd_host_context_t *context)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_SUCCESS;
    uint32_t               csdReg;

    /* Check for the NULL pointer. */
    if ((NULL != base) && (NULL != context))
    {
        switch (writeProtect)
        {
            case CY_SD_HOST_PERMANENT:
                csdReg = 1UL << CY_SD_HOST_CSD_PERM_WRITE_PROTECT;
                break;
            case CY_SD_HOST_ENABLE_TEMPORARY:
                csdReg = 1UL << CY_SD_HOST_CSD_TEMP_WRITE_PROTECT;
                break;
            case CY_SD_HOST_DISABLE_TEMPORARY:
                csdReg = 0UL;
                break;
            default:
                ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                break;
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            ret = Cy_SD_Host_OpsProgramCsd(base, csdReg, context);
        }
    }
    else
    {
        ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetCardStatus
****************************************************************************//**
*
*  Returns the card status.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return uint32_t
*     The card status (the result of the CMD13 command). To get the details of
* card status, "AND" returned value with \ref cy_en_sd_host_r1_response_t.
*
*******************************************************************************/
uint32_t Cy_SD_Host_GetCardStatus(SDHC_Type *base,
                                  cy_stc_sd_host_context_t const *context)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    uint32_t                    response = 0UL;
    uint32_t                    status = (1UL << CY_SD_HOST_CMD13_ERROR);

    /* Check for the NULL pointer. */
    if ((NULL != base) && (NULL != context))
    {
        cmd.commandIndex    = CY_SD_HOST_SD_CMD13;
        cmd.commandArgument = context->RCA << CY_SD_HOST_RCA_SHIFT;
        cmd.dataPresent     = false;
        cmd.enableAutoResponseErrorCheck = false;
        cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
        cmd.enableCrcCheck  = true;
        cmd.enableIdxCheck  = true;
        cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

        ret = Cy_SD_Host_SendCommand(base, &cmd);

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Wait for the Command Complete event. */
            ret = Cy_SD_Host_PollCmdComplete(base);
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            (void)Cy_SD_Host_GetResponse(base, (uint32_t *)&response, false);
            status = response;
        }
        else
        {
            status = (1UL << CY_SD_HOST_CMD13_ERROR);
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetSdStatus
****************************************************************************//**
*
*  Returns the SD status from the card.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *sdStatus
*     The pointer to where to store the SD status array.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_GetSdStatus(SDHC_Type *base,
                                              uint32_t *sdStatus,
                                              cy_stc_sd_host_context_t const *context)
{
    cy_en_sd_host_status_t       ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    cy_stc_sd_host_cmd_config_t  cmd;
    cy_stc_sd_host_data_config_t dataConfig;

    /* Check for the NULL pointer */
    if ((NULL != base) && (NULL != sdStatus) && (NULL != context))
    {
        ret = Cy_SD_Host_OpsSendAppCmd(base, context);
        if (CY_SD_HOST_SUCCESS == ret)
        {
            cmd.commandIndex    = CY_SD_HOST_SD_CMD13;
            cmd.commandArgument = context->RCA << CY_SD_HOST_RCA_SHIFT;
            cmd.dataPresent     = true;
            cmd.enableAutoResponseErrorCheck = false;
            cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
            cmd.enableCrcCheck  = true;
            cmd.enableIdxCheck  = true;
            cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

            dataConfig.blockSize            = CY_SD_HOST_SD_STATUS_BLOCKS;
            dataConfig.numberOfBlock        = 1UL;
            dataConfig.enableDma            = false;
            dataConfig.autoCommand          = CY_SD_HOST_AUTO_CMD_NONE;
            dataConfig.read                 = true;
            dataConfig.data                 = sdStatus;
            dataConfig.dataTimeout          = CY_SD_HOST_MAX_TIMEOUT;
            dataConfig.enableIntAtBlockGap  = false;
            dataConfig.enReliableWrite      = false;

            (void)Cy_SD_Host_InitDataTransfer(base, &dataConfig);

            ret = Cy_SD_Host_SendCommand(base, &cmd);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Wait for the Command Complete event. */
                ret = Cy_SD_Host_PollCmdComplete(base);
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                ret = Cy_SD_Host_CmdRxData(base, &dataConfig);
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetOcr
****************************************************************************//**
*
*  Reads the Operating Condition Register (OCR) register from the card.
*
* \note This function can be used only if the card is in the Idle state.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return uint32_t
*     The OCR register.
*
* \note For combo cards, the function returns the OCR register for the IO portion only.
*
*******************************************************************************/
uint32_t Cy_SD_Host_GetOcr(SDHC_Type *base, cy_stc_sd_host_context_t const *context)
{
    uint32_t ocrReg = 0UL;

    if (CY_SD_HOST_SD == context->cardType)
    {
        (void)Cy_SD_Host_OpsSdSendOpCond(base, &ocrReg, 0UL, context);
    }
    else if (CY_SD_HOST_EMMC == context->cardType)
    {
        (void)Cy_SD_Host_MmcOpsSendOpCond(base, &ocrReg, 0UL);
    }
    else if ((CY_SD_HOST_SDIO == context->cardType) ||
             (CY_SD_HOST_COMBO == context->cardType))
    {
        (void)Cy_SD_Host_OpsSdioSendOpCond(base, &ocrReg, 0UL);
    }
    else
    {
        /* Invalid card. */
    }

    return ocrReg;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetCid
****************************************************************************//**
*
*  Returns the Card Identification Register (CID) contents.
*
* \note This function can be used only if the card is in the Ready state.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param cid
*     The pointer to where to store the CID register.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_GetCid(SDHC_Type *base,
                                         uint32_t *cid)
{
    cy_stc_sd_host_cmd_config_t cmd;
    cy_en_sd_host_status_t      ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    uint32_t                    i;
    uint32_t                    response[CY_SD_HOST_RESPONSE_SIZE] = { 0UL };

    /* Check for the NULL pointer */
    if ((NULL != base) && (NULL != cid))
    {
        cmd.commandIndex    = CY_SD_HOST_SD_CMD2;
        cmd.commandArgument = 0UL;
        cmd.dataPresent     = false;
        cmd.enableAutoResponseErrorCheck = false;
        cmd.respType        = CY_SD_HOST_RESPONSE_LEN_136;
        cmd.enableCrcCheck  = true;
        cmd.enableIdxCheck  = false;
        cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

        ret = Cy_SD_Host_SendCommand(base, &cmd);

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Wait for the Command Complete event. */
            ret = Cy_SD_Host_PollCmdComplete(base);
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            (void)Cy_SD_Host_GetResponse(base, (uint32_t *)response, true);

            /* Get CID from the response. */
            for ( i = 0UL; i < CY_SD_HOST_CID_SIZE; i++ )
            {
                cid[i] = *((uint32_t *)(response + i));
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetCsd
****************************************************************************//**
*
*  Returns the Card Specific Data (CSD) register contents.
*
* \note This function can be used only if the card is in the Stand-by state.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *csd
*     The pointer to where to store the CSD register.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_GetCsd(SDHC_Type *base,
                                         uint32_t *csd,
                                         cy_stc_sd_host_context_t *context)
{
    cy_stc_sd_host_cmd_config_t   cmd;
    cy_en_sd_host_status_t        ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    uint32_t                      response[CY_SD_HOST_RESPONSE_SIZE] = { 0UL };
    uint32_t                      numSector;
    uint32_t                      cSize;
    uint32_t                      cSizeMult;
    uint32_t                      readBlLen;

    /* Check for the NULL pointer */
    if ((NULL != base) && (NULL != csd) && (NULL != context))
    {
        cmd.commandIndex    = CY_SD_HOST_SD_CMD9;
        cmd.commandArgument = context->RCA << CY_SD_HOST_RCA_SHIFT;
        cmd.dataPresent     = false;
        cmd.enableAutoResponseErrorCheck = false;
        cmd.respType        = CY_SD_HOST_RESPONSE_LEN_136;
        cmd.enableCrcCheck  = true;
        cmd.enableIdxCheck  = false;
        cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

        ret = Cy_SD_Host_SendCommand(base, &cmd);

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Wait for the Command Complete event. */
            ret = Cy_SD_Host_PollCmdComplete(base);
        }

        if (ret == CY_SD_HOST_SUCCESS)
        {
            (void)Cy_SD_Host_GetResponse(base, (uint32_t *)response, true);

            (void)memcpy(csd, response, sizeof(response));
            (void)memcpy(context->csd, response, sizeof(response));

            if ((CY_SD_HOST_SDHC == context->cardCapacity) ||
                (CY_SD_HOST_SDXC == context->cardCapacity)) /* High/Ext. Capacity (CSD version 2.0) */
            {
                cSize = (response[1] & CY_SD_HOST_CSD_V2_C_SIZE_MASK) >>
                         CY_SD_HOST_CSD_V2_C_SIZE_POS;

                numSector = (cSize + 1UL) << CY_SD_HOST_CSD_V2_SECTOR_MULT;
            }
            else /* Standard Capacity (CSD version 1.0) */
            {
                cSize =  (response[2] & CY_SD_HOST_CSD_V1_C_SIZE_MSB_MASK) <<
                         CY_SD_HOST_CSD_V1_C_SIZE_MSB_MULT;    /* C_SIZE3 */
                cSize +=((response[1] & CY_SD_HOST_CSD_V1_C_SIZE_ISB_MASK) >>
                         CY_SD_HOST_CSD_V1_C_SIZE_ISB_POS) <<
                         CY_SD_HOST_CSD_V1_C_SIZE_ISB_MULT;    /* C_SIZE2 */
                cSize += (response[1] & CY_SD_HOST_CSD_V1_C_SIZE_LSB_MASK) >>
                          CY_SD_HOST_CSD_V1_C_SIZE_LSB_POS;    /* C_SIZE1 */

                cSizeMult = ((response[1] & CY_SD_HOST_CSD_V1_C_SIZE_MULT_MASK) >>
                             CY_SD_HOST_CSD_V1_C_SIZE_MULT_POS);

                readBlLen = (response[2] & CY_SD_HOST_CSD_V1_READ_BL_LEN_MASK) >>
                             CY_SD_HOST_CSD_V1_READ_BL_LEN_POS; /* READ_BL_LEN */

                numSector = (cSize + 1UL) << (cSizeMult + 2UL);

                if (CY_SD_HOST_CSD_V1_BL_LEN_1024 == readBlLen)
                {
                    numSector *= CY_SD_HOST_CSD_V1_1024_SECT_FACTOR;
                }
                else if (CY_SD_HOST_CSD_V1_BL_LEN_2048 == readBlLen)
                {
                    numSector *= CY_SD_HOST_CSD_V1_2048_SECT_FACTOR;
                }
                else
                {
                    /* Block length = 512 bytes (readBlLen = 9u) */
                }
            }

            context->maxSectorNum = numSector;
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetExtCsd
****************************************************************************//**
*
*  Returns the EXTCSD Register contents. This is only for EMMC cards.
*  There are 512 bytes of data being read.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *extCsd
*     The pointer to where to store the EXTCSD register.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_GetExtCsd(SDHC_Type *base, uint32_t *extCsd,
                                                   cy_stc_sd_host_context_t *context)
{
    cy_stc_sd_host_cmd_config_t  cmd;
    cy_en_sd_host_status_t       ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    cy_stc_sd_host_data_config_t dataConfig;

    /* Check for the NULL pointer */
    if ((NULL != base) && (NULL != extCsd) && (NULL != context))
    {
        cmd.commandIndex    = CY_SD_HOST_MMC_CMD8;
        cmd.commandArgument = context->RCA << CY_SD_HOST_RCA_SHIFT;
        cmd.dataPresent     = true;
        cmd.enableAutoResponseErrorCheck = false;
        cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
        cmd.enableCrcCheck  = true;
        cmd.enableIdxCheck  = true;
        cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

        dataConfig.blockSize            = CY_SD_HOST_BLOCK_SIZE;
        dataConfig.numberOfBlock        = 1UL;
        dataConfig.enableDma            = false;
        dataConfig.autoCommand          = CY_SD_HOST_AUTO_CMD_NONE;
        dataConfig.read                 = true;
        dataConfig.data                 = extCsd;
        dataConfig.dataTimeout          = CY_SD_HOST_MAX_TIMEOUT;
        dataConfig.enableIntAtBlockGap  = false;
        dataConfig.enReliableWrite      = false;

        (void)Cy_SD_Host_InitDataTransfer(base, &dataConfig);

        ret = Cy_SD_Host_SendCommand(base, &cmd);

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* Wait for the Command Complete event. */
            ret = Cy_SD_Host_PollCmdComplete(base);
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            ret = Cy_SD_Host_CmdRxData(base, &dataConfig);
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            context->maxSectorNum = extCsd[CY_SD_HOST_EXTCSD_SEC_COUNT];

            context->cardCapacity = CY_SD_HOST_EMMC_LESS_2G;

            /* Check if the eMMC capacity is greater than 2GB */
            if ((CY_SD_HOST_MMC_LEGACY_SIZE_BYTES/CY_SD_HOST_BLOCK_SIZE) <
                 context->maxSectorNum)
            {
                context->cardCapacity = CY_SD_HOST_EMMC_GREATER_2G;
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetRca
****************************************************************************//**
*
*  Reads the Relative Card Address (RCA) register from the card.
*
* \note This function can be used only if the card is in the Identification or
* Stand-by state.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return uint32_t
*     The RCA register.
*
*******************************************************************************/
uint32_t Cy_SD_Host_GetRca(SDHC_Type *base)
{
    cy_stc_sd_host_cmd_config_t cmd;
    uint32_t                    response = 0UL;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD3;
    cmd.commandArgument = 0UL;
    cmd.dataPresent     = false;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = true;
    cmd.enableIdxCheck  = true;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    (void)Cy_SD_Host_SendCommand(base, &cmd);

    /* Wait for the Command Complete event. */
    (void)Cy_SD_Host_PollCmdComplete(base);

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    (void)Cy_SD_Host_GetResponse(base, (uint32_t *)&response, false);

    return (response >> CY_SD_HOST_RCA_SHIFT);
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetScr
****************************************************************************//**
*
*  Returns the SD Card Configuration Register (SCR) Register contents.
*
* \note This function can be used only if the card is in the Transition state.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *scr
*     The pointer to where to store the SCR register.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_GetScr(SDHC_Type *base,
                                         uint32_t *scr,
                                         cy_stc_sd_host_context_t const *context)
{
    cy_stc_sd_host_cmd_config_t  cmd;
    cy_en_sd_host_status_t       ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    cy_stc_sd_host_data_config_t dataConfig;

    /* Check for the NULL pointer */
    if ((NULL != base) && (NULL != scr) && (NULL != context))
    {
        ret = Cy_SD_Host_OpsSendAppCmd(base, context);
        if (CY_SD_HOST_SUCCESS == ret)
        {
            cmd.commandIndex    = CY_SD_HOST_SD_ACMD51;
            cmd.commandArgument = context->RCA << CY_SD_HOST_RCA_SHIFT;
            cmd.dataPresent     = true;
            cmd.enableAutoResponseErrorCheck = false;
            cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48B;
            cmd.enableCrcCheck  = true;
            cmd.enableIdxCheck  = true;
            cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

            dataConfig.blockSize           = CY_SD_HOST_SCR_BLOCKS;
            dataConfig.numberOfBlock       = 1UL;
            dataConfig.enableDma           = false;
            dataConfig.autoCommand         = CY_SD_HOST_AUTO_CMD_NONE;
            dataConfig.read                = true;
            dataConfig.data                = (uint32_t *)scr;
            dataConfig.dataTimeout         = CY_SD_HOST_MAX_TIMEOUT;
            dataConfig.enableIntAtBlockGap = false;
            dataConfig.enReliableWrite     = false;

            (void)Cy_SD_Host_InitDataTransfer(base, &dataConfig);

            ret = Cy_SD_Host_SendCommand(base, &cmd);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Wait for the Command Complete event. */
                ret = Cy_SD_Host_PollCmdComplete(base);
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                ret = Cy_SD_Host_CmdRxData(base, &dataConfig);
            }
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_ErrorReset
****************************************************************************//**
*
*  Checks for error event and resets it. Then resets the CMD line.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
static void Cy_SD_Host_ErrorReset(SDHC_Type *base)
{
    uint32_t intError; /* The error events mask. */

    intError = Cy_SD_Host_GetErrorInterruptStatus(base);

    /* Check the error event. */
    if (0UL < intError)
    {
        /* Clear the error event. */
        Cy_SD_Host_ClearErrorInterruptStatus(base, intError);

        Cy_SD_Host_SoftwareReset(base, CY_SD_HOST_RESET_CMD_LINE);
    }
}


/*******************************************************************************
* Function Name: Cy_SD_Host_NormalReset
****************************************************************************//**
*
*  Checks for a normal event and resets it.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
static void Cy_SD_Host_NormalReset(SDHC_Type *base)
{
    uint32_t intNormal; /* The normal events mask. */

    intNormal = Cy_SD_Host_GetNormalInterruptStatus(base);

    /* Check the normal event. */
    if (0UL < intNormal)
    {
        /* Clear the normal event. */
        Cy_SD_Host_ClearNormalInterruptStatus(base, intNormal);
    }
}


/*******************************************************************************
* Function Name: Cy_SD_Host_VoltageCheck
****************************************************************************//**
*
*  resets the card (CMD0) and checks the voltage (CMD8).
*
* \param *base
*     The SD host registers structure pointer.
*
* \return The CMD8 valid flag (f8).
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SD_Host_VoltageCheck(SDHC_Type *base)
{
    cy_en_sd_host_status_t ret;
    bool                   f8Flag = false; /* The CMD8 valid flag. */
    uint32_t               response = 0UL;  /* The CMD response. */
    uint32_t               retry = CY_SD_HOST_VOLTAGE_CHECK_RETRY;

    while (retry > 0UL)
    {
        /* Reset Card (CMD0). */
        ret = Cy_SD_Host_OpsGoIdle(base);  /* The Idle state. */

        /* Software reset for the CMD line. */
        Cy_SD_Host_SoftwareReset(base, CY_SD_HOST_RESET_CMD_LINE);

        /* Voltage check (CMD8). */
        ret = Cy_SD_Host_OpsSendIfCond(base,
                                       CY_SD_HOST_CMD8_VHS_27_36 |
                                       CY_SD_HOST_CMD8_CHECK_PATTERN,
                                       false);

        /* Check the response. */
        (void)Cy_SD_Host_GetResponse(base,
                                     (uint32_t *)&response,
                                     false);

        /* Check the pattern. */
        if (CY_SD_HOST_CMD8_CHECK_PATTERN == (response &
                                              CY_SD_HOST_CMD8_PATTERN_MASK))
        {
            /* The pattern is valid. */
            f8Flag = true;
        }
        else if (CY_SD_HOST_VOLTAGE_CHECK_RETRY == retry)
        {
           /* CMD8 fails. Retry one more time */
        }
        else
        {
            /* The unusable card or the SDIO card. */
            ret = CY_SD_HOST_ERROR_UNUSABLE_CARD;
        }

        if ((CY_SD_HOST_ERROR_TIMEOUT == ret) || (f8Flag))
        {
            /* The pattern is valid or voltage mismatch (No response). */
            break;
        }

        retry--;
    }

    if (CY_SD_HOST_SUCCESS != ret)   /* The Idle state. */
    {
        /* Reset the error and the CMD line for the case of the SDIO card. */
        Cy_SD_Host_ErrorReset(base);
        Cy_SD_Host_NormalReset(base);
    }

    return f8Flag;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_IoOcr
****************************************************************************//**
*
*  Sends CMD5 to get IO OCR. Checks if IO is present (sdio),
*   if the memory is present (mpFlag) and if 1.8 signaling can be supported (s18aFlag).
*
* \param *base
*     The SD host registers structure pointer.
*
* \param lowVoltageSignaling
*     The lowVoltageSignaling flag.
*
* \param *s18aFlag
*     The S18A flag (1.8 signaling support).
*
* \param *sdioFlag
*     The IO flag (the number of IO functions).
*
* \param *mpFlag
*     The MEM flag (memory support).
*
* \param *ocrReg
*     The Operation Condition register (OCR).
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_IoOcr(SDHC_Type *base,
                                      bool lowVoltageSignaling,
                                      uint32_t *s18aFlag,
                                      uint32_t *sdioFlag,
                                      bool *mpFlag,
                                      uint32_t *ocrReg)
{
    cy_en_sd_host_status_t ret;
    uint32_t               retry;

    /* Get IO OCR (CMD5) */
    ret = Cy_SD_Host_OpsSdioSendOpCond(base, ocrReg, 0UL);

    /* Get the number of IO functions. */
    *sdioFlag = *ocrReg & CY_SD_HOST_CMD5_IO_NUM_MASK;

    if (0UL < *sdioFlag)
    {
        if (true == lowVoltageSignaling)
        {
            /* Set the OCR to change the signal
            * voltage to 1.8 V for the UHS-I mode.
            */
            *ocrReg = (*ocrReg & CY_SD_HOST_IO_OCR_MASK) |
                           CY_SD_HOST_ACMD41_S18R;
        }

        retry = CY_SD_HOST_RETRY_TIME;
        while (retry > 0UL)
        {
            /* Set S18R and the voltage window in IO OCR (CMD5). */
            ret = Cy_SD_Host_OpsSdioSendOpCond(base,
                                              ocrReg,
                                              *ocrReg);

            /* Check the IO power up status. */
            if (CY_SD_HOST_SUCCESS == ret)
            {
                if (CY_SD_HOST_IO_OCR_C == (*ocrReg & CY_SD_HOST_IO_OCR_C))
                {
                    /* The SDIO card supports 1.8 signaling. */
                    *s18aFlag = 1UL;
                }

                if(CY_SD_HOST_CMD5_MP_MASK == (*ocrReg & CY_SD_HOST_CMD5_MP_MASK))
                {
                    /* MP = 1. (The memory is supported.) */
                    *mpFlag = true;
                }

                /* IO > 0. */
                break;
            }

            Cy_SysLib_DelayUs(CY_SD_HOST_SDIO_CMD5_TIMEOUT_MS); /* 1 sec timeout. */
            retry--;
        }

        if (CY_SD_HOST_SUCCESS != ret)
        {
            /* IO = 0. */
            *sdioFlag = 0UL;
        }
    }
    else
    {
        /* Software reset for the DAT line. */
        Cy_SD_Host_SoftwareReset(base, CY_SD_HOST_RESET_DATALINE);

        /* IO = 0. We have the SD memory card. Reset errors. */
        Cy_SD_Host_ErrorReset(base);

    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SdOcr
****************************************************************************//**
*
*  Sends ACMD41 to get SD OCR.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param lowVoltageSignaling
*     The lowVoltageSignaling flag.
*
* \param *s18aFlag
*     The S18A flag (1.8 signaling support).
*
* \param *mpFlag
*     The MEM flag (memory support).
*
* \param f8Flag
*     The CMD8 flag.
*
* \param *ocrReg
*     The Operation Condition register (OCR).
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_sd_host_status_t Cy_SD_Host_SdOcr(SDHC_Type *base,
                                      bool lowVoltageSignaling,
                                      uint32_t *s18aFlag,
                                      bool *mpFlag,
                                      bool f8Flag,
                                      uint32_t *ocrReg,
                                      cy_stc_sd_host_context_t *context)
{
    cy_en_sd_host_status_t ret;
    uint32_t               response = 0UL;  /* The CMD response. */
    uint32_t               retry;
    uint32_t               cmdArgument;

    /* Get OCR (ACMD41). The voltage window = 0. */
    ret = Cy_SD_Host_OpsSdSendOpCond(base,
                                     ocrReg,
                                     0x00000000UL,
                                     context);

    if (CY_SD_HOST_SUCCESS == ret)
    {
        /* Set the voltage window from 2.7 to 3.6 V.  */
        cmdArgument = CY_SD_HOST_ACMD41_VOLTAGE_MASK;

        if (f8Flag)
        {
            /* Set the SDHC supported bit.*/
            cmdArgument |= CY_SD_HOST_ACMD41_HCS;

            if (true == lowVoltageSignaling)
            {
                /* Set the 1.8 V request bit.*/
                cmdArgument |= CY_SD_HOST_ACMD41_S18R;
            }
        }

        /* Set OCR (ACMD41). */
        retry = CY_SD_HOST_RETRY_TIME;
        while (retry > 0UL)
        {
            ret = Cy_SD_Host_OpsSdSendOpCond(base,
                                             ocrReg,
                                             cmdArgument,
                                             context);
            if (CY_SD_HOST_SUCCESS == ret)
            {
                break;
            }
            Cy_SysLib_DelayUs(CY_SD_HOST_ACMD41_TIMEOUT_MS);
            retry--;
        }

        /* Check the response. */
        (void)Cy_SD_Host_GetResponse(base,
                                    (uint32_t *)&response,
                                    false);

        if (0UL == (response & CY_SD_HOST_OCR_CAPACITY_MASK))
        {
            /* The SDSC card. */
            context->cardCapacity = CY_SD_HOST_SDSC;
        }

        /* Check S18A. */
        if (CY_SD_HOST_OCR_S18A == (response &
                                    CY_SD_HOST_OCR_S18A))
        {
            /* The SD card supports the 1.8 signaling. */
            *s18aFlag |= 1UL;
        }

        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* MP = 1. (The memory is supported.) */
            *mpFlag = true;
        }
        else
        {
            /* MP = 0. (The memory is not supported.) */
            *mpFlag = false;
        }
    }
    else if (false == f8Flag)
    {
        /* Not a SD card */
        ret = CY_SD_HOST_ERROR_UNUSABLE_CARD;
        context->cardType = CY_SD_HOST_UNUSABLE;
    }
    else
    {
        /* The card is not present or busy */
    }

    Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_Enable
****************************************************************************//**
*
*  Enables the SD host block.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
void Cy_SD_Host_Enable(SDHC_Type *base)
{
    uint32_t retry;

    /* Check for the NULL pointer */
    if (NULL != base)
    {
        /* Enable the SDHC block. */
        SDHC_WRAP_CTL(base) = _CLR_SET_FLD32U(SDHC_WRAP_CTL(base),
                                              SDHC_WRAP_CTL_ENABLE,
                                              1UL);

        retry = CY_SD_HOST_RETRY_TIME;

        /* Enable the Internal clock. */
        SDHC_CORE_CLK_CTRL_R(base) = (uint16_t)_CLR_SET_FLD16U(SDHC_CORE_CLK_CTRL_R(base),
                                                               SDHC_CORE_CLK_CTRL_R_INTERNAL_CLK_EN,
                                                               1UL);

        while((true != _FLD2BOOL(SDHC_CORE_CLK_CTRL_R_INTERNAL_CLK_STABLE, SDHC_CORE_CLK_CTRL_R(base)))
              && (retry > 0UL))
        {
            /* Wait for the stable Internal Clock . */
            Cy_SysLib_DelayUs(CY_SD_HOST_INT_CLK_STABLE_TIMEOUT_MS);
            retry--;
        }
    }
}


/*******************************************************************************
* Function Name: Cy_SD_Host_Disable
****************************************************************************//**
*
*  Disables the SD host block.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
void Cy_SD_Host_Disable(SDHC_Type *base)
{
    /* Check for the NULL pointer */
    if (NULL != base)
    {
        Cy_SD_Host_DisableSdClk(base);

        /* Disable the Internal clock. */
        SDHC_CORE_CLK_CTRL_R(base) = (uint16_t)_CLR_SET_FLD16U(SDHC_CORE_CLK_CTRL_R(base),
                                        SDHC_CORE_CLK_CTRL_R_INTERNAL_CLK_EN,
                                        0UL);

        /* Disable the SDHC block. */
        SDHC_WRAP_CTL(base) = _CLR_SET_FLD32U(SDHC_WRAP_CTL(base),
                                        SDHC_WRAP_CTL_ENABLE,
                                        0UL);
    }
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SetSdClkDiv
****************************************************************************//**
*
*  Changes the speed of the SD bus. This function should be called along
*  with \ref Cy_SD_Host_SetHostSpeedMode to configure the bus correctly.
*
* \note
*  The divider is clocked from the CLK_HF clock (100 MHz). To determine
*  the SD bus speed divide the clock CLK_HF by the divider value passed
*  in this function. The divider value is 2*clkDiv.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param clkDiv
*     The clock divider for the SD clock.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_SetSdClkDiv(SDHC_Type *base, uint16_t clkDiv)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;

    /* Check for the NULL pointer */
    if (NULL != base)
    {
        SDHC_CORE_CLK_CTRL_R(base) = (uint16_t)(((uint32_t)SDHC_CORE_CLK_CTRL_R(base) &
                                                ~(SDHC_CORE_CLK_CTRL_R_FREQ_SEL_Msk |            /* Clear the first LSB 8 bits */
                                                  SDHC_CORE_CLK_CTRL_R_UPPER_FREQ_SEL_Msk)) |    /* Clear the upper 2 bits */
        _VAL2FLD(SDHC_CORE_CLK_CTRL_R_FREQ_SEL, ((uint32_t)clkDiv & CY_SD_HOST_FREQ_SEL_MSK)) |             /* Set the first LSB 8 bits */
        _VAL2FLD(SDHC_CORE_CLK_CTRL_R_UPPER_FREQ_SEL, ((uint32_t)clkDiv >> CY_SD_HOST_UPPER_FREQ_SEL_POS))); /* Set the upper 2 bits */

        /* Wait for at least 3 card clock periods */
        Cy_SysLib_DelayUs(CY_SD_HOST_3_PERIODS_US);

        ret = CY_SD_HOST_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_IsWpSet
****************************************************************************//**
*
*  Returns the state of the write protect switch on the SD card.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return bool
*     true - the write protect is set, false - the write protect is not set.
*
*******************************************************************************/
__WEAK bool Cy_SD_Host_IsWpSet(SDHC_Type const *base)
{
    return _FLD2BOOL(SDHC_CORE_PSTATE_REG_WR_PROTECT_SW_LVL, SDHC_CORE_PSTATE_REG(base));
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SetHostBusWidth
****************************************************************************//**
*
*  Only changes the bus width on the host side.
*  It doesn't change the bus width on the card side.
*  To change the bus width on the card, call Cy_SD_Host_SetBusWidth().
*
* \param *base
*     The SD host registers structure pointer.
*
* \param width
*     The width of the data bus.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_SetHostBusWidth(SDHC_Type *base,
                                                  cy_en_sd_host_bus_width_t width)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;

    /* Check for the NULL pointer */
    if (NULL != base)
    {
        SDHC_CORE_HOST_CTRL1_R(base) = (uint8_t)(((uint32_t)SDHC_CORE_HOST_CTRL1_R(base) &
                                               ~(SDHC_CORE_HOST_CTRL1_R_EXT_DAT_XFER_Msk |
                                                 SDHC_CORE_HOST_CTRL1_R_DAT_XFER_WIDTH_Msk)) |
                                        (_BOOL2FLD(SDHC_CORE_HOST_CTRL1_R_EXT_DAT_XFER, (CY_SD_HOST_BUS_WIDTH_8_BIT == width)) |
                                         _BOOL2FLD(SDHC_CORE_HOST_CTRL1_R_DAT_XFER_WIDTH, (CY_SD_HOST_BUS_WIDTH_4_BIT == width))));

        ret = CY_SD_HOST_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SetHostSpeedMode
****************************************************************************//**
*
*  Only updates the host register to indicate bus speed mode and the general
*  purpose output register to select card clock input and output delay.
*  This function doesn't change the speed on the bus, or change anything
*  in the card.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param speedMode
*     Bus Speed mode.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_SetHostSpeedMode(SDHC_Type *base,
                                                  cy_en_sd_host_bus_speed_mode_t speedMode)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_SUCCESS;
    uint32_t               inDelay = 0UL;
    uint32_t               outDelay = 0UL;
    uint32_t               ultraHighSpeed = 0UL;

    /* Check for the NULL pointer */
    if (NULL != base)
    {
        /* UHS Mode/eMMC Speed Mode Select */
        switch (speedMode)
        {
            case CY_SD_HOST_BUS_SPEED_EMMC_LEGACY:
            case CY_SD_HOST_BUS_SPEED_DEFAULT:
            case CY_SD_HOST_BUS_SPEED_SDR12_5:
                ultraHighSpeed = CY_SD_HOST_SDR12_SPEED; /* Max clock = 25 MHz */
                break;
            case CY_SD_HOST_BUS_SPEED_EMMC_HIGHSPEED_SDR:
            case CY_SD_HOST_BUS_SPEED_SDR25:
            case CY_SD_HOST_BUS_SPEED_HIGHSPEED:
                ultraHighSpeed = CY_SD_HOST_SDR25_SPEED; /* Max clock = 50 MHz */
                break;
            case CY_SD_HOST_BUS_SPEED_SDR50:
                ultraHighSpeed = CY_SD_HOST_SDR50_SPEED; /* Max clock = 100 MHz */
                break;
            case CY_SD_HOST_BUS_SPEED_DDR50:
                ultraHighSpeed = CY_SD_HOST_DDR50_SPEED; /* Max clock = 50 MHz */
                break;
            default:
                ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                break;
        }

        /* Card clock output delay select */
         switch (speedMode)
         {
             case CY_SD_HOST_BUS_SPEED_EMMC_LEGACY:
             case CY_SD_HOST_BUS_SPEED_DEFAULT:
             case CY_SD_HOST_BUS_SPEED_SDR12_5:
             case CY_SD_HOST_BUS_SPEED_HIGHSPEED:
                 outDelay = CY_SD_HOST_SDR12_OUT_DELAY;
                 break;
             case CY_SD_HOST_BUS_SPEED_EMMC_HIGHSPEED_SDR:
             case CY_SD_HOST_BUS_SPEED_SDR25:
             case CY_SD_HOST_BUS_SPEED_SDR50:
                 outDelay = CY_SD_HOST_SDR25_OUT_DELAY;
                 break;
             case CY_SD_HOST_BUS_SPEED_DDR50:
                 outDelay = CY_SD_HOST_DDR50_OUT_DELAY;
                 break;
             default:
                 ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                 break;
         }

         /* Card clock input delay select */
         switch (speedMode)
         {
             case CY_SD_HOST_BUS_SPEED_EMMC_LEGACY:
             case CY_SD_HOST_BUS_SPEED_DEFAULT:
             case CY_SD_HOST_BUS_SPEED_SDR12_5:
                inDelay = CY_SD_HOST_SDR12_IN_DELAY;
                 break;
             case CY_SD_HOST_BUS_SPEED_SDR25:
             case CY_SD_HOST_BUS_SPEED_SDR50:
                 inDelay = CY_SD_HOST_SDR25_IN_DELAY;
                 break;
             case CY_SD_HOST_BUS_SPEED_HIGHSPEED:
             case CY_SD_HOST_BUS_SPEED_EMMC_HIGHSPEED_SDR:
                 inDelay = CY_SD_HOST_HIGH_SPEED_IN_DELAY;
                 break;
             case CY_SD_HOST_BUS_SPEED_DDR50:
                 inDelay = CY_SD_HOST_DDR50_IN_DELAY;
                 break;
             default:
                 ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                 break;
         }

        if (CY_SD_HOST_ERROR_INVALID_PARAMETER != ret)
        {
            SDHC_CORE_HOST_CTRL1_R(base) = (uint8_t)_CLR_SET_FLD8U(SDHC_CORE_HOST_CTRL1_R(base),
                                          SDHC_CORE_HOST_CTRL1_R_HIGH_SPEED_EN,
                                          ((CY_SD_HOST_BUS_SPEED_HIGHSPEED == speedMode) ? 1UL : 0UL));

            SDHC_CORE_HOST_CTRL2_R(base) = (uint16_t)_CLR_SET_FLD16U(SDHC_CORE_HOST_CTRL2_R(base),
                                          SDHC_CORE_HOST_CTRL2_R_UHS_MODE_SEL,
                                          ultraHighSpeed);

            SDHC_CORE_GP_OUT_R(base) = (uint16_t)_CLR_SET_FLD16U(SDHC_CORE_GP_OUT_R(base),
                                       SDHC_CORE_GP_OUT_R_CARD_CLOCK_IN_DLY,
                                           inDelay);

            SDHC_CORE_GP_OUT_R(base) = (uint16_t)_CLR_SET_FLD16U(SDHC_CORE_GP_OUT_R(base),
                                       SDHC_CORE_GP_OUT_R_CARD_CLOCK_OUT_DLY,
                                       outDelay);
        }
    }
    else
    {
        ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SetBusSpeedMode
****************************************************************************//**
*
*  Negotiates with the card to change the bus speed mode of the card
*  and the host. It doesn't change the SD clock frequency that must be done
*  separately.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param speedMode
*     Bus speed mode.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_SetBusSpeedMode(SDHC_Type *base,
                                                  cy_en_sd_host_bus_speed_mode_t speedMode,
                                                  cy_stc_sd_host_context_t const *context)
{
    cy_en_sd_host_status_t  ret = CY_SD_HOST_SUCCESS;
    uint32_t                highSpeedValue = CY_SD_HOST_DEFAULT_SPEED;
    uint32_t                cmdArgument = 0UL;
    uint32_t                response[CY_SD_HOST_RESPONSE_SIZE] = { 0UL };

    /* Check for the NULL pointer */
    if (NULL != base)
    {
        CY_ASSERT_L3(CY_SD_HOST_IS_SPEED_MODE_VALID(speedMode));

        /* 1. Does the card support memory? */
        if ((CY_SD_HOST_SD == context->cardType) ||
            (CY_SD_HOST_EMMC == context->cardType) ||
            (CY_SD_HOST_COMBO == context->cardType))
        {
            /* 2. Change Bus Speed Mode: Issue CMD6 with mode 1 */
            switch (speedMode)
            {
                case CY_SD_HOST_BUS_SPEED_EMMC_LEGACY:
                case CY_SD_HOST_BUS_SPEED_DEFAULT:
                case CY_SD_HOST_BUS_SPEED_SDR12_5:
                    highSpeedValue = CY_SD_HOST_SDR12_SPEED; /* Max clock = 25 MHz */
                    break;
                case CY_SD_HOST_BUS_SPEED_EMMC_HIGHSPEED_SDR:
                case CY_SD_HOST_BUS_SPEED_SDR25:
                case CY_SD_HOST_BUS_SPEED_HIGHSPEED:
                    highSpeedValue = CY_SD_HOST_SDR25_SPEED; /* Max clock = 50 MHz */
                    break;
                case CY_SD_HOST_BUS_SPEED_SDR50:
                    highSpeedValue = CY_SD_HOST_SDR50_SPEED; /* Max clock = 100 MHz */
                    break;
                case CY_SD_HOST_BUS_SPEED_DDR50:
                    highSpeedValue = CY_SD_HOST_DDR50_SPEED; /* Max clock = 50 MHz */
                    break;
                default:
                    ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                    break;
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                if ((CY_SD_HOST_SD == context->cardType) ||
                    (CY_SD_HOST_COMBO == context->cardType))
                {
                    /* Set the mode bit to 1 and select the default function */
                    cmdArgument = (1UL << CY_SD_HOST_SWITCH_FUNCTION_BIT);

                    /* Set the High Speed/SDR25 bit */
                    cmdArgument |= highSpeedValue & 0xFUL;

                    /* Send CMD6 and parse response */
                    ret = Cy_SD_Host_SdCardSwitchFunc(base, cmdArgument, context->cardType);
                }
                else
                {
                    cmdArgument = (CY_SD_HOST_EMMC_ACCESS_WRITE_BYTE << CY_SD_HOST_EMMC_CMD6_ACCESS_OFFSET) |
                                      (CY_SD_HOST_EMMC_HS_TIMING_ADDR << CY_SD_HOST_EMMC_CMD6_IDX_OFFSET) |
                                      (highSpeedValue << CY_SD_HOST_EMMC_CMD6_VALUE_OFFSET) |
                                      (0x0UL << CY_SD_HOST_EMMC_CMD6_CMD_SET_OFFSET);

                    /* Send CMD6 */
                    ret = Cy_SD_Host_OpsSwitchFunc(base, cmdArgument);
                }
            }
        }

        /* 5. Is SDIO Supported? */
        if ((CY_SD_HOST_SDIO == context->cardType) ||
            (CY_SD_HOST_COMBO == context->cardType))
        {
            /* 6. Change Bus Speed Mode: Set EHS or BSS[2:0] in CCCR */
            ret = Cy_SD_Host_OpsSendIoRwDirectCmd(base,
                                                  0UL,
                                                  0UL,
                                                  0UL,
                                                  CY_SD_HOST_CCCR_SPEED_CONTROL,
                                                  0UL);

            (void)Cy_SD_Host_GetResponse(base, (uint32_t *)response, false);

            /* Check the SHS bit - the High Speed mode operation ability  */
            if (0UL != (response[0] & CY_SD_HOST_CCCR_SPEED_SHS_MASK))
            {
                switch (speedMode)
                {
                    case CY_SD_HOST_BUS_SPEED_DEFAULT:
                    case CY_SD_HOST_BUS_SPEED_SDR12_5:
                        /* BSS0 = 0, BSS1 = 0  */
                        break;
                    case CY_SD_HOST_BUS_SPEED_SDR25:
                    case CY_SD_HOST_BUS_SPEED_HIGHSPEED:
                        response[0] |= CY_SD_HOST_CCCR_SPEED_BSS0_MASK;
                        break;
                    case CY_SD_HOST_BUS_SPEED_SDR50:
                        response[0] |= CY_SD_HOST_CCCR_SPEED_BSS1_MASK;
                        break;
                    case CY_SD_HOST_BUS_SPEED_DDR50:
                        response[0] |= CY_SD_HOST_CCCR_SPEED_BSS2_MASK;
                        break;
                    default:
                        ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                        break;
                }

                /* Set the EHS bit to enable High Speed mode */
                if (CY_SD_HOST_SUCCESS == ret)
                {
                    highSpeedValue = response[0] & (CY_SD_HOST_CCCR_SPEED_BSS0_MASK |
                                             CY_SD_HOST_CCCR_SPEED_BSS1_MASK |
                                             CY_SD_HOST_CCCR_SPEED_SHS_MASK);

                    ret = Cy_SD_Host_OpsSendIoRwDirectCmd(base,
                                                          1UL,
                                                          0UL,
                                                          0UL,
                                                          CY_SD_HOST_CCCR_SPEED_CONTROL,
                                                          response[0]);

                    (void)Cy_SD_Host_GetResponse(base, (uint32_t *)response, false);

                    response[0] = response[0] & (CY_SD_HOST_CCCR_SPEED_BSS0_MASK |
                                   CY_SD_HOST_CCCR_SPEED_BSS1_MASK |
                                   CY_SD_HOST_CCCR_SPEED_SHS_MASK);

                    if(highSpeedValue != response[0])
                    {
                        ret = CY_SD_HOST_ERROR_UNINITIALIZED;
                    }
                }
            }
            else
            {
                /* The card can operate in High Speed mode only. */
            }
        }

        /* 3 and 7. Bus Speed Mode changed Successfully  */
        if (CY_SD_HOST_SUCCESS == ret)
        {
            /* 4 and 8. Set the same bus speed mode in the host controller */
            ret = Cy_SD_Host_SetHostSpeedMode(base, speedMode);
        }
    }
    else
    {
        ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_FindBusSpeedMode
****************************************************************************//**
*
*  Negotiates with the card to find the highest supported bus speed mode
*  of the card.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param lowVoltageSignaling
*     Support for 1.8V signaling in card and host.
*
* \param cardType
*     The type of card.
*
* \note
*     This function is applicable only for \ref CY_SD_HOST_SD &
*     \ref CY_SD_HOST_COMBO card types
*
* \return \ref cy_en_sd_host_bus_speed_mode_t
*
*******************************************************************************/
static cy_en_sd_host_bus_speed_mode_t Cy_SD_Host_FindBusSpeedMode(SDHC_Type *base,
                                                  bool lowVoltageSignaling,
                                                  cy_en_sd_host_card_type_t cardType)
{
    cy_stc_sd_host_cmd_config_t  cmd;
    cy_stc_sd_host_data_config_t dataConfig;
    uint32_t status[CY_SD_HOST_SWITCH_STATUS_LEN];
    cy_en_sd_host_status_t  ret = CY_SD_HOST_SUCCESS;
    cy_en_sd_host_bus_speed_mode_t speedMode = CY_SD_HOST_BUS_SPEED_DEFAULT;

    cmd.commandIndex    = CY_SD_HOST_SD_CMD6;
    cmd.commandArgument = 0x0UL;
    cmd.dataPresent     = true;
    cmd.enableAutoResponseErrorCheck = false;
    cmd.respType        = CY_SD_HOST_RESPONSE_LEN_48;
    cmd.enableCrcCheck  = true;
    cmd.enableIdxCheck  = true;
    cmd.cmdType         = CY_SD_HOST_CMD_NORMAL;

    dataConfig.blockSize           = CY_SD_HOST_SD_STATUS_BLOCKS;
    dataConfig.numberOfBlock       = 1UL;
    dataConfig.enableDma           = false;
    dataConfig.autoCommand         = CY_SD_HOST_AUTO_CMD_NONE;
    dataConfig.read                = true;
    dataConfig.data                = status;
    dataConfig.dataTimeout         = CY_SD_HOST_MAX_TIMEOUT;
    dataConfig.enableIntAtBlockGap = false;
    dataConfig.enReliableWrite     = false;

    /* Check for the NULL pointer */
    if (NULL != base)
    {
        if ((cardType == CY_SD_HOST_SD) || (cardType == CY_SD_HOST_COMBO))
        {
            (void)Cy_SD_Host_InitDataTransfer(base, &dataConfig);

            ret = Cy_SD_Host_SendCommand(base, &cmd);

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Wait for the Command Complete event. */
                ret = Cy_SD_Host_PollCmdComplete(base);
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Wait for the response on the DAT lines. */
                ret = Cy_SD_Host_CmdRxData(base, &dataConfig);
            }

            if (CY_SD_HOST_SUCCESS == ret)
            {
                /* Parse the response on DAT lines and assign bus.speed mode */
                if ((bool)(status[3] & 0x0000800UL)) /* Bit 404 refers to DDR50 support in 512 bit SD status */
                {
                    speedMode = CY_SD_HOST_BUS_SPEED_DDR50;
                }
                else if ((bool)(status[3] & 0x00002000UL))  /* Bit 402 refers to SDR50 support in 512 bit SD status */
                {
                    speedMode = CY_SD_HOST_BUS_SPEED_SDR50;
                }
                else if ((bool)(status[3] & 0x00004000UL))  /* Bit 401 refers to SDR25/High-Speed support in 512 bit SD status */
                {
                    if (lowVoltageSignaling)
                    {
                        speedMode = CY_SD_HOST_BUS_SPEED_SDR25;
                    }
                    else
                    {
                        speedMode = CY_SD_HOST_BUS_SPEED_HIGHSPEED;
                    }
                }
                else if ((bool)(status[3] & 0x00008000UL)) /* Bit 400 refers to SDR12_5/Default support in 512 bit SD status */
                {
                    if (lowVoltageSignaling)
                    {
                        speedMode = CY_SD_HOST_BUS_SPEED_SDR12_5;
                    }
                    else
                    {
                        speedMode = CY_SD_HOST_BUS_SPEED_DEFAULT;
                    }
                }
                else
                {
                    speedMode = CY_SD_HOST_BUS_SPEED_DEFAULT;
                }
            }

        Cy_SysLib_DelayUs(CY_SD_HOST_NCC_MIN_US);
        }
    }

    return speedMode;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SelBusVoltage
****************************************************************************//**
*
*  Negotiates with the SD card to change the bus signaling level to 1.8V.
*  After this function is called, the card is in the ready state.
*
* \note The host needs to change the regulator supplying voltage to
*       the VDDIO of the SD block in order to operate at 1.8V.
* \note This function changes RCA to 0 in the context. RCA in the context
*       should be updated (context.RCA = Cy_SD_Host_GetRca();)
*       when the card is in the Identification state.
* \note This function is applicable for SD cards only.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param enable18VSignal
*     If true, use the 1.8V signaling, false - use the 3.3V signaling.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
* If only the SD host functions which do not require context will be used, pass NULL
* as the pointer to the context.
*
* \return \ref cy_en_sd_host_status_t
*
* \note The SD card power supply should be disabled and initialized again when
*  this function returns CY_SD_HOST_ERROR_UNUSABLE_CARD.
*
* \note The dedicated io_volt_sel pin is used to change the regulator supplying
* voltage to the VDDIO of the SD block in order to operate at 1.8V. To configure
* the custom IO pin in order to control (using the GPIO driver) the regulator
* supplying voltage, the user must implement weak Cy_SD_Host_ChangeIoVoltage().
* Also, this function must set the SIGNALING_EN bit of the SDHC_CORE_HOST_CTRL2_R
* register when ioVoltage = CY_SD_HOST_IO_VOLT_1_8V.
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_SelBusVoltage(SDHC_Type *base,
                                                bool enable18VSignal,
                                                cy_stc_sd_host_context_t *context)
{
    cy_en_sd_host_status_t ret;
    uint32_t               ocrReg; /* The Operation Condition register. */
    uint32_t               s18aFlag = 0UL; /* The S18A flag. */
    bool                   f8Flag = false; /* The CMD8 flag. */
    bool                   mpFlag = false; /* The MEM flag. */

    context->RCA = 0UL;

    /* Send CMD0 and CMD8 commands. */
    f8Flag = Cy_SD_Host_VoltageCheck(base);

    /* Clear the insert event */
    Cy_SD_Host_NormalReset(base);

    /* Send ACMD41 */
    ret = Cy_SD_Host_SdOcr(base,
                           enable18VSignal,
                           &s18aFlag,
                           &mpFlag,
                           f8Flag,
                           &ocrReg,
                           context);

    if ((CY_SD_HOST_SUCCESS == ret) && (enable18VSignal) && (1UL == s18aFlag))
    {
        /* Voltage switch (CMD11). */
        ret = Cy_SD_Host_OpsVoltageSwitch(base, context);
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_EnableCardVoltage
****************************************************************************//**
*
*  Sets the card_if_pwr_en pin high.
*  This pin can be used to enable a voltage regulator used to power the card.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
__WEAK void Cy_SD_Host_EnableCardVoltage(SDHC_Type *base)
{
    SDHC_CORE_PWR_CTRL_R(base) = _CLR_SET_FLD8U(SDHC_CORE_PWR_CTRL_R(base), SDHC_CORE_PWR_CTRL_R_SD_BUS_PWR_VDD1, 1UL);
}


/*******************************************************************************
* Function Name: Cy_SD_Host_DisableCardVoltage
****************************************************************************//**
*
*  Sets the card_if_pwr_en pin low.
*  This pin can be used to disable a voltage regulator used to power the card.
*
* \param *base
*     The SD host registers structure pointer.
*
*******************************************************************************/
__WEAK void Cy_SD_Host_DisableCardVoltage(SDHC_Type *base)
{

    SDHC_CORE_PWR_CTRL_R(base) = _CLR_SET_FLD8U(SDHC_CORE_PWR_CTRL_R(base), SDHC_CORE_PWR_CTRL_R_SD_BUS_PWR_VDD1, 0UL);
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetResponse
****************************************************************************//**
*
* This function reads the response register from the last completed command.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *responsePtr
*     The pointer to response data.
*
* \param largeResponse
*     If true, the response is 136 bits, false - 32 bits.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t  Cy_SD_Host_GetResponse(SDHC_Type const *base,
                                               uint32_t *responsePtr,
                                               bool largeResponse)
{
    cy_en_sd_host_status_t  ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    volatile uint32_t const *responseBaseAddr;
    uint8_t                 i;
    uint8_t                 responseLength = (true == largeResponse) ? CY_SD_HOST_RESPONSE_SIZE : 1U;

    if ((NULL != base) &&
        (NULL != responsePtr))
    {
        /* Get the Response Register 0 address */
        responseBaseAddr = &SDHC_CORE_RESP01_R(base);

        /* Read the largeResponse Response registers values */
        for (i = 0U; i < responseLength; i++)
        {
            *responsePtr = *responseBaseAddr;
            responsePtr++;
            responseBaseAddr++;
        }

        ret = CY_SD_HOST_SUCCESS;
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_InitDataTransfer
****************************************************************************//**
*
*  Initializes the SD block for a data transfer. It does not start a transfer.
*  To start a transfer call Cy_SD_Host_SendCommand() after calling this function.
*  If DMA is not used for data transfer, the buffer needs to be filled
*  with data first if this is a write.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param dataConfig
*     The pointer to the data transfer configuration structure.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_InitDataTransfer(SDHC_Type *base,
                                                   cy_stc_sd_host_data_config_t const *dataConfig)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_SUCCESS;
    uint32_t               dmaMode;
    uint32_t               transferMode;

    if ((NULL != base) && (NULL != dataConfig) && (NULL != dataConfig->data))
    {
        CY_ASSERT_L3(CY_SD_HOST_IS_AUTO_CMD_VALID(dataConfig->autoCommand));
        CY_ASSERT_L2(CY_SD_HOST_IS_TIMEOUT_VALID(dataConfig->dataTimeout));
        CY_ASSERT_L2(CY_SD_HOST_IS_BLK_SIZE_VALID(dataConfig->blockSize, _FLD2VAL(SDHC_CORE_HOST_CTRL2_R_UHS_MODE_SEL, SDHC_CORE_HOST_CTRL2_R(base))));

        dmaMode = _FLD2VAL(SDHC_CORE_HOST_CTRL1_R_DMA_SEL, SDHC_CORE_HOST_CTRL1_R(base));

        SDHC_CORE_BLOCKSIZE_R(base) = 0U;
        SDHC_CORE_XFER_MODE_R(base) = 0U;

        if (((uint32_t)CY_SD_HOST_DMA_ADMA2_ADMA3 == dmaMode) && (dataConfig->enableDma))
        {
            /* ADMA3 Integrated Descriptor Address. */
            SDHC_CORE_ADMA_ID_LOW_R(base) = (uint32_t)dataConfig->data;
        }
        else
        {
            if (dataConfig->enableDma)
            {
                /* Set the ADMA descriptor table. */
                if ((uint32_t)CY_SD_HOST_DMA_SDMA == dmaMode)
                {
                    /* Set 512K bytes SDMA Buffer Boundary. */
                    SDHC_CORE_BLOCKSIZE_R(base) = _CLR_SET_FLD16U(SDHC_CORE_BLOCKSIZE_R(base),
                                                  SDHC_CORE_BLOCKSIZE_R_SDMA_BUF_BDARY,
                                                  CY_SD_HOST_SDMA_BUF_BYTES_512K);

                    if (true == _FLD2BOOL(SDHC_CORE_HOST_CTRL2_R_HOST_VER4_ENABLE, SDHC_CORE_HOST_CTRL2_R(base)))
                    {
                        /* The data address. */
                        SDHC_CORE_ADMA_SA_LOW_R(base) = (uint32_t)dataConfig->data;

                        /* Set the block count. */
                        SDHC_CORE_SDMASA_R(base) = dataConfig->numberOfBlock;
                    }
                    else
                    {
                        /* The data address. */
                        SDHC_CORE_SDMASA_R(base) = (uint32_t)dataConfig->data;
                    }
                }
                else
                {
                    /* The data address. */
                    SDHC_CORE_ADMA_SA_LOW_R(base) = (uint32_t)dataConfig->data;
                }
            }
            else
            {
                /* Set the block count. */
                SDHC_CORE_SDMASA_R(base) = dataConfig->numberOfBlock;
            }

            /* Set the block size. */
            SDHC_CORE_BLOCKSIZE_R(base) = _CLR_SET_FLD16U(SDHC_CORE_BLOCKSIZE_R(base),
                                          SDHC_CORE_BLOCKSIZE_R_XFER_BLOCK_SIZE,
                                          dataConfig->blockSize);

            /* Set the block count. */
            SDHC_CORE_BLOCKCOUNT_R(base) = (uint16_t)dataConfig->numberOfBlock;


            /* Set a multi- or single-block transfer.*/
            transferMode = _BOOL2FLD(SDHC_CORE_XFER_MODE_R_MULTI_BLK_SEL, (1U < dataConfig->numberOfBlock));

            /* Set the data transfer direction. */
            transferMode |= _BOOL2FLD(SDHC_CORE_XFER_MODE_R_DATA_XFER_DIR, dataConfig->read);

            /* Set the block count enable. */
            transferMode |= SDHC_CORE_XFER_MODE_R_BLOCK_COUNT_ENABLE_Msk;

            /* Enable the DMA or not. */
            transferMode |= _BOOL2FLD(SDHC_CORE_XFER_MODE_R_DMA_ENABLE, dataConfig->enableDma);

            /* Set an interrupt at the block gap. */
            SDHC_CORE_BGAP_CTRL_R(base) = (uint8_t)_CLR_SET_FLD8U(SDHC_CORE_BGAP_CTRL_R(base),
                                          SDHC_CORE_BGAP_CTRL_R_INT_AT_BGAP,
                                          ((dataConfig->enableIntAtBlockGap) ? 1UL : 0UL));

            /* Set the data timeout (Base clock*2^27). */
            SDHC_CORE_TOUT_CTRL_R(base) = _CLR_SET_FLD8U(SDHC_CORE_TOUT_CTRL_R(base),
                                                    SDHC_CORE_TOUT_CTRL_R_TOUT_CNT,
                                                    dataConfig->dataTimeout);

            /* The reliable write setting. */
            if (dataConfig->enReliableWrite)
            {
                ret = Cy_SD_Host_OpsSetBlockCount(base,
                                                  dataConfig->enReliableWrite,
                                                  dataConfig->numberOfBlock);
            }

            /* The auto-command setting. */
            switch (dataConfig->autoCommand)
            {
                case CY_SD_HOST_AUTO_CMD_NONE:
                    transferMode |= _VAL2FLD(SDHC_CORE_XFER_MODE_R_AUTO_CMD_ENABLE, 0UL);
                    break;
                case CY_SD_HOST_AUTO_CMD_12:
                    transferMode |= _VAL2FLD(SDHC_CORE_XFER_MODE_R_AUTO_CMD_ENABLE, 1UL);
                    break;
                case CY_SD_HOST_AUTO_CMD_23:
                    transferMode |= _VAL2FLD(SDHC_CORE_XFER_MODE_R_AUTO_CMD_ENABLE, 2UL);
                    break;
                case CY_SD_HOST_AUTO_CMD_AUTO:
                    transferMode |= _VAL2FLD(SDHC_CORE_XFER_MODE_R_AUTO_CMD_ENABLE, 3UL);
                    break;
                default:
                    ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
                    break;
            }

            SDHC_CORE_XFER_MODE_R(base) = (uint16_t)transferMode;
        }
    }

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_ChangeIoVoltage
****************************************************************************//**
*
*  Changes the logic level on the sd_io_volt_sel line. It assumes that
*  this line is used to control a regulator connected to the VDDIO of the PSoC.
*  This regulator allows for switching between the 3.3V and 1.8V signaling.
*
* \note The dedicated io_volt_sel pin is used to change the regulator supplying
* voltage to the VDDIO of the SD block in order to operate at 1.8V. To configure
* the custom IO pin in order to control (using the GPIO driver) the regulator
* supplying voltage, the user must implement weak Cy_SD_Host_ChangeIoVoltage().
* Also, this function must set the SIGNALING_EN bit of the SDHC_CORE_HOST_CTRL2_R
* register when ioVoltage = CY_SD_HOST_IO_VOLT_1_8V.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param ioVoltage
*     The voltage for IO.
*
*******************************************************************************/
__WEAK void Cy_SD_Host_ChangeIoVoltage(SDHC_Type *base, cy_en_sd_host_io_voltage_t ioVoltage)
{
    /* Set the 1.8V signaling enable. */
    SDHC_CORE_HOST_CTRL2_R(base) = _CLR_SET_FLD16U(SDHC_CORE_HOST_CTRL2_R(base),
                                              SDHC_CORE_HOST_CTRL2_R_SIGNALING_EN,
                                              (CY_SD_HOST_IO_VOLT_1_8V == ioVoltage) ? 1UL : 0UL);
}


/*******************************************************************************
* Function Name: Cy_SD_Host_IsCardConnected
****************************************************************************//**
*
*  Checks to see if a card is currently connected.
*
* \note You can use any GPIO custom pin for Card Detect. Add the SD Host driver
* Cy_SD_Host_IsCardConnected() function with the __WEAK type to your code.
* This function could read the value from any GPIO pin and return true when
* the card is connected.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return bool
*     true - the card is connected, false - the card is removed (not connected).
*
*******************************************************************************/
__WEAK bool Cy_SD_Host_IsCardConnected(SDHC_Type const *base)
{
    while(true != _FLD2BOOL(SDHC_CORE_PSTATE_REG_CARD_STABLE, SDHC_CORE_PSTATE_REG(base)))
    {
        /* Wait until the card is stable. */
    }

    return _FLD2BOOL(SDHC_CORE_PSTATE_REG_CARD_INSERTED, SDHC_CORE_PSTATE_REG(base));
}


/*******************************************************************************
* Function Name: Cy_SD_Host_SoftwareReset
****************************************************************************//**
*
*  Issues the software reset command to the SD card.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param reset
*     The reset type.
*
*******************************************************************************/
void Cy_SD_Host_SoftwareReset(SDHC_Type *base,
                              cy_en_sd_host_reset_t reset)
{
    switch (reset)
    {
        case CY_SD_HOST_RESET_DATALINE:
            SDHC_CORE_SW_RST_R(base) = (uint8_t)_VAL2FLD(SDHC_CORE_SW_RST_R_SW_RST_DAT, 1UL);

            /* Wait for at least 3 card clock periods */
            Cy_SysLib_DelayUs(CY_SD_HOST_3_PERIODS_US);

            while(false != _FLD2BOOL(SDHC_CORE_SW_RST_R_SW_RST_DAT, SDHC_CORE_SW_RST_R(base)))
            {
                /* Wait until the reset completes. */
            }

            break;
        case CY_SD_HOST_RESET_CMD_LINE:
            SDHC_CORE_SW_RST_R(base) = (uint8_t)_VAL2FLD(SDHC_CORE_SW_RST_R_SW_RST_CMD, 1UL);

            /* Wait for at least 3 card clock periods */
            Cy_SysLib_DelayUs(CY_SD_HOST_3_PERIODS_US);

            while(false != _FLD2BOOL(SDHC_CORE_SW_RST_R_SW_RST_CMD, SDHC_CORE_SW_RST_R(base)))
            {
                /* Wait until the reset completes. */
            }

            break;
        case CY_SD_HOST_RESET_ALL:

            SDHC_CORE_CLK_CTRL_R(base) = 0U;

            /* Wait for at least 3 card clock periods */
            Cy_SysLib_DelayUs(CY_SD_HOST_3_PERIODS_US);

            SDHC_CORE_SW_RST_R(base) = (uint8_t)_VAL2FLD(SDHC_CORE_SW_RST_R_SW_RST_ALL, 1UL);

            while(false != _FLD2BOOL(SDHC_CORE_SW_RST_R_SW_RST_ALL, SDHC_CORE_SW_RST_R(base)))
            {
                /* Wait until the reset completes. */
            }

            /* Enable the Internal clock. */
            SDHC_CORE_CLK_CTRL_R(base) = (uint16_t)_CLR_SET_FLD16U(SDHC_CORE_CLK_CTRL_R(base),
                                            SDHC_CORE_CLK_CTRL_R_INTERNAL_CLK_EN,
                                            1UL);

            while(true != _FLD2BOOL(SDHC_CORE_CLK_CTRL_R_INTERNAL_CLK_STABLE, SDHC_CORE_CLK_CTRL_R(base)))
            {
                /* Wait for the stable Internal Clock. */
            }

            break;
        default:
            /* Unknown Reset selection*/
            break;
    }
}


/*******************************************************************************
* Function Name: Cy_SD_Host_GetPresentState
****************************************************************************//**
*
*  Returns the values of the present state register.
*
* \param *base
*     The SD host registers structure pointer.
*
* \return The value of the present state register.
*
*******************************************************************************/
uint32_t Cy_SD_Host_GetPresentState(SDHC_Type const *base)
{
    uint32_t ret;

    ret = SDHC_CORE_PSTATE_REG(base);

    return ret;
}


/*******************************************************************************
* Function Name: Cy_SD_Host_DeepSleepCallback
****************************************************************************//**
*
* This function handles the transition of the SD Host into and out of
* Deep Sleep mode. It disables SD CLK before going to Deep Sleep mode and
* enables SD CLK after wake up from Deep Sleep mode.
* If the DAT line is active, or a read (write) transfer is being executed on
* the bus, the device cannot enter Deep Sleep mode.
*
* This function must be called during execution of \ref Cy_SysPm_CpuEnterDeepSleep.
* To do it, register this function as a callback before calling
* \ref Cy_SysPm_CpuEnterDeepSleep : specify \ref CY_SYSPM_DEEPSLEEP as the callback
* type and call \ref Cy_SysPm_RegisterCallback.
*
* \note When waking up from Deep Sleep, the SD Host driver requires up to 1 us
* for clock stabilization. By default the SD Host driver will wait this length
* of time on power up. The waiting loop is implemented in this function.
* If the application is time sensitive this delay can be overridden by the
* application by defining \ref CY_SD_HOST_CLK_RAMP_UP_TIME_US_WAKEUP.
* This allows the application to perform other operations while the clock
* is stabilizing in the background. However, the application must still make sure
* that the SD Host clock has had time to stabilize before attempting to use the
* SD card. The recommended way to override the value is to specify this as
* a custom define on the compiler command line. This can be done by appending
* the entry to the DEFINES variable in the application Makefile.
* Eg: DEFINES+=CY_SD_HOST_CLK_RAMP_UP_TIME_US_WAKEUP=40.
*
* \param callbackParams
* The pointer to the callback parameters structure
* \ref cy_stc_syspm_callback_params_t.
*
* \param mode
* Callback mode, see \ref cy_en_syspm_callback_mode_t
*
* \return
* \ref cy_en_syspm_status_t
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SD_Host_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams,
                                                  cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t ret = CY_SYSPM_FAIL;
    SDHC_Type *locBase = (SDHC_Type *) (callbackParams->base);

    switch(mode)
    {
        case CY_SYSPM_CHECK_READY:
        {
            /* Check DAT Line Active */
            uint32_t pState = Cy_SD_Host_GetPresentState(locBase);
            if ((CY_SD_HOST_DAT_LINE_ACTIVE != (pState & CY_SD_HOST_DAT_LINE_ACTIVE)) &&
                (CY_SD_HOST_CMD_CMD_INHIBIT_DAT != (pState & CY_SD_HOST_CMD_CMD_INHIBIT_DAT)))
            {
                ret = CY_SYSPM_SUCCESS;
            }
        }
        break;

        case CY_SYSPM_CHECK_FAIL:
        {
            ret = CY_SYSPM_SUCCESS;
        }
        break;

        case CY_SYSPM_BEFORE_TRANSITION:
        {
            /* Disable SD CLK before going to Deep Sleep mode */
            Cy_SD_Host_DisableSdClk(locBase);

            ret = CY_SYSPM_SUCCESS;
        }
        break;

        case CY_SYSPM_AFTER_TRANSITION:
        {
            /* Enable SD CLK after wake up from Deep Sleep mode */
            Cy_SD_Host_EnableSdClk(locBase);

            /* Wait for the stable CLK */
            Cy_SysLib_DelayUs(CY_SD_HOST_CLK_RAMP_UP_TIME_US_WAKEUP);

            ret = CY_SYSPM_SUCCESS;
        }
        break;

        default:
            /* Unknown state */
            break;
    }

    return (ret);
}

/*******************************************************************************
* Function Name: Cy_SD_Host_GetBlockCount
****************************************************************************//**
*
*  Returns the Block count in SD/eMMC Card.
*
* \param *base
*     The SD host registers structure pointer.
*
* \param *block_count
*     The pointer to store the block_count.
*
* \param context
* The pointer to the context structure \ref cy_stc_sd_host_context_t allocated
* by the user. The structure is used during the SD host operation for internal
* configuration and data retention. The user must not modify anything
* in this structure.
*
* \return \ref cy_en_sd_host_status_t
*
*******************************************************************************/
cy_en_sd_host_status_t Cy_SD_Host_GetBlockCount(SDHC_Type *base,
                                         uint32_t *block_count,
                                         cy_stc_sd_host_context_t *context)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_SUCCESS;

    /* Check for the NULL pointer */
    if ((NULL != base) && (NULL != block_count) && (NULL != context))
    {
        if ((CY_SD_HOST_SD == context->cardType) || (CY_SD_HOST_EMMC == context->cardType))
        {
            *block_count = context->maxSectorNum;
        }
    }
    else
    {
        ret = CY_SD_HOST_ERROR_INVALID_PARAMETER;
    }

    return ret;
}


CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.1');

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXSDHC */

/* [] END OF FILE */
