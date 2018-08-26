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

/*!
 * @file camera_def.h
 * @brief common macro and data structre defination of camera.
 * @ingroup diag_camera
 */

#include "video/adv7180_def.h"
#include "sdk.h"
#include "registers/regsiomuxc.h"

/*! Description of video formats supported.
 *
 *  PAL: raw=720x625, active=720x576.
 *  NTSC: raw=720x525, active=720x480.
 */
video_fmt_t video_fmts[] = {
	{			/*! NTSC */
	 .fmt_id = ADV7180_NTSC,
	 .name = "NTSC",
	 .raw_width = 720,	/* SENS_FRM_WIDTH */
	 .raw_height = 525,	/* SENS_FRM_HEIGHT */
	 .active_width = 720,	/* ACT_FRM_WIDTH plus 1 */
	 .active_height = 480,	/* ACT_FRM_WIDTH plus 1 */
	 },
	{			/*! (B, G, H, I, N) PAL */
	 .fmt_id = ADV7180_PAL,
	 .name = "PAL",
	 .raw_width = 720,
	 .raw_height = 625,
	 .active_width = 720,
	 .active_height = 576,
	 },
	{			/*! Unlocked standard */
	 .fmt_id = ADV7180_NOT_LOCKED,
	 .name = "Autodetect",
	 .raw_width = 720,
	 .raw_height = 625,
	 .active_width = 720,
	 .active_height = 576,
	 },
};

t_adv7180_i2c_reg_param adv7180_work_mode[] = {
	/* video input and output format:
	 * standard video input
	 * interlveaved ITU-R BT.656 */
	{0x01, 0xc8}, {0x02, 0x04}, {0x03, 0x00}, {0x04, 0xC4},
	/* video quality setting */
	{0x05, 0x00}, {0x06, 0x02}, {0x07, 0x7F}, {0x08, 0x80},
	{0x0A, 0x00}, {0x0B, 0x00}, {0x0C, 0x36}, {0x0D, 0x7C},
	{0x0E, 0x00}, {0x0F, 0x00}, {0x13, 0x00}, {0x14, 0x12},
	{0x15, 0x00}, {0x16, 0x00}, {0x17, 0x01}, {0x18, 0x93},
	{0xF1, 0x19}, {0x1A, 0x00}, {0x1B, 0x00}, {0x1C, 0x00},
	{0x1D, 0x40}, {0x1E, 0x00}, {0x1F, 0x00}, {0x20, 0x00},
	{0x21, 0x00}, {0x22, 0x00}, {0x23, 0xC0}, {0x24, 0x00},
	{0x25, 0x00}, {0x26, 0x00}, {0x28, 0x00}, {0x29, 0x00},
	{0x2A, 0x00}, {0x2B, 0xE1}, {0x2C, 0xAE}, {0x2D, 0xF4},
	{0x2E, 0x00}, {0x2F, 0xF0}, {0x30, 0x00}, {0x31, 0x12},
	{0x32, 0x41}, {0x33, 0x84}, {0x34, 0x00}, {0x35, 0x00},
	{0x36, 0x00}, {0x37, 0x01}, {0x38, 0x80}, {0x39, 0xC0},
	{0x3A, 0x10}, {0x3B, 0x05}, {0x3C, 0x58}, {0x3D, 0xB2},
	{0x3E, 0x64}, {0x3F, 0xE4}, {0x40, 0x90}, {0x41, 0x01},
	{0x42, 0x7E}, {0x43, 0xA4}, {0x44, 0xFF}, {0x45, 0xB6},
	{0x46, 0x12}, {0x48, 0x00}, {0x49, 0x00}, {0x4A, 0x00},
	{0x4B, 0x00}, {0x4C, 0x00}, {0x4D, 0xEF}, {0x4E, 0x08},
	{0x4F, 0x08}, {0x50, 0x08}, {0x51, 0x24}, {0x52, 0x0B},
	{0x53, 0x4E}, {0x54, 0x80}, {0x55, 0x00}, {0x56, 0x10},
	{0x57, 0x00}, {0x58, 0x00}, {0x59, 0x00}, {0x5A, 0x00},
	{0x5B, 0x00}, {0x5C, 0x00}, {0x5D, 0x00}, {0x5E, 0x00},
	{0x5F, 0x00}, {0x60, 0x00}, {0x61, 0x00}, {0x62, 0x20},
	{0x63, 0x00}, {0x64, 0x00}, {0x65, 0x00}, {0x66, 0x00},
	{0x67, 0x03}, {0x68, 0x01}, {0x69, 0x00}, {0x6A, 0x00},
	{0x6B, 0xC0}, {0x6C, 0x00}, {0x6D, 0x00}, {0x6E, 0x00},
	{0x6F, 0x00}, {0x70, 0x00}, {0x71, 0x00}, {0x72, 0x00},
	{0x73, 0x10}, {0x74, 0x04}, {0x75, 0x01}, {0x76, 0x00},
	{0x77, 0x3F}, {0x78, 0xFF}, {0x79, 0xFF}, {0x7A, 0xFF},
	{0x7B, 0x1E}, {0x7C, 0xC0}, {0x7D, 0x00}, {0x7E, 0x00},
	{0x7F, 0x00}, {0x80, 0x00}, {0x81, 0xC0}, {0x82, 0x04},
	{0x83, 0x00}, {0x84, 0x0C}, {0x85, 0x02}, {0x86, 0x03},
	{0x87, 0x63}, {0x88, 0x5A}, {0x89, 0x08}, {0x8A, 0x10},
	{0x8B, 0x00}, {0x8C, 0x40}, {0x8D, 0x00}, {0x8E, 0x40},
	{0x8F, 0x00}, {0x90, 0x00}, {0x91, 0x50}, {0x92, 0x00},
	{0x93, 0x00}, {0x94, 0x00}, {0x95, 0x00}, {0x96, 0x00},
	{0x97, 0xF0}, {0x98, 0x00}, {0x99, 0x00}, {0x9A, 0x00},
	{0x9B, 0x00}, {0x9C, 0x00}, {0x9D, 0x00}, {0x9E, 0x00},
	{0x9F, 0x00}, {0xA0, 0x00}, {0xA1, 0x00}, {0xA2, 0x00},
	{0xA3, 0x00}, {0xA4, 0x00}, {0xA5, 0x00}, {0xA6, 0x00},
	{0xA7, 0x00}, {0xA8, 0x00}, {0xA9, 0x00}, {0xAA, 0x00},
	{0xAB, 0x00}, {0xAC, 0x00}, {0xAD, 0x00}, {0xAE, 0x60},
	{0xAF, 0x00}, {0xB0, 0x00}, {0xB1, 0x60}, {0xB2, 0x1C},
	{0xB3, 0x54}, {0xB4, 0x00}, {0xB5, 0x00}, {0xB6, 0x00},
	{0xB7, 0x13}, {0xB8, 0x03}, {0xB9, 0x33}, {0xBF, 0x02},
	{0xC0, 0x00}, {0xC1, 0x00}, {0xC2, 0x00}, {0xC3, 0x00},
	{0xC4, 0x00}, {0xC5, 0x81}, {0xC6, 0x00}, {0xC7, 0x00},
	{0xC8, 0x00}, {0xC9, 0x04}, {0xCC, 0x69}, {0xCD, 0x00},
	{0xCE, 0x01}, {0xCF, 0xB4}, {0xD0, 0x00}, {0xD1, 0x10},
	{0xD2, 0xFF}, {0xD3, 0xFF}, {0xD4, 0x7F}, {0xD5, 0x7F},
	{0xD6, 0x3E}, {0xD7, 0x08}, {0xD8, 0x3C}, {0xD9, 0x08},
	{0xDA, 0x3C}, {0xDB, 0x9B}, {0xDC, 0xAC}, {0xDD, 0x4C},
	{0xDE, 0x00}, {0xDF, 0x00}, {0xE0, 0x14}, {0xE1, 0x80},
	{0xE2, 0x80}, {0xE3, 0x80}, {0xE4, 0x80}, {0xE5, 0x25},
	{0xE6, 0x44}, {0xE7, 0x63}, {0xE8, 0x65}, {0xE9, 0x14},
	{0xEA, 0x63}, {0xEB, 0x55}, {0xEC, 0x55}, {0xEE, 0x00},
	{0xEF, 0x4A}, {0xF0, 0x44}, {0xF1, 0x0C}, {0xF2, 0x32},
	{0xF3, 0x00}, {0xF4, 0x3F}, {0xF5, 0xE0}, {0xF6, 0x69},
	{0xF7, 0x10}, {0xF8, 0x00}, {0xF9, 0x03}, {0xFA, 0xFA},
	{0xFB, 0x40},
};

static void adv7180_hard_reset(uint8_t cvbs);

/*!
 * @brief initialize the i2c module for adv7180 -- mainly enable the i2c clock, module itself and the i2c clock prescaler.
 *
 * @param   base        base address of i2c module (also assigned for i2cx_clk)
 * @param   baud        the desired data rate in bps
 *
 * @return  0 if successful; non-zero otherwise
 */
static int32_t adv7180_i2c_init(uint32_t base, uint32_t baud)
{
    int32_t ret = 0;
    int32_t i2c_delay = 500 * 1000;

    ret = i2c_init(base, baud);
    if (ret != 0) {
        printf("I2C initialization failed!\n");
        return ret;
    }
    hal_delay_us(i2c_delay);

    return ret;
}

/*!
 * @brief Perform I2C write operation for adv7180 
 *
 * @param   reg 	sensor i2c register address
 * @param	pval 	value write to i2c register
 *
 * @return  0 if successful; non-zero otherwise
 */
static int32_t adv7180_write_reg(uint8_t reg, uint8_t pval)
{
    int ret = 0;
    struct imx_i2c_request rq = {0};

    rq.ctl_addr = g_adv7180_i2c_device.port;
    rq.dev_addr = g_adv7180_i2c_device.address;
    rq.reg_addr = reg;
    rq.reg_addr_sz = 1;

    rq.buffer_sz = 1;
    rq.buffer = &pval;
    ret = i2c_xfer(&rq, I2C_WRITE);

    return ret;
}

/*!
 * @brief Perform I2C read operation for adv7180
 *
 * @param   reg 	sensor i2c register address
 * @param	pval 	value read from i2c register
 *
 * @return  0 if successful; non-zero otherwise
 */
static int32_t adv7180_read_reg(uint8_t reg)
{
    int ret = 0;
    struct imx_i2c_request rq = {0};
	uint8_t pval = 0;

    rq.ctl_addr = g_adv7180_i2c_device.port;
    rq.dev_addr = g_adv7180_i2c_device.address;
    rq.reg_addr = reg;
    rq.reg_addr_sz = 1;

    rq.buffer_sz = 1;
    rq.buffer = &pval;
    ret = i2c_xfer(&rq, I2C_READ);

	if (ret == 0)
    	return (int32_t) pval;
	else 
		return -1;
}

/*!
 * @brief Perform adv7180 hardware power-down operation
 *
 * When @pwdn equals 0, it initiates hardware power-down mode
 * Before entering work mode, make sure call this function with @pwdn equals 1.
 *
 * @param	pwdn parameter controlis if initiate a hardware power-down mode or normal work mode. 0 for power-down mode, 1 for normal work mode.
 */
static void adv7180_pwdn(int32_t pwdn)
{
#if defined(BOARD_EVB)
    /*Tvin power down: PORT2_P97 -- CSI0_DAT5 (GPIO5_23) */
	gpio_set_gpio(GPIO_PORT5, 23);
	gpio_set_direction(GPIO_PORT5, 23, GPIO_GDIR_OUTPUT);

	if (pwdn == 1)
		gpio_set_level(GPIO_PORT5, 23, GPIO_HIGH_LEVEL);
	else
		gpio_set_level(GPIO_PORT5, 23, GPIO_LOW_LEVEL);
#elif defined(BOARD_SABRE_AI)
	if (pwdn == 1)
        max7310_set_gpio_output(1, 2, GPIO_HIGH_LEVEL);
    else
        max7310_set_gpio_output(1, 2, GPIO_LOW_LEVEL);
#endif
}

/*!
 * @brief Perform adv7180 reset operation
 *
 * Reset adv7180 through GPIO according to the timing specified by datasheet
 *
 */
static void adv7180_reset(void)
{
	int32_t reset_delay = 100000;

#if defined(BOARD_EVB)
	/*Tvin reset: PORT2_P95 -- CSI0_DAT7 ALT5 (GPIO5-25) */
    gpio_set_gpio(GPIO_PORT5, 25);
	gpio_set_direction(GPIO_PORT5, 25, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT5, 25, GPIO_HIGH_LEVEL);
#endif

	/*Tvin power down: PORT2_P97 */
	adv7180_pwdn(0);
	hal_delay_us(reset_delay);

	/*Turn into work mode by set power down to high level*/
	adv7180_pwdn(1);
}

/*!
 * @brief Software set the adv7180 power.
 *
 * @param	on whether turn on the adv7180 power on register.  1 for power on. 0 for power off.
 *
 * @return 0 on success; non-zero otherwise
 */
static int32_t adv7180_power_on(int32_t on)
{
	if (on) { /*turn on */
		if (adv7180_write_reg(ADV7180_PWR_MNG, 0) != 0)
			return TEST_FAILED;
	} else { /*turn off*/
		if (adv7180_write_reg(ADV7180_PWR_MNG, 0x24) != 0)
			return TEST_FAILED;
	}

	return TEST_PASSED;
}

/*!
 * @brief Initialize CSI and adv7180 io interface
 *
 */
static void csi0_tvin_io_init(void)
{
	/* iomux setting for csi0 */
	csi_port0_iomux_config();

	/* Tvin reset */
	adv7180_reset();

	hal_delay_us(20000);
}

int32_t adv7180_init(void)
{
	int8_t rev_id = 0;
	int8_t cvbs = 0; // YPrPb input false on arm2 board

	csi0_tvin_io_init();

	adv7180_i2c_init(g_adv7180_i2c_device.port, 50000);
	/* read the revision ID of the tvin chip */
	rev_id = adv7180_read_reg(ADV7180_IDENT);
	if (!((rev_id == 0x1B) || (rev_id == 0x1C) || (rev_id == 0x1E))) {
		printf("ADV7180 is expected! Wrong Version %02X\n", rev_id);
		return TEST_FAILED;
	}

	/* ADV7180 initialization. */
	adv7180_hard_reset(cvbs);

	hal_delay_us(500000);

	return TEST_PASSED;
}

int32_t adv7180_get_std(void)
{
	uint32_t reg_val;
	int32_t idx;

	adv7180_i2c_init(g_adv7180_i2c_device.port, 50000);

	/* Read the AD_RESULT to get the output video standard */
	reg_val = adv7180_read_reg(ADV7180_STATUS_1) & 0x70;

	if (reg_val == 0x40) {
		/* PAL */
		idx = ADV7180_PAL;
	} else if (reg_val == 0) {
		/*NTSC*/
		idx = ADV7180_NTSC;
	} else {
		idx = ADV7180_NOT_LOCKED;
		printf("Got invalid video standard!\n");
	}

	return idx;
}

int32_t adv7180_is_interlaced_mode(void)
{
	uint32_t reg_val;

	adv7180_i2c_init(g_adv7180_i2c_device.port, 50000);
	/* Read the AD_RESULT to get the output video if interlaced or progressive */
	reg_val = adv7180_read_reg(ADV7180_STATUS_3) & 0x40;

	if (reg_val)
		return 1;
	else 
		return 0;
}

/*!
 * @brief Reset and configure adv7180 into auto work mode
 *
 * @param	cvbs specify if the video input is CVBS input or YPbPr input. 1 for CVBS input on AIN1. 0 for YPbPr input on AIN1, 4, 5
 */
static void adv7180_hard_reset(uint8_t cvbs)
{
	int i;

	adv7180_i2c_init(g_adv7180_i2c_device.port, 50000);

	if (cvbs) {
		/* Set CVBS input on AIN1 */
		adv7180_write_reg(ADV7180_INPUT_CTL, 0x00);
		/* luma timing: [1:0]0x00 No delay
		 * chrome: [5:3] 0x03 No delay
		 * */
		adv7180_write_reg(0x27, 0x58); 
	} else {
		/*
		 * Set YPbPr input on AIN1,4,5 and normal
		 * operations(autodection of all stds).
		 */
		adv7180_write_reg(ADV7180_INPUT_CTL, 0x09);
		/* luma timing: [1:0]0x01 37ns
		 * chrome timeing: [5:3] 0x6 three pixels (late)
		 * */
		adv7180_write_reg(0x27, 0x71);
	}

	/* Datasheet recommends */
	/* download adv7180 */
	for (i = 0; i < sizeof(adv7180_work_mode) / sizeof(t_adv7180_i2c_reg_param); i++) {
		t_adv7180_i2c_reg_param *setting = &adv7180_work_mode[i];
		adv7180_write_reg(setting->addr, setting->value);
	}
}
