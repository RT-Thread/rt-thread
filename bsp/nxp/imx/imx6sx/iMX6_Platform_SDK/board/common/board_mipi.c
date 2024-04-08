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
#include "registers/regsccm.h"
#include "registers/regsccmanalog.h"
#include "registers/regsiomuxc.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
/*!
 * Provide the mipi camera power and reset
 */
void mipi_cam_power_on(void)
{
#if defined(BOARD_EVB)
    board_ioexpander_iomux_config();
    /*reset of camera sensor, pin 27 */
    max7310_set_gpio_output(0, 2, GPIO_LOW_LEVEL);
    hal_delay_us(1000);
    max7310_set_gpio_output(0, 2, GPIO_HIGH_LEVEL);

    /*power supply through pin25 of connector, for cam_pdown, power down and then up */
    max7310_set_gpio_output(0, 0, GPIO_LOW_LEVEL);
    hal_delay_us(1000);
    max7310_set_gpio_output(0, 0, GPIO_HIGH_LEVEL);
//    max7310_set_gpio_output(1, 1, GPIO_HIGH_LEVEL);
#endif

#if defined(BOARD_SABRE_AI)
    board_ioexpander_iomux_config();
    /*power supply through pin25 of connector, direct connected to P3V3_DELAY,
       controlled by CPU_PER_RST_B */
    /*reset of camera sensor, together with the reset button */
    max7310_set_gpio_output(0, 2, GPIO_LOW_LEVEL);
    hal_delay_us(1000);
    max7310_set_gpio_output(0, 2, GPIO_HIGH_LEVEL);
    max7310_set_gpio_output(0, 0, GPIO_HIGH_LEVEL);

#endif

#if defined(BOARD_SMART_DEVICE)
    /*power supply through pin25 of connector, for cam_pdown */
    gpio_set_gpio(GPIO_PORT6, 9);
    HW_IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B_SRE_V(SLOW));
    gpio_set_direction(GPIO_PORT6, 9, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT6, 9, GPIO_HIGH_LEVEL);

    /*reset of camera sensor, pin 27 */
    gpio_set_gpio(GPIO_PORT6, 10);
    HW_IOMUXC_SW_PAD_CTL_PAD_NAND_READY_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_READY_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_READY_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_READY_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_READY_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_READY_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_READY_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_READY_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_READY_SRE_V(SLOW));
    gpio_set_direction(GPIO_PORT6, 10, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT6, 10, GPIO_LOW_LEVEL);
    hal_delay_us(1000);
    gpio_set_level(GPIO_PORT6, 10, GPIO_HIGH_LEVEL);
#endif
}

/*!
 * enable mipi backlight
 */
void mipi_backlight_en(void)
{
    //configure pin19 of the mipi dsi/csi connector
#ifdef BOARD_EVB
    //set GPIO1_9 to 0 so clear vbus on board
    gpio_set_direction(GPIO_PORT1, 9, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT1, 9, GPIO_HIGH_LEVEL);
#endif

#ifdef BOARD_SABRE_AI
    //default be populated by P3V3_DELAYED
#endif

#ifdef BOARD_SMART_DEVICE
    gpio_set_gpio(GPIO_PORT2, 0);
    HW_IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00_SRE_V(SLOW));
    gpio_set_direction(GPIO_PORT2, 0, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 0, GPIO_HIGH_LEVEL);
#endif
}

/*!
 * reset MIPI display
 */
void mipi_display_reset(void)
{
#ifdef BOARD_EVB
/*pin29 of mipi connector for the LCD reset*/
    gpio_set_gpio(GPIO_PORT5, 0);
    HW_IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_SRE_V(SLOW));
    gpio_set_direction(GPIO_PORT5, 0, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT5, 0, GPIO_LOW_LEVEL);
    hal_delay_us(1000);
    gpio_set_level(GPIO_PORT5, 0, GPIO_HIGH_LEVEL);
    hal_delay_us(1000);
#endif

#ifdef BOARD_SABRE_AI
/*binded with the board reset button*/
#endif

#ifdef BOARD_SMART_DEVICE
/*pin29 of mipi connector for the LCD reset*/
    gpio_set_gpio(GPIO_PORT6, 11);
    HW_IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B_SRE_V(SLOW));
    gpio_set_direction(GPIO_PORT6, 11, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT6, 11, GPIO_LOW_LEVEL);
    hal_delay_us(1000);
    gpio_set_level(GPIO_PORT6, 11, GPIO_HIGH_LEVEL);
    hal_delay_us(1000);
#endif
}

void mipi_clock_set(void)
{
    BW_CCM_ANALOG_PFD_480_PFD1_FRAC(0x10);
}

void mipi_csi2_clock_set(void)
{
    //set VIDPLL(PLL5) to 596MHz 
    HW_CCM_ANALOG_PLL_VIDEO_WR(BF_CCM_ANALOG_PLL_VIDEO_DIV_SELECT(0) |
                               BF_CCM_ANALOG_PLL_VIDEO_ENABLE(1));
    HW_CCM_ANALOG_PLL_VIDEO_NUM_WR(0x00000000);
    HW_CCM_ANALOG_PLL_VIDEO_DENOM_WR(0x00000001);
    while (!HW_CCM_ANALOG_PLL_VIDEO.B.LOCK) ;   //waiting for PLL lock
    BF_CLR(CCM_ANALOG_PLL_VIDEO, BYPASS);

    //select CSI0_HSYNC osc_clk 24MHz, CKO1 output drives cko2 clock
    HW_IOMUXC_SW_MUX_CTL_PAD_CSI0_HSYNC_WR(
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_HSYNC_SION_V(DISABLED) |
            BF_IOMUXC_SW_MUX_CTL_PAD_CSI0_HSYNC_MUX_MODE_V(ALT3));

    HW_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC_SRE_V(SLOW));

    HW_CCM_CCOSR_WR(
                    BF_CCM_CCOSR_CLKO1_SEL(0) |
                    BF_CCM_CCOSR_CLKO1_DIV(0) |
                    BF_CCM_CCOSR_CLKO1_EN(1) |
                    BF_CCM_CCOSR_CLKO_SEL(1) |       // select cko2 for cko1 output
                    BF_CCM_CCOSR_CLKO2_SEL(0xe) |    // osc_clk
                    BF_CCM_CCOSR_CLKO2_DIV(0) |      // div 1
                    BF_CCM_CCOSR_CLKO2_EN(1));
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
