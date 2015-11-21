/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

#include "spdc/spdc_regs.h"
#include "spdc/spdc.h"
#include "registers/regsspdc.h"
#include "io.h"

////////////////////////////////////////////////////////////////////////////////
// CODE
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Convert the image data from 8bpp to 4bpp mode
 *
 * @param width image width
 * @param height image height
 * @param in input image buffer address
 * @param out output image buffer address
 */
static void image_convert_8bpp_to_4bpp(int width, int height, uint8_t * in, uint8_t * out)
{
    uint8_t pixel_y8[4];
    int i, j;

    for (j = 0; j < height; j++)
        for (i = 0; i < (width / 4); i++) {
            pixel_y8[0] = *(in + j * width + i * 4);
            pixel_y8[1] = *(in + j * width + i * 4 + 1);
            pixel_y8[2] = *(in + j * width + i * 4 + 2);
            pixel_y8[3] = *(in + j * width + i * 4 + 3);

            *(out + j * SPDC_HSIZE / 2 + i * 2) = ((pixel_y8[3] >> 4) & 0xF) | (pixel_y8[2] & 0xF0);
            *(out + j * SPDC_HSIZE / 2 + i * 2 + 1) =
                ((pixel_y8[1] >> 4) & 0xF) | (pixel_y8[0] & 0xF0);
        }
}

void spdc_update_image(int pos_x, int pos_y, int width, int height)
{
    uint8_t *img = (uint8_t *) SPDC_NEXT_BUF_ADDR + pos_y * SPDC_HSIZE / 2 + pos_x / 2;

    HW_SPDC_UPDATE_X_Y_WR((((pos_x & (~0x3)) + 1) << 16) | ((pos_y & (~0x3)) + 1));
    HW_SPDC_UPDATE_W_H_WR((width << 16) | height);

    image_convert_8bpp_to_4bpp(width, height, (uint8_t *) fsl_gray_600x230, img);
}

void spdc_set_buffers(void)
{
    HW_SPDC_NEXT_BUF_WR(SPDC_NEXT_BUF_ADDR);
    HW_SPDC_CURRENT_BUF_WR(SPDC_CUR_BUF_ADDR);
    HW_SPDC_PREVIOUS_BUFF_WR(SPDC_PREV_BUF_ADDR);
    HW_SPDC_FRM_CNT_BUFF_WR(SPDC_FRM_CNT_BUF_ADDR);
}

void spdc_load_wv_lut(unsigned int *lut, unsigned int load_addr)
{
    memcpy((void *)load_addr, lut, auo_lut_size);
    /*the LUT download will start automatically once the register is configured */
    HW_SPDC_LUT_BUFF_WR(load_addr);
}

void spdc_clock_gate(int on)
{
    if (on) {
        HW_SPDC_SW_GATE_CLK_WR(1);  //close all the clock
    } else {
        HW_SPDC_SW_GATE_CLK_WR(0);  //turn on all the clock
    }
}

void spdc_panel_init_set(int resolution, int hburst_len_en, int rgbw_mode_en, int pwr_ready,
                         int data_filt_en, int rl, int ud, int dual_gate, int yoe_pol)
{
    unsigned int val =
        (hburst_len_en << 13) | (rgbw_mode_en << 11) | (pwr_ready << 10) | (data_filt_en << 9)
        | (rl << 8) | (ud << 7) | (resolution << 2) | (dual_gate << 1) | yoe_pol;
    HW_SPDC_PANEL_INIT_SET_WR(val);
}

void spdc_temperature_set(float degrade)
{
    int tmp = (int)(degrade * 2);
    if (tmp < 0) {
        tmp = (1 << 8) | (((~tmp) + 1) & 0xFF);
    } else {
        tmp = tmp & 0xFF;
    }
    HW_SPDC_TEMPER_SETTING_WR(tmp);
}

void spdc_operation_start(int opt)
{
    switch (opt) {
    case SW_TCON_RESET:
        HW_SPDC_OPERATE_WR(1 << 31);
        break;
    case DISP_RESET:
        HW_SPDC_OPERATE_WR(1 << 2);
        break;
    case DEEP_REFRESH:
        HW_SPDC_OPERATE_WR(1 << 1);
        break;
    case DISP_REFRESH:
        HW_SPDC_OPERATE_WR(1 << 0);
        break;
    default:
        printf("Error:  unkown operation !!\n");
    }
}

void spdc_enable_interrupts(unsigned int mask)
{
    HW_SPDC_INT_EN_WR(mask);
}

int spdc_check_lut_download_finish(void)
{
    unsigned val = HW_SPDC_INT_ST_CLR_RD() & 0x4;

    if (val == 0x4) {
        /*clear the state flag */
        HW_SPDC_INT_ST_CLR_WR(0x4);
        return 1;
    } else
        return 0;
}

int spdc_check_tcon_init_finish(void)
{
    unsigned val = HW_SPDC_INT_ST_CLR_RD() & 0x2;

    if (val == 0x2) {
        /*clear the state flag */
        HW_SPDC_INT_ST_CLR_WR(0x2);
        return 1;
    } else
        return 0;
}

int spdc_check_operation_finish(void)
{
    unsigned val = HW_SPDC_INT_ST_CLR_RD() & 0x1;

    if (val == 0x1) {
        /*clear the state flag */
        HW_SPDC_INT_ST_CLR_WR(0x1);
        return 1;
    } else
        return 0;
}

void spdc_trigger_display(int mode)
{
    switch (mode) {
    case 0:
        HW_SPDC_DISP_TRIGGER_WR(0x00000001);
        break;
    case 1:
        HW_SPDC_DISP_TRIGGER_WR(0x00000003);
        break;
    case 2:
        HW_SPDC_DISP_TRIGGER_WR(0x00000005);
        break;
    case 3:
        HW_SPDC_DISP_TRIGGER_WR(0x00000009);
        break;
    default:
        printf("Unknown display mode %d!!\n", mode);
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
