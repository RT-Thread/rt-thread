/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef SDEMMC_W_PRV_R_SDEMMC_PRIVATE_H
#define SDEMMC_W_PRV_R_SDEMMC_PRIVATE_H

/**********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define SDEMMC_W_PRV_CSD_VERSION_1_0                        (0U)
#define SDEMMC_W_PRV_CSD_VERSION_2_0                        (1U) /* value of 1 is CSD 2.0 according to SD spec. */

#define SDEMMC_W_PRV_CMD_GO_IDLE_STATE                      (0U)
#define SDEMMC_W_PRV_CMD_SEND_OP_COND                       (1U)
#define SDEMMC_W_PRV_CMD_ALL_SEND_CID                       (2U)
#define SDEMMC_W_PRV_CMD_SEND_RELATIVE_ADDR                 (3U)
#define SDEMMC_W_PRV_CMD_SDIO                               (5U)
#define SDEMMC_W_PRV_CMD_SET_BUS_WIDTH                      (6U)
#define SDEMMC_W_PRV_CMD_SWITCH                             (6U)
#define SDEMMC_W_PRV_CMD_SEL_DES_CARD                       (7U)
#define SDEMMC_W_PRV_CMD_IF_COND                            (8U)
#define SDEMMC_W_PRV_CMD_SEND_CSD                           (9U)
#define SDEMMC_W_PRV_CMD_SEND_CID                           (10U)
#define SDEMMC_W_PRV_CMD_STOP_TRANSM                        (12U)
#define SDEMMC_W_PRV_CMD_SET_BLOCKLEN                       (16U)
#define SDEMMC_W_PRV_CMD_READ_SINGLE_BLOCK                  (17U)
#define SDEMMC_W_PRV_CMD_READ_MULTIPLE_BLOCK                (18U)
#define SDEMMC_W_PRV_CMD_SET_BLK_CNT                        (23U)
#define SDEMMC_W_PRV_CMD_WRITE_SINGLE_BLOCK                 (24U)
#define SDEMMC_W_PRV_CMD_WRITE_MULTIPLE_BLOCK               (25U)
#define SDEMMC_W_PRV_CMD_ERASE_WR_BLK_START                 (32U)
#define SDEMMC_W_PRV_CMD_ERASE_WR_BLK_END                   (33U)
#define SDEMMC_W_PRV_CMD_TAG_ERASE_GROUP_START              (0x423U)
#define SDEMMC_W_PRV_CMD_TAG_ERASE_GROUP_END                (0x424U)
#define SDEMMC_W_PRV_CMD_ERASE                              (38U)
#define SDEMMC_W_PRV_CMD_SD_SEND_OP_COND                    (41U)
#define SDEMMC_W_PRV_CMD_IO_RW_DIRECT                       (52U)
#define SDEMMC_W_PRV_CMD_IO_RW_EXTENDED                     (53U)
#define SDEMMC_W_PRV_CMD_IO_READ_EXT_SINGLE_BLOCK           (0x1c35U)
#define SDEMMC_W_PRV_CMD_IO_EXT_MULTI_BLOCK                 (0x6000U)
#define SDEMMC_W_PRV_CMD_IO_WRITE_EXT_SINGLE_BLOCK          (0x0c35U)

#define SDEMMC_W_PRV_CMD_APP_CMD                            (55U)
#define SDEMMC_W_PRV_CMD_C_ACMD                             (1U << 6) /* APP Command */

#define SDEMMC_W_PRV_IF_COND_VOLTAGE                        (1U)
#define SDEMMC_W_PRV_IF_COND_CHECK_PATTERN                  (0xAAU)

#define SDEMMC_W_PRV_OCR_CAPACITY_HC                        (1U << 30)

#define SDEMMC_W_PRV_OCR_VDD_2_7_V                          (1U << 15)
#define SDEMMC_W_PRV_OCR_VDD_2_8_V                          (1U << 16)
#define SDEMMC_W_PRV_OCR_VDD_2_9_V                          (1U << 17)
#define SDEMMC_W_PRV_OCR_VDD_3_0_V                          (1U << 18)
#define SDEMMC_W_PRV_OCR_VDD_3_1_V                          (1U << 19)
#define SDEMMC_W_PRV_OCR_VDD_3_2_V                          (1U << 20)
#define SDEMMC_W_PRV_OCR_VDD_3_3_V                          (1U << 21)
#define SDEMMC_W_PRV_OCR_VDD_3_4_V                          (1U << 22)
#define SDEMMC_W_PRV_OCR_VDD_3_5_V                          (1U << 23)
#define SDEMMC_W_PRV_OCR_VDD_SUPPORTED                                                                       \
    (SDEMMC_W_PRV_OCR_VDD_2_7_V | SDEMMC_W_PRV_OCR_VDD_2_8_V | SDEMMC_W_PRV_OCR_VDD_2_9_V | SDEMMC_W_PRV_OCR_VDD_3_0_V | \
     SDEMMC_W_PRV_OCR_VDD_3_1_V |                                                                            \
     SDEMMC_W_PRV_OCR_VDD_3_2_V | SDEMMC_W_PRV_OCR_VDD_3_3_V | SDEMMC_W_PRV_OCR_VDD_3_4_V | SDEMMC_W_PRV_OCR_VDD_3_5_V)

/* CMD52 Arguments */
#define SDEMMC_W_PRV_SDIO_CMD52_READ                        (0U)
#define SDEMMC_W_PRV_SDIO_CMD52_WRITE                       (1U)

/* SWITCH command argument's bit postion */
#define SDEMMC_W_PRV_SWITCH_ACCESS_SHIFT                    (24U)
#define SDEMMC_W_PRV_SWITCH_INDEX_SHIFT                     (16U)
#define SDEMMC_W_PRV_SWITCH_VALUE_SHIFT                     (8U)

#define SDEMMC_W_PRV_EMMC_EXT_CSD_SIZE                      (512U)

/* Offsets */
#define SDEMMC_W_PRV_E_CSD_PART_ATTR                        (156U)             /* R/W */
#define SDEMMC_W_PRV_E_CSD_PART_SUPP                        (160U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_ER_GRP_DEF                       (175U)             /* R/W */
#define SDEMMC_W_PRV_E_CSD_PART_CFG                         (179U)             /* R/W */
#define SDEMMC_W_PRV_E_CSD_ERASED_MEM_CONT                  (181U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_BUS_WIDTH                        (183U)             /* R/W */
#define SDEMMC_W_PRV_EMMC_EXT_CSD_HS_TIMING_OFFSET          (185U)             /* R/W */
#define SDEMMC_W_PRV_E_CSD_STRUCTURE                        (194U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_REV                              (192U)             /* Read Only */
#define SDEMMC_W_PRV_EMMC_EXT_CSD_DEVICE_TYPE_OFFSET        (196U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_PART_SWCH_TM                     (199U)             /* Read Only */
#define SDEMMC_W_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET          (212U)             /* Read Only, 4 bytes */
#define SDEMMC_W_PRV_E_CSD_S_A_TIMEOUT                      (217U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_HC_WP_GRP_SIZE                   (221U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_REL_WR_SEC_C                     (222U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_ER_TO_MULT                       (223U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_HC_ERASE_GRP_SIZE                (224U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_BOOT_MULT                        (226U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_SEC_TRIM_MULT                    (229U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_SEC_ERASE_MULT                   (230U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_SEC_FT_SUPP                      (231U)             /* Read Only */
#define SDEMMC_W_PRV_E_CSD_TRIM_MULT                        (232U)             /* Read Only */

/* Commands */
#define SDEMMC_W_PRV_EMMC_SWITCH_ACCESS_WRITE_BYTE          (3U)
#define SDEMMC_W_PRV_EMMC_HIGH_SPEED_52_MHZ_BIT             (2U)
#define SDEMMC_W_PRV_EMMC_HIGH_SPEED_MODE                   (((SDEMMC_W_PRV_EMMC_SWITCH_ACCESS_WRITE_BYTE << 24U) |  \
                                                          (SDEMMC_W_PRV_EMMC_EXT_CSD_HS_TIMING_OFFSET << 16U)) | \
                                                         (SDEMMC_W_PRV_EMMC_HIGH_SPEED_52_MHZ_BIT << 8U))

#define SDEMMC_W_PRV_SD_SWITCH_STATUS_SIZE                  (64U)
#define SDEMMC_W_PRV_SD_SWITCH_HIGH_SPEED_RESPONSE          (13U)
#define SDEMMC_W_PRV_SD_SWITCH_HIGH_SPEED_ERROR_RESPONSE    (16U)
#define SDEMMC_W_PRV_SD_SWITCH_HIGH_SPEED_ERROR             (0x0fU)
#define SDEMMC_W_PRV_SD_SWITCH_HIGH_SPEED_OK                (0x02U)

#define SDEMMC_W_PRV_EMMC_SEND_OP_COND                      (0x701U)
#define SDEMMC_W_PRV_EMMC_CMD_SWITCH_WBUSY                  (0x506U)      /* eMMC CMD6 switch command "with response busy" */
#define SDEMMC_W_PRV_EMMC_CMD_SEND_EXT_CSD                  (0x1C08U)     /* CMD 8, read data */
#define SDEMMC_W_PRV_EMMC_DEFAULT_CLOCK_RATE                (26000000U)   /* 26 MHz */
#define SDEMMC_W_PRV_EMMC_HIGH_SPEED_CLOCK_RATE             (52000000U)   /* 52 MHz */
#define SDEMMC_W_PRV_SD_HIGH_SPEED_MODE_SWITCH              (0x80FFFFF1U) /* set SD high speed */
#define SDEMMC_W_PRV_SD_DEFAULT_CLOCK_RATE                  (25000000U)   /* 25 MHz */
#define SDEMMC_W_PRV_SD_HIGH_SPEED_CLOCK_RATE               (50000000U)   /* 50 MHz */
#define SDEMMC_W_PRV_SDIO_HIGH_SPEED_CLOCK_RATE             (50000000U)   /* 50 MHz */

#define SDEMMC_W_PRV_EMMC_ERASE_ARGUMENT_TRIM               (1U)

#define SDEMMC_W_PRV_CSD_CID_SERIAL_NUMBER_BITS             (32)
#define SDEMMC_W_PRV_CSD_CID_PRODUCT_NAME_BITS              (40)

#define SDEMMC_W_PRV_MMC_RETRY_COUNT                        (100)
#define SDEMMC_W_PRV_SDIO_CCR_IOR_RETRY_COUNT               (10)

#define SDEMMC_W_PRV_EMMC_DELAY_10                          (10)
#define SDEMMC_W_PRV_EMMC_DELAY_100                         (100)
#define SDEMMC_W_PRV_EMMC_DELAY_10000                       (10000)

#define SDEMMC_W_PRV_SDIO_SEND_OP_COND                      (5)
#define SDEMMC_W_PRV_CARD_READY                             (0x80000000)
#define SDEMMC_W_PRV_R4_MEM_PR                              (0x08000000)
#define SDEMMC_W_PRV_SUPPORT_VOLTAGE                        (0x00300000)

#define SDEMMC_W_PRV_SDIO_CCCR_CCCR                         (0x00)

#define SDEMMC_W_PRV_SDIO_CCCR_CAPS                         (0x08)
#define SDEMMC_W_PRV_SDIO_CCCR_CAP_SMB                      (0x02)
#define SDEMMC_W_PRV_SDIO_CCCR_CAP_LSC                      (0x40)
#define SDEMMC_W_PRV_SDIO_CCCR_CAP_4BLS                     (0x80)

#define SDEMMC_W_PRV_SDIO_SPEED_SHS                         (0x01)
#define SDEMMC_W_PRV_SDIO_FBR_BASE(y)                       (0x100 * (y))
#define SDEMMC_W_PRV_SDIO_FBR_CIS                           (0x09)

#define SDEMMC_W_PRV_SDIO_CCCR_IOEX                         (0x02)
#define SDEMMC_W_PRV_SDIO_CCCR_IORX                         (0x03)

#define SDEMMC_W_PRV_SDIO_SDIO_R_1_00                       (0)
#define SDEMMC_W_PRV_SDIO_SDIO_R_2_00                       (3)
#define SDEMMC_W_PRV_SDIO_CCCR_R_1_10                       (1)
#define SDEMMC_W_PRV_SDIO_CCCR_R_1_20                       (2)

#define SDEMMC_W_PRV_SDIO_CCCR_POWER                        (0x12)
#define SDEMMC_W_PRV_SDIO_PWR_SMPC                          (0x01)
#define SDEMMC_W_PRV_SDIO_CCCR_SPEED                        (0x13)
#define SDEMMC_W_PRV_SDIO_FBR_BLKSZ                         (0x10)

/* Commands for applications */
#define SDEMMC_W_PRV_SD_APP_SD_STS                          (13)
#define SDEMMC_W_PRV_SD_APP_SEND_SCR                        (51)

/* SCR field definitions (sda_vsn) */
#define SDEMMC_W_PRV_SCR_SPEC_VER_0                         (0) /* Implements system specification 1.0 - 1.01 */
#define SDEMMC_W_PRV_SCR_SPEC_VER_1                         (1) /* Implements system specification 1.10 */
#define SDEMMC_W_PRV_SCR_SPEC_VER_2                         (2) /* Implements system specification 2.00-3.0X */


/* SD bus widths (bus_wid) */
#define SDEMMC_W_PRV_SD_BUS_WIDTH_1                         (0)
#define SDEMMC_W_PRV_SD_BUS_WIDTH_4                         (2)

/* CMD23 support (sd_cmds) */
#define SDEMMC_W_PRV_SCR_CMD23_SUPPORT                      (1 << 1)

#define SDEMMC_W_PRV_E_CSD_CD_TYPE_26                       (1 << 0)        /* 26MHz Read : Card Type */
#define SDEMMC_W_PRV_E_CSD_CD_TYPE_52                       (1 << 1)        /* 52MHz Read : Card Type */
#define SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_1_8V                 (1 << 2)        /* 52MHz Read : DDR I/O mode @1.8V or 3V */
#define SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_1_2V                 (1 << 3)        /* 52MHz Read : DDR I/O mode @1.2V */
#define SDEMMC_W_PRV_E_CSD_CD_TYPE_MASK                     (0xF)

#define SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_52                   (SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_1_8V | SDEMMC_W_PRV_E_CSD_CD_TYPE_DDR_1_2V)

#define SDEMMC_W_PRV_E_CSD_CMD_SET_NORMAL                   (1 << 0)

#define SDEMMC_W_PRV_MMC_SWITCH_MODE_WRITE_BYTE             (0x03)

#ifndef SDEMMC_W_ARRAY_SIZE
#define SDEMMC_W_ARRAY_SIZE(array)\
        (sizeof(array) / sizeof(array[0]))
#endif

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

typedef enum e_sdmmc_priv_card_type
{
    SDMMC_PRIV_CT_UNKNOWN_TYPE,
    SDMMC_PRIV_CT_SDIO_CARD,
    SDMMC_PRIV_CT_SD_CARD_1_1,
    SDMMC_PRIV_CT_SD_CARD,
    SDMMC_PRIV_CT_MMC_CARD,
    SDMMC_PRIV_CT_CARD_MAX
} sdmmc_priv_card_type_t;

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
            uint32_t reserved_8         : 2;  /* [9:8] */
            uint32_t file_format        : 2;  /* [11:10] file format */
            uint32_t tmp_write_protect  : 1;  /* [12]    temporary write protection */
            uint32_t perm_write_protect : 1;  /* [13]    permanent write protection */
            uint32_t copy               : 1;  /* [14]    copy flag */
            uint32_t file_format_grp    : 1;  /* [15]    file format group */
            uint32_t reserved_20        : 5;  /* [16-20] */
            uint32_t write_bl_partial   : 1;  /* [21]    partial blocks for write allowed */
            uint32_t write_bl_len       : 4;  /* [25:22] max. write data block length */
            uint32_t r2w_factor         : 3;  /* [28:26] write speed factor */
            uint32_t reserved_29        : 2;  /* [30:29] */
            uint32_t wp_grp_enable      : 1;  /* [31]    write protect group enable */
            uint32_t wp_grp_size        : 7;  /* [38:32] write protect group size */
            uint32_t sector_size        : 7;  /* [45:39] erase sector size */
            uint32_t erase_blk_en       : 1;  /* [46]    erase single block enable */
            uint32_t c_size_mult        : 3;  /* [49:47] device size multiplier */
            uint32_t vdd_w_curr_max     : 3;  /* [52:50] max. write current for vdd max */
            uint32_t vdd_w_curr_min     : 3;  /* [55:53] max. write current for vdd min */
            uint32_t vdd_r_curr_max     : 3;  /* [58:56] max. read current for vdd max */
            uint32_t vdd_r_curr_min     : 3;  /* [61:59] max. read current for vdd min */
            uint32_t c_size             : 12; /* [73:62] device size */
            uint32_t reserved_74        : 2;  /* [75:74] */
            uint32_t dsr_imp            : 1;  /* [76]    dsr implemented */
            uint32_t read_blk_misalign  : 1;  /* [77]    read block misalignment */
            uint32_t write_blk_misalign : 1;  /* [78]    write block misalignment */
            uint32_t read_bl_partial    : 1;  /* [79]    partial blocks for read allowed */
            uint32_t read_bl_len        : 4;  /* [83:80] max read data block length */
            uint32_t ccc                : 12; /* [95:84] card command classes */
            uint32_t tran_speed         : 8;  /* [103:96] max. data transfer rate */
            uint32_t nsac               : 8;  /* [111:104] data read access-time-2 clk cycles */
            uint32_t taac               : 8;  /* [119:112] data read access-time-1 */
            uint32_t reserved_120       : 6;  /* [125:120] */
            uint32_t csd_structure      : 2;  /* [127:126] csd structure */
            uint32_t reserved_128       : 8;  /* [135:128] */
        } csd_v1_b;

        /* All structures in this union must be packed since some bitfields span more than one 32-bit word. */
#if defined(__ICCARM__)
        __packed struct
#elif defined(__GNUC__)
        struct __attribute__((__packed__))
#endif
        {
            uint32_t reserved_8         : 2;  /* [9:8] */
            uint32_t file_format        : 2;  /* [11:10] file format */
            uint32_t tmp_write_protect  : 1;  /* [12]    temporary write protection */
            uint32_t perm_write_protect : 1;  /* [13]    permanent write protection */
            uint32_t copy               : 1;  /* [14]    copy flag */
            uint32_t file_format_grp    : 1;  /* [15]    file format group */
            uint32_t reserved_20        : 5;  /* [20:16] */
            uint32_t write_bl_partial   : 1;  /* [21]    partial blocks for write allowed */
            uint32_t write_bl_len       : 4;  /* [25:22] max. write data block length */
            uint32_t r2w_factor         : 3;  /* [28:26] write speed factor */
            uint32_t reserved_29        : 2;  /* [30:29] */
            uint32_t wp_grp_enable      : 1;  /* [31]    write protect group enable */
            uint32_t wp_grp_size        : 7;  /* [38:32] write protect group size */
            uint32_t sector_size        : 7;  /* [45:39] erase sector size */
            uint32_t erase_blk_en       : 1;  /* [46]    erase single block enable */
            uint32_t reserved_47        : 1;  /* [47] */
            uint32_t c_size             : 22; /* [69:48] device size */
            uint32_t reserved_70        : 6;  /* [75:70] */
            uint32_t dsr_imp            : 1;  /* [76]    dsr implemented */
            uint32_t read_blk_misalign  : 1;  /* [77]    read block misalignment */
            uint32_t write_blk_misalign : 1;  /* [78]    write block misalignment */
            uint32_t read_bl_partial    : 1;  /* [79]    partial blocks for read allowed */
            uint32_t read_bl_len        : 4;  /* [83:80] max read data block length */
            uint32_t ccc                : 12; /* [95:84] card command classes */
            uint32_t tran_speed         : 8;  /* [103:96] max. data transfer rate */
            uint32_t nsac               : 8;  /* [111:104] data read access-time-2 clk cycles */
            uint32_t taac               : 8;  /* [119:112] data read access-time-1 */
            uint32_t reserved_120       : 6;  /* [125:120] */
            uint32_t csd_structure      : 2;  /* [127:126] csd structure */
            uint32_t reserved_128       : 8;  /* [135:128] */
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
            uint32_t serial_number    : SDEMMC_W_PRV_CSD_CID_SERIAL_NUMBER_BITS;
            uint32_t product_revision : 8;
            uint64_t product_name     : SDEMMC_W_PRV_CSD_CID_PRODUCT_NAME_BITS;
            uint32_t oem_id           : 16;
            uint32_t mfg_id           : 8;
            uint32_t reserved_128     : 8;
        } cid;
    };
} sdmmc_priv_csd_reg_t;

typedef union u_sdmmc_priv_sdio_arg_t
{
    uint32_t arg;

    struct
    {
        uint32_t data             : 8;  /* read/write data */
        uint32_t stuff_8          : 1;  /* Stuff bit */
        uint32_t register_address : 17; /* Register Address */
        uint32_t stuff_26         : 1;  /* Stuff bit should be set to 1 */
        uint32_t raw              : 1;  /* 1= Read after write. */
        uint32_t function_number  : 3;  /* function0~function7 */
        uint32_t rw_flag          : 1;  /* 0:read, 1:write */
    } cmd_52_arg;

    struct
    {
        uint32_t count            : 9;  /* Byte/Block Count */
        uint32_t register_address : 17; /* Register Address */
        uint32_t op_code          : 1;  /* 0:fixed address, 1:incrementing address */
        uint32_t block_mode       : 1;  /* 0: Byte, 1:Block */
        uint32_t function_number  : 3;  /* function0~function7 */
        uint32_t rw_flag          : 1;  /* 0:read, 1:write */
    } cmd_53_arg;
} sdmmc_priv_sdio_arg_t;

typedef struct st_mmc_csd
{
     uint8_t           mmc_struct;             /* Structure */
     uint8_t           mmca_vsn;
     uint16_t          command_class;
     uint16_t          clks_for_tacc;
     uint32_t          ns_for_tacc;
     uint32_t          c_sz;
     uint32_t          factor_for_r2w;
     uint32_t          max_dtr;
     uint32_t          sz_for_erase;           /* erase_size In sectors */
     uint32_t          rd_bits_for_blk;
     uint32_t          wr_bits_for_blk;
     uint32_t          capa_size;
     uint32_t          rd_part:1,
                       rd_misalign_flag:1,
                       wr_part:1,
                       wr_misalign_flag:1;
} st_mmc_csd_t;

typedef struct st_mmc_ext_csd
{
     uint8_t           rev;
     uint8_t           erase_group_def;
     uint8_t           sec_feature_support;
     uint8_t           rel_sectors;
     uint8_t           rel_param;
     uint8_t           part_config;
     uint8_t           rst_n_function;
     uint8_t           cache_ctrl;
     uint8_t           max_packed_writes;
     uint8_t           max_packed_reads;
     uint8_t           packed_event_en;
     uint32_t          part_time;              /* Units: ms */
     uint32_t          sa_timeout;             /* Units: 100ns */
     uint32_t          generic_cmd6_time;      /* Units: 10ms */
     uint32_t          power_off_longtime;     /* Units: ms */
     uint32_t          hs_max_dtr;
     uint32_t          sectors;
     uint32_t          card_type;
     uint32_t          hc_erase_size;          /* In sectors */
     uint32_t          hc_erase_timeout;       /* In milliseconds */
     uint32_t          sec_trim_mult;          /* Secure trim multiplier  */
     uint32_t          sec_erase_mult;         /* Secure erase multiplier */
     uint32_t          trim_timeout;           /* In milliseconds */
     uint8_t           enhanced_area_en;       /* enable bit */
     uint64_t          enhanced_area_offset;   /* Units: Byte */
     uint32_t          enhanced_area_size;     /* Units: KB */
     uint32_t          boot_size;              /* in bytes */
     uint32_t          cache_size;             /* Units: KB */
     uint8_t           hpi_en;                 /* HPI enablebit */
     uint8_t           hpi;                    /* HPI support bit */
     uint32_t          hpi_cmd;                /* cmd used as HPI */
     uint8_t           raw_partition_support;  /* 160 */
     uint8_t           raw_erased_mem_count;   /* 181 */
     uint8_t           raw_ext_csd_structure;  /* 194 */
     uint8_t           raw_card_type;          /* 196 */
     uint8_t           out_of_int_time;        /* 198 */
     uint8_t           raw_s_a_timeout;        /* 217 */
     uint8_t           raw_hc_erase_gap_size;  /* 221 */
     uint8_t           raw_erase_timeout_mult; /* 223 */
     uint8_t           raw_hc_erase_grp_size;  /* 224 */
     uint8_t           raw_sec_trim_mult;      /* 229 */
     uint8_t           raw_sec_erase_mult;     /* 230 */
     uint8_t           raw_sec_feature_support;/* 231 */
     uint8_t           raw_trim_mult;          /* 232 */
     uint8_t           raw_sectors[4];         /* 212 - 4 bytes */

     uint32_t          feature_support;
#define MMC_DISCARD_FEATURE     BIT(0)         /* CMD38 feature */
} st_mmc_ext_csd_t;

typedef struct st_mmc_cid
{
    uint32_t          manfid;
    int8_t            prod_name[8];
    uint32_t          serial;
    uint16_t          oemid;
    uint16_t          year;
    uint8_t           hwrev;
    uint8_t           fwrev;
    uint8_t           month;
} st_mmc_cid_t;

typedef struct st_sd_scr
{
    uint8_t           sda_vsn;
    uint8_t           sda_spec3;
    uint8_t           bus_wid;
    uint8_t           sd_cmds;
} st_sd_scr_t;

typedef struct st_sd_ssr
{
    uint32_t          bus_width;
    uint16_t          cd_type;
    uint32_t          area_protected;
    uint32_t          spd_class;
    uint8_t           perf_mv;
    uint32_t          au;
    uint32_t          erase_to;
    uint32_t          erase_off;
} st_sd_ssr_t;

typedef struct st_sd_swt_caps
{
    uint32_t          hs_max_dtr;
    uint32_t          uhs_max_dtr;
    uint32_t          sd3_bus_mode;
    uint32_t          sd3_drv_type;
    uint32_t          sd3_curr_limit;
} st_sd_swt_caps_t;

typedef struct st_sdio_cccr
{
     uint32_t         sdio_vsn;
     uint32_t         sd_vsn;
     uint32_t         multi_block:1,
                      low_speed:1,
                      wide_bus:1,
                      high_power:1,
                      high_speed:1,
                      disable_cd:1;
} st_sdio_cccr_t;

typedef struct st_sdio_cis
{
     uint16_t         vendor;
     uint16_t         device;
     uint16_t         blksize;
     uint32_t         max_dtr;
     uint32_t         enable_timeout;
} st_sdio_cis_t;

typedef struct st_sdemmc_config
{
    sdmmc_priv_card_type_t            card_type;
    uint32_t                          ocr;
    uint32_t                          rca;
    uint32_t                          type;
    uint32_t                          raw_cid[4];
    uint32_t                          raw_csd[4];
    uint32_t                          raw_scr[2];
    uint32_t                          raw_ssr[16];
    uint32_t                          use_spi;
    uint32_t                          clock;
    uint32_t                          max_blk_size;
    uint32_t                          cur_blk_size;
    uint32_t                          bus_width;
    uint32_t                          erased_byte;
    st_mmc_csd_t                      csd;
    st_mmc_ext_csd_t                  ext_csd;
    st_mmc_cid_t                      cid;
    st_sd_scr_t                       scr;
    st_sd_ssr_t                       ssr;
    st_sd_swt_caps_t                  caps;
    st_sdio_cccr_t                    cccr;
    st_sdio_cis_t                     cis;
    uint8_t                           pext_csd[SDEMMC_W_PRV_EMMC_EXT_CSD_SIZE];
    uint8_t                           *psdio_cis;
    uint32_t                          sdio_num_info;
    uint8_t                           **psdio_info;
} st_sdemmc_config_t;

typedef fsp_err_t (tpl_parse_t)(st_sdemmc_config_t *config, uint8_t *buf, uint32_t size);

typedef struct tuples_for_cis {
    uint8_t code;
    uint8_t min_size;
    tpl_parse_t *parse;
} st_tuples_for_cis_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
