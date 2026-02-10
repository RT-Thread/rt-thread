/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_ospi_b.h"
#include <string.h>

#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
 #include "r_transfer_api.h"
 #include "r_dmac.h"
#endif

#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
 #if defined OSPI_B_CFG_DOTF_PROTECTED_MODE_SUPPORT_ENABLE
  #include "r_rsip_api.h"
  #include "r_rsip_public.h"
extern rsip_instance_t const * const gp_rsip_instance;
 #else
  #include "hw_sce_trng_private.h"
  #include "hw_sce_ra_private.h"
 #endif
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* "xSPI" in ASCII.  Used to determine if the control block is open. */
#define OSPI_B_PRV_OPEN                   (0x78535049U)

#define OSPI_B_PRV_CHANNELS_PER_UNIT      (2U)
#define OSPI_B_PRV_UNIT_CHANNELS_SHIFT    (OSPI_B_PRV_CHANNELS_PER_UNIT)
#define OSPI_B_PRV_UNIT_CHANNELS_MASK     ((1U << OSPI_B_PRV_UNIT_CHANNELS_SHIFT) - 1U)

/* If any of the BSP memory macros are not defined, give them a default value of 0 for use in this file. */
#ifndef BSP_OSPI0_CS0_START_ADDRESS
 #define BSP_OSPI0_CS0_START_ADDRESS      (0U)
#endif

#ifndef BSP_OSPI0_CS0_SIZE_BYTES
 #define BSP_OSPI0_CS0_SIZE_BYTES         (0U)
#endif

#ifndef BSP_OSPI0_CS1_START_ADDRESS
 #define BSP_OSPI0_CS1_START_ADDRESS      (0U)
#endif

#ifndef BSP_OSPI0_CS1_SIZE_BYTES
 #define BSP_OSPI0_CS1_SIZE_BYTES         (0U)
#endif

#ifndef BSP_OSPI1_CS0_START_ADDRESS
 #define BSP_OSPI1_CS0_START_ADDRESS      (0U)
#endif

#ifndef BSP_OSPI1_CS0_SIZE_BYTES
 #define BSP_OSPI1_CS0_SIZE_BYTES         (0U)
#endif

#ifndef BSP_OSPI1_CS1_START_ADDRESS
 #define BSP_OSPI1_CS1_START_ADDRESS      (0U)
#endif

#ifndef BSP_OSPI1_CS1_SIZE_BYTES
 #define BSP_OSPI1_CS1_SIZE_BYTES         (0U)
#endif

/**
 * Mask of all channels for a given OSPI_B unit.
 * @param p_ext_cfg Pointer to a OSPI_B extended config struct with the unit to mask.
 */
#define OSPI_B_PRV_UNIT_MASK(p_ext_cfg)                 (OSPI_B_PRV_UNIT_CHANNELS_MASK << \
                                                         (((p_ext_cfg)->ospi_b_unit) * OSPI_B_PRV_UNIT_CHANNELS_SHIFT))

/**
 * Individual bit mask for a single channel on a given OSPI_B unit.
 * @param p_ext_cfg Pointer to a OSPI_B extended config struct with the unit and channel to mask.
 */
#define OSPI_B_PRV_CH_MASK(p_ext_cfg)                   ((1U << ((p_ext_cfg)->channel)) << \
                                                         (((p_ext_cfg)->ospi_b_unit) * OSPI_B_PRV_UNIT_CHANNELS_SHIFT))

/**
 * Gets the extended configuration struct for this instance.
 * @param p_ctrl Pointer to the instance control block.
 */
#define OSPI_B_PRV_EXTENDED_CFG(p_ctrl)                 ((ospi_b_extended_cfg_t *) \
                                                         ((ospi_b_instance_ctrl_t *) (p_ctrl))->p_cfg->p_extend)

/** Indicates the provided protocol mode requires the Data-Strobe signal. */
#define OSPI_B_PRV_PROTOCOL_USES_DS_SIGNAL(protocol)    ((bool) (((uint32_t) (protocol)) & 0x200UL))

/** Number of bytes combined into a single transaction for memory-mapped writes. */
#define OSPI_B_PRV_COMBINATION_WRITE_LENGTH              (2U * ((uint8_t) OSPI_B_CFG_COMBINATION_FUNCTION + 1U))

/** Converts @ref spi_flash_address_bytes_t to a register compatible length value. */
#define OSPI_B_PRV_ADDR_BYTES_TO_LENGTH(spi_flash_bytes)    ((uint8_t) ((spi_flash_bytes) + 1U))

#define OSPI_B_PRV_BMCTL_DEFAULT_VALUE                   (0x0C)

#define OSPI_B_PRV_CMCFG_1BYTE_VALUE_MASK                (0xFF00U)
#define OSPI_B_PRV_CMCFG_2BYTE_VALUE_MASK                (0xFFFFU)

#define OSPI_B_PRV_AUTOCALIBRATION_DATA_SIZE             (0xFU)
#define OSPI_B_PRV_AUTOCALIBRATION_LATENCY_CYCLES        (0U)

#define OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_0    (0xFFFF0000U)
#define OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_1    (0x000800FFU)
#define OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_2    (0x00FFF700U)
#define OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_3    (0xF700F708U)

#define OSPI_B_PRV_ADDRESS_REPLACE_VALUE                 (0xF0U)
#define OSPI_B_PRV_ADDRESS_REPLACE_ENABLE_BITS           (OSPI_B_PRV_ADDRESS_REPLACE_VALUE << \
                                                          R_XSPI0_CMCFGCS_CMCFG0_ADDRPEN_Pos)
#define OSPI_B_PRV_ADDRESS_REPLACE_MASK                  (~(OSPI_B_PRV_ADDRESS_REPLACE_VALUE << 24))

#define OSPI_B_PRV_AUTOCALIBRATION_FRAME_INTERVAL        (0x1FU)
#define OSPI_B_PRV_AUTOCALIBRATION_NO_WRITE_CMD          (0x1U)
#define OSPI_B_PRV_AUTOCALIBRATION_SHIFT_DS_END_VALUE    (0x1FU)

#define OSPI_B_PRV_WORD_ACCESS_SIZE                      (4U)
#define OSPI_B_PRV_HALF_WORD_ACCESS_SIZE                 (2U)

#define OSPI_B_PRV_DIRECT_ADDR_AND_DATA_MASK             (7U)
#define OSPI_B_PRV_PAGE_SIZE_BYTES                       (256U)

#define OSPI_B_PRV_DIRECT_CMD_SIZE_MASK                  (0x3U)

#define OSPI_B_PRV_CDTBUF_CMD_OFFSET                     (16U)
#define OSPI_B_PRV_CDTBUF_CMD_UPPER_OFFSET               (24U)
#define OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK              (0xFFU)
#define OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_SHIFT             (8U)
#define OSPI_B_PRV_CDTBUF_CMD_2B_VALUE_MASK              (0xFFFFU)

#define OSPI_B_PRV_BMCTL0_DISABLED_VALUE                 (0x00) // 0b0000'0000
#define OSPI_B_PRV_BMCTL0_READ_ONLY_VALUE                (0x55) // 0b0101'0101
#define OSPI_B_PRV_BMCTL0_WRITE_ONLY_VALUE               (0xAA) // 0b1010'1010
#define OSPI_B_PRV_BMCTL0_READ_WRITE_VALUE               (0xFF) // 0b1111'1111

#define OSPI_B_PRV_BMCTL1_CLEAR_PREFETCH_MASK            (0x03 << R_XSPI0_BMCTL1_PBUFCLRCH_Pos)
#define OSPI_B_PRV_BMCTL1_PUSH_COMBINATION_WRITE_MASK    (0x03 << R_XSPI0_BMCTL1_MWRPUSHCH_Pos)

#define OSPI_B_PRV_COMSTT_MEMACCCH_MASK                  (0x03 << R_XSPI0_COMSTT_MEMACCCH_Pos)
#define OSPI_B_PRV_COMSTT_WRBUFNECH_MASK                 (0x03 << R_XSPI0_COMSTT_WRBUFNECH_Pos)

#define OSPI_B_PRV_COMSTT_PENDING_ACTION_MASK            (OSPI_B_PRV_COMSTT_MEMACCCH_MASK | \
                                                          OSPI_B_PRV_COMSTT_WRBUFNECH_MASK)

#define OSPI_B_SOFTWARE_DELAY                            (50U)

#define OSPI_B_PRV_DOTF_REG00_RESET_VALUE                (0x22000000)
#define OSPI_B_PRV_CONVAREAST_RESET_VALUE                (0x0)
#define OSPI_B_PRV_CONVAREAD_RESET_VALUE                 (0x0)
#define OSPI_B_PRV_DOTF_SEED_1_SEED_MASK                 (0x3)
#define OSPI_B_PRV_DOTF_SEED_1_ENABLE_MASK               (0xC)

/* These are used as modulus checking, make sure they are powers of 2. */
#define OSPI_B_PRV_CPU_ACCESS_LENGTH                     (8U)
#define OSPI_B_PRV_CPU_ACCESS_ALIGNMENT                  (8U)

#define OSPI_B_PRV_PROTOCOL_USES_DS_MASK                 (0x200U)

#define OSPI_B_PRV_UINT32_BITS                           (32)

#ifndef OSPI_B_MAX_WRITE_ENABLE_LOOPS
 #define OSPI_B_MAX_WRITE_ENABLE_LOOPS                   (5)
#endif

/* Number of address bytes in 4 byte address mode. */
#define OSPI_B_4_BYTE_ADDRESS                            (4U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static bool      r_ospi_b_status_sub(ospi_b_instance_ctrl_t * p_instance_ctrl, uint8_t bit_pos);
static fsp_err_t r_ospi_b_protocol_specific_settings(ospi_b_instance_ctrl_t * p_instance_ctrl);
static fsp_err_t r_ospi_b_write_enable(ospi_b_instance_ctrl_t * p_instance_ctrl);
static void      r_ospi_b_direct_transfer(ospi_b_instance_ctrl_t            * p_instance_ctrl,
                                          spi_flash_direct_transfer_t * const p_transfer,
                                          spi_flash_direct_transfer_dir_t     direction);
static ospi_b_xspi_command_set_t const * r_ospi_b_command_set_get(ospi_b_instance_ctrl_t * p_instance_ctrl);

#if OSPI_B_CFG_AUTOCALIBRATION_SUPPORT_ENABLE
static fsp_err_t r_ospi_b_automatic_calibration_seq(ospi_b_instance_ctrl_t * p_instance_ctrl);

#endif

#if OSPI_B_CFG_ROW_ADDRESSING_SUPPORT_ENABLE
static void r_ospi_b_row_load_store(ospi_b_instance_ctrl_t * const p_ctrl, uint32_t row_index, bool store_row);

#endif

#if OSPI_B_CFG_XIP_SUPPORT_ENABLE
static void r_ospi_b_dummy_read(uint32_t * p_read_address);
static void r_ospi_b_xip(ospi_b_instance_ctrl_t * p_instance_ctrl, bool is_entering);

#endif

#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
static fsp_err_t r_ospi_b_dotf_setup(uint8_t ospi_b_unit, ospi_b_dotf_cfg_t * p_dotf_cfg);

#endif

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Bit-flags specifying which channels are open so the module can be stopped when all are closed. */
static uint32_t g_ospi_b_channels_open_flags = 0;

/*******************************************************************************************************************//**
 * @addtogroup OSPI_B
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

const spi_flash_api_t g_ospi_b_on_spi_flash =
{
    .open           = R_OSPI_B_Open,
    .directWrite    = R_OSPI_B_DirectWrite,
    .directRead     = R_OSPI_B_DirectRead,
    .directTransfer = R_OSPI_B_DirectTransfer,
    .spiProtocolSet = R_OSPI_B_SpiProtocolSet,
    .write          = R_OSPI_B_Write,
    .erase          = R_OSPI_B_Erase,
    .statusGet      = R_OSPI_B_StatusGet,
    .xipEnter       = R_OSPI_B_XipEnter,
    .xipExit        = R_OSPI_B_XipExit,
    .bankSet        = R_OSPI_B_BankSet,
    .close          = R_OSPI_B_Close,
    .autoCalibrate  = R_OSPI_B_AutoCalibrate,
};

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Open the xSPI device. After the driver is open, the xSPI device can be accessed like internal flash memory.
 *
 * Implements @ref spi_flash_api_t::open.
 *
 * @retval FSP_SUCCESS              Configuration was successful.
 * @retval FSP_ERR_ASSERTION        The parameter p_ctrl or p_cfg is NULL.
 * @retval FSP_ERR_ALREADY_OPEN     Driver has already been opened with the same p_ctrl.
 * @retval FSP_ERR_CALIBRATE_FAILED Failed to perform auto-calibrate.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_Open (spi_flash_ctrl_t * const p_ctrl, spi_flash_cfg_t const * const p_cfg)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;
    fsp_err_t                ret             = FSP_SUCCESS;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_cfg);
    FSP_ASSERT(NULL != p_cfg->p_extend);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN != p_instance_ctrl->open, FSP_ERR_ALREADY_OPEN);
#endif

    const ospi_b_extended_cfg_t * const p_cfg_extend = (ospi_b_extended_cfg_t *) (p_cfg->p_extend);

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(BSP_PERIPHERAL_OSPI_B_CHANNEL_MASK & (1U << p_cfg_extend->ospi_b_unit));
    FSP_ERROR_RETURN(0 == (g_ospi_b_channels_open_flags & OSPI_B_PRV_CH_MASK(p_cfg_extend)), FSP_ERR_ALREADY_OPEN);
#endif

    R_XSPI0_Type * p_reg = (R_XSPI0_Type *) ((uint32_t) R_XSPI0 +
                                             p_cfg_extend->ospi_b_unit * ((uint32_t) R_XSPI1 - (uint32_t) R_XSPI0));

    /* Enable clock to the xSPI block */
    R_BSP_MODULE_START(FSP_IP_OSPI, p_cfg_extend->ospi_b_unit);

    /* Initialize control block. */
    p_instance_ctrl->p_cfg        = p_cfg;
    p_instance_ctrl->p_reg        = p_reg;
    p_instance_ctrl->spi_protocol = p_cfg->spi_protocol;
    p_instance_ctrl->channel      = p_cfg_extend->channel;
    p_instance_ctrl->ospi_b_unit  = p_cfg_extend->ospi_b_unit;

#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
    if (NULL != p_cfg_extend->p_dotf_cfg)
    {
        ret = r_ospi_b_dotf_setup(p_cfg_extend->ospi_b_unit, p_cfg_extend->p_dotf_cfg);
        FSP_ERROR_RETURN(FSP_SUCCESS == ret, ret);
    }
#endif

#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
    transfer_instance_t const * p_transfer = p_cfg_extend->p_lower_lvl_transfer;

 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_transfer);
 #endif

    /* Initialize transfer instance */
    p_transfer->p_api->open(p_transfer->p_ctrl, p_transfer->p_cfg);
#endif

    /* Disable memory-mapping for this slave. It will be enabled later on after initialization. */
    if (OSPI_B_DEVICE_NUMBER_0 == p_instance_ctrl->channel)
    {
        p_reg->BMCTL0 &= ~(R_XSPI0_BMCTL0_CH0CS0ACC_Msk | R_XSPI0_BMCTL0_CH1CS0ACC_Msk);
    }
    else
    {
        p_reg->BMCTL0 &= ~(R_XSPI0_BMCTL0_CH0CS1ACC_Msk | R_XSPI0_BMCTL0_CH1CS1ACC_Msk);
    }

    /* Perform xSPI Initial configuration as described in hardware manual (see
     * "Flows of Operations" in the OSPI section of the relevant hardware manual). */

    /* Set xSPI protocol mode. */
    uint32_t liocfg = ((uint32_t) p_cfg->spi_protocol) << R_XSPI0_LIOCFGCS_PRTMD_Pos;
    p_reg->LIOCFGCS[p_cfg_extend->channel] = liocfg;

    /* Set xSPI drive/sampling timing. */
    if (OSPI_B_DEVICE_NUMBER_0 == p_instance_ctrl->channel)
    {
        p_reg->WRAPCFG = ((uint32_t) p_cfg_extend->data_latch_delay_clocks << R_XSPI0_WRAPCFG_DSSFTCS0_Pos) &
                         R_XSPI0_WRAPCFG_DSSFTCS0_Msk;
    }
    else
    {
        p_reg->WRAPCFG = ((uint32_t) p_cfg_extend->data_latch_delay_clocks << R_XSPI0_WRAPCFG_DSSFTCS1_Pos) &
                         R_XSPI0_WRAPCFG_DSSFTCS1_Msk;
    }

    /* Set minimum cycles between xSPI frames. */
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->command_to_command_interval << R_XSPI0_LIOCFGCS_CSMIN_Pos) &
              R_XSPI0_LIOCFGCS_CSMIN_Msk;

    /* Set CS asserting extension in cycles */
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->cs_pulldown_lead << R_XSPI0_LIOCFGCS_CSASTEX_Pos) &
              R_XSPI0_LIOCFGCS_CSASTEX_Msk;

    /* Set CS releasing extension in cycles */
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->cs_pullup_lag << R_XSPI0_LIOCFGCS_CSNEGEX_Pos) &
              R_XSPI0_LIOCFGCS_CSNEGEX_Msk;

    /* Set SDR and DDR timing. */
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->sdr_drive_timing << R_XSPI0_LIOCFGCS_SDRDRV_Pos) &
              R_XSPI0_LIOCFGCS_SDRDRV_Msk;
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->sdr_sampling_edge << R_XSPI0_LIOCFGCS_SDRSMPMD_Pos) &
              R_XSPI0_LIOCFGCS_SDRSMPMD_Msk;
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->sdr_sampling_delay << R_XSPI0_LIOCFGCS_SDRSMPSFT_Pos) &
              R_XSPI0_LIOCFGCS_SDRSMPSFT_Msk;
    liocfg |= ((uint32_t) p_cfg_extend->p_timing_settings->ddr_sampling_extension << R_XSPI0_LIOCFGCS_DDRSMPEX_Pos) &
              R_XSPI0_LIOCFGCS_DDRSMPEX_Msk;

    /* Set xSPI CSn signal timings. */
    p_reg->LIOCFGCS[p_cfg_extend->channel] = liocfg;

    /* Set xSPI memory-mapping operation. */
    ret = r_ospi_b_protocol_specific_settings(p_instance_ctrl);

    /* Return response after issuing write transaction to xSPI bus, Enable prefetch function and combination if desired. */
    const uint32_t bmcfgch = (0 << R_XSPI0_BMCFGCH_WRMD_Pos) |
                             ((OSPI_B_CFG_COMBINATION_FUNCTION << R_XSPI0_BMCFGCH_MWRCOMB_Pos) &
                              (R_XSPI0_BMCFGCH_MWRCOMB_Msk | R_XSPI0_BMCFGCH_MWRSIZE_Msk)) |
                             ((OSPI_B_CFG_PREFETCH_FUNCTION << R_XSPI0_BMCFGCH_PREEN_Pos) &
                              R_XSPI0_BMCFGCH_PREEN_Msk);

    /* Both of these should have the same configuration and it affects all OSPI slave channels. */
    p_reg->BMCFGCH[0] = bmcfgch;
    p_reg->BMCFGCH[1] = bmcfgch;

    /* Re-activate memory-mapped mode in Read/Write. */
    if (0 == p_instance_ctrl->channel)
    {
        p_reg->BMCTL0 |= R_XSPI0_BMCTL0_CH0CS0ACC_Msk | R_XSPI0_BMCTL0_CH1CS0ACC_Msk;
    }
    else
    {
        p_reg->BMCTL0 |= R_XSPI0_BMCTL0_CH0CS1ACC_Msk | R_XSPI0_BMCTL0_CH1CS1ACC_Msk;
    }

    if (FSP_SUCCESS == ret)
    {
        p_instance_ctrl->open         = OSPI_B_PRV_OPEN;
        g_ospi_b_channels_open_flags |= OSPI_B_PRV_CH_MASK(p_cfg_extend);
    }
    else if (0 == (g_ospi_b_channels_open_flags & OSPI_B_PRV_UNIT_MASK(p_cfg_extend)))
    {
        /* If the open fails and no other channels are open, stop the module. */
        R_BSP_MODULE_STOP(FSP_IP_OSPI, p_cfg_extend->ospi_b_unit);
    }
    else
    {
        // Do nothing.
    }

    return ret;
}

/*******************************************************************************************************************//**
 * Writes raw data directly to the OctaFlash. API not supported. Use R_OSPI_B_DirectTransfer
 *
 * Implements @ref spi_flash_api_t::directWrite.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_DirectWrite (spi_flash_ctrl_t    * p_ctrl,
                                uint8_t const * const p_src,
                                uint32_t const        bytes,
                                bool const            read_after_write)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_src);
    FSP_PARAMETER_NOT_USED(bytes);
    FSP_PARAMETER_NOT_USED(read_after_write);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Reads raw data directly from the OctaFlash. API not supported. Use R_OSPI_B_DirectTransfer.
 *
 * Implements @ref spi_flash_api_t::directRead.
 *
 * @retval FSP_ERR_UNSUPPORTED         API not supported by OSPI.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_DirectRead (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_dest, uint32_t const bytes)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_dest);
    FSP_PARAMETER_NOT_USED(bytes);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Read/Write raw data directly with the OctaFlash.
 *
 * Implements @ref spi_flash_api_t::directTransfer.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_DirectTransfer (spi_flash_ctrl_t                  * p_ctrl,
                                   spi_flash_direct_transfer_t * const p_transfer,
                                   spi_flash_direct_transfer_dir_t     direction)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_transfer);
    FSP_ASSERT(0 != p_transfer->command_length);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    r_ospi_b_direct_transfer(p_instance_ctrl, p_transfer, direction);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Enters XIP (execute in place) mode.
 *
 * Implements @ref spi_flash_api_t::xipEnter.
 *
 * @retval FSP_SUCCESS                 XiP mode was entered successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_UNSUPPORTED         XiP support is not enabled.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_XipEnter (spi_flash_ctrl_t * p_ctrl)
{
#if OSPI_B_CFG_XIP_SUPPORT_ENABLE
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    r_ospi_b_xip(p_instance_ctrl, true);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Exits XIP (execute in place) mode.
 *
 * Implements @ref spi_flash_api_t::xipExit.
 *
 * @retval FSP_SUCCESS                 XiP mode was entered successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_UNSUPPORTED         XiP support is not enabled.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_XipExit (spi_flash_ctrl_t * p_ctrl)
{
#if OSPI_B_CFG_XIP_SUPPORT_ENABLE
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    r_ospi_b_xip(p_instance_ctrl, false);

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Program a page of data to the flash.
 *
 * Implements @ref spi_flash_api_t::write.
 *
 * @retval FSP_SUCCESS                 The flash was programmed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl, p_dest or p_src is NULL, or byte_count crosses a page boundary.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_INVALID_SIZE        Insufficient space remaining in page or write length is not a multiple of CPU access size when not using the DMAC.
 * @retval FSP_ERR_DEVICE_BUSY         Another Write/Erase transaction is in progress.
 * @retval FSP_ERR_WRITE_FAILED        Write operation failed.
 * @retval FSP_ERR_INVALID_ADDRESS     Destination or source is not aligned to CPU access alignment when not using the DMAC.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_Write (spi_flash_ctrl_t    * p_ctrl,
                          uint8_t const * const p_src,
                          uint8_t * const       p_dest,
                          uint32_t              byte_count)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;
    fsp_err_t                err             = FSP_SUCCESS;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_src);
    FSP_ASSERT(NULL != p_dest);
    FSP_ASSERT(0 != byte_count);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);

    /* Check that space remaining in page is sufficient for requested write size */
    uint32_t page_size   = p_instance_ctrl->p_cfg->page_size_bytes;
    uint32_t page_offset = (uint32_t) p_dest & (page_size - 1);
    FSP_ERROR_RETURN((page_size - page_offset) >= byte_count, FSP_ERR_INVALID_SIZE);

 #if !OSPI_B_CFG_DMAC_SUPPORT_ENABLE
    FSP_ERROR_RETURN((byte_count & (OSPI_B_PRV_CPU_ACCESS_LENGTH - 1)) == 0, FSP_ERR_INVALID_SIZE);
    FSP_ERROR_RETURN(((uint32_t) p_dest & (OSPI_B_PRV_CPU_ACCESS_ALIGNMENT - 1)) == 0, FSP_ERR_INVALID_ADDRESS);
  #if defined(__llvm__) && !defined(__ARMCC_VERSION)

    /* LLVM needs 32-bit aligned data. */
    FSP_ERROR_RETURN(((uint32_t) p_src & (0x3)) == 0, FSP_ERR_INVALID_ADDRESS);
  #endif
 #endif
#endif

    R_XSPI0_Type * const p_reg = p_instance_ctrl->p_reg;

    FSP_ERROR_RETURN(false == r_ospi_b_status_sub(p_instance_ctrl, p_instance_ctrl->p_cfg->write_status_bit),
                     FSP_ERR_DEVICE_BUSY);

#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE
    ospi_b_extended_cfg_t * p_cfg_extend = OSPI_B_PRV_EXTENDED_CFG(p_instance_ctrl);

    /* Setup and start DMAC transfer. */
    transfer_instance_t const * p_transfer = p_cfg_extend->p_lower_lvl_transfer;

    /* Enable Octa-SPI DMA Bufferable Write */
    dmac_extended_cfg_t const * p_dmac_extend = p_transfer->p_cfg->p_extend;
    R_DMAC0_Type              * p_dma_reg     = R_DMAC0 + (sizeof(R_DMAC0_Type) * p_dmac_extend->channel);
    p_dma_reg->DMBWR = R_DMAC0_DMBWR_BWE_Msk;

    /* Update the block-mode transfer settings */
    p_transfer->p_cfg->p_info->p_src  = p_src;
    p_transfer->p_cfg->p_info->p_dest = p_dest;
    p_transfer->p_cfg->p_info->transfer_settings_word_b.size = TRANSFER_SIZE_1_BYTE;
    p_transfer->p_cfg->p_info->transfer_settings_word_b.mode = TRANSFER_MODE_NORMAL;
    p_transfer->p_cfg->p_info->length = (uint16_t) byte_count;
    err = p_transfer->p_api->reconfigure(p_transfer->p_ctrl, p_transfer->p_cfg->p_info);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    r_ospi_b_write_enable(p_instance_ctrl);

    /* Start DMA */
    err = p_transfer->p_api->softwareStart(p_transfer->p_ctrl, TRANSFER_START_MODE_REPEAT);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Wait for DMAC to complete to maintain deterministic processing and backward compatibility */
    volatile transfer_properties_t transfer_properties = {0U};
    err = p_transfer->p_api->infoGet(p_transfer->p_ctrl, (transfer_properties_t *) &transfer_properties);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    while (FSP_SUCCESS == err && transfer_properties.transfer_length_remaining > 0)
    {
        err = p_transfer->p_api->infoGet(p_transfer->p_ctrl, (transfer_properties_t *) &transfer_properties);
        FSP_ERROR_RETURN(FSP_SUCCESS == err, err);
    }

    /* Disable Octa-SPI DMA Bufferable Write */
    p_dma_reg->DMBWR = 0U;

    /* If this number of bytes is less than the combination count, push the data to force a transaction. */
    if (OSPI_B_CFG_COMBINATION_FUNCTION != OSPI_B_COMBINATION_FUNCTION_DISABLE)
    {
        uint8_t combo_bytes = (uint8_t) (2U * ((uint8_t) OSPI_B_CFG_COMBINATION_FUNCTION + 1U));
        if (byte_count < combo_bytes)
        {
            p_reg->BMCTL1 = OSPI_B_PRV_BMCTL1_PUSH_COMBINATION_WRITE_MASK;;
        }
    }

#else
    uint64_t * p_dest64 = (uint64_t *) ((uint32_t) p_dest & ~(OSPI_B_PRV_CPU_ACCESS_ALIGNMENT - 1));
    uint64_t * p_src64  = (uint64_t *) p_src;

    err = r_ospi_b_write_enable(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    while (sizeof(uint64_t) <= byte_count)
    {
        /* When combination function is enabled, xSPI master transmits a xSPI
         * frame with the selected size while the sequential address is incremental. Please read
         * "Combination Function" in the OSPI Operation section of the relevant hardware manual.
         * So Basically Enable command should be
         * sent only once for a single burst(incremented addresses up to set combination size.). */
        *p_dest64 = *p_src64;
        p_dest64++;
        p_src64++;
        byte_count -= sizeof(uint64_t);
    }

    __DMB();

    p_reg->BMCTL1 = OSPI_B_PRV_BMCTL1_PUSH_COMBINATION_WRITE_MASK;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Erase a block or sector of flash.  The byte_count must exactly match one of the erase sizes defined in spi_flash_cfg_t.
 * For chip erase, byte_count must be SPI_FLASH_ERASE_SIZE_CHIP_ERASE.
 *
 * Implements @ref spi_flash_api_t::erase.
 *
 * @retval FSP_SUCCESS                 The command to erase the flash was executed successfully.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_device_address is NULL, byte_count doesn't match an erase
 *                                     size defined in spi_flash_cfg_t, or byte_count is set to 0.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_DEVICE_BUSY         The device is busy.
 * @retval FSP_ERR_WRITE_FAILED        Write operation failed.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_Erase (spi_flash_ctrl_t * p_ctrl, uint8_t * const p_device_address, uint32_t byte_count)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_device_address);
    FSP_ASSERT(0 != byte_count);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    spi_flash_cfg_t const * p_cfg         = p_instance_ctrl->p_cfg;
    uint16_t                erase_command = 0;
    bool send_address = true;

    ospi_b_xspi_command_set_t const * p_cmd_set = p_instance_ctrl->p_cmd_set;

    /* Use the address bytes and MSB mask to convert from system address to chip addresses.
     * This is better than using pointer subtraction because some devices (i.e., SiP) have different start addresses.
     * This method better mimics how memory-mapped addresses are converted in the hardware. */
    uint32_t addr_mask = (uint32_t) (~UINT8_MAX | p_cmd_set->address_msb_mask);          // Start with a full 32-bit mask with the address MSB mask in the lower byte.
    addr_mask <<= 8U * (OSPI_B_PRV_ADDR_BYTES_TO_LENGTH(p_cmd_set->address_bytes) - 1U); // Shift the MSB to the correct position.
    uint32_t chip_address = (uint32_t) ((uint32_t) p_device_address & ~addr_mask);       // Mask off the address bits that aren't needed.

    FSP_ERROR_RETURN(false == r_ospi_b_status_sub(p_instance_ctrl, p_cfg->write_status_bit), FSP_ERR_DEVICE_BUSY);

    /* Select the appropriate erase command from the command set. */
    spi_flash_erase_command_t const * p_erase_list = p_cmd_set->p_erase_commands->p_table;
    const uint8_t erase_list_length                = p_cmd_set->p_erase_commands->length;

    for (uint32_t index = 0; index < erase_list_length; index++)
    {
        /* If requested byte_count is supported by underlying flash, store the command. */
        if (byte_count == p_erase_list[index].size)
        {
            if (SPI_FLASH_ERASE_SIZE_CHIP_ERASE == byte_count)
            {
                /* Don't send address for chip erase. */
                send_address = false;
            }

            erase_command = p_erase_list[index].command;
            break;
        }
    }

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(0U != erase_command);
#endif

    fsp_err_t err = r_ospi_b_write_enable(p_instance_ctrl);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    spi_flash_direct_transfer_t direct_command =
    {
        .command        = erase_command,
        .command_length = (uint8_t) p_cmd_set->command_bytes,
        .address        = chip_address,
        .address_length = (send_address) ? OSPI_B_PRV_ADDR_BYTES_TO_LENGTH(p_cmd_set->address_bytes) : 0U,
        .data_length    = 0,
    };

    r_ospi_b_direct_transfer(p_instance_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);

    /* If prefetch is enabled, make sure the banks aren't being used and flush the prefetch caches after an erase. */
#if OSPI_B_CFG_PREFETCH_FUNCTION
    R_XSPI0_Type * const p_reg = p_instance_ctrl->p_reg;
    FSP_HARDWARE_REGISTER_WAIT((p_reg->COMSTT & OSPI_B_PRV_COMSTT_MEMACCCH_MASK), 0);
    p_reg->BMCTL1 = OSPI_B_PRV_BMCTL1_CLEAR_PREFETCH_MASK;
#endif

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Gets the write or erase status of the flash.
 *
 * Implements @ref spi_flash_api_t::statusGet.
 *
 * @retval FSP_SUCCESS                 The write status is in p_status.
 * @retval FSP_ERR_ASSERTION           p_instance_ctrl or p_status is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_StatusGet (spi_flash_ctrl_t * p_ctrl, spi_flash_status_t * const p_status)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_status);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Read device status. */
    p_status->write_in_progress = r_ospi_b_status_sub(p_instance_ctrl, p_instance_ctrl->p_cfg->write_status_bit);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * Selects the bank to access. Use ospi_b_bank_select_t as the bank value.
 *
 * Implements @ref spi_flash_api_t::bankSet.
 *
 * @retval FSP_ERR_UNSUPPORTED           This function is unsupported.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_BankSet (spi_flash_ctrl_t * p_ctrl, uint32_t bank)
{
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(bank);

    FSP_RETURN(FSP_ERR_UNSUPPORTED);
}

/*******************************************************************************************************************//**
 * Sets the SPI protocol.
 *
 * Implements @ref spi_flash_api_t::spiProtocolSet.
 *
 * @retval FSP_SUCCESS                SPI protocol updated on MPU peripheral.
 * @retval FSP_ERR_ASSERTION          A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN           Driver is not opened.
 * @retval FSP_ERR_CALIBRATE_FAILED   Failed to perform auto-calibrate.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_SpiProtocolSet (spi_flash_ctrl_t * p_ctrl, spi_flash_protocol_t spi_protocol)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* Save the old protocol in case of an undefined command set. */
    spi_flash_protocol_t old_protocol = p_instance_ctrl->spi_protocol;
    p_instance_ctrl->spi_protocol = spi_protocol;

    /* Update the SPI protocol and its associated registers. */
    fsp_err_t err = r_ospi_b_protocol_specific_settings(p_instance_ctrl);

    if (FSP_ERR_INVALID_MODE == err)
    {
        /* Restore the original spi protocol. Nothing else has been changed in this case. */
        p_instance_ctrl->spi_protocol = old_protocol;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Close the OSPI driver module.
 *
 * Implements @ref spi_flash_api_t::close.
 *
 * @retval FSP_SUCCESS             Configuration was successful.
 * @retval FSP_ERR_ASSERTION       p_instance_ctrl is NULL.
 * @retval FSP_ERR_NOT_OPEN        Driver is not opened.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_Close (spi_flash_ctrl_t * p_ctrl)
{
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;
    fsp_err_t                err             = FSP_SUCCESS;

#if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg);
    FSP_ASSERT(NULL != p_instance_ctrl->p_cfg->p_extend);
#endif

    ospi_b_extended_cfg_t * p_cfg_extend = OSPI_B_PRV_EXTENDED_CFG(p_instance_ctrl);

#if OSPI_B_CFG_DMAC_SUPPORT_ENABLE

    /* Initialize transfer instance */
    transfer_instance_t const * p_transfer = p_cfg_extend->p_lower_lvl_transfer;
    p_transfer->p_api->close(p_transfer->p_ctrl);
#endif

    p_instance_ctrl->open         = 0U;
    g_ospi_b_channels_open_flags &= ~OSPI_B_PRV_CH_MASK(p_cfg_extend);

    /* Disable clock to the OSPI block if all channels are closed. */
    if (0 == (g_ospi_b_channels_open_flags & OSPI_B_PRV_UNIT_MASK(p_cfg_extend)))
    {
        R_BSP_MODULE_STOP(FSP_IP_OSPI, p_cfg_extend->ospi_b_unit);
    }

    return err;
}

/*******************************************************************************************************************//**
 * AutoCalibrate the OSPI_B DS signal.
 *
 * Implements @ref spi_flash_api_t::autoCalibrate.
 *
 * @retval FSP_SUCCESS                 Autocalibration completed successfully.
 * @retval FSP_ERR_ASSERTION           A required pointer is NULL.
 * @retval FSP_ERR_NOT_OPEN            Driver is not opened.
 * @retval FSP_ERR_UNSUPPORTED         Autocalibration support is not enabled.
 * @retval FSP_ERR_CALIBRATE_FAILED    Failed to perform auto-calibrate.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_AutoCalibrate (spi_flash_ctrl_t * const p_ctrl)
{
#if OSPI_B_CFG_AUTOCALIBRATION_SUPPORT_ENABLE
    ospi_b_instance_ctrl_t * p_instance_ctrl = (ospi_b_instance_ctrl_t *) p_ctrl;

 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
 #endif

    /* Perform Automatic Calibration to appropriately update WRAPCFG DSSFTCSn field. */
    if (OSPI_B_PRV_PROTOCOL_USES_DS_SIGNAL(p_instance_ctrl->spi_protocol))
    {
        return r_ospi_b_automatic_calibration_seq(p_instance_ctrl);
    }

    return FSP_SUCCESS;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * Loads a row into the page buffer on devices which support row addressing.
 *
 * @param[in] p_ctrl    Pointer to a driver handle.
 * @param     row_index Index of the row in the OSPI device.
 *
 * @retval FSP_SUCCESS              Page transaction succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid argument.
 * @retval FSP_ERR_NOT_OPEN         Driver has not been opened.
 * @retval FSP_ERR_UNSUPPORTED      Row addressing support is not enabled
 * @retval FSP_ERR_DEVICE_BUSY      On going asynchronous operation or the device in in XiP mode.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_RowLoad (spi_flash_ctrl_t * const p_ctrl, uint32_t row_index)
{
#if !OSPI_B_CFG_ROW_ADDRESSING_SUPPORT_ENABLE
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(row_index);

    return FSP_ERR_UNSUPPORTED;
#else
 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == ((ospi_b_instance_ctrl_t *) p_ctrl)->open, FSP_ERR_NOT_OPEN);

    ospi_b_extended_cfg_t * const p_extend_cfg = OSPI_B_PRV_EXTENDED_CFG(p_ctrl);
    FSP_ERROR_RETURN(row_index < (1ULL << (8U * OSPI_B_PRV_ADDR_BYTES_TO_LENGTH(p_extend_cfg->row_index_bytes))),
                     FSP_ERR_INVALID_ARGUMENT);
 #endif

    r_ospi_b_row_load_store((ospi_b_instance_ctrl_t *) p_ctrl, row_index, false);

    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 * Stores (programs) the page buffer to a row on devices which support row addressing.
 *
 * @param[in] p_ctrl    Pointer to a driver handle.
 * @param     row_index Index of the row in the OSPI device.
 *
 * @retval FSP_SUCCESS              Page transaction succeeded.
 * @retval FSP_ERR_INVALID_ARGUMENT Invalid argument.
 * @retval FSP_ERR_NOT_OPEN         Driver has not been opened.
 * @retval FSP_ERR_UNSUPPORTED      Row addressing support is not enabled
 * @retval FSP_ERR_DEVICE_BUSY      On going asynchronous operation or the device in in XiP mode.
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_RowStore (spi_flash_ctrl_t * const p_ctrl, uint32_t row_index)
{
#if !OSPI_B_CFG_ROW_ADDRESSING_SUPPORT_ENABLE
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(row_index);

    return FSP_ERR_UNSUPPORTED;
#else
 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == ((ospi_b_instance_ctrl_t *) p_ctrl)->open, FSP_ERR_NOT_OPEN);

    ospi_b_extended_cfg_t * const p_extend_cfg = OSPI_B_PRV_EXTENDED_CFG(p_ctrl);
    FSP_ERROR_RETURN(row_index < (1ULL << (8U * OSPI_B_PRV_ADDR_BYTES_TO_LENGTH(p_extend_cfg->row_index_bytes))),
                     FSP_ERR_INVALID_ARGUMENT);
 #endif

    r_ospi_b_row_load_store((ospi_b_instance_ctrl_t *) p_ctrl, row_index, true);

    return FSP_SUCCESS;
#endif
}

/*******************************************************************************************************************//**
 * Configure DOTF
 *
 * @param[in]   p_ctrl                          Pointer to OSPI specific control structure
 * @param[in]   p_dotf_cfg                      Pointer to DOTF configuration structure
 *
 * @retval      FSP_SUCCESS                     DOTF enabled successfully
 * @retval      FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL Key initialization failed.
 * @retval      FSP_ERR_CRYPTO_SCE_FAIL         Key wrapping failed.
 * @retval      FSP_ERR_INVALID_ARGUMENT        Invalid key type argument.
 * @retval      FSP_ERR_UNSUPPORTED             DOTF support is not enabled
 **********************************************************************************************************************/
fsp_err_t R_OSPI_B_DOTF_Configure (spi_flash_ctrl_t * const p_ctrl, ospi_b_dotf_cfg_t * const p_dotf_cfg)
{
#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE
    fsp_err_t ret = FSP_SUCCESS;

 #if OSPI_B_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_ctrl);
    FSP_ASSERT(NULL != p_dotf_cfg);
    FSP_ERROR_RETURN(OSPI_B_PRV_OPEN == ((ospi_b_instance_ctrl_t *) p_ctrl)->open, FSP_ERR_NOT_OPEN);
 #endif

    ospi_b_extended_cfg_t * p_cfg_extend = OSPI_B_PRV_EXTENDED_CFG(p_ctrl);

    if (NULL != p_dotf_cfg)
    {
        ret = r_ospi_b_dotf_setup(p_cfg_extend->ospi_b_unit, p_dotf_cfg);
        if (FSP_SUCCESS != ret)
        {
            /* If the DOTF initialization fails, stop the module if no other channels are active. */
            if (0 == (g_ospi_b_channels_open_flags & OSPI_B_PRV_UNIT_MASK(p_cfg_extend)))
            {
                R_BSP_MODULE_STOP(FSP_IP_OSPI, p_cfg_extend->ospi_b_unit);
            }
        }
    }

    return ret;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(p_dotf_cfg);

    return FSP_ERR_UNSUPPORTED;
#endif
}

/*******************************************************************************************************************//**
 * @} (end addtogroup OSPI)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Perform initialization based on SPI/OPI protocol
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 *
 * @retval      FSP_SUCCESS                Protocol based settings completed successfully.
 * @retval      FSP_ERR_CALIBRATE_FAILED   Auto-Calibration failed.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_protocol_specific_settings (ospi_b_instance_ctrl_t * p_instance_ctrl)
{
    R_XSPI0_Type * const p_reg = p_instance_ctrl->p_reg;
    fsp_err_t            ret   = FSP_SUCCESS;

    /* Get the command set for the configured protocol and save it to the control struct. */
    ospi_b_xspi_command_set_t const * p_cmd_set = r_ospi_b_command_set_get(p_instance_ctrl);
    FSP_ERROR_RETURN(NULL != p_cmd_set, FSP_ERR_INVALID_MODE);

    p_instance_ctrl->p_cmd_set = p_cmd_set;

    /* Update the SPI protocol and latency mode. */
    uint32_t liocfg = p_reg->LIOCFGCS[p_instance_ctrl->channel] &
                      ~(R_XSPI0_LIOCFGCS_LATEMD_Msk | R_XSPI0_LIOCFGCS_PRTMD_Msk);
    liocfg |= (((uint32_t) p_instance_ctrl->spi_protocol << R_XSPI0_LIOCFGCS_PRTMD_Pos) & R_XSPI0_LIOCFGCS_PRTMD_Msk);
    liocfg |= (((uint32_t) p_cmd_set->latency_mode << R_XSPI0_LIOCFGCS_LATEMD_Pos) & R_XSPI0_LIOCFGCS_LATEMD_Msk);
    p_reg->LIOCFGCS[p_instance_ctrl->channel] = liocfg;

    /* Specifies the read/write commands and Read dummy clocks for Device
     * (see "Flow of Memory-mapping" in the OSPI section of the relevant hardware manual). */
    uint32_t cmcfg0 = ((uint32_t) (p_cmd_set->address_msb_mask << R_XSPI0_CMCFGCS_CMCFG0_ADDRPEN_Pos)) |
                      ((uint32_t) (p_cmd_set->frame_format << R_XSPI0_CMCFGCS_CMCFG0_FFMT_Pos)) |
                      (((uint32_t) p_cmd_set->address_bytes << R_XSPI0_CMCFGCS_CMCFG0_ADDSIZE_Pos) &
                       R_XSPI0_CMCFGCS_CMCFG0_ADDSIZE_Msk);

    /* When using 4-byte addressing, always mask off the most-significant nybble to remove the system bus offset from
     * the transmitted addresses. Ex. CS1 starts at 0x9000_0000 so it needs to mask off bits [31:28]. */
    if (p_cmd_set->address_bytes == SPI_FLASH_ADDRESS_BYTES_4)
    {
        cmcfg0 |= OSPI_B_PRV_ADDRESS_REPLACE_ENABLE_BITS;
    }

    /* Apply the frame format setting and update the register. */
    cmcfg0 |= (uint32_t) (p_cmd_set->frame_format << R_XSPI0_CMCFGCS_CMCFG0_FFMT_Pos);
    p_reg->CMCFGCS[p_instance_ctrl->channel].CMCFG0 = cmcfg0;

    /* Cache the appropriate command values for later use. */
    uint16_t read_command  = p_cmd_set->read_command;
    uint16_t write_command = p_cmd_set->program_command;

    /* If no length is specified or if the command byte length is 1, move the command to the upper byte. */
    if (OSPI_B_COMMAND_BYTES_1 == p_cmd_set->command_bytes)
    {
        read_command =
            (uint16_t) ((read_command & OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK) << OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_SHIFT);
        write_command =
            (uint16_t) ((write_command & OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK) << OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_SHIFT);
    }

    const uint8_t read_dummy_cycles  = p_cmd_set->read_dummy_cycles;
    const uint8_t write_dummy_cycles = p_cmd_set->program_dummy_cycles;

    p_reg->CMCFGCS[p_instance_ctrl->channel].CMCFG1 =
        (uint32_t) (((uint32_t) (read_command) << R_XSPI0_CMCFGCS_CMCFG1_RDCMD_Pos) |
                    ((uint32_t) (read_dummy_cycles << R_XSPI0_CMCFGCS_CMCFG1_RDLATE_Pos) &
                     R_XSPI0_CMCFGCS_CMCFG1_RDLATE_Msk));

    p_reg->CMCFGCS[p_instance_ctrl->channel].CMCFG2 =
        (uint32_t) (((uint32_t) (write_command) << R_XSPI0_CMCFGCS_CMCFG2_WRCMD_Pos) |
                    ((uint32_t) (write_dummy_cycles << R_XSPI0_CMCFGCS_CMCFG2_WRLATE_Pos) &
                     R_XSPI0_CMCFGCS_CMCFG2_WRLATE_Msk));

#if OSPI_B_CFG_AUTOCALIBRATION_SUPPORT_ENABLE
    ospi_b_extended_cfg_t * p_cfg_extend = OSPI_B_PRV_EXTENDED_CFG(p_instance_ctrl);

    /* Perform Automatic Calibration to appropriately update WRAPCFG DSSFTCSn field. */
    if ((0 == p_cfg_extend->data_latch_delay_clocks) &&
        OSPI_B_PRV_PROTOCOL_USES_DS_SIGNAL(p_instance_ctrl->spi_protocol))
    {
        ret = r_ospi_b_automatic_calibration_seq(p_instance_ctrl);
    }
#endif

    return ret;
}

/*******************************************************************************************************************//**
 * Gets device status.
 *
 * @param[in]  p_instance_ctrl         Pointer to a driver handle
 * @param[in]  bit_pos                 Write-in-progress bit position
 *
 * @return True if busy, false if not.
 **********************************************************************************************************************/
static bool r_ospi_b_status_sub (ospi_b_instance_ctrl_t * p_instance_ctrl, uint8_t bit_pos)
{
    ospi_b_xspi_command_set_t const * p_cmd_set = p_instance_ctrl->p_cmd_set;

    /* Skip status check if no command was specified. */
    if (0 == p_cmd_set->status_command)
    {
        return false;
    }

    spi_flash_direct_transfer_t direct_command =
    {
        .command        = p_cmd_set->status_command,
        .command_length = (uint8_t) p_cmd_set->command_bytes,
        .address_length = (uint8_t) (p_cmd_set->status_needs_address ?
                                     OSPI_B_PRV_ADDR_BYTES_TO_LENGTH(p_cmd_set->status_address_bytes) : 0U),
        .address      = (p_cmd_set->status_needs_address) ? p_cmd_set->status_address : 0U,
        .data_length  = 1U,
        .dummy_cycles = p_cmd_set->status_dummy_cycles,
    };

    /* 8D-8D-8D mode requires an address for any kind of read. If the address wasn't set by the configuration
     * set it to the general address length. */
    if ((direct_command.address_length != 0) && (SPI_FLASH_PROTOCOL_8D_8D_8D == p_instance_ctrl->spi_protocol))
    {
        direct_command.address_length = OSPI_B_PRV_ADDR_BYTES_TO_LENGTH(p_cmd_set->address_bytes);
    }

    r_ospi_b_direct_transfer(p_instance_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_READ);

    return (direct_command.data >> bit_pos) & 1U;
}

/*******************************************************************************************************************//**
 * Send Write enable command to the OctaFlash
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 *
 * @retval      FSP_SUCCESS         Write enable operation completed.
 * @retval      FSP_ERR_NOT_ENABLED Write enable failed.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_write_enable (ospi_b_instance_ctrl_t * p_instance_ctrl)
{
    ospi_b_xspi_command_set_t const * const p_cmd_set = p_instance_ctrl->p_cmd_set;

    /* If the command is 0x00, then skip sending the write enable. */
    if (0 == p_cmd_set->write_enable_command)
    {
        return FSP_SUCCESS;
    }

    spi_flash_direct_transfer_t direct_command =
    {
        .command        = p_cmd_set->write_enable_command,
        .command_length = (uint8_t) p_cmd_set->command_bytes,
        .address_length = 0,
        .address        = 0,
        .data_length    = 0,
        .dummy_cycles   = 0,
    };

    r_ospi_b_direct_transfer(p_instance_ctrl, &direct_command, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);

    /* In case write enable is not checked, assume write is enabled. */
    bool write_enabled = true;

#if OSPI_B_MAX_WRITE_ENABLE_LOOPS > 0U

    /* Verify write is enabled. */
    for (uint32_t i = 0U; i < OSPI_B_MAX_WRITE_ENABLE_LOOPS; i++)
    {
        write_enabled = r_ospi_b_status_sub(p_instance_ctrl, p_instance_ctrl->p_cfg->write_enable_bit);
        if (write_enabled)
        {
            break;
        }
    }
#endif

    FSP_ERROR_RETURN(write_enabled, FSP_ERR_NOT_ENABLED);

    return FSP_SUCCESS;
}

#if OSPI_B_CFG_AUTOCALIBRATION_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Perform Automatic Calibration
 *
 * @param[in]   p_instance_ctrl    Pointer to OSPI specific control structure
 *
 * @retval      FSP_SUCCESS                Auto-Calibration completed successfully.
 * @retval      FSP_ERR_CALIBRATE_FAILED   Auto-Calibration failed.
 * @retval      FSP_ERR_DEVICE_BUSY        Auto-Calibration is already running.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_automatic_calibration_seq (ospi_b_instance_ctrl_t * p_instance_ctrl)
{
    R_XSPI0_Type * const    p_reg        = p_instance_ctrl->p_reg;
    fsp_err_t               ret          = FSP_SUCCESS;
    ospi_b_extended_cfg_t * p_cfg_extend = OSPI_B_PRV_EXTENDED_CFG(p_instance_ctrl);

    ospi_b_xspi_command_set_t const * p_cmd_set = p_instance_ctrl->p_cmd_set;

    ospi_b_device_number_t channel = p_instance_ctrl->channel;

    /* Check that calibration is not in progress. */
    if (0 != p_reg->CCCTLCS[channel].CCCTL0_b.CAEN)
    {
        return FSP_ERR_DEVICE_BUSY;
    }

    const uint8_t command_bytes     = (uint8_t) p_cmd_set->command_bytes;
    uint16_t      read_command      = p_cmd_set->read_command;
    const uint8_t read_dummy_cycles = p_cmd_set->read_dummy_cycles;
    const uint8_t address_bytes     = OSPI_B_PRV_ADDR_BYTES_TO_LENGTH(p_cmd_set->address_bytes);

    /* If using 1 command byte, shift the read command over as the peripheral expects. */
    if (1U == command_bytes)
    {
        read_command =
            (uint16_t) ((read_command & OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK) <<
                        OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_SHIFT);
    }

    p_reg->CCCTLCS[channel].CCCTL1 =
        (((uint32_t) command_bytes << R_XSPI0_CCCTLCS_CCCTL1_CACMDSIZE_Pos) &
         R_XSPI0_CCCTLCS_CCCTL1_CACMDSIZE_Msk) |
        (((uint32_t) address_bytes << R_XSPI0_CCCTLCS_CCCTL1_CAADDSIZE_Pos) &
         R_XSPI0_CCCTLCS_CCCTL1_CAADDSIZE_Msk) |
        (OSPI_B_PRV_AUTOCALIBRATION_DATA_SIZE << R_XSPI0_CCCTLCS_CCCTL1_CADATASIZE_Pos) |
        (OSPI_B_PRV_AUTOCALIBRATION_LATENCY_CYCLES << R_XSPI0_CCCTLCS_CCCTL1_CAWRLATE_Pos) |
        (((uint32_t) read_dummy_cycles << R_XSPI0_CCCTLCS_CCCTL1_CARDLATE_Pos) &
         R_XSPI0_CCCTLCS_CCCTL1_CARDLATE_Msk);

    p_reg->CCCTLCS[channel].CCCTL2 =
        (((uint32_t) read_command << R_XSPI0_CCCTLCS_CCCTL2_CARDCMD_Pos) &
         R_XSPI0_CCCTLCS_CCCTL2_CARDCMD_Msk);

    p_reg->CCCTLCS[channel].CCCTL3 = (uint32_t) p_cfg_extend->p_autocalibration_preamble_pattern_addr &
                                     OSPI_B_PRV_ADDRESS_REPLACE_MASK;
    p_reg->CCCTLCS[channel].CCCTL4 = OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_0;
    p_reg->CCCTLCS[channel].CCCTL5 = OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_1;
    p_reg->CCCTLCS[channel].CCCTL6 = OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_2;
    p_reg->CCCTLCS[channel].CCCTL7 = OSPI_B_PRV_AUTOCALIBRATION_PREAMBLE_PATTERN_3;

    p_reg->CCCTLCS[channel].CCCTL0 =
        (OSPI_B_PRV_AUTOCALIBRATION_NO_WRITE_CMD << R_XSPI0_CCCTLCS_CCCTL0_CANOWR_Pos) |
        (OSPI_B_PRV_AUTOCALIBRATION_FRAME_INTERVAL <<
            R_XSPI0_CCCTLCS_CCCTL0_CAITV_Pos) |
        (OSPI_B_PRV_AUTOCALIBRATION_SHIFT_DS_END_VALUE <<
            R_XSPI0_CCCTLCS_CCCTL0_CASFTEND_Pos);

    /* Automatic Calibration Enable */
    p_reg->CCCTLCS[channel].CCCTL0_b.CAEN = 1;

    /* Check calibration success or failure. */
    while ((0 == ((p_reg->INTS >> (R_XSPI0_INTS_CASUCCS_Pos + channel)) & 0x01)) &&
           (0 == ((p_reg->INTS >> (R_XSPI0_INTS_CAFAILCS_Pos + channel)) & 0x01)))
    {
        /* Do nothing. */
    }

    /* Disable automatic calibration */
    p_reg->CCCTLCS[channel].CCCTL0_b.CAEN = 0;

    if (1 == ((p_reg->INTS >> (R_XSPI0_INTS_CASUCCS_Pos + channel)) & 0x01))
    {
        /* Clear automatic calibration success status */
        p_reg->INTC = (uint32_t) 1 << (R_XSPI0_INTS_CASUCCS_Pos + channel);
    }
    else if (1 == ((p_reg->INTS >> (R_XSPI0_INTS_CAFAILCS_Pos + channel)) & 0x01))
    {
        ret = FSP_ERR_CALIBRATE_FAILED;

        /* Clear automatic calibration failure status */
        p_reg->INTC = (uint32_t) 1 << (R_XSPI0_INTS_CAFAILCS_Pos + channel);
    }
    else
    {
        /* Do nothing. */
    }

    return ret;
}

#endif

/*******************************************************************************************************************//**
 * Performs direct data transfer with the OctaFlash
 *
 * @param[in]   p_instance_ctrl    Pointer to the instance ctrl struct.
 * @param[in]   p_transfer         Pointer to transfer parameters
 * @param[in]   direction          Read/Write
 **********************************************************************************************************************/
static void r_ospi_b_direct_transfer (ospi_b_instance_ctrl_t            * p_instance_ctrl,
                                      spi_flash_direct_transfer_t * const p_transfer,
                                      spi_flash_direct_transfer_dir_t     direction)
{
    R_XSPI0_Type * const         p_reg   = p_instance_ctrl->p_reg;
    const ospi_b_device_number_t channel = p_instance_ctrl->channel;

    uint32_t cdtbuf0 =
        (((uint32_t) p_transfer->command_length << R_XSPI0_CDBUF_CDT_CMDSIZE_Pos) & R_XSPI0_CDBUF_CDT_CMDSIZE_Msk) |
        (((uint32_t) p_transfer->address_length << R_XSPI0_CDBUF_CDT_ADDSIZE_Pos) & R_XSPI0_CDBUF_CDT_ADDSIZE_Msk) |
        (((uint32_t) p_transfer->data_length << R_XSPI0_CDBUF_CDT_DATASIZE_Pos) & R_XSPI0_CDBUF_CDT_DATASIZE_Msk) |
        (((uint32_t) p_transfer->dummy_cycles << R_XSPI0_CDBUF_CDT_LATE_Pos) & R_XSPI0_CDBUF_CDT_LATE_Msk) |
        (((uint32_t) direction << R_XSPI0_CDBUF_CDT_TRTYPE_Pos) & R_XSPI0_CDBUF_CDT_TRTYPE_Msk);

    cdtbuf0 |= (1 == p_transfer->command_length) ?
               ((p_transfer->command & OSPI_B_PRV_CDTBUF_CMD_1B_VALUE_MASK) << OSPI_B_PRV_CDTBUF_CMD_UPPER_OFFSET) :
               ((p_transfer->command & OSPI_B_PRV_CDTBUF_CMD_2B_VALUE_MASK) << OSPI_B_PRV_CDTBUF_CMD_OFFSET);

    /* Setup the manual command control. Cancel any ongoing transactions, direct mode, set channel, 1 transaction. */
    p_reg->CDCTL0 = ((((uint32_t) channel) << R_XSPI0_CDCTL0_CSSEL_Pos) & R_XSPI0_CDCTL0_CSSEL_Msk);

    /* Direct Read/Write settings
     * (see "Flow of Manual-command Procedure" in the OSPI section of the relevant hardware manual). */
    FSP_HARDWARE_REGISTER_WAIT(p_reg->CDCTL0_b.TRREQ, 0);

    p_reg->CDBUF[0].CDT = cdtbuf0;
    p_reg->CDBUF[0].CDA = p_transfer->address;

    if (SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE == direction)
    {
        p_reg->CDBUF[0].CDD0 = (uint32_t) (p_transfer->data_u64 & UINT32_MAX);
        if (p_transfer->data_length > sizeof(uint32_t))
        {
            p_reg->CDBUF[0].CDD1 = (uint32_t) (p_transfer->data_u64 >> OSPI_B_PRV_UINT32_BITS);
        }
    }

    /* Start the transaction and wait for completion. */
    p_reg->CDCTL0_b.TRREQ = 1;
    FSP_HARDWARE_REGISTER_WAIT(p_reg->CDCTL0_b.TRREQ, 0);

    if (SPI_FLASH_DIRECT_TRANSFER_DIR_READ == direction)
    {
        p_transfer->data_u64 = p_reg->CDBUF[0].CDD0;
        if (p_transfer->data_length > sizeof(uint32_t))
        {
            p_transfer->data_u64 |= (((uint64_t) p_reg->CDBUF[0].CDD1) << OSPI_B_PRV_UINT32_BITS);
        }
    }

    /* Clear interrupt flags. */
    p_reg->INTC = p_reg->INTS;
}

#if OSPI_B_CFG_XIP_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Performs a dummy read from the provided address.
 *
 * Some scenarios, mainly XiP state changes, require a memory-mapped read operation to emit the proper bus symbol. This
 * function will perform a read at the provided address, throw out the result, then toggle b3 of the address. The
 * toggling of b3 ensures the next dummy read will occur at an address that is not currently available in the OSPI_B
 * peripheral's 1-line (8-byte) data read buffer (this is not the same as the prefetch buffer). If the same address is
 * read twice in a row, the peripheral may return the buffered value instead of issuing a new bus transaction.
 *
 * @param[in,out] p_read_address Address as a uint32_t to read dummy data from
 **********************************************************************************************************************/
static void r_ospi_b_dummy_read (uint32_t * p_read_address)
{
    volatile uint64_t dummy_value = 0;

    if (0U != *p_read_address)
    {
        dummy_value     = *((volatile uint64_t *) *p_read_address);
        *p_read_address = ((*p_read_address) ^ 0x08U);
    }

    FSP_PARAMETER_NOT_USED(dummy_value);
}

/*******************************************************************************************************************//**
 * Configures the device to enter or exit XiP mode.
 *
 * @param[in]   p_instance_ctrl    Pointer to the instance ctrl struct.
 * @param[in]   is_entering        true if entering XiP mode, false if exiting.
 **********************************************************************************************************************/
static void r_ospi_b_xip (ospi_b_instance_ctrl_t * p_instance_ctrl, bool is_entering)
{
    R_XSPI0_Type * const    p_reg              = p_instance_ctrl->p_reg;
    const spi_flash_cfg_t * p_cfg              = p_instance_ctrl->p_cfg;
    uint32_t                dummy_read_address = 0;

    /* Get the initial address to perform dummy reads.
     * This is just the first word of the appropriate memory-mapped CS region.*/
    if (0U == p_instance_ctrl->ospi_b_unit)
    {
        dummy_read_address = ((OSPI_B_DEVICE_NUMBER_0 == p_instance_ctrl->channel) ?
                              BSP_OSPI0_CS0_START_ADDRESS :
                              BSP_OSPI0_CS1_START_ADDRESS);
    }
    else if (1U == p_instance_ctrl->ospi_b_unit)
    {
        dummy_read_address = ((OSPI_B_DEVICE_NUMBER_0 == p_instance_ctrl->channel) ?
                              BSP_OSPI1_CS0_START_ADDRESS :
                              BSP_OSPI1_CS1_START_ADDRESS);
    }
    else
    {
        /* Not a valid unit. */
    }

    const uint32_t reg_cmctlch = ((uint32_t) (p_cfg->xip_enter_command << R_XSPI0_CMCTLCH_XIPENCODE_Pos)) |
                                 ((uint32_t) (p_cfg->xip_exit_command << R_XSPI0_CMCTLCH_XIPEXCODE_Pos));

    /* Save the bus bridge config to restore it after the XiP mode change. */
    const uint32_t reg_bmcfgch0 = p_reg->BMCFGCH[0];
    const uint32_t reg_bmcfgch1 = p_reg->BMCFGCH[1];

 #if OSPI_B_CFG_PREFETCH_FUNCTION

    /* Clear the pre-fetch buffer so following reads always send a read transaction to the xSPI memory. */
    p_reg->BMCTL1 = OSPI_B_PRV_BMCTL1_CLEAR_PREFETCH_MASK;

    /* Disable the prefetch buffer. */
    p_reg->BMCFGCH[0] = reg_bmcfgch0 & ~R_XSPI0_BMCFGCH_PREEN_Msk;
    p_reg->BMCFGCH[1] = reg_bmcfgch1 & ~R_XSPI0_BMCFGCH_PREEN_Msk;
 #endif

    if (OSPI_B_COMBINATION_FUNCTION_DISABLE != OSPI_B_CFG_COMBINATION_FUNCTION)
    {
        /* Flush any combination writes before disabling. */
        p_reg->BMCTL1 = OSPI_B_PRV_BMCTL1_PUSH_COMBINATION_WRITE_MASK;
    }

    /* Perform a dummy read before disabling memory mapping. */
    r_ospi_b_dummy_read(&dummy_read_address);

    /* Disable bus bridge buffering. */
    p_reg->BMCFGCH[0] = 0U;
    p_reg->BMCFGCH[1] = 0U;

    /* Wait for any on-going access to complete. */
    FSP_HARDWARE_REGISTER_WAIT((p_reg->COMSTT & OSPI_B_PRV_COMSTT_PENDING_ACTION_MASK), 0);

    if (is_entering)
    {
        /* Change memory-mapping to read-only mode. */
        p_reg->BMCTL0 = OSPI_B_PRV_BMCTL0_READ_ONLY_VALUE;

        /* XiP enter/exit codes are configured only for memory mapped operations and affects both OSPI slave channels. */
        p_reg->CMCTLCH[0] = reg_cmctlch | R_XSPI0_CMCTLCH_XIPEN_Msk;
        p_reg->CMCTLCH[1] = reg_cmctlch | R_XSPI0_CMCTLCH_XIPEN_Msk;

        /* Perform a read to send the enter code. All further reads will use the enter code and will not send a read command code. */
        r_ospi_b_dummy_read(&dummy_read_address);
    }
    else
    {
        /* Disable XiP. The exit code needs to available at this stage. */
        p_reg->CMCTLCH[0] = reg_cmctlch;

        /* Perform a read to send the exit code. */
        r_ospi_b_dummy_read(&dummy_read_address);

        /* Clear all XiP settings. */
        p_reg->CMCTLCH[0] = 0U;
        p_reg->CMCTLCH[1] = 0U;

        /* This read should be without XiP. */
        r_ospi_b_dummy_read(&dummy_read_address);

        /* Change memory-mapping back to R/W mode. */
        p_reg->BMCTL0 = OSPI_B_PRV_BMCTL0_READ_WRITE_VALUE;
    }

    /* Restore bus bridge buffering to the previous state. */
    p_reg->BMCFGCH[0] = reg_bmcfgch0;
    p_reg->BMCFGCH[1] = reg_bmcfgch1;
}

#endif

/*******************************************************************************************************************//**
 * Gets the xspi command set for a protocol mode if it exists.
 *
 * @param[in]   p_instance_ctrl    Pointer to the instance ctrl struct.
 * @return Pointer to the command set, or NULL if it is normal SPI or has not been configured.
 **********************************************************************************************************************/
static ospi_b_xspi_command_set_t const * r_ospi_b_command_set_get (ospi_b_instance_ctrl_t * p_instance_ctrl)
{
    ospi_b_extended_cfg_t * p_cfg_extend = OSPI_B_PRV_EXTENDED_CFG(p_instance_ctrl);

    ospi_b_xspi_command_set_t * p_cmd_set;
    for (uint32_t i = 0; i < p_cfg_extend->p_xspi_command_set->length; i++)
    {
        p_cmd_set = &((ospi_b_xspi_command_set_t *) p_cfg_extend->p_xspi_command_set->p_table)[i];
        if (p_cmd_set->protocol == p_instance_ctrl->spi_protocol)
        {
            return p_cmd_set;
        }
    }

    /* If the protocol isn't found, return NULL. */
    return NULL;
}

#if OSPI_B_CFG_ROW_ADDRESSING_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Handles row load/stores for row addressable OSPI devices.
 * @param[in] p_ctrl    Pointer to the instance constrol struct.
 * @param     row_index Index of the page in the OSPI device.
 * @param     store_row Set to `true` to store the data buffer to a row, `false` to load a row into the buffer.
 *
 **********************************************************************************************************************/
static void r_ospi_b_row_load_store (ospi_b_instance_ctrl_t * const p_ctrl, uint32_t row_index, bool store_row)
{
    ospi_b_extended_cfg_t * const           p_extend_cfg = (ospi_b_extended_cfg_t *) p_ctrl->p_cfg->p_extend;
    ospi_b_xspi_command_set_t const * const p_cmd_set    = p_ctrl->p_cmd_set;
    spi_flash_direct_transfer_t             transfer     =
    {
        .command_length = (uint8_t) p_cmd_set->command_bytes,
        .address        = 0U,
        .address_length = 0U,
        .data           = row_index,
        .data_length    = OSPI_B_PRV_ADDR_BYTES_TO_LENGTH(p_extend_cfg->row_index_bytes)
    };

    if (store_row)
    {
        transfer.command      = p_cmd_set->row_store_command;
        transfer.dummy_cycles = p_cmd_set->row_store_dummy_cycles;
    }
    else
    {
        transfer.command      = p_cmd_set->row_load_command;
        transfer.dummy_cycles = p_cmd_set->row_load_dummy_cycles;
    }

    r_ospi_b_direct_transfer(p_ctrl, &transfer, SPI_FLASH_DIRECT_TRANSFER_DIR_WRITE);
}

#endif

#if OSPI_B_CFG_DOTF_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Configures DOTF side channel seed information
 *
 * @param[out]  p_seed                            Pointer to seed array.
 * @retval      FSP_SUCCESS                       DOTF seed initialization completed successfully.
 * @retval      FSP_ERR_CRYPTO_SCE_FAIL           TRNG generation failed.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_dotf_side_channal_seed_init (uint32_t p_seed[])
{
    uint32_t random_number[4U] = {0};
 #if defined OSPI_B_CFG_DOTF_PROTECTED_MODE_SUPPORT_ENABLE
    fsp_err_t err = gp_rsip_instance->p_api->randomNumberGenerate(gp_rsip_instance->p_ctrl,
                                                                  (uint8_t *) &random_number[0]);
 #else
    fsp_err_t err = HW_SCE_RNG_Read(random_number);
 #endif

    if (FSP_SUCCESS == err)
    {
        p_seed[0] = random_number[0];
        p_seed[1] = (random_number[1] & OSPI_B_PRV_DOTF_SEED_1_SEED_MASK) | OSPI_B_PRV_DOTF_SEED_1_ENABLE_MASK;
    }

    return err;
}

 #if defined OSPI_B_CFG_DOTF_PROTECTED_MODE_SUPPORT_ENABLE

/*******************************************************************************************************************//**
 * Configures the device for DOTF operation.
 *
 * @param[in]   ospi_b_unit                       Which OSPI unit
 * @param[in]   p_dotf_cfg                        Pointer to the DOTF configuration struct.
 * @retval      FSP_SUCCESS                       DOTF configuration completed successfully.
 * @retval      FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL   Key initialization failed.
 * @retval      FSP_ERR_CRYPTO_SCE_FAIL           Key wrapping failed.
 * @retval      FSP_ERR_INVALID_ARGUMENT          Invalid key type argument.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_dotf_setup (uint8_t ospi_b_unit, ospi_b_dotf_cfg_t * p_dotf_cfg)
{
    fsp_err_t sce_ret = FSP_SUCCESS;
    uint32_t  seed[2] = {0};
    FSP_PARAMETER_NOT_USED(ospi_b_unit);

    if (OSPI_B_DOTF_KEY_FORMAT_WRAPPED != p_dotf_cfg->format)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    static uint8_t            wrapped_key_value[RSIP_BYTE_SIZE_WRAPPED_KEY_RSA_4096_PRIVATE];
    static rsip_wrapped_key_t s_wrapped_key = {.p_value = wrapped_key_value};
    rsip_wrapped_key_t      * p_wrapped_key = &s_wrapped_key;

    if (OSPI_B_DOTF_AES_KEY_TYPE_128 == p_dotf_cfg->key_type)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_AES_128;
        memcpy(p_wrapped_key->p_value, p_dotf_cfg->p_key, RSIP_BYTE_SIZE_WRAPPED_KEY_AES_128);
    }
    else if (OSPI_B_DOTF_AES_KEY_TYPE_192 == p_dotf_cfg->key_type)
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }
    else if (OSPI_B_DOTF_AES_KEY_TYPE_256 == p_dotf_cfg->key_type)
    {
        p_wrapped_key->type = RSIP_KEY_TYPE_AES_256;
        memcpy(p_wrapped_key->p_value, p_dotf_cfg->p_key, RSIP_BYTE_SIZE_WRAPPED_KEY_AES_256);
    }
    else
    {
    }

    sce_ret = gp_rsip_instance->p_api->open(gp_rsip_instance->p_ctrl, gp_rsip_instance->p_cfg);
    if (FSP_SUCCESS != sce_ret)
    {
        return sce_ret;
    }

    sce_ret = r_ospi_b_dotf_side_channal_seed_init(seed);
    if (FSP_SUCCESS != sce_ret)
    {
        return sce_ret;
    }

    sce_ret =
        gp_rsip_instance->p_api->otfInit(gp_rsip_instance->p_ctrl, RSIP_OTF_CHANNEL_0, p_wrapped_key,
                                         (uint8_t *) &seed[0]);

    if (FSP_SUCCESS != sce_ret)
    {
        return sce_ret;
    }

    sce_ret = gp_rsip_instance->p_api->close(gp_rsip_instance->p_ctrl);
    if (FSP_SUCCESS != sce_ret)
    {
        return sce_ret;
    }

    if (sce_ret == FSP_SUCCESS)
    {
        /* Disable byte order conversion. */
        R_DOTF->REG00 = (OSPI_B_PRV_DOTF_REG00_RESET_VALUE | R_DOTF_REG00_B09_Msk);

        /* Load the IV. */
        R_DOTF->REG03 = bswap_32big(p_dotf_cfg->p_iv[0]);
        R_DOTF->REG03 = bswap_32big(p_dotf_cfg->p_iv[1]);
        R_DOTF->REG03 = bswap_32big(p_dotf_cfg->p_iv[2]);
        R_DOTF->REG03 = bswap_32big(p_dotf_cfg->p_iv[3]);
    }

    /* Set the end and start area for DOTF conversion in that order to
     * ensure that end address is always higher than start address. */
    R_DOTF->CONVAREAD  = (uint32_t) p_dotf_cfg->p_end_addr;
    R_DOTF->CONVAREAST = (uint32_t) p_dotf_cfg->p_start_addr;

    return sce_ret;
}

 #else

/*******************************************************************************************************************//**
 * Configures the device for DOTF operation.
 *
 * @param[in]   ospi_b_unit                       Which OSPI unit
 * @param[in]   p_dotf_cfg          Pointer to the DOTF configuration struct.
 * @retval      FSP_SUCCESS                       DOTF configuration completed successfully.
 * @retval      FSP_ERR_CRYPTO_SCE_KEY_SET_FAIL   Key initialization failed.
 * @retval      FSP_ERR_CRYPTO_SCE_FAIL           Key wrapping failed.
 * @retval      FSP_ERR_INVALID_ARGUMENT          Invalid key type argument.
 **********************************************************************************************************************/
static fsp_err_t r_ospi_b_dotf_setup (uint8_t ospi_b_unit, ospi_b_dotf_cfg_t * p_dotf_cfg)
{
    fsp_err_t     sce_ret = FSP_SUCCESS;
    uint32_t      unit    = ospi_b_unit;
    uint32_t      seed[2] = {0};
    uint32_t      wrapped_key[HW_SCE_AES256_KEY_INDEX_WORD_SIZE] = {0};
    sce_oem_cmd_t key_cmd = SCE_OEM_CMD_AES128;

    if ((((uint32_t) &(p_dotf_cfg->p_key[0])) & 0x03) && (((uint32_t) &(p_dotf_cfg->p_iv[0])) & 0x03))
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    if (OSPI_B_DOTF_AES_KEY_TYPE_128 == p_dotf_cfg->key_type)
    {
        key_cmd = SCE_OEM_CMD_AES128;
    }
    else if (OSPI_B_DOTF_AES_KEY_TYPE_192 == p_dotf_cfg->key_type)
    {
        key_cmd = SCE_OEM_CMD_AES192;
    }
    else if (OSPI_B_DOTF_AES_KEY_TYPE_256 == p_dotf_cfg->key_type)
    {
        key_cmd = SCE_OEM_CMD_AES256;
    }
    else
    {
        return FSP_ERR_INVALID_ARGUMENT;
    }

    /* Initialize the crypto engine. */
    HW_SCE_McuSpecificInit();

    if (OSPI_B_DOTF_KEY_FORMAT_PLAINTEXT == p_dotf_cfg->format)
    {
        /* Convert plaintext key to wrapped form. */
        sce_ret =
            HW_SCE_GenerateOemKeyIndexPrivate(SCE_OEM_KEY_TYPE_PLAIN,
                                              key_cmd,
                                              NULL,
                                              NULL,
                                              (uint8_t *) p_dotf_cfg->p_key,
                                              (uint32_t *) wrapped_key);
        if (FSP_SUCCESS != sce_ret)
        {
            return sce_ret;
        }
    }
    else
    {
        if (OSPI_B_DOTF_AES_KEY_TYPE_128 == p_dotf_cfg->key_type)
        {
            memcpy(wrapped_key, p_dotf_cfg->p_key, HW_SCE_AES128_KEY_INDEX_WORD_SIZE * 4);
        }
        else if (OSPI_B_DOTF_AES_KEY_TYPE_192 == p_dotf_cfg->key_type)
        {
            memcpy(wrapped_key, p_dotf_cfg->p_key, HW_SCE_AES192_KEY_INDEX_WORD_SIZE * 4);
        }
        else if (OSPI_B_DOTF_AES_KEY_TYPE_256 == p_dotf_cfg->key_type)
        {
            memcpy(wrapped_key, p_dotf_cfg->p_key, HW_SCE_AES256_KEY_INDEX_WORD_SIZE * 4);
        }
        else
        {
        }
    }

    sce_ret = r_ospi_b_dotf_side_channal_seed_init(seed);
    if (FSP_SUCCESS != sce_ret)
    {
        return sce_ret;
    }

    /* Use wrapped key with DOTF AES Engine. */
    if (SCE_OEM_CMD_AES128 == key_cmd)
    {
        sce_ret = HW_SCE_Aes128OutputKeyForDotfSubAdaptor(&unit, wrapped_key, seed);
    }
    else if (SCE_OEM_CMD_AES192 == key_cmd)
    {
        sce_ret = HW_SCE_Aes192OutputKeyForDotfSubAdaptor(&unit, wrapped_key, seed);
    }
    else
    {
        sce_ret = HW_SCE_Aes256OutputKeyForDotfSubAdaptor(&unit, wrapped_key, seed);
    }

    if (sce_ret == FSP_SUCCESS)
    {
        /* Disable byte order conversion. */
        R_DOTF->REG00 = (OSPI_B_PRV_DOTF_REG00_RESET_VALUE | R_DOTF_REG00_B09_Msk);

        /* Load the IV. */
        R_DOTF->REG03 = change_endian_long(p_dotf_cfg->p_iv[0]);
        R_DOTF->REG03 = change_endian_long(p_dotf_cfg->p_iv[1]);
        R_DOTF->REG03 = change_endian_long(p_dotf_cfg->p_iv[2]);
        R_DOTF->REG03 = change_endian_long(p_dotf_cfg->p_iv[3]);
    }

    /* Set the end and start area for DOTF conversion in that order to
     * ensure that end address is always higher than start address. */
    R_DOTF->CONVAREAD  = (uint32_t) p_dotf_cfg->p_end_addr;
    R_DOTF->CONVAREAST = (uint32_t) p_dotf_cfg->p_start_addr;

    return sce_ret;
}

 #endif
#endif
