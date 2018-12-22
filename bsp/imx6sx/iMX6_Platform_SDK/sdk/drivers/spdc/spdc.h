/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _SPDC_H_
#define _SPDC_H_

#include "sdk_types.h"

//! @addtogroup diag_spdc
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define TRUE 1
#define FALSE 0

#define MODE0                   //Gray refresh mode with flashing
#define MODE1                   //Gray refresh mdoe without flashing
#define MODE2                   //Text mode
#define MODE3                   //hand writing mode

/*
 * Enable this define to have a default panel
 * loaded during driver initialization
 */
//#define DEFAULT_PANEL_HW_INIT

#define SPDC_HSIZE 800
#define SPDC_VSIZE 600

/*SPDC memory map*/
#if defined(CHIP_MX6SL)
#define WV_DATA_ADDR			0x93000000
#define SPDC_NEXT_BUF_ADDR		0x93100000
#define SPDC_CUR_BUF_ADDR		0x93200000
#define SPDC_PREV_BUF_ADDR		0x93300000
#define SPDC_FRM_CNT_BUF_ADDR	0x93400000
#define SPDC_LUT_BUF_ADDR		0x93500000
#else
#error SPDC is not supported on the platform
#endif

enum epd_operation {
    SW_TCON_RESET,
    DISP_RESET,
    DEEP_REFRESH,
    DISP_REFRESH,
};

extern unsigned int fsl_gray_600x230[];
extern unsigned int auo_lut[];
extern int auo_lut_size;
extern void sipix_epd_clock_setting(int freq);
extern void spdc_power_up(void);

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Update the image to be shown
 *
 * @param pos_x x coordinate of update area
 * @param pos_y y coordinate of udpate area
 * @param width width of update area
 * @param height height of update area
 */
void spdc_update_image(int pos_x, int pos_y, int width, int height);

/*!
 * @brief Set EPD buffers
 */
void spdc_set_buffers(void);

/*!
 * @brief Load waveform lut to EPD controller
 *
 * @param lut waveform lut address
 * @param load_addr load address
 */
void spdc_load_wv_lut(unsigned int *lut, unsigned int load_addr);

/*!
 * @brief SPDC clock gate
 *
 * @param on 1 means clock enable while 0 means disable
 */
void spdc_clock_gate(int on);

/*!
 * @brief Initialize the Sipix EPD panel
 *
 * @param resolution index of resolution look-up table
 * @param hburst_len_en burst length enable
 * @param rgbw_mode_enable color mode or gray mode selection
 * @param pwr_ready power ready indication
 * @param data_filt_en enable or disable the data filter
 * @param rl right-left scan direction
 * @param ud up-down scan direction
 * @param dual_gete single or dual gate selection, this is for drive IC
 * @param yoe_pol polariry setting of YOE signal
 */
void spdc_panel_init_set(int resolution, int hburst_len_en, int rgbw_mode_en, int pwr_ready,
                         int data_filt_en, int rl, int ud, int dual_gate, int yoe_pol);

/*!
 * @brief Set the temperature for controller
 *
 * @param degrade temperature in degree
 */
void spdc_temperature_set(float degrade);

/*!
 * @brief Start operation
 *
 * @param opt operation mode
 */
void spdc_operation_start(int opt);

/*!
 * @brief enable SPDC interrupt
 *
 * @param mask interrupt source mask
 */
void spdc_enable_interrupts(unsigned int mask);

/*!
 * @brief Check if LUT download finished 
 */
int spdc_check_lut_download_finish(void);

/*!
 * @brief Check if TCON initialization finished 
 */
int spdc_check_tcon_init_finish(void);

/*!
 * @brief Check if operation finished 
 */
int spdc_check_operation_finish(void);

/*!
 * @brief Trigger the display
 *
 * @param mode Mode selection for display
 */
void spdc_trigger_display(int mode);

//! @}

#endif /*_SPDC_H_*/

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
