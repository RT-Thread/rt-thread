/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef SDHI_PRV_R_SDHI_PRIVATE_H
#define SDHI_PRV_R_SDHI_PRIVATE_H

/**********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SDHI_PRV_CSD_VERSION_1_0                        (0U)
#define SDHI_PRV_CSD_VERSION_2_0                        (1U) /* value of 1 is CSD 2.0 according to SD spec. */

#define SDHI_PRV_CMD_GO_IDLE_STATE                      (0U)
#define SDHI_PRV_CMD_SEND_OP_COND                       (1U)
#define SDHI_PRV_CMD_ALL_SEND_CID                       (2U)
#define SDHI_PRV_CMD_SEND_RELATIVE_ADDR                 (3U)
#define SDHI_PRV_CMD_SET_BUS_WIDTH                      (6U)
#define SDHI_PRV_CMD_SWITCH                             (6U)
#define SDHI_PRV_CMD_SEL_DES_CARD                       (7U)
#define SDHI_PRV_CMD_IF_COND                            (8U)
#define SDHI_PRV_CMD_SEND_CSD                           (9U)
#define SDHI_PRV_CMD_SET_BLOCKLEN                       (16U)
#define SDHI_PRV_CMD_READ_SINGLE_BLOCK                  (17U)
#define SDHI_PRV_CMD_READ_MULTIPLE_BLOCK                (18U)
#define SDHI_PRV_CMD_WRITE_SINGLE_BLOCK                 (24U)
#define SDHI_PRV_CMD_WRITE_MULTIPLE_BLOCK               (25U)
#define SDHI_PRV_CMD_ERASE_WR_BLK_START                 (32U)
#define SDHI_PRV_CMD_ERASE_WR_BLK_END                   (33U)
#define SDHI_PRV_CMD_TAG_ERASE_GROUP_START              (0x423U)
#define SDHI_PRV_CMD_TAG_ERASE_GROUP_END                (0x424U)
#define SDHI_PRV_CMD_ERASE                              (38U)
#define SDHI_PRV_CMD_SD_SEND_OP_COND                    (41U)
#define SDHI_PRV_CMD_IO_RW_DIRECT                       (52U)
#define SDHI_PRV_CMD_IO_READ_EXT_SINGLE_BLOCK           (0x1c35U)
#define SDHI_PRV_CMD_IO_EXT_MULTI_BLOCK                 (0x6000U)
#define SDHI_PRV_CMD_IO_WRITE_EXT_SINGLE_BLOCK          (0x0c35U)

#define SDHI_PRV_CMD_APP_CMD                            (55U)
#define SDHI_PRV_CMD_C_ACMD                             (1U << 6) /* APP Command */

#define SDHI_PRV_IF_COND_VOLTAGE                        (1U)
#define SDHI_PRV_IF_COND_CHECK_PATTERN                  (0xAAU)

#define SDHI_PRV_OCR_CAPACITY_HC                        (1U << 30)

#define SDHI_PRV_OCR_VDD_2_7_V                          (1U << 15)
#define SDHI_PRV_OCR_VDD_2_8_V                          (1U << 16)
#define SDHI_PRV_OCR_VDD_2_9_V                          (1U << 17)
#define SDHI_PRV_OCR_VDD_3_0_V                          (1U << 18)
#define SDHI_PRV_OCR_VDD_3_1_V                          (1U << 19)
#define SDHI_PRV_OCR_VDD_3_2_V                          (1U << 20)
#define SDHI_PRV_OCR_VDD_3_3_V                          (1U << 21)
#define SDHI_PRV_OCR_VDD_3_4_V                          (1U << 22)
#define SDHI_PRV_OCR_VDD_3_5_V                          (1U << 23)
#define SDHI_PRV_OCR_VDD_SUPPORTED                                                                       \
    (SDHI_PRV_OCR_VDD_2_7_V | SDHI_PRV_OCR_VDD_2_8_V | SDHI_PRV_OCR_VDD_2_9_V | SDHI_PRV_OCR_VDD_3_0_V | \
     SDHI_PRV_OCR_VDD_3_1_V |                                                                            \
     SDHI_PRV_OCR_VDD_3_2_V | SDHI_PRV_OCR_VDD_3_3_V | SDHI_PRV_OCR_VDD_3_4_V | SDHI_PRV_OCR_VDD_3_5_V)

/* SWITCH command argument's bit position */
#define SDHI_PRV_SWITCH_ACCESS_SHIFT                    (24U)
#define SDHI_PRV_SWITCH_INDEX_SHIFT                     (16U)
#define SDHI_PRV_SWITCH_VALUE_SHIFT                     (8U)

#define SDHI_PRV_EMMC_EXT_CSD_SIZE                      (512U)

/* Offsets */
#define SDHI_PRV_EMMC_EXT_CSD_HS_TIMING_OFFSET          (185U)
#define SDHI_PRV_EMMC_EXT_CSD_DEVICE_TYPE_OFFSET        (196U)
#define SDHI_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET          (212U)

/* Commands */
#define SDHI_PRV_EMMC_SWITCH_ACCESS_WRITE_BYTE          (3U)
#define SDHI_PRV_EMMC_HIGH_SPEED_52_MHZ_BIT             (2U)
#define SDHI_PRV_EMMC_HIGH_SPEED_MODE                   (((SDHI_PRV_EMMC_SWITCH_ACCESS_WRITE_BYTE << 24U) |  \
                                                          (SDHI_PRV_EMMC_EXT_CSD_HS_TIMING_OFFSET << 16U)) | \
                                                         (SDHI_PRV_EMMC_HIGH_SPEED_52_MHZ_BIT << 8U))

#define SDHI_PRV_SD_SWITCH_STATUS_SIZE                  (64U)
#define SDHI_PRV_SD_SWITCH_HIGH_SPEED_RESPONSE          (13U)
#define SDHI_PRV_SD_SWITCH_HIGH_SPEED_ERROR_RESPONSE    (16U)
#define SDHI_PRV_SD_SWITCH_HIGH_SPEED_ERROR             (0x0fU)
#define SDHI_PRV_SD_SWITCH_HIGH_SPEED_OK                (0x02U)

#define SDHI_PRV_EMMC_SEND_OP_COND                      (0x701U)
#define SDHI_PRV_EMMC_CMD_SWITCH_WBUSY                  (0x506U)      /* eMMC CMD6 switch command "with response busy" */
#define SDHI_PRV_EMMC_CMD_SEND_EXT_CSD                  (0x1C08U)     /* CMD 8, read data */
#define SDHI_PRV_EMMC_DEFAULT_CLOCK_RATE                (26000000U)   /* 26 MHz */
#define SDHI_PRV_EMMC_HIGH_SPEED_CLOCK_RATE             (52000000U)   /* 52 MHz */
#define SDHI_PRV_SD_HIGH_SPEED_MODE_SWITCH              (0x80FFFFF1U) /* set SD high speed */
#define SDHI_PRV_SD_DEFAULT_CLOCK_RATE                  (25000000U)   /* 25 MHz */
#define SDHI_PRV_SD_HIGH_SPEED_CLOCK_RATE               (50000000U)   /* 50 MHz */

#define SDHI_PRV_EMMC_ERASE_ARGUMENT_TRIM               (1U)

#define SDHI_PRV_CSD_CID_SERIAL_NUMBER_BITS             (32)
#define SDHI_PRV_CSD_CID_PRODUCT_NAME_BITS              (40)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_sdmmc_priv_sd_state
{
    SDMMC_PRIV_SD_STATE_IDLE,
    SDMMC_PRIV_SD_STATE_READY,
    SDMMC_PRIV_SD_STATE_IDENT,
    SDMMC_PRIV_SD_STATE_STBY,
    SDMMC_PRIV_SD_STATE_TRANSFER,
    SDMMC_PRIV_SD_STATE_DATA,
    SDMMC_PRIV_SD_STATE_RCV,
    SDMMC_PRIV_SD_STATE_PROG,
    SDMMC_PRIV_SD_STATE_DIS,
    SDMMC_PRIV_SD_STATE_RSVD9,
    SDMMC_PRIV_SD_STATE_RSVD10,
    SDMMC_PRIV_SD_STATE_RSVD11,
    SDMMC_PRIV_SD_STATE_RSVD12,
    SDMMC_PRIV_SD_STATE_RSVD13,
    SDMMC_PRIV_SD_STATE_RSVD14,
    SDMMC_PRIV_SD_STATE_RSVD15
} sdmmc_priv_sd_state_t;

/** SDMMC card specific data */
typedef struct st_sdmmc_priv_csd_reg
{
    union
    {
        uint8_t array[16];

        /* All structures in this union must be packed since some bitfields span more than one 32-bit word. */
#if defined(__ICCARM__)
        __packed struct
#elif defined(__GNUC__)
        struct __attribute__((__packed__))
#endif
        {
            volatile uint32_t sdrsp10;
            volatile uint32_t sdrsp32;
            volatile uint32_t sdrsp54;
            volatile uint32_t sdrsp76;
        } reg;

        /* All structures in this union must be packed since some bitfields span more than one 32-bit word. */
#if defined(__ICCARM__)
        __packed struct
#elif defined(__GNUC__)
        struct __attribute__((__packed__))
#endif
        {
            uint32_t reserved_8         : 2;  ///< [9:8]
            uint32_t file_format        : 2;  ///< [11:10] file format
            uint32_t tmp_write_protect  : 1;  ///< [12]    temporary write protection
            uint32_t perm_write_protect : 1;  ///< [13]    permanent write protection
            uint32_t copy               : 1;  ///< [14]    copy flag
            uint32_t file_format_grp    : 1;  ///< [15]    file format group
            uint32_t reserved_20        : 5;  ///< [16-20]
            uint32_t write_bl_partial   : 1;  ///< [21]    partial blocks for write allowed
            uint32_t write_bl_len       : 4;  ///< [25:22] max. write data block length
            uint32_t r2w_factor         : 3;  ///< [28:26] write speed factor
            uint32_t reserved_29        : 2;  ///< [30:29]
            uint32_t wp_grp_enable      : 1;  ///< [31]    write protect group enable
            uint32_t wp_grp_size        : 7;  ///< [38:32] write protect group size
            uint32_t sector_size        : 7;  ///< [45:39] erase sector size
            uint32_t erase_blk_en       : 1;  ///< [46]    erase single block enable
            uint32_t c_size_mult        : 3;  ///< [49:47] device size multiplier*/
            uint32_t vdd_w_curr_max     : 3;  ///< [52:50] max. write current for vdd max
            uint32_t vdd_w_curr_min     : 3;  ///< [55:53] max. write current for vdd min
            uint32_t vdd_r_curr_max     : 3;  ///< [58:56] max. read current for vdd max
            uint32_t vdd_r_curr_min     : 3;  ///< [61:59] max. read current for vdd min
            uint32_t c_size             : 12; ///< [73:62] device size
            uint32_t reserved_74        : 2;  ///< [75:74]
            uint32_t dsr_imp            : 1;  ///< [76]    dsr implemented
            uint32_t read_blk_misalign  : 1;  ///< [77]    read block misalignment
            uint32_t write_blk_misalign : 1;  ///< [78]    write block misalignment
            uint32_t read_bl_partial    : 1;  ///< [79]    partial blocks for read allowed
            uint32_t read_bl_len        : 4;  ///< [83:80] max read data block length
            uint32_t ccc                : 12; ///< [95:84] card command classes
            uint32_t tran_speed         : 8;  ///< [103:96] max. data transfer rate
            uint32_t nsac               : 8;  ///< [111:104] data read access-time-2 clk cycles
            uint32_t taac               : 8;  ///< [119:112] data read access-time-1
            uint32_t reserved_120       : 6;  ///< [125:120]
            uint32_t csd_structure      : 2;  ///< [127:126] csd structure
            uint32_t reserved_128       : 8;  ///< [135:128]
        } csd_v1_b;

        /* All structures in this union must be packed since some bitfields span more than one 32-bit word. */
#if defined(__ICCARM__)
        __packed struct
#elif defined(__GNUC__)
        struct __attribute__((__packed__))
#endif
        {
            uint32_t reserved_8         : 2;  ///< [9:8]
            uint32_t file_format        : 2;  ///< [11:10] file format
            uint32_t tmp_write_protect  : 1;  ///< [12]    temporary write protection
            uint32_t perm_write_protect : 1;  ///< [13]    permanent write protection
            uint32_t copy               : 1;  ///< [14]    copy flag
            uint32_t file_format_grp    : 1;  ///< [15]    file format group
            uint32_t reserved_20        : 5;  ///< [20:16]
            uint32_t write_bl_partial   : 1;  ///< [21]    partial blocks for write allowed
            uint32_t write_bl_len       : 4;  ///< [25:22] max. write data block length
            uint32_t r2w_factor         : 3;  ///< [28:26] write speed factor
            uint32_t reserved_29        : 2;  ///< [30:29]
            uint32_t wp_grp_enable      : 1;  ///< [31]    write protect group enable
            uint32_t wp_grp_size        : 7;  ///< [38:32] write protect group size
            uint32_t sector_size        : 7;  ///< [45:39] erase sector size
            uint32_t erase_blk_en       : 1;  ///< [46]    erase single block enable
            uint32_t reserved_47        : 1;  ///< [47]
            uint32_t c_size             : 22; ///< [69:48] device size
            uint32_t reserved_70        : 6;  ///< [75:70]
            uint32_t dsr_imp            : 1;  ///< [76]    dsr implemented
            uint32_t read_blk_misalign  : 1;  ///< [77]    read block misalignment
            uint32_t write_blk_misalign : 1;  ///< [78]    write block misalignment
            uint32_t read_bl_partial    : 1;  ///< [79]    partial blocks for read allowed
            uint32_t read_bl_len        : 4;  ///< [83:80] max read data block length
            uint32_t ccc                : 12; ///< [95:84] card command classes
            uint32_t tran_speed         : 8;  ///< [103:96] max. data transfer rate
            uint32_t nsac               : 8;  ///< [111:104] data read access-time-2 clk cycles
            uint32_t taac               : 8;  ///< [119:112] data read access-time-1
            uint32_t reserved_120       : 6;  ///< [125:120]
            uint32_t csd_structure      : 2;  ///< [127:126] csd structure
            uint32_t reserved_128       : 8;  ///< [135:128]
        } csd_v2_b;

        /* All structures in this union must be packed since some bitfields span more than one 32-bit word. */
#if defined(__ICCARM__)
        __packed struct
#elif defined(__GNUC__)
        struct __attribute__((__packed__))
#endif
        {
            uint32_t reserved_0 : 1;

            uint32_t crc              : 7;
            uint32_t mfg_date         : 12;
            uint32_t reserved_23      : 4;
            uint32_t serial_number    : SDHI_PRV_CSD_CID_SERIAL_NUMBER_BITS;
            uint32_t product_revision : 8;
            uint64_t product_name     : SDHI_PRV_CSD_CID_PRODUCT_NAME_BITS;
            uint32_t oem_id           : 16;
            uint32_t mfg_id           : 8;
            uint32_t reserved_128     : 8;
        } cid;
    };
} sdmmc_priv_csd_reg_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
