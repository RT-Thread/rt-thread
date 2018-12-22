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
#include "registers/regsesai.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void SGTL5000PowerUp_and_clockinit(void)
{
}

/*!
 *
 * Additional code related to clock configuration
 *
 */
unsigned int spdif_get_tx_clk_freq(void)
{
    return 30000000;
}

/*! From obds
 * Audio Codec Power on
 */
void audio_codec_power_on (void)
{
#ifdef BOARD_SMART_DEVICE
    //CODEC PWR_EN, key_col12
    gpio_set_gpio(GPIO_PORT4, 10);
    gpio_set_direction(GPIO_PORT4, 10, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT4, 10, GPIO_HIGH_LEVEL);
#endif
}

/*! From obds
 * Audio Clock Config
 */
void audio_clock_config(void)
{
#if defined(BOARD_SMART_DEVICE) 
    ccm_iomux_config();

    HW_CCM_CCOSR_WR(BF_CCM_CCOSR_CLKO2_EN(1)
                    | BF_CCM_CCOSR_CLKO2_DIV(6)
                    | BF_CCM_CCOSR_CLKO2_SEL(0x13)
                    | BF_CCM_CCOSR_CLKO_SEL(1));
#endif
}

/*!
 * @brief SPDIF clock configuration
 *
 * Use the default setting as follow:
 * CDCDR[spdif0_clk_sel](PLL3)->CDCDR[spdif0_clk_pred](div2)->CDCDR[spdif0_clk_podf](div8)-> spdif0_clk_root, so
 * the freqency of spdif0_clk should be 480/2/8 = 30MHz.
 */
void spdif_clk_cfg(void)
{
    HW_CCM_CDCDR.B.SPDIF0_CLK_SEL = 3;  // PLL3
    HW_CCM_CDCDR.B.SPDIF0_CLK_PODF = 7; // div 8
    HW_CCM_CDCDR.B.SPDIF0_CLK_PRED = 1; // div 2

    clock_gating_config(SPDIF_BASE_ADDR, CLOCK_ON);

    return;
}

/*!
 * Power no esai codec.
 */
int esai_codec_power_on(void)
{
    // No need to do anything for BOARD_SABRE_AI
    return 0;
}

void esai_clk_sel_gate_on()
{
    // source from PLL3_508
    HW_CCM_CSCMR2.B.ESAI_CLK_SEL = 1;

    clock_gating_config(REGS_ESAI_BASE, CLOCK_ON);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
