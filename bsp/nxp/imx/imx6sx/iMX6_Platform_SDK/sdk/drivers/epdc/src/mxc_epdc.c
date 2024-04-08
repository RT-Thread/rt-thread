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

#include "epdc/epdc_regs.h"
#include "epdc/epdc.h"
#include "epdc/waveform_data.h"
#include "epdc/fsl_image.h"
#include "registers/regsepdc.h"
#include "sdk.h"

////////////////////////////////////////////////////////////////////////////////
// CODE
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Check the waveform data
 *
 * @param wv_buf_orig expected waveform data
 * @param wv_buf_cur current waveform data
 * @param wv_buf_size total waveform data size
 *
 * @return TRUE for match and False for mismatch
 */
static int check_waveform(unsigned int *wv_buf_orig, unsigned int *wv_buf_cur,
                          unsigned int wv_buf_size)
{
    int i;
    int is_mismatch = FALSE;

    for (i = 0; i < wv_buf_size; i++) {
        if (wv_buf_orig[i] != wv_buf_cur[i]) {
            is_mismatch = TRUE;
            printf("Waveform Mismatch - wv_buf_orig[%d] = 0x%x, wv_buf_cur[%d] = 0x%x\n",
                   i, wv_buf_orig[i], i, wv_buf_cur[i]);
        }
    }

    return is_mismatch;
}

/*!
 * @brief Clock gate setting for the EPD controller
 */
static void epdc_clk_gate(int on_off)
{
    /* zero for normal operation */
    if (on_off) {
        // Enable clock gating (clear to enable)
        HW_EPDC_CTRL_CLR(EPDC_CTRL_CLKGATE);
    } else {
        // Disable clock gating
        HW_EPDC_CTRL_SET(EPDC_CTRL_CLKGATE);
    }
}

void epdc_reset(void)
{
    HW_EPDC_CTRL_SET(EPDC_CTRL_SFTRST);

    while (!(HW_EPDC_CTRL_RD() & EPDC_CTRL_CLKGATE)) ;

    HW_EPDC_CTRL_CLR(EPDC_CTRL_SFTRST); // clear the soft reset

    epdc_clk_gate(TRUE);

    while (HW_EPDC_CTRL_RD() & (EPDC_CTRL_SFTRST | EPDC_CTRL_CLKGATE)) ;
}

/*!
 * @brief Set the update data swizzles, which will indicate how to swap
 * the data before the Write Buffer is constructed
 *
 * @param upd_swizzle Data swap mode
 */
static void epdc_set_update_swizzle(unsigned int upd_swizzle)
{
    HW_EPDC_CTRL_CLR(EPDC_CTRL_UPD_DATA_SWIZZLE_MASK);
    HW_EPDC_CTRL_SET(upd_swizzle);
}

/*!
 * @brief Set the LUT data swizzles
 *
 * @param lut_swizzle Data swap mode
 */
static void epdc_set_lut_swizzle(unsigned int lut_swizzle)
{
    HW_EPDC_CTRL_CLR(EPDC_CTRL_LUT_DATA_SWIZZLE_MASK);
    HW_EPDC_CTRL_SET(lut_swizzle);
}

/*!
 * @brief Set the waveform data address
 *
 * @param addr Waveform data address
 */
static void epdc_set_waveform_addr(unsigned int addr)
{
    HW_EPDC_WVADDR_WR(addr);
}

/*!
 * @brief Set the temperature
 *
 * @param temp Temperature index, which is not the real degree but an
 * index to look-up table
 */
static void epdc_set_temp(unsigned int temp)
{
    HW_EPDC_TEMP_WR(temp);
}

/*!
 * @brief Set the resolution of the screen
 *
 * @param width width of panel resolution
 * @param height height of panel resolution
 */
static void epdc_set_screen_res(unsigned int width, unsigned int height)
{
    HW_EPDC_RES_WR((height << EPDC_RES_VERTICAL_OFFSET) | width);
}

/*!
 * @brief Set the EPDC working buffer address
 *
 * @param addr working buffer address
 */
static void epdc_set_working_buf_addr(unsigned int addr)
{
    HW_EPDC_WB_ADDR_WR(addr);
#ifdef CHIP_MX6SL               // Note: this is not documented in headers
    writel(addr, EPDC_PIGEON_16_1);
#endif
}

void epdc_set_update_addr(unsigned int addr)
{
    HW_EPDC_UPD_ADDR_WR(addr);
}

void epdc_set_update_coord(unsigned int x, unsigned int y)
{
    HW_EPDC_UPD_CORD_WR((y << EPDC_UPD_CORD_YCORD_OFFSET) | x);
}

void epdc_set_update_dimensions(unsigned int width, unsigned int height)
{
    HW_EPDC_UPD_SIZE_WR((height << EPDC_UPD_SIZE_HEIGHT_OFFSET) | width);
}

void epdc_submit_update(unsigned int lut_num, unsigned int waveform_mode,
                        unsigned int update_mode, int use_test_mode, unsigned int np_val)
{
    unsigned int reg_val = 0;

    if (use_test_mode) {
        HW_EPDC_UPD_FIXED_WR(((np_val << EPDC_UPD_FIXED_FIXNP_OFFSET) &
                              EPDC_UPD_FIXED_FIXNP_MASK) | EPDC_UPD_FIXED_FIXNP_EN);

        reg_val = EPDC_UPD_CTRL_USE_FIXED;
    } else {
        reg_val = 0;
        HW_EPDC_UPD_FIXED_WR(reg_val);
    }

    reg_val |=
        ((lut_num << EPDC_UPD_CTRL_LUT_SEL_OFFSET) &
         EPDC_UPD_CTRL_LUT_SEL_MASK) |
        ((waveform_mode << EPDC_UPD_CTRL_WAVEFORM_MODE_OFFSET) &
         EPDC_UPD_CTRL_WAVEFORM_MODE_MASK) | update_mode;

    HW_EPDC_UPD_CTRL_WR(reg_val);
}

int epdc_is_lut_complete(unsigned int lut_num)
{
    unsigned int val = HW_EPDC_IRQ_RD();
    int is_compl = val & (1 << lut_num) ? TRUE : FALSE;

    return is_compl;
}

void epdc_clear_lut_complete_irq(unsigned int lut_num)
{
    HW_EPDC_IRQ_CLR(1 << lut_num);
}

int epdc_is_lut_active(unsigned int lut_num)
{
    unsigned int val = 0;
    int is_active = 0;

    if (lut_num < 32) {
        val = HW_EPDC_STATUS_LUTS1_RD();
    } else {
        val = HW_EPDC_STATUS_LUTS2_RD();
        lut_num = lut_num % 32;
    }
    is_active = val & (1 << lut_num) ? TRUE : FALSE;

    return is_active;
}

int epdc_any_luts_active(void)
{
    int any_active = HW_EPDC_STATUS_LUTS1_RD() & HW_EPDC_STATUS_LUTS2_RD()? TRUE : FALSE;

    return any_active;
}

int epdc_any_luts_available(void)
{
    int luts_available =
        (HW_EPDC_STATUS_NEXTLUT_RD() & EPDC_STATUS_NEXTLUT_NEXT_LUT_VALID) ? TRUE : FALSE;
    return luts_available;
}

int epdc_get_next_lut(void)
{
    unsigned int val = HW_EPDC_STATUS_NEXTLUT_RD() & EPDC_STATUS_NEXTLUT_NEXT_LUT_MASK;
    return val;
}

int epdc_is_working_buffer_busy(void)
{
    unsigned int val = HW_EPDC_STATUS_LUTS1_RD() & HW_EPDC_STATUS_LUTS2_RD();
    int is_busy = (val & EPDC_STATUS_WB_BUSY) ? TRUE : FALSE;

    return is_busy;
}

int epdc_is_working_buffer_complete(void)
{
    unsigned int val = HW_EPDC_IRQ_RD();
    int is_compl = (val & EPDC_IRQ_WB_CMPLT_IRQ) ? TRUE : FALSE;

    return is_compl;
}

int epdc_is_collision(void)
{
    unsigned int val = HW_EPDC_IRQ_RD();
    int is_compl = (val & EPDC_IRQ_LUT_COL_IRQ) ? TRUE : FALSE;

    return is_compl;
}

void epdc_dump_registers(void)
{
    unsigned int reg = EPDC_BASE_ADDR;

    for (reg = EPDC_BASE_ADDR; reg < EPDC_BASE_ADDR + 0x800; reg += 0x10)
        printf("reg %08x : %08x\n", reg, readl(reg));
}

/*!
 * @brief Set the horizontal timing per the panel
 *
 * @param horiz_start blanking start in horizontal
 * @param horiz_end blanking end in horizontal
 * @param hsync_width sync width
 * @param hsync_line_length active line width
 */
static void epdc_set_horizontal_timing(unsigned int horiz_start, unsigned int horiz_end,
                                       unsigned int hsync_width, unsigned int hsync_line_length)
{
    unsigned int reg_val =
        ((hsync_width << EPDC_TCE_HSCAN1_LINE_SYNC_WIDTH_OFFSET) &
         EPDC_TCE_HSCAN1_LINE_SYNC_WIDTH_MASK)
        | ((hsync_line_length << EPDC_TCE_HSCAN1_LINE_SYNC_OFFSET) &
           EPDC_TCE_HSCAN1_LINE_SYNC_MASK);
    HW_EPDC_TCE_HSCAN1_WR(reg_val);

    reg_val = ((horiz_start << EPDC_TCE_HSCAN2_LINE_BEGIN_OFFSET) & EPDC_TCE_HSCAN2_LINE_BEGIN_MASK)
        | ((horiz_end << EPDC_TCE_HSCAN2_LINE_END_OFFSET) & EPDC_TCE_HSCAN2_LINE_END_MASK);
    HW_EPDC_TCE_HSCAN2_WR(reg_val);
}

/*!
 * @brief Set the horizontal timing per the panel
 *
 * @param vert_start blanking start in vertical
 * @param vert_end blanking end in vertical
 * @param vsync_width sync width
 */
void epdc_set_vertical_timing(unsigned int vert_start, unsigned int vert_end,
                              unsigned int vsync_width)
{
    unsigned int reg_val =
        ((vert_start << EPDC_TCE_VSCAN_FRAME_BEGIN_OFFSET) & EPDC_TCE_VSCAN_FRAME_BEGIN_MASK)
        | ((vert_end << EPDC_TCE_VSCAN_FRAME_END_OFFSET) & EPDC_TCE_VSCAN_FRAME_END_MASK)
        | ((vsync_width << EPDC_TCE_VSCAN_FRAME_SYNC_OFFSET) & EPDC_TCE_VSCAN_FRAME_SYNC_MASK);
    HW_EPDC_TCE_VSCAN_WR(reg_val);
}

void epdc_init_settings(void)
{
    unsigned int reg_val;
    int left_margin, right_margin, xres, yres, upper_margin, lower_margin, hsync_len, vsync_len;
    int vscan_holdoff, sdoed_width, sdoed_delay, sdoez_width, sdoez_delay, gdclk_hp_offs, gdsp_offs,
        gdoe_offs, gdclk_offs, num_ce;

    /*set timming for E060 panel, fresh rate is 85, pclk is 26.667MHz */
    left_margin = 8;
    right_margin = 100;
    upper_margin = 4;
    lower_margin = 8;
    hsync_len = 4;
    vsync_len = 1;
    xres = EPDC_HSIZE;
    yres = EPDC_VSIZE;

    /*set scan mode */
    vscan_holdoff = 4;
    sdoed_width = 10;
    sdoed_delay = 20;
    sdoez_width = 10;
    sdoez_delay = 20;
    gdclk_hp_offs = 419;
    gdsp_offs = 20;
    gdoe_offs = 0;
    gdclk_offs = 5;
    num_ce = 1;

    /* Reset */
    epdc_reset();

    /* EPDC_CTRL, set data format, no data swizzle */
    epdc_set_update_swizzle(EPDC_CTRL_UPD_DATA_SWIZZLE_ALL_BYTES_SWAP);
    epdc_set_lut_swizzle(EPDC_CTRL_LUT_DATA_SWIZZLE_NO_SWAP);

    /* EPDC_FORMAT - 2bit TFT and 4bit Buf pixel format, truncate data */
    reg_val = EPDC_FORMAT_TFT_PIXEL_FORMAT_2BIT
        | EPDC_FORMAT_BUF_PIXEL_FORMAT_P4N
        | ((0x0 << EPDC_FORMAT_DEFAULT_TFT_PIXEL_OFFSET) & EPDC_FORMAT_DEFAULT_TFT_PIXEL_MASK);
    HW_EPDC_FORMAT_WR(reg_val);

    /* EPDC_FIFOCTRL (disabled) */
    reg_val = ((100 << EPDC_FIFOCTRL_FIFO_INIT_LEVEL_OFFSET) & EPDC_FIFOCTRL_FIFO_INIT_LEVEL_MASK)
        | ((200 << EPDC_FIFOCTRL_FIFO_H_LEVEL_OFFSET) & EPDC_FIFOCTRL_FIFO_H_LEVEL_MASK)
        | ((100 << EPDC_FIFOCTRL_FIFO_L_LEVEL_OFFSET) & EPDC_FIFOCTRL_FIFO_L_LEVEL_MASK);
    HW_EPDC_FIFOCTRL_WR(reg_val);

    /* EPDC_TEMP - 8 for room temperature */
    epdc_set_temp(8);

    /* EPDC_RES */
    epdc_set_screen_res(EPDC_HSIZE, EPDC_VSIZE);

    /* EPDC_WB_ADDR */
    epdc_set_working_buf_addr(WB_DATA_ADDR);

    /* EPDC_WV_ADDR */
    epdc_set_waveform_addr(WV_DATA_ADDR);

    /*
     * EPDC_TCE_CTRL
     * VSCAN_HOLDOFF = 4
     * VCOM_MODE = MANUAL
     * VCOM_VAL = 0
     * DDR_MODE = DISABLED
     * LVDS_MODE_CE = DISABLED
     * LVDS_MODE = DISABLED
     * DUAL_SCAN = DISABLED
     * SDDO_WIDTH = 8bit
     * PIXELS_PER_SDCLK = 4
     */
    reg_val = ((4 << EPDC_TCE_CTRL_VSCAN_HOLDOFF_OFFSET) & EPDC_TCE_CTRL_VSCAN_HOLDOFF_MASK)
        | EPDC_TCE_CTRL_PIXELS_PER_SDCLK_4;
    HW_EPDC_TCE_CTRL_WR(reg_val);

    /* EPDC_TCE_HSCAN */
    epdc_set_horizontal_timing(left_margin, right_margin, hsync_len, hsync_len);

    /* EPDC_TCE_VSCAN */
    epdc_set_vertical_timing(upper_margin, lower_margin, vsync_len);

    /* EPDC_TCE_OE */
    reg_val = ((sdoed_width << EPDC_TCE_OE_SDOED_WIDTH_OFFSET) & EPDC_TCE_OE_SDOED_WIDTH_MASK)
        | ((sdoed_delay << EPDC_TCE_OE_SDOED_DLY_OFFSET) & EPDC_TCE_OE_SDOED_DLY_MASK)
        | ((sdoez_width << EPDC_TCE_OE_SDOEZ_WIDTH_OFFSET) & EPDC_TCE_OE_SDOEZ_WIDTH_MASK)
        | ((sdoez_delay << EPDC_TCE_OE_SDOEZ_DLY_OFFSET) & EPDC_TCE_OE_SDOEZ_DLY_MASK);
    HW_EPDC_TCE_OE_WR(reg_val);

    /* EPDC_TCE_TIMING1 */
    HW_EPDC_TCE_TIMING1_WR(0);

    /* EPDC_TCE_TIMING2 */
    reg_val = ((gdclk_hp_offs << EPDC_TCE_TIMING2_GDCLK_HP_OFFSET) & EPDC_TCE_TIMING2_GDCLK_HP_MASK)
        | ((gdsp_offs << EPDC_TCE_TIMING2_GDSP_OFFSET_OFFSET) & EPDC_TCE_TIMING2_GDSP_OFFSET_MASK);
    HW_EPDC_TCE_TIMING2_WR(reg_val);

    /* EPDC_TCE_TIMING3 */
    reg_val =
        ((gdoe_offs << EPDC_TCE_TIMING3_GDOE_OFFSET_OFFSET) & EPDC_TCE_TIMING3_GDOE_OFFSET_MASK)
        | ((gdclk_offs << EPDC_TCE_TIMING3_GDCLK_OFFSET_OFFSET) &
           EPDC_TCE_TIMING3_GDCLK_OFFSET_MASK);
    HW_EPDC_TCE_TIMING3_WR(reg_val);

    /*
     * EPDC_TCE_SDCFG
     * SDCLK_HOLD = 1
     * SDSHR = 1
     * NUM_CE = 1
     * SDDO_REFORMAT = FLIP_PIXELS
     * SDDO_INVERT = DISABLED
     * PIXELS_PER_CE = display horizontal resolution
     */
    reg_val = EPDC_TCE_SDCFG_SDCLK_HOLD | EPDC_TCE_SDCFG_SDSHR
        | ((num_ce << EPDC_TCE_SDCFG_NUM_CE_OFFSET) & EPDC_TCE_SDCFG_NUM_CE_MASK)
        | EPDC_TCE_SDCFG_SDDO_REFORMAT_FLIP_PIXELS
        | ((EPDC_HSIZE << EPDC_TCE_SDCFG_PIXELS_PER_CE_OFFSET) & EPDC_TCE_SDCFG_PIXELS_PER_CE_MASK);
    HW_EPDC_TCE_SDCFG_WR(reg_val);

    /*
     * EPDC_TCE_GDCFG
     * GDRL = 1
     * GDOE_MODE = 0;
     * GDSP_MODE = 0;
     */
    reg_val = EPDC_TCE_SDCFG_GDRL;
    HW_EPDC_TCE_GDCFG_WR(reg_val);

    /*
     * EPDC_TCE_POLARITY
     * SDCE_POL = ACTIVE LOW
     * SDLE_POL = ACTIVE HIGH
     * SDOE_POL = ACTIVE HIGH
     * GDOE_POL = ACTIVE HIGH
     * GDSP_POL = ACTIVE LOW
     */
    reg_val = EPDC_TCE_POLARITY_SDLE_POL_ACTIVE_HIGH
        | EPDC_TCE_POLARITY_SDOE_POL_ACTIVE_HIGH | EPDC_TCE_POLARITY_GDOE_POL_ACTIVE_HIGH;
    HW_EPDC_TCE_POLARITY_WR(reg_val);

    /* EPDC_IRQ_MASK */
    HW_EPDC_IRQ_MASK_WR(0x0007FFFF);

    /*
     * EPDC_GPIO
     */
    reg_val = ((0 << EPDC_GPIO_PWRCTRL_OFFSET) & EPDC_GPIO_PWRCTRL_MASK)
        | ((0 << EPDC_GPIO_BDR_OFFSET) & EPDC_GPIO_BDR_MASK);
    HW_EPDC_GPIO_WR(reg_val);
}

void epdc_buffer_init(void)
{
    memcpy((void *)WV_DATA_ADDR, wv_data, WV_SIZE * 4);

    memset((void *)WB_DATA_ADDR, 0x00, EPDC_VSIZE * EPDC_HSIZE / 2 * 4);

    memset((void *)UPD_BUFFER_MODE_0_ADDR, 0xFF, EPDC_VSIZE * EPDC_HSIZE / 2 * 4);
}

void epdc_load_image(void)
{
    memcpy((void *)IMAGE_STORE_0_ADDR, fsl_gray_600x230, 600 * 230);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
