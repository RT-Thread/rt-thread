/******************************************************************************
**
** \file      gh_vo_dve.c
**
** \brief     Digital Video Effect.
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
#include "gh_vo_dve.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_DVE_PHASE_INC_B0_REAL                        FIO_ADDRESS(VO_DVE,0x60008080) /* read/write */
#define REG_VO_DVE_PHASE_INC_B1_REAL                        FIO_ADDRESS(VO_DVE,0x60008084) /* read/write */
#define REG_VO_DVE_PHASE_INC_B2_REAL                        FIO_ADDRESS(VO_DVE,0x60008088) /* read/write */
#define REG_VO_DVE_PHASE_INC_B3_REAL                        FIO_ADDRESS(VO_DVE,0x6000808C) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B0_REAL                     FIO_ADDRESS(VO_DVE,0x60008090) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B1_REAL                     FIO_ADDRESS(VO_DVE,0x60008094) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B2_REAL                     FIO_ADDRESS(VO_DVE,0x60008098) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B3_REAL                     FIO_ADDRESS(VO_DVE,0x6000809C) /* read/write */
#define REG_VO_DVE_CNFG_F_REAL                              FIO_ADDRESS(VO_DVE,0x600080A0) /* read/write */
#define REG_VO_DVE_BLACK_LVL_REAL                           FIO_ADDRESS(VO_DVE,0x600080A8) /* read/write */
#define REG_VO_DVE_BLANK_LVL_REAL                           FIO_ADDRESS(VO_DVE,0x600080AC) /* read/write */
#define REG_VO_DVE_CLAMP_LVL_REAL                           FIO_ADDRESS(VO_DVE,0x600080B0) /* read/write */
#define REG_VO_DVE_SYNC_LVL_REAL                            FIO_ADDRESS(VO_DVE,0x600080B4) /* read/write */
#define REG_VO_DVE_CNFG_Y_REAL                              FIO_ADDRESS(VO_DVE,0x600080B8) /* read/write */
#define REG_VO_DVE_CNFG_O_REAL                              FIO_ADDRESS(VO_DVE,0x600080BC) /* read/write */
#define REG_VO_DVE_NBA_REAL                                 FIO_ADDRESS(VO_DVE,0x600080C8) /* read/write */
#define REG_VO_DVE_PBA_REAL                                 FIO_ADDRESS(VO_DVE,0x600080CC) /* read/write */
#define REG_VO_DVE_CNFG_C_REAL                              FIO_ADDRESS(VO_DVE,0x600080D0) /* read/write */
#define REG_VO_DVE_INOUT_MODE_REAL                          FIO_ADDRESS(VO_DVE,0x600080E0) /* read/write */
#define REG_VO_DVE_INPUT_SEL_REAL                           FIO_ADDRESS(VO_DVE,0x600080E4) /* read/write */
#define REG_VO_DVE_VSYNC_OFF_REAL                           FIO_ADDRESS(VO_DVE,0x600080E8) /* read/write */
#define REG_VO_DVE_HSYNC_OFF_H_REAL                         FIO_ADDRESS(VO_DVE,0x600080EC) /* read/write */
#define REG_VO_DVE_HSYNC_OFF_L_REAL                         FIO_ADDRESS(VO_DVE,0x600080F0) /* read/write */
#define REG_VO_DVE_HLINE_LNGTH_H_REAL                       FIO_ADDRESS(VO_DVE,0x600080F4) /* read/write */
#define REG_VO_DVE_HLINE_LNGTH_L_REAL                       FIO_ADDRESS(VO_DVE,0x600080F8) /* read/write */
#define REG_VO_DVE_CC_DATA_H_REAL                           FIO_ADDRESS(VO_DVE,0x60008104) /* read/write */
#define REG_VO_DVE_CC_DATA_L_REAL                           FIO_ADDRESS(VO_DVE,0x60008108) /* read/write */
#define REG_VO_DVE_CC_EN_REAL                               FIO_ADDRESS(VO_DVE,0x60008114) /* read/write */
#define REG_VO_DVE_MVP_N0_REAL                              FIO_ADDRESS(VO_DVE,0x60008120) /* read/write */
#define REG_VO_DVE_MVP_N1_REAL                              FIO_ADDRESS(VO_DVE,0x60008124) /* read/write */
#define REG_VO_DVE_MVP_N2_REAL                              FIO_ADDRESS(VO_DVE,0x60008128) /* read/write */
#define REG_VO_DVE_MVP_N3_REAL                              FIO_ADDRESS(VO_DVE,0x6000812C) /* read/write */
#define REG_VO_DVE_MVP_N4_REAL                              FIO_ADDRESS(VO_DVE,0x60008130) /* read/write */
#define REG_VO_DVE_MVP_N567_REAL                            FIO_ADDRESS(VO_DVE,0x60008134) /* read/write */
#define REG_VO_DVE_MVP_N8_REAL                              FIO_ADDRESS(VO_DVE,0x60008138) /* read/write */
#define REG_VO_DVE_MVP_N9_REAL                              FIO_ADDRESS(VO_DVE,0x6000813C) /* read/write */
#define REG_VO_DVE_MVP_N10_REAL                             FIO_ADDRESS(VO_DVE,0x60008140) /* read/write */
#define REG_VO_DVE_MVP_N11_H_REAL                           FIO_ADDRESS(VO_DVE,0x60008144) /* read/write */
#define REG_VO_DVE_MVP_N11_L_REAL                           FIO_ADDRESS(VO_DVE,0x60008148) /* read/write */
#define REG_VO_DVE_MVP_N12_H_REAL                           FIO_ADDRESS(VO_DVE,0x6000814C) /* read/write */
#define REG_VO_DVE_MVP_N12_L_REAL                           FIO_ADDRESS(VO_DVE,0x60008150) /* read/write */
#define REG_VO_DVE_MVP_N13_REAL                             FIO_ADDRESS(VO_DVE,0x60008154) /* read/write */
#define REG_VO_DVE_MVP_N14_REAL                             FIO_ADDRESS(VO_DVE,0x60008158) /* read/write */
#define REG_VO_DVE_MVP_N15_REAL                             FIO_ADDRESS(VO_DVE,0x6000815C) /* read/write */
#define REG_VO_DVE_BURST_ZONE_12_REAL                       FIO_ADDRESS(VO_DVE,0x60008160) /* read/write */
#define REG_VO_DVE_BURST_ZONE_EN_REAL                       FIO_ADDRESS(VO_DVE,0x60008164) /* read/write */
#define REG_VO_DVE_MVP_N21_L_REAL                           FIO_ADDRESS(VO_DVE,0x60008168) /* read/write */
#define REG_VO_DVE_MVP_N21_H_REAL                           FIO_ADDRESS(VO_DVE,0x6000816C) /* read/write */
#define REG_VO_DVE_TEST_F_REAL                              FIO_ADDRESS(VO_DVE,0x60008180) /* read/write */
#define REG_VO_DVE_TEST_YO_REAL                             FIO_ADDRESS(VO_DVE,0x60008184) /* read/write */
#define REG_VO_DVE_TEST_C_REAL                              FIO_ADDRESS(VO_DVE,0x6000818C) /* read/write */
#define REG_VO_DVE_MACV_TEST_REAL                           FIO_ADDRESS(VO_DVE,0x60008190) /* read/write */
#define REG_VO_DVE_HLINE_VRST_H_REAL                        FIO_ADDRESS(VO_DVE,0x600081B4) /* read/write */
#define REG_VO_DVE_HLINE_VRST_L_REAL                        FIO_ADDRESS(VO_DVE,0x600081B8) /* read/write */
#define REG_VO_DVE_VSM_VRST_REAL                            FIO_ADDRESS(VO_DVE,0x600081BC) /* read/write */
#define REG_VO_DVE_SYNC_START_REAL                          FIO_ADDRESS(VO_DVE,0x600081D0) /* read/write */
#define REG_VO_DVE_SYNC_END_REAL                            FIO_ADDRESS(VO_DVE,0x600081D4) /* read/write */
#define REG_VO_DVE_SYNC_SREND_REAL                          FIO_ADDRESS(VO_DVE,0x600081D8) /* read/write */
#define REG_VO_DVE_SYNC_EQEND_REAL                          FIO_ADDRESS(VO_DVE,0x600081DC) /* read/write */
#define REG_VO_DVE_ACTIVE_START_REAL                        FIO_ADDRESS(VO_DVE,0x600081E0) /* read/write */
#define REG_VO_DVE_ACTIVE_END_REAL                          FIO_ADDRESS(VO_DVE,0x600081E4) /* read/write */
#define REG_VO_DVE_WBRST_START_REAL                         FIO_ADDRESS(VO_DVE,0x600081E8) /* read/write */
#define REG_VO_DVE_NBRST_START_REAL                         FIO_ADDRESS(VO_DVE,0x600081EC) /* read/write */
#define REG_VO_DVE_NBRST_END_REAL                           FIO_ADDRESS(VO_DVE,0x600081F0) /* read/write */
#define REG_VO_DVE_CLOSED_CAPTION_REAL                      FIO_ADDRESS(VO_DVE,0x60008200) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_DVE_CNFG_F */
    U8 all;
    struct {
        U8 reset                        : 1;
        U8 config                       : 7;
    } bitc;
} GH_VO_DVE_CNFG_F_REAL_S;

typedef union { /* VO_DVE_CNFG_Y */
    U8 all;
    struct {
        U8 gain                         : 1;
        U8 lpf_select                   : 1;
        U8 delay_config                 : 3;
        U8 colorbar_en                  : 1;
        U8 interpolation_mode           : 2;
    } bitc;
} GH_VO_DVE_CNFG_Y_REAL_S;

typedef union { /* VO_DVE_CNFG_O */
    U8 all;
    struct {
        U8 y_tsel_yuv                   : 4;
        U8                              : 4;
    } bitc;
} GH_VO_DVE_CNFG_O_REAL_S;

typedef union { /* VO_DVE_INOUT_MODE */
    U8 all;
    struct {
        U8 tencd_mode                   : 3;
        U8                              : 1;
        U8 tsync_mode                   : 2;
        U8 vsync                        : 1;
        U8 hsync                        : 1;
    } bitc;
} GH_VO_DVE_INOUT_MODE_REAL_S;

typedef union { /* VO_DVE_INPUT_SEL */
    U8 all;
    struct {
        U8 delay                        : 1;
        U8                              : 3;
        U8 t_fsync_phs                  : 1;
        U8 vsync_in                     : 1;
        U8 clk_div                      : 2;
    } bitc;
} GH_VO_DVE_INPUT_SEL_REAL_S;

typedef union { /* VO_DVE_HSYNC_OFF_H */
    U8 all;
    struct {
        U8 delay                        : 3;
        U8                              : 5;
    } bitc;
} GH_VO_DVE_HSYNC_OFF_H_REAL_S;

typedef union { /* VO_DVE_HLINE_LNGTH_H */
    U8 all;
    struct {
        U8 hlc                          : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_HLINE_LNGTH_H_REAL_S;

typedef union { /* VO_DVE_CC_EN */
    U8 all;
    struct {
        U8 odd                          : 1;
        U8 even                         : 1;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_CC_EN_REAL_S;

typedef union { /* VO_DVE_MVP_N2 */
    U8 all;
    struct {
        U8 spacing                      : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N2_REAL_S;

typedef union { /* VO_DVE_MVP_N4 */
    U8 all;
    struct {
        U8 spacing                      : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N4_REAL_S;

typedef union { /* VO_DVE_MVP_N567 */
    U8 all;
    struct {
        U8 csln                         : 2;
        U8 csnum                        : 3;
        U8 cssp                         : 3;
    } bitc;
} GH_VO_DVE_MVP_N567_REAL_S;

typedef union { /* VO_DVE_MVP_N8 */
    U8 all;
    struct {
        U8 psd                          : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N8_REAL_S;

typedef union { /* VO_DVE_MVP_N9 */
    U8 all;
    struct {
        U8 psl                          : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N9_REAL_S;

typedef union { /* VO_DVE_MVP_N10 */
    U8 all;
    struct {
        U8 pss                          : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N10_REAL_S;

typedef union { /* VO_DVE_MVP_N11_H */
    U8 all;
    struct {
        U8 sync_line                    : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_MVP_N11_H_REAL_S;

typedef union { /* VO_DVE_MVP_N12_H */
    U8 all;
    struct {
        U8 sync_line                    : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_MVP_N12_H_REAL_S;

typedef union { /* VO_DVE_BURST_ZONE_12 */
    U8 all;
    struct {
        U8 zone2                        : 4;
        U8 zone1                        : 4;
    } bitc;
} GH_VO_DVE_BURST_ZONE_12_REAL_S;

typedef union { /* VO_DVE_BURST_ZONE_EN */
    U8 all;
    struct {
        U8 invert                       : 3;
        U8 advanced                     : 1;
        U8 zone3                        : 4;
    } bitc;
} GH_VO_DVE_BURST_ZONE_EN_REAL_S;

typedef union { /* VO_DVE_MVP_N21_H */
    U8 all;
    struct {
        U8 invert                       : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_MVP_N21_H_REAL_S;

typedef union { /* VO_DVE_TEST_F */
    U8 all;
    struct {
        U8 enable                       : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_TEST_F_REAL_S;

typedef union { /* VO_DVE_TEST_YO */
    U8 all;
    struct {
        U8 ou                           : 4;
        U8 yu                           : 4;
    } bitc;
} GH_VO_DVE_TEST_YO_REAL_S;

typedef union { /* VO_DVE_TEST_C */
    U8 all;
    struct {
        U8 channel                      : 4;
        U8                              : 4;
    } bitc;
} GH_VO_DVE_TEST_C_REAL_S;

typedef union { /* VO_DVE_HLINE_VRST_H */
    U8 all;
    struct {
        U8 hlr                          : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_HLINE_VRST_H_REAL_S;

typedef union { /* VO_DVE_VSM_VRST */
    U8 all;
    struct {
        U8 vsmr                         : 5;
        U8                              : 3;
    } bitc;
} GH_VO_DVE_VSM_VRST_REAL_S;

typedef union { /* VO_DVE_SYNC_START */
    U8 all;
    struct {
        U8 start                        : 4;
        U8                              : 4;
    } bitc;
} GH_VO_DVE_SYNC_START_REAL_S;

typedef union { /* VO_DVE_SYNC_END */
    U8 all;
    struct {
        U8 end                          : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_SYNC_END_REAL_S;

typedef union { /* VO_DVE_SYNC_EQEND */
    U8 all;
    struct {
        U8 end                          : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_SYNC_EQEND_REAL_S;

typedef union { /* VO_DVE_WBRST_START */
    U8 all;
    struct {
        U8 start                        : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_WBRST_START_REAL_S;

typedef union { /* VO_DVE_NBRST_START */
    U8 all;
    struct {
        U8 start                        : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_NBRST_START_REAL_S;

typedef union { /* VO_DVE_CLOSED_CAPTION */
    U8 all;
    struct {
        U8 edstat                       : 1;
        U8 ccstat                       : 1;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_CLOSED_CAPTION_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_PHASE_INC_B0(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B0_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_INC_B0(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B0_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B1 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_PHASE_INC_B1(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B1_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_INC_B1(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B2 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_PHASE_INC_B2(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B2_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_INC_B2(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B2_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B3 (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_PHASE_INC_B3(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B3_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_INC_B3(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B3_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B0 (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_PHASE_OFFSET_B0(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B0_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_OFFSET_B0(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B0_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B1 (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_PHASE_OFFSET_B1(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B1_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_OFFSET_B1(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B2 (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_PHASE_OFFSET_B2(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B2_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_OFFSET_B2(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B2_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B3 (read/write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_PHASE_OFFSET_B3(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B3_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_OFFSET_B3(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B3_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_F (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_CNFG_F(U8 data)
{
    GH_VO_DVE_CNFG_F_REAL_S real;
    GH_VO_DVE_CNFG_F_S dummy;
    dummy.all = data ;
    real.bitc.reset = dummy.bitc.reset;
    real.bitc.config = dummy.bitc.config;
    *(volatile U8 *)REG_VO_DVE_CNFG_F_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_F(void)
{
    GH_VO_DVE_CNFG_F_REAL_S real;
    GH_VO_DVE_CNFG_F_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_CNFG_F_REAL);

    dummy.bitc.reset = real.bitc.reset;
    dummy.bitc.config = real.bitc.config;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_CNFG_F_reset(U8 data)
{
    GH_VO_DVE_CNFG_F_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_F_REAL;
    d.bitc.reset = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_F_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_F_reset(void)
{
    GH_VO_DVE_CNFG_F_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_F_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}
GH_INLINE void GH_VO_DVE_set_CNFG_F_config(U8 data)
{
    GH_VO_DVE_CNFG_F_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_F_REAL;
    d.bitc.config = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_F_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_F_config(void)
{
    GH_VO_DVE_CNFG_F_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_F_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.config;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BLACK_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_BLACK_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BLACK_LVL_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_BLACK_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BLACK_LVL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BLANK_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_BLANK_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BLANK_LVL_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_BLANK_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BLANK_LVL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CLAMP_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_CLAMP_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CLAMP_LVL_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_CLAMP_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLAMP_LVL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_LVL (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_SYNC_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_LVL_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_LVL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_Y (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_CNFG_Y(U8 data)
{
    GH_VO_DVE_CNFG_Y_REAL_S real;
    GH_VO_DVE_CNFG_Y_S dummy;
    dummy.all = data ;
    real.bitc.gain = dummy.bitc.gain;
    real.bitc.lpf_select = dummy.bitc.lpf_select;
    real.bitc.delay_config = dummy.bitc.delay_config;
    real.bitc.colorbar_en = dummy.bitc.colorbar_en;
    real.bitc.interpolation_mode = dummy.bitc.interpolation_mode;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y(void)
{
    GH_VO_DVE_CNFG_Y_REAL_S real;
    GH_VO_DVE_CNFG_Y_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL);

    dummy.bitc.gain = real.bitc.gain;
    dummy.bitc.lpf_select = real.bitc.lpf_select;
    dummy.bitc.delay_config = real.bitc.delay_config;
    dummy.bitc.colorbar_en = real.bitc.colorbar_en;
    dummy.bitc.interpolation_mode = real.bitc.interpolation_mode;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_gain(U8 data)
{
    GH_VO_DVE_CNFG_Y_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL;
    d.bitc.gain = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_gain(void)
{
    GH_VO_DVE_CNFG_Y_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.gain;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_LPF_select(U8 data)
{
    GH_VO_DVE_CNFG_Y_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL;
    d.bitc.lpf_select = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_LPF_select(void)
{
    GH_VO_DVE_CNFG_Y_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.lpf_select;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_delay_config(U8 data)
{
    GH_VO_DVE_CNFG_Y_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL;
    d.bitc.delay_config = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_delay_config(void)
{
    GH_VO_DVE_CNFG_Y_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.delay_config;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_colorbar_en(U8 data)
{
    GH_VO_DVE_CNFG_Y_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL;
    d.bitc.colorbar_en = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_colorbar_en(void)
{
    GH_VO_DVE_CNFG_Y_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.colorbar_en;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_interpolation_mode(U8 data)
{
    GH_VO_DVE_CNFG_Y_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL;
    d.bitc.interpolation_mode = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_interpolation_mode(void)
{
    GH_VO_DVE_CNFG_Y_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.interpolation_mode;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_O (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_CNFG_O(U8 data)
{
    GH_VO_DVE_CNFG_O_REAL_S real;
    GH_VO_DVE_CNFG_O_S dummy;
    dummy.all = data ;
    real.bitc.y_tsel_yuv = dummy.bitc.y_tsel_yuv;
    *(volatile U8 *)REG_VO_DVE_CNFG_O_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_O(void)
{
    GH_VO_DVE_CNFG_O_REAL_S real;
    GH_VO_DVE_CNFG_O_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_CNFG_O_REAL);

    dummy.bitc.y_tsel_yuv = real.bitc.y_tsel_yuv;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_CNFG_O_Y_TSEL_YUV(U8 data)
{
    GH_VO_DVE_CNFG_O_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_O_REAL;
    d.bitc.y_tsel_yuv = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_O_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_O_Y_TSEL_YUV(void)
{
    GH_VO_DVE_CNFG_O_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_O_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.y_tsel_yuv;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBA (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_NBA(U32 data)
{
    *(volatile U32 *)REG_VO_DVE_NBA_REAL = data;
}
GH_INLINE U32  GH_VO_DVE_get_NBA(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DVE_NBA_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PBA (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_PBA(U32 data)
{
    *(volatile U32 *)REG_VO_DVE_PBA_REAL = data;
}
GH_INLINE U32  GH_VO_DVE_get_PBA(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DVE_PBA_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_C (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_CNFG_C(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CNFG_C_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_C(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_C_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_INOUT_MODE (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_INOUT_MODE(U8 data)
{
    GH_VO_DVE_INOUT_MODE_REAL_S real;
    GH_VO_DVE_INOUT_MODE_S dummy;
    dummy.all = data ;
    real.bitc.tencd_mode = dummy.bitc.tencd_mode;
    real.bitc.tsync_mode = dummy.bitc.tsync_mode;
    real.bitc.vsync = dummy.bitc.vsync;
    real.bitc.hsync = dummy.bitc.hsync;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE(void)
{
    GH_VO_DVE_INOUT_MODE_REAL_S real;
    GH_VO_DVE_INOUT_MODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL);

    dummy.bitc.tencd_mode = real.bitc.tencd_mode;
    dummy.bitc.tsync_mode = real.bitc.tsync_mode;
    dummy.bitc.vsync = real.bitc.vsync;
    dummy.bitc.hsync = real.bitc.hsync;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_INOUT_MODE_tencd_mode(U8 data)
{
    GH_VO_DVE_INOUT_MODE_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL;
    d.bitc.tencd_mode = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE_tencd_mode(void)
{
    GH_VO_DVE_INOUT_MODE_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tencd_mode;
}
GH_INLINE void GH_VO_DVE_set_INOUT_MODE_tsync_mode(U8 data)
{
    GH_VO_DVE_INOUT_MODE_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL;
    d.bitc.tsync_mode = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE_tsync_mode(void)
{
    GH_VO_DVE_INOUT_MODE_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.tsync_mode;
}
GH_INLINE void GH_VO_DVE_set_INOUT_MODE_vsync(U8 data)
{
    GH_VO_DVE_INOUT_MODE_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL;
    d.bitc.vsync = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE_vsync(void)
{
    GH_VO_DVE_INOUT_MODE_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync;
}
GH_INLINE void GH_VO_DVE_set_INOUT_MODE_hsync(U8 data)
{
    GH_VO_DVE_INOUT_MODE_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL;
    d.bitc.hsync = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE_hsync(void)
{
    GH_VO_DVE_INOUT_MODE_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_INPUT_SEL (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_INPUT_SEL(U8 data)
{
    GH_VO_DVE_INPUT_SEL_REAL_S real;
    GH_VO_DVE_INPUT_SEL_S dummy;
    dummy.all = data ;
    real.bitc.delay = dummy.bitc.delay;
    real.bitc.t_fsync_phs = dummy.bitc.t_fsync_phs;
    real.bitc.vsync_in = dummy.bitc.vsync_in;
    real.bitc.clk_div = dummy.bitc.clk_div;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL(void)
{
    GH_VO_DVE_INPUT_SEL_REAL_S real;
    GH_VO_DVE_INPUT_SEL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL);

    dummy.bitc.delay = real.bitc.delay;
    dummy.bitc.t_fsync_phs = real.bitc.t_fsync_phs;
    dummy.bitc.vsync_in = real.bitc.vsync_in;
    dummy.bitc.clk_div = real.bitc.clk_div;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_INPUT_SEL_delay(U8 data)
{
    GH_VO_DVE_INPUT_SEL_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL;
    d.bitc.delay = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL_delay(void)
{
    GH_VO_DVE_INPUT_SEL_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.delay;
}
GH_INLINE void GH_VO_DVE_set_INPUT_SEL_T_FSYNC_PHS(U8 data)
{
    GH_VO_DVE_INPUT_SEL_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL;
    d.bitc.t_fsync_phs = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL_T_FSYNC_PHS(void)
{
    GH_VO_DVE_INPUT_SEL_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.t_fsync_phs;
}
GH_INLINE void GH_VO_DVE_set_INPUT_SEL_vsync_in(U8 data)
{
    GH_VO_DVE_INPUT_SEL_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL;
    d.bitc.vsync_in = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL_vsync_in(void)
{
    GH_VO_DVE_INPUT_SEL_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_in;
}
GH_INLINE void GH_VO_DVE_set_INPUT_SEL_clk_div(U8 data)
{
    GH_VO_DVE_INPUT_SEL_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL;
    d.bitc.clk_div = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL_clk_div(void)
{
    GH_VO_DVE_INPUT_SEL_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.clk_div;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_VSYNC_OFF (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_VSYNC_OFF(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_VSYNC_OFF_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_VSYNC_OFF(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_VSYNC_OFF_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HSYNC_OFF_H (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_HSYNC_OFF_H(U8 data)
{
    GH_VO_DVE_HSYNC_OFF_H_REAL_S real;
    GH_VO_DVE_HSYNC_OFF_H_S dummy;
    dummy.all = data ;
    real.bitc.delay = dummy.bitc.delay;
    *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_HSYNC_OFF_H(void)
{
    GH_VO_DVE_HSYNC_OFF_H_REAL_S real;
    GH_VO_DVE_HSYNC_OFF_H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H_REAL);

    dummy.bitc.delay = real.bitc.delay;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_HSYNC_OFF_H_delay(U8 data)
{
    GH_VO_DVE_HSYNC_OFF_H_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H_REAL;
    d.bitc.delay = data;
    *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_HSYNC_OFF_H_delay(void)
{
    GH_VO_DVE_HSYNC_OFF_H_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.delay;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HSYNC_OFF_L (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_HSYNC_OFF_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_L_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_HSYNC_OFF_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HSYNC_OFF_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_LNGTH_H (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_HLINE_LNGTH_H(U8 data)
{
    GH_VO_DVE_HLINE_LNGTH_H_REAL_S real;
    GH_VO_DVE_HLINE_LNGTH_H_S dummy;
    dummy.all = data ;
    real.bitc.hlc = dummy.bitc.hlc;
    *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_LNGTH_H(void)
{
    GH_VO_DVE_HLINE_LNGTH_H_REAL_S real;
    GH_VO_DVE_HLINE_LNGTH_H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H_REAL);

    dummy.bitc.hlc = real.bitc.hlc;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_HLINE_LNGTH_H_HLC(U8 data)
{
    GH_VO_DVE_HLINE_LNGTH_H_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H_REAL;
    d.bitc.hlc = data;
    *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_LNGTH_H_HLC(void)
{
    GH_VO_DVE_HLINE_LNGTH_H_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hlc;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_LNGTH_L (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_HLINE_LNGTH_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_L_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_LNGTH_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_DATA_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_CC_DATA_H(U8 index, U8 data)
{
    *(volatile U8 *)(REG_VO_DVE_CC_DATA_H_REAL + index * FIO_MOFFSET(VO_DVE,0x00000008)) = data;
}
GH_INLINE U8   GH_VO_DVE_get_CC_DATA_H(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_VO_DVE_CC_DATA_H_REAL + index * FIO_MOFFSET(VO_DVE,0x00000008)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_DATA_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_CC_DATA_L(U8 index, U8 data)
{
    *(volatile U8 *)(REG_VO_DVE_CC_DATA_L_REAL + index * FIO_MOFFSET(VO_DVE,0x00000008)) = data;
}
GH_INLINE U8   GH_VO_DVE_get_CC_DATA_L(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_VO_DVE_CC_DATA_L_REAL + index * FIO_MOFFSET(VO_DVE,0x00000008)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_EN (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_CC_EN(U8 data)
{
    GH_VO_DVE_CC_EN_REAL_S real;
    GH_VO_DVE_CC_EN_S dummy;
    dummy.all = data ;
    real.bitc.odd = dummy.bitc.odd;
    real.bitc.even = dummy.bitc.even;
    *(volatile U8 *)REG_VO_DVE_CC_EN_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_CC_EN(void)
{
    GH_VO_DVE_CC_EN_REAL_S real;
    GH_VO_DVE_CC_EN_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_CC_EN_REAL);

    dummy.bitc.odd = real.bitc.odd;
    dummy.bitc.even = real.bitc.even;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_CC_EN_odd(U8 data)
{
    GH_VO_DVE_CC_EN_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CC_EN_REAL;
    d.bitc.odd = data;
    *(volatile U8 *)REG_VO_DVE_CC_EN_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CC_EN_odd(void)
{
    GH_VO_DVE_CC_EN_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CC_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.odd;
}
GH_INLINE void GH_VO_DVE_set_CC_EN_even(U8 data)
{
    GH_VO_DVE_CC_EN_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CC_EN_REAL;
    d.bitc.even = data;
    *(volatile U8 *)REG_VO_DVE_CC_EN_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_CC_EN_even(void)
{
    GH_VO_DVE_CC_EN_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CC_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.even;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N0 (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N0(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N0_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N0(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N0_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N1 (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N1(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N1_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N1(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N2 (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N2(U8 data)
{
    GH_VO_DVE_MVP_N2_REAL_S real;
    GH_VO_DVE_MVP_N2_S dummy;
    dummy.all = data ;
    real.bitc.spacing = dummy.bitc.spacing;
    *(volatile U8 *)REG_VO_DVE_MVP_N2_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N2(void)
{
    GH_VO_DVE_MVP_N2_REAL_S real;
    GH_VO_DVE_MVP_N2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_MVP_N2_REAL);

    dummy.bitc.spacing = real.bitc.spacing;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_MVP_N2_spacing(U8 data)
{
    GH_VO_DVE_MVP_N2_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N2_REAL;
    d.bitc.spacing = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N2_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N2_spacing(void)
{
    GH_VO_DVE_MVP_N2_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N2_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.spacing;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N3 (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N3(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N3_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N3(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N3_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N4 (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N4(U8 data)
{
    GH_VO_DVE_MVP_N4_REAL_S real;
    GH_VO_DVE_MVP_N4_S dummy;
    dummy.all = data ;
    real.bitc.spacing = dummy.bitc.spacing;
    *(volatile U8 *)REG_VO_DVE_MVP_N4_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N4(void)
{
    GH_VO_DVE_MVP_N4_REAL_S real;
    GH_VO_DVE_MVP_N4_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_MVP_N4_REAL);

    dummy.bitc.spacing = real.bitc.spacing;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_MVP_N4_spacing(U8 data)
{
    GH_VO_DVE_MVP_N4_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N4_REAL;
    d.bitc.spacing = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N4_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N4_spacing(void)
{
    GH_VO_DVE_MVP_N4_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N4_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.spacing;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N567 (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N567(U8 data)
{
    GH_VO_DVE_MVP_N567_REAL_S real;
    GH_VO_DVE_MVP_N567_S dummy;
    dummy.all = data ;
    real.bitc.csln = dummy.bitc.csln;
    real.bitc.csnum = dummy.bitc.csnum;
    real.bitc.cssp = dummy.bitc.cssp;
    *(volatile U8 *)REG_VO_DVE_MVP_N567_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N567(void)
{
    GH_VO_DVE_MVP_N567_REAL_S real;
    GH_VO_DVE_MVP_N567_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_MVP_N567_REAL);

    dummy.bitc.csln = real.bitc.csln;
    dummy.bitc.csnum = real.bitc.csnum;
    dummy.bitc.cssp = real.bitc.cssp;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_MVP_N567_CSLN(U8 data)
{
    GH_VO_DVE_MVP_N567_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N567_REAL;
    d.bitc.csln = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N567_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N567_CSLN(void)
{
    GH_VO_DVE_MVP_N567_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.csln;
}
GH_INLINE void GH_VO_DVE_set_MVP_N567_CSNUM(U8 data)
{
    GH_VO_DVE_MVP_N567_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N567_REAL;
    d.bitc.csnum = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N567_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N567_CSNUM(void)
{
    GH_VO_DVE_MVP_N567_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.csnum;
}
GH_INLINE void GH_VO_DVE_set_MVP_N567_CSSP(U8 data)
{
    GH_VO_DVE_MVP_N567_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N567_REAL;
    d.bitc.cssp = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N567_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N567_CSSP(void)
{
    GH_VO_DVE_MVP_N567_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cssp;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N8 (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N8(U8 data)
{
    GH_VO_DVE_MVP_N8_REAL_S real;
    GH_VO_DVE_MVP_N8_S dummy;
    dummy.all = data ;
    real.bitc.psd = dummy.bitc.psd;
    *(volatile U8 *)REG_VO_DVE_MVP_N8_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N8(void)
{
    GH_VO_DVE_MVP_N8_REAL_S real;
    GH_VO_DVE_MVP_N8_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_MVP_N8_REAL);

    dummy.bitc.psd = real.bitc.psd;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_MVP_N8_PSD(U8 data)
{
    GH_VO_DVE_MVP_N8_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N8_REAL;
    d.bitc.psd = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N8_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N8_PSD(void)
{
    GH_VO_DVE_MVP_N8_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N8_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.psd;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N9 (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N9(U8 data)
{
    GH_VO_DVE_MVP_N9_REAL_S real;
    GH_VO_DVE_MVP_N9_S dummy;
    dummy.all = data ;
    real.bitc.psl = dummy.bitc.psl;
    *(volatile U8 *)REG_VO_DVE_MVP_N9_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N9(void)
{
    GH_VO_DVE_MVP_N9_REAL_S real;
    GH_VO_DVE_MVP_N9_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_MVP_N9_REAL);

    dummy.bitc.psl = real.bitc.psl;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_MVP_N9_PSL(U8 data)
{
    GH_VO_DVE_MVP_N9_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N9_REAL;
    d.bitc.psl = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N9_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N9_PSL(void)
{
    GH_VO_DVE_MVP_N9_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N9_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.psl;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N10 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N10(U8 data)
{
    GH_VO_DVE_MVP_N10_REAL_S real;
    GH_VO_DVE_MVP_N10_S dummy;
    dummy.all = data ;
    real.bitc.pss = dummy.bitc.pss;
    *(volatile U8 *)REG_VO_DVE_MVP_N10_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N10(void)
{
    GH_VO_DVE_MVP_N10_REAL_S real;
    GH_VO_DVE_MVP_N10_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_MVP_N10_REAL);

    dummy.bitc.pss = real.bitc.pss;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_MVP_N10_PSS(U8 data)
{
    GH_VO_DVE_MVP_N10_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N10_REAL;
    d.bitc.pss = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N10_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N10_PSS(void)
{
    GH_VO_DVE_MVP_N10_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N10_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pss;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N11_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N11_H(U8 data)
{
    GH_VO_DVE_MVP_N11_H_REAL_S real;
    GH_VO_DVE_MVP_N11_H_S dummy;
    dummy.all = data ;
    real.bitc.sync_line = dummy.bitc.sync_line;
    *(volatile U8 *)REG_VO_DVE_MVP_N11_H_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N11_H(void)
{
    GH_VO_DVE_MVP_N11_H_REAL_S real;
    GH_VO_DVE_MVP_N11_H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_MVP_N11_H_REAL);

    dummy.bitc.sync_line = real.bitc.sync_line;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_MVP_N11_H_sync_line(U8 data)
{
    GH_VO_DVE_MVP_N11_H_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N11_H_REAL;
    d.bitc.sync_line = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N11_H_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N11_H_sync_line(void)
{
    GH_VO_DVE_MVP_N11_H_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N11_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sync_line;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N11_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N11_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N11_L_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N11_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N11_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N12_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N12_H(U8 data)
{
    GH_VO_DVE_MVP_N12_H_REAL_S real;
    GH_VO_DVE_MVP_N12_H_S dummy;
    dummy.all = data ;
    real.bitc.sync_line = dummy.bitc.sync_line;
    *(volatile U8 *)REG_VO_DVE_MVP_N12_H_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N12_H(void)
{
    GH_VO_DVE_MVP_N12_H_REAL_S real;
    GH_VO_DVE_MVP_N12_H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_MVP_N12_H_REAL);

    dummy.bitc.sync_line = real.bitc.sync_line;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_MVP_N12_H_sync_line(U8 data)
{
    GH_VO_DVE_MVP_N12_H_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N12_H_REAL;
    d.bitc.sync_line = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N12_H_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N12_H_sync_line(void)
{
    GH_VO_DVE_MVP_N12_H_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N12_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sync_line;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N12_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N12_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N12_L_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N12_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N12_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N13 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N13(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N13_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N13(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N13_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N14 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N14(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N14_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N14(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N14_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N15 (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N15(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N15_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N15(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N15_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BURST_ZONE_12 (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_12(U8 data)
{
    GH_VO_DVE_BURST_ZONE_12_REAL_S real;
    GH_VO_DVE_BURST_ZONE_12_S dummy;
    dummy.all = data ;
    real.bitc.zone2 = dummy.bitc.zone2;
    real.bitc.zone1 = dummy.bitc.zone1;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_12(void)
{
    GH_VO_DVE_BURST_ZONE_12_REAL_S real;
    GH_VO_DVE_BURST_ZONE_12_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_12_REAL);

    dummy.bitc.zone2 = real.bitc.zone2;
    dummy.bitc.zone1 = real.bitc.zone1;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_12_zone2(U8 data)
{
    GH_VO_DVE_BURST_ZONE_12_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12_REAL;
    d.bitc.zone2 = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_12_zone2(void)
{
    GH_VO_DVE_BURST_ZONE_12_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_12_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.zone2;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_12_zone1(U8 data)
{
    GH_VO_DVE_BURST_ZONE_12_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12_REAL;
    d.bitc.zone1 = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_12_zone1(void)
{
    GH_VO_DVE_BURST_ZONE_12_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_12_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.zone1;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BURST_ZONE_EN (read/write)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_EN(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_REAL_S real;
    GH_VO_DVE_BURST_ZONE_EN_S dummy;
    dummy.all = data ;
    real.bitc.invert = dummy.bitc.invert;
    real.bitc.advanced = dummy.bitc.advanced;
    real.bitc.zone3 = dummy.bitc.zone3;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_EN(void)
{
    GH_VO_DVE_BURST_ZONE_EN_REAL_S real;
    GH_VO_DVE_BURST_ZONE_EN_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL);

    dummy.bitc.invert = real.bitc.invert;
    dummy.bitc.advanced = real.bitc.advanced;
    dummy.bitc.zone3 = real.bitc.zone3;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_EN_invert(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL;
    d.bitc.invert = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_EN_invert(void)
{
    GH_VO_DVE_BURST_ZONE_EN_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.invert;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_EN_advanced(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL;
    d.bitc.advanced = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_EN_advanced(void)
{
    GH_VO_DVE_BURST_ZONE_EN_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.advanced;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_EN_zone3(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL;
    d.bitc.zone3 = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_EN_zone3(void)
{
    GH_VO_DVE_BURST_ZONE_EN_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.zone3;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N21_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N21_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N21_L_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N21_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N21_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N21_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MVP_N21_H(U8 data)
{
    GH_VO_DVE_MVP_N21_H_REAL_S real;
    GH_VO_DVE_MVP_N21_H_S dummy;
    dummy.all = data ;
    real.bitc.invert = dummy.bitc.invert;
    *(volatile U8 *)REG_VO_DVE_MVP_N21_H_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N21_H(void)
{
    GH_VO_DVE_MVP_N21_H_REAL_S real;
    GH_VO_DVE_MVP_N21_H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_MVP_N21_H_REAL);

    dummy.bitc.invert = real.bitc.invert;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_MVP_N21_H_invert(U8 data)
{
    GH_VO_DVE_MVP_N21_H_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N21_H_REAL;
    d.bitc.invert = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N21_H_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N21_H_invert(void)
{
    GH_VO_DVE_MVP_N21_H_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N21_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.invert;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_F (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_TEST_F(U8 data)
{
    GH_VO_DVE_TEST_F_REAL_S real;
    GH_VO_DVE_TEST_F_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U8 *)REG_VO_DVE_TEST_F_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_TEST_F(void)
{
    GH_VO_DVE_TEST_F_REAL_S real;
    GH_VO_DVE_TEST_F_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_TEST_F_REAL);

    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_TEST_F_enable(U8 data)
{
    GH_VO_DVE_TEST_F_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_F_REAL;
    d.bitc.enable = data;
    *(volatile U8 *)REG_VO_DVE_TEST_F_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_TEST_F_enable(void)
{
    GH_VO_DVE_TEST_F_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_F_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_YO (read/write)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_TEST_YO(U8 data)
{
    GH_VO_DVE_TEST_YO_REAL_S real;
    GH_VO_DVE_TEST_YO_S dummy;
    dummy.all = data ;
    real.bitc.ou = dummy.bitc.ou;
    real.bitc.yu = dummy.bitc.yu;
    *(volatile U8 *)REG_VO_DVE_TEST_YO_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_TEST_YO(void)
{
    GH_VO_DVE_TEST_YO_REAL_S real;
    GH_VO_DVE_TEST_YO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_TEST_YO_REAL);

    dummy.bitc.ou = real.bitc.ou;
    dummy.bitc.yu = real.bitc.yu;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_TEST_YO_ou(U8 data)
{
    GH_VO_DVE_TEST_YO_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_YO_REAL;
    d.bitc.ou = data;
    *(volatile U8 *)REG_VO_DVE_TEST_YO_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_TEST_YO_ou(void)
{
    GH_VO_DVE_TEST_YO_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_YO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ou;
}
GH_INLINE void GH_VO_DVE_set_TEST_YO_yu(U8 data)
{
    GH_VO_DVE_TEST_YO_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_YO_REAL;
    d.bitc.yu = data;
    *(volatile U8 *)REG_VO_DVE_TEST_YO_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_TEST_YO_yu(void)
{
    GH_VO_DVE_TEST_YO_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_YO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.yu;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_C (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_TEST_C(U8 data)
{
    GH_VO_DVE_TEST_C_REAL_S real;
    GH_VO_DVE_TEST_C_S dummy;
    dummy.all = data ;
    real.bitc.channel = dummy.bitc.channel;
    *(volatile U8 *)REG_VO_DVE_TEST_C_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_TEST_C(void)
{
    GH_VO_DVE_TEST_C_REAL_S real;
    GH_VO_DVE_TEST_C_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_TEST_C_REAL);

    dummy.bitc.channel = real.bitc.channel;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_TEST_C_channel(U8 data)
{
    GH_VO_DVE_TEST_C_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_C_REAL;
    d.bitc.channel = data;
    *(volatile U8 *)REG_VO_DVE_TEST_C_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_TEST_C_channel(void)
{
    GH_VO_DVE_TEST_C_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_C_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.channel;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MACV_TEST (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_MACV_TEST(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MACV_TEST_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_MACV_TEST(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MACV_TEST_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_VRST_H (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_HLINE_VRST_H(U8 data)
{
    GH_VO_DVE_HLINE_VRST_H_REAL_S real;
    GH_VO_DVE_HLINE_VRST_H_S dummy;
    dummy.all = data ;
    real.bitc.hlr = dummy.bitc.hlr;
    *(volatile U8 *)REG_VO_DVE_HLINE_VRST_H_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_VRST_H(void)
{
    GH_VO_DVE_HLINE_VRST_H_REAL_S real;
    GH_VO_DVE_HLINE_VRST_H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_HLINE_VRST_H_REAL);

    dummy.bitc.hlr = real.bitc.hlr;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_HLINE_VRST_H_HLR(U8 data)
{
    GH_VO_DVE_HLINE_VRST_H_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_HLINE_VRST_H_REAL;
    d.bitc.hlr = data;
    *(volatile U8 *)REG_VO_DVE_HLINE_VRST_H_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_VRST_H_HLR(void)
{
    GH_VO_DVE_HLINE_VRST_H_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_VRST_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hlr;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_VRST_L (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_HLINE_VRST_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_VRST_L_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_VRST_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_VRST_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_VSM_VRST (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_VSM_VRST(U8 data)
{
    GH_VO_DVE_VSM_VRST_REAL_S real;
    GH_VO_DVE_VSM_VRST_S dummy;
    dummy.all = data ;
    real.bitc.vsmr = dummy.bitc.vsmr;
    *(volatile U8 *)REG_VO_DVE_VSM_VRST_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_VSM_VRST(void)
{
    GH_VO_DVE_VSM_VRST_REAL_S real;
    GH_VO_DVE_VSM_VRST_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_VSM_VRST_REAL);

    dummy.bitc.vsmr = real.bitc.vsmr;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_VSM_VRST_VSMR(U8 data)
{
    GH_VO_DVE_VSM_VRST_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_VSM_VRST_REAL;
    d.bitc.vsmr = data;
    *(volatile U8 *)REG_VO_DVE_VSM_VRST_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_VSM_VRST_VSMR(void)
{
    GH_VO_DVE_VSM_VRST_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_VSM_VRST_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsmr;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_START (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_SYNC_START(U8 data)
{
    GH_VO_DVE_SYNC_START_REAL_S real;
    GH_VO_DVE_SYNC_START_S dummy;
    dummy.all = data ;
    real.bitc.start = dummy.bitc.start;
    *(volatile U8 *)REG_VO_DVE_SYNC_START_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_START(void)
{
    GH_VO_DVE_SYNC_START_REAL_S real;
    GH_VO_DVE_SYNC_START_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_SYNC_START_REAL);

    dummy.bitc.start = real.bitc.start;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_SYNC_START_start(U8 data)
{
    GH_VO_DVE_SYNC_START_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_SYNC_START_REAL;
    d.bitc.start = data;
    *(volatile U8 *)REG_VO_DVE_SYNC_START_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_START_start(void)
{
    GH_VO_DVE_SYNC_START_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_END (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_SYNC_END(U8 data)
{
    GH_VO_DVE_SYNC_END_REAL_S real;
    GH_VO_DVE_SYNC_END_S dummy;
    dummy.all = data ;
    real.bitc.end = dummy.bitc.end;
    *(volatile U8 *)REG_VO_DVE_SYNC_END_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_END(void)
{
    GH_VO_DVE_SYNC_END_REAL_S real;
    GH_VO_DVE_SYNC_END_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_SYNC_END_REAL);

    dummy.bitc.end = real.bitc.end;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_SYNC_END_end(U8 data)
{
    GH_VO_DVE_SYNC_END_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_SYNC_END_REAL;
    d.bitc.end = data;
    *(volatile U8 *)REG_VO_DVE_SYNC_END_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_END_end(void)
{
    GH_VO_DVE_SYNC_END_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_END_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.end;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_SREND (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_SYNC_SREND(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_SREND_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_SREND(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_SREND_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_EQEND (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_SYNC_EQEND(U8 data)
{
    GH_VO_DVE_SYNC_EQEND_REAL_S real;
    GH_VO_DVE_SYNC_EQEND_S dummy;
    dummy.all = data ;
    real.bitc.end = dummy.bitc.end;
    *(volatile U8 *)REG_VO_DVE_SYNC_EQEND_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_EQEND(void)
{
    GH_VO_DVE_SYNC_EQEND_REAL_S real;
    GH_VO_DVE_SYNC_EQEND_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_SYNC_EQEND_REAL);

    dummy.bitc.end = real.bitc.end;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_SYNC_EQEND_end(U8 data)
{
    GH_VO_DVE_SYNC_EQEND_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_SYNC_EQEND_REAL;
    d.bitc.end = data;
    *(volatile U8 *)REG_VO_DVE_SYNC_EQEND_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_EQEND_end(void)
{
    GH_VO_DVE_SYNC_EQEND_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_EQEND_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.end;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_ACTIVE_START (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_ACTIVE_START(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_ACTIVE_START_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_ACTIVE_START(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_ACTIVE_START_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_ACTIVE_END (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_ACTIVE_END(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_ACTIVE_END_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_ACTIVE_END(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_ACTIVE_END_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_WBRST_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_WBRST_START(U8 data)
{
    GH_VO_DVE_WBRST_START_REAL_S real;
    GH_VO_DVE_WBRST_START_S dummy;
    dummy.all = data ;
    real.bitc.start = dummy.bitc.start;
    *(volatile U8 *)REG_VO_DVE_WBRST_START_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_WBRST_START(void)
{
    GH_VO_DVE_WBRST_START_REAL_S real;
    GH_VO_DVE_WBRST_START_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_WBRST_START_REAL);

    dummy.bitc.start = real.bitc.start;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_WBRST_START_start(U8 data)
{
    GH_VO_DVE_WBRST_START_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_WBRST_START_REAL;
    d.bitc.start = data;
    *(volatile U8 *)REG_VO_DVE_WBRST_START_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_WBRST_START_start(void)
{
    GH_VO_DVE_WBRST_START_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_WBRST_START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBRST_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_NBRST_START(U8 data)
{
    GH_VO_DVE_NBRST_START_REAL_S real;
    GH_VO_DVE_NBRST_START_S dummy;
    dummy.all = data ;
    real.bitc.start = dummy.bitc.start;
    *(volatile U8 *)REG_VO_DVE_NBRST_START_REAL = real.all;
}
GH_INLINE U8   GH_VO_DVE_get_NBRST_START(void)
{
    GH_VO_DVE_NBRST_START_REAL_S real;
    GH_VO_DVE_NBRST_START_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_NBRST_START_REAL);

    dummy.bitc.start = real.bitc.start;
    return dummy.all;
}
GH_INLINE void GH_VO_DVE_set_NBRST_START_start(U8 data)
{
    GH_VO_DVE_NBRST_START_REAL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_NBRST_START_REAL;
    d.bitc.start = data;
    *(volatile U8 *)REG_VO_DVE_NBRST_START_REAL = d.all;
}
GH_INLINE U8   GH_VO_DVE_get_NBRST_START_start(void)
{
    GH_VO_DVE_NBRST_START_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_NBRST_START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBRST_END (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_set_NBRST_END(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_NBRST_END_REAL = data;
}
GH_INLINE U8   GH_VO_DVE_get_NBRST_END(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_NBRST_END_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CLOSED_CAPTION (read)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U8   GH_VO_DVE_get_CLOSED_CAPTION(void)
{
    GH_VO_DVE_CLOSED_CAPTION_REAL_S real;
    GH_VO_DVE_CLOSED_CAPTION_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U8 *)REG_VO_DVE_CLOSED_CAPTION_REAL);

    dummy.bitc.edstat = real.bitc.edstat;
    dummy.bitc.ccstat = real.bitc.ccstat;
    return dummy.all;
}
GH_INLINE U8   GH_VO_DVE_get_CLOSED_CAPTION_EDSTAT(void)
{
    GH_VO_DVE_CLOSED_CAPTION_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLOSED_CAPTION_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.edstat;
}
GH_INLINE U8   GH_VO_DVE_get_CLOSED_CAPTION_CCSTAT(void)
{
    GH_VO_DVE_CLOSED_CAPTION_REAL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLOSED_CAPTION_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ccstat;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DVE_init(void)
{
    int i;

    GH_VO_DVE_set_PHASE_INC_B0((U8)0x0000001f);
    GH_VO_DVE_set_PHASE_INC_B1((U8)0x0000007c);
    GH_VO_DVE_set_PHASE_INC_B2((U8)0x000000f0);
    GH_VO_DVE_set_PHASE_INC_B3((U8)0x00000021);
    GH_VO_DVE_set_PHASE_OFFSET_B0((U8)0x00000000);
    GH_VO_DVE_set_PHASE_OFFSET_B1((U8)0x00000000);
    GH_VO_DVE_set_PHASE_OFFSET_B2((U8)0x00000000);
    GH_VO_DVE_set_PHASE_OFFSET_B3((U8)0x00000000);
    GH_VO_DVE_set_CNFG_F((U8)0x00000000);
    GH_VO_DVE_set_BLACK_LVL((U8)0x00000000);
    GH_VO_DVE_set_BLANK_LVL((U8)0x00000000);
    GH_VO_DVE_set_CLAMP_LVL((U8)0x00000000);
    GH_VO_DVE_set_SYNC_LVL((U8)0x00000000);
    GH_VO_DVE_set_CNFG_Y((U8)0x00000010);
    GH_VO_DVE_set_CNFG_O((U8)0x00000000);
    GH_VO_DVE_set_NBA((U32)0x000000c8);
    GH_VO_DVE_set_PBA((U32)0x00000000);
    GH_VO_DVE_set_CNFG_C((U8)0x00000000);
    GH_VO_DVE_set_INOUT_MODE((U8)0x00000030);
    GH_VO_DVE_set_INPUT_SEL((U8)0x00000000);
    GH_VO_DVE_set_VSYNC_OFF((U8)0x00000000);
    GH_VO_DVE_set_HSYNC_OFF_H((U8)0x00000000);
    GH_VO_DVE_set_HSYNC_OFF_L((U8)0x00000000);
    GH_VO_DVE_set_HLINE_LNGTH_H((U8)0x00000000);
    GH_VO_DVE_set_HLINE_LNGTH_L((U8)0x00000000);
    for (i=0; i<2; i++)
    {
        GH_VO_DVE_set_CC_DATA_H(i, (U8)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VO_DVE_set_CC_DATA_L(i, (U8)0x00000000);
    }
    GH_VO_DVE_set_CC_EN((U8)0x00000000);
    GH_VO_DVE_set_MVP_N0((U8)0x0000003e);
    GH_VO_DVE_set_MVP_N1((U8)0x0000002e);
    GH_VO_DVE_set_MVP_N2((U8)0x00000015);
    GH_VO_DVE_set_MVP_N3((U8)0x0000002e);
    GH_VO_DVE_set_MVP_N4((U8)0x00000015);
    GH_VO_DVE_set_MVP_N567((U8)0x000000b6);
    GH_VO_DVE_set_MVP_N8((U8)0x0000001b);
    GH_VO_DVE_set_MVP_N9((U8)0x0000001b);
    GH_VO_DVE_set_MVP_N10((U8)0x00000024);
    GH_VO_DVE_set_MVP_N11_H((U8)0x00000024);
    GH_VO_DVE_set_MVP_N11_L((U8)0x000000e0);
    GH_VO_DVE_set_MVP_N12_H((U8)0x00000000);
    GH_VO_DVE_set_MVP_N12_L((U8)0x00000000);
    GH_VO_DVE_set_MVP_N13((U8)0x0000000f);
    GH_VO_DVE_set_MVP_N14((U8)0x0000000f);
    GH_VO_DVE_set_MVP_N15((U8)0x00000090);
    GH_VO_DVE_set_BURST_ZONE_12((U8)0x000000a0);
    GH_VO_DVE_set_BURST_ZONE_EN((U8)0x0000005c);
    GH_VO_DVE_set_MVP_N21_L((U8)0x000000ff);
    GH_VO_DVE_set_MVP_N21_H((U8)0x00000003);
    GH_VO_DVE_set_TEST_F((U8)0x00000000);
    GH_VO_DVE_set_TEST_YO((U8)0x00000000);
    GH_VO_DVE_set_TEST_C((U8)0x00000000);
    GH_VO_DVE_set_MACV_TEST((U8)0x00000000);
    GH_VO_DVE_set_HLINE_VRST_H((U8)0x00000000);
    GH_VO_DVE_set_HLINE_VRST_L((U8)0x00000000);
    GH_VO_DVE_set_VSM_VRST((U8)0x00000010);
    GH_VO_DVE_set_SYNC_START((U8)0x0000000c);
    GH_VO_DVE_set_SYNC_END((U8)0x0000004c);
    GH_VO_DVE_set_SYNC_SREND((U8)0x00000079);
    GH_VO_DVE_set_SYNC_EQEND((U8)0x0000002c);
    GH_VO_DVE_set_ACTIVE_START((U8)0x00000089);
    GH_VO_DVE_set_ACTIVE_END((U8)0x000000a4);
    GH_VO_DVE_set_WBRST_START((U8)0x0000005a);
    GH_VO_DVE_set_NBRST_START((U8)0x00000062);
    GH_VO_DVE_set_NBRST_END((U8)0x00000084);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

