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
#include "camera/camera_def.h"
#include "registers/regsiomuxc.h"
#include "registers/regsccm.h"
#include "registers/regsi2c.h"

extern void pf0100_enable_vgen4_1v8(void);
extern void pf0100_enable_vgen6_2v8(void);
extern void pf0100_enable_vgen2_1v5(void);
////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! The I2C signals that go over the camera connecter are connected
//! to I2C port 3.
uint8_t g_camera_i2c_port = HW_I2C3;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*!
 * power on camera sensor
 */
void camera_power_on(void)
{
    /*set io power high (DOVDD) */
    pf0100_enable_vgen4_1v8();
    hal_delay_us(500000);       /*T0 > 0ms until DOVDD stable */

    /*set analog power high (AVDD) */
    pf0100_enable_vgen6_2v8();
    hal_delay_us(500000);       /*T0 > 0ms until DOVDD stable */

    pf0100_enable_vgen2_1v5();
    hal_delay_us(500000);       /*T0 > 0ms until DOVDD stable */
}

/*!
 * reset camera sensor through GPIO on SMD board
 *
 */
void sensor_reset(void)
{
    int32_t reset_occupy = 1000, reset_delay = 1000;

    sensor_standby(0);

    /* MX6SL: cmos_reset_b through EPDC_SDSHR (GPIO1_26) */
    gpio_set_gpio(GPIO_PORT1, 26);
	gpio_set_direction(GPIO_PORT1, 26, GPIO_GDIR_OUTPUT);

	gpio_set_level(GPIO_PORT1, 26, GPIO_LOW_LEVEL);
    hal_delay_us(reset_occupy);

	gpio_set_level(GPIO_PORT1, 26, GPIO_HIGH_LEVEL);
    hal_delay_us(reset_delay);
}

/*!
 * set camera sensor to standby mode.
 *
 * @param	enable: specify whether set camera sensor to standby mode
 *
 */
void sensor_standby(int32_t enable)
{
    /* MX6SL:setting cmos_pwdn to EPDC_SDOE(gpio1_25), power down high active */
    gpio_set_gpio(GPIO_PORT1, 25);
	gpio_set_direction(GPIO_PORT1, 25, GPIO_GDIR_OUTPUT);
    if (enable)
		gpio_set_level(GPIO_PORT1, 25, GPIO_HIGH_LEVEL);
    else
		gpio_set_level(GPIO_PORT1, 25, GPIO_LOW_LEVEL);
}

/*!
 * set camera sensor clock to 24MHz.
 *
 */
void sensor_clock_setting(void)
{
    int32_t clock_delay = 1000;

    /* CMOS_XCLK through EPDC_GDRL (MCLK) */
	/* Document and register header is not consistent with what I set.
	 * measured the config perclk to OSC clock: 24MHz
	 */
	HW_IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL.B.MUX_MODE = ALT3;

	HW_CCM_CSCDR3.B.CSI_CORE_PODF = 0;
	HW_CCM_CSCDR3.B.CSI_CORE_CLK_SEL = 0;
	HW_CCM_CSCDR3.B.RESERVED0 = 0x41;

    hal_delay_us(clock_delay);
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
