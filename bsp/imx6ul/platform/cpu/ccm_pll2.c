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
#include "registers/regsuart.h"
#include "registers/regsepit.h"
#include "registers/regsspba.h"
#include "registers/regssdmaarm.h"
#include "registers/regsgpt.h"
#include "registers/regsi2c.h"
#include "registers/regsecspi.h"
#include "ccm_pll.h"
//#include "hardware.h"
//#include "soc_memory_map.h"
#define HW_ANADIG_REG_CORE		(ANATOP_IPS_BASE_ADDR + 0x140)
#define HW_ANADIG_PLL_SYS_RW  (ANATOP_IPS_BASE_ADDR + 0x000)
#define HW_ANADIG_REG_CORE_V_CORE_VALUE_mv(x)	((((x)-700)/25) << 0)
#define HW_ANADIG_REG_CORE_V_SOC_VALUE_mv(x)	((((x)-700)/25) << 18)
#define HW_ANADIG_REG_CORE_V_CORE_MSK		0x1F
#define HW_ANADIG_REG_CORE_V_SOC_MSK		(0x1F << 18)

uint32_t g_arm_clk = 528000000;

const uint32_t PLL2_OUTPUT[] = { 528000000, 396000000, 352000000, 198000000 };
const uint32_t PLL3_OUTPUT[] = { 480000000, 720000000, 540000000, 508235294, 454736842 };
const uint32_t PLL4_OUTPUT = 650000000;
const uint32_t PLL5_OUTPUT = 650000000;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void set_soc_core_voltage(unsigned int v_core_mv, unsigned int v_soc_mv)
{
    unsigned int val, val_v_core, val_v_soc;

    val = reg32_read(HW_ANADIG_REG_CORE);
    val &= ~HW_ANADIG_REG_CORE_V_CORE_MSK;
    val &= ~HW_ANADIG_REG_CORE_V_SOC_MSK;

    val_v_core = HW_ANADIG_REG_CORE_V_CORE_VALUE_mv(v_core_mv);
    val_v_soc = HW_ANADIG_REG_CORE_V_SOC_VALUE_mv(v_soc_mv);

    val |= val_v_core | val_v_soc;
    reg32_write(HW_ANADIG_REG_CORE, val);
}

void setup_clk(void)
{
		uint32_t div_select;
		uint32_t temp;	
		uint32_t arm_clk = g_arm_clk/1000000;
	  
		switch(arm_clk)
		{
			case 400:
				div_select = 33;
				set_soc_core_voltage(1150, 1175);
				return;
			case 528:
				div_select = 44;
				set_soc_core_voltage(1250, 1250);
				break;
			case 756:
				div_select = 63;
    		set_soc_core_voltage(1250, 1250);
    		printf("ARM Clock set to 756MHz\r\n");
    		break;
			default:
				return;
    }      	    			   	    			
    	
    // first, make sure ARM_PODF is clear
    HW_CCM_CACRR_WR(0);
    // write the div_select value into HW_ANADIG_PLL_SYS_RW
    // this will re-program the PLL to the new freq

    temp = readl(HW_ANADIG_PLL_SYS_RW);
    temp |= 0x10000;// set BYBASS 
    writel(temp, HW_ANADIG_PLL_SYS_RW);

    temp = readl(HW_ANADIG_PLL_SYS_RW);
    temp &= ~(0x0000007F);
    temp |= div_select;  // Update div 
    writel(temp, HW_ANADIG_PLL_SYS_RW);

		/* Wait for PLL to lock */
		while(!(readl(HW_ANADIG_PLL_SYS_RW) & 0x80000000));

		/*disable BYPASS*/
    temp = readl(HW_ANADIG_PLL_SYS_RW);
		temp &= ~0x10000;
    writel(temp, HW_ANADIG_PLL_SYS_RW);		
}

void ccm_init(void)
{
    HW_CCM_CCGR0_WR(0xffffffff);
    HW_CCM_CCGR1_WR(0xffffffff);    // EPIT, ESAI, GPT enabled by driver
    HW_CCM_CCGR2_WR(0xffffffff);    // I2C enabled by driver
    HW_CCM_CCGR3_WR(0xffffffff);
    HW_CCM_CCGR4_WR(0xffffffff);    // GPMI, Perfmon enabled by driver
    HW_CCM_CCGR5_WR(0xffffffff);    // UART, SATA enabled by driver
    HW_CCM_CCGR6_WR(0xffffffff);

    /*
     * Keep default settings at reset.
     * pre_periph_clk_sel is by default at 0, so the selected output
     * of PLL2 is the main output at 528MHz.
     * => by default, ahb_podf divides by 4 => AHB_CLK@132MHz.
     * => by default, ipg_podf divides by 2 => IPG_CLK@66MHz.
     */    
    HW_CCM_CBCDR.U = BF_CCM_CBCDR_AHB_PODF(3)
        | BF_CCM_CBCDR_AXI_PODF(1)
        | BF_CCM_CBCDR_IPG_PODF(1);
    
    setup_clk();

    /* Power up 480MHz PLL */
    reg32_write_mask(HW_CCM_ANALOG_PLL_USB1_ADDR, 0x00001000, 0x00001000);

    /* Enable 480MHz PLL */
    reg32_write_mask(HW_CCM_ANALOG_PLL_USB1_ADDR, 0x00002000, 0x00002000);
    
    reg32_write_mask(HW_CCM_CSCDR1_ADDR, 0x00000000, 0x0000003F);
}

uint32_t get_main_clock(main_clocks_t clock)
{
    uint32_t ret_val = 0;
    uint32_t pre_periph_clk_sel = HW_CCM_CBCMR.B.PRE_PERIPH_CLK_SEL;

    switch (clock) {
    case CPU_CLK:
        ret_val = g_arm_clk;
        break;
    case AXI_CLK:
        ret_val = PLL2_OUTPUT[pre_periph_clk_sel] / (HW_CCM_CBCDR.B.AXI_PODF + 1);
        break;
    case MMDC_CH0_AXI_CLK:
        ret_val = PLL2_OUTPUT[pre_periph_clk_sel] / (HW_CCM_CBCDR.B.MMDC_CH0_AXI_PODF + 1);
        break;
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
       	case UART5_MODULE_CLK:
     		case UART6_MODULE_CLK:
   			case UART7_MODULE_CLK:
   			case UART8_MODULE_CLK:   				
            // UART source clock is a fixed PLL3 / 6
            ret_val = PLL3_OUTPUT[0] / 6 / (HW_CCM_CSCDR1.B.UART_CLK_PODF + 1);
            break;
        case SPI_CLK:
            ret_val = PLL3_OUTPUT[0] / 8 / (HW_CCM_CSCDR2.B.ECSPI_CLK_PODF + 1);
            break;
        case RAWNAND_CLK:
            ret_val =
                PLL3_OUTPUT[0] / (HW_CCM_CS2CDR.B.ENFC_CLK_PRED + 1) / (HW_CCM_CS2CDR.B.ENFC_CLK_PODF +
                                                                        1);
            break;
        case CAN_CLK:
            // For i.mx6dq/sdl CAN source clock is a fixed PLL3 / 8
        	ret_val = PLL3_OUTPUT[0] / 8 / (HW_CCM_CSCMR2.B.CAN_CLK_PODF + 1);
        	break;
        default:
            break;
    }

    return ret_val;
}

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
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(12);
            break;         	
        case REGS_UART2_BASE:
            ccm_ccgrx = HW_CCM_CCGR0_ADDR;
            cgx_offset = CG(14);
            break;        	
        case REGS_UART3_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(5);
            break;           	
        case REGS_UART4_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(12);
            break;         	
        case REGS_UART5_BASE:
            ccm_ccgrx = HW_CCM_CCGR3_ADDR;
            cgx_offset = CG(1);
            break;         	
        case REGS_UART6_BASE:
            ccm_ccgrx = HW_CCM_CCGR3_ADDR;
            cgx_offset = CG(3);
            break;          	
        case REGS_UART7_BASE:
            ccm_ccgrx = HW_CCM_CCGR5_ADDR;
            cgx_offset = CG(13);
            break;          	
        case REGS_UART8_BASE:
            ccm_ccgrx = HW_CCM_CCGR6_ADDR;
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
        case REGS_EPIT1_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(6);
            break;
        case REGS_EPIT2_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(7);
            break;
        case REGS_GPT1_BASE:
        case REGS_GPT2_BASE:
            ccm_ccgrx = HW_CCM_CCGR1_ADDR;
            cgx_offset = CG(10)|CG(11);
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
        default:
            break;
    }

    // apply changes only if a valid address was found 
    if (ccm_ccgrx != 0)
    {
        ccm_ccgr_config(ccm_ccgrx, cgx_offset, gating_mode);
    }
}
////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
