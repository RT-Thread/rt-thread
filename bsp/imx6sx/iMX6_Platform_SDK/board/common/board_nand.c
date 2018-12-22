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

#include "gpmi/gpmi.h"
#include "core/ccm_pll.h"
#include "registers/regsgpmi.h"
#include "registers/regsccm.h"
#include "registers/regsccmanalog.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Configure and enable the GPMI and BCH clocks.
//!
//! The GPMI clock is selected to be sourced from the main PLL3 clock (480 MHz), then
//! divided by 4 and again by 1. The resulting clock is 120 MHz.
void gpmi_nand_clk_setup(void)
{
    HW_CCM_ANALOG_PFD_528_CLR(BM_CCM_ANALOG_PFD_528_PFD2_CLKGATE);

    // Gate clocks before adjusting dividers.
    clock_gating_config(REGS_GPMI_BASE, CLOCK_OFF);

    HW_CCM_CS2CDR.B.ENFC_CLK_SEL = 2;   // Select pll3 clock (480 MHz)
    HW_CCM_CS2CDR.B.ENFC_CLK_PRED = 3;  // Divide by 4
    HW_CCM_CS2CDR.B.ENFC_CLK_PODF = 0;  // Divide by 1

    // Ungate clocks.
    clock_gating_config(REGS_GPMI_BASE, CLOCK_ON);

    HW_CCM_CCGR0.B.CG2 = CLOCK_ON;  // apbhdma_hclk_enable
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
