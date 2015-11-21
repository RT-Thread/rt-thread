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
 * @file lcdif_drv.c
 * @brief Main driver for the LCDIF controller. It initializes the controller
 * and handle display mode.
 *
 * @ingroup diag_lcdif
 */

#include "sdk.h"
#include "logo.h"
#include "lcdif/lcdif_common.h"
#include "registers/regselcdif.h"

void lcdif_csc_config(int enable)
{
    if (enable) {
        /*CSC control, from RGB to YUV */
		HW_LCDIF_CSC_COEFF0.U = 0x00410002;
		HW_LCDIF_CSC_COEFF1.U = 0x00190081;
		HW_LCDIF_CSC_COEFF2.U = 0x03B603DB;
		HW_LCDIF_CSC_COEFF3.U = 0x00700070;
		HW_LCDIF_CSC_COEFF4.U = 0x03EE03A2;
		HW_LCDIF_CSC_OFFSET.U = 0x00800010;
		HW_LCDIF_CSC_LIMIT.U = 0x10F010EB;
	}

	BW_LCDIF_CTRL_RGB_TO_YCBCR422_CSC(enable);
}

/*!
 * @brief Reset the LCD controller by software mode
 */
static int lcdif_sw_reset(void)
{
	// software reset the LCDIF controller
	BW_LCDIF_CTRL_CLKGATE(0);
	BW_LCDIF_CTRL_SFTRST(1);
    hal_delay_us(100);

	BW_LCDIF_CTRL_SFTRST(0);
	BW_LCDIF_CTRL_CLKGATE(0);

    return 0;
}

/*!
 * @brief Set the LCD controller waveforms to driven the panel
 *
 * @param   sync_waveform	lcd waveform setting, including hsync/vsync/drdy and blanking parameters
 */
static int lcdif_waveform_setting(lcdif_sync_waveform_t *sync_waveform)
{
	/* frame size setting: 800 * 480 */
	HW_LCDIF_TRANSFER_COUNT.B.H_COUNT = sync_waveform->frameWidth;
	HW_LCDIF_TRANSFER_COUNT.B.V_COUNT = sync_waveform->frameHeight;

	/* timing setting */
	HW_LCDIF_TIMING.B.DATA_SETUP = 0x01;
	HW_LCDIF_TIMING.B.DATA_HOLD = 0x01;
	HW_LCDIF_TIMING.B.CMD_SETUP = 0x01;
	HW_LCDIF_TIMING.B.CMD_HOLD = 0x01;

	/* VSYNC and Dotclk Mode control setting */
	HW_LCDIF_VDCTRL0.B.VSYNC_PULSE_WIDTH = sync_waveform->vSyncPulseWidth;
	HW_LCDIF_VDCTRL0.B.VSYNC_PULSE_WIDTH_UNIT = sync_waveform->vSyncPulseUnit;
	HW_LCDIF_VDCTRL0.B.VSYNC_PERIOD_UNIT = sync_waveform->vSyncPeriodUnit;
	HW_LCDIF_VDCTRL0.B.ENABLE_POL = sync_waveform->enablePol;
	HW_LCDIF_VDCTRL0.B.DOTCLK_POL = sync_waveform->dotclkPol;
	HW_LCDIF_VDCTRL0.B.HSYNC_POL = sync_waveform->hsyncPol;
	HW_LCDIF_VDCTRL0.B.VSYNC_POL = sync_waveform->vSyncPol;
	HW_LCDIF_VDCTRL0.B.ENABLE_PRESENT = sync_waveform->enPresent;

	/* total vsync period */
	HW_LCDIF_VDCTRL1.B.VSYNC_PERIOD = sync_waveform->vSyncPeriod;

	/* total hsync setting */
	HW_LCDIF_VDCTRL2.B.HSYNC_PERIOD = sync_waveform->hSyncPeriod;
	HW_LCDIF_VDCTRL2.B.HSYNC_PULSE_WIDTH = sync_waveform->hSyncPulseWidth;

	HW_LCDIF_VDCTRL3.B.VERTICAL_WAIT_CNT = sync_waveform->vWaitCount;
	HW_LCDIF_VDCTRL3.B.HORIZONTAL_WAIT_CNT = sync_waveform->hWaitCount;

	HW_LCDIF_VDCTRL4.B.DOTCLK_H_VALID_DATA_CNT = sync_waveform->hValidDataCount;
	HW_LCDIF_VDCTRL4.B.SYNC_SIGNALS_ON = 0x1;

    return 0;
}

/*!
 * @brief Initialize lcdif controller
 */
static void lcdif_init(void)
{
	lcdif_power_on();
    lcdif_clock_enable();
    lcdif_backlight_on();

    /* pin muxing for LCD */
    lcd_iomux_config();

	/* reset controller */
    lcdif_sw_reset();

	/* setup the bus protocol
	 * 8080, signal from LCD is ignored */
	BW_LCDIF_CTRL1_MODE86(0);
	BW_LCDIF_CTRL1_BUSY_ENABLE(0);

	/* Take display out of reset */
	BW_LCDIF_CTRL1_RESET(1);

	/* VSYNC is an input by default */
	BW_LCDIF_VDCTRL0_VSYNC_OEB(1);

	/* Reset display */
	BW_LCDIF_CTRL1_RESET(0);
	hal_delay_us(10);
	BW_LCDIF_CTRL1_RESET(1);
	hal_delay_us(10);

	/* clear fifo in legency fifo: RX FIFO and TX FIFO */
	BW_LCDIF_CTRL1_FIFO_CLEAR(1);
	hal_delay_us(1000);
	BW_LCDIF_CTRL1_FIFO_CLEAR(0);
}

/*!
 * @brief Initialize LCD panel.
 *
 * Make sure high - to - low transition to reset the panel
 */
static void lcdif_panel_init(void)
{
	/* low */
	BW_LCDIF_CTRL1_RESET(0);
	hal_delay_us(100*1000);

	/* high */
	BW_LCDIF_CTRL1_RESET(1);	
	hal_delay_us(10*1000);

	/* low */
	BW_LCDIF_CTRL1_RESET(0);
	hal_delay_us(10*1000);

	/* high */
	BW_LCDIF_CTRL1_RESET(1);	
	hal_delay_us(1*1000);
}	

/*!
 * @brief Configure waveform parameters according to the timing of LCD panel
 *
 * @param   sync_waveform	lcd waveform setting, including hsync/vsync/drdy and blanking parameters
 */
static void setup_panel_params(lcdif_sync_waveform_t * syncWave)
{
    syncWave->frameWidth = WVGA_FW;
    syncWave->frameHeight = WVGA_FH;

    syncWave->enPresent = 1;
    //syncWave->dotclkPol = 0;
    syncWave->dotclkPol = 1;
    syncWave->hsyncPol = 0;
    syncWave->vSyncPol = 0;
    syncWave->enablePol = 1;
    syncWave->vSyncPeriodUnit = 1;
    syncWave->vSyncPulseUnit = 1;
    syncWave->vSyncPulseWidth = 10;

    syncWave->vSyncPeriod = 523;

    syncWave->hSyncPulseWidth = 10;
    syncWave->hSyncPeriod = 1063;

    syncWave->hWaitCount = 99;
    syncWave->vWaitCount = 33;

    syncWave->hValidDataCount = 800;
}

void lcdif_display_setup(void)
{
    lcdif_sync_waveform_t syncWave = { 0 };
    char recvCh = NONE_CHAR;

    memset((void *)DDR_LCD_BASE1, 0xFF, FRAME_WIDTH * FRAME_HEIGHT * 2);

    /* initilization for LCD */
    lcdif_init();
	/* make sure externel panel is reset by low-high transition */
    lcdif_panel_init();

    /* LCDIF control registers setting */
	BW_LCDIF_CTRL1_VSYNC_EDGE_IRQ(1);
	BW_LCDIF_CTRL1_BYTE_PACKING_FORMAT(0xF);
	BW_LCDIF_CTRL1_RECOVER_ON_UNDERFLOW(1);

	HW_LCDIF_CTRL2.B.OUTSTANDING_REQS = 0x4;

	/* VSYNC is an output by default */
	HW_LCDIF_VDCTRL0.B.VSYNC_OEB = 0;

	/* frame buffer start address */
	HW_LCDIF_CUR_BUF_WR(DDR_LCD_BASE1);
	HW_LCDIF_NEXT_BUF_WR(DDR_LCD_BASE1);


    /*DOTCLK or VSYNC mode control */
    setup_panel_params(&syncWave);
    lcdif_waveform_setting(&syncWave);

    printf("Please select the LCD panel type: \n");
    printf("\t0 - SEIKO 70WVW1TZ3 WVGA Panel (MX28LCD 24-bit)\n");
    printf("\t1 - CHUNHWA CLAA 070VC01 WVGA Panel (MX51LCD 16-bit)\n");
    do {
        recvCh = getchar();
    } while (recvCh == NONE_CHAR);

    if (recvCh == '0') {
        /*RGB888(24bit) in dotclk mode transfer */
		BW_LCDIF_CTRL_BYPASS_COUNT(1);	
		BW_LCDIF_CTRL_DOTCLK_MODE(1);	

		/* 24 bit data bus */
		BW_LCDIF_CTRL_LCD_DATABUS_WIDTH(0x3);

		BW_LCDIF_CTRL_MASTER(1);
		BW_LCDIF_CTRL_RUN(1);
    } else if (recvCh == '1') {
        /*RGB565(16bit) in dotclk mode transfer */
		BW_LCDIF_CTRL_BYPASS_COUNT(1);	
		BW_LCDIF_CTRL_DOTCLK_MODE(1);	

		/* 16 bit data bus */
		BW_LCDIF_CTRL_LCD_DATABUS_WIDTH(0x0);

		BW_LCDIF_CTRL_MASTER(1);
		BW_LCDIF_CTRL_RUN(1);
    } else {
        printf("Wrong panel type!\n");
    }
}

void image_center_copy(void)
{
    int width = 313, height = 117;
    int left_offset = (FRAME_WIDTH - width) / 2;
    int top_offset = (FRAME_HEIGHT - height) / 2;
    int i = 0;

    memset((void *)DDR_LCD_BASE1, 0xFF, FRAME_WIDTH * FRAME_HEIGHT * 2);

    for (i = 0; i < height; i++) {
        memcpy((void *)(DDR_LCD_BASE1 + FRAME_WIDTH * (top_offset + i) * 2 + left_offset * 2),
               &gImage_fsl[width * i * 2], width * 2);
    }
}
