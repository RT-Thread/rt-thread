/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup GLCDC
 * @{
 **********************************************************************************************************************/

#ifndef R_GLCDC_H
#define R_GLCDC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_display_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Display control block.  DO NOT INITIALIZE. */
typedef struct st_glcdc_instance_ctrl
{
    display_state_t state;                                 // Status of GLCDC module

    /* Parameters to Event processing for display devices */
    void (* p_callback)(display_callback_args_t * p_args); // Pointer to callback function
    void const          * p_context;                       // Pointer to the higher level device context
    const display_cfg_t * p_cfg;                           // Pointer to initial configurations
} glcdc_instance_ctrl_t;

/** Clock source select */
typedef enum e_glcdc_clk_src
{
    GLCDC_CLK_SRC_INTERNAL,            ///< Internal
    GLCDC_CLK_SRC_EXTERNAL,            ///< External
} glcdc_clk_src_t;

/** Clock frequency division ratio */
typedef enum e_glcdc_panel_clk_div
{
    GLCDC_PANEL_CLK_DIVISOR_1  = 1,    ///< Division Ratio 1/1
    GLCDC_PANEL_CLK_DIVISOR_2  = 2,    ///< Division Ratio 1/2
    GLCDC_PANEL_CLK_DIVISOR_3  = 3,    ///< Division Ratio 1/3
    GLCDC_PANEL_CLK_DIVISOR_4  = 4,    ///< Division Ratio 1/4
    GLCDC_PANEL_CLK_DIVISOR_5  = 5,    ///< Division Ratio 1/5
    GLCDC_PANEL_CLK_DIVISOR_6  = 6,    ///< Division Ratio 1/6
    GLCDC_PANEL_CLK_DIVISOR_7  = 7,    ///< Division Ratio 1/7
    GLCDC_PANEL_CLK_DIVISOR_8  = 8,    ///< Division Ratio 1/8
    GLCDC_PANEL_CLK_DIVISOR_9  = 9,    ///< Division Ratio 1/9
    GLCDC_PANEL_CLK_DIVISOR_12 = 12,   ///< Division Ratio 1/12
    GLCDC_PANEL_CLK_DIVISOR_16 = 16,   ///< Division Ratio 1/16
    GLCDC_PANEL_CLK_DIVISOR_24 = 24,   ///< Division Ratio 1/24
    GLCDC_PANEL_CLK_DIVISOR_32 = 32,   ///< Division Ratio 1/32
} glcdc_panel_clk_div_t;

/** LCD TCON output pin select */
typedef enum e_glcdc_tcon_pin
{
    GLCDC_TCON_PIN_NONE = -1,          ///< No output
    GLCDC_TCON_PIN_0,                  ///< LCD_TCON0
    GLCDC_TCON_PIN_1,                  ///< LCD_TCON1
    GLCDC_TCON_PIN_2,                  ///< LCD_TCON2
    GLCDC_TCON_PIN_3,                  ///< LCD_TCON3
} glcdc_tcon_pin_t;

/** Bus Arbitration setting */
typedef enum e_glcdc_bus_arbitraion
{
    GLCDC_BUS_ARBITRATION_ROUNDROBIN,  ///< Round robin
    GLCDC_BUS_ARBITRATION_FIX_PRIORITY ///< Fixed
} glcdc_bus_arbitration_t;

/** Correction circuit sequence control */
typedef enum e_glcdc_correction_proc_order
{
    GLCDC_CORRECTION_PROC_ORDER_BRIGHTNESS_CONTRAST2GAMMA, ///< Brightness -> contrast -> gamma correction
    GLCDC_CORRECTION_PROC_ORDER_GAMMA2BRIGHTNESS_CONTRAST  ///< Gamma correction -> brightness -> contrast
} glcdc_correction_proc_order_t;

/** Timing signals for driving the LCD panel */
typedef enum e_glcdc_tcon_signal_select
{
    GLCDC_TCON_SIGNAL_SELECT_STVA_VS = 0, ///< STVA/VS
    GLCDC_TCON_SIGNAL_SELECT_STVB_VE = 1, ///< STVB/VE
    GLCDC_TCON_SIGNAL_SELECT_STHA_HS = 2, ///< STH/SP/HS
    GLCDC_TCON_SIGNAL_SELECT_STHB_HE = 3, ///< STB/LP/HE
    GLCDC_TCON_SIGNAL_SELECT_DE      = 7  ///< DE
} glcdc_tcon_signal_select_t;

/** Clock phase adjustment for serial RGB output */
typedef enum e_glcdc_clut_plane
{
    GLCDC_CLUT_PLANE_0 = 0,            ///< GLCDC CLUT plane 0
    GLCDC_CLUT_PLANE_1 = 1,            ///< GLCDC CLUT plane 1
} glcdc_clut_plane_t;

/** Dithering mode */
typedef enum e_glcdc_dithering_mode
{
    GLCDC_DITHERING_MODE_TRUNCATE   = 0, ///< No dithering (truncate)
    GLCDC_DITHERING_MODE_ROUND_OFF  = 1, ///< Dithering with round off
    GLCDC_DITHERING_MODE_2X2PATTERN = 2, ///< Dithering with 2x2 pattern
    GLCDC_DITHERING_MODE_SETTING_MAX
} glcdc_dithering_mode_t;

/** Dithering mode */
typedef enum e_glcdc_dithering_pattern
{
    GLCDC_DITHERING_PATTERN_00 = 0,    ///< 2x2 pattern '00'
    GLCDC_DITHERING_PATTERN_01 = 1,    ///< 2x2 pattern '01'
    GLCDC_DITHERING_PATTERN_10 = 2,    ///< 2x2 pattern '10'
    GLCDC_DITHERING_PATTERN_11 = 3,    ///< 2x2 pattern '11'
} glcdc_dithering_pattern_t;

/** Output interface format */
typedef enum e_glcdc_input_interface_format
{
    GLCDC_INPUT_INTERFACE_FORMAT_RGB565   = 0, ///< Input interface format RGB565
    GLCDC_INPUT_INTERFACE_FORMAT_RGB888   = 1, ///< Input interface format RGB888
    GLCDC_INPUT_INTERFACE_FORMAT_ARGB1555 = 2, ///< Input interface format ARGB1555
    GLCDC_INPUT_INTERFACE_FORMAT_ARGB4444 = 3, ///< Input interface format ARGB4444
    GLCDC_INPUT_INTERFACE_FORMAT_ARGB8888 = 4, ///< Input interface format ARGB8888
    GLCDC_INPUT_INTERFACE_FORMAT_CLUT8    = 5, ///< Input interface format CLUT8
    GLCDC_INPUT_INTERFACE_FORMAT_CLUT4    = 6, ///< Input interface format CLUT4
    GLCDC_INPUT_INTERFACE_FORMAT_CLUT1    = 7, ///< Input interface format CLUT1
} glcdc_input_interface_format_t;

/** Output interface format */
typedef enum e_glcdc_output_interface_format
{
    GLCDC_OUTPUT_INTERFACE_FORMAT_RGB888     = 0, ///< Output interface format RGB888
    GLCDC_OUTPUT_INTERFACE_FORMAT_RGB666     = 1, ///< Output interface format RGB666
    GLCDC_OUTPUT_INTERFACE_FORMAT_RGB565     = 2, ///< Output interface format RGB565
    GLCDC_OUTPUT_INTERFACE_FORMAT_SERIAL_RGB = 3, ///< Output interface format Serial RGB
} glcdc_output_interface_format_t;

/** Dithering output format */
typedef enum e_glcdc_dithering_output_format
{
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB888 = 0, ///< Dithering output format RGB888
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB666 = 1, ///< Dithering output format RGB666
    GLCDC_DITHERING_OUTPUT_FORMAT_RGB565 = 2, ///< Dithering output format RGB565
} glcdc_dithering_output_format_t;

/** GLCDC hardware specific configuration */
typedef struct st_glcdc_extended_cfg
{
    glcdc_tcon_pin_t              tcon_hsync;            ///< GLCDC TCON output pin select
    glcdc_tcon_pin_t              tcon_vsync;            ///< GLCDC TCON output pin select
    glcdc_tcon_pin_t              tcon_de;               ///< GLCDC TCON output pin select
    glcdc_correction_proc_order_t correction_proc_order; ///< Correction control route select
    glcdc_clk_src_t               clksrc;                ///< Clock Source selection
    glcdc_panel_clk_div_t         clock_div_ratio;       ///< Clock divide ratio for dot clock
    glcdc_dithering_mode_t        dithering_mode;        ///< Dithering mode
    glcdc_dithering_pattern_t     dithering_pattern_A;   ///< Dithering pattern A
    glcdc_dithering_pattern_t     dithering_pattern_B;   ///< Dithering pattern B
    glcdc_dithering_pattern_t     dithering_pattern_C;   ///< Dithering pattern C
    glcdc_dithering_pattern_t     dithering_pattern_D;   ///< Dithering pattern D
} glcdc_extended_cfg_t;

/* GLCDC hardware specific control block */
typedef struct st_glcdc_ctrl
{
    display_coordinate_t back_porch;   ///< Zero coordinate for graphics plane(Back porch end)
    uint16_t             hsize;        ///< Horizontal pixel size in a line
    uint16_t             vsize;        ///< Vertical pixel size in a frame
    void               * p_context;    ///< Pointer to the function level device context
                                       // (e.g. display_ctrl_t type data)
} glcdc_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/* @cond INC_HEADER_DEFS_SEC */
/* Filled in Interface API structure for this Instance. */
extern const display_api_t g_display_on_glcdc;

/* @endcond */

/**********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

fsp_err_t R_GLCDC_Open(display_ctrl_t * const p_api_ctrl, display_cfg_t const * const p_cfg);
fsp_err_t R_GLCDC_Close(display_ctrl_t * const p_api_ctrl);
fsp_err_t R_GLCDC_Start(display_ctrl_t * const p_api_ctrl);
fsp_err_t R_GLCDC_Stop(display_ctrl_t * const p_api_ctrl);
fsp_err_t R_GLCDC_LayerChange(display_ctrl_t const * const        p_api_ctrl,
                              display_runtime_cfg_t const * const p_cfg,
                              display_frame_layer_t               layer);
fsp_err_t R_GLCDC_BufferChange(display_ctrl_t const * const p_api_ctrl,
                               uint8_t * const              framebuffer,
                               display_frame_layer_t        layer);

#if GLCDC_CFG_COLOR_CORRECTION_ENABLE
fsp_err_t R_GLCDC_ColorCorrection(display_ctrl_t const * const       p_api_ctrl,
                                  display_correction_t const * const p_correction);

#endif

fsp_err_t R_GLCDC_ClutUpdate(display_ctrl_t const * const     p_api_ctrl,
                             display_clut_cfg_t const * const p_clut_cfg,
                             display_frame_layer_t            layer);
fsp_err_t R_GLCDC_ClutEdit(display_ctrl_t const * const p_api_ctrl,
                           display_frame_layer_t        layer,
                           uint8_t                      index,
                           uint32_t                     color);
fsp_err_t R_GLCDC_StatusGet(display_ctrl_t const * const p_api_ctrl, display_status_t * const status);

/*******************************************************************************************************************//**
 * @} (end defgroup GLCDC)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
