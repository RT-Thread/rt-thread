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
#include "registers/regsccmanalog.h"
#include "registers/regsccm.h"
#include "registers/regsiomuxc.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*!
 * Provide the LVDS power through GPIO pins
 */
void lvds_power_on(void)
{
#if defined(BOARD_EVB)
    board_ioexpander_iomux_config();
    /*3.3V power supply through the load switch FDC6331L */
    max7310_set_gpio_output(0, 0, GPIO_HIGH_LEVEL);
    max7310_set_gpio_output(1, 1, GPIO_HIGH_LEVEL);

    /*lvds backlight enable, GPIO_9 */
    gpio_set_gpio(GPIO_PORT1, 9);
    gpio_set_direction(GPIO_PORT1, 9, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT1, 9, GPIO_HIGH_LEVEL);
#endif

#ifdef BOARD_SMART_DEVICE
    // 3v3 on by default
    // AUX_5V_EN LVDS0 power
    gpio_set_gpio(GPIO_PORT6, 10);
    gpio_set_direction(GPIO_PORT6, 10, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT6, 10, GPIO_HIGH_LEVEL);
    // PMIC_5V LVDS1 power on by default
    // backlight both lvds1/0, disp0_contrast/disp0_pwm, gpio1[21]
    gpio_set_gpio(GPIO_PORT1, 21);
    gpio_set_direction(GPIO_PORT1, 21, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT1, 21, GPIO_HIGH_LEVEL);
#endif

#ifdef BOARD_SABRE_AI
    board_ioexpander_iomux_config();
    /*3.3V power supply through IOexpander */
    max7310_set_gpio_output(0, 0, GPIO_HIGH_LEVEL);

    /*lvds backlight enable, GPIO_9 */
    gpio_set_gpio(GPIO_PORT2, 9);
    gpio_set_direction(GPIO_PORT2, 9, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 9, GPIO_HIGH_LEVEL);

#endif
}

/*! From obds
 * Disable the display panel
 */
void disable_para_panel(void)
{
    gpio_set_gpio(GPIO_PORT2, 31);
    HW_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_WR(
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_HYS_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_PUS_V(100K_OHM_PU) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_PUE_V(PULL) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_PKE_V(ENABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_SPEED_V(100MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_DSE_V(40_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_SRE_V(SLOW));
    gpio_set_direction(GPIO_PORT2, 31, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 31, GPIO_LOW_LEVEL);
}

/*! Copy from OBDS
 * Provide the power for TFT LCD backlight
 */
void tftlcd_backlight_en(char *panel_name)
{
    if (!strcmp(panel_name, "CLAA01 WVGA")) {
        /*GPIO to provide backlight */
        gpio_set_gpio(GPIO_PORT4, 20);
        gpio_set_direction(GPIO_PORT4, 20, GPIO_GDIR_OUTPUT);
        gpio_set_level(GPIO_PORT4, 20, GPIO_HIGH_LEVEL);
    } else if (!strcmp(panel_name, "BoundaryDev WVGA")) {
#if defined (BOARD_REV_A)
        /*lvds/parallel display backlight enable, GPIO2_0 */
        gpio_set_gpio(GPIO_PORT2, 9);
        gpio_set_direction(GPIO_PORT2, 9, GPIO_GDIR_OUTPUT);
        gpio_set_level(GPIO_PORT2, 9, GPIO_HIGH_LEVEL);

        // lcd_contrast conflict with actual BoundaryDev display so seeting to input
        // since TSC not used on SABRE AI
        gpio_set_gpio(GPIO_PORT4, 20);
        gpio_set_direction(GPIO_PORT4, 20, GPIO_GDIR_INPUT);
#elif defined (BOARD_REV_B) || defined(BOARD_REV_C)
        gpio_set_gpio(GPIO_PORT4, 20);
        gpio_set_direction(GPIO_PORT4, 20, GPIO_GDIR_OUTPUT);
        gpio_set_level(GPIO_PORT4, 20, GPIO_HIGH_LEVEL);
#endif
    } else {
        printf("Unsupported panel!\n");
    }
#if 0
#ifdef BOARD_SABRE_AI
    /*lvds/parallel display backlight enable, GPIO2_0 */
    gpio_set_gpio(GPIO_PORT2, 9);
    gpio_set_direction(GPIO_PORT2, 9, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 9, GPIO_LOW_LEVEL);

    // lcd_contrast conflict with actual BoundaryDev display so seeting to input
    // since TSC not used on SABRE AI
    gpio_set_gpio(GPIO_PORT4, 20);
    gpio_set_direction(GPIO_PORT4, 20, GPIO_GDIR_INPUT);
#endif
#ifdef BOARD_SMART_DEVICE
    /* AUX_3V15 */
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
    // backlight both lvds1/0, disp0_contrast/disp0_pwm, gpio1[21]
    gpio_set_gpio(GPIO_PORT1, 21);
    gpio_set_direction(GPIO_PORT1, 21, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT1, 21, GPIO_HIGH_LEVEL);
    // AUX_5V_EN LVDS0 power
    gpio_set_gpio(GPIO_PORT6, 10);
    gpio_set_direction(GPIO_PORT6, 10, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT6, 10, GPIO_HIGH_LEVEL);
#endif
#endif

}

/*! Copy from OBDS
 * Reset the TFT LCD
 */
void tftlcd_reset(char *panel_name)
{
    if (!strcmp(panel_name, "CLAA01 WVGA")) {
#ifdef BOARD_EVB
        gpio_set_gpio(GPIO_PORT2, 31);
        HW_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_WR(
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_HYS_V(ENABLED) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_PUS_V(100K_OHM_PU) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_PUE_V(PULL) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_PKE_V(ENABLED) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_ODE_V(DISABLED) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_SPEED_V(100MHZ) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_DSE_V(40_OHM) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_SRE_V(SLOW));
        gpio_set_direction(GPIO_PORT2, 31, GPIO_GDIR_OUTPUT);
        gpio_set_level(GPIO_PORT2, 31, GPIO_LOW_LEVEL);
        hal_delay_us(1000);
        gpio_set_level(GPIO_PORT2, 31, GPIO_HIGH_LEVEL);
        hal_delay_us(1000);
#endif
#ifdef BOARD_SMART_DEVICE
        gpio_set_gpio(GPIO_PORT3, 8);
        HW_IOMUXC_SW_PAD_CTL_PAD_EIM_AD08_WR(
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_AD08_HYS_V(ENABLED) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_AD08_PUS_V(100K_OHM_PU) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_AD08_PUE_V(PULL) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_AD08_PKE_V(ENABLED) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_AD08_ODE_V(DISABLED) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_AD08_SPEED_V(100MHZ) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_AD08_DSE_V(40_OHM) |
                BF_IOMUXC_SW_PAD_CTL_PAD_EIM_AD08_SRE_V(SLOW));
        gpio_set_direction(GPIO_PORT3, 8, GPIO_GDIR_OUTPUT);
        gpio_set_level(GPIO_PORT3, 8, GPIO_LOW_LEVEL);
        hal_delay_us(1000);
        gpio_set_level(GPIO_PORT3, 8, GPIO_HIGH_LEVEL);
        hal_delay_us(1000);
#endif
    }
}

/*!
 * @brief Configure ldb clock as per the display resolution.
 *
 * ldb clock is derived from PLL5, ldb on ipu1
 */
void ldb_clock_config(int freq, int ipu_index)
{
    if (freq == 65000000)       //for XGA resolution
    {
        //config pll3 PFD1 to 455M. pll3 is 480M 
        BW_CCM_ANALOG_PFD_480_PFD1_FRAC(19);

        // set ldb_di0_clk_sel to PLL3 PFD1
        HW_CCM_CS2CDR.B.LDB_DI0_CLK_SEL = 3;
        HW_CCM_CS2CDR.B.LDB_DI1_CLK_SEL = 3;

        // set clk_div to 7
        HW_CCM_CSCMR2.B.LDB_DI0_IPU_DIV = 1;
        HW_CCM_CSCMR2.B.LDB_DI1_IPU_DIV = 1;

        if (ipu_index == 1) {
            //set ipu1_di0_clk_sel from ldb_di0_clk 
            HW_CCM_CHSCCDR.B.IPU1_DI0_CLK_SEL = 3;  // ldb_di0_clk
            HW_CCM_CHSCCDR.B.IPU1_DI1_CLK_SEL = 3;  // ldb_di0_clk
        }
#if CHIP_MX6DQ
        else {
            //set ipu2_di0_clk_sel from ldb_di0_clk 
            HW_CCM_CSCDR2.B.IPU2_DI0_CLK_SEL = 3;
            HW_CCM_CSCDR2.B.IPU2_DI1_CLK_SEL = 3;
        }
#endif // CHIP_MX6DQ
    } else {
        printf("The frequency %d for LDB is not supported yet.", freq);
    }
}

void epdc_clock_setting(int freq)
{
#if defined(CHIP_MX6SDL)
    HW_CCM_CSCDR2.B.EPDC_PIX_PRE_CLK_SEL = 0x3; // 307M PFD

    HW_CCM_CSCDR2.B.EPDC_PIX_CLK_SEL = 0x0;

    /*set the output as 271M */
    BW_CCM_ANALOG_PFD_528_PFD0_FRAC(0x23);

    HW_CCM_CSCDR2.B.EPDC_PIX_PODF = 0x7;    // post divider

//  HW_IOMUXC_SW_MUX_CTL_PAD_GPIO_3.B.MUX_MODE = ALT4; //set as clko
#endif

#if defined(CHIP_MX6SL)
    HW_CCM_CSCDR2.B.EPDC_PIX_CLK_SEL = 0x5; //Use 540MPFD

    HW_CCM_CSCDR2.B.EPDC_PIX_PRED = 0x5;    //pred for EPDC

    HW_CCM_CBCMR.B.EPDC_PIX_PODF = 0x4;

    /*set the AXI clock, divided from MMDC clock */
    HW_CCM_CHSCCDR.B.EPDC_AXI_CLK_SEL = 0x0;
    HW_CCM_CHSCCDR.B.EPDC_AXI_PODF = 0x1;
#endif
}

void epdc_power_supply(void)
{
    int i = 0;
#if defined(CHIP_MX6SDL)
#if defined(BOARD_EVB)
    /*PMIC wakeup */
    gpio_set_gpio(GPIO_PORT2, 31);
    gpio_set_direction(GPIO_PORT2, 31, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 31, GPIO_HIGH_LEVEL);

    /*PMIC vcom */
    gpio_set_gpio(GPIO_PORT3, 17);
    gpio_set_direction(GPIO_PORT3, 17, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT3, 17, GPIO_HIGH_LEVEL);
#elif defined(BOARD_SMART_DEVICE)
    /*PMIC wakeup */
    gpio_set_gpio(GPIO_PORT3, 20);
    gpio_set_direction(GPIO_PORT3, 20, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT3, 20, GPIO_HIGH_LEVEL);

    /*PMIC vcom */
    gpio_set_gpio(GPIO_PORT3, 17);
    gpio_set_direction(GPIO_PORT3, 17, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT3, 17, GPIO_HIGH_LEVEL);
#endif
#endif

#if defined(CHIP_MX6SL)
    //EN : pmic_wakeup gpio2.14
    gpio_set_gpio(GPIO_PORT2, 14);
    gpio_set_direction(GPIO_PORT2, 14, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 14, GPIO_HIGH_LEVEL);

    //CEN : pmic_vcom gpio2.3
    gpio_set_gpio(GPIO_PORT2, 3);
    gpio_set_direction(GPIO_PORT2, 3, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 3, GPIO_HIGH_LEVEL);
#endif
    for (i = 0; i < 1000000; i++)
        __asm("nop");
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
