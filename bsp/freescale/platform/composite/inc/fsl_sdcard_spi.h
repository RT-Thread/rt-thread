/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_SDCARD_SPI_H__
#define __FSL_SDCARD_SPI_H__

#include "fsl_sdmmc_card.h"

/*! @addtogroup sdspi_carddrv_data_types */
/*! @{ */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef enum _sdspi_status_t
{
    kStatus_SDSPI_NoError = 0,              /*!< No Error */
    kStatus_SDSPI_Failed,                   /*!< General failure */
    kStatus_SDSPI_TransferFailed,           /*!< Transfer failed */
    kStatus_SDSPI_CardIsBusyError,          /*!< Card busy */
    kStatus_SDSPI_OutOfMemory,              /*!< Out of memory */
    kStatus_SDSPI_TimeoutError,             /*!< Time out */
    kStatus_SDSPI_WriteProtected,           /*!< Write protected */
    kStatus_SDSPI_NotSupportYet,            /*!< Not support */
} sdspi_status_t;

typedef enum _sdspi_response_type {
    kSdSpiRespTypeR1 = 0,                   /*!< Response 1 */
    kSdSpiRespTypeR1b,                      /*!< Response 1 with busy */
    kSdSpiRespTypeR2,                       /*!< Response 2 */
    kSdSpiRespTypeR3,                       /*!< Response 3 */
    kSdSpiRespTypeR7,                       /*!< Response 7 */
} sdspi_response_type_t;

typedef struct SdSpiDevice {
    uint32_t spiInstance;                   /*!< SPI master instance */
    struct SdSpiOps *ops;                   /*!< SPI operating struct pointer */
    void *spiState;                         /*!< SPI specific state */
    void *spiDevice;                        /*!< SPI specific device */
    uint32_t busBaudRate;
} sdspi_spi_t;

typedef struct SdSpiOps {
    uint32_t (*getMaxFrequency)(sdspi_spi_t *spi);      /*!< Get max frequency of SPI */
    uint32_t (*setFrequency)(sdspi_spi_t *spi, uint32_t frequency); /*!< Set frequency of SPI */
    uint32_t (*exchange)(sdspi_spi_t *spi, const uint8_t *in, uint8_t *out, uint32_t size); /*!< Exchange data over SPI */
    uint8_t (*sendWord)(sdspi_spi_t *spi, uint8_t word);        /*!< Send one word and fetch on return */
} sdspi_ops_t;

/*!
 * @brief SD Card for SPI Structure
 *
 * Defines the card structure including the necessary fields to identify and
 * describe the card.
 */
typedef struct SdSpiCard {
    sdcard_version_t version;                           /*!< Card version */
    uint32_t caps;                                      /*!< Card capacity */
#define SDSPI_CAPS_SDHC     (1 << 0)                    /*!< High capacity */
#define SDSPI_CAPS_SDXC     (1 << 1)                    /*!< Extended capacity */
#define SDSPI_CAPS_ACCESS_IN_BLOCK (1 << 2)
    uint32_t state;                                     /*!< Card state */
#define SDSPI_STATE_WRITE_PROTECTED (1 << 0)            /*!< Write protected */ 
    sdcard_type_t cardType;                             /*!< Card type */
    uint8_t rawCsd[16];                                 /*!< CSD */
    uint8_t rawCid[16];                                 /*!< CID */
    uint8_t rawScr[8];                                  /*!< SCR */
    uint32_t ocr;                                       /*!< OCR */
    uint32_t blockCount;                                /*!< Card total block number */
    uint32_t blockSize;                                 /*!< Card block size */
} sdspi_card_t;

typedef struct SdSpiRequest {
    uint8_t cmdIndex;                                   /*!< Command index */
    uint32_t argument;                                  /*!< Command argument */
    uint8_t respType;                                   /*!< Response type */
    uint8_t response[5];                                /*!< Response */
    uint8_t *data;                                      /*!< Data */
    uint32_t length;                                    /*!< Data length */
} sdspi_request_t;

#define SDSPI_TIMEOUT 1000

#define SDSPI_MAKE_CMD(x)           ((uint8_t) 0x40 | x)
#define SDSPI_READ_TIMEOUT_VALUE    (100)
#define SDSPI_WRITE_TIMEOUT_VALUE   (250)
#define IS_SD_CARD(x)               ((x)->cardType == kCardTypeSd)
#define IS_BLOCK_ACCESS(x)          ((x)->caps & SDSPI_CAPS_ACCESS_IN_BLOCK)

/* Card CSD */
/* CSD_STRUCTURE[126:127] */
#define SDMMC_CSD_CSDSTRUCTURE_VERSION(x) ((x)[0] >> 6)
/* SPEC_VERSION[122:125] */
#define MMC_CSD_SPEC_VERSION(x) (((x)[0] >> 2) & 0xF)

/* TAAC[112:119]: data read access time */
#define SDMMC_CSD_TAAC_TU(x) ((x)[1] & 7)
#define SDMMC_CSD_TAAC_TV(x) (((x)[1] >> 3) & 0xF)

/* NSAC[111:104]: data read access in clock cycles (NSAC * 100) */
#define SDMMC_CSD_NSAC(x) ((x)[2])
#define SDV20_CSD_NSAC(x) (0)

/* TRAN_SPEED[96:103]: max data transfer rate */
#define SDMMC_CSD_TRANSPEED_RU(x) ((x)[3] & 7)
#define SDMMC_CSD_TRANSPEED_TV(x) (((x)[3] >> 3) & 0x0F)

/* CCC[84:95]: card command class */
#define SDMMC_CSD_CCC(x) (((uint16_t)(x)[4] << 4) | ((uint16_t)(x)[5]) >> 4)

/* READ_BLK_LEN[80:83]: max read data block length */
#define SDMMC_CSD_READBLK_LEN(x) ((x)[5] & 0xF)
#define SDV20_CSD_READBLK_LEN(x) (9)

/* READ_BLK_PARTIAL[79:79]: partial blocks for read allowed */
#define SDMMC_CSD_READBLK_PARTIAL(x) ((x)[6] >> 7)
#define SDV20_CSD_READBLK_PARTIAL(x) (0)

/* WRITE_BLK_MISALIGN[78:78]: write block misalignment */
#define SDMMC_CSD_WRITEBLK_MISALIGN(x) (((x)[6] >> 6) & 1)
#define SDV20_CSD_WRITEBLK_MISALIGN(x) (0)
/* READ_BLK_MISALIGN[77:77]: read block misalignment */
#define SDMMC_CSD_READBLK_MISALIGN(x) (((x)[6] >> 5) & 1)
#define SDV20_CSD_READBLK_MISALIGN(x) (0)
/* DSR_IMP[76:76]: DSR implemented */
#define SDMMC_CSD_DSRIMP(x) (((x)[6] >> 4) & 1)
/* C_SIZE[62:73]: device size */
#define SDMMC_CSD_CSIZE(x) ((((x)[6] & 0x3) << 10) | ((x)[7] << 2) | (((x)[8] >> 6)))
#define SDV20_CSD_CSIZE(x) (((uint32_t)(x)[7] & 0x3f) << 16 | ((x)[8] << 8) | (x)[9])

/* VDD_R_CURR_MIN[59:61]: min read current at Vcc*/
#define SDMMC_CSD_VDD_R_CURR_MIN(x) (((x)[8] >> 3) & 7)
#define SDV20_CSD_VDD_R_CURR_MIN(x) (7)

/* VDD_R_CURR_MAX[56:58]: max read current at Vcc*/
#define SDMMC_CSD_VDD_R_CURR_MAX(x) ((x)[8] >> 7)
#define SDV20_CSD_VDD_R_CURR_MAX(x) (6)

/* VDD_W_CURR_MIN[53:55]: min write current at Vcc*/
#define SDMMC_CSD_VDD_W_CURR_MIN(x) (((x)[9] >> 5) & 7)
#define SDV20_CSD_VDD_W_CURR_MIN(x) (7)

/* VDD_W_CURR_MAX[50:52]: max write current at Vcc*/
#define SDMMC_CSD_VDD_W_CURR_MAX(x) ((x)[9] >> 2)
#define SDV20_CSD_VDD_W_CURR_MAX(x) (6)

/* C_SIZE_MULT[47:49]: device size multiplier */
#define SDMMC_CSD_CSIZEMULT(x) ((((x)[9] & 3) << 1) | ((x)[10] >> 7))
#define SDV20_CSD_CSIZEMULT(x) (8)

/* ER_BLK_EN[46:46]: erase single block enabled */
#define SD_CSD_ERASE_BLK_ENABLE(x) (((x)[10] >> 6) & 1)
#define SDV20_CSD_ERASE_BLK_ENABLE(x) (1)

/* SECTOR_SIZE[39:45]: erase sector size */
#define SD_CSD_SECTOR_SIZE(x) ((((x)[10] & 0x3F) << 1) | ((x)[11] >> 7))
#define SDV20_CSD_SECTOR_SIZE(x) (0x7F)

/* SECTOR_SIZE[42:46]: erase sector size */
#define MMC_CSD_SECOTR_SIZE(x) (((x)[10] >> 2) & 0x1F)
/* ER_GRP_SIZE[37:41]: erase group size */
#define MMC_CSD_ERASE_GRP_SIZE(x) ((((x)[10] & 3) << 3) | ((x)[11] >> 5))

/* WP_GRP_SIZE[32:38]: write protect group size */
#define SD_CSD_WP_GRP_SIZE(x) ((x)[11] & 0x7F)
#define SDV20_CSD_WP_GRP_SIZE(x) (0)

/* WP_GRP_SIZE[32:36]: write protect group size */
#define MMC_CSD_WP_GRP_SIZE(x) ((x)[11] & 0x1F)
/* WP_GRP_EN[31:31]: write protect group enable */
#define SDMMC_CSD_WP_GRP_ENABLE(x) ((x)[12] >> 7)
#define SDV20_CSD_WP_GRP_ENABLE(x) (0)
/* DFLT_ECC[29:30]: manufacturer default ECC */
#define MMC_CSD_DFLTECC(x) (((x)[12] >> 5) & 3)
/* R2W_FACTOR[26:28]: write speed factor */
#define SDMMC_CSD_R2W_FACTOR(x) (((x)[12] >> 2) & 7)
#define SDV20_CSD_R2W_FACTOR(x) (2)
/* WRITE_BLK_LEN[22:25]: max write data block length */
#define SDMMC_CSD_WRITEBLK_LEN(x) ((((x)[12] & 3) << 2) | ((x)[13] >> 6))
#define SDV20_CSD_WRITEBLK_LEN(x) (9)
/* WRITE_BLK_PARTIAL[21:21]: partial blocks for write allowed */
#define SDMMC_CSD_WRITEBLK_PARTIAL(x) (((x)[13] >> 5) & 1)
#define SDV20_CSD_WRITEBLK_PARTIAL(x) (0)
/* FILE_FORMAT_GROUP[15:15]: file format group */
#define SDMMC_CSD_FILEFORMAT_GRP(x) ((x)[14] >> 7)
#define SDV20_CSD_FILEFORMAT_GRP(x) (0)
/* COPY[14:14]: copy flag */
#define SDMMC_CSD_COPY(x) (((x)[14] >> 16) & 1)
/* PERM_WRITE_PROTECT[13:13]: permanent write protection */
#define SD_CSD_PERM_WRITEPROTECT(x) (((x)[14] >> 5) & 1)
/* TEMP_WRITE_PROTECT[13:13]: temporary write protection */
#define SD_CSD_TEMP_WRITEPROTECT(x) (((x)[14] >> 4) & 1)
/* FILE_FORMAT[10:11]: file format */
#define SDMMC_CSD_FILE_FORMAT(x) (((x)[14] >> 2) & 3)
#define SDV20_CSD_FILE_FORMAT(x) (0)
/* ECC[8:9]: ECC */
#define MMC_CSD_ECC(x) ((x)[14] & 3)
/* CRC[1:7]: CRC */
#define SDMMC_CSD_CRC(x) ((x)[15] >> 1)

/*! @} */

/*! @addtogroup sdspi_carddrv */
/*! @{ */

/*************************************************************************************************
 * API
 ************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @name SDCARD SPI DRIVER FUNCTION */
/*@{ */

/*!
 * @brief Initializes the card on a specific SPI instance.
 *
 * This function initializes the card on a specific SPI instance.
 *
 * @param spi spi device pointer
 * @param card the place to store card related information
 * @return kStatus_SDSPI_NoError on success
 */
sdspi_status_t SDSPI_DRV_Init(sdspi_spi_t *spi, sdspi_card_t *card);

/*!
 * @brief Reads blocks from the specific card.
 *
 * This function reads blocks from specific card.
 *
 * @param spi spi device pointer
 * @param card the handle of the card
 * @param buffer the buffer to hold the data read from card
 * @param startBlock the start block index
 * @param blockCount the number of blocks to read
 * @return kStatus_SDSPI_NoError on success
 */
sdspi_status_t SDSPI_DRV_ReadBlocks(sdspi_spi_t *spi, sdspi_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Writes blocks of data to the specific card.
 *
 * This function writes blocks to specific card
 *
 * @param spi spi device pointer
 * @param card the handle of the card
 * @param buffer the buffer holding the data to be written to the card
 * @param startBlock the start block index
 * @param blockCount the number of blocks to write
 * @return kStatus_SDSPI_NoError on success
 */
sdspi_status_t SDSPI_DRV_WriteBlocks(sdspi_spi_t *spi, sdspi_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Checks whether the card is write-protected.
 *
 * This function checks if the card is write-protected via CSD register.
 *
 * @param spi spi device pointer
 * @param card the specific card
 * @return kStatus_SDSPI_NoError on success
 */
bool SDSPI_DRV_CheckReadOnly(sdspi_spi_t *spi, sdspi_card_t *card);

/*!
 * @brief Deinitializes the card.
 *
 * This function deinitializes the specific card.
 *
 * @param spi spi device pointer
 * @param card the specific card
 */
void SDSPI_DRV_Shutdown(sdspi_spi_t *spi, sdspi_card_t *card);

/*@} */
#if defined(__cplusplus)
}
#endif
/*! @} */
#endif

/*************************************************************************************************
 * EOF
 ************************************************************************************************/

