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
#include "registers/regsiomuxc.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief IOMUX configuration for the Android_Buttons
//! @todo Confirm this functionality. Values written to the PAD registers do not make sense with comments.
void android_buttons_iomux_config()
{
    //HOME_(SD2_CMD_GPI1_11)
    gpio_set_gpio(GPIO_PORT1, 11);
    HW_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_WR(                            // pull-up enabled at pad
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_HYS_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_PUE_V(KEEP) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_PKE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_SPEED_V(200MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_DSE_V(60_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_CMD_SRE_V(SLOW));

    //BACK_(SD2_DATA3_GPI1_12)
    gpio_set_gpio(GPIO_PORT1, 12);
    HW_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_WR(                          // pull-up enabled at pad
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_HYS_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_PUE_V(KEEP) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_PKE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_SPEED_V(200MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_DSE_V(60_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3_SRE_V(SLOW));

    //PROG_(SD4_DATA4_GPI2_12)
    gpio_set_gpio(GPIO_PORT2, 12);
    HW_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_WR(                          // pull-up enabled at pad
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_HYS_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_PUE_V(KEEP) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_PKE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_SPEED_V(200MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_DSE_V(60_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4_SRE_V(SLOW));

    //VOL+_(SD4_DATA7_GPI2_15)
    gpio_set_gpio(GPIO_PORT2, 15);
    HW_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7_WR(                          // pull-up enabled at pad
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7_HYS_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7_PUE_V(KEEP) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7_PKE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7_SPEED_V(200MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7_DSE_V(60_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7_SRE_V(SLOW));

    //VOL-_(DISP0_DATA20_GPI5_14)
    gpio_set_gpio(GPIO_PORT5, 14);
    HW_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20_WR(                       // pull-up enabled at pad
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20_HYS_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20_PUS_V(100K_OHM_PD) |
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20_PUE_V(KEEP) |
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20_PKE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20_ODE_V(DISABLED) |
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20_SPEED_V(200MHZ) |
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20_DSE_V(60_OHM) |
            BF_IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20_SRE_V(SLOW));
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
