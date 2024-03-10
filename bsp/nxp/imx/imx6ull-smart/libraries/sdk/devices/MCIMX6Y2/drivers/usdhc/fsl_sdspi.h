/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#ifndef _FSL_SDSPI_H_
#define _FSL_SDSPI_H_

#include "fsl_common.h"
#include "fsl_specification.h"

/******************************************************************************
 * Definitions
 *****************************************************************************/
/*! @brief Driver version. */
#define FSL_SDSPI_DRIVER_VERSION (MAKE_VERSION(2U, 1U, 1U)) /*2.1.1*/

/*! @brief Default block size */
#define FSL_SDSPI_DEFAULT_BLOCK_SIZE (512U)

/*!
 * @addtogroup SDSPI
 * @{
 */

/*! @brief SDSPI API status */
enum _sdspi_status
{
    kStatus_SDSPI_SetFrequencyFailed = MAKE_STATUS(kStatusGroup_SDSPI, 0U), /*!< Set frequency failed */
    kStatus_SDSPI_ExchangeFailed = MAKE_STATUS(kStatusGroup_SDSPI, 1U),     /*!< Exchange data on SPI bus failed */
    kStatus_SDSPI_WaitReadyFailed = MAKE_STATUS(kStatusGroup_SDSPI, 2U),    /*!< Wait card ready failed */
    kStatus_SDSPI_ResponseError = MAKE_STATUS(kStatusGroup_SDSPI, 3U),      /*!< Response is error */
    kStatus_SDSPI_WriteProtected = MAKE_STATUS(kStatusGroup_SDSPI, 4U),     /*!< Write protected */
    kStatus_SDSPI_GoIdleFailed = MAKE_STATUS(kStatusGroup_SDSPI, 5U),       /*!< Go idle failed */
    kStatus_SDSPI_SendCommandFailed = MAKE_STATUS(kStatusGroup_SDSPI, 6U),  /*!< Send command failed */
    kStatus_SDSPI_ReadFailed = MAKE_STATUS(kStatusGroup_SDSPI, 7U),         /*!< Read data failed */
    kStatus_SDSPI_WriteFailed = MAKE_STATUS(kStatusGroup_SDSPI, 8U),        /*!< Write data failed */
    kStatus_SDSPI_SendInterfaceConditionFailed =
        MAKE_STATUS(kStatusGroup_SDSPI, 9U), /*!< Send interface condition failed */
    kStatus_SDSPI_SendOperationConditionFailed =
        MAKE_STATUS(kStatusGroup_SDSPI, 10U),                                    /*!< Send operation condition failed */
    kStatus_SDSPI_ReadOcrFailed = MAKE_STATUS(kStatusGroup_SDSPI, 11U),          /*!< Read OCR failed */
    kStatus_SDSPI_SetBlockSizeFailed = MAKE_STATUS(kStatusGroup_SDSPI, 12U),     /*!< Set block size failed */
    kStatus_SDSPI_SendCsdFailed = MAKE_STATUS(kStatusGroup_SDSPI, 13U),          /*!< Send CSD failed */
    kStatus_SDSPI_SendCidFailed = MAKE_STATUS(kStatusGroup_SDSPI, 14U),          /*!< Send CID failed */
    kStatus_SDSPI_StopTransmissionFailed = MAKE_STATUS(kStatusGroup_SDSPI, 15U), /*!< Stop transmission failed */
    kStatus_SDSPI_SendApplicationCommandFailed =
        MAKE_STATUS(kStatusGroup_SDSPI, 16U), /*!< Send application command failed */
};

/*! @brief SDSPI card flag */
enum _sdspi_card_flag
{
    kSDSPI_SupportHighCapacityFlag = (1U << 0U), /*!< Card is high capacity */
    kSDSPI_SupportSdhcFlag = (1U << 1U),         /*!< Card is SDHC */
    kSDSPI_SupportSdxcFlag = (1U << 2U),         /*!< Card is SDXC */
    kSDSPI_SupportSdscFlag = (1U << 3U),         /*!< Card is SDSC */
};

/*! @brief SDSPI response type */
typedef enum _sdspi_response_type
{
    kSDSPI_ResponseTypeR1 = 0U,  /*!< Response 1 */
    kSDSPI_ResponseTypeR1b = 1U, /*!< Response 1 with busy */
    kSDSPI_ResponseTypeR2 = 2U,  /*!< Response 2 */
    kSDSPI_ResponseTypeR3 = 3U,  /*!< Response 3 */
    kSDSPI_ResponseTypeR7 = 4U,  /*!< Response 7 */
} sdspi_response_type_t;

/*! @brief SDSPI command */
typedef struct _sdspi_command
{
    uint8_t index;        /*!< Command index */
    uint32_t argument;    /*!< Command argument */
    uint8_t responseType; /*!< Response type */
    uint8_t response[5U]; /*!< Response content */
} sdspi_command_t;

/*! @brief SDSPI host state. */
typedef struct _sdspi_host
{
    uint32_t busBaudRate; /*!< Bus baud rate */

    status_t (*setFrequency)(uint32_t frequency);                   /*!< Set frequency of SPI */
    status_t (*exchange)(uint8_t *in, uint8_t *out, uint32_t size); /*!< Exchange data over SPI */
    uint32_t (*getCurrentMilliseconds)(void);                       /*!< Get current time in milliseconds */
} sdspi_host_t;

/*!
 * @brief SD Card Structure
 *
 * Define the card structure including the necessary fields to identify and describe the card.
 */
typedef struct _sdspi_card
{
    sdspi_host_t *host;       /*!< Host state information */
    uint32_t relativeAddress; /*!< Relative address of the card */
    uint32_t flags;           /*!< Flags defined in _sdspi_card_flag. */
    uint8_t rawCid[16U];      /*!< Raw CID content */
    uint8_t rawCsd[16U];      /*!< Raw CSD content */
    uint8_t rawScr[8U];       /*!< Raw SCR content */
    uint32_t ocr;             /*!< Raw OCR content */
    sd_cid_t cid;             /*!< CID */
    sd_csd_t csd;             /*!< CSD */
    sd_scr_t scr;             /*!< SCR */
    uint32_t blockCount;      /*!< Card total block number */
    uint32_t blockSize;       /*!< Card block size */
} sdspi_card_t;

/*************************************************************************************************
 * API
 ************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name SDSPI Function
 * @{
 */

/*!
 * @brief Initializes the card on a specific SPI instance.
 *
 * This function initializes the card on a specific SPI instance.
 *
 * @param card Card descriptor
 * @retval kStatus_SDSPI_SetFrequencyFailed Set frequency failed.
 * @retval kStatus_SDSPI_GoIdleFailed Go idle failed.
 * @retval kStatus_SDSPI_SendInterfaceConditionFailed Send interface condition failed.
 * @retval kStatus_SDSPI_SendOperationConditionFailed Send operation condition failed.
 * @retval kStatus_Timeout Send command timeout.
 * @retval kStatus_SDSPI_NotSupportYet Not support yet.
 * @retval kStatus_SDSPI_ReadOcrFailed Read OCR failed.
 * @retval kStatus_SDSPI_SetBlockSizeFailed Set block size failed.
 * @retval kStatus_SDSPI_SendCsdFailed Send CSD failed.
 * @retval kStatus_SDSPI_SendCidFailed Send CID failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDSPI_Init(sdspi_card_t *card);

/*!
 * @brief Deinitializes the card.
 *
 * This function deinitializes the specific card.
 *
 * @param card Card descriptor
 */
void SDSPI_Deinit(sdspi_card_t *card);

/*!
 * @brief Checks whether the card is write-protected.
 *
 * This function checks if the card is write-protected via CSD register.
 *
 * @param card Card descriptor.
 * @retval true Card is read only.
 * @retval false Card isn't read only.
 */
bool SDSPI_CheckReadOnly(sdspi_card_t *card);

/*!
 * @brief Reads blocks from the specific card.
 *
 * This function reads blocks from specific card.
 *
 * @param card Card descriptor.
 * @param buffer the buffer to hold the data read from card
 * @param startBlock the start block index
 * @param blockCount the number of blocks to read
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_SDSPI_ReadFailed Read data failed.
 * @retval kStatus_SDSPI_StopTransmissionFailed Stop transmission failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDSPI_ReadBlocks(sdspi_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Writes blocks of data to the specific card.
 *
 * This function writes blocks to specific card
 *
 * @param card Card descriptor.
 * @param buffer the buffer holding the data to be written to the card
 * @param startBlock the start block index
 * @param blockCount the number of blocks to write
 * @retval kStatus_SDSPI_WriteProtected Card is write protected.
 * @retval kStatus_SDSPI_SendCommandFailed Send command failed.
 * @retval kStatus_SDSPI_ResponseError Response is error.
 * @retval kStatus_SDSPI_WriteFailed Write data failed.
 * @retval kStatus_SDSPI_ExchangeFailed Exchange data over SPI failed.
 * @retval kStatus_SDSPI_WaitReadyFailed Wait card to be ready status failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDSPI_WriteBlocks(sdspi_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/* @} */
#if defined(__cplusplus)
}
#endif
/*! @} */
#endif /* _FSL_SDSPI_H_ */
