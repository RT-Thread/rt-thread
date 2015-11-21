/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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
#include "registers/regsgpc.h"
#include "registers/regsiomuxc.h"
#include "registers/regsuart.h"
#include "registers/regsssi.h"
#include "registers/regsepit.h"
#include "registers/regsgpt.h"
#include "registers/regsi2c.h"
#include "registers/regsspdif.h"
#include "registers/regsspba.h"
#include "registers/regssdmaarm.h"
#include "registers/regsecspi.h"

#if defined(CHIP_MX6DQ)
#include "registers/regssata.h"
#endif

#if !defined(CHIP_MX6SL)
#include "registers/regsgpmi.h"
#include "registers/regsesai.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

const uint32_t PLL1_OUTPUT = 792000000;
const uint32_t PLL2_OUTPUT[] = { 528000000, 396000000, 352000000, 198000000, 594000000 };
const uint32_t PLL3_OUTPUT[] = { 480000000, 720000000, 540000000, 508235294, 454736842 };
const uint32_t PLL4_OUTPUT = 650000000;
const uint32_t PLL5_OUTPUT = 650000000;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void ccm_init(void)
{
    // ETHNET
    HW_CCM_ANALOG_PLL_ENET_CLR(BM_CCM_ANALOG_PLL_ENET_POWERDOWN);
    HW_CCM_ANALOG_PLL_ENET_SET(BM_CCM_ANALOG_PLL_ENET_ENABLE);
    HW_CCM_ANALOG_PLL_ENET_CLR(BM_CCM_ANALOG_PLL_ENET_BYPASS);
#if !defined (CHIP_MX6SL)
    HW_CCM_ANALOG_PLL_ENET.B.DIV_SELECT = 0x3;
#else
	HW_CCM_ANALOG_PLL_ENET.B.DIV_SELECT = 0x1;
#endif

    // Ungate clocks that are not enabled in a driver - need to be updated 
    HW_CCM_CCGR0_WR(0xffffffff);
    HW_CCM_CCGR1_WR(0xFFCF0FFF);    // EPIT, ESAI, GPT enabled by driver
    HW_CCM_CCGR2_WR(0xFFFFF03F);    // I2C enabled by driver
    HW_CCM_CCGR3_WR(0xffffffff);
    HW_CCM_CCGR4_WR(0x00FFFF03);    // GPMI, Perfmon enabled by driver
    HW_CCM_CCGR5_WR(0xF0FFFFCF);    // UART, SATA enabled by driver
    HW_CCM_CCGR6_WR(0xffffffff);

    /*
     * Keep default settings at reset.
     * pre_periph_clk_sel is by default at 0, so the selected output
     * of PLL2 is the main output at 528MHz.
     * => by default, ahb_podf divides by 4 => AHB_CLK@132MHz.
     * => by default, ipg_podf divides by 2 => IPG_CLK@66MHz.
     */
    HW_CCM_CBCDR.U = BF_CCM_CBCDR_AHB_PODF(3)
#if !defined (CHIP_MX6SL)
        | BF_CCM_CBCDR_AXI_PODF(1)
#endif
        | BF_CCM_CBCDR_IPG_PODF(1);

    /*
     * UART clock tree: PLL3 (480MHz) div-by-6: 80MHz
     * 80MHz uart_clk_podf (div-by-1) = 80MHz (UART module clock input)
     */
//    writel(readl(CCM_CSCDR1) & 0x0000003F, CCM_CSCDR1);
//     HW_CCM_CSCDR1.U = 

    /* Mask all interrupt sources that could wake up the processor when in
       a low power mode. A source is individually masked/unmasked when the 
       interrupt is enabled/disabled by the GIC/interrupt driver. */
    HW_GPC_IMR1_WR(0xFFFFFFFF);
    HW_GPC_IMR2_WR(0xFFFFFFFF);
    HW_GPC_IMR3_WR(0xFFFFFFFF);
    HW_GPC_IMR4_WR(0xFFFFFFFF);
}

uint32_t get_main_clock(main_clocks_t clock)
{
    uint32_t ret_val = 0;
    uint32_t pre_periph_clk_sel = HW_CCM_CBCMR.B.PRE_PERIPH_CLK_SEL;

    switch (clock) {
    case CPU_CLK:
        ret_val = PLL1_OUTPUT;
        break;
#if !defined (CHIP_MX6SL)
    case AXI_CLK:
        ret_val = PLL2_OUTPUT[pre_periph_clk_sel] / (HW_CCM_CBCDR.B.AXI_PODF + 1);
        break;
    case MMDC_CH0_AXI_CLK:
        ret_val = PLL2_OUTPUT[pre_periph_clk_sel] / (HW_CCM_CBCDR.B.MMDC_CH0_AXI_PODF + 1);
        break;
#endif
    case AHB_CLK:
        ret_val = PLL2_OUTPUT[pre_periph_clk_sel] / (HW_CCM_CBCDR.B.AHB_PODF + 1);
        break;
    case IPG_CLK:
        ret_val =
            PLL2_OUTPUT[pre_periph_clk_sel] / (HW_CCM_CBCDR.B.AHB_PODF +
                                               1) / (HW_CCM_CBCDR.B.IPG_PODF + 1);
        break;
    case IPG_PER_CLK:
        ret_val =
            PLL2_OUTPUT[pre_periph_clk_sel] / (HW_CCM_CBCDR.B.AHB_PODF +
                                               1) / (HW_CCM_CBCDR.B.IPG_PODF +
                                                     1) / (HW_CCM_CSCMR1.B.PERCLK_PODF + 1);
        break;
#if !defined (CHIP_MX6SL)
    case MMDC_CH1_AXI_CLK:
        ret_val = PLL2_OUTPUT[pre_periph_clk_sel] / (HW_CCM_CBCDR.B.MMDC_CH1_AXI_PODF + 1);
        break;
#endif
    default:
        break;
    }

    return ret_val;
}

uint32_t get_peri_clock(peri_clocks_t clock)
{
    uint32_t ret_val = 0;

    switch (clock)
    {
        case UART1_MODULE_CLK:
        case UART2_MODULE_CLK:
        case UART3_MODULE_CLK:
        case UART4_MODULE_CLK:
            // UART source clock is a fixed PLL3 / 6
            ret_val = PLL3_OUTPUT[0] / 6 / (HW_CCM_CSCDR1.B.UART_CLK_PODF + 1);
            break;
        
        // eCSPI clock:
        //     PLL3(480) -> /8 -> CSCDR2[ECSPI_CLK_PODF]
        case SPI_CLK:
            ret_val = PLL3_OUTPUT[0] / 8 / (HW_CCM_CSCDR2.B.ECSPI_CLK_PODF + 1);
            break;
        
#if !defined (CHIP_MX6SL)
        case RAWNAND_CLK:
            ret_val =
                PLL3_OUTPUT[0] / (HW_CCM_CS2CDR.B.ENFC_CLK_PRED + 1) / (HW_CCM_CS2CDR.B.ENFC_CLK_PODF +
                                                                        1);
            break;
            
        case CAN_CLK:
            // For i.mx6dq/sdl CAN source clock is a fixed PLL3 / 8
        ret_val = PLL3_OUTPUT[0] / 8 / (HW_CCM_CSCMR2.B.CAN_CLK_PODF + 1);
        break;
#endif

        default:
            break;
    }

    return ret_val;
}

/*!
 * Set/unset clock gating for a peripheral.
 * @param   ccm_ccgrx Address of the clock gating register: CCM_CCGR1,...
 * @param   cgx_offset Offset of the clock gating field: CG(x).
 * @param   gating_mode Clock gating mode: CLOCK_ON or CLOCK_OFF.
 */
void ccm_ccgr_config(uint32_t ccm_ccgrx, uint32_t cgx_offset, uint32_t gating_mode)
{
    if (gating_mode == CLOCK_ON)
    {
        *(volatile uint32_t *)(ccm_ccgrx) |= cgx_offset;
    }
    else
    {
        *(volatile uint32_t *)(ccm_ccgrx) &= ~cgx_offset;
    }
}

void clock_gating_config(uint32_t base_address, uint32_t gating_mode)
{
    uint32_t ccm_ccgrx = 0;
    uint32_t cgx_offset = 0;

    switch (base_address)
    {
        case REGS_UART1_BASE:
        case REGS_UART2_BASE:
        case REGS_UART3_BASE:
        case REGS_UART4_BASE:
        case REGS_UART5_BASE:
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(13) | CG(12);
            break;
        case REGS_SSI3_BASE:
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(11);
            break;
        case REGS_SSI2_BASE:
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(10);
            break;
        case REGS_SSI1_BASE:
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(9);
            break;
        case REGS_SPDIF_BASE:
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(7);
            break;
        case REGS_SPBA_BASE:
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(6);
            break;
        case REGS_SDMAARM_BASE:
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(3);
            break;
#if CHIP_MX6DQ
        case REGS_SATA_BASE:
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(2);
            break;
#endif // CHIP_MX6DQ
        case REGS_EPIT1_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(6);
            break;
        case REGS_EPIT2_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(7);
            break;
        case REGS_GPT_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(10);
            break;
        case REGS_I2C1_BASE:
            ccm_ccgrx = HW_CCM_CCGR2_ADDR;
            cgx_offset = CG(3);
            break;
        case REGS_I2C2_BASE:
            ccm_ccgrx = HW_CCM_CCGR2_ADDR;
            cgx_offset = CG(4);
            break;
        case REGS_I2C3_BASE:
            ccm_ccgrx = HW_CCM_CCGR2_ADDR;
            cgx_offset = CG(5);
            break;
        case REGS_ECSPI1_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(0);
            break;        
        case REGS_ECSPI2_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(1);
            break;        
        case REGS_ECSPI3_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(2);
            break;        
        case REGS_ECSPI4_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(3);
            break;        
#if CHIP_MX6DQ
        case REGS_ECSPI5_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(4);
            break;        
#endif // CHIP_MX6DQ
#if !defined (CHIP_MX6SL)
        case REGS_GPMI_BASE:
            ccm_ccgrx = HW_CCM_CCGR4_ADDR;
            cgx_offset = CG(15) | CG(14) | CG(13) | CG(12);
            break;
        case REGS_ESAI_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(8);
            break;
        case CAAM_BASE_ADDR:
            ccm_ccgrx = HW_CCM_CCGR0_ADDR;
            cgx_offset = CG(6) | CG(5) | CG(4);
            break;
#endif // !defined (CHIP_MX6SL)
        default:
            break;
    }

    // apply changes only if a valid address was found 
    if (ccm_ccgrx != 0)
    {
        ccm_ccgr_config(ccm_ccgrx, cgx_offset, gating_mode);
    }
}

void ccm_set_lpm_wakeup_source(uint32_t irq_id, bool doEnable)
{
    uint32_t reg_offset = 0;
    uint32_t bit_offset = 0;
    uint32_t gpc_imr = 0;

    // calculate the offset of the register handling that interrupt ID
    // ID starts at 32, so for instance ID=89 is handled by IMR2 because
    // the integer part of the division is reg_offset = 2
    reg_offset = (irq_id / 32);
    // and the rest of the previous division is used to calculate the bit
    // offset in the register, so for ID=89 this is bit_offset = 25
    bit_offset = irq_id - 32 * reg_offset;

    // get the current value of the corresponding GPC_IMRx register
    gpc_imr = readl(HW_GPC_IMR1_ADDR + (reg_offset - 1) * 4);

    if (doEnable) {
        // clear the corresponding bit to unmask the interrupt source 
        gpc_imr &= ~(1 << bit_offset);
        // write the new mask 
        writel(gpc_imr, HW_GPC_IMR1_ADDR + (reg_offset - 1) * 4);
    } else {
        // set the corresponding bit to mask the interrupt source 
        gpc_imr |= (1 << bit_offset);
        // write the new mask 
        writel(gpc_imr, HW_GPC_IMR1_ADDR + (reg_offset - 1) * 4);
    }
}

void ccm_enter_low_power(lp_modes_t lp_mode)
{
    uint32_t ccm_clpcr = 0;

    // if MMDC channel 1 is not used, the handshake must be masked 
    // set disable core clock in wait - set disable oscillator in stop
    ccm_clpcr = 
#if !defined (CHIP_MX6SL)
        BM_CCM_CLPCR_BYPASS_MMDC_CH1_LPM_HS |
#endif
        BM_CCM_CLPCR_SBYOS | BM_CCM_CLPCR_ARM_CLK_DIS_ON_LPM | lp_mode;

    if (lp_mode == STOP_MODE) {
        // enable peripherals well-biased 
        ccm_clpcr |= BM_CCM_CLPCR_WB_PER_AT_LPM;
    }

    HW_CCM_CLPCR_WR(ccm_clpcr);

    __asm(
             // data synchronization barrier (caches, TLB maintenance, ...) 
             "dsb;"
             // wait for interrupt instruction 
             "wfi;"
             // instruction synchronization barrier (flush the pipe-line) 
             "isb;");

    return;
}


#if !defined (CHIP_MX6SL)
/*!
 * @brief Configure ipu 1 and 2 hsp clk to default 264MHz
 *
 * ipu_hsp_clk is derived from mmdc_ch0 divided by 2.
 */
void ipu_hsp_clk_config(void)
{
    // clk_sel from mmdc_ch0, podf=1
    HW_CCM_CSCDR3_WR(BF_CCM_CSCDR3_IPU1_HSP_CLK_SEL(0)
                     | BF_CCM_CSCDR3_IPU1_HSP_PODF(1)
#if CHIP_MX6DQ
                     | BF_CCM_CSCDR3_IPU2_HSP_CLK_SEL(0)
                     | BF_CCM_CSCDR3_IPU2_HSP_PODF(1)
#endif // CHIP_MX6DQ
        );
}

void gpu_clock_config(void)
{
    HW_CCM_ANALOG_PLL_VIDEO_NUM_WR(0xFF0D6C3);
    HW_CCM_ANALOG_PLL_VIDEO_WR(BF_CCM_ANALOG_PLL_VIDEO_DIV_SELECT(2) |
                               BF_CCM_ANALOG_PLL_VIDEO_ENABLE(1) |
                               BF_CCM_ANALOG_PLL_VIDEO_BYPASS(1));
    while (!HW_CCM_ANALOG_PLL_VIDEO.B.LOCK) ;   //waiting for PLL lock
    BF_CLR(CCM_ANALOG_PLL_VIDEO, BYPASS);

    //ldb_di0_clk select PLL5
    HW_CCM_CS2CDR.B.LDB_DI0_CLK_SEL = 0;    // PLL5

    HW_IOMUXC_GPR3.B.LVDS1_MUX_CTL = 0; // LVDS1 source is IPU1 DI0 port
    HW_IOMUXC_GPR3.B.LVDS0_MUX_CTL = 2; // LVDS0 source is IPU2 DI0 port

    HW_CCM_CHSCCDR.B.IPU1_DI0_CLK_SEL = 3;  // derive clock from ldb_di0_clk
    HW_CCM_CSCMR2_SET(BM_CCM_CSCMR2_LDB_DI0_IPU_DIV | BM_CCM_CSCMR2_LDB_DI1_IPU_DIV);   // ldb_di0 divided by 3.5

#if CHIP_MX6DQ
    HW_CCM_CSCDR2.B.IPU2_DI0_CLK_SEL = 3;   // derive clock from ldb_di0_clk
    HW_CCM_CSCDR2.B.IPU2_DI1_CLK_SEL = 3;   // derive clock from 352M PFD
#endif // CHIP_MX6DQ
}
#endif

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
