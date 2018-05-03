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
#include "iomux_define.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*!
 * Turn on LCDIF power_en pin
 *
 * KEY_ROW5 (pin79) controls WVGA panel DISP pin, which is active high. 
 * 
 */
void lcdif_power_on(void)
{
	/* turn on lcdif power on
	 * (KEY_ROW5) ALT5: GPIO4_3 */
    gpio_set_gpio(GPIO_PORT4, 3);
	gpio_set_direction(GPIO_PORT4, 3, GPIO_GDIR_OUTPUT);
	gpio_set_level(GPIO_PORT4, 3, GPIO_HIGH_LEVEL);
}

/* !
 * Turn on lcdif backlight power supply
 *
 * 3V3_LCD_CONTRAST (pin 112) controls LED+ and LED- on imx28lcd board */
void lcdif_backlight_on(void)
{
    gpio_set_gpio(GPIO_PORT3, 23);
	gpio_set_direction(GPIO_PORT3, 23, GPIO_GDIR_OUTPUT);
	gpio_set_level(GPIO_PORT3, 23, GPIO_HIGH_LEVEL);
}

/*!
 * Configure lcdif pixel clock.
 *
 * lcdif pixel clock is derived from PLL3(480MHz) and set as 33.5MHz
 */
void lcdif_clock_enable(void)
{
	/* select PLL3 (480MHz) as source of lcdif pixel clock */
	HW_CCM_CSCDR2.B.LCDIF_PIX_CLK_SEL = 0x01;

	/* pixel clock is 34MHz*/
	/* set pre divide: 2*/
	HW_CCM_CSCDR2.B.LCDIF_PIX_PRED = 2 - 1;

	/* set post divide: 7
	 * CCM_CSCMR1[22:20], bit 22 and bit 21 are inverted.
	 * 000 --- 110	div by 7
	 * 001 --- 111	div by 8
	 * 010 --- 100	div by 5
	 * etc*/
	HW_CCM_CSCMR1.B.LCDIF_PIX_PODF = (7 - 1) ^ 0x6;

	/* enable pixel clock and axi clock */
	HW_CCM_CCGR3.B.CG4 = 0x3;
	HW_CCM_CCGR3.B.CG3 = 0x3;
}


void epdc_clock_setting(int freq)
{
	HW_CCM_CSCDR2.B.EPDC_PIX_CLK_SEL = 0x5; //Use 540MPFD

	HW_CCM_CSCDR2.B.EPDC_PIX_PRED = 0x5; //pred for EPDC

	HW_CCM_CBCMR.B.EPDC_PIX_PODF = 0x4;

    /*set the AXI clock, divided from MMDC clock */
	HW_CCM_CHSCCDR.B.EPDC_AXI_CLK_SEL = 0x0;
	HW_CCM_CHSCCDR.B.EPDC_AXI_PODF = 0x1;
}

void sipix_epd_clock_setting(int freq)
{
    /* set the EPD clock for Sipix EPD, this is not documented in the reg headers */
    HW_IOMUXC_GPR0_SET(0x100);

	HW_CCM_CSCDR2.B.EPDC_PIX_CLK_SEL = 0x5; //Use 540MPFD

	HW_CCM_CSCDR2.B.EPDC_PIX_PRED = 0x2; //pred for EPDC

	HW_CCM_CBCMR.B.EPDC_PIX_PODF = 0x3;
}

void epdc_power_supply(void)
{
	int i = 0;

	//EN : pmic_wakeup gpio2.14
    gpio_set_gpio(GPIO_PORT2, 14);
	gpio_set_direction(GPIO_PORT2, 14, GPIO_GDIR_OUTPUT);
	gpio_set_level(GPIO_PORT2, 14, GPIO_HIGH_LEVEL);

    //CEN : pmic_vcom gpio2.3
    gpio_set_gpio(GPIO_PORT2, 3);
	gpio_set_direction(GPIO_PORT2, 3, GPIO_GDIR_OUTPUT);
	gpio_set_level(GPIO_PORT2, 3, GPIO_HIGH_LEVEL);

    for (i = 0; i < 1000000; i++)
        __asm("nop");
}

void spdc_power_up(void)
{
    int i = 0;

    gpio_set_gpio(GPIO_PORT1, 17);
    gpio_set_direction(GPIO_PORT1, 17, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT1, 17, GPIO_LOW_LEVEL);

    /* Using the MAX17135 as the power supplier 
     * Panel connector are using the AXT334124
     *
     * Power Sequence:
     * VDD_Panel -> VEE -> VGG -> VDNS -> VDPS -> Vcom
     * 
     * Pin Connections:
     * Name         Pin# of MAX17135        Pin# of AXT334124   Comment
     * VDD_Panel:   3V15(from mainboard)    5,7                 default enabled, comming from DCDC3V15
     * VEE          6(DGVEE)                27,29
     * VGG          4(DGVDD)                23,25
     * VDNS         23(POS)                 1,3
     * VDPS         24(NEG)                 2,4
     * Vcom:        22(VCOM)                22,24
     */
    gpio_set_gpio(GPIO_PORT2, 7);
    gpio_set_direction(GPIO_PORT2, 7, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 7, GPIO_HIGH_LEVEL);

    //EN : pmic_wakeup gpio2.14
    gpio_set_gpio(GPIO_PORT2, 14);
    gpio_set_direction(GPIO_PORT2, 14, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 14, GPIO_HIGH_LEVEL);

    //CEN : pmic_vcom gpio2.3 
    gpio_set_gpio(GPIO_PORT2, 3);
    gpio_set_direction(GPIO_PORT2, 3, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 3, GPIO_HIGH_LEVEL);

    while (i++ < 10000)
        __asm("nop");

    gpio_set_gpio(GPIO_PORT1, 17);
    gpio_set_direction(GPIO_PORT1, 17, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT1, 17, GPIO_HIGH_LEVEL);
}


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
