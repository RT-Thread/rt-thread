/*!
*******************************************************************************
**
** \file      gh_audio.h
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
#ifndef _GH_AUDIO_H
#define _GH_AUDIO_H

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

#define GH_AUDIO_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_AUDIO_DEBUG_PRINT_FUNCTION printk
#else
#define GH_AUDIO_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_AUDIO_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_AUDIO_AHB_GENERAL0                              FIO_ADDRESS(AUDIO,0x90020E00) /* read/write */
#define REG_AUDIO_AHB_GENERAL1                              FIO_ADDRESS(AUDIO,0x90020E04) /* read/write */
#define REG_AUDIO_SYS_RST_CTRL0                             FIO_ADDRESS(AUDIO,0x90020C00) /* read/write */
#define REG_AUDIO_CKG_CTRL0                                 FIO_ADDRESS(AUDIO,0x90020C04) /* read/write */
#define REG_AUDIO_AUDIOBAND_CTRL2                           FIO_ADDRESS(AUDIO,0x90020C08) /* read/write */
#define REG_AUDIO_TIMING_CTRL0                              FIO_ADDRESS(AUDIO,0x90020C0C) /* read/write */
#define REG_AUDIO_AUDIOBAND_CTRL0                           FIO_ADDRESS(AUDIO,0x90020C10) /* read/write */
#define REG_AUDIO_AUDIOBAND_STS                             FIO_ADDRESS(AUDIO,0x90020C14) /* read */
#define REG_AUDIO_SDM_CTRL0                                 FIO_ADDRESS(AUDIO,0x90020C18) /* read/write */
#define REG_AUDIO_SDM_CTRL1                                 FIO_ADDRESS(AUDIO,0x90020C1C) /* read/write */
#define REG_AUDIO_NF_SYNTH_1_NF_H                           FIO_ADDRESS(AUDIO,0x90020C20) /* read/write */
#define REG_AUDIO_NF_SYNTH_1_NF_L                           FIO_ADDRESS(AUDIO,0x90020C24) /* read/write */
#define REG_AUDIO_NF_SYNTH_2_NF_H                           FIO_ADDRESS(AUDIO,0x90020C28) /* read/write */
#define REG_AUDIO_NF_SYNTH_2_NF_L                           FIO_ADDRESS(AUDIO,0x90020C2C) /* read/write */
#define REG_AUDIO_DIG_MIC_CTRL                              FIO_ADDRESS(AUDIO,0x90020C30) /* read/write */
#define REG_AUDIO_AUDIOBAND_STS2                            FIO_ADDRESS(AUDIO,0x90020C34) /* read */
#define REG_AUDIO_SDM_DWA_DATAIN_L                          FIO_ADDRESS(AUDIO,0x90020C38) /* read */
#define REG_AUDIO_SDM_DWA_DATAIN_R                          FIO_ADDRESS(AUDIO,0x90020C3C) /* read */
#define REG_AUDIO_VALID_SIGNALS                             FIO_ADDRESS(AUDIO,0x90020C40) /* read */
#define REG_AUDIO_PGA_DPGA_CFG                              FIO_ADDRESS(AUDIO,0x90020C44) /* read/write */
#define REG_AUDIO_MMP_DPGA_CFG1                             FIO_ADDRESS(AUDIO,0x90020C48) /* read/write */
#define REG_AUDIO_MMP_DPGA_CFG2                             FIO_ADDRESS(AUDIO,0x90020C4C) /* read/write */
#define REG_AUDIO_MIX_CTRL0                                 FIO_ADDRESS(AUDIO,0x90020C50) /* read/write */
#define REG_AUDIO_INT_DOUT                                  FIO_ADDRESS(AUDIO,0x90020C68) /* read */
#define REG_AUDIO_FIFO_TH_CTRL0                             FIO_ADDRESS(AUDIO,0x90020C6C) /* read/write */
#define REG_AUDIO_TIMING_CTRL1                              FIO_ADDRESS(AUDIO,0x90020D40) /* read/write */
#define REG_AUDIO_AUDIOBAND_CTRL1                           FIO_ADDRESS(AUDIO,0x90020D44) /* read/write */
#define REG_AUDIO_FIFO_CTRL                                 FIO_ADDRESS(AUDIO,0x90020D48) /* read/write */
#define REG_AUDIO_FIFO_STS                                  FIO_ADDRESS(AUDIO,0x90020D4C) /* read */
#define REG_AUDIO_NF_SYNTH_5_NF_H                           FIO_ADDRESS(AUDIO,0x90020D50) /* read */
#define REG_AUDIO_NF_SYNTH_5_NF_L                           FIO_ADDRESS(AUDIO,0x90020D54) /* read */
#define REG_AUDIO_INT_CTRL                                  FIO_ADDRESS(AUDIO,0x90020D58) /* read */
#define REG_AUDIO_SINE_GEN_CTRL0                            FIO_ADDRESS(AUDIO,0x90020D64) /* read/write */
#define REG_AUDIO_SINE_GEN_CTRL1                            FIO_ADDRESS(AUDIO,0x90020D68) /* read/write */
#define REG_AUDIO_TEST_CTRL0                                FIO_ADDRESS(AUDIO,0x90020D6C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL00                             FIO_ADDRESS(AUDIO,0x90021C00) /* read/write */
#define REG_AUDIO_ANALOG_CTRL01                             FIO_ADDRESS(AUDIO,0x90021C04) /* read/write */
#define REG_AUDIO_ANALOG_CTRL02                             FIO_ADDRESS(AUDIO,0x90021C08) /* read/write */
#define REG_AUDIO_ANALOG_CTRL03                             FIO_ADDRESS(AUDIO,0x90021C0C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL04                             FIO_ADDRESS(AUDIO,0x90021C10) /* read/write */
#define REG_AUDIO_ANALOG_CTRL05                             FIO_ADDRESS(AUDIO,0x90021C14) /* read/write */
#define REG_AUDIO_ANALOG_CTRL06                             FIO_ADDRESS(AUDIO,0x90021C18) /* read/write */
#define REG_AUDIO_ANALOG_CTRL07                             FIO_ADDRESS(AUDIO,0x90021C1C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL08                             FIO_ADDRESS(AUDIO,0x90021C20) /* read/write */
#define REG_AUDIO_ANALOG_CTRL09                             FIO_ADDRESS(AUDIO,0x90021C24) /* read/write */
#define REG_AUDIO_ANALOG_CTRL10                             FIO_ADDRESS(AUDIO,0x90021C28) /* read/write */
#define REG_AUDIO_ANALOG_CTRL11                             FIO_ADDRESS(AUDIO,0x90021C2C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL12                             FIO_ADDRESS(AUDIO,0x90021C30) /* read/write */
#define REG_AUDIO_ANALOG_CTRL13                             FIO_ADDRESS(AUDIO,0x90021C34) /* read/write */
#define REG_AUDIO_ANALOG_CTRL14                             FIO_ADDRESS(AUDIO,0x90021C38) /* read/write */
#define REG_AUDIO_ANALOG_CTRL15                             FIO_ADDRESS(AUDIO,0x90021C3C) /* read/write */
#define REG_AUDIO_ANALOG_CTRL16                             FIO_ADDRESS(AUDIO,0x90021C40) /* read/write */
#define REG_AUDIO_ANALOG_CTRL17                             FIO_ADDRESS(AUDIO,0x90021C44) /* read/write */
#define REG_AUDIO_ANALOG_CTRL18                             FIO_ADDRESS(AUDIO,0x90021C48) /* read/write */

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
} GH_AUDIO_AHB_GENERAL0_S;

typedef union { /* AUDIO_AHB_GENERAL1 */
    U16 all;
    struct {
        U16 audio_i2s_sel               : 1;
        U16                             : 15;
    } bitc;
} GH_AUDIO_AHB_GENERAL1_S;

typedef union { /* AUDIO_SYS_RST_CTRL0 */
    U16 all;
    struct {
        U16                             : 13;
        U16 reset_sdm_sync              : 1;
        U16 reset_dpga_sync             : 1;
        U16 reset_au_sync               : 1;
    } bitc;
} GH_AUDIO_SYS_RST_CTRL0_S;

typedef union { /* AUDIO_CKG_CTRL0 */
    U16 all;
    struct {
        U16 au_src1_mac_48m_dyng_en     : 1;
        U16                             : 15;
    } bitc;
} GH_AUDIO_CKG_CTRL0_S;

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
} GH_AUDIO_AUDIOBAND_CTRL2_S;

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
} GH_AUDIO_TIMING_CTRL0_S;

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
} GH_AUDIO_AUDIOBAND_CTRL0_S;

typedef union { /* AUDIO_AUDIOBAND_STS */
    U16 all;
    struct {
        U16 quant_out_r                 : 6;
        U16 quant_out_l                 : 6;
        U16                             : 4;
    } bitc;
} GH_AUDIO_AUDIOBAND_STS_S;

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
} GH_AUDIO_SDM_CTRL0_S;

typedef union { /* AUDIO_SDM_CTRL1 */
    U16 all;
    struct {
        U16 sdm_offset                  : 16;
    } bitc;
} GH_AUDIO_SDM_CTRL1_S;

typedef union { /* AUDIO_NF_SYNTH_1_NF_H */
    U16 all;
    struct {
        U16 value                       : 14;
        U16 trig                        : 2;
    } bitc;
} GH_AUDIO_NF_SYNTH_1_NF_H_S;

typedef union { /* AUDIO_NF_SYNTH_1_NF_L */
    U16 all;
    struct {
        U16 value                       : 16;
    } bitc;
} GH_AUDIO_NF_SYNTH_1_NF_L_S;

typedef union { /* AUDIO_NF_SYNTH_2_NF_H */
    U16 all;
    struct {
        U16 value                       : 14;
        U16                             : 1;
        U16 trig                        : 1;
    } bitc;
} GH_AUDIO_NF_SYNTH_2_NF_H_S;

typedef union { /* AUDIO_NF_SYNTH_2_NF_L */
    U16 all;
    struct {
        U16 value                       : 16;
    } bitc;
} GH_AUDIO_NF_SYNTH_2_NF_L_S;

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
} GH_AUDIO_DIG_MIC_CTRL_S;

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
} GH_AUDIO_AUDIOBAND_STS2_S;

typedef union { /* AUDIO_SDM_DWA_DATAIN_L */
    U16 all;
    struct {
        U16 data                        : 16;
    } bitc;
} GH_AUDIO_SDM_DWA_DATAIN_L_S;

typedef union { /* AUDIO_SDM_DWA_DATAIN_R */
    U16 all;
    struct {
        U16 data                        : 16;
    } bitc;
} GH_AUDIO_SDM_DWA_DATAIN_R_S;

typedef union { /* AUDIO_VALID_SIGNALS */
    U16 all;
    struct {
        U16 valid_signals               : 16;
    } bitc;
} GH_AUDIO_VALID_SIGNALS_S;

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
} GH_AUDIO_PGA_DPGA_CFG_S;

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
} GH_AUDIO_MMP_DPGA_CFG1_S;

typedef union { /* AUDIO_MMP_DPGA_CFG2 */
    U16 all;
    struct {
        U16 gain                        : 8;
        U16 gain_trig                   : 1;
        U16                             : 7;
    } bitc;
} GH_AUDIO_MMP_DPGA_CFG2_S;

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
} GH_AUDIO_MIX_CTRL0_S;

typedef union { /* AUDIO_FIFO_TH_CTRL0 */
    U16 all;
    struct {
        U16 tx                          : 7;
        U16                             : 1;
        U16 rx                          : 7;
        U16                             : 1;
    } bitc;
} GH_AUDIO_FIFO_TH_CTRL0_S;

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
} GH_AUDIO_TIMING_CTRL1_S;

typedef union { /* AUDIO_AUDIOBAND_CTRL1 */
    U16 all;
    struct {
        U16                             : 10;
        U16 sdm_dwa_datain_r_sel        : 2;
        U16 sdm_dwa_datain_l_sel        : 2;
        U16                             : 2;
    } bitc;
} GH_AUDIO_AUDIOBAND_CTRL1_S;

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
} GH_AUDIO_FIFO_CTRL_S;

typedef union { /* AUDIO_FIFO_STS */
    U16 all;
    struct {
        U16 tx_fifo_status              : 4;
        U16 rx_fifo_status              : 4;
        U16                             : 8;
    } bitc;
} GH_AUDIO_FIFO_STS_S;

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
} GH_AUDIO_SINE_GEN_CTRL0_S;

typedef union { /* AUDIO_SINE_GEN_CTRL1 */
    U16 all;
    struct {
        U16 sine_gen_ch1_freq           : 4;
        U16 sine_gen_ch1_gain           : 4;
        U16 sine_gen_ch2_freq           : 4;
        U16 sine_gen_ch2_gain           : 4;
    } bitc;
} GH_AUDIO_SINE_GEN_CTRL1_S;

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
} GH_AUDIO_TEST_CTRL0_S;

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
} GH_AUDIO_ANALOG_CTRL00_S;

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
} GH_AUDIO_ANALOG_CTRL01_S;

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
} GH_AUDIO_ANALOG_CTRL02_S;

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
} GH_AUDIO_ANALOG_CTRL03_S;

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
} GH_AUDIO_ANALOG_CTRL04_S;

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
} GH_AUDIO_ANALOG_CTRL05_S;

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
} GH_AUDIO_ANALOG_CTRL06_S;

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
} GH_AUDIO_ANALOG_CTRL07_S;

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
} GH_AUDIO_ANALOG_CTRL08_S;

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
} GH_AUDIO_ANALOG_CTRL09_S;

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
} GH_AUDIO_ANALOG_CTRL10_S;

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
} GH_AUDIO_ANALOG_CTRL11_S;

typedef union { /* AUDIO_ANALOG_CTRL12 */
    U16 all;
    struct {
        U16 audio_reg                   : 8;
        U16                             : 4;
        U16 test_bus_sel                : 4;
    } bitc;
} GH_AUDIO_ANALOG_CTRL12_S;

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
} GH_AUDIO_ANALOG_CTRL13_S;

typedef union { /* AUDIO_ANALOG_CTRL14 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL14_S;

typedef union { /* AUDIO_ANALOG_CTRL15 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL15_S;

typedef union { /* AUDIO_ANALOG_CTRL16 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL16_S;

typedef union { /* AUDIO_ANALOG_CTRL17 */
    U16 all;
    struct {
        U16 read_back                   : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL17_S;

typedef union { /* AUDIO_ANALOG_CTRL18 */
    U16 all;
    struct {
        U16 audio_sleep_dbg_bus         : 16;
    } bitc;
} GH_AUDIO_ANALOG_CTRL18_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register AUDIO_AHB_GENERAL0 (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_AHB_GENERAL0'. */
void GH_AUDIO_set_AHB_GENERAL0(U16 data);
/*! \brief Reads the register 'AUDIO_AHB_GENERAL0'. */
U16  GH_AUDIO_get_AHB_GENERAL0(void);
/*! \brief Writes the bit group 'USB_TM1' of register 'AUDIO_AHB_GENERAL0'. */
void GH_AUDIO_set_AHB_GENERAL0_USB_TM1(U8 data);
/*! \brief Reads the bit group 'USB_TM1' of register 'AUDIO_AHB_GENERAL0'. */
U8   GH_AUDIO_get_AHB_GENERAL0_USB_TM1(void);
/*! \brief Writes the bit group 'AHB_RMII_SEL' of register 'AUDIO_AHB_GENERAL0'. */
void GH_AUDIO_set_AHB_GENERAL0_AHB_RMII_SEL(U8 data);
/*! \brief Reads the bit group 'AHB_RMII_SEL' of register 'AUDIO_AHB_GENERAL0'. */
U8   GH_AUDIO_get_AHB_GENERAL0_AHB_RMII_SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_AHB_GENERAL1 (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_AHB_GENERAL1'. */
void GH_AUDIO_set_AHB_GENERAL1(U16 data);
/*! \brief Reads the register 'AUDIO_AHB_GENERAL1'. */
U16  GH_AUDIO_get_AHB_GENERAL1(void);
/*! \brief Writes the bit group 'AUDIO_I2S_SEL' of register 'AUDIO_AHB_GENERAL1'. */
void GH_AUDIO_set_AHB_GENERAL1_AUDIO_I2S_SEL(U8 data);
/*! \brief Reads the bit group 'AUDIO_I2S_SEL' of register 'AUDIO_AHB_GENERAL1'. */
U8   GH_AUDIO_get_AHB_GENERAL1_AUDIO_I2S_SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_SYS_RST_CTRL0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_SYS_RST_CTRL0'. */
void GH_AUDIO_set_SYS_RST_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_SYS_RST_CTRL0'. */
U16  GH_AUDIO_get_SYS_RST_CTRL0(void);
/*! \brief Writes the bit group 'RESET_SDM_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
void GH_AUDIO_set_SYS_RST_CTRL0_RESET_SDM_SYNC(U8 data);
/*! \brief Reads the bit group 'RESET_SDM_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_SDM_SYNC(void);
/*! \brief Writes the bit group 'RESET_DPGA_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
void GH_AUDIO_set_SYS_RST_CTRL0_RESET_DPGA_SYNC(U8 data);
/*! \brief Reads the bit group 'RESET_DPGA_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_DPGA_SYNC(void);
/*! \brief Writes the bit group 'RESET_AU_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
void GH_AUDIO_set_SYS_RST_CTRL0_RESET_AU_SYNC(U8 data);
/*! \brief Reads the bit group 'RESET_AU_SYNC' of register 'AUDIO_SYS_RST_CTRL0'. */
U8   GH_AUDIO_get_SYS_RST_CTRL0_RESET_AU_SYNC(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_CKG_CTRL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_CKG_CTRL0'. */
void GH_AUDIO_set_CKG_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_CKG_CTRL0'. */
U16  GH_AUDIO_get_CKG_CTRL0(void);
/*! \brief Writes the bit group 'AU_SRC1_MAC_48M_DYNG_EN' of register 'AUDIO_CKG_CTRL0'. */
void GH_AUDIO_set_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN(U8 data);
/*! \brief Reads the bit group 'AU_SRC1_MAC_48M_DYNG_EN' of register 'AUDIO_CKG_CTRL0'. */
U8   GH_AUDIO_get_CKG_CTRL0_AU_SRC1_MAC_48M_DYNG_EN(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_CTRL2 (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2(U16 data);
/*! \brief Reads the register 'AUDIO_AUDIOBAND_CTRL2'. */
U16  GH_AUDIO_get_AUDIOBAND_CTRL2(void);
/*! \brief Writes the bit group 'EN_DEC_4_p' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_4_p(U8 data);
/*! \brief Reads the bit group 'EN_DEC_4_p' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_4_p(void);
/*! \brief Writes the bit group 'EN_DEC_3_p' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_EN_DEC_3_p(U8 data);
/*! \brief Reads the bit group 'EN_DEC_3_p' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_EN_DEC_3_p(void);
/*! \brief Writes the bit group 'NT4_MIX_CTRL' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_NT4_MIX_CTRL(U8 data);
/*! \brief Reads the bit group 'NT4_MIX_CTRL' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_NT4_MIX_CTRL(void);
/*! \brief Writes the bit group 'NT3_MIX_CTRL' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_NT3_MIX_CTRL(U8 data);
/*! \brief Reads the bit group 'NT3_MIX_CTRL' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_NT3_MIX_CTRL(void);
/*! \brief Writes the bit group 'DEC_NUM3' of register 'AUDIO_AUDIOBAND_CTRL2'. */
void GH_AUDIO_set_AUDIOBAND_CTRL2_DEC_NUM3(U8 data);
/*! \brief Reads the bit group 'DEC_NUM3' of register 'AUDIO_AUDIOBAND_CTRL2'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL2_DEC_NUM3(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_TIMING_CTRL0 (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_TIMING_CTRL0'. */
U16  GH_AUDIO_get_TIMING_CTRL0(void);
/*! \brief Writes the bit group 'EN_TIME_GEN_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_TIME_GEN_p(U8 data);
/*! \brief Reads the bit group 'EN_TIME_GEN_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_TIME_GEN_p(void);
/*! \brief Writes the bit group 'EN_DEC_1_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_DEC_1_p(U8 data);
/*! \brief Reads the bit group 'EN_DEC_1_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_DEC_1_p(void);
/*! \brief Writes the bit group 'EN_DEC_2_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_DEC_2_p(U8 data);
/*! \brief Reads the bit group 'EN_DEC_2_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_DEC_2_p(void);
/*! \brief Writes the bit group 'EN_INT_1_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_INT_1_p(U8 data);
/*! \brief Reads the bit group 'EN_INT_1_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_INT_1_p(void);
/*! \brief Writes the bit group 'EN_INT_2_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_INT_2_p(U8 data);
/*! \brief Reads the bit group 'EN_INT_2_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_INT_2_p(void);
/*! \brief Writes the bit group 'EN_ASRC1_p' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_EN_ASRC1_p(U8 data);
/*! \brief Reads the bit group 'EN_ASRC1_p' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_EN_ASRC1_p(void);
/*! \brief Writes the bit group 'DEC_NUM' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_DEC_NUM(U8 data);
/*! \brief Reads the bit group 'DEC_NUM' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_DEC_NUM(void);
/*! \brief Writes the bit group 'DAC_SYNC_SEL' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_DAC_SYNC_SEL(U8 data);
/*! \brief Reads the bit group 'DAC_SYNC_SEL' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_DAC_SYNC_SEL(void);
/*! \brief Writes the bit group 'ADC_SYNC_SEL' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_ADC_SYNC_SEL(U8 data);
/*! \brief Reads the bit group 'ADC_SYNC_SEL' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_ADC_SYNC_SEL(void);
/*! \brief Writes the bit group 'SYNC_CLK2_SEL' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK2_SEL(U8 data);
/*! \brief Reads the bit group 'SYNC_CLK2_SEL' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK2_SEL(void);
/*! \brief Writes the bit group 'SYNC_CLK1_SEL' of register 'AUDIO_TIMING_CTRL0'. */
void GH_AUDIO_set_TIMING_CTRL0_SYNC_CLK1_SEL(U8 data);
/*! \brief Reads the bit group 'SYNC_CLK1_SEL' of register 'AUDIO_TIMING_CTRL0'. */
U8   GH_AUDIO_get_TIMING_CTRL0_SYNC_CLK1_SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_CTRL0 (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_AUDIOBAND_CTRL0'. */
U16  GH_AUDIO_get_AUDIOBAND_CTRL0(void);
/*! \brief Writes the bit group 'INI_SRAM' of register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0_INI_SRAM(U8 data);
/*! \brief Reads the bit group 'INI_SRAM' of register 'AUDIO_AUDIOBAND_CTRL0'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL0_INI_SRAM(void);
/*! \brief Writes the bit group 'CH12_SYNC_ENABLE' of register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE(U8 data);
/*! \brief Reads the bit group 'CH12_SYNC_ENABLE' of register 'AUDIO_AUDIOBAND_CTRL0'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH12_SYNC_ENABLE(void);
/*! \brief Writes the bit group 'CH2_INT_128FS_NF_SEL' of register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL(U8 data);
/*! \brief Reads the bit group 'CH2_INT_128FS_NF_SEL' of register 'AUDIO_AUDIOBAND_CTRL0'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH2_INT_128FS_NF_SEL(void);
/*! \brief Writes the bit group 'CH1_INT_128FS_NF_SEL' of register 'AUDIO_AUDIOBAND_CTRL0'. */
void GH_AUDIO_set_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL(U8 data);
/*! \brief Reads the bit group 'CH1_INT_128FS_NF_SEL' of register 'AUDIO_AUDIOBAND_CTRL0'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL0_CH1_INT_128FS_NF_SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_STS (read)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_AUDIOBAND_STS'. */
U16  GH_AUDIO_get_AUDIOBAND_STS(void);
/*! \brief Reads the bit group 'QUANT_OUT_R' of register 'AUDIO_AUDIOBAND_STS'. */
U8   GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_R(void);
/*! \brief Reads the bit group 'QUANT_OUT_L' of register 'AUDIO_AUDIOBAND_STS'. */
U8   GH_AUDIO_get_AUDIOBAND_STS_QUANT_OUT_L(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_CTRL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_SDM_CTRL0'. */
U16  GH_AUDIO_get_SDM_CTRL0(void);
/*! \brief Writes the bit group 'EN_SDM_p' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_EN_SDM_p(U8 data);
/*! \brief Reads the bit group 'EN_SDM_p' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_EN_SDM_p(void);
/*! \brief Writes the bit group 'FS_SYNTH_SEL_p' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_FS_SYNTH_SEL_p(U8 data);
/*! \brief Reads the bit group 'FS_SYNTH_SEL_p' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_FS_SYNTH_SEL_p(void);
/*! \brief Writes the bit group 'DAC_DIN_L_SEL' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_DAC_DIN_L_SEL(U8 data);
/*! \brief Reads the bit group 'DAC_DIN_L_SEL' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_DAC_DIN_L_SEL(void);
/*! \brief Writes the bit group 'DAC_DIN_R_SEL' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_DAC_DIN_R_SEL(U8 data);
/*! \brief Reads the bit group 'DAC_DIN_R_SEL' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_DAC_DIN_R_SEL(void);
/*! \brief Writes the bit group 'FIX_MSB_EN' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_FIX_MSB_EN(U8 data);
/*! \brief Reads the bit group 'FIX_MSB_EN' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_FIX_MSB_EN(void);
/*! \brief Writes the bit group 'FIX_MSB_SEL' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_FIX_MSB_SEL(U8 data);
/*! \brief Reads the bit group 'FIX_MSB_SEL' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_FIX_MSB_SEL(void);
/*! \brief Writes the bit group 'DITHER_EN_p' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_DITHER_EN_p(U8 data);
/*! \brief Reads the bit group 'DITHER_EN_p' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_DITHER_EN_p(void);
/*! \brief Writes the bit group 'DITHER_SEL' of register 'AUDIO_SDM_CTRL0'. */
void GH_AUDIO_set_SDM_CTRL0_DITHER_SEL(U8 data);
/*! \brief Reads the bit group 'DITHER_SEL' of register 'AUDIO_SDM_CTRL0'. */
U8   GH_AUDIO_get_SDM_CTRL0_DITHER_SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_CTRL1 (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_SDM_CTRL1'. */
void GH_AUDIO_set_SDM_CTRL1(U16 data);
/*! \brief Reads the register 'AUDIO_SDM_CTRL1'. */
U16  GH_AUDIO_get_SDM_CTRL1(void);
/*! \brief Writes the bit group 'SDM_OFFSET' of register 'AUDIO_SDM_CTRL1'. */
void GH_AUDIO_set_SDM_CTRL1_SDM_OFFSET(U16 data);
/*! \brief Reads the bit group 'SDM_OFFSET' of register 'AUDIO_SDM_CTRL1'. */
U16  GH_AUDIO_get_SDM_CTRL1_SDM_OFFSET(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_1_NF_H (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_NF_SYNTH_1_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_H(U16 data);
/*! \brief Reads the register 'AUDIO_NF_SYNTH_1_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_1_NF_H(void);
/*! \brief Writes the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_1_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_H_VALUE(U16 data);
/*! \brief Reads the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_1_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_1_NF_H_VALUE(void);
/*! \brief Writes the bit group 'TRIG' of register 'AUDIO_NF_SYNTH_1_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_H_TRIG(U8 data);
/*! \brief Reads the bit group 'TRIG' of register 'AUDIO_NF_SYNTH_1_NF_H'. */
U8   GH_AUDIO_get_NF_SYNTH_1_NF_H_TRIG(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_1_NF_L (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_NF_SYNTH_1_NF_L'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_L(U16 data);
/*! \brief Reads the register 'AUDIO_NF_SYNTH_1_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_1_NF_L(void);
/*! \brief Writes the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_1_NF_L'. */
void GH_AUDIO_set_NF_SYNTH_1_NF_L_VALUE(U16 data);
/*! \brief Reads the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_1_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_1_NF_L_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_2_NF_H (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_NF_SYNTH_2_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_H(U16 data);
/*! \brief Reads the register 'AUDIO_NF_SYNTH_2_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_2_NF_H(void);
/*! \brief Writes the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_2_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_H_VALUE(U16 data);
/*! \brief Reads the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_2_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_2_NF_H_VALUE(void);
/*! \brief Writes the bit group 'TRIG' of register 'AUDIO_NF_SYNTH_2_NF_H'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_H_TRIG(U8 data);
/*! \brief Reads the bit group 'TRIG' of register 'AUDIO_NF_SYNTH_2_NF_H'. */
U8   GH_AUDIO_get_NF_SYNTH_2_NF_H_TRIG(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_2_NF_L (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_NF_SYNTH_2_NF_L'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_L(U16 data);
/*! \brief Reads the register 'AUDIO_NF_SYNTH_2_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_2_NF_L(void);
/*! \brief Writes the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_2_NF_L'. */
void GH_AUDIO_set_NF_SYNTH_2_NF_L_VALUE(U16 data);
/*! \brief Reads the bit group 'VALUE' of register 'AUDIO_NF_SYNTH_2_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_2_NF_L_VALUE(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_DIG_MIC_CTRL (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL(U16 data);
/*! \brief Reads the register 'AUDIO_DIG_MIC_CTRL'. */
U16  GH_AUDIO_get_DIG_MIC_CTRL(void);
/*! \brief Writes the bit group 'PGA_STATUS_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_PGA_STATUS_CLR(U8 data);
/*! \brief Reads the bit group 'PGA_STATUS_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_PGA_STATUS_CLR(void);
/*! \brief Writes the bit group 'DPGA_STATUS_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_DPGA_STATUS_CLR(U8 data);
/*! \brief Reads the bit group 'DPGA_STATUS_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_DPGA_STATUS_CLR(void);
/*! \brief Writes the bit group 'PNT_MMC3_DEC_SYNC_ENZ' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ(U8 data);
/*! \brief Reads the bit group 'PNT_MMC3_DEC_SYNC_ENZ' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC3_DEC_SYNC_ENZ(void);
/*! \brief Writes the bit group 'PNT_MMC1_DEC_SYNC_ENZ' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ(U8 data);
/*! \brief Reads the bit group 'PNT_MMC1_DEC_SYNC_ENZ' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC1_DEC_SYNC_ENZ(void);
/*! \brief Writes the bit group 'PNT_MMC_DEC_ERR_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
void GH_AUDIO_set_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR(U8 data);
/*! \brief Reads the bit group 'PNT_MMC_DEC_ERR_CLR' of register 'AUDIO_DIG_MIC_CTRL'. */
U8   GH_AUDIO_get_DIG_MIC_CTRL_PNT_MMC_DEC_ERR_CLR(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_STS2 (read)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_AUDIOBAND_STS2'. */
U16  GH_AUDIO_get_AUDIOBAND_STS2(void);
/*! \brief Reads the bit group 'PGA_STATUS' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_PGA_STATUS(void);
/*! \brief Reads the bit group 'MMP2_MUTE_DONE' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_MMP2_MUTE_DONE(void);
/*! \brief Reads the bit group 'MMP1_MUTE_DONE' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_MMP1_MUTE_DONE(void);
/*! \brief Reads the bit group 'PNT_MMC_DEC_ERR_CLR' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_PNT_MMC_DEC_ERR_CLR(void);
/*! \brief Reads the bit group 'DPGA_STATUS' of register 'AUDIO_AUDIOBAND_STS2'. */
U8   GH_AUDIO_get_AUDIOBAND_STS2_DPGA_STATUS(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_DWA_DATAIN_L (read)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_SDM_DWA_DATAIN_L'. */
U16  GH_AUDIO_get_SDM_DWA_DATAIN_L(void);
/*! \brief Reads the bit group 'data' of register 'AUDIO_SDM_DWA_DATAIN_L'. */
U16  GH_AUDIO_get_SDM_DWA_DATAIN_L_data(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_SDM_DWA_DATAIN_R (read)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_SDM_DWA_DATAIN_R'. */
U16  GH_AUDIO_get_SDM_DWA_DATAIN_R(void);
/*! \brief Reads the bit group 'data' of register 'AUDIO_SDM_DWA_DATAIN_R'. */
U16  GH_AUDIO_get_SDM_DWA_DATAIN_R_data(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_VALID_SIGNALS (read)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_VALID_SIGNALS'. */
U16  GH_AUDIO_get_VALID_SIGNALS(void);
/*! \brief Reads the bit group 'VALID_SIGNALS' of register 'AUDIO_VALID_SIGNALS'. */
U16  GH_AUDIO_get_VALID_SIGNALS_VALID_SIGNALS(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_PGA_DPGA_CFG (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG(U16 data);
/*! \brief Reads the register 'AUDIO_PGA_DPGA_CFG'. */
U16  GH_AUDIO_get_PGA_DPGA_CFG(void);
/*! \brief Writes the bit group 'PGA2_gain' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain(U8 data);
/*! \brief Reads the bit group 'PGA2_gain' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain(void);
/*! \brief Writes the bit group 'PGA2_gain_trig' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_gain_trig(U8 data);
/*! \brief Reads the bit group 'PGA2_gain_trig' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_gain_trig(void);
/*! \brief Writes the bit group 'PGA2_mute' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_mute(U8 data);
/*! \brief Reads the bit group 'PGA2_mute' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_mute(void);
/*! \brief Writes the bit group 'PGA2_en' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA2_en(U8 data);
/*! \brief Reads the bit group 'PGA2_en' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA2_en(void);
/*! \brief Writes the bit group 'PGA1_gain' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain(U8 data);
/*! \brief Reads the bit group 'PGA1_gain' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain(void);
/*! \brief Writes the bit group 'PGA1_gain_trig' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_gain_trig(U8 data);
/*! \brief Reads the bit group 'PGA1_gain_trig' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_gain_trig(void);
/*! \brief Writes the bit group 'PGA1_mute' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_mute(U8 data);
/*! \brief Reads the bit group 'PGA1_mute' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_mute(void);
/*! \brief Writes the bit group 'PGA1_en' of register 'AUDIO_PGA_DPGA_CFG'. */
void GH_AUDIO_set_PGA_DPGA_CFG_PGA1_en(U8 data);
/*! \brief Reads the bit group 'PGA1_en' of register 'AUDIO_PGA_DPGA_CFG'. */
U8   GH_AUDIO_get_PGA_DPGA_CFG_PGA1_en(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_MMP_DPGA_CFG1 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1(U8 index, U16 data);
/*! \brief Reads the register 'AUDIO_MMP_DPGA_CFG1'. */
U16  GH_AUDIO_get_MMP_DPGA_CFG1(U8 index);
/*! \brief Writes the bit group 'DPGA_EN' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_DPGA_EN(U8 index, U8 data);
/*! \brief Reads the bit group 'DPGA_EN' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_DPGA_EN(U8 index);
/*! \brief Writes the bit group 'FADING_EN' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_FADING_EN(U8 index, U8 data);
/*! \brief Reads the bit group 'FADING_EN' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_FADING_EN(U8 index);
/*! \brief Writes the bit group 'MUTE_2_ZERO' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_MUTE_2_ZERO(U8 index, U8 data);
/*! \brief Reads the bit group 'MUTE_2_ZERO' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_MUTE_2_ZERO(U8 index);
/*! \brief Writes the bit group 'STEP' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_STEP(U8 index, U8 data);
/*! \brief Reads the bit group 'STEP' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_STEP(U8 index);
/*! \brief Writes the bit group 'OFFSET' of register 'AUDIO_MMP_DPGA_CFG1'. */
void GH_AUDIO_set_MMP_DPGA_CFG1_OFFSET(U8 index, U8 data);
/*! \brief Reads the bit group 'OFFSET' of register 'AUDIO_MMP_DPGA_CFG1'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG1_OFFSET(U8 index);

/*----------------------------------------------------------------------------*/
/* register AUDIO_MMP_DPGA_CFG2 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_MMP_DPGA_CFG2'. */
void GH_AUDIO_set_MMP_DPGA_CFG2(U8 index, U16 data);
/*! \brief Reads the register 'AUDIO_MMP_DPGA_CFG2'. */
U16  GH_AUDIO_get_MMP_DPGA_CFG2(U8 index);
/*! \brief Writes the bit group 'GAIN' of register 'AUDIO_MMP_DPGA_CFG2'. */
void GH_AUDIO_set_MMP_DPGA_CFG2_GAIN(U8 index, U8 data);
/*! \brief Reads the bit group 'GAIN' of register 'AUDIO_MMP_DPGA_CFG2'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG2_GAIN(U8 index);
/*! \brief Writes the bit group 'GAIN_TRIG' of register 'AUDIO_MMP_DPGA_CFG2'. */
void GH_AUDIO_set_MMP_DPGA_CFG2_GAIN_TRIG(U8 index, U8 data);
/*! \brief Reads the bit group 'GAIN_TRIG' of register 'AUDIO_MMP_DPGA_CFG2'. */
U8   GH_AUDIO_get_MMP_DPGA_CFG2_GAIN_TRIG(U8 index);

/*----------------------------------------------------------------------------*/
/* register AUDIO_MIX_CTRL0 (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_MIX_CTRL0'. */
U16  GH_AUDIO_get_MIX_CTRL0(void);
/*! \brief Writes the bit group 'CH2_MUX_SEL' of register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0_CH2_MUX_SEL(U8 data);
/*! \brief Reads the bit group 'CH2_MUX_SEL' of register 'AUDIO_MIX_CTRL0'. */
U8   GH_AUDIO_get_MIX_CTRL0_CH2_MUX_SEL(void);
/*! \brief Writes the bit group 'CH1_MUX_SEL' of register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0_CH1_MUX_SEL(U8 data);
/*! \brief Reads the bit group 'CH1_MUX_SEL' of register 'AUDIO_MIX_CTRL0'. */
U8   GH_AUDIO_get_MIX_CTRL0_CH1_MUX_SEL(void);
/*! \brief Writes the bit group 'SEL_DEC2_DOUT' of register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0_SEL_DEC2_DOUT(U8 data);
/*! \brief Reads the bit group 'SEL_DEC2_DOUT' of register 'AUDIO_MIX_CTRL0'. */
U8   GH_AUDIO_get_MIX_CTRL0_SEL_DEC2_DOUT(void);
/*! \brief Writes the bit group 'SEL_DEC1_DOUT' of register 'AUDIO_MIX_CTRL0'. */
void GH_AUDIO_set_MIX_CTRL0_SEL_DEC1_DOUT(U8 data);
/*! \brief Reads the bit group 'SEL_DEC1_DOUT' of register 'AUDIO_MIX_CTRL0'. */
U8   GH_AUDIO_get_MIX_CTRL0_SEL_DEC1_DOUT(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_INT_DOUT (read)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_INT_DOUT'. */
U16  GH_AUDIO_get_INT_DOUT(U8 index);

/*----------------------------------------------------------------------------*/
/* register AUDIO_FIFO_TH_CTRL0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_FIFO_TH_CTRL0'. */
void GH_AUDIO_set_FIFO_TH_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_FIFO_TH_CTRL0'. */
U16  GH_AUDIO_get_FIFO_TH_CTRL0(void);
/*! \brief Writes the bit group 'TX' of register 'AUDIO_FIFO_TH_CTRL0'. */
void GH_AUDIO_set_FIFO_TH_CTRL0_TX(U8 data);
/*! \brief Reads the bit group 'TX' of register 'AUDIO_FIFO_TH_CTRL0'. */
U8   GH_AUDIO_get_FIFO_TH_CTRL0_TX(void);
/*! \brief Writes the bit group 'RX' of register 'AUDIO_FIFO_TH_CTRL0'. */
void GH_AUDIO_set_FIFO_TH_CTRL0_RX(U8 data);
/*! \brief Reads the bit group 'RX' of register 'AUDIO_FIFO_TH_CTRL0'. */
U8   GH_AUDIO_get_FIFO_TH_CTRL0_RX(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_TIMING_CTRL1 (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1(U16 data);
/*! \brief Reads the register 'AUDIO_TIMING_CTRL1'. */
U16  GH_AUDIO_get_TIMING_CTRL1(void);
/*! \brief Writes the bit group 'DEC_NUM2' of register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1_DEC_NUM2(U8 data);
/*! \brief Reads the bit group 'DEC_NUM2' of register 'AUDIO_TIMING_CTRL1'. */
U8   GH_AUDIO_get_TIMING_CTRL1_DEC_NUM2(void);
/*! \brief Writes the bit group 'EN_ASRC3_p' of register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1_EN_ASRC3_p(U8 data);
/*! \brief Reads the bit group 'EN_ASRC3_p' of register 'AUDIO_TIMING_CTRL1'. */
U8   GH_AUDIO_get_TIMING_CTRL1_EN_ASRC3_p(void);
/*! \brief Writes the bit group 'CH2_INT_CNT_SYNC_SEL' of register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL(U8 data);
/*! \brief Reads the bit group 'CH2_INT_CNT_SYNC_SEL' of register 'AUDIO_TIMING_CTRL1'. */
U8   GH_AUDIO_get_TIMING_CTRL1_CH2_INT_CNT_SYNC_SEL(void);
/*! \brief Writes the bit group 'CH1_INT_CNT_SYNC_SEL' of register 'AUDIO_TIMING_CTRL1'. */
void GH_AUDIO_set_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL(U8 data);
/*! \brief Reads the bit group 'CH1_INT_CNT_SYNC_SEL' of register 'AUDIO_TIMING_CTRL1'. */
U8   GH_AUDIO_get_TIMING_CTRL1_CH1_INT_CNT_SYNC_SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_AUDIOBAND_CTRL1 (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_AUDIOBAND_CTRL1'. */
void GH_AUDIO_set_AUDIOBAND_CTRL1(U16 data);
/*! \brief Reads the register 'AUDIO_AUDIOBAND_CTRL1'. */
U16  GH_AUDIO_get_AUDIOBAND_CTRL1(void);
/*! \brief Writes the bit group 'SDM_DWA_DATAIN_R_SEL' of register 'AUDIO_AUDIOBAND_CTRL1'. */
void GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL(U8 data);
/*! \brief Reads the bit group 'SDM_DWA_DATAIN_R_SEL' of register 'AUDIO_AUDIOBAND_CTRL1'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_R_SEL(void);
/*! \brief Writes the bit group 'SDM_DWA_DATAIN_L_SEL' of register 'AUDIO_AUDIOBAND_CTRL1'. */
void GH_AUDIO_set_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL(U8 data);
/*! \brief Reads the bit group 'SDM_DWA_DATAIN_L_SEL' of register 'AUDIO_AUDIOBAND_CTRL1'. */
U8   GH_AUDIO_get_AUDIOBAND_CTRL1_SDM_DWA_DATAIN_L_SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_FIFO_CTRL (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL(U16 data);
/*! \brief Reads the register 'AUDIO_FIFO_CTRL'. */
U16  GH_AUDIO_get_FIFO_CTRL(void);
/*! \brief Writes the bit group 'TX_FIFO_INT_EN' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_INT_EN(U8 data);
/*! \brief Reads the bit group 'TX_FIFO_INT_EN' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_INT_EN(void);
/*! \brief Writes the bit group 'TX_FIFO_ENABLE' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_ENABLE(U8 data);
/*! \brief Reads the bit group 'TX_FIFO_ENABLE' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_ENABLE(void);
/*! \brief Writes the bit group 'TX_FIFO_STATUS_CLR' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_TX_FIFO_STATUS_CLR(U8 data);
/*! \brief Reads the bit group 'TX_FIFO_STATUS_CLR' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_TX_FIFO_STATUS_CLR(void);
/*! \brief Writes the bit group 'RX_FIFO_INT_EN' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_INT_EN(U8 data);
/*! \brief Reads the bit group 'RX_FIFO_INT_EN' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_INT_EN(void);
/*! \brief Writes the bit group 'RX_FIFO_ENABLE' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_ENABLE(U8 data);
/*! \brief Reads the bit group 'RX_FIFO_ENABLE' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_ENABLE(void);
/*! \brief Writes the bit group 'RX_FIFO_STATUS_CLR' of register 'AUDIO_FIFO_CTRL'. */
void GH_AUDIO_set_FIFO_CTRL_RX_FIFO_STATUS_CLR(U8 data);
/*! \brief Reads the bit group 'RX_FIFO_STATUS_CLR' of register 'AUDIO_FIFO_CTRL'. */
U8   GH_AUDIO_get_FIFO_CTRL_RX_FIFO_STATUS_CLR(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_FIFO_STS (read)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_FIFO_STS'. */
U16  GH_AUDIO_get_FIFO_STS(void);
/*! \brief Reads the bit group 'TX_FIFO_STATUS' of register 'AUDIO_FIFO_STS'. */
U8   GH_AUDIO_get_FIFO_STS_TX_FIFO_STATUS(void);
/*! \brief Reads the bit group 'RX_FIFO_STATUS' of register 'AUDIO_FIFO_STS'. */
U8   GH_AUDIO_get_FIFO_STS_RX_FIFO_STATUS(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_5_NF_H (read)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_NF_SYNTH_5_NF_H'. */
U16  GH_AUDIO_get_NF_SYNTH_5_NF_H(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_NF_SYNTH_5_NF_L (read)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_NF_SYNTH_5_NF_L'. */
U16  GH_AUDIO_get_NF_SYNTH_5_NF_L(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_INT_CTRL (read)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'AUDIO_INT_CTRL'. */
U16  GH_AUDIO_get_INT_CTRL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_SINE_GEN_CTRL0 (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_SINE_GEN_CTRL0'. */
U16  GH_AUDIO_get_SINE_GEN_CTRL0(void);
/*! \brief Writes the bit group 'CH1_SIN_GEN_EN_p' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p(U8 data);
/*! \brief Reads the bit group 'CH1_SIN_GEN_EN_p' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_CH1_SIN_GEN_EN_p(void);
/*! \brief Writes the bit group 'CH2_SIN_GEN_EN_p' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p(U8 data);
/*! \brief Reads the bit group 'CH2_SIN_GEN_EN_p' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_CH2_SIN_GEN_EN_p(void);
/*! \brief Writes the bit group 'EN_DIT_SINE' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SINE(U8 data);
/*! \brief Reads the bit group 'EN_DIT_SINE' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SINE(void);
/*! \brief Writes the bit group 'EN_DIT_SRC' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_EN_DIT_SRC(U8 data);
/*! \brief Reads the bit group 'EN_DIT_SRC' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_EN_DIT_SRC(void);
/*! \brief Writes the bit group 'PGA2_SWAP' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_PGA2_SWAP(U8 data);
/*! \brief Reads the bit group 'PGA2_SWAP' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_PGA2_SWAP(void);
/*! \brief Writes the bit group 'PGA1_SWAP' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_PGA1_SWAP(U8 data);
/*! \brief Reads the bit group 'PGA1_SWAP' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_PGA1_SWAP(void);
/*! \brief Writes the bit group 'INT2_MIX_CTRL' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_INT2_MIX_CTRL(U8 data);
/*! \brief Reads the bit group 'INT2_MIX_CTRL' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_INT2_MIX_CTRL(void);
/*! \brief Writes the bit group 'INT1_MIX_CTRL' of register 'AUDIO_SINE_GEN_CTRL0'. */
void GH_AUDIO_set_SINE_GEN_CTRL0_INT1_MIX_CTRL(U8 data);
/*! \brief Reads the bit group 'INT1_MIX_CTRL' of register 'AUDIO_SINE_GEN_CTRL0'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL0_INT1_MIX_CTRL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_SINE_GEN_CTRL1 (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1(U16 data);
/*! \brief Reads the register 'AUDIO_SINE_GEN_CTRL1'. */
U16  GH_AUDIO_get_SINE_GEN_CTRL1(void);
/*! \brief Writes the bit group 'SINE_GEN_CH1_FREQ' of register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ(U8 data);
/*! \brief Reads the bit group 'SINE_GEN_CH1_FREQ' of register 'AUDIO_SINE_GEN_CTRL1'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_FREQ(void);
/*! \brief Writes the bit group 'SINE_GEN_CH1_GAIN' of register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN(U8 data);
/*! \brief Reads the bit group 'SINE_GEN_CH1_GAIN' of register 'AUDIO_SINE_GEN_CTRL1'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH1_GAIN(void);
/*! \brief Writes the bit group 'SINE_GEN_CH2_FREQ' of register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ(U8 data);
/*! \brief Reads the bit group 'SINE_GEN_CH2_FREQ' of register 'AUDIO_SINE_GEN_CTRL1'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_FREQ(void);
/*! \brief Writes the bit group 'SINE_GEN_CH2_GAIN' of register 'AUDIO_SINE_GEN_CTRL1'. */
void GH_AUDIO_set_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN(U8 data);
/*! \brief Reads the bit group 'SINE_GEN_CH2_GAIN' of register 'AUDIO_SINE_GEN_CTRL1'. */
U8   GH_AUDIO_get_SINE_GEN_CTRL1_SINE_GEN_CH2_GAIN(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_TEST_CTRL0 (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0(U16 data);
/*! \brief Reads the register 'AUDIO_TEST_CTRL0'. */
U16  GH_AUDIO_get_TEST_CTRL0(void);
/*! \brief Writes the bit group 'DAC_TEST_EN' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_DAC_TEST_EN(U8 data);
/*! \brief Reads the bit group 'DAC_TEST_EN' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_DAC_TEST_EN(void);
/*! \brief Writes the bit group 'SDM_TEST_EN' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_SDM_TEST_EN(U8 data);
/*! \brief Reads the bit group 'SDM_TEST_EN' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_SDM_TEST_EN(void);
/*! \brief Writes the bit group 'SDM_SFT_DIS' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_SDM_SFT_DIS(U8 data);
/*! \brief Reads the bit group 'SDM_SFT_DIS' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_SDM_SFT_DIS(void);
/*! \brief Writes the bit group 'SRAM_CG_EN' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_SRAM_CG_EN(U8 data);
/*! \brief Reads the bit group 'SRAM_CG_EN' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_SRAM_CG_EN(void);
/*! \brief Writes the bit group 'TESTCLK_SEL' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_TESTCLK_SEL(U8 data);
/*! \brief Reads the bit group 'TESTCLK_SEL' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_TESTCLK_SEL(void);
/*! \brief Writes the bit group 'TESTBUS_SEL' of register 'AUDIO_TEST_CTRL0'. */
void GH_AUDIO_set_TEST_CTRL0_TESTBUS_SEL(U8 data);
/*! \brief Reads the bit group 'TESTBUS_SEL' of register 'AUDIO_TEST_CTRL0'. */
U8   GH_AUDIO_get_TEST_CTRL0_TESTBUS_SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL00 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL00'. */
U16  GH_AUDIO_get_ANALOG_CTRL00(void);
/*! \brief Writes the bit group 'DBNC_TIME' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_DBNC_TIME(U8 data);
/*! \brief Reads the bit group 'DBNC_TIME' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_DBNC_TIME(void);
/*! \brief Writes the bit group 'MCPLS_SEL' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_SEL(U8 data);
/*! \brief Reads the bit group 'MCPLS_SEL' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_SEL(void);
/*! \brief Writes the bit group 'MCPLS_PRD' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_PRD(U8 data);
/*! \brief Reads the bit group 'MCPLS_PRD' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_PRD(void);
/*! \brief Writes the bit group '_RSTZ_AU_DET' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00__RSTZ_AU_DET(U8 data);
/*! \brief Reads the bit group '_RSTZ_AU_DET' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00__RSTZ_AU_DET(void);
/*! \brief Writes the bit group 'INT_AU_DET_TEST_VALUE' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE(U8 data);
/*! \brief Reads the bit group 'INT_AU_DET_TEST_VALUE' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_VALUE(void);
/*! \brief Writes the bit group 'INT_AU_DET_TEST_MODE' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_INT_AU_DET_TEST_MODE(U8 data);
/*! \brief Reads the bit group 'INT_AU_DET_TEST_MODE' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_INT_AU_DET_TEST_MODE(void);
/*! \brief Writes the bit group 'MCPLS_EN' of register 'AUDIO_ANALOG_CTRL00'. */
void GH_AUDIO_set_ANALOG_CTRL00_MCPLS_EN(U8 data);
/*! \brief Reads the bit group 'MCPLS_EN' of register 'AUDIO_ANALOG_CTRL00'. */
U8   GH_AUDIO_get_ANALOG_CTRL00_MCPLS_EN(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL01 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL01'. */
U16  GH_AUDIO_get_ANALOG_CTRL01(void);
/*! \brief Writes the bit group 'INT_MASK_MICLP_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_MASK_MICLP_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_PLUGIN(void);
/*! \brief Writes the bit group 'INT_MASK_MICLP_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_MASK_MICLP_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_MICLP_UNPLUG(void);
/*! \brief Writes the bit group 'INT_MASK_SPK_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_MASK_SPK_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_PLUGIN(void);
/*! \brief Writes the bit group 'INT_MASK_SPK_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_MASK_SPK_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_SPK_UNPLUG(void);
/*! \brief Writes the bit group 'INT_MASK_HS_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_MASK_HS_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_PLUGIN(void);
/*! \brief Writes the bit group 'INT_MASK_HS_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_MASK_HS_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_UNPLUG(void);
/*! \brief Writes the bit group 'INT_MASK_HS_GND' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_MASK_HS_GND(U8 data);
/*! \brief Reads the bit group 'INT_MASK_HS_GND' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_MASK_HS_GND(void);
/*! \brief Writes the bit group 'INT_CLR_MICLP_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_CLR_MICLP_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_PLUGIN(void);
/*! \brief Writes the bit group 'INT_CLR_MICLP_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_CLR_MICLP_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_MICLP_UNPLUG(void);
/*! \brief Writes the bit group 'INT_CLR_SPK_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_CLR_SPK_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_PLUGIN(void);
/*! \brief Writes the bit group 'INT_CLR_SPK_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_CLR_SPK_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_SPK_UNPLUG(void);
/*! \brief Writes the bit group 'INT_CLR_HS_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_PLUGIN(U8 data);
/*! \brief Reads the bit group 'INT_CLR_HS_PLUGIN' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_PLUGIN(void);
/*! \brief Writes the bit group 'INT_CLR_HS_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_UNPLUG(U8 data);
/*! \brief Reads the bit group 'INT_CLR_HS_UNPLUG' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_UNPLUG(void);
/*! \brief Writes the bit group 'INT_CLR_HS_GNC' of register 'AUDIO_ANALOG_CTRL01'. */
void GH_AUDIO_set_ANALOG_CTRL01_INT_CLR_HS_GNC(U8 data);
/*! \brief Reads the bit group 'INT_CLR_HS_GNC' of register 'AUDIO_ANALOG_CTRL01'. */
U8   GH_AUDIO_get_ANALOG_CTRL01_INT_CLR_HS_GNC(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL02 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL02'. */
U16  GH_AUDIO_get_ANALOG_CTRL02(void);
/*! \brief Writes the bit group 'sdm_out_3_4_12_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_3_4_12_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_sel(void);
/*! \brief Writes the bit group 'sdm_out_1_2_12_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_1_2_12_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_sel(void);
/*! \brief Writes the bit group 'sdm_out_3_4_12_swap_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_3_4_12_swap_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_4_12_swap_sel(void);
/*! \brief Writes the bit group 'sdm_out_1_2_12_swap_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_1_2_12_swap_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_2_12_swap_sel(void);
/*! \brief Writes the bit group 'sdm_out_4_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_4_12_inv_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_4_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_4_12_inv_sel(void);
/*! \brief Writes the bit group 'sdm_out_3_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_3_12_inv_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_3_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_3_12_inv_sel(void);
/*! \brief Writes the bit group 'sdm_out_2_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_2_12_inv_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_2_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_2_12_inv_sel(void);
/*! \brief Writes the bit group 'sdm_out_1_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_sdm_out_1_12_inv_sel(U8 data);
/*! \brief Reads the bit group 'sdm_out_1_12_inv_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_sdm_out_1_12_inv_sel(void);
/*! \brief Writes the bit group 'dft_sel' of register 'AUDIO_ANALOG_CTRL02'. */
void GH_AUDIO_set_ANALOG_CTRL02_dft_sel(U8 data);
/*! \brief Reads the bit group 'dft_sel' of register 'AUDIO_ANALOG_CTRL02'. */
U8   GH_AUDIO_get_ANALOG_CTRL02_dft_sel(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL03 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL03'. */
U16  GH_AUDIO_get_ANALOG_CTRL03(void);
/*! \brief Writes the bit group 'SEL_IREFDET' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_SEL_IREFDET(U8 data);
/*! \brief Reads the bit group 'SEL_IREFDET' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_SEL_IREFDET(void);
/*! \brief Writes the bit group 'REG_EN_MICBIAS_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_REG_EN_MICBIAS_12(U8 data);
/*! \brief Reads the bit group 'REG_EN_MICBIAS_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_REG_EN_MICBIAS_12(void);
/*! \brief Writes the bit group 'MICV_SEL' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_MICV_SEL(U8 data);
/*! \brief Reads the bit group 'MICV_SEL' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_MICV_SEL(void);
/*! \brief Writes the bit group 'RCV_EN_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_RCV_EN_12(U8 data);
/*! \brief Reads the bit group 'RCV_EN_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_RCV_EN_12(void);
/*! \brief Writes the bit group 'HST_EN_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_HST_EN_12(U8 data);
/*! \brief Reads the bit group 'HST_EN_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_HST_EN_12(void);
/*! \brief Writes the bit group 'EN_MICDET_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_MICDET_12(U8 data);
/*! \brief Reads the bit group 'EN_MICDET_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_MICDET_12(void);
/*! \brief Writes the bit group 'REG_CONTROL' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_REG_CONTROL(U8 data);
/*! \brief Reads the bit group 'REG_CONTROL' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_REG_CONTROL(void);
/*! \brief Writes the bit group 'REG_SEL_CONTROL' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_REG_SEL_CONTROL(U8 data);
/*! \brief Reads the bit group 'REG_SEL_CONTROL' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_REG_SEL_CONTROL(void);
/*! \brief Writes the bit group 'EN_REF_NO_BG_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_REF_NO_BG_12(U8 data);
/*! \brief Reads the bit group 'EN_REF_NO_BG_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_REF_NO_BG_12(void);
/*! \brief Writes the bit group 'EN_POLLING_DRV_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_POLLING_DRV_12(U8 data);
/*! \brief Reads the bit group 'EN_POLLING_DRV_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_POLLING_DRV_12(void);
/*! \brief Writes the bit group 'IBSEL_AUDIO' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_IBSEL_AUDIO(U8 data);
/*! \brief Reads the bit group 'IBSEL_AUDIO' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_IBSEL_AUDIO(void);
/*! \brief Writes the bit group 'EN_AUDIO_IBIAS_12' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_AUDIO_IBIAS_12(U8 data);
/*! \brief Reads the bit group 'EN_AUDIO_IBIAS_12' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_AUDIO_IBIAS_12(void);
/*! \brief Writes the bit group 'EN_CLK_TST' of register 'AUDIO_ANALOG_CTRL03'. */
void GH_AUDIO_set_ANALOG_CTRL03_EN_CLK_TST(U8 data);
/*! \brief Reads the bit group 'EN_CLK_TST' of register 'AUDIO_ANALOG_CTRL03'. */
U8   GH_AUDIO_get_ANALOG_CTRL03_EN_CLK_TST(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL04 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL04'. */
U16  GH_AUDIO_get_ANALOG_CTRL04(void);
/*! \brief Writes the bit group 'PGA0_MICA2SEL' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2SEL(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA2SEL' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2SEL(void);
/*! \brief Writes the bit group 'PGA0_MICA2_GAIN' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA2_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA2_GAIN' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA2_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA0_MICA2' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA2(U8 data);
/*! \brief Reads the bit group 'EN_PGA0_MICA2' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA2(void);
/*! \brief Writes the bit group 'PGA0_MICA1_GAIN' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_PGA0_MICA1_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA1_GAIN' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_PGA0_MICA1_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA0_MICA1' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_PGA0_MICA1(U8 data);
/*! \brief Reads the bit group 'EN_PGA0_MICA1' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_PGA0_MICA1(void);
/*! \brief Writes the bit group 'IBIAS_PGA0' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_IBIAS_PGA0(U8 data);
/*! \brief Reads the bit group 'IBIAS_PGA0' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_IBIAS_PGA0(void);
/*! \brief Writes the bit group 'EN_IBIAS_PGA0' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_IBIAS_PGA0(U8 data);
/*! \brief Reads the bit group 'EN_IBIAS_PGA0' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_IBIAS_PGA0(void);
/*! \brief Writes the bit group 'EN_VCMBUF0_12' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_VCMBUF0_12(U8 data);
/*! \brief Reads the bit group 'EN_VCMBUF0_12' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_VCMBUF0_12(void);
/*! \brief Writes the bit group 'SEL_VCMREF0' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_SEL_VCMREF0(U8 data);
/*! \brief Reads the bit group 'SEL_VCMREF0' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_SEL_VCMREF0(void);
/*! \brief Writes the bit group 'PULLUP_HSIP' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_PULLUP_HSIP(U8 data);
/*! \brief Reads the bit group 'PULLUP_HSIP' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_PULLUP_HSIP(void);
/*! \brief Writes the bit group 'EN_MICDET_LP_12' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_MICDET_LP_12(U8 data);
/*! \brief Reads the bit group 'EN_MICDET_LP_12' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_MICDET_LP_12(void);
/*! \brief Writes the bit group 'EN_MICTRIM_12' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_EN_MICTRIM_12(U8 data);
/*! \brief Reads the bit group 'EN_MICTRIM_12' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_EN_MICTRIM_12(void);
/*! \brief Writes the bit group 'SEL_IREFGND' of register 'AUDIO_ANALOG_CTRL04'. */
void GH_AUDIO_set_ANALOG_CTRL04_SEL_IREFGND(U8 data);
/*! \brief Reads the bit group 'SEL_IREFGND' of register 'AUDIO_ANALOG_CTRL04'. */
U8   GH_AUDIO_get_ANALOG_CTRL04_SEL_IREFGND(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL05 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL05'. */
U16  GH_AUDIO_get_ANALOG_CTRL05(void);
/*! \brief Writes the bit group 'IBIAS_PGA1' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_IBIAS_PGA1(U8 data);
/*! \brief Reads the bit group 'IBIAS_PGA1' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_IBIAS_PGA1(void);
/*! \brief Writes the bit group 'EN_IBIAS_PGA1' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_EN_IBIAS_PGA1(U8 data);
/*! \brief Reads the bit group 'EN_IBIAS_PGA1' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_EN_IBIAS_PGA1(void);
/*! \brief Writes the bit group 'EN_VCMBUF1' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_EN_VCMBUF1(U8 data);
/*! \brief Reads the bit group 'EN_VCMBUF1' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_EN_VCMBUF1(void);
/*! \brief Writes the bit group 'SEL_VCMREF1' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_SEL_VCMREF1(U8 data);
/*! \brief Reads the bit group 'SEL_VCMREF1' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_SEL_VCMREF1(void);
/*! \brief Writes the bit group 'PGA0_LINE_SEL' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_LINE_SEL(U8 data);
/*! \brief Reads the bit group 'PGA0_LINE_SEL' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_LINE_SEL(void);
/*! \brief Writes the bit group 'PGA0_MUTE_R' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_R(U8 data);
/*! \brief Reads the bit group 'PGA0_MUTE_R' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_R(void);
/*! \brief Writes the bit group 'PGA0_MICA4_SEL' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_SEL(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA4_SEL' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_SEL(void);
/*! \brief Writes the bit group 'PGA0_MICA4_GAIN' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA4_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA4_GAIN' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA4_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA0_MICA4' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA4(U8 data);
/*! \brief Reads the bit group 'EN_PGA0_MICA4' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA4(void);
/*! \brief Writes the bit group 'PGA0_MICA3_GAIN' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA3_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA3_GAIN' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA3_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA0_MICA3' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_EN_PGA0_MICA3(U8 data);
/*! \brief Reads the bit group 'EN_PGA0_MICA3' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_EN_PGA0_MICA3(void);
/*! \brief Writes the bit group 'PGA0_MUTE_L' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MUTE_L(U8 data);
/*! \brief Reads the bit group 'PGA0_MUTE_L' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MUTE_L(void);
/*! \brief Writes the bit group 'PGA0_MICA2SEL' of register 'AUDIO_ANALOG_CTRL05'. */
void GH_AUDIO_set_ANALOG_CTRL05_PGA0_MICA2SEL(U8 data);
/*! \brief Reads the bit group 'PGA0_MICA2SEL' of register 'AUDIO_ANALOG_CTRL05'. */
U8   GH_AUDIO_get_ANALOG_CTRL05_PGA0_MICA2SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL06 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL06'. */
U16  GH_AUDIO_get_ANALOG_CTRL06(void);
/*! \brief Writes the bit group 'EN_DAC0_R_12' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_R_12(U8 data);
/*! \brief Reads the bit group 'EN_DAC0_R_12' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_R_12(void);
/*! \brief Writes the bit group 'EN_DAC0_L_12' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_L_12(U8 data);
/*! \brief Reads the bit group 'EN_DAC0_L_12' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_L_12(void);
/*! \brief Writes the bit group 'EN_DAC0_LDO11' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_DAC0_LDO11(U8 data);
/*! \brief Reads the bit group 'EN_DAC0_LDO11' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_DAC0_LDO11(void);
/*! \brief Writes the bit group 'LDO11_VC0' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_LDO11_VC0(U8 data);
/*! \brief Reads the bit group 'LDO11_VC0' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_LDO11_VC0(void);
/*! \brief Writes the bit group 'POS_RL0' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_POS_RL0(U8 data);
/*! \brief Reads the bit group 'POS_RL0' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_POS_RL0(void);
/*! \brief Writes the bit group 'PGA1_LINE_SEL' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_LINE_SEL(U8 data);
/*! \brief Reads the bit group 'PGA1_LINE_SEL' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_LINE_SEL(void);
/*! \brief Writes the bit group 'PGA1_MUTE_R' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_R(U8 data);
/*! \brief Reads the bit group 'PGA1_MUTE_R' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_R(void);
/*! \brief Writes the bit group 'PGA1_MICA4_GAIN' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA4_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA1_MICA4_GAIN' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA4_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA1_MICA4' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA4(U8 data);
/*! \brief Reads the bit group 'EN_PGA1_MICA4' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA4(void);
/*! \brief Writes the bit group 'PGA1_MUTE_L' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MUTE_L(U8 data);
/*! \brief Reads the bit group 'PGA1_MUTE_L' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MUTE_L(void);
/*! \brief Writes the bit group 'PGA1_MICA2_GAIN' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_PGA1_MICA2_GAIN(U8 data);
/*! \brief Reads the bit group 'PGA1_MICA2_GAIN' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_PGA1_MICA2_GAIN(void);
/*! \brief Writes the bit group 'EN_PGA1_MICA2' of register 'AUDIO_ANALOG_CTRL06'. */
void GH_AUDIO_set_ANALOG_CTRL06_EN_PGA1_MICA2(U8 data);
/*! \brief Reads the bit group 'EN_PGA1_MICA2' of register 'AUDIO_ANALOG_CTRL06'. */
U8   GH_AUDIO_get_ANALOG_CTRL06_EN_PGA1_MICA2(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL07 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL07'. */
U16  GH_AUDIO_get_ANALOG_CTRL07(void);
/*! \brief Writes the bit group 'EN_ADC1_DIT' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC1_DIT(U8 data);
/*! \brief Reads the bit group 'EN_ADC1_DIT' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC1_DIT(void);
/*! \brief Writes the bit group 'EN_ADC0_12' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_12(U8 data);
/*! \brief Reads the bit group 'EN_ADC0_12' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_12(void);
/*! \brief Writes the bit group 'SHRT_ADC0_L' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_L(U8 data);
/*! \brief Reads the bit group 'SHRT_ADC0_L' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_L(void);
/*! \brief Writes the bit group 'SHRT_ADC0_R' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_SHRT_ADC0_R(U8 data);
/*! \brief Reads the bit group 'SHRT_ADC0_R' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_SHRT_ADC0_R(void);
/*! \brief Writes the bit group 'RESET_ADC0_L' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_L(U8 data);
/*! \brief Reads the bit group 'RESET_ADC0_L' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_L(void);
/*! \brief Writes the bit group 'RESET_ADC0_R' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_RESET_ADC0_R(U8 data);
/*! \brief Reads the bit group 'RESET_ADC0_R' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_RESET_ADC0_R(void);
/*! \brief Writes the bit group 'SEL_IBIAS_ADC0' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_SEL_IBIAS_ADC0(U8 data);
/*! \brief Reads the bit group 'SEL_IBIAS_ADC0' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_SEL_IBIAS_ADC0(void);
/*! \brief Writes the bit group 'SEL_DIT_LVL_ADC0' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_SEL_DIT_LVL_ADC0(U8 data);
/*! \brief Reads the bit group 'SEL_DIT_LVL_ADC0' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_SEL_DIT_LVL_ADC0(void);
/*! \brief Writes the bit group 'EN_ADC0_DIT' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_ADC0_DIT(U8 data);
/*! \brief Reads the bit group 'EN_ADC0_DIT' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_ADC0_DIT(void);
/*! \brief Writes the bit group 'EN_DAC1_R_12' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_R_12(U8 data);
/*! \brief Reads the bit group 'EN_DAC1_R_12' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_R_12(void);
/*! \brief Writes the bit group 'EN_DAC1_L_12' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_L_12(U8 data);
/*! \brief Reads the bit group 'EN_DAC1_L_12' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_L_12(void);
/*! \brief Writes the bit group 'EN_DAC1_LDO11' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_EN_DAC1_LDO11(U8 data);
/*! \brief Reads the bit group 'EN_DAC1_LDO11' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_EN_DAC1_LDO11(void);
/*! \brief Writes the bit group 'LDO11_VC1' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_LDO11_VC1(U8 data);
/*! \brief Reads the bit group 'LDO11_VC1' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_LDO11_VC1(void);
/*! \brief Writes the bit group 'POS_RL1' of register 'AUDIO_ANALOG_CTRL07'. */
void GH_AUDIO_set_ANALOG_CTRL07_POS_RL1(U8 data);
/*! \brief Reads the bit group 'POS_RL1' of register 'AUDIO_ANALOG_CTRL07'. */
U8   GH_AUDIO_get_ANALOG_CTRL07_POS_RL1(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL08 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL08'. */
U16  GH_AUDIO_get_ANALOG_CTRL08(void);
/*! \brief Writes the bit group 'GAIN_EAR' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_GAIN_EAR(U8 data);
/*! \brief Reads the bit group 'GAIN_EAR' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_GAIN_EAR(void);
/*! \brief Writes the bit group 'EN_STG2AB_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_STG2AB_12(U8 data);
/*! \brief Reads the bit group 'EN_STG2AB_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_STG2AB_12(void);
/*! \brief Writes the bit group 'EN_OPLP_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_OPLP_12(U8 data);
/*! \brief Reads the bit group 'EN_OPLP_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_OPLP_12(void);
/*! \brief Writes the bit group 'EN_EARL_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_EARL_12(U8 data);
/*! \brief Reads the bit group 'EN_EARL_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_EARL_12(void);
/*! \brief Writes the bit group 'EN_EARR_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_EARR_12(U8 data);
/*! \brief Reads the bit group 'EN_EARR_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_EARR_12(void);
/*! \brief Writes the bit group 'EN_ADC1_12' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_EN_ADC1_12(U8 data);
/*! \brief Reads the bit group 'EN_ADC1_12' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_EN_ADC1_12(void);
/*! \brief Writes the bit group 'SHRT_ADC1_L' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_L(U8 data);
/*! \brief Reads the bit group 'SHRT_ADC1_L' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_L(void);
/*! \brief Writes the bit group 'SHRT_ADC1_R' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_SHRT_ADC1_R(U8 data);
/*! \brief Reads the bit group 'SHRT_ADC1_R' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_SHRT_ADC1_R(void);
/*! \brief Writes the bit group 'RESET_ADC1_L' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_L(U8 data);
/*! \brief Reads the bit group 'RESET_ADC1_L' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_L(void);
/*! \brief Writes the bit group 'RESET_ADC1_R' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_RESET_ADC1_R(U8 data);
/*! \brief Reads the bit group 'RESET_ADC1_R' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_RESET_ADC1_R(void);
/*! \brief Writes the bit group 'SEL_IBIAS_ADC1' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_SEL_IBIAS_ADC1(U8 data);
/*! \brief Reads the bit group 'SEL_IBIAS_ADC1' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_SEL_IBIAS_ADC1(void);
/*! \brief Writes the bit group 'SEL_DIT_LVL_ADC1' of register 'AUDIO_ANALOG_CTRL08'. */
void GH_AUDIO_set_ANALOG_CTRL08_SEL_DIT_LVL_ADC1(U8 data);
/*! \brief Reads the bit group 'SEL_DIT_LVL_ADC1' of register 'AUDIO_ANALOG_CTRL08'. */
U8   GH_AUDIO_get_ANALOG_CTRL08_SEL_DIT_LVL_ADC1(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL09 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL09'. */
U16  GH_AUDIO_get_ANALOG_CTRL09(void);
/*! \brief Writes the bit group 'MX_EAR' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_MX_EAR(U8 data);
/*! \brief Reads the bit group 'MX_EAR' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_MX_EAR(void);
/*! \brief Writes the bit group 'ISEL_OCP' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_ISEL_OCP(U8 data);
/*! \brief Reads the bit group 'ISEL_OCP' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_ISEL_OCP(void);
/*! \brief Writes the bit group 'ISEL_DRV' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_ISEL_DRV(U8 data);
/*! \brief Reads the bit group 'ISEL_DRV' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_ISEL_DRV(void);
/*! \brief Writes the bit group 'TST_DRV' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_TST_DRV(U8 data);
/*! \brief Reads the bit group 'TST_DRV' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_TST_DRV(void);
/*! \brief Writes the bit group 'EAR_MUTE' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_EAR_MUTE(U8 data);
/*! \brief Reads the bit group 'EAR_MUTE' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_EAR_MUTE(void);
/*! \brief Writes the bit group 'EAR_POPRES' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_EAR_POPRES(U8 data);
/*! \brief Reads the bit group 'EAR_POPRES' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_EAR_POPRES(void);
/*! \brief Writes the bit group 'TCSEL' of register 'AUDIO_ANALOG_CTRL09'. */
void GH_AUDIO_set_ANALOG_CTRL09_TCSEL(U8 data);
/*! \brief Reads the bit group 'TCSEL' of register 'AUDIO_ANALOG_CTRL09'. */
U8   GH_AUDIO_get_ANALOG_CTRL09_TCSEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL10 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL10'. */
U16  GH_AUDIO_get_ANALOG_CTRL10(void);
/*! \brief Writes the bit group 'MUTE_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE1(U8 data);
/*! \brief Reads the bit group 'MUTE_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE1(void);
/*! \brief Writes the bit group 'MX_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_MX_LINE1(U8 data);
/*! \brief Reads the bit group 'MX_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_MX_LINE1(void);
/*! \brief Writes the bit group 'GAIN_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE1(U8 data);
/*! \brief Reads the bit group 'GAIN_LINE1' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE1(void);
/*! \brief Writes the bit group 'EN_LINE1_R' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_R(U8 data);
/*! \brief Reads the bit group 'EN_LINE1_R' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_R(void);
/*! \brief Writes the bit group 'EN_LINE1_L' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE1_L(U8 data);
/*! \brief Reads the bit group 'EN_LINE1_L' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE1_L(void);
/*! \brief Writes the bit group 'MUTE_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_MUTE_LINE0(U8 data);
/*! \brief Reads the bit group 'MUTE_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_MUTE_LINE0(void);
/*! \brief Writes the bit group 'MX_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_MX_LINE0(U8 data);
/*! \brief Reads the bit group 'MX_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_MX_LINE0(void);
/*! \brief Writes the bit group 'GAIN_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_GAIN_LINE0(U8 data);
/*! \brief Reads the bit group 'GAIN_LINE0' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_GAIN_LINE0(void);
/*! \brief Writes the bit group 'EN_LINE0_R' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_R(U8 data);
/*! \brief Reads the bit group 'EN_LINE0_R' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_R(void);
/*! \brief Writes the bit group 'EN_LINE0_L' of register 'AUDIO_ANALOG_CTRL10'. */
void GH_AUDIO_set_ANALOG_CTRL10_EN_LINE0_L(U8 data);
/*! \brief Reads the bit group 'EN_LINE0_L' of register 'AUDIO_ANALOG_CTRL10'. */
U8   GH_AUDIO_get_ANALOG_CTRL10_EN_LINE0_L(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL11 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL11'. */
U16  GH_AUDIO_get_ANALOG_CTRL11(void);
/*! \brief Writes the bit group 'TST_AUTIO' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_TST_AUTIO(U8 data);
/*! \brief Reads the bit group 'TST_AUTIO' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_TST_AUTIO(void);
/*! \brief Writes the bit group 'SEL_CK_AUDIO' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_SEL_CK_AUDIO(U8 data);
/*! \brief Reads the bit group 'SEL_CK_AUDIO' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_SEL_CK_AUDIO(void);
/*! \brief Writes the bit group 'SEL_PHS_ADCCLK' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_SEL_PHS_ADCCLK(U8 data);
/*! \brief Reads the bit group 'SEL_PHS_ADCCLK' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_SEL_PHS_ADCCLK(void);
/*! \brief Writes the bit group 'ADC_CLK_FREQ' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_ADC_CLK_FREQ(U8 data);
/*! \brief Reads the bit group 'ADC_CLK_FREQ' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_ADC_CLK_FREQ(void);
/*! \brief Writes the bit group 'DAC_CLK_FREQ' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_DAC_CLK_FREQ(U8 data);
/*! \brief Reads the bit group 'DAC_CLK_FREQ' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_DAC_CLK_FREQ(void);
/*! \brief Writes the bit group 'EN_CLK' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_EN_CLK(U8 data);
/*! \brief Reads the bit group 'EN_CLK' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_EN_CLK(void);
/*! \brief Writes the bit group 'V_SET_LDO25' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_V_SET_LDO25(U8 data);
/*! \brief Reads the bit group 'V_SET_LDO25' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_V_SET_LDO25(void);
/*! \brief Writes the bit group 'EN_LDO25_12' of register 'AUDIO_ANALOG_CTRL11'. */
void GH_AUDIO_set_ANALOG_CTRL11_EN_LDO25_12(U8 data);
/*! \brief Reads the bit group 'EN_LDO25_12' of register 'AUDIO_ANALOG_CTRL11'. */
U8   GH_AUDIO_get_ANALOG_CTRL11_EN_LDO25_12(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL12 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL12'. */
void GH_AUDIO_set_ANALOG_CTRL12(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL12'. */
U16  GH_AUDIO_get_ANALOG_CTRL12(void);
/*! \brief Writes the bit group 'AUDIO_REG' of register 'AUDIO_ANALOG_CTRL12'. */
void GH_AUDIO_set_ANALOG_CTRL12_AUDIO_REG(U8 data);
/*! \brief Reads the bit group 'AUDIO_REG' of register 'AUDIO_ANALOG_CTRL12'. */
U8   GH_AUDIO_get_ANALOG_CTRL12_AUDIO_REG(void);
/*! \brief Writes the bit group 'TEST_BUS_SEL' of register 'AUDIO_ANALOG_CTRL12'. */
void GH_AUDIO_set_ANALOG_CTRL12_TEST_BUS_SEL(U8 data);
/*! \brief Reads the bit group 'TEST_BUS_SEL' of register 'AUDIO_ANALOG_CTRL12'. */
U8   GH_AUDIO_get_ANALOG_CTRL12_TEST_BUS_SEL(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL13 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL13'. */
U16  GH_AUDIO_get_ANALOG_CTRL13(void);
/*! \brief Writes the bit group 'MIC_TRIM_SEL_CFG' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_MIC_TRIM_SEL_CFG(U8 data);
/*! \brief Reads the bit group 'MIC_TRIM_SEL_CFG' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_MIC_TRIM_SEL_CFG(void);
/*! \brief Writes the bit group 'TRIM_STOP_SEL' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP_SEL(U8 data);
/*! \brief Reads the bit group 'TRIM_STOP_SEL' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP_SEL(void);
/*! \brief Writes the bit group 'RSTZ_TRIM_AU' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_RSTZ_TRIM_AU(U8 data);
/*! \brief Reads the bit group 'RSTZ_TRIM_AU' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_RSTZ_TRIM_AU(void);
/*! \brief Writes the bit group 'TRIM_AU_SEL' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_TRIM_AU_SEL(U8 data);
/*! \brief Reads the bit group 'TRIM_AU_SEL' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_AU_SEL(void);
/*! \brief Writes the bit group 'TRIM_STOP' of register 'AUDIO_ANALOG_CTRL13'. */
void GH_AUDIO_set_ANALOG_CTRL13_TRIM_STOP(U8 data);
/*! \brief Reads the bit group 'TRIM_STOP' of register 'AUDIO_ANALOG_CTRL13'. */
U8   GH_AUDIO_get_ANALOG_CTRL13_TRIM_STOP(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL14 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL14'. */
void GH_AUDIO_set_ANALOG_CTRL14(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL14'. */
U16  GH_AUDIO_get_ANALOG_CTRL14(void);
/*! \brief Writes the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL14'. */
void GH_AUDIO_set_ANALOG_CTRL14_READ_BACK(U16 data);
/*! \brief Reads the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL14'. */
U16  GH_AUDIO_get_ANALOG_CTRL14_READ_BACK(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL15 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL15'. */
void GH_AUDIO_set_ANALOG_CTRL15(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL15'. */
U16  GH_AUDIO_get_ANALOG_CTRL15(void);
/*! \brief Writes the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL15'. */
void GH_AUDIO_set_ANALOG_CTRL15_READ_BACK(U16 data);
/*! \brief Reads the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL15'. */
U16  GH_AUDIO_get_ANALOG_CTRL15_READ_BACK(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL16 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL16'. */
void GH_AUDIO_set_ANALOG_CTRL16(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL16'. */
U16  GH_AUDIO_get_ANALOG_CTRL16(void);
/*! \brief Writes the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL16'. */
void GH_AUDIO_set_ANALOG_CTRL16_READ_BACK(U16 data);
/*! \brief Reads the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL16'. */
U16  GH_AUDIO_get_ANALOG_CTRL16_READ_BACK(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL17 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL17'. */
void GH_AUDIO_set_ANALOG_CTRL17(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL17'. */
U16  GH_AUDIO_get_ANALOG_CTRL17(void);
/*! \brief Writes the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL17'. */
void GH_AUDIO_set_ANALOG_CTRL17_READ_BACK(U16 data);
/*! \brief Reads the bit group 'READ_BACK' of register 'AUDIO_ANALOG_CTRL17'. */
U16  GH_AUDIO_get_ANALOG_CTRL17_READ_BACK(void);

/*----------------------------------------------------------------------------*/
/* register AUDIO_ANALOG_CTRL18 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'AUDIO_ANALOG_CTRL18'. */
void GH_AUDIO_set_ANALOG_CTRL18(U16 data);
/*! \brief Reads the register 'AUDIO_ANALOG_CTRL18'. */
U16  GH_AUDIO_get_ANALOG_CTRL18(void);
/*! \brief Writes the bit group 'AUDIO_SLEEP_DBG_BUS' of register 'AUDIO_ANALOG_CTRL18'. */
void GH_AUDIO_set_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS(U16 data);
/*! \brief Reads the bit group 'AUDIO_SLEEP_DBG_BUS' of register 'AUDIO_ANALOG_CTRL18'. */
U16  GH_AUDIO_get_ANALOG_CTRL18_AUDIO_SLEEP_DBG_BUS(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_AUDIO_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_audio.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_AUDIO_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

