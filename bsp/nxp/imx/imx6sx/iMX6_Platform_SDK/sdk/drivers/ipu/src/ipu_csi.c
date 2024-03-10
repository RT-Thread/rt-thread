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
 * @file ipu_csi.c
 * @brief camera interface configuration of IPU.
 * @ingroup diag_ipu
 */

#include <string.h>
#include "ipu/ipu_common.h"

/*
 * set the CSI module to handle data from camera
 * @param width frame width of camera input
 * @param height frame height of camera input
 */
void ipu_csi_config(uint32_t ipu_index, uint32_t csi_interface, uint32_t raw_width,
                    uint32_t raw_height, uint32_t act_width, uint32_t act_height)
{
    int hsync_pol = 0, vsync_pol = 0, clock_mode, data_fmt;
    int hsc = 0, vsc = 0;

    if (csi_interface == CSI_PARALLEL) {
        clock_mode = CSI_CLK_MODE_GATED_CLK;
        data_fmt = CSI_YUYV;
    } else if (csi_interface == CSI_MIPI) {
        clock_mode = CSI_CLK_MODE_NONGATED_CLK;
        data_fmt = CSI_UYVY;
    } else if (csi_interface == CSI_BT656_NTSC_INTERLACED) {
        hsync_pol = 1;
        vsync_pol = 0;
        hsc = 0;
        vsc = 0xD;
        clock_mode = CSI_CLK_MODE_BT656_INTERLACED;
        data_fmt = CSI_UYVY;
    } else if (csi_interface == CSI_BT656_PAL_INTERLACED) {
        hsync_pol = 1;
        vsync_pol = 0;
        hsc = 0;
        vsc = 0x0;
        clock_mode = CSI_CLK_MODE_BT656_INTERLACED;
        data_fmt = CSI_UYVY;
    } else if (csi_interface == CSI_BT656_NTSC_PROGRESSIVE
               || csi_interface == CSI_BT656_PAL_PROGRESSIVE) {
        hsync_pol = 1;
        vsync_pol = 0;
        hsc = 0;
        vsc = 0x0;
        clock_mode = CSI_CLK_MODE_BT656_PROGRESSIVE;
        data_fmt = CSI_UYVY;
    } else if (csi_interface == CSI_TEST_MODE) {
        data_fmt = CSI_YUV444;
        clock_mode = CSI_CLK_MODE_NONGATED_CLK;
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_TEST_GEN_MODE, 1);
    } else {
        printf("Unsupport CSI interface\n");
    }

    /* setting CSI data source, default is from parallel interface */
    if (csi_interface == CSI_MIPI) {
        ipu_write_field(ipu_index, IPU_IPU_CONF__CSI0_DATA_SOURCE, 1);  //csi0 data souce is mipi
        switch (data_fmt) {
        case CSI_UYVY:
            ipu_write_field(ipu_index, IPU_CSI0_DI__CSI0_MIPI_DI0, 0x1E);   //(UYVY)MIPI_YUV422 8bit
            break;
        case CSI_RGB565:
            ipu_write_field(ipu_index, IPU_CSI0_DI__CSI0_MIPI_DI0, 0x22);   //MIPI_RGB565
            break;
        case CSI_RGB555:
            ipu_write_field(ipu_index, IPU_CSI0_DI__CSI0_MIPI_DI0, 0x21);   //MIPI_RGB555
            break;
        case CSI_RGB444:
            ipu_write_field(ipu_index, IPU_CSI0_DI__CSI0_MIPI_DI0, 0x20);   //MIPI_RGB565
            break;
        default:
            printf("\nThispixel format is not supported by MIPI_CSI2!\n");
            return;
        }
        /*using CSI0_MIPI_DI0 by default, DI1~3 unused */
        ipu_write_field(ipu_index, IPU_CSI0_DI__CSI0_MIPI_DI1, 0);
        ipu_write_field(ipu_index, IPU_CSI0_DI__CSI0_MIPI_DI2, 0);
        ipu_write_field(ipu_index, IPU_CSI0_DI__CSI0_MIPI_DI3, 0);
    } else {
        /* set parallel interface information */
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_DATA_EN_POL, 0);
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_EXT_VSYNC, 1);
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_SENS_PIX_CLK_POL, 0);   // pos edge
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_DATA_POL, 0);
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_HSYNC_POL, hsync_pol);
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_VSYNC_POL, vsync_pol);
    }

    /* setup destination */
    if (csi_vdi_direct_path == 1)
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_DATA_DEST, 2);  //destination is VDI
    else
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_DATA_DEST, 4);  //destination is IDMAC

    ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_SENS_PRTCL, clock_mode);    // Gated clock mode
    if(csi_interface == CSI_TEST_MODE)
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_DIV_RATIO, 0x9F);  //division ratio of HSP_CLK into SENSOR_MCLK to slow down the frame rate in test mode
    else
        ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_DIV_RATIO, 0);  
    ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_DATA_WIDTH, 1); //8bits per color
    ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_PACK_TIGHT, 0); //only when data format is RGB/YUV, and data_width > 8
    ipu_write_field(ipu_index, IPU_CSI0_SENS_CONF__CSI0_SENS_DATA_FORMAT, data_fmt);    // YUV422

    /*CSI0 common sensor configuration for PApa */
    /*set sensor frame size */
    ipu_write_field(ipu_index, IPU_CSI0_SENS_FRM_SIZE__CSI0_SENS_FRM_HEIGHT, raw_height - 1);
    ipu_write_field(ipu_index, IPU_CSI0_SENS_FRM_SIZE__CSI0_SENS_FRM_WIDTH, raw_width - 1);

    /*CSI_ACT_FRM_SIZE */
    ipu_write_field(ipu_index, IPU_CSI0_ACT_FRM_SIZE__CSI0_ACT_FRM_HEIGHT, act_height - 1);
    ipu_write_field(ipu_index, IPU_CSI0_ACT_FRM_SIZE__CSI0_ACT_FRM_WIDTH, act_width - 1);

    /*CSI_OUT_FRM_CTRL */
    ipu_write_field(ipu_index, IPU_CSI0_OUT_FRM_CTRL__CSI0_HORZ_DWNS, 0);
    ipu_write_field(ipu_index, IPU_CSI0_OUT_FRM_CTRL__CSI0_VERT_DWNS, 0);
    ipu_write_field(ipu_index, IPU_CSI0_OUT_FRM_CTRL__CSI0_HSC, hsc);
    ipu_write_field(ipu_index, IPU_CSI0_OUT_FRM_CTRL__CSI0_VSC, vsc);

    ipu_write_field(ipu_index, IPU_IPU_CONF__CSI_SEL, 0);
    ipu_write_field(ipu_index, IPU_IPU_CONF__CSI0_EN, 1);

    if (clock_mode == CSI_CLK_MODE_BT656_PROGRESSIVE) {
        ipu_write_field(ipu_index, IPU_CSI0_CCIR_CODE_1__FULL, 0x40030);
        ipu_write_field(ipu_index, IPU_CSI0_CCIR_CODE_3__FULL, 0xFF0000);
    } else if (clock_mode == CSI_CLK_MODE_BT656_INTERLACED) {
        /*
         * Field0BlankEnd = 0x6 (FVH 0x3), Field0BlankStart = 0x2 (FVH 0x2),
         * Field0ActiveEnd = 0x4 (FVH 0x1), Field0ActiveStart = 0 (FVH 0x0)
         */
        ipu_write_field(ipu_index, IPU_CSI0_CCIR_CODE_1__FULL, 0xD07DF);
        /*
         * Field0BlankEnd = 0x7 (FVH 0x7), Field0BlankStart = 0x3 (FVH 0x6),
         * Field0ActiveEnd = 0x5 (FVH 0x5), Field0ActiveStart = 0x1 (FVH 0x4)
         */
        ipu_write_field(ipu_index, IPU_CSI0_CCIR_CODE_2__FULL, 0x40596);
        ipu_write_field(ipu_index, IPU_CSI0_CCIR_CODE_3__FULL, 0xFF0000);
        ipu_write_field(ipu_index, IPU_CSI0_CCIR_CODE_1__CSI0_CCIR_ERR_DET_EN, 1);
    }
}

/*!
 * set the SMFC(fifo for camera input) property
 *
 * @param	ipu_index: ipu index
 * @param 	channel: select the channel number out of 0~3
 * @param 	map: choose the map between channel and fifo
 * @param 	burst_size: set the burst size of fifo input.
 *
 * @return -1 means channel not found, 0 means configuration is ok.
 */
uint32_t ipu_smfc_fifo_allocate(uint32_t ipu_index, uint32_t channel, uint32_t map,
                                uint32_t burst_size)
{
    switch (channel) {
    case 0:
        ipu_write_field(ipu_index, IPU_SMFC_MAP__MAP_CH0, map);
        ipu_write_field(ipu_index, IPU_SMFC_BS__BURST0_SIZE, burst_size);
        break;

    case 1:
        ipu_write_field(ipu_index, IPU_SMFC_MAP__MAP_CH1, map);
        ipu_write_field(ipu_index, IPU_SMFC_BS__BURST1_SIZE, burst_size);
        break;

    case 2:
        ipu_write_field(ipu_index, IPU_SMFC_MAP__MAP_CH2, map);
        ipu_write_field(ipu_index, IPU_SMFC_BS__BURST2_SIZE, burst_size);
        break;

    case 3:
        ipu_write_field(ipu_index, IPU_SMFC_MAP__MAP_CH3, map);
        ipu_write_field(ipu_index, IPU_SMFC_BS__BURST3_SIZE, burst_size);
        break;

    default:
        printf("Wrong channel selected!!\n");
        return -1;
    }

    ipu_write_field(ipu_index, IPU_IPU_CONF__SMFC_EN, 1);
    return 0;
}

/*!
 * link CSI channel smfc with display 
 *
 * @param	ipu_index: ipu index
 * @param 	smfc: select the smfc number out of 0/2
 *
 * @return -1 means channel not found, 0 means configuration is ok.
 */
void ipu_capture_disp_link(uint32_t ipu_index, uint32_t smfc)
{
    if (csi_vdi_direct_path == 0) {
        switch (smfc) {
        case 0:
            ipu_write_field(ipu_index, IPU_IPU_FS_PROC_FLOW3__SMFC0_DEST_SEL, 0x9); // smfc0 -> chan23
            ipu_write_field(ipu_index, IPU_IPU_FS_DISP_FLOW1__DP_SYNC0_SRC_SEL, 0x1);   // MG source from capture 0
            break;
        case 2:
            ipu_write_field(ipu_index, IPU_IPU_FS_PROC_FLOW3__SMFC2_DEST_SEL, 0x9); // smfc2 -> chan23
            ipu_write_field(ipu_index, IPU_IPU_FS_DISP_FLOW1__DP_SYNC0_SRC_SEL, 0x2);   // MG source from capture 2
            break;
        default:
            printf("Wrong smfc selected!!\n");
            break;
        }
    } else {
        ipu_write_field(ipu_index, IPU_IPU_FS_PROC_FLOW1__VDI_SRC_SEL, 0x01);   // csi
        ipu_write_field(ipu_index, IPU_IPU_FS_PROC_FLOW2__PRPVF_DEST_SEL, 0x09);    // DP sync0     
        ipu_write_field(ipu_index, IPU_IPU_FS_DISP_FLOW1__DP_SYNC0_SRC_SEL, 0x04);  // VF
    }
}

/*!
 * @brief Disable csi module
 *
 * @param	csi csi id
 *
 */
void ipu_disable_csi(uint32_t ipu_index, uint32_t csi)
{
    if (csi == 0) {
        ipu_write_field(ipu_index, IPU_IPU_CONF__CSI0_EN, 0);
    } else if (csi == 1) {
        ipu_write_field(ipu_index, IPU_IPU_CONF__CSI1_EN, 0);
    }
}

/*!
 * @brief Disable smfc module
 *
 */
void ipu_disable_smfc(uint32_t ipu_index)
{
    ipu_write_field(ipu_index, IPU_IPU_CONF__SMFC_EN, 0);
}

/*!
 * @brief Set the color of csi test mode
 *
 *
 * @param	ipu_index	ipu id
 * @param	color_mode 	the number of color to show on chessboard
 *
 */
void ipu_csi_test_mode_color(uint32_t ipu_index, int32_t color_mode)
{
    if (color_mode == 0) {
        /* red chessboard */
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_R_VALUE, 0xFF);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_G_VALUE, 0);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_B_VALUE, 0);
    } else if (color_mode == 1) {
        /* green chessboard */
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_R_VALUE, 0);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_G_VALUE, 0xFF);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_B_VALUE, 0);
    } else if (color_mode == 2) {
        /* blue chessboard */
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_R_VALUE, 0);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_G_VALUE, 0);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_B_VALUE, 0xFF);
    } else if (color_mode == 3) {
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_R_VALUE, 0xFF);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_G_VALUE, 0xFF);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_B_VALUE, 0x0);
    } else if (color_mode == 4) {
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_R_VALUE, 0);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_G_VALUE, 0xFF);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_B_VALUE, 0xFF);
    } else if (color_mode == 5) {
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_R_VALUE, 0xFF);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_G_VALUE, 0);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_B_VALUE, 0xFF);
    } else if (color_mode == 6) {
        /* white chessboard */
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_R_VALUE, 0xFF);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_G_VALUE, 0xFF);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_B_VALUE, 0xFF);
    } else if (color_mode == 7) {
        /* black chessboard */
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_R_VALUE, 0);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_G_VALUE, 0);
        ipu_write_field(ipu_index, IPU_CSI0_TST_CTRL__CSI0_PG_B_VALUE, 0);
    } else {
        printf("\nwrong color mode for csi test mode, invalid number is 0~6\n");
    }
}
