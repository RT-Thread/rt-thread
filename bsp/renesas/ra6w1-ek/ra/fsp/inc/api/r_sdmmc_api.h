/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SDMMC_API_H
#define R_SDMMC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"
#include "r_transfer_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @ingroup RENESAS_STORAGE_INTERFACES
 * @defgroup SDMMC_API SD/MMC Interface
 * @brief Interface for accessing SD, eMMC, and SDIO devices.
 *
 * @section SDMMC_API_SUMMARY Summary
 * The r_sdhi interface provides standard SD and eMMC media functionality. This interface also supports SDIO.
 *
 *
 * @{
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** SD/MMC media uses SD protocol or MMC protocol. */
typedef enum e_sdmmc_card_type
{
    SDMMC_CARD_TYPE_MMC  = 0,          ///< The media is an eMMC device.
    SDMMC_CARD_TYPE_SD   = 1,          ///< The media is an SD card.
    SDMMC_CARD_TYPE_SDIO = 2,          ///< The media is an SDIO card.
} sdmmc_card_type_t;

/** SD/MMC data bus is 1, 4 or 8 bits wide. */
typedef enum e_sdmmc_bus_width
{
    SDMMC_BUS_WIDTH_1_BIT  = 1,        ///< Data bus is 1 bit wide.
    SDMMC_BUS_WIDTH_4_BITS = 4,        ///< Data bus is 4 bits wide.
    SDMMC_BUS_WIDTH_8_BITS = 8,        ///< Data bus is 8 bits wide.
} sdmmc_bus_width_t;

/** SDIO transfer mode, configurable in SDIO read/write extended commands. */
typedef enum e_sdmmc_io_transfer_mode
{
    SDMMC_IO_MODE_TRANSFER_BYTE = 0,   ///< SDIO byte transfer mode
    SDMMC_IO_MODE_TRANSFER_BLOCK       ///< SDIO block transfer mode
} sdmmc_io_transfer_mode_t;

/** SDIO address mode, configurable in SDIO read/write extended commands. */
typedef enum e_sdmmc_io_address_mode
{
    SDMMC_IO_ADDRESS_MODE_FIXED = 0,   ///< Write all data to the same address
    SDMMC_IO_ADDRESS_MODE_INCREMENT    ///< Increment destination address after each write
} sdmmc_io_address_mode_t;

/** Controls the RAW (read after write) flag of CMD52. Used to read back the status after writing a control register. */
typedef enum e_sdmmc_io_write_mode
{
    SDMMC_IO_WRITE_MODE_NO_READ = 0,   ///< Write only (do not read back)
    SDMMC_IO_WRITE_READ_AFTER_WRITE    ///< Read back the register after write
} sdmmc_io_write_mode_t;

/** Events that can trigger a callback function */
typedef enum e_sdmmc_event
{
    SDMMC_EVENT_CARD_REMOVED      = 1U << 0, ///< Card removed event.
    SDMMC_EVENT_CARD_INSERTED     = 1U << 1, ///< Card inserted event.
    SDMMC_EVENT_RESPONSE          = 1U << 3, ///< Response event.
    SDMMC_EVENT_SDIO              = 1U << 4, ///< IO event.
    SDMMC_EVENT_TRANSFER_COMPLETE = 1U << 5, ///< Read or write complete.
    SDMMC_EVENT_TRANSFER_ERROR    = 1U << 6, ///< Read or write failed.
    SDMMC_EVENT_ERASE_COMPLETE    = 1U << 7, ///< Erase completed.
    SDMMC_EVENT_ERASE_BUSY        = 1U << 8, ///< Erase timeout, poll @ref sdmmc_api_t::statusGet.
} sdmmc_event_t;

/** Card detection configuration options. */
/* Card detection using DAT3 is not supported. */
typedef enum e_sdmmc_card_detect
{
    SDMMC_CARD_DETECT_NONE,            ///< Card detection unused.
    SDMMC_CARD_DETECT_CD,              ///< Card detection using the CD pin
} sdmmc_card_detect_t;

/** Write protection configuration options. */
typedef enum e_sdmmc_write_protect
{
    SDMMC_WRITE_PROTECT_NONE,          ///< Write protection unused.
    SDMMC_WRITE_PROTECT_WP,            ///< Write protection using WP pin
} sdmmc_write_protect_t;

/** Card state when receiving the prior command. */
typedef enum e_sdmmc_r1_state
{
    SDMMC_R1_STATE_IDLE  = 0,          ///< Idle State
    SDMMC_R1_STATE_READY = 0,          ///< Ready State
    SDMMC_R1_STATE_IDENT = 0,          ///< Identification State
    SDMMC_R1_STATE_STBY  = 0,          ///< Stand-by State
    SDMMC_R1_STATE_TRAN  = 0,          ///< Transfer State
    SDMMC_R1_STATE_DATA  = 0,          ///< Sending-data State
    SDMMC_R1_STATE_RCV   = 0,          ///< Receive-data State
    SDMMC_R1_STATE_PRG   = 0,          ///< Programming State
    SDMMC_R1_STATE_DIS   = 0,          ///< Disconnect State (between programming and stand-by)
    SDMMC_R1_STATE_IO    = 15,         ///< This is an I/O card and memory states do not apply
} sdmmc_r1_state_t;

/* Structure for decoding the response of a command.  For advanced use only. */
typedef union u_sdmmc_response
{
    uint32_t status;

    /** SDIO Card Status Register. */
    struct
    {
        uint32_t                : 3;
        uint32_t ake_seq_error  : 1;            // Error in the sequence of the authentication process
        uint32_t                : 1;
        uint32_t app_cmd        : 1;            // The card will expect ACMD, or an indication that the command has been interpreted as ACMD
        uint32_t fx_event       : 1;            // Extension Functions may set this bit to get host to deal with events
        uint32_t switch_error   : 1;            //
        uint32_t ready_for_data : 1;            // Corresponds to the buffer empty signaling on the bus

        /* The state of the card when receiving the command. If the command execution causes a state change, it will be
         * visible to the host in the response to the next command. */
        sdmmc_r1_state_t current_state     : 4;
        uint32_t         erase_reset       : 1; // An erase sequence was cleared before executing because an out of erase sequence command was received.
        uint32_t         card_ecc_disabled : 1; // The command has been executed without using the internal ECC.
        uint32_t         wp_erase_skip     : 1; // Set when only partial address space was erased due to existing write protected blocks or the temporary or permanent write protected card was erased.
        uint32_t         csd_overwrite     : 1; // The read only section of the CSD does not match the card content or an attempt to reverse the copy or permanent WP bits was made.
        uint32_t                           : 2;
        uint32_t error                     : 1; // A general or unknown error occurred during the operation.
        uint32_t cc_error                  : 1; // Internal card controller error.
        uint32_t card_ecc_failed           : 1; // Card internal ECC was applied but failed to correct the data.
        uint32_t illegal_command           : 1; // Command not legal for the card state.
        uint32_t com_crc_error             : 1; // The CRC check of the previous command failed.
        uint32_t lock_unlock_failed        : 1; // Set when a sequence or password error has been detected in the lock/unlock command.
        uint32_t device_is_locked          : 1; // When set, signals that the card is locked by the host.
        uint32_t wp_violation              : 1; // Set when the host attempts to write to a protected block or to the temporary or permanent write protected card.
        uint32_t erase_param               : 1; // An invalid selection of write-blocks for erase occurred.
        uint32_t erase_seq_error           : 1; // An error in the sequence of erase commands occurred.
        uint32_t block_len_error           : 1; // The transferred block length is not allowed for this card, or the number of transferred bytes does not match the block length.
        uint32_t address_error             : 1; // A misaligned address which did not match the block length was used in the command.
        uint32_t out_of_range              : 1; // The command's argument was out of the allowed range for this card.
    } status_b;

    struct
    {
        uint32_t reserved_0 : 7;

        uint32_t reserved_lvr         : 1;
        uint32_t reserved_8           : 7;
        uint32_t v_27_28              : 1;
        uint32_t v_28_29              : 1;
        uint32_t v_29_30              : 1;
        uint32_t v_30_31              : 1;
        uint32_t v_31_32              : 1;
        uint32_t v_32_33              : 1;
        uint32_t v_33_34              : 1;
        uint32_t v_34_35              : 1;
        uint32_t v_35_36              : 1;
        uint32_t s18A                 : 1;
        uint32_t reserved_25          : 5;
        uint32_t card_capacity_status : 1;
        uint32_t power_up_status      : 1;
    } r3;

    struct
    {
        uint32_t ocr : 24;

        uint32_t reserved_24  : 3;
        uint32_t memory       : 1;
        uint32_t io_functions : 3;
        uint32_t ready        : 1;
    } r4;

    struct
    {
        uint32_t read_write_data : 8;

        uint32_t out_of_range     : 1;
        uint32_t invalid_function : 1;
        uint32_t rfu              : 1;
        uint32_t error            : 1;
        uint32_t current_state    : 2;
        uint32_t illegal_command  : 1;
        uint32_t crc_error        : 1;
        uint32_t reserved_16      : 16;
    } r5;

    struct
    {
        uint32_t reserved_0 : 3;

        uint32_t         ake_seq_error   : 1;
        uint32_t         reserved_4      : 1;
        uint32_t         app_cmd         : 1;
        uint32_t         reserved_6      : 2;
        uint32_t         ready_for_data  : 1;
        sdmmc_r1_state_t current_state   : 4;
        uint32_t         error           : 1;
        uint32_t         illegal_command : 1;
        uint32_t         com_crc_error   : 1;
        uint32_t         rca             : 16;
    } r6;

    struct
    {
        uint32_t check_pattern : 8;

        uint32_t voltage_accepted : 4;
        uint32_t reserved_11      : 20;
    } r7;
} sdmmc_response_t;

/** Current status. */
typedef struct s_sdmmc_status
{
    /** False if card was removed (only applies if MCU supports card detection and SDnCD pin is connected), true otherwise.
     *
     *  If ready is false, call @ref sdmmc_api_t::mediaInit to reinitialize it
     */
    bool initialized;
    bool transfer_in_progress;         ///< true = Card is busy
    bool card_inserted;                ///< Card detect status, true if card detect is not used
} sdmmc_status_t;

/** Information obtained from the media device. */
typedef struct s_sdmmc_device
{
    sdmmc_card_type_t card_type;          ///< SD, eMMC, or SDIO
    bool              write_protected;    ///< true = Card is write protected
    uint32_t          clock_rate;         ///< Current clock rate
    uint32_t          sector_count;       ///< Sector count
    uint32_t          sector_size_bytes;  ///< Sector size
    uint32_t          erase_sector_count; ///< Minimum erasable unit (in 512 byte sectors)
} sdmmc_device_t;

/** Callback function parameter data */
typedef struct st_sdmmc_callback_args
{
    sdmmc_event_t    event;            ///< The event can be used to identify what caused the callback.
    sdmmc_response_t response;         ///< Response from card, only valid if SDMMC_EVENT_RESPONSE is set in event.
    void           * p_context;        ///< Placeholder for user data.
} sdmmc_callback_args_t;

/** Non-secure arguments for writeIo guard function */
typedef struct st_sdmmc_write_io_args_t
{
    uint8_t * const       p_data;
    uint32_t              function;
    uint32_t              address;
    sdmmc_io_write_mode_t read_after_write;
} sdmmc_write_io_args_t;

/** Non-secure arguments for readIoExt guard function */
typedef struct st_sdmmc_read_io_ext_args_t
{
    uint8_t * const          p_dest;
    uint32_t                 function;
    uint32_t                 address;
    uint32_t * const         count;
    sdmmc_io_transfer_mode_t transfer_mode;
    sdmmc_io_address_mode_t  address_mode;
} sdmmc_read_io_ext_args_t;

/** Non-secure arguments for writeIoExt guard function */
typedef struct st_sdmmc_write_io_ext_args_t
{
    uint8_t const * const    p_source;
    uint32_t                 function;
    uint32_t                 address;
    uint32_t                 count;
    sdmmc_io_transfer_mode_t transfer_mode;
    sdmmc_io_address_mode_t  address_mode;
} sdmmc_write_io_ext_args_t;

/** SD/MMC Configuration */
typedef struct st_sdmmc_cfg
{
    /* SD/MMC generic configuration */
    uint8_t                     channel;                 ///< Channel of SD/MMC host interface.
    sdmmc_bus_width_t           bus_width;               ///< Device bus width is 1, 4 or 8 bits wide.
    transfer_instance_t const * p_lower_lvl_transfer;    ///< Transfer instance used to move data with DMA or DTC

    /* Configuration for SD/MMC Event processing */
    void (* p_callback)(sdmmc_callback_args_t * p_args); ///< Pointer to callback function
    void * p_context;                                    ///< User defined context passed into callback function

    /* Pointer to SD/MMC peripheral specific configuration */
    void const * p_extend;                               ///< SD/MMC hardware dependent configuration

    /** Block size in bytes.  Block size must be 512 bytes for SD cards and eMMC devices.  Block size can be 1-512
     * bytes for SDIO. */
    uint32_t block_size;

    /** Whether or not card detection is used. */
    sdmmc_card_detect_t card_detect;

    /** Select whether or not to use the write protect pin. Select Not Used if the MCU or device does not have a write protect pin. */
    sdmmc_write_protect_t write_protect;
    IRQn_Type             access_irq;  ///< Access IRQ number
    IRQn_Type             sdio_irq;    ///< SDIO IRQ number
    IRQn_Type             card_irq;    ///< Card IRQ number
    IRQn_Type             dma_req_irq; ///< DMA request IRQ number
    uint8_t               access_ipl;  ///< Access interrupt priority
    uint8_t               sdio_ipl;    ///< SDIO interrupt priority
    uint8_t               card_ipl;    ///< Card interrupt priority
    uint8_t               dma_req_ipl; ///< DMA request interrupt priority
} sdmmc_cfg_t;

/** SD/MMC control block.  Allocate an instance specific control block to pass into the SD/MMC API calls.
 */
typedef void sdmmc_ctrl_t;

/** SD/MMC functions implemented at the HAL layer API. */
typedef struct st_sdmmc_api
{
    /** Open the SD/MMC driver.
     *
     *
     * @param[in]     p_ctrl    Pointer to SD/MMC instance control block.
     * @param[in]     p_cfg     Pointer to SD/MMC instance configuration structure.
     */
    fsp_err_t (* open)(sdmmc_ctrl_t * const p_ctrl, sdmmc_cfg_t const * const p_cfg);

    /** Initializes an SD/MMC device.  If the device is a card, the card must be plugged in prior to calling this API.
     * This API blocks until the device initialization procedure is complete.
     *
     *
     * @param[in]     p_ctrl    Pointer to SD/MMC instance control block.
     * @param[out]    p_device  Pointer to store device information.
     */
    fsp_err_t (* mediaInit)(sdmmc_ctrl_t * const p_ctrl, sdmmc_device_t * const p_device);

    /** Read data from an SD/MMC channel.
     * This API is not supported for SDIO devices.
     *
     *
     * @param[in]     p_ctrl          Pointer to an open SD/MMC instance control block.
     * @param[out]    p_dest          Pointer to data buffer to read data to.
     * @param[in]     start_sector    First sector address to read.
     * @param[in]     sector_count    Number of sectors to read.  All sectors must be in the range of
     *                                sdmmc_device_t::sector_count.
     */
    fsp_err_t (* read)(sdmmc_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const start_sector,
                       uint32_t const sector_count);

    /** Write data to SD/MMC channel.
     * This API is not supported for SDIO devices.
     *
     *
     * @param[in]     p_ctrl          Pointer to an open SD/MMC instance control block.
     * @param[in]     p_source        Pointer to data buffer to write data from.
     * @param[in]     start_sector    First sector address to write to.
     * @param[in]     sector_count    Number of sectors to write.  All sectors must be in the range of
     *                                sdmmc_device_t::sector_count.
     */
    fsp_err_t (* write)(sdmmc_ctrl_t * const p_ctrl, uint8_t const * const p_source, uint32_t const start_sector,
                        uint32_t const sector_count);

    /** Read one byte of I/O data from an SDIO device.
     * This API is not supported for SD or eMMC memory devices.
     *
     *
     * @param[in]     p_ctrl    Pointer to an open SD/MMC instance control block.
     * @param[out]    p_data    Pointer to location to store data byte.
     * @param[in]     function  SDIO Function Number.
     * @param[in]     address   SDIO register address.
     */
    fsp_err_t (* readIo)(sdmmc_ctrl_t * const p_ctrl, uint8_t * const p_data, uint32_t const function,
                         uint32_t const address);

    /** Write one byte of I/O data to an SDIO device.
     * This API is not supported for SD or eMMC memory devices.
     *
     *
     * @param[in]     p_ctrl            Pointer to an open SD/MMC instance control block.
     * @param[in,out] p_data            Pointer to data byte to write.  Read data is also provided here if
     *                                  read_after_write is true.
     * @param[in]     function          SDIO Function Number.
     * @param[in]     address           SDIO register address.
     * @param[in]     read_after_write  Whether or not to read back the same register after writing
     */
    fsp_err_t (* writeIo)(sdmmc_ctrl_t * const p_ctrl, uint8_t * const p_data, uint32_t const function,
                          uint32_t const address, sdmmc_io_write_mode_t const read_after_write);

    /** Read multiple bytes or blocks of I/O data from an SDIO device.
     * This API is not supported for SD or eMMC memory devices.
     *
     *
     * @param[in]     p_ctrl          Pointer to an open SD/MMC instance control block.
     * @param[out]    p_dest          Pointer to data buffer to read data to.
     * @param[in]     function        SDIO Function Number.
     * @param[in]     address         SDIO register address.
     * @param[in]     count           Number of bytes or blocks to read, maximum 512 bytes or 511 blocks.
     * @param[in]     transfer_mode   Byte or block mode
     * @param[in]     address_mode    Fixed or incrementing address mode
     */
    fsp_err_t (* readIoExt)(sdmmc_ctrl_t * const p_ctrl, uint8_t * const p_dest, uint32_t const function,
                            uint32_t const address, uint32_t * const count, sdmmc_io_transfer_mode_t transfer_mode,
                            sdmmc_io_address_mode_t address_mode);

    /** Write multiple bytes or blocks of I/O data to an SDIO device.
     * This API is not supported for SD or eMMC memory devices.
     *
     *
     * @param[in]     p_ctrl          Pointer to an open SD/MMC instance control block.
     * @param[in]     p_source        Pointer to data buffer to write data from.
     * @param[in]     function_number SDIO Function Number.
     * @param[in]     address         SDIO register address.
     * @param[in]     count           Number of bytes or blocks to write, maximum 512 bytes or 511 blocks.
     * @param[in]     transfer_mode   Byte or block mode
     * @param[in]     address_mode    Fixed or incrementing address mode
     */
    fsp_err_t (* writeIoExt)(sdmmc_ctrl_t * const p_ctrl, uint8_t const * const p_source, uint32_t const function,
                             uint32_t const address, uint32_t const count, sdmmc_io_transfer_mode_t transfer_mode,
                             sdmmc_io_address_mode_t address_mode);

    /** Enables SDIO interrupt for SD/MMC instance.
     * This API is not supported for SD or eMMC memory devices.
     *
     *
     * @param[in]     p_ctrl    Pointer to an open SD/MMC instance control block.
     * @param[in]     enable    Interrupt enable = true, interrupt disable = false.
     */
    fsp_err_t (* ioIntEnable)(sdmmc_ctrl_t * const p_ctrl, bool enable);

    /** Get SD/MMC device status.
     *
     *
     * @param[in]     p_ctrl    Pointer to an open SD/MMC instance control block.
     * @param[out]    p_status  Pointer to current driver status.
     */
    fsp_err_t (* statusGet)(sdmmc_ctrl_t * const p_ctrl, sdmmc_status_t * const p_status);

    /** Erase SD/MMC sectors. The sector size for erase is fixed at 512 bytes.
     * This API is not supported for SDIO devices.
     *
     *
     * @param[in]     p_ctrl        Pointer to an open SD/MMC instance control block.
     * @param[in]     start_sector  First sector to erase. Must be a multiple of sdmmc_device_t::erase_sector_count.
     * @param[in]     sector_count  Number of sectors to erase. Must be a multiple of sdmmc_device_t::erase_sector_count.
     *                              All sectors must be in the range of sdmmc_device_t::sector_count.
     */
    fsp_err_t (* erase)(sdmmc_ctrl_t * const p_ctrl, uint32_t const start_sector, uint32_t const sector_count);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Control block set in @ref sdmmc_api_t::open call.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(sdmmc_ctrl_t * const p_ctrl, void (* p_callback)(sdmmc_callback_args_t *),
                              void * const p_context, sdmmc_callback_args_t * const p_callback_memory);

    /** Close open SD/MMC device.
     *
     *
     * @param[in]     p_ctrl    Pointer to an open SD/MMC instance control block.
     */
    fsp_err_t (* close)(sdmmc_ctrl_t * const p_ctrl);
} sdmmc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_sdmmc_instance
{
    sdmmc_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    sdmmc_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    sdmmc_api_t const * p_api;         ///< Pointer to the API structure for this instance
} sdmmc_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup SDMMC_API)
 **********************************************************************************************************************/
