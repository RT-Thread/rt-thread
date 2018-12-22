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
#include "registers/regspxp.h"
#include "registers/regsccm.h"

/*!
 * @file pxp_drv.c
 * @brief Main driver for the PXP controller. It initializes the controller
 * and provide color space convertion functionality.
 *
 * @ingroup diag_lcdif
 */

/*!
 * @brief Reset the PXP controller by software mode
 */
static int pxp_sw_reset(void)
{
    /* clear register */
    BW_PXP_CTRL_SFTRST(1);
    hal_delay_us(1000);

    BW_PXP_CTRL_CLKGATE(0);
    BW_PXP_CTRL_SFTRST(0);

    return 0;
}

/*!
 * @brief Wait for PXP controller IRQ interrupt inside timeout time.
 */
static void pxp_proc_timeout(int time)
{
    while (HW_PXP_STAT.B.IRQ == 0) {
        time--;
        if (time == 0)
            break;
    };
    HW_PXP_STAT.B.IRQ = 0;
}

/*!
 * @brief Enable pxp axi clock.
 */
static void pxp_clock_enable(void)
{
    /* always on MX6SL */
    HW_CCM_CCGR3.B.CG1 = 0x3;
}

/*!
 * @brief Diable PXP after completing the single operation.
 */
void pxp_disable(void)
{
    /* The ENABLE bit will be cleared once the current operation completes 
     * If the Repeat mode is open, disable it. */
    if (HW_PXP_CTRL.B.EN_REPEAT)
        HW_PXP_CTRL.B.EN_REPEAT = 0;
}

void pxp_csc_process(void)
{
    pxp_clock_enable();
    pxp_sw_reset();

    /* Input and output buffer address */
    HW_PXP_PS_BUF_WR(DDR_PXP_PS_BASE1);
    HW_PXP_OUT_BUF_WR(DDR_LCD_BASE1);

    /* Input and output pitch
     * bytes between two vertically adj pixels */
    HW_PXP_PS_PITCH.B.PITCH = VGA_FW * 2;
    HW_PXP_OUT_PITCH.B.PITCH = FRAME_WIDTH * 2;

    /* set output frame */
    /* output frame size */
    HW_PXP_OUT_LRC.B.X = FRAME_WIDTH - 1;
    HW_PXP_OUT_LRC.B.Y = FRAME_HEIGHT - 1;

    /* left upper corner (0, 0) */
    HW_PXP_OUT_PS_ULC.B.X = 0;
    HW_PXP_OUT_PS_ULC.B.Y = 0;

    /* low right corner (input_width-1, input_height-1) */
    HW_PXP_OUT_PS_LRC.B.X = VGA_FW - 1;
    HW_PXP_OUT_PS_LRC.B.Y = VGA_FH - 1;

    /* set backgroud as white */
    HW_PXP_PS_BACKGROUND.B.COLOR = 0xFFFFFF;

    /* 1:1 scale */
    HW_PXP_PS_SCALE.B.XSCALE = 1 << 12;
    HW_PXP_PS_SCALE.B.YSCALE = 1 << 12;

    /* Input format U0Y0V0Y1 */
    HW_PXP_PS_CTRL.B.FORMAT = 0x12;

    /* Output format: RGB565 */
    HW_PXP_OUT_CTRL.B.FORMAT = 0xE;

    /* YCbCr->RGB coefficients */
    HW_PXP_CSC1_COEF0_WR(0x84AB01F0);
    HW_PXP_CSC1_COEF1_WR(0x01980204);
    HW_PXP_CSC1_COEF2_WR(0x0730079C);

    /* PXP run continuously */
    HW_PXP_CTRL.B.EN_REPEAT = 1;
    HW_PXP_CTRL.B.ENABLE = 1;
}
