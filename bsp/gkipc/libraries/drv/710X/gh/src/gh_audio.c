/******************************************************************************
**
** \file      gh_audio.c
**
** \brief     Audio Interface..
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
#include "gh_audio.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_AUDIO_AHB_GENERAL0_REAL                         FIO_ADDRESS(AUDIO,0x60020E00) /* read/write */
#define REG_AUDIO_AHB_GENERAL1_REAL                         FIO_ADDRESS(AUDIO,0x60020E04) /* read/write */
#define REG_AUDIO_SYS_RST_CTRL0_REAL                        FIO_ADDRESS(AUDIO,0x60020C00) /* read/write */
#define REG_AUDIO_CKG_CTRL0_REAL                            FIO_ADDRESS(AUDIO,0x60020C04) /* read/write */
#define REG_AUDIO_AUDIOBAND_CTRL2_REAL                      FIO_ADDRESS(AUDIO,0x60020C08) /* read/write */
#define REG_AUDIO_TIMING_CTRL0_REAL                         FIO_ADDRESS(AUDIO,0x60020C0C) /* read/write */
#define REG_AUDIO_AUDIOBAND_CTRL0_REAL                      FIO_ADDRESS(AUDIO,0x60020C10) /* read/write */
#define REG_AUDIO_AUDIOBAND_STS_REAL                        FIO_ADDRESS(AUDIO,0x60020C14) /* read */
#define REG_AUDIO_SDM_CTRL0_REAL                            FIO_ADDRESS(AUDIO,0x60020C18) /* read/write */
#define REG_AUDIO_SDM_CTRL1_REAL                            FIO_ADDRESS(AUDIO,0x60020C1C) /* read/write */
#define REG_AUDIO_NF_SYNTH_1_NF_H_REAL                      FIO_ADDRESS(AUDIO,0x60020C20) /* read/write */
#define REG_AUDIO_NF_SYNTH_1_NF_L_REAL                      FIO_ADDRESS(AUDIO,0x60020C24) /* read/write */
#define REG_AUDIO_NF_SYNTH_2_NF_H_REAL                      FIO_ADDRESS(AUDIO,0x60020C28) /* read/write */
#define REG_AUDIO_NF_SYNTH_2_NF_L_REAL                      FIO_ADDRESS(AUDIO,0x60020C2C) /* read/write */
#define REG_AUDIO_DIG_MIC_CTRL_REAL                         FIO_ADDRESS(AUDIO,0x60020C30) /* read/write */
#define REG_AUDIO_AUDIOBAND_STS2_REAL                       FIO_ADDRESS(AUDIO,0x60020C34) /* read */
#define REG_AUDIO_SDM_DWA_DATAIN_L_REAL                     FIO_ADDRESS(AUDIO,0x60020C38) /* read */
#define REG_AUDIO_SDM_DWA_DATAIN_R_REAL                     FIO_ADDRESS(AUDIO,0x60020C3C) /* read */
#define REG_AUDIO_VALID_SIGNALS_REAL                        FIO_ADDRESS(AUDIO,0x60020C40) /* read */
#define REG_AUDIO_PGA_DPGA_CFG_REAL                         FIO_ADDRESS(AUDIO,0x60020C44) /* read/write */
#define REG_AUDIO_MMP_DPGA_CFG1_REAL                        FIO_ADDRESS(AUDIO,0x60020C48) /* read/write */
#define REG_AUDIO_MMP_DPGA_CFG2_REAL                        FIO_ADDRESS(AUDIO,0x60020C4C) /* read/write */
#define REG_AUDIO_MIX_CTRL0_REAL                            FIO_ADDRESS(AUDIO,0x60020C50) /* read/write */
#define REG_AUDIO_INT_DOUT_REAL                             FIO_ADDRESS(AUDIO,0x60020C68) /* read */
#define REG_AUDIO_FIFO_TH_CTRL0_REAL                        FIO_ADDRESS(AUDIO,0x60020C6C) /* read/write */
#define REG_AUDIO_TIMING_CTRL1_REAL                         FIO_ADDRESS(AUDIO,0x60020D40) /* read/write */
#define REG_AUDIO_AUDIOBAND_CTRL1_REAL                      FIO_ADDRESS(AUDIO,0x60020D44) /* read/write */
#define REG_AUDIO_FIFO_CTRL_REAL                            FIO_ADDRESS(AUDIO,0x60020D48) /* read/write */
#define REG_AUDIO_FIFO_STS_REAL                             FIO_ADDRESS(AUDIO,0x60020D4C) /* read */
#define REG_AUDIO_NF_SYNTH_5_NF_H_REAL                      FIO_ADDRESS(AUDIO,0x60020D50) /* read */
#define REG_AUDIO_NF_SYNTH_5_NF_L_REAL                      FIO_ADDRESS(AUDIO,0x60020D54) /* read */
#define REG_AUDIO_INT_CTRL_REAL                             FIO_ADDRESS(AUDIO,0x60020D58) /* read */
#define REG_AUDIO_SINE_GEN_CTRL0_REAL                       FIO_ADDRESS(AUDIO,0x60020D64) /* read/write */
#define REG_AUDIO_SINE_GEN_CTRL1_REAL                       FIO_ADDRESS(AUDIO,0x60020D68) /* read/write */
#define REG_AUDIO_TEST_CTRL0_REAL                           FIO_ADDRESS(AUDIO,0x60020D6C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL00_REAL                        FIO_ADDRESS(AUDIO,0x60021C00) /* read/write */
#define REG_AUDIO_ANALOG_CTRL01_REAL                        FIO_ADDRESS(AUDIO,0x60021C04) /* read/write */
#define REG_AUDIO_ANALOG_CTRL02_REAL                        FIO_ADDRESS(AUDIO,0x60021C08) /* read/write */
#define REG_AUDIO_ANALOG_CTRL03_REAL                        FIO_ADDRESS(AUDIO,0x60021C0C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL04_REAL                        FIO_ADDRESS(AUDIO,0x60021C10) /* read/write */
#define REG_AUDIO_ANALOG_CTRL05_REAL                        FIO_ADDRESS(AUDIO,0x60021C14) /* read/write */
#define REG_AUDIO_ANALOG_CTRL06_REAL                        FIO_ADDRESS(AUDIO,0x60021C18) /* read/write */
#define REG_AUDIO_ANALOG_CTRL07_REAL                        FIO_ADDRESS(AUDIO,0x60021C1C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL08_REAL                        FIO_ADDRESS(AUDIO,0x60021C20) /* read/write */
#define REG_AUDIO_ANALOG_CTRL09_REAL                        FIO_ADDRESS(AUDIO,0x60021C24) /* read/write */
#define REG_AUDIO_ANALOG_CTRL10_REAL                        FIO_ADDRESS(AUDIO,0x60021C28) /* read/write */
#define REG_AUDIO_ANALOG_CTRL11_REAL                        FIO_ADDRESS(AUDIO,0x60021C2C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL12_REAL                        FIO_ADDRESS(AUDIO,0x60021C30) /* read/write */
#define REG_AUDIO_ANALOG_CTRL13_REAL                        FIO_ADDRESS(AUDIO,0x60021C34) /* read/write */
#define REG_AUDIO_ANALOG_CTRL14_REAL                        FIO_ADDRESS(AUDIO,0x60021C38) /* read/write */
#define REG_AUDIO_ANALOG_CTRL15_REAL                        FIO_ADDRESS(AUDIO,0x60021C3C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL16_REAL                        FIO_ADDRESS(AUDIO,0x60021C40) /* read/write */
#define REG_AUDIO_ANALOG_CTRL17_REAL                        FIO_ADDRESS(AUDIO,0x60021C44) /* read/write */
#define REG_AUDIO_ANALOG_CTRL18_REAL                        FIO_ADDRESS(AUDIO,0x60021C48) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* AUDIO_AHB_GENERAL0 */
    U16 all;
    struct {
        U16 usb_tm1                     : 1;
        U16 ahb_rmii_sel                : 1;
        U16                             : 14;
    } bitc;
} GH_AUDIO_AHB_GENERAL0_REAL_S;

typedef union { /* AUDIO_AHB_GENERAL1 */
    U16 all;
    struct {
        U16 audio_i2s_sel               : 1;
        U16                             : 15;
    } bitc;
} GH_AUDIO_AHB_GENERAL1_REAL_S;

typedef union { /* AUDIO_SYS_RST_CTRL0 */
    U16 all;
    struct {
        U16                             : 13;
        U16 reset_sdm_sync              : 1;
        U16 reset_dpga_sync             : 1;
        U16 reset_au_sync               : 1;
    } bitc;
} GH_AUDIO_SYS_RST_CTRL0_REAL_S;

typedef union { /* AUDIO_CKG_CTRL0 */
    U16 all;
    struct {
        U16 au_src1_mac_48m_dyng_en     : 1;
        U16                             : 15;
    } bitc;
} GH_AUDIO_CKG_CTRL0_REAL_S;

typedef union { /* AUDIO_AUDIOBAND_CTRL2 */
    U16 all;
    struct {
        U16                             : 2;
        U16 en_dec_4_p                  : 1;
        U16 en_dec_3_p                  : 1;
        U16                             : 4;
        U16 nt4_mix_ctrl                : 2;
        U16 nt3_mix_ctrl                : 2;
        U16                             : 2;
        U16 dec_num3                    : 2;
    } bitc;
} GH_AUDIO_AUDIOBAND_CTRL2_REAL_S;

typedef union { /* AUDIO_TIMING_CTRL0 */
    U16 all;
    struct {
        U16 en_time_gen_p               : 1;
        U16 en_dec_1_p                  : 1;
        U16 en_dec_2_p                  : 1;
        U16 en_int_1_p                  : 1;
        U16 en_int_2_p                  : 1;
        U16 en_asrc1_p                  : 1;
        U16                             : 2;
        U16 dec_num                     : 2;
        U16 dac_sync_sel                : 1;
        U16 adc_sync_sel                : 1;
        U16 sync_clk2_sel               : 2;
        U16 sync_clk1_sel               : 2;
    } bitc;
} GH_AUDIO_TIMING_CTRL0_REAL_S;

typedef union { /* AUDIO_AUDIOBAND_CTRL0 */
    U16 all;
    struct {
        U16 ini_sram                    : 1;
        U16 ch12_sync_enable            : 1;
        U16                             : 10;
        U16 ch2_int_128fs_nf_sel        : 1;
        U16 ch1_int_128fs_nf_sel        : 1;
        U16                             : 2;
    } bitc;
} GH_AUDIO_AUDIOBAND_CTRL0_REAL_S;

typedef union { /* AUDIO_AUDIOBAND_STS */
    U16 all;
    struct {
        U16 quant_out_r                 : 6;
        U16 quant_out_l                 : 6;
        U16                             : 4;
    } bitc;
} GH_AUDIO_AUDIOBAND_STS_REAL_S;

typedef union { /* AUDIO_SDM_CTRL0 */
    U16 all;
    struct {
        U16 en_sdm_p                    : 1;
        U16 fs_synth_sel_p              : 1;
        U16 dac_din_l_sel               : 2;
        U16 dac_din_r_sel               : 2;
        U16 fix_msb_en                  : 1;
        U16 fix_msb_sel                 : 5;
        U16 dither_en_p                 : 1;
        U16 dither_sel                  : 3;
    } bitc;
} GH_AUDIO_SDM_CTRL0_REAL_S;

typedef union { /* AUDIO_SDM_CTRL1 */
    U16 all;
    struct {
        U16 sdm_offset                  : 16;
    } bitc;
} GH_AUDIO_SDM_CTRL1_REAL_S;

typedef union { /* AUDIO_NF_SYNTH_1_NF_H */
    U16 all;
    struct {
        U16 value                       : 14;
        U16 trig                        : 2;
    } bitc;
} GH_AUDIO_NF_SYNTH_1_NF_H_REAL_S;

typedef union { /* AUDIO_NF_SYNTH_1_NF_L */
    U16 all;
    struct {
        U16 value                       : 16;
    } bitc;
} GH_AUDIO_NF_SYNTH_1_NF_L_REAL_S;

typedef union { /* AUDIO_NF_SYNTH_2_NF_H */
    U16 all;
    struct {
        U16 value                       : 14;
        U16                             : 1;
        U16 trig                        : 1;
    } bitc;
} GH_AUDIO_NF_SYNTH_2_NF_H_REAL_S;

typedef union { /* AUDIO_NF_SYNTH_2_NF_L */
    U16 all;
    struct {
        U16 value                       : 16;
    } bitc;
} GH_AUDIO_NF_SYNTH_2_NF_L_REAL_S;

typedef union { /* AUDIO_DIG_MIC_CTRL */
    U16 all;
    struct {
        U16 pga_status_clr              : 1;
        U16 dpga_status_clr             : 1;
        U16 pnt_mmc3_dec_sync_enz       : 1;
        U16 pnt_mmc1_dec_sync_enz       : 1;
        U16                             : 1;
        U16 pnt_mmc_dec_err_clr         : 1;
        U16                             : 10;
    } bitc;
} GH_AUDIO_DIG_MIC_CTRL_REAL_S;

typedef union { /* AUDIO_AUDIOBAND_STS2 */
    U16 all;
    struct {
        U16 pga_status                  : 2;
        U16 mmp2_mute_done              : 1;
        U16 mmp1_mute_done              : 1;
        U16 pnt_mmc_dec_err_clr         : 1;
        U16                             : 3;
        U16 dpga_status                 : 7;
        U16                             : 1;
    } bitc;
} GH_AUDIO_AUDIOBAND_STS2_REAL_S;

typedef union { /* AUDIO_SDM_DWA_DATAIN_L */
    U16 all;
    struct {
        U16 data                        : 16;
    } bitc;
} GH_AUDIO_SDM_DWA_DATAIN_L_REAL_S;

typedef union { /* AUDIO_SDM_DWA_DATAIN_R */
    U16 all;
    struct {
        U16 data                        : 16;
    } bitc;
} GH_AUDIO_SDM_DWA_DATAIN_R_REAL_S;

typedef union { /* AUDIO_VALID_SIGNALS */
    U16 all;
    struct {
        U16 valid_signals               : 16;
    } bitc;
} GH_AUDIO_VALID_SIGNALS_REAL_S;

typedef union { /* AUDIO_PGA_DPGA_CFG */
    U16 all;
    struct {
        U16 pga2_gain                   : 5;
        U16 pga2_gain_trig              : 1;
        U16 pga2_mute                   : 1;
        U16 pga2_en                     : 1;
        U16 pga1_gain                   : 5;
        U16 pga1_gain_trig              : 1;
        U16 pga1_mute                   : 1;
        U16 pga1_en                     : 1;
    } bitc;
} GH_AUDIO_PGA_DPGA_CFG_REAL_S;

typedef union { /* AUDIO_MMP_DPGA_CFG1 */
    U16 all;
    struct {
        U16 dpga_en                     : 1;
        U16 fading_en                   : 1;
        U16 mute_2_zero                 : 1;
        U16 step                        : 3;
        U16 offset                      : 5;
        U16                             : 5;
    } bitc;
} GH_AUDIO_MMP_DPGA_CFG1_REAL_S;

typedef union { /* AUDIO_MMP_DPGA_CFG2 */
    U16 all;
    struct {
        U16 gain                        : 8;
        U16 gain_trig                   : 1;
        U16                             : 7;
    } bitc;
} GH_AUDIO_MMP_DPGA_CFG2_REAL_S;

typedef union { /* AUDIO_MIX_CTRL0 */
    U16 all;
    struct {
        U16                             : 2;
        U16 ch2_mux_sel                 : 2;
        U16 ch1_mux_sel                 : 2;
        U16                             : 8;
        U16 sel_dec2_dout               : 1;
        U16 sel_dec1_dout               : 1;
    } bitc;
} GH_AUDIO_MIX_CTRL0_REAL_S;

typedef union { /* AUDIO_FIFO_TH_CTRL0 */
    U16 all;
    struct {
        U16 tx                          : 7;
        U16                             : 1;
        U16 rx                          : 7;
        U16                             : 1;
    } bitc;
} GH_AUDIO_FIFO_TH_CTRL0_REAL_S;

typedef union { /* AUDIO_TIMING_CTRL1 */
    U16 all;
    struct {
        U16                             : 8;
        U16 dec_num2                    : 2;
        U16                             : 1;
        U16 en_asrc3_p                  : 1;
        U16                             : 2;
        U16 ch2_int_cnt_sync_sel        : 1;
        U16 ch1_int_cnt_sync_sel        : 1;
    } bitc;
} GH_AUDIO_TIMING_CTRL1_REAL_S;

typedef union { /* AUDIO_AUDIOBAND_CTRL1 */
    U16 all;
    struct {
        U16                             : 10;
        U16 sdm_dwa_datain_r_sel        : 2;
        U16 sdm_dwa_datain_l_sel        : 2;
        U16                             : 2;
    } bitc;
} GH_AUDIO_AUDIOBAND_CTRL1_REAL_S;

typedef union { /* AUDIO_FIFO_CTRL */
    U16 all;
    struct {
        U16 tx_fifo_int_en              : 4;
        U16 tx_fifo_enable              : 1;
        U16                             : 2;
        U16 tx_fifo_status_clr          : 1;
        U16 rx_fifo_int_en              : 4;
        U16 rx_fifo_enable              : 1;
        U16                             : 2;
        U16 rx_fifo_status_clr          : 1;
    } bitc;
} GH_AUDIO_FIFO_CTRL_REAL_S;

typedef union { /* AUDIO_FIFO_STS */
    U16 all;
    struct {
        U16 tx_fifo_status              : 4;
        U16 rx_fifo_status              : 4;
        U16                             : 8;
    } bitc;
} GH_AUDIO_FIFO_STS_REAL_S;

typedef union { /* AUDIO_SINE_GEN_CTRL0 */
    U16 all;
    struct {
        U16 ch1_sin_gen_en_p            : 1;
        U16 ch2_sin_gen_en_p            : 1;
        U16 en_dit_sine                 : 1;
        U16 en_dit_src                  : 1;
        U16                             : 2;
        U16 pga2_swap                   : 1;
        U16 pga1_swap                   : 1;
        U16                             : 4;
        U16 int2_mix_ctrl               : 2;
        U16 int1_mix_ctrl               : 2;
    } bitc;
} GH_AUDIO_SINE_GEN_CTRL0_REAL_S;

typedef union { /* AUDIO_SINE_GEN_CTRL1 */
    U16 all;
    struct {
        U16 sine_gen_ch1_freq           : 4;
        U16 sine_gen_ch1_gain           : 4;
        U16 sine_gen_ch2_freq           : 4;
        U16 sine_gen_ch2_gain           : 4;
    } bitc;
} GH_AUDIO_SINE_GEN_CTRL1_REAL_S;

typedef union { /* AUDIO_TEST_CTRL0 */
    U16 all;
    struct {
        U16 dac_test_en                 : 1;
        U16 sdm_test_en                 : 1;
        U16 sdm_sft_dis                 : 1;
        U16 sram_cg_en                  : 1;
        U16 testclk_sel                 : 6;
        U16                             : 2;
        U16 testbus_sel                 : 4;
    } bitc;
} GH_AUDIO_TEST_CTRL0_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL00 */
    U16 all;
    struct {
        U16 dbnc_time                   : 2;
        U16 mcpls_sel                   : 2;
        U16 mcpls_prd                   : 3;
        U16                             : 5;
        U16 _rstz_au_det                : 1;
        U16 int_au_det_test_value       : 1;
        U16 int_au_det_test_mode        : 1;
        U16 mcpls_en                    : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL00_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL01 */
    U16 all;
    struct {
        U16                             : 1;
        U16 int_mask_miclp_plugin       : 1;
        U16 int_mask_miclp_unplug       : 1;
        U16 int_mask_spk_plugin         : 1;
        U16 int_mask_spk_unplug         : 1;
        U16 int_mask_hs_plugin          : 1;
        U16 int_mask_hs_unplug          : 1;
        U16 int_mask_hs_gnd             : 1;
        U16                             : 1;
        U16 int_clr_miclp_plugin        : 1;
        U16 int_clr_miclp_unplug        : 1;
        U16 int_clr_spk_plugin          : 1;
        U16 int_clr_spk_unplug          : 1;
        U16 int_clr_hs_plugin           : 1;
        U16 int_clr_hs_unplug           : 1;
        U16 int_clr_hs_gnc              : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL01_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL02 */
    U16 all;
    struct {
        U16                             : 3;
        U16 sdm_out_3_4_12_sel          : 1;
        U16 sdm_out_1_2_12_sel          : 1;
        U16 sdm_out_3_4_12_swap_sel     : 1;
        U16 sdm_out_1_2_12_swap_sel     : 1;
        U16 sdm_out_4_12_inv_sel        : 1;
        U16 sdm_out_3_12_inv_sel        : 1;
        U16 sdm_out_2_12_inv_sel        : 1;
        U16 sdm_out_1_12_inv_sel        : 1;
        U16                             : 4;
        U16 dft_sel                     : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL02_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL03 */
    U16 all;
    struct {
        U16 sel_irefdet                 : 2;
        U16 reg_en_micbias_12           : 1;
        U16 micv_sel                    : 2;
        U16 rcv_en_12                   : 1;
        U16 hst_en_12                   : 1;
        U16 en_micdet_12                : 1;
        U16 reg_control                 : 1;
        U16 reg_sel_control             : 1;
        U16 en_ref_no_bg_12             : 1;
        U16 en_polling_drv_12           : 1;
        U16 ibsel_audio                 : 2;
        U16 en_audio_ibias_12           : 1;
        U16 en_clk_tst                  : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL03_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL04 */
    U16 all;
    struct {
        U16 pga0_mica2sel               : 2;
        U16 pga0_mica2_gain             : 1;
        U16 en_pga0_mica2               : 1;
        U16 pga0_mica1_gain             : 1;
        U16 en_pga0_mica1               : 1;
        U16 ibias_pga0                  : 2;
        U16 en_ibias_pga0               : 1;
        U16 en_vcmbuf0_12               : 1;
        U16 sel_vcmref0                 : 1;
        U16 pullup_hsip                 : 1;
        U16 en_micdet_lp_12             : 1;
        U16 en_mictrim_12               : 1;
        U16 sel_irefgnd                 : 2;
    } bitc;
} GH_AUDIO_ANALOG_CTRL04_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL05 */
    U16 all;
    struct {
        U16 ibias_pga1                  : 2;
        U16 en_ibias_pga1               : 1;
        U16 en_vcmbuf1                  : 1;
        U16 sel_vcmref1                 : 1;
        U16 pga0_line_sel               : 1;
        U16 pga0_mute_r                 : 1;
        U16 pga0_mica4_sel              : 1;
        U16 pga0_mica4_gain             : 3;
        U16 en_pga0_mica4               : 1;
        U16 pga0_mica3_gain             : 1;
        U16 en_pga0_mica3               : 1;
        U16 pga0_mute_l                 : 1;
        U16 pga0_mica2sel               : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL05_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL06 */
    U16 all;
    struct {
        U16 en_dac0_r_12                : 1;
        U16 en_dac0_l_12                : 1;
        U16 en_dac0_ldo11               : 1;
        U16 ldo11_vc0                   : 1;
        U16 pos_rl0                     : 1;
        U16 pga1_line_sel               : 1;
        U16 pga1_mute_r                 : 1;
        U16 pga1_mica4_gain             : 3;
        U16 en_pga1_mica4               : 1;
        U16 pga1_mute_l                 : 1;
        U16 pga1_mica2_gain             : 3;
        U16 en_pga1_mica2               : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL06_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL07 */
    U16 all;
    struct {
        U16 en_adc1_dit                 : 1;
        U16 en_adc0_12                  : 1;
        U16 shrt_adc0_l                 : 1;
        U16 shrt_adc0_r                 : 1;
        U16 reset_adc0_l                : 1;
        U16 reset_adc0_r                : 1;
        U16 sel_ibias_adc0              : 2;
        U16 sel_dit_lvl_adc0            : 2;
        U16 en_adc0_dit                 : 1;
        U16 en_dac1_r_12                : 1;
        U16 en_dac1_l_12                : 1;
        U16 en_dac1_ldo11               : 1;
        U16 ldo11_vc1                   : 1;
        U16 pos_rl1                     : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL07_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL08 */
    U16 all;
    struct {
        U16                             : 1;
        U16 gain_ear                    : 2;
        U16 en_stg2ab_12                : 1;
        U16 en_oplp_12                  : 1;
        U16 en_earl_12                  : 1;
        U16 en_earr_12                  : 1;
        U16 en_adc1_12                  : 1;
        U16 shrt_adc1_l                 : 1;
        U16 shrt_adc1_r                 : 1;
        U16 reset_adc1_l                : 1;
        U16 reset_adc1_r                : 1;
        U16 sel_ibias_adc1              : 2;
        U16 sel_dit_lvl_adc1            : 2;
    } bitc;
} GH_AUDIO_ANALOG_CTRL08_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL09 */
    U16 all;
    struct {
        U16 mx_ear                      : 3;
        U16 isel_ocp                    : 2;
        U16 isel_drv                    : 2;
        U16 tst_drv                     : 4;
        U16 ear_mute                    : 1;
        U16 ear_popres                  : 2;
        U16 tcsel                       : 2;
    } bitc;
} GH_AUDIO_ANALOG_CTRL09_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL10 */
    U16 all;
    struct {
        U16 mute_line1                  : 1;
        U16 mx_line1                    : 2;
        U16 gain_line1                  : 3;
        U16 en_line1_r                  : 1;
        U16 en_line1_l                  : 1;
        U16 mute_line0                  : 1;
        U16 mx_line0                    : 2;
        U16 gain_line0                  : 3;
        U16 en_line0_r                  : 1;
        U16 en_line0_l                  : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL10_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL11 */
    U16 all;
    struct {
        U16                             : 3;
        U16 tst_autio                   : 4;
        U16 sel_ck_audio                : 2;
        U16 sel_phs_adcclk              : 1;
        U16 adc_clk_freq                : 1;
        U16 dac_clk_freq                : 1;
        U16 en_clk                      : 1;
        U16 v_set_ldo25                 : 2;
        U16 en_ldo25_12                 : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL11_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL12 */
    U16 all;
    struct {
        U16 audio_reg                   : 8;
        U16                             : 4;
        U16 test_bus_sel                : 4;
    } bitc;
} GH_AUDIO_ANALOG_CTRL12_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL13 */
    U16 all;
    struct {
        U16 mic_trim_sel_cfg            : 6;
        U16                             : 6;
        U16 trim_stop_sel               : 1;
        U16 rstz_trim_au                : 1;
        U16 trim_au_sel                 : 1;
        U16 trim_stop                   : 1;
    } bitc;
} GH_AUDIO_ANALOG_CTRL13_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL14 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL14_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL15 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL15_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL16 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL16_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL17 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL17_REAL_S;

typedef union { /* AUDIO_ANALOG_CTRL18 */
    U16 all;
    struct {
        U16 audio_sleep_dbg_bus         : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL18_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register AUDIO_AHB_GENERAL0 (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_AHB_GENERAL0(U16 data)
{
    GH_AUDIO_AHB_GENERAL0_REAL_S real;
    GH_AUDIO_AHB_GENERAL0_S dummy;
    dummy.all = data ;
    real.bitc.usb_tm1 = dummy.bitc.usb_tm1;
    real.bitc.ahb_rmii_sel = dummy.bitc.ahb_rmii_sel;
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_AHB_GENERAL0(void)
{
    GH_AUDIO_AHB_GENERAL0_REAL_S real;
    GH_AUDIO_AHB_GENERAL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL0_REAL);

    dummy.bitc.usb_tm1 = real.bitc.usb_tm1;
    dummy.bitc.ahb_rmii_sel = real.bitc.ahb_rmii_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_AHB_GENERAL0_USB_TM1(U8 data)
{
    GH_AUDIO_AHB_GENERAL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AHB_GENERAL0_REAL;
    d.bitc.usb_tm1 = data;
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AHB_GENERAL0_USB_TM1(void)
{
    GH_AUDIO_AHB_GENERAL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.usb_tm1;
}
GH_INLINE void GH_AUDIO_set_AHB_GENERAL0_AHB_RMII_SEL(U8 data)
{
    GH_AUDIO_AHB_GENERAL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AHB_GENERAL0_REAL;
    d.bitc.ahb_rmii_sel = data;
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AHB_GENERAL0_AHB_RMII_SEL(void)
{
    GH_AUDIO_AHB_GENERAL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ahb_rmii_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_AHB_GENERAL1 (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_AHB_GENERAL1(U16 data)
{
    GH_AUDIO_AHB_GENERAL1_REAL_S real;
    GH_AUDIO_AHB_GENERAL1_S dummy;
    dummy.all = data ;
    real.bitc.audio_i2s_sel = dummy.bitc.audio_i2s_sel;
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL1_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_AHB_GENERAL1(void)
{
    GH_AUDIO_AHB_GENERAL1_REAL_S real;
    GH_AUDIO_AHB_GENERAL1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL1_REAL);

    dummy.bitc.audio_i2s_sel = real.bitc.audio_i2s_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_AHB_GENERAL1_AUDIO_I2S_SEL(U8 data)
{
    GH_AUDIO_AHB_GENERAL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AHB_GENERAL1_REAL;
    d.bitc.audio_i2s_sel = data;
    *(volatile U16 *)REG_AUDIO_AHB_GENERAL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AHB_GENERAL1_AUDIO_I2S_SEL(void)
{
    GH_AUDIO_AHB_GENERAL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AHB_GENERAL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.audio_i2s_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_SYS_RST_CTRL0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_SYS_RST_CTRL0(U16 data)
{
    GH_AUDIO_SYS_RST_CTRL0_REAL_S real;
    GH_AUDIO_SYS_RST_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.reset_sdm_sync = dummy.bitc.reset_sdm_sync;
    real.bitc.reset_dpga_sync = dummy.bitc.reset_dpga_sync;
    real.bitc.reset_au_sync = dummy.bitc.reset_au_sync;
    *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_SYS_RST_CTRL0(void)
{
    GH_AUDIO_SYS_RST_CTRL0_REAL_S real;
    GH_AUDIO_SYS_RST_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL);

    dummy.bitc.reset_sdm_sync = real.bitc.reset_sdm_sync;
    dummy.bitc.reset_dpga_sync = real.bitc.reset_dpga_sync;
    dummy.bitc.reset_au_sync = real.bitc.reset_au_sync;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_SYS_RST_CTRL0_RESET_SDM_SYNC(U8 data)
{
    GH_AUDIO_SYS_RST_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL;
    d.bitc.reset_sdm_sync = data;
    *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_SDM_SYNC(void)
{
    GH_AUDIO_SYS_RST_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset_sdm_sync;
}
GH_INLINE void GH_AUDIO_set_SYS_RST_CTRL0_RESET_DPGA_SYNC(U8 data)
{
    GH_AUDIO_SYS_RST_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL;
    d.bitc.reset_dpga_sync = data;
    *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_DPGA_SYNC(void)
{
    GH_AUDIO_SYS_RST_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset_dpga_sync;
}
GH_INLINE void GH_AUDIO_set_SYS_RST_CTRL0_RESET_AU_SYNC(U8 data)
{
    GH_AUDIO_SYS_RST_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL;
    d.bitc.reset_au_sync = data;
    *(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_AU_SYNC(void)
{
    GH_AUDIO_SYS_RST_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SYS_RST_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset_au_sync;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_CKG_CTRL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_CKG_CTRL0(U16 data)
{
    GH_AUDIO_CKG_CTRL0_REAL_S real;
    GH_AUDIO_CKG_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.au_src1_mac_48m_dyng_en = dummy.bitc.au_src1_mac_48m_dyng_en;
    *(volatile U16 *)REG_AUDIO_CKG_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_CKG_CTRL0(void)
{
    GH_AUDIO_CKG_CTRL0_REAL_S real;
    GH_AUDIO_CKG_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_CKG_CTRL0_REAL);

    dummy.bitc.au_src1_mac_48m_dyng_en = real.bitc.au_src1_mac_48m_dyng_en;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN(U8 data)
{
    GH_AUDIO_CKG_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_CKG_CTRL0_REAL;
    d.bitc.au_src1_mac_48m_dyng_en = data;
    *(volatile U16 *)REG_AUDIO_CKG_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN(void)
{
    GH_AUDIO_CKG_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_CKG_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.au_src1_mac_48m_dyng_en;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_CTRL2 (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2(U16 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S real;
    GH_AUDIO_AUDIOBAND_CTRL2_S dummy;
    dummy.all = data ;
    real.bitc.en_dec_4_p = dummy.bitc.en_dec_4_p;
    real.bitc.en_dec_3_p = dummy.bitc.en_dec_3_p;
    real.bitc.nt4_mix_ctrl = dummy.bitc.nt4_mix_ctrl;
    real.bitc.nt3_mix_ctrl = dummy.bitc.nt3_mix_ctrl;
    real.bitc.dec_num3 = dummy.bitc.dec_num3;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_CTRL2(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S real;
    GH_AUDIO_AUDIOBAND_CTRL2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL);

    dummy.bitc.en_dec_4_p = real.bitc.en_dec_4_p;
    dummy.bitc.en_dec_3_p = real.bitc.en_dec_3_p;
    dummy.bitc.nt4_mix_ctrl = real.bitc.nt4_mix_ctrl;
    dummy.bitc.nt3_mix_ctrl = real.bitc.nt3_mix_ctrl;
    dummy.bitc.dec_num3 = real.bitc.dec_num3;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_4_p(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL;
    d.bitc.en_dec_4_p = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_4_p(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dec_4_p;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_3_p(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL;
    d.bitc.en_dec_3_p = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_3_p(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dec_3_p;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_NT4_MIX_CTRL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL;
    d.bitc.nt4_mix_ctrl = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_NT4_MIX_CTRL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.nt4_mix_ctrl;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_NT3_MIX_CTRL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL;
    d.bitc.nt3_mix_ctrl = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_NT3_MIX_CTRL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.nt3_mix_ctrl;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL2_DEC_NUM3(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL;
    d.bitc.dec_num3 = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL2_DEC_NUM3(void)
{
    GH_AUDIO_AUDIOBAND_CTRL2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dec_num3;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_TIMING_CTRL0 (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0(U16 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S real;
    GH_AUDIO_TIMING_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.en_time_gen_p = dummy.bitc.en_time_gen_p;
    real.bitc.en_dec_1_p = dummy.bitc.en_dec_1_p;
    real.bitc.en_dec_2_p = dummy.bitc.en_dec_2_p;
    real.bitc.en_int_1_p = dummy.bitc.en_int_1_p;
    real.bitc.en_int_2_p = dummy.bitc.en_int_2_p;
    real.bitc.en_asrc1_p = dummy.bitc.en_asrc1_p;
    real.bitc.dec_num = dummy.bitc.dec_num;
    real.bitc.dac_sync_sel = dummy.bitc.dac_sync_sel;
    real.bitc.adc_sync_sel = dummy.bitc.adc_sync_sel;
    real.bitc.sync_clk2_sel = dummy.bitc.sync_clk2_sel;
    real.bitc.sync_clk1_sel = dummy.bitc.sync_clk1_sel;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_TIMING_CTRL0(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S real;
    GH_AUDIO_TIMING_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    dummy.bitc.en_time_gen_p = real.bitc.en_time_gen_p;
    dummy.bitc.en_dec_1_p = real.bitc.en_dec_1_p;
    dummy.bitc.en_dec_2_p = real.bitc.en_dec_2_p;
    dummy.bitc.en_int_1_p = real.bitc.en_int_1_p;
    dummy.bitc.en_int_2_p = real.bitc.en_int_2_p;
    dummy.bitc.en_asrc1_p = real.bitc.en_asrc1_p;
    dummy.bitc.dec_num = real.bitc.dec_num;
    dummy.bitc.dac_sync_sel = real.bitc.dac_sync_sel;
    dummy.bitc.adc_sync_sel = real.bitc.adc_sync_sel;
    dummy.bitc.sync_clk2_sel = real.bitc.sync_clk2_sel;
    dummy.bitc.sync_clk1_sel = real.bitc.sync_clk1_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_TIME_GEN_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.en_time_gen_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_TIME_GEN_p(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_time_gen_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_DEC_1_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.en_dec_1_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_DEC_1_p(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dec_1_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_DEC_2_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.en_dec_2_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_DEC_2_p(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dec_2_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_INT_1_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.en_int_1_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_INT_1_p(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_int_1_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_INT_2_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.en_int_2_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_INT_2_p(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_int_2_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_EN_ASRC1_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.en_asrc1_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_EN_ASRC1_p(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_asrc1_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_DEC_NUM(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.dec_num = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_DEC_NUM(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dec_num;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_DAC_SYNC_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.dac_sync_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_DAC_SYNC_SEL(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dac_sync_sel;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_ADC_SYNC_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.adc_sync_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_ADC_SYNC_SEL(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_sync_sel;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK2_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.sync_clk2_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK2_SEL(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sync_clk2_sel;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK1_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL;
    d.bitc.sync_clk1_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK1_SEL(void)
{
    GH_AUDIO_TIMING_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sync_clk1_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_CTRL0 (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0(U16 data)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S real;
    GH_AUDIO_AUDIOBAND_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.ini_sram = dummy.bitc.ini_sram;
    real.bitc.ch12_sync_enable = dummy.bitc.ch12_sync_enable;
    real.bitc.ch2_int_128fs_nf_sel = dummy.bitc.ch2_int_128fs_nf_sel;
    real.bitc.ch1_int_128fs_nf_sel = dummy.bitc.ch1_int_128fs_nf_sel;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_CTRL0(void)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S real;
    GH_AUDIO_AUDIOBAND_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL);

    dummy.bitc.ini_sram = real.bitc.ini_sram;
    dummy.bitc.ch12_sync_enable = real.bitc.ch12_sync_enable;
    dummy.bitc.ch2_int_128fs_nf_sel = real.bitc.ch2_int_128fs_nf_sel;
    dummy.bitc.ch1_int_128fs_nf_sel = real.bitc.ch1_int_128fs_nf_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0_INI_SRAM(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL;
    d.bitc.ini_sram = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL0_INI_SRAM(void)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ini_sram;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL;
    d.bitc.ch12_sync_enable = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE(void)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ch12_sync_enable;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL;
    d.bitc.ch2_int_128fs_nf_sel = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ch2_int_128fs_nf_sel;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL;
    d.bitc.ch1_int_128fs_nf_sel = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ch1_int_128fs_nf_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_STS (read)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_STS(void)
{
    GH_AUDIO_AUDIOBAND_STS_REAL_S real;
    GH_AUDIO_AUDIOBAND_STS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS_REAL);

    dummy.bitc.quant_out_r = real.bitc.quant_out_r;
    dummy.bitc.quant_out_l = real.bitc.quant_out_l;
    return dummy.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_R(void)
{
    GH_AUDIO_AUDIOBAND_STS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.quant_out_r;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_L(void)
{
    GH_AUDIO_AUDIOBAND_STS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.quant_out_l;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_CTRL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_SDM_CTRL0(U16 data)
{
    GH_AUDIO_SDM_CTRL0_REAL_S real;
    GH_AUDIO_SDM_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.en_sdm_p = dummy.bitc.en_sdm_p;
    real.bitc.fs_synth_sel_p = dummy.bitc.fs_synth_sel_p;
    real.bitc.dac_din_l_sel = dummy.bitc.dac_din_l_sel;
    real.bitc.dac_din_r_sel = dummy.bitc.dac_din_r_sel;
    real.bitc.fix_msb_en = dummy.bitc.fix_msb_en;
    real.bitc.fix_msb_sel = dummy.bitc.fix_msb_sel;
    real.bitc.dither_en_p = dummy.bitc.dither_en_p;
    real.bitc.dither_sel = dummy.bitc.dither_sel;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_SDM_CTRL0(void)
{
    GH_AUDIO_SDM_CTRL0_REAL_S real;
    GH_AUDIO_SDM_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL);

    dummy.bitc.en_sdm_p = real.bitc.en_sdm_p;
    dummy.bitc.fs_synth_sel_p = real.bitc.fs_synth_sel_p;
    dummy.bitc.dac_din_l_sel = real.bitc.dac_din_l_sel;
    dummy.bitc.dac_din_r_sel = real.bitc.dac_din_r_sel;
    dummy.bitc.fix_msb_en = real.bitc.fix_msb_en;
    dummy.bitc.fix_msb_sel = real.bitc.fix_msb_sel;
    dummy.bitc.dither_en_p = real.bitc.dither_en_p;
    dummy.bitc.dither_sel = real.bitc.dither_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_EN_SDM_p(U8 data)
{
    GH_AUDIO_SDM_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL;
    d.bitc.en_sdm_p = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_EN_SDM_p(void)
{
    GH_AUDIO_SDM_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_sdm_p;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_FS_SYNTH_SEL_p(U8 data)
{
    GH_AUDIO_SDM_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL;
    d.bitc.fs_synth_sel_p = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_FS_SYNTH_SEL_p(void)
{
    GH_AUDIO_SDM_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fs_synth_sel_p;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_DAC_DIN_L_SEL(U8 data)
{
    GH_AUDIO_SDM_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL;
    d.bitc.dac_din_l_sel = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_DAC_DIN_L_SEL(void)
{
    GH_AUDIO_SDM_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dac_din_l_sel;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_DAC_DIN_R_SEL(U8 data)
{
    GH_AUDIO_SDM_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL;
    d.bitc.dac_din_r_sel = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_DAC_DIN_R_SEL(void)
{
    GH_AUDIO_SDM_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dac_din_r_sel;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_FIX_MSB_EN(U8 data)
{
    GH_AUDIO_SDM_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL;
    d.bitc.fix_msb_en = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_FIX_MSB_EN(void)
{
    GH_AUDIO_SDM_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fix_msb_en;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_FIX_MSB_SEL(U8 data)
{
    GH_AUDIO_SDM_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL;
    d.bitc.fix_msb_sel = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_FIX_MSB_SEL(void)
{
    GH_AUDIO_SDM_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fix_msb_sel;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_DITHER_EN_p(U8 data)
{
    GH_AUDIO_SDM_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL;
    d.bitc.dither_en_p = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_DITHER_EN_p(void)
{
    GH_AUDIO_SDM_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dither_en_p;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL0_DITHER_SEL(U8 data)
{
    GH_AUDIO_SDM_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL;
    d.bitc.dither_sel = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SDM_CTRL0_DITHER_SEL(void)
{
    GH_AUDIO_SDM_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dither_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_CTRL1 (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_SDM_CTRL1(U16 data)
{
    GH_AUDIO_SDM_CTRL1_REAL_S real;
    GH_AUDIO_SDM_CTRL1_S dummy;
    dummy.all = data ;
    real.bitc.sdm_offset = dummy.bitc.sdm_offset;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL1_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_SDM_CTRL1(void)
{
    GH_AUDIO_SDM_CTRL1_REAL_S real;
    GH_AUDIO_SDM_CTRL1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_SDM_CTRL1_REAL);

    dummy.bitc.sdm_offset = real.bitc.sdm_offset;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_SDM_CTRL1_SDM_OFFSET(U16 data)
{
    GH_AUDIO_SDM_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SDM_CTRL1_REAL;
    d.bitc.sdm_offset = data;
    *(volatile U16 *)REG_AUDIO_SDM_CTRL1_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_SDM_CTRL1_SDM_OFFSET(void)
{
    GH_AUDIO_SDM_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_offset;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_1_NF_H (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_H(U16 data)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_REAL_S real;
    GH_AUDIO_NF_SYNTH_1_NF_H_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    real.bitc.trig = dummy.bitc.trig;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_1_NF_H(void)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_REAL_S real;
    GH_AUDIO_NF_SYNTH_1_NF_H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H_REAL);

    dummy.bitc.value = real.bitc.value;
    dummy.bitc.trig = real.bitc.trig;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_H_VALUE(U16 data)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H_REAL;
    d.bitc.value = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_1_NF_H_VALUE(void)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.value;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_H_TRIG(U8 data)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H_REAL;
    d.bitc.trig = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_NF_SYNTH_1_NF_H_TRIG(void)
{
    GH_AUDIO_NF_SYNTH_1_NF_H_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.trig;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_1_NF_L (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_L(U16 data)
{
    GH_AUDIO_NF_SYNTH_1_NF_L_REAL_S real;
    GH_AUDIO_NF_SYNTH_1_NF_L_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_1_NF_L(void)
{
    GH_AUDIO_NF_SYNTH_1_NF_L_REAL_S real;
    GH_AUDIO_NF_SYNTH_1_NF_L_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L_REAL);

    dummy.bitc.value = real.bitc.value;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_1_NF_L_VALUE(U16 data)
{
    GH_AUDIO_NF_SYNTH_1_NF_L_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L_REAL;
    d.bitc.value = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_1_NF_L_VALUE(void)
{
    GH_AUDIO_NF_SYNTH_1_NF_L_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_1_NF_L_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_2_NF_H (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_H(U16 data)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_REAL_S real;
    GH_AUDIO_NF_SYNTH_2_NF_H_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    real.bitc.trig = dummy.bitc.trig;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_2_NF_H(void)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_REAL_S real;
    GH_AUDIO_NF_SYNTH_2_NF_H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H_REAL);

    dummy.bitc.value = real.bitc.value;
    dummy.bitc.trig = real.bitc.trig;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_H_VALUE(U16 data)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H_REAL;
    d.bitc.value = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_2_NF_H_VALUE(void)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.value;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_H_TRIG(U8 data)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H_REAL;
    d.bitc.trig = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_NF_SYNTH_2_NF_H_TRIG(void)
{
    GH_AUDIO_NF_SYNTH_2_NF_H_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.trig;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_2_NF_L (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_L(U16 data)
{
    GH_AUDIO_NF_SYNTH_2_NF_L_REAL_S real;
    GH_AUDIO_NF_SYNTH_2_NF_L_S dummy;
    dummy.all = data ;
    real.bitc.value = dummy.bitc.value;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_2_NF_L(void)
{
    GH_AUDIO_NF_SYNTH_2_NF_L_REAL_S real;
    GH_AUDIO_NF_SYNTH_2_NF_L_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L_REAL);

    dummy.bitc.value = real.bitc.value;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_NF_SYNTH_2_NF_L_VALUE(U16 data)
{
    GH_AUDIO_NF_SYNTH_2_NF_L_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L_REAL;
    d.bitc.value = data;
    *(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_2_NF_L_VALUE(void)
{
    GH_AUDIO_NF_SYNTH_2_NF_L_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_2_NF_L_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.value;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_DIG_MIC_CTRL (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL(U16 data)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S real;
    GH_AUDIO_DIG_MIC_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.pga_status_clr = dummy.bitc.pga_status_clr;
    real.bitc.dpga_status_clr = dummy.bitc.dpga_status_clr;
    real.bitc.pnt_mmc3_dec_sync_enz = dummy.bitc.pnt_mmc3_dec_sync_enz;
    real.bitc.pnt_mmc1_dec_sync_enz = dummy.bitc.pnt_mmc1_dec_sync_enz;
    real.bitc.pnt_mmc_dec_err_clr = dummy.bitc.pnt_mmc_dec_err_clr;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_DIG_MIC_CTRL(void)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S real;
    GH_AUDIO_DIG_MIC_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL);

    dummy.bitc.pga_status_clr = real.bitc.pga_status_clr;
    dummy.bitc.dpga_status_clr = real.bitc.dpga_status_clr;
    dummy.bitc.pnt_mmc3_dec_sync_enz = real.bitc.pnt_mmc3_dec_sync_enz;
    dummy.bitc.pnt_mmc1_dec_sync_enz = real.bitc.pnt_mmc1_dec_sync_enz;
    dummy.bitc.pnt_mmc_dec_err_clr = real.bitc.pnt_mmc_dec_err_clr;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_PGA_STATUS_CLR(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL;
    d.bitc.pga_status_clr = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_PGA_STATUS_CLR(void)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga_status_clr;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_DPGA_STATUS_CLR(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL;
    d.bitc.dpga_status_clr = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_DPGA_STATUS_CLR(void)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dpga_status_clr;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL;
    d.bitc.pnt_mmc3_dec_sync_enz = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ(void)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pnt_mmc3_dec_sync_enz;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL;
    d.bitc.pnt_mmc1_dec_sync_enz = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ(void)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pnt_mmc1_dec_sync_enz;
}
GH_INLINE void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR(U8 data)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL;
    d.bitc.pnt_mmc_dec_err_clr = data;
    *(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR(void)
{
    GH_AUDIO_DIG_MIC_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_DIG_MIC_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pnt_mmc_dec_err_clr;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_STS2 (read)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_STS2(void)
{
    GH_AUDIO_AUDIOBAND_STS2_REAL_S real;
    GH_AUDIO_AUDIOBAND_STS2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2_REAL);

    dummy.bitc.pga_status = real.bitc.pga_status;
    dummy.bitc.mmp2_mute_done = real.bitc.mmp2_mute_done;
    dummy.bitc.mmp1_mute_done = real.bitc.mmp1_mute_done;
    dummy.bitc.pnt_mmc_dec_err_clr = real.bitc.pnt_mmc_dec_err_clr;
    dummy.bitc.dpga_status = real.bitc.dpga_status;
    return dummy.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_PGA_STATUS(void)
{
    GH_AUDIO_AUDIOBAND_STS2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga_status;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_MMP2_MUTE_DONE(void)
{
    GH_AUDIO_AUDIOBAND_STS2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mmp2_mute_done;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_MMP1_MUTE_DONE(void)
{
    GH_AUDIO_AUDIOBAND_STS2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mmp1_mute_done;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_PNT_MMC_DEC_ERR_CLR(void)
{
    GH_AUDIO_AUDIOBAND_STS2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pnt_mmc_dec_err_clr;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_STS2_DPGA_STATUS(void)
{
    GH_AUDIO_AUDIOBAND_STS2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_STS2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dpga_status;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_DWA_DATAIN_L (read)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_SDM_DWA_DATAIN_L(void)
{
    GH_AUDIO_SDM_DWA_DATAIN_L_REAL_S real;
    GH_AUDIO_SDM_DWA_DATAIN_L_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_SDM_DWA_DATAIN_L_REAL);

    dummy.bitc.data = real.bitc.data;
    return dummy.all;
}
GH_INLINE U16  GH_AUDIO_get_SDM_DWA_DATAIN_L_data(void)
{
    GH_AUDIO_SDM_DWA_DATAIN_L_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_DWA_DATAIN_L_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_DWA_DATAIN_R (read)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_SDM_DWA_DATAIN_R(void)
{
    GH_AUDIO_SDM_DWA_DATAIN_R_REAL_S real;
    GH_AUDIO_SDM_DWA_DATAIN_R_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_SDM_DWA_DATAIN_R_REAL);

    dummy.bitc.data = real.bitc.data;
    return dummy.all;
}
GH_INLINE U16  GH_AUDIO_get_SDM_DWA_DATAIN_R_data(void)
{
    GH_AUDIO_SDM_DWA_DATAIN_R_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SDM_DWA_DATAIN_R_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_VALID_SIGNALS (read)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_VALID_SIGNALS(void)
{
    GH_AUDIO_VALID_SIGNALS_REAL_S real;
    GH_AUDIO_VALID_SIGNALS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_VALID_SIGNALS_REAL);

    dummy.bitc.valid_signals = real.bitc.valid_signals;
    return dummy.all;
}
GH_INLINE U16  GH_AUDIO_get_VALID_SIGNALS_VALID_SIGNALS(void)
{
    GH_AUDIO_VALID_SIGNALS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_VALID_SIGNALS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.valid_signals;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_PGA_DPGA_CFG (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG(U16 data)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S real;
    GH_AUDIO_PGA_DPGA_CFG_S dummy;
    dummy.all = data ;
    real.bitc.pga2_gain = dummy.bitc.pga2_gain;
    real.bitc.pga2_gain_trig = dummy.bitc.pga2_gain_trig;
    real.bitc.pga2_mute = dummy.bitc.pga2_mute;
    real.bitc.pga2_en = dummy.bitc.pga2_en;
    real.bitc.pga1_gain = dummy.bitc.pga1_gain;
    real.bitc.pga1_gain_trig = dummy.bitc.pga1_gain_trig;
    real.bitc.pga1_mute = dummy.bitc.pga1_mute;
    real.bitc.pga1_en = dummy.bitc.pga1_en;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_PGA_DPGA_CFG(void)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S real;
    GH_AUDIO_PGA_DPGA_CFG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL);

    dummy.bitc.pga2_gain = real.bitc.pga2_gain;
    dummy.bitc.pga2_gain_trig = real.bitc.pga2_gain_trig;
    dummy.bitc.pga2_mute = real.bitc.pga2_mute;
    dummy.bitc.pga2_en = real.bitc.pga2_en;
    dummy.bitc.pga1_gain = real.bitc.pga1_gain;
    dummy.bitc.pga1_gain_trig = real.bitc.pga1_gain_trig;
    dummy.bitc.pga1_mute = real.bitc.pga1_mute;
    dummy.bitc.pga1_en = real.bitc.pga1_en;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL;
    d.bitc.pga2_gain = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain(void)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga2_gain;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain_trig(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL;
    d.bitc.pga2_gain_trig = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain_trig(void)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga2_gain_trig;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_mute(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL;
    d.bitc.pga2_mute = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_mute(void)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga2_mute;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_en(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL;
    d.bitc.pga2_en = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_en(void)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga2_en;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL;
    d.bitc.pga1_gain = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain(void)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_gain;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain_trig(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL;
    d.bitc.pga1_gain_trig = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain_trig(void)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_gain_trig;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_mute(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL;
    d.bitc.pga1_mute = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_mute(void)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_mute;
}
GH_INLINE void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_en(U8 data)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL;
    d.bitc.pga1_en = data;
    *(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_en(void)
{
    GH_AUDIO_PGA_DPGA_CFG_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_PGA_DPGA_CFG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_en;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_MMP_DPGA_CFG1 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1(U8 index, U16 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S real;
    GH_AUDIO_MMP_DPGA_CFG1_S dummy;
    dummy.all = data ;
    real.bitc.dpga_en = dummy.bitc.dpga_en;
    real.bitc.fading_en = dummy.bitc.fading_en;
    real.bitc.mute_2_zero = dummy.bitc.mute_2_zero;
    real.bitc.step = dummy.bitc.step;
    real.bitc.offset = dummy.bitc.offset;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)) = real.all;
}
GH_INLINE U16  GH_AUDIO_get_MMP_DPGA_CFG1(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S real;
    GH_AUDIO_MMP_DPGA_CFG1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)));

    dummy.bitc.dpga_en = real.bitc.dpga_en;
    dummy.bitc.fading_en = real.bitc.fading_en;
    dummy.bitc.mute_2_zero = real.bitc.mute_2_zero;
    dummy.bitc.step = real.bitc.step;
    dummy.bitc.offset = real.bitc.offset;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_DPGA_EN(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018));
    d.bitc.dpga_en = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)) = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_DPGA_EN(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)));

    tmp_value.all = value;
    return tmp_value.bitc.dpga_en;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_FADING_EN(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018));
    d.bitc.fading_en = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)) = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_FADING_EN(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)));

    tmp_value.all = value;
    return tmp_value.bitc.fading_en;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_MUTE_2_ZERO(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018));
    d.bitc.mute_2_zero = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)) = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_MUTE_2_ZERO(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)));

    tmp_value.all = value;
    return tmp_value.bitc.mute_2_zero;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_STEP(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018));
    d.bitc.step = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)) = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_STEP(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)));

    tmp_value.all = value;
    return tmp_value.bitc.step;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG1_OFFSET(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018));
    d.bitc.offset = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)) = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG1_OFFSET(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG1_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)));

    tmp_value.all = value;
    return tmp_value.bitc.offset;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_MMP_DPGA_CFG2 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG2(U8 index, U16 data)
{
    GH_AUDIO_MMP_DPGA_CFG2_REAL_S real;
    GH_AUDIO_MMP_DPGA_CFG2_S dummy;
    dummy.all = data ;
    real.bitc.gain = dummy.bitc.gain;
    real.bitc.gain_trig = dummy.bitc.gain_trig;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)) = real.all;
}
GH_INLINE U16  GH_AUDIO_get_MMP_DPGA_CFG2(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG2_REAL_S real;
    GH_AUDIO_MMP_DPGA_CFG2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)));

    dummy.bitc.gain = real.bitc.gain;
    dummy.bitc.gain_trig = real.bitc.gain_trig;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG2_GAIN(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG2_REAL_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2_REAL + index * FIO_MOFFSET(AUDIO,0x00000018));
    d.bitc.gain = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)) = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG2_GAIN(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)));

    tmp_value.all = value;
    return tmp_value.bitc.gain;
}
GH_INLINE void GH_AUDIO_set_MMP_DPGA_CFG2_GAIN_TRIG(U8 index, U8 data)
{
    GH_AUDIO_MMP_DPGA_CFG2_REAL_S d;
    d.all = *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2_REAL + index * FIO_MOFFSET(AUDIO,0x00000018));
    d.bitc.gain_trig = data;
    *(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)) = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MMP_DPGA_CFG2_GAIN_TRIG(U8 index)
{
    GH_AUDIO_MMP_DPGA_CFG2_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)(REG_AUDIO_MMP_DPGA_CFG2_REAL + index * FIO_MOFFSET(AUDIO,0x00000018)));

    tmp_value.all = value;
    return tmp_value.bitc.gain_trig;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_MIX_CTRL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_MIX_CTRL0(U16 data)
{
    GH_AUDIO_MIX_CTRL0_REAL_S real;
    GH_AUDIO_MIX_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.ch2_mux_sel = dummy.bitc.ch2_mux_sel;
    real.bitc.ch1_mux_sel = dummy.bitc.ch1_mux_sel;
    real.bitc.sel_dec2_dout = dummy.bitc.sel_dec2_dout;
    real.bitc.sel_dec1_dout = dummy.bitc.sel_dec1_dout;
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_MIX_CTRL0(void)
{
    GH_AUDIO_MIX_CTRL0_REAL_S real;
    GH_AUDIO_MIX_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL);

    dummy.bitc.ch2_mux_sel = real.bitc.ch2_mux_sel;
    dummy.bitc.ch1_mux_sel = real.bitc.ch1_mux_sel;
    dummy.bitc.sel_dec2_dout = real.bitc.sel_dec2_dout;
    dummy.bitc.sel_dec1_dout = real.bitc.sel_dec1_dout;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_MIX_CTRL0_CH2_MUX_SEL(U8 data)
{
    GH_AUDIO_MIX_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL;
    d.bitc.ch2_mux_sel = data;
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MIX_CTRL0_CH2_MUX_SEL(void)
{
    GH_AUDIO_MIX_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ch2_mux_sel;
}
GH_INLINE void GH_AUDIO_set_MIX_CTRL0_CH1_MUX_SEL(U8 data)
{
    GH_AUDIO_MIX_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL;
    d.bitc.ch1_mux_sel = data;
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MIX_CTRL0_CH1_MUX_SEL(void)
{
    GH_AUDIO_MIX_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ch1_mux_sel;
}
GH_INLINE void GH_AUDIO_set_MIX_CTRL0_SEL_DEC2_DOUT(U8 data)
{
    GH_AUDIO_MIX_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL;
    d.bitc.sel_dec2_dout = data;
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MIX_CTRL0_SEL_DEC2_DOUT(void)
{
    GH_AUDIO_MIX_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_dec2_dout;
}
GH_INLINE void GH_AUDIO_set_MIX_CTRL0_SEL_DEC1_DOUT(U8 data)
{
    GH_AUDIO_MIX_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL;
    d.bitc.sel_dec1_dout = data;
    *(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_MIX_CTRL0_SEL_DEC1_DOUT(void)
{
    GH_AUDIO_MIX_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_MIX_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_dec1_dout;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_INT_DOUT (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_INT_DOUT(U8 index)
{
    U16 value = (*(volatile U16 *)(REG_AUDIO_INT_DOUT_REAL + index * FIO_MOFFSET(AUDIO,0x00000008)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_FIFO_TH_CTRL0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_FIFO_TH_CTRL0(U16 data)
{
    GH_AUDIO_FIFO_TH_CTRL0_REAL_S real;
    GH_AUDIO_FIFO_TH_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.tx = dummy.bitc.tx;
    real.bitc.rx = dummy.bitc.rx;
    *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_FIFO_TH_CTRL0(void)
{
    GH_AUDIO_FIFO_TH_CTRL0_REAL_S real;
    GH_AUDIO_FIFO_TH_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0_REAL);

    dummy.bitc.tx = real.bitc.tx;
    dummy.bitc.rx = real.bitc.rx;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_FIFO_TH_CTRL0_TX(U8 data)
{
    GH_AUDIO_FIFO_TH_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0_REAL;
    d.bitc.tx = data;
    *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_TH_CTRL0_TX(void)
{
    GH_AUDIO_FIFO_TH_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tx;
}
GH_INLINE void GH_AUDIO_set_FIFO_TH_CTRL0_RX(U8 data)
{
    GH_AUDIO_FIFO_TH_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0_REAL;
    d.bitc.rx = data;
    *(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_TH_CTRL0_RX(void)
{
    GH_AUDIO_FIFO_TH_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_TH_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_TIMING_CTRL1 (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1(U16 data)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S real;
    GH_AUDIO_TIMING_CTRL1_S dummy;
    dummy.all = data ;
    real.bitc.dec_num2 = dummy.bitc.dec_num2;
    real.bitc.en_asrc3_p = dummy.bitc.en_asrc3_p;
    real.bitc.ch2_int_cnt_sync_sel = dummy.bitc.ch2_int_cnt_sync_sel;
    real.bitc.ch1_int_cnt_sync_sel = dummy.bitc.ch1_int_cnt_sync_sel;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_TIMING_CTRL1(void)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S real;
    GH_AUDIO_TIMING_CTRL1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL);

    dummy.bitc.dec_num2 = real.bitc.dec_num2;
    dummy.bitc.en_asrc3_p = real.bitc.en_asrc3_p;
    dummy.bitc.ch2_int_cnt_sync_sel = real.bitc.ch2_int_cnt_sync_sel;
    dummy.bitc.ch1_int_cnt_sync_sel = real.bitc.ch1_int_cnt_sync_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1_DEC_NUM2(U8 data)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL;
    d.bitc.dec_num2 = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL1_DEC_NUM2(void)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dec_num2;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1_EN_ASRC3_p(U8 data)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL;
    d.bitc.en_asrc3_p = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL1_EN_ASRC3_p(void)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_asrc3_p;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL;
    d.bitc.ch2_int_cnt_sync_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL(void)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ch2_int_cnt_sync_sel;
}
GH_INLINE void GH_AUDIO_set_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL(U8 data)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL;
    d.bitc.ch1_int_cnt_sync_sel = data;
    *(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL(void)
{
    GH_AUDIO_TIMING_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TIMING_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ch1_int_cnt_sync_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_CTRL1 (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL1(U16 data)
{
    GH_AUDIO_AUDIOBAND_CTRL1_REAL_S real;
    GH_AUDIO_AUDIOBAND_CTRL1_S dummy;
    dummy.all = data ;
    real.bitc.sdm_dwa_datain_r_sel = dummy.bitc.sdm_dwa_datain_r_sel;
    real.bitc.sdm_dwa_datain_l_sel = dummy.bitc.sdm_dwa_datain_l_sel;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_AUDIOBAND_CTRL1(void)
{
    GH_AUDIO_AUDIOBAND_CTRL1_REAL_S real;
    GH_AUDIO_AUDIOBAND_CTRL1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1_REAL);

    dummy.bitc.sdm_dwa_datain_r_sel = real.bitc.sdm_dwa_datain_r_sel;
    dummy.bitc.sdm_dwa_datain_l_sel = real.bitc.sdm_dwa_datain_l_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1_REAL;
    d.bitc.sdm_dwa_datain_r_sel = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_dwa_datain_r_sel;
}
GH_INLINE void GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL(U8 data)
{
    GH_AUDIO_AUDIOBAND_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1_REAL;
    d.bitc.sdm_dwa_datain_l_sel = data;
    *(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL(void)
{
    GH_AUDIO_AUDIOBAND_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_AUDIOBAND_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_dwa_datain_l_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_FIFO_CTRL (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_FIFO_CTRL(U16 data)
{
    GH_AUDIO_FIFO_CTRL_REAL_S real;
    GH_AUDIO_FIFO_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.tx_fifo_int_en = dummy.bitc.tx_fifo_int_en;
    real.bitc.tx_fifo_enable = dummy.bitc.tx_fifo_enable;
    real.bitc.tx_fifo_status_clr = dummy.bitc.tx_fifo_status_clr;
    real.bitc.rx_fifo_int_en = dummy.bitc.rx_fifo_int_en;
    real.bitc.rx_fifo_enable = dummy.bitc.rx_fifo_enable;
    real.bitc.rx_fifo_status_clr = dummy.bitc.rx_fifo_status_clr;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_FIFO_CTRL(void)
{
    GH_AUDIO_FIFO_CTRL_REAL_S real;
    GH_AUDIO_FIFO_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL);

    dummy.bitc.tx_fifo_int_en = real.bitc.tx_fifo_int_en;
    dummy.bitc.tx_fifo_enable = real.bitc.tx_fifo_enable;
    dummy.bitc.tx_fifo_status_clr = real.bitc.tx_fifo_status_clr;
    dummy.bitc.rx_fifo_int_en = real.bitc.rx_fifo_int_en;
    dummy.bitc.rx_fifo_enable = real.bitc.rx_fifo_enable;
    dummy.bitc.rx_fifo_status_clr = real.bitc.rx_fifo_status_clr;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_INT_EN(U8 data)
{
    GH_AUDIO_FIFO_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL;
    d.bitc.tx_fifo_int_en = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_INT_EN(void)
{
    GH_AUDIO_FIFO_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tx_fifo_int_en;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_ENABLE(U8 data)
{
    GH_AUDIO_FIFO_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL;
    d.bitc.tx_fifo_enable = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_ENABLE(void)
{
    GH_AUDIO_FIFO_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tx_fifo_enable;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_STATUS_CLR(U8 data)
{
    GH_AUDIO_FIFO_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL;
    d.bitc.tx_fifo_status_clr = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_STATUS_CLR(void)
{
    GH_AUDIO_FIFO_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tx_fifo_status_clr;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_INT_EN(U8 data)
{
    GH_AUDIO_FIFO_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL;
    d.bitc.rx_fifo_int_en = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_INT_EN(void)
{
    GH_AUDIO_FIFO_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_fifo_int_en;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_ENABLE(U8 data)
{
    GH_AUDIO_FIFO_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL;
    d.bitc.rx_fifo_enable = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_ENABLE(void)
{
    GH_AUDIO_FIFO_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_fifo_enable;
}
GH_INLINE void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_STATUS_CLR(U8 data)
{
    GH_AUDIO_FIFO_CTRL_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL;
    d.bitc.rx_fifo_status_clr = data;
    *(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_STATUS_CLR(void)
{
    GH_AUDIO_FIFO_CTRL_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_fifo_status_clr;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_FIFO_STS (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_FIFO_STS(void)
{
    GH_AUDIO_FIFO_STS_REAL_S real;
    GH_AUDIO_FIFO_STS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_FIFO_STS_REAL);

    dummy.bitc.tx_fifo_status = real.bitc.tx_fifo_status;
    dummy.bitc.rx_fifo_status = real.bitc.rx_fifo_status;
    return dummy.all;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_STS_TX_FIFO_STATUS(void)
{
    GH_AUDIO_FIFO_STS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tx_fifo_status;
}
GH_INLINE U8   GH_AUDIO_get_FIFO_STS_RX_FIFO_STATUS(void)
{
    GH_AUDIO_FIFO_STS_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_FIFO_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_fifo_status;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_5_NF_H (read)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_5_NF_H(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_5_NF_H_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_5_NF_L (read)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_NF_SYNTH_5_NF_L(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_NF_SYNTH_5_NF_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_INT_CTRL (read)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_AUDIO_get_INT_CTRL(void)
{
    U16 value = (*(volatile U16 *)REG_AUDIO_INT_CTRL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_SINE_GEN_CTRL0 (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0(U16 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S real;
    GH_AUDIO_SINE_GEN_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.ch1_sin_gen_en_p = dummy.bitc.ch1_sin_gen_en_p;
    real.bitc.ch2_sin_gen_en_p = dummy.bitc.ch2_sin_gen_en_p;
    real.bitc.en_dit_sine = dummy.bitc.en_dit_sine;
    real.bitc.en_dit_src = dummy.bitc.en_dit_src;
    real.bitc.pga2_swap = dummy.bitc.pga2_swap;
    real.bitc.pga1_swap = dummy.bitc.pga1_swap;
    real.bitc.int2_mix_ctrl = dummy.bitc.int2_mix_ctrl;
    real.bitc.int1_mix_ctrl = dummy.bitc.int1_mix_ctrl;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_SINE_GEN_CTRL0(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S real;
    GH_AUDIO_SINE_GEN_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL);

    dummy.bitc.ch1_sin_gen_en_p = real.bitc.ch1_sin_gen_en_p;
    dummy.bitc.ch2_sin_gen_en_p = real.bitc.ch2_sin_gen_en_p;
    dummy.bitc.en_dit_sine = real.bitc.en_dit_sine;
    dummy.bitc.en_dit_src = real.bitc.en_dit_src;
    dummy.bitc.pga2_swap = real.bitc.pga2_swap;
    dummy.bitc.pga1_swap = real.bitc.pga1_swap;
    dummy.bitc.int2_mix_ctrl = real.bitc.int2_mix_ctrl;
    dummy.bitc.int1_mix_ctrl = real.bitc.int1_mix_ctrl;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL;
    d.bitc.ch1_sin_gen_en_p = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ch1_sin_gen_en_p;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL;
    d.bitc.ch2_sin_gen_en_p = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ch2_sin_gen_en_p;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SINE(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL;
    d.bitc.en_dit_sine = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SINE(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dit_sine;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SRC(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL;
    d.bitc.en_dit_src = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SRC(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dit_src;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_PGA2_SWAP(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL;
    d.bitc.pga2_swap = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_PGA2_SWAP(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga2_swap;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_PGA1_SWAP(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL;
    d.bitc.pga1_swap = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_PGA1_SWAP(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_swap;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_INT2_MIX_CTRL(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL;
    d.bitc.int2_mix_ctrl = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_INT2_MIX_CTRL(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int2_mix_ctrl;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL0_INT1_MIX_CTRL(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL;
    d.bitc.int1_mix_ctrl = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL0_INT1_MIX_CTRL(void)
{
    GH_AUDIO_SINE_GEN_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int1_mix_ctrl;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_SINE_GEN_CTRL1 (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1(U16 data)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S real;
    GH_AUDIO_SINE_GEN_CTRL1_S dummy;
    dummy.all = data ;
    real.bitc.sine_gen_ch1_freq = dummy.bitc.sine_gen_ch1_freq;
    real.bitc.sine_gen_ch1_gain = dummy.bitc.sine_gen_ch1_gain;
    real.bitc.sine_gen_ch2_freq = dummy.bitc.sine_gen_ch2_freq;
    real.bitc.sine_gen_ch2_gain = dummy.bitc.sine_gen_ch2_gain;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_SINE_GEN_CTRL1(void)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S real;
    GH_AUDIO_SINE_GEN_CTRL1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL);

    dummy.bitc.sine_gen_ch1_freq = real.bitc.sine_gen_ch1_freq;
    dummy.bitc.sine_gen_ch1_gain = real.bitc.sine_gen_ch1_gain;
    dummy.bitc.sine_gen_ch2_freq = real.bitc.sine_gen_ch2_freq;
    dummy.bitc.sine_gen_ch2_gain = real.bitc.sine_gen_ch2_gain;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL;
    d.bitc.sine_gen_ch1_freq = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ(void)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sine_gen_ch1_freq;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL;
    d.bitc.sine_gen_ch1_gain = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN(void)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sine_gen_ch1_gain;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL;
    d.bitc.sine_gen_ch2_freq = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ(void)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sine_gen_ch2_freq;
}
GH_INLINE void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN(U8 data)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL;
    d.bitc.sine_gen_ch2_gain = data;
    *(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN(void)
{
    GH_AUDIO_SINE_GEN_CTRL1_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_SINE_GEN_CTRL1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sine_gen_ch2_gain;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_TEST_CTRL0 (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_TEST_CTRL0(U16 data)
{
    GH_AUDIO_TEST_CTRL0_REAL_S real;
    GH_AUDIO_TEST_CTRL0_S dummy;
    dummy.all = data ;
    real.bitc.dac_test_en = dummy.bitc.dac_test_en;
    real.bitc.sdm_test_en = dummy.bitc.sdm_test_en;
    real.bitc.sdm_sft_dis = dummy.bitc.sdm_sft_dis;
    real.bitc.sram_cg_en = dummy.bitc.sram_cg_en;
    real.bitc.testclk_sel = dummy.bitc.testclk_sel;
    real.bitc.testbus_sel = dummy.bitc.testbus_sel;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_TEST_CTRL0(void)
{
    GH_AUDIO_TEST_CTRL0_REAL_S real;
    GH_AUDIO_TEST_CTRL0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL);

    dummy.bitc.dac_test_en = real.bitc.dac_test_en;
    dummy.bitc.sdm_test_en = real.bitc.sdm_test_en;
    dummy.bitc.sdm_sft_dis = real.bitc.sdm_sft_dis;
    dummy.bitc.sram_cg_en = real.bitc.sram_cg_en;
    dummy.bitc.testclk_sel = real.bitc.testclk_sel;
    dummy.bitc.testbus_sel = real.bitc.testbus_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_DAC_TEST_EN(U8 data)
{
    GH_AUDIO_TEST_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL;
    d.bitc.dac_test_en = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_DAC_TEST_EN(void)
{
    GH_AUDIO_TEST_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dac_test_en;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_SDM_TEST_EN(U8 data)
{
    GH_AUDIO_TEST_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL;
    d.bitc.sdm_test_en = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_SDM_TEST_EN(void)
{
    GH_AUDIO_TEST_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_test_en;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_SDM_SFT_DIS(U8 data)
{
    GH_AUDIO_TEST_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL;
    d.bitc.sdm_sft_dis = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_SDM_SFT_DIS(void)
{
    GH_AUDIO_TEST_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_sft_dis;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_SRAM_CG_EN(U8 data)
{
    GH_AUDIO_TEST_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL;
    d.bitc.sram_cg_en = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_SRAM_CG_EN(void)
{
    GH_AUDIO_TEST_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sram_cg_en;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_TESTCLK_SEL(U8 data)
{
    GH_AUDIO_TEST_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL;
    d.bitc.testclk_sel = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_TESTCLK_SEL(void)
{
    GH_AUDIO_TEST_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.testclk_sel;
}
GH_INLINE void GH_AUDIO_set_TEST_CTRL0_TESTBUS_SEL(U8 data)
{
    GH_AUDIO_TEST_CTRL0_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL;
    d.bitc.testbus_sel = data;
    *(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_TEST_CTRL0_TESTBUS_SEL(void)
{
    GH_AUDIO_TEST_CTRL0_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_TEST_CTRL0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.testbus_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL00 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00(U16 data)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S real;
    GH_AUDIO_ANALOG_CTRL00_S dummy;
    dummy.all = data ;
    real.bitc.dbnc_time = dummy.bitc.dbnc_time;
    real.bitc.mcpls_sel = dummy.bitc.mcpls_sel;
    real.bitc.mcpls_prd = dummy.bitc.mcpls_prd;
    real.bitc._rstz_au_det = dummy.bitc._rstz_au_det;
    real.bitc.int_au_det_test_value = dummy.bitc.int_au_det_test_value;
    real.bitc.int_au_det_test_mode = dummy.bitc.int_au_det_test_mode;
    real.bitc.mcpls_en = dummy.bitc.mcpls_en;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL00(void)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S real;
    GH_AUDIO_ANALOG_CTRL00_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL);

    dummy.bitc.dbnc_time = real.bitc.dbnc_time;
    dummy.bitc.mcpls_sel = real.bitc.mcpls_sel;
    dummy.bitc.mcpls_prd = real.bitc.mcpls_prd;
    dummy.bitc._rstz_au_det = real.bitc._rstz_au_det;
    dummy.bitc.int_au_det_test_value = real.bitc.int_au_det_test_value;
    dummy.bitc.int_au_det_test_mode = real.bitc.int_au_det_test_mode;
    dummy.bitc.mcpls_en = real.bitc.mcpls_en;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_DBNC_TIME(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL;
    d.bitc.dbnc_time = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_DBNC_TIME(void)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dbnc_time;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL;
    d.bitc.mcpls_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mcpls_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_PRD(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL;
    d.bitc.mcpls_prd = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_PRD(void)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mcpls_prd;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00__RSTZ_AU_DET(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL;
    d.bitc._rstz_au_det = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00__RSTZ_AU_DET(void)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL);

    tmp_value.all = value;
    return tmp_value.bitc._rstz_au_det;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL;
    d.bitc.int_au_det_test_value = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE(void)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_au_det_test_value;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_MODE(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL;
    d.bitc.int_au_det_test_mode = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_MODE(void)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_au_det_test_mode;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_EN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL;
    d.bitc.mcpls_en = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_EN(void)
{
    GH_AUDIO_ANALOG_CTRL00_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL00_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mcpls_en;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL01 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01(U16 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S real;
    GH_AUDIO_ANALOG_CTRL01_S dummy;
    dummy.all = data ;
    real.bitc.int_mask_miclp_plugin = dummy.bitc.int_mask_miclp_plugin;
    real.bitc.int_mask_miclp_unplug = dummy.bitc.int_mask_miclp_unplug;
    real.bitc.int_mask_spk_plugin = dummy.bitc.int_mask_spk_plugin;
    real.bitc.int_mask_spk_unplug = dummy.bitc.int_mask_spk_unplug;
    real.bitc.int_mask_hs_plugin = dummy.bitc.int_mask_hs_plugin;
    real.bitc.int_mask_hs_unplug = dummy.bitc.int_mask_hs_unplug;
    real.bitc.int_mask_hs_gnd = dummy.bitc.int_mask_hs_gnd;
    real.bitc.int_clr_miclp_plugin = dummy.bitc.int_clr_miclp_plugin;
    real.bitc.int_clr_miclp_unplug = dummy.bitc.int_clr_miclp_unplug;
    real.bitc.int_clr_spk_plugin = dummy.bitc.int_clr_spk_plugin;
    real.bitc.int_clr_spk_unplug = dummy.bitc.int_clr_spk_unplug;
    real.bitc.int_clr_hs_plugin = dummy.bitc.int_clr_hs_plugin;
    real.bitc.int_clr_hs_unplug = dummy.bitc.int_clr_hs_unplug;
    real.bitc.int_clr_hs_gnc = dummy.bitc.int_clr_hs_gnc;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL01(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S real;
    GH_AUDIO_ANALOG_CTRL01_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    dummy.bitc.int_mask_miclp_plugin = real.bitc.int_mask_miclp_plugin;
    dummy.bitc.int_mask_miclp_unplug = real.bitc.int_mask_miclp_unplug;
    dummy.bitc.int_mask_spk_plugin = real.bitc.int_mask_spk_plugin;
    dummy.bitc.int_mask_spk_unplug = real.bitc.int_mask_spk_unplug;
    dummy.bitc.int_mask_hs_plugin = real.bitc.int_mask_hs_plugin;
    dummy.bitc.int_mask_hs_unplug = real.bitc.int_mask_hs_unplug;
    dummy.bitc.int_mask_hs_gnd = real.bitc.int_mask_hs_gnd;
    dummy.bitc.int_clr_miclp_plugin = real.bitc.int_clr_miclp_plugin;
    dummy.bitc.int_clr_miclp_unplug = real.bitc.int_clr_miclp_unplug;
    dummy.bitc.int_clr_spk_plugin = real.bitc.int_clr_spk_plugin;
    dummy.bitc.int_clr_spk_unplug = real.bitc.int_clr_spk_unplug;
    dummy.bitc.int_clr_hs_plugin = real.bitc.int_clr_hs_plugin;
    dummy.bitc.int_clr_hs_unplug = real.bitc.int_clr_hs_unplug;
    dummy.bitc.int_clr_hs_gnc = real.bitc.int_clr_hs_gnc;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_mask_miclp_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_mask_miclp_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_mask_miclp_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_mask_miclp_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_mask_spk_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_mask_spk_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_mask_spk_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_mask_spk_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_mask_hs_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_mask_hs_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_mask_hs_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_mask_hs_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_GND(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_mask_hs_gnd = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_GND(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_mask_hs_gnd;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_clr_miclp_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_clr_miclp_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_clr_miclp_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_clr_miclp_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_clr_spk_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_clr_spk_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_clr_spk_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_clr_spk_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_PLUGIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_clr_hs_plugin = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_PLUGIN(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_clr_hs_plugin;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_UNPLUG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_clr_hs_unplug = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_UNPLUG(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_clr_hs_unplug;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_GNC(U8 data)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL;
    d.bitc.int_clr_hs_gnc = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_GNC(void)
{
    GH_AUDIO_ANALOG_CTRL01_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL01_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.int_clr_hs_gnc;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL02 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02(U16 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S real;
    GH_AUDIO_ANALOG_CTRL02_S dummy;
    dummy.all = data ;
    real.bitc.sdm_out_3_4_12_sel = dummy.bitc.sdm_out_3_4_12_sel;
    real.bitc.sdm_out_1_2_12_sel = dummy.bitc.sdm_out_1_2_12_sel;
    real.bitc.sdm_out_3_4_12_swap_sel = dummy.bitc.sdm_out_3_4_12_swap_sel;
    real.bitc.sdm_out_1_2_12_swap_sel = dummy.bitc.sdm_out_1_2_12_swap_sel;
    real.bitc.sdm_out_4_12_inv_sel = dummy.bitc.sdm_out_4_12_inv_sel;
    real.bitc.sdm_out_3_12_inv_sel = dummy.bitc.sdm_out_3_12_inv_sel;
    real.bitc.sdm_out_2_12_inv_sel = dummy.bitc.sdm_out_2_12_inv_sel;
    real.bitc.sdm_out_1_12_inv_sel = dummy.bitc.sdm_out_1_12_inv_sel;
    real.bitc.dft_sel = dummy.bitc.dft_sel;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL02(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S real;
    GH_AUDIO_ANALOG_CTRL02_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    dummy.bitc.sdm_out_3_4_12_sel = real.bitc.sdm_out_3_4_12_sel;
    dummy.bitc.sdm_out_1_2_12_sel = real.bitc.sdm_out_1_2_12_sel;
    dummy.bitc.sdm_out_3_4_12_swap_sel = real.bitc.sdm_out_3_4_12_swap_sel;
    dummy.bitc.sdm_out_1_2_12_swap_sel = real.bitc.sdm_out_1_2_12_swap_sel;
    dummy.bitc.sdm_out_4_12_inv_sel = real.bitc.sdm_out_4_12_inv_sel;
    dummy.bitc.sdm_out_3_12_inv_sel = real.bitc.sdm_out_3_12_inv_sel;
    dummy.bitc.sdm_out_2_12_inv_sel = real.bitc.sdm_out_2_12_inv_sel;
    dummy.bitc.sdm_out_1_12_inv_sel = real.bitc.sdm_out_1_12_inv_sel;
    dummy.bitc.dft_sel = real.bitc.dft_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL;
    d.bitc.sdm_out_3_4_12_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_out_3_4_12_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL;
    d.bitc.sdm_out_1_2_12_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_out_1_2_12_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL;
    d.bitc.sdm_out_3_4_12_swap_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_out_3_4_12_swap_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL;
    d.bitc.sdm_out_1_2_12_swap_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_out_1_2_12_swap_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_4_12_inv_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL;
    d.bitc.sdm_out_4_12_inv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_4_12_inv_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_out_4_12_inv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_12_inv_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL;
    d.bitc.sdm_out_3_12_inv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_12_inv_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_out_3_12_inv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_2_12_inv_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL;
    d.bitc.sdm_out_2_12_inv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_2_12_inv_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_out_2_12_inv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_12_inv_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL;
    d.bitc.sdm_out_1_12_inv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_12_inv_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdm_out_1_12_inv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL02_dft_sel(U8 data)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL;
    d.bitc.dft_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL02_dft_sel(void)
{
    GH_AUDIO_ANALOG_CTRL02_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL02_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dft_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL03 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03(U16 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S real;
    GH_AUDIO_ANALOG_CTRL03_S dummy;
    dummy.all = data ;
    real.bitc.sel_irefdet = dummy.bitc.sel_irefdet;
    real.bitc.reg_en_micbias_12 = dummy.bitc.reg_en_micbias_12;
    real.bitc.micv_sel = dummy.bitc.micv_sel;
    real.bitc.rcv_en_12 = dummy.bitc.rcv_en_12;
    real.bitc.hst_en_12 = dummy.bitc.hst_en_12;
    real.bitc.en_micdet_12 = dummy.bitc.en_micdet_12;
    real.bitc.reg_control = dummy.bitc.reg_control;
    real.bitc.reg_sel_control = dummy.bitc.reg_sel_control;
    real.bitc.en_ref_no_bg_12 = dummy.bitc.en_ref_no_bg_12;
    real.bitc.en_polling_drv_12 = dummy.bitc.en_polling_drv_12;
    real.bitc.ibsel_audio = dummy.bitc.ibsel_audio;
    real.bitc.en_audio_ibias_12 = dummy.bitc.en_audio_ibias_12;
    real.bitc.en_clk_tst = dummy.bitc.en_clk_tst;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL03(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S real;
    GH_AUDIO_ANALOG_CTRL03_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    dummy.bitc.sel_irefdet = real.bitc.sel_irefdet;
    dummy.bitc.reg_en_micbias_12 = real.bitc.reg_en_micbias_12;
    dummy.bitc.micv_sel = real.bitc.micv_sel;
    dummy.bitc.rcv_en_12 = real.bitc.rcv_en_12;
    dummy.bitc.hst_en_12 = real.bitc.hst_en_12;
    dummy.bitc.en_micdet_12 = real.bitc.en_micdet_12;
    dummy.bitc.reg_control = real.bitc.reg_control;
    dummy.bitc.reg_sel_control = real.bitc.reg_sel_control;
    dummy.bitc.en_ref_no_bg_12 = real.bitc.en_ref_no_bg_12;
    dummy.bitc.en_polling_drv_12 = real.bitc.en_polling_drv_12;
    dummy.bitc.ibsel_audio = real.bitc.ibsel_audio;
    dummy.bitc.en_audio_ibias_12 = real.bitc.en_audio_ibias_12;
    dummy.bitc.en_clk_tst = real.bitc.en_clk_tst;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_SEL_IREFDET(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.sel_irefdet = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_SEL_IREFDET(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_irefdet;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_REG_EN_MICBIAS_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.reg_en_micbias_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_REG_EN_MICBIAS_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reg_en_micbias_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_MICV_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.micv_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_MICV_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.micv_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_RCV_EN_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.rcv_en_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_RCV_EN_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rcv_en_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_HST_EN_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.hst_en_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_HST_EN_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hst_en_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_MICDET_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.en_micdet_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_MICDET_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_micdet_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_REG_CONTROL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.reg_control = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_REG_CONTROL(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reg_control;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_REG_SEL_CONTROL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.reg_sel_control = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_REG_SEL_CONTROL(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reg_sel_control;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_REF_NO_BG_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.en_ref_no_bg_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_REF_NO_BG_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_ref_no_bg_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_POLLING_DRV_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.en_polling_drv_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_POLLING_DRV_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_polling_drv_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_IBSEL_AUDIO(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.ibsel_audio = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_IBSEL_AUDIO(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ibsel_audio;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_AUDIO_IBIAS_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.en_audio_ibias_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_AUDIO_IBIAS_12(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_audio_ibias_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL03_EN_CLK_TST(U8 data)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL;
    d.bitc.en_clk_tst = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL03_EN_CLK_TST(void)
{
    GH_AUDIO_ANALOG_CTRL03_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL03_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_clk_tst;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL04 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04(U16 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S real;
    GH_AUDIO_ANALOG_CTRL04_S dummy;
    dummy.all = data ;
    real.bitc.pga0_mica2sel = dummy.bitc.pga0_mica2sel;
    real.bitc.pga0_mica2_gain = dummy.bitc.pga0_mica2_gain;
    real.bitc.en_pga0_mica2 = dummy.bitc.en_pga0_mica2;
    real.bitc.pga0_mica1_gain = dummy.bitc.pga0_mica1_gain;
    real.bitc.en_pga0_mica1 = dummy.bitc.en_pga0_mica1;
    real.bitc.ibias_pga0 = dummy.bitc.ibias_pga0;
    real.bitc.en_ibias_pga0 = dummy.bitc.en_ibias_pga0;
    real.bitc.en_vcmbuf0_12 = dummy.bitc.en_vcmbuf0_12;
    real.bitc.sel_vcmref0 = dummy.bitc.sel_vcmref0;
    real.bitc.pullup_hsip = dummy.bitc.pullup_hsip;
    real.bitc.en_micdet_lp_12 = dummy.bitc.en_micdet_lp_12;
    real.bitc.en_mictrim_12 = dummy.bitc.en_mictrim_12;
    real.bitc.sel_irefgnd = dummy.bitc.sel_irefgnd;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL04(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S real;
    GH_AUDIO_ANALOG_CTRL04_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    dummy.bitc.pga0_mica2sel = real.bitc.pga0_mica2sel;
    dummy.bitc.pga0_mica2_gain = real.bitc.pga0_mica2_gain;
    dummy.bitc.en_pga0_mica2 = real.bitc.en_pga0_mica2;
    dummy.bitc.pga0_mica1_gain = real.bitc.pga0_mica1_gain;
    dummy.bitc.en_pga0_mica1 = real.bitc.en_pga0_mica1;
    dummy.bitc.ibias_pga0 = real.bitc.ibias_pga0;
    dummy.bitc.en_ibias_pga0 = real.bitc.en_ibias_pga0;
    dummy.bitc.en_vcmbuf0_12 = real.bitc.en_vcmbuf0_12;
    dummy.bitc.sel_vcmref0 = real.bitc.sel_vcmref0;
    dummy.bitc.pullup_hsip = real.bitc.pullup_hsip;
    dummy.bitc.en_micdet_lp_12 = real.bitc.en_micdet_lp_12;
    dummy.bitc.en_mictrim_12 = real.bitc.en_mictrim_12;
    dummy.bitc.sel_irefgnd = real.bitc.sel_irefgnd;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.pga0_mica2sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2SEL(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_mica2sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.pga0_mica2_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_mica2_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA2(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.en_pga0_mica2 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA2(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_pga0_mica2;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA1_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.pga0_mica1_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA1_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_mica1_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.en_pga0_mica1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA1(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_pga0_mica1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_IBIAS_PGA0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.ibias_pga0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_IBIAS_PGA0(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ibias_pga0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_IBIAS_PGA0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.en_ibias_pga0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_IBIAS_PGA0(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_ibias_pga0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_VCMBUF0_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.en_vcmbuf0_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_VCMBUF0_12(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_vcmbuf0_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_SEL_VCMREF0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.sel_vcmref0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_SEL_VCMREF0(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_vcmref0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_PULLUP_HSIP(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.pullup_hsip = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_PULLUP_HSIP(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pullup_hsip;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_MICDET_LP_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.en_micdet_lp_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_MICDET_LP_12(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_micdet_lp_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_EN_MICTRIM_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.en_mictrim_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_EN_MICTRIM_12(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_mictrim_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL04_SEL_IREFGND(U8 data)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL;
    d.bitc.sel_irefgnd = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL04_SEL_IREFGND(void)
{
    GH_AUDIO_ANALOG_CTRL04_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL04_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_irefgnd;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL05 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05(U16 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S real;
    GH_AUDIO_ANALOG_CTRL05_S dummy;
    dummy.all = data ;
    real.bitc.ibias_pga1 = dummy.bitc.ibias_pga1;
    real.bitc.en_ibias_pga1 = dummy.bitc.en_ibias_pga1;
    real.bitc.en_vcmbuf1 = dummy.bitc.en_vcmbuf1;
    real.bitc.sel_vcmref1 = dummy.bitc.sel_vcmref1;
    real.bitc.pga0_line_sel = dummy.bitc.pga0_line_sel;
    real.bitc.pga0_mute_r = dummy.bitc.pga0_mute_r;
    real.bitc.pga0_mica4_sel = dummy.bitc.pga0_mica4_sel;
    real.bitc.pga0_mica4_gain = dummy.bitc.pga0_mica4_gain;
    real.bitc.en_pga0_mica4 = dummy.bitc.en_pga0_mica4;
    real.bitc.pga0_mica3_gain = dummy.bitc.pga0_mica3_gain;
    real.bitc.en_pga0_mica3 = dummy.bitc.en_pga0_mica3;
    real.bitc.pga0_mute_l = dummy.bitc.pga0_mute_l;
    real.bitc.pga0_mica2sel = dummy.bitc.pga0_mica2sel;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL05(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S real;
    GH_AUDIO_ANALOG_CTRL05_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    dummy.bitc.ibias_pga1 = real.bitc.ibias_pga1;
    dummy.bitc.en_ibias_pga1 = real.bitc.en_ibias_pga1;
    dummy.bitc.en_vcmbuf1 = real.bitc.en_vcmbuf1;
    dummy.bitc.sel_vcmref1 = real.bitc.sel_vcmref1;
    dummy.bitc.pga0_line_sel = real.bitc.pga0_line_sel;
    dummy.bitc.pga0_mute_r = real.bitc.pga0_mute_r;
    dummy.bitc.pga0_mica4_sel = real.bitc.pga0_mica4_sel;
    dummy.bitc.pga0_mica4_gain = real.bitc.pga0_mica4_gain;
    dummy.bitc.en_pga0_mica4 = real.bitc.en_pga0_mica4;
    dummy.bitc.pga0_mica3_gain = real.bitc.pga0_mica3_gain;
    dummy.bitc.en_pga0_mica3 = real.bitc.en_pga0_mica3;
    dummy.bitc.pga0_mute_l = real.bitc.pga0_mute_l;
    dummy.bitc.pga0_mica2sel = real.bitc.pga0_mica2sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_IBIAS_PGA1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.ibias_pga1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_IBIAS_PGA1(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ibias_pga1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_EN_IBIAS_PGA1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.en_ibias_pga1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_EN_IBIAS_PGA1(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_ibias_pga1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_EN_VCMBUF1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.en_vcmbuf1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_EN_VCMBUF1(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_vcmbuf1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_SEL_VCMREF1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.sel_vcmref1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_SEL_VCMREF1(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_vcmref1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_LINE_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.pga0_line_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_LINE_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_line_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.pga0_mute_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_R(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_mute_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.pga0_mica4_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_mica4_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.pga0_mica4_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_mica4_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA4(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.en_pga0_mica4 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA4(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_pga0_mica4;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA3_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.pga0_mica3_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA3_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_mica3_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA3(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.en_pga0_mica3 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA3(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_pga0_mica3;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.pga0_mute_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_L(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_mute_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA2SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL;
    d.bitc.pga0_mica2sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA2SEL(void)
{
    GH_AUDIO_ANALOG_CTRL05_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL05_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga0_mica2sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL06 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06(U16 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S real;
    GH_AUDIO_ANALOG_CTRL06_S dummy;
    dummy.all = data ;
    real.bitc.en_dac0_r_12 = dummy.bitc.en_dac0_r_12;
    real.bitc.en_dac0_l_12 = dummy.bitc.en_dac0_l_12;
    real.bitc.en_dac0_ldo11 = dummy.bitc.en_dac0_ldo11;
    real.bitc.ldo11_vc0 = dummy.bitc.ldo11_vc0;
    real.bitc.pos_rl0 = dummy.bitc.pos_rl0;
    real.bitc.pga1_line_sel = dummy.bitc.pga1_line_sel;
    real.bitc.pga1_mute_r = dummy.bitc.pga1_mute_r;
    real.bitc.pga1_mica4_gain = dummy.bitc.pga1_mica4_gain;
    real.bitc.en_pga1_mica4 = dummy.bitc.en_pga1_mica4;
    real.bitc.pga1_mute_l = dummy.bitc.pga1_mute_l;
    real.bitc.pga1_mica2_gain = dummy.bitc.pga1_mica2_gain;
    real.bitc.en_pga1_mica2 = dummy.bitc.en_pga1_mica2;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL06(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S real;
    GH_AUDIO_ANALOG_CTRL06_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    dummy.bitc.en_dac0_r_12 = real.bitc.en_dac0_r_12;
    dummy.bitc.en_dac0_l_12 = real.bitc.en_dac0_l_12;
    dummy.bitc.en_dac0_ldo11 = real.bitc.en_dac0_ldo11;
    dummy.bitc.ldo11_vc0 = real.bitc.ldo11_vc0;
    dummy.bitc.pos_rl0 = real.bitc.pos_rl0;
    dummy.bitc.pga1_line_sel = real.bitc.pga1_line_sel;
    dummy.bitc.pga1_mute_r = real.bitc.pga1_mute_r;
    dummy.bitc.pga1_mica4_gain = real.bitc.pga1_mica4_gain;
    dummy.bitc.en_pga1_mica4 = real.bitc.en_pga1_mica4;
    dummy.bitc.pga1_mute_l = real.bitc.pga1_mute_l;
    dummy.bitc.pga1_mica2_gain = real.bitc.pga1_mica2_gain;
    dummy.bitc.en_pga1_mica2 = real.bitc.en_pga1_mica2;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_R_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.en_dac0_r_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_R_12(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dac0_r_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_L_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.en_dac0_l_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_L_12(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dac0_l_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_LDO11(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.en_dac0_ldo11 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_LDO11(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dac0_ldo11;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_LDO11_VC0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.ldo11_vc0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_LDO11_VC0(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ldo11_vc0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_POS_RL0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.pos_rl0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_POS_RL0(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pos_rl0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_LINE_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.pga1_line_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_LINE_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_line_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.pga1_mute_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_R(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_mute_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA4_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.pga1_mica4_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA4_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_mica4_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA4(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.en_pga1_mica4 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA4(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_pga1_mica4;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.pga1_mute_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_L(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_mute_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA2_GAIN(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.pga1_mica2_gain = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA2_GAIN(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pga1_mica2_gain;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA2(U8 data)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL;
    d.bitc.en_pga1_mica2 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA2(void)
{
    GH_AUDIO_ANALOG_CTRL06_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL06_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_pga1_mica2;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL07 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07(U16 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S real;
    GH_AUDIO_ANALOG_CTRL07_S dummy;
    dummy.all = data ;
    real.bitc.en_adc1_dit = dummy.bitc.en_adc1_dit;
    real.bitc.en_adc0_12 = dummy.bitc.en_adc0_12;
    real.bitc.shrt_adc0_l = dummy.bitc.shrt_adc0_l;
    real.bitc.shrt_adc0_r = dummy.bitc.shrt_adc0_r;
    real.bitc.reset_adc0_l = dummy.bitc.reset_adc0_l;
    real.bitc.reset_adc0_r = dummy.bitc.reset_adc0_r;
    real.bitc.sel_ibias_adc0 = dummy.bitc.sel_ibias_adc0;
    real.bitc.sel_dit_lvl_adc0 = dummy.bitc.sel_dit_lvl_adc0;
    real.bitc.en_adc0_dit = dummy.bitc.en_adc0_dit;
    real.bitc.en_dac1_r_12 = dummy.bitc.en_dac1_r_12;
    real.bitc.en_dac1_l_12 = dummy.bitc.en_dac1_l_12;
    real.bitc.en_dac1_ldo11 = dummy.bitc.en_dac1_ldo11;
    real.bitc.ldo11_vc1 = dummy.bitc.ldo11_vc1;
    real.bitc.pos_rl1 = dummy.bitc.pos_rl1;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL07(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S real;
    GH_AUDIO_ANALOG_CTRL07_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    dummy.bitc.en_adc1_dit = real.bitc.en_adc1_dit;
    dummy.bitc.en_adc0_12 = real.bitc.en_adc0_12;
    dummy.bitc.shrt_adc0_l = real.bitc.shrt_adc0_l;
    dummy.bitc.shrt_adc0_r = real.bitc.shrt_adc0_r;
    dummy.bitc.reset_adc0_l = real.bitc.reset_adc0_l;
    dummy.bitc.reset_adc0_r = real.bitc.reset_adc0_r;
    dummy.bitc.sel_ibias_adc0 = real.bitc.sel_ibias_adc0;
    dummy.bitc.sel_dit_lvl_adc0 = real.bitc.sel_dit_lvl_adc0;
    dummy.bitc.en_adc0_dit = real.bitc.en_adc0_dit;
    dummy.bitc.en_dac1_r_12 = real.bitc.en_dac1_r_12;
    dummy.bitc.en_dac1_l_12 = real.bitc.en_dac1_l_12;
    dummy.bitc.en_dac1_ldo11 = real.bitc.en_dac1_ldo11;
    dummy.bitc.ldo11_vc1 = real.bitc.ldo11_vc1;
    dummy.bitc.pos_rl1 = real.bitc.pos_rl1;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC1_DIT(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.en_adc1_dit = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC1_DIT(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_adc1_dit;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.en_adc0_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_12(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_adc0_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.shrt_adc0_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_L(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.shrt_adc0_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.shrt_adc0_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_R(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.shrt_adc0_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.reset_adc0_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_L(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset_adc0_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.reset_adc0_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_R(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset_adc0_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_SEL_IBIAS_ADC0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.sel_ibias_adc0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_SEL_IBIAS_ADC0(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_ibias_adc0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_SEL_DIT_LVL_ADC0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.sel_dit_lvl_adc0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_SEL_DIT_LVL_ADC0(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_dit_lvl_adc0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_DIT(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.en_adc0_dit = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_DIT(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_adc0_dit;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_R_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.en_dac1_r_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_R_12(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dac1_r_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_L_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.en_dac1_l_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_L_12(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dac1_l_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_LDO11(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.en_dac1_ldo11 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_LDO11(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_dac1_ldo11;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_LDO11_VC1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.ldo11_vc1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_LDO11_VC1(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ldo11_vc1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL07_POS_RL1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL;
    d.bitc.pos_rl1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL07_POS_RL1(void)
{
    GH_AUDIO_ANALOG_CTRL07_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL07_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pos_rl1;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL08 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08(U16 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S real;
    GH_AUDIO_ANALOG_CTRL08_S dummy;
    dummy.all = data ;
    real.bitc.gain_ear = dummy.bitc.gain_ear;
    real.bitc.en_stg2ab_12 = dummy.bitc.en_stg2ab_12;
    real.bitc.en_oplp_12 = dummy.bitc.en_oplp_12;
    real.bitc.en_earl_12 = dummy.bitc.en_earl_12;
    real.bitc.en_earr_12 = dummy.bitc.en_earr_12;
    real.bitc.en_adc1_12 = dummy.bitc.en_adc1_12;
    real.bitc.shrt_adc1_l = dummy.bitc.shrt_adc1_l;
    real.bitc.shrt_adc1_r = dummy.bitc.shrt_adc1_r;
    real.bitc.reset_adc1_l = dummy.bitc.reset_adc1_l;
    real.bitc.reset_adc1_r = dummy.bitc.reset_adc1_r;
    real.bitc.sel_ibias_adc1 = dummy.bitc.sel_ibias_adc1;
    real.bitc.sel_dit_lvl_adc1 = dummy.bitc.sel_dit_lvl_adc1;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL08(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S real;
    GH_AUDIO_ANALOG_CTRL08_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    dummy.bitc.gain_ear = real.bitc.gain_ear;
    dummy.bitc.en_stg2ab_12 = real.bitc.en_stg2ab_12;
    dummy.bitc.en_oplp_12 = real.bitc.en_oplp_12;
    dummy.bitc.en_earl_12 = real.bitc.en_earl_12;
    dummy.bitc.en_earr_12 = real.bitc.en_earr_12;
    dummy.bitc.en_adc1_12 = real.bitc.en_adc1_12;
    dummy.bitc.shrt_adc1_l = real.bitc.shrt_adc1_l;
    dummy.bitc.shrt_adc1_r = real.bitc.shrt_adc1_r;
    dummy.bitc.reset_adc1_l = real.bitc.reset_adc1_l;
    dummy.bitc.reset_adc1_r = real.bitc.reset_adc1_r;
    dummy.bitc.sel_ibias_adc1 = real.bitc.sel_ibias_adc1;
    dummy.bitc.sel_dit_lvl_adc1 = real.bitc.sel_dit_lvl_adc1;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_GAIN_EAR(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.gain_ear = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_GAIN_EAR(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gain_ear;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_STG2AB_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.en_stg2ab_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_STG2AB_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_stg2ab_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_OPLP_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.en_oplp_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_OPLP_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_oplp_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_EARL_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.en_earl_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_EARL_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_earl_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_EARR_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.en_earr_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_EARR_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_earr_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_EN_ADC1_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.en_adc1_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_EN_ADC1_12(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_adc1_12;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.shrt_adc1_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_L(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.shrt_adc1_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.shrt_adc1_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_R(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.shrt_adc1_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.reset_adc1_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_L(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset_adc1_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.reset_adc1_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_R(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset_adc1_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_SEL_IBIAS_ADC1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.sel_ibias_adc1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_SEL_IBIAS_ADC1(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_ibias_adc1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL08_SEL_DIT_LVL_ADC1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL;
    d.bitc.sel_dit_lvl_adc1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL08_SEL_DIT_LVL_ADC1(void)
{
    GH_AUDIO_ANALOG_CTRL08_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL08_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_dit_lvl_adc1;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL09 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09(U16 data)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S real;
    GH_AUDIO_ANALOG_CTRL09_S dummy;
    dummy.all = data ;
    real.bitc.mx_ear = dummy.bitc.mx_ear;
    real.bitc.isel_ocp = dummy.bitc.isel_ocp;
    real.bitc.isel_drv = dummy.bitc.isel_drv;
    real.bitc.tst_drv = dummy.bitc.tst_drv;
    real.bitc.ear_mute = dummy.bitc.ear_mute;
    real.bitc.ear_popres = dummy.bitc.ear_popres;
    real.bitc.tcsel = dummy.bitc.tcsel;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL09(void)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S real;
    GH_AUDIO_ANALOG_CTRL09_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL);

    dummy.bitc.mx_ear = real.bitc.mx_ear;
    dummy.bitc.isel_ocp = real.bitc.isel_ocp;
    dummy.bitc.isel_drv = real.bitc.isel_drv;
    dummy.bitc.tst_drv = real.bitc.tst_drv;
    dummy.bitc.ear_mute = real.bitc.ear_mute;
    dummy.bitc.ear_popres = real.bitc.ear_popres;
    dummy.bitc.tcsel = real.bitc.tcsel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_MX_EAR(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL;
    d.bitc.mx_ear = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_MX_EAR(void)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mx_ear;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_ISEL_OCP(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL;
    d.bitc.isel_ocp = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_ISEL_OCP(void)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.isel_ocp;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_ISEL_DRV(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL;
    d.bitc.isel_drv = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_ISEL_DRV(void)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.isel_drv;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_TST_DRV(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL;
    d.bitc.tst_drv = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_TST_DRV(void)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tst_drv;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_EAR_MUTE(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL;
    d.bitc.ear_mute = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_EAR_MUTE(void)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ear_mute;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_EAR_POPRES(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL;
    d.bitc.ear_popres = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_EAR_POPRES(void)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ear_popres;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL09_TCSEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL;
    d.bitc.tcsel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL09_TCSEL(void)
{
    GH_AUDIO_ANALOG_CTRL09_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL09_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tcsel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL10 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10(U16 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S real;
    GH_AUDIO_ANALOG_CTRL10_S dummy;
    dummy.all = data ;
    real.bitc.mute_line1 = dummy.bitc.mute_line1;
    real.bitc.mx_line1 = dummy.bitc.mx_line1;
    real.bitc.gain_line1 = dummy.bitc.gain_line1;
    real.bitc.en_line1_r = dummy.bitc.en_line1_r;
    real.bitc.en_line1_l = dummy.bitc.en_line1_l;
    real.bitc.mute_line0 = dummy.bitc.mute_line0;
    real.bitc.mx_line0 = dummy.bitc.mx_line0;
    real.bitc.gain_line0 = dummy.bitc.gain_line0;
    real.bitc.en_line0_r = dummy.bitc.en_line0_r;
    real.bitc.en_line0_l = dummy.bitc.en_line0_l;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL10(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S real;
    GH_AUDIO_ANALOG_CTRL10_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    dummy.bitc.mute_line1 = real.bitc.mute_line1;
    dummy.bitc.mx_line1 = real.bitc.mx_line1;
    dummy.bitc.gain_line1 = real.bitc.gain_line1;
    dummy.bitc.en_line1_r = real.bitc.en_line1_r;
    dummy.bitc.en_line1_l = real.bitc.en_line1_l;
    dummy.bitc.mute_line0 = real.bitc.mute_line0;
    dummy.bitc.mx_line0 = real.bitc.mx_line0;
    dummy.bitc.gain_line0 = real.bitc.gain_line0;
    dummy.bitc.en_line0_r = real.bitc.en_line0_r;
    dummy.bitc.en_line0_l = real.bitc.en_line0_l;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.mute_line1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE1(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mute_line1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_MX_LINE1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.mx_line1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_MX_LINE1(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mx_line1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE1(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.gain_line1 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE1(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gain_line1;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.en_line1_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_R(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_line1_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.en_line1_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_L(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_line1_l;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.mute_line0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE0(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mute_line0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_MX_LINE0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.mx_line0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_MX_LINE0(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mx_line0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE0(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.gain_line0 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE0(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gain_line0;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_R(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.en_line0_r = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_R(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_line0_r;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_L(U8 data)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL;
    d.bitc.en_line0_l = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_L(void)
{
    GH_AUDIO_ANALOG_CTRL10_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_line0_l;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL11 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11(U16 data)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S real;
    GH_AUDIO_ANALOG_CTRL11_S dummy;
    dummy.all = data ;
    real.bitc.tst_autio = dummy.bitc.tst_autio;
    real.bitc.sel_ck_audio = dummy.bitc.sel_ck_audio;
    real.bitc.sel_phs_adcclk = dummy.bitc.sel_phs_adcclk;
    real.bitc.adc_clk_freq = dummy.bitc.adc_clk_freq;
    real.bitc.dac_clk_freq = dummy.bitc.dac_clk_freq;
    real.bitc.en_clk = dummy.bitc.en_clk;
    real.bitc.v_set_ldo25 = dummy.bitc.v_set_ldo25;
    real.bitc.en_ldo25_12 = dummy.bitc.en_ldo25_12;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL11(void)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S real;
    GH_AUDIO_ANALOG_CTRL11_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL);

    dummy.bitc.tst_autio = real.bitc.tst_autio;
    dummy.bitc.sel_ck_audio = real.bitc.sel_ck_audio;
    dummy.bitc.sel_phs_adcclk = real.bitc.sel_phs_adcclk;
    dummy.bitc.adc_clk_freq = real.bitc.adc_clk_freq;
    dummy.bitc.dac_clk_freq = real.bitc.dac_clk_freq;
    dummy.bitc.en_clk = real.bitc.en_clk;
    dummy.bitc.v_set_ldo25 = real.bitc.v_set_ldo25;
    dummy.bitc.en_ldo25_12 = real.bitc.en_ldo25_12;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_TST_AUTIO(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL;
    d.bitc.tst_autio = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_TST_AUTIO(void)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tst_autio;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_SEL_CK_AUDIO(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL;
    d.bitc.sel_ck_audio = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_SEL_CK_AUDIO(void)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_ck_audio;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_SEL_PHS_ADCCLK(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL;
    d.bitc.sel_phs_adcclk = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_SEL_PHS_ADCCLK(void)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sel_phs_adcclk;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_ADC_CLK_FREQ(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL;
    d.bitc.adc_clk_freq = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_ADC_CLK_FREQ(void)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adc_clk_freq;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_DAC_CLK_FREQ(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL;
    d.bitc.dac_clk_freq = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_DAC_CLK_FREQ(void)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dac_clk_freq;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_EN_CLK(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL;
    d.bitc.en_clk = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_EN_CLK(void)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_clk;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_V_SET_LDO25(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL;
    d.bitc.v_set_ldo25 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_V_SET_LDO25(void)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.v_set_ldo25;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL11_EN_LDO25_12(U8 data)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL;
    d.bitc.en_ldo25_12 = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL11_EN_LDO25_12(void)
{
    GH_AUDIO_ANALOG_CTRL11_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL11_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.en_ldo25_12;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL12 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL12(U16 data)
{
    GH_AUDIO_ANALOG_CTRL12_REAL_S real;
    GH_AUDIO_ANALOG_CTRL12_S dummy;
    dummy.all = data ;
    real.bitc.audio_reg = dummy.bitc.audio_reg;
    real.bitc.test_bus_sel = dummy.bitc.test_bus_sel;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL12(void)
{
    GH_AUDIO_ANALOG_CTRL12_REAL_S real;
    GH_AUDIO_ANALOG_CTRL12_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL12_REAL);

    dummy.bitc.audio_reg = real.bitc.audio_reg;
    dummy.bitc.test_bus_sel = real.bitc.test_bus_sel;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL12_AUDIO_REG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL12_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12_REAL;
    d.bitc.audio_reg = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL12_AUDIO_REG(void)
{
    GH_AUDIO_ANALOG_CTRL12_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL12_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.audio_reg;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL12_TEST_BUS_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL12_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12_REAL;
    d.bitc.test_bus_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL12_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL12_TEST_BUS_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL12_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL12_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.test_bus_sel;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL13 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13(U16 data)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S real;
    GH_AUDIO_ANALOG_CTRL13_S dummy;
    dummy.all = data ;
    real.bitc.mic_trim_sel_cfg = dummy.bitc.mic_trim_sel_cfg;
    real.bitc.trim_stop_sel = dummy.bitc.trim_stop_sel;
    real.bitc.rstz_trim_au = dummy.bitc.rstz_trim_au;
    real.bitc.trim_au_sel = dummy.bitc.trim_au_sel;
    real.bitc.trim_stop = dummy.bitc.trim_stop;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL13(void)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S real;
    GH_AUDIO_ANALOG_CTRL13_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL);

    dummy.bitc.mic_trim_sel_cfg = real.bitc.mic_trim_sel_cfg;
    dummy.bitc.trim_stop_sel = real.bitc.trim_stop_sel;
    dummy.bitc.rstz_trim_au = real.bitc.rstz_trim_au;
    dummy.bitc.trim_au_sel = real.bitc.trim_au_sel;
    dummy.bitc.trim_stop = real.bitc.trim_stop;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_MIC_TRIM_SEL_CFG(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL;
    d.bitc.mic_trim_sel_cfg = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_MIC_TRIM_SEL_CFG(void)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mic_trim_sel_cfg;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL;
    d.bitc.trim_stop_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.trim_stop_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_RSTZ_TRIM_AU(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL;
    d.bitc.rstz_trim_au = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_RSTZ_TRIM_AU(void)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rstz_trim_au;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_TRIM_AU_SEL(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL;
    d.bitc.trim_au_sel = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_AU_SEL(void)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.trim_au_sel;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP(U8 data)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL;
    d.bitc.trim_stop = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL = d.all;
}
GH_INLINE U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP(void)
{
    GH_AUDIO_ANALOG_CTRL13_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL13_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.trim_stop;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL14 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL14(U16 data)
{
    GH_AUDIO_ANALOG_CTRL14_REAL_S real;
    GH_AUDIO_ANALOG_CTRL14_S dummy;
    dummy.all = data ;
    real.bitc.read_back = dummy.bitc.read_back;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL14_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL14(void)
{
    GH_AUDIO_ANALOG_CTRL14_REAL_S real;
    GH_AUDIO_ANALOG_CTRL14_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL14_REAL);

    dummy.bitc.read_back = real.bitc.read_back;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL14_READ_BACK(U16 data)
{
    GH_AUDIO_ANALOG_CTRL14_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL14_REAL;
    d.bitc.read_back = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL14_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL14_READ_BACK(void)
{
    GH_AUDIO_ANALOG_CTRL14_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL14_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.read_back;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL15 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL15(U16 data)
{
    GH_AUDIO_ANALOG_CTRL15_REAL_S real;
    GH_AUDIO_ANALOG_CTRL15_S dummy;
    dummy.all = data ;
    real.bitc.read_back = dummy.bitc.read_back;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL15_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL15(void)
{
    GH_AUDIO_ANALOG_CTRL15_REAL_S real;
    GH_AUDIO_ANALOG_CTRL15_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL15_REAL);

    dummy.bitc.read_back = real.bitc.read_back;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL15_READ_BACK(U16 data)
{
    GH_AUDIO_ANALOG_CTRL15_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL15_REAL;
    d.bitc.read_back = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL15_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL15_READ_BACK(void)
{
    GH_AUDIO_ANALOG_CTRL15_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL15_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.read_back;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL16 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL16(U16 data)
{
    GH_AUDIO_ANALOG_CTRL16_REAL_S real;
    GH_AUDIO_ANALOG_CTRL16_S dummy;
    dummy.all = data ;
    real.bitc.read_back = dummy.bitc.read_back;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL16_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL16(void)
{
    GH_AUDIO_ANALOG_CTRL16_REAL_S real;
    GH_AUDIO_ANALOG_CTRL16_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL16_REAL);

    dummy.bitc.read_back = real.bitc.read_back;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL16_READ_BACK(U16 data)
{
    GH_AUDIO_ANALOG_CTRL16_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL16_REAL;
    d.bitc.read_back = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL16_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL16_READ_BACK(void)
{
    GH_AUDIO_ANALOG_CTRL16_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL16_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.read_back;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL17 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL17(U16 data)
{
    GH_AUDIO_ANALOG_CTRL17_REAL_S real;
    GH_AUDIO_ANALOG_CTRL17_S dummy;
    dummy.all = data ;
    real.bitc.read_back = dummy.bitc.read_back;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL17_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL17(void)
{
    GH_AUDIO_ANALOG_CTRL17_REAL_S real;
    GH_AUDIO_ANALOG_CTRL17_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL17_REAL);

    dummy.bitc.read_back = real.bitc.read_back;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL17_READ_BACK(U16 data)
{
    GH_AUDIO_ANALOG_CTRL17_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL17_REAL;
    d.bitc.read_back = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL17_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL17_READ_BACK(void)
{
    GH_AUDIO_ANALOG_CTRL17_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL17_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.read_back;
}

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL18 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL18(U16 data)
{
    GH_AUDIO_ANALOG_CTRL18_REAL_S real;
    GH_AUDIO_ANALOG_CTRL18_S dummy;
    dummy.all = data ;
    real.bitc.audio_sleep_dbg_bus = dummy.bitc.audio_sleep_dbg_bus;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL18_REAL = real.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL18(void)
{
    GH_AUDIO_ANALOG_CTRL18_REAL_S real;
    GH_AUDIO_ANALOG_CTRL18_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL18_REAL);

    dummy.bitc.audio_sleep_dbg_bus = real.bitc.audio_sleep_dbg_bus;
    return dummy.all;
}
GH_INLINE void GH_AUDIO_set_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS(U16 data)
{
    GH_AUDIO_ANALOG_CTRL18_REAL_S d;
    d.all = *(volatile U16 *)REG_AUDIO_ANALOG_CTRL18_REAL;
    d.bitc.audio_sleep_dbg_bus = data;
    *(volatile U16 *)REG_AUDIO_ANALOG_CTRL18_REAL = d.all;
}
GH_INLINE U16  GH_AUDIO_get_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS(void)
{
    GH_AUDIO_ANALOG_CTRL18_REAL_S tmp_value;
    U16 value = (*(volatile U16 *)REG_AUDIO_ANALOG_CTRL18_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.audio_sleep_dbg_bus;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_AUDIO_init(void)
{
    int i;

    GH_AUDIO_set_AHB_GENERAL0((U16)0x00000000);
    GH_AUDIO_set_AHB_GENERAL1((U16)0x00000000);
    GH_AUDIO_set_SYS_RST_CTRL0((U16)0x00000000);
    GH_AUDIO_set_CKG_CTRL0((U16)0x00000001);
    GH_AUDIO_set_AUDIOBAND_CTRL2((U16)0x00008a0e);
    GH_AUDIO_set_TIMING_CTRL0((U16)0x0000023f);
    GH_AUDIO_set_AUDIOBAND_CTRL0((U16)0x00000002);
    GH_AUDIO_set_SDM_CTRL0((U16)0x00000015);
    GH_AUDIO_set_SDM_CTRL1((U16)0x00000000);
    GH_AUDIO_set_NF_SYNTH_1_NF_H((U16)0x0000007d);
    GH_AUDIO_set_NF_SYNTH_1_NF_L((U16)0x00000000);
    GH_AUDIO_set_NF_SYNTH_2_NF_H((U16)0x000000c0);
    GH_AUDIO_set_NF_SYNTH_2_NF_L((U16)0x00000000);
    GH_AUDIO_set_DIG_MIC_CTRL((U16)0x00000000);
    GH_AUDIO_set_PGA_DPGA_CFG((U16)0x00000f0f);
    for (i=0; i<2; i++)
    {
        GH_AUDIO_set_MMP_DPGA_CFG1(i, (U16)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_AUDIO_set_MMP_DPGA_CFG2(i, (U16)0x00000000);
    }
    GH_AUDIO_set_MIX_CTRL0((U16)0x00000000);
    GH_AUDIO_set_FIFO_TH_CTRL0((U16)0x00000000);
    GH_AUDIO_set_TIMING_CTRL1((U16)0x00000200);
    GH_AUDIO_set_AUDIOBAND_CTRL1((U16)0x00002800);
    GH_AUDIO_set_FIFO_CTRL((U16)0x00000808);
    GH_AUDIO_set_SINE_GEN_CTRL0((U16)0x0000a000);
    GH_AUDIO_set_SINE_GEN_CTRL1((U16)0x00000000);
    GH_AUDIO_set_TEST_CTRL0((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL00((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL01((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL02((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL03((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL04((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL05((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL06((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL07((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL08((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL09((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL10((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL11((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL12((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL13((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL14((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL15((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL16((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL17((U16)0x00000000);
    GH_AUDIO_set_ANALOG_CTRL18((U16)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

