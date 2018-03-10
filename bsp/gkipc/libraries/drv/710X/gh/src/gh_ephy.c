/******************************************************************************
**
** \file      gh_ephy.c
**
** \brief     Ethernet PHY controller.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef SRC_INLINE
#include "gh_ephy.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_EPHY_MII_RMII_REAL                              FIO_ADDRESS(EPHY,0x60020E00) /* read/write */
#define REG_EPHY_CONTROL_REAL                               FIO_ADDRESS(EPHY,0x60022000) /* read/write */
#define REG_EPHY_STATUS_REAL                                FIO_ADDRESS(EPHY,0x60022004) /* read */
#define REG_EPHY_ID1_REAL                                   FIO_ADDRESS(EPHY,0x60022008) /* read */
#define REG_EPHY_ID2_REAL                                   FIO_ADDRESS(EPHY,0x6002200C) /* read */
#define REG_EPHY_ANAR_REAL                                  FIO_ADDRESS(EPHY,0x60022010) /* read/write */
#define REG_EPHY_ANLPAR_REAL                                FIO_ADDRESS(EPHY,0x60022014) /* read */
#define REG_EPHY_ANER_REAL                                  FIO_ADDRESS(EPHY,0x60022018) /* read/write */
#define REG_EPHY_ANNPAR_REAL                                FIO_ADDRESS(EPHY,0x6002201C) /* read/write */
#define REG_EPHY_TRANSMIT_PATTERN_REAL                      FIO_ADDRESS(EPHY,0x600221AC) /* read/write */
#define REG_EPHY_ANLPNP_REAL                                FIO_ADDRESS(EPHY,0x60022020) /* read */
#define REG_EPHY_MS_CONTROL_REAL                            FIO_ADDRESS(EPHY,0x60022024) /* read/write */
#define REG_EPHY_MS_STATUS_REAL                             FIO_ADDRESS(EPHY,0x60022028) /* read */
#define REG_EPHY_PSE_CONTROL_REAL                           FIO_ADDRESS(EPHY,0x6002202C) /* read/write */
#define REG_EPHY_PSE_STATUS_REAL                            FIO_ADDRESS(EPHY,0x60022030) /* read */
#define REG_EPHY_MMD_CONTROL_REAL                           FIO_ADDRESS(EPHY,0x60022034) /* read/write */
#define REG_EPHY_MMD_CONTROL_ADDR_REAL                      FIO_ADDRESS(EPHY,0x60022038) /* read/write */
#define REG_EPHY_AN_R_15_REAL                               FIO_ADDRESS(EPHY,0x6002203C) /* read */
#define REG_EPHY_WAVE_SHAPING_34_REAL                       FIO_ADDRESS(EPHY,0x60022040) /* read/write */
#define REG_EPHY_WAVE_SHAPING_56_REAL                       FIO_ADDRESS(EPHY,0x60022044) /* read/write */
#define REG_EPHY_WAVE_SHAPING_78_REAL                       FIO_ADDRESS(EPHY,0x60022048) /* read/write */
#define REG_EPHY_WAVE_SHAPING_9A_REAL                       FIO_ADDRESS(EPHY,0x6002204C) /* read/write */
#define REG_EPHY_WAVE_SHAPING_BC_REAL                       FIO_ADDRESS(EPHY,0x60022050) /* read/write */
#define REG_EPHY_WAVE_SHAPING_DE_REAL                       FIO_ADDRESS(EPHY,0x60022054) /* read/write */
#define REG_EPHY_SPEED_REAL                                 FIO_ADDRESS(EPHY,0x60022058) /* read/write */
#define REG_EPHY_LTP_REAL                                   FIO_ADDRESS(EPHY,0x6002205C) /* read/write */
#define REG_EPHY_MCU_REAL                                   FIO_ADDRESS(EPHY,0x60022060) /* read/write */
#define REG_EPHY_CODE_RAM_REAL                              FIO_ADDRESS(EPHY,0x60022064) /* read/write */
#define REG_EPHY_CODE_RAM_W_REAL                            FIO_ADDRESS(EPHY,0x60022068) /* read/write */
#define REG_EPHY_100M_LINK_REAL                             FIO_ADDRESS(EPHY,0x60022088) /* read/write */
#define REG_EPHY_DEBUG_REAL                                 FIO_ADDRESS(EPHY,0x600220C8) /* read/write */
#define REG_EPHY_DEBUG_MODE_REAL                            FIO_ADDRESS(EPHY,0x600220E0) /* read/write */
#define REG_EPHY_RST_EN_REAL                                FIO_ADDRESS(EPHY,0x600220E4) /* read/write */
#define REG_EPHY_SNR_K_REAL                                 FIO_ADDRESS(EPHY,0x60022284) /* read/write */
#define REG_EPHY_DET_MAX_REAL                               FIO_ADDRESS(EPHY,0x6002229C) /* read/write */
#define REG_EPHY_DET_MIN_REAL                               FIO_ADDRESS(EPHY,0x600222A0) /* read/write */
#define REG_EPHY_SNR_LEN_REAL                               FIO_ADDRESS(EPHY,0x600222EC) /* read/write */
#define REG_EPHY_LPF_REAL                                   FIO_ADDRESS(EPHY,0x60022340) /* read/write */
#define REG_EPHY_ADC_GAIN_PGA_REAL                          FIO_ADDRESS(EPHY,0x6002236C) /* read/write */
#define REG_EPHY_ADC_GSHIFT_REAL                            FIO_ADDRESS(EPHY,0x60022368) /* read/write */
#define REG_EPHY_ADC_REAL                                   FIO_ADDRESS(EPHY,0x6002236C) /* read/write */
#define REG_EPHY_PLL_ADC_CTRL3_REAL                         FIO_ADDRESS(EPHY,0x60022370) /* read/write */
#define REG_EPHY_RX_LPF_REAL                                FIO_ADDRESS(EPHY,0x60022374) /* read/write */
#define REG_EPHY_PLL_ADC_CTRL0_REAL                         FIO_ADDRESS(EPHY,0x60022394) /* read/write */
#define REG_EPHY_PLL_ADC_CTRL1_REAL                         FIO_ADDRESS(EPHY,0x60022398) /* read/write */
#define REG_EPHY_PLL_ADC_CTRL2_REAL                         FIO_ADDRESS(EPHY,0x600223A8) /* read/write */
#define REG_EPHY_TEST_TX_REAL                               FIO_ADDRESS(EPHY,0x600223B0) /* read/write */
#define REG_EPHY_PWR_REAL                                   FIO_ADDRESS(EPHY,0x600223BC) /* read/write */
#define REG_EPHY_ADC_DC_REAL                                FIO_ADDRESS(EPHY,0x600223D4) /* read/write */
#define REG_EPHY_ADCPL_REAL                                 FIO_ADDRESS(EPHY,0x600223E8) /* read/write */
#define REG_EPHY_LDO_REAL                                   FIO_ADDRESS(EPHY,0x600223F8) /* read/write */
#define REG_EPHY_CLK_GATE_REAL                              FIO_ADDRESS(EPHY,0x60022450) /* read */
#define REG_EPHY_CLK1_REAL                                  FIO_ADDRESS(EPHY,0x60022460) /* read/write */
#define REG_EPHY_GCR_TX_REAL                                FIO_ADDRESS(EPHY,0x60022470) /* read/write */
#define REG_EPHY_POWER_REAL                                 FIO_ADDRESS(EPHY,0x60022474) /* read/write */
#define REG_EPHY_MDIIO_REAL                                 FIO_ADDRESS(EPHY,0x60022540) /* read/write */
#define REG_EPHY_CLK0_REAL                                  FIO_ADDRESS(EPHY,0x60022588) /* read/write */
#define REG_EPHY_WAVE_CTRL_REAL                             FIO_ADDRESS(EPHY,0x600225D0) /* read/write */

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
} GH_EPHY_MII_RMII_REAL_S;

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
} GH_EPHY_CONTROL_REAL_S;

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
} GH_EPHY_STATUS_REAL_S;

typedef union { /* EPHY_ANAR */
    U16 all;
    struct {
        U16 selector                    : 5;
        U16 tech_ability                : 8;
        U16 rf                          : 1;
        U16                             : 1;
        U16 np                          : 1;
    } bitc;
} GH_EPHY_ANAR_REAL_S;

typedef union { /* EPHY_ANLPAR */
    U16 all;
    struct {
        U16 selector                    : 5;
        U16 tech_ability                : 8;
        U16 rf                          : 1;
        U16 ack                         : 1;
        U16 np                          : 1;
    } bitc;
} GH_EPHY_ANLPAR_REAL_S;

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
} GH_EPHY_ANER_REAL_S;

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
} GH_EPHY_ANNPAR_REAL_S;

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
} GH_EPHY_ANLPNP_REAL_S;

typedef union { /* EPHY_MMD_CONTROL */
    U16 all;
    struct {
        U16 devad                       : 5;
        U16                             : 9;
        U16 func                        : 2;
    } bitc;
} GH_EPHY_MMD_CONTROL_REAL_S;

typedef union { /* EPHY_AN_R_15 */
    U16 all;
    struct {
        U16                             : 12;
        U16 an_register_15              : 2;
        U16                             : 2;
    } bitc;
} GH_EPHY_AN_R_15_REAL_S;

typedef union { /* EPHY_WAVE_SHAPING_34 */
    U16 all;
    struct {
        U16 ltp_3                       : 8;
        U16 ltp_4                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_34_REAL_S;

typedef union { /* EPHY_WAVE_SHAPING_56 */
    U16 all;
    struct {
        U16 ltp_5                       : 8;
        U16 ltp_6                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_56_REAL_S;

typedef union { /* EPHY_WAVE_SHAPING_78 */
    U16 all;
    struct {
        U16 ltp_7                       : 8;
        U16 ltp_8                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_78_REAL_S;

typedef union { /* EPHY_WAVE_SHAPING_9A */
    U16 all;
    struct {
        U16 ltp_9                       : 8;
        U16 ltp_a                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_9A_REAL_S;

typedef union { /* EPHY_WAVE_SHAPING_BC */
    U16 all;
    struct {
        U16 ltp_b                       : 8;
        U16 ltp_c                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_BC_REAL_S;

typedef union { /* EPHY_WAVE_SHAPING_DE */
    U16 all;
    struct {
        U16 ltp_d                       : 8;
        U16 ltp_e                       : 8;
    } bitc;
} GH_EPHY_WAVE_SHAPING_DE_REAL_S;

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
} GH_EPHY_SPEED_REAL_S;

typedef union { /* EPHY_LTP */
    U16 all;
    struct {
        U16 width                       : 4;
        U16 tx_gm_rctrl                 : 4;
        U16                             : 8;
    } bitc;
} GH_EPHY_LTP_REAL_S;

typedef union { /* EPHY_MCU */
    U16 all;
    struct {
        U16 en                          : 1;
        U16 mcu_rdy                     : 1;
        U16                             : 14;
    } bitc;
} GH_EPHY_MCU_REAL_S;

typedef union { /* EPHY_CODE_RAM */
    U16 all;
    struct {
        U16 start_addr                  : 16;
    } bitc;
} GH_EPHY_CODE_RAM_REAL_S;

typedef union { /* EPHY_CODE_RAM_W */
    U16 all;
    struct {
        U16 start_addr                  : 16;
    } bitc;
} GH_EPHY_CODE_RAM_W_REAL_S;

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
} GH_EPHY_100M_LINK_REAL_S;

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
} GH_EPHY_DEBUG_REAL_S;

typedef union { /* EPHY_DEBUG_MODE */
    U16 all;
    struct {
        U16 signal                      : 8;
        U16 module                      : 8;
    } bitc;
} GH_EPHY_DEBUG_MODE_REAL_S;

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
} GH_EPHY_RST_EN_REAL_S;

typedef union { /* EPHY_SNR_K */
    U16 all;
    struct {
        U16 slice_up                    : 8;
        U16 snrchk_k1                   : 2;
        U16 snrchk_k2                   : 2;
        U16 snrchk_k3                   : 2;
        U16 gcr_ccpl_master_coarse_clkcc: 2;
    } bitc;
} GH_EPHY_SNR_K_REAL_S;

typedef union { /* EPHY_DET_MAX */
    U16 all;
    struct {
        U16 thrh_max_vga_coarse         : 8;
        U16 thrh_max_sig_det            : 8;
    } bitc;
} GH_EPHY_DET_MAX_REAL_S;

typedef union { /* EPHY_DET_MIN */
    U16 all;
    struct {
        U16 thrh_max_vga_fine           : 8;
        U16 thrh_min_sig_det            : 8;
    } bitc;
} GH_EPHY_DET_MIN_REAL_S;

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
} GH_EPHY_SNR_LEN_REAL_S;

typedef union { /* EPHY_LPF */
    U16 all;
    struct {
        U16 lpf_out_h                   : 10;
        U16 rxlpf_bwsel_10t             : 2;
        U16 rxlpf_bwsel_100t            : 2;
        U16 cable_length                : 2;
    } bitc;
} GH_EPHY_LPF_REAL_S;

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
} GH_EPHY_ADC_GAIN_PGA_REAL_S;

typedef union { /* EPHY_ADC_GSHIFT */
    U16 all;
    struct {
        U16 adc_gshift                  : 2;
        U16 gain                        : 6;
        U16                             : 8;
    } bitc;
} GH_EPHY_ADC_GSHIFT_REAL_S;

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
} GH_EPHY_ADC_REAL_S;

typedef union { /* EPHY_PLL_ADC_CTRL3 */
    U16 all;
    struct {
        U16                             : 8;
        U16 rxlpf_pd                    : 1;
        U16 tx_b_test                   : 6;
        U16                             : 1;
    } bitc;
} GH_EPHY_PLL_ADC_CTRL3_REAL_S;

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
} GH_EPHY_RX_LPF_REAL_S;

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
} GH_EPHY_PLL_ADC_CTRL0_REAL_S;

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
} GH_EPHY_PLL_ADC_CTRL1_REAL_S;

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
} GH_EPHY_PLL_ADC_CTRL2_REAL_S;

typedef union { /* EPHY_PWR */
    U16 all;
    struct {
        U16 pwr_k_in_lp                 : 3;
        U16 dtpwr_enable_lp             : 1;
        U16 gcr_adcpl_div_lp            : 3;
        U16 dummy                       : 9;
    } bitc;
} GH_EPHY_PWR_REAL_S;

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
} GH_EPHY_ADC_DC_REAL_S;

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
} GH_EPHY_ADCPL_REAL_S;

typedef union { /* EPHY_LDO */
    U16 all;
    struct {
        U16 dummy                       : 16;
    } bitc;
} GH_EPHY_LDO_REAL_S;

typedef union { /* EPHY_CLK_GATE */
    U16 all;
    struct {
        U16 eee_capability              : 16;
    } bitc;
} GH_EPHY_CLK_GATE_REAL_S;

typedef union { /* EPHY_CLK1 */
    U16 all;
    struct {
        U16 unkown                      : 4;
        U16 clko_200_gat                : 1;
        U16 clko_200_inv                : 1;
        U16 lut_new                     : 1;
        U16                             : 9;
    } bitc;
} GH_EPHY_CLK1_REAL_S;

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
} GH_EPHY_GCR_TX_REAL_S;

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
} GH_EPHY_POWER_REAL_S;

typedef union { /* EPHY_MDIIO */
    U16 all;
    struct {
        U16                             : 4;
        U16 mdio_idle_error_cnt_clear   : 1;
        U16                             : 7;
        U16 pd_vbuf                     : 1;
        U16                             : 3;
    } bitc;
} GH_EPHY_MDIIO_REAL_S;

typedef union { /* EPHY_CLK0 */
    U16 all;
    struct {
        U16 lpi_tx_tq_timer_msb         : 6;
        U16                             : 7;
        U16 clko_125_inv                : 1;
        U16 clko_100_gat                : 1;
        U16 clko_100_inv                : 1;
    } bitc;
} GH_EPHY_CLK0_REAL_S;

typedef union { /* EPHY_WAVE_CTRL */
    U16 all;
    struct {
        U16 shadow                      : 3;
        U16                             : 13;
    } bitc;
} GH_EPHY_WAVE_CTRL_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register EPHY_MII_RMII (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_MII_RMII(U32 data)
{
    GH_EPHY_MII_RMII_REAL_S real;
    GH_EPHY_MII_RMII_S dummy;
    dummy.all = data ;
    real.bitc.usb_tm1 = dummy.bitc.usb_tm1;
    real.bitc.rmii = dummy.bitc.rmii;
    *(volatile U32 *)REG_EPHY_MII_RMII_REAL = real.all;
}
GH_INLINE U32  GH_EPHY_get_MII_RMII(void)
{
    GH_EPHY_MII_RMII_REAL_S real;
    GH_EPHY_MII_RMII_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_EPHY_MII_RMII_REAL);

    dummy.bitc.usb_tm1 = real.bitc.usb_tm1;
    dummy.bitc.rmii = real.bitc.rmii;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_MII_RMII_USB_TM1(U8 data)
{
    GH_EPHY_MII_RMII_REAL_S d;
    d.all = *(volatile U32 *)REG_EPHY_MII_RMII_REAL;
    d.bitc.usb_tm1 = data;
    *(volatile U32 *)REG_EPHY_MII_RMII_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_MII_RMII_USB_TM1(void)
{
    GH_EPHY_MII_RMII_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EPHY_MII_RMII_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.usb_tm1;
}
GH_INLINE void GH_EPHY_set_MII_RMII_rmii(U8 data)
{
    GH_EPHY_MII_RMII_REAL_S d;
    d.all = *(volatile U32 *)REG_EPHY_MII_RMII_REAL;
    d.bitc.rmii = data;
    *(volatile U32 *)REG_EPHY_MII_RMII_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_MII_RMII_rmii(void)
{
    GH_EPHY_MII_RMII_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_EPHY_MII_RMII_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rmii;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_CONTROL (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_CONTROL(U16 data)
{
    GH_EPHY_CONTROL_REAL_S real;
    GH_EPHY_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.mii_ctl_unidirectional_enable = dummy.bitc.mii_ctl_unidirectional_enable;
    real.bitc.mii_ctl_speed_sel_msb = dummy.bitc.mii_ctl_speed_sel_msb;
    real.bitc.mii_ctl_col_test = dummy.bitc.mii_ctl_col_test;
    real.bitc.mii_ctl_duplex_mode = dummy.bitc.mii_ctl_duplex_mode;
    real.bitc.mii_ctl_restart_an = dummy.bitc.mii_ctl_restart_an;
    real.bitc.mii_ctl_isolate = dummy.bitc.mii_ctl_isolate;
    real.bitc.mii_ctl_power_down = dummy.bitc.mii_ctl_power_down;
    real.bitc.mii_ctl_an_en = dummy.bitc.mii_ctl_an_en;
    real.bitc.mii_ctl_speed_sel_lsb = dummy.bitc.mii_ctl_speed_sel_lsb;
    real.bitc.mii_ctl_loopback = dummy.bitc.mii_ctl_loopback;
    real.bitc.mii_ctl_reset = dummy.bitc.mii_ctl_reset;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_CONTROL(void)
{
    GH_EPHY_CONTROL_REAL_S real;
    GH_EPHY_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    dummy.bitc.mii_ctl_unidirectional_enable = real.bitc.mii_ctl_unidirectional_enable;
    dummy.bitc.mii_ctl_speed_sel_msb = real.bitc.mii_ctl_speed_sel_msb;
    dummy.bitc.mii_ctl_col_test = real.bitc.mii_ctl_col_test;
    dummy.bitc.mii_ctl_duplex_mode = real.bitc.mii_ctl_duplex_mode;
    dummy.bitc.mii_ctl_restart_an = real.bitc.mii_ctl_restart_an;
    dummy.bitc.mii_ctl_isolate = real.bitc.mii_ctl_isolate;
    dummy.bitc.mii_ctl_power_down = real.bitc.mii_ctl_power_down;
    dummy.bitc.mii_ctl_an_en = real.bitc.mii_ctl_an_en;
    dummy.bitc.mii_ctl_speed_sel_lsb = real.bitc.mii_ctl_speed_sel_lsb;
    dummy.bitc.mii_ctl_loopback = real.bitc.mii_ctl_loopback;
    dummy.bitc.mii_ctl_reset = real.bitc.mii_ctl_reset;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_unidirectional_enable(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_unidirectional_enable = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_unidirectional_enable(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_unidirectional_enable;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_speed_sel_msb(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_speed_sel_msb = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_speed_sel_msb(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_speed_sel_msb;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_col_test(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_col_test = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_col_test(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_col_test;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_duplex_mode(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_duplex_mode = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_duplex_mode(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_duplex_mode;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_restart_an(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_restart_an = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_restart_an(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_restart_an;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_isolate(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_isolate = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_isolate(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_isolate;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_power_down(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_power_down = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_power_down(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_power_down;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_an_en(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_an_en = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_an_en(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_an_en;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_speed_sel_lsb(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_speed_sel_lsb = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_speed_sel_lsb(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_speed_sel_lsb;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_loopback(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_loopback = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_loopback(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_loopback;
}
GH_INLINE void GH_EPHY_set_CONTROL_mii_ctl_reset(U8 data)
{
    GH_EPHY_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CONTROL_REAL;
    d.bitc.mii_ctl_reset = data;
    *(volatile U16 *)REG_EPHY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CONTROL_mii_ctl_reset(void)
{
    GH_EPHY_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_ctl_reset;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_STATUS (read)                                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_EPHY_get_STATUS(void)
{
    GH_EPHY_STATUS_REAL_S real;
    GH_EPHY_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    dummy.bitc.extended_capability = real.bitc.extended_capability;
    dummy.bitc.jabber_detect = real.bitc.jabber_detect;
    dummy.bitc.link_status = real.bitc.link_status;
    dummy.bitc.an_ability = real.bitc.an_ability;
    dummy.bitc.rf = real.bitc.rf;
    dummy.bitc.an_complete = real.bitc.an_complete;
    dummy.bitc.mf_preamble_suppression = real.bitc.mf_preamble_suppression;
    dummy.bitc.unidirectional_ability = real.bitc.unidirectional_ability;
    dummy.bitc.extended_status = real.bitc.extended_status;
    dummy.bitc.half_duplex_100t2 = real.bitc.half_duplex_100t2;
    dummy.bitc.full_duplex_100t2 = real.bitc.full_duplex_100t2;
    dummy.bitc.half_duplex_10 = real.bitc.half_duplex_10;
    dummy.bitc.full_duplex_10 = real.bitc.full_duplex_10;
    dummy.bitc.half_duplex_100x = real.bitc.half_duplex_100x;
    dummy.bitc.full_duplex_100x = real.bitc.full_duplex_100x;
    dummy.bitc.t4_100 = real.bitc.t4_100;
    return dummy.all;
}
GH_INLINE U8   GH_EPHY_get_STATUS_extended_capability(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.extended_capability;
}
GH_INLINE U8   GH_EPHY_get_STATUS_jabber_detect(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jabber_detect;
}
GH_INLINE U8   GH_EPHY_get_STATUS_link_status(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.link_status;
}
GH_INLINE U8   GH_EPHY_get_STATUS_an_ability(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.an_ability;
}
GH_INLINE U8   GH_EPHY_get_STATUS_rf(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rf;
}
GH_INLINE U8   GH_EPHY_get_STATUS_an_complete(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.an_complete;
}
GH_INLINE U8   GH_EPHY_get_STATUS_mf_preamble_suppression(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mf_preamble_suppression;
}
GH_INLINE U8   GH_EPHY_get_STATUS_unidirectional_ability(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.unidirectional_ability;
}
GH_INLINE U8   GH_EPHY_get_STATUS_extended_status(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.extended_status;
}
GH_INLINE U8   GH_EPHY_get_STATUS_half_duplex_100t2(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.half_duplex_100t2;
}
GH_INLINE U8   GH_EPHY_get_STATUS_full_duplex_100t2(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.full_duplex_100t2;
}
GH_INLINE U8   GH_EPHY_get_STATUS_half_duplex_10(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.half_duplex_10;
}
GH_INLINE U8   GH_EPHY_get_STATUS_full_duplex_10(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.full_duplex_10;
}
GH_INLINE U8   GH_EPHY_get_STATUS_half_duplex_100x(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.half_duplex_100x;
}
GH_INLINE U8   GH_EPHY_get_STATUS_full_duplex_100x(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.full_duplex_100x;
}
GH_INLINE U8   GH_EPHY_get_STATUS_t4_100(void)
{
    GH_EPHY_STATUS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.t4_100;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ID1 (read)                                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_EPHY_get_ID1(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ID1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ID2 (read)                                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_EPHY_get_ID2(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_ID2_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ANAR (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_ANAR(U16 data)
{
    GH_EPHY_ANAR_REAL_S real;
    GH_EPHY_ANAR_S dummy;
    dummy.all = data ;
    real.bitc.selector = dummy.bitc.selector;
    real.bitc.tech_ability = dummy.bitc.tech_ability;
    real.bitc.rf = dummy.bitc.rf;
    real.bitc.np = dummy.bitc.np;
    *(volatile U16 *)REG_EPHY_ANAR_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_ANAR(void)
{
    GH_EPHY_ANAR_REAL_S real;
    GH_EPHY_ANAR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ANAR_REAL);

    dummy.bitc.selector = real.bitc.selector;
    dummy.bitc.tech_ability = real.bitc.tech_ability;
    dummy.bitc.rf = real.bitc.rf;
    dummy.bitc.np = real.bitc.np;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_ANAR_selector(U8 data)
{
    GH_EPHY_ANAR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANAR_REAL;
    d.bitc.selector = data;
    *(volatile U16 *)REG_EPHY_ANAR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANAR_selector(void)
{
    GH_EPHY_ANAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.selector;
}
GH_INLINE void GH_EPHY_set_ANAR_tech_ability(U8 data)
{
    GH_EPHY_ANAR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANAR_REAL;
    d.bitc.tech_ability = data;
    *(volatile U16 *)REG_EPHY_ANAR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANAR_tech_ability(void)
{
    GH_EPHY_ANAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tech_ability;
}
GH_INLINE void GH_EPHY_set_ANAR_rf(U8 data)
{
    GH_EPHY_ANAR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANAR_REAL;
    d.bitc.rf = data;
    *(volatile U16 *)REG_EPHY_ANAR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANAR_rf(void)
{
    GH_EPHY_ANAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rf;
}
GH_INLINE void GH_EPHY_set_ANAR_np(U8 data)
{
    GH_EPHY_ANAR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANAR_REAL;
    d.bitc.np = data;
    *(volatile U16 *)REG_EPHY_ANAR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANAR_np(void)
{
    GH_EPHY_ANAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.np;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ANLPAR (read)                                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_EPHY_get_ANLPAR(void)
{
    GH_EPHY_ANLPAR_REAL_S real;
    GH_EPHY_ANLPAR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ANLPAR_REAL);

    dummy.bitc.selector = real.bitc.selector;
    dummy.bitc.tech_ability = real.bitc.tech_ability;
    dummy.bitc.rf = real.bitc.rf;
    dummy.bitc.ack = real.bitc.ack;
    dummy.bitc.np = real.bitc.np;
    return dummy.all;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_selector(void)
{
    GH_EPHY_ANLPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.selector;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_tech_ability(void)
{
    GH_EPHY_ANLPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tech_ability;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_rf(void)
{
    GH_EPHY_ANLPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rf;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_ack(void)
{
    GH_EPHY_ANLPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ack;
}
GH_INLINE U8   GH_EPHY_get_ANLPAR_np(void)
{
    GH_EPHY_ANLPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.np;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ANER (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_ANER(U16 data)
{
    GH_EPHY_ANER_REAL_S real;
    GH_EPHY_ANER_S dummy;
    dummy.all = data ;
    real.bitc.lp_an_able = dummy.bitc.lp_an_able;
    real.bitc.page_rec = dummy.bitc.page_rec;
    real.bitc.np_able = dummy.bitc.np_able;
    real.bitc.lp_np_able = dummy.bitc.lp_np_able;
    real.bitc.pd_fault = dummy.bitc.pd_fault;
    real.bitc.np_location = dummy.bitc.np_location;
    real.bitc.np_location_able = dummy.bitc.np_location_able;
    *(volatile U16 *)REG_EPHY_ANER_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_ANER(void)
{
    GH_EPHY_ANER_REAL_S real;
    GH_EPHY_ANER_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ANER_REAL);

    dummy.bitc.lp_an_able = real.bitc.lp_an_able;
    dummy.bitc.page_rec = real.bitc.page_rec;
    dummy.bitc.np_able = real.bitc.np_able;
    dummy.bitc.lp_np_able = real.bitc.lp_np_able;
    dummy.bitc.pd_fault = real.bitc.pd_fault;
    dummy.bitc.np_location = real.bitc.np_location;
    dummy.bitc.np_location_able = real.bitc.np_location_able;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_ANER_lp_an_able(U8 data)
{
    GH_EPHY_ANER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER_REAL;
    d.bitc.lp_an_able = data;
    *(volatile U16 *)REG_EPHY_ANER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANER_lp_an_able(void)
{
    GH_EPHY_ANER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lp_an_able;
}
GH_INLINE void GH_EPHY_set_ANER_page_rec(U8 data)
{
    GH_EPHY_ANER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER_REAL;
    d.bitc.page_rec = data;
    *(volatile U16 *)REG_EPHY_ANER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANER_page_rec(void)
{
    GH_EPHY_ANER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.page_rec;
}
GH_INLINE void GH_EPHY_set_ANER_np_able(U8 data)
{
    GH_EPHY_ANER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER_REAL;
    d.bitc.np_able = data;
    *(volatile U16 *)REG_EPHY_ANER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANER_np_able(void)
{
    GH_EPHY_ANER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.np_able;
}
GH_INLINE void GH_EPHY_set_ANER_lp_np_able(U8 data)
{
    GH_EPHY_ANER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER_REAL;
    d.bitc.lp_np_able = data;
    *(volatile U16 *)REG_EPHY_ANER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANER_lp_np_able(void)
{
    GH_EPHY_ANER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lp_np_able;
}
GH_INLINE void GH_EPHY_set_ANER_pd_fault(U8 data)
{
    GH_EPHY_ANER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER_REAL;
    d.bitc.pd_fault = data;
    *(volatile U16 *)REG_EPHY_ANER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANER_pd_fault(void)
{
    GH_EPHY_ANER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_fault;
}
GH_INLINE void GH_EPHY_set_ANER_np_location(U8 data)
{
    GH_EPHY_ANER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER_REAL;
    d.bitc.np_location = data;
    *(volatile U16 *)REG_EPHY_ANER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANER_np_location(void)
{
    GH_EPHY_ANER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.np_location;
}
GH_INLINE void GH_EPHY_set_ANER_np_location_able(U8 data)
{
    GH_EPHY_ANER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANER_REAL;
    d.bitc.np_location_able = data;
    *(volatile U16 *)REG_EPHY_ANER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANER_np_location_able(void)
{
    GH_EPHY_ANER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.np_location_able;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ANNPAR (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_ANNPAR(U16 data)
{
    GH_EPHY_ANNPAR_REAL_S real;
    GH_EPHY_ANNPAR_S dummy;
    dummy.all = data ;
    real.bitc.msg = dummy.bitc.msg;
    real.bitc.toggle = dummy.bitc.toggle;
    real.bitc.ack2 = dummy.bitc.ack2;
    real.bitc.mp = dummy.bitc.mp;
    real.bitc.np = dummy.bitc.np;
    *(volatile U16 *)REG_EPHY_ANNPAR_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_ANNPAR(void)
{
    GH_EPHY_ANNPAR_REAL_S real;
    GH_EPHY_ANNPAR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ANNPAR_REAL);

    dummy.bitc.msg = real.bitc.msg;
    dummy.bitc.toggle = real.bitc.toggle;
    dummy.bitc.ack2 = real.bitc.ack2;
    dummy.bitc.mp = real.bitc.mp;
    dummy.bitc.np = real.bitc.np;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_ANNPAR_msg(U16 data)
{
    GH_EPHY_ANNPAR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR_REAL;
    d.bitc.msg = data;
    *(volatile U16 *)REG_EPHY_ANNPAR_REAL = d.all;
}
GH_INLINE U16  GH_EPHY_get_ANNPAR_msg(void)
{
    GH_EPHY_ANNPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.msg;
}
GH_INLINE void GH_EPHY_set_ANNPAR_toggle(U8 data)
{
    GH_EPHY_ANNPAR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR_REAL;
    d.bitc.toggle = data;
    *(volatile U16 *)REG_EPHY_ANNPAR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANNPAR_toggle(void)
{
    GH_EPHY_ANNPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.toggle;
}
GH_INLINE void GH_EPHY_set_ANNPAR_ack2(U8 data)
{
    GH_EPHY_ANNPAR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR_REAL;
    d.bitc.ack2 = data;
    *(volatile U16 *)REG_EPHY_ANNPAR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANNPAR_ack2(void)
{
    GH_EPHY_ANNPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ack2;
}
GH_INLINE void GH_EPHY_set_ANNPAR_mp(U8 data)
{
    GH_EPHY_ANNPAR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR_REAL;
    d.bitc.mp = data;
    *(volatile U16 *)REG_EPHY_ANNPAR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANNPAR_mp(void)
{
    GH_EPHY_ANNPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mp;
}
GH_INLINE void GH_EPHY_set_ANNPAR_np(U8 data)
{
    GH_EPHY_ANNPAR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ANNPAR_REAL;
    d.bitc.np = data;
    *(volatile U16 *)REG_EPHY_ANNPAR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ANNPAR_np(void)
{
    GH_EPHY_ANNPAR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANNPAR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.np;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ANLPNP (read)                                                */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_EPHY_get_ANLPNP(void)
{
    GH_EPHY_ANLPNP_REAL_S real;
    GH_EPHY_ANLPNP_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ANLPNP_REAL);

    dummy.bitc.msg = real.bitc.msg;
    dummy.bitc.toggle = real.bitc.toggle;
    dummy.bitc.ack2 = real.bitc.ack2;
    dummy.bitc.mp = real.bitc.mp;
    dummy.bitc.np = real.bitc.np;
    return dummy.all;
}
GH_INLINE U16  GH_EPHY_get_ANLPNP_msg(void)
{
    GH_EPHY_ANLPNP_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.msg;
}
GH_INLINE U8   GH_EPHY_get_ANLPNP_toggle(void)
{
    GH_EPHY_ANLPNP_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.toggle;
}
GH_INLINE U8   GH_EPHY_get_ANLPNP_ack2(void)
{
    GH_EPHY_ANLPNP_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ack2;
}
GH_INLINE U8   GH_EPHY_get_ANLPNP_mp(void)
{
    GH_EPHY_ANLPNP_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mp;
}
GH_INLINE U8   GH_EPHY_get_ANLPNP_np(void)
{
    GH_EPHY_ANLPNP_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ANLPNP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.np;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_MS_CONTROL (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_MS_CONTROL(U16 data)
{
    *(volatile U16 *)REG_EPHY_MS_CONTROL_REAL = data;
}
GH_INLINE U16  GH_EPHY_get_MS_CONTROL(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_MS_CONTROL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_MS_STATUS (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_EPHY_get_MS_STATUS(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_MS_STATUS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_PSE_CONTROL (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_PSE_CONTROL(U16 data)
{
    *(volatile U16 *)REG_EPHY_PSE_CONTROL_REAL = data;
}
GH_INLINE U16  GH_EPHY_get_PSE_CONTROL(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_PSE_CONTROL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_PSE_STATUS (read)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_EPHY_get_PSE_STATUS(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_PSE_STATUS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_MMD_CONTROL (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_MMD_CONTROL(U16 data)
{
    GH_EPHY_MMD_CONTROL_REAL_S real;
    GH_EPHY_MMD_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.devad = dummy.bitc.devad;
    real.bitc.func = dummy.bitc.func;
    *(volatile U16 *)REG_EPHY_MMD_CONTROL_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_MMD_CONTROL(void)
{
    GH_EPHY_MMD_CONTROL_REAL_S real;
    GH_EPHY_MMD_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_MMD_CONTROL_REAL);

    dummy.bitc.devad = real.bitc.devad;
    dummy.bitc.func = real.bitc.func;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_MMD_CONTROL_devad(U8 data)
{
    GH_EPHY_MMD_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_MMD_CONTROL_REAL;
    d.bitc.devad = data;
    *(volatile U16 *)REG_EPHY_MMD_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_MMD_CONTROL_devad(void)
{
    GH_EPHY_MMD_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MMD_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.devad;
}
GH_INLINE void GH_EPHY_set_MMD_CONTROL_func(U8 data)
{
    GH_EPHY_MMD_CONTROL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_MMD_CONTROL_REAL;
    d.bitc.func = data;
    *(volatile U16 *)REG_EPHY_MMD_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_MMD_CONTROL_func(void)
{
    GH_EPHY_MMD_CONTROL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MMD_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.func;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_MMD_CONTROL_ADDR (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_MMD_CONTROL_ADDR(U16 data)
{
    *(volatile U16 *)REG_EPHY_MMD_CONTROL_ADDR_REAL = data;
}
GH_INLINE U16  GH_EPHY_get_MMD_CONTROL_ADDR(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_MMD_CONTROL_ADDR_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_AN_R_15 (read)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_EPHY_get_AN_R_15(void)
{
    GH_EPHY_AN_R_15_REAL_S real;
    GH_EPHY_AN_R_15_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_AN_R_15_REAL);

    dummy.bitc.an_register_15 = real.bitc.an_register_15;
    return dummy.all;
}
GH_INLINE U8   GH_EPHY_get_AN_R_15_an_register_15(void)
{
    GH_EPHY_AN_R_15_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_AN_R_15_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.an_register_15;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_34 (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_34(U16 data)
{
    GH_EPHY_WAVE_SHAPING_34_REAL_S real;
    GH_EPHY_WAVE_SHAPING_34_S dummy;
    dummy.all = data ;
    real.bitc.ltp_3 = dummy.bitc.ltp_3;
    real.bitc.ltp_4 = dummy.bitc.ltp_4;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_34(void)
{
    GH_EPHY_WAVE_SHAPING_34_REAL_S real;
    GH_EPHY_WAVE_SHAPING_34_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_34_REAL);

    dummy.bitc.ltp_3 = real.bitc.ltp_3;
    dummy.bitc.ltp_4 = real.bitc.ltp_4;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_34_ltp_3(U8 data)
{
    GH_EPHY_WAVE_SHAPING_34_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34_REAL;
    d.bitc.ltp_3 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_34_ltp_3(void)
{
    GH_EPHY_WAVE_SHAPING_34_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_34_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_3;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_34_ltp_4(U8 data)
{
    GH_EPHY_WAVE_SHAPING_34_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34_REAL;
    d.bitc.ltp_4 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_34_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_34_ltp_4(void)
{
    GH_EPHY_WAVE_SHAPING_34_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_34_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_4;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_56 (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_56(U16 data)
{
    GH_EPHY_WAVE_SHAPING_56_REAL_S real;
    GH_EPHY_WAVE_SHAPING_56_S dummy;
    dummy.all = data ;
    real.bitc.ltp_5 = dummy.bitc.ltp_5;
    real.bitc.ltp_6 = dummy.bitc.ltp_6;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_56(void)
{
    GH_EPHY_WAVE_SHAPING_56_REAL_S real;
    GH_EPHY_WAVE_SHAPING_56_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_56_REAL);

    dummy.bitc.ltp_5 = real.bitc.ltp_5;
    dummy.bitc.ltp_6 = real.bitc.ltp_6;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_56_ltp_5(U8 data)
{
    GH_EPHY_WAVE_SHAPING_56_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56_REAL;
    d.bitc.ltp_5 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_56_ltp_5(void)
{
    GH_EPHY_WAVE_SHAPING_56_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_56_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_5;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_56_ltp_6(U8 data)
{
    GH_EPHY_WAVE_SHAPING_56_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56_REAL;
    d.bitc.ltp_6 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_56_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_56_ltp_6(void)
{
    GH_EPHY_WAVE_SHAPING_56_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_56_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_6;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_78 (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_78(U16 data)
{
    GH_EPHY_WAVE_SHAPING_78_REAL_S real;
    GH_EPHY_WAVE_SHAPING_78_S dummy;
    dummy.all = data ;
    real.bitc.ltp_7 = dummy.bitc.ltp_7;
    real.bitc.ltp_8 = dummy.bitc.ltp_8;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_78(void)
{
    GH_EPHY_WAVE_SHAPING_78_REAL_S real;
    GH_EPHY_WAVE_SHAPING_78_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_78_REAL);

    dummy.bitc.ltp_7 = real.bitc.ltp_7;
    dummy.bitc.ltp_8 = real.bitc.ltp_8;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_78_ltp_7(U8 data)
{
    GH_EPHY_WAVE_SHAPING_78_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78_REAL;
    d.bitc.ltp_7 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_78_ltp_7(void)
{
    GH_EPHY_WAVE_SHAPING_78_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_78_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_7;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_78_ltp_8(U8 data)
{
    GH_EPHY_WAVE_SHAPING_78_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78_REAL;
    d.bitc.ltp_8 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_78_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_78_ltp_8(void)
{
    GH_EPHY_WAVE_SHAPING_78_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_78_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_8;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_9A (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_9A(U16 data)
{
    GH_EPHY_WAVE_SHAPING_9A_REAL_S real;
    GH_EPHY_WAVE_SHAPING_9A_S dummy;
    dummy.all = data ;
    real.bitc.ltp_9 = dummy.bitc.ltp_9;
    real.bitc.ltp_a = dummy.bitc.ltp_a;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_9A(void)
{
    GH_EPHY_WAVE_SHAPING_9A_REAL_S real;
    GH_EPHY_WAVE_SHAPING_9A_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A_REAL);

    dummy.bitc.ltp_9 = real.bitc.ltp_9;
    dummy.bitc.ltp_a = real.bitc.ltp_a;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_9A_ltp_9(U8 data)
{
    GH_EPHY_WAVE_SHAPING_9A_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A_REAL;
    d.bitc.ltp_9 = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_9A_ltp_9(void)
{
    GH_EPHY_WAVE_SHAPING_9A_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_9;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_9A_ltp_A(U8 data)
{
    GH_EPHY_WAVE_SHAPING_9A_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A_REAL;
    d.bitc.ltp_a = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_9A_ltp_A(void)
{
    GH_EPHY_WAVE_SHAPING_9A_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_9A_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_a;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_BC (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_BC(U16 data)
{
    GH_EPHY_WAVE_SHAPING_BC_REAL_S real;
    GH_EPHY_WAVE_SHAPING_BC_S dummy;
    dummy.all = data ;
    real.bitc.ltp_b = dummy.bitc.ltp_b;
    real.bitc.ltp_c = dummy.bitc.ltp_c;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_BC(void)
{
    GH_EPHY_WAVE_SHAPING_BC_REAL_S real;
    GH_EPHY_WAVE_SHAPING_BC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC_REAL);

    dummy.bitc.ltp_b = real.bitc.ltp_b;
    dummy.bitc.ltp_c = real.bitc.ltp_c;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_BC_ltp_B(U8 data)
{
    GH_EPHY_WAVE_SHAPING_BC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC_REAL;
    d.bitc.ltp_b = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_BC_ltp_B(void)
{
    GH_EPHY_WAVE_SHAPING_BC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_b;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_BC_ltp_C(U8 data)
{
    GH_EPHY_WAVE_SHAPING_BC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC_REAL;
    d.bitc.ltp_c = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_BC_ltp_C(void)
{
    GH_EPHY_WAVE_SHAPING_BC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_BC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_c;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_SHAPING_DE (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_DE(U16 data)
{
    GH_EPHY_WAVE_SHAPING_DE_REAL_S real;
    GH_EPHY_WAVE_SHAPING_DE_S dummy;
    dummy.all = data ;
    real.bitc.ltp_d = dummy.bitc.ltp_d;
    real.bitc.ltp_e = dummy.bitc.ltp_e;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_WAVE_SHAPING_DE(void)
{
    GH_EPHY_WAVE_SHAPING_DE_REAL_S real;
    GH_EPHY_WAVE_SHAPING_DE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE_REAL);

    dummy.bitc.ltp_d = real.bitc.ltp_d;
    dummy.bitc.ltp_e = real.bitc.ltp_e;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_DE_ltp_D(U8 data)
{
    GH_EPHY_WAVE_SHAPING_DE_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE_REAL;
    d.bitc.ltp_d = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_DE_ltp_D(void)
{
    GH_EPHY_WAVE_SHAPING_DE_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_d;
}
GH_INLINE void GH_EPHY_set_WAVE_SHAPING_DE_ltp_E(U8 data)
{
    GH_EPHY_WAVE_SHAPING_DE_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE_REAL;
    d.bitc.ltp_e = data;
    *(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_SHAPING_DE_ltp_E(void)
{
    GH_EPHY_WAVE_SHAPING_DE_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_SHAPING_DE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_e;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_SPEED (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_SPEED(U16 data)
{
    GH_EPHY_SPEED_REAL_S real;
    GH_EPHY_SPEED_S dummy;
    dummy.all = data ;
    real.bitc.ltp_f = dummy.bitc.ltp_f;
    real.bitc.isolate = dummy.bitc.isolate;
    real.bitc.rptr = dummy.bitc.rptr;
    real.bitc.duplex = dummy.bitc.duplex;
    real.bitc.speed = dummy.bitc.speed;
    real.bitc.ane = dummy.bitc.ane;
    real.bitc.ldps = dummy.bitc.ldps;
    real.bitc.disable_eee_force = dummy.bitc.disable_eee_force;
    *(volatile U16 *)REG_EPHY_SPEED_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_SPEED(void)
{
    GH_EPHY_SPEED_REAL_S real;
    GH_EPHY_SPEED_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_SPEED_REAL);

    dummy.bitc.ltp_f = real.bitc.ltp_f;
    dummy.bitc.isolate = real.bitc.isolate;
    dummy.bitc.rptr = real.bitc.rptr;
    dummy.bitc.duplex = real.bitc.duplex;
    dummy.bitc.speed = real.bitc.speed;
    dummy.bitc.ane = real.bitc.ane;
    dummy.bitc.ldps = real.bitc.ldps;
    dummy.bitc.disable_eee_force = real.bitc.disable_eee_force;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_SPEED_ltp_F(U8 data)
{
    GH_EPHY_SPEED_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED_REAL;
    d.bitc.ltp_f = data;
    *(volatile U16 *)REG_EPHY_SPEED_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SPEED_ltp_F(void)
{
    GH_EPHY_SPEED_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ltp_f;
}
GH_INLINE void GH_EPHY_set_SPEED_isolate(U8 data)
{
    GH_EPHY_SPEED_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED_REAL;
    d.bitc.isolate = data;
    *(volatile U16 *)REG_EPHY_SPEED_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SPEED_isolate(void)
{
    GH_EPHY_SPEED_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.isolate;
}
GH_INLINE void GH_EPHY_set_SPEED_rptr(U8 data)
{
    GH_EPHY_SPEED_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED_REAL;
    d.bitc.rptr = data;
    *(volatile U16 *)REG_EPHY_SPEED_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SPEED_rptr(void)
{
    GH_EPHY_SPEED_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rptr;
}
GH_INLINE void GH_EPHY_set_SPEED_duplex(U8 data)
{
    GH_EPHY_SPEED_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED_REAL;
    d.bitc.duplex = data;
    *(volatile U16 *)REG_EPHY_SPEED_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SPEED_duplex(void)
{
    GH_EPHY_SPEED_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.duplex;
}
GH_INLINE void GH_EPHY_set_SPEED_speed(U8 data)
{
    GH_EPHY_SPEED_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED_REAL;
    d.bitc.speed = data;
    *(volatile U16 *)REG_EPHY_SPEED_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SPEED_speed(void)
{
    GH_EPHY_SPEED_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.speed;
}
GH_INLINE void GH_EPHY_set_SPEED_ane(U8 data)
{
    GH_EPHY_SPEED_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED_REAL;
    d.bitc.ane = data;
    *(volatile U16 *)REG_EPHY_SPEED_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SPEED_ane(void)
{
    GH_EPHY_SPEED_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ane;
}
GH_INLINE void GH_EPHY_set_SPEED_ldps(U8 data)
{
    GH_EPHY_SPEED_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED_REAL;
    d.bitc.ldps = data;
    *(volatile U16 *)REG_EPHY_SPEED_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SPEED_ldps(void)
{
    GH_EPHY_SPEED_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ldps;
}
GH_INLINE void GH_EPHY_set_SPEED_disable_eee_force(U8 data)
{
    GH_EPHY_SPEED_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SPEED_REAL;
    d.bitc.disable_eee_force = data;
    *(volatile U16 *)REG_EPHY_SPEED_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SPEED_disable_eee_force(void)
{
    GH_EPHY_SPEED_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SPEED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.disable_eee_force;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_LTP (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_LTP(U16 data)
{
    GH_EPHY_LTP_REAL_S real;
    GH_EPHY_LTP_S dummy;
    dummy.all = data ;
    real.bitc.width = dummy.bitc.width;
    real.bitc.tx_gm_rctrl = dummy.bitc.tx_gm_rctrl;
    *(volatile U16 *)REG_EPHY_LTP_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_LTP(void)
{
    GH_EPHY_LTP_REAL_S real;
    GH_EPHY_LTP_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_LTP_REAL);

    dummy.bitc.width = real.bitc.width;
    dummy.bitc.tx_gm_rctrl = real.bitc.tx_gm_rctrl;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_LTP_width(U8 data)
{
    GH_EPHY_LTP_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_LTP_REAL;
    d.bitc.width = data;
    *(volatile U16 *)REG_EPHY_LTP_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_LTP_width(void)
{
    GH_EPHY_LTP_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LTP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.width;
}
GH_INLINE void GH_EPHY_set_LTP_tx_gm_rctrl(U8 data)
{
    GH_EPHY_LTP_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_LTP_REAL;
    d.bitc.tx_gm_rctrl = data;
    *(volatile U16 *)REG_EPHY_LTP_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_LTP_tx_gm_rctrl(void)
{
    GH_EPHY_LTP_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LTP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tx_gm_rctrl;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_MCU (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_MCU(U16 data)
{
    GH_EPHY_MCU_REAL_S real;
    GH_EPHY_MCU_S dummy;
    dummy.all = data ;
    real.bitc.en = dummy.bitc.en;
    real.bitc.mcu_rdy = dummy.bitc.mcu_rdy;
    *(volatile U16 *)REG_EPHY_MCU_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_MCU(void)
{
    GH_EPHY_MCU_REAL_S real;
    GH_EPHY_MCU_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_MCU_REAL);

    dummy.bitc.en = real.bitc.en;
    dummy.bitc.mcu_rdy = real.bitc.mcu_rdy;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_MCU_en(U8 data)
{
    GH_EPHY_MCU_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_MCU_REAL;
    d.bitc.en = data;
    *(volatile U16 *)REG_EPHY_MCU_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_MCU_en(void)
{
    GH_EPHY_MCU_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MCU_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en;
}
GH_INLINE void GH_EPHY_set_MCU_mcu_rdy(U8 data)
{
    GH_EPHY_MCU_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_MCU_REAL;
    d.bitc.mcu_rdy = data;
    *(volatile U16 *)REG_EPHY_MCU_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_MCU_mcu_rdy(void)
{
    GH_EPHY_MCU_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MCU_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mcu_rdy;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_CODE_RAM (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_CODE_RAM(U16 data)
{
    GH_EPHY_CODE_RAM_REAL_S real;
    GH_EPHY_CODE_RAM_S dummy;
    dummy.all = data ;
    real.bitc.start_addr = dummy.bitc.start_addr;
    *(volatile U16 *)REG_EPHY_CODE_RAM_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_CODE_RAM(void)
{
    GH_EPHY_CODE_RAM_REAL_S real;
    GH_EPHY_CODE_RAM_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_CODE_RAM_REAL);

    dummy.bitc.start_addr = real.bitc.start_addr;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_CODE_RAM_start_addr(U16 data)
{
    GH_EPHY_CODE_RAM_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CODE_RAM_REAL;
    d.bitc.start_addr = data;
    *(volatile U16 *)REG_EPHY_CODE_RAM_REAL = d.all;
}
GH_INLINE U16  GH_EPHY_get_CODE_RAM_start_addr(void)
{
    GH_EPHY_CODE_RAM_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CODE_RAM_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_addr;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_CODE_RAM_W (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_CODE_RAM_W(U16 data)
{
    GH_EPHY_CODE_RAM_W_REAL_S real;
    GH_EPHY_CODE_RAM_W_S dummy;
    dummy.all = data ;
    real.bitc.start_addr = dummy.bitc.start_addr;
    *(volatile U16 *)REG_EPHY_CODE_RAM_W_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_CODE_RAM_W(void)
{
    GH_EPHY_CODE_RAM_W_REAL_S real;
    GH_EPHY_CODE_RAM_W_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_CODE_RAM_W_REAL);

    dummy.bitc.start_addr = real.bitc.start_addr;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_CODE_RAM_W_start_addr(U16 data)
{
    GH_EPHY_CODE_RAM_W_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CODE_RAM_W_REAL;
    d.bitc.start_addr = data;
    *(volatile U16 *)REG_EPHY_CODE_RAM_W_REAL = d.all;
}
GH_INLINE U16  GH_EPHY_get_CODE_RAM_W_start_addr(void)
{
    GH_EPHY_CODE_RAM_W_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CODE_RAM_W_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_addr;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_100M_LINK (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_100M_LINK(U16 data)
{
    GH_EPHY_100M_LINK_REAL_S real;
    GH_EPHY_100M_LINK_S dummy;
    dummy.all = data ;
    real.bitc.an_mcu_100t_link_control = dummy.bitc.an_mcu_100t_link_control;
    real.bitc.an_mcu_nlp_link_control = dummy.bitc.an_mcu_nlp_link_control;
    real.bitc.nlp_frame_start_mode_en = dummy.bitc.nlp_frame_start_mode_en;
    real.bitc.detect_100m = dummy.bitc.detect_100m;
    real.bitc.mcu_an_enable = dummy.bitc.mcu_an_enable;
    real.bitc.force_100m_link_good = dummy.bitc.force_100m_link_good;
    real.bitc.an_100t_link_status = dummy.bitc.an_100t_link_status;
    real.bitc.an_nlp_link_status = dummy.bitc.an_nlp_link_status;
    real.bitc.mdio_disable = dummy.bitc.mdio_disable;
    real.bitc.mdc_edge_sel = dummy.bitc.mdc_edge_sel;
    real.bitc.an_bypass_link_status_check = dummy.bitc.an_bypass_link_status_check;
    real.bitc.adc_loop = dummy.bitc.adc_loop;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_100M_LINK(void)
{
    GH_EPHY_100M_LINK_REAL_S real;
    GH_EPHY_100M_LINK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    dummy.bitc.an_mcu_100t_link_control = real.bitc.an_mcu_100t_link_control;
    dummy.bitc.an_mcu_nlp_link_control = real.bitc.an_mcu_nlp_link_control;
    dummy.bitc.nlp_frame_start_mode_en = real.bitc.nlp_frame_start_mode_en;
    dummy.bitc.detect_100m = real.bitc.detect_100m;
    dummy.bitc.mcu_an_enable = real.bitc.mcu_an_enable;
    dummy.bitc.force_100m_link_good = real.bitc.force_100m_link_good;
    dummy.bitc.an_100t_link_status = real.bitc.an_100t_link_status;
    dummy.bitc.an_nlp_link_status = real.bitc.an_nlp_link_status;
    dummy.bitc.mdio_disable = real.bitc.mdio_disable;
    dummy.bitc.mdc_edge_sel = real.bitc.mdc_edge_sel;
    dummy.bitc.an_bypass_link_status_check = real.bitc.an_bypass_link_status_check;
    dummy.bitc.adc_loop = real.bitc.adc_loop;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_mcu_100t_link_control(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.an_mcu_100t_link_control = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_mcu_100t_link_control(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.an_mcu_100t_link_control;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_mcu_nlp_link_control(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.an_mcu_nlp_link_control = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_mcu_nlp_link_control(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.an_mcu_nlp_link_control;
}
GH_INLINE void GH_EPHY_set_100M_LINK_nlp_frame_start_mode_en(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.nlp_frame_start_mode_en = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_nlp_frame_start_mode_en(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.nlp_frame_start_mode_en;
}
GH_INLINE void GH_EPHY_set_100M_LINK_detect_100m(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.detect_100m = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_detect_100m(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.detect_100m;
}
GH_INLINE void GH_EPHY_set_100M_LINK_mcu_an_enable(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.mcu_an_enable = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_mcu_an_enable(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mcu_an_enable;
}
GH_INLINE void GH_EPHY_set_100M_LINK_force_100m_link_good(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.force_100m_link_good = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_force_100m_link_good(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.force_100m_link_good;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_100t_link_status(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.an_100t_link_status = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_100t_link_status(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.an_100t_link_status;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_nlp_link_status(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.an_nlp_link_status = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_nlp_link_status(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.an_nlp_link_status;
}
GH_INLINE void GH_EPHY_set_100M_LINK_mdio_disable(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.mdio_disable = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_mdio_disable(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mdio_disable;
}
GH_INLINE void GH_EPHY_set_100M_LINK_mdc_edge_sel(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.mdc_edge_sel = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_mdc_edge_sel(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mdc_edge_sel;
}
GH_INLINE void GH_EPHY_set_100M_LINK_an_bypass_link_status_check(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.an_bypass_link_status_check = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_an_bypass_link_status_check(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.an_bypass_link_status_check;
}
GH_INLINE void GH_EPHY_set_100M_LINK_adc_loop(U8 data)
{
    GH_EPHY_100M_LINK_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_100M_LINK_REAL;
    d.bitc.adc_loop = data;
    *(volatile U16 *)REG_EPHY_100M_LINK_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_100M_LINK_adc_loop(void)
{
    GH_EPHY_100M_LINK_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_100M_LINK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_loop;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_DEBUG (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_DEBUG(U16 data)
{
    GH_EPHY_DEBUG_REAL_S real;
    GH_EPHY_DEBUG_S dummy;
    dummy.all = data ;
    real.bitc.snr_locked = dummy.bitc.snr_locked;
    real.bitc.snr_locked_raw = dummy.bitc.snr_locked_raw;
    real.bitc.sig_det_flag = dummy.bitc.sig_det_flag;
    real.bitc.state_sync_on = dummy.bitc.state_sync_on;
    real.bitc.state_st_lk = dummy.bitc.state_st_lk;
    real.bitc.mux_recov_cnt = dummy.bitc.mux_recov_cnt;
    real.bitc.test_mux_sel = dummy.bitc.test_mux_sel;
    *(volatile U16 *)REG_EPHY_DEBUG_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_DEBUG(void)
{
    GH_EPHY_DEBUG_REAL_S real;
    GH_EPHY_DEBUG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_DEBUG_REAL);

    dummy.bitc.snr_locked = real.bitc.snr_locked;
    dummy.bitc.snr_locked_raw = real.bitc.snr_locked_raw;
    dummy.bitc.sig_det_flag = real.bitc.sig_det_flag;
    dummy.bitc.state_sync_on = real.bitc.state_sync_on;
    dummy.bitc.state_st_lk = real.bitc.state_st_lk;
    dummy.bitc.mux_recov_cnt = real.bitc.mux_recov_cnt;
    dummy.bitc.test_mux_sel = real.bitc.test_mux_sel;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_DEBUG_snr_locked(U8 data)
{
    GH_EPHY_DEBUG_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_REAL;
    d.bitc.snr_locked = data;
    *(volatile U16 *)REG_EPHY_DEBUG_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DEBUG_snr_locked(void)
{
    GH_EPHY_DEBUG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.snr_locked;
}
GH_INLINE void GH_EPHY_set_DEBUG_snr_locked_raw(U8 data)
{
    GH_EPHY_DEBUG_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_REAL;
    d.bitc.snr_locked_raw = data;
    *(volatile U16 *)REG_EPHY_DEBUG_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DEBUG_snr_locked_raw(void)
{
    GH_EPHY_DEBUG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.snr_locked_raw;
}
GH_INLINE void GH_EPHY_set_DEBUG_sig_det_flag(U8 data)
{
    GH_EPHY_DEBUG_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_REAL;
    d.bitc.sig_det_flag = data;
    *(volatile U16 *)REG_EPHY_DEBUG_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DEBUG_sig_det_flag(void)
{
    GH_EPHY_DEBUG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sig_det_flag;
}
GH_INLINE void GH_EPHY_set_DEBUG_state_sync_on(U8 data)
{
    GH_EPHY_DEBUG_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_REAL;
    d.bitc.state_sync_on = data;
    *(volatile U16 *)REG_EPHY_DEBUG_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DEBUG_state_sync_on(void)
{
    GH_EPHY_DEBUG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.state_sync_on;
}
GH_INLINE void GH_EPHY_set_DEBUG_state_st_lk(U8 data)
{
    GH_EPHY_DEBUG_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_REAL;
    d.bitc.state_st_lk = data;
    *(volatile U16 *)REG_EPHY_DEBUG_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DEBUG_state_st_lk(void)
{
    GH_EPHY_DEBUG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.state_st_lk;
}
GH_INLINE void GH_EPHY_set_DEBUG_mux_recov_cnt(U8 data)
{
    GH_EPHY_DEBUG_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_REAL;
    d.bitc.mux_recov_cnt = data;
    *(volatile U16 *)REG_EPHY_DEBUG_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DEBUG_mux_recov_cnt(void)
{
    GH_EPHY_DEBUG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mux_recov_cnt;
}
GH_INLINE void GH_EPHY_set_DEBUG_test_mux_sel(U8 data)
{
    GH_EPHY_DEBUG_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_REAL;
    d.bitc.test_mux_sel = data;
    *(volatile U16 *)REG_EPHY_DEBUG_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DEBUG_test_mux_sel(void)
{
    GH_EPHY_DEBUG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.test_mux_sel;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_DEBUG_MODE (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_DEBUG_MODE(U16 data)
{
    GH_EPHY_DEBUG_MODE_REAL_S real;
    GH_EPHY_DEBUG_MODE_S dummy;
    dummy.all = data ;
    real.bitc.signal = dummy.bitc.signal;
    real.bitc.module = dummy.bitc.module;
    *(volatile U16 *)REG_EPHY_DEBUG_MODE_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_DEBUG_MODE(void)
{
    GH_EPHY_DEBUG_MODE_REAL_S real;
    GH_EPHY_DEBUG_MODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_DEBUG_MODE_REAL);

    dummy.bitc.signal = real.bitc.signal;
    dummy.bitc.module = real.bitc.module;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_DEBUG_MODE_signal(U8 data)
{
    GH_EPHY_DEBUG_MODE_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_MODE_REAL;
    d.bitc.signal = data;
    *(volatile U16 *)REG_EPHY_DEBUG_MODE_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DEBUG_MODE_signal(void)
{
    GH_EPHY_DEBUG_MODE_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.signal;
}
GH_INLINE void GH_EPHY_set_DEBUG_MODE_module(U8 data)
{
    GH_EPHY_DEBUG_MODE_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DEBUG_MODE_REAL;
    d.bitc.module = data;
    *(volatile U16 *)REG_EPHY_DEBUG_MODE_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DEBUG_MODE_module(void)
{
    GH_EPHY_DEBUG_MODE_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DEBUG_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.module;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_RST_EN (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_RST_EN(U16 data)
{
    GH_EPHY_RST_EN_REAL_S real;
    GH_EPHY_RST_EN_S dummy;
    dummy.all = data ;
    real.bitc.mau_srst = dummy.bitc.mau_srst;
    real.bitc.pls_srst = dummy.bitc.pls_srst;
    real.bitc.sqe_test_enable = dummy.bitc.sqe_test_enable;
    real.bitc.lpbk_enable = dummy.bitc.lpbk_enable;
    real.bitc.jabber_enable = dummy.bitc.jabber_enable;
    real.bitc.ser_polarity_correction = dummy.bitc.ser_polarity_correction;
    real.bitc.por_stick_mode = dummy.bitc.por_stick_mode;
    real.bitc.recv_bit_bucket = dummy.bitc.recv_bit_bucket;
    real.bitc.rxclk_pol = dummy.bitc.rxclk_pol;
    real.bitc.txclk_pol = dummy.bitc.txclk_pol;
    real.bitc.adc_input_sign = dummy.bitc.adc_input_sign;
    real.bitc.mii_test_packet = dummy.bitc.mii_test_packet;
    real.bitc.clear_rcvpack = dummy.bitc.clear_rcvpack;
    real.bitc.miiloop_en_10m = dummy.bitc.miiloop_en_10m;
    real.bitc.mii_rxclk_pol = dummy.bitc.mii_rxclk_pol;
    real.bitc.mii_txclk_pol = dummy.bitc.mii_txclk_pol;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_RST_EN(void)
{
    GH_EPHY_RST_EN_REAL_S real;
    GH_EPHY_RST_EN_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    dummy.bitc.mau_srst = real.bitc.mau_srst;
    dummy.bitc.pls_srst = real.bitc.pls_srst;
    dummy.bitc.sqe_test_enable = real.bitc.sqe_test_enable;
    dummy.bitc.lpbk_enable = real.bitc.lpbk_enable;
    dummy.bitc.jabber_enable = real.bitc.jabber_enable;
    dummy.bitc.ser_polarity_correction = real.bitc.ser_polarity_correction;
    dummy.bitc.por_stick_mode = real.bitc.por_stick_mode;
    dummy.bitc.recv_bit_bucket = real.bitc.recv_bit_bucket;
    dummy.bitc.rxclk_pol = real.bitc.rxclk_pol;
    dummy.bitc.txclk_pol = real.bitc.txclk_pol;
    dummy.bitc.adc_input_sign = real.bitc.adc_input_sign;
    dummy.bitc.mii_test_packet = real.bitc.mii_test_packet;
    dummy.bitc.clear_rcvpack = real.bitc.clear_rcvpack;
    dummy.bitc.miiloop_en_10m = real.bitc.miiloop_en_10m;
    dummy.bitc.mii_rxclk_pol = real.bitc.mii_rxclk_pol;
    dummy.bitc.mii_txclk_pol = real.bitc.mii_txclk_pol;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_RST_EN_mau_srst(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.mau_srst = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_mau_srst(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mau_srst;
}
GH_INLINE void GH_EPHY_set_RST_EN_pls_srst(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.pls_srst = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_pls_srst(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pls_srst;
}
GH_INLINE void GH_EPHY_set_RST_EN_sqe_test_enable(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.sqe_test_enable = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_sqe_test_enable(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sqe_test_enable;
}
GH_INLINE void GH_EPHY_set_RST_EN_lpbk_enable(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.lpbk_enable = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_lpbk_enable(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lpbk_enable;
}
GH_INLINE void GH_EPHY_set_RST_EN_jabber_enable(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.jabber_enable = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_jabber_enable(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.jabber_enable;
}
GH_INLINE void GH_EPHY_set_RST_EN_ser_polarity_correction(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.ser_polarity_correction = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_ser_polarity_correction(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ser_polarity_correction;
}
GH_INLINE void GH_EPHY_set_RST_EN_por_stick_mode(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.por_stick_mode = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_por_stick_mode(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.por_stick_mode;
}
GH_INLINE void GH_EPHY_set_RST_EN_recv_bit_bucket(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.recv_bit_bucket = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_recv_bit_bucket(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.recv_bit_bucket;
}
GH_INLINE void GH_EPHY_set_RST_EN_rxclk_pol(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.rxclk_pol = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_rxclk_pol(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxclk_pol;
}
GH_INLINE void GH_EPHY_set_RST_EN_txclk_pol(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.txclk_pol = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_txclk_pol(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txclk_pol;
}
GH_INLINE void GH_EPHY_set_RST_EN_adc_input_sign(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.adc_input_sign = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_adc_input_sign(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_input_sign;
}
GH_INLINE void GH_EPHY_set_RST_EN_mii_test_packet(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.mii_test_packet = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_mii_test_packet(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_test_packet;
}
GH_INLINE void GH_EPHY_set_RST_EN_clear_rcvpack(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.clear_rcvpack = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_clear_rcvpack(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clear_rcvpack;
}
GH_INLINE void GH_EPHY_set_RST_EN_miiloop_en_10m(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.miiloop_en_10m = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_miiloop_en_10m(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.miiloop_en_10m;
}
GH_INLINE void GH_EPHY_set_RST_EN_mii_rxclk_pol(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.mii_rxclk_pol = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_mii_rxclk_pol(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_rxclk_pol;
}
GH_INLINE void GH_EPHY_set_RST_EN_mii_txclk_pol(U8 data)
{
    GH_EPHY_RST_EN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RST_EN_REAL;
    d.bitc.mii_txclk_pol = data;
    *(volatile U16 *)REG_EPHY_RST_EN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RST_EN_mii_txclk_pol(void)
{
    GH_EPHY_RST_EN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RST_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mii_txclk_pol;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_SNR_K (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_SNR_K(U16 data)
{
    GH_EPHY_SNR_K_REAL_S real;
    GH_EPHY_SNR_K_S dummy;
    dummy.all = data ;
    real.bitc.slice_up = dummy.bitc.slice_up;
    real.bitc.snrchk_k1 = dummy.bitc.snrchk_k1;
    real.bitc.snrchk_k2 = dummy.bitc.snrchk_k2;
    real.bitc.snrchk_k3 = dummy.bitc.snrchk_k3;
    real.bitc.gcr_ccpl_master_coarse_clkcc = dummy.bitc.gcr_ccpl_master_coarse_clkcc;
    *(volatile U16 *)REG_EPHY_SNR_K_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_SNR_K(void)
{
    GH_EPHY_SNR_K_REAL_S real;
    GH_EPHY_SNR_K_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_SNR_K_REAL);

    dummy.bitc.slice_up = real.bitc.slice_up;
    dummy.bitc.snrchk_k1 = real.bitc.snrchk_k1;
    dummy.bitc.snrchk_k2 = real.bitc.snrchk_k2;
    dummy.bitc.snrchk_k3 = real.bitc.snrchk_k3;
    dummy.bitc.gcr_ccpl_master_coarse_clkcc = real.bitc.gcr_ccpl_master_coarse_clkcc;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_SNR_K_slice_up(U8 data)
{
    GH_EPHY_SNR_K_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K_REAL;
    d.bitc.slice_up = data;
    *(volatile U16 *)REG_EPHY_SNR_K_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_K_slice_up(void)
{
    GH_EPHY_SNR_K_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.slice_up;
}
GH_INLINE void GH_EPHY_set_SNR_K_snrchk_k1(U8 data)
{
    GH_EPHY_SNR_K_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K_REAL;
    d.bitc.snrchk_k1 = data;
    *(volatile U16 *)REG_EPHY_SNR_K_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_K_snrchk_k1(void)
{
    GH_EPHY_SNR_K_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.snrchk_k1;
}
GH_INLINE void GH_EPHY_set_SNR_K_snrchk_k2(U8 data)
{
    GH_EPHY_SNR_K_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K_REAL;
    d.bitc.snrchk_k2 = data;
    *(volatile U16 *)REG_EPHY_SNR_K_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_K_snrchk_k2(void)
{
    GH_EPHY_SNR_K_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.snrchk_k2;
}
GH_INLINE void GH_EPHY_set_SNR_K_snrchk_k3(U8 data)
{
    GH_EPHY_SNR_K_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K_REAL;
    d.bitc.snrchk_k3 = data;
    *(volatile U16 *)REG_EPHY_SNR_K_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_K_snrchk_k3(void)
{
    GH_EPHY_SNR_K_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.snrchk_k3;
}
GH_INLINE void GH_EPHY_set_SNR_K_gcr_ccpl_master_coarse_clkcc(U8 data)
{
    GH_EPHY_SNR_K_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_K_REAL;
    d.bitc.gcr_ccpl_master_coarse_clkcc = data;
    *(volatile U16 *)REG_EPHY_SNR_K_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_K_gcr_ccpl_master_coarse_clkcc(void)
{
    GH_EPHY_SNR_K_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_K_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gcr_ccpl_master_coarse_clkcc;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_DET_MAX (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_DET_MAX(U16 data)
{
    GH_EPHY_DET_MAX_REAL_S real;
    GH_EPHY_DET_MAX_S dummy;
    dummy.all = data ;
    real.bitc.thrh_max_vga_coarse = dummy.bitc.thrh_max_vga_coarse;
    real.bitc.thrh_max_sig_det = dummy.bitc.thrh_max_sig_det;
    *(volatile U16 *)REG_EPHY_DET_MAX_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_DET_MAX(void)
{
    GH_EPHY_DET_MAX_REAL_S real;
    GH_EPHY_DET_MAX_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_DET_MAX_REAL);

    dummy.bitc.thrh_max_vga_coarse = real.bitc.thrh_max_vga_coarse;
    dummy.bitc.thrh_max_sig_det = real.bitc.thrh_max_sig_det;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_DET_MAX_thrh_max_vga_coarse(U8 data)
{
    GH_EPHY_DET_MAX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DET_MAX_REAL;
    d.bitc.thrh_max_vga_coarse = data;
    *(volatile U16 *)REG_EPHY_DET_MAX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DET_MAX_thrh_max_vga_coarse(void)
{
    GH_EPHY_DET_MAX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MAX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.thrh_max_vga_coarse;
}
GH_INLINE void GH_EPHY_set_DET_MAX_thrh_max_sig_det(U8 data)
{
    GH_EPHY_DET_MAX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DET_MAX_REAL;
    d.bitc.thrh_max_sig_det = data;
    *(volatile U16 *)REG_EPHY_DET_MAX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DET_MAX_thrh_max_sig_det(void)
{
    GH_EPHY_DET_MAX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MAX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.thrh_max_sig_det;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_DET_MIN (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_DET_MIN(U16 data)
{
    GH_EPHY_DET_MIN_REAL_S real;
    GH_EPHY_DET_MIN_S dummy;
    dummy.all = data ;
    real.bitc.thrh_max_vga_fine = dummy.bitc.thrh_max_vga_fine;
    real.bitc.thrh_min_sig_det = dummy.bitc.thrh_min_sig_det;
    *(volatile U16 *)REG_EPHY_DET_MIN_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_DET_MIN(void)
{
    GH_EPHY_DET_MIN_REAL_S real;
    GH_EPHY_DET_MIN_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_DET_MIN_REAL);

    dummy.bitc.thrh_max_vga_fine = real.bitc.thrh_max_vga_fine;
    dummy.bitc.thrh_min_sig_det = real.bitc.thrh_min_sig_det;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_DET_MIN_thrh_max_vga_fine(U8 data)
{
    GH_EPHY_DET_MIN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DET_MIN_REAL;
    d.bitc.thrh_max_vga_fine = data;
    *(volatile U16 *)REG_EPHY_DET_MIN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DET_MIN_thrh_max_vga_fine(void)
{
    GH_EPHY_DET_MIN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MIN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.thrh_max_vga_fine;
}
GH_INLINE void GH_EPHY_set_DET_MIN_thrh_min_sig_det(U8 data)
{
    GH_EPHY_DET_MIN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_DET_MIN_REAL;
    d.bitc.thrh_min_sig_det = data;
    *(volatile U16 *)REG_EPHY_DET_MIN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_DET_MIN_thrh_min_sig_det(void)
{
    GH_EPHY_DET_MIN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_DET_MIN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.thrh_min_sig_det;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_SNR_LEN (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_SNR_LEN(U16 data)
{
    GH_EPHY_SNR_LEN_REAL_S real;
    GH_EPHY_SNR_LEN_S dummy;
    dummy.all = data ;
    real.bitc.mcu_ctrl_dsp_fsm_state = dummy.bitc.mcu_ctrl_dsp_fsm_state;
    real.bitc.force_100m_en = dummy.bitc.force_100m_en;
    real.bitc.force_100m_snr_lock = dummy.bitc.force_100m_snr_lock;
    real.bitc.dsp_fsm_agc_en_mode_a = dummy.bitc.dsp_fsm_agc_en_mode_a;
    real.bitc.cable_len_offset = dummy.bitc.cable_len_offset;
    *(volatile U16 *)REG_EPHY_SNR_LEN_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_SNR_LEN(void)
{
    GH_EPHY_SNR_LEN_REAL_S real;
    GH_EPHY_SNR_LEN_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_SNR_LEN_REAL);

    dummy.bitc.mcu_ctrl_dsp_fsm_state = real.bitc.mcu_ctrl_dsp_fsm_state;
    dummy.bitc.force_100m_en = real.bitc.force_100m_en;
    dummy.bitc.force_100m_snr_lock = real.bitc.force_100m_snr_lock;
    dummy.bitc.dsp_fsm_agc_en_mode_a = real.bitc.dsp_fsm_agc_en_mode_a;
    dummy.bitc.cable_len_offset = real.bitc.cable_len_offset;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_mcu_ctrl_dsp_fsm_state(U8 data)
{
    GH_EPHY_SNR_LEN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN_REAL;
    d.bitc.mcu_ctrl_dsp_fsm_state = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_mcu_ctrl_dsp_fsm_state(void)
{
    GH_EPHY_SNR_LEN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mcu_ctrl_dsp_fsm_state;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_force_100m_en(U8 data)
{
    GH_EPHY_SNR_LEN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN_REAL;
    d.bitc.force_100m_en = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_force_100m_en(void)
{
    GH_EPHY_SNR_LEN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.force_100m_en;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_force_100m_snr_lock(U8 data)
{
    GH_EPHY_SNR_LEN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN_REAL;
    d.bitc.force_100m_snr_lock = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_force_100m_snr_lock(void)
{
    GH_EPHY_SNR_LEN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.force_100m_snr_lock;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_dsp_fsm_agc_en_mode_a(U8 data)
{
    GH_EPHY_SNR_LEN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN_REAL;
    d.bitc.dsp_fsm_agc_en_mode_a = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_dsp_fsm_agc_en_mode_a(void)
{
    GH_EPHY_SNR_LEN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsp_fsm_agc_en_mode_a;
}
GH_INLINE void GH_EPHY_set_SNR_LEN_cable_len_offset(U8 data)
{
    GH_EPHY_SNR_LEN_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_SNR_LEN_REAL;
    d.bitc.cable_len_offset = data;
    *(volatile U16 *)REG_EPHY_SNR_LEN_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_SNR_LEN_cable_len_offset(void)
{
    GH_EPHY_SNR_LEN_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_SNR_LEN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cable_len_offset;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_LPF (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_LPF(U16 data)
{
    GH_EPHY_LPF_REAL_S real;
    GH_EPHY_LPF_S dummy;
    dummy.all = data ;
    real.bitc.lpf_out_h = dummy.bitc.lpf_out_h;
    real.bitc.rxlpf_bwsel_10t = dummy.bitc.rxlpf_bwsel_10t;
    real.bitc.rxlpf_bwsel_100t = dummy.bitc.rxlpf_bwsel_100t;
    real.bitc.cable_length = dummy.bitc.cable_length;
    *(volatile U16 *)REG_EPHY_LPF_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_LPF(void)
{
    GH_EPHY_LPF_REAL_S real;
    GH_EPHY_LPF_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_LPF_REAL);

    dummy.bitc.lpf_out_h = real.bitc.lpf_out_h;
    dummy.bitc.rxlpf_bwsel_10t = real.bitc.rxlpf_bwsel_10t;
    dummy.bitc.rxlpf_bwsel_100t = real.bitc.rxlpf_bwsel_100t;
    dummy.bitc.cable_length = real.bitc.cable_length;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_LPF_lpf_out_h(U16 data)
{
    GH_EPHY_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_LPF_REAL;
    d.bitc.lpf_out_h = data;
    *(volatile U16 *)REG_EPHY_LPF_REAL = d.all;
}
GH_INLINE U16  GH_EPHY_get_LPF_lpf_out_h(void)
{
    GH_EPHY_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lpf_out_h;
}
GH_INLINE void GH_EPHY_set_LPF_rxlpf_bwsel_10t(U8 data)
{
    GH_EPHY_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_LPF_REAL;
    d.bitc.rxlpf_bwsel_10t = data;
    *(volatile U16 *)REG_EPHY_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_LPF_rxlpf_bwsel_10t(void)
{
    GH_EPHY_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxlpf_bwsel_10t;
}
GH_INLINE void GH_EPHY_set_LPF_rxlpf_bwsel_100t(U8 data)
{
    GH_EPHY_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_LPF_REAL;
    d.bitc.rxlpf_bwsel_100t = data;
    *(volatile U16 *)REG_EPHY_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_LPF_rxlpf_bwsel_100t(void)
{
    GH_EPHY_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxlpf_bwsel_100t;
}
GH_INLINE void GH_EPHY_set_LPF_cable_length(U8 data)
{
    GH_EPHY_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_LPF_REAL;
    d.bitc.cable_length = data;
    *(volatile U16 *)REG_EPHY_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_LPF_cable_length(void)
{
    GH_EPHY_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cable_length;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ADC_GAIN_PGA (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA(U16 data)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S real;
    GH_EPHY_ADC_GAIN_PGA_S dummy;
    dummy.all = data ;
    real.bitc.adc_bp = dummy.bitc.adc_bp;
    real.bitc.dac10t_testen = dummy.bitc.dac10t_testen;
    real.bitc.dac100t_testen = dummy.bitc.dac100t_testen;
    real.bitc.adc_bma = dummy.bitc.adc_bma;
    real.bitc.adc_pd = dummy.bitc.adc_pd;
    real.bitc.region_bank_rd = dummy.bitc.region_bank_rd;
    real.bitc.adcpll_ana_clken = dummy.bitc.adcpll_ana_clken;
    real.bitc.adcbin_testen = dummy.bitc.adcbin_testen;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_ADC_GAIN_PGA(void)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S real;
    GH_EPHY_ADC_GAIN_PGA_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL);

    dummy.bitc.adc_bp = real.bitc.adc_bp;
    dummy.bitc.dac10t_testen = real.bitc.dac10t_testen;
    dummy.bitc.dac100t_testen = real.bitc.dac100t_testen;
    dummy.bitc.adc_bma = real.bitc.adc_bma;
    dummy.bitc.adc_pd = real.bitc.adc_pd;
    dummy.bitc.region_bank_rd = real.bitc.region_bank_rd;
    dummy.bitc.adcpll_ana_clken = real.bitc.adcpll_ana_clken;
    dummy.bitc.adcbin_testen = real.bitc.adcbin_testen;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adc_bp(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL;
    d.bitc.adc_bp = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adc_bp(void)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_bp;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_dac10t_testen(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL;
    d.bitc.dac10t_testen = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_dac10t_testen(void)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dac10t_testen;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_dac100t_testen(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL;
    d.bitc.dac100t_testen = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_dac100t_testen(void)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dac100t_testen;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adc_bma(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL;
    d.bitc.adc_bma = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adc_bma(void)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_bma;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adc_pd(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL;
    d.bitc.adc_pd = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adc_pd(void)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_pd;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_region_bank_rd(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL;
    d.bitc.region_bank_rd = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_region_bank_rd(void)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.region_bank_rd;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adcpll_ana_clken(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL;
    d.bitc.adcpll_ana_clken = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adcpll_ana_clken(void)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcpll_ana_clken;
}
GH_INLINE void GH_EPHY_set_ADC_GAIN_PGA_adcbin_testen(U8 data)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL;
    d.bitc.adcbin_testen = data;
    *(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GAIN_PGA_adcbin_testen(void)
{
    GH_EPHY_ADC_GAIN_PGA_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GAIN_PGA_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcbin_testen;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ADC_GSHIFT (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_ADC_GSHIFT(U16 data)
{
    GH_EPHY_ADC_GSHIFT_REAL_S real;
    GH_EPHY_ADC_GSHIFT_S dummy;
    dummy.all = data ;
    real.bitc.adc_gshift = dummy.bitc.adc_gshift;
    real.bitc.gain = dummy.bitc.gain;
    *(volatile U16 *)REG_EPHY_ADC_GSHIFT_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_ADC_GSHIFT(void)
{
    GH_EPHY_ADC_GSHIFT_REAL_S real;
    GH_EPHY_ADC_GSHIFT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ADC_GSHIFT_REAL);

    dummy.bitc.adc_gshift = real.bitc.adc_gshift;
    dummy.bitc.gain = real.bitc.gain;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_ADC_GSHIFT_adc_gshift(U8 data)
{
    GH_EPHY_ADC_GSHIFT_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GSHIFT_REAL;
    d.bitc.adc_gshift = data;
    *(volatile U16 *)REG_EPHY_ADC_GSHIFT_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GSHIFT_adc_gshift(void)
{
    GH_EPHY_ADC_GSHIFT_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GSHIFT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_gshift;
}
GH_INLINE void GH_EPHY_set_ADC_GSHIFT_gain(U8 data)
{
    GH_EPHY_ADC_GSHIFT_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_GSHIFT_REAL;
    d.bitc.gain = data;
    *(volatile U16 *)REG_EPHY_ADC_GSHIFT_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_GSHIFT_gain(void)
{
    GH_EPHY_ADC_GSHIFT_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_GSHIFT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gain;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ADC (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_ADC(U16 data)
{
    GH_EPHY_ADC_REAL_S real;
    GH_EPHY_ADC_S dummy;
    dummy.all = data ;
    real.bitc.adc_bp = dummy.bitc.adc_bp;
    real.bitc.dac10t_testen = dummy.bitc.dac10t_testen;
    real.bitc.reg_dac100t_testen = dummy.bitc.reg_dac100t_testen;
    real.bitc.adc_bma = dummy.bitc.adc_bma;
    real.bitc.adc_pd = dummy.bitc.adc_pd;
    real.bitc.region_bank_rd = dummy.bitc.region_bank_rd;
    real.bitc.adcpll_ana_clken = dummy.bitc.adcpll_ana_clken;
    real.bitc.adcbin_testen = dummy.bitc.adcbin_testen;
    *(volatile U16 *)REG_EPHY_ADC_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_ADC(void)
{
    GH_EPHY_ADC_REAL_S real;
    GH_EPHY_ADC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ADC_REAL);

    dummy.bitc.adc_bp = real.bitc.adc_bp;
    dummy.bitc.dac10t_testen = real.bitc.dac10t_testen;
    dummy.bitc.reg_dac100t_testen = real.bitc.reg_dac100t_testen;
    dummy.bitc.adc_bma = real.bitc.adc_bma;
    dummy.bitc.adc_pd = real.bitc.adc_pd;
    dummy.bitc.region_bank_rd = real.bitc.region_bank_rd;
    dummy.bitc.adcpll_ana_clken = real.bitc.adcpll_ana_clken;
    dummy.bitc.adcbin_testen = real.bitc.adcbin_testen;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_ADC_adc_bp(U8 data)
{
    GH_EPHY_ADC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_REAL;
    d.bitc.adc_bp = data;
    *(volatile U16 *)REG_EPHY_ADC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_adc_bp(void)
{
    GH_EPHY_ADC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_bp;
}
GH_INLINE void GH_EPHY_set_ADC_dac10t_testen(U8 data)
{
    GH_EPHY_ADC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_REAL;
    d.bitc.dac10t_testen = data;
    *(volatile U16 *)REG_EPHY_ADC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_dac10t_testen(void)
{
    GH_EPHY_ADC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dac10t_testen;
}
GH_INLINE void GH_EPHY_set_ADC_reg_dac100t_testen(U8 data)
{
    GH_EPHY_ADC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_REAL;
    d.bitc.reg_dac100t_testen = data;
    *(volatile U16 *)REG_EPHY_ADC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_reg_dac100t_testen(void)
{
    GH_EPHY_ADC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reg_dac100t_testen;
}
GH_INLINE void GH_EPHY_set_ADC_adc_bma(U8 data)
{
    GH_EPHY_ADC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_REAL;
    d.bitc.adc_bma = data;
    *(volatile U16 *)REG_EPHY_ADC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_adc_bma(void)
{
    GH_EPHY_ADC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_bma;
}
GH_INLINE void GH_EPHY_set_ADC_adc_pd(U8 data)
{
    GH_EPHY_ADC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_REAL;
    d.bitc.adc_pd = data;
    *(volatile U16 *)REG_EPHY_ADC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_adc_pd(void)
{
    GH_EPHY_ADC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_pd;
}
GH_INLINE void GH_EPHY_set_ADC_region_bank_rd(U8 data)
{
    GH_EPHY_ADC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_REAL;
    d.bitc.region_bank_rd = data;
    *(volatile U16 *)REG_EPHY_ADC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_region_bank_rd(void)
{
    GH_EPHY_ADC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.region_bank_rd;
}
GH_INLINE void GH_EPHY_set_ADC_adcpll_ana_clken(U8 data)
{
    GH_EPHY_ADC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_REAL;
    d.bitc.adcpll_ana_clken = data;
    *(volatile U16 *)REG_EPHY_ADC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_adcpll_ana_clken(void)
{
    GH_EPHY_ADC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcpll_ana_clken;
}
GH_INLINE void GH_EPHY_set_ADC_adcbin_testen(U8 data)
{
    GH_EPHY_ADC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_REAL;
    d.bitc.adcbin_testen = data;
    *(volatile U16 *)REG_EPHY_ADC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_adcbin_testen(void)
{
    GH_EPHY_ADC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcbin_testen;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_PLL_ADC_CTRL3 (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL3(U16 data)
{
    GH_EPHY_PLL_ADC_CTRL3_REAL_S real;
    GH_EPHY_PLL_ADC_CTRL3_S dummy;
    dummy.all = data ;
    real.bitc.rxlpf_pd = dummy.bitc.rxlpf_pd;
    real.bitc.tx_b_test = dummy.bitc.tx_b_test;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_PLL_ADC_CTRL3(void)
{
    GH_EPHY_PLL_ADC_CTRL3_REAL_S real;
    GH_EPHY_PLL_ADC_CTRL3_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3_REAL);

    dummy.bitc.rxlpf_pd = real.bitc.rxlpf_pd;
    dummy.bitc.tx_b_test = real.bitc.tx_b_test;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL3_rxlpf_pd(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL3_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3_REAL;
    d.bitc.rxlpf_pd = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL3_rxlpf_pd(void)
{
    GH_EPHY_PLL_ADC_CTRL3_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxlpf_pd;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL3_tx_b_test(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL3_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3_REAL;
    d.bitc.tx_b_test = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL3_tx_b_test(void)
{
    GH_EPHY_PLL_ADC_CTRL3_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL3_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tx_b_test;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_RX_LPF (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_RX_LPF(U16 data)
{
    GH_EPHY_RX_LPF_REAL_S real;
    GH_EPHY_RX_LPF_S dummy;
    dummy.all = data ;
    real.bitc.rxlpf_ibsel = dummy.bitc.rxlpf_ibsel;
    real.bitc.rxlpf_bwsel = dummy.bitc.rxlpf_bwsel;
    real.bitc.unkown = dummy.bitc.unkown;
    real.bitc.rxlpf_cmsel = dummy.bitc.rxlpf_cmsel;
    real.bitc.rxlpf_outp_test = dummy.bitc.rxlpf_outp_test;
    real.bitc.rxlpf_outm_test = dummy.bitc.rxlpf_outm_test;
    real.bitc.rxlpf_bypass = dummy.bitc.rxlpf_bypass;
    real.bitc.ref_pd = dummy.bitc.ref_pd;
    real.bitc.ref_iint_pd = dummy.bitc.ref_iint_pd;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_RX_LPF(void)
{
    GH_EPHY_RX_LPF_REAL_S real;
    GH_EPHY_RX_LPF_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    dummy.bitc.rxlpf_ibsel = real.bitc.rxlpf_ibsel;
    dummy.bitc.rxlpf_bwsel = real.bitc.rxlpf_bwsel;
    dummy.bitc.unkown = real.bitc.unkown;
    dummy.bitc.rxlpf_cmsel = real.bitc.rxlpf_cmsel;
    dummy.bitc.rxlpf_outp_test = real.bitc.rxlpf_outp_test;
    dummy.bitc.rxlpf_outm_test = real.bitc.rxlpf_outm_test;
    dummy.bitc.rxlpf_bypass = real.bitc.rxlpf_bypass;
    dummy.bitc.ref_pd = real.bitc.ref_pd;
    dummy.bitc.ref_iint_pd = real.bitc.ref_iint_pd;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_ibsel(U8 data)
{
    GH_EPHY_RX_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF_REAL;
    d.bitc.rxlpf_ibsel = data;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_ibsel(void)
{
    GH_EPHY_RX_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxlpf_ibsel;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_bwsel(U8 data)
{
    GH_EPHY_RX_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF_REAL;
    d.bitc.rxlpf_bwsel = data;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_bwsel(void)
{
    GH_EPHY_RX_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxlpf_bwsel;
}
GH_INLINE void GH_EPHY_set_RX_LPF_unkown(U8 data)
{
    GH_EPHY_RX_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF_REAL;
    d.bitc.unkown = data;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_unkown(void)
{
    GH_EPHY_RX_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.unkown;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_cmsel(U8 data)
{
    GH_EPHY_RX_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF_REAL;
    d.bitc.rxlpf_cmsel = data;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_cmsel(void)
{
    GH_EPHY_RX_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxlpf_cmsel;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_outp_test(U8 data)
{
    GH_EPHY_RX_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF_REAL;
    d.bitc.rxlpf_outp_test = data;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_outp_test(void)
{
    GH_EPHY_RX_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxlpf_outp_test;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_outm_test(U8 data)
{
    GH_EPHY_RX_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF_REAL;
    d.bitc.rxlpf_outm_test = data;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_outm_test(void)
{
    GH_EPHY_RX_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxlpf_outm_test;
}
GH_INLINE void GH_EPHY_set_RX_LPF_rxlpf_bypass(U8 data)
{
    GH_EPHY_RX_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF_REAL;
    d.bitc.rxlpf_bypass = data;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_rxlpf_bypass(void)
{
    GH_EPHY_RX_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rxlpf_bypass;
}
GH_INLINE void GH_EPHY_set_RX_LPF_ref_pd(U8 data)
{
    GH_EPHY_RX_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF_REAL;
    d.bitc.ref_pd = data;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_ref_pd(void)
{
    GH_EPHY_RX_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ref_pd;
}
GH_INLINE void GH_EPHY_set_RX_LPF_ref_iint_pd(U8 data)
{
    GH_EPHY_RX_LPF_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_RX_LPF_REAL;
    d.bitc.ref_iint_pd = data;
    *(volatile U16 *)REG_EPHY_RX_LPF_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_RX_LPF_ref_iint_pd(void)
{
    GH_EPHY_RX_LPF_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_RX_LPF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ref_iint_pd;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_PLL_ADC_CTRL0 (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0(U16 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S real;
    GH_EPHY_PLL_ADC_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.ro_adcpl_lock = dummy.bitc.ro_adcpl_lock;
    real.bitc.gcr_adcpl_div = dummy.bitc.gcr_adcpl_div;
    real.bitc.test_adcpl_extcksel = dummy.bitc.test_adcpl_extcksel;
    real.bitc.ro_adcpl_high_flag = dummy.bitc.ro_adcpl_high_flag;
    real.bitc.pllclk_outen = dummy.bitc.pllclk_outen;
    real.bitc.ov_ref_test = dummy.bitc.ov_ref_test;
    real.bitc.gc_adcpl_rstb = dummy.bitc.gc_adcpl_rstb;
    real.bitc.ref_bgap_pd = dummy.bitc.ref_bgap_pd;
    real.bitc.adcraw_tst = dummy.bitc.adcraw_tst;
    real.bitc.adcraw_tst_sw = dummy.bitc.adcraw_tst_sw;
    real.bitc.ldo_pwrgd = dummy.bitc.ldo_pwrgd;
    real.bitc.adcraw_overflow = dummy.bitc.adcraw_overflow;
    real.bitc.adcpl_force_phase = dummy.bitc.adcpl_force_phase;
    real.bitc.gcr_adcpl_tog_clkcc = dummy.bitc.gcr_adcpl_tog_clkcc;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_PLL_ADC_CTRL0(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S real;
    GH_EPHY_PLL_ADC_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    dummy.bitc.ro_adcpl_lock = real.bitc.ro_adcpl_lock;
    dummy.bitc.gcr_adcpl_div = real.bitc.gcr_adcpl_div;
    dummy.bitc.test_adcpl_extcksel = real.bitc.test_adcpl_extcksel;
    dummy.bitc.ro_adcpl_high_flag = real.bitc.ro_adcpl_high_flag;
    dummy.bitc.pllclk_outen = real.bitc.pllclk_outen;
    dummy.bitc.ov_ref_test = real.bitc.ov_ref_test;
    dummy.bitc.gc_adcpl_rstb = real.bitc.gc_adcpl_rstb;
    dummy.bitc.ref_bgap_pd = real.bitc.ref_bgap_pd;
    dummy.bitc.adcraw_tst = real.bitc.adcraw_tst;
    dummy.bitc.adcraw_tst_sw = real.bitc.adcraw_tst_sw;
    dummy.bitc.ldo_pwrgd = real.bitc.ldo_pwrgd;
    dummy.bitc.adcraw_overflow = real.bitc.adcraw_overflow;
    dummy.bitc.adcpl_force_phase = real.bitc.adcpl_force_phase;
    dummy.bitc.gcr_adcpl_tog_clkcc = real.bitc.gcr_adcpl_tog_clkcc;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_lock(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.ro_adcpl_lock = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ro_adcpl_lock(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ro_adcpl_lock;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_div(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.gcr_adcpl_div = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_gcr_adcpl_div(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gcr_adcpl_div;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_test_adcpl_extcksel(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.test_adcpl_extcksel = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_test_adcpl_extcksel(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.test_adcpl_extcksel;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ro_adcpl_high_flag(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.ro_adcpl_high_flag = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ro_adcpl_high_flag(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ro_adcpl_high_flag;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_pllclk_outen(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.pllclk_outen = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_pllclk_outen(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pllclk_outen;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ov_ref_test(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.ov_ref_test = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ov_ref_test(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ov_ref_test;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_gc_adcpl_rstb(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.gc_adcpl_rstb = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_gc_adcpl_rstb(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_adcpl_rstb;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ref_bgap_pd(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.ref_bgap_pd = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ref_bgap_pd(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ref_bgap_pd;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.adcraw_tst = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_adcraw_tst(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcraw_tst;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_adcraw_tst_sw(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.adcraw_tst_sw = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_adcraw_tst_sw(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcraw_tst_sw;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_ldo_pwrgd(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.ldo_pwrgd = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_ldo_pwrgd(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ldo_pwrgd;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_adcraw_overflow(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.adcraw_overflow = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_adcraw_overflow(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcraw_overflow;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_adcpl_force_phase(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.adcpl_force_phase = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_adcpl_force_phase(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcpl_force_phase;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL0_gcr_adcpl_tog_clkcc(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL;
    d.bitc.gcr_adcpl_tog_clkcc = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL0_gcr_adcpl_tog_clkcc(void)
{
    GH_EPHY_PLL_ADC_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gcr_adcpl_tog_clkcc;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_PLL_ADC_CTRL1 (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1(U16 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S real;
    GH_EPHY_PLL_ADC_CTRL1_S dummy;
    dummy.all = data ;
    real.bitc.gc_adcpl_adcpd0 = dummy.bitc.gc_adcpl_adcpd0;
    real.bitc.gc_adcpl_adcpd1 = dummy.bitc.gc_adcpl_adcpd1;
    real.bitc.gc_adcpl_ccpd0 = dummy.bitc.gc_adcpl_ccpd0;
    real.bitc.gc_adcpl_ccpd1 = dummy.bitc.gc_adcpl_ccpd1;
    real.bitc.pd_adcpl_reg = dummy.bitc.pd_adcpl_reg;
    real.bitc.gcr_adcpl_mod_100t = dummy.bitc.gcr_adcpl_mod_100t;
    real.bitc.gcr_adcpl_ictrl = dummy.bitc.gcr_adcpl_ictrl;
    real.bitc.gcr_adcpl_enfrunz = dummy.bitc.gcr_adcpl_enfrunz;
    real.bitc.en_adcpl_porst = dummy.bitc.en_adcpl_porst;
    real.bitc.en_adcpl_adcphdac = dummy.bitc.en_adcpl_adcphdac;
    real.bitc.gc_adcpl_adcselect = dummy.bitc.gc_adcpl_adcselect;
    real.bitc.tx_d_test = dummy.bitc.tx_d_test;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_PLL_ADC_CTRL1(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S real;
    GH_EPHY_PLL_ADC_CTRL1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    dummy.bitc.gc_adcpl_adcpd0 = real.bitc.gc_adcpl_adcpd0;
    dummy.bitc.gc_adcpl_adcpd1 = real.bitc.gc_adcpl_adcpd1;
    dummy.bitc.gc_adcpl_ccpd0 = real.bitc.gc_adcpl_ccpd0;
    dummy.bitc.gc_adcpl_ccpd1 = real.bitc.gc_adcpl_ccpd1;
    dummy.bitc.pd_adcpl_reg = real.bitc.pd_adcpl_reg;
    dummy.bitc.gcr_adcpl_mod_100t = real.bitc.gcr_adcpl_mod_100t;
    dummy.bitc.gcr_adcpl_ictrl = real.bitc.gcr_adcpl_ictrl;
    dummy.bitc.gcr_adcpl_enfrunz = real.bitc.gcr_adcpl_enfrunz;
    dummy.bitc.en_adcpl_porst = real.bitc.en_adcpl_porst;
    dummy.bitc.en_adcpl_adcphdac = real.bitc.en_adcpl_adcphdac;
    dummy.bitc.gc_adcpl_adcselect = real.bitc.gc_adcpl_adcselect;
    dummy.bitc.tx_d_test = real.bitc.tx_d_test;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd0(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.gc_adcpl_adcpd0 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcpd0(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_adcpl_adcpd0;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcpd1(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.gc_adcpl_adcpd1 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcpd1(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_adcpl_adcpd1;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd0(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.gc_adcpl_ccpd0 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_ccpd0(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_adcpl_ccpd0;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_ccpd1(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.gc_adcpl_ccpd1 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_ccpd1(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_adcpl_ccpd1;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_pd_adcpl_reg(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.pd_adcpl_reg = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_pd_adcpl_reg(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_adcpl_reg;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_mod_100t(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.gcr_adcpl_mod_100t = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_mod_100t(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gcr_adcpl_mod_100t;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_ictrl(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.gcr_adcpl_ictrl = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_ictrl(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gcr_adcpl_ictrl;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gcr_adcpl_enfrunz(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.gcr_adcpl_enfrunz = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gcr_adcpl_enfrunz(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gcr_adcpl_enfrunz;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_porst(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.en_adcpl_porst = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_en_adcpl_porst(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_adcpl_porst;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_en_adcpl_adcphdac(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.en_adcpl_adcphdac = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_en_adcpl_adcphdac(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_adcpl_adcphdac;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_gc_adcpl_adcselect(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.gc_adcpl_adcselect = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_gc_adcpl_adcselect(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_adcpl_adcselect;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL1_tx_d_test(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL;
    d.bitc.tx_d_test = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL1_tx_d_test(void)
{
    GH_EPHY_PLL_ADC_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tx_d_test;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_PLL_ADC_CTRL2 (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2(U16 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S real;
    GH_EPHY_PLL_ADC_CTRL2_S dummy;
    dummy.all = data ;
    real.bitc.gc_ref_vgen = dummy.bitc.gc_ref_vgen;
    real.bitc.gc_ref_vcom = dummy.bitc.gc_ref_vcom;
    real.bitc.gc_ref_vcmpcmvx = dummy.bitc.gc_ref_vcmpcmvx;
    real.bitc.pd_lpf_op = dummy.bitc.pd_lpf_op;
    real.bitc.gc_adc_force1 = dummy.bitc.gc_adc_force1;
    real.bitc.gc_adc_force0 = dummy.bitc.gc_adc_force0;
    real.bitc.endiscz_10 = dummy.bitc.endiscz_10;
    real.bitc.gcr_adcpl_pdphadc = dummy.bitc.gcr_adcpl_pdphadc;
    real.bitc.adcpl_bank = dummy.bitc.adcpl_bank;
    real.bitc.adcpl_phase_force = dummy.bitc.adcpl_phase_force;
    real.bitc.adcpl_phase_force_st = dummy.bitc.adcpl_phase_force_st;
    real.bitc.adcpl_force_go = dummy.bitc.adcpl_force_go;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_PLL_ADC_CTRL2(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S real;
    GH_EPHY_PLL_ADC_CTRL2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    dummy.bitc.gc_ref_vgen = real.bitc.gc_ref_vgen;
    dummy.bitc.gc_ref_vcom = real.bitc.gc_ref_vcom;
    dummy.bitc.gc_ref_vcmpcmvx = real.bitc.gc_ref_vcmpcmvx;
    dummy.bitc.pd_lpf_op = real.bitc.pd_lpf_op;
    dummy.bitc.gc_adc_force1 = real.bitc.gc_adc_force1;
    dummy.bitc.gc_adc_force0 = real.bitc.gc_adc_force0;
    dummy.bitc.endiscz_10 = real.bitc.endiscz_10;
    dummy.bitc.gcr_adcpl_pdphadc = real.bitc.gcr_adcpl_pdphadc;
    dummy.bitc.adcpl_bank = real.bitc.adcpl_bank;
    dummy.bitc.adcpl_phase_force = real.bitc.adcpl_phase_force;
    dummy.bitc.adcpl_phase_force_st = real.bitc.adcpl_phase_force_st;
    dummy.bitc.adcpl_force_go = real.bitc.adcpl_force_go;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vgen(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.gc_ref_vgen = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vgen(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_ref_vgen;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcom(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.gc_ref_vcom = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vcom(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_ref_vcom;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_ref_vcmpcmvx(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.gc_ref_vcmpcmvx = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_ref_vcmpcmvx(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_ref_vcmpcmvx;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_pd_lpf_op(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.pd_lpf_op = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_pd_lpf_op(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_lpf_op;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force1(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.gc_adc_force1 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_adc_force1(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_adc_force1;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gc_adc_force0(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.gc_adc_force0 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gc_adc_force0(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gc_adc_force0;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_endiscz_10(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.endiscz_10 = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_endiscz_10(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.endiscz_10;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_gcr_adcpl_pdphadc(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.gcr_adcpl_pdphadc = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_gcr_adcpl_pdphadc(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gcr_adcpl_pdphadc;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_bank(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.adcpl_bank = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_bank(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcpl_bank;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.adcpl_phase_force = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_phase_force(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcpl_phase_force;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_phase_force_st(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.adcpl_phase_force_st = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_phase_force_st(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcpl_phase_force_st;
}
GH_INLINE void GH_EPHY_set_PLL_ADC_CTRL2_adcpl_force_go(U8 data)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL;
    d.bitc.adcpl_force_go = data;
    *(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PLL_ADC_CTRL2_adcpl_force_go(void)
{
    GH_EPHY_PLL_ADC_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PLL_ADC_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcpl_force_go;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_TEST_TX (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_TEST_TX(U16 data)
{
    *(volatile U16 *)REG_EPHY_TEST_TX_REAL = data;
}
GH_INLINE U16  GH_EPHY_get_TEST_TX(void)
{
    U16 value = (*(volatile U16 *)REG_EPHY_TEST_TX_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_PWR (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_PWR(U16 data)
{
    GH_EPHY_PWR_REAL_S real;
    GH_EPHY_PWR_S dummy;
    dummy.all = data ;
    real.bitc.pwr_k_in_lp = dummy.bitc.pwr_k_in_lp;
    real.bitc.dtpwr_enable_lp = dummy.bitc.dtpwr_enable_lp;
    real.bitc.gcr_adcpl_div_lp = dummy.bitc.gcr_adcpl_div_lp;
    real.bitc.dummy = dummy.bitc.dummy;
    *(volatile U16 *)REG_EPHY_PWR_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_PWR(void)
{
    GH_EPHY_PWR_REAL_S real;
    GH_EPHY_PWR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_PWR_REAL);

    dummy.bitc.pwr_k_in_lp = real.bitc.pwr_k_in_lp;
    dummy.bitc.dtpwr_enable_lp = real.bitc.dtpwr_enable_lp;
    dummy.bitc.gcr_adcpl_div_lp = real.bitc.gcr_adcpl_div_lp;
    dummy.bitc.dummy = real.bitc.dummy;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_PWR_pwr_k_in_lp(U8 data)
{
    GH_EPHY_PWR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PWR_REAL;
    d.bitc.pwr_k_in_lp = data;
    *(volatile U16 *)REG_EPHY_PWR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PWR_pwr_k_in_lp(void)
{
    GH_EPHY_PWR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PWR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pwr_k_in_lp;
}
GH_INLINE void GH_EPHY_set_PWR_dtpwr_enable_lp(U8 data)
{
    GH_EPHY_PWR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PWR_REAL;
    d.bitc.dtpwr_enable_lp = data;
    *(volatile U16 *)REG_EPHY_PWR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PWR_dtpwr_enable_lp(void)
{
    GH_EPHY_PWR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PWR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dtpwr_enable_lp;
}
GH_INLINE void GH_EPHY_set_PWR_gcr_adcpl_div_lp(U8 data)
{
    GH_EPHY_PWR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PWR_REAL;
    d.bitc.gcr_adcpl_div_lp = data;
    *(volatile U16 *)REG_EPHY_PWR_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_PWR_gcr_adcpl_div_lp(void)
{
    GH_EPHY_PWR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PWR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gcr_adcpl_div_lp;
}
GH_INLINE void GH_EPHY_set_PWR_dummy(U16 data)
{
    GH_EPHY_PWR_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_PWR_REAL;
    d.bitc.dummy = data;
    *(volatile U16 *)REG_EPHY_PWR_REAL = d.all;
}
GH_INLINE U16  GH_EPHY_get_PWR_dummy(void)
{
    GH_EPHY_PWR_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_PWR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dummy;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ADC_DC (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_ADC_DC(U16 data)
{
    GH_EPHY_ADC_DC_REAL_S real;
    GH_EPHY_ADC_DC_S dummy;
    dummy.all = data ;
    real.bitc.dc_force_en = dummy.bitc.dc_force_en;
    real.bitc.dc_force = dummy.bitc.dc_force;
    real.bitc.dc_can_inv = dummy.bitc.dc_can_inv;
    real.bitc.analog_blw = dummy.bitc.analog_blw;
    real.bitc.dc_k = dummy.bitc.dc_k;
    real.bitc.srst = dummy.bitc.srst;
    real.bitc.adc_cancel_out = dummy.bitc.adc_cancel_out;
    real.bitc.adc_cancel_disable = dummy.bitc.adc_cancel_disable;
    real.bitc.adc_start = dummy.bitc.adc_start;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_ADC_DC(void)
{
    GH_EPHY_ADC_DC_REAL_S real;
    GH_EPHY_ADC_DC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    dummy.bitc.dc_force_en = real.bitc.dc_force_en;
    dummy.bitc.dc_force = real.bitc.dc_force;
    dummy.bitc.dc_can_inv = real.bitc.dc_can_inv;
    dummy.bitc.analog_blw = real.bitc.analog_blw;
    dummy.bitc.dc_k = real.bitc.dc_k;
    dummy.bitc.srst = real.bitc.srst;
    dummy.bitc.adc_cancel_out = real.bitc.adc_cancel_out;
    dummy.bitc.adc_cancel_disable = real.bitc.adc_cancel_disable;
    dummy.bitc.adc_start = real.bitc.adc_start;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_ADC_DC_dc_force_en(U8 data)
{
    GH_EPHY_ADC_DC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC_REAL;
    d.bitc.dc_force_en = data;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_dc_force_en(void)
{
    GH_EPHY_ADC_DC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dc_force_en;
}
GH_INLINE void GH_EPHY_set_ADC_DC_dc_force(U8 data)
{
    GH_EPHY_ADC_DC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC_REAL;
    d.bitc.dc_force = data;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_dc_force(void)
{
    GH_EPHY_ADC_DC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dc_force;
}
GH_INLINE void GH_EPHY_set_ADC_DC_dc_can_inv(U8 data)
{
    GH_EPHY_ADC_DC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC_REAL;
    d.bitc.dc_can_inv = data;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_dc_can_inv(void)
{
    GH_EPHY_ADC_DC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dc_can_inv;
}
GH_INLINE void GH_EPHY_set_ADC_DC_analog_blw(U8 data)
{
    GH_EPHY_ADC_DC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC_REAL;
    d.bitc.analog_blw = data;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_analog_blw(void)
{
    GH_EPHY_ADC_DC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.analog_blw;
}
GH_INLINE void GH_EPHY_set_ADC_DC_dc_k(U8 data)
{
    GH_EPHY_ADC_DC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC_REAL;
    d.bitc.dc_k = data;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_dc_k(void)
{
    GH_EPHY_ADC_DC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dc_k;
}
GH_INLINE void GH_EPHY_set_ADC_DC_srst(U8 data)
{
    GH_EPHY_ADC_DC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC_REAL;
    d.bitc.srst = data;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_srst(void)
{
    GH_EPHY_ADC_DC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.srst;
}
GH_INLINE void GH_EPHY_set_ADC_DC_adc_cancel_out(U8 data)
{
    GH_EPHY_ADC_DC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC_REAL;
    d.bitc.adc_cancel_out = data;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_adc_cancel_out(void)
{
    GH_EPHY_ADC_DC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_cancel_out;
}
GH_INLINE void GH_EPHY_set_ADC_DC_adc_cancel_disable(U8 data)
{
    GH_EPHY_ADC_DC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC_REAL;
    d.bitc.adc_cancel_disable = data;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_adc_cancel_disable(void)
{
    GH_EPHY_ADC_DC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_cancel_disable;
}
GH_INLINE void GH_EPHY_set_ADC_DC_adc_start(U8 data)
{
    GH_EPHY_ADC_DC_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADC_DC_REAL;
    d.bitc.adc_start = data;
    *(volatile U16 *)REG_EPHY_ADC_DC_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADC_DC_adc_start(void)
{
    GH_EPHY_ADC_DC_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADC_DC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_start;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_ADCPL (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_ADCPL(U16 data)
{
    GH_EPHY_ADCPL_REAL_S real;
    GH_EPHY_ADCPL_S dummy;
    dummy.all = data ;
    real.bitc.mod_10t = dummy.bitc.mod_10t;
    real.bitc.mod = dummy.bitc.mod;
    real.bitc.mod_lp = dummy.bitc.mod_lp;
    real.bitc.adc_frc_zero = dummy.bitc.adc_frc_zero;
    real.bitc.adcpl_step = dummy.bitc.adcpl_step;
    real.bitc.ac_a_timer_start = dummy.bitc.ac_a_timer_start;
    real.bitc.ac_sample_timer_start = dummy.bitc.ac_sample_timer_start;
    real.bitc.txramp_gen_10t = dummy.bitc.txramp_gen_10t;
    *(volatile U16 *)REG_EPHY_ADCPL_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_ADCPL(void)
{
    GH_EPHY_ADCPL_REAL_S real;
    GH_EPHY_ADCPL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_ADCPL_REAL);

    dummy.bitc.mod_10t = real.bitc.mod_10t;
    dummy.bitc.mod = real.bitc.mod;
    dummy.bitc.mod_lp = real.bitc.mod_lp;
    dummy.bitc.adc_frc_zero = real.bitc.adc_frc_zero;
    dummy.bitc.adcpl_step = real.bitc.adcpl_step;
    dummy.bitc.ac_a_timer_start = real.bitc.ac_a_timer_start;
    dummy.bitc.ac_sample_timer_start = real.bitc.ac_sample_timer_start;
    dummy.bitc.txramp_gen_10t = real.bitc.txramp_gen_10t;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_ADCPL_mod_10t(U8 data)
{
    GH_EPHY_ADCPL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL_REAL;
    d.bitc.mod_10t = data;
    *(volatile U16 *)REG_EPHY_ADCPL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADCPL_mod_10t(void)
{
    GH_EPHY_ADCPL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mod_10t;
}
GH_INLINE void GH_EPHY_set_ADCPL_mod(U8 data)
{
    GH_EPHY_ADCPL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL_REAL;
    d.bitc.mod = data;
    *(volatile U16 *)REG_EPHY_ADCPL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADCPL_mod(void)
{
    GH_EPHY_ADCPL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mod;
}
GH_INLINE void GH_EPHY_set_ADCPL_mod_lp(U8 data)
{
    GH_EPHY_ADCPL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL_REAL;
    d.bitc.mod_lp = data;
    *(volatile U16 *)REG_EPHY_ADCPL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADCPL_mod_lp(void)
{
    GH_EPHY_ADCPL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mod_lp;
}
GH_INLINE void GH_EPHY_set_ADCPL_adc_frc_zero(U8 data)
{
    GH_EPHY_ADCPL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL_REAL;
    d.bitc.adc_frc_zero = data;
    *(volatile U16 *)REG_EPHY_ADCPL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADCPL_adc_frc_zero(void)
{
    GH_EPHY_ADCPL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_frc_zero;
}
GH_INLINE void GH_EPHY_set_ADCPL_adcpl_step(U8 data)
{
    GH_EPHY_ADCPL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL_REAL;
    d.bitc.adcpl_step = data;
    *(volatile U16 *)REG_EPHY_ADCPL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADCPL_adcpl_step(void)
{
    GH_EPHY_ADCPL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adcpl_step;
}
GH_INLINE void GH_EPHY_set_ADCPL_ac_a_timer_start(U8 data)
{
    GH_EPHY_ADCPL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL_REAL;
    d.bitc.ac_a_timer_start = data;
    *(volatile U16 *)REG_EPHY_ADCPL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADCPL_ac_a_timer_start(void)
{
    GH_EPHY_ADCPL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ac_a_timer_start;
}
GH_INLINE void GH_EPHY_set_ADCPL_ac_sample_timer_start(U8 data)
{
    GH_EPHY_ADCPL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL_REAL;
    d.bitc.ac_sample_timer_start = data;
    *(volatile U16 *)REG_EPHY_ADCPL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADCPL_ac_sample_timer_start(void)
{
    GH_EPHY_ADCPL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ac_sample_timer_start;
}
GH_INLINE void GH_EPHY_set_ADCPL_txramp_gen_10t(U8 data)
{
    GH_EPHY_ADCPL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_ADCPL_REAL;
    d.bitc.txramp_gen_10t = data;
    *(volatile U16 *)REG_EPHY_ADCPL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_ADCPL_txramp_gen_10t(void)
{
    GH_EPHY_ADCPL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_ADCPL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.txramp_gen_10t;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_LDO (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_LDO(U16 data)
{
    GH_EPHY_LDO_REAL_S real;
    GH_EPHY_LDO_S dummy;
    dummy.all = data ;
    real.bitc.dummy = dummy.bitc.dummy;
    *(volatile U16 *)REG_EPHY_LDO_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_LDO(void)
{
    GH_EPHY_LDO_REAL_S real;
    GH_EPHY_LDO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_LDO_REAL);

    dummy.bitc.dummy = real.bitc.dummy;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_LDO_dummy(U16 data)
{
    GH_EPHY_LDO_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_LDO_REAL;
    d.bitc.dummy = data;
    *(volatile U16 *)REG_EPHY_LDO_REAL = d.all;
}
GH_INLINE U16  GH_EPHY_get_LDO_dummy(void)
{
    GH_EPHY_LDO_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_LDO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dummy;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_CLK_GATE (read)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_EPHY_get_CLK_GATE(void)
{
    GH_EPHY_CLK_GATE_REAL_S real;
    GH_EPHY_CLK_GATE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_CLK_GATE_REAL);

    dummy.bitc.eee_capability = real.bitc.eee_capability;
    return dummy.all;
}
GH_INLINE U16  GH_EPHY_get_CLK_GATE_eee_capability(void)
{
    GH_EPHY_CLK_GATE_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK_GATE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.eee_capability;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_CLK1 (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_CLK1(U16 data)
{
    GH_EPHY_CLK1_REAL_S real;
    GH_EPHY_CLK1_S dummy;
    dummy.all = data ;
    real.bitc.unkown = dummy.bitc.unkown;
    real.bitc.clko_200_gat = dummy.bitc.clko_200_gat;
    real.bitc.clko_200_inv = dummy.bitc.clko_200_inv;
    real.bitc.lut_new = dummy.bitc.lut_new;
    *(volatile U16 *)REG_EPHY_CLK1_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_CLK1(void)
{
    GH_EPHY_CLK1_REAL_S real;
    GH_EPHY_CLK1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_CLK1_REAL);

    dummy.bitc.unkown = real.bitc.unkown;
    dummy.bitc.clko_200_gat = real.bitc.clko_200_gat;
    dummy.bitc.clko_200_inv = real.bitc.clko_200_inv;
    dummy.bitc.lut_new = real.bitc.lut_new;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_CLK1_unkown(U8 data)
{
    GH_EPHY_CLK1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK1_REAL;
    d.bitc.unkown = data;
    *(volatile U16 *)REG_EPHY_CLK1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CLK1_unkown(void)
{
    GH_EPHY_CLK1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.unkown;
}
GH_INLINE void GH_EPHY_set_CLK1_clko_200_gat(U8 data)
{
    GH_EPHY_CLK1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK1_REAL;
    d.bitc.clko_200_gat = data;
    *(volatile U16 *)REG_EPHY_CLK1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CLK1_clko_200_gat(void)
{
    GH_EPHY_CLK1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clko_200_gat;
}
GH_INLINE void GH_EPHY_set_CLK1_clko_200_inv(U8 data)
{
    GH_EPHY_CLK1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK1_REAL;
    d.bitc.clko_200_inv = data;
    *(volatile U16 *)REG_EPHY_CLK1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CLK1_clko_200_inv(void)
{
    GH_EPHY_CLK1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clko_200_inv;
}
GH_INLINE void GH_EPHY_set_CLK1_lut_new(U8 data)
{
    GH_EPHY_CLK1_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK1_REAL;
    d.bitc.lut_new = data;
    *(volatile U16 *)REG_EPHY_CLK1_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CLK1_lut_new(void)
{
    GH_EPHY_CLK1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lut_new;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_GCR_TX (read/write)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_GCR_TX(U16 data)
{
    GH_EPHY_GCR_TX_REAL_S real;
    GH_EPHY_GCR_TX_S dummy;
    dummy.all = data ;
    real.bitc.ioffset_sel = dummy.bitc.ioffset_sel;
    real.bitc.ld_vcmo = dummy.bitc.ld_vcmo;
    real.bitc.ph_delay = dummy.bitc.ph_delay;
    real.bitc.phase_100t = dummy.bitc.phase_100t;
    real.bitc.ld_iq_sel = dummy.bitc.ld_iq_sel;
    real.bitc.ld_iq_ibias = dummy.bitc.ld_iq_ibias;
    real.bitc.en_tx_ioffset = dummy.bitc.en_tx_ioffset;
    real.bitc.save2x_tx = dummy.bitc.save2x_tx;
    real.bitc.wssel_inv = dummy.bitc.wssel_inv;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_GCR_TX(void)
{
    GH_EPHY_GCR_TX_REAL_S real;
    GH_EPHY_GCR_TX_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    dummy.bitc.ioffset_sel = real.bitc.ioffset_sel;
    dummy.bitc.ld_vcmo = real.bitc.ld_vcmo;
    dummy.bitc.ph_delay = real.bitc.ph_delay;
    dummy.bitc.phase_100t = real.bitc.phase_100t;
    dummy.bitc.ld_iq_sel = real.bitc.ld_iq_sel;
    dummy.bitc.ld_iq_ibias = real.bitc.ld_iq_ibias;
    dummy.bitc.en_tx_ioffset = real.bitc.en_tx_ioffset;
    dummy.bitc.save2x_tx = real.bitc.save2x_tx;
    dummy.bitc.wssel_inv = real.bitc.wssel_inv;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ioffset_sel(U8 data)
{
    GH_EPHY_GCR_TX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX_REAL;
    d.bitc.ioffset_sel = data;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ioffset_sel(void)
{
    GH_EPHY_GCR_TX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ioffset_sel;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ld_vcmo(U8 data)
{
    GH_EPHY_GCR_TX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX_REAL;
    d.bitc.ld_vcmo = data;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ld_vcmo(void)
{
    GH_EPHY_GCR_TX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ld_vcmo;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ph_delay(U8 data)
{
    GH_EPHY_GCR_TX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX_REAL;
    d.bitc.ph_delay = data;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ph_delay(void)
{
    GH_EPHY_GCR_TX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ph_delay;
}
GH_INLINE void GH_EPHY_set_GCR_TX_phase_100t(U8 data)
{
    GH_EPHY_GCR_TX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX_REAL;
    d.bitc.phase_100t = data;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_phase_100t(void)
{
    GH_EPHY_GCR_TX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.phase_100t;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ld_iq_sel(U8 data)
{
    GH_EPHY_GCR_TX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX_REAL;
    d.bitc.ld_iq_sel = data;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ld_iq_sel(void)
{
    GH_EPHY_GCR_TX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ld_iq_sel;
}
GH_INLINE void GH_EPHY_set_GCR_TX_ld_iq_ibias(U8 data)
{
    GH_EPHY_GCR_TX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX_REAL;
    d.bitc.ld_iq_ibias = data;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_ld_iq_ibias(void)
{
    GH_EPHY_GCR_TX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ld_iq_ibias;
}
GH_INLINE void GH_EPHY_set_GCR_TX_en_tx_ioffset(U8 data)
{
    GH_EPHY_GCR_TX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX_REAL;
    d.bitc.en_tx_ioffset = data;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_en_tx_ioffset(void)
{
    GH_EPHY_GCR_TX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_tx_ioffset;
}
GH_INLINE void GH_EPHY_set_GCR_TX_save2x_tx(U8 data)
{
    GH_EPHY_GCR_TX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX_REAL;
    d.bitc.save2x_tx = data;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_save2x_tx(void)
{
    GH_EPHY_GCR_TX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.save2x_tx;
}
GH_INLINE void GH_EPHY_set_GCR_TX_wssel_inv(U8 data)
{
    GH_EPHY_GCR_TX_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_GCR_TX_REAL;
    d.bitc.wssel_inv = data;
    *(volatile U16 *)REG_EPHY_GCR_TX_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_GCR_TX_wssel_inv(void)
{
    GH_EPHY_GCR_TX_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_GCR_TX_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.wssel_inv;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_POWER (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_POWER(U16 data)
{
    GH_EPHY_POWER_REAL_S real;
    GH_EPHY_POWER_S dummy;
    dummy.all = data ;
    real.bitc.pd_tx_ld = dummy.bitc.pd_tx_ld;
    real.bitc.pd_tx_idac = dummy.bitc.pd_tx_idac;
    real.bitc.pd_dacramp_new = dummy.bitc.pd_dacramp_new;
    real.bitc.pd_dacnew_testen = dummy.bitc.pd_dacnew_testen;
    real.bitc.pd_tx_ld_10t = dummy.bitc.pd_tx_ld_10t;
    real.bitc.pd_tx_ld_100t = dummy.bitc.pd_tx_ld_100t;
    real.bitc.pd_tx_ld_lp = dummy.bitc.pd_tx_ld_lp;
    real.bitc.pd_tx_idac_10t = dummy.bitc.pd_tx_idac_10t;
    real.bitc.pd_tx_idac_100t = dummy.bitc.pd_tx_idac_100t;
    real.bitc.pd_tx_idac_lp = dummy.bitc.pd_tx_idac_lp;
    *(volatile U16 *)REG_EPHY_POWER_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_POWER(void)
{
    GH_EPHY_POWER_REAL_S real;
    GH_EPHY_POWER_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    dummy.bitc.pd_tx_ld = real.bitc.pd_tx_ld;
    dummy.bitc.pd_tx_idac = real.bitc.pd_tx_idac;
    dummy.bitc.pd_dacramp_new = real.bitc.pd_dacramp_new;
    dummy.bitc.pd_dacnew_testen = real.bitc.pd_dacnew_testen;
    dummy.bitc.pd_tx_ld_10t = real.bitc.pd_tx_ld_10t;
    dummy.bitc.pd_tx_ld_100t = real.bitc.pd_tx_ld_100t;
    dummy.bitc.pd_tx_ld_lp = real.bitc.pd_tx_ld_lp;
    dummy.bitc.pd_tx_idac_10t = real.bitc.pd_tx_idac_10t;
    dummy.bitc.pd_tx_idac_100t = real.bitc.pd_tx_idac_100t;
    dummy.bitc.pd_tx_idac_lp = real.bitc.pd_tx_idac_lp;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_ld(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_tx_ld = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_ld(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_tx_ld;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_idac(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_tx_idac = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_idac(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_tx_idac;
}
GH_INLINE void GH_EPHY_set_POWER_pd_dacramp_new(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_dacramp_new = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_dacramp_new(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_dacramp_new;
}
GH_INLINE void GH_EPHY_set_POWER_pd_dacnew_testen(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_dacnew_testen = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_dacnew_testen(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_dacnew_testen;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_ld_10t(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_tx_ld_10t = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_ld_10t(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_tx_ld_10t;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_ld_100t(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_tx_ld_100t = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_ld_100t(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_tx_ld_100t;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_ld_lp(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_tx_ld_lp = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_ld_lp(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_tx_ld_lp;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_idac_10t(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_tx_idac_10t = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_idac_10t(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_tx_idac_10t;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_idac_100t(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_tx_idac_100t = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_idac_100t(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_tx_idac_100t;
}
GH_INLINE void GH_EPHY_set_POWER_pd_tx_idac_lp(U8 data)
{
    GH_EPHY_POWER_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_POWER_REAL;
    d.bitc.pd_tx_idac_lp = data;
    *(volatile U16 *)REG_EPHY_POWER_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_POWER_pd_tx_idac_lp(void)
{
    GH_EPHY_POWER_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_POWER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_tx_idac_lp;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_MDIIO (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_MDIIO(U16 data)
{
    GH_EPHY_MDIIO_REAL_S real;
    GH_EPHY_MDIIO_S dummy;
    dummy.all = data ;
    real.bitc.mdio_idle_error_cnt_clear = dummy.bitc.mdio_idle_error_cnt_clear;
    real.bitc.pd_vbuf = dummy.bitc.pd_vbuf;
    *(volatile U16 *)REG_EPHY_MDIIO_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_MDIIO(void)
{
    GH_EPHY_MDIIO_REAL_S real;
    GH_EPHY_MDIIO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_MDIIO_REAL);

    dummy.bitc.mdio_idle_error_cnt_clear = real.bitc.mdio_idle_error_cnt_clear;
    dummy.bitc.pd_vbuf = real.bitc.pd_vbuf;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_MDIIO_mdio_idle_error_cnt_clear(U8 data)
{
    GH_EPHY_MDIIO_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_MDIIO_REAL;
    d.bitc.mdio_idle_error_cnt_clear = data;
    *(volatile U16 *)REG_EPHY_MDIIO_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_MDIIO_mdio_idle_error_cnt_clear(void)
{
    GH_EPHY_MDIIO_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MDIIO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mdio_idle_error_cnt_clear;
}
GH_INLINE void GH_EPHY_set_MDIIO_pd_vbuf(U8 data)
{
    GH_EPHY_MDIIO_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_MDIIO_REAL;
    d.bitc.pd_vbuf = data;
    *(volatile U16 *)REG_EPHY_MDIIO_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_MDIIO_pd_vbuf(void)
{
    GH_EPHY_MDIIO_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_MDIIO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_vbuf;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_CLK0 (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_CLK0(U16 data)
{
    GH_EPHY_CLK0_REAL_S real;
    GH_EPHY_CLK0_S dummy;
    dummy.all = data ;
    real.bitc.lpi_tx_tq_timer_msb = dummy.bitc.lpi_tx_tq_timer_msb;
    real.bitc.clko_125_inv = dummy.bitc.clko_125_inv;
    real.bitc.clko_100_gat = dummy.bitc.clko_100_gat;
    real.bitc.clko_100_inv = dummy.bitc.clko_100_inv;
    *(volatile U16 *)REG_EPHY_CLK0_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_CLK0(void)
{
    GH_EPHY_CLK0_REAL_S real;
    GH_EPHY_CLK0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_CLK0_REAL);

    dummy.bitc.lpi_tx_tq_timer_msb = real.bitc.lpi_tx_tq_timer_msb;
    dummy.bitc.clko_125_inv = real.bitc.clko_125_inv;
    dummy.bitc.clko_100_gat = real.bitc.clko_100_gat;
    dummy.bitc.clko_100_inv = real.bitc.clko_100_inv;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_CLK0_lpi_tx_tq_timer_msb(U8 data)
{
    GH_EPHY_CLK0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK0_REAL;
    d.bitc.lpi_tx_tq_timer_msb = data;
    *(volatile U16 *)REG_EPHY_CLK0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CLK0_lpi_tx_tq_timer_msb(void)
{
    GH_EPHY_CLK0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lpi_tx_tq_timer_msb;
}
GH_INLINE void GH_EPHY_set_CLK0_clko_125_inv(U8 data)
{
    GH_EPHY_CLK0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK0_REAL;
    d.bitc.clko_125_inv = data;
    *(volatile U16 *)REG_EPHY_CLK0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CLK0_clko_125_inv(void)
{
    GH_EPHY_CLK0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clko_125_inv;
}
GH_INLINE void GH_EPHY_set_CLK0_clko_100_gat(U8 data)
{
    GH_EPHY_CLK0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK0_REAL;
    d.bitc.clko_100_gat = data;
    *(volatile U16 *)REG_EPHY_CLK0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CLK0_clko_100_gat(void)
{
    GH_EPHY_CLK0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clko_100_gat;
}
GH_INLINE void GH_EPHY_set_CLK0_clko_100_inv(U8 data)
{
    GH_EPHY_CLK0_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_CLK0_REAL;
    d.bitc.clko_100_inv = data;
    *(volatile U16 *)REG_EPHY_CLK0_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_CLK0_clko_100_inv(void)
{
    GH_EPHY_CLK0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_CLK0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clko_100_inv;
}

/*----------------------------------------------------------------------------*/
/* register EPHY_WAVE_CTRL (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_set_WAVE_CTRL(U16 data)
{
    GH_EPHY_WAVE_CTRL_REAL_S real;
    GH_EPHY_WAVE_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.shadow = dummy.bitc.shadow;
    *(volatile U16 *)REG_EPHY_WAVE_CTRL_REAL = real.all;
}
GH_INLINE U16  GH_EPHY_get_WAVE_CTRL(void)
{
    GH_EPHY_WAVE_CTRL_REAL_S real;
    GH_EPHY_WAVE_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_EPHY_WAVE_CTRL_REAL);

    dummy.bitc.shadow = real.bitc.shadow;
    return dummy.all;
}
GH_INLINE void GH_EPHY_set_WAVE_CTRL_shadow(U8 data)
{
    GH_EPHY_WAVE_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_EPHY_WAVE_CTRL_REAL;
    d.bitc.shadow = data;
    *(volatile U16 *)REG_EPHY_WAVE_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_EPHY_get_WAVE_CTRL_shadow(void)
{
    GH_EPHY_WAVE_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_EPHY_WAVE_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.shadow;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_EPHY_init(void)
{
    GH_EPHY_set_MII_RMII((U32)0x00000002);
    GH_EPHY_set_CONTROL((U16)0x00000000);
    GH_EPHY_set_ANAR((U16)0x000001e1);
    GH_EPHY_set_ANER((U16)0x00000000);
    GH_EPHY_set_ANNPAR((U16)0x00000000);
    GH_EPHY_set_MS_CONTROL((U16)0x00000000);
    GH_EPHY_set_PSE_CONTROL((U16)0x00000000);
    GH_EPHY_set_MMD_CONTROL((U16)0x00000000);
    GH_EPHY_set_MMD_CONTROL_ADDR((U16)0x00000000);
    GH_EPHY_set_WAVE_SHAPING_34((U16)0x00007c7c);
    GH_EPHY_set_WAVE_SHAPING_56((U16)0x00007878);
    GH_EPHY_set_WAVE_SHAPING_78((U16)0x00007474);
    GH_EPHY_set_WAVE_SHAPING_9A((U16)0x00003868);
    GH_EPHY_set_WAVE_SHAPING_BC((U16)0x00000000);
    GH_EPHY_set_WAVE_SHAPING_DE((U16)0x00000000);
    GH_EPHY_set_SPEED((U16)0x00003c00);
    GH_EPHY_set_LTP((U16)0x00000000);
    GH_EPHY_set_MCU((U16)0x00000000);
    GH_EPHY_set_CODE_RAM((U16)0x00000000);
    GH_EPHY_set_CODE_RAM_W((U16)0x00000000);
    GH_EPHY_set_100M_LINK((U16)0x00000000);
    GH_EPHY_set_DEBUG((U16)0x00000000);
    GH_EPHY_set_DEBUG_MODE((U16)0x0000810a);
    GH_EPHY_set_RST_EN((U16)0x00000248);
    GH_EPHY_set_SNR_K((U16)0x00001520);
    GH_EPHY_set_DET_MAX((U16)0x0000024c);
    GH_EPHY_set_DET_MIN((U16)0x00000190);
    GH_EPHY_set_SNR_LEN((U16)0x00001800);
    GH_EPHY_set_LPF((U16)0x00000000);
    GH_EPHY_set_ADC_GAIN_PGA((U16)0x00001704);
    GH_EPHY_set_ADC_GSHIFT((U16)0x00000000);
    GH_EPHY_set_ADC((U16)0x00001704);
    GH_EPHY_set_PLL_ADC_CTRL3((U16)0x00004100);
    GH_EPHY_set_RX_LPF((U16)0x00004c43);
    GH_EPHY_set_PLL_ADC_CTRL0((U16)0x0000011a);
    GH_EPHY_set_PLL_ADC_CTRL1((U16)0x0000d190);
    GH_EPHY_set_PLL_ADC_CTRL2((U16)0x00000020);
    GH_EPHY_set_TEST_TX((U16)0x00000000);
    GH_EPHY_set_PWR((U16)0x00000059);
    GH_EPHY_set_ADC_DC((U16)0x00004060);
    GH_EPHY_set_ADCPL((U16)0x00000821);
    GH_EPHY_set_LDO((U16)0x00000000);
    GH_EPHY_set_CLK1((U16)0x00000053);
    GH_EPHY_set_GCR_TX((U16)0x00004100);
    GH_EPHY_set_POWER((U16)0x000003f3);
    GH_EPHY_set_MDIIO((U16)0x00001000);
    GH_EPHY_set_CLK0((U16)0x00004008);
    GH_EPHY_set_WAVE_CTRL((U16)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

