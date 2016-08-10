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

#ifndef __SDMMC_H__
#define __SDMMC_H__

/*! @addtogroup sdhc_card_std_def */
/*! @{ */

#define SDMMC_CARD_BUSY         ((uint32_t) 1 << 31)     /*!< card initialization complete */

#define SD_SCR_BUS_WIDTHS_1BIT  (1 << 0)                /*!< card supports 1 bit mode */
#define SD_SCR_BUS_WIDTHS_4BIT  (1 << 2)                /*!< card supports 4 bit mode */

#define SD_CCC_BASIC            (1 << 0)                /*!< Card command class 0 */
#define SD_CCC_BLOCK_READ       (1 << 2)                /*!< Card command class 2 */
#define SD_CCC_BLOCK_WRITE      (1 << 4)                /*!< Card command class 4 */
#define SD_CCC_ERASE            (1 << 5)                /*!< Card command class 5 */
#define SD_CCC_WRITE_PROTECTION (1 << 6)                /*!< Card command class 6 */
#define SD_CCC_LOCK_CARD        (1 << 7)                /*!< Card command class 7 */
#define SD_CCC_APP_SPEC         (1 << 8)                /*!< Card command class 8 */
#define SD_CCC_IO_MODE          (1 << 9)                /*!< Card command class 9 */
#define SD_CCC_SWITCH           (1 << 10)               /*!< Card command class 10 */

#define SD_OCR_CCS              (1 << 30)               /*!< card capacity status */
#define SD_OCR_HCS              (1 << 30)               /*!< card capacity status */
#define SD_OCR_XPC              (1 << 28)               /*!< SDXC power control */
#define SD_OCR_S18R             (1 << 24)               /*!< switch to 1.8V request */
#define SD_OCR_S18A             SD_OCR_S18R             /*!< switch to 1.8V accepted */

#define SD_HIGHSPEED_BUSY       (0x00020000U)           /*!< SD card high speed busy status bit in CMD6 response */
#define SD_HIGHSPEED_SUPPORTED  (0x00020000U)           /*!< SD card high speed support bit in CMD6 response */

#define SD_OCR_VDD_27_28        (1 << 15)               /*!< VDD 2.7-2.8 */
#define SD_OCR_VDD_28_29        (1 << 16)               /*!< VDD 2.8-2.9 */
#define SD_OCR_VDD_29_30        (1 << 17)               /*!< VDD 2.9-3.0 */
#define SD_OCR_VDD_30_31        (1 << 18)               /*!< VDD 3.0-3.1 */
#define SD_OCR_VDD_31_32        (1 << 19)               /*!< VDD 3.1-3.2 */
#define SD_OCR_VDD_32_33        (1 << 20)               /*!< VDD 3.2-3.3 */
#define SD_OCR_VDD_33_34        (1 << 21)               /*!< VDD 3.3-3.4 */
#define SD_OCR_VDD_34_35        (1 << 22)               /*!< VDD 3.4-3.5 */
#define SD_OCR_VDD_35_36        (1 << 23)               /*!< VDD 3.5-3.6 */

#define SDMMC_CLK_100KHZ        (100000U)
#define SDMMC_CLK_400KHZ        (400000U)
#define SDMMC_CLK_25MHZ         (25000000U)
#define SDMMC_CLK_50MHZ         (50000000U)

#define SDMMC_R1_OUT_OF_RANGE         ((uint32_t) 1 << 31)        /*!< R1: out of range status bit */
#define SDMMC_R1_ADDRESS_ERROR        (1 << 30)                 /*!< R1: address error status bit */
#define SDMMC_R1_BLOCK_LEN_ERROR      (1 << 29)                 /*!< R1: block length error status bit */
#define SDMMC_R1_ERASE_SEQ_ERROR      (1 << 28)                 /*!< R1: erase sequence error status bit */
#define SDMMC_R1_ERASE_PARAM          (1 << 27)                 /*!< R1: erase parameter error status bit */
#define SDMMC_R1_WP_VIOLATION         (1 << 26)                 /*!< R1: write protection violation status bit */
#define SDMMC_R1_CARD_IS_LOCKED       (1 << 25)                 /*!< R1: card locked status bit */
#define SDMMC_R1_LOCK_UNLOCK_FAILED   (1 << 24)                 /*!< R1: lock/unlock error status bit */
#define SDMMC_R1_COM_CRC_ERROR        (1 << 23)                 /*!< R1: CRC error status bit */
#define SDMMC_R1_ILLEGAL_COMMAND      (1 << 22)                 /*!< R1: illegal command status bit */
#define SDMMC_R1_CARD_ECC_FAILED      (1 << 21)                 /*!< R1: card ecc error status bit */
#define SDMMC_R1_CC_ERROR             (1 << 20)                 /*!< R1: internal card controller status bit */
#define SDMMC_R1_ERROR                (1 << 19)                 /*!< R1: a general or an unknown error status bit */
#define SDMMC_R1_CID_CSD_OVERWRITE    (1 << 16)                 /*!< R1: cid/csd overwrite status bit */
#define SDMMC_R1_WP_ERASE_SKIP        (1 << 15)                 /*!< R1: write protection erase skip status bit */
#define SDMMC_R1_CARD_ECC_DISABLED    (1 << 14)                 /*!< R1: card ecc disabled status bit */
#define SDMMC_R1_ERASE_RESET          (1 << 13)                 /*!< R1: erase reset status bit */
#define SDMMC_R1_STATUS(x)            ((uint32_t)(x) & 0xFFFFE000U)       /*!< R1: status */
#define SDMMC_R1_READY_FOR_DATA       (1 << 8)                  /*!< R1: ready for data status bit */
#define SDMMC_R1_SWITCH_ERROR         (1 << 7)                  /*!< R1: switch error status bit */
#define SDMMC_R1_APP_CMD              (1 << 5)                  /*!< R1: application command enabled status bit */
#define SDMMC_R1_AKE_SEQ_ERROR        (1 << 3)                  /*!< R1: error in the sequence of the authentication process*/
#define SDMMC_R1_ERROR_BITS(x)  (uint32_t)((x) & \
                              (SDMMC_R1_OUT_OF_RANGE | \
                               SDMMC_R1_ADDRESS_ERROR | \
                               SDMMC_R1_BLOCK_LEN_ERROR | \
                               SDMMC_R1_ERASE_SEQ_ERROR | \
                               SDMMC_R1_ERASE_PARAM | \
                               SDMMC_R1_WP_VIOLATION | \
                               SDMMC_R1_CARD_IS_LOCKED | \
                               SDMMC_R1_LOCK_UNLOCK_FAILED | \
                               SDMMC_R1_COM_CRC_ERROR | \
                               SDMMC_R1_ILLEGAL_COMMAND | \
                               SDMMC_R1_CARD_ECC_FAILED | \
                               SDMMC_R1_CC_ERROR | \
                               SDMMC_R1_ERROR | \
                               SDMMC_R1_CID_CSD_OVERWRITE | \
                               SDMMC_R1_AKE_SEQ_ERROR)) /*!< Check error card status */

#define SDMMC_R1_CURRENT_STATE(x)     (((x) & 0x00001E00U) >> 9)/*!< R1: current state */
#define SDMMC_R1_STATE_IDLE           (0U)                      /*!< R1: current state: idle */
#define SDMMC_R1_STATE_READY          (1U)                      /*!< R1: current state: ready */
#define SDMMC_R1_STATE_IDENT          (2U)                      /*!< R1: current state: ident */
#define SDMMC_R1_STATE_STBY           (3U)                      /*!< R1: current state: stby */
#define SDMMC_R1_STATE_TRAN           (4U)                      /*!< R1: current state: tran */
#define SDMMC_R1_STATE_DATA           (5U)                      /*!< R1: current state: data */
#define SDMMC_R1_STATE_RCV            (6U)                      /*!< R1: current state: rcv */
#define SDMMC_R1_STATE_PRG            (7U)                      /*!< R1: current state: prg */
#define SDMMC_R1_STATE_DIS            (8U)                      /*!< R1: current state: dis */

#define SDMMC_SD_VERSION_1_0         (1 << 0)                   /*!< SD card version 1.0 */
#define SDMMC_SD_VERSION_1_1         (1 << 1)                   /*!< SD card version 1.1 */
#define SDMMC_SD_VERSION_2_0         (1 << 2)                   /*!< SD card version 2.0 */
#define SDMMC_SD_VERSION_3_0         (1 << 3)                   /*!< SD card version 3.0 */

/* SPI mode related */
#define SDMMC_SPI_R1_IN_IDLE_STATE   (1 << 0)
#define SDMMC_SPI_R1_ERASE_RESET     (1 << 1)
#define SDMMC_SPI_R1_ILLEGAL_CMD     (1 << 2)
#define SDMMC_SPI_R1_COM_CRC_ERR     (1 << 3)
#define SDMMC_SPI_R1_ERASE_SEQ_ERR   (1 << 4)
#define SDMMC_SPI_R1_ADDRESS_ERR     (1 << 5)
#define SDMMC_SPI_R1_PARAMETER_ERR   (1 << 6)

#define SDMMC_SPI_R2_CARD_LOCKED     (1 << 0)
#define SDMMC_SPI_R2_WP_LOCK_FAILED  (1 << 1)
#define SDMMC_SPI_R2_ERR             (1 << 2)
#define SDMMC_SPI_R2_CC_ERR          (1 << 3)
#define SDMMC_SPI_R2_CARD_ECC_FAILED (1 << 4)
#define SDMMC_SPI_R2_WP_VIOLATION    (1 << 5)
#define SDMMC_SPI_R2_ERASE_PARAM     (1 << 6)
#define SDMMC_SPI_R2_OUT_OF_RANGE    (1 << 7)
#define SDMMC_SPI_R2_CSD_OVERWRITE   (1 << 7)

#define SDMMC_SPI_R7_VERSION_SHIFT   (28)
#define SDMMC_SPI_R7_VERSION_MASK    (0xF)
#define SDMMC_SPI_R7_VOLTAGE_SHIFT   (8)
#define SDMMC_SPI_R7_VOLTAGE_MASK    (0xF)
#define SDMMC_SPI_R7_VOLTAGE_27_36   ((uint32_t) 0x1 << SDMMC_SPI_R7_VOLTAGE_SHIFT)
#define SDMMC_SPI_R7_ECHO_SHIFT      (0)
#define SDMMC_SPI_R7_ECHO_MASK       ((uint32_t) 0xFF)

/* Data Error Token */
#define SDMMC_SPI_DET_MASK           (0xF)
#define SDMMC_SPI_DET_ERROR          (1 << 0)       /*!< Data error */
#define SDMMC_SPI_DET_CC_ERROR       (1 << 1)       /*!< CC error */
#define SDMMC_SPI_DET_ECC_FAILED     (1 << 2)       /*!< Card ecc error */
#define SDMMC_SPI_DET_OUT_OF_RANGE   (1 << 3)       /*!< Out of range */

/* Data Token */
#define SDMMC_SPI_DT_START_SINGLE_BLK (0xFEU)       /*!< First byte of block, single block */
#define SDMMC_SPI_DT_START_MULTI_BLK  (0xFCU)       /*!< First byte of block, multi-block */
#define SDMMC_SPI_DT_STOP_TRANSFER    (0xFDU)       /*!< Stop transmission */

/* Data Response */
#define SDMMC_SPI_DR_MASK             (0x1F)        /*!< Mask for data response bits */
#define SDMMC_SPI_DR_ACCEPTED         (0x05)        /*!< Data accepted */
#define SDMMC_SPI_DR_CRC_ERROR        (0x0B)        /*!< Data rejected due to CRC error */
#define SDMMC_SPI_DR_WRITE_ERROR      (0x0D)        /*!< Data rejected due to write error */

typedef enum _mmc_cmd_t {           /*   type     argument        response */
    kMmcSetRelativeAddr = 3,        /*!< ac       [31:16] RCA     R1 */
    kMmcSleepAwake = 5,             /*!< ac       [31:16] RCA     R1b */
                                    /*!<          [15] flag */
    kMmcSwitch = 6,                 /*!< ac       [31:16] RCA     R1b */
    kMmcSendExtCsd = 8,             /*!< adtc                     R1 */
    kMmcReadDataUntilStop = 11,     /*!< adtc     [31:0] data     R1 */
                                    /*!<          address */
    kMmcBusTestRead = 14,           /*!< adtc                     R1 */
    kMmcWriteDataUntilStop = 20,    /*!< ac       [31:0] data    R1 */
                                    /*!<          address */
    kMmcProgramCid = 26,            /*!< adtc                     R1 */
    kMmcEraseGroupStart = 35,       /*!< ac       [31:0] data     R1 */
                                    /*!<          address */
    kMmcEraseGroupEnd = 36,         /*!< ac       [31:0] data     R1 */
                                    /*!<          address */
    kMmcFastIo = 39,                /*!< ac                       R4 */
    kMmcGoIrqState = 40,            /*!< bcr                      R5 */
} mmc_cmd_t;

typedef enum _sdmmc_cmd_t {
    kGoIdleState = 0,               /*!< bc */
    kSendOpCond = 1,                /*!< bcr      [31:0] OCR      R3 */
    kAllSendCid = 2,                /*!< bcr                      R2 */
    kSetDsr = 4,                    /*!< bc       [31:16] RCA */
    kSelectCard = 7,                /*!< ac       [31:16] RCA     R1b */
    kSendCsd = 9,                   /*!< ac       [31:16] RCA     R2 */
    kSendCid = 10,                  /*!< ac       [31:16] RCA     R2 */
    kStopTransmission = 12,         /*!< ac       [31:16] RCA     R1b */
    kSendStatus = 13,               /*!< ac       [31:16] RCA     R1 */
    kGoInactiveState = 15,          /*!< ac       [31:16] RCA */

    kSetBlockLen = 16,              /*!< ac       [31:0] block    R1 */
                                    /*!<          length */
    kReadSingleBlock = 17,          /*!< adtc     [31:0] data     R1 */
                                    /*!<          address */
    kReadMultipleBlock = 18,        /*!< adtc     [31:0] data     R1 */
                                    /*!<          address */
    kSendTuningBlock = 19,          /*!< adtc     [31:0] all      R1 */
                                    /*!<          zero */
    kSetBlockCount = 23,            /*!< ac       [31:0] block    R1 */
                                    /*!<          count */
    kWriteBlock = 24,               /*!< adtc     [31:0] data     R1 */
                                    /*!<          address */
    kWriteMultipleBlock = 25,       /*!< adtc     [31:0] data     R1 */
                                    /*!<          address */
    kProgramCsd = 27,               /*!< adtc                     R1 */
    kSetWriteProt = 28,             /*!< ac       [31:0] data     R1b */
                                    /*!<          address */
    kClrWriteProt = 29,             /*!< ac       [31:0] data     R1b */
                                    /*!<          address */
    kSendWriteProt = 30,            /*!< adtc     [31:0] write    R1b */
                                    /*!<          protect data */
                                    /*!<          address */
    kErase = 38,                    /*!< ac                       R1 */
    kLockUnlock = 42,               /*!< adtc     all zero        R1 */
    kAppCmd = 55,                   /*!< ac       [31:16] RCA     R1 */
    kGenCmd = 56,                   /*!< adtc     [0] RD/WR       R1 */
    kReadOcr = 58,
} sdmmc_cmd_t;

typedef enum _sd_cmd_t {
    kSdSendRelativeAddr = 3,        /*!< bcr                      R6 */
    kSdSwitch = 6,                  /*!< adtc     [31] mode       R1 */
                                    /*!<          [15:12] func */
                                    /*!<          group 4: current */
                                    /*!<          limit */
                                    /*!<          [11:8] func */
                                    /*!<          group 3: drive */
                                    /*!<          strength */
                                    /*!<          [7:4] func  */
                                    /*!<          group 2: command */
                                    /*!<          system */
                                    /*!<          [3:0] func */
                                    /*!<          group 1: access */
                                    /*!<          mode */
    kSdSendIfCond = 8,              /*!< bcr      [11:8] supply   R7 */
                                    /*!<          voltage */
                                    /*!<          [7:0] check */
                                    /*!<          pattern */
    kSdVoltageSwitch = 11,          /*!< ac                       R1 */
    kSdSpeedClassControl = 20,      /*!< ac       [31:28] speed   R1b */
                                    /*!<          class control */
    kSdEraseWrBlkStart = 32,        /*!< ac       [31:0] data     R1 */
                                    /*!<          address */
    kSdEraseWrBlkEnd = 33,          /*!< ac       [31:0] data     R1 */
                                    /*!<          address */
} sd_cmd_t;

typedef enum _sd_acmd_t {
    kSdAppSetBusWdith = 6,          /*!< ac       [1:0] bus       R1 */
                                    /*!<          width */
    kSdAppStatus = 13,              /*!< adtc                     R1 */
    kSdAppSendNumWrBlocks = 22,     /*!< adtc                     R1 */
    kSdAppSetWrBlkEraseCount = 23,  /*!< ac       [22:0] number   R1 */
                                    /*!<          of blocks */
    kSdAppSendOpCond = 41,          /*!< bcr      [30] HCS        R3 */
                                    /*!<          [28] XPC */
                                    /*!<          [24] S18R */
                                    /*!<          [23:0] VDD */
                                    /*!<          voltage window */
    kSdAppSetClrCardDetect = 42,    /*!< ac       [0] set cd      R1 */
    kSdAppSendScr = 51,             /*!< adtc                     R1 */
} sd_acmd_t;

typedef enum _sd_buswidth_t {
    kSdBusWidth1Bit = 0,            /*!< SD data bus width 1-bit mode */
    kSdBusWidth4Bit = 2,            /*!< SD data bus width 1-bit mode */
} sd_buswidth_t;

typedef enum _sd_switch_mode_t {
    kSdSwitchCheck = 0,             /*!< SD switch mode 0: check function */
    kSdSwitchSet = 1,               /*!< SD switch mode 1: set function */
} sd_switch_mode_t;

typedef enum _sdcard_type
{
    kCardTypeUnknown = 1,           /*!< Unknown card type */
    kCardTypeSd,                    /*!< SD card type */
    kCardTypeMmc,                   /*!< MMC card type */
    kCardTypeSdio,                  /*!< SDIO card type */
} sdcard_type_t;

typedef enum _sdcard_version
{
    kSdCardVersion_1_x,
    kSdCardVersion_2_x,
    kSdCardVersion_3_x,
} sdcard_version_t;

typedef struct SdCsd {
    uint8_t csdStructure;           /*!< CSD structure [127:126] */
    uint8_t taac;                   /*!< Data read access-time-1 [119:112] */
    uint8_t nsac;                   /*!< Data read access-time-2 in clock cycles (NSAC*100) [111:104] */
    uint8_t tranSpeed;              /*!< Maximum data transfer rate [103:96] */
    uint16_t ccc;                   /*!< Card command classes [95:84] */
    uint8_t readBlkLen;             /*!< Maximum read data block length [83:80] */
    uint16_t flags;                 /*!< Card flags */
#define SDCARD_CSD_READ_BL_PARTIAL           (1<<0)         /*!< Partial blocks for read allowed [79:79]*/
#define SDCARD_CSD_WRITE_BLK_MISALIGN        (1<<1)         /*!< Write block misalignment [78:78]*/
#define SDCARD_CSD_READ_BLK_MISALIGN         (1<<2)         /*!< Read block misalignment [77:77]*/
#define SDCARD_CSD_DSR_IMP                   (1<<3)         /*!< DSR implemented [76:76] */
#define SDCARD_CSD_ERASE_BLK_ENABLED         (1<<4)         /*!< Erase single block enabled [46:46] */
#define SDCARD_CSD_WP_GRP_ENABLED            (1<<5)         /*!< Write protect group enabled [31:31] */
#define SDCARD_CSD_WRITE_BL_PARTIAL          (1<<6)         /*!< Partial blocks for write allowed [21:21]*/
#define SDCARD_CSD_FILE_FORMAT_GROUP         (1<<7)         /*!< File format group [15:15]*/
#define SDCARD_CSD_COPY                      (1<<8)         /*!< Copy flag [14:14]*/
#define SDCARD_CSD_PERM_WRITE_PROTECT        (1<<9)         /*!< Permanent write protection [13:13]*/
#define SDCARD_CSD_TMP_WRITE_PROTECT         (1<<10)        /*!< Temporary write protection [12:12]*/
    uint32_t cSize;             /*!< Device size [73:62] */
    uint8_t vddRCurrMin;        /*!< Maximum read current @VDD min [61:59] */
    uint8_t vddRCurrMax;        /*!< Maximum read current @VDD max [58:56] */
    uint8_t vddWCurrMin;        /*!< Maximum write current @VDD min [55:53] */
    uint8_t vddWCurrMax;        /*!< Maximum write current @VDD max [52:50] */
    uint8_t cSizeMult;          /*!< Device size multiplier [49:47] */
    uint8_t sectorSize;         /*!< Erase sector size [45:39] */
    uint8_t wpGrpSize;          /*!< Write protect group size [38:32] */
    uint8_t r2wFactor;          /*!< Write speed factor [28:26] */
    uint8_t writeBlkLen;        /*!< Maximum write data block length [25:22] */
    uint8_t fileFormat;         /*!< File format [11:10] */
    uint8_t reserved;
} sdcard_csd_t;

typedef struct SdScr {
    uint8_t scrStructure;       /*!< SCR Structure [63:60] */
    uint8_t sdSpec;             /*!< SD memory card spec. version [59:56] */
    uint16_t flags;             /*!< SCR flags */
#define SDCARD_SCR_DATA_STAT_AFTER_ERASE     (1<<0)         /*!< Data status after erases [55:55]*/
#define SDCARD_SCR_SD_SPEC3                  (1<<1)         /*!< Spec. version 3.00 or higher [47:47]*/
    uint8_t sdSecurity;         /*!< CPRM security support [54:52] */
    uint8_t sdBusWidths;        /*!< Data bus widths supported [51:48] */
    uint8_t exSecurity;         /*!< Extended security support [46:43] */
    uint8_t cmdSupport;         /*!< Command support bits [33:32] */
    uint32_t reservedForMan;    /*!< reserved for manufacturer usage [31:0] */
} sdcard_scr_t;

typedef struct SdCid {
    uint8_t mid;                    /*!< Manufacturer ID [127:120] */
    uint16_t oid;                   /*!< OEM/Application ID [119:104] */
    uint8_t pnm[6];                 /*!< Product name [103:64] */
    uint8_t prv;                 /*!< Product revision [63:56] */
    uint32_t psn;                   /*!< Product serial number [55:24] */
    uint16_t mdt;                 /*!< Manufacturing date [19:8] */
} sdcard_cid_t;

/*! @} */
#endif

/*************************************************************************************************
 * EOF
 ************************************************************************************************/
