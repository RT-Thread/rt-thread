/*
 * File      : drv_sdio.h
 * Copyright (c) 2006-2018, RT-Thread Development Team
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

#define MMC0_BASE_ADDR     0x20300000

struct raspi_mmc
{
    volatile rt_uint32_t arg2_reg;            /* (0x000) */
    volatile rt_uint32_t blksizecnt_reg;      /* (0x004) */
    volatile rt_uint32_t arg1_reg;            /* (0x008) */
    volatile rt_uint32_t cmdtm_reg;           /* (0x00C) */
    volatile rt_uint32_t resp0_reg;            /* (0x010) */
    volatile rt_uint32_t resp1_reg;            /* (0x014) */
    volatile rt_uint32_t resp2_reg;            /* (0x018) */
    volatile rt_uint32_t resp3_reg;            /* (0x01C) */
    volatile rt_uint32_t data_reg;           /* (0x020) */
    volatile rt_uint32_t status_reg;           /* (0x024) */
    volatile rt_uint32_t control0_reg;           /* (0x028) */
    volatile rt_uint32_t control1_reg;           /* (0x02C) */
    volatile rt_uint32_t interrupt_reg;            /* (0x030) */
    volatile rt_uint32_t irpt_mask_reg;            /* (0x034) */
    volatile rt_uint32_t irpt_en_reg;            /* (0x038) */
    volatile rt_uint32_t control2_reg;            /* (0x03C) */
    volatile rt_uint32_t reserved1[4];            /* (0x040) */
    volatile rt_uint32_t force_irpt_reg;            /* (0x050) */
    volatile rt_uint32_t reserved2[7];            /* (0x054) */
    volatile rt_uint32_t boot_timeout_reg;            /* (0x070) */
    volatile rt_uint32_t deg_sel_reg;            /* (0x074) */
    volatile rt_uint32_t reserved3[2];            /* (0x078) */
    volatile rt_uint32_t exrdfifo_cfg_reg;      /* (0x080) */
    volatile rt_uint32_t exrdfifo_cn_reg;       /* (0x084) */
    volatile rt_uint32_t tune_step_reg;        /* (0x088) */
    volatile rt_uint32_t tune_step_std_reg;    /* (0x08C) */
    volatile rt_uint32_t tune_step_ddr_reg;       /* (0x090) */
    volatile rt_uint32_t reserved4[23];            /* (0x094) */
    volatile rt_uint32_t spi_int_reg;            /* (0x0f0) */
    volatile rt_uint32_t reserved5[2];            /* (0x0f4) */
    volatile rt_uint32_t slotisr_ver_reg;            /* (0x0fC) */
};

typedef struct raspi_mmc *raspi_mmc_t;

#define MMC0    ((tina_mmc_t)MMC0_BASE_ADDR)


#define BIT(x)              (1<<(x))

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


/*
    SD CMD reg
REG[0-5] : Cmd ID
REG[6]   : Has response
REG[7]   : Long response
REG[8]   : Check response CRC
REG[9]   : Has data
REG[10]  : Write
REG[11]  : Steam mode
REG[12]  : Auto stop
REG[13]  : Wait previous over
REG[14]  : About cmd
REG[15]  : Send initialization
REG[21]  : Update clock
REG[31]  : Load cmd
*/


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

//#define SDXC_CHECK_CRC_CMD      BIT(19)
//
//#define SDXC_RESPONSE_CMD        BIT(6)
//#define SDXC_LONG_RESPONSE_CMD   BIT(7)
//#define SDXC_CHECK_CRC_CMD       BIT(8)
//#define SDXC_HAS_DATA_CMD        BIT(9)
//#define SDXC_WRITE_CMD           BIT(10)
//#define SDXC_STEAM_CMD           BIT(11)
//#define SDXC_AUTO_STOP_CMD       BIT(12)
//#define SDXC_WAIT_OVER_CMD       BIT(13)
//#define SDXC_ABOUT_CMD           BIT(14)
//#define SDXC_SEND_INIT_CMD       BIT(15)
//#define SDXC_UPDATE_CLOCK_CMD    BIT(21)
//#define SDXC_LOAD_CMD            BIT(31)

/* 
    SD status reg 
REG[0]   : FIFO_RX_LEVEL
REG[1]   : FIFO_TX_LEVEL
REG[2]   : FIFO_EMPTY
REG[3]   : FIFO_FULL
REG[4-7] : FSM_STA
REG[8]   : CARD_PRESENT
REG[9]   : CARD_BUSY
REG[10]  : FSM_BUSY
REG[11-16]: RESP_IDX 
REG[17-21]: FIFO_LEVEL
REG[31]   : DMA_REQ
*/

#define SDXC_CMD_INHIBIT    BIT(0)
#define SDXC_DAT_INHIBIT    BIT(1)
#define SDXC_DAT_ACTIVE     BIT(2)
#define SDXC_WRITE_TRANSFER     BIT(8)
#define SDXC_READ_TRANSFER     BIT(9)

//
//
//#define SDXC_FIFO_RX_LEVEL    BIT(0)
//#define SDXC_FIFO_TX_LEVEL    BIT(1)
//#define SDXC_FIFO_EMPTY       BIT(2)
//#define SDXC_FIFO_FULL        BIT(3)
//#define SDXC_CARD_PRESENT     BIT(8)
//#define SDXC_CARD_BUSY        BIT(9)
//#define SDXC_FSM_BUSY         BIT(10)
//#define SDXC_DMA_REQ          BIT(31)

struct mmc_des_v4p1
{
    rt_uint32_t                         : 1,
                    dic                 : 1, /* disable interrupt on completion                                    */
                    last_des            : 1, /* 1-this data buffer is the last buffer                              */
                    first_des           : 1, /* 1-data buffer is the first buffer,0-data buffer contained in the next descriptor is 1st buffer        */
                    des_chain           : 1, /* 1-the 2nd address in the descriptor is the next descriptor address */
                    end_of_ring         : 1, /* 1-last descriptor flag when using dual data buffer in descriptor   */
                                        : 24,
                    card_err_sum        : 1, /* transfer error flag                                                */
                    own                 : 1; /* des owner:1-idma owns it, 0-host owns it                           */

#define SDXC_DES_NUM_SHIFT 12  /* smhc2!! */
#define SDXC_DES_BUFFER_MAX_LEN (1 << SDXC_DES_NUM_SHIFT)
    rt_uint32_t data_buf1_sz     : 16,
                data_buf2_sz     : 16;
    rt_uint32_t buf_addr_ptr1;
    rt_uint32_t buf_addr_ptr2;
};

struct sdhci_cmd_t
{
    rt_uint32_t cmdidx;
    rt_uint32_t cmdarg;
    //const char* name;
   // rt_uint32_t code;
    rt_uint32_t resptype;
  //  rt_uint8_t rca;
  //  rt_uint32_t delay;
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

// Response types.
// Note that on the PI, the index and CRC are dropped, leaving 32 bits in RESP0.
#define RESP_NO    0     // No response
//#define RESP_R1    1     // 48  RESP0    contains card status
#define RESP_R1b  11     // 48  RESP0    contains card status, data line indicates busy
#define RESP_R2I   2     // 136 RESP0..3 contains 128 bit CID shifted down by 8 bits as no CRC
#define RESP_R2S  12     // 136 RESP0..3 contains 128 bit CSD shifted down by 8 bits as no CRC
//#define RESP_R3    3     // 48  RESP0    contains OCR register
//#define RESP_R6    6     // 48  RESP0    contains RCA and status bits 23,22,19,12:0
//#define RESP_R7    7     // 48  RESP0    contains voltage acceptance and check pattern

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


#endif
