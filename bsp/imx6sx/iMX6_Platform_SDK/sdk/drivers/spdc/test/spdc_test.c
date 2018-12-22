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
#include "io.h"

static int spdc_initialized = 0;

int spdc_test(void)
{
    int ret = 0;

    char recvCh = NONE_CHAR;

    spdc_iomux_config();

    /*turn on the SPDC clock */
    spdc_clock_gate(0);

    /*confgure the spdc system clock, 40MHz for 800*600@50Hz refresh rate */
    sipix_epd_clock_setting(40);

    spdc_enable_interrupts(0xF);    //enable all interrupts

    spdc_temperature_set(25);

    if (spdc_initialized == 0) {
        /*step1: cofnigure the wroking memory */
        spdc_set_buffers();

        /*step2: configure the waveform LUT */
        spdc_load_wv_lut(auo_lut, SPDC_LUT_BUF_ADDR);
        while (!spdc_check_lut_download_finish()) ;

        /*step3: configure the power sequence
         * SHD_N -> PWR0 -> PWR1 -> PWR2 ->PWR3*/
        spdc_power_up();

        /*step4: send the basic initial setting to SPDC */
        spdc_panel_init_set(0,  //resolution is 800*600 landscape
                            1,  //disable HBURST
                            0,  //gray mode
                            1,  //set power ready and trigger display
                            0,  //enable auto data filter
                            0,  //RL
                            0,  //UD
                            0,  //single gate
                            0   //low enable
            );
        while (!spdc_check_tcon_init_finish()) ;
        spdc_initialized = 1;
    }

    spdc_operation_start(DISP_RESET);
    while (!spdc_check_operation_finish()) ;

    spdc_update_image((SPDC_HSIZE - 600) / 2, (SPDC_VSIZE - 240) / 2, 600, 240);
    spdc_trigger_display(0);
    while (!spdc_check_operation_finish()) ;

    printf
        ("Do you see Freescale logo displayed on the sipix e-ink panel?(Y/y for yes, other for no)\n");

    do {
        recvCh = getchar();
    }
    while (recvCh == NONE_CHAR);

    printf("%c\n", recvCh);

    if (recvCh == 'Y' || recvCh == 'y') {
        ret = 0;
    } else {
        ret = -1;
    }

    return ret;
}
