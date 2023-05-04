/*
 * Copyright 2017-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ROMAPI_H_
#define _FSL_ROMAPI_H_

#include "fsl_common.h"

/*!
 * @addtogroup romapi
 * @{
 */

/*! @brief ROM API version 1.1.1. */
#define FSL_ROM_ROMAPI_VERSION (MAKE_VERSION(1U, 1U, 1U))
/*! @brief ROM FLEXSPI NOR driver version 1.7.0. */
#define FSL_ROM_FLEXSPINOR_DRIVER_VERSION (MAKE_VERSION(1U, 7U, 0U))

/*!
 * @name Common ROMAPI features info defines
 * @{
 */
/*! @brief ROM has FLEXSPI NOR API. */
#define FSL_ROM_HAS_FLEXSPINOR_API (1)
/*! @brief ROM has run bootloader API. */
#define FSL_ROM_HAS_RUNBOOTLOADER_API (1)
/*! @brief ROM has FLEXSPI NOR get config API. */
#define FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_GET_CONFIG (1)
/*! @brief ROM has flash init API. */
#define FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_FLASH_INIT (1)
/*! @brief ROM has erase API. */
#define FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE (1)
/*! @brief ROM has erase sector API. */
#define FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_SECTOR (1)
/*! @brief ROM has erase block API. */
#define FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_BLOCK (1)
/*! @brief ROM has erase all API. */
#define FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_ALL (1)
/*! @brief ROM has read API. */
#define FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_READ (1)
/*! @brief ROM has update lut API. */
#define FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_UPDATE_LUT (1)
/*! @brief ROM has FLEXSPI command API. */
#define FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_CMD_XFER (1)

/*@}*/

#define kROM_StatusGroup_FLEXSPINOR 201U /*!< ROM FLEXSPI NOR status group number.*/

#define FSL_ROM_FLEXSPI_LUT_SEQ(cmd0, pad0, op0, cmd1, pad1, op1)                                                      \
    (FLEXSPI_LUT_OPERAND0(op0) | FLEXSPI_LUT_NUM_PADS0(pad0) | FLEXSPI_LUT_OPCODE0(cmd0) | FLEXSPI_LUT_OPERAND1(op1) | \
     FLEXSPI_LUT_NUM_PADS1(pad1) | FLEXSPI_LUT_OPCODE1(cmd1))

/*! @brief Generate bit mask */
#define FSL_ROM_FLEXSPI_BITMASK(bit_offset) (1U << (bit_offset))

/*! @brief FLEXSPI memory config block related definitions */
#define FLEXSPI_CFG_BLK_TAG     (0x42464346UL) /*!< ascii "FCFB" Big Endian */
#define FLEXSPI_CFG_BLK_VERSION (0x56010400UL) /*!< V1.4.0 */

#define CMD_SDR        0x01U
#define CMD_DDR        0x21U
#define RADDR_SDR      0x02U
#define RADDR_DDR      0x22U
#define CADDR_SDR      0x03U
#define CADDR_DDR      0x23U
#define MODE1_SDR      0x04U
#define MODE1_DDR      0x24U
#define MODE2_SDR      0x05U
#define MODE2_DDR      0x25U
#define MODE4_SDR      0x06U
#define MODE4_DDR      0x26U
#define MODE8_SDR      0x07U
#define MODE8_DDR      0x27U
#define WRITE_SDR      0x08U
#define WRITE_DDR      0x28U
#define READ_SDR       0x09U
#define READ_DDR       0x29U
#define LEARN_SDR      0x0AU
#define LEARN_DDR      0x2AU
#define DATSZ_SDR      0x0BU
#define DATSZ_DDR      0x2BU
#define DUMMY_SDR      0x0CU
#define DUMMY_DDR      0x2CU
#define DUMMY_RWDS_SDR 0x0DU
#define DUMMY_RWDS_DDR 0x2DU
#define JMP_ON_CS      0x1FU
#define STOP           0U

#define FLEXSPI_1PAD 0U
#define FLEXSPI_2PAD 1U
#define FLEXSPI_4PAD 2U
#define FLEXSPI_8PAD 3U

/*!
 * NOR LUT sequence index used for default LUT assignment.
 *
 * @note It will take effect if the lut sequences are not customized.
 */
#define NOR_CMD_LUT_SEQ_IDX_READ       0U /*!< READ LUT sequence id in lookupTable stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS 1U /*!< Read Status LUT sequence id in lookupTable stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_READSTATUS_XPI \
    2U /*!< Read status DPI/QPI/OPI sequence id in lookupTable stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE 3U /*!< Write Enable sequence id in lookupTable stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_WRITEENABLE_XPI \
    4U /*!< Write Enable DPI/QPI/OPI sequence id in lookupTable stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_ERASESECTOR 5U /*!< Erase Sector sequence id in lookupTable stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_READID      7U
#define NOR_CMD_LUT_SEQ_IDX_ERASEBLOCK  8U  /*!< Erase Block sequence id in lookupTable stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM 9U  /*!< Program sequence id in lookupTable stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_CHIPERASE   11U /*!< Chip Erase sequence in lookupTable id stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_READ_SFDP   13U /*!< Read SFDP sequence in lookupTable id stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_RESTORE_NOCMD \
    14U /*!< Restore 0-4-4/0-8-8 mode sequence id in lookupTable stored in config block */
#define NOR_CMD_LUT_SEQ_IDX_EXIT_NOCMD \
    15U /*!< Exit 0-4-4/0-8-8 mode sequence id in lookupTable stored in config block */

/*!
 * @name Configuration Option
 * @{
 */
/*! @brief Serial NOR Configuration Option. */
typedef struct _serial_nor_config_option
{
    union
    {
        struct
        {
            uint32_t max_freq : 4;          /*!< Maximum supported Frequency */
            uint32_t misc_mode : 4;         /*!< miscellaneous mode */
            uint32_t quad_mode_setting : 4; /*!< Quad mode setting */
            uint32_t cmd_pads : 4;          /*!< Command pads */
            uint32_t query_pads : 4;        /*!< SFDP read pads */
            uint32_t device_type : 4;       /*!< Device type */
            uint32_t option_size : 4;       /*!< Option size, in terms of uint32_t, size = (option_size + 1) * 4 */
            uint32_t tag : 4;               /*!< Tag, must be 0x0E */
        } B;
        uint32_t U;
    } option0;

    union
    {
        struct
        {
            uint32_t dummy_cycles : 8;     /*!< Dummy cycles before read */
            uint32_t status_override : 8;  /*!< Override status register value during device mode configuration */
            uint32_t pinmux_group : 4;     /*!< The pinmux group selection */
            uint32_t dqs_pinmux_group : 4; /*!< The DQS Pinmux Group Selection */
            uint32_t drive_strength : 4;   /*!< The Drive Strength of FlexSPI Pads */
            uint32_t flash_connection : 4; /*!< Flash connection option: 0 - Single Flash connected to port A, 1 -
                                                Parallel mode, 2 - Single Flash connected to Port B */
        } B;
        uint32_t U;
    } option1;

} serial_nor_config_option_t;

/*@}*/

/*!
 * @name Support for init FLEXSPI NOR configuration
 * @{
 */
/*! @brief Flash Pad Definitions */
enum
{
    kSerialFlash_1Pad  = 1U, /*!< 1-wire communication */
    kSerialFlash_2Pads = 2U, /*!< 2-wire communication */
    kSerialFlash_4Pads = 4U, /*!< 4-wire communication */
    kSerialFlash_8Pads = 8U, /*!< 8-wire communication */
};

/*! @brief FLEXSPI clock configuration type */
enum
{
    kFLEXSPIClk_SDR, /*!< Clock configure for SDR mode */
    kFLEXSPIClk_DDR, /*!< Clock configure for DDR mode */
};

/*! @brief FLEXSPI Read Sample Clock Source definition */
enum _flexspi_read_sample_clk
{
    kFLEXSPIReadSampleClk_LoopbackInternally = 0U, /*!< FLEXSPI Read Sample Clock Source from the Internal loopback */
    kFLEXSPIReadSampleClk_LoopbackFromDqsPad = 1U, /*!< FLEXSPI Read Sample Clock Source from the Dqs Pad loopback */
    kFLEXSPIReadSampleClk_LoopbackFromSckPad = 2U, /*!< FLEXSPI Read Sample Clock Source from the Sck Pad loopback */
    kFLEXSPIReadSampleClk_ExternalInputFromDqsPad = 3U, /*!< FLEXSPI Read Sample Clock Source from the External Input
                                                             by the Dqs Pad */
};

/*! @brief Flash Type Definition */
enum
{
    kFLEXSPIDeviceType_SerialNOR = 1U, /*!< Flash device is Serial NOR */
};

/*! @brief Flash Configuration Command Type */
enum
{
    kDeviceConfigCmdType_Generic,    /*!< Generic command, for example: configure dummy cycles, drive strength, etc. */
    kDeviceConfigCmdType_QuadEnable, /*!< Quad Enable command */
    kDeviceConfigCmdType_Spi2Xpi,    /*!< Switch from SPI to DPI/QPI/OPI mode */
    kDeviceConfigCmdType_Xpi2Spi,    /*!< Switch from DPI/QPI/OPI to SPI mode */
    kDeviceConfigCmdType_Spi2NoCmd,  /*!< Switch to 0-4-4/0-8-8 mode */
    kDeviceConfigCmdType_Reset,      /*!< Reset device command */
};

/*! @brief Definitions for FLEXSPI Serial Clock Frequency */
enum _flexspi_serial_clk_freq
{
    kFLEXSPISerialClk_NoChange = 0U, /*!< FlexSPI serial clock no changed */
    kFLEXSPISerialClk_30MHz    = 1U, /*!< FlexSPI serial clock 30MHz */
    kFLEXSPISerialClk_50MHz    = 2U, /*!< FlexSPI serial clock 50MHz */
    kFLEXSPISerialClk_60MHz    = 3U, /*!< FlexSPI serial clock 60MHz */
    kFLEXSPISerialClk_75MHz    = 4U, /*!< FlexSPI serial clock 75MHz */
    kFLEXSPISerialClk_80MHz    = 5U, /*!< FlexSPI serial clock 80MHz */
    kFLEXSPISerialClk_100MHz   = 6U, /*!< FlexSPI serial clock 100MHz */
    kFLEXSPISerialClk_133MHz   = 7U, /*!< FlexSPI serial clock 133MHz */
    kFLEXSPISerialClk_166MHz   = 8U, /*!< FlexSPI serial clock 166MHz */
};

/*! @brief Misc feature bit definitions */
enum
{
    kFLEXSPIMiscOffset_DiffClkEnable            = 0U, /*!< Bit for Differential clock enable */
    kFLEXSPIMiscOffset_Ck2Enable                = 1U, /*!< Bit for CK2 enable */
    kFLEXSPIMiscOffset_ParallelEnable           = 2U, /*!< Bit for Parallel mode enable */
    kFLEXSPIMiscOffset_WordAddressableEnable    = 3U, /*!< Bit for Word Addressable enable */
    kFLEXSPIMiscOffset_SafeConfigFreqEnable     = 4U, /*!< Bit for Safe Configuration Frequency enable */
    kFLEXSPIMiscOffset_PadSettingOverrideEnable = 5U, /*!< Bit for Pad setting override enable */
    kFLEXSPIMiscOffset_DdrModeEnable            = 6U, /*!< Bit for DDR clock configuration indication. */
    kFLEXSPIMiscOffset_UseValidTimeForAllFreq   = 7U, /*!< Bit for DLLCR settings under all modes */
};

/*@}*/

/*! @brief Manufacturer ID */
enum
{
    kSerialFlash_ISSI_ManufacturerID    = 0x9DU, /*!< Manufacturer ID of the ISSI serial flash */
    kSerialFlash_Adesto_ManufacturerID  = 0x1F,  /*!< Manufacturer ID of the Adesto Technologies serial flash*/
    kSerialFlash_Winbond_ManufacturerID = 0xEFU, /*!< Manufacturer ID of the Winbond serial flash */
    kSerialFlash_Cypress_ManufacturerID = 0x01U, /*!< Manufacturer ID for Cypress */
};

/*! @brief ROM FLEXSPI NOR flash status */
enum _flexspi_nor_status
{
    kStatus_ROM_FLEXSPI_SequenceExecutionTimeout =
        MAKE_STATUS(kStatusGroup_FLEXSPI, 0), /*!< Status for Sequence Execution timeout */
    kStatus_ROM_FLEXSPI_InvalidSequence = MAKE_STATUS(kStatusGroup_FLEXSPI, 1), /*!< Status for Invalid Sequence */
    kStatus_ROM_FLEXSPI_DeviceTimeout   = MAKE_STATUS(kStatusGroup_FLEXSPI, 2), /*!< Status for Device timeout */
    kStatus_ROM_FLEXSPINOR_SFDP_NotFound =
        MAKE_STATUS(kROM_StatusGroup_FLEXSPINOR, 7), /*!< Status for SFDP read failure */
    kStatus_ROM_FLEXSPINOR_Flash_NotFound =
        MAKE_STATUS(kROM_StatusGroup_FLEXSPINOR, 9), /*!< Status for Flash detection failure */
    kStatus_FLEXSPINOR_DTRRead_DummyProbeFailed =
        MAKE_STATUS(kROM_StatusGroup_FLEXSPINOR, 10), /*!< Status for DDR Read dummy probe failure */
};

/*!
 * @name FLEXSPI NOR Configuration
 * @{
 */

/*! @brief FLEXSPI LUT Sequence structure */
typedef struct _flexspi_lut_seq
{
    uint8_t seqNum; /*!< Sequence Number, valid number: 1-16 */
    uint8_t seqId;  /*!< Sequence Index, valid number: 0-15 */
    uint16_t reserved;
} flexspi_lut_seq_t;

/*! @brief FLEXSPI DLL time */
typedef struct
{
    uint8_t time_100ps;  /*!< Data valid time, in terms of 100ps */
    uint8_t delay_cells; /*!< Data valid time, in terms of delay cells */
} flexspi_dll_time_t;

/*! @brief FLEXSPI Memory Configuration Block */
typedef struct _flexspi_mem_config
{
    uint32_t tag;       /*!< [0x000-0x003] Tag, fixed value 0x42464346UL */
    uint32_t version;   /*!< [0x004-0x007] Version,[31:24] -'V', [23:16] - Major, [15:8] - Minor, [7:0] - bugfix */
    uint32_t reserved0; /*!< [0x008-0x00b] Reserved for future use */
    uint8_t readSampleClkSrc;    /*!< [0x00c-0x00c] Read Sample Clock Source, valid value: 0/1/3 */
    uint8_t csHoldTime;          /*!< [0x00d-0x00d] Data hold time, default value: 3 */
    uint8_t csSetupTime;         /*!< [0x00e-0x00e] Date setup time, default value: 3 */
    uint8_t columnAddressWidth;  /*!< [0x00f-0x00f] Column Address with, for HyperBus protocol, it is fixed to 3, For
                                                    Serial NAND, need to refer to datasheet */
    uint8_t deviceModeCfgEnable; /*!< [0x010-0x010] Device Mode Configure enable flag, 1 - Enable, 0 - Disable */
    uint8_t deviceModeType; /*!< [0x011-0x011] Specify the configuration command type:Quad Enable, DPI/QPI/OPI switch,
                                               Generic configuration, etc. */
    uint16_t waitTimeCfgCommands;    /*!< [0x012-0x013] Wait time for all configuration commands, unit: 100us, Used for
                                                        DPI/QPI/OPI switch or reset command */
    flexspi_lut_seq_t deviceModeSeq; /*!< [0x014-0x017] Device mode sequence info, [7:0] - LUT sequence id, [15:8] - LUt
                                                        sequence number, [31:16] Reserved */
    uint32_t deviceModeArg;          /*!< [0x018-0x01b] Argument/Parameter for device configuration */
    uint8_t configCmdEnable;         /*!< [0x01c-0x01c] Configure command Enable Flag, 1 - Enable, 0 - Disable */
    uint8_t configModeType[3];       /*!< [0x01d-0x01f] Configure Mode Type, similar as deviceModeTpe */
    flexspi_lut_seq_t
        configCmdSeqs[3]; /*!< [0x020-0x02b] Sequence info for Device Configuration command, similar as deviceModeSeq */
    uint32_t reserved1;   /*!< [0x02c-0x02f] Reserved for future use */
    uint32_t configCmdArgs[3];     /*!< [0x030-0x03b] Arguments/Parameters for device Configuration commands */
    uint32_t reserved2;            /*!< [0x03c-0x03f] Reserved for future use */
    uint32_t controllerMiscOption; /*!< [0x040-0x043] Controller Misc Options, see Misc feature bit definitions for more
                                      details */
    uint8_t deviceType;            /*!< [0x044-0x044] Device Type:  See Flash Type Definition for more details */
    uint8_t sflashPadType; /*!< [0x045-0x045] Serial Flash Pad Type: 1 - Single, 2 - Dual, 4 - Quad, 8 - Octal */
    uint8_t serialClkFreq; /*!< [0x046-0x046] Serial Flash Frequency, device specific definitions. See System Boot
                                              Chapter for more details */
    uint8_t
        lutCustomSeqEnable; /*!< [0x047-0x047] LUT customization Enable, it is required if the program/erase cannot
                                              be done using 1 LUT sequence, currently, only applicable to HyperFLASH */
    uint32_t reserved3[2];  /*!< [0x048-0x04f] Reserved for future use */
    uint32_t sflashA1Size;  /*!< [0x050-0x053] Size of Flash connected to A1 */
    uint32_t sflashA2Size;  /*!< [0x054-0x057] Size of Flash connected to A2 */
    uint32_t sflashB1Size;  /*!< [0x058-0x05b] Size of Flash connected to B1 */
    uint32_t sflashB2Size;  /*!< [0x05c-0x05f] Size of Flash connected to B2 */
    uint32_t csPadSettingOverride;       /*!< [0x060-0x063] CS pad setting override value */
    uint32_t sclkPadSettingOverride;     /*!< [0x064-0x067] SCK pad setting override value */
    uint32_t dataPadSettingOverride;     /*!< [0x068-0x06b] data pad setting override value */
    uint32_t dqsPadSettingOverride;      /*!< [0x06c-0x06f] DQS pad setting override value */
    uint32_t timeoutInMs;                /*!< [0x070-0x073] Timeout threshold for read status command */
    uint32_t commandInterval;            /*!< [0x074-0x077] CS deselect interval between two commands */
    flexspi_dll_time_t dataValidTime[2]; /*!< [0x078-0x07b] CLK edge to data valid time for PORT A and PORT B */
    uint16_t busyOffset;                 /*!< [0x07c-0x07d] Busy offset, valid value: 0-31 */
    uint16_t busyBitPolarity; /*!< [0x07e-0x07f] Busy flag polarity, 0 - busy flag is 1 when flash device is busy, 1 -
                                                 busy flag is 0 when flash device is busy */
    uint32_t lookupTable[64]; /*!< [0x080-0x17f] Lookup table holds Flash command sequences */
    flexspi_lut_seq_t lutCustomSeq[12]; /*!< [0x180-0x1af] Customizable LUT Sequences */
    uint32_t reserved4[4];              /*!< [0x1b0-0x1bf] Reserved for future use */
} flexspi_mem_config_t;

/*! @brief  Serial NOR configuration block */
typedef struct _flexspi_nor_config
{
    flexspi_mem_config_t memConfig; /*!< Common memory configuration info via FLEXSPI */
    uint32_t pageSize;              /*!< Page size of Serial NOR */
    uint32_t sectorSize;            /*!< Sector size of Serial NOR */
    uint8_t ipcmdSerialClkFreq;     /*!< Clock frequency for IP command */
    uint8_t isUniformBlockSize;     /*!< Sector/Block size is the same */
    uint8_t isDataOrderSwapped;     /*!< Data order (D0, D1, D2, D3) is swapped (D1,D0, D3, D2) */
    uint8_t reserved0[1];           /*!< Reserved for future use */
    uint8_t serialNorType;          /*!< Serial NOR Flash type: 0/1/2/3 */
    uint8_t needExitNoCmdMode;      /*!< Need to exit NoCmd mode before other IP command */
    uint8_t halfClkForNonReadCmd;   /*!< Half the Serial Clock for non-read command: true/false */
    uint8_t needRestoreNoCmdMode;   /*!< Need to Restore NoCmd mode after IP command execution */
    uint32_t blockSize;             /*!< Block size */
    uint32_t reserve2[11];          /*!< Reserved for future use */
} flexspi_nor_config_t;

/*@}*/

/*! @brief FLEXSPI Operation Context */
typedef enum _flexspi_operation
{
    kFLEXSPIOperation_Command,  /*!< FLEXSPI operation: Only command, both TX and RX buffer are ignored. */
    kFLEXSPIOperation_Config,   /*!< FLEXSPI operation: Configure device mode, the TX FIFO size is fixed in LUT. */
    kFLEXSPIOperation_Write,    /*!< FLEXSPI operation: Write, only TX buffer is effective */
    kFLEXSPIOperation_Read,     /*!< FLEXSPI operation: Read, only Rx Buffer is effective. */
} flexspi_operation_t;

#define kFLEXSPIOperation_End   kFLEXSPIOperation_Read

/*! @brief FLEXSPI Transfer Context */
typedef struct _flexspi_xfer
{
    flexspi_operation_t operation; /*!< FLEXSPI operation */
    uint32_t baseAddress;          /*!< FLEXSPI operation base address */
    uint32_t seqId;                /*!< Sequence Id */
    uint32_t seqNum;               /*!< Sequence Number */
    bool isParallelModeEnable;     /*!< Is a parallel transfer */
    uint32_t *txBuffer;            /*!< Tx buffer */
    uint32_t txSize;               /*!< Tx size in bytes */
    uint32_t *rxBuffer;            /*!< Rx buffer */
    uint32_t rxSize;               /*!< Rx size in bytes */
} flexspi_xfer_t;

/*! @brief convert the type for MISRA */
#define MISRA_CAST(to_type, to_var, from_type, from_var)      \
    do                                                        \
    {                                                         \
        union                                                 \
        {                                                     \
            to_type to_var_tmp;                               \
            from_type from_var_tmp;                           \
        } type_converter_var = {.from_var_tmp = (from_var)};  \
        (to_var)             = type_converter_var.to_var_tmp; \
    } while (false)

#ifdef __cplusplus
extern "C" {
#endif

#if defined(FSL_FEATURE_BOOT_ROM_HAS_ROMAPI) && FSL_FEATURE_BOOT_ROM_HAS_ROMAPI

/*!
 * @brief ROM API init
 *
 * Get the bootloader api entry address.
 */
void ROM_API_Init(void);

/*!
 * @name Enter Bootloader
 * @{
 */

#if defined(FSL_ROM_HAS_RUNBOOTLOADER_API) && FSL_ROM_HAS_RUNBOOTLOADER_API
/*!
 * @brief Enter Bootloader.
 *
 * @param arg A pointer to the storage for the bootloader param.
 *        refer to System Boot Chapter in device reference manual for details.
 */
void ROM_RunBootloader(void *arg);
#endif /* FSL_ROM_HAS_RUNBOOTLOADER_API */

/*@}*/

/*!
 * @name GetConfig
 * @{
 */
#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_GET_CONFIG) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_GET_CONFIG
/*!
 * @brief Get FLEXSPI NOR Configuration Block based on specified option.
 *
 * @param instance storage the instance of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 * @param option A pointer to the storage Serial NOR Configuration Option Context.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 * @retval kStatus_ROM_FLEXSPI_DeviceTimeout the device timeout
 */
status_t ROM_FLEXSPI_NorFlash_GetConfig(uint32_t instance,
                                        flexspi_nor_config_t *config,
                                        serial_nor_config_option_t *option);
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_GET_CONFIG */

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initialize Serial NOR devices via FLEXSPI
 *
 * This function checks and initializes the FLEXSPI module for the other FLEXSPI APIs.
 *
 * @param instance storage the instance of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 * @retval kStatus_ROM_FLEXSPI_DeviceTimeout the device timeout
 */
status_t ROM_FLEXSPI_NorFlash_Init(uint32_t instance, flexspi_nor_config_t *config);

/*@}*/

/*!
 * @name Programming
 * @{
 */

/*!
 * @brief Program data to Serial NOR via FLEXSPI.
 *
 * This function programs the NOR flash memory with the dest address for a given
 * flash area as determined by the dst address and the length.
 *
 * @param instance storage the instance of FLEXSPI.
 * @param config  A pointer to the storage for the driver runtime state.
 * @param dst_addr A pointer to the desired flash memory to be programmed.
 *                @note It is recommended that use page aligned access;
 *                If the dst_addr is not aligned to page, the driver automatically
 *                aligns address down with the page address.
 * @param src A pointer to the source buffer of data that is to be programmed
 *            into the NOR flash.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 * @retval kStatus_ROM_FLEXSPI_DeviceTimeout the device timeout
 */
status_t ROM_FLEXSPI_NorFlash_ProgramPage(uint32_t instance,
                                          flexspi_nor_config_t *config,
                                          uint32_t dst_addr,
                                          const uint32_t *src);

/*@}*/

/*!
 * @name Reading
 * @{
 */

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_READ) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_READ
/*!
 * @brief Read data from Serial NOR via FLEXSPI.
 *
 * This function read the NOR flash memory with the start address for a given
 * flash area as determined by the dst address and the length.
 *
 * @param instance storage the instance of FLEXSPI.
 * @param config  A pointer to the storage for the driver runtime state.
 * @param dst     A pointer to the dest buffer of data that is to be read from the NOR flash.
 *                @note It is recommended that use page aligned access;
 *                If the dstAddr is not aligned to page, the driver automatically
 *                aligns address down with the page address.
 * @param start   The start address of the desired NOR flash memory to be read.
 * @param lengthInBytes The length, given in bytes to be read.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 * @retval kStatus_ROM_FLEXSPI_DeviceTimeout the device timeout
 */
status_t ROM_FLEXSPI_NorFlash_Read(
    uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t lengthInBytes);
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_READ */

/*@}*/

/*!
 * @name Erasing
 * @{
 */

/*!
 * @brief Erase Flash Region specified by address and length
 *
 * This function erases the appropriate number of flash sectors based on the
 * desired start address and length.
 *
 * @param instance storage the index of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired NOR flash memory to be erased.
 *              @note It is recommended that use sector-aligned access nor device;
 *              If dstAddr is not aligned with the sector,the driver automatically
 *              aligns address down with the sector address.
 * @param length The length, given in bytes to be erased.
 *              @note It is recommended that use sector-aligned access nor device;
 *              If length is not aligned with the sector,the driver automatically
 *              aligns up with the sector.
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 * @retval kStatus_ROM_FLEXSPI_DeviceTimeout the device timeout
 */
status_t ROM_FLEXSPI_NorFlash_Erase(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length);

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_SECTOR) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_SECTOR
/*!
 * @brief Erase one sector specified by address
 *
 * This function erases one of NOR flash sectors based on the desired address.
 *
 * @param instance storage the index of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired NOR flash memory to be erased.
 *                @note It is recommended that use sector-aligned access nor device;
 *                If dstAddr is not aligned with the sector, the driver automatically
 *                aligns address down with the sector address.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 * @retval kStatus_ROM_FLEXSPI_DeviceTimeout the device timeout
 */
status_t ROM_FLEXSPI_NorFlash_EraseSector(uint32_t instance, flexspi_nor_config_t *config, uint32_t start);
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_SECTOR */

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_BLOCK) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_BLOCK
/*!
 * @brief Erase one block specified by address
 *
 * This function erases one block of NOR flash based on the desired address.
 *
 * @param instance storage the index of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 * @param start The start address of the desired NOR flash memory to be erased.
 *              @note It is recommended that use block-aligned access nor device;
 *              If dstAddr is not aligned with the block, the driver automatically
 *              aligns address down with the block address.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 * @retval kStatus_ROM_FLEXSPI_DeviceTimeout the device timeout
 */
status_t ROM_FLEXSPI_NorFlash_EraseBlock(uint32_t instance, flexspi_nor_config_t *config, uint32_t start);
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_BLOCK */

#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_ALL) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_ALL
/*!
 * @brief Erase all the Serial NOR devices connected on FLEXSPI.
 *
 * @param instance storage the instance of FLEXSPI.
 * @param config A pointer to the storage for the driver runtime state.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 * @retval kStatus_ROM_FLEXSPI_DeviceTimeout the device timeout
 */
status_t ROM_FLEXSPI_NorFlash_EraseAll(uint32_t instance, flexspi_nor_config_t *config);
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_ERASE_ALL */

/*@}*/

/*!
 * @name Command
 * @{
 */
#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_CMD_XFER) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_CMD_XFER
/*!
 * @brief FLEXSPI command
 *
 * This function is used to perform the command write sequence to the NOR device.
 *
 * @param instance storage the index of FLEXSPI.
 * @param xfer A pointer to the storage FLEXSPI Transfer Context.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 */
status_t ROM_FLEXSPI_NorFlash_CommandXfer(uint32_t instance, flexspi_xfer_t *xfer);
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_CMD_XFER */
/*@}*/

/*!
 * @name UpdateLut
 * @{
 */
#if defined(FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_UPDATE_LUT) && FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_UPDATE_LUT
/*!
 * @brief Configure FLEXSPI Lookup table
 *
 * @param instance storage the index of FLEXSPI.
 * @param seqIndex storage the sequence Id.
 * @param lutBase A pointer to the look-up-table for command sequences.
 * @param seqNumber storage sequence number.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 */
status_t ROM_FLEXSPI_NorFlash_UpdateLut(uint32_t instance,
                                        uint32_t seqIndex,
                                        const uint32_t *lutBase,
                                        uint32_t seqNumber);
#endif /* FSL_ROM_FLEXSPINOR_API_HAS_FEATURE_UPDATE_LUT */

/*@}*/

/*!
 * @name Device status
 * @{
 */
/*!
 * @brief Wait until device is idle.
 *
 * @param instance  Indicates the index of FLEXSPI.
 * @param config    A pointer to the storage for the driver runtime state
 * @param isParallelMode Indicates whether NOR flash is in parallel mode.
 * @param address  Indicates the operation(erase/program/read) address for serial NOR flash.
 *
 * @retval kStatus_Success Api was executed successfully.
 * @retval kStatus_InvalidArgument A invalid argument is provided.
 * @retval kStatus_ROM_FLEXSPI_SequenceExecutionTimeout Sequence Execution timeout.
 * @retval kStatus_ROM_FLEXSPI_InvalidSequence A invalid Sequence is provided.
 * @retval kStatus_ROM_FLEXSPI_DeviceTimeout Device timeout.
 */
status_t ROM_FLEXSPI_NorFlash_WaitBusy(uint32_t instance,
                                       flexspi_nor_config_t *config,
                                       bool isParallelMode,
                                       uint32_t address);
/*@}*/

/*!
 * @name ClearCache
 * @{
 */

/*!
 * @name ClearCache
 * @{
 */

/*!
 * @brief Software reset for the FLEXSPI logic.
 *
 * This function sets the software reset flags for both AHB and buffer domain and
 * resets both AHB buffer and also IP FIFOs.
 *
 * @param instance storage the index of FLEXSPI.
 */
void ROM_FLEXSPI_NorFlash_ClearCache(uint32_t instance);

/*@}*/

#endif /* FSL_FEATURE_BOOT_ROM_HAS_ROMAPI */

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif /* _FSL_ROMAPI_H_ */
