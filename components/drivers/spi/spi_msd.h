/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-04-17     Bernard      first version.
 */

#ifndef SPI_MSD_H_INCLUDED
#define SPI_MSD_H_INCLUDED

#include <stdint.h>
#include <drivers/spi.h>

/* SD command (SPI mode) */
#define GO_IDLE_STATE                       0   /* CMD0  R1  */
#define SEND_OP_COND                        1   /* CMD1  R1  */
#define SWITCH_FUNC                         6   /* CMD6  R1  */
#define SEND_IF_COND                        8   /* CMD8  R7  */
#define SEND_CSD                            9   /* CMD9  R1  */
#define SEND_CID                            10  /* CMD10 R1  */
#define STOP_TRANSMISSION                   12  /* CMD12 R1B */
#define SEND_STATUS                         13  /* CMD13 R2  */
#define SET_BLOCKLEN                        16  /* CMD16 R1  */
#define READ_SINGLE_BLOCK                   17  /* CMD17 R1  */
#define READ_MULTIPLE_BLOCK                 18  /* CMD18 R1  */
#define WRITE_BLOCK                         24  /* CMD24 R1  */
#define WRITE_MULTIPLE_BLOCK                25  /* CMD25 R1  */
#define PROGRAM_CSD                         27  /* CMD27 R1  */
#define SET_WRITE_PROT                      28  /* CMD28 R1B */
#define CLR_WRITE_PROT                      29  /* CMD29 R1B */
#define SEND_WRITE_PROT                     30  /* CMD30 R1  */
#define ERASE_WR_BLK_START_ADDR             32  /* CMD32 R1  */
#define ERASE_WR_BLK_END_ADDR               33  /* CMD33 R1  */
#define ERASE                               38  /* CMD38 R1B */
#define LOCK_UNLOCK                         42  /* CMD42 R1  */
#define APP_CMD                             55  /* CMD55 R1  */
#define GEN_CMD                             56  /* CMD56 R1  */
#define READ_OCR                            58  /* CMD58 R3  */
#define CRC_ON_OFF                          59  /* CMD59 R1  */

/* Application-Specific Command */
#define SD_STATUS                           13  /* ACMD13 R2 */
#define SEND_NUM_WR_BLOCKS                  22  /* ACMD22 R1 */
#define SET_WR_BLK_ERASE_COUNT              23  /* ACMD23 R1 */
#define SD_SEND_OP_COND                     41  /* ACMD41 R1 */
#define SET_CLR_CARD_DETECT                 42  /* ACMD42 R1 */
#define SEND_SCR                            51  /* ACMD51 R1 */

/* Start Data tokens  */
/* Tokens (necessary because at nop/idle (and CS active) only 0xff is on the data/command line) */
#define MSD_TOKEN_READ_START                0xFE  /* Data token start byte, Start Single Block Read */
#define MSD_TOKEN_WRITE_SINGLE_START        0xFE  /* Data token start byte, Start Single Block Write */

#define MSD_TOKEN_WRITE_MULTIPLE_START      0xFC  /* Data token start byte, Start Multiple Block Write */
#define MSD_TOKEN_WRITE_MULTIPLE_STOP       0xFD  /* Data toke stop byte, Stop Multiple Block Write */

/* MSD reponses and error flags */
#define MSD_RESPONSE_NO_ERROR               0x00
#define MSD_IN_IDLE_STATE                   0x01
#define MSD_ERASE_RESET                     0x02
#define MSD_ILLEGAL_COMMAND                 0x04
#define MSD_COM_CRC_ERROR                   0x08
#define MSD_ERASE_SEQUENCE_ERROR            0x10
#define MSD_ADDRESS_ERROR                   0x20
#define MSD_PARAMETER_ERROR                 0x40
#define MSD_RESPONSE_FAILURE                0xFF

/* Data response error */
#define MSD_DATA_OK                         0x05
#define MSD_DATA_CRC_ERROR                  0x0B
#define MSD_DATA_WRITE_ERROR                0x0D
#define MSD_DATA_OTHER_ERROR                0xFF
#define MSD_DATA_RESPONSE_MASK              0x1F
#define MSD_GET_DATA_RESPONSE(res)          (res & MSD_DATA_RESPONSE_MASK)

#define MSD_CMD_LEN                         6           /**< command, arg and crc. */
#define MSD_RESPONSE_MAX_LEN                5           /**< response max len  */
#define MSD_CSD_LEN                         16          /**< SD crad CSD register len */
#define SECTOR_SIZE                         512         /**< sector size, default 512byte */

/* card try timeout, unit: ms */
#define CARD_TRY_TIMES                      3000
#define CARD_TRY_TIMES_ACMD41               800
#define CARD_WAIT_TOKEN_TIMES               800

#define MSD_USE_PRE_ERASED                              /**< id define MSD_USE_PRE_ERASED, before CMD25, send ACMD23 */

/**
 * SD/MMC card type
 */
typedef enum
{
    MSD_CARD_TYPE_UNKNOWN = 0,                      /**< unknown */
    MSD_CARD_TYPE_MMC,                              /**< MultiMedia Card */
    MSD_CARD_TYPE_SD_V1_X,                          /**< Ver 1.X  Standard Capacity SD Memory Card */
    MSD_CARD_TYPE_SD_V2_X,                          /**< Ver 2.00 or later Standard Capacity SD Memory Card */
    MSD_CARD_TYPE_SD_SDHC,                          /**< High Capacity SD Memory Card */
    MSD_CARD_TYPE_SD_SDXC,                          /**< later Extended Capacity SD Memory Card */
}msd_card_type;

typedef enum
{
    response_type_unknown = 0,
    response_r1,
    response_r1b,
    response_r2,
    response_r3,
    response_r4,
    response_r5,
    response_r7,
}response_type;

struct msd_device
{
    struct rt_device                parent;      /**< RT-Thread device struct */
    struct rt_device_blk_geometry   geometry;    /**< sector size, sector count */
    struct rt_spi_device *          spi_device;  /**< SPI interface */
    msd_card_type                   card_type;   /**< card type: MMC SD1.x SD2.0 SDHC SDXC */
    uint32_t                        max_clock;   /**< MAX SPI clock */
};

extern rt_err_t msd_init(const char * sd_device_name, const char * spi_device_name);

#endif // SPI_MSD_H_INCLUDED
