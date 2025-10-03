/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_DAC_H
#define R_DAC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "bsp_api.h"
#include "r_dac_cfg.h"
#include "r_dac_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/*******************************************************************************************************************//**
 * @addtogroup DAC
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** DAC Reference voltage selection. */
typedef enum e_dac_ref_volt_sel
{
    DAC_VREF_NONE        = 0x00,       ///< No reference voltage selected
    DAC_VREF_AVCC0_AVSS0 = 0x01,       ///< Select AVCC0/AVSS0
    DAC_VREF_IVREF_AVSS0 = 0x03,       ///< Select Internal reference voltage/AVSS0
    DAC_VREF_VREFH_VREFL = 0x06        ///< Select VREFH/VREFL
} dac_ref_volt_sel_t;

/** DAC instance control block. */
typedef struct st_dac_instance_ctrl
{
    uint8_t      channel;                  // DAC channel number
    uint8_t      channel_index;            // Channel index to access bits
    uint32_t     channel_opened;           // DAC Driver ID
    bool         output_amplifier_enabled; // DAC Output amplifier (on selected MCUs) enabled/disabled.
    bool         internal_output_enabled;  // Output provided to internal modules (on selected MCUs) enabled/disabled.
    R_DAC_Type * p_reg;                    // Base register for this channel
} dac_instance_ctrl_t;

/** DAC extended configuration */
typedef struct st_dac_extended_cfg
{
    bool               enable_charge_pump;       ///< Enable DAC charge pump available on selected MCUs.
    bool               output_amplifier_enabled; ///< Output amplifier enable available on selected MCUs.
    bool               internal_output_enabled;  ///< Internal output enable available on selected MCUs.
    dac_data_format_t  data_format;              ///< Data format
    dac_ref_volt_sel_t ref_volt_sel;             ///< Reference voltage selection
} dac_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const dac_api_t g_dac_on_dac;

/** @endcond */

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/
fsp_err_t R_DAC_Open(dac_ctrl_t * p_api_ctrl, dac_cfg_t const * const p_cfg);
fsp_err_t R_DAC_Write(dac_ctrl_t * p_api_ctrl, uint16_t value);
fsp_err_t R_DAC_Start(dac_ctrl_t * p_api_ctrl);
fsp_err_t R_DAC_Stop(dac_ctrl_t * p_api_ctrl);
fsp_err_t R_DAC_Close(dac_ctrl_t * p_api_ctrl);

/*******************************************************************************************************************//**
 * @} (end defgroup DAC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_DAC_H
