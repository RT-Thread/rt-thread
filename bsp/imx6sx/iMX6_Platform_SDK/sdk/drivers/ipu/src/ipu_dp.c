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

/*!
 * @file ipu_dp.c
 * @brief display controller configuration of IPU.
 * @ingroup diag_ipu
 */

#include "ipu/ipu_common.h"

/*!
 * config the DP module, mainly to perform blending, CSC and gamma correction
 * @param   ipu_index ipu index
 * @param   csc_type csc type
 * @param   dual_disp dual display mode
 * @param   fg_xp foreground x position
 * @param   fg_yp foreground y position
 * @param   alpha alpha value
 */
void ipu_dp_config(uint32_t ipu_index, uint32_t csc_type, uint32_t dual_disp, uint32_t fg_xp,
                   uint32_t fg_yp, uint32_t alpha)
{
    ipu_dp_fg_config(ipu_index, dual_disp, fg_xp, fg_yp, alpha);
    ipu_dp_csc_config(ipu_index, 0, csc_type);
}

/*!
 * this function is used to config the color space conversion task in the DP
 * @param   ipu_index ipu index, 1 or 2
 * @param   dp display
 * @param   csc_type csc type
 */
void ipu_dp_csc_config(uint32_t ipu_index, uint32_t dp, uint32_t csc_type)
{
    uint32_t ipu_base_addr = 0;
    int32_t(*coef)[3];

    /*  Y = R *  .299 + G *  .587 + B *  .114;
       U = R * -.169 + G * -.332 + B *  .500 + 128.;
       V = R *  .500 + G * -.419 + B * -.0813 + 128.; */
    int32_t rgb2yuv_coef[5][3] = {
        {0x04D, 0x096, 0x01D},
        {0x3D5, 0x3AB, 0x080},
        {0x080, 0x395, 0x3EB},
        {0x0000, 0x0200, 0x0200},
        {0x2, 0x2, 0x2},
    };

    /* R = (1.164 * (Y - 16)) + (1.596 * (Cr - 128));
       G = (1.164 * (Y - 16)) - (0.392 * (Cb - 128)) - (0.813 * (Cr - 128));
       B = (1.164 * (Y - 16)) + (2.017 * (Cb - 128); */
    int32_t yuv2rgb_coef[5][3] = {
        {0x4A, 0x0, 0x66},
        {0x4A, 0x3E7, 0x3CC},   //4A 3E7 3CC
        {0x4A, 0x81, 0x0},      //4A 81 0
        {0x3F22, 0x85, 0x3EEB}, //3F22 85 3EEB // A0, A1, A2
        {0x0, 0x0, 0x0},        /*S0,S1,S2 */
    };

    ipu_base_addr = REGS_IPU_BASE(ipu_index);

    ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_CSC_YUV_SAT_MODE_SYNC, 0);  //SAT mode is zero
    ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_CSC_GAMUT_SAT_EN_SYNC, 0);  //GAMUT en (RGB...)

    if (csc_type == NO_CSC)
        ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_CSC_DEF_SYNC, 0);   //disable CSC
    else
        ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_CSC_DEF_SYNC, 2);   //disable CSC

    if (csc_type == RGB_YUV)
        coef = rgb2yuv_coef;
    else if (csc_type == YUV_RGB)
        coef = yuv2rgb_coef;
    else
        coef = NULL;

    if (coef) {
        writel(GET_LSB(10, coef[0][0]) | (GET_LSB(10, coef[0][1]) << 16),
               ipu_base_addr + SRM_DP_CSCA_SYNC_0__ADDR + dp * 4);
        writel(GET_LSB(10, coef[0][2]) | (GET_LSB(10, coef[1][0]) << 16),
               ipu_base_addr + SRM_DP_CSCA_SYNC_1__ADDR + dp * 4);
        writel(GET_LSB(10, coef[1][1]) | (GET_LSB(10, coef[1][2]) << 16),
               ipu_base_addr + SRM_DP_CSCA_SYNC_2__ADDR + dp * 4);
        writel(GET_LSB(10, coef[2][0]) | (GET_LSB(10, coef[2][1]) << 16),
               ipu_base_addr + SRM_DP_CSCA_SYNC_3__ADDR + dp * 4);
        writel(GET_LSB(10, coef[2][2]) | (GET_LSB(14, coef[3][0]) << 16) |
               (coef[4][0] << 30), ipu_base_addr + SRM_DP_CSC_SYNC_0__ADDR + dp * 4);
        writel(GET_LSB(14, coef[3][1]) | (coef[4][1] << 14) |
               (GET_LSB(14, coef[3][2]) << 16) | (coef[4][2] << 30),
               ipu_base_addr + SRM_DP_CSC_SYNC_1__ADDR + dp * 4);
    }

    ipu_write_field(ipu_index, IPU_IPU_SRM_PRI2__DP_S_SRM_MODE, 3);
    ipu_write_field(ipu_index, IPU_IPU_SRM_PRI2__DP_SRM_PRI, 0x0);
}

/*!
 * this function is used to config the foreground plane for combination in the DP
 * @param ipu_index ipu index
 * @param   dual_disp dual display mode
 * @param   fg_xp foreground x position
 * @param   fg_yp foreground y position
 * @param   alpha alpha value
 */
void ipu_dp_fg_config(uint32_t ipu_index, uint32_t dual_disp, uint32_t fg_xp, uint32_t fg_yp,
                      uint32_t alpha)
{
    ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_GAMMA_EN_SYNC, 0);
    ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_GAMMA_YUV_EN_SYNC, 0);

    ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_COC_SYNC, 0);
    ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_GWCKE_SYNC, 0); //color key
    ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_GWAM_SYNC, 1);  //1=global alpha,0=local alpha
    ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_GWSEL_SYNC, 0); //1=graphic is FG,0=graphic is BG

    if (dual_disp) {
        ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_FG_EN_SYNC, 1); //1=FG channel enabled,0=FG channel disabled
        ipu_write_field(ipu_index, SRM_DP_FG_POS_SYNC__DP_FGXP_SYNC, fg_xp);
        ipu_write_field(ipu_index, SRM_DP_FG_POS_SYNC__DP_FGYP_SYNC, fg_yp);
        ipu_write_field(ipu_index, SRM_DP_GRAPH_WIND_CTRL_SYNC__DP_GWAV_SYNC, alpha);   // set the FG opaque
        ipu_write_field(ipu_index, SRM_DP_GRAPH_WIND_CTRL_SYNC__DP_GWCKR_SYNC, 0xFF);
        ipu_write_field(ipu_index, SRM_DP_GRAPH_WIND_CTRL_SYNC__DP_GWCKG_SYNC, 0xFF);
        ipu_write_field(ipu_index, SRM_DP_GRAPH_WIND_CTRL_SYNC__DP_GWCKB_SYNC, 0xFF);
    } else
        ipu_write_field(ipu_index, SRM_DP_COM_CONF_SYNC__DP_FG_EN_SYNC, 0); //1=FG channel enabled,0=FG channel disabled
}
