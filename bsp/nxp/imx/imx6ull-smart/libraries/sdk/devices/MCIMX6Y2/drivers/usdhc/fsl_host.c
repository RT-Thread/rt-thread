/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
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

#include "fsl_host.h"
#include "fsl_gpio.h"
#include "event.h"
#ifdef BOARD_USDHC_CD_PORT_BASE
#include "fsl_port.h"
#endif
/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief host controller error recovery.
 * @param host base address.
 */
static void Host_ErrorRecovery(HOST_TYPE *hostBase);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* DMA descriptor should allocate at non-cached memory */
AT_NONCACHEABLE_SECTION_ALIGN(uint32_t g_usdhcAdma2Table[USDHC_ADMA_TABLE_WORDS], USDHC_ADMA2_ADDR_ALIGN);
extern volatile uint32_t g_timeMilliseconds;
static volatile bool g_sdInsertedFlag;
/*******************************************************************************
 * Code
 ******************************************************************************/
static void DetectCardByGpio(void)
{
    g_sdInsertedFlag = true; //always return linked status!
}

/* Card detect. */
status_t CardInsertDetect(HOST_TYPE *hostBase)
{
    return kStatus_Success; //always return linked status!
}

/* Card detect pin port interrupt handler. */
void HOST_CARD_DETECT_INTERRUPT_HANDLER(void)
{
    if (HOST_CARD_DETECT_INTERRUPT_STATUS() & (1U << BOARD_USDHC_CD_GPIO_PIN))
    {
        DetectCardByGpio();
    }
    /* Clear interrupt flag.*/
    HOST_CARD_DETECT_INTERRUPT_CLEAR(~0U);
    EVENT_Notify(kEVENT_CardDetect);
}

/* User defined transfer function. */
static status_t USDHC_TransferFunction(USDHC_Type *base, usdhc_transfer_t *content)
{
    usdhc_adma_config_t dmaConfig;
    status_t error = kStatus_Success;

    if (content->data != NULL)
    {
        memset(&dmaConfig, 0, sizeof(usdhc_adma_config_t));
        /* config adma */
        dmaConfig.dmaMode = USDHC_DMA_MODE;
        dmaConfig.burstLen = kUSDHC_EnBurstLenForINCR;
        dmaConfig.admaTable = g_usdhcAdma2Table;
        dmaConfig.admaTableWords = USDHC_ADMA_TABLE_WORDS;
    }

    error = USDHC_TransferBlocking(base, &dmaConfig, content);

    if (error == kStatus_Fail)
    {
        /* host error recovery */
        Host_ErrorRecovery(base);
    }

    return error;
}

static void Host_ErrorRecovery(HOST_TYPE *hostBase)
{
    uint32_t status = 0U;
    /* get host present status */
    status = USDHC_GetPresentStatusFlags(hostBase);
    /* check command inhibit status flag */
    if ((status & kUSDHC_CommandInhibitFlag) != 0U)
    {
        /* reset command line */
        USDHC_Reset(hostBase, kUSDHC_ResetCommand, 100U);
    }
    /* check data inhibit status flag */
    if ((status & kUSDHC_DataInhibitFlag) != 0U)
    {
        /* reset data line */
        USDHC_Reset(hostBase, kUSDHC_ResetData, 100U);
    }
}

status_t HOST_Init(void *host)
{
    usdhc_host_t *usdhcHost = (usdhc_host_t *)host;

    /* init card power control */
    HOST_INIT_SD_POWER();
    HOST_INIT_MMC_POWER();

    /* Initializes SDHC. */
    usdhcHost->config.dataTimeout = USDHC_DATA_TIMEOUT;
    usdhcHost->config.endianMode = USDHC_ENDIAN_MODE;
    usdhcHost->config.readWatermarkLevel = USDHC_READ_WATERMARK_LEVEL;
    usdhcHost->config.writeWatermarkLevel = USDHC_WRITE_WATERMARK_LEVEL;
    usdhcHost->config.readBurstLen = USDHC_READ_BURST_LEN;
    usdhcHost->config.writeBurstLen = USDHC_WRITE_BURST_LEN;

    USDHC_Init(usdhcHost->base, &(usdhcHost->config));

    /* Define transfer function. */
    usdhcHost->transfer = USDHC_TransferFunction;
    /* event init timer */
    EVENT_InitTimer();

    return kStatus_Success;
}

void HOST_Reset(HOST_TYPE *hostBase)
{
    /* voltage switch to normal but not 1.8V */
    HOST_SWITCH_VOLTAGE180V(hostBase, false);
    /* Disable DDR mode */
    HOST_ENABLE_DDR_MODE(hostBase, false);
    /* disable tuning */
    HOST_EXECUTE_STANDARD_TUNING_ENABLE(hostBase, false);
    /* Disable HS400 mode */
    HOST_ENABLE_HS400_MODE(hostBase, false);
    /* Disable DLL */
    HOST_ENABLE_STROBE_DLL(hostBase, false);
}

void HOST_Deinit(void *host)
{
    usdhc_host_t *usdhcHost = (usdhc_host_t *)host;
    USDHC_Deinit(usdhcHost->base);
}
