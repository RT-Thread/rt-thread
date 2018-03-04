/******************************************************************************
**
** \file      gh_hdmi.c
**
** \brief     Video/Sensor Input.
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
#include "gh_hdmi.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_HDMI_INT_ENABLE_REAL                            FIO_ADDRESS(HDMI,0x60013000) /* read/write */
#define REG_HDMI_INT_STS_REAL                               FIO_ADDRESS(HDMI,0x60013004) /* read */
#define REG_HDMI_OP_MODE_REAL                               FIO_ADDRESS(HDMI,0x60013008) /* read/write */
#define REG_HDMI_CLOCK_GATED_REAL                           FIO_ADDRESS(HDMI,0x6001300C) /* read/write */
#define REG_HDMI_HDMISE_SOFT_RESETN_REAL                    FIO_ADDRESS(HDMI,0x60013010) /* read/write */
#define REG_HDMI_STS_REAL                                   FIO_ADDRESS(HDMI,0x60013104) /* read/write */
#define REG_HDMI_AUNIT_MCLK_REAL                            FIO_ADDRESS(HDMI,0x60013100) /* read/write */
#define REG_HDMI_AUNIT_NCTS_CTRL_REAL                       FIO_ADDRESS(HDMI,0x60013104) /* read/write */
#define REG_HDMI_AUNIT_N_REAL                               FIO_ADDRESS(HDMI,0x60013108) /* read/write */
#define REG_HDMI_AUNIT_CTS_REAL                             FIO_ADDRESS(HDMI,0x6001310C) /* read/write */
#define REG_HDMI_AUNIT_SRC_REAL                             FIO_ADDRESS(HDMI,0x60013110) /* read/write */
#define REG_HDMI_AUNIT_CS0_REAL                             FIO_ADDRESS(HDMI,0x60013114) /* read/write */
#define REG_HDMI_AUNIT_CS1_REAL                             FIO_ADDRESS(HDMI,0x60013118) /* read/write */
#define REG_HDMI_AUNIT_CS2_REAL                             FIO_ADDRESS(HDMI,0x6001311C) /* read/write */
#define REG_HDMI_AUNIT_CS3_REAL                             FIO_ADDRESS(HDMI,0x60013120) /* read/write */
#define REG_HDMI_AUNIT_CS4_REAL                             FIO_ADDRESS(HDMI,0x60013124) /* read/write */
#define REG_HDMI_AUNIT_CS5_REAL                             FIO_ADDRESS(HDMI,0x60013128) /* read/write */
#define REG_HDMI_AUNIT_LAYOUT_REAL                          FIO_ADDRESS(HDMI,0x6001312C) /* read/write */
#define REG_HDMI_PACKET_TX_CTRL_REAL                        FIO_ADDRESS(HDMI,0x60013130) /* read/write */
#define REG_HDMI_PACKET_GENERAL_CTRL_REAL                   FIO_ADDRESS(HDMI,0x60013134) /* read/write */
#define REG_HDMI_PACKET0_REAL                               FIO_ADDRESS(HDMI,0x60013138) /* read/write */
#define REG_HDMI_PACKET1_REAL                               FIO_ADDRESS(HDMI,0x6001313C) /* read/write */
#define REG_HDMI_PACKET2_REAL                               FIO_ADDRESS(HDMI,0x60013140) /* read/write */
#define REG_HDMI_PACKET3_REAL                               FIO_ADDRESS(HDMI,0x60013144) /* read/write */
#define REG_HDMI_PACKET4_REAL                               FIO_ADDRESS(HDMI,0x60013148) /* read/write */
#define REG_HDMI_PACKET5_REAL                               FIO_ADDRESS(HDMI,0x6001314C) /* read/write */
#define REG_HDMI_PACKET6_REAL                               FIO_ADDRESS(HDMI,0x60013150) /* read/write */
#define REG_HDMI_PACKET7_REAL                               FIO_ADDRESS(HDMI,0x60013154) /* read/write */
#define REG_HDMI_PACKET8_REAL                               FIO_ADDRESS(HDMI,0x60013158) /* read/write */
#define REG_HDMI_I2S_MODE_REAL                              FIO_ADDRESS(HDMI,0x60013258) /* read/write */
#define REG_HDMI_I2S_RX_CTRL_REAL                           FIO_ADDRESS(HDMI,0x6001325C) /* read/write */
#define REG_HDMI_I2S_WLEN_REAL                              FIO_ADDRESS(HDMI,0x60013260) /* read/write */
#define REG_HDMI_I2S_WPOS_REAL                              FIO_ADDRESS(HDMI,0x60013264) /* read/write */
#define REG_HDMI_I2S_SLOT_REAL                              FIO_ADDRESS(HDMI,0x60013268) /* read/write */
#define REG_HDMI_I2S_RX_FIFO_GTH_REAL                       FIO_ADDRESS(HDMI,0x6001326C) /* read/write */
#define REG_HDMI_I2S_CLOCK_REAL                             FIO_ADDRESS(HDMI,0x60013270) /* read/write */
#define REG_HDMI_I2S_INIT_REAL                              FIO_ADDRESS(HDMI,0x60013274) /* read/write */
#define REG_HDMI_I2S_RX_DATA_REAL                           FIO_ADDRESS(HDMI,0x60013278) /* read/write */
#define REG_HDMI_I2S_FIFO_CNTR_REAL                         FIO_ADDRESS(HDMI,0x60013284) /* read/write */
#define REG_HDMI_I2S_GATE_OFF_REAL                          FIO_ADDRESS(HDMI,0x60013288) /* read/write */
#define REG_HDMI_PACKET_MISC_REAL                           FIO_ADDRESS(HDMI,0x6001328C) /* read/write */
#define REG_HDMI_VUNIT_VBLANK_REAL                          FIO_ADDRESS(HDMI,0x60013290) /* read/write */
#define REG_HDMI_VUNIT_HBLANK_REAL                          FIO_ADDRESS(HDMI,0x60013294) /* read/write */
#define REG_HDMI_VUNIT_VACTIVE_REAL                         FIO_ADDRESS(HDMI,0x60013298) /* read/write */
#define REG_HDMI_VUNIT_HACTIVE_REAL                         FIO_ADDRESS(HDMI,0x6001329C) /* read/write */
#define REG_HDMI_VUNIT_CTRL_REAL                            FIO_ADDRESS(HDMI,0x600132A0) /* read/write */
#define REG_HDMI_VUNIT_VSYNC_DETECT_REAL                    FIO_ADDRESS(HDMI,0x600132A4) /* read/write */
#define REG_HDMI_HDMISE_TM_REAL                             FIO_ADDRESS(HDMI,0x600132A8) /* read/write */
#define REG_HDMI_P2P_AFIFO_LEVEL_REAL                       FIO_ADDRESS(HDMI,0x600132AC) /* read/write */
#define REG_HDMI_P2P_AFIFO_CTRL_REAL                        FIO_ADDRESS(HDMI,0x600132B0) /* read/write */
#define REG_HDMI_HDMISE_DBG_REAL                            FIO_ADDRESS(HDMI,0x600132B4) /* read/write */
#define REG_HDMI_HDMI_PHY_CTRL_REAL                         FIO_ADDRESS(HDMI,0x60013600) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* HDMI_INT_ENABLE */
    U32 all;
    struct {
        U32 vsync_active_detect_en      : 1;
        U32 hot_plug_detect_en          : 1;
        U32 hot_plug_loss_en            : 1;
        U32 cec_rx_interrupt_en         : 1;
        U32 cec_tx_interrupt_fail_en    : 1;
        U32 cec_tx_interrupt_ok_en      : 1;
        U32                             : 7;
        U32 phy_rx_sense_en             : 1;
        U32 i2s_rx_fifo_empty_en        : 1;
        U32 i2s_rx_fifo_full_en         : 1;
        U32 i2s_rx_fifo_over_en         : 1;
        U32 i2s_rx_gth_valid_en         : 1;
        U32 i2s_rx_idle_en              : 1;
        U32 cts_change_en               : 1;
        U32 p2p_wfull_en                : 1;
        U32 p2p_rempty_en               : 1;
        U32 p2p_below_lb_en             : 1;
        U32 p2p_exceed_ub_en            : 1;
        U32 hdmise_idle_en              : 1;
        U32 phy_rx_sense_remove_en      : 1;
        U32                             : 6;
    } bitc;
} GH_HDMI_INT_ENABLE_REAL_S;

typedef union { /* HDMI_INT_STS */
    U32 all;
    struct {
        U32 vsync_active_detect         : 1;
        U32 hot_plug_detect             : 1;
        U32 hot_plug_loss               : 1;
        U32 cec_rx_interrupt            : 1;
        U32 cec_tx_interrupt_fail       : 1;
        U32 cec_tx_interrupt_ok         : 1;
        U32                             : 7;
        U32 phy_rx_sense                : 1;
        U32 i2s_rx_fifo_empty           : 1;
        U32 i2s_rx_fifo_full            : 1;
        U32 i2s_rx_fifo_over            : 1;
        U32 i2s_rx_gth_valid            : 1;
        U32 i2s_rx_idle                 : 1;
        U32 cts_change                  : 1;
        U32 p2p_wfull                   : 1;
        U32 p2p_rempty                  : 1;
        U32 p2p_below_lb                : 1;
        U32 p2p_exceed_ub               : 1;
        U32 hdmise_idle                 : 1;
        U32 phy_rx_sense_remove         : 1;
        U32                             : 6;
    } bitc;
} GH_HDMI_INT_STS_REAL_S;

typedef union { /* HDMI_OP_MODE */
    U32 all;
    struct {
        U32 op_mode                     : 1;
        U32 op_en                       : 1;
        U32                             : 30;
    } bitc;
} GH_HDMI_OP_MODE_REAL_S;

typedef union { /* HDMI_CLOCK_GATED */
    U32 all;
    struct {
        U32 hdmise_clock_en             : 1;
        U32                             : 1;
        U32 cec_clock_en                : 1;
        U32                             : 29;
    } bitc;
} GH_HDMI_CLOCK_GATED_REAL_S;

typedef union { /* HDMI_HDMISE_SOFT_RESETN */
    U32 all;
    struct {
        U32 hdmise_soft_resetn          : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_HDMISE_SOFT_RESETN_REAL_S;

typedef union { /* HDMI_AUNIT_MCLK */
    U32 all;
    struct {
        U32 mclk_conf                   : 3;
        U32                             : 29;
    } bitc;
} GH_HDMI_AUNIT_MCLK_REAL_S;

typedef union { /* HDMI_AUNIT_NCTS_CTRL */
    U32 all;
    struct {
        U32 cts_sel                     : 1;
        U32 ncts_en                     : 1;
        U32                             : 30;
    } bitc;
} GH_HDMI_AUNIT_NCTS_CTRL_REAL_S;

typedef union { /* HDMI_AUNIT_N */
    U32 all;
    struct {
        U32 aunit_n                     : 20;
        U32                             : 12;
    } bitc;
} GH_HDMI_AUNIT_N_REAL_S;

typedef union { /* HDMI_AUNIT_CTS */
    U32 all;
    struct {
        U32 aunit_cts                   : 20;
        U32                             : 12;
    } bitc;
} GH_HDMI_AUNIT_CTS_REAL_S;

typedef union { /* HDMI_AUNIT_SRC */
    U32 all;
    struct {
        U32 i2s0_en                     : 1;
        U32 i2s1_en                     : 1;
        U32 i2s2_en                     : 1;
        U32 flat_line0                  : 1;
        U32 flat_line1                  : 1;
        U32 flat_line2                  : 1;
        U32                             : 26;
    } bitc;
} GH_HDMI_AUNIT_SRC_REAL_S;

typedef union { /* HDMI_AUNIT_LAYOUT */
    U32 all;
    struct {
        U32 layout                      : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_AUNIT_LAYOUT_REAL_S;

typedef union { /* HDMI_PACKET_TX_CTRL */
    U32 all;
    struct {
        U32 gen_en                      : 1;
        U32 gen_rpt                     : 1;
        U32 acp_en                      : 1;
        U32 acp_rpt                     : 1;
        U32 isrc_en                     : 1;
        U32 isrc_rpt                    : 1;
        U32 avi_en                      : 1;
        U32 avi_rpt                     : 1;
        U32 spd_en                      : 1;
        U32 spd_rpt                     : 1;
        U32 aud_en                      : 1;
        U32 aud_rpt                     : 1;
        U32 mpeg_en                     : 1;
        U32 mpeg_rpt                    : 1;
        U32 gamut_en                    : 1;
        U32 gamut_rpt                   : 1;
        U32                             : 15;
        U32 buf_switch_en               : 1;
    } bitc;
} GH_HDMI_PACKET_TX_CTRL_REAL_S;

typedef union { /* HDMI_PACKET_GENERAL_CTRL */
    U32 all;
    struct {
        U32 set_avmute                  : 1;
        U32                             : 3;
        U32 clr_avmute                  : 1;
        U32                             : 3;
        U32 cd                          : 4;
        U32 pp                          : 4;
        U32 def_phase                   : 1;
        U32                             : 15;
    } bitc;
} GH_HDMI_PACKET_GENERAL_CTRL_REAL_S;

typedef union { /* HDMI_PACKET0 */
    U32 all;
    struct {
        U32 acp_hb0                     : 8;
        U32 acp_hb1                     : 8;
        U32 acp_hb2                     : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET0_REAL_S;

typedef union { /* HDMI_PACKET1 */
    U32 all;
    struct {
        U32 acp_pb0                     : 8;
        U32 acp_pb1                     : 8;
        U32 acp_pb2                     : 8;
        U32 acp_pb3                     : 8;
    } bitc;
} GH_HDMI_PACKET1_REAL_S;

typedef union { /* HDMI_PACKET2 */
    U32 all;
    struct {
        U32 acp_pb4                     : 8;
        U32 acp_pb5                     : 8;
        U32 acp_pb6                     : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET2_REAL_S;

typedef union { /* HDMI_PACKET3 */
    U32 all;
    struct {
        U32 acp_pb7                     : 8;
        U32 acp_pb8                     : 8;
        U32 acp_pb9                     : 8;
        U32 acp_pb10                    : 8;
    } bitc;
} GH_HDMI_PACKET3_REAL_S;

typedef union { /* HDMI_PACKET4 */
    U32 all;
    struct {
        U32 acp_pb11                    : 8;
        U32 acp_pb12                    : 8;
        U32 acp_pb13                    : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET4_REAL_S;

typedef union { /* HDMI_PACKET5 */
    U32 all;
    struct {
        U32 acp_pb14                    : 8;
        U32 acp_pb15                    : 8;
        U32 acp_pb16                    : 8;
        U32 acp_pb17                    : 8;
    } bitc;
} GH_HDMI_PACKET5_REAL_S;

typedef union { /* HDMI_PACKET6 */
    U32 all;
    struct {
        U32 acp_pb18                    : 8;
        U32 acp_pb19                    : 8;
        U32 acp_pb20                    : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET6_REAL_S;

typedef union { /* HDMI_PACKET7 */
    U32 all;
    struct {
        U32 acp_pb21                    : 8;
        U32 acp_pb22                    : 8;
        U32 acp_pb23                    : 8;
        U32 acp_pb24                    : 8;
    } bitc;
} GH_HDMI_PACKET7_REAL_S;

typedef union { /* HDMI_PACKET8 */
    U32 all;
    struct {
        U32 acp_pb25                    : 8;
        U32 acp_pb26                    : 8;
        U32 acp_pb27                    : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET8_REAL_S;

typedef union { /* HDMI_I2S_MODE */
    U32 all;
    struct {
        U32 dai_mode                    : 3;
        U32                             : 29;
    } bitc;
} GH_HDMI_I2S_MODE_REAL_S;

typedef union { /* HDMI_I2S_RX_CTRL */
    U32 all;
    struct {
        U32 rx_ws_inv                   : 1;
        U32 rx_ws_mst                   : 1;
        U32 rx_ord                      : 1;
        U32                             : 29;
    } bitc;
} GH_HDMI_I2S_RX_CTRL_REAL_S;

typedef union { /* HDMI_I2S_WLEN */
    U32 all;
    struct {
        U32 dai_wlen                    : 5;
        U32                             : 27;
    } bitc;
} GH_HDMI_I2S_WLEN_REAL_S;

typedef union { /* HDMI_I2S_WPOS */
    U32 all;
    struct {
        U32 dai_wpos                    : 5;
        U32                             : 27;
    } bitc;
} GH_HDMI_I2S_WPOS_REAL_S;

typedef union { /* HDMI_I2S_SLOT */
    U32 all;
    struct {
        U32 dai_slot                    : 5;
        U32                             : 27;
    } bitc;
} GH_HDMI_I2S_SLOT_REAL_S;

typedef union { /* HDMI_I2S_RX_FIFO_GTH */
    U32 all;
    struct {
        U32 rx_fifo_gth                 : 8;
        U32                             : 24;
    } bitc;
} GH_HDMI_I2S_RX_FIFO_GTH_REAL_S;

typedef union { /* HDMI_I2S_CLOCK */
    U32 all;
    struct {
        U32                             : 5;
        U32 rx_scp                      : 1;
        U32                             : 26;
    } bitc;
} GH_HDMI_I2S_CLOCK_REAL_S;

typedef union { /* HDMI_I2S_INIT */
    U32 all;
    struct {
        U32 dai_reset                   : 1;
        U32 rx_enable                   : 1;
        U32                             : 30;
    } bitc;
} GH_HDMI_I2S_INIT_REAL_S;

typedef union { /* HDMI_I2S_RX_DATA */
    U32 all;
    struct {
        U32 rx_fifo_dout                : 24;
        U32                             : 8;
    } bitc;
} GH_HDMI_I2S_RX_DATA_REAL_S;

typedef union { /* HDMI_I2S_FIFO_CNTR */
    U32 all;
    struct {
        U32 rx_fifo_cntr                : 8;
        U32                             : 24;
    } bitc;
} GH_HDMI_I2S_FIFO_CNTR_REAL_S;

typedef union { /* HDMI_I2S_GATE_OFF */
    U32 all;
    struct {
        U32 gate_off_en                 : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_I2S_GATE_OFF_REAL_S;

typedef union { /* HDMI_PACKET_MISC */
    U32 all;
    struct {
        U32 left_valid_bit              : 1;
        U32 right_valid_bit             : 1;
        U32 spd_send_ctrl               : 1;
        U32 cts_sw_mode                 : 1;
        U32 ncts_priority               : 1;
        U32 i2s_rx_mode                 : 1;
        U32                             : 26;
    } bitc;
} GH_HDMI_PACKET_MISC_REAL_S;

typedef union { /* HDMI_VUNIT_VBLANK */
    U32 all;
    struct {
        U32 vblank_right_offset         : 6;
        U32 vblank_pulse_width          : 6;
        U32 vblank_left_offset          : 6;
        U32                             : 14;
    } bitc;
} GH_HDMI_VUNIT_VBLANK_REAL_S;

typedef union { /* HDMI_VUNIT_HBLANK */
    U32 all;
    struct {
        U32 hblank_right_offset         : 10;
        U32 hblank_pulse_width          : 10;
        U32 hblank_left_offset          : 10;
        U32                             : 2;
    } bitc;
} GH_HDMI_VUNIT_HBLANK_REAL_S;

typedef union { /* HDMI_VUNIT_VACTIVE */
    U32 all;
    struct {
        U32 vunit_vactive               : 11;
        U32                             : 21;
    } bitc;
} GH_HDMI_VUNIT_VACTIVE_REAL_S;

typedef union { /* HDMI_VUNIT_HACTIVE */
    U32 all;
    struct {
        U32 vunit_hactive               : 12;
        U32                             : 20;
    } bitc;
} GH_HDMI_VUNIT_HACTIVE_REAL_S;

typedef union { /* HDMI_VUNIT_CTRL */
    U32 all;
    struct {
        U32 vsync_pol                   : 1;
        U32 hsync_pol                   : 1;
        U32 video_mode                  : 1;
        U32                             : 29;
    } bitc;
} GH_HDMI_VUNIT_CTRL_REAL_S;

typedef union { /* HDMI_VUNIT_VSYNC_DETECT */
    U32 all;
    struct {
        U32 vsync_detect_en             : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_VUNIT_VSYNC_DETECT_REAL_S;

typedef union { /* HDMI_HDMISE_TM */
    U32 all;
    struct {
        U32 i2s_dout_mode               : 1;
        U32 vdata_src_mode              : 1;
        U32 video_pattern_mode          : 1;
        U32 adata_src_mode              : 1;
        U32                             : 4;
        U32 bg_b                        : 8;
        U32 bg_g                        : 8;
        U32 bg_r                        : 8;
    } bitc;
} GH_HDMI_HDMISE_TM_REAL_S;

typedef union { /* HDMI_P2P_AFIFO_LEVEL */
    U32 all;
    struct {
        U32 p2p_afifo_level             : 5;
        U32 p2p_afifo_min_level         : 5;
        U32 p2p_afifo_max_level         : 5;
        U32 p2p_afifo_lb                : 4;
        U32 p2p_afifo_ub                : 4;
        U32                             : 9;
    } bitc;
} GH_HDMI_P2P_AFIFO_LEVEL_REAL_S;

typedef union { /* HDMI_P2P_AFIFO_CTRL */
    U32 all;
    struct {
        U32 p2p_afifo_en                : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_P2P_AFIFO_CTRL_REAL_S;

typedef union { /* HDMI_HDMISE_DBG */
    U32 all;
    struct {
        U32 dbg_p2p_afifo_bypass        : 1;
        U32 dbg_vdata_src_mode          : 1;
        U32                             : 2;
        U32 dbg_ch_b_rev                : 1;
        U32 dbg_ch_g_rev                : 1;
        U32 dbg_ch_r_rev                : 1;
        U32                             : 1;
        U32 dbg_ch_swp                  : 3;
        U32                             : 21;
    } bitc;
} GH_HDMI_HDMISE_DBG_REAL_S;

typedef union { /* HDMI_HDMI_PHY_CTRL */
    U32 all;
    struct {
        U32 rstnd_hdmi                  : 1;
        U32 pib                         : 2;
        U32 pes                         : 2;
        U32 pdb_hdmi                    : 1;
        U32 pd_bg                       : 1;
        U32                             : 25;
    } bitc;
} GH_HDMI_HDMI_PHY_CTRL_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register HDMI_INT_ENABLE (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_INT_ENABLE(U32 data)
{
    GH_HDMI_INT_ENABLE_REAL_S real;
    GH_HDMI_INT_ENABLE_S dummy;
    dummy.all = data ;
    real.bitc.vsync_active_detect_en = dummy.bitc.vsync_active_detect_en;
    real.bitc.hot_plug_detect_en = dummy.bitc.hot_plug_detect_en;
    real.bitc.hot_plug_loss_en = dummy.bitc.hot_plug_loss_en;
    real.bitc.cec_rx_interrupt_en = dummy.bitc.cec_rx_interrupt_en;
    real.bitc.cec_tx_interrupt_fail_en = dummy.bitc.cec_tx_interrupt_fail_en;
    real.bitc.cec_tx_interrupt_ok_en = dummy.bitc.cec_tx_interrupt_ok_en;
    real.bitc.phy_rx_sense_en = dummy.bitc.phy_rx_sense_en;
    real.bitc.i2s_rx_fifo_empty_en = dummy.bitc.i2s_rx_fifo_empty_en;
    real.bitc.i2s_rx_fifo_full_en = dummy.bitc.i2s_rx_fifo_full_en;
    real.bitc.i2s_rx_fifo_over_en = dummy.bitc.i2s_rx_fifo_over_en;
    real.bitc.i2s_rx_gth_valid_en = dummy.bitc.i2s_rx_gth_valid_en;
    real.bitc.i2s_rx_idle_en = dummy.bitc.i2s_rx_idle_en;
    real.bitc.cts_change_en = dummy.bitc.cts_change_en;
    real.bitc.p2p_wfull_en = dummy.bitc.p2p_wfull_en;
    real.bitc.p2p_rempty_en = dummy.bitc.p2p_rempty_en;
    real.bitc.p2p_below_lb_en = dummy.bitc.p2p_below_lb_en;
    real.bitc.p2p_exceed_ub_en = dummy.bitc.p2p_exceed_ub_en;
    real.bitc.hdmise_idle_en = dummy.bitc.hdmise_idle_en;
    real.bitc.phy_rx_sense_remove_en = dummy.bitc.phy_rx_sense_remove_en;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_INT_ENABLE(void)
{
    GH_HDMI_INT_ENABLE_REAL_S real;
    GH_HDMI_INT_ENABLE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    dummy.bitc.vsync_active_detect_en = real.bitc.vsync_active_detect_en;
    dummy.bitc.hot_plug_detect_en = real.bitc.hot_plug_detect_en;
    dummy.bitc.hot_plug_loss_en = real.bitc.hot_plug_loss_en;
    dummy.bitc.cec_rx_interrupt_en = real.bitc.cec_rx_interrupt_en;
    dummy.bitc.cec_tx_interrupt_fail_en = real.bitc.cec_tx_interrupt_fail_en;
    dummy.bitc.cec_tx_interrupt_ok_en = real.bitc.cec_tx_interrupt_ok_en;
    dummy.bitc.phy_rx_sense_en = real.bitc.phy_rx_sense_en;
    dummy.bitc.i2s_rx_fifo_empty_en = real.bitc.i2s_rx_fifo_empty_en;
    dummy.bitc.i2s_rx_fifo_full_en = real.bitc.i2s_rx_fifo_full_en;
    dummy.bitc.i2s_rx_fifo_over_en = real.bitc.i2s_rx_fifo_over_en;
    dummy.bitc.i2s_rx_gth_valid_en = real.bitc.i2s_rx_gth_valid_en;
    dummy.bitc.i2s_rx_idle_en = real.bitc.i2s_rx_idle_en;
    dummy.bitc.cts_change_en = real.bitc.cts_change_en;
    dummy.bitc.p2p_wfull_en = real.bitc.p2p_wfull_en;
    dummy.bitc.p2p_rempty_en = real.bitc.p2p_rempty_en;
    dummy.bitc.p2p_below_lb_en = real.bitc.p2p_below_lb_en;
    dummy.bitc.p2p_exceed_ub_en = real.bitc.p2p_exceed_ub_en;
    dummy.bitc.hdmise_idle_en = real.bitc.hdmise_idle_en;
    dummy.bitc.phy_rx_sense_remove_en = real.bitc.phy_rx_sense_remove_en;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.vsync_active_detect_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_active_detect_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_HOT_PLUG_DETECT_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.hot_plug_detect_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_HOT_PLUG_DETECT_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hot_plug_detect_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_HOT_PLUG_LOSS_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.hot_plug_loss_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_HOT_PLUG_LOSS_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hot_plug_loss_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_CEC_RX_INTERRUPT_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.cec_rx_interrupt_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_CEC_RX_INTERRUPT_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_rx_interrupt_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.cec_tx_interrupt_fail_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_tx_interrupt_fail_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.cec_tx_interrupt_ok_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_tx_interrupt_ok_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.phy_rx_sense_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.phy_rx_sense_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.i2s_rx_fifo_empty_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_fifo_empty_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_FULL_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.i2s_rx_fifo_full_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_FULL_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_fifo_full_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_OVER_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.i2s_rx_fifo_over_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_OVER_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_fifo_over_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_GTH_VALID_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.i2s_rx_gth_valid_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_GTH_VALID_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_gth_valid_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_I2S_RX_IDLE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.i2s_rx_idle_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_I2S_RX_IDLE_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_idle_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_CTS_CHANGE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.cts_change_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_CTS_CHANGE_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cts_change_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_P2P_WFULL_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.p2p_wfull_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_P2P_WFULL_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_wfull_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_P2P_REMPTY_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.p2p_rempty_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_P2P_REMPTY_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_rempty_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_P2P_BELOW_LB_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.p2p_below_lb_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_P2P_BELOW_LB_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_below_lb_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_P2P_EXCEED_UB_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.p2p_exceed_ub_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_P2P_EXCEED_UB_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_exceed_ub_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_HDMISE_IDLE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.hdmise_idle_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_HDMISE_IDLE_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hdmise_idle_en;
}
GH_INLINE void GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN(U8 data)
{
    GH_HDMI_INT_ENABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL;
    d.bitc.phy_rx_sense_remove_en = data;
    *(volatile U32 *)REG_HDMI_INT_ENABLE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN(void)
{
    GH_HDMI_INT_ENABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_ENABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.phy_rx_sense_remove_en;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_INT_STS (read)                                               */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_HDMI_get_INT_STS(void)
{
    GH_HDMI_INT_STS_REAL_S real;
    GH_HDMI_INT_STS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    dummy.bitc.vsync_active_detect = real.bitc.vsync_active_detect;
    dummy.bitc.hot_plug_detect = real.bitc.hot_plug_detect;
    dummy.bitc.hot_plug_loss = real.bitc.hot_plug_loss;
    dummy.bitc.cec_rx_interrupt = real.bitc.cec_rx_interrupt;
    dummy.bitc.cec_tx_interrupt_fail = real.bitc.cec_tx_interrupt_fail;
    dummy.bitc.cec_tx_interrupt_ok = real.bitc.cec_tx_interrupt_ok;
    dummy.bitc.phy_rx_sense = real.bitc.phy_rx_sense;
    dummy.bitc.i2s_rx_fifo_empty = real.bitc.i2s_rx_fifo_empty;
    dummy.bitc.i2s_rx_fifo_full = real.bitc.i2s_rx_fifo_full;
    dummy.bitc.i2s_rx_fifo_over = real.bitc.i2s_rx_fifo_over;
    dummy.bitc.i2s_rx_gth_valid = real.bitc.i2s_rx_gth_valid;
    dummy.bitc.i2s_rx_idle = real.bitc.i2s_rx_idle;
    dummy.bitc.cts_change = real.bitc.cts_change;
    dummy.bitc.p2p_wfull = real.bitc.p2p_wfull;
    dummy.bitc.p2p_rempty = real.bitc.p2p_rempty;
    dummy.bitc.p2p_below_lb = real.bitc.p2p_below_lb;
    dummy.bitc.p2p_exceed_ub = real.bitc.p2p_exceed_ub;
    dummy.bitc.hdmise_idle = real.bitc.hdmise_idle;
    dummy.bitc.phy_rx_sense_remove = real.bitc.phy_rx_sense_remove;
    return dummy.all;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_VSYNC_ACTIVE_DETECT(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_active_detect;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_HOT_PLUG_DETECT(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hot_plug_detect;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_HOT_PLUG_LOSS(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hot_plug_loss;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_CEC_RX_INTERRUPT(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_rx_interrupt;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_FAIL(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_tx_interrupt_fail;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_OK(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_tx_interrupt_ok;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_PHY_RX_SENSE(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.phy_rx_sense;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_EMPTY(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_fifo_empty;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_FULL(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_fifo_full;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_OVER(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_fifo_over;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_GTH_VALID(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_gth_valid;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_I2S_RX_IDLE(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_idle;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_CTS_CHANGE(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cts_change;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_P2P_WFULL(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_wfull;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_P2P_REMPTY(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_rempty;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_P2P_BELOW_LB(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_below_lb;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_P2P_EXCEED_UB(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_exceed_ub;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_HDMISE_IDLE(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hdmise_idle;
}
GH_INLINE U8   GH_HDMI_get_INT_STS_PHY_RX_SENSE_REMOVE(void)
{
    GH_HDMI_INT_STS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_INT_STS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.phy_rx_sense_remove;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_OP_MODE (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_OP_MODE(U32 data)
{
    GH_HDMI_OP_MODE_REAL_S real;
    GH_HDMI_OP_MODE_S dummy;
    dummy.all = data ;
    real.bitc.op_mode = dummy.bitc.op_mode;
    real.bitc.op_en = dummy.bitc.op_en;
    *(volatile U32 *)REG_HDMI_OP_MODE_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_OP_MODE(void)
{
    GH_HDMI_OP_MODE_REAL_S real;
    GH_HDMI_OP_MODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_OP_MODE_REAL);

    dummy.bitc.op_mode = real.bitc.op_mode;
    dummy.bitc.op_en = real.bitc.op_en;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_OP_MODE_OP_MODE(U8 data)
{
    GH_HDMI_OP_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_OP_MODE_REAL;
    d.bitc.op_mode = data;
    *(volatile U32 *)REG_HDMI_OP_MODE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_OP_MODE_OP_MODE(void)
{
    GH_HDMI_OP_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_OP_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.op_mode;
}
GH_INLINE void GH_HDMI_set_OP_MODE_OP_EN(U8 data)
{
    GH_HDMI_OP_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_OP_MODE_REAL;
    d.bitc.op_en = data;
    *(volatile U32 *)REG_HDMI_OP_MODE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_OP_MODE_OP_EN(void)
{
    GH_HDMI_OP_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_OP_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.op_en;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_CLOCK_GATED (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_CLOCK_GATED(U32 data)
{
    GH_HDMI_CLOCK_GATED_REAL_S real;
    GH_HDMI_CLOCK_GATED_S dummy;
    dummy.all = data ;
    real.bitc.hdmise_clock_en = dummy.bitc.hdmise_clock_en;
    real.bitc.cec_clock_en = dummy.bitc.cec_clock_en;
    *(volatile U32 *)REG_HDMI_CLOCK_GATED_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_CLOCK_GATED(void)
{
    GH_HDMI_CLOCK_GATED_REAL_S real;
    GH_HDMI_CLOCK_GATED_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_CLOCK_GATED_REAL);

    dummy.bitc.hdmise_clock_en = real.bitc.hdmise_clock_en;
    dummy.bitc.cec_clock_en = real.bitc.cec_clock_en;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_CLOCK_GATED_HDMISE_CLOCK_EN(U8 data)
{
    GH_HDMI_CLOCK_GATED_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_CLOCK_GATED_REAL;
    d.bitc.hdmise_clock_en = data;
    *(volatile U32 *)REG_HDMI_CLOCK_GATED_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_CLOCK_GATED_HDMISE_CLOCK_EN(void)
{
    GH_HDMI_CLOCK_GATED_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_CLOCK_GATED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hdmise_clock_en;
}
GH_INLINE void GH_HDMI_set_CLOCK_GATED_CEC_CLOCK_EN(U8 data)
{
    GH_HDMI_CLOCK_GATED_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_CLOCK_GATED_REAL;
    d.bitc.cec_clock_en = data;
    *(volatile U32 *)REG_HDMI_CLOCK_GATED_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_CLOCK_GATED_CEC_CLOCK_EN(void)
{
    GH_HDMI_CLOCK_GATED_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_CLOCK_GATED_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cec_clock_en;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMISE_SOFT_RESETN (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_HDMISE_SOFT_RESETN(U32 data)
{
    GH_HDMI_HDMISE_SOFT_RESETN_REAL_S real;
    GH_HDMI_HDMISE_SOFT_RESETN_S dummy;
    dummy.all = data ;
    real.bitc.hdmise_soft_resetn = dummy.bitc.hdmise_soft_resetn;
    *(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_HDMISE_SOFT_RESETN(void)
{
    GH_HDMI_HDMISE_SOFT_RESETN_REAL_S real;
    GH_HDMI_HDMISE_SOFT_RESETN_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN_REAL);

    dummy.bitc.hdmise_soft_resetn = real.bitc.hdmise_soft_resetn;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN(U8 data)
{
    GH_HDMI_HDMISE_SOFT_RESETN_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN_REAL;
    d.bitc.hdmise_soft_resetn = data;
    *(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN(void)
{
    GH_HDMI_HDMISE_SOFT_RESETN_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_SOFT_RESETN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hdmise_soft_resetn;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_STS (read/write)                                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_STS(U32 data)
{
    *(volatile U32 *)REG_HDMI_STS_REAL = data;
}
GH_INLINE U32  GH_HDMI_get_STS(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_STS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_MCLK (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_MCLK(U32 data)
{
    GH_HDMI_AUNIT_MCLK_REAL_S real;
    GH_HDMI_AUNIT_MCLK_S dummy;
    dummy.all = data ;
    real.bitc.mclk_conf = dummy.bitc.mclk_conf;
    *(volatile U32 *)REG_HDMI_AUNIT_MCLK_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_MCLK(void)
{
    GH_HDMI_AUNIT_MCLK_REAL_S real;
    GH_HDMI_AUNIT_MCLK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_AUNIT_MCLK_REAL);

    dummy.bitc.mclk_conf = real.bitc.mclk_conf;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_AUNIT_MCLK_MCLK_CONF(U8 data)
{
    GH_HDMI_AUNIT_MCLK_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_MCLK_REAL;
    d.bitc.mclk_conf = data;
    *(volatile U32 *)REG_HDMI_AUNIT_MCLK_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_MCLK_MCLK_CONF(void)
{
    GH_HDMI_AUNIT_MCLK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_MCLK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mclk_conf;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_NCTS_CTRL (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_NCTS_CTRL(U32 data)
{
    GH_HDMI_AUNIT_NCTS_CTRL_REAL_S real;
    GH_HDMI_AUNIT_NCTS_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.cts_sel = dummy.bitc.cts_sel;
    real.bitc.ncts_en = dummy.bitc.ncts_en;
    *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_NCTS_CTRL(void)
{
    GH_HDMI_AUNIT_NCTS_CTRL_REAL_S real;
    GH_HDMI_AUNIT_NCTS_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL_REAL);

    dummy.bitc.cts_sel = real.bitc.cts_sel;
    dummy.bitc.ncts_en = real.bitc.ncts_en;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_AUNIT_NCTS_CTRL_CTS_SEL(U8 data)
{
    GH_HDMI_AUNIT_NCTS_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL_REAL;
    d.bitc.cts_sel = data;
    *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_NCTS_CTRL_CTS_SEL(void)
{
    GH_HDMI_AUNIT_NCTS_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cts_sel;
}
GH_INLINE void GH_HDMI_set_AUNIT_NCTS_CTRL_NCTS_EN(U8 data)
{
    GH_HDMI_AUNIT_NCTS_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL_REAL;
    d.bitc.ncts_en = data;
    *(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_NCTS_CTRL_NCTS_EN(void)
{
    GH_HDMI_AUNIT_NCTS_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_NCTS_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ncts_en;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_N (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_N(U32 data)
{
    GH_HDMI_AUNIT_N_REAL_S real;
    GH_HDMI_AUNIT_N_S dummy;
    dummy.all = data ;
    real.bitc.aunit_n = dummy.bitc.aunit_n;
    *(volatile U32 *)REG_HDMI_AUNIT_N_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_N(void)
{
    GH_HDMI_AUNIT_N_REAL_S real;
    GH_HDMI_AUNIT_N_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_AUNIT_N_REAL);

    dummy.bitc.aunit_n = real.bitc.aunit_n;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_AUNIT_N_AUNIT_N(U32 data)
{
    GH_HDMI_AUNIT_N_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_N_REAL;
    d.bitc.aunit_n = data;
    *(volatile U32 *)REG_HDMI_AUNIT_N_REAL = d.all;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_N_AUNIT_N(void)
{
    GH_HDMI_AUNIT_N_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_N_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.aunit_n;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CTS (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_CTS(U32 data)
{
    GH_HDMI_AUNIT_CTS_REAL_S real;
    GH_HDMI_AUNIT_CTS_S dummy;
    dummy.all = data ;
    real.bitc.aunit_cts = dummy.bitc.aunit_cts;
    *(volatile U32 *)REG_HDMI_AUNIT_CTS_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CTS(void)
{
    GH_HDMI_AUNIT_CTS_REAL_S real;
    GH_HDMI_AUNIT_CTS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_AUNIT_CTS_REAL);

    dummy.bitc.aunit_cts = real.bitc.aunit_cts;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_AUNIT_CTS_AUNIT_CTS(U32 data)
{
    GH_HDMI_AUNIT_CTS_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_CTS_REAL;
    d.bitc.aunit_cts = data;
    *(volatile U32 *)REG_HDMI_AUNIT_CTS_REAL = d.all;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CTS_AUNIT_CTS(void)
{
    GH_HDMI_AUNIT_CTS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CTS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.aunit_cts;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_SRC (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_SRC(U32 data)
{
    GH_HDMI_AUNIT_SRC_REAL_S real;
    GH_HDMI_AUNIT_SRC_S dummy;
    dummy.all = data ;
    real.bitc.i2s0_en = dummy.bitc.i2s0_en;
    real.bitc.i2s1_en = dummy.bitc.i2s1_en;
    real.bitc.i2s2_en = dummy.bitc.i2s2_en;
    real.bitc.flat_line0 = dummy.bitc.flat_line0;
    real.bitc.flat_line1 = dummy.bitc.flat_line1;
    real.bitc.flat_line2 = dummy.bitc.flat_line2;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_SRC(void)
{
    GH_HDMI_AUNIT_SRC_REAL_S real;
    GH_HDMI_AUNIT_SRC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL);

    dummy.bitc.i2s0_en = real.bitc.i2s0_en;
    dummy.bitc.i2s1_en = real.bitc.i2s1_en;
    dummy.bitc.i2s2_en = real.bitc.i2s2_en;
    dummy.bitc.flat_line0 = real.bitc.flat_line0;
    dummy.bitc.flat_line1 = real.bitc.flat_line1;
    dummy.bitc.flat_line2 = real.bitc.flat_line2;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_I2S0_EN(U8 data)
{
    GH_HDMI_AUNIT_SRC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL;
    d.bitc.i2s0_en = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_I2S0_EN(void)
{
    GH_HDMI_AUNIT_SRC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s0_en;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_I2S1_EN(U8 data)
{
    GH_HDMI_AUNIT_SRC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL;
    d.bitc.i2s1_en = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_I2S1_EN(void)
{
    GH_HDMI_AUNIT_SRC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s1_en;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_I2S2_EN(U8 data)
{
    GH_HDMI_AUNIT_SRC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL;
    d.bitc.i2s2_en = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_I2S2_EN(void)
{
    GH_HDMI_AUNIT_SRC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s2_en;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_FLAT_LINE0(U8 data)
{
    GH_HDMI_AUNIT_SRC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL;
    d.bitc.flat_line0 = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE0(void)
{
    GH_HDMI_AUNIT_SRC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.flat_line0;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_FLAT_LINE1(U8 data)
{
    GH_HDMI_AUNIT_SRC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL;
    d.bitc.flat_line1 = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE1(void)
{
    GH_HDMI_AUNIT_SRC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.flat_line1;
}
GH_INLINE void GH_HDMI_set_AUNIT_SRC_FLAT_LINE2(U8 data)
{
    GH_HDMI_AUNIT_SRC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL;
    d.bitc.flat_line2 = data;
    *(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE2(void)
{
    GH_HDMI_AUNIT_SRC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_SRC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.flat_line2;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS0 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_CS0(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS0_REAL = data;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS0(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS0_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_CS1(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS1_REAL = data;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS1(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_CS2(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS2_REAL = data;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS2(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS2_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS3 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_CS3(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS3_REAL = data;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS3(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS3_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS4 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_CS4(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS4_REAL = data;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS4(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS4_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS5 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_CS5(U32 data)
{
    *(volatile U32 *)REG_HDMI_AUNIT_CS5_REAL = data;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_CS5(void)
{
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_CS5_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_LAYOUT (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_AUNIT_LAYOUT(U32 data)
{
    GH_HDMI_AUNIT_LAYOUT_REAL_S real;
    GH_HDMI_AUNIT_LAYOUT_S dummy;
    dummy.all = data ;
    real.bitc.layout = dummy.bitc.layout;
    *(volatile U32 *)REG_HDMI_AUNIT_LAYOUT_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_AUNIT_LAYOUT(void)
{
    GH_HDMI_AUNIT_LAYOUT_REAL_S real;
    GH_HDMI_AUNIT_LAYOUT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_AUNIT_LAYOUT_REAL);

    dummy.bitc.layout = real.bitc.layout;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_AUNIT_LAYOUT_LAYOUT(U8 data)
{
    GH_HDMI_AUNIT_LAYOUT_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_AUNIT_LAYOUT_REAL;
    d.bitc.layout = data;
    *(volatile U32 *)REG_HDMI_AUNIT_LAYOUT_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_AUNIT_LAYOUT_LAYOUT(void)
{
    GH_HDMI_AUNIT_LAYOUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_AUNIT_LAYOUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.layout;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET_TX_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL(U32 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S real;
    GH_HDMI_PACKET_TX_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.gen_en = dummy.bitc.gen_en;
    real.bitc.gen_rpt = dummy.bitc.gen_rpt;
    real.bitc.acp_en = dummy.bitc.acp_en;
    real.bitc.acp_rpt = dummy.bitc.acp_rpt;
    real.bitc.isrc_en = dummy.bitc.isrc_en;
    real.bitc.isrc_rpt = dummy.bitc.isrc_rpt;
    real.bitc.avi_en = dummy.bitc.avi_en;
    real.bitc.avi_rpt = dummy.bitc.avi_rpt;
    real.bitc.spd_en = dummy.bitc.spd_en;
    real.bitc.spd_rpt = dummy.bitc.spd_rpt;
    real.bitc.aud_en = dummy.bitc.aud_en;
    real.bitc.aud_rpt = dummy.bitc.aud_rpt;
    real.bitc.mpeg_en = dummy.bitc.mpeg_en;
    real.bitc.mpeg_rpt = dummy.bitc.mpeg_rpt;
    real.bitc.gamut_en = dummy.bitc.gamut_en;
    real.bitc.gamut_rpt = dummy.bitc.gamut_rpt;
    real.bitc.buf_switch_en = dummy.bitc.buf_switch_en;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET_TX_CTRL(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S real;
    GH_HDMI_PACKET_TX_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    dummy.bitc.gen_en = real.bitc.gen_en;
    dummy.bitc.gen_rpt = real.bitc.gen_rpt;
    dummy.bitc.acp_en = real.bitc.acp_en;
    dummy.bitc.acp_rpt = real.bitc.acp_rpt;
    dummy.bitc.isrc_en = real.bitc.isrc_en;
    dummy.bitc.isrc_rpt = real.bitc.isrc_rpt;
    dummy.bitc.avi_en = real.bitc.avi_en;
    dummy.bitc.avi_rpt = real.bitc.avi_rpt;
    dummy.bitc.spd_en = real.bitc.spd_en;
    dummy.bitc.spd_rpt = real.bitc.spd_rpt;
    dummy.bitc.aud_en = real.bitc.aud_en;
    dummy.bitc.aud_rpt = real.bitc.aud_rpt;
    dummy.bitc.mpeg_en = real.bitc.mpeg_en;
    dummy.bitc.mpeg_rpt = real.bitc.mpeg_rpt;
    dummy.bitc.gamut_en = real.bitc.gamut_en;
    dummy.bitc.gamut_rpt = real.bitc.gamut_rpt;
    dummy.bitc.buf_switch_en = real.bitc.buf_switch_en;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_GEN_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.gen_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_GEN_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gen_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_GEN_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.gen_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_GEN_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gen_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_ACP_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.acp_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_ACP_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.acp_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_ACP_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.acp_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_ACP_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.acp_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_ISRC_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.isrc_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_ISRC_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.isrc_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_ISRC_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.isrc_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_ISRC_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.isrc_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_AVI_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.avi_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_AVI_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.avi_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_AVI_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.avi_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_AVI_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.avi_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_SPD_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.spd_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_SPD_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.spd_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_SPD_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.spd_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_SPD_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.spd_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_AUD_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.aud_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_AUD_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.aud_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_AUD_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.aud_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_AUD_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.aud_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_MPEG_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.mpeg_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_MPEG_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mpeg_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_MPEG_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.mpeg_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_MPEG_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mpeg_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_GAMUT_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.gamut_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_GAMUT_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gamut_en;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_GAMUT_RPT(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.gamut_rpt = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_GAMUT_RPT(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gamut_rpt;
}
GH_INLINE void GH_HDMI_set_PACKET_TX_CTRL_BUF_SWITCH_EN(U8 data)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL;
    d.bitc.buf_switch_en = data;
    *(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_TX_CTRL_BUF_SWITCH_EN(void)
{
    GH_HDMI_PACKET_TX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_TX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.buf_switch_en;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET_GENERAL_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL(U32 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S real;
    GH_HDMI_PACKET_GENERAL_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.set_avmute = dummy.bitc.set_avmute;
    real.bitc.clr_avmute = dummy.bitc.clr_avmute;
    real.bitc.cd = dummy.bitc.cd;
    real.bitc.pp = dummy.bitc.pp;
    real.bitc.def_phase = dummy.bitc.def_phase;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET_GENERAL_CTRL(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S real;
    GH_HDMI_PACKET_GENERAL_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL);

    dummy.bitc.set_avmute = real.bitc.set_avmute;
    dummy.bitc.clr_avmute = real.bitc.clr_avmute;
    dummy.bitc.cd = real.bitc.cd;
    dummy.bitc.pp = real.bitc.pp;
    dummy.bitc.def_phase = real.bitc.def_phase;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_SET_AVMUTE(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL;
    d.bitc.set_avmute = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_SET_AVMUTE(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.set_avmute;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_CLR_AVMUTE(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL;
    d.bitc.clr_avmute = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_CLR_AVMUTE(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clr_avmute;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_CD(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL;
    d.bitc.cd = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_CD(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cd;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_PP(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL;
    d.bitc.pp = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_PP(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pp;
}
GH_INLINE void GH_HDMI_set_PACKET_GENERAL_CTRL_DEF_PHASE(U8 data)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL;
    d.bitc.def_phase = data;
    *(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_GENERAL_CTRL_DEF_PHASE(void)
{
    GH_HDMI_PACKET_GENERAL_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_GENERAL_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.def_phase;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET0 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET0(U8 index, U32 data)
{
    GH_HDMI_PACKET0_REAL_S real;
    GH_HDMI_PACKET0_S dummy;
    dummy.all = data ;
    real.bitc.acp_hb0 = dummy.bitc.acp_hb0;
    real.bitc.acp_hb1 = dummy.bitc.acp_hb1;
    real.bitc.acp_hb2 = dummy.bitc.acp_hb2;
    *(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET0(U8 index)
{
    GH_HDMI_PACKET0_REAL_S real;
    GH_HDMI_PACKET0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    dummy.bitc.acp_hb0 = real.bitc.acp_hb0;
    dummy.bitc.acp_hb1 = real.bitc.acp_hb1;
    dummy.bitc.acp_hb2 = real.bitc.acp_hb2;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET0_ACP_HB0(U8 index, U8 data)
{
    GH_HDMI_PACKET0_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_hb0 = data;
    *(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET0_ACP_HB0(U8 index)
{
    GH_HDMI_PACKET0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_hb0;
}
GH_INLINE void GH_HDMI_set_PACKET0_ACP_HB1(U8 index, U8 data)
{
    GH_HDMI_PACKET0_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_hb1 = data;
    *(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET0_ACP_HB1(U8 index)
{
    GH_HDMI_PACKET0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_hb1;
}
GH_INLINE void GH_HDMI_set_PACKET0_ACP_HB2(U8 index, U8 data)
{
    GH_HDMI_PACKET0_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_hb2 = data;
    *(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET0_ACP_HB2(U8 index)
{
    GH_HDMI_PACKET0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET0_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_hb2;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET1 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET1(U8 index, U32 data)
{
    GH_HDMI_PACKET1_REAL_S real;
    GH_HDMI_PACKET1_S dummy;
    dummy.all = data ;
    real.bitc.acp_pb0 = dummy.bitc.acp_pb0;
    real.bitc.acp_pb1 = dummy.bitc.acp_pb1;
    real.bitc.acp_pb2 = dummy.bitc.acp_pb2;
    real.bitc.acp_pb3 = dummy.bitc.acp_pb3;
    *(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET1(U8 index)
{
    GH_HDMI_PACKET1_REAL_S real;
    GH_HDMI_PACKET1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    dummy.bitc.acp_pb0 = real.bitc.acp_pb0;
    dummy.bitc.acp_pb1 = real.bitc.acp_pb1;
    dummy.bitc.acp_pb2 = real.bitc.acp_pb2;
    dummy.bitc.acp_pb3 = real.bitc.acp_pb3;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET1_ACP_PB0(U8 index, U8 data)
{
    GH_HDMI_PACKET1_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb0 = data;
    *(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET1_ACP_PB0(U8 index)
{
    GH_HDMI_PACKET1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb0;
}
GH_INLINE void GH_HDMI_set_PACKET1_ACP_PB1(U8 index, U8 data)
{
    GH_HDMI_PACKET1_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb1 = data;
    *(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET1_ACP_PB1(U8 index)
{
    GH_HDMI_PACKET1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb1;
}
GH_INLINE void GH_HDMI_set_PACKET1_ACP_PB2(U8 index, U8 data)
{
    GH_HDMI_PACKET1_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb2 = data;
    *(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET1_ACP_PB2(U8 index)
{
    GH_HDMI_PACKET1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb2;
}
GH_INLINE void GH_HDMI_set_PACKET1_ACP_PB3(U8 index, U8 data)
{
    GH_HDMI_PACKET1_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb3 = data;
    *(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET1_ACP_PB3(U8 index)
{
    GH_HDMI_PACKET1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET1_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb3;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET2 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET2(U8 index, U32 data)
{
    GH_HDMI_PACKET2_REAL_S real;
    GH_HDMI_PACKET2_S dummy;
    dummy.all = data ;
    real.bitc.acp_pb4 = dummy.bitc.acp_pb4;
    real.bitc.acp_pb5 = dummy.bitc.acp_pb5;
    real.bitc.acp_pb6 = dummy.bitc.acp_pb6;
    *(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET2(U8 index)
{
    GH_HDMI_PACKET2_REAL_S real;
    GH_HDMI_PACKET2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    dummy.bitc.acp_pb4 = real.bitc.acp_pb4;
    dummy.bitc.acp_pb5 = real.bitc.acp_pb5;
    dummy.bitc.acp_pb6 = real.bitc.acp_pb6;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET2_ACP_PB4(U8 index, U8 data)
{
    GH_HDMI_PACKET2_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb4 = data;
    *(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET2_ACP_PB4(U8 index)
{
    GH_HDMI_PACKET2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb4;
}
GH_INLINE void GH_HDMI_set_PACKET2_ACP_PB5(U8 index, U8 data)
{
    GH_HDMI_PACKET2_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb5 = data;
    *(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET2_ACP_PB5(U8 index)
{
    GH_HDMI_PACKET2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb5;
}
GH_INLINE void GH_HDMI_set_PACKET2_ACP_PB6(U8 index, U8 data)
{
    GH_HDMI_PACKET2_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb6 = data;
    *(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET2_ACP_PB6(U8 index)
{
    GH_HDMI_PACKET2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET2_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb6;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET3 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET3(U8 index, U32 data)
{
    GH_HDMI_PACKET3_REAL_S real;
    GH_HDMI_PACKET3_S dummy;
    dummy.all = data ;
    real.bitc.acp_pb7 = dummy.bitc.acp_pb7;
    real.bitc.acp_pb8 = dummy.bitc.acp_pb8;
    real.bitc.acp_pb9 = dummy.bitc.acp_pb9;
    real.bitc.acp_pb10 = dummy.bitc.acp_pb10;
    *(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET3(U8 index)
{
    GH_HDMI_PACKET3_REAL_S real;
    GH_HDMI_PACKET3_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    dummy.bitc.acp_pb7 = real.bitc.acp_pb7;
    dummy.bitc.acp_pb8 = real.bitc.acp_pb8;
    dummy.bitc.acp_pb9 = real.bitc.acp_pb9;
    dummy.bitc.acp_pb10 = real.bitc.acp_pb10;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET3_ACP_PB7(U8 index, U8 data)
{
    GH_HDMI_PACKET3_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb7 = data;
    *(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET3_ACP_PB7(U8 index)
{
    GH_HDMI_PACKET3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb7;
}
GH_INLINE void GH_HDMI_set_PACKET3_ACP_PB8(U8 index, U8 data)
{
    GH_HDMI_PACKET3_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb8 = data;
    *(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET3_ACP_PB8(U8 index)
{
    GH_HDMI_PACKET3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb8;
}
GH_INLINE void GH_HDMI_set_PACKET3_ACP_PB9(U8 index, U8 data)
{
    GH_HDMI_PACKET3_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb9 = data;
    *(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET3_ACP_PB9(U8 index)
{
    GH_HDMI_PACKET3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb9;
}
GH_INLINE void GH_HDMI_set_PACKET3_ACP_PB10(U8 index, U8 data)
{
    GH_HDMI_PACKET3_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb10 = data;
    *(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET3_ACP_PB10(U8 index)
{
    GH_HDMI_PACKET3_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET3_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb10;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET4 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET4(U8 index, U32 data)
{
    GH_HDMI_PACKET4_REAL_S real;
    GH_HDMI_PACKET4_S dummy;
    dummy.all = data ;
    real.bitc.acp_pb11 = dummy.bitc.acp_pb11;
    real.bitc.acp_pb12 = dummy.bitc.acp_pb12;
    real.bitc.acp_pb13 = dummy.bitc.acp_pb13;
    *(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET4(U8 index)
{
    GH_HDMI_PACKET4_REAL_S real;
    GH_HDMI_PACKET4_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    dummy.bitc.acp_pb11 = real.bitc.acp_pb11;
    dummy.bitc.acp_pb12 = real.bitc.acp_pb12;
    dummy.bitc.acp_pb13 = real.bitc.acp_pb13;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET4_ACP_PB11(U8 index, U8 data)
{
    GH_HDMI_PACKET4_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb11 = data;
    *(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET4_ACP_PB11(U8 index)
{
    GH_HDMI_PACKET4_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb11;
}
GH_INLINE void GH_HDMI_set_PACKET4_ACP_PB12(U8 index, U8 data)
{
    GH_HDMI_PACKET4_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb12 = data;
    *(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET4_ACP_PB12(U8 index)
{
    GH_HDMI_PACKET4_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb12;
}
GH_INLINE void GH_HDMI_set_PACKET4_ACP_PB13(U8 index, U8 data)
{
    GH_HDMI_PACKET4_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb13 = data;
    *(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET4_ACP_PB13(U8 index)
{
    GH_HDMI_PACKET4_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET4_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb13;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET5 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET5(U8 index, U32 data)
{
    GH_HDMI_PACKET5_REAL_S real;
    GH_HDMI_PACKET5_S dummy;
    dummy.all = data ;
    real.bitc.acp_pb14 = dummy.bitc.acp_pb14;
    real.bitc.acp_pb15 = dummy.bitc.acp_pb15;
    real.bitc.acp_pb16 = dummy.bitc.acp_pb16;
    real.bitc.acp_pb17 = dummy.bitc.acp_pb17;
    *(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET5(U8 index)
{
    GH_HDMI_PACKET5_REAL_S real;
    GH_HDMI_PACKET5_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    dummy.bitc.acp_pb14 = real.bitc.acp_pb14;
    dummy.bitc.acp_pb15 = real.bitc.acp_pb15;
    dummy.bitc.acp_pb16 = real.bitc.acp_pb16;
    dummy.bitc.acp_pb17 = real.bitc.acp_pb17;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET5_ACP_PB14(U8 index, U8 data)
{
    GH_HDMI_PACKET5_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb14 = data;
    *(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET5_ACP_PB14(U8 index)
{
    GH_HDMI_PACKET5_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb14;
}
GH_INLINE void GH_HDMI_set_PACKET5_ACP_PB15(U8 index, U8 data)
{
    GH_HDMI_PACKET5_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb15 = data;
    *(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET5_ACP_PB15(U8 index)
{
    GH_HDMI_PACKET5_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb15;
}
GH_INLINE void GH_HDMI_set_PACKET5_ACP_PB16(U8 index, U8 data)
{
    GH_HDMI_PACKET5_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb16 = data;
    *(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET5_ACP_PB16(U8 index)
{
    GH_HDMI_PACKET5_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb16;
}
GH_INLINE void GH_HDMI_set_PACKET5_ACP_PB17(U8 index, U8 data)
{
    GH_HDMI_PACKET5_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb17 = data;
    *(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET5_ACP_PB17(U8 index)
{
    GH_HDMI_PACKET5_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET5_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb17;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET6 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET6(U8 index, U32 data)
{
    GH_HDMI_PACKET6_REAL_S real;
    GH_HDMI_PACKET6_S dummy;
    dummy.all = data ;
    real.bitc.acp_pb18 = dummy.bitc.acp_pb18;
    real.bitc.acp_pb19 = dummy.bitc.acp_pb19;
    real.bitc.acp_pb20 = dummy.bitc.acp_pb20;
    *(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET6(U8 index)
{
    GH_HDMI_PACKET6_REAL_S real;
    GH_HDMI_PACKET6_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    dummy.bitc.acp_pb18 = real.bitc.acp_pb18;
    dummy.bitc.acp_pb19 = real.bitc.acp_pb19;
    dummy.bitc.acp_pb20 = real.bitc.acp_pb20;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET6_ACP_PB18(U8 index, U8 data)
{
    GH_HDMI_PACKET6_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb18 = data;
    *(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET6_ACP_PB18(U8 index)
{
    GH_HDMI_PACKET6_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb18;
}
GH_INLINE void GH_HDMI_set_PACKET6_ACP_PB19(U8 index, U8 data)
{
    GH_HDMI_PACKET6_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb19 = data;
    *(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET6_ACP_PB19(U8 index)
{
    GH_HDMI_PACKET6_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb19;
}
GH_INLINE void GH_HDMI_set_PACKET6_ACP_PB20(U8 index, U8 data)
{
    GH_HDMI_PACKET6_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb20 = data;
    *(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET6_ACP_PB20(U8 index)
{
    GH_HDMI_PACKET6_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET6_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb20;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET7 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET7(U8 index, U32 data)
{
    GH_HDMI_PACKET7_REAL_S real;
    GH_HDMI_PACKET7_S dummy;
    dummy.all = data ;
    real.bitc.acp_pb21 = dummy.bitc.acp_pb21;
    real.bitc.acp_pb22 = dummy.bitc.acp_pb22;
    real.bitc.acp_pb23 = dummy.bitc.acp_pb23;
    real.bitc.acp_pb24 = dummy.bitc.acp_pb24;
    *(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET7(U8 index)
{
    GH_HDMI_PACKET7_REAL_S real;
    GH_HDMI_PACKET7_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    dummy.bitc.acp_pb21 = real.bitc.acp_pb21;
    dummy.bitc.acp_pb22 = real.bitc.acp_pb22;
    dummy.bitc.acp_pb23 = real.bitc.acp_pb23;
    dummy.bitc.acp_pb24 = real.bitc.acp_pb24;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET7_ACP_PB21(U8 index, U8 data)
{
    GH_HDMI_PACKET7_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb21 = data;
    *(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET7_ACP_PB21(U8 index)
{
    GH_HDMI_PACKET7_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb21;
}
GH_INLINE void GH_HDMI_set_PACKET7_ACP_PB22(U8 index, U8 data)
{
    GH_HDMI_PACKET7_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb22 = data;
    *(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET7_ACP_PB22(U8 index)
{
    GH_HDMI_PACKET7_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb22;
}
GH_INLINE void GH_HDMI_set_PACKET7_ACP_PB23(U8 index, U8 data)
{
    GH_HDMI_PACKET7_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb23 = data;
    *(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET7_ACP_PB23(U8 index)
{
    GH_HDMI_PACKET7_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb23;
}
GH_INLINE void GH_HDMI_set_PACKET7_ACP_PB24(U8 index, U8 data)
{
    GH_HDMI_PACKET7_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb24 = data;
    *(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET7_ACP_PB24(U8 index)
{
    GH_HDMI_PACKET7_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET7_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb24;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET8 (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET8(U8 index, U32 data)
{
    GH_HDMI_PACKET8_REAL_S real;
    GH_HDMI_PACKET8_S dummy;
    dummy.all = data ;
    real.bitc.acp_pb25 = dummy.bitc.acp_pb25;
    real.bitc.acp_pb26 = dummy.bitc.acp_pb26;
    real.bitc.acp_pb27 = dummy.bitc.acp_pb27;
    *(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET8(U8 index)
{
    GH_HDMI_PACKET8_REAL_S real;
    GH_HDMI_PACKET8_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    dummy.bitc.acp_pb25 = real.bitc.acp_pb25;
    dummy.bitc.acp_pb26 = real.bitc.acp_pb26;
    dummy.bitc.acp_pb27 = real.bitc.acp_pb27;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET8_ACP_PB25(U8 index, U8 data)
{
    GH_HDMI_PACKET8_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb25 = data;
    *(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET8_ACP_PB25(U8 index)
{
    GH_HDMI_PACKET8_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb25;
}
GH_INLINE void GH_HDMI_set_PACKET8_ACP_PB26(U8 index, U8 data)
{
    GH_HDMI_PACKET8_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb26 = data;
    *(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET8_ACP_PB26(U8 index)
{
    GH_HDMI_PACKET8_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb26;
}
GH_INLINE void GH_HDMI_set_PACKET8_ACP_PB27(U8 index, U8 data)
{
    GH_HDMI_PACKET8_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24));
    d.bitc.acp_pb27 = data;
    *(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24)) = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET8_ACP_PB27(U8 index)
{
    GH_HDMI_PACKET8_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_PACKET8_REAL + index * FIO_MOFFSET(HDMI,0x24)));

    tmp_value.all = value;
    return tmp_value.bitc.acp_pb27;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_MODE (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_MODE(U32 data)
{
    GH_HDMI_I2S_MODE_REAL_S real;
    GH_HDMI_I2S_MODE_S dummy;
    dummy.all = data ;
    real.bitc.dai_mode = dummy.bitc.dai_mode;
    *(volatile U32 *)REG_HDMI_I2S_MODE_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_MODE(void)
{
    GH_HDMI_I2S_MODE_REAL_S real;
    GH_HDMI_I2S_MODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_MODE_REAL);

    dummy.bitc.dai_mode = real.bitc.dai_mode;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_MODE_dai_mode(U8 data)
{
    GH_HDMI_I2S_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_MODE_REAL;
    d.bitc.dai_mode = data;
    *(volatile U32 *)REG_HDMI_I2S_MODE_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_MODE_dai_mode(void)
{
    GH_HDMI_I2S_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dai_mode;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_RX_CTRL (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_RX_CTRL(U32 data)
{
    GH_HDMI_I2S_RX_CTRL_REAL_S real;
    GH_HDMI_I2S_RX_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.rx_ws_inv = dummy.bitc.rx_ws_inv;
    real.bitc.rx_ws_mst = dummy.bitc.rx_ws_mst;
    real.bitc.rx_ord = dummy.bitc.rx_ord;
    *(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_RX_CTRL(void)
{
    GH_HDMI_I2S_RX_CTRL_REAL_S real;
    GH_HDMI_I2S_RX_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL);

    dummy.bitc.rx_ws_inv = real.bitc.rx_ws_inv;
    dummy.bitc.rx_ws_mst = real.bitc.rx_ws_mst;
    dummy.bitc.rx_ord = real.bitc.rx_ord;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_RX_CTRL_rx_ws_inv(U8 data)
{
    GH_HDMI_I2S_RX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL;
    d.bitc.rx_ws_inv = data;
    *(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_RX_CTRL_rx_ws_inv(void)
{
    GH_HDMI_I2S_RX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_ws_inv;
}
GH_INLINE void GH_HDMI_set_I2S_RX_CTRL_rx_ws_mst(U8 data)
{
    GH_HDMI_I2S_RX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL;
    d.bitc.rx_ws_mst = data;
    *(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_RX_CTRL_rx_ws_mst(void)
{
    GH_HDMI_I2S_RX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_ws_mst;
}
GH_INLINE void GH_HDMI_set_I2S_RX_CTRL_rx_ord(U8 data)
{
    GH_HDMI_I2S_RX_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL;
    d.bitc.rx_ord = data;
    *(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_RX_CTRL_rx_ord(void)
{
    GH_HDMI_I2S_RX_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_ord;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_WLEN (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_WLEN(U32 data)
{
    GH_HDMI_I2S_WLEN_REAL_S real;
    GH_HDMI_I2S_WLEN_S dummy;
    dummy.all = data ;
    real.bitc.dai_wlen = dummy.bitc.dai_wlen;
    *(volatile U32 *)REG_HDMI_I2S_WLEN_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_WLEN(void)
{
    GH_HDMI_I2S_WLEN_REAL_S real;
    GH_HDMI_I2S_WLEN_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_WLEN_REAL);

    dummy.bitc.dai_wlen = real.bitc.dai_wlen;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_WLEN_dai_wlen(U8 data)
{
    GH_HDMI_I2S_WLEN_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_WLEN_REAL;
    d.bitc.dai_wlen = data;
    *(volatile U32 *)REG_HDMI_I2S_WLEN_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_WLEN_dai_wlen(void)
{
    GH_HDMI_I2S_WLEN_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_WLEN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dai_wlen;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_WPOS (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_WPOS(U32 data)
{
    GH_HDMI_I2S_WPOS_REAL_S real;
    GH_HDMI_I2S_WPOS_S dummy;
    dummy.all = data ;
    real.bitc.dai_wpos = dummy.bitc.dai_wpos;
    *(volatile U32 *)REG_HDMI_I2S_WPOS_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_WPOS(void)
{
    GH_HDMI_I2S_WPOS_REAL_S real;
    GH_HDMI_I2S_WPOS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_WPOS_REAL);

    dummy.bitc.dai_wpos = real.bitc.dai_wpos;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_WPOS_dai_wpos(U8 data)
{
    GH_HDMI_I2S_WPOS_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_WPOS_REAL;
    d.bitc.dai_wpos = data;
    *(volatile U32 *)REG_HDMI_I2S_WPOS_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_WPOS_dai_wpos(void)
{
    GH_HDMI_I2S_WPOS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_WPOS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dai_wpos;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_SLOT (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_SLOT(U32 data)
{
    GH_HDMI_I2S_SLOT_REAL_S real;
    GH_HDMI_I2S_SLOT_S dummy;
    dummy.all = data ;
    real.bitc.dai_slot = dummy.bitc.dai_slot;
    *(volatile U32 *)REG_HDMI_I2S_SLOT_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_SLOT(void)
{
    GH_HDMI_I2S_SLOT_REAL_S real;
    GH_HDMI_I2S_SLOT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_SLOT_REAL);

    dummy.bitc.dai_slot = real.bitc.dai_slot;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_SLOT_dai_slot(U8 data)
{
    GH_HDMI_I2S_SLOT_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_SLOT_REAL;
    d.bitc.dai_slot = data;
    *(volatile U32 *)REG_HDMI_I2S_SLOT_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_SLOT_dai_slot(void)
{
    GH_HDMI_I2S_SLOT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_SLOT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dai_slot;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_RX_FIFO_GTH (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_RX_FIFO_GTH(U32 data)
{
    GH_HDMI_I2S_RX_FIFO_GTH_REAL_S real;
    GH_HDMI_I2S_RX_FIFO_GTH_S dummy;
    dummy.all = data ;
    real.bitc.rx_fifo_gth = dummy.bitc.rx_fifo_gth;
    *(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_RX_FIFO_GTH(void)
{
    GH_HDMI_I2S_RX_FIFO_GTH_REAL_S real;
    GH_HDMI_I2S_RX_FIFO_GTH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH_REAL);

    dummy.bitc.rx_fifo_gth = real.bitc.rx_fifo_gth;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_RX_FIFO_GTH_rx_FIFO_gth(U8 data)
{
    GH_HDMI_I2S_RX_FIFO_GTH_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH_REAL;
    d.bitc.rx_fifo_gth = data;
    *(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_RX_FIFO_GTH_rx_FIFO_gth(void)
{
    GH_HDMI_I2S_RX_FIFO_GTH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_RX_FIFO_GTH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_fifo_gth;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_CLOCK (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_CLOCK(U32 data)
{
    GH_HDMI_I2S_CLOCK_REAL_S real;
    GH_HDMI_I2S_CLOCK_S dummy;
    dummy.all = data ;
    real.bitc.rx_scp = dummy.bitc.rx_scp;
    *(volatile U32 *)REG_HDMI_I2S_CLOCK_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_CLOCK(void)
{
    GH_HDMI_I2S_CLOCK_REAL_S real;
    GH_HDMI_I2S_CLOCK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_CLOCK_REAL);

    dummy.bitc.rx_scp = real.bitc.rx_scp;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_CLOCK_rx_scp(U8 data)
{
    GH_HDMI_I2S_CLOCK_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_CLOCK_REAL;
    d.bitc.rx_scp = data;
    *(volatile U32 *)REG_HDMI_I2S_CLOCK_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_CLOCK_rx_scp(void)
{
    GH_HDMI_I2S_CLOCK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_CLOCK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_scp;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_INIT (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_INIT(U32 data)
{
    GH_HDMI_I2S_INIT_REAL_S real;
    GH_HDMI_I2S_INIT_S dummy;
    dummy.all = data ;
    real.bitc.dai_reset = dummy.bitc.dai_reset;
    real.bitc.rx_enable = dummy.bitc.rx_enable;
    *(volatile U32 *)REG_HDMI_I2S_INIT_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_INIT(void)
{
    GH_HDMI_I2S_INIT_REAL_S real;
    GH_HDMI_I2S_INIT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_INIT_REAL);

    dummy.bitc.dai_reset = real.bitc.dai_reset;
    dummy.bitc.rx_enable = real.bitc.rx_enable;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_INIT_dai_reset(U8 data)
{
    GH_HDMI_I2S_INIT_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_INIT_REAL;
    d.bitc.dai_reset = data;
    *(volatile U32 *)REG_HDMI_I2S_INIT_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_INIT_dai_reset(void)
{
    GH_HDMI_I2S_INIT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_INIT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dai_reset;
}
GH_INLINE void GH_HDMI_set_I2S_INIT_rx_enable(U8 data)
{
    GH_HDMI_I2S_INIT_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_INIT_REAL;
    d.bitc.rx_enable = data;
    *(volatile U32 *)REG_HDMI_I2S_INIT_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_INIT_rx_enable(void)
{
    GH_HDMI_I2S_INIT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_INIT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_enable;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_RX_DATA (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_RX_DATA(U8 index, U32 data)
{
    GH_HDMI_I2S_RX_DATA_REAL_S real;
    GH_HDMI_I2S_RX_DATA_S dummy;
    dummy.all = data ;
    real.bitc.rx_fifo_dout = dummy.bitc.rx_fifo_dout;
    *(volatile U32 *)(REG_HDMI_I2S_RX_DATA_REAL + index * FIO_MOFFSET(HDMI,0x4)) = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_RX_DATA(U8 index)
{
    GH_HDMI_I2S_RX_DATA_REAL_S real;
    GH_HDMI_I2S_RX_DATA_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_HDMI_I2S_RX_DATA_REAL + index * FIO_MOFFSET(HDMI,0x4)));

    dummy.bitc.rx_fifo_dout = real.bitc.rx_fifo_dout;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_RX_DATA_rx_FIFO_dout(U8 index, U32 data)
{
    GH_HDMI_I2S_RX_DATA_REAL_S d;
    d.all = *(volatile U32 *)(REG_HDMI_I2S_RX_DATA_REAL + index * FIO_MOFFSET(HDMI,0x4));
    d.bitc.rx_fifo_dout = data;
    *(volatile U32 *)(REG_HDMI_I2S_RX_DATA_REAL + index * FIO_MOFFSET(HDMI,0x4)) = d.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_RX_DATA_rx_FIFO_dout(U8 index)
{
    GH_HDMI_I2S_RX_DATA_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_HDMI_I2S_RX_DATA_REAL + index * FIO_MOFFSET(HDMI,0x4)));

    tmp_value.all = value;
    return tmp_value.bitc.rx_fifo_dout;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_FIFO_CNTR (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_FIFO_CNTR(U32 data)
{
    GH_HDMI_I2S_FIFO_CNTR_REAL_S real;
    GH_HDMI_I2S_FIFO_CNTR_S dummy;
    dummy.all = data ;
    real.bitc.rx_fifo_cntr = dummy.bitc.rx_fifo_cntr;
    *(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_FIFO_CNTR(void)
{
    GH_HDMI_I2S_FIFO_CNTR_REAL_S real;
    GH_HDMI_I2S_FIFO_CNTR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR_REAL);

    dummy.bitc.rx_fifo_cntr = real.bitc.rx_fifo_cntr;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_FIFO_CNTR_rx_FIFO_cntr(U8 data)
{
    GH_HDMI_I2S_FIFO_CNTR_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR_REAL;
    d.bitc.rx_fifo_cntr = data;
    *(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_FIFO_CNTR_rx_FIFO_cntr(void)
{
    GH_HDMI_I2S_FIFO_CNTR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_FIFO_CNTR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rx_fifo_cntr;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_GATE_OFF (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_I2S_GATE_OFF(U32 data)
{
    GH_HDMI_I2S_GATE_OFF_REAL_S real;
    GH_HDMI_I2S_GATE_OFF_S dummy;
    dummy.all = data ;
    real.bitc.gate_off_en = dummy.bitc.gate_off_en;
    *(volatile U32 *)REG_HDMI_I2S_GATE_OFF_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_I2S_GATE_OFF(void)
{
    GH_HDMI_I2S_GATE_OFF_REAL_S real;
    GH_HDMI_I2S_GATE_OFF_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_I2S_GATE_OFF_REAL);

    dummy.bitc.gate_off_en = real.bitc.gate_off_en;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_I2S_GATE_OFF_gate_off_en(U8 data)
{
    GH_HDMI_I2S_GATE_OFF_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_I2S_GATE_OFF_REAL;
    d.bitc.gate_off_en = data;
    *(volatile U32 *)REG_HDMI_I2S_GATE_OFF_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_I2S_GATE_OFF_gate_off_en(void)
{
    GH_HDMI_I2S_GATE_OFF_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_I2S_GATE_OFF_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gate_off_en;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET_MISC (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_PACKET_MISC(U32 data)
{
    GH_HDMI_PACKET_MISC_REAL_S real;
    GH_HDMI_PACKET_MISC_S dummy;
    dummy.all = data ;
    real.bitc.left_valid_bit = dummy.bitc.left_valid_bit;
    real.bitc.right_valid_bit = dummy.bitc.right_valid_bit;
    real.bitc.spd_send_ctrl = dummy.bitc.spd_send_ctrl;
    real.bitc.cts_sw_mode = dummy.bitc.cts_sw_mode;
    real.bitc.ncts_priority = dummy.bitc.ncts_priority;
    real.bitc.i2s_rx_mode = dummy.bitc.i2s_rx_mode;
    *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_PACKET_MISC(void)
{
    GH_HDMI_PACKET_MISC_REAL_S real;
    GH_HDMI_PACKET_MISC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_PACKET_MISC_REAL);

    dummy.bitc.left_valid_bit = real.bitc.left_valid_bit;
    dummy.bitc.right_valid_bit = real.bitc.right_valid_bit;
    dummy.bitc.spd_send_ctrl = real.bitc.spd_send_ctrl;
    dummy.bitc.cts_sw_mode = real.bitc.cts_sw_mode;
    dummy.bitc.ncts_priority = real.bitc.ncts_priority;
    dummy.bitc.i2s_rx_mode = real.bitc.i2s_rx_mode;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_LEFT_VALID_BIT(U8 data)
{
    GH_HDMI_PACKET_MISC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL;
    d.bitc.left_valid_bit = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_LEFT_VALID_BIT(void)
{
    GH_HDMI_PACKET_MISC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.left_valid_bit;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_RIGHT_VALID_BIT(U8 data)
{
    GH_HDMI_PACKET_MISC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL;
    d.bitc.right_valid_bit = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_RIGHT_VALID_BIT(void)
{
    GH_HDMI_PACKET_MISC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.right_valid_bit;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_SPD_SEND_CTRL(U8 data)
{
    GH_HDMI_PACKET_MISC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL;
    d.bitc.spd_send_ctrl = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_SPD_SEND_CTRL(void)
{
    GH_HDMI_PACKET_MISC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.spd_send_ctrl;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_CTS_SW_MODE(U8 data)
{
    GH_HDMI_PACKET_MISC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL;
    d.bitc.cts_sw_mode = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_CTS_SW_MODE(void)
{
    GH_HDMI_PACKET_MISC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cts_sw_mode;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_NCTS_PRIORITY(U8 data)
{
    GH_HDMI_PACKET_MISC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL;
    d.bitc.ncts_priority = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_NCTS_PRIORITY(void)
{
    GH_HDMI_PACKET_MISC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ncts_priority;
}
GH_INLINE void GH_HDMI_set_PACKET_MISC_I2S_RX_MODE(U8 data)
{
    GH_HDMI_PACKET_MISC_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL;
    d.bitc.i2s_rx_mode = data;
    *(volatile U32 *)REG_HDMI_PACKET_MISC_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_PACKET_MISC_I2S_RX_MODE(void)
{
    GH_HDMI_PACKET_MISC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_PACKET_MISC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_rx_mode;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_VBLANK (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_VUNIT_VBLANK(U32 data)
{
    GH_HDMI_VUNIT_VBLANK_REAL_S real;
    GH_HDMI_VUNIT_VBLANK_S dummy;
    dummy.all = data ;
    real.bitc.vblank_right_offset = dummy.bitc.vblank_right_offset;
    real.bitc.vblank_pulse_width = dummy.bitc.vblank_pulse_width;
    real.bitc.vblank_left_offset = dummy.bitc.vblank_left_offset;
    *(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_VUNIT_VBLANK(void)
{
    GH_HDMI_VUNIT_VBLANK_REAL_S real;
    GH_HDMI_VUNIT_VBLANK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL);

    dummy.bitc.vblank_right_offset = real.bitc.vblank_right_offset;
    dummy.bitc.vblank_pulse_width = real.bitc.vblank_pulse_width;
    dummy.bitc.vblank_left_offset = real.bitc.vblank_left_offset;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET(U8 data)
{
    GH_HDMI_VUNIT_VBLANK_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL;
    d.bitc.vblank_right_offset = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET(void)
{
    GH_HDMI_VUNIT_VBLANK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vblank_right_offset;
}
GH_INLINE void GH_HDMI_set_VUNIT_VBLANK_VBLANK_PULSE_WIDTH(U8 data)
{
    GH_HDMI_VUNIT_VBLANK_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL;
    d.bitc.vblank_pulse_width = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_PULSE_WIDTH(void)
{
    GH_HDMI_VUNIT_VBLANK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vblank_pulse_width;
}
GH_INLINE void GH_HDMI_set_VUNIT_VBLANK_VBLANK_LEFT_OFFSET(U8 data)
{
    GH_HDMI_VUNIT_VBLANK_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL;
    d.bitc.vblank_left_offset = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_LEFT_OFFSET(void)
{
    GH_HDMI_VUNIT_VBLANK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VBLANK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vblank_left_offset;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_HBLANK (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_VUNIT_HBLANK(U32 data)
{
    GH_HDMI_VUNIT_HBLANK_REAL_S real;
    GH_HDMI_VUNIT_HBLANK_S dummy;
    dummy.all = data ;
    real.bitc.hblank_right_offset = dummy.bitc.hblank_right_offset;
    real.bitc.hblank_pulse_width = dummy.bitc.hblank_pulse_width;
    real.bitc.hblank_left_offset = dummy.bitc.hblank_left_offset;
    *(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_VUNIT_HBLANK(void)
{
    GH_HDMI_VUNIT_HBLANK_REAL_S real;
    GH_HDMI_VUNIT_HBLANK_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL);

    dummy.bitc.hblank_right_offset = real.bitc.hblank_right_offset;
    dummy.bitc.hblank_pulse_width = real.bitc.hblank_pulse_width;
    dummy.bitc.hblank_left_offset = real.bitc.hblank_left_offset;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET(U16 data)
{
    GH_HDMI_VUNIT_HBLANK_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL;
    d.bitc.hblank_right_offset = data;
    *(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL = d.all;
}
GH_INLINE U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET(void)
{
    GH_HDMI_VUNIT_HBLANK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hblank_right_offset;
}
GH_INLINE void GH_HDMI_set_VUNIT_HBLANK_HBLANK_PULSE_WIDTH(U16 data)
{
    GH_HDMI_VUNIT_HBLANK_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL;
    d.bitc.hblank_pulse_width = data;
    *(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL = d.all;
}
GH_INLINE U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_PULSE_WIDTH(void)
{
    GH_HDMI_VUNIT_HBLANK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hblank_pulse_width;
}
GH_INLINE void GH_HDMI_set_VUNIT_HBLANK_HBLANK_LEFT_OFFSET(U16 data)
{
    GH_HDMI_VUNIT_HBLANK_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL;
    d.bitc.hblank_left_offset = data;
    *(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL = d.all;
}
GH_INLINE U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_LEFT_OFFSET(void)
{
    GH_HDMI_VUNIT_HBLANK_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HBLANK_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hblank_left_offset;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_VACTIVE (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_VUNIT_VACTIVE(U32 data)
{
    GH_HDMI_VUNIT_VACTIVE_REAL_S real;
    GH_HDMI_VUNIT_VACTIVE_S dummy;
    dummy.all = data ;
    real.bitc.vunit_vactive = dummy.bitc.vunit_vactive;
    *(volatile U32 *)REG_HDMI_VUNIT_VACTIVE_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_VUNIT_VACTIVE(void)
{
    GH_HDMI_VUNIT_VACTIVE_REAL_S real;
    GH_HDMI_VUNIT_VACTIVE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_VUNIT_VACTIVE_REAL);

    dummy.bitc.vunit_vactive = real.bitc.vunit_vactive;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_VUNIT_VACTIVE_VUNIT_VACTIVE(U16 data)
{
    GH_HDMI_VUNIT_VACTIVE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VACTIVE_REAL;
    d.bitc.vunit_vactive = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VACTIVE_REAL = d.all;
}
GH_INLINE U16  GH_HDMI_get_VUNIT_VACTIVE_VUNIT_VACTIVE(void)
{
    GH_HDMI_VUNIT_VACTIVE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VACTIVE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vunit_vactive;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_HACTIVE (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_VUNIT_HACTIVE(U32 data)
{
    GH_HDMI_VUNIT_HACTIVE_REAL_S real;
    GH_HDMI_VUNIT_HACTIVE_S dummy;
    dummy.all = data ;
    real.bitc.vunit_hactive = dummy.bitc.vunit_hactive;
    *(volatile U32 *)REG_HDMI_VUNIT_HACTIVE_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_VUNIT_HACTIVE(void)
{
    GH_HDMI_VUNIT_HACTIVE_REAL_S real;
    GH_HDMI_VUNIT_HACTIVE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_VUNIT_HACTIVE_REAL);

    dummy.bitc.vunit_hactive = real.bitc.vunit_hactive;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_VUNIT_HACTIVE_VUNIT_HACTIVE(U16 data)
{
    GH_HDMI_VUNIT_HACTIVE_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_HACTIVE_REAL;
    d.bitc.vunit_hactive = data;
    *(volatile U32 *)REG_HDMI_VUNIT_HACTIVE_REAL = d.all;
}
GH_INLINE U16  GH_HDMI_get_VUNIT_HACTIVE_VUNIT_HACTIVE(void)
{
    GH_HDMI_VUNIT_HACTIVE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_HACTIVE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vunit_hactive;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_CTRL (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_VUNIT_CTRL(U32 data)
{
    GH_HDMI_VUNIT_CTRL_REAL_S real;
    GH_HDMI_VUNIT_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.vsync_pol = dummy.bitc.vsync_pol;
    real.bitc.hsync_pol = dummy.bitc.hsync_pol;
    real.bitc.video_mode = dummy.bitc.video_mode;
    *(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_VUNIT_CTRL(void)
{
    GH_HDMI_VUNIT_CTRL_REAL_S real;
    GH_HDMI_VUNIT_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL);

    dummy.bitc.vsync_pol = real.bitc.vsync_pol;
    dummy.bitc.hsync_pol = real.bitc.hsync_pol;
    dummy.bitc.video_mode = real.bitc.video_mode;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_VUNIT_CTRL_VSYNC_POL(U8 data)
{
    GH_HDMI_VUNIT_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL;
    d.bitc.vsync_pol = data;
    *(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_VUNIT_CTRL_VSYNC_POL(void)
{
    GH_HDMI_VUNIT_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_pol;
}
GH_INLINE void GH_HDMI_set_VUNIT_CTRL_HSYNC_POL(U8 data)
{
    GH_HDMI_VUNIT_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL;
    d.bitc.hsync_pol = data;
    *(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_VUNIT_CTRL_HSYNC_POL(void)
{
    GH_HDMI_VUNIT_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync_pol;
}
GH_INLINE void GH_HDMI_set_VUNIT_CTRL_VIDEO_MODE(U8 data)
{
    GH_HDMI_VUNIT_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL;
    d.bitc.video_mode = data;
    *(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_VUNIT_CTRL_VIDEO_MODE(void)
{
    GH_HDMI_VUNIT_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.video_mode;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_VSYNC_DETECT (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_VUNIT_VSYNC_DETECT(U32 data)
{
    GH_HDMI_VUNIT_VSYNC_DETECT_REAL_S real;
    GH_HDMI_VUNIT_VSYNC_DETECT_S dummy;
    dummy.all = data ;
    real.bitc.vsync_detect_en = dummy.bitc.vsync_detect_en;
    *(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_VUNIT_VSYNC_DETECT(void)
{
    GH_HDMI_VUNIT_VSYNC_DETECT_REAL_S real;
    GH_HDMI_VUNIT_VSYNC_DETECT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT_REAL);

    dummy.bitc.vsync_detect_en = real.bitc.vsync_detect_en;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN(U8 data)
{
    GH_HDMI_VUNIT_VSYNC_DETECT_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT_REAL;
    d.bitc.vsync_detect_en = data;
    *(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN(void)
{
    GH_HDMI_VUNIT_VSYNC_DETECT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_VUNIT_VSYNC_DETECT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_detect_en;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMISE_TM (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_HDMISE_TM(U32 data)
{
    GH_HDMI_HDMISE_TM_REAL_S real;
    GH_HDMI_HDMISE_TM_S dummy;
    dummy.all = data ;
    real.bitc.i2s_dout_mode = dummy.bitc.i2s_dout_mode;
    real.bitc.vdata_src_mode = dummy.bitc.vdata_src_mode;
    real.bitc.video_pattern_mode = dummy.bitc.video_pattern_mode;
    real.bitc.adata_src_mode = dummy.bitc.adata_src_mode;
    real.bitc.bg_b = dummy.bitc.bg_b;
    real.bitc.bg_g = dummy.bitc.bg_g;
    real.bitc.bg_r = dummy.bitc.bg_r;
    *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_HDMISE_TM(void)
{
    GH_HDMI_HDMISE_TM_REAL_S real;
    GH_HDMI_HDMISE_TM_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_HDMISE_TM_REAL);

    dummy.bitc.i2s_dout_mode = real.bitc.i2s_dout_mode;
    dummy.bitc.vdata_src_mode = real.bitc.vdata_src_mode;
    dummy.bitc.video_pattern_mode = real.bitc.video_pattern_mode;
    dummy.bitc.adata_src_mode = real.bitc.adata_src_mode;
    dummy.bitc.bg_b = real.bitc.bg_b;
    dummy.bitc.bg_g = real.bitc.bg_g;
    dummy.bitc.bg_r = real.bitc.bg_r;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_I2S_DOUT_MODE(U8 data)
{
    GH_HDMI_HDMISE_TM_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL;
    d.bitc.i2s_dout_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_I2S_DOUT_MODE(void)
{
    GH_HDMI_HDMISE_TM_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.i2s_dout_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_VDATA_SRC_MODE(U8 data)
{
    GH_HDMI_HDMISE_TM_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL;
    d.bitc.vdata_src_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_VDATA_SRC_MODE(void)
{
    GH_HDMI_HDMISE_TM_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vdata_src_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_VIDEO_PATTERN_MODE(U8 data)
{
    GH_HDMI_HDMISE_TM_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL;
    d.bitc.video_pattern_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_VIDEO_PATTERN_MODE(void)
{
    GH_HDMI_HDMISE_TM_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.video_pattern_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_ADATA_SRC_MODE(U8 data)
{
    GH_HDMI_HDMISE_TM_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL;
    d.bitc.adata_src_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_ADATA_SRC_MODE(void)
{
    GH_HDMI_HDMISE_TM_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.adata_src_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_BG_B(U8 data)
{
    GH_HDMI_HDMISE_TM_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL;
    d.bitc.bg_b = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_BG_B(void)
{
    GH_HDMI_HDMISE_TM_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bg_b;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_BG_G(U8 data)
{
    GH_HDMI_HDMISE_TM_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL;
    d.bitc.bg_g = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_BG_G(void)
{
    GH_HDMI_HDMISE_TM_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bg_g;
}
GH_INLINE void GH_HDMI_set_HDMISE_TM_BG_R(U8 data)
{
    GH_HDMI_HDMISE_TM_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL;
    d.bitc.bg_r = data;
    *(volatile U32 *)REG_HDMI_HDMISE_TM_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_TM_BG_R(void)
{
    GH_HDMI_HDMISE_TM_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_TM_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bg_r;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_P2P_AFIFO_LEVEL (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL(U32 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S real;
    GH_HDMI_P2P_AFIFO_LEVEL_S dummy;
    dummy.all = data ;
    real.bitc.p2p_afifo_level = dummy.bitc.p2p_afifo_level;
    real.bitc.p2p_afifo_min_level = dummy.bitc.p2p_afifo_min_level;
    real.bitc.p2p_afifo_max_level = dummy.bitc.p2p_afifo_max_level;
    real.bitc.p2p_afifo_lb = dummy.bitc.p2p_afifo_lb;
    real.bitc.p2p_afifo_ub = dummy.bitc.p2p_afifo_ub;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_P2P_AFIFO_LEVEL(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S real;
    GH_HDMI_P2P_AFIFO_LEVEL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL);

    dummy.bitc.p2p_afifo_level = real.bitc.p2p_afifo_level;
    dummy.bitc.p2p_afifo_min_level = real.bitc.p2p_afifo_min_level;
    dummy.bitc.p2p_afifo_max_level = real.bitc.p2p_afifo_max_level;
    dummy.bitc.p2p_afifo_lb = real.bitc.p2p_afifo_lb;
    dummy.bitc.p2p_afifo_ub = real.bitc.p2p_afifo_ub;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL;
    d.bitc.p2p_afifo_level = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_afifo_level;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL;
    d.bitc.p2p_afifo_min_level = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_afifo_min_level;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL;
    d.bitc.p2p_afifo_max_level = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_afifo_max_level;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LB(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL;
    d.bitc.p2p_afifo_lb = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LB(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_afifo_lb;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_UB(U8 data)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL;
    d.bitc.p2p_afifo_ub = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_UB(void)
{
    GH_HDMI_P2P_AFIFO_LEVEL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_LEVEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_afifo_ub;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_P2P_AFIFO_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_P2P_AFIFO_CTRL(U32 data)
{
    GH_HDMI_P2P_AFIFO_CTRL_REAL_S real;
    GH_HDMI_P2P_AFIFO_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.p2p_afifo_en = dummy.bitc.p2p_afifo_en;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_P2P_AFIFO_CTRL(void)
{
    GH_HDMI_P2P_AFIFO_CTRL_REAL_S real;
    GH_HDMI_P2P_AFIFO_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL_REAL);

    dummy.bitc.p2p_afifo_en = real.bitc.p2p_afifo_en;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_P2P_AFIFO_CTRL_P2P_AFIFO_EN(U8 data)
{
    GH_HDMI_P2P_AFIFO_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL_REAL;
    d.bitc.p2p_afifo_en = data;
    *(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_P2P_AFIFO_CTRL_P2P_AFIFO_EN(void)
{
    GH_HDMI_P2P_AFIFO_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_P2P_AFIFO_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.p2p_afifo_en;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMISE_DBG (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_HDMISE_DBG(U32 data)
{
    GH_HDMI_HDMISE_DBG_REAL_S real;
    GH_HDMI_HDMISE_DBG_S dummy;
    dummy.all = data ;
    real.bitc.dbg_p2p_afifo_bypass = dummy.bitc.dbg_p2p_afifo_bypass;
    real.bitc.dbg_vdata_src_mode = dummy.bitc.dbg_vdata_src_mode;
    real.bitc.dbg_ch_b_rev = dummy.bitc.dbg_ch_b_rev;
    real.bitc.dbg_ch_g_rev = dummy.bitc.dbg_ch_g_rev;
    real.bitc.dbg_ch_r_rev = dummy.bitc.dbg_ch_r_rev;
    real.bitc.dbg_ch_swp = dummy.bitc.dbg_ch_swp;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_HDMISE_DBG(void)
{
    GH_HDMI_HDMISE_DBG_REAL_S real;
    GH_HDMI_HDMISE_DBG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL);

    dummy.bitc.dbg_p2p_afifo_bypass = real.bitc.dbg_p2p_afifo_bypass;
    dummy.bitc.dbg_vdata_src_mode = real.bitc.dbg_vdata_src_mode;
    dummy.bitc.dbg_ch_b_rev = real.bitc.dbg_ch_b_rev;
    dummy.bitc.dbg_ch_g_rev = real.bitc.dbg_ch_g_rev;
    dummy.bitc.dbg_ch_r_rev = real.bitc.dbg_ch_r_rev;
    dummy.bitc.dbg_ch_swp = real.bitc.dbg_ch_swp;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS(U8 data)
{
    GH_HDMI_HDMISE_DBG_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL;
    d.bitc.dbg_p2p_afifo_bypass = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS(void)
{
    GH_HDMI_HDMISE_DBG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dbg_p2p_afifo_bypass;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_VDATA_SRC_MODE(U8 data)
{
    GH_HDMI_HDMISE_DBG_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL;
    d.bitc.dbg_vdata_src_mode = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_VDATA_SRC_MODE(void)
{
    GH_HDMI_HDMISE_DBG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dbg_vdata_src_mode;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_CH_B_REV(U8 data)
{
    GH_HDMI_HDMISE_DBG_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL;
    d.bitc.dbg_ch_b_rev = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_B_REV(void)
{
    GH_HDMI_HDMISE_DBG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dbg_ch_b_rev;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_CH_G_REV(U8 data)
{
    GH_HDMI_HDMISE_DBG_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL;
    d.bitc.dbg_ch_g_rev = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_G_REV(void)
{
    GH_HDMI_HDMISE_DBG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dbg_ch_g_rev;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_CH_R_REV(U8 data)
{
    GH_HDMI_HDMISE_DBG_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL;
    d.bitc.dbg_ch_r_rev = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_R_REV(void)
{
    GH_HDMI_HDMISE_DBG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dbg_ch_r_rev;
}
GH_INLINE void GH_HDMI_set_HDMISE_DBG_DBG_CH_SWP(U8 data)
{
    GH_HDMI_HDMISE_DBG_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL;
    d.bitc.dbg_ch_swp = data;
    *(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_SWP(void)
{
    GH_HDMI_HDMISE_DBG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMISE_DBG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dbg_ch_swp;
}

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMI_PHY_CTRL (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL(U32 data)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S real;
    GH_HDMI_HDMI_PHY_CTRL_S dummy;
    dummy.all = data ;
    real.bitc.rstnd_hdmi = dummy.bitc.rstnd_hdmi;
    real.bitc.pib = dummy.bitc.pib;
    real.bitc.pes = dummy.bitc.pes;
    real.bitc.pdb_hdmi = dummy.bitc.pdb_hdmi;
    real.bitc.pd_bg = dummy.bitc.pd_bg;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL = real.all;
}
GH_INLINE U32  GH_HDMI_get_HDMI_PHY_CTRL(void)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S real;
    GH_HDMI_HDMI_PHY_CTRL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL);

    dummy.bitc.rstnd_hdmi = real.bitc.rstnd_hdmi;
    dummy.bitc.pib = real.bitc.pib;
    dummy.bitc.pes = real.bitc.pes;
    dummy.bitc.pdb_hdmi = real.bitc.pdb_hdmi;
    dummy.bitc.pd_bg = real.bitc.pd_bg;
    return dummy.all;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_RSTND_HDMI(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL;
    d.bitc.rstnd_hdmi = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_RSTND_HDMI(void)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rstnd_hdmi;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_PIB(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL;
    d.bitc.pib = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_PIB(void)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pib;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_PES(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL;
    d.bitc.pes = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_PES(void)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pes;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_PDB_HDMI(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL;
    d.bitc.pdb_hdmi = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_PDB_HDMI(void)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pdb_hdmi;
}
GH_INLINE void GH_HDMI_set_HDMI_PHY_CTRL_PD_BG(U8 data)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S d;
    d.all = *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL;
    d.bitc.pd_bg = data;
    *(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL = d.all;
}
GH_INLINE U8   GH_HDMI_get_HDMI_PHY_CTRL_PD_BG(void)
{
    GH_HDMI_HDMI_PHY_CTRL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_HDMI_HDMI_PHY_CTRL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pd_bg;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_HDMI_init(void)
{
    int i;

    GH_HDMI_set_INT_ENABLE((U32)0x00000000);
    GH_HDMI_set_OP_MODE((U32)0x00000000);
    GH_HDMI_set_CLOCK_GATED((U32)0x00000005);
    GH_HDMI_set_HDMISE_SOFT_RESETN((U32)0x00000000);
    GH_HDMI_set_STS((U32)0x00000001);
    GH_HDMI_set_AUNIT_MCLK((U32)0x00000001);
    GH_HDMI_set_AUNIT_NCTS_CTRL((U32)0x00000000);
    GH_HDMI_set_AUNIT_N((U32)0x00000000);
    GH_HDMI_set_AUNIT_CTS((U32)0x00000000);
    GH_HDMI_set_AUNIT_SRC((U32)0x00000001);
    GH_HDMI_set_AUNIT_CS0((U32)0x00000000);
    GH_HDMI_set_AUNIT_CS1((U32)0x00000000);
    GH_HDMI_set_AUNIT_CS2((U32)0x00000000);
    GH_HDMI_set_AUNIT_CS3((U32)0x00000000);
    GH_HDMI_set_AUNIT_CS4((U32)0x00000000);
    GH_HDMI_set_AUNIT_CS5((U32)0x00000000);
    GH_HDMI_set_AUNIT_LAYOUT((U32)0x00000000);
    GH_HDMI_set_PACKET_TX_CTRL((U32)0x00000000);
    GH_HDMI_set_PACKET_GENERAL_CTRL((U32)0x00000000);
    GH_HDMI_set_PACKET0(0, (U32)0x00000000);
    for (i=1; i<8; i++)
    {
        GH_HDMI_set_PACKET0(i, (U32)0x00000000);
    }
    GH_HDMI_set_PACKET1(0, (U32)0x00000000);
    for (i=1; i<8; i++)
    {
        GH_HDMI_set_PACKET1(i, (U32)0x00000000);
    }
    GH_HDMI_set_PACKET2(0, (U32)0x00000000);
    for (i=1; i<8; i++)
    {
        GH_HDMI_set_PACKET2(i, (U32)0x00000000);
    }
    GH_HDMI_set_PACKET3(0, (U32)0x00000000);
    for (i=1; i<8; i++)
    {
        GH_HDMI_set_PACKET3(i, (U32)0x00000000);
    }
    GH_HDMI_set_PACKET4(0, (U32)0x00000000);
    for (i=1; i<8; i++)
    {
        GH_HDMI_set_PACKET4(i, (U32)0x00000000);
    }
    GH_HDMI_set_PACKET5(0, (U32)0x00000000);
    for (i=1; i<8; i++)
    {
        GH_HDMI_set_PACKET5(i, (U32)0x00000000);
    }
    GH_HDMI_set_PACKET6(0, (U32)0x00000000);
    for (i=1; i<8; i++)
    {
        GH_HDMI_set_PACKET6(i, (U32)0x00000000);
    }
    GH_HDMI_set_PACKET7(0, (U32)0x00000000);
    for (i=1; i<8; i++)
    {
        GH_HDMI_set_PACKET7(i, (U32)0x00000000);
    }
    GH_HDMI_set_PACKET8(0, (U32)0x00000000);
    for (i=1; i<8; i++)
    {
        GH_HDMI_set_PACKET8(i, (U32)0x00000000);
    }
    GH_HDMI_set_I2S_MODE((U32)0x00000004);
    GH_HDMI_set_I2S_RX_CTRL((U32)0x00000000);
    GH_HDMI_set_I2S_WLEN((U32)0x00000017);
    GH_HDMI_set_I2S_WPOS((U32)0x00000000);
    GH_HDMI_set_I2S_SLOT((U32)0x00000000);
    GH_HDMI_set_I2S_RX_FIFO_GTH((U32)0x00000003);
    GH_HDMI_set_I2S_CLOCK((U32)0x00000000);
    GH_HDMI_set_I2S_INIT((U32)0x00000000);
    GH_HDMI_set_I2S_RX_DATA(0, (U32)0x00000000);
    for (i=1; i<3; i++)
    {
        GH_HDMI_set_I2S_RX_DATA(i, (U32)0x00000000);
    }
    GH_HDMI_set_I2S_FIFO_CNTR((U32)0x00000000);
    GH_HDMI_set_I2S_GATE_OFF((U32)0x00000000);
    GH_HDMI_set_PACKET_MISC((U32)0x00000000);
    GH_HDMI_set_VUNIT_VBLANK((U32)0x00000000);
    GH_HDMI_set_VUNIT_HBLANK((U32)0x00000000);
    GH_HDMI_set_VUNIT_VACTIVE((U32)0x00000000);
    GH_HDMI_set_VUNIT_HACTIVE((U32)0x00000000);
    GH_HDMI_set_VUNIT_CTRL((U32)0x00000000);
    GH_HDMI_set_VUNIT_VSYNC_DETECT((U32)0x00000001);
    GH_HDMI_set_HDMISE_TM((U32)0x00000000);
    GH_HDMI_set_P2P_AFIFO_LEVEL((U32)0x00620000);
    GH_HDMI_set_P2P_AFIFO_CTRL((U32)0x00000000);
    GH_HDMI_set_HDMISE_DBG((U32)0x00000000);
    GH_HDMI_set_HDMI_PHY_CTRL((U32)0x00000021);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

