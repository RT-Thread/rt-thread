/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup OSPI_B
 * @{
 **********************************************************************************************************************/

#ifndef R_OSPI_B_H
#define R_OSPI_B_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_ospi_b_cfg.h"
#include "r_spi_flash_api.h"

#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
 #include "r_transfer_api.h"
#endif

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#ifndef OSPI_B_MAX_WRITE_ENABLE_POLLING_LOOPS

/** Maximum number of status polling checks after enabling memory writes. */
 #define OSPI_B_MAX_WRITE_ENABLE_POLLING_LOOPS    (5)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** OSPI Flash chip select */
typedef enum e_ospi_b_chip_select
{
    OSPI_B_DEVICE_NUMBER_0 = 0U,       ///< Device connected to Chip-Select 0
    OSPI_B_DEVICE_NUMBER_1,            ///< Device connected to Chip-Select 1
} ospi_b_device_number_t;

/** OSPI flash number of command code bytes. */
typedef enum e_ospi_b_command_bytes
{
    OSPI_B_COMMAND_BYTES_1 = 1U,       ///< Command codes are 1 byte long.
    OSPI_B_COMMAND_BYTES_2 = 2U,       ///< Command codes are 2 bytes long.
} ospi_b_command_bytes_t;

/** OSPI frame to frame interval */
typedef enum e_ospi_b_frame_interval_clocks
{
    OSPI_B_COMMAND_INTERVAL_CLOCKS_1 = 0U, ///< 1 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_2,      ///< 2 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_3,      ///< 3 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_4,      ///< 4 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_5,      ///< 5 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_6,      ///< 6 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_7,      ///< 7 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_8,      ///< 8 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_9,      ///< 9 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_10,     ///< 10 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_11,     ///< 11 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_12,     ///< 12 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_13,     ///< 13 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_14,     ///< 14 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_15,     ///< 15 interval clocks
    OSPI_B_COMMAND_INTERVAL_CLOCKS_16,     ///< 16 interval clocks
} ospi_b_command_interval_clocks_t;

/** OSPI chip select de-assertion duration */
typedef enum e_ospi_b_cs_pullup_clocks
{
    OSPI_B_COMMAND_CS_PULLUP_CLOCKS_NO_EXTENSION = 0U, ///< CS asserting No extension
    OSPI_B_COMMAND_CS_PULLUP_CLOCKS_1,                 ///< CS asserting Extend 1 cycle
} ospi_b_command_cs_pullup_clocks_t;

/** OSPI chip select assertion duration */
typedef enum e_ospi_b_cs_pulldown_clocks
{
    OSPI_B_COMMAND_CS_PULLDOWN_CLOCKS_NO_EXTENSION = 0U, ///< CS negating No extension
    OSPI_B_COMMAND_CS_PULLDOWN_CLOCKS_1,                 ///< CS negating Extend 1 cycle
} ospi_b_command_cs_pulldown_clocks_t;

/** OSPI data strobe delay. */
typedef enum e_ospi_b_ds_timing_delay
{
    OSPI_B_DS_TIMING_DELAY_NONE = 0,   ///< Sample without delay.
    OSPI_B_DS_TIMING_DELAY_1    = 1,   ///< Delay sampling by 1 clock cell.
    OSPI_B_DS_TIMING_DELAY_2    = 2,   ///< Delay sampling by 2 clock cells.
    OSPI_B_DS_TIMING_DELAY_3    = 3,   ///< Delay sampling by 3 clock cells.
    OSPI_B_DS_TIMING_DELAY_4    = 4,   ///< Delay sampling by 4 clock cells.
    OSPI_B_DS_TIMING_DELAY_5    = 5,   ///< Delay sampling by 5 clock cells.
    OSPI_B_DS_TIMING_DELAY_6    = 6,   ///< Delay sampling by 6 clock cells.
    OSPI_B_DS_TIMING_DELAY_7    = 7,   ///< Delay sampling by 7 clock cells.
    OSPI_B_DS_TIMING_DELAY_8    = 8,   ///< Delay sampling by 8 clock cells.
    OSPI_B_DS_TIMING_DELAY_9    = 9,   ///< Delay sampling by 9 clock cells.
    OSPI_B_DS_TIMING_DELAY_10   = 10,  ///< Delay sampling by 10 clock cells.
    OSPI_B_DS_TIMING_DELAY_11   = 11,  ///< Delay sampling by 11 clock cells.
    OSPI_B_DS_TIMING_DELAY_12   = 12,  ///< Delay sampling by 12 clock cells.
    OSPI_B_DS_TIMING_DELAY_13   = 13,  ///< Delay sampling by 13 clock cells.
    OSPI_B_DS_TIMING_DELAY_14   = 14,  ///< Delay sampling by 14 clock cells.
    OSPI_B_DS_TIMING_DELAY_15   = 15,  ///< Delay sampling by 15 clock cells.
    OSPI_B_DS_TIMING_DELAY_16   = 16,  ///< Delay sampling by 16 clock cells.
    OSPI_B_DS_TIMING_DELAY_17   = 17,  ///< Delay sampling by 17 clock cells.
    OSPI_B_DS_TIMING_DELAY_18   = 18,  ///< Delay sampling by 18 clock cells.
    OSPI_B_DS_TIMING_DELAY_19   = 19,  ///< Delay sampling by 19 clock cells.
    OSPI_B_DS_TIMING_DELAY_20   = 20,  ///< Delay sampling by 20 clock cells.
    OSPI_B_DS_TIMING_DELAY_21   = 21,  ///< Delay sampling by 21 clock cells.
    OSPI_B_DS_TIMING_DELAY_22   = 22,  ///< Delay sampling by 22 clock cells.
    OSPI_B_DS_TIMING_DELAY_23   = 23,  ///< Delay sampling by 23 clock cells.
    OSPI_B_DS_TIMING_DELAY_24   = 24,  ///< Delay sampling by 24 clock cells.
    OSPI_B_DS_TIMING_DELAY_25   = 25,  ///< Delay sampling by 25 clock cells.
    OSPI_B_DS_TIMING_DELAY_26   = 26,  ///< Delay sampling by 26 clock cells.
    OSPI_B_DS_TIMING_DELAY_27   = 27,  ///< Delay sampling by 27 clock cells.
    OSPI_B_DS_TIMING_DELAY_28   = 28,  ///< Delay sampling by 28 clock cells.
    OSPI_B_DS_TIMING_DELAY_29   = 29,  ///< Delay sampling by 29 clock cells.
    OSPI_B_DS_TIMING_DELAY_30   = 30,  ///< Delay sampling by 30 clock cells.
    OSPI_B_DS_TIMING_DELAY_31   = 31,  ///< Delay sampling by 31 clock cells.
} ospi_b_ds_timing_delay_t;

/** OSPI SDR signal drive timing. */
typedef enum e_ospi_b_sdr_drive_timing
{
    OSPI_B_SDR_DRIVE_TIMING_BEFORE_CK = 0, ///< SDR is asserted 1/2 cycle before the rising-edge of CK.
    OSPI_B_SDR_DRIVE_TIMING_AT_CK     = 1, ///< SDR is asserted at the rising-edge of CK.
} ospi_b_sdr_drive_timing_t;

/** Clock edge useed to sample data in SDR mode. */
typedef enum e_ospi_b_ck_edge
{
    OSPI_B_CK_EDGE_FALLING = 0,        ///< Falling-edge of CK signal.
    OSPI_B_CK_EDGE_RISING  = 1,        ///< Rising-edge of CK signal.
} ospi_b_ck_edge_t;

/** SDR sampling window delay. */
typedef enum e_ospi_b_sdr_sampling_delay
{
    OSPI_B_SDR_SAMPLING_DELAY_NONE = 0, ///< No sampling delay.
    OSPI_B_SDR_SAMPLING_DELAY_1    = 1, ///< Delay sampling by 1 cycle.
    OSPI_B_SDR_SAMPLING_DELAY_2    = 2, ///< Delay sampling by 2 cycles.
    OSPI_B_SDR_SAMPLING_DELAY_3    = 3, ///< Delay sampling by 3 cycles.
    OSPI_B_SDR_SAMPLING_DELAY_4    = 4, ///< Delay sampling by 4 cycles.
    OSPI_B_SDR_SAMPLING_DELAY_5    = 5, ///< Delay sampling by 5 cycles.
    OSPI_B_SDR_SAMPLING_DELAY_6    = 6, ///< Delay sampling by 6 cycles.
    OSPI_B_SDR_SAMPLING_DELAY_7    = 7, ///< Delay sampling by 7 cycles.
} ospi_b_sdr_sampling_delay_t;

/** DDR sampling window extension. */
typedef enum e_ospi_b_ddr_sampling_extension
{
    OSPI_B_DDR_SAMPLING_EXTENSION_NONE = 0, ///< No sampling extension.
    OSPI_B_DDR_SAMPLING_EXTENSION_1    = 1, ///< Sampling extended by 1 cycle.
    OSPI_B_DDR_SAMPLING_EXTENSION_2    = 2, ///< Sampling extended by 2 cycles.
    OSPI_B_DDR_SAMPLING_EXTENSION_3    = 3, ///< Sampling extended by 3 cycles.
    OSPI_B_DDR_SAMPLING_EXTENSION_4    = 4, ///< Sampling extended by 4 cycles.
    OSPI_B_DDR_SAMPLING_EXTENSION_5    = 5, ///< Sampling extended by 5 cycles.
    OSPI_B_DDR_SAMPLING_EXTENSION_6    = 6, ///< Sampling extended by 6 cycles.
    OSPI_B_DDR_SAMPLING_EXTENSION_7    = 7, ///< Sampling extended by 7 cycles.
} ospi_b_ddr_sampling_extension_t;

/** Format of data frames used for communicating with the target device. */
typedef enum e_ospi_b_frame_format
{
    OSPI_B_FRAME_FORMAT_STANDARD                = 0x0, ///< Standard frame with command, address, and data phases.
    OSPI_B_FRAME_FORMAT_XSPI_PROFILE_1          = 0x1, ///< JEDEC XSPI 8D-8D-8D Profile 1.0 frame.
    OSPI_B_FRAME_FORMAT_XSPI_PROFILE_2          = 0x2, ///< JEDEC XSPI 8D-8D-8D Profile 2.0 frame.
    OSPI_B_FRAME_FORMAT_XSPI_PROFILE_2_EXTENDED = 0x3, ///< JEDEC XSPI 8D-8D-8D Profile 2.0 extended 6-byte command-address frame, used with HyperRAM.
} ospi_b_frame_format_t;

/** Variable or fixed latency selection for flash devices which can notify the host of requiring additional time. */
typedef enum e_ospi_b_latency_mode
{
    OSPI_B_LATENCY_MODE_FIXED = 0,     ///< Latency is fixed to the number of dummy cycles for the command.
    OSPI_B_LATENCY_MODE_VARIABLE,      ///< The flash target signifies additional latency (2x dummy cycles) by asserting the DQS line during the address phase.
} ospi_b_latency_mode_t;

/** Prefetch function settings */
typedef enum e_ospi_b_prefetch_function
{
    OSPI_B_PREFETCH_FUNCTION_DISABLE = 0x00, ///< Prefetch function disable
    OSPI_B_PREFETCH_FUNCTION_ENABLE  = 0x01, ///< Prefetch function enable
} ospi_b_prefetch_function_t;

/** Combination function settings */
typedef enum e_ospi_b_combination_function
{
    OSPI_B_COMBINATION_FUNCTION_DISABLE = 0x00,  ///< Combination function disable
    OSPI_B_COMBINATION_FUNCTION_4BYTE   = 0x01,  ///< Combine up to 4 bytes
    OSPI_B_COMBINATION_FUNCTION_8BYTE   = 0x03,  ///< Combine up to 8 bytes
    OSPI_B_COMBINATION_FUNCTION_12BYTE  = 0x05,  ///< Combine up to 12 bytes
    OSPI_B_COMBINATION_FUNCTION_16BYTE  = 0x07,  ///< Combine up to 16 bytes
    OSPI_B_COMBINATION_FUNCTION_20BYTE  = 0x09,  ///< Combine up to 20 bytes
    OSPI_B_COMBINATION_FUNCTION_24BYTE  = 0x0B,  ///< Combine up to 24 bytes
    OSPI_B_COMBINATION_FUNCTION_28BYTE  = 0x0D,  ///< Combine up to 28 bytes
    OSPI_B_COMBINATION_FUNCTION_32BYTE  = 0x0F,  ///< Combine up to 32 bytes
    OSPI_B_COMBINATION_FUNCTION_36BYTE  = 0x11,  ///< Combine up to 36 bytes
    OSPI_B_COMBINATION_FUNCTION_40BYTE  = 0x13,  ///< Combine up to 40 bytes
    OSPI_B_COMBINATION_FUNCTION_44BYTE  = 0x15,  ///< Combine up to 44 bytes
    OSPI_B_COMBINATION_FUNCTION_48BYTE  = 0x17,  ///< Combine up to 48 bytes
    OSPI_B_COMBINATION_FUNCTION_52BYTE  = 0x19,  ///< Combine up to 52 bytes
    OSPI_B_COMBINATION_FUNCTION_56BYTE  = 0x1B,  ///< Combine up to 56 bytes
    OSPI_B_COMBINATION_FUNCTION_60BYTE  = 0x1D,  ///< Combine up to 60 bytes
    OSPI_B_COMBINATION_FUNCTION_64BYTE  = 0x1F,  ///< Combine up to 64 bytes
    OSPI_B_COMBINATION_FUNCTION_2BYTE   = 0x1FF, ///< Combine up to 2 bytes
} ospi_b_combination_function_t;

/** Simple array length table structure. */
typedef struct st_ospi_b_table
{
    void  * p_table;                   ///< Pointer to the table array.
    uint8_t length;                    ///< Number of entries in the table.
} ospi_b_table_t;

/** Fixed timing configuration for bus signals. */
typedef struct st_ospi_b_timing_setting
{
    ospi_b_command_interval_clocks_t    command_to_command_interval; ///< Interval between 2 consecutive commands
    ospi_b_command_cs_pullup_clocks_t   cs_pullup_lag;               ///< Duration to de-assert CS line after the last command
    ospi_b_command_cs_pulldown_clocks_t cs_pulldown_lead;            ///< Duration to assert CS line before the first command
    ospi_b_sdr_drive_timing_t           sdr_drive_timing;            ///< Data signal timing relative to the rising-edge of the CK signal.
    ospi_b_ck_edge_t                sdr_sampling_edge;               ///< Selects the clock edge to sample the data signal.
    ospi_b_sdr_sampling_delay_t     sdr_sampling_delay;              ///< Number of cycles to delay before sampling the data signal.
    ospi_b_ddr_sampling_extension_t ddr_sampling_extension;          ///< Number of cycles to extending the data sampling window in DDR mode.
} ospi_b_timing_setting_t;

/** Command set used for a protocol mode. */
typedef struct st_ospi_b_xspi_command_set
{
    spi_flash_protocol_t      protocol;             ///< Protocol mode associated with this command set.
    ospi_b_frame_format_t     frame_format;         ///< Frame format to use for this command set.
    ospi_b_latency_mode_t     latency_mode;         ///< Configurable or variable latency, only valid for OSPI_B_FRAME_FORMAT_XSPI_PROFILE_2 and OSPI_B_FRAME_FORMAT_XSPI_PROFILE_2_EXTENDED.
    ospi_b_command_bytes_t    command_bytes;        ///< Number of command bytes for each command code.
    spi_flash_address_bytes_t address_bytes;        ///< Number of bytes used during the address phase.

    uint16_t read_command;                          ///< Read command.
    uint16_t program_command;                       ///< Memory program/write command.
    uint16_t write_enable_command;                  ///< Command to enable write or erase, set to 0x00 to ignore.
    uint16_t status_command;                        ///< Command to read the write status, set to 0x00 to ignore.
    uint16_t row_load_command;                      ///< Load a page into the device's internal buffer, set to 0x00 to ignore.
    uint16_t row_store_command;                     ///< Stores the device's internal buffer to the memory page, set to 0x00 to ignore.

    uint8_t read_dummy_cycles;                      ///< Dummy cycles to be inserted for read commands.
    uint8_t program_dummy_cycles;                   ///< Dummy cycles to be inserted for page program commands.
    uint8_t status_dummy_cycles;                    ///< Dummy cycles to be inserted for status read commands.
    uint8_t row_load_dummy_cycles;                  ///< Dummy cycles to be inserted for the page load command.
    uint8_t row_store_dummy_cycles;                 ///< Dummy cycles to be inserted for the page store command.

    uint8_t address_msb_mask;                       ///< Mask of bits to zero when using memory-mapped operations; only applies to the most-significant byte.

    bool     status_needs_address;                  ///< Indicates that reading the status register requires an address stage.
    uint32_t status_address;                        ///< Address to use for reading the status register with "busy" and "write-enable" flags.
    spi_flash_address_bytes_t status_address_bytes; ///< Number of bytes used for status register addressing.

    ospi_b_table_t const * p_erase_commands;        ///< List of all erase commands and associated sizes
} ospi_b_xspi_command_set_t;

/** OSPI DOTF AES Key Lengths. */
typedef enum e_ospi_b_dotf_aes_key_length_words
{
    OSPI_B_DOTF_AES_KEY_LENGTH_WORDS_128 = 16U,
    OSPI_B_DOTF_AES_KEY_LENGTH_WORDS_192 = 24U,
    OSPI_B_DOTF_AES_KEY_LENGTH_WORDS_256 = 32U
} ospi_b_dotf_aes_key_length_words_t;

/** PSPI DOTF AES Type. */
typedef enum e_ospi_b_dotf_aes_key_type
{
    OSPI_B_DOTF_AES_KEY_TYPE_128 = 0U,
    OSPI_B_DOTF_AES_KEY_TYPE_192 = 1U,
    OSPI_B_DOTF_AES_KEY_TYPE_256 = 2U
} ospi_b_dotf_aes_key_type_t;

/** OSPI DOTF key Type. */
typedef enum e_ospi_b_dotf_key_format
{
    OSPI_B_DOTF_KEY_FORMAT_PLAINTEXT = 0U,
    OSPI_B_DOTF_KEY_FORMAT_WRAPPED   = 1U,
} ospi_b_dotf_key_format_t;

/** This structure is used to hold all the DOTF related configuration. */
typedef struct st_ospi_b_dotf_cfg
{
    ospi_b_dotf_aes_key_type_t key_type;
    ospi_b_dotf_key_format_t   format;
    uint32_t                 * p_start_addr;
    uint32_t                 * p_end_addr;
    uint32_t                 * p_key;
    uint32_t                 * p_iv;
} ospi_b_dotf_cfg_t;

/** OSPI_B Extended configuration. */
typedef struct st_ospi_b_extended_cfg
{
    uint8_t                         ospi_b_unit;                             ///< The OSPI_B unit corresponding to the selected channel.
    ospi_b_device_number_t          channel;                                 ///< Device number to be used for memory device.
    ospi_b_timing_setting_t const * p_timing_settings;                       ///< Fixed protocol timing settings.
    ospi_b_table_t const          * p_xspi_command_set;                      ///< Additional protocol command sets; if additional protocol commands set are not used set this to NULL.
    ospi_b_ds_timing_delay_t        data_latch_delay_clocks;                 ///< Delay after assertion of the DS signal where data should be latched.
    uint8_t                       * p_autocalibration_preamble_pattern_addr; ///< OctaFlash memory address holding the preamble pattern
#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
    transfer_instance_t const * p_lower_lvl_transfer;                        ///< DMA Transfer instance used for data transmission
#endif
#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
    ospi_b_dotf_cfg_t * p_dotf_cfg;                                          ///< DOTF Configuration
#endif
#if OSPI_B_CFG_ROW_ADDRESSING_SUPPORT_ENABLE
    spi_flash_address_bytes_t row_index_bytes;                               ///< Number of bytes used to index the memory rows.
#endif
} ospi_b_extended_cfg_t;

/** Instance control block. DO NOT INITIALIZE.  Initialization occurs when @ref spi_flash_api_t::open is called */
typedef struct st_ospi_b_instance_ctrl
{
    spi_flash_cfg_t const           * p_cfg;        ///< Pointer to initial configuration.
    uint32_t                          open;         ///< Whether or not driver is open.
    spi_flash_protocol_t              spi_protocol; ///< Current OSPI protocol selected.
    ospi_b_device_number_t            channel;      ///< Device number to be used for memory device.
    uint8_t                           ospi_b_unit;  ///< OSPI_B instance number.
    ospi_b_xspi_command_set_t const * p_cmd_set;    ///< Command set for the active protocol mode.
    R_XSPI0_Type                    * p_reg;        ///< Address for the OSPI peripheral associated with this channel.
} ospi_b_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const spi_flash_api_t g_ospi_b_on_spi_flash;

/** @endcond */

fsp_err_t R_OSPI_B_Open(spi_flash_ctrl_t * const p_ctrl, spi_flash_cfg_t const * const p_cfg);
fsp_err_t R_OSPI_B_Close(spi_flash_ctrl_t * const p_ctrl);
fsp_err_t R_OSPI_B_DirectWrite(spi_flash_ctrl_t * const p_ctrl,
                               uint8_t const * const    p_src,
                               uint32_t const           bytes,
                               bool const               read_after_write);
fsp_err_t R_OSPI_B_DirectRead(spi_flash_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const bytes);
fsp_err_t R_OSPI_B_DirectTransfer(spi_flash_ctrl_t * const            p_ctrl,
                                  spi_flash_direct_transfer_t * const p_transfer,
                                  spi_flash_direct_transfer_dir_t     direction);
fsp_err_t R_OSPI_B_SpiProtocolSet(spi_flash_ctrl_t * const p_ctrl, spi_flash_protocol_t spi_protocol);
fsp_err_t R_OSPI_B_XipEnter(spi_flash_ctrl_t * const p_ctrl);
fsp_err_t R_OSPI_B_XipExit(spi_flash_ctrl_t * const p_ctrl);
fsp_err_t R_OSPI_B_Write(spi_flash_ctrl_t * const p_ctrl,
                         uint8_t const * const    p_src,
                         uint8_t * const          p_dest,
                         uint32_t                 byte_count);
fsp_err_t R_OSPI_B_Erase(spi_flash_ctrl_t * const p_ctrl, uint8_t * const p_device_address, uint32_t byte_count);
fsp_err_t R_OSPI_B_StatusGet(spi_flash_ctrl_t * const p_ctrl, spi_flash_status_t * const p_status);
fsp_err_t R_OSPI_B_BankSet(spi_flash_ctrl_t * const _ctrl, uint32_t bank);
fsp_err_t R_OSPI_B_AutoCalibrate(spi_flash_ctrl_t * const p_ctrl);

fsp_err_t R_OSPI_B_DOTF_Configure(spi_flash_ctrl_t * const p_ctrl, ospi_b_dotf_cfg_t * const p_dotf_cfg);

fsp_err_t R_OSPI_B_RowLoad(spi_flash_ctrl_t * const p_ctrl, uint32_t row_index);
fsp_err_t R_OSPI_B_RowStore(spi_flash_ctrl_t * const p_ctrl, uint32_t row_index);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup OSPI_B)
 **********************************************************************************************************************/
