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

#include "epdc/epdc_regs.h"
#include "epdc/epdc.h"
#include "utility/menu.h"
#include "sdk_types.h"

const char g_epdc_test_name[] = "EPDC Test";

void epdc_pvi_svga_sdr_init(void);
void epdc_pvi_svga_sdr_test(void);
void epdc_send_mode0_to_black_update(void);
void epdc_update_image(int width, int height, unsigned int img_base);
void epdc_send_image_update(unsigned int lut, epdc_upd_area_t upzone, unsigned int image_addr);
void epdc_send_erase_to_color(unsigned int lut, unsigned int mode,
                              epdc_upd_area_t upzone, int color);

static int epdc_initialized = 0;

test_return_t epdc_test(void)
{
    char recvCh = NONE_CHAR;
    const char* indent = menu_get_indent();

    if (epdc_initialized == 0) {
        epdc_iomux_config();

        epdc_clock_setting(27);

        epdc_power_supply();    // max17135 setting

        epdc_reset();

        epdc_pvi_svga_sdr_init();

        epdc_initialized = 1;
    }

    epdc_update_image(600, 230, IMAGE_STORE_0_ADDR);

    printf("%sDo you see Freescale logo displayed on the e-ink panel?(Y/y for yes, other for no)\n", indent);

    do {
        recvCh = getchar();
    }
    while (recvCh == NONE_CHAR);

    printf("%c\n", recvCh);

    if (recvCh == 'Y' || recvCh == 'y')
        return TEST_PASSED;
    else
        return TEST_FAILED;
}

void epdc_pvi_svga_sdr_init(void)
{
    epdc_buffer_init();

    epdc_init_settings();

    epdc_load_image();

    //epdc_dump_registers();

    /* Start commands */
    epdc_send_mode0_to_black_update();
}

void epdc_update_image(int width, int height, unsigned int img_base)
{
    // Send FSL across the screen
    int lut = 15;
    epdc_upd_area_t upz;

    if (width > EPDC_HSIZE || height > EPDC_VSIZE) {
        width = EPDC_HSIZE;
        height = EPDC_VSIZE;
    }

    upz.coordinate.x = (EPDC_HSIZE - width) / 2;
    upz.coordinate.y = (EPDC_VSIZE - height) / 2;
    upz.size.width = width;
    upz.size.height = height;

    lut = epdc_get_next_lut();
    epdc_send_erase_to_color(lut, EPDC_WV_MODE__GC16, upz, 0xF);

    while (epdc_is_lut_active(lut)) ;

    lut = epdc_get_next_lut();
    epdc_send_image_update(lut, upz, img_base);

    while (epdc_is_lut_active(lut)) ;
}

void epdc_send_mode0_to_black_update(void)
{
    int lut = 15;

    /* wait for working buffer to be idle */
    while (epdc_is_working_buffer_busy()) ;

    lut = epdc_get_next_lut();
    /* UPD update */
    epdc_set_update_addr(UPD_BUFFER_MODE_0_ADDR);
    epdc_set_update_coord(0, 0);
    epdc_set_update_dimensions(EPDC_HSIZE, EPDC_VSIZE);
    epdc_submit_update(lut, EPDC_WV_MODE__INIT, EPDC_UPD_UPDATE_MODE__FULL, 0x0, 0x0);

    /* Wait for LUT to finish */
    while (epdc_is_lut_active(lut)) ;
}

void epdc_send_image_update(unsigned int lut, epdc_upd_area_t upzone, unsigned int image_addr)
{
    while (epdc_is_working_buffer_busy()) ;

    /* UPD update */
    epdc_set_update_addr(image_addr);
    epdc_set_update_coord(upzone.coordinate.x, upzone.coordinate.y);
    epdc_set_update_dimensions(upzone.size.width, upzone.size.height);  // 600x230
    epdc_submit_update(lut, EPDC_WV_MODE__GC16, EPDC_UPD_UPDATE_MODE__PARTIAL, 0x0, 0x0);
}

void epdc_send_erase_to_color(unsigned int lut, unsigned int mode,
                              epdc_upd_area_t upzone, int color)
{
    while (epdc_is_working_buffer_busy()) ;

    /* UPD update */
    epdc_set_update_addr(UPD_BUFFER_MODE_0_ADDR);
    epdc_set_update_coord(upzone.coordinate.x, upzone.coordinate.y);
    epdc_set_update_dimensions(upzone.size.width, upzone.size.height);  // 600x230
    epdc_submit_update(lut, mode, EPDC_UPD_UPDATE_MODE__PARTIAL, 0x1, color);   //0xf0
}
