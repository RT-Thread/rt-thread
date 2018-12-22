/*!
*******************************************************************************
**
** \file      gh_hdmi.h
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
#ifndef _GH_HDMI_H
#define _GH_HDMI_H

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

#define GH_HDMI_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_HDMI_DEBUG_PRINT_FUNCTION printk
#else
#define GH_HDMI_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_HDMI_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_HDMI_INT_ENABLE                                 FIO_ADDRESS(HDMI,0x90013000) /* read/write */
#define REG_HDMI_INT_STS                                    FIO_ADDRESS(HDMI,0x90013004) /* read */
#define REG_HDMI_OP_MODE                                    FIO_ADDRESS(HDMI,0x90013008) /* read/write */
#define REG_HDMI_CLOCK_GATED                                FIO_ADDRESS(HDMI,0x9001300C) /* read/write */
#define REG_HDMI_HDMISE_SOFT_RESETN                         FIO_ADDRESS(HDMI,0x90013010) /* read/write */
#define REG_HDMI_STS                                        FIO_ADDRESS(HDMI,0x90013104) /* read/write */
#define REG_HDMI_AUNIT_MCLK                                 FIO_ADDRESS(HDMI,0x90013100) /* read/write */
#define REG_HDMI_AUNIT_NCTS_CTRL                            FIO_ADDRESS(HDMI,0x90013104) /* read/write */
#define REG_HDMI_AUNIT_N                                    FIO_ADDRESS(HDMI,0x90013108) /* read/write */
#define REG_HDMI_AUNIT_CTS                                  FIO_ADDRESS(HDMI,0x9001310C) /* read/write */
#define REG_HDMI_AUNIT_SRC                                  FIO_ADDRESS(HDMI,0x90013110) /* read/write */
#define REG_HDMI_AUNIT_CS0                                  FIO_ADDRESS(HDMI,0x90013114) /* read/write */
#define REG_HDMI_AUNIT_CS1                                  FIO_ADDRESS(HDMI,0x90013118) /* read/write */
#define REG_HDMI_AUNIT_CS2                                  FIO_ADDRESS(HDMI,0x9001311C) /* read/write */
#define REG_HDMI_AUNIT_CS3                                  FIO_ADDRESS(HDMI,0x90013120) /* read/write */
#define REG_HDMI_AUNIT_CS4                                  FIO_ADDRESS(HDMI,0x90013124) /* read/write */
#define REG_HDMI_AUNIT_CS5                                  FIO_ADDRESS(HDMI,0x90013128) /* read/write */
#define REG_HDMI_AUNIT_LAYOUT                               FIO_ADDRESS(HDMI,0x9001312C) /* read/write */
#define REG_HDMI_PACKET_TX_CTRL                             FIO_ADDRESS(HDMI,0x90013130) /* read/write */
#define REG_HDMI_PACKET_GENERAL_CTRL                        FIO_ADDRESS(HDMI,0x90013134) /* read/write */
#define REG_HDMI_PACKET0                                    FIO_ADDRESS(HDMI,0x90013138) /* read/write */
#define REG_HDMI_PACKET1                                    FIO_ADDRESS(HDMI,0x9001313C) /* read/write */
#define REG_HDMI_PACKET2                                    FIO_ADDRESS(HDMI,0x90013140) /* read/write */
#define REG_HDMI_PACKET3                                    FIO_ADDRESS(HDMI,0x90013144) /* read/write */
#define REG_HDMI_PACKET4                                    FIO_ADDRESS(HDMI,0x90013148) /* read/write */
#define REG_HDMI_PACKET5                                    FIO_ADDRESS(HDMI,0x9001314C) /* read/write */
#define REG_HDMI_PACKET6                                    FIO_ADDRESS(HDMI,0x90013150) /* read/write */
#define REG_HDMI_PACKET7                                    FIO_ADDRESS(HDMI,0x90013154) /* read/write */
#define REG_HDMI_PACKET8                                    FIO_ADDRESS(HDMI,0x90013158) /* read/write */
#define REG_HDMI_I2S_MODE                                   FIO_ADDRESS(HDMI,0x90013258) /* read/write */
#define REG_HDMI_I2S_RX_CTRL                                FIO_ADDRESS(HDMI,0x9001325C) /* read/write */
#define REG_HDMI_I2S_WLEN                                   FIO_ADDRESS(HDMI,0x90013260) /* read/write */
#define REG_HDMI_I2S_WPOS                                   FIO_ADDRESS(HDMI,0x90013264) /* read/write */
#define REG_HDMI_I2S_SLOT                                   FIO_ADDRESS(HDMI,0x90013268) /* read/write */
#define REG_HDMI_I2S_RX_FIFO_GTH                            FIO_ADDRESS(HDMI,0x9001326C) /* read/write */
#define REG_HDMI_I2S_CLOCK                                  FIO_ADDRESS(HDMI,0x90013270) /* read/write */
#define REG_HDMI_I2S_INIT                                   FIO_ADDRESS(HDMI,0x90013274) /* read/write */
#define REG_HDMI_I2S_RX_DATA                                FIO_ADDRESS(HDMI,0x90013278) /* read/write */
#define REG_HDMI_I2S_FIFO_CNTR                              FIO_ADDRESS(HDMI,0x90013284) /* read/write */
#define REG_HDMI_I2S_GATE_OFF                               FIO_ADDRESS(HDMI,0x90013288) /* read/write */
#define REG_HDMI_PACKET_MISC                                FIO_ADDRESS(HDMI,0x9001328C) /* read/write */
#define REG_HDMI_VUNIT_VBLANK                               FIO_ADDRESS(HDMI,0x90013290) /* read/write */
#define REG_HDMI_VUNIT_HBLANK                               FIO_ADDRESS(HDMI,0x90013294) /* read/write */
#define REG_HDMI_VUNIT_VACTIVE                              FIO_ADDRESS(HDMI,0x90013298) /* read/write */
#define REG_HDMI_VUNIT_HACTIVE                              FIO_ADDRESS(HDMI,0x9001329C) /* read/write */
#define REG_HDMI_VUNIT_CTRL                                 FIO_ADDRESS(HDMI,0x900132A0) /* read/write */
#define REG_HDMI_VUNIT_VSYNC_DETECT                         FIO_ADDRESS(HDMI,0x900132A4) /* read/write */
#define REG_HDMI_HDMISE_TM                                  FIO_ADDRESS(HDMI,0x900132A8) /* read/write */
#define REG_HDMI_P2P_AFIFO_LEVEL                            FIO_ADDRESS(HDMI,0x900132AC) /* read/write */
#define REG_HDMI_P2P_AFIFO_CTRL                             FIO_ADDRESS(HDMI,0x900132B0) /* read/write */
#define REG_HDMI_HDMISE_DBG                                 FIO_ADDRESS(HDMI,0x900132B4) /* read/write */
#define REG_HDMI_HDMI_PHY_CTRL                              FIO_ADDRESS(HDMI,0x90013600) /* read/write */

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
} GH_HDMI_INT_ENABLE_S;

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
} GH_HDMI_INT_STS_S;

typedef union { /* HDMI_OP_MODE */
    U32 all;
    struct {
        U32 op_mode                     : 1;
        U32 op_en                       : 1;
        U32                             : 30;
    } bitc;
} GH_HDMI_OP_MODE_S;

typedef union { /* HDMI_CLOCK_GATED */
    U32 all;
    struct {
        U32 hdmise_clock_en             : 1;
        U32                             : 1;
        U32 cec_clock_en                : 1;
        U32                             : 29;
    } bitc;
} GH_HDMI_CLOCK_GATED_S;

typedef union { /* HDMI_HDMISE_SOFT_RESETN */
    U32 all;
    struct {
        U32 hdmise_soft_resetn          : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_HDMISE_SOFT_RESETN_S;

typedef union { /* HDMI_AUNIT_MCLK */
    U32 all;
    struct {
        U32 mclk_conf                   : 3;
        U32                             : 29;
    } bitc;
} GH_HDMI_AUNIT_MCLK_S;

typedef union { /* HDMI_AUNIT_NCTS_CTRL */
    U32 all;
    struct {
        U32 cts_sel                     : 1;
        U32 ncts_en                     : 1;
        U32                             : 30;
    } bitc;
} GH_HDMI_AUNIT_NCTS_CTRL_S;

typedef union { /* HDMI_AUNIT_N */
    U32 all;
    struct {
        U32 aunit_n                     : 20;
        U32                             : 12;
    } bitc;
} GH_HDMI_AUNIT_N_S;

typedef union { /* HDMI_AUNIT_CTS */
    U32 all;
    struct {
        U32 aunit_cts                   : 20;
        U32                             : 12;
    } bitc;
} GH_HDMI_AUNIT_CTS_S;

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
} GH_HDMI_AUNIT_SRC_S;

typedef union { /* HDMI_AUNIT_LAYOUT */
    U32 all;
    struct {
        U32 layout                      : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_AUNIT_LAYOUT_S;

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
} GH_HDMI_PACKET_TX_CTRL_S;

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
} GH_HDMI_PACKET_GENERAL_CTRL_S;

typedef union { /* HDMI_PACKET0 */
    U32 all;
    struct {
        U32 acp_hb0                     : 8;
        U32 acp_hb1                     : 8;
        U32 acp_hb2                     : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET0_S;

typedef union { /* HDMI_PACKET1 */
    U32 all;
    struct {
        U32 acp_pb0                     : 8;
        U32 acp_pb1                     : 8;
        U32 acp_pb2                     : 8;
        U32 acp_pb3                     : 8;
    } bitc;
} GH_HDMI_PACKET1_S;

typedef union { /* HDMI_PACKET2 */
    U32 all;
    struct {
        U32 acp_pb4                     : 8;
        U32 acp_pb5                     : 8;
        U32 acp_pb6                     : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET2_S;

typedef union { /* HDMI_PACKET3 */
    U32 all;
    struct {
        U32 acp_pb7                     : 8;
        U32 acp_pb8                     : 8;
        U32 acp_pb9                     : 8;
        U32 acp_pb10                    : 8;
    } bitc;
} GH_HDMI_PACKET3_S;

typedef union { /* HDMI_PACKET4 */
    U32 all;
    struct {
        U32 acp_pb11                    : 8;
        U32 acp_pb12                    : 8;
        U32 acp_pb13                    : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET4_S;

typedef union { /* HDMI_PACKET5 */
    U32 all;
    struct {
        U32 acp_pb14                    : 8;
        U32 acp_pb15                    : 8;
        U32 acp_pb16                    : 8;
        U32 acp_pb17                    : 8;
    } bitc;
} GH_HDMI_PACKET5_S;

typedef union { /* HDMI_PACKET6 */
    U32 all;
    struct {
        U32 acp_pb18                    : 8;
        U32 acp_pb19                    : 8;
        U32 acp_pb20                    : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET6_S;

typedef union { /* HDMI_PACKET7 */
    U32 all;
    struct {
        U32 acp_pb21                    : 8;
        U32 acp_pb22                    : 8;
        U32 acp_pb23                    : 8;
        U32 acp_pb24                    : 8;
    } bitc;
} GH_HDMI_PACKET7_S;

typedef union { /* HDMI_PACKET8 */
    U32 all;
    struct {
        U32 acp_pb25                    : 8;
        U32 acp_pb26                    : 8;
        U32 acp_pb27                    : 8;
        U32                             : 8;
    } bitc;
} GH_HDMI_PACKET8_S;

typedef union { /* HDMI_I2S_MODE */
    U32 all;
    struct {
        U32 dai_mode                    : 3;
        U32                             : 29;
    } bitc;
} GH_HDMI_I2S_MODE_S;

typedef union { /* HDMI_I2S_RX_CTRL */
    U32 all;
    struct {
        U32 rx_ws_inv                   : 1;
        U32 rx_ws_mst                   : 1;
        U32 rx_ord                      : 1;
        U32                             : 29;
    } bitc;
} GH_HDMI_I2S_RX_CTRL_S;

typedef union { /* HDMI_I2S_WLEN */
    U32 all;
    struct {
        U32 dai_wlen                    : 5;
        U32                             : 27;
    } bitc;
} GH_HDMI_I2S_WLEN_S;

typedef union { /* HDMI_I2S_WPOS */
    U32 all;
    struct {
        U32 dai_wpos                    : 5;
        U32                             : 27;
    } bitc;
} GH_HDMI_I2S_WPOS_S;

typedef union { /* HDMI_I2S_SLOT */
    U32 all;
    struct {
        U32 dai_slot                    : 5;
        U32                             : 27;
    } bitc;
} GH_HDMI_I2S_SLOT_S;

typedef union { /* HDMI_I2S_RX_FIFO_GTH */
    U32 all;
    struct {
        U32 rx_fifo_gth                 : 8;
        U32                             : 24;
    } bitc;
} GH_HDMI_I2S_RX_FIFO_GTH_S;

typedef union { /* HDMI_I2S_CLOCK */
    U32 all;
    struct {
        U32                             : 5;
        U32 rx_scp                      : 1;
        U32                             : 26;
    } bitc;
} GH_HDMI_I2S_CLOCK_S;

typedef union { /* HDMI_I2S_INIT */
    U32 all;
    struct {
        U32 dai_reset                   : 1;
        U32 rx_enable                   : 1;
        U32                             : 30;
    } bitc;
} GH_HDMI_I2S_INIT_S;

typedef union { /* HDMI_I2S_RX_DATA */
    U32 all;
    struct {
        U32 rx_fifo_dout                : 24;
        U32                             : 8;
    } bitc;
} GH_HDMI_I2S_RX_DATA_S;

typedef union { /* HDMI_I2S_FIFO_CNTR */
    U32 all;
    struct {
        U32 rx_fifo_cntr                : 8;
        U32                             : 24;
    } bitc;
} GH_HDMI_I2S_FIFO_CNTR_S;

typedef union { /* HDMI_I2S_GATE_OFF */
    U32 all;
    struct {
        U32 gate_off_en                 : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_I2S_GATE_OFF_S;

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
} GH_HDMI_PACKET_MISC_S;

typedef union { /* HDMI_VUNIT_VBLANK */
    U32 all;
    struct {
        U32 vblank_right_offset         : 6;
        U32 vblank_pulse_width          : 6;
        U32 vblank_left_offset          : 6;
        U32                             : 14;
    } bitc;
} GH_HDMI_VUNIT_VBLANK_S;

typedef union { /* HDMI_VUNIT_HBLANK */
    U32 all;
    struct {
        U32 hblank_right_offset         : 10;
        U32 hblank_pulse_width          : 10;
        U32 hblank_left_offset          : 10;
        U32                             : 2;
    } bitc;
} GH_HDMI_VUNIT_HBLANK_S;

typedef union { /* HDMI_VUNIT_VACTIVE */
    U32 all;
    struct {
        U32 vunit_vactive               : 11;
        U32                             : 21;
    } bitc;
} GH_HDMI_VUNIT_VACTIVE_S;

typedef union { /* HDMI_VUNIT_HACTIVE */
    U32 all;
    struct {
        U32 vunit_hactive               : 12;
        U32                             : 20;
    } bitc;
} GH_HDMI_VUNIT_HACTIVE_S;

typedef union { /* HDMI_VUNIT_CTRL */
    U32 all;
    struct {
        U32 vsync_pol                   : 1;
        U32 hsync_pol                   : 1;
        U32 video_mode                  : 1;
        U32                             : 29;
    } bitc;
} GH_HDMI_VUNIT_CTRL_S;

typedef union { /* HDMI_VUNIT_VSYNC_DETECT */
    U32 all;
    struct {
        U32 vsync_detect_en             : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_VUNIT_VSYNC_DETECT_S;

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
} GH_HDMI_HDMISE_TM_S;

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
} GH_HDMI_P2P_AFIFO_LEVEL_S;

typedef union { /* HDMI_P2P_AFIFO_CTRL */
    U32 all;
    struct {
        U32 p2p_afifo_en                : 1;
        U32                             : 31;
    } bitc;
} GH_HDMI_P2P_AFIFO_CTRL_S;

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
} GH_HDMI_HDMISE_DBG_S;

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
} GH_HDMI_HDMI_PHY_CTRL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register HDMI_INT_ENABLE (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE(U32 data);
/*! \brief Reads the register 'HDMI_INT_ENABLE'. */
U32  GH_HDMI_get_INT_ENABLE(void);
/*! \brief Writes the bit group 'VSYNC_ACTIVE_DETECT_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN(U8 data);
/*! \brief Reads the bit group 'VSYNC_ACTIVE_DETECT_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_VSYNC_ACTIVE_DETECT_EN(void);
/*! \brief Writes the bit group 'HOT_PLUG_DETECT_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_HOT_PLUG_DETECT_EN(U8 data);
/*! \brief Reads the bit group 'HOT_PLUG_DETECT_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_HOT_PLUG_DETECT_EN(void);
/*! \brief Writes the bit group 'HOT_PLUG_LOSS_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_HOT_PLUG_LOSS_EN(U8 data);
/*! \brief Reads the bit group 'HOT_PLUG_LOSS_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_HOT_PLUG_LOSS_EN(void);
/*! \brief Writes the bit group 'CEC_RX_INTERRUPT_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_CEC_RX_INTERRUPT_EN(U8 data);
/*! \brief Reads the bit group 'CEC_RX_INTERRUPT_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_CEC_RX_INTERRUPT_EN(void);
/*! \brief Writes the bit group 'CEC_TX_INTERRUPT_FAIL_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN(U8 data);
/*! \brief Reads the bit group 'CEC_TX_INTERRUPT_FAIL_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_FAIL_EN(void);
/*! \brief Writes the bit group 'CEC_TX_INTERRUPT_OK_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN(U8 data);
/*! \brief Reads the bit group 'CEC_TX_INTERRUPT_OK_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_CEC_TX_INTERRUPT_OK_EN(void);
/*! \brief Writes the bit group 'PHY_RX_SENSE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_EN(U8 data);
/*! \brief Reads the bit group 'PHY_RX_SENSE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_EN(void);
/*! \brief Writes the bit group 'I2S_RX_FIFO_EMPTY_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_FIFO_EMPTY_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_EMPTY_EN(void);
/*! \brief Writes the bit group 'I2S_RX_FIFO_FULL_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_FULL_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_FIFO_FULL_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_FULL_EN(void);
/*! \brief Writes the bit group 'I2S_RX_FIFO_OVER_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_FIFO_OVER_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_FIFO_OVER_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_FIFO_OVER_EN(void);
/*! \brief Writes the bit group 'I2S_RX_GTH_VALID_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_GTH_VALID_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_GTH_VALID_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_GTH_VALID_EN(void);
/*! \brief Writes the bit group 'I2S_RX_IDLE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_I2S_RX_IDLE_EN(U8 data);
/*! \brief Reads the bit group 'I2S_RX_IDLE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_I2S_RX_IDLE_EN(void);
/*! \brief Writes the bit group 'CTS_CHANGE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_CTS_CHANGE_EN(U8 data);
/*! \brief Reads the bit group 'CTS_CHANGE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_CTS_CHANGE_EN(void);
/*! \brief Writes the bit group 'P2P_WFULL_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_P2P_WFULL_EN(U8 data);
/*! \brief Reads the bit group 'P2P_WFULL_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_P2P_WFULL_EN(void);
/*! \brief Writes the bit group 'P2P_REMPTY_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_P2P_REMPTY_EN(U8 data);
/*! \brief Reads the bit group 'P2P_REMPTY_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_P2P_REMPTY_EN(void);
/*! \brief Writes the bit group 'P2P_BELOW_LB_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_P2P_BELOW_LB_EN(U8 data);
/*! \brief Reads the bit group 'P2P_BELOW_LB_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_P2P_BELOW_LB_EN(void);
/*! \brief Writes the bit group 'P2P_EXCEED_UB_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_P2P_EXCEED_UB_EN(U8 data);
/*! \brief Reads the bit group 'P2P_EXCEED_UB_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_P2P_EXCEED_UB_EN(void);
/*! \brief Writes the bit group 'HDMISE_IDLE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_HDMISE_IDLE_EN(U8 data);
/*! \brief Reads the bit group 'HDMISE_IDLE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_HDMISE_IDLE_EN(void);
/*! \brief Writes the bit group 'PHY_RX_SENSE_REMOVE_EN' of register 'HDMI_INT_ENABLE'. */
void GH_HDMI_set_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN(U8 data);
/*! \brief Reads the bit group 'PHY_RX_SENSE_REMOVE_EN' of register 'HDMI_INT_ENABLE'. */
U8   GH_HDMI_get_INT_ENABLE_PHY_RX_SENSE_REMOVE_EN(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_INT_STS (read)                                               */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'HDMI_INT_STS'. */
U32  GH_HDMI_get_INT_STS(void);
/*! \brief Reads the bit group 'VSYNC_ACTIVE_DETECT' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_VSYNC_ACTIVE_DETECT(void);
/*! \brief Reads the bit group 'HOT_PLUG_DETECT' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_HOT_PLUG_DETECT(void);
/*! \brief Reads the bit group 'HOT_PLUG_LOSS' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_HOT_PLUG_LOSS(void);
/*! \brief Reads the bit group 'CEC_RX_INTERRUPT' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_CEC_RX_INTERRUPT(void);
/*! \brief Reads the bit group 'CEC_TX_INTERRUPT_FAIL' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_FAIL(void);
/*! \brief Reads the bit group 'CEC_TX_INTERRUPT_OK' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_CEC_TX_INTERRUPT_OK(void);
/*! \brief Reads the bit group 'PHY_RX_SENSE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_PHY_RX_SENSE(void);
/*! \brief Reads the bit group 'I2S_RX_FIFO_EMPTY' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_EMPTY(void);
/*! \brief Reads the bit group 'I2S_RX_FIFO_FULL' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_FULL(void);
/*! \brief Reads the bit group 'I2S_RX_FIFO_OVER' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_FIFO_OVER(void);
/*! \brief Reads the bit group 'I2S_RX_GTH_VALID' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_GTH_VALID(void);
/*! \brief Reads the bit group 'I2S_RX_IDLE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_I2S_RX_IDLE(void);
/*! \brief Reads the bit group 'CTS_CHANGE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_CTS_CHANGE(void);
/*! \brief Reads the bit group 'P2P_WFULL' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_P2P_WFULL(void);
/*! \brief Reads the bit group 'P2P_REMPTY' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_P2P_REMPTY(void);
/*! \brief Reads the bit group 'P2P_BELOW_LB' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_P2P_BELOW_LB(void);
/*! \brief Reads the bit group 'P2P_EXCEED_UB' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_P2P_EXCEED_UB(void);
/*! \brief Reads the bit group 'HDMISE_IDLE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_HDMISE_IDLE(void);
/*! \brief Reads the bit group 'PHY_RX_SENSE_REMOVE' of register 'HDMI_INT_STS'. */
U8   GH_HDMI_get_INT_STS_PHY_RX_SENSE_REMOVE(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_OP_MODE (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_OP_MODE'. */
void GH_HDMI_set_OP_MODE(U32 data);
/*! \brief Reads the register 'HDMI_OP_MODE'. */
U32  GH_HDMI_get_OP_MODE(void);
/*! \brief Writes the bit group 'OP_MODE' of register 'HDMI_OP_MODE'. */
void GH_HDMI_set_OP_MODE_OP_MODE(U8 data);
/*! \brief Reads the bit group 'OP_MODE' of register 'HDMI_OP_MODE'. */
U8   GH_HDMI_get_OP_MODE_OP_MODE(void);
/*! \brief Writes the bit group 'OP_EN' of register 'HDMI_OP_MODE'. */
void GH_HDMI_set_OP_MODE_OP_EN(U8 data);
/*! \brief Reads the bit group 'OP_EN' of register 'HDMI_OP_MODE'. */
U8   GH_HDMI_get_OP_MODE_OP_EN(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_CLOCK_GATED (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_CLOCK_GATED'. */
void GH_HDMI_set_CLOCK_GATED(U32 data);
/*! \brief Reads the register 'HDMI_CLOCK_GATED'. */
U32  GH_HDMI_get_CLOCK_GATED(void);
/*! \brief Writes the bit group 'HDMISE_CLOCK_EN' of register 'HDMI_CLOCK_GATED'. */
void GH_HDMI_set_CLOCK_GATED_HDMISE_CLOCK_EN(U8 data);
/*! \brief Reads the bit group 'HDMISE_CLOCK_EN' of register 'HDMI_CLOCK_GATED'. */
U8   GH_HDMI_get_CLOCK_GATED_HDMISE_CLOCK_EN(void);
/*! \brief Writes the bit group 'CEC_CLOCK_EN' of register 'HDMI_CLOCK_GATED'. */
void GH_HDMI_set_CLOCK_GATED_CEC_CLOCK_EN(U8 data);
/*! \brief Reads the bit group 'CEC_CLOCK_EN' of register 'HDMI_CLOCK_GATED'. */
U8   GH_HDMI_get_CLOCK_GATED_CEC_CLOCK_EN(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMISE_SOFT_RESETN (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_HDMISE_SOFT_RESETN'. */
void GH_HDMI_set_HDMISE_SOFT_RESETN(U32 data);
/*! \brief Reads the register 'HDMI_HDMISE_SOFT_RESETN'. */
U32  GH_HDMI_get_HDMISE_SOFT_RESETN(void);
/*! \brief Writes the bit group 'HDMISE_SOFT_RESETN' of register 'HDMI_HDMISE_SOFT_RESETN'. */
void GH_HDMI_set_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN(U8 data);
/*! \brief Reads the bit group 'HDMISE_SOFT_RESETN' of register 'HDMI_HDMISE_SOFT_RESETN'. */
U8   GH_HDMI_get_HDMISE_SOFT_RESETN_HDMISE_SOFT_RESETN(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_STS (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_STS'. */
void GH_HDMI_set_STS(U32 data);
/*! \brief Reads the register 'HDMI_STS'. */
U32  GH_HDMI_get_STS(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_MCLK (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_MCLK'. */
void GH_HDMI_set_AUNIT_MCLK(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_MCLK'. */
U32  GH_HDMI_get_AUNIT_MCLK(void);
/*! \brief Writes the bit group 'MCLK_CONF' of register 'HDMI_AUNIT_MCLK'. */
void GH_HDMI_set_AUNIT_MCLK_MCLK_CONF(U8 data);
/*! \brief Reads the bit group 'MCLK_CONF' of register 'HDMI_AUNIT_MCLK'. */
U8   GH_HDMI_get_AUNIT_MCLK_MCLK_CONF(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_NCTS_CTRL (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_NCTS_CTRL'. */
void GH_HDMI_set_AUNIT_NCTS_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_NCTS_CTRL'. */
U32  GH_HDMI_get_AUNIT_NCTS_CTRL(void);
/*! \brief Writes the bit group 'CTS_SEL' of register 'HDMI_AUNIT_NCTS_CTRL'. */
void GH_HDMI_set_AUNIT_NCTS_CTRL_CTS_SEL(U8 data);
/*! \brief Reads the bit group 'CTS_SEL' of register 'HDMI_AUNIT_NCTS_CTRL'. */
U8   GH_HDMI_get_AUNIT_NCTS_CTRL_CTS_SEL(void);
/*! \brief Writes the bit group 'NCTS_EN' of register 'HDMI_AUNIT_NCTS_CTRL'. */
void GH_HDMI_set_AUNIT_NCTS_CTRL_NCTS_EN(U8 data);
/*! \brief Reads the bit group 'NCTS_EN' of register 'HDMI_AUNIT_NCTS_CTRL'. */
U8   GH_HDMI_get_AUNIT_NCTS_CTRL_NCTS_EN(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_N (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_N'. */
void GH_HDMI_set_AUNIT_N(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_N'. */
U32  GH_HDMI_get_AUNIT_N(void);
/*! \brief Writes the bit group 'AUNIT_N' of register 'HDMI_AUNIT_N'. */
void GH_HDMI_set_AUNIT_N_AUNIT_N(U32 data);
/*! \brief Reads the bit group 'AUNIT_N' of register 'HDMI_AUNIT_N'. */
U32  GH_HDMI_get_AUNIT_N_AUNIT_N(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CTS (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_CTS'. */
void GH_HDMI_set_AUNIT_CTS(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CTS'. */
U32  GH_HDMI_get_AUNIT_CTS(void);
/*! \brief Writes the bit group 'AUNIT_CTS' of register 'HDMI_AUNIT_CTS'. */
void GH_HDMI_set_AUNIT_CTS_AUNIT_CTS(U32 data);
/*! \brief Reads the bit group 'AUNIT_CTS' of register 'HDMI_AUNIT_CTS'. */
U32  GH_HDMI_get_AUNIT_CTS_AUNIT_CTS(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_SRC (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_SRC'. */
U32  GH_HDMI_get_AUNIT_SRC(void);
/*! \brief Writes the bit group 'I2S0_EN' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_I2S0_EN(U8 data);
/*! \brief Reads the bit group 'I2S0_EN' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_I2S0_EN(void);
/*! \brief Writes the bit group 'I2S1_EN' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_I2S1_EN(U8 data);
/*! \brief Reads the bit group 'I2S1_EN' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_I2S1_EN(void);
/*! \brief Writes the bit group 'I2S2_EN' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_I2S2_EN(U8 data);
/*! \brief Reads the bit group 'I2S2_EN' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_I2S2_EN(void);
/*! \brief Writes the bit group 'FLAT_LINE0' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_FLAT_LINE0(U8 data);
/*! \brief Reads the bit group 'FLAT_LINE0' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE0(void);
/*! \brief Writes the bit group 'FLAT_LINE1' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_FLAT_LINE1(U8 data);
/*! \brief Reads the bit group 'FLAT_LINE1' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE1(void);
/*! \brief Writes the bit group 'FLAT_LINE2' of register 'HDMI_AUNIT_SRC'. */
void GH_HDMI_set_AUNIT_SRC_FLAT_LINE2(U8 data);
/*! \brief Reads the bit group 'FLAT_LINE2' of register 'HDMI_AUNIT_SRC'. */
U8   GH_HDMI_get_AUNIT_SRC_FLAT_LINE2(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS0 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_CS0'. */
void GH_HDMI_set_AUNIT_CS0(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS0'. */
U32  GH_HDMI_get_AUNIT_CS0(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_CS1'. */
void GH_HDMI_set_AUNIT_CS1(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS1'. */
U32  GH_HDMI_get_AUNIT_CS1(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_CS2'. */
void GH_HDMI_set_AUNIT_CS2(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS2'. */
U32  GH_HDMI_get_AUNIT_CS2(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS3 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_CS3'. */
void GH_HDMI_set_AUNIT_CS3(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS3'. */
U32  GH_HDMI_get_AUNIT_CS3(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS4 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_CS4'. */
void GH_HDMI_set_AUNIT_CS4(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS4'. */
U32  GH_HDMI_get_AUNIT_CS4(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_CS5 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_CS5'. */
void GH_HDMI_set_AUNIT_CS5(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_CS5'. */
U32  GH_HDMI_get_AUNIT_CS5(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_AUNIT_LAYOUT (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_AUNIT_LAYOUT'. */
void GH_HDMI_set_AUNIT_LAYOUT(U32 data);
/*! \brief Reads the register 'HDMI_AUNIT_LAYOUT'. */
U32  GH_HDMI_get_AUNIT_LAYOUT(void);
/*! \brief Writes the bit group 'LAYOUT' of register 'HDMI_AUNIT_LAYOUT'. */
void GH_HDMI_set_AUNIT_LAYOUT_LAYOUT(U8 data);
/*! \brief Reads the bit group 'LAYOUT' of register 'HDMI_AUNIT_LAYOUT'. */
U8   GH_HDMI_get_AUNIT_LAYOUT_LAYOUT(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET_TX_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_PACKET_TX_CTRL'. */
U32  GH_HDMI_get_PACKET_TX_CTRL(void);
/*! \brief Writes the bit group 'GEN_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_GEN_EN(U8 data);
/*! \brief Reads the bit group 'GEN_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_GEN_EN(void);
/*! \brief Writes the bit group 'GEN_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_GEN_RPT(U8 data);
/*! \brief Reads the bit group 'GEN_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_GEN_RPT(void);
/*! \brief Writes the bit group 'ACP_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_ACP_EN(U8 data);
/*! \brief Reads the bit group 'ACP_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_ACP_EN(void);
/*! \brief Writes the bit group 'ACP_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_ACP_RPT(U8 data);
/*! \brief Reads the bit group 'ACP_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_ACP_RPT(void);
/*! \brief Writes the bit group 'ISRC_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_ISRC_EN(U8 data);
/*! \brief Reads the bit group 'ISRC_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_ISRC_EN(void);
/*! \brief Writes the bit group 'ISRC_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_ISRC_RPT(U8 data);
/*! \brief Reads the bit group 'ISRC_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_ISRC_RPT(void);
/*! \brief Writes the bit group 'AVI_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_AVI_EN(U8 data);
/*! \brief Reads the bit group 'AVI_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_AVI_EN(void);
/*! \brief Writes the bit group 'AVI_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_AVI_RPT(U8 data);
/*! \brief Reads the bit group 'AVI_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_AVI_RPT(void);
/*! \brief Writes the bit group 'SPD_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_SPD_EN(U8 data);
/*! \brief Reads the bit group 'SPD_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_SPD_EN(void);
/*! \brief Writes the bit group 'SPD_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_SPD_RPT(U8 data);
/*! \brief Reads the bit group 'SPD_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_SPD_RPT(void);
/*! \brief Writes the bit group 'AUD_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_AUD_EN(U8 data);
/*! \brief Reads the bit group 'AUD_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_AUD_EN(void);
/*! \brief Writes the bit group 'AUD_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_AUD_RPT(U8 data);
/*! \brief Reads the bit group 'AUD_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_AUD_RPT(void);
/*! \brief Writes the bit group 'MPEG_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_MPEG_EN(U8 data);
/*! \brief Reads the bit group 'MPEG_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_MPEG_EN(void);
/*! \brief Writes the bit group 'MPEG_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_MPEG_RPT(U8 data);
/*! \brief Reads the bit group 'MPEG_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_MPEG_RPT(void);
/*! \brief Writes the bit group 'GAMUT_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_GAMUT_EN(U8 data);
/*! \brief Reads the bit group 'GAMUT_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_GAMUT_EN(void);
/*! \brief Writes the bit group 'GAMUT_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_GAMUT_RPT(U8 data);
/*! \brief Reads the bit group 'GAMUT_RPT' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_GAMUT_RPT(void);
/*! \brief Writes the bit group 'BUF_SWITCH_EN' of register 'HDMI_PACKET_TX_CTRL'. */
void GH_HDMI_set_PACKET_TX_CTRL_BUF_SWITCH_EN(U8 data);
/*! \brief Reads the bit group 'BUF_SWITCH_EN' of register 'HDMI_PACKET_TX_CTRL'. */
U8   GH_HDMI_get_PACKET_TX_CTRL_BUF_SWITCH_EN(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET_GENERAL_CTRL (read/write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_PACKET_GENERAL_CTRL'. */
U32  GH_HDMI_get_PACKET_GENERAL_CTRL(void);
/*! \brief Writes the bit group 'SET_AVMUTE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_SET_AVMUTE(U8 data);
/*! \brief Reads the bit group 'SET_AVMUTE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_SET_AVMUTE(void);
/*! \brief Writes the bit group 'CLR_AVMUTE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_CLR_AVMUTE(U8 data);
/*! \brief Reads the bit group 'CLR_AVMUTE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_CLR_AVMUTE(void);
/*! \brief Writes the bit group 'CD' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_CD(U8 data);
/*! \brief Reads the bit group 'CD' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_CD(void);
/*! \brief Writes the bit group 'PP' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_PP(U8 data);
/*! \brief Reads the bit group 'PP' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_PP(void);
/*! \brief Writes the bit group 'DEF_PHASE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
void GH_HDMI_set_PACKET_GENERAL_CTRL_DEF_PHASE(U8 data);
/*! \brief Reads the bit group 'DEF_PHASE' of register 'HDMI_PACKET_GENERAL_CTRL'. */
U8   GH_HDMI_get_PACKET_GENERAL_CTRL_DEF_PHASE(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET0 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET0'. */
void GH_HDMI_set_PACKET0(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET0'. */
U32  GH_HDMI_get_PACKET0(U8 index);
/*! \brief Writes the bit group 'ACP_HB0' of register 'HDMI_PACKET0'. */
void GH_HDMI_set_PACKET0_ACP_HB0(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_HB0' of register 'HDMI_PACKET0'. */
U8   GH_HDMI_get_PACKET0_ACP_HB0(U8 index);
/*! \brief Writes the bit group 'ACP_HB1' of register 'HDMI_PACKET0'. */
void GH_HDMI_set_PACKET0_ACP_HB1(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_HB1' of register 'HDMI_PACKET0'. */
U8   GH_HDMI_get_PACKET0_ACP_HB1(U8 index);
/*! \brief Writes the bit group 'ACP_HB2' of register 'HDMI_PACKET0'. */
void GH_HDMI_set_PACKET0_ACP_HB2(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_HB2' of register 'HDMI_PACKET0'. */
U8   GH_HDMI_get_PACKET0_ACP_HB2(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET1 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET1'. */
U32  GH_HDMI_get_PACKET1(U8 index);
/*! \brief Writes the bit group 'ACP_PB0' of register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1_ACP_PB0(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB0' of register 'HDMI_PACKET1'. */
U8   GH_HDMI_get_PACKET1_ACP_PB0(U8 index);
/*! \brief Writes the bit group 'ACP_PB1' of register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1_ACP_PB1(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB1' of register 'HDMI_PACKET1'. */
U8   GH_HDMI_get_PACKET1_ACP_PB1(U8 index);
/*! \brief Writes the bit group 'ACP_PB2' of register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1_ACP_PB2(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB2' of register 'HDMI_PACKET1'. */
U8   GH_HDMI_get_PACKET1_ACP_PB2(U8 index);
/*! \brief Writes the bit group 'ACP_PB3' of register 'HDMI_PACKET1'. */
void GH_HDMI_set_PACKET1_ACP_PB3(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB3' of register 'HDMI_PACKET1'. */
U8   GH_HDMI_get_PACKET1_ACP_PB3(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET2 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET2'. */
void GH_HDMI_set_PACKET2(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET2'. */
U32  GH_HDMI_get_PACKET2(U8 index);
/*! \brief Writes the bit group 'ACP_PB4' of register 'HDMI_PACKET2'. */
void GH_HDMI_set_PACKET2_ACP_PB4(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB4' of register 'HDMI_PACKET2'. */
U8   GH_HDMI_get_PACKET2_ACP_PB4(U8 index);
/*! \brief Writes the bit group 'ACP_PB5' of register 'HDMI_PACKET2'. */
void GH_HDMI_set_PACKET2_ACP_PB5(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB5' of register 'HDMI_PACKET2'. */
U8   GH_HDMI_get_PACKET2_ACP_PB5(U8 index);
/*! \brief Writes the bit group 'ACP_PB6' of register 'HDMI_PACKET2'. */
void GH_HDMI_set_PACKET2_ACP_PB6(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB6' of register 'HDMI_PACKET2'. */
U8   GH_HDMI_get_PACKET2_ACP_PB6(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET3 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET3'. */
U32  GH_HDMI_get_PACKET3(U8 index);
/*! \brief Writes the bit group 'ACP_PB7' of register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3_ACP_PB7(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB7' of register 'HDMI_PACKET3'. */
U8   GH_HDMI_get_PACKET3_ACP_PB7(U8 index);
/*! \brief Writes the bit group 'ACP_PB8' of register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3_ACP_PB8(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB8' of register 'HDMI_PACKET3'. */
U8   GH_HDMI_get_PACKET3_ACP_PB8(U8 index);
/*! \brief Writes the bit group 'ACP_PB9' of register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3_ACP_PB9(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB9' of register 'HDMI_PACKET3'. */
U8   GH_HDMI_get_PACKET3_ACP_PB9(U8 index);
/*! \brief Writes the bit group 'ACP_PB10' of register 'HDMI_PACKET3'. */
void GH_HDMI_set_PACKET3_ACP_PB10(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB10' of register 'HDMI_PACKET3'. */
U8   GH_HDMI_get_PACKET3_ACP_PB10(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET4 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET4'. */
void GH_HDMI_set_PACKET4(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET4'. */
U32  GH_HDMI_get_PACKET4(U8 index);
/*! \brief Writes the bit group 'ACP_PB11' of register 'HDMI_PACKET4'. */
void GH_HDMI_set_PACKET4_ACP_PB11(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB11' of register 'HDMI_PACKET4'. */
U8   GH_HDMI_get_PACKET4_ACP_PB11(U8 index);
/*! \brief Writes the bit group 'ACP_PB12' of register 'HDMI_PACKET4'. */
void GH_HDMI_set_PACKET4_ACP_PB12(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB12' of register 'HDMI_PACKET4'. */
U8   GH_HDMI_get_PACKET4_ACP_PB12(U8 index);
/*! \brief Writes the bit group 'ACP_PB13' of register 'HDMI_PACKET4'. */
void GH_HDMI_set_PACKET4_ACP_PB13(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB13' of register 'HDMI_PACKET4'. */
U8   GH_HDMI_get_PACKET4_ACP_PB13(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET5 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET5'. */
U32  GH_HDMI_get_PACKET5(U8 index);
/*! \brief Writes the bit group 'ACP_PB14' of register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5_ACP_PB14(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB14' of register 'HDMI_PACKET5'. */
U8   GH_HDMI_get_PACKET5_ACP_PB14(U8 index);
/*! \brief Writes the bit group 'ACP_PB15' of register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5_ACP_PB15(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB15' of register 'HDMI_PACKET5'. */
U8   GH_HDMI_get_PACKET5_ACP_PB15(U8 index);
/*! \brief Writes the bit group 'ACP_PB16' of register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5_ACP_PB16(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB16' of register 'HDMI_PACKET5'. */
U8   GH_HDMI_get_PACKET5_ACP_PB16(U8 index);
/*! \brief Writes the bit group 'ACP_PB17' of register 'HDMI_PACKET5'. */
void GH_HDMI_set_PACKET5_ACP_PB17(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB17' of register 'HDMI_PACKET5'. */
U8   GH_HDMI_get_PACKET5_ACP_PB17(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET6 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET6'. */
void GH_HDMI_set_PACKET6(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET6'. */
U32  GH_HDMI_get_PACKET6(U8 index);
/*! \brief Writes the bit group 'ACP_PB18' of register 'HDMI_PACKET6'. */
void GH_HDMI_set_PACKET6_ACP_PB18(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB18' of register 'HDMI_PACKET6'. */
U8   GH_HDMI_get_PACKET6_ACP_PB18(U8 index);
/*! \brief Writes the bit group 'ACP_PB19' of register 'HDMI_PACKET6'. */
void GH_HDMI_set_PACKET6_ACP_PB19(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB19' of register 'HDMI_PACKET6'. */
U8   GH_HDMI_get_PACKET6_ACP_PB19(U8 index);
/*! \brief Writes the bit group 'ACP_PB20' of register 'HDMI_PACKET6'. */
void GH_HDMI_set_PACKET6_ACP_PB20(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB20' of register 'HDMI_PACKET6'. */
U8   GH_HDMI_get_PACKET6_ACP_PB20(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET7 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET7'. */
U32  GH_HDMI_get_PACKET7(U8 index);
/*! \brief Writes the bit group 'ACP_PB21' of register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7_ACP_PB21(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB21' of register 'HDMI_PACKET7'. */
U8   GH_HDMI_get_PACKET7_ACP_PB21(U8 index);
/*! \brief Writes the bit group 'ACP_PB22' of register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7_ACP_PB22(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB22' of register 'HDMI_PACKET7'. */
U8   GH_HDMI_get_PACKET7_ACP_PB22(U8 index);
/*! \brief Writes the bit group 'ACP_PB23' of register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7_ACP_PB23(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB23' of register 'HDMI_PACKET7'. */
U8   GH_HDMI_get_PACKET7_ACP_PB23(U8 index);
/*! \brief Writes the bit group 'ACP_PB24' of register 'HDMI_PACKET7'. */
void GH_HDMI_set_PACKET7_ACP_PB24(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB24' of register 'HDMI_PACKET7'. */
U8   GH_HDMI_get_PACKET7_ACP_PB24(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET8 (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET8'. */
void GH_HDMI_set_PACKET8(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_PACKET8'. */
U32  GH_HDMI_get_PACKET8(U8 index);
/*! \brief Writes the bit group 'ACP_PB25' of register 'HDMI_PACKET8'. */
void GH_HDMI_set_PACKET8_ACP_PB25(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB25' of register 'HDMI_PACKET8'. */
U8   GH_HDMI_get_PACKET8_ACP_PB25(U8 index);
/*! \brief Writes the bit group 'ACP_PB26' of register 'HDMI_PACKET8'. */
void GH_HDMI_set_PACKET8_ACP_PB26(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB26' of register 'HDMI_PACKET8'. */
U8   GH_HDMI_get_PACKET8_ACP_PB26(U8 index);
/*! \brief Writes the bit group 'ACP_PB27' of register 'HDMI_PACKET8'. */
void GH_HDMI_set_PACKET8_ACP_PB27(U8 index, U8 data);
/*! \brief Reads the bit group 'ACP_PB27' of register 'HDMI_PACKET8'. */
U8   GH_HDMI_get_PACKET8_ACP_PB27(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_MODE (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_MODE'. */
void GH_HDMI_set_I2S_MODE(U32 data);
/*! \brief Reads the register 'HDMI_I2S_MODE'. */
U32  GH_HDMI_get_I2S_MODE(void);
/*! \brief Writes the bit group 'dai_mode' of register 'HDMI_I2S_MODE'. */
void GH_HDMI_set_I2S_MODE_dai_mode(U8 data);
/*! \brief Reads the bit group 'dai_mode' of register 'HDMI_I2S_MODE'. */
U8   GH_HDMI_get_I2S_MODE_dai_mode(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_RX_CTRL (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_RX_CTRL'. */
void GH_HDMI_set_I2S_RX_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_I2S_RX_CTRL'. */
U32  GH_HDMI_get_I2S_RX_CTRL(void);
/*! \brief Writes the bit group 'rx_ws_inv' of register 'HDMI_I2S_RX_CTRL'. */
void GH_HDMI_set_I2S_RX_CTRL_rx_ws_inv(U8 data);
/*! \brief Reads the bit group 'rx_ws_inv' of register 'HDMI_I2S_RX_CTRL'. */
U8   GH_HDMI_get_I2S_RX_CTRL_rx_ws_inv(void);
/*! \brief Writes the bit group 'rx_ws_mst' of register 'HDMI_I2S_RX_CTRL'. */
void GH_HDMI_set_I2S_RX_CTRL_rx_ws_mst(U8 data);
/*! \brief Reads the bit group 'rx_ws_mst' of register 'HDMI_I2S_RX_CTRL'. */
U8   GH_HDMI_get_I2S_RX_CTRL_rx_ws_mst(void);
/*! \brief Writes the bit group 'rx_ord' of register 'HDMI_I2S_RX_CTRL'. */
void GH_HDMI_set_I2S_RX_CTRL_rx_ord(U8 data);
/*! \brief Reads the bit group 'rx_ord' of register 'HDMI_I2S_RX_CTRL'. */
U8   GH_HDMI_get_I2S_RX_CTRL_rx_ord(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_WLEN (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_WLEN'. */
void GH_HDMI_set_I2S_WLEN(U32 data);
/*! \brief Reads the register 'HDMI_I2S_WLEN'. */
U32  GH_HDMI_get_I2S_WLEN(void);
/*! \brief Writes the bit group 'dai_wlen' of register 'HDMI_I2S_WLEN'. */
void GH_HDMI_set_I2S_WLEN_dai_wlen(U8 data);
/*! \brief Reads the bit group 'dai_wlen' of register 'HDMI_I2S_WLEN'. */
U8   GH_HDMI_get_I2S_WLEN_dai_wlen(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_WPOS (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_WPOS'. */
void GH_HDMI_set_I2S_WPOS(U32 data);
/*! \brief Reads the register 'HDMI_I2S_WPOS'. */
U32  GH_HDMI_get_I2S_WPOS(void);
/*! \brief Writes the bit group 'dai_wpos' of register 'HDMI_I2S_WPOS'. */
void GH_HDMI_set_I2S_WPOS_dai_wpos(U8 data);
/*! \brief Reads the bit group 'dai_wpos' of register 'HDMI_I2S_WPOS'. */
U8   GH_HDMI_get_I2S_WPOS_dai_wpos(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_SLOT (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_SLOT'. */
void GH_HDMI_set_I2S_SLOT(U32 data);
/*! \brief Reads the register 'HDMI_I2S_SLOT'. */
U32  GH_HDMI_get_I2S_SLOT(void);
/*! \brief Writes the bit group 'dai_slot' of register 'HDMI_I2S_SLOT'. */
void GH_HDMI_set_I2S_SLOT_dai_slot(U8 data);
/*! \brief Reads the bit group 'dai_slot' of register 'HDMI_I2S_SLOT'. */
U8   GH_HDMI_get_I2S_SLOT_dai_slot(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_RX_FIFO_GTH (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_RX_FIFO_GTH'. */
void GH_HDMI_set_I2S_RX_FIFO_GTH(U32 data);
/*! \brief Reads the register 'HDMI_I2S_RX_FIFO_GTH'. */
U32  GH_HDMI_get_I2S_RX_FIFO_GTH(void);
/*! \brief Writes the bit group 'rx_FIFO_gth' of register 'HDMI_I2S_RX_FIFO_GTH'. */
void GH_HDMI_set_I2S_RX_FIFO_GTH_rx_FIFO_gth(U8 data);
/*! \brief Reads the bit group 'rx_FIFO_gth' of register 'HDMI_I2S_RX_FIFO_GTH'. */
U8   GH_HDMI_get_I2S_RX_FIFO_GTH_rx_FIFO_gth(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_CLOCK (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_CLOCK'. */
void GH_HDMI_set_I2S_CLOCK(U32 data);
/*! \brief Reads the register 'HDMI_I2S_CLOCK'. */
U32  GH_HDMI_get_I2S_CLOCK(void);
/*! \brief Writes the bit group 'rx_scp' of register 'HDMI_I2S_CLOCK'. */
void GH_HDMI_set_I2S_CLOCK_rx_scp(U8 data);
/*! \brief Reads the bit group 'rx_scp' of register 'HDMI_I2S_CLOCK'. */
U8   GH_HDMI_get_I2S_CLOCK_rx_scp(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_INIT (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_INIT'. */
void GH_HDMI_set_I2S_INIT(U32 data);
/*! \brief Reads the register 'HDMI_I2S_INIT'. */
U32  GH_HDMI_get_I2S_INIT(void);
/*! \brief Writes the bit group 'dai_reset' of register 'HDMI_I2S_INIT'. */
void GH_HDMI_set_I2S_INIT_dai_reset(U8 data);
/*! \brief Reads the bit group 'dai_reset' of register 'HDMI_I2S_INIT'. */
U8   GH_HDMI_get_I2S_INIT_dai_reset(void);
/*! \brief Writes the bit group 'rx_enable' of register 'HDMI_I2S_INIT'. */
void GH_HDMI_set_I2S_INIT_rx_enable(U8 data);
/*! \brief Reads the bit group 'rx_enable' of register 'HDMI_I2S_INIT'. */
U8   GH_HDMI_get_I2S_INIT_rx_enable(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_RX_DATA (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_RX_DATA'. */
void GH_HDMI_set_I2S_RX_DATA(U8 index, U32 data);
/*! \brief Reads the register 'HDMI_I2S_RX_DATA'. */
U32  GH_HDMI_get_I2S_RX_DATA(U8 index);
/*! \brief Writes the bit group 'rx_FIFO_dout' of register 'HDMI_I2S_RX_DATA'. */
void GH_HDMI_set_I2S_RX_DATA_rx_FIFO_dout(U8 index, U32 data);
/*! \brief Reads the bit group 'rx_FIFO_dout' of register 'HDMI_I2S_RX_DATA'. */
U32  GH_HDMI_get_I2S_RX_DATA_rx_FIFO_dout(U8 index);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_FIFO_CNTR (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_FIFO_CNTR'. */
void GH_HDMI_set_I2S_FIFO_CNTR(U32 data);
/*! \brief Reads the register 'HDMI_I2S_FIFO_CNTR'. */
U32  GH_HDMI_get_I2S_FIFO_CNTR(void);
/*! \brief Writes the bit group 'rx_FIFO_cntr' of register 'HDMI_I2S_FIFO_CNTR'. */
void GH_HDMI_set_I2S_FIFO_CNTR_rx_FIFO_cntr(U8 data);
/*! \brief Reads the bit group 'rx_FIFO_cntr' of register 'HDMI_I2S_FIFO_CNTR'. */
U8   GH_HDMI_get_I2S_FIFO_CNTR_rx_FIFO_cntr(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_I2S_GATE_OFF (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_I2S_GATE_OFF'. */
void GH_HDMI_set_I2S_GATE_OFF(U32 data);
/*! \brief Reads the register 'HDMI_I2S_GATE_OFF'. */
U32  GH_HDMI_get_I2S_GATE_OFF(void);
/*! \brief Writes the bit group 'gate_off_en' of register 'HDMI_I2S_GATE_OFF'. */
void GH_HDMI_set_I2S_GATE_OFF_gate_off_en(U8 data);
/*! \brief Reads the bit group 'gate_off_en' of register 'HDMI_I2S_GATE_OFF'. */
U8   GH_HDMI_get_I2S_GATE_OFF_gate_off_en(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_PACKET_MISC (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC(U32 data);
/*! \brief Reads the register 'HDMI_PACKET_MISC'. */
U32  GH_HDMI_get_PACKET_MISC(void);
/*! \brief Writes the bit group 'LEFT_VALID_BIT' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_LEFT_VALID_BIT(U8 data);
/*! \brief Reads the bit group 'LEFT_VALID_BIT' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_LEFT_VALID_BIT(void);
/*! \brief Writes the bit group 'RIGHT_VALID_BIT' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_RIGHT_VALID_BIT(U8 data);
/*! \brief Reads the bit group 'RIGHT_VALID_BIT' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_RIGHT_VALID_BIT(void);
/*! \brief Writes the bit group 'SPD_SEND_CTRL' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_SPD_SEND_CTRL(U8 data);
/*! \brief Reads the bit group 'SPD_SEND_CTRL' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_SPD_SEND_CTRL(void);
/*! \brief Writes the bit group 'CTS_SW_MODE' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_CTS_SW_MODE(U8 data);
/*! \brief Reads the bit group 'CTS_SW_MODE' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_CTS_SW_MODE(void);
/*! \brief Writes the bit group 'NCTS_PRIORITY' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_NCTS_PRIORITY(U8 data);
/*! \brief Reads the bit group 'NCTS_PRIORITY' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_NCTS_PRIORITY(void);
/*! \brief Writes the bit group 'I2S_RX_MODE' of register 'HDMI_PACKET_MISC'. */
void GH_HDMI_set_PACKET_MISC_I2S_RX_MODE(U8 data);
/*! \brief Reads the bit group 'I2S_RX_MODE' of register 'HDMI_PACKET_MISC'. */
U8   GH_HDMI_get_PACKET_MISC_I2S_RX_MODE(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_VBLANK (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_VUNIT_VBLANK'. */
void GH_HDMI_set_VUNIT_VBLANK(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_VBLANK'. */
U32  GH_HDMI_get_VUNIT_VBLANK(void);
/*! \brief Writes the bit group 'VBLANK_RIGHT_OFFSET' of register 'HDMI_VUNIT_VBLANK'. */
void GH_HDMI_set_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET(U8 data);
/*! \brief Reads the bit group 'VBLANK_RIGHT_OFFSET' of register 'HDMI_VUNIT_VBLANK'. */
U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_RIGHT_OFFSET(void);
/*! \brief Writes the bit group 'VBLANK_PULSE_WIDTH' of register 'HDMI_VUNIT_VBLANK'. */
void GH_HDMI_set_VUNIT_VBLANK_VBLANK_PULSE_WIDTH(U8 data);
/*! \brief Reads the bit group 'VBLANK_PULSE_WIDTH' of register 'HDMI_VUNIT_VBLANK'. */
U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_PULSE_WIDTH(void);
/*! \brief Writes the bit group 'VBLANK_LEFT_OFFSET' of register 'HDMI_VUNIT_VBLANK'. */
void GH_HDMI_set_VUNIT_VBLANK_VBLANK_LEFT_OFFSET(U8 data);
/*! \brief Reads the bit group 'VBLANK_LEFT_OFFSET' of register 'HDMI_VUNIT_VBLANK'. */
U8   GH_HDMI_get_VUNIT_VBLANK_VBLANK_LEFT_OFFSET(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_HBLANK (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_VUNIT_HBLANK'. */
void GH_HDMI_set_VUNIT_HBLANK(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_HBLANK'. */
U32  GH_HDMI_get_VUNIT_HBLANK(void);
/*! \brief Writes the bit group 'HBLANK_RIGHT_OFFSET' of register 'HDMI_VUNIT_HBLANK'. */
void GH_HDMI_set_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET(U16 data);
/*! \brief Reads the bit group 'HBLANK_RIGHT_OFFSET' of register 'HDMI_VUNIT_HBLANK'. */
U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_RIGHT_OFFSET(void);
/*! \brief Writes the bit group 'HBLANK_PULSE_WIDTH' of register 'HDMI_VUNIT_HBLANK'. */
void GH_HDMI_set_VUNIT_HBLANK_HBLANK_PULSE_WIDTH(U16 data);
/*! \brief Reads the bit group 'HBLANK_PULSE_WIDTH' of register 'HDMI_VUNIT_HBLANK'. */
U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_PULSE_WIDTH(void);
/*! \brief Writes the bit group 'HBLANK_LEFT_OFFSET' of register 'HDMI_VUNIT_HBLANK'. */
void GH_HDMI_set_VUNIT_HBLANK_HBLANK_LEFT_OFFSET(U16 data);
/*! \brief Reads the bit group 'HBLANK_LEFT_OFFSET' of register 'HDMI_VUNIT_HBLANK'. */
U16  GH_HDMI_get_VUNIT_HBLANK_HBLANK_LEFT_OFFSET(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_VACTIVE (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_VUNIT_VACTIVE'. */
void GH_HDMI_set_VUNIT_VACTIVE(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_VACTIVE'. */
U32  GH_HDMI_get_VUNIT_VACTIVE(void);
/*! \brief Writes the bit group 'VUNIT_VACTIVE' of register 'HDMI_VUNIT_VACTIVE'. */
void GH_HDMI_set_VUNIT_VACTIVE_VUNIT_VACTIVE(U16 data);
/*! \brief Reads the bit group 'VUNIT_VACTIVE' of register 'HDMI_VUNIT_VACTIVE'. */
U16  GH_HDMI_get_VUNIT_VACTIVE_VUNIT_VACTIVE(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_HACTIVE (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_VUNIT_HACTIVE'. */
void GH_HDMI_set_VUNIT_HACTIVE(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_HACTIVE'. */
U32  GH_HDMI_get_VUNIT_HACTIVE(void);
/*! \brief Writes the bit group 'VUNIT_HACTIVE' of register 'HDMI_VUNIT_HACTIVE'. */
void GH_HDMI_set_VUNIT_HACTIVE_VUNIT_HACTIVE(U16 data);
/*! \brief Reads the bit group 'VUNIT_HACTIVE' of register 'HDMI_VUNIT_HACTIVE'. */
U16  GH_HDMI_get_VUNIT_HACTIVE_VUNIT_HACTIVE(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_CTRL (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_VUNIT_CTRL'. */
void GH_HDMI_set_VUNIT_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_CTRL'. */
U32  GH_HDMI_get_VUNIT_CTRL(void);
/*! \brief Writes the bit group 'VSYNC_POL' of register 'HDMI_VUNIT_CTRL'. */
void GH_HDMI_set_VUNIT_CTRL_VSYNC_POL(U8 data);
/*! \brief Reads the bit group 'VSYNC_POL' of register 'HDMI_VUNIT_CTRL'. */
U8   GH_HDMI_get_VUNIT_CTRL_VSYNC_POL(void);
/*! \brief Writes the bit group 'HSYNC_POL' of register 'HDMI_VUNIT_CTRL'. */
void GH_HDMI_set_VUNIT_CTRL_HSYNC_POL(U8 data);
/*! \brief Reads the bit group 'HSYNC_POL' of register 'HDMI_VUNIT_CTRL'. */
U8   GH_HDMI_get_VUNIT_CTRL_HSYNC_POL(void);
/*! \brief Writes the bit group 'VIDEO_MODE' of register 'HDMI_VUNIT_CTRL'. */
void GH_HDMI_set_VUNIT_CTRL_VIDEO_MODE(U8 data);
/*! \brief Reads the bit group 'VIDEO_MODE' of register 'HDMI_VUNIT_CTRL'. */
U8   GH_HDMI_get_VUNIT_CTRL_VIDEO_MODE(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_VUNIT_VSYNC_DETECT (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_VUNIT_VSYNC_DETECT'. */
void GH_HDMI_set_VUNIT_VSYNC_DETECT(U32 data);
/*! \brief Reads the register 'HDMI_VUNIT_VSYNC_DETECT'. */
U32  GH_HDMI_get_VUNIT_VSYNC_DETECT(void);
/*! \brief Writes the bit group 'VSYNC_DETECT_EN' of register 'HDMI_VUNIT_VSYNC_DETECT'. */
void GH_HDMI_set_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN(U8 data);
/*! \brief Reads the bit group 'VSYNC_DETECT_EN' of register 'HDMI_VUNIT_VSYNC_DETECT'. */
U8   GH_HDMI_get_VUNIT_VSYNC_DETECT_VSYNC_DETECT_EN(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMISE_TM (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM(U32 data);
/*! \brief Reads the register 'HDMI_HDMISE_TM'. */
U32  GH_HDMI_get_HDMISE_TM(void);
/*! \brief Writes the bit group 'I2S_DOUT_MODE' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_I2S_DOUT_MODE(U8 data);
/*! \brief Reads the bit group 'I2S_DOUT_MODE' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_I2S_DOUT_MODE(void);
/*! \brief Writes the bit group 'VDATA_SRC_MODE' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_VDATA_SRC_MODE(U8 data);
/*! \brief Reads the bit group 'VDATA_SRC_MODE' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_VDATA_SRC_MODE(void);
/*! \brief Writes the bit group 'VIDEO_PATTERN_MODE' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_VIDEO_PATTERN_MODE(U8 data);
/*! \brief Reads the bit group 'VIDEO_PATTERN_MODE' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_VIDEO_PATTERN_MODE(void);
/*! \brief Writes the bit group 'ADATA_SRC_MODE' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_ADATA_SRC_MODE(U8 data);
/*! \brief Reads the bit group 'ADATA_SRC_MODE' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_ADATA_SRC_MODE(void);
/*! \brief Writes the bit group 'BG_B' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_BG_B(U8 data);
/*! \brief Reads the bit group 'BG_B' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_BG_B(void);
/*! \brief Writes the bit group 'BG_G' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_BG_G(U8 data);
/*! \brief Reads the bit group 'BG_G' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_BG_G(void);
/*! \brief Writes the bit group 'BG_R' of register 'HDMI_HDMISE_TM'. */
void GH_HDMI_set_HDMISE_TM_BG_R(U8 data);
/*! \brief Reads the bit group 'BG_R' of register 'HDMI_HDMISE_TM'. */
U8   GH_HDMI_get_HDMISE_TM_BG_R(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_P2P_AFIFO_LEVEL (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL(U32 data);
/*! \brief Reads the register 'HDMI_P2P_AFIFO_LEVEL'. */
U32  GH_HDMI_get_P2P_AFIFO_LEVEL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LEVEL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_MIN_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_MIN_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MIN_LEVEL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_MAX_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_MAX_LEVEL' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_MAX_LEVEL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_LB' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_LB(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_LB' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_LB(void);
/*! \brief Writes the bit group 'P2P_AFIFO_UB' of register 'HDMI_P2P_AFIFO_LEVEL'. */
void GH_HDMI_set_P2P_AFIFO_LEVEL_P2P_AFIFO_UB(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_UB' of register 'HDMI_P2P_AFIFO_LEVEL'. */
U8   GH_HDMI_get_P2P_AFIFO_LEVEL_P2P_AFIFO_UB(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_P2P_AFIFO_CTRL (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_P2P_AFIFO_CTRL'. */
void GH_HDMI_set_P2P_AFIFO_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_P2P_AFIFO_CTRL'. */
U32  GH_HDMI_get_P2P_AFIFO_CTRL(void);
/*! \brief Writes the bit group 'P2P_AFIFO_EN' of register 'HDMI_P2P_AFIFO_CTRL'. */
void GH_HDMI_set_P2P_AFIFO_CTRL_P2P_AFIFO_EN(U8 data);
/*! \brief Reads the bit group 'P2P_AFIFO_EN' of register 'HDMI_P2P_AFIFO_CTRL'. */
U8   GH_HDMI_get_P2P_AFIFO_CTRL_P2P_AFIFO_EN(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMISE_DBG (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG(U32 data);
/*! \brief Reads the register 'HDMI_HDMISE_DBG'. */
U32  GH_HDMI_get_HDMISE_DBG(void);
/*! \brief Writes the bit group 'DBG_P2P_AFIFO_BYPASS' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS(U8 data);
/*! \brief Reads the bit group 'DBG_P2P_AFIFO_BYPASS' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_P2P_AFIFO_BYPASS(void);
/*! \brief Writes the bit group 'DBG_VDATA_SRC_MODE' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_VDATA_SRC_MODE(U8 data);
/*! \brief Reads the bit group 'DBG_VDATA_SRC_MODE' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_VDATA_SRC_MODE(void);
/*! \brief Writes the bit group 'DBG_CH_B_REV' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_CH_B_REV(U8 data);
/*! \brief Reads the bit group 'DBG_CH_B_REV' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_B_REV(void);
/*! \brief Writes the bit group 'DBG_CH_G_REV' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_CH_G_REV(U8 data);
/*! \brief Reads the bit group 'DBG_CH_G_REV' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_G_REV(void);
/*! \brief Writes the bit group 'DBG_CH_R_REV' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_CH_R_REV(U8 data);
/*! \brief Reads the bit group 'DBG_CH_R_REV' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_R_REV(void);
/*! \brief Writes the bit group 'DBG_CH_SWP' of register 'HDMI_HDMISE_DBG'. */
void GH_HDMI_set_HDMISE_DBG_DBG_CH_SWP(U8 data);
/*! \brief Reads the bit group 'DBG_CH_SWP' of register 'HDMI_HDMISE_DBG'. */
U8   GH_HDMI_get_HDMISE_DBG_DBG_CH_SWP(void);

/*----------------------------------------------------------------------------*/
/* register HDMI_HDMI_PHY_CTRL (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL(U32 data);
/*! \brief Reads the register 'HDMI_HDMI_PHY_CTRL'. */
U32  GH_HDMI_get_HDMI_PHY_CTRL(void);
/*! \brief Writes the bit group 'RSTND_HDMI' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_RSTND_HDMI(U8 data);
/*! \brief Reads the bit group 'RSTND_HDMI' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_RSTND_HDMI(void);
/*! \brief Writes the bit group 'PIB' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_PIB(U8 data);
/*! \brief Reads the bit group 'PIB' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_PIB(void);
/*! \brief Writes the bit group 'PES' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_PES(U8 data);
/*! \brief Reads the bit group 'PES' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_PES(void);
/*! \brief Writes the bit group 'PDB_HDMI' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_PDB_HDMI(U8 data);
/*! \brief Reads the bit group 'PDB_HDMI' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_PDB_HDMI(void);
/*! \brief Writes the bit group 'PD_BG' of register 'HDMI_HDMI_PHY_CTRL'. */
void GH_HDMI_set_HDMI_PHY_CTRL_PD_BG(U8 data);
/*! \brief Reads the bit group 'PD_BG' of register 'HDMI_HDMI_PHY_CTRL'. */
U8   GH_HDMI_get_HDMI_PHY_CTRL_PD_BG(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_HDMI_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_hdmi.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_HDMI_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

