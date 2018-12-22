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
 * @file ipu_ic.c
 * @brief display controller configuration of IPU.
 * @ingroup diag_ipu
 */
#include "ipu/ipu_common.h"

/*!
 * enable IC submodule
 *
 * @param	ipu_index:	ipu index
 * @param	ic_enable:	enable IC
 * @param	irt_enable:	enable IRT
 */
void ipu_ic_enable(int32_t ipu_index, int32_t ic_enable, int32_t irt_enable)
{
    ipu_write_field(ipu_index, IPU_IPU_CONF__IC_EN, ic_enable);
    ipu_write_field(ipu_index, IPU_IPU_CONF__IRT_EN, irt_enable);
}

void ipu_ic_rotation_config(int32_t ipu_index, int32_t taskType, int32_t rot, int32_t hf,
                            int32_t vf)
{
    switch (taskType) {
    case PP_TASK:
        ipu_write_field(ipu_index, IPU_IC_CONF__PP_EN, 0);
        ipu_write_field(ipu_index, IPU_IC_CONF__PP_ROT_EN, 0);

        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__T3_FLIP_LR, hf);
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__T3_FLIP_UD, vf);
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__T3_ROT, rot);
        break;
    case PrP_ENC_TASK:
        ipu_write_field(ipu_index, IPU_IC_CONF__PRPENC_EN, 0);
        ipu_write_field(ipu_index, IPU_IC_CONF__RWS_EN, 1);
        ipu_write_field(ipu_index, IPU_IC_CONF__CSI_MEM_WR_EN, 0);
        ipu_write_field(ipu_index, IPU_IPU_FS_PROC_FLOW1__ENC_IN_VALID, 1);

        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__T1_FLIP_LR, hf);
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__T1_FLIP_UD, vf);
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__T1_ROT, rot);
        break;
    case PrP_VF_TASK:
        ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_EN, 0);
        ipu_write_field(ipu_index, IPU_IC_CONF__RWS_EN, 1);
        ipu_write_field(ipu_index, IPU_IC_CONF__CSI_MEM_WR_EN, 0);
        ipu_write_field(ipu_index, IPU_IPU_FS_PROC_FLOW1__VF_IN_VALID, 1);

        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__T2_FLIP_LR, hf);
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__T2_FLIP_UD, vf);
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__T2_ROT, rot);
        break;
    default:
        printf("Wrong ic task type!\n");
        break;
    }
}

void ipu_ic_resize_config(int32_t ipu_index, int32_t taskType, ipu_res_info_t res_info)
{
    int32_t resCoff = 0, downsCoff = 0;

    switch (taskType) {
    case PrP_ENC_TASK:
        ipu_write_field(ipu_index, IPU_IC_CONF__PRPENC_EN, 0);
        ipu_write_field(ipu_index, IPU_IC_CONF__RWS_EN, 1);
        ipu_write_field(ipu_index, IPU_IC_CONF__CSI_MEM_WR_EN, 0);
        ipu_write_field(ipu_index, IPU_IPU_FS_PROC_FLOW1__ENC_IN_VALID, 1);

        if (res_info.width_in % 16 == 0) {
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB0_BURST_16, 1);    // set to 16bps
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB6_BURST_16, 1);
        } else {
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB0_BURST_16, 0);    // set to 8bps
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB6_BURST_16, 0);
        }

        ipu_write_field(ipu_index, IPU_IC_IDMAC_2__T1_FR_HEIGHT, res_info.height_out - 1);
        ipu_write_field(ipu_index, IPU_IC_IDMAC_3__T1_FR_WIDTH, res_info.width_out - 1);

        ipu_ic_calc_resize_coeffs(res_info.width_in, res_info.width_out, &resCoff, &downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PRP_ENC_RSC__PRPENC_DS_R_H, downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PRP_ENC_RSC__PRPENC_RS_R_H, resCoff);

        ipu_ic_calc_resize_coeffs(res_info.height_in, res_info.height_out, &resCoff, &downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PRP_ENC_RSC__PRPENC_DS_R_V, downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PRP_ENC_RSC__PRPENC_RS_R_V, resCoff);
        break;
    case PrP_VF_TASK:
        ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_EN, 0);
        ipu_write_field(ipu_index, IPU_IC_CONF__RWS_EN, 1);
        ipu_write_field(ipu_index, IPU_IC_CONF__CSI_MEM_WR_EN, 0);
        ipu_write_field(ipu_index, IPU_IPU_FS_PROC_FLOW1__VF_IN_VALID, 1);

        if (res_info.width_in % 16 == 0) {
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB1_BURST_16, 1);    // set to 16bps
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB6_BURST_16, 1);
        } else {
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB1_BURST_16, 0);    // set to 8bps
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB6_BURST_16, 0);
        }
        ipu_write_field(ipu_index, IPU_IC_IDMAC_2__T2_FR_HEIGHT, res_info.height_out - 1);
        ipu_write_field(ipu_index, IPU_IC_IDMAC_3__T2_FR_WIDTH, res_info.width_out - 1);

        ipu_ic_calc_resize_coeffs(res_info.width_in, res_info.width_out, &resCoff, &downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PRP_VF_RSC__PRPVF_DS_R_H, downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PRP_VF_RSC__PRPVF_RS_R_H, resCoff);

        ipu_ic_calc_resize_coeffs(res_info.height_in, res_info.height_out, &resCoff, &downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PRP_VF_RSC__PRPVF_DS_R_V, downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PRP_VF_RSC__PRPVF_RS_R_V, resCoff);
        break;
    case PP_TASK:
        ipu_write_field(ipu_index, IPU_IC_CONF__PP_EN, 0);
        ipu_write_field(ipu_index, IPU_IC_CONF__PP_CSC1, 0);
        ipu_write_field(ipu_index, IPU_IC_CONF__PP_CSC2, 0);
        ipu_write_field(ipu_index, IPU_IC_CONF__PP_CMB, 0);

        if (res_info.width_in % 16 == 0) {
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB2_BURST_16, 1);    // set to 16bps
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB5_BURST_16, 1);
        } else {
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB2_BURST_16, 0);    // set to 8bps
            ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB5_BURST_16, 0);
        }

        ipu_write_field(ipu_index, IPU_IC_IDMAC_2__T3_FR_HEIGHT, res_info.height_out - 1);
        ipu_write_field(ipu_index, IPU_IC_IDMAC_3__T3_FR_WIDTH, res_info.width_out - 1);

        ipu_ic_calc_resize_coeffs(res_info.width_in, res_info.width_out, &resCoff, &downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PP_RSC__PP_DS_R_H, downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PP_RSC__PP_RS_R_H, resCoff);

        ipu_ic_calc_resize_coeffs(res_info.height_in, res_info.height_out, &resCoff, &downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PP_RSC__PP_DS_R_V, downsCoff);
        ipu_write_field(ipu_index, IPU_IC_PP_RSC__PP_RS_R_V, resCoff);  // FROM (1536/2 -1)->479 *8192 = 13117
        break;
    default:
        printf("Wrong ic task type!\n");
        break;
    }
}

void ipu_ic_deinterlace_config(int32_t ipu_index, ipu_vdi_info_t vdi_info)
{
    int32_t resCoff = 0, downsCoff = 0;

    ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_EN, 0);
    ipu_write_field(ipu_index, IPU_IC_CONF__RWS_EN, 1);
    ipu_write_field(ipu_index, IPU_IC_CONF__CSI_MEM_WR_EN, 0);
    ipu_write_field(ipu_index, IPU_IPU_FS_PROC_FLOW1__VF_IN_VALID, 1);

    if (vdi_info.width_in % 16 == 0) {
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB1_BURST_16, 1);    // set to 16bps
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB6_BURST_16, 1);
    } else {
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB1_BURST_16, 0);    // set to 8bps
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB6_BURST_16, 0);
    }
    ipu_write_field(ipu_index, IPU_IC_IDMAC_2__T2_FR_HEIGHT, vdi_info.height_out - 1);
    ipu_write_field(ipu_index, IPU_IC_IDMAC_3__T2_FR_WIDTH, vdi_info.width_out - 1);

    ipu_ic_calc_resize_coeffs(vdi_info.width_in, vdi_info.width_out, &resCoff, &downsCoff);
    ipu_write_field(ipu_index, IPU_IC_PRP_VF_RSC__PRPVF_DS_R_H, downsCoff);
    ipu_write_field(ipu_index, IPU_IC_PRP_VF_RSC__PRPVF_RS_R_H, resCoff);

    ipu_ic_calc_resize_coeffs(vdi_info.height_in, vdi_info.height_out, &resCoff, &downsCoff);
    ipu_write_field(ipu_index, IPU_IC_PRP_VF_RSC__PRPVF_DS_R_V, downsCoff);
    ipu_write_field(ipu_index, IPU_IC_PRP_VF_RSC__PRPVF_RS_R_V, resCoff);
}

/*
* this function is used to calculate the params for resizing
*/
int32_t ipu_ic_calc_resize_coeffs(int32_t in_size, int32_t out_size, int32_t * resize_coeff,
                                  int32_t * downsize_coeff)
{
    int32_t tempSize;
    int32_t tempDownsize;

    /* Cannot downsize more than 8:1 */
    if ((out_size << 3) < in_size)
        return -1;

    /* compute downsizing coefficient */
    tempDownsize = 0;
    tempSize = in_size;

    while (((tempSize >= out_size * 2) || (tempSize > 1024))
           && (tempDownsize < 2)) {
        tempSize >>= 1;
        tempDownsize++;
    }

    *downsize_coeff = tempDownsize;

    /* compute resizing coefficient using the following equation:
       resizeCoeff = M*(SI -1)/(SO - 1)
       where M = 2^13, SI - input size, SO - output size    */
    *resize_coeff = (8192L * (tempSize - 1)) / (out_size - 1);

    if (*resize_coeff >= 16384L) {
        printf("Overflow on resize coeff %d.\n", *resize_coeff);
        *resize_coeff = 0x3FFF;
    }

    return 0;
}

/*
* this function is used to set the resizing parameters
*/
int32_t ipu_ic_config_resize_rate(int32_t ipu_index, char *task_type, uint32_t res_vert,
                                  uint32_t down_vert, uint32_t res_horiz, uint32_t down_horiz)
{
    uint32_t val;
    uint32_t ipu_base_addr = REGS_IPU_BASE(ipu_index);

    val = (down_vert << 30) | (res_vert << 16) | (down_horiz << 14) | (res_horiz);

    if (!strcmp(task_type, "PPTASK")) {
        writel(val, ipu_base_addr + IPU_IC_PP_RSC__ADDR);
    } else if (!strcmp(task_type, "VFTASK")) {
        writel(val, ipu_base_addr + IPU_IC_PRP_VF_RSC__ADDR);
    } else if (!strcmp(task_type, "PrPTASK")) {
        writel(val, ipu_base_addr + IPU_IC_PRP_ENC_RSC__ADDR);
    } else {
        printf("Task type is not defined!\n");
        return -1;
    }

    return 0;
}

/*
* this function is used to config the combination task in the IC
* local alpha with per-pixel or from separate buffer can be used
* global alpha can be used also.
*/
int32_t ipu_ic_combine_config(int32_t ipu_index, ic_comb_params_t comb_params)
{
    switch (comb_params.taskType) {
    case PrP_VF_TASK:
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB3_BURST_16, 1);    // set to 16bps

        if (comb_params.alpha > 0 && comb_params.alpha < 0x100) {
            ipu_write_field(ipu_index, IPU_IC_CONF__IC_GLB_LOC_A, 1);   // global alpha enabled
            ipu_write_field(ipu_index, IPU_IC_CMBP_1__IC_PRPVF_ALPHA_V, comb_params.alpha); // global alpha value
        } else {
            ipu_write_field(ipu_index, IPU_IC_CONF__IC_GLB_LOC_A, 0);   // local alpha from separate buffer
        }

        ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_CMB, (comb_params.alpha == 0) ? 0 : 1);
        ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_EN, 1);
        break;
    case PP_TASK:
        ipu_write_field(ipu_index, IPU_IC_IDMAC_1__CB4_BURST_16, 1);    // set to 16bps

        if (comb_params.alpha > 0 && comb_params.alpha < 0x100) {
            ipu_write_field(ipu_index, IPU_IC_CONF__IC_GLB_LOC_A, 1);   // global alpha enabled
            ipu_write_field(ipu_index, IPU_IC_CMBP_1__IC_PP_ALPHA_V, comb_params.alpha);    // global alpha
        } else {
            ipu_write_field(ipu_index, IPU_IC_CONF__IC_GLB_LOC_A, 0);   // local alpha in sepatate buffer
        }

        ipu_write_field(ipu_index, IPU_IC_CONF__PP_CMB, (comb_params.alpha == 0) ? 0 : 1);
        ipu_write_field(ipu_index, IPU_IC_CONF__PP_EN, 1);
        break;
    default:
        printf("Task Type is wrong!!\n");
        return -1;
    }

    return 0;
}

/*
* this function is used to config the color space conversion task in the IC
*/
int32_t ipu_ic_csc_config(int32_t ipu_index, int32_t csc_set_index, ic_csc_params_t csc_params)
{
    unsigned int param;
    unsigned int ipu_base_addr = REGS_IPU_BASE(ipu_index);

    unsigned int tpmBaseAddr = ipu_base_addr + TPM_BASE_OFFSET;
    unsigned int *base = NULL;

    if (csc_set_index != 1 && csc_set_index != 2) {
        printf("Wrong index input for IC CSC!!\n");
        return -1;
    }

    /*Y = R *  .299 + G *  .587 + B *  .114;
       U = R * -.169 + G * -.332 + B *  .500 + 128.;
       V = R *  .500 + G * -.419 + B * -.0813 + 128.; */
    unsigned int rgb2ycbcr_coeff[4][3] = {
        {0x004D, 0x0096, 0x001D},
        {0x01D5, 0x01AB, 0x0080},
        {0x0080, 0x0195, 0x01EB},
        {0x0000, 0x0200, 0x0200},   /* A0, A1, A2 */
    };

    /* transparent RGB->RGB matrix for combining
     */
    unsigned int rgb2rgb_coeff[4][3] = {
        {0x0080, 0x0000, 0x0000},
        {0x0000, 0x0080, 0x0000},
        {0x0000, 0x0000, 0x0080},
        {0x0000, 0x0000, 0x0000},   /* A0, A1, A2 */
    };

    /*
       R = (1.164 * (Y - 16)) + (1.596 * (Cr - 128));
       G = (1.164 * (Y - 16)) - (0.392 * (Cb - 128)) - (0.813 * (Cr - 128));
       B = (1.164 * (Y - 16)) + (2.017 * (Cb - 128);
     */
    unsigned int ycbcr2rgb_coeff[4][3] = {
        {0x95, 0x0, 0xCC},
        {0x95, 0x1CE, 0x198},
        {0x95, 0xFF, 0x0},
        {0x1E42, 0x10A, 0x1DD6},    // A0, A1, A2
    };

    /*
       R = (1.164 * alpha *  (Y - 16)) + (1.596 * (Cr - 128));
       G = (1.164 * alpha * (Y - 16)) - (0.392 * (Cb - 128)) - (0.813 * (Cr - 128));
       B = (1.164 * alpha * (Y - 16)) + (2.017 * (Cb - 128);
     */
    if (csc_set_index == 1) {
        if (csc_params.taskType == PrP_ENC_TASK) {
            base = (void *)(tpmBaseAddr + 0x2008);
        } else if (csc_params.taskType == PrP_VF_TASK) {
            base = (void *)(tpmBaseAddr + 0x4028);
        } else if (csc_params.taskType == PP_TASK) {
            base = (void *)(tpmBaseAddr + 0x6060);
        } else {
            printf("Wrong task type for IC CSC1 input!!\n");
            return -1;
        }
    } else {
        if (csc_params.taskType == PrP_VF_TASK) {
            base = (void *)(tpmBaseAddr + 0x4040);
        } else if (csc_params.taskType == PP_TASK) {
            base = (void *)(tpmBaseAddr + 0x6078);
        } else {
            printf("Wrong task type for IC CSC2 input!!\n");
            return -1;
        }
    }

    if ((csc_params.inFormat == YUV) && (csc_params.outFormat == RGB)) {
        /* Init CSC (YCbCr->RGB) */
        param = (ycbcr2rgb_coeff[3][0] << 27) |
            (ycbcr2rgb_coeff[0][0] << 18) | (ycbcr2rgb_coeff[1][1] << 9) | ycbcr2rgb_coeff[2][2];
        writel(param, base++);
        /* scale = 2, sat = 0 */
        param = (ycbcr2rgb_coeff[3][0] >> 5) | (2 << (40 - 32));
        writel(param, base++);

        param = (ycbcr2rgb_coeff[3][1] << 27) |
            (ycbcr2rgb_coeff[0][1] << 18) | (ycbcr2rgb_coeff[1][0] << 9) | ycbcr2rgb_coeff[2][0];
        writel(param, base++);
        param = (ycbcr2rgb_coeff[3][1] >> 5);
        writel(param, base++);

        param = (ycbcr2rgb_coeff[3][2] << 27) |
            (ycbcr2rgb_coeff[0][2] << 18) | (ycbcr2rgb_coeff[1][2] << 9) | ycbcr2rgb_coeff[2][1];
        writel(param, base++);
        param = (ycbcr2rgb_coeff[3][2] >> 5);
        writel(param, base++);
    } else if ((csc_params.inFormat == RGB) && (csc_params.outFormat == YUV)) {
        /* Init CSC1 (RGB->YCbCr) */
        param = (rgb2ycbcr_coeff[3][0] << 27) |
            (rgb2ycbcr_coeff[0][0] << 18) | (rgb2ycbcr_coeff[1][1] << 9) | rgb2ycbcr_coeff[2][2];
        writel(param, base++);
        /* scale = 1, sat = 0 */
        param = (rgb2ycbcr_coeff[3][0] >> 5) | (1UL << 8);
        writel(param, base++);

        param = (rgb2ycbcr_coeff[3][1] << 27) |
            (rgb2ycbcr_coeff[0][1] << 18) | (rgb2ycbcr_coeff[1][0] << 9) | rgb2ycbcr_coeff[2][0];
        writel(param, base++);
        param = (rgb2ycbcr_coeff[3][1] >> 5);
        writel(param, base++);

        param = (rgb2ycbcr_coeff[3][2] << 27) |
            (rgb2ycbcr_coeff[0][2] << 18) | (rgb2ycbcr_coeff[1][2] << 9) | rgb2ycbcr_coeff[2][1];
        writel(param, base++);
        param = (rgb2ycbcr_coeff[3][2] >> 5);
        writel(param, base++);
    } else if (((csc_params.inFormat == RGB) && (csc_params.outFormat == RGB))
               || ((csc_params.inFormat == YUV) && (csc_params.outFormat == YUV))) {
        /* Init CSC1 */
        param =
            (rgb2rgb_coeff[3][0] << 27) | (rgb2rgb_coeff[0][0] << 18) |
            (rgb2rgb_coeff[1][1] << 9) | rgb2rgb_coeff[2][2];
        writel(param, base++);
        /* scale = 2, sat = 0 */
        param = (rgb2rgb_coeff[3][0] >> 5) | (2UL << 8);
        writel(param, base++);

        param =
            (rgb2rgb_coeff[3][1] << 27) | (rgb2rgb_coeff[0][1] << 18) |
            (rgb2rgb_coeff[1][0] << 9) | rgb2rgb_coeff[2][0];
        writel(param, base++);
        param = (rgb2rgb_coeff[3][1] >> 5);
        writel(param, base++);

        param =
            (rgb2rgb_coeff[3][2] << 27) | (rgb2rgb_coeff[0][2] << 18) |
            (rgb2rgb_coeff[1][2] << 9) | rgb2rgb_coeff[2][1];
        writel(param, base++);
        param = (rgb2rgb_coeff[3][2] >> 5);
        writel(param, base++);
    } else {
        printf("Unkown color space conversion!!\n");
        return -1;
    }

    if (csc_set_index == 1) {
        if (csc_params.taskType == PrP_ENC_TASK) {
            ipu_write_field(ipu_index, IPU_IC_CONF__PRPENC_CSC1, 1);
        } else if (csc_params.taskType == PrP_VF_TASK) {
            ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_CSC1, 1);
        } else if (csc_params.taskType == PP_TASK) {
            ipu_write_field(ipu_index, IPU_IC_CONF__PP_CSC1, 1);
        } else {
            printf("Wrong Task input!!\n");
            return -1;
        }
    } else {
        if (csc_params.taskType == PrP_VF_TASK) {
            ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_CSC2, 1);
        } else if (csc_params.taskType == PP_TASK) {
            ipu_write_field(ipu_index, IPU_IC_CONF__PP_CSC2, 1);
        } else {
            printf("Wrong Task input!!\n");
            return -1;
        }
    }

    return 0;
}

/*
* enable ipu tasks, such as preprocessing/post-processing task
*/
int32_t ipu_ic_task_enable(int32_t ipu_index, int32_t task_type, int32_t task, int32_t enable)
{
    switch (task_type) {
    case PrP_ENC_TASK:

        if (task == IC_CSC1)
            ipu_write_field(ipu_index, IPU_IC_CONF__PRPENC_CSC1, enable);
        else if (IC_PRPENC)
            ipu_write_field(ipu_index, IPU_IC_CONF__PRPENC_EN, enable);
        else
            printf("Task Type is wrong!!\n");

        break;
    case PrP_VF_TASK:

        if (task == IC_CMB)
            ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_CMB, enable);
        else if (task == IC_CSC1)
            ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_CSC1, enable);
        else if (task == IC_CSC2)
            ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_CSC2, enable);
        else if (task == IC_PRPVF)
            ipu_write_field(ipu_index, IPU_IC_CONF__PRPVF_EN, enable);
        else
            printf("Task Type is wrong!!\n");

        break;
    case PP_TASK:

        if (task == IC_CMB)
            ipu_write_field(ipu_index, IPU_IC_CONF__PP_CMB, enable);
        else if (task == IC_CSC1)
            ipu_write_field(ipu_index, IPU_IC_CONF__PP_CSC1, enable);
        else if (task == IC_CSC2)
            ipu_write_field(ipu_index, IPU_IC_CONF__PP_CSC2, enable);
        else if (task == IC_PP)
            ipu_write_field(ipu_index, IPU_IC_CONF__PP_EN, enable);
        else if (task == IC_ROT)
            ipu_write_field(ipu_index, IPU_IC_CONF__PP_ROT_EN, enable);
        else
            printf("Task Type is wrong!!\n");

        break;
    default:
        printf("Task Type is wrong!!\n");
        return -1;
    }

    return 0;
}
