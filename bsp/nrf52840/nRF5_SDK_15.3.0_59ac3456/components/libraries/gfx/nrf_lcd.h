/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef NRF_LCD_H__
#define NRF_LCD_H__

#include <nrfx.h>

/** @file
 *
 * @defgroup nrf_lcd LCD Library
 * @{
 * @ingroup nrf_gfx
 *
 * @brief This module defines generic API for LCDs.
 */

/**
 * @brief Enumerator with available rotations.
 */
typedef enum{
    NRF_LCD_ROTATE_0 = 0,       /**< Rotate 0 degrees, clockwise. */
    NRF_LCD_ROTATE_90,          /**< Rotate 90 degrees, clockwise. */
    NRF_LCD_ROTATE_180,         /**< Rotate 180 degrees, clockwise. */
    NRF_LCD_ROTATE_270          /**< Rotate 270 degrees, clockwise. */
}nrf_lcd_rotation_t;

/**
 * @brief LCD instance control block.
 */
typedef struct
{
    nrfx_drv_state_t state;         /**< State of LCD instance. */
    uint16_t height;                /**< LCD height. */
    uint16_t width;                 /**< LCD width. */
    nrf_lcd_rotation_t rotation;    /**< LCD rotation. */
}lcd_cb_t;

/**
 * @brief LCD instance type.
 *
 * This structure provides generic API for LCDs.
 */
typedef struct
{
    /**
     * @brief Function for initializing the LCD controller.
     */
    ret_code_t (* lcd_init)(void);

    /**
     * @brief Function for uninitializing the LCD controller.
     */
    void (* lcd_uninit)(void);

    /**
     * @brief Function for drawing a single pixel.
     *
     * @param[in] x             Horizontal coordinate of the pixel.
     * @param[in] y             Vertical coordinate of the pixel.
     * @param[in] color         Color of the pixel in LCD accepted format.
     */
    void (* lcd_pixel_draw)(uint16_t x, uint16_t y, uint32_t color);

    /**
     * @brief Function for drawing a filled rectangle.
     *
     * @param[in] x             Horizontal coordinate of the point where to start drawing the rectangle.
     * @param[in] y             Vertical coordinate of the point where to start drawing the rectangle.
     * @param[in] width         Width of the image.
     * @param[in] height        Height of the image.
     * @param[in] color         Color with which to fill the rectangle in LCD accepted format.
     */
    void (* lcd_rect_draw)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

    /**
     * @brief Function for displaying data from an internal frame buffer.
     *
     * This function may be used when functions for drawing do not write directly to
     * LCD but to an internal frame buffer. It could be implemented to write data from this
     * buffer to LCD.
    */
    void (* lcd_display)(void);

    /**
     * @brief Function for rotating the screen.
     *
     * @param[in] rotation      Rotation as enumerated value.
     */
    void (* lcd_rotation_set)(nrf_lcd_rotation_t rotation);

    /**
     * @brief Function for setting inversion of colors on the screen.
     *
     * @param[in] invert        If true, inversion will be set.
     */
    void (* lcd_display_invert)(bool invert);

    /**
     * @brief Pointer to the LCD instance control block.
     */
    lcd_cb_t * p_lcd_cb;
}nrf_lcd_t;

/* @} */

#endif // NRF_LCD_H__
