/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#ifndef __FSL_SDHC_HAL_H__
#define __FSL_SDHC_HAL_H__

#include <assert.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_SDHC_COUNT

/*! @addtogroup sdhc_hal */
/*! @{ */

/* PRSSTA */
#define SDHC_HAL_DAT0_LEVEL             (SDHC_PRSSTAT_DLSL_MASK & (1 << 24))

/* XFERTYP */
#define SDHC_HAL_MAX_BLOCK_COUNT        ((1 << SDHC_BLKATTR_BLKCNT_WIDTH) - 1)
#define SDHC_HAL_ENABLE_DMA             SDHC_XFERTYP_DMAEN_MASK

#define SDHC_HAL_CMD_TYPE_SUSPEND       (SDHC_XFERTYP_CMDTYP(1))
#define SDHC_HAL_CMD_TYPE_RESUME        (SDHC_XFERTYP_CMDTYP(2))
#define SDHC_HAL_CMD_TYPE_ABORT         (SDHC_XFERTYP_CMDTYP(3))

#define SDHC_HAL_ENABLE_BLOCK_COUNT     SDHC_XFERTYP_BCEN_MASK
#define SDHC_HAL_ENABLE_AUTO_CMD12      SDHC_XFERTYP_AC12EN_MASK
#define SDHC_HAL_ENABLE_DATA_READ       SDHC_XFERTYP_DTDSEL_MASK
#define SDHC_HAL_MULTIPLE_BLOCK         SDHC_XFERTYP_MSBSEL_MASK

#define SDHC_HAL_RESP_LEN_136           ((0x1 << SDHC_XFERTYP_RSPTYP_SHIFT) & SDHC_XFERTYP_RSPTYP_MASK)
#define SDHC_HAL_RESP_LEN_48            ((0x2 << SDHC_XFERTYP_RSPTYP_SHIFT) & SDHC_XFERTYP_RSPTYP_MASK)
#define SDHC_HAL_RESP_LEN_48_BC         ((0x3 << SDHC_XFERTYP_RSPTYP_SHIFT) & SDHC_XFERTYP_RSPTYP_MASK)

#define SDHC_HAL_ENABLE_CRC_CHECK       SDHC_XFERTYP_CCCEN_MASK
#define SDHC_HAL_ENABLE_INDEX_CHECK     SDHC_XFERTYP_CICEN_MASK
#define SDHC_HAL_DATA_PRESENT           SDHC_XFERTYP_DPSEL_MASK

/* SYSCTL */
#define SDHC_HAL_MAX_DVS                (16U)
#define SDHC_HAL_INITIAL_DVS            (1U)            /* initial value of divisor to calculate clock rate */
#define SDHC_HAL_INITIAL_CLKFS          (2U)            /* initial value of clock selector to calculate clock rate */
#define SDHC_HAL_NEXT_DVS(x)            do { ((x) += 1); } while(0)
#define SDHC_HAL_PREV_DVS(x)            do { ((x) -= 1); } while(0)
#define SDHC_HAL_MAX_CLKFS              (256U)
#define SDHC_HAL_NEXT_CLKFS(x)          do { ((x) <<= 1); } while(0)
#define SDHC_HAL_PREV_CLKFS(x)          do { ((x) >>= 1); } while(0)

/* IRQSTAT */
#define SDHC_HAL_CMD_COMPLETE_INT       SDHC_IRQSTAT_CC_MASK
#define SDHC_HAL_DATA_COMPLETE_INT      SDHC_IRQSTAT_TC_MASK
#define SDHC_HAL_BLOCK_GAP_EVENT_INT    SDHC_IRQSTAT_BGE_MASK
#define SDHC_HAL_DMA_INT                SDHC_IRQSTAT_DINT_MASK
#define SDHC_HAL_DMA_ERR_INT            SDHC_IRQSTAT_DMAE_MASK
#define SDHC_HAL_BUF_WRITE_READY_INT    SDHC_IRQSTAT_BWR_MASK
#define SDHC_HAL_BUF_READ_READY_INT     SDHC_IRQSTAT_BRR_MASK
#define SDHC_HAL_CARD_INSERTION_INT     SDHC_IRQSTAT_CINS_MASK
#define SDHC_HAL_CARD_REMOVAL_INT       SDHC_IRQSTAT_CRM_MASK
#define SDHC_HAL_CARD_INT               SDHC_IRQSTAT_CINT_MASK
#define SDHC_HAL_CMD_TIMEOUT_ERR_INT    SDHC_IRQSTAT_CTOE_MASK
#define SDHC_HAL_CMD_CRC_ERR_INT        SDHC_IRQSTAT_CCE_MASK
#define SDHC_HAL_CMD_END_BIT_ERR_INT    SDHC_IRQSTAT_CEBE_MASK
#define SDHC_HAL_CMD_INDEX_ERR_INT      SDHC_IRQSTAT_CIE_MASK
#define SDHC_HAL_DATA_TIMEOUT_ERR_INT   SDHC_IRQSTAT_DTOE_MASK
#define SDHC_HAL_DATA_CRC_ERR_INT       SDHC_IRQSTAT_DCE_MASK
#define SDHC_HAL_DATA_END_BIT_ERR_INT   SDHC_IRQSTAT_DEBE_MASK
#define SDHC_HAL_AUTO_CMD12_ERR_INT     SDHC_IRQSTAT_AC12E_MASK

#define SDHC_HAL_CMD_ERR_INT            ((uint32_t)(SDHC_HAL_CMD_TIMEOUT_ERR_INT | \
                                        SDHC_HAL_CMD_CRC_ERR_INT | \
                                        SDHC_HAL_CMD_END_BIT_ERR_INT | \
                                        SDHC_HAL_CMD_INDEX_ERR_INT))
#define SDHC_HAL_DATA_ERR_INT           ((uint32_t)(SDHC_HAL_DATA_TIMEOUT_ERR_INT | \
                                        SDHC_HAL_DATA_CRC_ERR_INT | \
                                        SDHC_HAL_DATA_END_BIT_ERR_INT))
#define SDHC_HAL_DATA_ALL_INT           ((uint32_t)(SDHC_HAL_DATA_ERR_INT | \
                                        SDHC_HAL_DATA_COMPLETE_INT | \
                                        SDHC_HAL_BUF_READ_READY_INT | \
                                        SDHC_HAL_BUF_WRITE_READY_INT | \
                                        SDHC_HAL_DMA_ERR_INT | SDHC_HAL_DMA_INT))
#define SDHC_HAL_CMD_ALL_INT            ((uint32_t)(SDHC_HAL_CMD_ERR_INT | \
                                        SDHC_HAL_CMD_COMPLETE_INT | \
                                        SDHC_HAL_AUTO_CMD12_ERR_INT))
#define SDHC_HAL_CD_ALL_INT             ((uint32_t)(SDHC_HAL_CARD_INSERTION_INT | \
                                        SDHC_HAL_CARD_REMOVAL_INT))
#define SDHC_HAL_ALL_ERR_INT            ((uint32_t)(SDHC_HAL_CMD_ERR_INT | \
                                        SDHC_HAL_DATA_ERR_INT | \
                                        SDHC_HAL_AUTO_CMD12_ERR_INT | \
                                        SDHC_HAL_DMA_ERR_INT))

/* AC12ERR */
#define SDHC_HAL_ACMD12_NOT_EXEC_ERR    SDHC_AC12ERR_AC12NE_MASK
#define SDHC_HAL_ACMD12_TIMEOUT_ERR     SDHC_AC12ERR_AC12TOE_MASK
#define SDHC_HAL_ACMD12_END_BIT_ERR     SDHC_AC12ERR_AC12EBE_MASK
#define SDHC_HAL_ACMD12_CRC_ERR         SDHC_AC12ERR_AC12CE_MASK
#define SDHC_HAL_ACMD12_INDEX_ERR       SDHC_AC12ERR_AC12IE_MASK
#define SDHC_HAL_ACMD12_NOT_ISSUE_ERR   SDHC_AC12ERR_CNIBAC12E_MASK

/* ADMAES */
/* ADMA Error State (When ADMA Error Is Occurred.) */
#define SDHC_HAL_ADMA_STATE_ERR                      SDHC_ADMAES_ADMAES_MASK
/* ADMA Length Mismatch Error */
#define SDHC_HAL_ADMA_LEN_MIS_MATCH_FLAG             SDHC_ADMAES_ADMALME_MASK
/* ADMA Descriptor Error */ 
#define SDHC_HAL_ADMA_DESP_ERR_FLAG                  SDHC_ADMAES_ADMADCE_MASK

/* HTCAPBLT */
#define SDHC_HAL_SUPPORT_ADMA           SDHC_HTCAPBLT_ADMAS_MASK
#define SDHC_HAL_SUPPORT_HIGHSPEED     SDHC_HTCAPBLT_HSS_MASK
#define SDHC_HAL_SUPPORT_DMA            SDHC_HTCAPBLT_DMAS_MASK
#define SDHC_HAL_SUPPORT_SUSPEND_RESUME SDHC_HTCAPBLT_SRS_MASK
#define SDHC_HAL_SUPPORT_3_3_V          SDHC_HTCAPBLT_VS33_MASK
#define SDHC_HAL_SUPPORT_3_0_V          SDHC_HTCAPBLT_VS30_MASK
#define SDHC_HAL_SUPPORT_1_8_V          SDHC_HTCAPBLT_VS18_MASK

/* FEVT */
#define SDHC_HAL_ACMD12_NOT_EXEC_ERR_EVENT  SDHC_FEVT_AC12NE_MASK
#define SDHC_HAL_ACMD12_TIMEOUT_ERR_EVENT   SDHC_FEVT_AC12TOE_MASK
#define SDHC_HAL_ACMD12_CRC_ERR_EVENT       SDHC_FEVT_AC12CE_MASK
#define SDHC_HAL_ACMD12_END_BIT_ERR_EVENT   SDHC_FEVT_AC12EBE_MASK
#define SDHC_HAL_ACMD12_INDEX_ERR_EVENT     SDHC_FEVT_AC12IE_MASK
#define SDHC_HAL_ACMD12_NOT_ISSUE_ERR_EVENT SDHC_FEVT_CNIBAC12E_MASK
#define SDHC_HAL_CMD_TIMEOUT_ERR_EVENT      SDHC_FEVT_CTOE_MASK
#define SDHC_HAL_CMD_CRC_ERR_EVENT          SDHC_FEVT_CCE_MASK
#define SDHC_HAL_CMD_END_BIT_ERR_EVENT      SDHC_FEVT_CEBE_MASK
#define SDHC_HAL_CMD_INDEX_ERR_EVENT        SDHC_FEVT_CIE_MASK
#define SDHC_HAL_DATA_TIMEOUT_ERR_EVENT     SDHC_FEVT_DTOE_MASK
#define SDHC_HAL_DATA_CRC_ERR_EVENT         SDHC_FEVT_DCE_MASK
#define SDHC_HAL_DATA_END_BIT_ERR_EVENT     SDHC_FEVT_DEBE_MASK
#define SDHC_HAL_ACMD12_ERR_EVENT           SDHC_FEVT_AC12E_MASK
#define SDHC_HAL_CARD_INT_EVENT             SDHC_FEVT_CINT_MASK
#define SDHC_HAL_DMA_ERROR_EVENT            SDHC_FEVT_DMAE_MASK

/*! @brief MMC card BOOT type */
typedef enum _sdhc_hal_mmcboot {
    kSdhcHalMmcbootNormal = 0,
    kSdhcHalMmcbootAlter = 1,
} sdhc_hal_mmcboot_t;

/*! @brief Led control status */
typedef enum _sdhc_hal_led {
    kSdhcHalLedOff = 0,
    kSdhcHalLedOn = 1,
} sdhc_hal_led_t;

/*! @brief Data transfer width */
typedef enum _sdhc_hal_dtw {
    kSdhcHalDtw1Bit = 0,
    kSdhcHalDtw4Bit = 1,
    kSdhcHalDtw8Bit = 2,
} sdhc_hal_dtw_t;

/*! @brief SDHC endian mode */
typedef enum _sdhc_hal_endian {
    kSdhcHalEndianBig = 0,
    kSdhcHalEndianHalfWordBig = 1,
    kSdhcHalEndianLittle = 2,
} sdhc_hal_endian_t;

/*! @brief SDHC DMA mode */
typedef enum _sdhc_hal_dma_mode {
    kSdhcHalDmaSimple = 0,
    kSdhcHalDmaAdma1 = 1,
    kSdhcHalDmaAdma2 = 2,
} sdhc_hal_dma_mode_t;

/*! @brief SDHC ADMA address alignment size and length alignment size */
#define SDHC_HAL_ADMA1_ADDR_ALIGN           (4096)
#define SDHC_HAL_ADMA1_LEN_ALIGN            (4096)
#define SDHC_HAL_ADMA2_ADDR_ALIGN           (4)
#define SDHC_HAL_ADMA2_LEN_ALIGN            (4)

/*
 * ADMA1 descriptor table
 * |------------------------|---------|--------------------------|
 * | Address/page Field     |reserved |         Attribute        |
 * |------------------------|---------|--------------------------|
 * |31                    12|11      6|05  |04  |03|02 |01 |00   |
 * |------------------------|---------|----|----|--|---|---|-----|
 * | address or data length | 000000  |Act2|Act1| 0|Int|End|Valid|
 * |------------------------|---------|----|----|--|---|---|-----|
 *
 *
 * |------|------|-----------------|-------|-------------|
 * | Act2 | Act1 |     Comment     | 31-28 | 27 - 12     |
 * |------|------|-----------------|---------------------|
 * |   0  |   0  | No op           | Don't care          |
 * |------|------|-----------------|-------|-------------|
 * |   0  |   1  | Set data length |  0000 | Data Length |
 * |------|------|-----------------|-------|-------------|
 * |   1  |   0  | Transfer data   | Data address        |
 * |------|------|-----------------|---------------------|
 * |   1  |   1  | Link descriptor | Descriptor address  |
 * |------|------|-----------------|---------------------|
 *
 */
typedef uint32_t sdhc_hal_adma1_descriptor_t;
#define SDHC_HAL_ADMA1_DESC_VALID_MASK           (1 << 0)
#define SDHC_HAL_ADMA1_DESC_END_MASK             (1 << 1)
#define SDHC_HAL_ADMA1_DESC_INT_MASK             (1 << 2)
#define SDHC_HAL_ADMA1_DESC_ACT1_MASK            (1 << 4)
#define SDHC_HAL_ADMA1_DESC_ACT2_MASK            (1 << 5)
#define SDHC_HAL_ADMA1_DESC_TYPE_NOP             (SDHC_HAL_ADMA1_DESC_VALID_MASK)
#define SDHC_HAL_ADMA1_DESC_TYPE_TRAN            (SDHC_HAL_ADMA1_DESC_ACT2_MASK | SDHC_HAL_ADMA1_DESC_VALID_MASK)
#define SDHC_HAL_ADMA1_DESC_TYPE_LINK            (SDHC_HAL_ADMA1_DESC_ACT1_MASK | SDHC_HAL_ADMA1_DESC_ACT2_MASK | SDHC_HAL_ADMA1_DESC_VALID_MASK)
#define SDHC_HAL_ADMA1_DESC_TYPE_SET             (SDHC_HAL_ADMA1_DESC_ACT1_MASK | SDHC_HAL_ADMA1_DESC_VALID_MASK)
#define SDHC_HAL_ADMA1_DESC_ADDRESS_SHIFT        (12)
#define SDHC_HAL_ADMA1_DESC_ADDRESS_MASK         (0xFFFFFU)
#define SDHC_HAL_ADMA1_DESC_LEN_SHIFT            (12)
#define SDHC_HAL_ADMA1_DESC_LEN_MASK             (0xFFFFU)
#define SDHC_HAL_ADMA1_DESC_MAX_LEN_PER_ENTRY    (SDHC_HAL_ADMA1_DESC_LEN_MASK + 1)

/*
 * ADMA2 descriptor table
 * |----------------|---------------|-------------|--------------------------|
 * | Address Field  |     length    | reserved    |         Attribute        |
 * |----------------|---------------|-------------|--------------------------|
 * |63            32|31           16|15         06|05  |04  |03|02 |01 |00   |
 * |----------------|---------------|-------------|----|----|--|---|---|-----|
 * | 32-bit address | 16-bit length | 0000000000  |Act2|Act1| 0|Int|End|Valid|
 * |----------------|---------------|-------------|----|----|--|---|---|-----|
 *
 *
 * | Act2 | Act1 |     Comment     | Operation                                                         |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   0  |   0  | No op           | Don't care                                                        |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   0  |   1  | Reserved        | Read this line and go to next one                                 |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   1  |   0  | Transfer data   | Transfer data with address and length set in this descriptor line |
 * |------|------|-----------------|-------------------------------------------------------------------|
 * |   1  |   1  | Link descriptor | Link to another descriptor                                        |
 * |------|------|-----------------|-------------------------------------------------------------------|
 *
 */
typedef struct SdhcHalAdma2Descriptor {
    uint32_t attribute;
    uint32_t *address;
} sdhc_hal_adma2_descriptor_t;

/* ADMA1 descriptor control and status mask */
#define SDHC_HAL_ADMA2_DESC_VALID_MASK           (1 << 0)
#define SDHC_HAL_ADMA2_DESC_END_MASK             (1 << 1)
#define SDHC_HAL_ADMA2_DESC_INT_MASK             (1 << 2)
#define SDHC_HAL_ADMA2_DESC_ACT1_MASK            (1 << 4)
#define SDHC_HAL_ADMA2_DESC_ACT2_MASK            (1 << 5)
#define SDHC_HAL_ADMA2_DESC_TYPE_NOP             (SDHC_HAL_ADMA2_DESC_VALID_MASK)
#define SDHC_HAL_ADMA2_DESC_TYPE_RCV             (SDHC_HAL_ADMA2_DESC_ACT1_MASK | SDHC_HAL_ADMA2_DESC_VALID_MASK)
#define SDHC_HAL_ADMA2_DESC_TYPE_TRAN            (SDHC_HAL_ADMA2_DESC_ACT2_MASK | SDHC_HAL_ADMA2_DESC_VALID_MASK)
#define SDHC_HAL_ADMA2_DESC_TYPE_LINK            (SDHC_HAL_ADMA2_DESC_ACT1_MASK | SDHC_HAL_ADMA2_DESC_ACT2_MASK | SDHC_HAL_ADMA2_DESC_VALID_MASK)
#define SDHC_HAL_ADMA2_DESC_LEN_SHIFT            (16)
#define SDHC_HAL_ADMA2_DESC_LEN_MASK             (0xFFFFU)
#define SDHC_HAL_ADMA2_DESC_MAX_LEN_PER_ENTRY    (SDHC_HAL_ADMA2_DESC_LEN_MASK)

/* Card response type */
#define SDHC_HAL_RST_TYPE_ALL               SDHC_SYSCTL_RSTA_MASK
#define SDHC_HAL_RST_TYPE_CMD               SDHC_SYSCTL_RSTC_MASK
#define SDHC_HAL_RST_TYPE_DATA              SDHC_SYSCTL_RSTD_MASK

/* Maximum block length SDHC support */
#define SDHC_HAL_MAX_BLKLEN_512B            (0U)
#define SDHC_HAL_MAX_BLKLEN_1024B           (1U)
#define SDHC_HAL_MAX_BLKLEN_2048B           (2U)
#define SDHC_HAL_MAX_BLKLEN_4096B           (3U)

/* Voltage Support 3.3 V */ 
#define SDHC_HAL_SUPPORT_V330_FLAG                   (1U << 0)
/* Voltage Support 3.0 V */
#define SDHC_HAL_SUPPORT_V300_FLAG                   (1U << 1)
/* High Speed Support */
#define SDHC_HAL_SUPPORT_HIGHSPEED_FLAG              (1U << 2)
/* DMA Support */
#define SDHC_HAL_SUPPORT_DMA_FLAG                    (1U << 3)
/* ADMA Support */
#define SDHC_HAL_SUPPORT_ADMA_FLAG                   (1U << 4)
/* Suspend/Resume Support */
#define SDHC_HAL_SUPPORT_SUSPEND_RESUME_FLAG         (1U << 5)
/* Voltage Support 1.8 V */
#define SDHC_HAL_SUPPORT_V180_FLAG                   (1U << 6)
/* Support external dma */
#define SDHC_HAL_SUPPORT_EXDMA_FLAG                  (1U << 7)

/*! @brief Data structure to get the basic information of SDHC */
typedef struct SdhcHalBasicInfo
{
    uint8_t specVer;               /*!< Save the specification version */
    uint8_t vendorVer;             /*!< Save the vendor version */
    uint16_t maxBlkLen;             /*!< Save the maximum block length */
    uint32_t capability;           /*!< The capability flags */
}sdhc_hal_basic_info_t;

/*! @brief SD clock configuration to configure the clock of SD protocol unit */
typedef struct SdhcHalSdClkConfig
{
    bool enable;
    uint32_t maxHostClk;
    uint32_t destClk;
}sdhc_hal_sdclk_config_t;

/*! @brief Current SDHC status type */
typedef enum _sdhc_hal_curstat_type_t {
    kSdhcHalIsCmdInhibit,          /*!< Checks whether the command inhibit bit is set or not. */
    kSdhcHalIsDataInhibit,         /*!< Checks whether data inhibit bit is set or not. */
    kSdhcHalIsDataLineActive,      /*!< Checks whether data line is active. */
    kSdhcHalIsSdClockStable,       /*!< Checks whether the SD clock is stable or not. */
    kSdhcHalIsIpgClockOff,         /*!< Checks whether the  IPG clock is off or not. */
    kSdhcHalIsSysClockOff,         /*!< Checks whether the system clock is off or not. */
    kSdhcHalIsPeripheralClockOff,  /*!< Checks whether the peripheral clock is off or not. */
    kSdhcHalIsSdClkOff,            /*!< Checks whether  the  SD clock is off or not. */
    kSdhcHalIsWriteTransferActive, /*!< Checks whether the write transfer is active or not. */
    kSdhcHalIsReadTransferActive,  /*!< Checks whether the read transfer is active or not. */
    kSdhcHalIsBuffWriteEnabled,    /*!< Check whether the buffer write is enabled or not. */
    kSdhcHalIsBuffReadEnabled,     /*!< Checks whether the buffer read is enabled or not. */
    kSdhcHalIsCardInserted,        /*!< Checks whether the  card is inserted or not. */
    kSdhcHalIsCmdLineLevelHigh,    /*!< Checks whether the command line signal is high or not. */
    kSdhcHalGetDataLine0Level,      /*!< Gets the data line 0 signal level or not. */
    kSdhcHalGetDataLine1Level,      /*!< Gets the data line 1 signal level or not. */
    kSdhcHalGetDataLine2Level,      /*!< Gets the data line 2 signal level or not. */
    kSdhcHalGetDataLine3Level,      /*!< Gets the data line 3 signal level or not. */
    kSdhcHalGetDataLine4Level,      /*!< Gets the data line 4 signal level or not. */
    kSdhcHalGetDataLine5Level,      /*!< Gets the data line 5 signal level or not. */
    kSdhcHalGetDataLine6Level,      /*!< Gets the data line 6 signal level or not. */
    kSdhcHalGetDataLine7Level,      /*!< Gets the data line 7 signal level or not. */
    kSdhcHalGetCdTestLevel,        /*!< Gets the card detect test level. */
}sdhc_hal_curstat_type_t;

/* DAT3 As Card Detection Pin */
#define SDHC_HAL_EN_D3CD_FLAG                           (1U << 0)
/* Enables the card detect signal selection. */
#define SDHC_HAL_EN_CD_SIG_SEL_FLAG                     (1U << 1)
/* Enables stop at the block gap. */
#define SDHC_HAL_EN_STOP_AT_BLK_GAP_FLAG                (1U << 2)
/* Enables the read wait control for the SDIO cards. */
#define SDHC_HAL_EN_READ_WAIT_CTRL_FLAG                 (1U << 3)
/* Enables  stop at the block gap requests interrupt. */
#define SDHC_HAL_EN_INT_STOP_AT_BLK_GAP_FLAG            (1U << 4)
/* Enables wakeup event on the card interrupt. */
#define SDHC_HAL_EN_WAKEUP_ON_CARD_INT_FLAG             (1U << 5)
/* Enables wakeup event on the card insertion. */
#define SDHC_HAL_EN_WAKEUP_ON_CARD_INS_FLAG             (1U << 6)
/* Enables  wakeup event on card removal. */
#define SDHC_HAL_EN_WAKEUP_ON_CARD_REM_FLAG             (1U << 7)
/* Enables the external DMA request. */
#define SDHC_HAL_EN_EXT_DMA_REQ_FLAG                    (1U << 8)
/* Enables the exact block number for the SDIO CMD53. */ 
#define SDHC_HAL_EN_EXACT_BLK_NUM_FLAG                  (1U << 9)

/* Enables the boot ACK. */
#define SDHC_HAL_EN_BOOT_ACK_FLAG                           (1 << 0)
/* Enables the fast boot. */
#define SDHC_HAL_EN_FAST_BOOT_FLAG                          (1 << 1)
/* Enables the automatic stop at the block gap. */
#define SDHC_HAL_EN_BOOT_STOP_AT_BLK_GAP_FLAG               (1 << 2)

/*! @brief Data structure to configure the MMC boot feature */
typedef struct SdhcHalMmcBootParam
{
    uint32_t ackTimeout;      /*!< Sets the timeout value for the boot ACK. */
    sdhc_hal_mmcboot_t mode;  /*!< Configures the boot mode. */
    uint32_t blockCount;      /*!< Configures the the block count for the boot. */
    uint32_t enFlags;
}sdhc_mmcboot_param_t;

/*! @brief Data structure to initialize the SDHC */
typedef struct SdhcHalInitConfig
{
    sdhc_hal_led_t ledState;          /*!< Sets the LED state. */ 
    sdhc_hal_endian_t endianMode;     /*!< Configures the endian mode. */
    sdhc_hal_dma_mode_t dmaMode;      /*!< Sets the DMA mode. */
    uint8_t writeWatermarkLevel;      /*!< Sets the watermark for writing. */
    uint8_t readWatermarkLevel;       /*!< Sets the watermark for reading. */
    uint32_t enFlags;                 /*!< Enable or disable corresponding feature */
    sdhc_mmcboot_param_t bootParams;  /*!< Configuration read MMC card boot data feature*/
}sdhc_hal_config_t;

/*! @brief Command request structure */
typedef struct SdhcHalCmdReq
{
    uint32_t dataBlkSize;                             /*!< Command data Block size */
    uint32_t dataBlkCount;                            /*!< Command data Block count */
    uint32_t arg;                                     /*!< Command argument */
    uint32_t index;                                   /*!< Command index */
    uint32_t flags;                                   /*!< Command Flags */
}sdhc_hal_cmd_req_t;

/*! @brief SDHC error type */
typedef enum _sdhc_hal_err_type
{
    kAc12Err,                 /*!< Auto CMD12 error */
    kAdmaErr,                 /*!< ADMA error */     
}sdhc_hal_err_type_t;



/*************************************************************************************************
 * API
 ************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @name SDHC HAL FUNCTION */
/*@{ */

/*!
 * @brief Sends command to card.
 *
 * @param base SDHC base address
 * @param cmdReq command request structure
 */
void SDHC_HAL_SendCmd(SDHC_Type * base, const sdhc_hal_cmd_req_t* cmdReq);

/*!
 * @brief Fills the the data port.
 *
 * @param base SDHC base address
 * @param data the data about to be sent
 */
static inline void SDHC_HAL_SetData(SDHC_Type * base, uint32_t data)
{
    SDHC_WR_DATPORT(base, data);
}

/*!
 * @brief Retrieves the data from the data port.
 *
 * @param base SDHC base address
 * @return the data has been read
 */
static inline uint32_t SDHC_HAL_GetData(SDHC_Type * base)
{
    return SDHC_RD_DATPORT(base);
}

/*!
 * @brief Gets the current card's status.
 *
 * @param base SDHC base address
 * @param stateType The status type.
 * @return the status if happened corresponding to stateType
 *        - true: status flag has been set
 *        - false: status flag has not been set
 */
bool SDHC_HAL_GetCurState(SDHC_Type * base, sdhc_hal_curstat_type_t stateType);

/*!
 * @brief Sets the data transfer width.
 *
 * @param base SDHC base address
 * @param dtw data transfer width
 */
static inline void SDHC_HAL_SetDataTransferWidth(SDHC_Type * base, sdhc_hal_dtw_t dtw)
{
    SDHC_BWR_PROCTL_DTW(base, dtw);
}

/*!
* @brief Restarts a transaction which has stopped at the block gap.
*
* @param base SDHC base address
*/
static inline void SDHC_HAL_SetContinueRequest(SDHC_Type * base)
{
    SDHC_BWR_PROCTL_CREQ(base, 1);
}

/*!
* @brief Initialize the SDHC according to the configuration user input.
*
* @param base SDHC base address
* @param initConfig The configuration structure 
*/
void SDHC_HAL_Config(SDHC_Type * base, const sdhc_hal_config_t* initConfig);

/*!
 * @brief Sets SDHC SD protocol unit clock.
 *
 * @param base SDHC base address
 * @param clkConfItms SDHC SD protocol unit clock configuration items. 
 */
void SDHC_HAL_ConfigSdClock(SDHC_Type * base, sdhc_hal_sdclk_config_t* clkConfItms);

/*!
* @brief Gets the current interrupt status.
*
* @param base SDHC base address
* @return current interrupt flags
*/
static inline uint32_t SDHC_HAL_GetIntFlags(SDHC_Type * base)
{
    return SDHC_RD_IRQSTAT(base);
}

/*!
* @brief Clears a specified interrupt status.
*
* @param base SDHC base address
* @param mask to specify interrupts' flags to be cleared
*/
static inline void SDHC_HAL_ClearIntFlags(SDHC_Type * base, uint32_t mask)
{
    SDHC_WR_IRQSTAT(base, mask);
}

/*!
 * @brief Gets the error status of SDHC.
 *
 * @param base SDHC base address
 * @param errType the error type
 * @param errFlags the result error flags
*/
void SDHC_HAL_GetAllErrStatus(SDHC_Type * base, sdhc_hal_err_type_t errType, uint32_t* errFlags);

/*!
* @brief Sets the force events according to the given mask.
*
* @param base SDHC base address
* @param mask to specify the force events' flags to be set
*/
static inline void SDHC_HAL_SetForceEventFlags(SDHC_Type * base, uint32_t mask)
{
    SDHC_WR_FEVT(base, mask);
}

/*!
* @brief Sets the ADMA address.
*
* @param base SDHC base address
* @param address for ADMA transfer
*/
static inline void SDHC_HAL_SetAdmaAddress(SDHC_Type * base, uint32_t address)
{
    /* When use ADMA, disable simple DMA*/
    SDHC_WR_DSADDR(base, 0);
    SDHC_WR_ADSADDR(base, address);
}

/*!
 * @brief Gets the command response.
 *
 * @param base SDHC base address
 * @param index of response register, range from 0 to 3
 * @return The command response value.
 */
uint32_t SDHC_HAL_GetResponse(SDHC_Type * base, uint32_t index);

/*!
* @brief Enables the specified interrupts.
*
* @param base SDHC base address
* @param enable enable or disable
* @param mask to specify interrupts to be isEnabledd
*/
void SDHC_HAL_SetIntSignal(SDHC_Type * base, bool enable, uint32_t mask);

/*!
* @brief Enables the specified interrupt state.
*
* @param base SDHC base address
* @param enable enable or disable
* @param mask to specify interrupts' state to be enabled
*/
void SDHC_HAL_SetIntState(SDHC_Type * base, bool enable, uint32_t mask);

/*!
* @brief Performs an SDHC reset.
*
* @param base SDHC base address
* @param type the type of reset
* @param timeout timeout for reset
* @return 0 on success, else on error
*/
uint32_t SDHC_HAL_Reset(SDHC_Type * base, uint32_t type, uint32_t timeout);

/*!
* @brief Sends 80 clocks to the card to initialize the card.
*
* @param base SDHC base address
* @param timeout timeout for initialize card
* @return 0 on success, else on error
*/
uint32_t SDHC_HAL_InitCard(SDHC_Type * base, uint32_t timeout);

/*!
 * @brief Initializes the SDHC HAL.
 *
 * @param base SDHC base address
 */
void SDHC_HAL_Init(SDHC_Type * base);

/*!
 * @brief Gets the capability of SDHC.
 *
 * @param base SDHC base address
 * @param basicInfo Pointer to user data structure.
 */
void SDHC_HAL_GetBasicInfo(SDHC_Type * base, sdhc_hal_basic_info_t* basicInfo);

/*@} */
#if defined(__cplusplus)
}
#endif
/*! @} */

#endif

#endif
/*************************************************************************************************
 * EOF
 ************************************************************************************************/

