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
#ifdef SDIO_ENABLED
#include "fsl_sdio.h"
#endif
#include "clock_config.h"
#include "fsl_sdmmc_host.h"
#include "fsl_sdmmc_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* @brief host basic configuration */
#define BOARD_SDMMC_SD_HOST_BASEADDR   USDHC1
#define BOARD_SDMMC_SD_HOST_IRQ        USDHC1_IRQn
#define BOARD_SDMMC_MMC_HOST_BASEADDR  USDHC1
#define BOARD_SDMMC_MMC_HOST_IRQ       USDHC1_IRQn
#define BOARD_SDMMC_SDIO_HOST_BASEADDR USDHC1
#define BOARD_SDMMC_SDIO_HOST_IRQ      USDHC1_IRQn
/* @brief card detect configuration */
#define BOARD_SDMMC_SD_CD_GPIO_BASE        GPIO2
#define BOARD_SDMMC_SD_CD_GPIO_PIN         28u
#define BOARD_SDMMC_SD_CD_IRQ_PRIORITY     6U
#define BOARD_SDMMC_SD_CD_IRQ              GPIO2_Combined_16_31_IRQn
#define BOARD_SDMMC_SD_CD_INTTERUPT_TYPE   kGPIO_IntRisingOrFallingEdge
#define BOARD_SDMMC_SD_CD_INSERT_LEVEL     (0U)
#define BOARD_SDMMC_SD_CD_PORT_IRQ_HANDLER GPIO2_Combined_16_31_IRQHandler
/* @brief card detect type
 *
 * Note: Please pay attention, DAT3 card detection cannot works during the card access,
 * since the DAT3 will be used for data transfer, thus the functionality of card detect will be disabled. Using card
 * detect pin for card detection is recommended.
 */
#define BOARD_SDMMC_SD_CD_TYPE                       kSD_DetectCardByGpioCD
#define BOARD_SDMMC_SD_CARD_DETECT_DEBOUNCE_DELAY_MS (100U)
/*! @brief SD power reset */
#define BOARD_SDMMC_SD_POWER_RESET_GPIO_BASE GPIO1
#define BOARD_SDMMC_SD_POWER_RESET_GPIO_PIN  5U
/*! @brief SD IO voltage */
#define BOARD_SDMMC_SD_IO_VOLTAGE_CONTROL_TYPE kSD_IOVoltageCtrlByHost

#define BOARD_SDMMC_SD_HOST_SUPPORT_SDR104_FREQ (200000000U)
#define BOARD_SDMMC_MMC_HOST_SUPPORT_HS200_FREQ (180000000U)
/*! @brief mmc configuration */
#define BOARD_SDMMC_MMC_VCC_SUPPLY  kMMC_VoltageWindows270to360
#define BOARD_SDMMC_MMC_VCCQ_SUPPLY kMMC_VoltageWindows270to360
/*! @brief align with cache line size */
#define BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE (32U)

/*!@ brief host interrupt priority*/
#define BOARD_SDMMC_SD_HOST_IRQ_PRIORITY   (5U)
#define BOARD_SDMMC_MMC_HOST_IRQ_PRIORITY  (5U)
#define BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY (5U)
/*!@brief dma descriptor buffer size */
#define BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE (32U)
/*! @brief cache maintain function enabled for RW buffer */
#define BOARD_SDMMC_HOST_CACHE_CONTROL kSDMMCHOST_CacheControlRWBuffer

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
 * @brief BOARD SDIO configurations.
 * @param card card descriptor
 * @param cd card detect callback
 * @param cardInt card interrupt
 */
#ifdef SDIO_ENABLED
void BOARD_SDIO_Config(void *card, sd_cd_t cd, uint32_t hostIRQPriority, sdio_int_t cardInt);
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
