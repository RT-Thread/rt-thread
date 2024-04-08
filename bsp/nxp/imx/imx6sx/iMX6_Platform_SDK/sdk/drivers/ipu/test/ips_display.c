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

/*!
 * @file ips_display.c
 * @brief IPU display test.
 * @ingroup diag_ipu
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ips_test.h"

/*!
 * LVDS display test case. note that the memory for the flow is not released
 *
 * @param	panel:		ipu panel configuration data structure
 */
int32_t ips_display_test(ips_dev_panel_t * panel)
{
    uint32_t disp_mem = CH23_EBA0;
    uint32_t ipu_index = 1;     // use ipu 1
    uint8_t revchar;

    printf("\n-- Single Image Display -- \n");
    /*reset IPU */
    ipu_sw_reset(ipu_index, 1000);

    /*setup IPU display channel */
    ipu_display_setup(ipu_index, disp_mem, (uint32_t) NULL, INTERLEAVED_RGB565, panel);

    /*enable ipu display channel */
    ipu_enable_display(ipu_index);

    /*load image */
    load_centralized_image(disp_mem, panel);

    printf("Do you see the image (y or n)?\n");
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);
    if (!(revchar == 'Y' || revchar == 'y'))
        return FALSE;

    return TRUE;
}

/*!
 * HDMI 1080P60 display stream
 */
int32_t ips_hdmi_stream(void)
{
    int32_t ipu_index = 1;      // use ipu 1
    uint32_t disp_mem = CH23_EBA0;
    ips_dev_panel_t *panel;
    uint8_t revchar;

    /*enable panel */
    panel = search_panel("HDMI 1080P 60Hz");
    panel->panel_init(&ipu_index);

    printf("\n-- Single Image Display -- \n");
    /*reset IPU */
    ipu_sw_reset(ipu_index, 1000);

    /*setup IPU display channel */
    ipu_display_setup(ipu_index, disp_mem, (uint32_t) NULL, INTERLEAVED_RGB565, panel);

    /*enable ipu display channel */
    ipu_enable_display(ipu_index);

    /*load image */
    load_centralized_image(disp_mem, panel);

    printf("Do you see the image (y or n)?\n");
    do {
        revchar = getchar();
    } while (revchar == (uint8_t) 0xFF);
    if (revchar == 'Y' || revchar == 'y') {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*!
 * HDMI 700P60 display stream
 *
 * @param	ipu_index:	ipu index
 */
int32_t ips_hdmi_720P60_stream(int32_t ipu_index)
{
    uint32_t disp_mem0 = CH23_EBA0, disp_mem1 = (uint32_t) NULL;
    ips_dev_panel_t *panel;

    /*enable panel */
    panel = search_panel("HDMI 720P 60Hz");
    panel->panel_init(&ipu_index);

    /*reset IPU */
    ipu_sw_reset(ipu_index, 1000);

    /*setup IPU display channel */
    ipu_display_setup(ipu_index, disp_mem0, disp_mem1, PARTIAL_INTERLEAVED_YUV420, panel);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_UBO,
                        FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 8);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_SLY, FRAME_MAX_WIDTH - 1);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_SLUV, FRAME_MAX_WIDTH - 1);

    memset((void *)disp_mem0, 0x10, FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT);
    memset((void *)disp_mem0 + FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT, 0x80,
           FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 2);
    memset((void *)CH23_EBA1, 0x10, panel->width * panel->height);
    memset((void *)CH23_EBA1 + panel->width * FRAME_MAX_HEIGHT, 0x80,
           panel->width * panel->height / 2);

    /*realloc the DMFC fifo */
    ipu_dmfc_alloc(ipu_index, 23, DMFC_FIFO_512X128, 0, DMFC_BURST_32X128);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_NPB, 63);

    /*enable ipu display channel */
    ipu_enable_display(ipu_index);
    return 1;
}

/*!
 * HDMI 1080P60 display stream
 *
 * @param	ipu_index:	ipu index
 */
int32_t ips_hdmi_1080P60_stream(int32_t ipu_index)
{
    uint32_t disp_mem0 = CH23_EBA0, disp_mem1 = (uint32_t) NULL;
    ips_dev_panel_t *panel;

    /*enable panel */
    panel = search_panel("HDMI 1080P 60Hz");
    panel->panel_init(&ipu_index);

    /*reset IPU */
    ipu_sw_reset(ipu_index, 1000);

    /*setup IPU display channel */
    ipu_display_setup(ipu_index, disp_mem0, disp_mem1, PARTIAL_INTERLEAVED_YUV420, panel);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_UBO,
                        FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 8);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_SLY, FRAME_MAX_WIDTH - 1);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_SLUV, FRAME_MAX_WIDTH - 1);

    memset((void *)disp_mem0, 0x10, FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT);
    memset((void *)disp_mem0 + FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT, 0x80,
           FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 2);

    /*realloc the DMFC fifo */
    ipu_dmfc_alloc(ipu_index, 23, DMFC_FIFO_512X128, 0, DMFC_BURST_32X128);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_NPB, 63);

    /*enable ipu display channel */
    ipu_enable_display(ipu_index);
    return 1;
}

/*!
 * SII9022 1080P60 display stream
 * @param	ipu_index:	ipu index
 */
int32_t ips_ext_hdmi_transmitter_1080P60_stream(int32_t ipu_index)
{
    uint32_t disp_mem = CH23_EBA1;
    ips_dev_panel_t *panel;

    /*enable panel */
    panel = search_panel("SII9022 1080P 60Hz");
    panel->panel_init(&ipu_index);

    /*reset IPU */
    ipu_sw_reset(ipu_index, 1000);

    /*setup IPU display channel */
    ipu_display_setup(ipu_index, disp_mem, (uint32_t) NULL, PARTIAL_INTERLEAVED_YUV420, panel);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_UBO,
                        FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 8);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_SLY, FRAME_MAX_WIDTH - 1);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_SLUV, FRAME_MAX_WIDTH - 1);

    /*realloc the DMFC fifo */
    ipu_dmfc_alloc(ipu_index, 23, DMFC_FIFO_512X128, 0, DMFC_BURST_32X128);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_NPB, 63);

    /*enable ipu display channel */
    ipu_enable_display(ipu_index);

    return 1;
}

/*!
 * LVDS display stream
 *
 * @param	ipu_index:	ipu index
 */
int32_t ips_hannstar_xga_yuv_stream(int32_t ipu_index)
{
    uint32_t disp_mem0 = CH23_EBA1, disp_mem1 = (uint32_t) NULL;
    ips_dev_panel_t *panel;

    /*enable panel */
    panel = search_panel("HannStar XGA LVDS");
    panel->panel_init(&ipu_index);

    /*reset IPU */
    ipu_sw_reset(ipu_index, 1000);

    /*setup IPU display channel */
    ipu_display_setup(ipu_index, disp_mem0, disp_mem1, PARTIAL_INTERLEAVED_YUV420, panel);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_UBO,
                        FRAME_MAX_WIDTH * FRAME_MAX_HEIGHT / 8);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_SLY, FRAME_MAX_WIDTH - 1);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_SLUV, FRAME_MAX_WIDTH - 1);

    memset((void *)disp_mem0, 0x10, panel->width * panel->height);
    memset((void *)disp_mem0 + panel->width * FRAME_MAX_HEIGHT, 0x80,
           panel->width * panel->height / 2);

    /*realloc the DMFC fifo */
    ipu_dmfc_alloc(ipu_index, 23, DMFC_FIFO_512X128, 0, DMFC_BURST_32X128);
    ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, 23), NON_INTERLEAVED_NPB, 63);

    /*enable ipu display channel */
    ipu_enable_display(ipu_index);

    return 1;
}

/*!
 * MIPI display stream
 *
 * @param	ipu_index:	ipu index
 */
int32_t ips_mipi_wvga_rgb_stream(int32_t ipu_index)
{
    uint32_t disp_mem0 = CH23_EBA0, disp_mem1 = (uint32_t) NULL;
    ips_dev_panel_t *panel;

    panel = search_panel("TRULY MIPI TFT480800");

    /*reset IPU */
    ipu_sw_reset(ipu_index, 1000);

    /*setup IPU display channel */
    ipu_display_setup(ipu_index, disp_mem0, disp_mem1, INTERLEAVED_RGB565, panel);

    /*load image */
    load_centralized_image(disp_mem0, panel);

    /*enable ipu display channel */
    ipu_enable_display(ipu_index);

    /*enable panel */
    panel->panel_init(&ipu_index);

    return 1;
}
