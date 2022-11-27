/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _SDMMC_CONFIG_H_
#define _SDMMC_CONFIG_H_

#ifdef SD_ENABLED
#include "fsl_sd.h"
#endif
#ifdef MMC_ENABLED
#include "fsl_mmc.h"
#endif
#include "clock_config.h"
#include "fsl_sdmmc_host.h"
#include "fsl_sdmmc_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* @brief host basic configuration */
#define BOARD_SDMMC_SD_HOST_BASEADDR  SDHC
#define BOARD_SDMMC_MMC_HOST_BASEADDR SDHC

#define BOARD_SDMMC_SD_HOST_IRQ  SDHC_IRQn
#define BOARD_SDMMC_MMC_HOST_IRQ SDHC_IRQn
/* @brief card detect configuration */
#define BOARD_SDMMC_SD_CD_GPIO_BASE        GPIOB
#define BOARD_SDMMC_SD_CD_GPIO_PIN         20U
#define BOARD_SDMMC_SD_CD_PORT_BASE        PORTB
#define BOARD_SDMMC_SD_CD_PORT_IRQ         PORTB_IRQn
#define BOARD_SDMMC_SD_CD_IRQ_PRIORITY     6U
#define BOARD_SDMMC_SD_CD_INTTERUPT_TYPE   kPORT_InterruptEitherEdge
#define BOARD_SDMMC_SD_CD_INSERT_LEVEL     (0U)
#define BOARD_SDMMC_SD_CD_PORT_IRQ_HANDLER PORTB_IRQHandler
/* @brief card detect type
 *
 * Note: if you want to use DAT3 as card detect pin, please pay attention, DAT3 card detection cannot works during the
 * card access, since the DAT3 will be used for data transfer, thus the functionality of card detect interrupt will be
 * disabled as soon as card is detected. So If application would like to re-detect sdcard/sdiocard, please calling
 * SD_PollingCardInsert/SDIO_PollingCardInsert The function will polling the card detect status and could yield CPU
 * while RTOS and non-blocking adapter is using.
 *
 * Using card detect pin for card detection is recommended.
 */
#define BOARD_SDMMC_SD_CD_TYPE                       kSD_DetectCardByGpioCD
#define BOARD_SDMMC_SD_CARD_DETECT_DEBOUNCE_DELAY_MS (100U)

#define BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE (4U)
/* @brief mmc configuration */
#define BOARD_SDMMC_MMC_VCC_SUPPLY  kMMC_VoltageWindows270to360
#define BOARD_SDMMC_MMC_VCCQ_SUPPLY kMMC_VoltageWindows270to360

/* @brief The SDSPI configuration. */
#define BOARD_SDSPI_HOST_BASE         SPI1_BASE /*!< SPI base address for SDSPI */
#define BOARD_SDSPI_HOST_CD_GPIO_BASE GPIOB     /*!< Port related to card detect pin for SDSPI */
#define BOARD_SDSPI_HOST_CD_PIN       20U       /*!< Card detect pin for SDSPI */

/*!@ brief host interrupt priority*/
#define BOARD_SDMMC_SD_HOST_IRQ_PRIORITY  (5U)
#define BOARD_SDMMC_MMC_HOST_IRQ_PRIORITY (5U)
/*!@brief dma descriptor buffer size */
#define BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE (32U)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief BOARD SD configurations.
 * @param card card descriptor
 * @param cd card detect callback
 * @param userData user data for callback
 */
#ifdef SD_ENABLED
void BOARD_SD_Config(void *card, sd_cd_t cd, uint32_t hostIRQPriority, void *userData);
#endif

/*!
 * @brief BOARD MMC configurations.
 * @param card card descriptor
 * @param cd card detect callback
 * @param userData user data for callback
 */
#ifdef MMC_ENABLED
void BOARD_MMC_Config(void *card, uint32_t hostIRQPriority);

#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
