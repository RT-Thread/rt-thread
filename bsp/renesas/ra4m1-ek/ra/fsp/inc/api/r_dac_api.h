/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_ANALOG_INTERFACES
 * @defgroup DAC_API DAC Interface
 * @brief Interface for D/A converters.
 *
 * @section DAC_API_SUMMARY Summary
 * The DAC interface provides standard Digital/Analog Converter functionality.  A DAC application writes digital
 * sample data to the device and generates analog output on the DAC output pin.
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_DAC_API_H
#define R_DAC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common error codes and definitions. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DAC Open API data format settings. */
typedef enum e_dac_data_format
{
    DAC_DATA_FORMAT_FLUSH_RIGHT = 0,   ///< LSB of data is flush to the right leaving the top 4 bits unused.
    DAC_DATA_FORMAT_FLUSH_LEFT  = 1    ///< MSB of data is flush to the left leaving the bottom 4 bits unused.
} dac_data_format_t;

/** DAC information structure to store various information for a DAC */
typedef struct dac_info
{
    uint8_t bit_width;                 ///< Resolution of the DAC.
} dac_info_t;

/** DAC Open API configuration parameter */
typedef struct st_dac_cfg
{
    uint8_t      channel;              ///< ID associated with this DAC channel
    bool         ad_da_synchronized;   ///< AD/DA synchronization
    void const * p_extend;
} dac_cfg_t;

/** DAC control block.  Allocate an instance specific control block to pass into the DAC API calls.
 */
typedef void dac_ctrl_t;

/** DAC driver structure.  General DAC functions implemented at the HAL layer follow this API. */
typedef struct st_dac_api
{
    /** Initial configuration.
     *
     * @param[in]   p_ctrl     Pointer to control block. Must be declared by user. Elements set here.
     * @param[in]   p_cfg      Pointer to configuration structure. All elements of this structure must be set by user.
     */
    fsp_err_t (* open)(dac_ctrl_t * const p_ctrl, dac_cfg_t const * const p_cfg);

    /** Close the D/A Converter.
     *
     * @param[in]   p_ctrl     Control block set in @ref dac_api_t::open call for this timer.
     */
    fsp_err_t (* close)(dac_ctrl_t * const p_ctrl);

    /** Write sample value to the D/A Converter.
     *
     * @param[in]   p_ctrl     Control block set in @ref dac_api_t::open call for this timer.
     * @param[in]   value      Sample value to be written to the D/A Converter.
     */
    fsp_err_t (* write)(dac_ctrl_t * const p_ctrl, uint16_t value);

    /** Start the D/A Converter if it has not been started yet.
     *
     * @param[in]   p_ctrl     Control block set in @ref dac_api_t::open call for this timer.
     */
    fsp_err_t (* start)(dac_ctrl_t * const p_ctrl);

    /** Stop the D/A Converter if the converter is running.
     *
     * @param[in]   p_ctrl     Control block set in @ref dac_api_t::open call for this timer.
     */
    fsp_err_t (* stop)(dac_ctrl_t * const p_ctrl);
} dac_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_dac_instance
{
    dac_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    dac_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    dac_api_t const * p_api;           ///< Pointer to the API structure for this instance
} dac_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup DAC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
