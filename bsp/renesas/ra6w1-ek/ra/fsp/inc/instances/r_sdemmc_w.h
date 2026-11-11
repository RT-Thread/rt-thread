/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_SDEMMC_W_H
#define R_SDEMMC_W_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_sdemmc_w_cfg.h"
#include "r_sdmmc_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup SDEMMC_W
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define SDEMMC_W_MAX_BLOCK_SIZE    (512U)

#define SDEMMC_W_CLK_DIV_40M       (0U)
#define SDEMMC_W_CLK_DIV_20M       (1U)
#define SDEMMC_W_CLK_DIV_10M       (2U)
#define SDEMMC_W_CLK_DIV_5M        (4U)

#define SDEMMC_W_HOST_PORT_0       (0U)
#define SDEMMC_W_HOST_PORT_1       (1U)

#define SDEMMC_W_HOST_RXCLK_IN_0   (0U)
#define SDEMMC_W_HOST_RXCLK_IN_1   (1U)

#define SDEMMC_W_DEVICE_PORT_0     (0U)
#define SDEMMC_W_DEVICE_PORT_1     (1U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Private enumeration used in sdemmc_w_instance_ctrl_t. */
typedef enum e_sdemmc_w_transfer_dir
{
    SDEMMC_W_TRANSFER_DIR_NONE, ///< The transfer direction is none
    SDEMMC_W_TRANSFER_DIR_READ, ///< The transfer direction is read
    SDEMMC_W_TRANSFER_DIR_WRITE ///< The transfer direction is write
} sdemmc_w_transfer_dir_t;

/** Private structure used in sdemmc_w_instance_ctrl_t. */
typedef union
{
    uint32_t word;

    struct s_sdemmc_w_event_type
    {
        uint32_t response_end       : 1; ///<  response end detected
        uint32_t access_end         : 1; ///<  access end detected
        uint32_t reserved_1         : 4;
        uint32_t card_inserted      : 1; ///<  card insertion detected by cd pin
        uint32_t card_removed       : 1; ///<  card removal detected by cd pin
        uint32_t CardInterrupt      : 1; ///<  [8..8] CardInterrupt
        uint32_t reserved_5         : 6;
        uint32_t ErrorInterrupt     : 1; ///<  [15..15] ErrorInterrupt
        uint32_t CommandTimeoutError: 1; ///<  [16..16] CommandTimeoutError
        uint32_t crc_err            : 1; ///<  crc error
        uint32_t end_err            : 1; ///<  end bit error
        uint32_t cmd_err            : 1; ///<  command error
        uint32_t dto                : 1; ///<  data timeout
        uint32_t DataCRCError       : 1; ///<  [21..21] DataCRCError
        uint32_t DataEndBitError    : 1; ///<  [22..22] DataEndBitError
        uint32_t CurrentLimitError  : 1; ///<  [23..23] CurrentLimitError
        uint32_t AutoCMDError       : 1; ///<  [24..24] AutoCMDError
        uint32_t ADMAError          : 1; ///<  [25..25] ADMAError
        uint32_t TuningError        : 1; ///<  [26..26] TuningError
        uint32_t VendorSpecificError: 5; ///<  VendorSpecificError
    } bit;
} sdemmc_w_event_t;

/** Private enumeration used in sdmmc_callback_args_t. */
typedef enum e_sdemmc_w_priv_event
{
    SDEMMC_W_PRIV_EVENT_CARD_REMOVED        = 1U << 0,  ///<  Card removed event.
    SDEMMC_W_PRIV_EVENT_CARD_INSERTED       = 1U << 1,  ///<  Card inserted event.
    SDEMMC_W_PRIV_EVENT_RESPONSE            = 1U << 3,  ///<  Response event.
    SDEMMC_W_PRIV_EVENT_SDIO                = 1U << 4,  ///<  IO event.
    SDEMMC_W_PRIV_EVENT_TRANSFER_COMPLETE   = 1U << 5,  ///<  Read or write complete.
    SDEMMC_W_PRIV_EVENT_TRANSFER_ERROR      = 1U << 6,  ///<  Read or write failed.
    SDEMMC_W_PRIV_EVENT_ERASE_COMPLETE      = 1U << 7,  ///<  Erase completed.
    SDEMMC_W_PRIV_EVENT_ERASE_BUSY          = 1U << 8,  ///<  Erase timeout, poll @ref sdmmc_api_t::statusGet.
    SDEMMC_W_PRIV_EVENT_SDIO_FN1_WR_OVR     = 1U << 9,  ///<  IO event.
    SDEMMC_W_PRIV_EVENT_SDIO_FN1_RD_OVR     = 1U << 10, ///<  IO event.
    SDEMMC_W_PRIV_EVENT_SDIO_FN1_MSG_RDY    = 1U << 11, ///<  IO event.
    SDEMMC_W_PRIV_EVENT_SDIO_FN1_ACK_TO_ARM = 1U << 12, ///<  IO event.
} sdemmc_w_priv_event_t;

/**  SDIO pads drive current */
typedef enum e_sdemmc_w_sdio_device_drive_current
{
    SDEMMC_W_SDIO_DEVICE_DRIVE_CURRENT_2  = 0, ///< 2 mA @3.3V
    SDEMMC_W_SDIO_DEVICE_DRIVE_CURRENT_4  = 1, ///< 4 mA @3.3V
    SDEMMC_W_SDIO_DEVICE_DRIVE_CURRENT_8  = 2, ///< 8 mA @3.3V
    SDEMMC_W_SDIO_DEVICE_DRIVE_CURRENT_14 = 3, ///< 14 mA @3.3V
} sdemmc_w_sdio_device_drive_current_t;

/** SDIO DMA configuration */
typedef struct
{
    uint32_t sdio_dma_length;      ///< DMA length
    uint32_t sdio_dma_buf_address; ///< DMA buffer address
} sdio_device_dma_config;

/** SDIO role used in sdmmc_cfg_t p_extend. */
typedef enum e_sdemmc_w_role
{
    SDEMMC_W_ROLE_HOST,   ///< Act as SD/eMMC/SDIO host
    SDEMMC_W_ROLE_DEVICE, ///< Act as SDIO device
} sdemmc_w_role_t;

/** Extended SDMMC interface configuration */
typedef struct st_sdemmc_w_extended_cfg
{
    sdio_device_dma_config dma_config_tx; ///< ADMA Region physical memory
    sdio_device_dma_config dma_config_rx; ///< ADMA Region physical memory
    uint32_t               sdemmc_w_role;  ///< SD/eMMC/SDIO host or SDIO device
    uint8_t                              clk_div;       ///< Clock divider value
    uint8_t                host_port_sel; ///< SD/eMMC/SDIO host port selection. 0: P0_[13:4], 1: P1_[3:0] and P1_[15:10]
    uint8_t                host_rxclk_in_sel; ///< SD/eMMC/SDIO host rxclk_in selection. 0: clkout signal, 1: clkout_inv signal
    uint8_t                host_pull_en_cfg; ///< SD/eMMC/SDIO host PADs mode pull enable.
    uint8_t                host_pull_sel_cfg; ///< SD/eMMC/SDIO host PADs mode pull selection.
    uint8_t                device_port_sel; ///< SDIO device port selection. 0: Port P0_[13:8], 1: Port P1_[15:10]
    uint8_t                device_pull_en_cfg; ///< SDIO device PADs mode pull enable
    uint8_t                device_pull_sel_cfg; ///< SDIO device PADs mode pull selection
    sdemmc_w_sdio_device_drive_current_t   drive_current; ///< Drive current
} sdemmc_w_extended_cfg_t;

/** SDMMC extended callback arguments structure */
typedef struct st_sdemmc_w_transfer_result
{
    uint32_t              sdio_blk_or_byte; ///< This bit indicates current transaction is Block(1)/Byte(0)
    uint32_t              sdio_blk_size;    ///< The block size programmed by the SD host
    uint32_t              sdio_blk_count;   ///< The block count transferred from/to the SD host
} sdemmc_w_transfer_result_t;

/** SDMMC instance control block.  This is private to the FSP and should not be used or modified by the application. */
typedef struct st_sdemmc_w_instance_ctrl
{
    uint32_t                open;                   ///< Indicates whether the open() API has been successfully called.
    sdmmc_cfg_t const     * p_cfg;                  ///< Pointer to instance configuration
    sdmmc_device_t          device;                 ///< Information of the media device used
    bool                    sector_addressing;      ///< Whether or not use sector addressing in transfer
    bool                    transfer_in_progress;   ///< Whether or not transfer is in progress
    bool                    initialized;            ///< Whether or not driver is initialized
    SDIO_Type             * p_reg;                  ///< Base SDIO register for this channel
    SDEMMC_Type           * p_reg_mmc;              ///< Base SD/eMMC register for this channel
    volatile sdemmc_w_event_t sdemmc_w_event;             ///< Events of SDEMMC_W
    sdemmc_w_transfer_result_t result;              ///< Extended callback arguments

    void (* p_callback)(sdmmc_callback_args_t *);   ///< Pointer to callback
    sdmmc_callback_args_t * p_callback_memory;      ///< Pointer to optional callback argument memory
    void * p_context;              ///< Pointer to context to be passed into callback function
} sdemmc_w_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const sdmmc_api_t g_sdmmc_on_sdemmc_w;

/** @endcond */

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/

fsp_err_t R_SDEMMC_W_Open(sdmmc_ctrl_t * const p_api_ctrl, sdmmc_cfg_t const * const p_cfg);
fsp_err_t R_SDEMMC_W_MediaInit(sdmmc_ctrl_t * const p_api_ctrl, sdmmc_device_t * const p_device);
fsp_err_t R_SDEMMC_W_Read(sdmmc_ctrl_t * const p_api_ctrl,
                        uint8_t * const      p_dest,
                        uint32_t const       start_sector,
                        uint32_t const       sector_count);
fsp_err_t R_SDEMMC_W_Write(sdmmc_ctrl_t * const  p_api_ctrl,
                         uint8_t const * const p_source,
                         uint32_t const        start_sector,
                         uint32_t const        sector_count);
fsp_err_t R_SDEMMC_W_ReadIo(sdmmc_ctrl_t * const p_api_ctrl,
                          uint8_t * const      p_data,
                          uint32_t const       function,
                          uint32_t const       address);
fsp_err_t R_SDEMMC_W_WriteIo(sdmmc_ctrl_t * const        p_api_ctrl,
                           uint8_t * const             p_data,
                           uint32_t const              function,
                           uint32_t const              address,
                           sdmmc_io_write_mode_t const read_after_write);
fsp_err_t R_SDEMMC_W_ReadIoExt(sdmmc_ctrl_t * const     p_api_ctrl,
                             uint8_t * const          p_dest,
                             uint32_t const           function,
                             uint32_t const           address,
                             uint32_t * const         count,
                             sdmmc_io_transfer_mode_t transfer_mode,
                             sdmmc_io_address_mode_t  address_mode);
fsp_err_t R_SDEMMC_W_WriteIoExt(sdmmc_ctrl_t * const     p_api_ctrl,
                              uint8_t const * const    p_source,
                              uint32_t const           function,
                              uint32_t const           address,
                              uint32_t const           count,
                              sdmmc_io_transfer_mode_t transfer_mode,
                              sdmmc_io_address_mode_t  address_mode);
fsp_err_t R_SDEMMC_W_IoIntEnable(sdmmc_ctrl_t * const p_api_ctrl, bool enable);
fsp_err_t R_SDEMMC_W_StatusGet(sdmmc_ctrl_t * const p_api_ctrl, sdmmc_status_t * const p_status);
fsp_err_t R_SDEMMC_W_Erase(sdmmc_ctrl_t * const p_api_ctrl, uint32_t const start_sector, uint32_t const sector_count);
fsp_err_t R_SDEMMC_W_CallbackSet(sdmmc_ctrl_t * const          p_api_ctrl,
                               void (                      * p_callback)(sdmmc_callback_args_t *),
                               void * const            p_context,
                               sdmmc_callback_args_t * const p_callback_memory);
fsp_err_t R_SDEMMC_W_Close(sdmmc_ctrl_t * const p_api_ctrl);
fsp_err_t R_SDEMMC_W_ResultGet(sdmmc_ctrl_t * const p_api_ctrl, sdemmc_w_transfer_result_t * p_result);

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif /* R_SDEMMC_W_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup SDEMMC_W)
 **********************************************************************************************************************/
