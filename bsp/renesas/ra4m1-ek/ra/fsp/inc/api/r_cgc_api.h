/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef R_CGC_API_H
#define R_CGC_API_H

/*******************************************************************************************************************//**
 * @ingroup RENESAS_SYSTEM_INTERFACES
 * @defgroup CGC_API CGC Interface
 * @brief Interface for clock generation.
 *
 * @section CGC_API_SUMMARY Summary
 *
 * The CGC interface provides the ability to configure and use all of the CGC module's capabilities. Among the
 * capabilities is the selection of several clock sources to use as the system clock source. Additionally, the
 * system clocks can be divided down to provide a wide range of frequencies for various system and peripheral needs.
 *
 * Clock stability can be checked and clocks may also be stopped to save power when not needed. The API has a function
 * to return the frequency of the system and system peripheral clocks at run time. There is also a feature to detect
 * when the main oscillator has stopped, with the option of calling a user provided callback function.
 *
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Events that can trigger a callback function */
typedef enum e_cgc_event
{
    CGC_EVENT_OSC_STOP_DETECT_NMI      = 0, ///< Main oscillator stop detection has caused the NMI event
    CGC_EVENT_OSC_STOP_DETECT_MAIN_OSC = 1, ///< Main oscillator stop detection has caused the interrupt event
    CGC_EVENT_OSC_STOP_DETECT_SUBCLOCK = 2, ///< Subclock oscillator stop detection has caused the interrupt event
} cgc_event_t;

/** Callback function parameter data */
typedef struct st_cgc_callback_args
{
    cgc_event_t event;                 ///< The event can be used to identify what caused the callback
    void      * p_context;             ///< Placeholder for user data
} cgc_callback_args_t;

#ifndef BSP_OVERRIDE_CGC_CLOCK_T

/** System clock source identifiers -  The source of ICLK, BCLK, FCLK, PCLKS A-D and UCLK prior to the system clock
 * divider */
typedef enum e_cgc_clock
{
    CGC_CLOCK_HOCO     = 0,            ///< The high speed on chip oscillator
    CGC_CLOCK_MOCO     = 1,            ///< The middle speed on chip oscillator
    CGC_CLOCK_LOCO     = 2,            ///< The low speed on chip oscillator
    CGC_CLOCK_MAIN_OSC = 3,            ///< The main oscillator
    CGC_CLOCK_SUBCLOCK = 4,            ///< The subclock oscillator
    CGC_CLOCK_PLL      = 5,            ///< The PLL oscillator
    CGC_CLOCK_PLL2     = 6,            ///< The PLL2 oscillator
} cgc_clock_t;
#endif

/** PLL divider values */
typedef enum e_cgc_pll_div
{
    CGC_PLL_DIV_1 = 0,                 ///< PLL divider of 1
    CGC_PLL_DIV_2 = 1,                 ///< PLL divider of 2
    CGC_PLL_DIV_3 = 2,                 ///< PLL divider of 3
    CGC_PLL_DIV_4 = 3,                 ///< PLL divider of 4
    CGC_PLL_DIV_6 = 5,                 ///< PLL divider of 6
} cgc_pll_div_t;

/** PLL clock output divisor. */
typedef enum e_cgc_pll_out_div
{
    CGC_PLL_OUT_DIV_2   = 2,           ///< PLL output clock divided by 2
    CGC_PLL_OUT_DIV_3   = 3,           ///< PLL output clock divided by 3
    CGC_PLL_OUT_DIV_4   = 4,           ///< PLL output clock divided by 4
    CGC_PLL_OUT_DIV_5   = 5,           ///< PLL output clock divided by 5
    CGC_PLL_OUT_DIV_6   = 6,           ///< PLL output clock divided by 6
    CGC_PLL_OUT_DIV_8   = 8,           ///< PLL output clock divided by 8
    CGC_PLL_OUT_DIV_9   = 9,           ///< PLL output clock divided by 9
    CGC_PLL_OUT_DIV_1_5 = 10,          ///< PLL output clock divided by 1.5
    CGC_PLL_OUT_DIV_16  = 16,          ///< PLL output clock divided by 16
} cgc_pll_out_div_t;

#ifndef BSP_OVERRIDE_CGC_SYS_CLOCK_DIV_T

/** System clock divider values - The individually selectable divider of each of the system clocks, ICLK, BCLK, FCLK,
 * PCLKS A-D.  */
typedef enum e_cgc_sys_clock_div
{
    CGC_SYS_CLOCK_DIV_1  = 0,          ///< System clock divided by 1
    CGC_SYS_CLOCK_DIV_2  = 1,          ///< System clock divided by 2
    CGC_SYS_CLOCK_DIV_4  = 2,          ///< System clock divided by 4
    CGC_SYS_CLOCK_DIV_8  = 3,          ///< System clock divided by 8
    CGC_SYS_CLOCK_DIV_16 = 4,          ///< System clock divided by 16
    CGC_SYS_CLOCK_DIV_32 = 5,          ///< System clock divided by 32
    CGC_SYS_CLOCK_DIV_64 = 6,          ///< System clock divided by 64
    CGC_SYS_CLOCK_DIV_3  = 7,          ///< System clock divided by 3 (BCLK only)
} cgc_sys_clock_div_t;
#endif

#ifndef BSP_OVERRIDE_CGC_PLL_CFG_T

/** Clock configuration structure - Used as an input parameter to the @ref cgc_api_t::clockStart function for the PLL clock. */
typedef struct st_cgc_pll_cfg
{
    cgc_clock_t       source_clock;    ///< PLL source clock (main oscillator or HOCO)
    cgc_pll_div_t     divider;         ///< PLL divider
    cgc_pll_mul_t     multiplier;      ///< PLL multiplier
    cgc_pll_out_div_t out_div_p;       ///< PLL divisor for output clock P
    cgc_pll_out_div_t out_div_q;       ///< PLL divisor for output clock Q
    cgc_pll_out_div_t out_div_r;       ///< PLL divisor for output clock R
} cgc_pll_cfg_t;
#endif

#ifndef BSP_OVERRIDE_CGC_PIN_OUTPUT_CONTROL_T

/**  Pin output control enable/disable (SDCLK, BCLK). */
typedef enum e_cgc_pin_output_control
{
    CGC_PIN_OUTPUT_CONTROL_ENABLE  = 0, ///< Enable pin output
    CGC_PIN_OUTPUT_CONTROL_DISABLE = 1  ///< Disable pin output
} cgc_pin_output_control_t;

#endif

#ifndef BSP_OVERRIDE_CGC_DIVIDER_CFG_T

/** Clock configuration structure - Used as an input parameter to the @ref cgc_api_t::systemClockSet and @ref cgc_api_t::systemClockGet
 * functions. */
typedef struct st_cgc_divider_cfg
{
    union
    {
        uint32_t sckdivcr_w;                   ///< System clock Division control register

        struct
        {
            cgc_sys_clock_div_t pclkd_div : 4; ///< Divider value for PCLKD
            cgc_sys_clock_div_t pclkc_div : 4; ///< Divider value for PCLKC
            cgc_sys_clock_div_t pclkb_div : 4; ///< Divider value for PCLKB
            cgc_sys_clock_div_t pclka_div : 4; ///< Divider value for PCLKA
            cgc_sys_clock_div_t bclk_div  : 4; ///< Divider value for BCLK
            cgc_sys_clock_div_t pclke_div : 4; ///< Divider value for PCLKE
            cgc_sys_clock_div_t iclk_div  : 4; ///< Divider value for ICLK
            cgc_sys_clock_div_t fclk_div  : 4; ///< Divider value for FCLK
        } sckdivcr_b;
    };

    union
    {
        uint8_t sckdivcr2;                      ///< System clock Division control register 2

        struct
        {
            cgc_sys_clock_div_t cpuclk_div : 4; ///< Divider value for CPUCLK
            uint8_t             reserved   : 4;
        } sckdivcr2_b;
    };
} cgc_divider_cfg_t;
#endif

#ifndef BSP_OVERRIDE_CGC_USB_CLOCK_DIV_T

/** USB clock divider values */
typedef enum e_cgc_usb_clock_div
{
    CGC_USB_CLOCK_DIV_2 = 1,           ///< Divide USB source clock by 2
    CGC_USB_CLOCK_DIV_3 = 2,           ///< Divide USB source clock by 3
    CGC_USB_CLOCK_DIV_4 = 3,           ///< Divide USB source clock by 4
    CGC_USB_CLOCK_DIV_5 = 4,           ///< Divide USB source clock by 5
} cgc_usb_clock_div_t;
#endif

#ifndef BSP_OVERRIDE_CGC_CLOCK_CHANGE_T

/** Clock options */
typedef enum e_cgc_clock_change
{
    CGC_CLOCK_CHANGE_START = 0,        ///< Start the clock
    CGC_CLOCK_CHANGE_STOP  = 1,        ///< Stop the clock
    CGC_CLOCK_CHANGE_NONE  = 2,        ///< No change to the clock
} cgc_clock_change_t;
#endif

/** CGC control block.  Allocate an instance specific control block to pass into the CGC API calls.
 */
typedef void cgc_ctrl_t;

/** Configuration options. */
typedef struct st_cgc_cfg
{
    void (* p_callback)(cgc_callback_args_t * p_args);
    void       * p_context;
    void const * p_extend;             ///< Extension parameter for hardware specific settings.
} cgc_cfg_t;

#ifndef BSP_OVERRIDE_CGC_CLOCKS_CFG_T

/** Clock configuration */
typedef struct st_cgc_clocks_cfg
{
    cgc_clock_t        system_clock;   ///< System clock source enumeration
    cgc_pll_cfg_t      pll_cfg;        ///< PLL configuration structure
    cgc_pll_cfg_t      pll2_cfg;       ///< PLL2 configuration structure
    cgc_divider_cfg_t  divider_cfg;    ///< Clock dividers structure
    cgc_clock_change_t loco_state;     ///< State of LOCO
    cgc_clock_change_t moco_state;     ///< State of MOCO
    cgc_clock_change_t hoco_state;     ///< State of HOCO
    cgc_clock_change_t mainosc_state;  ///< State of Main oscillator
    cgc_clock_change_t pll_state;      ///< State of PLL
    cgc_clock_change_t pll2_state;     ///< State of PLL2
    cgc_clock_change_t subosc_state;   ///< State of Sub oscillator
} cgc_clocks_cfg_t;
#endif

/** CGC functions implemented at the HAL layer follow this API. */
typedef struct
{
    /** Initial configuration
     * @param[in]   p_ctrl         Pointer to instance control block
     * @param[in]   p_cfg          Pointer to configuration
     */
    fsp_err_t (* open)(cgc_ctrl_t * const p_ctrl, cgc_cfg_t const * const p_cfg);

    /** Configure all system clocks.
     * @param[in]   p_ctrl         Pointer to instance control block
     * @param[in]   p_clock_cfg    Pointer to desired configuration of system clocks
     */
    fsp_err_t (* clocksCfg)(cgc_ctrl_t * const p_ctrl, cgc_clocks_cfg_t const * const p_clock_cfg);

    /** Start a clock.
     * @param[in]   p_ctrl         Pointer to instance control block
     * @param[in]   clock_source   Clock source to start
     * @param[in]   p_pll_cfg      Pointer to PLL configuration, can be NULL if clock_source is not CGC_CLOCK_PLL or
     *                             CGC_CLOCK_PLL2
     */
    fsp_err_t (* clockStart)(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source,
                             cgc_pll_cfg_t const * const p_pll_cfg);

    /** Stop a clock.
     * @param[in]   p_ctrl         Pointer to instance control block
     * @param[in]   clock_source   The clock source to stop
     */
    fsp_err_t (* clockStop)(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source);

    /** Check the stability of the selected clock.
     * @param[in]   p_ctrl         Pointer to instance control block
     * @param[in]   clock_source   Which clock source to check for stability
     */
    fsp_err_t (* clockCheck)(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source);

    /** Set the system clock.
     * @param[in]   p_ctrl         Pointer to instance control block
     * @param[in]   clock_source   Clock source to set as system clock
     * @param[in]   p_divider_cfg  Pointer to the clock divider configuration
     */
    fsp_err_t (* systemClockSet)(cgc_ctrl_t * const p_ctrl, cgc_clock_t clock_source,
                                 cgc_divider_cfg_t const * const p_divider_cfg);

    /** Get the system clock information.
     * @param[in]   p_ctrl          Pointer to instance control block
     * @param[out]  p_clock_source  Returns the current system clock
     * @param[out]  p_divider_cfg   Returns the current system clock dividers
     */
    fsp_err_t (* systemClockGet)(cgc_ctrl_t * const p_ctrl, cgc_clock_t * const p_clock_source,
                                 cgc_divider_cfg_t * const p_divider_cfg);

    /** Enable and optionally register a callback for Main Oscillator stop detection.
     * @param[in]   p_ctrl       Pointer to instance control block
     */
    fsp_err_t (* oscStopDetectEnable)(cgc_ctrl_t * const p_ctrl);

    /** Disable Main Oscillator stop detection.
     * @param[in]   p_ctrl          Pointer to instance control block
     */
    fsp_err_t (* oscStopDetectDisable)(cgc_ctrl_t * const p_ctrl);

    /** Clear the oscillator stop detection flag.
     * @param[in]   p_ctrl          Pointer to instance control block
     */
    fsp_err_t (* oscStopStatusClear)(cgc_ctrl_t * const p_ctrl);

    /**
     * Specify callback function and optional context pointer and working memory pointer.
     *
     * @param[in]   p_ctrl                   Pointer to the CGC control block.
     * @param[in]   p_callback               Callback function
     * @param[in]   p_context                Pointer to send to callback function
     * @param[in]   p_working_memory         Pointer to volatile memory where callback structure can be allocated.
     *                                       Callback arguments allocated here are only valid during the callback.
     */
    fsp_err_t (* callbackSet)(cgc_ctrl_t * const p_ctrl, void (* p_callback)(cgc_callback_args_t *),
                              void * const p_context, cgc_callback_args_t * const p_callback_memory);

    /** Close the CGC driver.
     * @param[in]   p_ctrl          Pointer to instance control block
     */
    fsp_err_t (* close)(cgc_ctrl_t * const p_ctrl);
} cgc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_cgc_instance
{
    cgc_ctrl_t      * p_ctrl;          ///< Pointer to the control structure for this instance
    cgc_cfg_t const * p_cfg;           ///< Pointer to the configuration structure for this instance
    cgc_api_t const * p_api;           ///< Pointer to the API structure for this instance
} cgc_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup CGC_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_CGC_API_H
