/**
 * Copyright (c) 2009 - 2017, Nordic Semiconductor ASA
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
#include <stdbool.h>
#include <stdint.h>

#include "adns2080.h"
#include "sdio.h"

/*lint ++flb "Enter library region" */

#define ADNS2080_PRODUCT_ID   (0x2AU) /*!< ADNS2080 product id */
#define ADNS2080_RESET_NUMBER (0x5AU) /*!< ADNS2080 reset code */

/* ADNS2080 register addresses */
#define REG_PROD_ID          (0x00U) /*!< Product ID. Default value : 0x2A */
#define REG_REV_ID           (0x01U) /*!< Revision ID. Default value : 0x00 */
#define REG_MOTION_ST        (0x02U) /*!< Motion Status. Default value : 0x00 */
#define REG_DELTA_X          (0x03U) /*!< Lower byte of Delta_X. Default value : 0x00 */
#define REG_DELTA_Y          (0x04U) /*!< Lower byte of Delta_Y. Default value : 0x00 */
#define REG_SQUAL            (0x05U) /*!< Squal Quality. Default value : 0x00 */
#define REG_SHUT_HI          (0x06U) /*!< Shutter Open Time (Upper 8-bit). Default value : 0x00 */
#define REG_SHUT_LO          (0x07U) /*!< Shutter Open Time (Lower 8-bit). Default value : 0x64 */
#define REG_PIX_MAX          (0x08U) /*!< Maximum Pixel Value. Default value : 0xD0 */
#define REG_PIX_ACCUM        (0x09U) /*!< Average Pixel Value. Default value : 0x80 */
#define REG_PIX_MIN          (0x0AU) /*!< Minimum Pixel Value. Default value : 0x00 */
#define REG_PIX_GRAB         (0x0BU) /*!< Pixel Grabber. Default value : 0x00 */
#define REG_DELTA_XY_HIGH    (0x0CU) /*!< Upper 4 bits of Delta X and Y displacement. Default value : 0x00 */
#define REG_MOUSE_CTRL       (0x0DU) /*!< Mouse Control. Default value : 0x01 */
#define REG_RUN_DOWNSHIFT    (0x0EU) /*!< Run to Rest1 Time. Default value : 0x08 */
#define REG_REST1_PERIOD     (0x0FU) /*!< Rest1 Period. Default value : 0x01 */
#define REG_REST1_DOWNSHIFT  (0x10U) /*!< Rest1 to Rest2 Time. Default value : 0x1f */
#define REG_REST2_PERIOD     (0x11U) /*!< Rest2 Period. Default value : 0x09 */
#define REG_REST2_DOWNSHIFT  (0x12U) /*!< Rest2 to Rest3 Time. Default value : 0x2f */
#define REG_REST3_PERIOD     (0x13U) /*!< Rest3 Period. Default value : 0x31 */
#define REG_PERFORMANCE      (0x22U) /*!< Performance. Default value : 0x00 */
#define REG_RESET            (0x3aU) /*!< Reset. Default value : 0x00 */
#define REG_NOT_REV_ID       (0x3fU) /*!< Inverted Revision ID. Default value : 0xff */
#define REG_LED_CTRL         (0x40U) /*!< LED Control. Default value : 0x00 */
#define REG_MOTION_CTRL      (0x41U) /*!< Motion Control. Default value : 0x40 */
#define REG_BURST_READ_FIRST (0x42U) /*!< Burst Read Starting Register. Default value : 0x03 */
#define REG_BURST_READ_LAST  (0x44U) /*!< Burst Read Ending Register. Default value : 0x09 */
#define REG_REST_MODE_CONFIG (0x45U) /*!< Rest Mode Confi guration. Default value : 0x00 */
#define REG_MOTION_BURST     (0x63U) /*!< Burst Read. Default value : 0x00 */

/* ADNS2080 register bits */
#define REG_MOUSE_CTRL_POWERDOWN     (0x02U) /*!< Mouse control register powerdown bit */
#define REG_MOTION_CTRL_MOT_A        (0x80U) /*!< Motion control register polarity bit */
#define REG_MOTION_CTRL_MOT_S        (0x40U) /*!< Motion control register edge sensitivity bit */
#define REG_MOUSE_CTRL_RES_EN        (0x40U) /*!< Mouse control register resolution enable bit */
#define REG_MOUSE_CTRL_BIT_REPORTING (0x80U) /*!< Mouse control register "number of motion bits" bit*/

void adns2080_movement_read(int16_t * deltaX, int16_t * deltaY)
{
    uint8_t delta_x;       /*!< Stores REG_DELTA_X contents */
    uint8_t delta_y;       /*!< Stores REG_DELTA_Y contents */
    uint8_t delta_xy_high; /*!< Stores REG_DELTA_XY contents which contains upper 4 bits for both delta_x and delta_y when 12 bit mode is used */
    uint8_t delta_x_high;  /*!< Stores delta_x 4 MSB bits */
    uint8_t delta_y_high;  /*!< Stores delta_y 4 MSB bits */

    uint16_t u16_deltaX; /*!< This is used to buffer the result and will be cast later to int16_t */
    uint16_t u16_deltaY; /*!< This is used to buffer the result and will be cast later to int16_t */

    delta_x = sdio_read_byte(REG_DELTA_X);
    delta_y = sdio_read_byte(REG_DELTA_Y);

    if (adns2080_motion_bits_read() == ADNS2080_MOTION_BITS_12)
    {
        // In 12 bit mode the upper 4 bits are stored in a separate register
        // where first 4 upper bits are for delta_x and lower 4 bits for delta_y.
        delta_xy_high = sdio_read_byte(REG_DELTA_XY_HIGH);

        delta_x_high = ((delta_xy_high & 0xF0) >> 4);
        delta_y_high = (delta_xy_high & 0x0F);

        // Check if MSB is 1. If it is, this is a negative number and we have
        // to fill the upper unused bits with 1s.
        if (delta_x_high & 0x08)
        {
            u16_deltaX = 0xF000;
        }
        else
        {
            u16_deltaX = 0x0000;
        }

        // Check if MSB is 1. If it is, this is a negative number and we have
        // to fill the upper unused bits with 1s.
        if (delta_y_high & 0x08)
        {
            u16_deltaY = 0xF000;
        }
        else
        {
            u16_deltaY = 0x0000;
        }

        u16_deltaX |= (delta_x_high << 4) | delta_x;
        u16_deltaY |= (delta_y_high << 4) | delta_y;
    }
    else // Only 8 bits is used for motion data
    {
        // Check if MSB is 1. If it is, this is a negative number and we have
        // to fill the upper unused bits with 1s.
        if (delta_x & 0x80)
        {
            u16_deltaX = 0xFF00;
        }
        else
        {
            u16_deltaX = 0x0000;
        }

        // Check if MSB is 1. If it is, this is a negative number and we have
        // to fill the upper unused bits with 1s.
        if (delta_y & 0x80)
        {
            u16_deltaY = 0xFF00;
        }
        else
        {
            u16_deltaY = 0x0000;
        }

        u16_deltaX |= delta_x;
        u16_deltaY |= delta_y;
    }

    *deltaX = (int16_t)u16_deltaX;
    *deltaY = (int16_t)u16_deltaY;
}

adns2080_motion_bits_t adns2080_motion_bits_read(void)
{
    /* Read the most significant bit */
    return (adns2080_motion_bits_t)((sdio_read_byte(REG_MOUSE_CTRL) >> 7) & 0x01);
}

bool adns2080_is_motion_detected(void)
{
    return ((sdio_read_byte(REG_MOTION_ST) & 0x80) != 0);
}

uint8_t adns2080_product_id_read(void)
{
    return sdio_read_byte(REG_PROD_ID);
}

uint8_t adns2080_revision_id_read(void)
{
    return sdio_read_byte(REG_REV_ID);
}

adns2080_status_t adns2080_init(void)
{
    sdio_init();
    adns2080_reset();

    if (adns2080_product_id_read() != ADNS2080_PRODUCT_ID)
    {
        return ADNS2080_CHIP_NOT_DETECTED;
    }

    sdio_write_byte(REG_BURST_READ_FIRST, REG_DELTA_X);
    sdio_write_byte(REG_BURST_READ_LAST, REG_DELTA_Y);

    return ADNS2080_OK;
}

void adns2080_reset(void)
{
    sdio_write_byte(REG_RESET, ADNS2080_RESET_NUMBER);
}

void adns2080_powerdown(void)
{
    sdio_write_byte(REG_MOUSE_CTRL, REG_MOUSE_CTRL_POWERDOWN);
}

void adns2080_wakeup(void)
{
    adns2080_reset();
}

adns2080_status_t adns2080_motion_interrupt_set(motion_output_polarity_t polarity, motion_output_sensitivity_t sensitivity)
{
    uint8_t           databyte = 0;
    adns2080_status_t status   = ADNS2080_OK;

    switch (polarity)
    {
        case ADNS2080_MOTION_OUTPUT_POLARITY_LOW:
            databyte = 0; // Clear REG_MOTION_CTRL_MOT_A bit
            break;

        case ADNS2080_MOTION_OUTPUT_POLARITY_HIGH:
            databyte = REG_MOTION_CTRL_MOT_A;
            break;

        default:
            status = ADNS2080_INVALID_PARAMETER;
            break;
    }

    switch (sensitivity)
    {
        case ADNS2080_MOTION_OUTPUT_SENSITIVITY_LEVEL:
            databyte &= ~(REG_MOTION_CTRL_MOT_S);
            break;

        case ADNS2080_MOTION_OUTPUT_SENSITIVITY_EDGE:
            databyte |= (REG_MOTION_CTRL_MOT_S);
            break;

        default:
            status = ADNS2080_INVALID_PARAMETER;
            break;
    }

    if (status == ADNS2080_OK)
    {
        sdio_write_byte(REG_MOTION_CTRL, databyte);
    }

    return status;
}

adns2080_status_t adns2080_resolution_set(adns2080_resolution_t resolution)
{
    uint8_t           databyte = sdio_read_byte(REG_MOUSE_CTRL);
    adns2080_status_t status   = ADNS2080_OK;

    // Enable resolution settings on REG_MOUSE_CTRL [4:2]
    databyte |= (REG_MOUSE_CTRL_RES_EN);

    switch (resolution)
    {
        case ADNS2080_RESOLUTION_250DPI:
        case ADNS2080_RESOLUTION_500DPI:
        case ADNS2080_RESOLUTION_1000DPI:
        case ADNS2080_RESOLUTION_1250DPI:
        case ADNS2080_RESOLUTION_1500DPI:
        case ADNS2080_RESOLUTION_1750DPI:
        case ADNS2080_RESOLUTION_2000DPI:
            // Clear resolution bits [4:2]
            databyte &= ~(0x1C); // 0b00011100;
            // Set resolution bits
            databyte |= (uint8_t)((uint8_t)resolution << 2);
            break;

        default:
            status = ADNS2080_INVALID_PARAMETER;
            break;
    }

    if (status == ADNS2080_OK)
    {
        sdio_write_byte(REG_MOUSE_CTRL, databyte);
    }

    return status;
}

adns2080_status_t adns2080_motion_bits_set(adns2080_motion_bits_t motion_bits)
{
    uint8_t           databyte = sdio_read_byte(REG_MOUSE_CTRL);
    adns2080_status_t status   = ADNS2080_OK;

    switch (motion_bits)
    {
        case ADNS2080_MOTION_BITS_8:
            databyte &= ~(REG_MOUSE_CTRL_BIT_REPORTING);
            break;

        case ADNS2080_MOTION_BITS_12:
            databyte |= (REG_MOUSE_CTRL_BIT_REPORTING);
            break;

        default:
            status = ADNS2080_INVALID_PARAMETER;
            break;
    }

    if (status == ADNS2080_OK)
    {
        sdio_write_byte(REG_MOUSE_CTRL, databyte);
    }

    return status;
}

void adns2080_rest_periods_set(uint8_t rest1_period, uint8_t rest2_period, uint8_t rest3_period)
{
    adns2080_mode_t current_mode = adns2080_force_mode_read();
    adns2080_force_mode_set(ADNS2080_MODE_RUN1);
    sdio_write_byte(REG_REST1_PERIOD, rest1_period);
    sdio_write_byte(REG_REST2_PERIOD, rest2_period);
    sdio_write_byte(REG_REST3_PERIOD, rest3_period);
    adns2080_force_mode_set(current_mode);
}

void adns2080_downshift_times_set(uint8_t run_to_rest1_mode_time, uint8_t rest1_to_rest2_mode_time, uint8_t rest2_to_rest3_mode_time)
{
    adns2080_mode_t current_mode = adns2080_force_mode_read();
    adns2080_force_mode_set(ADNS2080_MODE_RUN1);
    sdio_write_byte(REG_RUN_DOWNSHIFT, run_to_rest1_mode_time);
    sdio_write_byte(REG_REST1_DOWNSHIFT, rest1_to_rest2_mode_time);
    sdio_write_byte(REG_REST2_DOWNSHIFT, rest2_to_rest3_mode_time);
    adns2080_force_mode_set(current_mode);
}

adns2080_mode_t adns2080_force_mode_read(void)
{
    return (adns2080_mode_t)((sdio_read_byte(REG_PERFORMANCE) >> 4) & 0x07);
}

void adns2080_force_mode_set(adns2080_mode_t mode)
{
    sdio_write_byte(REG_PERFORMANCE, (uint8_t)((uint8_t)mode << 4));
}

/*lint --flb "Leave library region" */
