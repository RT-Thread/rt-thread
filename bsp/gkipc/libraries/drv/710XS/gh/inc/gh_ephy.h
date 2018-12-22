/*!
*******************************************************************************
**
** \file      gh_ephy.h
**
** \brief     Ethernet PHY controller.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GH_EPHY_H
#define _GH_EPHY_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_EPHY_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_EPHY_DEBUG_PRINT_FUNCTION printk
#else
#define GH_EPHY_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_EPHY_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/* check configuration */
#ifndef GH_INLINE_LEVEL
  #error "GH_INLINE_LEVEL is not defined!"
#endif
#if GH_INLINE_LEVEL > 2
  #error "GH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef GH_INLINE
  #error "GH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef GH_INLINE_LEVEL
  #define GH_INLINE_LEVEL 0
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_EPHY_MII_RMII                                   FIO_ADDRESS(EPHY,0x90020E00) /* read/write */
#define REG_EPHY_CONTROL                                    FIO_ADDRESS(EPHY,0x90022000) /* read/write */
#define REG_EPHY_STATUS                                     FIO_ADDRESS(EPHY,0x90022004) /* read */
#define REG_EPHY_ID1                                        FIO_ADDRESS(EPHY,0x90022008) /* read */
#define REG_EPHY_ID2                                        FIO_ADDRESS(EPHY,0x9002200C) /* read */
#define REG_EPHY_ANAR                                       FIO_ADDRESS(EPHY,0x90022010) /* read/write */
#define REG_EPHY_ANLPAR                                     FIO_ADDRESS(EPHY,0x90022014) /* read */
#define REG_EPHY_ANER                                       FIO_ADDRESS(EPHY,0x90022018) /* read/write */
#define REG_EPHY_ANNPAR                                     FIO_ADDRESS(EPHY,0x9002201C) /* read/write */
#define REG_EPHY_ANLPNP                                     FIO_ADDRESS(EPHY,0x90022020) /* read */
#define REG_EPHY_MS_CONTROL                                 FIO_ADDRESS(EPHY,0x90022024) /* read/write */
#define REG_EPHY_MS_STATUS                                  FIO_ADDRESS(EPHY,0x90022028) /* read */
#define REG_EPHY_PSE_CONTROL                                FIO_ADDRESS(EPHY,0x9002202C) /* read/write */
#define REG_EPHY_PSE_STATUS                                 FIO_ADDRESS(EPHY,0x90022030) /* read */
#define REG_EPHY_MMD_CONTROL                                FIO_ADDRESS(EPHY,0x90022034) /* read/write */
#define REG_EPHY_MMD_CONTROL_ADDR                           FIO_ADDRESS(EPHY,0x90022038) /* read/write */
#define REG_EPHY_AN_R_15                                    FIO_ADDRESS(EPHY,0x9002203C) /* read */
#define REG_EPHY_WAVE_SHAPING_34                            FIO_ADDRESS(EPHY,0x90022040) /* read/write */
#define REG_EPHY_WAVE_SHAPING_56                            FIO_ADDRESS(EPHY,0x90022044) /* read/write */
#define REG_EPHY_WAVE_SHAPING_78                            FIO_ADDRESS(EPHY,0x90022048) /* read/write */
#define REG_EPHY_WAVE_SHAPING_9A                            FIO_ADDRESS(EPHY,0x9002204C) /* read/write */
#define REG_EPHY_WAVE_SHAPING_BC                            FIO_ADDRESS(EPHY,0x90022050) /* read/write */
#define REG_EPHY_WAVE_SHAPING_DE                            FIO_ADDRESS(EPHY,0x90022054) /* read/write */
#define REG_EPHY_SPEED                                      FIO_ADDRESS(EPHY,0x90022058) /* read/write */
#define REG_EPHY_LTP                                        FIO_ADDRESS(EPHY,0x9002205C) /* read/write */
#define REG_EPHY_MCU                                        FIO_ADDRESS(EPHY,0x90022060) /* read/write */
#define REG_EPHY_CODE_RAM                                   FIO_ADDRESS(EPHY,0x90022064) /* read/write */
#define REG_EPHY_CODE_RAM_W                                 FIO_ADDRESS(EPHY,0x90022068) /* read/write */
#define REG_EPHY_100M_LINK                                  FIO_ADDRESS(EPHY,0x90022088) /* read/write */
#define REG_EPHY_DEBUG                                      FIO_ADDRESS(EPHY,0x900220C8) /* read/write */
#define REG_EPHY_DEBUG_MODE                                 FIO_ADDRESS(EPHY,0x900220E0) /* read/write */
#define REG_EPHY_RST_EN                                     FIO_ADDRESS(EPHY,0x900220E4) /* read/write */
#define REG_EPHY_SNR_K                                      FIO_ADDRESS(EPHY,0x90022284) /* read/write */
#define REG_EPHY_DET_MAX                                    FIO_ADDRESS(EPHY,0x9002229C) /* read/write */
#define REG_EPHY_DET_MIN                                    FIO_ADDRESS(EPHY,0x900222A0) /* read/write */
#define REG_EPHY_SNR_LEN                                    FIO_ADDRESS(EPHY,0x900222EC) /* read/write */
#define REG_EPHY_LPF                                        FIO_ADDRESS(EPHY,0x90022340) /* read/write */
#define REG_EPHY_ADC_GAIN_PGA                               FIO_ADDRESS(EPHY,0x9002236C) /* read/write */
#define REG_EPHY_ADC_GSHIFT                                 FIO_ADDRESS(EPHY,0x90022368) /* read/write */
#define REG_EPHY_ADC                                        FIO_ADDRESS(EPHY,0x9002236C) /* read/write */
#define REG_EPHY_PLL_ADC_CTRL3                              FIO_ADDRESS(EPHY,0x90022370) /* read/write */
#define REG_EPHY_RX_LPF                                     FIO_ADDRESS(EPHY,0x90022374) /* read/write */
#define REG_EPHY_PLL_ADC_CTRL0                              FIO_ADDRESS(EPHY,0x90022394) /* read/write */
#define REG_EPHY_PLL_ADC_CTRL1                              FIO_ADDRESS(EPHY,0x90022398) /* read/write */
#define REG_EPHY_PLL_ADC_CTRL2                              FIO_ADDRESS(EPHY,0x900223A8) /* read/write */
#define REG_EPHY_TEST_TX                                    FIO_ADDRESS(EPHY,0x900223B0) /* read/write */
#define REG_EPHY_PWR                                        FIO_ADDRESS(EPHY,0x900223BC) /* read/write */
#define REG_EPHY_ADC_DC                                     FIO_ADDRESS(EPHY,0x900223D4) /* read/write */
#define REG_EPHY_ADCPL                                      FIO_ADDRESS(EPHY,0x900223E8) /* read/write */
#define REG_EPHY_LDO                                        FIO_ADDRESS(EPHY,0x900223F8) /* read/write */
#define REG_EPHY_CLK_GATE                                   FIO_ADDRESS(EPHY,0x90022450) /* read */
#define REG_EPHY_CLK1                                       FIO_ADDRESS(EPHY,0x90022460) /* read/write */
#define REG_EPHY_GCR_TX                                     FIO_ADDRESS(EPHY,0x90022470) /* read/write */
#define REG_EPHY_POWER                                      FIO_ADDRESS(EPHY,0x90022474) /* read/write */
#define REG_EPHY_MDIIO                                      FIO_ADDRESS(EPHY,0x90022540) /* read/write */
#define REG_EPHY_CLK0                                       FIO_ADDRESS(EPHY,0x90022588) /* read/write */
#define REG_EPHY_WAVE_CTRL                                  FIO_ADDRESS(EPHY,0x900225D0) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* EPHY_MII_RMII */
    U32 all;
    struct {
        U32 usb_tm1                     : 1;
        U32 rmii                        : 1;
        U32                             : 30;
    } bitc;
} GH_EPHY_MII_RMII_S;

typedef union { /* EPHY_CONTROL */
    U16 all;
    struct {
        U16                             : 5;
        U16 mii_ctl_unidirectional_enable: 1;
        U16 mii_ctl_speed_sel_msb       : 1;
        U16 mii_ctl_col_test            : 1;
        U16 mii_ctl_duplex_mode         : 1;
        U16 mii_ctl_restart_an          : 1;
        U16 mii_ctl_isolate             : 1;
        U16 mii_ctl_power_down          : 1;
        U16 mii_ctl_an_en               : 1;
        U16 mii_ctl_speed_sel_lsb       : 1;
        U16 mii_ctl_loopback            : 1;
        U16 mii_ctl_reset               : 1;
    } bitc;
} GH_EPHY_CONTROL_S;

typedef union { /* EPHY_STATUS */
    U16 all;
    struct {
        U16 extended_capability         : 1;
        U16 jabber_detect               : 1;
        U16 link_status                 : 1;
        U16 an_ability                  : 1;
        U16 rf                          : 1;
        U16 an_complete                 : 1;
        U16 mf_preamble_suppression     : 1;
        U16 unidirectional_ability      : 1;
        U16 extended_status             : 1;
        U16 half_duplex_100t2           : 1;
        U16 full_duplex_100t2           : 1;
        U16 half_duplex_10              : 1;
        U16 full_duplex_10              : 1;
        U16 half_duplex_100x            : 1;
        U16 full_duplex_100x            : 1;
        U16 t4_100                      : 1;
    } bitc;
} GH_EPHY_STATUS_S;

typedef union { /* EPHY_ANAR */
    U16 all;
    struct {
        U16 selector                    : 5;
        U16 tech_ability                : 8;
        U16 rf                          : 1;
        U16                             : 1;
        U16 np                          : 1;
    } bitc;
} GH_EPHY_ANAR_S;

typedef union { /* EPHY_ANLPAR */
    U16 all;
    struct {
        U16 selector                    : 5;
        U16 tech_ability                : 8;
        U16 rf                          : 1;
        U16 ack                         : 1;
        U16 np                          : 1;
    } bitc;
} GH_EPHY_ANLPAR_S;

typedef union { /* EPHY_ANER */
    U16 all;
    struct {
        U16 lp_an_able                  : 1;
        U16 page_rec                    : 1;
        U16 np_able                     : 1;
        U16 lp_np_able                  : 1;
        U16 pd_fault                    : 1;
        U16 np_location                 : 1;
        U16 np_location_able            : 1;
        U16                             : 9;
    } bitc;
} GH_EPHY_ANER_S;

typedef union { /* EPHY_ANNPAR */
    U16 all;
    struct {
        U16 msg                         : 11;
        U16 toggle                      : 1;
        U16 ack2                        : 1;
        U16 mp                          : 1;
        U16                             : 1;
        U16 np                          : 1;
    } bitc;
} GH_EPHY_ANNPAR_S;

typedef union { /* EPHY_ANLPNP */
    U16 all;
    struct {
        U16 msg                         : 11;
        U16 toggle                      : 1;
        U16 ack2                        : 1;
        U16 mp                          : 1;
        U16                             : 1;
        U16 np                          : 1;
    } bitc;
} GH_EPHY_ANLPNP_S;

typedef union { /* EPHY_MMD_CONTROL */
    U16 all;
    struct {
        U16 devad                       : 5;
        U16                             : 9;
        U16 func                        : 2;
    } bitc;
} GH_EPHY_MMD_CONTROL_S;

typedef union { /* EPHY_AN_R_15 */
    U16 all;
    struct {
        U16                             : 12;
        U16 an_register_15              : 2;
        U16                             : 2;
    } bitc;
} GH_EPHY_AN_R_15_S;

typedef union { /* EPHY_WAVE_SHAPING_34 */
    U16 all;
    struct {
        U16 ltp_3                       : 8;
        U16 ltp_4                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_34_S;

typedef union { /* EPHY_WAVE_SHAPING_56 */
    U16 all;
    struct {
        U16 ltp_5                       : 8;
        U16 ltp_6                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_56_S;

typedef union { /* EPHY_WAVE_SHAPING_78 */
    U16 all;
    struct {
        U16 ltp_7                       : 8;
        U16 ltp_8                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_78_S;

typedef union { /* EPHY_WAVE_SHAPING_9A */
    U16 all;
    struct {
        U16 ltp_9                       : 8;
        U16 ltp_a                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_9A_S;

typedef union { /* EPHY_WAVE_SHAPING_BC */
    U16 all;
    struct {
        U16 ltp_b                       : 8;
        U16 ltp_c                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_BC_S;

typedef union { /* EPHY_WAVE_SHAPING_DE */
    U16 all;
    struct {
        U16 ltp_d                       : 8;
        U16 ltp_e                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_DE_S;

typedef union { /* EPHY_SPEED */
    U16 all;
    struct {
        U16 ltp_f                       : 8;
        U16 isolate                     : 1;
        U16 rptr                        : 1;
        U16 duplex                      : 1;
        U16 speed                       : 1;
        U16 ane                         : 1;
        U16 ldps                        : 1;
        U16 disable_eee_force           : 1;
        U16                             : 1;
    } bitc;
} GH_EPHY_SPEED_S;

typedef union { /* EPHY_LTP */
    U16 all;
    struct {
        U16 width                       : 4;
        U16 tx_gm_rctrl                 : 4;
        U16                             : 8;
    } bitc;
} GH_EPHY_LTP_S;

typedef union { /* EPHY_MCU */
    U16 all;
    struct {
        U16 en                          : 1;
        U16 mcu_rdy                     : 1;
        U16                             : 14;
    } bitc;
} GH_EPHY_MCU_S;

typedef union { /* EPHY_CODE_RAM */
    U16 all;
    struct {
        U16 start_addr                  : 16;
    } bitc;
} GH_EPHY_CODE_RAM_S;

typedef union { /* EPHY_CODE_RAM_W */
    U16 all;
    struct {
        U16 start_addr                  : 16;
    } bitc;
} GH_EPHY_CODE_RAM_W_S;

typedef union { /* EPHY_100M_LINK */
    U16 all;
    struct {
        U16 an_mcu_100t_link_control    : 2;
        U16 an_mcu_nlp_link_control     : 2;
        U16 nlp_frame_start_mode_en     : 1;
        U16 detect_100m                 : 1;
        U16 mcu_an_enable               : 1;
        U16 force_100m_link_good        : 1;
        U16 an_100t_link_status         : 2;
        U16 an_nlp_link_status          : 2;
        U16 mdio_disable                : 1;
        U16 mdc_edge_sel                : 1;
        U16 an_bypass_link_status_check : 1;
        U16 adc_loop                    : 1;
    } bitc;
} GH_EPHY_100M_LINK_S;

typedef union { /* EPHY_DEBUG */
    U16 all;
    struct {
        U16 snr_locked                  : 1;
        U16 snr_locked_raw              : 1;
        U16 sig_det_flag                : 1;
        U16 state_sync_on               : 1;
        U16 state_st_lk                 : 3;
        U16                             : 1;
        U16 mux_recov_cnt               : 6;
        U16 test_mux_sel                : 2;
    } bitc;
} GH_EPHY_DEBUG_S;

typedef union { /* EPHY_DEBUG_MODE */
    U16 all;
    struct {
        U16 signal                      : 8;
        U16 module                      : 8;
    } bitc;
} GH_EPHY_DEBUG_MODE_S;

typedef union { /* EPHY_RST_EN */
    U16 all;
    struct {
        U16 mau_srst                    : 1;
        U16 pls_srst                    : 1;
        U16 sqe_test_enable             : 1;
        U16 lpbk_enable                 : 1;
        U16 jabber_enable               : 1;
        U16 ser_polarity_correction     : 1;
        U16 por_stick_mode              : 1;
        U16 recv_bit_bucket             : 1;
        U16 rxclk_pol                   : 1;
        U16 txclk_pol                   : 1;
        U16 adc_input_sign              : 1;
        U16 mii_test_packet             : 1;
        U16 clear_rcvpack               : 1;
        U16 miiloop_en_10m              : 1;
        U16 mii_rxclk_pol               : 1;
        U16 mii_txclk_pol               : 1;
    } bitc;
} GH_EPHY_RST_EN_S;

typedef union { /* EPHY_SNR_K */
    U16 all;
    struct {
        U16 slice_up                    : 8;
        U16 snrchk_k1                   : 2;
        U16 snrchk_k2                   : 2;
        U16 snrchk_k3                   : 2;
        U16 gcr_ccpl_master_coarse_clkcc: 2;
    } bitc;
} GH_EPHY_SNR_K_S;

typedef union { /* EPHY_DET_MAX */
    U16 all;
    struct {
        U16 thrh_max_vga_coarse         : 8;
        U16 thrh_max_sig_det            : 8;
    } bitc;
} GH_EPHY_DET_MAX_S;

typedef union { /* EPHY_DET_MIN */
    U16 all;
    struct {
        U16 thrh_max_vga_fine           : 8;
        U16 thrh_min_sig_det            : 8;
    } bitc;
} GH_EPHY_DET_MIN_S;

typedef union { /* EPHY_SNR_LEN */
    U16 all;
    struct {
        U16 mcu_ctrl_dsp_fsm_state      : 8;
        U16 force_100m_en               : 1;
        U16 force_100m_snr_lock         : 1;
        U16 dsp_fsm_agc_en_mode_a       : 1;
        U16 cable_len_offset            : 2;
        U16                             : 3;
    } bitc;
} GH_EPHY_SNR_LEN_S;

typedef union { /* EPHY_LPF */
    U16 all;
    struct {
        U16 lpf_out_h                   : 10;
        U16 rxlpf_bwsel_10t             : 2;
        U16 rxlpf_bwsel_100t            : 2;
        U16 cable_length                : 2;
    } bitc;
} GH_EPHY_LPF_S;

typedef union { /* EPHY_ADC_GAIN_PGA */
    U16 all;
    struct {
        U16 adc_bp                      : 4;
        U16 dac10t_testen               : 1;
        U16 dac100t_testen              : 1;
        U16                             : 2;
        U16 adc_bma                     : 4;
        U16 adc_pd                      : 1;
        U16 region_bank_rd              : 1;
        U16 adcpll_ana_clken            : 1;
        U16 adcbin_testen               : 1;
    } bitc;
} GH_EPHY_ADC_GAIN_PGA_S;

typedef union { /* EPHY_ADC_GSHIFT */
    U16 all;
    struct {
        U16 adc_gshift                  : 2;
        U16 gain                        : 6;
        U16                             : 8;
    } bitc;
} GH_EPHY_ADC_GSHIFT_S;

typedef union { /* EPHY_ADC */
    U16 all;
    struct {
        U16 adc_bp                      : 4;
        U16 dac10t_testen               : 1;
        U16 reg_dac100t_testen          : 1;
        U16                             : 2;
        U16 adc_bma                     : 4;
        U16 adc_pd                      : 1;
        U16 region_bank_rd              : 1;
        U16 adcpll_ana_clken            : 1;
        U16 adcbin_testen               : 1;
    } bitc;
} GH_EPHY_ADC_S;

typedef union { /* EPHY_PLL_ADC_CTRL3 */
    U16 all;
    struct {
        U16                             : 8;
        U16 rxlpf_pd                    : 1;
        U16 tx_b_test                   : 6;
        U16                             : 1;
    } bitc;
} GH_EPHY_PLL_ADC_CTRL3_S;

typedef union { /* EPHY_RX_LPF */
    U16 all;
    struct {
        U16 rxlpf_ibsel                 : 4;
        U16 rxlpf_bwsel                 : 2;
        U16 unkown                      : 4;
        U16 rxlpf_cmsel                 : 1;
        U16 rxlpf_outp_test             : 1;
        U16 rxlpf_outm_test             : 1;
        U16 rxlpf_bypass                : 1;
        U16 ref_pd                      : 1;
        U16 ref_iint_pd                 : 1;
    } bitc;
} GH_EPHY_RX_LPF_S;

typedef union { /* EPHY_PLL_ADC_CTRL0 */
    U16 all;
    struct {
        U16 ro_adcpl_lock               : 1;
        U16 gcr_adcpl_div               : 3;
        U16 test_adcpl_extcksel         : 1;
        U16 ro_adcpl_high_flag          : 1;
        U16 pllclk_outen                : 1;
        U16 ov_ref_test                 : 1;
        U16 gc_adcpl_rstb               : 1;
        U16 ref_bgap_pd                 : 1;
        U16 adcraw_tst                  : 1;
        U16 adcraw_tst_sw               : 1;
        U16 ldo_pwrgd                   : 1;
        U16 adcraw_overflow             : 1;
        U16 adcpl_force_phase           : 1;
        U16 gcr_adcpl_tog_clkcc         : 1;
    } bitc;
} GH_EPHY_PLL_ADC_CTRL0_S;

typedef union { /* EPHY_PLL_ADC_CTRL1 */
    U16 all;
    struct {
        U16 gc_adcpl_adcpd0             : 1;
        U16 gc_adcpl_adcpd1             : 1;
        U16 gc_adcpl_ccpd0              : 1;
        U16 gc_adcpl_ccpd1              : 1;
        U16 pd_adcpl_reg                : 1;
        U16 gcr_adcpl_mod_100t          : 2;
        U16 gcr_adcpl_ictrl             : 3;
        U16 gcr_adcpl_enfrunz           : 1;
        U16 en_adcpl_porst              : 1;
        U16 en_adcpl_adcphdac           : 1;
        U16 gc_adcpl_adcselect          : 1;
        U16 tx_d_test                   : 2;
    } bitc;
} GH_EPHY_PLL_ADC_CTRL1_S;

typedef union { /* EPHY_PLL_ADC_CTRL2 */
    U16 all;
    struct {
        U16 gc_ref_vgen                 : 1;
        U16 gc_ref_vcom                 : 2;
        U16 gc_ref_vcmpcmvx             : 2;
        U16 pd_lpf_op                   : 1;
        U16 gc_adc_force1               : 1;
        U16 gc_adc_force0               : 1;
        U16 endiscz_10                  : 1;
        U16 gcr_adcpl_pdphadc           : 1;
        U16 adcpl_bank                  : 3;
        U16 adcpl_phase_force           : 1;
        U16 adcpl_phase_force_st        : 1;
        U16 adcpl_force_go              : 1;
    } bitc;
} GH_EPHY_PLL_ADC_CTRL2_S;

typedef union { /* EPHY_PWR */
    U16 all;
    struct {
        U16 pwr_k_in_lp                 : 3;
        U16 dtpwr_enable_lp             : 1;
        U16 gcr_adcpl_div_lp            : 3;
        U16 dummy                       : 9;
    } bitc;
} GH_EPHY_PWR_S;

typedef union { /* EPHY_ADC_DC */
    U16 all;
    struct {
        U16 dc_force_en                 : 1;
        U16 dc_force                    : 4;
        U16 dc_can_inv                  : 1;
        U16 analog_blw                  : 1;
        U16 dc_k                        : 2;
        U16 srst                        : 1;
        U16 adc_cancel_out              : 4;
        U16 adc_cancel_disable          : 1;
        U16 adc_start                   : 1;
    } bitc;
} GH_EPHY_ADC_DC_S;

typedef union { /* EPHY_ADCPL */
    U16 all;
    struct {
        U16 mod_10t                     : 2;
        U16 mod                         : 2;
        U16 mod_lp                      : 2;
        U16 adc_frc_zero                : 3;
        U16 adcpl_step                  : 4;
        U16 ac_a_timer_start            : 1;
        U16 ac_sample_timer_start       : 1;
        U16 txramp_gen_10t              : 1;
    } bitc;
} GH_EPHY_ADCPL_S;

typedef union { /* EPHY_LDO */
    U16 all;
    struct {
        U16 dummy                       : 16;
    } bitc;
} GH_EPHY_LDO_S;

typedef union { /* EPHY_CLK_GATE */
    U16 all;
    struct {
        U16 eee_capability              : 16;
    } bitc;
} GH_EPHY_CLK_GATE_S;

typedef union { /* EPHY_CLK1 */
    U16 all;
    struct {
        U16 unkown                      : 4;
        U16 clko_200_gat                : 1;
        U16 clko_200_inv                : 1;
        U16 lut_new                     : 1;
        U16                             : 9;
    } bitc;
} GH_EPHY_CLK1_S;

typedef union { /* EPHY_GCR_TX */
    U16 all;
    struct {
        U16 ioffset_sel                 : 1;
        U16                             : 3;
        U16 ld_vcmo                     : 2;
        U16 ph_delay                    : 2;
        U16 phase_100t                  : 1;
        U16 ld_iq_sel                   : 2;
        U16 ld_iq_ibias                 : 2;
        U16 en_tx_ioffset               : 1;
        U16 save2x_tx                   : 1;
        U16 wssel_inv                   : 1;
    } bitc;
} GH_EPHY_GCR_TX_S;

typedef union { /* EPHY_POWER */
    U16 all;
    struct {
        U16 pd_tx_ld                    : 1;
        U16 pd_tx_idac                  : 1;
        U16 pd_dacramp_new              : 1;
        U16 pd_dacnew_testen            : 1;
        U16 pd_tx_ld_10t                : 1;
        U16 pd_tx_ld_100t               : 1;
        U16 pd_tx_ld_lp                 : 1;
        U16 pd_tx_idac_10t              : 1;
        U16 pd_tx_idac_100t             : 1;
        U16 pd_tx_idac_lp               : 1;
        U16                             : 6;
    } bitc;
} GH_EPHY_POWER_S;

typedef union { /* EPHY_MDIIO */
    U16 all;
    struct {
        U16                             : 4;
        U16 mdio_idle_error_cnt_clear   : 1;
        U16                             : 7;
        U16 pd_vbuf                     : 1;
        U16                             : 3;
    } bitc;
} GH_EPHY_MDIIO_S;

typedef union { /* EPHY_CLK0 */
    U16 all;
    struct {
        U16 lpi_tx_tq_timer_msb         : 6;
        U16                             : 7;
        U16 clko_125_inv                : 1;
        U16 clko_100_gat                : 1;
        U16 clko_100_inv                : 1;
    } bitc;
} GH_EPHY_CLK0_S;

typedef union { /* EPHY_WAVE_CTRL */
    U16 all;
    struct {
        U16 shadow                      : 3;
        U16                             : 13;
    } bitc;
} GH_EPHY_WAVE_CTRL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register EPHY_MII_RMII (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_MII_RMII'. */
void GH_EPHY_set_MII_RMII(U32 data);
/*! \brief Reads the register 'EPHY_MII_RMII'. */
U32  GH_EPHY_get_MII_RMII(void);
/*! \brief Writes the bit group 'USB_TM1' of register 'EPHY_MII_RMII'. */
void GH_EPHY_set_MII_RMII_USB_TM1(U8 data);
/*! \brief Reads the bit group 'USB_TM1' of register 'EPHY_MII_RMII'. */
U8   GH_EPHY_get_MII_RMII_USB_TM1(void);
/*! \brief Writes the bit group 'rmii' of register 'EPHY_MII_RMII'. */
void GH_EPHY_set_MII_RMII_rmii(U8 data);
/*! \brief Reads the bit group 'rmii' of register 'EPHY_MII_RMII'. */
U8   GH_EPHY_get_MII_RMII_rmii(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_MII_RMII(U32 data)
{
    *(volatile U32 *)REG_EPHY_MII_RMII = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MII_RMII] <-- 0x%08x\n",
                        REG_EPHY_MII_RMII,data,data);
    #endif
}
GH_INLINE U32  GH_EPHY_get_MII_RMII(void)
{
    U32 value = (*(volatile U32 *)REG_EPHY_MII_RMII);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MII_RMII] --> 0x%08x\n",
                        REG_EPHY_MII_RMII,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_MII_RMII_USB_TM1(U8 data)
{
    GH_EPHY_MII_RMII_S d;
    d.all = *(volatile U32 *)REG_EPHY_MII_RMII;
    d.bitc.usb_tm1 = data;
    *(volatile U32 *)REG_EPHY_MII_RMII = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MII_RMII_USB_TM1] <-- 0x%08x\n",
                        REG_EPHY_MII_RMII,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_MII_RMII_USB_TM1(void)
{
    GH_EPHY_MII_RMII_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EPHY_MII_RMII);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MII_RMII_USB_TM1] --> 0x%08x\n",
                        REG_EPHY_MII_RMII,value);
    #endif
    return tmp_value.bitc.usb_tm1;
}
GH_INLINE void GH_EPHY_set_MII_RMII_rmii(U8 data)
{
    GH_EPHY_MII_RMII_S d;
    d.all = *(volatile U32 *)REG_EPHY_MII_RMII;
    d.bitc.rmii = data;
    *(volatile U32 *)REG_EPHY_MII_RMII = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MII_RMII_rmii] <-- 0x%08x\n",
                        REG_EPHY_MII_RMII,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_MII_RMII_rmii(void)
{
    GH_EPHY_MII_RMII_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EPHY_MII_RMII);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MII_RMII_rmii] --> 0x%08x\n",
                        REG_EPHY_MII_RMII,value);
    #endif
    return tmp_value.bitc.rmii;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_CONTROL (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL(U16 data);
/*! \brief Reads the register 'EPHY_CONTROL'. */
U16  GH_EPHY_get_CONTROL(void);
/*! \brief Writes the bit group 'mii_ctl_unidirectional_enable' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_unidirectional_enable(U8 data);
/*! \brief Reads the bit group 'mii_ctl_unidirectional_enable' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_unidirectional_enable(void);
/*! \brief Writes the bit group 'mii_ctl_speed_sel_msb' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_speed_sel_msb(U8 data);
/*! \brief Reads the bit group 'mii_ctl_speed_sel_msb' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_speed_sel_msb(void);
/*! \brief Writes the bit group 'mii_ctl_col_test' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_col_test(U8 data);
/*! \brief Reads the bit group 'mii_ctl_col_test' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_col_test(void);
/*! \brief Writes the bit group 'mii_ctl_duplex_mode' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_duplex_mode(U8 data);
/*! \brief Reads the bit group 'mii_ctl_duplex_mode' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_duplex_mode(void);
/*! \brief Writes the bit group 'mii_ctl_restart_an' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_restart_an(U8 data);
/*! \brief Reads the bit group 'mii_ctl_restart_an' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_restart_an(void);
/*! \brief Writes the bit group 'mii_ctl_isolate' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_isolate(U8 data);
/*! \brief Reads the bit group 'mii_ctl_isolate' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_isolate(void);
/*! \brief Writes the bit group 'mii_ctl_power_down' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_power_down(U8 data);
/*! \brief Reads the bit group 'mii_ctl_power_down' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_power_down(void);
/*! \brief Writes the bit group 'mii_ctl_an_en' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_an_en(U8 data);
/*! \brief Reads the bit group 'mii_ctl_an_en' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_an_en(void);
/*! \brief Writes the bit group 'mii_ctl_speed_sel_lsb' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_speed_sel_lsb(U8 data);
/*! \brief Reads the bit group 'mii_ctl_speed_sel_lsb' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_speed_sel_lsb(void);
/*! \brief Writes the bit group 'mii_ctl_loopback' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_loopback(U8 data);
/*! \brief Reads the bit group 'mii_ctl_loopback' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_loopback(void);
/*! \brief Writes the bit group 'mii_ctl_reset' of register 'EPHY_CONTROL'. */
void GH_EPHY_set_CONTROL_mii_ctl_reset(U8 data);
/*! \brief Reads the bit group 'mii_ctl_reset' of register 'EPHY_CONTROL'. */
U8   GH_EPHY_get_CONTROL_mii_ctl_reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_CONTROL(U16 data)
{
    *(volatile U16 *)REG_EPHY_CONTROL = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_CONTROL(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_unidirectional_enable(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_unidirectional_enable = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_unidirectional_enable] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_unidirectional_enable(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_unidirectional_enable] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_unidirectional_enable;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_speed_sel_msb(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_speed_sel_msb = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_speed_sel_msb] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_speed_sel_msb(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_speed_sel_msb] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_speed_sel_msb;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_col_test(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_col_test = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_col_test] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_col_test(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_col_test] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_col_test;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_duplex_mode(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_duplex_mode = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_duplex_mode] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_duplex_mode(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_duplex_mode] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_duplex_mode;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_restart_an(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_restart_an = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_restart_an] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_restart_an(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_restart_an] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_restart_an;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_isolate(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_isolate = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_isolate] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_isolate(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_isolate] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_isolate;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_power_down(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_power_down = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_power_down] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_power_down(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_power_down] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_power_down;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_an_en(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_an_en = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_an_en] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_an_en(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_an_en] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_an_en;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_speed_sel_lsb(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_speed_sel_lsb = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_speed_sel_lsb] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_speed_sel_lsb(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_speed_sel_lsb] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_speed_sel_lsb;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_loopback(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_loopback = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_loopback] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_loopback(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_loopback] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_loopback;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_reset(U8 data)
{
    GH_EPHY_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL;
    d.bitc.mii_ctl_reset = data;
    *(volatile U16 *)REG_EPHY_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CONTROL_mii_ctl_reset] <-- 0x%08x\n",
                        REG_EPHY_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_reset(void)
{
    GH_EPHY_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CONTROL_mii_ctl_reset] --> 0x%08x\n",
                        REG_EPHY_CONTROL,value);
    #endif
    return tmp_value.bitc.mii_ctl_reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_STATUS (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'EPHY_STATUS'. */
U16  GH_EPHY_get_STATUS(void);
/*! \brief Reads the bit group 'extended_capability' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_extended_capability(void);
/*! \brief Reads the bit group 'jabber_detect' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_jabber_detect(void);
/*! \brief Reads the bit group 'link_status' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_link_status(void);
/*! \brief Reads the bit group 'an_ability' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_an_ability(void);
/*! \brief Reads the bit group 'rf' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_rf(void);
/*! \brief Reads the bit group 'an_complete' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_an_complete(void);
/*! \brief Reads the bit group 'mf_preamble_suppression' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_mf_preamble_suppression(void);
/*! \brief Reads the bit group 'unidirectional_ability' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_unidirectional_ability(void);
/*! \brief Reads the bit group 'extended_status' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_extended_status(void);
/*! \brief Reads the bit group 'half_duplex_100t2' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_half_duplex_100t2(void);
/*! \brief Reads the bit group 'full_duplex_100t2' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_full_duplex_100t2(void);
/*! \brief Reads the bit group 'half_duplex_10' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_half_duplex_10(void);
/*! \brief Reads the bit group 'full_duplex_10' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_full_duplex_10(void);
/*! \brief Reads the bit group 'half_duplex_100x' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_half_duplex_100x(void);
/*! \brief Reads the bit group 'full_duplex_100x' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_full_duplex_100x(void);
/*! \brief Reads the bit group 't4_100' of register 'EPHY_STATUS'. */
U8   GH_EPHY_get_STATUS_t4_100(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_EPHY_get_STATUS(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return value;
}
GH_INLINE U8   GH_EPHY_get_STATUS_extended_capability(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_extended_capability] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.extended_capability;
}
GH_INLINE U8   GH_EPHY_get_STATUS_jabber_detect(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_jabber_detect] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.jabber_detect;
}
GH_INLINE U8   GH_EPHY_get_STATUS_link_status(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_link_status] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.link_status;
}
GH_INLINE U8   GH_EPHY_get_STATUS_an_ability(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_an_ability] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.an_ability;
}
GH_INLINE U8   GH_EPHY_get_STATUS_rf(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_rf] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.rf;
}
GH_INLINE U8   GH_EPHY_get_STATUS_an_complete(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_an_complete] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.an_complete;
}
GH_INLINE U8   GH_EPHY_get_STATUS_mf_preamble_suppression(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_mf_preamble_suppression] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.mf_preamble_suppression;
}
GH_INLINE U8   GH_EPHY_get_STATUS_unidirectional_ability(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_unidirectional_ability] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.unidirectional_ability;
}
GH_INLINE U8   GH_EPHY_get_STATUS_extended_status(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_extended_status] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.extended_status;
}
GH_INLINE U8   GH_EPHY_get_STATUS_half_duplex_100t2(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_half_duplex_100t2] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.half_duplex_100t2;
}
GH_INLINE U8   GH_EPHY_get_STATUS_full_duplex_100t2(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_full_duplex_100t2] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.full_duplex_100t2;
}
GH_INLINE U8   GH_EPHY_get_STATUS_half_duplex_10(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_half_duplex_10] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.half_duplex_10;
}
GH_INLINE U8   GH_EPHY_get_STATUS_full_duplex_10(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_full_duplex_10] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.full_duplex_10;
}
GH_INLINE U8   GH_EPHY_get_STATUS_half_duplex_100x(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_half_duplex_100x] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.half_duplex_100x;
}
GH_INLINE U8   GH_EPHY_get_STATUS_full_duplex_100x(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_full_duplex_100x] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.full_duplex_100x;
}
GH_INLINE U8   GH_EPHY_get_STATUS_t4_100(void)
{
    GH_EPHY_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_STATUS_t4_100] --> 0x%08x\n",
                        REG_EPHY_STATUS,value);
    #endif
    return tmp_value.bitc.t4_100;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ID1 (read)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'EPHY_ID1'. */
U16  GH_EPHY_get_ID1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_EPHY_get_ID1(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ID1);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ID1] --> 0x%08x\n",
                        REG_EPHY_ID1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ID2 (read)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'EPHY_ID2'. */
U16  GH_EPHY_get_ID2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_EPHY_get_ID2(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ID2);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ID2] --> 0x%08x\n",
                        REG_EPHY_ID2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ANAR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_ANAR'. */
void GH_EPHY_set_ANAR(U16 data);
/*! \brief Reads the register 'EPHY_ANAR'. */
U16  GH_EPHY_get_ANAR(void);
/*! \brief Writes the bit group 'selector' of register 'EPHY_ANAR'. */
void GH_EPHY_set_ANAR_selector(U8 data);
/*! \brief Reads the bit group 'selector' of register 'EPHY_ANAR'. */
U8   GH_EPHY_get_ANAR_selector(void);
/*! \brief Writes the bit group 'tech_ability' of register 'EPHY_ANAR'. */
void GH_EPHY_set_ANAR_tech_ability(U8 data);
/*! \brief Reads the bit group 'tech_ability' of register 'EPHY_ANAR'. */
U8   GH_EPHY_get_ANAR_tech_ability(void);
/*! \brief Writes the bit group 'rf' of register 'EPHY_ANAR'. */
void GH_EPHY_set_ANAR_rf(U8 data);
/*! \brief Reads the bit group 'rf' of register 'EPHY_ANAR'. */
U8   GH_EPHY_get_ANAR_rf(void);
/*! \brief Writes the bit group 'np' of register 'EPHY_ANAR'. */
void GH_EPHY_set_ANAR_np(U8 data);
/*! \brief Reads the bit group 'np' of register 'EPHY_ANAR'. */
U8   GH_EPHY_get_ANAR_np(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_ANAR(U16 data)
{
    *(volatile U16 *)REG_EPHY_ANAR = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANAR] <-- 0x%08x\n",
                        REG_EPHY_ANAR,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_ANAR(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ANAR);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANAR] --> 0x%08x\n",
                        REG_EPHY_ANAR,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_ANAR_selector(U8 data)
{
    GH_EPHY_ANAR_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANAR;
    d.bitc.selector = data;
    *(volatile U16 *)REG_EPHY_ANAR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANAR_selector] <-- 0x%08x\n",
                        REG_EPHY_ANAR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANAR_selector(void)
{
    GH_EPHY_ANAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANAR_selector] --> 0x%08x\n",
                        REG_EPHY_ANAR,value);
    #endif
    return tmp_value.bitc.selector;
}
GH_INLINE void GH_EPHY_set_ANAR_tech_ability(U8 data)
{
    GH_EPHY_ANAR_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANAR;
    d.bitc.tech_ability = data;
    *(volatile U16 *)REG_EPHY_ANAR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANAR_tech_ability] <-- 0x%08x\n",
                        REG_EPHY_ANAR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANAR_tech_ability(void)
{
    GH_EPHY_ANAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANAR_tech_ability] --> 0x%08x\n",
                        REG_EPHY_ANAR,value);
    #endif
    return tmp_value.bitc.tech_ability;
}
GH_INLINE void GH_EPHY_set_ANAR_rf(U8 data)
{
    GH_EPHY_ANAR_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANAR;
    d.bitc.rf = data;
    *(volatile U16 *)REG_EPHY_ANAR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANAR_rf] <-- 0x%08x\n",
                        REG_EPHY_ANAR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANAR_rf(void)
{
    GH_EPHY_ANAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANAR_rf] --> 0x%08x\n",
                        REG_EPHY_ANAR,value);
    #endif
    return tmp_value.bitc.rf;
}
GH_INLINE void GH_EPHY_set_ANAR_np(U8 data)
{
    GH_EPHY_ANAR_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANAR;
    d.bitc.np = data;
    *(volatile U16 *)REG_EPHY_ANAR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANAR_np] <-- 0x%08x\n",
                        REG_EPHY_ANAR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANAR_np(void)
{
    GH_EPHY_ANAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANAR_np] --> 0x%08x\n",
                        REG_EPHY_ANAR,value);
    #endif
    return tmp_value.bitc.np;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ANLPAR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'EPHY_ANLPAR'. */
U16  GH_EPHY_get_ANLPAR(void);
/*! \brief Reads the bit group 'selector' of register 'EPHY_ANLPAR'. */
U8   GH_EPHY_get_ANLPAR_selector(void);
/*! \brief Reads the bit group 'tech_ability' of register 'EPHY_ANLPAR'. */
U8   GH_EPHY_get_ANLPAR_tech_ability(void);
/*! \brief Reads the bit group 'rf' of register 'EPHY_ANLPAR'. */
U8   GH_EPHY_get_ANLPAR_rf(void);
/*! \brief Reads the bit group 'ack' of register 'EPHY_ANLPAR'. */
U8   GH_EPHY_get_ANLPAR_ack(void);
/*! \brief Reads the bit group 'np' of register 'EPHY_ANLPAR'. */
U8   GH_EPHY_get_ANLPAR_np(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_EPHY_get_ANLPAR(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPAR] --> 0x%08x\n",
                        REG_EPHY_ANLPAR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_selector(void)
{
    GH_EPHY_ANLPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPAR_selector] --> 0x%08x\n",
                        REG_EPHY_ANLPAR,value);
    #endif
    return tmp_value.bitc.selector;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_tech_ability(void)
{
    GH_EPHY_ANLPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPAR_tech_ability] --> 0x%08x\n",
                        REG_EPHY_ANLPAR,value);
    #endif
    return tmp_value.bitc.tech_ability;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_rf(void)
{
    GH_EPHY_ANLPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPAR_rf] --> 0x%08x\n",
                        REG_EPHY_ANLPAR,value);
    #endif
    return tmp_value.bitc.rf;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_ack(void)
{
    GH_EPHY_ANLPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPAR_ack] --> 0x%08x\n",
                        REG_EPHY_ANLPAR,value);
    #endif
    return tmp_value.bitc.ack;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_np(void)
{
    GH_EPHY_ANLPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPAR_np] --> 0x%08x\n",
                        REG_EPHY_ANLPAR,value);
    #endif
    return tmp_value.bitc.np;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ANER (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_ANER'. */
void GH_EPHY_set_ANER(U16 data);
/*! \brief Reads the register 'EPHY_ANER'. */
U16  GH_EPHY_get_ANER(void);
/*! \brief Writes the bit group 'lp_an_able' of register 'EPHY_ANER'. */
void GH_EPHY_set_ANER_lp_an_able(U8 data);
/*! \brief Reads the bit group 'lp_an_able' of register 'EPHY_ANER'. */
U8   GH_EPHY_get_ANER_lp_an_able(void);
/*! \brief Writes the bit group 'page_rec' of register 'EPHY_ANER'. */
void GH_EPHY_set_ANER_page_rec(U8 data);
/*! \brief Reads the bit group 'page_rec' of register 'EPHY_ANER'. */
U8   GH_EPHY_get_ANER_page_rec(void);
/*! \brief Writes the bit group 'np_able' of register 'EPHY_ANER'. */
void GH_EPHY_set_ANER_np_able(U8 data);
/*! \brief Reads the bit group 'np_able' of register 'EPHY_ANER'. */
U8   GH_EPHY_get_ANER_np_able(void);
/*! \brief Writes the bit group 'lp_np_able' of register 'EPHY_ANER'. */
void GH_EPHY_set_ANER_lp_np_able(U8 data);
/*! \brief Reads the bit group 'lp_np_able' of register 'EPHY_ANER'. */
U8   GH_EPHY_get_ANER_lp_np_able(void);
/*! \brief Writes the bit group 'pd_fault' of register 'EPHY_ANER'. */
void GH_EPHY_set_ANER_pd_fault(U8 data);
/*! \brief Reads the bit group 'pd_fault' of register 'EPHY_ANER'. */
U8   GH_EPHY_get_ANER_pd_fault(void);
/*! \brief Writes the bit group 'np_location' of register 'EPHY_ANER'. */
void GH_EPHY_set_ANER_np_location(U8 data);
/*! \brief Reads the bit group 'np_location' of register 'EPHY_ANER'. */
U8   GH_EPHY_get_ANER_np_location(void);
/*! \brief Writes the bit group 'np_location_able' of register 'EPHY_ANER'. */
void GH_EPHY_set_ANER_np_location_able(U8 data);
/*! \brief Reads the bit group 'np_location_able' of register 'EPHY_ANER'. */
U8   GH_EPHY_get_ANER_np_location_able(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_ANER(U16 data)
{
    *(volatile U16 *)REG_EPHY_ANER = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANER] <-- 0x%08x\n",
                        REG_EPHY_ANER,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_ANER(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ANER);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANER] --> 0x%08x\n",
                        REG_EPHY_ANER,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_ANER_lp_an_able(U8 data)
{
    GH_EPHY_ANER_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER;
    d.bitc.lp_an_able = data;
    *(volatile U16 *)REG_EPHY_ANER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANER_lp_an_able] <-- 0x%08x\n",
                        REG_EPHY_ANER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANER_lp_an_able(void)
{
    GH_EPHY_ANER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANER_lp_an_able] --> 0x%08x\n",
                        REG_EPHY_ANER,value);
    #endif
    return tmp_value.bitc.lp_an_able;
}
GH_INLINE void GH_EPHY_set_ANER_page_rec(U8 data)
{
    GH_EPHY_ANER_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER;
    d.bitc.page_rec = data;
    *(volatile U16 *)REG_EPHY_ANER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANER_page_rec] <-- 0x%08x\n",
                        REG_EPHY_ANER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANER_page_rec(void)
{
    GH_EPHY_ANER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANER_page_rec] --> 0x%08x\n",
                        REG_EPHY_ANER,value);
    #endif
    return tmp_value.bitc.page_rec;
}
GH_INLINE void GH_EPHY_set_ANER_np_able(U8 data)
{
    GH_EPHY_ANER_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER;
    d.bitc.np_able = data;
    *(volatile U16 *)REG_EPHY_ANER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANER_np_able] <-- 0x%08x\n",
                        REG_EPHY_ANER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANER_np_able(void)
{
    GH_EPHY_ANER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANER_np_able] --> 0x%08x\n",
                        REG_EPHY_ANER,value);
    #endif
    return tmp_value.bitc.np_able;
}
GH_INLINE void GH_EPHY_set_ANER_lp_np_able(U8 data)
{
    GH_EPHY_ANER_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER;
    d.bitc.lp_np_able = data;
    *(volatile U16 *)REG_EPHY_ANER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANER_lp_np_able] <-- 0x%08x\n",
                        REG_EPHY_ANER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANER_lp_np_able(void)
{
    GH_EPHY_ANER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANER_lp_np_able] --> 0x%08x\n",
                        REG_EPHY_ANER,value);
    #endif
    return tmp_value.bitc.lp_np_able;
}
GH_INLINE void GH_EPHY_set_ANER_pd_fault(U8 data)
{
    GH_EPHY_ANER_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER;
    d.bitc.pd_fault = data;
    *(volatile U16 *)REG_EPHY_ANER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANER_pd_fault] <-- 0x%08x\n",
                        REG_EPHY_ANER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANER_pd_fault(void)
{
    GH_EPHY_ANER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANER_pd_fault] --> 0x%08x\n",
                        REG_EPHY_ANER,value);
    #endif
    return tmp_value.bitc.pd_fault;
}
GH_INLINE void GH_EPHY_set_ANER_np_location(U8 data)
{
    GH_EPHY_ANER_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER;
    d.bitc.np_location = data;
    *(volatile U16 *)REG_EPHY_ANER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANER_np_location] <-- 0x%08x\n",
                        REG_EPHY_ANER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANER_np_location(void)
{
    GH_EPHY_ANER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANER_np_location] --> 0x%08x\n",
                        REG_EPHY_ANER,value);
    #endif
    return tmp_value.bitc.np_location;
}
GH_INLINE void GH_EPHY_set_ANER_np_location_able(U8 data)
{
    GH_EPHY_ANER_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER;
    d.bitc.np_location_able = data;
    *(volatile U16 *)REG_EPHY_ANER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANER_np_location_able] <-- 0x%08x\n",
                        REG_EPHY_ANER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANER_np_location_able(void)
{
    GH_EPHY_ANER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANER_np_location_able] --> 0x%08x\n",
                        REG_EPHY_ANER,value);
    #endif
    return tmp_value.bitc.np_location_able;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ANNPAR (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_ANNPAR'. */
void GH_EPHY_set_ANNPAR(U16 data);
/*! \brief Reads the register 'EPHY_ANNPAR'. */
U16  GH_EPHY_get_ANNPAR(void);
/*! \brief Writes the bit group 'msg' of register 'EPHY_ANNPAR'. */
void GH_EPHY_set_ANNPAR_msg(U16 data);
/*! \brief Reads the bit group 'msg' of register 'EPHY_ANNPAR'. */
U16  GH_EPHY_get_ANNPAR_msg(void);
/*! \brief Writes the bit group 'toggle' of register 'EPHY_ANNPAR'. */
void GH_EPHY_set_ANNPAR_toggle(U8 data);
/*! \brief Reads the bit group 'toggle' of register 'EPHY_ANNPAR'. */
U8   GH_EPHY_get_ANNPAR_toggle(void);
/*! \brief Writes the bit group 'ack2' of register 'EPHY_ANNPAR'. */
void GH_EPHY_set_ANNPAR_ack2(U8 data);
/*! \brief Reads the bit group 'ack2' of register 'EPHY_ANNPAR'. */
U8   GH_EPHY_get_ANNPAR_ack2(void);
/*! \brief Writes the bit group 'mp' of register 'EPHY_ANNPAR'. */
void GH_EPHY_set_ANNPAR_mp(U8 data);
/*! \brief Reads the bit group 'mp' of register 'EPHY_ANNPAR'. */
U8   GH_EPHY_get_ANNPAR_mp(void);
/*! \brief Writes the bit group 'np' of register 'EPHY_ANNPAR'. */
void GH_EPHY_set_ANNPAR_np(U8 data);
/*! \brief Reads the bit group 'np' of register 'EPHY_ANNPAR'. */
U8   GH_EPHY_get_ANNPAR_np(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_ANNPAR(U16 data)
{
    *(volatile U16 *)REG_EPHY_ANNPAR = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANNPAR] <-- 0x%08x\n",
                        REG_EPHY_ANNPAR,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_ANNPAR(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANNPAR] --> 0x%08x\n",
                        REG_EPHY_ANNPAR,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_ANNPAR_msg(U16 data)
{
    GH_EPHY_ANNPAR_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR;
    d.bitc.msg = data;
    *(volatile U16 *)REG_EPHY_ANNPAR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANNPAR_msg] <-- 0x%08x\n",
                        REG_EPHY_ANNPAR,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_EPHY_get_ANNPAR_msg(void)
{
    GH_EPHY_ANNPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANNPAR_msg] --> 0x%08x\n",
                        REG_EPHY_ANNPAR,value);
    #endif
    return tmp_value.bitc.msg;
}
GH_INLINE void GH_EPHY_set_ANNPAR_toggle(U8 data)
{
    GH_EPHY_ANNPAR_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR;
    d.bitc.toggle = data;
    *(volatile U16 *)REG_EPHY_ANNPAR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANNPAR_toggle] <-- 0x%08x\n",
                        REG_EPHY_ANNPAR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANNPAR_toggle(void)
{
    GH_EPHY_ANNPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANNPAR_toggle] --> 0x%08x\n",
                        REG_EPHY_ANNPAR,value);
    #endif
    return tmp_value.bitc.toggle;
}
GH_INLINE void GH_EPHY_set_ANNPAR_ack2(U8 data)
{
    GH_EPHY_ANNPAR_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR;
    d.bitc.ack2 = data;
    *(volatile U16 *)REG_EPHY_ANNPAR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANNPAR_ack2] <-- 0x%08x\n",
                        REG_EPHY_ANNPAR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANNPAR_ack2(void)
{
    GH_EPHY_ANNPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANNPAR_ack2] --> 0x%08x\n",
                        REG_EPHY_ANNPAR,value);
    #endif
    return tmp_value.bitc.ack2;
}
GH_INLINE void GH_EPHY_set_ANNPAR_mp(U8 data)
{
    GH_EPHY_ANNPAR_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR;
    d.bitc.mp = data;
    *(volatile U16 *)REG_EPHY_ANNPAR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANNPAR_mp] <-- 0x%08x\n",
                        REG_EPHY_ANNPAR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANNPAR_mp(void)
{
    GH_EPHY_ANNPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANNPAR_mp] --> 0x%08x\n",
                        REG_EPHY_ANNPAR,value);
    #endif
    return tmp_value.bitc.mp;
}
GH_INLINE void GH_EPHY_set_ANNPAR_np(U8 data)
{
    GH_EPHY_ANNPAR_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR;
    d.bitc.np = data;
    *(volatile U16 *)REG_EPHY_ANNPAR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ANNPAR_np] <-- 0x%08x\n",
                        REG_EPHY_ANNPAR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ANNPAR_np(void)
{
    GH_EPHY_ANNPAR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANNPAR_np] --> 0x%08x\n",
                        REG_EPHY_ANNPAR,value);
    #endif
    return tmp_value.bitc.np;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ANLPNP (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'EPHY_ANLPNP'. */
U16  GH_EPHY_get_ANLPNP(void);
/*! \brief Reads the bit group 'msg' of register 'EPHY_ANLPNP'. */
U16  GH_EPHY_get_ANLPNP_msg(void);
/*! \brief Reads the bit group 'toggle' of register 'EPHY_ANLPNP'. */
U8   GH_EPHY_get_ANLPNP_toggle(void);
/*! \brief Reads the bit group 'ack2' of register 'EPHY_ANLPNP'. */
U8   GH_EPHY_get_ANLPNP_ack2(void);
/*! \brief Reads the bit group 'mp' of register 'EPHY_ANLPNP'. */
U8   GH_EPHY_get_ANLPNP_mp(void);
/*! \brief Reads the bit group 'np' of register 'EPHY_ANLPNP'. */
U8   GH_EPHY_get_ANLPNP_np(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_EPHY_get_ANLPNP(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPNP] --> 0x%08x\n",
                        REG_EPHY_ANLPNP,value);
    #endif
    return value;
}
GH_INLINE U16  GH_EPHY_get_ANLPNP_msg(void)
{
    GH_EPHY_ANLPNP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPNP_msg] --> 0x%08x\n",
                        REG_EPHY_ANLPNP,value);
    #endif
    return tmp_value.bitc.msg;
}
GH_INLINE U8   GH_EPHY_get_ANLPNP_toggle(void)
{
    GH_EPHY_ANLPNP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPNP_toggle] --> 0x%08x\n",
                        REG_EPHY_ANLPNP,value);
    #endif
    return tmp_value.bitc.toggle;
}
GH_INLINE U8   GH_EPHY_get_ANLPNP_ack2(void)
{
    GH_EPHY_ANLPNP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPNP_ack2] --> 0x%08x\n",
                        REG_EPHY_ANLPNP,value);
    #endif
    return tmp_value.bitc.ack2;
}
GH_INLINE U8   GH_EPHY_get_ANLPNP_mp(void)
{
    GH_EPHY_ANLPNP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPNP_mp] --> 0x%08x\n",
                        REG_EPHY_ANLPNP,value);
    #endif
    return tmp_value.bitc.mp;
}
GH_INLINE U8   GH_EPHY_get_ANLPNP_np(void)
{
    GH_EPHY_ANLPNP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ANLPNP_np] --> 0x%08x\n",
                        REG_EPHY_ANLPNP,value);
    #endif
    return tmp_value.bitc.np;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_MS_CONTROL (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_MS_CONTROL'. */
void GH_EPHY_set_MS_CONTROL(U16 data);
/*! \brief Reads the register 'EPHY_MS_CONTROL'. */
U16  GH_EPHY_get_MS_CONTROL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_MS_CONTROL(U16 data)
{
    *(volatile U16 *)REG_EPHY_MS_CONTROL = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MS_CONTROL] <-- 0x%08x\n",
                        REG_EPHY_MS_CONTROL,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_MS_CONTROL(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_MS_CONTROL);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MS_CONTROL] --> 0x%08x\n",
                        REG_EPHY_MS_CONTROL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_MS_STATUS (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'EPHY_MS_STATUS'. */
U16  GH_EPHY_get_MS_STATUS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_EPHY_get_MS_STATUS(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_MS_STATUS);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MS_STATUS] --> 0x%08x\n",
                        REG_EPHY_MS_STATUS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_PSE_CONTROL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_PSE_CONTROL'. */
void GH_EPHY_set_PSE_CONTROL(U16 data);
/*! \brief Reads the register 'EPHY_PSE_CONTROL'. */
U16  GH_EPHY_get_PSE_CONTROL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_PSE_CONTROL(U16 data)
{
    *(volatile U16 *)REG_EPHY_PSE_CONTROL = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PSE_CONTROL] <-- 0x%08x\n",
                        REG_EPHY_PSE_CONTROL,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_PSE_CONTROL(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_PSE_CONTROL);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PSE_CONTROL] --> 0x%08x\n",
                        REG_EPHY_PSE_CONTROL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_PSE_STATUS (read)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'EPHY_PSE_STATUS'. */
U16  GH_EPHY_get_PSE_STATUS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_EPHY_get_PSE_STATUS(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_PSE_STATUS);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PSE_STATUS] --> 0x%08x\n",
                        REG_EPHY_PSE_STATUS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_MMD_CONTROL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_MMD_CONTROL'. */
void GH_EPHY_set_MMD_CONTROL(U16 data);
/*! \brief Reads the register 'EPHY_MMD_CONTROL'. */
U16  GH_EPHY_get_MMD_CONTROL(void);
/*! \brief Writes the bit group 'devad' of register 'EPHY_MMD_CONTROL'. */
void GH_EPHY_set_MMD_CONTROL_devad(U8 data);
/*! \brief Reads the bit group 'devad' of register 'EPHY_MMD_CONTROL'. */
U8   GH_EPHY_get_MMD_CONTROL_devad(void);
/*! \brief Writes the bit group 'func' of register 'EPHY_MMD_CONTROL'. */
void GH_EPHY_set_MMD_CONTROL_func(U8 data);
/*! \brief Reads the bit group 'func' of register 'EPHY_MMD_CONTROL'. */
U8   GH_EPHY_get_MMD_CONTROL_func(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_MMD_CONTROL(U16 data)
{
    *(volatile U16 *)REG_EPHY_MMD_CONTROL = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MMD_CONTROL] <-- 0x%08x\n",
                        REG_EPHY_MMD_CONTROL,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_MMD_CONTROL(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_MMD_CONTROL);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MMD_CONTROL] --> 0x%08x\n",
                        REG_EPHY_MMD_CONTROL,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_MMD_CONTROL_devad(U8 data)
{
    GH_EPHY_MMD_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_MMD_CONTROL;
    d.bitc.devad = data;
    *(volatile U16 *)REG_EPHY_MMD_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MMD_CONTROL_devad] <-- 0x%08x\n",
                        REG_EPHY_MMD_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_MMD_CONTROL_devad(void)
{
    GH_EPHY_MMD_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MMD_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MMD_CONTROL_devad] --> 0x%08x\n",
                        REG_EPHY_MMD_CONTROL,value);
    #endif
    return tmp_value.bitc.devad;
}
GH_INLINE void GH_EPHY_set_MMD_CONTROL_func(U8 data)
{
    GH_EPHY_MMD_CONTROL_S d;
    d.all = *(volatile U16 *)REG_EPHY_MMD_CONTROL;
    d.bitc.func = data;
    *(volatile U16 *)REG_EPHY_MMD_CONTROL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MMD_CONTROL_func] <-- 0x%08x\n",
                        REG_EPHY_MMD_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_MMD_CONTROL_func(void)
{
    GH_EPHY_MMD_CONTROL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MMD_CONTROL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MMD_CONTROL_func] --> 0x%08x\n",
                        REG_EPHY_MMD_CONTROL,value);
    #endif
    return tmp_value.bitc.func;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_MMD_CONTROL_ADDR (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_MMD_CONTROL_ADDR'. */
void GH_EPHY_set_MMD_CONTROL_ADDR(U16 data);
/*! \brief Reads the register 'EPHY_MMD_CONTROL_ADDR'. */
U16  GH_EPHY_get_MMD_CONTROL_ADDR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_MMD_CONTROL_ADDR(U16 data)
{
    *(volatile U16 *)REG_EPHY_MMD_CONTROL_ADDR = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MMD_CONTROL_ADDR] <-- 0x%08x\n",
                        REG_EPHY_MMD_CONTROL_ADDR,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_MMD_CONTROL_ADDR(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_MMD_CONTROL_ADDR);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MMD_CONTROL_ADDR] --> 0x%08x\n",
                        REG_EPHY_MMD_CONTROL_ADDR,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_AN_R_15 (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'EPHY_AN_R_15'. */
U16  GH_EPHY_get_AN_R_15(void);
/*! \brief Reads the bit group 'an_register_15' of register 'EPHY_AN_R_15'. */
U8   GH_EPHY_get_AN_R_15_an_register_15(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_EPHY_get_AN_R_15(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_AN_R_15);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_AN_R_15] --> 0x%08x\n",
                        REG_EPHY_AN_R_15,value);
    #endif
    return value;
}
GH_INLINE U8   GH_EPHY_get_AN_R_15_an_register_15(void)
{
    GH_EPHY_AN_R_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_AN_R_15);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_AN_R_15_an_register_15] --> 0x%08x\n",
                        REG_EPHY_AN_R_15,value);
    #endif
    return tmp_value.bitc.an_register_15;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_34 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_WAVE_SHAPING_34'. */
void GH_EPHY_set_WAVE_SHAPING_34(U16 data);
/*! \brief Reads the register 'EPHY_WAVE_SHAPING_34'. */
U16  GH_EPHY_get_WAVE_SHAPING_34(void);
/*! \brief Writes the bit group 'ltp_3' of register 'EPHY_WAVE_SHAPING_34'. */
void GH_EPHY_set_WAVE_SHAPING_34_ltp_3(U8 data);
/*! \brief Reads the bit group 'ltp_3' of register 'EPHY_WAVE_SHAPING_34'. */
U8   GH_EPHY_get_WAVE_SHAPING_34_ltp_3(void);
/*! \brief Writes the bit group 'ltp_4' of register 'EPHY_WAVE_SHAPING_34'. */
void GH_EPHY_set_WAVE_SHAPING_34_ltp_4(U8 data);
/*! \brief Reads the bit group 'ltp_4' of register 'EPHY_WAVE_SHAPING_34'. */
U8   GH_EPHY_get_WAVE_SHAPING_34_ltp_4(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_34(U16 data)
{
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34 = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_34] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_34,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_34(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_34);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_34] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_34,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_34_ltp_3(U8 data)
{
    GH_EPHY_WAVE_SHAPING_34_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34;
    d.bitc.ltp_3 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_34_ltp_3] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_34,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_34_ltp_3(void)
{
    GH_EPHY_WAVE_SHAPING_34_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_34);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_34_ltp_3] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_34,value);
    #endif
    return tmp_value.bitc.ltp_3;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_34_ltp_4(U8 data)
{
    GH_EPHY_WAVE_SHAPING_34_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34;
    d.bitc.ltp_4 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_34_ltp_4] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_34,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_34_ltp_4(void)
{
    GH_EPHY_WAVE_SHAPING_34_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_34);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_34_ltp_4] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_34,value);
    #endif
    return tmp_value.bitc.ltp_4;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_56 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_WAVE_SHAPING_56'. */
void GH_EPHY_set_WAVE_SHAPING_56(U16 data);
/*! \brief Reads the register 'EPHY_WAVE_SHAPING_56'. */
U16  GH_EPHY_get_WAVE_SHAPING_56(void);
/*! \brief Writes the bit group 'ltp_5' of register 'EPHY_WAVE_SHAPING_56'. */
void GH_EPHY_set_WAVE_SHAPING_56_ltp_5(U8 data);
/*! \brief Reads the bit group 'ltp_5' of register 'EPHY_WAVE_SHAPING_56'. */
U8   GH_EPHY_get_WAVE_SHAPING_56_ltp_5(void);
/*! \brief Writes the bit group 'ltp_6' of register 'EPHY_WAVE_SHAPING_56'. */
void GH_EPHY_set_WAVE_SHAPING_56_ltp_6(U8 data);
/*! \brief Reads the bit group 'ltp_6' of register 'EPHY_WAVE_SHAPING_56'. */
U8   GH_EPHY_get_WAVE_SHAPING_56_ltp_6(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_56(U16 data)
{
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56 = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_56] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_56,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_56(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_56);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_56] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_56,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_56_ltp_5(U8 data)
{
    GH_EPHY_WAVE_SHAPING_56_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56;
    d.bitc.ltp_5 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_56_ltp_5] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_56,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_56_ltp_5(void)
{
    GH_EPHY_WAVE_SHAPING_56_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_56);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_56_ltp_5] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_56,value);
    #endif
    return tmp_value.bitc.ltp_5;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_56_ltp_6(U8 data)
{
    GH_EPHY_WAVE_SHAPING_56_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56;
    d.bitc.ltp_6 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_56_ltp_6] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_56,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_56_ltp_6(void)
{
    GH_EPHY_WAVE_SHAPING_56_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_56);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_56_ltp_6] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_56,value);
    #endif
    return tmp_value.bitc.ltp_6;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_78 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_WAVE_SHAPING_78'. */
void GH_EPHY_set_WAVE_SHAPING_78(U16 data);
/*! \brief Reads the register 'EPHY_WAVE_SHAPING_78'. */
U16  GH_EPHY_get_WAVE_SHAPING_78(void);
/*! \brief Writes the bit group 'ltp_7' of register 'EPHY_WAVE_SHAPING_78'. */
void GH_EPHY_set_WAVE_SHAPING_78_ltp_7(U8 data);
/*! \brief Reads the bit group 'ltp_7' of register 'EPHY_WAVE_SHAPING_78'. */
U8   GH_EPHY_get_WAVE_SHAPING_78_ltp_7(void);
/*! \brief Writes the bit group 'ltp_8' of register 'EPHY_WAVE_SHAPING_78'. */
void GH_EPHY_set_WAVE_SHAPING_78_ltp_8(U8 data);
/*! \brief Reads the bit group 'ltp_8' of register 'EPHY_WAVE_SHAPING_78'. */
U8   GH_EPHY_get_WAVE_SHAPING_78_ltp_8(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_78(U16 data)
{
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78 = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_78] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_78,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_78(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_78);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_78] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_78,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_78_ltp_7(U8 data)
{
    GH_EPHY_WAVE_SHAPING_78_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78;
    d.bitc.ltp_7 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_78_ltp_7] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_78,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_78_ltp_7(void)
{
    GH_EPHY_WAVE_SHAPING_78_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_78);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_78_ltp_7] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_78,value);
    #endif
    return tmp_value.bitc.ltp_7;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_78_ltp_8(U8 data)
{
    GH_EPHY_WAVE_SHAPING_78_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78;
    d.bitc.ltp_8 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_78_ltp_8] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_78,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_78_ltp_8(void)
{
    GH_EPHY_WAVE_SHAPING_78_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_78);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_78_ltp_8] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_78,value);
    #endif
    return tmp_value.bitc.ltp_8;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_9A (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_WAVE_SHAPING_9A'. */
void GH_EPHY_set_WAVE_SHAPING_9A(U16 data);
/*! \brief Reads the register 'EPHY_WAVE_SHAPING_9A'. */
U16  GH_EPHY_get_WAVE_SHAPING_9A(void);
/*! \brief Writes the bit group 'ltp_9' of register 'EPHY_WAVE_SHAPING_9A'. */
void GH_EPHY_set_WAVE_SHAPING_9A_ltp_9(U8 data);
/*! \brief Reads the bit group 'ltp_9' of register 'EPHY_WAVE_SHAPING_9A'. */
U8   GH_EPHY_get_WAVE_SHAPING_9A_ltp_9(void);
/*! \brief Writes the bit group 'ltp_A' of register 'EPHY_WAVE_SHAPING_9A'. */
void GH_EPHY_set_WAVE_SHAPING_9A_ltp_A(U8 data);
/*! \brief Reads the bit group 'ltp_A' of register 'EPHY_WAVE_SHAPING_9A'. */
U8   GH_EPHY_get_WAVE_SHAPING_9A_ltp_A(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_9A(U16 data)
{
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_9A] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_9A,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_9A(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_9A] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_9A,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_9A_ltp_9(U8 data)
{
    GH_EPHY_WAVE_SHAPING_9A_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A;
    d.bitc.ltp_9 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_9A_ltp_9] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_9A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_9A_ltp_9(void)
{
    GH_EPHY_WAVE_SHAPING_9A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_9A_ltp_9] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_9A,value);
    #endif
    return tmp_value.bitc.ltp_9;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_9A_ltp_A(U8 data)
{
    GH_EPHY_WAVE_SHAPING_9A_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A;
    d.bitc.ltp_a = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_9A_ltp_A] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_9A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_9A_ltp_A(void)
{
    GH_EPHY_WAVE_SHAPING_9A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_9A_ltp_A] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_9A,value);
    #endif
    return tmp_value.bitc.ltp_a;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_BC (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_WAVE_SHAPING_BC'. */
void GH_EPHY_set_WAVE_SHAPING_BC(U16 data);
/*! \brief Reads the register 'EPHY_WAVE_SHAPING_BC'. */
U16  GH_EPHY_get_WAVE_SHAPING_BC(void);
/*! \brief Writes the bit group 'ltp_B' of register 'EPHY_WAVE_SHAPING_BC'. */
void GH_EPHY_set_WAVE_SHAPING_BC_ltp_B(U8 data);
/*! \brief Reads the bit group 'ltp_B' of register 'EPHY_WAVE_SHAPING_BC'. */
U8   GH_EPHY_get_WAVE_SHAPING_BC_ltp_B(void);
/*! \brief Writes the bit group 'ltp_C' of register 'EPHY_WAVE_SHAPING_BC'. */
void GH_EPHY_set_WAVE_SHAPING_BC_ltp_C(U8 data);
/*! \brief Reads the bit group 'ltp_C' of register 'EPHY_WAVE_SHAPING_BC'. */
U8   GH_EPHY_get_WAVE_SHAPING_BC_ltp_C(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_BC(U16 data)
{
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_BC] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_BC,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_BC(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_BC] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_BC,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_BC_ltp_B(U8 data)
{
    GH_EPHY_WAVE_SHAPING_BC_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC;
    d.bitc.ltp_b = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_BC_ltp_B] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_BC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_BC_ltp_B(void)
{
    GH_EPHY_WAVE_SHAPING_BC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_BC_ltp_B] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_BC,value);
    #endif
    return tmp_value.bitc.ltp_b;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_BC_ltp_C(U8 data)
{
    GH_EPHY_WAVE_SHAPING_BC_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC;
    d.bitc.ltp_c = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_BC_ltp_C] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_BC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_BC_ltp_C(void)
{
    GH_EPHY_WAVE_SHAPING_BC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_BC_ltp_C] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_BC,value);
    #endif
    return tmp_value.bitc.ltp_c;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_DE (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_WAVE_SHAPING_DE'. */
void GH_EPHY_set_WAVE_SHAPING_DE(U16 data);
/*! \brief Reads the register 'EPHY_WAVE_SHAPING_DE'. */
U16  GH_EPHY_get_WAVE_SHAPING_DE(void);
/*! \brief Writes the bit group 'ltp_D' of register 'EPHY_WAVE_SHAPING_DE'. */
void GH_EPHY_set_WAVE_SHAPING_DE_ltp_D(U8 data);
/*! \brief Reads the bit group 'ltp_D' of register 'EPHY_WAVE_SHAPING_DE'. */
U8   GH_EPHY_get_WAVE_SHAPING_DE_ltp_D(void);
/*! \brief Writes the bit group 'ltp_E' of register 'EPHY_WAVE_SHAPING_DE'. */
void GH_EPHY_set_WAVE_SHAPING_DE_ltp_E(U8 data);
/*! \brief Reads the bit group 'ltp_E' of register 'EPHY_WAVE_SHAPING_DE'. */
U8   GH_EPHY_get_WAVE_SHAPING_DE_ltp_E(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_DE(U16 data)
{
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_DE] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_DE,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_DE(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_DE] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_DE,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_DE_ltp_D(U8 data)
{
    GH_EPHY_WAVE_SHAPING_DE_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE;
    d.bitc.ltp_d = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_DE_ltp_D] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_DE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_DE_ltp_D(void)
{
    GH_EPHY_WAVE_SHAPING_DE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_DE_ltp_D] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_DE,value);
    #endif
    return tmp_value.bitc.ltp_d;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_DE_ltp_E(U8 data)
{
    GH_EPHY_WAVE_SHAPING_DE_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE;
    d.bitc.ltp_e = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_SHAPING_DE_ltp_E] <-- 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_DE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_DE_ltp_E(void)
{
    GH_EPHY_WAVE_SHAPING_DE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_SHAPING_DE_ltp_E] --> 0x%08x\n",
                        REG_EPHY_WAVE_SHAPING_DE,value);
    #endif
    return tmp_value.bitc.ltp_e;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_SPEED (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_SPEED'. */
void GH_EPHY_set_SPEED(U16 data);
/*! \brief Reads the register 'EPHY_SPEED'. */
U16  GH_EPHY_get_SPEED(void);
/*! \brief Writes the bit group 'ltp_F' of register 'EPHY_SPEED'. */
void GH_EPHY_set_SPEED_ltp_F(U8 data);
/*! \brief Reads the bit group 'ltp_F' of register 'EPHY_SPEED'. */
U8   GH_EPHY_get_SPEED_ltp_F(void);
/*! \brief Writes the bit group 'isolate' of register 'EPHY_SPEED'. */
void GH_EPHY_set_SPEED_isolate(U8 data);
/*! \brief Reads the bit group 'isolate' of register 'EPHY_SPEED'. */
U8   GH_EPHY_get_SPEED_isolate(void);
/*! \brief Writes the bit group 'rptr' of register 'EPHY_SPEED'. */
void GH_EPHY_set_SPEED_rptr(U8 data);
/*! \brief Reads the bit group 'rptr' of register 'EPHY_SPEED'. */
U8   GH_EPHY_get_SPEED_rptr(void);
/*! \brief Writes the bit group 'duplex' of register 'EPHY_SPEED'. */
void GH_EPHY_set_SPEED_duplex(U8 data);
/*! \brief Reads the bit group 'duplex' of register 'EPHY_SPEED'. */
U8   GH_EPHY_get_SPEED_duplex(void);
/*! \brief Writes the bit group 'speed' of register 'EPHY_SPEED'. */
void GH_EPHY_set_SPEED_speed(U8 data);
/*! \brief Reads the bit group 'speed' of register 'EPHY_SPEED'. */
U8   GH_EPHY_get_SPEED_speed(void);
/*! \brief Writes the bit group 'ane' of register 'EPHY_SPEED'. */
void GH_EPHY_set_SPEED_ane(U8 data);
/*! \brief Reads the bit group 'ane' of register 'EPHY_SPEED'. */
U8   GH_EPHY_get_SPEED_ane(void);
/*! \brief Writes the bit group 'ldps' of register 'EPHY_SPEED'. */
void GH_EPHY_set_SPEED_ldps(U8 data);
/*! \brief Reads the bit group 'ldps' of register 'EPHY_SPEED'. */
U8   GH_EPHY_get_SPEED_ldps(void);
/*! \brief Writes the bit group 'disable_eee_force' of register 'EPHY_SPEED'. */
void GH_EPHY_set_SPEED_disable_eee_force(U8 data);
/*! \brief Reads the bit group 'disable_eee_force' of register 'EPHY_SPEED'. */
U8   GH_EPHY_get_SPEED_disable_eee_force(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_SPEED(U16 data)
{
    *(volatile U16 *)REG_EPHY_SPEED = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SPEED] <-- 0x%08x\n",
                        REG_EPHY_SPEED,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_SPEED(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SPEED] --> 0x%08x\n",
                        REG_EPHY_SPEED,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_SPEED_ltp_F(U8 data)
{
    GH_EPHY_SPEED_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED;
    d.bitc.ltp_f = data;
    *(volatile U16 *)REG_EPHY_SPEED = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SPEED_ltp_F] <-- 0x%08x\n",
                        REG_EPHY_SPEED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SPEED_ltp_F(void)
{
    GH_EPHY_SPEED_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SPEED_ltp_F] --> 0x%08x\n",
                        REG_EPHY_SPEED,value);
    #endif
    return tmp_value.bitc.ltp_f;
}
GH_INLINE void GH_EPHY_set_SPEED_isolate(U8 data)
{
    GH_EPHY_SPEED_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED;
    d.bitc.isolate = data;
    *(volatile U16 *)REG_EPHY_SPEED = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SPEED_isolate] <-- 0x%08x\n",
                        REG_EPHY_SPEED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SPEED_isolate(void)
{
    GH_EPHY_SPEED_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SPEED_isolate] --> 0x%08x\n",
                        REG_EPHY_SPEED,value);
    #endif
    return tmp_value.bitc.isolate;
}
GH_INLINE void GH_EPHY_set_SPEED_rptr(U8 data)
{
    GH_EPHY_SPEED_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED;
    d.bitc.rptr = data;
    *(volatile U16 *)REG_EPHY_SPEED = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SPEED_rptr] <-- 0x%08x\n",
                        REG_EPHY_SPEED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SPEED_rptr(void)
{
    GH_EPHY_SPEED_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SPEED_rptr] --> 0x%08x\n",
                        REG_EPHY_SPEED,value);
    #endif
    return tmp_value.bitc.rptr;
}
GH_INLINE void GH_EPHY_set_SPEED_duplex(U8 data)
{
    GH_EPHY_SPEED_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED;
    d.bitc.duplex = data;
    *(volatile U16 *)REG_EPHY_SPEED = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SPEED_duplex] <-- 0x%08x\n",
                        REG_EPHY_SPEED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SPEED_duplex(void)
{
    GH_EPHY_SPEED_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SPEED_duplex] --> 0x%08x\n",
                        REG_EPHY_SPEED,value);
    #endif
    return tmp_value.bitc.duplex;
}
GH_INLINE void GH_EPHY_set_SPEED_speed(U8 data)
{
    GH_EPHY_SPEED_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED;
    d.bitc.speed = data;
    *(volatile U16 *)REG_EPHY_SPEED = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SPEED_speed] <-- 0x%08x\n",
                        REG_EPHY_SPEED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SPEED_speed(void)
{
    GH_EPHY_SPEED_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SPEED_speed] --> 0x%08x\n",
                        REG_EPHY_SPEED,value);
    #endif
    return tmp_value.bitc.speed;
}
GH_INLINE void GH_EPHY_set_SPEED_ane(U8 data)
{
    GH_EPHY_SPEED_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED;
    d.bitc.ane = data;
    *(volatile U16 *)REG_EPHY_SPEED = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SPEED_ane] <-- 0x%08x\n",
                        REG_EPHY_SPEED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SPEED_ane(void)
{
    GH_EPHY_SPEED_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SPEED_ane] --> 0x%08x\n",
                        REG_EPHY_SPEED,value);
    #endif
    return tmp_value.bitc.ane;
}
GH_INLINE void GH_EPHY_set_SPEED_ldps(U8 data)
{
    GH_EPHY_SPEED_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED;
    d.bitc.ldps = data;
    *(volatile U16 *)REG_EPHY_SPEED = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SPEED_ldps] <-- 0x%08x\n",
                        REG_EPHY_SPEED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SPEED_ldps(void)
{
    GH_EPHY_SPEED_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SPEED_ldps] --> 0x%08x\n",
                        REG_EPHY_SPEED,value);
    #endif
    return tmp_value.bitc.ldps;
}
GH_INLINE void GH_EPHY_set_SPEED_disable_eee_force(U8 data)
{
    GH_EPHY_SPEED_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED;
    d.bitc.disable_eee_force = data;
    *(volatile U16 *)REG_EPHY_SPEED = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SPEED_disable_eee_force] <-- 0x%08x\n",
                        REG_EPHY_SPEED,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SPEED_disable_eee_force(void)
{
    GH_EPHY_SPEED_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SPEED_disable_eee_force] --> 0x%08x\n",
                        REG_EPHY_SPEED,value);
    #endif
    return tmp_value.bitc.disable_eee_force;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_LTP (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_LTP'. */
void GH_EPHY_set_LTP(U16 data);
/*! \brief Reads the register 'EPHY_LTP'. */
U16  GH_EPHY_get_LTP(void);
/*! \brief Writes the bit group 'width' of register 'EPHY_LTP'. */
void GH_EPHY_set_LTP_width(U8 data);
/*! \brief Reads the bit group 'width' of register 'EPHY_LTP'. */
U8   GH_EPHY_get_LTP_width(void);
/*! \brief Writes the bit group 'tx_gm_rctrl' of register 'EPHY_LTP'. */
void GH_EPHY_set_LTP_tx_gm_rctrl(U8 data);
/*! \brief Reads the bit group 'tx_gm_rctrl' of register 'EPHY_LTP'. */
U8   GH_EPHY_get_LTP_tx_gm_rctrl(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_LTP(U16 data)
{
    *(volatile U16 *)REG_EPHY_LTP = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LTP] <-- 0x%08x\n",
                        REG_EPHY_LTP,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_LTP(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_LTP);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LTP] --> 0x%08x\n",
                        REG_EPHY_LTP,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_LTP_width(U8 data)
{
    GH_EPHY_LTP_S d;
    d.all = *(volatile U16 *)REG_EPHY_LTP;
    d.bitc.width = data;
    *(volatile U16 *)REG_EPHY_LTP = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LTP_width] <-- 0x%08x\n",
                        REG_EPHY_LTP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_LTP_width(void)
{
    GH_EPHY_LTP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LTP);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LTP_width] --> 0x%08x\n",
                        REG_EPHY_LTP,value);
    #endif
    return tmp_value.bitc.width;
}
GH_INLINE void GH_EPHY_set_LTP_tx_gm_rctrl(U8 data)
{
    GH_EPHY_LTP_S d;
    d.all = *(volatile U16 *)REG_EPHY_LTP;
    d.bitc.tx_gm_rctrl = data;
    *(volatile U16 *)REG_EPHY_LTP = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LTP_tx_gm_rctrl] <-- 0x%08x\n",
                        REG_EPHY_LTP,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_LTP_tx_gm_rctrl(void)
{
    GH_EPHY_LTP_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LTP);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LTP_tx_gm_rctrl] --> 0x%08x\n",
                        REG_EPHY_LTP,value);
    #endif
    return tmp_value.bitc.tx_gm_rctrl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_MCU (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_MCU'. */
void GH_EPHY_set_MCU(U16 data);
/*! \brief Reads the register 'EPHY_MCU'. */
U16  GH_EPHY_get_MCU(void);
/*! \brief Writes the bit group 'en' of register 'EPHY_MCU'. */
void GH_EPHY_set_MCU_en(U8 data);
/*! \brief Reads the bit group 'en' of register 'EPHY_MCU'. */
U8   GH_EPHY_get_MCU_en(void);
/*! \brief Writes the bit group 'mcu_rdy' of register 'EPHY_MCU'. */
void GH_EPHY_set_MCU_mcu_rdy(U8 data);
/*! \brief Reads the bit group 'mcu_rdy' of register 'EPHY_MCU'. */
U8   GH_EPHY_get_MCU_mcu_rdy(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_MCU(U16 data)
{
    *(volatile U16 *)REG_EPHY_MCU = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MCU] <-- 0x%08x\n",
                        REG_EPHY_MCU,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_MCU(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_MCU);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MCU] --> 0x%08x\n",
                        REG_EPHY_MCU,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_MCU_en(U8 data)
{
    GH_EPHY_MCU_S d;
    d.all = *(volatile U16 *)REG_EPHY_MCU;
    d.bitc.en = data;
    *(volatile U16 *)REG_EPHY_MCU = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MCU_en] <-- 0x%08x\n",
                        REG_EPHY_MCU,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_MCU_en(void)
{
    GH_EPHY_MCU_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MCU);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MCU_en] --> 0x%08x\n",
                        REG_EPHY_MCU,value);
    #endif
    return tmp_value.bitc.en;
}
GH_INLINE void GH_EPHY_set_MCU_mcu_rdy(U8 data)
{
    GH_EPHY_MCU_S d;
    d.all = *(volatile U16 *)REG_EPHY_MCU;
    d.bitc.mcu_rdy = data;
    *(volatile U16 *)REG_EPHY_MCU = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MCU_mcu_rdy] <-- 0x%08x\n",
                        REG_EPHY_MCU,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_MCU_mcu_rdy(void)
{
    GH_EPHY_MCU_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MCU);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MCU_mcu_rdy] --> 0x%08x\n",
                        REG_EPHY_MCU,value);
    #endif
    return tmp_value.bitc.mcu_rdy;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_CODE_RAM (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_CODE_RAM'. */
void GH_EPHY_set_CODE_RAM(U16 data);
/*! \brief Reads the register 'EPHY_CODE_RAM'. */
U16  GH_EPHY_get_CODE_RAM(void);
/*! \brief Writes the bit group 'start_addr' of register 'EPHY_CODE_RAM'. */
void GH_EPHY_set_CODE_RAM_start_addr(U16 data);
/*! \brief Reads the bit group 'start_addr' of register 'EPHY_CODE_RAM'. */
U16  GH_EPHY_get_CODE_RAM_start_addr(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_CODE_RAM(U16 data)
{
    *(volatile U16 *)REG_EPHY_CODE_RAM = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CODE_RAM] <-- 0x%08x\n",
                        REG_EPHY_CODE_RAM,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_CODE_RAM(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_CODE_RAM);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CODE_RAM] --> 0x%08x\n",
                        REG_EPHY_CODE_RAM,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_CODE_RAM_start_addr(U16 data)
{
    GH_EPHY_CODE_RAM_S d;
    d.all = *(volatile U16 *)REG_EPHY_CODE_RAM;
    d.bitc.start_addr = data;
    *(volatile U16 *)REG_EPHY_CODE_RAM = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CODE_RAM_start_addr] <-- 0x%08x\n",
                        REG_EPHY_CODE_RAM,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_EPHY_get_CODE_RAM_start_addr(void)
{
    GH_EPHY_CODE_RAM_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CODE_RAM);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CODE_RAM_start_addr] --> 0x%08x\n",
                        REG_EPHY_CODE_RAM,value);
    #endif
    return tmp_value.bitc.start_addr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_CODE_RAM_W (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_CODE_RAM_W'. */
void GH_EPHY_set_CODE_RAM_W(U16 data);
/*! \brief Reads the register 'EPHY_CODE_RAM_W'. */
U16  GH_EPHY_get_CODE_RAM_W(void);
/*! \brief Writes the bit group 'start_addr' of register 'EPHY_CODE_RAM_W'. */
void GH_EPHY_set_CODE_RAM_W_start_addr(U16 data);
/*! \brief Reads the bit group 'start_addr' of register 'EPHY_CODE_RAM_W'. */
U16  GH_EPHY_get_CODE_RAM_W_start_addr(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_CODE_RAM_W(U16 data)
{
    *(volatile U16 *)REG_EPHY_CODE_RAM_W = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CODE_RAM_W] <-- 0x%08x\n",
                        REG_EPHY_CODE_RAM_W,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_CODE_RAM_W(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_CODE_RAM_W);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CODE_RAM_W] --> 0x%08x\n",
                        REG_EPHY_CODE_RAM_W,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_CODE_RAM_W_start_addr(U16 data)
{
    GH_EPHY_CODE_RAM_W_S d;
    d.all = *(volatile U16 *)REG_EPHY_CODE_RAM_W;
    d.bitc.start_addr = data;
    *(volatile U16 *)REG_EPHY_CODE_RAM_W = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CODE_RAM_W_start_addr] <-- 0x%08x\n",
                        REG_EPHY_CODE_RAM_W,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_EPHY_get_CODE_RAM_W_start_addr(void)
{
    GH_EPHY_CODE_RAM_W_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CODE_RAM_W);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CODE_RAM_W_start_addr] --> 0x%08x\n",
                        REG_EPHY_CODE_RAM_W,value);
    #endif
    return tmp_value.bitc.start_addr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_100M_LINK (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK(U16 data);
/*! \brief Reads the register 'EPHY_100M_LINK'. */
U16  GH_EPHY_get_100M_LINK(void);
/*! \brief Writes the bit group 'an_mcu_100t_link_control' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_an_mcu_100t_link_control(U8 data);
/*! \brief Reads the bit group 'an_mcu_100t_link_control' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_an_mcu_100t_link_control(void);
/*! \brief Writes the bit group 'an_mcu_nlp_link_control' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_an_mcu_nlp_link_control(U8 data);
/*! \brief Reads the bit group 'an_mcu_nlp_link_control' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_an_mcu_nlp_link_control(void);
/*! \brief Writes the bit group 'nlp_frame_start_mode_en' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_nlp_frame_start_mode_en(U8 data);
/*! \brief Reads the bit group 'nlp_frame_start_mode_en' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_nlp_frame_start_mode_en(void);
/*! \brief Writes the bit group 'detect_100m' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_detect_100m(U8 data);
/*! \brief Reads the bit group 'detect_100m' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_detect_100m(void);
/*! \brief Writes the bit group 'mcu_an_enable' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_mcu_an_enable(U8 data);
/*! \brief Reads the bit group 'mcu_an_enable' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_mcu_an_enable(void);
/*! \brief Writes the bit group 'force_100m_link_good' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_force_100m_link_good(U8 data);
/*! \brief Reads the bit group 'force_100m_link_good' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_force_100m_link_good(void);
/*! \brief Writes the bit group 'an_100t_link_status' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_an_100t_link_status(U8 data);
/*! \brief Reads the bit group 'an_100t_link_status' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_an_100t_link_status(void);
/*! \brief Writes the bit group 'an_nlp_link_status' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_an_nlp_link_status(U8 data);
/*! \brief Reads the bit group 'an_nlp_link_status' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_an_nlp_link_status(void);
/*! \brief Writes the bit group 'mdio_disable' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_mdio_disable(U8 data);
/*! \brief Reads the bit group 'mdio_disable' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_mdio_disable(void);
/*! \brief Writes the bit group 'mdc_edge_sel' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_mdc_edge_sel(U8 data);
/*! \brief Reads the bit group 'mdc_edge_sel' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_mdc_edge_sel(void);
/*! \brief Writes the bit group 'an_bypass_link_status_check' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_an_bypass_link_status_check(U8 data);
/*! \brief Reads the bit group 'an_bypass_link_status_check' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_an_bypass_link_status_check(void);
/*! \brief Writes the bit group 'adc_loop' of register 'EPHY_100M_LINK'. */
void GH_EPHY_set_100M_LINK_adc_loop(U8 data);
/*! \brief Reads the bit group 'adc_loop' of register 'EPHY_100M_LINK'. */
U8   GH_EPHY_get_100M_LINK_adc_loop(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_100M_LINK(U16 data)
{
    *(volatile U16 *)REG_EPHY_100M_LINK = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_100M_LINK(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_mcu_100t_link_control(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.an_mcu_100t_link_control = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_an_mcu_100t_link_control] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_mcu_100t_link_control(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_an_mcu_100t_link_control] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.an_mcu_100t_link_control;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_mcu_nlp_link_control(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.an_mcu_nlp_link_control = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_an_mcu_nlp_link_control] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_mcu_nlp_link_control(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_an_mcu_nlp_link_control] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.an_mcu_nlp_link_control;
}
GH_INLINE void GH_EPHY_set_100M_LINK_nlp_frame_start_mode_en(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.nlp_frame_start_mode_en = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_nlp_frame_start_mode_en] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_nlp_frame_start_mode_en(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_nlp_frame_start_mode_en] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.nlp_frame_start_mode_en;
}
GH_INLINE void GH_EPHY_set_100M_LINK_detect_100m(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.detect_100m = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_detect_100m] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_detect_100m(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_detect_100m] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.detect_100m;
}
GH_INLINE void GH_EPHY_set_100M_LINK_mcu_an_enable(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.mcu_an_enable = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_mcu_an_enable] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_mcu_an_enable(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_mcu_an_enable] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.mcu_an_enable;
}
GH_INLINE void GH_EPHY_set_100M_LINK_force_100m_link_good(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.force_100m_link_good = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_force_100m_link_good] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_force_100m_link_good(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_force_100m_link_good] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.force_100m_link_good;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_100t_link_status(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.an_100t_link_status = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_an_100t_link_status] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_100t_link_status(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_an_100t_link_status] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.an_100t_link_status;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_nlp_link_status(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.an_nlp_link_status = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_an_nlp_link_status] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_nlp_link_status(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_an_nlp_link_status] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.an_nlp_link_status;
}
GH_INLINE void GH_EPHY_set_100M_LINK_mdio_disable(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.mdio_disable = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_mdio_disable] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_mdio_disable(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_mdio_disable] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.mdio_disable;
}
GH_INLINE void GH_EPHY_set_100M_LINK_mdc_edge_sel(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.mdc_edge_sel = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_mdc_edge_sel] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_mdc_edge_sel(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_mdc_edge_sel] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.mdc_edge_sel;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_bypass_link_status_check(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.an_bypass_link_status_check = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_an_bypass_link_status_check] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_bypass_link_status_check(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_an_bypass_link_status_check] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.an_bypass_link_status_check;
}
GH_INLINE void GH_EPHY_set_100M_LINK_adc_loop(U8 data)
{
    GH_EPHY_100M_LINK_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK;
    d.bitc.adc_loop = data;
    *(volatile U16 *)REG_EPHY_100M_LINK = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_100M_LINK_adc_loop] <-- 0x%08x\n",
                        REG_EPHY_100M_LINK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_adc_loop(void)
{
    GH_EPHY_100M_LINK_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_100M_LINK_adc_loop] --> 0x%08x\n",
                        REG_EPHY_100M_LINK,value);
    #endif
    return tmp_value.bitc.adc_loop;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_DEBUG (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_DEBUG'. */
void GH_EPHY_set_DEBUG(U16 data);
/*! \brief Reads the register 'EPHY_DEBUG'. */
U16  GH_EPHY_get_DEBUG(void);
/*! \brief Writes the bit group 'snr_locked' of register 'EPHY_DEBUG'. */
void GH_EPHY_set_DEBUG_snr_locked(U8 data);
/*! \brief Reads the bit group 'snr_locked' of register 'EPHY_DEBUG'. */
U8   GH_EPHY_get_DEBUG_snr_locked(void);
/*! \brief Writes the bit group 'snr_locked_raw' of register 'EPHY_DEBUG'. */
void GH_EPHY_set_DEBUG_snr_locked_raw(U8 data);
/*! \brief Reads the bit group 'snr_locked_raw' of register 'EPHY_DEBUG'. */
U8   GH_EPHY_get_DEBUG_snr_locked_raw(void);
/*! \brief Writes the bit group 'sig_det_flag' of register 'EPHY_DEBUG'. */
void GH_EPHY_set_DEBUG_sig_det_flag(U8 data);
/*! \brief Reads the bit group 'sig_det_flag' of register 'EPHY_DEBUG'. */
U8   GH_EPHY_get_DEBUG_sig_det_flag(void);
/*! \brief Writes the bit group 'state_sync_on' of register 'EPHY_DEBUG'. */
void GH_EPHY_set_DEBUG_state_sync_on(U8 data);
/*! \brief Reads the bit group 'state_sync_on' of register 'EPHY_DEBUG'. */
U8   GH_EPHY_get_DEBUG_state_sync_on(void);
/*! \brief Writes the bit group 'state_st_lk' of register 'EPHY_DEBUG'. */
void GH_EPHY_set_DEBUG_state_st_lk(U8 data);
/*! \brief Reads the bit group 'state_st_lk' of register 'EPHY_DEBUG'. */
U8   GH_EPHY_get_DEBUG_state_st_lk(void);
/*! \brief Writes the bit group 'mux_recov_cnt' of register 'EPHY_DEBUG'. */
void GH_EPHY_set_DEBUG_mux_recov_cnt(U8 data);
/*! \brief Reads the bit group 'mux_recov_cnt' of register 'EPHY_DEBUG'. */
U8   GH_EPHY_get_DEBUG_mux_recov_cnt(void);
/*! \brief Writes the bit group 'test_mux_sel' of register 'EPHY_DEBUG'. */
void GH_EPHY_set_DEBUG_test_mux_sel(U8 data);
/*! \brief Reads the bit group 'test_mux_sel' of register 'EPHY_DEBUG'. */
U8   GH_EPHY_get_DEBUG_test_mux_sel(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_DEBUG(U16 data)
{
    *(volatile U16 *)REG_EPHY_DEBUG = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG] <-- 0x%08x\n",
                        REG_EPHY_DEBUG,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_DEBUG(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG] --> 0x%08x\n",
                        REG_EPHY_DEBUG,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_DEBUG_snr_locked(U8 data)
{
    GH_EPHY_DEBUG_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG;
    d.bitc.snr_locked = data;
    *(volatile U16 *)REG_EPHY_DEBUG = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_snr_locked] <-- 0x%08x\n",
                        REG_EPHY_DEBUG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DEBUG_snr_locked(void)
{
    GH_EPHY_DEBUG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_snr_locked] --> 0x%08x\n",
                        REG_EPHY_DEBUG,value);
    #endif
    return tmp_value.bitc.snr_locked;
}
GH_INLINE void GH_EPHY_set_DEBUG_snr_locked_raw(U8 data)
{
    GH_EPHY_DEBUG_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG;
    d.bitc.snr_locked_raw = data;
    *(volatile U16 *)REG_EPHY_DEBUG = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_snr_locked_raw] <-- 0x%08x\n",
                        REG_EPHY_DEBUG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DEBUG_snr_locked_raw(void)
{
    GH_EPHY_DEBUG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_snr_locked_raw] --> 0x%08x\n",
                        REG_EPHY_DEBUG,value);
    #endif
    return tmp_value.bitc.snr_locked_raw;
}
GH_INLINE void GH_EPHY_set_DEBUG_sig_det_flag(U8 data)
{
    GH_EPHY_DEBUG_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG;
    d.bitc.sig_det_flag = data;
    *(volatile U16 *)REG_EPHY_DEBUG = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_sig_det_flag] <-- 0x%08x\n",
                        REG_EPHY_DEBUG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DEBUG_sig_det_flag(void)
{
    GH_EPHY_DEBUG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_sig_det_flag] --> 0x%08x\n",
                        REG_EPHY_DEBUG,value);
    #endif
    return tmp_value.bitc.sig_det_flag;
}
GH_INLINE void GH_EPHY_set_DEBUG_state_sync_on(U8 data)
{
    GH_EPHY_DEBUG_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG;
    d.bitc.state_sync_on = data;
    *(volatile U16 *)REG_EPHY_DEBUG = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_state_sync_on] <-- 0x%08x\n",
                        REG_EPHY_DEBUG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DEBUG_state_sync_on(void)
{
    GH_EPHY_DEBUG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_state_sync_on] --> 0x%08x\n",
                        REG_EPHY_DEBUG,value);
    #endif
    return tmp_value.bitc.state_sync_on;
}
GH_INLINE void GH_EPHY_set_DEBUG_state_st_lk(U8 data)
{
    GH_EPHY_DEBUG_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG;
    d.bitc.state_st_lk = data;
    *(volatile U16 *)REG_EPHY_DEBUG = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_state_st_lk] <-- 0x%08x\n",
                        REG_EPHY_DEBUG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DEBUG_state_st_lk(void)
{
    GH_EPHY_DEBUG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_state_st_lk] --> 0x%08x\n",
                        REG_EPHY_DEBUG,value);
    #endif
    return tmp_value.bitc.state_st_lk;
}
GH_INLINE void GH_EPHY_set_DEBUG_mux_recov_cnt(U8 data)
{
    GH_EPHY_DEBUG_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG;
    d.bitc.mux_recov_cnt = data;
    *(volatile U16 *)REG_EPHY_DEBUG = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_mux_recov_cnt] <-- 0x%08x\n",
                        REG_EPHY_DEBUG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DEBUG_mux_recov_cnt(void)
{
    GH_EPHY_DEBUG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_mux_recov_cnt] --> 0x%08x\n",
                        REG_EPHY_DEBUG,value);
    #endif
    return tmp_value.bitc.mux_recov_cnt;
}
GH_INLINE void GH_EPHY_set_DEBUG_test_mux_sel(U8 data)
{
    GH_EPHY_DEBUG_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG;
    d.bitc.test_mux_sel = data;
    *(volatile U16 *)REG_EPHY_DEBUG = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_test_mux_sel] <-- 0x%08x\n",
                        REG_EPHY_DEBUG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DEBUG_test_mux_sel(void)
{
    GH_EPHY_DEBUG_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_test_mux_sel] --> 0x%08x\n",
                        REG_EPHY_DEBUG,value);
    #endif
    return tmp_value.bitc.test_mux_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_DEBUG_MODE (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_DEBUG_MODE'. */
void GH_EPHY_set_DEBUG_MODE(U16 data);
/*! \brief Reads the register 'EPHY_DEBUG_MODE'. */
U16  GH_EPHY_get_DEBUG_MODE(void);
/*! \brief Writes the bit group 'signal' of register 'EPHY_DEBUG_MODE'. */
void GH_EPHY_set_DEBUG_MODE_signal(U8 data);
/*! \brief Reads the bit group 'signal' of register 'EPHY_DEBUG_MODE'. */
U8   GH_EPHY_get_DEBUG_MODE_signal(void);
/*! \brief Writes the bit group 'module' of register 'EPHY_DEBUG_MODE'. */
void GH_EPHY_set_DEBUG_MODE_module(U8 data);
/*! \brief Reads the bit group 'module' of register 'EPHY_DEBUG_MODE'. */
U8   GH_EPHY_get_DEBUG_MODE_module(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_DEBUG_MODE(U16 data)
{
    *(volatile U16 *)REG_EPHY_DEBUG_MODE = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_MODE] <-- 0x%08x\n",
                        REG_EPHY_DEBUG_MODE,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_DEBUG_MODE(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_MODE);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_MODE] --> 0x%08x\n",
                        REG_EPHY_DEBUG_MODE,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_DEBUG_MODE_signal(U8 data)
{
    GH_EPHY_DEBUG_MODE_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_MODE;
    d.bitc.signal = data;
    *(volatile U16 *)REG_EPHY_DEBUG_MODE = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_MODE_signal] <-- 0x%08x\n",
                        REG_EPHY_DEBUG_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DEBUG_MODE_signal(void)
{
    GH_EPHY_DEBUG_MODE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_MODE);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_MODE_signal] --> 0x%08x\n",
                        REG_EPHY_DEBUG_MODE,value);
    #endif
    return tmp_value.bitc.signal;
}
GH_INLINE void GH_EPHY_set_DEBUG_MODE_module(U8 data)
{
    GH_EPHY_DEBUG_MODE_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_MODE;
    d.bitc.module = data;
    *(volatile U16 *)REG_EPHY_DEBUG_MODE = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DEBUG_MODE_module] <-- 0x%08x\n",
                        REG_EPHY_DEBUG_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DEBUG_MODE_module(void)
{
    GH_EPHY_DEBUG_MODE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_MODE);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DEBUG_MODE_module] --> 0x%08x\n",
                        REG_EPHY_DEBUG_MODE,value);
    #endif
    return tmp_value.bitc.module;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_RST_EN (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN(U16 data);
/*! \brief Reads the register 'EPHY_RST_EN'. */
U16  GH_EPHY_get_RST_EN(void);
/*! \brief Writes the bit group 'mau_srst' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_mau_srst(U8 data);
/*! \brief Reads the bit group 'mau_srst' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_mau_srst(void);
/*! \brief Writes the bit group 'pls_srst' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_pls_srst(U8 data);
/*! \brief Reads the bit group 'pls_srst' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_pls_srst(void);
/*! \brief Writes the bit group 'sqe_test_enable' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_sqe_test_enable(U8 data);
/*! \brief Reads the bit group 'sqe_test_enable' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_sqe_test_enable(void);
/*! \brief Writes the bit group 'lpbk_enable' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_lpbk_enable(U8 data);
/*! \brief Reads the bit group 'lpbk_enable' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_lpbk_enable(void);
/*! \brief Writes the bit group 'jabber_enable' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_jabber_enable(U8 data);
/*! \brief Reads the bit group 'jabber_enable' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_jabber_enable(void);
/*! \brief Writes the bit group 'ser_polarity_correction' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_ser_polarity_correction(U8 data);
/*! \brief Reads the bit group 'ser_polarity_correction' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_ser_polarity_correction(void);
/*! \brief Writes the bit group 'por_stick_mode' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_por_stick_mode(U8 data);
/*! \brief Reads the bit group 'por_stick_mode' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_por_stick_mode(void);
/*! \brief Writes the bit group 'recv_bit_bucket' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_recv_bit_bucket(U8 data);
/*! \brief Reads the bit group 'recv_bit_bucket' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_recv_bit_bucket(void);
/*! \brief Writes the bit group 'rxclk_pol' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_rxclk_pol(U8 data);
/*! \brief Reads the bit group 'rxclk_pol' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_rxclk_pol(void);
/*! \brief Writes the bit group 'txclk_pol' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_txclk_pol(U8 data);
/*! \brief Reads the bit group 'txclk_pol' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_txclk_pol(void);
/*! \brief Writes the bit group 'adc_input_sign' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_adc_input_sign(U8 data);
/*! \brief Reads the bit group 'adc_input_sign' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_adc_input_sign(void);
/*! \brief Writes the bit group 'mii_test_packet' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_mii_test_packet(U8 data);
/*! \brief Reads the bit group 'mii_test_packet' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_mii_test_packet(void);
/*! \brief Writes the bit group 'clear_rcvpack' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_clear_rcvpack(U8 data);
/*! \brief Reads the bit group 'clear_rcvpack' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_clear_rcvpack(void);
/*! \brief Writes the bit group 'miiloop_en_10m' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_miiloop_en_10m(U8 data);
/*! \brief Reads the bit group 'miiloop_en_10m' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_miiloop_en_10m(void);
/*! \brief Writes the bit group 'mii_rxclk_pol' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_mii_rxclk_pol(U8 data);
/*! \brief Reads the bit group 'mii_rxclk_pol' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_mii_rxclk_pol(void);
/*! \brief Writes the bit group 'mii_txclk_pol' of register 'EPHY_RST_EN'. */
void GH_EPHY_set_RST_EN_mii_txclk_pol(U8 data);
/*! \brief Reads the bit group 'mii_txclk_pol' of register 'EPHY_RST_EN'. */
U8   GH_EPHY_get_RST_EN_mii_txclk_pol(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_RST_EN(U16 data)
{
    *(volatile U16 *)REG_EPHY_RST_EN = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_RST_EN(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_RST_EN_mau_srst(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.mau_srst = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_mau_srst] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_mau_srst(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_mau_srst] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.mau_srst;
}
GH_INLINE void GH_EPHY_set_RST_EN_pls_srst(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.pls_srst = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_pls_srst] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_pls_srst(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_pls_srst] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.pls_srst;
}
GH_INLINE void GH_EPHY_set_RST_EN_sqe_test_enable(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.sqe_test_enable = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_sqe_test_enable] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_sqe_test_enable(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_sqe_test_enable] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.sqe_test_enable;
}
GH_INLINE void GH_EPHY_set_RST_EN_lpbk_enable(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.lpbk_enable = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_lpbk_enable] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_lpbk_enable(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_lpbk_enable] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.lpbk_enable;
}
GH_INLINE void GH_EPHY_set_RST_EN_jabber_enable(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.jabber_enable = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_jabber_enable] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_jabber_enable(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_jabber_enable] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.jabber_enable;
}
GH_INLINE void GH_EPHY_set_RST_EN_ser_polarity_correction(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.ser_polarity_correction = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_ser_polarity_correction] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_ser_polarity_correction(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_ser_polarity_correction] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.ser_polarity_correction;
}
GH_INLINE void GH_EPHY_set_RST_EN_por_stick_mode(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.por_stick_mode = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_por_stick_mode] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_por_stick_mode(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_por_stick_mode] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.por_stick_mode;
}
GH_INLINE void GH_EPHY_set_RST_EN_recv_bit_bucket(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.recv_bit_bucket = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_recv_bit_bucket] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_recv_bit_bucket(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_recv_bit_bucket] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.recv_bit_bucket;
}
GH_INLINE void GH_EPHY_set_RST_EN_rxclk_pol(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.rxclk_pol = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_rxclk_pol] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_rxclk_pol(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_rxclk_pol] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.rxclk_pol;
}
GH_INLINE void GH_EPHY_set_RST_EN_txclk_pol(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.txclk_pol = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_txclk_pol] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_txclk_pol(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_txclk_pol] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.txclk_pol;
}
GH_INLINE void GH_EPHY_set_RST_EN_adc_input_sign(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.adc_input_sign = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_adc_input_sign] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_adc_input_sign(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_adc_input_sign] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.adc_input_sign;
}
GH_INLINE void GH_EPHY_set_RST_EN_mii_test_packet(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.mii_test_packet = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_mii_test_packet] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_mii_test_packet(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_mii_test_packet] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.mii_test_packet;
}
GH_INLINE void GH_EPHY_set_RST_EN_clear_rcvpack(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.clear_rcvpack = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_clear_rcvpack] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_clear_rcvpack(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_clear_rcvpack] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.clear_rcvpack;
}
GH_INLINE void GH_EPHY_set_RST_EN_miiloop_en_10m(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.miiloop_en_10m = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_miiloop_en_10m] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_miiloop_en_10m(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_miiloop_en_10m] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.miiloop_en_10m;
}
GH_INLINE void GH_EPHY_set_RST_EN_mii_rxclk_pol(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.mii_rxclk_pol = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_mii_rxclk_pol] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_mii_rxclk_pol(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_mii_rxclk_pol] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.mii_rxclk_pol;
}
GH_INLINE void GH_EPHY_set_RST_EN_mii_txclk_pol(U8 data)
{
    GH_EPHY_RST_EN_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN;
    d.bitc.mii_txclk_pol = data;
    *(volatile U16 *)REG_EPHY_RST_EN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RST_EN_mii_txclk_pol] <-- 0x%08x\n",
                        REG_EPHY_RST_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RST_EN_mii_txclk_pol(void)
{
    GH_EPHY_RST_EN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RST_EN_mii_txclk_pol] --> 0x%08x\n",
                        REG_EPHY_RST_EN,value);
    #endif
    return tmp_value.bitc.mii_txclk_pol;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_SNR_K (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_SNR_K'. */
void GH_EPHY_set_SNR_K(U16 data);
/*! \brief Reads the register 'EPHY_SNR_K'. */
U16  GH_EPHY_get_SNR_K(void);
/*! \brief Writes the bit group 'slice_up' of register 'EPHY_SNR_K'. */
void GH_EPHY_set_SNR_K_slice_up(U8 data);
/*! \brief Reads the bit group 'slice_up' of register 'EPHY_SNR_K'. */
U8   GH_EPHY_get_SNR_K_slice_up(void);
/*! \brief Writes the bit group 'snrchk_k1' of register 'EPHY_SNR_K'. */
void GH_EPHY_set_SNR_K_snrchk_k1(U8 data);
/*! \brief Reads the bit group 'snrchk_k1' of register 'EPHY_SNR_K'. */
U8   GH_EPHY_get_SNR_K_snrchk_k1(void);
/*! \brief Writes the bit group 'snrchk_k2' of register 'EPHY_SNR_K'. */
void GH_EPHY_set_SNR_K_snrchk_k2(U8 data);
/*! \brief Reads the bit group 'snrchk_k2' of register 'EPHY_SNR_K'. */
U8   GH_EPHY_get_SNR_K_snrchk_k2(void);
/*! \brief Writes the bit group 'snrchk_k3' of register 'EPHY_SNR_K'. */
void GH_EPHY_set_SNR_K_snrchk_k3(U8 data);
/*! \brief Reads the bit group 'snrchk_k3' of register 'EPHY_SNR_K'. */
U8   GH_EPHY_get_SNR_K_snrchk_k3(void);
/*! \brief Writes the bit group 'gcr_ccpl_master_coarse_clkcc' of register 'EPHY_SNR_K'. */
void GH_EPHY_set_SNR_K_gcr_ccpl_master_coarse_clkcc(U8 data);
/*! \brief Reads the bit group 'gcr_ccpl_master_coarse_clkcc' of register 'EPHY_SNR_K'. */
U8   GH_EPHY_get_SNR_K_gcr_ccpl_master_coarse_clkcc(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_SNR_K(U16 data)
{
    *(volatile U16 *)REG_EPHY_SNR_K = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_K] <-- 0x%08x\n",
                        REG_EPHY_SNR_K,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_SNR_K(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_K] --> 0x%08x\n",
                        REG_EPHY_SNR_K,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_SNR_K_slice_up(U8 data)
{
    GH_EPHY_SNR_K_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K;
    d.bitc.slice_up = data;
    *(volatile U16 *)REG_EPHY_SNR_K = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_K_slice_up] <-- 0x%08x\n",
                        REG_EPHY_SNR_K,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_K_slice_up(void)
{
    GH_EPHY_SNR_K_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_K_slice_up] --> 0x%08x\n",
                        REG_EPHY_SNR_K,value);
    #endif
    return tmp_value.bitc.slice_up;
}
GH_INLINE void GH_EPHY_set_SNR_K_snrchk_k1(U8 data)
{
    GH_EPHY_SNR_K_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K;
    d.bitc.snrchk_k1 = data;
    *(volatile U16 *)REG_EPHY_SNR_K = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_K_snrchk_k1] <-- 0x%08x\n",
                        REG_EPHY_SNR_K,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_K_snrchk_k1(void)
{
    GH_EPHY_SNR_K_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_K_snrchk_k1] --> 0x%08x\n",
                        REG_EPHY_SNR_K,value);
    #endif
    return tmp_value.bitc.snrchk_k1;
}
GH_INLINE void GH_EPHY_set_SNR_K_snrchk_k2(U8 data)
{
    GH_EPHY_SNR_K_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K;
    d.bitc.snrchk_k2 = data;
    *(volatile U16 *)REG_EPHY_SNR_K = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_K_snrchk_k2] <-- 0x%08x\n",
                        REG_EPHY_SNR_K,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_K_snrchk_k2(void)
{
    GH_EPHY_SNR_K_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_K_snrchk_k2] --> 0x%08x\n",
                        REG_EPHY_SNR_K,value);
    #endif
    return tmp_value.bitc.snrchk_k2;
}
GH_INLINE void GH_EPHY_set_SNR_K_snrchk_k3(U8 data)
{
    GH_EPHY_SNR_K_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K;
    d.bitc.snrchk_k3 = data;
    *(volatile U16 *)REG_EPHY_SNR_K = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_K_snrchk_k3] <-- 0x%08x\n",
                        REG_EPHY_SNR_K,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_K_snrchk_k3(void)
{
    GH_EPHY_SNR_K_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_K_snrchk_k3] --> 0x%08x\n",
                        REG_EPHY_SNR_K,value);
    #endif
    return tmp_value.bitc.snrchk_k3;
}
GH_INLINE void GH_EPHY_set_SNR_K_gcr_ccpl_master_coarse_clkcc(U8 data)
{
    GH_EPHY_SNR_K_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K;
    d.bitc.gcr_ccpl_master_coarse_clkcc = data;
    *(volatile U16 *)REG_EPHY_SNR_K = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_K_gcr_ccpl_master_coarse_clkcc] <-- 0x%08x\n",
                        REG_EPHY_SNR_K,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_K_gcr_ccpl_master_coarse_clkcc(void)
{
    GH_EPHY_SNR_K_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_K_gcr_ccpl_master_coarse_clkcc] --> 0x%08x\n",
                        REG_EPHY_SNR_K,value);
    #endif
    return tmp_value.bitc.gcr_ccpl_master_coarse_clkcc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_DET_MAX (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_DET_MAX'. */
void GH_EPHY_set_DET_MAX(U16 data);
/*! \brief Reads the register 'EPHY_DET_MAX'. */
U16  GH_EPHY_get_DET_MAX(void);
/*! \brief Writes the bit group 'thrh_max_vga_coarse' of register 'EPHY_DET_MAX'. */
void GH_EPHY_set_DET_MAX_thrh_max_vga_coarse(U8 data);
/*! \brief Reads the bit group 'thrh_max_vga_coarse' of register 'EPHY_DET_MAX'. */
U8   GH_EPHY_get_DET_MAX_thrh_max_vga_coarse(void);
/*! \brief Writes the bit group 'thrh_max_sig_det' of register 'EPHY_DET_MAX'. */
void GH_EPHY_set_DET_MAX_thrh_max_sig_det(U8 data);
/*! \brief Reads the bit group 'thrh_max_sig_det' of register 'EPHY_DET_MAX'. */
U8   GH_EPHY_get_DET_MAX_thrh_max_sig_det(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_DET_MAX(U16 data)
{
    *(volatile U16 *)REG_EPHY_DET_MAX = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DET_MAX] <-- 0x%08x\n",
                        REG_EPHY_DET_MAX,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_DET_MAX(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MAX);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DET_MAX] --> 0x%08x\n",
                        REG_EPHY_DET_MAX,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_DET_MAX_thrh_max_vga_coarse(U8 data)
{
    GH_EPHY_DET_MAX_S d;
    d.all = *(volatile U16 *)REG_EPHY_DET_MAX;
    d.bitc.thrh_max_vga_coarse = data;
    *(volatile U16 *)REG_EPHY_DET_MAX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DET_MAX_thrh_max_vga_coarse] <-- 0x%08x\n",
                        REG_EPHY_DET_MAX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DET_MAX_thrh_max_vga_coarse(void)
{
    GH_EPHY_DET_MAX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MAX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DET_MAX_thrh_max_vga_coarse] --> 0x%08x\n",
                        REG_EPHY_DET_MAX,value);
    #endif
    return tmp_value.bitc.thrh_max_vga_coarse;
}
GH_INLINE void GH_EPHY_set_DET_MAX_thrh_max_sig_det(U8 data)
{
    GH_EPHY_DET_MAX_S d;
    d.all = *(volatile U16 *)REG_EPHY_DET_MAX;
    d.bitc.thrh_max_sig_det = data;
    *(volatile U16 *)REG_EPHY_DET_MAX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DET_MAX_thrh_max_sig_det] <-- 0x%08x\n",
                        REG_EPHY_DET_MAX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DET_MAX_thrh_max_sig_det(void)
{
    GH_EPHY_DET_MAX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MAX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DET_MAX_thrh_max_sig_det] --> 0x%08x\n",
                        REG_EPHY_DET_MAX,value);
    #endif
    return tmp_value.bitc.thrh_max_sig_det;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_DET_MIN (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_DET_MIN'. */
void GH_EPHY_set_DET_MIN(U16 data);
/*! \brief Reads the register 'EPHY_DET_MIN'. */
U16  GH_EPHY_get_DET_MIN(void);
/*! \brief Writes the bit group 'thrh_max_vga_fine' of register 'EPHY_DET_MIN'. */
void GH_EPHY_set_DET_MIN_thrh_max_vga_fine(U8 data);
/*! \brief Reads the bit group 'thrh_max_vga_fine' of register 'EPHY_DET_MIN'. */
U8   GH_EPHY_get_DET_MIN_thrh_max_vga_fine(void);
/*! \brief Writes the bit group 'thrh_min_sig_det' of register 'EPHY_DET_MIN'. */
void GH_EPHY_set_DET_MIN_thrh_min_sig_det(U8 data);
/*! \brief Reads the bit group 'thrh_min_sig_det' of register 'EPHY_DET_MIN'. */
U8   GH_EPHY_get_DET_MIN_thrh_min_sig_det(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_DET_MIN(U16 data)
{
    *(volatile U16 *)REG_EPHY_DET_MIN = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DET_MIN] <-- 0x%08x\n",
                        REG_EPHY_DET_MIN,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_DET_MIN(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MIN);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DET_MIN] --> 0x%08x\n",
                        REG_EPHY_DET_MIN,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_DET_MIN_thrh_max_vga_fine(U8 data)
{
    GH_EPHY_DET_MIN_S d;
    d.all = *(volatile U16 *)REG_EPHY_DET_MIN;
    d.bitc.thrh_max_vga_fine = data;
    *(volatile U16 *)REG_EPHY_DET_MIN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DET_MIN_thrh_max_vga_fine] <-- 0x%08x\n",
                        REG_EPHY_DET_MIN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DET_MIN_thrh_max_vga_fine(void)
{
    GH_EPHY_DET_MIN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MIN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DET_MIN_thrh_max_vga_fine] --> 0x%08x\n",
                        REG_EPHY_DET_MIN,value);
    #endif
    return tmp_value.bitc.thrh_max_vga_fine;
}
GH_INLINE void GH_EPHY_set_DET_MIN_thrh_min_sig_det(U8 data)
{
    GH_EPHY_DET_MIN_S d;
    d.all = *(volatile U16 *)REG_EPHY_DET_MIN;
    d.bitc.thrh_min_sig_det = data;
    *(volatile U16 *)REG_EPHY_DET_MIN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_DET_MIN_thrh_min_sig_det] <-- 0x%08x\n",
                        REG_EPHY_DET_MIN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_DET_MIN_thrh_min_sig_det(void)
{
    GH_EPHY_DET_MIN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MIN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_DET_MIN_thrh_min_sig_det] --> 0x%08x\n",
                        REG_EPHY_DET_MIN,value);
    #endif
    return tmp_value.bitc.thrh_min_sig_det;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_SNR_LEN (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_SNR_LEN'. */
void GH_EPHY_set_SNR_LEN(U16 data);
/*! \brief Reads the register 'EPHY_SNR_LEN'. */
U16  GH_EPHY_get_SNR_LEN(void);
/*! \brief Writes the bit group 'mcu_ctrl_dsp_fsm_state' of register 'EPHY_SNR_LEN'. */
void GH_EPHY_set_SNR_LEN_mcu_ctrl_dsp_fsm_state(U8 data);
/*! \brief Reads the bit group 'mcu_ctrl_dsp_fsm_state' of register 'EPHY_SNR_LEN'. */
U8   GH_EPHY_get_SNR_LEN_mcu_ctrl_dsp_fsm_state(void);
/*! \brief Writes the bit group 'force_100m_en' of register 'EPHY_SNR_LEN'. */
void GH_EPHY_set_SNR_LEN_force_100m_en(U8 data);
/*! \brief Reads the bit group 'force_100m_en' of register 'EPHY_SNR_LEN'. */
U8   GH_EPHY_get_SNR_LEN_force_100m_en(void);
/*! \brief Writes the bit group 'force_100m_snr_lock' of register 'EPHY_SNR_LEN'. */
void GH_EPHY_set_SNR_LEN_force_100m_snr_lock(U8 data);
/*! \brief Reads the bit group 'force_100m_snr_lock' of register 'EPHY_SNR_LEN'. */
U8   GH_EPHY_get_SNR_LEN_force_100m_snr_lock(void);
/*! \brief Writes the bit group 'dsp_fsm_agc_en_mode_a' of register 'EPHY_SNR_LEN'. */
void GH_EPHY_set_SNR_LEN_dsp_fsm_agc_en_mode_a(U8 data);
/*! \brief Reads the bit group 'dsp_fsm_agc_en_mode_a' of register 'EPHY_SNR_LEN'. */
U8   GH_EPHY_get_SNR_LEN_dsp_fsm_agc_en_mode_a(void);
/*! \brief Writes the bit group 'cable_len_offset' of register 'EPHY_SNR_LEN'. */
void GH_EPHY_set_SNR_LEN_cable_len_offset(U8 data);
/*! \brief Reads the bit group 'cable_len_offset' of register 'EPHY_SNR_LEN'. */
U8   GH_EPHY_get_SNR_LEN_cable_len_offset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_SNR_LEN(U16 data)
{
    *(volatile U16 *)REG_EPHY_SNR_LEN = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_LEN] <-- 0x%08x\n",
                        REG_EPHY_SNR_LEN,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_SNR_LEN(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_LEN] --> 0x%08x\n",
                        REG_EPHY_SNR_LEN,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_mcu_ctrl_dsp_fsm_state(U8 data)
{
    GH_EPHY_SNR_LEN_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN;
    d.bitc.mcu_ctrl_dsp_fsm_state = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_LEN_mcu_ctrl_dsp_fsm_state] <-- 0x%08x\n",
                        REG_EPHY_SNR_LEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_mcu_ctrl_dsp_fsm_state(void)
{
    GH_EPHY_SNR_LEN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_LEN_mcu_ctrl_dsp_fsm_state] --> 0x%08x\n",
                        REG_EPHY_SNR_LEN,value);
    #endif
    return tmp_value.bitc.mcu_ctrl_dsp_fsm_state;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_force_100m_en(U8 data)
{
    GH_EPHY_SNR_LEN_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN;
    d.bitc.force_100m_en = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_LEN_force_100m_en] <-- 0x%08x\n",
                        REG_EPHY_SNR_LEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_force_100m_en(void)
{
    GH_EPHY_SNR_LEN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_LEN_force_100m_en] --> 0x%08x\n",
                        REG_EPHY_SNR_LEN,value);
    #endif
    return tmp_value.bitc.force_100m_en;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_force_100m_snr_lock(U8 data)
{
    GH_EPHY_SNR_LEN_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN;
    d.bitc.force_100m_snr_lock = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_LEN_force_100m_snr_lock] <-- 0x%08x\n",
                        REG_EPHY_SNR_LEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_force_100m_snr_lock(void)
{
    GH_EPHY_SNR_LEN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_LEN_force_100m_snr_lock] --> 0x%08x\n",
                        REG_EPHY_SNR_LEN,value);
    #endif
    return tmp_value.bitc.force_100m_snr_lock;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_dsp_fsm_agc_en_mode_a(U8 data)
{
    GH_EPHY_SNR_LEN_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN;
    d.bitc.dsp_fsm_agc_en_mode_a = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_LEN_dsp_fsm_agc_en_mode_a] <-- 0x%08x\n",
                        REG_EPHY_SNR_LEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_dsp_fsm_agc_en_mode_a(void)
{
    GH_EPHY_SNR_LEN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_LEN_dsp_fsm_agc_en_mode_a] --> 0x%08x\n",
                        REG_EPHY_SNR_LEN,value);
    #endif
    return tmp_value.bitc.dsp_fsm_agc_en_mode_a;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_cable_len_offset(U8 data)
{
    GH_EPHY_SNR_LEN_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN;
    d.bitc.cable_len_offset = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_SNR_LEN_cable_len_offset] <-- 0x%08x\n",
                        REG_EPHY_SNR_LEN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_cable_len_offset(void)
{
    GH_EPHY_SNR_LEN_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_SNR_LEN_cable_len_offset] --> 0x%08x\n",
                        REG_EPHY_SNR_LEN,value);
    #endif
    return tmp_value.bitc.cable_len_offset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_LPF (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_LPF'. */
void GH_EPHY_set_LPF(U16 data);
/*! \brief Reads the register 'EPHY_LPF'. */
U16  GH_EPHY_get_LPF(void);
/*! \brief Writes the bit group 'lpf_out_h' of register 'EPHY_LPF'. */
void GH_EPHY_set_LPF_lpf_out_h(U16 data);
/*! \brief Reads the bit group 'lpf_out_h' of register 'EPHY_LPF'. */
U16  GH_EPHY_get_LPF_lpf_out_h(void);
/*! \brief Writes the bit group 'rxlpf_bwsel_10t' of register 'EPHY_LPF'. */
void GH_EPHY_set_LPF_rxlpf_bwsel_10t(U8 data);
/*! \brief Reads the bit group 'rxlpf_bwsel_10t' of register 'EPHY_LPF'. */
U8   GH_EPHY_get_LPF_rxlpf_bwsel_10t(void);
/*! \brief Writes the bit group 'rxlpf_bwsel_100t' of register 'EPHY_LPF'. */
void GH_EPHY_set_LPF_rxlpf_bwsel_100t(U8 data);
/*! \brief Reads the bit group 'rxlpf_bwsel_100t' of register 'EPHY_LPF'. */
U8   GH_EPHY_get_LPF_rxlpf_bwsel_100t(void);
/*! \brief Writes the bit group 'cable_length' of register 'EPHY_LPF'. */
void GH_EPHY_set_LPF_cable_length(U8 data);
/*! \brief Reads the bit group 'cable_length' of register 'EPHY_LPF'. */
U8   GH_EPHY_get_LPF_cable_length(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_LPF(U16 data)
{
    *(volatile U16 *)REG_EPHY_LPF = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LPF] <-- 0x%08x\n",
                        REG_EPHY_LPF,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_LPF(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_LPF);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LPF] --> 0x%08x\n",
                        REG_EPHY_LPF,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_LPF_lpf_out_h(U16 data)
{
    GH_EPHY_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_LPF;
    d.bitc.lpf_out_h = data;
    *(volatile U16 *)REG_EPHY_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LPF_lpf_out_h] <-- 0x%08x\n",
                        REG_EPHY_LPF,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_EPHY_get_LPF_lpf_out_h(void)
{
    GH_EPHY_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LPF_lpf_out_h] --> 0x%08x\n",
                        REG_EPHY_LPF,value);
    #endif
    return tmp_value.bitc.lpf_out_h;
}
GH_INLINE void GH_EPHY_set_LPF_rxlpf_bwsel_10t(U8 data)
{
    GH_EPHY_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_LPF;
    d.bitc.rxlpf_bwsel_10t = data;
    *(volatile U16 *)REG_EPHY_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LPF_rxlpf_bwsel_10t] <-- 0x%08x\n",
                        REG_EPHY_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_LPF_rxlpf_bwsel_10t(void)
{
    GH_EPHY_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LPF_rxlpf_bwsel_10t] --> 0x%08x\n",
                        REG_EPHY_LPF,value);
    #endif
    return tmp_value.bitc.rxlpf_bwsel_10t;
}
GH_INLINE void GH_EPHY_set_LPF_rxlpf_bwsel_100t(U8 data)
{
    GH_EPHY_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_LPF;
    d.bitc.rxlpf_bwsel_100t = data;
    *(volatile U16 *)REG_EPHY_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LPF_rxlpf_bwsel_100t] <-- 0x%08x\n",
                        REG_EPHY_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_LPF_rxlpf_bwsel_100t(void)
{
    GH_EPHY_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LPF_rxlpf_bwsel_100t] --> 0x%08x\n",
                        REG_EPHY_LPF,value);
    #endif
    return tmp_value.bitc.rxlpf_bwsel_100t;
}
GH_INLINE void GH_EPHY_set_LPF_cable_length(U8 data)
{
    GH_EPHY_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_LPF;
    d.bitc.cable_length = data;
    *(volatile U16 *)REG_EPHY_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LPF_cable_length] <-- 0x%08x\n",
                        REG_EPHY_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_LPF_cable_length(void)
{
    GH_EPHY_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LPF_cable_length] --> 0x%08x\n",
                        REG_EPHY_LPF,value);
    #endif
    return tmp_value.bitc.cable_length;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ADC_GAIN_PGA (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_ADC_GAIN_PGA'. */
void GH_EPHY_set_ADC_GAIN_PGA(U16 data);
/*! \brief Reads the register 'EPHY_ADC_GAIN_PGA'. */
U16  GH_EPHY_get_ADC_GAIN_PGA(void);
/*! \brief Writes the bit group 'adc_bp' of register 'EPHY_ADC_GAIN_PGA'. */
void GH_EPHY_set_ADC_GAIN_PGA_adc_bp(U8 data);
/*! \brief Reads the bit group 'adc_bp' of register 'EPHY_ADC_GAIN_PGA'. */
U8   GH_EPHY_get_ADC_GAIN_PGA_adc_bp(void);
/*! \brief Writes the bit group 'dac10t_testen' of register 'EPHY_ADC_GAIN_PGA'. */
void GH_EPHY_set_ADC_GAIN_PGA_dac10t_testen(U8 data);
/*! \brief Reads the bit group 'dac10t_testen' of register 'EPHY_ADC_GAIN_PGA'. */
U8   GH_EPHY_get_ADC_GAIN_PGA_dac10t_testen(void);
/*! \brief Writes the bit group 'dac100t_testen' of register 'EPHY_ADC_GAIN_PGA'. */
void GH_EPHY_set_ADC_GAIN_PGA_dac100t_testen(U8 data);
/*! \brief Reads the bit group 'dac100t_testen' of register 'EPHY_ADC_GAIN_PGA'. */
U8   GH_EPHY_get_ADC_GAIN_PGA_dac100t_testen(void);
/*! \brief Writes the bit group 'adc_bma' of register 'EPHY_ADC_GAIN_PGA'. */
void GH_EPHY_set_ADC_GAIN_PGA_adc_bma(U8 data);
/*! \brief Reads the bit group 'adc_bma' of register 'EPHY_ADC_GAIN_PGA'. */
U8   GH_EPHY_get_ADC_GAIN_PGA_adc_bma(void);
/*! \brief Writes the bit group 'adc_pd' of register 'EPHY_ADC_GAIN_PGA'. */
void GH_EPHY_set_ADC_GAIN_PGA_adc_pd(U8 data);
/*! \brief Reads the bit group 'adc_pd' of register 'EPHY_ADC_GAIN_PGA'. */
U8   GH_EPHY_get_ADC_GAIN_PGA_adc_pd(void);
/*! \brief Writes the bit group 'region_bank_rd' of register 'EPHY_ADC_GAIN_PGA'. */
void GH_EPHY_set_ADC_GAIN_PGA_region_bank_rd(U8 data);
/*! \brief Reads the bit group 'region_bank_rd' of register 'EPHY_ADC_GAIN_PGA'. */
U8   GH_EPHY_get_ADC_GAIN_PGA_region_bank_rd(void);
/*! \brief Writes the bit group 'adcpll_ana_clken' of register 'EPHY_ADC_GAIN_PGA'. */
void GH_EPHY_set_ADC_GAIN_PGA_adcpll_ana_clken(U8 data);
/*! \brief Reads the bit group 'adcpll_ana_clken' of register 'EPHY_ADC_GAIN_PGA'. */
U8   GH_EPHY_get_ADC_GAIN_PGA_adcpll_ana_clken(void);
/*! \brief Writes the bit group 'adcbin_testen' of register 'EPHY_ADC_GAIN_PGA'. */
void GH_EPHY_set_ADC_GAIN_PGA_adcbin_testen(U8 data);
/*! \brief Reads the bit group 'adcbin_testen' of register 'EPHY_ADC_GAIN_PGA'. */
U8   GH_EPHY_get_ADC_GAIN_PGA_adcbin_testen(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA(U16 data)
{
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GAIN_PGA] <-- 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_ADC_GAIN_PGA(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GAIN_PGA] --> 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adc_bp(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA;
    d.bitc.adc_bp = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GAIN_PGA_adc_bp] <-- 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adc_bp(void)
{
    GH_EPHY_ADC_GAIN_PGA_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GAIN_PGA_adc_bp] --> 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,value);
    #endif
    return tmp_value.bitc.adc_bp;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_dac10t_testen(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA;
    d.bitc.dac10t_testen = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GAIN_PGA_dac10t_testen] <-- 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_dac10t_testen(void)
{
    GH_EPHY_ADC_GAIN_PGA_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GAIN_PGA_dac10t_testen] --> 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,value);
    #endif
    return tmp_value.bitc.dac10t_testen;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_dac100t_testen(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA;
    d.bitc.dac100t_testen = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GAIN_PGA_dac100t_testen] <-- 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_dac100t_testen(void)
{
    GH_EPHY_ADC_GAIN_PGA_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GAIN_PGA_dac100t_testen] --> 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,value);
    #endif
    return tmp_value.bitc.dac100t_testen;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adc_bma(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA;
    d.bitc.adc_bma = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GAIN_PGA_adc_bma] <-- 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adc_bma(void)
{
    GH_EPHY_ADC_GAIN_PGA_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GAIN_PGA_adc_bma] --> 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,value);
    #endif
    return tmp_value.bitc.adc_bma;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adc_pd(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA;
    d.bitc.adc_pd = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GAIN_PGA_adc_pd] <-- 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adc_pd(void)
{
    GH_EPHY_ADC_GAIN_PGA_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GAIN_PGA_adc_pd] --> 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,value);
    #endif
    return tmp_value.bitc.adc_pd;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_region_bank_rd(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA;
    d.bitc.region_bank_rd = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GAIN_PGA_region_bank_rd] <-- 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_region_bank_rd(void)
{
    GH_EPHY_ADC_GAIN_PGA_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GAIN_PGA_region_bank_rd] --> 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,value);
    #endif
    return tmp_value.bitc.region_bank_rd;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adcpll_ana_clken(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA;
    d.bitc.adcpll_ana_clken = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GAIN_PGA_adcpll_ana_clken] <-- 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adcpll_ana_clken(void)
{
    GH_EPHY_ADC_GAIN_PGA_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GAIN_PGA_adcpll_ana_clken] --> 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,value);
    #endif
    return tmp_value.bitc.adcpll_ana_clken;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adcbin_testen(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA;
    d.bitc.adcbin_testen = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GAIN_PGA_adcbin_testen] <-- 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adcbin_testen(void)
{
    GH_EPHY_ADC_GAIN_PGA_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GAIN_PGA_adcbin_testen] --> 0x%08x\n",
                        REG_EPHY_ADC_GAIN_PGA,value);
    #endif
    return tmp_value.bitc.adcbin_testen;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ADC_GSHIFT (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_ADC_GSHIFT'. */
void GH_EPHY_set_ADC_GSHIFT(U16 data);
/*! \brief Reads the register 'EPHY_ADC_GSHIFT'. */
U16  GH_EPHY_get_ADC_GSHIFT(void);
/*! \brief Writes the bit group 'adc_gshift' of register 'EPHY_ADC_GSHIFT'. */
void GH_EPHY_set_ADC_GSHIFT_adc_gshift(U8 data);
/*! \brief Reads the bit group 'adc_gshift' of register 'EPHY_ADC_GSHIFT'. */
U8   GH_EPHY_get_ADC_GSHIFT_adc_gshift(void);
/*! \brief Writes the bit group 'gain' of register 'EPHY_ADC_GSHIFT'. */
void GH_EPHY_set_ADC_GSHIFT_gain(U8 data);
/*! \brief Reads the bit group 'gain' of register 'EPHY_ADC_GSHIFT'. */
U8   GH_EPHY_get_ADC_GSHIFT_gain(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_ADC_GSHIFT(U16 data)
{
    *(volatile U16 *)REG_EPHY_ADC_GSHIFT = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GSHIFT] <-- 0x%08x\n",
                        REG_EPHY_ADC_GSHIFT,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_ADC_GSHIFT(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GSHIFT);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GSHIFT] --> 0x%08x\n",
                        REG_EPHY_ADC_GSHIFT,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_ADC_GSHIFT_adc_gshift(U8 data)
{
    GH_EPHY_ADC_GSHIFT_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GSHIFT;
    d.bitc.adc_gshift = data;
    *(volatile U16 *)REG_EPHY_ADC_GSHIFT = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GSHIFT_adc_gshift] <-- 0x%08x\n",
                        REG_EPHY_ADC_GSHIFT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GSHIFT_adc_gshift(void)
{
    GH_EPHY_ADC_GSHIFT_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GSHIFT);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GSHIFT_adc_gshift] --> 0x%08x\n",
                        REG_EPHY_ADC_GSHIFT,value);
    #endif
    return tmp_value.bitc.adc_gshift;
}
GH_INLINE void GH_EPHY_set_ADC_GSHIFT_gain(U8 data)
{
    GH_EPHY_ADC_GSHIFT_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GSHIFT;
    d.bitc.gain = data;
    *(volatile U16 *)REG_EPHY_ADC_GSHIFT = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_GSHIFT_gain] <-- 0x%08x\n",
                        REG_EPHY_ADC_GSHIFT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_GSHIFT_gain(void)
{
    GH_EPHY_ADC_GSHIFT_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GSHIFT);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_GSHIFT_gain] --> 0x%08x\n",
                        REG_EPHY_ADC_GSHIFT,value);
    #endif
    return tmp_value.bitc.gain;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ADC (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_ADC'. */
void GH_EPHY_set_ADC(U16 data);
/*! \brief Reads the register 'EPHY_ADC'. */
U16  GH_EPHY_get_ADC(void);
/*! \brief Writes the bit group 'adc_bp' of register 'EPHY_ADC'. */
void GH_EPHY_set_ADC_adc_bp(U8 data);
/*! \brief Reads the bit group 'adc_bp' of register 'EPHY_ADC'. */
U8   GH_EPHY_get_ADC_adc_bp(void);
/*! \brief Writes the bit group 'dac10t_testen' of register 'EPHY_ADC'. */
void GH_EPHY_set_ADC_dac10t_testen(U8 data);
/*! \brief Reads the bit group 'dac10t_testen' of register 'EPHY_ADC'. */
U8   GH_EPHY_get_ADC_dac10t_testen(void);
/*! \brief Writes the bit group 'reg_dac100t_testen' of register 'EPHY_ADC'. */
void GH_EPHY_set_ADC_reg_dac100t_testen(U8 data);
/*! \brief Reads the bit group 'reg_dac100t_testen' of register 'EPHY_ADC'. */
U8   GH_EPHY_get_ADC_reg_dac100t_testen(void);
/*! \brief Writes the bit group 'adc_bma' of register 'EPHY_ADC'. */
void GH_EPHY_set_ADC_adc_bma(U8 data);
/*! \brief Reads the bit group 'adc_bma' of register 'EPHY_ADC'. */
U8   GH_EPHY_get_ADC_adc_bma(void);
/*! \brief Writes the bit group 'adc_pd' of register 'EPHY_ADC'. */
void GH_EPHY_set_ADC_adc_pd(U8 data);
/*! \brief Reads the bit group 'adc_pd' of register 'EPHY_ADC'. */
U8   GH_EPHY_get_ADC_adc_pd(void);
/*! \brief Writes the bit group 'region_bank_rd' of register 'EPHY_ADC'. */
void GH_EPHY_set_ADC_region_bank_rd(U8 data);
/*! \brief Reads the bit group 'region_bank_rd' of register 'EPHY_ADC'. */
U8   GH_EPHY_get_ADC_region_bank_rd(void);
/*! \brief Writes the bit group 'adcpll_ana_clken' of register 'EPHY_ADC'. */
void GH_EPHY_set_ADC_adcpll_ana_clken(U8 data);
/*! \brief Reads the bit group 'adcpll_ana_clken' of register 'EPHY_ADC'. */
U8   GH_EPHY_get_ADC_adcpll_ana_clken(void);
/*! \brief Writes the bit group 'adcbin_testen' of register 'EPHY_ADC'. */
void GH_EPHY_set_ADC_adcbin_testen(U8 data);
/*! \brief Reads the bit group 'adcbin_testen' of register 'EPHY_ADC'. */
U8   GH_EPHY_get_ADC_adcbin_testen(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_ADC(U16 data)
{
    *(volatile U16 *)REG_EPHY_ADC = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC] <-- 0x%08x\n",
                        REG_EPHY_ADC,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_ADC(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ADC);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC] --> 0x%08x\n",
                        REG_EPHY_ADC,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_ADC_adc_bp(U8 data)
{
    GH_EPHY_ADC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC;
    d.bitc.adc_bp = data;
    *(volatile U16 *)REG_EPHY_ADC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_adc_bp] <-- 0x%08x\n",
                        REG_EPHY_ADC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_adc_bp(void)
{
    GH_EPHY_ADC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_adc_bp] --> 0x%08x\n",
                        REG_EPHY_ADC,value);
    #endif
    return tmp_value.bitc.adc_bp;
}
GH_INLINE void GH_EPHY_set_ADC_dac10t_testen(U8 data)
{
    GH_EPHY_ADC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC;
    d.bitc.dac10t_testen = data;
    *(volatile U16 *)REG_EPHY_ADC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_dac10t_testen] <-- 0x%08x\n",
                        REG_EPHY_ADC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_dac10t_testen(void)
{
    GH_EPHY_ADC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_dac10t_testen] --> 0x%08x\n",
                        REG_EPHY_ADC,value);
    #endif
    return tmp_value.bitc.dac10t_testen;
}
GH_INLINE void GH_EPHY_set_ADC_reg_dac100t_testen(U8 data)
{
    GH_EPHY_ADC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC;
    d.bitc.reg_dac100t_testen = data;
    *(volatile U16 *)REG_EPHY_ADC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_reg_dac100t_testen] <-- 0x%08x\n",
                        REG_EPHY_ADC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_reg_dac100t_testen(void)
{
    GH_EPHY_ADC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_reg_dac100t_testen] --> 0x%08x\n",
                        REG_EPHY_ADC,value);
    #endif
    return tmp_value.bitc.reg_dac100t_testen;
}
GH_INLINE void GH_EPHY_set_ADC_adc_bma(U8 data)
{
    GH_EPHY_ADC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC;
    d.bitc.adc_bma = data;
    *(volatile U16 *)REG_EPHY_ADC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_adc_bma] <-- 0x%08x\n",
                        REG_EPHY_ADC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_adc_bma(void)
{
    GH_EPHY_ADC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_adc_bma] --> 0x%08x\n",
                        REG_EPHY_ADC,value);
    #endif
    return tmp_value.bitc.adc_bma;
}
GH_INLINE void GH_EPHY_set_ADC_adc_pd(U8 data)
{
    GH_EPHY_ADC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC;
    d.bitc.adc_pd = data;
    *(volatile U16 *)REG_EPHY_ADC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_adc_pd] <-- 0x%08x\n",
                        REG_EPHY_ADC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_adc_pd(void)
{
    GH_EPHY_ADC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_adc_pd] --> 0x%08x\n",
                        REG_EPHY_ADC,value);
    #endif
    return tmp_value.bitc.adc_pd;
}
GH_INLINE void GH_EPHY_set_ADC_region_bank_rd(U8 data)
{
    GH_EPHY_ADC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC;
    d.bitc.region_bank_rd = data;
    *(volatile U16 *)REG_EPHY_ADC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_region_bank_rd] <-- 0x%08x\n",
                        REG_EPHY_ADC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_region_bank_rd(void)
{
    GH_EPHY_ADC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_region_bank_rd] --> 0x%08x\n",
                        REG_EPHY_ADC,value);
    #endif
    return tmp_value.bitc.region_bank_rd;
}
GH_INLINE void GH_EPHY_set_ADC_adcpll_ana_clken(U8 data)
{
    GH_EPHY_ADC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC;
    d.bitc.adcpll_ana_clken = data;
    *(volatile U16 *)REG_EPHY_ADC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_adcpll_ana_clken] <-- 0x%08x\n",
                        REG_EPHY_ADC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_adcpll_ana_clken(void)
{
    GH_EPHY_ADC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_adcpll_ana_clken] --> 0x%08x\n",
                        REG_EPHY_ADC,value);
    #endif
    return tmp_value.bitc.adcpll_ana_clken;
}
GH_INLINE void GH_EPHY_set_ADC_adcbin_testen(U8 data)
{
    GH_EPHY_ADC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC;
    d.bitc.adcbin_testen = data;
    *(volatile U16 *)REG_EPHY_ADC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_adcbin_testen] <-- 0x%08x\n",
                        REG_EPHY_ADC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_adcbin_testen(void)
{
    GH_EPHY_ADC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_adcbin_testen] --> 0x%08x\n",
                        REG_EPHY_ADC,value);
    #endif
    return tmp_value.bitc.adcbin_testen;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_PLL_ADC_CTRL3 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_PLL_ADC_CTRL3'. */
void GH_EPHY_set_PLL_ADC_CTRL3(U16 data);
/*! \brief Reads the register 'EPHY_PLL_ADC_CTRL3'. */
U16  GH_EPHY_get_PLL_ADC_CTRL3(void);
/*! \brief Writes the bit group 'rxlpf_pd' of register 'EPHY_PLL_ADC_CTRL3'. */
void GH_EPHY_set_PLL_ADC_CTRL3_rxlpf_pd(U8 data);
/*! \brief Reads the bit group 'rxlpf_pd' of register 'EPHY_PLL_ADC_CTRL3'. */
U8   GH_EPHY_get_PLL_ADC_CTRL3_rxlpf_pd(void);
/*! \brief Writes the bit group 'tx_b_test' of register 'EPHY_PLL_ADC_CTRL3'. */
void GH_EPHY_set_PLL_ADC_CTRL3_tx_b_test(U8 data);
/*! \brief Reads the bit group 'tx_b_test' of register 'EPHY_PLL_ADC_CTRL3'. */
U8   GH_EPHY_get_PLL_ADC_CTRL3_tx_b_test(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL3(U16 data)
{
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3 = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL3] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL3,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_PLL_ADC_CTRL3(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL3] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL3,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL3_rxlpf_pd(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL3_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3;
    d.bitc.rxlpf_pd = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL3_rxlpf_pd] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL3_rxlpf_pd(void)
{
    GH_EPHY_PLL_ADC_CTRL3_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL3_rxlpf_pd] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL3,value);
    #endif
    return tmp_value.bitc.rxlpf_pd;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL3_tx_b_test(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL3_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3;
    d.bitc.tx_b_test = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL3_tx_b_test] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL3,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL3_tx_b_test(void)
{
    GH_EPHY_PLL_ADC_CTRL3_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL3_tx_b_test] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL3,value);
    #endif
    return tmp_value.bitc.tx_b_test;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_RX_LPF (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF(U16 data);
/*! \brief Reads the register 'EPHY_RX_LPF'. */
U16  GH_EPHY_get_RX_LPF(void);
/*! \brief Writes the bit group 'rxlpf_ibsel' of register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF_rxlpf_ibsel(U8 data);
/*! \brief Reads the bit group 'rxlpf_ibsel' of register 'EPHY_RX_LPF'. */
U8   GH_EPHY_get_RX_LPF_rxlpf_ibsel(void);
/*! \brief Writes the bit group 'rxlpf_bwsel' of register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF_rxlpf_bwsel(U8 data);
/*! \brief Reads the bit group 'rxlpf_bwsel' of register 'EPHY_RX_LPF'. */
U8   GH_EPHY_get_RX_LPF_rxlpf_bwsel(void);
/*! \brief Writes the bit group 'unkown' of register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF_unkown(U8 data);
/*! \brief Reads the bit group 'unkown' of register 'EPHY_RX_LPF'. */
U8   GH_EPHY_get_RX_LPF_unkown(void);
/*! \brief Writes the bit group 'rxlpf_cmsel' of register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF_rxlpf_cmsel(U8 data);
/*! \brief Reads the bit group 'rxlpf_cmsel' of register 'EPHY_RX_LPF'. */
U8   GH_EPHY_get_RX_LPF_rxlpf_cmsel(void);
/*! \brief Writes the bit group 'rxlpf_outp_test' of register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF_rxlpf_outp_test(U8 data);
/*! \brief Reads the bit group 'rxlpf_outp_test' of register 'EPHY_RX_LPF'. */
U8   GH_EPHY_get_RX_LPF_rxlpf_outp_test(void);
/*! \brief Writes the bit group 'rxlpf_outm_test' of register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF_rxlpf_outm_test(U8 data);
/*! \brief Reads the bit group 'rxlpf_outm_test' of register 'EPHY_RX_LPF'. */
U8   GH_EPHY_get_RX_LPF_rxlpf_outm_test(void);
/*! \brief Writes the bit group 'rxlpf_bypass' of register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF_rxlpf_bypass(U8 data);
/*! \brief Reads the bit group 'rxlpf_bypass' of register 'EPHY_RX_LPF'. */
U8   GH_EPHY_get_RX_LPF_rxlpf_bypass(void);
/*! \brief Writes the bit group 'ref_pd' of register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF_ref_pd(U8 data);
/*! \brief Reads the bit group 'ref_pd' of register 'EPHY_RX_LPF'. */
U8   GH_EPHY_get_RX_LPF_ref_pd(void);
/*! \brief Writes the bit group 'ref_iint_pd' of register 'EPHY_RX_LPF'. */
void GH_EPHY_set_RX_LPF_ref_iint_pd(U8 data);
/*! \brief Reads the bit group 'ref_iint_pd' of register 'EPHY_RX_LPF'. */
U8   GH_EPHY_get_RX_LPF_ref_iint_pd(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_RX_LPF(U16 data)
{
    *(volatile U16 *)REG_EPHY_RX_LPF = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_RX_LPF(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_ibsel(U8 data)
{
    GH_EPHY_RX_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF;
    d.bitc.rxlpf_ibsel = data;
    *(volatile U16 *)REG_EPHY_RX_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF_rxlpf_ibsel] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_ibsel(void)
{
    GH_EPHY_RX_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF_rxlpf_ibsel] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return tmp_value.bitc.rxlpf_ibsel;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_bwsel(U8 data)
{
    GH_EPHY_RX_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF;
    d.bitc.rxlpf_bwsel = data;
    *(volatile U16 *)REG_EPHY_RX_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF_rxlpf_bwsel] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_bwsel(void)
{
    GH_EPHY_RX_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF_rxlpf_bwsel] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return tmp_value.bitc.rxlpf_bwsel;
}
GH_INLINE void GH_EPHY_set_RX_LPF_unkown(U8 data)
{
    GH_EPHY_RX_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF;
    d.bitc.unkown = data;
    *(volatile U16 *)REG_EPHY_RX_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF_unkown] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_unkown(void)
{
    GH_EPHY_RX_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF_unkown] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return tmp_value.bitc.unkown;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_cmsel(U8 data)
{
    GH_EPHY_RX_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF;
    d.bitc.rxlpf_cmsel = data;
    *(volatile U16 *)REG_EPHY_RX_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF_rxlpf_cmsel] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_cmsel(void)
{
    GH_EPHY_RX_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF_rxlpf_cmsel] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return tmp_value.bitc.rxlpf_cmsel;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_outp_test(U8 data)
{
    GH_EPHY_RX_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF;
    d.bitc.rxlpf_outp_test = data;
    *(volatile U16 *)REG_EPHY_RX_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF_rxlpf_outp_test] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_outp_test(void)
{
    GH_EPHY_RX_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF_rxlpf_outp_test] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return tmp_value.bitc.rxlpf_outp_test;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_outm_test(U8 data)
{
    GH_EPHY_RX_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF;
    d.bitc.rxlpf_outm_test = data;
    *(volatile U16 *)REG_EPHY_RX_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF_rxlpf_outm_test] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_outm_test(void)
{
    GH_EPHY_RX_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF_rxlpf_outm_test] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return tmp_value.bitc.rxlpf_outm_test;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_bypass(U8 data)
{
    GH_EPHY_RX_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF;
    d.bitc.rxlpf_bypass = data;
    *(volatile U16 *)REG_EPHY_RX_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF_rxlpf_bypass] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_bypass(void)
{
    GH_EPHY_RX_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF_rxlpf_bypass] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return tmp_value.bitc.rxlpf_bypass;
}
GH_INLINE void GH_EPHY_set_RX_LPF_ref_pd(U8 data)
{
    GH_EPHY_RX_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF;
    d.bitc.ref_pd = data;
    *(volatile U16 *)REG_EPHY_RX_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF_ref_pd] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_ref_pd(void)
{
    GH_EPHY_RX_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF_ref_pd] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return tmp_value.bitc.ref_pd;
}
GH_INLINE void GH_EPHY_set_RX_LPF_ref_iint_pd(U8 data)
{
    GH_EPHY_RX_LPF_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF;
    d.bitc.ref_iint_pd = data;
    *(volatile U16 *)REG_EPHY_RX_LPF = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_RX_LPF_ref_iint_pd] <-- 0x%08x\n",
                        REG_EPHY_RX_LPF,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_ref_iint_pd(void)
{
    GH_EPHY_RX_LPF_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_RX_LPF_ref_iint_pd] --> 0x%08x\n",
                        REG_EPHY_RX_LPF,value);
    #endif
    return tmp_value.bitc.ref_iint_pd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_PLL_ADC_CTRL0 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0(U16 data);
/*! \brief Reads the register 'EPHY_PLL_ADC_CTRL0'. */
U16  GH_EPHY_get_PLL_ADC_CTRL0(void);
/*! \brief Writes the bit group 'ro_adcpl_lock' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_lock(U8 data);
/*! \brief Reads the bit group 'ro_adcpl_lock' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_ro_adcpl_lock(void);
/*! \brief Writes the bit group 'gcr_adcpl_div' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_div(U8 data);
/*! \brief Reads the bit group 'gcr_adcpl_div' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_gcr_adcpl_div(void);
/*! \brief Writes the bit group 'test_adcpl_extcksel' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_test_adcpl_extcksel(U8 data);
/*! \brief Reads the bit group 'test_adcpl_extcksel' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_test_adcpl_extcksel(void);
/*! \brief Writes the bit group 'ro_adcpl_high_flag' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_high_flag(U8 data);
/*! \brief Reads the bit group 'ro_adcpl_high_flag' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_ro_adcpl_high_flag(void);
/*! \brief Writes the bit group 'pllclk_outen' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_pllclk_outen(U8 data);
/*! \brief Reads the bit group 'pllclk_outen' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_pllclk_outen(void);
/*! \brief Writes the bit group 'ov_ref_test' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_ov_ref_test(U8 data);
/*! \brief Reads the bit group 'ov_ref_test' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_ov_ref_test(void);
/*! \brief Writes the bit group 'gc_adcpl_rstb' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_gc_adcpl_rstb(U8 data);
/*! \brief Reads the bit group 'gc_adcpl_rstb' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_gc_adcpl_rstb(void);
/*! \brief Writes the bit group 'ref_bgap_pd' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_ref_bgap_pd(U8 data);
/*! \brief Reads the bit group 'ref_bgap_pd' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_ref_bgap_pd(void);
/*! \brief Writes the bit group 'adcraw_tst' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst(U8 data);
/*! \brief Reads the bit group 'adcraw_tst' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_adcraw_tst(void);
/*! \brief Writes the bit group 'adcraw_tst_sw' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst_sw(U8 data);
/*! \brief Reads the bit group 'adcraw_tst_sw' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_adcraw_tst_sw(void);
/*! \brief Writes the bit group 'ldo_pwrgd' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_ldo_pwrgd(U8 data);
/*! \brief Reads the bit group 'ldo_pwrgd' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_ldo_pwrgd(void);
/*! \brief Writes the bit group 'adcraw_overflow' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_adcraw_overflow(U8 data);
/*! \brief Reads the bit group 'adcraw_overflow' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_adcraw_overflow(void);
/*! \brief Writes the bit group 'adcpl_force_phase' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_adcpl_force_phase(U8 data);
/*! \brief Reads the bit group 'adcpl_force_phase' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_adcpl_force_phase(void);
/*! \brief Writes the bit group 'gcr_adcpl_tog_clkcc' of register 'EPHY_PLL_ADC_CTRL0'. */
void GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_tog_clkcc(U8 data);
/*! \brief Reads the bit group 'gcr_adcpl_tog_clkcc' of register 'EPHY_PLL_ADC_CTRL0'. */
U8   GH_EPHY_get_PLL_ADC_CTRL0_gcr_adcpl_tog_clkcc(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0(U16 data)
{
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_PLL_ADC_CTRL0(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_lock(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.ro_adcpl_lock = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_lock] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ro_adcpl_lock(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_ro_adcpl_lock] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.ro_adcpl_lock;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_div(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.gcr_adcpl_div = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_div] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_gcr_adcpl_div(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_gcr_adcpl_div] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.gcr_adcpl_div;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_test_adcpl_extcksel(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.test_adcpl_extcksel = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_test_adcpl_extcksel] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_test_adcpl_extcksel(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_test_adcpl_extcksel] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.test_adcpl_extcksel;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_high_flag(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.ro_adcpl_high_flag = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_high_flag] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ro_adcpl_high_flag(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_ro_adcpl_high_flag] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.ro_adcpl_high_flag;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_pllclk_outen(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.pllclk_outen = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_pllclk_outen] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_pllclk_outen(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_pllclk_outen] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.pllclk_outen;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ov_ref_test(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.ov_ref_test = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_ov_ref_test] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ov_ref_test(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_ov_ref_test] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.ov_ref_test;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_gc_adcpl_rstb(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.gc_adcpl_rstb = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_gc_adcpl_rstb] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_gc_adcpl_rstb(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_gc_adcpl_rstb] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.gc_adcpl_rstb;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ref_bgap_pd(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.ref_bgap_pd = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_ref_bgap_pd] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ref_bgap_pd(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_ref_bgap_pd] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.ref_bgap_pd;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.adcraw_tst = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_adcraw_tst(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_adcraw_tst] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.adcraw_tst;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst_sw(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.adcraw_tst_sw = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst_sw] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_adcraw_tst_sw(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_adcraw_tst_sw] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.adcraw_tst_sw;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ldo_pwrgd(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.ldo_pwrgd = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_ldo_pwrgd] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ldo_pwrgd(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_ldo_pwrgd] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.ldo_pwrgd;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_adcraw_overflow(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.adcraw_overflow = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_adcraw_overflow] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_adcraw_overflow(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_adcraw_overflow] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.adcraw_overflow;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_adcpl_force_phase(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.adcpl_force_phase = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_adcpl_force_phase] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_adcpl_force_phase(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_adcpl_force_phase] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.adcpl_force_phase;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_tog_clkcc(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0;
    d.bitc.gcr_adcpl_tog_clkcc = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_tog_clkcc] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_gcr_adcpl_tog_clkcc(void)
{
    GH_EPHY_PLL_ADC_CTRL0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL0_gcr_adcpl_tog_clkcc] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL0,value);
    #endif
    return tmp_value.bitc.gcr_adcpl_tog_clkcc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_PLL_ADC_CTRL1 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1(U16 data);
/*! \brief Reads the register 'EPHY_PLL_ADC_CTRL1'. */
U16  GH_EPHY_get_PLL_ADC_CTRL1(void);
/*! \brief Writes the bit group 'gc_adcpl_adcpd0' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd0(U8 data);
/*! \brief Reads the bit group 'gc_adcpl_adcpd0' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcpd0(void);
/*! \brief Writes the bit group 'gc_adcpl_adcpd1' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd1(U8 data);
/*! \brief Reads the bit group 'gc_adcpl_adcpd1' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcpd1(void);
/*! \brief Writes the bit group 'gc_adcpl_ccpd0' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd0(U8 data);
/*! \brief Reads the bit group 'gc_adcpl_ccpd0' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_ccpd0(void);
/*! \brief Writes the bit group 'gc_adcpl_ccpd1' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd1(U8 data);
/*! \brief Reads the bit group 'gc_adcpl_ccpd1' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_ccpd1(void);
/*! \brief Writes the bit group 'pd_adcpl_reg' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_pd_adcpl_reg(U8 data);
/*! \brief Reads the bit group 'pd_adcpl_reg' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_pd_adcpl_reg(void);
/*! \brief Writes the bit group 'gcr_adcpl_mod_100t' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_mod_100t(U8 data);
/*! \brief Reads the bit group 'gcr_adcpl_mod_100t' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_mod_100t(void);
/*! \brief Writes the bit group 'gcr_adcpl_ictrl' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_ictrl(U8 data);
/*! \brief Reads the bit group 'gcr_adcpl_ictrl' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_ictrl(void);
/*! \brief Writes the bit group 'gcr_adcpl_enfrunz' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_enfrunz(U8 data);
/*! \brief Reads the bit group 'gcr_adcpl_enfrunz' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_enfrunz(void);
/*! \brief Writes the bit group 'en_adcpl_porst' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_porst(U8 data);
/*! \brief Reads the bit group 'en_adcpl_porst' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_en_adcpl_porst(void);
/*! \brief Writes the bit group 'en_adcpl_adcphdac' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_adcphdac(U8 data);
/*! \brief Reads the bit group 'en_adcpl_adcphdac' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_en_adcpl_adcphdac(void);
/*! \brief Writes the bit group 'gc_adcpl_adcselect' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcselect(U8 data);
/*! \brief Reads the bit group 'gc_adcpl_adcselect' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcselect(void);
/*! \brief Writes the bit group 'tx_d_test' of register 'EPHY_PLL_ADC_CTRL1'. */
void GH_EPHY_set_PLL_ADC_CTRL1_tx_d_test(U8 data);
/*! \brief Reads the bit group 'tx_d_test' of register 'EPHY_PLL_ADC_CTRL1'. */
U8   GH_EPHY_get_PLL_ADC_CTRL1_tx_d_test(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1(U16 data)
{
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_PLL_ADC_CTRL1(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd0(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.gc_adcpl_adcpd0 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd0] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcpd0(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcpd0] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.gc_adcpl_adcpd0;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd1(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.gc_adcpl_adcpd1 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd1] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcpd1(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcpd1] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.gc_adcpl_adcpd1;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd0(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.gc_adcpl_ccpd0 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd0] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_ccpd0(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_ccpd0] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.gc_adcpl_ccpd0;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd1(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.gc_adcpl_ccpd1 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd1] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_ccpd1(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_ccpd1] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.gc_adcpl_ccpd1;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_pd_adcpl_reg(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.pd_adcpl_reg = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_pd_adcpl_reg] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_pd_adcpl_reg(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_pd_adcpl_reg] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.pd_adcpl_reg;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_mod_100t(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.gcr_adcpl_mod_100t = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_mod_100t] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_mod_100t(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_mod_100t] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.gcr_adcpl_mod_100t;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_ictrl(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.gcr_adcpl_ictrl = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_ictrl] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_ictrl(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_ictrl] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.gcr_adcpl_ictrl;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_enfrunz(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.gcr_adcpl_enfrunz = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_enfrunz] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_enfrunz(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_enfrunz] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.gcr_adcpl_enfrunz;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_porst(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.en_adcpl_porst = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_porst] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_en_adcpl_porst(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_en_adcpl_porst] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.en_adcpl_porst;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_adcphdac(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.en_adcpl_adcphdac = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_adcphdac] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_en_adcpl_adcphdac(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_en_adcpl_adcphdac] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.en_adcpl_adcphdac;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcselect(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.gc_adcpl_adcselect = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcselect] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcselect(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcselect] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.gc_adcpl_adcselect;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_tx_d_test(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1;
    d.bitc.tx_d_test = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL1_tx_d_test] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_tx_d_test(void)
{
    GH_EPHY_PLL_ADC_CTRL1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL1_tx_d_test] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL1,value);
    #endif
    return tmp_value.bitc.tx_d_test;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_PLL_ADC_CTRL2 (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2(U16 data);
/*! \brief Reads the register 'EPHY_PLL_ADC_CTRL2'. */
U16  GH_EPHY_get_PLL_ADC_CTRL2(void);
/*! \brief Writes the bit group 'gc_ref_vgen' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vgen(U8 data);
/*! \brief Reads the bit group 'gc_ref_vgen' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vgen(void);
/*! \brief Writes the bit group 'gc_ref_vcom' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcom(U8 data);
/*! \brief Reads the bit group 'gc_ref_vcom' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vcom(void);
/*! \brief Writes the bit group 'gc_ref_vcmpcmvx' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcmpcmvx(U8 data);
/*! \brief Reads the bit group 'gc_ref_vcmpcmvx' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vcmpcmvx(void);
/*! \brief Writes the bit group 'pd_lpf_op' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_pd_lpf_op(U8 data);
/*! \brief Reads the bit group 'pd_lpf_op' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_pd_lpf_op(void);
/*! \brief Writes the bit group 'gc_adc_force1' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force1(U8 data);
/*! \brief Reads the bit group 'gc_adc_force1' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_adc_force1(void);
/*! \brief Writes the bit group 'gc_adc_force0' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force0(U8 data);
/*! \brief Reads the bit group 'gc_adc_force0' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_adc_force0(void);
/*! \brief Writes the bit group 'endiscz_10' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_endiscz_10(U8 data);
/*! \brief Reads the bit group 'endiscz_10' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_endiscz_10(void);
/*! \brief Writes the bit group 'gcr_adcpl_pdphadc' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_gcr_adcpl_pdphadc(U8 data);
/*! \brief Reads the bit group 'gcr_adcpl_pdphadc' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_gcr_adcpl_pdphadc(void);
/*! \brief Writes the bit group 'adcpl_bank' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_bank(U8 data);
/*! \brief Reads the bit group 'adcpl_bank' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_bank(void);
/*! \brief Writes the bit group 'adcpl_phase_force' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force(U8 data);
/*! \brief Reads the bit group 'adcpl_phase_force' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_phase_force(void);
/*! \brief Writes the bit group 'adcpl_phase_force_st' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force_st(U8 data);
/*! \brief Reads the bit group 'adcpl_phase_force_st' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_phase_force_st(void);
/*! \brief Writes the bit group 'adcpl_force_go' of register 'EPHY_PLL_ADC_CTRL2'. */
void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_force_go(U8 data);
/*! \brief Reads the bit group 'adcpl_force_go' of register 'EPHY_PLL_ADC_CTRL2'. */
U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_force_go(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2(U16 data)
{
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_PLL_ADC_CTRL2(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vgen(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.gc_ref_vgen = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vgen] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vgen(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vgen] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.gc_ref_vgen;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcom(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.gc_ref_vcom = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcom] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vcom(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vcom] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.gc_ref_vcom;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcmpcmvx(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.gc_ref_vcmpcmvx = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcmpcmvx] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vcmpcmvx(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vcmpcmvx] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.gc_ref_vcmpcmvx;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_pd_lpf_op(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.pd_lpf_op = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_pd_lpf_op] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_pd_lpf_op(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_pd_lpf_op] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.pd_lpf_op;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force1(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.gc_adc_force1 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force1] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_adc_force1(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_gc_adc_force1] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.gc_adc_force1;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force0(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.gc_adc_force0 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force0] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_adc_force0(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_gc_adc_force0] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.gc_adc_force0;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_endiscz_10(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.endiscz_10 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_endiscz_10] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_endiscz_10(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_endiscz_10] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.endiscz_10;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gcr_adcpl_pdphadc(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.gcr_adcpl_pdphadc = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_gcr_adcpl_pdphadc] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gcr_adcpl_pdphadc(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_gcr_adcpl_pdphadc] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.gcr_adcpl_pdphadc;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_bank(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.adcpl_bank = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_adcpl_bank] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_bank(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_adcpl_bank] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.adcpl_bank;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.adcpl_phase_force = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_phase_force(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_adcpl_phase_force] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.adcpl_phase_force;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force_st(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.adcpl_phase_force_st = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force_st] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_phase_force_st(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_adcpl_phase_force_st] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.adcpl_phase_force_st;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_force_go(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2;
    d.bitc.adcpl_force_go = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PLL_ADC_CTRL2_adcpl_force_go] <-- 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_force_go(void)
{
    GH_EPHY_PLL_ADC_CTRL2_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PLL_ADC_CTRL2_adcpl_force_go] --> 0x%08x\n",
                        REG_EPHY_PLL_ADC_CTRL2,value);
    #endif
    return tmp_value.bitc.adcpl_force_go;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_TEST_TX (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_TEST_TX'. */
void GH_EPHY_set_TEST_TX(U16 data);
/*! \brief Reads the register 'EPHY_TEST_TX'. */
U16  GH_EPHY_get_TEST_TX(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_TEST_TX(U16 data)
{
    *(volatile U16 *)REG_EPHY_TEST_TX = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_TEST_TX] <-- 0x%08x\n",
                        REG_EPHY_TEST_TX,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_TEST_TX(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_TEST_TX);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_TEST_TX] --> 0x%08x\n",
                        REG_EPHY_TEST_TX,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_PWR (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_PWR'. */
void GH_EPHY_set_PWR(U16 data);
/*! \brief Reads the register 'EPHY_PWR'. */
U16  GH_EPHY_get_PWR(void);
/*! \brief Writes the bit group 'pwr_k_in_lp' of register 'EPHY_PWR'. */
void GH_EPHY_set_PWR_pwr_k_in_lp(U8 data);
/*! \brief Reads the bit group 'pwr_k_in_lp' of register 'EPHY_PWR'. */
U8   GH_EPHY_get_PWR_pwr_k_in_lp(void);
/*! \brief Writes the bit group 'dtpwr_enable_lp' of register 'EPHY_PWR'. */
void GH_EPHY_set_PWR_dtpwr_enable_lp(U8 data);
/*! \brief Reads the bit group 'dtpwr_enable_lp' of register 'EPHY_PWR'. */
U8   GH_EPHY_get_PWR_dtpwr_enable_lp(void);
/*! \brief Writes the bit group 'gcr_adcpl_div_lp' of register 'EPHY_PWR'. */
void GH_EPHY_set_PWR_gcr_adcpl_div_lp(U8 data);
/*! \brief Reads the bit group 'gcr_adcpl_div_lp' of register 'EPHY_PWR'. */
U8   GH_EPHY_get_PWR_gcr_adcpl_div_lp(void);
/*! \brief Writes the bit group 'dummy' of register 'EPHY_PWR'. */
void GH_EPHY_set_PWR_dummy(U16 data);
/*! \brief Reads the bit group 'dummy' of register 'EPHY_PWR'. */
U16  GH_EPHY_get_PWR_dummy(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_PWR(U16 data)
{
    *(volatile U16 *)REG_EPHY_PWR = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PWR] <-- 0x%08x\n",
                        REG_EPHY_PWR,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_PWR(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_PWR);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PWR] --> 0x%08x\n",
                        REG_EPHY_PWR,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_PWR_pwr_k_in_lp(U8 data)
{
    GH_EPHY_PWR_S d;
    d.all = *(volatile U16 *)REG_EPHY_PWR;
    d.bitc.pwr_k_in_lp = data;
    *(volatile U16 *)REG_EPHY_PWR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PWR_pwr_k_in_lp] <-- 0x%08x\n",
                        REG_EPHY_PWR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PWR_pwr_k_in_lp(void)
{
    GH_EPHY_PWR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PWR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PWR_pwr_k_in_lp] --> 0x%08x\n",
                        REG_EPHY_PWR,value);
    #endif
    return tmp_value.bitc.pwr_k_in_lp;
}
GH_INLINE void GH_EPHY_set_PWR_dtpwr_enable_lp(U8 data)
{
    GH_EPHY_PWR_S d;
    d.all = *(volatile U16 *)REG_EPHY_PWR;
    d.bitc.dtpwr_enable_lp = data;
    *(volatile U16 *)REG_EPHY_PWR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PWR_dtpwr_enable_lp] <-- 0x%08x\n",
                        REG_EPHY_PWR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PWR_dtpwr_enable_lp(void)
{
    GH_EPHY_PWR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PWR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PWR_dtpwr_enable_lp] --> 0x%08x\n",
                        REG_EPHY_PWR,value);
    #endif
    return tmp_value.bitc.dtpwr_enable_lp;
}
GH_INLINE void GH_EPHY_set_PWR_gcr_adcpl_div_lp(U8 data)
{
    GH_EPHY_PWR_S d;
    d.all = *(volatile U16 *)REG_EPHY_PWR;
    d.bitc.gcr_adcpl_div_lp = data;
    *(volatile U16 *)REG_EPHY_PWR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PWR_gcr_adcpl_div_lp] <-- 0x%08x\n",
                        REG_EPHY_PWR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_PWR_gcr_adcpl_div_lp(void)
{
    GH_EPHY_PWR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PWR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PWR_gcr_adcpl_div_lp] --> 0x%08x\n",
                        REG_EPHY_PWR,value);
    #endif
    return tmp_value.bitc.gcr_adcpl_div_lp;
}
GH_INLINE void GH_EPHY_set_PWR_dummy(U16 data)
{
    GH_EPHY_PWR_S d;
    d.all = *(volatile U16 *)REG_EPHY_PWR;
    d.bitc.dummy = data;
    *(volatile U16 *)REG_EPHY_PWR = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_PWR_dummy] <-- 0x%08x\n",
                        REG_EPHY_PWR,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_EPHY_get_PWR_dummy(void)
{
    GH_EPHY_PWR_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PWR);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_PWR_dummy] --> 0x%08x\n",
                        REG_EPHY_PWR,value);
    #endif
    return tmp_value.bitc.dummy;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ADC_DC (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC(U16 data);
/*! \brief Reads the register 'EPHY_ADC_DC'. */
U16  GH_EPHY_get_ADC_DC(void);
/*! \brief Writes the bit group 'dc_force_en' of register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC_dc_force_en(U8 data);
/*! \brief Reads the bit group 'dc_force_en' of register 'EPHY_ADC_DC'. */
U8   GH_EPHY_get_ADC_DC_dc_force_en(void);
/*! \brief Writes the bit group 'dc_force' of register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC_dc_force(U8 data);
/*! \brief Reads the bit group 'dc_force' of register 'EPHY_ADC_DC'. */
U8   GH_EPHY_get_ADC_DC_dc_force(void);
/*! \brief Writes the bit group 'dc_can_inv' of register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC_dc_can_inv(U8 data);
/*! \brief Reads the bit group 'dc_can_inv' of register 'EPHY_ADC_DC'. */
U8   GH_EPHY_get_ADC_DC_dc_can_inv(void);
/*! \brief Writes the bit group 'analog_blw' of register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC_analog_blw(U8 data);
/*! \brief Reads the bit group 'analog_blw' of register 'EPHY_ADC_DC'. */
U8   GH_EPHY_get_ADC_DC_analog_blw(void);
/*! \brief Writes the bit group 'dc_k' of register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC_dc_k(U8 data);
/*! \brief Reads the bit group 'dc_k' of register 'EPHY_ADC_DC'. */
U8   GH_EPHY_get_ADC_DC_dc_k(void);
/*! \brief Writes the bit group 'srst' of register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC_srst(U8 data);
/*! \brief Reads the bit group 'srst' of register 'EPHY_ADC_DC'. */
U8   GH_EPHY_get_ADC_DC_srst(void);
/*! \brief Writes the bit group 'adc_cancel_out' of register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC_adc_cancel_out(U8 data);
/*! \brief Reads the bit group 'adc_cancel_out' of register 'EPHY_ADC_DC'. */
U8   GH_EPHY_get_ADC_DC_adc_cancel_out(void);
/*! \brief Writes the bit group 'adc_cancel_disable' of register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC_adc_cancel_disable(U8 data);
/*! \brief Reads the bit group 'adc_cancel_disable' of register 'EPHY_ADC_DC'. */
U8   GH_EPHY_get_ADC_DC_adc_cancel_disable(void);
/*! \brief Writes the bit group 'adc_start' of register 'EPHY_ADC_DC'. */
void GH_EPHY_set_ADC_DC_adc_start(U8 data);
/*! \brief Reads the bit group 'adc_start' of register 'EPHY_ADC_DC'. */
U8   GH_EPHY_get_ADC_DC_adc_start(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_ADC_DC(U16 data)
{
    *(volatile U16 *)REG_EPHY_ADC_DC = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_ADC_DC(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_ADC_DC_dc_force_en(U8 data)
{
    GH_EPHY_ADC_DC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC;
    d.bitc.dc_force_en = data;
    *(volatile U16 *)REG_EPHY_ADC_DC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC_dc_force_en] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_dc_force_en(void)
{
    GH_EPHY_ADC_DC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC_dc_force_en] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return tmp_value.bitc.dc_force_en;
}
GH_INLINE void GH_EPHY_set_ADC_DC_dc_force(U8 data)
{
    GH_EPHY_ADC_DC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC;
    d.bitc.dc_force = data;
    *(volatile U16 *)REG_EPHY_ADC_DC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC_dc_force] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_dc_force(void)
{
    GH_EPHY_ADC_DC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC_dc_force] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return tmp_value.bitc.dc_force;
}
GH_INLINE void GH_EPHY_set_ADC_DC_dc_can_inv(U8 data)
{
    GH_EPHY_ADC_DC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC;
    d.bitc.dc_can_inv = data;
    *(volatile U16 *)REG_EPHY_ADC_DC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC_dc_can_inv] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_dc_can_inv(void)
{
    GH_EPHY_ADC_DC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC_dc_can_inv] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return tmp_value.bitc.dc_can_inv;
}
GH_INLINE void GH_EPHY_set_ADC_DC_analog_blw(U8 data)
{
    GH_EPHY_ADC_DC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC;
    d.bitc.analog_blw = data;
    *(volatile U16 *)REG_EPHY_ADC_DC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC_analog_blw] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_analog_blw(void)
{
    GH_EPHY_ADC_DC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC_analog_blw] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return tmp_value.bitc.analog_blw;
}
GH_INLINE void GH_EPHY_set_ADC_DC_dc_k(U8 data)
{
    GH_EPHY_ADC_DC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC;
    d.bitc.dc_k = data;
    *(volatile U16 *)REG_EPHY_ADC_DC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC_dc_k] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_dc_k(void)
{
    GH_EPHY_ADC_DC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC_dc_k] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return tmp_value.bitc.dc_k;
}
GH_INLINE void GH_EPHY_set_ADC_DC_srst(U8 data)
{
    GH_EPHY_ADC_DC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC;
    d.bitc.srst = data;
    *(volatile U16 *)REG_EPHY_ADC_DC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC_srst] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_srst(void)
{
    GH_EPHY_ADC_DC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC_srst] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return tmp_value.bitc.srst;
}
GH_INLINE void GH_EPHY_set_ADC_DC_adc_cancel_out(U8 data)
{
    GH_EPHY_ADC_DC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC;
    d.bitc.adc_cancel_out = data;
    *(volatile U16 *)REG_EPHY_ADC_DC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC_adc_cancel_out] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_adc_cancel_out(void)
{
    GH_EPHY_ADC_DC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC_adc_cancel_out] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return tmp_value.bitc.adc_cancel_out;
}
GH_INLINE void GH_EPHY_set_ADC_DC_adc_cancel_disable(U8 data)
{
    GH_EPHY_ADC_DC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC;
    d.bitc.adc_cancel_disable = data;
    *(volatile U16 *)REG_EPHY_ADC_DC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC_adc_cancel_disable] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_adc_cancel_disable(void)
{
    GH_EPHY_ADC_DC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC_adc_cancel_disable] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return tmp_value.bitc.adc_cancel_disable;
}
GH_INLINE void GH_EPHY_set_ADC_DC_adc_start(U8 data)
{
    GH_EPHY_ADC_DC_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC;
    d.bitc.adc_start = data;
    *(volatile U16 *)REG_EPHY_ADC_DC = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADC_DC_adc_start] <-- 0x%08x\n",
                        REG_EPHY_ADC_DC,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_adc_start(void)
{
    GH_EPHY_ADC_DC_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADC_DC_adc_start] --> 0x%08x\n",
                        REG_EPHY_ADC_DC,value);
    #endif
    return tmp_value.bitc.adc_start;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_ADCPL (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_ADCPL'. */
void GH_EPHY_set_ADCPL(U16 data);
/*! \brief Reads the register 'EPHY_ADCPL'. */
U16  GH_EPHY_get_ADCPL(void);
/*! \brief Writes the bit group 'mod_10t' of register 'EPHY_ADCPL'. */
void GH_EPHY_set_ADCPL_mod_10t(U8 data);
/*! \brief Reads the bit group 'mod_10t' of register 'EPHY_ADCPL'. */
U8   GH_EPHY_get_ADCPL_mod_10t(void);
/*! \brief Writes the bit group 'mod' of register 'EPHY_ADCPL'. */
void GH_EPHY_set_ADCPL_mod(U8 data);
/*! \brief Reads the bit group 'mod' of register 'EPHY_ADCPL'. */
U8   GH_EPHY_get_ADCPL_mod(void);
/*! \brief Writes the bit group 'mod_lp' of register 'EPHY_ADCPL'. */
void GH_EPHY_set_ADCPL_mod_lp(U8 data);
/*! \brief Reads the bit group 'mod_lp' of register 'EPHY_ADCPL'. */
U8   GH_EPHY_get_ADCPL_mod_lp(void);
/*! \brief Writes the bit group 'adc_frc_zero' of register 'EPHY_ADCPL'. */
void GH_EPHY_set_ADCPL_adc_frc_zero(U8 data);
/*! \brief Reads the bit group 'adc_frc_zero' of register 'EPHY_ADCPL'. */
U8   GH_EPHY_get_ADCPL_adc_frc_zero(void);
/*! \brief Writes the bit group 'adcpl_step' of register 'EPHY_ADCPL'. */
void GH_EPHY_set_ADCPL_adcpl_step(U8 data);
/*! \brief Reads the bit group 'adcpl_step' of register 'EPHY_ADCPL'. */
U8   GH_EPHY_get_ADCPL_adcpl_step(void);
/*! \brief Writes the bit group 'ac_a_timer_start' of register 'EPHY_ADCPL'. */
void GH_EPHY_set_ADCPL_ac_a_timer_start(U8 data);
/*! \brief Reads the bit group 'ac_a_timer_start' of register 'EPHY_ADCPL'. */
U8   GH_EPHY_get_ADCPL_ac_a_timer_start(void);
/*! \brief Writes the bit group 'ac_sample_timer_start' of register 'EPHY_ADCPL'. */
void GH_EPHY_set_ADCPL_ac_sample_timer_start(U8 data);
/*! \brief Reads the bit group 'ac_sample_timer_start' of register 'EPHY_ADCPL'. */
U8   GH_EPHY_get_ADCPL_ac_sample_timer_start(void);
/*! \brief Writes the bit group 'txramp_gen_10t' of register 'EPHY_ADCPL'. */
void GH_EPHY_set_ADCPL_txramp_gen_10t(U8 data);
/*! \brief Reads the bit group 'txramp_gen_10t' of register 'EPHY_ADCPL'. */
U8   GH_EPHY_get_ADCPL_txramp_gen_10t(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_ADCPL(U16 data)
{
    *(volatile U16 *)REG_EPHY_ADCPL = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADCPL] <-- 0x%08x\n",
                        REG_EPHY_ADCPL,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_ADCPL(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADCPL] --> 0x%08x\n",
                        REG_EPHY_ADCPL,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_ADCPL_mod_10t(U8 data)
{
    GH_EPHY_ADCPL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL;
    d.bitc.mod_10t = data;
    *(volatile U16 *)REG_EPHY_ADCPL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADCPL_mod_10t] <-- 0x%08x\n",
                        REG_EPHY_ADCPL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADCPL_mod_10t(void)
{
    GH_EPHY_ADCPL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADCPL_mod_10t] --> 0x%08x\n",
                        REG_EPHY_ADCPL,value);
    #endif
    return tmp_value.bitc.mod_10t;
}
GH_INLINE void GH_EPHY_set_ADCPL_mod(U8 data)
{
    GH_EPHY_ADCPL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL;
    d.bitc.mod = data;
    *(volatile U16 *)REG_EPHY_ADCPL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADCPL_mod] <-- 0x%08x\n",
                        REG_EPHY_ADCPL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADCPL_mod(void)
{
    GH_EPHY_ADCPL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADCPL_mod] --> 0x%08x\n",
                        REG_EPHY_ADCPL,value);
    #endif
    return tmp_value.bitc.mod;
}
GH_INLINE void GH_EPHY_set_ADCPL_mod_lp(U8 data)
{
    GH_EPHY_ADCPL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL;
    d.bitc.mod_lp = data;
    *(volatile U16 *)REG_EPHY_ADCPL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADCPL_mod_lp] <-- 0x%08x\n",
                        REG_EPHY_ADCPL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADCPL_mod_lp(void)
{
    GH_EPHY_ADCPL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADCPL_mod_lp] --> 0x%08x\n",
                        REG_EPHY_ADCPL,value);
    #endif
    return tmp_value.bitc.mod_lp;
}
GH_INLINE void GH_EPHY_set_ADCPL_adc_frc_zero(U8 data)
{
    GH_EPHY_ADCPL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL;
    d.bitc.adc_frc_zero = data;
    *(volatile U16 *)REG_EPHY_ADCPL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADCPL_adc_frc_zero] <-- 0x%08x\n",
                        REG_EPHY_ADCPL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADCPL_adc_frc_zero(void)
{
    GH_EPHY_ADCPL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADCPL_adc_frc_zero] --> 0x%08x\n",
                        REG_EPHY_ADCPL,value);
    #endif
    return tmp_value.bitc.adc_frc_zero;
}
GH_INLINE void GH_EPHY_set_ADCPL_adcpl_step(U8 data)
{
    GH_EPHY_ADCPL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL;
    d.bitc.adcpl_step = data;
    *(volatile U16 *)REG_EPHY_ADCPL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADCPL_adcpl_step] <-- 0x%08x\n",
                        REG_EPHY_ADCPL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADCPL_adcpl_step(void)
{
    GH_EPHY_ADCPL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADCPL_adcpl_step] --> 0x%08x\n",
                        REG_EPHY_ADCPL,value);
    #endif
    return tmp_value.bitc.adcpl_step;
}
GH_INLINE void GH_EPHY_set_ADCPL_ac_a_timer_start(U8 data)
{
    GH_EPHY_ADCPL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL;
    d.bitc.ac_a_timer_start = data;
    *(volatile U16 *)REG_EPHY_ADCPL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADCPL_ac_a_timer_start] <-- 0x%08x\n",
                        REG_EPHY_ADCPL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADCPL_ac_a_timer_start(void)
{
    GH_EPHY_ADCPL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADCPL_ac_a_timer_start] --> 0x%08x\n",
                        REG_EPHY_ADCPL,value);
    #endif
    return tmp_value.bitc.ac_a_timer_start;
}
GH_INLINE void GH_EPHY_set_ADCPL_ac_sample_timer_start(U8 data)
{
    GH_EPHY_ADCPL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL;
    d.bitc.ac_sample_timer_start = data;
    *(volatile U16 *)REG_EPHY_ADCPL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADCPL_ac_sample_timer_start] <-- 0x%08x\n",
                        REG_EPHY_ADCPL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADCPL_ac_sample_timer_start(void)
{
    GH_EPHY_ADCPL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADCPL_ac_sample_timer_start] --> 0x%08x\n",
                        REG_EPHY_ADCPL,value);
    #endif
    return tmp_value.bitc.ac_sample_timer_start;
}
GH_INLINE void GH_EPHY_set_ADCPL_txramp_gen_10t(U8 data)
{
    GH_EPHY_ADCPL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL;
    d.bitc.txramp_gen_10t = data;
    *(volatile U16 *)REG_EPHY_ADCPL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_ADCPL_txramp_gen_10t] <-- 0x%08x\n",
                        REG_EPHY_ADCPL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_ADCPL_txramp_gen_10t(void)
{
    GH_EPHY_ADCPL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_ADCPL_txramp_gen_10t] --> 0x%08x\n",
                        REG_EPHY_ADCPL,value);
    #endif
    return tmp_value.bitc.txramp_gen_10t;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_LDO (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_LDO'. */
void GH_EPHY_set_LDO(U16 data);
/*! \brief Reads the register 'EPHY_LDO'. */
U16  GH_EPHY_get_LDO(void);
/*! \brief Writes the bit group 'dummy' of register 'EPHY_LDO'. */
void GH_EPHY_set_LDO_dummy(U16 data);
/*! \brief Reads the bit group 'dummy' of register 'EPHY_LDO'. */
U16  GH_EPHY_get_LDO_dummy(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_LDO(U16 data)
{
    *(volatile U16 *)REG_EPHY_LDO = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LDO] <-- 0x%08x\n",
                        REG_EPHY_LDO,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_LDO(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_LDO);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LDO] --> 0x%08x\n",
                        REG_EPHY_LDO,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_LDO_dummy(U16 data)
{
    GH_EPHY_LDO_S d;
    d.all = *(volatile U16 *)REG_EPHY_LDO;
    d.bitc.dummy = data;
    *(volatile U16 *)REG_EPHY_LDO = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_LDO_dummy] <-- 0x%08x\n",
                        REG_EPHY_LDO,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_EPHY_get_LDO_dummy(void)
{
    GH_EPHY_LDO_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LDO);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_LDO_dummy] --> 0x%08x\n",
                        REG_EPHY_LDO,value);
    #endif
    return tmp_value.bitc.dummy;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_CLK_GATE (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'EPHY_CLK_GATE'. */
U16  GH_EPHY_get_CLK_GATE(void);
/*! \brief Reads the bit group 'eee_capability' of register 'EPHY_CLK_GATE'. */
U16  GH_EPHY_get_CLK_GATE_eee_capability(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_EPHY_get_CLK_GATE(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_CLK_GATE);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK_GATE] --> 0x%08x\n",
                        REG_EPHY_CLK_GATE,value);
    #endif
    return value;
}
GH_INLINE U16  GH_EPHY_get_CLK_GATE_eee_capability(void)
{
    GH_EPHY_CLK_GATE_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK_GATE);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK_GATE_eee_capability] --> 0x%08x\n",
                        REG_EPHY_CLK_GATE,value);
    #endif
    return tmp_value.bitc.eee_capability;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_CLK1 (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_CLK1'. */
void GH_EPHY_set_CLK1(U16 data);
/*! \brief Reads the register 'EPHY_CLK1'. */
U16  GH_EPHY_get_CLK1(void);
/*! \brief Writes the bit group 'unkown' of register 'EPHY_CLK1'. */
void GH_EPHY_set_CLK1_unkown(U8 data);
/*! \brief Reads the bit group 'unkown' of register 'EPHY_CLK1'. */
U8   GH_EPHY_get_CLK1_unkown(void);
/*! \brief Writes the bit group 'clko_200_gat' of register 'EPHY_CLK1'. */
void GH_EPHY_set_CLK1_clko_200_gat(U8 data);
/*! \brief Reads the bit group 'clko_200_gat' of register 'EPHY_CLK1'. */
U8   GH_EPHY_get_CLK1_clko_200_gat(void);
/*! \brief Writes the bit group 'clko_200_inv' of register 'EPHY_CLK1'. */
void GH_EPHY_set_CLK1_clko_200_inv(U8 data);
/*! \brief Reads the bit group 'clko_200_inv' of register 'EPHY_CLK1'. */
U8   GH_EPHY_get_CLK1_clko_200_inv(void);
/*! \brief Writes the bit group 'lut_new' of register 'EPHY_CLK1'. */
void GH_EPHY_set_CLK1_lut_new(U8 data);
/*! \brief Reads the bit group 'lut_new' of register 'EPHY_CLK1'. */
U8   GH_EPHY_get_CLK1_lut_new(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_CLK1(U16 data)
{
    *(volatile U16 *)REG_EPHY_CLK1 = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK1] <-- 0x%08x\n",
                        REG_EPHY_CLK1,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_CLK1(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_CLK1);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK1] --> 0x%08x\n",
                        REG_EPHY_CLK1,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_CLK1_unkown(U8 data)
{
    GH_EPHY_CLK1_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK1;
    d.bitc.unkown = data;
    *(volatile U16 *)REG_EPHY_CLK1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK1_unkown] <-- 0x%08x\n",
                        REG_EPHY_CLK1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CLK1_unkown(void)
{
    GH_EPHY_CLK1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK1_unkown] --> 0x%08x\n",
                        REG_EPHY_CLK1,value);
    #endif
    return tmp_value.bitc.unkown;
}
GH_INLINE void GH_EPHY_set_CLK1_clko_200_gat(U8 data)
{
    GH_EPHY_CLK1_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK1;
    d.bitc.clko_200_gat = data;
    *(volatile U16 *)REG_EPHY_CLK1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK1_clko_200_gat] <-- 0x%08x\n",
                        REG_EPHY_CLK1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CLK1_clko_200_gat(void)
{
    GH_EPHY_CLK1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK1_clko_200_gat] --> 0x%08x\n",
                        REG_EPHY_CLK1,value);
    #endif
    return tmp_value.bitc.clko_200_gat;
}
GH_INLINE void GH_EPHY_set_CLK1_clko_200_inv(U8 data)
{
    GH_EPHY_CLK1_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK1;
    d.bitc.clko_200_inv = data;
    *(volatile U16 *)REG_EPHY_CLK1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK1_clko_200_inv] <-- 0x%08x\n",
                        REG_EPHY_CLK1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CLK1_clko_200_inv(void)
{
    GH_EPHY_CLK1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK1_clko_200_inv] --> 0x%08x\n",
                        REG_EPHY_CLK1,value);
    #endif
    return tmp_value.bitc.clko_200_inv;
}
GH_INLINE void GH_EPHY_set_CLK1_lut_new(U8 data)
{
    GH_EPHY_CLK1_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK1;
    d.bitc.lut_new = data;
    *(volatile U16 *)REG_EPHY_CLK1 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK1_lut_new] <-- 0x%08x\n",
                        REG_EPHY_CLK1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CLK1_lut_new(void)
{
    GH_EPHY_CLK1_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK1);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK1_lut_new] --> 0x%08x\n",
                        REG_EPHY_CLK1,value);
    #endif
    return tmp_value.bitc.lut_new;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_GCR_TX (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX(U16 data);
/*! \brief Reads the register 'EPHY_GCR_TX'. */
U16  GH_EPHY_get_GCR_TX(void);
/*! \brief Writes the bit group 'ioffset_sel' of register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX_ioffset_sel(U8 data);
/*! \brief Reads the bit group 'ioffset_sel' of register 'EPHY_GCR_TX'. */
U8   GH_EPHY_get_GCR_TX_ioffset_sel(void);
/*! \brief Writes the bit group 'ld_vcmo' of register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX_ld_vcmo(U8 data);
/*! \brief Reads the bit group 'ld_vcmo' of register 'EPHY_GCR_TX'. */
U8   GH_EPHY_get_GCR_TX_ld_vcmo(void);
/*! \brief Writes the bit group 'ph_delay' of register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX_ph_delay(U8 data);
/*! \brief Reads the bit group 'ph_delay' of register 'EPHY_GCR_TX'. */
U8   GH_EPHY_get_GCR_TX_ph_delay(void);
/*! \brief Writes the bit group 'phase_100t' of register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX_phase_100t(U8 data);
/*! \brief Reads the bit group 'phase_100t' of register 'EPHY_GCR_TX'. */
U8   GH_EPHY_get_GCR_TX_phase_100t(void);
/*! \brief Writes the bit group 'ld_iq_sel' of register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX_ld_iq_sel(U8 data);
/*! \brief Reads the bit group 'ld_iq_sel' of register 'EPHY_GCR_TX'. */
U8   GH_EPHY_get_GCR_TX_ld_iq_sel(void);
/*! \brief Writes the bit group 'ld_iq_ibias' of register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX_ld_iq_ibias(U8 data);
/*! \brief Reads the bit group 'ld_iq_ibias' of register 'EPHY_GCR_TX'. */
U8   GH_EPHY_get_GCR_TX_ld_iq_ibias(void);
/*! \brief Writes the bit group 'en_tx_ioffset' of register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX_en_tx_ioffset(U8 data);
/*! \brief Reads the bit group 'en_tx_ioffset' of register 'EPHY_GCR_TX'. */
U8   GH_EPHY_get_GCR_TX_en_tx_ioffset(void);
/*! \brief Writes the bit group 'save2x_tx' of register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX_save2x_tx(U8 data);
/*! \brief Reads the bit group 'save2x_tx' of register 'EPHY_GCR_TX'. */
U8   GH_EPHY_get_GCR_TX_save2x_tx(void);
/*! \brief Writes the bit group 'wssel_inv' of register 'EPHY_GCR_TX'. */
void GH_EPHY_set_GCR_TX_wssel_inv(U8 data);
/*! \brief Reads the bit group 'wssel_inv' of register 'EPHY_GCR_TX'. */
U8   GH_EPHY_get_GCR_TX_wssel_inv(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_GCR_TX(U16 data)
{
    *(volatile U16 *)REG_EPHY_GCR_TX = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_GCR_TX(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ioffset_sel(U8 data)
{
    GH_EPHY_GCR_TX_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX;
    d.bitc.ioffset_sel = data;
    *(volatile U16 *)REG_EPHY_GCR_TX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX_ioffset_sel] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ioffset_sel(void)
{
    GH_EPHY_GCR_TX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX_ioffset_sel] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return tmp_value.bitc.ioffset_sel;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ld_vcmo(U8 data)
{
    GH_EPHY_GCR_TX_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX;
    d.bitc.ld_vcmo = data;
    *(volatile U16 *)REG_EPHY_GCR_TX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX_ld_vcmo] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ld_vcmo(void)
{
    GH_EPHY_GCR_TX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX_ld_vcmo] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return tmp_value.bitc.ld_vcmo;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ph_delay(U8 data)
{
    GH_EPHY_GCR_TX_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX;
    d.bitc.ph_delay = data;
    *(volatile U16 *)REG_EPHY_GCR_TX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX_ph_delay] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ph_delay(void)
{
    GH_EPHY_GCR_TX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX_ph_delay] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return tmp_value.bitc.ph_delay;
}
GH_INLINE void GH_EPHY_set_GCR_TX_phase_100t(U8 data)
{
    GH_EPHY_GCR_TX_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX;
    d.bitc.phase_100t = data;
    *(volatile U16 *)REG_EPHY_GCR_TX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX_phase_100t] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_phase_100t(void)
{
    GH_EPHY_GCR_TX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX_phase_100t] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return tmp_value.bitc.phase_100t;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ld_iq_sel(U8 data)
{
    GH_EPHY_GCR_TX_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX;
    d.bitc.ld_iq_sel = data;
    *(volatile U16 *)REG_EPHY_GCR_TX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX_ld_iq_sel] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ld_iq_sel(void)
{
    GH_EPHY_GCR_TX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX_ld_iq_sel] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return tmp_value.bitc.ld_iq_sel;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ld_iq_ibias(U8 data)
{
    GH_EPHY_GCR_TX_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX;
    d.bitc.ld_iq_ibias = data;
    *(volatile U16 *)REG_EPHY_GCR_TX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX_ld_iq_ibias] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ld_iq_ibias(void)
{
    GH_EPHY_GCR_TX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX_ld_iq_ibias] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return tmp_value.bitc.ld_iq_ibias;
}
GH_INLINE void GH_EPHY_set_GCR_TX_en_tx_ioffset(U8 data)
{
    GH_EPHY_GCR_TX_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX;
    d.bitc.en_tx_ioffset = data;
    *(volatile U16 *)REG_EPHY_GCR_TX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX_en_tx_ioffset] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_en_tx_ioffset(void)
{
    GH_EPHY_GCR_TX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX_en_tx_ioffset] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return tmp_value.bitc.en_tx_ioffset;
}
GH_INLINE void GH_EPHY_set_GCR_TX_save2x_tx(U8 data)
{
    GH_EPHY_GCR_TX_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX;
    d.bitc.save2x_tx = data;
    *(volatile U16 *)REG_EPHY_GCR_TX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX_save2x_tx] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_save2x_tx(void)
{
    GH_EPHY_GCR_TX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX_save2x_tx] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return tmp_value.bitc.save2x_tx;
}
GH_INLINE void GH_EPHY_set_GCR_TX_wssel_inv(U8 data)
{
    GH_EPHY_GCR_TX_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX;
    d.bitc.wssel_inv = data;
    *(volatile U16 *)REG_EPHY_GCR_TX = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_GCR_TX_wssel_inv] <-- 0x%08x\n",
                        REG_EPHY_GCR_TX,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_wssel_inv(void)
{
    GH_EPHY_GCR_TX_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_GCR_TX_wssel_inv] --> 0x%08x\n",
                        REG_EPHY_GCR_TX,value);
    #endif
    return tmp_value.bitc.wssel_inv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_POWER (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_POWER'. */
void GH_EPHY_set_POWER(U16 data);
/*! \brief Reads the register 'EPHY_POWER'. */
U16  GH_EPHY_get_POWER(void);
/*! \brief Writes the bit group 'pd_tx_ld' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_tx_ld(U8 data);
/*! \brief Reads the bit group 'pd_tx_ld' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_tx_ld(void);
/*! \brief Writes the bit group 'pd_tx_idac' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_tx_idac(U8 data);
/*! \brief Reads the bit group 'pd_tx_idac' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_tx_idac(void);
/*! \brief Writes the bit group 'pd_dacramp_new' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_dacramp_new(U8 data);
/*! \brief Reads the bit group 'pd_dacramp_new' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_dacramp_new(void);
/*! \brief Writes the bit group 'pd_dacnew_testen' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_dacnew_testen(U8 data);
/*! \brief Reads the bit group 'pd_dacnew_testen' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_dacnew_testen(void);
/*! \brief Writes the bit group 'pd_tx_ld_10t' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_tx_ld_10t(U8 data);
/*! \brief Reads the bit group 'pd_tx_ld_10t' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_tx_ld_10t(void);
/*! \brief Writes the bit group 'pd_tx_ld_100t' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_tx_ld_100t(U8 data);
/*! \brief Reads the bit group 'pd_tx_ld_100t' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_tx_ld_100t(void);
/*! \brief Writes the bit group 'pd_tx_ld_lp' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_tx_ld_lp(U8 data);
/*! \brief Reads the bit group 'pd_tx_ld_lp' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_tx_ld_lp(void);
/*! \brief Writes the bit group 'pd_tx_idac_10t' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_tx_idac_10t(U8 data);
/*! \brief Reads the bit group 'pd_tx_idac_10t' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_tx_idac_10t(void);
/*! \brief Writes the bit group 'pd_tx_idac_100t' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_tx_idac_100t(U8 data);
/*! \brief Reads the bit group 'pd_tx_idac_100t' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_tx_idac_100t(void);
/*! \brief Writes the bit group 'pd_tx_idac_lp' of register 'EPHY_POWER'. */
void GH_EPHY_set_POWER_pd_tx_idac_lp(U8 data);
/*! \brief Reads the bit group 'pd_tx_idac_lp' of register 'EPHY_POWER'. */
U8   GH_EPHY_get_POWER_pd_tx_idac_lp(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_POWER(U16 data)
{
    *(volatile U16 *)REG_EPHY_POWER = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER] <-- 0x%08x\n",
                        REG_EPHY_POWER,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_POWER(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_ld(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_tx_ld = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_tx_ld] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_ld(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_tx_ld] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_tx_ld;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_idac(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_tx_idac = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_tx_idac] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_idac(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_tx_idac] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_tx_idac;
}
GH_INLINE void GH_EPHY_set_POWER_pd_dacramp_new(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_dacramp_new = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_dacramp_new] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_dacramp_new(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_dacramp_new] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_dacramp_new;
}
GH_INLINE void GH_EPHY_set_POWER_pd_dacnew_testen(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_dacnew_testen = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_dacnew_testen] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_dacnew_testen(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_dacnew_testen] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_dacnew_testen;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_ld_10t(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_tx_ld_10t = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_tx_ld_10t] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_ld_10t(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_tx_ld_10t] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_tx_ld_10t;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_ld_100t(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_tx_ld_100t = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_tx_ld_100t] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_ld_100t(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_tx_ld_100t] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_tx_ld_100t;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_ld_lp(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_tx_ld_lp = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_tx_ld_lp] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_ld_lp(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_tx_ld_lp] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_tx_ld_lp;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_idac_10t(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_tx_idac_10t = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_tx_idac_10t] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_idac_10t(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_tx_idac_10t] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_tx_idac_10t;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_idac_100t(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_tx_idac_100t = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_tx_idac_100t] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_idac_100t(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_tx_idac_100t] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_tx_idac_100t;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_idac_lp(U8 data)
{
    GH_EPHY_POWER_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER;
    d.bitc.pd_tx_idac_lp = data;
    *(volatile U16 *)REG_EPHY_POWER = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_POWER_pd_tx_idac_lp] <-- 0x%08x\n",
                        REG_EPHY_POWER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_idac_lp(void)
{
    GH_EPHY_POWER_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_POWER_pd_tx_idac_lp] --> 0x%08x\n",
                        REG_EPHY_POWER,value);
    #endif
    return tmp_value.bitc.pd_tx_idac_lp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_MDIIO (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_MDIIO'. */
void GH_EPHY_set_MDIIO(U16 data);
/*! \brief Reads the register 'EPHY_MDIIO'. */
U16  GH_EPHY_get_MDIIO(void);
/*! \brief Writes the bit group 'mdio_idle_error_cnt_clear' of register 'EPHY_MDIIO'. */
void GH_EPHY_set_MDIIO_mdio_idle_error_cnt_clear(U8 data);
/*! \brief Reads the bit group 'mdio_idle_error_cnt_clear' of register 'EPHY_MDIIO'. */
U8   GH_EPHY_get_MDIIO_mdio_idle_error_cnt_clear(void);
/*! \brief Writes the bit group 'pd_vbuf' of register 'EPHY_MDIIO'. */
void GH_EPHY_set_MDIIO_pd_vbuf(U8 data);
/*! \brief Reads the bit group 'pd_vbuf' of register 'EPHY_MDIIO'. */
U8   GH_EPHY_get_MDIIO_pd_vbuf(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_MDIIO(U16 data)
{
    *(volatile U16 *)REG_EPHY_MDIIO = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MDIIO] <-- 0x%08x\n",
                        REG_EPHY_MDIIO,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_MDIIO(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_MDIIO);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MDIIO] --> 0x%08x\n",
                        REG_EPHY_MDIIO,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_MDIIO_mdio_idle_error_cnt_clear(U8 data)
{
    GH_EPHY_MDIIO_S d;
    d.all = *(volatile U16 *)REG_EPHY_MDIIO;
    d.bitc.mdio_idle_error_cnt_clear = data;
    *(volatile U16 *)REG_EPHY_MDIIO = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MDIIO_mdio_idle_error_cnt_clear] <-- 0x%08x\n",
                        REG_EPHY_MDIIO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_MDIIO_mdio_idle_error_cnt_clear(void)
{
    GH_EPHY_MDIIO_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MDIIO);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MDIIO_mdio_idle_error_cnt_clear] --> 0x%08x\n",
                        REG_EPHY_MDIIO,value);
    #endif
    return tmp_value.bitc.mdio_idle_error_cnt_clear;
}
GH_INLINE void GH_EPHY_set_MDIIO_pd_vbuf(U8 data)
{
    GH_EPHY_MDIIO_S d;
    d.all = *(volatile U16 *)REG_EPHY_MDIIO;
    d.bitc.pd_vbuf = data;
    *(volatile U16 *)REG_EPHY_MDIIO = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_MDIIO_pd_vbuf] <-- 0x%08x\n",
                        REG_EPHY_MDIIO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_MDIIO_pd_vbuf(void)
{
    GH_EPHY_MDIIO_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MDIIO);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_MDIIO_pd_vbuf] --> 0x%08x\n",
                        REG_EPHY_MDIIO,value);
    #endif
    return tmp_value.bitc.pd_vbuf;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_CLK0 (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_CLK0'. */
void GH_EPHY_set_CLK0(U16 data);
/*! \brief Reads the register 'EPHY_CLK0'. */
U16  GH_EPHY_get_CLK0(void);
/*! \brief Writes the bit group 'lpi_tx_tq_timer_msb' of register 'EPHY_CLK0'. */
void GH_EPHY_set_CLK0_lpi_tx_tq_timer_msb(U8 data);
/*! \brief Reads the bit group 'lpi_tx_tq_timer_msb' of register 'EPHY_CLK0'. */
U8   GH_EPHY_get_CLK0_lpi_tx_tq_timer_msb(void);
/*! \brief Writes the bit group 'clko_125_inv' of register 'EPHY_CLK0'. */
void GH_EPHY_set_CLK0_clko_125_inv(U8 data);
/*! \brief Reads the bit group 'clko_125_inv' of register 'EPHY_CLK0'. */
U8   GH_EPHY_get_CLK0_clko_125_inv(void);
/*! \brief Writes the bit group 'clko_100_gat' of register 'EPHY_CLK0'. */
void GH_EPHY_set_CLK0_clko_100_gat(U8 data);
/*! \brief Reads the bit group 'clko_100_gat' of register 'EPHY_CLK0'. */
U8   GH_EPHY_get_CLK0_clko_100_gat(void);
/*! \brief Writes the bit group 'clko_100_inv' of register 'EPHY_CLK0'. */
void GH_EPHY_set_CLK0_clko_100_inv(U8 data);
/*! \brief Reads the bit group 'clko_100_inv' of register 'EPHY_CLK0'. */
U8   GH_EPHY_get_CLK0_clko_100_inv(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_CLK0(U16 data)
{
    *(volatile U16 *)REG_EPHY_CLK0 = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK0] <-- 0x%08x\n",
                        REG_EPHY_CLK0,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_CLK0(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_CLK0);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK0] --> 0x%08x\n",
                        REG_EPHY_CLK0,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_CLK0_lpi_tx_tq_timer_msb(U8 data)
{
    GH_EPHY_CLK0_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK0;
    d.bitc.lpi_tx_tq_timer_msb = data;
    *(volatile U16 *)REG_EPHY_CLK0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK0_lpi_tx_tq_timer_msb] <-- 0x%08x\n",
                        REG_EPHY_CLK0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CLK0_lpi_tx_tq_timer_msb(void)
{
    GH_EPHY_CLK0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK0_lpi_tx_tq_timer_msb] --> 0x%08x\n",
                        REG_EPHY_CLK0,value);
    #endif
    return tmp_value.bitc.lpi_tx_tq_timer_msb;
}
GH_INLINE void GH_EPHY_set_CLK0_clko_125_inv(U8 data)
{
    GH_EPHY_CLK0_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK0;
    d.bitc.clko_125_inv = data;
    *(volatile U16 *)REG_EPHY_CLK0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK0_clko_125_inv] <-- 0x%08x\n",
                        REG_EPHY_CLK0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CLK0_clko_125_inv(void)
{
    GH_EPHY_CLK0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK0_clko_125_inv] --> 0x%08x\n",
                        REG_EPHY_CLK0,value);
    #endif
    return tmp_value.bitc.clko_125_inv;
}
GH_INLINE void GH_EPHY_set_CLK0_clko_100_gat(U8 data)
{
    GH_EPHY_CLK0_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK0;
    d.bitc.clko_100_gat = data;
    *(volatile U16 *)REG_EPHY_CLK0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK0_clko_100_gat] <-- 0x%08x\n",
                        REG_EPHY_CLK0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CLK0_clko_100_gat(void)
{
    GH_EPHY_CLK0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK0_clko_100_gat] --> 0x%08x\n",
                        REG_EPHY_CLK0,value);
    #endif
    return tmp_value.bitc.clko_100_gat;
}
GH_INLINE void GH_EPHY_set_CLK0_clko_100_inv(U8 data)
{
    GH_EPHY_CLK0_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK0;
    d.bitc.clko_100_inv = data;
    *(volatile U16 *)REG_EPHY_CLK0 = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_CLK0_clko_100_inv] <-- 0x%08x\n",
                        REG_EPHY_CLK0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_CLK0_clko_100_inv(void)
{
    GH_EPHY_CLK0_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK0);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_CLK0_clko_100_inv] --> 0x%08x\n",
                        REG_EPHY_CLK0,value);
    #endif
    return tmp_value.bitc.clko_100_inv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_CTRL (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'EPHY_WAVE_CTRL'. */
void GH_EPHY_set_WAVE_CTRL(U16 data);
/*! \brief Reads the register 'EPHY_WAVE_CTRL'. */
U16  GH_EPHY_get_WAVE_CTRL(void);
/*! \brief Writes the bit group 'shadow' of register 'EPHY_WAVE_CTRL'. */
void GH_EPHY_set_WAVE_CTRL_shadow(U8 data);
/*! \brief Reads the bit group 'shadow' of register 'EPHY_WAVE_CTRL'. */
U8   GH_EPHY_get_WAVE_CTRL_shadow(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_EPHY_set_WAVE_CTRL(U16 data)
{
    *(volatile U16 *)REG_EPHY_WAVE_CTRL = data;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_CTRL] <-- 0x%08x\n",
                        REG_EPHY_WAVE_CTRL,data,data);
    #endif
}
GH_INLINE U16  GH_EPHY_get_WAVE_CTRL(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_CTRL);

    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_CTRL] --> 0x%08x\n",
                        REG_EPHY_WAVE_CTRL,value);
    #endif
    return value;
}
GH_INLINE void GH_EPHY_set_WAVE_CTRL_shadow(U8 data)
{
    GH_EPHY_WAVE_CTRL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_CTRL;
    d.bitc.shadow = data;
    *(volatile U16 *)REG_EPHY_WAVE_CTRL = d.all;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_EPHY_set_WAVE_CTRL_shadow] <-- 0x%08x\n",
                        REG_EPHY_WAVE_CTRL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_EPHY_get_WAVE_CTRL_shadow(void)
{
    GH_EPHY_WAVE_CTRL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_CTRL);

    tmp_value.all = value;
    #if GH_EPHY_ENABLE_DEBUG_PRINT
    GH_EPHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_EPHY_get_WAVE_CTRL_shadow] --> 0x%08x\n",
                        REG_EPHY_WAVE_CTRL,value);
    #endif
    return tmp_value.bitc.shadow;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_EPHY_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_EPHY_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

