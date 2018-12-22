/*!
*******************************************************************************
**
** \file      gh_usb_phy.h
**
** \brief     USB_PHY.
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
#ifndef _GH_USB_PHY_H
#define _GH_USB_PHY_H

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

#define GH_USB_PHY_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_USB_PHY_DEBUG_PRINT_FUNCTION printk
#else
#define GH_USB_PHY_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_USB_PHY_ENABLE_DEBUG_PRINT
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
#define REG_USB_PHY_UTMI_REG_00                             FIO_ADDRESS(USB_PHY,0x60021000) /* read/write */
#define REG_USB_PHY_UTMI_REG_01                             FIO_ADDRESS(USB_PHY,0x60021004) /* read/write */
#define REG_USB_PHY_UTMI_REG_02                             FIO_ADDRESS(USB_PHY,0x60021008) /* read/write */
#define REG_USB_PHY_UTMI_REG_03                             FIO_ADDRESS(USB_PHY,0x6002100C) /* read/write */
#define REG_USB_PHY_UTMI_REG_04                             FIO_ADDRESS(USB_PHY,0x60021010) /* read/write */
#define REG_USB_PHY_UTMI_REG_05                             FIO_ADDRESS(USB_PHY,0x60021014) /* read/write */
#define REG_USB_PHY_UTMI_REG_06                             FIO_ADDRESS(USB_PHY,0x60021018) /* read/write */
#define REG_USB_PHY_UTMI_STATUS                             FIO_ADDRESS(USB_PHY,0x6002101C) /* read */
#define REG_USB_PHY_UTMI_REG_08                             FIO_ADDRESS(USB_PHY,0x60021020) /* read/write */
#define REG_USB_PHY_UTMI_REG_09                             FIO_ADDRESS(USB_PHY,0x60021024) /* read/write */
#define REG_USB_PHY_UTMI_REG_0A                             FIO_ADDRESS(USB_PHY,0x60021028) /* read/write */
#define REG_USB_PHY_UTMI_REG_0B                             FIO_ADDRESS(USB_PHY,0x6002102C) /* read/write */
#define REG_USB_PHY_UTMI_REG_0C                             FIO_ADDRESS(USB_PHY,0x60021030) /* read/write */
#define REG_USB_PHY_UTMI_REG_10                             FIO_ADDRESS(USB_PHY,0x60021040) /* read/write */
#define REG_USB_PHY_UTMI_REG_11                             FIO_ADDRESS(USB_PHY,0x60021044) /* read/write */
#define REG_USB_PHY_UTMI_REG_12                             FIO_ADDRESS(USB_PHY,0x60021048) /* read/write */
#define REG_USB_PHY_UTMI_REG_13                             FIO_ADDRESS(USB_PHY,0x6002104C) /* read/write */
#define REG_USB_PHY_UTMI_REG_14                             FIO_ADDRESS(USB_PHY,0x60021050) /* read/write */
#define REG_USB_PHY_UTMI_REG_15                             FIO_ADDRESS(USB_PHY,0x60021054) /* read/write */
#define REG_USB_PHY_UTMI_REG_16                             FIO_ADDRESS(USB_PHY,0x60021058) /* read/write */
#define REG_USB_PHY_UTMI_REG_17                             FIO_ADDRESS(USB_PHY,0x6002105C) /* read/write */
#define REG_USB_PHY_UTMI_REG_18                             FIO_ADDRESS(USB_PHY,0x60021060) /* read/write */
#define REG_USB_PHY_UTMI_REG_19                             FIO_ADDRESS(USB_PHY,0x60021064) /* read/write */
#define REG_USB_PHY_UTMI_REG_1A                             FIO_ADDRESS(USB_PHY,0x60021068) /* read/write */
#define REG_USB_PHY_UTMI_REG_1B                             FIO_ADDRESS(USB_PHY,0x6002106C) /* read/write */
#define REG_USB_PHY_UTMI_REG_1C                             FIO_ADDRESS(USB_PHY,0x60021070) /* read/write */
#define REG_USB_PHY_UTMI_REG_1D                             FIO_ADDRESS(USB_PHY,0x60021074) /* read/write */
#define REG_USB_PHY_UTMI_REG_1E                             FIO_ADDRESS(USB_PHY,0x60021078) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* USB_PHY_UTMI_REG_00 */
    U16 all;
    struct {
        U16 pdn_override                : 1;
        U16 term_override               : 1;
        U16 ref_pdn                     : 1;
        U16 dp_puen                     : 1;
        U16 dm_puen                     : 1;
        U16 r_pumode                    : 1;
        U16 r_dp_pden                   : 1;
        U16 r_dm_pden                   : 1;
        U16 hs_dm_pdn                   : 1;
        U16 pll_pdn                     : 1;
        U16 hs_ted_pdn                  : 1;
        U16 hs_preamp_pdn               : 1;
        U16 f1_xcvf_pdn                 : 1;
        U16 vbusdet_pdn                 : 1;
        U16 iref_pdn                    : 1;
        U16 pdn                         : 1;
    } bitc;
} GH_USB_PHY_UTMI_REG_00_S;

typedef union { /* USB_PHY_UTMI_REG_01 */
    U16 all;
    struct {
        U16 sel_override                : 1;
        U16 fsls_sel                    : 1;
        U16 clk12_sel                   : 1;
        U16 nrzi_en                     : 1;
        U16 bitstuff_en                 : 1;
        U16 fl_lowimode                 : 1;
        U16 hs_tx_ten                   : 1;
        U16 bond_sel                    : 1;
        U16 bitstuff_override           : 1;
        U16 nrzi_override               : 1;
        U16 fl_sel_override             : 1;
        U16 eop40_det_delay_cnt         : 3;
        U16 linestate_sel               : 1;
        U16 hs_rterm_pdn                : 1;
    } bitc;
} GH_USB_PHY_UTMI_REG_01_S;

typedef union { /* USB_PHY_UTMI_REG_02 */
    U16 all;
    struct {
        U16 hs_tx_en_chip               : 1;
        U16 hs_tx_en_sw                 : 1;
        U16 dummy                       : 6;
        U16 tx_in_sel_multi_phase       : 2;
        U16 tx_out_sel_multi_phase      : 2;
        U16 utmi_tx_wait_cnt            : 4;
    } bitc;
} GH_USB_PHY_UTMI_REG_02_S;

typedef union { /* USB_PHY_UTMI_REG_03 */
    U16 all;
    struct {
        U16 rx_swreset                  : 1;
        U16 utmi_tx_sw_reset            : 1;
        U16 tx_force_hs_current_enable  : 1;
        U16 tx_fl_early_4               : 1;
        U16 tx_fl_latency_delay_1       : 1;
        U16 hs_stage_select             : 2;
        U16 otg_dual_role               : 1;
        U16 tx_reset_fsm                : 1;
        U16 cdr_mode_sel                : 1;
        U16 tx_reserved                 : 4;
        U16 vbusdet_test                : 2;
    } bitc;
} GH_USB_PHY_UTMI_REG_03_S;

typedef union { /* USB_PHY_UTMI_REG_04 */
    U16 all;
    struct {
        U16 utmi_clk_en                 : 1;
        U16 utmi_clk120_en              : 1;
        U16                             : 4;
        U16 clktest_en                  : 1;
        U16 clk_extra_0_en              : 1;
        U16 clk_extra_1_en              : 1;
        U16 xtal12_en                   : 1;
        U16 clk_ctl_override            : 1;
        U16 force_pll_on                : 1;
        U16 ck214_syn_en                : 1;
        U16 clk_274_en                  : 1;
        U16                             : 1;
        U16 hs_rx_roboust_en            : 1;
    } bitc;
} GH_USB_PHY_UTMI_REG_04_S;

typedef union { /* USB_PHY_UTMI_REG_05 */
    U16 all;
    struct {
        U16 utmi_clk_inv                : 1;
        U16 utmi_clk120_inv             : 1;
        U16 dummy1                      : 4;
        U16 clktest_inv                 : 1;
        U16 clk_extra_0_inv             : 1;
        U16 clk_extra_1_inv             : 1;
        U16 ck_inv_reserved             : 7;
    } bitc;
} GH_USB_PHY_UTMI_REG_05_S;

typedef union { /* USB_PHY_UTMI_REG_06 */
    U16 all;
    struct {
        U16 test_clock_select           : 6;
        U16 mac_clk_sel                 : 2;
        U16 double_data_rate            : 1;
        U16 clk_extra0_div_select       : 1;
        U16 clk_extra1_div_select       : 2;
        U16 utmi_ck_en_sel              : 2;
        U16 utmi_ckinv_en_sel           : 2;
    } bitc;
} GH_USB_PHY_UTMI_REG_06_S;

typedef union { /* USB_PHY_UTMI_STATUS */
    U16 all;
    struct {
        U16 elasticity_error            : 1;
        U16 sync_pattern_error          : 1;
        U16 eop_error                   : 1;
        U16 bit_stuffer_error           : 1;
        U16 elasticity_underflow        : 1;
        U16 overflow                    : 1;
        U16 clock_ready                 : 1;
        U16 interrupt                   : 1;
        U16 device                      : 1;
        U16 host                        : 1;
        U16 disconnect                  : 1;
        U16 tx_fsm                      : 1;
        U16 rx_fsm                      : 1;
        U16 low_speed                   : 1;
        U16 full_speed                  : 1;
        U16 hign_speed                  : 1;
    } bitc;
} GH_USB_PHY_UTMI_STATUS_S;

typedef union { /* USB_PHY_UTMI_REG_08 */
    U16 all;
    struct {
        U16 test_bus_select             : 4;
        U16 force_rx_nonbusy            : 1;
        U16 force_tx_nonbusy            : 1;
        U16 utmi_int_clr                : 1;
        U16 se0_set                     : 1;
        U16 tx_data                     : 1;
        U16 tx_en                       : 1;
        U16 tx_se0                      : 1;
        U16 tx_override                 : 1;
        U16 power_good_rst              : 1;
        U16 phy_mode_enable             : 1;
        U16 error_flag_clr              : 1;
        U16 hd_tx_override              : 1;
    } bitc;
} GH_USB_PHY_UTMI_REG_08_S;

typedef union { /* USB_PHY_UTMI_REG_09 */
    U16 all;
    struct {
        U16 deglitch_prd                : 6;
        U16 vdd2low_rst_enz             : 1;
        U16 deglitch_enz                : 1;
        U16 usbsyn_rst                  : 1;
        U16 reg_test                    : 3;
        U16 ib_rterm_test               : 3;
        U16 test_p1                     : 1;
    } bitc;
} GH_USB_PHY_UTMI_REG_09_S;

typedef union { /* USB_PHY_UTMI_REG_0A */
    U16 all;
    struct {
        U16 vbusvalid                   : 1;
        U16 avalid                      : 1;
        U16 sessend                     : 1;
        U16 iddig                       : 1;
        U16 opmode                      : 2;
        U16 xcvrsel                     : 2;
        U16 termsel                     : 1;
        U16 macmode_ovd                 : 1;
        U16 suspendm                    : 1;
        U16 usb_bond_ovd                : 1;
        U16 usb_bond_set                : 1;
        U16 host_chirp_det              : 1;
        U16 hs_tx_ien_mask              : 1;
        U16 hs_tx_ien_mask_method       : 1;
    } bitc;
} GH_USB_PHY_UTMI_REG_0A_S;

typedef union { /* USB_PHY_UTMI_REG_0B */
    U16 all;
    struct {
        U16 f                           : 11;
        U16 n                           : 5;
    } bitc;
} GH_USB_PHY_UTMI_REG_0B_S;

typedef union { /* USB_PHY_UTMI_REG_0C */
    U16 all;
    struct {
        U16 f                           : 16;
    } bitc;
} GH_USB_PHY_UTMI_REG_0C_S;

typedef union { /* USB_PHY_UTMI_REG_10 */
    U16 all;
    struct {
        U16 input_clock                 : 1;
        U16 divider_selection           : 2;
        U16 divider_control             : 5;
        U16 clock_outputs_source        : 2;
        U16 clock_outputs_ratio         : 2;
        U16 digital_output              : 2;
        U16 transmitter                 : 2;
    } bitc;
} GH_USB_PHY_UTMI_REG_10_S;

typedef union { /* USB_PHY_UTMI_REG_11 */
    U16 all;
    struct {
        U16 endisc                      : 1;
        U16 extdisc                     : 1;
        U16 enlockz                     : 1;
        U16 enauto                      : 1;
        U16 endcc                       : 1;
        U16 tvco                        : 2;
        U16 output_source               : 1;
        U16 eninv                       : 1;
        U16 eninventmux                 : 1;
        U16 input_clock                 : 1;
        U16                             : 5;
    } bitc;
} GH_USB_PHY_UTMI_REG_11_S;

typedef union { /* USB_PHY_UTMI_REG_12 */
    U16 all;
    struct {
        U16 ictl33                      : 3;
        U16 dis_hvflag_disc             : 1;
        U16 ensyn33                     : 1;
        U16 regulated                   : 2;
        U16 regulator                   : 1;
        U16                             : 8;
    } bitc;
} GH_USB_PHY_UTMI_REG_12_S;

typedef union { /* USB_PHY_UTMI_REG_13 */
    U16 all;
    struct {
        U16 de_glitch_time              : 2;
        U16 squelch_detector            : 2;
        U16                             : 6;
        U16 receiver_bias               : 2;
        U16                             : 4;
    } bitc;
} GH_USB_PHY_UTMI_REG_13_S;

typedef union { /* USB_PHY_UTMI_REG_14 */
    U16 all;
    struct {
        U16 slew_rate                   : 1;
        U16                             : 2;
        U16 hign_speed                  : 3;
        U16 full_speed0                 : 2;
        U16 full_speed1                 : 2;
        U16 slew                        : 1;
        U16 disable                     : 1;
        U16 test_dm                     : 1;
        U16 test_dp                     : 1;
        U16                             : 2;
    } bitc;
} GH_USB_PHY_UTMI_REG_14_S;

typedef union { /* USB_PHY_UTMI_REG_15 */
    U16 all;
    struct {
        U16 vspout                      : 2;
        U16 vsmout                      : 2;
        U16 vcpout                      : 2;
        U16 vcmout                      : 2;
        U16 pgd                         : 2;
        U16 power_good_33v              : 1;
        U16 power_good                  : 1;
        U16 vbg                         : 1;
        U16 vbgr                        : 1;
        U16                             : 1;
        U16 power_good_por              : 1;
    } bitc;
} GH_USB_PHY_UTMI_REG_15_S;

typedef union { /* USB_PHY_UTMI_REG_16 */
    U16 all;
    struct {
        U16                             : 3;
        U16 tx_text_clock               : 1;
        U16 tx_output_adjust            : 3;
        U16 tx_pre_emphasis_adjust      : 2;
        U16 tx_pre_emphasis_bias        : 1;
        U16 tx_current_bias             : 1;
        U16 hs_rterm                    : 3;
        U16 hs_tx                       : 1;
        U16 vbusdet_nc                  : 1;
    } bitc;
} GH_USB_PHY_UTMI_REG_16_S;

typedef union { /* USB_PHY_UTMI_REG_17 */
    U16 all;
    struct {
        U16 hs_rx                       : 1;
        U16 rterm                       : 1;
        U16 hs_rterm                    : 1;
        U16 hs_tx_itest                 : 1;
        U16                             : 4;
        U16 mute                        : 1;
        U16 pre_emphasis_en             : 1;
        U16 transition_edge             : 1;
        U16 enable_edge                 : 1;
        U16 clock_output                : 1;
        U16 source                      : 1;
        U16                             : 2;
    } bitc;
} GH_USB_PHY_UTMI_REG_17_S;

typedef union { /* USB_PHY_UTMI_REG_18 */
    U16 all;
    struct {
        U16 lock                        : 1;
        U16 flag1                       : 1;
        U16 flag2                       : 1;
        U16 test                        : 1;
        U16 power_good                  : 1;
        U16 vbus                        : 1;
        U16 otg                         : 1;
        U16 cid                         : 1;
        U16 avalid_atop                 : 1;
        U16 hs_disconnect               : 1;
        U16 hs_rx_data                  : 1;
        U16 hs_rx_chirp                 : 1;
        U16 fl_linestate0               : 1;
        U16 fl_linestate1               : 1;
        U16 failed                      : 1;
        U16 finish                      : 1;
    } bitc;
} GH_USB_PHY_UTMI_REG_18_S;

typedef union { /* USB_PHY_UTMI_REG_19 */
    U16 all;
    struct {
        U16 pg_tx_length                : 8;
        U16 pg_tx_go                    : 1;
        U16 pg_tx_mode                  : 1;
        U16 pg_tx_fixed_data            : 1;
        U16 continuous_mode             : 1;
        U16 receiving_mode              : 1;
        U16                             : 3;
    } bitc;
} GH_USB_PHY_UTMI_REG_19_S;

typedef union { /* USB_PHY_UTMI_REG_1A */
    U16 all;
    struct {
        U16 pg_tx_data                  : 16;
    } bitc;
} GH_USB_PHY_UTMI_REG_1A_S;

typedef union { /* USB_PHY_UTMI_REG_1B */
    U16 all;
    struct {
        U16 pg_tx_inc                   : 16;
    } bitc;
} GH_USB_PHY_UTMI_REG_1B_S;

typedef union { /* USB_PHY_UTMI_REG_1C */
    U16 all;
    struct {
        U16 en_ck192                    : 1;
        U16 vigen_pdn                   : 1;
        U16 selport                     : 1;
        U16 dp_status                   : 1;
        U16 dm_status                   : 1;
        U16 dp1_status                  : 1;
        U16 dm1_status                  : 1;
        U16 asrst_on                    : 1;
        U16 vbus                        : 1;
        U16 dummy                       : 1;
        U16 reserved                    : 6;
    } bitc;
} GH_USB_PHY_UTMI_REG_1C_S;

typedef union { /* USB_PHY_UTMI_REG_1D */
    U16 all;
    struct {
        U16 test_serdes                 : 8;
        U16 reg_test                    : 8;
    } bitc;
} GH_USB_PHY_UTMI_REG_1D_S;

typedef union { /* USB_PHY_UTMI_REG_1E */
    U16 all;
    struct {
        U16 ca_start                    : 1;
        U16 ca_end                      : 1;
        U16 power_good_sts              : 1;
        U16                             : 1;
        U16 ca_data                     : 12;
    } bitc;
} GH_USB_PHY_UTMI_REG_1E_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_00 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_00'. */
U16  GH_USB_PHY_get_UTMI_REG_00(void);
/*! \brief Writes the bit group 'pdn_override' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_pdn_override(U8 data);
/*! \brief Reads the bit group 'pdn_override' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_pdn_override(void);
/*! \brief Writes the bit group 'term_override' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_term_override(U8 data);
/*! \brief Reads the bit group 'term_override' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_term_override(void);
/*! \brief Writes the bit group 'ref_pdn' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_ref_pdn(U8 data);
/*! \brief Reads the bit group 'ref_pdn' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_ref_pdn(void);
/*! \brief Writes the bit group 'dp_puen' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_dp_puen(U8 data);
/*! \brief Reads the bit group 'dp_puen' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_dp_puen(void);
/*! \brief Writes the bit group 'dm_puen' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_dm_puen(U8 data);
/*! \brief Reads the bit group 'dm_puen' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_dm_puen(void);
/*! \brief Writes the bit group 'r_pumode' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_r_pumode(U8 data);
/*! \brief Reads the bit group 'r_pumode' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_r_pumode(void);
/*! \brief Writes the bit group 'r_dp_pden' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_r_dp_pden(U8 data);
/*! \brief Reads the bit group 'r_dp_pden' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_r_dp_pden(void);
/*! \brief Writes the bit group 'r_dm_pden' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_r_dm_pden(U8 data);
/*! \brief Reads the bit group 'r_dm_pden' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_r_dm_pden(void);
/*! \brief Writes the bit group 'hs_dm_pdn' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_hs_dm_pdn(U8 data);
/*! \brief Reads the bit group 'hs_dm_pdn' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_hs_dm_pdn(void);
/*! \brief Writes the bit group 'pll_pdn' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_pll_pdn(U8 data);
/*! \brief Reads the bit group 'pll_pdn' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_pll_pdn(void);
/*! \brief Writes the bit group 'hs_ted_pdn' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_hs_ted_pdn(U8 data);
/*! \brief Reads the bit group 'hs_ted_pdn' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_hs_ted_pdn(void);
/*! \brief Writes the bit group 'hs_preamp_pdn' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_hs_preamp_pdn(U8 data);
/*! \brief Reads the bit group 'hs_preamp_pdn' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_hs_preamp_pdn(void);
/*! \brief Writes the bit group 'f1_xcvf_pdn' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_f1_xcvf_pdn(U8 data);
/*! \brief Reads the bit group 'f1_xcvf_pdn' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_f1_xcvf_pdn(void);
/*! \brief Writes the bit group 'vbusdet_pdn' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_vbusdet_pdn(U8 data);
/*! \brief Reads the bit group 'vbusdet_pdn' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_vbusdet_pdn(void);
/*! \brief Writes the bit group 'iref_pdn' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_iref_pdn(U8 data);
/*! \brief Reads the bit group 'iref_pdn' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_iref_pdn(void);
/*! \brief Writes the bit group 'pdn' of register 'USB_PHY_UTMI_REG_00'. */
void GH_USB_PHY_set_UTMI_REG_00_pdn(U8 data);
/*! \brief Reads the bit group 'pdn' of register 'USB_PHY_UTMI_REG_00'. */
U8   GH_USB_PHY_get_UTMI_REG_00_pdn(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_00(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_pdn_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.pdn_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_pdn_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_pdn_override(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_pdn_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.pdn_override;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_term_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.term_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_term_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_term_override(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_term_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.term_override;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_ref_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.ref_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_ref_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_ref_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_ref_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.ref_pdn;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_dp_puen(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.dp_puen = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_dp_puen] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_dp_puen(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_dp_puen] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.dp_puen;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_dm_puen(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.dm_puen = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_dm_puen] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_dm_puen(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_dm_puen] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.dm_puen;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_r_pumode(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.r_pumode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_r_pumode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_r_pumode(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_r_pumode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.r_pumode;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_r_dp_pden(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.r_dp_pden = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_r_dp_pden] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_r_dp_pden(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_r_dp_pden] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.r_dp_pden;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_r_dm_pden(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.r_dm_pden = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_r_dm_pden] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_r_dm_pden(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_r_dm_pden] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.r_dm_pden;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_hs_dm_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.hs_dm_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_hs_dm_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_hs_dm_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_hs_dm_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.hs_dm_pdn;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_pll_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.pll_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_pll_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_pll_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_pll_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.pll_pdn;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_hs_ted_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.hs_ted_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_hs_ted_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_hs_ted_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_hs_ted_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.hs_ted_pdn;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_hs_preamp_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.hs_preamp_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_hs_preamp_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_hs_preamp_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_hs_preamp_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.hs_preamp_pdn;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_f1_xcvf_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.f1_xcvf_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_f1_xcvf_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_f1_xcvf_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_f1_xcvf_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.f1_xcvf_pdn;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_vbusdet_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.vbusdet_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_vbusdet_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_vbusdet_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_vbusdet_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.vbusdet_pdn;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_iref_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.iref_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_iref_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_iref_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_iref_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.iref_pdn;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_00_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_00_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_00;
    d.bitc.pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_00 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_00_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_00_pdn(void)
{
    GH_USB_PHY_UTMI_REG_00_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_00);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_00_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_00,value);
    #endif
    return tmp_value.bitc.pdn;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_01 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_01'. */
U16  GH_USB_PHY_get_UTMI_REG_01(void);
/*! \brief Writes the bit group 'sel_override' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_sel_override(U8 data);
/*! \brief Reads the bit group 'sel_override' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_sel_override(void);
/*! \brief Writes the bit group 'fsls_sel' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_fsls_sel(U8 data);
/*! \brief Reads the bit group 'fsls_sel' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_fsls_sel(void);
/*! \brief Writes the bit group 'clk12_sel' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_clk12_sel(U8 data);
/*! \brief Reads the bit group 'clk12_sel' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_clk12_sel(void);
/*! \brief Writes the bit group 'nrzi_en' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_nrzi_en(U8 data);
/*! \brief Reads the bit group 'nrzi_en' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_nrzi_en(void);
/*! \brief Writes the bit group 'bitstuff_en' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_bitstuff_en(U8 data);
/*! \brief Reads the bit group 'bitstuff_en' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_bitstuff_en(void);
/*! \brief Writes the bit group 'fl_lowimode' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_fl_lowimode(U8 data);
/*! \brief Reads the bit group 'fl_lowimode' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_fl_lowimode(void);
/*! \brief Writes the bit group 'hs_tx_ten' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_hs_tx_ten(U8 data);
/*! \brief Reads the bit group 'hs_tx_ten' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_hs_tx_ten(void);
/*! \brief Writes the bit group 'bond_sel' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_bond_sel(U8 data);
/*! \brief Reads the bit group 'bond_sel' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_bond_sel(void);
/*! \brief Writes the bit group 'bitstuff_override' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_bitstuff_override(U8 data);
/*! \brief Reads the bit group 'bitstuff_override' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_bitstuff_override(void);
/*! \brief Writes the bit group 'nrzi_override' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_nrzi_override(U8 data);
/*! \brief Reads the bit group 'nrzi_override' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_nrzi_override(void);
/*! \brief Writes the bit group 'fl_sel_override' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_fl_sel_override(U8 data);
/*! \brief Reads the bit group 'fl_sel_override' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_fl_sel_override(void);
/*! \brief Writes the bit group 'eop40_det_delay_cnt' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_eop40_det_delay_cnt(U8 data);
/*! \brief Reads the bit group 'eop40_det_delay_cnt' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_eop40_det_delay_cnt(void);
/*! \brief Writes the bit group 'linestate_sel' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_linestate_sel(U8 data);
/*! \brief Reads the bit group 'linestate_sel' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_linestate_sel(void);
/*! \brief Writes the bit group 'hs_rterm_pdn' of register 'USB_PHY_UTMI_REG_01'. */
void GH_USB_PHY_set_UTMI_REG_01_hs_rterm_pdn(U8 data);
/*! \brief Reads the bit group 'hs_rterm_pdn' of register 'USB_PHY_UTMI_REG_01'. */
U8   GH_USB_PHY_get_UTMI_REG_01_hs_rterm_pdn(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_01(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_sel_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.sel_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_sel_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_sel_override(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_sel_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.sel_override;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_fsls_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.fsls_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_fsls_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_fsls_sel(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_fsls_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.fsls_sel;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_clk12_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.clk12_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_clk12_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_clk12_sel(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_clk12_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.clk12_sel;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_nrzi_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.nrzi_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_nrzi_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_nrzi_en(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_nrzi_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.nrzi_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_bitstuff_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.bitstuff_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_bitstuff_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_bitstuff_en(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_bitstuff_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.bitstuff_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_fl_lowimode(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.fl_lowimode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_fl_lowimode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_fl_lowimode(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_fl_lowimode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.fl_lowimode;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_hs_tx_ten(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.hs_tx_ten = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_hs_tx_ten] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_hs_tx_ten(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_hs_tx_ten] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.hs_tx_ten;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_bond_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.bond_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_bond_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_bond_sel(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_bond_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.bond_sel;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_bitstuff_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.bitstuff_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_bitstuff_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_bitstuff_override(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_bitstuff_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.bitstuff_override;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_nrzi_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.nrzi_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_nrzi_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_nrzi_override(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_nrzi_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.nrzi_override;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_fl_sel_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.fl_sel_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_fl_sel_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_fl_sel_override(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_fl_sel_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.fl_sel_override;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_eop40_det_delay_cnt(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.eop40_det_delay_cnt = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_eop40_det_delay_cnt] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_eop40_det_delay_cnt(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_eop40_det_delay_cnt] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.eop40_det_delay_cnt;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_linestate_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.linestate_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_linestate_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_linestate_sel(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_linestate_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.linestate_sel;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_01_hs_rterm_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_01_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_01;
    d.bitc.hs_rterm_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_01 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_01_hs_rterm_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_01_hs_rterm_pdn(void)
{
    GH_USB_PHY_UTMI_REG_01_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_01);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_01_hs_rterm_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_01,value);
    #endif
    return tmp_value.bitc.hs_rterm_pdn;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_02 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_02'. */
void GH_USB_PHY_set_UTMI_REG_02(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_02'. */
U16  GH_USB_PHY_get_UTMI_REG_02(void);
/*! \brief Writes the bit group 'hs_tx_en_chip' of register 'USB_PHY_UTMI_REG_02'. */
void GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_chip(U8 data);
/*! \brief Reads the bit group 'hs_tx_en_chip' of register 'USB_PHY_UTMI_REG_02'. */
U8   GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_chip(void);
/*! \brief Writes the bit group 'hs_tx_en_sw' of register 'USB_PHY_UTMI_REG_02'. */
void GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_sw(U8 data);
/*! \brief Reads the bit group 'hs_tx_en_sw' of register 'USB_PHY_UTMI_REG_02'. */
U8   GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_sw(void);
/*! \brief Writes the bit group 'dummy' of register 'USB_PHY_UTMI_REG_02'. */
void GH_USB_PHY_set_UTMI_REG_02_dummy(U8 data);
/*! \brief Reads the bit group 'dummy' of register 'USB_PHY_UTMI_REG_02'. */
U8   GH_USB_PHY_get_UTMI_REG_02_dummy(void);
/*! \brief Writes the bit group 'tx_in_sel_multi_phase' of register 'USB_PHY_UTMI_REG_02'. */
void GH_USB_PHY_set_UTMI_REG_02_tx_in_sel_multi_phase(U8 data);
/*! \brief Reads the bit group 'tx_in_sel_multi_phase' of register 'USB_PHY_UTMI_REG_02'. */
U8   GH_USB_PHY_get_UTMI_REG_02_tx_in_sel_multi_phase(void);
/*! \brief Writes the bit group 'tx_out_sel_multi_phase' of register 'USB_PHY_UTMI_REG_02'. */
void GH_USB_PHY_set_UTMI_REG_02_tx_out_sel_multi_phase(U8 data);
/*! \brief Reads the bit group 'tx_out_sel_multi_phase' of register 'USB_PHY_UTMI_REG_02'. */
U8   GH_USB_PHY_get_UTMI_REG_02_tx_out_sel_multi_phase(void);
/*! \brief Writes the bit group 'utmi_tx_wait_cnt' of register 'USB_PHY_UTMI_REG_02'. */
void GH_USB_PHY_set_UTMI_REG_02_utmi_tx_wait_cnt(U8 data);
/*! \brief Reads the bit group 'utmi_tx_wait_cnt' of register 'USB_PHY_UTMI_REG_02'. */
U8   GH_USB_PHY_get_UTMI_REG_02_utmi_tx_wait_cnt(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_02(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_02(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_chip(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.hs_tx_en_chip = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_chip] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_chip(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_chip] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.hs_tx_en_chip;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_sw(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.hs_tx_en_sw = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_hs_tx_en_sw] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_sw(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_hs_tx_en_sw] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.hs_tx_en_sw;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_02_dummy(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.dummy = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_dummy] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_02_dummy(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_dummy] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.dummy;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_02_tx_in_sel_multi_phase(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.tx_in_sel_multi_phase = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_tx_in_sel_multi_phase] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_02_tx_in_sel_multi_phase(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_tx_in_sel_multi_phase] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.tx_in_sel_multi_phase;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_02_tx_out_sel_multi_phase(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.tx_out_sel_multi_phase = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_tx_out_sel_multi_phase] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_02_tx_out_sel_multi_phase(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_tx_out_sel_multi_phase] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.tx_out_sel_multi_phase;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_02_utmi_tx_wait_cnt(U8 data)
{
    GH_USB_PHY_UTMI_REG_02_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_02;
    d.bitc.utmi_tx_wait_cnt = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_02 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_02_utmi_tx_wait_cnt] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_02_utmi_tx_wait_cnt(void)
{
    GH_USB_PHY_UTMI_REG_02_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_02);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_02_utmi_tx_wait_cnt] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_02,value);
    #endif
    return tmp_value.bitc.utmi_tx_wait_cnt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_03 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_03'. */
U16  GH_USB_PHY_get_UTMI_REG_03(void);
/*! \brief Writes the bit group 'rx_swreset' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_rx_swreset(U8 data);
/*! \brief Reads the bit group 'rx_swreset' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_rx_swreset(void);
/*! \brief Writes the bit group 'utmi_tx_sw_reset' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_utmi_tx_sw_reset(U8 data);
/*! \brief Reads the bit group 'utmi_tx_sw_reset' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_utmi_tx_sw_reset(void);
/*! \brief Writes the bit group 'tx_force_hs_current_enable' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_tx_force_hs_current_enable(U8 data);
/*! \brief Reads the bit group 'tx_force_hs_current_enable' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_tx_force_hs_current_enable(void);
/*! \brief Writes the bit group 'tx_fl_early_4' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_tx_fl_early_4(U8 data);
/*! \brief Reads the bit group 'tx_fl_early_4' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_tx_fl_early_4(void);
/*! \brief Writes the bit group 'tx_fl_latency_delay_1' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_tx_fl_latency_delay_1(U8 data);
/*! \brief Reads the bit group 'tx_fl_latency_delay_1' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_tx_fl_latency_delay_1(void);
/*! \brief Writes the bit group 'hs_stage_select' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_hs_stage_select(U8 data);
/*! \brief Reads the bit group 'hs_stage_select' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_hs_stage_select(void);
/*! \brief Writes the bit group 'otg_dual_role' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_otg_dual_role(U8 data);
/*! \brief Reads the bit group 'otg_dual_role' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_otg_dual_role(void);
/*! \brief Writes the bit group 'tx_reset_fsm' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_tx_reset_fsm(U8 data);
/*! \brief Reads the bit group 'tx_reset_fsm' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_tx_reset_fsm(void);
/*! \brief Writes the bit group 'cdr_mode_sel' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_cdr_mode_sel(U8 data);
/*! \brief Reads the bit group 'cdr_mode_sel' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_cdr_mode_sel(void);
/*! \brief Writes the bit group 'tx_reserved' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_tx_reserved(U8 data);
/*! \brief Reads the bit group 'tx_reserved' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_tx_reserved(void);
/*! \brief Writes the bit group 'vbusdet_test' of register 'USB_PHY_UTMI_REG_03'. */
void GH_USB_PHY_set_UTMI_REG_03_vbusdet_test(U8 data);
/*! \brief Reads the bit group 'vbusdet_test' of register 'USB_PHY_UTMI_REG_03'. */
U8   GH_USB_PHY_get_UTMI_REG_03_vbusdet_test(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_03(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_rx_swreset(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.rx_swreset = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_rx_swreset] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_rx_swreset(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_rx_swreset] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.rx_swreset;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_utmi_tx_sw_reset(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.utmi_tx_sw_reset = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_utmi_tx_sw_reset] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_utmi_tx_sw_reset(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_utmi_tx_sw_reset] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.utmi_tx_sw_reset;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_tx_force_hs_current_enable(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_force_hs_current_enable = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_force_hs_current_enable] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_tx_force_hs_current_enable(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_force_hs_current_enable] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_force_hs_current_enable;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_tx_fl_early_4(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_fl_early_4 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_fl_early_4] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_tx_fl_early_4(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_fl_early_4] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_fl_early_4;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_tx_fl_latency_delay_1(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_fl_latency_delay_1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_fl_latency_delay_1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_tx_fl_latency_delay_1(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_fl_latency_delay_1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_fl_latency_delay_1;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_hs_stage_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.hs_stage_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_hs_stage_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_hs_stage_select(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_hs_stage_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.hs_stage_select;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_otg_dual_role(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.otg_dual_role = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_otg_dual_role] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_otg_dual_role(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_otg_dual_role] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.otg_dual_role;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_tx_reset_fsm(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_reset_fsm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_reset_fsm] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_tx_reset_fsm(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_reset_fsm] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_reset_fsm;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_cdr_mode_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.cdr_mode_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_cdr_mode_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_cdr_mode_sel(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_cdr_mode_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.cdr_mode_sel;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_tx_reserved(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.tx_reserved = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_tx_reserved] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_tx_reserved(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_tx_reserved] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.tx_reserved;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_03_vbusdet_test(U8 data)
{
    GH_USB_PHY_UTMI_REG_03_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_03;
    d.bitc.vbusdet_test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_03 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_03_vbusdet_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_03_vbusdet_test(void)
{
    GH_USB_PHY_UTMI_REG_03_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_03);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_03_vbusdet_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_03,value);
    #endif
    return tmp_value.bitc.vbusdet_test;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_04 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_04'. */
U16  GH_USB_PHY_get_UTMI_REG_04(void);
/*! \brief Writes the bit group 'utmi_clk_en' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_utmi_clk_en(U8 data);
/*! \brief Reads the bit group 'utmi_clk_en' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_utmi_clk_en(void);
/*! \brief Writes the bit group 'utmi_clk120_en' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_utmi_clk120_en(U8 data);
/*! \brief Reads the bit group 'utmi_clk120_en' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_utmi_clk120_en(void);
/*! \brief Writes the bit group 'clktest_en' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_clktest_en(U8 data);
/*! \brief Reads the bit group 'clktest_en' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_clktest_en(void);
/*! \brief Writes the bit group 'clk_extra_0_en' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_clk_extra_0_en(U8 data);
/*! \brief Reads the bit group 'clk_extra_0_en' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_clk_extra_0_en(void);
/*! \brief Writes the bit group 'clk_extra_1_en' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_clk_extra_1_en(U8 data);
/*! \brief Reads the bit group 'clk_extra_1_en' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_clk_extra_1_en(void);
/*! \brief Writes the bit group 'xtal12_en' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_xtal12_en(U8 data);
/*! \brief Reads the bit group 'xtal12_en' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_xtal12_en(void);
/*! \brief Writes the bit group 'clk_ctl_override' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_clk_ctl_override(U8 data);
/*! \brief Reads the bit group 'clk_ctl_override' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_clk_ctl_override(void);
/*! \brief Writes the bit group 'force_pll_on' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_force_pll_on(U8 data);
/*! \brief Reads the bit group 'force_pll_on' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_force_pll_on(void);
/*! \brief Writes the bit group 'ck214_syn_en' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_ck214_syn_en(U8 data);
/*! \brief Reads the bit group 'ck214_syn_en' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_ck214_syn_en(void);
/*! \brief Writes the bit group 'clk_274_en' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_clk_274_en(U8 data);
/*! \brief Reads the bit group 'clk_274_en' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_clk_274_en(void);
/*! \brief Writes the bit group 'hs_rx_roboust_en' of register 'USB_PHY_UTMI_REG_04'. */
void GH_USB_PHY_set_UTMI_REG_04_hs_rx_roboust_en(U8 data);
/*! \brief Reads the bit group 'hs_rx_roboust_en' of register 'USB_PHY_UTMI_REG_04'. */
U8   GH_USB_PHY_get_UTMI_REG_04_hs_rx_roboust_en(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_04(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_utmi_clk_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.utmi_clk_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_utmi_clk_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_utmi_clk_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_utmi_clk_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.utmi_clk_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_utmi_clk120_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.utmi_clk120_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_utmi_clk120_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_utmi_clk120_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_utmi_clk120_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.utmi_clk120_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_clktest_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clktest_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clktest_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_clktest_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clktest_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clktest_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_clk_extra_0_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clk_extra_0_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clk_extra_0_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_clk_extra_0_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clk_extra_0_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clk_extra_0_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_clk_extra_1_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clk_extra_1_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clk_extra_1_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_clk_extra_1_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clk_extra_1_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clk_extra_1_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_xtal12_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.xtal12_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_xtal12_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_xtal12_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_xtal12_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.xtal12_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_clk_ctl_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clk_ctl_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clk_ctl_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_clk_ctl_override(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clk_ctl_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clk_ctl_override;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_force_pll_on(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.force_pll_on = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_force_pll_on] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_force_pll_on(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_force_pll_on] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.force_pll_on;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_ck214_syn_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.ck214_syn_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_ck214_syn_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_ck214_syn_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_ck214_syn_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.ck214_syn_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_clk_274_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.clk_274_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_clk_274_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_clk_274_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_clk_274_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.clk_274_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_04_hs_rx_roboust_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_04_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_04;
    d.bitc.hs_rx_roboust_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_04 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_04_hs_rx_roboust_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_04_hs_rx_roboust_en(void)
{
    GH_USB_PHY_UTMI_REG_04_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_04);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_04_hs_rx_roboust_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_04,value);
    #endif
    return tmp_value.bitc.hs_rx_roboust_en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_05 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_05'. */
void GH_USB_PHY_set_UTMI_REG_05(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_05'. */
U16  GH_USB_PHY_get_UTMI_REG_05(void);
/*! \brief Writes the bit group 'utmi_clk_inv' of register 'USB_PHY_UTMI_REG_05'. */
void GH_USB_PHY_set_UTMI_REG_05_utmi_clk_inv(U8 data);
/*! \brief Reads the bit group 'utmi_clk_inv' of register 'USB_PHY_UTMI_REG_05'. */
U8   GH_USB_PHY_get_UTMI_REG_05_utmi_clk_inv(void);
/*! \brief Writes the bit group 'utmi_clk120_inv' of register 'USB_PHY_UTMI_REG_05'. */
void GH_USB_PHY_set_UTMI_REG_05_utmi_clk120_inv(U8 data);
/*! \brief Reads the bit group 'utmi_clk120_inv' of register 'USB_PHY_UTMI_REG_05'. */
U8   GH_USB_PHY_get_UTMI_REG_05_utmi_clk120_inv(void);
/*! \brief Writes the bit group 'dummy1' of register 'USB_PHY_UTMI_REG_05'. */
void GH_USB_PHY_set_UTMI_REG_05_dummy1(U8 data);
/*! \brief Reads the bit group 'dummy1' of register 'USB_PHY_UTMI_REG_05'. */
U8   GH_USB_PHY_get_UTMI_REG_05_dummy1(void);
/*! \brief Writes the bit group 'clktest_inv' of register 'USB_PHY_UTMI_REG_05'. */
void GH_USB_PHY_set_UTMI_REG_05_clktest_inv(U8 data);
/*! \brief Reads the bit group 'clktest_inv' of register 'USB_PHY_UTMI_REG_05'. */
U8   GH_USB_PHY_get_UTMI_REG_05_clktest_inv(void);
/*! \brief Writes the bit group 'clk_extra_0_inv' of register 'USB_PHY_UTMI_REG_05'. */
void GH_USB_PHY_set_UTMI_REG_05_clk_extra_0_inv(U8 data);
/*! \brief Reads the bit group 'clk_extra_0_inv' of register 'USB_PHY_UTMI_REG_05'. */
U8   GH_USB_PHY_get_UTMI_REG_05_clk_extra_0_inv(void);
/*! \brief Writes the bit group 'clk_extra_1_inv' of register 'USB_PHY_UTMI_REG_05'. */
void GH_USB_PHY_set_UTMI_REG_05_clk_extra_1_inv(U8 data);
/*! \brief Reads the bit group 'clk_extra_1_inv' of register 'USB_PHY_UTMI_REG_05'. */
U8   GH_USB_PHY_get_UTMI_REG_05_clk_extra_1_inv(void);
/*! \brief Writes the bit group 'ck_inv_reserved' of register 'USB_PHY_UTMI_REG_05'. */
void GH_USB_PHY_set_UTMI_REG_05_ck_inv_reserved(U8 data);
/*! \brief Reads the bit group 'ck_inv_reserved' of register 'USB_PHY_UTMI_REG_05'. */
U8   GH_USB_PHY_get_UTMI_REG_05_ck_inv_reserved(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_05(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_05(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_05_utmi_clk_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.utmi_clk_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_utmi_clk_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_05_utmi_clk_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_utmi_clk_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.utmi_clk_inv;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_05_utmi_clk120_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.utmi_clk120_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_utmi_clk120_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_05_utmi_clk120_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_utmi_clk120_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.utmi_clk120_inv;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_05_dummy1(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.dummy1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_dummy1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_05_dummy1(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_dummy1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.dummy1;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_05_clktest_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.clktest_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_clktest_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_05_clktest_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_clktest_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.clktest_inv;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_05_clk_extra_0_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.clk_extra_0_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_clk_extra_0_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_05_clk_extra_0_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_clk_extra_0_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.clk_extra_0_inv;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_05_clk_extra_1_inv(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.clk_extra_1_inv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_clk_extra_1_inv] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_05_clk_extra_1_inv(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_clk_extra_1_inv] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.clk_extra_1_inv;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_05_ck_inv_reserved(U8 data)
{
    GH_USB_PHY_UTMI_REG_05_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_05;
    d.bitc.ck_inv_reserved = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_05 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_05_ck_inv_reserved] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_05_ck_inv_reserved(void)
{
    GH_USB_PHY_UTMI_REG_05_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_05);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_05_ck_inv_reserved] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_05,value);
    #endif
    return tmp_value.bitc.ck_inv_reserved;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_06 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_06'. */
void GH_USB_PHY_set_UTMI_REG_06(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_06'. */
U16  GH_USB_PHY_get_UTMI_REG_06(void);
/*! \brief Writes the bit group 'test_clock_select' of register 'USB_PHY_UTMI_REG_06'. */
void GH_USB_PHY_set_UTMI_REG_06_test_clock_select(U8 data);
/*! \brief Reads the bit group 'test_clock_select' of register 'USB_PHY_UTMI_REG_06'. */
U8   GH_USB_PHY_get_UTMI_REG_06_test_clock_select(void);
/*! \brief Writes the bit group 'mac_clk_sel' of register 'USB_PHY_UTMI_REG_06'. */
void GH_USB_PHY_set_UTMI_REG_06_mac_clk_sel(U8 data);
/*! \brief Reads the bit group 'mac_clk_sel' of register 'USB_PHY_UTMI_REG_06'. */
U8   GH_USB_PHY_get_UTMI_REG_06_mac_clk_sel(void);
/*! \brief Writes the bit group 'double_data_rate' of register 'USB_PHY_UTMI_REG_06'. */
void GH_USB_PHY_set_UTMI_REG_06_double_data_rate(U8 data);
/*! \brief Reads the bit group 'double_data_rate' of register 'USB_PHY_UTMI_REG_06'. */
U8   GH_USB_PHY_get_UTMI_REG_06_double_data_rate(void);
/*! \brief Writes the bit group 'clk_extra0_div_select' of register 'USB_PHY_UTMI_REG_06'. */
void GH_USB_PHY_set_UTMI_REG_06_clk_extra0_div_select(U8 data);
/*! \brief Reads the bit group 'clk_extra0_div_select' of register 'USB_PHY_UTMI_REG_06'. */
U8   GH_USB_PHY_get_UTMI_REG_06_clk_extra0_div_select(void);
/*! \brief Writes the bit group 'clk_extra1_div_select' of register 'USB_PHY_UTMI_REG_06'. */
void GH_USB_PHY_set_UTMI_REG_06_clk_extra1_div_select(U8 data);
/*! \brief Reads the bit group 'clk_extra1_div_select' of register 'USB_PHY_UTMI_REG_06'. */
U8   GH_USB_PHY_get_UTMI_REG_06_clk_extra1_div_select(void);
/*! \brief Writes the bit group 'utmi_ck_en_sel' of register 'USB_PHY_UTMI_REG_06'. */
void GH_USB_PHY_set_UTMI_REG_06_utmi_ck_en_sel(U8 data);
/*! \brief Reads the bit group 'utmi_ck_en_sel' of register 'USB_PHY_UTMI_REG_06'. */
U8   GH_USB_PHY_get_UTMI_REG_06_utmi_ck_en_sel(void);
/*! \brief Writes the bit group 'utmi_ckinv_en_sel' of register 'USB_PHY_UTMI_REG_06'. */
void GH_USB_PHY_set_UTMI_REG_06_utmi_ckinv_en_sel(U8 data);
/*! \brief Reads the bit group 'utmi_ckinv_en_sel' of register 'USB_PHY_UTMI_REG_06'. */
U8   GH_USB_PHY_get_UTMI_REG_06_utmi_ckinv_en_sel(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_06(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_06(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_06_test_clock_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.test_clock_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_test_clock_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_06_test_clock_select(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_test_clock_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.test_clock_select;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_06_mac_clk_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.mac_clk_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_mac_clk_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_06_mac_clk_sel(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_mac_clk_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.mac_clk_sel;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_06_double_data_rate(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.double_data_rate = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_double_data_rate] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_06_double_data_rate(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_double_data_rate] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.double_data_rate;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_06_clk_extra0_div_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.clk_extra0_div_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_clk_extra0_div_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_06_clk_extra0_div_select(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_clk_extra0_div_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.clk_extra0_div_select;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_06_clk_extra1_div_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.clk_extra1_div_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_clk_extra1_div_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_06_clk_extra1_div_select(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_clk_extra1_div_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.clk_extra1_div_select;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_06_utmi_ck_en_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.utmi_ck_en_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_utmi_ck_en_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_06_utmi_ck_en_sel(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_utmi_ck_en_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.utmi_ck_en_sel;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_06_utmi_ckinv_en_sel(U8 data)
{
    GH_USB_PHY_UTMI_REG_06_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_06;
    d.bitc.utmi_ckinv_en_sel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_06 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_06_utmi_ckinv_en_sel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_06_utmi_ckinv_en_sel(void)
{
    GH_USB_PHY_UTMI_REG_06_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_06);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_06_utmi_ckinv_en_sel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_06,value);
    #endif
    return tmp_value.bitc.utmi_ckinv_en_sel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_STATUS (read)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'USB_PHY_UTMI_STATUS'. */
U16  GH_USB_PHY_get_UTMI_STATUS(void);
/*! \brief Reads the bit group 'elasticity_error' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_elasticity_error(void);
/*! \brief Reads the bit group 'Sync_pattern_error' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_Sync_pattern_error(void);
/*! \brief Reads the bit group 'EOP_error' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_EOP_error(void);
/*! \brief Reads the bit group 'bit_stuffer_error' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_bit_stuffer_error(void);
/*! \brief Reads the bit group 'elasticity_underflow' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_elasticity_underflow(void);
/*! \brief Reads the bit group 'overflow' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_overflow(void);
/*! \brief Reads the bit group 'clock_ready' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_clock_ready(void);
/*! \brief Reads the bit group 'interrupt' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_interrupt(void);
/*! \brief Reads the bit group 'device' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_device(void);
/*! \brief Reads the bit group 'host' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_host(void);
/*! \brief Reads the bit group 'Disconnect' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_Disconnect(void);
/*! \brief Reads the bit group 'TX_FSM' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_TX_FSM(void);
/*! \brief Reads the bit group 'RX_FSM' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_RX_FSM(void);
/*! \brief Reads the bit group 'low_speed' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_low_speed(void);
/*! \brief Reads the bit group 'full_speed' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_full_speed(void);
/*! \brief Reads the bit group 'Hign_speed' of register 'USB_PHY_UTMI_STATUS'. */
U8   GH_USB_PHY_get_UTMI_STATUS_Hign_speed(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_USB_PHY_get_UTMI_STATUS(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return value;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_elasticity_error(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_elasticity_error] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.elasticity_error;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_Sync_pattern_error(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_Sync_pattern_error] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.sync_pattern_error;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_EOP_error(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_EOP_error] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.eop_error;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_bit_stuffer_error(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_bit_stuffer_error] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.bit_stuffer_error;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_elasticity_underflow(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_elasticity_underflow] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.elasticity_underflow;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_overflow(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_overflow] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.overflow;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_clock_ready(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_clock_ready] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.clock_ready;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_interrupt(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_interrupt] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.interrupt;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_device(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_device] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.device;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_host(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_host] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.host;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_Disconnect(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_Disconnect] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.disconnect;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_TX_FSM(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_TX_FSM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.tx_fsm;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_RX_FSM(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_RX_FSM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.rx_fsm;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_low_speed(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_low_speed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.low_speed;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_full_speed(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_full_speed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.full_speed;
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_STATUS_Hign_speed(void)
{
    GH_USB_PHY_UTMI_STATUS_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_STATUS);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_STATUS_Hign_speed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_STATUS,value);
    #endif
    return tmp_value.bitc.hign_speed;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_08 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_08'. */
U16  GH_USB_PHY_get_UTMI_REG_08(void);
/*! \brief Writes the bit group 'test_bus_select' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_test_bus_select(U8 data);
/*! \brief Reads the bit group 'test_bus_select' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_test_bus_select(void);
/*! \brief Writes the bit group 'force_rx_nonbusy' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_force_rx_nonbusy(U8 data);
/*! \brief Reads the bit group 'force_rx_nonbusy' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_force_rx_nonbusy(void);
/*! \brief Writes the bit group 'force_tx_nonbusy' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_force_tx_nonbusy(U8 data);
/*! \brief Reads the bit group 'force_tx_nonbusy' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_force_tx_nonbusy(void);
/*! \brief Writes the bit group 'utmi_int_clr' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_utmi_int_clr(U8 data);
/*! \brief Reads the bit group 'utmi_int_clr' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_utmi_int_clr(void);
/*! \brief Writes the bit group 'se0_set' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_se0_set(U8 data);
/*! \brief Reads the bit group 'se0_set' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_se0_set(void);
/*! \brief Writes the bit group 'tx_data' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_tx_data(U8 data);
/*! \brief Reads the bit group 'tx_data' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_tx_data(void);
/*! \brief Writes the bit group 'tx_en' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_tx_en(U8 data);
/*! \brief Reads the bit group 'tx_en' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_tx_en(void);
/*! \brief Writes the bit group 'tx_se0' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_tx_se0(U8 data);
/*! \brief Reads the bit group 'tx_se0' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_tx_se0(void);
/*! \brief Writes the bit group 'tx_override' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_tx_override(U8 data);
/*! \brief Reads the bit group 'tx_override' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_tx_override(void);
/*! \brief Writes the bit group 'power_good_rst' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_power_good_rst(U8 data);
/*! \brief Reads the bit group 'power_good_rst' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_power_good_rst(void);
/*! \brief Writes the bit group 'phy_mode_enable' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_phy_mode_enable(U8 data);
/*! \brief Reads the bit group 'phy_mode_enable' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_phy_mode_enable(void);
/*! \brief Writes the bit group 'error_flag_clr' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_error_flag_clr(U8 data);
/*! \brief Reads the bit group 'error_flag_clr' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_error_flag_clr(void);
/*! \brief Writes the bit group 'hd_tx_override' of register 'USB_PHY_UTMI_REG_08'. */
void GH_USB_PHY_set_UTMI_REG_08_hd_tx_override(U8 data);
/*! \brief Reads the bit group 'hd_tx_override' of register 'USB_PHY_UTMI_REG_08'. */
U8   GH_USB_PHY_get_UTMI_REG_08_hd_tx_override(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_08(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_test_bus_select(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.test_bus_select = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_test_bus_select] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_test_bus_select(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_test_bus_select] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.test_bus_select;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_force_rx_nonbusy(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.force_rx_nonbusy = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_force_rx_nonbusy] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_force_rx_nonbusy(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_force_rx_nonbusy] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.force_rx_nonbusy;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_force_tx_nonbusy(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.force_tx_nonbusy = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_force_tx_nonbusy] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_force_tx_nonbusy(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_force_tx_nonbusy] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.force_tx_nonbusy;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_utmi_int_clr(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.utmi_int_clr = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_utmi_int_clr] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_utmi_int_clr(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_utmi_int_clr] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.utmi_int_clr;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_se0_set(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.se0_set = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_se0_set] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_se0_set(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_se0_set] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.se0_set;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_tx_data(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.tx_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_tx_data] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_tx_data(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_tx_data] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.tx_data;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_tx_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.tx_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_tx_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_tx_en(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_tx_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.tx_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_tx_se0(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.tx_se0 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_tx_se0] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_tx_se0(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_tx_se0] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.tx_se0;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_tx_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.tx_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_tx_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_tx_override(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_tx_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.tx_override;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_power_good_rst(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.power_good_rst = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_power_good_rst] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_power_good_rst(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_power_good_rst] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.power_good_rst;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_phy_mode_enable(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.phy_mode_enable = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_phy_mode_enable] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_phy_mode_enable(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_phy_mode_enable] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.phy_mode_enable;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_error_flag_clr(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.error_flag_clr = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_error_flag_clr] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_error_flag_clr(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_error_flag_clr] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.error_flag_clr;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_08_hd_tx_override(U8 data)
{
    GH_USB_PHY_UTMI_REG_08_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_08;
    d.bitc.hd_tx_override = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_08 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_08_hd_tx_override] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_08_hd_tx_override(void)
{
    GH_USB_PHY_UTMI_REG_08_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_08);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_08_hd_tx_override] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_08,value);
    #endif
    return tmp_value.bitc.hd_tx_override;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_09 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_09'. */
void GH_USB_PHY_set_UTMI_REG_09(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_09'. */
U16  GH_USB_PHY_get_UTMI_REG_09(void);
/*! \brief Writes the bit group 'deglitch_prd' of register 'USB_PHY_UTMI_REG_09'. */
void GH_USB_PHY_set_UTMI_REG_09_deglitch_prd(U8 data);
/*! \brief Reads the bit group 'deglitch_prd' of register 'USB_PHY_UTMI_REG_09'. */
U8   GH_USB_PHY_get_UTMI_REG_09_deglitch_prd(void);
/*! \brief Writes the bit group 'vdd2low_rst_enz' of register 'USB_PHY_UTMI_REG_09'. */
void GH_USB_PHY_set_UTMI_REG_09_vdd2low_rst_enz(U8 data);
/*! \brief Reads the bit group 'vdd2low_rst_enz' of register 'USB_PHY_UTMI_REG_09'. */
U8   GH_USB_PHY_get_UTMI_REG_09_vdd2low_rst_enz(void);
/*! \brief Writes the bit group 'deglitch_enz' of register 'USB_PHY_UTMI_REG_09'. */
void GH_USB_PHY_set_UTMI_REG_09_deglitch_enz(U8 data);
/*! \brief Reads the bit group 'deglitch_enz' of register 'USB_PHY_UTMI_REG_09'. */
U8   GH_USB_PHY_get_UTMI_REG_09_deglitch_enz(void);
/*! \brief Writes the bit group 'usbsyn_rst' of register 'USB_PHY_UTMI_REG_09'. */
void GH_USB_PHY_set_UTMI_REG_09_usbsyn_rst(U8 data);
/*! \brief Reads the bit group 'usbsyn_rst' of register 'USB_PHY_UTMI_REG_09'. */
U8   GH_USB_PHY_get_UTMI_REG_09_usbsyn_rst(void);
/*! \brief Writes the bit group 'reg_test' of register 'USB_PHY_UTMI_REG_09'. */
void GH_USB_PHY_set_UTMI_REG_09_reg_test(U8 data);
/*! \brief Reads the bit group 'reg_test' of register 'USB_PHY_UTMI_REG_09'. */
U8   GH_USB_PHY_get_UTMI_REG_09_reg_test(void);
/*! \brief Writes the bit group 'ib_rterm_test' of register 'USB_PHY_UTMI_REG_09'. */
void GH_USB_PHY_set_UTMI_REG_09_ib_rterm_test(U8 data);
/*! \brief Reads the bit group 'ib_rterm_test' of register 'USB_PHY_UTMI_REG_09'. */
U8   GH_USB_PHY_get_UTMI_REG_09_ib_rterm_test(void);
/*! \brief Writes the bit group 'test_p1' of register 'USB_PHY_UTMI_REG_09'. */
void GH_USB_PHY_set_UTMI_REG_09_test_p1(U8 data);
/*! \brief Reads the bit group 'test_p1' of register 'USB_PHY_UTMI_REG_09'. */
U8   GH_USB_PHY_get_UTMI_REG_09_test_p1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_09(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_09(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_09_deglitch_prd(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.deglitch_prd = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_deglitch_prd] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_09_deglitch_prd(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_deglitch_prd] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.deglitch_prd;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_09_vdd2low_rst_enz(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.vdd2low_rst_enz = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_vdd2low_rst_enz] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_09_vdd2low_rst_enz(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_vdd2low_rst_enz] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.vdd2low_rst_enz;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_09_deglitch_enz(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.deglitch_enz = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_deglitch_enz] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_09_deglitch_enz(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_deglitch_enz] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.deglitch_enz;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_09_usbsyn_rst(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.usbsyn_rst = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_usbsyn_rst] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_09_usbsyn_rst(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_usbsyn_rst] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.usbsyn_rst;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_09_reg_test(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.reg_test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_reg_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_09_reg_test(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_reg_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.reg_test;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_09_ib_rterm_test(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.ib_rterm_test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_ib_rterm_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_09_ib_rterm_test(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_ib_rterm_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.ib_rterm_test;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_09_test_p1(U8 data)
{
    GH_USB_PHY_UTMI_REG_09_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_09;
    d.bitc.test_p1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_09 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_09_test_p1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_09_test_p1(void)
{
    GH_USB_PHY_UTMI_REG_09_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_09);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_09_test_p1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_09,value);
    #endif
    return tmp_value.bitc.test_p1;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_0A (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_0A'. */
U16  GH_USB_PHY_get_UTMI_REG_0A(void);
/*! \brief Writes the bit group 'vbusvalid' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_vbusvalid(U8 data);
/*! \brief Reads the bit group 'vbusvalid' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_vbusvalid(void);
/*! \brief Writes the bit group 'avalid' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_avalid(U8 data);
/*! \brief Reads the bit group 'avalid' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_avalid(void);
/*! \brief Writes the bit group 'sessend' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_sessend(U8 data);
/*! \brief Reads the bit group 'sessend' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_sessend(void);
/*! \brief Writes the bit group 'iddig' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_iddig(U8 data);
/*! \brief Reads the bit group 'iddig' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_iddig(void);
/*! \brief Writes the bit group 'opmode' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_opmode(U8 data);
/*! \brief Reads the bit group 'opmode' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_opmode(void);
/*! \brief Writes the bit group 'xcvrsel' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_xcvrsel(U8 data);
/*! \brief Reads the bit group 'xcvrsel' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_xcvrsel(void);
/*! \brief Writes the bit group 'termsel' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_termsel(U8 data);
/*! \brief Reads the bit group 'termsel' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_termsel(void);
/*! \brief Writes the bit group 'macmode_ovd' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_macmode_ovd(U8 data);
/*! \brief Reads the bit group 'macmode_ovd' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_macmode_ovd(void);
/*! \brief Writes the bit group 'suspendm' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_suspendm(U8 data);
/*! \brief Reads the bit group 'suspendm' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_suspendm(void);
/*! \brief Writes the bit group 'usb_bond_ovd' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_usb_bond_ovd(U8 data);
/*! \brief Reads the bit group 'usb_bond_ovd' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_usb_bond_ovd(void);
/*! \brief Writes the bit group 'usb_bond_set' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_usb_bond_set(U8 data);
/*! \brief Reads the bit group 'usb_bond_set' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_usb_bond_set(void);
/*! \brief Writes the bit group 'host_chirp_det' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_host_chirp_det(U8 data);
/*! \brief Reads the bit group 'host_chirp_det' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_host_chirp_det(void);
/*! \brief Writes the bit group 'hs_tx_ien_mask' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask(U8 data);
/*! \brief Reads the bit group 'hs_tx_ien_mask' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask(void);
/*! \brief Writes the bit group 'hs_tx_ien_mask_method' of register 'USB_PHY_UTMI_REG_0A'. */
void GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask_method(U8 data);
/*! \brief Reads the bit group 'hs_tx_ien_mask_method' of register 'USB_PHY_UTMI_REG_0A'. */
U8   GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask_method(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_0A(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_vbusvalid(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.vbusvalid = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_vbusvalid] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_vbusvalid(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_vbusvalid] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.vbusvalid;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_avalid(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.avalid = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_avalid] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_avalid(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_avalid] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.avalid;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_sessend(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.sessend = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_sessend] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_sessend(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_sessend] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.sessend;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_iddig(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.iddig = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_iddig] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_iddig(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_iddig] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.iddig;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_opmode(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.opmode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_opmode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_opmode(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_opmode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.opmode;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_xcvrsel(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.xcvrsel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_xcvrsel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_xcvrsel(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_xcvrsel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.xcvrsel;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_termsel(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.termsel = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_termsel] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_termsel(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_termsel] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.termsel;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_macmode_ovd(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.macmode_ovd = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_macmode_ovd] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_macmode_ovd(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_macmode_ovd] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.macmode_ovd;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_suspendm(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.suspendm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_suspendm] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_suspendm(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_suspendm] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.suspendm;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_usb_bond_ovd(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.usb_bond_ovd = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_usb_bond_ovd] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_usb_bond_ovd(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_usb_bond_ovd] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.usb_bond_ovd;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_usb_bond_set(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.usb_bond_set = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_usb_bond_set] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_usb_bond_set(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_usb_bond_set] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.usb_bond_set;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_host_chirp_det(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.host_chirp_det = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_host_chirp_det] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_host_chirp_det(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_host_chirp_det] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.host_chirp_det;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.hs_tx_ien_mask = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.hs_tx_ien_mask;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask_method(U8 data)
{
    GH_USB_PHY_UTMI_REG_0A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A;
    d.bitc.hs_tx_ien_mask_method = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0A_hs_tx_ien_mask_method] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask_method(void)
{
    GH_USB_PHY_UTMI_REG_0A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0A_hs_tx_ien_mask_method] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0A,value);
    #endif
    return tmp_value.bitc.hs_tx_ien_mask_method;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_0B (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_0B'. */
void GH_USB_PHY_set_UTMI_REG_0B(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_0B'. */
U16  GH_USB_PHY_get_UTMI_REG_0B(void);
/*! \brief Writes the bit group 'f' of register 'USB_PHY_UTMI_REG_0B'. */
void GH_USB_PHY_set_UTMI_REG_0B_f(U16 data);
/*! \brief Reads the bit group 'f' of register 'USB_PHY_UTMI_REG_0B'. */
U16  GH_USB_PHY_get_UTMI_REG_0B_f(void);
/*! \brief Writes the bit group 'N' of register 'USB_PHY_UTMI_REG_0B'. */
void GH_USB_PHY_set_UTMI_REG_0B_N(U8 data);
/*! \brief Reads the bit group 'N' of register 'USB_PHY_UTMI_REG_0B'. */
U8   GH_USB_PHY_get_UTMI_REG_0B_N(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0B(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0B] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_0B(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0B);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0B] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0B_f(U16 data)
{
    GH_USB_PHY_UTMI_REG_0B_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B;
    d.bitc.f = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0B_f] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_0B_f(void)
{
    GH_USB_PHY_UTMI_REG_0B_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0B);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0B_f] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,value);
    #endif
    return tmp_value.bitc.f;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0B_N(U8 data)
{
    GH_USB_PHY_UTMI_REG_0B_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B;
    d.bitc.n = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0B = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0B_N] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_0B_N(void)
{
    GH_USB_PHY_UTMI_REG_0B_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0B);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0B_N] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0B,value);
    #endif
    return tmp_value.bitc.n;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_0C (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_0C'. */
void GH_USB_PHY_set_UTMI_REG_0C(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_0C'. */
U16  GH_USB_PHY_get_UTMI_REG_0C(void);
/*! \brief Writes the bit group 'f' of register 'USB_PHY_UTMI_REG_0C'. */
void GH_USB_PHY_set_UTMI_REG_0C_f(U16 data);
/*! \brief Reads the bit group 'f' of register 'USB_PHY_UTMI_REG_0C'. */
U16  GH_USB_PHY_get_UTMI_REG_0C_f(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0C(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0C = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0C] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0C,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_0C(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0C);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0C] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0C,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_0C_f(U16 data)
{
    GH_USB_PHY_UTMI_REG_0C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_0C;
    d.bitc.f = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_0C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_0C_f] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0C,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_0C_f(void)
{
    GH_USB_PHY_UTMI_REG_0C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_0C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_0C_f] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_0C,value);
    #endif
    return tmp_value.bitc.f;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_10 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_10'. */
void GH_USB_PHY_set_UTMI_REG_10(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_10'. */
U16  GH_USB_PHY_get_UTMI_REG_10(void);
/*! \brief Writes the bit group 'input_clock' of register 'USB_PHY_UTMI_REG_10'. */
void GH_USB_PHY_set_UTMI_REG_10_input_clock(U8 data);
/*! \brief Reads the bit group 'input_clock' of register 'USB_PHY_UTMI_REG_10'. */
U8   GH_USB_PHY_get_UTMI_REG_10_input_clock(void);
/*! \brief Writes the bit group 'divider_selection' of register 'USB_PHY_UTMI_REG_10'. */
void GH_USB_PHY_set_UTMI_REG_10_divider_selection(U8 data);
/*! \brief Reads the bit group 'divider_selection' of register 'USB_PHY_UTMI_REG_10'. */
U8   GH_USB_PHY_get_UTMI_REG_10_divider_selection(void);
/*! \brief Writes the bit group 'divider_control' of register 'USB_PHY_UTMI_REG_10'. */
void GH_USB_PHY_set_UTMI_REG_10_divider_control(U8 data);
/*! \brief Reads the bit group 'divider_control' of register 'USB_PHY_UTMI_REG_10'. */
U8   GH_USB_PHY_get_UTMI_REG_10_divider_control(void);
/*! \brief Writes the bit group 'clock_outputs_source' of register 'USB_PHY_UTMI_REG_10'. */
void GH_USB_PHY_set_UTMI_REG_10_clock_outputs_source(U8 data);
/*! \brief Reads the bit group 'clock_outputs_source' of register 'USB_PHY_UTMI_REG_10'. */
U8   GH_USB_PHY_get_UTMI_REG_10_clock_outputs_source(void);
/*! \brief Writes the bit group 'clock_outputs_ratio' of register 'USB_PHY_UTMI_REG_10'. */
void GH_USB_PHY_set_UTMI_REG_10_clock_outputs_ratio(U8 data);
/*! \brief Reads the bit group 'clock_outputs_ratio' of register 'USB_PHY_UTMI_REG_10'. */
U8   GH_USB_PHY_get_UTMI_REG_10_clock_outputs_ratio(void);
/*! \brief Writes the bit group 'digital_output' of register 'USB_PHY_UTMI_REG_10'. */
void GH_USB_PHY_set_UTMI_REG_10_digital_output(U8 data);
/*! \brief Reads the bit group 'digital_output' of register 'USB_PHY_UTMI_REG_10'. */
U8   GH_USB_PHY_get_UTMI_REG_10_digital_output(void);
/*! \brief Writes the bit group 'transmitter' of register 'USB_PHY_UTMI_REG_10'. */
void GH_USB_PHY_set_UTMI_REG_10_transmitter(U8 data);
/*! \brief Reads the bit group 'transmitter' of register 'USB_PHY_UTMI_REG_10'. */
U8   GH_USB_PHY_get_UTMI_REG_10_transmitter(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_10(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_10 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_10] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_10(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_10);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_10] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_10_input_clock(U8 data)
{
    GH_USB_PHY_UTMI_REG_10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_10;
    d.bitc.input_clock = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_10_input_clock] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_10_input_clock(void)
{
    GH_USB_PHY_UTMI_REG_10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_10_input_clock] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,value);
    #endif
    return tmp_value.bitc.input_clock;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_10_divider_selection(U8 data)
{
    GH_USB_PHY_UTMI_REG_10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_10;
    d.bitc.divider_selection = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_10_divider_selection] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_10_divider_selection(void)
{
    GH_USB_PHY_UTMI_REG_10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_10_divider_selection] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,value);
    #endif
    return tmp_value.bitc.divider_selection;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_10_divider_control(U8 data)
{
    GH_USB_PHY_UTMI_REG_10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_10;
    d.bitc.divider_control = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_10_divider_control] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_10_divider_control(void)
{
    GH_USB_PHY_UTMI_REG_10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_10_divider_control] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,value);
    #endif
    return tmp_value.bitc.divider_control;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_10_clock_outputs_source(U8 data)
{
    GH_USB_PHY_UTMI_REG_10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_10;
    d.bitc.clock_outputs_source = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_10_clock_outputs_source] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_10_clock_outputs_source(void)
{
    GH_USB_PHY_UTMI_REG_10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_10_clock_outputs_source] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,value);
    #endif
    return tmp_value.bitc.clock_outputs_source;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_10_clock_outputs_ratio(U8 data)
{
    GH_USB_PHY_UTMI_REG_10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_10;
    d.bitc.clock_outputs_ratio = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_10_clock_outputs_ratio] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_10_clock_outputs_ratio(void)
{
    GH_USB_PHY_UTMI_REG_10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_10_clock_outputs_ratio] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,value);
    #endif
    return tmp_value.bitc.clock_outputs_ratio;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_10_digital_output(U8 data)
{
    GH_USB_PHY_UTMI_REG_10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_10;
    d.bitc.digital_output = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_10_digital_output] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_10_digital_output(void)
{
    GH_USB_PHY_UTMI_REG_10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_10_digital_output] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,value);
    #endif
    return tmp_value.bitc.digital_output;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_10_transmitter(U8 data)
{
    GH_USB_PHY_UTMI_REG_10_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_10;
    d.bitc.transmitter = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_10 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_10_transmitter] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_10_transmitter(void)
{
    GH_USB_PHY_UTMI_REG_10_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_10);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_10_transmitter] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_10,value);
    #endif
    return tmp_value.bitc.transmitter;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_11 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_11'. */
U16  GH_USB_PHY_get_UTMI_REG_11(void);
/*! \brief Writes the bit group 'ENDISC' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_ENDISC(U8 data);
/*! \brief Reads the bit group 'ENDISC' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_ENDISC(void);
/*! \brief Writes the bit group 'EXTDISC' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_EXTDISC(U8 data);
/*! \brief Reads the bit group 'EXTDISC' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_EXTDISC(void);
/*! \brief Writes the bit group 'ENLOCKZ' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_ENLOCKZ(U8 data);
/*! \brief Reads the bit group 'ENLOCKZ' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_ENLOCKZ(void);
/*! \brief Writes the bit group 'ENAUTO' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_ENAUTO(U8 data);
/*! \brief Reads the bit group 'ENAUTO' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_ENAUTO(void);
/*! \brief Writes the bit group 'ENDCC' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_ENDCC(U8 data);
/*! \brief Reads the bit group 'ENDCC' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_ENDCC(void);
/*! \brief Writes the bit group 'TVCO' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_TVCO(U8 data);
/*! \brief Reads the bit group 'TVCO' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_TVCO(void);
/*! \brief Writes the bit group 'output_source' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_output_source(U8 data);
/*! \brief Reads the bit group 'output_source' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_output_source(void);
/*! \brief Writes the bit group 'ENINV' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_ENINV(U8 data);
/*! \brief Reads the bit group 'ENINV' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_ENINV(void);
/*! \brief Writes the bit group 'ENINVENTMUX' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_ENINVENTMUX(U8 data);
/*! \brief Reads the bit group 'ENINVENTMUX' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_ENINVENTMUX(void);
/*! \brief Writes the bit group 'input_clock' of register 'USB_PHY_UTMI_REG_11'. */
void GH_USB_PHY_set_UTMI_REG_11_input_clock(U8 data);
/*! \brief Reads the bit group 'input_clock' of register 'USB_PHY_UTMI_REG_11'. */
U8   GH_USB_PHY_get_UTMI_REG_11_input_clock(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_11(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_ENDISC(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.endisc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_ENDISC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_ENDISC(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_ENDISC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.endisc;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_EXTDISC(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.extdisc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_EXTDISC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_EXTDISC(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_EXTDISC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.extdisc;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_ENLOCKZ(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.enlockz = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_ENLOCKZ] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_ENLOCKZ(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_ENLOCKZ] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.enlockz;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_ENAUTO(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.enauto = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_ENAUTO] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_ENAUTO(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_ENAUTO] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.enauto;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_ENDCC(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.endcc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_ENDCC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_ENDCC(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_ENDCC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.endcc;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_TVCO(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.tvco = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_TVCO] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_TVCO(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_TVCO] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.tvco;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_output_source(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.output_source = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_output_source] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_output_source(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_output_source] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.output_source;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_ENINV(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.eninv = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_ENINV] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_ENINV(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_ENINV] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.eninv;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_ENINVENTMUX(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.eninventmux = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_ENINVENTMUX] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_ENINVENTMUX(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_ENINVENTMUX] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.eninventmux;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_11_input_clock(U8 data)
{
    GH_USB_PHY_UTMI_REG_11_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_11;
    d.bitc.input_clock = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_11 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_11_input_clock] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_11_input_clock(void)
{
    GH_USB_PHY_UTMI_REG_11_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_11);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_11_input_clock] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_11,value);
    #endif
    return tmp_value.bitc.input_clock;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_12 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_12'. */
void GH_USB_PHY_set_UTMI_REG_12(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_12'. */
U16  GH_USB_PHY_get_UTMI_REG_12(void);
/*! \brief Writes the bit group 'ICTL33' of register 'USB_PHY_UTMI_REG_12'. */
void GH_USB_PHY_set_UTMI_REG_12_ICTL33(U8 data);
/*! \brief Reads the bit group 'ICTL33' of register 'USB_PHY_UTMI_REG_12'. */
U8   GH_USB_PHY_get_UTMI_REG_12_ICTL33(void);
/*! \brief Writes the bit group 'DIS_HVFLAG_DISC' of register 'USB_PHY_UTMI_REG_12'. */
void GH_USB_PHY_set_UTMI_REG_12_DIS_HVFLAG_DISC(U8 data);
/*! \brief Reads the bit group 'DIS_HVFLAG_DISC' of register 'USB_PHY_UTMI_REG_12'. */
U8   GH_USB_PHY_get_UTMI_REG_12_DIS_HVFLAG_DISC(void);
/*! \brief Writes the bit group 'ENSYN33' of register 'USB_PHY_UTMI_REG_12'. */
void GH_USB_PHY_set_UTMI_REG_12_ENSYN33(U8 data);
/*! \brief Reads the bit group 'ENSYN33' of register 'USB_PHY_UTMI_REG_12'. */
U8   GH_USB_PHY_get_UTMI_REG_12_ENSYN33(void);
/*! \brief Writes the bit group 'Regulated' of register 'USB_PHY_UTMI_REG_12'. */
void GH_USB_PHY_set_UTMI_REG_12_Regulated(U8 data);
/*! \brief Reads the bit group 'Regulated' of register 'USB_PHY_UTMI_REG_12'. */
U8   GH_USB_PHY_get_UTMI_REG_12_Regulated(void);
/*! \brief Writes the bit group 'Regulator' of register 'USB_PHY_UTMI_REG_12'. */
void GH_USB_PHY_set_UTMI_REG_12_Regulator(U8 data);
/*! \brief Reads the bit group 'Regulator' of register 'USB_PHY_UTMI_REG_12'. */
U8   GH_USB_PHY_get_UTMI_REG_12_Regulator(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_12(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_12 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_12] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_12(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_12);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_12] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_12_ICTL33(U8 data)
{
    GH_USB_PHY_UTMI_REG_12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_12;
    d.bitc.ictl33 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_12_ICTL33] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_12_ICTL33(void)
{
    GH_USB_PHY_UTMI_REG_12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_12_ICTL33] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,value);
    #endif
    return tmp_value.bitc.ictl33;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_12_DIS_HVFLAG_DISC(U8 data)
{
    GH_USB_PHY_UTMI_REG_12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_12;
    d.bitc.dis_hvflag_disc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_12_DIS_HVFLAG_DISC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_12_DIS_HVFLAG_DISC(void)
{
    GH_USB_PHY_UTMI_REG_12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_12_DIS_HVFLAG_DISC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,value);
    #endif
    return tmp_value.bitc.dis_hvflag_disc;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_12_ENSYN33(U8 data)
{
    GH_USB_PHY_UTMI_REG_12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_12;
    d.bitc.ensyn33 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_12_ENSYN33] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_12_ENSYN33(void)
{
    GH_USB_PHY_UTMI_REG_12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_12_ENSYN33] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,value);
    #endif
    return tmp_value.bitc.ensyn33;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_12_Regulated(U8 data)
{
    GH_USB_PHY_UTMI_REG_12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_12;
    d.bitc.regulated = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_12_Regulated] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_12_Regulated(void)
{
    GH_USB_PHY_UTMI_REG_12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_12_Regulated] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,value);
    #endif
    return tmp_value.bitc.regulated;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_12_Regulator(U8 data)
{
    GH_USB_PHY_UTMI_REG_12_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_12;
    d.bitc.regulator = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_12 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_12_Regulator] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_12_Regulator(void)
{
    GH_USB_PHY_UTMI_REG_12_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_12);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_12_Regulator] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_12,value);
    #endif
    return tmp_value.bitc.regulator;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_13 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_13'. */
void GH_USB_PHY_set_UTMI_REG_13(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_13'. */
U16  GH_USB_PHY_get_UTMI_REG_13(void);
/*! \brief Writes the bit group 'De_glitch_time' of register 'USB_PHY_UTMI_REG_13'. */
void GH_USB_PHY_set_UTMI_REG_13_De_glitch_time(U8 data);
/*! \brief Reads the bit group 'De_glitch_time' of register 'USB_PHY_UTMI_REG_13'. */
U8   GH_USB_PHY_get_UTMI_REG_13_De_glitch_time(void);
/*! \brief Writes the bit group 'Squelch_detector' of register 'USB_PHY_UTMI_REG_13'. */
void GH_USB_PHY_set_UTMI_REG_13_Squelch_detector(U8 data);
/*! \brief Reads the bit group 'Squelch_detector' of register 'USB_PHY_UTMI_REG_13'. */
U8   GH_USB_PHY_get_UTMI_REG_13_Squelch_detector(void);
/*! \brief Writes the bit group 'receiver_bias' of register 'USB_PHY_UTMI_REG_13'. */
void GH_USB_PHY_set_UTMI_REG_13_receiver_bias(U8 data);
/*! \brief Reads the bit group 'receiver_bias' of register 'USB_PHY_UTMI_REG_13'. */
U8   GH_USB_PHY_get_UTMI_REG_13_receiver_bias(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_13(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_13 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_13] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_13,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_13(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_13);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_13] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_13,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_13_De_glitch_time(U8 data)
{
    GH_USB_PHY_UTMI_REG_13_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_13;
    d.bitc.de_glitch_time = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_13 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_13_De_glitch_time] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_13,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_13_De_glitch_time(void)
{
    GH_USB_PHY_UTMI_REG_13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_13);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_13_De_glitch_time] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_13,value);
    #endif
    return tmp_value.bitc.de_glitch_time;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_13_Squelch_detector(U8 data)
{
    GH_USB_PHY_UTMI_REG_13_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_13;
    d.bitc.squelch_detector = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_13 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_13_Squelch_detector] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_13,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_13_Squelch_detector(void)
{
    GH_USB_PHY_UTMI_REG_13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_13);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_13_Squelch_detector] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_13,value);
    #endif
    return tmp_value.bitc.squelch_detector;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_13_receiver_bias(U8 data)
{
    GH_USB_PHY_UTMI_REG_13_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_13;
    d.bitc.receiver_bias = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_13 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_13_receiver_bias] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_13,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_13_receiver_bias(void)
{
    GH_USB_PHY_UTMI_REG_13_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_13);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_13_receiver_bias] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_13,value);
    #endif
    return tmp_value.bitc.receiver_bias;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_14 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_14'. */
void GH_USB_PHY_set_UTMI_REG_14(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_14'. */
U16  GH_USB_PHY_get_UTMI_REG_14(void);
/*! \brief Writes the bit group 'slew_rate' of register 'USB_PHY_UTMI_REG_14'. */
void GH_USB_PHY_set_UTMI_REG_14_slew_rate(U8 data);
/*! \brief Reads the bit group 'slew_rate' of register 'USB_PHY_UTMI_REG_14'. */
U8   GH_USB_PHY_get_UTMI_REG_14_slew_rate(void);
/*! \brief Writes the bit group 'Hign_speed' of register 'USB_PHY_UTMI_REG_14'. */
void GH_USB_PHY_set_UTMI_REG_14_Hign_speed(U8 data);
/*! \brief Reads the bit group 'Hign_speed' of register 'USB_PHY_UTMI_REG_14'. */
U8   GH_USB_PHY_get_UTMI_REG_14_Hign_speed(void);
/*! \brief Writes the bit group 'Full_speed0' of register 'USB_PHY_UTMI_REG_14'. */
void GH_USB_PHY_set_UTMI_REG_14_Full_speed0(U8 data);
/*! \brief Reads the bit group 'Full_speed0' of register 'USB_PHY_UTMI_REG_14'. */
U8   GH_USB_PHY_get_UTMI_REG_14_Full_speed0(void);
/*! \brief Writes the bit group 'Full_speed1' of register 'USB_PHY_UTMI_REG_14'. */
void GH_USB_PHY_set_UTMI_REG_14_Full_speed1(U8 data);
/*! \brief Reads the bit group 'Full_speed1' of register 'USB_PHY_UTMI_REG_14'. */
U8   GH_USB_PHY_get_UTMI_REG_14_Full_speed1(void);
/*! \brief Writes the bit group 'slew' of register 'USB_PHY_UTMI_REG_14'. */
void GH_USB_PHY_set_UTMI_REG_14_slew(U8 data);
/*! \brief Reads the bit group 'slew' of register 'USB_PHY_UTMI_REG_14'. */
U8   GH_USB_PHY_get_UTMI_REG_14_slew(void);
/*! \brief Writes the bit group 'Disable' of register 'USB_PHY_UTMI_REG_14'. */
void GH_USB_PHY_set_UTMI_REG_14_Disable(U8 data);
/*! \brief Reads the bit group 'Disable' of register 'USB_PHY_UTMI_REG_14'. */
U8   GH_USB_PHY_get_UTMI_REG_14_Disable(void);
/*! \brief Writes the bit group 'test_DM' of register 'USB_PHY_UTMI_REG_14'. */
void GH_USB_PHY_set_UTMI_REG_14_test_DM(U8 data);
/*! \brief Reads the bit group 'test_DM' of register 'USB_PHY_UTMI_REG_14'. */
U8   GH_USB_PHY_get_UTMI_REG_14_test_DM(void);
/*! \brief Writes the bit group 'test_DP' of register 'USB_PHY_UTMI_REG_14'. */
void GH_USB_PHY_set_UTMI_REG_14_test_DP(U8 data);
/*! \brief Reads the bit group 'test_DP' of register 'USB_PHY_UTMI_REG_14'. */
U8   GH_USB_PHY_get_UTMI_REG_14_test_DP(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_14(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_14 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_14] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_14(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_14);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_14] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_14_slew_rate(U8 data)
{
    GH_USB_PHY_UTMI_REG_14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_14;
    d.bitc.slew_rate = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_14_slew_rate] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_14_slew_rate(void)
{
    GH_USB_PHY_UTMI_REG_14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_14_slew_rate] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,value);
    #endif
    return tmp_value.bitc.slew_rate;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_14_Hign_speed(U8 data)
{
    GH_USB_PHY_UTMI_REG_14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_14;
    d.bitc.hign_speed = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_14_Hign_speed] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_14_Hign_speed(void)
{
    GH_USB_PHY_UTMI_REG_14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_14_Hign_speed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,value);
    #endif
    return tmp_value.bitc.hign_speed;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_14_Full_speed0(U8 data)
{
    GH_USB_PHY_UTMI_REG_14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_14;
    d.bitc.full_speed0 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_14_Full_speed0] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_14_Full_speed0(void)
{
    GH_USB_PHY_UTMI_REG_14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_14_Full_speed0] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,value);
    #endif
    return tmp_value.bitc.full_speed0;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_14_Full_speed1(U8 data)
{
    GH_USB_PHY_UTMI_REG_14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_14;
    d.bitc.full_speed1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_14_Full_speed1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_14_Full_speed1(void)
{
    GH_USB_PHY_UTMI_REG_14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_14_Full_speed1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,value);
    #endif
    return tmp_value.bitc.full_speed1;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_14_slew(U8 data)
{
    GH_USB_PHY_UTMI_REG_14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_14;
    d.bitc.slew = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_14_slew] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_14_slew(void)
{
    GH_USB_PHY_UTMI_REG_14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_14_slew] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,value);
    #endif
    return tmp_value.bitc.slew;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_14_Disable(U8 data)
{
    GH_USB_PHY_UTMI_REG_14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_14;
    d.bitc.disable = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_14_Disable] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_14_Disable(void)
{
    GH_USB_PHY_UTMI_REG_14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_14_Disable] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,value);
    #endif
    return tmp_value.bitc.disable;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_14_test_DM(U8 data)
{
    GH_USB_PHY_UTMI_REG_14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_14;
    d.bitc.test_dm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_14_test_DM] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_14_test_DM(void)
{
    GH_USB_PHY_UTMI_REG_14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_14_test_DM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,value);
    #endif
    return tmp_value.bitc.test_dm;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_14_test_DP(U8 data)
{
    GH_USB_PHY_UTMI_REG_14_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_14;
    d.bitc.test_dp = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_14 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_14_test_DP] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_14_test_DP(void)
{
    GH_USB_PHY_UTMI_REG_14_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_14);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_14_test_DP] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_14,value);
    #endif
    return tmp_value.bitc.test_dp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_15 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_15'. */
U16  GH_USB_PHY_get_UTMI_REG_15(void);
/*! \brief Writes the bit group 'VSPOUT' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_VSPOUT(U8 data);
/*! \brief Reads the bit group 'VSPOUT' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_VSPOUT(void);
/*! \brief Writes the bit group 'VSMOUT' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_VSMOUT(U8 data);
/*! \brief Reads the bit group 'VSMOUT' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_VSMOUT(void);
/*! \brief Writes the bit group 'VCPOUT' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_VCPOUT(U8 data);
/*! \brief Reads the bit group 'VCPOUT' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_VCPOUT(void);
/*! \brief Writes the bit group 'VCMOUT' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_VCMOUT(U8 data);
/*! \brief Reads the bit group 'VCMOUT' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_VCMOUT(void);
/*! \brief Writes the bit group 'PGD' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_PGD(U8 data);
/*! \brief Reads the bit group 'PGD' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_PGD(void);
/*! \brief Writes the bit group 'Power_Good_33V' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_Power_Good_33V(U8 data);
/*! \brief Reads the bit group 'Power_Good_33V' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_Power_Good_33V(void);
/*! \brief Writes the bit group 'Power_Good' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_Power_Good(U8 data);
/*! \brief Reads the bit group 'Power_Good' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_Power_Good(void);
/*! \brief Writes the bit group 'VBG' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_VBG(U8 data);
/*! \brief Reads the bit group 'VBG' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_VBG(void);
/*! \brief Writes the bit group 'VBGR' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_VBGR(U8 data);
/*! \brief Reads the bit group 'VBGR' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_VBGR(void);
/*! \brief Writes the bit group 'Power_Good_POR' of register 'USB_PHY_UTMI_REG_15'. */
void GH_USB_PHY_set_UTMI_REG_15_Power_Good_POR(U8 data);
/*! \brief Reads the bit group 'Power_Good_POR' of register 'USB_PHY_UTMI_REG_15'. */
U8   GH_USB_PHY_get_UTMI_REG_15_Power_Good_POR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_15(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_VSPOUT(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.vspout = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_VSPOUT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_VSPOUT(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_VSPOUT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.vspout;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_VSMOUT(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.vsmout = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_VSMOUT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_VSMOUT(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_VSMOUT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.vsmout;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_VCPOUT(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.vcpout = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_VCPOUT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_VCPOUT(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_VCPOUT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.vcpout;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_VCMOUT(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.vcmout = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_VCMOUT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_VCMOUT(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_VCMOUT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.vcmout;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_PGD(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.pgd = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_PGD] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_PGD(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_PGD] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.pgd;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_Power_Good_33V(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.power_good_33v = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_Power_Good_33V] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_Power_Good_33V(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_Power_Good_33V] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.power_good_33v;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_Power_Good(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.power_good = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_Power_Good] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_Power_Good(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_Power_Good] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.power_good;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_VBG(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.vbg = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_VBG] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_VBG(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_VBG] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.vbg;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_VBGR(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.vbgr = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_VBGR] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_VBGR(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_VBGR] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.vbgr;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_15_Power_Good_POR(U8 data)
{
    GH_USB_PHY_UTMI_REG_15_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_15;
    d.bitc.power_good_por = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_15 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_15_Power_Good_POR] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_15_Power_Good_POR(void)
{
    GH_USB_PHY_UTMI_REG_15_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_15);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_15_Power_Good_POR] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_15,value);
    #endif
    return tmp_value.bitc.power_good_por;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_16 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_16'. */
void GH_USB_PHY_set_UTMI_REG_16(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_16'. */
U16  GH_USB_PHY_get_UTMI_REG_16(void);
/*! \brief Writes the bit group 'TX_text_clock' of register 'USB_PHY_UTMI_REG_16'. */
void GH_USB_PHY_set_UTMI_REG_16_TX_text_clock(U8 data);
/*! \brief Reads the bit group 'TX_text_clock' of register 'USB_PHY_UTMI_REG_16'. */
U8   GH_USB_PHY_get_UTMI_REG_16_TX_text_clock(void);
/*! \brief Writes the bit group 'TX_output_adjust' of register 'USB_PHY_UTMI_REG_16'. */
void GH_USB_PHY_set_UTMI_REG_16_TX_output_adjust(U8 data);
/*! \brief Reads the bit group 'TX_output_adjust' of register 'USB_PHY_UTMI_REG_16'. */
U8   GH_USB_PHY_get_UTMI_REG_16_TX_output_adjust(void);
/*! \brief Writes the bit group 'TX_pre_emphasis_adjust' of register 'USB_PHY_UTMI_REG_16'. */
void GH_USB_PHY_set_UTMI_REG_16_TX_pre_emphasis_adjust(U8 data);
/*! \brief Reads the bit group 'TX_pre_emphasis_adjust' of register 'USB_PHY_UTMI_REG_16'. */
U8   GH_USB_PHY_get_UTMI_REG_16_TX_pre_emphasis_adjust(void);
/*! \brief Writes the bit group 'TX_pre_emphasis_bias' of register 'USB_PHY_UTMI_REG_16'. */
void GH_USB_PHY_set_UTMI_REG_16_TX_pre_emphasis_bias(U8 data);
/*! \brief Reads the bit group 'TX_pre_emphasis_bias' of register 'USB_PHY_UTMI_REG_16'. */
U8   GH_USB_PHY_get_UTMI_REG_16_TX_pre_emphasis_bias(void);
/*! \brief Writes the bit group 'TX_current_bias' of register 'USB_PHY_UTMI_REG_16'. */
void GH_USB_PHY_set_UTMI_REG_16_TX_current_bias(U8 data);
/*! \brief Reads the bit group 'TX_current_bias' of register 'USB_PHY_UTMI_REG_16'. */
U8   GH_USB_PHY_get_UTMI_REG_16_TX_current_bias(void);
/*! \brief Writes the bit group 'HS_RTERM' of register 'USB_PHY_UTMI_REG_16'. */
void GH_USB_PHY_set_UTMI_REG_16_HS_RTERM(U8 data);
/*! \brief Reads the bit group 'HS_RTERM' of register 'USB_PHY_UTMI_REG_16'. */
U8   GH_USB_PHY_get_UTMI_REG_16_HS_RTERM(void);
/*! \brief Writes the bit group 'HS_TX' of register 'USB_PHY_UTMI_REG_16'. */
void GH_USB_PHY_set_UTMI_REG_16_HS_TX(U8 data);
/*! \brief Reads the bit group 'HS_TX' of register 'USB_PHY_UTMI_REG_16'. */
U8   GH_USB_PHY_get_UTMI_REG_16_HS_TX(void);
/*! \brief Writes the bit group 'VBUSDET_NC' of register 'USB_PHY_UTMI_REG_16'. */
void GH_USB_PHY_set_UTMI_REG_16_VBUSDET_NC(U8 data);
/*! \brief Reads the bit group 'VBUSDET_NC' of register 'USB_PHY_UTMI_REG_16'. */
U8   GH_USB_PHY_get_UTMI_REG_16_VBUSDET_NC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_16(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_16 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_16] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_16(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_16);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_16] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_16_TX_text_clock(U8 data)
{
    GH_USB_PHY_UTMI_REG_16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_16;
    d.bitc.tx_text_clock = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_16_TX_text_clock] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_16_TX_text_clock(void)
{
    GH_USB_PHY_UTMI_REG_16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_16_TX_text_clock] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,value);
    #endif
    return tmp_value.bitc.tx_text_clock;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_16_TX_output_adjust(U8 data)
{
    GH_USB_PHY_UTMI_REG_16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_16;
    d.bitc.tx_output_adjust = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_16_TX_output_adjust] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_16_TX_output_adjust(void)
{
    GH_USB_PHY_UTMI_REG_16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_16_TX_output_adjust] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,value);
    #endif
    return tmp_value.bitc.tx_output_adjust;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_16_TX_pre_emphasis_adjust(U8 data)
{
    GH_USB_PHY_UTMI_REG_16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_16;
    d.bitc.tx_pre_emphasis_adjust = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_16_TX_pre_emphasis_adjust] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_16_TX_pre_emphasis_adjust(void)
{
    GH_USB_PHY_UTMI_REG_16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_16_TX_pre_emphasis_adjust] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,value);
    #endif
    return tmp_value.bitc.tx_pre_emphasis_adjust;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_16_TX_pre_emphasis_bias(U8 data)
{
    GH_USB_PHY_UTMI_REG_16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_16;
    d.bitc.tx_pre_emphasis_bias = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_16_TX_pre_emphasis_bias] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_16_TX_pre_emphasis_bias(void)
{
    GH_USB_PHY_UTMI_REG_16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_16_TX_pre_emphasis_bias] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,value);
    #endif
    return tmp_value.bitc.tx_pre_emphasis_bias;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_16_TX_current_bias(U8 data)
{
    GH_USB_PHY_UTMI_REG_16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_16;
    d.bitc.tx_current_bias = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_16_TX_current_bias] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_16_TX_current_bias(void)
{
    GH_USB_PHY_UTMI_REG_16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_16_TX_current_bias] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,value);
    #endif
    return tmp_value.bitc.tx_current_bias;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_16_HS_RTERM(U8 data)
{
    GH_USB_PHY_UTMI_REG_16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_16;
    d.bitc.hs_rterm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_16_HS_RTERM] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_16_HS_RTERM(void)
{
    GH_USB_PHY_UTMI_REG_16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_16_HS_RTERM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,value);
    #endif
    return tmp_value.bitc.hs_rterm;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_16_HS_TX(U8 data)
{
    GH_USB_PHY_UTMI_REG_16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_16;
    d.bitc.hs_tx = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_16_HS_TX] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_16_HS_TX(void)
{
    GH_USB_PHY_UTMI_REG_16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_16_HS_TX] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,value);
    #endif
    return tmp_value.bitc.hs_tx;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_16_VBUSDET_NC(U8 data)
{
    GH_USB_PHY_UTMI_REG_16_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_16;
    d.bitc.vbusdet_nc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_16 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_16_VBUSDET_NC] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_16_VBUSDET_NC(void)
{
    GH_USB_PHY_UTMI_REG_16_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_16);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_16_VBUSDET_NC] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_16,value);
    #endif
    return tmp_value.bitc.vbusdet_nc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_17 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_17'. */
U16  GH_USB_PHY_get_UTMI_REG_17(void);
/*! \brief Writes the bit group 'HS_RX' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_HS_RX(U8 data);
/*! \brief Reads the bit group 'HS_RX' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_HS_RX(void);
/*! \brief Writes the bit group 'RTERM' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_RTERM(U8 data);
/*! \brief Reads the bit group 'RTERM' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_RTERM(void);
/*! \brief Writes the bit group 'HS_RTERM' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_HS_RTERM(U8 data);
/*! \brief Reads the bit group 'HS_RTERM' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_HS_RTERM(void);
/*! \brief Writes the bit group 'HS_TX_ITEST' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_HS_TX_ITEST(U8 data);
/*! \brief Reads the bit group 'HS_TX_ITEST' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_HS_TX_ITEST(void);
/*! \brief Writes the bit group 'Mute' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_Mute(U8 data);
/*! \brief Reads the bit group 'Mute' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_Mute(void);
/*! \brief Writes the bit group 'pre_emphasis_en' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_pre_emphasis_en(U8 data);
/*! \brief Reads the bit group 'pre_emphasis_en' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_pre_emphasis_en(void);
/*! \brief Writes the bit group 'transition_edge' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_transition_edge(U8 data);
/*! \brief Reads the bit group 'transition_edge' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_transition_edge(void);
/*! \brief Writes the bit group 'enable_edge' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_enable_edge(U8 data);
/*! \brief Reads the bit group 'enable_edge' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_enable_edge(void);
/*! \brief Writes the bit group 'clock_output' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_clock_output(U8 data);
/*! \brief Reads the bit group 'clock_output' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_clock_output(void);
/*! \brief Writes the bit group 'source' of register 'USB_PHY_UTMI_REG_17'. */
void GH_USB_PHY_set_UTMI_REG_17_source(U8 data);
/*! \brief Reads the bit group 'source' of register 'USB_PHY_UTMI_REG_17'. */
U8   GH_USB_PHY_get_UTMI_REG_17_source(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_17(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_HS_RX(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.hs_rx = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_HS_RX] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_HS_RX(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_HS_RX] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.hs_rx;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_RTERM(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.rterm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_RTERM] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_RTERM(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_RTERM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.rterm;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_HS_RTERM(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.hs_rterm = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_HS_RTERM] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_HS_RTERM(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_HS_RTERM] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.hs_rterm;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_HS_TX_ITEST(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.hs_tx_itest = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_HS_TX_ITEST] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_HS_TX_ITEST(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_HS_TX_ITEST] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.hs_tx_itest;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_Mute(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.mute = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_Mute] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_Mute(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_Mute] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.mute;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_pre_emphasis_en(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.pre_emphasis_en = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_pre_emphasis_en] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_pre_emphasis_en(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_pre_emphasis_en] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.pre_emphasis_en;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_transition_edge(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.transition_edge = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_transition_edge] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_transition_edge(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_transition_edge] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.transition_edge;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_enable_edge(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.enable_edge = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_enable_edge] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_enable_edge(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_enable_edge] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.enable_edge;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_clock_output(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.clock_output = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_clock_output] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_clock_output(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_clock_output] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.clock_output;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_17_source(U8 data)
{
    GH_USB_PHY_UTMI_REG_17_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_17;
    d.bitc.source = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_17 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_17_source] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_17_source(void)
{
    GH_USB_PHY_UTMI_REG_17_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_17);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_17_source] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_17,value);
    #endif
    return tmp_value.bitc.source;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_18 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_18'. */
U16  GH_USB_PHY_get_UTMI_REG_18(void);
/*! \brief Writes the bit group 'lock' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_lock(U8 data);
/*! \brief Reads the bit group 'lock' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_lock(void);
/*! \brief Writes the bit group 'flag1' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_flag1(U8 data);
/*! \brief Reads the bit group 'flag1' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_flag1(void);
/*! \brief Writes the bit group 'flag2' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_flag2(U8 data);
/*! \brief Reads the bit group 'flag2' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_flag2(void);
/*! \brief Writes the bit group 'test' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_test(U8 data);
/*! \brief Reads the bit group 'test' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_test(void);
/*! \brief Writes the bit group 'Power_good' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_Power_good(U8 data);
/*! \brief Reads the bit group 'Power_good' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_Power_good(void);
/*! \brief Writes the bit group 'Vbus' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_Vbus(U8 data);
/*! \brief Reads the bit group 'Vbus' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_Vbus(void);
/*! \brief Writes the bit group 'OTG' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_OTG(U8 data);
/*! \brief Reads the bit group 'OTG' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_OTG(void);
/*! \brief Writes the bit group 'CID' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_CID(U8 data);
/*! \brief Reads the bit group 'CID' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_CID(void);
/*! \brief Writes the bit group 'AVALID_ATOP' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_AVALID_ATOP(U8 data);
/*! \brief Reads the bit group 'AVALID_ATOP' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_AVALID_ATOP(void);
/*! \brief Writes the bit group 'HS_DISCONNECT' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_HS_DISCONNECT(U8 data);
/*! \brief Reads the bit group 'HS_DISCONNECT' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_HS_DISCONNECT(void);
/*! \brief Writes the bit group 'HS_RX_DATA' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_HS_RX_DATA(U8 data);
/*! \brief Reads the bit group 'HS_RX_DATA' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_HS_RX_DATA(void);
/*! \brief Writes the bit group 'HS_RX_CHIRP' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_HS_RX_CHIRP(U8 data);
/*! \brief Reads the bit group 'HS_RX_CHIRP' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_HS_RX_CHIRP(void);
/*! \brief Writes the bit group 'FL_LINESTATE0' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_FL_LINESTATE0(U8 data);
/*! \brief Reads the bit group 'FL_LINESTATE0' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_FL_LINESTATE0(void);
/*! \brief Writes the bit group 'FL_LINESTATE1' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_FL_LINESTATE1(U8 data);
/*! \brief Reads the bit group 'FL_LINESTATE1' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_FL_LINESTATE1(void);
/*! \brief Writes the bit group 'failed' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_failed(U8 data);
/*! \brief Reads the bit group 'failed' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_failed(void);
/*! \brief Writes the bit group 'finish' of register 'USB_PHY_UTMI_REG_18'. */
void GH_USB_PHY_set_UTMI_REG_18_finish(U8 data);
/*! \brief Reads the bit group 'finish' of register 'USB_PHY_UTMI_REG_18'. */
U8   GH_USB_PHY_get_UTMI_REG_18_finish(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_18(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_lock(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.lock = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_lock] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_lock(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_lock] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.lock;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_flag1(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.flag1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_flag1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_flag1(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_flag1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.flag1;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_flag2(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.flag2 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_flag2] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_flag2(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_flag2] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.flag2;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_test(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_test(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.test;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_Power_good(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.power_good = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_Power_good] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_Power_good(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_Power_good] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.power_good;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_Vbus(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.vbus = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_Vbus] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_Vbus(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_Vbus] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.vbus;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_OTG(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.otg = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_OTG] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_OTG(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_OTG] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.otg;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_CID(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.cid = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_CID] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_CID(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_CID] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.cid;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_AVALID_ATOP(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.avalid_atop = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_AVALID_ATOP] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_AVALID_ATOP(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_AVALID_ATOP] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.avalid_atop;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_HS_DISCONNECT(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.hs_disconnect = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_HS_DISCONNECT] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_HS_DISCONNECT(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_HS_DISCONNECT] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.hs_disconnect;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_HS_RX_DATA(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.hs_rx_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_HS_RX_DATA] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_HS_RX_DATA(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_HS_RX_DATA] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.hs_rx_data;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_HS_RX_CHIRP(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.hs_rx_chirp = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_HS_RX_CHIRP] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_HS_RX_CHIRP(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_HS_RX_CHIRP] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.hs_rx_chirp;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_FL_LINESTATE0(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.fl_linestate0 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_FL_LINESTATE0] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_FL_LINESTATE0(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_FL_LINESTATE0] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.fl_linestate0;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_FL_LINESTATE1(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.fl_linestate1 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_FL_LINESTATE1] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_FL_LINESTATE1(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_FL_LINESTATE1] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.fl_linestate1;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_failed(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.failed = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_failed] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_failed(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_failed] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.failed;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_18_finish(U8 data)
{
    GH_USB_PHY_UTMI_REG_18_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_18;
    d.bitc.finish = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_18 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_18_finish] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_18_finish(void)
{
    GH_USB_PHY_UTMI_REG_18_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_18);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_18_finish] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_18,value);
    #endif
    return tmp_value.bitc.finish;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_19 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_19'. */
void GH_USB_PHY_set_UTMI_REG_19(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_19'. */
U16  GH_USB_PHY_get_UTMI_REG_19(void);
/*! \brief Writes the bit group 'pg_tx_length' of register 'USB_PHY_UTMI_REG_19'. */
void GH_USB_PHY_set_UTMI_REG_19_pg_tx_length(U8 data);
/*! \brief Reads the bit group 'pg_tx_length' of register 'USB_PHY_UTMI_REG_19'. */
U8   GH_USB_PHY_get_UTMI_REG_19_pg_tx_length(void);
/*! \brief Writes the bit group 'pg_tx_go' of register 'USB_PHY_UTMI_REG_19'. */
void GH_USB_PHY_set_UTMI_REG_19_pg_tx_go(U8 data);
/*! \brief Reads the bit group 'pg_tx_go' of register 'USB_PHY_UTMI_REG_19'. */
U8   GH_USB_PHY_get_UTMI_REG_19_pg_tx_go(void);
/*! \brief Writes the bit group 'pg_tx_mode' of register 'USB_PHY_UTMI_REG_19'. */
void GH_USB_PHY_set_UTMI_REG_19_pg_tx_mode(U8 data);
/*! \brief Reads the bit group 'pg_tx_mode' of register 'USB_PHY_UTMI_REG_19'. */
U8   GH_USB_PHY_get_UTMI_REG_19_pg_tx_mode(void);
/*! \brief Writes the bit group 'pg_tx_fixed_data' of register 'USB_PHY_UTMI_REG_19'. */
void GH_USB_PHY_set_UTMI_REG_19_pg_tx_fixed_data(U8 data);
/*! \brief Reads the bit group 'pg_tx_fixed_data' of register 'USB_PHY_UTMI_REG_19'. */
U8   GH_USB_PHY_get_UTMI_REG_19_pg_tx_fixed_data(void);
/*! \brief Writes the bit group 'continuous_mode' of register 'USB_PHY_UTMI_REG_19'. */
void GH_USB_PHY_set_UTMI_REG_19_continuous_mode(U8 data);
/*! \brief Reads the bit group 'continuous_mode' of register 'USB_PHY_UTMI_REG_19'. */
U8   GH_USB_PHY_get_UTMI_REG_19_continuous_mode(void);
/*! \brief Writes the bit group 'receiving_mode' of register 'USB_PHY_UTMI_REG_19'. */
void GH_USB_PHY_set_UTMI_REG_19_receiving_mode(U8 data);
/*! \brief Reads the bit group 'receiving_mode' of register 'USB_PHY_UTMI_REG_19'. */
U8   GH_USB_PHY_get_UTMI_REG_19_receiving_mode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_19(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_19 = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_19] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_19(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_19);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_19] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_19_pg_tx_length(U8 data)
{
    GH_USB_PHY_UTMI_REG_19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_19;
    d.bitc.pg_tx_length = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_19_pg_tx_length] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_19_pg_tx_length(void)
{
    GH_USB_PHY_UTMI_REG_19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_19_pg_tx_length] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,value);
    #endif
    return tmp_value.bitc.pg_tx_length;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_19_pg_tx_go(U8 data)
{
    GH_USB_PHY_UTMI_REG_19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_19;
    d.bitc.pg_tx_go = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_19_pg_tx_go] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_19_pg_tx_go(void)
{
    GH_USB_PHY_UTMI_REG_19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_19_pg_tx_go] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,value);
    #endif
    return tmp_value.bitc.pg_tx_go;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_19_pg_tx_mode(U8 data)
{
    GH_USB_PHY_UTMI_REG_19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_19;
    d.bitc.pg_tx_mode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_19_pg_tx_mode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_19_pg_tx_mode(void)
{
    GH_USB_PHY_UTMI_REG_19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_19_pg_tx_mode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,value);
    #endif
    return tmp_value.bitc.pg_tx_mode;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_19_pg_tx_fixed_data(U8 data)
{
    GH_USB_PHY_UTMI_REG_19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_19;
    d.bitc.pg_tx_fixed_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_19_pg_tx_fixed_data] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_19_pg_tx_fixed_data(void)
{
    GH_USB_PHY_UTMI_REG_19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_19_pg_tx_fixed_data] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,value);
    #endif
    return tmp_value.bitc.pg_tx_fixed_data;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_19_continuous_mode(U8 data)
{
    GH_USB_PHY_UTMI_REG_19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_19;
    d.bitc.continuous_mode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_19_continuous_mode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_19_continuous_mode(void)
{
    GH_USB_PHY_UTMI_REG_19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_19_continuous_mode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,value);
    #endif
    return tmp_value.bitc.continuous_mode;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_19_receiving_mode(U8 data)
{
    GH_USB_PHY_UTMI_REG_19_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_19;
    d.bitc.receiving_mode = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_19 = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_19_receiving_mode] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_19_receiving_mode(void)
{
    GH_USB_PHY_UTMI_REG_19_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_19);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_19_receiving_mode] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_19,value);
    #endif
    return tmp_value.bitc.receiving_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_1A (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_1A'. */
void GH_USB_PHY_set_UTMI_REG_1A(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_1A'. */
U16  GH_USB_PHY_get_UTMI_REG_1A(void);
/*! \brief Writes the bit group 'pg_tx_data' of register 'USB_PHY_UTMI_REG_1A'. */
void GH_USB_PHY_set_UTMI_REG_1A_pg_tx_data(U16 data);
/*! \brief Reads the bit group 'pg_tx_data' of register 'USB_PHY_UTMI_REG_1A'. */
U16  GH_USB_PHY_get_UTMI_REG_1A_pg_tx_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1A(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1A = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1A] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1A,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_1A(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1A);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1A] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1A,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1A_pg_tx_data(U16 data)
{
    GH_USB_PHY_UTMI_REG_1A_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1A;
    d.bitc.pg_tx_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1A = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1A_pg_tx_data] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1A,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_1A_pg_tx_data(void)
{
    GH_USB_PHY_UTMI_REG_1A_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1A);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1A_pg_tx_data] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1A,value);
    #endif
    return tmp_value.bitc.pg_tx_data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_1B (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_1B'. */
void GH_USB_PHY_set_UTMI_REG_1B(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_1B'. */
U16  GH_USB_PHY_get_UTMI_REG_1B(void);
/*! \brief Writes the bit group 'pg_tx_inc' of register 'USB_PHY_UTMI_REG_1B'. */
void GH_USB_PHY_set_UTMI_REG_1B_pg_tx_inc(U16 data);
/*! \brief Reads the bit group 'pg_tx_inc' of register 'USB_PHY_UTMI_REG_1B'. */
U16  GH_USB_PHY_get_UTMI_REG_1B_pg_tx_inc(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1B(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1B = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1B] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1B,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_1B(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1B);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1B] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1B,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1B_pg_tx_inc(U16 data)
{
    GH_USB_PHY_UTMI_REG_1B_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1B;
    d.bitc.pg_tx_inc = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1B = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1B_pg_tx_inc] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1B,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_1B_pg_tx_inc(void)
{
    GH_USB_PHY_UTMI_REG_1B_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1B);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1B_pg_tx_inc] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1B,value);
    #endif
    return tmp_value.bitc.pg_tx_inc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_1C (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_1C'. */
U16  GH_USB_PHY_get_UTMI_REG_1C(void);
/*! \brief Writes the bit group 'en_ck192' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_en_ck192(U8 data);
/*! \brief Reads the bit group 'en_ck192' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_en_ck192(void);
/*! \brief Writes the bit group 'vigen_pdn' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_vigen_pdn(U8 data);
/*! \brief Reads the bit group 'vigen_pdn' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_vigen_pdn(void);
/*! \brief Writes the bit group 'selport' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_selport(U8 data);
/*! \brief Reads the bit group 'selport' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_selport(void);
/*! \brief Writes the bit group 'dp_status' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_dp_status(U8 data);
/*! \brief Reads the bit group 'dp_status' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_dp_status(void);
/*! \brief Writes the bit group 'dm_status' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_dm_status(U8 data);
/*! \brief Reads the bit group 'dm_status' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_dm_status(void);
/*! \brief Writes the bit group 'dp1_status' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_dp1_status(U8 data);
/*! \brief Reads the bit group 'dp1_status' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_dp1_status(void);
/*! \brief Writes the bit group 'dm1_status' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_dm1_status(U8 data);
/*! \brief Reads the bit group 'dm1_status' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_dm1_status(void);
/*! \brief Writes the bit group 'asrst_on' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_asrst_on(U8 data);
/*! \brief Reads the bit group 'asrst_on' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_asrst_on(void);
/*! \brief Writes the bit group 'VBUS' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_VBUS(U8 data);
/*! \brief Reads the bit group 'VBUS' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_VBUS(void);
/*! \brief Writes the bit group 'dummy' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_dummy(U8 data);
/*! \brief Reads the bit group 'dummy' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_dummy(void);
/*! \brief Writes the bit group 'reserved' of register 'USB_PHY_UTMI_REG_1C'. */
void GH_USB_PHY_set_UTMI_REG_1C_reserved(U8 data);
/*! \brief Reads the bit group 'reserved' of register 'USB_PHY_UTMI_REG_1C'. */
U8   GH_USB_PHY_get_UTMI_REG_1C_reserved(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_1C(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_en_ck192(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.en_ck192 = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_en_ck192] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_en_ck192(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_en_ck192] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.en_ck192;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_vigen_pdn(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.vigen_pdn = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_vigen_pdn] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_vigen_pdn(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_vigen_pdn] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.vigen_pdn;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_selport(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.selport = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_selport] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_selport(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_selport] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.selport;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_dp_status(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.dp_status = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_dp_status] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_dp_status(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_dp_status] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.dp_status;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_dm_status(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.dm_status = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_dm_status] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_dm_status(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_dm_status] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.dm_status;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_dp1_status(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.dp1_status = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_dp1_status] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_dp1_status(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_dp1_status] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.dp1_status;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_dm1_status(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.dm1_status = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_dm1_status] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_dm1_status(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_dm1_status] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.dm1_status;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_asrst_on(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.asrst_on = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_asrst_on] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_asrst_on(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_asrst_on] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.asrst_on;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_VBUS(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.vbus = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_VBUS] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_VBUS(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_VBUS] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.vbus;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_dummy(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.dummy = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_dummy] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_dummy(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_dummy] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.dummy;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1C_reserved(U8 data)
{
    GH_USB_PHY_UTMI_REG_1C_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C;
    d.bitc.reserved = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1C = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1C_reserved] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1C_reserved(void)
{
    GH_USB_PHY_UTMI_REG_1C_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1C);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1C_reserved] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1C,value);
    #endif
    return tmp_value.bitc.reserved;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_1D (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_1D'. */
void GH_USB_PHY_set_UTMI_REG_1D(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_1D'. */
U16  GH_USB_PHY_get_UTMI_REG_1D(void);
/*! \brief Writes the bit group 'test_serdes' of register 'USB_PHY_UTMI_REG_1D'. */
void GH_USB_PHY_set_UTMI_REG_1D_test_serdes(U8 data);
/*! \brief Reads the bit group 'test_serdes' of register 'USB_PHY_UTMI_REG_1D'. */
U8   GH_USB_PHY_get_UTMI_REG_1D_test_serdes(void);
/*! \brief Writes the bit group 'reg_test' of register 'USB_PHY_UTMI_REG_1D'. */
void GH_USB_PHY_set_UTMI_REG_1D_reg_test(U8 data);
/*! \brief Reads the bit group 'reg_test' of register 'USB_PHY_UTMI_REG_1D'. */
U8   GH_USB_PHY_get_UTMI_REG_1D_reg_test(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1D(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1D = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1D] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1D,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_1D(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1D);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1D] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1D,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1D_test_serdes(U8 data)
{
    GH_USB_PHY_UTMI_REG_1D_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1D;
    d.bitc.test_serdes = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1D = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1D_test_serdes] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1D,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1D_test_serdes(void)
{
    GH_USB_PHY_UTMI_REG_1D_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1D);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1D_test_serdes] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1D,value);
    #endif
    return tmp_value.bitc.test_serdes;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1D_reg_test(U8 data)
{
    GH_USB_PHY_UTMI_REG_1D_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1D;
    d.bitc.reg_test = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1D = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1D_reg_test] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1D,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1D_reg_test(void)
{
    GH_USB_PHY_UTMI_REG_1D_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1D);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1D_reg_test] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1D,value);
    #endif
    return tmp_value.bitc.reg_test;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register USB_PHY_UTMI_REG_1E (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'USB_PHY_UTMI_REG_1E'. */
void GH_USB_PHY_set_UTMI_REG_1E(U16 data);
/*! \brief Reads the register 'USB_PHY_UTMI_REG_1E'. */
U16  GH_USB_PHY_get_UTMI_REG_1E(void);
/*! \brief Writes the bit group 'ca_start' of register 'USB_PHY_UTMI_REG_1E'. */
void GH_USB_PHY_set_UTMI_REG_1E_ca_start(U8 data);
/*! \brief Reads the bit group 'ca_start' of register 'USB_PHY_UTMI_REG_1E'. */
U8   GH_USB_PHY_get_UTMI_REG_1E_ca_start(void);
/*! \brief Writes the bit group 'ca_end' of register 'USB_PHY_UTMI_REG_1E'. */
void GH_USB_PHY_set_UTMI_REG_1E_ca_end(U8 data);
/*! \brief Reads the bit group 'ca_end' of register 'USB_PHY_UTMI_REG_1E'. */
U8   GH_USB_PHY_get_UTMI_REG_1E_ca_end(void);
/*! \brief Writes the bit group 'power_good_sts' of register 'USB_PHY_UTMI_REG_1E'. */
void GH_USB_PHY_set_UTMI_REG_1E_power_good_sts(U8 data);
/*! \brief Reads the bit group 'power_good_sts' of register 'USB_PHY_UTMI_REG_1E'. */
U8   GH_USB_PHY_get_UTMI_REG_1E_power_good_sts(void);
/*! \brief Writes the bit group 'ca_data' of register 'USB_PHY_UTMI_REG_1E'. */
void GH_USB_PHY_set_UTMI_REG_1E_ca_data(U16 data);
/*! \brief Reads the bit group 'ca_data' of register 'USB_PHY_UTMI_REG_1E'. */
U16  GH_USB_PHY_get_UTMI_REG_1E_ca_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1E(U16 data)
{
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1E = data;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1E] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,data,data);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_1E(void)
{
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1E);

    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1E] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,value);
    #endif
    return value;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1E_ca_start(U8 data)
{
    GH_USB_PHY_UTMI_REG_1E_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1E;
    d.bitc.ca_start = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1E = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1E_ca_start] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1E_ca_start(void)
{
    GH_USB_PHY_UTMI_REG_1E_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1E);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1E_ca_start] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,value);
    #endif
    return tmp_value.bitc.ca_start;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1E_ca_end(U8 data)
{
    GH_USB_PHY_UTMI_REG_1E_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1E;
    d.bitc.ca_end = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1E = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1E_ca_end] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1E_ca_end(void)
{
    GH_USB_PHY_UTMI_REG_1E_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1E);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1E_ca_end] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,value);
    #endif
    return tmp_value.bitc.ca_end;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1E_power_good_sts(U8 data)
{
    GH_USB_PHY_UTMI_REG_1E_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1E;
    d.bitc.power_good_sts = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1E = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1E_power_good_sts] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_USB_PHY_get_UTMI_REG_1E_power_good_sts(void)
{
    GH_USB_PHY_UTMI_REG_1E_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1E);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1E_power_good_sts] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,value);
    #endif
    return tmp_value.bitc.power_good_sts;
}
GH_INLINE void GH_USB_PHY_set_UTMI_REG_1E_ca_data(U16 data)
{
    GH_USB_PHY_UTMI_REG_1E_S d;
    d.all = *(volatile U16 *)REG_USB_PHY_UTMI_REG_1E;
    d.bitc.ca_data = data;
    *(volatile U16 *)REG_USB_PHY_UTMI_REG_1E = d.all;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_USB_PHY_set_UTMI_REG_1E_ca_data] <-- 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_USB_PHY_get_UTMI_REG_1E_ca_data(void)
{
    GH_USB_PHY_UTMI_REG_1E_S tmp_value;
    U16 value = (*(volatile U16 *)REG_USB_PHY_UTMI_REG_1E);

    tmp_value.all = value;
    #if GH_USB_PHY_ENABLE_DEBUG_PRINT
    GH_USB_PHY_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_USB_PHY_get_UTMI_REG_1E_ca_data] --> 0x%08x\n",
                        REG_USB_PHY_UTMI_REG_1E,value);
    #endif
    return tmp_value.bitc.ca_data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_USB_PHY_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_USB_PHY_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

