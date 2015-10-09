/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#ifndef __FSL_SDHC_CARD_H__
#define __FSL_SDHC_CARD_H__

#include "fsl_sdhc_driver.h"
#include "fsl_sdmmc_card.h"

/*! @addtogroup sdhc_carddrv_data_types */
/*! @{ */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @brief SDHC Card Structure
 *
 * Defines the card structure including the necessary fields to identify and
 * describe the card.
 */
typedef struct SdhcCard {
    uint32_t hostInstance;                              /*!< Host instance id */
    sdhc_host_t *host;
    sdcard_type_t cardType;                             /*!< Card type */
    uint32_t rca;                                       /*!< Relative address of the card */
    uint32_t version;                                   /*!< Card version */
    uint32_t caps;                                      /*!< Capability */
#define SDMMC_CARD_CAPS_HIGHSPEED           (1 << 0)    /*!< SD card high speed support bit */
#define SDMMC_CARD_CAPS_HIGHCAPACITY        (1 << 1)    /*!< Card is high capacity */
#define SDMMC_CARD_CAPS_BUSWIDTH_4BITS      (1 << 2)    /*!< 4-bit data width support bit */
#define SDMMC_CARD_CAPS_BUSWIDTH_8BITS      (1 << 3)    /*!< 8-bit data width support bit */
#define SDMMC_CARD_CAPS_SDHC                (1 << 5)    /*!< Card is SDHC */
#define SDMMC_CARD_CAPS_SDXC                (1 << 6)    /*!< Card is SDXC */
    uint32_t rawCid[4];                                    /*!< CID */
    uint32_t rawCsd[4];                                    /*!< CSD */
    uint32_t rawScr[2];                                    /*!< CSD */
    uint32_t ocr;                                       /*!< OCR */
    sdcard_cid_t cid;                                   /*!< CID */
    sdcard_csd_t csd;                                   /*!< CSD */
    sdcard_scr_t scr;                                   /*!< SCR */
    uint32_t blockCount;                                /*!< Card total block number */
    uint32_t blockSize;                                 /*!< Card block size */
} sdhc_card_t;

#define DOES_CARD_SUPPORT_HIGHSPEED(x)      ((x)->caps & SDMMC_CARD_CAPS_HIGHSPEED)
#define DOES_CARD_SUPPORT_4BITS(x)          ((x)->caps & SDMMC_CARD_CAPS_BUSWIDTH_4BITS)
#define IS_HIGHCAPACITY_CARD(x)             ((x)->caps & SDMMC_CARD_CAPS_HIGHCAPACITY)
#define IS_SD_CARD(x)                       ((x)->cardType == kCardTypeSd)
#define IS_MMC_CARD(x)                      ((x)->cardType == kCardTypeMmc)
#define IS_SDIO_CARD(x)                     ((x)->cardType == kCardTypeSdio)
#define CARD_BLOCK_LEN(x)                   ((uint32_t)(1 << (x)))
#define FSL_SDHC_CARD_MAX_VOLT_RETRIES      (1000)

#define FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE    (512)     /*!< Default block size */
/*! @} */

/*! @addtogroup sdhc_carddrv */
/*! @{ */

/*************************************************************************************************
 * API
 ************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @name SDHC CARD DRIVER FUNCTION */
/*@{ */

/*!
 * @brief Initializes the card on a specific host controller.
 *
 * This function initializes the card on a specific SDHC.
 *
 * @param host the pointer to the host struct, it is allocated by user
 * @param card the place to store card related information
 * @return kStatus_SDHC_NoError on success
 */
sdhc_status_t SDCARD_DRV_Init(sdhc_host_t *host, sdhc_card_t *card);

/*!
 * @brief Reads blocks from the specific card.
 *
 * This function reads blocks from specific card, with default
 * block size defined by FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE.
 *
 * @param card the handle of the card
 * @param buffer the buffer to hold the data read from card
 * @param startBlock the start block index
 * @param blockCount the number of blocks to read
 * @return kStatus_SDHC_NoError on success
 */
sdhc_status_t SDCARD_DRV_ReadBlocks(sdhc_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Writes blocks of data to the specific card.
 *
 * This function writes blocks to specific card, with default
 * block size defined by FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE.
 *
 * @param card the handle of the card
 * @param buffer the buffer holding the data to be written to the card
 * @param startBlock the start block index
 * @param blockCount the number of blocks to write
 * @return kStatus_SDHC_NoError on success
 */
sdhc_status_t SDCARD_DRV_WriteBlocks(sdhc_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Erases blocks of the specific card.
 *
 * This function erases blocks of a specific card, with default
 * block size defined by the FSL_SDHC_CARD_DEFAULT_BLOCK_SIZE.
 *
 * @param card the handle of the card
 * @param startBlock the start block index
 * @param blockCount the number of blocks to erase
 * @return kStatus_SDHC_NoError on success
 */
sdhc_status_t SDCARD_DRV_EraseBlocks(sdhc_card_t *card, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Checks whether the card is write-protected.
 *
 * This function checks if the card is write-protected via CSD register.
 *
 * @param card the specific card
 * @return kStatus_SDHC_NoError on success
 */
bool SDCARD_DRV_CheckReadOnly(sdhc_card_t *card);

/*!
 * @brief Deinitializes the card.
 *
 * This function deinitializes the specific card.
 *
 * @param card the specific card
 */
void SDCARD_DRV_Shutdown(sdhc_card_t *card);

/*@} */
#if defined(__cplusplus)
}
#endif
/*! @} */
#endif

/*************************************************************************************************
 * EOF
 ************************************************************************************************/

