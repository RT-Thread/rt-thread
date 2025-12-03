/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_sdhi.h"
#include "r_sdhi_private.h"
#include "r_sdhi_cfg.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** "SDHI" in ASCII, used to determine if channel is open. */
#define SDHI_PRV_OPEN            (0x53444849U)

/* Create a bitmask of access errors. */
#define SDHI_PRV_CARD_CMD_ERR    (1U << 16) // Command error
#define SDHI_PRV_CARD_CRC_ERR    (1U << 17) // CRC error
#define SDHI_PRV_CARD_END_ERR    (1U << 18) // End bit error
#define SDHI_PRV_CARD_DTO        (1U << 19) // Data Timeout
#define SDHI_PRV_CARD_ILW        (1U << 20) // Illegal write address
#define SDHI_PRV_CARD_ILR        (1U << 21) // Illegal read address
#define SDHI_PRV_CARD_RSPT       (1U << 22) // Response timeout
#define SDHI_PRV_CARD_ILA_ERR    (1U << 31) // Illegal access

#define SDHI_PRV_ACCESS_ERROR_MASK                                                               \
    (SDHI_PRV_CARD_CMD_ERR | SDHI_PRV_CARD_CRC_ERR | SDHI_PRV_CARD_END_ERR | SDHI_PRV_CARD_DTO | \
     SDHI_PRV_CARD_ILW | SDHI_PRV_CARD_ILR | SDHI_PRV_CARD_RSPT | SDHI_PRV_CARD_ILA_ERR)

/* The clock register can be accessed 8 SD clock cycles after the last command completes. */

/* SD_INFO1 */
#define SDHI_PRV_SDHI_INFO1_RESPONSE_END                   (1U << 0)  // Response End
#define SDHI_PRV_SDHI_INFO1_ACCESS_END                     (1U << 2)  // Access End
#define SDHI_PRV_SDHI_INFO1_CARD_REMOVED                   (1U << 3)  // Card Removed
#define SDHI_PRV_SDHI_INFO1_CARD_INSERTED                  (1U << 4)  // Card Inserted
#define SDHI_PRV_SDHI_INFO1_CARD_DAT3_REMOVED              (1U << 8)  // Card Removed
#define SDHI_PRV_SDHI_INFO1_CARD_DAT3_INSERTED             (1U << 9)  // Card Inserted
#define SDHI_PRV_SDHI_INFO2_CARD_CMD_ERR                   (1U << 0)  // Command error
#define SDHI_PRV_SDHI_INFO2_CARD_CRC_ERR                   (1U << 1)  // CRC error
#define SDHI_PRV_SDHI_INFO2_CARD_END_ERR                   (1U << 2)  // End bit error
#define SDHI_PRV_SDHI_INFO2_CARD_DTO                       (1U << 3)  // Data Timeout
#define SDHI_PRV_SDHI_INFO2_CARD_ILW                       (1U << 4)  // Illegal write address
#define SDHI_PRV_SDHI_INFO2_CARD_ILR                       (1U << 5)  // Illegal read address
#define SDHI_PRV_SDHI_INFO2_CARD_RSPT                      (1U << 6)  // Response timeout
#define SDHI_PRV_SDHI_INFO2_CARD_BRE                       (1U << 8)  // Buffer read enable
#define SDHI_PRV_SDHI_INFO2_CARD_BWE                       (1U << 9)  // Buffer write enable
#define SDHI_PRV_SDHI_INFO2_CARD_ILA_ERR                   (1U << 15) // Illegal access

#define SDHI_PRV_SDHI_INFO2_MASK                                                                               \
    ((SDHI_PRV_SDHI_INFO2_CARD_CMD_ERR | SDHI_PRV_SDHI_INFO2_CARD_CRC_ERR | SDHI_PRV_SDHI_INFO2_CARD_END_ERR | \
      SDHI_PRV_SDHI_INFO2_CARD_DTO | SDHI_PRV_SDHI_INFO2_CARD_ILW | SDHI_PRV_SDHI_INFO2_CARD_ILR |             \
      SDHI_PRV_SDHI_INFO2_CARD_BRE |                                                                           \
      SDHI_PRV_SDHI_INFO2_CARD_BWE |                                                                           \
      SDHI_PRV_SDHI_INFO2_CARD_RSPT | SDHI_PRV_SDHI_INFO2_CARD_ILA_ERR))

#define SDHI_PRV_SDHI_INFO1_ACCESS_MASK                    ((SDHI_PRV_SDHI_INFO1_RESPONSE_END | \
                                                             SDHI_PRV_SDHI_INFO1_ACCESS_END))
#define SDHI_PRV_SDHI_INFO1_CARD_MASK                      ((SDHI_PRV_SDHI_INFO1_CARD_REMOVED |      \
                                                             SDHI_PRV_SDHI_INFO1_CARD_INSERTED |     \
                                                             SDHI_PRV_SDHI_INFO1_CARD_DAT3_REMOVED | \
                                                             SDHI_PRV_SDHI_INFO1_CARD_DAT3_INSERTED))
#define SDHI_PRV_SDHI_INFO1_CARD_REMOVED_MASK              ((SDHI_PRV_SDHI_INFO1_CARD_REMOVED | \
                                                             SDHI_PRV_SDHI_INFO1_CARD_DAT3_REMOVED))
#define SDHI_PRV_SDHI_INFO1_CARD_INSERTED_MASK             ((SDHI_PRV_SDHI_INFO1_CARD_INSERTED | \
                                                             SDHI_PRV_SDHI_INFO1_CARD_DAT3_INSERTED))

/* Clear all masks to enable interrupts by all sources.
 * Do not set BREM or BWEM when using DMA/DTC. This driver always uses DMA or DTC. */
#define SDHI_PRV_SDHI_INFO2_MASK_CMD_SEND                  (0x00007C80U)

/* The relationship of the SD Clock Control Register SD_CLK_CTRL CLKSEL to the division of the source PCLK
 * b7            b0
 * 1 1 1 1 1 1 1 1: PCLK
 * 0 0 0 0 0 0 0 0: PCLK/2
 * 0 0 0 0 0 0 0 1: PCLK/4
 * 0 0 0 0 0 0 1 0: PCLK/8
 * 0 0 0 0 0 1 0 0: PCLK/16
 * 0 0 0 0 1 0 0 0: PCLK/32
 * 0 0 0 1 0 0 0 0: PCLK/64
 * 0 0 1 0 0 0 0 0: PCLK/128
 * 0 1 0 0 0 0 0 0: PCLK/256
 * 1 0 0 0 0 0 0 0: PCLK/512.
 * Other settings are prohibited.
 */
#define SDHI_PRV_MAX_CLOCK_DIVISION_SHIFT                  (9U) /* 512 (2^9) is max clock division supported */

#define SDHI_PRV_CLK_CTRL_DIV_INVALID                      (0xFFU)

/* Delay up to 250 ms per sector before timing out waiting for response or response timeout flag. */

/* Delay up to 10 ms before timing out waiting for response or response timeout flag. */
#define SDHI_PRV_RESPONSE_TIMEOUT_US                       (10000U)

/* Delay up to 5 seconds before timing out waiting for busy after updating bus width or high speed status for eMMC. */
#define SDHI_PRV_BUSY_TIMEOUT_US                           (5000000U)

/* Delay up to 500 ms before timing out waiting for data or data timeout flag. */
#define SDHI_PRV_DATA_TIMEOUT_US                           (500000U)

/* Delay up to 100 ms before timing out waiting for access end flag after receiving data during initialization. */
#define SDHI_PRV_ACCESS_TIMEOUT_US                         (100000U)

/* 400 kHz maximum clock required for initialization. */
#define SDHI_PRV_INIT_MAX_CLOCK_RATE_HZ                    (400000U)
#define SDHI_PRV_BITS_PER_COMMAD                           (48U)
#define SDHI_PRV_BITS_PER_RESPONSE                         (48U)
#define SDHI_PRV_CLOCKS_BETWEEN_COMMANDS                   (8U)
#define SDHI_PRV_MIN_CYCLES_PER_COMMAND_RESPONSE           ((SDHI_PRV_BITS_PER_COMMAD +    \
                                                             SDHI_PRV_BITS_PER_RESPONSE) + \
                                                            SDHI_PRV_CLOCKS_BETWEEN_COMMANDS)
#define SDHI_PRV_INIT_ONE_SECOND_TIMEOUT_ITERATIONS        (SDHI_PRV_INIT_MAX_CLOCK_RATE_HZ / \
                                                            SDHI_PRV_MIN_CYCLES_PER_COMMAND_RESPONSE)

#define SDHI_PRV_CSD_REG_CCC_CLASS_10_BIT                  ((1U << 10)) // CCC_CLASS bit is set if the card supports high speed

/* Startup delay in milliseconds. */

#define SDHI_PRV_SD_OPTION_DEFAULT                         (0x40E0U)
#define SDHI_PRV_SD_OPTION_WIDTH8_BIT                      (13)

#define SDHI_PRV_BUS_WIDTH_1_BIT                           (4U)

#define SDHI_PRV_SD_INFO2_MASK_BREM_BWEM_MASK              (0x300U)
#define SDHI_PRV_EMMC_BUS_WIDTH_INDEX                      (183U)
#define SDHI_PRV_BYTES_PER_KILOBYTE                        (1024)
#define SDHI_PRV_SECTOR_COUNT_IN_EXT_CSD                   (0xFFFU)
#define SDHI_PRV_SD_CLK_CTRL_DEFAULT                       (0x20U)

#define SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_MASK           (0x4080)
#define SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_VAL            (0x80)
#define SDHI_PRV_SD_CLK_CTRLEN_TIMEOUT                     (8U * 512U)
#define SDHI_PRV_SD_INFO1_MASK_MASK_ALL                    (0x31DU)
#define SDHI_PRV_SD_INFO1_MASK_CD_ENABLE                   (0x305U)
#define SDHI_PRV_SD_STOP_SD_SECCNT_ENABLE                  (0x100U)
#define SDHI_PRV_SD_DMAEN_DMAEN_SET                        (0x2U)

#define SDHI_PRV_SDHI_PRV_SD_CLK_CTRL_CLKCTRLEN_MASK       (1U << 9)
#define SDHI_PRV_SDHI_PRV_SD_CLK_CTRL_CLKEN_MASK           (1U << 8)
#define SDHI_PRV_SDHI_PRV_SD_CLK_AUTO_CLOCK_ENABLE_MASK    (0x300U)

#define SDHI_PRV_ACCESS_BIT                                (2U)
#define SDHI_PRV_RESPONSE_BIT                              (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * sdhi_prv_ns_callback)(sdmmc_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile sdhi_prv_ns_callback)(sdmmc_callback_args_t * p_args);
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
#if SDHI_CFG_PARAM_CHECKING_ENABLE
static fsp_err_t r_sdhi_open_param_check(sdhi_instance_ctrl_t * p_ctrl, sdmmc_cfg_t const * const p_cfg);

#endif

#if SDHI_CFG_EMMC_SUPPORT_ENABLE
static fsp_err_t r_sdhi_emmc_check(sdhi_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_sdhi_csd_extended_get(sdhi_instance_ctrl_t * const p_ctrl, uint32_t rca, uint8_t * p_device_type);

#endif

#if SDHI_CFG_SD_SUPPORT_ENABLE
static fsp_err_t r_sdhi_sd_card_check(sdhi_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_sdhi_sd_high_speed(sdhi_instance_ctrl_t * const p_ctrl);

static void r_sdhi_write_protect_get(sdhi_instance_ctrl_t * const p_ctrl);

#endif

#if SDHI_CFG_SD_SUPPORT_ENABLE || SDHI_CFG_EMMC_SUPPORT_ENABLE
static fsp_err_t r_sdhi_clock_optimize(sdhi_instance_ctrl_t * const p_ctrl,
                                       uint32_t                     rca,
                                       sdmmc_priv_csd_reg_t * const p_csd_reg);

static fsp_err_t r_sdhi_csd_save(sdhi_instance_ctrl_t * const p_ctrl,
                                 uint32_t                     rca,
                                 sdmmc_priv_csd_reg_t * const p_csd_reg);

static fsp_err_t r_sdhi_read_and_block(sdhi_instance_ctrl_t * const p_ctrl,
                                       uint32_t                     command,
                                       uint32_t                     argument,
                                       uint32_t                     byte_count);

static fsp_err_t r_sdhi_bus_width_set(sdhi_instance_ctrl_t * const p_ctrl, uint32_t rca);

#endif

static fsp_err_t r_sdhi_erase_error_check(sdhi_instance_ctrl_t * const p_ctrl,
                                          uint32_t const               start_sector,
                                          uint32_t const               sector_count);

static fsp_err_t r_sdhi_common_error_check(sdhi_instance_ctrl_t * const p_ctrl);

static void r_sdhi_irq_enable(IRQn_Type irq, uint8_t priority, void * p_context);
static void r_sdhi_irq_disable(IRQn_Type irq);

static void r_sdhi_access_irq_process(sdhi_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args);

static void r_sdhi_command_send_no_wait(sdhi_instance_ctrl_t * p_ctrl, uint32_t command, uint32_t argument);

static fsp_err_t r_sdhi_command_send(sdhi_instance_ctrl_t * p_ctrl, uint32_t command, uint32_t argument);

static fsp_err_t r_sdhi_max_clock_rate_set(sdhi_instance_ctrl_t * p_ctrl, uint32_t max_rate);

static fsp_err_t r_sdhi_wait_for_event(sdhi_instance_ctrl_t * const p_ctrl, uint32_t bit, uint32_t timeout);

static fsp_err_t r_sdhi_rca_get(sdhi_instance_ctrl_t * const p_ctrl, uint32_t * p_rca);

static fsp_err_t r_sdhi_hw_cfg(sdhi_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_sdhi_card_identify(sdhi_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_sdhi_bus_cfg(sdhi_instance_ctrl_t * const p_ctrl);

static fsp_err_t r_sdhi_wait_for_device(sdhi_instance_ctrl_t * const p_ctrl);

static void r_sdhi_read_write_common(sdhi_instance_ctrl_t * const p_ctrl,
                                     uint32_t                     sector_count,
                                     uint32_t                     sector_size,
                                     uint32_t                     command,
                                     uint32_t                     argument);

static fsp_err_t r_sdhi_transfer_read(sdhi_instance_ctrl_t * const p_ctrl,
                                      uint32_t                     block_count,
                                      uint32_t                     bytes,
                                      void                       * p_data);

static fsp_err_t r_sdhi_transfer_write(sdhi_instance_ctrl_t * const p_ctrl,
                                       uint32_t                     block_count,
                                       uint32_t                     bytes,
                                       const uint8_t              * p_data);

static void r_sdhi_transfer_end(sdhi_instance_ctrl_t * const p_ctrl);

static void r_sdhi_call_callback(sdhi_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args);

void r_sdhi_transfer_callback(sdhi_instance_ctrl_t * p_ctrl);

void sdhimmc_accs_isr(void);

void sdhimmc_card_isr(void);

void sdhimmc_dma_req_isr(void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/** SDMMC function pointers   */
const sdmmc_api_t g_sdmmc_on_sdhi =
{
    .open        = R_SDHI_Open,
    .mediaInit   = R_SDHI_MediaInit,
    .read        = R_SDHI_Read,
    .write       = R_SDHI_Write,
    .readIo      = R_SDHI_ReadIo,
    .writeIo     = R_SDHI_WriteIo,
    .readIoExt   = R_SDHI_ReadIoExt,
    .writeIoExt  = R_SDHI_WriteIoExt,
    .ioIntEnable = R_SDHI_IoIntEnable,
    .statusGet   = R_SDHI_StatusGet,
    .erase       = R_SDHI_Erase,
    .callbackSet = R_SDHI_CallbackSet,
    .close       = R_SDHI_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup SDHI
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Opens the driver.  Resets SDHI, and enables card detection interrupts if card detection is enabled.
 * @ref R_SDHI_MediaInit must be called after this function before any other functions can be used.
 *
 * Implements @ref sdmmc_api_t::open().
 *
 * Example:
 * @snippet r_sdhi_example.c R_SDHI_Open
 *
 * @retval     FSP_SUCCESS                     Module is now open.
 * @retval     FSP_ERR_ASSERTION               Null Pointer or block size is not in the valid range of 1-512. Block size
 *                                             must be 512 bytes for SD cards and eMMC devices.
 * @retval     FSP_ERR_ALREADY_OPEN            Driver has already been opened with this instance of the control
 *                                             structure.
 * @retval     FSP_ERR_IRQ_BSP_DISABLED        Access interrupt is not enabled.
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  Requested channel does not exist on this MCU.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_Open (sdmmc_ctrl_t * const p_api_ctrl, sdmmc_cfg_t const * const p_cfg)
{
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDHI_CFG_PARAM_CHECKING_ENABLE
    err = r_sdhi_open_param_check(p_ctrl, p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    /* Open the transfer driver. Clear the transfer length in case the transfer_info_t structure is reused and the
     * length was copied to the upper 8 bits for block mode. Configurations are updated before it is used. */
    p_cfg->p_lower_lvl_transfer->p_cfg->p_info->transfer_settings_word = 0U;
    err = p_cfg->p_lower_lvl_transfer->p_api->open(p_cfg->p_lower_lvl_transfer->p_ctrl,
                                                   p_cfg->p_lower_lvl_transfer->p_cfg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Initialize control block. */
    memset(p_ctrl, 0, sizeof(*p_ctrl));
#if BSP_FEATURE_SDHI_VALID_CHANNEL_MASK > 1U
    p_ctrl->p_reg = p_cfg->channel ? R_SDHI1 : R_SDHI0;
#else
    p_ctrl->p_reg = R_SDHI0;
#endif
    p_ctrl->p_cfg = p_cfg;

    /* Clear module stop bit (turn module on). */
    R_BSP_MODULE_START(FSP_IP_SDHIMMC, p_cfg->channel);

    /* Reset stale interrupt flags */
    p_ctrl->p_reg->SD_INFO1 = 0U;

    /* Reset SDHI. */
    p_ctrl->p_reg->SOFT_RST = 0x0U;
    p_ctrl->p_reg->SOFT_RST = 0x1U;

    /* Configure card detection. */
    if (SDMMC_CARD_DETECT_CD == p_ctrl->p_cfg->card_detect)
    {
        p_ctrl->p_reg->SD_INFO1_MASK = SDHI_PRV_SD_INFO1_MASK_CD_ENABLE;
    }
    else
    {
        p_ctrl->p_reg->SD_INFO1_MASK = SDHI_PRV_SD_INFO1_MASK_MASK_ALL;
    }

    /* Set callback and context pointers, if configured */
    p_ctrl->p_callback        = p_cfg->p_callback;
    p_ctrl->p_context         = p_cfg->p_context;
    p_ctrl->p_callback_memory = NULL;

    /* Configure and enable interrupts. */
    R_BSP_IrqCfgEnable(p_cfg->access_irq, p_cfg->access_ipl, p_ctrl);
    r_sdhi_irq_enable(p_cfg->card_irq, p_cfg->card_ipl, p_ctrl);
    r_sdhi_irq_enable(p_cfg->dma_req_irq, p_cfg->dma_req_ipl, p_ctrl);

    p_ctrl->initialized = false;
    p_ctrl->open        = SDHI_PRV_OPEN;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes the SDHI hardware and completes identification and configuration for the SD or eMMC device.  This
 * procedure requires several sequential commands.  This function blocks until all identification and configuration
 * commands are complete.
 *
 * Implements @ref sdmmc_api_t::mediaInit().
 *
 * Example:
 * @snippet r_sdhi_example.c R_SDHI_MediaInit
 *
 * @retval     FSP_SUCCESS               Module is now ready for read/write access.
 * @retval     FSP_ERR_ASSERTION         Null Pointer or block size is not in the valid range of 1-512. Block size must
 *                                       be 512 bytes for SD cards and eMMC devices.
 * @retval     FSP_ERR_NOT_OPEN          Driver has not been initialized.
 * @retval     FSP_ERR_CARD_INIT_FAILED  Device was not identified as an SD card or eMMC device.
 * @retval     FSP_ERR_RESPONSE          Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT           Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY       Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_MediaInit (sdmmc_ctrl_t * const p_api_ctrl, sdmmc_device_t * const p_device)
{
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDHI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SDHI_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Device is not initialized until this function completes. */
    p_ctrl->initialized = false;

    /* Configure SDHI peripheral. */
    err = r_sdhi_hw_cfg(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Perform the identification procedure for SD card or eMMC device. */
    err = r_sdhi_card_identify(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Configure bus clock, block size, and bus width. */
    err = r_sdhi_bus_cfg(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check to see if the card is write protected (SD cards only). */
#if SDHI_CFG_SD_SUPPORT_ENABLE
    r_sdhi_write_protect_get(p_ctrl);
#endif

    /* Return device information to user. */
    p_ctrl->device.sector_size_bytes = p_ctrl->p_cfg->block_size;
    if (NULL != p_device)
    {
        *p_device = p_ctrl->device;
    }

    p_ctrl->initialized = true;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Reads data from an SD or eMMC device.  Up to 0x10000 sectors can be read at a time. Implements @ref sdmmc_api_t::read().
 *
 * A callback with the event SDMMC_EVENT_TRANSFER_COMPLETE is called when the read data is available.
 *
 * Example:
 * @snippet r_sdhi_example.c R_SDHI_Read
 *
 * @retval     FSP_SUCCESS                   Data read successfully.
 * @retval     FSP_ERR_ASSERTION             NULL pointer.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_Read (sdmmc_ctrl_t * const p_api_ctrl,
                       uint8_t * const      p_dest,
                       uint32_t const       start_sector,
                       uint32_t const       sector_count)
{
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDHI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_dest);
    FSP_ASSERT(sector_count <= (UINT16_MAX + 1));
#endif
    err = r_sdhi_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Configure the transfer interface for reading. */
    err = r_sdhi_transfer_read(p_ctrl, sector_count, p_ctrl->p_cfg->block_size, p_dest);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    uint32_t command  = 0U;
    uint32_t argument = start_sector;
    if (!p_ctrl->sector_addressing)
    {
        /* Standard capacity SD cards and some eMMC devices use byte addressing. */
        argument *= p_ctrl->p_cfg->block_size;
    }

    if (sector_count > 1U)
    {
        command = SDHI_PRV_CMD_READ_MULTIPLE_BLOCK;
    }
    else
    {
        command = SDHI_PRV_CMD_READ_SINGLE_BLOCK;
    }

    r_sdhi_read_write_common(p_ctrl, sector_count, p_ctrl->p_cfg->block_size, command, argument);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Writes data to an SD or eMMC device. Up to 0x10000 sectors can be written at a time. Implements @ref sdmmc_api_t::write().
 *
 * A callback with the event SDMMC_EVENT_TRANSFER_COMPLETE is called when the all data has been written and the device
 * is no longer holding DAT0 low to indicate it is busy.
 *
 * Example:
 * @snippet r_sdhi_example.c R_SDHI_Write
 *
 * @retval     FSP_SUCCESS                   Card write finished successfully.
 * @retval     FSP_ERR_ASSERTION             Handle or Source address is NULL.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 * @retval     FSP_ERR_CARD_WRITE_PROTECTED  SD card is Write Protected.
 * @retval     FSP_ERR_WRITE_FAILED          Write operation failed.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_Write (sdmmc_ctrl_t * const  p_api_ctrl,
                        uint8_t const * const p_source,
                        uint32_t const        start_sector,
                        uint32_t const        sector_count)
{
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;

#if SDHI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_source);
    FSP_ASSERT(sector_count <= (UINT16_MAX + 1));
#endif
    err = r_sdhi_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Check for write protection */
    FSP_ERROR_RETURN(!p_ctrl->device.write_protected, FSP_ERR_CARD_WRITE_PROTECTED);

    /* Configure the transfer interface for writing. */
    err = r_sdhi_transfer_write(p_ctrl, sector_count, p_ctrl->p_cfg->block_size, p_source);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, FSP_ERR_WRITE_FAILED);

    /* Call SDMMC protocol write function */
    uint32_t command  = 0U;
    uint32_t argument = start_sector;
    if (!p_ctrl->sector_addressing)
    {
        /* Standard capacity SD cards and some eMMC devices use byte addressing. */
        argument *= p_ctrl->p_cfg->block_size;
    }

    if (sector_count > 1U)
    {
        command = SDHI_PRV_CMD_WRITE_MULTIPLE_BLOCK;
    }
    else
    {
        command = SDHI_PRV_CMD_WRITE_SINGLE_BLOCK;
    }

    /* Casting to uint16_t safe because block size verified in R_SDHI_Open */
    r_sdhi_read_write_common(p_ctrl, sector_count, p_ctrl->p_cfg->block_size, command, argument);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * The Read function reads a one byte register from an SDIO card.  Implements @ref sdmmc_api_t::readIo().
 *
 * @note This function is not supported.
 *
 * @retval     FSP_ERR_UNSUPPORTED           SDIO is not supported.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_ReadIo (sdmmc_ctrl_t * const p_api_ctrl,
                         uint8_t * const      p_data,
                         uint32_t const       function,
                         uint32_t const       address)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_data);
    FSP_PARAMETER_NOT_USED(function);
    FSP_PARAMETER_NOT_USED(address);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Writes a one byte register to an SDIO card.  Implements @ref sdmmc_api_t::writeIo().
 *
 * @note This function is not supported.
 *
 * @retval     FSP_ERR_UNSUPPORTED           SDIO is not supported.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_WriteIo (sdmmc_ctrl_t * const        p_api_ctrl,
                          uint8_t * const             p_data,
                          uint32_t const              function,
                          uint32_t const              address,
                          sdmmc_io_write_mode_t const read_after_write)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_data);
    FSP_PARAMETER_NOT_USED(function);
    FSP_PARAMETER_NOT_USED(address);
    FSP_PARAMETER_NOT_USED(read_after_write);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Reads data from an SDIO card function.  Implements @ref sdmmc_api_t::readIoExt().
 *
 * @note This function is not supported.
 *
 * @retval     FSP_ERR_UNSUPPORTED           SDIO is not supported.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_ReadIoExt (sdmmc_ctrl_t * const     p_api_ctrl,
                            uint8_t * const          p_dest,
                            uint32_t const           function,
                            uint32_t const           address,
                            uint32_t * const         count,
                            sdmmc_io_transfer_mode_t transfer_mode,
                            sdmmc_io_address_mode_t  address_mode)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(function);
    FSP_PARAMETER_NOT_USED(address);
    FSP_PARAMETER_NOT_USED(count);
    FSP_PARAMETER_NOT_USED(transfer_mode);
    FSP_PARAMETER_NOT_USED(address_mode);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Writes data to an SDIO card function.  Implements @ref sdmmc_api_t::writeIoExt().
 *
 * @note This function is not supported.
 *
 * @retval     FSP_ERR_UNSUPPORTED           SDIO is not supported.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_WriteIoExt (sdmmc_ctrl_t * const     p_api_ctrl,
                             uint8_t const * const    p_source,
                             uint32_t const           function,
                             uint32_t const           address,
                             uint32_t const           count,
                             sdmmc_io_transfer_mode_t transfer_mode,
                             sdmmc_io_address_mode_t  address_mode)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(p_source);
    FSP_PARAMETER_NOT_USED(function);
    FSP_PARAMETER_NOT_USED(address);
    FSP_PARAMETER_NOT_USED(count);
    FSP_PARAMETER_NOT_USED(transfer_mode);
    FSP_PARAMETER_NOT_USED(address_mode);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Enables or disables the SDIO Interrupt.  Implements @ref sdmmc_api_t::ioIntEnable().
 *
 * @note This function is not supported.
 *
 * @retval     FSP_ERR_UNSUPPORTED  SDIO is not supported.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_IoIntEnable (sdmmc_ctrl_t * const p_api_ctrl, bool enable)
{
    FSP_PARAMETER_NOT_USED(p_api_ctrl);
    FSP_PARAMETER_NOT_USED(enable);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Provides driver status.  Implements @ref sdmmc_api_t::statusGet().
 *
 * @retval     FSP_SUCCESS        Status stored in p_status.
 * @retval     FSP_ERR_ASSERTION  NULL pointer.
 * @retval     FSP_ERR_NOT_OPEN   Driver has not been initialized.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_StatusGet (sdmmc_ctrl_t * const p_api_ctrl, sdmmc_status_t * const p_status)
{
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) p_api_ctrl;

#if SDHI_CFG_PARAM_CHECKING_ENABLE

    /* Check pointers for NULL values */
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);

    FSP_ERROR_RETURN(SDHI_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Check CD pin. */
    if (SDMMC_CARD_DETECT_CD == p_ctrl->p_cfg->card_detect)
    {
        p_status->card_inserted = p_ctrl->p_reg->SD_INFO1_b.SDCDMON;
    }
    else
    {
        p_status->card_inserted = true;
    }

    /* Whether or not the media is initialized. */
    p_status->initialized = p_ctrl->initialized;

    /* Check if the card is busy. */
    p_status->transfer_in_progress =
        (SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_VAL !=
         (p_ctrl->p_reg->SD_INFO2 & SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_MASK));

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erases sectors of an SD card or eMMC device.  Implements @ref sdmmc_api_t::erase().
 *
 * This function blocks until the erase command is sent.  Poll the status to determine when erase is complete.
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             A required pointer is NULL or an argument is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_CARD_WRITE_PROTECTED  SD card is Write Protected.
 * @retval     FSP_ERR_RESPONSE              Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT               Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY           Device is holding DAT0 low (device is busy) or another operation is
 *                                           ongoing.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_Erase (sdmmc_ctrl_t * const p_api_ctrl, uint32_t const start_sector, uint32_t const sector_count)
{
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) p_api_ctrl;

    fsp_err_t err = FSP_SUCCESS;
    uint32_t  start_address;
    uint32_t  end_address;
    uint32_t  start_command;
    uint32_t  end_command;
    uint32_t  argument;

    err = r_sdhi_erase_error_check(p_ctrl, start_sector, sector_count);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /*  SDHC, SDXC and eMMC high capacity media use block addressing. */
    if (true == p_ctrl->sector_addressing)
    {
        start_address = start_sector;
        end_address   = ((start_sector + sector_count) - 1);
    }
    else
    {
        start_address = (start_sector * p_ctrl->p_cfg->block_size);
        end_address   = ((start_sector + sector_count) * p_ctrl->p_cfg->block_size) - 1U;
    }

#if SDHI_CFG_EMMC_SUPPORT_ENABLE
    if (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type)
    {
        start_command = SDHI_PRV_CMD_TAG_ERASE_GROUP_START;
        end_command   = SDHI_PRV_CMD_TAG_ERASE_GROUP_END;
        argument      = SDHI_PRV_EMMC_ERASE_ARGUMENT_TRIM;
    }
    else
#endif
    {
        start_command = SDHI_PRV_CMD_ERASE_WR_BLK_START;
        end_command   = SDHI_PRV_CMD_ERASE_WR_BLK_END;
        argument      = 0U;            // Argument unused for SD
    }

    /* Send command to set start erase address (CMD35 for eMMC, CMD32 for SD). */
    err = r_sdhi_command_send(p_ctrl, start_command, start_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Send command to set end erase address (CMD36 for eMMC, CMD33 for SD). */
    err = r_sdhi_command_send(p_ctrl, end_command, end_address);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Send erase command (CMD38). */
    r_sdhi_command_send_no_wait(p_ctrl, SDHI_PRV_CMD_ERASE, argument);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 * Implements @ref sdmmc_api_t::callbackSet.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            A required pointer is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_CallbackSet (sdmmc_ctrl_t * const          p_api_ctrl,
                              void (                      * p_callback)(sdmmc_callback_args_t *),
                              void * const                  p_context,
                              sdmmc_callback_args_t * const p_callback_memory)
{
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) p_api_ctrl;

#if SDHI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(SDHI_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Get security state of p_callback */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if SDHI_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure */
    sdmmc_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                        CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context */
#if BSP_TZ_SECURE_BUILD
    p_ctrl->p_callback = callback_is_secure ? p_callback :
                         (void (*)(sdmmc_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_ctrl->p_callback = p_callback;
#endif
    p_ctrl->p_context         = p_context;
    p_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Closes an open SD/MMC device.  Implements @ref sdmmc_api_t::close().
 *
 * @retval     FSP_SUCCESS        Successful close.
 * @retval     FSP_ERR_ASSERTION  The parameter p_ctrl is NULL.
 * @retval     FSP_ERR_NOT_OPEN   Driver has not been initialized.
 **********************************************************************************************************************/
fsp_err_t R_SDHI_Close (sdmmc_ctrl_t * const p_api_ctrl)
{
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) p_api_ctrl;

#if SDHI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);

    FSP_ERROR_RETURN(SDHI_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_ctrl->open = 0U;

    /* Disable SDHI interrupts. */
    r_sdhi_irq_disable(p_ctrl->p_cfg->access_irq);
    r_sdhi_irq_disable(p_ctrl->p_cfg->card_irq);

    /* Put the card in idle state (CMD0). */
    r_sdhi_command_send_no_wait(p_ctrl, SDHI_PRV_CMD_GO_IDLE_STATE, 0);

    /* Close the transfer driver. */
    p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->close(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl);

    /* Do not set the module stop bit since the CMD0 may not be complete yet. Do not wait for CMD0 to complete because
     * the card could be unplugged and waiting for the response timeout in this function is not desirable. */

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup SDMMC)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

#if SDHI_CFG_PARAM_CHECKING_ENABLE

/*******************************************************************************************************************//**
 * Parameter checking for the open function.
 *
 * @param[in]  p_ctrl                          Pointer to the instance control block.
 * @param[in]  p_cfg                           Pointer to the instance configuration structure.
 *
 * @retval     FSP_SUCCESS                     Parameters to open() are in the valid range.
 * @retval     FSP_ERR_ASSERTION               A required input pointer is NULL, or the block size is 0 or > 512 bytes.
 * @retval     FSP_ERR_ALREADY_OPEN            Driver has already been opened with this instance of the control
 *                                             structure.
 * @retval     FSP_ERR_IP_CHANNEL_NOT_PRESENT  Requested channel does not exist on this MCU.
 * @retval     FSP_ERR_IRQ_BSP_DISABLED        Access interrupt is not enabled.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_open_param_check (sdhi_instance_ctrl_t * p_ctrl, sdmmc_cfg_t const * const p_cfg)
{
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_lower_lvl_transfer);
    FSP_ERROR_RETURN(SDHI_PRV_OPEN != p_ctrl->open, FSP_ERR_ALREADY_OPEN);

    /* Verify the requested channel exists on the MCU. */
    FSP_ERROR_RETURN(0U != ((1U << p_cfg->channel) & BSP_FEATURE_SDHI_VALID_CHANNEL_MASK),
                     FSP_ERR_IP_CHANNEL_NOT_PRESENT);

    /* Some MCUs don't support card detection. */
 #if !BSP_FEATURE_SDHI_HAS_CARD_DETECTION
    FSP_ASSERT(SDMMC_CARD_DETECT_NONE == p_cfg->card_detect);
 #endif

    /* Some MCUs don't support 8-bit MMC. */
 #if !BSP_FEATURE_SDHI_SUPPORTS_8_BIT_MMC
    FSP_ASSERT(SDMMC_BUS_WIDTH_8_BITS != p_cfg->bus_width);
 #endif

    /* SD and eMMC cards only support block size of 512 bytes on the SDHI hardware. */
    FSP_ASSERT(SDHI_MAX_BLOCK_SIZE == p_cfg->block_size);

    /* Access interrupt is required. */
    FSP_ERROR_RETURN(p_cfg->access_irq >= 0, FSP_ERR_IRQ_BSP_DISABLED);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Parameter checking for erase.
 *
 * @param[in]  p_ctrl                        Pointer to the instance control block.
 * @param[in]  start_sector                  First sector to write
 * @param[in]  sector_count                  Number of sectors to write
 *
 * @retval     FSP_SUCCESS                   Erase operation requested.
 * @retval     FSP_ERR_ASSERTION             A required pointer is NULL or an argument is invalid.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 * @retval     FSP_ERR_CARD_WRITE_PROTECTED  SD card is Write Protected.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_erase_error_check (sdhi_instance_ctrl_t * const p_ctrl,
                                           uint32_t const               start_sector,
                                           uint32_t const               sector_count)
{
    fsp_err_t err = r_sdhi_common_error_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if SDHI_CFG_PARAM_CHECKING_ENABLE

    /* Check for valid sector count.  Must be a non-zero multiple of erase_sector_count. */

    FSP_ASSERT(0U != sector_count);
    FSP_ASSERT(0U == (sector_count % p_ctrl->device.erase_sector_count));

    /* Check for valid start sector.  Must be a multiple of erase_sector_count. */
    FSP_ASSERT(0U == (start_sector % p_ctrl->device.erase_sector_count));
#else
    FSP_PARAMETER_NOT_USED(start_sector);
    FSP_PARAMETER_NOT_USED(sector_count);
#endif

    /* Check for write protection */
    FSP_ERROR_RETURN(!p_ctrl->device.write_protected, FSP_ERR_CARD_WRITE_PROTECTED);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Parameter checking for runtime APIs.
 *
 * @param[in]  p_ctrl                        Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS                   Device is ready to be accessed.
 * @retval     FSP_ERR_ASSERTION             A required pointer is NULL.
 * @retval     FSP_ERR_NOT_OPEN              Driver has not been initialized.
 * @retval     FSP_ERR_CARD_NOT_INITIALIZED  Card was unplugged.
 * @retval     FSP_ERR_DEVICE_BUSY           Driver is busy with a previous operation.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_common_error_check (sdhi_instance_ctrl_t * const p_ctrl)
{
#if SDHI_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(SDHI_PRV_OPEN == p_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* To verify no command sequence is in progress in SDHI, verify SD_INFO2.CBSY is not set.  To verify the card has
     * completed the requested operation, verify SD_INFO2.SDD0MON is set. */
    FSP_ERROR_RETURN(SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_VAL ==
                     (p_ctrl->p_reg->SD_INFO2 & SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_MASK),
                     FSP_ERR_DEVICE_BUSY);

#if SDHI_CFG_SD_SUPPORT_ENABLE

    /* Verify the card has not been removed since the last card initialization. */
    FSP_ERROR_RETURN(p_ctrl->initialized, FSP_ERR_CARD_NOT_INITIALIZED);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Configures and enables an interrupt.
 *
 * @param[in]  irq             Interrupt number.
 * @param[in]  priority        NVIC priority of the interrupt
 * @param[in]  p_context       Pointer to data required in the ISR.
 **********************************************************************************************************************/
static void r_sdhi_irq_enable (IRQn_Type irq, uint8_t priority, void * p_context)
{
    if (irq >= 0)
    {
        R_BSP_IrqCfgEnable(irq, priority, p_context);
    }
}

/*******************************************************************************************************************//**
 * Disables an interrupt.
 *
 * @param[in]  irq             Interrupt to disable.
 **********************************************************************************************************************/
static void r_sdhi_irq_disable (IRQn_Type irq)
{
    if (irq >= 0)
    {
        /* Disables interrupts in the NVIC. */
        R_BSP_IrqDisable(irq);

        /* Clears the control block from the vector information array. */
        R_FSP_IsrContextSet(irq, NULL);
    }
}

/*******************************************************************************************************************//**
 * Stores access interrupt flags in the control block and calls the callback.
 *
 * @param[in]  p_ctrl          Pointer to the instance control block.
 * @param[in]  p_args          Pointer to SDMMC callback arguments.
 **********************************************************************************************************************/
static void r_sdhi_access_irq_process (sdhi_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args)
{
    uint32_t     info1;
    uint32_t     info2;
    sdhi_event_t flags;

    /* Clear stop register after access end. */
    p_ctrl->p_reg->SD_STOP_b.STP = 0U;

    /* Read interrupt flag registers. */
    info1 = p_ctrl->p_reg->SD_INFO1;
    info2 = p_ctrl->p_reg->SD_INFO2;

    /* Clear interrupt flags processed in this ISR. */
    info1 &= SDHI_PRV_SDHI_INFO1_ACCESS_MASK;
    info2 &= SDHI_PRV_SDHI_INFO2_MASK;
    p_ctrl->p_reg->SD_INFO1 = (~info1);
    p_ctrl->p_reg->SD_INFO2 = (~info2);

    /* Combine all flags in one 32 bit word. */
    flags.word = (info1 | (info2 << 16));

    if (flags.bit.response_end)
    {
        p_args->event |= SDMMC_EVENT_RESPONSE;

        /* Check the R1 response. */
        if (1U == p_ctrl->p_reg->SD_STOP_b.SEC)
        {
            /* Get the R1 response for multiple block read and write from SD_RSP54 since the response in SD_RSP10 may
             * have been overwritten by the response to CMD12. */
            p_args->response.status = p_ctrl->p_reg->SD_RSP54;
        }
        else
        {
            p_args->response.status = p_ctrl->p_reg->SD_RSP10;
        }

        if (SDHI_PRV_CMD_ERASE == p_ctrl->p_reg->SD_CMD)
        {
            /* Determine if erase is complete or not based on DAT0. Access interrupt is not required for erase. */
            if (SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_VAL ==
                (p_ctrl->p_reg->SD_INFO2 & SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_MASK))
            {
                p_args->event |= SDMMC_EVENT_ERASE_COMPLETE;
            }
            else
            {
                p_args->event |= SDMMC_EVENT_ERASE_BUSY;
            }
        }
        else
        {
            /* Enable the access interrupt. */
            /* Disable response end interrupt (set the bit) and enable access end interrupt (clear the bit). */
            uint32_t mask = p_ctrl->p_reg->SD_INFO1_MASK;
            mask &= (~SDHI_PRV_SDHI_INFO1_ACCESS_END);
            mask |= SDHI_PRV_SDHI_INFO1_RESPONSE_END;
            p_ctrl->p_reg->SD_INFO1_MASK = mask;
        }
    }

    /* Check for errors */
    if (flags.word & SDHI_PRV_ACCESS_ERROR_MASK)
    {
        flags.bit.event_error  = 1U;
        p_args->event         |= SDMMC_EVENT_TRANSFER_ERROR;
        p_ctrl->p_reg->SD_STOP = 1U;

        /* Disable the transfer and clear related variables since an error occurred. */
        r_sdhi_transfer_end(p_ctrl);
    }
    else
    {
        /* Check for access end */
        if (flags.bit.access_end)
        {
            /* All aligned transfers end here. Unaligned write transfers also end here. Unaligned read transfers end
             * in the transfer callback. */
            if (SDHI_TRANSFER_DIR_READ != p_ctrl->transfer_dir)
            {
                /* Disable the transfer and clear related variables since the transfer is complete. */
                r_sdhi_transfer_end(p_ctrl);
                p_args->event |= SDMMC_EVENT_TRANSFER_COMPLETE;
            }
        }
    }

    /* Combine all events for each command because this flag is polled in some functions. */
    p_ctrl->sdhi_event.word |= flags.word;
}

/*******************************************************************************************************************//**
 * Send a command to the SD or eMMC device.
 *
 * @param[in]  p_ctrl          Pointer to the instance control block.
 * @param[in]  command         Command to send.
 * @param[in]  argument        Argument to send with the command.
 **********************************************************************************************************************/
static void r_sdhi_command_send_no_wait (sdhi_instance_ctrl_t * p_ctrl, uint32_t command, uint32_t argument)
{
    /* Clear Status */
    p_ctrl->p_reg->SD_INFO1 = 0U;
    p_ctrl->p_reg->SD_INFO2 = 0U;
    p_ctrl->sdhi_event.word = 0U;

    /* Enable response end interrupt. */
    /* Disable access end interrupt and enable response end interrupt. */
    uint32_t mask = p_ctrl->p_reg->SD_INFO1_MASK;
    mask &= (~SDHI_PRV_SDHI_INFO1_RESPONSE_END);
    mask |= SDHI_PRV_SDHI_INFO1_ACCESS_END;
    p_ctrl->p_reg->SD_INFO1_MASK = mask;
    p_ctrl->p_reg->SD_INFO2_MASK = SDHI_PRV_SDHI_INFO2_MASK_CMD_SEND;

    /* Enable Clock */
    p_ctrl->p_reg->SD_CLK_CTRL |= SDHI_PRV_SDHI_PRV_SD_CLK_AUTO_CLOCK_ENABLE_MASK;

    /* Write argument, then command to the SDHI peripheral. */
    p_ctrl->p_reg->SD_ARG  = argument & UINT16_MAX;
    p_ctrl->p_reg->SD_ARG1 = argument >> 16;
    p_ctrl->p_reg->SD_CMD  = command;
}

/*******************************************************************************************************************//**
 * Send a command to the SD or eMMC device and wait for response
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 * @param[in]  command              Command to send.
 * @param[in]  argument             Argument to send with the command.
 *
 * @retval     FSP_SUCCESS          Command sent and response received, no errors in response.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_command_send (sdhi_instance_ctrl_t * p_ctrl, uint32_t command, uint32_t argument)
{
    /* Verify the device is not busy. */
    r_sdhi_wait_for_device(p_ctrl);

    /* Send the command. */
    r_sdhi_command_send_no_wait(p_ctrl, command, argument);

    /* Wait for end of response, error or timeout */
    return r_sdhi_wait_for_event(p_ctrl, SDHI_PRV_RESPONSE_BIT, SDHI_PRV_RESPONSE_TIMEOUT_US);
}

/*******************************************************************************************************************//**
 * Set the SD clock to a rate less than or equal to the requested maximum rate.
 *
 * @param[in]  p_ctrl                    Pointer to the instance control block.
 * @param[in]  max_rate                  Maximum SD clock rate to set
 *
 * @retval     FSP_SUCCESS               SD clock rate is less than or equal to the requested maximum rate.
 * @retval     FSP_ERR_CARD_INIT_FAILED  Timeout setting divider or operation is still too fast at maximum divider
 *                                       (unlikely).
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_max_clock_rate_set (sdhi_instance_ctrl_t * p_ctrl, uint32_t max_rate)
{
    uint32_t setting = SDHI_PRV_CLK_CTRL_DIV_INVALID;

    /* Get the runtime frequency of the source of the SD clock */
    uint32_t frequency = R_FSP_SystemClockHzGet(BSP_FEATURE_SDHI_CLOCK);

    /* Iterate over all possible divisors, starting with the smallest, until the resulting clock rate is less than
     * or equal to the requested maximum rate. */
    for (uint32_t divisor_shift = BSP_FEATURE_SDHI_MIN_CLOCK_DIVISION_SHIFT;
         divisor_shift <= SDHI_PRV_MAX_CLOCK_DIVISION_SHIFT;
         divisor_shift++)
    {
        if ((frequency >> divisor_shift) <= max_rate)
        {
            /* If the calculated frequency is less than or equal to the maximum supported by the device,
             * select this frequency. The register setting is the divisor value divided by 4, or 0xFF for no divider. */
            setting = divisor_shift ? ((1U << divisor_shift) >> 2U) : UINT8_MAX;

            /* Set the clock setting. */

            /* The clock register is accessible 8 SD clock counts after the last command completes.  Each register access
             * requires at least one PCLK count, so check the register up to 8 times the maximum PCLK divisor value (512). */
            uint32_t timeout = SDHI_PRV_SD_CLK_CTRLEN_TIMEOUT;

            while (timeout > 0U)
            {
                /* Do not write to clock control register until this bit is set. */
                if (p_ctrl->p_reg->SD_INFO2_b.SD_CLK_CTRLEN)
                {
                    /* Set the calculated divider and enable clock output to start the 74 clocks required before
                     * initialization. Do not change the automatic clock control setting. */
                    uint32_t clkctrlen = p_ctrl->p_reg->SD_CLK_CTRL & SDHI_PRV_SDHI_PRV_SD_CLK_CTRL_CLKCTRLEN_MASK;
                    p_ctrl->p_reg->SD_CLK_CTRL = setting | clkctrlen | SDHI_PRV_SDHI_PRV_SD_CLK_CTRL_CLKEN_MASK;
                    p_ctrl->device.clock_rate  = frequency >> divisor_shift;

                    return FSP_SUCCESS;
                }

                timeout--;
            }

            /* Valid setting already found, stop looking. */
            break;
        }
    }

    return FSP_ERR_CARD_INIT_FAILED;
}

/*******************************************************************************************************************//**
 * Initializes SD host interface hardware.
 *
 * @param[in]  p_ctrl                    Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS               Operation completed successfully.
 * @retval     FSP_ERR_CARD_INIT_FAILED  Timeout setting divider or operation is still too fast at maximum divider
 *                                       (unlikely).
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_hw_cfg (sdhi_instance_ctrl_t * const p_ctrl)
{
    /* Reset SDHI. */
    p_ctrl->p_reg->SOFT_RST = 0x0U;
    p_ctrl->p_reg->SOFT_RST = 0x1U;

    /* Execute software reset or check SD_INFO2.SD_CLK_CTRLEN prior to calling this function. */
    p_ctrl->p_reg->SD_CLK_CTRL = SDHI_PRV_SD_CLK_CTRL_DEFAULT; // Automatic clock control disabled.
    p_ctrl->p_reg->SDIO_MODE   = 0x00U;                        // SDIO not supported.
    p_ctrl->p_reg->SD_DMAEN    = 0x00U;                        // Not in DMA mode initially.
    p_ctrl->p_reg->SDIF_MODE   = 0x00U;                        // CRC check is valid.
    p_ctrl->p_reg->EXT_SWAP    = 0x00U;                        // Don't swap endianness

    /* Set the clock frequency to 400 kHz or less for identification. */
    fsp_err_t err = r_sdhi_max_clock_rate_set(p_ctrl, SDHI_PRV_INIT_MAX_CLOCK_RATE_HZ);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set initial bus width to one bit wide. */
    p_ctrl->p_reg->SD_OPTION = SDHI_PRV_SD_OPTION_DEFAULT |
                               (SDHI_PRV_BUS_WIDTH_1_BIT << SDHI_PRV_SD_OPTION_WIDTH8_BIT);

    /* The host shall supply at least 74 SD clocks to the SD card while keeping CMD line high.  Reference section
     * 6.4.1.1 "Power Up Time of Card" in the SD Physical Layer Specification Version 6.00. */
    R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MILLISECONDS);

    /* Automatic clock control can be enabled only after 74 SD/MMC clock cycles are output. See
     * "Automatic Control of SD/MMC Clock Output (SD/MMC)" in the SDHI section of the relevant hardware manual. */

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes driver and device.
 *
 * @param[in]  p_ctrl                    Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS               Operation completed successfully.
 * @retval     FSP_ERR_CARD_INIT_FAILED  Device could not be identified.
 * @retval     FSP_ERR_ASSERTION         Card detection configured but not supported.
 * @retval     FSP_ERR_RESPONSE          Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT           Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY       Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_card_identify (sdhi_instance_ctrl_t * const p_ctrl)
{
    /* For SD cards, follow the procedure in Figure 4-1 "SD Memory Card State Diagram (card identification mode" in
     * Physical Layer Simplified Specification Version 6.00. */

    /* For eMMC devices, follow the procedure in A.6.1 "Bus Initialization" in JEDEC Standard No. 84-B51A. */

    /* Put the card in idle state. */
    fsp_err_t err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_GO_IDLE_STATE, 0);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if SDHI_CFG_SD_SUPPORT_ENABLE || SDHI_CFG_EMMC_SUPPORT_ENABLE
 #if SDHI_CFG_SD_SUPPORT_ENABLE

    /* Check to see if the device is an SD memory card (CMD8 + ACMD41). */
    err = r_sdhi_sd_card_check(p_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    if (SDMMC_CARD_TYPE_SD != p_ctrl->device.card_type)
 #endif
    {
 #if SDHI_CFG_EMMC_SUPPORT_ENABLE

        /* If the device is not SD memory, check to see if it is an eMMC device (CMD1). */
        err = r_sdhi_emmc_check(p_ctrl);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #endif
        if ((sdmmc_card_type_t) UINT8_MAX == p_ctrl->device.card_type)
        {

            /* If the device is not identified as an SD memory card or eMMC, return an error. */
            return FSP_ERR_CARD_INIT_FAILED;
        }
    }

    /* Enter identification state (CMD2). */
    err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_ALL_SEND_CID, 0); /* send SD CMD2 */
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Initializes bus clock, block length, and bus width.
 *
 * @param[in]  p_ctrl                    Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS               Operation completed successfully.
 * @retval     FSP_ERR_CARD_INIT_FAILED  Operation failed.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY       Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_bus_cfg (sdhi_instance_ctrl_t * const p_ctrl)
{
    /* Get relative card address (CMD3). */
    uint32_t  rca;
    fsp_err_t err = r_sdhi_rca_get(p_ctrl, &rca);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if SDHI_CFG_SD_SUPPORT_ENABLE || SDHI_CFG_EMMC_SUPPORT_ENABLE

    /* Decode CSD register depending on version of card */
    sdmmc_priv_csd_reg_t csd_reg;
    err = r_sdhi_csd_save(p_ctrl, rca, &csd_reg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Switch to transfer state (CMD7). */
    err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_SEL_DES_CARD, rca << 16);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set clock to highest supported frequency. */
    err = r_sdhi_clock_optimize(p_ctrl, rca, &csd_reg);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set the block length (CMD16) to 512 bytes. */
    err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_SET_BLOCKLEN, p_ctrl->p_cfg->block_size);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Set bus width. */
    err = r_sdhi_bus_width_set(p_ctrl, rca);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read or write data.
 *
 * @param[in]  p_ctrl          Pointer to the instance control block.
 * @param[in]  sector_count    Number of sectors to read or write.
 * @param[in]  sector_size     Size of one sector in bytes.
 * @param[in]  command         Command number
 * @param[in]  argument        Argument
 **********************************************************************************************************************/
static void r_sdhi_read_write_common (sdhi_instance_ctrl_t * const p_ctrl,
                                      uint32_t                     sector_count,
                                      uint32_t                     sector_size,
                                      uint32_t                     command,
                                      uint32_t                     argument)
{
    /* Set the sector count. */
    if (sector_count > 1U)
    {
        p_ctrl->p_reg->SD_STOP   = SDHI_PRV_SD_STOP_SD_SECCNT_ENABLE;
        p_ctrl->p_reg->SD_SECCNT = sector_count;
    }
    else
    {
        p_ctrl->p_reg->SD_STOP = 0U;
    }

    /* Set sector size */
    p_ctrl->p_reg->SD_SIZE = sector_size;

    /* Send command. */
    r_sdhi_command_send_no_wait(p_ctrl, command, argument);
}

#if SDHI_CFG_SD_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Checks to see if the device is an SD card.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS          Card type is set if the device is an SD card.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_sd_card_check (sdhi_instance_ctrl_t * const p_ctrl)
{
    /* CMD8 must be sent before ACMD41. Reference Figure 4-1 "SD Memory Card State Diagram (card identification mode)"
     * in the SD Physical Layer Specification Version 6.00. */
    uint32_t  argument = ((SDHI_PRV_IF_COND_VOLTAGE << 8) | SDHI_PRV_IF_COND_CHECK_PATTERN);
    fsp_err_t err      = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_IF_COND, argument);
    if (FSP_ERR_TIMEOUT == err)
    {
        FSP_RETURN(err);
    }

    /* An SD card responds to CMD8 by echoing the argument in the R7 response. An eMMC device responds to CMD8 with the
     * extended CSD. If the response does not match the argument, return to check if this is an eMMC device. */
    sdmmc_response_t response;
    response.status = p_ctrl->p_reg->SD_RSP10;

    /* CMD8 is not supported by spec V1.X so we have to try CMD41. */
    if ((FSP_ERR_RESPONSE == err) || (response.status == argument))
    {
        /* Try to send ACMD41 for up to 1 second as long as the card is responding and initialization is not complete.
         * Returns immediately if the card fails to respond to ACMD41. */

        /* To ensure the 1 second timeout, consider that there are 48 bits in a command, 48 bits
         * in a response, and 8 clock cycles minimum between commands, so there are 104 clocks minimum,
         * and the maximum clock rate at this point is 400 kHz, so issue the command 400000 / 104
         * times to ensure a timeout of at least 1 second. */
        for (uint32_t i = 0U; i < SDHI_PRV_INIT_ONE_SECOND_TIMEOUT_ITERATIONS; i++)
        {
            /* Send App Command - CMD55 */
            err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_APP_CMD, 0U);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            uint32_t ocr = SDHI_PRV_OCR_VDD_SUPPORTED | SDHI_PRV_OCR_CAPACITY_HC;

            /* ACMD41 */
            err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_C_ACMD | SDHI_PRV_CMD_SD_SEND_OP_COND, ocr);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            /* get response of ACMD41 (R3) */
            response.status = p_ctrl->p_reg->SD_RSP10;

            /*  Initialization complete? */
            if (response.r3.power_up_status)
            {
                /* High capacity card ? */
                /*  0 = SDSC, 1 = SDHC or SDXC */
                p_ctrl->sector_addressing = (response.r3.card_capacity_status > 0U);
                p_ctrl->device.card_type  = SDMMC_CARD_TYPE_SD;

                break;
            }
        }
    }

    return FSP_SUCCESS;
}

#endif

#if SDHI_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Checks to see if the device is an eMMC.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS          Card type is set if the device is an eMMC card.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_emmc_check (sdhi_instance_ctrl_t * const p_ctrl)
{
    uint32_t         ocr;
    sdmmc_response_t response = {0U};
    uint32_t         capacity;
    capacity = SDHI_PRV_OCR_CAPACITY_HC; /* SDHC cards supported */

    /* Tries to send CMD1 for up to 1 second as long as the device is responding and initialization is not complete.
     * Returns immediately if the device fails to respond to CMD1. */

    /* To ensure the 1 second timeout, consider that there are 48 bits in a command, 48 bits in a response, and 8 clock
     * cycles minimum between commands, so there are 104 clocks minimum, and the maximum clock rate at this point is 400
     * kHz, so issue the command 400000 / 104 times to ensure a timeout of at least 1 second. */
    for (uint32_t i = 0U; i < SDHI_PRV_INIT_ONE_SECOND_TIMEOUT_ITERATIONS; i++)
    {
        /*  Format and send cmd: Volt. window is usually 0x00300000 (3.4-3.2v) */
        /* SD cards will not respond to CMD1  */
        ocr  = SDHI_PRV_OCR_VDD_SUPPORTED;
        ocr |= capacity;

        fsp_err_t err = r_sdhi_command_send(p_ctrl, SDHI_PRV_EMMC_SEND_OP_COND, ocr);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* get response of CMD1  */
        response.status = p_ctrl->p_reg->SD_RSP10;

        /* Initialization complete? */
        if (response.r3.power_up_status)
        {
            p_ctrl->sector_addressing = (response.r3.card_capacity_status > 0U);
            p_ctrl->device.card_type  = SDMMC_CARD_TYPE_MMC;

            return FSP_SUCCESS;
        }
    }

    return FSP_SUCCESS;
}

#endif

#if SDHI_CFG_SD_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Update write protection status in control block.
 *
 * @param[in]  p_ctrl          Pointer to the instance control block.
 **********************************************************************************************************************/
static void r_sdhi_write_protect_get (sdhi_instance_ctrl_t * const p_ctrl)
{
    /* Update write protection status in the control block if the device is a card. */
    if (p_ctrl->p_cfg->write_protect)
    {
        p_ctrl->device.write_protected = (p_ctrl->p_reg->SD_INFO1_b.SDWPMON == 0U);
    }
}

#endif

/*******************************************************************************************************************//**
 * Wait for the device.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS          Previous operation is complete, and SDHI is ready for the next operation.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_wait_for_device (sdhi_instance_ctrl_t * const p_ctrl)
{
    /* Wait for the device to stop holding DAT0 low. */
    uint32_t timeout = SDHI_PRV_BUSY_TIMEOUT_US;
    while (SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_VAL !=
           (p_ctrl->p_reg->SD_INFO2 & SDHI_PRV_SD_INFO2_CBSY_SDD0MON_IDLE_MASK))
    {
        FSP_ERROR_RETURN(timeout > 0, FSP_ERR_DEVICE_BUSY);

        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
        timeout--;
    }

    return FSP_SUCCESS;
}

#if SDHI_CFG_SD_SUPPORT_ENABLE || SDHI_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Set SDHI clock to fastest allowable speed for card.
 *
 * @param[in]  p_ctrl                    Pointer to the instance control block.
 * @param[in]  rca                       Relative card address
 * @param[in]  p_csd_reg                 Pointer to card specific data.
 *
 * @retval     FSP_SUCCESS               Clock rate adjusted to the maximum speed allowed by both device and MCU.
 * @retval     FSP_ERR_RESPONSE          Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT           Device did not respond.
 * @retval     FSP_ERR_CARD_INIT_FAILED  Timeout setting divider or operation is still too fast at maximum divider
 *                                       (unlikely).
 * @retval     FSP_ERR_DEVICE_BUSY       Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_clock_optimize (sdhi_instance_ctrl_t * const p_ctrl,
                                        uint32_t                     rca,
                                        sdmmc_priv_csd_reg_t * const p_csd_reg)
{
    fsp_err_t err = FSP_SUCCESS;

    uint32_t max_clock_rate = SDHI_PRV_SD_DEFAULT_CLOCK_RATE;
 #if SDHI_CFG_EMMC_SUPPORT_ENABLE
    if (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type)
    {
        uint8_t device_type;
        err = r_sdhi_csd_extended_get(p_ctrl, rca, &device_type);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        max_clock_rate = SDHI_PRV_EMMC_DEFAULT_CLOCK_RATE;
        if ((SDHI_PRV_EMMC_HIGH_SPEED_52_MHZ_BIT & device_type) > 0U)
        {
            /* 52 MHz high speed supported, switch to this mode (CMD6). */
            err = r_sdhi_command_send(p_ctrl, SDHI_PRV_EMMC_CMD_SWITCH_WBUSY, SDHI_PRV_EMMC_HIGH_SPEED_MODE);
            FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

            max_clock_rate = SDHI_PRV_EMMC_HIGH_SPEED_CLOCK_RATE; // Set clock rate to 52 MHz maximum

            /* Device may signal busy after CMD6.  Wait for busy to clear. */
            r_sdhi_wait_for_device(p_ctrl);
        }
    }
    else
 #else
    FSP_PARAMETER_NOT_USED(rca);
 #endif
    {
 #if SDHI_CFG_SD_SUPPORT_ENABLE

        /* Ask SD card to switch to high speed if CMD6 is supported.  CMD6 is supported if bit 10 of the CCC field
         * in the CSD is set.*/
        if (SDHI_PRV_CSD_REG_CCC_CLASS_10_BIT == (SDHI_PRV_CSD_REG_CCC_CLASS_10_BIT & p_csd_reg->csd_v1_b.ccc))
        {
            if (FSP_SUCCESS == r_sdhi_sd_high_speed(p_ctrl))
            {
                max_clock_rate = SDHI_PRV_SD_HIGH_SPEED_CLOCK_RATE; // Set clock rate to 50 MHz maximum
            }
        }

 #else
        FSP_PARAMETER_NOT_USED(p_csd_reg);
 #endif
    }

    err = r_sdhi_max_clock_rate_set(p_ctrl, max_clock_rate);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Waits for the access end interrupt.
 *
 * @param[in]  p_ctrl            Pointer to the instance control block.
 * @param[in]  bit               Bit to check in p_ctrl->sdhi_event
 * @param[in]  timeout_us        Number of loops to check bit (at least 1 us per loop).
 *
 * @retval     FSP_SUCCESS       Requested bit (access end or response end) is set.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_wait_for_event (sdhi_instance_ctrl_t * const p_ctrl, uint32_t bit, uint32_t timeout_us)
{
    /* The event status is updated in the access interrupt.  Use a local copy of the event status to make sure
     * it isn't updated during the loop. */
    volatile sdhi_event_t event;
    while (true)
    {
        /* Check for updates to the event status. */
        event.word = p_ctrl->sdhi_event.word;

        /* Return an error if a hardware error occurred. */
        if (event.bit.event_error)
        {
            FSP_RETURN(FSP_ERR_RESPONSE);
        }

        /* If the requested bit is set, return success. */
        if (event.word & (1U << bit))
        {
            return FSP_SUCCESS;
        }

        /* Check for timeout. */
        timeout_us--;
        if (0U == timeout_us)
        {
            FSP_RETURN(FSP_ERR_TIMEOUT);
        }

        /* Wait 1 us for consistent loop timing. */
        R_BSP_SoftwareDelay(1U, BSP_DELAY_UNITS_MICROSECONDS);
    }
}

#if SDHI_CFG_SD_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Checks to see if the SD card supports high speed.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 *
 * @retval     FSP_SUCCESS          SD clock set to the maximum supported by both host and device.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_INTERNAL     Error in response from card during switch to high speed mode.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_sd_high_speed (sdhi_instance_ctrl_t * const p_ctrl)
{
    /* Issue CMD6 to switch to high speed. */
    fsp_err_t err = r_sdhi_read_and_block(p_ctrl,
                                          SDHI_PRV_CMD_SWITCH,
                                          SDHI_PRV_SD_HIGH_SPEED_MODE_SWITCH,
                                          SDHI_PRV_SD_SWITCH_STATUS_SIZE);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Read the switch response to see if the high speed switch is supported and completed successfully. */
    uint8_t * p_read_data_8 = (uint8_t *) &p_ctrl->aligned_buff[0];

    /* Check for successful switch. */
    if (SDHI_PRV_SD_SWITCH_HIGH_SPEED_OK ==
        (p_read_data_8[SDHI_PRV_SD_SWITCH_HIGH_SPEED_RESPONSE] & SDHI_PRV_SD_SWITCH_HIGH_SPEED_OK))
    {
        err = FSP_SUCCESS;
    }

    /* Check for error response to High speed Function. */
    if (SDHI_PRV_SD_SWITCH_HIGH_SPEED_ERROR ==
        (p_read_data_8[SDHI_PRV_SD_SWITCH_HIGH_SPEED_ERROR_RESPONSE] &
         SDHI_PRV_SD_SWITCH_HIGH_SPEED_ERROR))
    {
        err = FSP_ERR_INTERNAL;
    }

    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

#endif

#if SDHI_CFG_SD_SUPPORT_ENABLE || SDHI_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Save Card Specific Data.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 * @param[in]  rca                  Relative card address
 * @param[out] p_csd_reg            Pointer to card specific data.
 *
 * @retval     FSP_SUCCESS          Card specific data stored in provided pointer.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_csd_save (sdhi_instance_ctrl_t * const p_ctrl,
                                  uint32_t                     rca,
                                  sdmmc_priv_csd_reg_t * const p_csd_reg)
{
    /* Send CMD9 to get CSD */
    fsp_err_t err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_SEND_CSD, rca << 16);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* SDResponseR2 are bits from 8-127, first 8 MSBs are reserved */
    p_csd_reg->reg.sdrsp10 = p_ctrl->p_reg->SD_RSP10;
    p_csd_reg->reg.sdrsp32 = p_ctrl->p_reg->SD_RSP32;
    p_csd_reg->reg.sdrsp54 = p_ctrl->p_reg->SD_RSP54;
    p_csd_reg->reg.sdrsp76 = p_ctrl->p_reg->SD_RSP76;

    /* Get the CSD version. */
    uint32_t csd_version = p_csd_reg->csd_v1_b.csd_structure;

    /* Save sector count (total number of sectors on device) and erase sector count (minimum erasable unit in
     * sectors). */
    uint32_t mult;
    if ((SDHI_PRV_CSD_VERSION_1_0 == csd_version) || (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type))
    {
        mult = (1U << (p_csd_reg->csd_v1_b.c_size_mult + 2));
        p_ctrl->device.sector_count = ((p_csd_reg->csd_v1_b.c_size + 1U) * mult);

        /* Scale the sector count by the actual block size. */
        uint32_t read_sector_size = 1U << p_csd_reg->csd_v1_b.read_bl_len;
        p_ctrl->device.sector_count = p_ctrl->device.sector_count * (read_sector_size / SDHI_MAX_BLOCK_SIZE);

        if (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type)
        {
            /* If c_size is 0xFFF, then sector_count should be obtained from the extended CSD. Set it to 0 to indicate it
             * should come from the extended CSD later. */
            if (SDHI_PRV_SECTOR_COUNT_IN_EXT_CSD == p_csd_reg->csd_v1_b.c_size)
            {
                p_ctrl->device.sector_count = 0U;
            }
        }
    }

 #if SDHI_CFG_SD_SUPPORT_ENABLE
    else if (SDHI_PRV_CSD_VERSION_2_0 == csd_version)
    {
        p_ctrl->device.sector_count = (p_csd_reg->csd_v2_b.c_size + 1U) * SDHI_PRV_BYTES_PER_KILOBYTE;
    }
    else
    {
        /* Do Nothing */
    }

    if (SDHI_PRV_CSD_VERSION_1_0 == csd_version)
    {
        /* Get the minimum erasable unit (in 512 byte sectors). */
        p_ctrl->device.erase_sector_count = p_csd_reg->csd_v1_b.sector_size + 1U;
    }
    else
 #endif
    {
        /* For SDHC and SDXC cards, there are no erase group restrictions.
         *
         * Using the eMMC TRIM operation, there are no erase group restrictions. */
        p_ctrl->device.erase_sector_count = 1U;
    }

    return FSP_SUCCESS;
}

#endif

#if SDHI_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Get and store relevant extended card specific data.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 * @param[in]  rca                  Relative card address
 * @param[out] p_device_type        Pointer to store device type, which is used to determine if high speed is supported.
 *
 * @retval     FSP_SUCCESS          Device type obtained from eMMC extended CSD.  Sector count is also calculated here
 *                                  if it was not determined previously.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_csd_extended_get (sdhi_instance_ctrl_t * const p_ctrl, uint32_t rca, uint8_t * p_device_type)
{
    /* Ask card to send extended CSD (CMD8). */
    fsp_err_t err =
        r_sdhi_read_and_block(p_ctrl, SDHI_PRV_EMMC_CMD_SEND_EXT_CSD, rca << 16, SDHI_PRV_EMMC_EXT_CSD_SIZE);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Store device type.  Also store sector count if it is not already determined. */
    uint8_t * p_read_data_8 = (uint8_t *) &p_ctrl->aligned_buff[0];
    *p_device_type = p_read_data_8[SDHI_PRV_EMMC_EXT_CSD_DEVICE_TYPE_OFFSET];

    if (0U == p_ctrl->device.sector_count)
    {
        p_ctrl->device.sector_count = p_ctrl->aligned_buff[SDHI_PRV_EMMC_EXT_CSD_SEC_COUNT_OFFSET / sizeof(uint32_t)];
    }

    return FSP_SUCCESS;
}

#endif

#if SDHI_CFG_SD_SUPPORT_ENABLE || SDHI_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Issue command expecting data to be returned, and block until read data is returned.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 * @param[in]  command              Command to issue.
 * @param[in]  argument             Argument to send with command.
 * @param[in]  byte_count           Expected number of bytes to read.
 *
 * @retval     FSP_SUCCESS          Requested data read into internal buffer.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_read_and_block (sdhi_instance_ctrl_t * const p_ctrl,
                                        uint32_t                     command,
                                        uint32_t                     argument,
                                        uint32_t                     byte_count)
{
    /* Prepare transfer interface to read. */
    fsp_err_t err = r_sdhi_transfer_read(p_ctrl, 1U, byte_count, &p_ctrl->aligned_buff[0]);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Issue command. */
    r_sdhi_read_write_common(p_ctrl, 1U, byte_count, command, argument);

    /* Wait for access end, error, or timeout. */
    return r_sdhi_wait_for_event(p_ctrl, SDHI_PRV_ACCESS_BIT, SDHI_PRV_ACCESS_TIMEOUT_US);
}

#endif

/*******************************************************************************************************************//**
 * Gets or assigns the relative card address.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 * @param[out] p_rca                Pointer to store relative card address.
 *
 * @retval     FSP_SUCCESS          Relative card address is assigned and device is in standby state.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_rca_get (sdhi_instance_ctrl_t * const p_ctrl, uint32_t * p_rca)
{
    /* Send CMD3.  For eMMC, assign an RCA of SDHI channel number + 2. These bits of the argument are ignored for SD
     * cards. */
    uint32_t  rca = (p_ctrl->p_cfg->channel + 2U);
    fsp_err_t err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_SEND_RELATIVE_ADDR, rca << 16);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

#if SDHI_CFG_SD_SUPPORT_ENABLE
    sdmmc_response_t response = {0U};
    response.status = p_ctrl->p_reg->SD_RSP10;
    if (SDMMC_CARD_TYPE_MMC != p_ctrl->device.card_type)
    {
        /* Get relative card address from the response if the device is an SD card. */
        rca = (response.r6.rca);
    }
#endif

    *p_rca = rca;

    return FSP_SUCCESS;
}

#if SDHI_CFG_SD_SUPPORT_ENABLE || SDHI_CFG_EMMC_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Set bus width.
 *
 * @param[in]  p_ctrl               Pointer to the instance control block.
 * @param[in]  rca                  Relative card address
 *
 * @retval     FSP_SUCCESS          Bus width updated on device.
 * @retval     FSP_ERR_RESPONSE     Device responded with an error.
 * @retval     FSP_ERR_TIMEOUT      Device did not respond.
 * @retval     FSP_ERR_DEVICE_BUSY  Device is holding DAT0 low (device is busy) or another operation is ongoing.
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_bus_width_set (sdhi_instance_ctrl_t * const p_ctrl, uint32_t rca)
{
    uint32_t bus_width;
    uint32_t bus_width_setting;

    bus_width = p_ctrl->p_cfg->bus_width;

 #if SDHI_CFG_EMMC_SUPPORT_ENABLE
    if (SDMMC_CARD_TYPE_MMC == p_ctrl->device.card_type)
    {
        /* For eMMC, set bus width using CMD6. */
        bus_width_setting = ((bus_width >> 2U) & 0x03U);
        fsp_err_t err = r_sdhi_command_send(p_ctrl,
                                            SDHI_PRV_EMMC_CMD_SWITCH_WBUSY,
                                            ((0x1U << SDHI_PRV_SWITCH_ACCESS_SHIFT) |
                                             (SDHI_PRV_EMMC_BUS_WIDTH_INDEX <<
                                              SDHI_PRV_SWITCH_INDEX_SHIFT) |
                                             (bus_width_setting << SDHI_PRV_SWITCH_VALUE_SHIFT)));
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* Device may signal busy after CMD6.  Wait for busy to clear. */
        r_sdhi_wait_for_device(p_ctrl);
    }
    else
 #endif
    {
 #if SDHI_CFG_SD_SUPPORT_ENABLE

        /* Send CMD55, app command. */
        bus_width_setting = ((bus_width >> 1U) & 0x03U);
        fsp_err_t err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_APP_CMD, rca << 16);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

        /* For SD cards, set bus width using ACMD6. */
        err = r_sdhi_command_send(p_ctrl, SDHI_PRV_CMD_C_ACMD | SDHI_PRV_CMD_SET_BUS_WIDTH, bus_width_setting);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
 #else
        FSP_PARAMETER_NOT_USED(rca);
 #endif
    }

    /* Set the bus width in the SDHI peripheral. */
    uint32_t bus_width_reg = 0U;
    if (SDMMC_BUS_WIDTH_8_BITS == bus_width)
    {
        bus_width_reg = 1U;
    }

    if (SDMMC_BUS_WIDTH_1_BIT == bus_width)
    {
        bus_width_reg = SDHI_PRV_BUS_WIDTH_1_BIT;
    }

    p_ctrl->p_reg->SD_OPTION = SDHI_PRV_SD_OPTION_DEFAULT | (bus_width_reg << SDHI_PRV_SD_OPTION_WIDTH8_BIT);

    return FSP_SUCCESS;
}

#endif

/*******************************************************************************************************************//**
 * Performs workaround in the transfer interrupt for unaligned reads and writes.
 *
 * @param[in]     p_ctrl         Pointer to the instance control block.
 **********************************************************************************************************************/
void r_sdhi_transfer_callback (sdhi_instance_ctrl_t * p_ctrl)
{
#if SDMMC_CFG_UNALIGNED_ACCESS_ENABLE
    if (p_ctrl->transfer_blocks_total != p_ctrl->transfer_block_current)
    {
        if (SDHI_TRANSFER_DIR_READ == p_ctrl->transfer_dir)
        {
            /* If the transfer is a read operation into an unaligned buffer, copy the block read from the aligned
             * buffer in the control block to the application data buffer. */
            memcpy(p_ctrl->p_transfer_data, (void *) &p_ctrl->aligned_buff[0], p_ctrl->transfer_block_size);
        }

        if (SDHI_TRANSFER_DIR_WRITE == p_ctrl->transfer_dir)
        {
            /* If the transfer is a write operation from an unaligned buffer, copy the next block to write from the
             * application data buffer to the aligned buffer in the control block. */
            memcpy((void *) &p_ctrl->aligned_buff[0], p_ctrl->p_transfer_data, p_ctrl->transfer_block_size);
        }

        p_ctrl->transfer_block_current++;
        p_ctrl->p_transfer_data += p_ctrl->transfer_block_size;
    }

    if (p_ctrl->transfer_blocks_total == p_ctrl->transfer_block_current)
    {
        if (SDHI_TRANSFER_DIR_READ == p_ctrl->transfer_dir)
        {
            /* After the entire read transfer to an unaligned buffer is complete, read transfer end and callback are
             * performed in transfer interrupt to ensure the last block is in the application buffer before the
             * callback is called. */
            r_sdhi_transfer_end(p_ctrl);

            sdmmc_callback_args_t args;
            memset(&args, 0U, sizeof(args));
            args.p_context = p_ctrl->p_context;
            args.event    |= SDMMC_EVENT_TRANSFER_COMPLETE;
            r_sdhi_call_callback(p_ctrl, &args);
        }
    }

#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
#endif
}

/*******************************************************************************************************************//**
 * Set up transfer to read from device.
 *
 * @param[in]  p_ctrl       Pointer to the instance control block.
 * @param[in]  block_count  Number of blocks to transfer.
 * @param[in]  bytes        Bytes per block.
 * @param[in]  p_data       Pointer to data to read data from device into.
 *
 * @retval     FSP_SUCCESS  Transfer successfully configured to write data.
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               * @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_transfer_read (sdhi_instance_ctrl_t * const p_ctrl,
                                       uint32_t                     block_count,
                                       uint32_t                     bytes,
                                       void                       * p_data)
{
    transfer_info_t * p_info = p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info;

    /* When the SD_DMAEN.DMAEN bit is 1, set the SD_INFO2_MASK.BWEM bit to 1 and the SD_INFO2_MASK.BREM bit to 1. */
    p_ctrl->p_reg->SD_INFO2_MASK |= SDHI_PRV_SD_INFO2_MASK_BREM_BWEM_MASK;
    p_ctrl->p_reg->SD_DMAEN       = SDHI_PRV_SD_DMAEN_DMAEN_SET;

    uint32_t transfer_settings = (uint32_t) TRANSFER_MODE_BLOCK << TRANSFER_SETTINGS_MODE_BITS;
    transfer_settings |= TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_DEST_ADDR_BITS;
    transfer_settings |= TRANSFER_SIZE_4_BYTE << TRANSFER_SETTINGS_SIZE_BITS;

#if SDMMC_CFG_UNALIGNED_ACCESS_ENABLE

    /* If the pointer is not 4-byte aligned or the number of bytes is not a multiple of 4, use a temporary buffer.
     * Data will be transferred from the temporary buffer into the user buffer in an interrupt after each block transfer. */
    if ((0U != ((uint32_t) p_data & 0x3U)) || (0U != (bytes & 3U)))
    {
        transfer_settings |= TRANSFER_IRQ_EACH << TRANSFER_SETTINGS_IRQ_BITS;
        p_info->p_dest     = &p_ctrl->aligned_buff[0];

        p_ctrl->transfer_block_current = 0U;
        p_ctrl->transfer_blocks_total  = block_count;
        p_ctrl->p_transfer_data        = (uint8_t *) p_data;
        p_ctrl->transfer_dir           = SDHI_TRANSFER_DIR_READ;
        p_ctrl->transfer_block_size    = bytes;
    }
    else
#endif
    {
        transfer_settings |= TRANSFER_REPEAT_AREA_SOURCE << TRANSFER_SETTINGS_REPEAT_AREA_BITS;
        p_info->p_dest     = p_data;
    }

    p_info->transfer_settings_word = transfer_settings;
    p_info->p_src      = (uint32_t *) (&p_ctrl->p_reg->SD_BUF0);
    p_info->num_blocks = (uint16_t) block_count;

    /* Round up to the nearest multiple of 4 bytes for the transfer. */
    uint32_t words = (bytes + (sizeof(uint32_t) - 1U)) / sizeof(uint32_t);
    p_info->length = (uint16_t) words;

    /* Configure the transfer driver to read from the SD buffer. */
    fsp_err_t err = p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->reconfigure(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl,
                                                                            p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Set up transfer to write to device.
 *
 * @param[in]  p_ctrl       Pointer to the instance control block.
 * @param[in]  block_count  Number of blocks to transfer.
 * @param[in]  bytes        Bytes per block.
 * @param[in]  p_data       Pointer to data to write to device.
 *
 * @retval     FSP_SUCCESS  Transfer successfully configured to write data.
 * @return     See @ref RENESAS_ERROR_CODES or functions called by this function for other possible return codes. This
 *             function calls:
 *               * @ref transfer_api_t::reconfigure
 **********************************************************************************************************************/
static fsp_err_t r_sdhi_transfer_write (sdhi_instance_ctrl_t * const p_ctrl,
                                        uint32_t                     block_count,
                                        uint32_t                     bytes,
                                        const uint8_t              * p_data)
{
    transfer_info_t * p_info = p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info;

    /* When the SD_DMAEN.DMAEN bit is 1, set the SD_INFO2_MASK.BWEM bit to 1 and the SD_INFO2_MASK.BREM bit to 1. */
    p_ctrl->p_reg->SD_INFO2_MASK |= SDHI_PRV_SD_INFO2_MASK_BREM_BWEM_MASK;
    p_ctrl->p_reg->SD_DMAEN       = SDHI_PRV_SD_DMAEN_DMAEN_SET;

    uint32_t transfer_settings = (uint32_t) TRANSFER_MODE_BLOCK << TRANSFER_SETTINGS_MODE_BITS;
    transfer_settings |= TRANSFER_ADDR_MODE_INCREMENTED << TRANSFER_SETTINGS_SRC_ADDR_BITS;
    transfer_settings |= TRANSFER_SIZE_4_BYTE << TRANSFER_SETTINGS_SIZE_BITS;

#if SDMMC_CFG_UNALIGNED_ACCESS_ENABLE
    if ((0U != ((uint32_t) p_data & 0x3U)) || (0U != (bytes & 3U)))
    {
        transfer_settings |= TRANSFER_IRQ_EACH << TRANSFER_SETTINGS_IRQ_BITS;
        transfer_settings |= TRANSFER_REPEAT_AREA_SOURCE << TRANSFER_SETTINGS_REPEAT_AREA_BITS;

        /* If the pointer is not 4-byte aligned or the number of bytes is not a multiple of 4, use a temporary buffer.
         * Transfer the first block to the temporary buffer before enabling the transfer.  Subsequent blocks will be
         * transferred from the user buffer to the temporary buffer in an interrupt after each block transfer. */
        memcpy((void *) &p_ctrl->aligned_buff[0], p_data, bytes);
        p_info->p_src = &p_ctrl->aligned_buff[0];

        p_ctrl->transfer_block_current = 1U;
        p_ctrl->transfer_blocks_total  = block_count;
        p_ctrl->p_transfer_data        = (uint8_t *) &p_data[bytes];
        p_ctrl->transfer_dir           = SDHI_TRANSFER_DIR_WRITE;
        p_ctrl->transfer_block_size    = bytes;
    }
    else
#endif
    {
        p_info->p_src = p_data;
    }

    p_info->transfer_settings_word = transfer_settings;
    p_info->p_dest                 = (uint32_t *) (&p_ctrl->p_reg->SD_BUF0);
    p_info->num_blocks             = (uint16_t) block_count;

    /* Round up to the nearest multiple of 4 bytes for the transfer. */
    uint32_t words = (bytes + (sizeof(uint32_t) - 1U)) / sizeof(uint32_t);
    p_info->length = (uint16_t) words;

    /* Configure the transfer driver to write to the SD buffer. */
    fsp_err_t err = p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->reconfigure(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl,
                                                                            p_ctrl->p_cfg->p_lower_lvl_transfer->p_cfg->p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Close transfer driver, clear transfer data, and disable transfer in the SDHI peripheral.
 *
 * @param[in]     p_ctrl    Pointer to the instance control block.
 **********************************************************************************************************************/
static void r_sdhi_transfer_end (sdhi_instance_ctrl_t * const p_ctrl)
{
    p_ctrl->transfer_block_current = 0U;
    p_ctrl->transfer_blocks_total  = 0U;
    p_ctrl->p_transfer_data        = NULL;
    p_ctrl->transfer_dir           = SDHI_TRANSFER_DIR_NONE;
    p_ctrl->transfer_block_size    = 0U;

    p_ctrl->p_cfg->p_lower_lvl_transfer->p_api->disable(p_ctrl->p_cfg->p_lower_lvl_transfer->p_ctrl);
    p_ctrl->p_reg->SD_DMAEN = 0U;
}

/*******************************************************************************************************************//**
 * Calls user callback
 *
 * @param[in]     p_ctrl    Pointer to the instance control block.
 * @param[in]     p_args    Pointer to callback arguments with event and response set.
 **********************************************************************************************************************/
static void r_sdhi_call_callback (sdhi_instance_ctrl_t * p_ctrl, sdmmc_callback_args_t * p_args)
{
    /* Call user callback if provided, if an event was determined, and if the driver is initialized. */
    if (NULL != p_ctrl->p_callback)
    {
        sdmmc_callback_args_t args;

        /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
         * stored in non-secure memory so they can be accessed by a non-secure callback function. */
        sdmmc_callback_args_t * p_args_memory = p_ctrl->p_callback_memory;
        if (NULL == p_args_memory)
        {
            /* Use provided args struct on stack */
            p_args_memory = p_args;
        }
        else
        {
            /* Save current arguments on the stack in case this is a nested interrupt. */
            args = *p_args_memory;

            /* Copy the stacked args to callback memory */
            *p_args_memory = *p_args;
        }

        p_args_memory->p_context = p_ctrl->p_context;

#if BSP_TZ_SECURE_BUILD

        /* p_callback can point to a secure function or a non-secure function. */
        if (!cmse_is_nsfptr(p_ctrl->p_callback))
        {
            /* If p_callback is secure, then the project does not need to change security state. */
            p_ctrl->p_callback(p_args_memory);
        }
        else
        {
            /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
            sdhi_prv_ns_callback p_callback = (sdhi_prv_ns_callback) (p_ctrl->p_callback);
            p_callback(p_args_memory);
        }

#else

        /* If the project is not Trustzone Secure, then it will never need to change security state in order to call the callback. */
        p_ctrl->p_callback(p_args_memory);
#endif

        if (NULL != p_ctrl->p_callback_memory)
        {
            /* Restore callback memory in case this is a nested interrupt. */
            *p_ctrl->p_callback_memory = args;
        }
    }
}

/*******************************************************************************************************************//**
 * Calls user callback after response or data transfer complete.
 **********************************************************************************************************************/
void sdhimmc_accs_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type              irq    = R_FSP_CurrentIrqGet();
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    sdmmc_callback_args_t args;
    memset(&args, 0U, sizeof(args));
    r_sdhi_access_irq_process(p_ctrl, &args);

    /* Call user callback */
    if ((p_ctrl->initialized) && (0U != args.event))
    {
        r_sdhi_call_callback(p_ctrl, &args);
    }

    /* Clear the IR flag in the ICU */
    /* Clearing the IR bit must be done after clearing the interrupt source in the the peripheral */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * Calls user callback when card insertion or removal interrupt fires.
 **********************************************************************************************************************/
void sdhimmc_card_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE
    sdmmc_callback_args_t args;
    memset(&args, 0U, sizeof(args));

    IRQn_Type              irq    = R_FSP_CurrentIrqGet();
    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    sdhi_event_t info1 = {0U};
    info1.word = p_ctrl->p_reg->SD_INFO1;

    if (0U != (info1.word & SDHI_PRV_SDHI_INFO1_CARD_REMOVED_MASK))
    {
        p_ctrl->initialized = false;
        args.event         |= SDMMC_EVENT_CARD_REMOVED;
    }

    if (0U != (info1.word & SDHI_PRV_SDHI_INFO1_CARD_INSERTED_MASK))
    {
        args.event |= SDMMC_EVENT_CARD_INSERTED;
    }

    /* Clear interrupt flags processed in this ISR. */
    info1.word             &= SDHI_PRV_SDHI_INFO1_CARD_MASK;
    p_ctrl->p_reg->SD_INFO1 = (~info1.word);

    /* Call user callback if provided */
    args.p_context = p_ctrl->p_context;
    r_sdhi_call_callback(p_ctrl, &args);

    /* Clear the IR flag in the ICU */
    /* Clearing the IR bit must be done after clearing the interrupt source in the the peripheral */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}

/*******************************************************************************************************************//**
 * DMA ISR.  Called when a DTC transfer completes.  Not used for DMAC.
 *
 * Handles data copy for unaligned buffers and transfer complete processing.
 **********************************************************************************************************************/
void sdhimmc_dma_req_isr (void)
{
    /* Save context if RTOS is used */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();

    sdhi_instance_ctrl_t * p_ctrl = (sdhi_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    r_sdhi_transfer_callback(p_ctrl);

    /* Clear the IR flag in the ICU.
     * This must be after the callback because the next DTC transfer will begin when this bit is cleared. */
    R_BSP_IrqStatusClear(irq);

    /* Restore context if RTOS is used */
    FSP_CONTEXT_RESTORE
}
