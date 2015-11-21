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
 * @file ips_rotate.c
 * @brief IPU rotate IPU.
 * @ingroup diag_ipu
 */

#include <string.h>
#include <stdio.h>

#include "ips_test.h"

int32_t ips_rotate_test(ips_dev_panel_t * panel)
{
    uint32_t ipu_index = 1;     // use ipu 1
    uint32_t channel_in, channel_out;
    uint32_t rot_in_mem = CH28_EBA0, rot_out_mem = CH23_EBA0;
    ipu_rot_info_t rot_info;
    uint32_t taskType = PP_TASK;
    uint8_t revchar;

    /*Rotation Test. Press y to rotate 90 degree. */
    printf("\n-- Rotate central image block --\n");
    printf("Press 'Y' / 'y' for 90 degree clockwise rotation.\nOther key to exit.)\n");

    /*setup IPU display channel */
    ipu_display_setup(ipu_index, rot_out_mem, (uint32_t) NULL, INTERLEAVED_RGB565, panel);

    /*enable ipu display channel */
    ipu_enable_display(ipu_index);

    /*load image */
    load_centralized_image(rot_out_mem, panel);

    /*setup ic task and dma channel for rotate. */
    switch (taskType) {
    case PrP_ENC_TASK:
        channel_in = MEM_TO_IC_PRPENC_ROT_CH45;
        channel_out = IC_PRPENC_ROT_TO_MEM_CH48;
        break;
    case PrP_VF_TASK:
        channel_in = MEM_TO_IC_PRPVF_ROT_CH46;
        channel_out = IC_PRPVF_ROT_TO_MEM_CH49;
        break;
    case PP_TASK:
        channel_in = MEM_TO_IC_PP_ROT_CH47;
        channel_out = IC_PP_ROT_TO_MEM_CH50;
        break;
    default:
        printf("Wrong IC processing task.\n");
        return FALSE;
    }

    /*setup ipu rotate channel and task */
    memset(&rot_info, 0x00, sizeof(ipu_rot_info_t));
    rot_info.width_in = 640;
    rot_info.height_in = 480;
    rot_info.width_out = rot_info.height_in;
    rot_info.height_out = rot_info.width_in;
    rot_info.strideline_in = panel->width * 2;
    rot_info.strideline_out = panel->width * 2;
    rot_info.pixel_format_in = INTERLEAVED_RGB565;
    rot_info.pixel_format_out = INTERLEAVED_RGB565;
    rot_info.rot = 1;
    rot_info.hf = 0;
    rot_info.vf = 0;
    rot_info.addr0_in =
        rot_in_mem + (panel->height - rot_info.height_in) * panel->width + panel->width -
        rot_info.width_in;
    rot_info.addr0_out =
        rot_out_mem + (panel->height - rot_info.height_out) * panel->width + panel->width -
        rot_info.width_out;

    /*rotate idmac config */
    ipu_rotate_idmac_config(ipu_index, channel_in, channel_out, rot_info);

    /*rotate ic config */
    ipu_ic_enable(ipu_index, 0, 0);
    ipu_ic_rotation_config(ipu_index, taskType, rot_info.rot, rot_info.hf, rot_info.vf);

    ipu_ic_task_enable(ipu_index, PP_TASK, IC_PP, 1);
    ipu_ic_task_enable(ipu_index, PP_TASK, IC_ROT, 1);
    ipu_ic_enable(ipu_index, 1, 1);

    while (1) {
        do {
            revchar = getchar();
        } while (revchar == (uint8_t) 0xFF);
        if (revchar == 'Y' || revchar == 'y') {
            memcpy((void *)rot_in_mem, (void *)rot_out_mem, panel->width * panel->height * 2);
            while (ipu_idmac_channel_busy(1, channel_out)) ;
            while (ipu_idmac_channel_busy(1, channel_in)) ;
            ipu_channel_buf_ready(1, channel_out, 0);
            ipu_channel_buf_ready(1, channel_in, 0);
        } else
            break;
    };

    return TRUE;
}
