/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/emac/gd_eth_phy_rtl8201.c
**
** \version     $Id$
**
** \brief       1
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include "gtypes.h"
#include "gd_timer.h"
#include "gd_ethernet.h"
#include "gd_eth_priv.h"
#include "gd_eth_emac.h"
#include "gd_eth_phy.h"
#include "gd_eth_ephy.h"

#include "gh_eth.h"
#include "gh_ephy.h"
#include "gh_gpio.h"
//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local structures
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************

#define WRREG(addr, value)  *(volatile unsigned long*)(addr) = (value)
#define RDREG(addr)         *(volatile unsigned long*)(addr)
#if 0
void MHal_EMAC_WritReg8( U32 bank, U32 reg, U8 val )
{
    U32 address = REG_EPHY_CONTROL + (bank-0x32)*0x100*2;
    address = address + (reg << 1) - (reg & 1);

    *( ( volatile U8* ) address ) = val;
}

U8 MHal_EMAC_ReadReg8( U32 bank, U32 reg )
{
    U8 val;
    U32 address = REG_EPHY_CONTROL + (bank-0x32)*0x100*2;
    address = address + (reg << 1) - (reg & 1);

    val = *( ( volatile U8* ) address );
    return val;
}
#endif

GERR GD_ETH_EPHY_Init(void)
{
    U8 uRegVal;
#if 1
    //WRREG(0x60022540, 0x0000);//default is 0x1000
    //GH_EPHY_set_MDIIO_mdio_idle_error_cnt_clear(0x00);
    GH_EPHY_set_MDIIO_pd_vbuf(0x00);

    //WRREG(0x600220C8, 0xC400);  //default is 0x0000// reg_test_out(debug_bus_out)
    //GH_EPHY_set_DEBUG_snr_locked(0x00);
    //GH_EPHY_set_DEBUG_snr_locked_raw(0x00);
    //GH_EPHY_set_DEBUG_sig_det_flag(0x00);
    //GH_EPHY_set_DEBUG_state_sync_on(0x00);
    //GH_EPHY_set_DEBUG_state_st_lk(0x00);
    GH_EPHY_set_DEBUG_mux_recov_cnt(0x04);
    GH_EPHY_set_DEBUG_test_mux_sel(0x03);
    //GH_EPHY_set_DEBUG(0xC400);

    //WRREG(0x600220E0, 0x810A);//default is 0x0000  // debug mode
    GH_EPHY_set_DEBUG_MODE_signal(0x0A);
    GH_EPHY_set_DEBUG_MODE_module(0x81);
    //GH_EPHY_set_DEBUG(0x810A);

    //WRREG(0x60022588, 0x0007);  // DAC 100M clk gate for 10M TX
    //GH_EPHY_set_CLK0_lpi_tx_tq_timer_msb(0x07);
    //GH_EPHY_set_CLK0_clko_125_inv(0x00);
    //GH_EPHY_set_CLK0_clko_100_gat(0x00);
    //GH_EPHY_set_CLK0_clko_100_inv(0x00);

    //MHal_EMAC_WritReg8(0x0033, 0xde, 0x59);
    //WRREG(0x600223BC, 0x0059);//default is 0x0059
    //GH_EPHY_set_PWR_pwr_k_in_lp(0x01);
    //GH_EPHY_set_PWR_dtpwr_enable_lp(0x01);
    //GH_EPHY_set_PWR_gcr_adcpl_div_lp(0x05);
    //GH_EPHY_set_PWR_dummy(0x00);

    //MHal_EMAC_WritReg8(0x0033, 0xf4, 0x21);
    //WRREG(0x600223E8, 0x0821);//default is 0x0821
    //GH_EPHY_set_ADCPL_mod_10t(0x01);
    //GH_EPHY_set_ADCPL_mod(0x00);
    //GH_EPHY_set_ADCPL_mod_lp(0x02);
    //GH_EPHY_set_ADCPL_adc_frc_zero(0x00);
    //GH_EPHY_set_ADCPL_adcpl_step(0x04);
    //GH_EPHY_set_ADCPL_ac_a_timer_start(0x00);
    //GH_EPHY_set_ADCPL_ac_sample_timer_start(0x00);
    //GH_EPHY_set_ADCPL_txramp_gen_10t(0x00);

    //MHal_EMAC_WritReg8(0x0032, 0x72, 0x80);
    //WRREG(0x600220E4, 0x0480);//default is 0x0480
    //GH_EPHY_set_RST_EN_mau_srst(0x00);
    //GH_EPHY_set_RST_EN_pls_srst(0x00);
    //GH_EPHY_set_RST_EN_sqe_test_enable(0x00);
    //GH_EPHY_set_RST_EN_lpbk_enable(0x00);
    //GH_EPHY_set_RST_EN_jabber_enable(0x00);
    //GH_EPHY_set_RST_EN_ser_polarity_correction(0x00);
    //GH_EPHY_set_RST_EN_por_stick_mode(0x00);
    //GH_EPHY_set_RST_EN_recv_bit_bucket(0x01);
    //GH_EPHY_set_RST_EN_rxclk_pol(0x00);
    //GH_EPHY_set_RST_EN_txclk_pol(0x00);
    //GH_EPHY_set_RST_EN_adc_input_sign(0x01);
    //GH_EPHY_set_RST_EN_mii_test_packet(0x00);
    //GH_EPHY_set_RST_EN_clear_rcvpack(0x00);
    //GH_EPHY_set_RST_EN_miiloop_en_10m(0x00);
    //GH_EPHY_set_RST_EN_mii_rxclk_pol(0x00);
    //GH_EPHY_set_RST_EN_mii_txclk_pol(0x00);

    //MHal_EMAC_WritReg8(0x0033, 0xfc, 0x00);
    //MHal_EMAC_WritReg8(0x0033, 0xfd, 0x00);
    //WRREG(0x600223F8, 0x0000);//default is 0x0102
    GH_EPHY_set_LDO_dummy(0x0000);

    //MHal_EMAC_WritReg8(0x0033, 0xb7, 0x07);
    //WRREG(0x6002236C, 0x0700);//default is 0x1704
    GH_EPHY_set_ADC_adc_bp(0x00);
    //GH_EPHY_set_ADC_dac10t_testen(0x00);
    //GH_EPHY_set_ADC_reg_dac100t_testen(0x00);
    //GH_EPHY_set_ADC_adc_bma(0x07);
    GH_EPHY_set_ADC_adc_pd(0x00);
    //GH_EPHY_set_ADC_region_bank_rd(0x00);
    //GH_EPHY_set_ADC_adcpll_ana_clken(0x00);
    //GH_EPHY_set_ADC_adcbin_testen(0x00);
    //GH_EPHY_set_ADC(0x0700);

    //MHal_EMAC_WritReg8(0x0033, 0xcb, 0x11);
    //WRREG(0x60022394, 0x1100);//default is 0x111A
    //GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_lock(0x00);
    GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_div(0x00);
    GH_EPHY_set_PLL_ADC_CTRL0_test_adcpl_extcksel(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_high_flag(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0_pllclk_outen(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0_ov_ref_test(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0_gc_adcpl_rstb(0x01);
    //GH_EPHY_set_PLL_ADC_CTRL0_ref_bgap_pd(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst_sw(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0_ldo_pwrgd(0x01);
    //GH_EPHY_set_PLL_ADC_CTRL0_adcraw_overflow(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0_adcpl_force_phase(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_tog_clkcc(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL0(0x1100);

    //MHal_EMAC_WritReg8(0x0033, 0xcc, 0x80);
    //MHal_EMAC_WritReg8(0x0033, 0xcd, 0xd1);
    //WRREG(0x60022398, 0xD180);//default is 0xD990
    //GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd0(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd1(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd0(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd1(0x00);
    GH_EPHY_set_PLL_ADC_CTRL1_pd_adcpl_reg(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_mod_100t(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_ictrl(0x03);
    //GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_enfrunz(0x00);
    GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_porst(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_adcphdac(0x01);
    //GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcselect(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL1_tx_d_test(0x03);
    //GH_EPHY_set_PLL_ADC_CTRL1(0xD180);

    //MHal_EMAC_WritReg8(0x0033, 0xd4, 0x00);
    //WRREG(0x600223A8, 0x0000);//default is 0x0020
    //GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vgen(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcom(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcmpcmvx(0x00);
    GH_EPHY_set_PLL_ADC_CTRL2_pd_lpf_op(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force1(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force0(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_endiscz_10(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_gcr_adcpl_pdphadc(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_adcpl_bank(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force_st(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2_adcpl_force_go(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL2(0x0000);

    //MHal_EMAC_WritReg8(0x0033, 0xb9, 0x40);
    //WRREG(0x60022370, 0x4000);//default is 0x4100
    GH_EPHY_set_PLL_ADC_CTRL3_rxlpf_pd(0x00);
    //GH_EPHY_set_PLL_ADC_CTRL3_tx_b_test(0x20);

    //MHal_EMAC_WritReg8(0x0033, 0xbb, 0x05);
    //WRREG(0x60022374, 0x0500);//default is 0x4403
    //GH_EPHY_set_RX_LPF_rxlpf_ibsel(0x00);
    //GH_EPHY_set_RX_LPF_rxlpf_bwsel(0x00);
    //GH_EPHY_set_RX_LPF_unkown(0x02);
    //GH_EPHY_set_RX_LPF_rxlpf_cmsel(0x01);
    //GH_EPHY_set_RX_LPF_rxlpf_outp_test(0x00);
    //GH_EPHY_set_RX_LPF_rxlpf_outm_test(0x00);
    //GH_EPHY_set_RX_LPF_rxlpf_bypass(0x00);
    //GH_EPHY_set_RX_LPF_ref_pd(0x00);
    //GH_EPHY_set_RX_LPF_ref_iint_pd(0x00);
    GH_EPHY_set_RX_LPF(0x0500);

    //MHal_EMAC_WritReg8(0x0033, 0xea, 0x46);
    //WRREG(0x600223D4, 0x0046);//default is 0x4060
    //GH_EPHY_set_ADC_DC_dc_force_en(0x00);
    GH_EPHY_set_ADC_DC_dc_force(0x03);
    GH_EPHY_set_ADC_DC_dc_can_inv(0x00);
    //GH_EPHY_set_ADC_DC_analog_blw(0x01);
    //GH_EPHY_set_ADC_DC_dc_k(0x00);
    //GH_EPHY_set_ADC_DC_srst(0x00);
    //GH_EPHY_set_ADC_DC_adc_cancel_out(0x00);
    GH_EPHY_set_ADC_DC_adc_cancel_disable(0x00);
    //GH_EPHY_set_ADC_DC_adc_start(0x00);
    //GH_EPHY_set_ADC_DC(0x0046);

    //MHal_EMAC_WritReg8(0x0033, 0xa1, 0x00);
    //WRREG(0x60022340, 0x0000);//default is 0x1000
    //GH_EPHY_set_LPF_lpf_out_h(0x00);
    //GH_EPHY_set_LPF_rxlpf_bwsel_10t(0x00);
    GH_EPHY_set_LPF_rxlpf_bwsel_100t(0x00);
    //GH_EPHY_set_LPF_cable_length(0x00);
    //GH_EPHY_set_LPF(0x0000);

    //MHal_EMAC_WritReg8(0x0034, 0x3a, 0x03);
    //MHal_EMAC_WritReg8(0x0034, 0x3b, 0x00);
    //WRREG(0x60022474, 0x0003);//default is 0x03F3 power down close
    //GH_EPHY_set_POWER_pd_tx_ld(0x01);
    //GH_EPHY_set_POWER_pd_tx_idac(0x01);
    //GH_EPHY_set_POWER_pd_dacramp_new(0x00);
    //GH_EPHY_set_POWER_pd_dacnew_testen(0x00);
    GH_EPHY_set_POWER_pd_tx_ld_10t(0x00);
    GH_EPHY_set_POWER_pd_tx_ld_100t(0x00);
    GH_EPHY_set_POWER_pd_tx_ld_lp(0x00);
    GH_EPHY_set_POWER_pd_tx_idac_10t(0x00);
    GH_EPHY_set_POWER_pd_tx_idac_100t(0x00);
    GH_EPHY_set_POWER_pd_tx_idac_lp(0x00);
    //GH_EPHY_set_POWER(0x0003);

    //gain shift
    //MHal_EMAC_WritReg8(0x0033, 0xb4, 0x56);
    //WRREG(0x60022368, 0x0056);//default is 0x0000
    GH_EPHY_set_ADC_GSHIFT_adc_gshift(0x02);
    GH_EPHY_set_ADC_GSHIFT_gain(0x15);
    //GH_EPHY_set_ADC_GSHIFT(0x0056);

    //det max
    //MHal_EMAC_WritReg8(0x0033, 0x4f, 0x02);
    //WRREG(0x6002229C, 0x024C);//default is 0x054C
    //GH_EPHY_set_DET_MAX_thrh_max_vga_coarse(0x4C);
    GH_EPHY_set_DET_MAX_thrh_max_sig_det(0x02);
    //GH_EPHY_set_DET_MAX(0x024C);

    //det min
    //MHal_EMAC_WritReg8(0x0033, 0x51, 0x01);
    //WRREG(0x600222A0, 0x0160);//default is 0x0260
    //GH_EPHY_set_DET_MIN_thrh_max_vga_fine(0x60);
    GH_EPHY_set_DET_MIN_thrh_min_sig_det(0x01);
    //GH_EPHY_set_DET_MIN(0x0160);

    //snr len (emc noise)
    //MHal_EMAC_WritReg8(0x0033, 0x77, 0x18);
    //WRREG(0x600222EC, 0x1800);//default is 0x0000
    //GH_EPHY_set_SNR_LEN_mcu_ctrl_dsp_fsm_state(0x00);
    //GH_EPHY_set_SNR_LEN_force_100m_en(0x00);
    //GH_EPHY_set_SNR_LEN_force_100m_snr_lock(0x00);
    //GH_EPHY_set_SNR_LEN_dsp_fsm_agc_en_mode_a(0x00);
    GH_EPHY_set_SNR_LEN_cable_len_offset(0x03);
    //GH_EPHY_set_SNR_LEN(0x1800);

    //snr k value
    //MHal_EMAC_WritReg8(0x0033, 0x43, 0x15);
    //WRREG(0x60022284, 0x1520);//default is 0x1520
    //GH_EPHY_set_SNR_K_slice_up(0x20);
    //GH_EPHY_set_SNR_K_snrchk_k1(0x01);
    //GH_EPHY_set_SNR_K_snrchk_k2(0x01);
    //GH_EPHY_set_SNR_K_snrchk_k3(0x01);
    //GH_EPHY_set_SNR_K_gcr_ccpl_master_coarse_clkcc(0x00);

    //100 gat
    //MHal_EMAC_WritReg8(0x0034, 0xc5, 0x00);
    //WRREG(0x60022588, 0x0007);//default is 0x4007 DAC 100M clk gate for 10M TX
    //GH_EPHY_set_CLK0_lpi_tx_tq_timer_msb(0x07);
    //GH_EPHY_set_CLK0_clko_125_inv(0x00);
    GH_EPHY_set_CLK0_clko_100_gat(0x00);
    //GH_EPHY_set_CLK0_clko_100_inv(0x00);
    //GH_EPHY_set_CLK0(0x0007);

    //200 gat
    //MHal_EMAC_WritReg8(0x0034, 0x30, 0x43);
    //WRREG(0x60022460, 0x0043);//default is 0x0053 Add this 100M up down loop
    //GH_EPHY_set_CLK1_unkown(0x03);
    GH_EPHY_set_CLK1_clko_200_gat(0x00);
    //GH_EPHY_set_CLK1_clko_200_inv(0x00);
    //GH_EPHY_set_CLK1_lut_new(0x01);
    //GH_EPHY_set_CLK1(0x0043);

    //en_100t_phase
    //MHal_EMAC_WritReg8(0x0034, 0x39, 0x41);
    //WRREG(0x60022470, 0x4100);//default is 0x0000
    //GH_EPHY_set_GCR_TX_ioffset_sel(0x00);
    //GH_EPHY_set_GCR_TX_ld_vcmo(0x00);
    //GH_EPHY_set_GCR_TX_ph_delay(0x00);
    GH_EPHY_set_GCR_TX_phase_100t(0x01);
    //GH_EPHY_set_GCR_TX_ld_iq_sel(0x00);
    //GH_EPHY_set_GCR_TX_ld_iq_ibias(0x00);
    //GH_EPHY_set_GCR_TX_en_tx_ioffset(0x00);
    GH_EPHY_set_GCR_TX_save2x_tx(0x01);
    //GH_EPHY_set_GCR_TX_wssel_inv(0x00);
    //GH_EPHY_set_GCR_TX(0x4100);

    //10T waveform
    //uRegVal = MHal_EMAC_ReadReg8(0x0034, 0xe8);
    //uRegVal &= 0xf8;
    //uRegVal |= 0x06;
    //MHal_EMAC_WritReg8(0x0034, 0xe8, uRegVal);
    //WRREG(0x600225D0, uRegVal);//default is 0x0000
    GH_EPHY_set_WAVE_CTRL_shadow(0x06);

    //MHal_EMAC_WritReg8(0x0032, 0x2b, 0x00);
    //WRREG(0x60022054, 0x0000);//default is 0xF800 or 0xFC00
    //GH_EPHY_set_WAVE_SHAPING_DE_ltp_D(0x00);
    GH_EPHY_set_WAVE_SHAPING_DE_ltp_E(0x00);
    //GH_EPHY_set_WAVE_SHAPING_DE(0x0000);

    //analog
    //MHal_EMAC_WritReg8(0x0033, 0xd8, 0xb0);
    //MHal_EMAC_WritReg8(0x0033, 0xd9, 0x30);
    //WRREG(0x600223B0, 0x30B0);//default is 0x0000
    GH_EPHY_set_TEST_TX(0x30B0);

    //disable EEE
    //uRegVal = MHal_EMAC_ReadReg8(0x0032, 0x2d);
    //uRegVal |= 0x40;
    //MHal_EMAC_WritReg8(0x0032, 0x2d, uRegVal);
    //WRREG(0x60022058, 0x7C00);//default is 0x3C00
    //GH_EPHY_set_SPEED_ltp_F(0x00);
    //GH_EPHY_set_SPEED_isolate(0x00);
    //GH_EPHY_set_SPEED_rptr(0x00);
    //GH_EPHY_set_SPEED_duplex(0x01);
    //GH_EPHY_set_SPEED_speed(0x01);
    //GH_EPHY_set_SPEED_ane(0x01);
    //GH_EPHY_set_SPEED_ldps(0x01);
    GH_EPHY_set_SPEED_disable_eee_force(0x01);
    //GH_EPHY_set_SPEED(0x7C00);
#else
    //WRREG(0x60022000, 0x00000000);
    WRREG(0x600223F8, 0x00000000);
    WRREG(0x6002236C, 0x00000700);
    WRREG(0x60022394, 0x00001100);
    WRREG(0x60022398, 0x0000D180);
    WRREG(0x600223A8, 0x00000000);
    WRREG(0x60022370, 0x00004000);
    WRREG(0x60022374, 0x00000500);
    WRREG(0x600223D4, 0x00000046);
    WRREG(0x60022540, 0x00000000);
    WRREG(0x60022474, 0x00003A03);  // power down close
    WRREG(0x600220C8, 0x0000C400);  // reg_test_out(debug_bus_out)
    WRREG(0x600220E0, 0x0000810A);  // debug mode
    // riu_cs_bkb
    //WRREG(0x60022588, RDREG(0x60022588)&(~(1<<14)));    // DAC 100M clk gate for 10M TX
    WRREG(0x60022588, 0x00000007); // DAC 100M clk gate for 10M TX
    //WRREG(0x60022450, RDREG(0x60022450)&(~(1<<4)));     // DAC 200M clk gate for 10M TX
    //WRREG(0x60022450, 0x00000002); // DAC 200M clk gate for 10M TX
#if 0 // CASE 1 100M dis_an TX->RX GD_ETH_Open failed
    WRREG(0x60022058, RDREG(0x60022058)&(~(1<<12)));    // an_en from HW
    WRREG(0x60022058, RDREG(0x60022058)|(1<<11));       // MII 100M speed sel from HW
    WRREG(0x60022088, RDREG(0x60022088)|(1<<7));        // reg_force_100M_link_good
#endif

#if 0 // CASE 2 100M near_loop
    WRREG(0x60022058, RDREG(0x60022058)&(~(1<<12)));    // an_en from HW
    WRREG(0x60022058, RDREG(0x60022058)|(1<<11));       // MII 100M speed sel from HW
    WRREG(0x60022088, RDREG(0x60022088)|(1<<7));        // force 100M link good
    WRREG(0x60022000, RDREG(0x60022000)|(1<<14));       // reg_mii_ctl_loopback
    WRREG(0x600220DC, RDREG(0x600220DC)|0x7F);          // near_loop_s1
    // wait 100us
    for(ii=0;ii<20;ii++)
    {
        ;
    }
    //WRREG(0x600220DC, (RDREG(0x600220DC)&(~0x7F))|0x7E);// near_loop_s2
    // wait 100us
    for(ii=0;ii<20;ii++)
    {
        ;
    }
    WRREG(0x600220DC, (RDREG(0x600220DC)&(~0x7F))|0x7D);// near_loop_s3
#endif

#if 1 // CASE 3 10M dis_an TX->RX OK
    //WRREG(0x60022460, RDREG(0x60022460)&(~(1<<4)));     // reg_clk0_200
    //WRREG(0x60022058, RDREG(0x60022058)&(~(1<<12)));    // an_en from HW
    //WRREG(0x60022058, RDREG(0x60022058)&(~(1<<11)));    // MII 10M speed sel from HW
    //WRREG(0x60022080, RDREG(0x60022080)|(1<<7));        // force nlp pass
    WRREG(0x60022460, 0x0043);       // Add this 100M up down loop
    //GH_EPHY_set_SPEED_ane(0x01);

    //WRREG(0x60022088, RDREG(0x60022088)|(1<<7));        // force 100M link good
    GH_EPHY_set_SPEED_ane(0x00);
    GH_EPHY_set_SPEED_duplex(1);//full
    GH_EPHY_set_SPEED_speed(1);//100M
    WRREG(0x600221AC, RDREG(0x600221AC)|(1<<0));        // transmit pattern generation
#endif

#if 0 // CASE 4 10M near_loop
    WRREG(0x60022058, RDREG(0x60022058)&(~(1<<12)));    // an_en from HW
    WRREG(0x60022058, RDREG(0x60022058)&(~(1<<11)));    // MII 10M speed sel from HW
    WRREG(0x60022080, RDREG(0x60022080)|(1<<7));        // force nlp pass
    WRREG(0x60022180, RDREG(0x60022180)|(1<<14));       // reg_10M_near_loop
#endif

#if 0 // CASE 5 100M AN
    WRREG(0x60022058, RDREG(0x60022058)|(1<<12));       // an_en from HW
    WRREG(0x600221AC, RDREG(0x600221AC)|(1<<0));        // transmit pattern generation
    WRREG(0x6002209C, RDREG(0x6002209C)&0xFFFFFF00);    // reg_breaklink_timer
    WRREG(0x600220AC, RDREG(0x600220AC)|(1<<15));       // is_clk_sel, speed the simulation
#endif
#endif
    return GD_OK;
}
GERR GD_ETH_EPHY_Open(GD_HANDLE handle)
{
    GH_GPIO_set_PER_SEL_enet_sel((U32)0x00000000);
    return GD_OK;
}
GERR GD_ETH_EPHY_Close(GD_HANDLE handle)
{
    return GD_OK;
}
GERR GD_ETH_EPHY_SWReset(GD_HANDLE handle)
{
    return GD_OK;
}
GERR GD_ETH_EPHY_SetWorkMode(GD_HANDLE handle, GD_ETH_Work_ModeT workmode)
{
    GERR gerr = GD_OK;
    GD_ETH_PHY_DEVICE_DATA_S* device;
    U8      ii = 0;
    GBOOL   retval = GFALSE;
    U32     regval = (U32)0;
    U8      addr;
    // to be do: only can use an mode
    return GD_OK;
    if (handle == 0)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    device = (GD_ETH_PHY_DEVICE_DATA_S*)(handle);

    // workmode.mode
    if(workmode.mode == GD_ETH_PHY_IF_MODE_MII)
    {
    }
    else
    {
        return GD_ERR_ETH_NOT_SUPPORTED;
    }

    if (workmode.bEnAutoNeg == GTRUE)
    {
        GH_EPHY_set_SPEED_ane(0x01);
    }
    else
    {
        GH_EPHY_set_SPEED_ane(0x00);
        // workmode.speed
        if (workmode.speed == GD_ETH_SPEED_100M )   /* 100M */
        {
            GH_EPHY_set_SPEED_speed(0x01);
        }
        else if (workmode.speed == GD_ETH_SPEED_10M )/* 10M */
        {
            GH_EPHY_set_SPEED_speed(0x00);
        }
        else
        {
            return GD_ERR_ETH_NOT_SUPPORTED;
        }

        /* duplex */
        // workmode.duplex
        if(workmode.duplex == GD_ETH_FULL_DUPLEX)   /* Full Duplex */
        {
            GH_EPHY_set_SPEED_duplex(0x01);
        }
        else if(workmode.duplex == GD_ETH_HALF_DUPLEX) /* half */
        {
            GH_EPHY_set_SPEED_duplex(0x00);
        }
        else
        {
            return GD_ERR_ETH_NOT_SUPPORTED;
        }
    }
    return GD_OK;
}
GERR GD_ETH_EPHY_GetWorkStatus(GD_HANDLE handle, GD_ETH_StatParamsT* pStat)
{
    U16     reg;
    reg = GH_EPHY_get_CONTROL();

    pStat->speed    = (reg & 0x2000) ? GD_ETH_SPEED_100M : GD_ETH_SPEED_10M;
    pStat->duplex   = (reg & 0x0100) ? GD_ETH_FULL_DUPLEX : GD_ETH_HALF_DUPLEX;

    reg = GH_EPHY_get_STATUS();
    pStat->linkup   = (reg & 0x0020) ? GD_ETH_LINKUP : GD_ETH_LINKDOWN;

    return GD_OK;
}
GERR GD_ETH_EPHY_GetId(GD_HANDLE handle, U32 *phy_id)
{
    //U32     ulPhyId;
    //*phy_id |= (ulPhyId & 0xffff);
    return GD_OK;
}
//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************

