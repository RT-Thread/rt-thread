/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author		Notes
 * 2011-07-25     weety		first version
 */

#ifndef __CMD_H__
#define __CMD_H__

#ifdef __cplusplus
extern "C" {
#endif

   /* class 1 */
#define GO_IDLE_STATE         0   /* bc                          */
#define SEND_OP_COND          1   /* bcr  [31:0] OCR         R3  */
#define ALL_SEND_CID          2   /* bcr                     R2  */
#define SET_RELATIVE_ADDR     3   /* ac   [31:16] RCA        R1  */
#define SET_DSR               4   /* bc   [31:16] RCA            */
#define SWITCH                6   /* ac   [31:0] See below   R1b */
#define SELECT_CARD           7   /* ac   [31:16] RCA        R1  */
#define SEND_EXT_CSD          8   /* adtc                    R1  */
#define SEND_CSD              9   /* ac   [31:16] RCA        R2  */
#define SEND_CID             10   /* ac   [31:16] RCA        R2  */
#define READ_DAT_UNTIL_STOP  11   /* adtc [31:0] dadr        R1  */
#define STOP_TRANSMISSION    12   /* ac                      R1b */
#define SEND_STATUS          13   /* ac   [31:16] RCA        R1  */
#define GO_INACTIVE_STATE    15   /* ac   [31:16] RCA            */
#define SPI_READ_OCR         58   /* spi                  spi_R3 */
#define SPI_CRC_ON_OFF       59   /* spi  [0:0] flag      spi_R1 */

  /* class 2 */
#define SET_BLOCKLEN         16   /* ac   [31:0] block len   R1  */
#define READ_SINGLE_BLOCK    17   /* adtc [31:0] data addr   R1  */
#define READ_MULTIPLE_BLOCK  18   /* adtc [31:0] data addr   R1  */

  /* class 3 */
#define WRITE_DAT_UNTIL_STOP 20   /* adtc [31:0] data addr   R1  */

  /* class 4 */
#define SET_BLOCK_COUNT      23   /* adtc [31:0] data addr   R1  */
#define WRITE_BLOCK          24   /* adtc [31:0] data addr   R1  */
#define WRITE_MULTIPLE_BLOCK 25   /* adtc                    R1  */
#define PROGRAM_CID          26   /* adtc                    R1  */
#define PROGRAM_CSD          27   /* adtc                    R1  */

  /* class 6 */
#define SET_WRITE_PROT       28   /* ac   [31:0] data addr   R1b */
#define CLR_WRITE_PROT       29   /* ac   [31:0] data addr   R1b */
#define SEND_WRITE_PROT      30   /* adtc [31:0] wpdata addr R1  */

  /* class 5 */
#define ERASE_GROUP_START    35   /* ac   [31:0] data addr   R1  */
#define ERASE_GROUP_END      36   /* ac   [31:0] data addr   R1  */
#define ERASE                38   /* ac                      R1b */

  /* class 9 */
#define FAST_IO              39   /* ac   <Complex>          R4  */
#define GO_IRQ_STATE         40   /* bcr                     R5  */

  /* class 7 */
#define LOCK_UNLOCK          42   /* adtc                    R1b */

  /* class 8 */
#define APP_CMD              55   /* ac   [31:16] RCA        R1  */
#define GEN_CMD              56   /* adtc [0] RD/WR          R1  */


/* SD commands                           type  argument     response */
  /* class 0 */
/* This is basically the same command as for MMC with some quirks. */
#define SD_SEND_RELATIVE_ADDR     3   /* bcr                     R6  */
#define SD_SEND_IF_COND           8   /* bcr  [11:0] See below   R7  */

  /* class 10 */
#define SD_SWITCH                 6   /* adtc [31:0] See below   R1  */

  /* Application commands */
#define SD_APP_SET_BUS_WIDTH      6   /* ac   [1:0] bus width    R1  */
#define SD_APP_SEND_NUM_WR_BLKS  22   /* adtc                    R1  */
#define SD_APP_OP_COND           41   /* bcr  [31:0] OCR         R3  */
#define SD_APP_SEND_SCR          51   /* adtc                    R1  */

#define SCR_SPEC_VER_0		0	/* Implements system specification 1.0 - 1.01 */
#define SCR_SPEC_VER_1		1	/* Implements system specification 1.10 */
#define SCR_SPEC_VER_2		2	/* Implements system specification 2.00 */


/* SDIO commands                                          type  argument     response */
#define SD_IO_SEND_OP_COND          5 /* bcr  [23:0] OCR         R4  */
#define SD_IO_RW_DIRECT            52 /* ac   [31:0] See below   R5  */
#define SD_IO_RW_EXTENDED          53 /* adtc [31:0] See below   R5  */


/* CMD52 arguments */
#define SDIO_ARG_CMD52_READ             (0<<31)
#define SDIO_ARG_CMD52_WRITE            (1u<<31)
#define SDIO_ARG_CMD52_FUNC_SHIFT       28
#define SDIO_ARG_CMD52_FUNC_MASK        0x7
#define SDIO_ARG_CMD52_RAW_FLAG         (1u<<27)
#define SDIO_ARG_CMD52_REG_SHIFT        9
#define SDIO_ARG_CMD52_REG_MASK         0x1ffff
#define SDIO_ARG_CMD52_DATA_SHIFT       0
#define SDIO_ARG_CMD52_DATA_MASK        0xff
#define SDIO_R5_DATA(resp)            ((resp)[0] & 0xff)

/* CMD53 arguments */
#define SDIO_ARG_CMD53_READ             (0<<31)
#define SDIO_ARG_CMD53_WRITE            (1u<<31)
#define SDIO_ARG_CMD53_FUNC_SHIFT       28
#define SDIO_ARG_CMD53_FUNC_MASK        0x7
#define SDIO_ARG_CMD53_BLOCK_MODE       (1u<<27)
#define SDIO_ARG_CMD53_INCREMENT        (1u<<26)
#define SDIO_ARG_CMD53_REG_SHIFT        9
#define SDIO_ARG_CMD53_REG_MASK         0x1ffff
#define SDIO_ARG_CMD53_LENGTH_SHIFT     0
#define SDIO_ARG_CMD53_LENGTH_MASK      0x1ff
#define SDIO_ARG_CMD53_LENGTH_MAX       511


#ifdef __cplusplus
}
#endif

#endif
