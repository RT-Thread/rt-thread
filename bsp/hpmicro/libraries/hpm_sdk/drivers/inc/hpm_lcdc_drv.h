/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_LCDC_DRV_H
#define HPM_LCDC_DRV_H
#include "hpm_display_common.h"
#include "hpm_soc_feature.h"
#include "hpm_lcdc_regs.h"

/**
 *
 * @brief LCD driver APIs
 * @defgroup lcd_interface LCD driver APIs
 * @ingroup io_interfaces
 * @{
 */

#define LCDC_TEST_MODE_DISABLE       (0U)
#define LCDC_TEST_MODE_BACKGROUND    (1U)
#define LCDC_TEST_MODE_COLOR_BAR_COL (2U)
#define LCDC_TEST_MODE_COLOR_BAR_ROW (3U)

/* @brief LCD driver specific status */
enum {
    status_lcdc_no_active_layer_yet = MAKE_STATUS(status_group_lcdc, 1),
    status_lcdc_layer_not_supported = MAKE_STATUS(status_group_lcdc, 2),
};

/* @brief LCD line pattern */
typedef enum lcdc_line_pattern {
    lcdc_line_pattern_rgb = 0,
    lcdc_line_pattern_rbg,
    lcdc_line_pattern_gbr,
    lcdc_line_pattern_grb,
    lcdc_line_pattern_brg,
    lcdc_line_pattern_bgr,
} lcdc_line_pattern_t;

/* @brief LCD display mode */
typedef enum lcdc_display_mode {
    lcdc_display_mode_normal = 0,
    lcdc_display_mode_test_mode_1,
    lcdc_display_mode_test_mode_2,
    lcdc_display_mode_test_mode_3,
} lcdc_display_mode_t;

/* @brief LCD layer transfer max bytes */
typedef enum lcdc_layer_max_bytes_per_transfer {
    lcdc_layer_max_bytes_64 = 0,
    lcdc_layer_max_bytes_128,
    lcdc_layer_max_bytes_256,
    lcdc_layer_max_bytes_512,
    lcdc_layer_max_bytes_1024,
} lcdc_layer_max_bytes_per_transfer_t;

/* @brief LCD control */
typedef struct lcdc_control {
    lcdc_line_pattern_t line_pattern;   /**< Line pattern setting */
    lcdc_display_mode_t display_mode;   /**< Display mode setting */
    bool invert_pixel_data;             /**< Invert pixel data level */
    bool invert_pixel_clock;            /**< Invert pixel clock level */
    bool invert_href;                   /**< Invert href level */
    bool invert_vsync;                  /**< Invert vsync level */
    bool invert_hsync;                  /**< Invert hsync level */
} lcdc_control_t;

/* @brief LCD hsync/vsync config */
typedef struct lcdc_xsync_config {
    uint16_t front_porch_pulse;         /**< Front porch pulse */
    uint16_t back_porch_pulse;          /**< Back porch pulse */
    uint16_t pulse_width;               /**< Pulse width */
} lcdc_xsync_config_t;

/* @brief LCD config */
typedef struct lcdc_config {
    uint16_t resolution_x;              /**< Horizontal resolution in pixel */
    uint16_t resolution_y;              /**< Vertial resolution in pixel */
    lcdc_xsync_config_t hsync;          /**< Hsync config */
    lcdc_xsync_config_t vsync;          /**< Vsync config */
    display_color_32b_t background;     /**< Background color */
    lcdc_control_t control;             /**< LCD control */
} lcdc_config_t;

/* @brief LCD layer config */
typedef struct lcdc_layer_config {
    uint8_t max_ot;                                     /**< Maximum outstanding transfer */
    display_byteorder_t byteorder;                      /**< Byte order */
    display_yuv_format_t yuv;                           /**< YUV format */
    display_pixel_format_t pixel_format;                /**< Pixel format */
    display_alphablend_option_t alphablend;             /**< Alphablending option */
    display_yuv2rgb_config_t csc_config;                /**< Color space conversion config */
    lcdc_layer_max_bytes_per_transfer_t max_bytes;      /**< Layer max transfer bytes */
    uint16_t height;                                    /**< Layer height in pixel */
    uint16_t width;                                     /**< Layer width in pixel */
    uint16_t position_x;                                /**< Layer output position X coord */
    uint16_t position_y;                                /**< Layer output position Y coord */
    display_color_32b_t background;                     /**< Background color */
    uint32_t buffer;                                    /**< Pointer of layer display buffer */
} lcdc_layer_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief Layer config
 *
 * @param[in] ptr LCD base address
 */
static inline void lcdc_software_reset(LCDC_Type *ptr)
{
    ptr->CTRL |= LCDC_CTRL_SW_RST_MASK;
    ptr->CTRL &= ~LCDC_CTRL_SW_RST_MASK;
}

/**
 *
 * @brief Enable interrupt according to the given mask
 *
 * @param[in] ptr LCD base address
 * @param[in] interrupt_mask Mask of interrupts to be enabled
 */
static inline void lcdc_enable_interrupt(LCDC_Type *ptr, uint32_t interrupt_mask)
{
    ptr->INT_EN |= interrupt_mask;
}

/**
 *
 * @brief Disable interrupt according to the given mask
 *
 * @param[in] ptr LCD base address
 * @param[in] interrupt_mask Mask of interrupts to be disabled
 */
static inline void lcdc_disable_interrupt(LCDC_Type *ptr, uint32_t interrupt_mask)
{
    ptr->INT_EN &= ~interrupt_mask;
}

/**
 *
 * @brief Clear specific status according to the given mask
 *
 * @param[in] ptr LCD base address
 * @param[in] mask Status mask of status to be cleared
 */
static inline void lcdc_clear_status(LCDC_Type *ptr, uint32_t mask)
{
    ptr->ST |= mask;
}

/**
 *
 * @brief Make layer control shadow registers take effect
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index Index of layer to be controlled
 */
static inline bool lcdc_layer_control_shadow_loaded(LCDC_Type *ptr, uint8_t layer_index)
{
    return !(ptr->LAYER[layer_index].LAYCTRL & LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK);
}

/**
 *
 * @brief Get DMA status
 *
 * @param[in] ptr LCD base address
 * @retval DMA status
 */
static inline uint32_t lcdc_get_dma_status(LCDC_Type *ptr)
{
    return ptr->DMA_ST;
}

/**
 *
 * @brief Check DMA status against the given mask
 *
 * @param[in] ptr LCD base address
 * @param[in] mask Mask of expected DMA status
 * @retval true if all bits set to 1 in mask are set
 * @retval false if any bit set to 1 in mask is not set
 */
static inline bool lcdc_check_dma_status(LCDC_Type *ptr, uint32_t mask)
{
    return ((ptr->DMA_ST & mask) == mask);
}

/**
 *
 * @brief Clear DMA status according to the given mask
 *
 * @param[in] ptr LCD base address
 * @param[in] mask Mask of expected DMA status
 */
static inline void lcdc_clear_dma_status(LCDC_Type *ptr, uint32_t mask)
{
    ptr->DMA_ST |= mask;
}

/**
 *
 * @brief Get status
 *
 * @param[in] ptr LCD base address
 * @retval current status
 */
static inline uint32_t lcdc_get_status(LCDC_Type *ptr)
{
    return ptr->ST;
}

/**
 *
 * @brief Check status against the given mask
 *
 * @param[in] ptr LCD base address
 * @param[in] mask Mask of expected status
 * @retval true if all bits set to 1 in mask are set
 * @retval false if any bit set to 1 in mask is not set
 */
static inline bool lcdc_check_status(LCDC_Type *ptr, uint32_t mask)
{
    return (ptr->ST & mask) == mask;
}

/**
 *
 * @brief Set next buffer for certain layer
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index target layer to be configured
 * @param[in] buffer display buffer to be set
 */
static inline void lcdc_layer_set_next_buffer(LCDC_Type *ptr, uint32_t layer_index, uint32_t buffer)
{
    ptr->LAYER[layer_index].START0 = LCDC_LAYER_START0_ADDR0_SET(buffer);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

/**
 *
 * @brief Update specific layer background
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index target layer to be configured
 * @param[in] background color to be set as background
 */
static inline void lcdc_layer_update_background(LCDC_Type *ptr,
                uint8_t layer_index, display_color_32b_t background)
{
    ptr->LAYER[layer_index].BG_CL = LCDC_LAYER_BG_CL_ARGB_SET(background.u);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

/**
 *
 * @brief Update specific layer position
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index target layer to be configured
 * @param[in] x Position X coord
 * @param[in] y Position Y coord
 */
static inline void lcdc_layer_update_position(LCDC_Type *ptr,
        uint8_t layer_index, uint16_t x, uint32_t y)
{
    ptr->LAYER[layer_index].LAYPOS = LCDC_LAYER_LAYPOS_X_SET(x)
        | LCDC_LAYER_LAYPOS_Y_SET(y);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

/**
 *
 * @brief Update specific layer dimension
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index target layer to be configured
 * @param[in] width Width in pixel
 * @param[in] height Height in pixel
 */
static inline void lcdc_layer_update_dimension(LCDC_Type *ptr,
        uint8_t layer_index, uint8_t width, uint8_t height)
{
    ptr->LAYER[layer_index].LAYSIZE = LCDC_LAYER_LAYSIZE_WIDTH_SET(width)
        | LCDC_LAYER_LAYSIZE_HEIGHT_SET(height);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

/**
 *
 * @brief Update specific layer region
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index target layer to be configured
 * @param[in] x1 X coord of the top left pixel
 * @param[in] y1 Y coord of the top left pixel
 * @param[in] x2 X coord of the bottom right pixel
 * @param[in] y2 Y coord of the bottom right pixel
 */
static inline void lcdc_layer_set_region(LCDC_Type *ptr, uint8_t layer_index,
                        uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    ptr->LAYER[layer_index].LAYPOS = LCDC_LAYER_LAYPOS_X_SET(x1)
        | LCDC_LAYER_LAYPOS_Y_SET(y1);
    ptr->LAYER[layer_index].LAYSIZE = LCDC_LAYER_LAYSIZE_WIDTH_SET(x2 - x1 + 1)
        | LCDC_LAYER_LAYSIZE_HEIGHT_SET(y2 - y1 + 1);
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

/**
 *
 * @brief Update specific layer configuration
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index target layer to be configured
 */
static inline void lcdc_layer_update(LCDC_Type *ptr, uint8_t layer_index)
{
    ptr->LAYER[layer_index].LAYCTRL |= LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

/**
 *
 * @brief Enable specific layer
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index target layer to be configured
 */
static inline void lcdc_layer_enable(LCDC_Type *ptr, uint32_t layer_index)
{
    ptr->LAYER[layer_index].LAYCTRL |=
        (LCDC_LAYER_LAYCTRL_EN_MASK | LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK);
}

/**
 *
 * @brief Disable specific layer
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index target layer to be configured
 */
static inline void lcdc_layer_disable(LCDC_Type *ptr, uint32_t layer_index)
{
    ptr->LAYER[layer_index].LAYCTRL =
        (ptr->LAYER[layer_index].LAYCTRL & (~LCDC_LAYER_LAYCTRL_EN_MASK))
        | LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
}

/**
 *
 * @brief Set test mode
 *
 * @param[in] ptr LCD base address
 * @param[in] test_mode target test mode to be enabled
 */
static inline void lcdc_set_testmode(LCDC_Type *ptr, uint8_t test_mode)
{
    ptr->CTRL = ((ptr->CTRL & ~LCDC_CTRL_DISP_MODE_MASK))
        | LCDC_CTRL_DISP_MODE_SET(test_mode)
        | LCDC_CTRL_DISP_ON_MASK;
}

/**
 *
 * @brief Set background
 *
 * @param[in] ptr LCD base address
 * @param[in] color background color
 */
static inline void lcdc_set_background(LCDC_Type *ptr,
                                       display_color_32b_t color)
{
    ptr->BGND_CL = LCDC_BGND_CL_R_SET(color.r)
        | LCDC_BGND_CL_G_SET(color.g)
        | LCDC_BGND_CL_B_SET(color.b);
}

/**
 *
 * @brief Get default layer configuration value
 *
 * @param[in] ptr LCD base address
 * @param[out] layer Pointer of layer configuration struct buffer
 * @param[in] pixel_format Pixel format to be used for this layer
 * @param[in] layer_index target layer to be configured
 */
void lcdc_get_default_layer_config(LCDC_Type *ptr,
                                   lcdc_layer_config_t *layer, display_pixel_format_t pixel_format, uint8_t layer_index);

/**
 *
 * @brief Get default configuration value
 *
 * @param[in] ptr LCD base address
 * @param[out] config Pointer of configuration struct buffer
 */
void lcdc_get_default_config(LCDC_Type *ptr, lcdc_config_t *config);

/**
 *
 * @brief Initialize LCD controller
 *
 * @param[in] ptr LCD base address
 * @param[in] config Pointer of configuration struct buffer
 */
void lcdc_init(LCDC_Type *ptr, lcdc_config_t *config);

/**
 *
 * @brief Configure specific layer
 *
 * @param[in] ptr LCD base address
 * @param[in] layer_index target layer to be configured
 * @param[in] layer_config Pointer of layer configuration struct buffer
 * @param[in] enable_layer Set true if the layer needs to be enabled right after being configured
 */
hpm_stat_t lcdc_config_layer(LCDC_Type *ptr, uint8_t layer_index,
                       lcdc_layer_config_t *layer_config, bool enable_layer);

/**
 *
 * @brief Turn on display
 *
 * @param[in] ptr LCD base address
 */
void lcdc_turn_on_display(LCDC_Type *ptr);

/**
 *
 * @brief Turn off display
 *
 * @param[in] ptr LCD base address
 */
void lcdc_turn_off_display(LCDC_Type *ptr);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */

#endif /* HPM_LCDC_DRV_H */
