/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/usb/gd_usb.c
**
** \version     $Id$
**
** \brief       1
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2016 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#include <stdio.h>
#include <string.h>

#include "gtypes.h"
#include "gh_usb.h"
#include "gh_usb_phy.h"
#include "gh_hw_cfg.h"
#include "gh_debug_rct.h"
#include "gh_dma.h"
#include "gd_timer.h"
#include "gd_gpio.h"

#include "gd_usb.h"

#define USB_AHB_W(addr, value)  *(volatile unsigned long*)(addr) = (value)
#define USB_AHB_R(addr, value)  value = *(volatile unsigned long*)(addr)

#define CLK_REG_W 	USB_AHB_W
#define CLK_REG_R 	USB_AHB_R
//*****************************************************************************
//*****************************************************************************
//** Clock Switch Related Functions
//*****************************************************************************
//*****************************************************************************
/*
pheri_cken (w/r) - 0xA0170288
Bit	Field Name	Default
Value	Description
[31:7]	reserved	R	?¨¤?¨º¡§¡é?
[6]	Ssi2_cken	0x1	Ssi2 ????¡§o?¨¤?¡§?¡§o1?¡§1
[5]	ssi_cken	0x1	ssi ????¡§o?¨¤?¡§?¡§o1?¡§1
[4]	Sd2_cken	0x1	Sd2 ????¡§o?¨¤?¡§?¡§o1?¡§1
[3]	sd_cken	0x1	sd ????¡§o?¨¤?¡§?¡§o1?¡§1
[2]	reserved	0x1	?¨¤?¨º¡§¡é?
[1]	eth_cken	0x1	eth ????¡§o?¨¤?¡§?¡§o1?¡§1
[0]	usb_cken	0x1	usb ????¡§o?¨¤?¡§?¡§o1?¡§1
*/
#define REG_ADDR_CLK_POWER_SW 0xA0170288
#define CLK_BIT_USB_EN (1 << 0)
void gd_clk_disable_usb()
{
	U32 val_clk = 0;
	
	CLK_REG_R(REG_ADDR_CLK_POWER_SW, val_clk);
	
	val_clk &= ~CLK_BIT_USB_EN;
	
	CLK_REG_W(REG_ADDR_CLK_POWER_SW, val_clk);
}

void gd_clk_enable_usb()
{
	U32 val_clk = 0;
	
	CLK_REG_R(REG_ADDR_CLK_POWER_SW, val_clk);
	
	val_clk |= CLK_BIT_USB_EN;
	
	CLK_REG_W(REG_ADDR_CLK_POWER_SW, val_clk);
}

void gd_clk_disable_all()
{
	U32 val_clk = 0;
		
	CLK_REG_W(REG_ADDR_CLK_POWER_SW, val_clk);
}


#define GPIOx_ADDR_USB_PHY_RST(x)  (0xa0009100+0x4*x)  // USB_PHY_RST by GPIO[0] in GK7101S or GPIO[42] in GK7102C*/
GERR GD_USB_PHY_FPGA_Init(void)
{
#ifndef GK710X
    GH_PLL_set_USB_GRST_en(1);
    GD_TIMER_Delay(20);
    GH_PLL_set_USB_GRST_en(0);
    GD_TIMER_Delay(20);
    GH_PLL_set_USB_GRST_en(1);
#endif
	printf("[GK]%s()\n", __FUNCTION__);

    *((unsigned volatile int*)(GPIOx_ADDR_USB_PHY_RST(12)))=0x00000001;   // Reset External USB PHY on the FPGA Platform by GPIO[0] in GK7101S or GPIO[42] in GK7102C
    GD_TIMER_Delay(1);
    *((unsigned volatile int*)(GPIOx_ADDR_USB_PHY_RST(12)))=0x00000000;
	GD_TIMER_Delay(1);
	return GD_OK;
}

GERR GD_USB_PHY_Init(U8 GpioNumber)
{
    U32 tmp_data;
    U32 cmp_pass1;
    GD_HANDLE Gpiohandle;

    printf("UTMI2 Wait reset release.\n");
    GD_TIMER_Delay(100);
    printf("UTMI2 Begin initial sequence ...\n");

#ifdef GK710X
    GD_GPIO_Open(GpioNumber, GD_GPIO_TYPE_OUTPUT_1, NULL, &Gpiohandle);
    GD_GPIO_Write(Gpiohandle, 1);
#else
    GD_GPIO_Open(GpioNumber, GD_GPIO_TYPE_OUTPUT_1, NULL, &Gpiohandle);
    GD_GPIO_Write(Gpiohandle, 0);
#endif

    //USB_AHB_R(0x70170050, value);
    //USB_AHB_W(0x70170050, value | 0x02);
#ifndef GK710X
    //PHY reset
    GH_PLL_set_USB_GRST_en(1);
    GD_TIMER_Delay(20);
    GH_PLL_set_USB_GRST_en(0);
    GD_TIMER_Delay(20);
    GH_PLL_set_USB_GRST_en(1);
#endif

    // init phy
    //init UTMI
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x04<<2), 0x0000040f);
    // bit<7>: Power down UTMI port-0 bandgap current
    /*GH_USB_PHY_set_UTMI_REG_04_ck214_syn_en(1);
    GH_USB_PHY_set_UTMI_REG_04_utmi_clk120_en(1);

    GH_USB_PHY_set_UTMI_REG_04_clktest_en(0);
    GH_USB_PHY_set_UTMI_REG_04_clk_extra_0_en(0);

    GH_USB_PHY_set_UTMI_REG_04_clk_extra_1_en(0);
    GH_USB_PHY_set_UTMI_REG_04_xtal12_en(0);
    GH_USB_PHY_set_UTMI_REG_04_clk_ctl_override(1);
    GH_USB_PHY_set_UTMI_REG_04_force_pll_on(0);

    GH_USB_PHY_set_UTMI_REG_04_ck214_syn_en(0);
    GH_USB_PHY_set_UTMI_REG_04_clk_274_en(0);
    GH_USB_PHY_set_UTMI_REG_04_hs_rx_roboust_en(0);*/

    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x10<<2), 0x00008051);
    // PLL_TEST[15]: Bypass 480MHz clock divider
    // PLL_TEST[7:4]: 5'b0101_0 for 1.0x
    // PLL_TEST[0]: 1: synthesizer clock, 2'b11, 0: XIN_C
    /*GH_USB_PHY_set_UTMI_REG_10_input_clock(1);
    GH_USB_PHY_set_UTMI_REG_10_divider_selection(0x00);
    GH_USB_PHY_set_UTMI_REG_10_divider_control(0xA);

    GH_USB_PHY_set_UTMI_REG_10_clock_outputs_source(0x00);
    GH_USB_PHY_set_UTMI_REG_10_clock_outputs_ratio(0x00);
    GH_USB_PHY_set_UTMI_REG_10_digital_output(0x00);
    GH_USB_PHY_set_UTMI_REG_10_transmitter(0x02);*/

    //USB_AHB_W(REG_UTMI_BASE+(0x11<<2), 0x00002088);
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x11<<2), 0x00005080);
    // PLL_TEST[30:28]: 3'b101 for IBIAS current select
    // PLL_TEST[23] CLK480 to digital output source selection
    // PLL_TEST[20] reset pll
    /*GH_USB_PHY_set_UTMI_REG_11_ENDISC(0x00);
    GH_USB_PHY_set_UTMI_REG_11_EXTDISC(0x00);
    GH_USB_PHY_set_UTMI_REG_11_ENLOCKZ(0x00);
    GH_USB_PHY_set_UTMI_REG_11_ENAUTO(0x00);

    GH_USB_PHY_set_UTMI_REG_11_ENDCC(0x00);
    GH_USB_PHY_set_UTMI_REG_11_TVCO(0x00);
    GH_USB_PHY_set_UTMI_REG_11_output_source(0x01);

    GH_USB_PHY_set_UTMI_REG_11_ENINV(0x00);
    GH_USB_PHY_set_UTMI_REG_11_ENINVENTMUX(0x00);
    GH_USB_PHY_set_UTMI_REG_11_input_clock(0x00);*/
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x11<<2), 0x00005090);
    //GH_USB_PHY_set_UTMI_REG_11_ENDCC(0x01);

    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x00<<2), 0x00006BC3);
    // Turn on reference voltage and regulator
    // reg_pdn: bit<15>, bit <2> ref_pdn
    /*GH_USB_PHY_set_UTMI0_pdn_override(0x01);
    GH_USB_PHY_set_UTMI0_term_override(0x01);
    GH_USB_PHY_set_UTMI0_ref_pdn(0x00);
    GH_USB_PHY_set_UTMI0_dp_puen(0x00);

    GH_USB_PHY_set_UTMI0_dm_puen(0x00);
    GH_USB_PHY_set_UTMI0_r_pumode(0x00);
    GH_USB_PHY_set_UTMI0_r_dp_pden(0x01);
    GH_USB_PHY_set_UTMI0_r_dm_pden(0x01);

    GH_USB_PHY_set_UTMI0_hs_dm_pdn(0x01);
    GH_USB_PHY_set_UTMI0_pll_pdn(0x01);
    GH_USB_PHY_set_UTMI0_hs_ted_pdn(0x00);
    GH_USB_PHY_set_UTMI0_hs_preamp_pdn(0x01);

    GH_USB_PHY_set_UTMI0_f1_xcvf_pdn(0x00);
    GH_USB_PHY_set_UTMI0_vbusdet_pdn(0x01);
    GH_USB_PHY_set_UTMI0_iref_pdn(0x01);
    GH_USB_PHY_set_UTMI0_pdn(0x00);*/
    //USB_AHB_W(REG_UTMI_BASE+(0x0A<<2), 0x0000140B);
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x0A<<2), 0x00003403);

    GD_TIMER_Delay(20);
    // Delay(1ms) wait for regulator stable

    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x00<<2), 0x000069C3);
    // Turn on UPLL, reg_pdn: bit<9>
    //GH_USB_PHY_set_UTMI0_pll_pdn(0x00);
    GD_TIMER_Delay(10);

    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x11<<2), 0x00005080);
    // PLL_TEST[20] reset pll
    GD_TIMER_Delay(20);
    // Delay(2ms) wait for PLL stable
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x00<<2), 0x00000001);
    // Turn all (including hs_current) use override mode
    //GH_USB_PHY_set_UTMI0(0x00000001);
    GD_TIMER_Delay(1000);
    // Delay(1ms) wait for analog circuit stabl
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x1E<<2), 0x00000001);
    GD_TIMER_Delay(1000);
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x1E<<2), 0x00000000);
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x03<<2), 0x00000023);
    GD_TIMER_Delay(10);
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x03<<2), 0x00000020);
    // host
    // USB_AHB_W(REG_UTMI_BASE+(0x0A<<2), 0x00000003);
    // device
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x0A<<2), 0x0000000b);
    GD_TIMER_Delay(1000);
    // end init

    //reset USB controller
#ifdef GK710X
    USB_AHB_R(0x70170088, tmp_data);
    tmp_data |= 0x20000000;//0x6CC36011
    USB_AHB_W(0x70170088, tmp_data);
    GD_TIMER_Delay(10);
    tmp_data &= ~0x20000000;//0x4CC36011
    USB_AHB_W(0x70170088, 0x00000003);
    USB_AHB_W(0x70170088, tmp_data);
    GD_TIMER_Delay(10);
#else
    USB_AHB_R(0xa0170088, tmp_data);                 // usb_ctrl_soft_reset,USB controller ¡§¡§¡§a?t?????: rw
    tmp_data |= 0x20000000;//0x6CC36011                 // USB ???????¡§¡§¡§a?t??????¨º?|¨¬¡§a|¨¬????????
    USB_AHB_W(0xa0170088, tmp_data);
    GD_TIMER_Delay(10);
    tmp_data &= ~0x20000000;//0x4CC36011
    USB_AHB_W(0xa0170088, 0x00000003);
    USB_AHB_W(0xa0170088, tmp_data);
    GD_TIMER_Delay(10);
#endif
    //dev_connect;
    ///////////////////////////////////////////////////////////////////////////////
    //port-0 loop back check
    /*USB_AHB_W(REG_UTMI_BASE+(0x03<<2), 0x00000043);
    GH_USB_PHY_set_UTMI_REG_03_rx_swreset(0x01);
    GH_USB_PHY_set_UTMI_REG_03_utmi_tx_sw_reset(0x01);
    GH_USB_PHY_set_UTMI_REG_03_tx_force_hs_current_enable(0x00);
    GH_USB_PHY_set_UTMI_REG_03_tx_fl_early_4(0x00);

    GH_USB_PHY_set_UTMI_REG_03_tx_fl_latency_delay_1(0x00);
    GH_USB_PHY_set_UTMI_REG_03_hs_stage_select(0x02);
    GH_USB_PHY_set_UTMI_REG_03_otg_dual_role(0x00);

    GH_USB_PHY_set_UTMI_REG_03_tx_reset_fsm(0x00);
    GH_USB_PHY_set_UTMI_REG_03_cdr_mode_sel(0x00);
    GH_USB_PHY_set_UTMI_REG_03_tx_reserved(0x00);
    GH_USB_PHY_set_UTMI_REG_03_vbusdet_test(0x00);

    USB_AHB_W(REG_UTMI_BASE+(0x03<<2), 0x00000040);
    GH_USB_PHY_set_UTMI_REG_03_rx_swreset(0x00);
    GH_USB_PHY_set_UTMI_REG_03_utmi_tx_sw_reset(0x00);

    USB_AHB_W(REG_UTMI_BASE+(0x00<<2), 0x00000001);
    GH_USB_PHY_set_UTMI0(0x00000001);

    USB_AHB_W(REG_UTMI_BASE+(0x0A<<2), 0x00000600);
    // bit <9> mac_mode_ovd, bit <8> termsel, bit <7:6> xcvrsel, bit <5:4> opmode
    GH_USB_PHY_set_UTMI_REG_0A_vbusvalid(0x00);
    GH_USB_PHY_set_UTMI_REG_0A_avalid(0x00);
    GH_USB_PHY_set_UTMI_REG_0A_sessend(0x00);
    GH_USB_PHY_set_UTMI_REG_0A_iddig(0x00);

    GH_USB_PHY_set_UTMI_REG_0A_opmode(0x00);
    GH_USB_PHY_set_UTMI_REG_0A_xcvrsel(0x01);//0:high 1:full 2: low

    GH_USB_PHY_set_UTMI_REG_0A_termsel(0x01);//0:high 1:full
    GH_USB_PHY_set_UTMI_REG_0A_macmode_ovd(0x01);
    GH_USB_PHY_set_UTMI_REG_0A_suspendm(0x01);
    GH_USB_PHY_set_UTMI_REG_0A_usb_bond_ovd(0x00);

    GH_USB_PHY_set_UTMI_REG_0A_usb_bond_set(0x00);
    GH_USB_PHY_set_UTMI_REG_0A_host_chirp_det(0x00);
    GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask(0x00);
    GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask_method(0x00);

    USB_AHB_W(REG_UTMI_BASE+(0x08<<2), 0x00000078);
    // bit <7> hs_se0, bit<5> force_tx_non_busy, bit<4> force_rx_non_busy,
    // bit <3:0> debug bus select
    GH_USB_PHY_set_UTMI_REG_08_test_bus_select(0x08);

    GH_USB_PHY_set_UTMI_REG_08_force_rx_nonbusy(0x01);
    GH_USB_PHY_set_UTMI_REG_08_force_tx_nonbusy(0x01);
    GH_USB_PHY_set_UTMI_REG_08_utmi_int_clr(0x01);
    GH_USB_PHY_set_UTMI_REG_08_se0_set(0x00);

    GH_USB_PHY_set_UTMI_REG_08_tx_data(0x00);
    GH_USB_PHY_set_UTMI_REG_08_tx_en(0x00);
    GH_USB_PHY_set_UTMI_REG_08_tx_se0(0x00);
    GH_USB_PHY_set_UTMI_REG_08_tx_override(0x00);

    GH_USB_PHY_set_UTMI_REG_08_power_good_rst(0x00);
    GH_USB_PHY_set_UTMI_REG_08_phy_mode_enable(0x00);
    GH_USB_PHY_set_UTMI_REG_08_error_flag_clr(0x00);
    GH_USB_PHY_set_UTMI_REG_08_hd_tx_override(0x00);*/


#if 0
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x1A<<2), 0x00000000);    // set data pattern: 0000
    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x19<<2), 0x000001fe);    // bit <8> set tx_go, bit <10> fix data mode
    // TV.riu_read(REG_UTMI_BASE1+'h18);           //
    // poll_1_clear(REG_UTMI_BASE1+'h18, 'h8000);
    USB_AHB_R(REG_USB_PHY_UTMI_REG_00+(0x18<<2),  tmp_data); // bit <8> set tx_go, bit <10> fix data mode

    GD_TIMER_Delay(100);     // Delay(1ms) wait for analog circuit stabl

    if((tmp_data&0x0000C000)==0x00008000)
        cmp_pass1 = 1;
    else
        cmp_pass1 = 0;

    USB_AHB_W(REG_USB_PHY_UTMI_REG_00+(0x19<<2), 0x000000fe);    // clear tx_go (remember keep bit <10> for port1 fix data mode)
    if(cmp_pass1)
        printf("\n==========OK, USB TEST PASS.==========\n");
    else
        printf("\n=========Error,USB TEST FIAL.==========\n");
    //$finish();
#endif
    return GD_OK;
}


//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
GERR GD_USB_Init(void)
{
    printf("[GK]%s()\n", __FUNCTION__);
    //usb disconnect
    GH_USB_set_Power_W_PERI(0x00);

    //enable interrupt
    GH_USB_set_IntrTxE(0xFFFF);
    GH_USB_set_IntrRxE(0xFFFF);
    GH_USB_set_IntrUSBE(0xFF);

    //usb connect
#ifdef HS_MSC_TEST
    {
        GH_USB_set_Power_W_PERI(0x60);
    }
#endif
#ifdef FS_MSC_TEST
    {
        GH_USB_set_Power_W_PERI(0x40);
    }
#endif

    GH_USB_set_DevCtl_W(0x01);
    return GD_OK;
}


GERR GD_USB_Set_EP_Index(U8 idx)
{
//    GM_Printf("[GK]%s():EP:%d\n", __FUNCTION__, idx);
    GH_USB_set_Index(idx);

    return GD_OK;
}


//*REG_USB_CSR0L = 0x48;
GERR GD_USB_Set_CSR0L(U8 data)
{
    GH_USB_set_CSR0L_W_PERI(data);

    return GD_OK;
}

//regtmpdata = *REG_USB_CSR0L;
GERR GD_USB_Get_CSR0L(U8 *pdata)
{
    if(pdata != NULL)
        *pdata = GH_USB_get_CSR0L_R_PERI();
    else
        return GD_ERR_BAD_PARAMETER;

    return GD_OK;

    return GD_OK;
}


// *REG_USB_TXCSRH = 0x24;
GERR GD_USB_Set_TXCSRH(U8 data)
{
    GH_USB_set_TXCSRH_W_PERI(data);

    return GD_OK;
}

GERR GD_USB_Set_RXCSRH(U8 data)
{
    GH_USB_set_RXCSRH_W_PERI(data);

    return GD_OK;
}


GERR GD_USB_Set_RXCSRL(U8 data)
{
    GH_USB_set_RXCSRL_W_PERI(data);

    return GD_OK;
}


GERR GD_USB_Get_RXCSRL(U8 *data)
{
   *data = GH_USB_get_RXCSRL_R_PERI();

    return GD_OK;
}


// *REG_USB_FADDR = (UC8)wValue;
GERR GD_USB_Set_FADDR(U8 data)
{
    GH_USB_set_FAddr(data);

    return GD_OK;
}


GERR GD_USB_Get_POWER(U8 *data)
{
    *data = GH_USB_get_Power_R_HOST();

    return GD_OK;
}

GERR GD_USB_Read_EP_FIFOx(U8 aryData[], U32 reqBytesNum, U8 epIdx)
{
    U32 i = 0;

    for(i = 0; i < reqBytesNum; i++)
    {
        aryData[i] = GH_USB_get_FIFOs(epIdx);   // U8
    }

    return GD_OK;
}


// Func: cntType:0,COUNT0; 1: RxCOUNT
GERR GD_USB_Read_Rx_Count(U8 cntType, U32 *data)
{
    if(data == NULL)
        return GD_ERR_BAD_PARAMETER;

    // COUNT0
    if(cntType == 0)
    {
        *data = GH_USB_get_Count0();
    }
    else  // RxCOUNT
    {
        *data = GH_USB_get_RxCount();
    }

    return GD_OK;
}

U8 g_tx_ep = 1;
U8 g_rx_ep = 2;
void GD_USB_Init_msc_pipe(void)
{
    //enable interrupt
    GH_USB_set_Index(g_tx_ep);       //select EPx

    GH_USB_set_TXCSRL_W_PERI(0x40);  //clear data toggle  // reset the endpoint data toggle to 0
    GH_USB_set_TXCSRL_W_PERI(0x00);

#ifdef HS_MSC_TEST
    GH_USB_set_TxMaxP(0x0200);
#endif
#ifdef FS_MSC_TEST
    GH_USB_set_TxMaxP(0x0040);
#endif

    GH_USB_set_TXCSRH_W_PERI(0x24);  //clear data toggle  // enable the endpoint direction as TX, bulk or irq transfer; FrcDataTog, clear the data packet from FIFO.

    GH_USB_set_Index(g_rx_ep);   //select EPx
    //GH_USB_set_Index(0x02);    //select EP2
    GH_USB_set_RXCSRL_W_PERI(0x80);  //clear data toggle  // reset the endpoint data toggle to 0.
    GH_USB_set_RXCSRL_W_PERI(0x00);

#ifdef HS_MSC_TEST
    GH_USB_set_RxMaxP(0x0200);
#endif
#ifdef FS_MSC_TEST
    GH_USB_set_RxMaxP(0x0040);
#endif

#ifdef GK710X
    GH_USB_set_RXCSRH_W_PERI(0x00);

#else

    #ifdef USB_DATA_TRAN_MODE_DMA
    GH_USB_set_RXCSRH_W_PERI(0xa8);   // AutoClear & Bulk/Interrupt transfers, enable the DMA request for RX, DMA Request Mode 1
    #endif

    #ifdef USB_DATA_TRAN_MODE_PIO
    GH_USB_set_TXCSRH_W_PERI(0);     //set manual clear
    #endif

#endif // #ifdef GK710X

    GH_USB_set_TXCSRH_W_PERI(0x04);  // FrcDataTog, clear the data packet from FIFO.

}


void  GD_USB_Control_in(const U8 *p, U32 *length,U32 len0_flag)
{
    U32 i,tmp,index;

    printf("[GK]%s()\n", __FUNCTION__);

    index=0;
    while(1)
    {
        if((*length)>=64)
        {
            for(i=0;i<64;i++)
            {
                GH_USB_set_FIFOs(0x00,p[i]);

            }
            *length=*length-64;
            if((*length)==0)
                GH_USB_set_CSR0L_W_PERI(0x0a);   //SET  in buffer enable  // DataEnd & TxPktRdy are set.
            else
                GH_USB_set_CSR0L_W_PERI(0x02);   //SET  in buffer enable  // TxPktRdy is set. data is not end.

            while(GH_USB_get_CSR0L_R_PERI_TxPktRdy());  //  cleared automatically when a data packet has been transmitted.
        }
        else if((*length)!=0)
        {
            for(i=0;i<(*length);i++)
            {
                GH_USB_set_FIFOs(0x00,p[i]);
            }
            GH_USB_set_CSR0L_W_PERI(0x0a);   //SET  in buffer enable  // DataEnd & TxPktRdy are set.
            while(GH_USB_get_CSR0L_R_PERI_TxPktRdy());
            *length=0;

			printf("send short packet, tran end!!!\n");
            break;
        }
        else
        {
            if(len0_flag!=0)
            {
                GH_USB_set_CSR0L_W_PERI(0x0a);   //SET  in buffer enable
                while(GH_USB_get_CSR0L_R_PERI_TxPktRdy());
            }

			printf("send NULL paket, tran end!!!\n");
            break;
        }
    }
}

#ifdef GK710X
void GD_USB_In_tranTx(U8 *p, U32 len)
{
    U32 i;
    GH_USB_set_Index(0x01);    //select EP1
    GH_USB_set_TXCSRH_W_PERI(0x24);

    for(i=0;i<len;i++)
    {
        //*REG_USB_EP1FIFO = p[i];
        GH_USB_set_FIFOs(1, p[i]);
    }

    GH_USB_set_TXCSRL_W_PERI(0x01);
    while(GH_USB_get_TXCSRL_R_PERI_TxPktRdy());
}


GERR GD_USB_DMA_In_TranRx(U32 host_write_addr, U32 host_write_len)
{
    GH_DMA_set_Destination_Address(MUSB_RX_DMA_CHAN, host_write_addr);       //source data addr
    GH_DMA_set_Source_Address(MUSB_RX_DMA_CHAN, REG_USB_ADDR_FIFO_EP(2));    //USB FIFO addr
    //GH_DMA_set_Source_Address3(0, (U32)REG_USB_EP2FIFO);
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, 0x18800000|host_write_len);      //transfer length
    GH_DMA_set_Status(MUSB_RX_DMA_CHAN, 0x0);
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, 0xa8800000|host_write_len);    //start DMA ,byte mode

    GH_USB_set_RXCSRL_W_PERI(0);
    //GH_USB_set_Index(0x02);     //EP2 out
    GH_USB_set_RXCSRH_W_PERI(0xa8);

    while(GH_DMA_get_Control_en(MUSB_RX_DMA_CHAN));   //wait dma finish

    GH_USB_set_RXCSRH_W_PERI(0x08);     //disable out transfer

}

#if 0
GERR GD_USB_DMA_Out_TranTx(U32 read_addr, U32 read_len)
{
    GH_USB_set_Index(0x01);   //EP1 in
    GH_USB_set_TXCSRH_W_PERI(0xb4);

    GH_DMA_set_Source_Address(MUSB_TX_DMA_CHAN, read_addr);                //source data addr
    GH_DMA_set_Destination_Address(MUSB_TX_DMA_CHAN, REG_USB_ADDR_FIFO_EP(1));  //USB FIFO addr
    //GH_DMA_set_Destination_Address3(0, (U32)REG_USB_EP1FIFO);  //USB FIFO addr
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, 0x18800000|read_len);      //transfer length
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0x0);
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, 0x98800000|read_len);    //start DMA ,byte mode

    //GH_USB_set_TXCSR_W_PERI(0,0x1);      //enable in transfer
    while(GH_DMA_get_Control_en(MUSB_TX_DMA_CHAN));   //wait dma finish
    while(GH_USB_get_TXCSRL_R_PERI_TxPktRdy());  //wait transfer finish
    GH_USB_set_TXCSRH_W_PERI(0x24);

}
#endif 

// Func: read the INT reg & clear it.
GERR GD_USB_Read_Clear_IntrTx(U16 *pINT)
{
    if(pINT != NULL)
        *pINT = GH_USB_get_IntrTx();
    else
        return GD_ERR_BAD_PARAMETER;

    return GD_OK;
}


// Func: read the INT reg & clear it.
GERR GD_USB_Read_Clear_IntrRx(U16 *pINT)
{
    if(pINT != NULL)
        *pINT = GH_USB_get_IntrRx();
    else
        return GD_ERR_BAD_PARAMETER;

    return GD_OK;
}



#else // #ifdef GK710X

// Func: host recvs data from slave.
void GD_USB_In_tranTx(U8 *p, U32 len)
{
    U32 i, n=0;
    U32 maxPktSize = 0;

    printf("[GK]%s(), len=%d\n", __FUNCTION__, len);

    GH_USB_set_Index(g_tx_ep);

#ifdef USB_DATA_TRAN_MODE_DMA
    GH_USB_set_TXCSRH_W_PERI(0xa4);  // AutoSet & EPx  dir:Tx & DMAReqMode 1
    maxPktSize = 64;
    //maxPktSize = 1024;             // According to USB spec2.0, maxSize is 512 for BulkT
    //maxPktSize = 512;
#endif

#ifdef USB_DATA_TRAN_MODE_PIO
    GH_USB_set_TXCSRH_W_PERI(0xa0);  //set autoset & EP dir:TX
    //maxPktSize = 1024;
    maxPktSize = 512;               // According to USB spec2.0, maxSize is 512 for BulkT
#endif

	while(1)
	{
		if(len>=maxPktSize) //TxPktRdy will be automatically set when data of maxPktSize (value in TxMaxP) is loaded into the TX FIFO.
		{
			for(i=0;i<maxPktSize;i++)
			{
				//*REG_USB_EP1FIFO = p[n++];
                GH_USB_set_FIFOs(g_tx_ep, p[n]);
                //GH_USB_set_FIFOs(1, p[n]);
                n++;
			}

			while(GH_USB_get_TXCSRL_R_PERI() & 0x1);  // TxPktRdy
			len-=maxPktSize;
			if(len==0)
				break;
		}

		if(len<maxPktSize)
		{
			for(i=0;i<len;i++)
			{
				//*REG_USB_EP1FIFO = p[n++];
                GH_USB_set_FIFOs(g_tx_ep, p[n]);
                //GH_USB_set_FIFOs(1, p[n]);
                n++;
			}

			GH_USB_set_TXCSRL_W_PERI(0x01);
			while(GH_USB_get_TXCSRL_R_PERI() & 0x1);
			break;
		}
	}
}

// Func: host writes data using DMA. So the usb device would recv data from the host.
//       DMA Channel is from 0 - 3.
GERR GD_USB_DMA_In_TranRx(U32 host_write_addr, U32 host_write_len)
{
    U32 data = 0;

    printf("[GK]%s()\n", __FUNCTION__);

    GH_USB_set_Index(g_rx_ep);
    //GH_USB_set_Index(2);                //EP2 out

    GH_USB_set_RXCSRH_W_PERI(0xa8);    // AutoClear & enable DMA request for Rx endpoint 2 & DMA Request Mode 1

    GH_DMA_set_Source_Address(MUSB_RX_DMA_CHAN, REG_USB_ADDR_FIFO_EP(g_rx_ep));
   // GH_DMA_set_Source_Address(3, REG_USB_ADDR_FIFO_EP(2));
    GH_DMA_set_Destination_Address(MUSB_RX_DMA_CHAN, host_write_addr);

#if (USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_64)
    printf("[GK]USB_DMA_TBLK_SZ is 64 Bytes. var=%d, %d\n", USB_DMA_TBLK_SZ, TBLK_SZ_BYTES_64);
    //blk=64bytes, ts=8 4 2 1bytes
    data = 0x2b800000|host_write_len;
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_RX_DMA_CHAN, 0);
    data = 0xab800000|host_write_len;     // wr mem & Btbs:64B & ts:4B
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);
#elif (USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_32)
    printf("[GK]USB_DMA_TBLK_SZ is 32 Bytes. var=%d, %d\n", USB_DMA_TBLK_SZ, TBLK_SZ_BYTES_64);
    //blk=32bytes,  ts=8 4 2 1bytes
    data = 0x2a800000|host_write_len;
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_RX_DMA_CHAN, 0);
    data = 0xaa800000|host_write_len;     // wr mem & Btbs:32B & ts:4B
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);

#elif (USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_16)
    //blk=16bytes, ts=8 4 2 1bytes
    data = 0x29800000|host_write_len;
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_RX_DMA_CHAN, 0);
    data = 0xa9800000|host_write_len;     // wr mem & Btbs:16B & ts:4B
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);
#elif (USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_8)
    //blk=8bytes, ts=8 4 2 1bytes
    data = 0x28800000|host_write_len;
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_RX_DMA_CHAN, 0);
    data = 0xa8800000|host_write_len;     // wr mem & Btbs:8B & ts:4B
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);

#endif

    GH_USB_set_RXCSRL_W_PERI(0);
    while((GH_DMA_get_Control(MUSB_RX_DMA_CHAN) & 0x80000000)!=0);   //wait dma finish
    GH_USB_set_RXCSRH_W_PERI(0x08);                   //disable out transfer    // select DMA Request Mode 1 by yke

    return GD_OK;
}

// Func: host reads data using DMA. So the usb device would transfer data out to the host.
//       DMA Channel is from 0 - 3. EP: 1 - 16.
GERR GD_USB_DMA_Out_TranTx(U32 read_addr, U32 read_len)
{
    U32 data = 0;

    printf("[GK]%s()\n", __FUNCTION__);

     GH_USB_set_Index(g_tx_ep);
     //GH_USB_set_Index(1);

     GH_USB_set_TXCSRH_W_PERI(0xb4);   // AutoSet & endpoint 1 dir: Tx & enable the DMA request for the TX endpoint and DMA mode 1

     GH_DMA_set_Source_Address(MUSB_TX_DMA_CHAN, read_addr);
     GH_DMA_set_Destination_Address(MUSB_TX_DMA_CHAN, REG_USB_ADDR_FIFO_EP(g_tx_ep));
     //GH_DMA_set_Destination_Address(0, REG_USB_ADDR_FIFO_EP(1));

#if USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_64
    printf("[GK]USB_DMA_TBLK_SZ is 64 Bytes. var=%d\n", USB_DMA_TBLK_SZ);
    //blk=64bytes   //ts =8 4 2 1 bytes
    data = 0x1b800000|read_len;                     // read mem & Btbs:64B & ts:4B
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);
    GH_USB_PHY_set_Tx_Config_tx_dma_blk(DMA_TBLK_SZ_BYTES_64);    // ¦Ì¨¨??¨®¨² dma ??????¡ä??¡Â BlockSize ?? : 64Bytes
    data = 0x9b800000|read_len;
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
#elif USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_32
    printf("[GK]USB_DMA_TBLK_SZ is 32 Bytes. var=%d\n", USB_DMA_TBLK_SZ);
    //blk=32bytes  //ts =8 4 2 1 bytes
    data = 0x1a800000|read_len;                     // read mem & Btbs:32B & ts:4B
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);
    GH_USB_PHY_set_Tx_Config_tx_dma_blk(DMA_TBLK_SZ_BYTES_32);    // ¦Ì¨¨??¨®¨² dma ??????¡ä??¡Â BlockSize ?? : 32Bytes
    data = 0x9a800000|read_len;
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
#elif USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_16
    printf("[GK]USB_DMA_TBLK_SZ is 16 Bytes.\n");
    //blk=16bytes  //ts =8 4 2 1 bytes
    data = 0x19800000|read_len;                     // read mem & Btbs:16B & ts:4B
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);
    GH_USB_PHY_set_Tx_Config_tx_dma_blk(DMA_TBLK_SZ_BYTES_16);    // ¦Ì¨¨??¨®¨² dma ??????¡ä??¡Â BlockSize ?? : 16Bytes

    data = 0x99800000|read_len;
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);

#elif USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_8

    //blk=8bytes   //ts =8 4 2 1 bytes
    data = 0x18800000|read_len;                     // read mem & Btbs:8B & ts:4B
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);
    GH_USB_PHY_set_Tx_Config_tx_dma_blk(DMA_TBLK_SZ_BYTES_8);    // ¦Ì¨¨??¨®¨² dma ??????¡ä??¡Â BlockSize ?? : 8Bytes
    data = 0x98800000|read_len;
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);

#endif

     while((GH_DMA_get_Control(MUSB_TX_DMA_CHAN) & 0x80000000) != 0);    // auto clear enable-bit after finishing data transmitting

     while(GH_USB_get_TXCSRL_R_PERI() & 0x1);   // TxPktRdy should be cleared automatically for endpoint 1 after transmitting

     GH_USB_set_TXCSRH_W_PERI(0x24);  // dir:Tx & not enable the DMA request & DMA mode 1

    return GD_OK;
}



#define REG_DMA_FIFO_CLR  0x90003300
// Func: 1.host reads data using DMA. So the usb device would transfer data out to the host.
//       2.DMA Channel is from 0 - 3. EP: 1 - 16.
//       3.Test the bug of clearing DMA FIFO when restarting USB
GERR GD_USB_DMA_Out_TranTx_Fix_BugDMA(U32 read_addr, U32 read_len)
{
    U32 data = 0, tryCnt = 0;

    printf("[GK]%s()\n", __FUNCTION__);

     GH_USB_set_Index(g_tx_ep);

     GH_USB_set_TXCSRH_W_PERI(0xb4);   // AutoSet & endpoint 1 dir: Tx & enable the DMA request for the TX endpoint and DMA mode 1

     GH_DMA_set_Source_Address(MUSB_TX_DMA_CHAN, read_addr);
     GH_DMA_set_Destination_Address(MUSB_TX_DMA_CHAN, REG_USB_ADDR_FIFO_EP(g_tx_ep));

#if USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_64
    printf("[GK]USB_DMA_TBLK_SZ is 64 Bytes. var=%d\n", USB_DMA_TBLK_SZ);
    //blk=64bytes   //ts =8 4 2 1 bytes
    data = 0x1b800000|read_len;                     // read mem & Btbs:64B & ts:4B
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);
    GH_USB_PHY_set_Tx_Config_tx_dma_blk(DMA_TBLK_SZ_BYTES_64);    // ¦Ì¨¨??¨®¨² dma ??????¡ä??¡Â BlockSize ?? : 64Bytes
    data = 0x9b800000|read_len;
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
#elif USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_32
    printf("[GK]USB_DMA_TBLK_SZ is 32 Bytes. var=%d\n", USB_DMA_TBLK_SZ);
    //blk=32bytes  //ts =8 4 2 1 bytes
    data = 0x1a800000|read_len;                     // read mem & Btbs:32B & ts:4B
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);
    GH_USB_PHY_set_Tx_Config_tx_dma_blk(DMA_TBLK_SZ_BYTES_32);    // ¦Ì¨¨??¨®¨² dma ??????¡ä??¡Â BlockSize ?? : 32Bytes
    data = 0x9a800000|read_len;
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
#elif USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_16
    printf("[GK]USB_DMA_TBLK_SZ is 16 Bytes.\n");
    //blk=16bytes  //ts =8 4 2 1 bytes
    data = 0x19800000|read_len;                     // read mem & Btbs:16B & ts:4B
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);
    GH_USB_PHY_set_Tx_Config_tx_dma_rclr(0x01);
    GH_USB_PHY_set_Tx_Config_tx_dma_blk(DMA_TBLK_SZ_BYTES_16);    // ¦Ì¨¨??¨®¨² dma ??????¡ä??¡Â BlockSize ?? : 16Bytes
    GH_USB_PHY_set_Tx_Config_tx_dma_rclr(0x00);

    data = 0x99800000|read_len;
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);

#elif USB_DMA_TBLK_SZ == TBLK_SZ_BYTES_8

    //blk=8bytes   //ts =8 4 2 1 bytes
    data = 0x18800000|read_len;                     // read mem & Btbs:8B & ts:4B
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);
    GH_USB_PHY_set_Tx_Config_tx_dma_blk(DMA_TBLK_SZ_BYTES_8);    // ¦Ì¨¨??¨®¨² dma ??????¡ä??¡Â BlockSize ?? : 8Bytes
    data = 0x98800000|read_len;
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);

#endif

	data = 0;
    data = GH_DMA_get_Status(MUSB_TX_DMA_CHAN);
 	while(data == 0)
 	{
         data = GH_DMA_get_Status(MUSB_TX_DMA_CHAN);
	}

	// stop USB
	GH_USB_set_TXCSRH_W_PERI(0xa4);   // AutoSet & endpoint 1 dir: Tx & disable the DMA request for the TX endpoint and DMA mode 1
    printf("1....DMA CH0, CTL=%#x, STA=%#x, INT=%#x, STA0=%#x\n", GH_DMA_get_Control(MUSB_TX_DMA_CHAN), GH_DMA_get_Status(MUSB_TX_DMA_CHAN), GH_DMA_get_IR(), data);
    GH_USB_set_TXCSRL_W_PERI(0x08);   // set FlushFIFO
    GH_USB_set_TXCSRL_W_PERI(0x01);   // TxPktRdy
    GH_USB_set_TXCSRL_W_PERI(0x00);   //

    // stop DMA
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, 0);
    printf("2....DMA CH0, CTL=%#x, STA=%#x\n", GH_DMA_get_Control(MUSB_TX_DMA_CHAN), GH_DMA_get_Status(MUSB_TX_DMA_CHAN));
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);

     // clear DMA FIFO
     printf("....Clear DMA FIFO Reg & NO delay...\n");
    *(volatile unsigned int *)REG_DMA_FIFO_CLR = 0x01;  //clr fifo_ptr
    GH_USB_PHY_set_Tx_Config(0x11);

    return GD_OK;
}


// Func: host reads data using INT. So the usb device would transfer data out to the host.
//       DMA Channel is from 0 - 3. EP: 1 - 16.
GERR GD_USB_IRQ_Out_TranTx_Set(U32 hs_read_addr, U32 hs_read_len)
{
    U32 data = 0;

    printf("[GK]%s()\n", __FUNCTION__);

    GH_USB_set_Index(1);        //EP1 in

    GH_USB_set_TXCSRH_W_PERI(0xb4);         //bit2=1: mode1   // AutoSet & endpoint 1 dir: Tx & enable the DMA request for the TX endpoint and DMA mode 1

    GH_DMA_set_Source_Address(MUSB_TX_DMA_CHAN, hs_read_addr);
    GH_DMA_set_Destination_Address(MUSB_TX_DMA_CHAN, REG_USB_ADDR_FIFO_EP(1));

    data = 0x1b800000|hs_read_len;          //transfer length   //64bytes
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_TX_DMA_CHAN, 0);

    GH_USB_PHY_set_Tx_Config_tx_dma_blk(DMA_TBLK_SZ_BYTES_64);      //blk=64bytes  enable ack
    data = 0x9b800000|hs_read_len;                    //blk=64bytes, ts=4bytes
    GH_DMA_set_Control(MUSB_TX_DMA_CHAN, data);

    while((GH_DMA_get_Control(MUSB_TX_DMA_CHAN) & 0x80000000)!=0);      //wait dma finish

    return GD_OK;
}


// Func: host writes data using IRQ. So the usb device would recv data from the host.
//       DMA Channel is from 0 - 3.
GERR GD_USB_IRQ_In_TranRx_Set(U32 host_write_addr, U32 host_write_len)
{
    U32 data = 0;

    printf("[GK]%s()\n", __FUNCTION__);

    GH_USB_set_Index(2);              //EP2 out. WARNING: change the pos with the next code line
    GH_USB_set_RXCSRL_W_PERI(0);      //RxPktRdy is clear, next parket can received, chang by hr 20160314
    GH_USB_set_RXCSRH_W_PERI(0xa8);   //bit3=1, mode1, enable req();

    GH_DMA_set_Source_Address(MUSB_RX_DMA_CHAN, REG_USB_ADDR_FIFO_EP(2));
    GH_DMA_set_Destination_Address(MUSB_RX_DMA_CHAN, host_write_addr);

    data = 0x2b800000|host_write_len;      //transfer length   //64bytes
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);
    GH_DMA_set_Status(MUSB_RX_DMA_CHAN, 0);

    data = 0xab800000|host_write_len;     //blk=64bytes, ts=4bytes                             //reset flag
    GH_DMA_set_Control(MUSB_RX_DMA_CHAN, data);

    while((GH_DMA_get_Control(MUSB_RX_DMA_CHAN) & 0x80000000)!=0);   //wait dma finish

    return GD_OK;
}

// PIO mode
void GD_USB_PIO_In_tran_tx(U32 *p, U32 len)
{
    U32 i, n=0;
    U32 pkt_sz = 0;

    printf("[GK]%s()\n", __FUNCTION__);

    pkt_sz = 128; //256;      // According to MaxPktSize, It should be changed. Unit is word(4Bytes).

    GH_USB_set_Index(g_tx_ep);
    //GH_USB_set_Index(1);     //select EP1
    //*REG_USB_TXCSRH = 0xa4;    //ok!
    GH_USB_set_TXCSRH_W_PERI(0x20);    // dir:Tx & not enable the DMA request

	while(1)
	{
        if(len>=pkt_sz)
        {
    		for(i=0;i<pkt_sz;i++)
    		{
//    			*(volatile UINT32 *)REG_USB_EP1FIFO = p[n++];

                GH_USB_set_FIFOs_U32(g_tx_ep, p[n++]);
                //GH_USB_set_FIFOs_U32(1, p[n++]);
    		}

            GH_USB_set_TXCSRL_W_PERI(0x01);      // TxPktRdy
    		while((GH_USB_get_TXCSRL_R_PERI()&0x1)==0x01);
    		len -= pkt_sz;
    		if(len==0)
    			break;
        }
        else
        {
            for(i=0;i<len;i++)
    		{
    			//*(volatile UINT32 *)REG_USB_EP1FIFO = p[n++];
                GH_USB_set_FIFOs_U32(g_tx_ep, p[n++]);
                //GH_USB_set_FIFOs_U32(1, p[n++]);
    		}

            GH_USB_set_TXCSRL_W_PERI(0x01);
    		while((GH_USB_get_TXCSRL_R_PERI()&0x1)==0x01);
    		len=0;
    		break;
        }
	}
}

void GD_USB_PIO_In_tran_rx(U32 *p, U32 len)
{
    U32 i, n=0;
//    UINT32 data;
    U32 pkt_sz = 0;

    printf("[GK]%s()\n", __FUNCTION__);

    pkt_sz = 128; //256;   // According to MaxPktSize, It should be changed. Unit is word(4Bytes).
    GH_USB_set_Index(g_rx_ep);
    //GH_USB_set_Index(2);      //select EP2
    GH_USB_set_RXCSRH_W_PERI(0x00);

	while(1)
	{
		if((len>=pkt_sz)&&((GH_USB_get_RXCSRL_R_PERI()&0x1) == 0x1))
		{
			for(i=0;i<pkt_sz;i++)
			{
/*			    data = 0;
			    data = GH_USB_get_FIFOs(2);
                data |= GH_USB_get_FIFOs(2) << 8;

                data |= GH_USB_get_FIFOs(2) << 16;
                data |= GH_USB_get_FIFOs(2) << 24;
				//p[n++] = (*(volatile UINT32 *)REG_USB_EP2FIFO);
				p[n++] = data;
*/
                p[n++] = GH_USB_get_FIFOs_U32(g_rx_ep);
                //p[n++] = GH_USB_get_FIFOs_U32(2);
			}

			GH_USB_set_RXCSRL_W_PERI(0x00);                    //ok! manual REG_USB_RXCSRL bit0=0, will true!

			//while(((*REG_USB_RXCSRL)&0x1)==0x01)    //(auto: every time of 512B to wait REG_USB_RXCSRL bit0=0, maybe error)
			//{
			//	printf("RXCOUNT=%d\n",
		    //	(((*REG_USB_RXCOUNT_H)<<8)|(*REG_USB_RXCOUNT_L)));
			//}

			len-=pkt_sz;

			if(len==0)
				break;
		}

		if((len<pkt_sz)&&((GH_USB_get_RXCSRL_R_PERI()&0x1) == 0x1))
		{
			for(i=0;i<len;i++)
			{
/*			    data = 0;
			    data = GH_USB_get_FIFOs(2);
                data |= GH_USB_get_FIFOs(2) << 8;

                data |= GH_USB_get_FIFOs(2) << 16;
                data |= GH_USB_get_FIFOs(2) << 24;
				// p[n++] = (*REG_USB_EP2FIFO);      // maybe bug here
				p[n++] = data; */
                p[n++] = GH_USB_get_FIFOs_U32(g_rx_ep);
                //p[n++] = GH_USB_get_FIFOs_U32(2);
			}

			GH_USB_set_RXCSRL_W_PERI(0x00);

            //printf("len(<=128) = 0x%x\n", len);
			//while((*REG_USB_RXCSRL&0x1)==0x01);
			break;
		}
	}
}


// Func: read the INT reg & clear it.
GERR GD_USB_Read_Clear_IntrTx_L(U8 *pINT)
{
    if(pINT != NULL)
        *pINT = GH_USB_get_IntrTx_L();
    else
        return GD_ERR_BAD_PARAMETER;

    return GD_OK;
}


// Func: read the INT reg & clear it.
GERR GD_USB_Read_Clear_IntrRx_L(U8 *pINT)
{
    if(pINT != NULL)
        *pINT = GH_USB_get_IntrRx_L();
    else
        return GD_ERR_BAD_PARAMETER;

    return GD_OK;
}

#endif // #ifdef GK710X
