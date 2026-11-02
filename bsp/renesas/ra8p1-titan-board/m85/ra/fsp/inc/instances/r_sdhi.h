/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SDHI_H
#define R_SDHI_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sdhi_cfg.h"
#include "r_sdmmc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup SDHI
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SDHI_MAX_BLOCK_SIZE    (512U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Private enumeration used in sdhi_instance_ctrl_t. */
typedef enum e_sdhi_transfer_dir
{
    SDHI_TRANSFER_DIR_NONE,
    SDHI_TRANSFER_DIR_READ,
    SDHI_TRANSFER_DIR_WRITE
} sdhi_transfer_dir_t;

/* Private structure used in sdhi_instance_ctrl_t. */
typedef union
{
    uint32_t word;

    struct s_sdhi_event_type
    {
        uint32_t response_end       : 1; // < response end detected
        uint32_t reserved_1         : 1;
        uint32_t access_end         : 1; // < access end detected
        uint32_t card_removed       : 1; // < card removal detected by cd pin
        uint32_t card_inserted      : 1; // < card insertion detected by cd pin
        uint32_t reserved_5         : 3;
        uint32_t card_dat3_removed  : 1; // < card removal detected by dat3 pin
        uint32_t card_dat3_inserted : 1; // < card inserion detected by dat3 pin
        uint32_t reserved_10        : 6;
        uint32_t cmd_err            : 1; // < command error
        uint32_t crc_err            : 1; // < crc error
        uint32_t end_err            : 1; // < end bit error
        uint32_t dto                : 1; // < data timeout
        uint32_t ilw                : 1; // < illegal write address
        uint32_t ilr                : 1; // < illegal read address
        uint32_t rspt               : 1; // < response timeout
        uint32_t event_error        : 1; // < all error flags combined
        uint32_t bre                : 1; // < buffer read enable
        uint32_t bwe                : 1; // < buffer write enable
        uint32_t reserved_26        : 5;
        uint32_t ila_err            : 1; // < illegal access
    } bit;
} sdhi_event_t;

/** SDMMC instance control block.  This is private to the FSP and should not be used or modified by the application. */
typedef struct st_sdmmc_instance_ctrl
{
    uint32_t              open;
    sdmmc_cfg_t const   * p_cfg;
    sdmmc_device_t        device;
    bool                  sector_addressing;
    bool                  transfer_in_progress;
    bool                  initialized;
    R_SDHI0_Type        * p_reg;
    volatile sdhi_event_t sdhi_event;
    sdhi_transfer_dir_t   transfer_dir;
    uint8_t             * p_transfer_data;
    uint32_t              transfer_blocks_total;
    uint32_t              transfer_block_current;
    uint32_t              transfer_block_size;
    uint32_t              aligned_buff[SDHI_MAX_BLOCK_SIZE / sizeof(uint32_t)];

    void (* p_callback)(sdmmc_callback_args_t *); // Pointer to callback
    sdmmc_callback_args_t * p_callback_memory;    // Pointer to optional callback argument memory
    void * p_context;                             // Pointer to context to be passed into callback function
} sdhi_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const sdmmc_api_t g_sdmmc_on_sdhi;

/** @endcond */

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/

fsp_err_t R_SDHI_Open(sdmmc_ctrl_t * const p_api_ctrl, sdmmc_cfg_t const * const p_cfg);
fsp_err_t R_SDHI_MediaInit(sdmmc_ctrl_t * const p_api_ctrl, sdmmc_device_t * const p_device);
fsp_err_t R_SDHI_Read(sdmmc_ctrl_t * const p_api_ctrl,
                      uint8_t * const      p_dest,
                      uint32_t const       start_sector,
                      uint32_t const       sector_count);
fsp_err_t R_SDHI_Write(sdmmc_ctrl_t * const  p_api_ctrl,
                       uint8_t const * const p_source,
                       uint32_t const        start_sector,
                       uint32_t const        sector_count);
fsp_err_t R_SDHI_ReadIo(sdmmc_ctrl_t * const p_api_ctrl,
                        uint8_t * const      p_data,
                        uint32_t const       function,
                        uint32_t const       address);
fsp_err_t R_SDHI_WriteIo(sdmmc_ctrl_t * const        p_api_ctrl,
                         uint8_t * const             p_data,
                         uint32_t const              function,
                         uint32_t const              address,
                         sdmmc_io_write_mode_t const read_after_write);
fsp_err_t R_SDHI_ReadIoExt(sdmmc_ctrl_t * const     p_api_ctrl,
                           uint8_t * const          p_dest,
                           uint32_t const           function,
                           uint32_t const           address,
                           uint32_t * const         count,
                           sdmmc_io_transfer_mode_t transfer_mode,
                           sdmmc_io_address_mode_t  address_mode);
fsp_err_t R_SDHI_WriteIoExt(sdmmc_ctrl_t * const     p_api_ctrl,
                            uint8_t const * const    p_source,
                            uint32_t const           function,
                            uint32_t const           address,
                            uint32_t const           count,
                            sdmmc_io_transfer_mode_t transfer_mode,
                            sdmmc_io_address_mode_t  address_mode);
fsp_err_t R_SDHI_IoIntEnable(sdmmc_ctrl_t * const p_api_ctrl, bool enable);
fsp_err_t R_SDHI_StatusGet(sdmmc_ctrl_t * const p_api_ctrl, sdmmc_status_t * const p_status);
fsp_err_t R_SDHI_Erase(sdmmc_ctrl_t * const p_api_ctrl, uint32_t const start_sector, uint32_t const sector_count);
fsp_err_t R_SDHI_CallbackSet(sdmmc_ctrl_t * const          p_api_ctrl,
                             void (                      * p_callback)(sdmmc_callback_args_t *),
                             void * const                  p_context,
                             sdmmc_callback_args_t * const p_callback_memory);
fsp_err_t R_SDHI_Close(sdmmc_ctrl_t * const p_api_ctrl);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_SDHI_H

/*******************************************************************************************************************//**
 * @} (end addtogroup SDHI)
 **********************************************************************************************************************/
