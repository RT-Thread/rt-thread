/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_PDMA_DRV_H
#define HPM_PDMA_DRV_H
#include "hpm_soc_feature.h"
#include "hpm_display_common.h"
#include "hpm_pdma_regs.h"

/**
 * @brief PDMA driver APIs
 * @defgroup pdma_interface PDMA driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief PDMA status
 */
enum {
    status_pdma_done = status_success,
    status_pdma_error = MAKE_STATUS(status_group_pdma, 1),
    status_pdma_busy = MAKE_STATUS(status_group_pdma, 2),
    status_pdma_idle = MAKE_STATUS(status_group_pdma, 3),
};

/**
 * @brief PDMA plane
 */
typedef enum pdma_plane {
    pdma_plane_src = 0,
    pdma_plane_dst = 1,
    pdma_plane_both,
    pdma_plane_none,
} pdma_plane_t;

/**
 * @brief PDMA flip
 */
typedef enum pdma_flip {
    pdma_flip_none = 0,
    pdma_flip_horizontal = 1 << 0,
    pdma_flip_vertical = 1 << 1,
    pdma_flip_both = pdma_flip_horizontal | pdma_flip_vertical,
} pdma_flip_t;

/**
 * @brief PDMA rotate
 */
typedef enum pdma_rotate {
    pdma_rotate_0_degree = 0,
    pdma_rotate_90_degree = 1,
    pdma_rotate_180_degree = 2,
    pdma_rotate_270_degree = 3,
} pdma_rotate_t;

/**
 * @brief PDMA decimation
 */
typedef enum pdma_decimation {
    pdma_decimation_by_1 = 0,
    pdma_decimation_by_2 = 1,
    pdma_decimation_by_4 = 2,
    pdma_decimation_by_8 = 3,
} pdma_decimation_t;

/**
 * @brief PDMA block size
 */
typedef enum pdma_blocksize {
    pdma_blocksize_16x16,
    pdma_blocksize_8x8,
} pdma_blocksize_t;

/**
 * @brief PDMA make scale value
 */
#define PDMA_MAKE_SCALE_SET(integer, fractional)  \
    (((integer) & 0x3) << 12 | ((fractional) & 0xFFF))

/**
 * @brief PDMA plane config
 */
typedef struct pdma_plane_config {
    bool swap_byte3_byte1;                /**< set true to swap byte [31:24] and byte [15:8] */
    bool use_background_as_clear;         /**< set true to use background color at blending clear mode */
    bool ycbcr_mode;                      /**< set true if it is YCbCr mode */
    bool bypass_colorspace_conversion;    /**< set true to bypass color space conversion */
    bool byte_swap;                       /**< set true to swap [31:16] and [15:0] */
    display_byteorder_t byteorder;        /**< packing byte order type */
    pdma_flip_t flip;                     /**< flip type */
    pdma_rotate_t rotate;                 /**< rotate type */
    pdma_decimation_t x_dec;              /**< horizontal decimation */
    pdma_decimation_t y_dec;              /**< vertical decimation */
    display_pixel_format_t pixel_format;  /**< pixel format */
    uint32_t buffer;                      /**< buffer address */
    uint32_t background;                  /**< background color */
    uint32_t colorkey_high;               /**< colorkey high limit */
    uint32_t colorkey_low;                /**< colorkey low limit */
    uint16_t x_scale;                     /**< 14-bit horizontal scale */
    uint16_t y_scale;                     /**< 14-bit vertical scale */
    uint16_t pitch;                       /**< pitch value */
    uint16_t x_offset;                    /**< horizontal offset */
    uint16_t y_offset;                    /**< vertical offset */
    uint16_t width;                       /**< width */
    uint16_t height;                      /**< height */
} pdma_plane_config_t;

/**
 * @brief PDMA output config
 */
typedef struct pdma_output_config {
    display_alphablend_option_t alphablend;         /**< alpha blending mode */
    display_pixel_format_t pixel_format;            /**< pixel format */
    display_rgb2yuv_config_t rgb2yuv_config;        /**< RGB to YUV config */
    uint32_t buffer;                                /**< buffer */
    struct {
        uint16_t x;                                 /**< plane origin X coord */
        uint16_t y;                                 /**< plane origin Y coord */
        uint16_t width;                             /**< plane width */
        uint16_t height;                            /**< plane height */
    } plane[PDMA_SOC_PS_MAX_COUNT];                 /**< plane config */
    uint16_t width;                                 /**< output plane width */
    uint16_t height;                                /**< output plane height */
    uint16_t pitch;
} pdma_output_config_t;

/**
 * @brief PDMA config
 */
typedef struct pdma_config {
    display_byteorder_t byteorder;                  /**< byte order */
    pdma_blocksize_t block_size;                    /**< block size */
    pdma_plane_t enable_plane;                      /**< plane to be enabled */
} pdma_config_t;

/**
 * @brief PDMA plane info
 */
typedef struct pdma_plane_info {
    uint32_t buffer;                                /**< buffer */
    uint32_t x;                                     /**< plane origin X coord */
    uint32_t y;                                     /**< plane origin Y coord */
    uint32_t width;                                 /**< plane width */
    uint32_t height;                                /**< plane height */
    display_pixel_format_t format;                  /**< pixel format */
} pdma_plane_info_t;


typedef struct pdma_blit_option {
    display_alphablend_mode_t blend;
    struct {
        uint16_t x;
        uint16_t y;
    } translate;
    pdma_flip_t flip;
    pdma_rotate_t rotate;
    struct {
        float x; /* 0.0625 - 4095 */
        float y; /* 0.0625 - 4095 */
    } scale;
} pdma_blit_option_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get default configuration according to input pixel format
 *
 * @param [in] ptr PDMA base address
 * @param [out] config pdma_config_t
 * @param [in] pixel_format display_pixel_format_t
 */
void pdma_get_default_config(PDMA_Type *ptr, pdma_config_t *config, display_pixel_format_t pixel_format);

/**
 * @brief Get default plane configuration according input pixel format
 *
 * @param [in] ptr PDMA base address
 * @param [out] config pdma_plane_config_t
 * @param [in] pixel_format display_pixel_format_t
 */
void pdma_get_default_plane_config(PDMA_Type *ptr, pdma_plane_config_t *config, display_pixel_format_t pixel_format);

/**
 * @brief Get default YUV2RGB coefficient configuration according to input pixel format
 *
 * @note The two plane share one YUV2RGB_COEF, so not support convert one plane YUV422 format
 * and another plane YCbCr422 format at same time
 *
 * @param [in] ptr PDMA base address
 * @param [out] yuv2rgb_coef display_yuv2rgb_coef_t
 * @param [in] source_format the YUV2RGB input source pixel format
 */
void pdma_get_default_yuv2rgb_coef_config(PDMA_Type *ptr, display_yuv2rgb_coef_t *yuv2rgb_coef, display_pixel_format_t source_format);

/**
 * @brief Get default output configuration
 *
 * @param [in] ptr PDMA base address
 * @param [out] config pdma_output_config_t
 * @param [in] pixel_format output data pixel format
 */
void pdma_get_default_output_config(PDMA_Type *ptr,
                                    pdma_output_config_t *config, display_pixel_format_t pixel_format);

/**
 * @brief PDMA enable/disable irq
 *
 * @param [in] ptr PDMA base address
 * @param [in] mask irq mask
 * @param [in] enable :
 *  @arg true: enable
 *  @arg false: disable
 */
void pdma_enable_irq(PDMA_Type *ptr, uint32_t mask, bool enable);

/**
 * @brief PDMA config output
 *
 * @param [in] ptr PDMA base address
 * @param [in] config pdma_output_config_t
 */
void pdma_config_output(PDMA_Type *ptr, pdma_output_config_t *config);

/**
 * @brief Configure PDMA planes
 *
 * Note: The plane_src and plane_dst share one YUV2RGB_COEF, so not support convert one plane YUV422 format
 * and another plane YCbCr422 format at same time
 *
 * @param [in] ptr PDMA base address
 * @param [in] plane_src_config Pointer to plane_src configuration structure
 * @param [in] plane_dst_config Pointer to plan_dst configuration structure
 * @param [in] yuv2rgb_coef Pointer to yuv2rgb_coef configuration structure
 */
void pdma_config_planes(PDMA_Type *ptr, void *plane_src_config, void *plane_dst_config, void *yuv2rgb_coef);

/**
 * @brief PDMA initialization
 *
 * @param [in] ptr PDMA base address
 * @param [in] config pdma_output_config_t
 */
void pdma_init(PDMA_Type *ptr, pdma_config_t *config);

/**
 * @brief PDMA check status
 *
 * @param [in] ptr PDMA base address
 * @param [out] status pdma status
 */
hpm_stat_t pdma_check_status(PDMA_Type *ptr, uint32_t *status);

/**
 * @brief PDMA fill color
 *
 * @param [in] ptr PDMA base address
 * @param [in] dst target buff address
 * @param [in] dst_width target buff pixel width
 * @param [in] width output image width
 * @param [in] height output image height
 * @param [in] color color value
 * @param [in] alpha alpha value
 * @param [in] format display_pixel_format_t
 * @param [in] wait wait for execution to complete
 * @param [out] status pdma status
 * @retval hpm_stat_t: status_success if flip and rotate plane without any error
 */
hpm_stat_t pdma_fill_color(PDMA_Type *ptr, uint32_t dst, uint32_t dst_width,
                           uint32_t width, uint32_t height,
                           uint32_t color, uint8_t alpha,
                           display_pixel_format_t format,
                           bool wait, uint32_t *status);

/**
 * @brief PDMA flip rotate plane
 *
 * @param [in] ptr PDMA base address
 * @param [in] dst target buff address
 * @param [in] dst_width target buff pixel width
 * @param [in] src source buff address
 * @param [in] src_width source buff pixel width
 * @param [in] x x coordinate n buffer
 * @param [in] y y coordinate n buffer
 * @param [in] width output image width
 * @param [in] height output image height
 * @param [in] flip pdma_flip_t
 * @param [in] rotate pdma_rotate_t
 * @param [in] alpha alpha value
 * @param [in] format display_pixel_format_t
 * @param [in] wait wait for execution to complete
 * @param [out] status pdma status
 * @retval hpm_stat_t: status_success if flip and rotate plane without any error
 */
hpm_stat_t pdma_flip_rotate(PDMA_Type *ptr, uint32_t dst, uint32_t dst_width,
                    uint32_t src, uint32_t src_width, uint32_t x, uint32_t y,
                    uint32_t width, uint32_t height,
                    pdma_flip_t flip, pdma_rotate_t rotate, uint8_t alpha,
                    display_pixel_format_t format,
                    bool wait, uint32_t *status);

/**
 * @brief PDMA blit plane
 *
 * @param [in] ptr PDMA base address
 * @param [in] dst target buff address
 * @param [in] dst_width target buff pixel width
 * @param [in] src source buff address
 * @param [in] src_width source buff pixel width
 * @param [in] x x coordinate n buffer
 * @param [in] y y coordinate n buffer
 * @param [in] width output image width
 * @param [in] height output image height
 * @param [in] alpha alpha value
 * @param [in] format display_pixel_format_t
 * @param [in] wait wait for execution to complete
 * @param [out] status pdma status
 * @retval hpm_stat_t: status_success if flip and rotate plane without any error
 */
hpm_stat_t pdma_blit(PDMA_Type *ptr,
                     uint32_t dst, uint32_t dst_width,
                     uint32_t src, uint32_t src_width,
                     uint32_t x, uint32_t y, uint32_t width, uint32_t height,
                     uint8_t alpha,
                     display_pixel_format_t format,
                     bool wait, uint32_t *status);

/**
 * @brief PDMA scale plane
 *
 * @param [in] ptr PDMA base address
 * @param [in] dst target buff address
 * @param [in] dst_width target buff pixel width
 * @param [in] src source buff address
 * @param [in] src_width source buff pixel width
 * @param [in] x x coordinate n buffer
 * @param [in] y y coordinate n buffer
 * @param [in] width input image width
 * @param [in] height input image height
 * @param [in] target_width output image width
 * @param [in] target_height output image height
 * @param [in] alpha alpha value
 * @param [in] format display_pixel_format_t
 * @param [in] wait wait for execution to complete
 * @param [out] status pdma status
 * @retval hpm_stat_t: status_success if flip and rotate plane without any error
 */
hpm_stat_t pdma_scale(PDMA_Type *ptr,
                     uint32_t dst, uint32_t dst_width,
                     uint32_t src, uint32_t src_width,
                     uint32_t x, uint32_t y, uint32_t width, uint32_t height,
                     uint32_t target_width, uint32_t target_height,
                     uint8_t alpha,
                     display_pixel_format_t format,
                     bool wait, uint32_t *status);
/**
 * @brief PDMA get default blit option
 *
 * @param op option of blit
 */
void pdma_get_default_blit_option(pdma_blit_option_t *op);

/**
 * @brief PDMA blit plane by option
 *
 * @param ptr PDMA base address
 * @param dst target buff address
 * @param src source buff address
 * @param op option of blit
 * @param wait wait for execution to complete
 * @param status pdma status
 * @retval hpm_stat_t: status_success if flip and rotate plane without any error
 */
hpm_stat_t pdma_blit_ex(PDMA_Type *ptr,
                     display_buf_t *dst,
                     display_buf_t *src,
                     pdma_blit_option_t *op,
                     bool wait, uint32_t *status);

/**
 * @brief PDMA set block size
 *
 * @param [in] ptr PDMA base address
 * @param [in] size pdma_blocksize_t
 */
void pdma_set_block_size(PDMA_Type *ptr, pdma_blocksize_t size);

/**
 * @brief PDMA stop
 *
 * @param [in] ptr PDMA base address
 */
void pdma_stop(PDMA_Type *ptr);

/**
 * @brief PDMA stop
 *
 * @param [in] ptr PDMA base address
 *
 * @retval STAT register value
 */
static inline uint32_t pdma_get_status(PDMA_Type *ptr)
{
    return ptr->STAT;
}

/**
 * @brief PDMA start
 *
 * @param [in] ptr PDMA base address
 */
static inline void pdma_start(PDMA_Type *ptr)
{
    ptr->CTRL |= PDMA_CTRL_PDMA_EN_MASK;
    __asm volatile ("" : : "r" (ptr->CTRL));
}

/**
 * @brief PDMA software reset
 *
 * @param [in] ptr PDMA base address
 */
static inline void pdma_software_reset(PDMA_Type *ptr)
{
    ptr->CTRL |= PDMA_CTRL_PDMA_SFTRST_MASK;
    ptr->CTRL &= ~(PDMA_CTRL_PDMA_SFTRST_MASK);
    __asm volatile ("" : : "r" (ptr->CTRL));
}

/**
 * @brief PDMA set plane color key limits
 *
 * @param [in] ptr PDMA base address
 * @param [in] plane_index plane index
 * @param [in] key_high color key high limits
 * @param [in] key_low color key low limits
 */
static inline void pdma_set_plane_colorkey(PDMA_Type *ptr,
                                           uint8_t plane_index,
                                           uint32_t key_high,
                                           uint32_t key_low)
{
    ptr->PS[plane_index].CLRKEY_LOW = PDMA_PS_CLRKEY_LOW_LIMIT_SET(key_low);
    ptr->PS[plane_index].CLRKEY_HIGH = PDMA_PS_CLRKEY_HIGH_LIMIT_SET(key_high);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /* HPM_PDMA_DRV_H */
