/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _DRIVER_CHIP_SDMMC_SDMMC_H_
#define _DRIVER_CHIP_SDMMC_SDMMC_H_

#include "card.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SD_EXCLUSIVE_HOST

/* SD commands                           type  argument     response */
  /* class 0 */
/* This is basically the same command as for MMC with some quirks. */
#define SD_SEND_RELATIVE_ADDR           3       /* bcr                     R6, ask the card to publish a new relative address  */
#define SD_SEND_IF_COND                 8       /* bcr  [11:0] See below   R7, sends Sd memory card interface condition, for sd 2.0 */
#define SD_SWITCH_VOLTAGE               11      /* ac                      R1, switch to 1.8V bus signaling level  */

  /* class 10 */
#define SD_SWITCH                       6       /* adtc [31:0] See below   R1, checks swithcable function(mode 0),And swtich card function(mode 1), for sd 1.x  */

  /* class 5 */
#define SD_ERASE_WR_BLK_START           32       /* ac   [31:0] data addr   R1  */
#define SD_ERASE_WR_BLK_END             33       /* ac   [31:0] data addr   R1  */

  /* Application commands */
#define SD_APP_SET_BUS_WIDTH            6        /* ac   [1:0] bus width    R1  */
#define SD_APP_SD_STATUS                13       /* adtc                    R1  */
#define SD_APP_SEND_NUM_WR_BLKS         22       /* adtc                    R1  */
#define SD_APP_OP_COND                  41       /* bcr  [31:0] OCR         R3  */
#define SD_APP_SEND_SCR                 51       /* adtc                    R1  */

/* OCR bit definitions */
#define SD_OCR_S18R                     (1 << 24)    /* 1.8V switching request */
#define SD_ROCR_S18A                    SD_OCR_S18R  /* 1.8V switching accepted by card */
#define SD_OCR_XPC                      (1 << 28)    /* SDXC power control */
#define SD_OCR_CCS                      (1 << 30)    /* Card Capacity Status */

/*
 * SD_SWITCH argument format:
 *
 *      [31] Check (0) or switch (1)
 *      [30:24] Reserved (0)
 *      [23:20] Function group 6
 *      [19:16] Function group 5
 *      [15:12] Function group 4
 *      [11:8] Function group 3
 *      [7:4] Function group 2
 *      [3:0] Function group 1
 */

/*
 * SD_SEND_IF_COND argument format:
 *
 *  [31:12] Reserved (0)
 *  [11:8] Host Voltage Supply Flags
 *  [7:0] Check Pattern (0xAA)
 */

/*
 * SCR field definitions
 */
#define SCR_SPEC_VER_0                  0       /* Implements system specification 1.0 - 1.01 */
#define SCR_SPEC_VER_1                  1       /* Implements system specification 1.10 */
#define SCR_SPEC_VER_2                  2       /* Implements system specification 2.00-3.0X */

/*
 * SD bus widths
 */
#define SD_BUS_WIDTH_1                  0
#define SD_BUS_WIDTH_4                  2

/*
 * SD_SWITCH mode
 */
#define SD_SWITCH_CHECK                 0
#define SD_SWITCH_SET                   1

/*
 * SD_SWITCH function groups
 */
#define SD_SWITCH_GRP_ACCESS            0

/*
 * SD_SWITCH access modes
 */
#define SD_SWITCH_ACCESS_DEF            0
#define SD_SWITCH_ACCESS_HS             1

/*command index*/
/*basic commands*/
#define MMC_GO_IDLE_STATE               0       /* bc,rest all cards to idle state */
#define MMC_ALL_SEND_CID                2       /* bcr                     R2, asks any card to send CID numbers  */
#define MMC_SET_RELATIVE_ADDR           3       /*  bcr,ask the card to publish a new relative address,R6  */
#define MMC_SET_DSR                     4       /* bc,program the DSR of all cards,for sd 2.0  */
#define MMC_SELECT_CARD                 7       /* ac   [31:16] RCA        R1, select or deselect one card  */
#define MMC_SEND_EXT_CSD                8       /* adtc,the card sends it's ex_csd as a block of data,R1 */
#define MMC_SEND_CSD                    9       /* ac   [31:16] RCA        R2, addressed card send CSD  */
#define MMC_SEND_CID                    10      /* ac, addressed card send CID,R2  */
#define MMC_READ_DATA_UNTIL_STOP        11      /* atdc,read data stream from catd until a STOP_TRANSMITISSION follows,R1  */
#define MMC_STOP_TRANSMISSION           12      /* ac, termilate a multiple block read/write operation,R1b  */
#define MMC_SEND_STATUS                 13      /* ac, addressed card send its status regesiter,R1  */
#define MMC_GO_INACTIVE_STATE           15      /* ac, sets the card to inactive state  */
#define MMC_SEND_TUNING_PATTERN         19      /* adtc, send 64 bytes pattern for sdr50 and sdr104 mode  */

/* erase commands*/
#define MMC_ERASE_WR_BLK_START          32      /* ac,sets the address of the first write bloock to be erased,R1  */
#define MMC_ERASE_WR_BLK_END            33      /* ac,sets the address of the last write bloock to be erased,R1  */

/*MMC private command*/
#define MMC_SEND_OP_COND                1       /* bcr,Activates the card's initialization process,R3  */
#define MMC_SWITCH                      6       /* ac,switch the mode of operation of the selected card or modifies tge EXT_CSD,R1b  */
#define MMC_BUSTEST_R                   14      /* adtc,a host reads the reversed testing data pattern from a card,R1  */
#define MMC_BUSTEST_W                   19      /* adtc,a host sends the bus teset data pattern to a card,R1  */

/*sd io command*/
#define IO_SEND_OP_COND                 5       /* for SD IO.similar to ACMD41 for sd mem  */
#define IO_RW_DIRECT                    52
#define IO_RW_EXTENDED                  53
#define SD_IO_CMD54                     54

  /* class 2 */
#define MMC_SET_BLOCKLEN                16      /* ac   [31:0] block len   R1, select a block length for all read/write cmds  */
#define MMC_READ_SINGLE_BLOCK           17      /* adtc [31:0] data addr   R1, reads a block of the size seclected by SET_BLOCKLEN  */
#define MMC_READ_MULTIPLE_BLOCK         18      /* adtc [31:0] data addr   R1, continuously send blocks of data until interrupted by a stop transmission commmad  */
#define MMC_SEND_TUNING_BLOCK           19      /* adtc                    R1  */
#define MMC_SEND_TUNING_BLOCK_HS200     21      /* adtc R1  */

  /* class 3 */
#define MMC_WRITE_DAT_UNTIL_STOP        20      /* adtc [31:0] data addr   R1  */

  /* class 4 */
#define MMC_SET_BLOCK_COUNT             23      /* adtc [31:0] data addr   R1  */
#define MMC_WRITE_SINGLE_BLOCK          24      /* adtc [31:0] data addr   R1, writes a block of the size seclected by SET_BLOCKLEN  */
#define MMC_WRITE_MULTIPLE_BLOCK        25      /* adtc                    R1, continuously writes blocks of data until interrupted by a stop transmission commmad  */
#define MMC_PROGRAM_CID                 26      /* adtc                    R1  */
#define MMC_PROGRAM_CSD                 27      /* adtc                    R1, program the programmable bits of CSD  */

  /* class 6 */
#define MMC_SET_WRITE_PROT              28      /* ac   [31:0] data addr   R1b, sets the write protect bit of the addressed group */
#define MMC_CLR_WRITE_PROT              29      /* ac   [31:0] data addr   R1b, clears the write protect bit of the addressed group */
#define MMC_SEND_WRITE_PROT             30      /* adtc [31:0] wpdata addr R1, ask the card to send status of the write protection bits  */

  /* class 5 */
#define MMC_ERASE_GROUP_START           35      /* ac   [31:0] data addr   R1  */
#define MMC_ERASE_GROUP_END             36      /* ac   [31:0] data addr   R1  */
#define MMC_ERASE                       38      /* ac                      R1b, erase all selected write blocks */

  /* class 9 */
#define MMC_FAST_IO                     39      /* ac   <Complex>          R4, used to read or write 8 bit registers  */
#define MMC_GO_IRQ_STATE                40      /* bcr                     R5, sets the system info interrupt mode  */

  /* class 7 */
#define MMC_LOCK_UNLOCK                 42      /* adtc                    R1b, lock or unlock sd card */

  /* class 8 */
#define MMC_APP_CMD                     55      /* ac   [31:16] RCA        R1, indicates the next cmd is an specific cmd  */
#define MMC_GEN_CMD                     56      /* adtc [0] RD/WR          R1, send or get a block of data  */

static inline uint32_t mmc_op_multi(uint32_t opcode)
{
    return opcode == MMC_WRITE_MULTIPLE_BLOCK ||
           opcode == MMC_READ_MULTIPLE_BLOCK;
}

/*
 * MMC_SWITCH argument format:
 *
 *  [31:26] Always 0
 *  [25:24] Access Mode
 *  [23:16] Location of target Byte in EXT_CSD
 *  [15:08] Value Byte
 *  [07:03] Always 0
 *  [02:00] Command Set
 */

/*
  MMC status in R1, for native mode (SPI bits are different)
  Type
    e : error bit
    s : status bit
    r : detected and set for the actual command response
    x : detected and set during command execution. the host must poll
            the card by sending status command in order to read these bits.
  Clear condition
    a : according to the card state
    b : always related to the previous command. Reception of
            a valid command will clear it (with a delay of one command)
    c : clear by read
 */

#define R1_OUT_OF_RANGE                 (1 << 31)       /* er, c */
#define R1_ADDRESS_ERROR                (1 << 30)       /* erx, c */
#define R1_BLOCK_LEN_ERROR              (1 << 29)       /* er, c */
#define R1_ERASE_SEQ_ERROR              (1 << 28)       /* er, c */
#define R1_ERASE_PARAM                  (1 << 27)       /* ex, c */
#define R1_WP_VIOLATION                 (1 << 26)       /* erx, c */
#define R1_CARD_IS_LOCKED               (1 << 25)       /* sx, a */
#define R1_LOCK_UNLOCK_FAILED           (1 << 24)       /* erx, c */
#define R1_COM_CRC_ERROR                (1 << 23)       /* er, b */
#define R1_ILLEGAL_COMMAND              (1 << 22)       /* er, b */
#define R1_CARD_ECC_FAILED              (1 << 21)       /* ex, c */
#define R1_CC_ERROR                     (1 << 20)       /* erx, c */
#define R1_ERROR                        (1 << 19)       /* erx, c */
#define R1_UNDERRUN                     (1 << 18)       /* ex, c */
#define R1_OVERRUN                      (1 << 17)       /* ex, c */
#define R1_CID_CSD_OVERWRITE            (1 << 16)       /* erx, c, CID/CSD overwrite */
#define R1_WP_ERASE_SKIP                (1 << 15)       /* sx, c */
#define R1_CARD_ECC_DISABLED            (1 << 14)       /* sx, a */
#define R1_ERASE_RESET                  (1 << 13)       /* sr, c */
#define R1_STATUS(x)                    (x & 0xFFFFE000)
#define R1_CURRENT_STATE(x)             ((x & 0x00001E00) >> 9) /* sx, b (4 bits) */
#define R1_READY_FOR_DATA               (1 << 8)        /* sx, a */
#define R1_SWITCH_ERROR                 (1 << 7)        /* sx, c */
#define R1_APP_CMD                      (1 << 5)        /* sr, c */

#define R1_STATE_IDLE                   0
#define R1_STATE_READY                  1
#define R1_STATE_IDENT                  2
#define R1_STATE_STBY                   3
#define R1_STATE_TRAN                   4
#define R1_STATE_DATA                   5
#define R1_STATE_RCV                    6
#define R1_STATE_PRG                    7
#define R1_STATE_DIS                    8

/*ce-ata command*/
#define CEATA_RW_MULTIPLE_REGISTER      60
#define CEATA_RW_MULTIPLE_BLOCK         61

/*application specific commands used by sd mem*/
#define SET_BUS_WIDTH                   6      /* ac,define the bus width(00 = 1bit, 10 = 4bit),R1 */
#define SD_STATUS                       13     /* adtc,send the sd card status,R1 */
#define SEND_NUM_WR_BLOCKS              22     /* adtc,send the number of written write blocks,R1 */
#define SET_WR_BLK_ERASE_CNT            23     /* ac,set the number of write blocks to be pre-erased before writing,R1 */
#define SD_APP_OP_COND                  41     /* bcr,asks the accessed card to send its OCR(operating conditon register) content,R3 */
#define SET_CLR_CARD_DETECT             42     /* ac,connect or disconnect the pull up resistor of the card for card detect,R1 */
#define SEND_SCR                        51     /* adtc,reads the SCR(sd configure register),R1 */

/* MMC/SD in SPI mode reports R1 status always, and R2 for SEND_STATUS
 * R1 is the low order byte; R2 is the next highest byte, when present.
 */
#define R1_SPI_IDLE                     (1 << 0)
#define R1_SPI_ERASE_RESET              (1 << 1)
#define R1_SPI_ILLEGAL_COMMAND          (1 << 2)
#define R1_SPI_COM_CRC                  (1 << 3)
#define R1_SPI_ERASE_SEQ                (1 << 4)
#define R1_SPI_ADDRESS                  (1 << 5)
#define R1_SPI_PARAMETER                (1 << 6)

/* R1 bit 7 is always zero */
#define R2_SPI_CARD_LOCKED              (1 << 8)
#define R2_SPI_WP_ERASE_SKIP            (1 << 9)            /* or lock/unlock fail */
#define R2_SPI_LOCK_UNLOCK_FAIL         R2_SPI_WP_ERASE_SKIP
#define R2_SPI_ERROR                    (1 << 10)
#define R2_SPI_CC_ERROR                 (1 << 11)
#define R2_SPI_CARD_ECC_ERROR           (1 << 12)
#define R2_SPI_WP_VIOLATION             (1 << 13)
#define R2_SPI_ERASE_PARAM              (1 << 14)
#define R2_SPI_OUT_OF_RANGE             (1 << 15)           /* or CSD overwrite */
#define R2_SPI_CSD_OVERWRITE            R2_SPI_OUT_OF_RANGE

#define CEATA_INDENTIFY_DEVICE          0xec
#define CEATA_READ_DMA_EXT              0x25
#define CEATA_WRITE_DMA_EXT             0x35
#define CEATA_STANBY_IMMIDIATE          0xe0
#define CEATA_FLUSH_CACHE_EXT           0Xea

/*
 * OCR bits are mostly in host.h
 */
#define MMC_CARD_BUSY                   0x80000000  /* Card Power up status bit */

/* Card Command Classes (CCC) */
#define CCC_BASIC                       (1<<0)  /* (0) Basic protocol functions */
                                        /* (CMD0,1,2,3,4,7,9,10,12,13,15) */
                                        /* (and for SPI, CMD58,59) */
#define CCC_STREAM_READ                 (1<<1)  /* (1) Stream read commands */
                                        /* (CMD11) */
#define CCC_BLOCK_READ                  (1<<2)  /* (2) Block read commands */
                                        /* (CMD16,17,18) */
#define CCC_STREAM_WRITE                (1<<3)  /* (3) Stream write commands */
                                        /* (CMD20) */
#define CCC_BLOCK_WRITE                 (1<<4)  /* (4) Block write commands */
                                        /* (CMD16,24,25,26,27) */
#define CCC_ERASE                       (1<<5)  /* (5) Ability to erase blocks */
                                        /* (CMD32,33,34,35,36,37,38,39) */
#define CCC_WRITE_PROT                  (1<<6)  /* (6) Able to write protect blocks */
                                        /* (CMD28,29,30) */
#define CCC_LOCK_CARD                   (1<<7)  /* (7) Able to lock down card */
                                        /* (CMD16,CMD42) */
#define CCC_APP_SPEC                    (1<<8)  /* (8) Application specific */
                                        /* (CMD55,56,57,ACMD*) */
#define CCC_IO_MODE                     (1<<9)  /* (9) I/O mode */
                                        /* (CMD5,39,40,52,53) */
#define CCC_SWITCH                      (1<<10) /* (10) High speed switch */
                                        /* (CMD6,34,35,36,37,50) */
                                        /* (11) Reserved */
                                        /* (CMD?) */

/* CSD field definitions */
#define MMC_CSD_STRUCT_VER_1_0          0       /* Valid for system specification 1.0 - 1.2 */
#define MMC_CSD_STRUCT_VER_1_1          1       /* Valid for system specification 1.4 - 2.2 */
#define MMC_CSD_STRUCT_VER_1_2          2       /* Valid for system specification 3.1 - 3.2 - 3.31 - 4.0 - 4.1 */
#define MMC_CSD_STRUCT_EXT_CSD          3       /* Version is coded in CSD_STRUCTURE in EXT_CSD */

#define MMC_CSD_SPEC_VER_0              0       /* Implements system specification 1.0 - 1.2 */
#define MMC_CSD_SPEC_VER_1              1       /* Implements system specification 1.4 */
#define MMC_CSD_SPEC_VER_2              2       /* Implements system specification 2.0 - 2.2 */
#define MMC_CSD_SPEC_VER_3              3       /* Implements system specification 3.1 - 3.2 - 3.31 */
#define MMC_CSD_SPEC_VER_4              4       /* Implements system specification 4.0 - 4.1 */

/* EXT_CSD fields */
#define MMC_EXT_CSD_BOOT_BUS_COND       177     /* R/W */
#define MMC_EXT_CSD_PART_CONF           179     /* R/W */
#define MMC_EXT_CSD_BUS_WIDTH           183     /* R/W */
#define MMC_EXT_CSD_HS_TIMING           185     /* R/W */
#define MMC_EXT_CSD_CARD_TYPE           196     /* RO */
#define MMC_EXT_CSD_REV                 192     /* RO */
#define MMC_EXT_CSD_SEC_CNT             212     /* RO, 4 bytes */

/* EXT_CSD field definitions */
#define MMC_EXT_CSD_CMD_SET_NORMAL      (1<<0)
#define MMC_EXT_CSD_CMD_SET_SECURE      (1<<1)
#define MMC_EXT_CSD_CMD_SET_CPSECURE    (1<<2)

#define MMC_EXT_CSD_CARD_TYPE_26        (1<<0)  /* Card can run at 26MHz */
#define MMC_EXT_CSD_CARD_TYPE_52        (1<<1)  /* Card can run at 52MHz */

#define MMC_EXT_CSD_BUS_WIDTH_1         0       /* Card is in 1 bit mode */
#define MMC_EXT_CSD_BUS_WIDTH_4         1       /* Card is in 4 bit mode */
#define MMC_EXT_CSD_BUS_WIDTH_8         2       /* Card is in 8 bit mode */
#define MMC_EXT_CSD_BUS_WIDTH_4_DDR     5       /* Card is in 4 bit mode in DDR mode */
#define MMC_EXT_CSD_BUS_WIDTH_8_DDR     6       /* Card is in 8 bit mode in DDR mode */

/* MMC_SWITCH access modes */
#define MMC_SWITCH_MODE_CMD_SET         0x00    /* Change the command set */
#define MMC_SWITCH_MODE_SET_BITS        0x01    /* Set bits which are 1 in value */
#define MMC_SWITCH_MODE_CLEAR_BITS      0x02    /* Clear bits which are 1 in value */
#define MMC_SWITCH_MODE_WRITE_BYTE      0x03    /* Set target to value */

/* MMC_SWITCH boot modes */
#define MMC_SWITCH_MMCPART_NOAVAILABLE  (0xff)
#define MMC_SWITCH_PART_ACCESS_MASK     (0x7)
#define MMC_SWITCH_PART_SUPPORT         (0x1)
#define MMC_SWITCH_PART_BOOT_PART_MASK  (0x7 << 3)
#define MMC_SWITCH_PART_BOOT_PART_NONE  (0x0)
#define MMC_SWITCH_PART_BOOT_PART_1     (0x1)
#define MMC_SWITCH_PART_BOOT_PART_2     (0x2)
#define MMC_SWITCH_PART_BOOT_USER       (0x7)
#define MMC_SWITCH_PART_BOOT_ACK_MASK   (0x1 << 6)
#define MMC_SWITCH_PART_BOOT_ACK_ENB    (0x1)

/* MMC_SWITCH boot condition */
#define MMC_SWITCH_MMCBOOT_BUS_NOAVAILABLE     (0xff)
#define MMC_SWITCH_BOOT_MODE_MASK              (0x3 << 3)
#define MMC_SWITCH_BOOT_SDR_NORMAL             (0x0)
#define MMC_SWITCH_BOOT_SDR_HS                 (0x1)
#define MMC_SWITCH_BOOT_DDR                    (0x2)
#define MMC_SWITCH_BOOT_RST_BUS_COND_MASK      (0x1 << 2)
#define MMC_SWITCH_BOOT_RST_BUS_COND           (0x0)
#define MMC_SWITCH_BOOT_RETAIN_BUS_COND        (0x1)
#define MMC_SWITCH_BOOT_BUS_WIDTH_MASK         (0x3 << 0)
#define MMC_SWITCH_BOOT_BUS_SDRx1_DDRx4        (0x0)
#define MMC_SWITCH_BOOT_BUS_SDRx4_DDRx4        (0x1)
#define MMC_SWITCH_BOOT_BUS_SDRx8_DDRx8        (0x2)

/* SD_SWITCH function groups */
#define SD_SWITCH_GRP_ACCESS_MODE               0
#define SD_SWITCH_GRP_CMD_SYSTEM                1
#define SD_SWITCH_GRP_DRV_STRENGTH              2
#define SD_SWITCH_GRP_CUR_LIMIT                 3

/* SD_SWITCH access modes */
#define SD_SWITCH_ACCESS_DEF_SDR12              0
#define SD_SWITCH_ACCESS_HS_SDR25               1
#define SD_SWITCH_ACCESS_SDR50                  2
#define SD_SWITCH_ACCESS_SDR104                 3
#define SD_SWITCH_ACCESS_DDR50                  4

/* SD_SWITCH cmd system */
#define SD_SWITCH_CMDSYS_DEF                    0
#define SD_SWITCH_CMDSYS_EC                     1
#define SD_SWITCH_CMDSYS_OTP                    3
#define SD_SWITCH_CMDSYS_ASSD                   4
#define SD_SWITCH_CMDSYS_ESD                    0xc

/* SD_SWITCH driver strength */
#define SD_SWITCH_DRVSTR_DEF_TB                 0
#define SD_SWITCH_DRVSTR_DEF_TA                 1
#define SD_SWITCH_DRVSTR_DEF_TC                 2
#define SD_SWITCH_DRVSTR_DEF_TD                 3

/* SD_SWITCH current limit */
#define SD_SWITCH_CURLMT_DEF_200MA              0
#define SD_SWITCH_CURLMT_DEF_400MA              1
#define SD_SWITCH_CURLMT_DEF_600MA              2
#define SD_SWITCH_CURLMT_DEF_800MA              3

/**
 * @brief read SD card.
 * @param card:
 *        @arg card->card handler.
 * @param buf:
 *        @arg buf->for store readed data.
 * @param sblk:
 *        @arg sblk->start block num.
 * @param nblk:
 *        @arg nblk->number of blocks.
 * @retval  0 if success or other if failed.
 */
extern int32_t mmc_block_read(struct mmc_card *card, uint8_t *buf, uint64_t sblk, uint32_t nblk);

/**
 * @brief write SD card.
 * @param card:
 *        @arg card->card handler.
 * @param buf:
 *        @arg buf->data will be write.
 * @param sblk:
 *        @arg sblk->start block num.
 * @param nblk:
 *        @arg nblk->number of blocks.
 * @retval  0 if success or other if failed.
 */
extern int32_t mmc_block_write(struct mmc_card *card, const uint8_t *buf, uint64_t sblk, uint32_t nblk);

/**
 * @brief scan or rescan SD card.
 * @param card:
 *        @arg card->card handler.
 * @param sdc_id:
 *        @arg sdc_id->SDC ID which card on.
 * @retval  0 if success or other if failed.
 */
extern int32_t mmc_rescan(struct mmc_card *card, uint32_t sdc_id);

/**
 * @brief deinit SD card.
 * @param card:
 *        @arg card->card handler.
 * @retval  0 if success or other if failed.
 */
extern int32_t mmc_card_deinit(struct mmc_card *card);

/**
 * @brief malloc for card_info.
 * @param card_id:
 *        @arg card ID.
 * @retval  0 if success or other if failed.
 */
extern int32_t mmc_card_create(uint8_t card_id, SDCard_InitTypeDef *param);

/**
 * @brief free for card_info.
 * @param card_id:
 *        @arg card ID.
 * @retval  0 if success or other if failed.
 */
extern int32_t mmc_card_delete(uint8_t card_id);

/**
 * @brief get pointer of mmc_card.
 * @param card_id:
 *        @arg card ID.
 * @retval  pointer of mmc_card if success or NULL if failed.
 */
extern struct mmc_card* mmc_card_open(uint8_t card_id);

/**
 * @brief close mmc_card.
 * @param card_id:
 *        @arg card ID.
 * @retval  0 if success or other if failed.
 */
extern int32_t mmc_card_close(uint8_t card_id);
extern struct mmc_card_info* mmc_card_save(uint8_t card_id);
extern int32_t mmc_card_restore(struct mmc_card_info *s_card_info);

#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_CHIP_SDMMC_SDMMC_H_ */
