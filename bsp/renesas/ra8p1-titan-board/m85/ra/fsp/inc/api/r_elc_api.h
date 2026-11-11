/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_SYSTEM_INTERFACES
 * @defgroup ELC_API ELC Interface
 * @brief Interface for the Event Link Controller.
 *
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_ELC_API_H
#define R_ELC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#ifndef ELC_PERIPHERAL_NUM
 #define ELC_PERIPHERAL_NUM    (23U)
#endif

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#ifndef BSP_OVERRIDE_ELC_PERIPHERAL_T

/** Possible peripherals to be linked to event signals (not all available on all MCUs) */
typedef enum e_elc_peripheral
{
    ELC_PERIPHERAL_GPT_A   = (0),
    ELC_PERIPHERAL_GPT_B   = (1),
    ELC_PERIPHERAL_GPT_C   = (2),
    ELC_PERIPHERAL_GPT_D   = (3),
    ELC_PERIPHERAL_GPT_E   = (4),
    ELC_PERIPHERAL_GPT_F   = (5),
    ELC_PERIPHERAL_GPT_G   = (6),
    ELC_PERIPHERAL_GPT_H   = (7),
    ELC_PERIPHERAL_ADC0    = (8),
    ELC_PERIPHERAL_ADC0_B  = (9),
    ELC_PERIPHERAL_ADC1    = (10),
    ELC_PERIPHERAL_ADC1_B  = (11),
    ELC_PERIPHERAL_DAC0    = (12),
    ELC_PERIPHERAL_DAC1    = (13),
    ELC_PERIPHERAL_IOPORT1 = (14),
    ELC_PERIPHERAL_IOPORT2 = (15),
    ELC_PERIPHERAL_IOPORT3 = (16),
    ELC_PERIPHERAL_IOPORT4 = (17),
    ELC_PERIPHERAL_CTSU    = (18),
    ELC_PERIPHERAL_DA8_0   = (19),
    ELC_PERIPHERAL_DA8_1   = (20),
    ELC_PERIPHERAL_SDADC0  = (22),
} elc_peripheral_t;

#endif

/** ELC control block.  Allocate an instance specific control block to pass into the ELC API calls.
 */
typedef void elc_ctrl_t;

/** Main configuration structure for the Event Link Controller */
typedef struct st_elc_cfg
{
    elc_event_t const link[ELC_PERIPHERAL_NUM]; ///< Event link register settings
    void const      * p_extend;                 ///< Extension parameter for hardware specific settings
} elc_cfg_t;

#ifndef BSP_OVERRIDE_ELC_SOFTWARE_EVENT_T

/** Software event number */
typedef enum e_elc_software_event
{
    ELC_SOFTWARE_EVENT_0,              ///< Software event 0
    ELC_SOFTWARE_EVENT_1,              ///< Software event 1
} elc_software_event_t;

#endif

/** ELC driver structure. General ELC functions implemented at the HAL layer follow this API. */
typedef struct st_elc_api
{
    /** Initialize all links in the Event Link Controller.
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     * @param[in]   p_cfg   Pointer to configuration structure.
     **/
    fsp_err_t (* open)(elc_ctrl_t * const p_ctrl, elc_cfg_t const * const p_cfg);

    /** Disable all links in the Event Link Controller and close the API.
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     **/
    fsp_err_t (* close)(elc_ctrl_t * const p_ctrl);

    /** Generate a software event in the Event Link Controller.
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     * @param[in]   eventNum           Software event number to be generated.
     **/
    fsp_err_t (* softwareEventGenerate)(elc_ctrl_t * const p_ctrl, elc_software_event_t event_num);

    /** Create a single event link.
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     * @param[in]   peripheral The peripheral block that will receive the event signal.
     * @param[in]   signal     The event signal.
     **/
    fsp_err_t (* linkSet)(elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral, elc_event_t signal);

    /** Break an event link.
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     * @param[in]   peripheral   The peripheral that should no longer be linked.
     **/
    fsp_err_t (* linkBreak)(elc_ctrl_t * const p_ctrl, elc_peripheral_t peripheral);

    /** Enable the operation of the Event Link Controller.
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     **/
    fsp_err_t (* enable)(elc_ctrl_t * const p_ctrl);

    /** Disable the operation of the Event Link Controller.
     *
     * @param[in]   p_ctrl  Pointer to control structure.
     **/
    fsp_err_t (* disable)(elc_ctrl_t * const p_ctrl);
} elc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_elc_instance
{
    elc_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    elc_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    elc_api_t const * p_api;           ///< Pointer to the API structure for this instance
} elc_instance_t;

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

/*******************************************************************************************************************//**
 * @} (end defgroup ELC_API)
 **********************************************************************************************************************/
