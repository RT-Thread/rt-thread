/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "sdmmc_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_SDCardPowerControl(bool enable);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*!brief sdmmc dma buffer */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t s_sdmmcHostDmaBuffer[BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE],
                              SDMMCHOST_DMA_DESCRIPTOR_BUFFER_ALIGN_SIZE);
#if defined SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER && SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER
/* two cache line length for sdmmc host driver maintain unalign transfer */
SDK_ALIGN(static uint8_t s_sdmmcCacheLineAlignBuffer[BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE * 2U],
          BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE);
#endif
#if defined(SDIO_ENABLED) || defined(SD_ENABLED)
static sd_detect_card_t s_cd;
static sd_io_voltage_t s_ioVoltage = {
    .type = BOARD_SDMMC_SD_IO_VOLTAGE_CONTROL_TYPE,
    .func = NULL,
};
#endif
sdmmchost_t s_host;
#ifdef SDIO_ENABLED
static sdio_card_int_t s_sdioInt;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t BOARD_USDHC1ClockConfiguration(void)
{
    return 0;
}

#if defined(SDIO_ENABLED) || defined(SD_ENABLED)
void BOARD_SDCardPowerControl(bool enable)
{
}

void BOARD_SD_Pin_Config(uint32_t freq)
{
}
#endif

#ifdef SD_ENABLED
void BOARD_SD_Config(void *card, sd_cd_t cd, uint32_t hostIRQPriority, void *userData)
{
    assert(card);

    s_host.dmaDesBuffer         = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
    s_host.enableCacheControl   = BOARD_SDMMC_HOST_CACHE_CONTROL;
#if defined SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER && SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER
    s_host.cacheAlignBuffer     = s_sdmmcCacheLineAlignBuffer;
    s_host.cacheAlignBufferSize = BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE * 2U;
#endif

    ((sd_card_t *)card)->host                                = &s_host;
    ((sd_card_t *)card)->host->hostController.base           = BOARD_SDMMC_SD_HOST_BASEADDR;
    ((sd_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC1ClockConfiguration();

    ((sd_card_t *)card)->usrParam.cd         = &s_cd;
    ((sd_card_t *)card)->usrParam.pwr        = BOARD_SDCardPowerControl;
    ((sd_card_t *)card)->usrParam.ioStrength = BOARD_SD_Pin_Config;
    ((sd_card_t *)card)->usrParam.ioVoltage  = &s_ioVoltage;
    ((sd_card_t *)card)->usrParam.maxFreq    = BOARD_SDMMC_SD_HOST_SUPPORT_SDR104_FREQ;

    NVIC_SetPriority(BOARD_SDMMC_SD_HOST_IRQ, hostIRQPriority);
}
#endif

#ifdef SDIO_ENABLED
void BOARD_SDIO_Config(void *card, sd_cd_t cd, uint32_t hostIRQPriority, sdio_int_t cardInt)
{
    assert(card);

    s_host.dmaDesBuffer         = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
    s_host.enableCacheControl   = BOARD_SDMMC_HOST_CACHE_CONTROL;
#if defined SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER && SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER
    s_host.cacheAlignBuffer     = s_sdmmcCacheLineAlignBuffer;
    s_host.cacheAlignBufferSize = BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE * 2U;
#endif

    ((sdio_card_t *)card)->host                                = &s_host;
    ((sdio_card_t *)card)->host->hostController.base           = BOARD_SDMMC_SDIO_HOST_BASEADDR;
    ((sdio_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC1ClockConfiguration();

    ((sdio_card_t *)card)->usrParam.cd         = &s_cd;
    ((sdio_card_t *)card)->usrParam.pwr        = BOARD_SDCardPowerControl;
    ((sdio_card_t *)card)->usrParam.ioStrength = BOARD_SD_Pin_Config;
    ((sdio_card_t *)card)->usrParam.ioVoltage  = &s_ioVoltage;
    ((sdio_card_t *)card)->usrParam.maxFreq    = BOARD_SDMMC_SD_HOST_SUPPORT_SDR104_FREQ;
    if (cardInt != NULL)
    {
        s_sdioInt.cardInterrupt                 = cardInt;
        ((sdio_card_t *)card)->usrParam.sdioInt = &s_sdioInt;
    }

    BOARD_SDCardPowerResetInit();
    BOARD_SDCardDetectInit(cd, NULL);

    NVIC_SetPriority(BOARD_SDMMC_SDIO_HOST_IRQ, hostIRQPriority);
}
#endif

#ifdef MMC_ENABLED
static void BOARD_MMC_Pin_Config(uint32_t freq)
{
}

void BOARD_MMC_Config(void *card, uint32_t hostIRQPriority)
{
    assert(card);

    s_host.dmaDesBuffer         = s_sdmmcHostDmaBuffer;
    s_host.dmaDesBufferWordsNum = BOARD_SDMMC_HOST_DMA_DESCRIPTOR_BUFFER_SIZE;
    s_host.enableCacheControl   = BOARD_SDMMC_HOST_CACHE_CONTROL;
#if defined SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER && SDMMCHOST_ENABLE_CACHE_LINE_ALIGN_TRANSFER
    s_host.cacheAlignBuffer     = s_sdmmcCacheLineAlignBuffer;
    s_host.cacheAlignBufferSize = BOARD_SDMMC_DATA_BUFFER_ALIGN_SIZE * 2U;
#endif

    ((mmc_card_t *)card)->host                                = &s_host;
    ((mmc_card_t *)card)->host->hostController.base           = BOARD_SDMMC_MMC_HOST_BASEADDR;
    ((mmc_card_t *)card)->host->hostController.sourceClock_Hz = BOARD_USDHC1ClockConfiguration();
    ((mmc_card_t *)card)->usrParam.ioStrength                 = BOARD_MMC_Pin_Config;
    ((mmc_card_t *)card)->usrParam.maxFreq                    = BOARD_SDMMC_MMC_HOST_SUPPORT_HS200_FREQ;

    ((mmc_card_t *)card)->hostVoltageWindowVCC  = BOARD_SDMMC_MMC_VCC_SUPPLY;
    ((mmc_card_t *)card)->hostVoltageWindowVCCQ = BOARD_SDMMC_MMC_VCCQ_SUPPLY;

    NVIC_SetPriority(BOARD_SDMMC_MMC_HOST_IRQ, hostIRQPriority);
}
#endif
