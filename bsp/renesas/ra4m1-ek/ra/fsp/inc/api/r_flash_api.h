/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_STORAGE_INTERFACES
 * @defgroup FLASH_API Flash Interface
 * @brief Interface for the Flash Memory.
 *
 * @section FLASH_API_SUMMARY Summary
 *
 * The Flash interface provides the ability to read, write, erase, and blank check the code flash and data flash
 * regions.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_FLASH_API_H
#define R_FLASH_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/** Result type for certain operations */
typedef enum e_flash_result
{
    FLASH_RESULT_BLANK,                ///< Return status for Blank Check Function
    FLASH_RESULT_NOT_BLANK,            ///< Return status for Blank Check Function
    FLASH_RESULT_BGO_ACTIVE            ///< Flash is configured for BGO mode. Result is returned in callback.
} flash_result_t;

/** Parameter for specifying the startup area swap being requested by startupAreaSelect() */
typedef enum e_flash_startup_area_swap
{
    FLASH_STARTUP_AREA_BTFLG  = 0,     ///< Startup area will be set based on the value of the BTFLG
    FLASH_STARTUP_AREA_BLOCK0 = 0x2,   ///< Startup area will be set to Block 0
    FLASH_STARTUP_AREA_BLOCK1 = 0x3,   ///< Startup area will be set to Block 1
} flash_startup_area_swap_t;

/** Event types returned by the ISR callback when used in Data Flash BGO mode */
typedef enum e_flash_event
{
    FLASH_EVENT_ERASE_COMPLETE,        ///< Erase operation successfully completed
    FLASH_EVENT_WRITE_COMPLETE,        ///< Write operation successfully completed
    FLASH_EVENT_BLANK,                 ///< Blank check operation successfully completed. Specified area is blank
    FLASH_EVENT_NOT_BLANK,             ///< Blank check operation successfully completed. Specified area is NOT blank
    FLASH_EVENT_ERR_DF_ACCESS,         ///< Data Flash operation failed. Can occur when writing an unerased section.
    FLASH_EVENT_ERR_CF_ACCESS,         ///< Code Flash operation failed. Can occur when writing an unerased section.
    FLASH_EVENT_ERR_CMD_LOCKED,        ///< Operation failed, FCU is in Locked state (often result of an illegal command)
    FLASH_EVENT_ERR_FAILURE,           ///< Erase or Program Operation failed
    FLASH_EVENT_ERR_ONE_BIT            ///< A 1-bit error has been corrected when reading the flash memory area by the sequencer.
} flash_event_t;

/** ID Code Modes for writing to ID code registers */
typedef enum e_flash_id_code_mode
{
    FLASH_ID_CODE_MODE_UNLOCKED = 0,                            ///< ID code is ignored
    FLASH_ID_CODE_MODE_LOCKED_WITH_ALL_ERASE_SUPPORT = 0xC000U, ///< ID code is checked. All erase is available.
    FLASH_ID_CODE_MODE_LOCKED = 0x8000U                         ///< ID code is checked.
} flash_id_code_mode_t;

/** Flash status */
typedef enum e_flash_status
{
    FLASH_STATUS_IDLE,                 ///< The flash is idle.
    FLASH_STATUS_BUSY                  ///< The flash is currently processing a command.
} flash_status_t;

/** Anti-rollback counter selection.  */
typedef enum e_flash_arc
{
    FLASH_ARC_SEC    = 0,              ///< Anti-Rollback Counter for the secure application
    FLASH_ARC_OEMBL  = 1,              ///< Anti-Rollback Counter for the OEM bootloader
    FLASH_ARC_NSEC_0 = 2,              ///< Anti-Rollback Counter for non-secure application 0 (use when a single non-secure counter is available or when multiple non-secure counters are available)
    FLASH_ARC_NSEC_1 = 3,              ///< Anti-Rollback Counter for non-secure application 1 (use when multiple non-secure counters are available)
    FLASH_ARC_NSEC_2 = 4,              ///< Anti-Rollback Counter for non-secure application 2 (use when multiple non-secure counters are available)
    FLASH_ARC_NSEC_3 = 5,              ///< Anti-Rollback Counter for non-secure application 3 (use when multiple non-secure counters are available)
} flash_arc_t;

/** Flash block details stored in factory flash. */
typedef struct st_flash_block_info
{
    uint32_t block_section_st_addr;    ///< Starting address for this block section (blocks of this size)
    uint32_t block_section_end_addr;   ///< Ending address for this block section (blocks of this size)
    uint32_t block_size;               ///< Flash erase block size
    uint32_t block_size_write;         ///< Flash write block size
} flash_block_info_t;

/** Flash block details */
typedef struct st_flash_regions
{
    uint32_t num_regions;                     ///< Length of block info array
    flash_block_info_t const * p_block_array; ///< Block info array base address
} flash_regions_t;

/** Information about the flash blocks */
typedef struct st_flash_info
{
    flash_regions_t code_flash;        ///< Information about the code flash regions
    flash_regions_t data_flash;        ///< Information about the code flash regions
} flash_info_t;

/** Flash control block.  Allocate an instance specific control block to pass into the flash API calls.
 */
typedef void flash_ctrl_t;

/** Callback function parameter data */
typedef struct st_flash_user_cb_data
{
    flash_event_t event;               ///< Event can be used to identify what caused the callback (flash ready or error).
    void        * p_context;           ///< Placeholder for user data.  Set in @ref flash_api_t::open function in::flash_cfg_t.
} flash_callback_args_t;

/** FLASH Configuration */
typedef struct st_flash_cfg
{
    bool data_flash_bgo;                                 ///< True if BGO (Background Operation) is enabled for Data Flash.

    /* Configuration for FLASH Event processing */
    void (* p_callback)(flash_callback_args_t * p_args); ///< Callback provided when a Flash interrupt ISR occurs.

    /* Pointer to FLASH peripheral specific configuration */
    void const * p_extend;                               ///< FLASH hardware dependent configuration
    void       * p_context;                              ///< Placeholder for user data.  Passed to user callback in @ref flash_callback_args_t.
    uint8_t      ipl;                                    ///< Flash ready interrupt priority
    IRQn_Type    irq;                                    ///< Flash ready interrupt number
    uint8_t      err_ipl;                                ///< Flash error interrupt priority (unused in r_flash_lp)
    IRQn_Type    err_irq;                                ///< Flash error interrupt number (unused in r_flash_lp)
} flash_cfg_t;

/** Shared Interface definition for FLASH */
typedef struct st_flash_api
{
    /** Open FLASH device.
     *
     * @param[out]  p_ctrl       Pointer to FLASH device control. Must be declared by user. Value set here.
     * @param[in]   flash_cfg_t  Pointer to FLASH configuration structure. All elements of this structure
     *                           must be set by the user.
     */
    fsp_err_t (* open)(flash_ctrl_t * const p_ctrl, flash_cfg_t const * const p_cfg);

    /** Write FLASH device.
     *
     * @param[in]   p_ctrl         Control for the FLASH device context.
     * @param[in]   src_address    Address of the buffer containing the data to write to Flash.
     * @param[in]   flash_address  Code Flash or Data Flash address to write. The address must be on a
     *                             programming line boundary.
     * @param[in]   num_bytes      The number of bytes to write. This number must be a multiple
     *                             of the programming size. For Code Flash this is FLASH_MIN_PGM_SIZE_CF.
     *                             For Data Flash this is FLASH_MIN_PGM_SIZE_DF.
     *                             @warning Specifying a number that is not a multiple of the programming size
     *                             will result in SF_FLASH_ERR_BYTES being returned and no data written.
     */
    fsp_err_t (* write)(flash_ctrl_t * const p_ctrl, uint32_t const src_address, uint32_t const flash_address,
                        uint32_t const num_bytes);

    /** Erase FLASH device.
     *
     * @param[in]  p_ctrl               Control for the FLASH device.
     * @param[in]  address              The block containing this address is the first block erased.
     * @param[in]  num_blocks           Specifies the number of blocks to be erased, the starting block determined
     *                                  by the block_erase_address.
     */
    fsp_err_t (* erase)(flash_ctrl_t * const p_ctrl, uint32_t const address, uint32_t const num_blocks);

    /** Blank check FLASH device.
     *
     * @param[in]   p_ctrl                Control for the FLASH device context.
     * @param[in]   address               The starting address of the Flash area to blank check.
     * @param[in]   num_bytes             Specifies the number of bytes that need to be checked.
     *                                    See the specific handler for details.
     * @param[out]  p_blank_check_result  Pointer that will be populated by the API with the results of the blank check
     *                                    operation in non-BGO (blocking) mode. In this case the blank check operation
     *                                    completes here and the result is returned. In Data Flash BGO mode the blank
     *                                    check operation is only started here and the result obtained later when the
     *                                    supplied callback routine is called. In this case FLASH_RESULT_BGO_ACTIVE will
     *                                    be returned in p_blank_check_result.
     */
    fsp_err_t (* blankCheck)(flash_ctrl_t * const p_ctrl, uint32_t const address, uint32_t const num_bytes,
                             flash_result_t * const p_blank_check_result);

    /** Close FLASH device.
     *
     * @param[in]   p_ctrl        Pointer to FLASH device control.
     * @param[out]  p_info        Pointer to FLASH info structure.
     */
    fsp_err_t (* infoGet)(flash_ctrl_t * const p_ctrl, flash_info_t * const p_info);

    /** Close FLASH device.
     *
     * @param[in]  p_ctrl        Pointer to FLASH device control.
     */
    fsp_err_t (* close)(flash_ctrl_t * const p_ctrl);

    /** Get Status for FLASH device.
     *
     * @param[in]  p_ctrl        Pointer to FLASH device control.
     * @param[out]  p_ctrl       Pointer to the current flash status.
     */
    fsp_err_t (* statusGet)(flash_ctrl_t * const p_ctrl, flash_status_t * const p_status);

    /** Set Access Window for FLASH device.
     *
     * @param[in]  p_ctrl        Pointer to FLASH device control.
     * @param[in]  start_addr    Determines the Starting block for the Code Flash access window.
     * @param[in]  end_addr      Determines the Ending block for the Code Flash access window. This address will not be
     *                           within the access window.
     */
    fsp_err_t (* accessWindowSet)(flash_ctrl_t * const p_ctrl, uint32_t const start_addr, uint32_t const end_addr);

    /** Clear any existing Code Flash access window for FLASH device.
     *
     * @param[in]  p_ctrl        Pointer to FLASH device control.
     * @param[in]  start_addr    Determines the Starting block for the Code Flash access window.
     * @param[in]  end_addr      Determines the Ending block for the Code Flash access window.
     */
    fsp_err_t (* accessWindowClear)(flash_ctrl_t * const p_ctrl);

    /** Set ID Code for FLASH device. Setting the ID code can restrict access to the device. The ID code will be
     * required to connect to the device. Bits 126 and 127 are set based on the mode.
     *
     * For example, uint8_t id_bytes[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
     *                            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0x00};
     * with mode FLASH_ID_CODE_MODE_LOCKED_WITH_ALL_ERASE_SUPPORT
     * will result in an ID code of 00112233445566778899aabbccddeec0
     *
     * With mode FLASH_ID_CODE_MODE_LOCKED, it
     * will result in an ID code of 00112233445566778899aabbccddee80
     *
     *
     * @param[in]  p_ctrl        Pointer to FLASH device control.
     * @param[in]  p_id_bytes    Ponter to the ID Code to be written.
     * @param[in]  mode          Mode used for checking the ID code.
     */
    fsp_err_t (* idCodeSet)(flash_ctrl_t * const p_ctrl, uint8_t const * const p_id_bytes, flash_id_code_mode_t mode);

    /** Reset function for FLASH device.
     *
     * @param[in]  p_ctrl        Pointer to FLASH device control.
     */
    fsp_err_t (* reset)(flash_ctrl_t * const p_ctrl);

    /** Update Flash clock frequency (FCLK) and recalculate timeout values
     * @param[in]  p_ctrl        Pointer to FLASH device control.
     */
    fsp_err_t (* updateFlashClockFreq)(flash_ctrl_t * const p_ctrl);

    /** Select which block - Default (Block 0) or Alternate (Block 1) is used as the start-up area block.
     *
     * @param[in]  p_ctrl        Pointer to FLASH device control.
     * @param[in]  swap_type     FLASH_STARTUP_AREA_BLOCK0, FLASH_STARTUP_AREA_BLOCK1 or FLASH_STARTUP_AREA_BTFLG.
     * @param[in]  is_temporary  True or false. See table below.
     *
     * | swap_type             |    is_temporary |   Operation |
     * |-----------------------|-----------------|-------------|
     * | FLASH_STARTUP_AREA_BLOCK0 |  false  |     On next reset Startup area will be Block 0. |
     * | FLASH_STARTUP_AREA_BLOCK1 |  true   |     Startup area is immediately, but temporarily switched to Block 1. |
     * | FLASH_STARTUP_AREA_BTFLG  |  true   |     Startup area is immediately, but temporarily switched to the Block determined by the Configuration BTFLG. |
     *
     */
    fsp_err_t (* startupAreaSelect)(flash_ctrl_t * const p_ctrl, flash_startup_area_swap_t swap_type,
                                    bool is_temporary);

    /** Swap the bank used as the startup area. On Flash HP, need to change into dual bank mode to use this feature.
     *
     * @param[in]  p_ctrl        Pointer to FLASH device control.
     */
    fsp_err_t (* bankSwap)(flash_ctrl_t * const p_ctrl);

    /** Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to FLASH device control.
     * @param[in]   p_callback               Callback function to register
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(flash_ctrl_t * const p_ctrl, void (* p_callback)(flash_callback_args_t *),
                              void * const p_context, flash_callback_args_t * const p_callback_memory);

    /** Increment the selected anti-rollback counter.
     *
     * @warning Once incremented, the counter can never be decremented or reset, even with a debug probe.
     *
     * @param[in]  p_ctrl                    Pointer to FLASH device control.
     * @param[in]  counter                   The anti-rollback counter to increment
     */
    fsp_err_t (* antiRollbackCounterIncrement)(flash_ctrl_t * const p_ctrl, flash_arc_t counter);

    /** Refresh the selected anti-rollback counter flash area.
     *
     * @param[in]   p_ctrl                   Pointer to FLASH device control.
     * @param[in]   counter                  The anti-rollback counter to refresh
     */
    fsp_err_t (* antiRollbackCounterRefresh)(flash_ctrl_t * const p_ctrl, flash_arc_t counter);

    /** Read current count value of the selected anti-rollback counter.
     *
     * @param[in]   p_ctrl                   Pointer to FLASH device control.
     * @param[in]   counter                  The anti-rollback counter to read
     * @param[out]  p_count                  The current count value
     */
    fsp_err_t (* antiRollbackCounterRead)(flash_ctrl_t * const p_ctrl, flash_arc_t counter, uint32_t * const p_count);

    /** Write to the user lockable area for the flash device
     *
     * @warning Data will not be written if any segment of the specified area is locked.
     *
     * @param[in]   p_ctrl         Pointer to FLASH device control.
     * @param[in]   src_address    Address of the buffer containing the data to write to flash.
     * @param[in]   flash_address  User lockable area flash address to write. The address must be on a
     *                             programming line boundary.
     * @param[in]   num_bytes      The number of bytes to write. This number must be a multiple
     *                             of the programming size.
     */
    fsp_err_t (* userLockableAreaWrite)(flash_ctrl_t * const p_ctrl, uint32_t const src_address,
                                        uint32_t const flash_address, uint32_t const num_bytes);
} flash_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_flash_instance
{
    flash_ctrl_t      * p_ctrl;        ///< Pointer to the control structure for this instance
    flash_cfg_t const * p_cfg;         ///< Pointer to the configuration structure for this instance
    flash_api_t const * p_api;         ///< Pointer to the API structure for this instance
} flash_instance_t;

/******************************************************************************************************************//**
 * @} (end defgroup FLASH_API)
 *********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
