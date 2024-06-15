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
#include "registers/regspmu.h"
#include "registers/regsiomuxc.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void pcie_clk_setup(uint32_t enable)
{
    if (enable) {
        // gate on pci-e clks
        HW_CCM_CCGR4.B.CG0 = CLOCK_ON;

        // clear the powerdown bit
        HW_CCM_ANALOG_PLL_ENET_CLR(BM_CCM_ANALOG_PLL_ENET_POWERDOWN);
        // enable pll
        HW_CCM_ANALOG_PLL_ENET_SET(BM_CCM_ANALOG_PLL_ENET_ENABLE);
        // wait the pll locked
        while (!HW_CCM_ANALOG_PLL_ENET.B.LOCK) ;
        // Disable bypass
        HW_CCM_ANALOG_PLL_ENET_CLR(BM_CCM_ANALOG_PLL_ENET_BYPASS);
        // enable pci-e ref clk
        HW_CCM_ANALOG_PLL_ENET_SET(BM_CCM_ANALOG_PLL_ENET_ENABLE_125M);
    }
}

void pcie_card_pwr_setup(uint32_t enable)
{
#if defined(BOARD_EVB)
    i2c_init(I2C3_BASE_ADDR, 100000);
    board_ioexpander_iomux_config();

    if (enable) {
        //enable pciemini_3.3v
        max7310_set_gpio_output(1, 2, 1);
    } else {
        max7310_set_gpio_output(1, 2, 0);
    }
#endif

#if defined(BOARD_SMART_DEVICE)
   gpio_set_gpio(GPIO_PORT3, 19);
   gpio_set_direction(GPIO_PORT3, 19, GPIO_GDIR_OUTPUT); 

   if(enable){
	gpio_set_level(GPIO_PORT3, 19, GPIO_HIGH_LEVEL);
   }else{
	gpio_set_level(GPIO_PORT3, 19, GPIO_LOW_LEVEL);
   } 
#endif
}

void pcie_enable_extrn_125mhz_clk(uint32_t enable)
{
    if (enable) {
	//Enable 125MHz output of Enet_PLL
        HW_CCM_ANALOG_PLL_ENET_SET(BM_CCM_ANALOG_PLL_ENET_ENABLE_125M);

        // Select PCIe clock source and switch to output buffer, ie, CLK1_N/CLK1_P
        HW_PMU_MISC1_CLR(BM_PMU_MISC1_LVDSCLK1_IBEN);
        HW_PMU_MISC1.B.LVDS1_CLK_SEL = BV_PMU_MISC1_LVDS1_CLK_SEL__PCIE_REF;
        HW_PMU_MISC1_SET(BM_PMU_MISC1_LVDSCLK1_OBEN);
    }
}

// The external 100 MHz clock
void pcie_enable_extrn_100mhz_clk(uint32_t enable)
{
#if defined(CHIP_MX6SDL)
#define BV_PMU_MISC1_LVDS1_CLK_SEL__SATA_REF	11
#endif

    if (enable) {
	//Enable 100MHz output of Enet_PLL
        HW_CCM_ANALOG_PLL_ENET_SET(BM_CCM_ANALOG_PLL_ENET_ENABLE_100M);

        HW_PMU_MISC1_CLR(BM_PMU_MISC1_LVDSCLK1_IBEN);
        HW_PMU_MISC1.B.LVDS1_CLK_SEL = BV_PMU_MISC1_LVDS1_CLK_SEL__SATA_REF;
        HW_PMU_MISC1_SET(BM_PMU_MISC1_LVDSCLK1_OBEN);
    }
}

void pcie_card_rst(void)
{
#if defined(BOARD_EVB)
    i2c_init(I2C3_BASE_ADDR, 100000);
    board_ioexpander_iomux_config();

    max7310_set_gpio_output(0, 2, 0);

    hal_delay_us(200 * 1000);

    max7310_set_gpio_output(0, 2, 1);
#endif

#if defined(BOARD_SMART_DEVICE)
    gpio_set_gpio(GPIO_PORT4, 5);
    gpio_set_direction(GPIO_PORT4, 5, GPIO_GDIR_OUTPUT); 

    gpio_set_level(GPIO_PORT4, 5, GPIO_LOW_LEVEL);
    hal_delay_us(200 * 1000);
    gpio_set_level(GPIO_PORT4, 5, GPIO_HIGH_LEVEL);
#endif
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
