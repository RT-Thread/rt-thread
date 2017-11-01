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

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/* ENET iomux config */
void imx_ar8031_iomux()
{
    enet_iomux_config();        // iomux tool output
}

/*CPU_PER_RST_B low to high*/
void imx_KSZ9021RN_reset(void)
{
    //max7310_set_gpio_output(0, 2, GPIO_LOW_LEVEL);
    //hal_delay_us(1000000);
    //max7310_set_gpio_output(0, 2, GPIO_HIGH_LEVEL);
#ifdef BOARD_SABRE_LITE
    // Config gpio3_GPIO[23] to pad EIM_D23(D25)
    gpio_set_gpio(GPIO_PORT3, 23);
    HW_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23_SRE_V(SLOW));
    gpio_set_direction(GPIO3, 23, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO3, 23, GPIO_LOW_LEVEL);
    hal_delay_us(1000000);      // hold in reset for a delay
    gpio_set_level(GPIO3, 23, GPIO_LOW_HIGH);
#endif
}

/*CPU_PER_RST_B low to high*/
void imx_ar8031_reset(void)
{
#if defined(BOARD_SMART_DEVICE)
    /* Select ALT5 mode of ENET_CRS-DV for GPIO1_25 - PGMII_NRST */
    /* active low output */
    gpio_set_direction(GPIO_PORT1, 25, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT1, 25, GPIO_LOW_LEVEL);
    hal_delay_us(500);
    gpio_set_level(GPIO_PORT1, 25, GPIO_HIGH_LEVEL);
#elif defined(BOARD_SABRE_AI) && !defined(BOARD_REV_A)
    /* CPU_PER_RST_B low to high */
//    max7310_set_gpio_output(0, 2, GPIO_LOW_LEVEL);
//    hal_delay_us(1000);
//    max7310_set_gpio_output(0, 2, GPIO_HIGH_LEVEL);
#endif
}

/*! From obds
 * ENET iomux config
 */
void imx_enet_iomux(void)
{
    enet_iomux_config();        // iomux tool output

#ifdef BOARD_SABRE_AI
    /* Select ENET, ENET_CAN1_STEER(PORT_EXP_B3) */
    max7310_set_gpio_output(1, 2, GPIO_LOW_LEVEL);
    /* Select ALT5 mode of GPIO_19 for GPIO4_5 - PGMIT_INT_B */
    /* active low input */
    gpio_set_gpio(GPIO_PORT4, 5);
    gpio_set_direction(GPIO_PORT4, 5, GPIO_GDIR_INPUT);
#endif
}

void imx_enet_phy_reset(void)
{
	imx_ar8031_reset();
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
