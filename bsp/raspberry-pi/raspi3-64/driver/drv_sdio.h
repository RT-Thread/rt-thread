/*
 * File      : drv_sdio.h
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#ifndef __DRV_SDIO_H__
#define __DRV_SDIO_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/dev_mmcsd_core.h>

#include "board.h"

#define MMC0_BASE_ADDR     0x3F300000

/* Struct for Intrrrupt Information */
#define SDXC_CmdDone       BIT(0)
#define SDXC_DataDone      BIT(1)
#define SDXC_BlockGap      BIT(2)
#define SDXC_WriteRdy      BIT(4)
#define SDXC_ReadRdy       BIT(5)
#define SDXC_Card          BIT(8)
#define SDXC_Retune        BIT(12)
#define SDXC_BootAck       BIT(13)
#define SDXC_EndBoot       BIT(14)
#define SDXC_Err              BIT(15)
#define SDXC_CTOErr        BIT(16)
#define SDXC_CCRCErr       BIT(17)
#define SDXC_CENDErr       BIT(18)
#define SDXC_CBADErr       BIT(19)
#define SDXC_DTOErr        BIT(20)
#define SDXC_DCRCErr       BIT(21)
#define SDXC_DENDErr       BIT(22)
#define SDXC_ACMDErr       BIT(24)

#define SDXC_BLKCNT_EN          BIT(1)
#define SDXC_AUTO_CMD12_EN      BIT(2)
#define SDXC_AUTO_CMD23_EN      BIT(3)
#define SDXC_DAT_DIR              BIT(4)   //from card to host
#define SDXC_MULTI_BLOCK        BIT(5)
#define SDXC_CMD_RSPNS_136         BIT(16)
#define SDXC_CMD_RSPNS_48         BIT(17)
#define SDXC_CMD_RSPNS_48busy   BIT(16)|BIT(17)
#define SDXC_CHECK_CRC_CMD      BIT(19)
#define SDXC_CMD_IXCHK_EN       BIT(20)
#define SDXC_CMD_ISDATA         BIT(21)
#define SDXC_CMD_SUSPEND        BIT(22)
#define SDXC_CMD_RESUME         BIT(23)
#define SDXC_CMD_ABORT          BIT(23)|BIT(22)

#define SDXC_CMD_INHIBIT    BIT(0)
#define SDXC_DAT_INHIBIT    BIT(1)
#define SDXC_DAT_ACTIVE     BIT(2)
#define SDXC_WRITE_TRANSFER     BIT(8)
#define SDXC_READ_TRANSFER     BIT(9)

struct sdhci_cmd_t
{
    rt_uint32_t cmdidx;
    rt_uint32_t cmdarg;
    rt_uint32_t resptype;
    rt_uint32_t datarw;
#define DATA_READ 1
#define DATA_WRITE 2
    rt_uint32_t response[4];
};

struct sdhci_data_t
{
    rt_uint8_t * buf;
    rt_uint32_t flag;
    rt_uint32_t blksz;
    rt_uint32_t blkcnt;
};

struct sdhci_t
{
    char * name;
    rt_uint32_t voltages;
    rt_uint32_t width;
    rt_uint32_t clock;
    rt_err_t removeable;
    void * sdcard;

    rt_err_t (*detect)(struct sdhci_t * sdhci);
    rt_err_t (*setwidth)(struct sdhci_t * sdhci, rt_uint32_t width);
    rt_err_t (*setclock)(struct sdhci_t * sdhci, rt_uint32_t clock);
    rt_err_t (*transfer)(struct sdhci_t * sdhci, struct sdhci_cmd_t * cmd, struct sdhci_data_t * dat);
    void * priv;
};

struct sdhci_pdata_t
{
    rt_uint32_t virt;
};

// EMMC command flags
#define CMD_TYPE_NORMAL  0x00000000
#define CMD_TYPE_SUSPEND 0x00400000
#define CMD_TYPE_RESUME  0x00800000
#define CMD_TYPE_ABORT   0x00c00000
#define CMD_IS_DATA      0x00200000
#define CMD_IXCHK_EN     0x00100000
#define CMD_CRCCHK_EN    0x00080000
#define CMD_RSPNS_NO     0x00000000
#define CMD_RSPNS_136    0x00010000
#define CMD_RSPNS_48     0x00020000
#define CMD_RSPNS_48B    0x00030000
#define TM_MULTI_BLOCK   0x00000020
#define TM_DAT_DIR_HC    0x00000000
#define TM_DAT_DIR_CH    0x00000010
#define TM_AUTO_CMD23    0x00000008
#define TM_AUTO_CMD12    0x00000004
#define TM_BLKCNT_EN     0x00000002
#define TM_MULTI_DATA    (CMD_IS_DATA|TM_MULTI_BLOCK|TM_BLKCNT_EN)

#define RCA_NO     1
#define RCA_YES    2

// INTERRUPT register settings
#define INT_AUTO_ERROR   0x01000000
#define INT_DATA_END_ERR 0x00400000
#define INT_DATA_CRC_ERR 0x00200000
#define INT_DATA_TIMEOUT 0x00100000
#define INT_INDEX_ERROR  0x00080000
#define INT_END_ERROR    0x00040000
#define INT_CRC_ERROR    0x00020000
#define INT_CMD_TIMEOUT  0x00010000
#define INT_ERR          0x00008000
#define INT_ENDBOOT      0x00004000
#define INT_BOOTACK      0x00002000
#define INT_RETUNE       0x00001000
#define INT_CARD         0x00000100
#define INT_READ_RDY     0x00000020
#define INT_WRITE_RDY    0x00000010
#define INT_BLOCK_GAP    0x00000004
#define INT_DATA_DONE    0x00000002
#define INT_CMD_DONE     0x00000001
#define INT_ERROR_MASK   (INT_CRC_ERROR|INT_END_ERROR|INT_INDEX_ERROR| \
                          INT_DATA_TIMEOUT|INT_DATA_CRC_ERR|INT_DATA_END_ERR| \
                          INT_ERR|INT_AUTO_ERROR)
#define INT_ALL_MASK     (INT_CMD_DONE|INT_DATA_DONE|INT_READ_RDY|INT_WRITE_RDY|INT_ERROR_MASK)

#define EMMC_ARG2         (0x00)
#define EMMC_BLKSIZECNT   (0x04)
#define EMMC_ARG1         (0x08)
#define EMMC_CMDTM        (0x0c)
#define EMMC_RESP0        (0x10)
#define EMMC_RESP1        (0x14)
#define EMMC_RESP2        (0x18)
#define EMMC_RESP3        (0x1c)
#define EMMC_DATA         (0x20)
#define EMMC_STATUS       (0x24)
#define EMMC_CONTROL0     (0x28)
#define EMMC_CONTROL1     (0x2c)
#define EMMC_INTERRUPT    (0x30)
#define EMMC_IRPT_MASK    (0x34)
#define EMMC_IRPT_EN      (0x38)
#define EMMC_CONTROL2     (0x3c)
#define EMMC_BOOT_TIMEOUT (0x70)
#define EMMC_EXRDFIFO_EN  (0x84)
#define EMMC_SPI_INT_SPT  (0xf0)
#define EMMC_SLOTISR_VER  (0xfc)

// CONTROL register settings
#define C0_SPI_MODE_EN   0x00100000
#define C0_HCTL_HS_EN    0x00000004
#define C0_HCTL_DWITDH   0x00000002

#define C1_SRST_DATA     0x04000000
#define C1_SRST_CMD      0x02000000
#define C1_SRST_HC       0x01000000
#define C1_TOUNIT_DIS    0x000f0000
#define C1_TOUNIT_MAX    0x000e0000
#define C1_CLK_GENSEL    0x00000020
#define C1_CLK_EN        0x00000004
#define C1_CLK_STABLE    0x00000002
#define C1_CLK_INTLEN    0x00000001

#define FREQ_SETUP           400000  // 400 Khz
#define FREQ_NORMAL        25000000  // 25 Mhz

// SLOTISR_VER values
#define HOST_SPEC_NUM              0x00ff0000
#define HOST_SPEC_NUM_SHIFT        16
#define HOST_SPEC_V3               2
#define HOST_SPEC_V2               1
#define HOST_SPEC_V1               0

// STATUS register settings
#define SR_DAT_LEVEL1        0x1e000000
#define SR_CMD_LEVEL         0x01000000
#define SR_DAT_LEVEL0        0x00f00000
#define SR_DAT3              0x00800000
#define SR_DAT2              0x00400000
#define SR_DAT1              0x00200000
#define SR_DAT0              0x00100000
#define SR_WRITE_PROT        0x00080000  // From SDHC spec v2, BCM says reserved
#define SR_READ_AVAILABLE    0x00000800  // ???? undocumented
#define SR_WRITE_AVAILABLE   0x00000400  // ???? undocumented
#define SR_READ_TRANSFER     0x00000200
#define SR_WRITE_TRANSFER    0x00000100
#define SR_DAT_ACTIVE        0x00000004
#define SR_DAT_INHIBIT       0x00000002
#define SR_CMD_INHIBIT       0x00000001

#define CONFIG_MMC_USE_DMA
#define DMA_ALIGN       (32U)

#define SD_CMD_INDEX(a)        ((a) << 24)
#define SD_CMD_RESERVED(a)  0xffffffff
#define SD_CMD_INDEX(a)        ((a) << 24)
#define SD_CMD_TYPE_NORMAL    0x0
#define SD_CMD_TYPE_SUSPEND    (1 << 22)
#define SD_CMD_TYPE_RESUME    (2 << 22)
#define SD_CMD_TYPE_ABORT    (3 << 22)
#define SD_CMD_TYPE_MASK    (3 << 22)
#define SD_CMD_ISDATA        (1 << 21)
#define SD_CMD_IXCHK_EN        (1 << 20)
#define SD_CMD_CRCCHK_EN    (1 << 19)
#define SD_CMD_RSPNS_TYPE_NONE    0            // For no response
#define SD_CMD_RSPNS_TYPE_136    (1 << 16)        // For response R2 (with CRC), R3,4 (no CRC)
#define SD_CMD_RSPNS_TYPE_48    (2 << 16)        // For responses R1, R5, R6, R7 (with CRC)
#define SD_CMD_RSPNS_TYPE_48B    (3 << 16)        // For responses R1b, R5b (with CRC)
#define SD_CMD_RSPNS_TYPE_MASK  (3 << 16)
#define SD_CMD_MULTI_BLOCK    (1 << 5)
#define SD_CMD_DAT_DIR_HC    0
#define SD_CMD_DAT_DIR_CH    (1 << 4)
#define SD_CMD_AUTO_CMD_EN_NONE    0
#define SD_CMD_AUTO_CMD_EN_CMD12    (1 << 2)
#define SD_CMD_AUTO_CMD_EN_CMD23    (2 << 2)
#define SD_CMD_BLKCNT_EN        (1 << 1)
#define SD_CMD_DMA          1
#define SD_RESP_NONE        SD_CMD_RSPNS_TYPE_NONE
#define SD_RESP_R1          (SD_CMD_RSPNS_TYPE_48)           // | SD_CMD_CRCCHK_EN)
#define SD_RESP_R1b         (SD_CMD_RSPNS_TYPE_48B)         // | SD_CMD_CRCCHK_EN)
#define SD_RESP_R2          (SD_CMD_RSPNS_TYPE_136)           //| SD_CMD_CRCCHK_EN)
#define SD_RESP_R3          SD_CMD_RSPNS_TYPE_48
#define SD_RESP_R4          SD_CMD_RSPNS_TYPE_136
#define SD_RESP_R5          (SD_CMD_RSPNS_TYPE_48 | SD_CMD_CRCCHK_EN)
#define SD_RESP_R5b         (SD_CMD_RSPNS_TYPE_48B | SD_CMD_CRCCHK_EN)
#define SD_RESP_R6          (SD_CMD_RSPNS_TYPE_48 | SD_CMD_CRCCHK_EN)
#define SD_RESP_R7          (SD_CMD_RSPNS_TYPE_48 | SD_CMD_CRCCHK_EN)
#define SD_DATA_READ        (SD_CMD_ISDATA | SD_CMD_DAT_DIR_CH)
#define SD_DATA_WRITE       (SD_CMD_ISDATA | SD_CMD_DAT_DIR_HC)
#endif
