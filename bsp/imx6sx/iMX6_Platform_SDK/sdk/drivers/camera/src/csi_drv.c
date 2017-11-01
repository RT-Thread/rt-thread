/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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
#include "sdk.h"
#include "lcdif/lcdif_common.h"
#include "registers/regscsi.h"

/*!
 * @file csi_drv.c
 * @brief common functions for sensor on mx6sl evk.
 * @ingroup diag_camera
 */

/*!
 * @brief Reset the csi controller by software mode
 */
static void csi_sw_reset(void)
{
    /* reset control registers */
    HW_CSI_CSICR1.U = 0x40000800;
    HW_CSI_CSICR2.U = 0x0;
    HW_CSI_CSICR3.U = 0x0;

    /* reset frame count */
    HW_CSI_CSICR3.B.FRMCNT_RST = 1;
    HW_CSI_CSICR1.B.CLR_RXFIFO = 1;

    hal_delay_us(10000);
}

void csi_setup(void)
{
    /* reset control registers */
    csi_sw_reset();

    /* Gated clock mode, extern VSYNC */
    HW_CSI_CSICR1.B.GCLK_MODE = 1;

    /* 8-bit data for each pixel */
    HW_CSI_CSICR1.B.PIXEL_BIT = 0;

    /* Timing control */
    /* VSYNC external generated on failing edge */
    HW_CSI_CSICR1.B.SOF_POL = 1;

    /* Pixel data latched at falling edge of CSI_PIXCLK */
    HW_CSI_CSICR1.B.REDGE = 1;

    /* HSYNC is active high */
    HW_CSI_CSICR1.B.HSYNC_POL = 1;

    /* new added */
    HW_CSI_CSICR1.B.FCC = 1;
    HW_CSI_CSICR1.B.RESERVED1 = 1;

    /* FIFO control */
    /* sensor in:       Y0 U0 Y1 V0
     * before Rx FIFO:  Y0U0Y1V0
     * in Rx FIFO:      Y1VV0Y0U0*/
    HW_CSI_CSICR1.B.PACK_DIR = 1;   //little endian: pack from LSB first
    HW_CSI_CSICR1.B.SWAP16_EN = 1;  //enable 16-bit swapping

    HW_CSI_CSICR1.B.EOF_INT_EN = 1;

    /* RX count: after the count is reached, it will generate an EOF interrupt */
    HW_CSI_CSIRXCNT_WR(640 * 480 * 2 / 4);

    /* image format */
    /* frame width * height (in pixel) */
    HW_CSI_CSIIMAG_PARA.B.IMAGE_WIDTH = VGA_FW; // ?? VGA_FW * 2 works also??
    HW_CSI_CSIIMAG_PARA.B.IMAGE_HEIGHT = VGA_FH * 2;

    /* DMA control */
    HW_CSI_CSICR3.B.RXFF_LEVEL = 0x1;   //RxFIFO full level: 8 words
    HW_CSI_CSICR3.B.STATFF_LEVEL = 0x1; //RxFIFO full level: 8 words
    HW_CSI_CSICR3.B.DMA_REQ_EN_RFF = 1; //enable dma request
}

void csi_streamon(void)
{
    /* wait for EOF and clear RxFIFO */
    HW_CSI_CSISR.B.EOF_INT = 1;
    while (HW_CSI_CSISR.B.EOF_INT == 0) ;
    HW_CSI_CSICR1.B.CLR_RXFIFO = 1;

    /* buffer address: word aligned */
    HW_CSI_CSIDMASA_FB1_WR(DDR_PXP_PS_BASE1);
    HW_CSI_CSIDMASA_FB2_WR(DDR_PXP_PS_BASE1);

    HW_CSI_CSICR3.B.DMA_REFLASH_RFF = 1;
}

void csi_streamoff(void)
{
    int timeout = 5000;

    HW_CSI_CSISR.B.EOF_INT = 1;
    while (HW_CSI_CSISR.B.EOF_INT == 0) {
        hal_delay_us(10);
        if (timeout <= 0)
            break;
        timeout--;
    }

    HW_CSI_CSICR1.B.SOF_INTEN = 0;
    HW_CSI_CSICR1.B.FB1_DMA_DONE_INTEN = 0;
    HW_CSI_CSICR1.B.FB2_DMA_DONE_INTEN = 0;

    HW_CSI_CSIDMASA_FB1_WR(0);
    HW_CSI_CSIDMASA_FB2_WR(0);

    HW_CSI_CSICR3.B.DMA_REFLASH_RFF = 1;
}
